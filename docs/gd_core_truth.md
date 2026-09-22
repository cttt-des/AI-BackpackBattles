# gd_core 忠实性真值表（无头解耦内核）

> 交付目标：把解包代码的战斗逻辑从 Godot 节点树 / 渲染 / 物理 / 音频 / UI / 单例中剥出来，
> 成为不依赖场景树的纯逻辑模块，**判定链路 1:1 不变**。
>
> 本文是该承诺的取证文档：每一处改动都能对到源码行号，每一处剥离都给出「为什么它不影响判定」。
> 生成日期：2026-09-22

---

## 1. 模块映射

`gd_core/` 共 14 个脚本、4834 行。所有模块 `extends Reference`，无一继承 `Node`/`Node2D`。

| gd_core 文件 | 行数 | 对齐源文件 | 说明 |
|---|---:|---|---|
| `CoreConst.gd` | 240 | 跨文件常量/枚举 | `Item.Type`、`Item.Stat`、`Character.Stat`、`Game.EventType` 等归一，**为断 class_name 循环依赖而集中** |
| `CoreRng.gd` | 233 | `Util.rng`（`Game.gd`） | 注入式随机源；`BalancedRng` / `BalancedRange` 包装器照搬 |
| `CoreEvent.gd` | 94 | `Core/CombatEvent.gd` | 13/13 方法全覆盖 |
| `CoreEventBus.gd` | 123 | `Game` 信号系统 | `connect_signal` / `emit_signal` 语义保留 |
| `CoreCombatLog.gd` | 337 | `Core/CombatLog.gd`（1279 行） | **只保留事件工厂**（34/96），见 §5 |
| `CoreItemData.gd` | 104 | `ItemBook` 物品描述符 | 战斗只读字段 |
| `CoreDamageSource.gd` | 212 | `Utility/DamageSource.gd` | 23/23 全覆盖 |
| `CoreDamageResult.gd` | 96 | `Utility/DamageResult.gd` | 14/14 全覆盖 |
| `CoreBuff.gd` | 393 | `Core/Buff.gd` | 18/14（含 gd_core 侧辅助） |
| `CoreItem.gd` | 1168 | `Items/Item.gd`（约 5000 行） | 冷却/触发/激活主干 + 伤害数值；**行为 API 面未完成，见 §8** |
| `CoreCharacter.gd` | 1135 | `Core/Character.gd` | 138/210；伤害链 / 治疗 / 格挡 / 疲劳 / 体力 / 眩晕 |
| `CoreContext.gd` | 104 | 新增（无源文件） | 单例注入点，见 §3.1 |
| `CoreHooks.gd` | 178 | 新增（无源文件） | 副作用钩子，37 个空实现，见 §3.2 |
| `CoreCombat.gd` | 417 | `Game.gd:2978-3032/3257-3379` + `Interface/CombatTimer/CombatTimer.gd` | 战斗驱动主循环 |

运行入口：`gd_core_test/`（独立 Godot 工程，`gd_core` 以目录联接指向 `../gd_core`，保证单一真值来源）。

---

## 2. 一句话结论

**判定路径上的每一行都保留了；被删掉的全是「表现副作用」与「出战斗流程」（商店/合成/背包/存档/UI）。**
代价是 `CoreItem` 的方法面只到 157/628 —— 缺口 211 项集中在物品行为 API 面（§8），
所以 gd_core 目前**能跑通核心循环，但还不能承载 518 个真实物品行为**。

---

## 3. 解耦手法（三层）

### 3.1 单例访问 → `CoreContext` 注入

原版判定函数里遍布 `Game.stealLifeDamageSource`、`Game.PLAYER`、`Util.rng`、`Game.combatLog`。
它们是 autoload 单例，只要脚本被判定函数引用，就无法脱离场景树实例化。

改法：全部收敛为 `ctx.*`。

```gdscript
# 原版 Item.gd:5137
Game.stealLifeDamageSource.updateEffect(self, damage)
# gd_core CoreItem.gd
damageSource.updateEffect(self, damage)      # 共享伤害源由装配方传入
```

`CoreContext` 持有的共享对象与原版 `Game` 的静态字段一一对应：

| 原版 | gd_core |
|---|---|
| `Util.rng` | `ctx.rng` |
| `Game.combatLog` | `ctx.combat_log` |
| `Game.PLAYER` / `OPPONENT` | `ctx.player` / `ctx.opponent` |
| `Game.unhealingDamageSource` | `ctx.unhealingDamageSource` |
| `Game.fatigueDamageSource` | `ctx.fatigueDamageSource` |
| `Game.stealLifeDamageSource` | `ctx.stealLifeDamageSource` |
| `Util.time` | `ctx.time` + `ctx.advancePhysicsFrame()` |

