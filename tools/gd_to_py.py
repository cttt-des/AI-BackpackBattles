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
    args, deferred = [], []
    for a in split_args(sig[op + 1:cp]):
        txt, d = render_arg(a, hit, stat)
        if txt:
            args.append(txt)
        if d:
            deferred.append(d)
    if is_static:
        hit["static func→@staticmethod"] += 1
        return "@staticmethod\ndef %s(%s):" % (name, ", ".join(args)), deferred
    allargs = ["self"] + args
    return "def %s(%s):" % (name, ", ".join(allargs)), deferred


def render_arg(a, hit, stat):
    """返回 (参数声明文本, 延迟求值项或 None)。

    延迟求值项 = (参数名, 原始默认值表达式)，由发射方在函数体首行还原成
    `if <名> is GD_DEFAULT: <名> = <表达式>`；表达式在那里才走 Rewriter，
    因此可以正确解析 self 成员引用。
    """
    a = a.strip()
    if not a:
        return "", None
    eq = top_level_eq(a)
    lhs, rhs = (a[:eq], a[eq + 1:]) if eq >= 0 else (a, None)
    nm = lhs.split(":", 1)[0].strip()
    for gd, py in PY_KEYWORD_RENAMES:
        if nm == gd:
            hit["关键字标识符:参数 %s→%s" % (gd, py)] += 1
            nm = py
    if rhs is None:
        return nm, None
    rhs = rhs.strip()
    lit = _py_literals(rhs)
    if _is_plain_literal(lit):
        return "%s=%s" % (nm, lit), None
    hit["默认值延迟求值→GD_DEFAULT"] += 1
    return "%s=GD_DEFAULT" % nm, (nm, rhs)


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
            out.extend(self._stmt("self.%s = %s" % (name, val),
                                  gd_indent + py_off + 1, rw, {name}, True))
        out.append("")

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
                func_text, deferred = render_func(sig, self.hit, self.stat)
                for sig_line in func_text.split("\n"):
                    out.append("\t" * (gd_indent + py_off) + sig_line)
                # 非字面量默认值在函数体首行还原（GDScript 每次调用求值）
                for dname, dexpr in deferred:
                    out.extend(self._stmt(
                        "if %s is GD_DEFAULT: %s = %s" % (dname, dname, dexpr),
                        gd_indent + py_off + 1, rw, locs, True, is_static))
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
        base_gd = count_tabs(parts[0])
        out = ["\t" * py_indent + parts[0].lstrip("\t")]
        for p in parts[1:]:
            if not p.strip():
                out.append("")
                continue
            rel = count_tabs(p) - base_gd
            out.append("\t" * (py_indent + max(rel, 0)) + p.lstrip("\t"))
        return out


def transform_file(f, by_name, by_path, stat, hit, class_names):
    # ★ 生成模块在 gd_core/ 或 gd_core_items/[子目录/] 包里，而 _rt/_registry 在
    #   gd_core_py 顶层 —— 必须写足够的上级点数（`.` 会被解析成 gd_core_py.gd_core._rt，
    #   报 "No module named ..."）。depth = 路径段数 - 1（减掉模块自身）。
    depth = len(f.rel[:-3].split("/")) - 1
    dots = "." * (depth + 1)
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
    for _nm in em.hoisted_names:
        if _nm in methods or _nm in _field_names:
            stat["内嵌类别名撞名"].append("%s.%s" % (f.py_class, _nm))
        out.append("%s.%s = %s" % (f.py_class, _nm, _nm))
    if em.hoisted_names:
        out.append("")

    text = "\n".join(out) + "\n\n"
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


def emit_bootstrap(order, files_by_rel):
    out = [GEN_BANNER,
           '"""按 extends 依赖拓扑序导入全部模块（基类先注册，与 Godot 加载次序同义）。"""\n\n',
           "from . import _registry  # noqa: F401\n",
           "from . import _rt  # noqa: F401\n\n\n",
           "def load_all():\n",
           '    """导入全部 gd 模块。返回导入失败清单（空 = 全部成功）。"""\n',
           "    failed = []\n"]
    for rel in order:
        out.append("    try:\n")
        out.append("        import %s  # noqa: F401\n" % module_path(files_by_rel[rel]))
        out.append("    except Exception as exc:  # noqa: BLE001\n")
        out.append("        failed.append((%r, repr(exc)))\n" % rel)
    out.append("    return failed\n")
    return "".join(out)


def write_pkg(order, files_by_rel, by_name, by_path, class_names, stat, hit, write):
    texts = {}
    for rel in order:
        texts[rel] = transform_file(files_by_rel[rel], by_name, by_path,
                                    stat, hit, class_names)
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
        p = os.path.join(OUT_PKG, *py_file_rel(rel).split("/"))
        with io.open(p, "w", encoding="utf-8", newline="\n") as fh:
            fh.write(text)
    with io.open(os.path.join(OUT_PKG, "_bootstrap.py"), "w",
                 encoding="utf-8", newline="\n") as fh:
        fh.write(emit_bootstrap(order, files_by_rel))
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
        if bad:
            print("\n产物已过期（%d 个）：%s" % (len(bad), bad[:5]))
            return 1
        print("\n产物与 gd_core / gd_core_items 同步。")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
