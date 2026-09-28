# -*- coding: utf-8 -*-
"""gd_core_py 运行时垫片（手写文件，不被 tools/gd_to_py.py 覆盖）。

职责：提供 gd_core / gd_core_items 转写产物所依赖的、Python 没有对应物的
GDScript 语义。分四块：

  ① GDScript 内建函数（数值语义与 Python 不同者，一律垫片）
  ② 容器方法垫片（`.size()` / `.push_back()` / `.remove(i)` 等语义差异）
  ③ Godot 对象模型（Object / Reference / 信号 / FuncRef / Vector2 / enum）
  ④ RandomNumberGenerator —— **逐位等价**的 PCG32（见下）

★ `__all__` 必须显式列出全部名字（含下划线开头的垫片）：
  `from ._rt import *` 在无 `__all__` 时**跳过**下划线名，_div/_mod/_iter 会直接
  NameError —— 而每个生成模块都以这一行开头，漏了就是 521 个模块全崩。

────────────────────── 本文件里的「N 处调用」怎么核 ──────────────────────
本文件多处注释写着「项目里 N 处调用」之类的断言。这类数字**没有任何东西在守**，
写的时候可能是真的、后来某件物品用上了就变成假的，而**假断言不会报错**。

故本文件全部此类数字一律用同一支工具现算，判据是「代码列」而非注释列：

    python tools/count_api_usage.py --call --bare <符号>      # 调用点
    python tools/count_api_usage.py <符号>                    # 任意词边界出现

★ `--bare` 不可省：它排除前置为 `.` 的命中，用来区分**全局内建**与**对象方法** ——
  例如 `randomize()`（内建，裸调用 0 处）与 `rng.randomize()`（`RandomNumberGenerator`
  的方法，有 1 处）。两者混为一谈会得出完全相反的结论。
★ 曾经出过错的两处（已订正）：① `Color` 的「51 处命中全在注释」实为
  「gd_core 0 处、gd_core_items 51 处**代码**」；② `Color.White` 的「4 处」是
  `grep -E "Color\\.White"` 误匹配 `PieceColor.White` 的**伪足迹**，实算 0 处。

─────────────────────────── RNG 对齐依据 ───────────────────────────
源码存档 output/godot_src/（取自 godotengine/godot @ 3.6-stable）：
  thirdparty/misc/pcg.cpp               pcg32_random_r / pcg32_srandom_r
  core/math/random_pcg.h                rand() / randf() / randd() / random(f,t)
  core/math/random_number_generator.h   randi / randf_range / randi_range
实测基准：gd_core_test/RngProbe.gd 导出 gd_core_test/rng_probe.bin，
         tools/verify_godot_rng.py 逐位比对（不通过则本文件即为错）。

三个容易踩空的地方（照直觉写必错）：
  1. `randf()` **消费两个 rand()**：第一个取指数位、第二个取尾数位。
     所以 randf() 的第 1 个值和 randi() 的第 1 个值**不是同一个 rand()**。
  2. `randf()` 全程 **float32**：`(float)(rand()|0x80000001)` 会舍入，
     再 `ldexpf` 到 [-63,-32] 次幂。用 float64 算会得到不同的低位。
  3. `randf_range(from, to)` 走 `RandomPCG::random(float, float)` 重载
     （real_t 与 float 精确匹配），即 `randf() * (to - from) + from` 全部
     float32 运算；`randi_range` 则是 `rand() % (to-from+1) + from`。
"""

from __future__ import annotations

import builtins
import copy
import math
import random
import struct

# `RandomNumberGenerator.randomize()` 是否被触发过 —— 那意味着可复现性已丢失，
# 闸门应当据此判失败（[0] 是可变单元，避免 global 声明）。
_RANDOMIZED = [False]

__all__ = [
    # ── ① GDScript 内建 ──
    # ★ 刻意**不**列出 abs/min/max/int/float/bool/len/range/print/str：
    #   本模块没有同名定义，列出会让 `from ._rt import *` 抛
    #   AttributeError（__all__ 里的名字必须真实存在）；且这几个的语义与
    #   Python 内建一致，直接用内建即可。
    "PI", "TAU", "INF", "NAN", "f32",
    "floor", "ceil", "round", "clamp", "stepify", "fmod", "posmod", "snapped",
    "sqrt", "pow", "sign", "lerp", "inverse_lerp", "smoothstep", "move_toward",
    "wrapf", "wrapi", "deg2rad", "rad2deg", "is_instance_valid",
    "OS_has_feature", "randomize", "_gd_str", "_strv", "_gd_range", "_gd_fmt",
    "String", "Dictionary",
    # GDScript 全局函数与常量（转写产物按字面名字引用，见函数定义处的说明）
    "typeof", "tr", "TYPE_VECTOR2",
    # ── ② 容器/语义垫片 ──
    "_div", "_mod", "_iter", "_dup", "_erase", "_pop_at", "_find", "_resize",
    "_sort_custom", "_shuffle", "_get_slice", "_invert", "_hash", "_join",
    "_load", "_gid", "_fill", "_pick_random", "_substr",
    # ── ③ 对象模型 ──
    "GodotObject", "Reference", "Object", "Node", "Node2D", "Resource",
    "Signal", "FuncRef", "EnumDict", "Vector2", "Vector3", "Color",
    "GD_DEFAULT",
    # ── ④ RNG ──
    "RandomNumberGenerator", "PCG32",
]


# ═══════════════════════════ ① GDScript 内建 ═══════════════════════════

_F32 = struct.Struct("<f")


def f32(x):
    """把 double 舍入到 float32 再取回 double。

    Godot 3 官方构建的 `real_t` 是 float32；`RandomPCG::randf()` 与
    `RandomPCG::random(float,float)` 全程在 float32 上运算，直译成 Python
    的 float64 会在低位分叉，于是冷却/命中/暴击逐场漂移。
    """
    return _F32.unpack(_F32.pack(x))[0]


