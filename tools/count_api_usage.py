# -*- coding: utf-8 -*-
"""count_api_usage.py — 数 GDScript 源码里某个符号的**实际调用点**（代码 vs 注释分开数）。

为什么需要它
────────────
`gd_core_py/_rt.py` 里散着大量「项目里 0 处调用」的断言，用来给「已实现的保底接口」
或「刻意保持 no-op 的接口」背书。但这类断言**没有任何东西在守**：
写的时候可能是真的，后来某件物品用上了就变成假的，而**假断言不会报错**。

本仓库已经栽过一次同类跟头：生成物里写死的「判定路径缺口为 0」曾是假断言，
直到某天才偶然变成真的。教训是 —— 数字必须现算，结论必须可复现。

于是把「数调用点」这件事做成工具：注释里的每一句「N 处调用」都可以当场复算。

用法
────
    python tools/count_api_usage.py randomize hash randfn Color.white
    python tools/count_api_usage.py --call randomize randfn hash
    python tools/count_api_usage.py --dirs gd_core,gd_core_items --json

约定
────
- 默认扫 `gd_core/` + `gd_core_items/`（即**转写输入**，不是转写产物）
- `--call` 时只数 `name(` 形式（调用点）；否则数任何词边界出现
- 注释与字符串里的命中单独计数并默认**不计入** code
- `#` 注释按 GDScript 规则（`#` 到行尾）；字符串支持单引号 / 双引号 / 各自的三个连写
"""
import argparse
import json
import os
import re
import sys

sys.stdout.reconfigure(encoding="utf-8")

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def strip_comments_and_strings(src):
    """把源码切成 (code, comment, string) 三段文本。

    GDScript 的注释只有 `#` 到行尾，字符串有 ' " 和三引号。
    转义用 `\\`。不用正则是因为要正确跳过字符串里的 `#`。
    """
    code, comment, string = [], [], []
    i, n = 0, len(src)
    while i < n:
        ch = src[i]
        # 三引号
        if ch in "\"'" and src.startswith(ch * 3, i):
            q = ch * 3
            j = src.find(q, i + 3)
            j = n if j < 0 else j + 3
            string.append(src[i:j])
            i = j
            continue
        if ch in "\"'":
            j, k = i + 1, i
            while j < n:
                if src[j] == "\\":
                    j += 2
                    continue
                if src[j] == ch:
                    k = j
                    break
                if src[j] == "\n":      # 未闭合字符串，GDScript 会报错；这里就断在行尾
                    k = j - 1
                    break
                j += 1
            k = j if j >= n else k
            string.append(src[i:k + 1])
            i = k + 1
            continue
        if ch == "#":
            j = src.find("\n", i)
            j = n if j < 0 else j
            comment.append(src[i:j])
            i = j
            continue
        code.append(ch)
        i += 1
    return "".join(code), "".join(comment), "".join(string)


def iter_gd(dirs):
    for d in dirs:
        base = os.path.join(ROOT, d)
        if not os.path.isdir(base):
            continue
        for dirpath, _dirnames, filenames in os.walk(base):
            for fn in sorted(filenames):
                if fn.endswith(".gd"):
                    yield os.path.join(dirpath, fn)


def count_symbol(dirs, sym, as_call=False, bare=False):
    """返回 {code, comment, string, dotted, files:{rel: code_count}}。

    `bare=True` 时排除前置 `.` 的命中 —— 用来区分「全局内建」与「对象方法」：
      `randomize()`      = 全局内建（会破坏可复现性）
      `rng.randomize()`  = RandomNumberGenerator 的方法（正常用法）
    这两者混为一谈会得出完全相反的结论。
    """
    base = re.escape(sym) + (r"\s*\(" if as_call else r"\b")
    # 前置断言：`(?<![\w.])` 保证不是 `foo.name` / `foo.name(`
    rx_bare = re.compile((r"(?<![\w.])" + base) if bare else base)
    rx_any = re.compile(base)
    rx_dotted = re.compile(r"\.\s*" + base)
    out = {"code": 0, "comment": 0, "string": 0, "dotted": 0, "files": {}}
    for path in iter_gd(dirs):
        src = open(path, encoding="utf-8", errors="replace").read()
        code, comment, string = strip_comments_and_strings(src)
        out["dotted"] += len(rx_dotted.findall(code))
        c = len(rx_bare.findall(code))
        out["code"] += c
        out["comment"] += len(rx_bare.findall(comment))
        out["string"] += len(rx_bare.findall(string))
        if c:
            out["files"][os.path.relpath(path, ROOT).replace("\\", "/")] = c
    return out


def main():
    ap = argparse.ArgumentParser(description="数 GDScript 源码里符号的实际调用点")
    ap.add_argument("symbols", nargs="+", help="要数的符号，如 randomize / randfn / Color.white")
    ap.add_argument("--call", action="store_true", help="只数 `name(` 形式的调用点")
    ap.add_argument("--bare", action="store_true",
                    help="只数**裸**调用（前置不是 `.`）——区分全局内建 vs 对象方法")
    ap.add_argument("--dirs", default="gd_core,gd_core_items",
                    help="扫描目录（逗号分隔，相对项目根）")
    ap.add_argument("--json", action="store_true", help="输出 JSON")
    args = ap.parse_args()

    dirs = [d.strip() for d in args.dirs.split(",") if d.strip()]
    res = {}
    for sym in args.symbols:
        res[sym] = count_symbol(dirs, sym, args.call, args.bare)

    if args.json:
        print(json.dumps({"dirs": dirs, "as_call": args.call, "bare": args.bare,
                          "result": res}, ensure_ascii=False, indent=2))
        return 0

    mode = ("只数**裸**调用 name(（排除 x.name()）" if args.bare else
            "只数调用点 name(" if args.call else "词边界匹配")
    print("扫描目录：%s   （%s）" % (" + ".join(dirs), mode))
    print("%-26s %8s %8s %8s %8s   %s" % ("符号", "代码", "注释", "字符串", "点调用", "代码命中文件"))
    print("-" * 104)
    for sym in args.symbols:
        r = res[sym]
        files = r["files"]
        top = sorted(files.items(), key=lambda kv: -kv[1])[:3]
        desc = ", ".join("%s×%d" % (k.replace("gd_core_items/", "…/"), v) for k, v in top)
        if len(files) > 3:
            desc += " …(%d 个文件)" % len(files)
        print("%-26s %8d %8d %8d %8d   %s"
              % (sym, r["code"], r["comment"], r["string"], r["dotted"], desc or "—"))

    print()
    print("★ 判据：「代码」列才是真命中。注释列 >0 = 源码注释里也在提这个名字。")
    print("        「点调用」列 = 形如 `x.name` 的命中（--bare 已从「代码」里排除它们）。")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
