# -*- coding: utf-8 -*-
"""kernel_reset.py — gd_core_py 内核进程级全局态的逐局重置（ai 侧使用点修复）

【2026-10-03 更新】两处全局态已在 gd_core_py 内根治（本文件当年定位）：
`_rt._bind_battle(seed)` 由 CoreContext._init 在每局装配最早期调用，全局
Math 流改为随实例 seed 的实例级 RNG、get_instance_id() 台账改为本局专属
（gd_core_py/_rt.py 的 `_MATH_BIND` / `_GID_CUR`）。reset_kernel_state()
保留为冗余保险（清的只是无 ctx 回落路径的全局对象），逐局重置后与不重置
逐条一致（ai/tests/test_kernel_reset.py::test_no_reset_raw_determinism 守
护裸路径）。
★ 但该修复**不保持参战路径的行为**：Math 流起点由恒 `DEFAULT_SEED` 变为
  本局 seed、gid 序列由跨局累积变为逐局从 1 起步，都直接进入战斗随机消费
  序列——同 (阵容, seed) 的结局修复前后可翻转（实测 25 个可测局中 2 局，
  修复前后引擎数字不可比）。『reset≡不重置』说的只是修复后内核的进程内
  确定性，不是行为保持；详见 ai/kernel_fix_behavior_change.md。

背景（2026-10-03 复核确认的缺陷，本轮 eval_report 复现）
========================================================
gd_core_py 是 Godot 的机械转写，带两个**进程级全局**，局间从不重置：

1. `_rt._MATH_RNG`（gd_core_py/_rt.py:611-627）：物品脚本里裸 `arr.shuffle()`
   走的 Godot 全局 Math RNG（`_rt._shuffle`，_rt.py:597-608）。实测
   CombatLog_20261001_221121_R19_Loss 一局被抽 16 次；下次取用时若无残留才
   重新落到 `RandomNumberGenerator.DEFAULT_SEED`（即全新进程初值）。
2. `_rt._GID_MAP/_GID_NEXT/_GID_KEEP`（gd_core_py/_rt.py:670-690）：
   `get_instance_id()` 的进程级单调计数器，随历史只增不减；_GID_KEEP 还
   持有**全部历史局对象**的强引用（内存无界增长）。

实测后果（修复前，CombatLog_20261001_221121_R19_Loss 原阵容）：
  * 同进程 seed=101 连跑 6 次全新构造 → [1,1,0,1,1,1]——同一 (输入,seed)
    在同进程内三种结局，『(输入,seed)→胜负』不成立；
  * 全新进程 seeds 101..110 → 9/10；同进程先跑组1 的 10 局再跑组2 →
    逐 seed 模式又不同（三种历史三个结果）；
  * 相位矩阵（先跑 n 局热身再跑目标局，n=0..5）→ [1,0,1,1,1,1]，
    漂移随进程历史走。
于是 eval.py 的『同 seed 配对、配对减方差』前提失效（先跑完 orig 再跑 ai
的两侧进程历史不同），gen_dataset.py 的 2-seed 胜负标签同样带此噪声。

修复口径（不改 gd_core_py / simulator 现有代码，在使用点重置）
==============================================================
每局引擎使用（构造或构造+run）之前调用 `reset_kernel_state()`：
  * 先 `gc.collect()`——把上一局对象真正释放，避免清空 _GID_KEEP 后
    CPython 复用旧 id() 造成实例 id 语义错乱；
  * 清 `_MATH_RNG`——下次取用回到 DEFAULT_SEED（= 全新进程初值）；
  * 归零 `_GID_MAP/_GID_NEXT/_GID_KEEP`——gids 回到全新进程初值，
    并顺带修掉历史局对象的无界滞留。
刻意**不动** `simulator.gd_core_engine._DESCR_CACHE`：描述符跨局同身份是
适配层刻意维持的语义（`Item.isA` 靠引用相等判定、描述符被当字典键，见
simulator/gd_core_engine.py 文件头与 :547），清它反而破坏设计不变量。

重置后的确定性证据（ai/tests/test_kernel_reset.py，本轮实测）：
  * 同进程同 seed 同阵容连跑多次 → 逐局一致；
  * 『先跑别的局再跑目标局』（异阵容热身、多 seed 热身）→ 与净进程一致；
  * 换 PYTHONHASHSEED 的全新子进程彼此一致（排除跨进程哈希序因素）。
"""
from __future__ import annotations

import gc

import gd_core_py._rt as _rt


def reset_kernel_state() -> None:
    """把 gd_core_py 的进程级全局态清回『全新进程』初值。

    必须在**每局**引擎构造之前调用（含只构造不 run 的装配探针）。
    直接引用 _rt 内部名：gd_core_py 内部名变化时应立即炸出来，而不是
    静默漏清某一项继续带历史噪声。
    """
    gc.collect()                      # 先释放上一局对象，再动 id 台账
    _rt._MATH_RNG.clear()             # 裸 arr.shuffle() 的全局流 → DEFAULT_SEED
    _rt._GID_MAP.clear()
    _rt._GID_NEXT[0] = 1
    _rt._GID_KEEP.clear()