PI = math.pi
TAU = math.pi * 2.0
INF = math.inf
NAN = math.nan


def floor(x):
    """GDScript 的 floor 返回 float（不是 int）—— 直接 return 给 `-> int` 由调用方 int()。"""
    return float(math.floor(x))


def ceil(x):
    return float(math.ceil(x))


def round(x):
    """★ 不是 Python 内建 round（银行家舍入）。

    Godot: `(x >= 0) ? floor(x + 0.5) : -floor(-x + 0.5)`，即**远离零**。
    round(2.5)：GDScript 3、Python 2 —— 差一个整点，直接改判定。
    """
    return float(math.floor(x + 0.5) if x >= 0 else -math.floor(-x + 0.5))


def clamp(v, lo, hi):
    return lo if v < lo else (hi if v > hi else v)


def stepify(value, step):
    """GDScript: floor(value / step + 0.5) * step（step == 0 时原样返回）。"""
    if step == 0:
        return value
    return floor(_div(value, step) + 0.5) * step


def fmod(x, y):
    """C 语义：符号随被除数。与 Python 的 `%`（随除数）不同。"""
    return math.fmod(x, y)


def posmod(x, y):
    """GDScript fposmod：符号随除数（= Python 的 %）。"""
    return x % y


def snapped(x, step):
    if step == 0:
        return x
    return floor(x / step + 0.5) * step


def sqrt(x):
    """GDScript sqrt(负数) 返回 NAN 而非抛异常。"""
    if x < 0:
        return NAN
    return math.sqrt(x)


def pow(x, y):
    """GDScript pow 走 C pow：负底数 + 分数指数 → NAN，Python 内建会抛 ValueError。"""
    try:
        return math.pow(x, y)
    except (ValueError, OverflowError):
        return NAN


def sign(x):
    return (x > 0) - (x < 0)


def lerp(a, b, t):
    return a + (b - a) * t


def inverse_lerp(a, b, v):
    if a == b:
        return 0.0
    return (v - a) / (b - a)


def smoothstep(a, b, v):
    t = clamp(inverse_lerp(a, b, v), 0.0, 1.0)
    return t * t * (3.0 - 2.0 * t)


def move_toward(from_, to, delta):
    return from_ + clamp(to - from_, -delta, delta)


def wrapf(value, min_, max_):
    r = max_ - min_
    if r == 0:
        return min_
    return value - r * floor((value - min_) / r)


def wrapi(value, min_, max_):
    return int(wrapf(value, min_, max_))


def deg2rad(d):
    return d * PI / 180.0


def rad2deg(r):
    return r * 180.0 / PI


def is_instance_valid(obj):
    return obj is not None


# ── GDScript 全局函数：typeof / tr ──
#
# ★ 这两个是**转写产物的字面名字**：`gd_core_items/**/*.gd` 里写的就是
#   `typeof(state) == TYPE_VECTOR2` / `tr("CARD_HINT")`，GDScript 侧由 Godot
#   原生提供，Python 侧没有 → `NameError`。
#   实测缺口：`typeof` 1 处（ChessPiece）、`tr` 3 处（Joker / Reverse / ChessPiece）。
#   由 `tools/scan_translit_gaps.py --undef` 守住，别只靠跑一遍去发现。

# Variant::Type 的取值（Godot 3.6 `core/variant/variant.h`）。
# ★ 只定义**有调用点**的那一个：全项目只有 `TYPE_VECTOR2`。
#   需要别的时按同一张表补（NIL=0 BOOL=1 INT=2 REAL=3 STRING=4 VECTOR2=5
#   RECT2=6 VECTOR3=7 TRANSFORM2D=8 PLANE=9 QUAT=10 AABB=11 BASIS=12
#   TRANSFORM=13 COLOR=14 NODE_PATH=15 RID=16 OBJECT=17 DICTIONARY=18
#   ARRAY=19，之后是 Pool*Array 20–26）。
#   刻意**不**预先定义整张表 —— 没有调用点的常量＝没人守的契约。
TYPE_VECTOR2 = 5


def typeof(v):
    """`typeof()`：返回 Variant::Type。

    只覆盖本内核真正会出现的类型；其余（含一切对象实例）归 `OBJECT`。
    ★ 判 `bool` 必须排在 `int` 前：Python 里 `isinstance(True, int)` 为真，
      颠倒会让 `typeof(true)` 返回 INT 而不是 BOOL。
    """
    if v is None:
        return 0                                    # NIL
    if isinstance(v, bool):
        return 1                                    # BOOL
    if isinstance(v, int):
        return 2                                    # INT
    if isinstance(v, float):
        return 3                                    # REAL
    if isinstance(v, str):
        return 4                                    # STRING
    if isinstance(v, Vector2):
        return TYPE_VECTOR2
    if isinstance(v, Vector3):
        return 7                                    # VECTOR3
    if isinstance(v, Color):
        return 14                                   # COLOR
    if isinstance(v, (list, tuple)):
        return 19                                   # ARRAY
    if isinstance(v, dict):
        return 18                                   # DICTIONARY
    return 17                                       # OBJECT


def tr(message):
    """`Object.tr()`：无头内核里没有翻译表，返回原文。

    依据：Godot 的 `TranslationServer.translate()` 在**查不到条目**时返回原字符串，
    而本内核不加载任何 `.translation` 资源 —— 故恒等即等价。
    ★ 现有 3 个调用点**全在描述文本拼接**（`descr += ...`），不参与战斗判定。
    """
    return message


_py_abs = builtins.abs
# 同上：本模块把 floor/ceil/round 覆盖成了 GDScript 语义，故其余内建也取别名保留，
# 避免以后加垫片时误用被覆盖的名字。
_py_cos = math.cos
_py_sin = math.sin


class _GdDefault:
    """GDScript 默认参数值的哨兵（见下）。"""

    __slots__ = ()

    def __repr__(self):
        return "GD_DEFAULT"


