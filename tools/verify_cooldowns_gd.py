# -*- coding: utf-8 -*-
"""冷却等价校验 —— 里程碑 ⑥ 的 `verify_cooldowns` 等价校验。

分两半，两个半边都必须过：

  ── A. 静态半边：冷却路径逐函数对照（纯 Python，秒级） ──
     把 `gd_core/CoreItem.gd` 与 `decompiled_full/Items/Item.gd` 里**冷却路径**的
     每一个函数体抽出来，各自规范化后逐行比对。差异分四级：

       SAME      两边逐行相等
       MAPPED    差异行命中**已声明**的规范化/语义改写规则（规则表在下方，每条
                 都必须真的命中，0 命中的规则会被点名 —— 表笔没接上等于没断言）
       EXTRA     内核独有行，命中已声明的「内核新增」台账（如 `_tickTimers` 驱动）
       UNATTR    未归因差异 —— 出现即 FAIL

     ★ 为什么做了逐事件对照还要做逐行对照：事件对照只覆盖**56 局跑到的事件**；
       冷却路径上「本局没触达的那条分支」它看不见。逐行对照是代码面的，不看运气。

     ★ 为什么不做「整函数文本 diff 然后人工看」：那样每改一次内核都要重看一遍，
       且看不出「差异属于哪一类」。声明式规则的意义是：差异**必须**落到某一类里，
       落不进去就是 FAIL，而不是「看起来差不多」。

  ── B. 动态半边：逐帧冷却推进恒等式（读 Godot 侧落下的数据） ──
     数据源 `gd_core_test/cooldown_battle_result.txt`，由闸门 9
     （`gd_core_test/ItemBattle.gd`）在**同一批 517 场对局**里逐帧轮询产出
     ——tick 次序/delta/上限与普通驱动逐字相同，只多出采样。

     判据：
       D1  `triggerTime_n == triggerTime_{n-1} − δ × getSpeed()`
           在「前后两帧冷却都激活、都未眩晕」的帧上必须逐位成立 —— 这就是内核
           `CoreItem.physicsTick` 的那个减法。实测 22.8 万帧、违背 0 帧。
       D2  首个 `iterationCooldown` 变更帧必须落在三类之一：
             A 递减触发   `tt == tt⁻ − δ·speed + ic`（`trigger()` 的 `+= ic`）
             B 比例缩放   `tt == (tt⁻/ic⁻)·ic`（`updateBaseCooldown`）
             C 台账归因   D2_ALLOW 里逐条给出机制，且工具会去物品脚本核实该机制
                          确实存在（双向核验，台账不许当遮羞布）
           落进 C 之外的第四类 = FAIL。
       D3  抖动指纹 `iterationCooldown / getCooldown()` ∈ [0.95, 1.05]，且不退化
           为常数 —— 原版 `Util.rng.randf_range(0.95, 1.05)` 的可复算指纹，也是
           「冷却语义三方分歧（`simulator/` 返回固定 cd）」的口径守卫。

     ★ 观测面单独判：`seen=0`（从未装上冷却）判 FAIL；`start_act=0`（装上即被撤）
       必须能被物品脚本里的 `preCombatStart → deactivateCooldown()` 解释。
       「什么都没测到」不许冒充「测了且通过」。

用法：
    python tools/verify_cooldowns_gd.py            # A + B
    python tools/verify_cooldowns_gd.py --static   # 只跑 A（不需要先跑闸门 9）
    python tools/verify_cooldowns_gd.py -v         # A 附逐函数差异明细
"""
from __future__ import annotations

import difflib
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

CORE_PATH = os.path.join(ROOT, "gd_core", "CoreItem.gd")
# 直挂层：内核没写的少数函数由它提供（工具生成，非手写）。
# ★ 不把它当第二权威 —— 它是 build_item_scripts.py 从原版机械转译的产物，
#   故 A 段同样逐行对照，只是把来源标出来。
ADAPTER_PATH = os.path.join(ROOT, "gd_core_items", "Item.gd")
ORIG_PATH = os.path.join(ROOT, "decompiled_full", "Items", "Item.gd")
DYNAMIC_PATH = os.path.join(ROOT, "gd_core_test", "cooldown_battle_result.txt")

VERBOSE = "-v" in sys.argv or "--verbose" in sys.argv

