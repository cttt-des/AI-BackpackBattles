# -*- coding: utf-8 -*-
"""build_item_scripts.py — 把原版 Items/*.gd 转译为「直挂 CoreItem」的无头行为脚本

================ 为什么这么做 ================
gd_core 已经把战斗主干（冷却/触发/激活 + 伤害链 + Buff + 疲劳/判胜）逐行移植完毕，
判定路径的方法面已基本完整（**当前缺口数以 `tools/gd_core_coverage.py` 现场核算为准**，
不要在此写死 —— 曾写死「缺口为 0」，后来新增 `initSockets` 等项后就成了假断言）。
既然方法面已完整，就没有必要再维护第二套「转译成别的语言」的行为产物：直接让原版
物品脚本**继承 CoreItem** 跑，忠实度最高（行为代码逐字未改），且最精简（无中间层）。

================ 转译规则（每条都能对回源码行号）================
R1  extends 重写
      `extends Item` / `extends Weapon` …            → 原样保留（靠 class_name 解析）
      `extends "res://Items/X.gd"`                   → `extends "res://gd_core_items/X.gd"`
      非物品脚本（extends 链到不了 Item）             → 跳过
R2  onready var 求值时机
      原版 `onready var X := expr` 由节点 `_ready` 触发赋值；内核无场景树。
      统一收集进合成函数 `_readyInit()`（内容顺序 = 源码出现顺序），
      由装配层在「物品挂好 ctx/descriptor/inventory 之后」调用一次。
R3  func _ready()
      原版 `_ready` 里含判定必需的初始化（如 Weapon 建 damageSource）。
      合并进 `_readyInit()`，且**排在 onready 赋值之后**（原版 onready 先于 _ready）。
      子类 `_readyInit()` 开头写 `.()` 调父类同名函数（GDScript 3 基类调用语法），
      父先子后，与原版 `_ready` 的隐式父类优先一致。
R4  符号映射（表达式级，控制流一行不动）
      枚举/常量类  → CoreConst.* / CoreDamageSource / CoreDamageResult
      单例类       → ctx.util. / ctx.bus. / ctx.rng / ctx.hooks.*
      视觉类       → ctx.hooks.*（空实现，**替换而非删除**，故控制流零改动）
R5  节点模态引用（sprite / animation / $Xxx / get_node …）
      这类是场景树对象，无法用空钩子替代（属性读写与方法调用都会崩）。
      所在**函数整函数剥离为空桩**（保留签名，避免调用点 `Nonexistent function`），
      并计入报告。若该函数属战斗路径，报告中标 ★ 供人工定裁。

用法：
    python tools/build_item_scripts.py            # 生成到 gd_core_items/
    python tools/build_item_scripts.py --dry-run  # 只出报告，不写文件
"""
from __future__ import annotations

import collections
import io
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, "decompiled_full", "Items")
OUT = os.path.join(ROOT, "gd_core_items")
# 基类在 Items/ 内的相对名。★ 模块级常量：`shim_header()` 等模块级函数也要用，
# 早先只在 main() 里当局部变量，导致生成文件头时 NameError。
ITEM_BASE = "Item.gd"
REPORT = os.path.join(ROOT, "output", "port", "item_build_report.txt")

# 顶格内嵌类声明 `class X:`
INNER_CLASS_RE = re.compile(r"^class\s+([A-Za-z_]\w*)\s*:")
# 函数声明**首行**识别（`static` 可选、签名可折行，故只要求出现 `func 名(`）
FUNC_HEAD_RE = re.compile(r"^(\s*)(?:static\s+)?func\s+([A-Za-z_]\w*)\s*\(")
# 单行完整签名（`static` 可选）
FUNC_RE = re.compile(
    r"^(\s*)(?:static\s+)?func\s+([A-Za-z_]\w*)\s*\(([^)]*)\)(\s*->[^:]*)?:")
EXT_RE = re.compile(r"^extends\s+([^\n#]+)", re.M)
ONREADY_RE = re.compile(
    r"^(\s*)onready\s+var\s+([A-Za-z_]\w*)\s*(?::\s*[^=]+?)?\s*(:?=.*)?$")
VAR_RE = re.compile(r"^(\s*)var\s+([A-Za-z_]\w*)")
NODE_MODAL_RE = re.compile(r"^\s*onready\s+var\s+([A-Za-z_]\w*)\s*:?=\s*\$(.+)", re.M)

# ── R5：节点模态（从原版基类 `onready var X = $Node` 自动提取，见 extract_node_modals）──
NODE_MODALS: set[str] = set()
TIMER_MODAL_NAMES: set[str] = set()
# 内核基类已声明的成员名（避免子类重复声明遮蔽）
CORE_MEMBERS: set[str] = set()
# R3b 第一类：原版 Item.gd 有、CoreItem 没有的「壳成员」
SHELL_MEMBERS: set[str] = set()
# R3b 第二类：本文件里因引用外部子系统类而被删掉的顶层声明名（**逐文件重算**）
DROP_SYMBOLS: set[str] = set()

# ── R6：计时器 ──
# 物品 tscn 里的 XxxTimer 子节点承载 buff 时长（判定），不能当视觉剥掉。
# 转译器解析同名 tscn 的 [node] / [connection]，把它改写成虚拟计时器创建调用。
TSCN_NODE_RE = re.compile(r'\[node name="([^"]+)"\s+type="([^"]+)"')
TSCN_CONN_RE = re.compile(
    r'\[connection\s+signal="([^"]+)"\s+from="([^"]+)"\s+to="([^"]+)"\s+method="([^"]+)"\s*\]')
DOLLAR_RE = re.compile(r"^\s*\$\s*([A-Za-z_]\w*)")

# 生成的赋值形式：X = newItemTimer("节点名", "回调方法", 是否叠加)
TIMER_ASSIGN = ('%s = newItemTimer("%s", "%s", %s)')

# ── R4c：类型名映射 ──
# 物品脚本对内核类型做标注/构造（`var res: DamageResult = ...` / `DamageResult.new()`）。
# 这些是类型改名，不是行为改动。
TYPE_TOKEN_MAP = {
    "DamageResult": "CoreDamageResult",
    "DamageSource": "CoreDamageSource",
    "ItemDescriptor": "CoreItemData",
}

# ── R7：残留外部符号兜底 ──
# 映射后仍出现的「大写名.」说明该函数依赖商店/UI/制作系统（原版这些方法只从
# 商店与拖拽流程调用，不参与战斗判定）。整函数剥离为空桩并计入报告；
# 若该函数在 BATTLE_FUNCS 里，报告中标 ★ 供人工定裁。
MAPPED_OK = {
    "CoreConst", "CoreUtil", "CoreItem", "CoreCharacter", "CoreGrid", "CoreTimer",
    "CoreDamageSource", "CoreDamageResult", "CoreCombat", "CoreCombatLog",
    "CoreContext", "CoreItemData", "CoreEvent", "CoreEventBus", "CoreBuff",
    "CoreHooks", "CoreRng",
}

# 引擎内建类型 / 全局单例函数（GDScript 3 的全局命名空间里本就存在）
ENGINE_LIKE = {
    "Node", "Node2D", "RigidBody2D", "Area2D", "Sprite", "Reference", "Object",
    "Timer", "Tween", "SceneTree", "SceneTreeTween", "Engine", "OS", "Input",
    "Resource", "PackedScene", "Image", "ImageTexture", "Label", "ColorRect",
    "Control", "AnimationPlayer", "Particles2D", "CPUParticles2D",
    "AudioStreamPlayer", "CollisionShape2D", "CollisionPolygon2D",
    "RectangleShape2D", "CanvasItem", "Texture", "Vector2", "Vector3", "Rect2",
    "Color", "Transform2D", "Basis", "Quat", "Array", "Dictionary", "String",
    "PoolStringArray", "PoolByteArray", "PoolIntArray", "PoolRealArray",
    "PoolVector2Array", "PoolColorArray", "File", "Directory", "JSON",
    "Marshalls", "RandomNumberGenerator", "Viewport", "RichTextLabel",
    "TextureRect", "StreamTexture", "AtlasTexture", "DynamicFont", "Font",
    "Theme", "CanvasLayer", "ShaderMaterial", "Material", "Gradient", "Curve",
    "Path2D", "Line2D", "Polygon2D", "Light2D", "Camera2D", "Performance",
    "ProjectSettings", "Thread", "Mutex", "WeakRef", "MainLoop", "TileMap",
    "VisibilityNotifier2D", "Groups", "Math", "PI", "TAU", "INF", "NAN",
    "TranslationServer", "RemoteTransform2D", "Position2D", "BackBufferCopy",
    "PhysicsMaterial", "SubResource", "Range", "ProgressBar", "Panel", "NodePath",
    "FuncRef", "GDScript", "Script", "SceneState", "MultiMesh", "Mesh",
}
RESIDUAL_RE = re.compile(r"(?<![\w.\"])([A-Z][A-Za-z0-9_]*)\s*\.")

# 解析期可用的**类型名**白名单（用于擦除解析不了的类型标注）。
# 引擎内建 + 内核类 + GDScript 值类型；其余（Socket / BitStream / WeightedBag …）
# 都是没随物品脚本转译的外部子系统类，标注必须擦掉。
KNOWN_TYPE_NAMES = set(ENGINE_LIKE) | set(MAPPED_OK) | {
    "Object", "Reference", "Variant", "int", "float", "bool", "String",
    "Array", "Dictionary", "Vector2", "Vector3", "Color", "Rect2",
    "Transform2D", "NodePath", "PoolStringArray", "PoolByteArray",
    "PoolIntArray", "PoolRealArray", "PoolVector2Array", "PoolColorArray",
    "void", "FuncRef", "RID", "Quat", "Basis", "AABB", "Plane",
    "Resource", "Texture", "Shape2D", "InputEvent", "Node", "Node2D",
}

# ── 适配层 `gd_core_items/Item.gd` 的文件头 ──
#
# ★ 文件头里的每个数字都在**生成时现算**，不留字面量。
#   本节曾写死「6573 行 / 628 方法」「469 个物品脚本」「判定路径缺口为 0」三项，
#   而这三项都会随代码演进变成**假断言**（写死时 469 个直接/间接子类，
#   2026-09-23 实测只有 238 个直接 `extends Item`；判定路径缺口当时也已不是 0）。
#   更糟的是本文件头自称「内容随代码同步」—— 只有现算才对得起这句话。
#
#   覆盖率与判定路径缺口由 `tools/gd_core_coverage.py` 现场核算，
#   且已作为闸门 1（`tools/audit_gd_core.py`）的输入之一 —— **不要在注释里断言**。

_EXTENDS_RE = re.compile(r'^extends\s+(.+?)\s*$')


def _count_direct_item_subclasses(outputs):
    """统计 generated 脚本里直接继承 `Item` 的个数（含 `extends "res://.../Item.gd"`）。"""
    n = 0
    for rel, text in outputs.items():
        if rel == ITEM_BASE:
            continue
        for ln in text.split("\n"):
            s = ln.strip()
            if not s.startswith("extends"):
                continue
            m = _EXTENDS_RE.match(s)
            if m:
                base = m.group(1).strip().strip('"')
                if base == "Item" or base.endswith("/Item.gd"):
                    n += 1
            break
    return n


def shim_header(outputs):
    """生成适配层文件头（数字全部现算，见上方说明）。"""
    # ★ ITEM_BASE 已含扩展名（"Item.gd"），不要再拼 ".gd"
    src = os.path.join(SRC, ITEM_BASE)
    n_lines = n_funcs = 0
    if os.path.exists(src):
        with io.open(src, encoding="utf-8", errors="replace") as fh:
            for ln in fh:
                n_lines += 1
                if ln.startswith("func "):
                    n_funcs += 1
    n_total = sum(1 for rel in outputs if rel != ITEM_BASE)
    n_direct = _count_direct_item_subclasses(outputs)
    return '''# =============================================================================
# Item.gd — 物品基类适配层（**自动生成，勿手改**）
# 生成器：tools/build_item_scripts.py
# =============================================================================
# 原版 `Items/Item.gd` 是 {lines} 行 / {funcs} 方法的 RigidBody2D：战斗主干 + 拖拽物理
# + 粒子音效 + 商店存档混在一起。战斗主干已逐行移植进 `gd_core/CoreItem.gd`，
# 本文件承载**CoreItem 之外的剩余面**，使 {total} 个原版物品脚本（其中 {direct} 个
# 直接 `extends Item`，其余经 `Weapon`/`Bag`/`Gem`/`Card` 等中间类间接继承）
# 能逐字不改地跑在无头内核里。
#
# ★ 本注释里的数字**全部在生成时现算**；覆盖率与「判定路径缺口」不在注释里断言，
#   以 `tools/gd_core_coverage.py` 的现场核算为准（见 tools/run_gd_core.py 闸门）。
#
# 生成方式（不是手写）：把原版 Item.gd 过一遍与物品脚本相同的转译流水线，
# 再与 CoreItem 求差 —— 同名函数/成员/常量/枚举一律丢弃（**内核版本权威**），
# 其余照搬。视觉调用已由通用规则剥成 `ctx.hooks.*` 空钩子或空桩；
# 剥空的块由 ensure_blocks_nonempty() 补 `pass`，故块结构始终合法。
# =============================================================================
'''.format(lines=n_lines, funcs=n_funcs, total=n_total, direct=n_direct)


def load_tscn_index():
    """返回 {物品相对路径(不含扩展): {'nodes': {名: 类型}, 'conns': [(sig, from, method, to)]}}"""
    idx = {}
    for dirpath, _dirs, files in os.walk(SRC):
        for fn in files:
            if not fn.endswith(".tscn"):
                continue
            path = os.path.join(dirpath, fn)
            rel = os.path.relpath(path, SRC).replace(os.sep, "/")[:-5]
            try:
                with io.open(path, encoding="utf-8", errors="replace") as fh:
                    body = fh.read()
            except OSError:
                continue
            nodes = {}
            for m in TSCN_NODE_RE.finditer(body):
                nodes[m.group(1)] = m.group(2)
            conns = []
            for m in TSCN_CONN_RE.finditer(body):
                conns.append((m.group(1), m.group(2), m.group(4), m.group(3)))
            idx[rel] = {"nodes": nodes, "conns": conns}
    return idx


def timer_spec(tscn_info, node_name: str):
    """查某 Timer 节点的 (回调方法, 是否叠加)。无连接则回调为空。"""
    if tscn_info is None:
        return ("", False)
    for sig, frm, method, to in tscn_info["conns"]:
        if frm == node_name and to == ".":
            return (method, sig == "multi_timeout")
    return ("", False)


def is_timer_node(tscn_info, node_name: str) -> bool:
    if tscn_info is None:
        return False
    return tscn_info["nodes"].get(node_name) == "Timer"


def collect_in_file_names(body: str) -> set:
    """本文件定义的 enum / const / class_name / signal / var / func 名（本文件内可见）。"""
    names = set()
    for m in re.finditer(r"^\s*enum\s+([A-Za-z_]\w*)", body, re.M):
        names.add(m.group(1))
    for m in re.finditer(r"^\s*const\s+([A-Za-z_]\w*)", body, re.M):
        names.add(m.group(1))
    for m in re.finditer(r"^\s*class_name\s+([A-Za-z_]\w*)", body, re.M):
        names.add(m.group(1))
    for m in re.finditer(r"^\s*signal\s+([A-Za-z_]\w*)", body, re.M):
        names.add(m.group(1))
    for m in re.finditer(r"^\s*(?:onready\s+)?var\s+([A-Za-z_]\w*)", body, re.M):
        names.add(m.group(1))
    # 函数名也算「本文件可见」：默认参数值可能是 `= someLocalHelper()`
    for m in re.finditer(r"^\s*(?:static\s+)?func\s+([A-Za-z_]\w*)", body, re.M):
        names.add(m.group(1))
    return names


