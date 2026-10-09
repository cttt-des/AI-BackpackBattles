# 受控神谕（Controlled Oracle）工作流 — 模拟器与原版引擎 100% 一致

> 目标：用反编译源码编译出一个**受控 Godot 程序**（只保留历史记录 + 战斗功能），
> 以拷贝的 history.db 为数据源、由我们完全控制的 rng 种子跑历史对战，
> 作为"真值神谕"对模拟器做逐事件校对，修复分歧直到 **gd_core_py ≡ 神谕 逐位一致**。
> 生成日期：2026-10-05。取代前一代"活体捕获"方案（本方案全自动后台运行，不抢占前台）。

---

## 0. 为什么这个方案更优

| 维度 | 活体捕获（旧方案） | 受控神谕（本方案） |
|------|-------------------|-------------------|
| 前台占用 | 抢焦点/鼠标点击，干扰使用 | **全程无头后台**，零干扰 |
| rng 种子 | 只能从内存捕获"战斗开始时刻的 state"（有捕获窗口风险） | **我们完全控制种子**——任意 (阵容, seed) 对皆可复现 |
| 覆盖面 | 只能打历史里真实出现过的对局 | 历史对局全量（1001 runs × 各回合）× 任意种子 |
| 红线安全 | 靠点击纪律 | **物理不可能进排名/休闲**——主游戏场景/在线模式入口根本不加载 |
| 对 Steam 版 | 只读内存 | **零接触**：只拷贝 history.db 快照，且前后校验和证明未修改 |

神谕的合法性：它 = Godot 3.6 引擎 + **运行版（1.1.8）反编译出的原版脚本**
（`extracted_running/decomp/` 的 Item.gd/Character.gd/Combat.gd/Buff.gd/CombatLog.gd 原文件），
即"通过反编译得到的源码修复后进行编译"的原版引擎本体，只是剥掉了 UI 与在线入口。

## 1. 随机性前提（已核实，见 docs/rng_truth.md）

单一全局 `Util.rng`（PCG32），一切 roll 消费同一链，`BalancedRng.reset()` 不重播种。
⇒ **神谕在开战前设 `Util.rng.seed = S`（我们选的确定性种子）后，整场战斗完全由
(S, 双方阵容, 初始 HP/体力/回合) 决定**。gd_core/gd_core_py 用同一 S 重放即应逐位一致。

## 2. 阶段

### Phase 1 — 冻结现场与拷贝
- **Steam 完整性基线**：记录 `Backpack Battles/` 下 `BackpackBattles.pck`、`history.db` 等
  全部文件 MD5 → `output/oracle/steam_baseline.json`（工作流结束时复核，证明零修改）
- 拷贝 `extracted_running/decomp/` → `oracle/`（工作副本，随意改）
- 拷贝 Steam `history.db` → `oracle/data/history.db`（只读快照）
- 交付：`tools/prepare_oracle.py`（幂等，world.run 闸门）

### Phase 2 — 神谕脚本与无头调通（迭代闸门）
- `oracle/oracle_fight.gd`（SceneTree 脚本，仿 gd_core_test/LineupBattle.gd 的宿主方式）：
  1. 读 `oracle/fight_config.json`（seed / runID / roundID / 输出路径）
  2. 从拷贝的 history.db 经**原版 RunDatabase/BuildHistoryData.deserializeRound** 装配双方阵容
     （原版反序列化路径 = 零失真）
  3. `Util.rng.seed = S` → 装配 → 跑原版战斗 tick 到判胜
  4. 原版 CombatLog.events 全量 dump（JSON）+ 双方阵容快照
- 无头迭代：`Godot --headless --path oracle --script oracle_fight.gd` → 修到跑通
  （预期问题：autoload 的场景引用/Steam 初始化/网络单例——按需桩化，SteamHelper 走无 Steam 分支）
- **红线硬保证**：不加载主游戏场景（Main.tscn 不进场景树），排名/休闲入口在神谕里不存在；
  脚本内注释与断言写明"本程序永不进入在线模式"
- 退出标准：≥1 场战斗自然结束、事件 dump 非空、同 seed 重跑逐位一致

### Phase 3 — 三方逐位对齐
- 神谕输出双方阵容 → `tools/gen_fixture_from_lineup.py` 生成 gd_core fixture
- 三方同 (阵容, seed)：
  - 神谕(Godot 1.1.8 原版脚本) ↔ gd_core(Godot 移植) ↔ gd_core_py(Python 移植)
- canonical_events.py 逐事件 diff → 分歧点定位（数据/内核移植/转写）
- 选材：DK 场次（run 1548/1556 回合 18，终审黏黏龙骑士）+ 多样性场次（不同 run/回合，覆盖不同机制）

### Phase 4 — 修复循环（有界 ≤4 轮）
- 按分歧定位修 gd_core_py / gd_core / gd_core_runtime.json
- 每轮重跑三方对齐：对齐场数递增、已对齐场不退步
- Godot 侧改动跑 LineupBattle 回归防破坏

### Phase 5 — 回归固化与报告
- `tools/verify_oracle.py`：批量 (阵容, seed) 用例，gd_core_py vs 神谕逐位比对
- Steam 完整性复核（基线 MD5 全等）
- 报告：对齐场数、分歧清单、终审结论

## 3. 一致性的最终定义（本工作流的验收）

gd_core_py 对任意一组 (历史阵容对, 种子)，与受控神谕（原版引擎 + 原版脚本）的
事件流**逐位一致**——由于种子受控，这是可无限采样、可精确断言的"完全一致"，
且神谕运行原版脚本与原版 CombatLog，即用户要求的"模拟器与原版游戏引擎完全一致"。

## 4. 风险与对策

| 风险 | 对策 |
|------|------|
| 反编译工程无头跑不起来（autoload 场景引用缺失等） | Phase 2 有界迭代；桩化按"最小侵入"原则且全部记录在案；Plan B = 加载 Main.tscn 但程序化驱动 |
| Steam 初始化在无 Steam 环境崩溃 | SteamHelper 源码有无 Steam 分支；必要时桩化（记录在案） |
| 历史对战装配路径依赖 UI 节点 | 用原版反序列化 + Inventory 装配（gd_core_test 已验证该路径可行性），绕开 UI |
| 神谕与 gd_core 版本差（1.1.8 vs 1.1.7 移植基底） | 战斗逻辑两版 diff 极小（已核实）；若遇差异以神谕（1.1.8）为准修 gd_core |
| 修改 Steam 版文件 | 禁令 + 前后 MD5 基线复核（Phase 1/5） |
