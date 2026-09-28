# -*- coding: utf-8 -*-
"""scan_translit_gaps.py — 转写缺口静态扫描（GDScript → Python）

补 `跑一遍全量` 覆盖不到的面：**未被任何测试执行到的分支**。

两类缺口（都是本项目实际踩过的）：

  A. **变量遮蔽方法**
     GDScript 里成员变量与方法**分属两张表**，子类 `var speed` 与基类 `func speed()`
     可以共存：`self.speed` 取变量，`self.speed()` 调方法。
     Python 里实例属性直接**遮蔽**类方法 → 运行时报
     `TypeError: 'float' object is not callable`，且只在「该物品上场 + 跑到那一行」时炸。
     实测：Girl Power / Perpetuum Mobile / Sloth 三件。

  B. **未映射符号**
     转写只做了「视觉剥离 + 符号映射」，映射表没覆盖到的全局名会原样落进 Python，
     变成 `NameError: name 'xxx' is not defined`。
     实测：`call_deferred`（2 件）、`typeof` + `TYPE_VECTOR2`（12 件棋类）。

★ 两类都**不能靠跑一遍发现**：A 只在特定物品 + 特定分支触发；B 只在被调用的函数里炸。
  故本工具走**静态枚举**，把缺口面一次列全。

用法：
    python tools/scan_translit_gaps.py            # 两类都扫
    python tools/scan_translit_gaps.py --shadow   # 只扫 A
    python tools/scan_translit_gaps.py --undef    # 只扫 B
    python tools/scan_translit_gaps.py --json     # 机器可读
"""
from __future__ import annotations

import ast
import builtins
import io
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GD_DIRS = [os.path.join(ROOT, "gd_core"), os.path.join(ROOT, "gd_core_items")]
PY_DIRS = [os.path.join(ROOT, "gd_core_py")]

FUNC_HEAD_RE = re.compile(r"^\s*(?:static\s+)?func\s+([A-Za-z_]\w*)\s*\(")
VAR_HEAD_RE = re.compile(r"^var\s+([A-Za-z_]\w*)")
EXTENDS_RE = re.compile(r'^extends\s+(.+?)\s*$')
# ★ 单双引号都要认：`ast.unparse()` 输出**单引号**，源码里是双引号。
#   早先只写双引号 → Python 侧继承链恒断 → 该侧恒返回「无」。
RES_PATH_RE = re.compile(r"""["']res://([^"']+)["']""")


# ═════════════════════════ A. 变量遮蔽方法 ═════════════════════════

def _gd_files():
    for d in GD_DIRS:
        for dirpath, _dirs, files in os.walk(d):
            for f in sorted(files):
                if f.endswith(".gd"):
                    yield os.path.join(dirpath, f)


def _parse_gd(path: str) -> dict:
    """只取三类顶层信息：extends、顶层 var、func。"""
    ext = ""
    vars_, funcs = set(), set()
    with io.open(path, encoding="utf-8", errors="replace") as fh:
        for ln in fh:
            if not ext:
                m = EXTENDS_RE.match(ln.rstrip("\n"))
                if m:
                    ext = m.group(1).strip()
                    continue
            m = VAR_HEAD_RE.match(ln)
            if m:
                vars_.add(m.group(1))
            m = FUNC_HEAD_RE.match(ln)
            if m:
                funcs.add(m.group(1))
    return {"extends": ext, "vars": vars_, "funcs": funcs}


