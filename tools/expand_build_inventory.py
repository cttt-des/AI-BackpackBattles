#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""expand_build_inventory.py — 扩样 P0 预检：history/ 多库合并 + 逐回合解码盘点

用途（对应 docs/扩大用例对齐规划.md §4.3）：
  1) 扫描 history/history-*.db（BuildHistoryDB 三表 runData/roundData），按**文件名排序**
     给每个库一个 runID 偏移 offset = 100000 * (序号+1)，使合并后 runID 全局唯一
     （各库 runID 段互相重叠，直接合并会互踩；offset 只改索引、不改 buildInfo 语义）。
  2) 逐回合 decode_build_info（core/build_history.py，与游戏 deserializeStream 同位流语义），
     统计解码成功率、物品集合、宝石、职业、件数、版本。
  3) 产出 output/oracle/expand/inventory.json：
       - meta：库清单/偏移/版本分布/class 分布/解码成功率
       - rounds：每回合画像（精简，物品名 + 宝石名）
       - run_map：合并 runID → (库, 原 runID)
  4) 打印覆盖诊断：物品出现次数分布、零覆盖清单（与描述符表/assets 对照）。

只读：不改 history/ 下任何文件，不碰 oracle/。

用法：
    python -X utf8 tools/expand_build_inventory.py
    python -X utf8 tools/expand_build_inventory.py --out output/oracle/expand/inventory.json