# ─────────────────────────── 函数对 ───────────────────────────
# (内核名, 原版名)。名字不同的是因为内核把引擎回调换成了显式驱动入口。
FUNC_PAIRS = [
    ("getSpeed", "getSpeed"),
    ("speed", "speed"),
    ("getStackSpeedMods", "getStackSpeedMods"),
    ("hasCooldown", "hasCooldown"),
    ("isCooldownActive", "isCooldownActive"),
    ("activateCooldown", "activateCooldown"),
    ("deactivateCooldown", "deactivateCooldown"),
    ("onAfterEffectFinished", "onAfterEffectFinished"),
    ("combatEnd", "combatEnd"),
    ("getBaseCooldown", "getBaseCooldown"),
    ("getBaseCooldownIndex", "getBaseCooldownIndex"),
    ("getCooldown", "getCooldown"),
    ("getCooldownIndex", "getCooldownIndex"),
    ("getModifiedCooldown", "getModifiedCooldown"),
    ("getModifiedCooldownIndex", "getModifiedCooldownIndex"),
    ("getCooldownEncoded", "getCooldownEncoded"),
    ("isCooldownModified", "isCooldownModified"),
    ("logCooldown", "logCooldown"),
    ("adjustCooldown", "adjustCooldown"),
    ("setBaseCooldown", "setBaseCooldown"),
    ("resetBaseCooldown", "resetBaseCooldown"),
    ("updateBaseCooldown", "updateBaseCooldown"),
    ("preCombatStart", "preCombatStart"),
    ("trigger", "trigger"),
    ("advanceCooldownPercent", "advanceCooldownPercent"),
    ("advanceCooldownSeconds", "advanceCooldownSeconds"),
    ("physicsTick", "_physics_process"),
]

# ─────────────────── 规范化规则（双侧相同地施加） ───────────────────
# 单例/命名空间到内核的机械改名。这些在整份内核里是全局约定，
# 不构成「冷却路径特有的改写」。
CANON_BOTH = [
    (r"\bCoreConst\.ItemStat\.", "Stat."),
    (r"\bCoreConst\.Owner\.", "Owner."),
    (r"\bCoreConst\.CharID\.", "CharID."),
    (r"\bCoreConst\.", ""),
    (r"\bctx\.hooks\.", "Hooks."),
    (r"\bctx\.combat_log\.", "CombatLog."),
    (r"\bctx\.rng\.", "Rng."),
    (r"\bUtil\.rng\.", "Rng."),
    # Util.flip(chance) = `return rng.randf() <= chance`（Utility/Util.gd:1010），
    # 与 CoreRng.flip 逐字一致；内核无 Util 单例，改为实例方法调用。
    (r"\bUtil\.flip\(", "Rng.flip("),
    (r"\bGame\.combatLog\.", "CombatLog."),
    (r"\bGame\.Leagues\.", "Leagues."),
    (r"\bGame\.Mode\.", "Mode."),
    (r"\bGame\.isBelowLeague\(", "isBelowLeague("),
    (r"\bGame\.curMode\b", "curMode"),
    (r"\bUtil\.", ""),
    (r"\bctx\.", ""),
    (r"\bme\.", ""),
    # 钩子调用：内核显式传 self，原版是物品自己的方法
    (r"\bHooks\.(\w+)\(self,\s*", r"Hooks.\1("),
    (r"\bHooks\.(\w+)\(self\)", r"Hooks.\1()"),
]

# ─────────────────── 语义改写声明（每条必须命中） ───────────────────
# ★ 这些不是「名字不同」，是**同一语义的两种写法**。每一条都附依据。
#   命中次数为 0 会被判「陈旧条目」——声明了却不发生，说明内核变了或规则写错了。
#
# 内核侧 → 归一形
SEMANTIC_CORE = [
    (r"character_ != null and character_\.playerId == CharID\.OPPONENT and \(below_master or lobbies_mode\)",
     "@isOpponentAndBelowMasterOrLobbies",
     "原版判「物品属于对手 且 处于 Master 以下联赛或 Lobbies 模式」——依据 ownerType 与全局 Game 状态；"
     "内核无单例，改读宿主物品的 character_ 与注入的 ctx.below_master/lobbies_mode"),
    (r"setCooldownActive\(false\)", "setActiveFalse()",
     "内核把「关闭冷却推进」抽成显式设值；原版对应 set_physics_process(false)。"
     "combatEnd() 是冷却路径上唯一的调用点（★ 没有 setCooldownActive(true) —— "
     "开启走的是 activateCooldown()，故本表不声明 true 分支，声明了会因 0 命中被判陈旧）"),
    (r"_cooldown_active = true", "setActiveTrue()",
     "activateCooldown() 的实现体：原版 = set_physics_process(true)"),
    (r"_cooldown_active = false", "setActiveFalse()",
     "deactivateCooldown() 的实现体：原版 = set_physics_process(false)"),
    (r"\breturn _cooldown_active\b", "return @isCdActive",
     "isCooldownActive() 的实现体：原版 = is_physics_processing()。"
     "★ 该映射掩盖了一处**已知张力**（战斗外窗口），见 TENSIONS"),
    (r"\bif not _cooldown_active:", "if not @isCdActive:",
     "同上：读的是同一个谓词"),
    (r"\bif isCooldownActive\(\)", "if @isCdActive():",
     "getCooldownEncoded 里读的也是同一个谓词"),
]

