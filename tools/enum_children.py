"""
枚举 root 视口的 children 列表（偏移 0x108），对每个孩子 dump GDScript 成员，
用于定位 Game 自动加载单例并确定其成员下标。

用法：
  python tools/enum_children.py --pid 18616
"""
import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent.parent))

from core.memory_reader import MemoryReader
from core.godot_probe import read_module_sections, _read_u64, _is_plausible_ptr, _is_valid_instance


def decode_stringname(reader, node, name_off):
    """尽力从 node+name_off 的 StringName 解出名字（Godot 3.6 最佳努力）。"""
    try:
        data_ptr = _read_u64(reader, node + name_off)
        if not _is_plausible_ptr(data_ptr):
            return None
        # StringName::_Data 后段是 String name；String::_Data 含 utf8 指针。
        # 这里采用通用启发：在 _Data 后 0x20~0x40 处找 utf8 指针。
        for skip in (0x20, 0x24, 0x28, 0x30, 0x38):
            sp = _read_u64(reader, data_ptr + skip)
            if _is_plausible_ptr(sp):
                # String::_Data: refcount(8)+..., utf8 指针常在前 0x18 内
                for s2 in (0x8, 0x10, 0x18, 0x0):
                    up = _read_u64(reader, sp + s2)
                    if _is_plausible_ptr(up):
                        raw = reader.read(up, 64)
                        if raw:
                            end = raw.find(b"\x00")
                            s = raw[:end if end >= 0 else 32]
                            if 1 <= len(s) <= 40 and all(32 <= c < 127 or c >= 0xC0 for c in s):
                                return s.decode("utf-8", "replace")
    except Exception:
        pass
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--pid", type=int, required=True)
    ap.add_argument("--children-off", type=int, default=0x108)
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

    # 复现链路
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
        print("[-] 链路未找到")
        return 1
    obj, s, r = chain
    print(f"[*] os={hex(obj)} scenetree={hex(s)} root={hex(r)}")

    co = args.children_off
    print(f"[*] 枚举 children @ {hex(co)}:")
    print(f"    {'idx':>3}  {'child_addr':<18}  {'name':<16}  members[:12]")
    for ci in range(0, 40):
        # List::first @ r+co
        first = _read_u64(reader, r + co)
        cur = first
        val = None
        i = 0
        while cur and i <= ci:
            v = _read_u64(reader, cur)
            if i == ci:
                val = v
                break
            nxt = _read_u64(reader, cur + 8)
            cur = nxt
            i += 1
        if val is None:
            break
        if not _is_plausible_ptr(val) or not is_inst(val):
            print(f"    {ci:>3}  {hex(val)}  (非实例)")
            continue
        name = decode_stringname(reader, val, 0x10)
        # 读成员
        si = _read_u64(reader, val + 8)
        members = []
        if _is_plausible_ptr(si):
            vec = si + 0x18
            mptr = _read_u64(reader, vec)
            msize = reader.read_int32(vec + 8) if hasattr(reader, "read_int32") else None
            if msize is None:
                d = reader.read(vec + 8, 4)
                msize = int.from_bytes(d, "little") if d else None
            if _is_plausible_ptr(mptr) and msize and 0 < msize < 500:
                for k in range(min(msize, 12)):
                    vaddr = mptr + k * 24
                    vt = reader.read_int32(vaddr) if hasattr(reader, "read_int32") else None
                    if vt is None:
                        dd = reader.read(vaddr, 4)
                        vt = int.from_bytes(dd, "little") if dd else None
                    if vt == 2:
                        dd = reader.read(vaddr + 8, 8)
                        members.append(int.from_bytes(dd, "little") if dd else None)
                    elif vt == 3:
                        dd = reader.read(vaddr + 8, 8)
                        members.append(int.from_bytes(dd, "little") if dd else None)
                    else:
                        members.append(f"t{vt}")
        print(f"    {ci:>3}  {hex(val)}  {str(name):<16}  {members}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