def residual_symbols(code: str, allowed: set) -> set:
    """返回映射后仍无法解析的外部「大写名」（去掉字符串与注释后判定）。"""
    out = set()
    for m in RESIDUAL_RE.finditer(code):
        n = m.group(1)
        if n in MAPPED_OK or n in allowed:
            continue
        out.add(n)
    return out


def first_residual_line(kept_lines: list, res: set) -> str:
    """找出第一个含残留符号的行（报告用）。"""
    for ln in kept_lines:
        code = re.sub(r"#[^\n]*", "", ln)
        for m in RESIDUAL_RE.finditer(code):
            if m.group(1) in res:
                return ln.strip()[:62]
    return ""
EXTRA_NODE_TOKENS = [
    r"\$", r"get_node\s*\(", r"get_parent\s*\(", r"add_child\s*\(",
    r"\bqueue_free\s*\(", r"\bphysics_material_override\b", r"\bcollision_layer\b",
    r"\bcollision_mask\b", r"\blinear_velocity\b", r"\bangular_velocity\b",
    r"\bapply_impulse\s*\(", r"\bglobal_position\b", r"\bglobal_rotation\b",
    r"\bglobal_scale\b", r"\bz_index\b", r"\bmodulate\b", r"\bself_modulate\b",
    r"\bmaterial\b", r"\bshader_param\b", r"\bset_shader_param\s*\(",
    r"\bSceneTreeTween\b", r"\.interpolate_property\s*\(", r"\.tween_property\s*\(",
    r"\bcreate_tween\s*\(", r"\bTween\s*\(", r"\bparticles\b", r"\bParticles2D\b",
    r"\bCPUParticles2D\b", r"\bAnimationPlayer\b", r"\bplay\s*\(",
    # ── RigidBody2D / Node2D / CanvasItem / Sprite 的**物理与表现属性** ──
    # 这些属性在内核里不存在（CoreItem extends Reference）。它们出现在
    # `initPhysicsMaterial()`、`_ready()`、拖拽/粒子回调里，属场景耦合；
    # 逐行判定的判据要认得它们，否则整段物理初始化会被当成判定代码保留，
    # 解析报 `The identifier "mass" isn't declared in the current scope`。
    # ★ 加 `(?<![\w.])` 前置守卫，避免误伤 `baseMass` / `sprite.mass` 这类形式。
    #
    # ★★ `rotation` **刻意不在此列**：它是内核的权威判定字段
    #    （CoreItem 里由 faceDirection 导出，见其注释），
    #    ChessPiece.prepare 用 `cell.rotated(rotation)` 算棋子的移动格 —— 属判定。
    #    曾经把它列进来，直接把 ChessPiece.prepare 误判为视觉并整函数剥离。
    r"(?<![\w.])mass\b", r"\bgravity_scale\b", r"\blinear_damp\b",
    r"\bangular_damp\b", r"(?<![\w.])friction\b", r"(?<![\w.])bounce\b",
    r"\bcan_sleep\b", r"\bcontact_monitor\b", r"\bcontacts_reported\b",
    r"\bcontinuous_cd\b", r"\bcustom_integrator\b", r"\binertia\b",
    r"\bsleeping\b", r"\bapplied_force\b", r"\bapplied_torque\b",
    r"\bset_collision_layer\b", r"\bset_collision_mask\b",
    r"\bset_collision_layer_bit\b", r"\bset_collision_mask_bit\b",
    r"\bset_process\b", r"\bset_physics_process\b", r"\bset_process_input\b",
    r"\bset_process_unhandled_input\b",
    r"(?<![\w.])scale\b", r"\brotation_degrees\b",
    r"(?<![\w.])offset\b", r"\bpivot_offset\b", r"\brect_position\b",
    r"\brect_size\b", r"\brect_scale\b", r"\bz_as_relative\b", r"\blight_mask\b",
    r"(?<![\w.])texture\b", r"\bregion_rect\b", r"(?<![\w.])frame\b",
    r"\bspeed_scale\b", r"\bautoplay\b", r"\bvolume_db\b",
    r"(?<![\w.])stream\b", r"(?<![\w.])emitting\b", r"\bone_shot\b",
    r"\binitial_velocity\b", r"(?<![\w.])spread\b", r"\bpercent_visible\b",
    r"\bPhysics2DDirectBodyState\b", r"\bInputEvent\b",
    # ── Node 专有方法（CoreItem extends Reference，没有这些） ──
    r"\bget_node_or_null\s*\(", r"\bget_children\s*\(", r"\bis_in_group\s*\(",
    r"\bfind_node\s*\(", r"\bget_tree\s*\(", r"\bset_as_toplevel\s*\(",
    r"\bto_global\s*\(", r"\bto_local\s*\(", r"\bget_global_transform\s*\(",
    r"\bset_cellv\s*\(", r"\bget_used_cells_by_id\s*\(", r"\bset_deferred\s*\(",
    r"\.tween_method\s*\(", r"\.tween_callback\s*\(", r"\.tween_property\s*\(",
    r"\bset_visible\s*\(", r"(?<![\w.])hide\s*\(", r"(?<![\w.])show\s*\(",
    r"\bYSort\b", r"\bCanvasLayer\b", r"\bGridContainer\b", r"\bViewport\b",
]

# ── R4：枚举 / 类常量 映射（判定路径必须等价，不能丢）──
ENUM_MAP = {
    "Type.": "CoreConst.Type.",
    "Affected.": "CoreConst.Affected.",
    "FaceDirection.": "CoreConst.FaceDirection.",
    "Rarity.": "CoreConst.Rarity.",
    "Owner.": "CoreConst.Owner.",
    "StatModified.": "CoreConst.StatModified.",
    "Priority.": "CoreConst.Priority.",
    "CraftingPriority.": "CoreConst.CraftingPriority.",
    "StuffedClasses.": "CoreConst.StuffedClasses.",
    "Tag.": "CoreConst.Tag.",
    "Stack.": "CoreConst.Stack.",
    "StackChangeType.": "CoreConst.StackChangeType.",
    # ★ 刻意**不映射** `GemMode.`：它不是全局枚举，而是 `Items/Gems/Gem.gd:16`
    #   的**文件内枚举**（Weapon/Armor/Inventory/Inactive）。转译只做符号搬家、
    #   不改语义 —— Gem.gd 自己保留 `enum GemMode{`，其子类（Wisp / BadgerRune /
    #   BurningCoal …共 22 支）照原版裸写 `GemMode.X`，靠 GDScript 的常量继承解析。
    #   曾经把它映射到 `CoreConst.GemMode.`（CoreConst 里并无此项），
    #   于是 268 处 `Invalid get index 'GemMode'` —— 而 getGemMode() 是宝石
    #   「嵌在武器/护甲/背包上分别走哪条 prepare 分支」的唯一判据，
    #   报错即整个宝石行为链断掉（只有逐件真打的闸门才抓得到）。
    "Character.StaminaResult.": "CoreConst.StaminaResult.",
    "StaminaResult.": "CoreConst.StaminaResult.",
    "DamageSource.": "CoreDamageSource.",
    "DamageResult.": "CoreDamageResult.",
    "Item.Type.": "CoreConst.Type.",
    "Item.Rarity.": "CoreConst.Rarity.",
    "Item.Owner.": "CoreConst.Owner.",
    "Item.Stat.": "CoreConst.ItemStat.",
    "Stat.": "CoreConst.ItemStat.",
}

# ── R4：单例 → ctx 成员（判定语义，必须精确映射）──
SINGLETON_MAP = {
    "Util.": "ctx.util.",
    "EventBus.": "ctx.bus.",
}

# `Util.rng` 要单独先替换（否则会被 Util. 规则变成 ctx.util.rng，语义错）
PRE_MAP = {
    "Util.rng": "ctx.rng",
    "Game.PLAYER": "ctx.player",
    "Game.OPPONENT": "ctx.opponent",
    "Game.combatLog": "ctx.combat_log",
    # ── Game 上的战斗相关**状态量**（原版是 autoload 成员，内核放到 ctx）──
    # ★ `Game.combatTimer` 是 CombatTimer 单例节点：物品脚本用
    #   `connectForCombat(Game.combatTimer, "fatigue_start", "onFatigueStarted")`
    #   订阅疲劳信号（Pumpkin / PoweroftheMoon / ArtifactStoneDeath）。
    #   EventBus 按 emitter.get_instance_id() 配对，而疲劳信号正是 CoreCombat
    #   用 self 发出的，故必须映射到 ctx.combat（由 CoreCombat._init 回填）。
    "Game.combatTimer": "ctx.combat",
    "Game.sandbagActive": "ctx.sandbag_active",
    "Game.curMode": "ctx.cur_mode",
    "Game.curRound": "ctx.cur_round",
    # ★ `Game.cubeAdvanced` / `Game.ropeSpeedups` 是 Game 上的战斗内运行期字典
    #   （Game.gd:388-389），跨回合会残留，故清空点必须一并对齐
    #   （Game.gd:3330-3331 → CoreCombat.combatEndDeferred）。消费方：
    #   Cube/BismuthCube/PlasticCube（同一物品被第二个方块推进冷却要乘 penaltyFactor）、
    #   Rope（夹住 maxSpeed 上限并在到期时按同量回收）。
    "Game.cubeAdvanced": "ctx.cube_advanced",
    "Game.ropeSpeedups": "ctx.rope_speedups",
    # ★ `Game.eventTypeKeys` = Util.invertDictionary(EventType)（Game.gd:512）。
    #   **不是纯文本**：MagicRing.giveStacksFromEffect 用它把 effect.stackType 转成
    #   参数名再喂 getP() 取战斗数值（MagicRing.gd:107-109）。
    "Game.eventTypeKeys": "ctx.event_type_keys",
    # ★ 全局伤害源（Game.gd:2426-2433 构造；内核在 CoreContext._init 逐行对齐）。
    #   fatigueDamageSource 被 ArtifactStoneDeath 读 minDamage 算疲劳增量；
    #   stealLifeDamageSource 被 CoreItem.stealLife 用（item.py 侧同源）。
    "Game.stealLifeDamageSource": "ctx.stealLifeDamageSource",
    "Game.fatigueDamageSource": "ctx.fatigueDamageSource",
    # ★ 出体力累计次数：Item.gd:4208 在 playOutOfStaminaAnimation 里累加，
    #   Game.gd:3366 与 Shopkeeper.gd:102 在**局外**消费（联赛判罚）。映射后
    #   战斗内只是个忠实副作用，不改变任何战斗判定。
    "Game.numTimesOutOfStamina": "ctx.out_of_stamina_count",
    # ★ `Game.combatSceneNode.advanceTime(t)`（PoweroftheMoon.onPostCombatStart）：
    #   Combat.gd:920-923 的实体只有第一句是真效果 —— `Game.combatTimer.advanceTime(time)`，
    #   其余是背景动画倍速与动画计时器（表现层）。内核里 `ctx.combat` 就是那个
    #   combatTimer，且 CoreCombat.advanceTime 已按 CombatTimer.gd:184-196 实现。
    "Game.combatSceneNode.advanceTime(": "ctx.combat.advanceTime(",
    # ★ `Util.time` / `Util.frameCounter` 是 Util 上的全局累加量（Util.gd:3-4），
    #   内核把同一物理帧累加量放在 ctx 上（advancePhysicsFrame），故要重定向；
    #   若走 Util. → ctx.util. 的兜底规则会变成不存在的方法。
    "Util.time": "ctx.time",
    "Util.frameCounter": "ctx.frame_counter",
}

# ── R4b：Game 上的**判定相关**静态辅助（对齐 Game.gd:5643-5660，内核已在 CoreConst 提供）──
# 这些被物品行为大量使用（`Game.EventType.Cold` 等 162 处），必须精确映射。
GAME_STATIC_MAP = {
    "Game.EventType.": "CoreConst.EventType.",
    "Game.Classes_Full.": "CoreConst.Classes_Full.",
    "Game.Classes.": "CoreConst.Classes.",
    "Game.Mode.": "CoreConst.GameMode.",
    "Game.getBuffs(": "CoreConst.getBuffs(",
    "Game.getDebuffs(": "CoreConst.getDebuffs(",
    "Game.getStacks(": "CoreConst.getStacks(",
    "Game.isBuff(": "CoreConst.isBuff(",
    "Game.isDebuff(": "CoreConst.isDebuff(",
    "Game.isStack(": "CoreConst.isStack(",
}

# ── R4：纯视觉单例 → 空钩子（替换而非删除）──
VISUAL_SINGLETON_MAP = {
    "Sound.playSound_process": "ctx.hooks.playSoundProcess",
    "Sound.playSound": "ctx.hooks.playSound",
    "ObjectPool.particleOneShot": "ctx.hooks.particleOneShot",
    "ObjectPool.returnInstance": "ctx.hooks.poolReturnInstance",
    "ObjectPool.instance": "ctx.hooks.poolInstance",
}

# ── R5：战斗路径函数名（这些函数里若只剩视觉语句，必须报 ★ 供人工定裁）──
BATTLE_FUNCS = {
    "prepare", "onPrepare", "onPreCombatStart", "onCombatStart", "onCombatEnd",
    "doCooldownEffect", "doActivation", "canAffect", "canAffect_secondary",
    "canAffect_tertiary", "canAffect_lightning", "canAffect_color",
    "onDealtDamage", "onDamaged", "onPreDealDamage_early", "onPreDealDamage",
    "onPostDealDamage", "onAttack", "onStun", "onStunned", "onKill", "onDeath",
    "getTriggerPriority", "onStateChanged", "onStackChanged", "onBuffApplied",
    "onChargeReceived", "onItemAdded", "onItemRemoved", "onAffectedItemAdded",
    "onAffectedItemRemoved", "isAffectingDistinct", "affectsEmpty", "canBlock",
    "canHealOrLifesteal", "reactsToCharges", "onTriggerPotion", "consumePotion",
    "onTrigger", "onActivate", "activate", "reactToItemTypeChange",
}


def collect() -> dict:
    out = {}
    for dirpath, _dirs, files in os.walk(SRC):
        for fn in files:
            if not fn.endswith(".gd"):
                continue
            path = os.path.join(dirpath, fn)
            rel = os.path.relpath(path, SRC).replace(os.sep, "/")
            with io.open(path, encoding="utf-8", errors="replace") as fh:
                out[rel] = fh.read()
    return out


def strip_str_comments(body: str) -> str:
    body = re.sub(r"#[^\n]*", "", body)
    body = re.sub(r'"(?:[^"\\]|\\.)*"', '""', body)
    return body


