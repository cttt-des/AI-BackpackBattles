# -*- coding: utf-8 -*-
"""consistency_suite.py — 模拟器 ↔ 真值一致性评分套件（docs/consistency_workflow.md §3 Phase 2 / M3）

对 dist/output/combat_logs/ 每组真值（双方阵容 v4 JSON + 事件日志）：
  1. 用 gd_core 内核（simulator.simulate.simulate_once，ENGINES=("gd_core",)）同阵容跑
     3 个种子（42/43/44）——直接同进程 import，不为单场起子进程；
  2. 逐组产出：
     · 胜负方向命中（3 seed 多数胜负 vs 真值 Win/Loss）
     · 时长中位数差（模拟 3 seed 中位 vs 真值末事件 t）
     · 双方 HP 终值差（tools/canonical_events.py 的 HP 账本口径：格挡前
       params.damage 记借，真值/模拟同口径，可直比）
     · HP 逐秒曲线距离（L1，真值 vs 各 seed 模拟曲线取中位；曲线末端各自
       冻结在终值）
     · 逐类型事件量比（真值计数 vs 模拟 3 seed 中位数，规范化事件流口径）
     · 偏差最大物品（激活/伤害比 = 模拟中位 / 真值，|max_ratio-1| 最大者）
  3. 汇总 output/consistency_report.json：{score, summary, worstGroups, perGroup}，
     并打印一段话总结。

评分（0-100，逐组加权，总分 = 可评分组的均值）：
  方向命中 30 · 时长 15（|差|/真值 ≥50% 记 0）· HP 终值 15（均差/初始 ≥30% 记 0）
  · HP 曲线 20（L1/秒/双方初始和 ≥5% 记 0）· 事件量比 15（∈[0.6,1.6] 占比）
  · 物品偏差 5（|比-1| ≥100% 记 0）

单组异常（阵容 id 不在物品库 → _MissingItem、位流解码失败等）记为该组
{"error": ...} 并继续，不拖垮全量。个别 seed 失败时该 seed 剔除、组内用余下
seed；全部 seed 失败才算组 error。

用法:
    python -X utf8 tools/consistency_suite.py --groups 2   # 快速试跑
    python -X utf8 tools/consistency_suite.py              # 全量（约 5-15 分钟）
"""
from __future__ import annotations

import argparse
import glob
import json
import os
import statistics
import sys
import time
from collections import Counter
from typing import Any, Dict, List, Optional

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)

from tools.canonical_events import (            # noqa: E402  HP 账本 + 规范事件流
    build_hp_ledger,
    initial_hp_from_lineup,
    parse_sim_events,
    parse_truth_group,
)

TRUTH_DIR = os.path.join(ROOT, "dist", "output", "combat_logs")
OUT_PATH = os.path.join(ROOT, "output", "consistency_report.json")
SEEDS = (42, 43, 44)
MAX_TIME = 90.0                        # simulate_once 默认口径；实录时长 ≤44s，均覆盖

# ── 评分权重（总分 100） ────────────────────────────────────────────────────
W_DIRECTION, W_TIME, W_HP_END, W_CURVE, W_EVENTS, W_ITEM = 30, 15, 15, 20, 15, 5
# 容差标定（分量扣到 0 的偏差幅度）
TIME_TOL = 0.5         # 时长相对差 ≥50% → 0 分
HP_END_TOL = 0.3       # HP 终值均差/初始 ≥30% → 0 分
CURVE_TOL = 0.05       # 每秒 L1 / 双方初始和 ≥5% → 0 分
EVENT_RATIO_OK = (0.6, 1.6)   # 事件量比合格区间（同 tools/compare_truth.py 口径）
ITEM_TOL = 1.0         # 物品 |比-1| ≥100% → 0 分
# 物品进入"偏差最大"候选的最小真值量（过滤小样本噪声）
ITEM_MIN_ACT, ITEM_MIN_DMG = 3, 30.0

# 模拟流伤害源 origin（simulator/gd_core_engine.py::_origin_key，小写关键字）
# → 真值 type_name 口径（core/combatlog_reader.py 导出的 origin.name）
_DMG_SOURCE_NORM = {
    "fatigue": "Fatigue", "poison": "Poison", "spikes": "Spikes",
    "unhealing": "Unhealing", "vampirism": "Vampirism",
    "regen": "Regeneration", "bl": "Block", "mana": "Mana",
    "empower": "Empower", "heat": "Heat", "lucky": "Lucky",
    "cold": "Cold", "blind": "Blind",
}


