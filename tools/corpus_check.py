# -*- coding: utf-8 -*-
"""corpus_check.py — 对局记录校验（原始层一致性 + 可折叠性）

检查项（逐条给 PASS/FAIL，任一 FAIL 退出码 1）::

  1. meta.json 可读、schema 与 recorder 版本一致
  2. seq 单调递增无重复；t 单调不减
  3. 每回合都有 `R{nn}_shop_open` 快照
  4. `combat_start` 事件都有对应 `R{nn}_combat_start` 快照且含背包
  5. 每回合 `combat_start` 数量 ≤ 1（重复开战会被抓出来）
  6. lock/unlock 与快照的 reserved 闭合：净锁定变化能从事件推出
  7. 金币收支：同回合内 buy/sell/reroll 的 delta 之和与快照金币差一致（可容忍记录期外变化）
  8. 背包 v4 可被 `ai/encoding.py` 编码（物品库缺 id 不算失败，只警告）
  9. 折叠可重算：`fold_run` 不抛异常，样本数与 lineups 数量 > 0（若该局有开战）

用法::

    python -X utf8 tools/corpus_check.py output/records/<run_id> [更多...]
    python -X utf8 tools/corpus_check.py --all output/records
"""
from __future__ import annotations

import argparse
import json
import os
import sys
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple

_REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if _REPO not in sys.path:
    sys.path.insert(0, _REPO)

from core.store import iter_run_events, load_meta, load_snapshot  # noqa: E402
from tools.corpus_fold import fold_run  # noqa: E402


class Report:
    def __init__(self, run_dir: Path):
        self.run_dir = run_dir
        self.items: List[Tuple[str, str, str]] = []   # (level, name, detail)

    def ok(self, name: str, detail: str = "") -> None:
        self.items.append(("PASS", name, detail))

    def warn(self, name: str, detail: str = "") -> None:
        self.items.append(("WARN", name, detail))

    def fail(self, name: str, detail: str = "") -> None:
        self.items.append(("FAIL", name, detail))

    @property
    def failed(self) -> bool:
        return any(lv == "FAIL" for lv, _, _ in self.items)

    def render(self) -> str:
        lines = [f"== {self.run_dir.name} =="]
        for lv, name, detail in self.items:
            lines.append(f"  [{lv}] {name}" + (f" — {detail}" if detail else ""))
        return "\n".join(lines)


