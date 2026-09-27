#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""run_item_parse.py — 运行物品脚本全量解析并归类错误

Godot 每个脚本只报**首个**解析错误，且错误只走控制台（GDScript 拿不到）。
本脚本运行 gd_core_test/ItemParseAll.gd，把控制台输出按「错误类型 → 出现次数 → 样例文件」
归类，供 tools/build_item_scripts.py 逐类修。

用法：
    python tools/run_item_parse.py            # 只归类，打印 top 错误
    python tools/run_item_parse.py --full     # 同时打印每条错误原文
"""
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GODOT = os.path.join(ROOT, "output", "godot36", "Godot_v3.6-stable_win64.exe")
TEST_PROJ = os.path.join(ROOT, "gd_core_test")

# 退出期噪声
_NOISE_KEYS = (
    "Godot Engine v", "OpenGL ES", "Async. shader",
    "ObjectDB instances leaked", "Resources still in use",
    "_first != nullptr", "at: ~List", "at: cleanup", "at: clear",
    "WARNING: Script", "scripts/script_debugger", "core/script_debugger",
    "print_error", "print_stray_nodes", "print_error_messages",
    "system/", "ObjectDB", "glad", "video/", "drivers/",
)

# Godot 3 报错格式为两行：
#   SCRIPT ERROR: Parse Error: The identifier "foo" isn't declared in the current scope.
#             at: GDScript::reload (res://gd_core_items/Bag.gd:14)
_RE_MSG = re.compile(r"SCRIPT ERROR: Parse Error:\s*(?P<msg>.*)$")
_RE_AT = re.compile(r"at:\s*GDScript::reload\s*\((?P<file>res://[^:)]+):(?P<line>\d+)\)")


def _decode(raw: bytes) -> str:
    for enc in ("utf-8", "cp936"):
        try:
            return raw.decode(enc)
        except UnicodeDecodeError:
            continue
    return raw.decode("utf-8", errors="replace")


def _key_of(msg: str) -> str:
    """把具体错误归一成「类型键」，同类错误合并计数。"""
    m = re.search(r'The identifier "([^"]+)"', msg)
    if m:
        return 'identifier "%s"' % m.group(1)
    m = re.search(r'Function "([^"]+)" not found', msg)
    if m:
        return 'function "%s" not found' % m.group(1)
    m = re.search(r'Identifier "([^"]+)" not found', msg)
    if m:
        return 'identifier "%s" not found' % m.group(1)
    m = re.search(r'The function signature doesn\'t match', msg)
    if m:
        return "function signature mismatch"
    m = re.search(r"Expected ([^,]+), got", msg)
    if m:
        return "expected-token: %s" % m.group(1)
    for pat in (
        "Not a valid type", "Unindent does not match",
        "Indented block expected", "Unexpected indentation",
        "Expected end of statement", "Mixed use of tabs and spaces",
        "Standalone expression", "A non-void function must return",
        "Too many arguments", "Not enough arguments",
        "Cannot use a null instance", "Invalid argument",
        "Only the parent class", "cannot be used as a", "has no member",
        "The member", "Cannot assign a value", "Can't assign",
        "Invalid operands", "Cyclic", "cyclic",
    ):
        if pat in msg:
            return "%s: %s" % (pat, msg[:70])
    return msg[:90]


def main() -> int:
    full = "--full" in sys.argv
    cmd = [GODOT, "--no-window", "--audio-driver", "Dummy",
           "--path", TEST_PROJ, "--script", "res://ItemParseAll.gd"]
    p = subprocess.run(cmd, cwd=ROOT, capture_output=True)
    out = _decode((p.stdout or b"") + (p.stderr or b""))
    lines = out.splitlines()

    groups = {}       # key -> {(file,line): msg}
    pending = None    # ★ Godot 的顺序是「先 SCRIPT ERROR 消息，后 at: 位置」。
    #                     必须先把消息存起来、等 at: 行到了再配对；
    #                     若反过来按「at: 行设置上下文、下一条消息归属它」配对，
    #                     归属会整体**错位一行**（样本文件/行号全错）。
    total = 0
    for raw in lines:
        s = raw.strip()
        if not s:
            continue
        if any(k in s for k in _NOISE_KEYS):
            continue
        m = _RE_AT.search(s)
        if m:
            loc = (m.group("file"), int(m.group("line")))
            if pending is not None:
                groups.setdefault(_key_of(pending), {})[loc] = pending
                total += 1
                pending = None
            continue
        m = _RE_MSG.search(s)
        if m:
            pending = m.group("msg").strip()
            continue

    print("=" * 70)
    print("物品脚本解析错误归类（Godot 每文件只报首个错误）")
    print("=" * 70)
    print("错误条目总数：%d，类型数：%d" % (total, len(groups)))
    print()
    print("--- 按受影响文件数排序 ---")
    for key, items in sorted(groups.items(), key=lambda kv: -len(kv[1])):
        files = sorted({f for f, _ in items})
        sample = min((l for f, l in items if f == files[0]), default=0)
        print("%4d  %-58s  例：%s:%d" % (len(files), key, files[0], sample))
        if full:
            for (f, ln) in files[:6]:
                print("        %s:%d  %s" % (f, ln, items[(f, ln)]))

    print()
    print("--- 完整失败清单见 gd_core_test/item_parse_result.txt ---")
    return 0


if __name__ == "__main__":
    sys.exit(main())
