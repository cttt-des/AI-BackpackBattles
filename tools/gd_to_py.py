#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""gd_to_py.py — 把 gd_core/ 与 gd_core_items/ 的 GDScript **机械**转写为 Python

定位
====
用户要求「把翻译后的 gd 代码转写为 py 并编译成新版模拟器」。本工具是那一步的
唯一入口：输入 gd_core（18 脚本）+ gd_core_items（503 脚本），输出纯 Python 包
gd_core_py/。转写是机械的（不做任何逻辑改写），保真的判据是
「Python 版与 GDScript 版在**同种子同阵容**下逐字符一致」—— 即
`tools/run_gd_py.py`（流水线闸门 13）拿 56 局真实对局与 Godot 基准逐行比对。

为什么可以机械转写（实测语法面，见 tools/survey_gd_syntax.py --verify）
=====================================================================
521 文件 29311 行里，GDScript 专有构造只有一小圈。**下列数字全部由
`python tools/survey_gd_syntax.py --verify` 断言（21 项），走样即 FAIL：**
  · yield / preload / setget / ** 幂 / @装饰器        —— 代码内 **0 处**
    （`onready` 9 处、`add_child` 2 处只是**注释**里的提及，代码内也是 0）
  · 场景树（$路径 / get_node / add_child）            —— 代码内 **0 处**
  · String 格式化 `%`                                —— **0 处**
    （唯一一处 `"_stacks_changed_%d" % x` 已于 2026-09-28 改为 EventType
     反查拼接修 Buff 信号名断裂，见 gd_core/CoreCharacter.gd）
  · match 20 行、enum 55 行、signal 9 行、内嵌 class 8 行、static 38 行
  · is 类型检查 24 行、`.new(` 55 行
  · 内建容器方法（调用次数）：size 63 / push_back 64 / empty 56 / clear 44 /
    erase 26 / values 11 / duplicate 8
    （★ 55/64/56 为 SALVAGE_FUNCS 点名抢救 MagicRing 等后新口径，
     断言见 tools/survey_gd_syntax.py CLAIMS）
  · Vector2 **138 行 / 198 次**（含 INF、算符、.x/.y）；Vector3 **0 次**
其余行与 Python 同形（if/for/while/return/缩进/注释）。

必须**语义级**处理的地方（都不是语法糖，照搬会静默出错）
====================================================
1. **隐式 self**：GDScript 函数体内裸引用类成员/同级方法即 self 访问
   （`fight_ended = true`、`activateItems(items)`）。Python 里裸名是局部名 →
   全部 NameError。规则：函数体内、且在「类作用域成员 ∪ 继承成员 ∪ 同级方法」
   中、又不在本函数局部名里 → 补 `self.`。类体层（缩进 0）不补，因为 Python
   的类体执行期本就共享命名空间。
2. **int/int 除法**：GDScript 3 截断整除，Python 真除。
   `activations / activationsToTrigger` 会从 0 变成 0.333…。
   做法：把含 `/` `%` 的单行语句交给 Python `ast` 重写（优先级天然正确）→
   运行时助手 `_div` / `_mod`。多行语句走字符级兜底并**逐条上报**。
3. **int%int 取余符号**：GDScript（C 语义）随被除数，Python 随除数。
   `-5 % 2` GDScript = -1、Python = 1。
4. **容器方法语义**：`.remove(i)` 在 GDScript 是**按索引**删（Python 是按值）、
   `.erase(v)` 是按值删、`.keys()/.values()` 返回**副本**（Python 返回视图）。
   每条都对应一个专门改写，**不允许同名照搬**。
5. **枚举成员撞 Python 关键字**：`CoreConst.StuffedClasses.None` 是合法 GDScript
   却是 Python 语法错误 → 改写成 `[...]["None"]`。

输出布局
========
  gd_core_py/_rt.py        —— 运行时垫片（手写，不被本工具覆盖）
  gd_core_py/_registry.py  —— 类注册表（手写）
  gd_core_py/_bootstrap.py —— 按 extends 拓扑序导入全部模块（生成）
  gd_core_py/_colors.py    —— Godot 具名色表（由 tools/gen_color_names.py 生成，
                              本工具不覆盖；流水线的 0/14 阶段每轮重出）
  gd_core_py/gd_core/*.py  —— 每个 .gd 一个模块（生成）
  gd_core_py/gd_core_items/**

类解析：GDScript 的 class_name 是全局命名空间，Python 没有。故用 _registry 做
「GDScript 名 / res:// 路径 / 文件主干名 → Python 类」映射；`extends X` 与运行期
`X.new()` 都经它解析。模块导入按 extends 依赖拓扑排序（基类先注册），与 Godot
的加载次序语义一致。

用法：
    python tools/gd_to_py.py            # 生成 gd_core_py/
    python tools/gd_to_py.py --check    # 只校验产物是否与源码同步
    python tools/gd_to_py.py --report   # 打印规则命中与未识别构造（不写文件）
"""
from __future__ import annotations

import ast
import io
import os
import re
import sys
from collections import Counter, defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC_DIRS = ("gd_core", "gd_core_items")
OUT_PKG = os.path.join(ROOT, "gd_core_py")
GEN_BANNER = ("# -*- coding: utf-8 -*-\n"
              "# 自动生成，勿手改。生成器：tools/gd_to_py.py\n")

# GDScript 内建类型/对象 → Python
TYPE_MAP = {
    "void": "None", "bool": "bool", "int": "int", "float": "float",
    "String": "str", "Array": "list", "Dictionary": "dict",
    "Vector2": "Vector2", "Vector3": "Vector3", "Color": "Color",
    "Reference": "GodotObject", "Object": "GodotObject", "Node": "GodotObject",
    "Node2D": "GodotObject", "Resource": "GodotObject", "FuncRef": "FuncRef",
    "RandomNumberGenerator": "RandomNumberGenerator",
}

LITERAL_MAP = [("null", "None"), ("true", "True"), ("false", "False")]

PY_KEYWORDS = {
    "None", "True", "False", "and", "or", "not", "if", "else", "elif", "for",
    "while", "in", "is", "lambda", "class", "def", "return", "pass", "import",
    "from", "global", "del", "with", "yield", "assert", "raise", "try",
    "except", "finally", "break", "continue", "nonlocal", "as", "print", "exec",
}

# 不能被 self. 化的名字：内建自由函数 / 垫片 / 构造器 / Python 内建
NEVER_SELF = {
    "abs", "min", "max", "str", "int", "float", "bool", "len", "range", "print",
    "floor", "ceil", "round", "clamp", "stepify", "fmod", "sqrt", "pow", "sign",
    "lerp", "randomize", "isinstance", "type", "getattr", "setattr", "hasattr",
    "callable", "enumerate", "sorted", "list", "dict", "tuple", "set", "sum",
    "any", "all", "zip", "map", "filter", "repr", "id", "super", "open",
    "PI", "INF", "NAN", "Vector2", "EnumDict", "Signal", "FuncRef", "GodotObject",
    "RandomNumberGenerator", "_div", "_mod", "_iter", "_dup", "_erase",
    "_pop_at", "_find", "_resize", "_sort_custom", "_shuffle", "_get_slice",
    "_invert", "_hash", "_join", "_load", "_gid", "OS_has_feature",
    # GDScript 全局函数（`_rt` 垫片提供，不是任何类的方法）
    "typeof", "tr",
    # Python 语法结构
    "if", "elif", "else", "for", "while", "return", "and", "or", "not", "in",
    "is", "pass", "break", "continue", "assert", "del", "lambda",
}

CONTAINER_RULES = {
    "size", "empty", "has", "push_back", "append_array", "pop_front", "pop_back",
    "duplicate", "erase", "remove", "find", "keys", "values", "front", "back",
    "sort_custom", "shuffle", "resize", "begins_with", "length", "get_slice",
    "invert", "hash", "join", "count", "bsearch", "rfind",
    # Python 里没有同名方法的 GDScript 内建（见 _render 的对应分支）：
    "fill", "pick_random", "substr", "to_lower", "to_upper",
}

SELF_METHODS = {"has_method", "call", "callv", "emit_signal", "get_instance_id",
                "get_script", "is_connected", "disconnect"}

# ★ GDScript 里合法、Python 里却是关键字的名字 —— 必须重命名，否则 SyntaxError。
#   实测本项目只用到 `from`（CoreRng.gd:65 `func randf_range(from, to)`）。
#   这些词在 GDScript 中**没有语法意义**（GDScript 无 import 语法），
#   故在代码段内做词法级替换是安全的；字符串已被 mask 保护，注释不参与改写。
# 每条容器规则的**合法实参个数区间**（min, max）。
#
# ★ 为什么必须有这个守卫：改写是**按方法名**匹配的，不看接收者类型。当项目里存在
#   与 GDScript 内建同名的自有方法时，规则会误伤 —— 而且误伤得很难看：
#   `ctx.rng.shuffle(p_items)`（CoreRng.gd:80 的自有方法，1 参）被改写成
#   `_shuffle(ctx.rng)`，**实参被整条丢掉**，于是 `len(CoreRng)` 抛 TypeError。
#   实参个数是最廉价的判别器：`Array.shuffle()` 恒 0 参、`CoreRng.shuffle(arr)` 恒 1 参。
#   实测本项目的同名冲突只有 3 处（shuffle / empty / fill），其中 empty 与 fill 的
#   调用点走的是裸调用与 `.method()` 父类调用，本就不经 _calls，故守卫主要拦 shuffle。
CONTAINER_ARITY = {
    "size": (0, 0), "empty": (0, 0), "has": (1, 1), "push_back": (1, 1),
    "append_array": (1, 1), "pop_front": (0, 0), "pop_back": (0, 0),
    "duplicate": (0, 1), "erase": (1, 1), "remove": (1, 1), "find": (1, 3),
    "keys": (0, 0), "values": (0, 0), "front": (0, 0), "back": (0, 0),
    "sort_custom": (2, 2), "shuffle": (0, 0), "resize": (1, 1),
    "begins_with": (1, 1), "length": (0, 0), "get_slice": (2, 2),
    "invert": (0, 0), "hash": (0, 0), "join": (1, 1), "count": (1, 1),
    "bsearch": (1, 3), "rfind": (1, 2),
    "fill": (1, 1), "pick_random": (0, 0), "substr": (1, 2),
    "to_lower": (0, 0), "to_upper": (0, 0),
}

PY_KEYWORD_RENAMES = (("from", "from_"),)

# GDScript「带类型、无初值」变量声明的默认值（`var x: Array`）。
# ★ 依据是**实测**而非文档：gd_core_test/DefaultProbe.gd 在本机 Godot 3.6 上
#   逐条打印 typeof 与字面值，见 tools/gd_to_py.py 里 field_inits 的注释。
#   未列出的类型（含全部 Object 派生类与无类型变量）一律是 Null → None。
GD_TYPE_DEFAULTS = {
    "bool": "False",
    "int": "0",
    "float": "0.0",
    "String": '""',
    "Array": "[]",
    "Dictionary": "{}",
    "Vector2": "Vector2()",
    "Vector3": "Vector3()",
    "Color": "Color()",
    "PoolStringArray": "[]",
    "PoolByteArray": "[]",
    "PoolIntArray": "[]",
    "PoolRealArray": "[]",
    "PoolVector2Array": "[]",
    "PoolColorArray": "[]",
}

# 裸 `str(` 调用（不带接收者、不在字符串里）：用于按实参个数分流到 _strv
_BARE_STR_RE = re.compile(r"(?<![\w.\"'])str\s*\(")
# 裸 `range(` 调用：GDScript 返回 Array，须走 _gd_range
_BARE_RANGE_RE = re.compile(r"(?<![\w.\"'])range\s*\(")

EXTENDS_RE = re.compile(r"^\s*extends\s+(\"[^\"]+\"|[A-Za-z_]\w*)\s*$")
CLASSNAME_RE = re.compile(r"^\s*class_name\s+([A-Za-z_]\w*)\s*$")
NESTED_CLASS_RE = re.compile(
    r"^\s*class\s+([A-Za-z_]\w*)\s*(?:extends\s+([A-Za-z_]\w*))?\s*:\s*$")
FUNC_RE = re.compile(r"^\s*(static\s+)?func\s+([A-Za-z_]\w*)\s*\(")
SIGNAL_DECL_RE = re.compile(r"^\s*signal\s+([A-Za-z_]\w*)\s*(\((.*)\))?\s*$")
ENUM_RE = re.compile(r"^\s*enum\s*([A-Za-z_]\w*)?\s*\{")
# 声明修饰符：onready（节点就绪时赋值）、export / export(Type)（编辑器导出）
DECL_RE = re.compile(
    r"^(\s*)(?:(?:onready|export(?:\s*\([^)]*\))?)\s+)*(var|const)\s+([A-Za-z_]\w*)(.*)$")
FOR_RE = re.compile(r"^\s*for\s+([A-Za-z_]\w*)\s+in\s+")
MATCH_RE = re.compile(r"^(\t*)match\s+(.+?)\s*:\s*$")


# ═══════════════════════════ 词法工具 ═══════════════════════════

def split_code_comment(line: str):
    out, i, n, quote = [], 0, len(line), None
    while i < n:
        c = line[i]
        if quote:
            out.append(c)
            if c == "\\" and i + 1 < n:
                out.append(line[i + 1])
                i += 2
                continue
            if c == quote:
                quote = None
            i += 1
            continue
        if c in "\"'":
            quote = c
            out.append(c)
            i += 1
            continue
        if c == "#":
            return "".join(out), line[i:]
        out.append(c)
        i += 1
    return "".join(out), ""


def mask_strings(code: str):
    out, i, n, strs = [], 0, len(code), []
    while i < n:
        c = code[i]
        if c in "\"'":
            q, j = c, i + 1
            while j < n:
                if code[j] == "\\":
                    j += 2
                    continue
                if code[j] == q:
                    break
                j += 1
            strs.append(code[i:j + 1])
            out.append("\x00S%d\x00" % (len(strs) - 1))
            i = j + 1
            continue
        out.append(c)
        i += 1
    return "".join(out), strs


def unmask_strings(code: str, strs) -> str:
    return re.sub(r"\x00S(\d+)\x00", lambda m: strs[int(m.group(1))], code)


def split_args(s: str):
    parts, buf, depth, quote = [], [], 0, None
    i, n = 0, len(s)
    while i < n:
        c = s[i]
        if quote:
            buf.append(c)
            if c == "\\" and i + 1 < n:
                buf.append(s[i + 1])
                i += 2
                continue
            if c == quote:
                quote = None
            i += 1
            continue
        if c in "\"'":
            quote = c
            buf.append(c)
            i += 1
            continue
        if c in "([{":
            depth += 1
        elif c in ")]}":
            depth -= 1
        if c == "," and depth == 0:
            parts.append("".join(buf).strip())
            buf = []
            i += 1
            continue
        buf.append(c)
        i += 1
    tail = "".join(buf).strip()
    if tail:
        parts.append(tail)
    return parts


def find_matching(s: str, i: int, open_ch="(", close_ch=")") -> int:
    depth, quote, n = 0, None, len(s)
    while i < n:
        c = s[i]
        if quote:
            if c == "\\":
                i += 2
                continue
            if c == quote:
                quote = None
            i += 1
            continue
        if c in "\"'":
            quote = c
        elif c == open_ch:
            depth += 1
        elif c == close_ch:
            depth -= 1
            if depth == 0:
                return i
        i += 1
    return -1


def find_matching_back(s: str, i: int, close_ch: str, open_ch: str) -> int:
    depth, j = 0, i
    while j >= 0:
        c = s[j]
        if c == close_ch:
            depth += 1
        elif c == open_ch:
            depth -= 1
            if depth == 0:
                return j
        j -= 1
    return -1


def chain_start(s: str, last: int) -> int:
    """返回 s 中「以 last 结尾的后缀表达式链」的起点；失败 -1。

    可识别：标识符 / 带实参的调用 / 下标 / 括号组，以及它们的 `.` `()` `[]` 串联。

    ★ 这里曾有个**只在「链尾是下标」时才暴露**的缺陷：处理完 `[...]` 后函数直接
      `return i + 1`，没有回到循环继续往前吃标识符 —— 于是
      `currentAffectedItems[color].keys()` 的「接收者起点」被算成了 `[` 而不是
      `currentAffectedItems`，容器规则改写后得到
      `currentAffectedItemslist([color].keys())`（**元素被吞、语法还合法**）。
      同一个缺陷也会打歪 `_type_checks`：`arr[0] is Array` 会变成
      `aisinstance([0], list)` —— 前缀整段被替换掉，且不报错。
      故循环条件改为「只要左边还接着链元素（标识符、下标记号、调用记号或 `.`）就继续」。
      实测 gd_core/gd_core_items 里「接收者以 `]`/`)` 结尾的 `.方法(`」共 2 处，
      都被此缺陷命中；修后两处均正确。
    """
    i = last
    while True:
        if i < 0:
            return -1
        c = s[i]
        if c in ")]}":
            j = find_matching_back(s, i, c, {")": "(", "]": "[", "}": "{"}[c])
            if j < 0:
                return -1
            i = j - 1
        elif c.isalnum() or c == "_":
            j = i
            while j >= 0 and (s[j].isalnum() or s[j] == "_"):
                j -= 1
            i = j
        else:
            return -1
        if i < 0:
            return 0
        # 链式：紧接着 `.` → 跨过它继续；紧接着另一个链元素 → 也继续
        if s[i] == ".":
            i -= 1
            continue
        if s[i].isalnum() or s[i] == "_" or s[i] in ")]}":
            continue
        return i + 1


def receiver_start(s: str, dot: int) -> int:
    return chain_start(s, dot - 1)


def count_tabs(line: str) -> int:
    return len(line) - len(line.lstrip("\t"))


def top_level_eq(s: str) -> int:
    """返回 s 中顶层单个 `=` 的下标（排除 ==/!=/<=/>=/:=），找不到 -1。"""
    depth, quote = 0, None
    i, n = 0, len(s)
    while i < n:
        c = s[i]
        if quote:
            if c == "\\":
                i += 2
                continue
            if c == quote:
                quote = None
            i += 1
            continue
        if c in "\"'":
            quote = c
        elif c in "([{":
            depth += 1
        elif c in ")]}":
            depth -= 1
        elif c == "=" and depth == 0:
            nxt = s[i + 1] if i + 1 < n else ""
            prv = s[i - 1] if i else ""
            if nxt in "=<>" or prv in "=<>!+-*/%:":
                i += 1
                continue
            return i
        i += 1
    return -1


# ═══════════════════════════ 表达式改写 ═══════════════════════════