# 原版侧 → 归一形
SEMANTIC_ORIG = [
    (r"ownerType == Owner\.Opponent and \(isBelowLeague\(Leagues\.Master\) or curMode == Mode\.Lobbies\)",
     "@isOpponentAndBelowMasterOrLobbies",
     "同上（内核侧改写）"),
    (r"set_physics_process\(true\)", "setActiveTrue()",
     "同上（内核侧改写）"),
    (r"set_physics_process\(false\)", "setActiveFalse()",
     "同上（内核侧改写）"),
    (r"\breturn is_physics_processing\(\)", "return @isCdActive",
     "同上（内核侧改写）"),
    (r"\bif is_physics_processing\(\)", "if @isCdActive():",
     "同上（内核侧改写）"),
    # 纯表现钩子：原版是物品自己的方法，内核统一走 CoreHooks 空实现
    (r"\bshowCooldownSmooth\(", "Hooks.showCooldownSmooth(",
     "表现钩子：内核 CoreHooks 里为空实现，不参与判定"),
    (r"\bshowCooldown\(", "Hooks.showCooldown(",
     "表现钩子：同上"),
]

# ─────────────────── 已声明剥离（原版有、内核删） ───────────────────
# (函数对名, 正则, 依据)。每条必须命中，0 命中即判「陈旧条目」。
DROP_LEDGER = [
    ("advanceCooldownPercent/advanceCooldownPercent", r"^spawnLabelOnItem\(",
     "漂浮冷却数字（Util.spawnLabelOnItem → BuffLabel.spawnLabelOnItem），"
     "纯表现，属既有剥离类别「日志/UI」。★ 删它不影响下一行的 snapshotItemTooltipStat，"
     "两者互相独立（前者画数字，后者记 tooltip 时间线）"),
    ("advanceCooldownSeconds/advanceCooldownSeconds", r"^spawnLabelOnItem\(",
     "同上"),
]

# ─────────────────── 内核新增行台账（每条必须命中） ───────────────────
# (函数对名, 正则, 依据)
EXTRA_LEDGER = [
    ("physicsTick/_physics_process", r"_tickTimers\(delta\)",
     "原版物品计时器是场景树 Timer 子节点，冷却门之外独立推进；内核是显式虚拟计时器，"
     "故必须在冷却门之前调 _tickTimers。★ 放在门后会让 buff 时长在冷却未激活时停摆"),
    ("physicsTick/_physics_process", r"if not @isCdActive:",
     "原版靠引擎「物理帧未启用就不回调」隐式跳过；内核显式判。"
     "★ 该谓词与原版 is_physics_processing() 在**战斗外窗口**存在机制差异，"
     "见本文件 TENSIONS 与 docs/gd_core_truth.md §6"),
    ("physicsTick/_physics_process", r"return$",
     "同上"),
]

# ─────────────────── 已知张力（只报告，不判 FAIL） ───────────────────
TENSIONS = [
    ("isCooldownActive",
     "内核 = 显式标志 _cooldown_active；原版 = is_physics_processing()。"
     "Godot 3.6 实测：脚本定义了 _physics_process 的节点入树后 is_physics_processing() 为 True"
     "（裸 Node2D 为 False），故原版物品在**入树后到首次 preCombatStart 之间**该谓词为真，"
     "而内核为假。战斗内不可观测 —— 依据：① 该窗口的状态被 preCombatStart 无条件重置"
     "（iterationCooldown/triggerTime/激活冷却三项都重写）；② 战斗路径上读该谓词的只有"
     "getCooldownEncoded、advanceCooldownPercent/Seconds 与 3 支物品脚本（TeslaCoil/TimeDilator/"
     "Ukulele），全部在 preCombatStart 之后才被调用；③ 枚举物品脚本无「战斗中往背包插入新物品」"
     "（BagofGiving/Lootbox/FurciferPrime/PortableAltar 加的是商店池 itemPool 而非背包）。"
     "未定裁的残留：该窗口内原版 _physics_process 是否真的推进/触发（取决于其中 character_ "
     "是否为空、iterationCooldown 是否为 0），需活体观察原版；即便推进也发生在战斗外。"),
]


# ─────────────────────────── 抽取 ───────────────────────────

_TOP = re.compile(r"^[A-Za-z_@#]")


