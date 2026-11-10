# -*- coding: utf-8 -*-
"""simulate.py — 战斗模拟器 CLI 入口

输入：两个阵容 JSON 文件（玩家 + 对手）
输出：战斗过程日志（JSON + 人类可读 txt）+ 战斗结果（JSON）

用法:
    python -m simulator.simulate lineup_A.json lineup_B.json
    python -m simulator.simulate lineup_A.json lineup_B.json --seed 42 --outdir output/
    python -m simulator.simulate lineup_A.json lineup_B.json --runs 100     # 蒙特卡洛

阵容文件格式见 docs/simulator_architecture.md §2。
"""
from __future__ import annotations

import argparse
import json
import os
import sys
import time
from typing import Dict, List, Optional

from .data import load_items, load_characters
from .lineup import load_lineup, LineupError, resolve_items

# 战斗内核：gd_core（逆向真值 1:1 内核，三方对齐 1690/1690 全绿）自 2026-11-09 起
# 是唯一默认与唯一 CLI 选项。历史 engine/（自研转译内核，engine/rng.flip 缺失已
# 不可用）与 simulator/combat.py（旧内核）已下线、文件保留作参考；两者仍可经
# simulate_once(engine=...) 显式指定（回归对照用）。三内核构造/run/summary/
# result_json 面一致。
ENGINES = ("gd_core",)
DEFAULT_ENGINE = "gd_core"


def _get_combat_engine(name: str = DEFAULT_ENGINE):
    """唯一内核 = gd_core。

    历史：engine/（自研转译内核，rng.flip 缺失不可用）与 simulator/combat.py
    （旧内核）已于 2026-11-10 下线；engine/ 整包删除（判据渲染器迁到
    simulator/log_text.py），旧内核对照工具随之退场，需要时查 git 历史。
    """
    if name == "gd_core":
        from .gd_core_engine import GDCoreEngine
        return GDCoreEngine, load_items, load_characters
    raise ValueError("未内核 %r：只支持 'gd_core'（旧内核对已下线）" % (name,))


def _log_events(eng) -> List[dict]:
    """统一两内核事件视图（两引擎 log 均实现 to_dict）"""
    data = eng.log.to_dict()
    if data is None:
        return []
    return data if isinstance(data, list) else data.get("events", [])


def _log_text(eng, lang: Optional[str]) -> str:
    """人类可读战报（两引擎 log 均实现 to_text）"""
    txt = eng.log.to_text(lang or "en")
    return txt if txt is not None else ""


def _out_basename(player_path: str, opponent_path: str) -> str:
    pa = os.path.splitext(os.path.basename(player_path))[0]
    oa = os.path.splitext(os.path.basename(opponent_path))[0]
    return f"{pa}_vs_{oa}"


def simulate_once(player_path: str, opponent_path: str, item_db, character_db,
                  seed: Optional[int], max_time: float = 90.0,
                  engine: str = DEFAULT_ENGINE,
                  light_log: bool = False) -> "CombatEngine":
    """light_log=True：logEvent 旁路化（S3-C12/M2-6，跳过事件物化）。

    logEvent 不消耗 rng、不改内核状态（docs/gd_core_engine.py::_LogMixin），
    跳过对胜负判定零影响；调用方必须不消费事件流（MC 只取胜负）才可开。
    单场/对照工具恒 False（默认），零行为变化。"""
    CombatEngine = _get_combat_engine(engine)[0]
    player = load_lineup(player_path)
    opponent = load_lineup(opponent_path)
    eng = CombatEngine(player, opponent, item_db, character_db,
                       seed=seed, max_time=max_time, light_log=light_log)
    eng.run()
    return eng


