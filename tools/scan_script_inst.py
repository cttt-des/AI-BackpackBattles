"""
对所有 root.children(0x6c0) 子节点，寻找带 GDScriptInstance 的节点
（节点内存里有 p 指向合法实例且 p+0 == node，即 owner 回指），
对其 dump GDScriptInstance::members 向量（自动定位）。输出带 members 的节点。

用法：
  python tools/scan_script_inst.py --pid 18616
"""
import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent.parent))

from core.memory_reader import MemoryReader
from core.godot_probe import read_module_sections, _read_u64, _is_plausible_ptr, _is_valid_instance


def find_script_instance(reader, is_inst, node):
    nmem = reader.read(node, 0x300) or b""
    for i in range(0, len(nmem) - 8, 8):
        p = int.from_bytes(nmem[i:i + 8], "little")
        if _is_plausible_ptr(p) and is_inst(p) and _read_u64(reader, p + 0) == node:
            return p, i
    return None, None


def find_members_vec(reader, is_inst, si):
    simem = reader.read(si, 0x100) or b""
    for k in range(0, len(simem) - 8, 8):
        vp = int.from_bytes(simem[k:k + 8], "little")
        if not _is_plausible_ptr(vp):
            continue
        ok = 0
        for m in range(8):
            vh = reader.read(vp + m * 24, 4)
            if not vh:
                break
            t = int.from_bytes(vh, "little")
            if 0 <= t <= 24:
                ok += 1
            else:
                break
        if ok >= 5:
            sz = None
            sd = reader.read(vp + 8, 4)
            if sd:
                sz = int.from_bytes(sd, "little")
            return vp, k, sz
    return None, None, None


def dump_members(reader, mptr, msize):
    out = []
    for k in range(min(msize, 40)):
        vaddr = mptr + k * 24
        vh = reader.read(vaddr, 4)
        if not vh:
            out.append(None); continue
        t = int.from_bytes(vh, "little")
        if t == 2:
            q = reader.read(vaddr + 8, 8)
            out.append(int.from_bytes(q, "little") if q else None)
        elif t == 3:
            q = reader.read(vaddr + 8, 8)
            out.append(int.from_bytes(q, "little") if q else None)
        else:
            out.append(f"t{t}")
    return out


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

    first = _read_u64(reader, r + 0x6c0)
    cur = first
    seen = set()
    for ci in range(60):
        if not _is_plausible_ptr(cur) or cur in seen:
            break
        seen.add(cur)
        val = _read_u64(reader, cur)
        if _is_plausible_ptr(val) and is_inst(val):
            si, off = find_script_instance(reader, is_inst, val)
            if si is not None:
                mptr, mk, msize = find_members_vec(reader, is_inst, si)
                if mptr and msize and 0 < msize < 2000:
                    mems = dump_members(reader, mptr, msize)
                    print(f"  [{ci:2d}] {hex(val)} si@{hex(off)}={hex(si)} "
                          f"members@{hex(mk)} size={msize}")
                    print(f"        members={mems}")
        nxt = _read_u64(reader, cur + 8)
        cur = nxt
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