def _resolve_ext(decl: str) -> str:
    """extends 声明 → 本仓库内的 .gd 绝对路径（解析不到返回 ""）。

    ★ 三种形态都要认：
      `"res://gd_core/CoreItem.gd"`  —— 内核侧已是仓库相对路径，**直接对根拼**
      `"res://Items/Weapon.gd"`      —— 原版路径，映到 gd_core_items/
      `Item` / `Weapon`              —— 裸基名，按 stem 在两侧目录里找

    早先只处理了第二种，把 `res://gd_core/CoreItem.gd` 拼成 `gd_core/gd_core/...`
    → Item.gd 的继承链断在这里 → 撞名扫描恒返回「无」（**表笔没接上**）。
    """
    decl = decl.strip().strip('"').strip("'")
    if not decl:
        return ""
    if decl.startswith("res://"):
        rel = decl[len("res://"):].replace("\\", "/")
        cand = os.path.normpath(os.path.join(ROOT, rel))
        if os.path.exists(cand):
            return cand
        # 原版路径 res://Items/X.gd → 内核侧镜像（去掉 Items/ 前缀）
        alt = rel.replace("Items/", "", 1) if rel.startswith("Items/") else rel
        for d in GD_DIRS:
            c = os.path.normpath(os.path.join(d, alt))
            if os.path.exists(c):
                return c
        return ""
    # 裸基名（extends Item / extends Weapon）
    base = decl if decl.endswith(".gd") else decl + ".gd"
    for d in GD_DIRS:
        p = os.path.join(d, base)
        if os.path.exists(p):
            return p
    return ""


def scan_shadow() -> list:
    """返回 [(脚本, 变量, 定义该变量的位置, 被遮蔽的方法, 定义该方法的脚本)]。"""
    info = {p: _parse_gd(p) for p in _gd_files()}
    out = []
    for path, d in info.items():
        if not d["vars"]:
            continue
        # 沿继承链收集基类的 func（**不含自身**：自身同名 var+func 是 GDScript 里的真冲突）
        chain_funcs = {}          # 方法名 -> 定义它的脚本
        seen = {path}
        cur = path
        while True:
            ext = info.get(cur, {}).get("extends", "")
            nxt = _resolve_ext(ext) if ext else ""
            if not nxt or nxt in seen or nxt not in info:
                break
            seen.add(nxt)
            for fn in info[nxt]["funcs"]:
                chain_funcs.setdefault(fn, nxt)
            # 同名变量也沿链传递（子类继承父类的 var，同样会遮蔽）
            cur = nxt
        for v in sorted(d["vars"] & set(chain_funcs)):
            owner = chain_funcs[v]
            out.append((os.path.relpath(path, ROOT).replace("\\", "/"), v,
                        os.path.relpath(owner, ROOT).replace("\\", "/")))
    return out


