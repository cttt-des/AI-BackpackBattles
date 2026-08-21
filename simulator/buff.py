# -*- coding: utf-8 -*-
"""buff.py — Buff 栈系统（对齐 Core/Buff.gd）

包含：永久栈 + 临时栈（duration 超时消失）、抗性（resistChancePercent）、
反射（reflectChancePercent）、净化保护（cleanseProtectionChancePercent）、
MAX_STACKS 上限（Block=100000，其余=10000）。
"""
from __future__ import annotations

from typing import Optional, TYPE_CHECKING

if TYPE_CHECKING:
    from .character import Character


# buff 类型常量（对齐 Game.EventType，仅栈类型）
class BuffType:
    BLOCK = 100
    LUCKY = 101
    REGENERATION = 102
    VAMPIRISM = 103
    SPIKES = 104
    MANA = 105
    EMPOWER = 106
    HEAT = 107
    POISON = 108
    BLIND = 109
    COLD = 110

    ALL = [BLOCK, LUCKY, REGENERATION, VAMPIRISM, SPIKES, MANA,
           EMPOWER, HEAT, POISON, BLIND, COLD]

    # 名称 <-> 类型
    NAMES = {
        "block": BLOCK, "lucky": LUCKY, "regen": REGENERATION,
        "vampirism": VAMPIRISM, "spikes": SPIKES, "mana": MANA,
        "empower": EMPOWER, "heat": HEAT, "poison": POISON,
        "blind": BLIND, "cold": COLD,
    }
    INV = {v: k for k, v in NAMES.items()}


def is_buff(t: int) -> bool:
    return BuffType.BLOCK <= t <= BuffType.HEAT


def is_debuff(t: int) -> bool:
    return BuffType.POISON <= t <= BuffType.COLD


class TemporaryStacks:
    """Buff.gd 内部类 TemporaryStacks"""
    __slots__ = ("amount", "timeout", "item")

    def __init__(self, amount: int, timeout: float, item=None):
        self.amount = amount
        self.timeout = timeout          # 绝对时间（战斗时钟）
        self.item = item


