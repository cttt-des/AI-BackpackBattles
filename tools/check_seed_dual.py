# -*- coding: utf-8 -*-
"""seed 双态指纹校验：跑两个固定 seed，比对 ticks/events/winner。

用法：
    python -X utf8 tools/check_seed_dual.py

判据（台账 §0）：
    seed=20260923 → ticks=907  events=1548
    seed=42       → ticks=1042 events=1991

为什么需要它：这两个数对「内核语义」最敏感——任何改动只要挪动了一次 RNG 抽取、
一次 tick 内的求值次序、或一个物品的触发时刻，ticks 或 events 就会变。
它比 60 场对齐快两个数量级（秒级），是改内核时最先跑的那道闸。
"""
import json
import os
import sys

_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if _ROOT not in sys.path:
    sys.path.insert(0, _ROOT)

EXPECT = {20260923: (907, 1548), 42: (1042, 1991)}
PL = os.path.join(_ROOT, "lineups", "truth_20261001_220653_R19_player.json")
OP = os.path.join(_ROOT, "lineups", "truth_20261001_220653_R19_opponent.json")


def main() -> int:
    from simulator.gd_core_engine import GDCoreEngine
    plj = json.load(open(PL, encoding="utf-8"))
    opj = json.load(open(OP, encoding="utf-8"))
    copy = __import__("copy").deepcopy
    fails = 0
    for seed, (exp_ticks, exp_events) in EXPECT.items():
        e = GDCoreEngine(copy(plj), copy(opj), {}, {}, seed=seed, max_time=180.0)
        e.run()
        ticks, events = int(e._ticks), e.log.event_count
        ok = (ticks == exp_ticks and events == exp_events)
        fails += 0 if ok else 1
        print("seed=%-9d ticks=%-5d events=%-5d %s"
              % (seed, ticks, events, "OK" if ok else
                 "DRIFT (期望 %d/%d)" % (exp_ticks, exp_events)))
    print()
    print("FAILS = %d" % fails)
    return 1 if fails else 0


if __name__ == "__main__":
    raise SystemExit(main())
