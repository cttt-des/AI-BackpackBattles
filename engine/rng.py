# -*- coding: utf-8 -*-
"""engine/rng.py — 平衡随机（对齐 Utility/BalancedRandom.gd + BalancedRange.gd 完整真值）

docs/engine_truth.md §4。接口兼容旧内核（BalancedRng(seed=..., base_rng=...)、
._rng、reset()），供 engine/character.py / engine/item.py 直接使用。
"""
from __future__ import annotations

import random


class BalancedRng:
    """BalancedRandom.gd 完整还原：欠胜加速/过胜减速/防连击/防连败/偏置"""

    def __init__(self, start_bias: float = 0.0, seed: int | None = None,
                 base_rng: random.Random | None = None):
        self._rng = base_rng if base_rng is not None else random.Random(seed)
        # expectedWins = Util.rng.randf_range(0.2, -0.2) + _init bias（BalancedRandom.gd:4,9）
        self.expected_wins = self._rng.uniform(-0.2, 0.2) + start_bias
        self.wins = 0
        self.balancedness = 3.0
        self.last_result = False

    def set_bias(self, bias: float):
        self.expected_wins += bias

    def roll(self, target: float) -> bool:
        if target <= 0:
            return False
        if target >= 1:
            return True

        chance = target
        dif = self.expected_wins - self.wins
        if dif > 0.3:
            chance *= self.balancedness * min(1.0, dif)
        elif dif < -0.3:
            chance /= self.balancedness * min(1.0, -dif)

        self.expected_wins += target

        if self.last_result and target < 0.4:
            chance *= 0.5
        elif (not self.last_result) and target > 0.6:
            chance *= 2.0

        # Util.flip：randf() <= chance（含等号）
        result = self._rng.random() <= chance
        self.last_result = result
        if result:
            self.wins += 1
            return True
        return False

    def roll_percent(self, target_percent: float) -> bool:
        return self.roll(target_percent / 100.0)

    def reset(self):
        """BalancedRandom.gd:104：expectedWins 归 0（偏置由 setBias 重设）"""
        self.expected_wins = 0.0
        self.wins = 0
        self.last_result = False


class BalancedRange:
    """BalancedRange.randIntRange：伤害区间累积器（|acc|>=1 向均值修正）"""

    def __init__(self, rng: random.Random):
        self._rng = rng
        self.acc = 0.0

    def reset(self):
        self.acc = 0.0

    def rand_int_range(self, from_: int, to: int) -> int:
        rng_val = self._rng.randint(from_, to)
        expected = 0.5 * (from_ + to)
        dif = rng_val - expected
        if self.acc >= 1:
            malus = min(rng_val - from_, int(self.acc))
            self.acc -= malus
            rng_val -= malus
        elif self.acc <= -1:
            bonus = min(to - rng_val, int(abs(self.acc)))
            self.acc += bonus
            rng_val += bonus
        self.acc += dif
        return rng_val


def flip(rng: random.Random, chance: float = 0.5) -> bool:
    """Util.flip（Util.gd）：randf() <= chance"""
    return rng.random() <= chance


def roll(rng: random.Random, maximum: float = 100.0) -> float:
    return rng.uniform(0.0, maximum)


def flip_percent(rng: random.Random, chance: float) -> bool:
    return rng.uniform(0.0, 100.0) <= chance
