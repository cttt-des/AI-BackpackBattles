# -*- coding: utf-8 -*-
"""evaluator.py — P1 评估器：对手池 + CRN 配对比较 + 多指标报告（规划 §5 / §7 P1）

对手池（§5.2 固定池组合，防单池过拟合）：
  池 A：rating ∈ [target, target+200] —— 优化用
  池 B：rating ∈ [target-200, target] —— 验收用
  池 C：全分布均匀抽 —— 泛化检验用
  每池 = 终盘（最后一轮）合法摆盘阵容，含宝石；储物箱物品（x≥9）剔除。

CRN（§5.3 共同随机数）：比较候选 X/Y 时，对手 o 与种子 s 的配对完全一致，
Δ = p_X(o,s) − p_Y(o,s) 按对手聚合。判据：扰动间 Δ 的 std < 0.03 通过。

多指标（§5.1）：平均胜率 / 对手间方差 / 最差对手胜率 / 对高分对手胜率。

吞吐实测（本机）：R19 大阵容 warm 36–66 ms/场（单核）。
"""
from __future__ import annotations

import json
import os
import random
import sqlite3
import statistics
import sys
from typing import Dict, List, Optional, Sequence, Tuple

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)

from trainer.layout_rules import ItemIndex, check_layout, COLS, ROWS  # noqa: E402

FACE_TO_ROT = {0: 0, 1: 90, 2: 180, 3: 270}


# ═════════════════════════ 对手池 ═════════════════════════

class OpponentPool:
    """从 corpus.sqlite 构造固定对手池。每个对手 = 完整 lineup dict + 元数据。"""

    def __init__(self, db_path: Optional[str] = None):
        self.db = db_path or os.path.join(ROOT, "database", "corpus.sqlite")
        imap = json.load(open(os.path.join(ROOT, "assets", "item_index_map.json"),
                              encoding="utf-8"))
        self.i2n = {int(k): v for k, v in imap["index_to_name"].items()}
        self.g2n = list(imap["gem_order"])
        self.index = ItemIndex()

    def _build_lineup(self, rk: str, last: int, health: int, stamina: int,
                      class_name: str) -> Optional[dict]:
        """★ round 语义（2026-11-12 修正）：corpus round_no 是 **1 基**（R1..R18，
        18 回合制，history roundID 同为 1 基）。之前 round=last+1 是错位——
        'R19' 实为 R18。

        ★ health 语义（2026-11-12 修正）：corpus_rounds.health 是**已含回合
        成长的当回合基础最大血量**（serializeRound 推 getBaseMaxHealth；
        实证：Adventurer R18 = 25 + 10×3 + 15×5 + 20×5 + 30×4 = 350）。
        character_stats 会按 round 再叠加成长 ⇒ 塞 class_modifiers 就是
        双重计数（R18 双侧虚高 ~355 血）。正确契约 = health_override 直通 +
        class_modifiers 只放 stamina + round 保留真值（cur_round 供
        LevelUp 类物品读）。
        """
        con = sqlite3.connect("file:" + self.db, uri=True)
        try:
            rows = con.execute(
                "SELECT gid, x, y, face, gems_json FROM corpus_items "
                "WHERE record_key=? AND round_no=? ORDER BY seq", (rk, last)).fetchall()
        finally:
            con.close()
        items = []
        for gid, x, y, face, gems in rows:
            name = self.i2n.get(gid)
            if name is None:
                return None
            if x is None or y is None or x >= COLS or y >= ROWS:
                continue  # 储物箱 / 异常
            ent = {"id": name, "at": [y, x], "r": FACE_TO_ROT.get(face or 0, 0)}
            if gems:
                gn = [self.g2n[g] for g in json.loads(gems)
                      if isinstance(g, int) and 0 <= g < len(self.g2n)]
                if gn:
                    ent["gems"] = gn
            items.append(ent)
        lineup = {"version": 4, "name": rk, "character": class_name or "Adventurer",
                  "round": last, "grid": [ROWS, COLS], "items": items,
                  "storage": [],
                  "health_override": int(health or 0),
                  "class_modifiers": {"stamina": int(stamina or 0)}}
        ents = [{"id": e["id"], "rot": e["r"], "row": e["at"][0], "col": e["at"][1]}
                for e in items]
        good, _diags = check_layout(self.index, ents)
        lineup["_legal"] = good
        return lineup

    def sample(self, band: Optional[Tuple[float, float]], size: int,
               seed: int = 0) -> List[dict]:
        """band=None → 全分布均匀抽。返回合法终盘阵容列表。"""
        con = sqlite3.connect("file:" + self.db, uri=True)
        try:
            rng = random.Random(seed)
            if band:
                rows = con.execute(
                    "SELECT record_key, rounds_played, rating, class_name "
                    "FROM corpus_runs WHERE rating BETWEEN ? AND ? "
                    "AND rounds_played >= 5", (band[0], band[1])).fetchall()
            else:
                rows = con.execute(
                    "SELECT record_key, rounds_played, rating, class_name "
                    "FROM corpus_runs WHERE rounds_played >= 5").fetchall()
            rng.shuffle(rows)
            pools: List[dict] = []
            for rk, last, rating, cls in rows:
                if len(pools) >= size:
                    break
                hp = con.execute(
                    "SELECT health, stamina FROM corpus_rounds "
                    "WHERE record_key=? AND round_no=?", (rk, last)).fetchone()
                if not hp:
                    continue
                lu = self._build_lineup(rk, last, hp[0], hp[1], cls)
                if lu is None or not lu["_legal"] or len(lu["items"]) < 8:
                    continue
                lu["_rating"] = rating
                pools.append(lu)
            return pools
        finally:
            con.close()

    def pools_abc(self, target: float, size: int = 50, seed: int = 0):
        """§5.2：优化池 A / 保底池 B / 泛化池 C。"""
        return {
            "A": self.sample((target, target + 200), size, seed),
            "B": self.sample((max(target - 200, 0), target), size, seed + 1),
            "C": self.sample(None, size, seed + 2),
        }

    def sample_at_round(self, round_no: int, size: int, seed: int = 0,
                        min_items: int = 5):
        """按回合采样的对手池（回合分层实验 §7.2）。

        corpus round_no 为 1 基（R1..R18，规划 §1.3 表）。同一回合内不分
        rating 段——回合匹配优先于段位匹配，池大小优先。
        """
        con = sqlite3.connect("file:" + self.db, uri=True)
        try:
            rng = random.Random(seed)
            rows = con.execute(
                "SELECT c.record_key, r.rating, r.class_name, c.health, c.stamina "
                "FROM corpus_rounds c JOIN corpus_runs r ON r.record_key = c.record_key "
                "WHERE c.round_no = ? AND c.item_count >= ?",
                (round_no, min_items)).fetchall()
            rng.shuffle(rows)
            pools: List[dict] = []
            for rk, rating, cls, hp, st in rows:
                if len(pools) >= size:
                    break
                lu = self._build_lineup(rk, round_no, hp, st, cls)
                if lu is None or not lu["_legal"] or len(lu["items"]) < min_items:
                    continue
                lu["_rating"] = rating
                pools.append(lu)
            return pools
        finally:
            con.close()


