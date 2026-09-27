# gd_core 忠实性真值表（无头解耦内核）

> 交付目标：把解包代码的战斗逻辑从 Godot 节点树 / 渲染 / 物理 / 音频 / UI / 单例中剥出来，
> 成为不依赖场景树的纯逻辑模块，**判定链路 1:1 不变**。
>
> 本文是该承诺的取证文档：每一处改动都能对到源码行号，每一处剥离都给出「为什么它不影响判定」。
> 生成日期：2026-09-22
> 2026-09-23 修订：§1 模块表校准（18 脚本 / 9046 行，补 `CoreItemBook`/`CoreTimer`）、
> §2 结论改「直挂」口径、§3.2 钩子数 51、§5 新增陷阱 3/4、§6 新增 15/16/17/18、
> §7 闸门扩至九道、§8 里程碑 ④ 结项、§9 工具索引重编
> 2026-09-27 修订：§5 新增陷阱 5（Socket 折叠与访问面枚举）、§6 新增 19（原版死代码照搬）、
> §7 闸门扩至十道（新增 `GemFacade`）、§8 **判定路径缺口归零**、
> `lineup_gem_test` 解锁（SKIP 理由经实证为陈旧）

---

## 1. 模块映射

`gd_core/` 共 18 个脚本、9061 行。所有模块 `extends Reference`，无一继承 `Node`/`Node2D`。

| gd_core 文件 | 行数 | 对齐源文件 | 说明 |
|---|---:|---|---|
| `CoreConst.gd` | 375 | `Core/Game.gd` 常量/枚举 | `Item.Type` / `Item.Stat` / `Item.FaceDirection` / `Item.Owner` / `Item.Affected` / `Character.Stat` / `Game.EventType` / `Game.Classes` 等归一，**为断 class_name 循环依赖而集中** |
| `CoreUtil.gd` | 279 | `Utility/Util.gd`（1683 行） | 战斗相关子集：`dictAdd/Sub/AddDict/Erase` + `sortDict`（+内部 `DictSorter`）+ `truth` + `changeTimer`，见 §6.14 |
| `CoreRng.gd` | 233 | `Util.rng` | 注入式随机源；`BalancedRng` / `BalancedRange` 包装器照搬 |
| `CoreEvent.gd` | 94 | `Core/CombatEvent.gd` | 12/13（余 1 为表现） |
| `CoreEventBus.gd` | 123 | `Game` 信号系统 | `connect_signal` / `emit_signal` 语义保留 |
| `CoreCombatLog.gd` | 339 | `Core/CombatLog.gd`（1279 行） | **只保留事件工厂**（34/96），见 §5 |
| `CoreItemData.gd` | 307 | `Items/ItemDescriptor.gd` | 描述符**实例形态**：`getP` / `paramBases` 双向表 / `addNamedParam` |
| `CoreItemBook.gd` | 197 | `Sheets/ItemBook.gd` | 描述符**注册表**（自动生成）：标识符 → 同一 `CoreItemData` 实例，保证 `isA` 的引用相等语义 |
| `CoreDamageSource.gd` | 212 | `Utility/DamageSource.gd` | 23/23 全覆盖 |
| `CoreDamageResult.gd` | 96 | `Utility/DamageResult.gd` | 14/14 全覆盖 |
| `CoreBuff.gd` | 398 | `Core/Buff.gd` | 14 → 18（多出的是 gd_core 侧辅助） |
| `CoreGrid.gd` | 245 | `Core/Inventory.gd`（1331 行） | **战斗相关子集**：格子映射 / 邻接 / 受影响格查询，见 §6.6 |
| `CoreItem.gd` | 3416 | `Items/Item.gd`（6573 行） | 冷却/触发/激活主干 + 伤害数值 + 宝石托管（Socket 折叠，§5 陷阱 5）+ **物品行为 API 面（422 方法）** |
| `CoreCharacter.gd` | 1670 | `Core/Character.gd` | 186/210；伤害链 / 治疗 / 格挡 / 疲劳 / 体力 / 眩晕 / 战怒 / 无敌 / 职业 |
| `CoreTimer.gd` | 125 | Godot 内建 `Timer` + `Utility/MultiTimer.gd` | **虚拟计时器**：物品 tscn 的 `timeout → buffEnded` 连接承载 buff 结束判定，不可当表现剥离 |
| `CoreContext.gd` | 237 | 新增（无源文件） | 单例注入点 + 延迟调用队列，见 §3.1 |
| `CoreHooks.gd` | 250 | 新增（无源文件） | 副作用钩子，51 个空实现，见 §3.2 |
| `CoreCombat.gd` | 465 | `Game.gd:2978-3032/3257-3379` + `Interface/CombatTimer/CombatTimer.gd` | 战斗驱动主循环 + 装配接口 |

运行入口：`gd_core_test/`（独立 Godot 工程，`gd_core` 以目录联接指向 `../gd_core`，保证单一真值来源）。

---

## 2. 一句话结论

**判定路径上的每一行都保留了；被删掉的全是「表现副作用」与「出战斗流程」（商店/合成/背包/存档/UI）。**

原版 `Items/**.gd` 的 503 份物品脚本**逐字不改地直接 `extends Item` 挂在 `CoreItem` 上**运行
（转译只做「视觉剥离 + 符号映射」，见 §5），驱动 518 件物品中的 **517 件可上场物品**
（余 1 件无独立脚本，属基类行为）。因此 gd_core 现在跑的是完整战斗：
核心循环 + 伤害链 + Buff + 网格邻接/朝向 + 计时器 + **517 件物品的真实行为**。

当前方法名覆盖率 `709 / 998 = 71.0%`（`CoreItem` 422/628、`CoreCharacter` 186/210），
**判定路径缺口 0 项**（最后一项 `initSockets` 已按「折叠后无事可做」闭合，见 §5 陷阱 5）。
「未收录」的 289 项经可达性定裁全部属既有剥离类别（商店/合成/拖拽/几何/日志 UI）。

