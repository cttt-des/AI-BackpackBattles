# -*- coding: utf-8 -*-
"""gd_core_engine.py — 把 gd_core 无头内核接成模拟器的第三个战斗内核

本模块做什么
============
`gd_core/` + `gd_core_items/` 是原版战斗逻辑 1:1 移植（无场景树、无单例、无渲染），
`gd_core_py/` 是它经 `tools/gd_to_py.py` 机械转写出的 Python 版本。本模块是**适配层**：
把模拟器的输入（`lineups/*.json` 形状的阵容 dict）编译成内核装配指令，跑完一局，
再把内核的状态翻译回模拟器既有的对外接口（`summary()` / `result_json()` / `log`）。

为什么是适配层而不是重新实现
============================
装配次序本身就是**战斗语义的一部分**，不能重新发明：

    combat.setup() → 注网格元数据 → _readyInit() → inventory.addItem() → setGem()×n
    → combat.startBattle()

★ 物品必须在 `combat.setup()` **之后**才装：`_readyInit` 里 `newItemTimer` 等依赖
  `ctx.combat` 已就位；写反了会静默丢掉首轮计时。
★ 描述符必须**全局唯一**（模块级 `_DESCR_CACHE`）：`Item.isA` 靠引用相等判定，
  `countAllPlacedOfType` 把描述符当字典键。每局 new 一份会让同名物品在后一场覆盖
  注册表，前一场那件的 `isA` 立刻判假。
★ `_readyInit()` 先于 `addItem`、`setGem` 又晚于 `addItem` —— 三者次序都取自原版的
  节点生命周期，不是随手排的。

这套次序已在 `gd_core_test/LineupBattle.gd`（Godot 侧）与 `tools/run_gd_py.py`
（Python 侧）各实现一遍并逐字符对齐过 56 局。本模块是同一套装配的第三个调用点，
因此 `tools/check_gd_core_engine.py` 会拿同一批 56 局基准再比对一次 ——
否则「引擎能用」就等于「引擎跑的是那份被验证过的逻辑」，这种说法不可证伪。

数据来源
========
只读 `assets/gd_core_runtime.json`（由 `tools/gen_gd_core_data.py` 在构建期生成）。
刻意不读 `extracted/Items/*.tscn`、`gd_core_items/*.gd`、`gd_core/CoreConst.gd` ——
那三处在打包后的 exe 里不该跟着发布，且逐次解析会拖慢启动。

已知边界（不掩盖）
==================
· 只支持有转译脚本的物品。`assets/gd_core_runtime.json` 的 `unplayable` 列了哪些物品
  装不了（当前实测见该文件的 `counts`）；阵容用到它们会在装配时报错，而不是
  「装上但什么都不做」这种零报错的静默失效。
· 袋子（bag）的 `contents`（袋内嵌套物品）在本适配层不递归装配 —— 与
  `tools/gen_lineup_fixture.py` 的口径一致；两处要改就一起改。
· 表现层调用（`ctx.hooks.*`）全部保留为空实现；唯一被覆写的是 `logEvent`
  （事件留痕）。覆写它不改变判定：`CoreHooks` 的每个钩子都是 `-> void`、
  函数体 `pass`、**不在任何 if 条件里**（已静态核验）。
"""
from __future__ import annotations

import json
import math
import os
import random
import sys
from typing import Any, Dict, List, Optional

# ── 路径：开发态 = 仓库根；冻结态 = PyInstaller 的 _MEIPASS ──
if getattr(sys, "frozen", False):
    _BASE = getattr(sys, "_MEIPASS", os.path.dirname(os.path.abspath(sys.executable)))
else:
    _BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

_DATA_NAME = os.path.join("assets", "gd_core_runtime.json")

# gd_core_py 是顶层包；开发态仓库根在 sys.path 上，冻结态 _MEIPASS 在 sys.path 上。
if _BASE not in sys.path:
    sys.path.insert(0, _BASE)

MAX_TICKS = 20000          # 无头保护上限（与 gd_core_test/LineupBattle.gd 同值）

# 栈类型的展示名（与 engine/buff.py 的 BuffType.NAMES 逐字一致 —— GUI 的 buff
# 快照列直接消费它）
STACK_NAMES = {
    100: "block", 101: "lucky", 102: "regen", 103: "vampirism", 104: "spikes",
    105: "mana", 106: "empower", 107: "heat", 108: "poison", 109: "blind",
    110: "cold",
}

# CoreConst.EventType 名 → 模拟器事件类型（`engine/log_text.py` 的口径）。
# None = 该类型在原版日志里没有对应行（落在 _SUPPRESSED 语义里）。
_EVENT_TYPE_MAP = {
    "Activation": "item_activate",
    "DealDamage": "attack",
    "CriticalDamage": "critical",
    "MissedAttack": "missed",
    "TakeDamage": "attack",
    "LoseHealth": "lose_health",
    "AttackSpeed": None,
    "InvulnerableStart": "invulnerable_start",
    "InvulnerableEnd": "invulnerable_end",
    "Stun": "stun",
    "StunResisted": "stun_resisted",
    "CriticalResisted": "crit_resisted",
    "Health": "heal",
    "Stamina": "stamina_gain",
    "DrainStamina": "stamina_drain",
    "OutofStamina": "out_of_stamina",
    "DamageBuff": "damage_buff",
    "DamReduction": "dam_reduction",
    "DamIncrease": "dam_increase",
    "TemporaryMaxHealth": "temporary_max_health",
    "TemporaryMaxStamina": "temporary_max_stamina",
    "BattleRageStart": "battle_rage_start",
    "BattleRageEnd": "battle_rage_end",
    "Reincarnate": "reincarnate",
    "CooldownAdvance": None,
    "Unhealing": "unhealing",
    "Fatigue": "fatigue_damage",
    "Win": "combat_end",
    "Loss": "combat_end",
}


# ═══════════════════════════ 运行时数据（进程内单例） ═══════════════════════════

_DATA: Optional[dict] = None


def runtime_data() -> dict:
    global _DATA
    if _DATA is None:
        path = os.path.join(_BASE, _DATA_NAME)
        if not os.path.exists(path):
            raise RuntimeError(
                "缺少 gd_core 运行时数据：%s\n"
                "请先跑 `python tools/gen_gd_core_data.py` 生成，再重新打包。" % path)
        with open(path, encoding="utf-8") as f:
            _DATA = json.load(f)
    return _DATA


# ═══════════════════════════ 内核装载（惰性，只做一次） ═══════════════════════════

_K: Optional[dict] = None


class KernelError(RuntimeError):
    pass


def kernel() -> dict:
    """导入并装载 gd_core_py，返回常用类的句柄表（进程内只做一次）。"""
    global _K
    if _K is not None:
        return _K

    from gd_core_py import _bootstrap, _registry as _R
    from gd_core_py._rt import Vector2

    failed = _bootstrap.load_all()
    if failed:
        raise KernelError("gd_core_py 模块导入失败 %d 个：%s"
                          % (len(failed), [f[0] for f in failed[:5]]))
    miss = _R.missing()
    if miss:
        raise KernelError("gd_core_py 类注册表出现占位符（导入拓扑序错）：%s"
                          % list(miss.items())[:3])

    const = _R.C("res://gd_core/CoreConst.gd")
    _K = {
        "_R": _R,
        "Vector2": Vector2,
        "CoreConst": const,
        "CoreHooks": _R.C("res://gd_core/CoreHooks.gd"),
        "CoreItem": _R.C("res://gd_core/CoreItem.gd"),
        "CoreItemData": _R.C("res://gd_core/CoreItemData.gd"),
        "CoreCharacter": _R.C("res://gd_core/CoreCharacter.gd"),
        "CoreCombat": _R.C("res://gd_core/CoreCombat.gd"),
        "CoreContext": _R.C("res://gd_core/CoreContext.gd"),
        # EventType 名 ↔ 值（现算，不写死数字）
        "ET_NAME": {int(v): k for k, v in const.EventType.items()},
    }
    return _K


