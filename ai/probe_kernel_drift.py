# -*- coding: utf-8 -*-
"""probe_kernel_drift.py — gd_core_py 同 (阵容,seed) 进程内漂移探针

直接运行：  python ai/probe_kernel_drift.py [组目录|Player.json路径] [seed] [次数] [--warm N]

默认（无参数）：CombatLog_20261001_221121_R19_Loss、seed=101、连跑 6 次。

两种模式：
  * 默认     ：同进程连跑 n 局，**每局前不调用 reset_kernel_state()** ——
               复现『(输入,seed)→胜负』随进程历史漂移的原始缺陷；
  * --reset  ：每局前调用 reset_kernel_state()（ai/kernel_reset.py 的临时绕过），
               作为对照。
  * --warm N ：连跑目标局之前，先用另一组实录热身 N 局（同样受模式控制）。

输出每局 (winner, end_time) 行 + 末行 JSON 摘要。退出码恒 0（探针不断言，
判定交给 test_kernel_reset.py / 报告人）。
"""
from __future__ import annotations

import json
import os
import sys

_HERE = os.path.dirname(os.path.abspath(__file__))
_ROOT = os.path.dirname(_HERE)
if _ROOT not in sys.path:
    sys.path.insert(0, _ROOT)

from simulator.gd_core_engine import GDCoreEngine          # noqa: E402
from simulator.lineup import load_lineup                   # noqa: E402

_LOG_DIR = os.path.join(_ROOT, "dist", "output", "combat_logs")
DEFAULT_GROUP = os.path.join(_LOG_DIR, "CombatLog_20261001_221121_R19_Loss")
WARM_GROUP = os.path.join(_LOG_DIR, "CombatLog_20261001_221048_R19_Loss")


def _sides(group_dir: str):
    base = os.path.join(group_dir, os.path.basename(group_dir))
    return load_lineup(base + ".Player.json"), load_lineup(base + ".Opponent.json")


def main(argv):
    use_reset = "--reset" in argv
    argv = [a for a in argv if a != "--reset"]
    warm = 0
    if "--warm" in argv:
        i = argv.index("--warm")
        warm = int(argv[i + 1])
        del argv[i:i + 2]

    group = argv[0] if argv else DEFAULT_GROUP
    if os.path.isfile(group):
        base = group.replace(".Player.json", "")
        group = os.path.dirname(base) if os.path.dirname(base) else group
    seed = int(argv[1]) if len(argv) > 1 else 101
    n = int(argv[2]) if len(argv) > 2 else 6

    from ai.kernel_reset import reset_kernel_state
    p, o = _sides(group)
    rows = []

    if warm:
        wp, wo = _sides(WARM_GROUP)
        for i in range(warm):
            if use_reset:
                reset_kernel_state()
            eng = GDCoreEngine(wp, wo, {}, {}, seed=901 + i)
            eng.run()
            rows.append({"kind": "warm", "i": i, "winner": int(eng.player_wins()),
                         "t": eng.summary()["time"]})

    for i in range(n):
        if use_reset:
            reset_kernel_state()
        eng = GDCoreEngine(p, o, {}, {}, seed=seed)
        eng.run()
        rows.append({"kind": "target", "i": i, "seed": seed,
                     "winner": int(eng.player_wins()), "t": eng.summary()["time"]})

    for r in rows:
        print("%-6s i=%d seed=%s winner=%d t=%.2f" % (
            r["kind"], r["i"], r.get("seed", "-"), r["winner"], r["t"]))
    print(json.dumps({"mode": "reset" if use_reset else "raw",
                      "warm": warm, "group": os.path.basename(group),
                      "target_winners": [r["winner"] for r in rows
                                         if r["kind"] == "target"]}))
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