★ 但「覆盖率」与「真的跑起来了」是两件事，本轮的两次实测都印证了这一点：
闸门 9（517 件逐一真打）首轮抓出 101 条运行期错误、二轮又抓出 288 条，
其中包含一处**成类静默失效**（§5 陷阱 3）—— 它让 98 件物品的开场回调
整整一轮都没被调用，而所有静态闸门与真实阵容闸门**全绿**。
同类教训在宝石上也出现过一次：`lineup_gem_test` 曾被标为 SKIP，解锁后**零报错通过**，
但零报错只说明「没走进宝石代码」，真正证明它生效要用 A/B 对照（§7 闸门 10）。


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

钩子共 **51** 个，分 7 组（`CoreHooks.gd` 内以 `# ── 组名 ──` 分隔）：物品层表现、
战斗计时器表现、角色层表现、角色状态表现、物品朝向／放置预览、统计埋点、战斗日志。
其中统计埋点（`addMetric` / `snapshot*` / `updateDamageMeter`）在原版也是纯采集，不回流判定；
朝向／放置预览组只服务装配期 UI，战斗期不读。

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
| Godot `Timer` 节点（无敌/战怒/自动战怒/游戏内 tick） | **改物理帧步进** | 超时点触发**同一方法**，见 §6.7 |
| 网格几何换算（`to_global`/`world_to_map`/`map_to_world`） | **折叠为格空间** | 等价性论证见 §6.6 |

**五条容易踩的剥离陷阱**（都已修，并写进了闸门）：

1. **剥离 ≠ 不留签名。** 物品行为脚本会**调用**某些表现方法（`miniActivate`、
   `moveTo`、`canCombine`、`insertCounter`、`resetZ`、`onGateItemRoll`…）。内核若不提供
   同签名，行为接入时直接 `Nonexistent function`。故这些方法在内核里以
   「同签名空实现 / 转发 hooks / 忠实返回判定值」保留 —— 逐个在源码行号上标注了剥离依据。
   其中 `canCombine()`（`Item.gd:5852` 恒返回 `placed`）与 `reactToItemTypeChange()`
   （基类恒 `true`）**返回值参与判定**，必须忠实返回而非恒 false。

2. **剥离与否要看调用点，不能看名字。** `onPrepare` / `onCombatEnd` 在 `Skill.gd` 之外的
   `CombatLog.gd` 里也有同名方法（日志面板用），只看名字会把日志 UI 误判成物品回调。
   定裁用 `tools/gap_audit.py`（调用闭包）而非关键词，见 §9。

3. **★ 行为接缝必须两极：注入的 `_behavior` 优先，否则回落到物品实例自身。**
   原版这些调用本来就是打在物品自己身上的多态调用（`Item.gd:382 var me = self` →
   `:3400 me.onCombatStart()`、`:5158 me.onChargeReceived(charge)`；
   `hasStartofBattle()` 就是 `has_method("onCombatStart")`）。
   首版接缝只认注入对象，而**全工程只有 4 个合成测试（Smoke/GridSmoke/Bench/Probe）
   会设 `_behavior`**，于是 `onCombatStart`(98 件) / `onDealtDamage`(21 件) /
   `onChargeReceived`(11 件) / `getGatedDescriptor` 等回调**全部静默不执行、零报错** ——
   闸门 8/9 当时只断言「有激活」，而激活来自 `doCooldownEffect` 的多态调用，
   压根不经过接缝，于是全套闸门绿着放过了它。实证：`PiggyofRiches.onCombatStart`
   调 `inventory.countSocketedGems()`（内核无此方法），闸门 9 逐一跑过它却一条错误都没有。
   现为**两级派发**（`CoreItem.SELF_BEHAVIOR_METHODS` 白名单 + `callv` 回落），
   并由 `tools/audit_gd_core.py` 检查项 5 与闸门 9 的「派发可达性」断言双重看住 (2026-09-23)。

   ★ 白名单**只含基类未定义的名字**：与基类同名的（`canAffect` / `doCooldownEffect` /
   `getTriggerPriority` / `getAffectedCellsAfterRotate_*` / `ready_deferred` /
   `reactToItemTypeChange` …）是虚方法覆写点，GDScript 多态已经打到物品脚本上，
   接缝再回落会变成**自我递归**（`CoreItem.doCooldownEffect` 的整个函数体就是
   `_behavior_call("doCooldownEffect")`）。

   同一处还有第二个「双闸门挡死」：`hasPreDealDamageEarlyEffect` 等 5 个钩子存在性标志
   **从未被赋值**（恒 false）。原版是 `onready var ... = has_method(...)`（`Item.gd:500-504`），
   内核等价位置是 `CoreItem._readyInit()`，已补。

4. **★ 纯表现表达式不得夹带进判定路径 —— 哪怕它只是个函数实参。**
   `CoreBuff.gd` 的三处 `Util.spawnReflectLabel/ResistedLabel/ProtectedLabel(type, pos, …)`
   里 `pos = character.randBuffLabelPos()` 看着像纯取值，实则内部抽两次
   `Util.rng.randf_range`（`Character.gd:688-692`）。结果只喂给一个表现为空实现的钩子，
   却因此**平移了后续所有随机判定**。内核不变式是「写入 `ctx.rng` 的调用点都参与判定」，
   故三个钩子**去掉 `pos` 实参**（与 `CoreCharacter` 文件头「伤害数字坐标整体删除（纯表现）」
   同一政策）。这是**有意偏差**：不逐位复刻原版在表现层的 RNG 消耗。

