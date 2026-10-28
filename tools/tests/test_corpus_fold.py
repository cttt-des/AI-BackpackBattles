# -*- coding: utf-8 -*-
"""test_corpus_fold.py — 折叠层单测（合成对局目录，无游戏依赖）

验证：
* 反复摆盘（来回 move/place）净零 → 整段丢弃，不产样本
* 反复切换锁定后回到原状 → 整段丢弃
* 锁→解锁→锁 → 折叠成一条 set_reserved(true)
* 买入被切成决策点，且 next_state 正确
* combat_start 产出一条 lineups 记录
* 状态重放：折叠出的 next_state 与原始记录末态一致
"""
from __future__ import annotations

import json
import os
import shutil
import sys
import tempfile
import unittest
from pathlib import Path

_HERE = os.path.dirname(os.path.abspath(__file__))
# 向上找到仓库根（含 core/lineup.py 的目录），不依赖测试文件所在的层级
_ROOT = _HERE
while not os.path.exists(os.path.join(_ROOT, "core", "lineup.py")):
    parent = os.path.dirname(_ROOT)
    if parent == _ROOT:
        raise RuntimeError("未找到仓库根目录（core/lineup.py）")
    _ROOT = parent
if _ROOT not in sys.path:
    sys.path.insert(0, _ROOT)

from tools.corpus_fold import FoldStats, fold_run  # noqa: E402

# 临时目录放仓库内：部分沙箱环境不允许写系统 temp
_TMP_ROOT = Path(_ROOT) / ".recorder_test_tmp"


def _mkdtemp(prefix: str) -> Path:
    """不用 tempfile.mkdtemp：它建 0700 目录，在部分 Windows 沙箱下会让
    子目录 mkdir 被拒（WinError 5）。这里自己建普通目录。"""
    _TMP_ROOT.mkdir(parents=True, exist_ok=True)
    for i in range(1000):
        p = _TMP_ROOT / f"{prefix}{os.getpid()}_{i}"
        if not p.exists():
            p.mkdir()
            return p
    raise RuntimeError("无法创建测试临时目录")


def _make_run(tmp: Path, events, snapshots=None, meta=None) -> Path:
    run = tmp / "20260101_000000_r01"
    (run / "raw").mkdir(parents=True)
    (run / "snapshots").mkdir(parents=True)
    (run / "meta.json").write_text(json.dumps(meta or {
        "schema": 4, "run_id": run.name, "character": "Ranger",
        "source": "human", "started_at": "2026-01-01T00:00:00",
    }, ensure_ascii=False), encoding="utf-8")
    lines = [json.dumps(e, ensure_ascii=False) for e in events]
    (run / "raw" / "R01.jsonl").write_text("\n".join(lines) + ("\n" if lines else ""),
                                           encoding="utf-8")
    for name, data in (snapshots or {}).items():
        (run / "snapshots" / f"{name}.json").write_text(
            json.dumps(data, ensure_ascii=False), encoding="utf-8")
    return run


def _shop_snap(round_num=1, gold=10, shop=None, backpack=None):
    return {
        "round": round_num, "gold": gold, "hp": 5, "wins": 0, "losses": 0,
        "character": "Ranger",
        "backpack": backpack or {"version": 4, "grid": [7, 9], "items": []},
        "storage": [],
        "shop": shop or [
            {"slot": 0, "id": "Dagger", "price": 3, "normal_price": 3,
             "on_sale": False, "free": False, "bought": False, "reserved": False},
            {"slot": 1, "id": "Broom", "price": 4, "normal_price": 4,
             "on_sale": False, "free": False, "bought": False, "reserved": False},
        ],
    }


def _ev(seq, type_, round_=1, action=None, delta=None, anchor="R01_shop_open"):
    return {"seq": seq, "t": float(seq), "type": type_, "round": round_,
            "phase": "shop", "source": "diff", "confidence": 0.9,
            "action": action or {}, "delta": delta or {}, "anchor": anchor}


