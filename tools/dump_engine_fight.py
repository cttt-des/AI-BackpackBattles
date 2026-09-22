# -*- coding: utf-8 -*-
"""
engine 侧战斗事件导出——一致性验证的被测数据源。

与原版游戏对账（docs/consistency_verification.md）：
游戏侧用 bridge v2 的 tap_combat 拿真值事件流，本工具用同初态 lineup + 同种子
在 engine/ 上复放并导出同一 JSON 结构，供 diff 工具比对。

用法：
  python tools/dump_engine_fight.py <player.json> <opponent.json> --seed 42 [-o out.json]
  python tools/dump_engine_fight.py <player.json> <opponent.json> --seed 42 --runs 30  # 统计模式

输出 JSON：
  {"engine": "engine", "seed": 42, "player": ..., "opponent": ...,
   "result": {"winner": ..., "duration_s": ..., "player_hp": ..., "opponent_hp": ...},
   "events": [...],   # 单场模式：log.to_dict()
   "text": "...",     # 游戏格式战斗日志（log_text 渲染）
   "stats": {...}}    # 统计模式：胜率/场均时长/伤害
"""

import argparse
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))

from simulator.simulate import simulate_once, load_lineup, _log_events, _log_text
from simulator.data import load_items, load_characters


def run_once(player_path, opponent_path, item_db, character_db, seed, max_time=90.0):
    eng = simulate_once(player_path, opponent_path, item_db, character_db,
                        seed=seed, max_time=max_time, engine="engine")
    return eng


def main() -> int:
    ap = argparse.ArgumentParser(description="engine/ 战斗事件导出（一致性验证被测侧）")
    ap.add_argument("player")
    ap.add_argument("opponent")
    ap.add_argument("--seed", type=int, required=True)
    ap.add_argument("--runs", type=int, default=1, help=">1 为统计模式（蒙特卡洛）")
    ap.add_argument("--max-time", type=float, default=90.0)
    ap.add_argument("-o", "--out", default=None, help="输出 JSON 路径（默认 stdout）")
    args = ap.parse_args()

    item_db, character_db = load_items(), load_characters()

    if args.runs > 1:
        wins = 0
        durations = []
        for i in range(args.runs):
            eng = run_once(args.player, args.opponent, item_db, character_db,
                           seed=args.seed + i, max_time=args.max_time)
            r = eng.result_json() if hasattr(eng, "result_json") else {}
            meta = r.get("meta", {})
            if meta.get("winner") == "player":
                wins += 1
            durations.append(meta.get("fight_time", 0))
        out = {
            "engine": "engine", "seed": args.seed, "runs": args.runs,
            "player": Path(args.player).stem, "opponent": Path(args.opponent).stem,
            "stats": {
                "win_rate": wins / args.runs,
                "avg_duration_s": sum(durations) / max(len(durations), 1),
            },
        }
    else:
        eng = run_once(args.player, args.opponent, item_db, character_db,
                       seed=args.seed, max_time=args.max_time)
        events = _log_events(eng)
        text = _log_text(eng, "zh")
        r = eng.result_json() if hasattr(eng, "result_json") else {}
        out = {
            "engine": "engine", "seed": args.seed,
            "player": Path(args.player).stem, "opponent": Path(args.opponent).stem,
            "result": r,
            "event_count": len(events),
            "events": events,
            "text": text,
        }

    payload = json.dumps(out, ensure_ascii=False, indent=1)
    if args.out:
        Path(args.out).write_text(payload, encoding="utf-8")
        print(f"已写出 {args.out}（事件 {out.get('event_count', '-')} 条）", file=sys.stderr)
    else:
        print(payload)
    return 0


if __name__ == "__main__":
    sys.exit(main())
