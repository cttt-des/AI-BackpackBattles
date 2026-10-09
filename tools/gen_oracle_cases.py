#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
gen_oracle_cases.py — 受控神谕对战用例清单生成器（oracle/fights.json）
（docs/oracle_workflow.md Phase 3 选材交付件）

用途：从拷贝的只读快照 oracle/data/history.db（Utility/BuildHistoryDB.gd 三表：
runData/roundData）为受控神谕批量跑批生成确定性对战用例清单。

规则（对齐 docs/oracle_workflow.md 与指令）：
  * SQL：每 run 取最后一回合 —— SELECT runID, MAX(roundID) FROM roundData GROUP BY runID。
  * 画像：每 run 取 class（Game.gd:129 enum Classes_Full）、最后一回合 buildInfo 解码出的
    item 数、Dragon Knight 是否在场等做多样性画像（复用 core/build_history.decode_build_info，
    编码 = BitStream 6bit+62 偏移；写侧仅 MagicRing 有持久段，见 Items/Exclusive/MagicRing.gd:283）。
  * 选样：默认全量（roundData 有回合的 run 全入选）；--limit N 裁剪时按 class 均匀分层，
    必含 Dragon Knight 在场的 run + 钉死 1548/1556（docs/oracle_workflow.md:57 终审场）
    + 物品数全局/各 class 最大最小的极端样本；不得少于 120 个。
  * 用例：{"case_id": "run<runID>_r<roundID>", "seed": (runID*7919+13) & 0x7FFFFFFF,
    "run_id": runID, "round_id": lastRound} —— 种子对每 run 固定，任意时刻可复现。
  * 打印 class 分布与用例总数；exit 0 且 fights.json 用例非空。

用法：
    python tools/gen_oracle_cases.py                # 全量（有回合的 run 全入选）
    python tools/gen_oracle_cases.py --limit 200    # 裁剪到 200 个（class 均匀分层）

