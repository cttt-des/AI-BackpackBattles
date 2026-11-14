# -*- coding: utf-8 -*-
"""make_probe_holding.py — 摆盘标尺样本采集：H 生成器（交付物 1）

任务书：docs/摆盘标尺样本采集_开发任务书.md §3。

造一套"有取舍压力"的持有列表 H：
  基底 = 该回合真实终盘阵容（corpus round_no=N，合法、真实）
  + 注入 = 同回合同职业其他真实阵容的非包物品（分布真实）
  ⇒ Σ物品需格 > Σ包格 × (1 + overfill)，玩家必须舍弃若干件。

产出三件套（+ 基底留档）：
  <name>.H.json        v4 持有列表（给桥接器 load_holding）
  <name>.清单.md       中文清单（给真人玩家，路线 B 直接可用）
  <name>.初始摆盘.json 解析分贪心的合法初始布局（玩家/桥接器的起点）
  <name>_base.json     基底阵容留档（meta.baseline_name 指向它）

构造规则（任务书 §3.2，逐条落实）：
  1 基底=真实终盘阵容        → _pick_baseline，check_layout 必过
  2 注入取自同回合真实阵容   → 同回合 + 同职业（职业决定物品池）
  3 need > cap × (1+overfill) → 注入循环的硬条件
  4 不注入包                  → is_bag 过滤
  5 至少 3 件可舍弃           → inject_items 下限 3
  6 id 必须是资产 key         → i2n 映射 + idx.has 双重过滤
  7 基底/初始摆盘过 check_layout → _verify
  8 同 seed 可复现            → 唯一 rng、sorted 遍历、ORDER BY、无时间戳

用法：
  python -I trainer/make_probe_holding.py --round 12 --character Ranger --out probe_samples/
  python -I trainer/make_probe_holding.py --preset all
"""
from __future__ import annotations

import argparse
import json
import os
import random
import sqlite3
import sys
from collections import Counter

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)

from trainer.layout_rules import (  # noqa: E402
    ItemIndex, check_layout, analytic_score, COLS, ROWS,
    BAG_SPECS, WEIGHTS, _cond_fn)
from simulator.i18n import zh_name  # noqa: E402

DB_PATH = os.path.join(ROOT, "database", "corpus.sqlite")
IMAP_PATH = os.path.join(ROOT, "assets", "item_index_map.json")

FACE_TO_ROT = {0: 0, 1: 90, 2: 180, 3: 270}

# 任务书 §3.5 五套预设（名称 → (回合, inject_items, overfill)）
PRESETS = [
    ("probe_R01", 1, 3, 0.10),
    ("probe_R05", 5, 3, 0.10),
    ("probe_R12", 12, 3, 0.10),
    ("probe_R18", 18, 3, 0.10),
    ("probe_R18_rich", 18, 12, 0.30),
]
# 职业全覆盖（corpus 全部 7 职业；2026-11-12 用户要求）
PRESET_CHARS = ["Ranger", "Pyromancer", "Reaper", "Adventurer",
                "Mage", "Engineer", "Berserker"]


# ═════════════════════════ corpus 读取 ═════════════════════════

def _load_index_map():
    with open(IMAP_PATH, encoding="utf-8") as f:
        imap = json.load(f)
    i2n = {int(k): v for k, v in imap["index_to_name"].items()}
    g2n = list(imap["gem_order"])
    return i2n, g2n


def _lineup_from_corpus(con, i2n, g2n, idx, rk: str, round_no: int):
    """一条真实终盘阵容 → (v4 items 列表, or None)。与 evaluator.OpponentPool 同口径，
    额外保留 gems（真实阵容的已镶宝石）。"""
    rows = con.execute(
        "SELECT gid, x, y, face, gems_json FROM corpus_items "
        "WHERE record_key=? AND round_no=? ORDER BY seq", (rk, round_no)).fetchall()
    items = []
    for gid, x, y, face, gems in rows:
        name = i2n.get(gid)
        if name is None or not idx.has(name):
            return None
        if x is None or y is None or x >= COLS or y >= ROWS:
            continue  # 储物箱 / 异常
        ent = {"id": name, "at": [int(y), int(x)], "r": FACE_TO_ROT.get(face or 0, 0)}
        if gems:
            gn = [g2n[g] for g in json.loads(gems)
                  if isinstance(g, int) and 0 <= g < len(g2n)]
            if gn:
                ent["gems"] = gn
        items.append(ent)
    return items


