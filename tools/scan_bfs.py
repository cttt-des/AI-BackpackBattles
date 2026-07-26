"""
BFS（深度 2）从 root 出发，沿 children(0x6c0) 遍历所有节点；
对每个节点的 script_instance（owner 回指 node），读取其 GDScript 脚本对象，
在脚本内存里搜 "Game" 字符串（脚本资源路径 res://Core/Game.gd）以定位 Game 自动加载单例。

用法：
  python tools/scan_bfs.py --pid 18616
"""
import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent.parent))

from core.memory_reader import MemoryReader
from core.godot_probe import read_module_sections, _read_u64, _is_plausible_ptr, _is_valid_instance


def find_script_path(reader, is_inst, q):
    # q 是 script_instance；script 在 q+0x10 (Ref<GDScript> 的 ptr)
    script_ptr = _read_u64(reader, q + 0x10)
    if not _is_plausible_ptr(script_ptr):
        # 试 q+8
        script_ptr = _read_u64(reader, q + 8)
        if not _is_plausible_ptr(script_ptr):
            return None
    smem = reader.read(script_ptr, 0x300) or b""
    # 搜可读串
    for m in __import__("re").finditer(rb"[\x20-\x7e]{3,}", smem):
        s = m.group()
        if b"Game" in s or b"game" in s:
            try:
                return s.decode("ascii", "replace")
            except Exception:
                return str(s)
    # 也搜 UTF-32（Godot String 内部是 UTF-32）
    for i in range(0, len(smem) - 8, 4):
        u = int.from_bytes(smem[i:i + 4], "little")
        if 32 <= u < 127:
            # 连续 ASCII UTF-32
            chars = []
            j = i
            while j + 4 <= len(smem):
                c = int.from_bytes(smem[j:j + 4], "little")
                if 32 <= c < 127:
                    chars.append(chr(c)); j += 4
                else:
                    break
            if 3 <= len(chars) <= 60 and "Game" in "".join(chars):
                return "".join(chars)
    return None


def find_si(reader, is_inst, node):
    nmem = reader.read(node, 0x400) or b""
    for i in range(0, len(nmem) - 8, 8):
        q = int.from_bytes(nmem[i:i + 8], "little")
        if _is_plausible_ptr(q) and is_inst(q) and _read_u64(reader, q + 8) == node:
            return q, i
    return None, None


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

    # BFS 深度 2
    visited = set()
    queue = [(r, 0)]
    visited.add(r)
    game_hits = []
    while queue:
        node, depth = queue.pop(0)
        if depth >= 2:
            continue
        if not is_inst(node):
            continue
        si, off = find_si(reader, is_inst, node)
        if si is not None:
            path = find_script_path(reader, is_inst, si)
            print(f"  [SI] node={hex(node)} si_off={hex(off)} path={path!r}")
            if path and "Game" in path:
                game_hits.append((node, off, path))
        # 入队子节点
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

    print(f"[*] BFS 访问节点数 = {len(visited)}")
    print(f"[*] 含 'Game' 的脚本路径命中 = {len(game_hits)}")
    for h in game_hits:
        print("    ", h)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
