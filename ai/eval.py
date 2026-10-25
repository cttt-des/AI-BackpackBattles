# -*- coding: utf-8 -*-
"""eval.py — 端到端评测：真值实录阵容上 原摆盘 vs placer 重摆 的同 seed 引擎胜率对比

流程（对每组实录）
==================
1. **装配闸**：对 原阵容 vs 实录 Opponent 构造一次 GDCoreEngine——抛 _MissingItem
   的组（实录混有 GoldCounter/Icon 等不可装配件）整组跳过；同时顺手实测原阵容
   的引擎装配数（eng.player_items），供后面守恒对照用。
2. **重摆**：调 ai/placer.py（子进程，--topk 1）重摆 Player 阵容，取其 top-1 候选。
3. **守恒校验（完全独立，不复用 placer 的解析/成员推断）**：
   a. *物品多重集*：用本文件自己的平铺函数（只认原始 JSON 形状：v4 items 平铺
      + 显式 `in`；或 v3 backpack.items 嵌套 contents），从 **原始阵容 JSON** 与
      **候选 lineup** 各取全部扁平物品，核对 id 多重集与宝石全局多重集逐位一致；
   b. *引擎装配数*：用 GDCoreEngine 分别实测 原阵容 与 候选 的装配数（构造期
      eng.player_items 的长度，另比对装配 id 多重集），两者必须相等，不等记
      verification=mismatch 并跳过该组——引擎对输入阵容的实际装配结果是唯一口径。
   任一不一致 → 该组记 verification=mismatch，跳过（绝不拿漂移候选评测）。
4. **同 seed 配对对比**：用**完全相同的 seed 列表**（base, base+1, … 共 --seeds
   个）**逐 seed 交错**模拟 原阵容 vs 重摆阵容 对该实录 Opponent（对每个 seed
   先跑 orig 再跑 ai）。每局模拟前调 ai/kernel_reset.reset_kernel_state() 把
   gd_core_py 的进程级全局态（裸 arr.shuffle() 的全局 Math RNG 与实例 id
   台账）清回全新进程初值——不重置时同 (输入,seed) 的结局随进程历史漂移
   （2026-10-03 实测：同 seed 连跑 6 次 → [1,1,0,1,1,1]，先跑别的组再跑又
   是另一组逐 seed 结果），『同 seed 配对』无从谈起；重置后每局结果是
   (阵容, seed) 的确定函数（ai/tests/test_kernel_reset.py 回归验证），
   配对减方差才成立。

输出
====
* 每场 stdout 打印 `EVAL <name> <origWinRate> <aiWinRate> <delta>`（3 位小数，
  delta = ai − orig）；跳过的组往 stderr 打 `SKIP <name> [<阶段>/<verification>]
  <原因>`（stdout 只留 EVAL/SUMMARY 行，便于机器抓取）；
* 全部结束后打印 `SUMMARY <平均delta> <提升场数>/<总场数>`（总场数 = 实际评测
  的组数；0 组评测时平均 delta 如实打 n/a）；
* 逐场明细（含每 seed 胜负、两侧装配数、verification）与汇总写入
  ai/eval_report.json（中断时也写入已评部分，interrupted=true）。报告另带
  **不确定度**：两侧胜率的 Wilson 95% CI、逐 seed 配对 delta 的正态近似
  95% CI（--seeds 默认 10 偏小，CI 仅指示性，勿当显著性强断言）。

用法
====
    python ai/eval.py [--truth-dir dist/output/combat_logs] [--weights ai/weights.pt]
                      [--seeds 10] [--limit 20] [--seed 101] [--out ai/eval_report.json]

自测：python ai/eval.py --seeds 2 --limit 2
"""
from __future__ import annotations

import argparse
import contextlib
import glob
import io
import json
import math
import os
import shutil
import statistics
import subprocess
import sys
import tempfile
import time
import traceback
from collections import Counter
from typing import Any, Dict, List, Optional, Tuple

_REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if _REPO not in sys.path:
    sys.path.insert(0, _REPO)

from ai.kernel_reset import reset_kernel_state                    # noqa: E402
from simulator.gd_core_engine import GDCoreEngine, _MissingItem   # noqa: E402
from simulator.lineup import load_lineup, LineupError             # noqa: E402

DEFAULT_TRUTH_DIR = os.path.join(_REPO, "dist", "output", "combat_logs")
DEFAULT_WEIGHTS = os.path.join(_REPO, "ai", "weights.pt")
DEFAULT_OUT = os.path.join(_REPO, "ai", "eval_report.json")
PLACER_SCRIPT = os.path.join(_REPO, "ai", "placer.py")
PLACER_TIMEOUT_S = 600            # 单组重摆上限（实测 500 迭代 ~142s/组，余量充足）


class _Skip(Exception):
    """单组跳过信号（stage/verification/reason 进报告，组不计入评测）。"""

    def __init__(self, stage: str, verification: str, reason: str):
        super().__init__(reason)
        self.stage = stage
        self.verification = verification
        self.reason = reason


# ─────────────────────── 独立平铺（守恒校验专用，不经 placer） ───────────────────────

def flat_items(lineup: dict) -> List[Tuple[str, Tuple[str, ...]]]:
    """从**原始阵容 JSON**（未经任何 placer 解析/成员推断）取全部扁平物品。

    只认 JSON 自身形状：
    * v4 平铺：`items` 数组（显式 `in` 指向承载袋下标）——每一条都是一件扁平
      物品，`in` 与否不影响计入（谁真正参战交给引擎装配探针去判）；
    * v3/内部形状：`backpack.items` + 嵌套 `contents` 递归。
    返回 [(id, 宝石元组), ...]（保持平铺序）；id 缺失的条目如实计入 "<no-id>"。
    """
    out: List[Tuple[str, Tuple[str, ...]]] = []

    def gem_ids(gems) -> Tuple[str, ...]:
        res = []
        for g in gems or []:
            if isinstance(g, dict):
                g = g.get("id") or g.get("key")
            if isinstance(g, str) and g:
                res.append(g)
        return tuple(res)

    def walk(entries):
        for e in entries or []:
            if not isinstance(e, dict):
                continue
            out.append((str(e.get("id") or "<no-id>"), gem_ids(e.get("gems"))))
            walk(e.get("contents"))

    bp = lineup.get("backpack")
    if isinstance(bp, dict) and isinstance(bp.get("items"), list):
        walk(bp["items"])
    else:
        walk(lineup.get("items"))
    return out


def multiset_diff(exp: Counter, got: Counter, cap: int = 4) -> str:
    """多重集差异的可读描述（缺/多各取前 cap 项）。"""
    miss, extra = exp - got, got - exp
    fmt = lambda c: dict(list(c.items())[:cap])                    # noqa: E731
    return "缺 %s 多 %s" % (fmt(miss), fmt(extra))


def conservation_mismatch(orig_lineup: dict, cand_lineup: dict) -> Optional[str]:
    """独立守恒校验①：候选物品多重集（id + 宝石全局多重集）必须与原始阵容
    JSON 的全部扁平物品逐位一致。一致返回 None，不一致返回原因。"""
    orig = flat_items(orig_lineup)
    cand = flat_items(cand_lineup)
    if not orig:
        return "原阵容 JSON 没有物品"
    if not cand:
        return "候选 lineup 没有物品"
    orig_ids = Counter(i for i, _ in orig)
    cand_ids = Counter(i for i, _ in cand)
    if orig_ids != cand_ids:
        return ("物品 id 多重集不一致（原 %d 件 vs 候选 %d 件）：%s"
                % (sum(orig_ids.values()), sum(cand_ids.values()),
                   multiset_diff(orig_ids, cand_ids)))
    orig_gems = Counter(g for _, gs in orig for g in gs)
    cand_gems = Counter(g for _, gs in cand for g in gs)
    if orig_gems != cand_gems:
        return "宝石全局多重集不一致：%s" % multiset_diff(orig_gems, cand_gems)
    return None