def _norm_origin(key: Optional[str]) -> Optional[str]:
    """模拟 origin 关键字 → 真值 origin.name 口径（物品名两边一致，直通）。"""
    if key is None:
        return None
    return _DMG_SOURCE_NORM.get(key, key)


def truth_groups(limit: Optional[int] = None) -> List[str]:
    out = []
    for grp in sorted(glob.glob(os.path.join(TRUTH_DIR, "*"))):
        base = os.path.join(grp, os.path.basename(grp))
        if os.path.isfile(base + ".Player.json"):
            out.append(grp)
            if limit is not None and len(out) >= limit:
                break
    return out


# ═══════════════════════════ 真值侧 ═══════════════════════════

def truth_metrics(grp_path: str) -> Dict[str, Any]:
    """一组真值 → 方向/时长/HP 账本/逐秒曲线/逐类型计数/逐物品量。"""
    grp = parse_truth_group(grp_path)
    lineups = grp["lineups"]
    if lineups["P"] is None or lineups["O"] is None:
        raise FileNotFoundError("组目录缺阵容 JSON，无法推初始 HP")
    tev = grp["events"]
    if not tev:
        raise ValueError("真值事件流为空")
    truth_win = any(e["type"] == "Win" for e in tev)
    truth_time = max(e["t"] for e in tev)
    p0 = initial_hp_from_lineup(lineups["P"])
    o0 = initial_hp_from_lineup(lineups["O"])
    ledger = build_hp_ledger(tev, p0, o0)
    return {
        "events": tev,
        "truth_win": truth_win,
        "truth_time": truth_time,
        "hp_initial": {"P": p0, "O": o0},
        "hp_terminal": ledger["terminal"],
        "curve": ledger["curve_per_second"],
        "type_counts": Counter(e["type"] for e in tev),
        "item_usage": item_usage(tev),
    }


def item_usage(events: List[Dict[str, Any]]) -> Dict[Any, Dict[str, float]]:
    """规范化事件流 → {(side, origin): {act, dmg}}（per_item_diff.py 同口径：
    Activation 计激活，DealDamage/CriticalDamage 按 params.damage 计伤害）。"""
    usage: Dict[Any, Dict[str, float]] = {}
    for e in events:
        key = e.get("origin_key")
        if not key:
            continue
        side = e.get("side")
        if side not in ("P", "O"):
            continue
        t = e["type"]
        if t == "Activation":
            slot = usage.setdefault((side, key), {"act": 0, "dmg": 0.0})
            slot["act"] += 1
        elif t in ("DealDamage", "CriticalDamage"):
            dmg = (e.get("params") or {}).get("damage")
            if isinstance(dmg, (int, float)) and not isinstance(dmg, bool):
                slot = usage.setdefault((side, key), {"act": 0, "dmg": 0.0})
                slot["dmg"] += float(dmg)
    return usage


# ═══════════════════════════ 模拟侧 ═══════════════════════════

def sim_event_dicts(eng) -> List[Dict[str, Any]]:
    """引擎事件视图（_EventOut）→ parse_sim_events 可解析的 dict 列表。

    ★ 不能走 eng.log.to_dict()：它不带 buff_type，栈事件（Block/Lucky/Mana…）
    会全部数不成类型（ai/compare_gd_truth.py 同款结论）。这里直接用
    eng.log.events，把 buff_type 一并带给 canonical.parse_sim_events。
    """
    out = []
    for e in eng.log.events:
        origin = getattr(e.origin, "key", None) if e.origin is not None else None
        out.append({
            "t": e.t, "type": e.type, "actor": e.actor, "target": e.target,
            "origin": _norm_origin(origin), "params": dict(e.params or {}),
            "buff_type": e.buff_type,
        })
    return out


