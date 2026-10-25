# -*- coding: utf-8 -*-
"""eval_report.py — 重摆候选的引擎级评测报告（原阵容基线 vs 候选，同 seed 对比）

为什么需要这个脚本
==================
此前 ai/ 下没有任何评测脚本：smoke_placer 只「跑引擎不报错」就算过、从不跑
原阵容基线、也不看胜率——一次实跑 5 个候选全部 0/5 仍然 PASS。本脚本补上
引擎级验收：

1. **同 seed 配对对比**：原阵容（基线）与每个重摆候选各跑同一组 seed
   （配对减方差），报告各自的引擎胜率与差值。每局前经 ai/kernel_reset
   重置内核进程级全局态，保证 (配置, 对手, seed) → 结局确定（2026-10-03 修复）。
2. **引擎装配计数**：记录引擎实际装配的物品数（len(engine.player_items)），
   量化「重摆不得丢物品」在引擎侧是否成立（袋内物品引擎不装配，
   见 simulator/gd_core_engine.py 文件头「已知边界」）。
3. **搜索污染的显式声明 + 泛化对照**：候选是 placer 在**这个固定对手上**
   best-of-search 选出来的，固定对手上的数字是「选内」数字，天然偏乐观；
   脚本另从真值实录池抽 K 个**未参与选优**的对手，报告候选在它们上面的
   胜率（「选外」泛化数字）。选内/选外两组都进报告。
4. **代理 vs 引擎校准**：候选的 proxy_winrate 与引擎胜率并列报告并算
   Spearman 秩相关（候选数 ≥3 时）——代理分是否兑现为引擎胜率，一目了然。

用法
====
    python ai/eval_report.py --lineup <Player.json> --opponent <Opponent.json>
                             [--placer-out ai/placer_out.json] [--seeds 20]
                             [--seed 101] [--extra-opponents 3]
                             [--out ai/eval_report.json]
stdout 输出人类可读摘要；完整报告写 --out（默认 ai/eval_report.json）。
"""
from __future__ import annotations

import argparse
import glob
import json
import os
import sys
import time
from typing import Dict, List, Optional, Tuple

_REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if _REPO not in sys.path:
    sys.path.insert(0, _REPO)

from simulator.gd_core_engine import GDCoreEngine          # noqa: E402
from simulator.lineup import load_lineup                   # noqa: E402
from ai.kernel_reset import reset_kernel_state             # noqa: E402
from ai.train import spearman                              # noqa: E402

DEFAULT_PLACER_OUT = os.path.join(_REPO, "ai", "placer_out.json")
DEFAULT_OUT = os.path.join(_REPO, "ai", "eval_report.json")
COMBAT_LOGS_DIR = os.path.join(_REPO, "dist", "output", "combat_logs")

# worker 进程共享的阵容（Pool initializer 注入，避免每任务重复装载内核/阵容）
_G: Dict[str, object] = {}


def _pool_init(baseline: dict, candidates: List[dict], opponents: List[Tuple[str, dict]]):
    _G["baseline"] = baseline
    _G["candidates"] = candidates
    _G["opponents"] = opponents


def _run_one(task: Tuple[str, int, int]) -> dict:
    """(config 名, 对手下标, seed) → 一局结果。任何异常折成 error。"""
    cfg, oi, seed = task
    try:
        if cfg == "__baseline__":
            player = _G["baseline"]
        else:
            player = _G["candidates"][int(cfg)]
        opp_name, opp = _G["opponents"][oi]
        # 每局前清内核进程级全局态：同 (配置, 对手, seed) 的结局必须是确定
        # 函数，否则同 seed 配对随 worker 进程历史漂移（ai/kernel_reset.py）。
        reset_kernel_state()
        eng = GDCoreEngine(player, opp, {}, {}, seed=seed)
        fielded = len(eng.player_items)          # 引擎实际装配的物品数
        eng.run()
        return {"cfg": cfg, "opp": oi, "win": bool(eng.player_wins()),
                "fielded": fielded, "reason": str(eng.win_reason)}
    except Exception as exc:                     # noqa: BLE001
        return {"cfg": cfg, "opp": oi, "error": "%s: %s" % (type(exc).__name__, exc)}


