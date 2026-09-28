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
> 2026-09-28 修订：§6 新增 21（`stun()` 信号派发缺失——本轮唯一实锤联动断点，
> 已修复并端到端验证）、§6 新增 22（zh 渲染层「以显示」机翻兜底——显示层偏离，不改判定）

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

20. **`isCooldownActive()` 换了机制：显式标志 vs 引擎谓词。** 原版这一句是

    ```gdscript
    decompiled_full/Items/Item.gd:3765   func isCooldownActive() -> bool:
    decompiled_full/Items/Item.gd:3766       return is_physics_processing()
    ```

    内核没有场景树，改为显式标志 `_cooldown_active`（`activateCooldown()` / `deactivateCooldown()`
    与 `combatEnd()` 三处设值）。

    **Godot 3.6 实测（探针）**：脚本里定义了 `_physics_process` 的节点，**入树后
    `is_physics_processing()` 为 `True`**（裸 `Node2D` 为 `False`；`set_script()` 与
    `PackedScene.instance()` 两条路径结果相同）。而 `Item.gd:4453` 正定义了 `_physics_process`，
    全库 `.tscn` 也没有任何一处覆写 `physics_process` 属性。故**原版物品从入树到首次
    `preCombatStart` 之间，这个谓词为真，而内核为假** —— 两者机制不同。

    **为什么在战斗内不可观测**（三条互相独立的依据）：

    ① 该窗口的状态被 `preCombatStart()` **无条件重置** ——
       `iterationCooldown = adjustCooldown(); triggerTime = iterationCooldown;
       activateCooldown()` 三项全写，战场只消费重置后的值；
    ② 战斗路径上读该谓词的只有三处：`getCooldownEncoded()`（表现用的进度编码）、
       `advanceCooldownPercent/Seconds`（两者都在 `preCombatStart` 之后才可能被调用），
       以及 3 支物品脚本（`TeslaCoil` / `TimeDilator` / `Ukulele`）—— 全部在战斗内；
    ③ 枚举物品脚本**不存在「战斗中往背包插入新物品」**这样的选手：
       `BagofGiving` / `Lootbox` / `FurciferPrime` / `PortableAltar` 调用的是
       `itemPool.addItem(descriptor)`（**商店池**），不是 `Inventory.addItem`。
       没有「半路入树、错过 `preCombatStart`」的物品，该窗口就没有战斗内的入口。

    **未定裁的残留（不臆测）**：该窗口内原版 `_physics_process` 是否会真的推进乃至触发
    （取决于当时 `character_` 是否为空、`iterationCooldown` 是否为 0），以及若触发是否会
    污染 `consumed` / `numCharges` 这类跨战斗状态 —— **需活体观察原版才能定裁**。
    即便推进，也发生在**战斗之外**，且被 ① 抹除。
    登记方式：`tools/verify_cooldowns_gd.py` 的 `TENSIONS` 每条运行都会打印这段，
    不隐藏、不静默消除。

21. **★ `stun()` 漏发 `character_stunned` 信号（本轮联动排查唯一实锤断点，已修复）。**
    原版 `Character.gd:1075-1082` 的 `stun()` 非抵挡分支：
    `EventBus.emitEvent(self, "character_stunned", event, [event])` —— emitEvent 语义是
    **记日志 + 定向派发**（先 `logEvent(event)` 再查连接表回调）。内核首版误写成
    `ctx.bus.logEvent(event)`（只记不派发）→ 订阅方 `Dagger.onStun`（眩晕补刀，全库
    唯一订阅者，静态对账 40 种信号 × 503 份脚本得出）**静默失效**：眩晕照常发生、
    日志照常出 Stun 行、零报错——「零报错 ≠ 生效」的又一实证。
    **修复**：`gd_core/CoreCharacter.gd` 与 `gd_core_py/gd_core/CoreCharacter.py`（手工同步）
    的 `stun()` 非抵挡分支改回 `ctx.bus.emitEvent(self, "character_stunned", event, [event])`。
    **验证**：Hammer+Dagger 同侧端到端——眩晕 3 次、`onStun` 触发 3 次（此前 0 次）。
    **系统性对账**（本轮新增方法）：全库静态扫描「订阅信号 → 原版发射点 → 内核发射点」
    三方对账 + 动态全家桶连接表审计 + 282 件联动物品逐件「affected 格摆邻居 ×
    预期信号 ⇒ 连接存在」批量验证，除上述 1 处外**零断点**；转写函数完整性
    （原版 gd → 直挂 gd → Python py 两段函数集合对账）517 份零缺失。

22. **zh 渲染层：LOG_Activation 机翻「{origin}以显示。」→ 可读兜底「{origin}已激活。」**
    官方 zh 文本为机翻瑕疵（en = "{origin} activated."）。显示层兜底与 §6 疲劳行
    （`FatigueDamage` 官方无键）同等待遇：**不影响判定路径，只影响 `engine/log_text.py`
    的中文渲染**，en 渲染与 JSON 事件流保持原样。同批排查结论：zh 物品名表对
    runtime 全部 517 件物品零缺失；「激活行无伴随效果行」（如石制护甲
    `doCooldownEffect` 去除对手不存在的尖刺/充能）为原版同款行为，不是缺陷。

---

## 7. 验收方式与当前结果

一键流水线：

```bash
python tools/run_gd_core.py          # 十七道闸门（0 前置阶段 + 1–10 GDScript 侧 + 11–14 Python 侧 + 15–16 跨/收尾 + 17 Python 侧全物品）
python tools/run_gd_core.py --bench  # 附吞吐基准
```

★ 闸门 1–10 验的是 **GDScript 版内核**（`gd_core/` + `gd_core_items/`）；闸门 11–14 验的是
它的 **Python 转写版**（`gd_core_py/`），也就是模拟器真正跑的那一份。两者必须分开取证 ——
「GDScript 版对」不蕴含「Python 版对」（见 §10）。闸门 15 是唯一**跨两侧**的一道：它把
两侧的事件轨迹逐条对上；闸门 16 是**判定路径的运算级取证**（静态逐行 + 动态逐帧，
见下）；闸门 17 补的是**覆盖缺口**：门 9 把 517 件带上 GDScript 侧，而 Python 侧一直
只跑 8 套阵容（见下）。