def _pick_baseline(con, i2n, g2n, idx, rng: random.Random, round_no: int,
                   character: str):
    """选基底：该回合真实终盘阵容，合法、有包、规模非平凡。失败返回 None。"""
    if character is None:
        # 职业：按该回合 run 数加权随机（确定性：sorted 遍历 + rng.random）
        cnt = dict(con.execute(
            "SELECT class_name, COUNT(*) FROM corpus_runs "
            "WHERE rounds_played>=? GROUP BY class_name", (round_no,)).fetchall())
        names, cum = sorted(cnt), []
        acc = 0
        for n in names:
            acc += cnt[n]
            cum.append(acc)
        pick = rng.random() * acc
        character = names[[i for i, c in enumerate(cum) if pick < c][0]]

    rks = [r[0] for r in con.execute(
        "SELECT record_key FROM corpus_runs WHERE rounds_played>=? AND class_name=? "
        "ORDER BY record_key", (round_no, character)).fetchall()]
    rng.shuffle(rks)
    for rk in rks:
        items = _lineup_from_corpus(con, i2n, g2n, idx, rk, round_no)
        if not items or len(items) < 6:
            continue
        bags = [e for e in items if idx.is_bag(e["id"])]
        if not bags:
            continue
        ents = _to_ents(items)
        ok, _diags = check_layout(idx, ents)
        if not ok:
            continue
        meta = con.execute(
            "SELECT rating, rating_bucket FROM corpus_runs WHERE record_key=?",
            (rk,)).fetchone()
        return {"rk": rk, "character": character, "items": items,
                "rating": meta[0], "bucket": meta[1]}
    return None


def _injection_plan(con, i2n, idx, rng: random.Random, round_no: int,
                    character: str, baseline_rk: str, baseline_items,
                    inject_items: int, overfill: float):
    """注入计划：同回合同职业真实阵容的非包物品，按出现频率加权抽样。

    每件物品名上限 = 该回合同职业任一单阵容的最大同名数（堆叠上限保持真实）。
    循环直到【件数 ≥ inject_items 且 need ≥ cap×(1+overfill)】，池尽则提前停。
    """
    cnt = Counter()
    per_lineup_max = Counter()
    rows = con.execute(
        "SELECT ci.record_key, ci.gid FROM corpus_items ci "
        "JOIN corpus_runs cr ON ci.record_key=cr.record_key "
        "WHERE ci.round_no=? AND cr.class_name=? AND ci.record_key<>? "
        "ORDER BY ci.record_key, ci.seq",
        (round_no, character, baseline_rk)).fetchall()
    seen = Counter()
    cur_rk = None
    for rk, gid in rows:
        name = i2n.get(gid)
        if name is None or not idx.has(name) or idx.is_bag(name):
            continue
        if rk != cur_rk:
            for n, c in seen.items():
                if c > per_lineup_max[n]:
                    per_lineup_max[n] = c
            seen = Counter()
            cur_rk = rk
        seen[name] += 1
        cnt[name] += 1
    for n, c in seen.items():
        if c > per_lineup_max[n]:
            per_lineup_max[n] = c
    if not cnt:
        return []

    # 频率加权抽样流：名字按频次展开（sorted 保证确定性），rng 洗牌后成流
    stream = sorted(cnt.elements())
    rng.shuffle(stream)

    base_cnt = Counter(e["id"] for e in baseline_items)
    ents = _to_ents(baseline_items)
    cap = _cap_of(idx, baseline_items)
    need = _need_of(idx, baseline_items)
    injected: list = []
    inj_cnt: Counter = Counter()
    for name in stream:
        if inj_cnt[name] + base_cnt[name] >= per_lineup_max[name]:
            continue  # 超出真实堆叠上限
        injected.append(name)
        inj_cnt[name] += 1
        need += idx.num_cells(name, 0)
        if len(injected) >= inject_items and \
                need >= cap * (1.0 + overfill):
            break
    return injected


# ═════════════════════════ 统计（任务书 §3.3 口径） ═════════════════════════

