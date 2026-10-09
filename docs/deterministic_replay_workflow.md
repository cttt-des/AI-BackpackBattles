# L3 确定性重放工作流 — 模拟器与原版 100% 一致

> 目标：**同一场对战、同一 rng 状态、同一阵容 → 模拟器与原版逐事件 100% 一致**。
> 本文档是 docs/consistency_workflow.md L3 层的落地设计。
> 生成日期：2026-10-04

---

## 0. 随机性真值（已源码核实，本工作流的立足点）

| 事实 | 源码依据 | 推论 |
|------|----------|------|
| 全游戏**单一全局 rng**：`Util.rng = RandomNumberGenerator.new()` | Util.gd:6 | 没有独立的 per-item 种子链 |
| `randomize()` 只在 Util._ready（游戏启动）调用一次 | Util.gd:76-77 | 启动后 rng 是一条确定的 PCG32 状态链 |
| 一切随机最终走 `Util.flip` = `rng.randf() <= chance` | Util.gd:1010-1011 | 命中/暴击/概率触发/伤害区间全部消费同一链 |
| `BalancedRng`（chanceRng）只是包着 `Util.flip` 的平衡器 | BalancedRandom.gd:71-96 | `expectedWins` 初始化消耗全局 rng 一次（Item.gd:472 每件物品 new 一次） |
| `BalancedRng.reset()` 只清计数器，**不重播种** | BalancedRandom.gd:104-112 | 战斗开始时刻的 `rng.state` = 该场战斗的全部随机状态 |
| 历史对战 `Game.startHistoryRun` 不重播种 | Game.gd:2690-2704、BuildHistory.gd:507 | 历史对战的随机性同样由战斗开始时刻的 state 决定 |

**结论**：捕获「战斗开始时刻的 `Util.rng.state`（64 位 PCG32 状态）+ 双方阵容 + 初始 HP/体力/回合」
即可确定性重放整场战斗。`MAX_SIZE`/位流、阵容、HP 体力均已可从 history.db 解码——唯一缺的输入就是 state。

## 1. 原版游戏的使用约束（用户指定，工具层强制配合）

- ✅ 只允许：历史记录界面 → 选中历史对局/回合 → **历史记录自带的对战功能**
  （`BuildHistory.gd` fightButton / FightPopUI → `Game.startHistoryRun`，Mode.History，离线）
- ❌ 绝对禁止：排名游戏（Ranked）、休闲游戏（Unranked/Lobbies）等任何在线匹配
- 配合措施：捕获工具是**纯只读旁路**（内存读 + 事件读，无任何输入模拟），游戏由用户手动操作；
  捕获协议文档（`docs/capture_protocol.md`）把操作步骤限死在历史记录界面内

## 2. 阶段

### P0 — RNG 语义考古（纯源码，已可执行）
- 产出 `docs/rng_truth.md`：上面表格的展开版 + **内存对象图路径**推导
  （Util autoload 节点 → GDScriptInstance.members → rng 成员槽位 → RandomNumberGenerator
  对象的 seed/state 字段偏移——沿用 ItemBook/CombatLog 的 godot_reader 标定方法）
- 历史对战输入清单逐行核实（startHistoryRun → 装配 → 判定胜负的完整输入面）
- 退出标准：文档给出 rng state 的唯一内存定位方案与验证方法

### P1 — gd_core 支持 rng state 注入
- `gd_core/CoreContext`（或 CoreRng）增加 `set_state(state: int)`：PCG32 直接设状态
  （Godot RandomNumberGenerator 的 `state` setter 语义：`state = v` 后下一次 randf 从 v 前进）
- `gd_core_test/RngStateProbe.gd`：Godot 原生 RandomNumberGenerator 设同一 state 跑 N 步
  vs gd_core 内核同 state 跑 N 步 → 逐位一致
- `gd_core_py/_rt.py` 同步；`tools/verify_godot_rng.py` 增加 state 注入段
- 退出标准：world.run 闸门（Godot + verify 脚本）全过

### P2 — 活体 rng state 读取器
- `core/godot_reader.py` 增加 `read_rng_state()`：按 P0 的内存路径读 Util.rng 的
  seed/state 双 u64
- 标定方法：连续两次读取差分（战斗外 state 不变 → 读数稳定 = 读对字段）；
  战斗内 state 单调前进（PCG 前向）
