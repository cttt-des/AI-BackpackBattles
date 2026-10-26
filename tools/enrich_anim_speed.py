#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""enrich_anim_speed.py — 把每件物品攻击动画的 minSpeed/maxSpeed 写进 battle_items.json

缺口（r16 批 2 raw 双指针定谳，run604_r10）：
  ItemAnimation.gd:34 `playback_speed = Util.rng.randf_range(minSpeed, maxSpeed)`
  ——export 默认 0.8/1.2，各 <名>Animation.tscn 根节点可覆写（例：
  OnionCutterAnimation.tscn:117-118 minSpeed=0.7/maxSpeed=1.05）。内核
  CoreItem.gd:982 此前硬编码 randf_range(0.8,1.2)——抽数相同但**值**随域漂移，
  值经 delayed 动画时长链泄漏进触发相位（O 5.75 vs G 5.9833，14 ticks）。

产出：battle_items.json 每件物品追加 `anim_speed_min` / `anim_speed_max`
（float，缺省 0.8/1.2——无 Animation.tscn 或 tscn 未覆写时）。

用法：
  python tools/enrich_anim_speed.py            # 写入（幂等）
  python tools/enrich_anim_speed.py --check    # 只校验
"""
from __future__ import annotations

import io
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

DB_PATH = os.path.join(ROOT, "assets", "battle_items.json")
# ★ np23 data_r5：动画 tscn 源由 extracted_running/decomp（目录已不存在，探测恒空）
#   切到录制侧工程 oracle/Items（只读）。原两根布局（Items/Animations +
#   Items/Exclusive/Animations）在 oracle 树同构存活（86+75 个 tscn）。
ANI_DIRS = [
    os.path.join(ROOT, "oracle", "Items", "Animations"),
    os.path.join(ROOT, "oracle", "Items", "Exclusive", "Animations"),
]

DEFAULT_MIN, DEFAULT_MAX = 0.8, 1.2


def anim_tscn_path(key: str):
    name = key.replace(" ", "")
    for d in ANI_DIRS:
        p = os.path.join(d, "%sAnimation.tscn" % name)
        if os.path.exists(p):
            return p
    return None


def read_speeds(path: str):
    """读 tscn 根节点的 minSpeed/maxSpeed 覆写（未覆写返回 None）。"""
    txt = io.open(path, encoding="utf-8", errors="replace").read()
    mn = re.search(r"^minSpeed\s*=\s*([0-9.]+)\s*$", txt, re.M)
    mx = re.search(r"^maxSpeed\s*=\s*([0-9.]+)\s*$", txt, re.M)
    return (float(mn.group(1)) if mn else None,
            float(mx.group(1)) if mx else None)


def main() -> int:
    check_only = "--check" in sys.argv
    db = json.load(io.open(DB_PATH, encoding="utf-8"))
    changed = 0
    n_over = 0
    for key, entry in db["items"].items():
        p = anim_tscn_path(key)
        mn, mx = read_speeds(p) if p else (None, None)
        want_min = mn if mn is not None else DEFAULT_MIN
        want_max = mx if mx is not None else DEFAULT_MAX
        if (float(entry.get("anim_speed_min", DEFAULT_MIN)) != want_min
                or float(entry.get("anim_speed_max", DEFAULT_MAX)) != want_max):
            entry["anim_speed_min"] = want_min
            entry["anim_speed_max"] = want_max
            changed += 1
        if mn is not None or mx is not None:
            n_over += 1
    print("动画 speed 域：%d / %d 件覆写；需更新 %d 件"
          % (n_over, len(db["items"]), changed))
    if check_only:
        return 1 if changed else 0
    if changed:
        with io.open(DB_PATH, "w", encoding="utf-8", newline="\n") as fh:
            json.dump(db, fh, ensure_ascii=False, indent=1)
        print("已写入 %s" % DB_PATH)
    return 0


if __name__ == "__main__":
    sys.exit(main())