def _cap_of(idx: ItemIndex, items) -> int:
    """容器格：所选包的占格总和（包与包不重叠，直接相加）。"""
    return sum(idx.num_cells(e["id"], e["r"]) for e in items if idx.is_bag(e["id"]))


def _need_of(idx: ItemIndex, items) -> int:
    """物品需格：非包物品的占格总和。"""
    return sum(idx.num_cells(e["id"], e["r"]) for e in items if not idx.is_bag(e["id"]))


def _to_ents(items_v4):
    """v4 条目 → layout_rules 条目（{"id","rot","row","col"}）。"""
    return [{"id": e["id"], "rot": int(e.get("r", 0)) % 360,
             "row": int(e["at"][0]), "col": int(e["at"][1])} for e in items_v4]


# ═════════════════════════ 初始摆盘（解析分贪心） ═════════════════════════

def _item_a_delta(idx: ItemIndex, name: str) -> float:
    """候选物品自身的 A 类分（与 analytic_score 的 A 口径逐字一致，只算一件）。"""
    d = idx.descr(name)
    a = 0.0
    for k, v in d.get("namedParams", {}).items():
        if k in ("luck", "spikes", "heal", "block", "mana", "regen",
                 "vampirism", "empower", "stamina"):
            a += WEIGHTS.get({"stamina": "stamina_reg"}.get(k, k), 0.0) * float(v)
    d_min, d_max = float(d["minDam"]), float(d["maxDam"])
    if d_min or d_max:
        a += WEIGHTS["dmg"] * (d_min + d_max) / 2.0
    return a


def _initial_layout(idx: ItemIndex, baseline_items, injected_names):
    """基底原样保留（真实合法布局），注入物品逐件贪心找合法位。

    位置得分 = ΔA（物品自身）+ ΔB（新增加成指派边）——与 analytic_score
    同一套 BAG_SPECS/WEIGHTS/_cond_fn 表，只算候选新增的那部分
    （加一件非包物品不会改变已有边），故逐位调用整场 analytic_score 等价
    且快一个数量级。同分取扫描序首个（确定性）。放不下的留在 unplaced
    （正是取舍压力），不求最优。
    """
    entries = _to_ents(baseline_items)
    # 包实例域预计算（assign_bonuses 同口径：occ 域 / affected 域）
    bag_insts = []  # (name, occ_set, aff_set)
    filled: dict = {}
    for e in entries:
        occ = {(c[0] + e["col"], c[1] + e["row"])
               for c in idx.collision_cells(e["id"], e["rot"])}
        if idx.is_bag(e["id"]):
            bag_insts.append((e["id"], occ,
                              {(c[0] + e["col"], c[1] + e["row"])
                               for c in idx.affected_cells(e["id"], e["rot"])}))
        else:
            for c in occ:
                filled[c] = e["id"]
    bag_union = set()
    for _n, occ, _a in bag_insts:
        bag_union |= occ
    bag_names = {n for n, _o, _a in bag_insts}

    cache: dict = {}

    def score_at(name, rot, col, row):
        """(name, rot) 下命中包实例模式的 Δ分；同模式同分（与位置无关）。"""
        rel = idx.collision_cells(name, rot)
        occ = {(c[0] + col, c[1] + row) for c in rel}
        hits = {}
        for bname, occset, affset in bag_insts:
            spec = BAG_SPECS.get(bname)
            if spec is None or spec["coverage"] is None:
                continue
            dom = occset if spec["coverage"] == "items" else affset
            if occ & dom:
                hits[bname] = hits.get(bname, 0) + 1
        # 全局协同：候选是伙伴物品（如 Bagtacular）→ 已有对应包各加一条
        partner_edges = sum(
            WEIGHTS.get(syn, 0.0)
            for _bn, spec in BAG_SPECS.items() for syn, partner in
            spec.get("global", []) if partner == name and _bn in bag_names)
        key = (name, tuple(sorted(hits.items())), partner_edges)
        if key not in cache:
            b = partner_edges
            for bname, n in hits.items():
                spec = BAG_SPECS[bname]
                cond = _cond_fn(idx, spec["cond"])
                if spec["cond"] is None or cond(name):
                    b += WEIGHTS.get(spec["effect"], 0.0) * n
            cache[key] = _item_a_delta(idx, name) + b
        return cache[key]

    placed, unplaced = [], []
    for name in injected_names:
        best = None
        for rot in (0, 90, 180, 270):
            if str(rot) not in idx.items[name]["rot"]:
                continue
            rel = idx.collision_cells(name, rot)
            for row in range(ROWS):
                for col in range(COLS):
                    bad = False
                    occ = []
                    for c in rel:
                        x, y = c[0] + col, c[1] + row
                        if x < 0 or x >= COLS or y < 0 or y >= ROWS:
                            bad = True
                            break
                        cell = (x, y)
                        if cell not in bag_union or cell in filled:
                            bad = True
                            break
                        occ.append(cell)
                    if bad:
                        continue
                    sc = score_at(name, rot, col, row)
                    cand_key = (sc, -rot, -row, -col)
                    if best is None or cand_key > best[0]:
                        best = (cand_key, {"id": name, "rot": rot,
                                           "row": row, "col": col})
        if best is not None:
            e = best[1]
            entries.append(e)
            for c in idx.collision_cells(e["id"], e["rot"]):
                filled[(c[0] + e["col"], c[1] + e["row"])] = name
            placed.append(name)
        else:
            unplaced.append(name)
    ok, diags = check_layout(idx, entries)
    assert ok, f"初始摆盘不合法: {diags}"
    return entries, placed, unplaced