GD_DEFAULT = _GdDefault()
"""默认参数「延迟求值」哨兵。

★ 为什么需要：GDScript 的默认参数在**每次调用时**求值，所以
  `func f(x = descriptor.activationAni)` 与 `func f(v = Vector2(0, 0))`
  都合法，且每次拿到**新**对象。Python 的默认值只在**函数定义时**求值一次：
    · 引用成员 → 定义时没有 self，直接 NameError（转写器无法在签名里补 self.）；
    · 容器/对象字面量 → 所有调用共享同一个实例。
  两者都会静默改变行为。故非字面量默认值一律写成 `= GD_DEFAULT`，
  由函数体首行 `if x is GD_DEFAULT: x = <原表达式>` 还原 —— 此时 self 已就绪，
  且每次调用重新求值。
"""


def _gd_str(x):
    """GDScript 的 str()：float 整数化不带 `.0`，容器带 [] / {}。

    ★ 刻意**不**导出为 `str`：项目里 `str()` 有少量调用点且多为日志，
      覆盖 Python 内建 `str` 的影响面比收益大。待核对用法后再决定。
    """
    if x is None:
        return "Null"
    if isinstance(x, bool):
        return "True" if x else "False"
    if isinstance(x, float):
        if x == int(x) and abs(x) < 1e16:
            return str(int(x))
        return repr(x)
    if isinstance(x, (list, tuple)):
        return "[%s]" % ", ".join(_gd_str(i) for i in x)
    if isinstance(x, dict):
        return "{%s}" % ", ".join("%s: %s" % (_gd_str(k), _gd_str(v))
                                  for k, v in x.items())
    return str(x)


def _gd_range(*args):
    """GDScript `range()` —— 返回 **Array**，不是 Python 的惰性 range。

    ★ 这是会静默失真的地方：GDScript 的 range 是货真价实的数组，可拼接、可下标、
      有 `.size()`。`CoreConst.getStacks()` 就是
      `[EventType.Block] + getBuffs() + getDebuffs()` —— 直译成 Python 会抛
      `TypeError: can only concatenate list (not "range") to list`（这条会报错，
      还算走运）；而 `range(3)[0]`、`range(3).size()` 之类会**静默**给出错误结果。
    生成器把裸 `range(` 统一改写成本函数（8 处），不遮蔽 Python 内建。

    ★ 实参按 **int 截断（向零）** —— GDScript 的 range 接受 float 并把 Variant 转 int。
      实测（gd_core_test/RangeProbe.gd，本机 Godot 3.6）：
        range(2.5)→[0,1]  range(2.9)→[0,1]  range(-2.5)→[]   range(0.4)→[]
        range(1.5,4.5)→[1,2,3]  range(-1.5,2.7)→[-1,0,1]
        range(5,0,-1.7)→[5,4,3,2,1]  range(0,5,-1)→[]
      与 Python 的 `int()` 截断方向完全一致，故直接 int() 即可。
      `pickRandomStacksToGive` 里 `range(numStacks)` 的 numStacks 是 float，
      不做截断会直接 TypeError（转写产物实测撞到）。
    """
    return list(range(*[int(a) for a in args]))


def _gd_fmt(fmt, args):
    """GDScript `"…" % x` —— 右侧是 Array 时按**逐元素**填参。

    ★ 这是 Python `%` 会静默给错结果的地方：Python 把 list/tuple 当**单值**
      （`"%s" % [1, 2]` → `"[1, 2]"`），GDScript 则展开成多个实参
      （`"%s %s" % ["a", "b"]` → `"a b"`）。故右侧容器统一转 tuple。
    """
    if isinstance(args, (list, tuple)):
        return fmt % tuple(args)
    return fmt % args


def _strv(*args):
    """GDScript `str(a, b, c)` —— **多参数是拼接**，不是 Python 的 `str(x)`。

    ★ 只有 GDScript 侧的多参形式才走这里：1 参仍是 Python 内建 `str`，
      由生成器按**实参个数**分流（tools/gd_to_py.py 的 Rewriter._str_calls）。
      写成「一律覆盖 str」会连带打断 `isinstance(x, str)` 这类类型检查
      （`is String` 被转成 `isinstance(x, str)`），故不做全局遮蔽。
    """
    if len(args) == 1:
        return _gd_str(args[0])
    return "".join(_gd_str(a) for a in args)


def String(x=""):
    """GDScript `String(x)` 构造器（单参）。

    与 `_gd_str` 同语义，只在数值格式上区别于 Python 内建：
    GDScript `String(1.0)` = `"1"`，Python `str(1.0)` = `"1.0"`。
    项目里 8 处，全部落在物品描述文本与参数名拼装上
    （`Item.gd` 的 insertParameter / getP(str("scale", …))），
    后者生成的是 `getP` 的**键**，格式错了会静默取不到参数。
    """
    return _gd_str(x)


def Dictionary():
    """GDScript `Dictionary()` 构造器 → 空字典（9 处，全部零参）。"""
    return {}


def OS_has_feature(_feature):
    """无头内核恒为「非编辑器、非编辑器构建」。

    ★ 与 gd_core 的取值必须一致：CoreItemData 用它决定 _editor / _full_version
      等标志位，而这些标志位参与 isReleased() —— 双引擎对照时两边必须同值。
    """
    return False


def randomize():
    """全局内建 `randomize()` —— **裸调用 0 处**，保持 no-op。

    ★ 「0 处」是 `tools/count_api_usage.py --call --bare randomize` 的实算结果，
      不是印象。grep 会数出 1 处 `randomize`，但那处是 `CoreRng.gd:25` 的
      `rng.randomize()` —— **对象方法**，已由本文件 `RandomPCG.randomize()` 真实现。
      两者混为一谈会得出相反的结论，故 count_api_usage 特意区分裸调用 / 点调用。
    """
    return None


# ═══════════════════════════ ② 容器/语义垫片 ═══════════════════════════