5. **★ 场景树节点折叠成普通对象时，「折叠的完整边界」必须用调用面枚举来定，不能靠感觉。**
   原版宝石挂在**插座节点**上：`sockets = $Icon/Sockets.get_children()`（`Item.gd:309`），
   `gem.addToSocket(sockets[id])` 把该节点存进 `gem.socket`，而宝石的每个身份判定
   （`isOwnable`/`isPlaced`/`getInventory`/`getEffectiveOwnerType`）又都回到
   `socket.getItem()`（`Gem.gd:36-76`）。节点上有两个方向：`socket.item` 回指宿主
   （由 `Item.initSockets()` 装填）、`socket.gem` 指回宝石（由 `GemSocket.onDropGem` 装填）。
   内核无节点树，把插座身份**折叠为宿主物品本身**：`CoreItem.setGem` 把 `self` 当 socket
   传下去，`CoreItem.getItem()` 恒返回 `self` —— 于是 `socket.item = self` 这条后置条件
   **恒真**，`initSockets()` 成为「无事可做」而非「遗漏」（内核保留其签名并注明折叠依据，
   覆盖度缺口据此归零）。
   **判断折叠够不够的唯一可靠办法是枚举宝石对 socket 的实际访问面**：
   `grep -rn "socket\." gd_core_items/` 得 15 处，战斗路径上**只有** `socket.getItem()`；
   其余（`onPickupGem` / `socket.gem = null` / `hideSocket`）全在拖拽与丢弃路径上，
   战斗内不可达。故折叠完整。★ 反过来说：将来若有行为脚本用上 `socket.getGem()`，
   折叠就会漏（一颗宝石无法回答「我是第几个插座」）—— 那时必须按 socketId 建门面。
   与陷阱 3 同构的是它的**静默性**：折叠若没接上，宝石会安安静静跑完一整场却不产生任何效果，
   一行报错都没有。故单独立闸门 10 逐条取证（含公式级数值与三种模式的 A/B）。

原版 `Item.gd` 628 个方法中，178 项按类别属解耦剥离；`CoreItem` 收录 422 项，
**判定路径缺口 0 项**（数字来源与含义见 §7、§8）。

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

6. **坐标系统一折叠为「格空间」。** 原版受影响格是「格 → 全局坐标 → 再回格」的往返
   （`getAffectedPoints()` = `getGlobalPointsForCells(tile高) + getAffectedCells_noRotate()`，
   后者又经 `getCollisionPoints()` → `getCellsForGlobalPositions()`）。逐段代入可见两次往返
   各自把格心映射回自身（`floor(格心/cellSize)` 恒等于该格），净效果即格空间集合运算。
   内核据此剥离全部 `to_global`/`world_to_map`/`map_to_world`/`halfCellSize`。
   **风险**：若某物品的 `collisionMap` 相对背包 TileMap 存在非整格偏移，会引入一格错位。
   项目已有等价模型 `simulator/grid.py`（47 套真实阵容零冲突），后续以此逐项比对证伪。

7. **三个 Godot `Timer` 节点 → 物理帧步进。** `InvulnerabilityTimer` / `BattleRageTimer` /
   `AutoRageTimer` 在 `Character.tscn` 里以信号连接驱动（`:1668-1670`），且都是 `one_shot`。
   内核改为在 `physicsTick` 里递减，**超时点触发同名方法**（`invulnerabilityEnded` /
   `endBattleRage` / `startAutoRage`），状态迁移次序与原版一致；差别只在计时精度来自定步长。
   之前的缺口是致命的：`_invul_left` 只写不推进，**无敌永不结束**。
   `Util.changeTimer(timer, t)` = `start(t + timeLeft)` 的**延长**语义也已照搬
   （已无敌/已战怒时再触发是延长而非覆盖）。

8. **`faceDirection` 提升为权威字段，`rotation` 成为派生值。** 原版没有 `faceDirection`
   字段的来源：它是 Node2D 的 `rotation`（带 tween 插值）经
   `getFaceDirection() = (int(2*rotation/PI + 2.25PI) + 5) % 4` 量化出来的。内核无节点、
   无插值，故令 `rotation = faceDirection * PI/2` 恒成立 —— 代人原式恒等。
   **这是判定输入**：`SpintoWin.doCooldownEffect/gainsStack` 按方向分流 Heat/Lucky/
   Regeneration/Mana（`SpintoWin.gd:33-52`），`LongSpear.gd:6-7`、`RainbowPotion.gd:17/96/98`
   同样按方向分流。战斗期该字段只读（`rotateLeft/Right` 只由玩家按键触发）。

9. **`_behavior_call` 必须回传返回值。** 曾漏写 `return`，导致 `canAffect` 全员静默判否
   （全部联动物品失效）而**不报任何错**。已加静态闸门：`VALUE_RETURNING_BEHAVIORS`
   清单里的方法，其派发点必须以 `return` 开头（`tools/audit_gd_core.py` 第 4 项）。

10. **`bool(x)` 是 GDScript 4 的构造式**，3.x 无此内置，直接调用运行期报
    `Nonexistent 'bool' constructor`。内核统一用 `CoreUtil.truth(x)`（语义 = GDScript 条件真值）。
    同样进了静态闸门（`tools/audit_gd_core.py` 第 5 项）。

11. **`CoreCombat.prepareItems` 不清空、不重复登记背包。** 原版物品在**商店/摆放阶段**
    就已 `Inventory.addItem` 入包，`Game.gd:3023` 的 `prepareItems` 只做 prepare。
    若在 prepareItems 里 `cleanUp()`，会连放置期建好的格子映射与受影响集一并抹掉
    （`Character.prepare` 的自动战怒选品正是读这个背包）。
    需要干净重开一场时由装配层显式调 `resetInventories()`。

12. **反编译标注可能不可信。** 例：`Character.gd:195` 写作 `func isChibi() -> int:`
    但函数体返回 bool 字段 `chibi` —— 原版源码不可能编译通过，该标注是反编译器补的。
    内核去掉标注保留语义。凡「照抄反编译文本却编译不过」的地方，先怀疑标注。

