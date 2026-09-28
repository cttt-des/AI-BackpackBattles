#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
check_gd_core_engine.py — 证明 `simulator/gd_core_engine.py` 跑的是**那份被验证过的逻辑**

为什么要单独存在
================
「引擎能跑通一局」不是判据，「引擎和 Godot 侧基准逐字符一致」才是。本工具把
`gd_core_test/lineup_result.txt` 里那 56 行（**Godot 3.6 宿主**跑出来的权威基准）
拿来，逐行比对 `simulator/gd_core_engine.py` 经**生产装配路径**跑出来的同 56 局。

三处调用点、一份口径
====================
    ① gd_core_test/LineupBattle.gd         ← Godot 3.6 宿主，产出基准
    ② tools/run_gd_py.py                   ← Python 侧端到端驱动器
    ③ simulator/gd_core_engine.py          ← 模拟器内核（本工具的被测对象）

三者用的是同一套装配次序、同一套种子公式、同一批阵容。①②已对齐；本工具把③也拉进来。
差异只可能来自：装配次序被改、运行时数据资产失真、事件/计量钩子口径漂移。

计数口径（★ 与 ① 逐字一致，不是「差不多」）
==========================================
`_BenchProbe` 覆写的四个钩子，与 `LineupBattle.gd::HookProbe` 一一对应：

    snapshotItemMetric(ItemMetrics.Activations)   → act
    spawnLabel_character(type==Health ? heal : dmg) → dmg / heal / gem
    playFatigueAnimation                          → fat
    playStunAnimation                             → stun

★ 激活计数走**统计埋点**而非动画钩子：原版 `Item.activate()` 只在
  `animationOverride != null` 时才播放激活动画，常规触发那次不走它 —— 拿动画计数会
  得到「act=0 但伤害照打」的假警报。

用法
====
    python tools/check_gd_core_engine.py             # 全量 56 局比对
    python tools/check_gd_core_engine.py --limit 3   # 只跑前 N 个阵容（调试）
    python tools/check_gd_core_engine.py --report    # 额外打印逐局明细