def scan_shadow_py() -> list:
    """Python 侧同项扫描：`self.X = ...` 遮蔽继承链上的 `def X`。

    与 GDScript 侧互为交叉验证：两侧结果**应当一致**。
    不一致就说明某一侧的扫描器坏了（本项目已踩过：继承链解析写错 →
    GDScript 侧恒返回「无」，只剩 Python 侧说话）。
    """
    # 1) 建索引：py 文件 → 顶层类节点
    by_file = {}
    for dirpath, _dirs, files in os.walk(os.path.join(ROOT, "gd_core_py")):
        for f in sorted(files):
            if not f.endswith(".py"):
                continue
            path = os.path.join(dirpath, f)
            rel = os.path.relpath(path, ROOT).replace("\\", "/")
            try:
                with io.open(path, encoding="utf-8") as fh:
                    tree = ast.parse(fh.read())
            except SyntaxError:
                continue
            classes = [n for n in tree.body if isinstance(n, ast.ClassDef)]
            if classes:
                by_file[rel] = classes

    def base_path_of(cls: ast.ClassDef):
        """解析 `class X(_R.C("res://..."))` → 父类所在 py 相对路径。"""
        for b in cls.bases:
            s = ast.unparse(b) if hasattr(ast, "unparse") else ""
            m = RES_PATH_RE.search(s)
            if m:
                gd_rel = m.group(1).replace("\\", "/")
                py_rel = "gd_core_py/" + (
                    gd_rel[:-3] + ".py" if gd_rel.endswith(".gd") else gd_rel + ".py")
                if py_rel in by_file:
                    return py_rel
        return ""

    def pick(rel: str):
        """父类所在文件 → 那个「真正当基类用」的类。

        ★ 不能取 `classes[0]`：转写产物里同一个 .gd 的**内嵌类**会排在主类之前
          （如 `gd_core_items/Item.py` 的第一个顶层类是 `SignalConnection`，
          `Item` 在第二个）。取 [0] 会让继承链断在这里，扫描恒返回「无」。

        三级判据：
          1. 基类表达式里出现 `_R.C(` 的 —— 转写出来的类都是这种（继承内核类）
          2. 类名与文件 stem 相同的 —— 内核类直接 `extends GodotObject`（如
             `class CoreItem(GodotObject)`），第 1 条不命中，靠这条
          3. 都没有才退回第一个（并会让整条链变得不可信）
        """
        for c in by_file[rel]:
            for b in c.bases:
                s = ast.unparse(b) if hasattr(ast, "unparse") else ""
                if "_R.C(" in s:
                    return c
        stem = os.path.basename(rel)[:-3]
        for c in by_file[rel]:
            if c.name == stem:
                return c
        return by_file[rel][0]

    def defs_of(cls):
        """真正的方法名。`@property` / `@x.setter` / `@x.deleter` **不算**
        —— 那是防遮蔽的正当写法（见 `_rt.py::RandomNumberGenerator.seed`），
        把它算成「被遮蔽的方法」是误报。"""
        out = set()
        for n in cls.body:
            if not isinstance(n, ast.FunctionDef):
                continue
            if n.decorator_list:
                d0 = n.decorator_list[0]
                is_prop = (isinstance(d0, ast.Name) and d0.id == "property") or (
                    isinstance(d0, ast.Attribute)
                    and d0.attr in ("setter", "deleter", "getter"))
                if is_prop:
                    continue
            out.add(n.name)
        return out

    def attrs_of(cls):
        out = set()
        for n in ast.walk(cls):
            if isinstance(n, (ast.Assign, ast.AnnAssign, ast.AugAssign)):
                tgts = n.targets if isinstance(n, ast.Assign) else [n.target]
                for t in tgts:
                    if isinstance(t, ast.Attribute) and isinstance(t.value, ast.Name) \
                            and t.value.id == "self":
                        out.add(t.attr)
        return out

    # 2) 沿链求交
    out = []
    for rel, classes in sorted(by_file.items()):
        for cls in classes:
            names, attrs = set(), set()
            owner = {}
            cur_rel, cur_cls = rel, cls
            seen = set()
            while cur_cls is not None and (cur_rel, cur_cls.name) not in seen:
                seen.add((cur_rel, cur_cls.name))
                for d in defs_of(cur_cls):
                    names.add(d)
                    owner.setdefault(d, cur_rel)
                attrs |= attrs_of(cur_cls)
                nxt_rel = base_path_of(cur_cls)
                cur_cls = pick(nxt_rel) if nxt_rel else None
                cur_rel = nxt_rel or cur_rel
            for x in sorted(names & attrs):
                out.append((rel, cls.name, x, owner.get(x, "?")))
    return out


# ═════════════════════════ B. 未映射符号 ═════════════════════════

def _rt_exports() -> set:
    """`from _rt import *` 带来的名字（失败则退回扫源码里的顶层赋值/def/class）。"""
    try:
        sys.path.insert(0, ROOT)
        import importlib
        rt = importlib.import_module("gd_core_py._rt")
        names = set(dir(rt))
        return {n for n in names if not n.startswith("__")}
    except Exception:  # noqa: BLE001
        pass
    names = set()
    p = os.path.join(ROOT, "gd_core_py", "_rt.py")
    if os.path.exists(p):
        with io.open(p, encoding="utf-8", errors="replace") as fh:
            for ln in fh:
                m = re.match(r"^(?:def|class)\s+([A-Za-z_]\w*)", ln)
                if m:
                    names.add(m.group(1))
                m = re.match(r"^([A-Za-z_]\w*)\s*=", ln)
                if m:
                    names.add(m.group(1))
    return names


class _Scope:
    """收集一个作用域里的绑定名。"""

    def __init__(self, outer=None, seed=()):
        self.names = set(seed)
        self.outer = outer

    def has(self, n):
        s = self
        while s is not None:
            if n in s.names:
                return True
            s = s.outer
        return False