# ─────────────────────────────── 引擎 ───────────────────────────────

def engine_assembly(player_v3: dict, opp_v3: dict, seed: int) -> Tuple[int, Counter]:
    """GDCoreEngine 构造期实测装配：返回 (装配物品数, 装配物品 id 多重集)。
    eng.player_items 来自 _build_side——引擎视角的参战物品（宝石不计件）。
    构造前重置内核全局态（构造本身也会写全局态，见 ai/kernel_reset.py）；
    内核/引擎的零星 print（如 setGem 超容量的 "ohnonononononno"，gd_core_py/
    gd_core/CoreItem.py:2594）重定向走，不污染 stdout 的 EVAL/SUMMARY 行。"""
    buf = io.StringIO()
    with contextlib.redirect_stdout(buf):
        reset_kernel_state()
        eng = GDCoreEngine(player_v3, opp_v3, seed=seed)
        n = len(eng.player_items)
        ids = Counter(it.key for it in eng.player_items)
    return n, ids


def run_match(player_v3: dict, opp_v3: dict, seed: int) -> bool:
    """跑一局引擎，返回玩家是否获胜（与 simulator/simulate.py 同口径）。

    局前重置 gd_core_py 进程级全局态（全局 Math RNG / 实例 id 台账）：
    不重置时结局随进程历史漂移，同 (输入, seed) 不复现——这是修掉的
    『同 seed 配对』前提缺陷，见 ai/kernel_reset.py 文件头。引擎零星
    print 重定向，不污染 stdout 的 EVAL/SUMMARY 行。
    """
    buf = io.StringIO()
    with contextlib.redirect_stdout(buf):
        reset_kernel_state()
        eng = GDCoreEngine(player_v3, opp_v3, seed=seed)
        eng.run()
        win = bool(eng.player_wins())
    return win


# ─────────────────────────────── 不确定度 ───────────────────────────────

_Z95 = statistics.NormalDist().inv_cdf(0.975)     # 1.959963…

def wilson_ci(k: int, n: int) -> List[float]:
    """胜率 k/n 的 Wilson 95% 置信区间（n 小时远比朴素 ±1.96√(p(1-p)/n) 稳）。"""
    if n <= 0:
        return [0.0, 1.0]
    p = k / n
    denom = 1 + _Z95 ** 2 / n
    center = (p + _Z95 ** 2 / (2 * n)) / denom
    half = _Z95 / denom * math.sqrt(p * (1 - p) / n + _Z95 ** 2 / (4 * n * n))
    return [round(max(0.0, center - half), 6), round(min(1.0, center + half), 6)]


def paired_delta_ci(orig_res: List[int], ai_res: List[int]) -> List[float]:
    """逐 seed 配对差 ai−orig 的均值 ± 正态近似 95% CI。

    n=10 偏小、差值域 {-1,0,1}，正态近似偏粗糙——**仅指示性**，判断
    『CI 是否含 0』时须连同逐 seed 明细一起看。
    """
    diffs = [a - b for a, b in zip(ai_res, orig_res)]
    n = len(diffs)
    mean = sum(diffs) / n
    if n < 2:
        return [round(mean, 6), round(mean, 6)]
    sd = statistics.stdev(diffs)                   # 样本标准差 (n-1)
    half = _Z95 * sd / math.sqrt(n)
    return [round(mean - half, 6), round(mean + half, 6)]


# ─────────────────────────────── placer 子进程 ───────────────────────────────

