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
    """日志渲染只读 `.key`（`engine/log_text.py::_render_event`）。非物品实例。"""
    __slots__ = ("key",)

    def __init__(self, key: str):
        self.key = key

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
                return str(origin.descriptor.identifier)
            except Exception:  # noqa: BLE001 —— 只为日志，不因取名失败而中断
                return str(origin.getName())
        return None

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

        okey = self._origin_key(event.origin)
        self.events.append(_EventOut(
            t=float(event.timestamp or 0.0),
            etype=etype,
            actor=actor,
            target=self._side(event.target),
            origin=_OriginRef(okey) if okey else None,
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
    occupied = sorted({(c[1] + row, c[0] + col) for c in anchor})
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
                 probe_bases=()):
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
        self.ctx = ctx
        self.hooks.ctx = ctx
        p = self._make_character(ctx, k["CoreCharacter"].ID.PLAYER, ps, cls_p)
        o = self._make_character(ctx, k["CoreCharacter"].ID.OPPONENT, os_, cls_o)
        self._p, self._o = p, o

        # 局外回合数：LevelUp.onPrepare 读 ctx.cur_round（对齐原版 Game.curRound）
        try:
            ctx.cur_round = int(player_lineup.get("round") or 0)
        except Exception:  # noqa: BLE001
            pass

        combat = k["CoreCombat"](ctx)
        combat.max_time = self.max_time
        combat.setup(p, o)
        self.combat = combat

        owner = k["CoreConst"].Owner
        self._p_items = self._build_side(ctx, p, player_lineup,
                                         owner.PlayerInventory)
        self._o_items = self._build_side(ctx, o, opponent_lineup, owner.Opponent)
        # 物品要在 combat.setup() 之后装；startBattle 再兜住双方
        combat.startBattle(self._p_items, self._o_items)

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

    def _make_character(self, ctx, pid, stats, cls_id):
        k = self._K
        c = k["CoreCharacter"](ctx, pid)
        c.characterClass = int(cls_id)
        c.setMaxHealth(int(stats["health"]))
        c.setCurrentHealth(int(stats["health"]))
        c.maxStamina = float(stats["stamina"])
        c.baseMaxStamina = float(stats["stamina"])
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

    def _place(self, ctx, chr_, key, row, col, rot, owner_type, ready=True):
        k = self._K
        vec = k["Vector2"]
        pl = _place_of(self._data, key, row, col, rot)
        it = self._make_item(ctx, chr_, key, pl["script"], pl["sockets"],
                             pl["collision"], pl["affected"])
        it.occupiedCells = [vec(int(c[0]), int(c[1])) for c in pl["occupied"]]
        it.ownerType = owner_type
        # 原版次序：物品入场景树时 _ready 先跑，随后 Inventory.addItem 才调 addToInventory
        if ready:
            it._readyInit()
        return it

    def _build_side(self, ctx, chr_, lineup, owner_type):
        out = []
        for sec in ("backpack", "storage"):
            if sec == "storage":
                continue          # 储物箱里的物品不参战（对齐原版：只装背包）
            s = lineup.get(sec) or {}
            for e in (s.get("items") or []):
                key = e.get("id") or e.get("key")
                if not key:
                    continue
                it = self._place(ctx, chr_, key, int(e.get("row") or 0),
                                 int(e.get("col") or 0),
                                 int(e.get("rotation") or 0), owner_type)
                chr_.inventory.addItem(it, it.occupiedCells)
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
        while not self.combat.fight_ended and ticks < MAX_TICKS:
            self.combat.physicsTick(d)
            ticks += 1
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
