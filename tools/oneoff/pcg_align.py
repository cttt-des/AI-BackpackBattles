# -*- coding: utf-8 -*-
"""读 rng_probe.bin 并尝试对齐 Godot 3.6 的 RandomNumberGenerator。

思路：不靠记忆猜实现，而是把 Godot 的真实输出当约束，枚举候选 PCG 变体，
用「前 K 个 randi 全等」筛选出唯一实现，再用 randf/randf_range 段验证。
"""
import os
import struct
import sys

sys.stdout.reconfigure(encoding="utf-8")
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PATH = os.path.join(ROOT, "gd_core_test", "rng_probe.bin")

raw = open(PATH, "rb").read()
magic, n_seeds, n_per, n_segs = struct.unpack_from("<IIII", raw, 0)
assert magic == 0x524E4731, hex(magic)
seeds = list(struct.unpack_from("<%dq" % n_seeds, raw, 16))
off = 16 + 8 * n_seeds
vals = list(struct.unpack_from("<%dd" % (n_seeds * n_segs * n_per), raw, off))


def seg(si, seed_i):
    base = (seed_i * n_segs + si) * n_per
    return vals[base:base + n_per]


print("seeds =", seeds, " n_per =", n_per, " n_segs =", n_segs)
print("\n── 段 0: randi() 前 6 个 ──")
for i, s in enumerate(seeds):
    print("  seed=%-12d %s" % (s, [int(x) for x in seg(0, i)[:6]]))
print("\n── 段 1: randf() 前 6 个 ──")
for i, s in enumerate(seeds):
    print("  seed=%-12d %s" % (s, ["%.17g" % x for x in seg(1, i)[:4]]))
print("\n── 段 5: randi_range(0,99) 前 8 个 ──")
for i, s in enumerate(seeds):
    print("  seed=%-12d %s" % (s, [int(x) for x in seg(5, i)[:8]]))
print("\n── 段 6: randi_range(5,5) 前 3 个（min==max 边界）──")
for i, s in enumerate(seeds):
    print("  seed=%-12d %s" % (s, [int(x) for x in seg(6, i)[:3]]))

MASK64 = (1 << 64) - 1
MULT = 6364136223846793005
DEFAULT_INC = 1442695040888963407      # PCG_DEFAULT_INCREMENT_64
DEFAULT_SEED = 0x853C49E6748FEA9B


def pcg_out(state):
    xorshifted = (((state >> 18) ^ state) >> 27) & 0xFFFFFFFF
    rot = (state >> 59) & 31
    return ((xorshifted >> rot) | (xorshifted << ((-rot) & 31))) & 0xFFFFFFFF


class Cand:
    """一个候选实现：给出 seed → 前 N 个 rand() 输出 + 其 randf 定义。"""

    def __init__(self, name, init, randf_mode="u32max"):
        self.name = name
        self.init = init
        self.randf_mode = randf_mode

    def seq(self, s, n):
        st, inc = self.init(s)
        out = []
        for _ in range(n):
            st = (st * MULT + inc) & MASK64
            out.append(pcg_out(st))
        return out


def f32(x):
    return struct.unpack("<f", struct.pack("<f", x))[0]


CANDS = []


def add(name, init, randf_mode="u32max"):
    CANDS.append(Cand(name, init, randf_mode))


add("S0: st=seed,inc=D", lambda s: (s, DEFAULT_INC))
add("S1: st=seed+D,inc=D", lambda s: ((s + DEFAULT_INC) & MASK64, DEFAULT_INC))
add("S2: st=(seed*MULT+D)+D,inc=D",
    lambda s: (((s + DEFAULT_INC) & MASK64 * 1) , DEFAULT_INC))


def _s2(s):
    st = (s * MULT + DEFAULT_INC) & MASK64
    st = (st * MULT + DEFAULT_INC) & MASK64
    return (st, DEFAULT_INC)


add("S2: st=两次推进后,inc=D", _s2)


def _s3(s):
    # 标准 PCG 播种：state=0, inc=(seed<<1)|1 ... 但 Godot 用固定 inc
    st = (s + DEFAULT_INC) & MASK64
    st = (st * MULT + DEFAULT_INC) & MASK64
    return (st, DEFAULT_INC)


add("S3", _s3)
add("S4: st=seed,inc=D|1", lambda s: (s, DEFAULT_INC | 1))
add("S5: st=seed|1,inc=D", lambda s: (s | 1, DEFAULT_INC))
add("S6: inc=(seed<<1)|1,st=seed",
    lambda s: ((s + ((s << 1) | 1)) & MASK64, (s << 1) | 1))


def _s7(s):
    inc = ((s << 1) | 1) & MASK64
    st = (s + inc) & MASK64
    st = (st * MULT + inc) & MASK64
    st = (st + s) & MASK64
    st = (st * MULT + inc) & MASK64
    return (st, inc)


add("S7: 标准PCG播种(inc=(s<<1)|1)", _s7)

K = 6
print("\n══ 候选实现对齐（比较前 %d 个 randi）══" % K)
targets = {seeds[i]: [int(x) for x in seg(0, i)[:K]] for i in range(n_seeds)}
for c in CANDS:
    ok = 0
    heads = []
    for s in seeds:
        got = c.seq(s, K)
        heads.append(got[0])
        if got == targets[s]:
            ok += 1
    print("  %-34s 全等 seeds=%d/%d   首值=%s" % (c.name, ok, n_seeds, heads))
print("\n  实测首值 =", [targets[s][0] for s in seeds])
print("  实测前3 =", {s: targets[s][:3] for s in seeds[:2]})
