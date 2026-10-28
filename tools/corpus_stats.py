# -*- coding: utf-8 -*-
"""corpus_stats.py — 语料统计（样本量 / 动作分布 / 物品覆盖）

用法::

    python -X utf8 tools/corpus_stats.py output/records/<run_id>
    python -X utf8 tools/corpus_stats.py --all output/records
    python -X utf8 tools/corpus_stats.py --all output/records --json
"""
from __future__ import annotations

import argparse
import json
import os
import sys
from collections import Counter
from pathlib import Path
from typing import Dict, List, Optional

_REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if _REPO not in sys.path:
    sys.path.insert(0, _REPO)

from core.store import load_meta  # noqa: E402
from tools.corpus_fold import fold_dir, fold_run  # noqa: E402


def stats_of(run_dir: Path) -> dict:
    """优先读已折叠的 corpus/，没有就现算（不写盘）。"""
    decisions: List[dict] = []
    lineups: List[dict] = []
    dpath = run_dir / "corpus" / "decisions.jsonl"
    lpath = run_dir / "corpus" / "lineups.jsonl"
    if dpath.exists() or lpath.exists():
        for p, sink in ((dpath, decisions), (lpath, lineups)):
            if not p.exists():
                continue
            with open(p, encoding="utf-8") as f:
                for line in f:
                    line = line.strip()
                    if line:
                        sink.append(json.loads(line))
        fold_stats = None
    else:
        decisions, lineups, fold_stats, _traces = fold_run(run_dir)

    action_kind = Counter()
    action_item = Counter()
    rounds = Counter()
    for rec in decisions:
        for act in (rec.get("actions") or []):
            kind = act.get("kind") or "unknown"
            action_kind[kind] += 1
            if act.get("id"):
                action_item[act["id"]] += 1
        rounds[rec.get("round")] += 1

    lineup_items = Counter()
    for rec in lineups:
        for it in ((rec.get("lineup") or {}).get("items") or []):
            lineup_items[it.get("id")] += 1

    meta = load_meta(run_dir)
    return {
        "run_id": meta.get("run_id") or run_dir.name,
        "decisions": len(decisions),
        "lineups": len(lineups),
        "actions": dict(action_kind.most_common()),
        "top_items": dict(action_item.most_common(15)),
        "lineup_items": dict(lineup_items.most_common(15)),
        "per_round": {str(k): v for k, v in sorted(rounds.items(),
                                                   key=lambda kv: (kv[0] is None, kv[0]))},
        "fold": fold_stats.as_dict() if fold_stats else None,
        "incomplete": bool(meta.get("incomplete")),
    }


def main(argv: Optional[List[str]] = None) -> int:
    ap = argparse.ArgumentParser(description="语料统计")
    ap.add_argument("runs", nargs="*", help="对局目录")
    ap.add_argument("--all", metavar="ROOT", help="统计 ROOT 下所有对局")
    ap.add_argument("--json", action="store_true", help="JSON 输出")
    args = ap.parse_args(argv)

    runs: List[Path] = [Path(p) for p in args.runs]
    if args.all:
        root = Path(args.all)
        runs.extend(sorted(p for p in root.iterdir()
                           if p.is_dir() and (p / "raw").exists()))
    if not runs:
        ap.print_help()
        return 2

    out = []
    for run in runs:
        if not (run / "raw").exists():
            continue
        out.append(stats_of(run))

    if args.json:
        print(json.dumps(out, ensure_ascii=False, indent=2))
        return 0

    total_dec = sum(s["decisions"] for s in out)
    total_lin = sum(s["lineups"] for s in out)
    for s in out:
        print(f"== {s['run_id']} ==")
        print(f"  决策样本: {s['decisions']}   摆盘样本: {s['lineups']}"
              + ("   [不完整]" if s["incomplete"] else ""))
        if s["actions"]:
            print("  动作分布: " + ", ".join(f"{k}={v}"
                                            for k, v in s["actions"].items()))
        if s["per_round"]:
            print("  每回合样本: " + ", ".join(f"R{k}={v}"
                                              for k, v in s["per_round"].items()))
        if s["top_items"]:
            print("  高频动作物品: " + ", ".join(f"{k}×{v}"
                                                for k, v in s["top_items"].items()))
    print()
    print(f"合计 {len(out)} 局：决策样本 {total_dec} 条，摆盘样本 {total_lin} 条")
    return 0


if __name__ == "__main__":
    sys.exit(main())