# ═══════════════════════════ 事件桥 ═══════════════════════════

class _OriginRef:
    """日志渲染只读 `.key`（`engine/log_text.py::_render_event`）。非物品实例。

    ★ gem_host/gem_slot（受控神谕对齐路径附加字段，docs/oracle_workflow.md Phase 3）：
      origin 为镶嵌宝石时记录宿主物品标识与槽位号，供工具层把内核事件序列化成
      神谕 events.json 的 `{"kind":"gem","host":…,"socket_index":…}` 形状
      （oracle_fight.gd::_jsonable 同构）。渲染层只读 `.key`（宝石自身标识），
      故对 `engine/log_text.py` 的输出零影响。普通物品/数字 origin 两字段恒 None。
    ★ damage_source（对齐路径附加字段）：origin 为数字伤害源（DamageSource.Type，
      经 typeToKeyword 化的 keyword）时置 True——神谕 dump 里这类 origin 是裸数字，
      物品/宝石是 dict，工具层据此还原形状。"""
    __slots__ = ("key", "gem_host", "gem_slot", "damage_source")

    def __init__(self, key: str, gem_host: Optional[str] = None,
                 gem_slot: Optional[int] = None, damage_source: bool = False):
        self.key = key
        self.gem_host = gem_host
        self.gem_slot = gem_slot
        self.damage_source = damage_source

    def __repr__(self):
        return "<%s>" % self.key


class _EventOut:
    """`engine/events.py::Event` 的等价视图（字段一致，但不 import engine）。"""
    __slots__ = ("t", "type", "actor", "target", "origin", "params",
                 "parent", "depth", "buff_type", "id")

    def __init__(self, t, etype, actor, target, origin, params, parent, depth,
                 buff_type, eid):
        self.t = t
        self.type = etype
        self.actor = actor
        self.target = target
        self.origin = origin
        self.params = params
        self.parent = parent
        self.depth = depth
        self.buff_type = buff_type
        self.id = eid


def _json_safe(v, depth=0):
    """事件参数落到 JSON 前的净化（内核参数理论上都是标量，这里只做兜底）。"""
    if v is None or isinstance(v, (bool, int, str)):
        return v
    if isinstance(v, float):
        return v if math.isfinite(v) else 0.0
    if depth >= 3:
        return str(v)
    if isinstance(v, dict):
        return {str(k): _json_safe(x, depth + 1) for k, x in v.items()}
    if isinstance(v, (list, tuple)):
        return [_json_safe(x, depth + 1) for x in v]
    return str(v)


def _new_stats():
    return {"damage_dealt": 0.0, "healing_done": 0.0, "crits": 0, "misses": 0,
            "out_of_stamina": 0, "activations": 0,
            "n_damage_events": 0, "n_heal_events": 0}


class _LogMixin:
    """事件桥 mixin。

    实现方式：覆写 `CoreHooks.logEvent(event)` —— 这是内核**唯一**的事件出口
    （`CoreCombatLog.logEvent` → `ctx.hooks.logEvent`；`CoreEventBus.emitAndLog`
    亦同），故一份覆写就拿到全部事件，且不触碰任何判定路径。

    ★ 为什么是 mixin + 动态派生（见 `_make_probe_class`）而不是静态子类：
      基类 `CoreHooks` 是转写产物、**运行时**才能从注册表取到。写成
      `class Probe(CoreHooks)` 就要在本模块 import 期把内核版本写死进来。
    ★ 必须是 MRO 里的**第一个**基类：`CoreHooks` 也定义了 `logEvent`（空实现），
      排在它后面覆写会失效，且失效是静默的（日志全空、判定全对）。
    """

    _ET_NAME: Dict[int, str] = {}
    ctx = None

    def _init_fields(self):
        super()._init_fields()
        self.events: List[_EventOut] = []
        self.warnings: List[str] = []
        self.stats = {0: _new_stats(), 1: _new_stats()}

    # ── 工具 ──

    @staticmethod
    def _side(player_id):
        if player_id is None:
            return None
        try:
            pid = int(player_id)
        except (TypeError, ValueError):
            return None
        return "player" if pid == 0 else "opponent"

    @staticmethod
    def _origin_key(origin):
        k = kernel()
        if isinstance(origin, k["CoreItem"]):
            try:
                ident = str(origin.descriptor.identifier)
            except Exception:  # noqa: BLE001 —— 只为日志，不因取名失败而中断
                return str(origin.getName())
            # 宝石 origin：附宿主/槽位（_OriginRef 新字段；渲染仍只读 .key）
            try:
                is_gem = bool(origin.isGem())
            except Exception:  # noqa: BLE001
                is_gem = False
            if is_gem:
                host = getattr(origin, "socket", None)
                host_key = None
                slot = None
                if host is not None:
                    try:
                        host_key = str(host.descriptor.identifier)
                    except Exception:  # noqa: BLE001
                        host_key = None
                    try:
                        for i, g in enumerate(list(host.gems)):
                            if g is origin:
                                slot = i
                                break
                    except Exception:  # noqa: BLE001
                        slot = None
                return _OriginRef(ident, host_key, slot)
            return _OriginRef(ident)
        # 数字 origin = DamageSource.Type（原版 CombatEvent.asText：
        # `origin is Item` 为假时走 Game.typeToKeyword(origin)）。
        # typeToKeyword 1:1：特例 Block→"bl"、Regeneration→"regen"，
        # 其余 eventTypeKeys[_type].to_lower()（此处经 ET_NAME 反查现算，
        # 不写死数字——见 decompiled_full/Core/Game.gd:5663）。
        # 实际出现的值：Fatigue=99（takeFatigueDamage → fatigueDamageSource）。
        try:
            num = int(origin)
        except (TypeError, ValueError):
            return None
        # ★ 用 kernel()["ET_NAME"]（单例现算），不要读 _LogMixin._ET_NAME ——
        #   那是基类空 dict；真实的 {值: 名} 表注入在动态派生的探针类上。
        name = kernel()["ET_NAME"].get(num)
        if not name:
            return None
        if num == k["CoreConst"].EventType.get("Block"):
            return _OriginRef("bl", damage_source=True)
        if num == k["CoreConst"].EventType.get("Regeneration"):
            return _OriginRef("regen", damage_source=True)
        return _OriginRef(name.lower(), damage_source=True)

    def _actor_of(self, event):
        """actor = 事件来源物品的所属角色；无物品来源时回落 getMainActor()。"""
        k = kernel()
        origin = event.origin
        if isinstance(origin, k["CoreItem"]):
            ch = origin.character()
            if ch is not None:
                return self._side(ch.playerId)
        try:
            return self._side(event.getMainActor())
        except Exception:  # noqa: BLE001
            return None

    # ── 钩子覆写 ──

    def logEvent(self, event):
        if event is None:
            return None
        et = int(event.type) if event.type is not None else -1
        name = self._ET_NAME.get(et, "")
        params = event.params or {}

        # 栈事件（Block..Cold = 100..110）：原版按「正=获得 / 负=失去」分派，
        # 见 CoreBuff.gd changeCurrentLogShowLabel（- change）与 gainStacks（+ amount）
        if 100 <= et <= 110:
            amount = params.get("amount", 0) or 0
            if params.get("timeout"):
                etype = "stack_timeout"
            elif isinstance(amount, (int, float)) and amount < 0:
                etype = "stack_lose"
            else:
                etype = "stack_gain"
            buff_type = et
        else:
            etype = _EVENT_TYPE_MAP.get(name)
            buff_type = None

        actor = self._actor_of(event)
        self._count(name, actor, params)

        if etype is None:
            return None          # 原版日志里没有这一行

        # 栈增益的「对自身施加」变体（原版 asText：getMainActor() == target
        # → GAIN_DEBUFF_SELF）：施加方与受方同侧即为 self（如剧毒矛自毒）。
        if etype == "stack_gain" and 100 <= et <= 110:
            tgt = self._side(event.target)
            if actor is not None and tgt == actor:
                params = dict(params)
                params["actor_is_target"] = True

        okey = self._origin_key(event.origin)
        if okey is None:
            oref = None
        elif isinstance(okey, _OriginRef):
            oref = okey
        else:
            oref = _OriginRef(okey)
        self.events.append(_EventOut(
            t=float(event.timestamp or 0.0),
            etype=etype,
            actor=actor,
            target=self._side(event.target),
            origin=oref,
            params={str(kk): _json_safe(vv) for kk, vv in params.items()},
            parent=(getattr(event.parentEvent, "id", None)
                    if event.parentEvent is not None else None),
            depth=int(event.getDepth()),
            buff_type=buff_type,
            eid=int(event.id),
        ))
        return None

    def _count(self, name, actor, params):
        side = 0 if actor == "player" else (1 if actor == "opponent" else None)
        if side is None:
            return
        st = self.stats[side]
        if name == "Activation":
            st["activations"] += 1
        elif name in ("DealDamage", "CriticalDamage"):
            st["damage_dealt"] += float(params.get("damage", 0) or 0)
            st["n_damage_events"] += 1
            if name == "CriticalDamage":
                st["crits"] += 1
        elif name == "MissedAttack":
            st["misses"] += 1
        elif name == "Health":
            st["healing_done"] += float(params.get("amount", 0) or 0)
            st["n_heal_events"] += 1
        elif name == "OutofStamina":
            st["out_of_stamina"] += 1

    # ── 收尾（合成原版的 Win/Loss 行） ──

    def emit_combat_end(self, t: float, winner: str, reason: str):
        self.events.append(_EventOut(
            t=float(t), etype="combat_end", actor=None, target=None, origin=None,
            params={"winner": winner, "reason": reason}, parent=None, depth=0,
            buff_type=None, eid=-1))

    # ── 对外视图（对齐 `engine/events.py::CombatLog`） ──

    def to_dict(self):
        return [{"t": e.t, "type": e.type, "actor": e.actor, "target": e.target,
                 "params": dict(e.params)} for e in self.events]

    def to_text(self, lang: Optional[str] = None):
        from engine.log_text import render_log
        return render_log(self.events, lang or "zh")