13. **原版疑点一律照搬不修**，例如 `CombatLog.createEvent_BattleRageEnd` 把
    `Game.EventType.BattleRageEnd` 当 `origin` 传入；`createEvent_StackTemporary` 先调
    5 参版本再补 `reflected`。修复它们反而会偏离原版。

14. **`sortDict` 原文不可复现，内核改为注入 RNG 可复现。** 原版
    `sortDict(dict, shuffleBeforeSort=true)` 用 `Array.shuffle()`（走 Godot 全局 RNG）
    再做 Godot 非稳定的 `sort_custom`。内核改为「注入 rng 洗牌 + 稳定降序」，
    取值域相同（同为按值降序），仅同值并列次序不同。全仓库只有
    `Item.getStackFraction`（`Item.gd:5642`）用到该分支。

15. **★ `descriptor.params` 必须按列对齐（定长 10），紧凑数组是错的。**
    原版 `ItemBook.gd:855-875` 对 `p1..p10` **每一列**取值 push_back（空列 push 默认 0），
    故 `const NUM_PARAMS = 10` 且 `params[i]` 恒等于第 (i+1) 列 ——
    `getP1() = getP_check(0) = params[0]` … `getP10() = params[9]`。
    早先 `simulator/build_data.py` 的提取**跳过空列**，于是「前面有空列」的物品整体错位：

    | 物品 | CSV 实际列 | 紧凑数组（错） | 后果 |
    |---|---|---|---|
    | Carrot | `p2=4:luckt` | `[4.0]` | `getP2()` 越界报错；`getP1()` 错得 4.0 |
    | Poison Ivy | `p1,p2,p4` | `[18,25,2]` | `getP4()` 错得 2.0 |
    | Dark Lantern | `p1,p2,p3,p5` | `[50,50,1.3,7]` | `getP5()` 错得 0.0；`getP4()` 错得 7.0 |
    | Brass Knuckles | `p1,p2,p4` | `[0.3,5,50]` | `getP4()` 错得 50.0 |

    **静默偏值比报错更危险**（越界才报错，错位不报）。修正入口：生成器
    `simulator/build_data.py` 已改走 `tools/item_sheet.py` 的 `aligned_params()`；
    已生成的 `assets/battle_items.json` 由 `tools/align_item_params.py` 定点重写
    （只改 `params` 一个字段，全文件 diff 仅 518 处，无其它字段漂移）；
    `tools/gen_lineup_fixture.py` 在消费点断言 `len(params) == NUM_PARAMS`。
    两个 Python 引擎的 56 场回归基线与修正前**逐位一致**（该轮修复只影响未被
    这些固定阵容用到的物品）。

16. **Godot 报错定位的判读陷阱（不是偏差，是工具坑）。** `SCRIPT ERROR` 形如
    `at: <函数名> (res://<脚本路径>:<行号>)`，其中**行号取自函数真正定义的那个脚本，
    路径取的却是运行期实例的脚本**。于是内核方法出错时会打印成
    `at: getP_check (res://gd_core_items/PoisonIvy.gd:1441)` ——
    而 `PoisonIvy.gd` 只有 51 行，1441 指的是 `CoreItem.gd`。
    判读一律按「函数名 + 行号」回内核脚本里找。已记入 `tools/run_gd_core.py` 文件头。

17. **★ 生成代码里不许写死「核算结论」—— 它必然过期，而且会冒充证据。**
    `gd_core_items/Item.gd` 是自动生成的，文件头自称「内容随代码同步」，
    但里面写死了三项字面量：

    | 文件头写死的内容 | 2026-09-23 实测 | 性质 |
    |---|---|---|
    | `6573 行 / 628 方法` | 恰为 6573 / 628 | 当时对，源文件一改就错 |
    | `469 个原版物品脚本` | **502** 个脚本（其中 238 个直接 `extends Item`） | **早已失真** |
    | `判定路径缺口为 0` | 缺口 **1** 项（`initSockets`） | **假断言** |

    > 顺带一个提醒：该项在 2026-09-27 已**真的**变成 0。这恰恰说明「写死结论」的
    > 危险性 —— 一份曾经为假的断言，会在一段时间后**偶然变成真**，
    > 而读代码的人无从分辨它写下时到底是哪一种。

    第三项最危险：它把「某一时刻的核算结果」固化成了生成物的一部分，读代码的人会
    以为**当前**已验证过。修法是把 `SHIM_HEADER` 常量改成现算函数 `shim_header(outputs)`
    （行数/方法数从 `decompiled_full/Items/Item.gd` 读，脚本数与直接子类数从本次
    `outputs` 统计），并写明「覆盖率与判定路径缺口不在注释里断言，以
    `tools/gd_core_coverage.py` 的现场核算为准」。顺带修掉生成器自身文档头与
    4 处行内注释里的同类陈旧数字。
    **判据：「生成物里出现的数字，必须是生成那一刻算出来的」** ——
    凡需要另一个工具才知道的结论，只能**指向**那个工具，不能抄结论。
    （修完复跑：生成物字节幂等；九道闸门全绿，触发合计仍为 7108 次 —— 证明改动纯在注释层。）

18. **压缩已到地板 —— 有度量，不靠感觉。** `tools/measure_dead_weight.py` 给出可复现的数字：

    | 范围 | 死残留 | 总量 | 占比 |
    |---|---:|---:|---:|
    | `gd_core`（手写内核） | 26 行 | 9067 行 | **0.3%** |
    | `gd_core_items`（自动生成） | 304 行 | 20244 行 | **1.5%** |
    | 合计 | 330 行 | 29311 行 | 1.1% |

    「死残留」= 空桩函数 + 未被引用字段，判据**刻意保守**（动态派发敏感名单 +
    跨文件同名互认 —— 例：`playAttackAnimation` 在 `CoreHooks` 有定义，那么物品脚本里
    对它的空覆写就不算零引用）。故真实可删量只会更小；且其中大头（**125 行，占全部
    死残留的 38%**）集中在适配层 `gd_core_items/Item.gd`，多为
    `onready var X = $Particles` 剥成 `var X` 后的字段残迹 ——
    它们支撑着「原版脚本逐字不改」所需的成员面。

    三条结论：

    ① 手写内核已基本没有冗余可削（0.3%），继续「精简」更可能伤到保真；
    ② 唯一值得做的清理是**规则级**的（在生成器里加剥离规则并重跑），不是逐行删；
    ③ 逐行删的风险大于收益：物品脚本里 328 个空桩函数看似垃圾，实为原版
       `has_method()` 动态派发的落点，删了会让回调**静默失效**（§5 陷阱 3 的同类）。
       按项目既定原则「宁可少删」，该工具**只报告、不删除**。