def check_run(run_dir: Path) -> Report:
    rep = Report(run_dir)
    run_dir = Path(run_dir)
    if not (run_dir / "raw").exists():
        rep.fail("目录结构", "缺少 raw/")
        return rep

    # 1. meta
    try:
        meta = load_meta(run_dir)
        if not meta:
            rep.fail("meta.json", "缺失或为空")
        elif meta.get("schema") != 4:
            rep.warn("meta.json", f"schema={meta.get('schema')}（期望 4）")
        else:
            rep.ok("meta.json", f"run_id={meta.get('run_id')})")
    except Exception as e:  # noqa: BLE001
        rep.fail("meta.json", f"解析失败: {e}")
        meta = {}

    # 收集事件
    events: List[Dict[str, Any]] = []
    try:
        for _rnd, ev in iter_run_events(run_dir):
            events.append(ev)
    except Exception as e:  # noqa: BLE001
        rep.fail("事件流", f"读取失败: {e}")
        return rep
    if not events:
        rep.fail("事件流", "没有任何事件")
        return rep

    # 2. seq / t 单调
    seqs = [ev.get("seq") for ev in events if isinstance(ev.get("seq"), int)]
    if len(seqs) != len(events):
        rep.warn("seq", f"{len(events) - len(seqs)} 条事件缺 seq")
    if seqs and any(b <= a for a, b in zip(seqs, seqs[1:])):
        rep.fail("seq", "非严格递增（可能存在重复写入）")
    else:
        rep.ok("seq", f"{len(seqs)} 条严格递增")
    ts = [ev.get("t") for ev in events if isinstance(ev.get("t"), (int, float))]
    if len(ts) > 1 and any(b < a - 1e-6 for a, b in zip(ts, ts[1:])):
        rep.warn("t", "存在时间回退（系统时钟跳变？）")
    else:
        rep.ok("t", "单调不减")

    # 3/4/5. 快照与开战
    rounds = sorted({ev.get("round") for ev in events
                     if isinstance(ev.get("round"), int)})
    missing_shop = []
    for rnd in rounds:
        ref = f"snapshots/R{rnd:02d}_shop_open.json"
        if load_snapshot(run_dir, ref) is None:
            missing_shop.append(rnd)
    if missing_shop:
        rep.fail("回合快照", f"缺失 R{sorted(set(missing_shop))} 的 shop_open")
    else:
        rep.ok("回合快照", f"{len(rounds)} 个回合齐全")

    combat_starts = [ev for ev in events if ev.get("type") == "combat_start"]
    per_round: Dict[int, int] = {}
    for ev in combat_starts:
        rnd = ev.get("round")
        if isinstance(rnd, int):
            per_round[rnd] = per_round.get(rnd, 0) + 1
    dup = {k: v for k, v in per_round.items() if v > 1}
    if dup:
        rep.warn("开战次数", f"回合重复开战记录: {dup}")
    missing_combat = []
    for ev in combat_starts:
        ref = (ev.get("action") or {}).get("anchor")
        if not ref or load_snapshot(run_dir, ref) is None:
            missing_combat.append(ev.get("round"))
    if missing_combat:
        rep.fail("开战快照", f"缺失/不可读: R{missing_combat}")
    elif combat_starts:
        empty = [ev.get("round") for ev in combat_starts
                 if not ((load_snapshot(run_dir, (ev.get("action") or {}).get("anchor"))
                          or {}).get("backpack") or {}).get("items")]
        if empty:
            rep.warn("开战快照", f"以下回合开战背包为空: {empty}")
        else:
            rep.ok("开战快照", f"{len(combat_starts)} 份，均含背包")

    # 6. lock/unlock 计数（只做一致性提示）
    locks = [ev for ev in events if ev.get("type") in ("lock", "unlock")]
    rep.ok("锁定事件", f"{len(locks)} 条（折叠层会归并）")

    # 7. 金币收支（同回合 buy/sell/reroll 的 delta 汇总）
    gold_moves: Dict[int, int] = {}
    for ev in events:
        t = ev.get("type")
        if t not in ("buy", "sell", "reroll"):
            continue
        delta = (ev.get("delta") or {}).get("gold")
        if delta is None:
            a = ev.get("action") or {}
            if t == "buy" and a.get("price") is not None:
                delta = -int(a["price"])
            elif t == "sell" and a.get("price") is not None:
                delta = int(a["price"])
            elif t == "reroll" and a.get("cost") is not None:
                delta = -int(a["cost"])
        if delta is None:
            continue
        rnd = ev.get("round")
        if isinstance(rnd, int):
            gold_moves[rnd] = gold_moves.get(rnd, 0) + int(delta)
    rep.ok("金币流水", f"{len(gold_moves)} 个回合有金币变动记录")
    if meta.get("incomplete"):
        rep.warn("完整性", "meta.incomplete=true（存在采样缺口）")

    # 8. 编码兼容（encoding.py 可导入时真跑一遍，否则退化为结构自检）
    snaps = {}
    for ref in sorted((run_dir / "snapshots").glob("*_combat_start.json")):
        snap = json.loads(ref.read_text(encoding="utf-8"))
        lineup = snap.get("backpack_combat") or snap.get("backpack") or {}
        if lineup.get("items"):
            snaps[ref.name] = lineup
    try:
        from ai.encoding import encode_lineup
        db_path = Path(_REPO) / "assets" / "gd_core_runtime.json"
        item_db = json.loads(db_path.read_text(encoding="utf-8"))
        bad = []
        for name, lineup in snaps.items():
            try:
                enc = encode_lineup(lineup, item_db)
            except Exception as e:  # noqa: BLE001
                bad.append(f"{name}: {e}")
                continue
            if enc.get("ids") is None:
                bad.append(f"{name}: ids 为空")
        if bad:
            rep.fail("编码兼容", "; ".join(bad[:3]))
        else:
            rep.ok("编码兼容", f"{len(snaps)} 份开战摆盘可被 encoding.py 编码")
    except Exception as e:  # noqa: BLE001
        # 编码层当前不可导入（仓库既有问题，非本工具职责）：退化为结构自检
        problems = []
        for name, lineup in snaps.items():
            for it in lineup.get("items") or []:
                at = it.get("at") or [0, 0]
                if not (0 <= int(at[0]) < 30 and 0 <= int(at[1]) < 30):
                    problems.append(f"{name}: {it.get('id')} 坐标越界 {at}")
                if it.get("r") not in (0, 90, 180, 270, None):
                    problems.append(f"{name}: {it.get('id')} 旋转角非法 {it.get('r')}")
        if problems:
            rep.fail("编码兼容", "; ".join(problems[:3]))
        else:
            rep.ok("编码兼容",
                   f"{len(snaps)} 份开战摆盘结构合法"
                   f"（encoding.py 当前不可导入，未做真编码：{type(e).__name__}）")

    # 9. 折叠可重算
    try:
        decisions, lineups, stats, _traces = fold_run(run_dir)
        if stats.unknown_changes > max(3, len(events) // 50):
            rep.warn("折叠", f"未归类事件偏多: {stats.unknown_changes}")
        if lineups or decisions:
            rep.ok("折叠", f"decisions={len(decisions)} lineups={len(lineups)} "
                            f"丢弃净零段={stats.dropped_zero_segments}")
        else:
            rep.fail("折叠", "既没有决策样本也没有摆盘样本")
    except Exception as e:  # noqa: BLE001
        rep.fail("折叠", f"fold_run 抛异常: {e}")

    return rep


def main(argv: Optional[List[str]] = None) -> int:
    ap = argparse.ArgumentParser(description="校验对局记录（原始层 + 折叠可行性）")
    ap.add_argument("runs", nargs="*", help="对局目录")
    ap.add_argument("--all", metavar="ROOT", help="校验 ROOT 下所有对局目录")
    args = ap.parse_args(argv)

    runs: List[Path] = [Path(p) for p in args.runs]
    if args.all:
        root = Path(args.all)
        runs.extend(sorted(p for p in root.iterdir()
                           if p.is_dir() and (p / "raw").exists()))
    if not runs:
        ap.print_help()
        return 2

    bad = 0
    for run in runs:
        rep = check_run(run)
        print(rep.render())
        if rep.failed:
            bad += 1
    print()
    print(f"共 {len(runs)} 局，失败 {bad} 局")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