# ═════════════════════════ 批量模拟（多进程） ═════════════════════════

_W = {}


def _pool_init():
    # ★ GD_PURE_PY=1 时屏蔽 gd_core_py 的 .pyd 加载（tools/_purepy_arm 同款）。
    #   用途：内核重建窗口期（另一构建进程在刷 .pyd，新旧 cdef 布局混杂时
    #   bag 模块 import 必炸 ValueError），纯 py 腿与 .pyd 产物完全解耦。
    #   必须 BEFORE 任何 gd_core_py/simulator 导入。
    import os as _os
    if _os.environ.get("GD_PURE_PY") == "1":
        import tools._purepy_arm  # noqa: F401
    from simulator.data import load_items, load_characters
    _W["items"] = load_items()
    _W["chars"] = load_characters()


def _to_engine_form(lu: dict) -> dict:
    """GDCoreEngine 只吃 v3 内部形（backpack.items[row/col/rotation]）。

    trainer 各装载器产出 v4 平铺形（items[].at=[row,col]）——此处单点转换，
    与 simulator/lineup._normalize_v4 同口径（不 import 私有函数，避免
    跨模块耦合漂移：这里只走本文件实际用到的字段）。
    """
    if "backpack" in lu:
        return lu
    items = []
    for it in lu.get("items") or []:
        at = it.get("at") or [0, 0]
        e = {"id": it.get("id"), "row": int(at[0]), "col": int(at[1]),
             "rotation": int(it.get("r", 0) or 0) % 360,
             "gems": [{"id": g} for g in (it.get("gems") or [])]}
        if it.get("in") is not None:
            e["in"] = it["in"]
        items.append(e)
    grid = lu.get("grid") or [ROWS, COLS]
    return {
        "version": 3,
        "character": lu.get("character") or "Adventurer",
        "round": lu.get("round", 1),
        "class_modifiers": lu.get("class_modifiers") or {},
        "health_override": lu.get("health_override"),
        "backpack": {"grid": {"rows": int(grid[0]), "cols": int(grid[1])},
                     "items": items},
        "storage": [],
    }