19. **原版自带的死代码要照搬，且不要给它立契约。** `Gem.isInInventory()`（`Gem.gd:72-76`）
    覆写了一个 `Item` 上**并不存在**的方法：`socket != null` 分支调
    `socket.getItem().isInInventory()`，`else` 分支调 `.isInInventory()` ——
    而 `grep -rn "func isInInventory" decompiled_full/` 只命中 `Gem.gd` 自身，
    且全仓库无任何调用点。也就是说**这条 else 分支在原版里也会运行时报错**，
    只是没人走到。内核逐字保留其形状（转译产物同样如此），
    闸门 10 **刻意不为它写断言** —— 给死代码立契约会把它固化成「必须可调用」，
    反而制造出一个原版没有的约束。判据：**照搬事实，但只给活路径立契约。**
    （`initSockets` 与它相反：**看似死、实为活** —— 详见 §5 陷阱 5。）

---

## 7. 验收方式与当前结果

一键流水线：

```bash
python tools/run_gd_core.py          # 十道闸门
python tools/run_gd_core.py --bench  # 附吞吐基准
```

| # | 闸门 | 工具 | 当前结果 |
|---|---|---|---|
| 0 | 四支幂等生成器全量前置（描述符注册表 / 物品脚本转译 / 阵容夹具 / class_name 注册表） | `gen_core_item_book.py` → `build_item_scripts.py` → `gen_lineup_fixture.py` → `gen_test_project.py` | 通过 |
| 1 | 静态审计：`ctx.*`/`Core*.` 引用 + 行为派发返回值 + **行为派发落点可达** + `bool()` 误用 | `tools/audit_gd_core.py` | 通过（0 问题） |
| 2 | class_name 依赖环 | `tools/check_class_cycles.py` | 通过（0 环） |
| 3 | 内核脚本在 Godot 3.6 下全量解析 | `gd_core_test/ParseAll.gd` | 通过（failed=0） |
| 4 | 四项契约冒烟（含计时器契约） | `gd_core_test/Smoke.gd` | **PASS** |
| 5 | 四项网格子系统契约（含朝向契约） | `gd_core_test/GridSmoke.gd` | **PASS** |
| 6 | 物品脚本全量解析（503 个） | `gd_core_test/ItemParseAll.gd` | 通过（0 错误） |
| 7 | 单例门面契约（描述符身份 / 库存查询 / 包装层 / Game 状态量 / combatTimer 身份） | `gd_core_test/FacadeSmoke.gd` | **PASS** |
| 8 | 8 套真实阵容端到端（**56 局**全矩阵 + 确定性复跑 + **宝石实效 A/B**） | `gd_core_test/LineupBattle.gd` | **PASS** |
| 9 | **517 件可转译物品逐一真打一场** + 派发可达性断言 | `gd_core_test/ItemBattle.gd` | **PASS** |
| 10 | **宝石 / Socket 门面契约**：折叠等价性 / `getGemMode` 四分支 / 三种模式公式级效果 / 自身冷却自行触发 | `gd_core_test/GemFacade.gd` | **PASS** |
| — | 覆盖度核算 | `tools/gd_core_coverage.py` | 709/998 = 71.0%，**判定缺口 0** |
| — | 数据不变量 | `tools/align_item_params.py --check` | 通过（params 全 518 件已按列对齐） |
| — | 压缩度量 | `tools/measure_dead_weight.py` | `gd_core` 0.3% / `gd_core_items` 1.5% |

**闸门 9 的存在理由（本轮最大教训）**：前面八道全绿时它首轮仍抓出 101 条运行期错误、
修完第一批后第二轮又抓出 288 条。因为

* 闸门 6 只证明脚本**解析得了**，不证明「装上之后跑得起来」；
* 闸门 8 的真实阵容只覆盖 16 件物品，某件物品特有的分支永不触发；
* Godot 3 遇到 `Nonexistent function` / `Invalid call` **只打一行 SCRIPT ERROR 就中断
  当前函数继续跑**，退出码仍是 0 —— 于是「某行判定静默不执行」在任何只看
  「通过/失败」的闸门里都是隐形的，只有外层 stdout 扫描能抓（`scan_errors=True`）。

它抓到的三类问题按「危险度」排序：

| 类型 | 实例 | 为什么静态闸门看不见 |
|---|---|---|
| **成类静默失效** | 行为接缝只认注入对象 → 98 件 `onCombatStart`、21 件 `onDealtDamage` 从不执行 | 解析通过；且激活数来自另一条多态路径，非零 |
| **数据错位** | `params` 紧凑数组 → `getP1..getP10` 整体错位 | 越界才报错，错位静默偏值 |
| **映射错** | `GemMode.` → `CoreConst.GemMode.`（不存在） → 22 支宝石/符文的 `getGemMode()` 全断 | 只在运行期解引用时炸 |

闸门 9 另新增**派发可达性断言**：对每件物品，凡脚本里实现了
`onCombatStart` / `onPreDealDamage_early` / `onPreDealDamage_late` / `onDealtDamage` /
`onChargeReceived` / `onChargeLeft`，就必须被内核的派发判定看见
（实测 212 处回调实现，全部可见）。这条断言正是 §5 陷阱 3 的回归护栏。

