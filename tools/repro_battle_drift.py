# -*- coding: utf-8 -*-
"""repro_battle_drift.py —— 引擎「同进程跨场状态泄漏」最小复现（6.1）

用法:
    python tools/repro_battle_drift.py            # 三组对照实验
    python tools/repro_battle_drift.py --once     # 只跑一场（供外部循环）

预期（修复前）:
    A 同进程连跑 4 次  → 4 个不同指纹
    B 每场前 _bind_battle(seed) → 4 个相同指纹
    C 每个进程只跑 1 场 → 8 次进程调用全同

预期（修复后）:
    A 也应收敛为 1 个指纹
"""
import hashlib
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from trainer.evaluator import OpponentPool, _to_engine_form  # noqa: E402
from simulator.gd_core_engine import GDCoreEngine  # noqa: E402
import gd_core_py._rt as RT  # noqa: E402

IDX = 9
SEED = 12345
BAND = (450, 650)


def _pair():
    pool = OpponentPool()
    opps = pool.sample(BAND, 100, seed=1)
    p = _to_engine_form(opps[0])
    o = _to_engine_form(opps[IDX % len(opps)])
    return p, o, SEED + IDX


def _fp(p, o, seed):
    e = GDCoreEngine(p, o, seed=seed)
    e.run()
    evs = [(round(getattr(ev, "t", 0), 6), str(getattr(ev, "origin", None)),
            str(getattr(ev, "params", None))[:50]) for ev in e.log.events]
    h = hashlib.sha256(json.dumps(evs, default=str).encode()).hexdigest()[:12]
    return h, int(e._ticks), len(evs)


def main(argv):
    p, o, seed = _pair()
    if "--once" in argv:
        h, t, n = _fp(p, o, seed)
        print(h, t, n)
        return 0

    print("A 原样连跑 4 次（修复前每场不同）:")
    for _ in range(4):
        print("   ", _fp(p, o, seed))

    print("B 每场前手动 _bind_battle(seed)（修复前即收敛）:")
    for _ in range(4):
        RT._bind_battle(seed)
        print("   ", _fp(p, o, seed))
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
