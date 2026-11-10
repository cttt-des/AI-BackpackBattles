# -*- coding: utf-8 -*-
"""bench_sim.py — 模拟器性能基准（docs/性能优化执行路径.md S0-H1）

收编 tools/_perf_bench.py 与 tools/_perf_pool.py。所有性能数字一律出自本工具，
口径固化见执行路径 §10.4（p50+p95+ms/千 tick 三件套、N≥20 单场 / N≥128 并行、
同机同日、每份数字带命令与 JSON 路径）。

用法:
    python tools/bench_sim.py --n 20 --rounds 5 --json output/perf/out.json
    python tools/bench_sim.py --n 128 --workers 4 --json output/perf/pool4.json
    python tools/bench_sim.py --ttfb                 # 冷启动 TTFB（子进程实测）
    python tools/bench_sim.py --n 20 --pin 0,1,2,3   # 绑核（子进程继承亲和掩码）
    python tools/bench_sim.py --n 3 --profile-out output/perf/profile.json
                                     # sys.monitoring 逐函数调用计数剖面（A1）

口径:
  · 单场计时窗口 = GDCoreEngine 构造 + run()（事件对象化计入，产品真实路径）；
    事件字节/胜负等后处理在计时窗外。
  · ms/千 tick = p50 ÷ 平均 tick ×1000（A5 归一化，跨阵容可比）。
  · 复现性 = 各轮 p50 的 (max-min)/median，≤3% 视为过 A3/A5（G0 门）。
  · 不变性探针（语义不变）：同 seed 跨轮的 (winner, ticks, n_events, events_bytes)
    必须逐字段全等，任何一项漂移即判 FAIL——性能数字随之作废。

不作假:  本工具不改内核、不缓存跨场对象（_DESCR_CACHE 等 kernel 级缓存按产品
         路径自然复用），不跳过事件物化（那是 S3-C12 的选项，不是基准的）。
"""
from __future__ import annotations

import argparse
import json
import os
import statistics
import subprocess
import sys
import time
from concurrent.futures import ProcessPoolExecutor

_TOOLS = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(_TOOLS)
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)

DEFAULT_P = os.path.join(ROOT, "lineups", "truth_20261001_220653_R19_player.json")
DEFAULT_O = os.path.join(ROOT, "lineups", "truth_20261001_220653_R19_opponent.json")

_V1_CPROFILE_TOP = [  # v1 cProfile 名单（profiled cum 序），供 A1 对照
    "physicsTick(CoreCombat)", "physicsTick(CoreItem)", "trigger",
    "getSpeed", "tickTimersPass", "emitAndLog", "emitEvent",
    "doCooldownEffect", "attack", "activate", "call_funcv",
    "_build_side", "_iter", "_tickTimers", "dealDamage", "randf_range",
]


def _pctl(sorted_xs, q):
    """线性插值百分位；sorted_xs 非空。"""
    if len(sorted_xs) == 1:
        return sorted_xs[0]
    pos = (len(sorted_xs) - 1) * q / 100.0
    lo = int(pos)
    hi = min(lo + 1, len(sorted_xs) - 1)
    frac = pos - lo
    return sorted_xs[lo] * (1 - frac) + sorted_xs[hi] * frac


def _pin(cores: str):
    """绑核（Windows）：SetProcessAffinityMask；spawn 子进程默认继承。"""
    mask = 0
    for c in cores.split(","):
        mask |= 1 << int(c)
    import ctypes
    h = ctypes.windll.kernel32.GetCurrentProcess()
    if not ctypes.windll.kernel32.SetProcessAffinityMask(h, mask):
        print("WARNING: 绑核失败，继续不绑核", file=sys.stderr)


# ── 单场（计时窗口内） ──────────────────────────────────────────────

def _fight(pl_str, op_str, seed, max_time=180.0, cpu_time=False):
    """返回 (ms, ticks, winner, timed_out, n_events)。JSON 解析在窗口外。

    cpu_time=True 时用 process_time 计时（排除被系统抢占/降频等待的墙钟时间），
    用于在降频机上拿到与频率无关的口径。
    """
    import json as _j
    from simulator.gd_core_engine import GDCoreEngine
    _clock = time.process_time if cpu_time else time.perf_counter
    t0 = _clock()
    eng = GDCoreEngine(_j.loads(pl_str), _j.loads(op_str), {}, {},
                       seed=seed, max_time=max_time)
    eng.run()
    ms = (_clock() - t0) * 1000.0
    winner = "player" if eng.player_wins() else "opponent"
    return (ms, int(eng._ticks), winner, bool(eng.timed_out),
            len(eng.log.events))