class Rewriter:
    """把一行（或一条语句）GDScript 改写成 Python。hit/warn 为统计出口。"""

    def __init__(self, class_names, members, methods, hit, warn, stat,
                 own_class_names=frozenset(), owner_class=None):
        self.class_names = class_names      # 全部 GDScript class_name / 文件主干名
        self.members = members              # 本类 + 继承链的成员名（含枚举/信号/嵌套类）
        self.methods = methods              # 本类 + 继承链的方法名
        self.own_class_names = own_class_names   # 本文件自己声明的类名（裸引用可用）
        self.owner_class = owner_class      # 本文件的顶层 Python 类名（static 上下文用）
        self.hit = hit
        self.warn = warn
        self.stat = stat

    # ── 主入口 ──
    def rewrite(self, line: str, locals_=None, in_func=False,
                in_static=False) -> str:
        locals_ = locals_ or set()
        code, comment = split_code_comment(line)
        if not code.strip():
            return line
        masked, strs = mask_strings(code)
        masked = self._kw_names(masked)
        masked = self._decl(masked)
        masked = self._literals(masked)
        masked = self._dot_new(masked)
        masked = self._keyword_attrs(masked)
        masked = self._str_calls(masked)
        masked = self._range_calls(masked)
        masked = self._calls(masked)
        masked = self._free_calls(masked, locals_, in_func, in_static)
        masked = self._globals(masked, in_static)
        masked = self._members(masked, locals_, in_func, in_static)
        masked = self._type_checks(masked)
        masked = self._for_iter(masked)
        masked = self._tilde(masked)
        masked = self._classrefs(masked, locals_)
        out = unmask_strings(masked, strs)
        out = self._keyword_colon_split(out)
        return out + comment

    def _str_calls(self, s: str) -> str:
        """GDScript `str(a, b, …)` → `_strv(a, b, …)`（**按实参个数分流**）。

        ★ 为什么不能简单覆盖同名：GDScript 的 `str()` 多参是**拼接**，Python 的
          `str()` 只吃一个实参。项目里 8 处调用，其中 4 处是多参
          （`str("cd", i + 1)` 拼参数键、`str(requiredStr, "\\n\\n", descr)` 拼描述）。
          若在 _rt 里直接把 `str` 覆盖成变参函数，会连带打断类型检查 ——
          `is String` 被转写成了 `isinstance(x, str)`，那时 `str` 已不是类型。
        故只改多参那几处，单参保持 Python 内建（语义本就一致）。
        """
        out, i, n = [], 0, len(s)
        while i < n:
            m = _BARE_STR_RE.search(s, i)
            if not m:
                out.append(s[i:])
                break
            op = m.end() - 1
            cp = find_matching(s, op)
            if cp < 0:
                out.append(s[i:])
                break
            args = split_args(s[op + 1:cp])
            if len(args) > 1:
                self.hit["多参 str()→_strv"] += 1
                out.append(s[i:m.start()])
                out.append("_strv(")
                out.append(s[op + 1:cp])
                out.append(")")
            else:
                out.append(s[i:cp + 1])
            i = cp + 1
        return "".join(out)

    def _range_calls(self, s: str) -> str:
        """裸 `range(` → `_gd_range(`（GDScript 的 range 返回 Array，不是惰性序列）。

        与 `_str_calls` 不同，这里**不需要**按实参分流：全部改写。
        唯一要避的是 Python 自己的 `range`，故垫片另起名而不是遮蔽内建。
        """
        out, i, n = [], 0, len(s)
        while i < n:
            m = _BARE_RANGE_RE.search(s, i)
            if not m:
                out.append(s[i:])
                break
            self.hit["裸 range()→_gd_range"] += 1
            out.append(s[i:m.start()])
            out.append("_gd_range(")
            i = m.end()
        return "".join(out)

    def _self_prefix(self, in_static):
        """隐式主体的限定前缀。

        ★ GDScript 的 `static func` 里没有 self：写 `self.x` 会在运行第一行就
          NameError。但 static func **可以**读本类枚举/常量（`Stack.Food`），
          所以不能简单跳过改写 —— 要改成类名限定。类名是本模块的全局名。
        """
        if in_static and self.owner_class:
            self.hit["static 上下文→类名限定"] += 1
            return self.owner_class + "."
        return "self."

    # ── 裸类名 → _R.C("名字") ──
    def _classrefs(self, s: str, locals_: set) -> str:
        """把跨文件引用的裸类名解析成 _R.C("名字")。

        ★ 为什么必须做：GDScript 的 class_name 是一个**全局命名空间**，跨文件写
          `CoreDamageSource.new(...)` / `CoreConst.getBuffs(...)` / `x is CoreItem`
          都靠它解析。Python 模块之间没有共享全局名 —— 裸引用只会**在跑到的瞬间**
          抛 NameError（静态检查抓不到，冷路径可能整局都不触发）。
        本文件自己声明的类名（顶层 py_class + 同文件 class）保持裸引用：它们在
        本模块内就是模块全局名，且同文件 class 根本不 reg，走 _R.C 反而找不到。

        前缀守卫 `(?<![\\w.\"'])` 保证 `CoreConst.Rarity.Food` 只改 `CoreConst`
        —— `Rarity`/`Food` 前面是 `.`，不会被误伤（`Food` 恰好也是项目里的
        `Food.gd` 主干名，少了这道守卫会把枚举成员改成类引用，静默改变判定）。
        """
        names = (set(self.class_names) - set(TYPE_MAP) - self.own_class_names
                 - set(locals_) - set(self.members) - set(self.methods))
        if not names:
            return s
        pat = re.compile(r"(?<![\w.\"'])(%s)(?![\w])" % "|".join(
            re.escape(x) for x in sorted(names, key=len, reverse=True)))

        def rep(m):
            self.hit["裸类名→_R.C"] += 1
            return '_R.C("%s")' % m.group(1)
        return pat.sub(rep, s)

    # ── Python 关键字标识符重命名（GDScript 合法 / Python 非法）──
    def _kw_names(self, s: str) -> str:
        for gd, py in PY_KEYWORD_RENAMES:
            pat = r"(?<![\w.])%s(?![\w])" % gd
            n = len(re.findall(pat, s))
            if n:
                self.hit["关键字标识符:%s→%s" % (gd, py)] += n
                s = re.sub(pat, py, s)
        return s

    # ── var / const 声明 → 普通赋值 ──
    def _decl(self, s: str) -> str:
        m = DECL_RE.match(s)
        if not m:
            return s
        head, kw, name, rest = m.group(1), m.group(2), m.group(3), m.group(4).strip()
        val = None
        if rest.startswith(":="):
            val = rest[2:].strip()
        elif rest.startswith("="):
            val = rest[1:].strip()
        elif rest.startswith(":"):
            eq = top_level_eq(rest)
            val = rest[eq + 1:].strip() if eq >= 0 else None
        elif rest == "":
            val = None
        else:
            self.stat["声明未解析"].append(s.strip()[:90])
            return s
        self.hit["var/const→赋值"] += 1
        return "%s%s = %s" % (head, name, val if val else "None")

    # ── null/true/false ──
    def _literals(self, s: str) -> str:
        for gd, py in LITERAL_MAP:
            pat = r"(?<![\w.])%s(?![\w])" % gd
            n = len(re.findall(pat, s))
            if n:
                self.hit["字面量:" + gd] += n
                s = re.sub(pat, py, s)
        return s

    # ── X.new( → X( ──
    def _dot_new(self, s: str) -> str:
        out, i = [], 0
        while True:
            m = re.search(r"\.new\s*\(", s[i:])
            if not m:
                out.append(s[i:])
                break
            out.append(s[i:i + m.start()])
            out.append("(")
            i = i + m.end()
            self.hit[".new(→("] += 1
        return "".join(out)

    # ── X.None → X["None"] ──
    def _keyword_attrs(self, s: str) -> str:
        def rep(m):
            self.hit["关键字成员:" + m.group(1)] += 1
            return '["%s"]' % m.group(1)
        return re.sub(r"\.(%s)\b" % "|".join(sorted(PY_KEYWORDS)), rep, s)

    # ── 容器方法（递归处理接收者与实参） ──
    def _calls(self, s: str) -> str:
        guard, i = 0, 0
        while True:
            guard += 1
            if guard > 4000:
                self.warn.append("call-rewrite 迭代超限: %s" % s[:90])
                return s
            m = re.compile(r"\.([A-Za-z_]\w*)\s*\(").search(s, i)
            if not m:
                return s
            name = m.group(1)
            if name not in CONTAINER_RULES and name != "new":
                i = m.end()
                continue
            rs = receiver_start(s, m.start())
            if rs < 0:
                k = m.start() - 1
                while k >= 0 and s[k] == " ":
                    k -= 1
                if k >= 0 and (s[k].isalnum() or s[k] in "_)]"):
                    self.warn.append("接收者不可解析: %s" % s[:90])
                # 否则是 GDScript 的 `.method()` 父类调用，交给 super 规则
                i = m.end()
                continue
            op = s.index("(", m.start())
            cp = find_matching(s, op)
            if cp < 0:
                i = m.end()
                continue
            recv = self._calls(s[rs:m.start()])
            args = [self._calls(a) for a in split_args(s[op + 1:cp])]
            # ★ 实参个数守卫：不符 GDScript 内建签名的，说明是同名的**项目自有方法**
            #   （例：CoreRng.shuffle(array)），必须原样保留。见 CONTAINER_ARITY 注释。
            lo, hi = CONTAINER_ARITY.get(name, (0, 99))
            if not (lo <= len(args) <= hi):
                self.hit[".%s(%d 参)→按项目方法保留" % (name, len(args))] += 1
                i = m.end()
                continue
            rep = self._render(name, recv, args)
            if rep is None:
                i = m.end()
                continue
            s = s[:rs] + rep + s[cp + 1:]
            i = rs + len(rep)

    def _render(self, name, recv, args):
        h = self.hit
        if name == "new":
            h[".new(→("] += 1
            return "%s(%s)" % (recv, ", ".join(args))
        if name == "size":
            h[".size()→len"] += 1
            return "len(%s)" % recv
        if name == "length":
            h[".length→len"] += 1
            return "len(%s)" % recv
        if name == "empty":
            h[".empty()→not"] += 1
            return "(not %s)" % recv
        if name == "has":
            h[".has→in"] += 1
            return "(%s in %s)" % (args[0], recv)
        if name == "push_back":
            h[".push_back→append"] += 1
            return "%s.append(%s)" % (recv, args[0])
        if name == "append_array":
            h[".append_array→extend"] += 1
            return "%s.extend(%s)" % (recv, args[0])
        if name == "pop_front":
            h[".pop_front→pop(0)"] += 1
            return "%s.pop(0)" % recv
        if name == "pop_back":
            h[".pop_back→pop()"] += 1
            return "%s.pop()" % recv
        if name == "duplicate":
            h[".duplicate→_dup"] += 1
            return "_dup(%s%s)" % (recv, (", " + ", ".join(args)) if args else "")
        if name == "erase":
            h[".erase→_erase"] += 1
            return "_erase(%s, %s)" % (recv, ", ".join(args))
        if name == "remove":
            h[".remove→_pop_at(按索引)"] += 1
            return "_pop_at(%s, %s)" % (recv, ", ".join(args))
        if name == "find":
            h[".find→_find"] += 1
            return "_find(%s, %s)" % (recv, ", ".join(args))
        if name == "keys":
            h[".keys()→list(副本)"] += 1
            return "list(%s.keys())" % recv
        if name == "values":
            h[".values()→list(副本)"] += 1
            return "list(%s.values())" % recv
        if name == "front":
            h[".front→[0]"] += 1
            return "%s[0]" % recv
        if name == "back":
            h[".back→[-1]"] += 1
            return "%s[-1]" % recv
        if name == "sort_custom":
            h[".sort_custom→_sort_custom"] += 1
            return "_sort_custom(%s, %s)" % (recv, ", ".join(args))
        if name == "shuffle":
            h[".shuffle→_shuffle"] += 1
            return "_shuffle(%s)" % recv
        if name == "resize":
            h[".resize→_resize"] += 1
            return "_resize(%s, %s)" % (recv, ", ".join(args))
        if name == "begins_with":
            h[".begins_with→startswith"] += 1
            return "%s.startswith(%s)" % (recv, ", ".join(args))
        if name == "get_slice":
            h[".get_slice→_get_slice"] += 1
            return "_get_slice(%s, %s)" % (recv, ", ".join(args))
        if name == "invert":
            h[".invert→_invert"] += 1
            return "_invert(%s)" % recv
        if name == "hash":
            h[".hash→_hash"] += 1
            return "_hash(%s)" % recv
        if name == "join":
            h[".join→_join"] += 1
            return "_join(%s, %s)" % (recv, ", ".join(args))
        # ── GDScript 与 Python 名字/语义都不同的内建（Python 里没有同名方法） ──
        if name == "fill":
            h[".fill→_fill"] += 1
            return "_fill(%s, %s)" % (recv, ", ".join(args))
        if name == "pick_random":
            h[".pick_random→_pick_random"] += 1
            return "_pick_random(%s)" % recv
        if name == "substr":
            h[".substr→_substr"] += 1
            return "_substr(%s%s)" % (recv, (", " + ", ".join(args)) if args else "")
        # to_lower / to_upper 语义与 Python 的 lower / upper **完全一致**，
        # 只是名字不同：直接换成同名方法，不必绕垫片。
        if name == "to_lower":
            h[".to_lower→lower"] += 1
            return "%s.lower()" % recv
        if name == "to_upper":
            h[".to_upper→upper"] += 1
            return "%s.upper()" % recv
        return None

    # ── 裸方法调用（同级/继承方法 + Object 方法）→ self. ──
    def _free_calls(self, s: str, locals_: set, in_func: bool,
                    in_static: bool = False) -> str:
        if not in_func:
            return s
        owned = (self.methods | SELF_METHODS) - locals_
        owned -= self.class_names
        owned -= self.own_class_names
        # 同 _members：本类真声明过的方法要优先于 NEVER_SELF（否则会落到内建上）
        owned -= (NEVER_SELF - self.methods)
        if not owned:
            return s
        prefix = self._self_prefix(in_static)
        tag = "裸调用→" + ("类名" if in_static else "self.")
        pat = re.compile(r"(?<![\w.])(%s)\s*\(" % "|".join(
            re.escape(x) for x in sorted(owned, key=len, reverse=True)))

        def rep(m):
            self.hit[tag] += 1
            return prefix + m.group(1) + "("
        return pat.sub(rep, s)

    # ── 全局对象 / 内建 ──
    def _globals(self, s: str, in_static: bool = False) -> str:
        h = self.hit
        conn_rep = (self.owner_class + ".connect(" if (in_static and self.owner_class)
                    else "self.connect(")
        for pat, rep_, tag in (
            (r"\bOS\.has_feature\s*\(", "OS_has_feature(", "OS.has_feature→垫片"),
            # ★ OS.get_environment(x) → _os_environ_get(x)（_rt 垫片，包
            #   os.environ.get(x, "")；2026-10-08 CoreRng._stacktrace 首个用例）。
            (r"\bOS\.get_environment\s*\(", "_os_environ_get(", "OS.get_environment→垫片"),
            (r"\bEngine\.time_scale\b", "1.0", "Engine.time_scale→1.0"),
            # ★ `load(...)` 的判定**不能依赖后面的引号**：mask_strings() 在进入
            #   改写前已把字符串字面量换成占位符，`(?=\")` 于是恒不成立 ——
            #   这条规则从写下那天起**一次都没命中过**（全库 `_load(` 调用点恒为 0，
            #   `_rt._load` 垫片一直是死代码），而 CoreUtil.isItemDescriptor 就该用上它。
            #   放宽为「名字前不是标识符/点」即可：全库无自定义 `func load(`，
            #   对象方法式 `x.load(...)` 由 (?<![\w.]) 排除。
            (r"(?<![\w.])load\s*\(", "_load(", "load→_load"),
            (r"(?<![\w.])funcref\s*\(", "FuncRef(", "funcref→FuncRef"),
            (r"(?<![\w.])randomize\s*\(", "randomize(", "randomize→垫片"),
            (r"(?<![\w.])connect\s*\(", conn_rep, "裸 connect→垫片"),
        ):
            new = re.sub(pat, rep_, s)
            if new != s:
                h[tag] += 1
                s = new
        # GDScript 的 `.method()`（点号打头）= 调用父类实现 → super().method(
        # 判据：点号左侧不是标识符/`)`/`]`（那些是普通属性访问，已由 _calls 处理）
        # ★ static 上下文里 Python 的零参 super() 会 RuntimeError（没有 __class__ 单元），
        #   必须写成 super(Cls, Cls)。
        n_super = len(re.findall(r"(?<![\w.)\]])\.[A-Za-z_]\w*\s*\(", s))
        if n_super:
            if in_static and self.owner_class:
                h[".method()→super(Cls,Cls).（static）"] += n_super
                s = re.sub(r"(?<![\w.)\]])\.([A-Za-z_]\w*)(\s*\()",
                           r"super(%s, %s).\1\2" % (self.owner_class,
                                                    self.owner_class), s)
            else:
                h[".method()→super()."] += n_super
                s = re.sub(r"(?<![\w.)\]])\.([A-Za-z_]\w*)(\s*\()",
                           r"super().\1\2", s)
        return s

    # ── 隐式 self：裸成员引用 ──
    def _members(self, s: str, locals_: set, in_func: bool,
                 in_static: bool = False) -> str:
        if not in_func:
            return s
        # ★ NEVER_SELF 是用来保护**内建自由函数**不被误加 self. 的；但当某个名字
        #   本身就是**本类声明的成员**时，它必须优先按成员解析 —— 否则裸引用会落到
        #   Python 内建上，得到「合法的错值」。
        #   实证：CoreBuff.gd 的 `var type` 是成员，`item.getAmplificationChancePercent(type)`
        #   于是把 Python 内建 `type` 传了进去，下游
        #   `buffAmplificationChances[buffType]` 抛 `KeyError: <class 'type'>`。
        #   同类还有 dict / id / sorted / sum（全项目 8 处成员声明，0 处方法声明）。
        #   GDScript 侧没有 sum()/sorted()/dict()/id() 这些内建，故让位给成员是安全的。
        names = ((self.members - locals_) - self.class_names
                 - self.own_class_names - (NEVER_SELF - self.members))
        if not names:
            return s
        prefix = self._self_prefix(in_static)
        tag = "裸成员→" + ("类名" if in_static else "self.")
        pat = re.compile(r"(?<![\w.])(%s)(?![\w(])" % "|".join(
            re.escape(x) for x in sorted(names, key=len, reverse=True)))

        def rep(m):
            self.hit[tag] += 1
            return prefix + m.group(1)
        return pat.sub(rep, s)

    # ── `expr is Type` → isinstance(...) ──
    def _type_checks(self, s: str) -> str:
        hits = list(re.finditer(r"\s+is\s+([A-Za-z_]\w*)", s))
        for m in reversed(hits):
            typ = m.group(1)
            start = chain_start(s, m.start() - 1)
            if start < 0:
                self.warn.append("is 左操作数不可解析: %s" % s[:90])
                continue
            expr = s[start:m.start()]
            py = TYPE_MAP.get(typ, typ)
            # GD_DEFAULT 是转写器自己引入的哨兵，`x is GD_DEFAULT` 用的是 Python 的
            # 身份比较（正是本意），不该走 isinstance 也不该报「未知类型」。
            if typ == "GD_DEFAULT":
                continue
            if py not in ("bool", "int", "float", "str", "list", "dict",
                          "Vector2", "GodotObject", "FuncRef", "Color") \
                    and py not in self.class_names:
                self.warn.append("is 未知类型 %s: %s" % (typ, s[:90]))
                continue
            s = s[:start] + "isinstance(%s, %s)" % (expr.strip(), py) + s[m.end():]
            self.hit["is→isinstance"] += 1
        return s

    # ── for X in EXPR: → _iter ──
    def _for_iter(self, s: str) -> str:
        m = re.match(r"^(\s*)for\s+([A-Za-z_]\w*)\s+in\s+(.+?)\s*:\s*(.*)$", s, re.S)
        if not m:
            return s
        self.hit["for→_iter"] += 1
        body = m.group(4)
        return "%sfor %s in _iter(%s):%s" % (m.group(1), m.group(2), m.group(3),
                                             (" " + body) if body.strip() else "")

    # ── `not in` / `in` 无需改；`&&`/`||`/`!` 项目里没有，保底 ──
    def _tilde(self, s: str) -> str:
        if "&&" in s or "||" in s:
            self.hit["布尔算符"] += 1
            s = s.replace("&&", " and ").replace("||", " or ")
        return s

    # ── GDScript 单行块 `if x: stmt` → 两行 ──
    def _keyword_colon_split(self, s: str) -> str:
        """★ 只产出**相对**缩进（body 用单个 tab），绝对缩进由 Emitter._stmt 统加。

        若这里写成 `head + kw + ... + head + "\\t" + body`（自带绝对缩进），
        _stmt 再前缀一次就会翻倍 —— 而 Python 对多余缩进的处理是
        语法错误（顶层语句）或改变归属（类体内），两种都很难回查。
        """
        m = re.match(r"^(\s*)(if|elif|else|while|for|func|static func|match)\b(.*)$",
                     s, re.S)
        if not m:
            return s
        _head, kw, rest = m.group(1), m.group(2), m.group(3)
        if "\n" in s:
            return s
        depth, quote, idx, i = 0, None, -1, 0
        while i < len(rest):
            c = rest[i]
            if quote:
                if c == "\\":
                    i += 2
                    continue
                if c == quote:
                    quote = None
            elif c in "\"'":
                quote = c
            elif c in "([{":
                depth += 1
            elif c in ")]}":
                depth -= 1
            elif c == ":" and depth == 0 and not (
                    i + 1 < len(rest) and rest[i + 1] == "="):
                idx = i
                break
            i += 1
        if idx < 0:
            return s
        body = rest[idx + 1:].strip()
        if not body:
            return s
        self.hit["单行块→两行"] += 1
        return "%s%s:\n\t%s" % (kw, rest[:idx], body)


# ═══════════════════════════ / 与 % 语义重写 ═══════════════════════════

def _is_str_expr(n) -> bool:
    """判断表达式是否**一定是字符串**（用于区分 `%` 是格式化还是取模）。

    ★ 这个区分是必须的：GDScript 的 `%` 有两个完全不同的含义 —— 整数取模 与
      字符串格式化。ast 里两者都是 `BinOp(op=Mod)`，只能靠左操作数的**类型**分。
      漏判的后果实测过：`"_stacks_changed_%d" % stackType` 被改写成
      `_mod("_stacks_changed_%d", stackType)`，运行到那一行抛
      `TypeError: must be real number, not str`（CoreCharacter.gd:209）。
    """
    if isinstance(n, ast.Constant):
        return isinstance(n.value, str)
    if hasattr(ast, "JoinedStr") and isinstance(n, ast.JoinedStr):
        return True
    if isinstance(n, ast.BinOp) and isinstance(n.op, ast.Add):
        return _is_str_expr(n.left) or _is_str_expr(n.right)
    return False


class DivModRewriter(ast.NodeTransformer):
    def visit_BinOp(self, node):
        self.generic_visit(node)
        if isinstance(node.op, ast.Div):
            return ast.Call(func=ast.Name(id="_div", ctx=ast.Load()),
                            args=[node.left, node.right], keywords=[])
        if isinstance(node.op, ast.Mod):
            # 字符串 `%` 是格式化：GDScript 右侧为 Array 时逐元素填参，
            # Python 的 `%` 会把它当**单个值**，故走 _gd_fmt 而不是 _mod。
            fn = "_gd_fmt" if _is_str_expr(node.left) else "_mod"
            return ast.Call(func=ast.Name(id=fn, ctx=ast.Load()),
                            args=[node.left, node.right], keywords=[])
        return node


DIVMOD_GUARD = re.compile(r"(?<![/*=<>!+\-])[/%](?![=/*])")
# 「简单原子」：能安全参与 `/` `%` 改写的操作数形态。
# ★ 必须包含**点号链**（`self.tickCounter`）：`self.` 前缀是先于本步加的，若原子
#   只吃 `tickCounter`，兜底改写会在 `self.` 之后插入 `_mod(...)`，得到
#   `self._mod(tickCounter, 2)` —— 语法合法、运行时 AttributeError。
SIMPLE_ATOM = (r"(?:[A-Za-z_]\w*(?:\([^()]*\))?(?:\[[^\[\]]*\])?"
               r"(?:\.[A-Za-z_]\w*(?:\([^()]*\))?(?:\[[^\[\]]*\])?)*"
               r"|_div\([^()]*\)|_mod\([^()]*\)|\d+\.\d+|\d*\.\d+|\d+"
               r"|\([^()]*\)|\[[^\[\]]*\])")


def rewrite_divmod(line: str, stat) -> str:
    code, comment = split_code_comment(line)
    if not DIVMOD_GUARD.search(code):
        return line
    indent = code[:len(code) - len(code.lstrip())]
    body = code.strip()
    if not body:
        return line
    # ★ 块首行（`if cond:` / `while cond:` / `for …:`）本身不是完整语句，
    #   ast.parse 必然 SyntaxError，于是整类行都掉进正则兜底。
    #   补一个 `pass` 体让它们走**精确的 ast 改写**，再把 `pass` 摘掉。
    #   （实测：`if tickCounter % 2 == 0:` 掉兜底后产出了 `self._mod(...)`）
    only_header = body.endswith(":") and not body.endswith("::")
    try:
        tree = ast.parse(body + " pass" if only_header else body, mode="exec")
    except SyntaxError:
        stat["divmod_兜底"].append(body[:90])
        return simple_divmod(code) + comment
    new = DivModRewriter().visit(tree)
    ast.fix_missing_locations(new)
    try:
        text = ast.unparse(new)
    except Exception:  # noqa: BLE001
        stat["divmod_兜底"].append(body[:90])
        return simple_divmod(code) + comment
    if only_header:
        rows = text.split("\n")
        if not rows or rows[-1].strip() != "pass":
            stat["divmod_兜底"].append(body[:90])
            return simple_divmod(code) + comment
        text = "\n".join(rows[:-1])
    stat["divmod_ast"] += 1
    if only_header:
        stat["divmod_ast_块首行"] += 1
    return "\n".join(indent + ln for ln in text.split("\n")) + comment


def simple_divmod(code: str) -> str:
    pat = re.compile(r"(" + SIMPLE_ATOM + r")\s*([/%])\s*(" + SIMPLE_ATOM + r")")
    guard = 0
    while True:
        guard += 1
        if guard > 800:
            return code
        m = pat.search(code)
        if not m:
            return code
        fn = "_div" if m.group(2) == "/" else "_mod"
        code = code[:m.start()] + "%s(%s, %s)" % (fn, m.group(1), m.group(3)) \
            + code[m.end():]


# ═══════════════════════════ 文件扫描 ═══════════════════════════

class FileCtx:
    def __init__(self, rel, text):
        self.rel = rel
        self.res_path = "res://" + rel
        self.text = text
        self.lines = text.split("\n")
        self.class_name = None
        self.extends = None
        self.py_class = None
        self.own_members = set()
        self.own_methods = set()
        self.ancestors = []


def py_class_name(rel: str, class_name: str, taken: set) -> str:
    if class_name and class_name not in taken:
        return class_name
    base = os.path.splitext(rel)[0].replace("/", "__")
    cand = base.split("__", 1)[1] if "__" in base else base
    cand = re.sub(r"[^0-9A-Za-z_]", "_", cand)
    if not cand or cand[0].isdigit():
        cand = "_" + cand
    if class_name and cand != class_name:
        cand = cand + "__" + class_name
    n, k = cand, 2
    while n in taken:
        n = "%s_%d" % (cand, k)
        k += 1
    return n


