"""
扫描 root 视口内存，找出真正的 children 列表偏移：
Godot List<T> 布局 = { Element* first(+0); Element* last(+8); int count(+16) }。
真实 children 列表的 count 应较大（autoload + 场景子节点），且遍历后多为合法实例。

用法：
  python tools/scan_children_off.py --pid 18616
"""
import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent.parent))

from core.memory_reader import MemoryReader
from core.godot_probe import read_module_sections, _read_u64, _is_plausible_ptr, _is_valid_instance


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

    print(f"[*] 扫描 children 偏移 (count@+16):")
    best = []
    for co in range(0x30, 0x300, 8):
        first = _read_u64(reader, r + co)
        if not _is_plausible_ptr(first):
            continue
        cnt = reader.read_int32(r + co + 16)
        if cnt is None or cnt <= 0 or cnt > 1000:
            continue
        # 遍历 count 个元素
        valid = 0
        cur = first
        for _ in range(cnt):
            if not _is_plausible_ptr(cur):
                break
            v = _read_u64(reader, cur)
            if _is_plausible_ptr(v) and is_inst(v):
                valid += 1
            nxt = _read_u64(reader, cur + 8)
            cur = nxt
        if valid >= 3:
            best.append((co, cnt, valid))
            print(f"    off={hex(co)} count={cnt} valid={valid}")
    print(f"[*] 候选 children 偏移数 = {len(best)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