def _make_probe_class(hooks_base, et_name, extra=()):
    """动态派生探针类。

    ★ 基类顺序：`extra…` → `_LogMixin` → `hooks_base`。两者的位置都不能换：
      · `_LogMixin` 必须在 `hooks_base` **之前** —— `CoreHooks` 也定义了 `logEvent`
        （空实现），排在后面覆写会失效，而且是**静默**失效（日志全空、判定全对）。
      · `extra` 在最前 —— 供取证工具叠加上与 Godot 侧同名同口径的计数钩子
        （见 tools/check_gd_core_engine.py），生产路径不付这份开销。
    """
    return type("GDCoreHooks", tuple(extra) + (_LogMixin, hooks_base),
                {"_ET_NAME": et_name,
                 "resource_path": "gd_core:engine_probe"})


# ═══════════════════════════ 角色 / 物品视图 ═══════════════════════════

class _CharacterView:
    """把 CoreCharacter 包成 `engine/character.py` 的对外读面。"""

    def __init__(self, ch, name: str, stats: dict):
        self._ch = ch
        self._name = name
        self._stats = stats

    def display_name(self) -> str:
        return self._name

    def get_max_health(self) -> float:
        return float(self._ch.getMaxHealth())

    def get_current_health(self) -> float:
        return float(self._ch.getCurrentHealth())

    def get_max_stamina(self) -> float:
        return float(self._ch.getMaxStamina())

    def get_current_stamina(self) -> float:
        return float(self._ch.getCurrentStamina())

    @property
    def is_dead(self) -> bool:
        return bool(self._ch.isDead)

    @property
    def stats(self) -> dict:
        return dict(self._stats)

    def get_buff_snapshot(self) -> dict:
        out = {}
        for t, nm in STACK_NAMES.items():
            v = self._ch.getStacks(t)
            if v:
                out[nm] = int(v)
        return out


class _ItemView:
    """物品读面：模拟器侧只用到 `.key`（与 `Item.getName()`）。"""

    def __init__(self, item):
        self._item = item
        self.key = str(item.descriptor.identifier)
        self.name = self.key
        self.rarity = int(item.descriptor.rarity)

    def __repr__(self):
        return "<gd_item %s>" % self.key


# ═══════════════════════════ 角色属性（权威公式的镜像，见下方说明） ═══════════════════════════

def character_stats(lineup: dict, char_db: dict) -> dict:
    """★★ 本函数是 `tools/gen_lineup_fixture.py::character_stats` 的**镜像**。

    引擎侧不能 import tools/（打包后不可用），故刻意复制一份。两处一致性由
    `tools/gen_gd_core_data.py::verify_character_stats` 在构建期用 21 个探针逐值
    对拍 —— 公式漂移会在生成资产时直接失败，而不是在 exe 里安静算错血量。
    """
    character = lineup.get("character") or "Adventurer"
    mods = lineup.get("class_modifiers") or {}
    db_char = char_db.get(character, {})
    base_health = float(mods.get("health", db_char.get("health", 25.0)))
    stamina = float(mods.get("stamina", db_char.get("stamina", 5.0)))
    regen = float(mods.get("stamina_regen", db_char.get("regen", 1.0)))
    override = lineup.get("health_override")
    if override is not None:
        health = float(override)
    else:
        health = base_health
        for i in range(2, int(lineup.get("round") or 1) + 1):
            if i >= 15:
                health += 30
            elif i >= 10:
                health += 20
            elif i >= 5:
                health += 15
            else:
                health += 10
    return {"health": health, "stamina": stamina, "regen": regen}


def class_id_of(lineup: dict, classes: dict) -> int:
    """职业名 → 枚举值。``classes`` 来自运行时资产（CoreConst.Classes_Full 的拷贝）。"""
    name = lineup.get("character") or "Adventurer"
    for k, v in classes.items():
        if k.lower() == str(name).lower():
            return int(v)
    raise _MissingItem("未知职业 %s（请检查 CoreConst.Classes / Classes_Full）" % name)


# ═══════════════════════════ 装配 ═══════════════════════════

class _MissingItem(Exception):
    pass


def _key_of(x):
    return (x.get("id") or x.get("key")) if isinstance(x, dict) else x