class TestFoldZeroNet(unittest.TestCase):
    def setUp(self):
        self.tmp = _mkdtemp("foldtest_")

    def tearDown(self):
        shutil.rmtree(self.tmp, ignore_errors=True)

    def test_repeated_placement_net_zero_is_dropped(self):
        """同一物品来回摆 4 次、最后回到原位 → 过程段净零，不产样本。"""
        events = [
            _ev(1, "round_start", action={"to_round": 1}),
            _ev(2, "move", action={"id": "Dagger", "from": [2, 3], "to": [4, 5], "r": 0}),
            _ev(3, "rotate", action={"id": "Dagger", "at": [4, 5], "from_r": 0, "to_r": 90}),
            _ev(4, "rotate", action={"id": "Dagger", "at": [4, 5], "from_r": 90, "to_r": 0}),
            _ev(5, "move", action={"id": "Dagger", "from": [4, 5], "to": [2, 3], "r": 0}),
            _ev(6, "combat_start", action={"anchor": "snapshots/R01_combat_start.json"}),
        ]
        snap = _shop_snap(backpack={"version": 4, "grid": [7, 9], "items": [
            {"id": "Dagger", "at": [2, 3], "r": 0}]})
        run = _make_run(self.tmp, events, snapshots={"R01_shop_open": snap})
        decisions, lineups, stats, _t = fold_run(run)
        self.assertEqual(stats.dropped_zero_segments, 1)
        self.assertEqual(stats.decisions, 0)      # round_start 不产样本
        self.assertEqual(len(lineups), 1)

    def test_placement_with_net_change_is_kept(self):
        """来回摆几次但净位置不同 → 该段不丢弃（保留在 next_state 里）。"""
        events = [
            _ev(1, "round_start", action={"to_round": 1}),
            _ev(2, "move", action={"id": "Dagger", "from": [2, 3], "to": [4, 5], "r": 0}),
            _ev(3, "move", action={"id": "Dagger", "from": [4, 5], "to": [5, 5], "r": 0}),
            _ev(4, "combat_start", action={"anchor": "snapshots/R01_combat_start.json"}),
        ]
        snap = _shop_snap(backpack={"version": 4, "grid": [7, 9], "items": [
            {"id": "Dagger", "at": [2, 3], "r": 0}]})
        run = _make_run(self.tmp, events, snapshots={"R01_shop_open": snap})
        _d, _l, stats, _t = fold_run(run)
        self.assertEqual(stats.dropped_zero_segments, 0)
        # 摆盘净变化不产决策样本（交给摆盘 AI / lineups），但段被记录下来
        self.assertEqual(stats.decisions, 0)
        self.assertEqual(stats.placement_only_segments, 1)

    def test_lock_toggle_back_to_original_is_dropped(self):
        events = [
            _ev(1, "round_start", action={"to_round": 1}),
            _ev(2, "lock", action={"slot": 0, "id": "Dagger", "price": 3}),
            _ev(3, "unlock", action={"slot": 0, "id": "Dagger", "price": 3}),
            _ev(4, "lock", action={"slot": 0, "id": "Dagger", "price": 3}),
            _ev(5, "unlock", action={"slot": 0, "id": "Dagger", "price": 3}),
            _ev(6, "combat_start", action={"anchor": "snapshots/R01_combat_start.json"}),
        ]
        run = _make_run(self.tmp, events, snapshots={"R01_shop_open": _shop_snap()})
        decisions, lineups, stats, _t = fold_run(run)
        self.assertEqual(stats.dropped_zero_segments, 1)
        self.assertEqual(stats.decisions, 0)

    def test_lock_toggle_ending_locked_folds_to_one(self):
        events = [
            _ev(1, "round_start", action={"to_round": 1}),
            _ev(2, "lock", action={"slot": 0, "id": "Dagger", "price": 3}),
            _ev(3, "unlock", action={"slot": 0, "id": "Dagger", "price": 3}),
            _ev(4, "lock", action={"slot": 0, "id": "Dagger", "price": 3}),
            _ev(5, "buy", action={"slot": 1, "id": "Broom", "price": 4},
                delta={"gold": -4}),
            _ev(6, "combat_start", action={"anchor": "snapshots/R01_combat_start.json"}),
        ]
        run = _make_run(self.tmp, events, snapshots={"R01_shop_open": _shop_snap()})
        decisions, _lineups, stats, _t = fold_run(run)
        self.assertEqual(stats.decisions, 2)     # 锁定决策 + 买入决策
        rec = decisions[0]
        self.assertEqual(rec["actions"][0]["kind"], "set_reserved")
        self.assertTrue(rec["actions"][0]["value"])
        self.assertEqual(rec["actions"][0]["slot"], 0)
        self.assertEqual(sum(1 for a in rec["actions"]
                             if a["kind"] == "set_reserved"), 1)
        self.assertEqual(stats.folded_lock_toggles, 2)   # 3 次切换 → 1 条
        # 买入样本不该含 set_reserved（锁定已独立成样本）
        self.assertEqual([a["kind"] for a in decisions[1]["actions"]], ["buy"])

    def test_buy_becomes_decision_with_next_state(self):
        events = [
            _ev(1, "round_start", action={"to_round": 1}),
            _ev(2, "buy", action={"slot": 1, "id": "Broom", "price": 4,
                                  "price_source": "decoded"},
                delta={"gold": -4}),
            _ev(3, "place", action={"id": "Broom", "at": [1, 1], "r": 0,
                                    "from": "shop"}),
            _ev(4, "combat_start", action={"anchor": "snapshots/R01_combat_start.json"}),
        ]
        run = _make_run(self.tmp, events, snapshots={"R01_shop_open": _shop_snap()})
        decisions, _lineups, stats, _t = fold_run(run)
        self.assertEqual(stats.decisions, 1)
        rec = decisions[0]
        self.assertEqual(rec["actions"][0]["kind"], "buy")
        self.assertEqual(rec["actions"][0]["id"], "Broom")
        self.assertEqual(rec["state"]["gold"], 10)
        # 摆放过程体现在 next_state，而不是变成动作
        ids = [it["id"] for it in rec["next_state"]["backpack"]]
        self.assertIn("Broom", ids)
        self.assertNotIn("place", [a["kind"] for a in rec["actions"]])

    def test_combat_start_captures_combat_lineup(self):
        lineup = {"version": 4, "grid": [7, 9], "items": [
            {"id": "Dagger", "at": [2, 3], "r": 0}]}
        events = [
            _ev(1, "round_start", action={"to_round": 1}),
            _ev(2, "combat_start", action={"anchor": "snapshots/R01_combat_start.json"}),
        ]
        run = _make_run(self.tmp, events, snapshots={
            "R01_shop_open": _shop_snap(),
            "R01_combat_start": {"round": 1, "gold": 10, "hp": 5,
                                 "backpack": lineup, "backpack_combat": lineup,
                                 "shop": []},
        })
        _dec, lineups, stats, _t = fold_run(run)
        self.assertEqual(len(lineups), 1)
        self.assertEqual(lineups[0]["lineup"]["items"][0]["id"], "Dagger")
        self.assertEqual(lineups[0]["round"], 1)

    def test_unknown_change_is_counted_not_emitted(self):
        events = [
            _ev(1, "round_start", action={"to_round": 1}),
            _ev(2, "unknown_change", action={}),
            _ev(3, "combat_start", action={"anchor": "snapshots/R01_combat_start.json"}),
        ]
        run = _make_run(self.tmp, events, snapshots={"R01_shop_open": _shop_snap()})
        _d, _l, stats, _t = fold_run(run)
        self.assertEqual(stats.unknown_changes, 1)