def extract_node_modals(scr: dict) -> set:
    """从基类脚本的 `onready var X = $Node`、`onready var X = <模态>.属性` 提取节点模态名。

    做**传递闭包**：`onready var fluid = $Fluid` 与 `onready var fluidMat = fluid.material`
    都是节点派生值，后续 `fluidMat.set_shader_param(...)` 同样属视觉。
    """
    pat = re.compile(r"^\s*onready\s+var\s+([A-Za-z_]\w*)\s*(?::\s*[^=]+?)?\s*:?=\s*(.+)$", re.M)
    pairs = []
    for _rel, body in scr.items():
        for m in pat.finditer(body):
            pairs.append((m.group(1), m.group(2).strip()))

    modals = set()
    for name, rhs in pairs:
        if rhs.startswith("$"):
            modals.add(name)
    changed = True
    while changed:
        changed = False
        for name, rhs in pairs:
            if name in modals:
                continue
            m2 = re.match(r"^(?:self\.)?([A-Za-z_]\w*)\s*[\.\[]", rhs)
            if m2 and m2.group(1) in modals:
                modals.add(name)
                changed = True
    for name, rhs in pairs:
        if any(rhs.startswith(p) for p in VISUAL_CALL_PREFIXES):
            modals.add(name)
    # ★ 非 onready 的赋值也算：`fluidTween = Util.refreshTween(fluidTween)` 之后
    #   `fluidTween.tween_property(...)` 同属视觉。漏掉这条，Laboratory.onStateChanged
    #   里 `fluidTween.tween_property` 会命中 `\bplay\s*\(`/tween 令牌变成 mixed，
    #   把开头的 `baseCooldownOverride = getBaseCooldownIndex(phase)`（**冷却覆写，
    #   判定**）连带剥掉。
    pat_assign = re.compile(
        r"^\s*(?:self\.)?([A-Za-z_]\w*)\s*=\s*([^\n=].*)$", re.M)
    for _rel, body in scr.items():
        for m in pat_assign.finditer(body):
            name, rhs = m.group(1), m.group(2).strip()
            if any(rhs.startswith(p) for p in VISUAL_CALL_PREFIXES):
                modals.add(name)
    return modals


def group_statements(lines: list) -> list:
    """把函数体按**语句**分组：括号未闭合的行与其续行算同一条语句。

    逐行判定会误伤多行语句 —— `activationParticles.process_material.scale = min(`
    折行写参数时首行括号未闭合，逐行判会落到 mixed，把整个战斗函数剥成空桩
    （StaffofFire.onPreDealDamage_early 的热/法力消耗与加伤判定就这么丢过）。
    按语句判定后，整条语句的根接收者是模态 → 整条删除，判定行全部保留。

    返回 [(首行下标, 末行下标)]。
    """
    out = []
    i = 0
    while i < len(lines):
        j = i
        depth = _balance(strip_str_comments(lines[i]))
        guard = 0
        while depth > 0 and j + 1 < len(lines) and guard < 80:
            j += 1
            guard += 1
            depth += _balance(strip_str_comments(lines[j]))
        out.append((i, j))
        i = j + 1
    return out


def classify_statements(lines: list, extra: set = None) -> list:
    """**按语句**判定视觉耦合级别，返回 [(kind, 原文行, 重写行列表)]。

    与逐行 `classify_line` 的唯一区别是判定单位。逐行判定会误伤多行语句：
    `activationParticles.process_material.scale = min(` 折行写参数时首行括号
    未闭合 → 两条规则（`pure` 整行删除）都因 `complete` 守卫不成立 → 落到
    `has_node_modal → mixed` → **整个战斗函数被剥成空桩**。
    StaffofFire.onPreDealDamage_early 的热/法力消耗与加伤判定就这么丢过。

    按语句判定后，整条语句的根接收者是模态 → 整条删除，判定行全部保留。
    单行语句走原路径，既有行为不变（`classify_line` 的 `complete` 守卫
    正是为多行语句设计的，此处不再触发）。
    """
    out = []
    for (i, j) in group_statements(lines):
        chunk = lines[i:j + 1]
        # 判定用去注释文本（`#` 后的括号不算数）；返回的 `raw` 保留原文，
        # 使 `none` 语句的输出与逐行版完全一致（注释保留）。
        bare = [re.sub(r"#[^\n]*", "", x) for x in chunk]
        # A/B 开关：ITEM_STMT_LEVEL=0 退回逐行判定（仅用于回归对照，勿用于正式产出）
        if os.environ.get("ITEM_STMT_LEVEL") == "0":
            out.extend((k, [x], [rw]) for x, (k, rw) in zip(chunk, (classify_line(b, extra) for b in bare)))
            continue
        kind, rewritten = classify_line("\n".join(bare), extra)
        out.append((kind, chunk, rewritten.split("\n")))
    # 把「条件引用节点模态」的分支降级为纯视觉（块体内无判定才降，否则保持 mixed）
    return demote_modal_headers(out, extra)


def extends_of(body: str):
    m = EXT_RE.search(body)
    return m.group(1).strip() if m else None


def sig_span(lines: list, i: int):
    """从第 i 行起取一个完整的函数签名，支持**多行签名**。

    原版有把参数表折行的写法，例如
        func playActivationAnimation(aniType = descriptor.activationAni,
                playAnimation := true, ...):
    单行正则匹配不到，会把签名当普通语句、把参数续行当顶层代码，
    最终报 `Indented block expected after declaration of ... function`。
    故：签名未闭合（括号净深度 > 0）或行尾不是 `:` 时继续收下一行。

    返回 (签名文本, 最后一行下标)。
    """
    head = lines[i]
    j = i
    guard = 0
    while guard < 20:
        code = re.sub(r"#[^\n]*", "", head)
        if _balance(code) <= 0 and code.rstrip().endswith(":"):
            break
        if j + 1 >= len(lines):
            break
        j += 1
        head = head + "\n" + lines[j]
        guard += 1
    return head, j


def extract_inner_classes(body: str):
    """抽出 GDScript **内嵌类**（顶格 `class X:` + 其缩进块）。

    内嵌类不是顶层函数。若把它混进 `split_functions`，它的方法会以「带缩进的
    func 头」形式出现在输出里，Godot 报
    `Error parsing expression, misplaced: func`（整文件解析失败）。
    而 `Item.gd` 一失败，`class_name Item` 就解析不了，全部子类会连锁报
    `The method "getP1" isn't declared in the current class` —— 一个内嵌类
    能带崩全量解析，故必须单独处理。

    返回 (inner: [(类名, 原文)], body_without_inner)。
    """
    lines = body.splitlines()
    kept = []
    inner = []
    i = 0
    while i < len(lines):
        m = INNER_CLASS_RE.match(lines[i])
        if m:
            block = [lines[i]]
            i += 1
            while i < len(lines) and (not lines[i].strip() or lines[i][:1].isspace()):
                block.append(lines[i])
                i += 1
            inner.append((m.group(1), "\n".join(block)))
            kept.extend([""] * len(block))
            continue
        kept.append(lines[i])
        i += 1
    return inner, "\n".join(kept)


def transpile_inner_class(text: str, in_file: set, type_scope: set = None) -> str:
    """内嵌类转译：符号映射 + 视觉/上下文缺失的方法改空桩。

    ★ 内嵌类**不在** Item 的继承链上，因此拿不到 `ctx`（`ctx` 是 CoreItem 的成员）。
      所以判据是：方法体映射后若出现 `ctx.` 或残留外部符号 → 该方法在内核里
      无法运行（属场景树/单例耦合），置空桩；其余逐行保留。
    """
    lines = text.splitlines()
    out = [lines[0]] if lines else []
    i = 1
    while i < len(lines):
        line = lines[i]
        if FUNC_HEAD_RE.match(line):
            header, j = sig_span(lines, i)
            last = header.split("\n")[-1]
            ind = len(last) - len(last.lstrip("\t"))
            # 方法体 = 签名之后所有「缩进更深」的行（含空行）
            k = j + 1
            blines = []
            while k < len(lines):
                l = lines[k]
                if l.strip():
                    lind = len(l) - len(l.lstrip("\t"))
                    if lind <= ind:
                        break
                blines.append(l)
                k += 1
            keep = [b for b in blines if "preload(" not in b]
            joined = "\n".join([clean_header_defaults(map_symbols(header), in_file, type_scope)]
                               + [map_symbols(b) for b in keep])
            if ("ctx." in joined
                    or residual_symbols(strip_str_comments(joined), in_file)):
                out.append("%s\n%s" % (
                    clean_header_defaults(map_symbols(header), in_file, type_scope),
                    stripped_body(header, blines)))
            else:
                out.append(joined)
            i = k
            continue
        if "preload(" in line:
            i += 1
            continue
        if residual_symbols(strip_str_comments(line), in_file):
            i += 1
            continue
        out.append(map_symbols(line))
        i += 1
    return "\n".join(out)


def split_top_commas(s: str) -> list:
    """按**顶层**逗号切分（忽略括号内的逗号，如 `Vector2(1, 2)`）。"""
    out = []
    depth = 0
    cur = ""
    for ch in s:
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur)
            cur = ""
            continue
        cur += ch
    out.append(cur)
    return out


def clean_header_defaults(header: str, in_file: set, type_scope: set = None) -> str:
    """净化函数签名：擦掉解析不了的类型标注 + 置空解析不了的默认值。

    类型标注：`func getDataPersistent(bitStream: BitStream)` —— `BitStream` 是
    外部存档子系统类，不随物品脚本转译 → `The identifier "BitStream" isn't declared`。
    擦掉标注退回动态类型，语义不变。

    默认值：原版会用界面/存档单例或节点属性当默认值，例如
        func pushToStorage(targetPos = Game.STORAGEBOX.center):
        func someVisualThing(pos = global_position):
    `Game.STORAGEBOX` 是场景对象、`global_position` 是 Node2D 属性，无头内核里都没有。
    这类签名**必须能编译** —— 一个坏签名会让整文件解析失败，连锁带崩全部子类。

    判据（通用，不靠硬编码名单）：默认值表达式的**根标识符**若既不在本文件声明里、
    也不在内核成员表里、也不是引擎内建类型，则视为不可解析 → 置 `null`。
    只动签名，不动函数体（体若含残留符号仍会整函数剥离）。

    ★ `type_scope` 与 `in_file` 必须分开：
      `in_file` 含**全工程名字并集**（用于宽松判定残留符号），但它不代表
      「本文件类型可见域」——`Socket` 在 `GemSocket.gd` 里被声明过，若拿并集当
      类型域，`Gem.gd` 的 `var hoveredSocket: Socket` 就会被认为类型合法，
      而实际上本工程没有编译 `Socket` 类，Godot 报
      `The identifier "Socket" isn't a valid type (not a script or class)`。
    """
    scope = type_scope if type_scope is not None else in_file
    # 返回类型 `-> T`：T 解析不了就整个擦掉（`-> Object` 会引入调用期类型不匹配）
    m = re.search(r"\s*->\s*([A-Za-z_]\w*)", header)
    if m and not type_ok(m.group(1), scope):
        k = header.index(":", m.end()) if ":" in header[m.end():] else len(header)
        header = header[:m.start()] + header[k:]
    i = header.find("(")
    j = header.rfind(")")
    if i < 0 or j < 0:
        return header
    params = header[i + 1:j]
    parts = split_top_commas(params)
    out = []
    for p in parts:
        rhs = None
        if "=" in p:
            k = p.index("=")
            lhs, rhs = p[:k], p[k + 1:]
        else:
            lhs = p
        # 参数类型标注 `x: T` → T 解析不了就擦掉
        mt = re.match(r"^(\s*[A-Za-z_]\w*\s*):\s*([A-Za-z_]\w*)(.*)$", lhs, re.S)
        if mt and not type_ok(mt.group(2), scope):
            lhs = mt.group(1) + mt.group(3)
        if rhs is not None:
            if ("ctx." in rhs
                    or residual_symbols(strip_str_comments(rhs), in_file)
                    or not _default_value_resolvable(rhs, in_file)):
                out.append(lhs.rstrip() + " = null")
                continue
            out.append(lhs + "=" + rhs)
            continue
        out.append(lhs)
    return header[:i + 1] + ",".join(out) + header[j:]


_DEFAULT_LITERAL_RE = re.compile(
    r"^(?:-?\d|true\b|false\b|null\b|\"|'|\[|\{|\()")


def type_ok(t: str, allowed: set) -> bool:
    """类型名能否解析（引擎内建 / 内核类 / 本工程内已声明）。"""
    return (t in KNOWN_TYPE_NAMES or t.startswith("Core") or t in allowed)


ONREADY_TYPE_RE = re.compile(r"^\s*onready\s+var\s+([A-Za-z_]\w*)\s*:\s*([A-Za-z_]\w*)")


def onready_decl(line: str, name: str, allowed: set) -> str:
    """生成 onready 成员声明，**保留可解析的类型标注**。

    ★ 为什么必须保（实测踩到的真偏离）：原版有 53 处 `onready var X: int = getP1()`，
      而 `getP*()` 统一返回 float。带标注时 Godot 3 会把赋进来的 float **截断成
      int**，于是后续
        `damageAcc / damagePerPoison` 是**整除**（7/5 → 1）
        `damageAcc %= damagePerPoison` 合法
      丢掉标注后 X 成了 float，混算语义立刻变：
        · 整除变真除 —— PoisonBow 的毒层数由 1 变 1.4，直接改变战斗结果；
        · 取模直接报错 —— `Invalid operands 'int' and 'float' in operator '%'`
          （PoisonBow.doCooldownEffect 就是这么炸的，闸门 8 抓出来的）。
      类型名解析不了（`Socket` / `BitStream` / `WeightedBag`）时退回动态类型，
      与 strip_unknown_types_in_decl 同一判据。
    """
    m = ONREADY_TYPE_RE.match(line)
    if m and m.group(1) == name and type_ok(m.group(2), allowed):
        return "var %s: %s" % (name, m.group(2))
    return "var " + name


def strip_unknown_types_in_decl(line: str, allowed: set) -> str:
    """擦掉声明里解析不了的类型标注：`var socket: Socket = null` → `var socket = null`。

    原版会拿**外部子系统类**当类型（`Socket` / `BitStream` / `WeightedBag`），
    这些类不随物品脚本转译，类型名解析不了会直接报
    `The identifier "Socket" isn't declared in the current scope`。
    擦掉标注 = 退回动态类型，运行语义不变（GDScript 静态类型只是提示与检查）。

    ★ 只作用于 `var NAME: TYPE` 这一种形态：
      泛化到任意 `X: Y` 会误伤字典字面量 `{Type.Weapon: Type.Weapon}` 与
      单行 `if x: return`，故必须限定上下文。
    """
    m = re.match(r"^(\s*(?:onready\s+|export\b[^\n]*?\s+)?var\s+[A-Za-z_]\w*\s*)"
                 r":\s*([A-Za-z_]\w*)", line)
    if m and not type_ok(m.group(2), allowed):
        return m.group(1) + line[m.end():]
    return line


def _default_value_resolvable(rhs: str, in_file: set) -> bool:
    """默认参数值能否在无头内核里解析？字面量直接通过，否则看根标识符。"""
    s = strip_str_comments(rhs).strip()
    if not s:
        return True
    if _DEFAULT_LITERAL_RE.match(s):
        return True
    m = re.match(r"^(?:self\.)?([A-Za-z_]\w*)", s)
    if not m:
        return True
    root = m.group(1)
    return (root in in_file or root in CORE_MEMBERS
            or root in ENGINE_LIKE or root in MAPPED_OK)