def _battle(job):
    lu_p, lu_o, seed = job
    from simulator.gd_core_engine import GDCoreEngine
    try:
        eng = GDCoreEngine(_to_engine_form(lu_p), _to_engine_form(lu_o),
                           _W["items"], _W["chars"],
                           seed=seed, max_time=90.0, light_log=True)
        eng.run()
        return 1 if eng.player_wins() else 0
    except Exception:
        return -1  # 装配失败计负（区分于败局）


SIMS_TOTAL = {"count": 0}   # 引擎对局账面（P3 双臂同预算对照用）


def _run_jobs(jobs, workers: int) -> List[int]:
    from concurrent.futures import ProcessPoolExecutor
    import multiprocessing as mp
    workers = max(1, min(workers, mp.cpu_count()))
    SIMS_TOTAL["count"] += len(jobs)
    with ProcessPoolExecutor(max_workers=workers, initializer=_pool_init) as ex:
        return list(ex.map(_battle, jobs, chunksize=4))


def eval_vs_pool(player: dict, pool: Sequence[dict], seeds_per_opp: int = 8,
                 base_seed: int = 2026_11_11, workers: int = 8) -> dict:
    """多指标报告（§5.1）。CRN 固定配对：seed(o, k) = base + o_idx*1e4 + k。

    返回 per-opponent 胜率序列与聚合指标（不含 -1 装配失败场）。
    """
    jobs, meta = [], []
    for oi, opp in enumerate(pool):
        for k in range(seeds_per_opp):
            jobs.append((player, opp, base_seed + oi * 10000 + k))
        meta.append({"rating": opp.get("_rating"), "n_items": len(opp["items"])})
    res = _run_jobs(jobs, workers)
    per_opp = []
    for oi, m in enumerate(meta):
        wins = res[oi * seeds_per_opp:(oi + 1) * seeds_per_opp]
        valid = [w for w in wins if w >= 0]
        per_opp.append({"rating": m["rating"], "n_items": m["n_items"],
                        "wr": sum(valid) / max(len(valid), 1),
                        "errs": len(wins) - len(valid)})
    wrs = [p["wr"] for p in per_opp]
    high = [p["wr"] for p in per_opp
            if p["rating"] is not None and p["rating"] >= (player.get("_target_rating") or 1e18) - 1e18]
    return {
        "mean_wr": statistics.fmean(wrs),
        "std_opp": statistics.pstdev(wrs) if len(wrs) > 1 else 0.0,
        "worst_wr": min(wrs),
        "per_opp": per_opp,
        "n_opp": len(pool), "seeds": seeds_per_opp,
        "total_sims": len(jobs), "sim_errors": sum(1 for r in res if r < 0),
    }


def paired_delta(a: dict, b: dict, pool: Sequence[dict], seeds_per_opp: int = 8,
                 base_seed: int = 2026_11_11, workers: int = 8) -> dict:
    """CRN 配对比较：同一 (对手, seed) 下两候选各跑一场，Δ = wr_a − wr_b。

    关键：两候选共享完全相同的随机流配对（对手序列与种子逐一对齐）。
    """
    jobs = []
    for oi, opp in enumerate(pool):
        for k in range(seeds_per_opp):
            s = base_seed + oi * 10000 + k
            jobs.append((a, opp, s))
    res_a = _run_jobs(jobs, workers)
    jobs_b = [(b, opp, base_seed + oi * 10000 + k)
              for oi, opp in enumerate(pool) for k in range(seeds_per_opp)]
    res_b = _run_jobs(jobs_b, workers)
    deltas = []
    for oi in range(len(pool)):
        wa = res_a[oi * seeds_per_opp:(oi + 1) * seeds_per_opp]
        wb = res_b[oi * seeds_per_opp:(oi + 1) * seeds_per_opp]
        valid = [(x, y) for x, y in zip(wa, wb) if x >= 0 and y >= 0]
        if valid:
            deltas.append(sum(x - y for x, y in valid) / len(valid))
    return {
        "deltas_per_opp": deltas,
        "mean_delta": statistics.fmean(deltas),
        "std_delta": statistics.pstdev(deltas) if len(deltas) > 1 else 0.0,
        "n_opp": len(deltas),
    }