# ── 计时窗外取证（不变性探针用） ────────────────────────────────────

def _evidence(pl_str, op_str, seed, max_time=180.0):
    """同 _fight，另带 events_bytes（计时窗外补测，仅用于语义不变比对）。"""
    import json as _j
    from simulator.gd_core_engine import GDCoreEngine
    eng = GDCoreEngine(_j.loads(pl_str), _j.loads(op_str), {}, {},
                       seed=seed, max_time=max_time)
    eng.run()
    ms = None
    return {"ms": None, "ticks": int(eng._ticks),
            "winner": "player" if eng.player_wins() else "opponent",
            "timed_out": bool(eng.timed_out),
            "n_events": len(eng.log.events),
            "events_bytes": len(json.dumps(eng.log.to_dict(),
                                           ensure_ascii=False).encode("utf-8"))}


def _summarize(rows):
    """rows: [(ms, ticks, winner, timed_out, n_events)] → 指标三件套。"""
    ms = sorted(r[0] for r in rows)
    ticks = [r[1] for r in rows]
    p50 = _pctl(ms, 50)
    out = {
        "n": len(rows),
        "p50_ms": round(p50, 1),
        "p95_ms": round(_pctl(ms, 95), 1),
        "min_ms": round(ms[0], 1),
        "max_ms": round(ms[-1], 1),
        "mean_ticks": round(statistics.fmean(ticks), 1) if ticks else 0,
        "ms_per_k_tick": round(p50 / (statistics.fmean(ticks) / 1000.0), 1)
        if ticks and statistics.fmean(ticks) > 0 else None,
        "fights_per_s_core": round(1000.0 / p50, 2) if p50 > 0 else None,
        "wins_player": sum(1 for r in rows if r[2] == "player"),
        "timed_out_n": sum(1 for r in rows if r[3]),
    }
    return out


# ── 进程池（--workers） ─────────────────────────────────────────────

def _pool_worker(args):
    seed, pl_str, op_str = args
    return _fight(pl_str, op_str, seed)


# ── TTFB（冷启动到首场结果） ────────────────────────────────────────

def _ttfb(pl_path, op_path):
    code = (
        "import sys, time, json; sys.path.insert(0, %r);"
        "t0=time.perf_counter();"
        "from simulator.gd_core_engine import GDCoreEngine;"
        "pl=json.load(open(%r,encoding='utf-8'));"
        "op=json.load(open(%r,encoding='utf-8'));"
        "e=GDCoreEngine(pl,op,{},{},seed=42,max_time=180.0);e.run();"
        "print(int((time.perf_counter()-t0)*1000), e.player_wins())"
    ) % (ROOT, pl_path, op_path)
    t0 = time.perf_counter()
    r = subprocess.run([sys.executable, "-I", "-c", code],
                       capture_output=True, text=True, cwd=ROOT)
    wall = (time.perf_counter() - t0) * 1000.0
    inproc_ms = None
    if r.returncode == 0 and r.stdout.strip():
        head = r.stdout.strip().splitlines()[-1].split()
        inproc_ms = float(head[0])
    return {"ttfb_wall_ms": round(wall, 1),
            "first_fight_ms": inproc_ms,
            "exit": r.returncode}


# ── A1: sys.monitoring 逐函数调用计数 ──────────────────────────────

def _profile_run(n, pl_str, op_str, base_seed):
    import sys as _s
    mon = getattr(_s, "monitoring", None)
    if mon is None:
        raise RuntimeError("sys.monitoring 不可用（需 Python ≥3.12）")
    TOOL = mon.use_tool_id  # noqa: F841 占位防误删
    tid = 5  # 自留区间 0-4 避开解释器保留；冲突则回落
    counts = {}

    def cb(code, instruction_offset):
        # register_callback(tool_id, event, func) 的回调为平参签名
        key = (getattr(code, "co_qualname", code.co_name),
               os.path.basename(code.co_filename))
        counts[key] = counts.get(key, 0) + 1

    mon.use_tool_id(tid, "bench_sim_a1")
    mon.register_callback(tid, mon.events.PY_START, cb)
    mon.set_events(tid, mon.events.PY_START)
    fights = []
    try:
        for i in range(n):
            t0 = time.perf_counter()
            ms, ticks, winner, to, nev = _fight(pl_str, op_str, base_seed + i)
            fights.append({"seed": base_seed + i, "ms": round(ms, 1),
                           "ticks": ticks, "winner": winner})
    finally:
        mon.set_events(tid, 0)
        mon.free_tool_id(tid)
    return fights, counts