def run_seed(player_path: str, opponent_path: str, item_db, character_db,
             seed: int) -> Dict[str, Any]:
    """单 seed 模拟 → 该 seed 的全部观测。异常向上抛（由组级捕获降级）。"""
    from simulator.simulate import simulate_once          # 引擎为 gd_core
    from ai.kernel_reset import reset_kernel_state        # 逐局清进程级全局态
    reset_kernel_state()
    eng = simulate_once(player_path, opponent_path, item_db, character_db,
                        seed=seed, max_time=MAX_TIME, engine="gd_core")
    events = parse_sim_events(sim_event_dicts(eng))
    row: Dict[str, Any] = {
        "seed": seed,
        "win": bool(eng.player_wins()),
        "time": float(eng.summary()["time"]),
        "hp_initial": {"P": float(eng.player.get_max_health()),
                       "O": float(eng.opponent.get_max_health())},
        "type_counts": Counter(e["type"] for e in events),
        "item_usage": item_usage(events),
        "hp": None, "curve": None,
    }
    # HP 账本可能与事件计数解耦失败（如个别事件受害方推导不出）——
    # 计数照常产出，HP 指标记 None，不连坐整局。
    try:
        ledger = build_hp_ledger(events, row["hp_initial"]["P"],
                                 row["hp_initial"]["O"], MAX_TIME)
        row["hp"] = ledger["terminal"]
        row["curve"] = ledger["curve_per_second"]
    except ValueError as exc:
        row["hp_error"] = repr(exc)
    return row


# ═══════════════════════════ 度量 ═══════════════════════════

def curve_l1(curve_a: List[Dict[str, Any]], curve_b: List[Dict[str, Any]],
             term_a: Dict[str, float], term_b: Dict[str, float]) -> float:
    """两条逐秒 HP 曲线的 L1 距离：Σ_s (|ΔP| + |ΔO|)。

    秒级对齐（canonical 账本逐秒快照，整数秒齐备）；一条曲线在其末事件之后
    冻结在终值（战斗已结束，HP 不再变动）。
    """
    def fn(curve, term):
        pts = {int(c["t"]): (c["hp_p"], c["hp_o"]) for c in curve
               if int(c["t"]) == c["t"]}
        last_t = max((c["t"] for c in curve), default=0.0)

        def val(s: int):
            if s > last_t:
                return term["P"], term["O"]
            if s in pts:
                return pts[s]
            prev = [k for k in pts if k <= s]   # 防御：整数快照缺位时取最近
            return pts[max(prev)] if prev else (term["P"], term["O"])
        return val, last_t

    fa, la = fn(curve_a, term_a)
    fb, lb = fn(curve_b, term_b)
    total = 0.0
    for s in range(int(max(la, lb)) + 1):
        ap, ao = fa(s)
        bp, bo = fb(s)
        total += abs(ap - bp) + abs(ao - bo)
    return total


def event_ratios(t_counts: Counter, sim_counts: List[Counter]) -> Dict[str, Dict]:
    """逐类型事件量比：真值计数 vs 模拟中位（真值 >0 的类型；模拟独有类型
    记 ratio=None 供排查）。"""
    out: Dict[str, Dict] = {}
    sim_union: set = set().union(*[set(c) for c in sim_counts]) if sim_counts else set()
    types = sorted(({t for t, v in t_counts.items() if v > 0} | sim_union)
                   - {"combat_start", "combat_end", "Stack"})
    for t in types:
        tv = t_counts.get(t, 0)
        med = statistics.median(c.get(t, 0) for c in sim_counts)
        if tv > 0:
            out[t] = {"truth": tv, "sim_med": med,
                      "ratio": round(med / tv, 2)}
        else:
            out[t] = {"truth": 0, "sim_med": med, "ratio": None}
    return out


def worst_item(t_usage: Dict[Any, Dict[str, float]],
               sim_usages: List[Dict[Any, Dict[str, float]]]) -> Optional[Dict]:
    """偏差最大物品：真值量达标的 (side,item) 中 |比-1| 最大者（激活/伤害比）。

    比 = 模拟 3 seed 中位 / 真值；模拟缺该物品（真值物品不在物品库等）→ 比 0，
    恰是"未知物品被忽略"陷阱的可见化。
    """
    keys = set(t_usage)
    for u in sim_usages:
        keys |= set(u)

    def med(u_list, key, field):
        return statistics.median(u.get(key, {}).get(field, 0) for u in u_list)

    best = None
    for key in keys:
        tu = t_usage.get(key, {})
        t_act, t_dmg = tu.get("act", 0), tu.get("dmg", 0.0)
        m_act = med(sim_usages, key, "act")
        m_dmg = med(sim_usages, key, "dmg")
        if t_act < ITEM_MIN_ACT and t_dmg < ITEM_MIN_DMG:
            continue                     # 真值样本太小，比值全是噪声
        devs, ratios = [], {}
        if t_act > 0:
            r = m_act / t_act
            ratios["act"] = round(r, 2)
            devs.append(abs(r - 1))
        if t_dmg > 0:
            r = m_dmg / t_dmg
            ratios["dmg"] = round(r, 2)
            devs.append(abs(r - 1))
        if not devs:
            continue
        dev = max(devs)
        if best is None or dev > best["dev"]:
            best = {"side": key[0], "item": key[1], "dev": round(dev, 2),
                    "act_truth": t_act, "act_sim_med": m_act,
                    "dmg_truth": round(t_dmg, 1), "dmg_sim_med": round(m_dmg, 1),
                    "ratios": ratios}
    return best


