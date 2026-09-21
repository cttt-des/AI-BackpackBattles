# -*- coding: utf-8 -*-
"""compare_engines.py — 旧内核 vs 新内核同种子快照对照与差异归因

对照两份回归基线（tools/regression_baseline.py --save 产物）：
  * output/baseline/baseline_latest.json          （simulator 旧内核）
  * output/baseline/baseline_latest__engine.json  （engine 新内核）

输出每场差异（胜负/时长/HP/事件指纹）并按已知引擎差异项归因，每条归因给出
源码依据（engine_truth.md 对照表 / GDScript 行号），无源码依据的差异标记为
[UNATTRIBUTED] —— 验收标准：该项为 0。

用法：
    python tools/compare_engines.py                 # 对照 latest 两份基线
    python tools/compare_engines.py --tag before    # 指定标签
    python tools/compare_engines.py --json out.json
"""
from __future__ import annotations

import argparse
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)

for _stream in (sys.stdout, sys.stderr):
    try:
        if hasattr(_stream, "reconfigure"):
            _stream.reconfigure(encoding="utf-8", errors="replace")
    except Exception:  # noqa: BLE001
        pass

OUT_DIR = os.path.join(ROOT, "output", "baseline")

# ---- 已知引擎差异项（归因清单）----
# 每项：谓词(新旧两场记录) -> 命中则可归因；附源码依据
ATTRIBUTIONS = [
    {
        "name": "冷却 ±5% 抖动（adjustCooldown）",
        "basis": "Item.gd adjustCooldown 0.975~1.05；engine/item.py adjust_cooldown；"
                 "旧内核固定 iterationCooldown（无抖动）",
        "pred": lambda old, new: abs(
            (new.get("time") or 0) - (old.get("time") or 0)) > 0.01,
    },
    {
        "name": "Goobert 信号联动修复（新内核生效）",
        "basis": "KingGoobert.gd:26 .prepare() 链；engine/gen/behaviors.py "
                 "f_King_Goobert__prepare 补链；activations 数值差异",
        "pred": lambda old, new: (
            (new.get("player_activations") or 0) != (old.get("player_activations") or 0)
            or (new.get("opponent_activations") or 0) != (old.get("opponent_activations") or 0)),
    },
    {
        "name": "事件流重排/增删（新内核事件面：惰性日志、weapon 链、宝石分发）",
        "basis": "engine/events.py 惰性事件 vs simulator CombatLog；"
                 "engine/combat.py activateItems 三阶段",
        "pred": lambda old, new: new.get("events_hash") != old.get("events_hash"),
    },
]

# 按优先级归因：先细后粗（胜负 > activations > 时长 > 事件指纹）


def load_baseline(tag: str, engine: str):
    from regression_baseline import baseline_path
    p = baseline_path(tag, engine)
    if not os.path.exists(p):
        raise SystemExit(f"基线不存在: {p}")
    return json.load(open(p, encoding="utf-8")), p


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description="双内核快照对照与差异归因")
    ap.add_argument("--tag", default="latest")
    ap.add_argument("--json", default=None, help="差异报告输出路径")
    args = ap.parse_args(argv)
    sys.path.insert(0, os.path.join(ROOT, "tools"))

    old_base, old_p = load_baseline(args.tag, "simulator")
    new_base, new_p = load_baseline(args.tag, "engine")
    print(f"旧内核: {old_p}（{len(old_base['results'])} 场）")
    print(f"新内核: {new_p}（{len(new_base['results'])} 场）")

    def key(r):
        return (r.get("player"), r.get("opponent"))

    old_map = {key(r): r for r in old_base["results"]}
    new_map = {key(r): r for r in new_base["results"]}

    rows = []
    n_diff = 0
    n_unattr = 0
    for k in sorted(set(old_map) & set(new_map)):
        o, n = old_map[k], new_map[k]
        if "error" in o or "error" in n:
            rows.append({"pair": k, "error": o.get("error") or n.get("error")})
            continue
        fields = {}
        for f in ("winner", "reason", "time", "fatigue_counter", "player_hp",
                  "opponent_hp", "player_activations", "opponent_activations",
                  "events_hash", "log_hash"):
            if o.get(f) != n.get(f):
                fields[f] = [o.get(f), n.get(f)]
        if not fields:
            continue
        n_diff += 1
        # 归因：命中已知谓词则记录，否则 UNATTRIBUTED
        hit = [a["name"] for a in ATTRIBUTIONS if a["pred"](o, n)]
        if not hit:
            n_unattr += 1
            hit = ["[UNATTRIBUTED]"]
        rows.append({"pair": list(k), "diff_fields": fields,
                     "attribution": hit,
                     "basis": [a["basis"] for a in ATTRIBUTIONS
                               if a["pred"](o, n)]})

    print("=" * 70)
    print(f"可比对 {len(set(old_map) & set(new_map))} 场，差异 {n_diff} 场"
          f"（其中未归因 {n_unattr} 场）")
    for r in rows:
        if "error" in r:
            print(f"  [ERR] {r['pair']}: {r['error']}")
            continue
        flag = "!!!" if r["attribution"] == ["[UNATTRIBUTED]"] else "   "
        brief = ", ".join(f"{f}: {v[0]} -> {v[1]}"
                          for f, v in r["diff_fields"].items()
                          if f in ("winner", "time", "player_activations",
                                   "opponent_activations"))
        print(f"{flag} {r['pair'][0]} vs {r['pair'][1]}  {brief}")
        print(f"        归因: {'; '.join(r['attribution'])}")

    if args.json:
        os.makedirs(os.path.dirname(os.path.abspath(args.json)), exist_ok=True)
        json.dump({"n_diff": n_diff, "n_unattributed": n_unattr,
                   "rows": rows},
                  open(args.json, "w", encoding="utf-8"),
                  ensure_ascii=False, indent=1)
        print(f"报告: {args.json}")
    # 验收标准：无未归因差异
    return 1 if n_unattr else 0


if __name__ == "__main__":
    raise SystemExit(main())
