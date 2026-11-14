# -*- coding: utf-8 -*-
"""30 场对齐差异的独立复现脚本 —— 只依赖 native_sim_cpp/，不需要主仓库。

用法（把本目录与 native_sim_cpp/ 放在同一级）：
    python verify.py                      # 全部 30 场，只报结果
    python verify.py --case run101668_r7_o604708_r7   # 单场，打印并排事件
    python verify.py --case <id> --ctx 12 # 单场，打印分歧点前后 12 条

判据：
  1. 自洽确定性：同一 case 连跑两遍，ticks / event_count / hp 全等（应全过）
  2. 与参考（expected_py.json，已与神谕逐行一致）比：
       - winner
       - 事件数（注意：参考侧多发一条 emit_combat_end，故正常差值 = -1）
       - 首个 type 序列分歧位置
  C++ 事件行由 gd_sim_dbg_event_line() 导出，格式：
       ts=f:<hex>|type=<int>|id=<int>|tgt=<int>|parent=<int>|origin=<...>|params=<...>

退出码：0 = 与参考一致（含 -1 口径差）；1 = 有实质分歧。
"""
import argparse
import ctypes
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
# 允许 native_sim_cpp 与本目录同级或在其内部
# 兼容三种摆放：同级 native_sim_cpp/、上级 native_sim_cpp/、上级本身就是 bundle
for cand in (os.path.join(HERE, "native_sim_cpp"),
             os.path.join(HERE, "..", "native_sim_cpp"),
             os.path.join(HERE, "..", "..", "native_sim_cpp"),
             os.path.join(HERE, ".."),
             os.path.join(HERE, "..", "..")):
    if os.path.isdir(os.path.join(cand, "native_sim")):
        sys.path.insert(0, os.path.abspath(cand))
        break
else:
    print("找不到 native_sim 包（把本目录与 native_sim_cpp/ 放同级）")
    raise SystemExit(2)

from native_sim import get_simulator  # noqa: E402

CASES = {c["case_id"]: c for c in json.load(open(os.path.join(HERE, "cases.json"), encoding="utf-8"))}
EXPECTED = json.load(open(os.path.join(HERE, "expected_py.json"), encoding="utf-8"))
ACTUAL = json.load(open(os.path.join(HERE, "actual_cpp.json"), encoding="utf-8"))

sim = get_simulator()
lib = sim.lib
lib.gd_sim_set_dbg_events.argtypes = [ctypes.c_int32]
lib.gd_sim_dbg_event_count.restype = ctypes.c_int32
lib.gd_sim_dbg_event_line.restype = ctypes.c_char_p
lib.gd_sim_dbg_event_line.argtypes = [ctypes.c_int32]

OPTS = dict(below_master=True, native_activation_order=True,
            reseed_after_player_character=True, formal_ev_gate=500000, max_time=90.0)


def run(case):
    """跑一场，返回 (BattleResult, [canonical 行])。"""
    lib.gd_sim_set_dbg_events(1)
    r = sim.run_one(case["player"], case["opponent"], seed=case["seed"],
                    round_id=case["round_id"], **OPTS)
    n = lib.gd_sim_dbg_event_count()
    return r, [lib.gd_sim_dbg_event_line(i).decode("utf-8", "replace") for i in range(n)]


def types_of(lines):
    return [int(x.split("|type=")[1].split("|")[0]) for x in lines]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--case", default=None)
    ap.add_argument("--ctx", type=int, default=6, help="分歧点前后打印条数")
    a = ap.parse_args()

    ids = [a.case] if a.case else sorted(CASES)
    bad = 0
    print("%-30s %6s %6s %6s  %-7s %s" % ("case", "cpp_n", "ref_n", "delta", "win", "首个分歧"))
    for cid in ids:
        case = CASES[cid]
        ref = EXPECTED[cid]
        r, lines = run(case)

        # 判据 1：自洽确定性
        r2, lines2 = run(case)
        det = (r.ticks == r2.ticks and r.event_count == r2.event_count
               and lines == lines2)

        cpp_t = types_of(lines)
        # 参考侧已精简为列表：ev = [type, t, parent, target, origin, params]
        ref_ev = ref["ev"]
        ref_t = [int(e[0]) for e in ref_ev]
        first = None
        for i in range(min(len(cpp_t), len(ref_t))):
            if cpp_t[i] != ref_t[i]:
                first = i
                break

        delta = r.event_count - ref["event_count"]
        cpp_win = "player" if r.player_wins else "opponent"
        ref_win = ref.get("winner")
        ok = (delta == -1) and (cpp_win == ref_win) and det
        if not ok:
            bad += 1
        print("%-30s %6d %6d %+6d  %-7s %s%s"
              % (cid, r.event_count, ref["event_count"], delta,
                 "%s/%s" % (cpp_win, ref_win),
                 ("idx=%d" % first) if first is not None else "前缀一致",
                 "" if ok else "   <<<"))

        if a.case:
            print()
            print("自洽确定性(跑两遍逐位相等):", det)
            print("C++ 行数 %d / 参考 %d" % (len(lines), len(ref_ev)))
            if first is not None:
                lo = max(0, first - a.ctx)
                hi = min(max(len(lines), len(ref_ev)), first + a.ctx + 1)
                print()
                for i in range(lo, hi):
                    cl = lines[i] if i < len(lines) else "-"
                    rl = "-"
                    if i < len(ref_ev):
                        e = ref_ev[i]
                        org = e[4]
                        ok_ = "/".join(str(x) for x in org if x) if isinstance(org, list) else org
                        rl = "type=%s p=%s org=%s" % (e[0], e[2], ok_)
                    mark = " <<<" if i == first else ""
                    print("  %3d C++: %s" % (i, cl[:130]))
                    print("      参考: %s%s" % (rl, mark))
    print()
    print("实质分歧 %d / %d 场" % (bad, len(ids)))
    return 0 if bad == 0 else 1


if __name__ == "__main__":
    raise SystemExit(main())
