"""
宽搜：对 root.children(0x6c0) 的每个子节点，扫描其内存里所有「合法实例」指针 Q，
在 Q 内找 Vector<Variant> 成员向量（_ptr -> >=3 个 Variant 头），凡是 size>=5 的
都 dump 出来——用于在任意位置定位 Game（成员数量大）。

用法：
  python tools/scan_si3.py --pid 18616
"""
import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent.parent))

from core.memory_reader import MemoryReader
from core.godot_probe import read_module_sections, _read_u64, _is_plausible_ptr, _is_valid_instance


def find_members_vec(reader, is_inst, si):
    simem = reader.read(si, 0x200) or b""
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
        if ok >= 3:
            sd = reader.read(vp + 8, 4)
            sz = int.from_bytes(sd, "little") if sd else None
            return vp, k, sz
    return None, None, None


def dump_members(reader, mptr, msize):
    out = []
    for k in range(min(msize, 60)):
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
    for ci in range(258):
        if not _is_plausible_ptr(cur) or cur in seen:
            break
        seen.add(cur)
        val = _read_u64(reader, cur)
        if _is_plausible_ptr(val) and is_inst(val):
            nmem = reader.read(val, 0x400) or b""
            for i in range(0, len(nmem) - 8, 8):
                q = int.from_bytes(nmem[i:i + 8], "little")
                if _is_plausible_ptr(q) and is_inst(q):
                    mptr, mk, msize = find_members_vec(reader, is_inst, q)
                    if mptr and msize and 5 <= msize < 2000:
                        mems = dump_members(reader, mptr, msize)
                        print(f"  child[{ci}] {hex(val)} q_off={hex(i)} "
                              f"members_off={hex(mk)} size={msize}")
                        print(f"        {mems}")
        nxt = _read_u64(reader, cur + 8)
        cur = nxt
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
