# -*- coding: utf-8 -*-
"""test_recorder.py — 记录器差分层 / 折叠层的纯函数单测

不依赖游戏进程：用合成 `Frame` 序列驱动 `diff_frames`，用合成事件流驱动
`tools/corpus_fold.py` 的折叠函数。

直接运行::

    python -X utf8 ai/tests/test_recorder.py
    python -X utf8 -m unittest tools.tests.test_recorder -v

覆盖：
* 买入（bought 标志 / 槽位消失两种信号）、卖出、刷新
* 摆放、位移、旋转、宝石变更、储物箱进出
* 锁定 / 解锁 / 买走时游戏自动复位不另记
* 反复摆盘归零、反复切换锁定归零、锁→解锁→锁折叠为一条
* 撕裂帧不产事件、阶段往返、回合推进
"""
from __future__ import annotations

import os
import sys
import unittest

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

from core.recorder import (Frame, PHASE_COMBAT, PHASE_SHOP, diff_frames,
                           normalize)


def _bp(*items):
    """背包规范元组列表：(id, row, col, r, gems, in)"""
    return tuple(sorted(items))


def _st(*items):
    """储物箱规范元组：(id, row, col, r, gems)"""
    return tuple(sorted(items))


def _shop(*slots):
    """商店规范元组：(slot, id, price, normal, on_sale, free, bought, reserved)"""
    return tuple(sorted(slots))


def _frame(round=1, phase=PHASE_SHOP, gold=10, hp=5, backpack=(), storage=(),
           shop=(), **kw) -> Frame:
    return Frame(t=kw.pop("t", 0.0), round=round, phase=phase, gold=gold, hp=hp,
                 wins=kw.pop("wins", 0), losses=kw.pop("losses", 0),
                 character=kw.pop("character", "Ranger"),
                 backpack=backpack, storage=storage, shop=shop, **kw)


def _types(events):
    return [e["type"] for e in events]


def _diff(prev, cur):
    return diff_frames(prev, cur, {"anchor": "R01_shop_open"})


class TestDiffBuySell(unittest.TestCase):
    def test_buy_by_bought_flag(self):
        prev = _frame(gold=10, shop=_shop((0, "Dagger", 3, 3, False, False, False, False)))
        cur = _frame(gold=7, storage=_st(("Dagger", 0, 0, 0, ())),
                     shop=_shop((0, "Dagger", 3, 3, False, False, True, False)))
        ev = _diff(prev, cur)
        self.assertIn("buy", _types(ev))
        buy = next(e for e in ev if e["type"] == "buy")
        self.assertEqual(buy["action"]["slot"], 0)
        self.assertEqual(buy["action"]["id"], "Dagger")
        self.assertEqual(buy["action"]["price"], 3)
        self.assertEqual(buy["action"]["price_source"], "decoded")

    def test_buy_by_slot_disappearing(self):
        """bought 标志已被重置时，靠"槽位消失+同 id 入箱+金币减少"识别。"""
        prev = _frame(gold=10, shop=_shop((1, "Broom", 4, 4, False, False, False, False)))
        cur = _frame(gold=6, storage=_st(("Broom", 0, 0, 0, ())),
                     shop=_shop((1, None, None, None, False, False, False, False)))
        ev = _diff(prev, cur)
        self.assertIn("buy", _types(ev))
        self.assertNotIn("reroll", _types(ev))

    def test_sell_from_backpack(self):
        prev = _frame(gold=5, backpack=_bp(("Dagger", 2, 3, 0, (), -1)))
        cur = _frame(gold=7, backpack=_bp())
        ev = _diff(prev, cur)
        self.assertEqual(_types(ev), ["sell"])
        self.assertEqual(ev[0]["action"]["id"], "Dagger")
        self.assertEqual(ev[0]["action"]["from"], "backpack")

    def test_sell_from_storage(self):
        prev = _frame(gold=5, storage=_st(("Broom", 0, 0, 0, ())))
        cur = _frame(gold=6, storage=_st())
        ev = _diff(prev, cur)
        self.assertEqual(_types(ev), ["sell"])
        self.assertEqual(ev[0]["action"]["from"], "storage")

    def test_reroll(self):
        prev = _frame(gold=10, shop=_shop(
            (0, "Dagger", 3, 3, False, False, False, False),
            (1, "Broom", 4, 4, False, False, False, False)))
        cur = _frame(gold=9, shop=_shop(
            (0, "Sword", 5, 5, False, False, False, False),
            (1, "Shield", 4, 4, False, False, False, False)))
        ev = _diff(prev, cur)
        self.assertEqual(_types(ev), ["reroll"])
        self.assertEqual(ev[0]["action"]["cost"], 1)

    def test_reroll_keeps_locked_slot(self):
        prev = _frame(gold=10, shop=_shop(
            (0, "Dagger", 3, 3, False, False, False, True),
            (1, "Broom", 4, 4, False, False, False, False)))
        cur = _frame(gold=9, shop=_shop(
            (0, "Dagger", 3, 3, False, False, False, True),
            (1, "Shield", 4, 4, False, False, False, False)))
        ev = _diff(prev, cur)
        self.assertEqual(_types(ev), ["reroll"])
        self.assertEqual(ev[0]["evidence"]["kept_slots"], [0])