# ── 主流程 ──────────────────────────────────────────────────────────

def main():
    ap = argparse.ArgumentParser(description="模拟器性能基准（S0-H1）")
    ap.add_argument("--n", type=int, default=20, help="每轮场数（单场≥20）")
    ap.add_argument("--rounds", type=int, default=5,
                    help="轮数（复现性=各轮 p50 离散度）")
    ap.add_argument("--seed", type=int, default=20260923, help="起始种子")
    ap.add_argument("--workers", type=int, default=1,
                    help="进程池 worker 数（>1 时 rounds 固定 1）")
    ap.add_argument("--lineup-p", default=DEFAULT_P)
    ap.add_argument("--lineup-o", default=DEFAULT_O)
    ap.add_argument("--json", default=None, help="结果 JSON 落盘路径")
    ap.add_argument("--ttfb", action="store_true", help="附测冷启动 TTFB")
    ap.add_argument("--pin", default=None, help="绑核，如 0,1,2,3")
    ap.add_argument("--profile-out", default=None,
                    help="sys.monitoring 调用计数剖面路径（单进程小 n）")
    ap.add_argument("--label", default="unspecified",
                    help="配置标签（进 JSON，供 A/B 对照）")
    ap.add_argument("--cpu-time", action="store_true",
                    help="用 process_time 计时（排除降频/抢占的墙钟等待）")
    ap.add_argument("--warmup", type=int, default=0,
                    help="先跑 N 场热身并丢弃（抹平 pyc/pyd 冷加载）")
    args = ap.parse_args()

    if args.pin:
        _pin(args.pin)

    for p in (args.lineup_p, args.lineup_o):
        if not os.path.exists(p):
            print(f"阵容不存在: {p}", file=sys.stderr)
            return 2
    with open(args.lineup_p, encoding="utf-8") as f:
        pl_str = f.read()
    with open(args.lineup_o, encoding="utf-8") as f:
        op_str = f.read()

    out = {"stage": args.label,
           "machine": f"{os.cpu_count()}L, Python {sys.version.split()[0]}",
           "cmd": " ".join(sys.argv),
           "lineups": [os.path.basename(args.lineup_p),
                       os.path.basename(args.lineup_o)],
           "workers": args.workers, "n": args.n}

    # ── A1 剖面模式 ──
    if args.profile_out:
        fights, counts = _profile_run(args.n, pl_str, op_str, args.seed)
        top = sorted(counts.items(), key=lambda kv: -kv[1])[:30]
        v1_names = {n.split("(")[0] for n in _V1_CPROFILE_TOP}
        out["fights"] = fights
        out["top_calls"] = [
            {"function": k[0], "file": k[1], "calls": v,
             "in_v1_cprofile_top": k[0].split(".")[-1] in v1_names}
            for k, v in top]
        out["note"] = ("sys.monitoring PY_START 调用计数（非耗时）；"
                       "与 v1 cProfile 耗时名单互为印证")
        _emit(out, args.profile_out)
        _print_summary(out)
        return 0

    # ── 常规基准 ──
    if args.n < 20 and args.workers == 1:
        print("WARN: 单场基准 N<20，按 §10.4 只报趋势不报倍数", file=sys.stderr)
    if args.workers > 1:
        if args.n < 128:
            print("WARN: 并行基准 N<128，按 §10.4 只报趋势", file=sys.stderr)
        args.rounds = 1
        jobs = [(args.seed + i, pl_str, op_str) for i in range(args.n)]
        t0 = time.perf_counter()
        with ProcessPoolExecutor(max_workers=args.workers) as ex:
            rows = list(ex.map(_pool_worker, jobs, chunksize=4))
        wall = (time.perf_counter() - t0) * 1000.0
        s = _summarize(rows)
        s["wall_ms"] = round(wall, 1)
        s["throughput_fights_per_s"] = round(args.n / (wall / 1000.0), 2)
        out.update(s)
        out["round_p50_ms"] = None       # 并行模式不测复现性（S1 验收另测）
        out["repro_spread_pct"] = None
    else:
        rounds = []
        rows_all = []
        # 热身：同 seed 跑若干场丢弃，抹平 pyc/pyd 冷加载与首次属性缓存
        if args.warmup > 0:
            for i in range(args.warmup):
                _fight(pl_str, op_str, args.seed + 100000 + i,
                       cpu_time=args.cpu_time)
        for r in range(args.rounds):
            t0 = time.perf_counter()
            rows = [_fight(pl_str, op_str, args.seed + i,
                           cpu_time=args.cpu_time)
                    for i in range(args.n)]
            rounds.append(round(time.perf_counter() - t0, 3))
            rows_all.extend(rows)
        out.update(_summarize(rows_all))
        rp50 = _summarize(rows_all)  # 全量口径
        per_round = [_summarize(rows_all[r * args.n:(r + 1) * args.n])
                     for r in range(args.rounds)]
        p50s = [p["p50_ms"] for p in per_round]
        out["round_wall_s"] = rounds
        out["round_p50_ms"] = p50s
        med = _pctl(sorted(p50s), 50)
        out["repro_spread_pct"] = round((max(p50s) - min(p50s)) / med * 100.0,
                                        2) if med > 0 and len(p50s) > 1 else 0.0
        out["repro_pass_3pct"] = bool(out["repro_spread_pct"] <= 3.0)
        out["clock"] = "process_time" if args.cpu_time else "perf_counter"
        out["warmup"] = args.warmup

        # ── 语义不变性探针：同 seed 跨轮比对（A 轮 vs 最后一轮） ──
        subset = args.n if args.n <= 5 else 3
        ev_a = [_evidence(pl_str, op_str, args.seed + i) for i in range(subset)]
        ev_b = [_evidence(pl_str, op_str, args.seed + i) for i in range(subset)]
        delta = [{"seed": args.seed + i,
                  "field": k, "a": ea[k], "b": eb[k]}
                 for i, (ea, eb) in enumerate(zip(ev_a, ev_b))
                 for k in ("ticks", "winner", "timed_out", "n_events",
                           "events_bytes") if ea[k] != eb[k]]
        out["invariance_delta"] = delta
        out["invariance_pass"] = not delta
        out["events_bytes_first_seed"] = ev_a[0]["events_bytes"]

    if args.ttfb:
        out["ttfb"] = _ttfb(args.lineup_p, args.lineup_o)

    path = args.json
    if path:
        os.makedirs(os.path.dirname(os.path.abspath(path)), exist_ok=True)
        _emit(out, path)
    _print_summary(out, path)
    return 0 if (out.get("invariance_pass", True)
                 and out.get("repro_pass_3pct", True)) else 1