def save_outputs(eng: "CombatEngine", player_path: str, opponent_path: str,
                 outdir: str, seed: Optional[int], lang: Optional[str] = None):
    os.makedirs(outdir, exist_ok=True)
    base = _out_basename(player_path, opponent_path)
    seed_suffix = f"_seed{seed}" if seed is not None else ""
    log_json_path = os.path.join(outdir, f"{base}{seed_suffix}_log.json")
    result_path = os.path.join(outdir, f"{base}{seed_suffix}_result.json")
    log_txt_path = os.path.join(outdir, f"{base}{seed_suffix}_log.txt")

    # 战斗日志
    log_data = {
        "version": 1,
        "meta": {
            "seed": seed,
            "tick_rate": 60,
            "combat_delay": 2.5,
            "max_time": 90.0,
        },
        "setup": {
            "player": {"name": eng.player.display_name(),
                       "max_health": eng.player.get_max_health(),
                       "stamina": eng.player.get_max_stamina(),
                       "items": [it.key for it in eng.player_items]},
            "opponent": {"name": eng.opponent.display_name(),
                         "max_health": eng.opponent.get_max_health(),
                         "stamina": eng.opponent.get_max_stamina(),
                         "items": [it.key for it in eng.opponent_items]},
        },
        "events": _log_events(eng),
    }
    with open(log_json_path, 'w', encoding='utf-8') as f:
        json.dump(log_data, f, ensure_ascii=False, indent=2)

    # 战斗结果
    result = eng.result_json()
    with open(result_path, 'w', encoding='utf-8') as f:
        json.dump(result, f, ensure_ascii=False, indent=2)

    # 人类可读日志
    txt = _log_text(eng, lang)
    with open(log_txt_path, 'w', encoding='utf-8') as f:
        f.write(txt + "\n")

    return log_json_path, result_path, log_txt_path


def _mc_worker(job):
    """蒙特卡洛并行 worker（S1-E1/C12）：进程池任务入口，模块级函数保证可 pickle。

    只回传统计（E3-lite：胜负），不回传事件流——事件对象化的成本留在
    worker 侧（产品语义不变：胜负判定与 seed→战斗映射与串行路径完全一致）。
    light_log=True：logEvent 旁路化（S3-C12，跳过事件物化；logEvent 不消耗
    rng、不改内核状态，胜负判定零影响）。"""
    from simulator.gd_core_engine import GDCoreEngine
    from .lineup import load_lineup
    seed, player_path, opponent_path, max_time = job
    pl = load_lineup(player_path)
    op = load_lineup(opponent_path)
    eng = GDCoreEngine(pl, op, None, None, seed, max_time, light_log=True)
    eng.run()
    return bool(eng.player_wins())


def _pool_init(player_path, opponent_path, max_time):
    """S1-B9 worker 预热：进程 initializer——内核装载（B2 分层导入后
    gd_core 树一次 ≈0.75s）+ 一场热身战斗（解释器/JIT 缓存、_DESCR_CACHE
    描述符注册表全部就位）。热身用固定种子 1、独立 ctx，不污染任何战斗
    语义（每场隔离；正式场 seed 从任务传入）。"""
    try:
        eng = simulate_once(player_path, opponent_path, None, None, 1,
                            max_time, engine=DEFAULT_ENGINE)
        eng.run()
    except Exception:  # noqa: BLE001 —— 预热失败不挡任务（首轮任务自会装载）
        pass
    return True