def strip_comment(line: str) -> str:
    """去掉行尾注释。带引号状态机：`"a#b"` 里的 `#` 不是注释。"""
    out = []
    quote = None
    i = 0
    while i < len(line):
        c = line[i]
        if quote:
            out.append(c)
            if c == "\\" and i + 1 < len(line):
                out.append(line[i + 1])
                i += 2
                continue
            if c == quote:
                quote = None
        else:
            if c in "\"'":
                quote = c
                out.append(c)
            elif c == "#":
                break
            else:
                out.append(c)
        i += 1
    return "".join(out)


def extract_funcs(path: str) -> dict:
    """{函数名: (定义行号, [体行...])}。体不含 func 头那一行。

    体 = 从 func 行的下一行起，直到下一个列 0 的非空行（且不是 pass / 注释）。
    """
    with open(path, encoding="utf-8") as fh:
        lines = fh.read().splitlines()
    funcs = {}
    i = 0
    while i < len(lines):
        m = re.match(r"^func\s+([A-Za-z_]\w*)\s*\(", lines[i])
        if not m:
            i += 1
            continue
        name = m.group(1)
        start = i
        j = i + 1
        body = []
        while j < len(lines):
            ln = lines[j]
            s = ln.strip()
            if s and not ln[0].isspace():
                if s == "pass" or s.startswith("#"):
                    # 列 0 的 pass / 注释：pass 属函数尾部，注释不属函数
                    if s == "pass":
                        body.append(ln)
                        j += 1
                        continue
                    break
                break
            body.append(ln)
            j += 1
        if name in funcs:
            raise SystemExit("同名函数重复定义：%s @ %s:%d" % (name, path, start + 1))
        funcs[name] = (start + 1, body)
        i = j
    return funcs


# ─────────────────────────── 规范化 ───────────────────────────

class Counter:
    def __init__(self):
        self.hits = {}

    def bump(self, key):
        self.hits[key] = self.hits.get(key, 0) + 1


def normalize(body: list, side: str, hits: Counter) -> list:
    """side: 'core' | 'orig'。返回规范化后的行列表。"""
    # ① 去掉行尾注释、合并续行（\ 结尾）
    raw = []
    buf = ""
    for ln in body:
        s = strip_comment(ln)
        if buf:
            buf += " " + s.strip()
        else:
            buf = s.strip()
        if buf.endswith("\\"):
            buf = buf[:-1].rstrip()
            continue
        raw.append(buf)
        buf = ""
    if buf:
        raw.append(buf)

    out = []
    for ln in raw:
        s = " ".join(ln.split())
        if not s:
            continue
        # ② 机械改名
        for pat, rep in CANON_BOTH:
            s2 = re.sub(pat, rep, s)
            if s2 != s:
                hits.bump("canon:" + pat)
                s = s2
        # ③ 语义改写
        for pat, rep, _note in (SEMANTIC_CORE if side == "core" else SEMANTIC_ORIG):
            s2 = re.sub(pat, rep, s)
            if s2 != s:
                hits.bump("sem:" + pat)
                s = s2
        # ④ 空格式收尾：去掉标点前后多余空格
        s = re.sub(r"\s+([:,\)\]])", r"\1", s)
        s = re.sub(r"([\(\[])\s+", r"\1", s)
        s = re.sub(r"\s*([=+\-*/<>])\s*", r"\1", s)
        out.append(s)
    return out


def declared_extra(pair: str, line: str):
    for p, pat, note in EXTRA_LEDGER:
        if p != pair:
            continue
        if re.search(pat, line):
            return note
    return None


def declared_drop(pair: str, line: str):
    for p, pat, note in DROP_LEDGER:
        if p != pair:
            continue
        if re.search(pat, line):
            return note
    return None


# ─────────────────────────── A. 静态半边 ───────────────────────────