MASK64 = (1 << 64) - 1
UINT32_MAX = 0xFFFFFFFF


def _div(a, b):
    """GDScript `/` 语义。

    ★ 两个 int → **截断整除**（C 语义，向零取整）；任一是 float → 真除。
      直译成 Python 会得到真除：`activations / activationsToTrigger` 从 0 变成
      0.333…，触发次数判定整体失真，且不报任何错。
    """
    if isinstance(a, bool) or isinstance(b, bool):
        return a / b
    if isinstance(a, int) and isinstance(b, int):
        if b == 0:
            raise ZeroDivisionError("integer division by zero")
        q = abs(a) // abs(b)
        return -q if (a < 0) != (b < 0) else q
    return a / b


def _mod(a, b):
    """GDScript `%` 语义。

    ★ 两个 int → **符号随被除数**（C 的 `%`）；Python 的 `%` 符号随除数：
      `-5 % 2` 在 GDScript 是 -1、Python 是 1。凡是「轮转取余」的判定都会反向。
      float → `Math::fmod` 语义。
    """
    if isinstance(a, int) and isinstance(b, int):
        if b == 0:
            raise ZeroDivisionError("integer modulo by zero")
        r = abs(a) % abs(b)
        return -r if a < 0 else r
    return math.fmod(a, b)


def _iter(x):
    """GDScript `for v in X` 的迭代值。

    ★ `for i in 5` 在 GDScript 迭代 0..4；`for k in dict` 迭代 **key**。
      Python 里 `for i in 5` 直接 TypeError。

    ★ **float 也「可迭代」，且不是 `range()`**：实测（gd_core_test/IterProbe.gd，
      本机 Godot 3.6，逐条打印元素值与 typeof）：
        for i in 3.0  → 0,1,2      （3 次）
        for i in 2.5  → 0,1,2      （3 次 —— 不是 range(2.5) 的 2 次！）
        for i in 0.5  → 0          （1 次）
        for i in -1.5 → 空
        元素类型是 **int**（typeof=2）
      即「i 从 0 递增，只要 `i < 该 float` 就继续」→ 等价于 `range(ceil(f))`。
      写成 `range(f)` 会把 `for i in 2.5` 少跑一轮 —— 而 `CoreBuff.gainTemporary`
      的层数就是 `for i in amount:`，amount 是 float（护甲/尖刺按层结算），
      少一轮会让整类层数结算静默偏少。
    """
    if isinstance(x, dict):
        return list(x.keys())
    if isinstance(x, (list, tuple, set, range)):
        return x
    if isinstance(x, float):
        # 注意顺序：先 float 再 int（bool 是 int 的子类，但 GDScript 里
        # `for i in true` 同样是按 1 迭代，行为一致，无需特判）
        return range(int(math.ceil(x))) if x > 0 else range(0)
    if isinstance(x, int):
        return range(x)
    return x


def _fill(coll, value):
    """`Array.fill(v)`：**原地**把全部元素设为 v（不改变长度）。

    ★ 不是 Python 里任何内建的等价物 —— `list` 没有 fill，`[v] * n` 会换掉对象
      （调用方可能持有原引用）。`self.itemMetrics.fill(0)`（CoreItem.setup:240）
      就是原地填充，写成返回新表会让指标数组与实例脱钩。
    """
    for i in range(len(coll)):
        coll[i] = value
    return coll


def _pick_random(coll):
    """`Array.pick_random()`：用一个元素**随机**取。

    ★ 走 `_math_rng()`（与 `_shuffle` 同一路数）：Godot 的 `pick_random` 用的是
      全局 RNG，原版那里本就不可复现。内核统一收敛到注入种子，保证同种子同结果 ——
      这是内核的**有意偏差**（docs/gd_core_truth.md 第 6 节同类）。
    """
    n = len(coll)
    if n == 0:
        return None
    return coll[_math_rng().randi() % n]


def _substr(s, from_, length=None):
    """`String.substr(from, len)`：按**字符**截取。

    语义要点（与 Python 切片不同的两处，都在下标越界与负长度上）：
      · GDScript 的 from 超长 → 空串（Python 切片同样给空串，一致）
      · 负 from 在 GDScript 里是「从末尾数」，Python 同理
      · length 省略 = 到末尾；length 为负 → GDScript 返回空串
    """
    if not isinstance(s, str):
        s = _gd_str(s)
    n = len(s)
    start = int(from_)
    if start < 0:
        start = max(0, n + start)
    if length is None:
        return s[start:]
    ln = int(length)
    if ln < 0:
        return ""
    return s[start:start + ln]


def _dup(x, deep=False):
    """`Array.duplicate()` / `Dictionary.duplicate()`：**浅拷贝**（元素仍共享）。"""
    if deep:
        return copy.deepcopy(x)
    if isinstance(x, dict):
        return dict(x)
    if isinstance(x, list):
        return list(x)
    return copy.copy(x)


def _erase(coll, value):
    """`Array.erase(v)` 按**值**删第一个匹配；`Dictionary.erase(k)` 按键删。"""
    if isinstance(coll, dict):
        coll.pop(value, None)
    else:
        try:
            coll.remove(value)
        except ValueError:
            pass
    return coll


def _pop_at(coll, index):
    """`Array.remove(i)` —— ★按**索引**删，不是按值（Python 的 remove 是按值）。"""
    i = int(index)
    if 0 <= i < len(coll):
        coll.pop(i)
    return coll


def _find(coll, value, from_=0):
    """`Array.find` 找不到返回 **-1**（Python 的 .index 抛 ValueError）。"""
    try:
        return coll.index(value, int(from_))
    except ValueError:
        return -1


def _resize(arr, n):
    """`Array.resize(n)`：截断或补 null。"""
    n = int(n)
    if n < len(arr):
        del arr[n:]
    else:
        arr.extend([None] * (n - len(arr)))
    return arr


