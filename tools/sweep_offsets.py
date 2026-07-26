"""
偏移扫描诊断：在运行中的游戏进程上，用实测方式找出正确的
(main_loop, root, parent, children, child_index) 偏移组合。

原理：
  .data 全局里有一批「指向合法实例（vtable 在 .rdata）」的对象（含 OS 实例），
  但不知道哪个是 OS。我们用正向链路校验 + 偏移网格扫描：
    候选 obj -> obj+ml_off (SceneTree, 合法实例)
             -> +root_off (根视口, 合法实例且 parent==null)
             -> children[child_index] (Game, 合法实例)
  用 is_valid_instance 记忆化避免重复 vtable 校验，大幅加速。

诊断输出分级计数（n_ml / n_root / n_parent / n_child），定位链路在哪一级断裂。

用法：
  python tools/sweep_offsets.py --pid 18616
"""
import argparse
import sys
import time
from pathlib import Path
from typing import Dict, List, Optional, Tuple

sys.path.insert(0, str(Path(__file__).parent.parent))

from core.memory_reader import MemoryReader
from core.godot_probe import (
    read_module_sections, _read_u64, _read_u32, _in_range,
    _is_plausible_ptr, _is_valid_instance, _get_child,
)

# 扫描网格（八字节对齐）
ML_GRID = list(range(0x180, 0x290, 8))
ROOT_GRID = list(range(0x180, 0x290, 8))
PARENT_GRID = list(range(0x0, 0x48, 4))
CHILD_GRID = list(range(0x30, 0x90, 8))
CHILD_INDICES = [8, 7, 9, 6, 10, 5, 4, 11, 3, 12, 2, 13, 1, 14, 0, 15, 16, 17]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--pid", type=int, required=True)
    args = ap.parse_args()

    reader = MemoryReader(args.pid)
    base = reader.module_base
    print(f"[*] 模块基址 = {hex(base)}")
    secs = read_module_sections(reader)
    if not secs:
        print("[-] 无法读取 PE 段表"); return 1
    text = next((s for s in secs if s[0] == ".text"))
    rdata = next((s for s in secs if s[0] == ".rdata"))
    data = next((s for s in secs if s[0] == ".data"))
    text_lo, text_hi = base + text[1], base + text[1] + text[2]
    rdata_lo, rdata_hi = base + rdata[1], base + rdata[1] + rdata[2]

    _vt_cache: Dict[int, bool] = {}
    def is_inst(addr):
        if addr in _vt_cache:
            return _vt_cache[addr]
        r = _is_valid_instance(reader, addr, text_lo, text_hi, rdata_lo, rdata_hi)
        _vt_cache[addr] = r
        return r

    t0 = time.time()
    instances: List[int] = []
    addr = base + data[1]
    end = addr + data[2]
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
    print(f"[*] 合法实例数 = {len(instances)}  ({time.time()-t0:.1f}s)")

    n_ml = n_root = n_parent = 0
    hits: List[dict] = []
    seen_os_pairs = set()
    for obj in instances:
        for ml in ML_GRID:
            s = _read_u64(reader, obj + ml)
            if not _is_plausible_ptr(s) or not is_inst(s) or s == obj:
                continue
            n_ml += 1
            for ro in ROOT_GRID:
                r = _read_u64(reader, s + ro)
                if not _is_plausible_ptr(r) or not is_inst(r) or r == s:
                    continue
                n_root += 1
                for po in PARENT_GRID:
                    if _read_u64(reader, r + po) != 0:
                        continue
                    n_parent += 1
                    for ci in CHILD_INDICES:
                        for co in CHILD_GRID:
                            child = _get_child(reader, r, ci, co)
                            if (_is_plausible_ptr(child) and is_inst(child)
                                    and child != r and child != s and child != obj):
                                hits.append({
                                    "os": hex(obj), "ml": hex(ml), "root": hex(ro),
                                    "parent": hex(po), "child_off": hex(co),
                                    "child_idx": ci, "game": hex(child),
                                })
                                break
                        if hits and hits[-1]["os"] == hex(obj):
                            break
                    if hits and hits[-1]["os"] == hex(obj):
                        break
            if hits and hits[-1]["os"] == hex(obj):
                break

    print(f"[*] n_ml={n_ml}  n_root={n_root}  n_parent={n_parent}  "
          f"n_child={len(hits)}  ({time.time()-t0:.1f}s)")
    for h in hits[:30]:
        print("    ", h)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
