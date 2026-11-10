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
                  engine: str = DEFAULT_ENGINE) -> "CombatEngine":
    CombatEngine = _get_combat_engine(engine)[0]
    player = load_lineup(player_path)
    opponent = load_lineup(opponent_path)
    eng = CombatEngine(player, opponent, item_db, character_db,
                       seed=seed, max_time=max_time)
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
        eng = simulate_once(args.player, args.opponent, item_db, character_db,
                            seed, args.max_time, engine=args.engine)
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