def _sort_custom(coll, obj, method):
    """`Array.sort_custom(instance, "method")`：比较器返回 True 表示 a 排在 b 前。

    ★ 已知偏差（待双引擎归因）：Godot 3 的 SortArray 是**不稳定**排序，本实现
      经 cmp_to_key 后继承 Python 的**稳定**排序。对优先级相等的物品，两者的
      相对次序可能不同。项目里 3 处调用点的比较器都是严格不等判定
      （`a.getTriggerPriority() > b.getTriggerPriority()`），相等时返回 False。
    """
    import functools
    fn = getattr(obj, method) if isinstance(method, str) else method

    def _cmp(a, b):
        if fn(a, b):
            return -1
        if fn(b, a):
            return 1
        return 0

    coll.sort(key=functools.cmp_to_key(_cmp))
    return coll


def _shuffle(arr):
    """`Array.shuffle()` —— 用 **Godot 全局 RNG**（`Math::default_pcg`）。

    ★ 与 `CoreRng.shuffle`（成员实现，走 ctx 的 rng）是两条独立随机流：
      物品脚本里的裸 `arr.shuffle()` 走这一条，`ctx.rng.shuffle(arr)` 走那一条。
      这里维护一个与 Godot 同初始种子的全局实例，用于位对齐。
    """
    rng = _math_rng()
    for i in range(len(arr) - 1, 0, -1):
        j = rng.randi() % (i + 1)
        arr[i], arr[j] = arr[j], arr[i]
    return arr


_MATH_RNG = []


def _math_rng():
    if not _MATH_RNG:
        # ★ 必须是 `RandomNumberGenerator` 而不是裸 `PCG32`：
        #   `Array.shuffle()` 要的是 `Math::rand()` → `randi()`，而 PCG32 只暴露
        #   `next_u32()`。早先这里塞的是 `PCG32(DEFAULT_SEED)`，于是任何物品脚本里
        #   的裸 `arr.shuffle()` 都抛 `AttributeError: 'PCG32' object has no attribute
        #   'randi'`（实测 Cupcake Dragon 走 onPreDealDamage_early 时命中）。
        #   ★ 两者**随机流完全相同**（实测：`PCG32(DEFAULT_SEED).next_u32()` 与
        #     `RandomNumberGenerator(DEFAULT_SEED).randi()` 前 5 项逐位一致 ——
        #     `RandomNumberGenerator.seed` 的 setter 本身就是
        #     `pcg.srandom(seed, inc)`，与 `PCG32(seed)` 同一路径），
        #     所以这是**补方法**，不是改流。
        _MATH_RNG.append(RandomNumberGenerator(RandomNumberGenerator.DEFAULT_SEED))
    return _MATH_RNG[0]


def _get_slice(s, delimiter, slice_):
    """`String.get_slice(delim, idx)`：越界返回空串。"""
    parts = str(s).split(delimiter)
    i = int(slice_)
    if 0 <= i < len(parts):
        return parts[i]
    return ""


def _invert(d):
    """`Dictionary.invert()`：**原地**交换键值。"""
    items = list(d.items())
    d.clear()
    for k, v in items:
        d[v] = k
    return d


def _hash(x):
    """GDScript `hash(x)`：32 位。项目里 0 处调用，保留以免将来踩空。"""
    if isinstance(x, str):
        h = 5381
        for ch in x:
            h = ((h << 5) + h + ord(ch)) & UINT32_MAX
        return h
    if isinstance(x, (int, float, bool)) or x is None:
        return builtins.hash(x) & UINT32_MAX
    return builtins.hash(repr(x)) & UINT32_MAX


def _join(arr, sep=""):
    return str(sep).join(_gd_str(x) for x in arr)


def _load(path):
    """`load("res://...")` → 已注册的类对象（供 `Util.isItemDescriptor` 比较）。"""
    from . import _registry as _R
    return _R.C(str(path))


_GID_MAP = {}
_GID_NEXT = [1]
_GID_KEEP = []


def _gid(obj):
    """`Object.get_instance_id()`。

    Godot 用它做「实例身份集合」：`CoreEventBus` 的 emissionID 高位、
    `CoreItem.dynamicTypes` 的元素、以及 `rope_speedups` / `cube_advanced`
    这类**以物品实例为键**的字典。故必须稳定唯一，且不能随 GC 复用
    （_GID_KEEP 持强引用，避免 CPython 复用 id()）。
    """
    k = id(obj)
    g = _GID_MAP.get(k)
    if g is None:
        g = _GID_NEXT[0]
        _GID_NEXT[0] += 1
        _GID_MAP[k] = g
        _GID_KEEP.append(obj)
    return g


# ═══════════════════════════ ③ Godot 对象模型 ═══════════════════════════

class EnumDict(dict):
    """GDScript `enum` 的替身。

    原版枚举是字典语义 + 点号访问，二者都要支持：
      `CoreConst.Rarity.Food` 和 `CoreConst.StuffedClasses["None"]`
    后者是因为 `None` 是 Python 关键字（GDScript 里是合法成员名），
    转写器把它写成下标访问，下标必须走 `dict.__getitem__` 而非属性。
    """

    def __init__(self, name, members=None):
        super().__init__(members or {})
        object.__setattr__(self, "_enum_name", name)

    def __getattr__(self, k):
        try:
            return self[k]
        except KeyError:
            raise AttributeError("%s 枚举无成员 %r" % (self._enum_name, k))

    def size(self):
        return len(self)

    def empty(self):
        return not self

    def has(self, k):
        return k in self

    def __repr__(self):
        return "EnumDict(%s, %d members)" % (self._enum_name, len(self))


class Signal:
    """`signal foo` 声明出的信号对象。

    连接表在**实例**上（`GodotObject._gd_conns`），与 Godot 的 per-object
    connections 一致 —— 若把连接表挂在类属性 Signal 上，所有物品实例会共享
    同一份监听者，属于灾难级串味。
    """

    __slots__ = ("name",)

    def __init__(self, name):
        self.name = name

    def __repr__(self):
        return "Signal(%s)" % self.name


