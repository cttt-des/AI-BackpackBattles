# 模拟器 ↔ 原版一致性检验工作流

> 目标：系统性检验模拟器与原版的一致性，定位并修复偏差，最终达成可证明的一致。
> 本文是操作手册：每阶段有交付物、工具与退出标准，全部基于仓库现有资产。
> 生成日期：2026-10-02

---

## 0. 现状资产盘点（工作流的输入）

| 资产 | 位置 | 作用 |
|------|------|------|
| 真值实录 | `dist/output/combat_logs/`（25 组，每组 5 文件） | 真实游戏的双方阵容（v4）+ 逐事件日志 + 双语战报 |
| 历史位流解码 | `core/build_history.py` | history.db → 1001 runs × 18 rounds 全部摆盘（314k 物品放置记录）→ 任意阵容池 |
| gd_core 内核（Godot） | `gd_core/` + `gd_core_test/` | 原版战斗逻辑 1:1 移植，可无头运行（`output/godot36/Godot_v3.6-stable_win64.exe`） |
| gd_core 内核（Python） | `gd_core_py/` | GDScript → Python 机械转写（`tools/gd_to_py.py`） |
| 事件轨迹 | `gd_core_test/event_trace.txt` | gd_core 原生事件轨迹（`t\|type\|target\|origin\|params` 规范格式） |
| RNG 逐位探针 | `gd_core_test/RngProbe.gd` + `tools/verify_godot_rng.py` | 已证明 gd_core_py 的 RandomNumberGenerator 与 Godot 3.6 逐位一致 |
| 表现钩子 | `gd_core_test/LineupBattle.gd` HookProbe | 激活/伤害/治疗/宝石治疗/疲劳/眩晕计数埋点（CoreHooks） |
| 旧对照工具 | `tools/compare_truth.py` / `per_item_diff.py` | 分布型对照（胜负/时长/事件分布/逐物品）——本工作流的起点而非终点 |

## 1. 「完全一致」的分层定义（验收目标）

| 层级 | 命题 | 可达性 |
|------|------|--------|
| **L1 确定性一致** | 任意阵容/种子下，`gd_core_py`(Python) 与 `gd_core`(Godot) 的战斗输出**逐位一致** | ✅ 可精确达成——RngProbe 已证 RNG 逐位一致，缺的是覆盖面（现有 56 局闸门仅 8 套阵容，DK+Twine+Chili 组合从未过闸） |
| **L2 行为一致** | `gd_core`(Godot) 与真实游戏的**行为分布**在容差内（实录对照评分 ≥ 阈值） | ✅ 度量型——分布收敛 + 不变量全部成立 |
| **L3 逐事件一致** | 同 rng 种子下 gd_core 与真实游戏**逐事件对齐** | ⏳ stretch——需活体读游戏内存的 rng 种子（combatlog_reader 扩展）；达成后即可精确复现任意一场实录 |

**关键推论**：模拟器的最终一致性 = L1（精确）+ L2（度量）。L1 是我们完全可控的；
L2 的残差只可能来自反编译失真或版本差（v1.1.7 内核 vs v1.1.8 运行版）。

## 2. 三角定位法（缺陷归因的核心方法）

```
        真实游戏（实录）
        │            ▲
   L2 对照│            │L2 对照
        ▼            │
  gd_core(Godot) ──L1 逐位──▶ gd_core_py(Python)
```

任何行为偏差跑两次对照即可定位到唯一一层：

| 观测 | 结论 | 修复位置 |
|------|------|----------|
| gd_core(Godot) 也复现偏差 | 反编译内核或数据错 | `gd_core/*.gd`（对照 `decompiled_full/` 源码）或 `assets/gd_core_runtime.json` |
| Godot 对、Python 错 | 转写器 bug | `tools/gd_to_py.py` 或 `gd_core_py/` 手补 |
| 两边都对、与实录不符 | 内核↔游戏差异 | 版本差（1.1.7 vs 1.1.8）/ 反编译失真 → 回源码逐行核 |

**立即可做的定位**：黏黏龙骑士正反馈环——56 局闸门的 8 套阵容不含 DK+Twine+Chili
组合，该链**从未过 L1 闸门**。用实录阵容生成 fixture 跑 gd_core(Godot)，一次对照
就能把 DK 问题钉死在某一层（见 M2）。

## 3. 阶段与里程碑

### Phase 0 — 事件规范化与 HP 账本（M1）

**问题**：游戏日志（CombatEvent id/parent/depth）、gd_core 轨迹（`t|type|target|origin|params`）、
Python 模拟事件（dict）三套格式互不相通；分布对照无法区分「rng 差异」与「行为差异」。

**交付**：`tools/canonical_events.py`
- 三种日志 → 统一规范事件流：`(t, type, side, origin_key, params)`；时间戳对齐（游戏 tick 60Hz 取整）
- **HP 账本**：从事件流重建双方 HP 曲线（DealDamage/Critical/Fatigue/Poison/Spikes/Unhealing 记借，Health/Regeneration 记贷）——HP 轨迹是对 rng 最不敏感的**状态级**指标，曲线分叉即真实行为差异
- 退出标准：同一实录能被三种来源解析出一致的 HP 终值

### Phase 1 — 三角定位DK（M2，最高优先）

**交付**：`tools/gen_fixture_from_lineup.py`（实录/历史阵容 → LineupFixture 格式）+
gd_core_test 新闸门 `TruthBattle.gd`（跑实录阵容，输出 HookProbe 计数 + event_trace）。

