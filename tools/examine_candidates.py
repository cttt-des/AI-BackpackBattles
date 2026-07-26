"""
检查若干候选节点（SceneTree 直接引用的实例）是否为「根视口」：
  - 存在 parent==null 的偏移
  - 存在一个 children 列表（链表遍历出大量合法子节点）
对每个候选 dump parent 偏移与 children 候选偏移。

用法：
  python tools/examine_candidates.py --pid 18616
"""
import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent.parent))

from core.memory_reader import MemoryReader
from core.godot_probe import read_module_sections, _read_u64, _is_plausible_ptr, _is_valid_instance


def examine(reader, is_inst, label, node, lo, hi):
    print(f"\n=== {label} = {hex(node)} ===")
    # parent 候选
    print("  parent==null 偏移: ", end="")
    ps = []
    for po in range(0x0, 0x40, 4):
        if _read_u64(reader, node + po) == 0:
            ps.append(hex(po))
    print(", ".join(ps) if ps else "(无)")
    # children 候选：扫描 qword 指向 Element，遍历链表统计合法子节点
    print("  children 候选 (>=3 合法子节点):")
    found = False
    for co in range(0x30, 0x800, 8):
        first = _read_u64(reader, node + co)
        if not _is_plausible_ptr(first):
            continue
        valid = 0
        cur = first
        seen = set()
        for _ in range(300):
            if not _is_plausible_ptr(cur) or cur in seen:
                break
            seen.add(cur)
            v = _read_u64(reader, cur)
            if _is_plausible_ptr(v) and is_inst(v):
                valid += 1
            nxt = _read_u64(reader, cur + 8)
            cur = nxt
        if valid >= 3:
            print(f"    off={hex(co)} valid={valid}")
            found = True
    if not found:
        print("    (无)")


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
    print(f"[*] os={hex(obj)} s={hex(s)} r={hex(r)}")

    # SceneTree 直接引用的实例
    srefs = []
    smem = reader.read(s, 0x400) or b""
    for i in range(0, len(smem) - 8, 8):
        p = int.from_bytes(smem[i:i + 8], "little")
        if _is_plausible_ptr(p) and is_inst(p):
            srefs.append(p)
    print(f"[*] SceneTree 引用的实例: {[hex(x) for x in srefs]}")
    for k, n in enumerate(srefs):
        examine(reader, is_inst, f"SceneTree-ref[{k}]", n, 0x30, 0x800)
    examine(reader, is_inst, "r(root候选)", r, 0x30, 0x800)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
