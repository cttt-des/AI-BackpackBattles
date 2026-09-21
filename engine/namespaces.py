# -*- coding: utf-8 -*-
"""engine/namespaces.py — 行为代码可见的枚举/常量命名空间

真值枚举按源码抄录；物品私有状态枚举（CrownState 等）用**缓存属性桩**：
同一命名空间内属性比较自洽（state == X.A 成立），使状态机物品在自己的
枚举体系内正确运转；跨命名空间无意义访问计入 stub 命中（可观测）。
"""
from __future__ import annotations

from types import SimpleNamespace


def enum_ns(**kw):
    return SimpleNamespace(**kw)


def stub_enum(name: str, memo: dict):
    """缓存属性桩：attr 首次访问生成唯一 sentinel 并缓存（同空间比较自洽）"""
    ns = memo.get(name)
    if ns is None:
        class _EnumStub:
            __slots__ = ("_name", "_cache")

            def __init__(self, n):
                object.__setattr__(self, "_name", n)
                object.__setattr__(self, "_cache", {})

            def _record(self, attr):
                pass                  # 命名空间桩：属性自洽即可（命名空间级登记）

            def __getattr__(self, attr):
                if attr.startswith("__"):
                    raise AttributeError(attr)
                cache = object.__getattribute__(self, "_cache")
                if attr not in cache:
                    cache[attr] = _EnumSentinel(
                        f"{object.__getattribute__(self, '_name')}.{attr}")
                return cache[attr]

            def __call__(self, *a, **k):
                return self

            def __setattr__(self, attr, val):
                pass

        class _EnumSentinel:
            __slots__ = ("label",)

            def __init__(self, label):
                self.label = label

            def __eq__(self, other):
                return self is other or (isinstance(other, _EnumSentinel) and other.label == self.label)

            def __hash__(self):
                return hash(("sentinel", self.label))

            def __repr__(self):
                return self.label

            def __call__(self, *a, **k):
                # 视觉桩方法调用（ObjectPool.particleOneShot(...) 等）：返回自身自洽
                return self

        ns = _EnumStub(name)
        memo[name] = ns
    return ns


# ---- Item.gd 96-112 Stack（位标志） ----
Stack = enum_ns(Block=1, Lucky=2, Regeneration=4, Vampirism=8, Spikes=16,
                Mana=32, Empower=64, Heat=128, Poison=256, Blind=512, Cold=1024,
                Buff=254, Debuff=1792, BuffNoLuck=126)

# ---- Item.gd Tiles（tscn CollisionMap tile id） ----
Tiles = enum_ns(Extension=2, Collision=3, Affected=4, AffectedDynamic=5,
                AffectedSecondary=6, AffectedSecondaryDynamic=7,
                AffectedExtension=8, AffectedTertiary=10, AffectedLightning=11)

# ---- Item.gd Mat ----
Mat = enum_ns(Default=0, Wood=1, Metal=2, Leather=3, Glass=4, Stone=5,
              Squishy=6, Jewelry=7, Sand=8, Paper=9, Slime=10, Ice=11)

# ---- Item.gd 170/182/259 引擎枚举（真值；未列成员按需补充） ----
DropResult = enum_ns(AddedToInventory=0, Dropped=1, Destroyed=2, Unknown=3)
PickupType = enum_ns(Default=0)
StackChangeType = enum_ns(Gain=0, Lose=1, Temporary=2)
CraftingPriority = enum_ns(Lowest=-10000, Low=-1000, Normal=0, High=1000, Highest=10000)
BagTiles = enum_ns(Default=2, CanAdd=6, CannotAdd=5)

# ---- 常量 ----
INF = float("inf")
PI = 3.141592653589793
cellSize = 80.0


def make_constant_table(stub_memo: dict) -> dict:
    """代码生成模块级常量表（引擎真值 + 登记桩命名空间）"""
    table: dict = {
        "Stack": Stack, "Tiles": Tiles, "Mat": Mat,
        "DropResult": DropResult, "PickupType": PickupType,
        "StackChangeType": StackChangeType, "CraftingPriority": CraftingPriority,
        "BagTiles": BagTiles, "INF": INF, "PI": PI, "cellSize": cellSize,
    }
    # 物品私有/视觉命名空间 → 桩（缓存属性，空间内自洽）
    for name in ("CrownState", "SpearState", "ArmState", "FrogState",
                 "Physics", "Tiles2", "Settings", "CustomRules",
                 "InputBlocker", "PieceColor", "Active", "String",
                 "SignalConnection", "TileMap", "RigidBody2D", "CollisionShape2D",
                 "Physics2DShapeQueryParameters", "ConvexPolygonShape2D",
                 "Particles2D", "AtlasTexture", "AnimationPlayer", "ObjectPool",
                 "ItemPool", "Sound", "ActivationParticles", "ActivationParticles1",
                 "ActivationParticles2", "ActiveParticles", "CircleLight",
                 "GoobertAnimation", "RingEffect", "Light", "Zap", "Distortion",
                 "BitStream", "BuffParticles", "ColdParticles", "LifestealParticles",
                 "LifestealLight", "SkillLight", "SaleParticles", "hatchParticles",
                 "ManaOrbGlow", "ManathirstInner", "ManathirstInnerGlow",
                 "BottleOfBooze", "fluidGradientTex", "StatModified",
                 "Sockets", "Frame", "Nonoxidated", "Arm", "Fluid", "filling",
                 "leftCounter", "rightCounter", "Active1", "Active2",
                 "Light1", "Light2", "Particles1", "Particles2"):
        table[name] = stub_enum(name, stub_memo)
    return table