| # | 闸门 | 工具 | 当前结果 |
|---|---|---|---|
| 0 | **七支**幂等生成器 + **一支前置断言**全量前置（描述符注册表 / 物品脚本转译 / 阵容夹具 / class_name 注册表 / Python 转写 / 模拟器运行时数据 / **具名色表** / **语法面断言**） | `gen_core_item_book.py` → `build_item_scripts.py` → `gen_lineup_fixture.py` → `gen_test_project.py` → `gd_to_py.py` → `gen_gd_core_data.py` → `gen_color_names.py` → `survey_gd_syntax.py --verify` | 通过（色表 146 条 / 语法面 21 项断言全对） |
| 1 | 静态审计：`ctx.*`/`Core*.` 引用 + 行为派发返回值 + **行为派发落点可达** + `bool()` 误用 | `tools/audit_gd_core.py` | 通过（0 问题） |
| 2 | class_name 依赖环 | `tools/check_class_cycles.py` | 通过（0 环） |
| 3 | 内核脚本在 Godot 3.6 下全量解析 | `gd_core_test/ParseAll.gd` | 通过（failed=0） |
| 4 | 四项契约冒烟（含计时器契约） | `gd_core_test/Smoke.gd` | **PASS** |
| 5 | 四项网格子系统契约（含朝向契约） | `gd_core_test/GridSmoke.gd` | **PASS** |
| 6 | 物品脚本全量解析（503 个） | `gd_core_test/ItemParseAll.gd` | 通过（0 错误） |
| 7 | 单例门面契约（描述符身份 / 库存查询 / 包装层 / Game 状态量 / combatTimer 身份） | `gd_core_test/FacadeSmoke.gd` | **PASS** |
| 8 | 8 套真实阵容端到端（**56 局**全矩阵 + 确定性复跑 + **宝石实效 A/B** + **落事件轨迹**) | `gd_core_test/LineupBattle.gd` | **PASS** |
| 9 | **517 件可转译物品逐一真打一场** + 派发可达性断言 | `gd_core_test/ItemBattle.gd` | **PASS** |
| 10 | **宝石 / Socket 门面契约**：折叠等价性 / `getGemMode` 四分支 / 三种模式公式级效果 / 自身冷却自行触发 | `gd_core_test/GemFacade.gd` | **PASS** |
| 11 | 转写产物与**手写文件**语法体检（531/531）→ **转写缺口扫描**（撞名 / 未映射 / 丢行）→ **缺口扫描正对照**（删 1 行须报出） | `tools/check_gd_py.py` → `tools/scan_translit_gaps.py` → `tools/check_scan_gaps.py` | 通过（531/531；`TRANSLIT_GAPS: PASS`；`SCAN_GAPS_CONTROL: PASS`） |
| 12 | `CoreRng` 与 Godot 3.6 **逐位**一致 | `tools/verify_godot_rng.py` | 通过（840/840 值） |
| 13 | Python 版内核端到端：8 套阵容 56 局 + 确定性 + 宝石 A/B + **RNG 可复现性双侧判据** + 落事件轨迹，与闸门 8 基准**逐字符**对照 | `tools/run_gd_py.py` | **PASS**（56/56 一致 / 4053 条事件落盘） |
| 14 | **模拟器内核接入一致性**：经生产装配路径复跑同 56 局，再逐字符对照 | `tools/check_gd_core_engine.py` | **PASS**（56/56 一致） |
| **15** | **逐事件对照**：门 8 与门 13 的事件轨迹逐条比对（**4053 条**），SAME / NUMEQ / DIFF 三级判定 | `tools/compare_events.py` | **PASS**（SAME 2273 + NUMEQ 1780 + **DIFF 0**） |
| **16** | **冷却等价校验**：A 静态逐行对照（冷却路径 27 对函数 / 99 行相等 / **0 行未归因**）+ B 动态逐帧恒等式（读门 9 遥测：303 件带冷却物品，`triggerTime -= δ×getSpeed()` **22.8 万帧 / 0 违背**）+ 抖动指纹 ∈ [0.95, 1.05] | `tools/verify_cooldowns_gd.py` | **PASS** |
| **17** | **Python 侧全物品逐一上场**：517 件各带一场，判「装配成功 / 零异常 / 自然收场」 | `tools/check_gd_py_items.py` | **PASS**（517 件，异常 0 / 未转译 0 / 超时 0） |
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

**闸门 17 的存在理由（Python 侧的覆盖缺口）**：闸门 9 把 517 件物品逐一带上
**GDScript 侧**内核的场，而闸门 13/14 只跑 8 套阵容的 56 局 —— 于是 **Python 侧
（模拟器真正跑的那一份）从未把全部物品过一遍**。代价是实测出来的：**19 件物品在
模拟器里一用就崩**，而整条流水线全绿、一行红都不报。

六类缺口（件间有重叠），全部是**转写映射**问题，不是内核逻辑问题：

| # | 缺口 | 件数 | 表现 | 根因 |
|---|---|---|---|---|
| 1 | `call_deferred` 未映射 | 8 | `NameError`（2 件在入包当帧就抛） | 内核有 `ctx.defer`，生成器漏了这条映射 |
| 2 | `typeof` + `TYPE_VECTOR2` 未提供 | 12（棋类） | `NameError` | `_rt` 里没有这两个名字 |
| 3 | **变量名遮蔽基类方法** | 4 | `TypeError: 'float' object is not callable` | 子类 `var speed` 遮蔽 `CoreItem.speed()`（见 §11.2） |
| 4 | `tr` 未提供 | 3 | `NameError` | 同 2（三处全在描述文本拼接，不参与判定） |
| 5 | `PCG32.randi` 缺失 | 1 | `AttributeError` | `_rt._math_rng()` 塞的是裸 `PCG32`，而 `Array.shuffle()` 要的是 `randi()` |
| 6 | **`_readyInit` 里整行丢失** | ≥1 | `AttributeError: 'NoneType' …` | `find_block_end` 按缩进判块结束，多行字面量的 `}` 顶格 → 它**后面**的语句被当成函数体外内容整行丢弃 |

★ 这 19 件不是冷门物品：ChessMaster / Sloth / Wand of Dissonance / Girl Power 都在其中。

★ 六类里有**三类**（1、5、6）的共同特征是「**GDScript 侧完全正常**」：
  1 靠 Godot 原生提供 `call_deferred`；5 靠 GDScript 的 `Array.shuffle()` 走 Godot 自己的
  实现；6 因为 GDScript 解析器**不看续行缩进**（`}` 顶格也能正确闭合）。
  于是闸门 9 全绿而 Python 侧崩 —— 「闸门 1–10 是 GDScript 侧、11–14 是 Python 侧」
  这套切分是对的，**缺的是 Python 侧的覆盖面**，不是判据强度。

★ 另有两处「判据本身坏了」被本轮翻出来，都属于**表笔没接上**：
  · `gd_to_py.py` 的 `load→_load` 规则要求 `(` 后紧跟**引号**，而 `mask_strings()` 在那之前
    已把字符串换成占位符 → 该规则**从写下起一次都没命中过**，垫片 `_rt._load` 一直是死代码；
  · 新写的「丢行」扫描少了 `re.M`，`^` 只匹配文件首行 → 恒返回「无」，看着像全库干净。
  后者是被**正对照**当场抓出来的（`tools/check_scan_gaps.py`），故它已进流水线。

两者互补且不可互替：真实对局里伤害受 buff/暴击影响，只适合断言方向与存在性；
公式与取整方向只有在受控数值下才断言得了。

**闸门 15 的存在理由（摘要一致 ≠ 战斗一致）**：闸门 13/14 比对的是 56 局的**摘要**
`win / t / php / ohp / act / dmg / heal / gem / fat / stun`。摘要一致是**必要不充分**条件：

> 两句不同的战斗可以给出完全相同的摘要 —— 某次伤害被挪后一拍、某个层数施加到了另一件
> 物品、某次治疗换了起源、两次小伤害合并成一次大伤害。摘要看不见，事件流看得见。

故闸门 15 把口径推到 `CoreCombatLog` 的**每一次 `logEvent`**：

* **取样面**：`CoreCombatLog.logEvent(event)` → `_ctx.hooks.logEvent(event)` —— 这是
  原版全部战斗事件的唯一出口（攻击 / 伤害 / 暴击 / 治疗 / 掉血 / 层数增减 / 眩晕 /
  格挡 / 尖刺 / 中毒 / 吸血 / 寒冷 / 致盲 / 激活 / 疲劳 …），一处取样即覆盖整条判定路径的输出面。
