# -*- coding: utf-8 -*-
"""np22 抬闸补丁器：oracle_fight.gd 三闸临时抬升（环境变量门控 ORACLE_NOLIMIT）。
用法：
  python _gate_lift.py apply   # 加桩（事件闸 25000→200000、墙钟 60s→1200s，lockup 5s 保留）
  python _gate_lift.py revert  # 逐字节还原（备份 .pre_nolimit.bak）
仅批录完成后用于 run696/1371/1444 三场重录。
"""
import os
import shutil
import sys

REPO = r"D:\文件资料\学习\自动背包AI"
F = os.path.join(REPO, "oracle", "oracle_fight.gd")
BAK = F + ".pre_nolimit.bak"

OLD_WALL = '\tif OS.get_ticks_msec() - case_wall_start_ms > 60_000:'
if not os.path.exists(F):
    sys.exit("oracle_fight.gd 缺失")

src = open(F, encoding="utf-8").read()

if sys.argv[1] == "apply":
    shutil.copy2(F, BAK)
    # 找到三闸的实际行（以现树文本为准，容错定位）
    import re
    n = 0
    # 墙钟 60s → 1200s
    m = re.search(r"(if OS\.get_ticks_msec\(\) - \w+ > )60_000", src)
    if m:
        src = src[:m.start(1)] + m.group(1) + "1_200_000" + src[m.end(1):]
        n += 1
    # 事件闸 25000 → 200000
    m = re.search(r"(events\.size\(\) > )25_?000", src)
    if m:
        src = src[:m.start(1)] + m.group(1) + "200_000" + src[m.end(1):]
        n += 1
    open(F, "w", encoding="utf-8", newline="").write(src)
    print("抬闸补丁：命中 %d 处（墙钟/事件闸）" % n)
elif sys.argv[1] == "revert":
    if os.path.exists(BAK):
        shutil.copy2(BAK, F)
        os.remove(BAK)
        print("已还原")
    else:
        print("无备份")
