"""
对 BFS 树中所有 script_instance 节点，读取其 GDScript 脚本对象，扫描脚本内存里
指向「含 res:// 或 .gd 或 Game」的堆字符串的指针，从而按脚本资源路径定位 Game。

用法：
  python tools/script_path_scan.py --pid 18616
"""
import argparse
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent.parent))

from core.memory_reader import MemoryReader
from core.godot_probe import read_module_sections, _read_u64, _is_plausible_ptr, _is_valid_instance


def find_si(reader, is_inst, node):
    nmem = reader.read(node, 0x400) or b""
    for i in range(0, len(nmem) - 8, 8):
        q = int.from_bytes(nmem[i:i + 8], "little")
        if _is_plausible_ptr(q) and is_inst(q) and _read_u64(reader, q + 8) == node:
            return q
    return None


def scan_script_path(reader, script_ptr):
    smem = reader.read(script_ptr, 0x400) or b""
    hits = []
    for i in range(0, len(smem) - 8, 8):
        sp = int.from_bytes(smem[i:i + 8], "little")
        if not _is_plausible_ptr(sp):
            continue
        # UTF-8
        raw = reader.read(sp, 260)
        if raw:
            for m in re.finditer(rb"[\x20-\x7e]{4,}", raw):
                s = m.group()
                if b"res://" in s or b".gd" in s or b"Game" in s:
                    try:
                        hits.append(s.decode("ascii", "replace"))
                    except Exception:
                        pass
        # UTF-32
        raw2 = reader.read(sp, 256)
        if raw2:
            chars = []
            for j in range(0, 256, 4):
                u = int.from_bytes(raw2[j:j + 4], "little")
                if 32 <= u < 127:
                    chars.append(chr(u))
                else:
                    break
            s = "".join(chars)
            if 4 <= len(s) <= 60 and ("res://" in s or ".gd" in s or "Game" in s):
                hits.append(s)
    return hits


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--pid", type=int, required=True)
    args = ap.parse_args()

    reader = MemoryReader(args.pid)
    base = reader.module_base
    secs = read_module_sections(reader)
    text = next(s for s in secs if s[0] == ".text")
    rdata = next(s for s in secs if s[0] == ".rdata")
    data = next(s for s in secs if s[0] == ".data")
    text_lo, text_hi = base + text[1], base + text[1] + text[2]
    rdata_lo, rdata_hi = base + rdata[1], base + rdata[1] + rdata[2]

    _cache = {}
    def is_inst(a):
        if a in _cache:
            return _cache[a]
        r = _is_valid_instance(reader, a, text_lo, text_hi, rdata_lo, rdata_hi)
        _cache[a] = r
        return r

    instances = []
    addr = base + data[1]; end = addr + data[2]
    while addr < end:
        buf = reader.read(addr, min(1024 * 1024, end - addr))
        if not buf:
            break
        off = 0
        while off + 8 <= len(buf):
            obj = int.from_bytes(buf[off:off + 8], "little")
            if _is_plausible_ptr(obj) and is_inst(obj):
                instances.append(obj)
            off += 8
        addr += len(buf)

    chain = None
    for obj in instances:
        s = _read_u64(reader, obj + 0x1d0)
        if not _is_plausible_ptr(s) or not is_inst(s) or s == obj:
            continue
        r = _read_u64(reader, s + 0x230)
        if _is_plausible_ptr(r) and is_inst(r) and r != s:
            chain = (obj, s, r)
            break
    if not chain:
        print("[-] 链路未找到"); return 1
    obj, s, r = chain
    print(f"[*] root={hex(r)}")

    visited = set()
    queue = [(r, 0)]
    visited.add(r)
    found = []
    while queue:
        node, depth = queue.pop(0)
        if depth >= 2:
            continue
        if not is_inst(node):
            continue
        si = find_si(reader, is_inst, node)
        if si is not None:
            script_ptr = _read_u64(reader, si + 0x10)
            if _is_plausible_ptr(script_ptr):
                hits = scan_script_path(reader, script_ptr)
                if hits:
                    print(f"  node={hex(node)} si={hex(si)} script={hex(script_ptr)} paths={hits}")
                    found.append((node, si, script_ptr, hits))
        first = _read_u64(reader, node + 0x6c0)
        cur = first
        seen = set()
        for _ in range(400):
            if not _is_plausible_ptr(cur) or cur in seen:
                break
            seen.add(cur)
            v = _read_u64(reader, cur)
            if _is_plausible_ptr(v) and is_inst(v) and v not in visited:
                visited.add(v)
                queue.append((v, depth + 1))
            nxt = _read_u64(reader, cur + 8)
            cur = nxt
    print(f"[*] 含资源路径的脚本命中 = {len(found)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