"""
from __future__ import annotations

import argparse
import io
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)

from simulator.gd_core_engine import (  # noqa: E402
    GDCoreEngine, class_id_of, kernel, runtime_data)
from simulator.lineup import load_lineup  # noqa: E402

BASE_SEED = 20260923
PAIR_STRIDE = 101
TIME_LIMIT = 180.0
BASELINE = os.path.join(ROOT, "gd_core_test", "lineup_result.txt")
LINEUP_DIR = os.path.join(ROOT, "lineups")
OUT_PATH = os.path.join(ROOT, "output", "engine_gd_core_result.txt")


# ═══════════════════════ 基准同口径探针 ═══════════════════════

def _make_bench_probe():
    """延迟构造：`CoreConst` 与 `CoreItem` 要等 kernel() 装载完才有。"""
    k = kernel()
    Const = k["CoreConst"]
    Item = k["CoreItem"]

    class _BenchProbe:
        def _init_fields(self):
            super()._init_fields()
            self.activations = 0
            self.damage_events = 0
            self.damage_sum = 0.0
            self.heal_events = 0
            self.heal_sum = 0.0
            self.gem_heals = 0
            self.gem_heal_sum = 0.0
            self.fatigue_ticks = 0
            self.stuns = 0

        def snapshotItemMetric(self, _item, metricIndex, _playerId=None,
                               _withNextEvent=False):
            if metricIndex == Const.ItemMetrics.Activations:
                self.activations += 1

        def spawnLabel_character(self, _character, type, damage, item=None):
            if type == Const.EventType.Health:
                self.heal_events += 1
                self.heal_sum += abs(float(damage))
                if item is not None and isinstance(item, Item) and item.isGem():
                    self.gem_heals += 1
                    self.gem_heal_sum += abs(float(damage))
            else:
                self.damage_events += 1
                self.damage_sum += abs(float(damage))

        def playFatigueAnimation(self, _name):
            self.fatigue_ticks += 1

        def playStunAnimation(self, _character, _duration):
            self.stuns += 1

    return _BenchProbe


def outcome(eng) -> str:
    pr = eng.hooks
    return ("win=%s t=%.2f php=%.0f ohp=%.0f act=%d dmg=%d/%s heal=%d/%s "
            "gem=%d/%s fat=%d stun=%d" % (
                "P" if eng.player_wins() else "O", eng.combat_time,
                eng._p.curHealth, eng._o.curHealth,
                pr.activations, pr.damage_events, "%.1f" % pr.damage_sum,
                pr.heal_events, "%.1f" % pr.heal_sum,
                pr.gem_heals, "%.1f" % pr.gem_heal_sum,
                pr.fatigue_ticks, pr.stuns))


def parse_rows(text):
    """从结果文件抽 `xxx vs yyy：win=…` 行 → {对决名: 结果串}。"""
    out = {}
    for line in text.split("\n"):
        s = line.strip()
        if " vs " in s and "：win=" in s:
            name, rest = s.split("：", 1)
            out[name.strip()] = rest.strip()
    return out


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--limit", type=int, default=0,
                    help="只用前 N 个阵容（调试用；0 = 全部 8 个）")
    ap.add_argument("--report", action="store_true", help="打印逐局明细")
    args = ap.parse_args()

    data = runtime_data()
    names = sorted(data["counts"]["lineup_names"])
    if args.limit:
        names = names[:args.limit]

    lineups = {}
    for n in names:
        lineups[n] = load_lineup(os.path.join(LINEUP_DIR, n + ".json"))

    probe_cls = _make_bench_probe()
    rows = []
    timeouts = []
    zero_act = []
    for a in names:
        for b in names:
            if a == b:
                continue
            seed = (BASE_SEED + PAIR_STRIDE * names.index(a) + names.index(b))
            eng = GDCoreEngine(lineups[a], lineups[b], {}, {}, seed=seed,
                               max_time=TIME_LIMIT, probe_bases=(probe_cls,))
            eng.run()
            line = "%s vs %s：%s" % (a.replace("lineup_", ""),
                                     b.replace("lineup_", ""), outcome(eng))
            rows.append(line)
            if not eng.fight_ended:
                timeouts.append(line)
            if eng.hooks.activations == 0:
                zero_act.append(line)

    print("CHECK_GDCORE_ENGINE: 已跑 %d 局" % len(rows))
    if args.report:
        for r in rows:
            print("   " + r)

    fails = []
    if timeouts:
        fails.append("有 %d 局未收场：%s" % (len(timeouts), timeouts[:2]))
    if zero_act:
        fails.append("有 %d 局物品一次都没触发：%s" % (len(zero_act), zero_act[:2]))

    # ── 与 Godot 基准逐行对照 ──
    if not os.path.exists(BASELINE):
        fails.append("基准文件不存在：%s" % BASELINE)
        gd = {}
    else:
        gd = parse_rows(io.open(BASELINE, encoding="utf-8").read())
    py = parse_rows("\n".join(rows))

    common = sorted(set(gd) & set(py))
    only_gd = sorted(set(gd) - set(py))
    only_py = sorted(set(py) - set(gd))
    diff = [k for k in common if gd[k] != py[k]]

    print("基准 %d 局 / 本次 %d 局 / 可比 %d 局" % (len(gd), len(py), len(common)))
    # --limit 是调试开关，只跑子集；此时「基准有而本次无」是预期内的，不作为判据
    if not args.limit:
        if only_gd:
            fails.append("基准有而本次无的对局 %d 个：%s" % (len(only_gd), only_gd[:3]))
        if only_py:
            fails.append("本次有而基准无的对局 %d 个：%s" % (len(only_py), only_py[:3]))
    elif only_gd:
        print("  （--limit %d，另有 %d 局基准未参与比对，不作为判据）"
              % (args.limit, len(only_gd)))

    if diff:
        print("  ✗ 不一致 %d / %d 局：" % (len(diff), len(common)))
        for k in diff:
            print("    %s" % k)
            print("      基准 %s" % gd[k])
            print("      本次 %s" % py[k])
        fails.append("有 %d 局与 Godot 基准不一致" % len(diff))
    elif common:
        print("  ✓ 全部 %d 局逐字符一致"
              "（赢家 / 时长 / 双方血量 / 激活·伤害·治疗·宝石·疲劳·眩晕 计数）"
              % len(common))

    os.makedirs(os.path.dirname(OUT_PATH), exist_ok=True)
    io.open(OUT_PATH, "w", encoding="utf-8", newline="\n").write(
        "\n".join(rows) + "\n")

    if fails:
        for f in fails:
            print("CHECK_GDCORE_ENGINE: FAIL  " + f)
        print("CHECK_GDCORE_ENGINE: FAIL (%d 项)" % len(fails))
        return 1
    print("CHECK_GDCORE_ENGINE: PASS")
    return 0


if __name__ == "__main__":
    sys.exit(main())
