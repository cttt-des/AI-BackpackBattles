# -*- coding: utf-8 -*-
"""scan_item_symbols.py — 统计物品脚本里单例成员的具体用法

为 tools/build_item_scripts.py 的符号映射表提供依据。
"""
from __future__ import annotations

import collections
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, "decompiled_full", "Items")

WATCH = ["Game", "ItemBook", "Util", "EventBus", "Sound", "ObjectPool",
         "Character", "DamageSource", "DamageResult", "ItemPool", "CraftingManager",
         "Global", "SoundManager", "Effects", "CustomRules", "Logger"]

MEMBER_RE = {
    w: re.compile(r"(?<![\w.])" + w + r"\.([A-Za-z_]\w*)") for w in WATCH
}


def collect():
    out = {}
    for dirpath, _dirs, files in os.walk(SRC):
        for fn in files:
            if fn.endswith(".gd") and fn != "Item.gd":
                path = os.path.join(dirpath, fn)
                rel = os.path.relpath(path, SRC).replace(os.sep, "/")
                with open(path, encoding="utf-8", errors="replace") as fh:
                    out[rel] = fh.read()
    return out


def clean(body):
    body = re.sub(r"#[^\n]*", "", body)
    body = re.sub(r'"(?:[^"\\]|\\.)*"', '""', body)
    return body


def main() -> int:
    scr = collect()
    for w in WATCH:
        members = collections.Counter()
        files = collections.defaultdict(set)
        for rel, body in scr.items():
            for m in MEMBER_RE[w].finditer(clean(body)):
                members[m.group(1)] += 1
                files[m.group(1)].add(rel)
        if not members:
            continue
        print("=== %s. 成员用法（%d 种） ===" % (w, len(members)))
        for k, v in members.most_common(30):
            print("  %-32s %4d 次  %d 文件" % (k, v, len(files[k])))
        print()
    return 0


if __name__ == "__main__":
    sys.exit(main())
