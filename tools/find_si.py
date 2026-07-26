"""
定位某节点的 ScriptInstance 与 GDScriptInstance::members 向量：
  扫描节点内存找 p，使 p 为合法实例且 p+0 == node（owner 回指）。
  再 dump p 的内存，找 Vector<Variant> 头（_ptr -> 一连串 Variant 头）。

用法：
  python tools/find_si.py --pid 18616 --node 0x1b250d83380
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
    ap.add_argument("--node", type=lambda x: int(x, 16), required=True)
    args = ap.parse_args()
    node = args.node

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

    print(f"[*] node={hex(node)}")
    # 扫描 node 内存找 script_instance
    nmem = reader.read(node, 0x200) or b""
    print("[*] node 内指向合法实例且 owner 回指的 qword:")
    for i in range(0, len(nmem) - 8, 8):
        p = int.from_bytes(nmem[i:i + 8], "little")
        if _is_plausible_ptr(p) and is_inst(p) and _read_u64(reader, p + 0) == node:
            print(f"    node+{hex(i)} -> si={hex(p)}")
            # dump si 内存
            simem = reader.read(p, 0x80) or b""
            print(f"    --- si={hex(p)} 内存 ---")
            for j in range(0, len(simem), 16):
                chunk = simem[j:j + 16]
                print(f"      {p + j:016x}  " + " ".join(f"{b:02x}" for b in chunk))
            # 在 si 内找 Vector<Variant> 头：某 qword 指向的区域内有一串 Variant 头
            print(f"    --- si 内候选 members 向量 (_ptr -> Variant 序列) ---")
            for k in range(0, len(simem) - 8, 8):
                vp = int.from_bytes(simem[k:k + 8], "little")
                if _is_plausible_ptr(vp):
                    # 读 8 个连续 Variant 头检查类型合法性
                    headers_ok = 0
                    for m in range(8):
                        vh = reader.read(vp + m * 24, 4)
                        if not vh:
                            break
                        t = int.from_bytes(vh, "little")
                        if 0 <= t <= 24:  # Variant::Type 范围
                            headers_ok += 1
                        else:
                            break
                    if headers_ok >= 5:
                        d = reader.read(vp - 8, 4)  # _size 在 _ptr 前? 实际 size 在 +8
                        # Vector: _ptr@k, _size@k+8
                        sz = reader.read_int32(vp + 8) if hasattr(reader, "read_int32") else None
                        if sz is None:
                            sd = reader.read(vp + 8, 4)
                            sz = int.from_bytes(sd, "little") if sd else None
                        print(f"      si+{hex(k)} -> vec_ptr={hex(vp)} type_seq={headers_ok} size@+8={sz}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
