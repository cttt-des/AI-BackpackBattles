#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
run_truth_battle.py — 在 Godot 无头内核里跑真值阵容复现（docs/consistency_workflow.md §3 Phase 1 / M2）

包装 gd_core_test/TruthBattle.gd：
    subprocess 调 output/godot36/Godot_v3.6-stable_win64.exe
        --headless --path gd_core_test --script TruthBattle.gd
透传 Godot 的 stdout/stderr 与退出码。TruthBattle.gd 自己落两个产物：
    gd_core_test/truth_result.txt —— HookProbe 计数 + 结果摘要
    gd_core_test/truth_trace.txt  —— 逐事件轨迹（t|id|type|depth|origin|target|params，
                                     含每次 DK 攻击的时间戳）

用法：
    python -X utf8 tools/run_truth_battle.py
退出码：Godot 进程退出码（0 = 跑通且轨迹非空）。
"""
from __future__ import annotations

import os
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GODOT = os.path.join(ROOT, "output", "godot36", "Godot_v3.6-stable_win64.exe")
PROJECT = os.path.join(ROOT, "gd_core_test")
SCRIPT = "TruthBattle.gd"
TRACE = os.path.join(PROJECT, "truth_trace.txt")
RESULT = os.path.join(PROJECT, "truth_result.txt")


def main() -> int:
    if not os.path.exists(GODOT):
        print("找不到 Godot：%s" % GODOT, file=sys.stderr)
        return 2
    cmd = [GODOT, "--headless", "--path", PROJECT, "--script", SCRIPT]
    proc = subprocess.run(cmd, capture_output=True, text=True,
                          encoding="utf-8", errors="replace", cwd=ROOT)
    # 透传输出
    if proc.stdout:
        sys.stdout.write(proc.stdout)
    if proc.stderr:
        sys.stderr.write(proc.stderr)

    for path in (RESULT, TRACE):
        if os.path.exists(path):
            print("[run_truth_battle] 产物：%s（%d 字节）"
                  % (os.path.relpath(path, ROOT), os.path.getsize(path)))
        else:
            print("[run_truth_battle] 缺产物：%s" % os.path.relpath(path, ROOT),
                  file=sys.stderr)

    print("[run_truth_battle] Godot 退出码：%d" % proc.returncode)
    return proc.returncode


if __name__ == "__main__":
    raise SystemExit(main())