def _place_of(data: dict, key: str, row: int, col: int, rot: int) -> dict:
    """锚点系几何 → 实际摆位（坐标约定见 `tools/gen_gd_core_data.py` 文件头）。

    ★ `occupied` 必须由**未平移的**锚点系 collision 再算一次，不能在已平移的
      `collision` 上再加 row/col —— 那样是平移两次，第 n 列落成第 2n 列，物品
      间距被整体拉大（相邻联动判定随之全错），而且只错一格以上的摆位、错得很安静。
      参考实现：`tools/gen_lineup_fixture.py::placement_of`（`rotated` 是锚点系原序）。
    """
    ent = data["items"].get(key)
    if ent is None:
        raise _MissingItem("物品 %s 不在可装配清单里（无转译脚本）" % key)
    r = ent["rot"][str(int(rot) % 360)]
    anchor = r["collision"]                     # 锚点系，min 已归一化到 (0,0)
    collision = [[c[0] + col, c[1] + row] for c in anchor]
    affected = {int(color): [[c[0] + col, c[1] + row] for c in cells]
                for color, cells in r["affected"].items()}
    # ★ occupied 必须与 collision/affected 同一坐标系（Vector2(x=col, y=row)，
    #   见 tools/gen_gd_core_data.py 文件头）。此前写成 (c[1]+row, c[0]+col)
    #   （行、列互换）→ filledCells 的键与 affected 查询格错位，1×1 物品
    #   的邻接联动（getAffectedItems）恒空且零报错——Magic Ring/Mana Orb/
    #   Amulet of Darkness 等受影响格联动全部静默失效。
    occupied = sorted({(c[0] + col, c[1] + row) for c in anchor})
    return {"occupied": occupied, "collision": collision, "affected": affected,
            "script": ent["script"], "sockets": int(ent["sockets"]),
            "descr": ent["descr"]}


# ★ 模块级 = 原版脚本级 var，跨对局复用。见文件头「描述符必须全局唯一」。
_DESCR_CACHE: Dict[str, Any] = {}


# ═══════════════════════════ 引擎 ═══════════════════════════

