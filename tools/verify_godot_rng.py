# -*- coding: utf-8 -*-
"""校验 gd_core_py 的 RandomNumberGenerator 与 Godot 3.6 逐位一致。

基准：gd_core_test/RngProbe.gd 用本机 Godot 跑出的 gd_core_test/rng_probe.bin
     （不是从源码推断的预期值 —— 是 Godot 真实吐出的字节）。
第二段「state 注入」：基准来自 gd_core_test/RngStateProbe.gd 跑出的
     gd_core_test/rng_state_probe.bin（Godot 原生 `state` setter 注入后的原生流），
     逐 state 逐段比对本文件的 RandomNumberGenerator.state 注入路径。

用法: python tools/verify_godot_rng.py
退出码 0 = 全部段逐位一致。

★ 为什么必须逐位：randf_range 的结果会乘进冷却（`cd * randf_range(0.975,1.05)`），
  float32 尾数差 1 位就足以让某次攻击早/晚一帧，进而让整场事件序列分叉 ——
  那时双引擎对照会把「RNG 实现错了」误报成「战斗逻辑不一致」。
★ 为什么还要测 state：确定性重放要把**运行中途实测的 64 位 state** 灌进
  Python 侧从中途续跑。Godot 的 state setter 是直接赋值 `pcg.state = p_state`
  （output/godot_src/random_pcg.h:79），不前进、不重播 —— 若 Python 侧
  state setter 语义有偏（比如当成 seed 重播），中途续跑整条流立刻分叉。
"""
from __future__ import annotations

import os
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)

from gd_core_py._rt import RandomNumberGenerator  # noqa: E402

BIN = os.path.join(ROOT, "gd_core_test", "rng_probe.bin")
STATE_BIN = os.path.join(ROOT, "gd_core_test", "rng_state_probe.bin")

SEG_NAMES = [
    "randi()",
    "randf()",
    "randf_range(0.975, 1.05)",
    "randf_range(0.2, -0.2)",
    "randf_range(0.0, 100.0)",
    "randi_range(0, 99)",
    "randi_range(5, 5)",
]


def call(seg, r):
    if seg == 0:
        return float(r.randi())
    if seg == 1:
        return r.randf()
    if seg == 2:
        return r.randf_range(0.975, 1.05)
    if seg == 3:
        return r.randf_range(0.2, -0.2)
    if seg == 4:
        return r.randf_range(0.0, 100.0)
    if seg == 5:
        return float(r.randi_range(0, 99))
    return float(r.randi_range(5, 5))


def main():
    bad_seed = _verify_seed_segments()
    bad_state = _verify_state_injection()
    if bad_seed or bad_state:
        print("RNG 未对齐 —— gd_core_py 不得用于双引擎对照。")
        return 1
    return 0


def _verify_seed_segments():
    """段 0：seed 路径（基准 rng_probe.bin，RngProbe.gd 产出）。"""
    if not os.path.exists(BIN):
        print("缺少基准文件 %s —— 先跑：" % BIN)
        print("  output/godot36/Godot_v3.6-stable_win64.exe --no-window "
              "--audio-driver Dummy --path gd_core_test --script RngProbe.gd")
        return 2

    raw = open(BIN, "rb").read()
    magic, n_seeds, n_per, n_segs = struct.unpack_from("<IIII", raw, 0)
    if magic != 0x524E4731:
        print("基准文件 magic 不对：%08x" % magic)
        return 2
    seeds = list(struct.unpack_from("<%dq" % n_seeds, raw, 16))
    off = 16 + 8 * n_seeds
    vals = list(struct.unpack_from("<%dd" % (n_seeds * n_segs * n_per), raw, off))

    print("基准：%d 个种子 × %d 段 × %d 个值" % (n_seeds, n_segs, n_per))
    print("       seeds = %s\n" % seeds)

    bad = 0
    checked = 0
    for si in range(n_segs):
        seg_bad = []
        for i, s in enumerate(seeds):
            r = RandomNumberGenerator()
            r.seed = s
            base = (i * n_segs + si) * n_per
            for k in range(n_per):
                want = vals[base + k]
                got = call(si, r)
                checked += 1
                if got != want:
                    seg_bad.append((s, k, want, got))
        status = "ok  " if not seg_bad else "FAIL"
        print("  [%s] 段%d  %-26s 全等 %d/%d" %
              (status, si, SEG_NAMES[si], n_per * n_seeds - len(seg_bad),
               n_per * n_seeds))
        for s, k, want, got in seg_bad[:4]:
            print("         seed=%d idx=%d\n           期待 %.17g\n           实得 %.17g"
                  % (s, k, want, got))
            if si in (0, 5, 6):
                print("           （整数段按 bit 比较：期待 %d / 实得 %d）"
                      % (int(want), int(got)))
        bad += len(seg_bad)

    print("\n[seed 路径] 共比对 %d 个值，不一致 %d 个。" % (checked, bad))
    if bad:
        return 1
    print("RNGPROBE: seed 路径与 Godot 3.6 逐位一致。")
    return 0


def _verify_state_injection():
    """段 1：state 注入路径（基准 rng_state_probe.bin，RngStateProbe.gd 产出）。

    基准流是 Godot 原生侧的输出：对每个 state，原生 RandomNumberGenerator
    注入 state 后逐段跑 N 步。本侧用同一组 state 注入 Python 版
    RandomNumberGenerator.state，逐位比对 —— 对齐点是 random_pcg.h:79
    `RandomPCG::set_state` = `pcg.state = p_state`（不前进、不重播）。
    """
    if not os.path.exists(STATE_BIN):
        print("\n缺少 state 注入基准 %s —— 先跑：" % STATE_BIN)
        print("  output/godot36/Godot_v3.6-stable_win64.exe --headless "
              "--path gd_core_test --script RngStateProbe.gd")
        return 2

    raw = open(STATE_BIN, "rb").read()
    magic, n_states, n_per, n_segs = struct.unpack_from("<IIII", raw, 0)
    if magic != 0x524E4732:
        print("state 基准文件 magic 不对：%08x" % magic)
        return 2
    states = list(struct.unpack_from("<%dq" % n_states, raw, 16))
    off = 16 + 8 * n_states
    vals = list(struct.unpack_from("<%dd" % (n_states * n_segs * n_per), raw, off))

    print("\n[state 注入] 基准：%d 个 state × %d 段 × %d 个值"
          % (n_states, n_segs, n_per))
    print("       states = %s\n" % states)

    bad = 0
    checked = 0
    r = RandomNumberGenerator()
    for i, s in enumerate(states):
        for si in range(n_segs):
            # 每段都从同一 state 重新注入，段间独立（对齐探针的段隔离）
            r.state = s
            base = (i * n_segs + si) * n_per
            for k in range(n_per):
                want = vals[base + k]
                got = call(si, r)
                checked += 1
                if got != want:
                    bad += 1
                    if bad <= 4:
                        print("  FAIL state=%d 段%d idx=%d\n"
                              "         期待 %.17g\n         实得 %.17g"
                              % (s, si, k, want, got))

    print("  共比对 %d 个值，不一致 %d 个。" % (checked, bad))
    if bad:
        return 1
    print("RNGSTATEPROBE: state 注入路径与 Godot 3.6 逐位一致。")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