"""
from __future__ import annotations

import argparse
import glob
import json
import os
import sqlite3
import sys
import time
from collections import Counter

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)

from core.build_history import _find_map, decode_build_info  # noqa: E402

DB_GLOB = os.path.join(ROOT, "history", "history-*.db")
OUT_DEFAULT = os.path.join(ROOT, "output", "oracle", "expand", "inventory.json")
RUN_OFFSET_STEP = 100000
CLASS_NAMES = {0: "Ranger", 1: "Reaper", 2: "Berserker", 3: "Pyromancer",
               4: "Mage", 5: "Adventurer", 6: "Engineer"}


def version_to_string(ver: int) -> str:
    return "%d.%d.%d" % (ver // 1000000, (ver % 1000000) // 1000, ver % 1000)


def scan(db_path: str, offset: int, imap) -> tuple:
    """读一个库 → (rounds, run_meta, stats)。rounds 内 run_id 已加 offset。"""
    con = sqlite3.connect("file:%s?mode=ro" % db_path, uri=True)
    try:
        cur = con.cursor()
        run_meta = {r[0]: r[1:] for r in cur.execute(
            "SELECT runID, class, version, time, subclass, skill1, skill2 FROM runData")}
        rows = cur.execute(
            "SELECT runID, roundID, result, health, stamina, buildInfo FROM roundData "
            "ORDER BY runID, roundID").fetchall()
    finally:
        con.close()

    rounds = []
    n_ok = n_fail = n_empty = 0
    by_ver = Counter()
    by_ver_fail = Counter()
    for run_id, round_id, result, health, stamina, build_info in rows:
        meta = run_meta.get(run_id)
        if meta is None:
            continue
        cls_id, version, _t, subclass, skill1, skill2 = meta
        vstr = version_to_string(version)
        by_ver[vstr] += 1
        decoded = None
        if build_info:
            try:
                decoded = decode_build_info(build_info, imap)
            except Exception:
                decoded = None
        else:
            n_empty += 1
        if decoded is None:
            n_fail += 1
            by_ver_fail[vstr] += 1
            continue
        n_ok += 1
        items = decoded["items"]
        names = [it["id"] for it in items]
        gems = []
        for it in items:
            gems.extend(it["gems"])
        rounds.append({
            "run_id": run_id + offset,
            "src_run_id": run_id,
            "round_id": round_id,
            "class_id": cls_id,
            "class": CLASS_NAMES.get(cls_id, "cls%d" % cls_id),
            "version": vstr,
            "subclass": subclass,
            "skills": [skill1, skill2],
            "result": result,
            "health": decoded["health"],
            "stamina": decoded["stamina"],
            "item_count": len(items),
            "items": names,
            "gems": gems,
        })
    stats = {
        "db": os.path.relpath(db_path, ROOT).replace("\\", "/"),
        "offset": offset,
        "runs": len(run_meta),
        "rounds_rows": len(rows),
        "decoded_ok": n_ok,
        "decoded_fail": n_fail,
        "buildinfo_empty": n_empty,
        "by_version": dict(sorted(by_ver.items())),
        "by_version_fail": dict(sorted(by_ver_fail.items())),
    }
    return rounds, run_meta, stats


def main() -> None:
    ap = argparse.ArgumentParser(description="history 多库合并 + 逐回合解码盘点（扩样 P0 预检）")
    ap.add_argument("--out", default=OUT_DEFAULT)
    ap.add_argument("--glob", default=DB_GLOB)
    args = ap.parse_args()

    dbs = sorted(glob.glob(args.glob))
    if not dbs:
        print("[inventory] 未找到库：%s" % args.glob, file=sys.stderr)
        sys.exit(1)
    imap = _find_map()
    t0 = time.time()

    all_rounds = []
    run_map = {}
    db_stats = []
    for i, db in enumerate(dbs):
        offset = RUN_OFFSET_STEP * (i + 1)
        rounds, run_meta, stats = scan(db, offset, imap)
        for rid in run_meta:
            run_map[str(rid + offset)] = {"db": stats["db"], "src_run_id": rid}
        all_rounds.extend(rounds)
        db_stats.append(stats)
        print("[inventory] %-16s runs=%-5d rounds=%-6d ok=%-6d fail=%-4d empty=%-3d"
              % (stats["db"], stats["runs"], stats["rounds_rows"],
                 stats["decoded_ok"], stats["decoded_fail"], stats["buildinfo_empty"]))

    item_count = Counter()
    for r in all_rounds:
        for name in r["items"]:
            item_count[name] += 1
    ver_count = Counter(r["version"] for r in all_rounds)
    cls_count = Counter(r["class"] for r in all_rounds)

    doc = {
        "format": "expand-inventory/1",
        "generated_by": "tools/expand_build_inventory.py",
        "generated_at": time.strftime("%Y-%m-%dT%H:%M:%S"),
        "run_id_rule": "run_id = 原runID + 100000*(库序号+1)，库序号按文件名排序",
        "dbs": db_stats,
        "totals": {
            "dbs": len(dbs),
            "rounds_decoded": len(all_rounds),
            "distinct_items": len(item_count),
            "by_version": dict(sorted(ver_count.items())),
            "by_class": dict(sorted(cls_count.items())),
        },
        "item_freq": dict(sorted(item_count.items(), key=lambda kv: (-kv[1], kv[0]))),
        "run_map": run_map,
        "rounds": all_rounds,
    }
    os.makedirs(os.path.dirname(os.path.abspath(args.out)), exist_ok=True)
    with open(args.out, "w", encoding="utf-8", newline="\n") as f:
        json.dump(doc, f, ensure_ascii=False, separators=(",", ":"))
        f.write("\n")

    print("[inventory] 合计可解码回合 %d；版本分布 %s；class 分布 %s"
          % (len(all_rounds), dict(sorted(ver_count.items())), dict(sorted(cls_count.items()))))
    print("[inventory] 物品种数 %d；件数 0 的回合 %d；最大件数 %d"
          % (len(item_count), sum(1 for r in all_rounds if r["item_count"] == 0),
             max((r["item_count"] for r in all_rounds), default=0)))
    print("[inventory] 用时 %.1fs；已写出 %s（%.1f MB）"
          % (time.time() - t0, args.out, os.path.getsize(args.out) / 1048576.0))


if __name__ == "__main__":
    main()