def run_static() -> int:
    core_funcs = extract_funcs(CORE_PATH)
    adapter_funcs = extract_funcs(ADAPTER_PATH)
    orig_funcs = extract_funcs(ORIG_PATH)

    print("A. 冷却路径逐函数对照")
    print("   内核   %s" % os.path.relpath(CORE_PATH, ROOT))
    print("   直挂层 %s（内核未写的少数函数由它提供）"
          % os.path.relpath(ADAPTER_PATH, ROOT))
    print("   原版   %s" % os.path.relpath(ORIG_PATH, ROOT))
    print()
    print("   %-46s %4s %4s %4s %4s %4s  %s"
          % ("函数", "内核", "原版", "同", "剥离", "未归", "判定"))

    hits = Counter()
    drop_used = Counter()
    extra_used = Counter()
    unattr_total = 0
    same_total = 0
    func_bad = []
    skip = []

    for cname, oname in FUNC_PAIRS:
        pair = "%s/%s" % (cname, oname)
        src = "内核"
        if cname in core_funcs:
            body = core_funcs[cname][1]
        elif cname in adapter_funcs:
            body = adapter_funcs[cname][1]
            src = "直挂层"
        else:
            skip.append("缺函数 %s（内核与直挂层都没有）" % cname)
            continue
        if oname not in orig_funcs:
            skip.append("原版缺函数 %s" % oname)
            continue
        cl = normalize(body, "core", hits)
        ol = normalize(orig_funcs[oname][1], "orig", hits)

        # 已声明剥离：原版独有的纯表现行
        kept, dropped = [], 0
        for ln in ol:
            note = declared_drop(pair, ln)
            if note is None:
                kept.append(ln)
            else:
                dropped += 1
                drop_used.bump("%s :: %s" % (pair, pat_of(DROP_LEDGER, pair, ln)))
        ol = kept

        sm = difflib.SequenceMatcher(a=ol, b=cl, autojunk=False)
        same_here = 0
        unattr = []
        for tag, i1, i2, j1, j2 in sm.get_opcodes():
            if tag == "equal":
                same_here += i2 - i1
                continue
            ok = True
            details = []
            for ln in ol[i1:i2]:
                details.append(("-", ln))
            for ln in cl[j1:j2]:
                note = declared_extra(pair, ln)
                if note is not None:
                    extra_used.bump("%s :: %s" % (pair, ln))
                    continue
                ok = False
                details.append(("+", ln))
            if not ok:
                unattr.append((tag, details))

        unattr_lines = sum(len(d) for _t, d in unattr)
        unattr_total += unattr_lines
        same_total += same_here
        status = "PASS" if not unattr_lines else "FAIL"
        print("   %-46s %4d %4d %4d %4d %4d  %s%s"
              % (pair, len(cl), len(ol), same_here, dropped, unattr_lines, status,
                 "" if src == "内核" else "（源：%s）" % src))
        if unattr_lines:
            func_bad.append(pair)
            for tag, details in unattr:
                print("      [%s]" % tag)
                for sign, ln in details:
                    print("          %s %s" % (sign, ln))

    # ── 台账体检：声明了却 0 命中 = 表笔没接上 ──
    stale_sem = []
    for side, table in (("core", SEMANTIC_CORE), ("orig", SEMANTIC_ORIG)):
        for pat, _rep, _note in table:
            if ("sem:" + pat) not in hits.hits:
                stale_sem.append("%s  %s" % (side, pat))
    stale_drop = []
    for pair, pat, _note in DROP_LEDGER:
        if not any(k.startswith(pair + " :: " + pat) for k in drop_used.hits):
            stale_drop.append("%s  %s" % (pair, pat))
    stale_extra = []
    for pair, pat, _note in EXTRA_LEDGER:
        if not any(k.startswith(pair + " :: ") and re.search(pat, k.split(" :: ", 1)[1])
                   for k in extra_used.hits):
            stale_extra.append("%s  %s" % (pair, pat))
    # 全局改名规则（CANON_BOTH）在**这 27 个冷却函数**里可能合法地 0 命中，
    # 故只作信息项、不计 FAIL —— 它的纪律由整份内核的闸门 1 守。
    idle_canon = [pat for pat, _rep in CANON_BOTH if ("canon:" + pat) not in hits.hits]

    print()
    if skip:
        for s in skip:
            print("   跳过：" + s)
    if stale_sem:
        print("   ★ 语义改写规则陈旧（声明了却 0 命中）：")
        for s in stale_sem:
            print("      " + s)
    if stale_drop:
        print("   ★ 剥离台账陈旧（声明了却 0 命中）：")
        for s in stale_drop:
            print("      " + s)
    if stale_extra:
        print("   ★ 内核新增台账陈旧（声明了却 0 命中）：")
        for s in stale_extra:
            print("      " + s)
    if idle_canon:
        print("   （信息）本次未触达的全局改名规则 %d 条：%s"
              % (len(idle_canon), "；".join(idle_canon[:4]) + "…"
                 if len(idle_canon) > 4 else "；".join(idle_canon)))
    print("   共 %d 对函数；逐行相等 %d 行；已声明剥离 %d 行；内核新增 %d 行；未归因 %d 行"
          % (len(FUNC_PAIRS), same_total, sum(drop_used.hits.values()),
             sum(extra_used.hits.values()), unattr_total))

    for name, note in TENSIONS:
        print()
        print("   ★ 已知张力（报告项，不计 FAIL）%s：" % name)
        for chunk in _wrap(note, 88):
            print("      " + chunk)

    ok = not unattr_total and not stale_sem and not stale_drop and not stale_extra
    print()
    print("COOLDOWN_A: %s" % ("PASS" if ok else "FAIL"))
    return 0 if ok else 1