def run_placer(player_path: str, opp_path: str, weights: str,
               out_path: str) -> Tuple[Optional[dict], Optional[str]]:
    """调 ai/placer.py（子进程，--topk 1），取 top-1 候选。失败返回 (None, 原因)。"""
    cmd = [sys.executable, PLACER_SCRIPT,
           "--lineup", player_path, "--opponent", opp_path,
           "--topk", "1", "--weights", weights, "--out", out_path]
    try:
        proc = subprocess.run(cmd, cwd=_REPO, capture_output=True, text=True,
                              encoding="utf-8", timeout=PLACER_TIMEOUT_S)
    except subprocess.TimeoutExpired:
        return None, "placer 超时（>%ds）" % PLACER_TIMEOUT_S
    if proc.returncode != 0:
        tail = (proc.stderr or "").strip().splitlines()[-3:]
        return None, "placer 退出码 %d: %s" % (
            proc.returncode, " | ".join(tail) or "(无 stderr)")
    data = None
    err = None
    for src in ("stdout", "file"):          # stdout 为主，--out 文件兜底
        try:
            if src == "stdout":
                data = json.loads(proc.stdout)
            else:
                with open(out_path, encoding="utf-8") as f:
                    data = json.load(f)
            break
        except Exception as exc:                             # noqa: BLE001
            err = "%s 解析失败: %s" % (src, exc)
    if not isinstance(data, dict):
        return None, err or "placer 输出不是 JSON 对象"
    cands = data.get("candidates") or []
    if not cands:
        return None, "placer 无候选"
    return cands[0], None


# ─────────────────────────────── 单组评测 ───────────────────────────────