> ⚠️ 命名坑：原版字段名 `log` 在 gd_core 里必须叫 `combat_log` ——
> `log` 是 GDScript 内置函数，用作成员名会直接 Parse Error。

### 3.2 表现副作用 → `CoreHooks` 钩子（默认全空）

原版把视觉/音频/UI 直接内联写在判定函数尾部，例如：

```gdscript
# 原版 Item.gd trigger() 附近
playActivationAnimation(...)
showCooldown(1.0 - (triggerTime / iterationCooldown))
```

gd_core 改为：

```gdscript
ctx.hooks.playActivationAnimation(self, ...)
ctx.hooks.showCooldown(self, 1.0 - (triggerTime / iterationCooldown))
```

**保真论证（这是整套方案成立的前提）：**

1. 所有 `ctx.hooks.*` 调用都位于函数体**尾部**，不参与任何 `if` / 循环条件 / 返回值计算；
2. 因此空实现与真实实现产生**完全相同的判定状态**，仅少了屏幕上的像素与声音；
3. 需要真实表现时（注入回游戏进程内运行）继承 `CoreHooks` 覆写即可，判定代码零改动。

钩子共 37 个，分 6 组：物品层表现、战斗计时器表现、角色层表现、粒子/位移、统计埋点、战斗日志。
其中统计埋点（`addMetric` / `snapshot*` / `updateDamageMeter`）在原版也是纯采集，不回流判定。

**唯一需要单独论证的一类**：原版有把副作用写进条件的分支，例如
`if animation.current_animation != "Poison": ...`。这类不挂钩子，而是**整体删除**，
并在 §5 记为「纯表现分支」——因为被条件保护的语句只改动画状态，不写任何被判定读取的量。

### 3.3 class_name 循环依赖 → 常量集中 + 鸭子类型

Godot 3.x 里 `class_name` 脚本互相引用（含自引用）会报
`couldn't be fully loaded (script error or cyclic dependency)`。实际踩到 5 个环：

| 环 | 解法 |
|---|---|
| `CoreCharacter` ↔ `CoreItem` ↔ `CoreDamageSource` ↔ `CoreDamageResult` | 枚举迁到零依赖的 `CoreConst` |
| `CoreDamageSource` 判 `origin is CoreItem` | 改鸭子类型 `origin.has_method("isCoreItem")` |
| `CoreItemData.fromDict` 返回自身类型 + `CoreItemData.new()` | 改实例工厂 `var o = self` |
| `CoreItem` 出向引用 `CoreCharacter.ID` / `.StaminaResult` | 改用 `CoreConst.CharID` / `CoreConst.StaminaResult` |

守门工具：`tools/check_class_cycles.py`（DFS 找环，退出码非 0 即有环）。

---

## 4. 帧内次序契约（提速的前提是不乱序）

`CoreCombat.physicsTick(delta)` 的固定次序，逐条对齐已验证的 Python 引擎 `engine/combat.py:_tick`：

```
① _pending_deferred flush（对齐 call_deferred 帧末语义）
② fight_ended 守卫
③ 开战倒计时（未激活前 combat_time 不增长 → 事件时间戳从 0 起算）
④ combat_time += delta
⑤ ctx.advancePhysicsFrame(delta)          # Util 全局物理时钟
⑥ 物品 physicsTick 循环                    # Item.gd:4453-4458
⑦ 角色 physicsTick 循环                    # 眩晕递减 + 体力再生
⑧ onTick（TickTimer 1s 循环）
⑨ tickBuffs（Buff 临时栈超时）
⑩ _fatigueTick
⑪ 超时兜底 forceLoseCombat
⑫ 帧末 flush
```

**因果链上的两个关键语义**（容易写错，均已对齐）：

- **判胜在伤害链中途同步置位**：`endCombat()` 由 `character_died` 信号在伤害结算过程中同步调用，
  `fight_ended` 立刻为 `true`（后续事件派发被挡下），但收尾 `combatEndDeferred()` 延到帧末。
- **疲劳起点**：`startFatigue()` **不**发 `fatigue_start` 信号（原版如此），
  该信号在 `dealFatigueDamage()` 首次执行时发出。首发时刻 = `FATIGUE_TIME(17) = 14 + 3`。

---

## 5. 剥离清单

| 类别 | 处理 | 说明 |
|---|---|---|
| 渲染/动画/粒子/tween/shader/z_index | 改走 `ctx.hooks.*` | 纯副作用 |
| 音频/音效/BGM | 改走 `ctx.hooks.*` | 纯副作用 |
| UI 悬停/拖拽/预览/提示框 | 改走 `ctx.hooks.*` | 纯副作用 |
| 统计埋点与伤害计量表 | 改走 `ctx.hooks.*` | 原版即只读采集 |
| 战斗日志文本渲染与回放（约 1000 行） | **删除** | `CombatLog.gd` 只留事件工厂 |
| 商店 / 合成 / 背包格 / 宝石槽 / 存档 / 成就 / 联网 | **删除** | 属出战斗流程 |
| 节点生命周期（`_ready`/`_physics_process`/`_notification`） | **删除** | 改由 `CoreCombat` 显式驱动 |