* **两侧各写一遍序列化器**（两种语言无法共享），行格式
  `<id>|<type>|<depth>|<origin>|<target>|<params>`；起源身份取「名字 + ownerType + 占格坐标」，
  宝石再拼「宿主身份 + 插槽号」。
* **输入**：`gd_core_test/event_trace.txt`（门 8 落盘）vs `output/py_event_trace.txt`（门 13 落盘）。

差异分三级，而不是「相等/不等」二值 —— 因为两侧的**数值类型表示**本来就可能不同：

| 级别 | 含义 | 处置 |
|---|---|---|
| `SAME` | 逐字符相同 | — |
| `NUMEQ` | 仅 `int`↔`float` 表示不同，且**数值相等** | 计入统计，不判失败；但要聚合看集中在哪 |
| `DIFF` | 值不等 / 结构不同 / 条数不同 | 必须逐条归因，不允许 `UNATTRIBUTED` |

实测（56 局）：**4053 条事件，SAME 2273 + NUMEQ 1780 + DIFF 0**。

`NUMEQ` 全部集中在两类字段，根因是同一件事 —— **GDScript 的带类型变量在赋值时强制转换，
Python 不会**：

```
gd_core/CoreDamageResult.gd:18   var damage: int        ← 声明是 int
CoreCombatLog.gd:97              event.setParam("damage", damageRes.damage)
                                  →  GDScript 记 int 4 ；Python 记 float 4.0
```

聚合分布（`tools/compare_events.py --numeq-detail`）：

| 事件类型 | 字段 | 次数 |
|---|---|---:|
| `DealDamage` | `damage: int≠float` | 1174 |
| `Health` | `amount: int≠float` | 527 |
| `CriticalDamage` | `damage: int≠float` | 35 |
| `Spikes` / `Poison` / `Block` / `Blind` / `Vampirism` / `Cold` | `amount: int≠float` | 16 / 9 / 7 / 5 / 4 / 3 |

★ **为什么 `NUMEQ` 不等于「无害」，而这个判据仍然够强**：若某处 `damage *= 1.5` 得到的
**不是整数**，GDScript 会**截断**成 int 而 Python 保留小数 —— 此时两侧数值**不相等**，
`NUMEQ` 会立刻降级为 `DIFF` 并在报告里指名到「事件号 + 字段」。所以在 56 局里拿到
`DIFF 0`，等价于「这批对局的类型强制转换点上，被转换的值恰好都是整数」。
**仍未覆盖**：其他阵容/物品上是否也存在非整数的强制转换点（见 §10.6 的覆盖边界）。

**闸门 16 的存在理由（`verify_cooldowns` 等价校验）**：闸门 15 把口径推到了「每一次
`logEvent`」，但它只覆盖**事件输出面**。冷却路径上有一整段判定**不产生事件**：

```
gd_core/CoreItem.gd:640   triggerTime -= delta * getSpeed()
CoreItem.gd:642           if triggerTime <= 0: trigger()
```

这两行决定「哪一帧开火」，却只在**跨过 0 的那一帧**才留下事件痕迹；少减一点、`getSpeed()`
取错一次、`delta` 用了 `_process` 的，都不会改变事件**内容**，只会改变事件**时刻** ——
而 56 局里只要双方血量对比没翻盘，摘要就还是那一个摘要。所以冷却要单独取证，且必须**两半**：

| 半边 | 做法 | 能证明什么 | 证明不了什么 |
|---|---|---|---|
| **A 静态** | 把 `gd_core/CoreItem.gd` 与 `decompiled_full/Items/Item.gd` 的 **27 对**冷却函数体各自规范化后逐行比对（99 行相等） | 「这行**照抄了**原版」——差异全部落进已声明台账 | 跑起来是不是真按这行算 |
| **B 动态** | 门 9 改成**逐帧轮询**驱动（tick 次序/delta/上限与普通驱动逐字相同，只加采样），核对 `triggerTime` 每帧的差 | 「跑起来**真是**这么算的」——22.8 万帧、0 违背 | 算的是不是原版那一行 |

A 的设计要点是**差异必须落到某一类**，而不是「看起来差不多」：

| 类别 | 台账 | 体检 |
|---|---|---|
| 机械改名 | `CANON_BOTH`（`Util.rng.`→`ctx.rng.`、`Game.combatLog.`→`ctx.combat_log.`、`Stat.`→`CoreConst.ItemStat.` …） | 全局约定，本子集 0 命中只作信息项 |
| 语义改写 | `SEMANTIC_CORE` / `SEMANTIC_ORIG`（`set_physics_process(true)` ↔ `setActiveTrue()`、`is_physics_processing()` ↔ `_cooldown_active` …） | **每条必须命中**，0 命中判「陈旧条目」= FAIL |
| 已声明剥离 | `DROP_LEDGER`（`spawnLabelOnItem` 漂浮数字，纯表现） | 同上，每条必须命中 |
| 内核新增 | `EXTRA_LEDGER`（`_tickTimers(delta)` 与显式冷却门） | 同上，每条必须命中 |
| **未归因** | — | 出现即 FAIL |

B 的判据分四档（首触发必须落在前两档或**带机制核实的**台账里，否则 FAIL）：

| 档 | 内容 |
|---|---|
| D1 | `tt_n == tt_{n-1} − δ × getSpeed()`（「前后两帧冷却都激活、都未眩晕」的帧）——**22.8 万帧 / 0 违背** |
| D2-A | 首个 `iterationCooldown` 变更帧：`tt == tt⁻ − δ·speed + ic`（`trigger()` 的 `+= ic`）——**289 件** |
| D2-B | 同上帧：`tt == (tt⁻/ic⁻)·ic`（`updateBaseCooldown` 的比例保持）——0 件 |
| D2-C | 台账归因，且工具会**回物品脚本里核实机制确实存在**——**2 件**：Dragon Knight（`advanceCooldownPercent`）、Robodog（`setBaseCooldown → updateBaseCooldown` 同帧复合） |

★ D2-C 是本次唯一「不可从帧边界反算」的一类，处置方式是**双向核验的台账**而不是放过：
台账项没出现 → 判「陈旧」FAIL；出现了但物品脚本里查不到该机制 → 判「台账在掩盖」FAIL。

★ 另外两处**观测面**也单独判（「什么都没测到」不许冒充「测了且通过」）：

* `seen == 0`（整场没观测到 `iterationCooldown` 从 0 变非 0）→ **FAIL**。实测 0 件。
* `start_act == 0`（冷却刚装上就被撤）→ 实测 **11 件**，且必须能被物品脚本里
  `preCombatStart(): .preCombatStart(); deactivateCooldown()` 解释（Card 系继承
  `Card.gd`，DeerTotem / DragonSet / ExtraAngy 自声明）。查不到即 FAIL。

★ **抖动指纹**：`iterationCooldown / getCooldown()` 实测 ∈ **[0.950730, 1.048556]**，取值
**292 种**。这是原版 `Util.rng.randf_range(0.95, 1.05)` 的可复算指纹，同时是
「冷却语义三方分歧」的口径守卫 —— `simulator/` 那份返回**固定 cd**，比值会恒为 1.0
（只有 1 种取值），D3 会当场抓住。