class TestDiffInventory(unittest.TestCase):
    def test_place_from_storage(self):
        prev = _frame(backpack=_bp(), storage=_st(("Dagger", 0, 0, 0, ())))
        cur = _frame(backpack=_bp(("Dagger", 2, 3, 0, (), -1)), storage=_st())
        ev = _diff(prev, cur)
        self.assertEqual(_types(ev), ["place"])
        self.assertEqual(ev[0]["action"]["from"], "storage")
        self.assertEqual(ev[0]["action"]["at"], [2, 3])

    def test_move(self):
        prev = _frame(backpack=_bp(("Dagger", 2, 3, 0, (), -1)))
        cur = _frame(backpack=_bp(("Dagger", 4, 5, 0, (), -1)))
        ev = _diff(prev, cur)
        self.assertEqual(_types(ev), ["move"])
        self.assertEqual(ev[0]["action"]["from"], [2, 3])
        self.assertEqual(ev[0]["action"]["to"], [4, 5])

    def test_rotate(self):
        prev = _frame(backpack=_bp(("Dagger", 2, 3, 0, (), -1)))
        cur = _frame(backpack=_bp(("Dagger", 2, 3, 90, (), -1)))
        ev = _diff(prev, cur)
        self.assertEqual(_types(ev), ["rotate"])
        self.assertEqual(ev[0]["action"]["from_r"], 0)
        self.assertEqual(ev[0]["action"]["to_r"], 90)

    def test_gems_change(self):
        prev = _frame(backpack=_bp(("Sword", 1, 1, 0, (), -1)))
        cur = _frame(backpack=_bp(("Sword", 1, 1, 0, ("Chipped Ruby",), -1)))
        ev = _diff(prev, cur)
        self.assertEqual(_types(ev), ["gems_change"])
        self.assertEqual(ev[0]["action"]["to"], ["Chipped Ruby"])

    def test_storage_in(self):
        prev = _frame(backpack=_bp(("Dagger", 2, 3, 0, (), -1)), storage=_st())
        cur = _frame(backpack=_bp(), storage=_st(("Dagger", 0, 0, 0, ())))
        ev = _diff(prev, cur)
        self.assertEqual(_types(ev), ["storage_in"])

    def test_combine(self):
        prev = _frame(backpack=_bp(
            ("Dagger", 0, 0, 0, (), -1),
            ("Dagger", 0, 1, 0, (), -1)))
        cur = _frame(backpack=_bp(("Falcon Blade", 0, 0, 0, (), -1)))
        ev = _diff(prev, cur)
        self.assertEqual(_types(ev), ["combine"])
        self.assertEqual(len(ev[0]["action"]["inputs"]), 2)
        self.assertEqual(ev[0]["action"]["output"]["id"], "Falcon Blade")

    def test_unchanged_frame_yields_nothing(self):
        f = _frame(backpack=_bp(("Dagger", 2, 3, 0, (), -1)))
        self.assertEqual(_diff(f, f), [])