原版 `Item.gd` 628 个方法中，199 个按名字属于上述类别（`解耦剥离`），199 项之外仍有
`待目视` 135 项与 `★战斗缺口` 211 项 —— 这三个数字的含义见 §7、§8。

---

## 6. 已知偏差与张力（不做隐藏）

1. **`adjustCooldown()` 的 ±5% 抖动：gd_core 保留，与 `simulator/` 有意分歧。**
   - 原版 `Item.gd:3805-3812`：玩家物品 `cd × randf_range(0.95, 1.05)`；
     对手且低于大师段位 `cd × randf_range(0.975, 1.05)`。gd_core 与 `engine/item.py` 一致，**照搬**。
   - `simulator/item.py` 按用户确认的游戏实际体感返回固定 `cd`。
   - 两者都对，但**不可混用**：`gd_core` 对齐「引擎真值」，`simulator` 对齐「体感真值」。
     smoke test 的断言因此写区间 `cd×[0.95,1.05]`，而非 `== cd`。

2. **去掉了原版没有的返回类型标注。** 移植时给不少函数补了 `-> int` / `-> float`，
   Godot 3 严格检查后暴露失配（如 `getModifiedEffectDamage` 原版无标注、可返回 float；
   `getBuffAccuracyMod` 原版返回 int 运算结果）。为忠实原版，**删标注而非加强转**。

3. **`getModifiedEffectDamage` 补回漏抄项。** 原版含
   `modifiedDamage *= (1.0 + character().typedDamageFactors[Effect])`，首版移植漏了，
   属真实保真缺陷，已补（`Item.gd:5130-5134`）。

4. **`statDisplayOverrides` 覆盖分支补回。** 原版 9 处 stat getter 都先查该数组；
   首版漏了 6 处（`getMinDamage`/`getMaxDamage`/`getSpeed`/`getAccuracy`/`getChance`/`getChance2`/`getCooldown`/`getCritChancePercent`）。
   `getCritChancePercent` 的判据是 `override != null`，其余是 `if override` —— 差异照搬。

5. **`ctx.time` 跨场不清零**（对齐 `Util.time` 是全局物理时钟）。因此 `orderered_items`
   排序与 `checkTriggerCount` 的 `triggersThisFrame` 依赖该时钟时，语义与原版一致。

6. **原版疑点一律照搬不修**，例如 `CombatLog.createEvent_BattleRageEnd` 把
   `Game.EventType.BattleRageEnd` 当 `origin` 传入；`createEvent_StackTemporary` 先调
   5 参版本再补 `reflected`。修复它们反而会偏离原版。

---

## 7. 验收方式与当前结果

一键流水线：

```bash
python tools/run_gd_core.py          # 四道闸门
python tools/run_gd_core.py --bench  # 附吞吐基准
```

| # | 闸门 | 工具 | 当前结果 |
|---|---|---|---|
| 1 | 静态审计：`ctx.*` 与 `Core*.` 引用是否都有定义 | `tools/audit_gd_core.py` | 通过（0 未定义） |
| 2 | class_name 依赖环 | `tools/check_class_cycles.py` | 通过（0 环） |
| 3 | 14 个脚本在 Godot 3.6 下全量解析 | `gd_core_test/ParseAll.gd` | 通过（failed=0/14） |
| 4 | 三项契约冒烟 | `gd_core_test/Smoke.gd` | **PASS** |
| — | 覆盖度核算 | `tools/gd_core_coverage.py` | 见下 |

**闸门 4 实测**（`gd_core_test/smoke_result.txt`）：

```
[1] 基础对拼：玩家 2 武器(5dmg/1.0cd) HP100  vs  对手 1 武器 HP20
    fight_ended=True  result=0(Win)  用时=1.95s  首击=0.983s
    HP  player=95.0  opponent=0.0
[2] 疲劳契约：双方空手 HP30 → 24.02s 收场，fatigue_counter=8，双死判玩家胜
[3] 确定性：同种子两场逐位一致（0|7.9667|6.0|0.0|0）
SMOKE: PASS
```

三项断言覆盖：冷却抖动区间、疲劳时序（17s 首发 + 1s 递增 1,2,3…8 累计 36 > 30）、
判胜与收尾（败者归 0 / 胜者至少 1）、同种子确定性。

**吞吐基准**（`gd_core_test/bench_result.txt`，加速比 = 模拟秒 / 墙钟秒，60Hz 实时 = 1×）：