def pat_of(table, pair, line):
    for p, pat, _note in table:
        if p == pair and re.search(pat, line):
            return pat
    return "?"


def _wrap(text: str, width: int):
    out, cur = [], ""
    for ch in text:
        cur += ch
        if len(cur) >= width:
            out.append(cur)
            cur = ""
    if cur:
        out.append(cur)
    return out


# ─────────────────────────── B. 动态半边 ───────────────────────────

TICK = 1.0 / 60.0
EPS = 1e-9

HEADER = ("key\tcd\tgc0\tseen\tstart_act\ttt0\tic0\tspeed0\tactive_frames\td1_ok\td1_bad\t"
          "n_chg\tc_p_tt\tc_p_ic\tc_p_speed\tc_tt\tc_ic\tt_first\tsp_changes\tstun_frames")
NCOL = len(HEADER.split("\t"))

# 列下标（改表头必须同步改这里）
C_KEY, C_CD, C_GC0, C_SEEN, C_START_ACT = 0, 1, 2, 3, 4
C_TT0, C_IC0, C_SPEED0, C_ACTF, C_D1OK, C_D1BAD = 5, 6, 7, 8, 9, 10
C_NCHG, C_P_TT, C_P_IC, C_P_SP, C_TT, C_IC = 11, 12, 13, 14, 15, 16
C_TFIRST, C_SPCHG, C_STUNF = 17, 18, 19

FIXTURE = os.path.join(ROOT, "gd_core_test", "item_battle_fixture.json")
KITEMS = os.path.join(ROOT, "gd_core_items")

# ── D2 未归因台账 ──
# 首个 iterationCooldown 变更帧若既不满足「递减触发」也不满足「比例缩放」，
# 必须命中本台账：给出**机制**，并且工具会去物品脚本里核实该机制确实存在
# （双向核验：台账项没出现 = 陈旧；出现但脚本里查无此机制 = 台账在掩盖）。
D2_ALLOW = [
    ("Dragon Knight", r"advanceCooldownPercent",
     "onItemActivated → advanceCooldownPercent(cdAdvance)：由物品效果按百分比推进自身冷却，"
     "推进量 reduction = amount/100 × iterationCooldown，触发发生在**这一路**而不是"
     "δ×getSpeed 那一步，故帧边界上反算不出单步公式。该路径本身在 A 段逐行对照过。"),
    ("Robodog", r"setBaseCooldown|updateBaseCooldown",
     "doCooldownEffect → setBaseCooldown(baseCooldownOverride + cdIncrease) → updateBaseCooldown："
     "同一帧里先走 trigger()（+iterationCooldown）再走比例缩放（×新ic/旧ic），"
     "两个已逐行对照过的步骤复合成一个不可从帧边界反算的跳变。"),
]

# ── 观测面为零的解释台账（start_act == 0） ──
# 判据：该物品脚本（或其继承链）的 preCombatStart 体内必须含 deactivateCooldown()。


def _fixture_scripts() -> dict:
    import json
    with open(FIXTURE, encoding="utf-8") as fh:
        data = json.load(fh)
    out = {}
    for key, entry in data["items"].items():
        out[key] = entry["script"].replace("res://", "")
    return out


def _read_kitem(rel_from_res: str) -> str:
    rel = rel_from_res.replace("\\", "/")
    for pre in ("res://", "gd_core_items/"):
        if rel.startswith(pre):
            rel = rel[len(pre):]
    p = os.path.normpath(os.path.join(ROOT, "gd_core_items", *rel.split("/")))
    if os.path.isfile(p) and p.startswith(os.path.normpath(os.path.join(ROOT, "gd_core_items"))):
        with open(p, encoding="utf-8") as fh:
            return fh.read()
    return ""


_KITEM_INDEX = None


def _by_basename(name: str) -> str:
    """按 basename 在 gd_core_items/ 里找脚本（原版 `extends Card` 只给基名）。"""
    global _KITEM_INDEX
    if _KITEM_INDEX is None:
        _KITEM_INDEX = {}
        for dirpath, _dirs, files in os.walk(KITEMS):
            for f in files:
                if f.endswith(".gd"):
                    _KITEM_INDEX.setdefault(f, os.path.relpath(
                        os.path.join(dirpath, f), KITEMS).replace("\\", "/"))
    for cand in (name, name + ".gd"):
        if cand in _KITEM_INDEX:
            return _KITEM_INDEX[cand]
    return ""