**闸门 10 的存在理由（宝石的「零报错假通过」）**：`lineup_gem_test` 曾被标为 SKIP，
理由是「Socket 门面未建」。实际解锁后**一次就零报错通过**（8 套阵容 56 局）——
但复核发现：**零报错不等于宝石生效**。若折叠链断在任意一环
（`setGem` 没接上 / `getGemMode` 判错 / `prepareWeapon` 没跑 / `attacked` 没派发），
宝石会安静地跑完整场而什么都不做，一行错都不报。故补两道独立取证：

* **闸门 8 的 `test_gem_effect`（存在性）**：同种子 A/B —— 含宝石 / 去宝石。
  要求含宝石侧 `gem_heals > 0`、去宝石侧**恒为 0**（后者同时校验探针归属判据没误伤），
  且含宝石侧治疗总数高于对照局。实测：`gem=4/4.0`、`heal=7/24.0`，
  战局从 `t=14.88 php=30` 变为 `t=10.98 php=34` —— 宝石确实改变了结果。
* **闸门 10 `GemFacade`（公式级）**：用合成数值把每一步都控住 ——
  伤害 100 → `ceil(100×7%) = +7`；伤害 57 → `ceil(3.99) = +4`（验取整方向是向上而非四舍五入）；
  未命中 → 不治疗；`miniActivate` 与治疗**一一对应**。另验 `getGemMode` 四分支
  （Weapon/Armor/Inventory/Inactive）、`hasCooldown` 只在 Inventory 侧为真、
  Armor 分支**不得**订阅 `attacked`（反向卡门，防分流写反两边都「跑得通」）、
  Inventory 模式的**自身冷却能自行触发**（推帧到 5.15s，对手 −4、自身 +6）。

两者互补且不可互替：真实对局里伤害受 buff/暴击影响，只适合断言方向与存在性；
公式与取整方向只有在受控数值下才断言得了。

**闸门 3 的一个坑（已修）**：`load()` 对**有解析错误**的脚本不一定返回 null —— Godot 会
回一个残缺脚本对象，其 `get_script_method_list()` 为空。只判 `null` 会漏掉真错误
（曾漏掉 `CoreCharacter` 的一处语法错误，闸门假通过）。现在「方法数为 0」一并判失败。

**闸门 4 实测**（`gd_core_test/smoke_result.txt`）：

```
[1] 基础对拼：玩家 2 武器(5dmg/1.0cd) HP100  vs  对手 1 武器 HP20
    fight_ended=True  result=0(Win)  用时=1.95s  首击=0.983s
    HP  player=95.0  opponent=0.0
[2] 疲劳契约：双方空手 HP30 → 24.02s 收场，fatigue_counter=8，双死判玩家胜
[3] 确定性：同种子两场逐位一致（0|7.9667|6.0|0.0|0）
[4] 计时器契约：无敌按时结束 / 已无敌时延长 / 战怒按时结束 / applyBonus /
    已战怒时延长 / AUTO_RAGE_DELAY=5.0s 自动开大 → AUTO_RAGE_DUR=4.0s 结束
SMOKE: PASS
```

**闸门 5 实测**（`gd_core_test/grid_result.txt`）：

```
[1] 受影响格判定链：命中格 3 个 → canAffect 闸门后 2 个（非武器被挡）→ 快照
    → getFirstAffectedItem 随加入次序变化（SwordA / 调换后 SwordB）
[2] 邻接：四邻域去重 6 格、排除自身占格、邻接物品 [SwordA, SwordC]
[3] 确定性：同装配次序 + 同种子两位逐位一致（2|2|3|SwordA）
[4] 朝向：四方向写入 getFaceDirection 同值、rotation = fd×90°、
    四方向分流出 4 种不同效果、rotateLeft/Right 回绕正确
GRID: PASS
```

三项断言覆盖：冷却抖动区间、疲劳时序（17s 首发 + 1s 递增 1,2,3…8 累计 36 > 30）、
判胜与收尾（败者归 0 / 胜者至少 1）、同种子确定性。

**吞吐基准**（`gd_core_test/bench_result.txt`，加速比 = 模拟秒 / 墙钟秒，60Hz 实时 = 1×）：

| 场景 | 加速比 | 单帧成本 |
|---|---:|---:|
| 双方各 2 武器 3dmg/0.8cd | 92× | 137 µs |
| 双方各 4 武器 3dmg/0.8cd | 57× | 179 µs |
| 双方各 6 武器 5dmg/1.0cd | 41× | 247 µs |
| 双方空手（纯疲劳 24s 场） | 358× | 42 µs |

> ⚠️ **口径与波动说明**：
> · 本机为共享负载，同一场景两次运行的墙钟差最高达 2×（首轮实测区间为 33×–546×）；
>   **绝对倍数不可复现，只有量级可信**。
> · 这是**相对 60Hz 实时**的倍数，来自「脱离场景树后不再有渲染/物理/音频/节点调度」。
> · 未做「gd_core 相对原版场景树」的倍数断言 —— 那需要在游戏内实测，此处不臆测。
> · 单帧成本随物品数近似线性增长（2→6 把武器约 1.8 倍），符合「逐物品遍历冷却 + 事件工厂」的预期复杂度。
> · 本轮补入网格邻接/朝向/计时器后，单帧成本与首轮同量级（2 武器：79-154 µs → 137 µs），未见劣化。

---

## 8. 尚未完成（下一步的输入）

`tools/gd_core_coverage.py` 的方法名覆盖率是 **709 / 998 = 71.0%**，分层看：

| 模块 | 覆盖率 |
|---|---|
| `DamageSource` / `DamageResult` / `Buff` / `Event` / `EventBus` / `Rng` | **100%（Buff 为超集）** |
| `CoreCharacter` | 186 / 210 |
| `CoreItem` | 422 / 628 |
| `CoreCombatLog` | 34 / 96（**有意**只留事件工厂） |