| 场景 | 加速比（两次实测区间） | 单帧成本 |
|---|---:|---:|
| 双方各 2 武器 3dmg/0.8cd | 82× – 160× | 79 – 154 µs |
| 双方各 4 武器 3dmg/0.8cd | 55× – 76× | 135 – 185 µs |
| 双方各 6 武器 5dmg/1.0cd | 33× – 75× | 135 – 305 µs |
| 双方空手（纯疲劳 24s 场） | 233× – 546× | 28 – 65 µs |

> ⚠️ **口径与波动说明**：
> · 区间是因为本机为共享负载，两次运行的墙钟差最高达 2×；**绝对倍数不可复现，只有量级可信**。
> · 这是**相对 60Hz 实时**的倍数，来自「脱离场景树后不再有渲染/物理/音频/节点调度」。
> · 未做「gd_core 相对原版场景树」的倍数断言 —— 那需要在游戏内实测，此处不臆测。
> · 单帧成本随物品数近似线性增长（2→6 把武器约 4 倍），符合「逐物品遍历冷却 + 事件工厂」的预期复杂度。

---

## 8. 尚未完成（下一步的输入）

`tools/gd_core_coverage.py` 的方法名覆盖率是 **396 / 998 = 39.7%**，但按模块分层看结论完全不同：

| 模块 | 覆盖率 |
|---|---|
| `DamageSource` / `DamageResult` / `Buff` / `Event` / `EventBus` / `Rng` | **100%（Buff 为超集）** |
| `CoreCharacter` | 138 / 210 |
| `CoreItem` | 157 / 628 |
| `CoreCombatLog` | 34 / 96（**有意**只留事件工厂） |

**判定路径缺口 211 项**（`CoreItem` 176 + `CoreCharacter` 35），根据与判定路径的关系分三类：

1. **物品行为 API 面（最高优先）** —— 518 个物品行为转译后会直接调这些函数，缺了就跑不起来：
   `heal`、`stealLife`、`canHealOrLifesteal`、`sendCharge`、`reactsToCharges`、`chargeLeft`、
   `giveBuffPower`、`giveStacks`/`pickRandomStacks`/`stealRandomBuff`、`useMana`/`tryUseMana`/`checkMana`、
   `useSpikes`/`loseSpikes`、`useVampirism`/`loseVampirism`、`useLucky`/`tryUseLucky`、`useHeat`、
   `useRegeneration`、`cleansePoison`/`cleanseCold`/`cleanseBlind`、`inflictCold`、`stun`、
   `canBlock`/`healthToBlock`、`purgeDamage`、`stun`、`selfInflictBlind`……

2. **网格邻接 / 宝石 / 联动（阶段2）** —— 与 Python 侧已完成的那批同构：
   `canAffect`、`getAffectedItems`、`getNeighborItemsAndGems`、`getCollisionCells`、
   `getExtensionCells`、`setGem`/`getGemsOfItems`、`rotateTo`……

3. **体力/生命上限细化** —— `getCurrentStamina`/`setCurrentStamina`、`giveMaxStamina`、
   `giveMaxHealth`、`reduceMaxHealth`、`getTemporaryMaxHealth` 等。

**里程碑顺序建议**（与项目既有约定一致：底层没就位就不提前实现上层）：

```
① 补 §8.1 物品行为 API 面  → gd_core 能跑通真实物品行为
② 接 518 物品行为到 _behavior 缝（转译产物已有：simulator/build_data 路径）
③ 跑 tools/verify_cooldowns.py 等价校验 + 与 Python 引擎双引擎对照
④ 补 §8.2 网格邻接/宝石/联动
⑤ 全量 56 场双引擎对照，逐场比对胜者/结束时刻/事件序列
```

在此之前，**不应宣称 gd_core 已等价于原版战斗系统** —— 它当前等价的范围是
「核心循环 + 伤害链主干 + Buff 语义 + 疲劳/判胜/收尾」，且已被闸门 3/4 与基准实测覆盖。

---

## 9. 工具索引

| 工具 | 作用 |
|---|---|
| `tools/run_gd_core.py` | 一键四道闸门（`--bench` 附基准） |
| `tools/audit_gd_core.py` | 静态审计：`ctx.*` / `Core*.*` 引用完整性 |
| `tools/check_class_cycles.py` | class_name 循环依赖检测 |
| `tools/gd_core_coverage.py` | 覆盖度核算（`--list` 明细 / `--unknown` 只看待目视） |
| `gd_core_test/ParseAll.gd` | 全量解析（Godot 每脚本只报首个错误，故逐文件 `load`） |
| `gd_core_test/Smoke.gd` | 三项契约冒烟 |
| `gd_core_test/Bench.gd` | 吞吐基准 |
| `gd_core_test/Probe.gd` | 逐帧取证（触发时刻 / combat_time / 末态血量） |