def run_mc_pool(player_path, opponent_path, seed, runs, workers, max_time=90.0,
                progress_cb=None):
    """S1-E1/E2：蒙特卡洛进程池统一入口（CLI 与 GUI 共用）。

    · 逐 seed 确定性不变：seed_r = seed + r，与串行循环逐一对应——
      验收口径 = 逐 seed 胜负与串行全等（G1 门）。
    · E2 动态批次：seeds 切成 8 场/批交给池（ex.map chunksize=8），worker
      完成一批即领下一批，长尾场不拖住整块；批内结果聚合回传统计（E3）。
    · progress_cb(done, wins)：按完成批回报（GUI 侧再 50ms 节流，G4）。
    返回 wins（玩家胜场数）。
    """
    from concurrent.futures import ProcessPoolExecutor
    import multiprocessing as _mp
    workers = max(1, min(workers, _mp.cpu_count(), runs))
    jobs = [(seed + r if seed is not None else None,
             player_path, opponent_path, max_time)
            for r in range(runs)]
    wins = 0
    done = 0
    with ProcessPoolExecutor(max_workers=workers,
                             initializer=_pool_init,
                             initargs=(player_path, opponent_path, max_time)) as ex:
        for w in ex.map(_mc_worker, jobs, chunksize=8):
            wins += bool(w)
            done += 1
            if progress_cb is not None:
                progress_cb(done, wins)
    return wins


# ═══════════════════ §9.6 训练场景 API（内存态批量 + 统计回传） ═══════════════════
# 面向 RL 训练循环：lineup 以内存 dict 直传（免每次读盘+JSON 解析）、
# 逐场回传统计（ticks/combat_time/damage，供 reward shaping）。
# 确定性口径与 run_mc_pool 完全一致（seed_r = seed + r，逐 seed 与串行全等）。
# want_stats=True 时该场退回全量探针（logEvent 计数面）——统计精确、单场变慢；
# 只要胜负时保持 light_log=True（S3-C12 口径）。


def _mc_mem_worker(job):
    """内存态蒙特卡洛 worker（§9.6）：dict 直传 + 可选统计。模块级可 pickle。"""
    from simulator.gd_core_engine import GDCoreEngine
    seed, player, opponent, max_time, want_stats = job
    light = not want_stats
    eng = GDCoreEngine(player, opponent, None, None, seed, max_time,
                       light_log=light)
    eng.run()
    rec = {
        "seed": seed,
        "win": bool(eng.player_wins()),
        "ticks": int(eng._ticks),
        "combat_time": round(float(eng.combat_time), 2),
        "reason": eng.win_reason,
    }
    if want_stats:
        st = eng.log.stats
        rec["damage_dealt"] = {"player": st[0]["damage_dealt"],
                               "opponent": st[1]["damage_dealt"]}
        rec["healing_done"] = {"player": st[0]["healing_done"],
                               "opponent": st[1]["healing_done"]}
        rec["crits"] = {"player": st[0]["crits"], "opponent": st[1]["crits"]}
        rec["misses"] = {"player": st[0]["misses"], "opponent": st[1]["misses"]}
        rec["out_of_stamina"] = {"player": st[0]["out_of_stamina"],
                                 "opponent": st[1]["out_of_stamina"]}
        rec["activations"] = {"player": st[0]["activations"],
                              "opponent": st[1]["activations"]}
    return rec


def _agg_p50(xs):
    import statistics as _stat
    return round(_stat.median(xs), 1) if xs else None


