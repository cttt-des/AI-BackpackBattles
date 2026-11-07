#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""expand_merge_history.py — 把 history/history-*.db 合并成神谕可读的单库

背景：神谕 oracle_fight.gd 固定读 res://data/history.db（= oracle/data/history.db），
且 res://fights.json 里的 run_id 必须在该库中能找到。history/ 下 7 个库的 runID
段互相重叠（如 1-291、192-254、1-235…），直接拼接会互踩，故按**文件名排序**
给每个库一个偏移 offset = 100000*(序号+1)：

    merged_runID = 原 runID + offset

偏移只改库内索引，不改 buildInfo 位流与回合内容；run_id → (库, 原 runID) 的
映射与 tools/expand_build_inventory.py 产出的 run_map 完全一致（同一规则），
因此用例表里的 run_id 可直接在本库中查到。

表结构与 oracle/data/history.db 保持一致（runData 10 列 / roundData 7 列）。

用法：
    python -X utf8 tools/expand_merge_history.py
    python -X utf8 tools/expand_merge_history.py --only-cases output/oracle/expand/cases.json
        # 只把用例涉及的 run 写进库（体积极小，神谕载入更快；仍保持偏移规则）
"""
from __future__ import annotations

import argparse
import glob
import json
import os
import sqlite3
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DB_GLOB = os.path.join(ROOT, "history", "history-*.db")
OUT_DEFAULT = os.path.join(ROOT, "output", "oracle", "expand", "data", "history.db")
RUN_OFFSET_STEP = 100000

SCHEMA = """
CREATE TABLE runData (
    runID INTEGER PRIMARY KEY,
    class INTEGER, loadout INTEGER, rank INTEGER, version INTEGER, time INTEGER,
    subclass INTEGER, skill1 INTEGER, skill2 INTEGER, custom TEXT
);
CREATE TABLE roundData (
    runID INTEGER, roundID INTEGER, result INTEGER, tries INTEGER,
    health INTEGER, stamina INTEGER, buildInfo TEXT,
    PRIMARY KEY (runID, roundID)
);
"""


def main() -> None:
    ap = argparse.ArgumentParser(description="合并 history 多库为神谕单库（runID 加偏移）")
    ap.add_argument("--out", default=OUT_DEFAULT)
    ap.add_argument("--glob", default=DB_GLOB)
    ap.add_argument("--only-cases", default="", help="只写入该用例表涉及的 run/回合")
    args = ap.parse_args()

    dbs = sorted(glob.glob(args.glob))
    if not dbs:
        print("[merge] 未找到库：%s" % args.glob, file=sys.stderr)
        sys.exit(1)

    keep_runs = None
    if args.only_cases:
        with open(args.only_cases, encoding="utf-8") as f:
            doc = json.load(f)
        keep_runs = set()
        for c in doc["cases"]:
            keep_runs.add((int(c["run_id"]), int(c["round_id"])))
            keep_runs.add((int(c["opp_run_id"]), int(c["opp_round_id"])))
        print("[merge] 仅保留用例涉及回合 %d 个" % len(keep_runs))
        # 缩到 run 级（同 run 其它回合一并带上，便于神谕取 wins/losses/tries 历史）
        keep_run_ids = {rid for rid, _ in keep_runs}

    os.makedirs(os.path.dirname(os.path.abspath(args.out)), exist_ok=True)
    if os.path.exists(args.out):
        os.remove(args.out)
    dst = sqlite3.connect(args.out)
    dst.executescript(SCHEMA)

    t0 = time.time()
    total_runs = total_rounds = 0
    run_map = {}
    for i, db in enumerate(dbs):
        offset = RUN_OFFSET_STEP * (i + 1)
        src = sqlite3.connect("file:%s?mode=ro" % db, uri=True)
        cur = src.cursor()
        runs = cur.execute(
            "SELECT runID, class, loadout, rank, version, time, subclass, skill1, skill2, custom "
            "FROM runData ORDER BY runID").fetchall()
        n_run = n_round = 0
        for row in runs:
            rid = row[0] + offset
            if keep_runs is not None and rid not in keep_run_ids:
                continue
            dst.execute("INSERT INTO runData VALUES (?,?,?,?,?,?,?,?,?,?)",
                        (rid,) + tuple(row[1:]))
            run_map[str(rid)] = {"db": os.path.relpath(db, ROOT).replace("\\", "/"),
                                 "src_run_id": row[0]}
            n_run += 1
        rounds = cur.execute(
            "SELECT runID, roundID, result, tries, health, stamina, buildInfo "
            "FROM roundData ORDER BY runID, roundID").fetchall()
        for row in rounds:
            rid = row[0] + offset
            if keep_runs is not None and (rid, row[1]) not in keep_runs:
                continue
            dst.execute("INSERT INTO roundData VALUES (?,?,?,?,?,?,?)", (rid,) + tuple(row[1:]))
            n_round += 1
        src.close()
        total_runs += n_run
        total_rounds += n_round
        print("[merge] %-16s offset=%-7d runs=%-5d rounds=%-6d"
              % (os.path.relpath(db, ROOT), offset, n_run, n_round))

    dst.commit()
    dst.close()

    map_path = os.path.splitext(args.out)[0] + "_run_map.json"
    with open(map_path, "w", encoding="utf-8", newline="\n") as f:
        json.dump({"rule": "run_id = 原runID + 100000*(库序号+1)",
                   "dbs": [os.path.relpath(d, ROOT).replace("\\", "/") for d in dbs],
                   "run_map": run_map}, f, ensure_ascii=False, indent=1)
        f.write("\n")

    print("[merge] 合计 runs=%d rounds=%d；写出 %s（%.1f MB）+ %s；用时 %.1fs"
          % (total_runs, total_rounds, args.out, os.path.getsize(args.out) / 1048576.0,
             map_path, time.time() - t0))


if __name__ == "__main__":
    main()
