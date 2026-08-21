# -*- coding: utf-8 -*-
"""rng.py — 平衡随机（还原 Utility/BalancedRandom.gd）

BalancedRng 不是普通随机：它会跟踪"期望胜率 vs 实际胜率"的偏差，
偏差过大时动态调整判定概率，让长线结果接近期望值（防止连续倒霉/连续走运）。
accuracyRng / critRng / critResistanceRng / stunResistanceRng 均为此类。
"""
from __future__ import annotations

import random


class BalancedRng:
    """对齐 BalancedRandom.gd 的 roll / rollPercent / reset"""

    def __init__(self, start_bias: float = 0.0, seed: int | None = None,
                 base_rng: random.Random | None = None):
        self._rng = base_rng if base_rng is not None else random.Random(seed)
        self.expected_wins = self._rng.uniform(-0.2, 0.2) + start_bias
        self.wins = 0
        self.balancedness = 3.0
        self.last_result = False

    def set_bias(self, bias: float):
        self.expected_wins += bias

    def roll(self, target: float) -> bool:
        """roll(target): target ∈ [0,1]"""
        if target <= 0:
            return False
        if target >= 1:
            return True

        chance = target

        # 平衡修正：实际胜率偏离期望过多时调整概率
        dif = self.expected_wins - self.wins
        if dif > 0.3:
            chance *= self.balancedness * min(1.0, dif)
        elif dif < -0.3:
            chance /= self.balancedness * min(1.0, -dif)

        self.expected_wins += target

        # 连败/连胜修正
        if self.last_result and target < 0.4:
            chance *= 0.5
        elif not self.last_result and target > 0.6:
            chance *= 2.0

        result = self._rng.random() < chance
        self.last_result = result
        if result:
            self.wins += 1
        return result

    def roll_percent(self, target_percent: float) -> bool:
        """rollPercent(target): target 为百分数 (0-100)"""
        return self.roll(target_percent / 100.0)

    def reset(self):
        self.expected_wins = 0.0
        self.wins = 0
        self.last_result = False


def rand_int_range(rng: random.Random, lo: int, hi: int) -> int:
    """物品伤害范围随机（对齐 damageRangeRng.randIntRange）"""
    return rng.randint(lo, hi)