# ═════════════════════════ 产出文件 ═════════════════════════

def _dump_json(path, obj):
    with open(path, "w", encoding="utf-8", newline="\n") as f:
        json.dump(obj, f, ensure_ascii=False, indent=1)
        f.write("\n")


def _agg_table(idx: ItemIndex, items):
    """按名字聚合（数量、占格、宝石附注），输出顺序按首次出现（确定性）。"""
    agg = {}
    order = []
    for e in items:
        n = e["id"]
        if n not in agg:
            agg[n] = {"count": 0, "cells": idx.num_cells(n, e.get("r", 0)),
                      "gems": Counter()}
            order.append(n)
        agg[n]["count"] += 1
        for g in e.get("gems", []):
            agg[n]["gems"][g] += 1
    return [(n, agg[n]) for n in order]


def _write_checklist_md(path, name, round_no, character, items, cap, need,
                        overfill, idx, rating, bucket):
    nb_bags = sum(1 for e in items if idx.is_bag(e["id"]))
    excess = need - cap
    nb_sizes = [idx.num_cells(e["id"], e.get("r", 0)) for e in items
                if not idx.is_bag(e["id"])]
    mean_sz = (sum(nb_sizes) / len(nb_sizes)) if nb_sizes else 1.0
    drop_n = max(1, round(excess / max(mean_sz, 0.1)))
    tgt = f"对约 {rating:.0f} 分（{bucket}）分段对手" if rating else "对同分段对手"

    lines = []
    a = lines.append
    a(f"# 持有清单：{name}")
    a("")
    a(f"- 回合：R{round_no}")
    a(f"- 职业：{character}")
    a(f"- 物品总数：**{len(items)} 件**（其中包 {nb_bags} 件）")
    a(f"- 容器格：**{cap} 格**；物品需格：**{need} 格**")
    a(f"- ⇒ **需要舍弃约 {excess} 格，也就是少上约 {drop_n} 件物品**")
    a(f"- 目标：{tgt}，**期望胜率最大化**")
    a("")
    a("> 表里是你手上的**全部**物品，不要求全上。")
    a("> **摆不下是正常的**，请选择你认为最好的组合。")
    a("")

    bags = [e for e in items if idx.is_bag(e["id"])]
    gem_names = set(_load_index_map()[1])
    gems = [e for e in items if not idx.is_bag(e["id"]) and e["id"] in gem_names]
    others = [e for e in items
              if not idx.is_bag(e["id"]) and e["id"] not in gem_names]
    groups = [("## 背包（容器，占格但提供空间）", bags),
              ("## 武器与装备", others)]
    if gems:
        groups.append(("## 宝石（未镶嵌，散装占格；可镶到带孔武器上）", gems))
    for title, group in groups:
        a(title)
        a("")
        a("| 数量 | 中文名 | 英文名（备查） | 占格 |")
        a("|---|---|---|---|")
        for n, info in _agg_table(idx, group):
            zh = zh_name(n)
            a(f"| {info['count']} | {zh} | {n} | {info['cells']} |")
        a("")

    gem_notes = []
    for n, info in _agg_table(idx, items):
        if info["gems"]:
            gs = "、".join(f"{zh_name(g)} ×{c}" for g, c in sorted(info["gems"].items()))
            gem_notes.append(f"- {zh_name(n)}（{n}）已镶：{gs}")
    if gem_notes:
        a("## 已镶宝石（随物品一起持有）")
        a("")
        lines.extend(gem_notes)
        a("")

    a("> 说明：")
    a("> 1. 表里是**你手上的全部物品**，不是全部都要上；")
    a("> 2. **摆不下时可以少上**，少上几件是允许的，请选你认为最好的组合；")
    a("> 3. 请**在沙盒模式**里按清单挑出这些物品（不要碰真实存档）；")
    a("> 4. 摆完请用**现有导出方法**导出当前阵容；")
    a("> 5. 请按**最大化胜率**来摆，不要按平时习惯随手摆；")
    a("> 6. 有物品不知道怎么用就**忽略它**（避免硬凑）。")
    a("")
    with open(path, "w", encoding="utf-8", newline="\n") as f:
        f.write("\n".join(lines))