★ **分母必须是 `getCooldown()` 而不是 `descriptor.cd`**：两者**不等是合法的**
（`LightningPotion.gd:23` 的 `onPrepare` 就把 `baseCooldownOverride` 重写成
`randf_range(cd0, cd1)`）。第一版用 `cd` 当分母，报了两条假越界（Dragon Knight 0.889、
Lightning Potion 1.130），是**判据自己制造的差异**。

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
| ⑥ `verify_cooldowns` 等价校验 + 与 Python 引擎双引擎对照 | **完成**（对照见 §10：56 局逐字符一致 + 4053 条事件逐条一致；`verify_cooldowns` 等价校验见 **闸门 16**：A 静态 27 对函数 / 99 行相等 / 0 未归因 + B 动态 22.8 万帧 / 0 违背） |
| ⑦ 全量双引擎逐事件对照（胜者/结束时刻/事件序列） | **完成**（闸门 15：56 局 / 4053 条事件，SAME 2273 + NUMEQ 1780 + **DIFF 0**；见 §7 与 §10.6） |
| ⑧ Python 转写 + 接入模拟器并出 exe | **完成**（见 §10） |

**本轮补的不是里程碑，而是「面完成了但没走遍」的覆盖缺口。**

里程碑 ⑧ 在**面**上早就完成了（转写 + 接入 + 出 exe），但 Python 侧**从来没有把 517 件
物品逐一跑过** —— 只有 8 套阵容的 56 局。代价是实测的：**19 件物品在模拟器里一用就崩**，
其中包含 ChessMaster / Sloth / Wand of Dissonance / Girl Power，而整条流水线全绿、
一行红都不报。缺口清单见 §7 的「闸门 17 的存在理由」。

现已补两道：
* **闸门 17**：Python 侧全物品逐一上场（与闸门 9 对等）；
* **闸门 11 的第二、三小步**：三类转写缺口的**静态**扫描（撞名 / 未映射 / 丢行）+
  给「0 命中」配的正对照 —— 静态扫描覆盖「没被任何测试执行到的分支」，这是跑一遍做不到的。

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
见上方里程碑 ⑤ 与 §5 陷阱 5。里程碑 ⑥⑦ 随此前置条件解除而**两项均已闭环**：
⑦ = 闸门 15（4053 条事件逐条一致），⑥ = 闸门 16（冷却路径逐行 + 逐帧双取证）。

即便如此，**仍不应宣称 gd_core 已等价于原版战斗系统**。它当前等价的范围是
「核心循环 + 伤害链主干 + Buff 语义 + 网格邻接/受影响集 + 朝向 + 计时器状态 +
疲劳/判胜/收尾 + **517 件原版物品脚本逐字不改直挂运行** + **宝石三模式与 Socket 折叠** +
**冷却路径（逐行 + 逐帧双取证）**」，已被闸门 3/4/5（合成契约）、闸门 8（真实阵容 56 局
+ 宝石 A/B）、闸门 9（517 件全量逐一上场）、闸门 10（宝石公式级）、闸门 15（逐事件）、
闸门 16（冷却逐行逐帧）覆盖。**仍缺的证据**见 §10.6：
① 静态覆盖只核了「基类有没有洞」，物品脚本自带的行为分支未逐条对照；
② 事件对照只覆盖 8 套阵容 / 56 局 —— **闸门 17 已让 517 件在 Python 侧逐一上场，但它只判
「跑得下去」，不判「算得一样」**（某件物品完全可能跑完整场却数值全错），故「517 件的数值一致性」
仍然没有证据；
③ `NUMEQ` 只证明「这批转换点上被转换的值恰好都是整数」。
所以「等价」仍是**「无已知偏差」**，不是「已证明无偏差」—— 差别在于**尚未遍历到的分支**。

★ 需要区分两件事（容易混为一谈）：

| 命题 | 现状 |
|---|---|
| gd_core（GDScript 版）与 **它自己的 Python 转写版** 一致 | **已证明**（闸门 11–14 逐字符 + 闸门 15 逐事件） |
| gd_core 与原版游戏一致 | **无已知偏差**，未证明（证据见闸门 15/16；缺口见 §10.6） |

前一问是「转写有没有引入偏差」，后一问是「移植有没有理解错原版」。前一轮闭环的是**前者**，
本轮（闸门 16）第一次对**后者**给出了代码面 + 运算面的直接证据 —— 但仍是**一个路径**的证据，
不是全路径。

---

---

## 9. 工具索引

### 验收与守卫

| 工具 | 作用 |
|---|---|
| `tools/run_gd_core.py` | **一键十七道闸门**（`--bench` 附基准） |
| `tools/audit_gd_core.py` | 静态审计：引用完整性 + 行为派发返回值 + `bool()` 误用 + **派发落点可达** |
| `tools/check_class_cycles.py` | class_name 循环依赖检测 |
| `tools/gd_core_coverage.py` | 覆盖度核算（`--list` 明细 / `--unknown` 只看待目视） |
| `tools/gap_audit.py` | **缺口定裁**：调用闭包可达性，替代关键词启发式 |
| `tools/check_gd_py.py` | **产物 + 手写**文件语法体检（531 文件 `ast.parse`） |
| `tools/verify_godot_rng.py` | `CoreRng` 与 Godot 3.6 **逐位**对齐校验 |
| `tools/run_gd_py.py` | Python 版内核端到端（56 局 + 确定性 + 宝石 A/B + **RNG 可复现性双侧判据** + 事件轨迹落盘 + 与 Godot 基准逐字符对照） |
| `tools/check_gd_core_engine.py` | **模拟器内核**经生产装配路径复跑同 56 局并逐字符对照 |
| `tools/compare_events.py` | **逐事件对照**：两侧事件轨迹逐条比对，SAME / NUMEQ / DIFF 三级判定（闸门 15） |
| `tools/verify_cooldowns_gd.py` | **冷却等价校验**：A 冷却路径 27 对函数逐行对照（差异须落进已声明台账）+ B 逐帧恒等式与抖动指纹（闸门 16） |
| `tools/check_gd_py_items.py` | **Python 侧全物品逐一上场**：517 件各带一场，判装配/零异常/自然收场。与闸门 9 对等，补的是 Python 侧的**覆盖面**（闸门 17） |
| `tools/scan_translit_gaps.py` | **转写缺口静态扫描**三段：A 变量遮蔽继承链方法 / B 未映射符号（AST 未绑定名）/ C 整行丢失（闸门 11）。★ A、B 覆盖「没被任何测试执行到的分支」，是跑一遍做不到的 |
| `tools/check_scan_gaps.py` | 给上一个的「0 命中」配**正对照**：删掉 Python 产物里 1 行赋值，要求扫描必须报出，随后还原并复核字节一致（闸门 11 第三小步） |
| `tools/verify_cooldowns.py` | 冷却首触发校验 —— 但对象是 **`simulator/` 手写引擎**（旧版，274/274 通过）。★ 与上一个同名不同物：那份返回**固定 cd**，`gd_core` 走原版 `cd × randf_range(0.95,1.05)`，两者语义不同，勿混用 |
| `tools/count_api_usage.py` | 数某符号在 `.gd` 里的**真实调用点**（代码 / 注释 / 字符串分开数；`--bare` 区分全局内建与对象方法） |
| `tools/survey_gd_syntax.py` | 语法面清单；`--verify` 断言 `gd_to_py.py` 文档里引用的 21 个数字（流水线 0 阶段） |