def scan_files():
    files, taken = [], set()
    for d in SRC_DIRS:
        for root, _dirs, names in os.walk(os.path.join(ROOT, d)):
            for fn in sorted(names):
                if not fn.endswith(".gd"):
                    continue
                p = os.path.join(root, fn)
                rel = os.path.relpath(p, ROOT).replace(os.sep, "/")
                with io.open(p, encoding="utf-8", errors="replace") as fh:
                    ctx = FileCtx(rel, fh.read())
                for ln in ctx.lines:
                    m = CLASSNAME_RE.match(ln)
                    if m:
                        ctx.class_name = m.group(1)
                        break
                ctx.py_class = py_class_name(rel, ctx.class_name, taken)
                taken.add(ctx.py_class)
                for ln in ctx.lines:
                    m = EXTENDS_RE.match(ln)
                    if m:
                        ctx.extends = m.group(1)
                        break
                files.append(ctx)

    by_name, by_path, by_stem = {}, {}, {}
    for f in files:
        by_path[f.res_path] = f
        if f.class_name:
            by_name[f.class_name] = f
        stem = os.path.splitext(os.path.basename(f.rel))[0]
        by_stem.setdefault(stem, []).append(f)
    return files, by_name, by_path, by_stem


def resolve_ref(ref, by_name, by_path):
    if not ref:
        return None
    if ref.startswith('"'):
        return by_path.get(ref.strip('"'))
    if ref in TYPE_MAP:
        return None
    return by_name.get(ref)


def topo_order(files, by_name, by_path, stat):
    deps = {}
    for f in files:
        base = resolve_ref(f.extends, by_name, by_path)
        deps[f.rel] = base.rel if base is not None else None
    order, state = [], {}

    def visit(rel, stack):
        st = state.get(rel)
        if st == 2:
            return
        if st == 1:
            stat["循环依赖"].append(" → ".join(stack + [rel]))
            return
        state[rel] = 1
        dep = deps.get(rel)
        if dep:
            visit(dep, stack + [rel])
        state[rel] = 2
        order.append(rel)

    for f in files:
        visit(f.rel, [])
    return order


def collect_class_scope(lines, i0, i1, base_indent, stat):
    """只在 base_indent 层收集成员/方法/枚举/信号/嵌套类（不下钻函数体）。

    返回 (members, methods, enums, signals, nested, fields)；
    fields 为类体层 `var` 的 (名字, 原始声明串) 列表 —— 交给 _init_fields 发射。
    """
    members, methods = set(), set()
    enums, signals, nested = [], [], set()
    fields = []
    i = i0
    while i < i1:
        code, _ = split_code_comment(lines[i])
        if not code.strip():
            i += 1
            continue
        if count_tabs(code) != base_indent:
            i += 1
            continue
        m = ENUM_RE.match(code)
        if m:
            body, i = gather_enum(lines, i)
            enums.append((base_indent, m.group(1), body))
            if m.group(1):
                members.add(m.group(1))
            continue
        m = SIGNAL_DECL_RE.match(code)
        if m:
            signals.append(m.group(1))
            members.add(m.group(1))
            i += 1
            continue
        m = DECL_RE.match(code)
        if m:
            members.add(m.group(3))
            if m.group(2) == "var":
                # ★ 类体层 `var` 绝不能留作 Python 类属性：`var xs = []` 在 Python 里
                #   是「全实例共享同一个 list」，原版是「每次实例化重新求值」。
                #   故收集起来改由 _init_fields() 逐实例赋值（见 transform_file）。
                stmt, i = gather_statement(lines, i, i1)
                fields.append((m.group(3),
                               " ".join(x.strip() for x in stmt).strip()))
                continue
            i += 1
            continue
        m = FUNC_RE.match(code)
        if m:
            methods.add(m.group(2))
            _sig, i = gather_signature(lines, i)
            continue
        m = NESTED_CLASS_RE.match(code)
        if m:
            members.add(m.group(1))
            nested.add(m.group(1))
            i = find_block_end(lines, i, base_indent)
            continue
        i += 1
    return members, methods, enums, signals, nested, fields


def find_block_end(lines, i, base_indent):
    """返回 i 处块（缩进 > base_indent）的结束下标。

    ★ 判块结束必须**跳过括号未闭合的续行**。多行字面量的续行可以顶格写：
      生成器把原版 `onready var X = {` 的续行原样搬进 `_readyInit()`，闭合的 `}`
      就落在第 0 列。只按缩进判，会在 `}` 那一行误判「块已结束」，把它**后面**的
      语句整条丢掉 —— 丢得毫无声响。
      实测：WandofDissonance 的 `damageSource = CoreDamageSource.new().setItem(self)`
      就这么从 Python 产物里消失，导致 `dealEffectDamage` 拿到 null 的 damageSource
      抛 `AttributeError: 'NoneType' object has no attribute 'updateEffect'`。
      ★ 为什么 GDScript 侧没这个问题：GDScript 解析器不看续行缩进，`}` 顶格也能
        正确闭合；只有「按缩进切块」的转写器会误判 → 两侧产物不一致。
    """
    j = i + 1
    depth = 0
    while j < len(lines):
        code, _ = split_code_comment(lines[j])
        # 进入本行**之前**仍在括号内 → 本行是续行，缩进不参与判断
        if depth <= 0 and code.strip() and count_tabs(code) <= base_indent:
            break
        depth += (code.count("(") - code.count(")")
                  + code.count("[") - code.count("]")
                  + code.count("{") - code.count("}"))
        j += 1
    return j


def gather_enum(lines, i):
    raw = lines[i]
    depth = raw.count("{") - raw.count("}")
    body = [raw.split("{", 1)[1] if "{" in raw else ""]
    j = i + 1
    while depth > 0 and j < len(lines):
        ln = lines[j]
        depth += ln.count("{") - ln.count("}")
        body.append(ln.rsplit("}", 1)[0] if depth <= 0 else ln)
        j += 1
    if body and body[0].strip() == "" and len(body) == 1:
        body = []
    return "\n".join(body), j


def gather_signature(lines, i):
    raw = lines[i]
    depth = raw.count("(") - raw.count(")")
    sig = [raw.strip()]
    j = i + 1
    while (depth > 0 or not sig[-1].rstrip().endswith(":")) and j < len(lines):
        ln = lines[j].strip()
        depth += ln.count("(") - ln.count(")")
        sig.append(ln)
        j += 1
    return " ".join(sig), j


def gather_statement(lines, i, i1):
    code, _ = split_code_comment(lines[i])
    depth = (code.count("(") - code.count(")") + code.count("[") - code.count("]")
             + code.count("{") - code.count("}"))
    stmt = [lines[i]]
    j = i + 1
    while depth > 0 and j < i1:
        c2, _ = split_code_comment(lines[j])
        depth += (c2.count("(") - c2.count(")") + c2.count("[") - c2.count("]")
                  + c2.count("{") - c2.count("}"))
        stmt.append(lines[j])
        j += 1
    return stmt, j


def render_enum(name, body, stat):
    """把 enum 成员渲染成 EnumDict({...})。

    ★ 分隔符必须同时认**逗号与换行**：原版 Item.gd:82-86 的 CraftingPriority 就是
      `Mixed = 2` 与 `NonGem = 1` 用换行分隔（没有逗号）—— 只按逗号切会把两条并成
      一条，值读成非数字后被静默丢弃（枚举少成员 → 取值为 None → 判定全错）。
    """
    members, nxt = [], 0
    for raw in re.split(r"[,\n]", body):
        item = raw.strip()
        if not item:
            continue
        code_item, _ = split_code_comment(item)
        item = code_item.strip()
        if not item:
            continue
        if "=" in item:
            k, v = item.split("=", 1)
            k, v = k.strip(), v.strip()
            try:
                val = int(eval(v, {"__builtins__": {}}, {}))
            except Exception:  # noqa: BLE001
                stat["枚举值未求值"].append("%s.%s = %s" % (name, k, v))
                continue
            nxt = val + 1
        else:
            k, val = item, nxt
            nxt += 1
        if not re.match(r"^[A-Za-z_]\w*$", k):
            stat["枚举行异常"].append("%s.%s" % (name, k))
            continue
        members.append('"%s": %d' % (k, val))
    return 'EnumDict("%s", {%s})' % (name, ", ".join(members))


def _py_literals(s: str) -> str:
    """null/true/false → None/True/False（只认独立词，不碰 .null 之类属性）。"""
    for gd, py in LITERAL_MAP:
        s = re.sub(r"(?<![\w.])%s(?![\w])" % gd, py, s)
    return s


def _is_plain_literal(s: str) -> bool:
    """能否作为 Python 默认值**原地**求值（字面量、负数、容器字面量）。"""
    try:
        ast.literal_eval(s)
        return True
    except Exception:  # noqa: BLE001
        return False


def render_func(sig, hit, stat):
    """`func name(args) -> T:` → (签名文本, 延迟求值默认值列表)。

    ★ 非静态成员函数必须补 `self`：GDScript 的 self 是隐式的（函数体内裸写成员名
      即 self.member），Python 必须显式声明，漏了会让所有成员访问变成
      未定义局部名 —— 而且只在那一行执行时才炸。
    ★ 已是 `static func` 的**不能**加 self：会与调用点 `Cls.fn(...)` 的实参个数错位。
      本项目 38 处 static func 集中在 CoreUtil/CoreConst 等工具类。
    ★ 返回值第二项是需要在函数体首行还原的默认值（见 _rt.GD_DEFAULT）。
    """
    m = FUNC_RE.match(sig)
    is_static, name = bool(m.group(1)), m.group(2)
    op = sig.index("(", sig.index("func"))
    cp = find_matching(sig, op)
    if cp < 0:
        stat["签名括号不配对"].append(sig[:100])
        cp = len(sig) - 1
    args, deferred, coerces = [], [], []
    for a in split_args(sig[op + 1:cp]):
        txt, d, co = render_arg(a, hit, stat)
        if txt:
            args.append(txt)
        if d:
            deferred.append(d)
        if co:
            coerces.append(co)
    if is_static:
        hit["static func→@staticmethod"] += 1
        return "@staticmethod\ndef %s(%s):" % (name, ", ".join(args)), deferred, coerces
    allargs = ["self"] + args
    return "def %s(%s):" % (name, ", ".join(allargs)), deferred, coerces


def top_level_infer_eq(s: str) -> int:
    """返回 s 中顶层 `:=` 的下标（GDScript 推断类型默认值声明），找不到 -1。

    top_level_eq 有意排除 `:=`（语句侧 `var x := 1` 由 DECL_RE 处理，不能当
    赋值改写）；但参数面 `resync := true` 是默认值声明（CoreBuff.gd:425
    `_startTimer(duration: float, resync := true)`），不还原会生成无默认值形参
    `def _startTimer(self, duration, resync)`，单参调用点直接 TypeError
    （run634 py 腿缺产物：CoreBuff._startTimer() missing 'resync'）。
    """
    depth, quote = 0, None
    i, n = 0, len(s)
    while i < n:
        c = s[i]
        if quote:
            if c == "\\":
                i += 2
                continue
            if c == quote:
                quote = None
            i += 1
            continue
        if c in "\"'":
            quote = c
        elif c in "([{":
            depth += 1
        elif c in ")]}":
            depth -= 1
        elif c == ":" and depth == 0 and i + 1 < n and s[i + 1] == "=":
            return i
        i += 1
    return -1


def render_arg(a, hit, stat):
    """返回 (参数声明文本, 延迟求值项或 None)。

    延迟求值项 = (参数名, 原始默认值表达式)，由发射方在函数体首行还原成
    `if <名> is GD_DEFAULT: <名> = <表达式>`；表达式在那里才走 Rewriter，
    因此可以正确解析 self 成员引用。
    ★ `:=` 推断默认值（如 `resync := true`）由 top_level_infer_eq 还原为
      Python `resync=True`（top_level_eq 有意排除 `:=`，见其 docstring）。
    """
    a = a.strip()
    if not a:
        return "", None, None
    eq = top_level_eq(a)
    if eq >= 0:
        lhs, rhs = a[:eq], a[eq + 1:]
    else:
        eq2 = top_level_infer_eq(a)
        if eq2 >= 0:
            hit["`:=` 推断默认值还原"] += 1
            lhs, rhs = a[:eq2], a[eq2 + 2:]
        else:
            lhs, rhs = a, None
    nm = lhs.split(":", 1)[0].strip()
    # ★ np51：GDScript 对**显式类型化 int 形参**的实参做隐式截断（float→int 朝零
    #   取整；实证：Dark Lantern onCombatStart loseHealth 107.5→事件 amount -107，
    #   扩样 60 场 py 腿保 -107.5 全红）。Python 无类型约束，必须登记为函数体首行
    #   `name = int(name)`（发射位在 GD_DEFAULT 默认值还原**之后**，语义=先取
    #   实参/默认、后按形参类型截断）。仅精确 `: int` 生效；`: float` 的直减语义
    #   已由 divmod/_div 改写面保证；`:=` 推断形参无显式注解，不在此列。
    coerce = None
    parts = lhs.split(":", 1)
    if len(parts) == 2 and parts[1].strip() == "int":
        coerce = nm
    for gd, py in PY_KEYWORD_RENAMES:
        if nm == gd:
            hit["关键字标识符:参数 %s→%s" % (gd, py)] += 1
            nm = py
            if coerce == gd:
                coerce = nm
    if rhs is None:
        return nm, None, coerce
    rhs = rhs.strip()
    lit = _py_literals(rhs)
    if _is_plain_literal(lit):
        return "%s=%s" % (nm, lit), None, coerce
    hit["默认值延迟求值→GD_DEFAULT"] += 1
    return "%s=GD_DEFAULT" % nm, (nm, rhs), coerce


def func_locals(body_lines, params) -> set:
    names = set(params)
    for raw in body_lines:
        code, _ = split_code_comment(raw)
        m = DECL_RE.match(code)
        if m:
            names.add(m.group(3))
            continue
        m = FOR_RE.match(code)
        if m:
            names.add(m.group(1))
    return names


# ═══════════════════════════ 类体发射 ═══════════════════════════

class Emitter:
    def __init__(self, f, by_name, by_path, stat, hit, class_names,
                 own_class_names=frozenset()):
        self.f = f
        self.by_name = by_name
        self.by_path = by_path
        self.stat = stat
        self.hit = hit
        self.class_names = class_names
        self.own_class_names = own_class_names
        # 同文件 `class X:`（Inner Class）被提到模块级后**不能就地发射**，见 class_body
        # 的 NESTED_CLASS_RE 分支。这里按遇到顺序收集，最后由 transform_file 统一
        # 插到外层类**之前**。
        self.hoisted = []
        self.hoisted_names = []

    # ── 类体层 var → 逐实例初始化 ──
    def field_inits(self, fields, gd_indent, py_off, members, methods, out):
        """发射 `_init_fields()`。

        ★ 为什么必须这样：Python 的类属性是**全实例共享**的，而 GDScript 的类体
          `var xs = []` 是**每次实例化重新求值**。若照搬成类属性，502 件物品脚本的
          所有实例会共用同一个 stacks/buffs/affected 容器 —— 且**一行错都不报**。
        父类字段先于子类（`super()._init_fields()` 打头），与 GDScript 求值顺序一致。
        GDScript 的 `_init()` 在字段之后执行，由 GodotObject.__init__ 串起来。
        """
        if not fields:
            return
        rw = Rewriter(self.class_names, members, methods, self.hit,
                      self.stat["未识别"], self.stat, self.own_class_names,
                      self.f.py_class)
        ind = "\t" * (gd_indent + py_off)
        out.append(ind + "def _init_fields(self):")
        out.append(ind + "\tsuper()._init_fields()")
        # ★ 显式 `: int` 字段 → py 侧 int 强制属性（round16）：
        #   GDScript 对 int 型字段赋 float 静默截断；py 无类型会把字段
        #   污染成 float，下游 `/` 整除语义漂移（实证
        #   CoreDamageResult.damage：gd int 6/4=1 vs py float 6.0/4=1.5→round→2，
        #   run575_r18 SS 毒叠漂移）。发射存储字段 self._<name> +
        #   <name> property（setter int() 截断）。
        typed_int = []
        for name, decl in fields:
            m2 = DECL_RE.match(decl)
            rest2 = (m2.group(4).strip() if m2 else "")
            if rest2.startswith(":") and rest2[1:].split("=")[0].split("#")[0].strip() == "int":
                typed_int.append(name)
        for name, decl in fields:
            m = DECL_RE.match(decl)
            rest = (m.group(4).strip() if m else "")
            val = "None"
            if rest.startswith(":="):
                val = rest[2:].strip() or "None"
            elif rest.startswith("="):
                val = rest[1:].strip() or "None"
            elif rest.startswith(":"):
                eq = top_level_eq(rest)
                if eq >= 0:
                    val = rest[eq + 1:].strip() or "None"
                else:
                    # ★ 带类型但**无初值**：GDScript 给的是该类型的零值，不是 Null。
                    #   实测（gd_core_test/DefaultProbe.gd，本机 Godot 3.6，逐条打印 typeof）：
                    #     Array→[]  Dictionary→{}  int→0  float→0.0  String→""  bool→false
                    #     Vector2→(0,0)  Color→(0,0,0,1)  PoolStringArray→[]
                    #     而 Object 类（Reference/Node/RandomNumberGenerator/FuncRef）
                    #     与无类型变量 → Null
                    #   一律写 None 的后果：`var types: Array` 变成 None，紧接着
                    #   `self.types.append(...)`（CoreDamageSource.setItem）立刻
                    #   AttributeError —— 这是转写产物第一次真跑就撞上的坑。
                    tname = rest[1:].split("#")[0].strip()
                    val = GD_TYPE_DEFAULTS.get(tname, "None")
                    if tname in GD_TYPE_DEFAULTS:
                        self.hit["带类型无初值→类型零值"] += 1
                    elif tname:
                        self.stat["未知类型零值"].append("%s: %s" % (name, tname))
            store = ("_" + name) if name in typed_int else name
            out.extend(self._stmt("self.%s = %s" % (store, val),
                                  gd_indent + py_off + 1, rw, {name}, True))
        out.append("")
        for name in typed_int:
            out.append(ind + "@property")
            out.append(ind + "def %s(self):" % name)
            out.append(ind + "\treturn self._%s" % name)
            out.append(ind + "@%s.setter" % name)
            out.append(ind + "def %s(self, v):" % name)
            out.append(ind + "\tself._%s = int(v)" % name)

    def class_body(self, lines, i0, i1, gd_indent, py_off, members, methods, out):
        """发射一个类体。

        ★ 缩进映射（本项目最容易写错、错了还很难回查的一处）：
            Python 缩进 = GDScript 缩进 + py_off
          而 py_off = 1 - (该类**类体层**的 GDScript 缩进)，原因是两者的结构不同：
            · GDScript 顶层类：类体层缩进 0，方法定义在 0、方法体在 1。
            · Python  顶层类：类体层缩进 1，方法定义在 1、方法体在 2。
            · GDScript 同文件 `class X:`（Inner Class）写在缩进 0，但它的**类体层
              是缩进 1**；本项目把它提到 Python 模块级，于是类体层缩进 1。
          取 py_off = 1 - 类体层缩进 后：顶层类 py_off=1（0→1，1→2），
          Inner Class py_off=0（1→1，2→2），两条都对。
          早期实现直接把 gd_indent 当 Python 缩进，结果所有方法定义落到模块级，
          产物是「能 import 但类名全是空的」——比语法错误更隐蔽。
        """
        rw = Rewriter(self.class_names, members, methods, self.hit,
                      self.stat["未识别"], self.stat, self.own_class_names,
                      self.f.py_class)
        i = i0
        while i < i1:
            raw = lines[i]
            code, comment = split_code_comment(raw)
            if not code.strip():
                out.append(("\t" * (count_tabs(raw) + py_off) + raw.strip())
                           if raw.strip() else "")
                i += 1
                continue
            if count_tabs(code) != gd_indent:
                i += 1
                continue
            if EXTENDS_RE.match(code) or CLASSNAME_RE.match(code):
                i += 1
                continue
            m = ENUM_RE.match(code)
            if m:
                _b, i = gather_enum(lines, i)
                continue
            if SIGNAL_DECL_RE.match(code):
                i += 1
                continue
            # 类体层 var 已由 field_inits 收走 → 这里必须跳过，否则同名字段
            # 既出现在类属性又出现在 _init_fields（类属性那份是共享的）
            m = DECL_RE.match(code)
            if m:
                stmt, i = gather_statement(lines, i, i1)
                if m.group(2) == "const":
                    for sl in stmt:
                        out.extend(self._stmt(sl, count_tabs(sl) + py_off, rw,
                                              set(), False))
                continue
            m = NESTED_CLASS_RE.match(code)
            if m:
                # ★ 同文件 Inner Class（GDScript `class X extends Y:` 写在类体层）。
                #   Python 没有「块结束」标记：一旦把 `class X:` 提到缩进 0，后续所有
                #   缩进 1 的行都会被它吞进去 —— 而外层类的成员恰好也在缩进 1。
                #   就地发射的后果实测过：`CoreUtil` 里 `DictSorter` 之后的方法
                #   （invertDictionary / filterDuplicates / …）全部变成 DictSorter 的
                #   方法，`CoreUtil.invertDictionary` 直接消失，报
                #   `type object 'CoreUtil' has no attribute ...`。
                #   ★ 而且是**静默偏移**：产物语法完全合法，ast.parse 与 import 都不报，
                #   只有真的调用到那些方法才炸。
                #   故内嵌类改为「渲染到独立缓冲 → 外层类之前统一发射」。
                nm, ext = m.group(1), m.group(2)
                end = find_block_end(lines, i, gd_indent)
                (sub_members, sub_methods, sub_enums, sub_signals,
                 _sub_nested, sub_fields) = collect_class_scope(
                     lines, i + 1, end, gd_indent + 1, self.stat)
                base = TYPE_MAP.get(ext or "Reference", "GodotObject")
                sub = []
                # Inner Class 提到 Python 模块级 → class 语句缩进 0
                sub.append("class %s(%s):" % (nm, base))
                # 它的类体层在 GDScript 是 gd_indent+1、在 Python 是 1 → py_off 归零
                sub_off = 1 - (gd_indent + 1)
                sub_py = (gd_indent + 1) + sub_off
                if not sub_members and not sub_methods and not sub_fields:
                    sub.append("\t" * sub_py + "pass")
                for _ind, ename, ebody in sub_enums:
                    sub.append("\t" * sub_py + "%s = %s"
                               % (ename, render_enum(ename, ebody, self.stat)))
                for sname in sub_signals:
                    sub.append('\t' * sub_py
                               + '%s = Signal("%s")' % (sname, sname))
                self.field_inits(sub_fields, gd_indent + 1, sub_off,
                                 sub_members, sub_methods, sub)
                self.class_body(lines, i + 1, end, gd_indent + 1, sub_off,
                                sub_members, sub_methods, sub)
                sub.append("")
                # ★ 递归可能已经往里塞了更深一层的内嵌类，它们在 sub 之前发射
                #   （更深者先定义，与外层类体若引用内层时的求值顺序一致）。
                self.hoisted.extend(sub)
                self.hoisted_names.append(nm)
                i = end
                continue
            m = FUNC_RE.match(code)
            if m:
                is_static = bool(m.group(1))
                sig, body_start = gather_signature(lines, i)
                body_end = find_block_end(lines, i, gd_indent)
                params = self._param_names(sig)
                locs = func_locals(lines[body_start:body_end], params)
                # ★ render_func 可能返回多行（static func 会多出 @staticmethod 行），
                #   必须逐行加缩进 —— 只用一次 append 会让 `def` 掉回模块级。
                func_text, deferred, coerces = render_func(sig, self.hit, self.stat)
                for sig_line in func_text.split("\n"):
                    out.append("\t" * (gd_indent + py_off) + sig_line)
                # 非字面量默认值在函数体首行还原（GDScript 每次调用求值）
                for dname, dexpr in deferred:
                    out.extend(self._stmt(
                        "if %s is GD_DEFAULT: %s = %s" % (dname, dname, dexpr),
                        gd_indent + py_off + 1, rw, locs, True, is_static))
                # ★ np51 类型化 int 形参截断（在默认值还原之后、函数体之前）
                for cname in coerces:
                    out.append("\t" * (gd_indent + py_off + 1)
                               + "%s = int(%s)" % (cname, cname))
                    self.hit["带类型 int 参数→int() 截断"] += 1
                self._body_lines(lines, body_start, body_end, py_off, rw,
                                 locs, out, is_static)
                i = body_end
                continue
            stmt, i = gather_statement(lines, i, i1)
            for sl in stmt:
                out.extend(self._stmt(sl, count_tabs(sl) + py_off, rw,
                                      set(), False))
        return out

    def _param_names(self, sig):
        op = sig.index("(", sig.index("func"))
        cp = find_matching(sig, op)
        names = []
        for a in split_args(sig[op + 1:cp] if cp > 0 else ""):
            eq = top_level_eq(a)
            lhs = (a[:eq] if eq >= 0 else a).strip()
            nm = lhs.split(":", 1)[0].strip()
            if re.match(r"^[A-Za-z_]\w*$", nm):
                names.append(nm)
        return names

    def _body_lines(self, lines, i0, i1, py_off, rw, locals_, out,
                    in_static=False):
        i = i0
        while i < i1:
            raw = lines[i]
            code, _ = split_code_comment(raw)
            if not code.strip():
                out.append(("\t" * (count_tabs(raw) + py_off) + raw.strip())
                           if raw.strip() else "")
                i += 1
                continue
            if MATCH_RE.match(code):
                i = self._emit_match(lines, i, i1, py_off, rw, locals_, out,
                                     in_static)
                continue
            stmt, i = gather_statement(lines, i, i1)
            for sl in stmt:
                out.extend(self._stmt(sl, count_tabs(sl) + py_off, rw,
                                      locals_, True, in_static))

    def _emit_match(self, lines, i, i1, py_off, rw, locals_, out, in_static):
        """GDScript `match` → Python if/elif 链。

        GDScript 的 match 是**值比较**（语义等价 `==`），且无默认分支、无命中时
        静默跳过 —— 与不带 else 的 if/elif 链完全一致，故可直译。
        项目实测 20 处 match / 98 个 case，全部是「常量表达式:」形态。

        返回 match 块结束后的行下标（调用方的 i 要跳过去，否则 case 会被当成
        普通语句再发一次）。
        """
        code, _ = split_code_comment(lines[i])
        m = MATCH_RE.match(code)
        gd_ind = len(m.group(1))
        subj = m.group(2).strip()
        py_ind = gd_ind + py_off

        end = i + 1
        while end < i1:
            c, _ = split_code_comment(lines[end])
            if c.strip() and count_tabs(c) <= gd_ind:
                break
            end += 1

        # 切出 case：case 行在 gd_ind+1 层，体在更深层，直到下一个 case 或块尾
        cases = []
        k = i + 1
        while k < end:
            c, _ = split_code_comment(lines[k])
            if not c.strip() or count_tabs(c) != gd_ind + 1:
                k += 1
                continue
            b = k + 1
            while b < end:
                c2, _ = split_code_comment(lines[b])
                if c2.strip() and count_tabs(c2) <= gd_ind + 1:
                    break
                b += 1
            cases.append((c.strip(), k, b))
            k = b

        if not cases:
            out.append("\t" * py_ind + "pass")
            return end

        self.hit["match→if/elif"] += 1
        first, default = True, None
        for label, ks, be in cases:
            lbl = label.rstrip()
            if not lbl.endswith(":"):
                self.stat["match case 非块形态"].append(label[:80])
                continue
            lbl = lbl[:-1].strip()
            if lbl == "_":
                default = (ks, be)
                self.hit["match 默认分支→else"] += 1
                continue
            kw = "if" if first else "elif"
            first = False
            conds = ["%s == %s" % (subj, part.strip())
                     for part in split_args(lbl) if part.strip()]
            head = "%s %s:" % (kw, " or ".join(conds) if conds else "False")
            out.extend(self._stmt(head, py_ind, rw, locals_, True, in_static))
            self._body_lines(lines, ks + 1, be, py_off, rw, locals_, out,
                             in_static)
        if default is not None:
            out.append("\t" * py_ind + "else:")
            self._body_lines(lines, default[0] + 1, default[1], py_off, rw,
                             locals_, out, in_static)
        if first:
            out.append("\t" * py_ind + "pass")
        return end

    def _stmt(self, line, py_indent, rw, locals_, in_func, in_static=False):
        """发射一条语句（可能展开成多行）。

        py_indent = **首行**的最终 Python 缩进层数（调用方完成 GDScript→Python 换算）。

        ★ 必须剥掉行首原有的 tab 再前缀：rewrite() 全程保留前导缩进（mask_strings
          只动字符串），若直接 `py_indent + r` 就会把缩进叠成两倍 —— 而两倍缩进
          在 Python 里往往仍是**合法**的（只要同一块内一致），会静默改变嵌套层级。
          续行（括号内、`if x: stmt` 拆出的第二行）保留**相对**首行的缩进。
        """
        r = rw.rewrite(line, locals_, in_func, in_static)
        r = "\n".join(rewrite_divmod(p, self.stat) for p in r.split("\n"))
        parts = r.split("\n")
        # ★ np24：GDScript `assert(cond, msg)` 直译成 `assert (cond, msg)` 在
        #   Python 里是**恒真元组**（非空元组为真）——断言永不触发。剥掉这层
        #   括号还原成 py 的 `assert cond, msg`（只在顶层逗号处拆，括号平衡内不动）。
        first = parts[0].lstrip("\t")
        if first.startswith("assert (") and first.endswith(")"):
            inner = first[len("assert ("):-1]
            depth = 0
            for _i, _ch in enumerate(inner):
                if _ch in "([{":
                    depth += 1
                elif _ch in ")]}":
                    depth -= 1
                elif _ch == "," and depth == 0:
                    parts[0] = ("\t" * py_indent + "assert " + inner[:_i].strip()
                                + ", " + inner[_i + 1:].strip())
                    break
        base_gd = count_tabs(parts[0])
        out = ["\t" * py_indent + parts[0].lstrip("\t")]
        for p in parts[1:]:
            if not p.strip():
                out.append("")
                continue
            rel = count_tabs(p) - base_gd
            out.append("\t" * (py_indent + max(rel, 0)) + p.lstrip("\t"))
        return out


