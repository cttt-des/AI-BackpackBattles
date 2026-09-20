# -*- coding: utf-8 -*-
"""update_zh_names.py — 用游戏内置中文翻译（新解包 CSV）更新 battle_items.json 的 zh

真值源：decompiled_full/.assets/Sheets/CSV/{Items,Full,ExclusiveItems}.csv
的 zh_Hans_CN 列（游戏 1.0 内置简体中文）。名字行 = en 列无 $ 且长度 < 40。

匹配策略：
  1. 精确 en 名匹配（规范化空格/横杠）
  2. 手工核实的改名映射 RENAME_MAP（旧数据键名 → 新版官方名）

覆盖不到的物品（新版已改名且无法可靠对应、或已移除的旧物品）保留现值
（来自旧版官方翻译提取），并在报告中列出。

用法：
  python tools/update_zh_names.py           # 更新写库（自动 .bak）
  python tools/update_zh_names.py --check   # 只报告
"""
from __future__ import annotations

import csv
import json
import os
import shutil
import sys
from datetime import datetime

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CSV_DIR = os.path.join(ROOT, "decompiled_full", ".assets", "Sheets", "CSV")
DB_PATH = os.path.join(ROOT, "assets", "battle_items.json")

# 旧数据键名 → 新版官方名（逐一人工核实）
RENAME_MAP = {
    "Phoenix2": "Enraged Phoenix",           # Phoenix 孵化二阶段
    # 法术卷轴系列（效果一一对应：冰墙/黑暗爆发/重生/净化祝福）
    "Spell Scroll Ice": "Spell Scroll: Ice Block",
    "Spell Scroll Dark": "Spell Scroll: Dark Frenzy",
    "Spell Scroll Nature": "Spell Scroll: Regrowth",
    "Spell Scroll Light": "Spell Scroll: Blessing of Purity",
    "Engineer Box": "Engineer's Box",
}


def norm(s: str) -> str:
    # 去空格/横杠/下划线/冒号/撇号/句点（Artifact Stone: Heat、Thor's Hammer 类差异）
    for ch in " -_:.'’":
        s = s.replace(ch, "")
    return s.lower()


def load_official() -> dict:
    """en 名 -> zh_Hans_CN（名字行；en 含 $ 的为描述行，跳过）"""
    out = {}
    for fn in ("Items.csv", "Full.csv", "ExclusiveItems.csv"):
        path = os.path.join(CSV_DIR, fn)
        if not os.path.exists(path):
            continue
        with open(path, encoding="utf-8-sig") as f:
            for r in csv.reader(f):
                if len(r) >= 4 and r[1] and "$" not in r[1] and len(r[1]) < 40 and r[3].strip():
                    out.setdefault(r[1].strip(), r[3].strip())
    return out


def main():
    check_only = "--check" in sys.argv
    official = load_official()
    by_norm = {norm(k): (k, v) for k, v in official.items()}
    print(f"官方翻译条目: {len(official)}")

    db = json.load(open(DB_PATH, encoding="utf-8"))
    items = db.get("items", db)
    same = updated = uncovered = 0
    uncovered_list = []
    for key, v in items.items():
        target = official.get(key) or by_norm.get(norm(key))
        if target is None and key in RENAME_MAP:
            target = official.get(RENAME_MAP[key])
        if target is None:
            uncovered += 1
            uncovered_list.append(key)
            continue
        cur = v.get("zh") or ""
        if cur == target:
            same += 1
        else:
            updated += 1
            if not check_only:
                v["zh"] = target
    print(f"一致 {same} / 更新 {updated} / 官方无对应（保留现值）{uncovered}")
    if uncovered_list:
        print("无对应物品:", ", ".join(sorted(uncovered_list)))

    if check_only or not updated:
        return
    stamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    shutil.copy2(DB_PATH, f"{DB_PATH}.bak_{stamp}")
    json.dump(db, open(DB_PATH, "w", encoding="utf-8"), ensure_ascii=False, indent=1)
    print(f"已写出 {DB_PATH}（备份 .bak_{stamp}）")


if __name__ == "__main__":
    main()