### 代码生成与数据管线

| 工具 | 作用 |
|---|---|
| `tools/build_item_scripts.py` | 原版 `Items/**.gd` → `gd_core_items/` 转译（视觉剥离 + 符号映射） |
| `tools/item_sheet.py` | **原版权威物品表单一入口**：自动 GDEC 解密 + `p1..p10` 按列对齐 |
| `tools/align_item_params.py` | 定点重写 `assets/battle_items.json` 的 `params`（`--check` 幂等校验） |
| `tools/gen_lineup_fixture.py` | 生成 `lineup_battle_fixture.json`（消费点断言 `params` 定长 10） |
| `tools/gen_test_project.py` | 自动重生成 `gd_core_test/project.godot` 的 class_name 注册表 |
| `tools/dump_methods.py` | 从原版抽指定方法的完整源码体（含起止行号），做移植底稿 |
| `tools/gen_gd_core_data.py` | 把 gd_core 跑一局所需的**全部外部数据**编译成单一 JSON（`assets/gd_core_runtime.json`，exe 只读它；`--check` 只校验同步） |
| `tools/gen_color_names.py` | Godot 3.6 具名色表 → `gd_core_py/_colors.py`（`--fetch` 拉源 / `--check` 校验同步） |
| `tools/measure_dead_weight.py` | **精简度体检**：死桩函数 / 未引用字段的占比（只报告不删除，见 §6.18） |
| `tools/oneoff/` | 一次性侦察/诊断脚本的**冻结归档**（31 个，附 README 说明各自结论落在哪） |

### 闸门脚本（`gd_core_test/`）

| 脚本 | 作用 |
|---|---|
| `ParseAll.gd` | 全量解析（Godot 每脚本只报首个错误，故逐文件 `load`） |
| `Smoke.gd` | 四项契约冒烟（基础对拼 / 疲劳 / 确定性 / 计时器） |
| `GridSmoke.gd` | 四项网格契约（受影响格判定链 / 邻接 / 确定性 / 朝向） |
| `FacadeSmoke.gd` | 门面契约（物品/角色/网格三类对外接口的形状与默认值） |
| `ItemParseAll.gd` | 517 件转译脚本逐个 `load` + 描述符绑定 |
| `LineupFixture.gd` | **生成物**：`lineups/*.json` → 内联描述符/占格/受影响格（含宝石与脚本路径） |
| `LineupBattle.gd` | 8 套真实阵容对拼（56 局矩阵 + 确定性复跑 + **宝石实效 A/B** + **事件轨迹落盘**） |
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

---

## 10. Python 转写与模拟器接入（本轮）

> ⚠️ **本节于 2026-09-27 被重建**。一次文档重排脚本误删了本节，且该文件当时未提交
> （`docs/` 的上一个 commit 早于本节写作），无副本可还原。现按两个来源重建：
> ① 误删前已读入上下文的逐字内容（§10.1–§10.4、§10.6 之后的部分）；
> ② 缺失的 §10.4 表尾与 §10.5 正文（约 18 行）按 `docs/` 之外**权威源**重写 ——
> `gd_core_test/LineupBattle.gd::place_and_ready`、`tools/run_gd_py.py::place_and_ready`、
> `simulator/gd_core_engine.py::_place_of` 三处调用点的实际代码，以及
> `tools/run_gd_core.py` 闸门 14 的注释。
> **重写部分**（§10.5）请以代码为准复核，其余各节为原文。

### 10.1 为什么可以机械转写

`gd_core/`（18 脚本 9067 行）+ `gd_core_items/`（503 脚本 20244 行）合计 **29311 行**，
用 `tools/gd_to_py.py` 产出 522 个 Python 模块。之所以敢做机械转写而不是重写，
是因为转写前先**穷举统计过 GDScript 专有构造的实际命中数**：

| 构造 | 命中 | 处置 |
|---|---|---|
| `yield` / `preload` / `setget` / `onready` / `@装饰器` / `**` 幂 | **代码内 0** | 无需处理（`onready` 9 处、`add_child` 2 处只是**注释**里的提及） |
| 场景树（`$路径` / `get_node` / `add_child`） | **代码内 0** | 无需处理 |
| 字符串格式化 `%` | **1**（`CoreCharacter.gd:209`） | `_gd_fmt` 垫片 |
| `Color` 字面量 | **gd_core 0 处 / gd_core_items 51 处（29 文件）** | `_rt.Color` + 146 条具名色表 |
| `divmod`（`/` 与 `%` 语义） | 360 处 | `ast` 精确重写（见 §10.3 ②③） |
| 字符兜底（正则，非 ast） | 2 | 经核实无优先级风险，留痕 |

★ 上表数字**不靠人眼维护**：`tools/survey_gd_syntax.py --verify` 把它们断言成 21 条判据，
作为流水线 0 阶段的一支前置断言。内核语法面一变（有人加了个 `yield`、多了一处 `%` 格式化），
流水线当场在这条上红，而不是等到转写产物跑出错来。

> 早先这里写过「`Color` 51 处（全在注释）+ 49 处」，两处都错：`gd_core` 本体实为 **0 处
> 代码 / 0 处注释**，`gd_core_items` 实为 **51 处代码 / 0 处注释**。「51 处命中全在注释」
> 是把两者的口径串在一起读出来的。另有「`Color.White` 4 处」的**伪足迹** ——
> `grep -E "Color\.White"` 会匹配到 `PieceColor.White`，实算 `Color.White` = 0 处
> （唯一真实用法是 `Color.white`，`Item.gd:352`）。

换句话说：**这个项目的 GDScript 面是封闭且极小的**，所以机械转写是可行的；
但「小」不等于「浅」——下面 13 处是必须做**语义级**处理的地方。

### 10.2 转写规则表（实测命中数，由 `tools/gd_to_py.py --report` 现场核算）

```
裸成员→self. 5659 / 裸调用→self. 5337 / 裸类名→_R.C 1112 / var/const→赋值 957
.method()→super(). 666 / for→_iter 453 / 字面量:false 428 / null 322 / true 310
带类型无初值→类型零值 256 / static 上下文→类名限定 226 / 单行块→两行 113
.size()→len 63 / .push_back→append 62 / .empty()→not 54 / .new(→( 53
默认值延迟求值→GD_DEFAULT 42 / static func→@staticmethod 38 / .erase→_erase 26
is→isinstance 24 / match→if/elif 20 / .shuffle→_shuffle 11 / .values()→list 11
.append_array→extend 9 / .duplicate→_dup 8 / .keys()→list 7 / OS.has_feature→垫片 6
.fill→_fill 6 / .has→in 5 / 关键字标识符:from→from_ 5 / 裸 connect→垫片 5
.remove→_pop_at 4 / .pop_front→pop(0) 4 / .find→_find 3 / funcref→FuncRef 2
.resize 2 / 裸 range()→_gd_range 8 / .substr→_substr 1 / .to_lower→lower 1
关键字成员:None 1 / 多参 str()→_strv 4 / 字符兜底 2
```

### 10.3 13 处必须语义级处理的地方