def eval_group(name: str, player_path: str, opp_path: str, weights: str,
               seed_list: List[int], placer_out: str) -> Dict[str, Any]:
    """评测一组实录：装配闸 → 重摆 → 独立守恒校验 → 同 seed 配对模拟。
    返回逐场明细 dict；不可评测一律 raise _Skip（绝不含糊带过）。"""
    # ── 读原始 JSON（守恒校验的标准口径）+ 引擎内部形状 ──
    try:
        with open(player_path, encoding="utf-8") as f:
            orig_raw = json.load(f)
    except (OSError, json.JSONDecodeError) as exc:
        raise _Skip("load", "io_error", "实录 Player JSON 读取失败: %s" % exc)
    try:
        orig_v3 = load_lineup(player_path)
        opp_v3 = load_lineup(opp_path)
    except LineupError as exc:
        raise _Skip("load", "lineup_invalid", "阵容加载失败: %s" % exc)

    # ── 装配闸：原阵容 vs 实录 Opponent 构造引擎 ──
    #    _MissingItem 组整组跳过；同时实测原阵容装配数（守恒对照的基准）
    try:
        n_orig, ids_orig = engine_assembly(orig_v3, opp_v3, seed_list[0])
    except _MissingItem as exc:
        raise _Skip("assembly_probe", "missing_item",
                    "引擎装配抛 _MissingItem: %s" % exc)
    except LineupError as exc:
        raise _Skip("assembly_probe", "lineup_invalid", "阵容加载失败: %s" % exc)
    except Exception as exc:                                 # noqa: BLE001
        raise _Skip("assembly_probe", "engine_error",
                    "引擎装配异常 %s: %s" % (type(exc).__name__, exc))

    # ── 重摆：placer 子进程，取 top-1 候选 ──
    cand, why = run_placer(player_path, opp_path, weights, placer_out)
    if cand is None:
        raise _Skip("placer", "placer_failed", why)
    cand_lineup = cand.get("lineup")
    if not isinstance(cand_lineup, dict):
        raise _Skip("placer", "placer_failed", "top-1 候选缺 lineup 字段")

    # ── 守恒校验①（独立）：候选物品/宝石多重集 == 原始阵容 JSON 全部扁平物品 ──
    mism = conservation_mismatch(orig_raw, cand_lineup)
    if mism:
        raise _Skip("verification", "mismatch", mism)

    # ── 守恒校验②（引擎实测）：原阵容 vs 候选 的装配数（与 id 多重集）必须一致 ──
    ai_path = placer_out.replace(".json", ".Player.json")
    with open(ai_path, "w", encoding="utf-8") as f:
        json.dump(cand_lineup, f, ensure_ascii=False)
    try:
        ai_v3 = load_lineup(ai_path)
    except LineupError as exc:
        raise _Skip("verification", "mismatch", "重摆阵容加载失败: %s" % exc)
    try:
        n_ai, ids_ai = engine_assembly(ai_v3, opp_v3, seed_list[0])
    except _MissingItem as exc:
        raise _Skip("verification", "mismatch",
                    "候选引擎装配抛 _MissingItem（原阵容可装配）: %s" % exc)
    except Exception as exc:                                 # noqa: BLE001
        raise _Skip("verification", "mismatch",
                    "候选引擎装配异常 %s: %s" % (type(exc).__name__, exc))
    if n_ai != n_orig:
        raise _Skip("verification", "mismatch",
                    "引擎装配数不一致：原阵容 %d 件 vs 候选 %d 件" % (n_orig, n_ai))
    if ids_ai != ids_orig:
        raise _Skip("verification", "mismatch",
                    "引擎装配 id 多重集不一致（装配数同 %d）：%s"
                    % (n_orig, multiset_diff(ids_orig, ids_ai)))

    # ── 同 seed 列表配对对比：原阵容 vs 重摆阵容（同 Opponent）──
    #    逐 seed 交错（每 seed 先 orig 后 ai）；每局前 run_match 内部重置内核
    #    全局态，结局是 (阵容, seed) 的确定函数，配对减方差成立。
    try:
        orig_res: List[int] = []
        ai_res: List[int] = []
        for s in seed_list:
            orig_res.append(int(run_match(orig_v3, opp_v3, s)))
            ai_res.append(int(run_match(ai_v3, opp_v3, s)))
    except _MissingItem as exc:
        raise _Skip("simulation", "missing_item",
                    "模拟期装配抛 _MissingItem（构造期未触发）: %s" % exc)
    except Exception as exc:                                 # noqa: BLE001
        raise _Skip("simulation", "engine_error",
                    "模拟期引擎异常 %s: %s" % (type(exc).__name__, exc))

    orig_wins, ai_wins = sum(orig_res), sum(ai_res)
    orig_rate = orig_wins / len(seed_list)
    ai_rate = ai_wins / len(seed_list)
    return {
        "name": name,
        "player": os.path.abspath(player_path),
        "opponent": os.path.abspath(opp_path),
        "seeds": list(seed_list),
        "n_items": sum(Counter(i for i, _ in flat_items(orig_raw)).values()),
        "n_items_ai": sum(Counter(i for i, _ in flat_items(cand_lineup)).values()),
        "engine_items_orig": n_orig,
        "engine_items_ai": n_ai,
        "orig_wins": orig_wins,
        "ai_wins": ai_wins,
        "orig_win_rate": round(orig_rate, 6),
        "ai_win_rate": round(ai_rate, 6),
        "orig_win_rate_ci95": wilson_ci(orig_wins, len(seed_list)),
        "ai_win_rate_ci95": wilson_ci(ai_wins, len(seed_list)),
        "delta": round(ai_rate - orig_rate, 6),
        "delta_ci95": paired_delta_ci(orig_res, ai_res),
        "orig_results": orig_res,
        "ai_results": ai_res,
        "placer": {"rank": cand.get("rank"),
                   "proxy_winrate": cand.get("proxy_winrate"),
                   "assembled_items": cand.get("assembled_items")},
        "verification": "ok",
    }


# ─────────────────────────────── 主流程 ───────────────────────────────