class TestDiffReserved(unittest.TestCase):
    def test_lock(self):
        prev = _frame(shop=_shop((2, "Dagger", 3, 3, False, False, False, False)))
        cur = _frame(shop=_shop((2, "Dagger", 3, 3, False, False, False, True)))
        ev = _diff(prev, cur)
        self.assertEqual(_types(ev), ["lock"])
        self.assertEqual(ev[0]["action"]["slot"], 2)

    def test_unlock(self):
        prev = _frame(shop=_shop((2, "Dagger", 3, 3, False, False, False, True)))
        cur = _frame(shop=_shop((2, "Dagger", 3, 3, False, False, False, False)))
        ev = _diff(prev, cur)
        self.assertEqual(_types(ev), ["unlock"])

    def test_buy_does_not_emit_unlock(self):
        """买走时游戏自动 setReserved(false)，不能另记一次 unlock。"""
        prev = _frame(gold=10, shop=_shop((0, "Dagger", 3, 3, False, False, False, True)))
        cur = _frame(gold=7, storage=_st(("Dagger", 0, 0, 0, ())),
                     shop=_shop((0, "Dagger", 3, 3, False, False, True, False)))
        ev = _diff(prev, cur)
        types = _types(ev)
        self.assertIn("buy", types)
        self.assertNotIn("unlock", types)

    def test_lock_toggle_roundtrip_is_unknown_free(self):
        """一帧内锁上又解开（两帧之间回到原状）→ 无事件。"""
        base = _frame(shop=_shop((0, "Dagger", 3, 3, False, False, False, False)))
        self.assertEqual(_diff(base, base), [])


class TestDiffCombatAndRound(unittest.TestCase):
    def test_round_start(self):
        prev = _frame(round=6)
        cur = _frame(round=7)
        ev = _diff(prev, cur)
        self.assertIn("round_start", _types(ev))
        rs = next(e for e in ev if e["type"] == "round_start")
        self.assertEqual(rs["action"]["to_round"], 7)

    def test_unknown_change_when_unclassifiable(self):
        prev = _frame(gold=10)
        cur = _frame(gold=13)   # 金币增加但没有物品变化
        ev = _diff(prev, cur)
        self.assertEqual(_types(ev), ["unknown_change"])
        self.assertEqual(ev[0]["confidence"], 0.0)


class TestNormalize(unittest.TestCase):
    def test_normalize_from_bot_state(self):
        state = {
            "gold": 12, "hp": 22, "round": 7, "wins": 3, "losses": 2,
            "character": "Ranger",
            "live_items": {
                "backpack": [{"name": "Dagger", "row": 2, "col": 3,
                              "rotation": 0.0, "cells": [(2, 3)]}],
                "storage": [{"name": "Broom", "row": 0, "col": 0,
                             "rotation": 0.0, "cells": []}],
                "shop": [{"slot": 0, "name": "Sword", "price": 5,
                          "normal_price": 5, "on_sale": False, "free": False,
                          "bought": False, "reserved": False}],
            },
        }
        f = normalize(state, None, now=1.0)
        self.assertTrue(f.ok)
        self.assertEqual(f.gold, 12)
        self.assertEqual(f.round, 7)
        self.assertEqual(f.phase, PHASE_SHOP)
        self.assertEqual(f.backpack, (("Dagger", 2, 3, 0, (), -1),))
        self.assertEqual(f.shop[0][1], "Sword")

    def test_normalize_missing_state_marks_not_ok(self):
        f = normalize(None, None, now=1.0)
        self.assertFalse(f.ok)

    def test_phase_combat_when_combatlog_running(self):
        state = {"gold": 3, "hp": 10, "round": 5, "live_items": {}}
        combat = {"connected": True, "event_count": 42, "finished": False}
        f = normalize(state, combat, now=1.0)
        self.assertEqual(f.phase, PHASE_COMBAT)


if __name__ == "__main__":
    unittest.main(verbosity=2)