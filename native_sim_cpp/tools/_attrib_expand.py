# -*- coding: utf-8 -*-
"""60 场分歧归因实验（只测不修）：expand 语料 py 腿四臂对照。

臂A = verify_oracle 复刻（below_master=True + 夹具 gems 槽长 + rng_state 注入 + recorded 终序 + p_stats）
臂B = A 去掉 rng_state 注入（纯 seed 重播种）
臂C = B 换 below_master=False（辨 below_master 方向）
臂D = A 的 below_master 档位 + 无 gems 槽长（= native 现行装配口径：descr sockets）
对照：账本（winner.oracle/oracleEvents，含 +1 合成行）与 native 三闸结果。
"""
import json
import os
import sys

ROOT = r"D:\文件资料\学习\自动背包AI"
sys.path.insert(0, ROOT)  # 只用主仓 simulator（bundle 自带副本较旧，无 p_stats/rng_state）

os.environ["GD_PURE_PY"] = "1"  # 纯 py 臂：另一会话 build_cython 正占用 pyd，绕开 DLL 锁
sys.path.insert(0, os.path.join(ROOT, "tools"))
import _purepy_arm  # noqa: E402,F401  必须先装 finder 屏蔽 pyd（env 置位后）

from simulator.gd_core_engine import GDCoreEngine  # noqa: E402
from simulator.lineup import load_lineup  # noqa: E402
from verify_oracle import _FightEndGate  # noqa: E402

CASES = [
    "run704507_r18_o101208_r18",
    "run604732_r10_o704548_r11",
    "run101617_r16_o300168_r16",
]


def load_case(cid):
    case = next(c for c in json.load(open(os.path.join(ROOT, "gd_core_test", "expand_align_cases.json"), encoding="utf-8"))["cases"] if c["case_id"] == cid)
    raw = {"player": case["player"], "opponent": case["opponent"]}  # case json 原始条目（gems 长度/体力真值）
    case["player"] = load_lineup(os.path.join(ROOT, "output", "oracle", "align_expand", "lineups", "oracle_%s_player.json" % cid))
    case["opponent"] = load_lineup(os.path.join(ROOT, "output", "oracle", "align_expand", "lineups", "oracle_%s_opponent.json" % cid))
    case["_raw"] = raw
    return case, raw
    led = next(c for c in json.load(open(os.path.join(ROOT, "output", "oracle", "expand", "alignment_expand.json"), encoding="utf-8"))["perCase"] if c["caseId"] == cid)
    gd = json.load(open(os.path.join(ROOT, "output", "oracle", "align_expand", "gdcore", cid, "events.json"), encoding="utf-8"))
    order = gd["activation_order"]
    rs = {}
    with open(os.path.join(ROOT, "output", "oracle", "expand", "fights", cid, "rng_state.txt"), encoding="utf-8") as f:
        for ln in f:
            if ln.startswith("seed="):
                rs["seed"] = int(ln.strip()[5:])
            elif ln.startswith("state="):
                rs["state"] = int(ln.strip()[6:])
    return case, led, order, rs


def run_arm(case, raw, order, *, below_master, gem_lens, rng_state):
    kw = dict(seed=int(case["seed"]), max_time=90.0,
              probe_bases=(_FightEndGate,),
              below_master=below_master,
              reseed_after_player_character=True,
              post_seed_draws=0,
              label_rng_enabled=bool(case.get("label_rng", True)),
              p_activation_order=[int(x) for x in order["player"]],
              o_activation_order=[int(x) for x in order["opponent"]],
              formal_ev_gate=25000,
              custom_health_multiplier=float(case.get("custom_health_multiplier", 100.0)),
              p_stats={"stamina": raw["player"].get("stamina"),
                       "health": raw["player"].get("health"),
                       "regen": raw["player"].get("regen")},
              o_stats={"stamina": raw["opponent"].get("stamina"),
                       "health": raw["opponent"].get("health"),
                       "regen": raw["opponent"].get("regen")},
              rng_state=rng_state)
    if gem_lens:
        kw["p_gem_lens"] = [len(e.get("gems") or []) for e in raw["player"]["items"] if not e.get("storage")]
        kw["o_gem_lens"] = [len(e.get("gems") or []) for e in raw["opponent"]["items"] if not e.get("storage")]
    eng = GDCoreEngine(case["player"], case["opponent"], {}, {}, **kw)
    eng.run()
    return {"ticks": int(eng._ticks),
            "winner": "player" if eng.player_wins() else "opponent",
            "events": int(eng.log.event_count),
            "php": float(eng._p.curHealth), "ohp": float(eng._o.curHealth)}


def main():
    gate = json.load(open(os.path.join(ROOT, "native_sim_cpp", "output", "three_gates_g23.json"), encoding="utf-8"))
    native = {r["case_id"]: r["got"] for r in gate["results"]["gate3_60"]["perCase"]}
    for cid in CASES:
        case, raw = load_case(cid)
        led = next(c for c in json.load(open(os.path.join(ROOT, "output", "oracle", "expand", "alignment_expand.json"), encoding="utf-8"))["perCase"] if c["caseId"] == cid)
        gd = json.load(open(os.path.join(ROOT, "output", "oracle", "align_expand", "gdcore", cid, "events.json"), encoding="utf-8"))
        order = gd["activation_order"]
        rs = {}
        with open(os.path.join(ROOT, "output", "oracle", "expand", "fights", cid, "rng_state.txt"), encoding="utf-8") as f:
            for ln in f:
                if ln.startswith("state="):
                    rs["state"] = int(ln.strip()[6:])
        nt = native.get(cid, {})
        print(f"== {cid}")
        print(f"   账本: win={led['winner']['oracle']} ev={led['oracleEvents']} (seed={case['seed']}, 录制state={rs['state']%2**63})")
        print(f"   native: win={nt.get('winner')} ev={nt.get('events')} ticks={nt.get('ticks')}")
        for tag, kw in [
            ("A 复刻(=True,gl,state)", dict(below_master=True, gem_lens=True, rng_state=rs["state"])),
            ("B 无state(=True,gl)", dict(below_master=True, gem_lens=True, rng_state=None)),
            ("C bl=False(+gl,state)", dict(below_master=False, gem_lens=True, rng_state=rs["state"])),
            ("D 无gl(=True,state)", dict(below_master=True, gem_lens=False, rng_state=rs["state"])),
        ]:
            try:
                r = run_arm(case, raw, order, **kw)
                print(f"   {tag}: ticks={r['ticks']} win={r['winner']} ev={r['events']} php={r['php']} ohp={r['ohp']}")
            except Exception as e:
                print(f"   {tag}: EXC {type(e).__name__}: {e}")


if __name__ == "__main__":
    main()