def parse_args(argv=None):
    ap = argparse.ArgumentParser(
        description="真值实录阵容上 原摆盘 vs 重摆 的同 seed 引擎胜率对比")
    ap.add_argument("--truth-dir", default=DEFAULT_TRUTH_DIR,
                    help="真值实录目录（每组一个子目录，含 *.Player.json/*.Opponent.json）")
    ap.add_argument("--weights", default=DEFAULT_WEIGHTS,
                    help="placer 代理模型权重（默认 ai/weights.pt）")
    ap.add_argument("--seeds", type=int, default=10,
                    help="每场模拟数（原阵容与重摆阵容各跑同一 seed 列表，默认 10）")
    ap.add_argument("--limit", type=int, default=None,
                    help="最多评多少组（默认不限）——按组名序只处理前 N 组，"
                         "被跳过的组也计入名额（运行时长有确定上界）")
    ap.add_argument("--seed", type=int, default=101,
                    help="seed 列表基值：列表 = seed, seed+1, …（默认 101）")
    ap.add_argument("--out", default=DEFAULT_OUT,
                    help="报告 JSON 路径（默认 ai/eval_report.json）")
    return ap.parse_args(argv)


def find_groups(truth_dir: str) -> List[Tuple[str, str, str]]:
    """实录目录 → [(组名, Player.json 路径, Opponent.json 路径)]，按组名排序。"""
    groups = []
    for entry in sorted(os.listdir(truth_dir)):
        sub = os.path.join(truth_dir, entry)
        if not os.path.isdir(sub):
            continue
        players = sorted(glob.glob(os.path.join(sub, "*.Player.json")))
        opps = sorted(glob.glob(os.path.join(sub, "*.Opponent.json")))
        if len(players) == 1 and len(opps) == 1:
            groups.append((entry, players[0], opps[0]))
        else:
            print("SKIP %s 未找到唯一的 .Player.json/.Opponent.json 对"
                  "（player=%d opponent=%d）" % (entry, len(players), len(opps)),
                  file=sys.stderr)
    return groups


def write_report(out_path: str, report: dict):
    with open(out_path, "w", encoding="utf-8") as f:
        json.dump(report, f, ensure_ascii=False, indent=2)
        f.write("\n")