def pick_extra_opponents(k: int, exclude_path: str, seed: int) -> List[Tuple[str, dict]]:
    """从真值实录池抽 K 个对手（剔除含不可装配物品的实录——引擎装配会抛
    _MissingItem，同 ai/gen_dataset.load_truth_pool 口径），排除与本次评测
    固定对手同目录（同一局实录）的阵容。"""
    import random
    from ai.gen_dataset import load_runtime, playable_pool, lineup_ids
    data = load_runtime()
    pool_ok = playable_pool(data)
    seen_dirs = {os.path.dirname(os.path.abspath(exclude_path))}
    pool: List[Tuple[str, dict]] = []
    for path in sorted(glob.glob(os.path.join(COMBAT_LOGS_DIR, "*", "*.Opponent.json"))):
        d = os.path.dirname(os.path.abspath(path))
        if d in seen_dirs:
            continue
        seen_dirs.add(d)
        try:
            lu = load_lineup(path)
        except Exception:                        # noqa: BLE001
            continue
        if any(i not in pool_ok for i in lineup_ids(lu)):
            continue
        pool.append((os.path.basename(d), lu))
    rng = random.Random(seed)
    rng.shuffle(pool)
    return pool[:max(k, 0)]


def run_eval(player_path: str, opponent_path: str, placer_out_path: str,
             seeds: List[int], n_extra: int, extra_seed: int) -> dict:
    """主评测：返回报告 dict（不落盘）。"""
    t0 = time.time()
    baseline_v3 = load_lineup(player_path)
    with open(opponent_path, encoding="utf-8") as f:
        opp_v4 = json.load(f)
    opponent_v3 = load_lineup(opponent_path)
    with open(placer_out_path, encoding="utf-8") as f:
        placer = json.load(f)

    cand_v3 = [_load_lineup_dict(c["lineup"]) for c in placer.get("candidates", [])]
    extras = pick_extra_opponents(n_extra, opponent_path, extra_seed)
    opponents = [("fixed", opponent_v3)] + extras

    tasks = []
    for oi in range(len(opponents)):
        for si, seed in enumerate(seeds):
            tasks.append(("__baseline__", oi, seed))
            for ci in range(len(cand_v3)):
                tasks.append((str(ci), oi, seed))

    from multiprocessing import Pool
    results = {"__baseline__": {}, **{str(i): {} for i in range(len(cand_v3))}}
    n_err = 0
    with Pool(processes=min(os.cpu_count() or 1, 8), initializer=_pool_init,
              initargs=(baseline_v3, cand_v3, opponents)) as pool_mp:
        for res in pool_mp.imap_unordered(_run_one, tasks, chunksize=4):
            if "error" in res:
                n_err += 1
                print("⚠ 对局失败：cfg=%s opp=%d %s" % (res["cfg"], res["opp"], res["error"]),
                      file=sys.stderr)
                continue
            results[res["cfg"]].setdefault(res["opp"], []).append(res)

    def summarize(cfg: str) -> dict:
        per_opp = {}
        for oi, rs in sorted(results[cfg].items()):
            wins = sum(r["win"] for r in rs)
            fielded = sorted({r["fielded"] for r in rs})
            per_opp[opponents[oi][0] if oi == 0 else
                    "extra:%s" % opponents[oi][0]] = {
                        "wins": wins, "seeds": len(rs),
                        "winrate": round(wins / max(len(rs), 1), 4),
                        "engine_fielded_items": fielded,
                    }
        fixed = per_opp.get("fixed", {"winrate": None})
        extras_r = {k: v for k, v in per_opp.items() if k != "fixed"}
        extra_wr = [v["winrate"] for v in extras_r.values()]
        return {"per_opponent": per_opp,
                "fixed_winrate": fixed["winrate"],
                "extra_mean_winrate": (round(sum(extra_wr) / len(extra_wr), 4)
                                        if extra_wr else None)}

    base_sum = summarize("__baseline__")
    cand_sums = []
    for i, c in enumerate(placer.get("candidates", [])):
        s = summarize(str(i))
        s["rank"] = c.get("rank")
        s["proxy_winrate"] = c.get("proxy_winrate")
        s["claimed_engine_items"] = c.get("engine_items")
        cand_sums.append(s)

    # 代理 vs 引擎校准（固定对手、候选数 ≥3 时）
    rho = None
    if len(cand_sums) >= 3:
        xs = [c["proxy_winrate"] for c in cand_sums if c["fixed_winrate"] is not None]
        ys = [c["fixed_winrate"] for c in cand_sums if c["fixed_winrate"] is not None]
        if len(xs) == len(cand_sums):
            rho = round(spearman(xs, ys), 4)

    best = max(cand_sums, key=lambda c: (c["fixed_winrate"] is not None,
                                         c["fixed_winrate"] or 0.0), default=None)
    report = {
        "meta": {
            "lineup": os.path.abspath(player_path),
            "opponent": os.path.abspath(opponent_path),
            "placer_out": os.path.abspath(placer_out_path),
            "seeds": [int(s) for s in seeds],
            "n_extra_opponents": len(extras),
            "extra_opponents": [name for name, _ in extras],
            "elapsed_s": round(time.time() - t0, 1),
            "engine_errors": n_err,
            "selection_bias_note":
                "候选由 placer 在本固定对手上 best-of-search 选出（按代理分）；"
                "fixed 对手上的胜率是「选内」数字，天然偏乐观。extra:* 对手未参与"
                "选优，其胜率是「选外」泛化数字——两者都报告，勿只看选内。",
            "engine_visibility_note":
                "引擎只装配根物品（simulator/gd_core_engine.py:_build_side）；"
                "engine_fielded_items 即引擎侧实际参战物品数，与候选 JSON 件数的差"
                "= 留袋物品（如实计入 placer_out 的 bag_items，非静默丢失）。",
        },
        "baseline": base_sum,
        "candidates": cand_sums,
        "proxy_vs_engine_spearman_fixed": rho,
        "verdict": {
            "best_candidate_fixed_winrate": best["fixed_winrate"] if best else None,
            "baseline_fixed_winrate": base_sum["fixed_winrate"],
            "improvement_fixed": (round(best["fixed_winrate"] - base_sum["fixed_winrate"], 4)
                                  if best and best["fixed_winrate"] is not None
                                  and base_sum["fixed_winrate"] is not None else None),
        },
    }
    return report