class FuncRef:
    """`funcref(instance, "method")` / `FuncRef.new().set_*()`。

    项目里只有两处真实用途：CoreCombat 把 `endCombat` 交给角色死亡回调、
    CoreEventBus 把 receiver.method 包成可调用对象。
    """

    __slots__ = ("_instance", "_method", "_binds")

    def __init__(self, instance=None, method=None):
        self._instance = instance
        self._method = method
        self._binds = []

    def set_function(self, name):
        self._method = name
        return self

    def set_instance(self, obj):
        self._instance = obj
        return self

    def get_instance(self):
        return self._instance

    def is_valid(self):
        return self._instance is not None and self._method is not None \
            and callable(getattr(self._instance, str(self._method), None))

    def call_func(self, *args):
        return getattr(self._instance, str(self._method))(*(list(args) + self._binds))

    def call_funcv(self, args):
        return getattr(self._instance, str(self._method))(*(list(args) + self._binds))


class Vector2:
    """Godot Vector2（分量运算逐分量；`v * 2` 是缩放）。

    ★ 存 double 而非 float32：格坐标全是小整数，两种精度结果相同；
      但 double 不会在 `cell + direction * offset` 链上累积舍入。
    """

    __slots__ = ("x", "y")

    def __init__(self, x=0.0, y=0.0):
        object.__setattr__(self, "x", float(x))
        object.__setattr__(self, "y", float(y))

    def __setattr__(self, k, v):
        object.__setattr__(self, k, float(v))

    ZERO = None
    ONE = None
    RIGHT = None
    LEFT = None
    UP = None
    DOWN = None
    INF = None

    def __add__(self, o):
        return Vector2(self.x + o.x, self.y + o.y)

    def __sub__(self, o):
        return Vector2(self.x - o.x, self.y - o.y)

    def __neg__(self):
        return Vector2(-self.x, -self.y)

    def __mul__(self, o):
        if isinstance(o, Vector2):
            return Vector2(self.x * o.x, self.y * o.y)
        return Vector2(self.x * o, self.y * o)

    def __rmul__(self, o):
        return Vector2(self.x * o, self.y * o)

    def __truediv__(self, o):
        if isinstance(o, Vector2):
            return Vector2(self.x / o.x, self.y / o.y)
        return Vector2(self.x / o, self.y / o)

    def __eq__(self, o):
        return isinstance(o, Vector2) and self.x == o.x and self.y == o.y

    def __ne__(self, o):
        return not self.__eq__(o)

    def __hash__(self):
        return hash((self.x, self.y))

    def __iter__(self):
        return iter((self.x, self.y))

    def __repr__(self):
        return "(%s, %s)" % (_gd_str(self.x), _gd_str(self.y))

    def __bool__(self):
        return self.x != 0.0 or self.y != 0.0

    def copy(self):
        return Vector2(self.x, self.y)

    def length(self):
        return math.sqrt(self.x * self.x + self.y * self.y)

    def length_squared(self):
        return self.x * self.x + self.y * self.y

    def distance_to(self, o):
        return Vector2(self.x - o.x, self.y - o.y).length()

    def distance_squared_to(self, o):
        dx, dy = self.x - o.x, self.y - o.y
        return dx * dx + dy * dy

    def normalized(self):
        n = self.length()
        return Vector2(self.x / n, self.y / n) if n != 0 else Vector2()

    def floor(self):
        return Vector2(math.floor(self.x), math.floor(self.y))

    def round(self):
        return Vector2(round(self.x), round(self.y))

    def abs(self):
        return Vector2(_py_abs(self.x), _py_abs(self.y))

    def rotated(self, phi):
        """`Vector2.rotated(phi)`：逆时针旋转 phi **弧度**（Godot 2D 里 y 向下，
        故屏幕上看起来是顺时针；公式本身与引擎一致）。

        ★ 本项目唯一使用点在国际象棋棋子 `ChessPiece.gd:35`
          （`cell.rotated(rotation).round()`）—— 它属**判定路径**（算移动格），
          故必须逐字对齐：引擎实现就是
          `Vector2(x * cos - y * sin, x * sin + y * cos)`。
        """
        c, s = _py_cos(phi), _py_sin(phi)
        return Vector2(self.x * c - self.y * s, self.x * s + self.y * c)

    def as_tuple(self):
        return (self.x, self.y)


Vector2.ZERO = Vector2(0.0, 0.0)
Vector2.ONE = Vector2(1.0, 1.0)
Vector2.RIGHT = Vector2(1.0, 0.0)
Vector2.LEFT = Vector2(-1.0, 0.0)
Vector2.UP = Vector2(0.0, -1.0)
Vector2.DOWN = Vector2(0.0, 1.0)
Vector2.INF = Vector2(INF, INF)


class Vector3:
    __slots__ = ("x", "y", "z")

    def __init__(self, x=0.0, y=0.0, z=0.0):
        self.x, self.y, self.z = float(x), float(y), float(z)

    ZERO = None

    def __eq__(self, o):
        return isinstance(o, Vector3) and (self.x, self.y, self.z) == (o.x, o.y, o.z)

    def __hash__(self):
        return hash((self.x, self.y, self.z))

    def __repr__(self):
        return "(%s, %s, %s)" % (self.x, self.y, self.z)


Vector3.ZERO = Vector3()


