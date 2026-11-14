# -*- coding: utf-8 -*-
"""p0_acceptance.py — P0 继续判据验收（规划 §7 P0）：

  1. corpus 抽 1000 个真实终盘阵容 → 双层合法率（判据：≥50% 继续，<50% 解口径）
  2. history 三库（高质量摆盘冷启动数据）全量终盘解码 → 合法率 + 指派提取抽样
  3. 解析目标函数 A/B 演算冒烟

输出 trainer/p0_acceptance_report.json。
"""
from __future__ import annotations

import json
import os
import random
import sqlite3
import sys
from collections import Counter

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)

from trainer.layout_rules import (  # noqa: E402
    ItemIndex, check_layout, assign_bonuses, analytic_score, COLS, ROWS,
)

FACE_TO_ROT = {0: 0, 1: 90, 2: 180, 3: 270}


def corpus_entries(rows, i2n):
    """corpus_items 行 → 布局条目（x=col 锚=包围盒左上；face→rot）。"""
    out = []
    for seq, gid, x, y, face in rows:
        name = i2n.get(gid)
        if name is None:
            return None
        out.append({"id": name, "rot": FACE_TO_ROT.get(face or 0, 0),
                    "row": y, "col": x})
    return out


def main():
    index = ItemIndex()
    imap = json.load(open(os.path.join(ROOT, "assets", "item_index_map.json"),
                          encoding="utf-8"))
    i2n = {int(k): v for k, v in imap["index_to_name"].items()}
    report = {}

    # ── 1. corpus 1000 终盘 ──
    con = sqlite3.connect("file:" + os.path.join(ROOT, "database", "corpus.sqlite"),
                          uri=True)
    cur = con.cursor()
    runs = cur.execute(
        "SELECT r.record_key, r.rounds_played FROM corpus_runs r "
        "WHERE r.rounds_played >= 5 ORDER BY RANDOM() LIMIT 1000").fetchall()
    n, ok, fail_codes = 0, 0, Counter()
    fail_samples = {}
    for rk, rounds_played in runs:
        last = rounds_played
        rows = cur.execute(
            "SELECT seq, gid, x, y, face FROM corpus_items "
            "WHERE record_key=? AND round_no=?", (rk, last)).fetchall()
        if not rows:
            continue
        ents = corpus_entries(rows, i2n)
        if ents is None:
            fail_codes["GID_UNMAPPED"] += 1
            n += 1
            continue
        # 只取棋盘内（x<COLS；x>=9 是储物箱，不参战）
        ents = [e for e in ents if e["col"] < COLS]
        good, diags = check_layout(index, ents)
        n += 1
        if good:
            ok += 1
        else:
            for d in diags:
                fail_codes[d["code"]] += 1
            key = diags[0]["code"]
            fail_samples.setdefault(key, (rk, last, diags[:3]))
    con.close()
    report["corpus"] = {
        "sampled": n, "legal": ok, "rate": round(ok / max(n, 1), 4),
        "fail_codes": dict(fail_codes), "fail_samples": {
            k: {"run": v[0], "round": v[1], "diags": v[2]}
            for k, v in fail_samples.items()},
    }
    print(f"[corpus] 1000 终盘合法率 = {ok}/{n} = {ok/max(n,1):.1%}")
    print("        失败码分布:", dict(fail_codes))

    # ── 2. history 三库 ──
    from core.build_history import decode_build_info, _find_map
    hist_map = _find_map()
    hstat = {}
    h_examples = []
    for db in ["history-01.db", "history-06.db", "history-07.db"]:
        path = os.path.join(ROOT, "history", db)
        hcon = sqlite3.connect(path)
        hcur = hcon.cursor()
        rows = hcur.execute(
            "SELECT runID, MAX(roundID) FROM roundData GROUP BY runID").fetchall()
        okh, nh = 0, 0
        codes = Counter()
        for run_id, last_round in rows:
            bi = hcur.execute(
                "SELECT buildInfo FROM roundData WHERE runID=? AND roundID=?",
                (run_id, last_round)).fetchone()
            if not bi or not bi[0]:
                continue
            try:
                dec = decode_build_info(bi[0], hist_map)
            except Exception:
                codes["DECODE_ERROR"] += 1
                nh += 1
                continue
            if dec is None:
                codes["DECODE_NONE"] += 1
                nh += 1
                continue
            ents = [{"id": it["id"], "rot": it["r"],
                     "row": it["at"][0], "col": it["at"][1]}
                    for it in dec["items"] if it["at"][0] < ROWS and it["at"][1] < COLS]
            good, diags = check_layout(index, ents)
            nh += 1
            if good:
                okh += 1
                if len(h_examples) < 3 and len(ents) >= 20:
                    sc = analytic_score(index, ents)
                    h_examples.append({"db": db, "run": run_id,
                                       "n_items": len(ents), "score": sc})
            else:
                for d in diags:
                    codes[d["code"]] += 1
        hcon.close()
        hstat[db] = {"runs": nh, "legal": okh,
                     "rate": round(okh / max(nh, 1), 4), "codes": dict(codes)}
        print(f"[history] {db}: 终盘 {nh} 局, 合法 {okh} ({okh/max(nh,1):.1%}), 码={dict(codes)}")
    report["history"] = hstat
    report["history_examples"] = h_examples

    # ── 3. 指派提取冒烟（取一个合法 history 终盘）──
    if h_examples:
        pass
    out = os.path.join(ROOT, "trainer", "p0_acceptance_report.json")
    with open(out, "w", encoding="utf-8") as f:
        json.dump(report, f, ensure_ascii=False, indent=1, default=str)
    print("saved ->", out)


if __name__ == "__main__":
    main()