def _load_lineup_dict(v4: dict):
    """v4 阵容 dict → 内部 v3（复用 simulator/lineup 的规范化，经临时文件）。"""
    import tempfile
    with tempfile.NamedTemporaryFile("w", suffix=".json", delete=False,
                                     encoding="utf-8") as f:
        json.dump(v4, f, ensure_ascii=False)
        path = f.name
    try:
        return load_lineup(path)
    finally:
        os.unlink(path)


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description="重摆候选引擎级评测报告")
    ap.add_argument("--lineup", required=True, help="原玩家阵容 JSON（基线）")
    ap.add_argument("--opponent", required=True, help="固定对手阵容 JSON")
    ap.add_argument("--placer-out", default=DEFAULT_PLACER_OUT,
                    help="placer 输出 JSON（默认 ai/placer_out.json）")
    ap.add_argument("--seeds", type=int, default=20, help="每配置 seed 数（默认 20）")
    ap.add_argument("--seed", type=int, default=101, help="首个 seed（依次 +1）")
    ap.add_argument("--extra-opponents", type=int, default=3,
                    help="泛化对照用的额外对手数（从真值实录池抽，0=关）")
    ap.add_argument("--extra-seed", type=int, default=7, help="额外对手抽样种子")
    ap.add_argument("--out", default=DEFAULT_OUT, help="报告输出路径（默认 ai/eval_report.json）")
    args = ap.parse_args(argv)

    seeds = [args.seed + i for i in range(max(args.seeds, 1))]
    report = run_eval(args.lineup, args.opponent, args.placer_out, seeds,
                      args.extra_opponents, args.extra_seed)
    os.makedirs(os.path.dirname(os.path.abspath(args.out)), exist_ok=True)
    with open(args.out, "w", encoding="utf-8") as f:
        json.dump(report, f, ensure_ascii=False, indent=2)
        f.write("\n")

    b = report["baseline"]["fixed_winrate"]
    print("基线（原阵容）  引擎胜率 %s" % _fmt(b))
    for c in report["candidates"]:
        print("候选 #%-2d  代理 %.4f  引擎 %s  （选外均值 %s）  引擎装配 %s"
              % (c["rank"], c["proxy_winrate"], _fmt(c["fixed_winrate"]),
                 _fmt(c["extra_mean_winrate"]),
                 c["per_opponent"]["fixed"]["engine_fielded_items"]))
    v = report["verdict"]
    print("最优候选 %s vs 基线 %s（差 %s）；代理-引擎 Spearman(固定对手)=%s"
          % (_fmt(v["best_candidate_fixed_winrate"]), _fmt(v["baseline_fixed_winrate"]),
             _fmt(v["improvement_fixed"]), report["proxy_vs_engine_spearman_fixed"]))
    print("报告已写入 %s" % args.out)
    return 0


def _fmt(x):
    return "n/a" if x is None else ("%.4f" % x if isinstance(x, float) else str(x))


if __name__ == "__main__":
    raise SystemExit(main())