def run_mc_mem(player, opponent, seed, runs, workers=1, max_time=90.0,
               want_stats=False, progress_cb=None):
    """内存态批量对战（§9.6 训练 API）。

    player/opponent：lineup dict（与 lineup JSON 同构；GDCoreEngine 直接收）。
    返回聚合 dict：
      {runs, wins_player, win_rate, ticks_p50, ticks_mean, combat_time_mean,
       per-run 逐场明细 records（含 seed 胜负 ticks；want_stats 时加六面统计）}
    确定性：seed_r = seed + r，与 run_mc_pool/串行循环逐 seed 全等（G1 口径）。
    """
    from concurrent.futures import ProcessPoolExecutor
    import multiprocessing as _mp
    import statistics as _stat
    runs = max(1, int(runs))
    workers = max(1, min(workers, _mp.cpu_count(), runs))
    jobs = [(seed + r if seed is not None else None,
             player, opponent, max_time, bool(want_stats))
            for r in range(runs)]
    records = []
    with ProcessPoolExecutor(max_workers=workers,
                             initializer=_pool_init_mem,
                             initargs=()) as ex:
        for i, rec in enumerate(ex.map(_mc_mem_worker, jobs, chunksize=8)):
            records.append(rec)
            if progress_cb is not None:
                progress_cb(i + 1, sum(1 for x in records if x["win"]))
    ticks = [r["ticks"] for r in records]
    agg = {
        "runs": runs,
        "wins_player": sum(1 for r in records if r["win"]),
        "win_rate": round(sum(1 for r in records if r["win"]) / runs * 100.0, 2),
        "ticks_p50": _agg_p50(ticks),
        "ticks_mean": round(_stat.fmean(ticks), 1) if ticks else None,
        "combat_time_mean": round(_stat.fmean([r["combat_time"] for r in records]), 2)
        if records else None,
        "records": records,
    }
    if want_stats:
        agg["damage_dealt"] = {
            "player": round(_stat.fmean([r["damage_dealt"]["player"] for r in records]), 1),
            "opponent": round(_stat.fmean([r["damage_dealt"]["opponent"] for r in records]), 1),
        }
        agg["healing_done"] = {
            "player": round(_stat.fmean([r["healing_done"]["player"] for r in records]), 1),
            "opponent": round(_stat.fmean([r["healing_done"]["opponent"] for r in records]), 1),
        }
        agg["crits"] = {
            "player": sum(r["crits"]["player"] for r in records),
            "opponent": sum(r["crits"]["opponent"] for r in records),
        }
        agg["misses"] = {
            "player": sum(r["misses"]["player"] for r in records),
            "opponent": sum(r["misses"]["opponent"] for r in records),
        }
        agg["out_of_stamina"] = {
            "player": sum(r["out_of_stamina"]["player"] for r in records),
            "opponent": sum(r["out_of_stamina"]["opponent"] for r in records),
        }
        agg["activations"] = {
            "player": sum(r["activations"]["player"] for r in records),
            "opponent": sum(r["activations"]["opponent"] for r in records),
        }
    return agg


def _pool_init_mem():
    """§9.6 worker 预热（内存态版）：内核装载 + 一场热身（固定种子 1，
    独立 ctx，不污染战斗语义；与 _pool_init 同口径，入参免读盘）。"""
    try:
        from simulator.gd_core_engine import GDCoreEngine
        eng = GDCoreEngine({"backpack": {"items": []}},
                           {"backpack": {"items": []}}, {}, {},
                           seed=1, max_time=1.0)
        eng.run()
    except Exception:  # noqa: BLE001 —— 预热失败不挡任务（首轮自会装载）
        pass
    return True


