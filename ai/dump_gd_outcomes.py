# -*- coding: utf-8 -*-
"""dump_gd_outcomes.py — gd_core 引擎逐 (真值组, seed) 结果快照

直接运行：  python ai/dump_gd_outcomes.py [--out PATH] [--no-reset] [--seeds A,B,..]

用途：内核复现性修复的**行为变化**对照（修复不保持参战路径行为——同
(阵容, seed) 结局修复前后有翻转，详见 ai/kernel_fix_behavior_change.md）。
对 dist/output/combat_logs 下全部真值组
按 compare_truth.py 同款种子（42..46）逐局跑 GDCoreEngine，输出 JSON：
    [{"group": 组名, "seed": 42, "winner": 0/1, "time": 12.3, "error": null}, ...]

模式：
  * 默认     ：每局前 reset_kernel_state()（与 eval.py 现行口径一致）；
  * --no-reset：不调用重置 —— 修复后与默认模式**逐条一致**（这验证的是
               修复后内核的进程内确定性『reset≡不重置』，不是行为保持）。
"""
from __future__ import annotations

import glob
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
SEEDS = list(range(42, 47))          # 与 tools/compare_truth.py 同款


def main(argv):
    out = "ai/gd_outcomes.json"
    no_reset = "--no-reset" in argv
    if "--out" in argv:
        out = argv[argv.index("--out") + 1]
    if "--seeds" in argv:
        seeds = [int(s) for s in argv[argv.index("--seeds") + 1].split(",")]
    else:
        seeds = SEEDS

    if not no_reset:
        from ai.kernel_reset import reset_kernel_state
    else:
        def reset_kernel_state():
            return None

    groups = []
    for grp in sorted(glob.glob(os.path.join(_LOG_DIR, "*"))):
        base = os.path.join(grp, os.path.basename(grp))
        if os.path.isfile(base + ".Player.json"):
            groups.append((os.path.basename(grp), base))

    rows = []
    for name, base in groups:
        try:
            la = load_lineup(base + ".Player.json")
            lb = load_lineup(base + ".Opponent.json")
        except Exception as e:  # noqa: BLE001
            rows.append({"group": name, "seed": None, "winner": None,
                         "time": None, "error": "load: %r" % (e,)})
            continue
        for seed in seeds:
            reset_kernel_state()
            try:
                eng = GDCoreEngine(la, lb, {}, {}, seed=seed)
                eng.run()
                rows.append({"group": name, "seed": seed,
                             "winner": int(eng.player_wins()),
                             "time": round(eng.summary()["time"], 3),
                             "error": None})
            except Exception as e:  # noqa: BLE001
                rows.append({"group": name, "seed": seed, "winner": None,
                             "time": None, "error": repr(e)})
        print("%s done (%d/%d)" % (name, len(rows), len(groups) * len(seeds)),
              file=sys.stderr)

    with open(out, "w", encoding="utf-8") as f:
        json.dump(rows, f, ensure_ascii=False, indent=1)
    ok = sum(1 for r in rows if r["error"] is None)
    wins = sum(r["winner"] or 0 for r in rows if r["error"] is None)
    print("rows=%d ok=%d wins=%d -> %s" % (len(rows), ok, wins, out))
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