def main(argv=None) -> int:
    args = parse_args(argv)
    if args.seeds < 1:
        print("--seeds 必须 ≥ 1", file=sys.stderr)
        return 2
    if not os.path.isdir(args.truth_dir):
        print("真值实录目录不存在: %s" % args.truth_dir, file=sys.stderr)
        return 2
    if not os.path.isfile(args.weights):
        print("权重文件不存在: %s" % args.weights, file=sys.stderr)
        return 2
    seed_list = [args.seed + i for i in range(args.seeds)]

    groups = find_groups(args.truth_dir)
    if args.limit is not None:
        groups = groups[:max(args.limit, 0)]

    tmpdir = tempfile.mkdtemp(prefix="ai_eval_")
    t_start = time.time()
    evaluated: List[Dict[str, Any]] = []
    skipped: List[Dict[str, Any]] = []
    interrupted = False

    def record_skip(name: str, stage: str, verification: str, reason: str):
        skipped.append({"name": name, "stage": stage,
                        "verification": verification, "reason": reason})
        print("SKIP %s [%s/%s] %s" % (name, stage, verification, reason),
              file=sys.stderr)

    try:
        for name, player_path, opp_path in groups:
            t0 = time.time()
            try:
                rec = eval_group(name, player_path, opp_path, args.weights,
                                 seed_list, os.path.join(tmpdir, "placer_%s.json" % name))
            except _Skip as sk:
                record_skip(name, sk.stage, sk.verification, sk.reason)
                continue
            except Exception as exc:                         # noqa: BLE001
                # 兜底：单组意外故障不拖垮整轮评测（traceback 末行如实入报告）
                tail = traceback.format_exc().strip().splitlines()[-1]
                record_skip(name, "internal", "unexpected_error",
                            "%s: %s | %s" % (type(exc).__name__, exc, tail))
                continue
            rec["elapsed_s"] = round(time.time() - t0, 1)
            print("EVAL %s %.3f %.3f %.3f"
                  % (name, rec["orig_win_rate"], rec["ai_win_rate"], rec["delta"]))
            evaluated.append(rec)
    except KeyboardInterrupt:
        interrupted = True
        print("中断：已评测 %d 组、跳过 %d 组，写入部分报告" % (len(evaluated), len(skipped)),
              file=sys.stderr)
    finally:
        shutil.rmtree(tmpdir, ignore_errors=True)

    # ── 汇总 ──
    n_eval = len(evaluated)
    deltas = [g["delta"] for g in evaluated]
    mean_delta = sum(deltas) / n_eval if n_eval else None   # 0 组评测 → n/a（不伪造 0 信号）
    improved = sum(1 for d in deltas if d > 0)
    # 配对 delta 的 95% CI 不含 0 的组数（n=10/组，CI 偏宽，仅指示性）
    sig = sum(1 for g in evaluated
              if not (g["delta_ci95"][0] <= 0 <= g["delta_ci95"][1]))

    if n_eval:
        print("SUMMARY %.3f %d/%d" % (mean_delta, improved, n_eval))
    else:
        print("SUMMARY n/a 0/0")

    report = {
        "meta": {
            "truth_dir": os.path.abspath(args.truth_dir),
            "weights": os.path.abspath(args.weights),
            "seeds_per_side": args.seeds,
            "seed_list": seed_list,
            "limit": args.limit,
            "interrupted": interrupted,
            "elapsed_s": round(time.time() - t_start, 1),
            "groups_found": len(groups),
            "evaluated": n_eval,
            "skipped": len(skipped),
            "method": "对每组：GDCoreEngine 装配闸（抛 _MissingItem 的组跳过，同时实测"
                      "原阵容装配数）→ ai/placer.py 子进程重摆取 top-1 候选 → 守恒校验"
                      "（完全独立，不复用 placer 解析/成员推断）：①本地平铺函数直接从"
                      "原始阵容 JSON 与候选 lineup 取全部扁平物品，核对 id 多重集与宝石"
                      "全局多重集；②GDCoreEngine 分别实测原阵容与候选的装配数（eng."
                      "player_items），必须相等，不等记 verification=mismatch 并跳过 →"
                      " 用完全相同的 seed 列表**逐 seed 交错**模拟 原阵容 vs 重摆阵容 "
                      "对实录 Opponent；delta = ai − orig，配对同 seed 减方差。"
                      "每局模拟/探针前调 ai/kernel_reset.reset_kernel_state() 把 "
                      "gd_core_py 进程级全局态清回全新进程初值（2026-10-03 修复：不重置"
                      "时同 (输入,seed) 结局随进程历史漂移，同 seed 配对不成立），重置后"
                      "每局结局是 (阵容,seed) 的确定函数（ai/tests/test_kernel_reset.py）",
            "uncertainty": "orig/ai 胜率报 Wilson 95% CI；逐 seed 配对 delta 报正态近似 "
                           "95% CI（seeds_per_side=10 偏小，CI 仅指示性）",
        },
        "groups": evaluated,
        "skipped_groups": skipped,
        "summary": {"mean_delta": None if mean_delta is None else round(mean_delta, 6),
                    "improved": improved, "evaluated": n_eval,
                    "delta_ci95_excludes_zero": sig,
                    "skipped": len(skipped),
                    "skipped_by_stage": dict(Counter(s["stage"] for s in skipped)),
                    "skipped_by_verification":
                        dict(Counter(s["verification"] for s in skipped))},
    }
    write_report(args.out, report)
    print("报告 → %s" % args.out, file=sys.stderr)
    return 130 if interrupted else 0


if __name__ == "__main__":
    raise SystemExit(main())
