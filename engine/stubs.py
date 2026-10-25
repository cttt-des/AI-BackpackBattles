# -*- coding: utf-8 -*-
"""engine/stubs.py — 显式桩登记表（fail-fast 的白名单面）

与旧架构的本质区别：这里**没有**万能 _Noop 兜底。任何行为代码触到的
引擎面必须属于以下三类之一，否则 = 硬错误（计入 failures，可在战报观测）：
  A. 引擎真实实现（engine/item.py 等的方法/属性）
  B. 本表登记的桩（视觉/引擎内部调用，无战斗语义）——每次命中计数可见
  C. 数据驱动的方法（behavior.methods / class_methods 池）
"""
from __future__ import annotations

from typing import Dict


class StubRegistry:
    """桩命中计数器（战斗可观测：战报里能看到每个桩被命中多少次）"""

    def __init__(self):
        self.hits: Dict[str, int] = {}

    def hit(self, name: str):
        self.hits[name] = self.hits.get(name, 0) + 1

    def make_noop(self, name: str):
        """生成一个登记过的 no-op 调用桩（链式安全）"""
        self.hit(name)

        class _Stub:
            __slots__ = ("_reg", "_name")

            def __init__(self, reg, name):
                object.__setattr__(self, "_reg", reg)
                object.__setattr__(self, "_name", name)

            def _record(self, attr):
                object.__getattribute__(self, "_reg").hit(
                    f"{object.__getattribute__(self, '_name')}.{attr}")

            def __getattr__(self, attr):
                self._record(attr)
                return self

            def __call__(self, *a, **k):
                self._record("__call__")
                return self

            def __setattr__(self, attr, val):
                self._record(f"set:{attr}")

            # 视觉量算术（arm.rotation += PI 等）：结果仍是桩（保持链式自洽）
            def _op(self, *a):
                self._record("__arith__")
                return self

            __add__ = __radd__ = __iadd__ = _op
            __sub__ = __rsub__ = __isub__ = _op
            __mul__ = __rmul__ = __imul__ = _op
            __truediv__ = __rtruediv__ = __itruediv__ = _op

            def __eq__(self, other):
                # current_animation != '' 等比较：桩与任意值不等（ falsy 分支）
                return self is other

            def __hash__(self):
                return id(self)

            def __repr__(self):
                return f"<Stub {object.__getattribute__(self, '_name')}>"

            def __str__(self):
                return ""

        return _Stub(self, name)


# 已登记桩清单（gen 期校验依据；运行期命中全部计数可见）
REGISTERED_STUBS = {
    # —— 视觉/动画 ——
    "visual_only": "纯视觉调用（粒子/tween/动画/音效/贴图/位置）",
    # —— 引擎内部表现层 ——
    "combatLog_snapshot": "CombatLog.snapshotItem* 系列：仅工具提示快照，无战斗语义",
    "combatLog_metric": "CombatLog.addMetric 等指标记录",
    "show_cooldown": "showCooldown(Smooth)：冷却条视觉",
    "setState_visual": "Item.setState 的表现层部分（战斗态由引擎 set_state 管理）",
}

# 物品实例上的**视觉属性**（节点引用/材质/音效/粒子等）：
# __getattr__ 命中这些名字 → 返回登记桩（计数可见），否则 AttributeError 硬失败
VISUAL_ITEM_ATTRS = {
    "preload", "activationParticles", "activationPulse", "Color", "Color2",
    "impactSoundVolume", "pickupSound", "drinkSound", "triggerSound",
    "shovelSound", "timeDilatorSound", "sound", "dragParticles",
    "specificDragParticles", "spawnPos", "digParticles", "blindParticles",
    "spadesParticles", "fluid", "fluidTween", "fluidGradient",
    "fluidGradientTex", "baseFoaminess", "baseScroll", "baseLevelModification",
    "connectorScene", "notInChainMark", "cardAnimation", "front", "back",
    "activeFront", "digUpBag", "critTimer", "buffTimer", "speedTimer",
    "particleTimer", "blindingLightTimer", "unhealingTimer", "healingReductionTimer",
    "poisonTimer", "speedbuffTimer", "invuTimer", "digUpItems", "filters",
    "activationParticles1", "activationParticles2", "activationPulse1",
    "hitParticles", "blockParticles", " ManaOrbGlow", "ManaOrbGlow",
    "manaOrbGlow", "glow", "PulsePosition", "Icon", "icon", "sprite",
    "chargeParticles", "hatchParticles", "spadesParticles", "SpawnParticles",
    "spawnParticles", "shadow", "bounce", "progressMaterial",
    # 节点引用类（反编译源 `$Icon / TileMap` 空格伪影 → 转译成除法表达式，
    # onready 赋值失败后属性缺失；iv 初始化跳过数值默认值，此处接视觉桩）
    "bagTilemap", "bag_tilemap", "border", "arm", "arm2", "armAnimation",
    "arm_animation", "armSprite", "arm_animation_sprite",
    "goobertAnimation", "goobert_animation", "idleAnimation", "idle_animation",
    "activeParticles", "active_particles", "filling", "fillingGlow",
    "filling_glow", "light", "TileMap", "tilemap",
}


# 遗留视觉桩（engine 内部兼容点；命中计数可见）
_LEGACY_STUBS = StubRegistry()
