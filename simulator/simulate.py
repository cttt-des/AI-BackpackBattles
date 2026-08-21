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

from .combat import CombatEngine
from .data import load_items, load_characters
from .lineup import load_lineup, LineupError, resolve_items


def _out_basename(player_path: str, opponent_path: str) -> str:
    pa = os.path.splitext(os.path.basename(player_path))[0]
    oa = os.path.splitext(os.path.basename(opponent_path))[0]
    return f"{pa}_vs_{oa}"


def simulate_once(player_path: str, opponent_path: str, item_db, character_db,
                  seed: Optional[int], max_time: float = 90.0) -> CombatEngine:
    player = load_lineup(player_path)
    opponent = load_lineup(opponent_path)
    eng = CombatEngine(player, opponent, item_db, character_db,
                       seed=seed, max_time=max_time)
    eng.run()
    return eng


def save_outputs(eng: CombatEngine, player_path: str, opponent_path: str,
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
        "events": eng.log.to_dict(),
    }
    with open(log_json_path, 'w', encoding='utf-8') as f:
        json.dump(log_data, f, ensure_ascii=False, indent=2)

    # 战斗结果
    result = eng.result_json()
    with open(result_path, 'w', encoding='utf-8') as f:
        json.dump(result, f, ensure_ascii=False, indent=2)

    # 人类可读日志
    txt = eng.log.to_text(lang)
    with open(log_txt_path, 'w', encoding='utf-8') as f:
        f.write(txt + "\n")

    return log_json_path, result_path, log_txt_path


def main(argv: Optional[List[str]] = None) -> int:
    ap = argparse.ArgumentParser(description='Backpack Battles 战斗模拟器（输入两阵容 JSON）')
    ap.add_argument('player', help='玩家阵容 JSON 文件')
    ap.add_argument('opponent', help='对手阵容 JSON 文件')
    ap.add_argument('--seed', type=int, default=None, help='随机种子（固定可复现）')
    ap.add_argument('--outdir', default='output', help='输出目录（默认 output/）')
    ap.add_argument('--runs', type=int, default=1, help='模拟场数（>1 为蒙特卡洛，只输出统计）')
    ap.add_argument('--max-time', type=float, default=90.0, help='最大战斗时长（秒）')
    ap.add_argument('--verbose', action='store_true', help='打印详细结果')
    args = ap.parse_args(argv)

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
    for run in range(args.runs):
        seed = args.seed + run if args.seed is not None else None
        eng = CombatEngine(player_lineup, opponent_lineup, item_db, character_db,
                           seed=seed, max_time=args.max_time)
        eng.run()
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
                print(eng.log.to_text())

    if args.runs > 1:
        print(f"\n=== {args.runs} 场统计 ===")
        print(f"  玩家胜率: {wins / args.runs * 100:.1f}%  ({wins}/{args.runs})  "
              f"耗时: {time.time() - t0:.1f}s")
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