**步骤**：
1. 从 25 组实录抽 DK 场次（220653 / 221407 / 220653 双方）生成 fixture
2. `Godot --script TruthBattle.gd` 跑 gd_core(Godot)
3. 对照三角：真值实录 ↔ Godot 轨迹 ↔ Python 轨迹
4. 退出标准：DK 偏差被钉死到数据/内核/转写之一，并出修复补丁

### Phase 2 — 一致性评分套件（M3）

**交付**：`tools/consistency_suite.py`（升级 compare_truth.py）
- 对 25 组实录 × N 种子：结构指标（胜负/时长/终局 HP）+ Phase 0 的 HP 曲线距离
  （DTW 或逐秒 L1）+ 逐物品激活/伤害/治疗比
- 输出 `output/consistency_report.json`：总分 + 按影响面（受影响组数 × 偏差幅度）
  排序的缺陷榜
- **回归门槛**：任何内核/数据改动，套件总分不得下降（CI 手动跑）

### Phase 3 — 不变量检验器（M4，破局 rng 混淆）

**问题**：分布对照的致命弱点——rng 序列不同会让逐项数值天然波动，行为 bug 藏在噪声里。
**解法**：对 rng **无感**的硬不变量，同时作用于实录与模拟：

| ID | 不变量 | 真值依据 |
|----|--------|----------|
| I1 | 冷却驱动物品的激活次数 = f(时长, cd, speed 序列) 的确定函数（±首帧粒度） | Item.gd `_physics_process`/`trigger` |
| I2 | 每次攻击伤害 ∈ [minDam, maxDam] × 修正（Empower/暴击×2/伤害因子），越界即 bug | DamageSource |
| I3 | 暴击率 ≈ critChancePercent（二项置信区间，n≥30 时 ±5%） | Character.gd |
| I4 | Block 消耗 ≤ 累计获得栈数；任一时刻消耗不超过持有 | Buff.gd |
| I5 | 疲劳首跳 14s，间隔 3s→1s，双方独立 | CombatTimer.gd |
| I6 | 同帧同物品激活 ≤ 3（限流），每秒激活 ≤ 60×3 | Item.gd 4697-4702 |
| I7 | HP 单调性：扣血 ≤ 当前血；终局血 ≤ 0 → 判负 | Character.gd |
| I8 | 事件因果：伤害 origin 必须存在于对应侧摆盘；治疗 origin 同 | CombatEvent.gd |
| I9 | 充能物品触发数 = ⌊供给方 activated 数 / 阈值⌋（±双激活随机项） | Goobert.gd 等 |
| I10 | 速度 = (speedScale + (heat-cold)×0.02) 修正后 clamp 0.1..10，栈数可从事件流重建 | Item.gd 3742-3757 |

**交付**：`tools/invariants.py`（输入规范事件流 → 违例报告）。
对 25 组实录跑 = **真值自身也受检验**（可发现导出器漏事件）；对模拟跑 = 行为 bug 探测器。
违例与 rng 无关，修一个少一个。

### Phase 4 — 覆盖矩阵收口（M5）

**目标**：L1 闸门覆盖 518 物品 × 核心机制（近战/远程/格挡/栈增减/插座/袋/宝石/充能联动）。

**交付**：
- `tools/gen_coverage_fixtures.py`：从 314k 历史放置记录统计每物品上场频次 →
  按「高频优先 + 零覆盖优先」生成最小对局阵容（含 A/B 对照：目标物品在/不在）
- 批量跑 gd_core(Godot) vs gd_core_py 逐位闸门 → 覆盖率仪表
- 退出标准：每件物品至少出现在 1 个过闸阵容中；转写缺口清零

### Phase 5 — L3 逐事件对齐（stretch）

- `core/combatlog_reader.py` 扩展：活体读 `Util.rng`/`chanceRng`/`critRng` 的种子与状态
  （ Godot RandomNumberGenerator 的 state 是 64 位整数，内存布局可循 ItemBook 先例）
- 若游戏每场用可读种子 → 同种子喂 gd_core → 与实录**逐事件对齐**，
  DK 等所有 rng 相关争议一次终结
- 风险：种子可能 randomize()（不可复现）→ 降级为「rng 状态流校验」（对比两边的
  roll 消耗次数与取值分布）

## 4. 执行顺序与依赖

```
M1 规范化 ──▶ M2 三角定位DK ──▶ M3 评分套件 ──▶ M4 不变量 ──▶ M5 覆盖矩阵 ──▶ L3
   │              │                │               │
   └── HP账本     └─ 需 M1         └─ 需 M1        └─ 需 M1（不变量跑在规范流上）
```

- M1 → M2 是关键路径：DK 是当前唯一已知的行为级缺陷，M2 的三角定位同时验证
  整个三角方法论
- M3 与 M4 可并行；M4 的不变量清单会随缺陷修复持续扩充（每个新缺陷沉淀一条不变量）
- 每完成一层 L1 扩容（新阵容过闸），`tools/check_gd_core_engine.py` 的逐字符校验
  必须保持 0 差异

## 5. 退出标准（「完全一致」的最终验收）

1. **L1**：覆盖矩阵 100%——518 物品全部出现在至少 1 个过闸阵容；任意过闸阵容
   Godot vs Python 逐位一致
2. **L2**：25 组实录评分全部达标（结构指标 100%，HP 曲线距离 < ε，逐物品比 ∈
   [1-δ, 1+δ]），且不变量 I1-I10 在实录与模拟上零违例
3. **DK 链**：真值阵容下模拟不再正反馈爆炸（攻击间隔分布与实录一致）
4. 残差清单：仅剩「反编译失真/版本差」类已归因条目，每条附源码行号依据
