"""
修正版：在 root.children(0x6c0) 子节点中定位 GDScriptInstance。
C++ 对象 vtable 在 +0，故 owner 在 +8（非 +0）。
  - 扫描节点内存找 Q，使 Q 为合法实例且 read(Q+8)==node（owner 回指）→ Q 即 script_instance
    Q 在节点内的偏移 = object_script_instance_off
  - 从 Q 扫描找 Vector<Variant> 头（_ptr -> 一串 Variant 头），其偏移 = gdscript_members_off
  - dump members，寻找 Game（含 gold/hp/round 的成员模式）

用法：
  python tools/scan_si2.py --pid 18616
"""
import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent.parent))

from core.memory_reader import MemoryReader
from core.godot_probe import read_module_sections, _read_u64, _is_plausible_ptr, _is_valid_instance


def find_si_and_off(reader, is_inst, node):
    nmem = reader.read(node, 0x400) or b""
    for i in range(0, len(nmem) - 8, 8):
        q = int.from_bytes(nmem[i:i + 8], "little")
        if _is_plausible_ptr(q) and is_inst(q) and _read_u64(reader, q + 8) == node:
            return q, i
    return None, None


def find_members_vec(reader, is_inst, si):
    simem = reader.read(si, 0x120) or b""
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
            sd = reader.read(vp + 8, 4)
            sz = int.from_bytes(sd, "little") if sd else None
            return vp, k, sz
    return None, None, None


def dump_members(reader, mptr, msize):
    out = []
    for k in range(min(msize, 50)):
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
    for ci in range(320):
        if not _is_plausible_ptr(cur) or cur in seen:
            break
        seen.add(cur)
        val = _read_u64(reader, cur)
        if _is_plausible_ptr(val) and is_inst(val):
            si, off = find_si_and_off(reader, is_inst, val)
            if si is not None:
                mptr, mk, msize = find_members_vec(reader, is_inst, si)
                if mptr and msize and 0 < msize < 2000:
                    mems = dump_members(reader, mptr, msize)
                    print(f"  [{ci:2d}] {hex(val)} si_off={hex(off)} members_off={hex(mk)} size={msize}")
                    print(f"        {mems}")
        nxt = _read_u64(reader, cur + 8)
        cur = nxt
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
