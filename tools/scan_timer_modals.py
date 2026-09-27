# -*- coding: utf-8 -*-
"""scan_timer_modals.py — 统计物品脚本里的「计时器模态」

原版物品用 `$XxxTimer` 节点做战斗计时（buff 时长/冷却门），由 tscn 的
`timeout` 信号连到行为方法。无头内核里必须换成虚拟计时器，否则这类 buff
会「开了永不结束」。本工具量化规模并给出每个计时器的 wait_time 与连接目标。
"""
from __future__ import annotations

import collections
import io
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, "decompiled_full", "Items")

TIMER_DECL_RE = re.compile(r"^\s*onready\s+var\s+([A-Za-z_]\w*)\s*:?=\s*\$(.+)$", re.M)
TIMER_USE_RE = re.compile(r"(?<![\w.])([A-Za-z_]\w*)\s*\.\s*(start|stop|get_time_left|time_left|one_shot|wait_time)\b")


def collect():
    gd, tscn = {}, {}
    for dirpath, _dirs, files in os.walk(SRC):
        for fn in files:
            path = os.path.join(dirpath, fn)
            rel = os.path.relpath(path, SRC).replace(os.sep, "/")
            try:
                with io.open(path, encoding="utf-8", errors="replace") as fh:
                    body = fh.read()
            except OSError:
                continue
            if fn.endswith(".gd"):
                gd[rel] = body
            elif fn.endswith(".tscn"):
                tscn[rel] = body
    return gd, tscn


def main() -> int:
    gd, tscn = collect()

    # 1. 哪些模态名以 Timer 结尾（＝计时器节点）
    timer_name_re = re.compile(r"Timer$")
    timers = collections.defaultdict(set)      # 模态名 -> 声明所在文件
    for rel, body in gd.items():
        for m in TIMER_DECL_RE.finditer(body):
            name, path = m.group(1), m.group(2)
            if timer_name_re.search(name) or "Timer" in path:
                timers[name].add(rel)

    print("=== 以 Timer 形态声明的模态（%d 个） ===" % len(timers))
    for name in sorted(timers):
        print("  %-26s 声明于 %d 个文件" % (name, len(timers[name])))

    # 2. 每个计时器在行为里的用法（start / stop / get_time_left）
    uses = collections.Counter()
    use_files = collections.defaultdict(set)
    for rel, body in gd.items():
        if rel == "Item.gd":
            continue
        code = re.sub(r"#[^\n]*", "", body)
        for m in TIMER_USE_RE.finditer(code):
            name, method = m.group(1), m.group(2)
            if name in timers:
                uses["%s.%s" % (name, method)] += 1
                use_files["%s.%s" % (name, method)].add(rel)

    print("\n=== 计时器用法统计 ===")
    for k, v in uses.most_common(40):
        print("  %-34s %3d 次  %d 文件" % (k, v, len(use_files[k])))

    # 3. 计时器总开关：有多少物品脚本引用了任一计时器
    touching = set()
    for rel, body in gd.items():
        if rel == "Item.gd":
            continue
        code = re.sub(r"#[^\n]*", "", body)
        for name in timers:
            if re.search(r"(?<![\w.])" + re.escape(name) + r"\b", code):
                touching.add(rel)
    print("\n引用了任一计时器的物品脚本：%d" % len(touching))
    for rel in sorted(touching)[:40]:
        print("   %s" % rel)

    # 4. tscn 侧：Timer 节点的 wait_time / one_shot / timeout 连接
    print("\n=== tscn 里的 Timer 配置与 timeout 连接（样例 25） ===")
    shown = 0
    conn_re = re.compile(r'\[connection[^\]]*signal="timeout"[^\]]*\]')
    node_re = re.compile(r'\[node name="([^"]*Timer[^"]*)"[^\]]*\]\s*\n((?:[a-z_]+ = [^\n]*\n)*)')
    for rel in sorted(tscn):
        body = tscn[rel]
        for m in node_re.finditer(body):
            tname, props = m.group(1), m.group(2)
            wt = re.search(r"wait_time = ([\d.]+)", props)
            os_ = re.search(r"one_shot = (true|false)", props)
            as_ = re.search(r"autostart = (true|false)", props)
            if wt:
                print("  %-40s %-22s wait=%-7s one_shot=%-6s autostart=%s"
                      % (rel, tname, wt.group(1),
                         os_.group(1) if os_ else "-",
                         as_.group(1) if as_ else "-"))
                shown += 1
                if shown >= 25:
                    break
        if shown >= 25:
            break
    return 0


if __name__ == "__main__":
    sys.exit(main())
