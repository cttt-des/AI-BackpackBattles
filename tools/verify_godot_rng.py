# -*- coding: utf-8 -*-
"""校验 gd_core_py 的 RandomNumberGenerator 与 Godot 3.6 逐位一致。

基准：gd_core_test/RngProbe.gd 用本机 Godot 跑出的 gd_core_test/rng_probe.bin
     （不是从源码推断的预期值 —— 是 Godot 真实吐出的字节）。

用法: python tools/verify_godot_rng.py
退出码 0 = 全部段逐位一致。

★ 为什么必须逐位：randf_range 的结果会乘进冷却（`cd * randf_range(0.975,1.05)`），
  float32 尾数差 1 位就足以让某次攻击早/晚一帧，进而让整场事件序列分叉 ——
  那时双引擎对照会把「RNG 实现错了」误报成「战斗逻辑不一致」。
"""
from __future__ import annotations

import os
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)

from gd_core_py._rt import RandomNumberGenerator  # noqa: E402

BIN = os.path.join(ROOT, "gd_core_test", "rng_probe.bin")

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

    print("\n共比对 %d 个值，不一致 %d 个。" % (checked, bad))
    if bad:
        print("RNG 未对齐 —— gd_core_py 不得用于双引擎对照。")
        return 1
    print("RNGPROBE: 与 Godot 3.6 逐位一致。")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