注意：实测 1548/1556 自身 buildInfo 解码不含 Dragon Knight（其"DK 场次"标签来自
当年活体实录的对手段，不在 history.db 内）；本脚本仍按指令钉死入选，并把真正的
DK 在场 run 集合（解码实测）全部必含，两者都写进打印与 JSON 摘要，不掩盖分歧。
"""
from __future__ import annotations

import argparse
import json
import os
import sqlite3
import sys
from datetime import datetime

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)

# 既有 buildInfo 解码器（BitStream 6bit+62 偏移 + MagicRing 12bit 持久段，
# 写侧真值见 extracted_running/decomp/Core/RunDatabase.gd serializeRound）
from core.build_history import _find_map, decode_build_info  # noqa: E402

DB_PATH = os.path.join(ROOT, "oracle", "data", "history.db")
OUT_PATH = os.path.join(ROOT, "oracle", "fights.json")

# class 编号 → 名称：extracted_running/decomp/Core/Game.gd:129 enum Classes_Full
# （与 core/build_history.py CLASSES 的 0..3 段一致，此处补全 4..6）
CLASS_NAMES = {0: "Ranger", 1: "Reaper", 2: "Berserker", 3: "Pyromancer",
               4: "Mage", 5: "Adventurer", 6: "Engineer"}

DRAGON_KNIGHT = "Dragon Knight"   # 物品名（assets/item_index_map_live.json index 398）
PINNED_RUNS = (1548, 1556)        # 指令/doc 点名的终审场，无条件入选
MIN_CASES = 120                   # 裁剪下限（指令红线）
SEED_MASK = 0x7FFFFFFF

# runData.version → 版本串：Game.gd:687 versionToString（major.minor.mini 三段十进制）


def version_to_string(ver: int) -> str:
    return "%d.%d.%d" % (ver // 1000000, (ver % 1000000) // 1000, ver % 1000)


def derive_seed(run_id: int) -> int:
    """确定性种子：对每 run 固定，任意时刻可复现（指令钦定公式）。"""
    return (run_id * 7919 + 13) & SEED_MASK


def case_id(run_id: int, round_id: int) -> str:
    return "run%d_r%d" % (run_id, round_id)


def fail(msg: str) -> None:
    print("[gen_oracle_cases] FAIL: " + msg, file=sys.stderr)
    sys.exit(1)


def load_profiles(db_path: str):
    """读 history.db 并解码最后一回合 buildInfo → 每 run 多样性画像。

    返回 (profiles, stats)。profiles 按 runID 升序；任一 run 的最后回合
    解码失败不致命（decode_ok=False，画像保留、不参与极端样本），fail-fast
    只针对结构性错误（runData/roundData 断链、SQL 空结果）。
    """
    if not os.path.exists(db_path):
        fail("history.db 不存在: %s" % db_path)
    con = sqlite3.connect(db_path)
    try:
        cur = con.cursor()
        # —— 指令钦定 SQL：每 run 最后一回合 ——
        last_rounds = dict(cur.execute(
            "SELECT runID, MAX(roundID) FROM roundData GROUP BY runID").fetchall())
        if not last_rounds:
            fail("roundData 为空，无回合可回放")
        all_run_ids = {r[0] for r in cur.execute("SELECT runID FROM runData").fetchall()}
        orphan = sorted(set(last_rounds) - all_run_ids)
        if orphan:
            fail("roundData 引用了 runData 不存在的 runID: %s" % orphan[:10])
        run_meta = {r[0]: r[1:] for r in cur.execute(
            "SELECT runID, class, loadout, subclass, skill1, skill2, version "
            "FROM runData").fetchall()}
        last_rows = {}
        for run_id, round_id in last_rounds.items():
            row = cur.execute(
                "SELECT result, health, stamina, buildInfo FROM roundData "
                "WHERE runID = ? AND roundID = ?", (run_id, round_id)).fetchone()
            if row is None:
                fail("runID=%d 最后回合 roundID=%d 行缺失" % (run_id, round_id))
            last_rows[run_id] = (round_id,) + row
    finally:
        con.close()

    imap = _find_map()
    profiles = []
    n_decode_fail = 0
    for run_id in sorted(last_rounds):
        round_id, result, health, stamina, build_info = last_rows[run_id]
        cls_id, loadout, subclass, skill1, skill2, version = run_meta[run_id]
        decoded = None
        try:
            if build_info:
                decoded = decode_build_info(build_info, imap)
        except Exception:
            decoded = None
        items = decoded["items"] if decoded else []
        names = [it["id"] for it in items]
        profiles.append({
            "case_id": case_id(run_id, round_id),
            "run_id": run_id,
            "round_id": round_id,
            "class_id": cls_id,
            "class": CLASS_NAMES.get(cls_id, "cls%d" % cls_id),
            "subclass": subclass,
            "skills": [skill1, skill2],
            "loadout": loadout,
            "version": version_to_string(version),
            "rounds": round_id,          # 回合从 1 连续（已全库核验无空洞）
            "result_last": result,
            "health": health,
            "stamina": stamina,
            "item_count": len(items) if decoded else None,
            "decode_ok": decoded is not None,
            "dragon_knight": DRAGON_KNIGHT in names,
        })
        if decoded is None:
            n_decode_fail += 1
    stats = {
        "runs_in_run_data": len(all_run_ids),
        "runs_with_rounds": len(last_rounds),
        "runs_without_rounds": sorted(all_run_ids - set(last_rounds)),
        "decode_fail_last_round": n_decode_fail,
    }
    return profiles, stats


def pick_extremes(profiles):
    """物品数极端样本：全局与各 class 的最大/最小（仅 decode_ok 参与）。"""
    picked = []
    ok = [p for p in profiles if p["decode_ok"]]
    if not ok:
        return picked
    for scope, pool in (("global", ok),):
        for sign, tag in ((-1, "max"), (1, "min")):
            best = min(pool, key=lambda p: (sign * p["item_count"], p["run_id"]))
            picked.append((scope + "_" + tag, best))
    by_class = {}
    for p in ok:
        by_class.setdefault(p["class_id"], []).append(p)
    for cls_id in sorted(by_class):
        pool = by_class[cls_id]
        for sign, tag in ((-1, "max"), (1, "min")):
            best = min(pool, key=lambda p: (sign * p["item_count"], p["run_id"]))
            picked.append((CLASS_NAMES[cls_id] + "_" + tag, best))
    return picked


def select_cases(profiles, limit=None):
    """按选样规则给出入选画像列表。

    默认（limit=None）：全量。--limit N：裁剪到 N（>=MIN_CASES），
    必含 = DK 在场 run ∪ 钉死 1548/1556 ∪ 极端样本；剩余配额按 class
    均匀分层（每轮补当前已选最少的 class，class_id 升序破平，runID 升序取
    最小未选者），结果确定可复现。
    """
    by_run = {p["run_id"]: p for p in profiles}
    if limit is None:
        return list(profiles), {"mode": "all", "mandatory": len(profiles)}

    if limit < MIN_CASES:
        fail("--limit=%d 低于下限 %d（指令：不得少于 %d 个）"
             % (limit, MIN_CASES, MIN_CASES))
    if limit > len(profiles):
        fail("--limit=%d 超过有回合的 run 总数 %d" % (limit, len(profiles)))

    mandatory = {}
    def take(tag, p):
        if p["run_id"] not in mandatory:
            mandatory[p["run_id"]] = tag

    for p in profiles:
        if p["dragon_knight"]:
            take("dragon_knight", p)
    for run_id in PINNED_RUNS:
        if run_id in by_run:
            take("pinned_%d" % run_id, by_run[run_id])
        else:
            fail("钉死 run %d 不在 roundData（无回合可回放）" % run_id)
    for tag, p in pick_extremes(profiles):
        take("extreme_" + tag, p)
    if len(mandatory) > limit:
        fail("必含样本 %d 已超过 --limit=%d，规则互相矛盾" % (len(mandatory), limit))

    pool = {}
    for p in profiles:
        if p["run_id"] not in mandatory:
            pool.setdefault(p["class_id"], []).append(p)
    for cls_id in pool:
        pool[cls_id].sort(key=lambda p: p["run_id"])

    picked = [by_run[run_id] for run_id in mandatory]
    count_by_class = {}
    for p in picked:
        count_by_class[p["class_id"]] = count_by_class.get(p["class_id"], 0) + 1

    while len(picked) < limit:
        # 当前已选最少、且还有存货的 class 优先（class_id 升序破平）→ 均匀分层
        cands = [c for c in sorted(pool) if pool[c]]
        if not cands:
            fail("可用样本耗尽（%d < %d）" % (len(picked), limit))
        target = min(cands, key=lambda c: (count_by_class.get(c, 0), c))
        p = pool[target].pop(0)
        picked.append(p)
        count_by_class[target] = count_by_class.get(target, 0) + 1

    picked.sort(key=lambda p: p["run_id"])
    return picked, {"mode": "stratified:limit=%d" % limit,
                    "mandatory": len(mandatory),
                    "mandatory_tags": sorted(set(mandatory.values()))}


def main() -> None:
    ap = argparse.ArgumentParser(description="生成受控神谕对战用例清单 oracle/fights.json")
    ap.add_argument("--db", default=DB_PATH, help="history.db 路径（默认 oracle/data/history.db）")
    ap.add_argument("--out", default=OUT_PATH, help="输出 JSON（默认 oracle/fights.json）")
    ap.add_argument("--limit", type=int, default=None,
                    help="裁剪到 N 个用例（class 均匀分层；缺省=全量；下限 %d）" % MIN_CASES)
    args = ap.parse_args()

    profiles, db_stats = load_profiles(args.db)
    selected, sel_stats = select_cases(profiles, args.limit)

    cases = [{
        "case_id": p["case_id"],
        "seed": derive_seed(p["run_id"]),
        "run_id": p["run_id"],
        "round_id": p["round_id"],
    } for p in selected]
    if not cases:
        fail("用例清单为空")

    NAME_TO_CLASS_ID = {name: cid for cid, name in CLASS_NAMES.items()}

    def dist(items):
        d = {}
        for p in items:
            d[p["class"]] = d.get(p["class"], 0) + 1
        # 按 class_id 升序（Game.gd Classes_Full 定义序）
        return {k: d[k] for k in sorted(d, key=lambda k: NAME_TO_CLASS_ID[k])}

    dist_all = dist(profiles)
    dist_sel = dist(selected)
    dk_selected = [p for p in selected if p["dragon_knight"]]
    dk_all = [p for p in profiles if p["dragon_knight"]]
    decode_fail_sel = [p for p in selected if not p["decode_ok"]]

    doc = {
        "format": "oracle-fight-cases/1",
        "generated_by": "tools/gen_oracle_cases.py",
        "generated_at": datetime.now().isoformat(timespec="seconds"),
        "source_db": os.path.relpath(args.db, ROOT).replace("\\", "/"),
        "seed_rule": "seed = (run_id * 7919 + 13) & 0x7FFFFFFF",
        "case_id_rule": "run<run_id>_r<round_id>",
        "opponent_rule": "神谕缺省镜像对手（同 run 同回合，见 oracle/oracle_fight.gd read_config）",
        "selection": {
            "mode": sel_stats["mode"],
            "runs_in_run_data": db_stats["runs_in_run_data"],
            "runs_with_rounds": db_stats["runs_with_rounds"],
            "runs_without_rounds_count": len(db_stats["runs_without_rounds"]),
            "min_cases": MIN_CASES,
            "decode_fail_last_round": db_stats["decode_fail_last_round"],
            "decode_fail_in_selected": len(decode_fail_sel),
            "dragon_knight_runs_available": len(dk_all),
            "dragon_knight_in_selected": len(dk_selected),
            "pinned_runs": list(PINNED_RUNS),
            "note_pinned": "1548/1556 解码不含 Dragon Knight（DK 标签源自活体实录对手侧），"
                           "仍按指令/doc 钉死入选；真 DK run 集合由解码实测必含",
        },
        "class_distribution_selected": dist_sel,
        "class_distribution_all": dist_all,
        "cases": cases,
        "run_profile": profiles,
    }
    os.makedirs(os.path.dirname(os.path.abspath(args.out)), exist_ok=True)
    with open(args.out, "w", encoding="utf-8", newline="\n") as f:
        json.dump(doc, f, ensure_ascii=False, indent=1)
        f.write("\n")

    # —— 汇总打印（指令第 5 条：class 分布与用例总数）——
    print("[gen_oracle_cases] 数据源: %s" % args.db)
    print("[gen_oracle_cases] runData 共 %d run，其中 %d 有回合可回放（%d 个无回合、无用例），"
          "最后回合解码失败 %d"
          % (db_stats["runs_in_run_data"], db_stats["runs_with_rounds"],
             len(db_stats["runs_without_rounds"]), db_stats["decode_fail_last_round"]))
    print("[gen_oracle_cases] class 分布（有回合 run 全量 %d）: %s"
          % (len(profiles), dist_all))
    print("[gen_oracle_cases] class 分布（入选用例 %d）: %s" % (len(cases), dist_sel))
    print("[gen_oracle_cases] Dragon Knight 在场 run：全量 %d / 入选 %d；钉死 %s（实测不含 DK，"
          "按 doc:57 终审场入选）" % (len(dk_all), len(dk_selected), list(PINNED_RUNS)))
    ext = pick_extremes(profiles)
    print("[gen_oracle_cases] 物品数极端样本: " + ", ".join(
        "%s=run%d(%s)" % (tag, p["run_id"], p["item_count"]) for tag, p in ext))
    if decode_fail_sel:
        print("[gen_oracle_cases] 注意: %d 个入选 run 最后回合 buildInfo 解码失败"
              "（神谕装配大概率同样失败，跑批时会被逐场报错）: %s"
              % (len(decode_fail_sel),
                 [p["case_id"] for p in decode_fail_sel][:10]))
    print("[gen_oracle_cases] 用例总数: %d（模式 %s，必含 %d）"
          % (len(cases), sel_stats["mode"], sel_stats["mandatory"]))
    print("[gen_oracle_cases] 已写出: %s（%.1f KB）"
          % (args.out, os.path.getsize(args.out) / 1024.0))


if __name__ == "__main__":
    main()