class TestFoldReplayConsistency(unittest.TestCase):
    """折叠得到的状态必须与直接用 apply_event 重放的结果一致。"""

    def setUp(self):
        self.tmp = _mkdtemp("foldtest_")

    def tearDown(self):
        shutil.rmtree(self.tmp, ignore_errors=True)

    def test_placement_after_buy_lands_in_next_state(self):
        events = [
            _ev(1, "round_start", action={"to_round": 1}),
            _ev(2, "buy", action={"slot": 0, "id": "Dagger", "price": 3},
                delta={"gold": -3}),
            _ev(3, "place", action={"id": "Dagger", "at": [2, 3], "r": 90,
                                    "gems": ["Chipped Ruby"], "from": "shop"}),
            _ev(4, "buy", action={"slot": 1, "id": "Broom", "price": 4},
                delta={"gold": -4}),
            _ev(5, "combat_start", action={"anchor": "snapshots/R01_combat_start.json"}),
        ]
        run = _make_run(self.tmp, events, snapshots={"R01_shop_open": _shop_snap()})
        decisions, _l, _s, _t = fold_run(run)
        self.assertEqual(len(decisions), 2)
        first = decisions[0]
        bp = first["next_state"]["backpack"]
        self.assertEqual(len(bp), 1)
        self.assertEqual(bp[0]["at"], [2, 3])
        self.assertEqual(bp[0]["r"], 90)
        self.assertEqual(bp[0]["gems"], ["Chipped Ruby"])
        self.assertEqual(first["next_state"]["gold"], 7)
        self.assertEqual(decisions[1]["state"]["gold"], 7)


if __name__ == "__main__":
    unittest.main(verbosity=2)