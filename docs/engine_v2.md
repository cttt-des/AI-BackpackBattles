# 战斗引擎 v2（engine/）— 架构与切换说明

> 新战斗内核 `engine/`：编译期代码生成 + fail-fast + 无进程级单例。
> 本文档说明 v2 与旧内核 `simulator/` 的关系、模块职责、验收结论与切换点。
> 生成日期：2026-09-21（Phase 2~5 完成版）

---

## 1. 为什么重写

旧内核 `simulator/` 的静默降级设计（`_Noop`/`_SafeDict` 兜底 + 异常吞掉）使
**物品行为失效不可观测**：Goobert 全族因 `CombatLog.snapshotItemTooltipStat`
缺桩，`prepare()` 在信号连接前 AttributeError 被静默吞掉，信号一个没连，
验收探针还因"只验路径通、不验回调真执行"而假阳性放行。

v2 的三原则：

1. **源码为唯一真值**：所有行为从 `decompiled_full/` 逐行转译，AST 级生成
   Python 模块 `engine/gen/behaviors.py`（3174 个转译函数，常驻 import）
2. **fail-fast**：运行期命中未登记桩 = 硬错误并计数（`engine/stubs.py` 白名单），
   不再静默兜底；异常计入 `behavior.failures` 可观测
3. **无单例**：战斗状态全部挂在 `BattleContext`/`CombatEngine` 上，可
   deepcopy/序列化（RL 铺路），支持多进程并行

## 2. 模块地图

| 模块 | 职责 | 对齐源码 |
|------|------|----------|
| `engine/gen/behaviors.py` | 3174 个转译行为函数 + METAS（extends 链/iv/timer） | Items/*.gd 全部 |
| `engine/behavior.py` | BehaviorExecutor：`resolve_fn` 沿 extends 链解析、super_execute、failures 记录 | GDScript 继承语义 |
| `engine/item.py` | 冷却 ±5% 抖动、activate 同帧限流、触发器、宝石三模式、电荷、affected 几何 | Items/Item.gd |
| `engine/character.py` | takeDamage 14 步链、buff 全语义、体力溢出窗口 | Core/Character.gd, Buff.gd |
| `engine/combat.py` | 2.5s 开战延迟、三阶段激活、1s tick、疲劳（advanceTime 支持）、判胜 | Core/Game.gd, CombatTimer.gd |
| `engine/rng.py` | BalancedRandom（防连击/防连败/联赛偏置）+ BalancedRange | Util.gd |
| `engine/context.py` | BattleContext（战斗级单例替代）：game/combatLog/util/item_book/event_bus | Core/Game.gd, Util.gd, ItemBook |
| `engine/namespaces.py` | 枚举/常量命名空间（真值 + 自洽桩） | 各 .gd enum |
| `engine/stubs.py` | 显式桩登记表（视觉属性白名单 + 命中计数） | — |
| `engine/events.py` | 惰性事件日志（AI 热路径零文本开销） | — |

## 3. 数据流

```
decompiled_full/*.gd
   │  simulator/extract_items.py（AST 级代码生成器，fail-fast API 校验）
   ▼
engine/gen/behaviors.py（3174 函数，编译期产物）
   │
assets/battle_items.json ── engine/data.py ──▶ engine.CombatEngine
   ▼
BattleContext（ctx 注入全部参战物品）→ run() → 惰性事件 → result_json()
```

## 4. 切换点

| 入口 | 默认内核 | 回退方式 |
|------|----------|----------|
| `python -m simulator.simulate A B` | engine | `--engine simulator` |
| GUI（`battle_simulator.py`） | engine | `simulate_once(..., engine='simulator')` |
| `tools/regression_baseline.py` | simulator（历史基线兼容） | `--engine engine` |
| `tools/verify_linkage.py` | engine（已切换） | — |
| `tools/audit_item_effects.py` | engine（已切换） | — |

旧内核 `simulator/` 冻结保留（仅致命 bug 修复），作为回归对照基线。

## 5. 验收结论（2026-09-21）

- **信号级联动探针**：Goobert 全族 12/12 PASS（连接数 + 回调真实执行计数 + 零 failure）；
  King Gobert 修复 = `f_King_Goobert__prepare` 补 `Goobert.prepare` 链
  （KingGoobert.gd:26 `.prepare()` 转译遗漏）
- **verify_linkage** 18/18 PASS（含 Twine 几何/信号、Rope 速度、药水信号）
- **audit 三层对账**：518 物品运行时生命周期探测 **0 失败**
  （修复：`_EnumSentinel` 算术/调用、descriptor 可哈希、GameGlobal
  Classes/Mode/combatTimer/combatSceneNode/timeAdvance、视觉属性 iv 跳过）
- **56 场双引擎对照**（8 阵容全对打，seed=42）：差异 100% 归因（未归因 0），
  归因清单：事件面重构（56）、±5% 冷却抖动传导（37 时长 / 10 疲劳计数）、
  HP 差异（12/9）；胜负翻转 1 场（poison_bow vs greatsword_tank，
  21.02s→19.02s 疲劳节奏位移，预期内）
- **affected 几何修复**：`_affected_cells_abs` 与碰撞同一归一化基准
  （碰撞与 Affected tile 同处 CollisionMap 坐标系，extract_grid.py decode_tile
  出口一致；此前多格物品受影响格整体错位 (min_x, min_y)）

## 6. 已知边界

- `methods_raw` 转译失败 87 个（51 物品）与未入库 443 个方法（196 物品，视觉/
  商店类为主）为 Phase 1 静态对账的已知存量，运行时探测已确认不影响战斗路径
- 新内核日志为惰性事件流（无文本渲染），`to_text` 由工具侧按需生成
- RL 训练接口（observation/reward/批量训练入口）为第二阶段 roadmap，未实现
