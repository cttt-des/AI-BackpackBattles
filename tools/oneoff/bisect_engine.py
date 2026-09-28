# -*- coding: utf-8 -*-
"""二分：找出 GDCoreEngine 与 run_gd_py 装配路径的差异来源。"""
import os
import sys

ROOT = r"D:\文件资料\学习\自动背包AI"
sys.path.insert(0, ROOT)

from simulator import gd_core_engine as GE                      # noqa: E402
from simulator.lineup import load_lineup                        # noqa: E402
from tools.check_gd_core_engine import _make_bench_probe, outcome  # noqa: E402

names = ["lineup_armor_wall", "lineup_cursed_reaper", "lineup_dagger_swarm"]
lu = {n: load_lineup(os.path.join(ROOT, "lineups", n + ".json")) for n in names}
probe = _make_bench_probe()
BASE_SEED, STRIDE = 20260923, 101

# 基准（来自 gd_core_test/lineup_result.txt）
BASE = {
    ("armor_wall", "cursed_reaper"):
        "win=O t=22.20 php=0 ohp=40 act=36 dmg=37/205.0 heal=20/49.0 gem=0/0.0 fat=8 stun=0",
    ("cursed_reaper", "armor_wall"):
        "win=P t=23.02 php=34 ohp=0 act=39 dmg=40/210.0 heal=21/52.0 gem=0/0.0 fat=9 stun=0",
    ("dagger_swarm", "cursed_reaper"):
        "win=O t=8.38 php=0 ohp=41 act=18 dmg=14/69.0 heal=8/49.0 gem=0/0.0 fat=1 stun=0",
    ("armor_wall", "dagger_swarm"):
        "win=P t=27.02 php=25 ohp=0 act=51 dmg=43/199.0 heal=11/52.0 gem=0/0.0 fat=13 stun=0",
}

PAIRS = [("lineup_armor_wall", "lineup_cursed_reaper"),
         ("lineup_cursed_reaper", "lineup_armor_wall"),
         ("lineup_dagger_swarm", "lineup_cursed_reaper"),
         ("lineup_armor_wall", "lineup_dagger_swarm")]


def run(label, patch=None):
    print("=== %s ===" % label)
    for a, b in PAIRS:
        if patch:
            patch()
        seed = BASE_SEED + STRIDE * names.index(a) + names.index(b)
        eng = GE.GDCoreEngine(lu[a], lu[b], {}, {}, seed=seed, max_time=180.0,
                              probe_bases=(probe,))
        eng.run()
        got = outcome(eng)
        ref = BASE[(a[7:], b[7:])]
        print("  %-28s %s   %s" % (a[7:] + " vs " + b[7:],
                                   "OK " if got == ref else "DIFF", got))
        if got != ref:
            print("  %-28s 基准%s" % ("", " " * 4 + ref))
    print()


# ① 现状
run("① 现状")

# ② 不设 ctx.cur_round
_orig_make = GE.GDCoreEngine.__init__


def patch_no_round():
    GE.GDCoreEngine.__init__ = _orig_make


# 包一层：临时把 cur_round 写回 0
_orig_ctx_cls = None
print("lineups 物品清单：")
for n in names:
    items = []
    for sec in ("backpack", "storage"):
        for e in (lu[n].get(sec) or {}).get("items") or []:
            items.append("%s@%s,%s r%s%s" % (e.get("id"), e.get("row"), e.get("col"),
                                             e.get("rotation"),
                                             "/S" if sec == "storage" else ""))
    print("  %-20s class=%s round=%s\n      %s"
          % (n, lu[n].get("character"), lu[n].get("round"), ", ".join(items)))
