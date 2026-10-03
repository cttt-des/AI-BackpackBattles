# engine_batch — GPU 批量仿真内核（骨架）

《背包乱斗》AI 训练引擎的批量仿真层。架构与验收标准见
[docs/training_engine_architecture.md](../docs/training_engine_architecture.md)（§2 内核层、§7 里程碑）。

## 地位与边界

- **L1 仿真内核**：B 个环境 lockstep 批量推进，状态为定长张量。
- **对照物**：`engine/`（单 env 真值内核，冻结）。本目录的一切行为必须能对照
  `decompiled_full/` 行号与 `docs/engine_truth.md`；M2 验收 = 56 场回归指纹与单 env 一致。
- **不侵入** `engine/` 与 `simulator/`。

## 当前状态

骨架阶段（M0）。实现前必须完成：

1. 状态布局评审冻结（架构文档 §2.2）。
2. M0.5 框架 spike：用 `engine/` 真值内核包 vmap 式批量，实测 RTX 5080 吞吐，
   数据决定 JAX / PyTorch 绑定。
3. P0 物品 top80 清单（从回放/统计数据圈定）。

## 设计铁律（违反即返工）

1. 状态形状编译期恒定；动态集合 = 最大容量 + 存在掩码。
2. step/init 纯函数；随机性显式 PRNG key 传入，不藏状态内。
3. observation 与 internal state 分离。
4. 合法动作掩码在环境内计算并随 obs 返回。
5. terminated / truncated 显式区分，截断 bootstrap V(s)。
6. 战斗 = SMDP macro-step：定长 scan + 终止掩码，结果折叠为单转移。
7. 新行为必附 `decompiled_full/` 行号引用。

## 目录规划（实现时填充）

```
engine_batch/
├── README.md            # 本文件
├── state.py             # 状态布局（冻结后实现，定长张量结构）
├── combat.py            # 战斗 kernel（M1）
├── placement.py         # 放置 kernel（M1）
├── shop.py              # 商店 kernel（M3）
├── rng.py               # 向量化 BalancedRng / BalancedRange / 显式 key
├── behaviors/           # P0 物品行为（batched kernel，逐物品对照 engine_truth）
└── env.py               # 决策步 API + 合法掩码 + 乐观重置池 + auto-reset
```
