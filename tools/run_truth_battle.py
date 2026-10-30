#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
run_truth_battle.py — 在 Godot 无头内核里跑真值阵容复现（docs/consistency_workflow.md §3 Phase 1 / M2）

包装 gd_core_test/TruthBattle.gd：
    tools/godot_headless.run() 调 output/godot36/Godot_v3.6-stable_win64.exe
        --no-window --audio-driver Dummy --path gd_core_test --script TruthBattle.gd
        （**独立隐藏桌面**：3.6 无 --headless，--no-window 仍会出可见窗口）
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
    # ★ 2026-10-30：--headless 是 4.x 参数，3.6 写了会出真窗口并招搜狗 IME
    #   弹 "OpenMem failed"；沙箱禁匿名管道（capture_output → WinError 5）。
    #   统一走 tools/godot_headless（--no-window + 文件重定向 + APPDATA 隔离）。
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    import godot_headless as gh
    rc, out, _lp = gh.run(gh.cmd(project="gd_core_test", script=SCRIPT),
                          label="truth")
    if out:
        sys.stdout.write(out)

    for path in (RESULT, TRACE):
        if os.path.exists(path):
            print("[run_truth_battle] 产物：%s（%d 字节）"
                  % (os.path.relpath(path, ROOT), os.path.getsize(path)))
        else:
            print("[run_truth_battle] 缺产物：%s" % os.path.relpath(path, ROOT),
                  file=sys.stderr)

    print("[run_truth_battle] Godot 退出码：%d" % rc)
    return rc


if __name__ == "__main__":
    raise SystemExit(main())