**判定路径缺口：0 项。** 最后一项 `CoreItem.initSockets` 已按「折叠后无事可做」闭合
（等价性论证与访问面枚举见 §5 陷阱 5，验收见闸门 10）——**它从来不是遗漏，而是折叠的必然结果**。
里程碑 1（物品/角色行为 API 面）与里程碑 4（网格邻接/受影响格/朝向）已闭合，剩余
`待目视 64 项` 经可达性定裁全部属既有剥离类别（商店/合成/拖拽/几何/日志 UI），其中相当
一部分是**同名误报**（如 `onPrepare`/`onCombatEnd` 在 `CombatLog.gd` 里也有同名方法，
属日志面板）。

> **口径提醒**：上表的「收录」是**方法名集合差**，度量的是「内核自己写了多少」。
> 自里程碑 ④ 改为**直挂方案**后，517 件原版物品脚本以 `extends Item` 的形式直接跑在
> `CoreItem` 之上，它们携带的方法**不计入该表**——即真实的判定路径覆盖比 71.0% 更高。
> 该表的价值是守住「基类不许有洞」，不是衡量整体能力。

**里程碑进度：**

| 里程碑 | 状态 |
|---|---|
| ① 物品／角色行为 API 面（Item 176 + Character 35 项缺口） | **完成**（缺口 0） |
| ② 网格邻接 / 宝石 / 联动（原 §8.2） | **完成**（`CoreGrid` 20 方法 + `CoreItem` 邻接块，闸门 5 覆盖） |
| ③ 朝向 / 计时器 / 类型变化重建 | **完成**（§6.7-6.9） |
| ④ 接 518 物品行为到内核 | **完成**（**直挂方案**，见下） |
| ⑤ Socket 门面 + 宝石阵容解锁 | **完成**（折叠方案，闸门 8 的 A/B + 闸门 10 覆盖） |
| ⑥ `verify_cooldowns` 等价校验 + 与 Python 引擎双引擎对照 | **下一步**（缺口已归零，无阻塞） |
| ⑦ 全量双引擎逐事件对照（胜者/结束时刻/事件序列） | 待 ⑥ |

**里程碑 ⑤ 的形态：折叠，而不是「补一个 Socket 类」。**

原版宝石挂在**插座节点**上（`GemSocket.gd`，`Node2D`，有 `item`/`gem` 两个字段 +
`getItem`/`getGem`/`onDropGem`/`onPickupGem`）。内核的做法是把插座身份**折叠为宿主物品本身**：
`CoreItem.setGem` 把 `self` 当 socket 传给宝石、`CoreItem.getItem()` 恒返回 `self`。
**依据是访问面枚举**：`grep -rn "socket\." gd_core_items/` 得 15 处，战斗路径上只有
`socket.getItem()`，其余全在拖拽/丢弃路径（战斗内不可达）。
于是 `setGemData`（存档序列化，唯一消费方 `Game.gd:1382/1407/1423` 的 `saveRunState`）
与 `initSockets`（后置条件恒真的回指）**本就不参与战斗**，无需在内核里存在，
而 `lineup_gem_test` 也随之解锁。完整论证见 §5 陷阱 5，验收见闸门 8 的 A/B 与闸门 10。

**里程碑 ④ 的最终形态：直挂，而非「把行为搬进 `_behavior`」。**

`CoreItem._behavior` 的契约是 `hasBehavior(item, methodName) -> bool` +
`callBehavior(item, methodName, args) -> Variant`（**必须回传原值**）。但它现在**只是
合成测试用的注入口，不是物品的必经之路**：

- `tools/build_item_scripts.py` 把 `decompiled_full/Items/**.gd` 逐字转译到
  `gd_core_items/`，**只做视觉剥离 + 符号映射，一行逻辑都不改写**；
- 转译产物 `extends Item`（`Item` 再挂 `CoreItem`），0 参构造 + 显式 `setup()`；
- 于是 `doCooldownEffect` / `canAffect` / `getTriggerPriority` 等**靠 GDScript 多态
  直达物品脚本的覆写**，压根不经过 `_behavior`；
- 而 `onCombatStart` / `onDealtDamage` / `onChargeReceived` 这类**基类没有定义的
  回调**，原版是靠 `has_method()` 动态派发的（`Item.gd:3390-3391`、`:382`+`:3400`、
  `:5158`、`:500-504`），内核照抄同一套 —— 详见 §5 陷阱 3。

**为什么必须保留 `_behavior` 且做成两级**（这条是踩过坑才写下的）：早先只留 `_behavior`
一条路，而**没有任何物品脚本被注入它**（全工程只 `Smoke`/`GridSmoke`/`Bench`/`Probe`
四个合成测试会设），结果 98 件 `onCombatStart`、21 件 `onDealtDamage`、11 件
`onChargeReceived` 的回调**全部静默不执行、且零报错** —— 闸门 8/9 当时全绿也看不见，
因为它们只断言「有激活」，而激活来自 `doCooldownEffect` 的多态调用，那条路不经过本接缝。
现在的两级派发（注入优先 → 回落 `callv` 打物品自身）配合两道永久守卫
（`audit_gd_core.py` 检查项 5、`ItemBattle.gd` 派发可达性断言）把这个洞封死了。

**里程碑 ④ 的一个待定项（数据未就位，暂不实现）**：`Item.isBattleRageItem()` 依赖
`descriptor.hasBattleRageEffect`，其来源是 `ItemBook.gd:1401` 从**描述文本**里找
`"$rage["` 标记；`assets/battle_items.json` 目前没有导出该标记，故内核该字段默认 `false`
（等价于当前游戏实际数据下「没有物品能触发自动战怒」这一状态）。装配层若能提供
`hasBattleRageEffect` 键即自动生效 —— 机制已忠实实现，不臆测数据。