def _has_self_deactivate(script_rel: str, seen=None) -> bool:
    """该脚本（或继承链）的 preCombatStart 体内是否有 deactivateCooldown()。"""
    seen = seen or set()
    if script_rel in seen:
        return False
    seen.add(script_rel)
    text = _read_kitem(script_rel)
    if not text:
        return False
    body = extract_funcs_text(text, "preCombatStart")
    if body and re.search(r"deactivateCooldown\(\)", body):
        return True
    m = re.search(r"^extends\s+(\S+)", text, re.M)
    if not m:
        return False
    base = m.group(1).strip().strip('"').replace("res://", "")
    nxt = base if _read_kitem(base) else _by_basename(os.path.basename(base))
    return bool(nxt) and _has_self_deactivate(nxt, seen)


def extract_funcs_text(text: str, name: str) -> str:
    m = re.search(r"^func\s+%s\s*\([^)]*\)[^\n]*\n" % re.escape(name), text, re.M)
    if not m:
        return ""
    rest = text[m.end():]
    stop = re.search(r"^\S", rest, re.M)
    return rest[:stop.start()] if stop else rest


def run_dynamic() -> int:
    print()
    print("B. 逐帧冷却推进恒等式（数据源 %s）"
          % os.path.relpath(DYNAMIC_PATH, ROOT))
    if not os.path.exists(DYNAMIC_PATH):
        print("   缺少数据文件 —— 先跑闸门 9：")
        print("     output/godot36/Godot_v3.6-stable_win64.exe --no-window "
              "--audio-driver Dummy --path gd_core_test --script ItemBattle.gd")
        return 2
    if os.path.getmtime(DYNAMIC_PATH) < os.path.getmtime(CORE_PATH):
        print("   数据文件比 %s 旧 —— 拒绝给旧内核背书。先重跑闸门 9。"
              % os.path.relpath(CORE_PATH, ROOT))
        return 2

    rows = []
    with open(DYNAMIC_PATH, encoding="utf-8") as fh:
        for ln in fh:
            ln = ln.rstrip("\n")
            if not ln:
                continue
            parts = ln.split("\t")
            if parts[0] == "key":
                if ln != HEADER:
                    print("   表头不认识：\n     %s\n     期望：\n     %s" % (ln, HEADER))
                    return 2
                continue
            if len(parts) != NCOL:
                print("   行字段数 %d ≠ %d：%s" % (len(parts), NCOL, ln))
                return 2
            rows.append(parts)

    print("   读完 %d 件带冷却物品（闸门 9 的同 517 场对局，切换驱动方式采样）" % len(rows))
    if not rows:
        print("   数据为空 —— 无观测即无断言，判 FAIL")
        return 1

    scripts = _fixture_scripts()
    fail = []

    # ── 观测面 ──
    never_armed = [r[C_KEY] for r in rows if r[C_SEEN] == "0"]
    zero_obs = [r[C_KEY] for r in rows if r[C_START_ACT] == "0"]
    bad_zero = []
    for k in zero_obs:
        rel = scripts.get(k, "")
        if not rel or not _has_self_deactivate(rel):
            bad_zero.append(k)
    print("   观测面：%d 件装上冷却（从未装上 %d 件）；%d 件装上即被撤（start_act=0）"
          % (len(rows) - len(never_armed), len(never_armed), len(zero_obs)))
    if never_armed:
        fail.append("从未装上冷却（seen=0）：%s" % ", ".join(never_armed[:8]))
    if bad_zero:
        fail.append("「装上即撤」但脚本里查不到 `preCombatStart` → `deactivateCooldown()`：%s"
                    % ", ".join(bad_zero[:8]))
    elif zero_obs:
        print("     └ 全部 %d 件均由 `preCombatStart(): .preCombatStart(); deactivateCooldown()`"
              " 解释（Card 系继承或自声明）✓" % len(zero_obs))

    # ── D1 ──
    d1_ok = sum(int(r[C_D1OK]) for r in rows)
    d1_bad = sum(int(r[C_D1BAD]) for r in rows)
    bad_d1 = [r[C_KEY] for r in rows if int(r[C_D1BAD])]
    if bad_d1:
        fail.append("D1 违背的 %d 件：%s" % (len(bad_d1), ", ".join(bad_d1[:8])))
    print("   D1 `triggerTime -= δ × getSpeed()`：成立 %d 帧 / 违背 %d 帧" % (d1_ok, d1_bad))
    if not d1_ok:
        fail.append("D1 一帧都没成立 —— 表笔没接上（无观测即无断言）")

    # ── D2 ──
    n_chg_items = [r for r in rows if int(r[C_NCHG]) > 0]
    bucket = {"A": [], "B": [], "X": []}
    for r in n_chg_items:
        c_p_tt, c_p_ic, c_p_sp = float(r[C_P_TT]), float(r[C_P_IC]), float(r[C_P_SP])
        c_tt, c_ic = float(r[C_TT]), float(r[C_IC])
        dec = c_p_tt - TICK * c_p_sp
        if abs(c_tt - (dec + c_ic)) <= EPS:
            bucket["A"].append(r[C_KEY])
        elif (c_p_ic and (abs(c_tt - (c_p_tt / c_p_ic) * c_ic) <= EPS
                          or abs(c_tt - (dec / c_p_ic) * c_ic) <= EPS)):
            bucket["B"].append(r[C_KEY])
        else:
            bucket["X"].append(r[C_KEY])
    print("   首个 iterationCooldown 变更帧：%d 件观测到" % len(n_chg_items))
    print("     A 递减触发 `tt == tt⁻ − δ·speed + ic`          %d 件" % len(bucket["A"]))
    print("     B 比例缩放 `updateBaseCooldown`                %d 件" % len(bucket["B"]))
    print("     X 需台账归因                                  %d 件 %s"
          % (len(bucket["X"]), bucket["X"]))
    allow_hit = set()
    for name, mech, _note in D2_ALLOW:
        if name in bucket["X"]:
            allow_hit.add(name)
            if not _script_has_mechanism(scripts.get(name, ""), mech):
                fail.append("D2 台账项 %s 声称机制 /%s/，但物品脚本里查不到" % (name, mech))
    stale = [n for n, _m, _x in D2_ALLOW if n not in allow_hit]
    if stale:
        fail.append("D2 台账陈旧（声明了却没出现）：%s" % ", ".join(stale))
    unattr = [n for n in bucket["X"] if n not in {a[0] for a in D2_ALLOW}]
    if unattr:
        fail.append("D2 未归因 %d 件：%s" % (len(unattr), ", ".join(unattr[:8])))
    if not n_chg_items:
        fail.append("D2 一件都没观测到冷却变更 —— 表笔没接上")
    for name, mech, note in D2_ALLOW:
        if name in allow_hit:
            print("       · %s（机制 /%s/ 已在脚本里核实）：%s" % (name, mech, note[:56] + "…"))

    # ── D3（抖动指纹）──
    ratios = []
    for r in rows:
        gc0 = float(r[C_GC0])
        if r[C_START_ACT] == "0" or gc0 == 0.0:
            continue
        ratios.append((r[C_KEY], float(r[C_IC0]) / gc0))
    rmin = min(x for _k, x in ratios)
    rmax = max(x for _k, x in ratios)
    nuniq = len({round(x, 12) for _k, x in ratios})
    print("   D3 抖动指纹 `iterationCooldown / getCooldown()` ∈ [%.6f, %.6f]，取值 %d 种"
          % (rmin, rmax, nuniq))
    off = [(k, x) for k, x in ratios if not (0.95 - 1e-9 <= x <= 1.05 + 1e-9)]
    if off:
        fail.append("D3 越出原版 randf_range(0.95, 1.05) 区间：%s" % off[:5])
    if nuniq < 2:
        fail.append("D3 比值只有 %d 种取值 —— 随机因子没取（退化成固定 cd 语义）" % nuniq)

    # ── 首触发时刻 vs 状态链预测（报告项）──
    hits = 0
    tot = 0
    for r in rows:
        t1 = float(r[C_TFIRST])
        if t1 < 0.0 or r[C_START_ACT] == "0":
            continue
        sp0 = float(r[C_SPEED0])
        ticks_pred = float(r[C_TT0]) / sp0 / TICK if sp0 > 0 else 0.0
        tot += 1
        if abs(t1 / TICK - ticks_pred) <= 2.0:
            hits += 1
    print("   首触发时刻 ∈ 状态链预测（±2 tick）：%d/%d" % (hits, tot))

    print()
    if fail:
        for f in fail:
            print("   B FAIL  " + f)
        print("COOLDOWN_B: FAIL (%d 项)" % len(fail))
        return 1
    print("COOLDOWN_B: PASS")
    return 0


def _script_has_mechanism(script_rel: str, mech: str) -> bool:
    if not script_rel:
        return False
    return bool(re.search(mech, _read_kitem(script_rel)))


def main() -> int:
    rc_a = run_static()
    if "--static" in sys.argv:
        return rc_a
    rc_b = run_dynamic()
    print()
    print("=" * 60)
    print("verify_cooldowns 等价校验：%s"
          % ("PASS" if rc_a == 0 and rc_b == 0 else "FAIL"))
    return 0 if rc_a == 0 and rc_b == 0 else 1


if __name__ == "__main__":
    raise SystemExit(main())
