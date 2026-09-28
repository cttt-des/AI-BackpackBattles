#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
gen_gd_core_data.py — 把 gd_core 内核跑一局所需的**全部外部数据**编译成单一 JSON

存在的理由
==========
`simulator/gd_core_engine.py` 要在**打包后的 exe 里**装配阵容。而闸门 8
（`gd_core_test/LineupBattle.gd`）与 `tools/run_gd_py.py` 的装配数据来自
`tools/gen_lineup_fixture.py`，那个模块在 **import 时**就要读三处磁盘：

    gd_core/CoreConst.gd          枚举真值源（解析文本）
    gd_core_items/**.gd           脚本路径索引（os.walk 502 个文件）
    extracted/Items/**.tscn       socket 数（glob 1028 个 tscn，逐个正则）

前两处在 exe 里还能当数据带进去，第三处（extracted/ 解密产物）体积与语义上都
不该跟着发布。故本工具在**构建期**把这些一次性算清，落成一个 JSON 资产，
运行时只读这一个文件。

产出：assets/gd_core_runtime.json
    {
      "version", "generator", "source", "counts",
      "classes":  {<职业名>: <枚举值>},          ← CoreConst.Classes_Full
      "characters": {…},                        ← assets/characters.json 内联
      "items": {
         <物品key>: {
            "script": "res://gd_core_items/Exclusive/StoneArmor.gd",
            "sockets": <int>,
            "descr": {…compile_descriptor 输出，字段名下划线风格与内核一致…},
            "rot": {"0"|"90"|"180"|"270": {
                       "collision": [[col,row], …],        # 锚点系、已归一化到 min=(0,0)
                       "affected": {"<颜色枚举>": [[col,row], …]}
            }}
         }
      },
      "unplayable": [<无转译脚本、无法装配的物品 key>]
    }

坐标约定：与 `tools/gen_lineup_fixture.py` 文件头一致（向量 Vector2(x=col, y=row)）。
  `rot` 里的格是**锚点系**（place 在 (0,0) 时算出来的），装配时按
  `(col + x, row + y)` 平移到实际锚点 —— 故一份数据可服务任意摆位。

★ 计数一律**现算**（`counts` 由本次扫描结果填充），不写死任何断言。
★ `character_stats` 的回合成长公式在运行时由 `simulator/gd_core_engine.py` 复刻，
  本工具末尾用**同一批探针**与 `tools/gen_lineup_fixture.character_stats` 对拍，
  公式漂移会在这里直接暴露（而不是在 exe 里安静算错血量）。

用法：
    python tools/gen_gd_core_data.py            # 生成/覆盖 assets/gd_core_runtime.json
    python tools/gen_gd_core_data.py --check    # 只比对是否与源数据同步（不写文件）
"""
from __future__ import annotations

import argparse
import glob
import io
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)

from tools import gen_lineup_fixture as GF  # noqa: E402

OUT_PATH = os.path.join(ROOT, "assets", "gd_core_runtime.json")
DB_PATH = os.path.join(ROOT, "assets", "battle_items.json")
CHAR_DB_PATH = os.path.join(ROOT, "assets", "characters.json")
LINEUP_DIR = os.path.join(ROOT, "lineups")
ROTATIONS = (0, 90, 180, 270)


def _load_chars() -> dict:
    if not os.path.exists(CHAR_DB_PATH):
        return {}
    d = json.load(io.open(CHAR_DB_PATH, encoding="utf-8"))
    if isinstance(d, dict) and "characters" in d:
        return d["characters"]
    return d or {}


def build() -> dict:
    db = json.load(io.open(DB_PATH, encoding="utf-8"))["items"]

    items = {}
    unplayable = []
    for key in sorted(db):
        entry = db[key]
        path = GF.script_path_opt(key, entry)
        if not path:
            unplayable.append(key)
            continue
        descr = GF.compile_descriptor(key, entry)
        rot = {}
        for deg in ROTATIONS:
            pl = GF.placement_of(key, entry, 0, 0, deg)
            rot[str(deg)] = {
                "collision": [[int(c[0]), int(c[1])] for c in pl["collision"]],
                "affected": {str(int(col)): [[int(c[0]), int(c[1])] for c in cells]
                             for col, cells in pl["affected"].items()},
            }
        items[key] = {
            "script": path,
            "sockets": int(descr["sockets"]),
            "descr": descr,
            "rot": rot,
        }

    # 职业枚举：Classes_Full 覆盖 Classes 的全部取值（0..3 一致），故直接用 Full
    classes = dict(GF.ENUMS.get("Classes_Full") or {})
    for k, v in (GF.ENUMS.get("Classes") or {}).items():
        classes.setdefault(k, v)

    lineups = sorted(os.path.splitext(os.path.basename(p))[0]
                     for p in glob.glob(os.path.join(LINEUP_DIR, "*.json")))

    return {
        "version": 1,
        "generator": "tools/gen_gd_core_data.py",
        "source": {
            "items": "assets/battle_items.json",
            "characters": "assets/characters.json",
            "enums": "gd_core/CoreConst.gd",
            "scripts": "gd_core_items/",
            "sockets": "extracted/Items/*.tscn",
            "lineups": "lineups/*.json",
        },
        "counts": {
            "db_items": len(db),
            "playable_items": len(items),
            "unplayable_items": len(unplayable),
            "lineups": len(lineups),
            "lineup_names": lineups,
        },
        "classes": classes,
        "characters": _load_chars(),
        "items": items,
        "unplayable": unplayable,
    }


# ─────────────────── 与 gen_lineup_fixture 对拍（防公式漂移） ───────────────────

def character_stats(lineup: dict, char_db: dict) -> dict:
    """★ 这是 `simulator/gd_core_engine.py` 里同名函数的**镜像**。

    两处必须逐字一致（引擎侧不能 import tools/，打包后不可用）。故这里刻意
    复制一份，并由 `verify_character_stats()` 对拍。
    """
    character = lineup.get("character") or "Adventurer"
    mods = lineup.get("class_modifiers") or {}
    db_char = char_db.get(character, {})
    base_health = float(mods.get("health", db_char.get("health", 25.0)))
    stamina = float(mods.get("stamina", db_char.get("stamina", 5.0)))
    regen = float(mods.get("stamina_regen", db_char.get("regen", 1.0)))
    override = lineup.get("health_override")
    if override is not None:
        health = float(override)
    else:
        health = base_health
        for i in range(2, int(lineup.get("round") or 1) + 1):
            if i >= 15:
                health += 30
            elif i >= 10:
                health += 20
            elif i >= 5:
                health += 15
            else:
                health += 10
    return {"health": health, "stamina": stamina, "regen": regen}


PROBE_LINEUPS = []
for _round in (1, 2, 4, 5, 9, 10, 14, 15, 20):
    PROBE_LINEUPS.append({"character": "Adventurer", "round": _round})
    PROBE_LINEUPS.append({"character": "Ranger", "round": _round,
                          "class_modifiers": {"health": 40, "stamina": 7,
                                              "stamina_regen": 2.0}})
PROBE_LINEUPS.append({"character": "Mage", "round": 3, "health_override": 123})
PROBE_LINEUPS.append({"character": "Mage", "round": 1, "class_modifiers": {}})
PROBE_LINEUPS.append({"character": "Engineer", "round": 16})


def verify_character_stats(char_db: dict) -> list:
    """返回不一致清单（空 = 通过）。"""
    bad = []
    for lu in PROBE_LINEUPS:
        mine = character_stats(lu, char_db)
        ref = GF.character_stats(lu, char_db)
        for k in ("health", "stamina", "regen"):
            if abs(float(mine[k]) - float(ref[k])) > 1e-9:
                bad.append("%s.%s: 镜像 %r ≠ 权威 %r"
                           % (lu, k, mine[k], ref[k]))
    return bad


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--check", action="store_true",
                    help="只校验是否与源数据同步，不写文件")
    args = ap.parse_args()

    data = build()

    bad = verify_character_stats(data["characters"])
    print("角色属性公式对拍：%d 个探针 → %s"
          % (len(PROBE_LINEUPS), "✓ 一致" if not bad else "✗ %d 处不一致" % len(bad)))
    for b in bad:
        print("   " + b)
    if bad:
        print("GEN_GD_CORE_DATA: FAIL")
        return 1

    body = json.dumps(data, ensure_ascii=False, sort_keys=False,
                      separators=(",", ":"))

    if args.check:
        if not os.path.exists(OUT_PATH):
            print("产物不存在：%s\nGEN_GD_CORE_DATA: FAIL" % OUT_PATH)
            return 1
        old = io.open(OUT_PATH, encoding="utf-8").read()
        if old != body:
            print("产物与源数据不同步：%s\nGEN_GD_CORE_DATA: FAIL" % OUT_PATH)
            return 1
        print("产物与源数据同步 ✓")
    else:
        io.open(OUT_PATH, "w", encoding="utf-8", newline="\n").write(body)
        print("已写出 %s（%.2f MB）"
              % (OUT_PATH, len(body.encode("utf-8")) / 1024.0 / 1024.0))

    c = data["counts"]
    print("物品库 %d 件 → 可装配 %d 件 / 无转译脚本 %d 件"
          % (c["db_items"], c["playable_items"], c["unplayable_items"]))
    if data["unplayable"]:
        print("   无脚本：%s%s"
              % (", ".join(data["unplayable"][:8]),
                 " …" if len(data["unplayable"]) > 8 else ""))
    print("阵容 %d 套：%s" % (c["lineups"], ", ".join(c["lineup_names"])))
    print("GEN_GD_CORE_DATA: PASS")
    return 0


if __name__ == "__main__":
    sys.exit(main())
