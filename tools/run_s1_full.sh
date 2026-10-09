#!/usr/bin/env bash
# 阶段1 全量流水线（神谕批量完成后执行）：
#   1) gd_core(Godot) 侧 state 注入重放 914 场（分块续跑）
#   2) gd_core_py 侧同 (阵容, seed, state) 重放
#   3) 三方逐行比对 → output/oracle/alignment_s1.json
# 全程无头；Godot 由 verify_oracle*.py 以子进程方式调用（--headless，无窗口）。
set -x
cd "D:\文件资料\学习\自动背包AI"
python -X utf8 tools/verify_oracle_s1.py > output/oracle/align/s1_full.log 2>&1
echo "S1_FULL_EXIT=$?"
