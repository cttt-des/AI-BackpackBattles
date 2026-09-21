# -*- coding: utf-8 -*-
"""engine/events.py — 每场战斗的事件日志（惰性渲染：AI 训练热路径不生成文本）

对齐旧 CombatLog 的事件构造 API 面（buff/character/item/combat 的调用点），
事件为轻量 record；文本渲染延后到需要人类可读输出时（v2 暂不渲染）。
"""
from __future__ import annotations

from dataclasses import dataclass, field
from typing import Any, Dict, List, Optional

from .stubs import StubRegistry


@dataclass
class Event:
    t: float
    type: str
    actor: Optional[str] = None            # 'player' / 'opponent'
    target: Optional[str] = None
    origin: Any = None                     # 物品引用（供联动追踪；不进指纹）
    params: Dict[str, Any] = field(default_factory=dict)
    parent: Optional[int] = None
    depth: int = 0
    buff_type: Optional[int] = None


class CombatLog:
    """惰性事件收集器。快照方法（snapshotItem* 系列）为**登记桩**：
    工具提示快照无战斗语义，但必须显式登记（Goobert 家族 prepare 依赖其存在）。"""

    def __init__(self, stubs: StubRegistry):
        self.stubs = stubs
        self.current_time: float = 0.0
        self.events: List[Event] = []
        self.warnings: List[str] = []
        self._next_id = 0
        self._parent_stack: List[int] = []

    # ---------------- 基础 ----------------
    def warn(self, msg: str):
        self.warnings.append(msg)

    def _emit(self, etype: str, actor=None, target=None, origin=None,
              params=None, buff_type=None, parent=None) -> Event:
        if parent is None:
            parent = self._parent_stack[-1] if self._parent_stack else None
        depth = 0
        if parent is not None:
            for ev in reversed(self.events):
                if ev.id == parent:
                    depth = ev.depth + 1
                    break
        ev = Event(self.current_time, etype, actor, target, origin,
                   params or {}, parent, depth, buff_type)
        ev.id = self._next_id
        self._next_id += 1
        self.events.append(ev)
        return ev

    def begin_activation(self, event_id: Optional[int]):
        if event_id is not None:
            self._parent_stack.append(event_id)

    def end_activation(self):
        if self._parent_stack:
            self._parent_stack.pop()

    # ---------------- 战斗流程 ----------------
    def combat_start(self, t: float):
        return self._emit("combat_start")

    def combat_end(self, t: float, winner: str, reason: str):
        return self._emit("combat_end", params={"winner": winner, "reason": reason})

    def fatigue_start(self, t: float):
        return self._emit("fatigue_start")

    def fatigue_damage(self, t, counter, p_amount, o_amount):
        return self._emit("fatigue_damage", params={"counter": counter,
                                                    "amount": p_amount,
                                                    "o_amount": o_amount})

    # ---------------- 物品激活 ----------------
    def item_activate(self, t, actor, origin, params=None, parent=None):
        return self._emit("item_activate", actor=actor, origin=origin,
                          params=params or {}, parent=parent)

    def out_of_stamina(self, t, actor, origin=None):
        return self._emit("out_of_stamina", actor=actor, origin=origin)

    # ---------------- 攻击/伤害 ----------------
    def attack(self, t, actor, target, origin, damage, health_damage,
               crit=False, missed=False, parent=None, hit=True,
               block_absorbed=0, critical=False, **kw):
        return self._emit("attack", actor=actor, target=target, origin=origin,
                          params={"damage": damage, "health_damage": health_damage,
                                  "crit": bool(crit or critical), "missed": bool(missed),
                                  "hit": bool(hit), "block_absorbed": block_absorbed},
                          parent=parent)

    def missed(self, t, actor, target, origin=None, parent=None):
        return self._emit("missed", actor=actor, target=target, origin=origin, parent=parent)

    def lose_health(self, t, actor, amount, origin=None, parent=None):
        return self._emit("lose_health", actor=actor,
                          params={"amount": amount}, parent=parent)

    def death(self, t, actor):
        return self._emit("death", actor=actor)

    def spike_damage(self, t, actor, target, amount, origin=None):
        return self._emit("spike_damage", actor=actor, target=target,
                          params={"amount": amount})

    def unhealing(self, t, actor, target, amount, origin=None):
        return self._emit("unhealing", actor=actor, target=target,
                          params={"amount": amount})

    def crit_resisted(self, t, actor, origin=None):
        return self._emit("crit_resisted", actor=actor, origin=origin)

    # ---------------- 治疗/体力 ----------------
    def heal(self, t, actor, amount, origin=None, parent=None, overheal=0):
        return self._emit("heal", actor=actor,
                          params={"amount": amount, "overheal": overheal}, parent=parent)

    def stamina_gain(self, t, actor, amount, origin=None):
        return self._emit("stamina_gain", actor=actor, params={"amount": amount})

    def stamina_drain(self, t, actor, amount, origin=None):
        return self._emit("stamina_drain", actor=actor, params={"amount": amount})

    # ---------------- Buff 栈 ----------------
    def stack_gain(self, t, actor, target, origin, buff, amount,
                   permanent=True, duration=None, parent=None, resisted=False,
                   reflected=False, protected=False, buff_type=None):
        p = {"buff": buff, "amount": amount, "permanent": permanent}
        if duration is not None:
            p["duration"] = duration
        for flag, val in (("resisted", resisted), ("reflected", reflected),
                          ("protected", protected)):
            if val:
                p[flag] = True
        return self._emit("stack_gain", actor=actor, target=target, origin=origin,
                          params=p, parent=parent, buff_type=buff_type)

    def stack_lose(self, t, actor, buff, amount, origin=None, resisted=False,
                   parent=None, buff_type=None):
        return self._emit("stack_lose", actor=actor, origin=origin,
                          params={"buff": buff, "amount": amount, "resisted": resisted},
                          parent=parent, buff_type=buff_type)

    def stack_timeout(self, t, actor, buff, amount, buff_type=None):
        return self._emit("stack_timeout", actor=actor,
                          params={"buff": buff, "amount": amount}, buff_type=buff_type)

    def stun(self, t, actor, target, duration, origin=None, parent=None):
        return self._emit("stun", actor=actor, target=target,
                          params={"duration": duration}, parent=parent)

    def stun_resisted(self, t, actor, target, origin=None):
        return self._emit("stun_resisted", actor=actor, target=target)

    def stun_end(self, t, actor):
        return self._emit("stun_end", actor=actor)

    def invulnerable_start(self, t, actor, duration):
        return self._emit("invulnerable_start", actor=actor,
                          params={"duration": duration})

    def invulnerable_end(self, t, actor):
        return self._emit("invulnerable_end", actor=actor)

    # ---------------- 登记桩（engine/stubs.py REGISTERED_STUBS） ----------------
    def snapshotItemTooltipStat(self, *a, **k):
        self.stubs.hit("combatLog_snapshot.snapshotItemTooltipStat")

    def snapshotItemState(self, *a, **k):
        self.stubs.hit("combatLog_snapshot.snapshotItemState")

    def addMetric(self, *a, **k):
        self.stubs.hit("combatLog_metric.addMetric")

    # ---------------- 输出面（对齐旧 CombatLog.to_dict/to_text 消费方） ----------------
    def to_dict(self):
        """事件列表（dict 视图）。GUI/工具直接消费返回值——不可返回 None。"""
        return [{"t": ev.t, "type": ev.type, "actor": ev.actor,
                 "target": ev.target,
                 "params": dict(ev.params or {})}
                for ev in self.events]

    def to_text(self, lang=None):
        """按游戏 CombatLog 格式渲染（复刻 CombatEvent.asText()：
        深度缩进 + LOG 模板 + 官方中文物品名；详见 engine/log_text.py）"""
        from .log_text import render_log
        return render_log(self.events, lang or "zh")

    def __getattr__(self, name):
        if name.startswith("_"):
            raise AttributeError(name)
        # 未在类上显式实现的日志方法：登记可见的桩（而非静默 _Noop 或报错）
        # 注意：仅限「调用即丢弃」语义的快照/度量方法；有返回值消费方
        # （to_text/to_dict 类）必须在类上真实实现
        self.stubs.hit(f"combatLog.{name}")
        return lambda *a, **k: None