# ═════════════════════════ 主入口 ═════════════════════════

def make_holding(round_no: int, character: str | None = None,
                 inject_items: int = 3, overfill: float = 0.10,
                 seed: int = 0, out_dir: str = "probe_samples",
                 name: str | None = None) -> dict:
    """生成一套带取舍压力的持有列表 H（任务书 §3.1 接口）。

    参数:
      round_no:     目标回合 1..18（决定可用稀有度与典型规模）
      character:    职业；None 则从该回合真实阵容里按 run 数加权随机取
      inject_items: 注入的额外物品件数下限（至少 3，制造取舍压力）
      overfill:     目标超容比例（0.10 = 物品需格比容器格多 10%）
      seed:         随机种子（同种子必须产出同一套 H）
      out_dir:      输出目录（相对仓库根）
      name:         样本名；缺省 probe_R{round:02d}_{职业}。
                    预设模式须显式传（如 probe_R18_rich），避免与
                    probe_R18 同回合撞名。

    返回: {"H": v4_dict, "baseline": v4_dict, "init": v4_dict, "stats": {...}}
    同时写出 <name>.H.json / <name>.清单.md / <name>.初始摆盘.json / <name>_base.json
    """
    assert 1 <= round_no <= 18, "round_no 须在 1..18"
    inject_items = max(int(inject_items), 3)  # 规则 5：至少 3 件可舍弃
    idx = ItemIndex()
    i2n, g2n = _load_index_map()
    rng = random.Random(seed)
    con = sqlite3.connect("file:" + DB_PATH, uri=True)
    try:
        base = _pick_baseline(con, i2n, g2n, idx, rng, round_no, character)
        if base is None:
            raise RuntimeError(f"该回合/职业找不到合法真实阵容: "
                               f"R{round_no} {character}")
        injected = _injection_plan(con, i2n, idx, rng, round_no,
                                   base["character"], base["rk"],
                                   base["items"], inject_items, overfill)
    finally:
        con.close()

    name = name or f"probe_R{round_no:02d}_{base['character']}"
    out_path = out_dir if os.path.isabs(out_dir) else os.path.join(ROOT, out_dir)
    os.makedirs(out_path, exist_ok=True)

    # H：基底（真实 at/r 与 gems）+ 注入件（at 无约束意义，[0,0] 占位）
    h_items = [dict(e) for e in base["items"]]
    h_items += [{"id": n, "at": [0, 0], "r": 0} for n in injected]
    cap, need = _cap_of(idx, h_items), _need_of(idx, h_items)
    achieved = (need / cap - 1.0) if cap else float("inf")

    H = {"version": 4, "name": name, "character": base["character"],
         "round": round_no, "grid": [ROWS, COLS], "items": h_items,
         "meta": {"cap": cap, "need": need, "overfill": overfill,
                  "injected": injected,
                  "baseline_name": f"{name}_base", "seed": seed}}

    # 初始摆盘：基底 + 贪心放置的注入件（必须过 check_layout）。
    # 条目不带 gems——宝石随物品在清单附注里列出，玩家手构时自行镶上。
    ents, placed, unplaced = _initial_layout(idx, base["items"], injected)
    init_items = [{"id": e["id"], "at": [e["row"], e["col"]], "r": e["rot"]}
                  for e in ents]
    init_score = analytic_score(idx, ents)
    INIT = {"version": 4, "name": f"{name}_init",
            "character": base["character"], "round": round_no,
            "grid": [ROWS, COLS], "items": init_items,
            "meta": {"h_name": name, "placed": placed, "unplaced": unplaced,
                     "analytic": {"A": init_score["A"], "B": init_score["B"]}}}

    # 基底留档
    BASE = {"version": 4, "name": f"{name}_base",
            "character": base["character"], "round": round_no,
            "grid": [ROWS, COLS],
            "items": [dict(e) for e in base["items"]],
            "meta": {"h_name": name, "corpus_rk": base["rk"],
                     "rating": base["rating"], "bucket": base["bucket"]}}

    _dump_json(os.path.join(out_path, f"{name}.H.json"), H)
    _write_checklist_md(os.path.join(out_path, f"{name}.清单.md"), name,
                        round_no, base["character"], h_items, cap, need,
                        overfill, idx, base["rating"], base["bucket"])
    _dump_json(os.path.join(out_path, f"{name}.初始摆盘.json"), INIT)
    _dump_json(os.path.join(out_path, f"{name}_base.json"), BASE)

    stats = {"name": name, "round": round_no, "character": base["character"],
             "cap": cap, "need": need, "overfill_target": overfill,
             "overfill_achieved": round(achieved, 4),
             "items_total": len(h_items), "items_baseline": len(base["items"]),
             "bags": sum(1 for e in h_items if idx.is_bag(e["id"])),
             "injected": len(injected), "placed_in_init": len(placed),
             "unplaced": len(unplaced),
             "zh_missing": [e["id"] for e in h_items
                            if zh_name(e["id"]) == e["id"]]}
    return {"H": H, "baseline": BASE, "init": INIT, "stats": stats}