①②③ 隐式 self / `int/int` 截断整除 / `int%int` 取余符号随被除数；
④ `.remove(i)` 按索引 vs `.erase(v)` 按值；⑤ 枚举成员撞 Python 关键字
（`StuffedClasses.None`）；⑥ Python 类属性全实例共享（GDScript `var` 是逐实例的）；
⑦ Python 默认值**定义时求值一次**（GDScript 每次调用求值）；
⑧ 裸类名跨模块引用（→ `_R.C` 注册表）；⑨ `match` 语句；
**⑩ 内嵌类提到模块级后吞掉外层后续成员**；**⑪ 实例属性访问内嵌类**（`ctx.rng.BalancedRng`）；
**⑫ 同名冲突误伤**（`ctx.rng.shuffle(arr)` 被当成 Array 内建 `_shuffle(recv)` 并丢掉实参）；
**⑬ `chain_start` 链尾是下标时不回溯**（`currentAffectedItems[0].foo` 的接收者算成了下标表达式）。

其中 ⑩⑪⑫ 都是**静默失效**型缺陷（改了名字解析结果、不报错），例如：

* ⑩ `DictSorter` 内嵌类被提到缩进 0 之后，`CoreUtil` 后续所有缩进 1 的成员都成了
  `DictSorter` 的成员 → `AttributeError: type object 'CoreUtil' has no attribute 'invertDictionary'`；
* ⑫ `CONTAINER_ARITY` 实参守卫：`ctx.rng.shuffle(p_items)` 的接收者是 `CoreRng`（不是 Array），
  按 Array 内建规则转写会**丢掉实参**，且只在运行时以 `TypeError: object of type 'CoreRng' has no len()` 现形。

### 10.4 四张**实测**权威表（不靠记忆，各有一条 Godot 探针）

| 表 | 探针 | 结论 |
|---|---|---|
| 类型默认值 | `gd_core_test/DefaultProbe.gd` | `Array→[]`、`Dictionary→{}`、`int→0`、`float→0`、`String→""`、`bool→false`；**Object 派生类与无类型 → Null**；**逐实例独立** |
| `range(f)` 对 float | `RangeProbe.gd` | **截断向零**：`2.5→[0,1]`、`-2.5→[]`、`(1.5,4.5)→[1,2,3]` |
| `for i in <float>` | `IterProbe.gd` | **ceil 次**：`3.0→0,1,2`（3 次，**不是** `range()` 的 2 次）、`0.5→0`、`-1.5→空` |
| 具名色 | `core/color_names.inc @ 3.6-stable` | 146 条，通道按 `Color::hex` 的 **float32 除法**复算 |

### 10.5 装配次序：三处调用点，一份口径

**次序本身是战斗语义的一部分**（不是「怎么摆都行」的工程细节）：

```
combat.setup()  →  注网格元数据  →  _readyInit()  →  inventory.addItem()
                →  逐个 setGem()  →  combat.startBattle()
```

★ 物品必须在 `combat.setup()` **之后**才装：`_readyInit` 里的 `newItemTimer` 等依赖
`ctx.combat` 已就位。写成「先装物品、再 setup」会**静默丢掉首轮计时**。
★ 宝石必须在宿主**入包之后**才 `setGem`（对齐原版「先摆宿主、再 setGemData」的次序）。

三处调用点各写一遍同一口径，且**互相独立**：

| 调用点 | 函数 | 用途 |
|---|---|---|
| `gd_core_test/LineupBattle.gd` | `place_and_ready()` | GDScript 侧权威基准（闸门 8） |
| `tools/run_gd_py.py` | `place_and_ready()` | Python 侧对照（闸门 13） |
| `simulator/gd_core_engine.py` | `_place_of()` + `_place()` | 模拟器生产路径（闸门 14） |

三处独立是**故意的**：闸门 14 不是闸门 13 的重复，它验的是「模拟器真正用的那条装配」。
本轮实测抓到一次典型分歧：`occupied` 若由**已平移的** collision 再算一次，等于平移两次 ——
第 n 列落成第 2n 列，物品间距整体拉大，**相邻联动判定全错**，而闸门 13 全绿。
故闸门 14 存在的理由就是「13 通过 ≠ 生产路径通过」。

### 10.6 当前证据边界（不要越过）

| 已证明 | 未证明 |
|---|---|
| 56 局**逐字符**一致：赢家 / 结束时长 / 双方末态血量 / 激活·伤害·治疗·宝石·疲劳·眩晕计数 | gd_core 与原版游戏**本身**的等价 |
| **4053 条事件逐条一致**（闸门 15：门 8 与门 13 的事件轨迹对照，DIFF 0） | **51 个 `CoreHooks` 调用序**一致（未做；见下「为什么不做」） |
| **RNG 消耗序**一致（840/840 值逐位；且正常路径从未触发 `randomize()`，双侧判据） | **517 件物品的逐事件对照**（逐条事件比对只做到 8 套阵容 / 56 局） |
| **Python 侧全物品可跑**（闸门 17：517 件，装配失败 0 / 异常 0 / 超时 0） | 517 件在**两侧**的数值一致性 —— 闸门 17 只判「不崩」，不判「算得一样」 |
| 同种子跨进程可复现（闸门 13 确定性复跑 8 组） | 非整数强制转换点是否存在（见下「NUMEQ 的真实含义」） |
| 宝石实效：去宝石侧治疗数必须为 0、含宝石侧必须 > 0（可证伪的 A/B） | 物品脚本**自带的行为分支**逐条对照（见下「静态覆盖 ≠ 分支覆盖」） |
| **冷却路径双取证**（闸门 16）：27 对函数逐行对照 0 未归因 + `triggerTime -= δ×getSpeed()` 22.8 万帧 0 违背 + 抖动指纹 ∈ [0.95, 1.05]（292 种取值） | 冷却之外的其余判定路径（伤害链 / Buff / 网格邻接 / 疲劳）尚无同等级的逐帧恒等式 |

★ **为什么「56 局逐字符」不够、要再加「4053 条事件逐条」**：前者是**结果面**判据，
理论上存在「偏差互相抵消」的构造；后者是**过程面**判据，逐条带上事件类型 / 父链深度 /
起源身份 / 全部参数。两者不互替，但后者严格更强。

★ **NUMEQ 的真实含义（不要把「已证明」读大一格）**：4053 条里 1780 条是 `NUMEQ` ——
两侧数值相等、仅 `int`↔`float` 表示不同，根因是 **GDScript 的 `var x: int` 在赋值时强制
转换、Python 不会**（源头 `CoreDamageResult.gd:18`）。这条判据**对截断是敏感的**：
若某处被强制转换的值不是整数，GDScript 会截断、Python 保留小数 → 数值不等 → `NUMEQ`
立刻降级为 `DIFF` 并被指名。所以 `DIFF 0` 的含义精确地是：

> 「**在这 8 套阵容 / 56 局所触达的类型转换点上，被转换的值恰好都是整数。**」

它**不**等于「整条判定路径上不存在非整数强制转换」。要把这句话也证掉，需要把事件对照
扩到闸门 9 的 517 件逐一上场（两侧都要落轨迹）—— 这是下一步，不是已完成的结论。