def main(argv: Optional[List[str]] = None) -> int:
    ap = argparse.ArgumentParser(description='Backpack Battles 战斗模拟器（输入两阵容 JSON）')
    ap.add_argument('player', help='玩家阵容 JSON 文件')
    ap.add_argument('opponent', help='对手阵容 JSON 文件')
    ap.add_argument('--seed', type=int, default=None, help='随机种子（固定可复现）')
    ap.add_argument('--outdir', default='output', help='输出目录（默认 output/）')
    ap.add_argument('--runs', type=int, default=1, help='模拟场数（>1 为蒙特卡洛，只输出统计）')
    ap.add_argument('--workers', type=int, default=1,
                    help='蒙特卡洛并行 worker 数（>1 且 --runs>1 时启用进程池；'
                         '逐 seed 结果与串行全等）')
    ap.add_argument('--max-time', type=float, default=90.0, help='最大战斗时长（秒）')
    ap.add_argument('--engine', choices=ENGINES, default=DEFAULT_ENGINE,
                    help='战斗内核：gd_core（唯一默认，逆向真值 1:1）')
    ap.add_argument('--verbose', action='store_true', help='打印详细结果')
    args = ap.parse_args(argv)

    _, load_items, load_characters = _get_combat_engine(args.engine)
    item_db = load_items()
    character_db = load_characters()

    # 预校验阵容
    try:
        player_lineup = load_lineup(args.player)
        opponent_lineup = load_lineup(args.opponent)
    except LineupError as e:
        print(f"❌ 阵容加载失败: {e}", file=sys.stderr)
        return 2

    # 物品库覆盖检查
    for path, lineup in ((args.player, player_lineup), (args.opponent, opponent_lineup)):
        found, unknown = resolve_items(lineup, item_db)
        if unknown:
            print(f"⚠ [{os.path.basename(path)}] 以下物品不在物品库中，将被忽略: "
                  f"{', '.join(dict.fromkeys(unknown))}", file=sys.stderr)

    wins = 0
    t0 = time.time()
    last_eng = None

    # ── 蒙特卡洛并行路径（S1-E1/E2/B9）：--workers>1 且 runs>1 ──
    # 逐 seed 确定性不变：seed = args.seed + run，与串行循环逐一对应，
    # 因此胜负对拍必须逐 seed 全等（验收口径，docs/性能优化执行路径.md S1）。
    if args.workers > 1 and args.runs > 1:
        wins = run_mc_pool(args.player, args.opponent, args.seed, args.runs,
                           args.workers, args.max_time)
        rate = wins / args.runs * 100
        print(f"\n=== {args.runs} 场统计（workers={args.workers}） ===")
        print(f"  玩家胜率: {rate:.1f}%  ({wins}/{args.runs})  "
              f"耗时: {time.time() - t0:.1f}s")
        return 0

    for run in range(args.runs):
        seed = args.seed + run if args.seed is not None else None
        # ★ M2-6：串行 MC（runs>1）与并行 _mc_worker 同口径——事件物化旁路化，
        #   只累加胜负；runs==1 单场路径不变（全量事件+落盘+战报）。
        eng = simulate_once(args.player, args.opponent, item_db, character_db,
                            seed, args.max_time, engine=args.engine,
                            light_log=(args.runs > 1))
        last_eng = eng
        if eng.player_wins():
            wins += 1

        if args.runs == 1:
            log_path, result_path, txt_path = save_outputs(
                eng, args.player, args.opponent, args.outdir, args.seed)
            s = eng.summary()
            print(f"⚔ {s['player']['name']} vs {s['opponent']['name']}")
            print(f"  结果: {'玩家胜 ✅' if eng.player_wins() else '玩家败 ❌'}  "
                  f"原因: {s['reason']}  耗时: {s['time']}s")
            print(f"  玩家 HP: {s['player']['hp']}/{s['player']['max_hp']}  "
                  f"体力: {s['player']['stamina']}  buffs: {s['player']['buffs']}")
            print(f"  对手 HP: {s['opponent']['hp']}/{s['opponent']['max_hp']}  "
                  f"体力: {s['opponent']['stamina']}  buffs: {s['opponent']['buffs']}")
            print(f"  玩家统计: 伤害 {s['player']['stats']['damage_dealt']} | "
                  f"治疗 {s['player']['stats']['healing_done']} | "
                  f"暴击 {s['player']['stats']['crits']} | "
                  f"未命中 {s['player']['stats']['misses']} | "
                  f"体力耗尽 {s['player']['stats']['out_of_stamina']}")
            print(f"  疲劳计数: {s['fatigue_counter']}")
            print(f"📄 战斗日志 JSON: {log_path}")
            print(f"📄 战斗结果 JSON: {result_path}")
            print(f"📄 人类可读日志: {txt_path}")
            if args.verbose:
                print(f"\n--- 战斗过程 ---")
                print(_log_text(eng, None))

    if args.runs > 1:
        print(f"\n=== {args.runs} 场统计 ===")
        print(f"  玩家胜率: {wins / args.runs * 100:.1f}%  ({wins}/{args.runs})  "
              f"耗时: {time.time() - t0:.1f}s")
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