def _verify(result: dict, idx: ItemIndex) -> dict:
    """任务书 §7.1 自检：合法性 / 压力 / 中文名 / 统计口径。"""
    H, INIT, stats = result["H"], result["init"], result["stats"]
    base_ents = _to_ents([e for e in result["baseline"]["items"]])
    init_ents = _to_ents(INIT["items"])
    base_ok, base_diag = check_layout(idx, base_ents)
    init_ok, init_diag = check_layout(idx, init_ents)
    return {
        "name": stats["name"],
        "baseline_legal": base_ok,
        "baseline_diags": base_diag if not base_ok else [],
        "init_legal": init_ok,
        "init_diags": init_diag if not init_ok else [],
        "overfill_ok": stats["need"] > stats["cap"] * (1 + stats["overfill_target"] - 1e-9),
        "cap_le_63": stats["cap"] <= COLS * ROWS,
        "ids_in_assets": all(idx.has(e["id"]) for e in H["items"]),
        "zh_missing": stats["zh_missing"],
        "injected_ge_3": stats["injected"] >= 3,
    }


def main(argv=None):
    ap = argparse.ArgumentParser(description="H 生成器（摆盘标尺样本采集 交付物 1）")
    ap.add_argument("--round", type=int, default=None, help="目标回合 1..18")
    ap.add_argument("--character", default=None, help="职业；缺省按该回合分布加权随机")
    ap.add_argument("--inject", type=int, default=3, help="注入件数下限（≥3）")
    ap.add_argument("--overfill", type=float, default=0.10, help="目标超容比例")
    ap.add_argument("--seed", type=int, default=0)
    ap.add_argument("--out", default="probe_samples", help="输出目录（相对仓库根）")
    ap.add_argument("--preset", default=None,
                    help="all = 一次生成任务书 §3.5 的 5 套 × 3 职业")
    ap.add_argument("--pair-s", default=None,
                    help="§6.2 包装：给玩家导出的 S 补 meta（配合 --h --player）")
    ap.add_argument("--h", default=None, help="--pair-s 对应的 H.json")
    ap.add_argument("--player", default="", help="玩家标识（同一 H 多人时区分）")
    args = ap.parse_args(argv)

    if args.pair_s:
        if not args.h:
            ap.error("--pair-s 需要 --h")
        S = pair_with_h(args.pair_s, args.h, player=args.player)
        print(json.dumps(S["meta"], ensure_ascii=False, indent=1))
        return 0

    idx = ItemIndex()

    if args.preset == "all":
        results = []
        for pi, (pname, rnd, inj, ovf) in enumerate(PRESETS):
            for ci, ch in enumerate(PRESET_CHARS):
                r = make_holding(rnd, ch, inj, ovf, seed=pi * 100 + ci,
                                 out_dir=args.out, name=f"{pname}_{ch}")
                v = _verify(r, idx)
                results.append(v)
                s = r["stats"]
                flag = "OK " if all([v["baseline_legal"], v["init_legal"],
                                     v["overfill_ok"], v["cap_le_63"],
                                     v["ids_in_assets"], not v["zh_missing"],
                                     v["injected_ge_3"]]) else "FAIL"
                print(f"[{flag}] {s['name']:24s} cap={s['cap']:3d} "
                      f"need={s['need']:3d} over={s['overfill_achieved']:+.1%} "
                      f"(目标{ovf:+.0%}) items={s['items_total']:2d} "
                      f"注入{s['injected']:2d} 初始摆上{s['placed_in_init']:2d} "
                      f"zh缺失={len(s['zh_missing'])}")
        # 可复现性：对最后一个 H 用同 seed 重跑一遍，序列化逐字节比对
        rep_name = results[-1]["name"]
        _last_seed = (len(PRESETS) - 1) * 100 + len(PRESET_CHARS) - 1
        r2 = make_holding(PRESETS[-1][1], PRESET_CHARS[-1], PRESETS[-1][2],
                          PRESETS[-1][3], seed=_last_seed, out_dir=args.out,
                          name=rep_name)
        ser = lambda o: json.dumps(o, ensure_ascii=False, indent=1) + "\n"
        with open(os.path.join(ROOT, args.out, f"{rep_name}.H.json"),
                  encoding="utf-8") as f:
            on_disk = f.read()
        same = ser(r2["H"]) == on_disk and ser(r2["H"]) == ser(
            _reload_h(args.out, rep_name))
        print(f"[复现] {rep_name}: {'逐字节一致' if same else '不一致!!'}")
        with open(os.path.join(ROOT, args.out, "_summary.json"), "w",
                  encoding="utf-8", newline="\n") as f:
            json.dump(results, f, ensure_ascii=False, indent=1)
        return 0

    if args.round is None:
        ap.error("需要 --round 或 --preset all")
    r = make_holding(args.round, args.character, args.inject, args.overfill,
                     seed=args.seed, out_dir=args.out)
    v = _verify(r, idx)
    s = r["stats"]
    print(json.dumps({"stats": s, "verify": v}, ensure_ascii=False, indent=1))
    return 0