★ **为什么不做「51 个 `CoreHooks` 调用序」对照**：这 51 个钩子**全部是表现层**
（动画 / 飘字 / 音效 / 提示刷新），在 `CoreHooks` 里默认空实现、**不参与任何判定**
（这一点由 §5 的剥离清单与 `audit_gd_core.py` 守着）。要对称地取证得在 GDScript 侧手写
51 个覆写（GDScript 无元编程），而它给出的信息量**弱于**事件流 —— 事件流带参数与父链，
钩子名只说明「某个呈现动作被请求了」。故选择事件流作为对照面，并把
`run_gd_py.py::TraceProbe`（51 钩子记录器）留在单侧、标明未被使用。

★ **静态覆盖 ≠ 分支覆盖**（闸门 16 暴露出的口径问题）：`tools/gd_core_coverage.py` 的
709/998 是**方法名集合差**，度量的是「**内核基类**有没有洞」。自里程碑 ④ 改为直挂方案后，
517 件原版物品脚本以 `extends Item` 直跑在 `CoreItem` 之上，它们自带的方法**不计入该表**。
所以「判定路径缺口 0」的准确含义是「基类与该实现的方法名对得上」，**不是**
「每条 `if` 的两侧都被执行过」。闸门 16 的 A 段之所以只覆盖 27 个函数，也是同一原因 ——
逐行对照的是**基类**的冷却实现；物品脚本各自的覆写由「转译器逐字不改」+ 闸门 6/9
（全量解析 + 逐一上场）覆盖，那是**另一种**证据，不是逐行身份证据。

★ **闸门 17 的证据边界（别把它读大一格）**：它判三件事 —— 装配得起来、跑得下去、
自然收场。它**不**判「算得对」：某件物品完全可能跑完整场、一个异常都没有，却因转写偏差
而数值全错（某处 `_div` 落成 `/`、某个 `int()` 截断方向不同），闸门 17 照样 PASS。
**517 件的数值一致性仍然缺** —— 那要把两侧都落事件轨迹再逐条比对（闸门 15 的做法），
规模会从 4053 条涨到数十万条。它当前的价值是精确的：**把「一用就崩」这一类清零**，
并把 Python 侧的覆盖面拉到与 GDScript 侧对等。

### 10.7 模拟器接入

* `simulator/simulate.py` 的 `ENGINES = ("engine", "simulator", "gd_core")`，
  `--engine gd_core` 走新内核；GUI 控制区也加了「内核」下拉。
* `simulator/gd_core_engine.py` 是适配层，对外面（构造 / `run` / `summary` /
  `result_json` / `log.to_dict|to_text` / `player_wins`）与 `engine/combat.py` 一致。
* 运行时数据只读 `assets/gd_core_runtime.json`（`tools/gen_gd_core_data.py` 生成），
  **刻意不读** `extracted/Items/*.tscn` / `gd_core/CoreConst.gd` / `gd_core_items/*.gd` ——
  那三处在 exe 里不该跟着发布。
* 实测吞吐：同一对阵容跑 100 场蒙特卡洛，`gd_core` **8.6s** vs `engine` **24.2s**（≈2.8×）。
* 三个已知边界（不掩盖）：① 只能装配有转译脚本的物品（当前 517/518，缺 `Coins`）；
  ② 袋子 `contents` 不递归装配（与夹具口径一致）；③ `summary()` 的 `stats` 口径是
  **事件 actor 侧**，与旧引擎的统计口径不同（不影响胜负判定）。

★ 两处「零报错但结果错」的陷阱，本轮各修一次，写在这里防止复现：

1. **`seed=None` 不能直接传给内核**。内核的随机源是 `CoreRng(seed)`，`None` 会被折成 `0` ——
   于是「不指定种子跑 100 场」变成同一场重复 100 次，胜率恒为 100% / 0%，且不报错。
   适配层改为显式抽 `SystemRandom` 种子并回写 `eng.seed`（可复现）。
2. **打包前必须校验运行时数据同步**。`assets/gd_core_runtime.json` 是物品网格几何的快照，
   改了物品库却忘了重生成，exe 里的内核会拿旧几何装配 —— 战斗照跑、结果偏差、零报错。
   `build_simulator_exe.py` 因此在打包前强制跑 `gen_gd_core_data.py --check`。

### 10.8 exe 自检入口

`dist/BackpackSimulator.exe --selftest`：不开窗口，三个内核各真打一场并落
`selftest_report.txt`，用**退出码**表态。

存在的理由：三个内核在 `simulate._get_combat_engine` 里**都是延迟导入**，
`gd_core_py` 更是延迟到 `kernel()` 才 import。于是「打包漏了子包 / 漏了 assets」
在 GUI 启动时完全看不出来——窗口正常弹、示例阵容正常列、点开始才炸。`--selftest`
是不依赖界面的那条验收入口。**每次重新打包后都该跑一次。**

---

## 11. 本轮新增的守卫（都是「把口头结论变成可复算判据」）

这一轮的主要收获不是功能，而是把几处**写在注释里、没有任何东西在看**的断言变成了工具。

| 原先（不可复算） | 现在（可复算 + 进流水线） |
|---|---|
| `_rt.py` 注释断言「`randomize()` 项目里 0 处调用」 | `tools/count_api_usage.py --call --bare`（区分**裸内建**与**对象方法**；实测裸调用确为 0，1 处命中是 `CoreRng.gd:25` 的 `rng.randomize()`） |
| `_rt.py` 里 `_RANDOMIZED` 标志位注释写着「供闸门断言『未触发』」 | 此前**只声明、从未被读取**（空话）。现接为 `run_gd_py.py` 的 **[7] RNG 可复现性**，且**双侧**：正常路径须未触发 + `CoreRng(0)` 正对照须能翻转标志位（否则该判据恒真 = 没判据） |
| `gd_to_py.py` 文档里的语法面数字（「`%` 0 处」「Vector2 141 处」） | `tools/survey_gd_syntax.py --verify` 断言 **21 项**，流水线 0 阶段的一支前置断言。顺带查出两处真错：`%` 实为 **1 处**、Vector2 实为 **138 行 / 198 次** |
| `gd_to_py.py` 文档引用「保真判据 = `tools/compare_gd_core.py`」 | **该文件不存在**。改为指向真正在跑的 `tools/run_gd_py.py`（闸门 13） |
| 色表链路散在 `output/` 的 4 个文件（`fetch_color_table.py` + `make_colors.py` + `_colors_header.txt` + `color_table.py`），`output/` 还是 `.gitignore` 的（丢了找不回） | 收敛成 `tools/gen_color_names.py`（`--fetch` 拉源 / 生成 / `--check` 校验），并纳入流水线 0 阶段。**搬迁前后数据指纹一致**：146 条、`sha256=70286c7e…` |
| `check_gd_py.py` 的 `HANDWRITTEN` 是「**跳过体检**」名单 | 改成「不计入产物口径」但**仍体检** —— 手写文件恰恰最需要体检（生成器有闸门守，人手写的没有）。体检面 522 → **531**（521 产物 + 10 手写） |
| `run_gd_py.py::_install_trace` 给 51 个钩子挂覆写，却**不调父类实现** | 等于把 `HookProbe` 的四个计数钩子在 `TraceProbe` 上整段遮蔽 → 开 trace 时 `act` 恒为 0 且**零报错**。现已改为「先记录、再调父类实现」。（`TraceProbe` 当前未被对照工具使用，见 §10.6） |
| 一次性侦察脚本散在 `output/`（`.gitignore`，随时可能被清且找不回） | 归档到 `tools/oneoff/`（**31 个，进版本库**），附 README 逐条说明「结论落在哪、已被谁取代」。其中 `survey_gd_syntax.py` 因被文档引用而**转正**到 `tools/` |