# ═══════════════════════════ 评分 ═══════════════════════════

def _clamp01(x: float) -> float:
    return max(0.0, min(1.0, x))


def score_group(m: Dict[str, Any]) -> Dict[str, Any]:
    """逐组评分 0-100（权重与容差见模块 docstring）。"""
    comp: Dict[str, float] = {}
    comp["direction"] = W_DIRECTION if m["direction_hit"] else 0.0

    rel_time = abs(m["sim_time_median"] - m["truth_time"]) / max(m["truth_time"], 1.0)
    comp["time"] = W_TIME * _clamp01(1 - rel_time / TIME_TOL)

    init_avg = (m["hp_initial"]["P"] + m["hp_initial"]["O"]) / 2
    diffs = [abs(m["hp_terminal_diff"][s]) for s in ("P", "O")]
    hp_rel = (sum(diffs) / len(diffs)) / max(init_avg, 1.0)
    comp["hp_end"] = W_HP_END * _clamp01(1 - hp_rel / HP_END_TOL)

    horizon = max(m["truth_time"], m["sim_time_median"], 1.0)
    init_sum = m["hp_initial"]["P"] + m["hp_initial"]["O"]
    curve_rate = m["hp_curve_l1"] / (horizon * max(init_sum, 1.0))
    comp["curve"] = W_CURVE * _clamp01(1 - curve_rate / CURVE_TOL)

    ratios = [v["ratio"] for v in m["event_ratios"].values()
              if v["ratio"] is not None]
    comp["events"] = W_EVENTS * (_clamp01(sum(
        1 for r in ratios if EVENT_RATIO_OK[0] <= r <= EVENT_RATIO_OK[1]
    ) / len(ratios)) if ratios else 1.0)

    comp["item"] = W_ITEM if m["worst_item"] is None else \
        W_ITEM * _clamp01(1 - m["worst_item"]["dev"] / ITEM_TOL)

    score = round(sum(comp.values()))
    return {"score": score, "components": {k: round(v, 1) for k, v in comp.items()}}


def worst_sentence(m: Dict[str, Any]) -> str:
    """主要偏差一句话：取失分最多的分量组织措辞。"""
    comp = m["components"]
    weight = {"direction": W_DIRECTION, "time": W_TIME, "hp_end": W_HP_END,
              "curve": W_CURVE, "events": W_EVENTS, "item": W_ITEM}
    key = min(comp, key=lambda k: comp[k] / weight[k])
    if key == "direction":
        return "胜负方向未命中（3 seed 多数与真值相反）"
    if key == "time":
        return ("时长偏差 %.1fs（真值 %.1fs vs 模拟中位 %.1fs）"
                % (m["sim_time_median"] - m["truth_time"], m["truth_time"],
                   m["sim_time_median"]))
    if key == "hp_end":
        return ("HP 终值差 P%+.0f/O%+.0f（真值 P%.0f/O%.0f）"
                % (m["hp_terminal_diff"]["P"], m["hp_terminal_diff"]["O"],
                   m["hp_terminal"]["P"], m["hp_terminal"]["O"]))
    if key == "curve":
        return ("HP 逐秒曲线 L1=%.0f（每秒约占双方初始和 %.1f%%）"
                % (m["hp_curve_l1"],
                   100 * m["hp_curve_l1"] / (max(m["truth_time"], 1.0)
                                             * max(m["hp_initial"]["P"]
                                                   + m["hp_initial"]["O"], 1.0))))
    if key == "events":
        bad = sorted(((t, v) for t, v in m["event_ratios"].items()
                      if v["ratio"] is not None
                      and not (EVENT_RATIO_OK[0] <= v["ratio"] <= EVENT_RATIO_OK[1])),
                     key=lambda kv: abs(1 - kv[1]["ratio"]))
        if bad:
            t, v = bad[-1]
            return "事件量比偏差最大：%s ×%.2f（真值 %d vs 模拟中位 %.0f）" % (
                t, v["ratio"], v["truth"], v["sim_med"])
        return "事件量比整体偏离"
    if m["worst_item"] is not None:
        wi = m["worst_item"]
        return "偏差最大物品：%s（%s）激活 ×%s / 伤害 ×%s" % (
            wi["item"], wi["side"], wi["ratios"].get("act", "-"),
            wi["ratios"].get("dmg", "-"))
    return "偏差轻微"