def collect_top_decls(body: str) -> list:
    """收集**全文件**的顶层声明（var / const / enum / signal / onready var / class_name）。

    ★ 早期版本只取「第一个函数之前」的前言区（top_level_decls），
      但原版 GDScript 习惯把成员声明**夹在函数之间**，例如 Item.gd 的
      `var specificDragParticles: Array`（第 307 行）、`var faceDirection`（404 行）
      都排在若干函数之后。只扫前言区会让这些成员凭空消失，表现为子类报
      `The identifier "xxx" isn't declared in the current scope`。
      GDScript 的函数体一定有缩进，故「顶格 + 声明关键字」即顶层声明。

    多行字面量（`const X = {` / `enum Y{` / `var Z = [`）按括号闭合整块收取。
    """
    lines = body.splitlines()
    out = []
    i = 0
    while i < len(lines):
        line = lines[i]
        if (line and not line[0].isspace()
                and not FUNC_HEAD_RE.match(line)
                and not re.match(r"^(?:remote|master|puppet|sync|tool)\b", line)
                and re.match(r"^(?:class_name|onready|export|var|const|enum|signal)\b",
                             line)):
            block = [line]
            guard = 0
            # ★ 条件是「最后一行之后的净深度 > 0」。paren_depths() 返回的是
            #   **每行之前**的深度，单行块 [-1] 恒为 0，必须再加上该行自身的净增量
            #   —— 否则 `enum X{` 只会收自己，缩进的枚举体全部丢失。
            while (guard < 80 and i + 1 < len(lines)
                   and paren_depths(block)[-1] + _balance(block[-1]) > 0):
                i += 1
                block.append(lines[i])
                guard += 1
            out.extend(block)
        i += 1
    return out


def split_functions(body: str):
    """返回 [(header_str, name, body_str, start_line, end_line, indent)]，含顶层变量区。"""
    lines = body.splitlines()
    funcs = []
    cur = None
    top_start = None
    i = 0
    while i < len(lines):
        line = lines[i]
        m = FUNC_HEAD_RE.match(line)
        if m:
            header, j = sig_span(lines, i)
            if cur is not None:
                cur[4] = i
                funcs.append(cur)
            else:
                top_start = i
            cur = [header, m.group(2), [], i, None, len(m.group(1))]
            i = j + 1
            continue
        if cur is not None:
            # 下一个顶层声明（无缩进的 var/const/enum/signal/class）才结束函数
            if line and not line[0].isspace() and re.match(
                    r"^(var|const|enum|signal|class_name|extends|onready)\b", line):
                cur[4] = i
                funcs.append(cur)
                cur = None
                i += 1
                continue
            cur[2].append(line)
        i += 1
    if cur is not None:
        cur[4] = len(lines)
        funcs.append(cur)
    return funcs, (top_start if top_start is not None else 0), lines


def has_node_modal(code: str, extra: set = None) -> bool:
    """该代码是否**解引用场景节点模态**（⇒ 内核里求不了值）。

    ★ 判据前必须先剥掉字符串字面量，否则会把**物品参数名**误判成节点属性。
      EXTRA_NODE_TOKENS 里有一批裸词规则（`(?<![\\w.])scale\\b` / `offset` /
      `mass` / `bounce` / `frame` / `stream` / `texture` / `spread` …），它们本意是抓
      `scale = Vector2(2,2)`、`node.offset = ...` 这类节点属性写入。但物品脚本里
      **同名词大量出现在字符串实参中** —— `getP("scale")` / `getP_m("offset")` /
      `getParamModifier("scale")` 读的是描述符具名参数，与场景节点毫无关系。
      不剥字符串就会被判 `mixed` → **整个战斗函数剥成空桩**，而且只打印一条
      汇总计数、不报具体物品，属于最隐蔽的一类漏转译。
      实测：MagicRing.giveStacksFromEffect 的整套叠层给予逻辑（含
      `getScaledParam(stackName, paramScale)` 战斗数值查表）就是这么整段丢的。
      字符串剥离是幂等的，故原先已在外部调用的三处不做改动、不受影响。
    """
    code = strip_str_comments(code)
    if any(re.search(t, code) for t in EXTRA_NODE_TOKENS):
        return True
    names = NODE_MODALS if not extra else (NODE_MODALS | extra)
    for name in names:
        if re.search(r"(?<![\w.])" + re.escape(name) + r"\b", code):
            return True
    return False


def collect_local_visual_vars(blines: list) -> set:
    """收集函数内的**局部视觉变量**：`var particles = ObjectPool.particleOneShot(...)`。

    这类变量只服务视觉；转译把右侧剥成 `null` 后，后续 `particles.position = ...`
    必须一并删掉，否则对 null 取属性会在运行期崩。故先扫出这些名字，当作模态处理。
    """
    out = set()
    for b in blines:
        code = re.sub(r"#[^\n]*", "", b)
        m = re.match(r"^\s*var\s+([A-Za-z_]\w*)\s*(?::\s*[^=]+?)?\s*:?=\s*(.+)$", code)
        if not m:
            continue
        name, rhs = m.group(1), m.group(2).strip()
        if rhs.startswith("$"):
            out.add(name)
            continue
        m2 = re.match(r"^(?:self\.)?([A-Za-z_]\w*)\s*[\.\[]", rhs)
        if m2 and (m2.group(1) in NODE_MODALS or m2.group(1) in out):
            out.add(name)
            continue
        # `ObjectPool.xxx(...)` / `Sound.xxx(...)` / `ctx.hooks.xxx(...)`
        if any(rhs.startswith(p) for p in VISUAL_CALL_PREFIXES):
            out.add(name)
    return out


# ── 整调用剥离名单：这些调用的**唯一效果**就是操作场景对象/音频，
#    连同实参一起剥掉（实参里常出现 `sprite` / `global_position` 这类节点模态）。
#    判据：调用名本身就是视觉专用；核心循环从不读它们的返回值。
VISUAL_CALL_PREFIXES = [
    "ObjectPool.particleOneShot",
    "ObjectPool.returnInstance",
    "ObjectPool.instance",
    "Sound.playSound_process",
    "Sound.playSound",
    "Util.createPulse",
    "Util.refreshTween",
    "Util.killTween",
    "Util.randPitch",
    "Util.highlight",
    "Util.zapScene",
    "Util.reparent",
    "Util.stretchSpriteToWidth",
    "Util.getGlobalZ",
    "Util.debugOnly",
    "Util.eprint",
    "Util.eassert",
    "ctx.hooks.",
    "create_tween",
    "Tween.new",
    # 直挂原版物品脚本后新暴露的纯表现调用（贴图/材质/拖拽尾迹/动画实例）
    # ★ `createAnimation()` 在战利品判定函数里很常见：
    #     `var ani = createAnimation(); ani.animation.play("DoubleHit")`
    #   把 createAnimation 认成视觉 → `ani` 被 collect_local_visual_vars 收进
    #   局部视觉变量 → 后续 `ani.*` 行整行删除，**函数其余判定得以保留**。
    #   若不认它，`ani.animation.play(...)` 会命中 `\bplay\s*\(` 变成 mixed，
    #   整个 doCooldownEffect（含 dealDamage/useStamina/activate）被剥成空桩 ——
    #   FalconBlade / RubyChonk 就这么丢过伤害。
    "createAnimation",
    "setTexture",
    "setSpriteMaterial",
    "setOutline",
    "activateDragParticles",
    "deactivateDragParticles",
    # 无头内核里物品没有父节点（`get_parent()` 恒为 null），挂视觉特效实例
    # 的语句必然无意义。TimeDilator.doCooldownEffect 尾部的
    # `var ani = ObjectPool.instance(...)` / `get_parent().add_child(ani)` /
    # `ani.global_position = ...` 属视觉，但中间夹着 `addSpeed`/`activate`
    # 判定；不剥它整函数就成了空桩。
    "get_parent().add_child",
]

VISUAL_LINE_DROP_RE = re.compile(r"^\s*(?:0|null|var\s+[A-Za-z_]\w*(\s*:\s*[^=]+)?\s*:?=\s*)?(?:0|null)\s*$")

# ── 独立的纯表现方法调用：整条语句只有这一个调用、无返回值、不参与任何判定。
#    命中即可整语句删除，**函数其余判定得以保留**。
#    ★ 判据从严：只收「调用本身不改判定状态、返回值从不被读」的方法。
#      下列是有意**不收**的（它们都改判定状态，删掉就是真丢逻辑）：
#        · activate / miniActivate / activateCooldown / deactivateCooldown
#          —— 改冷却与激活态
#        · consume / useStamina / tryUseMana / giveHeat / addBonusDamage
#          —— 消耗/资源/加伤
#        · refreshTriggers / check_triggers / onStateChanged / queue_redraw
#          —— 触发链
VISUAL_METHOD_DROP = {"show", "hide", "refreshTween", "repositionPiece"}

# ── `Game.connect("<signal>", ...)` 里的**非战斗**流程信号白名单 ──
# 判据：逐个核过 Items/ 下全部 `Game.connect(` 调用点（共 7 个文件 11 处），
#   列为非战斗的是「商店/标题/打造/拖拽」流程 —— 内核（纯战斗）永不派发，
#   连接与否对判定无影响。
#   ★ 不含 `combat_end`（ElectricalCharge.preset）与 `switching_to_combat`
#     （FurciferPrime._ready）：它们挂在战斗流程上，不臆断其可丢，保持现状
#     整函数剥离并进报告。
NONCOMBAT_GAME_SIGNALS = {
    "pre_shop_opened_from_combat", "pre_shop_opened_from_title",
    "shop_opened", "title_to_shop", "returned_to_title",
    "item_picked_up", "item_dropped", "item_crafted", "run_started",
}


def match_paren(s: str, open_idx: int) -> int:
    """返回与 s[open_idx] 处 '(' 配对的 ')' 下标；找不到返回 -1。"""
    depth = 0
    i = open_idx
    n = len(s)
    in_str = None
    while i < n:
        ch = s[i]
        if in_str:
            if ch == "\\":
                i += 2
                continue
            if ch == in_str:
                in_str = None
        elif ch in ("'", '"'):
            in_str = ch
        elif ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
            if depth == 0:
                return i
        i += 1
    return -1


def strip_visual_calls(code: str) -> tuple:
    """把视觉调用整体替换成 `null`（含实参）。返回 (新代码, 剥掉个数)。

    用 `null` 占位而非空串，是为了让 `var x = <call>` 这类行在替换后仍是合法语句，
    从而能被 VISUAL_LINE_DROP_RE 识别为「纯视觉行」并整行删除。
    """
    out = code
    total = 0
    for pre in VISUAL_CALL_PREFIXES:
        idx = 0
        while True:
            i = out.find(pre, idx)
            if i < 0:
                break
            # ★ 左侧必须有单词边界：否则 `activateDragParticles` 会命中
            #   `deactivateDragParticles` 的子串，替换成 `null` 后留下 `de`+`null`
            #   = `denull` 这种残渣（一个真发生过的语法错误）。
            if i > 0 and (out[i - 1].isalnum() or out[i - 1] == "_"
                          or out[i - 1] == "."):
                idx = i + len(pre)
                continue
            # 前缀必须紧接 '('（中间只许空白），否则是别的标识符
            j = i + len(pre)
            while j < len(out) and out[j] == " ":
                j += 1
            if j >= len(out) or out[j] != "(":
                idx = i + len(pre)
                continue
            end = match_paren(out, j)
            if end < 0:
                break
            out = out[:i] + "null" + out[end + 1:]
            total += 1
            idx = i + 4
    return out, total


def classify_line(code: str, extra: set = None):
    """逐行判定视觉耦合级别。返回 (kind, rewritten)。

    'pure'  —— 该行唯一效果是操作场景对象（含「视觉调用是唯一语句」与
               「只赋给视觉变量」两种形态）。**直接删行**：场景对象在内核里不存在。
    'keep'  —— 含视觉调用但还夹着判定语句；`rewritten` 已把视觉调用剥成 `null`。
    'mixed' —— 模态出现在条件 / 运算 / 返回值等**非独立位置**，无法安全改写，
               保守起见整函数剥离为空桩并计入报告。
    'none'  —— 与视觉无关。
    """
    s = code.strip()
    if not s:
        return ("blank", code)
    modals = NODE_MODALS if not extra else (NODE_MODALS | extra)
    # ★ 「整行删除」的两个规则都必须要求该行**括号已闭合**。
    #   多行语句（`shaderTween.tween_property(sprite, "scale", \` 折行续参数）
    #   的首行一旦被删，续行就成了孤儿，Godot 报
    #   `Expected end of statement after expression`。
    #   未闭合时让它落到 `has_node_modal → mixed`（整函数剥离），更安全。
    complete = _balance(code) == 0
    # 独立语句：行首就是模态对象（或 $NodePath）
    m = re.match(r"^(?:self\.)?([A-Za-z_]\w*)\s*\.", s)
    if complete and m and m.group(1) in modals:
        return ("pure", code)
    if complete and s.startswith("$"):
        return ("pure", code)
    # 独立的纯表现方法调用（`show()` / `hide()` / `repositionPiece(cell)`）：
    # 无返回值、不参与判定，整语句可删。命中的函数因此得以保留其余判定
    # （ChessPiece.onStateChanged 的 `captured`/`inventory.clearItemCells` 就是这么救回来的）。
    if complete:
        m0 = re.match(r"^(?:self\.)?([A-Za-z_]\w*)\s*\(", s)
        if m0 and m0.group(1) in VISUAL_METHOD_DROP:
            return ("pure", code)
    # 壳成员（原版 Item.gd 上存在、内核里**没有**的成员）的赋值或方法调用 → 视觉。
    # 依据：内核已完整移植判定路径（当前缺口数以 tools/gd_core_coverage.py 为准），
    # 故任何「只有场景壳才有」的成员都是拖拽/物理/粒子/存档态，与判定无关。
    # 例：`shaderTween = null` / `shaderTween.tween_method(...)` / `totalWeight = ...`
    #     —— 内核里 shaderTween 恒为 null，这类语句保留会在运行期崩。
    m1 = re.match(r"^(?:self\.)?([A-Za-z_]\w*)", s)
    if complete and m1 and (m1.group(1) in SHELL_MEMBERS
                            or m1.group(1) in DROP_SYMBOLS):
        if re.match(r"^(?:self\.)?%s\s*(?:\.|\[|=|\+=|-=|\*=|/=|\+=)"
                    % re.escape(m1.group(1)), s):
            return ("pure", code)
    # ★ 给**视觉变量**赋一个视觉调用 → 整语句删除。
    #   这类语句若不删，`strip_visual_calls` 会把它剥成 `fluidTween = null`，
    #   而 `null` 形态不匹配 VISUAL_LINE_DROP_RE（左侧不是字面 `var`），
    #   于是落到 `has_node_modal → mixed` —— **整个函数被剥成空桩**。
    #   Laboratory.onStateChanged 的 `baseCooldownOverride = getBaseCooldownIndex(phase)`
    #   （冷却覆写，判定）就是这么丢的。
    m2 = re.match(r"^(?:self\.)?([A-Za-z_]\w*)\s*=\s*(.+)$", s)
    if complete and m2 and m2.group(1) in modals:
        if any(m2.group(2).strip().startswith(p) for p in VISUAL_CALL_PREFIXES):
            return ("pure", code)
    # ★ 场外流程信号连接 → 整语句删除。
    #   内核只派发战斗事件（ctx.bus + connectForCombat），而 `Game.connect(...)`
    #   连的是 Game 这个 autoload**节点**上的流程信号（商店/标题/打造/拖拽），
    #   内核永不派发它们。命中它的函数因此得以保留其余判定 ——
    #   ChessBoard.onPrepare 的棋子收集与 originCells 就是这么救回来的。
    #   ★ 白名单只收**已确认非战斗**的信号名；`combat_end` / `switching_to_combat`
    #     刻意不在内（它们在战斗流程上，见 ElectricalCharge/FurciferPrime），
    #     其所在函数保持 `Game` 残留符号 → 整函数剥离并进报告，交人工定裁。
    if complete:
        mg = re.match(r"^(?:self\.)?Game\.connect\(\s*\"([^\"]+)\"", s)
        if mg and mg.group(1) in NONCOMBAT_GAME_SIGNALS:
            return ("pure", code)

    stripped, n_stripped = strip_visual_calls(code)
    if n_stripped:
        if VISUAL_LINE_DROP_RE.match(stripped):
            return ("pure", code)
        if not has_node_modal(stripped, extra):
            return ("keep", stripped)
        return ("mixed", stripped)

    # var 声明，右侧整体是视觉
    m = re.match(r"^var\s+[A-Za-z_]\w*(\s*:\s*[^=]+?)?\s*:?=\s*(.+)$", s, re.DOTALL)
    if m:
        rhs = m.group(2).strip()
        if rhs.startswith("$"):
            return ("pure", code)
        m2 = re.match(r"^(?:self\.)?([A-Za-z_]\w*)\s*[\.\[]", rhs)
        if m2 and m2.group(1) in modals:
            return ("pure", code)
        # ★ 派生量声明也属视觉：`var angleDif = arm.rotation` 之后
        #   `var dur = angleDif * 0.3` 只含视觉变量与字面量，与判定无关。
        #   不认它就会落到 mixed，把 Eat-o-matic.onStateChanged 的
        #   `armState = _armState`（状态机赋值，判定）连带剥掉。
        if expr_all_visual(rhs, modals):
            return ("pure", code)
    if has_node_modal(code, extra):
        return ("mixed", code)
    return ("none", code)


