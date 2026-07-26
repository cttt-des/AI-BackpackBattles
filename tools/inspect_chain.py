"""
聚焦诊断：复现 sweep 找到的唯一 (obj->s->r) 候选链路，
详细 dump r（根视口候选）的内存，手动定位 children 列表与 parent，
并枚举所有可能的 children 偏移/下标，看能否命中合法 Game 子节点。

用法：
  python tools/inspect_chain.py --pid 18616
"""
import argparse
import sys
from pathlib import Path
from typing import Dict, List

sys.path.insert(0, str(Path(__file__).parent.parent))

from core.memory_reader import MemoryReader
from core.godot_probe import (
    read_module_sections, _read_u64, _read_u32,
    _is_plausible_ptr, _is_valid_instance, _get_child,
)


def dump_hex(label, data, base_addr):
    print(f"--- {label} (base {hex(base_addr)}, {len(data)} bytes) ---")
    for i in range(0, len(data), 16):
        chunk = data[i:i + 16]
        hexs = " ".join(f"{b:02x}" for b in chunk)
        asc = "".join(chr(b) if 32 <= b < 127 else "." for b in chunk)
        print(f"{base_addr + i:016x}  {hexs:<48}  {asc}")


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

    _vt_cache: Dict[int, bool] = {}
    def is_inst(a):
        if a in _vt_cache:
            return _vt_cache[a]
        r = _is_valid_instance(reader, a, text_lo, text_hi, rdata_lo, rdata_hi)
        _vt_cache[a] = r
        return r

    # 复现 sweep 找唯一 (obj,s,r)
    instances: List[int] = []
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
    print(f"[*] 合法实例数 = {len(instances)}")

    ML = list(range(0x180, 0x290, 8))
    ROOT = list(range(0x180, 0x290, 8))
    chain = None
    for obj in instances:
        for ml in ML:
            s = _read_u64(reader, obj + ml)
            if not _is_plausible_ptr(s) or not is_inst(s) or s == obj:
                continue
            for ro in ROOT:
                r = _read_u64(reader, s + ro)
                if _is_plausible_ptr(r) and is_inst(r) and r != s:
                    chain = (obj, ml, s, ro, r)
                    break
            if chain:
                break
        if chain:
            break

    if not chain:
        print("[-] 未找到任何 obj->s->r 候选")
        return 1

    obj, ml, s, ro, r = chain
    print(f"[*] 候选链路: os={hex(obj)} ml={hex(ml)} scenetree={hex(s)} "
          f"root_off={hex(ro)} root={hex(r)}")

    # dump root 内存
    rmem = reader.read(r, 0x200)
    dump_hex("ROOT viewport candidate", rmem, r)

    # 在 root 内存里找所有指向「合法实例」的指针（候选 parent / children head）
    print("\n[*] root 内指向合法实例的 qword 偏移:")
    for i in range(0, len(rmem) - 8, 8):
        p = int.from_bytes(rmem[i:i + 8], "little")
        if _is_plausible_ptr(p) and is_inst(p):
            print(f"    off={hex(i)} -> {hex(p)}")

    # 尝试在所有偏移上当作 children 列表头，枚举 child_index 0..20
    print("\n[*] 枚举 children 偏移 x 下标，找合法子节点:")
    found_any = False
    for co in range(0x30, 0x200, 8):
        head = _read_u64(reader, r + co)
        if not _is_plausible_ptr(head):
            continue
        for ci in range(0, 21):
            child = _get_child(reader, r, ci, co)
            if _is_plausible_ptr(child) and is_inst(child):
                print(f"    child_off={hex(co)} idx={ci} -> {hex(child)}")
                found_any = True
    if not found_any:
        print("    (无)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
