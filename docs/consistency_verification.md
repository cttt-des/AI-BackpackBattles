# 翻译一致性验证协议（engine/ ↔ 原版游戏）

> 目标：**量化验证转译内核 `engine/` 与原版游戏《背包乱斗》(v1.1.7) 的行为一致性**，产出按物品归因的偏差榜，替代"细致重构翻译"——只修数据证实有偏差的物品。
> 背景：README 已知问题（绳索不激活、Goobert 双触发等）在验收工具全绿状态下存在，说明静态对账覆盖不了实战时序。本协议用**真游戏自己的运行时数据**做裁决。
> 通道：bridge 注入（进程内，可播种 RNG、可 tapped 战斗事件流）+ engine/ 同种子复放。桥接脚本：`bridge/bridge.gd`（v2 已加一致性验证命令）。

## 0. 原则

1. **游戏是真值，不是对手**：所有不一致以游戏侧数据为准，engine/ 是被测对象。
2. **先证游戏可复现，再谈比对**：同种子两场游戏事件流必须逐字节一致，否则存在未播种的随机通道，先解决这个（见 §3）。
3. **差异必须归因到物品**：每条不匹配事件带源物品，聚合出 per-item 偏差榜——修榜上的，不动榜外的。

## 1. 数据流

```
原版游戏（v1.1.7 + bridge PCK 补丁）
   │  seed_rng(S)                ← 播种 Util.rng + 全局 RNG
   │  tap_combat(start)          ← _process 逐帧轮询 Game.combatLog.events 增量
   │  [玩家摆好阵容 → 开战]
   │  get_tapped_events → 游戏事件流 JSON（真值）
   │  snapshot_run → 双方阵容/网格/宝石/回合状态（对局初态）
   ▼
diff 工具（tools/consistency_diff.py，TODO）
   ▲
engine/（同初态 lineup v3/v4 + 同种子 S）
   │  tools/dump_engine_fight.py → engine 事件流 JSON（被测）
   │  （engine 时间轴为 60Hz tick，diff 时归一化到秒）
```

## 2. bridge v2 一致性命令（已加入 bridge.gd）

| 命令 | 参数 | 说明 |
|---|---|---|
| `seed_rng` | `{"seed": int}` | `Util.rng.seed = seed` + 全局 `seed(seed)`；战斗准备阶段游戏会自行 reset 各 BalancedRng（从 Util.rng 派生） |
| `tap_combat` | `{"enable": bool}` | 开关事件 tapped：每个物理帧检查 `Game.combatLog.events` 长度，增量序列化（CombatEvent 脚本属性全量 dump）入缓冲区 |
| `get_tapped_events` | `{"clear": bool}` | 取走缓冲事件；`clear=true` 清空（每场战斗边界用） |
| `snapshot_run` | — | 复用现有 reader：背包/仓库/商店全量属性 + Game 的 round/gold/hp + 双方 Character 的 curHealth/maxHealth/buffs |
| `get_fight_result` | — | fightEnded、双方最终血量、combatTime（CombatTimer） |

tapped 用轮询而非信号钩子：零侵入游戏逻辑（只读 combatLog 数组），不冒改变时序的风险。

## 3. 验证协议（按序执行）

### 阶段 0：游戏自洽性（前置门槛）
同阵容、同种子 S，连续打 2 场 → 两份事件流 diff 必须为**空**。
- 非空 → 存在未播种通道（疑似：`Array.shuffle`/`pick_random` 走全局 RNG 已在 seed_rng 覆盖；需排查 OS 时间、字典序、物理帧抖动相关分支）。逐个封堵后重测。
- 此阶段纯游戏侧，不涉 engine/。

### 阶段 1：初态一致性
`battle_items.json` + lineup v3/v4 导入 engine/ 的初态（物品集/位置/旋转/宝石/职业）vs `snapshot_run` 的游戏初态：
- 字段级 diff（数量、item_id、grid 坐标、朝向、gems）。
- 不一致 = 数据层 bug（转译或导出），先于行为修。

### 阶段 2：单场确定性比对
同初态 + 同种子 → engine/ 事件流 vs 游戏事件流，对齐规则：
1. 按事件序号对齐；时间戳字段归一化（engine tick/60 → 秒，容忍 ±1 tick = ±16.7ms 的取整差）。
2. 分类：缺失 / 多余 / 数值不符（amount/hp）/ 时序不符（同序号时间差 > 2 tick）/ 顺序不符。
3. 每条事件归因源物品名，聚合 per-item 偏差计数。
- **验收线**：P0 物品（出场 top80）零数值类不符；时序类不符 ≤2 tick；已知问题物品（Rope/Goobert 系）允许出现在偏差榜，但榜外物品必须为零。

### 阶段 3：统计一致性（确定性之外的兜底）
单场不一致但疑似同分布（如 RNG 通道未完全对齐）时：同阵容双方各打 N=100 场（游戏侧种子扫描，engine 侧种子扫描）→ 胜率差 <2% 且伤害分布 KS 检验 p>0.05。
- 统计一致不能替代阶段 2（README 的教训：联动错可能不改变胜率分布），只作辅助证据。

### 阶段 4：覆盖扩展
- 56 场回归指纹阵容（regression_baseline）逐场过阶段 2；
- 对局 fuzz：随机合法阵容生成器（tools 侧 TODO）× 种子扫描，偏差榜累积；
- 商店域（rollItems/reroll/促销）待 engine/ 移植后用同一协议验（snapshot 扩展商店字段）。

## 4. 产出物

1. **per-item 偏差榜**（JSON + md 报告）：`docs/consistency_deviation_report.md`，字段 = {item, 事件类型， 偏差类别， 出现场次， 典型样本}。
2. **修复清单**：只含榜上物品；修完重跑阶段 2 销项。
3. **验收基线**：偏差榜全零的阵容集固化进 `tools/regression_baseline.py` 的 engine↔game 双端指纹（区别于现有 engine↔simulator 双内核指纹）。

## 5. 风险与边界

- **桥接注入 modifies game files**：只在离线/练习模式跑；外置内存模式（core/memory_reader）可做阶段 1 与阶段 3 的降级通道（无法播种 → 只能统计比对）。
- **事件序列化保真**：CombatEvent 的 script vars 经 `_safe_get_all_properties` 全量 dump；对象引用型字段（item 指针）序列化为 script 路径 + name，diff 侧按 name 匹配。
- **时序归一化误差**：游戏战斗帧率波动（非 lockstep）时事件时间戳有抖动，阶段 2 的 ±2 tick 容差即为此设；若抖动系统性超差，改比"事件序号 + 相对间隔"而非绝对时间。
- **不要在比对中'修'游戏侧数据**：游戏侧原始 dump 永远原样归档（`output/game_truth/`），一切归一化在 diff 工具内的副本上进行。