class Color:
    """GDScript 的 Color。

    用量实算（`tools/count_api_usage.py Color`）：
      · `gd_core/`      **0 处**（代码 0 / 注释 0）
      · `gd_core_items/` **51 处 / 29 个文件**（Top: MagicRing 10、Item 8、SpintoWin 5）
    物品脚本是逐字直挂的，故必须有。具名常量见文件末尾的 `_attach_named_colors()`。
    """

    __slots__ = ("r", "g", "b", "a")

    def __init__(self, r=0.0, g=0.0, b=0.0, a=1.0):
        self.r, self.g, self.b, self.a = float(r), float(g), float(b), float(a)

    def __eq__(self, o):
        return (isinstance(o, Color)
                and (self.r, self.g, self.b, self.a) == (o.r, o.g, o.b, o.a))

    def __hash__(self):
        return hash((self.r, self.g, self.b, self.a))

    def __repr__(self):
        return "Color(%s, %s, %s, %s)" % (self.r, self.g, self.b, self.a)


def _attach_named_colors():
    """把 Godot 3.6 的 146 个具名颜色挂成 `Color.<name>` 类属性。

    ★ 不做的话会在**物品脚本构造时**就炸：`Item._init_fields` 里那句
      `self.defaultColor = Color.white`（Item.gd:352）是 `AttributeError`。
      这类静态库数据必须补齐，它不是死代码，也没有「用不到就不实现」的余地 ——
      因为 `Item` 是全部 502 件物品的基类。

    ★ **不加** `Color.White` / `Color.Black` 这类大写别名：Godot 的静态色常量全小写。
      仓库里曾搜出的「`Color.White` 4 处」是 `grep -E "Color\\.White"` 把
      `PieceColor.White` 一并匹配的**伪足迹** —— 实算 `Color.White` = 0 处
      （`Color.white` = 1 处，就是 Item.gd:352）。加大写别名等于**杜撰引擎里没有的
      常量**，会让一处笔误静默通过，故不做。
    """
    from ._colors import _COLOR_NAMES
    for _n, _v in _COLOR_NAMES.items():
        setattr(Color, _n, Color(*_v))


_attach_named_colors()


class GodotObject:
    """`Object` / `Reference` 的替身，也是全部 gd 类的基类。

    ★ 实例化链路刻意做成 `__init__ → _init_fields() → _init()`：
      GDScript 的求值顺序是「先父类字段、后子类字段，字段全部就绪后才调 _init」。
      `_init_fields()` 由生成器发射（类体层的 `var` 逐实例赋值），
      `_init()` 就是原版那个 `func _init`（**不改名**，因为跨类调用
      `._init(...)` 会被转成 `super()._init(...)`，改名就断了）。
    """

    resource_path = None

    def __init__(self, *args, **kwargs):
        self._init_fields()
        self._init(*args, **kwargs)

    def _init_fields(self):
        pass

    def _init(self, *args, **kwargs):
        pass

    # ── Object 接口 ──

    def has_method(self, name):
        """`Object.has_method` —— 只认真方法，不认字段。

        ★ 这是 `_behavior` 两级派发的判据：CoreItem 用它决定「物品脚本自己是否
          实现了该回调」。把属性误判成方法会让回落分支去调一个非可调用对象。
        """
        return callable(getattr(self, str(name), None))

    def call(self, name, *args):
        return getattr(self, str(name))(*args)

    def callv(self, name, args):
        return getattr(self, str(name))(*(args or []))

    def get_instance_id(self):
        return _gid(self)

    def get_script(self):
        """返回类对象本身 —— `Util.isItemDescriptor` 拿它和 `load(path)` 比相等。"""
        return type(self)

    def get_class(self):
        return type(self).__name__

    def free(self):
        return None

    def set_script(self, _s):
        return None

    # ── 信号 ──

    def emit_signal(self, name, *args):
        conns = self.__dict__.get("_gd_conns")
        if not conns:
            return
        for target, method in list(conns.get(str(name), ())):
            cb = getattr(target, str(method), None)
            if callable(cb):
                cb(*args)

    def connect(self, signal, target, method, binds=None):
        conns = self.__dict__.setdefault("_gd_conns", {})
        conns.setdefault(str(signal), []).append((target, method))
        return None

    def disconnect(self, signal, target, method):
        conns = self.__dict__.get("_gd_conns")
        if not conns:
            return
        lst = conns.get(str(signal))
        if not lst:
            return
        conns[str(signal)] = [c for c in lst if c != (target, method)]

    def is_connected(self, signal, target, method):
        conns = self.__dict__.get("_gd_conns")
        if not conns:
            return False
        return (target, method) in conns.get(str(signal), ())


# 内建类型别名：TYPE_MAP 把 Reference/Object/Node 等一律映射到 GodotObject
Reference = GodotObject
Object = GodotObject
Node = GodotObject
Node2D = GodotObject
Resource = GodotObject


# ═══════════════════════════ ④ RandomNumberGenerator ═══════════════════════════

PCG_MULT = 6364136223846793005
PCG_DEFAULT_INC_64 = 1442695040888963407


class PCG32:
    """`thirdparty/misc/pcg.cpp` 的直译（M.E. O'Neill 的 minimal PCG32）。

    只暴露 next_u32()（= pcg32_random_r）；randf/randd 的浮点转换放在
    RandomNumberGenerator 层 —— 因为 Godot 把转换放在 RandomPCG 上，
    而 randi_range 等直接用 rand() 原始输出。
    """

    __slots__ = ("state", "inc")

    def __init__(self, seed_=0, init_seq=PCG_DEFAULT_INC_64):
        self.srandom(seed_, init_seq)

    def srandom(self, init_state, init_seq):
        """pcg32_srandom_r：注意 state 是 **+= initstate**（不是赋值）。"""
        self.state = 0
        self.inc = ((init_seq << 1) | 1) & MASK64
        self.next_u32()
        self.state = (self.state + init_state) & MASK64
        self.next_u32()
        return self

    def next_u32(self):
        old = self.state
        self.state = (old * PCG_MULT + self.inc) & MASK64
        xorshifted = (((old >> 18) ^ old) >> 27) & UINT32_MAX
        rot = (old >> 59) & 31
        return ((xorshifted >> rot) | (xorshifted << ((-rot) & 31))) & UINT32_MAX


