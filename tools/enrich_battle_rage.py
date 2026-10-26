# -*- coding: utf-8 -*-
"""enrich_battle_rage.py — 战怒描述符标记（hasBattleRageEffect）写入 battle_items.json

引擎真值（ItemBook.gd:1401，录制侧 oracle/Sheets/ItemBook.gd 同一规则）：
    item.hasBattleRageEffect = (descr.find("$rage[") != -1)
    descr = Util.tra(descriptionKey + "_DESCR")
descriptionKey：宝石走五阶分层名（ItemBook.gd:1363-1371），其余 = 物品名
（ItemBook.gd:1373-1374）。DESCR 行唯一来源 = oracle/Sheets/CSV/
ExclusiveItems.csv（Dialog/Interface 实测 0 行 _DESCR）；无 DESCR 行的物品
（如 Spiked Wall——其脚本自调 startBattleRage 但描述符旗按规则为 false）
tra 落空返回键名本身 → 不含 "$rage[" → false，与规则一致。

★ runtime dump 不可用说明：oracle/rage_dump_tmp.gd 为官方提取器（跑神谕工程
  ItemBook+Util.tra），但本环境 headless 启动该工程挂死（rc=124，autoload
  循环引用解析错误链，Util.gd:28 parse error → tra 断链）——如实记未跑成。
  静态口径 = 录制工程自身的 locale 表 ExclusiveItems.csv（Util.tra 的数据源）
  任一语言列含 "$rage[" 即真，与运行时规则逐字等价。
  实测标记集（16 件，两 CSV 版本间无 ExclusiveItems 差异面）：
  Badger Rune / Berserker Bag / Brass Knuckles / Busted Blade / Chain Whip /
  Deer Totem / Double Axe / Dragon Claws / Dragon Set / Dragonscale Armor /
  Dragonskin Boots / Extra Angy / Spiked Collar / Spiked Staff / Toolbox /
  Wolf Badge。

消费面（已就绪、此前数据恒缺）：CoreItemData.gd:317 fromDict 读
hasBattleRageEffect；CoreItem.gd:281-283 isBattleRageItem（Character.prepare
自动战怒挑选面）；两侧装载点 descriptor_of/_descriptor 已透传。verify_oracle
hints（tools/verify_oracle.py:874/905）明确将此列为 data 面缺口。

改完须重生成：
    python tools/gen_gd_core_data.py      # assets/gd_core_runtime.json
    python tools/gen_lineup_fixture.py    # gd_core_test/item_battle_fixture.json

用法：
  python tools/enrich_battle_rage.py            # 写库（自动 .bak 备份，只增不改）
  python tools/enrich_battle_rage.py --check    # 只报告标记集与命中
"""
from __future__ import annotations

import csv
import io
import json
import os
import shutil
import sys
from datetime import datetime

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CSV_PATH = os.path.join(ROOT, "oracle", "Sheets", "CSV", "ExclusiveItems.csv")
DB_PATH = os.path.join(ROOT, "assets", "battle_items.json")
MARKER = "$rage["


def rage_keys() -> set:
    """ItemBook.gd:1401 规则的静态等价：<_DESCR 行任一语言列含 $rage[ → 该物品。"""
    out = set()
    for r in csv.DictReader(io.open(CSV_PATH, encoding="utf-8-sig")):
        key = r.get("key") or ""
        if not key.endswith("_DESCR"):
            continue
        if any(MARKER in (v or "") for k, v in r.items() if k != "key"):
            out.add(key[: -len("_DESCR")])
    return out


def main() -> int:
    check_only = "--check" in sys.argv
    want = rage_keys()
    print("ExclusiveItems.csv 规则标记集：%d 件：%s"
          % (len(want), ", ".join(sorted(want))))

    db = json.load(io.open(DB_PATH, encoding="utf-8"))
    items = db.get("items", db)
    hit = [k for k in items if k in want]
    absent = sorted(want - set(items))
    already = [k for k in hit if items[k].get("has_battle_rage_effect")]
    print("battle_items 命中 %d 件（已标 %d）；CSV 有而库无 %s"
          % (len(hit), len(already), absent or "∅"))
    if check_only:
        return 0

    changed = 0
    for k in hit:
        if not items[k].get("has_battle_rage_effect"):
            items[k]["has_battle_rage_effect"] = True
            changed += 1
    if changed:
        stamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        shutil.copy2(DB_PATH, "%s.bak_%s" % (DB_PATH, stamp))
        json.dump(db, io.open(DB_PATH, "w", encoding="utf-8", newline="\n"),
                  ensure_ascii=False, indent=1)
        print("已写出 %s：新增标记 %d 件（备份 .bak_%s）" % (DB_PATH, changed, stamp))
    else:
        print("无变更，不写库")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