# 常量标识符白名单：它们本身不携带判定信息。**有意保持极小** ——
# 名字漏进来一个就可能把判定表达式误判成视觉（`var x = round(slowestCd)`
# 里的 `round` 就不在白名单，故该行不会被误删）。
SAFE_CONST_IDENTS = {"PI", "TAU", "INF", "NAN", "true", "false", "null", "self"}


def expr_all_visual(rhs: str, modals: set) -> bool:
    """表达式是否**只**由视觉变量 + 常量构成（⇒ 与判定无关，可整语句删除）。

    两个必要条件，缺一不可：
      ① 至少有一个标识符是视觉变量（`modals`）—— 排除 `var x = 0.0` 这类
         纯字面量声明（它可能是判定量的初值，绝不能删）；
      ② 其余标识符都在 `modals ∪ SAFE_CONST_IDENTS` 内。
    属性名不算标识符（`arm.rotation` 只取 `arm`），故 `var x = arm.rotation`
    成立而 `var x = character().getHeat()` 不成立。
    """
    code, _ = strip_visual_calls(strip_str_comments(rhs))
    idents = set(re.findall(r"(?<![\w.])([A-Za-z_]\w*)", code))
    if not any(n in modals for n in idents):
        return False
    return all(n in modals or n in SAFE_CONST_IDENTS for n in idents)


def is_visual_header(line: str, extra: set = None) -> bool:
    """该行是否是**解引用节点模态的块头**（`if animation.current_animation == "":`）。

    这类块头在内核里无法求值 —— 模态对象恒为 null，`null.current_animation`
    一执行就崩。它又不能按「整行删除」处理（那是块头，删了体就成了孤儿）。
    """
    code = re.sub(r"#[^\n]*", "", line)
    if _balance(code) != 0 or not code.rstrip().endswith(":"):
        return False
    if not re.match(r"^\s*(if|elif|for|while)\b", code):
        return False
    return bool(has_node_modal(strip_str_comments(code), extra))


def demote_modal_headers(stmts: list, extra: set = None) -> list:
    """把「条件引用节点模态」的**整条 if/elif/else 链**降级为纯视觉并删除。

    依据：内核里不存在场景节点，`animation` / `sprite` 这类模态恒为 null，
    条件无法求值；该分支的唯一效果是播动画/改材质，删掉对判定无损。
    不这么做，Resistor.onChargeReceived 的
    `if character().getHeat() < heatThreshold: giveHeat(heat); miniActivate()`
    （充能热度阈值判定）会跟那条 `else: if animation...` 一起被剥成空桩。

    ★ **两个硬约束**（都踩过坑）：
      ① **链要整条处理**。只删 `if` 分支、留下 `else:` 会得到 `misplaced: else`
         —— Item.gd `initSpriteMaterial` 的
         `if sprite.texture is AtlasTexture: ... else: ...` 就是这么把整个适配层
         打崩、连带 465 个子类报 `method "giveHeat" isn't declared` 的。
      ② **块体内一旦出现有效保留语句**（`none` / `keep`，即任何判定）就**不降级**，
         保持 `mixed` → 整函数剥离并进报告交人工定裁。
         「静默禁用一条含判定的分支」比「显式剥离整函数」危险得多。
    """
    n = len(stmts)
    kinds = [s[0] for s in stmts]
    eff = [False] * n

    def indent_of(idx):
        l0 = stmts[idx][1][0] if stmts[idx][1] else ""
        return len(l0) - len(l0.lstrip()), l0

    for i in range(n - 1, -1, -1):
        cur_indent, first = indent_of(i)
        if kinds[i] == "mixed" and is_visual_header(first, extra):
            # 收整条链：if → (elif|else)*，各分支的体按「缩进更深」划段
            chain, bodies = [i], []
            j = i + 1
            while True:
                start = j
                while j < n:
                    ind, l0 = indent_of(j)
                    if l0.strip() and ind <= cur_indent:
                        break
                    j += 1
                bodies.append((start, j))
                k = j
                while k < n and not (stmts[k][1][0].strip()
                                     if stmts[k][1] else ""):
                    k += 1
                if k >= n:
                    break
                ind, l0 = indent_of(k)
                if ind == cur_indent and re.match(r"^\s*(?:elif|else)\b", l0):
                    chain.append(k)
                    j = k + 1
                    continue
                break
            if not any(eff[s] for a, b in bodies for s in range(a, b)):
                for x in chain:
                    kinds[x] = "pure"
                continue
        eff[i] = kinds[i] in ("none", "keep")
    return [(kinds[i], stmts[i][1], stmts[i][2]) for i in range(n)]


def _balance(line: str) -> int:
    """单行的括号净深度（忽略注释与字符串内容）。"""
    code = re.sub(r"#[^\n]*", "", line)
    code = re.sub(r'"(?:[^"\\]|\\.)*"', '""', code)
    return (code.count("(") - code.count(")")
            + code.count("[") - code.count("]")
            + code.count("{") - code.count("}"))


def paren_depths(lines: list) -> list:
    """返回每行**之前**的累计括号深度。

    用途：GDScript 里多行表达式（跨行的 if 条件、多行字典/数组字面量）会让
    「以 `:` 结尾的行」并不一定是块头。例如 Crown.gd：
        if (crownState == CrownState.Inactive and
            character().isVulnerable() and
            checkMana(manaCost)):
    这里的第 3 行以 `:` 结尾，但它是条件的收尾、不是块头；若误判为块头并补 `pass`，
    就会多出一层缩进，引发 `Unindent does not match any outer indentation level`。
    """
    out = []
    d = 0
    for ln in lines:
        out.append(d)
        code = re.sub(r"#[^\n]*", "", ln)
        code = re.sub(r'"(?:[^"\\]|\\.)*"', '""', code)
        d += code.count("(") - code.count(")")
        d += code.count("[") - code.count("]")
        d += code.count("{") - code.count("}")
        if d < 0:
            d = 0
    return out


def ensure_blocks_nonempty(lines: list) -> list:
    """删行后若某个块（以 `:` 结尾的行）下面没有语句了，补 `pass`。

    ★ 缩进必须与原文件一致（物品脚本统一用 tab）——混用 tab/空格 Godot 直接报
      `Mixed tabs and spaces in indentation`。
    ★ 只有「括号深度为 0 且以 `:` 结尾」的行才是块头（见 paren_depths）。
    """
    depths = paren_depths(lines)
    out = []
    for i, ln in enumerate(lines):
        out.append(ln)
        s = ln.strip()
        if not s.endswith(":") or s.startswith("#") or depths[i] > 0:
            continue
        cur_indent = len(ln) - len(ln.lstrip())
        pad = "\t" * (ln[:cur_indent].count("\t") + 1)
        # ★ 找**下一条非空行**再判缩进：块头与首语句之间常有只含制表的空行
        #   （PoweroftheMoon.onPrepare 就是 `if ...:` / `\t` / 语句），
        #   若拿空行当 nxt，`nxt.strip()` 为空会误判成「块是空的」而补一层
        #   `pass`。虽然语义无害（pass 是空操作），但产出里会多出无谓语句。
        nxt = None
        for k in range(i + 1, len(lines)):
            if lines[k].strip():
                nxt = lines[k]
                break
        if nxt is None:
            out.append(pad + "pass")
        elif (len(nxt) - len(nxt.lstrip())) <= cur_indent:
            out.append(pad + "pass")
    return out


ITEMBOOK_MAP = None


def itembook_map() -> dict:
    """`ItemBook.<成员>` → `ctx.item_book.<成员>` 的**白名单**映射。

    白名单**只**收两类：
      · 描述符成员（`bagtacularDescriptor` 等）—— 名字→标识符表直接从生成的
        `gd_core/CoreItemBook.gd` 的 `DESCRIPTOR_IDS` 常量读，与内核
        **单一真值源**同步，不手工维护。改写结果是
        `ctx.item_book.getDescriptor("<标识符>")`，因此不存在「成员变量与注册表
        失同步」的可能（原版的 `ItemBook.Xxx` 与 `getDescriptor(...)` 本就是一回事）。
      · 按描述符查询库存的 8 个方法（`getItemsInInventoryOfType` 家族）。
    其余 ItemBook 成员（商店/打造/图鉴/稀有度池）**故意不映射**：
    `ItemBook` 于是仍是残留外部符号 → 那些场外函数照旧整函数剥离。
    这是刻意的边界 —— 内核只承担战斗，不重建商店。

    ★ 判据来自调用点普查：`getDescriptor` 与查询家族之外，ItemBook 的引用
      全部落在 `onShopEntered` / `onItemRoll` / `getGatedDescriptor` /
      `onAddToInventory_deferred` 这类**场外**函数里。
    """
    global ITEMBOOK_MAP
    if ITEMBOOK_MAP is not None:
        return ITEMBOOK_MAP

    path = os.path.join(ROOT, "gd_core", "CoreItemBook.gd")
    text = ""
    if os.path.exists(path):
        with io.open(path, encoding="utf-8", errors="replace") as fh:
            text = fh.read()
    # DESCRIPTOR_IDS 常量体：`"名字": "标识符",`
    block = re.search(r"const\s+DESCRIPTOR_IDS\s*:=\s*\{(.*?)\n\}", text,
                      re.S)
    out = {}
    if block:
        for name, ident in re.findall(r'"([A-Za-z_]\w*)"\s*:\s*"([^"]+)"',
                                      block.group(1)):
            out[name] = 'ctx.item_book.getDescriptor("%s")' % ident
    for m in ["getDescriptor",
              "getItemsInInventoryOfType", "getItemsInInventoryOfType_opponent",
              "countItemsInInventoryOfType", "countItemsInInventoryOfType_opponent",
              "countPlacedItemsInInventoryOfType",
              "isItemInInventory", "isItemInInventory_opponent"]:
        out[m] = "ctx.item_book." + m
    ITEMBOOK_MAP = out
    return ITEMBOOK_MAP


def map_itembook(line: str) -> str:
    """把**白名单内**的 `ItemBook.X` 换成内核等价写法（白名单外原样留下）。

    留下即是「剥离信号」：那些函数仍会命中 R5 残留符号检查，
    整函数剥离并进报告 —— 与加映射前行为一致，不会静默放行。
    """
    # 长键优先：`getItemsInInventoryOfType_opponent` 不能被无 `_opponent` 的抢走
    table = itembook_map()
    for k in sorted(table, key=len, reverse=True):
        line = re.sub(r"(?<![\w.])ItemBook\." + re.escape(k) + r"\b",
                      table[k], line)
    return line


# ── R9：`call_deferred` → 内核帧末队列 ──
#
# 原版 `Object.call_deferred(method, args…)`（Godot 3）与内核 `ctx.defer` 语义对齐：
# 都「排到帧末执行」（见 CoreCombat.gd 头部注释：按原版 call_deferred 语义延到
# 帧末 flush）。故这是**映射**而非剥离，控制流零改动。
#
# ★ 不映射的后果很隐蔽：GDScript 侧由 Godot 原生提供实现，**看起来完全正常**；
#   Python 侧没有这个名字 → `NameError: name 'call_deferred' is not defined`。
#   实测 10 处，其中 2 处（AcornAce / BuytheHolyLight 的 onAddToInventory）在物品
#   装进背包的当帧就抛。
_CALL_DEFERRED_RE = re.compile(
    r"(?<![\w.])"
    r"(?:(?P<target>[A-Za-z_]\w*(?:\[[^\]]*\])?(?:\.[A-Za-z_]\w*)*)\s*\.\s*)?"
    r"call_deferred\s*\(")


def map_call_deferred(line: str) -> str:
    """`call_deferred("m", a)` → `ctx.defer(self, "m", [a])`；`x.call_deferred("m")` 的
    target 从 `self` 换成 `x`。"""
    out = line
    while True:
        m = _CALL_DEFERRED_RE.search(out)
        if not m:
            break
        op = out.index("(", m.end() - 1)
        cl = match_paren(out, op)
        if cl < 0:
            break
        args = [a.strip() for a in split_top_commas(out[op + 1:cl])]
        target = m.group("target") or "self"
        name = args[0] if args and args[0] else '""'
        rest = [a for a in args[1:] if a]
        rep = 'ctx.defer(%s, %s, [%s])' % (target, name, ", ".join(rest))
        out = out[:m.start()] + rep + out[cl + 1:]
    return out


# ── R8：变量名遮蔽继承链方法 ──
#
# GDScript 里**成员变量与方法分属两张表**：子类 `var speed` 与基类 `func speed()`
# 可以共存 —— `self.speed` 取变量、`self.speed()` 调方法（`GDScriptInstance` 的
# `get` 走 members 表、`call` 走 member_functions 表）。
# Python 只有一张表：`self.speed = None` 直接**遮蔽**类方法 `speed`，之后内核
# `CoreItem.getSpeed()` 里的 `self.speed()` 抛
# `TypeError: 'float' object is not callable`。
#
# ★ 判据是**继承链**（含内核 CoreItem 的方法面），不是「名字看起来像」。
#   实测 4 件：ChessMaster / GirlPower / PerpetuumMobile / Sloth，变量都是 `speed`。
#   它们没有外部读取者，改的是纯本地名字，不触碰任何跨脚本约定。
#
# ★ 为什么不改 `_rt` 让属性不遮蔽方法：`self.x` 与 `self.x()` 在运行期本就无法
#   区分（同名但语义不同），要区分就得把所有方法调用改走显式派发，侵入面远大于
#   改一个纯本地变量名。
#
# ★ 为什么不改内核方法名：`speed()` / `getSpeed()` 是原版 `Item.gd` 的名字，
#   内核逐行对齐它们，改名会破坏「与本函数逐行一致」的可核性。
SHADOW_SUFFIX = "_v"

# 字符串 / 注释的区间（改名时跳过）
_STR_SPAN_RE = re.compile(
    r'"(?:[^"\\]|\\.)*"' + r"|'(?:[^'\\]|\\.)*'" + r"|#[^\n]*")


