"""
调试：手动 dump root(+0x108) 的 children Element 链表，以及 SceneTree 对象 s 的全部
指向合法实例的 qword，判断 children 结构是否与我们假设的 Element{value,next} 一致。

用法：
  python tools/dump_chain.py --pid 18616
"""
import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent.parent))

from core.memory_reader import MemoryReader
from core.godot_probe import read_module_sections, _read_u64, _is_plausible_ptr, _is_valid_instance


def dump_hex(label, data, base_addr):
    print(f"--- {label} (base {hex(base_addr)}, {len(data)} bytes) ---")
    for i in range(0, len(data), 16):
        chunk = data[i:i + 16]
        hexs = " ".join(f"{b:02x}" for b in chunk)
        print(f"{base_addr + i:016x}  {hexs}")


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
    print(f"[*] os={hex(obj)} s(scenetree)={hex(s)} r(root)={hex(r)}")

    # dump s 全部指向合法实例的 qword
    print(f"\n[*] SceneTree s={hex(s)} 内指向合法实例的 qword 偏移:")
    smem = reader.read(s, 0x300) or b""
    for i in range(0, len(smem) - 8, 8):
        p = int.from_bytes(smem[i:i + 8], "little")
        if _is_plausible_ptr(p) and is_inst(p):
            print(f"    s+{hex(i)} -> {hex(p)}")

    # dump root r 全部指向合法实例的 qword（前 0x300）
    print(f"\n[*] root r={hex(r)} 内指向合法实例的 qword 偏移 (前 0x300):")
    rmem = reader.read(r, 0x300) or b""
    for i in range(0, len(rmem) - 8, 8):
        p = int.from_bytes(rmem[i:i + 8], "little")
        if _is_plausible_ptr(p) and is_inst(p):
            print(f"    r+{hex(i)} -> {hex(p)}")

    # 手动跟随 r+0x108 的链表，打印每个 Element 的 {addr, value, next, next2}
    print(f"\n[*] 手动跟随 r+0x108 的 Element 链表 (最多 12 个):")
    first = _read_u64(reader, r + 0x108)
    print(f"    first = {hex(first) if first else first}")
    cur = first
    for k in range(12):
        if not _is_plausible_ptr(cur):
            print(f"    [{k}] cur={hex(cur)} (结束/非法)")
            break
        emem = reader.read(cur, 0x30)
        if not emem:
            print(f"    [{k}] cur={hex(cur)} 无法读")
            break
        value = int.from_bytes(emem[0:8], "little")
        nxt = int.from_bytes(emem[8:16], "little")
        nxt2 = int.from_bytes(emem[16:24], "little")
        print(f"    [{k}] elem={hex(cur)} value={hex(value)} next={hex(nxt)} next2={hex(nxt2)}"
              f"  value_inst={is_inst(value) if _is_plausible_ptr(value) else 'n/a'}")
        cur = nxt
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