def _emit(out, path):
    with open(path, "w", encoding="utf-8") as f:
        json.dump(out, f, ensure_ascii=False, indent=2)
        f.write("\n")


def _print_summary(out, path=None):
    if "top_calls" in out:                       # A1 剖面模式
        top = out["top_calls"][:10]
        hit = sum(1 for e in top if e["in_v1_cprofile_top"])
        print(f"[{out.get('stage','?')}] A1 剖面 {out.get('n')} 场 "
              f"top10 命中 v1 名单 {hit}/10；前 5："
              + ", ".join(f"{e['function']}×{e['calls']}" for e in top[:5]))
        if path:
            print(f"  → {path}")
        return
    line = (f"[{out.get('stage','?')}] workers={out.get('workers',1)} "
            f"n={out.get('n')} p50={out.get('p50_ms')}ms "
            f"p95={out.get('p95_ms')}ms ms/千tick={out.get('ms_per_k_tick')} "
            f"场·核/s={out.get('fights_per_s_core')}")
    if out.get("throughput_fights_per_s"):
        line += f" 吞吐={out['throughput_fights_per_s']}场/s"
    if out.get("repro_spread_pct") is not None:
        line += (f" 复现散布={out['repro_spread_pct']}%"
                 f"({'+PASS' if out.get('repro_pass_3pct') else 'FAIL'})")
    if out.get("invariance_pass") is False:
        line += f" 不变性=FAIL({len(out['invariance_delta'])}项漂移)"
    elif "invariance_pass" in out:
        line += " 不变性=PASS"
    if out.get("ttfb"):
        line += f" TTFB={out['ttfb']['ttfb_wall_ms']}ms"
    print(line)
    if path:
        print(f"  → {path}")


if __name__ == "__main__":
    raise SystemExit(main())