def _top_var_names(body: str) -> set:
    """本文件顶层声明的变量名（含 `onready var`，它转译后会变成顶层 `var`）。"""
    out = set(re.findall(r"^(?:onready\s+)?var\s+([A-Za-z_]\w*)", body, re.M))
    out |= set(re.findall(r"^\s*onready\s+var\s+([A-Za-z_]\w*)", body, re.M))
    return out


def chain_func_names(scr: dict) -> dict:
    """逐脚本算出「继承链上全部 func 名」，走到内核边界时并入 CoreItem 的方法面。"""
    cache = {}

    def resolve(decl):
        decl = (decl or "").strip().strip('"')
        if decl.startswith("res://Items/"):
            return decl[len("res://Items/"):]
        if decl.startswith("res://"):
            return ""                       # 已指向内核侧，交给 core 并集
        return decl if decl.endswith(".gd") else decl + ".gd"

    core = script_names(os.path.join(ROOT, "gd_core", "CoreItem.gd"))["func"]

    def walk(rel):
        if rel in cache:
            return cache[rel]
        cache[rel] = set()                  # 环保护（先占位再回填）
        body = scr.get(rel, "")
        out = set(re.findall(r"^\s*(?:static\s+)?func\s+([A-Za-z_]\w*)",
                             body, re.M))
        if rel == ITEM_BASE:
            out |= core
        base = resolve(extends_of(body))
        if base and base in scr:
            out |= walk(base)
        elif base or rel == ITEM_BASE:
            out |= core                     # 走到内核边界
        cache[rel] = out
        return out

    for rel in scr:
        walk(rel)
    return cache


def rename_var(text: str, old: str, new: str) -> str:
    """把**代码段**里的变量 `old` 改名为 `new`。

    只改「变量引用」：后跟 `(` 的 `old(` 是方法调用，必须原样留着
    （实测这 4 件物品里没有同名方法调用，但规则要经得起将来）。
    字符串与注释内的不动（`getP("speed")` 的 key 不能改）。
    """
    spans = [(m.start(), m.end()) for m in _STR_SPAN_RE.finditer(text)]
    pat = re.compile(r"(?<![\w])" + re.escape(old) + r"(?![\w(])")

    def rep(m):
        s = m.start()
        for a, b in spans:
            if a <= s < b:
                return m.group(0)
        return new

    return pat.sub(rep, text)


def map_symbols(line: str) -> str:
    line = map_call_deferred(line)
    for k, v in PRE_MAP.items():
        line = re.sub(r"(?<![\w.])" + re.escape(k) + r"\b", v, line)
    for k, v in GAME_STATIC_MAP.items():
        line = line.replace(k, v)
    line = map_itembook(line)
    # 类型名（裸标识符，含类型标注 `var x: DamageResult` 与构造 `DamageResult.new()`）
    for k, v in TYPE_TOKEN_MAP.items():
        line = re.sub(r"(?<![\w.])" + k + r"(?![\w])", v, line)
    # 长键优先，避免 `Item.Stat.` 被 `Stat.` 抢先替换
    for k in sorted(ENUM_MAP, key=len, reverse=True):
        line = re.sub(r"(?<![\w.])" + re.escape(k), ENUM_MAP[k], line)
    for k in sorted(VISUAL_SINGLETON_MAP, key=len, reverse=True):
        line = re.sub(r"(?<![\w.])" + re.escape(k) + r"\b",
                      VISUAL_SINGLETON_MAP[k], line)
    for k in sorted(SINGLETON_MAP, key=len, reverse=True):
        line = re.sub(r"(?<![\w.])" + re.escape(k), SINGLETON_MAP[k], line)
    return line


# 空桩的返回值：整函数剥离后，带 `-> T` 的函数必须返回 T 的零值，
# 否则 Godot 报 `A non-void function must return a value in all possible paths`。
STUB_RETURN = {
    "bool": "false", "int": "0", "float": "0.0", "String": '""',
    "Array": "[]", "Dictionary": "{}", "Vector2": "Vector2.ZERO",
    "void": None,
}


def stub_body(header: str) -> str:
    """按返回类型生成空桩体。

    ★ 缩进必须**比签名首行深一级**：内嵌类的方法签名自带一个 tab
      （`\\tfunc destroy():`）；多行签名（参数表折行）更要以**首行**为准，
      若按末行算会得到偏深的缩进，虽能解析但与源码风格不符。
      若桩体缩进不深于签名，Godot 会报
      `Indented block expected after declaration of "destroy" function`。
    """
    first = header.split("\n")[0]
    pad = "\t" * (len(first) - len(first.lstrip("\t")) + 1)
    m = re.search(r"->\s*([A-Za-z_][\w\.]*)", header)
    if not m:
        return pad + "pass"
    rt = m.group(1)
    if rt == "void":
        return pad + "pass"
    if rt in STUB_RETURN:
        return pad + "return %s" % STUB_RETURN[rt]
    return pad + "return null"


# ═════════ 抢救机制（2026-09-28 联动修复）═════════
#
# 整函数剥离有两类**误伤**：函数体「视觉 + 判定」混排时（如 MagicRing.sortEffects
# 的 stones/symbols 贴图染色 + effectDict 构建），按节点模态/残留符号把**整个函数**
# 剥成空桩，会把判定逻辑一起清零 —— MagicRing 由此整件死掉（effectDict 恒空，
# onCombatStart/doCooldownEffect 空转，0 次激活）。
#
# SALVAGE_FUNCS 是**点名名单**：这些函数不做整函数剥离，改走行级抢救 ——
#   ① map_symbols 先行（Util.rng→ctx.rng 等映射后的口径才准）；
#   ② 逐行 classify_line：pure（纯视觉）丢、mixed（模态进条件/返回值）丢；
#   ③ 残留符号 / 壳成员 / 本函数内先前被丢局部名的悬空引用 → 连带丢；
#   ④ ensure_blocks_nonempty 补空块；整体再过一遍残留+模态终检，不过回退空桩。
#
# ★ 名单是**审计驱动**的（tools/audit_stripped_funcs.py，带正对照）：
#   只有「被剥前含判定语句、且判定路径在战斗里可达」的函数才进名单。
#   不做全局开放 —— 行级丢弃可能漏掉跨语句的数据流依赖，点名 + 闸门兜底。
SALVAGE_FUNCS = {
    ("MagicRing.gd", "sortEffects"),
    ("MagicRing.gd", "randEffects"),
    ("ManaOrb.gd", "onManaChanged"),
    ("AmuletofDarkness.gd", "onItemActivated"),
    ("ChessPiece.gd", "onEliminatedBy"),
}

# 抢救时的**额外节点模态**：非 onready、但在 `_ready` 里从场景节点取值的成员
# （`stones.push_back(sprite.get_node("Stone1"))`）。内核里它们恒为空容器，
# 任何解引用都会崩 → 视觉行必须丢。
SALVAGE_EXTRA_MODALS = {
    "MagicRing.gd": {"stones", "symbols", "triggerTypeSymbols"},
}

# `_ready` 合并（R3）里启用「行级残留符号丢弃」的文件：只有它们带
# 「if ownerType == ItemLibrary: Game.itemLibrary.connect(...) else: randEffects()」
# 这类「残留符号与判定同语句」的形态。内核里 ownerType 恒非 ItemLibrary
# （装配只设 PlayerInventory / Opponent），丢弃 connect 行为后 else 支即
# 原版战斗语义。
SALVAGE_READY_FILES = {"MagicRing.gd"}


def salvage_body(rel: str, keep_header: str, blines: list, in_file: set,
                 inner_names: set = ()):
    """行级抢救（语句分组判定）。成功返回函数全文（头+体），失败返回 None。

    语句级而非逐行：多行语句（折行写参数）整条判定，否则首行被丢、
    续行成孤儿（randEffects 的 `randi_range(Lucky, \n Cold)` 实测过）。
    """
    extra = SALVAGE_EXTRA_MODALS.get(os.path.basename(rel))
    allowed = in_file | set(inner_names)
    dropped_local = set()
    out = []
    for kind, raw, rewritten in classify_statements(blines, extra):
        mapped = [map_symbols(x) for x in raw]
        text = strip_str_comments("\n".join(mapped))
        s = text.strip()
        if not s:
            out.extend(mapped)
            continue
        mvar = re.match(r"^\s*(?:var\s+)?([A-Za-z_]\w*)\s*:?=", s)
        first = re.match(r"^\s*(?:var\s+)?([A-Za-z_]\w*)", s)
        if kind == "pure":
            if first:
                dropped_local.add(first.group(1))
            continue
        names = set(re.findall(r"(?<![\w.])([A-Za-z_]\w*)", s))
        drop = (names & dropped_local or kind == "mixed"
                or residual_symbols(text, allowed)
                or touches_shell_member(text))
        if drop:
            if mvar:
                dropped_local.add(mvar.group(1))
            continue
        if kind == "keep":
            out.extend(map_symbols(x) for x in rewritten)
        else:
            out.extend(mapped)
    if not any(l.strip() for l in out):
        return None
    body = ensure_blocks_nonempty([keep_header] + out)[1:]
    text = "\n".join([keep_header] + body)
    if (residual_symbols(strip_str_comments(text), allowed)
            or touches_shell_member(text)
            or has_node_modal(strip_str_comments(text), extra)):
        return None
    return text


def salvage_ready_lines(rel: str, lines: list, in_file: set):
    """R3 合并中的行级残留符号丢弃（只对 SALVAGE_READY_FILES 生效）。

    输入是**已映射**的语句行；逐行丢「引用残留符号」的行，
    其余原样保留（含块头），空块由 ensure_blocks_nonempty 兜底。
    返回 None = 全丢。
    """
    out = []
    for line in lines:
        code = strip_str_comments(line)
        if code.strip() and residual_symbols(code, in_file):
            continue
        out.append(line)
    return out if any(l.strip() for l in out) else None


# 父类调用：GDScript 用**行首点号**调父实现（原版 `Bag.gd:79` 的
# `.addToInventory(_inventory, _occupiedCells, _placedByPlayer)`）。
PARENT_CALL_RE = re.compile(r"^\s*\.\s*[A-Za-z_]\w*\s*\(")


def parent_calls_of(blines: list) -> list:
    """挑出函数体**顶层**的父类调用语句。

    ★ 为什么整函数剥离时必须把它们留下：空桩不是「删掉这个函数」，而是**影子覆盖**
      基类同名实现。原版若先调 `.同名方法(...)` 再补自己的表现，剥成 pass 会连带丢掉
      **基类的全部逻辑** —— 这比「少一段表现」严重得多，且完全没有报错症状。
      实测：`Bag.addToInventory` 原版首句就是 `.addToInventory(...)`（真正写
      placed / inventory / 受影响集的地方），被剥成 pass 后 28 件包的 placed 恒假、
      inventory 恒 null，进而 `getItemsInside()` 在 null 上取方法直接崩。
    只取**顶层**（缩进 == 函数体最小缩进）的调用：嵌在 if/for 里的父类调用若提到顶层
    会改变执行条件，宁可不留（此时退回普通空桩）。
    """
    codes = [re.sub(r"#[^\n]*", "", b) for b in blines]
    indents = [len(c) - len(c.lstrip("\t")) for c in codes if c.strip()]
    if not indents:
        return []
    base = min(indents)
    out = []
    for c in codes:
        if not c.strip():
            continue
        if len(c) - len(c.lstrip("\t")) != base:
            continue
        if PARENT_CALL_RE.match(c):
            out.append(c.rstrip())
    return out


def stripped_body(header: str, blines: list) -> str:
    """整函数剥离时的桩体：保留顶层父类调用，其余退化成按返回类型的空值。"""
    calls = parent_calls_of(blines)
    if calls:
        return "\n".join(calls)
    return stub_body(header)


def read_text(path: str) -> str:
    with io.open(path, encoding="utf-8", errors="replace") as fh:
        return fh.read()


def references_dropped(code: str) -> str:
    """该函数体是否引用了**本文件里已被丢弃的声明**（`DROP_SYMBOLS`）。

    场景：`var frozenFlameBag = WeightedBag.new()` 因引用外部子系统被删，
    名字进 DROP_SYMBOLS；但 `getGatedDescriptor()` 里还留着
    `frozenFlameBag.roll()` —— 声明没了、引用还在，Godot 报
    `identifier "frozenFlameBag" isn't declared in the current scope`（整文件失败）。

    ★ 为什么必须在**函数级**兜底：函数级的残留符号检查（R5）只认
      「首字母大写的外部符号」（RESIDUAL_RE）。像 frozenFlameBag 这种小写
      局部名它看不到 —— 此前是靠同一函数里**另外**引用了 `ItemBook` 才被连带
      剥掉的；一旦 `ItemBook.getDescriptor` 被映射成内核可用面，掩护就没了，
      缺口立刻显形（FrozenFlame.gd:66）。
    """
    for name in DROP_SYMBOLS:
        if re.search(r"(?<![\w.])%s\b" % re.escape(name), code):
            return name
    return ""


def touches_shell_member(code: str) -> str:
    """R3b 判定：该行是否引用了「壳成员」或「被丢弃的声明」。

    `_ready` 在原版里是**场景/物理初始化**（挂粒子、设颜色、建碰撞形状）。
    这类语句操作的成员在无头内核里根本不存在值（会是 null / 空数组），
    若保留进 `_readyInit()`，解析能过但一调用就崩（如
    `specificDragParticles[0].self_modulate = amuletColor` 索引空数组）。
    故：`_ready` 体里**只保留引用内核成员的语句**（如
    `damageSource = DamageSource.new().setItem(self)`），其余属壳初始化，丢弃。

    两种命中：
      · SHELL_MEMBERS  —— 原版 Item.gd 有、内核没有的成员
      · DROP_SYMBOLS   —— 本文件里因引用外部子系统类而被删掉的**声明名**
                          （`var digUpBag = WeightedBag.new()` 被删后，
                           `digUpBag.prepare(...)` 就成了悬空引用）
    """
    code = strip_str_comments(code)
    for name in DROP_SYMBOLS:
        if re.search(r"(?<![\w.])%s\b" % re.escape(name), code):
            return name
    for name in SHELL_MEMBERS:
        if re.search(r"(?<![\w.])%s\b" % re.escape(name), code):
            return name
    return ""


def core_members(core_dir: str, entry: str = "CoreItem.gd") -> set:
    """沿 `entry` 的 extends 链收集成员名（`var X` / `onready var X`）。

    用途：物品脚本的 `onready var X` 转译后要在成员区补 `var X`；
    若 X 已在**内核基类链**上声明过（如 `damageSource` / `desiredFaceDirection`），
    就不能重复声明 —— 那会遮蔽父类成员。

    ★ 必须只走 CoreItem 的继承链，**不能扫整个 gd_core 目录**：
      CoreCharacter.gd 里也有 `var buffs` / `var staminaRegen` / `var maxStamina`，
      它们是**另一个类**的成员，物品脚本继承不到。早期版本扫全目录，导致
      `var buffs` 被误判为「内核已有」而漏声明，表现为
      `The identifier "buffs" isn't declared in the current scope`。
    """
    out = set()
    cur = entry
    seen = set()
    while cur and cur not in seen:
        seen.add(cur)
        path = os.path.join(core_dir, cur)
        if not os.path.exists(path):
            break
        body = read_text(path)
        for m in re.finditer(r"^(?:onready\s+)?var\s+([A-Za-z_]\w*)", body, re.M):
            out.add(m.group(1))
        # 下一个祖先：`extends "res://gd_core/X.gd"` 或 `extends X`（同目录）
        m = re.search(r'^extends\s+"res://gd_core/([^"]+)"', body, re.M)
        if not m:
            m2 = re.search(r"^extends\s+([A-Za-z_]\w*)\s*$", body, re.M)
            if not m2:
                break
            cand = os.path.join(core_dir, m2.group(1) + ".gd")
            cur = os.path.basename(cand) if os.path.exists(cand) else None
            continue
        cur = os.path.basename(m.group(1)) if os.path.exists(
            os.path.join(core_dir, os.path.basename(m.group(1)))) else None
    return out


