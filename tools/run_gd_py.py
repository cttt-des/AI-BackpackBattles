#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
run_gd_py.py — gd_core_py 端到端驱动器（Python 侧的 gd_core_test/LineupBattle.gd）

存在的理由
==========
`tools/gd_to_py.py` 把 `gd_core/` + `gd_core_items/`（521 文件 / 29311 行）机械转写成
Python。静态体检（`tools/check_gd_py.py`）只能证明**语法过关**，证明不了「跑得起来」。
本工具是产物第一次真正被执行的地方：把 8 套真实阵容按 lineup 摆盘装进 Python 内核，
从开战打到判胜，与 Godot 侧闸门 8 的 56 局基准逐行对照。

对照口径（★ 是本工具的核心价值）
================================
`gd_core_test/lineup_result.txt` 里那 56 行 `win=… t=… php=… ohp=… act=… dmg=…`
是 **Godot 3.6 宿主跑出来的权威基准**。两侧输入同源（都来自
`tools/gen_lineup_fixture.build()`，纯 Python 函数），种子同源（BASE_SEED 20260923
+ PAIR_STRIDE 101 的同一公式），故这些行应当**逐字符相等**。
任何一行的差异都指向转写器或运行时垫片的语义偏差 —— 这是「一致性」的可证伪判据，
而不是「两边都跑通了」这种不可证伪的说法。

装配次序（必须对齐原版，不是对齐模拟器）
======================================
     setup → 注网格元数据 → _readyInit → inventory.addItem → 逐个 setGem

★ 物品要在 `combat.setup()` **之后**才装：`_readyInit` 里 `newItemTimer` 等依赖
  `ctx.combat` 已就位。写成「先装物品、再 setup」会静默丢掉首轮计时。
★ 描述符**全局唯一**（`_descr_cache` 模块级）：`Item.isA` 靠引用相等判定，
  `countAllPlacedOfType` 等查询拿描述符当字典键。每局 new 一份会让同名物品在
  后一场覆盖注册表，前一场那件的 `isA` 立刻判假。

用法
====
    python tools/run_gd_py.py                 # 全量：装配自检 + 56 局 + 确定性 + 宝石 A/B + RNG 可复现性
    python tools/run_gd_py.py --limit 3       # 只跑前 3 个阵容的对局矩阵（调试用；对照自动跳过）
    python tools/run_gd_py.py --no-compare    # 跑全部自检但跳过基准对照