# ═══════════════════════════ 主流程 ═══════════════════════════

def evaluate_group(grp_path: str, item_db, character_db,
                   seeds: List[int]) -> Dict[str, Any]:
    name = os.path.basename(grp_path.rstrip("\\/"))
    base = os.path.join(grp_path, name)
    try:
        tm = truth_metrics(grp_path)
    except Exception as e:  # noqa: BLE001 —— 单组真值解析失败不拖垮全量
        return {"name": name, "error": "truth: %r" % (e,)}

    rows: List[Dict[str, Any]] = []
    seed_errors: List[str] = []
    for seed in seeds:
        try:
            rows.append(run_seed(base + ".Player.json", base + ".Opponent.json",
                                 item_db, character_db, seed))
        except Exception as e:  # noqa: BLE001 —— 单 seed 失败剔除，不连坐整组
            seed_errors.append("seed%d: %r" % (seed, e))
    if not rows:
        return {"name": name, "error": "all seeds failed: " + "; ".join(seed_errors)}

    wins = [r["win"] for r in rows]
    direction_hit = (sum(wins) > len(wins) / 2) == tm["truth_win"]

    sim_time_med = statistics.median(r["time"] for r in rows)
    hp_rows = [r for r in rows if r["hp"] is not None]
    curve_rows = [r for r in rows if r["curve"] is not None]

    hp_terminal_sim_med = {s: (statistics.median(r["hp"][s] for r in hp_rows)
                               if hp_rows else None) for s in ("P", "O")}
    hp_terminal_diff = {s: (hp_terminal_sim_med[s] - tm["hp_terminal"][s]
                            if hp_terminal_sim_med[s] is not None else None)
                        for s in ("P", "O")}
    l1s = [curve_l1(tm["curve"], r["curve"], tm["hp_terminal"], r["hp"])
           for r in curve_rows]
    hp_curve_l1 = statistics.median(l1s) if l1s else None

    m: Dict[str, Any] = {
        "name": name,
        "truth_win": tm["truth_win"], "truth_time": round(tm["truth_time"], 2),
        "seeds_run": [r["seed"] for r in rows],
        "seed_errors": seed_errors,
        "sim_win_rate": round(sum(wins) / len(wins), 2),
        "direction_hit": direction_hit,
        "sim_time_median": round(sim_time_med, 2),
        "time_median_diff": round(sim_time_med - tm["truth_time"], 2),
        "hp_initial": tm["hp_initial"],
        "hp_terminal": {s: round(tm["hp_terminal"][s], 1) for s in ("P", "O")},
        "hp_terminal_sim_med": {s: (round(hp_terminal_sim_med[s], 1)
                                    if hp_terminal_sim_med[s] is not None else None)
                                for s in ("P", "O")},
        "hp_terminal_diff": {s: (round(hp_terminal_diff[s], 1)
                                 if hp_terminal_diff[s] is not None else None)
                             for s in ("P", "O")},
        "hp_curve_l1": round(hp_curve_l1, 1) if hp_curve_l1 is not None else None,
        "event_ratios": event_ratios(tm["type_counts"],
                                     [r["type_counts"] for r in rows]),
        "worst_item": worst_item(tm["item_usage"],
                                 [r["item_usage"] for r in rows]),
        "per_seed": [{"seed": r["seed"], "win": r["win"], "time": round(r["time"], 2),
                      "hp_terminal": (None if r["hp"] is None
                                      else {s: round(r["hp"][s], 1)
                                            for s in ("P", "O")})}
                     for r in rows],
    }
    # 评分需要的字段不允许 None（HP 账本全失败的组降级为缺指标 → 不评分）
    hp_ok = all(m[k][s] is not None for k in ("hp_terminal_diff",)
                for s in ("P", "O")) and m["hp_curve_l1"] is not None
    if hp_ok:
        m.update(score_group(m))
        m["worst"] = worst_sentence(m)
    else:
        m["score"] = None
        m["components"] = None
        m["worst"] = "HP 账本重建失败（seed 全部缺 HP 观测），未评分"
    return m