def _rt_export_names():
    """从 gd_core_py/_rt.py 源 AST 提取 __all__ 字面量（生成期只读一次）。

    不 import 运行态 _rt（避免把 .pyd 产物状态当真源）。"""
    import ast as _ast
    p = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                     "gd_core_py", "_rt.py")
    tree = _ast.parse(io.open(p, encoding="utf-8").read())
    for node in tree.body:
        if isinstance(node, _ast.Assign) and len(node.targets) == 1 \
                and isinstance(node.targets[0], _ast.Name) \
                and node.targets[0].id == "__all__":
            return {elt.value for elt in node.value.elts
                    if isinstance(elt, _ast.Constant)}
    raise RuntimeError("M1-2: _rt.py 未找到 __all__ 字面量")


_RT_EXPORT_NAMES = _rt_export_names()


def transform_file(f, by_name, by_path, stat, hit, class_names):
    # ★ 生成模块在 gd_core/ 或 gd_core_items/[子目录/] 包里，而 _rt/_registry 在
    #   gd_core_py 顶层 —— 必须写足够的上级点数（`.` 会被解析成 gd_core_py.gd_core._rt，
    #   报 "No module named ..."）。depth = 路径段数 - 1（减掉模块自身）。
    depth = len(f.rel[:-3].split("/")) - 1
    dots = "." * (depth + 1)
    if _is_pxd_whitelisted(f.rel):
        # ★ M1-2/L1：白名单模块伴随 pxd cimport GodotObject——
        #   编译态模块 dict 预绑该 C type，`from .._rt import *` 重绑即抛
        #   "Cannot overwrite C type"。故改发**显式具名导入**（剔除
        #   GodotObject；静态解析保住 Cython 对 f32/_iter 等的识别），
        #   GodotObject 由 pxd cimport 提供编译态绑定；纯 py 态无 pxd，
        #   由「条件补绑」行补上。__all__ 清单生成期从 _rt.py 源 AST 提取。
        names = _RT_EXPORT_NAMES - {"GodotObject"}
        out = [GEN_BANNER,
               "from %s_rt import (  # noqa: F401\n" % dots,
               ",\n".join("    %s" % n for n in sorted(names)),
               ",\n)\n",
               "if \"GodotObject\" not in globals():\n"
               "\tfrom %s_rt import GodotObject  # 纯 py 补绑；编译态 pxd 已预绑\n" % dots,
               "from %s import _registry as _R\n" % dots,
               "\n\n"]
    else:
        out = [GEN_BANNER,
               "from %s_rt import *  # noqa: F401,F403\n" % dots,
               "from %s import _registry as _R\n" % dots,
               "\n\n"]
    base = resolve_ref(f.extends, by_name, by_path)
    if f.extends is None:
        base_expr = "GodotObject"
    elif base is not None:
        base_expr = '_R.C("%s")' % base.res_path
    else:
        base_expr = TYPE_MAP.get(f.extends, "GodotObject")
    out.append("class %s(%s):\n" % (f.py_class, base_expr))
    _cls_idx = len(out) - 1          # 内嵌类要插到这一行之前，见 Emitter.hoisted
    out.append('\tresource_path = "%s"\n' % f.res_path)

    members, methods, enums, signals, _nested, fields = collect_class_scope(
        f.lines, 0, len(f.lines), 0, stat)
    # ★ 必须回填：继承链上的成员/方法靠 `a.own_members` 取（见下一行循环），
    #   而 topological order 保证基类先 transform。早期版本漏了这两行赋值，
    #   于是子类看不到父类成员 —— 表现不是报错，而是「父类字段名没被加 self.」，
    #   在运行到那一行时才 NameError，且只在部分物品上出现。
    f.own_members = set(members)
    f.own_methods = set(methods)
    for a in f.ancestors:
        members |= a.own_members
        methods |= a.own_methods

    if enums:
        for _ind, ename, ebody in enums:
            out.append("\t%s = %s\n" % (ename, render_enum(ename, ebody, stat)))
        out.append("\n")
    for sname in signals:
        out.append('\t%s = Signal("%s")\n' % (sname, sname))
    if signals:
        out.append("\n")

    # ★ 本文件自己声明的类名（顶层 py_class + 全部同文件类）：它们在本模块内是
    #   模块全局名，直接裸引用即可，不要再走 _R.C（见 Rewriter._classrefs）。
    own = {f.py_class} | set(re.findall(r"^\s*class\s+([A-Za-z_]\w*)",
                                        "\n".join(f.lines), re.M))

    em = Emitter(f, by_name, by_path, stat, hit, class_names, own)
    # 顶层类：GDScript 类体层缩进 0、Python 类体层缩进 1 → py_off = 1
    em.field_inits(fields, 0, 1, members, methods, out)
    em.class_body(f.lines, 0, len(f.lines), 0, 1, members, methods, out)

    # 同文件 Inner Class：提到模块级、且放在外层类**之前**。
    # ★ 为什么必须在前：外层类体层可能出现引用内嵌类的初值（`X.new()`），
    #   那种引用在**类定义时**求值，内嵌类必须先存在。
    #   反方向（内嵌类引用外层）全部发生在方法体内，Python 在**调用时**才查模块全局，
    #   故与顺序无关 —— 实测 8 个内嵌类无反向的类体级引用。
    if em.hoisted:
        out[_cls_idx:_cls_idx] = em.hoisted

    # ★ 内嵌类还要在外层类上**留一份别名**：GDScript 既允许裸名 `BalancedRng.new(...)`
    #   （同文件内），也允许经实例/类去取 `ctx.rng.BalancedRng.new(...)`
    #   —— 后者在 GDScript 里能拿到那个内嵌类，提到模块级后就成了「实例上没有该属性」，
    #   运行到那一行才 AttributeError（CoreCharacter.gd:178-181 与 CoreItem.gd:191-192
    #   共 6 处正是这个形态）。别名同时覆盖 `Outer.Inner` 与 `instance.Inner` 两种写法。
    # ★ 别名会**覆盖**外层类上同名的方法/字段，故必须排除这两种真冲突。
    #   注意不能拿 `members` 当判据：collect_class_scope 本就把内嵌类名并入 members
    #   （这样 `_members` 知道它们是名字），那是既有设计，不是冲突。
    _field_names = {fn for fn, _d in fields}
    # ★ M1-2（2026-11-11）：内嵌类别名原为类型级**创建后**赋值
    #   （`X.Inner = Inner`）——cdef class（白名单）类型不可变，创建后加
    #   属性即 TypeError。别名必须保留（instance.Inner 访问面，CoreCharacter
    #   的 self.ctx.rng.BalancedRng 实证）——白名单模块改发**类体末尾**的
    #   缩进赋值（type 创建期落 type dict，与 Target=EnumDict 同机制）；
    #   内嵌类均先于外层类发射（out[_cls_idx] 插入点实证），名字已绑定。
    #   非白名单模块保持原类型级赋值（plain 类可变）。
    for _nm in em.hoisted_names:
        if _nm in methods or _nm in _field_names:
            stat["内嵌类别名撞名"].append("%s.%s" % (f.py_class, _nm))
        if _is_pxd_whitelisted(f.rel):
            out.append("\t%s = %s" % (_nm, _nm))
        else:
            out.append("%s.%s = %s" % (f.py_class, _nm, _nm))
    if em.hoisted_names:
        out.append("")

    text = "\n".join(out) + "\n\n"
    # ★ push_back 兜底（round16）：调用改写器按行解析实参，跨行续行的
    #   .push_back( 会原样漏到 Python 侧（CoreItem.py 3 处 trace 块实证）。
    #   GDScript push_back 仅 Array 所有 → py list.append 恒等价，全量重写安全。
    n_pb = text.count(".push_back(")
    if n_pb:
        text = text.replace(".push_back(", ".append(")
        hit[".push_back→append(兜底)"] = \
            hit.get(".push_back→append(兜底)", 0) + n_pb
    # PoolRealArray f32 舍入模板（op11）：gd 侧无 f32 cast，用 PoolRealArray
    # 单元素写读实现；py 侧 rt.f32（struct round-trip）等价。三行模板整体替换，
    # 防全量重转写冲掉手改（SSD 19 场 PoolRealArray NameError 实证）。
    _T2 = chr(9) + chr(9)
    _pa_tpl = _T2 + "pa = PoolRealArray()" + chr(10) + _T2 + "pa.append(x)" + chr(10) + _T2 + "return pa[0]"
    n_f32 = text.count(_pa_tpl)
    if n_f32:
        text = text.replace(_pa_tpl, _T2 + "return f32(x)")
        hit["PoolRealArray→rt.f32"] = hit.get("PoolRealArray→rt.f32", 0) + n_f32
    text += '_R.reg("%s", %s)\n' % (f.res_path, f.py_class)
    if f.class_name:
        text += '_R.reg("%s", %s)\n' % (f.class_name, f.py_class)
    stem = os.path.splitext(os.path.basename(f.rel))[0]
    text += '_R.reg("%s", %s)\n' % (stem, f.py_class)
    return text


# ═══════════════════════════ 导出 ═══════════════════════════

_ILLEGAL = re.compile(r"[^A-Za-z0-9_]")


def _sani(part):
    """把路径分量/模块名里对 Python 非法的字符换成 `_`。

    ★ 项目里有 3 个物品脚本名带连字符（`White-EyesBlueDragon.gd` 等）。
      `import gd_core_py.gd_core_items.White-EyesBlueDragon` 是语法错误，
      会让整条 bootstrap 导入链在第 629 行断掉 —— 而且报错位置指向 _bootstrap，
      不指向真正的肇事文件。注意只改 Python 侧的模块/文件名，
      res_path 与注册别名保持 GDScript 原样（那是 GDScript 在用的键）。
    """
    return _ILLEGAL.sub("_", part)


def module_path(f):
    return "gd_core_py." + ".".join(_sani(p) for p in f.rel[:-3].split("/"))


def py_file_rel(rel):
    """`gd_core/xxx.gd` → `gd_core/xxx.py`（逐段 sanitize 的相对路径）。"""
    return "/".join(_sani(p) for p in rel[:-3].split("/")) + ".py"


def emit_bootstrap(order, files_by_rel, stripped_hooks=None):
    out = [GEN_BANNER,
           '"""按 extends 依赖拓扑序导入全部模块（基类先注册，与 Godot 加载次序同义）。"""\n\n',
           "from . import _registry  # noqa: F401\n",
           "from . import _rt  # noqa: F401\n\n\n",
           # ── S2-B2 回归修复配套：stem → 全模块路径全量映射。_registry
           #    ._lazy_import 用它兜底 items 树的非祖先跨类引用
           #    （ChessBoard 运行时 isinstance _R.C("ChessPiece")，ChessPiece
           #    非 ChessBoard 祖先、不在 load_for 闭包 → 此前落占位类，
           #    isinstance 恒 False=沉默语义死 / 属性访问炸=py 腿缺产物，
           #    60 场精选集 14 红根因）。load_all 时代「任何 C() 可解析」。
           "def _stem2mod_rows():\n",
           "    return [\n"]
    for rel in order:
        mod = module_path(files_by_rel[rel])
        stem = mod.rsplit(".", 1)[-1]
        out.append("        (%r, %r),\n" % (stem, mod))
    out.append("    ]\n\n\n")
    out.append("_STEM2MOD = dict(_stem2mod_rows())\n\n\n")
    out.append("def load_all():\n")
    out.append('    """导入全部 gd 模块。返回导入失败清单（空 = 全部成功）。"""\n')
    out.append("    failed = []\n")
    for rel in order:
        out.append("    try:\n")
        out.append("        import %s  # noqa: F401\n" % module_path(files_by_rel[rel]))
        out.append("    except Exception as exc:  # noqa: BLE001\n")
        out.append("        failed.append((%r, repr(exc)))\n" % rel)
    out.append("    return failed\n\n\n")

    # ── S2-B2 分层导入（docs/性能优化执行路径.md；设计数据 tools/leaf_audit.py）──
    # load_core() = gd_core/ 树全部模块（战斗判定面 + 物品适配层，159 个）；
    # load_for(scripts) = 按阵容物品脚本路径补导 items 树的祖先闭包
    # （抽样阵容平均 ~3 个模块，冷启动可省 ≈76% 导入；判据 A
    # 「leaf 直接基类全部可解析」已由 leaf_audit 全量验证 0 违例）。
    # ★ 基类必须先于子类导入（class X(_R.C(基类)) 在导入期求值），故
    #   load_for 沿 _ITEM_PARENTS 先展开闭包、再按 _ITEM_ORDER 拓扑序导入。
    def _items_edges():
        parents = {}
        for rel in order:
            if not rel.startswith("gd_core_items/"):
                continue
            f = files_by_rel[rel]
            ps = sorted({seg.rel for seg in (f.ancestors or [])
                         if seg.rel.startswith("gd_core_items/")})
            parents[rel] = ps
        return parents

    iparents = _items_edges()
    item_order = [rel for rel in order if rel.startswith("gd_core_items/")]

    # load_core 地板集修正（判据：gd_core/ 适配树在导入期继承行为基类，
    # np24-P3-7 双树结构）：gd_core/ 模块的 items 祖先闭包必须随档一导入，
    # 否则占位类静默顶替（_R.missing() 闸会红）。leaf_audit 抽样口径与此同。
    need_core = set()

    def _need_transitive(rels):
        stack = list(rels)
        while stack:
            r0 = stack.pop()
            if r0 in need_core:
                continue
            need_core.add(r0)
            stack.extend(iparents.get(r0, ()))

    for rel in order:
        if rel.startswith("gd_core/"):
            for seg in files_by_rel[rel].ancestors or []:
                if seg.rel.startswith("gd_core_items/"):
                    _need_transitive([seg.rel])

    out.append("# 物品树 extends 父链（生成期从 GDScript extends 段提取，仅 items 树内父）\n")
    out.append("_ITEM_PARENTS = {\n")
    for rel, ps in iparents.items():
        if ps:
            out.append("    %r: %r,\n" % (rel, ps))
    out.append("}\n\n")
    out.append("# items 树拓扑序（load_all 同序的子序列，基类先于子类）\n")
    out.append("_ITEM_ORDER = [\n")
    for rel in item_order:
        out.append("    %r,\n" % rel)
    out.append("]\n\n")
    # ★ 档二性能：load_for 原先对每个阵容脚本线性扫 _ITEM_ORDER 全表
    #   （108 脚本 × 505 项 = 5.5 万次 rsplit，实测 7.5 ms/场，占装配 24%）。
    #   items 树 stem 无重名（生成期断言下方），故可索引化到 O(1) 查找。
    _stems = {}
    for rel in item_order:
        _stem = rel.rsplit("/", 1)[-1][:-3]
        assert _stem not in _stems, ("items 树 stem 重名：%r ↔ %r"
                                     % (_stems.get(_stem), rel))
        _stems[_stem] = rel
    out.append("# items 树 stem → rel（生成期断言无重名；load_for 的 O(1) 索引）\n")
    out.append("_ITEM_STEM = {\n")
    for _stem, rel in _stems.items():
        out.append("    %r: %r,\n" % (_stem, rel))
    out.append("}\n\n")
    out.append("# items 树 (rel, 模块路径)，拓扑序——load_for 按需循环导入\n")
    out.append("_ITEM_MODULES = [\n")
    for rel in item_order:
        out.append("    (%r, %r),\n" % (rel, module_path(files_by_rel[rel])))
    out.append("]\n\n\n")

    out.append("def load_core():\n")
    out.append('    """档一：gd_core/ 树全部模块 + 其行为基类闭包（战斗判定面）。返回失败清单。"""\n')
    out.append("    failed = []\n")
    for rel in order:
        if not rel.startswith("gd_core/") and rel not in need_core:
            continue
        out.append("    try:\n")
        out.append("        import %s  # noqa: F401\n" % module_path(files_by_rel[rel]))
        out.append("    except Exception as exc:  # noqa: BLE001\n")
        out.append("        failed.append((%r, repr(exc)))\n" % rel)
    out.append("    return failed\n\n\n")

    out.append("def load_for(scripts):\n")
    out.append('    """档二：按阵容脚本路径补导 items 祖先闭包。幂等；须先 load_core()。"""\n')
    out.append("    failed = []\n")
    out.append("    want = set()\n")
    out.append("    for s in scripts or ():\n")
    out.append("        stem = str(s).rsplit('/', 1)[-1]\n")
    out.append("        if stem.endswith('.gd'):\n")
    out.append("            stem = stem[:-3]\n")
    out.append("        rel = _ITEM_STEM.get(stem)\n")
    out.append("        if rel is None:\n")
    out.append("            continue\n")
    out.append("        stack = [rel]\n")
    out.append("        while stack:\n")
    out.append("            r0 = stack.pop()\n")
    out.append("            if r0 not in want:\n")
    out.append("                want.add(r0)\n")
    out.append("                stack.extend(_ITEM_PARENTS.get(r0, ()))\n")
    out.append("    # 拓扑序逐项导入（与原先静态 if 链同序，仅保留「按需」约束）\n")
    out.append("    for rel, mod in _ITEM_MODULES:\n")
    out.append("        if rel not in want:\n")
    out.append("            continue\n")
    out.append("        try:\n")
    out.append("            __import__(mod)\n")
    out.append("        except Exception as exc:  # noqa: BLE001\n")
    out.append("            failed.append((rel, repr(exc)))\n")
    out.append("    return failed\n")

    # ── M2-1 空钩子剥离清单（装配期断言数据源，simulator/gd_core_engine
    #    ._make_probe_class 读它对探针覆写做交集检查）──
    out.append("\n\n# ── M2-1 空钩子剥离清单（生成器发射；勿手改）──\n")
    out.append("STRIPPED_HOOKS = %r\n" % (sorted(stripped_hooks or ()),))
    return "".join(out)