★ 这一轮的教训与 §6.19 是同一条：**写进注释的数字，没有任何东西在守**。
区别只是这次连数字本身的正确性也是靠 `count_api_usage.py` / `survey_gd_syntax.py` 现算才发现有问题。

### 11.1 冷却等价校验（闸门 16）抓到的真问题

把冷却路径逐行对照一遍，抓到 1 处**真遗漏**与 4 处**判据自身**的错：

| # | 性质 | 内容 |
|---|---|---|
| 1 | **内核真遗漏** | `CoreItem.getSpeed()` 少了原版 `Item.gd:3743-3744` 的两行短路 `var override = statDisplayOverrides[Stat.Speed]; if override: return override`。这不是有意剥离 —— 同族分支（`MinDamage` / `MaxDamage` / `Accuracy` / `Chance` / `Chance2` / `StaminaCost` / `BaseCooldown`）在内核里**都保留着**，只有 `Speed` 漏了。唯一写入方是 `CombatLog.gd:612` 的日志回放路径（`item.setStat(stat, statLogger.getItemStatAt(...))`），战斗中该数组恒为 `null`，故**补回是零行为变化**；但缺了它，「本函数与原版逐行一致」这句话就不成立。已补，并立了守卫。 |
| 2 | 判据错 | 抖动指纹第一版拿 `descriptor.cd` 当分母 → 报了两条**假越界**（Dragon Knight 0.889、Lightning Potion 1.130）。分母必须是 `getCooldown()`：`LightningPotion.gd:23` 的 `onPrepare` 就把 `baseCooldownOverride` 重写成 `randf_range(cd0, cd1)`，两者**不等是合法的**。 |
| 3 | 判据错 | `NUMEQ` 式的浮点比较：遥测用 `%.10f` 打印，反算时误差可达 5e-10，逼近 1e-9 容差。改成 `%.12f`，并写明「打印精度必须远小于判据容差，否则是判据自己制造的假差异」。 |
| 4 | 判据错 | 「装上即撤」11 件的解释一度查不出来 —— 是脚本路径解析写错了（fixture 里是 `res://gd_core_items/Exclusive/DeerTotem.gd`，我又拼了一次 `gd_core_items/`），而 `extends Card` 这种**基名**形式需要按 basename 查索引。**判据失败时先怀疑判据**。 |
| 5 | 观测面 | `start_act` / `seen` 这两个「观测面」字段是补上的：最初版本用「观察到激活」当起点，于是 Card 系（`preCombatStart` 里装完就 `deactivateCooldown()`）整场**什么都测不到**，却会显示成一行漂亮的全零、不报错。**「什么都没测到」不许冒充「测了且通过」** —— 现在 `seen=0` 直接 FAIL，`start_act=0` 必须能被脚本里的机制解释。 |

★ 第 2–4 条是同一类：**判据自己算错了，而错误以「失败」的形式呈现**。若不逐条定裁、
直接改判据容差把红变绿，就会得到一份「在测判据而不是在测内核」的工具。定裁的顺序是
「先回源码看这一行到底是什么语义」，再决定判据怎么写。

### 11.2 变量遮蔽方法（GDScript 双表 ↔ Python 单表）

**这是本轮最有意思的一处语义分歧，值得单独记。**

GDScript 里**成员变量与方法分属两张表**：`GDScriptInstance::get()` 查 members，
`GDScriptInstance::call()` 查 `member_functions`。所以子类写

```gdscript
var speed = 0.0
```

与基类写

```gdscript
func speed() -> float:
	return speedScale
```

**可以共存且互不干扰**：`self.speed` 拿到变量，`self.speed()` 调到方法。

Python 只有一张表：实例属性 `self.speed = 0.0` 直接**遮蔽**类方法 `speed`，于是
`CoreItem.getSpeed()` 里的 `self.speed()` 抛
`TypeError: 'float' object is not callable`。而且它只在「该物品上场 **且** 冷却推进到
`getSpeed()`」时才炸 —— 解析、语法体检、静态审计全都不报。

实测 4 件：`ChessMaster` / `GirlPower` / `PerpetuumMobile` / `Sloth`，变量都是 `speed`。

处置：生成器里做**撞名消歧**（`speed` → `speed_v`），判据是「本文件顶层 `var` ∩ 继承链
（含内核 `CoreItem`）上的 `func` 名」。三条备选方案为什么不选：

| 方案 | 为什么不选 |
|---|---|
| 改内核方法名（`speed()` → `getSpeedScale()`） | 破坏「与原版 `Item.gd` 该函数逐行一致」的可核性 |
| 改 `_rt` 让属性不遮蔽方法 | 运行期 `self.x` 与 `self.x()` 同名时**本就无法区分**；要区分就得把所有方法调用改走显式派发，侵入面远大于改一个纯本地变量名 |
| **改子类的变量名** ✓ | 这 4 件的 `speed` 都是纯本地变量（无 `get("speed")` 动态访问、无外部读取者），改名不触碰任何跨脚本约定 |

★ 反向的同类处置：`_rt.RandomNumberGenerator.seed` 用 `@property` 是**对的** ——
那里 GDScript 侧写的是 `rng.seed = x`（属性赋值），若在 Python 里做成普通方法，
这行赋值会把方法**覆盖掉**、静默失去播种语义。同一个坑的两个方向。
新写的扫描器一开始把它当「遮蔽」报了误报，故判据必须排除 `@property` / `@x.setter`。

★ **两侧独立扫描是必需的**：GDScript 侧按 `extends` 链走文件系统，Python 侧按 AST 走
`_R.C("res://…")`。两者结果**必须一致**，不一致就说明某一侧的扫描器坏了 ——
本轮实测两次（继承链只认 `"res://Items/…"` 不认 `"res://gd_core/…"`；正则只认双引号而
`ast.unparse()` 输出单引号），两次都表现为「恒返回『无』」，看起来和「全库干净」一模一样。

### 11.3 本轮新增的守卫

| 原先 | 现在 |
|---|---|
| `gd_to_py.py` 的 `load→_load` 规则**从未命中过**（判据要求 `(` 后紧跟引号，而 `mask_strings()` 已把字符串换成占位符）；垫片 `_rt._load` 一直是死代码 | 放宽为「名字前不是标识符/点」，`CoreUtil.isItemDescriptor` 这才真正用上它 |
| 转写缺口的发现方式 = 「用户撞上崩溃了再报」 | `tools/scan_translit_gaps.py` 三段静态扫描（撞名 / 未映射 / 丢行），覆盖**未被任何测试执行到的分支**，进流水线 |
| 闸门 9 只扫 `SCRIPT ERROR` | 现状保留，但**Python 侧补了对等的闸门 17**；GDScript 侧的运行期错误（`Invalid call` 等）是否会漏，见 §6 的张力清单 |
| 「0 命中即通过」的判据没有任何东西在守 | `tools/check_scan_gaps.py` 正对照：删 1 行须报出、还原后须回到 PASS。**它当场抓出我新写的扫描器少了 `re.M`** |
| Python 侧全物品从未跑过 | 闸门 17：517 件各带一场，异常 0 / 未转译 0 / 超时 0 |

