#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""expand_select_cases.py — 扩样 P1：覆盖优先选样（异阵容对局）

依据 docs/扩大用例对齐规划.md §5（覆盖维度 / 贪心集合覆盖 / 配对语义），
在 tools/expand_build_inventory.py 的 inventory.json 上选样，产出：

    output/oracle/expand/cases.json            ← 神谕可直接读（read_cases 只认
                                                  case_id/seed/run_id/round_id/
                                                  opp_run_id/opp_round_id）
    output/oracle/expand/selection_report.md   ← 覆盖预测与分布报告

硬约束（本次扩样的额外要求）：
  * 全部为不同阵容对局：opp_run_id != run_id，且双方物品多重集不同
    （同 run 镜像对局一律不选，与 914 场基线口径相反）。
  * 配对语义仍然真实：对手是「同回合阶段」的历史对手（游戏原生
    «历史记录 → 标记对手» 语义），cross-run 配对。

选样方法：
  1) 候选池：版本 >= 1.1.5（主池），1.1.4 单列旧版本补充池；item_count>=1。
  2) 分组桶：class_id × 回合阶段（1 / 2-3 / 4-6 / 7-9 / 10-12 / 13-15 / 16-18）。
     每桶按「稀有物品得分」抽样候选池（每桶最多 --per-bucket 个，确定性抽样）。
  3) 轮转贪心：轮流在 49 个桶里挑「边际新增覆盖最大」的回合，直到目标场数；
     稀有物品权重 w = clamp(40/freq, 1, 12)，纯覆盖增量记分。
  4) 对手：在「同阶段、不同 run」的候选里选让组合增益最大者，class 不同加分、
     被复用次数扣分；双方物品多重集相同则拒绝。
  5) 必含：全局/每 class 的物品数极端样本、稀有物品兜底、1.1.4 旧版本补充。

用法：
    python -X utf8 tools/expand_select_cases.py
    python -X utf8 tools/expand_select_cases.py --target 100 --out output/oracle/expand/smoke/cases.json
