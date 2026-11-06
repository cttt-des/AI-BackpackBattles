#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""check_godot_launch.py — 扫出「绕过 tools/godot_headless.py 自己起 Godot」的脚本。

为什么需要这个检查（2026-11-02 实证）：
  绕过 gh 直接 subprocess 起 Godot 会同时丢掉三样东西：
    1. startupinfo（SW_HIDE）→ **窗口直接弹到屏幕上**。oracle 项目窗口是
       1920x1080，用户看到的就是「全屏 Godot 窗口」；
    2. 隐藏桌面 / APPDATA 隔离 → user:// 互踩、IME 弹窗无人压制；
    3. 文件重定向（沙箱禁匿名管道，capture_output 会 WinError 5）。
  而且历史脚本还爱写 --headless —— Godot 3.6 **没有这个参数**，写了等于走普通
  窗口路径，比不写更糟（看起来像在无头跑，实则照样出窗）。

实测对照（同一台机器）：
  · 裸 Popen 起一个会弹 MessageBox 的宿主 → 弹窗可见（曾可见=YES）
  · 走 gh.spawn 的同一个宿主        → 弹窗 0 次可见（被 SW_HIDE/看门狗按住）

用法：
    python -X utf8 tools/check_godot_launch.py          # 扫全仓，有违规就 rc=1
    python -X utf8 tools/check_godot_launch.py --all    # 连 output/ 下的历史脚本一起扫
退出码：0=干净；1=发现绕过 gh 的启动点。
"""
import argparse
import io
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

#: 判定「这行在起 Godot」的特征
GODOT_SIGNS = (
    'Godot_v3.',
    'godot36',
    "Godot_v3.6-stable_win64.exe",
)
#: 出现这些参数说明调用方知道要静音（但仍需经 gh 才有 SW_HIDE）
QUIET_ARGS = ('--no-window', '--audio-driver')
BAD_ARGS = ('--headless',)   # 3.6 不存在此参数


def scan(paths):
    """只把「真的会起进程」的代码算进来；注释/文档字符串里提到这些词不算。"""
    issues = []
    for p in paths:
        if os.path.basename(p) == 'godot_headless.py':
            continue   # 唯一允许直接拼 Godot 路径的地方
        try:
            text = io.open(p, encoding='utf-8', errors='replace').read()
        except OSError:
            continue
        lines = text.splitlines()
        # 只认**带引号的**命令行参数，避免把注释里「不要写 --headless」当违规
        has_exe_literal = bool(re.search(r"['\"][^'\"]*Godot_v3\.[^'\"]*['\"]", text))
        headless_literal = bool(re.search(r"['\"]--headless['\"]", text))
        uses_gh = 'godot_headless' in text or 'gh.spawn' in text or 'gh.run' in text

        # 真启动点：subprocess 调用 + （Godot 路径字面量 或 变量 GODOT/GODOT_ARGS）
        launch_lines = []
        for i, ln in enumerate(lines, 1):
            if ln.lstrip().startswith('#'):
                continue
            if re.search(r'subprocess\.(Popen|run)\(', ln) or re.search(r'\b(Popen|py_popen)\(', ln):
                window = '\n'.join(lines[i - 1:i + 8])
                # 只认 Godot 引擎本体：可执行文件名/目录名，别把 GH（GitHub CLI）算进来
                if ('Godot_v3' in window or 'godot36' in window
                        or re.search(r'\bGODOT\b', window) or 'godot_headless' in window):
                    launch_lines.append((i, window))

        if launch_lines and not uses_gh:
            issues.append((p, 'L%d' % launch_lines[0][0],
                           '起 Godot 没走 godot_headless（窗口会露到屏幕）'))
            continue

        for i, window in launch_lines:
            if 'startupinfo' not in window and 'py_popen' not in window \
                    and 'godot_headless' not in window and 'gh.' not in window:
                issues.append((p, 'L%d' % i,
                               '起进程没带 startupinfo（窗口会露到屏幕）'))

        # 带引号的 --headless 字面量：3.6 不存在该参数，写了等于没静音
        if has_exe_literal and headless_literal and launch_lines:
            issues.append((p, 'L', '命令行里用了 --headless（3.6 不认）'))
    return issues

def main() -> int:
    ap = argparse.ArgumentParser(description='检查是否有脚本绕过 gh 启动 Godot')
    ap.add_argument('--all', action='store_true',
                    help='连 output/ 下的历史脚本一起扫（默认跳过 output/）')
    args = ap.parse_args()

    targets = []
    for root, dirs, files in os.walk(ROOT):
        rel = os.path.relpath(root, ROOT)
        if rel != '.' and (rel.startswith('.git') or '__pycache__' in rel):
            continue
        if not args.all and (rel == 'output' or rel.startswith('output' + os.sep)):
            continue
        for f in files:
            if f.endswith('.py'):
                targets.append(os.path.join(root, f))

    issues = scan(targets)
    if not issues:
        print('OK：%d 个脚本，未发现绕过 godot_headless 的启动点' % len(targets))
        return 0

    print('发现 %d 处绕过 godot_headless 的 Godot 启动：' % len(issues))
    for p, where, why in issues:
        print('  %s %s:%s  %s' % ('[X]', os.path.relpath(p, ROOT), where, why))
    print()
    print('统一入口（无窗口、无弹窗、日志自动落盘）：')
    print('  python -X utf8 tools/run_godot_script.py <script.gd> [--project P] [--env K=V]')
    print('批量/并行请用 gh.run_many(...max_parallel=N)，不要自己拼 Popen。')
    return 1


if __name__ == '__main__':
    sys.exit(main())