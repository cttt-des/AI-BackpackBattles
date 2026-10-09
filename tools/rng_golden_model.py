#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""rng_golden_model.py — Godot 3.6 PCG32 黄金模型：从 rng_state.txt 前向复算
神谕 rng_log 的每一抽，自动探测「未记日志的消耗」（randPitch 等直调
rng.randf_range 的调用点在 oracle 里不走 rng_trace_* 包装）。

模型依据（output/godot_src/ 节选）：
  pcg32_random_r（pcg.cpp:6-15）：oldstate 输出，state = old*M + inc；
  randf（random_pcg.h:113-120，CLZ32 路径）：2 抽常态（proto_exp_offset==0 早退 1 抽）；
  randf_range（random_pcg.cpp:45-47 float 重载）= randf()*(to-from)+from；
  randi_range（random_number_generator.h:64-70）= rand() % (to-from+1) + from，1 抽。
"""
from __future__ import annotations

import io
import math
import struct
import sys

MASK = (1 << 64) - 1
MULT = 6364136223846793005
INC = 2885390081777926815


def _f32(x: float) -> float:
    """C float（32 位）舍入。"""
    return struct.unpack('f', struct.pack('f', x))[0]


class PCG:
    def __init__(self, state: int):
        self.state = state & MASK

    def rand(self) -> int:
        old = self.state
        self.state = (old * MULT + INC) & MASK
        xorshifted = (((old >> 18) ^ old) >> 27) & 0xFFFFFFFF
        rot = (old >> 59) & 31
        return ((xorshifted >> rot) | (xorshifted << ((32 - rot) & 31))) & 0xFFFFFFFF

    def randf(self) -> float:
        proto = self.rand()
        if proto == 0:
            return 0.0
        significand = self.rand() | 0x80000001
        clz = 32 - proto.bit_length()
        # C++ LDEXPF → float32 舍入（real_t = float）
        return _f32(math.ldexp(float(significand), -32 - clz))

    def randf_range(self, frm: float, to: float) -> float:
        # float 重载：randf()*(to-from)+from（float32 全程，逐_op 舍入）
        prod = _f32(self.randf() * _f32(to - frm))
        return _f32(prod + _f32(frm))

    def randi_range(self, frm: int, to: int) -> int:
        r = self.rand()
        if to < frm:
            return r % (frm - to + 1) + to
        return r % (to - frm + 1) + frm


def read_state(path: str) -> int:
    for ln in io.open(path, encoding="utf-8", errors="replace"):
        ln = ln.strip()
        if ln.startswith("state="):
            return int(ln[6:]) & MASK
    raise RuntimeError("state= not found in %s" % path)


def load_log(path: str, offset: int = 0):
    rows = []
    for ln in io.open(path, encoding="utf-8", errors="replace"):
        ln = ln.strip()
        if not ln:
            continue
        left, rest = ln.split("=>")
        val = float(rest.split("@")[0].strip())
        p = left.split()
        rows.append((p[1], float(p[2]), float(p[3]), val))
    return rows[offset:]


def main() -> int:
    state_path = sys.argv[1]
    log_path = sys.argv[2]
    offset = int(sys.argv[3]) if len(sys.argv) > 3 else 0
    pcg = PCG(read_state(state_path))
    rows = load_log(log_path, offset)
    print("simulating %d logged draws from state" % len(rows))
    gaps = []
    i = 0
    for idx, (kind, a, b, val) in enumerate(rows):
        # 先按「无未记消耗」复算
        if kind == "randf_range":
            got = pcg.randf_range(a, b)
            steps = 2
        elif kind == "randi_range":
            got = float(pcg.randi_range(int(a), int(b)))
            steps = 1
        elif kind == "randf":
            got = pcg.randf()
            steps = 2
        else:
            raise RuntimeError(kind)
        if abs(got - val) <= abs(val) * 1e-6 + 1e-9:
            continue
        # 值不匹配 → 尝试插入 unlogged 抽（2 步 randf 族 / 1 步 randi），k≤8
        fixed = False
        for extra_kind, extra_steps in (("randf_range", 2), ("randi", 1), ("randf", 2)):
            for k in range(1, 9):
                # 回滚：记下当前 state，重放 k 次 unlogged 再复算本抽
                saved = pcg.state
                ok = True
                for _ in range(k):
                    if extra_kind == "randi":
                        pcg.rand()
                    else:
                        pcg.randf()
                if kind == "randf_range":
                    got2 = pcg.randf_range(a, b)
                elif kind == "randi_range":
                    got2 = float(pcg.randi_range(int(a), int(b)))
                else:
                    got2 = pcg.randf()
                if abs(got2 - val) <= abs(val) * 1e-6 + 1e-9:
                    gaps.append((idx, k * extra_steps, extra_kind))
                    fixed = True
                    break
                pcg.state = saved
            if fixed:
                break
        if not fixed:
            print("D[%4d] UNRESOLVED %s %s %s => log=%s model=%s"
                  % (idx, kind, a, b, val, got))
            return 1
    print("all draws resolved; unlogged-gap insertions:")
    for idx, steps, kind in gaps:
        print("  before logged draw #%d: %d PCG steps (%s family)"
              % (idx, steps, kind))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