**判定路径缺口已归零**（2026-09-27）：最后一项 `initSockets` 按「折叠后无事可做」闭合，
见上方里程碑 ⑤ 与 §5 陷阱 5。这意味着**里程碑 ⑥⑦ 已无阻塞**：可以开始做
`verify_cooldowns` 等价校验与「gd_core ↔ Python 引擎」的逐事件对照了。

在此之前，**不应宣称 gd_core 已等价于原版战斗系统**。它当前等价的范围是
「核心循环 + 伤害链主干 + Buff 语义 + 网格邻接/受影响集 + 朝向 + 计时器状态 +
疲劳/判胜/收尾 + **517 件原版物品脚本逐字不改直挂运行** + **宝石三模式与 Socket 折叠**」，
已被闸门 3/4/5（合成契约）、闸门 8（真实阵容 56 局 + 宝石 A/B）、
闸门 9（517 件全量逐一上场）、闸门 10（宝石公式级）覆盖。**尚缺的证据**是里程碑 ⑥⑦：
与 Python 引擎的逐事件对照 —— 在那之前，「等价」只是「无已知偏差」，不是「已证明无偏差」。

---

## 9. 工具索引

### 验收与守卫

| 工具 | 作用 |
|---|---|
| `tools/run_gd_core.py` | **一键十道闸门**（`--bench` 附基准；`--only N` 单闸重跑） |
| `tools/audit_gd_core.py` | 静态审计：引用完整性 + 行为派发返回值 + `bool()` 误用 + **派发落点可达** |
| `tools/check_class_cycles.py` | class_name 循环依赖检测 |
| `tools/gd_core_coverage.py` | 覆盖度核算（`--list` 明细 / `--unknown` 只看待目视） |
| `tools/gap_audit.py` | **缺口定裁**：调用闭包可达性，替代关键词启发式 |

### 代码生成与数据管线

| 工具 | 作用 |
|---|---|
| `tools/build_item_scripts.py` | 原版 `Items/**.gd` → `gd_core_items/` 转译（视觉剥离 + 符号映射） |
| `tools/item_sheet.py` | **原版权威物品表单一入口**：自动 GDEC 解密 + `p1..p10` 按列对齐 |
| `tools/align_item_params.py` | 定点重写 `assets/battle_items.json` 的 `params`（`--check` 幂等校验） |
| `tools/gen_lineup_fixture.py` | 生成 `lineup_battle_fixture.json`（消费点断言 `params` 定长 10） |
| `tools/gen_test_project.py` | 自动重生成 `gd_core_test/project.godot` 的 class_name 注册表 |
| `tools/dump_methods.py` | 从原版抽指定方法的完整源码体（含起止行号），做移植底稿 |
| `tools/measure_dead_weight.py` | **精简度体检**：死桩函数 / 未引用字段的占比（只报告不删除，见 §6.18） |

### 闸门脚本（`gd_core_test/`）

| 脚本 | 作用 |
|---|---|
| `ParseAll.gd` | 全量解析（Godot 每脚本只报首个错误，故逐文件 `load`） |
| `Smoke.gd` | 四项契约冒烟（基础对拼 / 疲劳 / 确定性 / 计时器） |
| `GridSmoke.gd` | 四项网格契约（受影响格判定链 / 邻接 / 确定性 / 朝向） |
| `FacadeSmoke.gd` | 门面契约（物品/角色/网格三类对外接口的形状与默认值） |
| `ItemParseAll.gd` | 517 件转译脚本逐个 `load` + 描述符绑定 |
| `LineupFixture.gd` | **生成物**：`lineups/*.json` → 内联描述符/占格/受影响格（含宝石与脚本路径） |
| `LineupBattle.gd` | 8 套真实阵容对拼（56 局矩阵 + 确定性复跑 + **宝石实效 A/B**） |
| `ItemBattle.gd` | **全物品逐一上场**：517 件各 1 场，兼派发可达性断言 |
| `GemFacade.gd` | **宝石 / Socket 门面契约**：折叠等价性 / `getGemMode` 四分支 / 三模式公式级效果 |
| `Bench.gd` | 吞吐基准 |
| `Probe.gd` | 逐帧取证（触发时刻 / combat_time / 末态血量） |

### `tools/gap_audit.py` 的判据（重要）

覆盖度核算的关键词启发式只能回答「这个名字像不像战斗方法」，回答不了「谁在调它」。
`gap_audit.py` 建立**调用图**后从判定路径入口做闭包：

1. 解析 `decompiled_full/**/*.gd`，按顶层 `func` 归属建立 `(文件, 函数) → {被调名}`；
2. 种子 = ① `gd_core` 已收录方法 ② `Core/Combat.gd` 与 `Items/**.gd` 的全部函数；
3. 被调名**只解析到判定路径文件**（`Items/Item.gd`、`Core/Character.gd`、`Core/Buff.gd`、
   `Core/CombatLog.gd`、`Utility/Damage*.gd`、`Core/CombatEvent.gd`）内的定义；
4. 种子节点只**展开自身**、其名字不记为「被调用」—— 否则 `Items/X.gd` 对 `Item.gd`
   方法的**覆写**会被反向解析成「有人调了 Item.gd 的它」，把大批 UI 方法误判成可达。

用法：

```bash
python tools/gap_audit.py                      # 闭包定裁 + 必须补/合法剥离清单
python tools/gap_audit.py --detail <名>...     # 看某方法的定义与全部调用点
cat 名单.txt | tr '\n' ',' | python tools/gap_audit.py --reach   # 只判给定名单
```

**已知局限**：`--reach` 是名字级上界，跨文件同名会误报（例：`CombatLog.gd` 的
`onPrepare`/`onCombatEnd` 与 `Item.gd` 的同名）。误报方向是「要求多补」，不会漏判。
判定某个方法该不该补，最终仍以其**调用点上下文**为准（`--detail` 给出源码行）。

