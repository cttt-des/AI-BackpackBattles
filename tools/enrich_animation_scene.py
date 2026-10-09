#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""enrich_animation_scene.py — 把「物品有无攻击动画场景」写进 battle_items.json

缺口（docs/alignment_fix_workflow.md 阶段1 逐行对齐实证）：
  `ItemDescriptor.animationScene`（ItemBook.gd:788-802 按**文件存在性**装载：
  Items/Animations/<名无空格>Animation.tscn → Items/Exclusive/Animations/<…>），
  是 Item.playAnimation 的闸（Item.gd:5345-5346）。有动画场景的物品每次 activate()
  会经 ItemAnimation.intialize 消耗 4 抽 Util.rng（randomizePosition 3 抽 +
  playback_speed 1 抽，Items/Animations/ItemAnimation.gd:24-35）——纯表现，但
  真实推进判定链；内核此前无此字段 ⇒ 恒不消耗 ⇒ 电荷/攻击密集局从开战批量起
  链位错位。

产出：battle_items.json 每件物品追加 `has_animation_scene`（bool）。

用法：
  python tools/enrich_animation_scene.py            # 写入（幂等）
  python tools/enrich_animation_scene.py --check    # 只校验
"""
from __future__ import annotations

import io
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

DB_PATH = os.path.join(ROOT, "assets", "battle_items.json")
# 与 ItemBook.gd:788-802 同源的探测根（1.1.8 运行版反编译树；正式包
# loadExclusiveContent()==true ⇒ Exclusive/Animations 分支恒可达）
ANI_DIRS = [
    os.path.join(ROOT, "extracted_running", "decomp", "Items", "Animations"),
    os.path.join(ROOT, "extracted_running", "decomp", "Items", "Exclusive", "Animations"),
]


def has_animation_scene(key: str) -> bool:
    name = key.replace(" ", "")
    for d in ANI_DIRS:
        if os.path.exists(os.path.join(d, "%sAnimation.tscn" % name)):
            return True
    return False


def main() -> int:
    check_only = "--check" in sys.argv
    db = json.load(io.open(DB_PATH, encoding="utf-8"))
    changed = 0
    for key, entry in db["items"].items():
        want = has_animation_scene(key)
        if bool(entry.get("has_animation_scene", False)) != want:
            entry["has_animation_scene"] = want
            changed += 1
    n = sum(1 for e in db["items"].values() if e.get("has_animation_scene"))
    print("动画场景：%d / %d 件物品有 Animation.tscn；需更新 %d 件"
          % (n, len(db["items"]), changed))
    if check_only:
        return 1 if changed else 0
    if changed:
        with io.open(DB_PATH, "w", encoding="utf-8", newline="\n") as fh:
            json.dump(db, fh, ensure_ascii=False, indent=1)
            fh.write("\n")
        print("已写入 %s" % os.path.relpath(DB_PATH, ROOT))
    else:
        print("battle_items.json 已同步")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
