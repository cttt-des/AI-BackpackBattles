# -*- coding: utf-8 -*-
"""scan_tscn_connections.py — 统计物品 tscn 里的信号连接

无头内核没有场景树，物品脚本原先靠 tscn 连接驱动的战斗回调（尤其是计时器
`timeout` / `multi_timeout` → 行为方法）必须由装配层显式重建。
本工具量化规模并给出连接清单，作为转译器的输入。
"""
from __future__ import annotations

import collections
import io
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, "decompiled_full", "Items")

CONN_RE = re.compile(
    r'\[connection\s+signal="([^"]+)"\s+from="([^"]+)"\s+to="([^"]+)"\s+method="([^"]+)"\s*\]')
NODE_RE = re.compile(r'\[node name="([^"]+)"\s+type="([^"]+)"([^\]]*)\]')
SCRIPT_RE = re.compile(r'script = ExtResource\(\s*(\d+)\s*\)')
EXT_RE = re.compile(r'\[ext_resource path="([^"]+)" type="[^"]+" id=(\d+)\]')


def main() -> int:
    files = []
    for dirpath, _dirs, fs in os.walk(SRC):
        for fn in fs:
            if fn.endswith(".tscn"):
                files.append(os.path.join(dirpath, fn))

    sig_cnt = collections.Counter()
    to_self = 0
    to_other = 0
    timer_conns = []
    per_file = collections.Counter()
    node_types = collections.Counter()
    timer_scripts = collections.Counter()

    for path in files:
        rel = os.path.relpath(path, SRC).replace(os.sep, "/")
        with io.open(path, encoding="utf-8", errors="replace") as fh:
            body = fh.read()
        exts = {m.group(2): m.group(1) for m in EXT_RE.finditer(body)}
        nodes = {}
        for m in NODE_RE.finditer(body):
            nodes[m.group(1)] = (m.group(2), m.group(3))
            node_types[m.group(2)] += 1
        for m in CONN_RE.finditer(body):
            sig, frm, to, method = m.groups()
            sig_cnt[sig] += 1
            per_file[rel] += 1
            if to == ".":
                to_self += 1
            else:
                to_other += 1
            # 计时器相关：from 节点类型是 Timer，或信号含 timeout
            ttype, props = nodes.get(frm, ("?", ""))
            if ttype == "Timer" or "timeout" in sig:
                sid = SCRIPT_RE.search(props)
                tscript = exts.get(sid.group(1), "Timer") if sid else "Timer"
                timer_scripts[os.path.basename(tscript)] += 1
                timer_conns.append((rel, frm, sig, method, to, tscript))

    print("tscn 数：%d，连接总数：%d（to=\".\" %d，to 其他 %d）"
          % (len(files), sum(sig_cnt.values()), to_self, to_other))

    print("\n=== 信号名分布（前 25） ===")
    for k, v in sig_cnt.most_common(25):
        print("  %-30s %d" % (k, v))

    print("\n=== 节点类型分布（前 20） ===")
    for k, v in node_types.most_common(20):
        print("  %-26s %d" % (k, v))

    print("\n=== 计时器连接（%d 条），按脚本归类 ===" % len(timer_conns))
    for k, v in timer_scripts.most_common():
        print("  %-24s %d" % (k, v))

    print("\n=== 计时器连接明细（前 45） ===")
    for rel, frm, sig, method, to, ts in timer_conns[:45]:
        print("  %-40s %-20s %-16s -> %s%s  [%s]"
              % (rel, frm, sig, method, "" if to == "." else ("@" + to), ts))
    return 0


if __name__ == "__main__":
    sys.exit(main())
