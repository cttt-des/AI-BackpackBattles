# -*- coding: utf-8 -*-
"""enrich_split_params.py — 修复 battle_items.json 具名参数的 CSV 逗号格合并缺失

引擎真值（decompiled_full/Sheets/ItemBook.gd:858-868）：ItemBook 逐 p1..p10 列
解析物品参数，**含逗号的单元格按 "," 拆分为多个具名参数**，每段 "值:名"：

    if "," in colStr:
        var paramSubList = colStr.split(",")
        for split in paramSubList:
            var split2 = split.split(":")
            var paramVal = float(split2[0])
            item.addNamedParam(split2[1], paramVal)
            item.params.push_back(paramVal)
            paramI += 1

battle_items.json 的具名参数生产链只按 ":" 切了一次（取首段值为值、其余整体为
名），把整格压成一个垃圾键——受影响物品（proper csv 解析实测共 3 件）：

    Pine Protector  "5:maxspikes,1:maxspikes_food" → {maxspikes:5, maxspikes_food:1}
    Magic Ring      "4:poison,3:cold,2:blind" 等 4 格 → poison/cold/blind/lucky/
                    regeneration/spikes/mana/heat/vampirism/empower 各归其位
    Superior Ring   同 Magic Ring

后果实证（r2_0 任务，run808/809/810/811/815 五场 oracle≠gdcore，首分歧
idx=32/24/21/90/10）：SpikedShield.beforeBlock 的
`maxSpikes = getP("maxspikes") + getP("maxspikes_food")*N` 双双取 0 →
spikesLeft=0 恒 gate → Pine Protector 全场 0 次 giveSpikes（oracle 9/18/24/28/18
次）；格挡面（damblock 减伤 / drainStamina / activate）两侧全等，唯独 104 入栈
事件缺失，连带每次入栈 getNextFreeLabelPosition 2 抽的表现层链消耗缺失 → RNG
流错位（run808 idx36 Cheese Goobert 随机 buff oracle=Empower+Spikes vs
gd=Lucky+Mana）。

修复方式：把合并键逆向还原成 CSV 单元格（值 + ":" + 键，恰为生产链的逆）、按
ItemBook.gd:858-868 语义拆成独立具名参数写回，**并与 decompiled_full/Sheets/
CSV/ItemData_e.csv（csv 模块完整解析，含引号格）逐格对账**——对不上即中止不
写库。params 位置数组本就正确（首段值在位），不动。

消费面：gd_core/CoreItemData.gd fromDict 原样收 named_params（键即真值），
gd_core_py 同（gen 管线转写，无需另改）；simulator/gd_core_engine.py:96 与
gd_core_test/OracleAlignBattle.gd:192（item_battle_fixture.json descr.namedParams）
两侧装载点各自受益。改完须重生成：
    python tools/gen_gd_core_data.py      # assets/gd_core_runtime.json（py 侧）
    python tools/gen_lineup_fixture.py    # gd_core_test/item_battle_fixture.json（gd 侧）

用法：
  python tools/enrich_split_params.py            # 写库（自动 .bak 备份）
  python tools/enrich_split_params.py --check    # 只报告受影响物品与对账结果
"""
from __future__ import annotations

import csv
import json
import os
import shutil
import sys
from datetime import datetime

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
# ★ np23 data_r3：对账源切 oracle 语料版（1.1.9 录制真值）。受影响 3 件的
#   p1..p10 列在两 CSV 间逐格全等（53 行版本差不含它们），切源不改值，
#   只统一战斗数据链 provenance（与 enrich_stack_flags/enrich_unique_pool 同口径）。
CSV_PATH = os.path.join(ROOT, "oracle", "Sheets", "CSV", "ItemData.csv")
DB_PATH = os.path.join(ROOT, "assets", "battle_items.json")

PARAM_COLS = ["p%d" % i for i in range(1, 11)]


def parse_cell(cell: str):
    """ItemBook.gd:858-868 的 Python 对应：逗号格 → [(值, 名), ...]（保序）。

    仅对**含逗号**的格生效（无逗号格走 getFloat/getParamName 单参数支，本工具
    不碰）。段内必须恰好一个 ":"（与原版 split(":")[0]/[1] 同口径）。
    """
    if "," not in (cell or ""):
        return None
    out = []
    for seg in cell.split(","):
        parts = seg.split(":")
        if len(parts) != 2:
            raise SystemExit("CSV 参数格段 %r 不是「值:名」形态（ItemBook.gd:862 口径）"
                             % seg)
        out.append((float(parts[0]), parts[1]))
    return out


def main():
    check_only = "--check" in sys.argv
    rows = {}
    with open(CSV_PATH, encoding="utf-8-sig") as f:
        for r in csv.DictReader(f):
            rows[r["name"]] = r
    print("oracle ItemData.csv: %d 行" % len(rows))

    db = json.load(open(DB_PATH, encoding="utf-8"))
    items = db.get("items", db)
    touched = changed = 0
    for key, v in items.items():
        np = v.get("named_params") or {}
        merged = {k: val for k, val in np.items() if "," in k}
        if not merged:
            continue
        touched += 1
        r = rows.get(key)
        if r is None:
            raise SystemExit("%s：CSV 缺行，无法对账（拒绝盲拆）" % key)
        # CSV 真值：该行全部含逗号的 p 格 → [(值,名)...] 列表集合
        csv_cells = []
        for col in PARAM_COLS:
            parsed = parse_cell(r.get(col, "") or "")
            if parsed is not None:
                csv_cells.append(parsed)
        # 逆向还原 + 对账：合并键 = 单元格去掉首个 ":" 前段的剩余整体
        for k, val in merged.items():
            cell = "%s:%s" % (repr(float(val)) if float(val) != int(float(val))
                              else int(float(val)), k)
            want = parse_cell(cell)
            if want not in csv_cells:
                raise SystemExit(
                    "%s：还原格 %r 拆得 %r，与 CSV 真值 %r 不符（拒绝写库）"
                    % (key, cell, want, csv_cells))
            print("  %s: %r:%s → %s" % (
                key, val, k,
                ", ".join("%s=%s" % (n, x) for x, n in want)))
            if not check_only:
                # 原位替换，保序：以键值对列表重建（dict 保持插入序，json 落盘同序）
                idx = list(np.keys()).index(k)
                flat = list(np.items())
                flat[idx:idx + 1] = [(n, x) for x, n in want]
                np.clear()
                np.update(flat)
                changed += 1

    print("受影响物品 %d 件，拆分键 %d 个" % (touched, changed))
    if check_only:
        return
    if changed:
        stamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        shutil.copy2(DB_PATH, "%s.bak_%s" % (DB_PATH, stamp))
        json.dump(db, open(DB_PATH, "w", encoding="utf-8"),
                  ensure_ascii=False, indent=1)
        print("已写出 %s（备份 .bak_%s）" % (DB_PATH, stamp))
    else:
        print("无变更，不写库")


if __name__ == "__main__":
    main()