- 集成进 `combatlog_exporter.py`：战斗期间**密集轮询**（战斗检测到后 100ms 级），
  记录最早捕获的 state（捕获越早，越可能早于第一次 roll）
- 退出标准：同一场战斗能同时导出 (最早 rng state, 双方阵容, 完整事件流)

### P3 — 真值捕获会话（需用户手动操作游戏）
- 协议（`docs/capture_protocol.md`，给用户的操作单）：
  1. 启动游戏 + 启动扩展版 combatlog_exporter（开始监听）
  2. 游戏内：历史记录 → 选中对局与回合 → 点对战（**全程不离开历史记录功能**）
  3. 打完回到历史记录，可换下一场重复
- 每场产出 `output/replay/<时间戳>/`：`rng_state.txt`（最早捕获 state）+ 双方阵容 v4 +
  `events.json`（完整事件流）
- 场次建议：先 3~5 场（含 DK 场次），跑通后扩到 20+ 场

### P4 — 逐位对齐与修复循环（核心阶段）
- 重放器：`tools/replay_truth.py` —— 输入捕获三元组 → gd_core(Godot) 注入 state 跑同阵容
  → 规范事件流逐事件 diff（canonical_events.py 已就绪）
- 对齐判据：事件数、逐事件 (t, type, side, origin, params) 完全一致（t 以 tick 为单位）
- 分歧处理：分歧点即确定性逻辑错的精确位置 → 三角定位（data/kernel/转写）→
  **修 gd_core/*.gd（反编译源码修复）→ Godot 无头运行即编译验证** → gd_core_py 同步转写 → 重放
- 黏黏龙骑士终审：同 state 同 roll 序列下，若重放仍在 DK 链分叉，即为内核/数据确定性 bug，
  逐行对源码修到一致
- 退出标准：**至少 3 场捕获对战逐事件 100% 一致**

### P5 — 回归固化
- 每份捕获三元组 = 一个逐位回归用例；`tools/verify_replay.py` 批量重放全部捕获
- 纳入验收链：任何内核/数据/转写改动后必须全绿
- 覆盖扩展：每多捕获一场（不同对局/回合），用例池 grows；历史 DB 有 1001 runs 可持续供阵容

## 3. 风险与对策

| 风险 | 对策 |
|------|------|
| state 捕获晚于第一次 roll（前几事件不对齐） | 战斗检测后 100ms 级密集轮询取最早值；若重放首事件即分叉则判定捕获过晚，该场重捕；PCG 状态也可由「结束时刻 state 反向步进校验消耗次数」辅助判断 |
| RandomNumberGenerator 对象内存布局未知 | P0 按 godot_reader 既有标定法（两次读差分 + 字段语义验证）；Godot 3.6 源码可查 PCG32 字段序 |
| 历史对战的对手快照来源复杂（对手=当年真实玩家的另一 run 快照） | P0 逐行核 startHistoryRun 的对手装配路径；对手阵容也可由 combatlog_reader 的结构性物品读取在捕获时同步拿到（双保险） |
| 战斗内还有非 rng 的不确定性（帧率、物理） | 原版战斗是 60Hz 固定 tick 逻辑（_physics_process），无物理随机性；gd_core 已按固定 tick 复刻 |
| 修复改了 gd_core 后 gd_core_py 漂移 | 每次改 .gd 必须同步跑 gd_to_py 转写 + RngProbe/逐位闸门（纳入 P4 循环） |

## 4. 里程碑与退出标准

| 里程碑 | 交付 | 退出标准 |
|--------|------|----------|
| M-P0 | docs/rng_truth.md | 内存定位方案 + 历史对战输入面核实完毕 |
| M-P1 | state 注入 + 逐位探针 | world.run 闸门全过 |
| M-P2 | 活体读取器 + 导出器集成 | 同场战斗产出三元组 |
| M-P3 | ≥3 场捕获 | 三元组完整（state 早于首 roll） |
| M-P4 | 逐事件对齐 | ≥3 场 100% 一致；DK 终审结论落定 |
| M-P5 | 回归套件 | verify_replay 全绿并入验收链 |

**最终验收**：模拟器（gd_core_py，经 gd_core 同步）对任意一场捕获的历史对战，
从捕获的 rng state 重放，与原版事件流**逐事件 100% 一致**——即用户要求的
"模拟器与原版游戏引擎完全一致"的可证明形式。