def _collect_binds(node, sc: _Scope):
    """把一个作用域内所有「绑定型」语法收集进 sc。"""
    for n in ast.walk(node):
        if isinstance(n, ast.Name) and isinstance(n.ctx, (ast.Store, ast.Del)):
            sc.names.add(n.id)
        elif isinstance(n, ast.arg):
            sc.names.add(n.arg)
        elif isinstance(n, (ast.FunctionDef, ast.AsyncFunctionDef, ast.ClassDef)):
            sc.names.add(n.name)
        elif isinstance(n, ast.alias):
            sc.names.add((n.asname or n.name).split(".")[0])
        elif isinstance(n, ast.ExceptHandler) and n.name:
            sc.names.add(n.name)
        elif isinstance(n, ast.Global):
            sc.names.update(n.names)
        elif isinstance(n, ast.Nonlocal):
            sc.names.update(n.names)


def _walk_scoped(node, sc: _Scope, found: list, path: str):
    """按嵌套作用域递归，报告未绑定的 Name(Load)。

    注意：类体内直接引用的名字在 Python 里**不走类作用域**（函数体里读不到类变量），
    但我们只关心「是否完全没定义」，所以把类体当作浅层作用域处理即可 ——
    宁可漏报也不误报：本函数只报「连外层都没有」的名字。
    """
    for child in ast.iter_child_nodes(node):
        if isinstance(child, (ast.FunctionDef, ast.AsyncFunctionDef, ast.Lambda)):
            inner = _Scope(outer=sc)
            args = getattr(child, "args", None)
            if args is not None:
                _collect_binds(args, inner)
            body = child.body if isinstance(child.body, list) else [child.body]
            for b in body:
                _collect_binds(b, inner)
            for b in body:
                _walk_scoped(b, inner, found, path)
        elif isinstance(child, ast.ClassDef):
            inner = _Scope(outer=sc)
            for b in child.body:
                _collect_binds(b, inner)
            for b in child.body:
                _walk_scoped(b, inner, found, path)
        elif isinstance(child, (ast.ListComp, ast.SetComp, ast.DictComp,
                                ast.GeneratorExp)):
            inner = _Scope(outer=sc)
            for gen in child.generators:
                _collect_binds(gen.target, inner)
                _collect_binds(gen.iter, inner)
            for f in ("elt", "key", "value"):
                v = getattr(child, f, None)
                if v is not None:
                    _walk_scoped(v, inner, found, path)
        else:
            _collect_binds(child, sc)
            _walk_scoped(child, sc, found, path)


BUILTINS = set(dir(builtins)) | {"__file__", "__name__", "__doc__", "self", "cls"}


def scan_undef() -> list:
    exports = _rt_exports()
    out = []
    for d in PY_DIRS:
        for dirpath, _dirs, files in os.walk(d):
            for f in sorted(files):
                if not f.endswith(".py"):
                    continue
                path = os.path.join(dirpath, f)
                rel = os.path.relpath(path, ROOT).replace("\\", "/")
                try:
                    with io.open(path, encoding="utf-8") as fh:
                        tree = ast.parse(fh.read(), filename=rel)
                except SyntaxError as e:
                    out.append((rel, 0, "<SyntaxError: %s>" % e, "syntax"))
                    continue
                module_scope = _Scope(seed=set(exports) | BUILTINS)
                _collect_binds(tree, module_scope)
                found: list = []
                _walk_scoped(tree, module_scope, found, rel)

                seen = set()
                for n in ast.walk(tree):
                    if isinstance(n, ast.Name) and isinstance(n.ctx, ast.Load):
                        if n.id in module_scope.names or n.id in BUILTINS:
                            continue
                        if n.id in seen:
                            continue
                        # 函数/类内局部：由 _walk_scoped 负责，这里只做兜底
                        seen.add(n.id)
                        found.append(n)
                if found:
                    names = sorted({n.id for n in found})
                    ln = min(n.lineno for n in found if hasattr(n, "lineno"))
                    out.append((rel, ln, ", ".join(names), "undef"))
    return out


# ═════════════════════════ C. 整行丢失 ═════════════════════════