def script_names(path: str) -> dict:
    """返回某个脚本里的 {func/var/const/enum/inner: set(名字)}（只取顶层声明）。"""
    body = read_text(path)
    out = {"func": set(), "var": set(), "const": set(), "enum": set(),
           "inner": set()}
    for m in re.finditer(r"^(?:static\s+)?func\s+([A-Za-z_]\w*)", body, re.M):
        out["func"].add(m.group(1))
    for m in re.finditer(r"^(?:onready\s+)?var\s+([A-Za-z_]\w*)", body, re.M):
        out["var"].add(m.group(1))
    for m in re.finditer(r"^const\s+([A-Za-z_]\w*)", body, re.M):
        out["const"].add(m.group(1))
    for m in re.finditer(r"^enum\s+([A-Za-z_]\w*)", body, re.M):
        out["enum"].add(m.group(1))
    for m in re.finditer(r"^class\s+([A-Za-z_]\w*)\s*:", body, re.M):
        out["inner"].add(m.group(1))
    return out


def decl_blocks(lines: list) -> list:
    """把顶层声明行按「括号闭合」切成块（多行 const/enum/字典字面量是一块）。

    用途：适配层过滤时，丢弃一个多行 `const X = {` 必须连它的 `}` 一起丢，
    否则留下的孤立续行会报 `Unexpected indentation`。
    """
    blocks = []
    i = 0
    while i < len(lines):
        block = [lines[i]]
        guard = 0
        while (guard < 60 and i + 1 < len(lines)
               and paren_depths(block)[-1] + _balance(block[-1]) > 0):
            i += 1
            block.append(lines[i])
            guard += 1
        blocks.append(block)
        i += 1
    return blocks


def filter_shim(funcs: list, head: list, core_names: dict):
    """把「转译后的原版 Item.gd」过滤成**只保留 CoreItem 之外的剩余面**。

    核心原则：**内核版本权威**。CoreItem 已逐行移植了 Item.gd 的战斗主干，
    故同名函数/成员/常量一律丢弃适配层版本，避免遮蔽内核实现。
    其余（CoreItem 没有的判定辅助方法、壳成员、非战斗常量）原样保留，
    这样全部物品脚本对 `Item` 的方法面引用就都解析得到。

    返回 (kept_funcs, kept_head, dropped_func_names, dropped_decl_names)。
    """
    kept_funcs, dropped_funcs = [], []
    for text, name in funcs:
        if name in core_names["func"]:
            dropped_funcs.append(name)
            continue
        kept_funcs.append((text, name))

    kept_head, dropped_decls = [], []
    for block in decl_blocks(head):
        s = block[0].strip()
        name = None
        for kind, pat in (("const", r"^const\s+([A-Za-z_]\w*)"),
                          ("enum", r"^enum\s+([A-Za-z_]\w*)"),
                          ("var", r"^(?:export\b[^\n]*?\s+)?var\s+([A-Za-z_]\w*)")):
            m = re.match(pat, s)
            if m:
                name = (kind, m.group(1))
                break
        if name and name[1] in core_names[name[0]]:
            dropped_decls.append(name[1])
            continue
        kept_head.extend(block)
    return kept_funcs, kept_head, dropped_funcs, dropped_decls


def top_level_decls(body: str) -> list[str]:
    """收集函数区之前的顶层声明（var/const/enum/signal/onready），保留原顺序。"""
    lines = body.splitlines()
    out = []
    for line in lines:
        if FUNC_HEAD_RE.match(line):
            break
        out.append(line)
    return out


def build_item_resolver(scr: dict):
    """判断脚本是否物品（extends 链可达 Item），并给出父类的输出侧引用。"""
    by_local = {rel[:-3]: rel for rel in scr}
    # ★ 另建 class_name → 路径 索引，不能只靠「路径去扩展名」当类名：
    #   中间基类大多躺在 Items/ 顶层（Items/Gem.gd 之类），`rel[:-3]` 恰好等于类名；
    #   但 `Items/Gems/Gem.gd` 的类名是 `Gem`、路径却推出 "Gems/Gem"，
    #   于是所有 `extends Gem` 的宝石脚本（Ruby/Amethyst/Emerald/Sapphire/Topaz/
    #   Skull/LumpofCoal/CorruptedCrystal，共 8 个）都被误判成「非物品」而**整类漏转译**。
    by_class = {}
    for rel in scr:
        m = re.search(r"^class_name\s+([A-Za-z_]\w*)", scr[rel], re.M)
        if m:
            by_class.setdefault(m.group(1), rel)

    def lookup_local(key: str):
        return by_class.get(key) or by_local.get(key)

    def parent_ref(ext: str):
        """返回 (kind, key)：kind ∈ local / res / engine"""
        if ext is None:
            return ("none", "")
        if ext.startswith('"') or ext.startswith("'"):
            path = ext.strip("\"'")
            if path.startswith("res://Items/"):
                return ("res", path[len("res://Items/"):])
            return ("res_other", path)
        return ("local", ext)

    memo = {}

    def is_item(rel, depth=0):
        if rel in memo:
            return memo[rel]
        if depth > 10:
            return False
        ext = extends_of(scr[rel])
        kind, key = parent_ref(ext)
        if kind == "local":
            if key == "Item":
                memo[rel] = True
                return True
            child = lookup_local(key)
            if child is None:
                memo[rel] = False
                return False
            memo[rel] = is_item(child, depth + 1)
            return memo[rel]
        if kind == "res":
            if key == "Item.gd":
                memo[rel] = True
                return True
            if key in scr:
                memo[rel] = is_item(key, depth + 1)
                return memo[rel]
            memo[rel] = False
            return False
        memo[rel] = False
        return False

    def out_parent(rel):
        """输出侧的父类引用形式。

        有 class_name 的中间基类（Item / Weapon / Food …）→ 用裸名（`extends Weapon`），
        与原版写法一致；**没有 class_name** 的（原版用 `extends "res://Items/Stone.gd"`）
        → 改写为目标路径 `extends "res://gd_core_items/Stone.gd"`，
        否则 Godot 报 `Unknown class: "Stone"`。
        """
        ext = extends_of(scr[rel])
        kind, key = parent_ref(ext)
        target_rel = None
        if kind == "local":
            if key == "Item":
                return "Item"
            target_rel = lookup_local(key)
            if target_rel is None:
                return None
        elif kind == "res":
            if key == "Item.gd":
                return "Item"
            if key in scr:
                target_rel = key
            else:
                return None
        else:
            return None
        if target_rel is None:
            return None
        m = re.search(r"^class_name\s+([A-Za-z_]\w*)", scr[target_rel], re.M)
        if m:
            return m.group(1)
        return '"res://gd_core_items/%s"' % target_rel

    return is_item, out_parent


