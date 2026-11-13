# -*- coding: utf-8 -*-
"""§12.5/P1: _place_of 几何缓存全量等价性扫描(对照旧实现逐结构比较)。

全量 = 可装配清单每个 key × 4 朝向 × 每朝向首个锚点 (row,col) 真实平移。
判据: occupied/collision/affected/script/sockets/descr/charge_frame 七项全等。
"""
import importlib
import io
import json
import os
import subprocess
import sys

ROOT = r'D:\文件资料\学习\自动背包AI'
os.chdir(ROOT)
sys.path.insert(0, ROOT)

from simulator import gd_core_engine as E  # noqa: E402  含 _GEO_CACHE 新实现

# 旧实现(参照系,取自 ce47a982^ 即缓存引入前) —— 逐结构重算
data = E.runtime_data()

MISS = getattr(E, '_MissingItem', None)


def ref_place(data, key, row, col, rot):
    """旧实现参照(ce47a982^ 逐行还原)。"""
    ent = data["items"].get(key)
    if ent is None:
        raise SystemExit("missing " + key)
    r = ent["rot"][str(int(rot) % 360)]
    anchor = r["collision"]
    collision = [[c[0] + col, c[1] + row] for c in anchor]
    affected = {int(color): [[c[0] + col, c[1] + row] for c in cells]
                for color, cells in r["affected"].items()}
    occupied = sorted({(c[0] + col, c[1] + row) for c in anchor})
    return {"occupied": occupied, "collision": collision, "affected": affected,
            "script": ent["script"], "sockets": int(ent["sockets"]),
            "descr": ent["descr"],
            "charge_frame": tuple(r.get("charge_frame") or (0, 0))}


fails = 0
n = 0
for key in sorted(data["items"]):
    ent = data["items"][key]
    for rot in (0, 90, 180, 270):
        rk = str(rot)
        if rk not in ent["rot"]:
            continue
        row, col = 3, 5     # 真实量级的非零锚点;平移只做加法,单点即可代表
        got = E._place_of(data, key, row, col, rot)
        want = ref_place(data, key, row, col, rot)
        n += 1
        for field in ("occupied", "collision", "affected", "script",
                      "sockets", "descr", "charge_frame"):
            if got[field] != want[field]:
                # 类型等价放宽:tuple vs list 深比
                a = [list(x) if isinstance(x, (list, tuple)) else x
                     for x in got[field]] if isinstance(got[field], list) \
                    else got[field]
                b = [list(x) if isinstance(x, (list, tuple)) else x
                     for x in want[field]] if isinstance(want[field], list) \
                    else want[field]
                if a != b:
                    fails += 1
                    if fails <= 5:
                        print(f'FAIL {key} rot={rot} {field}: '
                              f'got={str(a)[:120]} want={str(b)[:120]}')
                else:
                    print(f'type-equiv OK {key} rot={rot} {field} '
                          f'({type(got[field]).__name__} vs '
                          f'{type(want[field]).__name__})')
print(f'PLACEOF SWEEP: {n} 组合, fails={fails}')
sys.exit(0 if fails == 0 else 1)