class RandomNumberGenerator:
    """`core/math/random_number_generator.h` + `random_pcg.h` 的逐位等价实现。

    `seed` / `state` 做成 property：GDScript 侧写的是 `rng.seed = _seed`
    （属性赋值），转写后也是赋值 —— 若 seed 是普通方法，这行会**把方法覆盖掉**，
    下一次 `rng.seed = x` 变成对属性赋值、静默失去播种语义。
    """

    DEFAULT_SEED = 12047754176567800795
    DEFAULT_INC = PCG_DEFAULT_INC_64

    def __init__(self, p_seed=None, p_inc=None):
        object.__setattr__(self, "_inc", self.DEFAULT_INC if p_inc is None else p_inc)
        object.__setattr__(self, "_pcg", PCG32(0, self._inc))
        self.seed = self.DEFAULT_SEED if p_seed is None else p_seed

    # ── seed / state ──

    @property
    def seed(self):
        return self._current_seed

    @seed.setter
    def seed(self, v):
        """`RandomPCG::seed`：记录 current_seed，然后用 (seed, current_inc) 重播 PCG。"""
        object.__setattr__(self, "_current_seed", int(v) & MASK64)
        self._pcg.srandom(self._current_seed, self._inc)

    @property
    def state(self):
        return self._pcg.state

    @state.setter
    def state(self, v):
        self._pcg.state = int(v) & MASK64

    # ── 整数 ──

    def randi(self):
        """`RandomPCG::rand()` → uint32。"""
        return self._pcg.next_u32()

    def randi_range(self, from_, to):
        """`ret % (to - from + 1) + from`（to < from 时用反向区间）。"""
        ret = self._pcg.next_u32()
        if to < from_:
            return ret % (from_ - to + 1) + to
        return ret % (to - from_ + 1) + from_

    # ── 浮点（float32 全程）──

    def randf(self):
        """★ 消费**两个** rand()：先取指数偏移，再取尾数。

        ```c
        uint32_t proto_exp_offset = rand();
        if (proto_exp_offset == 0) return 0;
        return LDEXPF((float)(rand() | 0x80000001), -32 - CLZ32(proto_exp_offset));
        ```
        """
        proto = self._pcg.next_u32()
        if proto == 0:
            return 0.0
        clz = 32 - proto.bit_length()
        mantissa = f32(float(self._pcg.next_u32() | 0x80000001))
        return f32(math.ldexp(mantissa, -32 - clz))

    def randd(self):
        """double 版：第二个/第三个 rand() 拼 64 位尾数，再 ldexp(-64 - clz)。"""
        proto = self._pcg.next_u32()
        if proto == 0:
            return 0.0
        clz = 32 - proto.bit_length()
        hi = self._pcg.next_u32()
        lo = self._pcg.next_u32()
        sig = ((hi << 32) | lo) | 0x8000000000000001
        return math.ldexp(float(sig), -64 - clz)

    def randf_range(self, from_, to):
        """`RandomPCG::random(float, float)` = `randf() * (to - from) + from`。

        real_t 是 float32，与 float 重载精确匹配（无需 promotion），故整条链
        都在 float32 上运算 —— 每步都要重新舍入。
        """
        rf = self.randf()
        d = f32(f32(to) - f32(from_))
        return f32(f32(rf * d) + f32(from_))

    def randfn(self, mean=0.0, deviation=1.0):
        """Box-Muller（Godot 实现）。

        ★ 实算 **0 处调用**（`tools/count_api_usage.py --call --bare randfn`）。
          保留理由不是「保底」这种含糊话，而是：本类是 `RandomPCG` 的**整体重写**，
          而 `randfn` 是 `RandomNumberGenerator` 的公开 API —— 物品脚本随时可能调它。
        ★ 但「0 处调用」有一个必须说清的代价：**它的实现正确性没有被任何闸门覆盖**。
          闸门 12 的 840/840 逐位对齐只走 `randf` / `randf_range` / `randi`。
          若将来有物品用上 `randfn`，先补一条位对齐用例，再上战斗。
        """
        u1 = self.randf()
        u2 = self.randf()
        return mean + deviation * (math.cos(TAU * u2) * math.sqrt(-2.0 * math.log(u1))
                                   if u1 > 0 else 0.0)

    def randomize(self):
        """时间播种 —— 对齐引擎语义，但同时**丢弃可复现性**。

        ★ 调用点只有一处（实算：`tools/count_api_usage.py --call randomize`
          → 1 处 / `gd_core/CoreRng.gd:25`）：`if _seed == 0: rng.randomize()`。
          两个驱动器都**恒传非零种子**，故正常路径不会走到：
            · 闸门/对照：`BASE_SEED = 20260923`（`gd_core_test/LineupBattle.gd:80`
              与 `tools/run_gd_py.py:61` 同值）
            · 模拟器：`GDCoreEngine` 的 `SystemRandom().randrange(1, 2 ** 31)`
              —— 下界取 **1 而非 0** 正是为了不落进这条分支
          先前这里写的是 no-op，注释还断言「项目里 0 处调用」—— 那是句没有依据的
          结论（实际有 1 处），且 no-op 会让「种子传 0」这条路径在 Python 侧
          静默地与 Godot 不一致。故改为真播种 + 记一个标志位，供闸门断言「未触发」。
        ★ 那条闸门就是 `tools/run_gd_py.py` 的 **[7] RNG 可复现性**（`_RANDOMIZED`），
          且是**双侧**判据：正常路径须仍为 False，同时 `CoreRng(0)` 正对照须翻成 True。
          只做第一侧是无效断言（标志位若没接上就恒为 False，无条件通过）。
        """
        _RANDOMIZED[0] = True
        self.seed = random.getrandbits(64)
        return None

    # ── 兼容 Godot 的 set/get 口 ──

    def set_seed(self, v):
        self.seed = v

    def get_seed(self):
        return self.seed

    def set_state(self, v):
        self.state = v

    def get_state(self):
        return self.state