class Buff:
    """对齐 Buff.gd：单一 buff 类型的栈管理"""

    def __init__(self, btype: int, character: 'Character'):
        self.type = btype
        self.is_buff = is_buff(btype)
        self.character = character
        self.current: int = 0
        self.permanent_stacks: int = 0
        self.temporary_stacks: list[TemporaryStacks] = []
        # 抗性 / 反射 / 净化保护（百分数）
        self.resist_chance_percent: float = 0.0
        self.resist_stacks: int = 0
        self.reflect_chance_percent: float = 0.0
        self.cleanse_protection_chance_percent: float = 0.0
        # 最近一次增减的 抗性/反射/保护 计数（供日志渲染 resist/reflect/protect 行）
        self.last_resisted: int = 0
        self.last_reflected: int = 0
        self.last_protected: int = 0
        self.max_stacks = 100000 if btype == BuffType.BLOCK else 10000

    @property
    def signalName(self) -> str:
        """camelCase 别名（行为脚本以 signalName 访问）"""
        return self.signal_name

    @property
    def signal_name(self) -> str:
        """signalName — 该 buff 栈变化时的角色信号名（Mr Struggles 等连接用）"""
        name = BuffType.INV.get(self.type, '').lower()
        return f"character_{name}_changed"

    # ---------------- 基础 ----------------
    def get_stacks(self) -> int:
        return self.current

    def set_stacks(self, amount: int):
        self.current = amount

    def reset(self):
        self.current = 0
        self.permanent_stacks = 0
        self.temporary_stacks.clear()
        self.resist_chance_percent = 0.0
        self.resist_stacks = 0
        self.reflect_chance_percent = 0.0
        self.cleanse_protection_chance_percent = 0.0

    def change_resist_chance(self, chance: float):
        self.resist_chance_percent += chance

    def change_resist_stacks(self, amount: int):
        self.resist_stacks = max(0, self.resist_stacks + int(amount))

    def change_reflect_chance(self, amount: float):
        self.reflect_chance_percent += amount

    def change_cleanse_protection_chance(self, chance: float):
        self.cleanse_protection_chance_percent += chance

    # ---------------- 增益（对齐 Buff.gainTemporary） ----------------
    def gain_temporary(self, amount: int, duration: float, item=None,
                       trigger_event=None, reflect: bool = False, rng=None):
        """
        gainTemporary — 完整抗性/反射/上限流程。
        返回实际增加层数。
        """
        if amount <= 0:
            return 0

        # 抗性判定（逐层）
        total_resist = self.resist_chance_percent
        if item is not None and not reflect:
            amp = getattr(item, 'get_amplification_chance_percent', None)
            if amp is not None:
                total_resist -= amp(self.type)
        resisted = 0
        if total_resist > 0:
            for _ in range(amount):
                if rng is not None and rng.random() * 100.0 < total_resist:
                    resisted += 1
        elif total_resist < 0:
            for _ in range(amount):
                if rng is not None and rng.random() * 100.0 < -total_resist:
                    amount += 1
        left = amount - resisted

        # 反射（仅 debuff，非 reflect 传递）
        reflected = 0
        if not self.is_buff and not reflect:
            for _ in range(amount):
                if rng is not None and rng.random() * 100.0 < self.reflect_chance_percent:
                    reflected += 1
            left -= reflected
            # debuffReflectStacks（固定反射层数）
            if left > 0 and self.character.debuff_reflect_stacks > 0:
                used = min(left, self.character.debuff_reflect_stacks)
                reflected += used
                left -= used
                self.character.change_debuff_reflect_stacks(-used)
            if reflected > 0:
                amount -= reflected
                # 反射给对方（递归调用 gainTemporary with reflect=True）
                if self.character.opponent is not None:
                    self.character.opponent.gain_stacks_temporary(
                        self.type, reflected, duration, item, trigger_event, True)

        # 抗性栈 / 角色 debuff 抗性栈
        if not self.is_buff:
            pass  # resistStacks 逻辑简化（武器连击等不常涉及）

        # 记录抗性/反射计数（供日志）
        if not self.is_buff:
            own_stacks_used = min(left, self.resist_stacks)
            resisted += own_stacks_used
            left -= own_stacks_used
            self.resist_stacks -= own_stacks_used
            character_stacks_used = min(left, self.character.debuff_resist_stacks)
            resisted += character_stacks_used
            left -= character_stacks_used
            self.character.change_debuff_resist_stacks(-character_stacks_used)
            amount -= own_stacks_used + character_stacks_used

        self.last_resisted = resisted
        self.last_reflected = reflected

        # 上限裁剪
        if amount > 0:
            amount = min(amount, self.max_stacks - self.current)
            if amount == 0:
                return 0
            self.current += amount

            if duration < 0:
                self.permanent_stacks += amount
            else:
                # 用引擎当前时钟（绝对时间）计算超时点
                base_time = 0.0
                ch_log = getattr(self.character, 'log', None)
                if ch_log is not None:
                    base_time = ch_log.current_time
                self.temporary_stacks.append(TemporaryStacks(amount, base_time + duration, item))

        return amount

    def gain_stacks(self, amount: int, item=None, trigger_event=None, reflect: bool = False) -> int:
        return self.gain_temporary(amount, -1, item, trigger_event, reflect)

    # ---------------- 失去（对齐 Buff.loseStacks） ----------------
    def lose_stacks(self, amount: int, item=None, trigger_event=None, used: bool = False) -> int:
        amount = min(self.current, amount)

        if not used:
            protected = 0
            # 净化保护
            cp = self.cleanse_protection_chance_percent
            rng = getattr(self.character, '_rng', None)
            if cp > 0:
                for _ in range(amount):
                    if rng is not None and rng.random() * 100.0 < cp:
                        protected += 1
            elif cp < 0:
                for _ in range(amount):
                    if rng is not None and rng.random() * 100.0 < -cp:
                        protected -= 1
            amount -= protected
            self.last_protected = protected
            amount = max(0, min(amount, self.current))
            # buff 保护栈
            if (self.is_buff and self.type != BuffType.BLOCK
                    and amount > 0 and self.character.buff_protect_stacks > 0):
                used_prot = min(amount, self.character.buff_protect_stacks)
                amount -= used_prot
                self.character.buff_protect_stacks -= used_prot

        # 永久栈优先扣除，再扣临时栈（最远的先扣）
        if not self.is_buff and amount > 0 and self.resist_stacks > 0:
            protected_by_stacks = min(amount, self.resist_stacks)
            amount -= protected_by_stacks
            self.resist_stacks -= protected_by_stacks

        if self.permanent_stacks >= amount:
            self.permanent_stacks -= amount
        else:
            remaining = amount - self.permanent_stacks
            self.permanent_stacks = 0
            while remaining > 0 and self.temporary_stacks:
                farthest = max(self.temporary_stacks, key=lambda s: s.timeout)
                if farthest.amount > remaining:
                    farthest.amount -= remaining
                    remaining = 0
                else:
                    remaining -= farthest.amount
                    self.temporary_stacks.remove(farthest)

        change = min(self.current, amount)
        if change > 0:
            self.current -= change
        return change

    # ---------------- 超时 ----------------
    def process_timeouts(self, now: float, log=None, character_id=None):
        """检查临时栈超时（对齐 onTimeout）"""
        removed = []
        for s in self.temporary_stacks:
            if s.timeout <= now:
                removed.append(s)
        for s in removed:
            self.temporary_stacks.remove(s)
            change = min(self.current, s.amount)
            if change > 0:
                self.current -= change
                if log is not None:
                    log.stack_timeout(now, character_id, character_id,
                                      getattr(s.item, 'key', None) if s.item else None,
                                      BuffType.INV.get(self.type, str(self.type)),
                                      change, buff_type=self.type)
        return len(removed)