def main(argv: Optional[List[str]] = None) -> int:
    if hasattr(sys.stdout, "reconfigure"):
        sys.stdout.reconfigure(encoding="utf-8", errors="replace")
    ap = argparse.ArgumentParser(
        description="模拟器 ↔ 真值一致性评分套件（consistency_workflow M3）")
    ap.add_argument("--groups", type=int, default=None, metavar="N",
                    help="只跑前 N 组（试跑用；默认全量）")
    ap.add_argument("--seeds", default=",".join(map(str, SEEDS)),
                    help="种子列表（默认 42,43,44）")
    ap.add_argument("--out", default=OUT_PATH, help="报告输出路径")
    args = ap.parse_args(argv)
    seeds = [int(s) for s in args.seeds.split(",") if s.strip()]

    from simulator.data import load_items, load_characters
    item_db = load_items()
    character_db = load_characters()

    groups = truth_groups(args.groups)
    print(f"真值组: {len(groups)}  种子: {seeds}  内核: gd_core"
          f"（simulator.simulate.simulate_once 同进程）\n")

    per_group = []
    t_all = time.time()
    for i, grp in enumerate(groups, 1):
        t0 = time.time()
        m = evaluate_group(grp, item_db, character_db, seeds)
        per_group.append(m)
        if "error" in m:
            print("[%d/%d] %-44s ERROR: %s" % (i, len(groups), m["name"], m["error"]))
        else:
            print("[%d/%d] %-44s 得分 %s  方向%s  时长 %.1fs vs %.1fs  "
                  "HP差 P%+.0f/O%+.0f  L1=%s  (%.1fs)"
                  % (i, len(groups), m["name"], m["score"],
                     "✓" if m["direction_hit"] else "✗",
                     m["sim_time_median"], m["truth_time"],
                     m["hp_terminal_diff"]["P"] or 0, m["hp_terminal_diff"]["O"] or 0,
                     m["hp_curve_l1"], time.time() - t0))
        sys.stdout.flush()

    scored = [m for m in per_group if m.get("score") is not None]
    errored = [m for m in per_group if "error" in m]
    total_score = round(statistics.mean(m["score"] for m in scored)) if scored else 0

    worst_groups = {}
    for m in per_group:
        if "error" in m:
            worst_groups[m["name"]] = "组级错误：" + m["error"]
        elif m.get("worst"):
            worst_groups[m["name"]] = m["worst"]

    dir_hits = sum(1 for m in scored if m["direction_hit"])
    if scored:
        parts = [
            "共 %d 组真值、%d 个种子，可评分 %d 组、组级错误 %d 组；" % (
                len(per_group), len(seeds), len(scored), len(errored)),
            "总分 %d/100，" % total_score,
            "胜负方向命中 %d/%d，" % (dir_hits, len(scored)),
            "平均时长差 %+.1fs，" % (statistics.mean(
                m["time_median_diff"] for m in scored) if scored else 0),
        ]
        w_named = [(m["name"], m["worst"]) for m in
                   sorted(scored, key=lambda m: m["score"])[:3]
                   if m.get("worst")]
        if w_named:
            parts.append("偏差最突出的组：" + "；".join(
                "%s（%s）" % (n, w) for n, w in w_named) + "。")
        if errored:
            parts.append("错误组：%s。" % ", ".join(m["name"] for m in errored))
        summary = "".join(parts)
    else:
        summary = "全部 %d 组均失败，无法评分。" % len(per_group)
    print("\n" + summary)

    report = {
        "score": total_score,
        "summary": summary,
        "engine": "gd_core（simulator.simulate.simulate_once，同进程 import）",
        "seeds": seeds,
        "groups_total": len(per_group),
        "groups_scored": len(scored),
        "groups_error": len(errored),
        "direction_hits": dir_hits,
        "worstGroups": worst_groups,
        "perGroup": per_group,
    }
    os.makedirs(os.path.dirname(args.out), exist_ok=True)
    with open(args.out, "w", encoding="utf-8") as f:
        json.dump(report, f, ensure_ascii=False, indent=1)
    print("报告: %s（耗时 %.0fs）" % (args.out, time.time() - t_all))
    return 0


if __name__ == "__main__":
    sys.exit(main())