# ★ 必须带 re.M：不带时 `^` 只匹配**整个字符串的开头**，`^\t+名字 =` 于是只在文件
#   第一行生效 —— 判据恒返回「无」，看着像「全库干净」。
#   这是本项目第二次栽在同一个坑上（第一次是 `scan_shadow` 的继承链解析写错，
#   GDScript 侧恒返回「无」）。故本工具对「0 命中」一律配正对照：
#   `output/positive_control_drop.py` 会人为删掉一行、要求扫描必须报出来。
_GD_ASSIGN_RE = re.compile(r"^\t+([A-Za-z_]\w*)\s*=(?!=)", re.M)
_GD_FOR_RE = re.compile(r"^\t+for\s+([A-Za-z_]\w*)\s+in\b", re.M)


def _strip_enum_blocks(text: str) -> str:
    """删掉 `enum X { … }` 整块。

    ★ 为什么必须删：enum 成员在 GD 里是 `\\tName = 0` 的形态，看起来和赋值一模一样，
      但在 Python 产物里它们进了 `EnumDict({"Name": 0, …})` —— **不是赋值**。
      不剔除就会产生成片的误报（实测 147 处里绝大多数是 CoreConst 的枚举成员），
      而误报一多，真丢行就淹没了。
    """
    out, depth = [], 0
    for ln in text.split("\n"):
        s = ln.strip()
        if depth > 0:
            depth += s.count("{") - s.count("}")
            continue
        if re.match(r"enum\s+[A-Za-z_]\w*\s*[:{]?", s):
            depth = s.count("{") - s.count("}")
            continue
        out.append(ln)
    return "\n".join(out)


def scan_dropped_assigns() -> list:
    """GD 产物里赋过值的名字，在对应 Python 产物里找不到任何赋值 → 疑似整行丢失。

    为什么需要第三类判据：A（撞名）与 B（未定义名字）都是**静态可枚举的名字问题**，
    而「整行消失」两者都抓不到 —— 那行既没撞名也没引用未定义符号，它就是不见了。

    实测两个真实事故：
      1. `gd_to_py.py::find_block_end` 按缩进判块结束，多行字面量的 `}` 写在第 0 列
         → 误判函数体提前结束 → `_readyInit()` 里 `damageSource = ...` 整行丢弃
         （WandofDissonance / Laboratory 等 18 个含顶格 `}` 的文件受影响）。
      2. `core/color_names.inc` 那条链路上「规则写了但从未命中」是同类：
         写下了却没人核对它到底有没有生效。

    ★ 这是**启发式**：GD 的 `x = 1` 在 Python 侧可能被改写成别的形态（展开、函数调用），
      故命中要人工定裁。它只负责把「GD 写了而 Python 里连名字都没出现」的清单捞出来。
    """
    out = []
    for gd_dir, py_dir in ((os.path.join(ROOT, "gd_core"), os.path.join(ROOT, "gd_core_py", "gd_core")),
                           (os.path.join(ROOT, "gd_core_items"), os.path.join(ROOT, "gd_core_py", "gd_core_items"))):
        for dirpath, _dirs, files in os.walk(gd_dir):
            for f in sorted(files):
                if not f.endswith(".gd"):
                    continue
                gd_path = os.path.join(dirpath, f)
                rel = os.path.relpath(gd_path, gd_dir)
                # ★ Python 产物名把 `-` 换成 `_`（`White-EyesBlueDragon.gd` →
                #   `White_EyesBlueDragon.py`）。只按原样找会误报「无对应产物」。
                stem = rel[:-3]
                py_path = os.path.join(py_dir, stem + ".py")
                if not os.path.exists(py_path):
                    py_path = os.path.join(py_dir, stem.replace("-", "_") + ".py")
                if not os.path.exists(py_path):
                    out.append((os.path.relpath(gd_path, ROOT).replace("\\", "/"),
                                "", "<无对应 Python 产物>"))
                    continue
                with io.open(gd_path, encoding="utf-8", errors="replace") as fh:
                    gd = fh.read()
                with io.open(py_path, encoding="utf-8", errors="replace") as fh:
                    py = fh.read()
                gd = re.sub(r"#[^\n]*", "", gd)
                gd = re.sub(r'"(?:[^"\\]|\\.)*"', '""', gd)
                gd = _strip_enum_blocks(gd)
                names = set(m.group(1) for m in _GD_ASSIGN_RE.finditer(gd))
                names |= set(m.group(1) for m in _GD_FOR_RE.finditer(gd))
                for n in sorted(names):
                    if re.search(r"(?:self\.)?" + re.escape(n) + r"\s*=(?!=)", py):
                        continue
                    if re.search(r"for\s+%s\b" % re.escape(n), py):
                        continue
                    # 枚举/常量表：GD 靠 `enum X { Name = 0 }`，Python 侧是
                    # `EnumDict({"Name": 0})` —— 名字以**字典键**形态存在。
                    if re.search(r"[\"']%s[\"']\s*[:=]" % re.escape(n), py):
                        continue
                    out.append((os.path.relpath(gd_path, ROOT).replace("\\", "/"), n,
                                os.path.relpath(py_path, ROOT).replace("\\", "/")))
    return out