def _apply_cooldown_f32(texts):
    """★ np25 P3（py-only 压线到期翻转）：冷却链对称 float32 化。

    GDScript 3 的 Variant REAL 是 float32——每个算术 op 一次舍入；直译成
    Python float64 后低位分叉在**压线到期判定**（triggerTime 恰在 0 附近）
    上翻帧：run874_r7 实证同一物理帧 gd 到期序 Chili#10→Chili#11→Blueberries、
    py 为 Chili#10→Blueberries→Chili#11（TRIG/BUS 双侧桩，rng 消耗逐值全等）。
    规则清单覆盖 triggerTime/iterationCooldown/speedScale 的**全部**写点
    （缺一处就制造新的单边不对称——np25 曾因漏 953/970 两写点把 run570 打红）。
    f32 = _rt 的 float32 舍入垫片（生成文件已 `from ._rt import *`）。

    ★★ np25 f64 实验面（2026-10-30，修复员·py-only 11 场收编）——本函数已整体
    停用（BYPASS）：Godot 3.x 的 Variant REAL / GDScript float 实为 **64 位
    double**（P3 前提「REAL=float32」系与 Godot 4 混淆的误设），gd 侧
    CoreItem.gd 冷却链为 typed float 直减无外层舍入 ⇒ 正确转写 = 纯 f64 直译。
    P3 的 f32 规则在 11 场 py-only 冷却族（run571/581/701/787/828/864/960/
    1189/1222/1223/1406）上制造压线 ±1 tick 翻转（勘察输入实测 run1223_r7
    翻转拍 triggerTime=0.01657561772、每帧递减≈0.01666665、穿越残差 −9.1e-8s）。
    143 场全量「行为中性」旁证gd 实际算术更近 f64（台账 run874 定谳原文）。
    规则表保留在下方仅作历史档案（R_LIST_F32），便于回滚/对照。
    """
    return texts  # ← BYPASS：f64 直译
    R = [
        # 物理帧推进（Item.py 与 CoreItem.py 两处同形）
        ("self.triggerTime -= delta * self.getSpeed()",
         "self.triggerTime = f32(self.triggerTime - f32(delta * self.getSpeed()))"),
        # speed 链（getSpeed）
        ("speed_ = self.speed() + self.getStackSpeedMods()",
         "speed_ = f32(self.speed() + self.getStackSpeedMods())"),
        ("modifiedSpeed = 1.0 + speed_",
         "modifiedSpeed = f32(1.0 + speed_)"),
        ("modifiedSpeed = _div(1.0, 1.0 - speed_)",
         "modifiedSpeed = f32(_div(1.0, 1.0 - speed_))"),
        ("modifiedSpeed = clamp(modifiedSpeed, 0.1, 10.0)",
         "modifiedSpeed = f32(clamp(modifiedSpeed, 0.1, 10.0))"),
        # getStackSpeedMods
        ("return (self.character().getHeat() - self.character().getCold()) * 0.02",
         "return f32(f32(self.character().getHeat() - self.character().getCold()) * 0.02)"),
        # adjustCooldown
        ("adjustedCooldown = self.getCooldown()",
         "adjustedCooldown = f32(self.getCooldown())"),
        ("adjustedCooldown *= self.ctx.rng.randf_range(0.975, 1.05)",
         "adjustedCooldown = f32(adjustedCooldown * self.ctx.rng.randf_range(0.975, 1.05))"),
        ("adjustedCooldown *= self.ctx.rng.randf_range(0.95, 1.05)",
         "adjustedCooldown = f32(adjustedCooldown * self.ctx.rng.randf_range(0.95, 1.05))"),
        # updateBaseCooldown
        ("cdProgress = _div(self.triggerTime, self.iterationCooldown)",
         "cdProgress = f32(_div(self.triggerTime, self.iterationCooldown))"),
        # trigger() 与 onCooldownStart（两处同形 iterationCooldown 赋值）
        ("self.iterationCooldown = self.adjustCooldown()",
         "self.iterationCooldown = f32(self.adjustCooldown())"),
        ("self.triggerTime = self.iterationCooldown",
         "self.triggerTime = f32(self.iterationCooldown)"),
        ("self.triggerTime += self.iterationCooldown",
         "self.triggerTime = f32(self.triggerTime + self.iterationCooldown)"),
        ("self.triggerTime = cdProgress * self.iterationCooldown",
         "self.triggerTime = f32(cdProgress * self.iterationCooldown)"),
        # advanceCooldownPercent / advanceCooldownSeconds
        ("reduction = _div(amount, 100.0) * self.iterationCooldown",
         "reduction = f32(_div(amount, 100.0) * self.iterationCooldown)"),
        ("self.triggerTime -= reduction",
         "self.triggerTime = f32(self.triggerTime - reduction)"),
        ("self.triggerTime -= amount * self.getSpeed()",
         "self.triggerTime = f32(self.triggerTime - f32(amount * self.getSpeed()))"),
        # addSpeed / reduceSpeed
        ("self.speedScale += amount",
         "self.speedScale = f32(self.speedScale + amount)"),
        ("self.speedScale -= amount",
         "self.speedScale = f32(self.speedScale - amount)"),
    ]
    for rel, text in list(texts.items()):
        t = text
        for old, new in R:
            if old in t:
                t = t.replace(old, new)
        if t != text:
            texts[rel] = t
    return texts


def _hoist_classrefs(texts, order, files_by_rel, stat, hit):
    """S3-C4：把函数体内的 `_R.C(...)` 类引用提升为模块末常量绑定。

    动机（docs/性能优化执行路径.md S3 批1；A1 剖面实证）：`_R.C` 每调用
    查注册表 ≈13 万次/场，前四名热点 getHeat/getCold/getSpeed/canAffect_color
    全是 `_R.C("CoreConst").枚举.成员` 形态——三层开销（函数调用+dict 查找
    +EnumDict.__getattr__）。提升后热路径只剩一次模块全局名读取。

    安全规则（违者一律保持动态 C()，宁少勿错）：
      1. 只提升**函数体内**的引用——class 体/模块级/函数签名默认值在导入期
         求值，先于模块末绑定存在；
      2. 目标 stem 全树唯一，或目标模块是本模块的 extends 祖先（拓扑序保证
         已导入）。两树同名（Item/Bag 等 reg() 仲裁名）且非祖先的引用**不提升**
         ——运行时 C() 拿仲裁终态，模块末提前绑定可能拿到错树的类；
      3. 目标可解析：gd_core/ 树恒先全量载（load_core/load_all/load_for 皆然），
         故 gd_core/ 目标恒可提升；items 树目标仅祖先链可提升；
      4. 提升形态：纯属性链 `_R.C(x).a.b`（链尾不被立即调用）整链提升为常量
         （枚举成员= int，值稳定）；链被立即调用或非属性链只提升 C() 本身。
         绑定表达式在模块末重新求值，语义与原位求值一致（注册表此时已含目标）。

    落地方式：AST 定位表达式 Span → 原文精确替换为常量名（注释/缩进/排版
    全保留）→ 模块末发射绑定块。守门：REG 九场 + ast_diff（预期差异面=
    Name/Attribute/Call 数量变化 + 文件尾新增 Assign）。
    """
    # stem → 模块 rel 清单（跨树同名检测）
    stem2rels = {}
    for rel, f in files_by_rel.items():
        stem2rels.setdefault(_stem_of_rel(rel), []).append(rel)

    def _target_qualifies(arg_src, cur_rel, ancestor_rels):
        stem = arg_src
        if stem.startswith("res://"):
            stem = stem[len("res://"):]
        if stem.endswith(".gd"):
            stem = stem[:-3]
        rels = stem2rels.get(stem)
        if not rels:
            return False                      # 不可解析（TYPE_MAP 等已在上游排除）
        if len(rels) == 1:
            target = rels[0]
        else:
            # 歧义名：仅当解析目标在本模块祖先链（或就是本模块）才提升
            same = [r for r in rels if r == cur_rel]
            anc = [r for r in rels if r in ancestor_rels]
            if same:
                return True
            if anc:
                target = anc[0]
            else:
                return False
        if target == cur_rel:
            return True
        if target in ancestor_rels:
            return True
        if target.startswith("gd_core/"):
            return True                       # gd_core 树恒先全量载
        return False

    import ast as _ast

    changed_total = 0
    for rel in order:
        text = texts.get(rel)
        if not text or "_R.C(" not in text:
            continue
        f = files_by_rel[rel]
        ancestor_rels = {a.rel for a in (f.ancestors or [])}
        try:
            tree = _ast.parse(text)
        except SyntaxError:
            continue
        # 父链表
        pmap = {}
        for p in _ast.walk(tree):
            for c in _ast.iter_child_nodes(p):
                pmap[c] = p
        # 收集候选 C() 调用（函数体内、单常量参）
        cands = []
        for node in _ast.walk(tree):
            if not isinstance(node, _ast.Call):
                continue
            fu = node.func
            if not (isinstance(fu, _ast.Attribute) and fu.attr == "C"
                    and isinstance(fu.value, _ast.Name) and fu.value.id == "_R"):
                continue
            if (len(node.args) != 1
                    or not isinstance(node.args[0], _ast.Constant)
                    or not isinstance(node.args[0].value, str)):
                continue
            # 函数体内判定（签名默认值/装饰器/class 体一律排除）
            cur, ok = node, False
            while True:
                p = pmap.get(cur)
                if p is None:
                    break
                if isinstance(p, _ast.FunctionDef):
                    ok = any(_span_contains(b, node) for b in p.body)
                    break
                if isinstance(p, (_ast.ClassDef, _ast.Module)):
                    break
                cur = p
            if not ok:
                continue
            # 目标安全判定
            if not _target_qualifies(node.args[0].value, rel, ancestor_rels):
                continue
            # 向上扩展纯属性链（链尾不被立即调用才算整链）
            span = node
            while True:
                p = pmap.get(span)
                if isinstance(p, _ast.Attribute) and p.value is span:
                    gp = pmap.get(p)
                    if isinstance(gp, _ast.Call) and gp.func is p:
                        break                   # 链被调用：止于当前（C() 本身）
                    span = p
                    continue
                break
            cands.append((node, span))

        if not cands:
            continue
        # 唯一化：同源码表达式共享一个常量；每个候选点独立替换
        uniq = {}
        chain_srcs = set()                    # 属性链提升（需惰性哨兵兜底）
        for _node, span in cands:
            src = _span_text(text, span)
            if src not in uniq:
                uniq[src] = "_H_%d" % (len(uniq) + 1)
            if span is not _node:             # 非纯 C()：带属性链
                chain_srcs.add(src)
        reps = sorted(((span.lineno, span.col_offset,
                        span.end_lineno, span.end_col_offset,
                        uniq[_span_text(text, span)])
                       for _node, span in cands),
                      key=lambda r: (-r[0], -r[1]))
        lines = text.split("\n")
        for l1, c1, l2, c2, name in reps:
            if l1 == l2:
                lines[l1 - 1] = lines[l1 - 1][:c1] + name + lines[l1 - 1][c2:]
            else:
                lines[l1 - 1] = lines[l1 - 1][:c1] + name
                for mid in range(l1, l2 - 1):
                    lines[mid] = ""
                lines[l2 - 1] = lines[l2 - 1][c2:]
        # 模块末绑定块
        # ★ 属性链提升一律 try/except：GDScript 源里存在「引用了别的类上不存在的
        #   属性」的死路径（如 gd_core/Item.gd:1064 → CoreConst.CraftingPriority，
        #   该枚举实际在 Item.gd:82——原位求值=调用时 AttributeError，双腿同构）。
        #   绑定挪到导入期不能把死路径提前炸响，故失败位绑定 _HoistPending
        #   （_rt 哨兵：首次真实使用在同调用点抛同型异常）。
        block = ["",
                 "# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，"
                 "模块末绑定）──"]
        for src, name in sorted(uniq.items(), key=lambda kv: kv[1]):
            if src in chain_srcs:
                # ★ try/except 体用 TAB 缩进——产物全文件为 tab 缩进，Cython
                #   词法对 tab/space 混用做全局校验（比 CPython 严），混排即拒编
                block.append("try:")
                block.append("\t%s = %s" % (name, src))
                block.append("except AttributeError as _he:")
                block.append("\t%s = _HoistPending(_he)" % name)
            else:
                block.append("%s = %s" % (name, src))
        new_text = "\n".join(lines) + "\n" + "\n".join(block) + "\n"
        _ast.parse(new_text)                  # 语法自检，破即中止生成
        texts[rel] = new_text
        changed_total += 1
        hit["C4提升常量"] += len(uniq)
    hit["C4提升模块"] = changed_total
    stat["C4"] = ["%d 模块" % changed_total]
    return texts


def _stem_of_rel(rel):
    s = rel.rsplit("/", 1)[-1]
    if s.endswith(".py"):
        s = s[:-3]
    elif s.endswith(".gd"):
        s = s[:-3]
    return s


def _span_text(text, node):
    lines = text.split("\n")
    l1, c1, l2, c2 = node.lineno, node.col_offset, node.end_lineno, node.end_col_offset
    if l1 == l2:
        return lines[l1 - 1][c1:c2]
    parts = [lines[l1 - 1][c1:]]
    parts += lines[l1:l2 - 1]
    parts.append(lines[l2 - 1][:c2])
    return "\n".join(parts)


def _span_contains(outer, inner):
    return (outer.lineno, outer.col_offset) <= (inner.lineno, inner.col_offset) and \
           (inner.end_lineno, inner.end_col_offset) <= (outer.end_lineno, outer.end_col_offset)


def _iter_inline(texts, stat, hit):
    """S3-C1-lite：`for v in _iter(ARG):` 对纯名字/属性链 ARG 发射内联守卫。

    动机（A1 剖面 post-C4）：`_iter` 59 万次/3场居首，大头是**微小列表**
    （_tickTimers 8.8 万次调用各带一个 `_iter`，计时器列表通常 1-3 个元素）。
    每次调用 = 函数帧 + 2-4 层 isinstance——内联守卫消掉函数调用本身。

    改写：`for v in _iter(ARG):` → `for v in (ARG if ARG.__class__ is list
    else _iter(ARG)):`。语义等价性：
      · ARG 限**纯名字或属性链**（无函数调用=无副作用，双重求值无害；
        EnumDict 等自定义 __getattr__ 亦无副作用，且非 list 落回 _iter 同路）；
      · 条件表达式在循环开始前求值**一次**（与原 `_iter(ARG)` 同点同次）；
      · list 精确匹配（__class__ is list）——子类与其它类型一律落回 _iter
        原分支，字典/float/int 语义逐位不变。
    """
    import ast as _ast
    changed = 0
    total = 0
    for rel in list(texts):
        text = texts[rel]
        if "_iter(" not in text:
            continue
        try:
            tree = _ast.parse(text)
        except SyntaxError:
            continue
        pmap = {}
        for p in _ast.walk(tree):
            for c in _ast.iter_child_nodes(p):
                pmap[c] = p
        cands = []
        for node in _ast.walk(tree):
            if not isinstance(node, _ast.Call):
                continue
            fu = node.func
            if not (isinstance(fu, _ast.Name) and fu.id == "_iter"
                    and len(node.args) == 1):
                continue
            arg = node.args[0]
            if not (isinstance(arg, _ast.Name)
                    or isinstance(arg, _ast.Attribute)):
                continue
            # ARG 链上不允许任何 Call（防副作用双重求值）
            if any(isinstance(n, _ast.Call) for n in _ast.walk(arg)):
                continue
            # 只在 For.iter 的直接位置改写
            p = pmap.get(node)
            if not (isinstance(p, _ast.For) and p.iter is node):
                continue
            cands.append((arg, node))
        if not cands:
            continue
        reps = sorted(((node.lineno, node.col_offset,
                        node.end_lineno, node.end_col_offset,
                        _span_text(text, arg))
                       for arg, node in cands),
                      key=lambda r: (-r[0], -r[1]))
        lines = text.split("\n")
        for l1, c1, l2, c2, arg_src in reps:
            # ★ 用 __class__ 而非 type()：生成代码里存在局部变量 `type` 遮蔽
            #   内建（GDScript 常见 `var type`），arg.__class__ 无遮蔽风险
            new_expr = "(%s if %s.__class__ is list else _iter(%s))" % (
                arg_src, arg_src, arg_src)
            if l1 == l2:
                lines[l1 - 1] = lines[l1 - 1][:c1] + new_expr + lines[l1 - 1][c2:]
            else:
                lines[l1 - 1] = lines[l1 - 1][:c1] + new_expr
                for mid in range(l1, l2 - 1):
                    lines[mid] = ""
                lines[l2 - 1] = lines[l2 - 1][c2:]
            total += 1
        new_text = "\n".join(lines)
        try:
            _ast.parse(new_text)
        except SyntaxError:
            continue                      # 安全网：失败保原样
        texts[rel] = new_text
        changed += 1
    hit["C1内联For"] = total
    stat["C1"] = ["%d 模块 %d 处" % (changed, total)]
    return texts


def _inline_accessors(texts, stat, hit):
    """S3-C6-lite：零覆写单返回访问器在调用点内联（A1 剖面堆栈链 54 万次/3场）。

    全树审计（grep `^func <名>` 于 gd_core/ + gd_core_items/）确认以下方法
    **无任何子类覆写**（GDScript 方法默认虚分派，零覆写=静态内联安全），
    且方法体为单表达式（self 只读、无副作用）：
      · CoreBuff.getStacks()      → self._current（property 存储位直读，
                                    免 property 描述符 + 免一层调用）
      · CoreCharacter.getStacks(t) → self.buffs[t]._current（免两层调用）
      · CoreCharacter.isStunned()  → self.stunnedDuration > 0
    改写（调用点 Span 替换，接收者表达式原样复用、只出现一次=无双重求值）：
      E.getStacks()   → E._current
      E.getStacks(A)  → E.buffs[A]._current
      E.isStunned()   → (E.stunnedDuration > 0)   # 加括号防优先级错位
    ★ 守门：REG 九场 + 同 seed tick 等价 + ast_diff 预期面。任何一层将来
      被子类覆写，本趟必须同步收窄（审计表写死在 _INLINE_ACCESSORS）。
    """
    import ast as _ast
    # ★ 机械审计（替代手工 grep）：同名方法跨类定义数——>1 类定义即弃该模式
    #   （GDScript 虚分派下接收者类型不可静态判定，盲内联=改错类语义。
    #   实测：getStacks 同时存在于 CoreBuff/CoreConst/CoreCharacter——
    #   0-arg 形态弃用，1-arg 形态唯一归 CoreCharacter 保留）。
    defs_by_name = {}                     # name -> {call_arity: {classes}}
    for t in texts.values():
        try:
            t_tree = _ast.parse(t)
        except SyntaxError:
            continue
        for cd in _ast.walk(t_tree):
            if not isinstance(cd, _ast.ClassDef):
                continue
            for fd in cd.body:
                if not isinstance(fd, _ast.FunctionDef):
                    continue
                # ★ 调用态元数：@staticmethod 无 self 不减（CoreConst.getStacks
                #   即无参静态方法——首版按「减 self」算错 arities，0-arg 盲内联
                #   炸出 CoreConst._current）
                is_static = any(isinstance(d, _ast.Name) and d.id == "staticmethod"
                                for d in fd.decorator_list)
                call_arity = len(fd.args.args) - (0 if is_static else 1)
                defs_by_name.setdefault(fd.name, {}).setdefault(
                    call_arity, set()).add(cd.name)

    def _only_definer(name, call_arity, cls):
        # ★ 按调用态元数分派：n-arg 调用只能命中 call_arity==n 的定义，
        #   其他元数定义与此无关（getStacks 的 0-arg 定义不影响 1-arg 判定）
        d = defs_by_name.get(name, {})
        return d.get(call_arity) == {cls}

    inline_getStacks0 = _only_definer("getStacks", 0, "CoreBuff")
    inline_getStacks1 = _only_definer("getStacks", 1, "CoreCharacter")
    inline_isStunned = _only_definer("isStunned", 0, "CoreCharacter")
    inline_hasCharacter = _only_definer("hasCharacter", 0, "CoreItem")
    inline_speed = _only_definer("speed", 0, "CoreItem")
    inline_gssm = _only_definer("getStackSpeedMods", 0, "CoreItem")
    changed = 0
    total = 0
    for rel in list(texts):
        text = texts[rel]
        if ".getStacks(" not in text and ".isStunned(" not in text:
            continue
        try:
            tree = _ast.parse(text)
        except SyntaxError:
            continue
        pmap = {}
        for p in _ast.walk(tree):
            for c in _ast.iter_child_nodes(p):
                pmap[c] = p
        reps = []
        for node in _ast.walk(tree):
            if not isinstance(node, _ast.Call):
                continue
            fu = node.func
            if not isinstance(fu, _ast.Attribute):
                continue
            recv = fu.value
            if recv is None or isinstance(recv, _ast.Lambda):
                continue
            # ★ 接收者表达式**原样保留、求值一次**（与原 `.method()` 同点同次），
            #   任何形态（含 Call 接收者如 `self.character().isStunned()`）皆
            #   无副作用风险——原误判「含调用有风险」已修正（isStunned 72k
            #   剩余调用全在 Call 接收者上）。
            if (fu.attr == "getStacks" and not node.args and not node.keywords
                    and inline_getStacks0):
                new = "%s._current" % _span_text(text, recv)
            elif (fu.attr == "getStacks" and len(node.args) == 1
                    and not node.keywords and inline_getStacks1):
                a = node.args[0]
                if isinstance(a, (_ast.Starred, _ast.Lambda)):
                    continue
                new = "%s.buffs[%s]._current" % (_span_text(text, recv),
                                                 _span_text(text, a))
            elif (fu.attr == "isStunned" and not node.args and not node.keywords
                    and inline_isStunned):
                # ★ 单引用模式（接收者求值一次）——Call 接收者安全；
                #   C6c 曾误加双引用纯度守卫，把 self.character().isStunned()
                #   这类热站点（26k/场）挡在门外，2026-11-10 修正
                new = "(%s.stunnedDuration > 0)" % _span_text(text, recv)
            elif (fu.attr == "hasCharacter" and not node.args
                    and not node.keywords and inline_hasCharacter):
                if any(isinstance(n, _ast.Call) for n in _ast.walk(recv)):
                    continue
                new = "(%s.placed and %s.character_ != None)" % (
                    _span_text(text, recv), _span_text(text, recv))
            elif (fu.attr == "speed" and not node.args and not node.keywords
                    and inline_speed):
                # 单返回体（return speedScale）——接收者单引用，任意形态安全
                new = "%s.speedScale" % _span_text(text, recv)
            elif (fu.attr == "getStackSpeedMods" and not node.args
                    and not node.keywords and inline_gssm):
                # 体 = (character().getHeat() - character().getCold()) * 0.02
                # 展开后接收者出现两次 → 接收者限纯表达式（无调用=无副作用）
                if any(isinstance(n, _ast.Call) for n in _ast.walk(recv)):
                    continue
                r = _span_text(text, recv)
                new = ("(%s.character().getHeat() - %s.character().getCold()) * 0.02"
                       % (r, r))
            else:
                continue
            reps.append((node.lineno, node.col_offset,
                         node.end_lineno, node.end_col_offset, new))
        if not reps:
            continue
        reps.sort(key=lambda r: (-r[0], -r[1]))
        lines = text.split("\n")
        for l1, c1, l2, c2, new in reps:
            if l1 == l2:
                lines[l1 - 1] = lines[l1 - 1][:c1] + new + lines[l1 - 1][c2:]
            else:
                lines[l1 - 1] = lines[l1 - 1][:c1] + new
                for mid in range(l1, l2 - 1):
                    lines[mid] = ""
                lines[l2 - 1] = lines[l2 - 1][c2:]
            total += 1
        new_text = "\n".join(lines)
        try:
            _ast.parse(new_text)
        except SyntaxError:
            continue
        texts[rel] = new_text
        changed += 1
    hit["C6内联访问器"] = total
    stat["C6"] = ["%d 模块 %d 处" % (changed, total)]
    return texts