class GDCoreEngine:
    """对齐 `engine/combat.py::CombatEngine` 的构造 / run / summary / result_json 面。"""

    def __init__(self, player_lineup: Dict[str, Any],
                 opponent_lineup: Dict[str, Any],
                 item_db: Optional[Dict[str, Dict]] = None,
                 character_db: Optional[Dict[str, Dict]] = None,
                 seed: Optional[int] = None,
                 max_time: float = 90.0,
                 probe_bases=(),
                 below_master: bool = False,
                 p_activation_order: Optional[List[int]] = None,
                 o_activation_order: Optional[List[int]] = None,
                 reseed_after_player_character: bool = False,
                 post_seed_draws: int = 0,
                 rng_state: Optional[int] = None,
                 label_rng_enabled: Optional[bool] = None,
                 warm_latch: bool = False,
                 perm_stack_override: Optional[Dict[int, int]] = None,
                 r5_dual_exec: Optional[Dict[str, int]] = None,
                 p_gem_lens: Optional[List[int]] = None,
                 o_gem_lens: Optional[List[int]] = None,
                 _r5_warm: bool = False,
                 _r5_warm_gate: int = 25000,
                 formal_ev_gate: int = 25000):
        # ★ np21-R5 双执行拓扑（py 腿镜像，真源 = gd_core_test/OracleAlignBattle.gd
        #   R5_DUAL_EXEC 表 + 注入段，逐点同步；机理与语料证据链见该处注释）：
        #   r5_dual_exec={"warm_event_gate": 25000} 时，正式装配前先用同 case
        #   同 seed 构造并跑完一个**干净第 1 次执行**（暖场）——独立 ctx、无
        #   rng_state 注入、无任何宿主补偿、截于事件闸不清理——随后按录制进程
        #   的残留拓扑回灌正式场：
        #     ① permanentStacks（teardown 的 cleanse 不清永久栈，np18-C 语义）；
        #     ② EventBus 存活连接嫁接（发射体=暖场玩家 && 接收体=玩家侧物品，
        #       暖场时序挂正式 bus、陈旧先于新鲜；接收体 ctx/character_ 与
        #       damageSource/chanceRng/damageRangeRng 抽源改指正式侧）；
        #     ③ fatigueCounter 第四残留（CombatTimer 跨执行共享节点，只在
        #       combatEnd 复位；暖场>17s 已疲劳且截断不复位 ⇒ 正式场
        #       hasFatigueStarted 自 t=0 即真；值不敏感——t=14 startFatigue
        #       照常复位 0）。
        #   _r5_warm/_r5_warm_gate 为内部递归参数（暖场实例专用），外部不传。
        self._r5_journal: List[tuple] = []
        self._r5_fatigue = 0
        self._r5_warm_pkg = None
        if r5_dual_exec and not _r5_warm:
            warm = GDCoreEngine(
                player_lineup, opponent_lineup, item_db, character_db,
                seed=seed, max_time=max_time, probe_bases=probe_bases,
                below_master=below_master,
                p_activation_order=p_activation_order,
                o_activation_order=o_activation_order,
                reseed_after_player_character=reseed_after_player_character,
                post_seed_draws=post_seed_draws,
                label_rng_enabled=label_rng_enabled,
                p_gem_lens=p_gem_lens,
                o_gem_lens=o_gem_lens,
                _r5_warm=True,
                _r5_warm_gate=int(r5_dual_exec.get("warm_event_gate", 25000)))
            warm.run()
            self._r5_warm_pkg = warm
        self._r5_warm_flag = _r5_warm
        self._r5_warm_gate = int(_r5_warm_gate)
        # ★ np22 重录场正式腿事件闸对位（真源 = gd_core_test/OracleAlignBattle.gd
        #   NP22_REC_EV_GATE 表 + tools/verify_oracle.py PY_NP22_REC_EV_GATE）：
        #   三场新语料以 ORACLE_NOLIMIT=1（事件闸 200000）全长录制，正式腿
        #   必须同闸对位，否则在 M12=25000 截断 → 伪长度分歧。其余场缺省
        #   25000 零变化。
        self._formal_ev_gate = int(formal_ev_gate)
        # ★ seed 的语义：内核的随机源是 `CoreRng(seed)`，**不是** Python 的
        #   `random.Random(None)` —— 后者不给种子会按 OS 熵随机化，前者拿到 None
        #   会被折成 0。若这里直接把 None 传下去，「不指定种子跑 100 场」会变成
        #   同一场重复 100 次，胜率恒为 100% 或 0%，且**一行错都不报**。
        #   故这里显式抽一个真随机种子，并把它写进 self.seed 以便复现
        #   （`save_outputs` 会拿它进文件名，用户能照着复跑同一场）。
        if seed is None:
            seed = random.SystemRandom().randrange(1, 2 ** 31)
        self.seed = seed
        self._seed = seed
        self.max_time = float(max_time)
        # 物品数据由运行时资产自带，item_db 仅用于接口签名对齐（见文件头）
        self.item_db = item_db or {}
        k = kernel()
        data = runtime_data()
        self._data = data
        self._K = k
        self.warnings: List[str] = []

        # ── 角色属性 ──
        self._chars = data.get("characters") or character_db or {}
        ps = character_stats(player_lineup, self._chars)
        os_ = character_stats(opponent_lineup, self._chars)
        self._ps, self._os = ps, os_
        cls_p = class_id_of(player_lineup, data.get("classes") or {})
        cls_o = class_id_of(opponent_lineup, data.get("classes") or {})

        # ── 装配 ──
        probe_cls = _make_probe_class(k["CoreHooks"], k["ET_NAME"], probe_bases)
        self.hooks = probe_cls()
        self.log = self.hooks                     # 事件视图即日志视图
        ctx = k["CoreContext"](int(seed), self.hooks)
        # np21-R5：暖场实例打开连接台账（键控默认关，正式/非键控路径零扰动）
        if _r5_warm:
            ctx.bus.connect_journal_enabled = True
        # ★ 标签视觉抽开关（round19，与 gd 侧 OracleAlignBattle 同步）
        if label_rng_enabled is not None:
            ctx.label_rng_enabled = bool(label_rng_enabled)
        self.ctx = ctx
        self.hooks.ctx = ctx
        # 对齐 Game.isBelowLeague(Master)（Character.gd:304 / Item.gd:3791 消费）。
        # np24 终谳（探针 rng_log，三场 events≡语料）：录制时该条件为真——冷却批
        # = 玩家侧 (0.95,1.05) + 对手侧 (0.975,1.05)、±0.2 命中/暴击偏置在位。
        # 族A「对手全 +1 tick」根源在对手速度面（gd 1.06 v oracle ~1.07），非映射。
        # 默认 False；神谕对齐驱动（tools/verify_oracle.py）显式传 True。
        ctx.below_master = bool(below_master)
        # ★ np24：deferred 冲刷关闭（与 gd 宿主 OracleAlignBattle.gd 同位；录制
        #   [M11]：阻塞循环无帧，战斗内 call_deferred 永不执行——Deck of Cards
        #   卡链零启动实证）。py 腿此前靠装配期缓存陈旧而偶然一致（deck cards=0）。
        ctx.deferred_flush_enabled = False
        # ★ np24：EngineerBox 接力死亡镜像（与 gd 宿主 OracleAlignBattle.gd 同位；
        #   录制侧 EB ChargeTimer 首弹 1 次/侧、队列不推进，接力重发射=0）。
        ctx.eb_relay_mirrored = True
        p = self._make_character(ctx, k["CoreCharacter"].ID.PLAYER, ps, cls_p,
                                 player_lineup.get("base_max_stamina"))
        # ★ np21-R5 残留①（permanentStacks 收割灌入，gd 宿主 [r5-warm] 块同位）：
        #   暖场玩家终局永久栈（teardown 的 cleanse 不清）——纯字段写、零 rng。
        if self._r5_warm_pkg is not None:
            _wp = self._r5_warm_pkg._p
            for _bt, _wbuf in _wp.buffs.items():
                if _bt in p.buffs:
                    p.buffs[_bt].permanentStacks = int(_wbuf.permanentStacks)
        # ★ np21-① 宿主补偿镜像（与 gd_core_test/OracleAlignBattle.gd:497-514 逐点同步）：
        #   录制工件受控补偿，非内核语义——仅神谕对齐驱动按键控表传入，默认关闭
        #   （既有路径 python -m simulator.simulate / 56 局基准零变化）。
        #   注入点 = 玩家角色构造后、播种（reseed）前：纯字段写、零 rng 消耗
        #   （gd 侧同位，角色构造链消耗随后被 seed 抹除）。
        #   · perm_stack_override（np18-C 收割注入 + np20-C canonical 校正的净面）：
        #     跨执行 permanentStacks 残留（oracle Buff.reset 不清 permanentStacks，
        #     语料=录制管线第 3 次执行，携带前执行永久栈）；
        #   · warm_latch（np17-B）：暖场 watchdog 截断不走 endCombat ⇒ PLAYER
        #     attack_moving_forward 暖场置真后永不复位 ⇒ 正式场首次武器攻跳本体 5 抽。
        if perm_stack_override:
            for _bt, _stk in perm_stack_override.items():
                if _bt in p.buffs:
                    p.buffs[_bt].permanentStacks = int(_stk)
        if warm_latch:
            p.attack_moving_forward = True
        # ★ 神谕装配期链约定（docs/oracle_workflow.md Phase 3；与
        #   gd_core_test/OracleAlignBattle.gd 同步）：神谕复用 PLAYER（角色构造
        #   消耗在本场播种前，被 seed 抹除），随后任何物品实例创建之前
        #   Util.rng.seed = S（oracle_fight.gd:554），对手角色在播种后实例化。
        #   reseed_after_player_character=True 时照此重播种；
        #   post_seed_draws 兜底补装配期的额外链消耗——阶段2 已把装配期消耗面
        #   逻辑一致地还原进内核（Item 场景双绑定 4 步/实例 + FlickerAnimation
        #   入树 2 步，见 CoreItem.setup/_readyInit），神谕对齐路径恒传 0；
        #   旧的校准常数 14（ORACLE_SCENE_DRAWS）已删——它是单场误标定
        #   （917 场实测装配差 0..444 步，非常数）。两者默认关闭 = 既有行为。
        if reseed_after_player_character:
            ctx.rng.rng.seed = int(self._seed)
            for _ in range(int(post_seed_draws)):
                ctx.rng.rng.randi()

        # 局外回合数：LevelUp.onPrepare 读 ctx.cur_round（对齐原版 Game.curRound）
        try:
            ctx.cur_round = int(player_lineup.get("round") or 0)
        except Exception:  # noqa: BLE001
            pass

        combat = k["CoreCombat"](ctx)
        combat.max_time = self.max_time
        # ★ 阶段3 装配次序（r17 批2 通道 A，与 gd_core_test/OracleAlignBattle.gd
        #   同步落地）：神谕播种后的装配次序 =
        #   「玩家物品 → 对手角色 4 抽 BalancedRng（Character.gd:94-97）→ 对手物品」
        #   （oracle_fight.gd:567-597 实证；run818_r5 raw 级对位定谳——神谕
        #   rng_log_first.txt raw16/19/22/39 == gd 平移前同构位的 +4）。此前两侧
        #   都把对手角色的 4 抽（_make_character→CoreCharacter.__init__ 的
        #   4×BalancedRng）插在玩家物品之前，玩家侧每笔装配抽取（ctor+ready）
        #   整体 +4 插位 → 窗口内 ctor/ready 抽互换 raw → BalancedRng
        #   expectedWins ctor 值差 → 战斗期值差族（run628_r14 idx37 O8/G11 纯
        #   值差、run818_r5 idx70 dmg 16vs17）。r14「ready 抽未内联」误诊纠正：
        #   两侧逐物品本就是 [2 ctor][ready] 紧邻结构，唯对手角色块错位——
        #   CoreItem._readyInit 段零改动。
        #   op6 不变量保持：ctx.player/ctx.combat 仍在玩家物品装配之前绑定
        #   （BagofStones.gd:13 装配期读 ctx.player.INVENTORY）；全工程装配期钩子
        #   （_readyInit/onAddToInventory/onItemAdded/getAffectedCellsAfterRotate*）
        #   零处读 ctx.opponent/ctx.combat（r17 批2 全量扫描），
        #   CoreItem.addToInventory 的 ownerType 判定对 ctx.opponent 判空。
        #   门控 = reseed_after_player_character（仅 tools/verify_oracle.py:281 的
        #   神谕对齐路径传 True）：既有路径（python -m simulator.simulate / 56 局
        #   基准）的装配序列保持逐字节不变。
        if reseed_after_player_character:
            ctx.player = p
            ctx.combat = combat
        else:
            o = self._make_character(ctx, k["CoreCharacter"].ID.OPPONENT, os_, cls_o,
                                     opponent_lineup.get("base_max_stamina"))
            self._p, self._o = p, o
            combat.setup(p, o)
            self.combat = combat

        # ★ 描述符预注册（2026-10-10 round 修复：isA 身份链占位符缺口，与
        #   gd_core_test/OracleAlignBattle.gd 同步）：CoreItemBook.getDescriptor
        #   对未注册名惰性造「零值占位实例」，_descriptor 的 register 随后用
        #   真实数据**换掉**表项——早于真实注册拿到占位引用的物品（Buy the
        #   Holy Light._readyInit 的 getDescriptor("Oil Lamp")，装配序在灯之前
        #   的场次）此后 isA 恒 false（引用相等），canAffect 全局灯面静默失效
        #   （run634_r18 玩家灯缺 +0.40 speed → 冷却恒慢 → 事件链漂移）。
        #   真游戏全物品共享同一份 .tres 资源，不存在「先占位后换实例」。
        #   放置任何物品（含宝石）前先把本场两侧全部真实描述符注册进
        #   item_book，占位窗口归零。纯数据面操作，零 rng 消耗。
        for _pre_lu in (player_lineup, opponent_lineup):
            for _pre_e in ((_pre_lu.get("backpack") or {}).get("items") or []):
                _pre_k = _pre_e.get("id") or _pre_e.get("key")
                if _pre_k:
                    self._descriptor(ctx, _pre_k)
                for _pre_g in (_pre_e.get("gems") or []):
                    _pre_gk = _key_of(_pre_g)
                    if _pre_gk:
                        self._descriptor(ctx, _pre_gk)

        owner = k["CoreConst"].Owner
        # ★ np24 簇A①：per-index 实例槽真值（= cases json 条目 gems 数组长度，
        #   含 null 空槽——v3 lineup 的 gems 在生成链丢了 null，长度不可用；
        #   由驱动 run_py 从 oracle_align_cases.json 逐条传入，与 v3 items
        #   按装配序 1:1 对齐）。None = 无真值（非神谕路径），回落夹具容量。
        self._p_gem_lens = p_gem_lens
        self._o_gem_lens = o_gem_lens
        self._p_items = self._build_side(ctx, p, player_lineup,
                                         owner.PlayerInventory, p_gem_lens)
        if reseed_after_player_character:
            # 对手角色 4 抽落神谕位：玩家物品之后、对手物品之前；
            # combat.setup 在此补完整接线（ctx.player/ctx.combat 重赋值幂等）
            o = self._make_character(ctx, k["CoreCharacter"].ID.OPPONENT, os_, cls_o,
                                     opponent_lineup.get("base_max_stamina"))
            self._p, self._o = p, o
            combat.setup(p, o)
            self.combat = combat
        self._o_items = self._build_side(ctx, o, opponent_lineup, owner.Opponent,
                                         o_gem_lens)
        # 物品要在 combat.setup() 之后装（既有路径由上方 else 分支保证；
        # 神谕路径 ctx.player/ctx.combat 先绑定，op6 语义不变）；startBattle 再兜住双方
        # ★ 激活顺序直通（受控神谕对齐路径）：原版开战前的 shuffle 走引擎全局链
        #   （docs/rng_truth.md §1.4-2），内核 ctx.rng.shuffle 是自研替身。对齐时
        #   宿主把「真 Godot 全局链 seed(S) → shuffle×2 → sort_TriggerPriority」
        #   算出的终序（下标表，指向各侧装配序数组）传进来，startBattle 以
        #   preordered=True 直通——不 shuffle、不排序、不消耗 ctx.rng。
        #   默认 None = 既有行为（内核内部 shuffle，56 局基准不变）。
        # ★ 阶段1 神谕 rng state 注入（docs/alignment_fix_workflow.md §2 阶段1）：
        #   神谕在「战斗装配完成后、开战序列（prepareItems/activateItems）与首次
        #   tick 之前」导出 Util.rng.state（oracle_fight.gd rng_state.txt）。此处
        #   在同样语义的边界——装配（双方角色+物品实例）完成、startBattle 的
        #   prepareItems/activateItems 与逐 tick 判定链之前——把该 state 原样灌进
        #   内核随机源（CoreContext.set_state → PCG state 直写，不前进不重播，
        #   docs/rng_truth.md §2.3），绕开装配期消耗差异，隔离战斗期判定链。
        #   机制前提：两侧都在 prepareItems 同点把全部 BalancedRng 重置归零
        #   （原版 Item.gd:3345-3351 / Character.gd:294-317；内核 CoreItem.gd:531 /
        #   CoreCharacter.gd:259），故链 state 唯一决定后续每次掷点。
        #   GDScript 落盘的是有符号 64 位视角的 u64，set_state 内部按 MASK64 归一。
        if rng_state is not None:
            ctx.set_state(int(rng_state))
        # ★ np21-R5 残留②（连接泄漏嫁接，gd 宿主 [r5-graft] 块同位）：把暖场
        #   bus 台账中「发射体=暖场玩家 && 接收体=玩家侧物品」的连接按暖场时序
        #   挂上正式 bus（发射体映射为正式玩家——oracle 里 PLAYER 节点跨执行
        #   复用）；此刻正式侧 onPrepare 连接尚未建立（startBattle→prepareItems
        #   才连）⇒ 追加即天然「陈旧先于新鲜」。陈旧接收体 ctx/character_ 改指
        #   正式侧；damageSource/chanceRng/damageRangeRng 抽源改指正式 ctx.rng
        #   （oracle：进程级共享 Util.rng ⇒ 陈旧处理器消耗正式链 rng）。
        #   BalancedRng 平衡态保留暖场值（正式 prepareItems 重置只遍历正式清单）。
        #   暖场自然终局时 oracle combatEndDeferred→disconnectAll 已清连接 ⇒ 不嫁接。
        if self._r5_warm_pkg is not None and not self._r5_warm_pkg.fight_ended:
            _wpk = self._r5_warm_pkg
            _wp, _wctx = _wpk._p, _wpk.ctx
            _owner_pv = int(k["CoreConst"].Owner.PlayerInventory)
            _stale = {}
            for entry in list(getattr(_wctx.bus, "connect_journal", [])):
                if entry[0] is not _wp or entry[2] is None:
                    continue
                if int(entry[2].ownerType) != _owner_pv:
                    continue
                ctx.bus.connectEvent(p, entry[1], entry[2], entry[3])
                _stale[id(entry[2])] = entry[2]
            for _rcv in _stale.values():
                _rcv.ctx = ctx
                _rcv.character_ = p
                if getattr(_rcv, "damageSource", None) is not None:
                    _rcv.damageSource._rng = ctx.rng
                if getattr(_rcv, "chanceRng", None) is not None:
                    _rcv.chanceRng._rng = ctx.rng
                if getattr(_rcv, "damageRangeRng", None) is not None:
                    _rcv.damageRangeRng._rng = ctx.rng
            # np21-R5 stale_used_stacks 键控覆盖（gd 宿主同位；封闭推导见
            # gd_core_test/OracleAlignBattle.gd R5_DUAL_EXEC 表注）——gd 干净
            # 暖场收官值 ≠ 语料录制批（旧树）收官值时按推导真值覆盖。
            _ov = (r5_dual_exec or {}).get("stale_used_stacks") or {}
            if _ov:
                for _rcv in _stale.values():
                    _id_ = str(getattr(getattr(_rcv, "descriptor", None), "identifier", ""))
                    if _id_ not in _ov:
                        continue
                    for _bt, _v in _ov[_id_].items():
                        if getattr(_rcv, "usedStacks", None) is not None and int(_bt) in _rcv.usedStacks:
                            _rcv.usedStacks[int(_bt)] = float(_v)
            # np21-R5 残留③（fatigueCounter，只在截断路径存活；值不敏感——
            # t=14 startFatigue 照常复位 0，仅经 hasFatigueStarted 面可观测）
            if _wctx.combat is not None:
                self._r5_fatigue = int(_wctx.combat.fatigue_counter)
        if p_activation_order is not None or o_activation_order is not None:
            if (p_activation_order is None or o_activation_order is None
                    or sorted(p_activation_order) != list(range(len(self._p_items)))
                    or sorted(o_activation_order) != list(range(len(self._o_items)))):
                raise ValueError("激活顺序下标表必须两侧同时给出且为满排列")
            combat.startBattle([self._p_items[i] for i in p_activation_order],
                               [self._o_items[i] for i in o_activation_order],
                               True)
        else:
            combat.startBattle(self._p_items, self._o_items)

        # ★ np21-R5 残留③注入（fatigueCounter，gd 宿主 startBattle 后同位）：
        #   startBattle 已清 counter、其后 activateItems 只清 flag 不清 counter，
        #   故注入后仅经 hasFatigueStarted()（=counter>0）面可观测；t=14
        #   startFatigue 照常复位。纯字段写，零 rng 消耗。
        if self._r5_fatigue > 0:
            combat.fatigue_counter = self._r5_fatigue

        # 对外视图
        self.player = _CharacterView(p, self._lineup_name(player_lineup),
                                     self.log.stats[0])
        self.opponent = _CharacterView(o, self._lineup_name(opponent_lineup),
                                       self.log.stats[1])
        self.player_items = [_ItemView(i) for i in self._p_items]
        self.opponent_items = [_ItemView(i) for i in self._o_items]
        self.fight_ended = False
        self.winner = None
        self.combat_time = 0.0
        self.fatigue_counter = 0
        self.timed_out = False
        self._ticks = 0

    # ── 装配 ──

    @staticmethod
    def _lineup_name(lineup: dict) -> str:
        return (str((lineup.get("meta") or {}).get("name") or "")
                or str(lineup.get("character") or "") or "未命名")

    def _make_character(self, ctx, pid, stats, cls_id, base_stamina=None):
        k = self._K
        c = k["CoreCharacter"](ctx, pid)
        c.characterClass = int(cls_id)
        c.setMaxHealth(int(stats["health"]))
        c.setCurrentHealth(int(stats["health"]))
        c.maxStamina = float(stats["stamina"])
        c.baseMaxStamina = float(stats["stamina"])
        # ★ base_max_stamina（受控神谕对齐路径附加键）：原版 maxStamina 与
        #   baseMaxStamina 是两个字段——神谕对手侧 initHistoryOpponent 显式
        #   baseMaxStamina=5 + recalculateMaxStamina（=5+Stamina Sack 数，可以
        #   大于 base），战斗内再触发 recalculate 时按 base 重算。此处允许阵容
        #   显式区分两者（默认仍 = stamina，既有行为不变）。
        if base_stamina is not None:
            c.baseMaxStamina = float(base_stamina)
        c.baseStaminaRegen = float(stats["regen"])
        c.staminaRegen = float(stats["regen"])
        c.fillUpStamina()
        return c

    def _descriptor(self, ctx, key):
        k = self._K
        made = _DESCR_CACHE.get(key)
        if made is None:
            d = self._data["items"][key]["descr"]
            made = k["CoreItemData"]().fromDict({
                "name": d["name"], "identifier": d["identifier"],
                "minDam": d["minDam"], "maxDam": d["maxDam"], "cd": d["cd"],
                "extraCds": d["extraCds"], "accuracy": d["accuracy"],
                "staminaCost": d["staminaCost"], "block": d["block"],
                "price": d["price"], "rarity": d["rarity"],
                "classes": d["classes"], "canActivate": d["canActivate"],
                "chance": d["chance"], "chance2": d["chance2"],
                "types": d["types"], "tags": d["tags"], "params": d["params"],
                "namedParams": d["namedParams"],
                # 配方图（tools/enrich_recipes.py）：战斗语义只消费非空性
                #（isCraftedItem → Cog/Anvil 的 canAffect）
                "originatingRecipes": d.get("originatingRecipes", []),
                # 攻击动画场景（enrich_animation_scene.py）：playAnimation 的闸。
                #   np24 终谳更正：神谕 ItemAnimation 4 抽走 Util.rng 直连（无日志），
                #   块照常消耗——内核 activate 以裸抽对位（见 gd_core/CoreItem.gd），
                #   数据面照夹具原值传递（与 gd 宿主 descriptor_of 同步）。
                "animationScene": bool(d.get("animationScene", False)),
                # FlickerAnimation 子节点（tools/enrich_flicker_animation.py，阶段2
                # 装配期对齐）：_ready 消耗 randf_range(minDist,maxDist) 2 步 +
                # 战斗期 playAni 消耗 randf_range(minSpeed,maxSpeed) 2 步
                #（Items/Animations/FlickerAnimation.gd:13-19；消费点见
                #  gd_core/CoreItem.gd 的 _readyInit / flickerPlayAni）
                "flickerAni": bool(d.get("flickerAni", False)),
                "flickerMinDist": float(d.get("flickerMinDist", 0.1)),
                "flickerMaxDist": float(d.get("flickerMaxDist", 3.0)),
                "flickerMinSpeed": float(d.get("flickerMinSpeed", 0.3)),
                "flickerMaxSpeed": float(d.get("flickerMaxSpeed", 1.0)),
                # 连接器/宝石 _ready 抽（同阶段2 装配期对齐，消费点 CoreItem._readyInit）
                "connectorReadyRoll": bool(d.get("connectorReadyRoll", False)),
                "gemRoll": bool(d.get("gemRoll", False)),
                # 随机 unique 池（tools/enrich_unique_pool.py）：isTreasure() 的唯一
                # 依据（Item.gd:5723-5724 ← ItemBook.gd:899-901）——Fedora 计 treasure
                "randomUniquePool": bool(d.get("randomUniquePool", False)),
                # gained/removed/usedStacks（round10；与 gd_core/CoreItemData.
                # fromDict:347-349 同名直传——Toad/PoisonFrog 阈值网络判定面）
                "gainedStacks": int(d.get("gainedStacks", 0)),
                "removedStacks": int(d.get("removedStacks", 0)),
                "usedStacks": int(d.get("usedStacks", 0)),
                # 战怒描述符（oracle rage_dump_tmp.gd）：isBattleRageItem 判定面
                "hasBattleRageEffect": bool(d.get("hasBattleRageEffect", False)),
                # 场景绑定深度（tools/enrich_scene_depth.py）：setup() chanceRng 次数
                "sceneDepth": int(d.get("sceneDepth", 2)),
            })
            _DESCR_CACHE[key] = made
        return ctx.item_book.register(made)

    def _make_item(self, ctx, chr_, key, script, sockets, collision, affected):
        k = self._K
        R = k["_R"]
        if not R.is_registered(script):
            raise _MissingItem("物品 %s 的脚本未转译：%s" % (key, script))
        vec = k["Vector2"]
        it = R.C(script)()
        it.setup(ctx, self._descriptor(ctx, key), chr_)
        # 插座数组按 socket 数建等长（原版 sockets = $Icon/Sockets.get_children()）
        for _i in range(int(sockets)):
            it.gems.append(None)
        it.collisionCells = [vec(int(c[0]), int(c[1])) for c in collision]
        it.affectedTileCells = {
            int(color): [vec(int(c[0]), int(c[1])) for c in cells]
            for color, cells in affected.items()}
        return it

    def _place(self, ctx, chr_, key, row, col, rot, owner_type, ready=True,
               sockets=None):
        k = self._K
        vec = k["Vector2"]
        pl = _place_of(self._data, key, row, col, rot)
        # np24 簇A①：sockets 显式传入时以传入值为准（= 神谕实例真值
        # len(lineup gems)，见 _build_side 注）；缺省回落夹具容量（宝石自身的
        # 槽——语料无嵌套宝石，零战斗面）。
        it = self._make_item(ctx, chr_, key, pl["script"],
                             pl["sockets"] if sockets is None else int(sockets),
                             pl["collision"], pl["affected"])
        it.occupiedCells = [vec(int(c[0]), int(c[1])) for c in pl["occupied"]]
        it.ownerType = owner_type
        # ★ 朝向（战斗判定输入，CoreConst.FaceDirection 0..3 = 顺时针 1/4 圈）：
        #   阵容条目的 rotation 是度数。此前内核恒 UP——电荷路径
        #   （Battery.chargeCells 等**本地格**常量，经 Item.getGlobalPointsForCells
        #   的节点旋转变换映射进背包）与 SpintoWin/LongSpear/RainbowPotion 的
        #   朝向分流全部按 0° 计算（受控神谕对齐路径 run1160_r18 实证）。
        it.faceDirection = (int(rot) // 90) % 4
        # 原版次序：物品入场景树时 _ready 先跑，随后 Inventory.addItem 才调 addToInventory
        if ready:
            it._readyInit()
        return it

    def _build_side(self, ctx, chr_, lineup, owner_type, gem_lens=None):
        out = []
        _gi = 0
        for sec in ("backpack", "storage"):
            if sec == "storage":
                continue          # 储物箱里的物品不参战（对齐原版：只装背包）
            s = lineup.get(sec) or {}
            for e in (s.get("items") or []):
                key = e.get("id") or e.get("key")
                if not key:
                    continue
                # np24 簇A①：优先用驱动传入的实例槽真值（cases json 条目 gems
                # 长度，null 空槽计入）；v3 gems 丢了 null 不能用其长度。
                _sock = None
                if gem_lens is not None and _gi < len(gem_lens):
                    _sock = int(gem_lens[_gi])
                _gi += 1
                it = self._place(ctx, chr_, key, int(e.get("row") or 0),
                                 int(e.get("col") or 0),
                                 int(e.get("rotation") or 0), owner_type,
                                 sockets=_sock)
                chr_.inventory.addItem(it, it.occupiedCells)
                # ★ r34 crafted 效果真值覆写（对齐重放元组覆写点）：_ready_init 的
                #   roll 照常消耗链位（与神谕重放同序），随后用史真值覆写（零 rng）。
                #   仅 MagicRing 族有此方法；effects 缺省/None 跳过。
                effs = e.get("effects")
                if effs and hasattr(it, "setCraftedEffects"):
                    it.setCraftedEffects(effs)
                # 宝石在宿主入包之后才 setGem
                for gi, g in enumerate(e.get("gems") or []):
                    gkey = _key_of(g)
                    if not gkey:
                        continue
                    gem = self._place(ctx, chr_, gkey, 0, 0, 0, owner_type)
                    it.setGem(gi, gem)
                out.append(it)
        return out

    # ── 运行 ──

    def run(self):
        d = self._K["CoreContext"].PHYSICS_DELTA
        ticks = 0
        # oracle M12 事件数闸对位（oracle_fight.gd:742-744：events>25000
        # 提前判停、status=timeout、已产生事件照常 dump、winner 不判胜）。
        # gd 宿主（OracleAlignBattle.gd）已补同款；py 引擎此前缺 →
        # length 簇 py 侧跑到自然终局，事件数/战报长度与 oracle 分歧。
        # np21-R5：暖场实例用表内 T_w 闸（=暖场截断点）；np22 重录三场正式腿
        # 用 formal_ev_gate 对位抬闸（录制工件对位）；其余场维持 M12 常数 25000。
        _gate = self._r5_warm_gate if self._r5_warm_flag else self._formal_ev_gate
        while not self.combat.fight_ended and ticks < MAX_TICKS:
            self.combat.physicsTick(d)
            ticks += 1
            if len(self.log.events) > _gate:
                break
        self._ticks = ticks
        self.fight_ended = bool(self.combat.fight_ended)
        self.combat_time = float(self.combat.combat_time)
        self.fatigue_counter = int(self.combat.fatigue_counter)
        self.timed_out = bool(self.combat.timed_out)
        self.winner = self.combat.winner()
        self.log.emit_combat_end(self.combat_time,
                                 "player" if self.player_wins() else "opponent",
                                 self.win_reason)
        return self

    def player_wins(self) -> bool:
        return bool(self.combat.playerWins())

    @property
    def win_reason(self) -> str:
        # 对齐 `engine/combat.py::_end_fight` 的取值域（'death' / 'timeout'）
        return "timeout" if self.timed_out else "death"

    # ── 输出面 ──

    def summary(self) -> Dict[str, Any]:
        return {
            "winner": "player" if self.player_wins() else "opponent",
            "reason": self.win_reason,
            "time": round(self.combat_time, 2),
            "fatigue_counter": self.fatigue_counter,
            "player": self._side_summary(self._p, self.player, 0),
            "opponent": self._side_summary(self._o, self.opponent, 1),
            "timeline": {"hp_history": []},
        }

    def _side_summary(self, ch, view, side):
        st = self.log.stats[side]
        return {
            "name": view.display_name(),
            "hp": round(view.get_current_health(), 1),
            "max_hp": round(view.get_max_health(), 1),
            "stamina": round(view.get_current_stamina(), 1),
            "dead": view.is_dead,
            "buffs": view.get_buff_snapshot(),
            "stats": {
                "damage_dealt": round(st["damage_dealt"], 1),
                "healing_done": round(st["healing_done"], 1),
                "crits": st["crits"],
                "misses": st["misses"],
                "out_of_stamina": st["out_of_stamina"],
                "activations": st["activations"],
            },
        }

    def result_json(self) -> Dict[str, Any]:
        s = self.summary()
        return {
            "version": 1,
            "engine": "gd_core",
            "meta": {
                "seed": self._seed,
                "fight_time": s["time"],
                "winner": s["winner"],
                "reason": s["reason"],
                "fatigue_counter": s["fatigue_counter"],
                "num_events": len(self.log.events),
                "ticks": self._ticks,
            },
            "player": s["player"],
            "opponent": s["opponent"],
            "timeline": s["timeline"],
        }

    # ── 取证面（工具消费；不参与战斗） ──

    def totals(self) -> dict:
        """双方合计的现场量（供 `tools/check_gd_core_engine.py` 与基准对照）。"""
        a, b = self.log.stats[0], self.log.stats[1]
        return {
            "activations": a["activations"] + b["activations"],
            "damage_events": a["n_damage_events"] + b["n_damage_events"],
            "damage_sum": a["damage_dealt"] + b["damage_dealt"],
            "heal_events": a["n_heal_events"] + b["n_heal_events"],
            "heal_sum": a["healing_done"] + b["healing_done"],
        }