def main() -> int:
    dry = "--dry-run" in sys.argv
    scr = collect()
    global NODE_MODALS, TIMER_MODAL_NAMES
    all_modals = extract_node_modals(scr)
    # `$XxxTimer` 会被转译成虚拟 CoreTimer（判定对象，必须保留），
    # 故从「视觉模态」里移除 —— 否则 `critTimer.stop()` 会被当视觉删掉。
    TIMER_MODAL_NAMES = {m for m in all_modals if m.endswith("Timer")}
    NODE_MODALS = all_modals - TIMER_MODAL_NAMES
    tscn_idx = load_tscn_index()

    is_item, out_parent = build_item_resolver(scr)

    items = [rel for rel in sorted(scr) if rel != "Item.gd" and is_item(rel)]
    skipped = [rel for rel in sorted(scr) if rel != "Item.gd" and not is_item(rel)]
    # ★ 基类 `Item.gd` 也过一遍转译，产出 `gd_core_items/Item.gd` 适配层：
    #   `extends "res://gd_core/CoreItem.gd"` + 「CoreItem 之外的剩余面」。
    #   原版 Item.gd 是 6573 行 / 628 方法的大类（战斗主干已移植进 CoreItem，
    #   剩下的是壳成员、判定辅助、商店/UI）。不转译它，子类引用的
    #   `regen` / `DRAG_PRIORITY` / `countAllInInventoryOfType` 就无处解析。
    #   （ITEM_BASE 是模块级常量，见文件头附近）
    work = items + [ITEM_BASE]
    print("物品脚本：%d；跳过（非物品）：%d；另转译基类 %s"
          % (len(items), len(skipped), ITEM_BASE))

    # 全局名字表：本工程内所有物品脚本定义的 enum/const/class_name/var
    global_names = set()
    for rel, body in scr.items():
        global_names |= collect_in_file_names(body)
    global_names |= MAPPED_OK | set(ENGINE_LIKE)

    global CORE_MEMBERS, SHELL_MEMBERS
    CORE_MEMBERS = core_members(os.path.join(ROOT, "gd_core"))
    # 内核基类 CoreItem.gd 的方法/常量/成员名 —— 适配层过滤时的「权威名单」
    CORE_ITEM_NAMES = script_names(
        os.path.join(ROOT, "gd_core", "CoreItem.gd"))
    # R3b：壳成员 = 原版 Item.gd 顶层 var 减去 CoreItem 已声明的
    # （预先算出，因为 Item.gd 排在最后转译，而全部子类要用到）
    SHELL_MEMBERS = (script_names(os.path.join(SRC, "Item.gd"))["var"]
                     - CORE_ITEM_NAMES["var"])

    stats = collections.Counter()
    stripped_funcs = []          # (rel, func, 是否战斗函数, 原因/命中)
    unresolved = collections.defaultdict(set)
    outputs = {}
    shell_dropped = collections.Counter()   # R3b 丢弃的壳成员 → 次数
    shim_dropped = ([], [])                 # 适配层被内核覆盖丢弃的 (函数, 声明)

    # R8：撞名变量消歧表（必须先于一切转译 —— 后续所有处理都读改过名的 body）
    _chain = chain_func_names(scr)
    shadow_map = {rel: (_top_var_names(body) & _chain.get(rel, set()))
                  for rel, body in scr.items()}
    shadow_map = {r: s for r, s in shadow_map.items() if s}
    shadow_renamed = []

    for rel in work:
        body = scr[rel]
        for _n in sorted(shadow_map.get(rel, ())):
            body = rename_var(body, _n, _n + SHADOW_SUFFIX)
            shadow_renamed.append((rel, _n))
        inner, body = extract_inner_classes(body)
        funcs, _top_end, _lines = split_functions(body)
        decls = collect_top_decls(body)
        if rel == ITEM_BASE:
            parent = '"res://gd_core/CoreItem.gd"'
        else:
            parent = out_parent(rel)
        tscn_info = tscn_idx.get(rel[:-3])
        in_file = collect_in_file_names(body) | global_names
        # 类型可见域（严格）：只能用**本文件**声明 + 内核成员链上的名字。
        # 不能并入 global_names —— 那会让别的物品脚本声明过的类名
        # （如 GemSocket.gd 的 Socket）在本文件里被误判为「类型可用」。
        type_scope = collect_in_file_names(body) | CORE_MEMBERS | set(MAPPED_OK)

        # ── R2 / R6：onready var 处理 ──
        # ★ 原版 `onready var X = expr` 是「成员声明 + ready 时求值」两件事。
        #   转译后求值移进 `_readyInit()`，但**成员声明必须补上**，否则
        #   `_readyInit` 里对 X 赋值会报 `Identifier not declared`。
        #   若该名字已在 CoreItem（及其祖先）里声明过，则不再重复声明，避免遮蔽。
        onready_assigns = []
        onready_decls = []
        kept_decls = []
        dropped_names = set()
        # ★ 按**声明块**（含多行续行）处理，而不是逐行：
        #   `const X = {` 的体是若干缩进行，若只按行删掉含 preload 的那些，
        #   会留下没有 `}` 的残块 → `Error parsing expression, misplaced: const`。
        for block in decl_blocks(decls):
            line = block[0]
            joined = "\n".join(block)
            m_decl = re.match(
                r"^\s*(?:onready\s+|export\b[^\n]*?\s+)?var\s+([A-Za-z_]\w*)",
                line)
            # 视觉资源常量（preload 粒子/音效/贴图/shader/场景）→ **整块**删除。
            # 引用它们的语句都是视觉调用，已在逐行剥离里删掉。
            if "preload(" in joined:
                stats["preload_dropped"] += 1
                if m_decl:
                    dropped_names.add(m_decl.group(1))
                continue
            m = ONREADY_RE.match(line)
            if not m:
                # 顶层声明里若带商店/UI 符号（`var x = ItemBook.fooDescriptor`、
                # `var bag = WeightedBag.new()`），该声明无法编译，删除它；
                # 名字记进 DROP_SYMBOLS，引用它的语句会被一并剥离（避免悬空引用）。
                # ★ 判据用**映射后**的文本：`ItemBook.getDescriptor(...)` 已被
                #   map_symbols 换成 `ctx.item_book.getDescriptor(...)`，属内核可用面，
                #   不该再按「残留外部符号」删掉（PoweroftheMoon 的
                #   `onready var moonArmorDescriptor = ItemBook.getDescriptor("Moon Armor")`
                #   就是这么被误删的）。映射白名单外的 ItemBook 成员仍会残留 → 照删。
                if residual_symbols(strip_str_comments(map_symbols(joined)), in_file):
                    stats["decl_dropped"] += 1
                    if m_decl:
                        dropped_names.add(m_decl.group(1))
                    continue
                # 类型标注（`: Socket` / `: BitStream`）解析不了就擦掉，声明本身保留
                for i2 in range(len(block)):
                    block[i2] = strip_unknown_types_in_decl(block[i2], type_scope)
                kept_decls.extend(map_symbols(b) for b in block)
                continue
            _indent, name, rhs = m.group(1), m.group(2), m.group(3) or ""
            # 多行字面量（`onready var X = [` 跨若干行到 `]`）：续行已在块里
            if len(block) > 1:
                stats["onready_multiline"] += 1
                rhs = rhs + "\n" + "\n".join(block[1:])
            dm = DOLLAR_RE.match(rhs[1:] if rhs.startswith("=") else rhs.lstrip(": "))
            if dm:
                node = dm.group(1)
                if is_timer_node(tscn_info, node):
                    method, is_multi = timer_spec(tscn_info, node)
                    onready_assigns.append("\t" + TIMER_ASSIGN %
                                           (name, node, method, "true" if is_multi else "false"))
                    stats["timer_created"] += 1
                    if method:
                        stats["timer_with_callback"] += 1
                else:
                    # 纯视觉节点引用（sprite / animation / particles / tilemap …）→ 赋值删除。
                    # ★ 成员声明仍要保留：`onready var bagTilemap = $Icon/TileMap` 在内核里
                    #   就是 `bagTilemap = null`，别处若拿它当「存在与否」的判据（null 检查）
                    #   才不会报未声明。
                    stats["onready_visual_dropped"] += 1
                    if name not in CORE_MEMBERS:
                        onready_decls.append(onready_decl(line, name, type_scope))
                    continue
            else:
                # 表达式求值（getP / getP1 / descriptor 派生 / has_method 能力标志 …）
                # → 保留，改到 _readyInit 里求值。
                # ★ 但若表达式碰到「壳成员」或节点属性（`baseBounce = physics_material_override.bounce`
                #   `specificDragParticles = ...`），它属场景初始化，内核里没有对应对象，
                #   赋值会崩 → 丢弃。判据与 R3b 一致。
                rb = rhs[1:] if rhs.startswith("=") else rhs.lstrip(": ")
                # ★ 与函数体同口径：残留符号判据用**映射后**文本（原因同上）
                rb_mapped = map_symbols(rb)
                if (touches_shell_member(rb_mapped)
                        or has_node_modal(strip_str_comments(rb_mapped))
                        or residual_symbols(strip_str_comments(rb_mapped), in_file)):
                    stats["onready_shell_dropped"] += 1
                    # ★ 只丢**赋值**，成员声明照旧保留：`onready var border = get_node_or_null(...)`
                    #   在内核里就是 `border = null`，而 `hasBagEffect() -> border != null`
                    #   之类的判定会读到它。声明漏了就报 `The identifier "border" isn't declared`。
                    if name not in CORE_MEMBERS:
                        onready_decls.append(onready_decl(line, name, type_scope))
                    continue
                onready_assigns.append("\t%s = %s" % (name, rb_mapped.strip()))
                stats["onready_var"] += 1
            if name not in CORE_MEMBERS:
                onready_decls.append(onready_decl(line, name, type_scope))

        # ── 函数体处理 ──
        global DROP_SYMBOLS
        DROP_SYMBOLS = dropped_names
        new_funcs = []
        ready_body = None
        for header, name, blines, _s, _e, _indent in funcs:
            if name == "_ready":
                ready_body = blines
                continue
            local_modals = collect_local_visual_vars(blines)
            # ★ 按**语句**判定（非逐行）：多行语句必须整条判定，否则折行写参数的
            #   视觉语句首行括号未闭合，会落到 mixed 把整个战斗函数剥空。
            stmts = classify_statements(blines, local_modals)
            kinds = [s[0] for s in stmts]
            if "mixed" in kinds:
                keep_header = clean_header_defaults(map_symbols(header), in_file, type_scope)
                # ── 抢救：点名函数不整函数剥离，走行级视觉/残留丢弃 ──
                if (os.path.basename(rel), name) in SALVAGE_FUNCS:
                    sal = salvage_body(rel, keep_header, blines, in_file,
                                       {n for n, _ in inner})
                    if sal is not None:
                        new_funcs.append([sal, name])
                        stats["func_salvaged"] += 1
                        continue
                new_funcs.append(["%s\n%s" % (keep_header,
                                              stripped_body(keep_header, blines)), name])
                bad = stmts[kinds.index("mixed")][1]
                stripped_funcs.append((rel, name, name in BATTLE_FUNCS,
                                       "节点模态", bad[0].strip()[:62]
                                       if bad else ""))
                stats["func_stripped_modal"] += 1
                continue

            kept = []
            for kind, raw, rewritten in stmts:
                if kind == "pure":
                    stats["line_dropped"] += len(raw)
                    continue
                if kind == "keep":
                    stats["line_rewritten"] += 1
                    kept.extend(map_symbols(x) for x in rewritten)
                else:
                    kept.extend(map_symbols(x) for x in raw)
            if not kept:
                kept = ["\tpass"]
            body_lines = ensure_blocks_nonempty(
                [clean_header_defaults(map_symbols(header), in_file, type_scope)] + kept)[1:]
            func_text = "\n".join(
                [clean_header_defaults(map_symbols(header), in_file, type_scope)] + body_lines)

            # ── R7：残留外部符号兜底（映射后仍解析不了 → 属商店/UI 依赖，整函数剥离）──
            #   ★ 另一类必剥：`static func` 里出现 `ctx.`。
            #     `ctx` 是 CoreItem 的**实例成员**，静态函数访问不到，Godot 报
            #     `Can't access member variable ("ctx") from a static function.`。
            #     命中的都是文本/本地化助手（如 getRarityName 用 ctx.util.tr），非战斗。
            res = residual_symbols(strip_str_comments(func_text), in_file)
            # 本文件里被丢弃的声明若仍被引用 → 悬空引用，必剥（见 references_dropped）
            dangling = references_dropped(strip_str_comments(func_text))
            static_ctx = (re.match(r"^\s*static\s+func", header) is not None
                          and "ctx." in func_text)
            if res or static_ctx or dangling:
                keep_header = clean_header_defaults(map_symbols(header), in_file, type_scope)
                # ── 抢救：点名函数不整函数剥离，走行级视觉/残留丢弃 ──
                sal = None
                if not static_ctx and (os.path.basename(rel), name) in SALVAGE_FUNCS:
                    sal = salvage_body(rel, keep_header, blines, in_file,
                                       {n for n, _ in inner})
                if sal is not None:
                    new_funcs.append([sal, name])
                    stats["func_salvaged"] += 1
                    continue
                new_funcs.append(["%s\n%s" % (keep_header,
                                              stripped_body(keep_header, blines)), name])
                if static_ctx:
                    reason = "静态函数用 ctx"
                elif res:
                    reason = "残留符号 " + ",".join(sorted(res)[:3])
                else:
                    reason = "悬空声明 " + dangling
                stripped_funcs.append((rel, name, name in BATTLE_FUNCS, reason,
                                       first_residual_line(kept, res) if res
                                       else ""))
                stats["func_stripped_residual"] += 1
                for s in res:
                    unresolved[rel].add(s)
                if dangling:
                    unresolved[rel].add(dangling)
                continue

            new_funcs.append([func_text, name])
            stats["func_kept"] += 1

        # ── R3：合成 _readyInit ──
        # `.()` 是 GDScript 2 的无参父类调用语法，3.x 必须写 `.<method>()`。
        init_lines = ["func _readyInit():", "\t._readyInit()"]
        init_lines += onready_assigns
        if ready_body:
            ready_kept = []
            # 与函数体同口径：按**语句**判定（多行语句整条判定）。
            for kind, raw, rewritten in classify_statements(ready_body):
                code = re.sub(r"#[^\n]*", "", "\n".join(raw))
                if kind == "pure":
                    stats["line_dropped"] += len(raw)
                    continue
                # R3b：`_ready` 是场景初始化，只留引用内核成员的语句。
                # ★ **块头行必须保留**（`if not pooled:` / `for x in y:`），
                #   只丢它下面的叶语句。若把块头删掉、把体留下，就产生
                #   `Unexpected indentation`；而整块丢掉又会改变控制流语义
                #   （`if not pooled:` 在内核里恒为真，保留才与原版一致）。
                #   唯一例外：块头**解引用了节点模态**（`if sprite.visible:`），
                #   内核里对象是 null，保留会在运行期崩 → 连体一起丢。
                is_header = (len(raw) == 1 and kind != "keep"
                             and code.rstrip().endswith(":")
                             and _balance(code) == 0
                             and re.match(r"^\s*(if|elif|else|for|while|match)\b",
                                          code))
                if is_header and not has_node_modal(strip_str_comments(code)):
                    ready_kept.extend(map_symbols(x) for x in raw)
                    continue
                shell_hit = touches_shell_member(code)
                if shell_hit or has_node_modal(strip_str_comments(code)):
                    stats["ready_shell_dropped"] += 1
                    shell_dropped[shell_hit or "节点属性"] += 1
                    continue
                src = rewritten if kind == "keep" else raw
                ready_kept.extend(map_symbols(x) for x in src)
            # ── 抢救（SALVAGE_READY_FILES）：行级丢弃引用残留符号的行。
            #    Game.connect 连的是场外流程信号（内核永不派发），丢行后
            #    空的 if 分支由 ensure_blocks_nonempty 补 pass，
            #    else 分支（`if not wasJustCrafted: randEffects()`）得以保留。
            if os.path.basename(rel) in SALVAGE_READY_FILES and ready_kept:
                pruned = salvage_ready_lines(rel, ready_kept, in_file)
                if pruned is not None:
                    ready_kept = pruned
            # 用「伪头部」给 ensure_blocks_nonempty 提供缩进上下文，
            # 使被掏空的子块（`if not pooled:` 下面全被剥掉）补上 `pass`。
            ready_kept = ensure_blocks_nonempty(
                ["func _readyInit():"] + ready_kept)[1:]
            res = residual_symbols(strip_str_comments("\n".join(ready_kept)), in_file)
            if res:
                for s in res:
                    unresolved[rel].add(s)
                stats["ready_stripped"] += 1
                ready_kept = []
            init_lines += ready_kept
            stats["ready_merged"] += 1
        if len(init_lines) == 2:
            init_lines.append("\tpass")
        new_funcs.append(["\n".join(init_lines), "_readyInit"])

        # ── 组装文件：成员声明块 ──
        head = []
        seen_members = set()
        for l in kept_decls + onready_decls:
            if not l.strip() or l.startswith("extends "):
                continue
            mm = re.match(r"^(?:export\b[^\n]*?\s+)?var\s+([A-Za-z_]\w*)", l.strip())
            if mm:
                if mm.group(1) in seen_members:
                    continue
                seen_members.add(mm.group(1))
            head.append(l)

        # ── 适配层过滤（仅基类 Item.gd）──
        #   只保留 CoreItem 之外的剩余面：内核版本权威，同名一律以内核为准。
        #   `_readyInit` 例外：内核的是空实现 `pass`，适配层要保留自己的
        #   onready 赋值链（父先子后），故不参与「同名丢弃」。
        if rel == ITEM_BASE:
            keep_init = [(t, n) for t, n in new_funcs if n == "_readyInit"]
            drop_them = [(t, n) for t, n in new_funcs if n != "_readyInit"]
            keep_init_names = {n for _t, n in keep_init}
            others, head, dr_funcs, dr_decls = filter_shim(
                drop_them, head, CORE_ITEM_NAMES)
            shim_dropped = (dr_funcs, dr_decls)
            new_funcs = keep_init + others if keep_init_names else others

        ext_line = "extends %s" % (parent if parent else "CoreItem")
        parts = [ext_line] + head + [""]
        for text, _n in new_funcs:
            parts.append(text)
            parts.append("")
        # 内嵌类：映射后逐个输出；若内核基类已有同名内嵌类（如 CoreItem 自带
        # `class SignalConnection`），丢弃适配层版本，避免遮蔽内核实现。
        for iname, itext in inner:
            if rel == ITEM_BASE and iname in CORE_ITEM_NAMES["inner"]:
                shim_dropped[0].append("class " + iname)
                continue
            parts.append(transpile_inner_class(itext, in_file, type_scope))
            parts.append("")
        outputs[rel] = "\n".join(parts)

    # ── 输出 ──
    if not dry:
        for rel, text in outputs.items():
            path = os.path.join(OUT, rel.replace("/", os.sep))
            os.makedirs(os.path.dirname(path), exist_ok=True)
            with io.open(path, "w", encoding="utf-8", newline="\n") as fh:
                if rel == ITEM_BASE:
                    fh.write(shim_header(outputs))
                fh.write(text)

    # ── 报告 ──
    rep = []
    rep.append("build_item_scripts 报告")
    rep.append("=" * 68)
    rep.append("物品脚本 %d（跳过非物品 %d）" % (len(items), len(skipped)))
    rep.append("函数保留 %d" % stats["func_kept"])
    rep.append("  整函数剥离 —— 节点模态 %d、残留符号 %d" %
               (stats["func_stripped_modal"], stats["func_stripped_residual"]))
    rep.append("  行级抢救（SALVAGE_FUNCS 点名）%d 个" % stats["func_salvaged"])
    rep.append("视觉行删除 %d、视觉调用剥成 null %d" %
               (stats["line_dropped"], stats["line_rewritten"]))
    rep.append("onready：表达式求值保留 %d、视觉节点引用删除 %d" %
               (stats["onready_var"], stats["onready_visual_dropped"]))
    rep.append("虚拟计时器创建 %d 个（其中 %d 个带 tscn timeout 回调）" %
               (stats["timer_created"], stats["timer_with_callback"]))
    rep.append("_ready 合并进 _readyInit：%d 个文件" % stats["ready_merged"])
    rep.append("R3b `_ready` 壳初始化行丢弃 %d 行（涉及成员 %d 种）"
               % (stats["ready_shell_dropped"], len(shell_dropped)))
    if shell_dropped:
        rep.append("   " + "、".join(
            "%s×%d" % (k, v) for k, v in shell_dropped.most_common(12)))
    rep.append("")
    rep.append("★ 基类适配层 gd_core_items/Item.gd")
    rep.append("   被内核覆盖丢弃：函数 %d 个、声明 %d 个"
               % (len(shim_dropped[0]), len(shim_dropped[1])))
    rep.append("   保留：见 gd_core_items/Item.gd（内核未实现的判定辅助 + 壳成员）")
    rep.append("")
    reasons = collections.Counter(s[3] for s in stripped_funcs)
    # A/B 对照用：把剥离明细落到文件（含全部非战斗函数，便于两次运行 diff）
    dump = os.environ.get("ITEM_STRIP_DUMP")
    if dump:
        with io.open(dump, "w", encoding="utf-8", newline="\n") as fh:
            for rel, name, isb, reason, sample in sorted(stripped_funcs):
                fh.write("%s\t%s\t%s\t%s\t%s\n"
                         % (rel, name, "B" if isb else "-", reason, sample))
    rep.append("剥离原因分布")
    for k, v in reasons.most_common(15):
        rep.append("   %-30s %d" % (k, v))

    battle_stripped = [s for s in stripped_funcs if s[2]]
    rep.append("")
    rep.append("★ 被剥离的**战斗函数**（%d 个，需人工定裁）" % len(battle_stripped))
    agg = collections.Counter(s[1] for s in battle_stripped)
    for name, n in agg.most_common(40):
        rep.append("   %-26s %d 个文件" % (name, n))
    rep.append("")
    rep.append("  明细（前 45 条）")
    for rel, name, _b, reason, sample in battle_stripped[:45]:
        rep.append("   %-38s %-24s %s" % (rel, name, reason))
        rep.append("        %s" % sample)

    rep.append("")
    rep.append("被剥离的非战斗函数（前 25 种）")
    nonbattle = collections.Counter(s[1] for s in stripped_funcs if not s[2])
    for name, n in nonbattle.most_common(25):
        rep.append("   %-26s %d 个文件" % (name, n))

    rep.append("")
    sym_files = collections.defaultdict(set)
    for rel, syms in unresolved.items():
        for s in syms:
            sym_files[s].add(rel)
    rep.append("导致剥离的外部符号（%d 种）" % len(sym_files))
    for s, files in sorted(sym_files.items(), key=lambda kv: -len(kv[1]))[:30]:
        rep.append("   %-28s %d 个文件" % (s, len(files)))
    rep.append("")
    rep.append("★ 无任何剥离的文件：%d / %d"
               % (len(items) - len({s[0] for s in stripped_funcs}), len(items)))
    text = "\n".join(rep) + "\n"
    os.makedirs(os.path.dirname(REPORT), exist_ok=True)
    with io.open(REPORT, "w", encoding="utf-8", newline="\n") as fh:
        fh.write(text)
    print("\n" + text)
    return 0


if __name__ == "__main__":
    sys.exit(main())