def _shim_locals(texts, stat, hit):
    """S3-C15：函数体内的 `_rt` 垫片全局引用提为局部别名（LOAD_GLOBAL→LOAD_FAST）。

    动机（A1 剖面 post-C6）：热函数每次调用多次 LOAD_GLOBAL 垫片名
    （_iter/_mod/_div/f32/clamp/min/max/int/len…）。模块全局在导入后恒定
    （生成代码从无再绑定），提为局部是纯读路径优化、零语义面。

    规则：
      · 只处理 FunctionDef 方法体（嵌套 def 跳过）；引用 ≥2 次的垫片名才提升；
      · 名字在该函数内被赋值/作形参（遮蔽）→ 跳过该名；
      · 别名 `原名__loc`（审计函数内与模块级均无占用才用）；
      · 改写 = 函数首行前插别名赋值 + 体内 Load 态 Name 跨度替换。
    语义安全：垫片为模块级常量函数/常量，无 global 语句、无运行期重绑定；
    ast_diff 预期面 = Name 数量变化 + 函数头新增 Assign。
    """
    import ast as _ast
    SHIMS = {"_iter", "_mod", "_div", "f32", "clamp", "_fill", "_erase",
             "_pop_at", "_find", "_resize", "_sort_custom", "_shuffle",
             "_get_slice", "_invert", "_hash", "_join", "_pick_random",
             "_substr", "_gd_fmt", "_gd_range", "_gd_str", "_strv", "stepify",
             "posmod", "fmod", "snapped", "move_toward", "wrapf", "wrapi",
             "is_equal_approx", "inverse_lerp", "smoothstep", "lerp", "sign",
             "deg2rad", "rad2deg", "DB", "GAP"}
    changed = 0
    total = 0
    for rel in list(texts):
        text = texts[rel]
        if "def " not in text:
            continue
        try:
            tree = _ast.parse(text)
        except SyntaxError:
            continue
        reps = []                             # (l1,c1,l2,c2,new)
        inserts = []                          # (lineno, col, assign_lines)
        seen_funcs = set()
        for cd in _ast.walk(tree):
            if not isinstance(cd, _ast.ClassDef):
                continue
            for fd in cd.body:
                if not isinstance(fd, _ast.FunctionDef) or id(fd) in seen_funcs:
                    continue
                seen_funcs.add(id(fd))
                # 收集本函数内（不含嵌套 def/签名默认值/装饰器）的垫片 Load 引用
                counts = {}
                shadowed = set()
                names_used = set()
                load_nodes = {}               # shim 名 -> [Name 节点]
                stack = list(fd.body)
                while stack:
                    n = stack.pop()
                    if isinstance(n, _ast.FunctionDef):
                        continue              # 嵌套函数不处理
                    if isinstance(n, _ast.Name):
                        names_used.add(n.id)
                        if n.id in SHIMS:
                            if isinstance(n.ctx, _ast.Load):
                                counts[n.id] = counts.get(n.id, 0) + 1
                                load_nodes.setdefault(n.id, []).append(n)
                            else:
                                shadowed.add(n.id)
                    stack.extend(_ast.iter_child_nodes(n))
                for a in fd.args.args:
                    shadowed.add(a.arg)
                # 函数体首语句缩进（取首行原文前缀——产物是 TAB 缩进，
                # 用空格重排会 tab/space 混排触发 SyntaxError）
                if not fd.body:
                    continue
                if fd.body[0].lineno == fd.lineno:
                    continue                  # 单行 def，无块体可插
                first_line = text.split("\n")[fd.body[0].lineno - 1]
                indent = first_line[:fd.body[0].col_offset]
                hoist = []
                for name, cnt in counts.items():
                    if name in shadowed or cnt < 2:
                        continue
                    alias = name + "__loc"
                    if alias in names_used or alias in SHIMS:
                        continue
                    hoist.append((name, alias))
                if not hoist:
                    continue
                inserts.append((fd.body[0].lineno, None,
                                [f"{indent}{a} = {n}"
                                 for n, a in hoist]))
                for name, alias in hoist:
                    for n in load_nodes.get(name, ()):
                        reps.append((n.lineno, n.col_offset,
                                     n.end_lineno, n.end_col_offset, alias))
        if not reps:
            continue
        reps.sort(key=lambda r: (-r[0], -r[1]))
        lines = text.split("\n")
        for l1, c1, l2, c2, new in reps:
            if l1 == l2:
                lines[l1 - 1] = lines[l1 - 1][:c1] + new + lines[l1 - 1][c2:]
            else:
                lines[l1 - 1] = lines[l1 - 1][:c1] + new
                for mid in range(l1, l2 - 1):
                    lines[mid] = ""
                lines[l2 - 1] = lines[l2 - 1][c2:]
        # 头部插入（行号自大而小，倒序插不失效）
        for lno, col, assign_lines in sorted(inserts, key=lambda x: -x[0]):
            lines[lno - 1:lno - 1] = assign_lines
        new_text = "\n".join(lines)
        try:
            _ast.parse(new_text)
        except SyntaxError as _se:
            hit["C15跳过_SyntaxError"] += 1
            print("WARN: C15 拼接后语法失败 %s: %s" % (rel, _se))
            continue
        texts[rel] = new_text
        changed += 1
        total += sum(len(a) for _l, _c, a in inserts)
    hit["C15局部化"] = total
    stat["C15"] = ["%d 模块 %d 别名" % (changed, total)]
    return texts


def _d1_seen_set(texts, stat, hit):
    """S3-D1：CoreGrid.getItemsInCells 的 O(n²) 列表判重改 seen-set + 顺序追加。

    原式 `if not item in itemsInCells and item.placed:`（列表成员线性扫描，
    受影响格 × 库内物品数平方级）；改 seen-set 判重、按发现顺序 append——
    输出逐元素相同（两条件合取、均无副作用，求值次序不影响结果集与顺序，
    规划 §189 已证安全）。精确锚点 + 出现计数校验，漂移即抛（防重生成
    静默跳过）。哈希键 = 物品实例（默认 id 哈希，跨场不持久）。
    """
    key = "gd_core/CoreGrid.gd"
    t = texts.get(key)
    if t is None:
        return texts
    old_decl = "\t\titemsInCells = []\n"
    old_guard = ("\t\t\t\tif not item in itemsInCells and item.placed:\n"
                 "\t\t\t\t\titemsInCells.append(item)\n")
    if t.count(old_decl) != 1 or t.count(old_guard) != 1:
        raise RuntimeError(
            "D1: CoreGrid.getItemsInCells 锚点计数异常（decl=%d guard=%d）——"
            "生成器文本已漂移，需人工对位" % (t.count(old_decl), t.count(old_guard)))
    t = t.replace(old_decl, old_decl + "\t\t_items_seen = {}\n", 1)
    t = t.replace(old_guard,
                  "\t\t\t\tif item.placed and item not in _items_seen:\n"
                  "\t\t\t\t\t_items_seen[item] = True\n"
                  "\t\t\t\t\titemsInCells.append(item)\n", 1)
    import ast as _ast
    _ast.parse(t)
    texts[key] = t
    hit["D1_seen_set"] = 1
    stat["D1"] = ["CoreGrid.getItemsInCells"]
    return texts


def _f5a_tick_inline(texts, stat, hit):
    """S5-F5a（有界切片）：tick 计时器链内联——physicsTick→tickTimersPass→
    _tickTimers 三层派发压平为循环体直发。

    审计（全树 grep）：tickTimersPass/_tickTimers 仅 CoreItem.gd 定义、零覆写；
    调用点闭合（tickTimersPass 仅 CoreCombat.physicsTick 1 处、_tickTimers 仅
    tickTimersPass 内 self+gem 两处）——虚派发静态等价。热路径省 ~50 万次
    方法调用/3场（253k tickTimersPass + 253k self._tickTimers）。
    方法本体保留（转写保真；热路径不再经过）。锚点计数校验，漂移即抛。
    """
    import ast as _ast
    ti = texts.get("gd_core/CoreItem.gd")
    if ti is None:
        raise RuntimeError("F5a: 缺 gd_core/CoreItem.gd 文本——texts 键名漂移")
    if True:
        old = ("\tdef tickTimersPass(self, delta):\n"
               "\t\tself._tickTimers(delta)\n"
               "\t\tfor gem in (self.gems if self.gems.__class__ is list else _iter(self.gems)):\n"
               "\t\t\tif gem != None:\n"
               "\t\t\t\tgem._tickTimers(delta)\n")
        if ti.count(old) != 1:
            raise RuntimeError(
                "F5a: tickTimersPass 锚点计数=%d（需 1）——生成器文本已漂移" % ti.count(old))
        new = ("\tdef tickTimersPass(self, delta):\n"
               "\t\tfor t in (self.timers if self.timers.__class__ is list else _iter(self.timers)):\n"
               "\t\t\tt.tick(delta)\n"
               "\t\tfor gem in (self.gems if self.gems.__class__ is list else _iter(self.gems)):\n"
               "\t\t\tif gem != None:\n"
               "\t\t\t\tfor t in (gem.timers if gem.timers.__class__ is list else _iter(gem.timers)):\n"
               "\t\t\t\t\tt.tick(delta)\n")
        ti = ti.replace(old, new, 1)
        _ast.parse(ti)
        # ★ 键必须是 .gd 源 rel——.py 键会生成重复条目，写入循环按插入序
        #   用陈旧快照覆盖 .gd 的变换结果（C17b 被清掉的真凶）
        texts["gd_core/CoreItem.gd"] = ti
    cc = texts.get("gd_core/CoreCombat.gd")
    if cc is None:
        raise RuntimeError("F5a: 缺 gd_core/CoreCombat.gd 文本——texts 键名漂移")
    if True:
        old = "\t\t\t\titem.tickTimersPass(delta)\n"
        if cc.count(old) != 1:
            raise RuntimeError(
                "F5a: CoreCombat tickTimersPass 调用点计数=%d（需 1）——文本已漂移"
                % cc.count(old))
        new = ("\t\t\t\tfor t in (item.timers if item.timers.__class__ is list else _iter__loc(item.timers)):\n"
               "\t\t\t\t\tt.tick(delta)\n"
               "\t\t\t\tfor gem in (item.gems if item.gems.__class__ is list else _iter__loc(item.gems)):\n"
               "\t\t\t\t\tif gem != None:\n"
               "\t\t\t\t\t\tfor t in (gem.timers if gem.timers.__class__ is list else _iter__loc(gem.timers)):\n"
               "\t\t\t\t\t\t\tt.tick(delta)\n")
        cc = cc.replace(old, new, 1)
        _ast.parse(cc)
        texts["gd_core/CoreCombat.gd"] = cc
    hit["F5a_tick_inline"] = 2
    stat["F5a"] = ["CoreItem.tickTimersPass 内联 + CoreCombat 调用点展开"]
    return texts


def _clamp_inline(texts, stat, hit):
    """S3-C17a：纯实参的 clamp(...) 调用点内联为三元链（81k 调用/3场，热路径
    26.5k 集中在 getSpeed）。

    展开式 = _rt.clamp 函数体原样：`lo if v < lo else (hi if v > hi else v)`。
    安全性：v 出现三次 → 实参 v 限纯表达式（无 Call 节点；属性链幂等，
    全树 property 仅 CoreBuff.current 纯读——审计）；lo/hi 各出现一次任意
    形态。NaN 语义与函数逐位一致（两比较均 False → 返回 v）。
    """
    import ast as _ast
    total = 0
    changed = 0
    for rel in list(texts):
        text = texts[rel]
        if "clamp(" not in text:
            continue
        try:
            tree = _ast.parse(text)
        except SyntaxError:
            continue
        reps = []
        for node in _ast.walk(tree):
            if not isinstance(node, _ast.Call):
                continue
            fu = node.func
            if not (isinstance(fu, _ast.Name) and fu.id == "clamp"
                    and len(node.args) == 3 and not node.keywords):
                continue
            v, lo, hi = node.args
            if any(isinstance(n, _ast.Call) for n in _ast.walk(v)):
                continue                       # v 三次出现 → 限纯表达式
            new = "(%s if %s < %s else (%s if %s > %s else %s))" % (
                _span_text(text, lo), _span_text(text, v), _span_text(text, lo),
                _span_text(text, hi), _span_text(text, v), _span_text(text, hi),
                _span_text(text, v))
            reps.append((node.lineno, node.col_offset,
                         node.end_lineno, node.end_col_offset, new))
        if not reps:
            continue
        reps.sort(key=lambda r: (-r[0], -r[1]))
        lines = text.split("\n")
        for l1, c1, l2, c2, new in reps:
            if l1 == l2:
                lines[l1 - 1] = lines[l1 - 1][:c1] + new + lines[l1 - 1][c2:]
            else:
                lines[l1 - 1] = lines[l1 - 1][:c1] + new
                for mid in range(l1, l2 - 1):
                    lines[mid] = ""
                lines[l2 - 1] = lines[l2 - 1][c2:]
            total += 1
        new_text = "\n".join(lines)
        try:
            _ast.parse(new_text)
        except SyntaxError:
            continue
        texts[rel] = new_text
        changed += 1
    hit["C17a_clamp内联"] = total
    stat["C17a"] = ["%d 模块 %d 处" % (changed, total)]
    return texts


def _hook_strip(texts, stat, hit):
    """S3-C17b：剥离热路径 no-op 表现钩子调用（hooks.showCooldown，71k/3场）。

    等价性论证：CoreHooks.showCooldown 是空方法（-> void, pass），gd 宿主侧
    同为空 GDScript 方法——两侧皆 no-op；实参 `1.0 - _div(...)` 纯数学+属性
    读（无副作用）；56 局基准探针（_BenchProbe）计数
    fatigue/stun/activation/damage，**不计数 showCooldown**（grep 实证）——
    剥离对全部验收探针零影响。仅剥热路径 1 处（冷却 per-item-per-tick）；
    冷路径（showCooldownSmooth/resetZ/Card.py）保留不动。
    精确锚点 + 计数校验，漂移即抛。
    """
    import ast as _ast
    key = "gd_core/CoreItem.gd"
    t = texts.get(key)
    if t is None:
        raise RuntimeError("C17b: 缺 gd_core/CoreItem.gd 文本——texts 键名漂移")
    old = ("\t\t\tself.ctx.hooks.showCooldown(self, 1.0 - _div(self.triggerTime, self.iterationCooldown))\n")
    if t.count(old) != 1:
        raise RuntimeError(
            "C17b: showCooldown 热调用锚点计数=%d（需 1）——文本已漂移" % t.count(old))
    t = t.replace(old, "", 1)
    _ast.parse(t)
    texts[key] = t
    hit["C17b_hook_strip"] = 1
    stat["C17b"] = ["CoreItem 冷却热路径 hooks.showCooldown 剥离"]
    return texts


# ── M2-1 空钩子调用点剥离 ─────────────────────────────────────────────
# 生成期**保留**（不剥）的钩子：全部来自已知探针覆写，来源逐一 grep 实证。
# 运行期由 simulator/gd_core_engine._make_probe_class 的装配断言兜底——若未来
# 出现未列入本表的新覆写，装配期直接抛 KernelError（响亮失败，绝不静默空转）。
_HOOK_KEEP = {
    # simulator/gd_core_engine.py::_LogMixin.logEvent —— 事件桥唯一出口，
    # 剥离=事件流静默变空（判定还全对，本项目最险的一类坑）。
    "logEvent",
    # tools/check_gd_core_engine.py::_make_bench_probe —— 56 局取证探针的
    # 计数面（activations/heal/damage/fatigue/stun），gd 宿主侧同口径对拍。
    "snapshotItemMetric",
    "spawnLabel_character",
    "playFatigueAnimation",
    "playStunAnimation",
}


def _noop_hook_methods(hooks_text):
    """从生成的 CoreHooks 模块文本收集「空体」方法名。

    空体 = 方法体仅由 `pass` / `return` / `return None` 构成；允许前缀
    `x = int(x)` 形态的冗余自转换（addMetric/snapshotItemMetric/
    snapshotGlobalStat 三处——纯局部变量，无任何可观察效果）。
    """
    import ast as _ast
    tree = _ast.parse(hooks_text)
    out = {}
    for cls in [n for n in tree.body if isinstance(n, _ast.ClassDef)]:
        for fn in [n for n in cls.body if isinstance(n, (_ast.FunctionDef,
                                                         _ast.AsyncFunctionDef))]:
            kind = None
            for st in fn.body:
                if isinstance(st, _ast.Pass):
                    kind = kind or "pass"
                    continue
                if isinstance(st, _ast.Return) and (
                        st.value is None
                        or (isinstance(st.value, _ast.Constant)
                            and st.value.value is None)):
                    kind = kind or "return"
                    continue
                # 冗余自转换：target 与实参同名、int(...) 直包
                if (isinstance(st, _ast.Assign) and len(st.targets) == 1
                        and isinstance(st.targets[0], _ast.Name)
                        and isinstance(st.value, _ast.Call)
                        and isinstance(st.value.func, _ast.Name)
                        and st.value.func.id == "int"
                        and len(st.value.args) == 1
                        and isinstance(st.value.args[0], _ast.Name)
                        and st.value.args[0].id == st.targets[0].id
                        and not st.value.keywords):
                    kind = "int_coerce"
                    continue
                kind = None
                break
            if kind:
                out[fn.name] = kind
    return out


def _hook_call_name(stmt):
    """stmt 是 `*.hooks.<name>(...)` 表达式语句时返回 <name>，否则 None。

    匹配面：Expr(Call(func=Attribute(value=Attribute(attr='hooks'), attr=NAME)))。
    接收者链不限定（self.ctx.hooks / self._ctx.hooks 全覆盖）；
    仅接受**纯表达式语句**形态——赋值/返回/实参位置的钩子调用一概不剥。
    """
    import ast as _ast
    if not isinstance(stmt, _ast.Expr):
        return None
    call = stmt.value
    if not isinstance(call, _ast.Call):
        return None
    fn = call.func
    if not (isinstance(fn, _ast.Attribute) and fn.attr != "hooks"
            and isinstance(fn.value, _ast.Attribute)
            and fn.value.attr == "hooks"):
        return None
    return fn.attr


def _char_bind(texts, stat, hit):
    """A-2（§C-2，2026-11-11）：同函数内 2+ 次 `.character()` 局部绑定。

    守卫（保守第一，判定不了不改）：
      ① 接收者恒为字面 self（obj.character() 不动——obj 可能是任意物品）；
      ② 函数体含 try → 整函数放弃；
      ③ 函数体含任何 self.X 属性赋值（= / +=）→ 放弃（可能间接改 gemMode）；
      ④ 函数体含 mutator 形调用（set*/add*/gain*/lose*/activate*/…）→ 放弃；
      ⑤ 排除名：character/setCharacter/_init/_init_fields/_process。
    命中：首次调用前插 `\t\t_ch = self.character()`，后续 `self.character()`
    改 `_ch`（限 self 接收者）。纯文本变换 + 逐文件 ast.parse 语法闸。
    """
    import ast as _ast
    import re as _re
    mutator = _re.compile(
        r'self\.(?:set|add|remove|clear|activate|deactivate|gain|lose|apply|take'
        r'|use|reset|consume|destroy|place|move)[A-Za-z_0-9]*\(')
    excluded = ('character', 'setCharacter', '_init', '_init_fields', '_process')
    pat_fn = _re.compile(
        r'(?P<head>\tdef (?P<name>[A-Za-z_][A-Za-z_0-9]*)\(self[^\n]*\n)'
        r'(?P<body>(?:\t\t.*\n)*)')
    total = 0
    for rel in sorted(texts):
        t2 = texts[rel]
        if '.character()' not in t2:
            continue
        n_file = 0

        def _sub(m):
            nonlocal n_file
            name, body = m.group('name'), m.group('body')
            if name in excluded or 'try:' in body:
                return m.group(0)
            calls = body.count('self.character()')
            if calls < 2:
                return m.group(0)
            if _re.search(r'self\.[A-Za-z_][A-Za-z_0-9]* *(\+=|=[^=])', body):
                return m.group(0)
            if mutator.search(body):
                return m.group(0)
            new_body = body.replace('self.character()', '_ch')
            head_indent = '\t\t'
            new_body = head_indent + '_ch = self.character()\n' + new_body
            n_file += 1
            return m.group('head') + new_body

        nt = pat_fn.sub(_sub, t2)
        if n_file:
            try:
                _ast.parse(nt)
            except SyntaxError:
                raise RuntimeError('A-2: %s 语法闸失败' % rel)
            texts[rel] = nt
            total += n_file
    if total:
        hit['A2_char_bind'] = total
        stat['A2'] = ['%d 个函数 character() 局部绑定' % total]
    return texts