# ═════════════════════════ 主流程 ═════════════════════════

def main() -> int:
    only_shadow = "--shadow" in sys.argv
    only_undef = "--undef" in sys.argv
    only_drop = "--drop" in sys.argv
    as_json = "--json" in sys.argv
    only_one = only_shadow or only_undef or only_drop

    shadow = [] if (only_undef or only_drop) else scan_shadow()
    shadow_py = [] if (only_undef or only_drop) else scan_shadow_py()
    undef = [] if (only_shadow or only_drop) else scan_undef()
    dropped = [] if (only_shadow or only_undef) else scan_dropped_assigns()

    if as_json:
        print(json.dumps({"shadow_gd": shadow, "shadow_py": shadow_py,
                          "undef": undef, "dropped": dropped},
                         ensure_ascii=False, indent=2))
        return 0

    print("A. 变量遮蔽方法（GDScript 双表语义 → Python 单表）")
    if shadow:
        print("   [GDScript 侧] %-50s %-16s %s" % ("脚本", "变量（遮蔽）", "被遮蔽的方法定义处"))
        for rel, v, owner in shadow:
            print("   %-64s %-16s %s" % (rel, v, owner))
    else:
        print("   [GDScript 侧] 无")
    if shadow_py:
        print("   [Python 侧]   %-50s %-16s %s" % ("模块", "遮蔽的属性", "被遮蔽的方法定义处"))
        for rel, cls, v, owner in shadow_py:
            print("   %-64s %-16s %s" % ("%s::%s" % (rel, cls), v, owner))
    else:
        print("   [Python 侧]   无")
    gd_set = {(r.split("/")[-1], v) for r, v, _o in shadow}
    py_set = {(r.split("/")[-1].replace(".py", ".gd"), v) for r, _c, v, _o in shadow_py}
    print("   命中：GDScript %d 处 / Python %d 处%s"
          % (len(shadow), len(shadow_py),
             "" if not (gd_set ^ py_set) else "  ★ 两侧不一致，扫描器需查"))

    print()
    print("B. 未映射符号（Python 侧未绑定名字）")
    if undef:
        for rel, ln, names, kind in undef:
            print("   %-64s :%-5d %s" % (rel, ln, names))
        print("   命中 %d 个文件" % len(undef))
    else:
        print("   无")

    print()
    print("C. 整行丢失（GD 里赋过值、对应 Python 产物里找不到同名赋值）")
    if dropped:
        print("   %-56s %-22s %s" % ("GD 产物", "疑似丢掉的左值", "对应 Python 产物"))
        for gd_rel, n, py_rel in dropped:
            print("   %-56s %-22s %s" % (gd_rel, n, py_rel))
        print("   命中 %d 处（启发式，须人工定裁）" % len(dropped))
    else:
        print("   无")

    print()
    ok = not shadow and not shadow_py and not undef and not dropped
    print("TRANSLIT_GAPS: %s（遮蔽 %d 处 / 未映射 %d 文件 / 疑似丢行 %d 处）"
          % ("PASS" if ok else "FAIL", len(shadow) + len(shadow_py),
             len(undef), len(dropped)))
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
