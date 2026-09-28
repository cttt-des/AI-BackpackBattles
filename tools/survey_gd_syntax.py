#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""survey_gd_syntax.py — 枚举 gd_core + gd_core_items 里全部需转写的语法构造。

存在的理由
==========
`tools/gd_to_py.py` 是**机械**转写器 —— 它成立的前提是「GDScript 专有构造只有一小圈」。
这句话必须可复算，否则转写器漏掉一类构造时谁也不知道。

本工具把那个「一小圈」量化成清单，并在 `--verify` 下**断言** `gd_to_py.py` 文档里
引用的每一个数字。数字走样（有人往内核里加了 `yield`、或加了一处 `%` 格式化）就当场失败。

★ 这正是本仓库栽过的跟头：生成物里写死的「判定路径缺口为 0」曾是假断言。
  故凡文档里出现「N 处」，都得有个工具能当场把它算出来。

用法
====
    python tools/survey_gd_syntax.py            # 打印全量语法面清单
    python tools/survey_gd_syntax.py --verify   # 只断言 gd_to_py.py 引用的那些数字

判据口径
========
- 「行数」= 含该构造的**行**数（一行命中多次算一次）
- 「代码」= 去掉字符串与注释后的命中；注释里的提及不算
"""
import argparse
import os
import re
import sys
from collections import Counter, defaultdict

sys.stdout.reconfigure(encoding="utf-8")

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEFAULT_DIRS = ["gd_core", "gd_core_items"]


def load(dirs):
    out = {}
    for d in dirs:
        base = os.path.join(ROOT, d)
        for root, _, files in os.walk(base):
            for f in sorted(files):
                if f.endswith(".gd"):
                    p = os.path.join(root, f)
                    rel = os.path.relpath(p, ROOT).replace(os.sep, "/")
                    with open(p, encoding="utf-8", errors="replace") as fh:
                        out[rel] = fh.read().splitlines()
    return out


def strip_str(s):
    """去字符串与注释，避免误判（粗粒度，够用；三引号不在本内核语法面内）。"""
    s = re.sub(r'"[^"\n]*"', '""', s)
    s = re.sub(r"'[^'\n]*'", "''", s)
    s = re.sub(r"#[^\n]*", "", s)
    return s


EXPR_PATS = {
    "&& / || / !":        r"(?<![&|!=])&&|\|\||(?<![!=!])!(?![=])",
    "match 语句":          r"^\t*match\s",
    "yield":              r"\byield\b",
    "preload(":           r"\bpreload\s*\(",
    "load(":              r"(?<!pre)\bload\s*\(",
    ".new(":              r"\.new\s*\(",
    "$ 节点路径":          r"\$[A-Za-z_]",
    "% 字符串格式化":       r'%\s*(\[|[sdfox])',
    "is 类型检查":          r"\bis\s+[A-Z]",
    "typeof(":            r"\btypeof\s*\(",
    "lambda func(":       r"func\s*\([^)]*\)\s*:",
    "emit_signal(":       r"\bemit_signal\s*\(",
    "connect(":           r"\bconnect\s*\(",
    "disconnect(":        r"\bdisconnect\s*\(",
    "callv(":             r"\bcallv\s*\(",
    ".call(":             r"\.call\s*\(",
    "has_method(":        r"\bhas_method\s*\(",
    "call_group":         r"\bcall_group\b",
    "setget":             r"\bsetget\b",
    "onready":            r"\bonready\b",
    "assert(":            r"\bassert\s*\(",
    "push_error":         r"\bpush_error\b",
    "print(":             r"\bprint\s*\(",
    "printerr":           r"\bprinterr\b",
    "OS./Engine.":        r"\bOS\.|\bEngine\.",
    "randf/randi":        r"\brandf\b|\brandi\b|\brandf_range\b|\brandi_range\b",
    "Tween/Timer 类":      r"\bTween\b|\bTimer\b",
    "Vector2":            r"\bVector2\b",
    "Color":              r"\bColor\b",
}

HEAD_KEYWORDS = ("if", "elif", "else", "for", "while", "match", "return", "break",
                 "continue", "pass", "var", "const", "func", "extends", "class_name",
                 "class", "enum", "signal", "static", "setget", "onready", "export",
                 "static func", "assert", "yield", "tool")


def scan(src):
    """返回 dict：head / expr / calls / ops / nfiles / nlines。"""
    head, head_ex = Counter(), defaultdict(list)
    head_re = re.compile(r"^(\t*)([A-Za-z_]\w*|static\s+func|class\s+\w+|@\w+)")
    for rel, lines in src.items():
        for i, ln in enumerate(lines, 1):
            s = ln.lstrip("\t")
            if not s or s.startswith("#"):
                continue
            m = head_re.match(ln)
            if not m:
                continue
            kw = m.group(2)
            if re.match(r"^static\s+func$", kw):
                kw = "static func"
            if kw in HEAD_KEYWORDS or kw.startswith("@") \
                    or re.match(r"^class\b", kw) or re.match(r"^static\b", kw):
                head[kw] += 1
                if len(head_ex[kw]) < 2:
                    head_ex[kw].append("%s:%d" % (rel, i))

    expr = Counter()
    for rel, lines in src.items():
        for ln in lines:
            code = strip_str(ln)
            for name, pat in EXPR_PATS.items():
                if re.search(pat, code):
                    expr[name] += 1
    tri = 0
    for rel, lines in src.items():
        for ln in lines:
            code = strip_str(ln)
            if re.search(r"\S\s+if\s+.+\s+else\s+\S", code) and not re.match(r"^\t*(if|elif)\b", code):
                tri += 1
    expr["三元 a if c else b"] = tri

    calls = Counter()
    for rel, lines in src.items():
        for ln in lines:
            for m in re.finditer(r"\.([A-Za-z_]\w*)\s*\(", strip_str(ln)):
                calls[m.group(1)] += 1

    ops = {}
    for name, pat in {
        "整除 / 与 %": r"[^/*]\s[/%]\s",
        "** 幂": r"\*\*",
        "位运算 &|^": r"(?<!&)&(?![&=])|(?<!\|)\|(?<!\|)(?![|=])",
        "@ 装饰器": r"^\s*@",
        ":= 推断声明": r":=",
        "-> 返回类型": r"->",
        "\\ 续行": r"\\$",
    }.items():
        ops[name] = sum(1 for lines in src.values() for ln in lines
                        if re.search(pat, strip_str(ln)))

    # 词边界出现次数（与「行数」不同口径，用于区分「N 行 / M 次」）
    occ = {}
    for name in ("Vector2", "Color", "Vector3"):
        rx = re.compile(r"\b%s\b" % name)
        occ[name] = sum(len(rx.findall(strip_str(ln)))
                        for lines in src.values() for ln in lines)

    return {"head": head, "head_ex": head_ex, "expr": expr, "calls": calls,
            "ops": ops, "occ": occ,
            "nfiles": len(src), "nlines": sum(len(v) for v in src.values())}


# ═══════════════════════ 断言：gd_to_py.py 文档引用的数字 ═══════════════════════
# 每条 = (说明, 取值函数, 期望值)。期望值改了就说明有人动了内核语法面 —— 必须回看
# gd_to_py.py 的文档与转写规则是否还成立。
CLAIMS = [
    ("yield 出现次数（代码）",        lambda s: s["expr"]["yield"], 0),
    ("preload( 出现行数",            lambda s: s["expr"]["preload("], 0),
    ("setget 出现行数",              lambda s: s["expr"]["setget"], 0),
    # ★ onready / add_child 在**注释**里有提及（9 处 / 2 处），代码内 0 处。
    #   strip_str 去注释，故这里数到 0 才是对的；用 count_api_usage.py 可对照。
    ("onready 行数（代码内）",        lambda s: s["expr"]["onready"], 0),
    ("$ 节点路径 出现行数",           lambda s: s["expr"]["$ 节点路径"], 0),
    ("match 行首出现行数",            lambda s: s["head"]["match"], 20),
    ("enum 行首出现行数",             lambda s: s["head"]["enum"], 55),
    ("signal 行首出现行数",           lambda s: s["head"]["signal"], 9),
    ("class（内嵌）行首行数",          lambda s: s["head"]["class"], 8),
    # ★ 取 head["static"]：正则交替 `[A-Za-z_]\w*|static\s+func` 里前者先生效，
    #   故 `static func` 一律归入 "static" 桶（两者合计 38）。
    ("static / static func 行数",    lambda s: s["head"]["static"], 38),
    # ★ 曾为 1（`"_stacks_changed_%d" % stackType`）；2026-09-28 该行改为
    #   EventType 反查拼接（修 Buff 信号名断裂）→ 全库归 0
    ("String 格式化 % 行数",          lambda s: s["expr"]["% 字符串格式化"], 0),
    ("is 类型检查 行数",              lambda s: s["expr"]["is 类型检查"], 24),
    # ★ 54→55 / 62→64 / 55→56：SALVAGE_FUNCS 点名抢救（MagicRing.sortEffects/
    #   randEffects 等）给产物新增了真实代码行 —— RingEffect.new()、
    #   ringTypes/effects.push_back、stones.empty() 等回归产物。
    (".new( 行数",                   lambda s: s["expr"][".new("], 55),
    (".size() 调用次数",             lambda s: s["calls"]["size"], 63),
    (".push_back() 调用次数",        lambda s: s["calls"]["push_back"], 64),
    (".empty() 调用次数",            lambda s: s["calls"]["empty"], 56),
    ("Vector2 出现次数",             lambda s: s["occ"]["Vector2"], 198),
    ("Color 出现次数",               lambda s: s["occ"]["Color"], 51),
    ("Vector3 出现次数",             lambda s: s["occ"]["Vector3"], 0),
    ("** 幂 行数",                   lambda s: s["ops"]["** 幂"], 0),
    ("@ 装饰器 行数",                 lambda s: s["ops"]["@ 装饰器"], 0),
]


def verify(st):
    print("=== 断言 gd_to_py.py 文档引用的语法面数字 ===")
    print("扫描 %d 个 .gd 文件，%d 行\n" % (st["nfiles"], st["nlines"]))
    bad = []
    for desc, fn, want in CLAIMS:
        got = fn(st)
        ok = (got == want)
        print("  %-30s 期望 %5s  实为 %5s   %s" % (desc, want, got, "✓" if ok else "✗"))
        if not ok:
            bad.append((desc, want, got))
    print()
    if bad:
        for desc, want, got in bad:
            print("  ✗ %s：文档写 %s，实为 %s —— 文档或转写规则需要复核" % (desc, want, got))
        print("\nSURVEY_VERIFY: FAIL (%d 项)" % len(bad))
        return 1
    print("SURVEY_VERIFY: PASS（%d 项全对）" % len(CLAIMS))
    return 0


def main():
    ap = argparse.ArgumentParser(description="枚举 gd_core 语法面 / 断言文档数字")
    ap.add_argument("--dirs", default=",".join(DEFAULT_DIRS))
    ap.add_argument("--verify", action="store_true", help="只断言 gd_to_py.py 引用的数字")
    args = ap.parse_args()

    dirs = [d.strip() for d in args.dirs.split(",") if d.strip()]
    src = load(dirs)
    st = scan(src)

    if args.verify:
        return verify(st)

    print("扫描 %d 个 .gd 文件，%d 行\n" % (st["nfiles"], st["nlines"]))
    print("── 1) 行首关键字 ──")
    for k, v in st["head"].most_common():
        print("  %-14s %6d   e.g. %s" % (k, v, st["head_ex"][k][0]))

    print("\n── 2) 表达式级构造（行数） ──")
    for k, v in st["expr"].most_common():
        if v:
            print("  %-22s %6d" % (k, v))
    zero = [k for k, v in st["expr"].items() if not v]
    if zero:
        print("  （0 处：%s）" % "、".join(zero))

    print("\n── 3) 出现最多的成员调用（前 60） ──")
    for k, v in st["calls"].most_common(60):
        print("  %-22s %6d" % (k, v))

    print("\n── 4) 特殊运算符（行数） ──")
    for k, v in st["ops"].items():
        print("  %-16s %6d" % (k, v))

    print("\n── 5) 类型出现次数（词边界） ──")
    for k, v in st["occ"].items():
        print("  %-16s %6d" % (k, v))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