def _typed_hot_loops(texts, stat, hit):
    """§4.2/D1（2026-11-13）：CoreCombat.physicsTick 双侧物品冷却循环 C 类型化。

    形态＝注解式（模块指令 `annotation_typing=True` + PEP 526 局部注解）：
      - 纯 py 臂零开销：CPython 对函数内局部注解**不求值不存表**，.py 保持
        可被 GD_PURE_PY 臂源码导入（无 cimport / 无 cython 模块依赖）；
      - `item: CoreItem` → `_cooldown_active`（bint）/`triggerTime`（double）
        槽位 C 读写、`getSpeed()`（cpdef double）C 直调；每次迭代付一次
        isinstance 收窄（参战物品全在 CoreItem 继承链上，§4.2 风险 1 已确认；
        违反时 TypeError 响亮失败，不静默）；
      - `character()` **虚派发保留**（§2.1 红线 ⛔ 内联）：每 item-tick 仍恰好
        调用一次，仅对返回值变量类型化 → `stunnedDuration` 走 C double 槽读。
        帧内调用集合与调用次数不变（无 §2.1 事件驱动调度问题）。
    微基准锚：tools/typed_loop_probe（typed 0.008 vs untyped 0.272 µs/item-tick，
    仅属性访问段 35.8x；整场预期 −8~12%，判据 mean_ms ≥3%）。
    """
    import ast as _ast
    key = "gd_core/CoreCombat.gd"
    t = texts.get(key)
    if t is None or "_cooldown_active" not in t:
        return texts

    # 模块头：指令 + 姊妹模块导入（相对导入，与 Item.py 的基类导入同约定）
    old_head = ("# 自动生成，勿手改。生成器：tools/gd_to_py.py\n"
                "\n"
                "from .._rt import (  # noqa: F401\n")
    new_head = ("# 自动生成，勿手改。生成器：tools/gd_to_py.py\n"
                "\n"
                "# cython: annotation_typing=True\n"
                "from .CoreItem import CoreItem  # noqa: F401  D1 注解式类型化（纯 py 零开销）\n"
                "from .CoreCharacter import CoreCharacter  # noqa: F401  D1 同上\n"
                "\n"
                "from .._rt import (  # noqa: F401\n")
    if t.count(old_head) != 1:
        raise RuntimeError("D1T: CoreCombat 模块头锚点漂移（count=%d）"
                           % t.count(old_head))
    t = t.replace(old_head, new_head)

    n_loops = 0
    for side in ("opponent", "player"):
        old = (
            "\t\tfor item in _iter__loc(self.%s.inventory.getItems()):\n"
            "\t\t\tif item._cooldown_active:\n"
            "\t\t\t\tif not (item.character().stunnedDuration > 0):\n"
            "\t\t\t\t\titem.triggerTime -= delta * item.getSpeed()\n"
            "\t\t\t\t\tif item.triggerTime <= 0:\n"
            "\t\t\t\t\t\titem.trigger()\n" % side)
        new = (
            "\t\t# D1（§4.2）：循环变量 C 类型化——注解式，纯 py 臂零开销；\n"
            "\t\t# character() 虚派发保留（每 item-tick 恰一次），仅类型化返回值。\n"
            "\t\titem: CoreItem\n"
            "\t\tfor item in _iter__loc(self.%s.inventory.getItems()):\n"
            "\t\t\tif item._cooldown_active:\n"
            "\t\t\t\tch_: CoreCharacter = item.character()\n"
            "\t\t\t\tif not (ch_.stunnedDuration > 0):\n"
            "\t\t\t\t\titem.triggerTime -= delta * item.getSpeed()\n"
            "\t\t\t\t\tif item.triggerTime <= 0:\n"
            "\t\t\t\t\t\titem.trigger()\n" % side)
        if t.count(old) != 1:
            raise RuntimeError("D1T: %s 冷却循环锚点漂移（count=%d）"
                               % (side, t.count(old)))
        t = t.replace(old, new)
        n_loops += 1

    try:
        _ast.parse(t)
    except SyntaxError as e:
        raise RuntimeError("D1T: CoreCombat 语法闸失败: %s" % e)
    texts[key] = t
    hit['D1T_typed_loops'] = n_loops
    stat['D1T'] = ['physicsTick 双侧冷却循环类型化（item/ch_ 注解式）']
    return texts


def _strip_noop_hooks(texts, stat, hit):
    """M2-1：剥离空钩子（CoreHooks 全 pass 方法）的全部调用点。

    等价性论证（三层）：
    ① 方法体空（含冗余 int 自转换）⇒ 调用无可观察效果；实参表达式里的
       属性链/纯函数求值同样无副作用——CoreHooks.gd 头注已证「钩子不参与
       判定（全部纯尾部副作用调用）」。
    ② 语句级删除 + 块安全：调用点是纯 Expr 语句（grep 实证无赋值/返回形），
       块内全部语句可删时留 1 个 `pass` 占位（if/for/while/try 体语法不破；
       while 体全删不构成新死循环——空钩子本就不改循环条件，原代码同结局）。
    ③ 探针安全：_HOOK_KEEP 显式保留全部已知探针覆写；装配期断言
       （simulator/gd_core_engine._make_probe_class）对未知覆写响亮失败。
    剥离清单发射进 _bootstrap.STRIPPED_HOOKS，供装配断言与审计工具读取。
    """
    import ast as _ast
    hooks_key = "gd_core/CoreHooks.gd"
    hooks_text = texts.get(hooks_key)
    if hooks_text is None:
        raise RuntimeError("M2: 缺 gd_core/CoreHooks.gd 文本——texts 键名漂移")
    noop = _noop_hook_methods(hooks_text)
    unexpected_keep = sorted(set(_HOOK_KEEP) - set(noop))
    if unexpected_keep:
        raise RuntimeError(
            "M2: _HOOK_KEEP 含非空体方法 %s——探针覆写的方法体已变，"
            "请重审剥离面" % unexpected_keep)
    strippable = {n for n in noop if n not in _HOOK_KEEP}
    if not strippable:
        stat["M2"] = ["无空体方法可剥（CoreHooks 全保留）"]
        return texts

    total = 0
    per_file = {}
    for rel in sorted(texts):
        t = texts[rel]
        if ".hooks." not in t:
            continue
        tree = _ast.parse(t)
        # (start, end, pass_at_start) 行区间清单；逆序套用以保持行号有效
        spans = []
        for node in _ast.walk(tree):
            for field in ("body", "orelse", "finalbody"):
                lst = getattr(node, field, None)
                if not (isinstance(lst, list) and lst):
                    continue
                marks = [(_hook_call_name(st), st) for st in lst]
                dels = [(nm, st) for nm, st in marks
                        if nm is not None and nm in strippable]
                if not dels:
                    continue
                whole = len(dels) == len(lst)
                for i, (nm, st) in enumerate(dels):
                    spans.append((st.lineno, st.end_lineno,
                                  whole and i == 0))
        if not spans:
            continue
        lines = t.splitlines(keepends=True)
        for start, end, as_pass in sorted(spans, reverse=True):
            if as_pass:
                indent = re.match(r"[ \t]*", lines[start - 1]).group(0)
                lines[start - 1] = indent + "pass\n"
                if end > start:
                    del lines[start:end]
            else:
                del lines[start - 1:end]
        nt = "".join(lines)
        _ast.parse(nt)          # 语法闸：漂移即抛
        texts[rel] = nt
        per_file[rel] = len(spans)
        total += len(spans)

    if total == 0:
        raise RuntimeError("M2: strippable=%d 个方法但零调用点命中——"
                           "匹配面或文本漂移" % len(strippable))
    hit["M2_noop_hooks"] = total
    stat["M2"] = ["剥离 %d 个调用点 / %d 个空方法（保留 %d 个探针覆写）"
                  % (total, len(strippable), len(_HOOK_KEEP))]
    stat["M2_stripped_hooks"] = sorted(strippable)
    stat["M2_per_file"] = ["%s:%d" % (k, v) for k, v in
                           sorted(per_file.items(), key=lambda kv: -kv[1])]
    return texts


def _d2_adjcells_seen(texts, stat, hit):
    """S4-D2（有界实现）：CoreGrid.getAdjacentCells 邻接格判重 seen-set 化。

    原式双重线性判重（`not neighbor in cells` × O(cells) + `not neighbor in
    adjacentCells` × O(增长表)）→ 两 set 一次构建、O(1) 成员查询。输出 =
    发现顺序 append（逐元素相同——getAdjacentItems→getItemsInCells 消费链
    保序，getNeighborItemsAndGems 邻接序不变，规划 §189 安全口径）。
    精确锚点 + 计数校验，漂移即抛。
    """
    import ast as _ast
    key = "gd_core/CoreGrid.gd"
    t = texts.get(key)
    if t is None:
        raise RuntimeError("D2: 缺 gd_core/CoreGrid.gd 文本——texts 键名漂移")
    old = ("\t\tadjacentCells = []\n"
           "\t\tfor cell in (cells if cells.__class__ is list else _iter__loc(cells)):\n"
           "\t\t\tfor offset in _iter__loc([Vector2.RIGHT, Vector2.LEFT, Vector2.UP, Vector2.DOWN]):\n"
           "\t\t\t\tneighbor = cell + offset\n"
           "\n"
           "\t\t\t\tif (not neighbor in cells and \n"
           "\t\t\t\t\tnot neighbor in adjacentCells):\n"
           "\t\t\t\t\tadjacentCells.append(neighbor)\n")
    if t.count(old) != 1:
        raise RuntimeError(
            "D2: getAdjacentCells 锚点计数=%d（需 1）——文本已漂移" % t.count(old))
    new = ("\t\tadjacentCells = []\n"
           "\t\t_cells_seen = set(cells)\n"
           "\t\t_adj_seen = set()\n"
           "\t\tfor cell in (cells if cells.__class__ is list else _iter__loc(cells)):\n"
           "\t\t\tfor offset in _iter__loc([Vector2.RIGHT, Vector2.LEFT, Vector2.UP, Vector2.DOWN]):\n"
           "\t\t\t\tneighbor = cell + offset\n"
           "\n"
           "\t\t\t\tif (neighbor not in _cells_seen and \n"
           "\t\t\t\t\tneighbor not in _adj_seen):\n"
           "\t\t\t\t\t_adj_seen.add(neighbor)\n"
           "\t\t\t\t\tadjacentCells.append(neighbor)\n")
    t = t.replace(old, new, 1)
    _ast.parse(t)
    texts[key] = t
    hit["D2_adjcells_seen"] = 1
    stat["D2"] = ["CoreGrid.getAdjacentCells seen-set 化"]
    return texts


def _f5b_physick_inline(texts, stat, hit):
    """S5-F5b（F5 第二切片）：CoreItem.physicsTick 在 CoreCombat 两调用点展开。

    审计：physicsTick 全树仅 CoreItem.gd 定义（零覆写）；调用点仅
    CoreCombat.physicsTick 双侧循环 2 处；体=冷却门+眩晕门+递减+触发
    （isStunned 零覆写单行体已审计）。展开后 25.3 万次方法调用/3场清零
    （其中 ~70% 是非冷却物品的「调用+属性+早退」纯开销）。
    虚调用保留：character()（Gem 有覆写）、getSpeed()、trigger() 原样转写。
    精确锚点 + 计数校验，漂移即抛。
    """
    import ast as _ast
    cc = texts.get("gd_core/CoreCombat.gd")
    if cc is None:
        raise RuntimeError("F5b: 缺 gd_core/CoreCombat.gd 文本——texts 键名漂移")
    old = "\t\t\titem.physicsTick(delta)\n"
    if cc.count(old) != 2:
        raise RuntimeError(
            "F5b: physicsTick 调用点计数=%d（需 2）——文本已漂移" % cc.count(old))
    new = ("\t\t\tif item._cooldown_active:\n"
           "\t\t\t\tif not (item.character().stunnedDuration > 0):\n"
           "\t\t\t\t\titem.triggerTime -= delta * item.getSpeed()\n"
           "\t\t\t\t\tif item.triggerTime <= 0:\n"
           "\t\t\t\t\t\titem.trigger()\n")
    cc = cc.replace(old, new, 2)
    _ast.parse(cc)
    texts["gd_core/CoreCombat.gd"] = cc
    hit["F5b_physick_inline"] = 2
    stat["F5b"] = ["CoreItem.physicsTick 双调用点展开"]
    return texts


def _cy_round_alias(texts, stat, hit):
    """F1-Cython 伴生趟：产物内自由 `round(` 调用改名为 gd_round 别名。

    动机：`round` 是 Cython 内建优化名——实参推断为 C double 时绕过模块
    全局 shim（GDScript 远离零取整），伤害取整语义漂移（run1514_r18
    gd=7/py=6 实证）。gd_round = _rt 同函数别名（非内建名 → Cython 走
    运行期全局解析 → shim 保留）。CPython 腿同别名零变化。
    负向后顾排除 `.round(`（Vector2 方法调用，运行期属性协议本就安全）。
    """
    import re as _re
    pat = _re.compile(r"(?<![.\w])round\(")
    total = 0
    for rel in list(texts):
        t = texts[rel]
        n = len(pat.findall(t))
        if not n:
            continue
        texts[rel] = pat.sub("gd_round(", t)
        total += n
    hit["cy_round_alias"] = total
    stat["cy_round"] = ["%d 处改名" % total]
    return texts


# ── M1-2：pxd 槽位声明发射（白名单起步）──────────────────────────────
# 槽位化前提（_m12_probe 实测，2026-11-10）：
#   · 伴随 .pxd 声明 cdef class（.py 保持普通 class 体）→ 实例无 __dict__，
#     未声明属性赋值 AttributeError（编译态强制）；基类链必须全部 cdef
#     （GodotObject 已在批A 转 cdef，见 _rt.pxd）。
#   · 普通 Python 子类继承 cdef 基类：自带 __dict__，实例影子/light_log
#     机制不受影响；探针类（引擎侧 plain）同理。
#   · cdef 体里允许运行时调用类属性（EnumDict 枚举实测合法）。
# 白名单外的类保持 plain（实例有 __dict__，行为不变）。扩白名单前必须：
#   ① 引擎/工具侧对该类实例无未声明属性赋值（grep gd_core_engine.py）；
#   ② 类体无方法名影子赋值；③ 过 seed 双态 + 60 场 + REG9。
_PXD_WHITELIST = {
    "gd_core/CoreEvent.gd",
    # ── M1-2b 批（2026-11-10）：数据/计时类 ──
    "gd_core/CoreDamageResult.gd",
    "gd_core/CoreDamageSource.gd",
    "gd_core/CoreTimer.gd",
    "gd_core/CoreRng.gd",
    "gd_core/CoreBuff.gd",
    # ── M1-2c 批：热大类（M1-3 热 8 的 gd_core 树部分） ──
    "gd_core/CoreGrid.gd",
    "gd_core/CoreEventBus.gd",      # +引擎补充槽 connect_journal_enabled
    "gd_core/CoreCombat.gd",
    "gd_core/CoreContext.gd",       # +引擎补充槽 ×7（装配期动态赋值面）
    "gd_core/CoreCharacter.gd",
    "gd_core/CoreItem.gd",
    # ── L1 试点（§11.3，2026-11-11）：items 树基类是 _R.C() 运行时解析——
    #    cdef 类要求基类编译期可知，白名单 items 模块改发**直接导入**基类
    #    （extends 拓扑序保证基模块先导入；_R.reg 注册不受影响）。
    #    试点链：Item_2(适配层) → Card_2 → AceofSpades_2，全绿再扩 141。
    "gd_core/Item.gd",                     # 适配层 A（Exclusive 链根）
}

# 白名单判定（含前缀规则——L1 全量扩批时把 gd_core_items/ 整树纳入）
def _is_pxd_whitelisted(rel):
    if rel in _PXD_WHITELIST:
        return True
    return rel.startswith("gd_core_items/")   # L1 全量：items 整树槽位化

# 引擎侧（simulator/gd_core_engine.py）对内核实例的动态赋值面——cdef 槽化
# 后必须以补充槽声明，否则编译态 AttributeError。逐项 grep 实证
# （gd_core_engine.py:945-1041）；生成器收集器只看生成文本，看不见这些。
_PXD_EXTRA_SLOTS = {
    "gd_core/CoreContext.gd": {
        # GDCoreEngine.__init__ 装配期逐个赋值
        "label_rng_enabled",          # 948 标签视觉抽开关（round19）
        "below_master",               # 956 np24 对手冷却掷面
        "custom_health_multiplier",   # 959 np51 存档健康倍率
        "keyed_stop_clears_seen",     # 961 np43 键控
        "keyed_cleanse_biggest_first",  # 962 np43 键控
        "deferred_flush_enabled",     # 966 np24 deferred 冲刷
        "eb_relay_mirrored",          # 970 EngineerBox 接力死亡镜像
    },
    "gd_core/CoreEventBus.gd": {
        "connect_journal_enabled",    # 945 np21-R5 连接台账（键控默认关）
    },
}


def _collect_instance_slots(py_text):
    """从生成的 .py 文本收集 [(类名, 基类形态, 实例属性槽集合), ...]（声明序）。

    基类形态三分类（L1：items 树基类是 `_R.C("res://...")` 运行时解析）：
      ("godot", None)   —— Name 基类 GodotObject
      ("call", res_str) —— `_R.C("res://...")` 单常量实参（跨文件基类）
      ("plain", None)   —— 其余（多基类/关键字/未知 Name/怪形态）→ 保持 plain
    槽集 = 类方法体内全部 `self.X =` / `self.X +=` 赋值目标，剔除：类体级
    赋值、方法名（影子赋值即违规，抛错）、property 名（走 setter）。
    """
    import ast as _ast
    tree = _ast.parse(py_text)
    classes = [n for n in tree.body if isinstance(n, _ast.ClassDef)]
    if not classes:
        raise RuntimeError("M1-2: 模块零顶层类")
    out = []
    for cls in classes:
        base_kind, base_ref = "plain", None
        if len(cls.bases) == 1 and not cls.keywords:
            b = cls.bases[0]
            if isinstance(b, _ast.Name):
                if b.id == "GodotObject":
                    base_kind, base_ref = "godot", None
                else:
                    base_kind, base_ref = "plain", None   # 本地别名基类（罕见）
            elif (isinstance(b, _ast.Call)
                  and ((isinstance(b.func, _ast.Name) and b.func.id == "_R.C")
                       or (isinstance(b.func, _ast.Attribute)
                           and b.func.attr == "C"
                           and isinstance(b.func.value, _ast.Name)
                           and b.func.value.id == "_R"))
                  and len(b.args) == 1
                  and isinstance(b.args[0], _ast.Constant)
                  and isinstance(b.args[0].value, str)
                  and not b.keywords):
                base_kind, base_ref = "call", b.args[0].value
        body_class_attrs = set()
        for st in cls.body:
            if isinstance(st, (_ast.Assign, _ast.AnnAssign)):
                targets = st.targets if isinstance(st, _ast.Assign) else [st.target]
                for t in targets:
                    if isinstance(t, _ast.Name):
                        body_class_attrs.add(t.id)
        methods = {n.name for n in cls.body
                   if isinstance(n, (_ast.FunctionDef, _ast.AsyncFunctionDef))}
        # property 名不是槽：`self.id = v` 走 setter（cdef class 支持 property，
        # setter 体内的 self._id 赋值才是槽）。CoreEvent.id = 属性 + _id 后备。
        # @property 是 Name 装饰器；@x.setter 形态的 Attribute 装饰器一并在内。
        props = {n.name for n in cls.body if isinstance(n, _ast.FunctionDef)
                 and any((isinstance(d, _ast.Name) and d.id == "property")
                         or (isinstance(d, _ast.Attribute) and d.attr == "property")
                         for d in n.decorator_list)}
        slots = set()
        for fn in [n for n in cls.body if isinstance(n, _ast.FunctionDef)]:
            for node in _ast.walk(fn):
                if isinstance(node, _ast.Assign):
                    for t in node.targets:
                        if isinstance(t, _ast.Attribute) \
                                and isinstance(t.value, _ast.Name) \
                                and t.value.id == "self":
                            slots.add(t.attr)
        shadow = (slots - props) & methods
        if shadow:
            raise RuntimeError("M1-2: %s 实例属性与方法同名影子 %s——产物形态漂移"
                               % (cls.name, sorted(shadow)))
        slots -= body_class_attrs
        slots -= props
        out.append((cls.name, base_kind, base_ref, slots, props))
    return out


# ── L1 cdef 可行性规划（文本后置两遍式）────────────────────────────────
# 流程：transform 产出文本（类语句保持 _R.C 原形态）→ 本函数从文本收集
# 类/基类/槽 + 沿 extends DAG 传播 cdef 可行性 → 改写可 cdef 类的基类为
# 直接导入别名 → 发 pxd（仅可 cdef 类）。
# 可行性规则：godot 基类→可；call 基类→目标模块在白名单且其主类可才可；
# 其余形态→不可（连带派生类不可）。
_CDEF_PLAN = {}
_SLOTSETS = {}          # (rel, cls) -> (own_final, inherited_union, inherited_props)


def _final_slots(rel, cls_name):
    """该类最终 own 槽集（剔除祖先已声明【槽与 property】名）+ 祖先并集。

    property 必须一并剔除：派生槽会遮蔽基 property，令基模块编译态直读
    （self.x on typed base）与派生槽写分裂成两个存储（CTNONE 实证）。"""
    key = (rel, cls_name)
    if key in _SLOTSETS:
        return _SLOTSETS[key]
    e = next((x for x in (_CDEF_PLAN.get(rel) or []) if x[0] == cls_name), None)
    if e is None or not e[4]:
        _SLOTSETS[key] = (set(), set(), set())
        return _SLOTSETS[key]
    inherited = set()
    inherited_props = set()
    if e[5] is not None:
        base_rel, base_cls = e[5]
        own_b, union_b, props_b = _final_slots(base_rel, base_cls)
        inherited |= union_b
        inherited_props |= props_b
    # 祖先本类 property 名（跨模块取基类条目）
    bprops = set()
    if e[5] is not None:
        base_rel, base_cls = e[5]
        be = next((x for x in (_CDEF_PLAN.get(base_rel) or [])
                   if x[0] == base_cls), None)
        if be is not None:
            bprops = be[6]
    own = set(e[3]) - inherited - inherited_props - bprops
    _SLOTSETS[key] = (own, own | inherited, inherited_props | bprops)
    return _SLOTSETS[key]


