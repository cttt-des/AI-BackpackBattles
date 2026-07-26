"""
枚举 children 列表（偏移 0x6c0 与 0x798），dump 每个孩子的成员数组与成员数，
用于定位 Game 自动加载单例（autoload 顺序第 9 个 = 下标 8）。

用法：
  python tools/enum2.py --pid 18616
"""
import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent.parent))

from core.memory_reader import MemoryReader
from core.godot_probe import read_module_sections, _read_u64, _is_plausible_ptr, _is_valid_instance


def read_variant_int(reader, vaddr):
    d = reader.read(vaddr, 4)
    if not d:
        return None
    vt = int.from_bytes(d, "little")
    if vt == 2:
        q = reader.read(vaddr + 8, 8)
        return int.from_bytes(q, "little") if q else None
    if vt == 3:
        q = reader.read(vaddr + 8, 8)
        return int.from_bytes(q, "little") if q else None
    return f"t{vt}"


def dump_members(reader, node):
    si = _read_u64(reader, node + 8)
    if not _is_plausible_ptr(si):
        return None, []
    vec = si + 0x18
    mptr = _read_u64(reader, vec)
    d = reader.read(vec + 8, 4)
    msize = int.from_bytes(d, "little") if d else None
    if not _is_plausible_ptr(mptr) or not msize or msize <= 0 or msize > 2000:
        return msize, []
    mems = []
    for k in range(min(msize, 30)):
        mems.append(read_variant_int(reader, mptr + k * 24))
    return msize, mems


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

    for co in (0x6c0, 0x798):
        print(f"\n===== children @ {hex(co)} =====")
        first = _read_u64(reader, r + co)
        cur = first
        seen = set()
        for ci in range(50):
            if not _is_plausible_ptr(cur) or cur in seen:
                print(f"  [结束] cur={hex(cur)}")
                break
            seen.add(cur)
            val = _read_u64(reader, cur)
            if _is_plausible_ptr(val) and is_inst(val):
                msize, mems = dump_members(reader, val)
                print(f"  [{ci:2d}] {hex(val)}  members={msize}  {mems}")
            else:
                print(f"  [{ci:2d}] {hex(val)}  (非实例)")
            nxt = _read_u64(reader, cur + 8)
            cur = nxt
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