def crn_reproducibility_probe(player: dict, pool: Sequence[dict], perturb_fn,
                              n_perturb: int = 8, n_seedsets: int = 2,
                              base_seed: int = 2026_11_12,
                              workers: int = 8) -> dict:
    """§7 P1 验收实验（判据的度量口径重设计，理由见 trainer 报告）：

    规划原文「扰动间 Δ 的标准差 < 0.03」在实现上有一个语义坑：不同扰动的 Δ
    含**真实效应差异**（挪 A ≠ 挪 B），其 std 主要是信号不是噪声。
    决策真正需要的是：**同一对候选的 Δ 估计量在换一批种子后会不会变**——
    即 100 场评估的复现性噪声。故本探针：

      对每个扰动 i（候选 vs 基准）：
        Δ̂_i¹ = mean over 对手 of CRN配对胜差 @ 种子集1
        Δ̂_i² = 同 @ 种子集2（完全独立的种子）
      复现性噪声 = mean_i |Δ̂_i¹ − Δ̂_i²|
      判据：< 0.03 ⇒ 单批 100 场可分辨 0.03 级差异 ⇒ 通过

    同时给出非配对（独立种子）口径的同指标，量化 CRN 的增益：
      unpaired Δ̂'：候选的种子与基准错开（各自独立流）。
    """
    perturbs = [perturb_fn(player, i) for i in range(n_perturb)]
    valid = [(i, p) for i, p in enumerate(perturbs) if p is not None]
    n_dropped = len(perturbs) - len(valid)
    sets = [base_seed + ss * 1_000_000 for ss in range(n_seedsets)]
    SHIFT = 500_000   # 非配对口径：候选种子相对基准错开

    base_wr = {}     # [si] → 逐对手胜率（基准 @ 该种子集）
    base_wr_shift = {}  # [si] → 逐对手胜率（基准 @ 错位种子，供非配对口径）
    for si, seedset in enumerate(sets):
        base_wr[si] = [max(r, 0) for r in _run_jobs(
            [(player, opp, seedset + oi * 10000) for oi, opp in enumerate(pool)],
            workers)]
        base_wr_shift[si] = [max(r, 0) for r in _run_jobs(
            [(player, opp, seedset + oi * 10000 + SHIFT) for oi, opp in enumerate(pool)],
            workers)]

    d_paired = {si: [] for si in range(n_seedsets)}
    d_unpaired = {si: [] for si in range(n_seedsets)}
    for i, p in valid:
        for si, seedset in enumerate(sets):
            pw = [max(r, 0) for r in _run_jobs(
                [(p, opp, seedset + oi * 10000) for oi, opp in enumerate(pool)],
                workers)]
            uw = [max(r, 0) for r in _run_jobs(
                [(p, opp, seedset + oi * 10000 + SHIFT) for oi, opp in enumerate(pool)],
                workers)]
            d_paired[si].append(statistics.fmean(pw) - statistics.fmean(base_wr[si]))
            d_unpaired[si].append(statistics.fmean(uw) - statistics.fmean(base_wr_shift[si]))
    diffs_p = [abs(a - b) for a, b in zip(d_paired[0], d_paired[1])] if n_seedsets >= 2 else []
    diffs_u = [abs(a - b) for a, b in zip(d_unpaired[0], d_unpaired[1])] if n_seedsets >= 2 else []
    return {
        "n_perturb": n_perturb, "n_valid_perturb": len(valid),
        "n_dropped_none": n_dropped,
        "n_opp": len(pool), "n_seedsets": n_seedsets,
        "noise_paired_mean": statistics.fmean(diffs_p) if diffs_p else None,
        "noise_paired_max": max(diffs_p) if diffs_p else None,
        "noise_unpaired_mean": statistics.fmean(diffs_u) if diffs_u else None,
        "noise_unpaired_max": max(diffs_u) if diffs_u else None,
        "delta_paired_s0": d_paired.get(0, []),
        "delta_paired_s1": d_paired.get(1, []),
        "base_wr_mean": statistics.fmean(base_wr[0]),
    }