def _plan_and_rewrite_bases(texts, files_by_rel, by_path, stat, hit):
    """返回 {py_rel: pxd_text}；就地改写 texts 中可 cdef 类的基类语句。"""
    _CDEF_PLAN.clear()
    memo = {}

    for rel in sorted(r for r in files_by_rel if _is_pxd_whitelisted(r)):
        t = texts.get(rel)
        if t is None:
            continue
        try:
            recs = _collect_instance_slots(t)
        except Exception as e:  # noqa: BLE001 —— 形态漂移：整模块保持 plain
            stat.setdefault("L1_保留plain", []).append("%s: %s" % (rel, e))
            _CDEF_PLAN[rel] = []
            continue
        _CDEF_PLAN[rel] = [list(r[:4]) + [None, None, r[4]] for r in recs]
        # 记录结构：[0]名 [1]kind [2]ref [3]slots [4]cdef_able [5](base_rel,base_cls)
        #           [6]本类 property 名集（供派生类槽排除——防遮蔽基 property）

    def _able(rel, cls_name):
        key = (rel, cls_name)
        if key in memo:
            return memo[key]
        memo[key] = False                       # 环路防御（extends 为 DAG）
        for e in (_CDEF_PLAN.get(rel) or []):
            if e[0] != cls_name:
                continue
            kind, ref = e[1], e[2]
            if kind == "godot":
                ok = True
            elif kind == "call":
                bf = by_path.get(ref)
                ok = (bf is not None and _is_pxd_whitelisted(bf.rel)
                      and _able(bf.rel, bf.py_class))
                if ok:
                    e[5] = (bf.rel, bf.py_class)
            else:
                ok = False
            memo[key] = ok
            e[4] = ok
            return ok
        return False

    n_rewrite = 0
    pxds = {}
    for rel in sorted(_CDEF_PLAN):
        entries = _CDEF_PLAN[rel]
        if not entries:
            continue
        f = files_by_rel[rel]
        _able(rel, f.py_class)
        for e in entries:
            _able(rel, e[0])
        t = texts[rel]
        depth = len(rel[:-3].split("/")) - 1
        dots = "." * (depth + 1)
        inserts = []
        for e in entries:
            if not e[4]:
                continue
            cls_name = e[0]
            if e[5] is not None:
                base_rel, base_cls = e[5]
                alias = "_base_cls_%s" % cls_name
                bpkg = base_rel[:-3].split("/")        # 全段含 stem=模块路径
                fpkg = rel[:-3].split("/")[:-1]        # 包段（剔 stem）
                common = 0
                while common < min(len(bpkg), len(fpkg)) \
                        and bpkg[common] == fpkg[common]:
                    common += 1
                rdots = "." * (len(fpkg) - common + 1)
                suffix = ".".join(bpkg[common:])
                # ★ 条件补绑（GodotObject 同款机制）：编译态 pxd 以
                #   `cimport <Base> as <alias>` 预绑 C 名（globals 已含），
                #   运行态重复绑定即 "Assignment to non-lvalue"——故 .py 侧
                #   只在 globals 缺名时导入；纯 py 态无 pxd，恒绑定。
                imports = ("if \"%s\" not in globals():\n"
                           "\tfrom %s%s import %s as %s"
                           % (alias, rdots, suffix, base_cls, alias))
                old_stmt = "class %s(_R.C(\"%s\")):" % (cls_name, e[2])
                if t.count(old_stmt) != 1:
                    raise RuntimeError(
                        "L1: %s 基类语句锚点漂移（%r）" % (cls_name, old_stmt))
                t = t.replace(old_stmt, "class %s(%s):" % (cls_name, alias))
                inserts.append(imports)
                n_rewrite += 1
        if inserts:
            anchor = "from %s import _registry as _R\n" % dots
            idx = t.index(anchor) + len(anchor)
            t = t[:idx] + "".join(ln + "\n" for ln in inserts) + "\n" + t[idx:]
            texts[rel] = t
        # pxd：仅可 cdef 类；own 槽剔除祖先已声明名（防派生槽遮蔽基槽劈 ABI）
        for e in entries:
            if e[4]:
                _final_slots(rel, e[0])
        pxds[py_file_rel(rel)] = _render_pxd(entries, module_py_rel=py_file_rel(rel),
                                             gd_rel=rel)
    hit["L1_base_rewrite"] = n_rewrite
    return pxds


def _render_pxd(entries, module_py_rel, gd_rel):
    _render_ctx = (gd_rel, gd_rel)   # (有效 rel, gd_rel)——final 槽查询键
    lines = [
        "# -*- coding: utf-8 -*-",
        "# 自动生成，勿手改。生成器：tools/gd_to_py.py（M1-2/L1 实例槽位声明）",
        "#",
        "# 仅收录本模块「可 cdef」的类（基类链全 cdef）；keep-plain 类（运行时",
        "# 基类/辅助形态）不在此声明，.py 里保持 plain class——同模块混布合法。",
        "# 槽位 object 型起步；引擎补充槽见 tools/gd_to_py.py _PXD_EXTRA_SLOTS。",
        "",
    ]
    n_slots = 0
    for e in entries:
        if not e[4]:
            continue
        cls_name, base_cls = e[0], e[5]
        if base_cls is None:
            lines.append("from gd_core_py._rt cimport GodotObject\n")
            base_expr = "GodotObject"
        else:
            base_rel, base_py = base_cls
            alias = "_base_cls_%s" % cls_name
            lines.append("from gd_core_py.%s cimport %s as %s\n"
                         % (base_rel[:-3].replace("/", "."), base_py, alias))
            base_expr = alias
        use, _u1, _u2 = _final_slots(_render_ctx[0], cls_name)
        is_stem = cls_name == _render_ctx[1].rsplit("/", 1)[-1][:-3]
        if is_stem:
            use |= _PXD_EXTRA_SLOTS.get(_render_ctx[1], set())
        lines.append("\ncdef class %s(%s):\n" % (cls_name, base_expr))
        if use:
            l3 = _l3_numeric_types(_render_ctx[1])
            extra_names = (_PXD_EXTRA_SLOTS.get(_render_ctx[1], set())
                           if is_stem else set())
            for name in sorted(use):
                ctype = 'object'
                if name not in extra_names and (gd_rel, name) not in _L3_BLOCKLIST:
                    ctype = l3.get(name, 'object')
                if ctype == 'object':
                    lines.append("    cdef public object %s" % name)
                else:
                    lines.append("    cdef public %s %s" % (ctype, name))
        else:
            lines.append("    pass")   # cdef 类体不允许为空（零槽全继承类同样）
        n_slots += len(use)
        if is_stem:
            for name, ret, pdecl in _L2_CPDEF.get(_render_ctx[1], []):
                args = ", ".join("%s %s" % (ct, pn) for pn, ct in pdecl)
                lines.append("    cpdef %s %s(self%s)"
                             % (_L2_TYPE[ret], name,
                                (", " + args) if args else ""))
        lines.append("\n")
    return "\n".join(lines)


def _strip_signal_attrs(texts, stat, hit):
    """白名单模块剥离类体级 `X = Signal("...")` 属性（GDScript `signal X` 转写形）。

    依据：全树零消费（grep emit/connect/type 级访问 0 命中；GodotObject.emit_signal
    走 _gd_conns 连接表，不读 Signal 类属性）。cdef 类的非描述符类型属性对实例
    只读，会阻断同名实例槽（var hovered 与 signal hovered 同名共存的原版语义 =
    实例读 var）——剥离后同名实例槽接管，语义保持。"""
    import re as _re
    pat = _re.compile(r'^\t[A-Za-z_][A-Za-z_0-9]* = Signal\("[^"]*"\)\n', _re.M)
    total = 0
    for rel in sorted(r for r in texts if _is_pxd_whitelisted(r)):
        t2 = texts[rel]
        n = len(pat.findall(t2))
        if n:
            texts[rel] = pat.sub('', t2)
            total += n
    if total:
        hit["L1_signal_strip"] = total
        stat["L1_signal_strip"] = ["%d 处 Signal 类属性剥离（装饰性，零消费）" % total]
    return texts


def _hoist_referenced_classattrs(texts, stat, hit):
    """白名单模块：跨类裸引用的类体属性 → 模块级别名（TriggerType 实证）。

    扫描每个白名单模块：收集各类**类体级**赋值名（含 EnumDict 枚举/嵌套类
    别名）；扫描全部方法体的裸 Name 引用；`引用名 ∈ 类体属性名 且 非模块级
    已有名` → 模块尾补 `<名> = <属主类>.<名>`。局部名遮蔽不受影响（局部
    优先）；plain 模式的潜伏 NameError 顺带修复。"""
    import ast as _ast
    total = 0
    for rel in sorted(r for r in texts if _is_pxd_whitelisted(r)):
        t2 = texts[rel]
        try:
            tree = _ast.parse(t2)
        except SyntaxError:
            continue
        module_names = {n.targets[0].id for n in tree.body
                        if isinstance(n, _ast.Assign)
                        and isinstance(n.targets[0], _ast.Name)}
        module_names |= {n.name for n in tree.body
                         if isinstance(n, _ast.ClassDef)}   # cdef 类名不可再赋值
        class_attrs = {}          # 名 -> 首个属主类名
        for cls in [n for n in tree.body if isinstance(n, _ast.ClassDef)]:
            for st in cls.body:
                if isinstance(st, _ast.Assign):
                    for tg in st.targets:
                        if isinstance(tg, _ast.Name) \
                                and tg.id not in class_attrs:
                            class_attrs[tg.id] = cls.name
        if not class_attrs:
            continue
        referenced = set()
        for cls in [n for n in tree.body if isinstance(n, _ast.ClassDef)]:
            for fn_ in [n for n in cls.body
                        if isinstance(n, _ast.FunctionDef)]:
                for node in _ast.walk(fn_):
                    if isinstance(node, _ast.Name) \
                            and isinstance(node.ctx, _ast.Load) \
                            and node.id in class_attrs \
                            and node.id not in module_names:
                        referenced.add(node.id)
        need = sorted(referenced)
        if not need:
            continue
        alias_lines = "".join(
            "%s = %s.%s\n" % (nm, class_attrs[nm], nm) for nm in need)
        texts[rel] = t2 + "\n\n# ── L1 跨类裸引用类属性提升（生成器发射）──\n" + alias_lines
        total += len(need)
    if total:
        hit["L1_classattr_alias"] = total
        stat["L1_classattr_alias"] = ["%d 处类体属性模块级别名（跨类裸引用）" % total]
    return texts


_L2_CPDEF = {}          # gd_rel -> [decl lines]
_L2_TYPE = {"bool": "bint", "int": "long long", "float": "double"}  # §11.4 链 1: getSpeed 等访问器 cpdef double
_L2_SIG_RE = None


def _plan_l2_cpdef(files_by_rel, stat, hit):
    """扫描白名单 .gd 源的函数注解，产出主类 cpdef 声明（全局签名兼容预检）。

    兼容规则：方法名在全树任何出现点（含未注解/Variant 返回形态）签名不同
    → 整名排除。覆盖重写经 vtable 正确派发（cpdef 设计目标）；本批方法几乎
    全部经未类型化 object 引用调用（Python 属性派发，天然 override-aware）。"""
    import os as _os
    import re as _re
    import keyword as _keyword
    global _L2_SIG_RE
    if _L2_SIG_RE is None:
        _L2_SIG_RE = _re.compile(
            r'^func ([A-Za-z_][A-Za-z_0-9]*)\(([^)]*)\)(?: *-> *([A-Za-z_][A-Za-z_0-9]*))?:',
            _re.M)
    sig_by_name = {}          # name -> set((ptypes_tuple, ret_or_None))
    # §11.4 止损:闸门红揪出「某路径 return None」的函数名 → _L2_BLOCKLIST
    # (文件头常量)即退回 def;不要 try/except 兜。
    _l2_block = _L2_BLOCKLIST
    per_module = {}           # rel -> [(name, ret, [(pname, ctype)])]
    for rel in sorted(r for r in files_by_rel if _is_pxd_whitelisted(r)):
        src_path = _os.path.join(_os.path.dirname(_os.path.dirname(
            _os.path.abspath(__file__))), rel)
        try:
            src = io.open(src_path, encoding='utf-8').read()
        except OSError:
            continue
        decls = []
        for mm in _L2_SIG_RE.finditer(src):
            name, params, ret = mm.group(1), mm.group(2), mm.group(3)
            pl = [x.strip() for x in params.split(',') if x.strip()]
            ptypes, pdecl, ok = [], [], True
            for pp in pl:
                pm = _re.match(r'^([A-Za-z_][A-Za-z_0-9]*)(?:: *(bool|int|float))? *(=.*)?$', pp)
                if pm is None:
                    ok = False
                    break
                pname, pty, dflt = pm.group(1), pm.group(2), pm.group(3)
                ptypes.append(pty)                      # None=未注解
                # 本批只收 bool/int 形参（float 面、未注解、带默认、关键字名
                # 一律跳过整个方法——flipPercent(self, from, to) 实证）
                if dflt is not None or pty not in _L2_TYPE \
                        or _keyword.iskeyword(pname):
                    ok = False
                    break
                pdecl.append((pname, _L2_TYPE[pty]))
            if not ok:
                continue                                 # 本形态不可声明
            sig_by_name.setdefault(name, set()).add(
                (tuple(ptypes), ret))
            if ret in _L2_TYPE and name not in _L2_BLOCKLIST:
                per_module.setdefault(rel, []).append(
                    (name, ret, pdecl))
        # 逐模块落声明（兼容预检后过滤）
        _L2_CPDEF[rel] = per_module.get(rel, [])
    excluded = set()
    for name, sigs in sig_by_name.items():
        if len(sigs) > 1:
            excluded.add(name)
    n = 0
    for rel, decls in list(_L2_CPDEF.items()):
        kept = [d for d in decls if d[0] not in excluded]
        _L2_CPDEF[rel] = kept
        n += len(kept)
        if len(kept) != len(decls):
            stat.setdefault("L2_签名冲突排除", []).append(
                "%s: %d/%d" % (rel, len(decls) - len(kept), len(decls)))
    if excluded:
        stat.setdefault("L2_排除名", []).append(str(sorted(excluded))[:200])
    hit["L2_cpdef_decl"] = n
    return n


_L2_BLOCKLIST = set()   # §11.4 止损位(见 _plan_l2_cpdef)
_L3_TYPE = {"bool": "bint", "int": "long long", "float": "double"}  # §11.4 链: float 面(整链 C 化闭环实验)  # §3.1 判定后:float 面回退 object(实测复合路径 -9~-24%,见 §3.1 判读)
_L3_BLOCKLIST = set()   # 止损：编译/闸门揪出的字段 (rel, field) 加入即回退 object
_L3_RE = None


def _l3_numeric_types(gd_rel):
    # ★ 2026-11-12 重开（§H-5，撤回 §B-2 判否）：object 槽 vs 数值槽微基准差
    #   13-40x（§H-2），PCG32 u64 先例 1.9x——机制启用。§3.1：float 面重开
    #   （GDScript float=64 位与 double 同宽；f32 只来自显式 f32() 垫片，
    #   double 槽+显式 f32(x) ≡ object 槽+f32(x) 逐位相同）；字段被赋 None →
    #   编译态 TypeError 立刻炸（不静默，止损走 _L3_BLOCKLIST）。
    global _L3_RE
    import os as _os
    import re as _re
    if _L3_RE is None:
        _L3_RE = _re.compile(
            r'^var ([A-Za-z_][A-Za-z_0-9]*)'
            r'(?: *: *(bool|int|float)(?!\w)'
            r'| *:= *(True|False|true|false|[-+]?\d+(?:\.\d+)?))(?![.\w])', _re.M)
    src_path = _os.path.join(_os.path.dirname(_os.path.dirname(
        _os.path.abspath(__file__))), gd_rel)
    try:
        src = io.open(src_path, encoding='utf-8').read()
    except OSError:
        return {}
    out = {}
    for mm in _L3_RE.finditer(src):
        name, ann, lit = mm.group(1), mm.group(2), mm.group(3)
        if ann is not None:
            out[name] = _L3_TYPE[ann]
        elif lit is not None:
            # `:=` 静态推断(GDScript 锁定类型):false/true→bint,整数→ll,小数→double
            out[name] = 'bint' if lit in ('True', 'False', 'true', 'false') else (
                'double' if '.' in lit else 'long long')
    return out


def _pxd_emission(texts, files_by_rel, by_path, stat, hit):
    """L1/M1-2 入口：规划 cdef 可行性 → 改写基类语句 → 渲染 pxd。

    返回 {py_rel: pxd_text}。keep-plain 类不进 pxd；白名单模块文本被就地
    改写（可 cdef 类的基类语句 → 直接导入别名）。"""
    _strip_signal_attrs(texts, stat, hit)
    _hoist_referenced_classattrs(texts, stat, hit)
    n_cp = _plan_l2_cpdef(files_by_rel, stat, hit)
    pxds = _plan_and_rewrite_bases(texts, files_by_rel, by_path, stat, hit)
    stat["M1_2_pxd"] = ["%s：%d 槽" % (k, v.count("cdef public"))
                        for k, v in sorted(pxds.items())]
    hit["M1_2_pxd_emit"] = len(pxds)
    return pxds


def write_pkg(order, files_by_rel, by_name, by_path, class_names, stat, hit, write):
    texts = {}
    for rel in order:
        texts[rel] = transform_file(files_by_rel[rel], by_name, by_path,
                                    stat, hit, class_names)
    texts = _apply_cooldown_f32(texts)
    # ★ 顺序：C6 内联先行、C4 提升后行——提升绑定块捕获内联后的表达式，
    #   且死路径哨兵（_HoistPending）对内联后的文本兜底。
    # ★ GD_SKIP_PASSES=C6,C1,C15,C4（逗号分隔）可按趟关闭——破闸二分用。
    _skip = set((os.environ.get("GD_SKIP_PASSES") or "").split(",")) - {""}
    if "C6" not in _skip:
        texts = _inline_accessors(texts, stat, hit)
    if "C1" not in _skip:
        texts = _iter_inline(texts, stat, hit)
    if "C15" not in _skip:
        texts = _shim_locals(texts, stat, hit)
    if "C4" not in _skip:
        texts = _hoist_classrefs(texts, order, files_by_rel, stat, hit)
    if "D1" not in _skip:
        texts = _d1_seen_set(texts, stat, hit)
    if "F5" not in _skip:
        texts = _f5a_tick_inline(texts, stat, hit)
        texts = _f5b_physick_inline(texts, stat, hit)
    if "C17a" not in _skip:
        texts = _clamp_inline(texts, stat, hit)
    if "C17b" not in _skip:
        texts = _hook_strip(texts, stat, hit)
    if "D2" not in _skip:
        texts = _d2_adjcells_seen(texts, stat, hit)
    if "M2" not in _skip:
        texts = _strip_noop_hooks(texts, stat, hit)
    if "A2" not in _skip:
        texts = _char_bind(texts, stat, hit)
    if "D1T" not in _skip:
        texts = _typed_hot_loops(texts, stat, hit)
    if "CY" not in _skip:
        texts = _cy_round_alias(texts, stat, hit)
    pxd_texts = {} if "M1_2" in _skip else _pxd_emission(texts, files_by_rel, by_path, stat, hit)
    stat["M1_2_pxd_texts"] = pxd_texts    # --check 复用（write=False 时 main 取）
    if not write:
        return texts
    dirs = {OUT_PKG}
    for d in SRC_DIRS:
        for root, subs, names in os.walk(os.path.join(ROOT, d)):
            reldir = os.path.relpath(root, ROOT).replace(os.sep, "/")
            sani_dir = os.path.join(OUT_PKG, *[_sani(x) for x in reldir.split("/")])
            if any(x.endswith(".gd") for x in names) or root != os.path.join(ROOT, d):
                dirs.add(sani_dir)
            for sub in subs:
                dirs.add(os.path.join(sani_dir, _sani(sub)))
    for d in sorted(dirs):
        if not os.path.isdir(d):
            os.makedirs(d)
        init = os.path.join(d, "__init__.py")
        if not os.path.exists(init):
            with io.open(init, "w", encoding="utf-8", newline="\n") as fh:
                fh.write("")
    for rel, text in texts.items():
        # ★ 防御断言：texts 键必须是 .gd 源 rel——.py 键 = 重复条目，会以
        #   陈旧快照覆盖 .gd 的变换结果（C17b 首版被清掉的事故根因）
        if rel.endswith(".py"):
            raise RuntimeError("write_pkg: texts 出现 .py 键 %r——趟内赋值键名错误" % rel)
        p = os.path.join(OUT_PKG, *py_file_rel(rel).split("/"))
        # ★ M1-2 卫生（2026-11-11）：内容不变则跳过写盘（保 mtime）——
        #   build_cython 的 mtime 幂等判定依赖「.py 变了 pyd 才算陈旧」，
        #   无差别重写会把 664 个未变模块全部标陈旧、触发全量重编。
        if os.path.exists(p):
            with io.open(p, encoding="utf-8", newline="") as fh:
                if fh.read() == text:
                    continue
        with io.open(p, "w", encoding="utf-8", newline="\n") as fh:
            fh.write(text)
    # ── M1-2：pxd 与 .py 同目录落盘（伴随声明）──
    for py_rel, ptext in pxd_texts.items():
        p = os.path.join(OUT_PKG, *py_rel.split("/"))
        p = p[:-3] + ".pxd"
        with io.open(p, "w", encoding="utf-8", newline="\n") as fh:
            fh.write(ptext)
    with io.open(os.path.join(OUT_PKG, "_bootstrap.py"), "w",
                 encoding="utf-8", newline="\n") as fh:
        fh.write(emit_bootstrap(order, files_by_rel,
                                stripped_hooks=stat.get("M2_stripped_hooks")))
    return texts


def main() -> int:
    files, by_name, by_path, by_stem = scan_files()
    files_by_rel = {f.rel: f for f in files}
    stat = defaultdict(list)
    stat["divmod_ast"] = 0
    stat["divmod_ast_块首行"] = 0
    hit = Counter()
    order = topo_order(files, by_name, by_path, stat)
    for f in files:
        chain, cur = [], resolve_ref(f.extends, by_name, by_path)
        seen = set()
        while cur is not None and cur.rel not in seen:
            seen.add(cur.rel)
            chain.append(cur)
            cur = resolve_ref(cur.extends, by_name, by_path)
        f.ancestors = chain
    class_names = set(by_name) | set(by_stem) | set(TYPE_MAP)

    write = "--report" not in sys.argv and "--check" not in sys.argv
    texts = write_pkg(order, files_by_rel, by_name, by_path, class_names,
                      stat, hit, write)

    print("转写 %d 个 .gd → %d 个 Python 模块" % (len(files), len(order)))
    print("  divmod 走 ast 精确重写 %d 处（其中块首行 %d）"
          % (stat["divmod_ast"], stat["divmod_ast_块首行"]))
    print("\n── 改写规则命中 ──")
    for k, v in hit.most_common(50):
        print("  %-30s %6d" % (k, v))
    for key, label in (("divmod_兜底", "/ 或 % 走字符兜底"),
                       ("未识别", "未识别构造"),
                       ("声明未解析", "声明未解析"),
                       ("枚举值未求值", "枚举值未求值"),
                       ("枚举行异常", "枚举行异常"),
                       ("签名括号不配对", "签名括号不配对"),
                       ("match case 非块形态", "match case 非块形态"),
                       ("循环依赖", "循环依赖"),
                       ("内嵌类别名撞名", "内嵌类别名撞名"),
                       ("未知类型零值", "未知类型零值（按 None 处理）")):
        if stat[key]:
            print("\n── %s：%d 条 ──" % (label, len(stat[key])))
            for x in stat[key][:25]:
                print("  " + str(x))

    if "--check" in sys.argv:
        bad = []
        for rel, text in texts.items():
            p = os.path.join(OUT_PKG, *py_file_rel(rel).split("/"))
            old = ""
            if os.path.exists(p):
                old = io.open(p, encoding="utf-8", errors="replace").read()
            if old != text:
                bad.append(rel)
        for py_rel, ptext in (stat.get("M1_2_pxd_texts") or {}).items():
            p = os.path.join(OUT_PKG, *py_rel.split("/"))
            p = p[:-3] + ".pxd"
            old = ""
            if os.path.exists(p):
                old = io.open(p, encoding="utf-8", errors="replace").read()
            if old != ptext:
                bad.append(py_rel + " → .pxd")
        if bad:
            print("\n产物已过期（%d 个）：%s" % (len(bad), bad[:5]))
            return 1
        print("\n产物与 gd_core / gd_core_items 同步。")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
