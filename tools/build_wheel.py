# -*- coding: utf-8 -*-
"""build_wheel.py — 构建可分发的 wheel（含 664 个 .pyd）。

为什么需要：pyd 是**构建产物**（与 cp314-win_amd64 ABI 绑定，84MB），不适合进 git；
但只发 GUI exe 又满足不了「用模拟器训练 AI」的需求——训练要的是可 import 的编程接口。
wheel 满足两者：pip 安装即得编译态内核 + 数据 + 示例阵容。

用法：
    python -X utf8 tools/build_wheel.py              # 检查 pyd 齐全后构建
    python -X utf8 tools/build_wheel.py --no-cython  # 跳过编译（复用现有 pyd）

产物：dist/backpack_battles_sim-<ver>-cp314-cp314-win_amd64.whl
"""
from __future__ import annotations

import argparse
import glob
import os
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DIST = os.path.join(ROOT, "dist")


def _count(ext: str) -> int:
    n = 0
    for d, _, fs in os.walk(os.path.join(ROOT, "gd_core_py")):
        n += sum(1 for f in fs if f.endswith(ext))
    return n


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--no-cython", action="store_true",
                    help="跳过 Cython 全量重编，直接用现有 .pyd")
    a = ap.parse_args()

    py, pyd = _count(".py"), _count(".pyd")
    print("[wheel] 源码 %d 个 .py / 现有 %d 个 .pyd" % (py, pyd))
    expect = py - 9          # 9 个非热模块（__init__/_bootstrap/_registry/_colors）不编
    if pyd < expect:
        msg = "[wheel] .pyd 不足（%d < %d）" % (pyd, expect)
        if a.no_cython:
            print(msg + "，继续构建（部分模块为纯 Python 腿）")
        else:
            print(msg + "，请先跑 python -X utf8 tools/build_cython.py --list ... 全量编译")
            return 2

    env = dict(os.environ)
    env["PYTHONUTF8"] = "1"
    cmd = [sys.executable, "-m", "pip", "wheel", ".", "--no-deps",
           "--no-build-isolation", "-w", DIST]
    print("[wheel] " + " ".join(cmd))
    r = subprocess.run(cmd, cwd=ROOT, env=env)
    if r.returncode != 0:
        print("[wheel] BUILD FAILED rc=%d" % r.returncode)
        return r.returncode

    whls = sorted(glob.glob(os.path.join(DIST, "backpack_battles_sim-*.whl")))
    if not whls:
        print("[wheel] 未找到 wheel 产物")
        return 1
    w = whls[-1]
    size = os.path.getsize(w) / 1048576.0
    print("=" * 60)
    print("WHEEL OK: %s  (%.1f MB)" % (w, size))
    print("install:  pip install " + os.path.basename(w))
    print("=" * 60)
    return 0


if __name__ == "__main__":
    sys.exit(main())
