# -*- coding: utf-8 -*-
"""battle_simulator.py — 战斗模拟器 GUI 入口（PyInstaller 打包目标）

运行:
    python battle_simulator.py        # 开发态
    BackpackSimulator.exe             # 冻结态（lineups/ 放在 exe 同目录）
"""
import sys
import os

# 确保仓库根目录在 path 中（开发态直接运行本脚本时）
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from simulator.gui import main

if __name__ == '__main__':
    main()