def _reload_h(out_dir: str, name: str) -> dict:
    with open(os.path.join(ROOT, out_dir, f"{name}.H.json"), encoding="utf-8") as f:
        return json.load(f)


# ═════════════════════════ S 配对包装（任务书 §6.2） ═════════════════════════

def pair_with_h(s_path: str, h_path: str, player: str = "",
                out_path: str | None = None) -> dict:
    """给玩家导出的 S 补训练侧 meta：h_name / excluded / player。

    已有导出方法不产出 meta 时用这层包装：读 H 的 items，逐件比对 S，
    多重集合差即 excluded（玩家舍弃的件）。out_path 缺省原地补写 S。
    """
    with open(s_path, encoding="utf-8") as f:
        S = json.load(f)
    with open(h_path, encoding="utf-8") as f:
        H = json.load(f)
    want: Counter = Counter(e["id"] for e in H["items"])
    got: Counter = Counter(e["id"] for e in S.get("items", []))
    excluded = []
    for name in sorted(want):
        for _ in range(want[name] - got.get(name, 0)):
            excluded.append(name)
    S.setdefault("meta", {})
    S["meta"].update({"h_name": H.get("name", os.path.basename(h_path)),
                      "excluded": excluded, "player": player})
    unknown = sorted(set(got) - set(want))
    if unknown:
        S["meta"]["not_in_h"] = unknown  # 对照异常：S 出现了 H 没有的物品
    if out_path:
        _dump_json(out_path, S)
    return S


if __name__ == "__main__":
    sys.exit(main())
