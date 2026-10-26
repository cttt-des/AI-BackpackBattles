# -*- coding: utf-8 -*-
"""enrich_stack_flags.py — 从 ItemData_e.csv 的 gain/remove/use 列提取
gained/removed/usedStacks 位标志写入 battle_items.json。

引擎真值（decompiled_full/Sheets/ItemBook.gd:877-879）：
    item.gainedStacks = table.getFlags("gain", Item.Stack, line)
    item.removedStacks = table.getFlags("remove", Item.Stack, line)
    item.usedStacks = table.getFlags("use", Item.Stack, line)
Table.getFlags（Table.gd:38-44）：按 "," 分裂、去全部空格、逐 token 查
Item.Stack 枚举求和；枚举含聚合键 Buff/Debuff/BuffNoLuck（Item.gd:96-112）。

消费面：CoreItem.gd:5383 gainsStack / :5393 gainsBuffs（gainedStacks &
Stack.Buff）/ :5399 inflictsDebuffs——Toad/PoisonFrog 等
canAffect = gainsBuffs() or usesBuffs() 的阈值网络全靠它
（run575_r18 首分歧实证：Toad 对 Snake 幸运 16 的治疗 7 整条缺失）。

用法：
  python tools/enrich_stack_flags.py            # 写库（自动 .bak 备份）
  python tools/enrich_stack_flags.py --check    # 只报告覆盖率
"""
from __future__ import annotations

import csv
import json
import os
import shutil
import sys
from datetime import datetime

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
# ★ np23 data_r1：数据源切 oracle 语料版（1.1.9 录制真值）。gain/use/remove 三列
#   与 decompiled ItemData_e.csv 逐行全等（53 行参数 diff 中无此三列），切源不改
#   值，只把战斗数据链的 provenance 统一到语料版本。
CSV_PATH = os.path.join(ROOT, "oracle", "Sheets", "CSV", "ItemData.csv")
DB_PATH = os.path.join(ROOT, "assets", "battle_items.json")

# Item.gd:96-112 enum Stack（聚合键与位值原样照搬）
STACK_FLAGS = {
    "None": 0,
    "Block": 1,
    "Lucky": 2,
    "Regeneration": 4,
    "Vampirism": 8,
    "Spikes": 16,
    "Mana": 32,
    "Empower": 64,
    "Heat": 128,
    "Poison": 256,
    "Blind": 512,
    "Cold": 1024,
    "Buff": 128 + 64 + 32 + 16 + 8 + 4 + 2,       # 254
    "Debuff": 1024 + 512 + 256,                    # 1792
    "BuffNoLuck": 128 + 64 + 32 + 16 + 8 + 4,      # 252
}

COLUMNS = (("gain", "gained_stacks"), ("remove", "removed_stacks"),
           ("use", "used_stacks"))


def get_flags(value: str) -> int:
    """Table.gd:38-44 的 Python 对应（分裂/去空格/求和）。"""
    flags = 0
    for tok in (value or "").replace(" ", "").split(","):
        if tok != "":
            if tok not in STACK_FLAGS:
                raise SystemExit("未知 Stack 名 %r（列值 %r）：请核对 Item.gd:96-112"
                                 % (tok, value))
            flags += STACK_FLAGS[tok]
    return flags


def main():
    check_only = "--check" in sys.argv
    rows = {}
    with open(CSV_PATH, encoding="utf-8-sig") as f:
        for r in csv.DictReader(f):
            rows[r["name"]] = r
    print(f"oracle ItemData.csv: {len(rows)} 行")

    db = json.load(open(DB_PATH, encoding="utf-8"))
    items = db.get("items", db)
    covered = missing = changed = 0
    for key, v in items.items():
        r = rows.get(key)
        if r is None:
            missing += 1
            continue
        covered += 1
        for col, field in COLUMNS:
            want = get_flags(r.get(col))
            if int(v.get(field) or 0) != want:
                changed += 1
                if not check_only:
                    v[field] = want
    print(f"覆盖 {covered} / 缺失 {missing} / 位标志变更 {changed}")

    if check_only:
        return
    if changed:
        stamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        shutil.copy2(DB_PATH, f"{DB_PATH}.bak_{stamp}")
        json.dump(db, open(DB_PATH, "w", encoding="utf-8"), ensure_ascii=False, indent=1)
        print(f"已写出 {DB_PATH}（备份 .bak_{stamp}）")
    else:
        print("无变更，不写库")


if __name__ == "__main__":
    main()