"""
from __future__ import annotations

import argparse
import json
import os
import sys
import time
from collections import Counter, defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INV_DEFAULT = os.path.join(ROOT, "output", "oracle", "expand", "inventory.json")
CASES_DEFAULT = os.path.join(ROOT, "output", "oracle", "expand", "cases.json")
REPORT_DEFAULT = os.path.join(ROOT, "output", "oracle", "expand", "selection_report.md")

MAIN_VERSIONS = ("1.1.5", "1.1.6", "1.1.7", "1.1.8", "1.1.9")
LEGACY_VERSION = "1.1.4"
VERSION_TARGET = {"1.1.5": 60, "1.1.6": 90, "1.1.7": 140, "1.1.8": 260, "1.1.9": 520}
RARE_FREQ = 40
SEED_MASK = 0x7FFFFFFF
ROUND_STAGES = ((1, 1), (2, 3), (4, 6), (7, 9), (10, 12), (13, 15), (16, 18))
CLASS_NAMES = {0: "Ranger", 1: "Reaper", 2: "Berserker", 3: "Pyromancer",
               4: "Mage", 5: "Adventurer", 6: "Engineer"}


def stage_of(round_id):
    for lo, hi in ROUND_STAGES:
        if lo <= round_id <= hi:
            return str(lo) if lo == hi else "%d-%d" % (lo, hi)
    return "19+"


def derive_seed(run_id, round_id, opp_run_id):
    return (run_id * 7919 + round_id * 104729 + opp_run_id * 1299709 + 13) & SEED_MASK


def case_id_of(run_id, round_id, opp_run_id, opp_round_id):
    return "run%d_r%d_o%d_r%d" % (run_id, round_id, opp_run_id, opp_round_id)


def load_rounds(path):
    with open(path, encoding="utf-8") as f:
        doc = json.load(f)
    rounds = [r for r in doc["rounds"] if r["item_count"] >= 1 and r["items"]]
    freq = {k: int(v) for k, v in doc["item_freq"].items()}
    return rounds, freq, doc


def weight_of(item, freq):
    f = freq.get(item, 0)
    if f <= 0:
        return 20.0
    if f > RARE_FREQ:
        # 普通物品权重不为 0：否则贪心永远选不到「只含普通物品」的回合，
        # 会让 Gigawatz/Hedgehog 这类常见但在稀有权重下零增益的物品漏覆盖。
        return 0.5
    return min(12.0, RARE_FREQ / float(f))


def rare_score(r, freq):
    s = sum(weight_of(i, freq) for i in r["items"])
    s += 0.6 * sum(weight_of(g, freq) for g in r["gems"])
    return s


def sample_bucket(cands, per_bucket):
    cands.sort(key=lambda r: (-r["_rare"], r["run_id"], r["round_id"]))
    if len(cands) <= per_bucket:
        return list(cands)
    head = cands[: per_bucket // 2]
    rest = cands[per_bucket // 2:]
    step = max(1, len(rest) // (per_bucket - len(head)))
    tail = rest[::step][: per_bucket - len(head)]
    out, seen = [], set()
    for r in list(head) + list(tail):
        k = (r["run_id"], r["round_id"])
        if k in seen:
            continue
        seen.add(k)
        out.append(r)
    return out


def main():
    ap = argparse.ArgumentParser(description="扩样覆盖优先选样（异阵容对局）")
    ap.add_argument("--inventory", default=INV_DEFAULT)
    ap.add_argument("--out", default=CASES_DEFAULT)
    ap.add_argument("--report", default=REPORT_DEFAULT)
    ap.add_argument("--target", type=int, default=1200)
    ap.add_argument("--legacy", type=int, default=100)
    ap.add_argument("--per-bucket", type=int, default=140)
    args = ap.parse_args()

    t0 = time.time()
    rounds, freq, _inv = load_rounds(args.inventory)
    for r in rounds:
        r["_rare"] = rare_score(r, freq)
        r["stage"] = stage_of(r["round_id"])

    main_pool = [r for r in rounds if r["version"] in MAIN_VERSIONS]
    legacy_pool = [r for r in rounds if r["version"] == LEGACY_VERSION]

    buckets = defaultdict(list)
    for r in main_pool:
        buckets[(r["class_id"], r["stage"])].append(r)
    pool = {}
    for key, cands in buckets.items():
        pool[key] = sample_bucket(cands, args.per_bucket)

    opp_by_stage = defaultdict(list)
    for r in main_pool:
        opp_by_stage[r["stage"]].append(r)
    opp_pools = {}
    for st, cands in opp_by_stage.items():
        cands.sort(key=lambda r: (-r["_rare"], r["run_id"], r["round_id"]))
        if len(cands) > 900:
            step = max(1, len(cands) // 900)
            cands = cands[::step]
        opp_pools[st] = cands

    mandatory = []
    tag_of = {}

    def add_mandatory(r, tag):
        k = (r["run_id"], r["round_id"])
        if k in tag_of:
            return
        tag_of[k] = tag
        mandatory.append(r)

    if main_pool:
        add_mandatory(min(main_pool, key=lambda r: (-r["item_count"], r["run_id"], r["round_id"])), "global_max_items")
        add_mandatory(min(main_pool, key=lambda r: (r["item_count"], r["run_id"], r["round_id"])), "global_min_items")
        by_class = defaultdict(list)
        for r in main_pool:
            by_class[r["class_id"]].append(r)
        for cid in sorted(by_class):
            g = by_class[cid]
            add_mandatory(min(g, key=lambda r: (-r["item_count"], r["run_id"], r["round_id"])), "class%d_max_items" % cid)
            add_mandatory(min(g, key=lambda r: (r["item_count"], r["run_id"], r["round_id"])), "class%d_min_items" % cid)
    ultra = [k for k, v in freq.items() if v <= 2]
    for name in sorted(ultra):
        cand = [r for r in main_pool if name in r["items"]]
        if cand:
            add_mandatory(min(cand, key=lambda r: (r["item_count"], r["run_id"], r["round_id"])),
                          "ultra_rare:%s" % name)

    covered = set()
    chosen = []
    chosen_keys = set()
    version_count = Counter()
    class_count = Counter()
    stage_count = Counter()

    def take(r, reason):
        chosen.append((r, reason))
        chosen_keys.add((r["run_id"], r["round_id"]))
        covered.update(r["items"])
        covered.update(r["gems"])
        version_count[r["version"]] += 1
        class_count[r["class_id"]] += 1
        stage_count[r["stage"]] += 1

    for r in mandatory:
        if len(chosen) >= args.target:
            break
        take(r, tag_of[(r["run_id"], r["round_id"])])

    keys = sorted(pool.keys(), key=lambda k: (k[0], int(k[1].split("-")[0])))
    active = set(keys)
    progress = True
    budget = max(1, args.target - args.legacy)
    while progress and len(chosen) < budget and active:
        progress = False
        for key in [k for k in keys if k in active]:
            if len(chosen) >= budget:
                break
            best, best_score = None, 0.0
            any_left = False
            for r in pool[key]:
                k = (r["run_id"], r["round_id"])
                if k in chosen_keys:
                    continue
                any_left = True
                gain = 0.0
                for name in r["items"]:
                    if name not in covered:
                        gain += weight_of(name, freq)
                for g in r["gems"]:
                    if g not in covered:
                        gain += 0.6 * weight_of(g, freq)
                gap = VERSION_TARGET.get(r["version"], 0) - version_count[r["version"]]
                score = gain + (0.04 * gap if gap > 0 else 0.0)
                if score > best_score:
                    best, best_score = r, score
            if not any_left:
                active.discard(key)
            if best is None:
                continue
            take(best, "bucket:%d/%s" % key)
            progress = True

    legacy_chosen = []
    if args.legacy > 0 and legacy_pool:
        legacy_pool.sort(key=lambda r: (-r["_rare"], r["run_id"], r["round_id"]))
        step = max(1, len(legacy_pool) // max(1, args.legacy * 3))
        for r in legacy_pool[::step]:
            if len(legacy_chosen) >= args.legacy:
                break
            legacy_chosen.append(r)

    def multiset(r):
        return tuple(sorted(r["items"]))

    opp_used = Counter()
    cases = []
    pairs_same_lineup = 0
    class_pair = Counter()
    for r, reason in [(a, b) for a, b in chosen] + [(r, "legacy_1.1.4") for r in legacy_chosen]:
        stage = r["stage"]
        cands = opp_pools.get(stage)
        if not cands:
            cands = opp_pools[sorted(opp_pools)[0]]
        best, best_score = None, -1e9
        ms_r = multiset(r)
        for o in cands:
            if o["run_id"] == r["run_id"]:
                continue
            if (o["run_id"], o["round_id"]) in chosen_keys:
                continue
            if multiset(o) == ms_r:
                pairs_same_lineup += 1
                continue
            gain = 0.0
            for name in o["items"]:
                if name not in covered:
                    gain += weight_of(name, freq)
            for g in o["gems"]:
                if g not in covered:
                    gain += 0.6 * weight_of(g, freq)
            score = gain
            # 职业配对铺开：同类配对本来稀缺（库里同类对手少），给强加成，
            # 保证 7x7=49 种配对全部出现；已铺开的配对退回普通权重。
            pc = class_pair[(r["class_id"], o["class_id"])]
            if pc == 0:
                score += 6.0
            elif pc < 12:
                score += 2.5
            if o["class_id"] != r["class_id"]:
                score += 1.5
            if o["round_id"] == r["round_id"]:
                score += 1.5
            score -= 0.8 * opp_used[(o["run_id"], o["round_id"])]
            score += 0.001 * o["_rare"]
            if score > best_score:
                best, best_score = o, score
        if best is None:
            for o in cands:
                if o["run_id"] != r["run_id"] and multiset(o) != ms_r:
                    best = o
                    break
        if best is None:
            continue
        opp_used[(best["run_id"], best["round_id"])] += 1
        covered.update(best["items"])
        covered.update(best["gems"])
        class_pair[(r["class_id"], best["class_id"])] += 1
        cases.append({
            "case_id": case_id_of(r["run_id"], r["round_id"], best["run_id"], best["round_id"]),
            "seed": derive_seed(r["run_id"], r["round_id"], best["run_id"]),
            "run_id": r["run_id"],
            "round_id": r["round_id"],
            "opp_run_id": best["run_id"],
            "opp_round_id": best["round_id"],
            "player_class": r["class"],
            "player_class_id": r["class_id"],
            "opp_class": best["class"],
            "opp_class_id": best["class_id"],
            "player_version": r["version"],
            "opp_version": best["version"],
            "player_stage": r["stage"],
            "player_items": r["item_count"],
            "opp_items": best["item_count"],
            "player_src_run": r["src_run_id"],
            "opp_src_run": best["src_run_id"],
            "select_reason": reason,
            "opp_reuse": opp_used[(best["run_id"], best["round_id"])],
        })

    ids = [c["case_id"] for c in cases]
    assert len(ids) == len(set(ids)), "case_id 重复"
    seeds = [c["seed"] for c in cases]
    dup_seeds = len(seeds) - len(set(seeds))
    mirrored = [c["case_id"] for c in cases if c["run_id"] == c["opp_run_id"]]
    combos = Counter((c["run_id"], c["round_id"], c["opp_run_id"], c["opp_round_id"]) for c in cases)
    dup_combos = [k for k, v in combos.items() if v > 1]

    doc = {
        "format": "oracle-fight-cases/1",
        "generated_by": "tools/expand_select_cases.py",
        "generated_at": time.strftime("%Y-%m-%dT%H:%M:%S"),
        "source_inventory": os.path.relpath(args.inventory, ROOT).replace("\\", "/"),
        "seed_rule": "seed = (run_id*7919 + round_id*104729 + opp_run_id*1299709 + 13) & 0x7FFFFFFF",
        "case_id_rule": "run<run_id>_r<round_id>_o<opp_run_id>_r<opp_round_id>",
        "opponent_rule": "同回合阶段、不同 run 的跨 run 配对（原版历史记录标记对手语义）；"
                         "双方物品多重集必须不同（全部为不同阵容对局）",
        "selection": {
            "target": args.target,
            "legacy_1_1_4": len(legacy_chosen),
            "chosen": len(cases),
            "per_bucket": args.per_bucket,
            "rare_freq_threshold": RARE_FREQ,
            "version_target": VERSION_TARGET,
            "mirrored_cases": len(mirrored),
            "same_lineup_pairs_skipped": pairs_same_lineup,
            "dup_seeds": dup_seeds,
            "dup_combos": len(dup_combos),
        },
        "coverage": {
            "items_covered": len(covered),
            "items_total_in_history": len(freq),
            "by_version": dict(sorted(version_count.items())),
            "by_class": {str(k): v for k, v in sorted(class_count.items())},
            "by_stage": dict(sorted(stage_count.items())),
            "class_pairs": {"%s->%s" % k: v for k, v in sorted(class_pair.items())},
        },
        "cases": cases,
    }
    os.makedirs(os.path.dirname(os.path.abspath(args.out)), exist_ok=True)
    with open(args.out, "w", encoding="utf-8", newline="\n") as f:
        json.dump(doc, f, ensure_ascii=False, indent=1)
        f.write("\n")

    rare_left = sorted(k for k, v in freq.items() if v <= RARE_FREQ and k not in covered)
    lines = []
    lines.append("# 扩样选样报告（覆盖优先 / 全异阵容）")
    lines.append("")
    lines.append("生成：%s｜选样器：tools/expand_select_cases.py｜目标 %d 场，实选 **%d 场**"
                 % (doc["generated_at"], args.target, len(cases)))
    lines.append("")
    lines.append("## 一、硬约束自检")
    lines.append("")
    lines.append("| 项 | 值 | 说明 |")
    lines.append("|---|---|---|")
    lines.append("| 镜像对局（同 run 同回合） | **%d** | 必须为 0 |" % len(mirrored))
    lines.append("| case_id 重复 | 0 | 目录名唯一 |")
    lines.append("| seed 重复 | %d | 不同对局允许同种子，仅记录 |" % dup_seeds)
    lines.append("| 对局四元组重复 | %d | 必须为 0 |" % len(dup_combos))
    lines.append("| 物品多重集相同的配对（已跳过） | %d | 已剔除候选 |" % pairs_same_lineup)
    lines.append("")
    lines.append("## 二、覆盖预测")
    lines.append("")
    lines.append("- 历史库可解码物品 **%d** 种；本批覆盖 **%d** 种" % (len(freq), len(covered)))
    lines.append("- 稀有物品（历史库出现 ≤%d 次）未覆盖：**%d** 种%s"
                 % (RARE_FREQ, len(rare_left), ("（" + "、".join(rare_left[:12]) + "）") if rare_left else ""))
    lines.append("")
    lines.append("### 版本分布（玩家侧）")
    lines.append("")
    lines.append("| 版本 | 场数 | 期望 |")
    lines.append("|---|---|---|")
    for v, n in sorted(version_count.items()):
        lines.append("| %s | %d | %s |" % (v, n, VERSION_TARGET.get(v, "-")))
    if legacy_chosen:
        lines.append("| %s（旧版本补充，单列） | %d | %d |" % (LEGACY_VERSION, len(legacy_chosen), args.legacy))
    lines.append("")
    lines.append("### 职业分布（玩家侧）")
    lines.append("")
    lines.append("| 职业 | 场数 |")
    lines.append("|---|---|")
    for cid, n in sorted(class_count.items()):
        lines.append("| %s | %d |" % (CLASS_NAMES.get(cid, cid), n))
    lines.append("")
    lines.append("### 回合阶段分布")
    lines.append("")
    lines.append("| 回合阶段 | 场数 |")
    lines.append("|---|---|")
    for st, n in sorted(stage_count.items(), key=lambda kv: int(kv[0].split("-")[0])):
        lines.append("| %s | %d |" % (st, n))
    lines.append("")
    lines.append("### 职业配对（玩家→对手，前 15）")
    lines.append("")
    lines.append("| 配对 | 场数 |")
    lines.append("|---|---|")
    for k, v in sorted(class_pair.items(), key=lambda kv: -kv[1])[:15]:
        lines.append("| %s→%s | %d |" % (CLASS_NAMES.get(k[0], k[0]),
                                          CLASS_NAMES.get(k[1], k[1]), v))
    lines.append("")
    lines.append("## 三、跑批")
    lines.append("")
    lines.append("冒烟：python -X utf8 tools/expand_run_oracle.py --smoke")
    lines.append("全量：python -X utf8 tools/expand_run_oracle.py")
    with open(args.report, "w", encoding="utf-8", newline="\n") as f:
        f.write("\n".join(lines) + "\n")

    print("[select] 选出 %d 场（目标 %d）；1.1.4 补充 %d 场" % (len(cases), args.target, len(legacy_chosen)))
    print("[select] 物品覆盖 %d / %d；稀有未覆盖 %d 种" % (len(covered), len(freq), len(rare_left)))
    print("[select] 版本分布 %s" % dict(sorted(version_count.items())))
    print("[select] 镜像 %d、四元组重复 %d、seed 重复 %d" % (len(mirrored), len(dup_combos), dup_seeds))
    print("[select] 已写出 %s 与 %s；用时 %.1fs" % (args.out, args.report, time.time() - t0))


if __name__ == "__main__":
    main()