"""
from __future__ import annotations

import argparse
import io
import os
import sys
import traceback

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)

from tools.gen_lineup_fixture import build as build_fixture  # noqa: E402

from gd_core_py import _bootstrap, _registry as _R  # noqa: E402
from gd_core_py._rt import Vector2  # noqa: E402

OUT_DIR = os.path.join(ROOT, "output")
PY_RESULT = os.path.join(OUT_DIR, "py_lineup_result.txt")
GD_RESULT = os.path.join(ROOT, "gd_core_test", "lineup_result.txt")
# 逐事件轨迹（Task #9 的取样面；与 GDScript 侧 gd_core_test/event_trace.txt 对照）
PY_EVENT_TRACE = os.path.join(OUT_DIR, "py_event_trace.txt")

# ── 运行参数（与 LineupBattle.gd 逐字对齐） ──
BASE_SEED = 20260923
PAIR_STRIDE = 101
TIME_LIMIT = 180.0
MAX_TICKS = 20000

SKIPPED = set()


# ═══════════════════════════ 内核装载 ═══════════════════════════

LOAD_FAILED = _bootstrap.load_all()

CoreConst = _R.C("res://gd_core/CoreConst.gd")
CoreHooks = _R.C("res://gd_core/CoreHooks.gd")
CoreItem = _R.C("res://gd_core/CoreItem.gd")
CoreItemData = _R.C("res://gd_core/CoreItemData.gd")
CoreCharacter = _R.C("res://gd_core/CoreCharacter.gd")
CoreCombat = _R.C("res://gd_core/CoreCombat.gd")
CoreContext = _R.C("res://gd_core/CoreContext.gd")


# ═══════════════════════════ 探针 ═══════════════════════════

_HOOK_NAMES = [n for n, v in vars(CoreHooks).items()
               if callable(v) and not n.startswith("__")
               and n not in ("_init", "_init_fields", "has_method", "call", "callv",
                             "get_instance_id", "get_script", "get_class", "free",
                             "set_script", "emit_signal", "connect", "disconnect",
                             "is_connected")]


# ═══════════════════ 事件流 canonical 序列化（须与 GDScript 侧逐字同构） ═══════════════════
#
# 用途：Task #9「双引擎逐事件对照」。两侧都只有一个事件汇点 ——
# `CoreCombatLog.logEvent(event)` → `_ctx.hooks.logEvent(event)`。
# 把每次调用压成一行稳定文本，两侧逐行比对，就能把「56 局摘要一致」升级成
# 「**每一次攻击/伤害/治疗/层数/眩晕都一致**」。
#
# ★ 为什么这比摘要强：两句不同的战斗可以有完全相同的
#   `win/t/php/ohp/act/dmg/heal/gem/fat/fat/stun` 摘要（例如某次伤害被挪后一拍、
#   某个层数的施加对象换了一件物品）。摘要看不见，事件流看得见。
#
# ★ 为什么序列化器要写两遍（Python + GDScript）而不是共享代码：
#   共享不了（两种语言）。写两遍的代价是可能出现「假不一致」—— 那会当场暴露、
#   人工归因即可。真正的风险是「假一致」，故格式里塞进足够多的字段：
#   事件号 / 类型 / 父链深度 / 起源身份 / 目标 / 全部参数键值。
#   起源身份取「名字 + ownerType + 占格坐标」；宝石再拼上「宿主身份 + 插槽号」。
#
# ★ 分隔符选择：**字段**分隔符是 `|`，故 origin / params 值的**内部**绝不能用 `|`。
#   早先写成 `it:<名字>|<ownerType>|<格>`，结果一行被拆成 8 段、解析直接失败
#   （而且失败得很安静：整批差异都被归成「格式不可解析」）。键内一律用 `~`。
#   `gem(<宿主>~<插槽号>)` 同理。

def _ecells(item):
    """占格坐标规范串：按 (x,y) 升序，`x,y` 以 `;` 相连；无格记 `-`。"""
    cells = getattr(item, "occupiedCells", None) or []
    pairs = sorted((int(c.x), int(c.y)) for c in cells)
    return ";".join("%d,%d" % p for p in pairs) if pairs else "-"


def ekey(obj):
    """把 origin / params 值压成稳定短串。

    ★ 宝石的特殊处理：`setGem` 把插座身份折叠成宿主物品本身
      （`gem.socket = self`、`host.gems[socketId] = gem`），宝石自己
      `occupiedCells` 被清空 → 单靠名字+格无法区分同名的两颗宝石。
      故宝石记成 `gem(<宿主身份>#<插槽号>)`，宿主身份递归复用同一函数。
    """
    if obj is None:
        return "-"
    if isinstance(obj, bool):
        return "T" if obj else "F"
    if isinstance(obj, int):
        return "i%d" % obj
    if isinstance(obj, float):
        return "%.6f" % obj

    sock = getattr(obj, "socket", None)
    if sock is not None:
        sid = -1
        for i, g in enumerate(getattr(sock, "gems", None) or []):
            if g is obj:
                sid = i
                break
        return "gem(%s~%d)" % (ekey(sock), sid)

    if hasattr(obj, "getName") and hasattr(obj, "occupiedCells"):
        return "it:%s~%d~%s" % (obj.getName(), int(obj.ownerType), _ecells(obj))

    # 预料外的类型：有名字就带名字，否则只记 `?`。
    # ★ 实测（56 局全部事件）origin 只有 int 与物品两类、params 只有 int/float/bool
    #   三类，走不到这里；留着是为了「出现新类型时不要静默变成同一串」。
    if hasattr(obj, "getName"):
        return "ob:%s" % obj.getName()
    return "?"


def eline(event):
    """单条事件 → 一行文本：`id|type|depth|origin|target|params`。"""
    params = ",".join("%s=%s" % (k, ekey(event.params[k]))
                      for k in sorted(event.params.keys()))
    return "%d|%d|%d|%s|%s|%s" % (int(event.id), int(event.getType()),
                                  int(event.getDepth()), ekey(event.getOrigin()),
                                  ekey(event.target), params)


class HookProbe(CoreHooks):
    """`LineupBattle.gd::HookProbe` 的等价物。

    计数口径全部取「只可能由战斗判定路径触发」的钩子（见 CoreHooks.gd 分区注释）。
    ★ 激活计数走**统计埋点**（`snapshotItemMetric`）而不是动画钩子：原版 `activate()`
      只在 `animationOverride != null` 时才播放激活动画，常规触发那次不走它 ——
      拿动画计数会得到「act=0 但伤害照打」的假警报。
    """

    def _init_fields(self):
        super()._init_fields()
        self.activations = 0
        self.damage_events = 0
        self.damage_sum = 0.0
        self.heal_events = 0
        self.heal_sum = 0.0
        self.gem_heals = 0
        self.gem_heal_sum = 0.0
        self.fatigue_ticks = 0
        self.stuns = 0
        # 逐事件轨迹。None = 不记（默认）；list = 记 canonical 行（见 ekey/eline）。
        # ★ 记与不记**只影响这一行 append**，不参与任何判定 —— 故可在生产装配路径上开。
        self.event_lines = None

    # ── 四条计数钩子 ──

    def snapshotItemMetric(self, _item, metricIndex, _playerId=None,
                           _withNextEvent=False):
        if metricIndex == CoreConst.ItemMetrics.Activations:
            self.activations += 1

    def spawnLabel_character(self, _character, type, damage, item=None):
        if type == CoreConst.EventType.Health:
            self.heal_events += 1
            self.heal_sum += abs(float(damage))
            if item is not None and isinstance(item, CoreItem) and item.isGem():
                self.gem_heals += 1
                self.gem_heal_sum += abs(float(damage))
        else:
            self.damage_events += 1
            self.damage_sum += abs(float(damage))

    def playFatigueAnimation(self, _name):
        self.fatigue_ticks += 1

    def playStunAnimation(self, _character, _duration):
        self.stuns += 1

    # ── 事件流记录（第 51 个钩子） ──

    def logEvent(self, event):
        """`CoreCombatLog.logEvent` 的唯一出口。

        ★ 这是 Task #9 逐事件对照的取样点：原版的**每一个**战斗事件
          （攻击 / 伤害 / 治疗 / 层数增减 / 眩晕 / 激活 / 疲劳 …）都经这里过一遍，
          故这一处就能覆盖整条判定路径的输出面。
        """
        if self.event_lines is not None:
            self.event_lines.append(eline(event))


class TraceProbe(HookProbe):
    """在 HookProbe 之上记录**全部 51 个钩子**的调用序。

    全部 CoreHooks 方法都是 `-> void` 且零 `return`（已静态核验），故「记录 + 返回
    None」与默认空实现在**返回值上完全等价**，可安全叠加在任意钩子上而不会改变判定。

    ★ 当前**未被任何对照工具使用**，保留理由与已知边界都写在这里，免得被误当成
      「已取证」：
      · 逐事件对照（Task #9）用的是 `logEvent` 这一个钩子的事件流（见 ekey/eline），
        不是 51 个钩子。**事件流是更强的证人** —— 它带参数与父链，而钩子名只说明
        「某个呈现层动作被请求了」。
      · 单侧可用（本侧），GDScript 侧要 51 个手写覆写才能对称；收益不抵成本，故不做。
      · 若要启用，必须走 `HookProbe` 的实现而不能整段替换 —— 见 `_install_trace`。
    """

    def _init_fields(self):
        super()._init_fields()
        self.trace = []

    def _hook(self, name, args):
        self.trace.append((name, tuple(ekey(a) for a in args)))


def _install_trace():
    """给 TraceProbe 动态挂上 51 个钩子覆写（手工写 51 个方法既长又易漏）。

    ★★ 必须先调**父类实现**再记录。早先这里写成「只记录 + 返回 None」，等于把
       `HookProbe` 的四个计数钩子（snapshotItemMetric / spawnLabel_character /
       playFatigueAnimation / playStunAnimation）在 TraceProbe 上**整段遮蔽**掉了 ——
       于是开 trace 跑出来的 `act` 恒为 0，而**一行错都不报**。
       这正是「零报错 ≠ 生效」的又一实例。父类实现全部返回 None，故先调后记
       在返回值上完全等价。
    """
    def make(name):
        parent = getattr(HookProbe, name)

        def hooked(self, *args):
            self._hook(name, args)
            return parent(self, *args)

        hooked.__name__ = str(name)
        return hooked
    for n in _HOOK_NAMES:
        setattr(TraceProbe, n, make(n))


_install_trace()


# ═══════════════════════════ 夹具 ═══════════════════════════

FIXTURE_ITEMS, FIXTURE_LINEUPS = build_fixture()


# ═══════════════════════════ 装配辅助（对应 LineupBattle.gd 同名函数） ═══════════════════════════

def v(cell):
    """夹具里的格是 [col, row]；内核向量是 Vector2(x=col, y=row)。"""
    return Vector2(int(cell[0]), int(cell[1]))


def vlist(cells):
    return [v(c) for c in cells]


def live_lineups():
    return sorted(k for k in FIXTURE_LINEUPS.keys() if k not in SKIPPED)


def new_character(ctx, pid, lu):
    c = CoreCharacter(ctx, pid)
    c.characterClass = int(lu["class"])
    c.setMaxHealth(int(lu["health"]))
    c.setCurrentHealth(int(lu["health"]))
    c.maxStamina = float(lu["stamina"])
    c.baseMaxStamina = float(lu["stamina"])
    c.baseStaminaRegen = float(lu["regen"])
    c.staminaRegen = float(lu["regen"])
    c.fillUpStamina()
    return c


# ★ 模块级 = GDScript 脚本级 var，跨对局复用（见文件头「描述符全局唯一」）
_DESCR_CACHE = {}


def descriptor_of(ctx, key):
    if key in _DESCR_CACHE:
        return ctx.item_book.register(_DESCR_CACHE[key])
    d = FIXTURE_ITEMS[key]
    made = CoreItemData().fromDict({
        "name": d["name"],
        "identifier": d["identifier"],
        "minDam": d["minDam"],
        "maxDam": d["maxDam"],
        "cd": d["cd"],
        "extraCds": d["extraCds"],
        "accuracy": d["accuracy"],
        "staminaCost": d["staminaCost"],
        "block": d["block"],
        "price": d["price"],
        "rarity": d["rarity"],
        "classes": d["classes"],
        "canActivate": d["canActivate"],
        "chance": d["chance"],
        "chance2": d["chance2"],
        "types": d["types"],
        "tags": d["tags"],
        "params": d["params"],
        "namedParams": d["namedParams"],
    })
    _DESCR_CACHE[key] = made
    return ctx.item_book.register(made)


_SCRIPT_FAIL = []


def script_of(path):
    """取物品脚本类。

    ★ 与 GDScript 侧的差别：那边 `load(path)` 失败返回 null（可判定），
      Python 侧 `_R.C()` 未命中会返回**占位类**（不报错）。若不显式查注册表，
      「脚本没转译出来」会表现成「物品装上了但什么都不做」—— 零报错、静默失效。
      故这里对未登记路径必须立即判失败。
    """
    if not _R.is_registered(path):
        _SCRIPT_FAIL.append(path)
        return None
    return _R.C(path)


def make_item(ctx, chr_, e):
    path = e["script"]
    cls = script_of(path)
    if cls is None:
        return None
    it = cls()
    it.setup(ctx, descriptor_of(ctx, e["key"]), chr_)
    # 插座数组按 socket 数建等长（原版 sockets = $Icon/Sockets.get_children()）
    n = int(FIXTURE_ITEMS[e["key"]]["sockets"])
    for _i in range(n):
        it.gems.append(None)
    # 网格元数据（原版由 cacheCollisionCells() 从 TileMap 读；内核由装配层注入）
    it.collisionCells = vlist(e["collision"])
    aff = {}
    for color in e["affected"].keys():
        aff[int(color)] = vlist(e["affected"][color])
    it.affectedTileCells = aff
    return it


def place_and_ready(ctx, chr_, e, owner_type, with_gems=True):
    it = make_item(ctx, chr_, e)
    if it is None:
        return None
    it.occupiedCells = vlist(e["occupied"])
    it.ownerType = owner_type
    # 原版次序：物品入场景树时 _ready 先跑，随后 Inventory.addItem 才调 addToInventory
    it._readyInit()
    chr_.inventory.addItem(it, it.occupiedCells)
    # 宝石在宿主入包之后才 setGem（对齐原版「先摆宿主、再 setGemData」的次序）
    if not with_gems:
        return it
    gems = e["gems"]
    gem_scripts = e.get("gemScripts") or []
    for gi in range(len(gems)):
        gkey = gems[gi]
        gd = {
            "key": gkey,
            "script": gem_scripts[gi],
            "collision": [[0, 0]],
            "affected": {},
            "occupied": [],
        }
        gem = make_item(ctx, chr_, gd)
        if gem is None:
            continue
        gem._readyInit()
        it.setGem(gi, gem)
    return it


def build_side(ctx, chr_, lu, owner_type, with_gems=True):
    out = []
    for e in lu["items"]:
        if e["storage"]:
            continue          # 储物箱里的物品不参战（对齐原版：只装背包）
        it = place_and_ready(ctx, chr_, e, owner_type, with_gems)
        if it is not None:
            out.append(it)
    return out


def new_battle(seed_value, p_name, o_name, with_gems=True, trace=False):
    # ★ trace 只打开 `event_lines` 记录，**不换 probe 类** —— 走的是与生产完全同一
    #   条装配路径，这样事件流取证才代表真正被验收的那个装配。
    probe = HookProbe()
    if trace:
        probe.event_lines = []
    ctx = CoreContext(seed_value, probe)
    pla = FIXTURE_LINEUPS[p_name]
    opp = FIXTURE_LINEUPS[o_name]
    p = new_character(ctx, CoreCharacter.ID.PLAYER, pla)
    o = new_character(ctx, CoreCharacter.ID.OPPONENT, opp)
    combat = CoreCombat(ctx)
    combat.setup(p, o)
    # 物品要在 combat 就绪之后装（_readyInit 里 newItemTimer 等依赖 ctx.combat）
    p_items = build_side(ctx, p, pla, CoreConst.Owner.PlayerInventory, with_gems)
    o_items = build_side(ctx, o, opp, CoreConst.Owner.Opponent, with_gems)
    combat.startBattle(p_items, o_items)
    return {"ctx": ctx, "p": p, "o": o, "combat": combat, "probe": probe,
            "p_items": p_items, "o_items": o_items}


def run_battle(ctx, combat):
    ticks = 0
    while not combat.fight_ended and ticks < MAX_TICKS:
        combat.physicsTick(CoreContext.PHYSICS_DELTA)
        ticks += 1


def winner_label(combat):
    w = combat.winner()          # ★ winner 是方法，不是属性
    if w is None:
        return "draw"
    return "P" if w.playerId == CoreCharacter.ID.PLAYER else "O"


def outcome(w):
    combat = w["combat"]
    p = w["p"]
    probe = w["probe"]
    return ("win=%s t=%.2f php=%.0f ohp=%.0f act=%d dmg=%d/%s heal=%d/%s "
            "gem=%d/%s fat=%d stun=%d" % (
                winner_label(combat), combat.combat_time, p.curHealth,
                w["o"].curHealth, probe.activations, probe.damage_events,
                ("%.1f" % probe.damage_sum), probe.heal_events,
                ("%.1f" % probe.heal_sum), probe.gem_heals,
                ("%.1f" % probe.gem_heal_sum), probe.fatigue_ticks, probe.stuns))


# ═══════════════════════════ 报告 ═══════════════════════════

class Report:
    def __init__(self):
        self.lines = []
        self.failures = []
        self.rows = []

    def say(self, line):
        self.lines.append(line)

    def check(self, cond, what):
        if not cond:
            self.failures.append(what)

    def dump(self):
        os.makedirs(OUT_DIR, exist_ok=True)
        with io.open(PY_RESULT, "w", encoding="utf-8") as fh:
            fh.write("\n".join(self.lines) + "\n")


R = Report()


# ═══════════════════════════ 0. 装载自检 ═══════════════════════════

def test_bootstrap():
    R.say("")
    R.say("[0] 装载自检：521 个转写模块全部导入、类注册表无占位符")
    R.check(not LOAD_FAILED, "有 %d 个模块导入失败：%s"
            % (len(LOAD_FAILED), str(LOAD_FAILED[:3])))
    st = _R.stats()
    R.check(st["placeholders"] == 0,
            "注册表出现 %d 个占位类（导入拓扑序不对）：%s"
            % (st["placeholders"], str(st["missing"])))
    R.say("    导入失败 %d / 注册 %d 类 / 占位符 %d ✓"
          % (len(LOAD_FAILED), st["registered"], st["placeholders"]))
    if LOAD_FAILED:
        for rel, exc in LOAD_FAILED[:10]:
            R.say("      FAIL %s: %s" % (rel, exc))


# ═══════════════════════════ 1. 夹具自检 ═══════════════════════════

def test_fixture_shape():
    R.say("")
    R.say("[1] 夹具自检：枚举已按 CoreConst 转成 int、几何已转成绝对格")

    R.check(len(FIXTURE_ITEMS) >= 16, "夹具物品数异常：%d" % len(FIXTURE_ITEMS))
    R.check(len(FIXTURE_LINEUPS) == 8, "夹具阵容数应为 8，实为 %d" % len(FIXTURE_LINEUPS))

    bad = []
    for k in sorted(FIXTURE_ITEMS):
        d = FIXTURE_ITEMS[k]
        for t in d["types"]:
            if not isinstance(t, int):
                bad.append(k + ".types")
                break
        if not isinstance(d["tags"], int):
            bad.append(k + ".tags")
    R.check(not bad, "类型/标签未转成 int：" + str(bad))

    for name in sorted(FIXTURE_LINEUPS):
        lu = FIXTURE_LINEUPS[name]
        seen = set()
        oob = 0
        for e in lu["items"]:
            for c in e["occupied"]:
                if int(c[0]) < 0 or int(c[0]) >= 7 or int(c[1]) < 0 or int(c[1]) >= 10:
                    oob += 1
                key = (int(c[0]), int(c[1]))
                if key in seen:
                    R.check(False, "阵容 %s 摆盘重叠于格 %s" % (name, str(key)))
                seen.add(key)
        R.check(oob == 0, "阵容 %s 有 %d 个占格越出 7×10 背包" % (name, oob))

    n = sum(len(FIXTURE_LINEUPS[k]["items"]) for k in FIXTURE_LINEUPS)
    R.say("    物品 %d / 阵容 %d / 摆盘件数 %d ✓（枚举 int 化 ✓、无重叠 ✓、不越界 ✓）"
          % (len(FIXTURE_ITEMS), len(FIXTURE_LINEUPS), n))


# ═══════════════════════════ 2. 装配自检 ═══════════════════════════

def test_assemble_once():
    R.say("")
    R.say("[2] 装配自检：物品脚本 / 网格 / 描述符 / 入包四条路径逐件走通")

    names = live_lineups()
    R.check(len(names) >= 7, "可用阵容应 ≥ 7，实为 %d" % len(names))

    w = new_battle(BASE_SEED, names[0], names[1])
    ctx = w["ctx"]
    lu = FIXTURE_LINEUPS[names[0]]

    R.check(len(w["p_items"]) == len(lu["items"]),
            "玩家侧装配件数 %d 应等于阵容件数 %d"
            % (len(w["p_items"]), len(lu["items"])))

    for it in w["p_items"]:
        R.check(it is not None, "装配出 null 物品")
        R.check(it.placed, "%s 应已入包（placed）" % it.getName())
        R.check(it.ownerType == CoreConst.Owner.PlayerInventory,
                "%s 的 ownerType 应为 PlayerInventory，实为 %d"
                % (it.getName(), it.ownerType))
        R.check(len(it.occupiedCells) > 0, "%s 应占至少 1 格" % it.getName())
        R.check(ctx.item_book.getDescriptor(it.getName()) is it.descriptor,
                "%s 的描述符应就是注册表里那一个实例（isA 前提）" % it.getName())
    for it in w["o_items"]:
        R.check(it.ownerType == CoreConst.Owner.Opponent,
                "对手侧 %s 的 ownerType 应为 Opponent，实为 %d"
                % (it.getName(), it.ownerType))

    R.say("    玩家 %d 件 / 对手 %d 件装配成功 ✓（placed ✓ / ownerType ✓ / 描述符身份 ✓）"
          % (len(w["p_items"]), len(w["o_items"])))


# ═══════════════════════════ 3. 全对局矩阵 ═══════════════════════════

def test_all_pairs(limit=0):
    names = live_lineups()
    if limit:
        names = names[:limit]
    R.say("")
    R.say("[3] 全对局矩阵：%d 套阵容的两两对战（含每件物品确实参与）" % len(names))

    zero_act = []
    timeouts = []
    no_damage = []
    trace = []
    for a in names:
        for b in names:
            if a == b:
                continue          # 自己打自己在对决矩阵里无信息量
            seed_value = (BASE_SEED + PAIR_STRIDE * live_lineups().index(a)
                          + live_lineups().index(b))
            # ★ 开 trace：走的是同一条生产装配路径，只多一次 append。
            #   事件流是 Task #9 逐事件对照的取样面（见 tools/compare_events.py）。
            w = new_battle(seed_value, a, b, trace=True)
            run_battle(w["ctx"], w["combat"])
            probe = w["probe"]
            trace.append("## %s|%s|%d" % (a, b, seed_value))
            trace.extend(probe.event_lines)
            row = "%s vs %s：%s" % (a.replace("lineup_", ""),
                                    b.replace("lineup_", ""), outcome(w))
            R.rows.append(row)
            if not w["combat"].fight_ended:
                R.check(False, "对局未收场（超过 %d tick）：%s" % (MAX_TICKS, row))
                timeouts.append(row)
                continue
            if w["combat"].timed_out:
                timeouts.append(row)
            if probe.activations == 0:
                zero_act.append(row)
            if probe.damage_events == 0:
                no_damage.append(row)

    R.say("    已完成 %d 局" % len(R.rows))
    for r in R.rows:
        R.say("      " + r)
    R.check(not timeouts, "有 %d 局靠 timed_out 兜底收场：%s"
            % (len(timeouts), str(timeouts[:3])))
    R.check(not zero_act, "有 %d 局物品一次都没触发（行为没跑起来）：%s"
            % (len(zero_act), str(zero_act[:3])))
    R.check(not no_damage, "有 %d 局没有任何伤害事件：%s"
            % (len(no_damage), str(no_damage[:3])))

    # ── 落事件轨迹（Task #9 逐事件对照的输入） ──
    # ★ 空轨迹必须是失败：若 logEvent 因任何原因没被调用（钩子没接上、probe 换了类），
    #   文件会「生成成功且为空」，逐行对照就成了「0 = 0 通过」——典型的空断言。
    n_ev = sum(1 for ln in trace if not ln.startswith("##"))
    io.open(PY_EVENT_TRACE, "w", encoding="utf-8").write("\n".join(trace) + "\n")
    R.check(n_ev > 0, "事件轨迹为空 —— logEvent 没被接上，逐事件对照会退化成空断言")
    R.say("    事件轨迹：%d 局 / %d 条事件 → %s"
          % (len(R.rows), n_ev, os.path.relpath(PY_EVENT_TRACE, ROOT)))


# ═══════════════════════════ 4. 确定性 ═══════════════════════════

def test_determinism():
    R.say("")
    R.say("[4] 确定性：同种子重跑，赢家/血量/时长/事件计数须逐位一致")

    names = live_lineups()
    diff = []
    for i in range(len(names)):
        a = names[i]
        b = names[(i + 1) % len(names)]
        seed_value = BASE_SEED + 7777 + i
        r1 = None
        r2 = None
        for rep in range(2):
            w = new_battle(seed_value, a, b)
            run_battle(w["ctx"], w["combat"])
            line = outcome(w)
            cur = [line, w["p"].curHealth, w["o"].curHealth, w["combat"].combat_time]
            if rep == 0:
                r1 = cur
            else:
                r2 = cur
        if str(r1) != str(r2):
            diff.append("%s vs %s：%s ≠ %s" % (a, b, str(r1), str(r2)))
    R.check(not diff, "有 %d 组同种子结果不一致：%s" % (len(diff), str(diff[:3])))
    R.say("    复跑 %d 组 ✓" % len(names))


# ═══════════════════════════ 5. 宝石实效（A/B 对照） ═══════════════════════════

def test_gem_effect():
    R.say("")
    R.say("[5] 宝石实效 A/B：同种子含宝石 / 去宝石，宝石必须真的产生治疗")

    a_name = "lineup_gem_test"
    b_name = "lineup_dagger_swarm"
    seed_value = BASE_SEED + 9101

    with_gem = new_battle(seed_value, a_name, b_name, True)
    run_battle(with_gem["ctx"], with_gem["combat"])
    without_gem = new_battle(seed_value, a_name, b_name, False)
    run_battle(without_gem["ctx"], without_gem["combat"])

    pa = with_gem["probe"]
    pb = without_gem["probe"]
    R.say("    含宝石：%s" % outcome(with_gem))
    R.say("    去宝石：%s" % outcome(without_gem))

    # ① 对照局一次宝石治疗都不能有 —— 同时验证探针的归属判据没误伤
    R.check(pb.gem_heals == 0,
            "去宝石对照局不该有宝石治疗，实为 %d 次" % pb.gem_heals)
    # ② 含宝石侧必须真的治疗过。★ 宝石链路若断在任意一环，整场照样零报错跑完，
    #    只有这个计数能揭穿它。
    R.check(pa.gem_heals > 0, "gem_test 的宝石一次都没治疗 —— 宝石效果静默失效")
    # ③ 每次宝石治疗的量必须 ≥ 1（公式 ceil(伤害 × 7%)）
    R.check(pa.gem_heal_sum >= float(pa.gem_heals),
            "宝石治疗合计 %.1f 小于 %d 次 × 1 HP —— 公式下界被破坏"
            % (pa.gem_heal_sum, pa.gem_heals))
    # ④ 宝石必须改变战局
    R.check(pa.heal_events > pb.heal_events,
            "含宝石局治疗次数 %d 未高于对照局 %d —— 宝石治疗未进入角色结算"
            % (pa.heal_events, pb.heal_events))
    R.say("    宝石治疗 %d 次 / 合计 %.1f HP；对照局 0 次 ✓（治疗总数 %d > %d）"
          % (pa.gem_heals, pa.gem_heal_sum, pa.heal_events, pb.heal_events))


# ═══════════════════════════ 6. 与 Godot 基准逐行对照 ═══════════════════════════

def parse_rows(text):
    """从结果文件里抽出 `xxx vs yyy：win=…` 行 → {对决名: 结果串}。"""
    out = {}
    for line in text.split("\n"):
        s = line.strip()
        if " vs " in s and "：win=" in s:
            name, rest = s.split("：", 1)
            out[name.strip()] = rest.strip()
    return out


def test_compare_baseline():
    R.say("")
    R.say("[6] 与 Godot 基准对照：56 局逐行比对（gd_core_test/lineup_result.txt）")

    if not os.path.exists(GD_RESULT):
        R.say("    基准文件不存在，跳过：%s" % GD_RESULT)
        return
    with io.open(GD_RESULT, encoding="utf-8") as fh:
        gd = parse_rows(fh.read())
    py = {}
    for r in R.rows:
        name, rest = r.split("：", 1)
        py[name.strip()] = rest.strip()

    common = sorted(set(gd) & set(py))
    only_gd = sorted(set(gd) - set(py))
    only_py = sorted(set(py) - set(gd))
    diff = [k for k in common if gd[k] != py[k]]

    R.say("    基准 %d 局 / 本次 %d 局 / 可比 %d 局" % (len(gd), len(py), len(common)))
    if only_gd:
        R.check(False, "基准有而本次无的对局 %d 个：%s" % (len(only_gd), str(only_gd[:3])))
    if only_py:
        R.check(False, "本次有而基准无的对局 %d 个：%s" % (len(only_py), str(only_py[:3])))

    if diff:
        R.say("    ✗ 不一致 %d / %d 局：" % (len(diff), len(common)))
        for k in diff:
            R.say("      %s" % k)
            R.say("        基准 %s" % gd[k])
            R.say("        Py   %s" % py[k])
        R.check(False, "有 %d 局与 Godot 基准不一致" % len(diff))
    else:
        R.say("    ✓ 全部 %d 局逐字符一致（赢家 / 时长 / 双方血量 / 五类事件计数）"
              % len(common))


# ═══════════════════════════ 7. RNG 可复现性（randomize 未触发） ═══════════════════════════

def test_rng_not_randomized():
    """证明「种子非零」这条前提真的成立，而不是靠注释保证。

    背景：`CoreRng.gd:22-27` 是 `if _seed == 0: rng.randomize() else: rng.seed = _seed`。
    一旦走到 `randomize()`，整局的随机源变成时间播种，**可复现性静默丢失** ——
    而所有「逐字符对照基准」的结论都会随之作废，且不会报任何错。

    ★ 双侧判据（缺一不可）：
      ① 正常路径：跑完全部自检后 `_RANDOMIZED[0]` 必须仍为 False；
      ② 正对照：显式造一个 `CoreRng(0)`，标志位必须**翻成 True**。
         只做 ① 是不够的 —— 若标志位根本没接上（永远 False），① 是无条件成立的，
         这种「恒真断言」等于没断言。② 才是证明它带电的那根表笔。
    """
    from gd_core_py import _rt

    R.say("")
    R.say("[7] RNG 可复现性：整条正常路径不得触发 RandomNumberGenerator.randomize()")

    # ① 正常路径
    R.check(_rt._RANDOMIZED[0] is False,
            "正常路径触发了 randomize() —— 随机源已变成时间播种，可复现性丢失")

    # ② 正对照：这条路径必须能让标志位翻转（证明判据 ① 不是恒真）
    #    ★ 注意构造语法：转写器把 `CoreRng.new(0)` 映射成 `CoreRng(0)`（.new 规则），
    #      这里写 `.new(0)` 会 AttributeError。
    rng_cls = _R.C("res://gd_core/CoreRng.gd")
    _before = _rt._RANDOMIZED[0]
    _rt._RANDOMIZED[0] = False
    rng_cls(0)
    R.check(_rt._RANDOMIZED[0] is True,
            "CoreRng(0) 未触发 randomize() —— 标志位没接上，判据 ① 是恒真的空断言")
    _rt._RANDOMIZED[0] = _before
    R.say("    正常路径未触发 ✓  种子 0 正对照已触发 ✓（判据带电）")


# ═══════════════════════════ main ═══════════════════════════

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--limit", type=int, default=0,
                    help="对局矩阵只用前 N 个阵容（调试用；0 = 全部）")
    ap.add_argument("--no-compare", action="store_true", help="跳过基准对照")
    args = ap.parse_args()

    R.say("")
    R.say("=== gd_core_py 真实阵容端到端验证 ===")
    print("GDRUN: start")

    test_bootstrap()
    print("GDRUN: bootstrap done")

    test_fixture_shape()
    print("GDRUN: shape done")

    test_assemble_once()
    print("GDRUN: assemble done")

    test_all_pairs(args.limit)
    print("GDRUN: pairs done")

    test_determinism()
    print("GDRUN: determinism done")

    test_gem_effect()
    print("GDRUN: gem done")

    if not args.no_compare and not args.limit:
        test_compare_baseline()
        print("GDRUN: compare done")

    test_rng_not_randomized()
    print("GDRUN: rng done")

    if _SCRIPT_FAIL:
        R.check(False, "有 %d 个物品脚本未转译（注册表缺路径）：%s"
                % (len(_SCRIPT_FAIL), str(sorted(set(_SCRIPT_FAIL))[:5])))

    R.say("")
    if not R.failures:
        R.say("GDRUN: PASS")
    else:
        for f in R.failures:
            R.say("GDRUN: FAIL  " + str(f))
        R.say("GDRUN: FAIL (%d 项)" % len(R.failures))
    R.dump()

    print("")
    print("\n".join(R.lines[-40:]))
    return 0 if not R.failures else 1


if __name__ == "__main__":
    sys.exit(main())
