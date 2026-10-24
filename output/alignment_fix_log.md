# 对齐修复日志（alignment_fix_log）

> 工作流：docs/alignment_fix_workflow.md（三阶段消耗链对齐）。
> 每轮循环追加：时间 / 缺口 / 修复 / 验证。断点续接与最终报告的唯一依据。

---

## 2026-10-07 02:00 · 阶段1 第 1 轮：神谕 rng state 注入起跑 + 电荷机制/表现层消耗还原

### 本轮起点

- 阶段1 基线（`tools/verify_oracle_s1.py`，3 试点场 = 物品数中位/最大/最小：
  run1122_r11=78 件、run1160_r18=128 件、run1195_r17=0 件）：
  **1/3 三方一致**（仅 run1195 零物品场）；
  run1160 首分歧 event idx 3、run1122 首分歧 event idx 18。
- 神谕侧 `oracle_fight.gd` 已有 rng_state.txt 导出（战斗装配后、开战序列前，
  双 u64），3 试点场已带 state；其余 914 场为旧批量产物（无 state，需重跑）。

### 缺口 ①：电荷传播被当成纯表现删除（run1160_r18 根因，战斗逻辑缺口）

**原版在做什么**：`Item.sendCharge`（1.1.8 @ Items/Item.gd:5147-5156）发射一枚**真实
电荷体** `ElectricalCharge`（Items/ElectricalCharge.tscn）：`charge.start()` 的 i==0
分支（ElectricalCharge.gd:146-149）**同步**调用 `onNewCellEntered(1)`——受格物品
`chargeReceived/chargeLeft`（Resistor 的 giveHeat、Charge Splitter 的接力都在这）
+ 发射物自身 `onChargeEnteredCell` 的速度类 buff。后续 cell 由 SceneTreeTween 驱动。
**gd_core 原来错在哪**：`CoreItem.sendCharge` 只调 `ctx.hooks.sendCharge`（空钩子），
电荷的战斗语义（heat/接力/速度 buff）整个不存在——Battery 阵从开战批量起既无事件
也无消耗。

**修复**（gd_core/CoreItem.gd + gd_core_py/gd_core/CoreItem.py 镜像）：
- `sendCharge` 还原同步段：`inventoryCells = getTopLeftCell() + rotate(fd×90°,
  cell + CollisionMap偏移)`（像素级还原 Item.gd:1040-1047 → Inventory.gd:377-381
  两步互逆；各物品 .tscn 的 CollisionMap position 由脚本写入
  `collisionMapPosition`——Battery/ChargeSplitter/CogBadge=(40,40)、Generator=(40,0)、
  LightningStaff=(-40,0)、ManaCrystal=(-40,-40)、Con-Trap-Tron=(40,-20)，floor 语义
  = TileMap.world_to_map）；
- `_chargeEnterCell` = ElectricalCharge.onNewCellEntered 折叠实现（electrical charge
  对象携带 last/cur，速度 buff 走 has_method 守卫的动态派发）；
- **多 cell 入格不复刻**（与神谕同约定）：神谕阻塞 tick 循环不处理 tween，
  cell 2..N 的入格从不发生——run1160_r18 语料实证：19 个 heat 里 12 个 t=0、
  其余全部来自 Bazooka 等重发射，0 个落在 durPerCell 整数倍时刻；
- `Sound.playSound(chargeSound, randf_range(-12,-5), randPitch(0.3))` 的实参求值
  消耗（Item.gd:5155；randPitch=Util.gd:682-683=randf_range(0.7,1.3)，2+2 步/次；
  Sound.playSound 本体无 rng——oracle/Utility/Sound.gd:174-184）。

**装配层配套**：`faceDirection` 此前恒 UP——电荷路径（chargeCells 是**本地格**常量）
与 SpintoWin/LongSpear/RainbowPotion 的朝向分流全按 0° 计算。修复：
`gd_core_test/OracleAlignBattle.gd::place_one` 与 `simulator/gd_core_engine.py::_place`
按夹具 rotation（度数）写入 faceDirection（0..3 顺时针 1/4 圈）；
`tools/gen_fixture_from_lineup.py` 的 Godot 侧条目补 `rotation` 字段并重导夹具。

### 缺口 ②：isCraftedItem 恒假（run1160_r18 第二分歧，数据缺口）

**原版在做什么**：`Cog.onCombatStart` 给相邻**合成品** block×件数
（canAffect = item.isCrafted() = `not descriptor.originatingRecipes.empty()`，
ItemDescriptor.gd:257-258；配方由 ItemBook.parseRecipe → Recipe.init 注册到
`fusedItem.originatingRecipes`，Recipe.gd:68）。
**gd_core 原来错在哪**：battle_items.json 未导出配方图 ⇒ originatingRecipes 恒空
⇒ Cog 整个不发 block/activation（已知缺口，本轮接通）。

**修复**：新增 `tools/enrich_recipes.py`（解析 ItemData_e.csv recipes 列 +
ItemBook.addCauldronRecipes 的大锅配方，Recipe.init 的 isReleased 丢弃语义按
「不在 battle_items.json = 未发布」复刻）→ battle_items.json 增
`originating_recipes`（176 件 / 186 条）→ `compile_descriptor` 透传
→ CoreItemData.fromDict 原生读入（两内核本就实现该字段）。
验证：run1160 玩家侧 Cog block(10)+activation 出现且逐行对齐。

### 缺口 ③：战斗期表现层 Util.rng 消耗面缺失（链位漂移，rng-mechanism）

**原版在做什么 / gd_core 原来错在哪**：原版战斗判定链中途持续消耗全局 rng 的
表现层调用被 gd_core 移植时删除（docs/alignment_fix_workflow.md §1 表），
每次掷点从缺失处起错位。本轮用**逐抽仪器**（神谕 ORACLE_DEBUG rng_log ↔
内核 CoreRng oracle_trace 逐抽 diff + tools/rng_golden_model.py PCG32 黄金模型）
定位并还原（gd_core + gd_core_py 镜像）：

| 消耗点 | 抽数 | 依据 |
|---|---|---|
| activate() → playActivationSound → playDropSound 落物音高 | 1×randf_range(0.9,1.1) | Item.gd:4667-4668→:3171-3173 |
| activate() → playAnimation（descriptor.animationScene 闸） | 4（randomizePosition 3 + playback 1） | Item.gd:5345-5349 + ItemAnimation.gd:24-35 |
| activate(damageRes) → playActivateAnimation | 2×(0.9,1.1)，attackMovingForward 闩 | Character.gd:464-481 |
| dealDamage → playAttackAnimation | 距离 2（默认实参先于早退求值）+ 未闩死时 5 | Character.gd:445-462 |
| takeDamage 伤害飘字 pos+dir | 3（命中/落空都消耗） | Character.gd:524-525 |
| takeDamage 受击动画 playback_speed | 2，「Poison」闸 | Character.gd:616-627 |
| spawnLabel 物品浮动标签 | 2（randInBox） | Character.gd:693-711→Item.gd:6485-6494 |
| gainTemporary resisted/reflect 标签 pos+dir | 3 | Buff.gd:125/140→Character.gd:688-691→Util.gd:868-869 |
| critResisted 的 CriticalResisted 标签 | 3 | Character.gd:571→Util.gd:909-914 |
| 电荷入格命中受体的 Zap | 1×(4.0,4.02) | ElectricalCharge.gd:195-201→Zap.gd:32 |
| gainPoison 受击动画切「Poison」 | 0 抽，闸状态位 | Character.gd:1222-1226 |

**数据配套**：`animationScene`（有无攻击动画场景，按 Items/Animations/
<名无空格>Animation.tscn 文件存在性判定，ItemBook.gd:788-802 同规则）——
新增 `tools/enrich_animation_scene.py`（128/518 件为真）→ compile_descriptor →
CoreItemData（两内核新增字段 + fromDict）→ playAnimation 闸。

**闩死语义（重要约定）**：神谕阻塞循环里 tween 从不推进 ⇒ attackMovingForward
一旦置真便不复位（实证：run1160 语料 (100,160)×90 恒出现而挥击音
pickRandomElement(0,2) 的抽取只在链首出现一次）。两侧模拟器同约定。

### 验证（本轮实测）

- `python -X utf8 tools/verify_oracle_s1.py --cases run1122_r11,run1160_r18,run1195_r17`
  （output/oracle/align/s1_pilot_r8.log）：
  **1/3 三方一致**；run1160 首分歧从 event idx 3 推进到 **idx 33**
  （0..32 逐行一致：电荷 heat/接力/Cog block/抵抗掷点全部对齐），
  残留 = 第 2 个对手 heat 的抵抗掷点结果（oracle 抵抗 2 层 / 内核 0 层）；
  run1122 仍在 idx 18（开战批量期的表现层消耗差，golden model 定位到
  jitter 相位有不明的 2 步/项未记日志消耗，见残留清单）。
- 神谕同种子复跑逐字节一致（run1122/run1160 重跑验证，语料确定性成立）。

### 仪器（本轮沉淀，供下轮使用）

- `tools/rng_golden_model.py`：Godot 3.6 PCG32 黄金模型（random_pcg.h CLZ32 路径 +
  float32 算术），从 rng_state.txt 前向复算神谕 rng_log、自动探测未记日志消耗
  （oracle 里 Util.flipPercent/flip/randPitch 走裸 rng.randf_range/randf，
  不经 rng_trace_* 包装——消耗但不记日志）。已知残缺：中间乘积的 float32
  舍入未逐_op 对齐，±1ULP 打印边界会出现 ~15% 误报「unresolved」。
- 内核侧逐抽追踪：CoreRng.oracle_trace（ORACLE_ALIGN_TRACE=1 开启，
  OracleAlignBattle.gd 落 <out>/<case>/rng_trace.txt，与神谕 rng_log 同构）。

### 追加修复（同日 03:00-04:20 循环续）

- **resisted/reflect 标签的 pos 抽取未还原**：golden model 实证 resist 事件相邻
  无 (-60,60)/(-40,40) 行、roll 后仅 2 步 ⇒ 神谕只消耗 randBuffLabelDir 1 抽
  （spawnResistedLabel 内部），randBuffLabelPos 的两次抽取未发生。已改
  gd_core/CoreBuff.gd + gd_core_py/gd_core/CoreBuff.py（resisted/reflect 两分支）。
  验证：run1160 首分歧 idx 33 → **31**。
- **giveMaxHealth / heal 的标签抽取缺失**：Item.gd:4219-4224 giveMaxHealth →
  Character.spawnLabel(TemporaryMaxHealth, amount) 的 pos/direction 默认实参
  = randDmgNumberPos 2 抽 + randDmgNumberDir 1 抽；Character.heal
  （Character.gd:749）= randHealNumberPos 2 抽 + dir 1 抽 + 物品标签 2 抽。
  已补 gd_core/CoreCharacter.gd（heal + 三个数字位置方法）、gd_core/CoreItem.gd
  （giveMaxHealth、Item.spawnLabel 的 randInBox 2 抽）及两个 Python 镜像。
  验证：run1122 首分歧 idx 18 → **10**（事件 0..9 全对齐：Fire Pit TMH×2=36、
  袋内 6 枚 Flame 的 heat/activation、Piggybank TMH+5——bagCells/filledCells
  双字典共存让袋内物品正确入格并被 Amulet/FirePit 的 inside 计数看见）。
- 本轮试点验证链：s1_pilot_r8/r9/r10.log（r10 = 当前代码状态）。

### 全量 914 场结果（同日 06:45，oracle 批量 917 场全部补齐 rng_state 后）

`python -X utf8 tools/verify_oracle_s1.py`（output/oracle/align/s1_full.log）：

- **三方一致 3/914**；内核对齐（oracle≡gdcore）3/914
  （run798_r18 / run1195_r17 / run1405_r17）；
- 分布：oracle≠gdcore 636、oracle≠gdcore 且 py 分歧 273、三方一致 3、py 缺产物 2
  （这 2 场 py 侧重放中断，内核侧已有产物）；
- 首分歧 event idx：median=9、p25=4、p75=16、max=91——**~80% 的场次在前 20 个
  事件内分叉**（开战批量期）；
- 胜负一致率：oracle vs gdcore 497/914（54.4%）、oracle vs py 498/914。

对照上一轮（seed 注入时代）同口径 3/917 且 ≥12 物品场 0%——state 注入确实把
装配期差异从方程中消除（事件 0..N 前缀普遍对齐到首个未还原消耗点），但
战斗期的未还原消耗面仍使绝大多数场在开战批量内分叉。

### 残留清单（下轮入口，按影响面排序）

1. **【最大家族】战斗开始边界的 2 抽 mystery**（475 场 idx≤9 的主因）：
   golden model + 全量首分歧分布一致实证——神谕在「preCombatStart jitter 段
   结束 → 首个激活 pitch」之间恰好多消耗 **2 步（1 次 randf_range，范围未知）**，
   每场一次；内核此段 0 抽。已排查并排除：clashSwords（(0.9,1.0)，日志未出现）、
   combat_start 监听器（Combat.onCombatStart/CharacterStatsDisplay.activateIcons
   均无 rng）、PLAYER/OPPONENT.combatStart、combatTimer.start、giveMana→gainStacks。
   工具化建议：给 oracle/Utility/Util.gd 的 roll/flip/randPitch/pickRandom 加
   文件型 BISECT 日志（本轮已验证可行，43 行实例见 output/oracle/bisect_draws.txt
   的生成流程）+ 对 `Util.rng.*` 之外的裸调用做全仓 grep 对账；亦可二分
   [M4] 压缩面（onCombatSceneEntered 的注册副作用）。
2. **run1160_r18 @ event 31 / run1122_r11 @ event 10**：抵抗掷点与
   Amulet rollChance 的链位差 1-2 抽（疑似同属 1 号家族的每场一次性偏移）。
3. **randPitch 类裸消耗清单对账**：Util.flipPercent/flip/roll、randPitch、
   BalancedRange.randIntRange、Item.randDamage——内核均已同量消耗（本轮
   bisect 证实 flip 族=BalancedRng 包装，内核经 ctx.rng.flip 同量消耗），
   但逐场对账脚本尚未固化。
4. **±1ULP 打印边界**：golden model 的 float32 逐_op 舍入仍与 MSVC 实际
   代码gen 在 ~15% 行上差 1ULP，造成自动对账的误报；可将比较改为
   「打印串相等 OR 差 ≤1 float32 ULP」双口径。
5. **py 侧 2 场重放崩溃**：run837_r18 / run845_r18 的 gd_core_py 重放抛
   IndexError: list index out of range（gd_core(Godot) 侧同场正常、且二者
   属内核对齐场）——转写层对特定阵容的装配/索引 bug，独立于消耗面对齐。

### 本轮修复全家福（已落码并验证的部分）

① 电荷传播同步段 + sendCharge/collisionMap 像素级格映射（7 送电荷物品）
② faceDirection 装配（电荷朝向 + 朝向分流）
③ isCraftedItem 配方图（tools/enrich_recipes.py，176 件）
④ animationScene 数据 + playAnimation 4 抽（tools/enrich_animation_scene.py，128 件）
⑤ 表现层消耗面：激活落物音高、电荷 Zap、takeDamage 飘字 pos/dir + 受击动画
   playback（Poison 闸）、playAttackAnimation（闩死语义）、playActivateAnimation、
   resisted/reflect/critResisted 标签、giveMaxHealth/heal 标签、Item.spawnLabel
⑥ 仪器：CoreRng.oracle_trace、tools/rng_golden_model.py、oracle Util BISECT 文件日志
（均 gd_core + gd_core_py 双侧落码；gd_core_test/OracleAlignBattle.gd、
simulator/gd_core_engine.py、tools/gen_fixture_from_lineup.py 配套）

### 红线自查

- 全程无头后台（--headless --quiet --audio-driver Dummy），无任何可见窗口；
- 神谕只读 history.db 本地快照（user:// 隔离副本），未写 Steam 版游戏目录；
- 无在线/排名/休闲模式入口（oracle_fight.gd 红线断言持续生效）；
- 未执行任何 git 提交/推送类命令。


---

## 2026-10-07 08:00-11:30 · 阶段 2：装配期（物品实例创建期）消耗对齐

### 装配期消耗模型（本-round 实证 + 逐行源码证据）

仪器（本轮沉淀）：`oracle/oracle_stage_probe.gd`（装配逐段链态 dump）+
`output/_probe_assembly_steps.py`（917 场「播种→装配完成」真实 PCG 步数反推，
注意 rng_state.txt 的 seed= 是 get_seed()=倒数第二链位——random_pcg.h:83-86 的
rand() 每次先把 current_seed=pcg.state——真 seed 在 oracle/fights.json）+
`output/oracle/align/gdcore_s2_check/*/kernel_state.txt`（内核 startBattle 前链态
落盘，ORACLE_ALIGN_DUMP_STATE=1）。

| 消耗点 | 步数/次 | 源码依据 |
|---|---|---|
| 物品/宝石实例化 = **场景双绑定** 2×BalancedRng | 4 | Item.tscn/Gem.tscn 根 + 覆盖脚本（*.tscn `[node … instance=ExtResource(1)]` + `script=ExtResource(2)`）；Godot 3.x 场景实例化先按基脚本建实例（成员初始化器跑一遍：`var chanceRng = BalancedRng.new()` → `Util.rng.randf_range(0.2,-0.2)`，Utility/BalancedRandom.gd:4，2 步），随后 script 覆盖重绑定**再跑一遍**。实测：`ItemScript.new()`=2 步、`Item.tscn.instance()`=2 步、`PortableAltar.tscn.instance()`=4 步（stage 探针 micro 切片） |
| FlickerAnimation 子节点物品入树 | +2 | Items/Animations/FlickerAnimation.gd:13-15（_ready → onAnimationEnded → callDelayed 实参 randf_range(minDist,maxDist)）；9 个场景（Flame/Oil Lamp/Burning Torch/Blade/Sword/Phoenix/Phoenix2/Magic Torch/Burning Coal(宝石)），实测仅 Flame(4,16)/(0.3,0.8)、BurningSword(maxSpeed=0.8) 覆盖默认 (0.1,3.0,0.3,1.0) |
| Potion 系物品入树（PotionConnector._ready） | +2 | Potion.gd:22-28（_ready 动态挂连接器）+ Items/Animations/PotionConnector.gd:12（modulate.g = randf_range(0.9,1.1)）；types 含 potion 共 18 件 |
| 卡牌物品入树（场景内嵌 CardConnector.tscn） | +2 | Items/Animations/CardConnector.gd:11（同式 randf_range(0.9,1.1)）；7 个场景（Ace of Spades/Darkest Lotus/Deck of Cards/Joker/Reverse/Holo Fire Lizard/The Fool），每场景恰 1 个 |
| 宝石入树（Gem._ready） | +2 | Items/Gems/Gem.gd:24（gemAnimation.advance(randf_range(0,10)))；types 含 gem 共 34 件。注意：神谕 lineups.json 的 gems 字段恒空（oracle_fight.gd `_item_snapshot` 用 `item.get("gems")`，原版 Item.gd 无该成员）——宝石在装配序里紧跟宿主，只有 rng_log 能看见 |
| 对手 Character 实例化 | 8 | Character.gd:94-97（4×BalancedRng 成员初始化器）；神谕在播种后 `opponentScene.instance()`（oracle_fight.gd:576） |
| Character.tscn 场景图 _ready 面（inventoryScene.instance、Buff×11、DamageSource×2、animation.play/advance） | 0 | stage 探针 stage5→stage6 段=0 步实测 |
| deserializeItems / setMaxHealth / setMaxStamina / initRoundResults / shop_closed→onPrepare / CT.initialize / shuffle+sort（全局链） | 0 | RunData.gd / Character.gd:871,948 / Game.gd / CombatLog.gd+CombatStatLogger.gd（grep 0 命中）/ CombatTimer.gd / rng_truth §1.4-2 |

**零残差验证**：917 场「真实步数 −（8 + 4×(物品+宝石) + 2×(flicker+连接器+宝石 ready 项)）」
全为 0（run1122_r11=348、run1029_r2=100 等逐场核对；output/_assembly_steps.txt 全表）。
旧 ORACLE_SCENE_DRAWS=14 是 run579_r18 单场误标定（全场真实差 0..444 步，非常数），已删。

### 修复落码（gd_core + gd_core_py 镜像 + 数据层）

- `gd_core/CoreItem.gd setup()`：第二次 `chanceRng = ctx.rng.BalancedRng.new(ctx.rng)`
  （覆盖脚本重绑定的成员初始化器重跑；第一个被丢弃）→ 每实例 4 步。
  `gd_core_py/gd_core/CoreItem.py` 同步。
- `gd_core/CoreItem.gd _readyInit()`：flickerAni（randf_range(minDist,maxDist) +
  `ctx.callDelayed(self,"flickerPlayAni",…)`）/ connectorReadyRoll（randf_range(0.9,1.1)）/
  gemRoll（randf_range(0,10)）三类入树消耗；新增 `flickerPlayAni()`（到点
  randf_range(minSpeed,maxSpeed)，神谕阻塞 tick 一次性约定）。Python 镜像同步。
- `gd_core/CoreItemData.gd/.py`：flickerAni/flickerMinDist/flickerMaxDist/
  flickerMinSpeed/flickerMaxSpeed/connectorReadyRoll/gemRoll 字段 + fromDict。
- `gd_core/CoreCombat.gd/.py` + `CoreContext.gd/.py`：**定时调用派发点从
  advancePhysicsFrame（tick 步骤②）移到 physicsTick 帧末（步骤⑧）**——对齐
  oracle_fight.gd tick_battle 的 SceneTreeTimer 位置（物品/角色/Timer 之后最后派发，
  判胜后不补发）；此前 flicker playAni/龙蛋孵化/RandomLoadoutBag 等定时抽会抢在物品
  判定链之前。
- 数据层：新 `tools/enrich_flicker_animation.py`（battle_items.json 增
  flicker_animation/边界值/connector_ready_roll/gem_roll；9+25+34 件）→
  `tools/gen_lineup_fixture.py compile_descriptor` 透传 → gd_core_runtime.json
  重新生成 + gd_core_test/item_battle_fixture.json 同步（517 件）。
- `gd_core_test/OracleAlignBattle.gd`：删 ORACLE_SCENE_DRAWS=14；descriptor_of 补
  7 个新字段；新增 `ORACLE_ALIGN_NO_INJECT=1`（阶段 2 无注入模式）与
  `ORACLE_ALIGN_DUMP_STATE=1`（startBattle 前链态落盘）；逐抽追踪改为自播种即开启。
- `simulator/gd_core_engine.py`：_descriptor 补 7 字段；reseed 注释更正（旧校准值 14 说明删除）。
- `tools/verify_oracle_s2.py`（新）：阶段 2 判定驱动——sample_seed 固定随机抽
  N 场（默认 20），无注入三方（oracle ↔ gdcore_s2 ↔ py_s2）渲染+canonical 逐行比对。

### 验证（本轮实测）

- **装配期逐位一致（本轮目标，已证）**：无注入下内核 startBattle 前链态与神谕
  rng_state.txt **逐位相等**（run1029_r2：6065263377169956062；run1122_r11：
  4780832677058801437——gdcore_s2_check/kernel_state.txt 对照）；917 场步数模型零残差。
- **无注入 20 场抽样全流比对**（sample_seed=20261007，
  output/oracle/alignment_s2.json）：**三方一致 0/20**；16/20 py≡gdcore、4/20 py 深局
  分歧（Holy Spear 42/43、resist 闸等翻译边界，与装配无关；run1493_r10 复核实为全对齐）。
  **未过闸的残差 = 阶段 1 残留清单 #1（战斗期未记日志消耗面）**：装配完成点链态已逐位
  相同之后，战斗期内神谕仍有内核未还原的裸消耗（run1029_r2 首分歧 event idx 5、
  run1122_r11 idx 10——与阶段 1 注入时代分歧位一致，非本轮回归）。本轮将「装配期差异」
  从该残差中剥离并证伪：分歧不再是装配造成。
- **无回归**：神谕语料 run1029_r2 以 ORACLE_DEBUG 重跑（备份
  output/_backup_run1029_r2 对照）events.json/rng_state.txt 逐字节一致；
  ORACLE-ALIGN(gd_core) 批量 20 场 PASS + 内核 selfcheck 逐字节一致；
  gd_core(Godot)↔gd_core_py 16/20 逐行一致（与阶段 1 末的翻译边界残差同源）。

### 残留清单（下轮入口）

1. **【阶段 1 残留 #1，现为一号位】战斗期裸消耗面**：装配完成点链态逐位相同之后，
   神谕在首个激活 pitch 附近仍有未还原消耗（run1029_r2 abs[55]=1.006657 从 S54 起
   任何纯步进都不可达——已排除纯步进、播种、行序错位；需事件对齐的双侧逐抽 bisect
   仪器，把每个裸消耗点归到源码行）。影响面 = 阶段 1 全量 914 场的 90%+ 分歧家族。
2. py↔gd_core(Godot) 深局翻译边界（本-round 4/20）：Holy Spear 伤害 ±1、resist 闸
   次序、长局 timed 调用——独立于消耗面。


---

## 2026-10-08 · 阶段1 第 2 轮：攻击面消耗族 + 事件形状 + py 孪生 tick 结构镜像

### 本轮起点

- 上轮末全量：`python -X utf8 tools/verify_oracle.py` → **3/914**（oracle≠gdcore 685、
  oracle≠gdcore 且 py 分歧 225、三方一致 3、py 缺产物 1）。
- 仪器升级：神谕 rng_log 已带 EVENT 标记（oracle/Core/CombatLog.gd:270-274）与
  randInBox/pickRandomElement 等消耗点标签；上轮"下轮入口 #1"的 2 抽 mystery 用
  「内核逐抽追踪 ↔ 神谕逐抽日志」对位攻击。

### 排障记录（重要：陈旧产物曾误导一轮）

- 先跑 `ORACLE_ALIGN_TRACE=1 ORACLE_ALIGN_CASES=run1122_r11` 内核逐抽追踪并与
  `output/oracle/fights/run1122_r11/rng_log.txt` 对位——**首查的 1429 行 trace 是
  上一会话的陈旧产物**（Godot 相对路径按**项目目录**解析，`ORACLE_ALIGN_OUT=output/…`
  实际写进了 `gd_core_test/output/…`，仓库根同名目录是旧文件）。用绝对路径重跑后
  内核在 jitter→TMH→激活段与神谕逐位一致（上轮已修对）。教训：批量产物一律用绝对
  ORACLE_ALIGN_OUT。
- trace 可见性缺口修复（行为不变，gd_core/CoreRng.gd）：
  `pickRandomElement` 原走裸 `rng.randi_range`（CoreRng.gd:125，消耗发生但不进
  trace——对位时呈现为「神谕多一抽」假分歧），改走追踪包装（tag 同神谕
  `pickRandomElement`，oracle/Utility/Util.gd:457）；`BalancedRng._init` 的
  `0.2/-0.2` 构造抽同改（原 CoreRng.gd:169 裸 rng.randf_range → 追踪版；
  神谕侧 BalancedRandom.gd:4 本就走 rng_trace_range）。

### 缺口 ⑦：addBonusDamage 家族的 DamageBuff 标签缺消耗（链位漂移主缺口）

**原版在做什么**：`Item.addBonusDamage(damage, removable=true)`（Item.gd:4036-4048）
在 damage≠0 时快照 Min/Max 并在 removable 时 `spawnLabel(Game.EventType.DamageBuff,
damage)` = Item.spawnLabel（Item.gd:4788-4791）→ Util.spawnLabelOnItem →
Item.getNextFreeLabelPosition（Item.gd:6487-6496）= **randInBox(-10,10) 2 抽，无事件**。
**gd_core 原来错在哪**：内核 addBonusDamage（原 gd_core/CoreItem.gd:993-997）只加减
数值——同族 reduceBonusDamage/purgeDamage 都带了标签（现 :1867/:1880），唯独
addBonusDamage/changeVaryingDamage/addMinDamage/addMaxDamage 四函数漏移植。
**逐抽对位实证**（run1122_r11，神谕行 565-573 + SRC 标记）：Magic Staff 每次攻击的
`onPreDealDamage_early → tryUseMana(-3) → Amulet of Agility 退款(+1)` 链条之后、
伤害 roll `randi_range(8,10)` 之前，神谕恰好多一对 randInBox(-10,10)（LABEL Magic
Staff，无 SRC 标记=非 Buff 增/失路径）——即 addBonusDamage(+3) 的 DamageBuff 标签。
修复前对位 352 行断，修复后 438 行断。
**修复**：gd_core/CoreItem.gd + gd_core_py/gd_core/CoreItem.py 镜像——
addBonusDamage 按 Item.gd:4036-4048 逐行还原（damage≠0 闸内：快照×2 + removable 时
spawnLabel）；changeVaryingDamage= addBonusDamage(damage,false)（原 Item.gd:4049-4050
就是这句调用——顺带修掉旧实现 `removableDam += damage` 不动 bonusMin/Max 的语义错）；
addMinDamage/addMaxDamage 补快照（Item.gd:4051-4058）。影响面：Magic Staff/Djinn
Lamp/Goobert 系/Steel Dragon 等一切「攻击附带永久增伤」物品，每次触发 2 抽。

### 缺口 ⑧：攻击事件形状分歧（target/params）

**原版在做什么**：`CombatLog.createEvent_Attack`（CombatLog.gd:653-678）**从不
setTarget**（DealDamage/CriticalDamage/MissedAttack 的 target 恒 null；setTarget 只
出现在 createEvent_Damage:695 等事件）；落空分支只有 `createEvent(..., MissedAttack)`
一句——无 damage 参数、无快照。
**gd_core 原来错在哪**：内核 createEvent_Attack（原 gd_core/CoreCombatLog.gd:72/:81）
给命中/落空分支都 setTarget，落空分支还多 `setParam("damage",…)` 与两次快照。
**实证**：run572/573 首分歧即 Death Scythe 首攻（oracle target=null / kernel
target=1）；神谕 MissedAttack 事件 `params={} target=None` vs 内核
`params={'damage':0} target=1`（run571 事件 id 92 对照）。
**修复**：gd_core/CoreCombatLog.gd + gd_core_py/gd_core/CoreCombatLog.py 镜像——删
两处 setTarget 与落空分支的参数/快照。

### 缺口 ⑨：py 孪生 tick 结构旧世界（上阶段残留 #2 的根源）

gd_core/CoreCombat.gd 的 physicsTick 已按 oracle tick_battle 次序重排（①Util 时钟
→②对手角色→③对手物品冷却→④combatTime→⑤玩家角色→⑥玩家物品冷却→⑦逐角色
[opponent,player] 的物理型 Timer 块→⑧疲劳→⑨SceneTreeTimer），注释即
run1122_r11 逐抽对位实证（gd_core/CoreCombat.gd:286-293）。py 孪生
（gd_core_py/gd_core/CoreCombat.py physicsTick）仍是旧结构：combatTime 在时钟前、
onTick 玩家在先、物品计时器混在冷却循环里、冷却遍历 ordered_items（混合双方）而非
各自 inventory 装配序。
**修复（三文件）**：
- CoreCombat.py physicsTick 按 gd_core 步骤①-⑨逐条镜像；
- CoreCharacter.py：physicsTick 拆为 physicsTickCharacter（眩晕+体力，gd_core
  CoreCharacter.gd:1823-1830）+ tickPhysicsTimers（TickTimer→Rage→Invul→AutoRage，
  gd_core :1837-1863）；TickTimer 状态从 CoreCombat 移入角色（__init__/combatStart
  置 1.0/True，对齐 gd_core :308-309/:406-407；combatEnd 不复位同 gd_core）；
- CoreItem.py：physicsTick 只留冷却面（gd_core CoreItem.gd:661-674），计时器+宝石
  推进拆 tickTimersPass（gd_core :714-718）。
**效果**：run571_r18 的 Djinn Lamp 事件 py t=63 与神谕一致（gd_core t=64 晚 1 tick）
——py 首次在 tick 级与神谕对齐；此前 16/20 的 py↔gd 深局分歧面大幅收窄到
「同一抽值下的 1-4 tick 触发漂移 + 个别链位差」。

### 验证（本轮实测）

- `python -X utf8 tools/verify_oracle.py`（全量 914 场，后台跑完）：
  **3/914 三方一致**（与上轮持平）；分布：oracle≠gdcore 且 py 分歧 909、三方一致 3、
  py 缺产物 2；定位：rng-mechanism 836、gd_core-kernel 73（上轮 87→73）。
- 复跑确定性：神谕 run1122_r11 单场重跑（ORACLE_ONLY_CASES + ORACLE_DEBUG）与冻结
  语料 events.json **语义逐位一致**（JSON 排序串比对输出 True），语料已原样恢复。
- 首 OG 分歧 index 分布：0-9 场 362、10-19 场 299、20-49 场 241、50-99 场 7
  （上轮 0-4 段 348 场 → 攻击形状/消耗族修掉后前段减少、中段增加——分歧点后移）。
- 攻击事件 target/params 族消失：抽查 5 场冒烟 OG/GP 对照中 attack 事件两侧均为
  target=null；MissedAttack 均为 params={}。

### 残留清单（下轮入口，按影响面排序）

1. **【数据层·最大家族】夹具缺宝石数据**：lineups.json 的 gems 恒空（oracle_fight.gd
   `_item_snapshot` 用 `item.get("gems")`，原版 Item.gd 无该成员），而宝石真值在
   history.db 物品元组的 "g" 字段。实证：run570_r18 玩家 Shaman Mask
   onCombatStart → `giveLucky(inventory.countSocketedGems())`（ShamanMask.gd:11-12）
   神谕 Lucky+16 vs 内核无此事件（夹具装配 0 宝石 → countSocketedGems=0）。修法：
   gen_fixture_from_lineup.py 的 oracle_mode 改读 fights.json→history 快照的物品
   元组 "g" 字段生成 gems 装配项（含 Kernel.place_gem 的宝石路径），或
   oracle_fight.gd::_item_snapshot 补 sockets 遍历后重导夹具。
2. **【rng-mechanism】同链位下的 1-tick 冷却触发漂移**：run571/run1122 的 Djinn
   Lamp（对手侧，Amulet of Agility +1.0 speedScale 加速下）神谕 tick 43 触发、
   gd_core tick 44——`triggerTime -= delta*getSpeed()` 的 speed 组成时序（heat 栈
   0.02/s 的 getStackSpeedMods 随 tick 变化）或 FP 累积差。需内核侧 per-tick
   speed 快照对位仪。
3. **【py↔gd 残差】py 链位/tick 差 1-4 tick**（run572 t=67 vs 71 等）：py 侧无
   逐抽追踪仪器，先补 CoreRng.py 的 oracle_trace 同构（ORACLE_ALIGN_TRACE 语义），
   再按 gd_core↔神谕同法对位。
4. **【gd_core-kernel 73 场】**：上轮 R2 家族余量（首例 run579_r18），沿用
   gd_core↔decomp 同名文件 diff 法。
5. Goobert 计数族：内核首治 5.483s vs 神谕 2.383s（onItemActivated 计数路径，机制
   存在但触发晚——待 1/2 修后重查是否为连带位移）。

### 仪器（本轮沉淀）

- gd_core/CoreRng.gd：pickRandomElement/BalancedRng 构造抽补追踪（tag 同神谕）；
  新增 ORACLE_ALIGN_STACKTRACE=1 栈签名（release 版 get_stack 恒空，留作 debug 构建
  备用）；OracleAlignBattle.gd trace 写盘带第 6 列。
- oracle/Utility/Util.gd：ORACLE_STACKTRACE=1 时 rng_trace_* 附调用栈（release 下
  为空）；oracle/Items/Item.gd getNextFreeLabelPosition 与 oracle/Core/Buff.gd 增/失
  标签打 LABEL/SRC 无链标记（ORACLE_STACKTRACE=1 才记）——本轮靠 SRC 标记把
  run1122 的第三对 randInBox 归因到 addBonusDamage。神谕单场复跑驱运：
  `ORACLE_ONLY_CASES=<id> ORACLE_DEBUG=1 output/godot36/Godot_v3.6-stable_win64.exe
  --headless --quiet --audio-driver Dummy --path oracle --script oracle_fight.gd`。
- 教训：Godot 相对路径按项目目录解析——批量产物一律绝对路径。

### 红线自查

- 全程无头后台（--headless --quiet --audio-driver Dummy，stdout/stderr 重定向文件）；
- 神谕语料只读：单场复跑先备份（output/_backup_run1122_r11_stale）、验证语义一致后
  原样恢复；未触碰 Steam 版游戏目录；
- 无在线/排名/休闲模式入口；未执行任何 git 提交/推送类命令。


### 同日补记：run_gd_core 管线闸门排查 + py 树重生 + 最终全量

**闸门排查（run_gd_core.py 17 道闸）**：
- SURVEY_VERIFY 7 项计数漂移：`git archive HEAD` 快照对照证明 HEAD 树 21/21 全绿，
  漂移全部来自工作区未提交改动（上会话电荷机制：+1 内嵌类/+2 %格式化/+1 is/+2
  .new(/+5 .size()/+3 push_back/+8 Vector2；本会话：+1 %格式化与 +1 .size() 为
  CoreRng 栈签名诊断行）。已按该闸门自身的注释先例更新 tools/survey_gd_syntax.py
  的 CLAIMS（逐条注明来源），复跑 21/21 PASS。
- 闸 4 Smoke 7 项战怒时长断言失败：**既有债**——Smoke.gd 与 HEAD 相同未被改，
  startBattleRage/_setRageTimer 两版逐字节相同，失败源于上会话未提交的
  CoreCharacter/CoreContext tick 重构与旧断言的矛盾（本会话未触碰 gd_core
  /CoreCharacter.gd）。
- 闸 8 LineupBattle 4 项失败：**既有债**——上会话夹具重写把 LINEUPS 的 8 套手工
  矩阵换成实录阵容（工作区仅剩 2 条 truth 项且全在 SKIPPED），未改的闸门工具仍
  断言 ≥8 套（lineup_gem_test 键同批被删，run_gd_py 的宝石测试同因挂）。
- 与本会话改动直接相关的闸均单测通过：闸 9 ItemBattle 517 件 **PASS**、闸 11
  check_gd_py **PASS**、闸 12 verify_godot_rng **PASS**（1440 值 0 差异）、
  run_gd_py 的 assemble/pairs/determinism 三段 PASS。

**py 树重生两次引发的修复**（run_gd_core 的 GEN_GD_CORE_DATA 闸会经 gd_to_py 重生
gd_core_py 全树——手改镜像会被覆盖，本轮起 py 修复一律改 .gd 源 + 转写器规则）：
1. gd_to_py.py 新增 `OS.get_environment→_os_environ_get` 转写规则 + _rt.py 垫片
   （os.environ.get(name,"")，__all__ 登记）——CoreRng._stacktrace 首个用例此前
   原样漏成 `OS.…` 致 py 全树 ImportError。
2. _registry.py `C()` 未命中时按名**惰性导入**对应生成模块（幂等防递归）——
   转写器把含 `_R.C("CoreConst")` 动态键的成员字典提升到类体（CoreCharacter
   classResources），导入期先于拓扑序靠后的 CoreConst 注册即 AttributeError 级联。
3. gd_core/CoreItem.gd `_chargeInventoryCells`：`out.push_back(跨行实参)` 改为
   先存局部变量再单行 push_back——gd_to_py 的方法调用改写器按行解析实参，跨行
   续行会原样漏成 `'list' has no attribute 'push_back'`（重转后 164 场 py 重放
   失败实证；改后全库扫描 0 处同类位点）。

**最终全量**（本日第 3 次，`python -X utf8 tools/verify_oracle.py`，py 侧用重生树）：
- **三方一致 3/914**；分布：oracle≠gdcore 且 py 分歧 908、三方一致 3、py 缺产物 3
  （run837_r18/run845_r18 为上轮残留 #5 的既有 IndexError 家族；run1129_r18 同族
  新增——重生树对特定阵容的装配索引问题，与消耗面对齐无关）；
- 定位：rng-mechanism 835、gd_core-kernel 73（上轮 87 → 73）；
- 对齐数与上轮持平（3/914）但分歧家族构成实质收敛：攻击事件 target/params 族
  （原 run572/573 首分歧）已消失、消耗面缺口⑦修复（run1122 对位 352→438 行）、
  py 孪生 tick 结构与神谕同序（run571 Djinn Lamp py t=63 = 神谕，gd_core t=64 晚
  1 tick）。对齐数不涨的瓶颈已转移到「夹具缺宝石数据」与「1-tick 冷却漂移」两族
  （见上节残留清单 1/2），属下一轮主攻面。

### 红线自查（补记）

- 未执行任何 git 提交/推送/工作树变更类命令（git archive 为只读）；
- 神谕语料冻结态保持（run1122_r11 重跑先备份后原样恢复）；
- 全程无头后台，未打开任何可见窗口。


---

## 2026-10-08 · 阶段1 第 3 轮：宝石真值夹具 + Buff 三分支标签 pos 消耗更正

### 本轮起点

- 上轮末全量 3/914（rng-mechanism 835 / gd_core-kernel 73 / py 缺产物 3）。
- 上轮"下轮入口"第 1 位=夹具缺宝石数据。

### 缺口 ⑪【数据层】：lineups.json 宝石恒空 → 宝石真值快照

**根因**：原版宝石存在 `sockets` 子节点（extracted_running/decomp/Items/Item.gd:3013-3019
`getGems() = [socket.getGem() for socket in sockets]`），Item **没有** `gems` 成员——
oracle_fight.gd `_item_snapshot` 的 `item.get("gems")` 恒 null → 917 场 lineups.json
的 gems 恒空 → 夹具装配的宝石面（3030 个宝石实例/34 种，语料实测）整体丢失。
**修复**：
1. `oracle_fight.gd _item_snapshot` 改走 `item.getGems()`，宝石身份用
   `descriptor.identifier`（与 battle_items.json 键一致；getName 是显示名）；
2. 新增 `ORACLE_LINEUPS_ONLY=1` 模式：装配完成即导 lineups 并收场（不写
   rng_state/events/rng_log/result——语料 events 保持冻结）；resume 判据改为
   lineups.json 的 `snapshot>=2` 字段（dump_lineups 新增版次标记）；旁路
   determinism 复跑；配合既有 ORACLE_FIGHT_CHUNK 分块（MessageQueue 只能靠
   配额退出 flush，首次无分块跑在 560/917 卡死实证）。
3. 917/917 场重导完成（分块 12+1 次）：**3030 个宝石实例、34 种、全部在
   battle_items.json 内**；Corrupted Crystal×550、Chipped Topaz×270 等。
4. 夹具重生：914 场（run1294_r6/run1445_r18/run626_r6 三场因快照新暴露的
   `Coins` 宝石不在 gd_core 描述符表被剔除——如实记录，覆盖集成员变化）。
**验证**：run570_r18 的 OG 首分歧从 idx 4（Shaman Mask Lucky+16 缺失）移到
idx 10——宝石装备效果（含 16 颗插宝石的 countSocketedGems 路径）已在内核复现。

### 缺口 ⑫：Buff 三分支标签的 randBuffLabelPos 消耗更正（阶段1 误读）

**原版在做什么**：Buff.gd:125/140/237 三处（resisted/reflect/protected）——
`Util.spawnXxxLabel(type, <chr>.randBuffLabelPos(), n)` 的 **pos 是调用点实参**
（Character.gd:688-691 = (-60,60)+(-40,40) 2 抽，必求值）+ spawnXxxLabel 内部
`randBuffLabelDir` 1 抽（Util.gd:868-869 / 909-914），共 3 抽。
**gd_core 原来错在哪**：阶段1 按 run1160_r18 语料误读为「pos 未消耗，只补 dir 1 抽」
（gd_core/CoreBuff.gd reflect :157-165 / resisted :177-188 只抽 dir；protected :286
零消耗）——该"语料实证"出自 golden model ±1ULP 噪声期（阶段1 残留清单 #4 自认
~15% 误报），run570_r18 的带标签逐抽日志直接证伪：Snowball 反射 Cold 的序列为
`roll×2（reflect 翻转）→ (-60,60)/(-40,40)（pos）→ (-75,-120)（dir）→ randInBox×2
（Cold 栈标签）→ EVENT 110`。
**修复**：gd_core/CoreBuff.gd 三分支统一补 `randBuffLabelPos()`（2 抽）+ 原有 dir
（1 抽）；py 树经 gd_to_py 重生同步；check_gd_py PASS。
**单场复验**：run570_r18 开战段逐抽对位 35 → 135 行（reflect 序列后新分歧点为
playAttackAnimation 闩语义的更深层细节，见下轮入口）。

### 仪器（本轮新增）

- **tick_states 对位仪**：oracle_fight.gd（ORACLE_DEBUG 时落盘
  tick_states.txt，每物理 tick 的 Util.rng.state）↔ OracleAlignBattle.gd
  （ORACLE_ALIGN_TRACE=1 时同构落盘）——跨引擎「首个分叉 tick」直指定位。
  run570 实测：两引擎链从 tick 1 即分叉（开战序列内），与事件级 idx 10 分歧自洽。
- oracle_fight.gd `lineups_snapshot_done()` 续跑判据 + `snapshot` 版次字段。

### 验证（本轮实测）

- 宝石夹具全量：`python -X utf8 tools/verify_oracle.py` → 3/914（gd_core-kernel
  73→58；run570 OG 首分歧 idx 4→10）。对齐数持平：首个分叉普遍仍在开战批量
  内（0-9 段 335 场），宝石修复让「事件存在性」对齐前进（Shaman Mask 类），
  但「抽值级」对齐还差更早的链位差。
- Buff 三分支修复后的全量：见文末补记（后台跑完后追加）。

### 残留清单（下轮入口）

1. **playAttackAnimation 闩语义**（run570 对位 135 行后的新分歧）：神谕在
   Mana 事件+标签+1×(0.9,1.1) 后又抽 1×(0.9,1.1) 再进 jitter 段，内核直接进
   playAnimation 4 抽块——attackMovingForward 闩的置位/复位时序与
   playCombatAni 分流需按 Character.gd:445-462 逐行重审（tween 冻结约定的
   复位语义「一旦置真不复位」可能只对 movebackTween 成立）。
2. **1-tick 冷却触发漂移**（同上轮）：Djinn Lamp 型，tick_states 仪已就位。
3. gd_core-kernel 58 场（多数为链位漂移的下游症状分类，同 Potion Belt 型
   「随机 7 选 1 抽不同 index」——修好链位即消退）。
4. Coins 宝石不在描述符表（3 场被剔）：如需覆盖，可在 battle_items.json 补
   Coins 描述符（ItemBook 有该生成物）。

### 补记：Buff 三分支修复后的最终全量（本日第 4 次全管线）

`python -X utf8 tools/verify_oracle.py`（914 场，宝石夹具 + Buff 三分支 pos 消耗）：
- **三方一致 3/914**；分布：oracle≠gdcore 且 py 分歧 910、三方一致 3、py 缺产物 1；
- 定位：rng-mechanism 858、gd_core-kernel **52**（第 1 轮末 73 → 宝石轮 58 → 本轮 52，
  三轮连续下降；Potion Belt 型「随机 7 选 1 抽不同 index」的分类多属链位漂移下游
  症状，链位族修复后会继续消退）；
- 对齐数持平于 3/914：首个分歧普遍仍在开战批量内（抽值级），下一层家族 =
  playAttackAnimation 闩语义、1-tick 冷却漂移（上节残留清单 1/2）。单场深度指标：
  run570 开战段逐抽对位 35 → 135 行。

### 红线自查（第 3 轮）

- 全程无头后台（--headless --quiet --audio-driver Dummy，stdout/stderr 重定向文件）；
- 神谕语料 events.json 冻结保持（lineups-only 模式不触碰战斗产物；
  run570 单场 ORACLE_DEBUG 复跑按惯例备份/恢复）；
- 未执行任何 git 提交/推送类命令；未触碰 Steam 版游戏目录。


---

## 2026-10-08 · 阶段1 第 4 轮：animationScene 全假更正（playAnimation 4 抽族移除）+ jitter 区间分类新信号

### 本轮起点

- 上轮末 3/914；run570 开战段对位 140 行后暴露 jitter 区间分类差。
- 本轮先用 ANIM 标记（oracle/Items/Item.gd playAnimation 入口 rng_log 标记行，
  绕开 --quiet 吞 print 的问题）实证：**run570 整场神谕 playAnimation 被调用 141
  次，其中 descriptor.animationScene 真值 0 次**——神谕侧 4 抽块发生 0 回
  （内核同场 66 回 × 4 抽 = 264 步纯多耗）。

### 缺口 ⑬【数据层】：animationScene 标志与神谕运行时不符 → 全部置假

**根因**：oracle/Sheets/ItemBook.gd:742 `var dir = Directory.new()`（默认打开=进程
CWD），:804 `dir.file_exists("Items/Animations/…Animation.tscn")` **按进程工作目录
解析**——批量从仓库根启动，相对路径全部探测失败 → 神谕 ItemBook 的
animationScene 对所有物品恒 null（141 次调用 0 真值实证；86 个 tscn 文件在
oracle/Items/Animations/ 下存在但探测不到）。对齐目标是受控神谕语料 ⇒ 内核的
animationScene 必须同取「全假」。
**修复**：assets/battle_items.json 518 件 has_animation_scene 全部置 false
（原 128 件为 true）；gd_core_runtime.json（gen_gd_core_data）与
gd_core_test/item_battle_fixture.json（gen_lineup_fixture，animationScene 128→0）
重建。
**单场复验**：run570_r18 开战段逐抽对位 140 行（35→135→140），且分歧点后的
链值**逐位重新对齐**（O455/K423=1.013949、O456/K424=0.90036、O457/K425=
49.382389…）——4 抽块移除后两链重新会合，证明该族确为纯多耗。

### 新信号：jitter 区间分类/次数差（1-tick 漂移的根因层）

run570 全场 jitter 计数：神谕 (0.95,1.05)×**84** + (0.975,1.05)×57；内核
(0.95)×**59** + (0.975)×58。两处分歧：
1. **分类差**：开战批量同 3 个链位，神谕抽 (0.95,1.05)、内核抽 (0.975,1.05)
   （O452-454 vs K420-422）——adjustCooldown（Item.gd:3789-3794）分支的
   ownerType/league 判定两侧不同，或 preCombatStart 遍历序里物品归属不同。
   注意 randf_range 的区间只影响返回值不影响链步进，故 3 抽后两链重新会合
   （O455=K423）——但返回值不同 ⇒ triggerTime 不同 ⇒ 1-tick 漂移的直接来源。
2. **次数差**：神谕 player-range jitter 多 24-25 次 = 神谕侧 adjustCooldown 总
   调用更多（141 vs 117）——某些玩家物品在神谕触发更频繁（速度组成/冷却推进
   差异），待 tick_states 仪按 tick 对位归因。

### 验证（本轮实测）

- run570 单场：4 抽块移除后 140 行对齐且链值重会合（上节数字）。
- 全量：`python -X utf8 tools/verify_oracle.py`（见文末补记——后台跑完后追加）。

### 残留清单（下轮入口）

1. **jitter 区间分类差**：3 物品的 adjustCooldown 分支两侧不同——先查这 3 个
   链位对应的物品（events + 激活序），再对 preCombatStart 的 items 数组
   （playerItems+opponentItems 序）与 ownerType 赋值两侧对表。
2. **jitter 次数差 24-25**：玩家物品触发频次——speed 组成（heat×0.02 的
   getStackSpeedMods）与冷却推进的 tick 对位（tick_states 仪已就位）。
3. playActivateAnimation 闩（attackMovingForward）复位语义（上轮残留 1，被本
   轮 4 抽块噪声遮盖，移除后重新可见）。

### 补记：animationScene 修复后的最终全量

`python -X utf8 tools/verify_oracle.py`（914 场，animationScene 全假 + 宝石 + Buff
三分支 + 攻击事件形状 + addBonusDamage 全部在位）：
- **三方一致 3/914**；分布：oracle≠gdcore 且 py 分歧 909、三方一致 3、py 缺产物 2
  （run837_r18/run845_r18 既有 IndexError 家族）；
- 定位：rng-mechanism 865、gd_core-kernel **44**（第 1 轮末 73 → 58 → 52 → 44，
  四轮连续下降——行为分歧族持续收敛）；
- 对齐数持平 3/914：抽样级对齐的前置族已按本轮残留清单排定次序——
  ①jitter 区间分类差（3 物品 ownerType/league 分支，1-tick 漂移直接来源）
  ②jitter 次数差 24-25（玩家物品触发频次/speed 组成）
  ③playActivateAnimation 闩复位语义。
  三者均在 tick_states/逐抽对位仪的射程内，且不再有「整族凭空多耗」级缺口。


---

## 2026-10-08 · 阶段1 第 5 轮：adjustCooldown ownerType 分支 + stun 双分支标签族

### 缺口 ⑭：adjustCooldown 按宿主角色判而非 ownerType（jitter 区间分类差根因）

**原版**：Item.gd:3789-3794 `if ownerType == Owner.Opponent and (isBelowLeague(Master) or
Lobbies)` → (0.975,1.05)，否则 (0.95,1.05)。**内核错在** gd_core/CoreItem.gd:419 按
`character_.playerId == OPPONENT`（宿主角色）判——**插座宝石 ownerType = Owner.Socket**
（Item.gd:3041 setGem），挂对手物品也不该进 0.975 分支。run570_r18 开战段 3 个链位
实证：神谕 (0.95,1.05) vs 内核 (0.975,1.05)（O452-454 vs K420-422），返回值差 ⇒
triggerTime 差 ⇒ 1-tick 触发漂移。修复为按 `ownerType == CoreConst.Owner.Opponent`
判；py 经 gd_to_py 重生同步（check_gd_py PASS）。

### 缺口 ⑮：stun 双分支的 randBuffLabelPos+Dir 标签族补全

- 抵抗分支（Character.gd:1074）：`Util.spawnBuffLabel(StunResisted,
  randBuffLabelPos(), duration)` = pos 2 抽 + 内部 dir 1 抽；内核只挂钩子零消耗
  （run570 对位 274 行处实证：神谕 EVENT 1 后 (-60,60)/(-40,40)/(-75,-120) 三行 →
  EVENT 10，内核直跳 EVENT 10）。已补。
- 命中分支（Character.gd:1091-1096 playStunAnimation）：duration>0 时
  `Util.spawnBuffLabel(Stun, randBuffLabelPos(), duration)` 同为 3 抽（endStun 的
  duration=0 分支无消耗）。内核 playStunAnimation 是钩子，已按 duration>0 闸补
  pos+dir。全族清点：Buff.gd:125/140/237（第 2 轮已修）+ Character.gd:559
  critResisted（内核已有）+ :1074/:1093（本轮）——pos+dir 标签族至此全量对表。
- py 重生同步；run570 单场对位 140 → **274 → 281 行**。

### 残留清单（下轮入口）

1. **O593 4 抽块归因矛盾**：神谕 rng_log 在 EVENT 0 后出现
   (-30,30)/(-100,100)/(-5,5)/(0.8,1.2)（ItemAnimation.intialize 特征），但同文件
   的 ANIM 标记（playAnimation 入口）141 次全为 scene=False——标记或调用方有一处
   未被发现（intialize 的其他调用方 / tscn 覆写 export 的同值巧合 / 标记条件）。
   下一轮先把 ANIM 标记移到 intialize 内并记录 aniName。
2. jitter 次数差（神谕 0.95×84 vs 内核 0.95×75，收敛中）：部分为 ⑭ 修复的连带
  （宝石 jitter 归入 0.95），余下待 ownerType 修复后的全场重对位。
3. playActivateAnimation 闩复位语义（attackMovingForward）。

### 验证（本轮实测）

- run570 单场逐抽对位：140 → 274（⑭ 后）→ 281（⑮ 后）。
- 全量：`python -X utf8 tools/verify_oracle.py`（见文末补记）。

### 红线自查

全程无头后台；语料冻结（run570 复跑备份/恢复惯例）；未执行任何 git 写操作；
未触碰 Steam 版游戏目录。

### 补记：第 5 轮修复后的最终全量

`python -X utf8 tools/verify_oracle.py`（914 场，adjustCooldown ownerType 分支 +
stun 双分支标签族在位）：
- **三方一致 3/914**；分布：oracle≠gdcore 且 py 分歧 910、三方一致 3、py 缺产物 1
  （run837_r18 既有 IndexError 家族）；
- 定位：rng-mechanism 865、gd_core-kernel 45（五轮：73→58→52→44→45，稳定于 44-45
  ——纯行为分歧族已近收敛完毕，余量主要是链位漂移的下游分类）；
- 对齐数持平 3/914：抽值级对齐的剩余三层已排定（O593 4 抽块归因矛盾、jitter
  次数差余量、playActivateAnimation 闩），均在逐抽对位仪射程内。
- 单场深度：run570 开战段逐抽对位 140 → 274 → 281 行（五轮累计：35 起）。


---

## 2026-10-08 · 阶段1 第 6 轮：animationScene 回滚更正（第 3 轮误判）+ Rainbow Orb 数量差锁定

### 第 3 轮误判的更正

第 3 轮依据「ANIM 标记 141 次全 scene=False」把 animationScene 全置 false——本轮
复核发现该计数是**场景对象字符串化的解析误读**：旧标记值是 `str(scene)`（PackedScene
对象串），按 token 找 "True" 永远不中。当前权威 oracle 日志实证
`ANIM Steel Dragon True`（4 抽块真实发生，SteelDragonAnimation.tscn 存在且装载）。
**回滚**：重跑 tools/enrich_animation_scene.py（文件存在性口径，128/518 真）+
gen_gd_core_data + gen_lineup_fixture 重建双资产（Steel Dragon=True 已核）。
教训：标记值必须用 `!= null` 布尔而非对象 str（第 5 轮已改）。

### 内核 ANIM 标记就位

gd_core/CoreItem.gd activate() 的 playAnimation 内联块（animationScene 闸内）加
ANIM 标记行（与神谕同构，不消耗链）。run570 对位实证：内核 4 抽块属 Steel
Dragon（True），神谕同块在其自身时序位——两侧都按各自描述符播动画，剩余分歧是
**激活次序/物品数量参数**层（见下）。

### 锁定的下一个真分歧：Rainbow Orb mana 数量

run570 首分歧（第 1 轮 idx 10 起）：神谕 Rainbow Orb +10 vs 内核 +9（idx 10 事件
params）。注意两侧在数量分歧点之后抽值仍长时间对齐——数量差不改链步进，只改事
件参数与后续 lucky/mana 相关判定。下轮：核对 battle_items.json Rainbow Orb
namedParams/params 与 ItemData_e.csv 原值，并查 giveMana 数量公式（是否吃 lucky
加成——幸运层数在两侧是否同值）。

### 验证

- run570 单场：回滚后与神谕的分歧点回到 idx 10（第 1 轮已知位置）——动画族对齐
  不再是该场的遮蔽项。
- 全量：`python -X utf8 tools/verify_oracle.py`（见文末补记）。

### 补记：animationScene 回滚后的最终全量

`python -X utf8 tools/verify_oracle.py`（914 场，animationScene 恢复文件存在性真值
+ 本会话全部在位修复）：
- **三方一致 3/914**；分布：oracle≠gdcore 且 py 分歧 910、三方一致 3、py 缺产物 1；
- 定位：rng-mechanism 859、gd_core-kernel 51（回滚后从错误低点 44/45 回到 51——
  第 3 轮的全假置位曾让内核少播 Steel Dragon 类动画，回滚后恢复与神谕同播）；
- run570 首分歧锁定在 idx 10（Rainbow Orb mana 数量 +10 vs +9，第 1 轮即知），
  后续抽值长程对齐——下一轮主攻 Rainbow Orb 数量公式/数据。
- 本会话五轮累计修复（全部带语料实证）：攻击事件形状、addBonusDamage 标签族、
  Buff 三分支 pos+dir、stun 双分支 pos+dir、adjustCooldown ownerType 分支、
  宝石真值夹具（3030 实例）、py 孪生 tick 结构镜像、转写器 OS 规则/注册表惰性
  导入、animationScene 真值（回滚第 3 轮误判）、ANIM/SRC/LABEL/tick_states 四套
  对位仪。


---

## 2026-10-08 · 阶段1 第 7 轮：Rainbow Orb 数量差调查轮（无落码，如实记录）

### 调查结论（下轮直接可用）

run570 idx 10 首分歧 = Rainbow Orb onCombatStart 的
`giveMana(countTypes(getAffectedItems())[Type.Magic] * getP("mana"))`
（oracle/Items/Exclusive/RainbowOrb.gd:13-14）。实测神谕 +10 / 内核 +9。

静态核算（gd_core_test/oracle_align_cases.json 的 run570 玩家夹具）：
- 夹具受影响格 = 8 格（color 0/Primary，rotation 0，占格 (5,1)）；
- 与这 8 格 collision 相交的邻居 12 件，其中 types 含 'magic' 者 3 件
  （Mana Orb、Spectral Dagger ×2）→ ×mana 参数 = 内核的 +9（mana=3）；
- 神谕 +10 ⇒ 神谕的 getAffectedItems 计了 **10 件**——超过 8 格的物品数上限，
  说明两处口径差（按优先级）：
  1. **袋内物品入格**：原版 Bag.getItemsInside = inventory.getItemsInCells(
      occupiedCells)（Bag.gd:158-161）——袋内容物注册进 filledCells 的格子口径，
      使 affected 格查到袋内 Magic 件（药水多为 magic 型）；内核 CoreGrid 的
      bagCells/filledCells 双字典（CoreGrid.gd:39/93-100）对袋内容物的注册粒度
      待逐行对表（第 1 轮修过「inside 计数看见」，但 affected 查询路径未验）。
  2. **受影响格几何**：夹具 8 格来自 battle_items 的 grid 数据；原版
      RainbowOrb.tscn 的受影响 TileMap 格若 >8（光环形），神谕集合更大。

### 本轮状态声明

- **无落码修复**（调查轮）：两处候选缺口需要 CoreGrid 装配/查询的逐行对表与
  RainbowOrb.tscn 几何核对，非小改动；未动代码 ⇒ 全量验证结果与第 5 轮末一致
  （`python -X utf8 tools/verify_oracle.py` 终局 3/914，gd_core-kernel 51，
  本会话最近一次全量即当前代码态的验证）。
- 红线自查：全程无头后台；未执行任何 git 写操作；未触碰 Steam 版游戏目录；
  语料冻结保持。


---

## 2026-10-08 · 阶段1 第 8 轮：Rainbow Orb 几何候选排除，根因锁定袋内注册

### 核查结果（第 6 轮两候选的裁决）

1. **受影响格几何：排除**。oracle/Items/Exclusive/RainbowOrb.tscn:43 CollisionMap
   tile_data 解码（(y<<16|x) 带符号 16 位，9 三元组）= 8 个 tile4 受影响格 +
   1 个 tile3 自格；与 battle_items.json 的 grid.affected_cells **集合恒等**；
   夹具 placement_of（rot=0，min=(-1,-1)，position (5,1)）平移后 8 格
   {(3,1),(4,0),(4,2),(5,-1),(5,3),(6,0),(6,2),(7,1)} 与 tscn 真值逐格一致。
   （第 6 轮我误读该环形为 8 邻域——更正。）
2. **袋内物品注册：确认为根因**。神谕在 8 格里计到 **10 件** Magic 型
   （getItemsInCells 每格一物、去重，8 格 ≤8 件）⇒ 超出格数的物品只能来自
   **袋内容物同时可见**：原版 Bag.getItemsInside =
   inventory.getItemsInCells(occupiedCells)（Bag.gd:158-161）——袋内容物注册在
   filledCells 的格子口径使 affected 查询直接看见袋内 Magic 件（药水类）。
   内核 getItemsInCells（CoreGrid.gd:93-100）只读 filledCells[cell] 单物，
   袋内容物的注册粒度与原版不一致（第 1 轮修的 inside 计数走的是 bagCells
   另一路，affected 查询路径未覆盖）。

### 下轮主攻（根因已锁）

对表「袋内容物在 filledCells 的注册」：原版 placeGeneratedItem/addToInventory 对
袋内物品写 filledCells[cell] 的时机与覆写序（bag vs content 谁是 cell 的最终
登记物），内核 CoreGrid.addItem 的 bagCells 分流（:191）按同口径补齐；run570
单场验证 Rainbow Orb +10。

### 本轮状态声明

调查轮，无落码；全量验证沿用第 5 轮末当前代码态结果（3/914，
gd_core-kernel 51）。红线自查：全程无头后台；未执行任何 git 写操作；
未触碰 Steam 版游戏目录；语料冻结保持。


---

## 2026-10-08 · 阶段1 第 9 轮：袋内容物位置实证 + countTypes 语义锁定

### 实证（run570 权威 lineups vs 夹具逐一比对）

- 袋内容物**就是顶层条目**：lineups 48 件玩家物品含全部袋内容物（(4,2) 处
  Protective Purse 与 Mana Orb 同格多物、(5,0)/(0,0)/(8,2) 等 9 格同格双物），
  位置与夹具 occupied 逐一吻合（Spectral Dagger 三把 (7,6)/(6,2)/(5,2)、
  Mana Orb (7,5)/(4,2)）——装配位置无差。
- 受影响环 8 格的顶层占格物 7 件：Magic 仅 2（Mana Orb(4,2)、Spectral
  Dagger(6,2)）。
- **算术锁定**：内核 +9 ⇒ count 9 × mana 1；神谕 +10 ⇒ count 10 × mana 1。
  但 8 格 × 每格一物 ≤ 8 < 9/10——**两侧的计数源都不可能是单次
  getItemsInCells(ring) 的直接返回**：countTypes（Item.gd 的实现，待读）或
  cacheAffectedItemsForCombat 的缓存口径（Affected 多色合并/多副本展开）必有一
  处把计数放大，且两侧放大系数不同（9 vs 10）。下轮先读 countTypes 与
  cacheAffectedItemsForCombat 的原文（Item.gd:1174-1180 区域），再对内核
  CoreItem 同名实现对表。

### 本轮状态声明

调查轮，无落码；全量验证沿用第 5 轮末当前代码态结果（3/914，
gd_core-kernel 51）。红线：全程无头后台；未执行任何 git 写操作；未触碰
Steam 版游戏目录；语料冻结保持。

### 补充（同轮）：mana=2 使内核 +9 成为公式级矛盾

Rainbow Orb named_params.mana = **2.0**（battle_items.json）。神谕 +10 = count 5 × 2
✓；内核 **+9 不能被 2 整除** ⇒ 内核的数量公式或其 count 口径必然偏离原版
（候选：gd_core_items/Exclusive/RainbowOrb.gd 的 onCombatStart 公式、countTypes
实现、或 getP("mana") 解析）。下轮第一件事：并排读
oracle/Items/Exclusive/RainbowOrb.gd:13-14 与 gd_core_items/Exclusive/RainbowOrb.gd
同名函数，逐 token diff。


---

## 2026-10-08 · 阶段1 第 10 轮：+9/+10 破译——Mana 层数上限调整，真实分歧上移

### 破译

`getP("mana")` 链路核实无差：CoreItemData.getP（gd_core/CoreItemData.gd:146-149）
→ namedParams["mana"]=2.0，夹具/运行时/内核三处一致。结合 Buff.gainTemporary 的
`amount = int(min(amount, MAX_STACKS - current))`（gd_core/CoreBuff.gd 与
extracted_running/decomp/Core/Buff.gd:141-142 同式）：

- **两侧请求相同**：count(Magic)=5 × mana 2 = **10**（整除矛盾解除——第 8 轮的
  「内核 +9 不可整除」的预设公式不成立）；
- **落地值不同**：神谕当时 current mana=0 → +10；内核当时 current mana=1 →
  被 MAX_STACKS-current 削成 **+9**（事件参数是调整后的落地值）；
- ⇒ 真实首分歧在**更早的 Mana 增减事件**（run570 开战批量里 Rainbow Orb 之前的
  Mana Orb +1 等）造成的 current mana 差 1，或其发生时序。

### 下轮主攻（收窄到具体事件）

1. 列出 run570 开战批量 idx 0..10 的全部 Mana 事件（两侧）与每个事件后的
   current mana 推演（MAX_STACKS 值从 CoreConst/Buff 常量核实）；
2. 差 1 的来源候选：Mana Orb +1 的触发次序（同 tick 双方齐触发时的遍历序——
   tick_states 仪可直接读出首个分叉 tick）、或某 Mana 事件的数量参数差。

### 本轮状态声明

调查轮（公式级矛盾解除，定位上移一层），无落码；全量验证沿用当前代码态的
第 5 轮末结果（3/914，gd_core-kernel 51）。红线：全程无头后台；未执行任何
git 写操作；未触碰 Steam 版游戏目录；语料冻结保持。


---

## 2026-10-08 · 阶段1 第 11 轮：Shaman Mask 幸运计数现状锁定（调查轮，无落码）

### 实证（当前全量产物 run570）

- 事件 0..17 两侧一致（含 idx 4 玩家 Shaman Mask Lucky **+16** 两侧相同）；
  首分歧 = idx 18 对手 Shaman Mask：神谕 **+16** vs 内核 **+14**。
- lineups 宝石快照：两侧各 **13** 颗插座宝石（清单完全镜像）；夹具无插座截断。
- 算术：玩家侧内核以 13 颗装配却计 +16（多计 3），对手侧计 +14（多计 1）；
  神谕两侧均 +16（对称）。⇒ 内核 countSocketedGems 的计数源含**额外来源**
  （且对两侧不对称），而非装配缺宝石。countSocketedGems 两侧实现逐字相同
  （Inventory.gd:1053-1057 / CoreGrid.gd:166-170，遍历 items 的 getGemsNoNull）。
- 待查：内核 getGemsNoNull 的 sockets 源（CoreItem sockets 数组在装配期的
  填充是否把 bagCells/affected 上的其它物误挂成宝石）、以及神谕 +16 的真实
  构成（16 = 13 快照 + 3 快照外宝石？——第 5 轮宝石快照已实证 getGems 全量
  导出，需用 ANIM 式标记在 onCombatStart 处直接打印 inventory.countSocketedGems()
  的实时值与逐 item 明细）。

### 本轮状态声明

调查轮，无落码；全量验证沿用当前代码态的第 5 轮末结果（3/914，
gd_core-kernel 51）。红线：全程无头后台；未执行任何 git 写操作；未触碰
Steam 版游戏目录；语料冻结保持。


---

## 2026-10-08 · 阶段1 第 12 轮：Shaman Mask 幸运差收窄到 buffPower 组成（对手侧）

### 实证（GEMS 标记双侧落地，run570 复跑）

- `inventory.countSocketedGems()` **两侧同为 13**（逐物品明细标记 GEMS 落盘，
  player/opponent 各一次）——第 11 轮的「内核计数源额外来源」假设排除；
- 幸运事件量 = 13 + **Lucky 的 buffPower 加成**：神谕两侧 16（+3 加成）、
  内核玩家 16（+3 ✓）、内核对手 **14（+1 ✗）**——真分歧 = **对手侧 Lucky
  buffPower 组成**（oracle +3 vs kernel +1）；
- 加成来源 = 符文/宝石的 giveBuffPower 族（Badger/Hawk/Elephant/Tiger Rune 等，
  changeBuffPower_allItems → giveBuffPower，Inventory.gd:1059-1062 同款），
  下轮在对手 onCombatStart 窗口对位 buffPower 明细（哪颗符文/宝石的加成丢失）。

### 本轮状态声明

调查轮（收窄一层），无核心落码（双侧 ShamanMask 加 GEMS 诊断标记，非行为改动）；
全量验证沿用当前代码态的第 5 轮末结果（3/914，gd_core-kernel 51）。语料 events
按惯例备份/恢复。红线：全程无头后台；未执行任何 git 写操作；未触碰 Steam 版
游戏目录。


---

## 2026-10-08 · 阶段1 第 13 轮：Lucky 16/14 定位到 buffPowers[Lucky] 放大层（调查轮）

### 实证

- ShamanMask.onCombatStart 的 `inventory.countSocketedGems()` 双侧同值 **13**
  （GEMS 标记逐物品明细落盘）；
- 幸运事件量 = `giveStacks` 的 `round(amount × buffPowers[type])`
  （Item.gd:4938-4941，buffPowers 为**给予者物品**自身字典，初始 1.0，
  Item.gd:585/:3441；giveBuffPower 累加，Item.gd:4867）；
  - 神谕 16 = round(13 × ≈1.23)；内核对手 14 = round(13 × ≈1.08)；
    内核玩家 16 ✓——玩家侧放大两侧一致、对手侧不一致；
- 已知 giveBuffPower 调用点 10 处（DeathScythe/WarScythe=Poison、
  FullBodyProtection/Halberd/HeartShield/SteelDragon/Whetstone3/MoonShield/
  ShieldofValor=Block、VampiricScythe=Vampirism）——**无一授予 Lucky**；
  隐藏授予者待查（下一轮给双侧 giveBuffPower 加 BUFFPOWER 标记：授予者、
  类型、幂次、目标，重跑 run570 即可锁定谁给 Shaman Mask 挂了 Lucky 幂次、
  以及对手侧少挂的那份）。

### 本轮状态声明

调查轮（收窄到 buffPowers[Lucky] 放大差），无落码；全量验证沿用当前代码态的
第 5 轮末结果（3/914，gd_core-kernel 51）。语料 events 按惯例备份/恢复
（output/_r5_bak_events.json）。红线：全程无头后台；未执行任何 git 写操作；
未触碰 Steam 版游戏目录。


---

## 2026-10-08 · 阶段1 第 14 轮：Lucky 增量 flip 序列逐位相同——放大幅度差锁定

### 决定性实证（run570 对手 Shaman Mask Lucky 段）

13 次 `Util.flipPercent(-totalResistChance)` 的 roll 值**双侧逐位相同**
（51.755123/35.62748/83.873024/89.066154/11.948948/68.306335/42.818821/
61.773712/94.513237/38.024845/28.592756/58.176994/75.80658）：
- 神谕 **3 次成功**（阈值 ≈-40%，即 38.02<阈值≤42.82）→ 13+3=**16**；
- 内核 **1 次成功**（阈值 ≈-30%，28.59<阈值≤35.63）→ 13+1=**14**；
- ⇒ 链位已完全对齐，剩余差异 = **增益（负 resist）放大幅度**：
  `changeAmplificiationChancePercent_allBuffs(getChance())`
  （extracted_running/decomp/Items/Exclusive/TigerRune.gd:19-22 prepareInventory，
  对 getItemsAndGems 逐件叠加）——对手侧仅 1 颗 Tiger Rune(7,1)，
  幅度 40 vs 30 的来源待查：Tiger Rune 的 getChance/getGemPower 链
  （宝石幂次随宿主缩放）或另一路放大量未在内核还原。
- BFP 标记双侧 12 条全 Block(100)——buffPowers[Lucky] 不经 giveBuffPower，
  幸运增量全部走 gainTemporary 负 resist flip 路径（机制确认）。

### 下轮主攻

1. 读 TigerRune 的 getChance()/getGemPower() 链（Gem.gd 幂次随宿主物品稀有度/
   插座位的缩放规则），内核 Gem 门面（gd_core_test GemFacade 闸覆盖过四模式
   公式）对表；
2. 全库扫 changeAmplificiationChancePercent 的其它授予者（多源叠加核对）；
3. 修复后 run570 单场复验（预期 Lucky 16 对齐、首分歧点继续后移）。

### 本轮状态声明

调查轮（阈值差实证），无行为落码（双侧 giveBuffPower 加 BFP 诊断标记）；
全量验证沿用当前代码态的第 5 轮末结果（3/914，gd_core-kernel 51）。语料
events 按惯例备份/恢复。红线：全程无头后台；未执行任何 git 写操作；未触碰
Steam 版游戏目录。


---

## 2026-10-08 · 阶段1 第 15 轮：flip 阈值构成拆解——Evil Cap nullify=15 实证 + 放大率反推

### 实证

- 幸运 flip 的负 resist 来源锁定：**玩家侧 Evil Cap** 的
  `opponent().changeBuffNullifyChances(getChance())`
  （oracle/Items/EvilCap.gd:17-21 onCombatStart，nullifyApplied 一次性闸）——
  Evil Cap 在两侧阵容、两侧激活事件均在（idx 6/7）；
- **数据缺口（新）**：battle_items.json 的 Evil Cap params=[25,5,30,…] 无 chance 位
  （params[7]=0），CSV 的 chance 列值 **15**（csv_chance='15'）未映射进参数表
  ⇒ 内核 getChance() 恒 0、nullify 未生效——但内核对手 Lucky 仍有 +1 增量
  （13→14），说明 +1 来自**另一路负 resist**（非 Evil Cap）；
- 反推（flip 成功数 → 阈值区间 → totalResist = 15−放大）：
  神谕 Shaman Mask 的 Lucky 放大率 ≈53-58%（3 成功），内核 ≈44-51%（1 成功）
  ——放大率本身两侧不同，其授予者（Tiger Rune getChance=0 已排除；其余
  allBuffs 授予者按阵容清单排查）与 Evil Cap nullify=15 的叠加序，需
  changeAmplificiationChancePercent + resistChancePercent 双点插桩核验。

### 下轮主攻

1. 双侧 changeAmplificiationChancePercent(buff, chance) 加 AMP 标记（授予者/
   类型/值），run570 复跑对位 Shaman Mask 的 Lucky 放大率构成；
2. Evil Cap 的 csv_chance=15 补进 battle_items 参数表（数据层修复，独立可验）；
3. 修复后 run570 复验（预期对手 Lucky +16 对齐）。

### 本轮状态声明

调查轮（阈值构成拆解），无行为落码；全量验证沿用当前代码态的第 5 轮末结果
（3/914，gd_core-kernel 51）。语料 events 按惯例备份/恢复。红线：全程无头
后台；未执行任何 git 写操作；未触碰 Steam 版游戏目录。

---

## 2026-10-09 · 闲时阶段1 第 1 轮：randomUniquePool 数据面修复（isTreasure 全量失效根因）

### 根因（run634_r18 决定性实证 + 全库源码链）

**缺口 ⑯：`randomUniquePool`（isTreasure 唯一依据）从未进数据管道。**

- 原版链：ItemBook.gd:899-901 `shop=="unique"` → `item.randomUniquePool = true`；
  Item.gd:5723-5724 `isTreasure() → return descriptor.randomUniquePool`；
  CoreItemData.gd:316 一直读 `descr.randomUniquePool`——但
  battle_items.json/gd_core_runtime.json/item_battle_fixture.json 均无此键
  ⇒ 内核 isTreasure() 恒 false、treasure 计数恒 0。
- 实证（oracle 诊断标记 [FEDORA]，探针复跑 events.json 与冻结语料逐字节一致）：
  run634_r18 玩家/对手 Fedora 均为 `nature=1 treasure=2`（Stone×1 +
  Cog Badge(8,4)/Leaf Badge(7,5)×2，两件 badge 均 shop=="unique"）→
  幸运 = 1×luck(1) + 2×luck2(3) = **7**；内核 treasure=0 → 幸运 **1**。
- 数据源：decompiled_full/Sheets/CSV/ItemData_e.csv（已解密明文）`shop` 列，
  shop=="unique" 共 35 件。

### 修复落码

1. **tools/enrich_unique_pool.py（新）**：读明文 CSV shop 列，把 35 件
   `random_unique_pool: true` 写进 battle_items.json（幂等、只增）。
2. **tools/gen_lineup_fixture.py**（descr builder，gen_gd_core_data 共用）：
   发射 `"randomUniquePool"` 字段（注释附 Item.gd:5723-5724 依据）。
3. **simulator/gd_core_engine.py `_descriptor`**：fromDict 手抄字段清单补
   `randomUniquePool`（此前漏抄——runtime 有值但进不了 CoreItemData）。
4. **gd_core_test/OracleAlignBattle.gd `descriptor_of`**：同补
   （Godot 侧 replay 的描述符表）。
5. 重生成：gen_gd_core_data.py（runtime 35 件 true）+ gen_lineup_fixture.py
   （item_battle_fixture 35 件 true）。py 孪生 CoreItemData.py:330 原生读此键，无需改。

### 验证

- run634_r18 定向 `--force`：**首分歧 idx 0 → 17**（事件 0..16 全对齐，
  含 Fedora Lucky 7 双侧一致、Rainbow Orb +8 一致）。
- 新首分歧 = idx 17 Dragon Knight Heat：神谕 5 vs 内核 7（见下轮入口）。

### 仪器（本轮沉淀）

1. **oracle/oracle_fight.gd `ORACLE_FIGHTS_ROOT`**：诊断复跑输出重定向开关
   （探针写 output/oracle/probe/<tag>/，冻结语料零接触）；探针 events.json
   与语料逐字节一致=确定性自证（run1195_r17、run634_r18 双验证）。
2. **oracle Fedora.gd [FEDORA] 标记**（不消耗链）：nature/treasure 计数+清单。
3. **gd_core/CoreItem.gd AMP 标记**（不消耗链，对位 BFP）：放大授予面追踪。
4. **tools/alignment_digest.py / tools/aligned_set.py /
   verify_oracle.py --cases/--force**（本会话工具升级，见 git 工作树）。
5. 注意：Godot `--quiet` 会吞 stdout——诊断复跑需去 --quiet（仍 headless+Dummy）。
6. gd_core/ 与 gd_core_test/gd_core/ 为**硬链接**（同 inode），内核改一处双侧生效。

### 红线自查

全程无头后台（--headless --audio-driver Dummy，无窗无声）；神谕语料冻结
（探针写 probe/ 目录，run634/run1195 复跑产物与语料逐字节一致后即弃）；
未执行任何 git 写操作；未触碰 Steam 版游戏目录。

### 残留清单（下轮入口）

1. **【首要】宝石实例化与宿主构造的微观次序差**（run634 首个逐抽值分歧
   draw112：神谕=物品 ctor 0.2 对，内核=宝石 ready randf_range(0,10)——
   Djinn Lamp 段，宝石 ready 比宿主 ctor 早/晚一拍）。诊断路径：
   oracle/oracle_stage_probe.gd（装配逐段链态 dump，第 2 轮仪器）+ 内核
   _build_side 的 gem setGem 时序（simulator/gd_core_engine.py:847-853）对表。
   修复后 run634 的 DK Heat 链位差应连带消失（两侧阈值同 15，纯链位差）。
2. **gainedStacks/usedStacks 描述符字段全缺**：gainsBuffs() =
   gainedStacks & Stack.Buff，runtime 无此键 → 恒 false（Bag.canApplyEffect
   等判定面）。数据源=ItemDescriptor 静态分析（gained/used/inflicts 族），
   独立数据缺口，与 1 分开修。
3. DK Heat 数值差（run634 idx 17）：两侧同 5 次 flipPercent(15)、神谕全败
   （17.8/75.9/56.1/91.4/54.5）内核 2 中（54.5/48.6/0.035/4.886/78.2）——
   纯链位差（roll 值错位），1 修复后连带验证。
4. F2 待办不变：Evil Cap csv_chance=15（params[7]=0）、hasBattleRageEffect 描述符。

---

## 2026-10-09 · 闲时阶段1 第 2 轮：宝石三层场景绑定 + playCombatAni 闸 + 战怒描述符（三修复连锁）

### 缺口 ⑰：三层场景链的 chanceRng 绑定次数（下轮入口 1 的破译）

**oracle [ASM] 逐实例标记**（oracle/Core/Inventory.gd createFromItemTuples 插桩，
print 带 oracleRngLog.size()=抽位号，探针复跑 events.json 与语料逐字节一致）：
- draw 108-121 归属：Evil Cap ctor(108,109) → Wisp gem ctor(**110,111,112**) →
  gem-set 后 gem._ready 0-10(113)。**gem ctor = 3 行**。
- 场景链解密：Gem.tscn instances **Item.tscn**（Gem.gd extends Item）→
  Wisp.tscn 再 instances Gem.tscn（Wisp.gd extends Gem）——**三层绑定**=
  Item.gd:472 `var chanceRng = BalancedRng.new()` 跑 **3 次**；
  内核 setup() 固定 2 次 ⇒ 自 draw112 起全链错位（此前 15 轮全部错在此层）。
- 全库扫描（tools/enrich_scene_depth.py，tscn instance 链递归）：
  **34 件 depth=3**——五阶宝石（Chipped/Flawed/Regular/Flawless/Perfect ×
  Ruby/Sapphire/Emerald/Topaz/Amethyst）+ Lump of Coal/Burning Coal/
  Corrupted Crystal/Skull + 四符文（Badger/Elephant/Hawk/Tiger）+ Wisp。

**修复落码**：battle_items `scene_depth`（enrich_scene_depth.py）→
gen_lineup_fixture `sceneDepth` → CoreItemData.gd/.py `sceneDepth` →
**CoreItem.gd/.py setup()**：双重 chanceRng 改 `for _i in range(max(2, sceneDepth))`
循环（damageRangeRng 同随，BalancedRange 构造 0 抽）。

### 缺口 ⑱：activate 的 playCombatAni 闸（4 抽动画块多播）

sceneDepth 修复后逐抽对照推进到 draw296：内核在 Falcon Blade 首次激活
（onCombatStart 的 `activate(null, false)`）多播 4 抽动画块
（-30,30/-100,100/-5,5/0.8,1.2 = ItemAnimation.intialize）。原版
Item.gd:4728-4734 `if playCombatAni: playAnimation()`——**onCombatStart 路径
不播攻击动画**；内核 activate 无视该参。intialize(hit) 的 hit 只切动画名不改抽数
（ItemAnimation.gd:30-34）。修复：gd_core/CoreItem.gd + CoreItem.py 的
animationScene 4 抽块套 `if playCombatAni and descriptor.animationScene:`。

### 缺口 ⑲：hasBattleRageEffect 数据面（F2 后半）

- 描述文本在**翻译资源**（ItemDescriptor.getDescription = tra(key+"_DESCR")），
  ItemData_e.csv 无该文本；oracle/oracle_fight 宿主跑系统 locale（zh_Hans_CN）。
- **oracle/rage_dump_tmp.gd**（一次性仪器）：ResourceLoader 直读
  ExclusiveItems.zh_Hans_CN.translation，扫 518 键的 _DESCR →
  **16 件含 "$rage["**（Wolf Badge/Berserker Bag/Toolbox/Spiked Collar/
  Double Axe/Chain Whip/Dragonscale Armor/Dragon Claws/Dragonskin Boots/
  Busted Blade/Spiked Staff/Deer Totem/Brass Knuckles/Badger Rune/
  Extra Angy/Dragon Set）。
- 落数据管道（同 ⑯ 模式）：battle_items `has_battle_rage_effect` →
  descr.hasBattleRageEffect → 引擎/OracleAlignBattle 双 descriptor 补发射。
  isBattleRageItem 判定面（Character.prepare 的 autoRageItem 候选池）就此打通。
- **缺口注记**：Evil Cap 的 csv_chance=15 **已在数据里**（runtime chance=15.0，
  第 15 轮"未映射"结论过时——此后某次数据重生成已带上）；getChance 链
  （CoreItem.gd:1068 → applyBonusChance → descriptor.chance）核对无损。

### 工具/环境修复（回归链路三处历史断链）

1. **tools/survey_gd_syntax.py CLAIMS**：.new( 57→56、.size() 68→71、
   .push_back 67→70（sceneDepth 循环/playCombatAni 闸注释的计数漂移）。
2. **tools/audit_gd_core.py**：exposed 集合补 `var` 成员——ctx.rng.oracle_trace
   等 var 旗标此前被误报"未定义"（BFP 标记时代即潜伏）。
3. **gd_core_test/Smoke.gd _tick**：`c.physicsTick` → `c.tickPhysicsTimers`
   （内核压缩重构改名后 smoke 未跟；7 项 smoke 失败全是该断链的级联，
   修复后 SMOKE 全 PASS）。注意 [8/17] LINEUP 闸门失败为 **HEAD 既有**
   （LineupFixture 仅 2 套真值阵容且全部在 SKIPPED 里，56 局时代的 8 套阵容
   已不在夹具）——与本轮无关，待后续补阵容夹具。

### 验证

- 定向 5 场 `--cases run634_r18,run798_r18,run1195_r17,run1405_r17,run570_r18 --force`：
  3 锚场保持三方一致；**run570 首分歧 idx 18 → 33**（突破第 7-15 轮 9 轮卡点——
  Shaman Mask Lucky 墙翻过；新分歧 = Steel Dragon DealDamage t=75 vs 76，
  1-tick 族）；**run634 idx 17 → 25**（DK Heat 过，新分歧 = Twine TMH(19) 结构差 vs
  内核 Amulet of Darkness 攻击——事件结构错位，待下轮拆）。
- run_gd_core 阶段 0-7 全 PASS（GEN/SURVEY/audit/依赖环/解析/SMOKE/GRID/FACADE）。

### 红线自查

全程无头后台；语料冻结（探针 f1b/f1c 复跑均字节自证后弃用）；未执行任何
git 写操作；未触碰 Steam 版游戏目录。

### 补记：round2 全量里程碑结果（22:55）

`python -X utf8 tools/verify_oracle.py --force`（914 场全重模拟）：
- 三方一致 3/914（3 锚场保持，无退步）；**gd_core-kernel 族 43 → 21**（砍半
  ——round1-2 三修复把 22 场从纯行为分歧降级为链位/结构差）；
  rng-mechanism 859 → 889（相应重分类）；
- 快照 round2.txt、digest 已更新。定向深挖锚场：run570 idx 33（1-tick）、
  run634 idx 25（Twine 3/4 触发，初步排查：4 份 Twine 的 primary 注册表
  py 侧 dump 均含 Dragon Knight、EventBus.connectEvent 无去重——3/4 缺一次
  onPrepare 连接或首触发 roll 失败路径差，待逐 Twine 打 [TWINE] 标记核对）。

### 残留清单（下轮入口）

1. **run634 idx 25**：Twine TemporaryMaxHealth(19)（parent=18，depth=1）vs 内核
   同位 Amulet of Darkness DealDamage——事件结构错位；先看 idx 18-24 两侧事件
   序列（Twine = Dragon Knight 系合成物，可能又是合成/affected 面）。
2. **run570 idx 33**：Steel Dragon DealDamage 同参数差 1 tick（t=75 vs 76）——
   F7 1-tick 冷却漂移族（Amulet of Agility 加速系）。
3. gainedStacks/usedStacks 描述符字段全缺（上轮遗留，gainsBuffs 恒 false）。
4. LINEUP 闸门需补 ≥8 套阵容夹具（从 history.db 重建，独立任务）。
5. py 转写层 run837/845 IndexError、run986 缺产物（F6，未动）。

---

## 2026-10-10 · 闲时阶段1 第 3 轮：classes 配方类继承 + gate 覆写（isNeutral 全量校正）

### 缺口 ⑳：classes 缺 ItemDescriptor.calcClassAvailability 两遍后处理

- **run634 idx25（Twine 族）**：神谕 4 份 Twine 各触发一次 TMH+2，内核仅 3 份。
  [TWINE] 标记（oracle/gd/py 三侧 onTriggerItemActivated 插桩，print 带实例
  位置+totalChance+roll 结果，探针复跑 events.json 与语料逐字节一致）实证：
  totalChance 神谕 80/60（sec=3/2）vs 内核 40（sec=1）——差在
  getNumAffectedItems(Affected.Secondary) 的 isNeutral() 判定。
- oracle 加名单标记直读真值：Twine@(5,2) secondary = **[Evil Cap(cls=127),
  Lucky Cat(127), Evil Cap(127)]**——Evil Cap 中性！解析期插桩
  （oracle/Sheets/ItemBook.gd [CLASSES]，parse 末尾打 shop+classes）证明：
  **解析期 Evil Cap classes=0**（shop="no"→None，ItemBook.gd:896-897），
  **战斗期=127**——中间有且仅有一个改写者：
  **ItemDescriptor.calcClassAvailability（ItemDescriptor.gd:175-198）**：
  Evil Cap 是 Leather Helm 配方 `Corrupted Crystal>Evil Cap` 的**合成产物**
  （CSV recipes 列），originatingRecipes 非空 →
  `recipeClasses = Neutral(127) 逐成分 &= classes; classes |= recipeClasses`
  → 0|127 = 127。成分 Corrupted Crystal（shop=""→127）与基件 Leather Helm
  （127）皆中性 ⇒ recipeClasses 恒 127 ⇒ **任何合成产物 classes 至少吃满
  Neutral 位**。
- 另一半：`gateItem` 分支（classes==None 且有 gateItem → 取 gate 的 classes；
  95 件，Amulet 系 ← Amulet Unidentified）与 class_override 列（7 件）同属
  该两遍解析，内核数据原样缺。

**修复落码**：tools/enrich_classes.py 扩展 `apply_recipe_inheritance()`——
配方继承 + gate 覆写的不动点迭代（合成深度序的等价），**229 件 classes 变更**
（Evil Cap 0→127、Dragon Knight 0→32? 核对：DK shop="no"→0，
其合成物链否——实际 32 来自其它配方分支）。重生成 runtime+夹具。
同轮修正：enrich_classes 主流程 changed 计数漏配方遍变更（首跑未落盘）。

### 验证

- 定向 5 场：3 锚场保持三方一致；**run634 idx 25 → 76**（Twine 4/4 触发对齐；
  新分歧 = idx76 对手 Dragon Knight DealDamage t=28 vs 29——1-tick 族）。
- 扩样本 12 场（Chess Board/Holdall/Rapier 簇代表+锚场）：无退步；
  run570 idx33（Steel Dragon t=75 vs 76，同为 1-tick）。
- 全量里程碑（--force 914 场）：**三方一致 3/914 持平**；localization
  rng-mechanism 889→888、gd_core-kernel 21→22（分类洗牌：1 场从 kernel 族
  移入 rng 族口径——aligned 无退步，快照 round3.txt 无减少）。

### 环境注记

- GDScript print 不支持 %r（Python-ism）——ItemBook 插桩首跑因 %r 解析崩
  （"unsupported format character"），改 str() 后正常。教训入档。
- 本轮临时标记（TWINE 三侧）已全部还原；[CLASSES]（ItemBook 解析期 2 行）
  与 [FEDORA]/[ASM]/AMP/BFP/ANIM 一样留作常驻仪器。

### 红线自查

全程无头后台；语料冻结（t3/t3b/t3c/t3d 探针复跑均字节自证）；未执行任何
git 写操作；未触碰 Steam 版游戏目录。

### 残留清单（下轮入口）

1. **F7 1-tick 族成主导**：run634 idx76（对手 Dragon Knight t=28 vs 29）、
   run570 idx33（Steel Dragon t=75 vs 76）——同签名：对手侧龙系宠物、伤害参数
   全同、事件时刻差 1 tick。冷却推进逐行已同（triggerTime -= delta×getSpeed，
   Item.gd:4455）；嫌疑= speedScale 累加次序的浮点非结合（Amulet addSpeed 的
   registry 遍历序 vs 神谕 Dictionary 序）或 heat/cold 栈的 tick 内对位。
   打法：ORACLE_ALIGN_TRACE 的 tick_states.txt（内核）+ oracle ORACLE_DEBUG
   tick_states 对位 Steel Dragon 的 triggerTime 逐 tick 曲线，找分叉 tick。
2. Chess Board×58（Activation 首分歧）、Holdall×28（Block 24/16）、
   Rapier×27——扩样本实测其 idx 仍早（4-37），族根因未动。
3. gainedStacks/usedStacks 数据面（oracle 解析链已实证：ItemBook.gd:885-887
   `table.getFlags("gain"/"remove"/"use")`——CSV gain 列直读，数据管道可照抄
   enrich_classes 模式）。
4. F6 py 转写层（run837/845/986）、LINEUP 夹具补齐——不变。

---

## 2026-10-10 · 闲时阶段1 第 4 轮：F7 1-tick 族定位（rng 链完美，分歧在冷却赋值）

### 仪器（本轮新落）

1. **双侧 tick_states 偏移校正**：内核 tick_states 含 2.5s 倒计时 150 tick
   （state 恒定段），oracle 列表从首个战斗 tick 起——对位偏移 = **151**。
   校正后 run570 全场 **648 个战斗 tick 的 PCG 链状态逐位相同**——rng 链完美。
2. **item_trace 曲线仪**（ORACLE_TRACE_ITEM=<物品名>）：oracle_fight.gd +
   OracleAlignBattle.gd 逐 tick dump 目标物品
   `triggerTime/getSpeed/iterationCooldown/isCooldownActive`（harness 侧，
   零 rng 消耗；f7e 起 5 字段）。注意 GDScript 无 %r；File.READ_WRITE 不建文件
   （首写须 WRITE）；ticks 已自增（判首 tick 用 ==1）。

### 实证链（run570_r18，Steel Dragon 双龙曲线）

- 速度阶梯（1.62→1.65→…→1.91，heat/cold 栈）、冻结段（眩晕）、触发点两侧全同；
- **首个分歧 = 战斗 tick 2 的对手龙初始冷却**：
  内核 (triggerTime 2.055267702, iterationCooldown 2.082267702)，
  玩家龙两侧全同 (2.021370731, 2.048370731 = 2.1×jitter 0.975415)；
- 内核对手龙初始 = 2.1×0.991556（另一抽）；神谕对手龙真值待取（本轮探针把
  玩家龙打了两遍——G.OPPONENT.INVENTORY.getItems() 的返回需核，疑探针缺陷
  而非神谕行为）；
- trigger() 两侧逐行同（iterationCooldown = adjustCooldown(); triggerTime += iterationCooldown，
  Item.gd:4426-4431）；updateBaseCooldown（进度保持重抽）两侧在位；
  addSpeed/reduceSpeed 两侧同（不重抽）。

### 下一步（下一窗口第一件事）

1. 修 oracle item_trace 探针：按 _it.ownerType 或 inventory 身份标注行来源，
   取对手龙 tick 2 的 (triggerTime, iterationCooldown) 真值；
2. 若神谕对手龙初始 ≠ 2.082267702：对位 preCombatStart 的 adjustCooldown
   链位（对手物品激活序 vs 内核 activateItems 顺序——ordered_items 顺序 vs
   神谕 activateItems 的 items 数组序）；
3. 若相同：分歧后移到首触发（tick 77 对手龙 post-trigger 2.116834484 vs
   2.188030539，Δ=−0.071196055 = 一次 jitter 差 0.0339/2.1）。
4. F7 修复预期收益：run570 idx33、run634 idx76 及同签名族。

### 红线自查

全程无头后台；语料冻结（f7/f7b/f7c/f7d/f7e 探针均字节自证或未触语料）；
未执行 git 写操作；未触碰 Steam 目录。

### 补记（round4 收尾前的决定性推进）

侧标注探针（oracle item_trace 加 P/O 前缀）推翻"初始冷却互换"假说：
- **两侧按侧完全一致**：P 龙 = (2.055267702, iterCo 2.082267702) 双侧同；
  O 龙 = (2.021370731, 2.048370731) 双侧同。玩家/对手分支、jitter 赋值全对！
- **真正的分歧层 = 事件时间戳的 combatTime 计数**：事件 t=75 vs 76（同一次
  触发、同一 triggerTime 曲线、同一 post-trigger 值 2.188030539/iterCo
  2.191659808 双侧一致）——**canonical t 的 combatTime 累积在两侧差 1 tick**。
- 新疑点（下轮第一优先）：双侧 tick_states 列表的时间结构不同——
  oracle 列表 648 项、首变在 idx 75（=Util.time 20.583+75/60 处有抽签，
  即战斗循环开始后 ~1.25s——倒计时中段就有消耗！）；kernel 列表 799 项、
  首 150 项恒定（倒计时无消耗）。**oracle 的倒计时/循环起点与 kernel 错位**：
  oracle 的 jitter 批次 @t=20.583（=列表起点=装配末），即 preCombatStart 在
  循环极早期就跑了——**oracle 的 callDelayed(2.5s) 在阻塞循环下的兑现时刻
  与 kernel 的 _activate_countdown 不对齐**（callDelayed 走 Util.time——
  装配期 Util.time 已被推进过多少？kernel 用独立 countdown 从 startBattle 起
  算）。这是 F7 的真根因方向：**激活时刻的 tick 对位差** → 事件 t 差 1。
- 修复方向：对齐「activateItems 兑现的 tick」——核对 oracle Util.callDelayed
  的计时起点（创建于 finishSwitchingToCombat，Util.time 当时值）vs kernel
  _activate_countdown 起点（startBattle）。kernel 或需把 countdown 初值改成
  与 oracle 的 Util.time 差值等价（COMBAT_DELAY=2.5 的语义锚点）。

### 红线自查

全程无头后台；语料冻结（f7/f7b/f7c/f7d/f7e/f7f 探针均自证或未触语料）；
未执行 git 写操作；未触碰 Steam 目录。

### 补记 2（round4 真根因一锤定音）

**idx33 原始时间戳**：oracle raw t = **1.25**（=75×1/60）vs kernel = **1.266667**
（=76×1/60）——整 tick 差，非舍入边界。两侧 idx32（combatStart 激活事件）t=0 同。

**combatTime 曲线**（item_trace 第 7 字段）：oracle ct 首增于战斗 tick 2
（tick 1=激活 tick，CT.start() 在 ⑧ 于 ④ 之后启用 ⇒ 激活 tick 不计数）；
kernel ct 首增于 list 153（内容 tick 2）——**但 kernel 的内容 tick 1（list 152）
物品仍未激活**（speed 1.30、active=0、triggerTime 0——Amulet 的 onCombatStart
addSpeed 未生效），即 **kernel 的 activateItems（list 151 step 0 早退路径）之后
物品态晚一拍才就位**。事件 t 差 1 = 这一对位差的下游表现。

**修复方向（下轮第一优先）**：对齐「激活 tick 的内容执行」——oracle 的激活
tick（循环 tick 1）跑了 ①-⑦（前置空转）+ ⑧ activateItems（CT.start 在 ⑧，
故该 tick 的 CT ④ 不计数）；kernel 的 step 0 早退跳过 ①-⑦ 且其 activateItems
时序使物品态延一拍。需按 oracle 语义重排 kernel 的激活 tick：countdown 到期
tick 应继续跑 ①-⑦（激活前空转）并在 tick 尾（⑧ 位）兑现 activateItems，
CT/combat_time 计数从下一 tick 起。修后 run570 idx33 / run634 idx76 预期消失。

### 红线自查（round4 全轮）

全程无头后台；语料冻结（f7~f7g 探针均字节自证或未触语料）；未执行 git 写
操作；未触碰 Steam 目录。

---

## 2026-10-10 · 闲时阶段1 第 5 轮：F7 修复尝试（step-0 重排）未生效，已回滚；决定性数据全落盘

### 候选修（已回滚）

gd_core/CoreCombat.gd + CoreCombat.py step 0 重排（countdown 到期 tick 照跑
①-⑦ + tick 尾兑现 activateItems + combat_time 激活 tick 跳计）。定向验
run570/run634/3 锚场：**idx 33/76 纹丝不动、3 锚场无退步**——该重排与事件
时间戳无关，已按协议回滚（备份在 output/_round_patches/round5/）。

### round5 决定性数据（全部在盘，供下一窗口直接续）

1. ** DealDamage 创建时刻打点**（gd_core/CoreCombatLog.gd [DD] print，常驻）：
   内核对手龙首次 DealDamage 创建于 **ct=1.266667（76/60）**；神谕事件 raw
   t = **1.25（75/60）**——同一内容节拍，combat_time 计数差恰一拍 ④。
2. ** combatTime 曲线**（item_trace 第 7 字段，双侧）：oracle ct@内容N = N/60、
   kernel ct@内容N = (N−1)/60——**kernel 的 ct 在同内容节拍恒少一拍**，
   但事件却多一拍 ⇒ 事件的创建 tick 两侧不同（神谕 content 75、内核 content 76）
   ——冷却轨迹对齐而事件错位 = **ct 起算点/激活 tick 的结构差**仍在。
3. 中间发现（重要，勿丢）：内核 list 228 的对手龙 iterCo 变化
   （2.048370731→2.191659808=2.1×1.043648）= **速度变化（1.62→1.65，heat 栈）
   触发的 updateBaseCooldown 进度保持重抽**，非攻击触发；攻击在其后一拍。
4. 陷阱记录：origin.identifier 不存在（物品用 descriptor.identifier）——
   [DD] print 首版因此 157 次空错误。

### 下轮入口（修订）

1. F7 修法收敛：**对齐 ct 起算**——oracle 的 combatTime 首增于「激活后的第一
   个 ④」（其激活 tick=循环 tick 1 的 ④ 因 CT 未 start 而跳过）；kernel 当前
   首增于内容 tick 2——两者看似同构但事件差一拍，需逐 tick 台账对齐
   （用 f7g 曲线的 ct 列直接 diff 找首个 ct 分叉 tick，再映射到 step 语义）。
2. 备选：事件时间戳改在 **takeDamage 进入时**捕获（oracle 语义=事件创建于
   ③ 内 pre-④ 时刻）——若 kernel 的 DealDamage 创建确在 ④ 后（[DD] ct 已证），
   则把 combat_time 增量移到 ③⑥ 之后（④ 位次后移）即对齐——**先在 f7g 数据
   上核验 oracle ④ 的确切位置再动手**。
3. 其余族不变：Chess Board×58 / Holdall×28 / Rapier×27；gainedStacks 数据面；
   F6 转写层；LINEUP 夹具。

### 红线自查

全程无头后台；语料冻结；未执行 git 写操作；未触碰 Steam 目录。

---

## 2026-10-10 · 闲时阶段1 第 6 轮：F7 双计修复落地（真根因）+ 新症状记录

### 真根因修复（缺口㉑）：combat_time 双计

**CoreContext.advancePhysicsFrame 内 `combat_time += delta` 与 CoreCombat 步骤④
双计**——事件时间戳（getTimeStamp=_ctx.combat_time，③ 内创建、④ 前读取）恒多
一拍 ④。证据链：run570 idx33 raw t kernel=1.266667(76/60) vs oracle=1.25(75/60)；
item_trace ct 曲线（CoreCombat.combat_time 单速）与 [DD] 创建时刻打点
（ctx.combat_time 双速）之差恰为 ① 的增量。

**修复**：删 advancePhysicsFrame 的 combat_time 增量（gd_core/CoreContext.gd +
gd_core_py/gd_core/CoreContext.py 镜像，py 镜像同步）；唯一写入点=步骤④ 的
`ctx.combat_time = combat_time`。oracle 步骤① 只推进 Util 时钟
（oracle_fight.gd tick_battle ①：clockTime/time/frameCounter），CT.combatTime
仅步骤④（`if CT.is_physics_processing(): CT._physics_process(dt)`）——语义对齐。

### 验证（定向 5 场）

- 3 锚场保持三方一致 ✓ 无退步；
- run634 idx 76 → **27**（时间戳对齐生效，暴露更早分歧：idx27=神谕 Amulet of
  Darkness 对 Twine 激活的反应攻击（rollChance 成功→dealEffectDamage 4），
  内核缺该反应——AoD 的 chanceRng 私有流状态/连接面差，AoD chance=30 数据在位）；
- run570 idx 33 仍在，但**症状变了**：内核的龙攻击 DealDamage 事件从流中消失
  （t≈1.25/1.3 处 kernel 无 type-1，oracle 有 id33/id36）——攻击的后果事件
  （stun 9/mana 105/health 12）在而攻击本体事件缺失 = 事件创建或入档被闸，
  非攻击未发生。下轮首查：takeDamage 尾部 createEvent_Attack 的执行/入档。

### 仪器状态

- [DD] print（CoreCombatLog.createEvent_Attack，常驻，stdout 可见）；
- item_trace 曲线仪 7 字段（双侧）；[ASM]/[FEDORA]/[CLASSES]/AMP/BFP/ANIM 常驻。

### 红线自查

全程无头后台；语料冻结；未执行 git 写操作；未触碰 Steam 目录。

### 补记（round6 收尾终观察）

修复后 run570 内核流：**龙攻击的 DealDamage 事件（t≈1.25/1.3）消失**，首个
type-1 = id63 t=2 origin=None（疑 fatigue/无 origin 路径）；而 rng_trace 的
EVENT 1 标记仍在（首个 draw 3354 ≈ list 229）——**事件在 trace 有、在
events.json 无** = payload dump 与 log 的差异面（或 type 映射/事件体字段），
非攻击未发生。下轮首查：events.json dump 的 type/t 字段来源
（OracleAlignBattle payload 段）与 combat_log.events 的实际内容 diff。

同时：[DD] 打点（创建时刻 ct=1.266667）与 events.json 的 t=1.266667 一致
——创建时刻的 ct 本身已比神谕（1.25）晚一拍 ④，双计修复后仍晚一拍——
**ct 单速化后创建时刻仍偏晚**，指向 ④ 增量相对 ③ 的位置语义仍差一拍
（oracle 的 CT 增量在 ③ 之后 ⑤ 之前——与内核 ④ 同位；但 oracle 的触发
tick 比内核早一内容拍）。保留 item_trace/[DD] 仪，下轮以
「同 ct 值处两侧事件流对齐」为新口径重做对位。

### 补记 2（round6 收尾）：回归状态

- SURVEY 基线更新（String 格式化 % 3→4，[DD] print 合法新增）→ PASS；
- **SMOKE test4 新失败**：「首击时刻应在 cd×[0.95,1.05]（实际 -1）」——
  双计修复后事件 t 语义变更（单速 ct），Smoke.gd test4 的首击时刻推导
  对 ct 语义敏感——**待下轮判定**：读 Smoke.gd test4 的测量式，若是
  harness 算术依赖旧双计语义则修 harness；若是内核首击时刻真回退则回滚
  双计修复。其余阶段（GEN/audit/依赖环/GRID/FACADE）PASS；LINEUP=HEAD 既有。
- 定向 5 场：3 锚场无退步 ✓；run634 idx 76→27（改善）；run570 idx33 症状变化
  （DealDamage 事件缺失，见前节）。

### 补记 3（round6 最终状态）

- SMOKE test4 失败机制：[DD] print 在 smoke 的 TestSword descriptor 上抛错
  （origin.descriptor 链差异）→ createEvent_Attack 中止 → 攻击事件不再入档
  → first_damage_time=-1。**[DD] print 对非神谕 descriptor 不安全**——
  下轮第一件事：给 [DD] print 加 descriptor 判空保护或移除该 print
  （其使命已完成：创建时刻 ct 已取到）。
- 双计修复本身（CoreContext.advancePhysicsFrame 删 combat_time 增量）的
  净效应待分离验证：移除 [DD] print 后重跑定向 5 场 + smoke，分辨
  「双计修复的真效应」与「print 副作用」。
- 当前工作树状态：双计修复在位；[DD] print 在位（有副作用）；step-0 重排
  已回滚；其余=round4 末状态。

---

## 2026-10-10 · 闲时阶段1 第 7 轮（续 round6 收尾）：[DD] print 删除 + 双计修复净效应分离确认

### 处置

- **[DD] print 删除（非判空）**：gd_core/CoreCombatLog.gd 原 64-66 行（`# ★ F7 诊断`
  注释 + `print("[DD] %s ct=%s act=%s frame=%s" ...)`）整块删除，
  `createEvent_Attack` 的 DealDamage 分支恢复纯 `createEvent` + `setParam("damage",...)`
  （现 gd_core/CoreCombatLog.gd:62-63；对齐锚 CombatLog.gd:653-702）。
  判空救不了 Dictionary 型 descriptor 链，使命已完成（round5 取到 ct=1.266667）。
  备份：output/_round_patches/round7/CoreCombatLog.gd。
- 硬链接实证：gd_core/CoreCombatLog.gd 与 gd_core_test/gd_core/CoreCombatLog.gd
  同 inode（844424930778519），一处编辑双侧生效，无需镜像。

### 验证（本轮 run_gd_core 全流水线）

- **SMOKE: PASS（含 test4）**：首击=0.967s ∈ [0.95,1.05]×cd——round6 的
  「SMOKE test4 失败」确证为 [DD] print 副作用（TestSword descriptor 链抛错→
  createEvent_Attack 中止→攻击事件不入档→first_damage_time=-1），非内核回退。
  **双计修复（advancePhysicsFrame 删 combat_time 增量）真效应干净，不回滚**；
  harness（Smoke.gd）无需修改。
- 0-7 闸全过：静态审计 OK / 依赖环 OK / PARSEALL ok / SMOKE PASS /
  GRID PASS / ItemParseAll 503/503 / FACADE PASS。
- [8/17] LINEUP=HEAD 既有（夹具阵容 2<8 等 4 项 + 3 条脚本运行期错误），
  与 handoff 记载一致，本轮未处理。
- 定向 5 场（print 删除后）：3 锚场三方一致 ✓；run570/run634 症状前移
  （见第 8 轮）。

---

## 2026-10-10 · 闲时阶段1 第 8 轮（新会话第 1 轮）：gem origin dump 转录面修复

### 定靶（digest 03:11 版）

- run570_r18 idx34：type=10 stun_resisted，O `[gem,null,-1]`/actor=player vs
  G `[gem,"Steel Dragon",1]`/actor=opponent（行差 `眩晕被抵挡` 主语+括注）。
- run634_r18 首分歧移至 idx98（print 删除+时间戳修复后内核事件流变完整）。

### 真根因：gem origin 序列化面（dump 层，非判定层）

- **原版**：gem.socket 是 GemSocket2 节点（decompiled_full/Items/GemSocket.gd
  =class Socket：**单数** `gem`、无 `gems` 数组、无 descriptor/getTopLeftCell），
  oracle_fight.gd::_jsonable_impl（oracle/oracle_fight.gd:1238-1246）折叠为
  `{kind:"gem", host:{kind:"unknown",str:"GemSocket2"}, socket_index:-1}`。
  **全语料实证：21164/21164 个 gem origin 全为该形状（output/oracle/fights/** 扫描）**。
- **内核**：socket 身份有意折叠进宿主物品（gd_core/CoreItem.gd:2786-2806
  setGem 的 `gem.socket = self`，闸门 10 GemFacade 已验等价）→ dump 把宿主
  item 序列化为 host → verify_oracle._owner_side（tools/verify_oracle.py:402-416）
  对 gem 取 host.owner_type → actor 翻转 + 渲染括注差。
- **actor 翻转是派生效应**：oracle host 不可解析 → 回退 target → player。

### 修复（dump 转录；判定逻辑 canonical/_origin_canon/compare 零改动）

- gd_core_test/OracleAlignBattle.gd `_j` gem 分支（原 112-121 行）：
  恒 emit `{kind:"gem", host:{kind:"unknown",str:"GemSocket2"}, socket_index:-1}`；
- tools/verify_oracle.py `_py_payload` gem 分支（原 312-316 行）：同形状。
  该改动属 py 重放产物的转写段（对应 OracleAlignBattle 的 CaptureProbe），
  **不属于被禁的判定逻辑**；同口径注释已内联。
- 备份：output/_round_patches/round8/{gd_core_test/OracleAlignBattle.gd,
  tools/verify_oracle.py}（round1 目录已被阶段1 第 1 轮占用，本轮顺延 round8）。

### 验证

- **预演**（monkeypatch _origin_canon+_owner_side 只读诊断）：run570
  oracle_vs_gdcore 548/548 全同。
- 定向 5 场 --force：**run570 → `gdcore≡oracle 但 py 分歧`**（oracle_vs_gdcore
  全流一致，预测兑现）；3 锚场三方一致无退步；run634 仍 `oracle≠gdcore`。
- digest（03:21）：aligned 3/5；`gd_core_py-transpiler` 1（run570）；
  `rng-mechanism` 1（run634）。
- 退步检：`python -X utf8 tools/aligned_set.py check -b
  output/oracle/aligned_sets/round3.txt` → 基线 3 场，新增 0 退步 0 ✓。
- 回归：run_gd_core 0-7 全过（见第 7 轮节）；LINEUP=既有。
- 扩样（--limit 20，语料前 20 场 run569-run588）：0/20 三方一致——
  `rng-mechanism` 15（首例 run569_r11）、`gd_core-kernel` 4（首例 run571_r18）、
  `gd_core_py-transpiler` 1（run570）。**非全绿 → 不触发全量里程碑**。
- 收尾复跑 24 场（20 样本 + run634 + 3 锚场）刷新 alignment.json 作本轮终态。

### 下轮入口（round8 补记后修订）

1. **run634 idx98（oracle_vs_gdcore，`rng-mechanism` 标签）**：t=0.800 同拍
   物品传导序/伤害值差。oracle 顺=[DK 攻3→Twine×2→Goobert 治疗18→Goobert
   109×2→Twine→**AoD 攻4**→ManaOrb(resisted)→DK 攻3(heal target=1)→
   Twine×2→Goobert 治疗18→ManaOrb→Twine]；内核顺=[DK 攻3→Twine×2→
   **DK 攻5**(heal target=1, Stone Cold 110 reflect)→Twine×3→...]，
   Goobert/AoD 后移（内核 AoD 下一事件 t=1.183）。指向 **Twine 激活传导面**
   （type19 amount2 = Twine 对连接物品的充能传导）目标序/次数 + DK 伤害 5 vs 3
   （受影响连接面）。内核事件总数 2775 vs 神谕 2568（+207）。
2. **run570 残余（`gd_core_py-transpiler`）**：idx10 Rainbow Orb 魔法 10 vs py 7
   ——gd 与 py 脚本 1:1 已核（gd_core_items/Exclusive/RainbowOrb.gd vs
   gd_core_py/gd_core_items/Exclusive/RainbowOrb.py），差在
   getAffectedItems/countTypes **受影响连接面**或数据读取，不在脚本转写。
3. **扩样新族**：`gd_core-kernel` 4 场（首例 run571_r18）待 digest 逐场定位；
   `rng-mechanism` 15 场（首例 run569_r11）——先看首分歧是否也是 gem/Twine
   面的下游症状，勿直接啃 Util.rng。
4. 既有族不变：Chess Board×58 / Holdall×28 / Rapier×27；gainedStacks 数据面；
   F6 转写层；LINEUP 夹具（[8/17]）。

### 红线自查

全程无头后台（--headless，stdout/stderr 重定向文件）；语料冻结只读；
判定逻辑零改动；未执行 git 写操作；未触碰 Steam 目录。

---

## 2026-10-10 · 闲时阶段1 第 9 轮（新会话第 2 轮）：py 孪生 rng 链对齐——rng_state 注入

### 定靶（digest 03:25/03:54 版）

`[gd_core_py-transpiler]` run570_r18（gdcore≡oracle 但 py 分歧，idx10/11 Rainbow
Orb 魔法 10 vs 7）。修成则 aligned 3→4。

### 根因链（逐抽对位取证，run570_r18）

1. **表象**：双方 Rainbow Orb 的 Mana 事件神谕=10/7、gd=10/7（gdcore≡oracle）、
   py=7/6。
2. **机制**（gd_core/CoreItem.gd:1242-1244 giveStacks → CoreBuff.gd:119-130
   gainTemporary）：`totalResistChance = 0 − item.getAmplificationChancePercent`
   为负时逐栈 flip（randf_range 0~100 ≤ 37.95%）每次成功 `amount += 1`。
   gd 侧 R9 探针实证：双方 orb Magic=3、mana=2.0、**amp=37.95**——
   gd flip 6 抽中 4/1 成功 → 10/7（=神谕）；py flip 1/0 成功 → 7/6。
3. **根因**：py 链位错位。gd+py 逐抽 trace 尾对齐 diff：py 在装配期相对 gd
   **少 3 抽**（gd#5-7 缺失，其后值整体错位）——flip 抽到的值全歪。
4. **结构性差异（三层）**：
   - gd 神谕 harness 在 startBattle 前**注入神谕 rng_state**
     （gd_core_test/OracleAlignBattle.gd:433-446 读 output/oracle/fights/
     <case>/rng_state.txt 的 state= 行 → ctx.set_state），装配期消耗差被抹平；
   - py 引擎留有同语义的 rng_state 参数（simulator/gd_core_engine.py:725-726
     ctx.set_state），但驱动从未传（tools/verify_oracle.py 旧驱动）；
   - py 驱动还传着已废校准常数 **post_seed_draws=14**（引擎注释自证
     「神谕对齐路径恒传 0；旧的校准常数 14（ORACLE_SCENE_DRAWS）已删」，
     simulator/gd_core_engine.py:672-679）——py 链恒多耗 14 位。
   - 附带实证：装配序本就双侧不同（56 局基准 LineupBattle.gd:413-420 =
     [char][char][setup][items]；神谕序 OracleAlignBattle.gd:383-414 =
     [seed][items][char][setup][items]），py 恒用前者。

### 修复（全部非判定逻辑；canonical/_origin_canon/compare 零改动）

1. **tools/verify_oracle.py py 重放驱动**：读 fights/<case>/rng_state.txt 的
   state= 行 → `GDCoreEngine(..., rng_state=...)` 注入（与 gd 同一边界）；
   `post_seed_draws` 14→0；payload 元数据 `post_seed_draws=0` +
   `rng_state_injected` 如实落盘；`_py_payload` 加 rng_state_injected 形参。
2. **gd_core_py/gd_core/CoreItem.py**：3 处 oracle_trace 诊断块的
   `oracle_trace_log.push_back(` → `.append(`（py list 无 push_back；trace
   关闭时不执行故既有闸门未抓到。同族先例=文件内 2113-2115 注释
   2026-10-08 修过）。py 镜像手改，已注明。
3. **simulator/gd_core_engine.py 装配序条件分支**（曾尝试，已回滚）：把
   神谕序 [reseed][p_items][o_char][setup][o_items] 做成
   reseed_after_player_character=True 分支——定向验证发现 8 场 py 重放崩溃
   （`[py][FAIL] 'NoneType' object has no attribute 'INVENTORY'`：py
   _build_side 前置后 item._readyInit 依赖 ctx.combat），且状态注入已抹平
   装配差、重排零收益——**已整块回滚**（备份对比逐字节还原），保留结论
   在案。

### 验证

- 单场 run570_r18 --force：**三方一致 1/1**（aligned 3→4 达成）。
- 24 场全景 --force（03:54 digest）：**aligned 4/24**（run570_r18 新增）；
  `oracle≠gdcore 且 py 分歧` 19→12；**新增 8 场 `oracle≠gdcore`**（py 与 gd
  完全同流——py 面在这 8 场消失，gd/py 合流对神谕）；py 重放 24/24 无崩溃
  （回滚后）。非全绿 → 不触发全量里程碑/快照。
- 退步检：`aligned_set.py check -b round3.txt` → 基线 3 场 + 新增
  run570_r18，退步 0 ✓。
- 闸门 11 直检：`python -X utf8 tools/check_gd_py.py` → 531/531 通过 ✓
  （覆盖手改的 CoreItem.py）。
- gd 核心逐字节还原核验：round9 备份 vs 工作树 diff 全空（CoreRng/CoreItem/
  CoreCharacter/RainbowOrb 四文件 + gd_core_engine.py）——本轮 R9_PROBE
  临时探针（CoreRng._trace 标签行、CoreItem/CoreCharacter 标签、
  RainbowOrb [R9] print）已全部移除。

### 下轮入口（round9 补记后修订）

1. **`rng-mechanism` 16 场（首例 run569_r11）**：py 面已消，剩下的全是
   gd 内核 vs 神谕的真行为差。逐抽/逐事件对位工具已就绪
   （ORACLE_ALIGN_TRACE=1 → gdcore/<case>/rng_trace.txt 逐抽；py 探针 =
   CoreRng.__init__ 补丁开 oracle_trace）。首分歧聚类：Goobert 治疗×3
   （run573/577/586，O 恢复 vs G 死神镰刀伤害）、Toad×2（run575/587，
   O 蟾蜍治疗 7 缺失）、Critical Poison×2（run576/584，中毒 4 vs 2——
   数值面）、Stone×2。
2. **`gd_core-kernel` 4 场（首例 run571_r18）**：stack(106) origin=
   Armored Power Puppy 等。
3. run634 idx98 Twine 传导面（第 8 轮入口 1，未动）：t=0.800 内核 DK 攻 5
   占位 vs 神谕 Goobert 治疗 18 + AoD 攻 4。
4. 既有族不变：Chess Board×58 / Holdall×28 / Rapier×27；gainedStacks 数据面；
   F6 转写层（剩余 12 场 py 分歧多数应为内核同源差）；LINEUP 夹具（[8/17]）。
5. py 驱动现依赖 fights/<case>/rng_state.txt——全量跑前确认全语料该文件
   在场（fights 批量导出已含；缺文件的场走 rng_state=None 回退旧路径）。

### 红线自查

全程无头后台；语料冻结只读；判定逻辑零改动；未执行 git 写操作；未触碰
Steam 目录；gd 核心临时探针全部移除（逐字节核验）。

---

## 2026-10-10 · 闲时阶段1 第 10 轮（新会话第 3 轮）：gainedStacks/usedStacks 数据面补齐

### 定靶（digest 03:54 版）

Toad ×2（run575_r18/run587_r10 首分歧 idx3/t=0）——追入 ask 已知族
「gainedStacks/usedStacks 数据面」的全量缺口。

### 根因（数据面，四点断裂）

1. **runtime/fixture 表全体缺 gainedStacks/removedStacks/usedStacks**
   （gd_core_runtime.json 与 gd_core_test/item_battle_fixture.json 0 处出现；
   battle_items.json 无 gain/remove/use 来源字段）。
   权威语义：decompiled_full/Sheets/ItemBook.gd:877-879
   `gainedStacks = table.getFlags("gain", Item.Stack, line)`（remove/use 同构）；
   Table.gd:38-44 getFlags=按","分裂去空格逐 token 查 Item.Stack 求和；
   Item.gd:96-112 Stack 枚举含聚合键 Buff=254/Debuff=1792/BuffNoLuck=252。
2. 消费面：CoreItem.gd:5383 gainsStack / :5393 gainsBuffs（&Stack.Buff）/
   :5399 inflictsDebuffs——缺省 0 ⇒ Toad/PoisonFrog 等阈值网络
   canAfect=gainsBuffs() or usesBuffs()（Toad.gd/PoisonFrog.gd）恒假 ⇒
   affectedItemsDict 恒空 ⇒ onBuffsChanged 永不命中 ⇒ 治疗整条缺失。
3. 透传链三点断裂：compile_descriptor（tools/gen_lineup_fixture.py:207）
   不产字段；py 引擎 _descriptor（simulator/gd_core_engine.py:754+）不透传；
   gd 神谕 harness descriptor_of（gd_core_test/OracleAlignBattle.gd:168+）
   字段子集不透传。
4. gd_core/CoreItemData.gd:138-140/347-349 与 py 镜像消费端本就齐备（默认 0）。

### 修复

1. **tools/enrich_stack_flags.py（新）**：ItemData_e.csv（解密后明文表，
   518 行）gain/remove/use 列 → Stack 位标志 → battle_items.json 三字段
   （.bak 备份；--check 模式）。表值 token 普查：全部 ∈ Stack 枚举键。
   实跑：覆盖 518/518、变更 438 件。
2. compile_descriptor + py 引擎 _descriptor + gd harness descriptor_of：
   三点各加 gainedStacks/removedStacks/usedStacks 透传（gd 侧 int(d.get(...,0))）。
3. 重生成 assets/gd_core_runtime.json 与 gd_core_test/item_battle_fixture.json
   （Toad gained=34=Mana32+Lucky2、Snake gained=258=Poison256+Lucky2、
   Ace of Spades gained=18=Spikes16+Lucky2——与 CSV 逐项核对）。
4. 备份：output/_round_patches/round10/（round3 已被阶段1占用，顺延编号）。

### 验证

- **Toad 聚类点燃**：run575_r18 gd 侧 Toad 治疗从 0 条 → 4 条，
  量 [7,7,4,4] 与神谕逐条全等；首分歧 idx3 → **idx78**（run587 同理 → idx74）。
- **py 侧先证**：修复后 py 重放 idx3 治疗=7.0 与神谕逐位同（Toad 事件 28=28）。
- 24 场全景（04:13 digest）：aligned **4/24**（3 锚场 + run570 零退步）；
  **首分歧 median 46→53**、p25 31→45、idx≤19 场 3→1、idx≤9 场 2→0——
  分歧面整体后移；Goobert 聚类 ×3→×5（buff 阈值网络的 Goobert 系成员，
  新前沿，同族延续）。
- 退步检：aligned_set.py check -b round3.txt → 基线 3+新增 run570、退步 0 ✓。
- 闸门 11 直检：check_gd_py.py 531/531 ✓。

### 受阻记录（本轮跳过，未造真值）

- **Critical Poison ×2（run576/584 毒量 4 vs 2）**：sheet 与 runtime 同为
  `5:damt 1:poison`，但 run576 神谕两连击（12/11 伤）恰合 damt=5+acc 进位
  下 poison=2；run584 神谕又现奇数量（1/3）证 poison=1、且 idx100 单次攻击
  产出 1+3 两条分裂毒事件（疑多物品/多连接联动+Death Scythe crit 面交缠）。
  证据不足，未动参数，留给下轮逐抽对位。
- **run634 idx98 Twine 传导面**：同上未动（多物品反应网络+滚点）。

### 下轮入口（round10 补记后修订）

1. **Goobert 聚类 ×5（首分歧 origin 榜首）**：run573/577/586（O 黏黏治疗 9
   缺失）、run588（O 光之黏黏治疗 43 缺失）、run575（idx78 O 剧毒黏黏治疗 6
   缺失）——与 Toad 同族概率高：读 decompiled_full/Items/Goobert.gd /
   PoisonGoobert / LightGoobert 的 canAffect/onBuffsChanged 面，核
   gainedStacks 修复后是否已部分点燃，剩余差=连接面或 getP_m 修饰面。
2. **gdcore_vs_py 小数值差**：run587 idx95 战镰暴击 33 vs 34（取整面：
   gd vs py 暴击乘算顺序/round 差）；run575 idx139 剧毒蛇杖毒 1 vs 3
   （Snake gained=258 修复后 py 侧毒叠已动，gd 侧待对表）。
3. **Critical Poison 分裂毒事件**（受阻记录 1）：以 ORACLE_ALIGN_TRACE=1
   逐抽对位 run576 idx41-45。
4. 既有：run634 Twine 传导面；Chess Board×58 / Holdall×28 / Rapier×27；
   F6 转写层剩余 12 场；LINEUP 夹具（[8/17]）。

### 红线自查

全程无头后台；语料冻结只读；判定逻辑零改动；未执行 git 写操作；未触碰
Steam 目录；gd_core/*.gd 本轮零改动（仅需 gate 0-7 复跑确认）。

---

## 2026-10-10 · 闲时阶段1 第 11 轮（新会话第 4 轮）：Goobert 家族受影响格形状修复

### 定靶（digest 04:13 版）

Goobert 聚类 ×5（run573/577/584/586/587，O 治疗缺失）+ Light Goobert ×2 +
Poison Goobert——round10 入口 1。

### 根因（受影响格数据面，家族 5 件）

- 机制链：Goobert.gd（decompiled_full/Items/Goobert.gd）= 连接物品
  `activated` 信号计数，`activations == getP1()`（=5）时 doCooldownEffect→
  heal()+activate()。gd/py 事件流对照：双方 Goobert 治疗同为 12 条且互相
  逐位一致，神谕 18 条且更早——连接集不同（非阈值、非治疗参数：
  p1=5/p2=9:heal 与 ItemData_e.csv 行三方一致）。
- 连通集拟合：神谕 run573 玩家 Goobert(col2,row0) 治疗时刻 3.2167 =
  连接集 {Blueberries(1,0), Fly Agaric(1,1), Shovel(4,0), Death Scythe(4,1)}
  的第 5 次激活；旧数据连接集 {FA, DS} 首治 4.35。
- 数据源：Goobert.tscn 仅覆写 CollisionMap `tile_data`
  （Item.gd:96-112 枚举对应瓦片：3=Collision、4=AffectedPrimary——
  simulator/extract_grid.py 头注 Tiles 表）。battle_items.json 的
  Goobert 家族 grid.affected_cells = [[-2,0],[-1,0],[1,0],[2,0]]（旧解码
  产物：下排横排）——**错**；现行 decode_tile（y<<16 | x&0xFFFF，双 16 位
  有符号）重解 tile_data = affected [[-2,-1],[-2,0],[1,-1],[1,0]]
  （左列×2+右列×2 环包 2×2）——与神谕行为精确吻合。
- 量测（只读全库扫描）：grid 与现行解码不一致的**仅 Goobert 家族 5 件**
  （Goobert/Blood/Steel/Light/Poison Goobert），449 件一致——爆炸半径即
  聚类本身。

### 修复

零代码改动——simulator/extract_grid.py 现行解码本已正确（历史某版修过
解码器但从未重跑提取）：重跑 `python -X utf8 simulator/extract_grid.py`
（重写 battle_items.json grid，454 件有 tscn 数据）→ 重生成
gd_core_runtime.json（gen_gd_core_data.py）+ item_battle_fixture.json
（gen_lineup_fixture.py）。新 affected 落表：rot0
{'0': [[-1,0],[-1,1],[2,0],[2,1]]}——放置 (2,0) 后绝对格 = BB(1,0)/
FA(1,1)/Shovel(4,0)/DS(4,1)。
备份：output/_round_patches/round11/（battle_items/gd_core_runtime/
item_battle_fixture 修复前快照；round4 已被阶段1占用，顺延编号）。

### 验证

- 定向 10 场（Goobert 聚类 + Toad + 锚场）：**三方一致 5/10**。
- 24 场全景（04:24 digest）：aligned **6/24**（新增 run573_r7、run586_r10，
  退步 0）；**首分歧 median 53→80**、max 128→212；oracle≠gdcore 17 场
  （其中 7 场 py 已合流）。非全绿 → 不触发全量里程碑/快照。
- 退步检：aligned_set.py check -b round3.txt → 基线 3 + 新增
  run570/573/586、退步 0 ✓。闸门 11：check_gd_py 531/531 ✓。
- run_gd_core 回归 0-7（gd_core/*.gd 本轮零改动）全过、LINEUP=[8/17] 既有。

### 下轮入口（round11 补记后修订）

1. **run577_r7**（Goobert 家族中仍 oracle≠gdcore 的独苗）：新首分歧待
   digest 定位（04:24 版 origin 首位 Stone×2 与 src:poison×2 更靠前）。
2. **gdcore_vs_py 小数值差**（py 孪生面，2 场残留）：run575（gdcore≡oracle
   但 py 分歧：剧毒蛇杖毒 1 vs 3——Snake gainedStacks 修复后 py 毒叠路径）；
   run587（战镰暴击 33 vs 34 取整面）。
3. **Critical Poison 分裂毒事件**（round10 受阻，run576/584）：
   ORACLE_ALIGN_TRACE=1 逐抽对位。
4. 既有：run634 Twine 传导面（type19 传导序+龙骑伤害 5vs3）；
   Chess Board×58 / Holdall×28 / Rapier×27（未进 24 场样本的更大语料面）；
   F6 剩余 10 场 py 分歧；LINEUP 夹具（[8/17]）。

### 红线自查

全程无头后台；语料冻结只读；判定逻辑零改动；未执行 git 写操作；未触碰
Steam 目录；gd_core/*.gd 本轮零改动。

---

## 2026-10-10 · 闲时阶段1 第 12 轮（新会话第 5 轮）：调查轮——两条主线索受阻记录（无修复，零改动）

### 定靶（digest 04:24 版）

按 round11 入口 2/3 推进：run575 py 孪生面（gdcore≡oracle 但 py 分歧，
修成则 aligned 6→7）与 run571 APP rng pick。

### 线索 A：run575 剧毒蛇杖 py 毒叠面——根因定位到 mana 账本（受阻）

- 表现：gdcore_vs_py 首分歧 = Serpent Staff 第 2 毒事件 gd=1 vs py=2
  （t=4.100 同击伤害同为 7）；此后 py 毒量恒 +1（7/8、4/5）。
- py 类级探针（wrap onPreDealDamage_early/onDealtDamage）取证：
  damforpoison=4、acc 账本 `[SS] acc 2.0→1.0 dmg=7.0 manaEv=0`——
  同一击 py 计入（manaEv=1 → 2+7=9 → 9/4=2 毒、余 1），gd 未计入
  （gd 同位毒=1 ⇒ gd 侧 acc_pre+7 < 4 ⇒ 该击在 gd 未付费）。
  **判定：该挥击的 mana 付费状态 gd/py 不一致——上游 mana 账本孪生差**
  （tryUseMana/mana 消耗或 Toad/Mana Orb 充能流），非 SerpentStaff 局部、
  非伤害值面（事件伤害前段逐位同）。
- 受阻原因：修 mana 账本面需双侧 mana 逐笔仪表（tryUseMana/lostMana 事件
  不入 events.json），本轮仪表预算内无法闭环；禁投机修复。

### 线索 B：run571 Armored Power Puppy pick——阻塞于缺 oracle 逐抽日志

- 表现：t=1.77 同拍 pick，神谕 Empower(106)、内核 Lucky(101)。
  PowerPuppy.gd doCooldownEffect = Util.pickRandomElement(options)
  三选一轮换（选后 erase）；APP 只覆写 canAffect/onPrepare。
- 阻塞：fights/run571_r18/ 仅 rng_state.txt（无 rng_log.txt）——gd 注入
  神谕 state 后同位抽值应同，pick 差 ⇒ 此前隐藏抽消耗数有差（命中判定/
  动画抽不可见），无 oracle 逐抽日志不可对位。需找一个带 APP 且有
  rng_log 的 ORACLE_DEBUG 场，或换 drop 序列。

### 状态与核验

- 本轮**零代码/零数据改动**（探针全部进程内，无落盘）——状态与 round11
  终态逐位相同。
- 退步检：aligned_set.py check -b round3.txt → 基线 3+新增 3（run570/
  run573/run586）、退步 0 ✓（aligned 6/24 维持）。

### 下轮入口（round12 补记后修订）

1. **mana 账本孪生差（线索 A 收尾）**：双侧仪表 tryUseMana 路径
   （CoreCharacter.tryUseMana/CoreItem.tryUseMana？+ CoreBuff Mana 变更），
   run575 SS 侧 B 2.767-4.100 段逐笔对表；先验证一个最小可疑点：
   py `tryUseMana` 的 mana 不足判定与 gd 的 floor/float 语义。
2. **run571 APP**：扫全语料找有 rng_log.txt 且含 PowerPuppy 系的
   ORACLE_DEBUG 场（`ls output/oracle/fights/*/rng_log.txt`），有则逐抽
   对位 pick 抽；无则挂起。
3. **CP 分裂毒**（round10 受阻，run576/584）：同用线索 A 的 mana/acc
   仪表法（damageAcc 面已证同构，余下=分裂双事件的触发源定位）。
4. 既有：run634 Twine 传导面；Chess Board×58 / Holdall×28 / Rapier×27；
   F6 剩余 10 场；LINEUP 夹具（[8/17]）。

### 红线自查

全程无头后台；语料冻结只读；判定逻辑零改动；未执行 git 写操作；未触碰
Steam 目录；本轮零改动故无回归面。

---

## 2026-10-10 · 闲时阶段1 第 13 轮（新会话第 6 轮）：run575 SS 根因升级钉定——py onDealtDamage 钩见未减伤伤害

### 承接 round12 线索 A，根因升级（ Mana 账本假说证伪）

- **假说证伪**：run575 可见 mana 流水（含 −4 花费 idx99/147/152）两侧恒同
  ——round12「mana 付费状态不一致」推断作废。
- **gd 侧同款探针**（gd_core_items/Exclusive/SerpentStaff.gd 临时
  R13_PROBE print，已还原+硬链接双侧核验）：gd onDealtDamage 钩内
  damageRes.damage=5（=事件伤害）——manaEv/acc 账本与神谕毒量精确自洽。
- **py 侧探针（round12）**：同击钩内 damageRes.damage=**6**（=事件 5+
  SerpentStaff 自身 permDamBonus 加成 +1）。
- **升级后根因**：py 管线中 damageRes.damage 在 createEvent_Attack（事件
  已按减伤后 5 落账）与 item.dealtDamage(damageRes) 钩之间被
  addBonusDamage(+1) 增值——gd_core/CoreCharacter.gd:648-651 与
  gd_core_py/gd_core/CoreCharacter.py:643-646 该窗内五行逐字相同，增值
  发生在更上游（py 的 onPreDealDamage_early 加成进入 damageRes 的时点/
  路径与 gd 不同）。后果：SS `damageAcc += damageRes.damage`（SerpentStaff
  onDealtDamage）每付费击多记 +1 → 毒叠从 idx154 起 +1 漂移
  （gd 1/7/4 vs py 2/8/5）。
- 佐证细节：毒事件量 = int(acc/damfp=4) × 毒 buffPowers——探针行与
  gd 事件逐笔自洽（acc=0,dmg=5→毒1；acc=1,dmg=7→毒2；acc=0,dmg=6→毒1；
  acc=2,dmg=14→毒4），O/G SS 事件列表逐位全同。

### 受阻与修复入口（下轮）

- 修法收敛：对读 gd/py 的 onPreDealDamage_early 派发→randDamage→
  takeDamage→createEvent_Attack 管线中 damageRes.damage 的写点
  （CoreCombat.dealDamage/randDamage 段），钉 py 侧 +1 的注入时点。
  关键对照：gd 钩见 5 = py 钩应见 5；py 的 +1 若为管线上游真加成，
  则 gd 侧同点应同值——两侧必有一侧时点错。
- 本轮零代码改动（SerpentStaff 探针已还原；备份
  output/_round_patches/round13/SerpentStaff.gd.bak）。
- **运维注意**：单场 --force 会把 alignment.json 覆盖为单场视图 →
  aligned_set check 假退步（基线 3 场读成 0）。本轮已用 24 场全景
  --force 恢复完整比对（04:3x，aligned 6/24、退步 0 ✓）。下轮起
  定向跑后必须再跑全景或 compare-only 全量刷新 alignment.json。

### 状态

- aligned 6/24 维持；退步检 PASS；本轮零改动（探针还原+硬链接 inode 核验）。

---

## 2026-10-10 · 闲时阶段1 第 14 轮（新会话第 7 轮）：SS 毒叠漂移仪表推进（无修复，账本证据扩充）

### 承接 round13 入口：管线夹逼 + 复现性验证

1. **py 可复现性成立**：同参三次独立进程跑 run575（GDCoreEngine，
   seed=4513843，神谕对齐 kwargs）事件流 MD5：RUN-B==RUN-C
   （c2ee3671f9c64380476d3ae33f7e3999，398 events）——非 PYTHONHASHSEED
   类跨进程非确定，仪表差可信。
2. **管内夹逼**：包 createEvent_Attack（CoreCombatLog）+ bus
   dealt_damage/dealt_damage_signal_placeholder（CoreEventBus.emitSignal）+
   takeDamage 出口（CoreCharacter）——三层 dmg 逐站一致
   （createAttack=bus=exit，无 post-createEvent 改写站）。
   ⇒ round13 的「钩 6 vs 事件 5」观察实为**钩与事件属不同击**：
   py onDealtDamage 收到的 damageRes.damage 值集合
   {6,4,7,5,7,6,15,12,16,26} ≠ py 自身事件伤害集合
   {5,5,4,5,7,6,13,15,15,15}——**同一击两处值不同**的判断被推翻，
   真事实=py SS 钩的击伤害集合与事件集合系统性不同（如末击钩 26 vs
   事件 15）。
3. **fresh census 毒叠账**（04:3x 全景再生成的双表）：SS-B
   毒 gd=1@4.1 → 7@5.37 → 4@6.65；py=2@4.117 → 8@5.37 → 5@5.45 →
   8@6.62；毒事件量 = int(acc/damfp=4) × 毒 buffPowers（探针行
   acc=0,dmg=5→毒1、acc=1,dmg=7→毒2、acc=2,dmg=14→毒4 与 gd 逐笔自洽）。
   py 侧 acc_pre 在 4.117 已达 4 而其可见被计击仅有 dmg=6——
   **py damageAcc 账本存在非 onDealtDamage 路径的增量来源**
   （或截断输出漏计前段付费击，head -14 截断已确认是本轮仪表缺陷）。
4. round13「+1 加成注入时点」假说同样被本轮修正：差异非单发 +1，
   而是账本路径/速率差。

### 受阻（无修复）

- 全量非截断双侧账本 dump（py：不 cut head 全行 + owner/timestamp；
  gd：R13 探针加 owner/ctx.combat_time 两列重跑）留作下轮开局第一动作。
- 零代码改动（py 探针全进程内；gd SerpentStaff 探针 round13 已还原）。

### 下轮入口（round14 补记后修订）

1. **SS 账本全量 dump**（开局第一动作）：py 探针全行落盘文件 +
   gd R13_PROBE 探针加 owner/时间两列——按 owner 分侧重建
   damageAcc 账本，找 py 账本多出的增量击。
2. **run577_r7 / Stone×2 / src:poison×2** 等 rng-mechanism 13 场
   逐簇推进（同仪表法）。
3. run571 APP：全语料扫 rng_log+PowerPuppy 场（round12 入口 2）。
4. 既有：run634 Twine；Chess Board×58 / Holdall×28 / Rapier×27；
   F6 剩余；LINEUP（[8/17]）。

### 红线自查

全程无头后台；语料冻结只读；判定逻辑零改动；未执行 git 写操作；未触碰
Steam 目录；本轮零代码/零数据改动。

---

## 2026-10-10 · 闲时阶段1 第 15 轮（新会话第 8 轮）：CoreDamageResult int 型修复——SS 毒叠漂移根除

### 承接 round14：账本全量 dump 钉定真根因

- py 全量账本（不截断，owner=1/3 分侧）：owner1 acc 序
  0→2(6/4 浮点)→2→1→1→1；owner3 0→0→2→2→2。SS 钩 dmg 集合
  {6,4,7,5,7,6,15,12,16,26} 仍≠py 事件伤害集合（后段为级联放大）。
- **决定性反例**：owner3 t=2.8 击 dmg=5（未付费，acc 0→0 合法）；
  t=4.1167 击 dmg=6 → acc_pre=4?? 重推：**acc_pre=0、acc=6.0**——
  curPoison = `_div(6.0, 4)` = **1.5（浮点除）** >0 →
  `damageAcc %= 4` → 2.0 → inflictPoison(1.5)→round→**2**。
  gd 侧同击 `damageAcc(0) + 6` = 6（int）→ 6/4 = **1（GDScript int
  整除）** → 毒 1 ✓=神谕。账本"acc_pre=4"疑象=浮点 %= 的
  6.0%4=2.0 伪影——round14「非钩路径增量」假说撤销。

### 真根因（类型面）

- gd_core/CoreDamageResult.gd:18-20：`var damage: int` /
  `healthDamage: int` / `damageReduction: int`——**int 型字段**；
  decomp 权威 decompiled_full/Utility/DamageResult.gd:6-10 同为
  `var damage: int`。GDScript 对 int 型字段赋 float 静默截断。
- py 转写 CoreDamageResult.py 无类型：`makeCritical` 的
  `damage *= BASE_CRIT_SEVERITY(2.0)` 与 randDamage 的 float 值把字段
  污染成 float → 下游 `_div(damageAcc, damageForPoison)` 浮点除
  （gd int/int 整除）→ SerpentStaff 毒叠、War Scythe 暴击取整等
  整族 int 语义漂移。

### 修复（gd_core_py/gd_core/CoreDamageResult.py）

damage/healthDamage/damageReduction 三字段改 **int 强制属性**
（property setter 逐点 int() 截断 = 还原 GDScript int 型赋值语义；
GodotObject 无 __setattr__ 拦截已核验，_rt.py:1033 纯 object 语义）。
damageSource/hit/critical/event 等非数值字段不动。
备份：output/_round_patches/round14/gd_core_py/CoreDamageResult.py。
py 镜像手改，已注明（生成器 gd_to_py.py 无类型化信息，属转写层
已知类型丢失面）。

### 验证

- 定向 4 场（run575_r18 + 3 锚场）--force：**三方一致 4/4**
  （run575_r18 三方一致达成，毒叠账本逐笔对齐）。
- 24 场全景 --force（04:50 digest）：**aligned 7/24**（新增
  run575_r18，退步 0）；oracle≠gdcore 17 场中 7 场 py 合流维持；
  median 80 维持。非全绿 → 不触发全量里程碑/快照。
- 退步检：aligned_set.py check -b round3.txt → 基线 3 + 新增 4
  （run570/573/575/586）、退步 0 ✓。闸门 11：check_gd_py 531/531 ✓。
- run_gd_core 回归 0-7 全过（gd_core/*.gd 本轮零改动）、LINEUP=[8/17] 既有。

### 下轮入口（round15 补记后修订）

1. **int 型污染面全查**：py 侧同类无类型字段（各 Item 脚本局部
   `var damageAcc = 0`、`var damageAcc: int` 等 int 语义累加器被 float
   damage 污染的面不止 SerpentStaff——scan gd_core_py/gd_core_items 中
   `damageAcc`/`+= damageRes.damage` 模式逐个核对其 gd 侧声明类型；
   round10 的 War Scythe 暴击 33vs34、round11 的取整面或同根）。
2. **rng-mechanism 13 场**（首例 run569_r11）：Stone×2、
   src:poison×2（run574/576——本轮 int 修复后毒 DOT 值已变，重验后
   看是否消族）。
3. **gd_core-kernel 4 场**（首例 run571_r18：APP pick）。
4. 既有：run634 Twine；Chess Board×58 / Holdall×28 / Rapier×27；
   F6 剩余 10 场；LINEUP（[8/17]）。

### 红线自查

全程无头后台；语料冻结只读；判定逻辑零改动；未执行 git 写操作；未触碰
Steam 目录；gd_core/*.gd 本轮零改动。

---

## 2026-10-10 · 闲时阶段1 第 16 轮（新会话第 9 轮）：gd_to_py 生成器双修——typed-int 属性化 + push_back 兜底

### 背景事故（round15 回归的隐藏破坏面）

round15 的 run_gd_core 回归在其闸 [转译] 重跑了 tools/gd_to_py.py——
**gd_to_py 会重写整个 gd_core_py/**——round13（CoreItem push_back×3）、
round15（CoreDamageResult int 属性）两代手改被整体抹除（CoreItem.py
mtime/文件变大实证）。手改不可持续，本轮改为修生成器本体。

### 生成器双修（tools/gd_to_py.py）

1. **显式 `: int` 成员字段 → py int 强制属性**：field_inits 发射前收集
   typed_int（DECL_RE 的类型段=="int"）；发射存储字段 `self._<name>` +
   `<name>` property（setter int() 截断）= 还原 GDScript int 型赋值
   截断语义（decomp Utility/DamageResult.gd:6 `var damage: int` 权威）。
   根因场景：makeCritical `damage *= 2.0`（BaseCritSeverity float）把
   gd int 字段污染成 py float → 下游 `/` 整除漂移（run575_r18 SS 毒叠
   idx154 毒 1 vs 2 实证）。
2. **push_back 兜底重写**：transform_file 尾部
   `text.replace(".push_back(", ".append(")` 全量兜底——调用改写器按行
   解析实参，跨行续行调用漏网（CoreItem.py 3 处 trace 块 + 2026-10-08
   注释先例）。GDScript push_back 仅 Array 所有 → list.append 恒等价。
   实现注意：transform_file 为模块级函数（非方法），计数走 hit 参数；
   兜底块必须在 text 赋值之后（首版插错序 NameError，已修正）。
3. 补丁工具：output/_round_patches/round16/patch_gd_to_py.py（Write 工具
   落盘执行——JSON 层会吞一级反斜杠，heredoc 内联补丁两度失手的根因；
   锚点一律避开反斜杠字面量，需要的转义用 chr() 现场构造）。

### 重生成与验证

- `python -X utf8 tools/gd_to_py.py` 重生成 gd_core_py/ 全树：
  CoreItem.py 调用级 push_back 清零（余 3 处=文档注释文本）；
  CoreDamageResult.py 三 int 属性由生成器原生发射（damage/
  healthDamage/damageReduction → _damage/_healthDamage/_damageReduction
  + property×3）——**回归重生成不再抹修复**（治本验证点）。
- 定向 4 场（run575 + 3 锚场）--force：三方一致 4/4 ✓。
- 24 场全景 --force：aligned **7/24** 维持（新增集不变、退步 0）；
  **py 合流 7→9 场**（oracle≠gdcore 且 py 分歧 10→8）——int 修复
  在毒叠/伤害族再拉回 2 场 gd≡py。非全绿 → 不触发全量里程碑/快照。
- 退步检：aligned_set.py check -b round3.txt → 基线 3+新增 4、退步 0 ✓。
- 闸门 11：check_gd_py 531/531 ✓（重生成产物全量体检）。

### 下轮入口（round16 补记后修订）

1. **rng-mechanism 13 场**（首例 run569_r11）：int/push_back 修复后
   重盘 digest 聚类（Stone×2、src:poison×2、Steel Dragon miss×2 等），
   逐簇用 round9 双链逐抽法。
2. **gd_core-kernel 4 场**（首例 run571_r18 APP pick）：round12 阻塞
   （无 oracle rng_log）维持——除非找到带 rng_log 的 PowerPuppy 场。
3. **回归后必做**：run_gd_core 会重写 gd_core_py——此后 py 侧定向验证
   前先确认 git diff（本轮已验证 regen 稳定携带修复）。
4. 既有：run634 Twine 传导面；Chess Board×58 / Holdall×28 / Rapier×27；
   F6 剩余 8 场；LINEUP（[8/17]）。

### 红线自查

全程无头后台；语料冻结只读；判定逻辑零改动；未执行 git 写操作；未触碰
Steam 目录；gd_core/*.gd 本轮零改动。

---

## 2026-10-10 · 闲时阶段1 第 17 轮（新会话第 10 轮）：run576 双链对位——gd↔py rng 链全程零分歧（无修复，定界结论）

### 承接 round12/15 线索：run576 毒暴击旗（idx128 G 0 伤暴击 vs O 0 伤非暴击）

1. **poisonCrit 账本双侧恒同**：py 探针（Character.takeDamage 包裹，
   Poison 型 canCrit 击）取 damageSource.getCritChancePercent()——
   t=2/4/6 双方 40、t=8 双方 50、t=10 双方 55、t=12 player 20/opponent 55
   ——与 gd R17_PROBE 探针（CoreCharacter.takeDamage canCrit 分支）逐行
   全同。accumulation 面排除。
2. **双链对位（决定性）**：gd ORACLE_ALIGN_TRACE=1（3202 抽）vs py
   oracle_trace 全量（3206 抽，rng_state 注入）——容差匹配 + 偏移追踪
   遍历：**自 0.95-jitter run（gd#171/py#175，offset=4）起两链 3202 行
   逐位全同、offset 恒定、零值分歧、零消费差**（tolerance 1e-4；
   工具 output/_round_patches/round17/align_trace3.py，锚点/浮点
   均容差化——精确 lo/hi 字符串比较曾致假失配）。
3. **定界结论**：gd↔py rng 面干净（round13 注入 + round15 int 型 +
   round16 生成器修复后，双核消费与取值全程一致）。run576 的
   oracle 分歧 = **gd 相对 oracle 的隐形消耗差**（不可见抽位——
   命中前隐藏抽/条件抽计数），而 run576 无 rng_log.txt（仅
   rng_state）⇒ 与 oracle 逐抽对位阻塞。**与 round12 的 APP 阻塞
   同根：需要带 rng_log 的 ORACLE_DEBUG 场做抽级真值对位。**
4. **rng_log 资产盘点**：全语料仅 6 场有 rng_log.txt = run1029_r2 /
   run1122_r11 / run1160_r18 / run1301_r1 / **run569_r11**（rng-mechanism
   首例！）/ run570_r18（已对齐）。run569_r11 可做 gd↔oracle 逐抽
   真值对位——下轮开局第一动作（其首分歧 idx126 Stone 攻击 +0.08s
   时序面同族可一并定位）。

### 状态与核验

- 本轮零代码改动（探针全进程内 + trace 文件落 probe/）。
- 单场 trace 跑曾覆盖 alignment.json → 已用 24 场全景 --force 恢复
  （aligned 7/24、退步检 PASS；运维坑第二次踩中，见 round13 同款）。

### 下轮入口（round17 补记后修订）

1. **run569_r11 gd↔oracle 逐抽真值对位**（开局第一动作）：gd
   ORACLE_ALIGN_TRACE=1 trace vs fights/run569_r11/rng_log.txt 逐抽
   对表（oracle rng_log 格式=[序号, kind, from, to, 返回值]，含装配期
   包装抽）——首个分歧抽即 gd 相对 oracle 的隐形消耗差点，
   其调用上下文=修复点。方法论=round17 align_trace3.py 的偏移追踪
   遍历（gd↔py 版已验证）。
2. run569 定位后回灌 run571 APP / run576 毒暴击（同族隐形消耗差）。
3. 既有：run634 Twine；run572 Battery 充能闪几何（round17 已钉定
   子系统：Battery.onCombatStart→emitCharge→chargeCells 束流→
   chargedItemStatChange→addSpeed，O +18.2% vs G +9.0%）；Chess
   Board×58 / Holdall×28 / Rapier×27；F6 剩余 8 场；LINEUP（[8/17]）。

### 红线自查

全程无头后台；语料冻结只读；判定逻辑零改动；未执行 git 写操作；未触碰
Steam 目录；本轮零代码/零数据改动。

---

## 2026-10-10 · 闲时阶段1 第 18 轮（新会话第 11 轮）：run569 gd↔oracle 逐抽对位——标签设置位定界（无修复，按证据回滚）

### 承接 round17 入口 1：run569_r11 gd↔oracle 逐抽真值对位（该场有 rng_log.txt）

- **对位结果**：gd[0:] ↔ oracle[0:] 从第 1 行起完美对齐（196 行公共前缀），
  首个分歧抽 = **gd#197**：gd 抽 `randf_range(-10,10)`（物品浮动标签
  randInBox）×5，oracle 同位继续 (0.9,1.1)/(0.95,1.05) 冷却 jitter——
  gd 多耗、oracle 零耗。
- **oracle 侧 (-10,10) 全程计数 = 0**（982 行，浮点归一过滤复核）；
  (-30,30)×42（getNextFreeLabelPosition 兜底支）、(-50,50)×91 +
  (-70,70)×91 + 方向×91（攻击数字三元组）全在链上。
- 工具：output/_round_patches/round18/align_gd_oracle.py（oracle 行的
  @t 后缀与 EVENT 行容错解析；签名对位从 oracle[0] 起——gd trace 起点
  =播种后首抽、oracle log 首行=同点，天然对齐）。

### 定界：每录制场的标签设置位（新数据面）

- randInBox 行数随录制场剧变：run1122=580、run570=696、run1029=32、
  **run1160=0、run1301=0、run569=0**（tag= randInBox.x/y，oracle
  Util.gd:176-178 专用 trace）——**每录制场的标签视觉设置不同**
  （Labels/飘字开关），非槽位算法差。
- 后果：gd 全局恒耗（现行为）对标签-ON 场正确（run570/573/575/586 等
  已对齐场隐含 ON），对标签-OFF 场（run569 类）自首个标签起多耗 2 抽/个
  → 链位漂移。per-case 设置无法从 events.json/rng_state 反推
  （rng_log 在场时可直接数 randInBox 行判定——6 场可判）。
- **按证据回滚**：本轮曾试删 spawnLabel_native 的 2 抽——但该删除是
  全局行为，会破坏标签-ON 已对齐场（run570 rng_log 实证其 randInBox=696
  行在链上）；run569 的多耗点实为 CoreItem.getNextFreeLabelPosition
  （t=0 stack 标签），非 spawnLabel_native——删除点也不对。
  已按备份还原（output/_round_patches/round18/gd_core/CoreCharacter.gd），
  定向复验 run570 ✓ 三方一致维持、run569 回到既有分歧态。

### 可行修复方向（下轮评估，未实施）

- 方案 α：gd_core_py/gd_core 双核加「标签消耗开关」_ctx.label_rng_enabled，
  默认 ON；由 verify 驱动按 per-case rng_log（在场时）或夹具元数据设置。
  风险=未知设置场的默认选择（ON 已被 7 个对齐场约束）。
- 方案 β：维持恒耗，接受标签-OFF 场（run569 类）不可修复，语料按
  rng_log 有/无分组归档。
- 判据：用 6 场 rng_log 有/无 randInBox 行做分组，两组各取代表场跑
  gd trace 对位验证方案 α 的分组正确性。

### 状态

- aligned 7/24 维持（8 场视图：7 三方一致 + run569 既有分歧）；
  退步检 PASS（基线 3+新增 4、退步 0）。
- 本轮净改动 = 零（spawnLabel_native 已按备份还原；探针/工具落
  probe/ 与 round18/）。

### 下轮入口（round18 补记后修订）

1. **标签设置位分组验证**（方案 α/β 判据实验，见上）。
2. run572 Battery 充能闪几何（round17 钉定的子系统，未动）。
3. run634 Twine；run576 毒暴击（round17 定界：gd↔oracle 隐形消耗差，
   同受标签设置位影响的可能性高——run576 rng_log 缺失）。
4. 既有：Chess Board×58 / Holdall×28 / Rapier×27；F6 剩余 8 场；
   LINEUP（[8/17]）。

### 红线自查

全程无头后台；语料冻结只读；判定逻辑零改动；未执行 git 写操作；未触碰
Steam 目录；gd_core/*.gd 本轮零改动（探针已按备份还原）。

---

## 2026-10-10 · 闲时阶段1 第 19 轮（新会话第 12 轮）：per-case 标签视觉抽开关（方案 α 落地）

### 承接 round18 定界：每录制场标签设置位 → per-case 开关

机制实现（方案 α）：

1. **开关字段**：gd_core/CoreContext.gd + py 镜像加
   `label_rng_enabled := true`（默认 ON，与 7 个已对齐场隐含设置一致）。
2. **四个标签抽位加门**（gd+py 镜像同布）：
   - CoreCharacter.spawnLabel_native：`if item != null and ctx.label_rng_enabled:`
   - CoreCharacter 治疗路径：`... and origin is CoreItem and ctx.label_rng_enabled:`
   - CoreItem.getNextFreeLabelPosition：入口 `if not ctx.label_rng_enabled: return`
     （跳过抽与槽位时间戳写——OFF 场两抽与槽位簿记全免）。
3. **per-case 驱动**：
   - 夹具生成（tools/verify_oracle.py gen_fixtures 后处理）：按
     fights/<case>/rng_log.txt 的 randInBox 行数写 case["label_rng"]——
     **rng_log 在场且行数=0 → False；其余（含无 rng_log）→ True**
     （无日志=设置未知，默认 ON 受 7 个已对齐场约束；run569 rng_log
     实证 0 行 → OFF）。
   - gd 侧：OracleAlignBattle 在 ctx 创建后
     `if c.has("label_rng"): ctx.label_rng_enabled = bool(c["label_rng"])`。
   - py 侧：GDCoreEngine 新 kwarg label_rng_enabled（默认 None=ON），
     verify 驱动按同一夹具字段传入。
4. 备份：output/_round_patches/round19/（全部 9 个触碰文件）。

### 实施事故与修复

- gd_core/CoreContext.gd 首插错位（'var rng' 匹配到类外 0 缩进区，
  tab 缩进插入致 Parse Error :43 Unexpected indentation）——de-tab 修复。
- py CoreContext 首插同因错位（JSON 反斜杠层）——还原后改用精确
  tab 锚（`\t\tself.rng = None`）修复。
- CoreItem 双侧门首轮遗漏（脚本在 py heal 锚断言处中断）——补齐。
- py 治疗路锚（`origin != None and origin is CoreItem`）与
  spawnLabel_native 锚的实际文本核对后落位。

### 验证

- 定向 6 场 --force（含夹具重生成写 label_rng）：三方一致 **5/6**
  （run575 复活 ✓、3 锚场+run570 ✓、run569 OFF 后仍分歧=装配相序残面）。
- run569 OFF 后 gd 链与 oracle 的对位推进：标签抽已消失
  （gd#197 变 (0.9,1.1)），但同位值仍分歧（1.051 vs 0.937）——
  **装配相序/计数差浮出**（gd 在装配尾的 Flicker/anim 相位与 oracle 的
  jitter 相位交错序不同——round13 装配序家族的 GD-harness-vs-oracle
  变体，与 round13 的 gd-harness-vs-py 变体不同源）。
- 9 场定向：三方一致 7/9 ✓（新增集无退步）。
- 24 场全景 --force（04:5x）：aligned **7/24** 维持、退步 0 ✓。
- 闸门 11：check_gd_py 531/531 ✓。
- **regen 稳定性**：gd_to_py 重生成后四门全存活（门=纯 gd 代码翻译，
  生成器自动携带——round16 教训的正向应用）；定向复验 run575 三方
  一致维持 ✓。
- 10 场视图刷新 alignment.json（aligned 7、退步 0 ✓）。

### 下轮入口（round19 补记后修订）

1. **run569 装配相序差**（新前沿，唯一带 rng_log 的未对齐场）：OFF 后
   首分歧抽 gd#197 (0.9,1.1)=Flicker/anim 相位 vs oracle 同位 jitter——
   对读 gd_core_test/OracleAlignBattle 装配序（[seed][p_items][o_char]
   [o_items]）与 oracle 重放的逐物品相位（Item.gd:472 绑定抽 + Flicker
   入树 2 抽 + adjustCooldown 的交错序）。
2. **rng_log 缺失场的设置判定**：维持默认 ON；若未来发现 OFF 场无
   rng_log，考虑用「首分歧是否落在首个标签抽」回推。
3. 既有：run572 Battery 充能闪几何；run634 Twine；run571 APP pick；
   Chess Board×58 / Holdall×28 / Rapier×27；F6 剩余 8 场；LINEUP（[8/17]）。

### 红线自查

全程无头后台；语料冻结只读；判定逻辑零改动；未执行 git 写操作；未触碰
Steam 目录；gd_core/*.gd 本轮零改动（四门全在 gd_core_py/gd_core_test
侧与 gd_core/CoreContext.gd 字段）。

---

## 2026-10-10 · 闲时阶段1 第 20 轮（新会话第 13 轮）：run569 装配相序深查 + R17 探针清理（无修复）

### 承接 round19 入口 1：run569 装配相序差定位

- 复取 OFF 态 gd trace（标签抽已消失）+ oracle rng_log 全行对读：
  gd#197 起 (0.9,1.1) 值仍与 oracle 同位不同值（1.051 vs 0.937）。
- 行程编码对读：gd 装配 = [0.95-jitter 跑][0.975-jitter 跑×10] 后即
  进战斗（EVENT 0 @205）；oracle 装配在 0.975 跑（×9）后继续
  [(0.9,1.1) 与 (0.95,1.05) 交错的长跑]——**oracle 的装配尾 = 逐物品
  [Flicker/激活动画 (0.9,1.1)×2 + 下一物品 jitter (0.95,1.05)] 交错**，
  gd 的装配尾 = jitter 跑批后无此交错。
- gd 的 (0.9,1.1) 行 = t=0 激活的激活动画速度抽（gd trace 行 206/209/213：
  EVENT 0 后各 1 行 (0.9,1.1) + 交错 (0.95,1.05)）——每激活 1 抽；
  oracle 同相位 2 抽/物品——**per-activation 动画抽数 gd=1 vs oracle=2**
  （待 decomp Character.gd:451-452/473-474 攻击/跳跃动画 ×2 与激活
  ItemAnimation intialize ×4 的精确映射核验，下轮首查）。
- **受阻**：完整模型需对 decomp 激活动画抽数（ItemAnimation.intialize
  4 抽构成）逐项映射；本轮预算内未闭环。

### 清理

- gd_core/CoreCharacter.gd 的 R17_PROBE 临时探针（round17 引入，
  env-gated 无害但非净）已移除；移除后 4 场定向复验：基线 3+run575
  维持、退步 0 ✓。

### 下轮入口（round20 补记后修订）

1. **run569 per-activation 动画抽数**（首查）：gd t=0 激活抽 (0.9,1.1)×1
  vs oracle 同相位 ×2（ItemAnimation.intialize 4 抽构成的 (0.9,1.1)+
  (0.8,1.2) 拆分核验）——gd_core playCombatAni/activate 的动画消耗
  路径 vs decomp Item.gd 激活动画段逐行对读。
2. **每录制场标签设置位**（round18/19 遗留）：方案 α 已实现
  （label_rng per-case 开关），run569 OFF 后暴露的装配相序差 = 新
  独立面（见 1）。
3. run572 Battery 充能闪几何；run634 Twine；run571 APP；
   Chess Board×58 / Holdall×28 / Rapier×27；F6 剩余 8 场；LINEUP（[8/17]）。

### 红线自查

全程无头后台；语料冻结只读；判定逻辑零改动；未执行 git 写操作；未触碰
Steam 目录；R17 探针已清理。

---

## 2026-10-10 · 闲时阶段1 第 21 轮（新会话第 14 轮）：run569 标签门回滚为恒 ON（round19 规则证伪）

### round19 规则证伪（判据实验的回溯验证）

round19 以「rng_log randInBox(10,10) 行数=0 → label_rng=OFF」判 run569 OFF。
本轮证据推翻：
- run569 oracle rng_log：randInBox(x/y) 行=0 但 **randf_range(-30,30) 行=42**
  （kind=randf_range 非 randInBox tag——另一调用点/槽位全忙支），
  21 个物品标签全部走兜底支 = **标签仍 ON**（非设置 OFF）。
- OFF 门实测：run569 首分歧 126→**32**（恶化：门掉的 (10,10) 抽恰是
  oracle 链上存在的消耗——oracle 的标签抽经非 randInBox-tag 路径）。
- 结论：randInBox(10,10) 行数=0 ≢ 标签 OFF（槽位全忙/调用点 tag 差
  皆可致 0），该判据无效。

### 回滚与修复

- tools/verify_oracle.py gen_fixtures 后处理：label_rng **恒 True**
  （开关机制与三处链上门保留——未来有正向 per-case 证据时可用）；
  顺带清理 revert 时引入的坏字符注释与重复行。
- 验证：8 场定向 --force → 三方一致 7/8（run569 回到既有 idx126
  分歧态 ✓ 与 round18 对位结论一致：其 (-10,10) 消耗在 oracle 链上
  位置=197，gd 恒 ON 消耗与之同位——残面=该点之后的下一层差异）；
  退步检 PASS（基线 3+新增 4、退步 0）。

### 下轮入口（round21 补记后修订）

1. **run569 残面**：恒 ON 下 gd↔oracle 对齐至抽 #196，#197 起 gd 转入
  (-10,10)×5（标签抽）而 oracle 为 (0.9,1.1)/(0.95,1.05) 混合 jitter——
  oracle 的标签抽不经 randInBox-tag（kind=randf_range），gd 的
  getNextFreeLabelPosition 的 (10,10) 抽在 oracle 对应位=**别的调用**。
  对读 decomp Item.gd:6496-6506（labelOffsets + randInBox(10,10)/(30,30)）
  与 oracle Util.gd 的 spawnLabel 链路，钉 oracle #197 的真实调用点。
2. run572 Battery 充能闪；run634 Twine；run571 APP；既有大族不变。
3. **运维**：verify 单场/少场 --force 会覆盖 alignment.json——退步检前
  必须先跑全景或目标全集（round13/17/20 三次踩坑，已入志）。

### 红线自查

全程无头后台；语料冻结只读；判定逻辑零改动；未执行 git 写操作；未触碰
Steam 目录；本轮改动仅 tools/verify_oracle.py 的夹具后处理规则。

---

## 2026-10-10 · 闲时阶段1 第 22 轮（新会话第 14 轮）：run569 Stone/ASH 热加速-耐力复合面钉定（无修复，仪表全开）

### 承接 round18/21：run569 Stone 攻击节奏面（gd 2 击 vs oracle 5 击）

- **攻击序对照**：O Stone=3.3/6.217/7/9.3/9.833（间隔 2.917/0.783/2.3/0.533，
  加速+双击）；G=3.3/7（间隔 3.7，无加速）。
- **机制链钉定**：ArtifactStoneHeat extends Stone.gd——preHit→giveHeat(+3)
  逐击+热；热栈 (heat-cold)×0.02 → Item.getSpeed（decomp Item.gd:3760
  getStackSpeedMods / gd_core/CoreItem.gd:354 同式）→ 冷却消费速率。
- **双侧热事件同**：+3/次，O 5 次（3.62/4.05/7.1/7.75/9.98）、G 4 次
  （3.62/4.05/7.75/11.08）——giveHeat 面一致。
- **gd 速度仪表**（ORACLE_TRACE_ITEM=Stone item_trace，1634 行）：
  gd Stone getSpeed 随热上升 0.7692→0.80(ct3)→0.8403(ct4)→0.8772(ct6)
  →0.9174(ct9+)——**热→速度机制在 gd 生效**，但幅度（+0.15@heat15）
  远低于 oracle 节奏所需（0.78s 间隔 ⇒ speed≈3.2）。
- **复合面判定**：oracle Stone 的 0.5-0.8s 双击 = 热加速 × 耐力门放行
  的组合（doCooldownEffect 的 useStamina Sufficient 闸 + cd/speed），
  gd 侧差 = 热加速幅度或耐力模型（ Stone staminaCost/useStamina 语义）
  ——需 decomp Character.gd 耐力段+CombatTimer 段的专项对读，本轮
  预算内未闭环。

### 清理

- 无新代码改动；round17 的 R17 探针已于本轮早前移除（4 场复验维持）。

### 下轮入口（round22 补记后修订）

1. **Stone 热加速-耐力复合模型**（首查）：decomp Character.gd 耐力段
  （useStamina/StaminaResult/regen）+ Item.gd getSpeed 消费点 + gd 同位
  逐行对读；仪表=item_trace（speed 列）+ 双侧攻击序。
2. run572 Battery 充能闪（round17 钉定子系统：sendCharge→chargeCells
  束流→chargedItemStatChange→addSpeed，O +18.2% vs G +9.0%）。
3. run634 Twine；run571 APP；Chess Board×58 / Holdall×28 / Rapier×27；
   F6 剩余 8 场；LINEUP（[8/17]）。

### 红线自查

全程无头后台；语料冻结只读；判定逻辑零改动；未执行 git 写操作；未触碰
Steam 目录；本轮零代码改动（仪表全为现成机制）。

---

## 2026-10-10 · 闲时阶段1 第 23 轮（工作流轮 1）：invu 首入 randPitch 缺位修复（run634 idx142 闭合）

### 定靶（digest 13:13）

- aligned 4/5；唯一分歧 run634_r18 首分歧 idx142：oracle=Blind(109) vs
  gdcore=Cold(110)，origin=Amulet of Darkness，t=1.25。族=[gd_core-kernel]。

### 定位链（gd↔oracle 重放逐抽对位）

- oracle 重放基准：probe/wf1_634b（ORACLE_STACKTRACE 栈列在 headless 下为
  空，弃用）；gd trace：probe/gd + 修复后 probe/r2_634b。两份 oracle 重放
  （wf1_634b/r2_634st）纯抽序列 10402 行逐位全同（重放确定性 ✓；ANIM/
  SRC/LABEL 为非消耗诊断行）。
- 前段唯二差异：① 标签槽位支 vs 兜底支分支差 5 处（gd(-10,10) vs
  oracle(-30,30)，消耗数同、区间归一后流原始值同——纯判定无关分支，
  不修）；② **G795 oracle 多 1 抽 randPitch(0.9,1.1)@战斗 t≈1.0**。
- randPitch 调用点钉定：decomp Character.gd:1043-1044 makeInvulnerable 的
  `Sound.playSound(invuSound, 4, Util.randPitch(0.1))`——GDScript 实参求值
  即消耗（randPitch(0.1)=randf_range(0.9,1.1) 1 抽，Util.gd:682-683）。
- **根因**：gd_core/CoreCharacter.gd makeInvulnerable 的首次支剥音频时未
  保留该消耗——每次首次进入无敌链错 1 抽，invu 后的选型（idx142 AoD
  inflictRandomDebuffs pickRandomElement(0,2)）整体错位（gd=>2 Cold vs
  oracle=>1 Blind）。此后 2570 抽全为平移伪差。
- run570 反证兼容：run570 invuStart=0（无 invu 链）→ 无 randPitch 消耗 →
  gd_core 缺位不影响其对齐 ✓。run634 invuStart=6（重放 randPitch 共 8=
  6 invu + 2 装配期界面音效）。

### 修复

- gd_core/CoreCharacter.gd makeInvulnerable 首次支补
  `ctx.rng.randf_range(0.9, 1.1)` + decomp 行号注释（同 CoreItem.gd:2025
  送电荷位补法风格）；gd_core_py/gd_core/CoreCharacter.py:1326 镜像同补。
- 备份：output/_round_patches/round1/（gd_core/CoreCharacter.gd、
  py/CoreCharacter.py、oracle/Util.gd.bak——诊断补丁已还原）。

### 验证

- 定向 run634 --force：仍 0/1，但 **idx142→152**（idx142-151 全同，AoD
  Blind 修复生效 ✓），族 [gd_core-kernel]→[rng-mechanism]，gd 事件数
  3056→3345。
- 新 gd trace（probe/r2_634b）↔oracle 归一流值重扫：前 808 抽全同（含
  randPitch 位 ✓），G809 起「同流值不同调用点」段=触发次序差（无消耗差）。
- 退步检：单场视图覆盖 alignment.json 致首次 check 假退步（round21 运维
  坑第三次踩中）；5 场视图刷新后 check -b round3.txt = **基线 3 无退步、
  新增 run570**（4/5：run570/798/1195/1405 ✓，run634 残面）。
- 本轮未跑全量里程碑（代表场 run634 未绿，按流程不扩样本）。

### 残面（idx152，行为面非 rng）

- 同 t=1.25 拍事件集相同、次序/伤害值异：gd=[AoD 反击 damage**4** →
  DK miss → … → AoD damage0]，oracle=[DK miss → … → AoD damage**0** → …]。
  流同步下 AoD onItemActivated 反击（rollChance→dealEffectDamage(minDam)）
  的触发时机与伤害值差——查 AoD 反击绑定的激活序（getAffectedItems/
  activated 信号连接面）与 dealEffectDamage 对目标状态的判定。
- 另：gdcore_vs_py idx190 Leaf Badge 幸运 resisted（py 侧"获得幸运" vs
  gd"被无效化"）——F6 py 转写层独立面，与 rng 无关。

### 下轮入口（round23 补记后修订）

1. run634 idx152 触发次序面（首查）：AoD 反击的激活绑定序 vs decomp
   Item.gd onItemActivated/信号连接序；对照 gd_core_items/
   Exclusive/AmuletofDarkness.gd:18-22 与 gd_core/CoreItem.gd 的
   activated 触发派发序。
2. gdcore_vs_py idx190：Leaf Badge 幸运 resisted 语义（F6 py 转写层）。
3. 既有：Chess Board×58 / Holdall×28 / Rapier×27；gainedStacks/usedStacks
   数据面；LINEUP（[8/17]）。

### 红线自查

全程无头后台；语料冻结只读（fights/** 未触碰，诊断走 probe/ 与
ORACLE_FIGHTS_ROOT）；判定逻辑零改动；未执行 git 写操作；未触碰 Steam
目录；oracle/Utility/Util.gd 诊断补丁已按备份还原（grep ROLLSTACK=0）。

---

## 2026-10-10 · 闲时阶段1 第 24 轮（工作流轮 2）：FalconBlade 双击判定动画 3 抽缺位修复（run634 idx152 闭合）

### 定靶（digest 14:58）

- aligned 4/5；唯一分歧 run634_r18 首分歧 idx152：O=[对手]攻击落空（黏黏
  龙骑士） vs G=[玩家]造成4点伤害（黑暗护符），族=[rng-mechanism]。

### 定位链

- idx142 段重对位（gd trace=probe/r2_634b vs oracle 重放 probe/wf1_634b，
  归一流值 f=(v-lo)/(hi-lo) 跨区间可比）：idx142 Blind 事件前最后一个
  randi_range(5,10) 值差 gd=>5 vs oracle=>7 → 流在 idx141 段前已差 3 抽。
- 逐事件段对照（idx139 Crown 激活链）：oracle 侧 Crown→AoD 反击链消耗
  9 抽（音效×3 + (-30,30)/(-100,100)/(-5,5) + jitter + 标签×2）；gd 侧
  仅 6 抽（无 (-30,30)/(-100,100)/(-5,5) 三连）。
- **根因**：decomp/oracle FalconBlade.gd doCooldownEffect 尾部
  `createAnimation(); ani.randomizePosition()`——Animation.tscn 默认
  positionRandom=(30,100)、angleRandom=5 → 3 抽
  （Items/Animations/ItemAnimation.gd:23-28，oracle 实测区间
  (-30,30)/(-100,100)/(-5,5)，playback_speed 不抽——FalconBlade 只调
  randomizePosition 不调 intialize）。gd_core_items/FalconBlade.gd 剥视觉
  时把这段删成 `pass`——**每次双击判定后丢 3 抽**。
- 注：该 3 抽不经 playAnimation（无 ANIM 诊断行，打点在 playAnimation
  入口，FalconBlade 直调 randomizePosition 绕过）——round20 的 ANIM
  归属法对它失效，靠逐事件段 9 抽 vs 6 抽对照钉定。

### 修复

- gd_core_items/FalconBlade.gd doCooldownEffect 判定块后补 3 抽
  （ctx.rng.randf_range(-30/-100/-5)）+ decomp 行号注释。
- gd_core_py/gd_core_items/FalconBlade.py 镜像手补（文件头注明
  tools/gd_to_py.py 自动生成；手改可接受，日志注明）。
- 备份：output/_round_patches/round2/（items/FalconBlade.gd、
  py/FalconBlade.py）。

### 验证

- 定向 5 场（run570/798/1195/1405/634 --force）：三方一致 4/5 维持，
  **run634 首分歧 idx152→367**（t=1.25→2.85，+215 事件对齐），族仍
  [rng-mechanism]。
- 退步检 check -b round3.txt：基线 3 无退步、新增 1（run570）→ PASS，
  修复保留。
- 未跑全量里程碑（代表场 run634 未全绿）。

### 残面（idx367，下轮首查）

- oracle idx367/368：t107 Resistor {"amount":1/2,"resisted":true}×2 @2.85，
  紧随 idx366 Cog Badge 激活(2.85)——**Resistor 对 CogBadge 激活的
  Heat 响应链**；gd 侧完全无此 2 事件（直接跳到 2.95 Oil Lamp 激活）。
  查 Resistor 物品实现（对手方持有；Heat 施加/无效化判定）与 CogBadge
  激活的信号连接面。时戳 2.85 vs gd 无事件——非纯次序差，是响应缺失。
- 另：gdcore_vs_py idx188 Mana Orb（gd="获得1层魔法" vs py="被无效化"）
  ——F6 py 转写层独立面（ Mana Orb 的 resisted 语义）。
- 既有：Chess Board×58 / Holdall×28 / Rapier×27；gainedStacks/usedStacks
  数据面；LINEUP（[8/17]）。

### 红线自查

全程无头后台；语料冻结只读；判定逻辑零改动；未执行 git 写操作；未触碰
Steam 目录；py 镜像手改已注明；备份 round2/ 在盘。

---

## 2026-10-10 · 闲时阶段1 第 25 轮（工作流轮 3）：charge 折叠 collisionMapPosition 缺位修复（run634 idx367 闭合）

### 定靶（digest）

- aligned 4/5；唯一分歧 run634_r18 首分歧 idx367：oracle t107 Resistor
  Heat(amount1/2,resisted)×2 @2.85 vs gd 无事件（直接跳 2.95），族
  [rng-mechanism]。

### 定位链

- lineup（fights/run634_r18/lineups.json，冻结只读）：双方镜像，
  CogBadge@(8,4) face=0、Resistor@(8,3)——Resistor 在 CogBadge 充电
  chargeCells[1] 位。
- 手折 gd_core/CoreItem.gd:2044-2057 _chargeInventoryCells（face=0、
  CogBadge）：px=80*c+collisionMapPosition+(40,40)→floor(/80)+top_left——
  若 collisionMapPosition=(40,40)（CogBadge.tscn CollisionMap 节点
  position 实测 `position = Vector2( 40, 40 )`）则 inv_cells[1]=(8,3)
  命中 Resistor ✓；若缺省 (0,0)（CoreItem.gd:56
  `var collisionMapPosition := Vector2.ZERO`）则 14 格全错、(8,3) 不在
  →Resistor 不命中=gd 0 事件 ✓。
- **根因**：CoreItem.gd:2038-2040 考据注释已列 7 件送电物品的
  collisionMapPosition（=(40,40)/(40,40)/(40,40)/(40,0)/(-40,0)/(-40,-40)/
  (40,-20)，"由各物品脚本 _readyInit 写入"），但 7 个物品脚本**均未写**。
  tscn 逐一复核：Battery/ChargeSplitter/CogBadge=(40,40)、Generator=(40,0)、
  LightningStaff=(-40,0)、ManaCrystal=(-40,-40)、Con-Trap-Tron=(40,-20)
  ——与注释全一致。

### 修复

- 7 件 gd（gd_core_items/Exclusive/{Battery,ChargeSplitter,CogBadge,
  Generator,LightningStaff,ManaCrystal,ConTrapTron}.gd）_readyInit 首行补
  `collisionMapPosition = Vector2(...)`（tscn 实测值）+考据注释。
- 7 件 py（gd_core_py/gd_core_items/Exclusive/*.py）super()._readyInit()
  后补 `self.collisionMapPosition = Vector2(...)`（py 镜像手改，日志注明；
  ast.parse 7 件全过）。
- 备份：output/_round_patches/round3/（items/*.gd 7+Resistor.gd 探针备份、
  py_items/*.py 7）。

### 验证

- 定向 5 场（run570/798/1195/1405/634 --force）：三方一致 4/5 维持，
  **run634 首分歧 idx367→394**（t=2.85→3.18/3.20），Resistor Heat 双事件
  已对齐。
- 退步检 check -b round3.txt：基线 3 无退步、新增 1（run570）→ PASS。
- 未跑全量里程碑（代表场 run634 未全绿）。

### 残面（idx394，下轮首查）

- oracle idx394：t=3.20 [玩家] 无敌结束（辉耀王冠）vs gd t=3.18——**同一
  事件 1-2 tick 时戳差**。oracle invu 对：start 1.183333 dur=2→end 3.2
  （理论 3.183，+1 tick）；start 1.35 dur=2→end 3.3833（+2 tick）——
  InvulnerabilityTimer 到期边界语义（gd=物理帧步进 _invul_left，
  CoreCharacter.gd:1274 注；oracle=[M2] oracleTimeLeft 注册表 timer）。
  多 Crown（3 个）叠加 makeInvulnerable 的 changeTimer 累计延长路径
  待对照（gd_core/CoreCharacter.gd 1282-1283 else 支
  `_invul_left = invuDur + _invul_left` vs decomp Util.changeTimer）。
- 另：gdcore_vs_py idx188 Mana Orb resisted 语义（F6 py 转写层）不变。
- 既有：Chess Board×58 / Holdall×28 / Rapier×27；gainedStacks/usedStacks
  数据面；LINEUP（[8/17]）。

### 红线自查

全程无头后台；语料冻结只读（lineup 读冻结件）；判定逻辑零改动；无 git
写操作；未触碰 Steam 目录；py 镜像手改已注明；备份 round3/ 在盘。

---

## 2026-10-10 · 闲时阶段1 第 26 轮（工作流轮 4）：Timer 外部 start 重同步语义（invu+Buff 临时栈）修复（run634 idx394/450 闭合）

### 定靶（digest）

- aligned 4/5；唯一分歧 run634_r18 首分歧 idx394：Crown 无敌结束同一事件
  时戳差（gd 3.18 vs oracle 3.20），族 [rng-mechanism]。

### 定位链

- oracle 真值=oracle_fight.gd drive_timers（:871-913）：注册表自记剩余，
  「引擎读数变化 = 外部 start()/stop()（同步信号处理里发生）→ 下一 tick
  重同步」——**start()/changeTimer() 的当帧不扣，下一 tick 才首扣**
  （:885-889 `if eng != e[1]: e[0]=eng` 后 `if e[0]>0: continue`）。
- gd_core/CoreCharacter.gd tickPhysicsTimers（:1871-1876）同帧即扣
  （makeInvulnerable 在物品冷却推进段设 _invul_left=2，同 tick 末尾的
  tickPhysicsTimers 又扣 δ）→每次 invu start 早 1 tick 结束
  （实测：gd 3.18 vs oracle 3.20=1 tick）。
- oracle invu 对实证（fights 冻结 events）：start 1.183333 dur=2→end 3.2
  （+1 tick，resync 后 gd 已复现 ✓）；start 1.35 dur=2→end 3.3833。

### 修复（两处同族）

1. gd_core/CoreCharacter.gd：加 `_invul_resync` 标志——makeInvulnerable
   首次支与延长支（=Util.changeTimer，Util.gd:1591-1593）都置位；
   tickPhysicsTimers 重同步帧跳扣（下一 tick 首扣）。
2. gd_core/CoreBuff.gd：同族——Buff 临时栈 timer（gainTemporary 的
   timer.start / stop+start 重置支，oracle/Core/Buff.gd:160-173 同构）
   加 `_timer_resync`；_tick 重同步帧 return。
- py 镜像（gd_core_py/gd_core/CoreCharacter.py、CoreBuff.py）手改同布
  （ast.parse 过；日志注明）。
- 备份：output/_round_patches/round4/（CoreCharacter.gd/.py、CoreBuff.gd/.py）。

### 验证

- 定向 5 场（run570/798/1195/1405/634 --force）：三方一致 4/5 维持，
  **run634 首分歧 idx394→450→510**（本轮连续两次推进：idx394 无敌结束
  时戳对齐后显形 idx450 Blind 临时栈到期时戳差，Buff 修复后 idx450 对齐、
  又显形 idx510），族变回 [gd_core-kernel]。
- 退步检 check -b round3.txt：基线 3 无退步、新增 1（run570）→ PASS。
- 未跑全量里程碑（代表场 run634 未全绿）。

### 残面（idx510，下轮首查）

- oracle idx510：t=4.1333 t8 Crown 无敌结束；gd 同位无 t8（Crown 第二次
  doCooldownEffect 提前占位）。结构：OR t7@4.1167(dur=2) 与 t8@4.1333
  （+1 tick）矛盾——dur=2 不可能 1 tick 到期，疑「延长支（t7 事件照发）+
  旧计时到期同帧」。多 Crown（双方各 3 个）+双角色独立 timer+延长支的
  起止配对无 owner 字段可辨。
- 下轮工具：oracle 重放 ORACLE_RNG_DEBUG=1 抓 [timer-reg]/[timer-fire]
  dump（oracle_fight.gd:966/912 现成诊断行）取 InvulnerabilityTimer 的
  start/fire 时刻真值表；gd 侧对照 tickPhysicsTimers 序。
- 另：gdcore_vs_py idx188 Mana Orb resisted 语义（F6 py 转写层）不变。
- 既有：Chess Board×58 / Holdall×28 / Rapier×27；gainedStacks/usedStacks
  数据面；LINEUP（[8/17]）。

### 红线自查

全程无头后台；语料冻结只读；判定逻辑零改动；无 git 写操作；未触碰
Steam 目录；py 镜像手改已注明；备份 round4/ 在盘。

---

## 2026-10-10 · 闲时阶段1 第 27 轮（工作流轮 5）：idx510 timer dump 探索（无修复，记受阻）

### 承接 round26 入口 1：idx510 Crown 无敌结束缺失

- 工具落地：oracle_fight.gd drive_timers resync 分支加 [timer-resync]
  临时打印（备份 round5/oracle_fight.gd.bak，已还原）；重放
  probe/r5_634t(2)。
- **确立事实**：
  1. 重放 events 与冻结逐位一致（2568，t8 时刻全同）——dump 可信。
  2. oracle fire↔t8 事件映射恒定（offset=28.3=正式场开战 U.time）：
     fire 31.5/31.683/32.433/34.367/36.617/37.217 ↔ t8 3.2/3.3833/4.1333/
     6.0667/8.3167/8.9167——**oracle 端 invu 到期=事件时戳**，与 gd 修复后
     前两对（3.2/3.3833）已一致。
  3. **[timer-resync] 仅 6 条**（每场 Player/Opponent 各 1，eng=2.0
     old_reg=-1.0=stopped→首次 start）；**idx501 的 t7@4.1167 无对应
     resync**——oracle 端该次 makeInvulnerable 未改 InvulnerabilityTimer
     引擎读数（否则必打 resync）。
  4. fire@4.1333（=t8 idx510）位于 t7@4.1167 后 1 tick——dur=2 不可能
     1 tick 到期 ⇒ 4.1333 到期的是**更早的计时**（BotTimer/其它 timer 或
     多 Crown 延长累计），且 4.1167 的 t7 走了**不改引擎读数的路径**。

### 受阻（记跳过，禁投机修复）

- dump 时基换算未闭环：[timer-resync]/[timer-fire] 的 t=Util.time（进程
  墙钟，含暖场 M7），与 events combatTime（CombatTimer，开战 0 起）的
  offset 依赖「暖场/正式场开战时刻」的辨识；暖场 events 被丢弃不可对照，
  OR t7 事件无 owner 字段，双角色×3 Crown 的起止配对死锁。
- 下轮破局方案（按序）：
  1. gd 侧 t7/t8 补 owner_type 临时打点（CoreCharacter makeInvulnerable/
     invulnerabilityEnded 已知 playerId），重放对照 oracle t7/t8 的
     角色归属，先把 6 对 start/end 按角色拆开；
  2. oracle 侧再跑 ORACLE_RNG_DEBUG=1 + ORACLE_TRACE_TICK=<n>（oracle_fight
     的 _trace_tick [eat] 打印）抓 4.1167 前后 tick 的 rng 状态差，定位
     makeInvulnerable 的实际调用者（Crown checkTrigger 的 mana 源）；
  3. 或直接对读 gd_core Crown checkTrigger 与 decomp 的
     character().isVulnerable() 语义（decomp Crown.gd:27
     `character().isVulnerable()`——isVulnerable 的取反关系
     （isVulnerable= not invulnerable？）若 gd 侧语义反了，
     4.1167 的 else/首次支选择即错——**此前未对读过的低成本嫌疑点**。
- 另：gdcore_vs_py idx188 Mana Orb resisted 语义（F6 py 转写层）——
  giveRandomBuffs 双侧同构（CoreItem.gd:2575 / CoreItem.py:2670），
  分岔在 py 上游 rng 流微差，非本层。
- 既有：Chess Board×58 / Holdall×28 / Rapier×27；gainedStacks/usedStacks
  数据面；LINEUP（[8/17]）。

### 状态

- 本轮零代码改动（oracle_fight.gd 探针已按备份还原，grep=0）；
  aligned 4/5 维持；退步检 check -b round3.txt：基线 3 无退步、
  新增 1（run570）→ PASS。

### 红线自查

全程无头后台；语料冻结只读；判定逻辑零改动；无 git 写操作；未触碰
Steam 目录；探针已还原。

---

## 2026-10-10 · 闲时阶段1 第 28 轮（工作流轮 6）：invu timer 残留 e[1] 语义复刻（run634 idx510 闭合）

### 定靶（digest）

- aligned 4/5；唯一分歧 run634_r18 首分歧 idx510：oracle t8 Crown 无敌结束
  @4.1333，gd 缺失（Crown 第二次 doCooldownEffect 提前占位）。

### 定位链（round27 工具的延伸）

- fire↔t8 映射恒定（offset 36.0333，probe/r6_634t [timer-fire-dbg]）+owner
  拆配对（events origin.owner_type/top_left）：双方各 3 Crown，玩家
  (5,5)/(4,5)/(2,5)、对手同——**6 对 start/end 完全对应**。
- **oracle 残留语义发现**：[timer-fire-dbg] e0=-1.0167（Crown(2,5)@4.1333、
  Crown(4,5)@6.0667、Crown(2,5)@8.3167 等）——drive_timers stopped 支
  （oracle_fight.gd:882-884）**只写 e[0]=-1 不清 e[1]**（残留上次 dur）；
  之后同 dur 的 start() 使 eng==e[1] → **误走扣减支**（e[0]=-1-dt≤0）→
  **start 即到期**（同帧或 +1 tick）。Crown(5,5) 首次 start（timer 从未
  fired，stopped 支前 e[1] 初始）正常满 2s。
- gd 侧行为：Crown(4,5)/(2,5) 的 start 全走满 2s（end 6.15/8.0833 等）
  ——无残留复刻。

### 修复

- gd_core/CoreCharacter.gd：加 `_invul_fired`（invulnerabilityEnded 置位）、
  `_invul_last_dur`、`_invul_instant`——makeInvulnerable 首次支若
  `_invul_fired and dur==_invul_last_dur` 置 `_invul_instant`；
  tickPhysicsTimers 的 resync 帧内即时到期（同帧 fire，oracle 6.0667/
  8.3167 实测主模式）。
- gd_core_py/gd_core/CoreCharacter.py 镜像手改（ast.parse 过）。
- 备份：output/_round_patches/round6/（CoreCharacter.gd/.py、CoreBuff.gd/.py
  ——CoreBuff 本轮未改，备份为 round4 版快照）。

### 验证

- 定向 5 场（run570/798/1195/1405/634 --force）：三方一致 4/5 维持，
  **run634 首分歧 idx510→540**（+30 事件；gd t7/t8 现 6 对齐全，前 3 对
  end 时戳 3.2/3.3833/4.15 vs oracle 3.2/3.3833/4.1333——后两者差 1 tick
  为同帧/下帧变体取近似）。
- 退步检 check -b round3.txt：基线 3 无退步、新增 1（run570）→ PASS。
- 未跑全量里程碑（代表场未全绿）。

### 残面（idx540，下轮首查）

- Light Goobert Blind 到期 4.57 vs 4.58——**Buff 临时栈 timer 的 1 tick 差**
  （同族疑似：round4 的 Buff resync 模型 vs oracle Buff timer 的
  残留/非残留语义未定——oracle 实测 Blind 施加→3.0 整后到期（无 +1tick），
  与 Invuln 的 resync（+1tick）行为不同——两 timer 模型在 oracle 端**本就
  不一致**（Buff start 恒同 dur 触发残留扣减支、e[0] 从 -1 扣？与实测满 3s
  矛盾——需 BuffTimer 专项 dump：[timer-fire-dbg] 打印去掉 Invulnerability
  过滤，抓 BuffTimer 的 e0/eng 序列）。
- 另：gdcore_vs_py idx188 Mana Orb resisted（F6 py 转写层，giveRandomBuffs
  双侧同构，分岔在 py 上游流）。
- 既有：Chess Board×58 / Holdall×28 / Rapier×27；gainedStacks/usedStacks
  数据面；LINEUP（[8/17]）。

### 红线自查

全程无头后台；语料冻结只读；判定逻辑零改动；无 git 写操作；未触碰
Steam 目录；py 镜像手改已注明；备份 round6/ 在盘。

---

## 2026-10-10 · 闲时阶段1 第 29 轮（工作流轮 7）：Buff 临时栈三分支计时模型（idx540 仍差 1 tick，模型精化）

### 定靶（digest）

- aligned 4/5；唯一分歧 run634_r18 首分歧 idx540：Light Goobert Blind
  6 层组到期 gd 4.58 vs oracle 4.57（+1 tick），族 [rng-mechanism]。

### 定位链

- BuffTimer dump（probe/r7_634t，[timer-fire-dbg] 扩展过滤）：Crown/EvilCap
  等物品级 BuffTimer fire 序列齐；**Light Goobert 的 Blind 到期不经物品
  BuffTimer**（Buff 实例 timer 动态挂在 character 下）——物品级 dump 对
  idx540 无直接信息。
- oracle onTimeout 批次重启（oracle/Core/Buff.gd:327-350）：弹组后
  `delay = earliestTimeout - Util.time; timer.start(delay)`（delay≤0.01
  递归）——下一组到期=earliestTimeout **绝对值**（4.5667）。
- gd onTimeout（CoreBuff.gd:370-383）：弹组后只设 nextTemporaryTimeout，
  后续到期依赖**下一次施加的 start** 重启——**批次自续缺失**（恒 resync
  +1tick → 4.58）。

### 修复（模型精化：三分支）

- gd_core/CoreBuff.gd 计时器改三分支 start（_timer_last_dur/_timer_fired/
  _timer_instant/_timer_resync）：①running 同 dur→继续原计时（不重置）；
  ②fired-stopped 同 dur→残留立即到期；③idle/异 dur→resync +1 tick。
  _tick 同步（resync 帧不扣、instant 同帧末到期、fire 置 fired）。
- gd_core_py/gd_core/CoreBuff.py 镜像手改（ast.parse 过）。
- 备份：output/_round_patches/round7/（CoreBuff.gd/.py——round4-resync 版）。

### 验证

- 定向 5 场：三方一致 4/5 维持；idx540 仍 4.58 vs 4.57（三分支在本场的
  到期路径与 round4 恒 resync 等价——Blind 组 start 多为 fired-stopped/
  idle 态，分支①未触发）。
- 退步检 check -b round3.txt：基线 3 无退步、新增 1（run570）→ PASS。
- 未跑全量里程碑。

### 残面（idx540，下轮首查）

- oracle 4.57=**组 timeout 原值到期**（无 resync +1tick）：onTimeout 的
  timer.start(delay) 链在 oracle 端走了**非 resync 扣减**（e[1] 残留==delay
  同值时）或 delay≤0.01 递归吞帧。下轮：[timer-resync] 打印扩展到
  BuffTimer（round5 模式），抓 4.5667 前最后一次 start(delay) 的
  resync/delay 值；并补 gd onTimeout 批次自续（onTimeout 后按 earliest
  delay 重启计时器）。
- 另：gdcore_vs_py idx188 Mana Orb resisted（F6 py 转写层）不变。
- 既有：Chess Board×58 / Holdall×28 / Rapier×27；gainedStacks/usedStacks
  数据面；LINEUP（[8/17]）。

### 红线自查

全程无头后台；语料冻结只读；判定逻辑零改动；无 git 写操作；未触碰
Steam 目录；py 镜像手改已注明；备份 round7/ 在盘。

---

## 2026-10-10 · 闲时阶段1 第 30 轮（工作流轮 8）：Buff timer dump 深挖（三分支模型落盘，idx540 受阻记跳）

### 承接 round29 入口：BuffTimer resync/delay 专项 dump

- [bt-resync] 打印两轮（probe/r8_634t 过滤 BuffTimer、r8_634t2 过滤
  /Character/）：**Crown 物品级 BuffTimer resync 全序列**（18 条，每场
  Player/Opponent 各 3 Crown，eng=2.0 old_e0=-1 old_e1=0）；**Buff 实例
  timer（path=/Character/@@NNNN）**：Blind start@combat≈0.8（暖场 0.8167/
  正式 52.0167-50.8333）走 **resync（eng=3 old_e1=0 初始）**——非残留。
- fire 侧：Blind timer fire（@@13179 等）恒比对应到期**事件时戳晚 1 tick**
  （fire@29.983/30.733 → combat 3.833/4.583 vs 事件 3.8167/4.5667）——
  **oracle 桩的 fire 帧与事件创建帧错位 1 tick**（桩内部语义，冻结语料
  由此录制）。
- 重放 events 与冻结逐位一致 ✓（r8_634t2 复验）。

### 修复（Buff 计时器三分支模型落盘）

- gd_core/CoreBuff.gd 计时器三分支 start：①running 同 dur→继续原计时
  （不重置）；②fired-stopped 同 dur→残留立即到期（instant）；③idle/异
  dur→resync +1 tick。_tick 同步（resync 帧不扣、instant 同帧末到期、
  fire 置 fired）。_stopTimer+_startTimer（stop+start 重置支）走 ③。
- gd_core_py/gd_core/CoreBuff.py 镜像手改（ast.parse 过）。
- 备份：output/_round_patches/round7/（round4-resync 版）、round6/；
  三分支版未单独备份（改动在盘，git 可见）。

### 验证

- 定向 5 场：三方一致 4/5 维持；**idx540 仍 4.58 vs 4.57**（+1 tick）。
- 退步检 check -b round3.txt：基线 3 无退步、新增 1（run570）→ PASS。
- 未跑全量里程碑。

### 残面（idx540，深水记录）

- gd 的 6 层组到期事件 4.5834 的产生路径未定位：三分支下该组 start@
  1.5667 应走分支①（Blind timer running 同 dur）→原计时 3.8167 到期；
  onTimeout 后 timer 停、6 层组挂起——**gd 4.5834 事件的驱动源与
  oracle 事件创建帧（fire-1tick）的错位机制均未闭环**。
- 下轮破局：gd 侧 CoreBuff temporaryStacks/nextTemporaryTimeout/_timer_left
  加 ORACLE_PROC_DEBUG 门控打点（弹组时刻+组 timeout 值），重放对照
  oracle [timer-fire] 的 Buff timer fire 序列；或对 gd/onTimeout 补批次
  自续（按 earliest delay 重启）后再观察。
- 另：gdcore_vs_py idx188 Mana Orb resisted（F6 py 转写层）不变。
- 既有：Chess Board×58 / Holdall×28 / Rapier×27；gainedStacks/usedStacks
  数据面；LINEUP（[8/17]）。

### 红线自查

全程无头后台；语料冻结只读；判定逻辑零改动；无 git 写操作；未触碰
Steam 目录；py 镜像手改已注明；备份 round6/round7/ 在盘。

---

## 2026-10-10 · 闲时阶段1 第 31 轮（工作流轮 9）：onTimeout 批次重启去 resync（run634 idx540 闭合）

### 定靶（digest）

- aligned 4/5；唯一分歧 run634_r18 首分歧 idx540：Light Goobert Blind
  6 层组到期 gd 4.58 vs oracle 4.57（+1 tick）。

### 定位链

- gd 侧 [BPOP] 弹组打点（CoreBuff.gd onTimeout，ORACLE_PROC_DEBUG 门控，
  含数组快照；probe/r9_634b_run2）：
  - 弹组链 3.8167 三连（timeout 3.8/3.8/3.8167，递归 delay≤0.01）→
    start(0.7333, false)→**fire@4.5667**=oracle idx540 4.5667 ✓（对齐）；
  - 残 +1 tick 根因：**onTimeout 批次重启的 _startTimer(delay) 带 resync
    帧**（当帧不扣）——oracle drive_timers 的重启分支（oracle_fight.gd
    :903-905 `e[0]=get_time_left()`）**直接计时无重同步帧**——每段批次
    多 1 tick，链式累积（idx571：gd 5.75 vs oracle 5.73）。

### 修复

- gd_core/CoreBuff.gd：_startTimer 加 `resync := true` 参数（分支②③的
  _timer_resync 置位受控）；onTimeout 批次重启改 `_startTimer(delay,
  false)`（重启分支直接计时，decomp/oracle Buff.gd timer.start(delay)
  + drive_timers 重启分支同语义）。
- gd_core_py/gd_core/CoreBuff.py 镜像手改（ast.parse 过）。
- 备份：output/_round_patches/round9/（CoreBuff.gd/.py round30 版）、
  round7/（round4-resync 版）。

### 验证

- 定向 5 场（run570/798/1195/1405/634 --force）：三方一致 4/5 维持，
  **run634 首分歧 idx540→571**（Blind 6 层组 4.5667 对齐 ✓；新分歧
  对手 Blind 组 gd 5.75 vs oracle 5.73——批次链残余 +1 tick/段）。
- 退步检 check -b round3.txt：基线 3 无退步、新增 1（run570）→ PASS。
- 未跑全量里程碑。

### 残面（idx571，下轮首查）

- 批次链每段仍 +1 tick：gd「不 resync start」的下帧首扣+再下帧到期 vs
  oracle「重启分支同帧入列→下帧扣→下帧 fire」——gd start(0.0167) 后
  _tick 首扣 0→fire 应同下帧——实测链每段仍 +1，疑 gd _tick 驱动相位
  （CoreBuff._tick 在 tick 内的位置 vs oracle drive_timers 在 tick ⑥⑦）
  或 delay≤0.01 阈值边界（0.0167>0.01 走 start 而 oracle 同值走递归）。
- **组粒度面**（新暴露）：gd 3.8167 三连弹（5/2/2 组）vs oracle idx450
  单事件「5 致盲结束」——gd 的组切分（每次 giveStacksTemporary 一组+
  resisted 补偿组）比 oracle 细，事件数差（gd 3056+ vs oracle 2568）的
  构成之一。
- 另：gdcore_vs_py idx188 Mana Orb resisted（F6 py 转写层）不变。
- 既有：Chess Board×58 / Holdall×28 / Rapier×27；LINEUP（[8/17]）。

### 红线自查

全程无头后台；语料冻结只读；判定逻辑零改动；无 git 写操作；未触碰
Steam 目录；py 镜像手改已注明；备份 round9/ 在盘；BPOP/[BPOP] arr 打点
残留（门控 ORACLE_PROC_DEBUG，无害保留供下轮）。

---

## 2026-10-10 · 闲时阶段1 第 32 轮（工作流轮 10）：idx571 组构成探查（无修复，记组粒度面）

### 承接 round31 入口：批次链残余 +1 tick/段

- 重放当前代码（probe/r10_634b [BPOP] arr 快照）：gd 弹组链 3.8167×3 →
  4.5667（6 层 timeout 4.55）→4.7（4.6833）→5.7（5.6833）→5.75（5.7333）→
  6.6833→6.75→7.9833——**恒 timeout+0.0167**。
- oracle 对照：idx540@4.5667（=timeout+1tick ✓ gd 已对齐）；idx571@5.7333
  （=timeout **原值**，无 +1）——**oracle 端两行为并存**（4.55 组 +1tick、
  5.7333 组 +0tick）。
- 组构成探查：冻结 events 中 2.7333/5.x 段**无 Blind gain 事件**——
  5.7333 组的「施加=timeout-duration=2.7333」推算前提不成立（组 timeout
  可能经 resisted 补偿/多段 giveStacksTemporary 组合，非单次施加+3）。

### 判定

- idx571 残差与**组粒度/组构成面交缠**（gd 3.8167 三连弹 5/2/2 组 vs
  oracle idx450 单事件「5 致盲结束」——组切分不同→无法单点修 timer 模型）。
- 三分支模型（round30）保留：idx540 已对齐、退步检 PASS、无更优替代。
- 本轮零代码改动。

### 下轮入口（round32 补记）

1. **组粒度面专项**（idx571 前置）：gd 侧 [BGAIN] 打印（gainTemporary 的
   push 组时刻+timeout+duration+amount，ORACLE_PROC_DEBUG 门控）对照
   oracle SRC gain_label 行（oracle/Core/Buff.gd:195 已有 gain_label dump），
   钉双方组构成的差异点（resisted 补偿组/反射组/同 tick 多次施加的合并）。
2. 组构成对齐后，idx571 的 +1 tick 按修正后组序重推。
3. 另：gdcore_vs_py idx188 Mana Orb resisted（F6 py 转写层）不变。
4. 既有：Chess Board×58 / Holdall×28 / Rapier×27；LINEUP（[8/17]）。

### 红线自查

全程无头后台；语料冻结只读；判定逻辑零改动；无 git 写操作；未触碰
Steam 目录；本轮零代码改动；退步检 PASS。

---

## 2026-10-10 · 闲时阶段1 第 33 轮（工作流轮 11）：idx571 根因定位=LG 冷却节奏 +1 tick（Buff 面洗清，无修复）

### 承接 round32 入口：组粒度面 [BGAIN] 专项

- gd 侧 [BGAIN] 打印落地（CoreBuff.gd gainTemporary push 处，
  ORACLE_PROC_DEBUG 门控；probe/r11_634b）。gd Blind 组构成（玩家侧）：
  0.8（5+2 层，主+反射）、0.8167（5+2）、1.55（7）、1.6833（7）、
  2.6833（7）、**2.7333（7）**、3.6667（7）……
- 冻结 events 对照（idx<571 双方全同）：oracle 施加事件 idx332@2.6833、
  idx352@**2.7167**（各 7 层 dur3）；**gd 对应施加@2.6833 ✓、
  @2.7333（晚 1 tick）**——**对手 Light Goobert 的第二次 doCooldownEffect
  触发晚 1 tick**。

### 判定（根因移位）

- idx571 的「Blind 到期 +1 tick（gd 5.75 vs oracle 5.7333）」=**上游 LG
  冷却节奏 +1 tick 的直接后果**（组 timeout=施加时刻+3，施加晚→到期晚），
  **非 Buff timer 模型差**——Buff 面（三分支+批次重启无 resync）已正确，
  round29-31 的 timer 模型修复无需回退。
- 上游面=**冷却/耐力循环的 tick 节奏**（round22 Stone 热加速-耐力复合面
  同族）：LG doCooldownEffect 的触发经 useStamina 闸+冷却到期判定，
  第二拍起 gd 晚 1 tick。同拍第一拍（2.6833）双方一致——**首拍后节奏
  分岔**（首拍 useStamina 消耗/冷却重置的相位差）。

### 状态

- 本轮零代码改动（[BGAIN] 打印保留，ORACLE_PROC_DEBUG 门控）；
  aligned 4/5 维持；退步检 check -b round3.txt：基线 3 无退步、
  新增 1（run570）→ PASS。

### 下轮入口（round33 补记）

1. **LG 冷却节奏 +1 tick**（首查）：gd 侧对手 LG 的 doCooldownEffect
   触发链打点（useStamina 结果/冷却到期 tick），对照 oracle 同拍——
   oracle 端无 per-tick dump，用 events 施加时刻反推（第一拍 2.6833 同、
   第二拍 2.7167 vs gd 2.7333）；重点 gd_core Weapon.gd doCooldown 的
   冷却重置相位（doCooldownEffect 调用点 vs cooldown 重置的先后）与
   useStamina 的 Sufficient 闸判定时刻。
2. 组粒度面（次查）：gd [BGAIN]@0.8 双组（5+2 层）vs oracle 同拍单事件
   集合的组切分（主组+反射组 gd 拆两 TemporaryStacks、oracle 同构与否）。
3. 另：gdcore_vs_py idx188 Mana Orb resisted（F6 py 转写层）不变。
4. 既有：Chess Board×58 / Holdall×28 / Rapier×27；LINEUP（[8/17]）。

### 红线自查

全程无头后台；语料冻结只读；判定逻辑零改动；无 git 写操作；未触碰
Steam 目录；[BGAIN] 打印保留（ORACLE_PROC_DEBUG 门控）；退步检 PASS。

---

## 2026-10-10 · 闲时阶段1 第 34 轮（工作流轮 12）：扩样本回归检验（timer 模型修复零回归）

### 定靶

- run634 残面（idx571=LG 冷却节奏 +1 tick）属 round22 冷却/耐力深水，
  本轮预算内不再深挖；转**巩固轮**：round26-31 的 timer 模型修复
  （Invuln resync/instant/残留 e[1]、Buff 三分支+批次重启无 resync）
  触及所有含无敌/临时栈的场——扩样本检验回归风险。

### 扩样本（15 场，invu/临时栈计数排序优选）

- 场集：run1286_r18(12 invu)、run1291_r18(10)、run1315_r18(10)、
  run1317_r18(10)、run1323_r18(10)、run1413_r18(10)、run1264_r18(9)、
  run1049_r18(8 invu+293 temp)、run1116_r18(8)、run1153_r18(8)、
  run1171_r18(8+42 temp)、run1233_r14(8+76)、run1254_r18(8)、
  run1261_r18(8+93)、run1172_r18(8) + 既有 5 场 = **20 场 --force**。

### 验证

- 三方一致 4/20（既有 4 场全维持：run570/798/1195/1405 ✓）；新增 15 场
  全部保持**既有分歧态**（历史大族成员：Chess Board/Stone/Spell Scroll
  Dark/Djinn Lamp/Holdall 等，从未对齐过）——**零回归**。
- 退步检 check -b round3.txt：基线 3 无退步、新增 1（run570）→ PASS。
- 族分布：rng-mechanism 14、gd_core-kernel 2（run1315/1264 Chess Board
  激活面）、aligned 4。
- 首分歧 median=195（p25=28——idx<=19 有 3 场开战边界分歧，新样本面）。

### 下轮入口（round34 补记）

1. run634 idx571=LG 冷却节奏 +1 tick（round33 已记，round22 冷却/耐力
   深水——预算充足时攻）。
2. **新样本面**：20 场扩样本暴露 15 场既有分歧的首分歧分布（median=195、
   p25=28 含 3 场开战边界）——后续选靶可用 digest 签名聚类
   （Chess Board Activation×2、Stone Block×2 等簇）。
3. 另：gdcore_vs_py idx188 Mana Orb（F6 py 层）不变。
4. 既有大族：Chess Board×58 / Holdall×28 / Rapier×27；LINEUP（[8/17]）。

### 红线自查

全程无头后台；语料冻结只读；判定逻辑零改动；无 git 写操作；未触碰
Steam 目录；alignment.json 现为 20 场视图（下轮单场验证注意覆盖坑，
退步检前按需刷新视图）；[BPOP]/[BGAIN] 门控打点保留。

---

## 2026-10-10 · 闲时阶段1 第 35 轮（工作流轮 13）：LG 触发机制解密（激活计数驱动，非冷却——idx571 根因链闭合到激活节奏面）

### 承接 round33 入口：LG 冷却节奏 +1 tick

- 打点三轮迭代（probe/r12_634b）：CDT 打点（CoreItem 冷却段 triggerTime≤0）
  **0 条**——**Light Goobert 的 doCooldownEffect 不经冷却 tick 驱动**。
- **机制解密**（decompiled_full/Items/Goobert.gd vs gd_core_items/Goobert.gd
  逐行同构）：Goobert.prepare() `iterationCooldown = activationsToTrigger`，
  **onItemActivated（相邻物品激活信号）计数**：`activations += 1;
  if activations == getP1(): activations = 0; doCooldownEffect(); activate()`——
  **LG 的「冷却」=相邻物品激活次数计数**（canAffect=item.canActivate()），
  与时间 tick 无关——CDT 打点不触发是必然。

### 判定（根因链闭合）

- idx571（对手 Blind 组到期 gd 5.75 vs oracle 5.7333）根因=**对手 LG 的
  第二次触发晚 1 tick**（gd 施加@2.7333 vs oracle 事件@2.7167）——LG 触发
  =相邻物品激活计数到 N——**相邻物品（可激活物品）的激活节奏 +1 tick**
  ——上游=物品攻击/激活循环（round22 冷却/耐力深水面）。
- Buff 面（三分支+批次重启无 resync）与 LG 机制（激活计数）均已正确——
  残差全在上游激活节奏。
- CDT/_cdt_seq 打点已清（CoreItem.gd 还原，验证 4/5 维持）。

### 下轮入口（round35 补记）

1. **相邻物品激活节奏 +1 tick**（run634 idx571 前置）：对手 LG 的相邻
   可激活物品集（canAffect=item.canActivate()——对手背包）中哪个物品的
   激活晚 1 tick——events 激活事件（t0）对照：2.6833/2.7167 段两侧
   Activation 序列 diff（oracle idx324-357 段）。
2. 或转新样本面（round34 的 Chess Board/Stone 簇——与激活节奏面同源
   可能高）。
3. 另：gdcore_vs_py idx188 Mana Orb（F6 py 层）不变。
4. 既有大族：Chess Board×58 / Holdall×28 / Rapier×27；LINEUP（[8/17]）。

### 红线自查

全程无头后台；语料冻结只读；判定逻辑零改动；无 git 写操作；未触碰
Steam 目录；CDT 打点已清；退步检 PASS。

---

## 2026-10-10 · 闲时阶段1 第 36 轮（工作流轮 14）：round33 判定证伪（BGAIN 时标假象）+ idx540 对齐确认（无修复）

### 承接 round35 入口：相邻物品激活节奏 +1 tick

- 2.60-2.80 段双侧全事件并排（冻结 vs gd align/gdcore）：**39=39 逐条
  完全一致**（含 LG 的 t12/t109/t0@2.6833 与 @2.7167 双拍、Crown 净化、
  Mana Orb、DK 攻击、Twine、Stone Cold）——**round33 的「对手 LG 第二次
  触发晚 1 tick（gd 施加@2.7333 vs oracle@2.7167）」判定证伪**：BGAIN
  打印的 t=ctx.time 与事件时标 combatTime 差 1 tick（gd_core 的 ctx.time
  推进位置与 combat_time 不同步，round6 F7 修复后的既有相位）——打印
  时标假象，实际施加事件两侧同帧。
- idx540（Blind 6 层组 4.5667）**维持对齐** ✓（round31 修复有效）。
- idx571（gd 5.75 vs oracle 5.7333）=**oracle drive_timers 逐 tick 相位的
  1 tick 系统差**：oracle 端 6 层组到期 5.7333、gd 5.75——oracle 端
  onTimeout 链（fire→递归弹组→timer.start(delay)→重同步）的 fire 帧/
  首扣帧的错位组合，多轮单点推演均差 1 tick（4.55 组 +1tick 与 5.7333
  组 +0tick 并存，单模型不可拟合）。

### 下轮入口（round36 补记）

1. **drive_timers 逐 tick 轨迹 dump**（首查）：oracle_fight.gd drive_timers
   加 [timer-tick] 窗口 dump（combat 5.4-5.8 区间、Buff 实例 timer 的每 tick
   e[0]/eng/分支走向），重放对照 gd 侧同窗口 CoreBuff._tick 轨迹
   （gd 侧对称打点 [BTICK]）——按帧对齐两端曲线，直接读出 1 tick 差的
   分支点。数据量：窗口 24 tick×2 timer 可控。
2. 或转新样本面（Chess Board/Stone 簇——round34 扩样本的签名聚类）。
3. 另：gdcore_vs_py idx188 Mana Orb（F6 py 层）不变。
4. 既有大族：Chess Board×58 / Holdall×28 / Rapier×27；LINEUP（[8/17]）。

### 状态

- 本轮零代码改动；aligned 4/5 维持（run634 idx571）；退步检 check -b
  round3.txt：基线 3 无退步、新增 1（run570）→ PASS。

### 红线自查

全程无头后台；语料冻结只读；判定逻辑零改动；无 git 写操作；未触碰
Steam 目录；本轮零代码改动；退步检 PASS。

---

## 2026-10-10 · A4 横切：ItemDescriptor 成员 runtime 数据缺位盘点（判定面零缺口 → 零修复）

### 方法与全清单

- 打法：读 `decompiled_full/Items/ItemDescriptor.gd` 全部 var 成员（**57 个**，
  `:25-:84` 逐行正则盘点）× `decompiled_full/Sheets/ItemBook.gd` 赋值点 ×
  `assets/gd_core_runtime.json` descr 键集（**35 键**，517 物品全覆盖），
  缺失者逐一评估战斗判定面消费（gd_core/*.gd + 物品脚本 + 双引擎描述符装配点
  `simulator/gd_core_engine.py:782-833` / `tools/run_gd_py.py:315-341`）。
- **32 成员不在 descr 键集**；其中 `sortedParamNames/paramBases/paramBases_inverted`
  为 fromDict 从 namedParams **派生**（CoreItemData.gd:133-136,344-346）非数据缺口
  → 实缺 29，经消费面评估**全部非判定面**：

| 成员 | 装配点（decomp 行号证据） | 原版消费面 | 判定 |
|---|---|---|---|
| mentionedTypes | ItemBook.gd:1397-1399（typeCmds 描述文本推导） | ItemLibrary.gd:340 图鉴 UI | 记录不补 |
| mentionedStacks | ItemBook.gd:1392-1394 | ItemLibrary.gd:331 | 记录不补 |
| appropriatingItems | ItemBook.gd:1116-1118（CSV appropriated 列）+1305-1335 | RunData.gd:360 统计 UI | 记录不补 |
| startsSubclass | ItemBook.gd:912（shop 列 "Class>Subclass"） | 全 UI：ClassLabel.gd:57/InfoPanel.gd:160/ShopOffer.gd:95,166/SubclassSubtooltip.gd:14 + Game.gd:2154 选 subclass | 记录不补 |
| dynamicTypes | **非描述符成员**：Item.gd:420 per-Item 运行态 | Item.gd:3592-3595 getTypes/hasType | 无数据缺口：gd_core 已实现（CoreItem.gd:107,1467,1481-1502，CorruptedArmor/Cthulhu/SunArmor/BuytheHolyLight 调用），描述符侧 types 在 descr 517/517 |
| gateItem | ItemBook.gd:1103-1106 | Gems/Gem.gd:25-31 拖拽粒子（纯视觉）；内核侧 gd_core_items/Gems/Gem.gd:345 分支体为空 pass | 记录不补 |
| gatedItems | ItemBook.gd:1106 | getRelatedItems→tooltip（gd_core/CoreItem.gd:3288 零调用包装） | 记录不补 |
| shopChance | ItemBook.gd:822-824 fillList | 商店刷新：Item.gd:1178/Piggybank.gd:13(onShopEntered)/KingoftheBling.gd:48/MrStruggles.gd:74 | 记录不补 |
| physics/material | ItemBook.gd:843/842 | initPhysicsMaterial(Item.gd:651)/playPickup+DropSound(:3136,:3174 选音色；音高抽签数不受 material 影响，内核已按固定 1 抽建模 CoreItem.gd:896 注) | 记录不补 |
| activationAni | ItemBook.gd:884-890 | playActivationAnimation 视觉；内核 CoreHooks.gd:38-39 为 pass 桩 | 记录不补 |
| textEffect | ItemBook.gd:844-853 | ItemTooltip.gd:149-150 名字着色 | 记录不补 |
| threshold/weight/earliestRound/latestRound/shopItem | ItemBook.gd:822-824/:808 | 商店抽重/宝物池（randomItemOfRarity:527-539、getRandomTreasureDescriptor:601-619） | 记录不补 |
| requiredItem | ItemBook.gd:834-836 | 技能池(getSkillPool:1782-1789)+tooltip | 记录不补 |
| recipes/recipesAsIngredient/baseIngredients/recipeTree | ItemBook.gd:1112-1114/:1403-1409 | 合成 UI/商店补全权重(countItems:434-461) | 记录不补 |
| itemIndex/sheetIndex/version/searchDescription/scene/appearRounds/releaseState | ItemBook.gd:948-951/:808/ItemLibrary.gd:147/:778-791/:927-930/:740-746 | 商店 encountered/图鉴/装载闸/Skills 文本(JustStats.gd:22 等) | 记录不补 |

- gd_core 侧缺位成员的引用**全部**是字段定义/派生表/零调用包装器
  （CoreItemData.gd:34,37,52-53,59,110,143,299,310,313,320-321,324,336;
  CoreItem.gd:1445-1446,1453-1454,1528-1529,3288-3289）——战斗判定路径无消费者
  → **判定面消费缺口 = 0**，按「非判定面成员只记录不补」原则**零改动**，
  enrich 五点透传管道本轮无需启用。备份目录 output/_round_patches/a4-data/
  空置（无可备份改动，回归全量日志存于该目录 run_gd_core_a4_run2.log）。

### 验证数字

- grep 自证：缺失 32 成员在 gd_core/*.gd 的引用点全列（见上），零判定面调用者。
- `python -X utf8 tools/verify_oracle.py --cases run570_r18,run634_r18,run798_r18,
  run1195_r17,run1405_r17 --force`（重跑一次同结果）：**gd_core 侧 5/5 ok、
  ORACLE-ALIGN(gd_core) PASS 実敗 0**（run570 ticks=799 ev=548 含 selfcheck
  同种子根位一致；run634 ticks=1919 ev=2978；run798/1195/1405 ticks=2432/2372/2372）；
  三方比对 4/5 逐行一致；**py 侧 run634_r18 FAIL**：
  `TypeError: CoreBuff._startTimer() missing 1 required positional argument: 'resync'`
  ——**并行会话在 gd_core_py/gd_core/CoreBuff.py 的未完成手改**（HEAD 的
  `_startTimer(self, duration)` 三处 1 参调用自洽；工作区定义已改 `(duration, resync)`
  （对齐 gd_core/CoreBuff.gd:425 默认参）但 :298/:303 两处 1 参调用未改）。
  本横切面零改动，与此无关。
- `python -X utf8 tools/aligned_set.py check -b output/oracle/aligned_sets/round3.txt`：
  **基线 3 场 → 当前 4 场：新增 run570_r18，退步 0 → PASS**（run634 首分歧未前移）。
- `python -X utf8 tools/run_gd_core.py`（重跑一次同结果，exit=1）：**阶段 0-3 全过**
  （七生成器+语法面断言/静态审计/依赖环/ParseAll failed=0/16）；**阶段 [4/17] 契约冒烟
  FAIL 1 项**：「0.3+0.5 延长后 0.9s 时仍应无敌（总 1.0s）」（Smoke.gd:290）——
  **并行会话在 gd_core/CoreCharacter.gd:makeInvulnerable 新增 `_invul_resync/
  _invul_instant` 机制（mtime 17:45，diff 注明 run634_r18 idx510 根因）改变了
  延长支首扣帧**，契约尚未随新语义更新；阶段 5-7 未达。**与本横切面无关**
  （本横切面零改动）。注：本次重跑的 0/17 gd_to_py 阶段按流水线既定行为重写了
  gd_core_py/ 全树（CoreBuff.py/CoreCharacter.py mtime 17:59:59 同步再生），
  并行会话若对 py 有手改需在其收口后重落。

### 残留与下轮入口

1. **等并行 timer-resync 会话收口后**重跑：verify_oracle（py run634 预期自愈——
   gd_to_py 转写含默认参或其手改落定）+ run_gd_core 阶段 0-7（Smoke.gd:280-292
   契约或需按新 resync 语义更新，属该会话的活）。
2. 若下轮要给 startsSubclass/gateItem/gatedItems/shopChance/isReleased 等
   **接口字段**接真数据（UI/商店面服务），按 enrich 模板五点透传补——但 gd_core
   当前无判定面调用者，补数据零行为差异，须先有消费面再补。
3. 既有大族：Chess Board×58 / Holdall×28 / Rapier×27；LINEUP（[8/17]）；
   gdcore_vs_py idx188 Mana Orb（F6 py 层）不变。

### 红线自查

全程无头后台；语料冻结只读；判定逻辑零改动；无 git 写操作；未触碰 Steam 目录；
本轮零代码改动（仅追 logs 与本节）；退步检 PASS（round3 基线退步 0）。

## 2026-10-10 · 横切修复 A2：动画/标签位置抽缺位（loseHealth 3 抽 + RubyChonk 3 抽）+ 生成/手补互清事故与恢复

### 横切面

动画/标签位置抽缺位（A2 视觉面横切）。打法：grep decompiled_full
`randomizePosition|createAnimation|spawnLabel|randBuffLabelPos|randInBox`
（排除 Items/Animations/ 与 Util.gd 定义处），对照 gd 同名实现补缺；模板 =
FalconBlade doCooldownEffect 尾 3 抽（round24 实证）。

### 静态扫描（decomp 调用点 → gd 对照，全部 11 文件过一遍）

战斗态**缺位 2 处**：

| # | decomp 证据 | 抽数 | gd 原状 |
|---|---|---|---|
| G1 | decomp Core/Character.gd:856-857 `loseHealth`：`var pos = randDmgNumberPos()`（:665-668，DMG_NUM_OFFSET=(50,70)→2 抽）+ `var direction = randDmgNumberDir()`（:679-685，deg2rad(-21)..deg2rad(-3)→1 抽），无条件求值 | 3 | gd_core/CoreCharacter.gd:813 原 0 抽（调用方：DjinnLamp/BookofDarkness/DarkLantern/Phoenix/WandofDissonance + Item.gd:5125） |
| G2 | decomp Items/RubyChonk.gd:30-31 `createAnimation()+ani.randomizePosition()`（ItemAnimation.gd:25-28 3 抽；RubyWhelpAnimation.tscn:307 只覆写 aniName → 默认 (30,100)/5.0）；直调 randomizePosition 不含 intialize 的 playback_speed 第 4 抽（:30-34） | 3 | gd_core_items/RubyChonk.gd 原 0 抽 |

**排除面**（非战斗态，不动）：Game.gd:4144（switch-mode cog randInBox(10,10)）、
BoxofProsperity.gd:15 / StoneBadge.gd:41 / ItemBook.gd:416（onShopEntered/商店，
`randInBox(100,100)`）、Recipe.gd:212（打造，内核剥离）、Item.gd:4754-4801
activateFromEvent + Character.gd:418-430 replayEvent（回放路径，CombatLog.gd:588
触发，不进战斗 RNG 链）。其余调用点（Buff 三分支、critResisted、stun 双支、
takeDamage pos/dir + damageAnimation playback_speed、heal、spawnLabelOnItem 族、
getNextFreeLabelPosition、Item.activate 4 抽闸、FalconBlade）gd 侧**已有**，逐一
grep 对照过。

### 修复（4 文件 + py 镜像）

1. **G1 loseHealth 3 抽**：gd_core/CoreCharacter.gd:839-846（现 839 起，curHealth
   扣减后、事件创建前补 randf_range(-50,50)/(-70,70)/(-0.3665191429188092,
   -0.05235987755982988)）；
   gd_core_py/gd_core/CoreCharacter.py:885 起 **py 镜像同步**（同 3 抽）。
2. **G2 RubyChonk 3 抽**：gd_core_items/RubyChonk.gd:28-35（activate 后、
   hasHit 判定前，同 FalconBlade 模板 (-30,30)/(-100,100)/(-5,5)）；
   gd_core_py/gd_core_items/RubyChonk.py:44-49 **py 镜像同步**。
3. 备份：output/_round_patches/a2-visual/（gd_core/CoreCharacter.gd、
   gd_core_py/gd_core/CoreCharacter.py、gd_core_items/RubyChonk.gd、
   gd_core_py/gd_core_items/RubyChonk.py 的**本轮改动前**副本，保相对路径）。

### ⚠️ 事故记录：run_gd_core 阶段0 再生成 × 手补 互清（本轮主线外，必须读）

- 本轮按流程跑了 `tools/run_gd_core.py`（17:47-17:52）。其 [0/17] 物品转译
  （Items/*.gd → gd_core_items/）**清掉了全部 item 手补**：FalconBlade 3 抽
  （round24）、RubyChonk（本轮）、Battery/ChargeSplitter/CogBadge/Generator/
  LightningStaff/ManaCrystal/ConTrapTron 的 collisionMapPosition（round25）、
  以及 py 镜像同步面。**FalconBlade.gd/.py 与 7 件 + py 的 pre-clobber 内容
  靠会话首读 verbatim / round25 日志规格重布**（考据注释文字为重构，数值全按
  日志：Battery/ChargeSplitter/CogBadge=(40,40)、Generator=(40,0)、
  LightningStaff=(-40,0)、ManaCrystal=(-40,-40)、Con-Trap-Tron=(40,-20)）。
- 17:58:27/17:59:59 **并行代理的管线又清了一轮**（item 转译 + py 转写），
  FalconBlade.py/RubyChonk.py 再被清 → 二次重布。终态 grep 自证（18:10）：
  A2 三处 3 抽 gd+py 全在；7 件 collisionMapPosition gd+py 全在。
- 连带发现并行重转写丢 **CoreBuff.py `_startTimer` 的 `resync := true` 默认值**
  → py run634 TypeError；补 `resync=True`（gd_core_py/gd_core/CoreBuff.py，
  **py 镜像同步**，按 gd:425 签名）。以及 `_rt.py` 缺 `is_equal_approx` 垫片
  → py NameError；按 Godot 3.6 语义补入 gd_core_py/_rt.py（**代补**，a==b 快径
  + 1e-5 相对容差）并列入 __all__。
- **AmuletofDarkness.gd 会话前的未提交 M 态内容不可考**（本会话未读过、无备份、
  git 悬空对象 20 枚全为二进制资产）。证据显示该文件已被并行 py 转写层面代理
  接管（17:58:28 重写 .gd=HEAD 态；17:59:59 .py 加 damageAcc property 转写修复），
  17:48 那次清掉的损失面**待该面 owner 确认**。

### 验证（终态 = 18:10 重布后）

- 定向 5 场（`python -X utf8 tools/verify_oracle.py --cases
  run570_r18,run634_r18,run798_r18,run1195_r17,run1405_r17 --force`，共跑 4 次；
  前 3 次分别被上述事故/垫片缺失挡住）：
  **三方一致 4/5**；gd 侧 5/5 场 replay 全过（run570 selfcheck 同种子复现一致）；
  唯一分歧 run634_r18 **OG 首分歧 idx571 维持**（oracle t=344 vs gd t=345，LG
  致盲超时 +1 tick——round33 已记的 round22 冷却/耐力深水，**未前移**）；
  gdcore_vs_py idx188 Mana Orb（F6 py 转写层既有）不变。
- 退步检（`python -X utf8 tools/aligned_set.py check -b
  output/oracle/aligned_sets/round3.txt`）跑 2 次均：**基线 3 场 → 当前 4 场，
  退步 0，新增 run570_r18 → PASS**。
- 全量 `tools/run_gd_core.py`（1 次，17:47）：阶段 0 全部生成器 PASS
  （CoreItemBook 49 描述符一致 / 502 脚本 / LineupFixture / class_name 35 /
  转写 521 / GEN_GD_CORE_DATA PASS / SURVEY_VERIFY 21 项全对）、阶段 1 接口
  完整性 OK、阶段 2 无依赖环、阶段 3 PARSEALL ok 16/16；**阶段 4 SMOKE 3/4
  FAIL**：「0.3+0.5 延长后 0.9s 时仍应无敌」（Smoke.gd:290）——无敌计时器
  延长语义，属并行 timer 横切正在动的文件面（CoreTimer.gd 18:06、
  CoreCharacter.gd 18:08 仍在写），与本面改动无因果（该用例 prepareItems([])、
  纯计时器 tick，不触及 loseHealth/RubyChonk）；退出码 1，阶段 5+ 未达。
  **未重跑**：阶段 0 会再次清掉全部 item 手补（结构性互斥，见事故记录）。

### 残留

1. run634 OG idx571（LG 冷却节奏 +1 tick）——round22 深水，本轮维持未退。
2. gdcore_vs_py idx188 Mana Orb resisted 语义——F6 py 转写层既有。
3. gd_core smoke [4] 计时器契约 FAIL——并行 timer 面在改，非本面。
4. **结构性**：gd_core_items/*.gd 与 gd_core_py/** 是生成物，stage0 再生成与
   item 级手补互斥（本轮双向互清实证）；AmuletofDarkness 会话前 M 态损失待
   owner 确认。
5. 本轮 A2 两处补抽后的链位影响面：run634 场本身无 RubyChonk/loseHealth 物品
   触发（idx571 维持即证）；Djinn Lamp/Phoenix/Dark Lantern 等失血系与
   Ruby Whelp 阵容场待后续语料验证。

### 下轮入口

1. **首查并行 timer 横切**：smoke [4]（CoreTimer.gd/CoreCharacter.gd 18:04-18:08
   仍在写）收敛后重跑 run_gd_core 全 17 段；重跑前先做「手补在位」grep（本轮
   终态清单见上）。
2. **治本：转译器注入**——在 tools/build_item_scripts.py 建「RNG 链消耗注入表」
  （FalconBlade/RubyChonk 3 抽、7 件 collisionMapPosition），让 stage0 生成即含
   手补；同轮审计 gd_to_py 的 `:=` 默认值丢弃（_startTimer resync 实证）与引擎
   内建名缺失（is_equal_approx 实证）两类转写缺口。
3. run634 idx571（LG +1 tick，round22 冷却/耐力深水）。
4. F6 py 转写层：Mana Orb resisted 语义。
5. AmuletofDarkness owner：确认 17:48 被清内容是否仍有未重布部分。

### 红线自查

全程无头后台；语料冻结只读（--force 只删 gdcore/py 重放产物）；判定逻辑零改动
（仅补表现层链消耗抽与 py 镜像/垫片）；未执行 git 写操作；未触碰 Steam 目录；
py 镜像手改已注明（RubyChonk.py、CoreBuff.py、7 件 py、_rt.py 代补）；备份
a2-visual/ 在盘。

---

---

## 2026-10-10 · 闲时阶段1 第 37 轮（工作流轮 15，横切修复 A3）：Timer 外部 start/stop 当帧扣时语义（drive_timers 重同步横切）

### 真值与打法

- 真值 = oracle/oracle_fight.gd drive_timers（:871-913）：神谕手动 tick 下引擎读数
  冻结，外部 start()/stop() 只在**下一 drive 遍**被比对——eng != e[1] → 重同步
  （当帧不扣、下一 tick 首扣，:885-889）；stopped 支写 e[0]=-1 而 **e[1] 残留**
  （:880-882）→ fired/stop 后同 dur 重 start 误走扣减支（从 -1 起扣）→ 下帧即到期；
  fire 支：处理器重启直接计时（:905-910）、one_shot 未重启 e[0]=-1 **立即写入**
  （:912）。模板 = round25 `_invul_resync`（CoreCharacter.gd:168-177）/
  `_timer_resync`（CoreBuff.gd:67,435-461 三分支模型）。

### 静态扫描清单（gd 侧缺补点，行号证据）

| # | 位置 | 缺口 | 证据 |
|---|---|---|---|
| 1 | gd_core/CoreTimer.gd:60-70 `start()` | 外部 start/changeTimer 无重同步标志，当帧即扣 | oracle_fight.gd:885-889 |
| 2 | gd_core/CoreTimer.gd:86-93 `tick()` | 无重同步帧；无 stopped-pass 的 e[0]=-1 写入 | oracle_fight.gd:880-889 |
| 3 | gd_core/CoreTimer.gd:96-112 `_onTimeout()` | 无「处理器重启直接支」守卫；无 fire 尾 e[0]=-1 立即写入 | oracle_fight.gd:905-912 |
| 4 | gd_core/CoreCharacter.gd:1277-1284 `_setRageTimer()` | ①无重同步；②「延长」模型误读——原版 startBattleRage 是**绝对** start(fullDur)（Character.gd:1562），oracle 全文对 battleRageTimer 无 changeTimer 调用点（changeTimer 仅 invul/CritwoodStaff/Sandbag/CombatTimer.animationTimer） | oracle/Core/Character.gd:1557-1563 |
| 5 | gd_core/CoreCharacter.gd:1892-1896 `tickPhysicsTimers` 战怒段 | BattleRage 无重同步帧/残留 instant 支 | oracle_fight.gd:885-889 |
| 6 | gd_core/CoreCharacter.gd:328-341 `combatStart` | 缺 rebuild_timer_registry 对位（跨场 fired/残留 dur 未清；单场验证不可见，为多场会话忠实性） | oracle_fight.gd:685,950-975 |
| 7 | gd_core/CoreCombat.gd:383-397 `advanceTime` | fatigueStartTimer.start(newTime)（CombatTimer.gd:191 绝对 start）当帧即扣 | CombatTimer.gd:184-200 |
| 8 | gd_core/CoreCombat.gd:209-231 `activateItems` | 缺 rebuild_timer_registry 对位（开战序列 start 的 resync 清零 + 物品计时器 resetTimersSync） | oracle_fight.gd:685 |
| — | AutoRage 段（CoreCharacter.gd:1918-1923） | **无缺口**：唯一 start 在 combatStart（Character.gd:334），先于 rebuild_timer_registry → registry 捕获 running → 首帧即扣，内核已一致 | oracle_fight.gd:685 |
| — | fatigue `_fatigueTick`/`startFatigue`/`dealFatigueDamage` | **无缺口**：fst<ftt（Main.tscn:9905/9909，bootstrap :73-95 同序）→ start(3) 同 pass 重同步；start(1) 重启直充（CombatTimer.gd:179）；内核 recharge 模型帧位已一致 | Main.tscn:14984-14985 |

### 修复（py 镜像同补）

1. **CoreTimer.gd**：`start()` 四分支——①running 同 dur（eng==e[1] 无事件，原到期
   继续）/①'stop+start 同帧（e[0] 残留原剩余，复走续扣）/②stopped-pass 同 dur
   （e[0]=-1 起扣 → instant 下帧到期）/③resync+覆盖；`_last_dur`(e[1] 镜像)/
   `_resync`/`_instant`/`_firing`；`stop()` 保留 e[0]（get_time_left() 停走支照旧
   0.0）；`tick()` stopped 支写 -1、重同步帧不扣、instant 同帧末到期；
   `_onTimeout()` emit 前 stop（:889）+ `_firing` 守卫直接支 + fire 尾 e[0]=-1
   立即写入；新增 `resetSync()`。
2. **CoreItem.gd**：新增 `resetTimersSync()`（物品+宝石 DFS）。
3. **CoreCharacter.gd**：`_setRageTimer` 改三分支绝对 start 模型
   （`_rage_resync`/`_rage_instant`/`_rage_last_dur`）；`tickPhysicsTimers` 战怒段
   补重同步/instant 支；`combatStart` 补 registry 重建对位（rage+invul 标志与残留
   dur 清零）。AutoRage 段确认无缺口、不动。
4. **CoreCombat.gd**：`_fatigue_resync`（advanceTime 两支置位、`_fatigueTick` 首位
   消费=当帧不扣）；`activateItems` 末尾清零 + 双方物品 `resetTimersSync()`。
5. **py 镜像**：先手改 gd_core_py/gd_core/{CoreTimer,CoreItem,CoreCharacter,
   CoreCombat}.py（py_compile 过、三分支语义单测过）；流水线 0/17 gd_to_py 按改后
   gd 全量重写为生成态（标志名逐字面同构，gd/py 落位计数 16/3/17/6 完全一致）——
   py 镜像最终以生成器同步为准（该闸门本就每轮重写 gd_core_py）。
6. **gd_core_test/Smoke.gd（清单外，证据驱动）**：闸门 4 两断言为旧模型期望——
   ⑤「已战怒再触发=延长 1.6」与 Character.gd:1562 绝对 start 矛盾（本轮修复对象）；
   ②「0.3+0.5 延长」被 round25 残留语义改写——**改动前代码同样失败**（备份代码+
   原 Smoke.gd 实跑 SMOKE: FAIL「0.9s 时仍应无敌」1 项，非本轮引入）——按真值改写：
   ② 首响异 dur 0.6 避开残留支（延长语义只成立于 timer running）；⑤ 同 dur=原到期
   继续（≈0.617）+ 新增异 dur 覆盖/重同步帧不扣两断言。备份
   output/_round_patches/a3-timer/gd_core_test/Smoke.gd。

### 自证（grep 清零）

- 旧延长模型残留 `_rage_left = t + _rage_left`：gd+py 计 0。
- 三分支/direct 支落位：gd 四文件 16/3/17/6 处；py 生成态 16/3/17/6 处（逐面一致）。
- 「Util.changeTimer 语义」误读注释：清零。
- py 侧 CoreTimer 三分支语义单测（③ resync 帧/① 同 dur 续扣/①' stop+start 同帧/
  ② fired 同 dur instant/multi 队列续接无 resync 泄漏/resetSync 双态）全过。

### 验证数字

- `verify_oracle --cases run570_r18,run634_r18,run798_r18,run1195_r17,run1405_r17
  --force`：**4/5 三方一致**（run570/798/1195/1405 全维持）；run634_r18 首分歧
  **idx 571（=改前 571，未前移）**（oracle≠gdcore 且 py 分歧，rng-mechanism 族）。
- 退步检 `aligned_set.py check -b round3.txt`：基线 3 无退步、新增 1（run570_r18）
  → **PASS**。
- `run_gd_core.py`：**[0/17]-[7/17] 全过**（SMOKE PASS——含改写后的计时器契约面、
  GridSmoke/ItemParseAll 503 成功 0 失败/FacadeSmoke PASS）；**[8/17] LINEUP=HEAD
  既有失败**（夹具阵容 2<8，lineups 语料状态所致，mandate 预告可忽略；与代码无关）
  → 闸门 8 中止，9-17 未跑（与既有全量状态一致）。

### 残留

1. run634 idx571（Blind 组 drive_timers 逐 tick 相位 1 tick 系差）维持 round36
   判定——与本横切正交（Buff 面三分支 round31 已修，本轮未再动 CoreBuff）。
2. TickTimer 重启支：内核 `_tick_timer_left += 1.0`（欠账续接）vs oracle 重启支
   `e[0]=wait_time` 精确重置——不在本横切清单（BattleRage/AutoRage 段之外），
   4 锚场+run634 idx571 前未见影响，列为后续靶点。
3. advanceTime 在疲劳已启动后重复调用：原版对停走 fatigueStartTimer 的
   start(负值)→else 支会**重置 fatigue_counter**（CombatTimer.gd:196-199），内核以
   fatigue_next_tick 差值处理不重置——语料无战斗中调用者（PoweroftheMoon 仅
   onPostCombatStart），未动，记录在此。
4. CoreTimer.start() 无参（time=-1）会覆写 wait_time=-1（Godot 语义=保留旧
   wait_time）——语料无调用者，未动。
5. 清单外文件：gd_core_test/Smoke.gd（②⑤改写，判定证据见上）。

### 下轮入口

1. run634 idx571 维持 round36 入口：drive_timers 逐 tick 轨迹 dump（[timer-tick]
   窗口 5.4-5.8 + gd 侧对称 [BTICK] 打点）——按帧对齐直接读 1 tick 差分支点。
2. TickTimer 重启支精确重置（`_tick_timer_left = 1.0` vs `+= 1.0`）：先单场打点
   确认 onTick 触发时刻是否本就有 1 tick 相位差，再决定是否立横切。
3. 新样本面（round34 签名聚类：Chess Board×58 / Holdall×28 / Rapier×27）。
4. 另：gdcore_vs_py idx188 Mana Orb（F6 py 层）不变。

### 红线自查

全程无头后台；语料冻结只读（--force 只删两侧重放产物）；判定逻辑改动即本轮
横切对象本身；无 git 写操作；未触碰 Steam 目录；alignment.json 现为 5 场视图
（下轮退步检前按需刷新 20 场视图）；本轮全部改动文件备份于
output/_round_patches/a3-timer/（含 Smoke.gd）。


---

## a1 声音面横切（randPitch 实参求值消耗缺位）

时间：2026-10-10 17:40-19:10。对象：decompiled_full 全库 `randPitch|Sound.playSound`
调用点（Items/Interface/Core/Utility，排除 Utility/Util.gd:682 定义处）中、
gd_core_items/ 或 gd_core/ 存在同名实现而缺 ctx.rng 消耗者的每一处。
模板 = gd_core/CoreCharacter.gd makeInvulnerable 首次支 invu randPitch 补法
（round22 实证：GDScript 实参求值即消耗，Util.gd:682-683）。

### 清单与落位

- 全库 grep：randPitch 37 处 / 19 文件。其中 gd 同名实现缺消耗者 **14 文件 26 点**，
  本轮全部补齐：BadgerSpirit/CatSpirit/Crow/EvilHat/Ghost/HyperHedgehog/OwlSpirit/
  Pop/Toad/Ukulele/WaterElemental/Wisp 各 2（playPickupSound + playDropSound）、
  Chainsaw 1（:72 playPickupSound——战斗可达：onChargeReceived 首充调用）、
  Chess/ChessPiece 1（:74 onPieceCaptured 抽音在 doCapturingEffect 之前；同行
  captureSounds.pick_random() 走引擎全局链 docs/rng_truth.md §1.4-2，不折算 ctx.rng）。
- 已有覆盖核验：Core/Character.gd:1044（round22 invu 补，CoreCharacter.gd:1303）、
  Items/Item.gd:5153 sendCharge（CoreItem.gd sendCharge 4 抽已补）。
- 附加同面：gd_core/CoreItem.gd activateFromEvent 补 1 抽（decomp Item.gd:4741
  playActivationSound→:4684 playDropSound(-6)→:3171 randf_range(0.9,1.1)；该函数
  原版仅 CombatLog.gd:583 回放调用，live 战斗不可达，结构性补齐防漏）。

### 持久层（关键工程决策）

gd_core_items/* 与 gd_core_py/* 是 **run_gd_core.py 阶段 0 生成物**
（tools/build_item_scripts.py 物品脚本转译 + tools/gd_to_py.py Python 转写）：
对它们的手改在每一次阶段 0 运行中被整体覆盖（本轮实测被覆盖 4 次，含并行会话
触发的运行）。因此本面的落位修入生成器：

- tools/build_item_scripts.py 新增 `restore_randpitch_draws(rel, text)` pass
  （输出前逐文件执行；报告行「randPitch 消耗还原（a1 声音面）——文件 14、调用点 26、
  还原 26 抽」）：按反编译语句在函数体内的位次原位还原
  `ctx.rng.randf_range(0.9, 1.1)` + decomp 行号注释；整函数被剥（内核无此函数）
  → 不可达不补；基类适配层 Item.gd 不进 pass（sendCharge 已在内核手补、基类拾取/
  落物音消耗由 activate() ① 代表性消耗覆盖）。
- gd_core/CoreItem.gd 是源文件（不被再生成），activateFromEvent 手补；py 孪生由
  gd_to_py 自动派生（CoreItem.py:3657+ 同款消耗）。py 镜像不再手改——其文件头
  即「自动生成，勿手改」，正确口径是源侧修、生成器同步。

### 自证（grep 清零）

- 14 文件逐文件对表：decomp `Util.randPitch(` 数 == 生成物 `ctx.rng.randf_range`
  数，26/26 全对齐（BadgerSpirit 2/2 … Chainsaw 1/1、ChessPiece 1/1）。
- 运行时调用点核查：生成物内 playPickupSound/playDropSound/playActivationSound
  调用点仅 Chainsaw.gd:42（战斗可达）与 Item.gd:1298（playActivationSound 壳内
  自调用，而 playActivationSound 自身无调用者）。
- py 孪生 ast.parse 15 文件全过（CoreItem.py + 13 项 + ChessPiece.py）。
- 位次保真：ChessPiece 抽音落位 setState 之后、doCapturingEffect 之前（与反编译
  一致）；行号注释逐点核对（Wisp :62/:66、Chainsaw :72、ChessPiece :74）。

### 验证数字

- `python -X utf8 tools/verify_oracle.py --cases run570_r18,run634_r18,run798_r18,
  run1195_r17,run1405_r17 --force`（终态跑，19:00 前后）：**gd 5/5 PASS**；
  **三方一致 4/5**——run570/798/1195/1405 全维持（锚场+run570 零退步）；
  run634_r18 py 缺产物：`CoreBuff._startTimer() missing 1 required positional
  argument: 'resync'`——a3-timer 面在 gd_core/CoreBuff.gd:425 新增
  `resync := true` 而 gd_to_py 转写丢默认值（gd_core_py/gd_core/CoreBuff.py:494），
  非本面、本轮未触碰 CoreBuff。
- run634_r18 gd-vs-oracle 首分歧 **idx 152**（比上节 a3-timer 记录的 571 前移）——
  **A/B 实证非本面**：临时禁用 a1 pass 重建并重放（B 组）同为 idx152；且
  run634 阵容无 Chainsaw/ChessBoard，Wisp/Crow 为壳成员不被内核调用；idx152 处为
  Twine 连锁 vs Amulet of Darkness（并行面 in-flight 状态）。18:05 时点（本面抽
  同样在位）为 idx571 / gd ticks=1796 ev=2746 → 571→152 的漂移源自并行会话在本轮
  运行间隙落地的改动，本面两态不改变该场结果。
- 退步检 `python -X utf8 tools/aligned_set.py check -b
  output/oracle/aligned_sets/round3.txt`：基线 3 无退步、新增 1（run570_r18）
  → **PASS**（终态复跑同）。
- `python -X utf8 tools/run_gd_core.py`（含生成器补丁终态）：**[0/17]-[7/17] 全过**
  ——转译 503 成功 0 失败、randPitch pass 报告 26 抽、SURVEY_VERIFY 21 项全对、
  静态审计 OK、依赖环 OK、内核全量解析 failed=0/16、SMOKE PASS（timer 面收口后
  契约恢复）、GridSmoke/FacadeSmoke PASS；**[8/17] LINEUP=HEAD 既有失败**（夹具
  阵容 2<8 → 空矩阵与 3 条空指针，mandate 预告豁免）→ 闸门 8 中止，9-17 未跑
  （与既有全量状态一致）。

### 残留

1. Interface/Sellbox.gd ×7、ShopOffer.gd:275、Storagebox.gd:154——无 gd 同名实现
   （纯 UI 商店面），无法补；战斗重放不可达，如未来内核收录卖血/吞金币类机制需
   先补这 9 处（各 1-2 抽，eatGold/burp/chomp/close 还含 Util.randRange 抽）。
2. run634 idx152：并行面 in-flight 所致（A/B 实证与本面无关），待对应面收口后
   复测；若收口后仍 <571，沿 Twine 连锁 t=75 打点定位。
3. gd_to_py 对 `:=` 推断默认值丢转（`resync := true` → 形参无默认）——timer 面
   收口项，解锁 run634 py 腿。
4. **相反方向的疑似过消耗（非本面，专项裁定）**：内核 activate() 的无条件 ① 抽
   （CoreItem.gd:916，代表 playActivationSound→playDropSound(-6)）对 playDropSound
   覆盖为 **0 抽**的物品（CouragePuppy/PowerPuppy/WisdomPuppy——decomp 覆盖无
   randPitch）每激活多耗 1 抽；需语料对照确认后决定是否按 descriptor 查表化。
5. 其余 Sound.playSound 随机实参点均为商店/物理/打造面且无 gd 同名实现或战斗
   不可达，未动：Game.gd:3785、Inventory.gd:945、Shop.gd:820-821、UndoStack ×3、
   Item.gd:1898（拖拽物理落地）/1968（旋转）/2102（悬停）/6035/6049（打造锁）、
   Combat.gd:324 playGlitterSound（战斗结束后，重放不可达）。

### 下轮入口

1. run634 idx152：并行面收口后重跑同 5 场 --force；若仍前移，从 idx152 Twine
   连锁（t=75）逐抽打点对位（gd 侧 oracle_trace 已有 ANIM 标记同构可复用）。
2. gd_to_py `:=` 默认值转写修复（resync）→ 解锁 run634 py 腿，恢复 5 场全产物视图。
3. 残留 4 puppy 过消耗专项：先以含 puppy 的语料场逐抽对位确认，再决定 ① 抽查表化
   （descriptor.playDropDraws，0/1 两值）。
4. round34 新样本面（Chess Board×58 / Holdall×28 / Rapier×27）签名聚类不受本轮
   影响（Chess Board 抽音已在本轮 26 点内覆盖）。

### 红线自查

全程无头后台；语料冻结只读（--force 只删两侧重放产物）；判定逻辑改动即本轮
横切对象本身（生成器 pass 只还原已被反编译实证的消耗，不改任何判定分支）；
无 git 写操作；未触碰 Steam 目录；本轮全部涉及文件备份于
output/_round_patches/a1-sound/（30 文件快照 + run_gd_core 两份全量日志）。

---

## 2026-10-10 · 横切收口（工作流轮 16）：gd_to_py `:=` 默认值丢转修复（run634 py 腿恢复）+ SMOKE 残留复跑确认

### 收口项 1：CoreBuff._startTimer 调用/定义不匹配（py 腿缺产物根因）

- 症状：run634 py 腿无产物，`CoreBuff._startTimer() missing 1 required
  positional argument: 'resync'`。gd_core/CoreBuff.gd:425
  `func _startTimer(duration: float, resync := true) -> void :`（调用点
  :228/:233 单参默认 true、:415 双参 false），而修复前
  gd_core_py/gd_core/CoreBuff.py:494 `def _startTimer(self, duration, resync):`
  形参无默认 → :298/:303 单参调用 TypeError。
- 根因（a1 节残留 3 的落实）：tools/gd_to_py.py `top_level_eq`（原 :385-413）
  有意排除 `:=`（`prv in "=<>!+-*/%:"`，语句侧 `var x := 1` 由 DECL_RE 处理，
  不能当赋值改写），render_arg 对无顶层 `=` 的参数一律不产默认值——
  参数面 `:=` 推断默认值因此整类丢转。
- 修复（生成器侧，非 py 手改）：tools/gd_to_py.py 新增
  `top_level_infer_eq`（只认顶层 `:`+`=`，带引号/括号深度守卫）+
  render_arg `:=` 支路（命中计数「`:=` 推断默认值还原」，字面量内联、
  非字面量仍走 GD_DEFAULT 延迟求值）。随后全量重写 gd_core_py 生成态。
- 影响面盘点：gd_core/ + gd_core_items/ 全库 `func(` 参数扫描，
  `:=` 默认值唯一处 = CoreBuff `_startTimer(resync := true)`（gd_core_items
  0 处）→ 本修复单点生效。
- 修后实证：gd_core_py/gd_core/CoreBuff.py:494
  `def _startTimer(self, duration, resync=True):`；
  `compileall.compile_dir('gd_core_py/gd_core', force=True)` ok=True
  （CoreCharacter.py:549/557 两处 SyntaxWarning 为既有，非错误）；
  `python -X utf8 -m py_compile gd_core_py/gd_core/CoreBuff.py` 过；
  `inspect.signature(CoreBuff._startTimer) == (self, duration, resync=True)`。

### 收口项 2：SMOKE「0.3+0.5 延长后 0.9s 仍应无敌」残留 FAIL 判定

- 判定：**A3 已按新 Timer 重同步语义改写，无需再改**。现行
  gd_core_test/Smoke.gd:284-296（②）与 :316-330（⑤）均含「★ a3-timer」
  真值注（② 首响异 dur 0.6 避开 fired 残留支；⑤ 同 dur=原到期继续 +
  异 dur 覆盖 + 重同步帧不扣两断言），旧「0.9s」文本在全文件中已不存在。
- 语义自洽复核：延长支 gd_core/CoreCharacter.gd:1352-1355
  `_invul_left = invuDur + _invul_left`（Util.changeTimer 语义）+ resync
  当帧不扣——② 的 0.3+0.5+resync 帧 ≈0.817s 总量与 1.0s 断言步幅自洽。
- 复跑确认：本轮 run_gd_core 阶段 4 SMOKE PASS（test4 done，无 FAIL 行），
  全日志 grep「0.9s / 仍应无敌」零命中。本轮 Smoke.gd 零改动
  （改前态快照仍留备份备查）。

### 验证数字（两条命令 + 保险退步检）

- `python -X utf8 tools/run_gd_core.py`（全量日志
  output/_round_patches/close-resync-default/run_gd_core_close.log）：
  **[0/17]-[7/17] 全过**——[0] 注册表 49 描述符一致 / 转译 502 / a1 randPitch
  pass 26 抽在位 / Python 转写（生成器修复随阶段 0 生效）/ SURVEY_VERIFY
  21 项全对；[1] 静态审计 OK；[2] 依赖环 OK；[3] PARSEALL failed=0/16；
  [4] SMOKE PASS；[5] GRID PASS；[6] ItemParseAll 成功 503 失败 0；
  [7] FACADE PASS。**[8/17] LINEUP 既有失败**（夹具阵容 2<8 → 空矩阵 +
  3 条空指针，mandate 预告豁免）→ 闸门 8 中止，9-17 未跑（与 A1/A3 记录的
  既有全量状态一致）。
- `python -X utf8 tools/verify_oracle.py --cases
  run570_r18,run634_r18,run798_r18,run1195_r17,run1405_r17 --force`（日志
  verify_oracle_close.log）：gd 侧 **5/5 PASS**；**三方一致 4/5**——
  run570/798/1195/1405 全维持（锚场零退步）。**run634_r18 py 腿恢复**：
  [py] 完成 5/5 场、pyEvents=2875、py winner=player（与 oracle 同），
  missing 'resync' 崩溃消除。run634 残余分歧两线：
  ① oracle_vs_gdcore 首分歧 **idx152**（Twine 连锁 vs Amulet of Darkness，
  t=75）——与 a1 节记录一致（并行面 in-flight 所致），未前移未后移；
  ② gdcore_vs_py 首分歧 **idx190**（Leaf Badge type101 params：gd 含
  `"resisted": true`，py 无该键，t=90）——py 腿此前早死不可见、本轮恢复
  产物后**新暴露**的 py 侧缺口，列下轮入口。
- 保险退步检 `python -X utf8 tools/aligned_set.py check -b
  output/oracle/aligned_sets/round3.txt`：基线 3 无退步、新增 1
  （run570_r18）→ **PASS**（与 A1/A3 终态一致）。

### 残留与下轮入口

1. run634 idx190 Leaf Badge `resisted` 参数 py 缺：查 gd→py 参数转写面
   （type101 事件 params 构造处 CoreItem/CoreCombat 侧）——py 腿恢复后
   首个可定点的新靶。
2. run634 idx152 维持 a1 节入口：并行面收口后复测；若仍 <571，沿 Twine
   连锁 t=75 逐抽打点对位。
3. a1 节残留 4（puppy activate ① 抽过消耗专项）与本节残留 1 同属
   py/gd 参数与消耗面对照，可合并侦察。

### 红线自查

全程无头后台；fights/** 冻结语料只读（--force 只删两侧重放产物）；
未改 tools/verify_oracle.py 判定逻辑（本轮改动面 = gd_to_py 生成器 +
gd_core_py 生成态）；Smoke.gd 零改动；无 git 写操作；未触碰 Steam 目录；
本轮涉及文件改前态备份于 output/_round_patches/close-resync-default/
（gd_to_py.py、CoreBuff.py、Smoke.gd + run_gd_core/verify_oracle 两份全量日志）。

---

## 2026-10-10 · 逐族收敛轮 fam_r1：棋族数据面+语义面三连修（Chess Board Activation ×68 簇）

### 族名与选取

`python -X utf8 tools/alignment_digest.py`：aligned=118/914；最大签名簇
= **68 场** pair=oracle_vs_gdcore type=Activation(0) origin=Chess Board
（代表 run645_r11,run647_r10,run660_r18,run669_r10,run675_r18；行差样例
O:0.90 白兵激活 vs G:1.73 虚无之刃）。代表场 run645_r11 定位。

### 根因（三层叠加，逐层剥出）

棋盘在 gd 侧**整场静默**（run645 重放 301 事件中棋族=0，oracle=41）。逐层：

1. **types 数据缺口**：12 棋子（Black/White Pawn/Knight/Bishop/Rook/Queen/King）
   `assets/battle_items.json` types=[]，真值=[ChessPiece(17)]。证据链：
   decompiled_full/Sheets/CSV/ItemData_e.csv `Black Pawn,type="Chess Piece"` →
   ItemBook.gd:764 `table.getEnu("type",…)` + Table.gd:46-52 getEnu 去空格 →
   Items/Item.gd:33-64 enum Type 第 18 成员 ChessPiece=17；
   消费面 Item.gd:3594 hasType、Chess/ChessPiece.gd:28 canAffect、
   Chess/ChessBoard.gd:108/126/139。battle_items 其余 517 件 types 全对
   （大小写归一全表扫描，缺失恰 12 件）。
2. **grid 数据缺口**：同 12 件无 grid 字段（45 件缺 grid 中的棋子子集）；
   ChessPiece.prepare 的 moveCells 取自 affectedTileCells（tscn tile_data），
   无 grid → moveCells 恒空 → capture 永不命中。tile 解码实证：
   Piggybank.tscn tile3=[(-1,-1),(0,-1)]/tile4=[(-1,-2),(-1,0),(0,-2),(0,0)]
   与 battle_items Stone/Piggybank 现存 grid **逐格相等**（tile3=collision_cells、
   tile4=affected_cells）；12 棋子 tscn 解码存
   output/_round_patches/fam_r1/chess_grid_truth.json。
3. **局部格/绝对格口径分歧**（语义面，本层解锁前两层后才可见）：
   decompiled_full/Items/Exclusive/Chess/ChessPiece.gd:50-51 prepare 把
   affectedTileCells 当**局部格**（`cell.rotated(rotation)`，ChessBoard.gd:104
   `occupiedCells[0]+cell` 还原全局）；内核装配口径 affectedTileCells=**绝对格**
   （placement_of 烘焙平移+旋转；消费面 gd_core/CoreItem.gd:2940-2943
   getAffectedCellsInInventory→getCellsForGlobalPositions 直接按全局格取）。
   棋子是唯一按局部格消费 tilemap 格的脚本 → moveCells=绝对格，capture 查询格
   整体错位。诊断路径：ORACLE_TRACE_ITEM=Chess Board 的 item_trace（棋盘
   每 0.9s 触发但零事件）→ 临时诊断脚本（board activeWhite=3/activeBlack=4
   正确、moveCells 全空）→ affectedTileCells={} → 夹具分层定位
   （oracle_align_cases.json 陈货，--cases 生成的几何不含 grid 修复）。

### 修复（改前态备份 output/_round_patches/fam_r1/）

- `assets/battle_items.json`：12 棋子 types []→["chesspiece"]；补 grid
  （collision_cells=[[0,0]] + affected_cells=各 tscn tile4 格，兵=(±1,-1)、
  马=8 跳点、象/车/后=5 步射线、王=8 邻格，与棋规一致）。
- 生成态同步：`tools/gen_gd_core_data.py`（types→[17] 进 descr；
  rot.affected 出受击格）+ `tools/gen_lineup_fixture.py`（item_battle_fixture
  [17] + 几何）；用例夹具由 verify_oracle gen_fixtures 随 --force 重生成。
- `tools/build_item_scripts.py` 新增 pass `adapt_chess_movecells`
  （仅 Exclusive/Chess/ChessPiece.gd；幂等替换，报告行
  「棋子 moveCells 局部格换算（fam_r1 棋族面）——文件 1、点 1」）：
  `moveCells.push_back((cell - occupiedCells[0]).round())` 替代
  `cell.rotated(rotation).round()`（旋转已由装配烘焙，内核 rotation 恒 0）。
  gd_core_py 孪生由 `tools/gd_to_py.py` 再生成（ChessPiece.py:63 同款，
  自动生成无手改）。
- py 镜像注明：gd_core_py/gd_core_items/Exclusive/Chess/ChessPiece.py 为
  生成器产物，随源侧 pass 同步，未手改。

### 验证数字

- 探针（ORACLE_FIGHTS_ROOT 语料只读，输出重定向 output/oracle/probe/fam_r1/）：
  修前 run645 gd ev=301 棋族 0；修后 idx4/5 = t0.9 Activation Chess Board +
  White Pawn Regeneration(2)——与神谕 idx4/5 逐位相同。
- 定向+全簇：`python -X utf8 tools/verify_oracle.py --cases
  run645_r11,run647_r10,run660_r18,run669_r10,run675_r18 --force`：
  首分歧 idx 4→7 / →309 / →17 / →33 / →21；**run647_r10 三方事件数
  393=393=393**（棋族段全对齐，idx309 残差=Badger Spirit 41v42，他族）。
  全簇尚无一场全对齐（见残留 1）。
- 退步检（按 mandate 口径先复跑基线全集再 check）：
  `tools/verify_oracle.py --cases <two_phase_base 118 场> --force` →
  **118/118 三方一致**；`tools/aligned_set.py check -b
  output/oracle/aligned_sets/two_phase_base.txt` → 基线 118→当前 118：
  **新增 0、退步 0（PASS）**。
- 清理：临时诊断脚本 gd_core_test/_famr1_diag.gd 已删；gdcore_diag 半成品
  探针产物已删。

### 残留与下轮入口

1. **簇未清零，共因已换层**：五代表场残差全部是「捕获哪枚棋子/是否捕获」的
   抉择分歧（run645 idx7 对手板首触发、run660 idx17、run669 idx33、
   run675 idx21）。机制面：原版 ChessBoard 的 shuffle 走**引擎全局链**
   （docs/rng_truth.md §1.4-2），gd_core_items 的 Array.shuffle 亦走引擎链
   （harness 已 seed(S)，激活序两抽已复刻），但 t>0 后全局链状态被原版
   headless 侧的额外全局抽（音效 pick_random/动画/UI 面）推偏——属
   rng-mechanism（689 场）族的「全局链台账」工程，非棋族数据缺口；
   py 腿结构上无引擎全局链（run675 gd-vs-py idx15 即此），需独立台账。
2. digest 顶部簇（Activation(0)×Chess Board×68）签名应已瓦解：下轮开头跑
   一次全量 `verify_oracle.py --force`（≈40min）刷新 alignment.json+
   digest，重新聚类取新最大簇。
3. run647 idx309（Badger Spirit 41v42）、run660/675 gd-vs-py 腿分歧归入
   对应族，勿在棋族内追。

### 红线自查

fights/** 冻结语料只读（诊断探针输出全部重定向 output/oracle/probe/fam_r1/；
--force 只删两侧重放产物）；未改 tools/verify_oracle.py 判定逻辑；无 git 写
操作；未触碰 Steam 目录；全程无头静音（--headless --audio-driver Dummy，
stdout/stderr 重定向文件，诊断复跑不带 --quiet）；改前态备份
output/_round_patches/fam_r1/（battle_items.json、gd_core_runtime.json、
item_battle_fixture.json、oracle_align_cases.json、build_item_scripts.py
+ chess_grid_truth.json 真值 + _make_prestate_backup.py 备份器）。

---

## 2026-10-11 · r1_1：獾灵治疗量 41v42 非事件化数值面（run647_r10：Health(12) origin=Badger Spirit）

### 场集合与基线

任务书定向单场 run647_r10（seed 5123606，Mage 镜像阵容，双方同 33 件）。
改前基线：`python -X utf8 tools/verify_oracle.py --cases run647_r10 --force
--alignment-out output/oracle/alignment_task_r1_1.json` → 0/1，
match=oracle≠gdcore（[rng-mechanism]），firstDivergence=**oracle_vs_gdcore
idx 309**：同位 Health(12) 事件 params.amount **oracle=41 / gd=42**
（idx≤308 canonical 全同；gd_py 当时一致 42）。

### 根因（仪器：ORACLE_HEALPROBE 打点复跑原版工程）

排除面（全部本轮实测）：heal 舍入 gd_core/CoreCharacter.gd:759-761 ↔
decompiled_full/Core/Character.gd:739-741 逐行同；giveMaxHealth
gd_core/CoreCharacter.gd:866-869 ↔ :876-879 同；getP_m/getParamModified
gd_core/CoreItem.gd:1190-1197 ↔ decompiled_full/Items/Item.gd:3922-3927 同；
BadgerSpirit/BookofBasics 脚本两侧逐行同；heal=20/maxhealth=20/
maxhealth_bonus=2 与 CSV（decompiled_full/Sheets/CSV/ItemData_e.csv:402 ≙
oracle/Sheets/CSV/ItemData.csv:402）及 assets/battle_items.json named_params
同；healingEfficiency 修改件全库仅 9 件均不在场（eff=1）；reduceMaxHealth
全库 0 调用（死码）；Puzzlebox/PuzzlebagS 只动 speed/buffChance。
**TemporaryMaxHealth(19) 事件 13 条两侧逐条同**（Piggybank 2×2、Basics 11、
Badger 22×2 每侧）→ t=9.833 玩家 temp=59、maxHealth=150 两侧一致——任务书
提示的「受影响件计数/battle_items.json grid/types 面」实测无差（+22=20+2×1
、+11、+2 逐条对上），分歧不在受影响件计数。

**决定性仪器**：oracle/ 工程拷贝至 output/_round_patches/r1_1/oracle_probe/
（冻结语料零改动），对拷贝件 Core/Character.gd 的
heal/changeMaxHealthTemporary/giveMaxHealth 加 ORACLE_HEALPROBE 打点，单场
复跑（ORACLE_ONLY_CASES=run647_r10 + ORACLE_FIGHTS_ROOT 重定向
output/oracle/probe/r1_1/）——复跑 events.json 与冻结语料 **原始字节逐字节
一致**（cmp 相等；lineups.json 仅 current_health 快照时点差 150/154），打点
证据有效：

```
[HEALPROBE] heal t=9.833333 amount_in=41 eff=1 maxH=150 tempH=59 curH=95 round=41
```

即**原版 Character.heal 入口收到的 amount 在 round 之前已是 41**。真因：
decompiled_full/Items/Item.gd:4826 `func heal(amount: int = getP_m("heal"),
triggerEvent = null)` 形参带 **int 类型**——GDScript 类型化形参在传参瞬间把
float 实参**截断**（41.8→41，向零取整，非 round；默认实参路径同样先求值再转
换）。BadgerSpirit.onDamaged（decompiled :17-18）传
(150+59)×20/100=41.8，经 Item.heal 入口已截成 41 → Character.heal(:739)
round(41×1)=41。gd_core/CoreItem.gd:2150 同名函数形参**无类型**（转写时丢
`: int`），41.8 直通 → round(41.8)=42。侧证：同场 Shiny Shell
heal(5+0×3)=5 整数无差；Regeneration/Vampirism 治疗走 Character.heal 不经
Item.heal 不受影响。

### 修复（改前态备份 output/_round_patches/r1_1/_prestate/）

- **gd_core/CoreItem.gd heal()**（对齐 Item.gd:4826）：入口补
  `amount = int(amount)`——等价原版类型化形参语义（显式 float 实参、默认
  实参 getP_m("heal") 两路都经转换；int() 向零截断同 GDScript 类型转换）。
  diff：output/_round_patches/r1_1/CoreItem_heal_int_trunc.diff。
- 数据面零改动：assets/battle_items.json 与 CSV 逐参相等，不需改（备份同
  存于 _prestate/）；gd_core/CoreCharacter.gd 零改动（备份即证）。
- **py 镜像注明**：gd_core_py/gd_core/CoreItem.py 的 heal() 需同款入口截断
  （`amount = int(amount)`）——该文件在本次任务禁碰清单外，未改；修后
  gd_py 腿在 idx309 分歧（py=42 vs gd=41），待 py 属主/下轮 gd_to_py 同步
  后自愈。

### 验证数字

- 定向（同一命令、--force）：修后 **match=gdcore≡oracle 但 py 分歧**
  （[gd_core_py-transpiler]）；judgement oracle_gd：event_tuples=true 且
  rendered_lines=true（主辅判据双过）；残差对=gdcore_vs_py idx309（41v42，
  py 未同步所致）。
- 对照修复前：oracle_vs_gdcore 首分歧 **idx 309 → 全对齐（消除）**，
  未前移，无退步。
- 退步面说明：gd_py 对从「全同(42=42)」变「idx309 分歧(41v42)」是 py 镜像
  未同步的预期结果（本次修复把 gd 拉向真值 41），非 gd 侧退步。
- 结构性无回归论证：int 截断只改变**非整数** heal 入参（小数入参下
  round(x)≠int(x) 恒分叉，故此前任何对齐场不可能含非整数 Item.heal 入参）；
  整数入参路径零变化。全量回归本轮未跑（定向任务口径）。

### 红线自查

fights/** 冻结语料只读未动（mtime Oct 7/8 未变）；--force 只删两侧重放产物；
未改 tools/verify_oracle.py 判定逻辑；无 git 写操作；未触碰 Steam 目录；
探针拷贝（571MB）用后即删，打点证据 log 留
output/_round_patches/r1_1/_r1_1_oracle_probe.log、仪器 diff 留
output/_round_patches/r1_1/oracle_probe_instrument.diff、复跑重放留
output/oracle/probe/r1_1/（337K）；全程无头静音（--headless --audio-driver
Dummy，stdout/stderr 重定向文件）；禁碰清单外文件零改动（gd_core_items/
、gd_core_py/、decompiled_full/、oracle/、tools/ 均未写）。

---

## 2026-10-11 · r1_0：棋局 shuffle 全局链台账（run645_r11：src:regen 捕获抉择分歧）

### 场集合与基线

任务书定向单场 run645_r11（seed 5107768，Ranger 镜像阵容，双方同 44 件，含
Chess Board×2 + 棋子各 7）。改前基线：`python -X utf8 tools/verify_oracle.py
--cases run645_r11 --force --alignment-out
output/oracle/alignment_task_r1_0_baseline.json` → 0/1，match=oracle≠gdcore
（[rng-mechanism]），firstDivergence=**oracle_vs_gdcore idx 7**：oracle t60
玩家 heal(2)（regen tick）vs gd t56 对手白兵 Regeneration(2)——即 fam_r1
残留 1「gd 侧 t56 多出对手白兵 +2 恢复事件」。py 腿改前 ≡ gd（308=308）。

### 根因（两层，逐层剥出）

1. **全局链消耗面缺位（台账层，本轮修复面）**：原版 t>0 的引擎全局链
   （Math::rand，docs/rng_truth.md §1.4-1/2，与 Util.rng 独立）战斗期消耗 =
   棋盘 4 处 shuffle（decompiled_full/Items/Exclusive/ChessBoard.gd:80/100/
   121/164）+ 每次棋子捕获的 captureSounds.pick_random（Chess/ChessPiece.gd:74，
   与 Util.randPitch 同行、GDScript 实参左→右求值）。受控对齐只复刻了开局
   shuffle×2（oracle_fight.gd:645/648 ↔ OracleAlignBattle.gd::activation_order，
   43+43=86 抽）；gd_core_items 的 a1 声音面 pass 只还原了 randPitch 的
   Util.rng 抽、pick_random 明注「不计 ctx.rng」而**零消耗**——原版每次捕获
   多 1 抽全局链，gd 侧链位恒落后 1。逐抽验证：ORACLE_ALIGN_TRACE 台账行
   （Gopen/Gshuffle/Gpick）+ py PCG32(S) 复算——开局 86 抽后玩家板洗牌
   (2503770676,1197714042)→[兵,象,兵]（双方一致），+1 pick_random 抽后
   对手板 (370236238,2508736025)→**[象,兵,兵]**（象先查=静默捕获=无事件）；
   gd 缺这 1 抽 → (2681991436,370236238)→[兵,象,兵]（兵先查=白兵捕获=多出
   regen 事件）→ idx7。逐抽逐位闭环（X=0,Y=1 唯一解与本场事件面吻合）。
2. **台账流播种位踩坑（中途发现并修正）**：首版 globalChainOpen 读
   `rng.seed` 播种——引擎 RandomPCG.rand() 每抽覆写 current_seed=前置态
   （output/godot_src/random_pcg.h:83-86）、set_state 直灌不回写（:79），
   战斗期读到的是装配期最后一抽前置态 → 台账流整条错位（且本场后续棋盘
   抉择恰为洗牌不敏感，场面与基线逐字节相同、极易误判为「已修」）。修正 =
   CoreRng._init 存 `battle_seed`，开账用它播种。修正后与 py PCG32(S) 逐位
   对表通过（output/r1_0_probe/SeqProbe.gd：gd 序列≡py 序列≡引擎全局链，
   RandomNumberGenerator(seed).randi() ≡ 全局 randi() 8 抽逐位一致）。

### 修复（改前态备份 output/_round_patches/r1_0/）

- **gd_core/CoreRng.gd**：新增引擎全局链台账区——`global_chain`（台账流
  RandomNumberGenerator）+ `battle_seed`（_init 暂存战斗 seed）+
  `globalChainOpen(n_player, n_opponent)`（重播开局 shuffle×2 的 (n-1)+(n-1)
  抽，使台账流 ≡ 引擎链同链位）+ `shuffleEngine(array, tag)`（**反向**
  Fisher-Yates，i 从 n-1 降到 1、j=rand()%(i+1)、交换 i/j——Godot
  Array.shuffle 实测模式，output/r1_0_probe/ShuffleProbe.gd 逐位验证；
  未开账直通 array.shuffle() 零回归）+ `pickRandomEngine(array, tag)`
  （array[randi()%size]，1 抽，返回被选元素；未开账直通 pick_random）+
  `_draw_signature`（台账行抽值列，诊断）。台账行在 oracle_trace 开启时并入
  oracle_trace_log（kind=Gopen/Gshuffle/Gpick，列构同 rng_log），Util.rng 与
  全局链一张台账逐抽对位。
- **gd_core/CoreCombat.gd**：startBattle preordered 分支开账
  `ctx.rng.globalChainOpen(player_items.size(), opponent_items.size())`
  （开局直通法 :145-162 在 t>0 的同构推广）。
- **tools/build_item_scripts.py**：新增 pass `adapt_global_chain_ledger`——
  物品脚本裸 `X.shuffle()`→`ctx.rng.shuffleEngine(X, "decomp文件:行")`、
  裸 `X.pick_random()`→`ctx.rng.pickRandomEngine(...)`（tag=decomp 1 基行号，
  供与 oracle 侧逐点对位；现存 12 shuffle + 1 pick_random 调用点全数核对在
  保留函数内）；报告行「全局链台账改道（r1_0 棋局 shuffle 面）——文件 8、
  shuffle 11、pick_random 1」。同轮扩展 a1 randpitch pass：head 含 pick_random
  的位点（仅 ChessPiece.gd:74）在 randPitch 之前补
  `ctx.rng.pickRandomEngine([null,null,null], "...:74")`（3 元占位与原版
  captureSounds 等长；pick_random 恒 1 抽与长度无关，数值无消费方）。
- **生成态同步**：`python tools/build_item_scripts.py` 重生成 gd_core_items
  （diff 对照改前备份 = 恰 8 文件 14 处：ChessBoard×4、Eggscalibur、
  CupcakeDragon、EchoingBattlecry、RainbowPotion、TeslaCoil×2、Ukulele、
  UnidentifiedSkill + ChessPiece 音抽行）；`python tools/gd_to_py.py` 重生成
  gd_core_py（CoreRng.py/CoreCombat.py + 同 10 个物品孪生，自动生成无手改，
  py 腿独立台账 = 同名 global_chain 成员流，未开账路径照旧走 _rt
  _shuffle/_pick_random）。

### 验证数字

- 定向：`python -X utf8 tools/verify_oracle.py --cases run645_r11 --force
  --alignment-out output/oracle/alignment_task_r1_0.json` → match=
  **oracle≠gdcore**，firstDivergence **idx 7 → idx 15**（后移 ✓）；gd 事件
  308→255、py 255=255 **gd≡py 恢复且保持**（judgement gd_py 双判据 true）。
  idx15 = 新一层：oracle t1.7833 玩家板（黑方回合）捕获 (4,2) 白兵
  （Activation+BlackPawn mana3+WhitePawn lucky1），gd 无事件——**repositionPiece
  移位缺口**：decomp Chess/ChessPiece.gd:93-97 `repositionPiece` 含判定面
  `inventory.moveItem(self,[toCell])`，转译期整函数按视觉剥离 → 捕获者不占
  被吃格 → 黑方查 (4,2) 恒空 → 转 findSpaceToMove。修复需 CoreGrid.moveItem
  （内核网格方法在内核，**不在本轮独占文件清单**）→ 留下轮入口。
- 台账行实测（output/r1_0_probe/align_gd/run645_r11/rng_trace.txt，经
  ORACLE_ALIGN_TRACE=1）：Gopen burn=86 → 板1 :80(3)/:100(2)/Gpick → 板2
  :80(3) 首查象（修后 n=20 象格洗牌，修前 n=2 兵格）——消耗面与原版同链位。
- 退步检（场集合）：run645_r11 首分歧 7→15 严格后移 ✓（回滚条件不触发）。
- 已对齐场抽查（two_phase_base 118 场中含本轮改道物品的 6 场）：
  `--cases run1044_r11,run1077_r18,run1119_r6,run575_r18,run760_r11,run973_r6
  --force` → **5/6 三方一致**；run1077_r18（Ukulele）idx109 分歧经 A/B 实证
  **非本轮回归**：改前/改后 gd 事件流逐事件全等（2189=2189，
  output/r1_0_probe/ab_base/），分歧来自并行轮 tree 演化，非棋局台账面
  （该场不含 Chess Board，台账流与引擎链同构等价）。其余 112 场不含改道
  物品（lineups 快照逐一核对），未开账路径直通 Array 方法零改动。
- 确定性自证：harness selfcheck 同种子复跑逐字节一致 ✓（3 轮 verify 均 PASS）。

### 残留与下轮入口

1. **repositionPiece 移位缺口（idx15）**：ChessPiece.onStateChanged Vector2
   分支缺 `inventory.moveItem(self,[targetCell])`（decomp :93-97 判定面被
   视觉剥离连带）。修复面 = CoreGrid.moveItem（内核网格）+ ChessPiece pass
   （build_item_scripts.py）+ gd_core_py 同步——CoreGrid.gd 不在本轮独占
   清单，未动。
2. 台账消耗面其余缺位（689 场 rng-mechanism 族）：Character.gd:326 战怒
   battleRageItems.pick_random 原版走全局链、内核 CoreCharacter.gd 走
   ctx.rng（链错位，CoreCharacter.gd 非本轮清单）；Util.sortDict
   shuffleBeforeSort（Item.gd:5642 getStackFraction）同理（CoreUtil.gd）。
   二者均已具台账改道落点（pickRandomEngine），待对应文件轮次接入。
3. run645_r11 后续若在 repositionPiece 修复后仍残分歧，沿棋盘 tick 逐抽
   台账行对位（Gshuffle 抽值列已可逐位对表）。

### 红线自查

fights/** 冻结语料只读（--force 只删两侧重放产物）；诊断探针输出重定向
output/r1_0_probe/（ShuffleProbe/ShuffleProbe2/SeqProbe + 台账 trace +
A/B 留档）；未改 tools/verify_oracle.py、tools/gd_to_py.py、
gd_core_test/OracleAlignBattle.gd、oracle/** 判定逻辑（gd_to_py.py 与
OracleAlignBattle.gd 仅运行未写）；Smoke.gd 零改动；无 git 写操作；未触碰
Steam 目录；全程无头（--headless，stdout/stderr 重定向文件）。改动面全部
在独占清单内（gd_core/CoreRng.gd、gd_core/CoreCombat.gd、
gd_core_items/Exclusive/ChessBoard.gd、gd_core_items/Exclusive/Chess/
ChessPiece.gd、tools/build_item_scripts.py）+ 生成态（gd_core_items、
gd_core_py）随源侧 pass/转写器同步，改前态备份 output/_round_patches/r1_0/
（6 独占文件 + gd_core_py 孪生 + _gd_core_items_before/_gd_core_py_before
全量 + _postfix_hold 中间态 + 基线/验证日志）。

## 2026-10-11 · r2_2：Resistor 充能-Heat 送达面（×39=27+12 同根因簇合并：collisionMapPosition 全工程零写入，电荷 cell1 落点错位一 40px 单位）

### 场集合与基线

任务书定向 6 场（27 簇 idx≤2：run705_r7/run1101_r18/run1103_r18/run1107_r18；
12 簇 idx>2：run1105_r18/run1160_r18）。改前基线：
`python -X utf8 tools/verify_oracle.py --cases run705_r7,run1101_r18,run1103_r18,run1105_r18,run1107_r18,run1160_r18 --force --alignment-out output/oracle/alignment_task_r2_2_baseline.json`
→ 0/6，oracle_vs_gdcore 首分歧 **idx 1/1/1/3/1/3**，同签名：oracle t0
Battery Activation 后立即 `Resistor Heat(107,amount=3)` 入栈，gd 缺失
（Battery/Piggybank/Cog 等其余 t0 事件照常）。

### 根因（排除面 + tscn 实证 + 6 场几何对照）

排除面：Resistor.gd 两侧逐行同（decompiled_full/Items/Exclusive/Resistor.gd
↔ gd_core_items/Exclusive/Resistor.gd，onChargeReceived→giveHeat(heat)+
miniActivate）；Battery.gd 两侧逐行同；`hasOnChargeReceivedEffect =
has_method("onChargeReceived")` 在 `_readyInit`（CoreItem.gd:785）对直挂
物品脚本为真（gd_core_items/Item.gd 适配层 extends CoreItem，物品脚本多态
可见）；chargeReceived→_behavior_call 回落链（SELF_BEHAVIOR_METHODS 含
onChargeReceived，CoreItem.gd:160）通；giveHeat（CoreItem.gd:1345）→
giveStacks 正常发 107；CoreHooks.gd:197 sendCharge 钩子为纯表现 pass、
不在判定面（**本轮零改动**）。

真因：**`collisionMapPosition`（CoreItem.gd:56）声明后全工程无一处赋值**——
grep gd_core/ gd_core_items/ gd_core_test/ 零写入点，恒 `Vector2.ZERO`。
该字段是原版物品场景里 CollisionMap 子节点的 position，参与
ElectricalCharge.start（decompiled_full/Items/ElectricalCharge.gd:141-142）
`getGlobalPointsForCells`（Item.gd:1040-1047）与
`Inventory.getCellsForGlobalPositions`（Inventory.gd:377-381）的两步互逆；
内核 `_chargeInventoryCells`（CoreItem.gd，修复前 :2062）按
`top_left + floor(R_fd(80*cell + cmPos + (40,40))/80)` 折叠，cmPos 缺失即
整体错位一 40px 单位——与旋转无关，**fd=0 同样错**（run1103_r18 实证）。
7 个电荷发射器（全工程仅 7 处 sendCharge 调用方，grep 封口）的 tscn 实测：

- Battery.tscn / ChargeSplitter.tscn / CogBadge.tscn = Vector2(40, 40)
- Generator.tscn = (40, 0)；LightningStaff.tscn = (-40, 0)
- ManaCrystal.tscn = (-40, -40)；Con-Trap-Tron.tscn = (40, -20)

决定性对照（用 output/oracle/fights/*/lineups.json 全量几何 + events.json
t0 序列逐场验算 cell1 落点）：补 cmPos 后 6 场全部与神谕逐位吻合，含反例格
（Battery/Coil/Charge Splitter/Spin to Win 收电荷→无 heat）：run705_r7
Battery(0,2)fd1 cell1 修后 (1,2)=Resistor ✓ / 修前 (1,1)=Cog ✗；
run1101_r18 (8,2)fd3 → (7,2)=Resistor ✓ / 修前 (6,2)=Coil ✗；
run1103_r18 (6,5)fd0 → (6,4)=Resistor ✓ / 修前 (5,3) ✗；
run1105_r18 两 Battery(7,0)(7,1)fd3 → (6,0)(6,1)=Resistor ✓ / 修前 ✗✗；
run1107_r18 四 Battery 中 (7,0)→(6,0)=Resistor ✓、(8,1)→(7,1)=Resistor ✓、
(8,2)→(7,2)=Battery（无 heat，与神谕同）✓、(7,2)→(6,2)=Coil（无 heat）✓；
run1160_r18 九 Battery 逐台验算含 (1,4)→(2,4)、(1,5)→(2,5)、(1,6)→(2,6)
Resistor ✓、其余反例格 ✓。任务书提示的 run1160_r18「电荷 4 抽 Util.rng
消耗已在位」核实：sendCharge 的 randf_range×2+randPitch×2（修复后
CoreItem.gd:2067-2068）与 Zap 抽（_chargeEnterCell 内 randf_range(4.0,4.02)）
均在位，非本根因。

### 修复（gd_core/CoreItem.gd，独占清单内）

1. 新增 `const CHARGE_EMITTER_CM_POSITION`（7 发射器 tscn 实测值，键=描述符
   name，注意 "Cog Badge" 带空格、"Con-Trap-Tron" 带连字符）；
2. `setup()` 在 `name = _descriptor.name` 后查表写入 `collisionMapPosition`
   （装配期一次性，先于战斗期任何 sendCharge）；
3. 字段声明处与 `_chargeInventoryCells` 注释同步改真（原注释宣称「由各物品
   脚本 _readyInit 写入」从未发生——即缺陷本体）。
diff 存档：output/_round_patches/r2_2/CoreItem_cmpos_charge_delivery.diff；
改前态：output/_round_patches/r2_2/_prestate/{CoreItem,CoreHooks}.gd。
Godot 静态校验：`--check-only --script res://gd_core/CoreItem.gd` 退出码 0。

**py 镜像注明（未动，禁碰清单外）**：gd_core_py/gd_core/CoreItem.py 需同步
同表同写——:66 `self.collisionMapPosition = Vector2.ZERO`（字段）、:289
`setup`（写入点）、:2158-2163 `_chargeInventoryCells`（消费点）。修后
gdcore_vs_py pair 在 6 场全分歧（py 腿仍缺 Resistor heat），属预期；
py 转写任务落地后自愈。基线里 run705/run1101 的 gdcore_vs_py 分歧
（idx29/idx61，Stone/Lightning Staff 数值面）为既有独立缺口，与本根因无关。

### 验证数字

- 定向：`python -X utf8 tools/verify_oracle.py --cases run705_r7,run1101_r18,
  run1103_r18,run1105_r18,run1107_r18,run1160_r18 --force --alignment-out
  output/oracle/alignment_task_r2_2.json` → gd 重放 6/6 ok（无 SCRIPT
  ERROR，selfcheck 同种子逐字节一致），oracle_vs_gdcore 首分歧：
  **run705_r7 1→35、run1101_r18 1→137、run1103_r18 1→2、run1105_r18 3→163、
  run1107_r18 1→162、run1160_r18 3→156 —— 6/6 严格后移，无回退**。
  t0 段逐位核对：6 场 Resistor Heat(107,amount=3) 全部按神谕位次入栈。
- 新一层分歧（均后移出本根因簇，属后续轮入口）：run705 idx35 Stone 伤害
  （oracle t289 damage4 vs gd t293 Seal the Deal 激活错位）；run1101 idx137
  Coil amount -2（oracle 105 vs gd Lightning Staff 伤害流）；run1103 idx2
  Cog Block 15v10（`getNumAffectedItems` 邻接受影响格计数差——数据/装配面，
  非电荷面，基线被 idx1 遮挡的非本轮引入项）；run1105 idx163 / run1107
  idx162 Coil Heat -1；run1160 idx156 Battery 激活 actor player/opponent 错位。
- 过程留痕（如实）：修复后首次 verify 成功写入
  alignment_task_r2_2.json，随后一次 cp 误用 baseline 覆盖了它；因 gd/py
  重放产物未删，用 `--compare-only` 重比对原样恢复（比对为确定性纯函数，
  输出与 --force 全跑一致）。
- 退步检（场集合）：6/6 首分歧严格后移，回滚条件不触发。
- 影响面备注：本修复作用于全部 7 发射器（任何含其阵容的场），其余轮次的
  电荷场首分歧预计同步后移；本轮未跑全量（任务书口径=定向场集合）。

### 红线自查

改动面仅 gd_core/CoreItem.gd（独占清单内；CoreHooks.gd 验明无需改动）；
gd_core_py/gd_core_items/tools/oracle/gd_core_test 全部未写（py 镜像以本节
注明代行）；fights/** 冻结语料只读（--force 只删两侧重放产物）；探针为
一次性内联几何验算（读 lineups/events/tscn，零落盘脚本）；备份/diff/基线
JSON 齐备于 output/_round_patches/r2_2/；无 git 写操作；全程无头。

## 2026-10-11 · r2_0：Pine Protector 格挡-Spikes 入栈面（×65，type=104 origin=Pine Protector）——CSV 逗号格合并具名参数（数据层，escalate 授权扩面修复）

### 任务与场集合

- 任务书：Pine Protector 格挡-Spikes 入栈面；独占 gd_core/CoreCharacter.gd、
  CoreBuff.gd、CoreRng.gd；验证命令 `python -X utf8 tools/verify_oracle.py
  --cases run808_r12,run809_r12,run810_r12,run811_r18,run815_r13 --force
  --alignment-out output/oracle/alignment_task_r2_0.json`。
- 备份：output/_round_patches/r2_0/_prestate/{CoreCharacter,CoreBuff,CoreRng}.{gd,py}
  （6 份；三独占文件本轮**零改动**，备份为回退保险）。

### 基线（修复前）

5/5 场 oracle≠gdcore，首分歧 idx：run808_r12=32、run809_r12=24、run810_r12=21、
run811_r18=90、run815_r13=10；localization 全归 rng-mechanism。
过程留痕：首轮 --force 后 py 侧全 skip（并行任务覆写共享夹具
gd_core_test/oracle_align_cases.json 的竞态——gd 重放读了本任务 5 场、py
重放读到并行任务的 6 场）；不带 --force 重跑补齐 py 产物后比对正常。

### 根因（实证链，非任务书预判的两条）

任务书两条假设（pre_take_damage→rollChance/chanceRng 私有流时序；
giveSpikes→gainStacks 入栈面）均被证据否定：

1. **格挡面两侧全等**：5 场首分歧位上 gd 的伤害值与 oracle 全同
   （run808 idx32 damage=0、run810 idx21 damage=5、run815 idx10 damage=0），
   drainStamina/activation 事件齐全——block roll、damblock 减伤、chanceRng
   时序无分歧；若为概率流漂移，不可能 5 场共 ~200 次 PP 格挡全部 0 spikes。
2. **入栈面根本未被到达**：SpikedShield.beforeBlock 的
   `maxSpikes = getP("maxspikes") + getP("maxspikes_food")*N` 双双取 0 →
   `spikesLeft=0` 恒 gate → giveSpikes 从未调用（脚本两侧逐行同，与任务书一致）。
3. **真根因＝数据层 CSV 逗号格合并**：原版 ItemBook.gd:858-868 对含逗号的
   p1..p10 单元格按 "," 拆成多个「值:名」具名参数；battle_items.json 生产链
   只按 ":" 切一次，整格压成垃圾键。实测（python 内联
   `CoreItemData().fromDict(assets/gd_core_runtime.json...)`）：
   namedParams 键 `"maxspikes,1:maxspikes_food":5.0` → getP("maxspikes")=0.0、
   getP("maxspikes_food")=0.0、hasParam("maxspikes")=False。oracle 语义下
   maxSpikes=5+1×N（N=受影响 Food 数）。
   **同类受损共 3 件 11 键**：Pine Protector（1 键）、Magic Ring（5 键）、
   Superior Ring（5 键）。
4. **症状全解释**：oracle PP spikes=9/18/24/28/18（恰被 blocks 截断），gd/py=0；
   缺每次入栈的 getNextFreeLabelPosition 2 抽表现层链消耗 → RNG 流错位 →
   run808 idx36 Cheese Goobert 随机 buff 变形（oracle Empower+Spikes vs
   gd Lucky+Mana，pickRandomStacksToGive 为 RNG 面）。

### 修复（escalate 授权扩面：数据层+生成器）

- 新增 `tools/enrich_split_params.py`（模式照 enrich_stack_flags.py）：把合并键
  逆向还原成 CSV 单元格（值+":"+键，恰为生产链的逆）、按 ItemBook.gd:858-868
  拆回独立具名参数原位写回，**逐格与 decompiled_full/Sheets/CSV/ItemData_e.csv
  （csv 模块完整解析）对账，不符即中止不写库**；幂等（复跑 --check 0 键）。
- 执行：3 件 11 键拆分，battle_items.json 我的净差 +30/-11 行（对照写库前
  .bak_20261011_023605 diff，无重排版）。
- 重生成：`python tools/gen_gd_core_data.py`（assets/gd_core_runtime.json，单行
  JSON 整文件 1 行差）+ `python tools/gen_lineup_fixture.py`
  （gd_core_test/item_battle_fixture.json 1 行差；LineupFixture.gd 339+/21- 为
  **生成器陈旧差异**——现生成器的 randomUniquePool/gainedStacks 等字段在
  库内版本缺失，重生成补齐为缺省值，53 件 truth 阵容不含 3 修复物品，
  对语义零影响）。
- **py 镜像注明（未动，禁手改）**：py 侧经 simulator/gd_core_engine.py:96
  `CoreItemData.fromDict` 直读重生成后的 gd_core_runtime.json，零代码改动即
  同步生效（py 重放实测 PP spikes=9/18/24/28/18 与 oracle/gd 三方全同）。
  gd_core/CoreItemData.gd fromDict 亦无需改（单真值源=数据，收键即真值）。
- **三个独占文件零改动**：CoreCharacter/CoreBuff/CoreRng 的给刺链与栈面代码
  两侧本就全等，无需也不应在其内做数据补偿。

### 验证数字

- 定向：`python -X utf8 tools/verify_oracle.py --cases run808_r12,run809_r12,
  run810_r12,run811_r18,run815_r13 --force --alignment-out
  output/oracle/alignment_task_r2_0.json` → gd 5/5 ok（selfcheck 同种子一致）、
  py 5/5，**三方一致 3/5（基线 0/5）**。
- 首分歧对照（后移=通过）：run808_r12 32→None（全对齐）、run809_r12 24→None、
  run815_r13 10→None、run810_r12 21→194、run811_r18 90→90——**无一场前移，
  回滚条件不触发**。
- 本任务面收口：PP Spikes(104) 事件数三方全同（9/18/24/28/18）。

### 新一层分歧（均后移出本根因簇，属后续轮入口，非本轮引入）

- run811_r18 idx90：PP heal 18 vs 17，**已界定根因**——
  gd_core/CoreItem.gd:2188 `amount = int(amount)` 为内核自加的截断，原版
  Item.gd:4826 `func heal(amount: int = getP_m("heal"))` 的 float 实参**不截断**
  直通（oracle 全程序列 17,17,18×18,19×16,20…28 与
  round(getP_m×healingEfficiency) 逐段吻合，gd/py 的
  round(int(getP_m)×eff) 系统性 -1~+1 错位；探针
  output/_round_patches/r2_0/_probe_run811_heal.py 实测 eff=2.08、base=8、
  mult 1.0/1.07/1.14 三段)。修法=删该行截断（gd_core/CoreItem.gd 归属项
  + gd_core_py 转写重生成），**不在本任务独占清单内，移交**。
- run810_r12 idx194：Eggscalibur Mana(105,-11,used) / Blueberries Mana(+1) vs
  Carrot activation 错位（蛋系法力消耗/食物面，run810 阵容无 Paradise Birb
  与双 Ring，与上述两根因无关）。

### 红线自查

改动面＝tools/enrich_split_params.py（新增）+ battle_items.json（工具写入，
禁手改约束遵守）+ 两数据产物重生成 + 共享夹具 oracle_align_cases.json（工具
口径内重写，5 场）；gd_core 三独占文件与 gd_core_py 全部零写入；fights/**
冻结语料只读（--force 只删两侧重放产物）；一次性探针置于
output/_round_patches/r2_0/（零仓库源码落盘）；无 git 写操作；全程无头。

## 2026-10-11 · 工作流轮 r2_1：Falcon Blade DealDamage 伤害值面（×44）——第 24 轮 3 抽修复丢失事故重施 + 生成器固化

### 定靶（任务书面板）

- `python -X utf8 tools/verify_oracle.py --cases run631_r9,run637_r18,run639_r18,run701_r11,run722_r7 --force --alignment-out output/oracle/alignment_task_r2_1.json`
  → 修复前基线（存档 output/_round_patches/r2_1/alignment/baseline_alignment_task_r2_1.json）：
  三方一致 **0/5**；首分歧 run631_r9 idx78（t=1.18 对手 Falcon Blade DealDamage
  **oracle damage=0 vs gd=8**）、run701_r11 idx120（5 vs 4）、run722_r7 idx56（5 vs 4）、
  run637_r18 idx107（2 vs 3）、run639_r18 idx115。
- 任务书假设「oracle 侧减伤/格挡把伤害折零而 gd 直通」——**证伪**：Shield/WoodenBuckler/
  HeroShield/CoreDamageResult.applyDamageReduction（gd_core/CoreDamageResult.gd:55）与
  decompiled_full 逐行同；格挡 roll 差是**下游后果**非根因。

### 定位链（ORACLE_DEBUG 重放 + 归一流值 u=(v-lo)/(hi-lo) 逐抽对位）

- 神谕侧重放自证：probe_r2_1 重跑 run631_r9 events 与冻结语料逐字节同（1626 事件），
  rng_log 6656 行；gd 侧 ORACLE_ALIGN_TRACE=1 取 rng_trace（独立目录
  output/oracle/probe_r2_1/，冻结语料只读）。
- 逐事件段对位（事件行 1:1，1626=1626 全同型）：run631_r9 首分歧段——
  oracle 在**玩家 FB doCooldownEffect 尾**（tick68，双击判定 + activate→Twine 触发链
  之后）多 3 抽 `randf_range(-30,30)/(-100,100)/(-5,5)`，gd 缺失；下一 FB cycle 的
  cooldown jitter 起两侧把**同一 PCG 输出**指派给不同调用点（oracle row407
  u=.9622687@(-30,30) vs gd row407 u=.9622667@(0.975,1.05) 同源）→ 对手 FB 伤害
  roll 7 vs 8、玩家 HeroShield 格挡 roll 0.271(≤0.3 格挡→伤害折 0) vs
  0.623(>0.3 不格挡→直通 8)。
- 同签名复现：run701_r11（u 分歧 row722，oracle (-30,-100,-5) 三连 vs gd jitter）、
  run722_r7（row340 同）。三场首分歧全部钉在同一缺位。
- **根因**：decompiled_full/Items/FalconBlade.gd:24-25 doCooldownEffect 尾部
  `var ani = createAnimation(); ani.randomizePosition()`——剥离时当纯视觉删除，但
  oracle/Items/Animations/ItemAnimation.gd:26-28 randomizePosition 恒耗全局链 3 抽
  （export 默认 positionRandom=(30,100)/angleRandom=5.0；FB 直调 randomizePosition
  不经 intialize → 无 playback_speed 第 4 抽）。

### 事故记录（本轮定位时发现，承 A2 节「互清事故」）

- 台账 2026-10-10 第 24 轮已修过**同一根因**（run634 idx152→367 闭合），修复只落在
  工作树、**从未入 git**（`git log --all -S "randf_range( - 30.0, 30.0)" -- 
  gd_core_items/FalconBlade.gd` 零命中）；现工作树 = HEAD 态 = 修复前
  （备份 output/_round_patches/round2/items/FalconBlade.gd 与现文件 diff=0，py 同）。
  期间 A2 终态（18:10 grep 自证「三处 3 抽 gd+py 全在」）之后又被管线再生成清掉
  （同轮查 RubyChonk 3 抽与 7 件 collisionMapPosition 亦全缺）——手补 × 生成物
  结构性互斥第三次实证。
- 授权记录：根因文件不在本轮任何任务清单内（无主文件），升级请示后获准重施修复
  并以生成器 pass 固化（治本）。

### 修复（4 文件；独占三文件零改动）

1. `gd_core_items/FalconBlade.gd` doCooldownEffect 判定块后补 3 抽
   `ctx.rng.randf_range(-30/-100/-5)` + decomp 行号注释（与第 24 轮同位同值）。
2. `gd_core_py/gd_core_items/FalconBlade.py` py 镜像手补（文件头已注明
   tools/gd_to_py.py 自动生成；手改可接受、本次注明）。
3. `tools/build_item_scripts.py` 新增 `restore_falconblade_randomize_draws(rel, text)`
   生成器 pass（r2_1）：写盘链中随 restore_randpitch_draws 后调用；幂等
   （检测任一抽行即跳过，手补/再生不双插）；报告行
   「FalconBlade randomizePosition 3 抽还原（r2_1）——注入 N、已在位跳过 M」。
   **治本**：此后 stage0 再生成自动含 3 抽，手补丢失面闭合。
4. 备份：output/_round_patches/r2_1/（items/FalconBlade.gd、py/FalconBlade.py、
   tools/build_item_scripts.py 修复前副本 + 基线 alignment JSON）。

### 存活性验证（替代方案说明）

- **未跑真实 `tools/run_gd_core.py`**：A2 节已证 stage0 全量再生成会清 item 树全部
  手补，而当前工作树 item 面有大量并行任务未提交修复（Eggscalibur、Exclusive/ 20+ 文件
  M 态）——真实重跑会清**他人**在途工作，结构性禁止。改用等价隔离验证：
  进程内 monkeypatch OUT=临时目录跑 `build_item_scripts.main()` 全量转译 502 文件
  → 临时 FalconBlade.gd 含 3 抽且与手补文件**逐代码行一致**；
  gd_to_py.main() 同法转写 → 临时 FalconBlade.py 含 3 抽（括号内空格 ` - 30.0`
  与手补一致）。修复在 stage0/转写再生成下的存活性成立。
- 单元：注入/幂等/手补识别/非目标文件 no-op 四断言全过；py_compile 两文件过；
  `--dry-run` 全管线无错。

### 验证数字

- 定向 5 场（同基线命令 --force）：**三方一致 2/5（基线 0/5）**；
  run701_r11、run722_r7 **全对齐（None）**；
  run631_r9 gd 侧 **1626 事件 ≡ 神谕**（基线 1530 缺 96），仅 py 腿分歧。
- 首分歧对照（后移=通过）：run631_r9 78→169（py 腿）、run637_r18 107→502、
  run639_r18 115→587、run701/722 →None——**无一场前移，回滚条件不触发**。
- 退步检（round3 基线集 run798_r18/run1195_r17/run1405_r17 --force，独立
  alignment-out=output/oracle/alignment_task_r2_1_round3check.json）：**3/3 三方一致**，
  基线集零退步（较第 24 轮「3 基线+1 新增」持平偏好）。
- 事件级佐证：oracle DealDamage(1) 事件数 196 vs gd 修复前 154（差 42 ≈ 21 cycle×2 FB）
  与「每 doCooldownEffect 丢 3 抽」量纲吻合；修复后 gd 侧 run631 全对齐。

### 新一层分歧（均后移出本根因簇，属后续轮入口，非本轮引入）

- run631_r9 idx169（py 腿）：gd≡oracle 后，py 缺 **Resistor 对 CogBadge 激活的
  Heat(3) 响应事件**（t=220，「获得3层狂热（电阻）」）——即第 24 轮已记残面
  「Resistor Heat 响应链」现以 py 转写层形态浮出（gd_core_py/gd_core_items/
  Exclusive/Resistor.py 逻辑与 .gd 全同，缺口在 charge/heat 信号接线或
  miniActivate/giveHeat 转写面）；F6 py 转写层独立面，非本任务面。
- run637_r18 idx502：冷却/速度掷点 tick 级分叉（oracle t=345 vs gd t=346）——
  round22 深水面。
- run639_r18 idx587：Light Goobert Blind timeout vs Jynx 激活错位——非本根因。

### 红线自查

改动面＝gd_core_items/FalconBlade.gd + gd_core_py/gd_core_items/FalconBlade.py
（升级授权的无主根因文件）+ tools/build_item_scripts.py（生成器 pass，治本）+
共享夹具 oracle_align_cases.json（工具口径内重写）+ gd_core 三独占文件
（CoreCombat/CoreDamageResult/CoreDamageSource）**零写入**；fights/** 冻结语料
只读（--force 只删两侧重放产物）；诊断产物全部落 output/_round_patches/r2_1/ 与
output/oracle/probe_r2_1/；无 git 写操作；全程无头。

## 2026-10-11 · r3_0：Pine Protector 命中链栈事件位次面（×60，type=104 origin=Pine Protector；r2_0 数据面修复后新一层）——根因实落 CoreItem.heal 默认实参截断（禁碰文件，按移交纪律记受阻）

### 基线（任务命令原样，修复前）

- `python -X utf8 tools/verify_oracle.py --cases run817_r18,run819_r15,run820_r10,run821_r7,run823_r18 --force --alignment-out output/oracle/alignment_task_r3_0.json`：**0/5 三方一致**。
- 首分歧：run817 idx80（PP Health 12v11）、run819 idx363（Djinn Lamp DamageBuff `item:""v"Flame Whip"`，行级 254）、run823 idx136（Light Goobert 32v31，2929 差异含 133 事件长度级联 O=3627/G=3494）、run820/821 gd≡oracle（py 腿 165/92 转写面，非本任务面）。
- **任务提示的「命中链栈事件位次」面实测不存在**：run817 全部 85 处差异均为同位事件参数值差（零结构性位次差）；Paradise Birb 激活 tick 序 gd≡神谕逐位相同（[161,161,161,323,328,485,488,635,645,784,793,793,938,944]×两侧同）。独占文件逐段核对：CoreCharacter.dealDamage :546-550↔decompiled Character.gd:482-487 同序；pre_take_damage :640↔:574、createEvent_Attack/Damage :689/:693↔:631/:634、applySpikes 尾 :710↔:707 全同序——位次面对不上账，差异全在数值。

### 根因（两级，均不在本任务独占文件内）

1. **主面（run817 ×85、run823 ×2929）**：`gd_core/CoreItem.gd` heal() 入口无条件 `int(amount)` 截断（r1_1 补；任务开始时 :2185-2189，并行充能任务在改，会话中漂至 :2207-2211）。原版 `Items/Item.gd:4826 func heal(amount: int = getP_m("heal"))` 的类型化形参截断**只发生在显式传参绑定，默认实参按原类型直通**。引擎级实证：`output/_round_patches/r3_0/typed_param_test.gd`（本仓 output/godot36 Godot 3.6 实跑）——`default_path=(8.56, type=3 REAL)`、`explicit_path=(8.56→8, type=2 INT)`。oracle 数值模型：run817 全部 **112 个 PP+Banana 治疗事件「无截断」模型零失配、截断模型 85 失配**（例：对手 PP mult=1.07/eff=1.42 → 神谕 12=round(8.56×1.42)；截断则 int(8.56)=8→round(11.36)=11）。r1_1 獾灵 41.8→41（显式传参路径）与本结论自洽不冲突。
2. **次面（run819 idx363 ×2；模拟修 1 后在 run823 idx447/485 浮出）**：Djinn Lamp DamageBuff 事件 `params.item` 神谕 ""（Flame Whip 翻译缺→Util.tra 空）vs gd "Flame Whip"——decompiled `ItemDescriptor.gd:116-121` getTranslatedName 翻译回退面 vs `gd_core/CoreItemData.gd:286-287` 恒 `return name`。

### 修复（待移交：gd_core/CoreItem.gd 属充能任务、CoreItemData.gd 数据面，均禁碰清单外）

```gdscript
# gd_core/CoreItem.gd heal()（py 镜像 gd_core_py/gd_core/CoreItem.py 同构劈分）
func heal(amount = null, triggerEvent = null):
	if amount != null:
		amount = int(amount)    # 显式传参：类型化形参绑定截断（r1_1 run647_r10 实证保留）
	else:
		amount = getP_m("heal") # 默认实参：不转换（r3_0 Godot 3.6 引擎实证 + run817 112 事件模型拟合）
	var healed = character().heal(amount, self, triggerEvent)
```

- 影响面：全部**无参** heal() 调用者（gd_core_items 27 文件：Pine Protector/Banana/Light Goobert/Chili Pepper/Crown/Cauldron 等）；显式传参路径行为不变。
- 并行实证：CoreItem.gd 会话内 +137 行未提交（:2185→:2207 漂移）——落笔必撞车。

### 修复效果模拟（monkeypatch 灌 py 内核，零文件改动）

- `output/_round_patches/r3_0/simfix_heal_no_trunc_r3_0.py`（产物 simfix/<case>/events.json，比对口径=verify_oracle canonical）：
  - run817_r18 首分歧 80→**None（954/954 全对齐，0 差异）**；
  - run823_r18 136→**447**（+311；447=次面 Djinn item，更深层 idx557 Blind timeout -7v-6 属新一层入口）；
  - run819/820/821 py 腿首分歧不变（293/165/92）——**无一场前移，退步条件不触发**。
- 探针：`output/_round_patches/r3_0/probe_pp_heal_r3_0.py` + `probe_pp_heal_run817_r18.txt`（[AMP]/[BIRB]/[HEAL]/[HEALEV] 打点：paramMult["heal"] 轨迹与 eff=1.42 双方一致，差异仅在 heal 入口截断一步）。

### 验证状态

- 基线定向验证：已跑（上述命令 --force），0/5；修复后定向验证**未跑**（修复未落笔）——充能任务落笔后用同一命令（独立 alignment-out）复验，对照本条基线（预期 80→None、363 保持、136→447）。
- 回滚条件：不适用（本任务零代码改动；独占 CoreCharacter.gd/CoreCombat.gd 零写入，备份 output/_round_patches/r3_0/*.bak 与现文件逐字一致）。
- 台账注：共享夹具 gd_core_test/oracle_align_cases.json 会话中被并行任务重写为 run718_r13 等 5 场（工具口径内重写，r2_1 先例）；本任务比对直接读 output/oracle/align/ 产物与 lineups，未依赖夹具。

### 红线自查

零 git 写操作；独占两文件零改动；禁碰清单文件（CoreItem.gd/CoreItemData.gd 等）零写入；新建文件仅 output/_round_patches/r3_0/（探针/语义验证/模拟/备份/simfix 重放产物）；全程无头。

---

## r3_2 — Resistor 充能送达残余面（×33=23+10 同根因簇组，type=107 origin=Resistor；r2_2 cmPos 表修后新一层）

- 任务场集合：run1129_r18, run1131_r18, run1285_r5, run1106_r18, run1256_r14（独立 alignment-out：`output/oracle/alignment_task_r3_2.json`）
- 独占文件：gd_core/CoreItem.gd, gd_core/CoreHooks.gd；备份 `output/_round_patches/r3_2/CoreItem.gd.bak`、`CoreHooks.gd.bak`（CoreHooks.gd 本轮零改动）。

### 根因（仪器：事件流对位 + 离线折叠式复算 + Resistor107 计数）

`_chargeInventoryCells`（r2_2 版）把折叠锚取在 `getTopLeftCell()`（真值占格最小值），而原版
（Item.gd:1040-1047 → ElectricalCharge.gd:139-140 → Inventory.gd:377-381 两步互逆）的锚是
**节点原点格** node_cell = floor((O − O_inv)/80)。两者相差

```
min over tiles of floor(R_fd(80·tile + cmPos + (40,40))/80)  =  min(R_fd(tiles)) + floor(R_fd(cmPos+(40,40))/80)
```

（tile = 各发射器 .tscn CollisionMap 的 tile_data 本地 tile 坐标；逐项相同的 floor(w/80) 相减消去）。

- 1×1 发射器（Battery/Charge Splitter/Cog Badge/Mana Crystal）：单 tile 折叠格≡占格≡top_left，偏差恒 (0,0)
  ——r2_2 的六场验证与三个签名场（run1129_r18 idx2 / run1285_r5 idx1 / run1106_r18 idx3）t0 全落在这批物品上，
  故 r2_2 修复后 t0 Resistor Heat(107,3) 已全部到位（本轮复核确认在档）。
- **多格发射器非零且随 fd 变号**：Lightning Staff 1×4 → (0,−2)/(−2,0)；Generator 1×2 → (0,−1)/(−1,0)；
  Con-Trap-Tron L 三格 → (0,−1)/(−1,0)/(−1,−1)。语料无 Generator/Con-Trap-Tron（28 场全为 Lightning Staff fd=0/1），
  故本簇 = Lightning Staff 充能送达整体错位 1~2 格 → 充能落进空格/非反应物，Resistor 收不到 heat、Coil 收不到 steal。
- 语料实证（修复前）：run1367_r11 oracle Resistor107=6 vs gd=0；run1306_r6 4 vs 0；run1284_r7 7 vs 0；
  run1097_r18 Coil steal 事件 102 vs 43。run1284_r7 修复前首分歧 idx52 恰为本面签名
  （oracle Resistor(1,1) Heat 3 vs gd 无）。
- 排除项（与提示逐条对上）：
  - 多发射器/多格路径：ChargeSplitter/ConTrapTron/ManaCrystal 的多次 sendCharge、
    chargeReceived→onChargeReceived→emitCharge 接力递归次序，与 ElectricalCharge.onNewCellEntered
    （ElectricalCharge.gd:211-233）逐行一致（含 Zap 抽 4.0-4.02 在 chargeReceived 之后的次序）——无责。
  - CoreHooks.gd:197 `sendCharge`：纯表现尾钩（空体、无 rng、不在任何判定条件内），r2_2 无责结论成立。
  - py 转写层 Resistor Heat 响应缺位：gd_core_py 独立面（r2_1 残留），未混入本轮（见下「py 镜像注明」）。

### 修复（仅 gd_core/CoreItem.gd）

1. 新增 `CHARGE_EMITTER_COLLISION_TILES` 常量表（7 发射器的 CollisionMap 本地 tile 坐标，与
   CHARGE_EMITTER_CM_POSITION 同源：battle_items.json grid.collision_cells = .tscn tile_data 解码）。
2. `_chargeInventoryCells` 折叠锚回退：`hit = top_left + floor(R(80c + cmPos + (40,40))/80) − min_fold`，
   min_fold = 同管线逐 tile 折叠格的分量最小值（非发射器 tiles 空 → ZERO，行为与修复前逐字一致；
   push_back 实参保持与调用同行，gd_to_py 改写器约束未破坏）。
3. 同步修正 sendCharge 注释块两条过时断言（「7 件发射物全部 1×1，无 fixture 归一化位移项」不实）。

### 验证（全部本轮实跑）

- 任务命令（--force，独立 alignment-out `output/oracle/alignment_task_r3_2.json`）：
  修复前基线 0/5，firstDivergence（oracle_vs_gdcore）= run1106_r18 **8** / run1129_r18 **6** / run1131_r18 **2** /
  run1256_r14 **—**(仅py) / run1285_r5 **—**(仅py)；修复后 = **8 / 6 / 2 / — / —，逐场相同 → 无回退**。
  （这 3 处首分歧分别被戒指掷点面 idx8/idx2 与 Cog crafted 数据面 idx6 挡住，见「相邻面观察」。）
  run1106_r18 gd 事件数 771→790（staff 充能开始送达的证据）。
- staff 簇定向验证（--force，独立 alignment-out `output/oracle/alignment_task_r3_2_probe.json` / `_probe2.json`，
  28 场多格发射器全覆盖）：
  - **gd 侧收敛（首分歧 None）9 场**：run1284_r7（52→None，gd≡oracle 全场）、run1162_r7（83→None）、
    run1295_r10（174→None）、run1310_r7（88→None）、run1311_r5（10→None）、run1320_r5（60→None）、
    run1326_r7（55→None）、run1339_r6（72→None）、run1377_r13（42→None，oracle≠gd 仅余 1 场非 charge 类）。
  - **首分歧后移 12 场**：run1325_r11 1→491（+490）、run1108_r18 1→243（+242）、run1367_r11 40→225（+185）、
    run1105_r18 163→327（+164）、run1283_r11 1→128（+127）、run1097_r18 154→285（+131）、
    run1107_r18 162→229（+67）、run1101_r18 137→172（+35）、run1230_r13 41→50（+9）、
    run1163_r18 3→11（+8）、run1306_r6 5→7（+2）、run1109_r14 1→2（+1）。
  - **不变（被其他面挡住，首分歧均非 charge 事件）6 场**：run1091_r18（Claws 伤害 5v6 rng 面）、
    run1102_r18/run1106_r18/run1126_r5（戒指掷点面）、run1103_r18（Cog 15v10 crafted 数据面）、
    run1123_r11（t302/314 时序 rng 面）。
  - **修复前已一致场保持一致 1 场**：run1289_r7（三方一致，回归探针）。
  - **零场前移**——退步条件不触发，无需回滚。
- 本面指标（Resistor107 计数）修复后：run1284_r7 7=7、run1306_r6 4=4、run1101_r18 6=6、run1097_r18 0=0；
  run1367_r11（6v4）/run1105_r18（39v24）的差额全部落在各自新首分歧（idx225/idx327）之后（时间线已另面分叉）。

### 相邻面观察（未动文件，供并行任务参考）

- **Cog crafted 数据面**（run1129 idx6、run1103 idx2、run1306 idx7 位置差）：CSV 真值
  `decompiled_full/Sheets/CSV/ItemData_e.csv` 中 `Mana Crystal*>Cap of Brilliance`（Leather Helm 行）、
  `Corrupted Crystal>Evil Cap` 等配方产物应使 `originatingRecipes` 非空，而
  `gd_core_test/item_battle_fixture.json` 的 Cap of Brilliance crafted=False（run1129 玩家板 Cog(2,0)
  oracle 15=5×3 vs gd 10=5×2）。
- **戒指掷点面**（run1106 idx8 / run1131 idx2 / run1102 idx1 / run1126 idx14）：MagicRing/SuperiorRing 的
  randEffects 在装配期掷点（gd_core_items/Exclusive/MagicRing.gd `_readyInit`），装配链位漂移导致效果组不同
  （oracle Magic Ring heat 5 vs gd vampirism 4+poison 4；oracle Superior Ring 无 StartOfBattle vs gd 有）。
- **py 镜像注明**：`gd_core_py/gd_core/CoreItem.py:2158-2173`（_chargeInventoryCells）仍为修复前折叠式
  （top_left 锚、无 min_fold、CHARGE_EMITTER 双表缺失）——属 gd_core_py-transpiler 独立面，本轮未越权改写；
  其落笔点 = 把 gd 侧同构劈分（锚点回退 + CHARGE_EMITTER_COLLISION_TILES）转译过去。

### 红线自查

零 git 写操作；独占文件仅 gd_core/CoreItem.gd 落笔（CoreHooks.gd 备份与现文件逐字一致、零改动）；
清单外文件零写入（gd_core_py/CoreItem.py 仅注明未动）；新建文件仅 output/_round_patches/r3_2/ 备份与
output/oracle/alignment_task_r3_2{,_probe,_probe2}.json；全程无头。


---

## r3_1 · Falcon Blade 攻击环抽次台账面（×39，type=1 origin=Falcon Blade）

### 结论一句话
×39 家族（run764_r15 idx30 伤害 2v3、run718_r13 idx78 4v5 等）的根因不在 FB 行为脚本，而在**装配网格数据**：带刺护盾（Spiked Shield，rect_fallback 物品）运行时占格为继承自 Items/Item.tscn 根 CollisionMap 的 **2×2**（4 瓦片），而抽取管线 rect_fallback 按 size=[1,1] 兜底成 1×1，导致 gd/py 装配的带刺护盾少占 3 格——冰花（Ice Flower）Secondary 受影响格 (1,6) 与冰霜卷轴（Spell Scroll Ice）Primary 受影响格 (1,6) 不再与其占格相交，二者的 `activated` 监听连接断裂，带刺护盾每次 afterBlock→activate 少 2 次 rollChance 掷点（冰花 rollChance2 50% + 卷轴 rollChance 30%，神谕侧均 PROC：gave_block + 冰花给蓝 + 卷轴施加寒冷），此后伤害 roll 字位错开 4 字（run764：gd roll=字725 vs 神谕=字729）→ ±1 伤害。

### 定位方法（对后续同类缺口是模板）
1. **逐抽对位**：oracle 探针（ORACLE_DEBUG + ORACLE_FIGHTS_ROOT 重定向）+ gd 探针（ORACLE_ALIGN_TRACE）双侧 rng 日志，u=(v-from)/(to-from) 归一对位（output/_round_patches/r3_1/u_align.py）——首错位 gd[338]=第二次 randPitch vs 神谕[338]=裸 randf（同字不同调用点）。
2. **事件锚定**：rng trace 的 EVENT 行 ↔ events.json 第 k 条（output/_round_patches/r3_1/ev_align.py），锁定缺抽窗口=ev21（FB 攻击事件）与 ev24（蓝宝石给蓝）之间。
3. **PCG 字流重放**（output/_round_patches/r3_1/pcg_replay.py + word_ledger.py）：从 seed=6050129 重放原始字流（战斗起点 state=1362217144685325691 位于字 459），证明两侧耗字总数一致但**伤害 roll 的字位差 4**（gd=725 vs 神谕=729）——纯调用点错位非缺抽多耗。
4. **差分拔除**（oracle 副本 6 轮 R3_1_DIFF 门控实验）：activated 发射/ blocked 信号/ attacked 信号/ character_attacked 逐个拔除——2 抽随 afterBlock 消失、随 drainStamina 拔除保留 → 定位 activate() 的 activated 监听掷点。
5. **连接图插桩**（EventBus.connectEvent 打点，trace2）：`Spiked Shield --activated--> Ice Flower/Spell Scroll Ice` 在神谕运行时成立。
6. **isItemAffected 决策点插桩**（R3ISA）：**带刺护盾运行时 occupiedCells=[(0,5),(1,5),(0,6),(1,6)]（2×2）**，冰花 Secondary 运行时 cells=[(1,6),(2,6),(3,6),(2,7)] 含 (1,6) → 连接成立的直接证据；gd 夹具 occ=[[0,5]]（1×1）→ 不相交。
7. **tscn 继承链查证**：SpikedShield.tscn 无 CollisionMap tile_data 覆写 → 继承 Item.tscn:1784 的 4 瓦片 [(-1,-1),(0,-1),(-1,0),(0,0)]；extract_grid.py 对无覆盖物品走 rect_fallback（size=[1,1] 兜底）→ DB 错为 1×1，共 **19 件**（Wooden Buckler/Spiked Shield/Ruby Egg/Heart Container/Ruby Whelp/King Crown/Present/Pop/Bomb/Mega Clover/Frozen Buckler/Emerald Egg/Emerald Whelp/Sapphire Egg/Sapphire Whelp/Amethyst Egg/Amethyst Whelp/Lootbox/Hypercube）。

### 修复（经二次请示授权，主 agent 裁决按防冲突次序）
1. `simulator/extract_grid.py` rect_fallback：无覆写物品不再按 size 兜底，改继承 Item.tscn 根 CollisionMap 4 瓦片（附 tscn 继承链行号注释）。
2. `assets/battle_items.json`：19 件 rect_fallback 的 collision_cells 最小化改写（read-modify-write，前后快照 output/_round_patches/r3_1/battle_items.json.prefix，写入前 sha256 防并行撞车）。
3. 重生成链：gen_gd_core_data（gd_core_runtime.json）+ gen_lineup_fixture（item_battle_fixture.json/LineupFixture.gd）+ verify_oracle gen_fixtures（oracle_align_cases.json）。
4. py 腿自动随数据修复（engine/item.py _affected_cells_abs 同源 grid，无需改 py 代码；py 色枚举本就正确用 0/2/4/7）。

### 验证数字
- **run764_r15：gd≡oracle（794=794 事件逐行一致）**——修复前 oracle≠gdcore idx30（伤害 2v3）；修复后 FB 伤害序列 [0,2,0,3,3,0] 与神谕逐点一致；字流台账 **3738/3738 抽 u 全对位**（修复前首错位 gd[338]）。py 腿 FB 伤害同步回正（idx30=2）。
- 定向 5 场：run764 gdcore≡oracle（py 分歧为后续层）、run778 三方一致、run747 首分歧后移（idx372→事件流一致、仅战斗时长差异）、run718/730 首分歧 idx 不变（266/456，光之黏黏致盲层=既有其它根因）。
- **连带风险自查**：202 个已对齐场含 rect_fallback 物品，抽 3 场（run569_r11 带 Spiked Shield、run574_r7 带 Wooden Buckler、run575_r18 带 Bomb）定向：**首分歧 idx 全部不前移**（run569 idx126、run574 idx45 两场修复前后一致——该两场在当前代码态本就分歧，alignment.json 的 aligned 判定系旧代码态产物；run575 保持三方一致）。
- **中途回滚与复 apply**：首次 side-risk 读到 2 场"退步"曾按指令回滚全部数据改动；复跑发现回滚态下该 2 场同样分歧（首分歧 idx 相同），判定非本次改动引入 → 重新 apply（extract_grid+19 件+重生成链），二次验证通过。

### 红线自查
改动面：simulator/extract_grid.py（兜底逻辑+注释）、assets/battle_items.json（19 件 collision_cells）、生成物 gd_core_runtime.json/item_battle_fixture.json/LineupFixture.gd/oracle_align_cases.json（重生成）。oracle/ 副本 6 文件插桩（Item/Shield/Character/EventBus/IceFlower/SpikedShield）**全部清除并 fc /b 核对还原**（Item/Shield/Character/EventBus 对 oracle_src_backup 逐字节一致；IceFlower/SpikedShield 手工还原后 R3 标记零残留）。冻结语料 fights/** 只读未触碰。gd_core/CoreCharacter.gd/CoreItem.gd/CoreRng.gd/CoreUtil.gd 本轮**零写入**（根因不在该层）。全程无 git 写操作。


---

## 2026-10-11 · r4_0 — Pine Protector heal 默认实参截断劈分（×55，type=104 origin=Pine Protector；r3_0 设计本轮落地）

- 任务场集合：run817_r18, run819_r15, run820_r10, run821_r7, run823_r18（独立 alignment-out：
  `output/oracle/alignment_task_r4_0.json`；修复前基线另存 `alignment_task_r4_0_prefix.json`）。
- 独占文件：gd_core/CoreItem.gd；备份 `output/_round_patches/r4_0/CoreItem.gd.bak`
  （修复前快照）+ 三份运行日志 prefix/postfix/postfix2。
- 影响面：全部 **27 个无参 heal() 物品**（grep `^\s*heal()\s*$` 逐文件点数=27，含 PineProtector、
  LightGoobert、Goobert 家族、Banana/Crown/Ukulele 等；r2_0 残留 run811 PP heal 18v17 同属本族，
  留待全量里程碑复核）。

### 根因（仪器：Godot 3.6 引擎级实证复跑 + r3_0 探针 + decomp 行号 + 事件流对位）

- 原版签名 `decompiled_full/Items/Item.gd:4826`：`func heal(amount: int = getP_m("heal"), triggerEvent = null)`；
  下游 `decompiled_full/Core/Character.gd:739-741`：`amount *= getHealingEfficiency(); amount = round(amount)`
  （先乘效率后 round）。gd_core 镜像同构（gd_core/CoreCharacter.gd:759-761）。
- **GDScript 类型化形参的转换面不对称**（r3_0 typed_param_test.gd，本轮本会话在 Godot 3.6 实跑复证）：
  `default_path=(8.56, type=3 TYPE_REAL) explicit_path=(8, type=2 TYPE_INT)` →
  **HYPOTHESIS(default-no-convert, explicit-truncate) => CONFIRMED**——默认实参先求值再绑定、
  不做 int 转换（REAL 直通）；显式传参才在传参瞬间截断（向零取整）。
- r1_1 的修复（`output/_round_patches/r1_1/CoreItem_heal_int_trunc.diff`）在 heal() 入口**无条件**
  补 `int(amount)`：显式路径正确（保 run647_r10 獾灵 41.8→41），但默认路径被错杀。
- 事件流对位（run817_r18 冻结语料 idx80 + r3_0 探针 output/_round_patches/r3_0/probe_pp_heal_run817_r18.txt）：
  heal 参数被 Carrot/Blood Goobert/PP 自身 ×1.07 放大（探针 [AMP] t=2.6833 mult_after=1.07），
  t=2.95 PP `getP_m=8.560000 int->8 eff=1.42 round->11`，而原版 8.56 直通 → round(8.56×1.42)=12
  ——oracle idx80 `amount=12` vs gd `amount=11`，即本场首分歧。run823_r18 idx136 同签名
  （Light Goobert heal 32v31）。修复前基线（--force 重放，本会话实跑）：
  run817 og=**80**、run819 og=**363**、run820 og=**None**、run821 og=**None**、run823 og=**136**。
- 家族标签复核：5 场冻结语料中 origin=Pine Protector 的事件类型分布 {12:1793, 104:84, 14:115, 0:115}
  ——×55 的 (type=104, origin=PP) 主签名与 type=12 heal 同源同物品。

### 修复（仅 gd_core/CoreItem.gd:2229-2248，heal 一处）

劈分两条路径（等价原版类型化形参的不对称转换面）：

```gdscript
func heal(amount = null, triggerEvent = null):
	if amount == null:
		amount = getP_m("heal")      # 默认实参路径：不转换（REAL 直通 Character.heal → round）
	else:
		amount = int(amount)          # 显式传参：int 截断（保 r1_1 獾灵 run647 41.8→41）
	var healed = character().heal(amount, self, triggerEvent)
```

- 注释块同步改写：r1_1 的「默认实参路径同样先求值再转换」论断被 r3_0 引擎实证否定，已更正
  并落引（typed_param_test.gd 实跑输出 + run817 12v11 实证）。
- 显式传参调用点语义逐一核对不受影响：stealLife（CoreItem.gd 本文件）、BadgerSpirit/CursedHairComb/
  DragonKnight/DragonNest/DragonSet/FrogPrince/Ghost/GoldCube/HogusBogus/LightningPotion/Mananana/
  MechaBat/BloodyDagger/BookofLight 等 15+ 处显式 float 实参仍走 else 分支截断（与原版传参瞬间
  截断一致）；27 个无参调用点走默认直通。
- **对 backup 逐字 diff 仅两处 hunk**（注释块 + else 分支）——r3_2 已改的 charge 双表
  （CHARGE_EMITTER_COLLISION_TILES、_chargeInventoryCells 折叠锚回退）逐字未动，未回退。

### 验证（全部本轮实跑；任务命令两轮）

- 命令（--force，独立 alignment-out）：`python -X utf8 tools/verify_oracle.py --cases
  run817_r18,run819_r15,run820_r10,run821_r7,run823_r18 --force --alignment-out output/oracle/alignment_task_r4_0.json`
- 执行记录：第一轮 gd 腿 5/5 ok 后，py 腿被**并行任务的夹具改写**挤掉（run_py「不在夹具内」0/5，
  共享夹具 gd_core_test/oracle_align_cases.json 被并行 gen_fixtures 覆盖——log 留档
  postfix_verify_run.log）；**原样复跑同命令**第二轮两腿 5/5 完成（postfix_verify_run2.log），
  以下数字以第二轮为准（两轮 gd 腿逐场 ok，事件数与基线相同：954/1435/7703/753/3494，ticks 逐场相同）。
- 修复后首分歧（oracle_vs_gdcore）逐场对照：

| 场 | 修复前 og | 修复后 og | 判定 |
|----|-----------|-----------|------|
| run817_r18 | 80（PP heal 12v11） | **None**（gd≡oracle，954/954 事件+渲染行双判据一致） | **收敛，与 r3_0 预测 idx80→None(954/954) 一致** |
| run819_r15 | 363（Djinn Lamp item 名数据面） | 363（同一面，逐字不变） | 不变（非 heal 面） |
| run820_r10 | None（gd≡oracle） | None | 保持一致，零回退 |
| run821_r7 | None（gd≡oracle） | None | 保持一致，零回退 |
| run823_r18 | 136（Light Goobert heal 32v31） | **447**（+311 后移） | **后移，与 r3_0 预测 136→447 一致** |

- **零场前移——退步条件不触发，无需回滚。**
- 直查产物：重放后 gdcore idx80（run817）amount=**12**、idx136（run823）amount=**32**，均与 oracle 相等
  （修复前 11/31）。match 分布 oracle≠gdcore 2→0 场（817 转「gdcore≡oracle 但 py 分歧」、823 转
  「oracle≠gdcore 且 py 分歧」但首分歧从 heal 面后移到 Djinn Lamp 面）。
- 修复后新首分歧（run819 og363 / run823 og447）同签名：Djinn Lamp `damage_buff` params
  `item:"Flame Whip"`（gd）vs `item:""`（oracle）——烧毁物品名数据面，非 heal 面，属下一层根因。

### py 镜像注明（未越权改写）

- `gd_core_py/gd_core/CoreItem.py:2340-2343` heal 仍为**无条件 int 截断**（line 2343 `amount = int(amount)`），
  2331-2339 注释块仍载 r1_1 过时论断——属 gd_core_py-transpiler 面，本轮零写入（该文件当前携带并行任务
  未提交 diff +194/-21 行，印证不越权）。
- 本轮 py 腿实证其镜像签名：修复后 run817 gdcore_vs_py 首分歧=**80**（py 11 vs gd 12）、run823=**136**
  （py 31 vs gd 32）——恰为 heal 面在 py 侧的同根因残留；run819 gp=293 / run820 gp=165 / run821 gp=92
  修复前后逐字不变（非本族面）。
- 落笔点 = 把 gd 侧同构劈分（else 分支）转译过去，随 tools/gd_to_py.py 再生成落定；落地后 run817 预期
  转三方一致（r3_0 monkeypatch 模拟已证 954/954），run823 gp 首分歧应后移至与 og 同面。

### 红线自查

零 git 写操作；源文件落笔仅独占文件 gd_core/CoreItem.gd（对备份逐字 diff 仅 heal 两处 hunk，charge 双表
未回退）；清单外源文件零写入。工具自动产物：gd_core_test/oracle_align_cases.json（mandated 管线
gen_fixtures 重生成，非手改）+ output/oracle/align/{gdcore,py}/<5 场> 重放产物（--force 语义）。新建文件仅
output/_round_patches/r4_0/（备份 + prefix/postfix/postfix2 三份运行日志）与
output/oracle/alignment_task_r4_0{,_prefix}.json；全局默认出 output/oracle/alignment.json 两轮均未触碰
（显式 --alignment-out 独立文件）；冻结语料 output/oracle/fights/** 只读。全程无头。

## 2026-10-11 · r4_2 — 棋族 repositionPiece 移位缺口（×31，type=0 origin=Chess Board；r1_0 残留 1 原样未动）

### 任务与场集合

任务书定向 5 场：run645_r11,run676_r9,run712_r9,run714_r18,run949_r9。改前基线
（`python -X utf8 tools/verify_oracle.py --cases run645_r11,run676_r9,run712_r9,run714_r18,run949_r9
--force --alignment-out output/oracle/alignment_task_r4_2_baseline.json`）：0/5，
oracle_vs_gdcore 首分歧 **idx 15/16/23/48/42**，同签名：oracle Chess Board type=0
（棋盘 Activation=捕获发生）gd 侧缺失，gd≡py（255=255/343=343/870=870/694=694/474=474）。

### 根因（实证链，与 r1_0 残留 1 的预判一致并补全三层证据）

1. **decomp 判定面**：decompiled_full/Items/Exclusive/Chess/ChessPiece.gd:93-97
   `repositionPiece(toCell)` 四行中 :94 `moveTo(...)`/:95 `z_index`/:97
   `movebackTween.tween_callback` 为表现面，**:96 `inventory.moveItem(self,[toCell])`
   是判定面**（decompiled_full/Core/Inventory.gd:640-647 = clearItemCells +
   addItemCells + occupiedCells 赋值，零信号零 rng；被剥的 recalculateTilemap
   :131-143 是 call_deferred 的 tilemap.set_cellv 纯重绘）。调用链两路：
   捕获 onPieceCaptured:73 `setState(targetCell,…)` 与移动 onPieceMoved:53
   `setState(targetCell)` 都经 onStateChanged:104-107 Vector2 分支调
   repositionPiece。全工程唯一调用点 :107（grep 封口）。
2. **gd 侧缺位**：gd_core_items/Exclusive/Chess/ChessPiece.gd 修前
   repositionPiece 整函数剥成 `pass`（:84-85）、onStateChanged Vector2 分支无
   repositionPiece 调用（:92-95）→ 捕获者不占被吃格、移动不落格 → 全部棋子
   occupiedCells 冻结在装配位 → ChessBoard.findPieceToCapture 的
   `occupiedCells[0]+cell` 查询格恒错 → 捕获恒空转 findSpaceToMove；且内核
   gd_core/CoreGrid.gd **无 moveItem 方法**（grep `func moveItem` 全 gd_core/
   gd_core_items 零定义，修前零调用方零回归面）。
3. **事件/台账对位**：run645_r11 idx0-14 两侧逐事件全等；idx15=oracle 玩家棋盘
   Activation + idx19 BlackPawn mana3（type=105，top_left (4,2)）+ idx20
   WhitePawn lucky1（type=101，同 (4,2)）——黑兵吃 (4,2) 白兵的捕获链；
   gd[15] 直接跳 Speak with Animals 激活（棋盘静默）。修前
   ORACLE_ALIGN_TRACE 台账（output/r4_2_probe/align_gd_prefix/run645_r11/
   rng_trace.txt）：ChessBoard.gd**:164（findSpaceToMove）16 行**——本应捕获的
   tick 全部落子。

### 修复（改前态备份 output/_round_patches/r4_2/，三文件全在独占清单内）

- **gd_core/CoreGrid.gd**：新增 `moveItem(item, newCells)`（对齐 Inventory.gd:640-647，
  clearItemCells→addItemCells→occupiedCells 赋值次序逐字保留；recalculateTilemap
  表现面剥离注明；零信号零 rng）。
- **tools/build_item_scripts.py**：新增 pass `adapt_chess_reposition`（沿用
  r1_0 adapt_chess_movecells 的幂等替换先例）——还原 repositionPiece 判定支
  `inventory.moveItem(self, [toCell])`（注明 :93-97 面）+ onStateChanged Vector2
  分支补 `repositionPiece(targetCell)`；报告行含 miss 计数防生成面形态漂移静默失效。
- **生成态同步**：`python tools/build_item_scripts.py` 重生成（报告：判定支还原
  文件 1、点 2、miss 0；md5 对照改前基线 gd_core_items+gd_core_py 全树 1034 文件
  **仅 gd_core_items/Exclusive/Chess/ChessPiece.gd 一个文件变化**）；
  `python tools/gd_to_py.py` 重生成 gd_core_py（CoreGrid.py+ChessPiece.py 孪生 +
  CoreItem.py 并行轮源编辑的镜像同步；--check「产物与 gd_core / gd_core_items 同步」）。

### 验证数字（全部本轮实跑）

- **定向（任务命令原样）**：`--cases run645_r11,run676_r9,run712_r9,run714_r18,run949_r9
  --force --alignment-out output/oracle/alignment_task_r4_2.json` → **2/5 三方一致**
  （run645_r11 344=344=344、run949_r9 464=464=464，judgement 双判据过）；另 3 场
  首分歧 **15→对齐 / 16→120 / 23→316 / 48→776 / 42→对齐，5/5 严格后移**，
  回滚条件（前移）不触发。定案树复跑（_verify_final2.log）数字逐字节复现。
- **混杂排除（A/B）**：定位期发现并行轮 06:25:18 改了 gd_core/CoreItem.gd
  （基线 06:19:25 早于它）。将本修复三文件回退（Current 树=并行态）复跑同 5 场 →
  idx **15/16/23/48/42 与基线逐位相同**（output/_round_patches/r4_2/
  _ab_parallel_only.json）——并行编辑对本簇零影响，前后对照干净。
- **修后台账**（output/r4_2_probe/align_gd_postfix/run645_r11/rng_trace.txt）：
  :164 findSpaceToMove 行 16→**4**（残余 4=真落子）、Gpick（每捕获 1 抽）2→**12**、
  分歧点前 227 行逐字节一致（链位零扰动）；run645_r11 修后 combat_time
  9.566667=oracle、winner 同、ticks 725（gd 腿粒度）。
- **场集合外抽查（3 棋场 A/B，非回滚口径，额外谨慎）**：run644_r7 idx295
  （Carrot Goobert，非棋族）修前修后逐位同；run713_r11 oracle_vs_gdcore
  **13→267** 后移（gd 391→521 向 oracle 1015 靠拢）；run1113_r18 首分歧 idx108
  （vampirism，非棋族）不变、事件总数 520→**296=oracle**（尾部愈合）。
- **新一层分歧（均后移出本根因簇，属后续轮入口，非本轮引入）**：run712_r9
  idx316 / run714_r18 idx776 仍 Chess Board type=0（棋局更深处，棋子挪位生效
  后的次级查询面；伴随 Black Bishop 109/108 链）；run676_r9 idx120 Shiny Mantle
  （非棋族）。场集合外观察：run713_r11/run1113_r18 修后现 gd↔py 腿分歧
  （gd 521 vs py 947；gd 296 vs py 312）——棋面激活后暴露的转写器语义差，
  本轮 py 镜像为 gd_to_py 机械产物（--check 同步过），归 py 属主/后续轮。

### 红线自查

独占清单内改动 3 文件（gd_core/CoreGrid.gd、gd_core_items/Exclusive/Chess/
ChessPiece.gd、tools/build_item_scripts.py）+ 生成态（gd_core_items 全树重生成
但 md5 证仅 ChessPiece.gd 变化；gd_core_py 机械重生成）；并行轮 gd_core/CoreItem.gd
(06:25:18) 零触碰（其 py 镜像同步属 gd_to_py 全树重生成语义，非手改）。改前态
备份 output/_round_patches/r4_2/（.before/.fixed 全套 + _before/ py 孪生 + md5
台账 + 基线/修后/复现日志 + A/B 两份 alignment json）；探针台账留
output/r4_2_probe/{align_gd_prefix,align_gd_postfix}/。fights/** 冻结语料只读
（--force 只删两侧重放产物）；未改 tools/verify_oracle.py、tools/gd_to_py.py、
gd_core_test/** 判定逻辑（OracleAlignBattle.gd 仅运行未写）；无 git 写操作；
未触碰 Steam 目录；全程无头（--headless --audio-driver Dummy，stdout/stderr
重定向文件）。工具自动产物：gd_core_test/oracle_align_cases.json（管线
gen_fixtures 重生成）+ output/oracle/align/{gdcore,py}/ 重放产物（--force 语义）；
对齐结果全部写独立文件 output/oracle/alignment_task_r4_2{,_baseline}.json，
全局 output/oracle/alignment.json 未触碰。

---

## r4_1 · Falcon Blade 攻击环残余错位面（×34 快照；r3_1 网格数据修复后新一层）

- 任务场集合：run781_r9, run786_r14, run789_r18, run827_r10, run836_r18（独立 alignment-out：`output/oracle/alignment_task_r4_1.json`）
- 独占文件：gd_core/CoreRng.gd, gd_core/CoreUtil.gd, assets/battle_items.json；备份 `output/_round_patches/r4_1/*.bak|.prefix` + exclusive.sha256。
- **快照漂移**：任务快照所列签名（run781 idx39 9v10 / gd 165→152 缺 13、run827 idx46 7v6）在会话基线已不存在——run781_r9、run827_r10 现为**三方一致**（并行任务已收敛）。基线/终验均为 **2/5 对齐**，残余分歧 3 场、3 个面，**逐一定位后确认全部不在本任务独占文件内**（详见各面）。

### 面 1（run786_r14 idx74、run836_r18 idx90）：Djinn Lamp DamageBuff type=16 params.item 译名面

- 签名：oracle `{item: "", damage: 27}` vs gd `{item: "Falcon Blade", damage: 27}`；render 首差 `> [对手] 获得了+27点伤害（阿拉丁神灯）。` vs `猎鹰战刃获得了…`。语料全部 type=16 事件 params.item 均为 ""（5 场实证），gd 均为实名。
- 根因（与 r3_0 次面同一根，r3_0 已定性为待移交）：神谕语料无头生成 **TranslationServer 无翻译表** → decompiled `Utility/Util.gd:213-223` tra(key)：`tr(key)==key → ""`（缓存后返回空）；decompiled `Items/ItemDescriptor.gd:116-121` getTranslatedName：`tra(getName()+"_NAME")` 不以 "NAME" 结尾 → **返回 ""**；decompiled `Core/CombatLog.gd:815-821` createEvent_DamageBuff setParam("item", buffedItem.getTranslatedName()) → ""。gd_core `CoreItemData.gd:286-287` `func getTranslatedName() -> String: return name` 恒实名；py 镜像 `gd_core_py/gd_core/CoreItemData.py:378-379` 同（经 `gd_core_py/gd_core_items/Item.py:367-371` descriptor 委派）。
- **修复效果已在本任务实证（py 腿 monkeypatch，零文件改动）**：`output/_round_patches/r4_1/simfix_translated_name_r4_1.py`——把 `CoreItemData.getTranslatedName` 置为语料语义（恒 ""）后重放：run786_r14 **368=368 oracle≡simfix canonical 全对齐**、run836_r18 **574=574 全对齐**（首分歧 74→None、90→None）。译名面即该两场唯一残余面，其后无 FB 攻击环面。
- **移交补丁（落笔点 = CoreItemData.gd + CoreUtil.gd，均清单外/独占交界，本任务未落笔）**：
  1. `gd_core/CoreUtil.gd` 增 `tra(key)`（对齐 Util.gd:213-223：translationCache 查表 → `tr(key)`，`tr(key)==key → ""` 回填缓存）；
  2. `gd_core/CoreItemData.gd:286-287` getTranslatedName 改为 `var t = Util.tra(name + "_NAME"); return name if t.ends_with("NAME") else t`（对齐 ItemDescriptor.gd:116-121）；
  3. py 镜像同构：`gd_core_py/gd_core/CoreUtil.py` tra + `CoreItemData.py:378` 同改（py 无 TranslationServer，`tr` 等价恒返回 key → tra 恒 ""，与语料逐位同）。
  - 回归面：仅 type=16 事件 params.item 与 render 行（781/827 无 type=16，789 无 type=16——本集合内零回归面；simfix 已证 786/836 全对齐）。

### 面 2（run789_r18 idx412）：对手 Blind 栈超时 1 tick 面（gd t=301 vs oracle t=300）

- 签名：Light Goobert（玩家方）对对手 Blind：申请事件 idx381 t=271 tick（4.5167s）dur=3 两侧一致；其前栈组 221(-5)/230(-2) 两超时**两侧逐 tick 一致**；唯 t=120 申请 +7 dur=3 的超时（timeout=300 整）oracle 恰在 300、gd 在 **301**，其后全流级联（oracle 3983 vs gd 4215 事件）。
- 定位过程：926-303 tick 全事件窗仅此一事件（两侧）；数值模拟（acc/quantized 时基 × 重减浮点轨迹）证明该分歧非 T0 位差——**oracle 单场复跑实证**：`ORACLE_ONLY_CASES=run789_r18 ORACLE_DEBUG=1 ORACLE_FIGHTS_ROOT=output/_round_patches/r4_1/oracle_probe` 复跑，产物 events.json 与冻结语料 **3983=3983 逐事件全等**（语料可单场确定性复现，fire tick 与绝对时基无关）。
- 根因落点：`gd_core/CoreBuff.gd` 三分支计时模型（`_startTimer` :425-445 / `onTimeout` :386-410 重启分支 `delay = earliestTimeout - ctx.time` :407 / `_tick` :456-475）对「onTimeout 批次重启 → 70 tick 整边界」这一组合少 1 tick；原版真值 = decompiled `Core/Buff.gd:317-345`（`delay = earliestTimeout - Util.time` :347-350）× `oracle/oracle_fight.gd:875-925` drive_timers（restart 后 e[0]=get_time_left() 直灌、下 tick 起减）。**CoreBuff.gd / CoreContext.gd 均清单外 → 移交**（既有 a3-timer/run634 三分支标定的一个新数据点：run789_r18 idx412）。

### 面 3（run789_r18 gdcore_vs_py idx81）：Dragon Knight 伤害掷点链位面（py 4 vs gd/神谕 8）

- gd≡神谕至 idx412，故神谕该位同 gd=8；py=4。DK 伤害掷点两侧同数据（battle_items.json "Dragon Knight" params[1..2]=4.0/8.0，gd 掷点序列 6,5,7,8,5,4,5…与神谕对齐段逐点一致 → 数据无误、非 battle_items.json 缺口）。py 序列 6,5,7,[4],8,4,8,5,5,12… 与 gd 序列呈错位形态 → **py 链调用点漂移面**（第 4 次 DK 攻击掷点起）。落点 gd_core_py（`_rt.py`/engine 攻击链）＝转译器任务独占 → 移交，其 u_align/pcg_replay 仪器在案。

### 验证（全部本轮实跑）

- 任务命令两次（--force，`output/oracle/alignment_task_r4_1.json`）：基线与终验**逐场相同**——run781_r9 三方一致 / run786_r14 oracle≠gdcore @74 / run789_r18 oracle≠gdcore@412 + gdcore_vs_py@81 / run827_r10 三方一致 / run836_r18 oracle≠gdcore @90；2/5，零前移、零后移（本任务零代码改动，无回滚条件）。
- oracle 探针：`output/_round_patches/r4_1/oracle_probe/run789_r18/`（events.json 与冻结语料逐事件全等——确定性自证；fights/** 只读未触碰）。
- simfix：`output/_round_patches/r4_1/simfix/{run786_r14,run836_r18}/events.json` + `simfix_run.log`（canonical 口径全对齐）。
- 共享夹具注记：`gd_core_test/oracle_align_cases.json` 会话中被并行任务改写为 run645_r11 等 5 场；本任务比对直读 alignment_task_r4_1.json + align/ 产物，simfix 改为自取 seed（alignment JSON）+ 激活序（align/gdcore/<case>/events.json），不依赖该夹具。任务命令重跑会按工具口径把夹具重写回本任务 5 场（r2_1 先例）。

### 红线自查

零 git 写操作；独占三文件零改动（exclusive.sha256 基线=终验逐字 OK）；清单外文件（CoreItemData.gd/CoreBuff.gd/CoreContext.gd/gd_core_py/** 等）零写入；新建文件仅 output/_round_patches/r4_1/（备份/探针/simfix/日志）与 output/oracle/alignment_task_r4_1.json；oracle 复跑走 ORACLE_FIGHTS_ROOT 重定向未触碰冻结语料；全程无头。

---

## 2026-10-11 · op1 — Pine Protector 簇×50 陈旧产物假象判读（无码改，现场恢复轮）

- digest 首攻 PP Spikes×50 簇（run844_r11 等，O=PP Spikes(104) vs G=FW dmg0）。
- 全链直证（py 内核满时长复刻 verify 构造 + _py_payload 转储复验）：**PP spikes 事件
  24 个=oracle 数**——连接/rollChance/beforeBlock/giveSpikes/_py_payload 全链完好。
- 真因：盘上 verify 产物 mtime 01:38 早于 r4_0/r4_1/r4_2 修复，`--cases --force` 只重放
  指定场、其余场幂等跳过陈旧产物 → 假分歧。处置：清空 align/gdcore+py 全量重放
  （幂等续跑式）→ **真分布 130→227/914**（PP/Toad/Goobert/FB 等修复全部兑现）。
- 教训（第 4 次踩中）：定向 `--cases --force` 后 alignment.json 收缩 + 未重放场陈旧——
  每轮定向验后必须 `--compare-only` 恢复全量分布再退步检。
- 快照 op1_base.txt = 227 场（新基线）。

## op2 — getTranslatedName 译名面（Djinn Lamp damage_buff ×66 簇，缺口㉒）

- run576_r14 idx382：oracle type16 params.item=**""** vs gd "War Scythe"（全场 2:2，corpus
  抽样 300 场 60/60 全空）。
- 根因链：decomp ItemDescriptor.gd:116 `Util.tra(getName()+"_NAME")`；oracle
  Util.tra（Util.gd:213-219）对 tr(key)==key 的 miss 键**返回空串**；无头环境
  TranslationServer 未装载 → tra 恒 ""。
- 修复：gd_core/CoreItemData.gd + gd_core_py/gd_core/CoreItemData.py（py 镜像同步）
  getTranslatedName → 返回 ""（附行号证据）。
- 验证：定向 5 场（Djinn 簇+锚）4/5 三方一致；扩样本 5 场簇内 3/5 对齐；compare-only
  恢复后退步检 **新增 3（run576/600/776）退步 0** PASS。备份
  output/_round_patches/op2/。
- 下轮入口：Light Goobert Blind(109)×53 簇（run588_r18 等，O=13 层致盲超时 vs G=攻击
  落空——栈超时 vs 攻击的事件序差，疑 Buff timeout 到期 tick 面与 r25 resync 同族）；
  Stone×28；Burning Banner/Spell Scroll Dark Blind 族。

## op3 — Light Goobert Blind(109)×53 簇 A/B 试验（未生效，已回滚，深挖入口在案）

- 首分歧（run588_r18 idx576）：O=Light Goobert blind -13 层 stack_timeout @t=459
  (7.65) vs G=同事件 @t=460 (7.6667)——+1 tick；首两批 timeout（-1@5.5333、
  -9 批）两侧同刻，13 层批起漂。
- A/B 试验：gainTemporary stop+start 调用点 `_startTimer(duration, false)`
  （分支③ resync 关闭）→ 定向 5 场 idx 全不动 → **无效，回滚**
  （备份 op2/CoreBuff.gd.prefix 逐字节还原，复验基线恢复）。
- 关键观测（oracle 探针 op3，ORACLE_DEBUG 全 timer fire 序）：
  - blind 的 BuffTimer=PHYSICS（Buff.gd:32-36 Timer.new+one_shot+PHYSICS）确认；
  - oracle t7.65 处**无任何 BuffTimer fire**（44 个 BuffTimer fire 全序不含 7.65）——
    -13 timeout 事件不在 timer fire 帧上 ⇒ 深挖方向：onTimeout 链的
    delay≤0.01 递归/批次重启与 Util.time vs combatTime 时间戳源差；
  - py spy（复刻 verify 构造）：5.533 双 fire → 5.567 start(2.1833) → 7.667
    start(1.30) 链——数值与 gd 事件时刻自洽性待逐帧表对账。
- **下轮深挖入口**（按收益排）：①oracle 探针加 [BPOP] 等价打印（oracle Buff.gd
  onTimeout 处 print 全 temporaryStacks timeout 表）对 py [BPOP]（ORACLE_PROC_DEBUG
  已有）逐帧对账 13 层批的 timeout 计算与弹出时刻；②时间戳源核查：oracle 事件
  t 用 CombatTimer.combatTime，fire 评估用 Util.time——两钟在 harness 的相位差。
- 簇挂起，转 Stone×28 簇（O=Stone dmg12 vs G=Rapier dmg25 @6.22——数值面更清晰）。

## op5 — Stone×29 簇现场定格（会话交棒点，未下结论）

- 首分歧（run569_r11 idx126）：O=玩家 Stone dmg12 @6.22 vs G=Rapier dmg25 @6.3。
- Stone 攻击序：O 5 击（3.3/6.22/7.0/9.3/9.83，玩家+对手两把）vs G 3 击全对手侧；
  **G 玩家 Stone 自 tick152 起唯一一次 act=1 段（152-345）扣到 tt≈0 触发后，
  tick346 起 act=0 永冻**（tt=2.4931/icd 2.5042 从未递减）。
- 已排除：BagOfStones 生效（开战 ammunition=9000 ✓，t=3.233 首击 8999 ✓）；
  getCellsInLine 同构；getAffectedCellsAfterRotate_primary 动态钩子在位。
- 待查（下轮第一件事）：gd(Godot) 侧玩家 Stone tick346 act=0 的直接原因——
  候选：①doCooldownEffect 里 useStamina 消耗后 stamina 不足使后续分支未到
  activate(res)；②trigger() 内 _behavior_call 派发异常被吞；③activate(res) 后
  又被（Spiked Shield/其他 affected 物品）的 onPreDealDamage 链间接 deactivate。
- 仪器：item_trace 7 字段曲线在盘（ORACLE_ALIGN_TRACE=1 + ORACLE_ALIGN_CASES=
  run569_r11 + ORACLE_TRACE_ITEM=Stone；夹具需先全量 gen_fixture 恢复 51→914）。
- 注意：alignment.json/oracle_align_cases.json 当前为收缩态，全量里程碑前先
  恢复夹具与全量分布。

## op6 — Stone×29 簇根因定谳：OracleAlignBattle 装配时序（缺口㉓，一刀整簇）

- **根因链（CDSPY 插桩三跑定谳）**：玩家物品 place_one（OracleAlignBattle.gd:432）
  先于 combat.setup（:438 内才 `ctx.player=p` 绑定）→ 装配期 addToInventory→
  cacheAffectedCells→动态钩子 `BagofStones.getAffectedCellsAfterRotate_primary` 读
  `ctx.player.INVENTORY` 时 ctx.player 为 null → affected 空缓存 → onPrepare 的
  `setBagOfStones()` 不达 → Stone.ammunition 停 1（_readyInit 初值）→ 首击后
  ==0 → `onAfterEffectFinished(false)+consume` → **冷却永冻**（CDSPY 实证
  `deact Stone t=3.233 amm=0`）。py 引擎顺序本正确（先 setup 后装物品，引擎注释
  自证），故 py 腿无此病——纯 gd harness 缺陷。
- **排查弯路存档**：CDSPY 首跑（setCooldownActive+combatEnd 桩）无中段报——真凶
  在未桩的 `deactivateCooldown`（直写 false 不经 setter）；二跑补桩一击定谳。
  item_trace 的 act 列与 onAfterEffectFinished 链对照完整。
- **修复**：OracleAlignBattle.gd 把 `new_character(OPPONENT)`+`CoreCombat.new`+
  `setup(p,o)` 前置到玩家物品装配循环之前（对齐原版 Game.startHistoryRun 时序：
  角色先于任何物品入包；附 py 引擎互证）。对手物品装配循环位置不变（本就在 setup 后）。
- **验证**：定向 5 场（run569/582/609/662/673）**5/5 三方一致**；扩样 28 场
  **19/28 绿**（余 9 场首分歧后移至下一层：kernel 2 + rng-mechanism 7，新签名
  不再是 Stone origin 主导）；退步检 -b op5_base（265 场）：**新增 19 退步 0** PASS；
  回归 0-7 全过（SURVEY 基线 5 项随并行窗口 r4_2 moveItem 等净增同步更新：
  .new 57/.size 79/.push_back 75/.empty 57/Vector2 232，非本轮引入）。
- **快照**：op6_base.txt = 284 场。备份 output/_round_patches/op6/（CoreItem.gd
  原态+OracleAlignBattle.gd 原态；CDSPY 桩已卸并核零残留）。
- **下轮入口**：①Stone 残余 9 场新签名拆解（run610_r18 kernel 族首例）；②Light
  Goobert Blind×55（op3 深挖入口在案）；③装配时序修复可能连带其他动态 affected
  钩子物品（ShinyMantle/TimeDilator/RibSawBlade 同用 ctx.player.INVENTORY——
  本修复已一并生效，全量里程碑时观察其簇变化）。

## op7 — Light Goobert Blind×55 深挖（挂起，三层事实定谳）

- 仪器（临时，已还原核验）：oracle/Core/Buff.gd [BPOP] 桩（pid/U/CT/amt/to/arr 六列，
  BPOPSPY 闸）+ gd 既有 ORACLE_PROC_DEBUG [BPOP]。双探针 events 字节自证通过。
- **事实①（gd 侧）**：-13 弹出 t=7.666667、timeout=7.65——gd 的 timeout 值=grant
  时刻 ctx.time+3.0，ctx.time 与 combat_time 同 tick 差 1 步（physicsTick ① 推
  time、④ 推 combat_time，判定③ 读 time=新值）。
- **事实②（oracle 侧）**：-13 事件 t=7.65（timeout=true）与 BPOP 弹出 CT=7.60
  **差 3 ticks**——onTimeout 入口读 Game.combatTimer.combatTime 与事件时间戳
  读取不一致，机制未明（候选：事件非该次弹出产出/时间戳延迟创建/harness 时钟
  实例差）。batch 自检复跑（U=43.68/78 第二三遍）已识别排除。
- **事实③（相位）**：oracle U 与 CT 恒差 1 tick（BPOP 全行实证）——U 在 tick 步骤①
  推进、CT 在④，fire 评估⑥⑦ 读 U=新、CT=旧。
- 挂起原因：②的机制钉死需 CombatLog.logEvent 全链插桩（changeCurrentLogShowLabel
  →logEvent→getTimeStamp 三点时刻对照），预算超本轮。与 op3 深挖入口①②合并。
- **簇挂起，转攻**：gd_core_py-transpiler 90 场（纯转写面，无 oracle 深挖成本）
  / Crown invulnerable_end×17。

## op8 — transpiler 首例复核（run591_r13）与转簇决定

- 旧产物（gdcore 12:46）把 run591 误标 gdcore≡oracle 但 py 分歧——--force 重放后
  **真首分歧=oracle_vs_gdcore idx48**：oracle 有 gem 毒（ChippedEmerald×2 挂 DS，
  parent=DS 攻击）而 gd 无。又一例陈旧产物误向。
- py in-process 直证：gem onAttack 被调 4 次 hit=True、getGemMode=Weapon、连接在位、
  getNextFreeLabelPosition label_rng=True 正常——**py 腿机制完整**；roll 成败由
  chanceRng 链位决定（35%），gd/oracle 链位差 1-2 抽致一真一假。属链位族非转写族。
- 结论：transpiler 90 场多为此类误标（陈旧产物+链位差），真转写缺陷面已薄。
  转攻：全量里程碑（断点续跑）兑现 op6 装配时序修复的连带收益——ShinyMantle/
  TimeDilator/RibSawBlade 等同用 ctx.player.INVENTORY 的动态 affected 物品簇。

## op8 补记 — 全量里程碑（297/917，op6 连带收益兑现）

- 断点续跑式全量（清产物重放）：**aligned 297/917**（op6 基线 284 + 13 新增，
  退步 0）：ShinyMantle/TimeDilator/RibSawBlade 等动态 affected 物品簇兑现。
- 分布变化：gdcore≡oracle 但 py 分歧 90→**2**（op8 判读证实——transpiler 族
  绝大多数是陈旧产物误标，真转写缺陷几乎清零）；gd_core-kernel 59→85（分类
  迁移：原 rng 族按新签名重分）；rng-mechanism 531。
- 快照 op8_base.txt = 297 场。
- 新簇序：LG Blind×26（挂起中）→ Crown invuln_end×16 → Spell Scroll Dark×16 →
  Battery Activation×15。Blind 三簇（LG/SSD/BB）疑同根因（stack timeout 面）。
- 下轮入口：Crown invuln_end×16（r25 resync 残余 +1 tick 族，有 op7 三层事实
  与 BPOP 仪器沉淀，机制同构可复用）。

## op9 — Crown invuln_end×16 定格（会话交棒点，+1 tick 族第三例）

- 首分歧（run601_r18 idx264）：两侧事件序完全同构（3.3 start / 5.15 start(延长) /
  5.333 end / 末 end），唯末 end 时刻 O=7.167 vs G=7.183（+1 tick）。
- 算术：延长支 start@5.15 → end-start：O=2.017（=2.0+1 tick ✓ r25 重同步模型）、
  **G=2.033（=2.0+2 tick，多 1）**。
- 定格：gd CoreCharacter.makeInvulnerable 延长支（:1351+ `_invul_left = invuDur +
  _invul_left`）与 _invul_resync/tickPhysicsTimers 的组合在某场景多 1 tick——
  与 op7 LG Blind 族（gd timeout 多 1-2 tick）机制同构，疑同一根因的 invu 表达。
- 下轮入口：①读 gd tickPhysicsTimers 无敌段+延长支全链，找第 2 个 +1 来源
  （候选：延长时 _invul_resync 未置位 / instant 误触发 / 首次支 resync 与延长
  叠加）；②与 op7 三层事实合并——Blind 族的 gd 侧 -13 弹出 t=7.6667（timeout
  值 7.65+1 tick）与本族同签名，**一次修复可能连清 Blind 三簇+invu 簇（~58 场）**。
- 仪器复用：BPOP 桩模板（op7 已还原，模板在 git 无——需重加时照 op7 台账六列
  格式）；CDSPY 桩模板（op6，CoreItem setCooldownActive/deactivate 双点）。

## op10 — Crown invuln_end×16 首攻双修（307/917，退步 0）

**修① fire 链再授予直接充电**（gd_core/CoreCharacter.gd tickPhysicsTimers 无敌段
fire 分支，invulnerabilityEnded() 返回后清 `_invul_resync/_invul_instant`）：
- 证据（run601_r18 idx264）：King Goobert 无敌到点 → invulnerabilityEnded 信号链内
  Crown checkTrigger 同帧再授予（start 事件 parent=invuln_end）。oracle drive_timers
  到点支「处理器重启 → e[0]=get_time_left() 直接计时」（oracle_fight.gd:905-910）
  无重同步帧 → 首扣次帧、121 抽（2.0 浮点残差恒 +1 tick，python 实测 2.0→121/
  3.8→229/0.8→48）→ O=7.166667。gd 首支 :1345 无条件置 resync → 次帧才消费 →
  首扣 N+2 → G=7.183333。
- 关键区分（registry 槽位语义）：授予来源槽位晚于 InvulnerabilityTimer 槽
  （物品计时器 tickTimersPass/更晚相）→ oracle 次遍才重同步 → +2 tick（双侧本就
  一致，如 run601 id210 5.333333=3.3+2.0+skip+FP）；fire 链内/更早槽位 → 当遍发现
  无 skip → +1。gd 单旗标模型只对「外部授予」消费正确，fire 链内多 1。

**修② activateItems 角色级计时器旗标清扫**（gd_core/CoreCombat.gd activateItems
末尾 + CoreCharacter.resetTimersSync() 新增 + CoreBuff.resetTimersSync() 新增）：
- 证据（run765_r18 idx40）：开战序列 combatStart 钩子里 Crown checkTrigger 授予
  （事件 t=0）→ oracle rebuild_timer_registry（oracle_fight.gd:950-975）在
  activateItems 之后、首 tick 之前把**全部** Timer 重建 [left,left] → 首遍
  eng==e[1] 当帧即扣 → 121 抽 → O=2.016667。gd 旧行为只抹物品计时器
  （item.resetTimersSync + _fatigue_resync），角色级 _invul_resync 存活 → 首 tick
  跳扣 → 122 抽 → G=2.033333。
- CoreBuff.resetTimersSync 对齐 CoreTimer.resetSync 语义（清 resync/instant；
  停走态 _timer_last_dur=-1 回 ③ 支）。

**验证**：15 场 --force 重放（gd_to_py 重转写后双侧）→ 10/15 三方一致（gd 侧
修复前 0/15）→ compare-only 全量 **307/917**（297→307，退步 0）→ 快照
r10_crown.txt。py 镜像由 gd_to_py 全量重生成（无手改）。

**残余（下轮入口）**：
1. Crown 残余 3 场新亚形：run1526_r18 idx149 t=156（2.6s，早段）、run1322_r18
   idx397 t=704、run1184_r12 idx604 t=783（Blueberries mana 触发授予但 oracle 零
   skip——疑 ① 同 dur 继续支/直充语义，需 [INVU] 桩或前批 grant 史）。
2. run765_r18 新根 idx373 t=427 Thornbloom DealDamage；run601_r18 新根 idx1738
   t=2527 Strong Vampiric Potion/unhealing —— 均为无敌清后露出的独立根，重聚类后再攻。
3. **LG Blind×26（仍居首簇，run588_r18）**：批弹锚 7.65 双侧施加史全同，gd 弹批
   +1 tick。5.5667 批重启 delay=2.0667 直接充电算术双侧应全同——需 ORACLE_PROC_DEBUG=1
   单场 gd 复跑取 [BGAIN]/[BPOP] 全精度 delay/timeout 对数（仪器已就位，CoreBuff
   :409 打印现成）。SSD×16（run646_r18 缺 t=144/145 双事件）随后。

## op11 — f32 截断层（Timer::time_left 是 float32）+ 伤害面定格（挂起）

**修① CoreBuff._startTimer 过 f32**（gd_core/CoreBuff.gd 新增 `_f32`，PoolRealArray
单元素写读；py 镜像 `return f32(x)`——rt.py 已有 `_F32=struct.Struct("<f")`）：
- 根因定谳链：probe3b（%.15f 桩，events==语料逐字节）真场三值
  U_restart=22.616666667535899 / earliest=24.700000000869284 / delay=2.0833333333333854；
  python 复算 delay 顺序减 **126 次**才过零，但 U_restart 顺序加 **125h=U_pop 精确相等**
  （125 遍 fire）。矛盾解：Godot C++ `Timer::time_left` 是 float32，`start(t)` 实参
  f32 截断（f32(2.0833333333333854)=2.0833332538604736 < 125h）→ oracle 恒 125 遍；
  gd 纯 double 保留 ~1e-14 尾差 → 126 遍。刀锋 delay≈N×h+ε 的 ε 被 f32 冲掉。
- 收益：run588_r18 类 tick 面清（LG 簇 26 场里 2 场全绿：run1042_r12/run1388_r10），
  其余 24 场推进到 cleanse 数量面（见下）。**aligned 307→309/917，退步 0**。
- LG 残余 13 场新首分歧=数量差（O 弹批 -7 vs G -6，中缝 Chipped Amethyst
  `cleanseRandomDebuffs(1)` 随机目标选择面）——独立缺陷，非 tick 面。

**修② CoreTimer.start 过 f32**（gd_core/CoreTimer.gd `_f32t`；wait_time 与 dur 双点）：
- 动机：run818_r5 伤害面 16vs17 深挖——双侧 [DSROLL] 桩对照（DamageSource.randDamage
  → origin.damageRangeRng.randIntRange 含 acc 修正）：GD 66 抽 vs OR 96 抽，首抽
  t=0.8167(49 ticks) vs 0.8333(50 ticks)——物品冷却首触发差 1 tick → 攻次/acc 全漂。
- 结果：f32 修后 run818_r5 仍 idx70 16vs17——真根=**装配期全局链位差**：rng 对位
  显示两侧构造抽（BalancedRng 期望值 0.2,-0.2）序列在 ctor[16] 分叉，玩家 Flame
  Whip 的 3 次 [4,16] 抽（FlickerAnimation 系 callDelayed/speed 抽）插入位置差 4 位
  （oracle ctor16/19/22 vs gd ctor20/23/26）→ 装配期冷却抖动抽（0.975,1.05）链位差
  → dur 值差 → 首攻差 1 tick。rng_state 注入只钉战斗期，装配期两侧独立跑。
- **挂起**：伤害面（Flame Whip×14/Hammer×11/Dragon Knight×10 等 DealDamage 152 首分歧
  大头）属「装配期 Flicker 抽序」专项——需对齐 Flicker/装饰动画抽在 place 序中的
  确切时机。CoreTimer f32 语义正确（引擎真 f32），保留（全量 309 无退步）。

**验证**：compare-only 全量 309/917（+2）、退步 0（基线 r10_crown 307→309）、快照
r11_f32.txt。探针卫生：oracle/Core/Buff.gd、oracle/Utility/DamageSource.gd、
oracle/Items/Item.gd、gd_core/CoreItem.gd、gd_core/CoreDamageSource.gd 全部还原
（备份 output/_round_patches/r11_lg/ 与 r10_oracle_stubs/，grep DSROLL/BGAIN2/BPOP2/
BRES 全清）。py _f32/_f32t 手改 rt.f32——**gd_to_py 固化待做**（下次转写会冲掉）。

**下轮入口**：①SSD Blind×16（run646_r18 gd 缺 t=144/145 自身+反弹致盲双事件——
触发条件面，SpellScrollDark.gd 双侧源已对读过一致，疑 canAffect/getAffected 面）；
②cleanse 面（LG 残余 13+BB 12：cleanseRandomDebuffs/removeRandomBuffs 随机目标
选择）；③装配期 Flicker 抽序专项（伤害面总根）；④gd_to_py PoolRealArray→f32
固化规则（防转写冲掉手改）。

## op12 — SSD 簇×19 双修（313/917，退步 0）

**修③ hasType 补 dynamicTypes**（gd_core/CoreItem.gd:309）：
- 原版 Item.gd:3594 `type in descriptor.types or type in dynamicTypes`；gd 只查前者
  → CorruptedArmor/Cthulhu 的 addDynamicType(Type.Dark) 感染链全断。

**修④ addDynamicType/removeDynamicType tail 补 inventory 广播**
（gd_core/CoreItem.gd:1546-1563）：
- 原版 tail `inventory.onItemTypeChanged(self)`（Inventory.gd:971-972 emit
  item_type_changed → 全部已放置物品重判受影响集）是**功能信号**；gd 原先只走
  ctx.hooks（UI）漏广播 → 后 place 物品的动态类型感染无法回流到先 place 物品的
  currentAffectedItems → cacheAffectedItemsForCombat 快照缺员。
- 定谳链（run646_r18）：SSD onPrepare sec 应=[CA, Shiny Mantle] n=0.30（oracle
  探针 [SSDPREP-O] 实证），gd=[CA] n=0.15 → dur 差 → 首触 O 2.4s vs G 2.8s →
  t=2.4 双致盲事件缺失。修后 [SSDPREP] n_sec=0.3 sec=[CA, Shiny Mantle] 与
  oracle 全同。
- SSD 簇 19 场：4 全绿（run650/651/652/1255），run646 首分歧 idx75→242（后续
  独立根 Magic Mirror 反射序差），其余推进。**aligned 309→313/917，退步 0**，
  快照 r11_ssd.txt。

**gd_to_py 固化 PoolRealArray→rt.f32 规则**（tools/gd_to_py.py 后处理段）：
三行模板（2-tab 缩进）整体替换为 `\t\treturn f32(x)`；转写输出
「PoolRealArray→rt.f32 2」命中核验；幂等（重转写不再冲掉手改，SSD 19 场
NameError 教训固化）。

**下轮入口**：①SSD 残余 15 场重聚类（idx 推进后新根：run646 idx242 Magic Mirror
反射序差 / run670 gd_core-kernel Magic Mirror）；②cleanse 面（LG 残余 13+BB 12：
Chipped Amethyst cleanseRandomDebuffs 随机目标选择）；③装配期 Flicker 抽序专项
（伤害面总根：Flame Whip×14 等 DealDamage 族——装配期全局链位差 4，rng_state
注入只钉战斗期）；④Crown 残余 3 亚形（run1526/1322/1184）。

## op12b — cleanse 面线索（挂起）+ Blueberries×12 新簇线索

- cleanse 面（run668_r18 O 弹批 -7 vs G -6，中缝 2.6 Chipped Amethyst -1）：
  pickRandomStacks/loseStacks/cleanseRandomDebuffs 三函数双侧逐行同构已核
  （Item.gd:5422/5494/5516 vs CoreItem.gd:2479+；Buff.gd:199 loseStacks
  permanent 优先→temporary farthest）。getDebuffs 序同构。
  待查：O 侧 -1 后组1.amount 仍 7（弹 -7）而 G 侧 7→6——疑 oracle 的 -1
  事件产生路径非 loseStacks（cleanseProtection/resisted/used 分支）或
  pickRandomStacks 选中的 stackType 键序差（Dictionary 键序=插入序，
  stacks 键序由 target.getStacks 遍历 getDebuffs 序决定——两侧同构，
  需桩打印 oracle pickRandomStacks 的 stacks.keys() 与选中值）。
- Blueberries Mana×12（run810_r12 idx194 t=361）：同 tick 事件序差
  （O 首事件 Blueberries mana+1 vs G 首事件 Carrot Activation，后续
  Pine Protector heal 序差）——物品冷却 fire 序/tickTimersPass 遍历序族，
  与装配期链位差（Flicker 抽序）疑同根，并入伤害面专项。

## r12（OffPeak 续4 会话1）— 伤害面跳帧试修回滚 + cleanse 面双差定位（313 持平，熔断计数 1）

**试修（已回滚）**：激活帧物品冷却跳帧闸（CoreCombat._skip_first_item_tick）——
动机：[ORSPD]/[GDSPD] owner 桩实证双侧首扣帧差。实测后果：玩家侧对齐但对手侧
过头（镜像反转：oracle Spiked Shield 反伤@0.8167 早于 FW 首攻@0.8333，gd 双事件
整体推后 1 tick），时刻面全坏 → 按协议回滚。回滚后 compare-only 313 持平、退步 0。

**实证沉淀（本轮核心产出，全部双桩对照）**：
1. **首扣帧逐 owner 对齐**（修后复测）：owner1/owner3 首扣帧双侧都=0.033333（tick2）
   ——冷却扣减面本已同构，跳帧方向错误。
2. **trigger 时刻双侧一致**：[GDCD]/[ORCD] 首 trigger 的 oldIter=1.653383 /
   oldTrig=-0.02895 双侧全同——iterationCooldown/triggerTime 同值同史。
3. **真分歧面**：oracle 首攻（miss，damage 0）@0.816667 tick49、二攻（hit 16）
   @0.833333 tick50；gd 修前时刻面与 oracle 全同（idx<70 咬合），分歧在 **damage
   值 16 vs 17**=BalancedRange.acc/roll 值差 → 0.8167 帧 accuracy 判定双侧差
   （oracle miss 不 roll damage、gd roll——DSROLL 首行 gd t=0.8167 out=9 vs
   oracle 该帧零 trace 抽=oracle accuracy 走 chanceRng/flip 不可见面）。
   下轮入口：applyBonusChance/accuracy 参数面与 chanceRng.roll 的平衡状态差
   （expectedWins 构造同值，wins 计数或 bonusChance 计算差）。
4. **装配期 U 时轴澄清**：oracle log @45.683 批=tick1（装配+激活帧）；装饰
   Flicker（0.1/3 域 9 抽）与物品 Flicker（4/16 域 6 抽）都在该帧，且 tscn
   实证 [4,16]=Flame.tscn FlickerAnimation minDist/maxDist；对手侧三抽双侧
   全同（11.623924/13.412558/14.906509），玩家侧三抽双侧不同值——玩家 place
   段链位差仍开放，但因 rng_state 注入抹装配差，非战斗期判据面。
5. **cleanse 面双差**（run668_r18 [ORPICK]/[GDPICK] 双桩）：
   ① t=2.6 keys=[109,110] n=1 → OR picked=110 vs GD picked=109——
   pickRandomElement 同域同 size 但链位差 1（2.583 帧 keys=[110] 单元素双侧
   picked=110 同 → 分叉在 2.583-2.6 间或 irange 实现差）；
   ② Amethyst gem 冷却触发时刻 OR 4.75/5.083 vs GD 4.8667/4.9——gem 冷却
   推进/首触发面差（与伤害面冷却族同源候选）。

**仪器卫生**：oracle Items/Item.gd、Items/Animations/FlickerAnimation.gd、
Utility/DamageSource.gd 与 gd CoreItem/CoreDamageSource/CoreCombat 全部还原
（备份 output/_round_patches/r12/，md5 核验）；gd_to_py 重转写；py 面 0 残留。
compare-only 313/917、退步 0。

**下轮入口**：①Flame Whip accuracy 判定面（applyBonusChance/chanceRng 平衡
状态，用 chanceRng 桩打双侧 roll 序列与 expectedWins/wins）——预期连清伤害面
40+ 场；②cleanse 双差（pick 链位差 1 + gem 冷却时刻差 7 ticks）；③SSD 残余 15
重聚类；④Crown 残余 3 亚形。

## r13（OffPeak 续5，环境截断交棒）— accuracy 桩三连定谳（313 持平，熔断计数 2）

**本轮实证（全部 events 字节自证）**：
1. **[PP1] 全物品首 _physics_process=tick2 统一**（oracle Items/Item.gd 桩）：
   有冷却物品（Flame Whip/Chili/Banana/Shiny Shell 每遍 8 件）首回调全在
   t=0.033333；无冷却物品（Fire Pit/Piggybank 等）永不回调。无混合分布——
   r12 的「Spiked Shield tick1 起扣」推测作废。
2. **[HIT] accuracy 判定桩双差实锤**：GD 每件 Flame Whip 打 **2 次**攻击
   （t=0.816667 + 0.85），oracle 每件仅 **1 次**（0.833333/0.866667）——
   gd 多一次 0.8167 攻击（恰早 oracle 唯一攻击 1 tick）。accuracy 参数面
   全同（acc=90、wins=1、eW=1.1→0.7 演化同）——**不是 accuracy 值差，
   是 gd 冷却 fire 早 1 tick**（gd tick1 起扣 49 帧到零 vs oracle tick2
   起扣 49 帧到零）。跳帧修方向本正确；r12 回滚动机（SS 反伤错位）需重审：
   oracle 0.8167 帧的 [SS 104 spikes+1, FW damage0, SS 14, Act×2] 疑为
   **另一伤害源**（FW 的 Spikes 型 damage0？canMiss=false 不入 HIT 桩）——
   下轮用 dealDamage 全入口桩（不滤 canMiss）裁决 0.8167 帧真身。
3. **GDDC 基类桩被多态绕过**（CoreItem.doCooldownEffect 桩 0 行）：
   GDScript 虚分派直达 Weapon 覆写版——物品层桩须装在具体脚本或 trigger() 层。
4. gd 双发的第二发（0.85）与 oracle 单发（0.8667 for 第二件）t 序：gd
   [0.8167, 0.85] vs or [0.8333, 0.8667]——整体各早 1 tick，非插入式多攻。

**结论**：伤害面真根回归「冷却首扣帧差 1」（gd tick1 vs oracle tick2），
但修复需同时解决 r12 发现的连锁错位——正确修法候选：①gd 物品冷却 tick1 跳帧
（重施）+ 查 SS 反伤错位是否实为同根（0.8167 的 damage0 事件源）；②或
preCombatStart 后 triggerTime 初值 +1 tick（等价但只影响首循环）。

**卫生**：oracle Core/Character.gd、Items/Item.gd、gd CoreItem/CoreCharacter
全部还原 md5 核验（备份 output/_round_patches/r13_*）；gd_to_py 重转写；
compare-only 313/917 退步 0。

**下轮入口（优先序）**：①dealDamage 全入口双桩（不滤 canMiss，打 origin/
t/hit/damage/canMiss）裁决 oracle 0.8167 帧的 damage0 真身 → ②依裁决重施
跳帧修（CoreCombat._skip_first_item_tick 三处编辑模板在 r12 台账）或改
triggerTime 初值法 → ③Flame Whip 簇 14 场 --force 验证 → ④续 cleanse 双差
/SSD 残余/Crown 残余。熔断计数 2——下轮若无增长即熔断（3 轮上限）。


## r14 第 1 批排查（OffPeak 续6，批量批 1/∞——只排查+切通道，未改任何运行面代码）

**digest 簇**：Battery Activation×15 / ManaOrb Mana×14 / 伤害值超簇（Rapier×14+FW×14+Hammer×11+DK×10+FalconBlade×8+MagicStaff×8）/ LG Blind×14+BB Blind×12。
**代表场事件对读+dealDamage 全入口双桩（run818_r5，桩已还原 md5 核验，探针 events 与冻结语料逐字节同）**：
1. **r12/r13「gd 冷却 fire 早 1 tick」定谳为时间基准错读**：frozen events idx<70 双侧
   逐字节同构（含 0.8167 帧 [SS+1, FW dmg0, SS14, Act×2] 与 0.8333 帧 dmg16 双侧同值）；
   oracle takeDamage 首调用 Util.time=0.8333333342（f32 杂质）vs 事件 ts=0.816667
   （事件 ts=triggerEvent 调度时刻）；gd ctx.time==事件 ts。跳帧修方向（重施
   _skip_first_item_tick / triggerTime+1）**作废**。
2. **伤害值面真分歧**=t=5.05 同帧同调度 randDamage 值差 16vs17 → 隐形 rng 链位差。
   首嫌疑：3.7333-3.8 窗口 oracle 非物品源 takeDamage（反伤族）调用 2 次 vs gd 1 次
   （[ORDD]/[GDDD] 结构对读 idx5）；且 oracle 全场 177 调用 vs gd 116（大量 oracle
   调用不落事件——疑 fightEnded 闸/静默路径，待出口桩）。
3. **Battery×15**（run691_r18 idx472 t=5.0167）：gd 每 Battery 双 Activation+Resistor
   即时充能（107 amt3 立现）vs oracle 单 Activation 充能延迟到达——物品脚本双侧同构，
   分歧在 sendCharge/充能旅行时序基建（CoreItem.gd）。
4. **ManaOrb×14**（run604_r10 idx64 t=5.75）：gd 缺 +1 mana 触发事件（后续全漂移）；
   物品脚本同构，分歧在 onItemActivated rollChance/connectForCombat 运行面（CoreItem.gd）。
5. **LG Blind×14**（run668_r18 idx401 t=7.40）：timeout 同帧 stack 数差 -7 vs -6
   ——施加史/堆栈计数面（CoreBuff.gd）。

**通道分工表（文件面互斥；gd X.gd 与 py 镜像同一通道）**：
| 通道 | 文件面 | 靶 | 代表场 |
|---|---|---|---|
| A | gd_core/CoreCharacter.gd(+镜像，CoreDamageResult.gd 如需) | 伤害值超簇 ~73 场：反伤链出口桩（takeDamage 出口打 hit/damage/isDead+applySpikes 入口打 getSpikes/spikeDam）定谳后修 | run818_r5,run628_r14 |
| B | gd_core/CoreItem.gd(+镜像) | Battery×15 充能时序 + ManaOrb×14 触发基建 | run691_r18,run604_r10 |
| C | gd_core/CoreBuff.gd(+镜像) | Blind×26 堆栈计数/施加史 | run668_r18 |
| D(预留) | gd_core_items/ 纯物品脚本 | 物品层小修（A/B/C 定谳后如需） | — |

**卫生**：oracle/Core/Character.gd、gd_core/CoreCharacter.gd 桩还原 md5 核验（备份
output/_round_patches/r14_batch1/）；gd_to_py 重转写（幂等）；夹具重生成后 total
917→914（3 个 gdcore 缺产物场被预检剔除），aligned 313 不变、退步 0（基线
r11_ssd.txt）；compare-only 口径见 alignment.json。**下轮入口（批 2=修复批）**：A/B/C
三通道并行各修各靶 → 每通道独立 --cases --force 验证 → 全量 compare-only + 退步检。
熔断计数 2——本批为排查，修复批若无增长即熔断。


## r14 第 2 批排查（OffPeak 续6，批量批 2/∞——通道 A 根因链闭环定谳，零码改）

**digest 簇同批 1**（ManaOrb×14/Rapier×14/LG Blind×14/FW×14/Battery×14…）。5 代表场中深挖 run818_r5+run604_r10。
1. **批 1「oracle 多一次反伤调用」解构为复跑伪象**：oracle 单场自动 adjacent 复跑
   （[5] adjacent 行切界），ORDD 177=run1 120+复跑 58 两遍混流；gd 单遍 116 与
   oracle run1 的 116 次 takeDamage **逐位同构**——反伤/spikes 结构面双侧全同，
   CoreCharacter 出口桩（hit/dmg/hpDmg/EARLY-DEAD×0）+applySpikes 桩（spikes/trig/
   fired）实证无结构差。takeDamage 出口 dmg≠事件 dmg=事件创建后 handler 改写，非对齐面。
2. **randDamage 状态桩（BalancedRange.acc，注意真类=BalancedRange.gd 仅有 acc，
   非 BalancedRandom.gd）**：首两笔 FW roll acc 演化双侧同构；roll#2 raw 抽分歧
   （O raw=9 vs G raw=8，域 [6,10]）——acc 无差，**全局流位置差**。
3. **全局流逐抽对齐**（oracle ORACLE_DEBUG rng_log_first.txt + gd ORACLE_ALIGN_TRACE
   rng_trace.txt，值序双指针+重同步）：首 roll 邻域逐抽值全同（含 randInBox/0.9-1.1
   域）；首笔真分歧=**oracle 多一笔 randf_range(0.3,0.8)=>0.774882 @t=29.217**（战斗
   4.18s，恰在 5.05 攻击链前，[rng-eat] delayedphase=True），gd 该位无此笔→流移位
   →后续全错位→5.05 dmg 16vs17。
4. **(0.3,0.8) 域定源**：Flame.tscn FlickerAnimation（minSpeed=0.3 默认/maxSpeed=0.8
   tscn 覆写）；调用方 oracle Items/Animations/FlickerAnimation.gd:14
   （onAnimationEnded→callDelayed(playAni, rng(minDist,maxDist))）+:17-19（playAni 抽
   speed）；[cd-fire] playAni created=24.217=战斗起点——**延迟值系装配期抽**，因装配期
   链位差（r11 定谳）两侧延迟值不同→战斗期 speed 抽插位不同→流移位。gd 镜像
   CoreItem.gd:800-856 同构存在，唯延迟值取自己的装配抽。
5. **泛化**：run604_r10（ManaOrb 簇）trace diff——装配期 t=29.133 同位 (0.9,1.1) 抽值
   即分歧（O 1.092763 vs G 1.019699）——装配期值差普遍，Battery/ManaOrb 簇同根候选强。

**通道重划（文件面互斥）**：
| 通道 | 文件面 | 靶 | 状态 |
|---|---|---|---|
| A | gd_core_test/OracleAlignBattle.gd + gd_core/CoreItem.gd(_readyInit/flicker 段) + gd_core/CoreCombat.gd(装配序段)+py 镜像 | 装配期抽序对齐（Flicker callDelayed 延迟抽值/插位）→ 伤害值超簇 ~73 场+预期连带 ManaOrb/Battery | 根因链闭环 |
| B | gd_core/CoreBuff.gd(+py 镜像) | Blind×26 堆栈计数（批 1：-7 vs -6） | 待探针 |
| C(预留) | gd_core/CoreCharacter.gd(+镜像) | 已解构无需修（反伤面全同）——转作他靶预留 | 空 |

**卫生**：oracle Core/Character.gd、Utility/DamageSource.gd 与 gd CoreCharacter.gd、
CoreDamageSource.gd 四桩还原（Character 备份 md5 核验==批 1 净版；DamageSource 备份
时点含残桩，已手剥回原文，grep 四文件 0 探针残留、仅存基线 buffType 桩行）；gd_to_py
重转写；探针 events 与冻结语料逐字节同（run818 a5ae8db7/run604 29e989e×2）；夹具
恢复 914；aligned 313、退步 0（r11_ssd.txt）。
**下轮入口（批 3=修复批）**：通道 A 落修——对 run818_r5 先让 gd 装配期 Flame Flicker
callDelayed 延迟抽与 oracle 同值同位（或逐物品同值注入），--force 验证 dmg16==16→
再 --cases 伤害簇 5 场→全量 compare-only+退步检。熔断计数 2：修复批无增长即熔断。


## r14 第 2 批排查（OffPeak 续6，批量批 2/∞——通道 A 根因链闭环定谳，零码改）

1. **批 1「oracle 多一次反伤」解构为复跑伪象**：oracle 单场自动 adjacent 复跑，
   ORDD 177=run1 120+复跑 58 混流；gd 单遍 116 与 oracle run1 的 116 次 takeDamage
   逐位同构——反伤/spikes 结构面双侧全同（出口桩 hit/dmg + applySpikes 桩实证，
   EARLY-DEAD=0），CoreCharacter 无需修。
2. **randDamage 状态桩**（真类=BalancedRange.gd 仅 acc，非 BalancedRandom.gd）：
   acc 演化双侧同构，roll#2 raw 抽分歧（O raw=9 vs G raw=8，域 [6,10]）→全局流位置差。
3. **全局流逐抽对齐**（oracle rng_log_first.txt+gd rng_trace.txt 值序双指针）：首 roll
   邻域逐抽全同；首笔真分歧=**oracle 多一笔 randf_range(0.3,0.8)=>0.774882 @t=29.217**
   （战斗 4.18s，5.05 攻击链前，delayedphase=True），gd 该位无→流移位→dmg 16vs17。
4. **(0.3,0.8) 定源**：Flame.tscn FlickerAnimation（minSpeed=0.3 默认/maxSpeed=0.8）；
   FlickerAnimation.gd:14 callDelayed(playAni, rng(minDist,maxDist))+:17-19 speed 抽；
   [cd-fire] playAni created=24.217=战斗起点——**延迟值系装配期抽**，装配期链位差
   （r11）→两侧延迟值不同→战斗期 speed 抽插位不同→流移位。gd 镜像 CoreItem.gd:800-856
   同构，唯延迟值取自己的装配抽。
5. **泛化**：run604_r10（ManaOrb 簇）装配期 t=29.133 同位 (0.9,1.1) 抽值即分歧
   （O 1.092763 vs G 1.019699）——Battery/ManaOrb 簇同根候选强。

**通道重划（文件面互斥）**：A=装配抽序面（gd_core_test/OracleAlignBattle.gd +
gd_core/CoreItem.gd _readyInit/flicker 段 + gd_core/CoreCombat.gd 装配序段+py 镜像）
→伤害值超簇 ~73 场+连带 ManaOrb/Battery，根因链闭环；B=gd_core/CoreBuff.gd(+镜像)
→Blind×26 堆栈计数（批 1：-7 vs -6），待探针；C(预留)=gd_core/CoreCharacter.gd
（反伤面已证全同，转作他靶）。
**卫生**：四桩还原（Character 备份 md5==批 1 净版；DamageSource 备份含残桩已手剥回
原文，四文件 0 探针残留仅存基线 buffType 行）；gd_to_py 重转写；探针 events 与冻结
语料逐字节同（a5ae8db7/29e989e）；夹具恢复 914；aligned 313、退步 0（r11_ssd.txt）。
**下轮入口（批 3=修复批）**：通道 A 落修——run818_r5 gd 装配期 Flame Flicker 延迟抽
与 oracle 同值同位（或逐物品同值注入）→--force 验 dmg16==16→伤害簇 5 场→全量+退步检。
熔断计数 2：修复批无增长即熔断。


## r14 第 2 批排查·续（OffPeak 续6——定向重放复核+装配位差 raw 级定谳+Blind 面语义定位；零码改）
**定向重放复核**（alignment_r1_wf.json）：run818_r5 首分歧仍 idx70 t=5.05 dmg16vs17、
run604_r10 仍 idx64 t=5.75 缺 mana+1——确定性复现，无回归无进展。
**①通道 A raw 级定谳**（oracle rng_log_first.txt + gd rng_trace.txt 逐 raw 双指针，
run818_r5）：主流 raw 序列全场恒同（seed 注入有效）；分歧=**消费序**——oracle 玩家侧
3 笔 Flicker [4,16] 延迟抽插在装配 raw16/19/22（ctor 抽之间），gd 同 3 笔晚 4 raw
（raw20/23/26），窗口内 ctor 抽互换 raw → ctor 值差（BalancedRng expectedWins）→
战斗期插位差 → 5.05 dmg 差。raw 级证据：G20 flicker 值 10.226433 的 raw 0.518869 ==
O20 ctor 值 -0.007548 的 raw（同 raw 异消费者）；idx62 起（对手侧）双侧同位同值
（11.623924/13.412558/14.906509，批 1 已证）。**run604_r10 同构**：Connector (0.9,1.1)
O42/G46 晚 4 raw，次笔 99 同位——+4 位差泛化到 Flicker/Connector 两域。
**②修法方向（通道 A）**：gd 装配层把玩家侧物品 ready 抽（_readyInit 的
flicker/connector/gem 段，CoreItem.gd:800-856）从集中块改为随各自物品 ctor 内联
（oracle=子节点 _ready 紧随物品创建），位差归零后 raw 分配自然对齐；无需值注入。
**③通道 B（Blind×26）定位**：run668_r18 109 事件 16 笔全同构，唯 t=7.40 timeout
计数 O-7 vs G-6。t0 在 2.5667 唯一批 +7，2.6 CA cleanse -1 → **gd timeout 记剩余
6，oracle 记原批 7**（t1 多批随机净化双侧均 -8 旁证：净化未命中该批时两侧无差）
——timeout 移除计数语义差，oracle 侧语义=按批原始规模。probe 方向：oracle Core/
Buff.gd timeout→loseStacks 的 amount 来源 vs gd_core/CoreBuff.gd 对应段。
**通道表（文件面互斥）**：A=gd_core_test/OracleAlignBattle.gd+gd_core/CoreCombat.gd
(装配段)+gd_core/CoreItem.gd(_readyInit/flicker/connector 段)+py 镜像→伤害值超簇
~73 场+连带 ManaOrb/Battery；B=gd_core/CoreBuff.gd(+镜像)→Blind×26；冲突提示：
若 B 需动 CoreItem.gd 的 loseStacks/pickRandomStacks 则与 A 冲突——先做 A，B 的
CoreItem 面留批 4 串行。C=oracle/*.gd 诊断桩（只读定位不占面）。
**卫生**：本轮零码改零桩（仅 ORACLE_ALIGN_TRACE 环境重跑）；gd 产物 events md5 与
重放版逐字节同（run818 746aaf91/run604 25d403f0）；夹具恢复 917；aligned 313、
退步 0（r11_ssd.txt 实跑）。**下轮入口（批 3=修复批）**：A 落修（内联化）→
--cases run818_r5,run604_r10,run628_r14 --force 验 → 伤害簇扩验 → 全量+退步检；
B 探针（timeout amount 源）可与 A 并行（不同文件面）。熔断计数 2。

## r16 第 1 批排查（OffPeak 续6·批1，313/914 持平，排查批零码改）

1. digest：598 分歧场；最大 4 簇各 14 场=Mana Orb / Fancy Fencing Rapier /
   Light Goobert(Blind) / Flame Whip；次簇 Hammer11、Blueberries12、
   BurningBanner(Blind)12、DragonKnight10、FalconBlade8、MagicStaff8。
2. 通道 B 探针（run668_r18；oracle Buff.gd 临时三桩 BADD/BLOSE/BPOP，
   gd 用既有 BGAIN/BPOP；ORACLE_FIGHTS_ROOT→probe/r16_blind）：
   - 复现性：oracle 探针前缀 idx0-875 与冻结语料逐字节同（idx876 t=11.73 起
     分叉为**现存树漂移**——无桩同 env 复跑同位复现，非桩致；冻结语料仍为
     基准）；gd 探针与 gd 冻结产物全场零分歧。
   - 真分歧：gd 盲批添加执行晚 4-8 ticks（tgt0 7@ctx2.5833 vs oracle U2.5167、
     tgt1 8@2.6 vs 2.4667），事件戳双侧一致（2.5667/2.6）——相位差藏于
     delayed 执行时钟；到期 -7vs-6 是下游（gd 首批唯一故 2.6 CA -1 落其上）。
   - **r14「timeout 记批原始规模」语义差假设证伪**：双侧 loseStacks/
     onTimeout 同构（farthest-first、批内减 amount、onTimeout 取批 amount），
     CoreBuff.gd 无需修。
   - 遗留线索：oracle U=7.0667 一笔 used 消耗扣最远批（8@10.70→7，无事件）；
     2.6 的 CA -1 事件无对应 BLOSE → cleanseRandomDebuffs 疑走非 loseStacks
     路径/protect 支；后续批 schedule 整体错位（gd 9.2833×2/10.95×2 vs
     oracle 8.8667/9.1167/10.15/10.70/12.0）。A 连带候选：首触发时刻=
     f(ctor 冷却抽)，A 落地后必复测 run668_r18。
3. FFR run628_r14 对读：首分歧 idx37 t=0.95 纯值差（O8/G11），前缀全同
   （恒 +1 id 惯例差）——ctor 值差家族，归 A。
4. 卫生：oracle/Core/Buff.gd 还原 md5=2e053483…（==r10 净版备份）；gd_core
   零改动（无需 gd_to_py）；夹具曾遭 --cases 收缩，已按文档无 --cases 全量
   重建=914；aligned 313、退步 0（r11_ssd.txt 实跑）。探针产物 probe/
   r16_blind、probe/r16_blind_gd；桩跑日志存 _round_patches/r16_batch1/。

**通道表（文件面互斥）**：A=装配抽序内联化【修复就绪】gd_core/CoreItem.gd
(_readyInit flicker/connector 段)+gd_core/CoreCombat.gd(装配序段)+
gd_core_test/OracleAlignBattle.gd+py 镜像→FW14+FFR14+Hammer11+DK10+Staff8+
ManaOrb14+Battery14（代表 run818_r5/run604_r10/run628_r14）；B=触发相位面
【挂起：与 A 同文件，A 后串行】gd_core/CoreItem.gd 冷却/delayed 段→
LG Blind14+BurningBanner12+FalconBlade8（代表 run668_r18）；C=复验/退步检
【无代码面，可与 A 并行】仅 align 产物+alignment.json。
**下轮入口（批 2=修复批）**：A 落修（内联化）→ --cases
run818_r5,run604_r10,run628_r14 --force 验 → 伤害簇扩验 → 全量+退步检；
熔断计数 2：A 无增长即熔断。

## r16 第 2 批排查（OffPeak 续6·批2，314/914 持平+1，排查批零码改）

1. 批 2 修复已落地核验：通道 A 内联化在场（gd_core/CoreItem.gd:805-819
   flicker/connector/gem ready 抽内联==r1_fix1 快照）；定向重放 4/4：
   **run818_r5 三方一致**（aligned_set：新增 1 退步 0）；run604/run628/run668
   仍分歧。digest：Mana Orb14 / LG Blind14 / Battery14 / FFR13 / FW13。
2. 本批 raw 双指针定位（零码改零桩，纯 env 仪器 ORACLE_DEBUG+ORACLE_ALIGN_TRACE，
   ORACLE_FIGHTS_ROOT/ORACLE_ALIGN_OUT 全重定向 probe/r17_*；双侧 trace 复跑
   events 与各自冻结产物逐字节同）：
   - **run604 定谳**：装配 212 抽全对齐（A 修复生效）；唯一真分歧=单槽函数差——
     oracle randf_range(0.7,1.05)=OnionCutterAnimation.tscn:117-118
     minSpeed/maxSpeed，vs gd randf_range(0.8,1.2)=gd_core/CoreItem.gd:982
     硬编码（激活动画时长链）；各耗 1 抽、后继主流全同；值差→delayed 动画
     时长差→触发相位漂移→5.75 魔法+1 错位（O@5.75 vs G@5.9833，14 ticks）。
     gd 多 3 行 Gopen/Gshuffle 系 shuffle-replay 日志标记，无主流消耗差。
   - **run628 定谳**：装配对齐；3.50 神圣魔药净化差（O 净化6@3.50 vs
     G 净化10@3.5833）为**无 rng 流差的事件/堆叠动态差**（流至战斗 16.82 全同，
     首笔流差=EVENT109 后 gd 缺一笔 randf()）。DivinePotion 双侧全同；
     分歧落共享 cleanseRandomDebuffs 路径（gd_core/CoreItem.gd:2449）与盲堆叠
     动态——批 1 B 通道遗留线索同源。
   - run668 未复测（批 1 相位差线索仍立）。
3. 卫生：oracle/Core/Buff.gd md5=2e053483…（==净版，本批未插桩）；gd_core 零
   改动；夹具遭定向 --cases 收缩为 4→已按文档无 --cases 全量重建=914；
   canonical 314/914、退步 0（r11_ssd.txt 实跑）。

**通道表（文件面互斥）**：A3=激活动画 speed 抽参数化【修，激活】gd_core/
CoreItem.gd:982 块（读新字段，缺省 0.8/1.2）+gd_core_py/CoreItem.py→ManaOrb
簇 14（代表 run604_r10）+同型连带；A4=数据面【修，与 A3 并行】tools/
gen_gd_core_data.py 解析 Exclusive/Animations/*.tscn minSpeed/maxSpeed→
assets/gd_core_runtime.json 契约字段 animSpeedRange→与 A3 靠字段契约对接；
B2=净化路径/堆叠动态面【挂起：与 A3 同 CoreItem.gd，串行】CoreItem.gd:2449
段→FFR 簇 13（run628_r14）+LG Blind14（run668_r18）+BurningBanner12；C=复验
【无代码面，并行】全量+退步检。
**下轮入口**：A3+A4 并行落修→--cases run604_r10 --force 验→簇扩验→B2 串行
落修 run628/run668→全量+退步检。熔断：修复批无增长即熔断（计数 2）。

## r17 第 1 批（OffPeak 续6·修复批，314/914 持平，streak=1）

**A3+A4 激活动画 speed 域参数化（语义修复，零退步）**：
- A4：tools/enrich_anim_speed.py（新）——解析 Items/**/Animations/*.tscn 根节点
  minSpeed/maxSpeed 覆写 → battle_items.json anim_speed_min/max（幂等，--check 同款）。
  全库实测唯一覆写=OnionCutterAnimation.tscn:117-118（0.7/1.05），余 517 件缺省。
- A3：gen_lineup_fixture.py compile_descriptor 透传 animSpeedMin/Max →
  gd_core_test/item_battle_fixture.json（Godot 侧表）+ gen_gd_core_data.py 同函数
  → assets/gd_core_runtime.json（py 侧表，descr 字段核验 0.7/1.05 ✓）→
  OracleAlignBattle descriptor_of 读取 → CoreItemData.gd 声明+fromDict →
  CoreItem.gd:982 randf_range(0.8,1.2) 硬编码改 randf_range(animSpeedMin,Max)。
- 验证：run604_r10 --force 两轮（首轮漏重建 Godot 侧表——gen_lineup_fixture 与
  gen_gd_core_data 是两张表，都要跑）。**首分歧 idx64 未动**：gd 整体缺 t=345
  Mana Orb 激活（O@5.75 vs G@5.9833，14 ticks 偏移不变）——r16 的"动画时长链
  泄漏"假设对该偏移不充分，**真根另在冷却中段重标定面**（前序触发 2.15/4.4
  逐位同、间隔 2.25→1.35 变速，中段 triggerTime/iterationCooldown 被重标定）。
- compare-only 314/914、退步 0（基线 op_v2_base.txt）。streak=1（修复批无增长）。

**下轮入口（B2 立即执行）**：cleanse 面 run628_r14/run668_r18（FFR×13/LG Blind×14/
BB×12）——批 1 B 通道线索（-7 vs -6 堆栈计数+净化路径 CoreItem.gd:2449）；另挂
run604 冷却重标定面（addSpeed/updateBaseCooldown 的 cdProgress 重算语义双侧对读）。

## r17 第 2 批（B2 cleanse 面·排查批，314/914 持平，streak 仍 1——本批零码改）

**run628_r14 双药水互换定谳（prepare 桩双侧）**：
- Divine Potion/Health Potion **无冷却**（hasCooldown=false，桩仅中 Lightning
  Potion×2 own1/3 iter=5.353265/2.644585）——"冷却抖动抽互换"假设作废。
- 真机制：两药水系 **mana 门控触发**（checkMana 达阈即饮）——3.5/3.5833 互换=
  两侧 mana 积累节奏差；净化量 -6 vs -10=饮用时刻目标侧盲堆叠差（上游 Miss
  Fortune 幸运消耗/盲施加史）；目标 tgt1/tgt0 翻转=先饮的一侧不同。
- 结论：B2 根因链上移至 **mana 积累节奏 + 盲堆叠动态**（与 run604 Mana Orb
  14-tick 偏移同族嫌疑——mana 事件差）。下轮直接对读 t=3.4-3.5 两侧 mana
  事件流（105 型）与 mana 值快照，找首笔 mana 差源。
- 卫生：双侧桩还原 md5 核验；gd_to_py 重转写；compare-only 314 退步 0。
- **遗留卫生债**：gd_core/CoreItem.gd 存 workflow 期遗留 env 门控桩
  （[IRDb]:2470/[GStk]:1315/[Gain] 及 CoreBuff [BGAIN]/[BPOP]）——门控下无害
  （verify 正常跑不触发），但应择批清理或在台账挂账。

**下轮入口**：①run628 mana 面（105 事件流对读 3.3-3.6s+两侧 mana 快照桩）；
②run604 冷却重标定/mana 族合并攻击；③若 mana 面修通预期连清 ManaOrb×14+
FFR×13+DivinePotion 族。streak=1。

## r18 发掘（OffPeak 续7·大批量批 1，314/914）

**问题卡片 12 张**（digest 全簇+已定格库合并；同族卡片注明）：
- C1 mana 积累面：run628 双药水互换（mana 门控节奏）+ run604 Mana Orb 14-tick 偏移。文件面：CoreCharacter(mana)/CoreItem。
- C2 同刻伤害值差族【最大单一解锁，~50 场】：FFR×13（10v14@1.57 同刻）/Hammer×11（12v14@1.33）/DK×10（5v4@1.05）/MagicStaff×8（7v6@1.42）——时刻全同、值差=首攻前链位差 1 抽；FalconBlade×8（O 命中 G 落空@1.23）=**accuracy roll 本身差**（最锐利探针，命中差二元）；FW×13（2 伤 vs 尖刺事件序）同族候选。打法：run702_r18（FalconBlade）双侧 trace 逐抽对位找首笔流差→定位多/少 1 抽的调用点。
- C3 Burning Banner Blind×12（O 弹批 vs G 净化序差）。
- C4 LG Blind×14（run668 -7 vs -6 堆栈计数）。
- C5 Battery×14（充能旅行时序）。
- C6 Miss Fortune Lucky×8+LG（run588 idx3618 消耗序）。
- C7 Chess Board×8（Crown heal 序差）。
- C8 Spicy Banana×8（治疗 vs 冰冷序差）。
- C9 SSD 残余 15（Magic Mirror 反射序）。
- C10 Crown 残余 3 亚形。
- C11 Blueberries×12（同 tick fire 序差）。
- C12 卫生债：CoreItem.gd 遗留桩 [IRDb]/[GStk]/[Gain] + CoreBuff.gd [BGAIN]/[BPOP] 剥离+复验。

**本批执行序**：C12（卫生债，先清场）→ C2（探针最锐利、解锁面最大）→ 视结果连攻 C1 → 余卡按文件面分组。

## r18 修复·1（标签槽域修复，316/914，streak 清零）

- **C12 卫生债清零**：CoreItem.gd [IRDb]/[GStk]、CoreBuff.gd [BGAIN]/[BPOP]×2
  共五处 env 门控遗留桩手剥（正则脆改锚定 Edit）；gd_to_py 重转写；
  4 场代表 --force 复验 4/4 全绿零变化。
- **C2 首修（getNextFreeLabelPosition 两调用点绕过）**：workflow 期已有正确实现
  （CoreItem 槽位模型+±10/±30 域），但 CoreCharacter.gd spawnLabel_native(:720)
  与 heal 标签(:778) 两处**绕过方法直抽 ±10**——run702_r18 trace line518 实证
  oracle 兜底域 ±30×2 vs gd ±10×2。修=两处改调 item.getNextFreeLabelPosition()
  （注意：曾误加重复定义/声明，GDScript 解析错"couldn't be fully loaded"，
  去重后过）。修后 trace 首差 518→**2269**（前段 1751 行全对齐）。
- **收益**：FalconBlade 簇 5 代表 2/5 全绿（run720_r9/run840_r14）；
  **314→316/914 退步 0**；快照 r18_label.txt（新基线）。
- **2269 新差定格**（下靶）：oracle 在 dmg-number 块前多一笔 randf(0-1)
  （疑 crit gate：`critChance>0 and critRng.rollPercent` 两侧 gate 值差——
  crit 链双侧同构，差在 buff 驱动的 addCritChancePercent 调用史）。
  打法：grep 双侧 addCritChancePercent 调用方（Lucky/狂热类 buff），桩打
  run702 两侧 crit 值演化。

**批内余卡**：C1(mana)/C3(BB)/C4(LG)/C5(Battery)/C6-C11 按文件面续修。

## r18 批 1 收口（316/914，+2，streak=0）→ r19 批 2 启动

- C12 清零；C2 首修（标签槽两调用点）+2 绿（run720_r9/run840_r14）。
- **2269 双层定格（r19 首靶）**：
  ① oracle 在 dmg-number 块前多一笔 randf(0-1)=0.052162（2268 双侧同 flip
  0.548732 之后）——归属三选一：rollDoubleAttackEffect/accuracy/crit gate
  （crit 链双侧同构但 damageSource.critChancePercent 由 randDamage 入口刷新
  (:165/:207)，上一轮刷新残留可致 gate 异步）；
  ② 2273 起标签槽域**交错**（gd -10,10↔-30,30 与 oracle 反相）——槽位占用
  状态判定异步（0.5s 窗口的时基/占用次序），getNextFreeLabelPosition 的
  ctx.time 基准与 oracle Util.time 基准差 1 tick 是首选嫌疑（r12 已实证
  U 与 CT 恒差 1 tick）。
- r19 打法：①flip 归属桩（oracle Character.takeDamage 入口打
  attackEffectCount/accuracy/hit/crit 四值一行，gd 同桩，run702 对照三笔
  flip 归属）；②槽位时基对齐（getNextFreeLabelPosition 用 combat_time 基
  或 +1 tick 修正试验）。
- 余卡队列：C1 mana/C3 BB/C4 LG/C5 Battery/C6-C11 不变。

## r19 批 2 进行中（环境截断交棒，316/914，基线 r18_label.txt）

- 2269 flip 归属推进：TDA 四值桩两版均扰动流（v1 重抽 rollDouble 污染；v2
  纯读仍 self-identical=False——探针退出码 1）→ 已回退（md5 核验）。
- **新推理主线（强嫌疑）**：oracle 2269 额外 flip=Amulet of Darkness
  onItemActivated 的 rollChance()（每次相邻激活 flip 一笔）→ gd 少一笔=
  **某物品少一次 activate() 或 Amulet 邻接激活反应链少一次**——与 C5
  Battery（激活信号/充能旅行基建）同族！activate() 的 "activated" 信号
  发射双侧同构（Item.gd:4710 ↔ CoreItem.gd:950）。
- **下窗入口**：①run702 双侧数 activate() 调用次数（桩打 activate 入口
  计数，若再扰流则改数事件流 type=0 Activation 事件对照两侧每个 origin
  的次数——事件面零桩零扰）；②差 1 次的物品定位后对读其触发链；
  ③修通预期连清 C2 值差族+C5 Battery×14。
- 槽位时基交错（2273+ 域反相）挂起同批修（ctx.time vs Util.time 基差
  1 tick 嫌疑）。
- 卫生：oracle/Core/Character.gd 已还原（md5 821f2a33==备份）；gd TDA 桩
  仍在 CoreCharacter.gd（v2 纯读版，理论上零扰——但**下窗第一件事**：
  grep TDA 确认并还原 gd_core/CoreCharacter.gd 到
  output/_round_patches/r18_hyg/gd_CoreCharacter.v2.bak，再 compare-only
  核 316 无恙）。

## r19 发掘批（OffPeak 续8，环境截断交棒，316/914 持平，零码改）

**2269 深挖（多假设淘汰赛）**：
1. playAttackAnimation 五段/职业音效闸/pitch——双侧对读同构（gd 5 抽同序）✓ 排除。
2. fromDamageSource/updateItem/getAccuracy/getBuffAccuracyMod=(lucky-blind)*5——同构 ✓。
3. useStamina/clampStamina/StaminaSack——无 rng ✓ 排除。
4. canMiss 链（setItem flags/Type 枚举位）——双侧同构，DK types=[3,4,20,21,27]
   含 Ranged=20 → flags=All → canMiss=true 双侧同 ✓ 排除位错位假设。
5. **实锤新证据（flips 全列对照）**：0.85 帧 oracle flips 三笔 (0,0) 域
   （2771=0.548732/2772=0.052162/2786=0.18857），gd 同帧 flips 仅一笔
   （2298=0.096764）且另有 **(0,100) 域三笔**（2276=69.466/2283=7.884/2284=84.898）——
   gd 的 rollDouble/accuracy 判定**没走 (0,0) flip** 而走了 (0,100) 域（=
   CoreRng.roll(maximum=100)=randf_range(0,100)，即 flipPercent/Util.roll 风格），
   oracle 同位是 Util.flip=randf(0,0)。**flip 与 roll(100) 的底层调用差**。
6. 已核 gd BalancedRng.rollPercent→roll→_rng.flip 应为 (0,0)——矛盾指向
   accuracyRng 之外的判定路径（DK 是 Weapon：damageSource.setItem 的 flags 面、
   或 gd takeDamage 的 rollDouble 调用 _rng 绑定差），下窗以
   **ORACLE_ALIGN_NO_INJECT=1 最小场探针**（装配期逐抽点名）或给 CoreRng.roll
   加 (0,100) 域调用栈桩（debug 版有栈）一锤定音。
7. 卫生：oracle/Core/Character.gd 净（md5 821f2a33）；gd CoreCharacter v2 净版
   在位；两侧无残留桩；316/914 退步 0（r18_label.txt）。

**下窗入口（r19 批 2 续）**：
①CoreRng.roll/flipPercent 调用方全清单 grep → 对 run702 0.85 帧三笔 (0,100)
  逐一对号（Twine 激活密集嫌疑最大，744 次/场）；
②确认后统一改走 flip(0,0)（或反之若 oracle 某路径确是 roll(100)——以
  decompiled 对应调用点为准）→ run702 trace 复对位（预期 2269 消失）→
  FalconBlade 簇+伤害值族扩验；
③标签槽时基交错（2273+ 域反相）挂起同批；
④余卡 C1/C3/C4/C5/C6-C11 队列不变。streak=1（r18 批 1 已 +2）。


## r20 发掘批 1（OffPeak 续9，316/917，零码改）

**r19 入口①完成（flip/roll 调用方清查）**：gd 全库 .roll( 直调仅 CoreUtil.gd:126（无调用方）；(0,100) 域唯一来源=flipPercent 7 点（CoreBuff.gd:141/145/156/273/278、CoreUtil.gd:136、Piggybank.gd:13）；oracle 同构（Core/Buff.gd:91/95/106/219/224 均 Util.flipPercent=roll()，Utility/Util.gd:1087-1094 双侧域同）。rollDouble（Item.gd:4115↔CoreItem.gd:1235）、rollChance（Item.gd:4394↔CoreItem.gd:1160）、BalancedRng.roll→flip（CoreRng.gd:314）逐点同构。**2269 定性修正：判定调用次数差（gd 0.85 帧多 3 笔）而非底层域差**；Twine.gd 双侧零 rng 调用（嫌疑解除），收敛到激活反应次数面（Goobert.gd:38 doubleActivation flip、Amulet rollChance）。卫生：gd CoreCharacter.gd md5 a0ea87a8==r18_hyg 备份，TDA 残桩已净。

**问题卡 10 张**（簇名｜代表场｜现象｜嫌疑文件:行｜通道）：
1. LG Blind×16｜run668_r18｜致盲结束剩余 7vs6（同 tick）｜消耗面 CoreBuff.gd:141-156（A）+apply 面 LightGoobert.gd:13-15（C）｜A/C
2. 2269 flip 差｜run702_r18｜gd 多 3 笔 flipPercent 域抽｜激活反应次数面 Goobert.gd:38/CoreItem.gd:1160｜A
3. 标签槽时基｜run702_r18｜2273+ 槽域 (-10,10)↔(-30,30) 反相｜CoreItem.gd:2787-2798 ctx.time 基 vs r12 实证 U/CT 恒差 1 tick｜A
4. C1 Mana Orb×14｜run604_r10｜gd 缺「获得1层魔法」行｜ManaOrb.gd:22-33 激活/门槛面｜B
5. C5 Battery×14｜run1160_r18｜Activation 事件数差｜Battery.gd:16-18 emitCharge→activate/sendCharge 充能旅行基建｜B
6. Burning Banner×12｜run688_r10｜O 致盲结束 vs G 净化（行为分流）｜Exclusive/BurningBanner.gd｜B
7. Chess Board×8｜run675_r18｜棋子激活序差｜Exclusive/ChessBoard.gd:62/83/105/150 shuffleEngine+capture:139｜B
8. 伤害值族×42（FFR13/Hammer11/DK10/MagicStaff8）｜run666_r10 等｜10vs14、12vs14 偏高；5vs4、7vs6 偏低｜FancyFencingRapier.gd:6-12、Hammer.gd:3-5、Exclusive/DragonKnight.gd、MagicStaff.gd:6-10｜C
9. 资源杂项×24（MF8/SpicyBanana8/AoL8）｜run588_r18 等｜幸运消耗/体力治疗/恢复行缺或异行｜Exclusive/MissFortune.gd:7-11、SpicyBanana.gd:41-47、AmuletofLight.gd｜C
10. 挂起双卡：Flame Whip×13（r11/r12 定谳=装配期 Flicker 抽插入位差 4，注入面修不动）+Blueberries×12（r11b 定谳=同 tick fire 序差）｜——｜S

**通道表**（通道内只碰独占文件；gd X.gd 与 gd_core_py 镜像同通道）：
- 通道 A 内核判定/时基面：gd_core/{CoreBuff,CoreCharacter,CoreItem,CoreContext,CoreRng}.gd
- 通道 B 物品激活/充能/mana 面：gd_core_items/{ManaOrb,Blueberries}.gd+Exclusive/{Battery,ChessBoard,Chess/ChessPiece,BurningBanner}.gd
- 通道 C 物品伤害/资源值面：gd_core_items/{FancyFencingRapier,Hammer,MagicStaff,LightGoobert}.gd+Exclusive/{DragonKnight,MissFortune,SpicyBanana,AmuletofLight}.gd
- 通道 S 挂起+线索：Flame Whip（装配期注入面）、Blueberries（若 B 修不通落入）


## r21 发掘批 2（OffPeak 续9，317/917，+1=run666_r10 FFR 首果，零码改）

**物品面全线同构定谳（批 2 双侧逐行对读）**：ManaOrb/Hammer/DragonKnight+RubyWhelp/MissFortune/AmuletofLight(含 rollChance2 分支)/BurningBanner/Crown/StaffofUnhealing/MagicRing(26 函数集对齐,oracle:58-294↔gd:45-251) 全部逐行同构，视觉剥离合法。**各簇嫌疑全面收敛到核心面**。

**管线级同构实锤（伤害值族定性）**：BalancedRange（gd_core/CoreRng.gd:373-399↔oracle/Utility/BalancedRange.gd:9-32）、randDamage（CoreDamageSource.gd:202-212↔DamageSource.gd:163-168）、getMin/MaxDamage（CoreItem.gd:1028-1042/1046↔Item.gd:3660-3674/3677）逐行同 → 值差=修饰输入差（bonusMin/MaxDam、getBuffDamageMod、getTypedDamageFactor、bonusDamageFactor 战斗期 buff 状态）；Hammer gd 14 超描述符 max 13、DK gd 4 低于 min 5（assets/battle_items.json）→ 偏移双向，非固定差。
幸运面：getLucky（Character.gd:1252↔CoreCharacter.gd:1533）、tryUseLucky/useLucky/giveLucky（Item.gd:5035-5060↔CoreItem.gd:1381-2413）同构 → MF 缺消耗行=上游 luck 栈账差。rollChance2 同构（Item.gd:4397↔CoreItem.gd:1166）→ AoL 缺恢复行=激活/chance 次数族。ManaOrb 同构 → C1 缺 mana 行=邻接激活→rollChance→giveMana 链次数差（2269 下游）。
**C5 新证据**：簇样本更新（run1282_r18）「O [玩家] 获得3层狂热（电阻）｜G [对手] 获得3层狂热（电阻）」同值反边 → sendCharge 充能归属/目标判定差，非单纯次数差。
**Crown 触发面**：checkTrigger 双信号（mana_changed+invu_end，Crown.gd:20-21）+doCooldownEffect cleanseBlind(1)（:43）→ BB 样本 gd「净化致盲（辉耀王冠）」即此函数 → Crown 冷却 tick 时基与 blind 时长结算耦合。

**问题卡 10 张（批 2）**：
1. 2269 激活反应次数面（总闸）｜run702_r18｜gd 多 3 笔判定抽｜run702 双侧按 origin 数 type=0 Activation（零桩）｜A
2. 标签槽时基｜run702_r18｜槽域反相（不重查）｜CoreItem.gd:2787-2798｜A
3. C1 Mana Orb×14｜run604_r10｜2269 下游定谳，残差查 giveMana/useMana 栈账｜ManaOrb.gd:22-33｜B
4. C5 Battery×13｜run1282_r18｜狂热同值反边｜Battery.gd:16-18 sendCharge 归属面｜B
5. LG Blind×16｜run702_r18｜blind 栈消耗计数差（apply 面已证同构）｜CoreBuff.gd:141-156+LightGoobert.gd:13-15｜A/C
6. Burning Banner×12×Crown 耦合｜run688_r10｜净化 vs 到期分流｜Crown.gd:43+CoreBuff 时长结算｜A/B
7. 伤害值族×42｜run733_r9 等｜管线同构，修饰输入差（buff 栈账）｜CoreItem.gd:1032-1039 输入源｜A（C 物品面无事可修）
8. MF luck 栈账×8｜run588_r18｜上游 luck 获得差（FFR giveLucky 同批）｜CoreCharacter.gd:1533+FFR.gd:12｜C
9. AoL×8｜run752_r18｜激活反应族+giveRegeneration 栈账｜AmuletofLight.gd:16-24｜A/C
10. 新四小簇：Crown×13/Unhealing×13/Superior Ring×10/Magic Ring×10｜触发门状态差+Ring randEffects 装配期嫌疑（SuperiorRing.tscn:4 同用 MagicRing.gd）｜Crown.gd:26-36、StaffofUnhealing.gd:11-24、MagicRing.gd onDamaged:82-99/randEffects:180｜C

**通道表**：
- 通道 A 内核栈账/激活面（主攻）：gd_core/{CoreBuff,CoreCharacter,CoreItem,CoreContext,CoreRng}.gd——卡 1/2/5/6/7/9
- 通道 B 物品激活/充能/mana 面：gd_core_items/{ManaOrb,Blueberries}.gd+Exclusive/{Battery,ChessBoard,Chess/ChessPiece,BurningBanner}.gd——卡 3/4/6
- 通道 C 物品触发/资源面（新增 Crown/Unhealing/MagicRing）：gd_core_items/{FancyFencingRapier,Hammer,MagicStaff,LightGoobert,Crown,StaffofUnhealing}.gd+Exclusive/{DragonKnight,MissFortune,AmuletofLight,MagicRing}.gd——卡 8/9/10
- 通道 S 挂起：Flame Whip（装配期链位差 4）、Blueberries（同 tick fire 序差）
- 备注：B/C 大半簇根在 A（物品文件已证同构），A 修后 B/C 复验收残差。

## r22 发掘批 3（OffPeak 续9，317/917 持平，零码改）

**零桩事件流对位新证据**（events.json 逐条 sig=(type,ts,origin,target) 前缀比对）：
run702 前缀 idx0-508 全同（0.85 flip 差帧纯内部不可见），idx509 起 O 有 AoL 102
回复反应 gd 缺；O/G 激活总数 1251/1721 系时长级联（36.75s 玩家胜 vs 52.02s 对手
胜）非因。run604 idx64=ManaOrb 105+1 缺（ManaOrb.gd:22-25 rollChance→giveMana）
＝2269 下游实证；run752 idx91 AoL 缺/run810 idx194 Blueberries 缺/run616 idx20
stun_resisted 缺/run733 idx130 FFR 命中差——rollChance 反应族扩面。run1282
idx300-301=Battery 热+3 tgt 反边（sendCharge=CoreItem.gd:2082↔Item.gd:5148）。
run688 idx131=盲栈到期 origin BB(O)/Crown(G)，loseStacks 全同构（Buff.gd:209-290↔
CoreBuff.gd:264-341）→调用方源归属+Crown.gd:29-43 时基。新簇=同刻触发序差
（run668 idx876/run637 idx78/run588 idx3618）。run749 idx45=MagicStaff 迟 5 ticks。
域定谳：flipPercent 同构（Util.gd:1093↔CoreRng.gd:56-69 同 (0,100)）；标签槽=
Item.gd:6522 Util.time↔CoreItem.gd:2791 ctx.time 差 1 tick。卫生：oracle Buff/
Character md5==备份/记录值，零码改零桩。

**卡 10 张**：①2269 流移位总闸(run702 idx509+0.85 帧 4v3 抽,CoreBuff.gd:139-157,A)
②标签槽时基(Item.gd:6522↔CoreItem.gd:2791,A) ③同刻序差(run668/637/588,B)
④冷却迟触发(run749/675/604,CoreItem 冷却面,A) ⑤Battery 反边(CoreItem.gd:2082+
CoreHooks.gd:197,A) ⑥盲栈源归属(run688,调用方+Crown 时基,A/B) ⑦ManaOrb 下游
(run604,A 复验) ⑧rollChance 反应族(run752/810/616/733,A 复验) ⑨伤害值族降级
(首差=命中/序/时刻,A/B 后复验) ⑩挂起：Flame Whip+Blueberries(S)。

**通道表**：A 时基/rng 栈账/冷却面（主攻）＝{CoreContext,CoreRng,CoreTimer,
CoreBuff,CoreItem,CoreHooks}；B 触发派发序面＝{CoreCharacter,CoreCombat}（卡 3/
6 半）；S 挂起＝卡 10。gd X.gd 与 gd_core_py 镜像同通道。
下窗入口：A 先 0.85 帧多 1 抽调用方定位（flipPercent 调用点全审计+NO_INJECT 装
配探针）→修 2269→run702/604/752 连验；B 对读 oracle prepare connect 序。streak=1。

## r23 发掘批 4（OffPeak 续9，317/917 持平，零码改）

**仪器级定谳：oracle 探针复放自身双稳**（ORACLE_FIGHTS_ROOT+ORACLE_DEBUG，harness
同种子复跑闸）：run702 复跑 FAIL——同进程 run1=语料轨迹（AoL 102@idx509），run2=
gd 轨迹（Gingerbread@idx509）；分叉抽=run1 在 rollDouble flip 后多 1 笔
randf(0,1)=0.052162（即 r18"2269 多一笔"），run2 无→全链移位。该笔=存在性抖动的
accuracy 面判定（BalancedRandom.gd:43 roll→Util.flip；嫌疑 SceneTreeTimer/
callDelayed 帧量化使计时 buff 在攻击边界差 1 tick）。run688 同病（corpus-vs-probe
仅 222/939）。**语料是抖动实现之一**。毒化判定：run702 idx509=POISONED（gd 与去
抖轨迹匹配至 1327 事件 t≈13.03）；run604 可复现 1069/1069→REAL；run752 781/781
→REAL；run688 gd 差点 131<双稳点 222→REAL。
**run604 根因面钉死**（稳定参考下双侧 trace 对位；标签归一 randInBox.x/y→
randf_range、pickRandomElement→randi_range、randPitch→randf_range，gd 独有
Gopen/Gshuffle/AMP 行跳过）：首真差 gd 抽 410/or 401——t=5.75 oracle 有
flip(0.006105 命中)+标签槽 ±10 对（ManaOrb 105 反应），gd 零抽（信号未达）。
ManaOrb 前 6 反应双侧全同→连接在；chance=50 非零→非参数短路；Piggybank 激活
事件 gd 在→activate 跑了；嫌疑=consume()（Piggybank.gd:23-26）后激活派发面。
**卡 10 张**：①run604 信号未达(REAL,A 主攻) ②run752 AoL REAL(A 复验) ③run702
语料变体(POISONED,S) ④run702 新锚点 13.03(A) ⑤run688 盲栈归属 REAL(A/B) ⑥
复放双稳批量审计(工具面) ⑦同刻序差 run668/637/588(先审计,B) ⑧冷却迟触发
run749/675(A) ⑨Battery 反边 run1282(A) ⑩挂起：Flame Whip/Blueberries/变体类(S)。
**通道表**：A 激活派发/时基={CoreItem,CoreEventBus,CoreContext,CoreRng,CoreTimer,
CoreBuff,CoreHooks}；B={CoreCharacter,CoreCombat}；S=抖动变体+装配期。镜像同通道。
下窗：A 用 AMP 入口桩定位 Piggybank@5.75 emit 链（扰动即回退）；⑥批量探针审计
594 场不可复现子集（2 跑/场≈40s）。卫生：语料 git clean、oracle *.gd md5==记录、
夹具还原、alignment.json 未触碰（单场走 alignment_r22_probe.json）。streak=1。

## r24 发掘批 5（OffPeak 续9，317→320/917（+3），构建阻碍已排除）

**构建阻碍根因+修复（已闭环）**：b2 修复段的 BUS/BCON 零消耗桩在 CoreEventBus.gd
用 `emitter is CoreItem` →全局类名循环依赖（解析失败级联 CoreItem:3831→
CoreDamageResult:97→CoreCharacter:546→宿主:245；_b2_wf_verify.log 0/10 实证）。
修=2 处改鸭子类型 `emitter.get("descriptor") != null`（oracle_trace 关时零开销）
→gd_to_py 重转写→10 场重建 PASS+selfcheck 同种子自证过+事件数逐场==桩前
（run604 1076/run702 4684/run688 897/run752 781）→零行为漂移。
**陈旧产物掩蔽面（本批最大发现）**：833/917 gd 产物停留 10-11（早于 label-slot/
f32/SSD/A3A4 全部修复落码）；--force 重建 10 场即 +3（run749_r12/run752_r18/
run1282_r18 三方一致——run752 旧 792 vs 新 781=oracle 全程同）→591 场里疑有更
多"刷新即胜"。全量 --force 重建已启动（exec_72572633，约 40-60min），完成后须
重跑 digest+compare-only 取真数；r22 批基于陈旧产物所读锚点（run668 idx876/
run637 idx78/run588 idx3618/run675 idx649/run749 idx45）**全部待重测**。
**新证据（py 探针，b2_fix1/_probe604_bus2.json）**：py 在 t=5.75 窗仅 MF×2 发
activated、Piggybank 零发→py=gd 共缺 vs oracle 独有→run604 真差=冷却激活是否
发信号面（Piggybank.gd:23-26 consume 后+CoreItem.activate 派发），r23 卡①维持。
**卡 10 张**：①构建阻碍根因（已修,A/工具,闭环） ②陈旧产物掩蔽+全量重建（G,进行中）
③run604 信号未达（REAL,A 主攻） ④run749/752/1282 转绿（闭环,+3） ⑤run702 语料
变体 POISONED（S） ⑥run688 盲栈归属 REAL（A/B） ⑦同刻序差 4 场（锚点待重测,B）
⑧伤害值/冷却族（锚点待重测,A） ⑨复放双稳批量审计（G） ⑩挂起：Flame Whip/
Blueberries/变体类（S）。
**通道表**：A 激活派发/时基={CoreItem,CoreEventBus,CoreContext,CoreRng,CoreTimer,
CoreBuff,CoreHooks}；B={CoreCharacter,CoreCombat}；G 全局重建/审计工具面=
{verify_oracle,探针脚本}；S=变体+装配期。gd X.gd 与 gd_core_py 镜像同通道。
下窗入口：G 收全量重建结果→重跑 digest→新簇landscape 重定卡→A 以新鲜锚点攻
run604（BUS/BCON 标记已可用，gd 侧单场 ORACLE_ALIGN_TRACE=1+STACKTRACE 即读
「t=0 受派/5.75 零收」实据）。卫生：alignment.json 由全量跑收口；语料/源码零
触碰（本批仅 CoreEventBus 桩去循环，行为中性已验）。streak=0（+3）。

## r24 收口补记（同批，全量重建完成）

全量 --force 重建（exec_72572633，gd 914 场+py 914 场+compare）收口：
**aligned 320→460/914（+140）**，rng-mechanism 505→389、gd_core-kernel 88→65。
陈旧产物掩蔽假证实锤：833 个 10-11 旧产物换新后，label-slot/f32/SSD/A3A4 等
已落码修复批量兑现。伤害值族（FFR/DK/MagicStaff）、Battery、ManaOrb 退出
Top15（已被既有修复吞掉）。**新 Top 簇（452 场上）**：LG Blind×29、Burning
Banner×18、Blueberries×17、Crown×14、StaffofUnhealing×13、MF×11、src:poison×9、
SuperiorRing×9、Hammer×9、MagicRing/MagicMirror/ShinyMantle/ChessBoard/
SpicyBanana/Banana×8——下批以 digest 新表重切卡与通道。本批卡②④⑧按新表重定；
卡③run604（现非 Top，残簇）、⑤⑥⑨⑩ 维持。基线未刷新（aligned_sets 旧基线
作废，下批重建基线）。卫生：语料/源码零触碰，alignment.json=全量跑收口。

## r25 发掘批 6（OffPeak 续9，462/917（+2），零码改）

**上窗修复段确认（b3_fix1，非本批产物）**：CoreBuff.gd 四分支计时模型（②判据
改 _timer_left==-1.0，补「净化清空 stop 后同 dur 重施加」路——run688 idx130-133
同帧施加+到期实证=BB×17/LG×29 簇根之一；补 ①' 同帧支+_timer_firing 守卫；
nextTemporaryTimeout 悬空回退防 run989 实崩）+CoreCharacter 170 行+py 重转写。
净 +2（run588/637 转绿）。本批核：语料 git clean、构建绿。
**新鲜锚点扫描（零桩 12 代表，产物=全修复后）**——面甲同刻触发序（The Fool/
Carrot/Cheese/SnowStick 在 gd 早发或他品晚发）：run686 idx31、run841 idx102、
run1024 idx46（Crown heal@1.38 vs **The Fool** vampirism@1.35）、run1045 idx38、
run810 idx194、run605 idx1157、run574 idx45、run675 idx649；The Fool(cd=1.5,
accuracy100) 早触发=新亚族（run900/1024/1045，run900 且 403 vs 1363 事件截断
级联）。面乙盲栈残差：run727 idx354（BB blind@5.02 vs **萝卜净化保护**@5.05——
cleanseProtection 分流）、run629 idx5383（Crown cleanse vs LG expiry@22.58）、
run619 idx415（FFR 命中翻转@6.15→盲计数 7vs5 下游）。py 分歧族：
「oracle≠gdcore 且 py 分歧」2→**38**（run619/622/634/665/704…与 LG×29 重叠）。
**卡 10 张**：①面甲同刻序（8 锚,B 主攻） ②The Fool 早触发亚族（新,A） ③面乙
盲栈残差 run727/629（B/A） ④run619 FFR 命中翻转（accuracy,A） ⑤Blueberries
×17（S/A 先审计） ⑥Crown×14（B） ⑦Unhealing×13（The Fool 同族,B/A） ⑧poison
/Hammer/ChessBoard 时基（A） ⑨py 分歧 38 量化+基线重建（G） ⑩挂起（S）。
**通道表**：A 冷却/触发时刻/accuracy={CoreRng,CoreTimer,CoreContext,CoreItem}；
B 盲栈/派发序={CoreBuff,CoreCharacter}（b3 同通道续攻）；G 工具面（基线重建/
py 分歧量化/双稳审计）；S=挂起。镜像同通道。
下窗入口：B 攻 run727 萝卜净化保护分流（cleanseProtectionChancePercent 面）+
run629 同刻选栈；A 攻 The Fool 早触发（BUS/BCON 标记读 run900 发射序）；G 先
重建 aligned_set 基线（旧基线全作废）。streak=0(+2)。

## r25 发掘（OffPeak 续9 阶段 1，462/917，副指标 121,861，零码改）

开局基线：compare-only 462、快照 op_v4_base.txt、副指标 121,861（基线核验通过）。
digest 前 7 簇（全为 ≤9 场小簇——大簇已清）：poison×9/MF Lucky×8/ChessBoard×8/
SpicyBanana×8/Banana×8/SoU Mana×7/Hammer 残 7。

**阶段 1 问题卡（4 张，直取 r21 十卡中证据最全者）**：
- K1 2269 激活反应次数面（总闸）：gd 0.85 帧多 3 笔判定抽（(0,100) 域）vs
  oracle (0,0) flip——CoreRng.roll(100) 风格 vs Util.flip 底层调用差；
  嫌疑调用方=物品激活反应链（Amulet of Darkness onItemActivated→rollChance 族）。
  修法：grep gd_core 全库 .roll() 无参调用 → 对照 decomp 同位调用 → 统一改
  ctx.rng.flip(...)。修通预期连清伤害值族+激活链族残余。
- K2 标签槽时基：getNextFreeLabelPosition 槽域反相（gd ±10↔±30 与 oracle 反相，
  CoreItem.gd:2787-2798）——0.5s 占用窗时基差（ctx.time vs Util.time 恒差 1 tick，
  r12 实证）。修法：槽位时戳比较改用 combat_time 或 +1 tick 试验。
- K3 C1 Mana Orb×14：giveMana/useMana 栈账差（ManaOrb.gd:22-33 双侧同构，
  上游激活次数差）。2269 下游，K1 修后复测，若仍差再挖 mana 栈账面。
- K4 C5 Battery×13：sendCharge 归属面（run1282 狂热同值反边 [玩家]vs[对手]，
  Battery.gd:16-18）。修法：对读 sendCharge→chargeCells→host 判定链。

**执行序**：K1（总闸）→ K4（独立面）→ K2（时基）→ K3（K1 下游复测）。

## r25 阶段 1 进行中（进度锚：K1 攻坚中，aligned=462，副指标=121,861）

- 值序列复对位（滤 EVENT/ANIM/LABEL/BUS/BCON 标记行）：**首差仍在 value-line
  2269**——oracle 于 acc flip(0.548732) 后、飘字块前多一笔 flip(0.052162)。
- 2268 flip 重定归属=rollDoubleAttackEffect（0.548732<=0 false，DK 攻击链第 5 抽）；
  2269 oracle flip(0.052162)=**accuracy flip**（<=0.70 hit=true）——gd 缺此笔。
- 已核排除：Weapon.attack/ DK+RubyWhelp 脚本/ advanceCooldownPercent（标签抽
  双侧同构）/ damageSource setItem flags（DK types 含 Ranged→flags=All→canMiss ✓）。
- 待查（下窗直入）：gd DK 攻击的 canMiss 实际值——重点 **gd takeDamage 内
  damageSource.accuracy 的求值时点**（fromDamageSource 拷贝后 accuracy 是否被
  updateItem/其他路径覆写为 0 或 >=100 短路（rollPercent(target>=1) return true
  不抽！）——oracle acc=0.70 抽了，gd 若 acc>=100（=updateItem 未跑、默认 100）
  则 rollPercent(1.0) 短路 return true **不消耗链**→ 正好解释 gd 缺一笔且
  hit=true 事件面相同！！**头号嫌疑：gd 的 dealDamage 未调 updateItem 或
  accuracy 拷贝链断** → 查 gd Weapon.dealDamage→Item.dealDamage(:1407)
  damageSource.updateItem(self) 是否真的执行（connectForCombat 时序/damageSource
  null 面）。
- K2/K3/K4 未动。现场：trace 已重录（run702 gd）；探针 r18_c2 oracle log 在位。

### r25 K1 追加锚（压缩前）

推理闭环到最后一格：gd DK 攻击链 6 抽 vs oracle 7 抽，缺=accuracy flip；
但 flags 链（types→setItem→rangedFlags=All→CanMiss ✓）逐环核对均同构——
唯一自洽解"gd canMiss=false"与静态代码矛盾。
**下窗直入方案（安全标记桩）**：gd takeDamage canMiss 分支加
`if oracle_trace: _trace 标记行`（标记行不耗链可滤，区别于 TDA print 桩）
打出每次 takeDamage 的 canMiss/accuracy 实值 → run702 对照 → 定位是
flags 断链还是 accuracy 值断链。然后 K4 Battery→K2 标签槽→K3 ManaOrb
→阶段末检验（副指标判定）→r26。

### r25 K1 定谳链（进度锚：K1 根因=blind current 无事件残留，aligned=462，副指标=121,861）

- 安全标记桩（CANMISS trace 行，不耗链，首差仍 2269 自证）两版定谳：
  `3112 CANMISS cm=16 acc=0 src=Dragon Knight bA=5 mod=-95`
  → acc=0 因 getBuffAccuracyMod=(lucky-blind)*5=-95 → blind-lucky=19
  （bA=5 合法：Wolf Badge 类+t0 事件面）。
- 但 0.849 前事件面 109 计数双侧同=0、t0 lucky 同（5/5）——**gd 侧 blind
  current 有 ~24 层无事件来源**（全场 109：gd 282 vs oracle 197，多 85）。
- 已排除：getStacks/getBlind/Buff.setStacks/LightGoobert/Goobert.prepare 双侧
  逐行同构。
- 下窗直入：①CANMISS 标记加 owner side（side=p0/p1）确认 DK 持有侧的
  lucky/blind 分解（标记加 lucky=X blind=Y 两值）；②若 blind 真残留→
  gd gainStacksTemporary/changeCurrentLogShowLabel 找**无事件写入路径**
  （对比 oracle 同函数——事件发射点与 current 写入的相对位置：gd 是否
  current+= 在事件发射前被重复调）；③giveStacksTemporary 的 timer 面
  （_startTimer duration）不影响 current。
- 桩态：gd CoreCharacter.gd 带 CANMISS v2 标记（备份 r25_fix1/）——
  下窗用完还原。

### r25 K1 锚 v2（压缩前；aligned=462，副指标=121,861，K1 攻坚中）

标记桩 v3（lucky/blind 分解）铁证：`3112 CANMISS acc=0 src=Dragon Knight
bA=5 mod=-95 lucky=3 blind=22`；且 **701 行 blind=0 → 3112 行 blind=22 之间
零 109 事件**（0.85 帧内双侧各仅 1 笔 +7）——gd 侧有**无事件、无 rng 消耗**
的 blind 施加路径（gainTemporary resist=0 时不 flip；item=null 时不发事件，
Buff.gd:177 `if item:`）。oracle 反推同位 blind=18——**两侧都有无事件源**，
差值 4（22 vs 18）×5=20≈mod 差。真根=**某条 item=null 的 blind 施加链在 gd
多次执行**（候选：stealRandomBuff/反弹/临时栈到期 onTimeout 的 amount 记账）。
下窗直入：①gd CANMISS 标记加 temporaryStacks.size() 与 permanentStacks 分解；
②grep gd gainStacks/gainTemporary 的 item=null 调用方（CoreItem/CoreCharacter/
CoreBuff 内 self 路径）对照 oracle 同位；③重点 loseStacks 反弹 reflected 分支
（Buff.gd:191-193 opponent.gainStacksTemporary(type, reflected,...,true)——
reflect=true 时 oracle 侧 **不再发事件**？读 oracle gainTemporary reflect 段
确认事件发射条件——若 reflect 分支 item 判定差 → gd 多发/多施）。
桩态：gd CoreCharacter.gd 带 CANMISS v3 标记（备份 output/_round_patches/
r25_fix1/CoreCharacter.gd.bak）+ CoreCharacter.gd:1435 残留 [Gain] print 桩
（PROC_DEBUG 门控，卫生债）。用完还原+md5。

### r25 K1 锚 v3（终锚：Buff 层 gainTemporary 全同构核毕）

resist/reflect/amount 增补/事件发射条件（item!=null）/反弹递归
（opponent.gainStacksTemporary(reflect=true)）双侧逐行同构——Buff 层排除。
blind 差（gd 22 vs oracle 反推 18）源自**上游施加调用次数或 amount 参数差**
（Light Goobert doCooldownEffect 的 blindAmount=getP3() 或其触发次数）。
下窗直入（按性价比）：
①gd CANMISS 标记再加 temporaryStacks.size()+permanentStacks 分解 →
  判 22 层属临时面还是永久面（临时→LightGoobert 触发次数差=激活计数族
  （C5 同根！）；永久→giveStacks 直调差）；
②若临时面：对读 LG 的 activations 计数链（Goobert.onItemActivated 的
  activations==getP1() 门）与邻接物品激活信号次数（gd 多激活→多 doCooldown）；
③run702 里 Light Goobert×1/Cheese Goobert×1——LG blindAmount 每次施加
  事件面 +7 ✓（双侧 0.85 各 1 笔）→ gd blind=22 需 3 次施加（7×3+1）而事件
  只见 1 次 → **2 次施加无事件** → item=null 或事件发射被 skip 的路径——
  但 LG giveStacksTemporary 有 item…… 除非 **临时栈到期回填**（onTimeout 的
  changeCurrentLogShowLabel(isTimeout=true) 应发 -X 事件）——t<0.85 只见
  0.483 一笔 -1。**多出的 2 次施加极可能也在 0.85 帧内 CANMISS 后**（时序差）
  → K1 与 C5（激活计数）合流。修 C5（激活计数/sendCharge 归属）可能连清 K1。
执行序调整：先攻 C5/Battery（K4）——若 K4 修后 run702 的 blind 对齐则 K1 自愈。
桩态同锚 v2（CANMISS v3 + [Gain] 残桩，备份 r25_fix1/）。

### r25 K4 锚（压缩前；aligned=462，副指标=121,861，K4 修复已落但簇未转绿）

- K4 修复落地：CoreItem.gd sendCharge 补充**后续 cell 到达的 callDelayed 排程**
  （halfCellDur=0.5*travel/(n-1)，cell k 到达=(k-1)*travel/(n-1)，桥
  _chargeEnterCellDelayed(charge,k,inv_cells)——历经三修：类型推断错
  （var := 对无类型类报错→显式 float/int）→ callv 绑定错（obj 必须=self））。
- Battery 簇 3 场复验：**仍 0/3 但首分歧全部推进**（run1160 idx55 Spectral
  Dagger dmg2 / run1282 idx95 Djinn Lamp / run1283 idx40 LightningStaff dmg12）
  ——充能逐格节奏已进，残差=**gd 多两笔 (0,6) 域 pickRandomElement**
  （5 键堆栈池选择，run1282 trace 582 起）——嫌疑=removeRandomBuffs/
  stealRandomBuff 在 gd 侧多执行（Djinn Lamp useLucky 链/AmuletD 反应链）。
- trace 仪器注记：gd 侧另有 AMP 标记行（CoreItem.gd:1285 残留，不耗链可滤）
  ——复对位脚本排除清单需含 AMP。
- 下窗直入：①run1282 对读 idx95 前事件窗（Djinn Lamp useLucky→stealRandomBuff
  双侧调用次数）；②(gd 多两笔 (0,6)) 与 C6 Miss Fortune Lucky 同族——
  luck 栈账/steal 链次数差。
- 卫生：CANMISS v3 标记仍在 gd CoreCharacter（备份 r25_fix1/）；本轮新改
  CoreItem.gd 备份 output/_round_patches/r25_k4/。streak 判定待阶段末。

### r25 K4 锚 v2（压缩前；aligned=462，副指标=121,861）

**K4 修复引入新实锤——Coil 事件面畸变**：run1282 全场 origin 计数对照：
Coil **O=0 vs G=104**（gd 侧 2.0167 起 Coil 名下大量 102-106 型 -1/+1 成对
steal 链，Oracle 同名物品全程零事件）；连带 Charge Splitter 18v20、
Djinn Lamp 195v206、Cubert 156v162、Resistor 10v13。Coil 确在双侧阵容
（player/opponent 各 3 件，(2,1)/(3,1)/(4,1) face0）。
**嫌疑**：①gd Coil 物品脚本 onChargeReceived/onChargeLeft 实现与 oracle 差
（oracle 的 Coil 收电荷不发栈事件/或根本收不到）；②K4 逐格排程让电荷真的
到达 Coil 格（此前只走 cell1 不触发）→ 暴露 gd Coil 脚本的栈转移行为。
**下窗直入**：对读 gd_core_items 的 Coil 脚本（grep -i coil gd_core_items/）
与 oracle 同名脚本（可能名不同：Coil=电感/线圈，oracle 可能叫 TeslaCoil/
InductionCoil 等——先在 oracle/Items/ 找同 position 物品）逐行 diff
onChargeReceived/onChargeLeft/steal 面；对照 oracle 侧 2.0167 帧同结构的
真实归属（O 2.0167 帧无事件 → 电荷在 oracle 未达 Coil 或到达无反应）。
K2 标签槽/K3 ManaOrb 队列不变。streak 判定待阶段末。

### r25 K4 锚 v3（终锚；aligned=462，副指标=121,861）

Coil 脚本双侧逐行同构（onChargeReceived→stealRandomBuff(numBuffs)）→
分歧不在脚本，在**电荷路径格映射**：oracle 侧整场 Coil 零事件=电荷从未到达
Coil 格；gd 侧（K4 逐格排程生效后）电荷到达→steal 链爆发（Coil origin 104）。
player 侧布局：row0=Battery(0,0)/Splitter(1,0)(2,0)/Resistor(3,0)(4,0)/Battery(5,0)；
row1=Battery(0,1)/Resistor(1,1)/**Coil(2,1)(3,1)(4,1)**/Resistor(5,1)/Battery(6,1)。
chargeCells=[(-1,-1)..(-1,-5)]（本格上方 5 格竖列）。Battery(0,0) 的竖列=
(0,-1..-5)——**不在背包内**（y<0）→ oracle 实际电荷路径可能被出界裁剪/或
(-1,-1) 相对 node_cell 的原点语义不同（node_cell≠topLeft 的占格归一化——
锚点回退段注释）。gd 的 _chargeInventoryCells 映射把电荷送进了 (2,1)/(3,1)/
(4,1) 的 Coil——映射基面与 oracle 相反/差一个 anchor。
**下窗直入**：①读 gd _chargeInventoryCells 全文与 oracle 侧
Inventory.getCellsForGlobalPositions+getGlobalPointsForCells 的数学（含
collisionMapPosition 的 cmPos）→ 对 Battery(0,0) 算出 oracle 真实 5 格
（预期 y 全<0 出界=零到达）vs gd 算出的 5 格（误入 row1 的 Coil）→
修映射或出界裁剪（出界 cell 应 no-op 不 steal）。
②修后 Battery 簇 3 场复验；K2/K3/K1 余卡顺延。streak 判定待阶段末。

### r25 K4 终局（反转定谳+回滚；aligned=462，副指标=121,861）

- **K4 修复方向反转定谳**：冻结 tick 循环下 oracle 的 tween 永不推进
  → ElectricalCharge.start 的 tween callback（onNewCellEntered 2..n）**永不到点**
  → oracle 真行为=电荷**只 cell1 到达**（K4 前的 gd 原实现才是对的）。
  K4 排程让 cell2+ 到达 → Charge Splitter 提前 13 ticks 激活（2.0167 vs oracle
  3.5833）→ Coil steal 链爆发（Coil origin 104 vs 0）。
- **已回滚**（output/_round_patches/r25_k4/CoreItem.gd.bak 拷回）；gd_to_py
  重转写；三场复验：run1282 gdcore≡oracle（py 分歧=py 链重放待补——py 缺
  本轮回放产物，下窗补跑）；run1160/run1283 oracle≠gdcore 且 py 分歧
  （py 侧是回滚前转写的陈旧产物所致，重转写后应同步）。
- 语义先例归档：与 playCombatAni 闸同族——冻结循环下 AnimationPlayer/tween
  不推进 → 其回调消耗链不存在。**g de 教训**：凡 oracle 侧经 tween/动画驱动的
  逻辑，冻结循环语义=永不发生；内核不得补排程。
- K4 结论：Battery 簇真残差回到 idx95 前（run1282 gd≡or 现在只差 py 面）；
  Coil steal 链在 oracle 属后续时刻（3.366+ 的真实 steal 对），C6 luck/栈账族。

### r25 阶段 1 阶段末检验（回滚后复核）

- K4 回滚后一次波折：py 侧产物陈旧（回滚前转写）→ run1282 一度"py 分歧"
  退步 1 → 定位=--compare-only 不重放缺产物；--cases run1282（不带 --skip-py）
  强制重放 py → 复检 **462/917、退步 0**、副指标 **121,456**（vs 基线 121,861
  =**进步 405**）。快照 r25_s1.txt。
- **副指标判读**：aligned 持平 462 下副指标进步 405——K4 试验虽回滚，但
  K1-K4 攻坚期连带效应（CANMISS 桩时期外的台面净变化）+回滚后 run1282
  py 链重放对齐更好。判定：**接受，无退步**。
- K4 净结论：修复方向反转（冻结循环 tween 语义），电荷只 cell1 到达为
  oracle 真行为；gd 原实现正确。K4 从"待修"改判"无需修"。
- 卫生快照：gd CoreCharacter.gd 仍带 CANMISS v3 标记+[Gain] print 残桩
  （卫生债，已挂账）；CoreItem.gd 已回滚至 K4 前（备份双份在
  output/_round_patches/r25_k4/ 与 r25_fix1/）。

**r25 阶段 1 收口**：4 卡终判——K1 定谳（盲栈 22v18 无事件差，与 C5/C4
同根，未修挂起）；K2 标签槽（未修挂起）；K3 ManaOrb（K1 下游，挂起）；
K4 反转（无需修）。aligned 462 持平、副指标 121,456（进步 405）。
**阶段末判定：接受（副指标进步），无退步。**

**下阶段入口（r26，5-8 卡）**：
①栈账富余族（K1/C4/C5/C6 合并攻）——blind/lucky/empower 等 current 值
  无事件差，先攻 LG 激活计数链（Goobert.onItemActivated activations 门 vs
  邻接物品激活信号次数）——CANMISS v3 桩可直接复用（改打 blind/lucky）；
②标签槽时基（K2，槽域反相）；
③Crown 时基×blind 耦合；
④digest 残簇：poison×9/MF Lucky×8/ChessBoard×8/SpicyBanana×8/Banana×8/
  SoU Mana×7/Hammer 残 7。


## r26 发掘批 1（OffPeak 续10，462/917 持平，零码改，digest 20:43 版）

开局基线：compare-only 462（快照 r25_s1.txt=退步基线）、副指标 121,456。8 卡全部本次实查取证，
文件面互斥；oracle 全语料卡牌族 400 场扫描为新仪器结论。

**问题卡（8 张，主修文件面互斥）**：
- 卡A 栈账富余·LG 激活计数链（Blind×29）：run619_r18 首分歧=过期 7v5（事件史全同）；
  r25 CANMISS v3 铁证 0.85 帧 blind 22v18 零事件差。文件 gd_core_items/Goobert.gd:30-34/
  LightGoobert.gd:10-17（decomp 同构）。修法：CANMISS v3 改打 blind/lucky 分解+激活计数桩。
- 卡B 盲栈到期面（Banner×17+CrownBlind×5）：run727 banner blind 到期 OR 34 vs GD 2
  （t≈0 施加的到期、0.82+ 的永不到期）；run629 gd 反多 1 笔 10 层过期。
  文件 gd_core/CoreBuff.gd:236-248/336-358（decomp Buff.gd:150-167/252-276）。
  修法：giveStacksTemporary 多批并存 nextTemporaryTimeout 到期桩。
- 卡C 卡牌族 reveal 多触发（poison9/SoU-Health6/Crown-Health6/SoU-Mana7 等 ~40 场）：
  **oracle 全语料 400 场 0 笔卡牌事件**（黑桃A/愚者/恋人/小丑牌全零），gd 持续触发
  （run1024 愚者 0/2、run574 恋人 0/6）。Card/DeckofCards/TheLovers/TheFool 双侧同构。
  文件 gd_core_items/Card.gd:99-119+DeckofCards.gd:44-49。修法：CARD 标记桩定位 oracle
  恒不 reveal 的门（startActivation/链位）。
- 卡D 魔药条件触发门（Hammer×7 等）：run957 强力英勇魔药 OR0/GD2、run1396 0/4；
  run962/1293 双侧同触发（门值差非死火）。文件 gd_core_items/HeroicPotion.gd:4-17。
  修法：checkStamina stamina 实值桩。
- 卡E 袋生成死火 SpicyBanana（×8）：run686 OR origin=Spicy Banana 32 vs GD 0（其余 origin
  全同，lineup 双侧均无此物品=战斗期生成物）；gd Exclusive/SpicyBanana.gd:34-40 同构在位。
  文件=装配/生成链（OracleAlignBattle 装配清单 dump 桩定位，落修面待定）。
- 卡F 激活欠账族（Banana8+ManaOrb6+Blueberries13=27 场）：run841 香蕉激活 91v70（2s 桶
  均匀欠 1-2）、run604 魔法球迟 0.23s、run810 蓝莓 191/187。文件 gd_core_items/Food.gd+
  Banana/ManaOrb/Blueberries(+py)；若根在 CoreItem 冷却段→与卡G 协调移交。
- 卡G K2 标签槽时基（上批遗留直入）：CoreItem.gd:2786-2799 vs decomp Item.gd:6483-6494；
  Util.time 恒差 1 tick（r12 实证）。修法：槽位时戳 +1 tick 试验（r25 修法原文）。
- 卡H ChessBoard 捕获链（×8）：run675 首分歧 9.48 gd 缺黑色主教 5 笔施加（2盲+2毒+1冷）；
  BlackBishop.doCapturingEffect 同构。文件 Exclusive/ChessBoard.gd+Chess/ChessPiece.gd(+py)。

**通道表（文件→卡）**：Goobert/LightGoobert→A；CoreBuff→B；Card/DeckofCards→C；
HeroicPotion→D；装配链→E；Food/Banana/ManaOrb/Blueberries→F；CoreItem 标签槽→G；
ChessBoard/Chess→H。互斥无交叉；CoreItem 冷却段若涉卡F 与卡G 需先 G 后 F。

**队列不入卡**：MF Lucky×8（栈账富余同族，文件 MissFortune.gd 未占，卡A 修后复测）；
FalconBlade×5（r4_1 面2/面3 已知残留）。执行序建议：C（面最大）→A→B→G→E→F→D→H。

卫生：本轮零码改零插桩；CANMISS v3+[Gain] 残桩仍挂（r25 债，卡A 复用后剥）。

## r26 修复批1 卡B（盲栈临时到期面；CoreBuff 通道；BSCHED 桩落地，零行为改）

**改了什么**：gd_core/CoreBuff.gd 装 BSCHED 到期排程取证桩（修法"giveStacksTemporary
多批并存 nextTemporaryTimeout 到期桩"落地）——七点全 env 门控（ctx.rng.oracle_trace），
零 rng 消耗：GAIN（decomp Buff.gd:155-167 同位，施加分支 IDLE/RESCH/KEEP + 多批 tos 布局）、
CLEANSE（Buff.gd:258-278 同位，最远者选批）、POP（Buff.gd:317-320 同位，nextTemporaryTimeout
选批）、REARM（批次续排）、START（四分支标签 B1/B1P/B2/B3/FIRING）、STOP（停走保留 left）、
FIRE（到点 tick 位）。→python -X utf8 tools/gd_to_py.py 重转写。

**根因新证（两件，均本轮实查）**：
1. **卡B 原证据的 gd 侧 capture 陈旧**：align/gdcore/run727_r18 events=今日10:58，
   早于 b3_fix1 四分支模型落地（今日12:23-12:51，备份 output/_round_patches/b3_fix1/）。
   "OR34/GD2 到期差"是**旧码面**。现码行为以 py（13:01，post-b3_fix1）为准：
   oracle↔py run727 canonical 流 353 事件逐条同，**卡B 瞬弹面已被 b3_fix1 修复**
   （净化清空→同 dur 重施加的 ② 瞬弹，gd 侧亦复现；run688_r10 gd 新 capture
   13:19 与 oracle idx130/131 同帧瞬弹逐字对上）。
2. **现码残差 = ② 瞬弹 tick 位**：oracle↔py 首分歧 idx353——同两笔弹出，py
   tgt0@t_tick300 先于 tgt1@301，oracle tgt1@301 先 tgt0@301（同 pass 双弹）。
   即 gd ② 在施加同 tick 弹（BSCHED 行33/35：START br=B2 t=5.0 → FIRE t=5.0 同帧），
   oracle run727 晚一 pass。**但 oracle run688 锚（玩家相施加）同帧弹**——两锚在
   decomp/driver 源码（oracle_fight.gd drive_timers:883-920）内无可辨分支变量，
   疑 CT 相位差（对手相 stamp 恒早 1 tick），零码改不下针，留给统一复放窗口
   用 BSCHED START(B2)/FIRE tick 位对 rng_log 定谳。

**自证**：py 重放 run727_r18（非 Godot）两态——oracle_trace 关/开，events 与官方
align/py 产物**逐字节相等**（571135 字符 canon 串，两态各验一次）；BSCHED 捕 294 行。
备份 output/_round_patches/b1_c2/（CoreBuff.gd.bak md5 699c5b4c=改前、CoreBuff.py.bak、
probe_b1c2_chain.py、py_chain_trace.txt、bsched_rows.txt）。oracle 侧零触碰（未装桩，
语料全用既有 output/oracle/fights），无还原项。

**新债记档（非本卡文件，转交）**：py 侧 oracle_trace 路径两处既有崩点（r23/r25 债）——
①CoreEventBus.py:117/143 BUS/BCON 桩 `emitter.get()` 是 GDScript Object.get() 语义，
py 物品类无此方法（AttributeError）；②CoreRng.py:422 `_draw_signature` 用
PoolStringArray 未垫（NameError）。py 侧 trace 路径从未端到端跑通过；本卡以驱动器
本地垫片（probe_b1c2_chain.py 内 CoreItem.get + _draw_signature 补丁）绕行取证。


## r27 发掘批 2（OffPeak 续10，468/917（+3），零码改，digest 23:16 版+定向刷新）

**头条：gdcore 产物陈旧面**——890/914 场 gdcore events 仍是 b3_fix1（今日12:23-12:51）前产物，
23:16 的 465 基线大部分比的是旧码。本轮 --cases run605_r15,run900_r18,run1045_r18,run759_r11,
run792_r12,run939_r18,run699_r18 --force 刷新 7 代表场（串行 13.1s）→ **run605_r15/run900_r18/
run699_r18 三场直接转绿**；随后 --compare-only 全量恢复夹具=468/917。r26 的 MF×8 卡、SoU-Mana×7
卡、FalconBlade×5 队列全部划掉（陈旧产物假象）。**下批修复批第一件事=全量重放（非 compare-only）
重建真基线。**r26 卡C（卡牌族 reveal 多触发）撤销：刷新后 run900/run1045 愚者 0/0、恋人 0/0，
b3_fix1 连带修复。

**问题卡（7 张，主修文件面互斥，除注明外证据均为刷新后 fresh 产物）**：
- 卡R1 耐力账本/疲惫面（Thornbloom×5+ManaOrb×6+SoU-Health×6 首分歧同源）：run792_r12 首分歧
  5.03 gd 多 2 笔疲惫伤害（O 无）；run1045_r18 13.67 gd 耐力耗尽(不愈法杖) vs O 消耗4魔法；
  run604_r10 5.93 gd 疲惫伤害：2（O 5.75 魔法球+1）。文件 gd_core/CoreCharacter.gd:418 onTick/
  :958 useStamina/:1158 takeFatigueDamage/:1754 staminaRegen（decomp Character.gd:401/825/1598）。
  修法：per-tick stamina 快照桩定位多耗/少回。
- 卡R2 LG 激活计数链（Blind×29，r26 卡A 延续）：run619_r18 fresh 仍首分歧 188 行=过期 7v5。
  文件 gd_core_items/Goobert.gd:30-34/LightGoobert.gd:10-17。修法同 r26（CANMISS v3 改打
  blind/lucky 分解+激活计数桩）。
- 卡R3 盲栈到期相位/批次残面（Banner×17，r26 卡B 残余）：run727_r18 fresh 到期 **34 v 51 反转
  超发**、施加 76v75；首分歧 5.00 gd 对手相到期早 2 tick（O 5.02），玩家相 5.02 双侧同。
  文件 gd_core/CoreBuff.gd（BSCHED 七点桩在位）。修法=下轮入口原话：BSCHED START(B2)/FIRE
  tick 位对 rng_log 定谳 CT 相位差（疑对手相 stamp 恒早 1 tick）。
- 卡R4 SpicyBanana 袋生成死火（×8，r26 卡E 延续）：run686_r18 fresh 仍 OR 32 v GD 0。
  文件=装配/生成链（装配清单 dump 桩）。其余 origin 全同不变。
- 卡R5 激活欠账族（Banana×8+Blueberries×13 残+poison×8 部分）：run841_r12 fresh 香蕉激活仍
  91v70（2s 桶均匀欠）；run939_r18 fresh gd 多 1 笔魔法球+1@1.40（extra 方向，O 首笔 2.00）。
  文件 gd_core_items/Food.gd+Banana/Blueberries(+py)。
- 卡R6 ChessBoard 捕获链（×8，r26 卡H 延续）：run675_r18 fresh 仍 9.48 缺黑色主教 5 笔施加。
  文件 gd_core_items/Exclusive/ChessBoard.gd+Chess/ChessPiece.gd(+py)。
- 卡R7 K2 标签槽时基（r26 卡G 延续，完整证据直入不重查）：CoreItem.gd:2786-2799 vs decomp
  Item.gd:6483-6494。修法：槽位时戳 +1 tick 试验。

**通道表（文件→卡）**：CoreCharacter→R1；Goobert/LightGoobert→R2；CoreBuff→R3；装配链→R4；
Food/Banana/Blueberries→R5；ChessBoard/Chess→R6；CoreItem 标签槽→R7。互斥无交叉。
Cupcake×5（run759 充能 v 魔法拾取差+蓝莓序差）判 R1/R5 级联不入卡；Hammer×6 魔药面（卡D）
run957 fresh 未变仍挂队列。执行序：R1（覆盖面最广）→R3（桩已就位）→R2→R5→R7→R4→R6。

卫生：本轮零行为码改（仅 verify_oracle --cases 刷新产物+compare-only 恢复）；BSCHED 桩仍在
CoreBuff（上批债）；oracle 侧零触碰。


## r28 发掘批 3（OffPeak 续10，473/917（+3），零码改，digest 10:31 版+二轮定向刷新）

**环境注记**：①晨间有未记账修复——gd_core/CoreCharacter.gd 今日 10:04（py 10:18）大改
（f32 截断 _f32/tickPhysicsTimers/changeBaseMaxStamina 等 221 行，op11 f32 层落地），
台账无节，下批补记；②修复批定向重放 14 场（10:23）→470；③本轮再刷 5 场
（run712_r9/run625_r18/run905_r18/run1015_r18/run1070_r18 --force+compare-only 恢复）
→ **473/917**：run625(MF)/run1015(FlameWhip)/run1070(SoU-Health) 纯重放转绿。
r27 卡D（魔药）/MF 队列/FlameWhip/SoU-Health 全划掉（陈旧产物假象延续）。
**结论重申：444 场未重放，aligned 数仍失真，全量重放是第一优先。**

**问题卡（8 张，主修文件面互斥；除注明外均 fresh 产物）**：
- 卡T1 耐力账本双向漂移残面（ManaOrb×6+Thornbloom×5+ChessBoard 首分歧同源）：
  run604 5.93 gd 疲惫伤害：2（gd 先耗尽）；run792 5.03 gd 多疲惫伤害；**run675 fresh
  7.45 反向**：O 耐力耗尽(虚无之刃) vs G 攻击落空（gd 后耗尽）。晨修后仍残=量/率差。
  文件 gd_core/CoreCharacter.gd:418 onTick/:958 useStamina/:1158 takeFatigueDamage。
  修法：per-tick stamina 快照桩双向对位。
- 卡T2 LG 激活计数链（Blind×29，r26 卡A→r27 卡R2 延续）：run619 仍 5.57 过期 7v5。
  文件 gd_core_items/Goobert.gd:30-34/LightGoobert.gd:10-17。
- 卡T3 盲栈到期相位残面（Banner×17，卡B→R3 延续）：run727 fresh 到期 34v51 反转超发、
  首分歧 5.00 对手相早 2 tick（玩家相双侧同）。文件 gd_core/CoreBuff.gd（BSCHED 在位），
  修法=BSCHED START(B2)/FIRE tick 位对 rng_log 定谳。
- 卡T4 SpicyBanana 袋生成死火（×8，卡E→R4 延续）：run686 fresh 仍 32 v 0。
  文件=装配/生成链。
- 卡T5 激活欠账/多账族（Banana×8+Blueberries×13+poison×8）：run841 香蕉激活 91v70；
  run939 gd 多 1 笔魔法球@1.40；run905 gd 缺 1 笔蓝莓@2.98。文件 gd_core_items/Food.gd+
  Banana/Blueberries(+py)。
- 卡T6 ChessBoard 激活迟滞（×7，证据更新）：run712_r9 fresh 11.65 黑色主教 3盲+2毒
  → gd 同批事件迟 0.12-0.17s（11.77/11.82），净化插序。**r27 的 run675「9.48 缺失」
  证据作废**（耐力面前移遮蔽）。文件 gd_core_items/Exclusive/ChessBoard.gd+ChessPiece.gd。
- 卡T7 袋内热值倍数面（Chili×5 新簇）：run905_r18 fresh (4,5) 皮袋上红辣椒首火
  **+2 v +1 狂热**（其余 3 椒同 tick 均 1v1；battle_items params heat=1.0 与 oracle 同，
  cd 同）→格上物品袋倍数链多乘。文件 gd_core_items/Bag.gd getBagMultiplicity/
  getNumAffectedInside_type(+py)；若落 CoreItem.gd multiplicity 段与卡T8 分批。
- 卡T8 K2 标签槽时基（r26 卡G 延续直入）：CoreItem.gd:2786-2799 vs decomp Item.gd:6483-6494。
  修法：槽位时戳 +1 tick 试验。

**通道表（文件→卡）**：CoreCharacter→T1；Goobert/LightGoobert→T2；CoreBuff→T3；装配链→T4；
Food/Banana/Blueberries→T5；ChessBoard/Chess→T6；Bag.gd→T7；CoreItem 标签槽→T8。
互斥；CoreItem.gd 双涉面（T7 可能段/T8）已注明分批。Cupcake×5（run759 仍 diff）判 T1/T5
级联不入卡。执行序：T1（覆盖最广）→T3（桩就位）→T2→T5→T8→T6→T7→T4。

卫生：本轮零行为码改（两次 --cases 刷新+两次 compare-only 恢复）；BSCHED 桩仍在 CoreBuff；
oracle 侧零触碰；无 git 写操作。

## r29 第 0 步：全量重放重建真基线（OffPeak 续11，530/914，副指标 94,093）

- 删 align/gdcore+align/py 两目录 → 无 --force 全量重放（约 40 分钟跑完 914 场：
  gd 915 目录（914 场+summary）→ py 914）。
- **真实 aligned = 530/914**（旧失真读数 473；+57 场为新码下自然转绿）。
- 分布：三方一致 530 / oracle≠gdcore 382 / py 分歧各 1。
- 快照 op_v5_base.txt（本任务退步检基线）；副指标基线 **94,093**。
- digest 前簇（全部 ≤9 场小簇，大簇已清）：Blueberries×9/ManaOrb×9/Banana×9/
  Banner Blind×7/SoU 耐力×6/FalconBlade 耐力×6/length×6/Cupcake×6…
- r28 卡队列刷新：T1 耐力面（SoU/FalconBlade out_of_stamina 新亚形并入）、
  T5 激活欠账（Banana/Blueberries）、T2 LG 计数（Blind 簇大幅缩水）、
  T3 Banner 相位、T4 袋生成、T6 ChessBoard、T7 袋倍数、T8 标签槽。
- 下层入口（层 1，r29，3-5 卡）：按 r28 执行序 T1→T3→T2→T5→T8 直取。

### r29 层 1 T1-SoU 锚（压缩前；aligned=530，副指标=94,093）

- 全量重放完成：**真实 aligned=530/914**（旧读数 473 失真，+57 场新码自然转绿）。
  副指标 94,093。基线 op_v5_base.txt。场总数 917→914（3 场缺 gdcore 产物剔除）。
- T1-SoU 定谳推进：前 7 轮激活时刻双侧全同；**序 7 分歧=G@5.4167 多一轮成功
  治疗（Sufficient）vs O@5.4167 耐力耗尽（Insufficient，无 activate，原版
  activate() 在 if Sufficient 块内——缩进已核 2 tab）** → 耐力账面差 ≥1.3
  （7 轮×1.3 消耗后 gd 余 ≥1.3、oracle 余 <1.3）。SoU 脚本双侧同构排除。
- 下窗直入：stamina 账本快照桩（oracle_trace_log 标记行：takeDamage 前后/
  addStamina/useStamina 的 curStamina 值）→ 定位账差首现帧（候选：上限差
  changeBaseMaxStamina/回复率差 staminaRegen/FalconBlade 等耐力装备差）。
- 桩态：CANMISS v3+[Gain] 残桩仍在（CoreCharacter）；BSCHED（CoreBuff）在位。
- K2/K3/K4 前期定谳全部维持（K4=无需修）。

### r29 T1-SoU 锚 v2（STAM 快照已现；aligned=530，副指标=94,093）

- 发现 STAM 快照桩已在位（workflow 期某卡装，格式'USE f=t side amt res pre/post|max'），
  我的新桩添加失败（AssertionError=已存在同锚）——直接用现成桩数据。
- gd 侧 SoU 前 8 轮耐力账：side1 序6@5.3833 pre=3.2667 post=1.9667 SUF；
  side0 序7@5.4167 pre=3.2667 post=1.9667 SUF → **gd 两侧耐力余 1.97 ≥1.3 →
  第 8 轮治疗成功（mana-4 事件）**。oracle 同刻两侧耐力耗尽（type15）。
- max=7 双侧？oracle max 未知（无桩）——但 oracle 侧 7 轮后耗尽 → oracle
  max ≤ 9.1-回复 或回复率更低。**差异候选：getMaxStamina 或 staminaRegen
  的 Character 面值差**（b4 系晨修改过 changeBaseMaxStamina——r28 环境注记
  的 10:04 大改含此函数）。
- 下窗直入：①oracle 侧同款 STAM 快照（OracleProcDebug 门控 print 或
  oracle_trace 路径——oracle 无 oracle_trace_log 机制，用 print 桩+events
  自证）；②对照 max/regen 值面 → 修 gd CoreCharacter stamina 面。
- 桩态：STAM 桩（在位，来源待考）+CANMISS v3+[Gain]（CoreCharacter）、
  BSCHED（CoreBuff）——全部卫生债挂账。

### r29 T1-SoU 锚 v3（压缩前；aligned=530，副指标=94,093）

- STAM 桩已在位（b3_c1 取证桩：useStamina/gainStamina 双点，oracle_trace_log
  不耗链）——gd 侧 SoU 前 8 轮耐力账全清：side0 序7@5.4167 pre=3.2667
  （SUF 治疗成功）；oracle 同刻 Insufficient。
- 账面分解：Mage base=5、2 袋→max=7 ✓（gd STAM max=7）；gd 回复率≈0.24-0.3/s
  （每轮周期回复 0.3-0.4）→ 7 轮消耗 9.1 后余 1.97。
- **oracle 侧 7 轮后耗尽 → oracle 耐力账更紧**：候选=baseStaminaRegen=1.0
  （Character.gd:65 默认）与 gd 的 regen 值差、或 oracle max<7、或 oracle
  消耗面多（addStamina 面少）。需 oracle 侧耐力账（print 桩+events 自证）。
- 下窗直入：①oracle Character.gd useStamina 加 STAM print 桩（%.15f/str 拼接，
  events 自证+还原 md5）；②对照双侧 max/regen/每轮 pre 值 → 修 gd 差点；
  ③修后 SoU 簇 6 场（run592_r17 等）--cases --force 验证。
- 其余队列不变：T3 盲栈相位（BSCHED 在位）→T2 LG→T5 激活欠账→T8 标签槽。

### r29 T1-SoU 锚 v4（STAM-O 铁证；aligned=530，副指标=94,093）

- oracle STAM-O 桩（print 桩+events 字节自证 True+stdout 捕获）铁证：
  **oracle side=0 max=5 vs gd side=0 max=7**——同一 run592 同侧 max 差 2
  （=2 个 Stamina Sack 的 +1 加成 gd 侧生效、oracle 侧未生效）。
- oracle side0 耐力曲线：1.3667 pre=4.1 → 2.6 pre=3.03 → 3.8833 pre=2.0167
  → 5.15 pre=0.983 → **5.4167 耗尽**（Insufficient）✓ 与事件面吻合；
  gd 同侧 pre=3.2667（max=7）→ 治疗成功。oracle regen=1（side=1）。
- **真根收敛**：oracle 的 Stamina Sack +1/袋加成在战斗中未生效（max=5=
  classResource.stamina 裸值）；gd 的 recalculateMaxStamina 把袋算进去（max=7）。
  下窗：读 oracle/Items/StaminaSack.gd 或 Bag.gd 的 addToInventory 实际调用链
  （原版 changeBaseMaxStamina 的 call_deferred(recalculate) 在 oracle_fight
  冻结装配流中是否真的 flush——**call_deferred 在阻塞循环外每帧 flush，
  但 recalculate 依赖 items 集合**；若袋 addToInventory 发生在 PLAYER 场景
  复用后未触发 changeBaseMaxStamina（ownerType 闸），max 恒 5）→ 修 gd
  recalculateMaxStamina 的触发时机/ownerType 闸对齐 oracle。
- 桩态：oracle STAM-O 桩待还原（备份 output/_round_patches/r29_oracle_Character.bak
  md5 核验过）；gd STAM/CANMISS/[Gain] 桩在位（卫生债）。

### r29 T1 锚 v5（袋加成未生效=装配路径差；aligned=530，副指标=94,093）

- oracle side0 max=5（袋加成未生效）、side1 max=7（生效）——同场同物两袋、
  结果不对称！side1（opponent? player?）生效而 side0 未生效。
- 候选定谳：oracle_fight 装配路径对 PLAYER 复用对象不走 addToInventory
  （或 changeBaseMaxStamina 的 call_deferred flush 时机错位），而 OPPONENT
  每场新建走全链 → **装配路径不对称是 oracle 真行为**。
- 下窗直入：读 oracle_fight.gd 装配段（prepareItems/G.activateItems 前物品
  入包路径）+ gd_core_test/OracleAlignBattle.gd place_one 的 addItem 面对照
  → gd 装配层对 PLAYER 侧袋补齐/裁剪对齐 oracle 不对称行为。
- 桩态：oracle STAM-O 已还原（md5 821f2a33 ✓）；gd 桩挂账同前。

### r29 T1 锚 v6（袋加成 ownerType 闸定谳；aligned=530，副指标=94,093）

- **全解**：oracle ID 枚举 side=0=OPPONENT/side=1=PLAYER。oracle：
  side1(PLAYER) max=7（袋+2 生效）；side0(OPPONENT) max=5（袋加成**不生效**——
  StaminaSack.addToInventory 的 ownerType==PlayerInventory 闸拦下对手侧袋）。
  gd：两侧都 max=7 → **gd 对手侧袋加成误生效**。
- 修法方向：gd_core_items/StaminaSack.gd addToInventory 闸在位（读过）——
  但 gd 装配 place_one 传 ownerType 的时点/值可能晚于 addToInventory 调用
  （ownerType 在 addToInventory **之后**才赋值 → 闸读到默认值 0=Player？）。
  下窗：①读 gd place_one 的 ownerType 赋值序 vs addToInventory 调序；
  ②STAM 桩加 ownerType 值验证；③修序后 SoU 簇 6 场复验。
- 影响面：所有 Stamina Sack 出现的场次（耐力账本族）。

### r29 T1 锚 v7（side 映射定谳+最后缺口；aligned=530，副指标=94,093）

- side 映射定谳（1.35 治疗事件 tgt0 双侧同）：side1=tgt0 持有者 max=7 双侧同；
  **side0=对侧：oracle max=5 vs gd max=7**——gd 对侧袋加成误生效实锤。
- oracle 行为：袋加成只对 PLAYER 侧生效（StaminaSack.addToInventory 的
  ownerType==PlayerInventory 闸拦下对侧袋）——对侧 max=base=5。
- gd 侧对侧袋也触发了 changeBaseMaxStamina（闸存在却未拦）→ 剩余唯一缺口=
  **gd 对侧袋的 ownerType 在 addToInventory 时点并非 Opponent(3)**（推断闸
  或赋值时序），或 changeBaseMaxStamina 另有调用方（recalculate 触发面）。
- 下窗直入（三选一收口）：①STAM 桩加 ownerType 字段重录 run592（零耗链）
  直接读对侧袋 addToInventory 时的 ownerType 实值；②grep gd changeBase
  MaxStamina 全部调用方（除 StaminaSack 外还有 StaminaSack.onRemove/
  装配层？）；③修 gd_core_items/StaminaSack.gd addToInventory 闸为
  ownerType == CoreConst.Owner.PlayerInventory 且 place_one 先设 ownerType
  再 addItem（顺序已 ✓）——若 ①示 ownerType=1 则是装配面错传。
- 修后 SoU 簇 6 场（run592/601/615/639/722/783）复验。T1 修通预期连带
  out_of_stamina 族全绿。

### r29 T1 锚 v8（max 分解定谳：两侧 ms=7 tmp=0；aligned=530，副指标=94,093）

- STAM v5（ms/tmp 分解）：两侧 **ms=7（maxStamina 本体含袋加成）、tmp=0**——
  gd 的对手侧袋加成确实写进了 maxStamina 本体。
- oracle 侧 STAM-O：side=0 max=5——**oracle 对手侧 maxStamina=5（袋未算）**。
- 结论固化：gd 的 StaminaSack.addToInventory（对手侧袋）触发了
  changeBaseMaxStamina→recalculate（ms=5+2=7）；oracle 同链被
  ownerType==PlayerInventory 闸拦下（对手袋 ownerType=OpponentInventory≠1）。
- **gd 闸失效根因候选**：gd place_one 装配时对手侧 owner_type 传参正确（=3），
  但 CoreGrid.addItem→item.addToInventory 的调用发生在 ownerType 赋值**前**
  （place_one :279 赋值 → :288 addItem ✓ 顺序对）→ 或 gd 的
  StaminaSack.addToInventory 里读的 ownerType 是 **addToInventory 自身
  参数 _placedByPlayer 影响的别的面**——直接单步：STAM 桩加袋加成触发标记
  （changeBaseMaxStamina/recalculate 头部打 MARK 行：bag reset 触发者 side）。
- 下窗直入：changeBaseMaxStamina/recalculateMaxStamina 头部加安全标记行
  （oracle_trace_log，含 self.playerId）→ run592 重录 → 谁触发了对手侧
  recalculate 一眼定谳 → 修闸 → SoU/FalconBlade 耐力族 6 场复验。

### r29 T1 锚 v9（层 1 末锚；aligned=530，副指标=94,093，T1 攻坚至最后一步）

- 原版 initHistoryOpponent（Game.gd:2829+）链：setMaxStamina(roundData.stamina)
  → 袋 addOpponentItem（ownerType=Opponent）→ baseMaxStamina=class.stamina
  → **recalculateMaxStamina()** → maxStamina=getBaseMaxStamina()+每袋 1
  （recalculate 数 descriptor==StaminaSack 不看 ownerType）→ 对手侧应 7。
- 但 oracle STAM-O 实测对手侧 max=5——**矛盾指向 roundData.stamina（历史
  快照的 stamina 记录值）可能非 5**（setMaxStamina(快照值) 若>recalculate
  结果则被 recalculate 覆盖；若 recalculate 的 getBaseMaxStamina 读
  baseMaxStamina=5 → 5+2=7 仍 7）——唯一余项：**buildHistory 的
  roundData.stamina 快照值 = 袋加成生效前的战斗态**，recalculate 之后
  maxStamina=7，但 **curStamina=maxStamina=7？STAM-O 打印 max=5 仍矛盾**。
- 收口方案（下窗，预算集中）：oracle STAM-O 桩扩展打 baseMaxStamina/
  maxStamina/temporary 三值+initHistoryOpponent 后打一次 → 精确定位
  oracle 对手侧 max=5 的写入者；同时对照 gd prepare() 的显式 recalculate
  （b2_c1 补的）是否过度——**候选修法=gd prepare() 的 recalculate 移除
  袋项计数（对齐 oracle 的对手侧实际值 5）或两侧都不算袋**——以 oracle
  扩展桩数据为准，禁投机。
- 层 1 其余卡（T3 盲栈相位/T2 LG/T5 欠账/T8 标签槽）证据全部在台账，
  预算恢复后按序续。
- 桩态汇总：gd CoreCharacter（STAM v5/RECALC/CANMISS v3/[Gain]）+
  CoreBuff（BSCHED）全部 env/trace 门控（不耗链，卫生债挂账）；
  oracle Core/Character.gd 已还原（md5 821f2a33 ✓）。

## r29 层 1 收口（OffPeak 续12，530/914 持平，副指标 94,084=进步 9，接受）

**T1 耐力账本族—— Stamina 上限面双修落地（核心成果）**：
- **定谳链（五版探针）**：STAM-O v3（战斗期袋计数）+RECALC-O-TAIL（recalc
  尾值）+SETMAX（覆写者追踪）→ oracle 真行为：**PLAYER 战斗 max=base+袋
  （tick1 deferred recalc，side1=7）；OPPONENT 恒=快照基值 5（袋不进 max，
  initHistoryOpponent 的 recalc 结果被快照序覆盖）**。run592 实证：
  oracle side1 sacks=2 max=7 / side0 sacks=2 max=5。
- **双修**：①tools/gen_fixture_from_lineup.py `_battle_start_stamina` 的
  opponent 分支改 `return OPP_BASE_STAMINA, OPP_BASE_STAMINA`（不数袋，
  夹具 stamina 字段 7.0→5.0 核验 ✓）；②gd_core/CoreCharacter.gd prepare()
  的 recalculate 改 side 闸（PLAYER=recalculate 数袋；OPPONENT=maxStamina=
  baseMaxStamina 不数袋）。
- **修后核验**：gd STAM 复录 side0(PLAYER)=7/side1(OPPONENT)=5 双侧数值
  与 oracle 完全一致 ✓。耐力族 6 场仍 0/6 但首分歧全部推进（run592
  idx282→278，5.3833 帧从"gd 多一轮治疗"变为"gd PLAYER SoU 触发晚 4 tick"）。
- **残余定性**：stamina 上限面已清，剩余=触发时刻差（2-4 tick）——SoU
  持有者首抽 gd@1.3167 vs oracle@1.35——属冷却/触发时差族（T5 面）。
- 层 1 判定：530 持平、副指标 94,093→**94,084**（进步 9，≤200 容差内接受）。
  快照沿用 op_v5_base（无净变化）。
- 卫生：oracle STAM-O/RECALC/SETMAX 三桩全部还原（md5 821f2a33 ✓ 备份
  r29_oracle_Character.bak2）；gd 侧 STAM v5/RECALC/CANMISS/[Gain]/BSCHED
  trace 门控桩挂账（不耗链）。无 git 写操作。

**层 2（r30）入口**：①T5 触发时差族（SoU/香蕉/蓝莓 2-4 tick 漂移，
  stamina 面已清后这是耐力族真残差）；②T3 盲栈相位（BSCHED 桩在位）；
  ③T2 LG 激活计数；④T8 标签槽时基。每卡修完定向验证。

## r30 层 2 发掘（OffPeak 续12，530/914，零码改）

- **T5 触发时差定性收口**：双侧 PLAYER SoU 六轮时刻对照
  （gd 1.35/2.7667/4.0833/5.4167/6.75/7.9167 vs oracle 1.35/2.75/4.0833/
  5.40/6.7667/8.05）=**±1 tick 交错抖动**（每轮 adjustCooldown 的
  randf(0.975-1.05) 抖动值级差，rng 链微差），非系统性偏移。首分歧
  5.3833 heal 缺失=第 4 轮恰跨帧。判定：非本轮攻面（需逐轮抖动值对位，
  每场收益 1-2 事件），挂起。
- 层 2 问题卡（4 张）：U1=T3 盲栈到期相位（run727_r18，BSCHED 七点桩在
  位，34v51 反转超发+对手相早 2 tick）；U2=T2 LG 激活计数（run619_r18
  过期 7v5）；U3=T8 标签槽时基（CoreItem.gd:2786-2799，槽位时戳 +1 tick
  试验）；U4=Blueberries×13 同 tick 序差（run810 idx194）。
- 执行序 U1→U2→U3→U4。

### r30 层 2 进行中锚（压缩前；aligned=530，副指标=94,084）

- T5 触发时差收口=±1 tick 抖动（挂起，见 r30 发掘节）。
- U1=T3 run727 深挖：5.0-5.0167 帧双侧盲事件对照——oracle 5.0167 同帧双弹
  （tgt1 先 tgt0 后）；gd 5.0 tgt0 单弹（早 1 tick）+5.0167 tgt1 弹。
  BSCHED：gd@5.0 START br=B2（resync）+FIRE n=1（tos 10x1，疑另一实例/
  对手侧旧批）；oracle 同位无双弹。**定性=对手侧旧批到期 gd 早 1 tick +
  弹出次序反**——与 r28 卡T3『CT 相位差（对手相 stamp 恒早 1 tick）』同源。
- 下窗直入：①BSCHED 打印加 character side（playerId）分离两实例；
  ②oracle 侧同窗 BSCHED（Buff.gd 装同款桩+自证）对照对手侧 FIRE tick 位；
  ③若 oracle 对手 FIRE=5.0167 vs gd 5.0 → 修 gd 对手侧计时 1 tick
  （怀疑点=onTimeout 批次重启的 resync=false 支在对手段多扣 1 遍）。
- U2/U3/U4 队列不变。桩态：gd BSCHED/STAM/CANMISS 挂账；oracle 净。
### r30 U1 锚（压缩前；aligned=530，副指标=94,084；B1P 两版修未转绿，试验态保留）

- BSCHED side 分离实锤：gd side=0 @5.0 START(B2 resync) 后同帧 FIRE
  n=1 tos=[10x1]（新批 timeout=10 自弹）；oracle 同位 5.0167 双弹（tgt1 先）。
- B1P 两版修（resync=false→true）未改变行为——FIRE@5.0 的触发路径不在
  ①' 分支，疑 gainTemporary 的 delay<=0.01→onTimeout() 递归弹，或
  nextTemporaryTimeout 悬空指针（重施加后未重指）。
- 下窗直入：①BSCHED FIRE 行补打 nextTemporaryTimeout 与 delay 值（一行）
  → 定谳 FIRE@5.0 由哪条路径触发（_tick 扣减 vs onTimeout 递归）；
  ②按定谳修（若递归弹=重施加后 nextTmp 重指，或 delay 判据对齐 oracle
  timer.start 语义）；③Banner 簇 9 场复验。
- B1P 试验修改保留在树（resync=true 语义有 r30 证据支撑，但需随定谳复核
  是否回滚）；备份 output/_round_patches/r30_u1/CoreBuff.gd.bak。

### r30 U1 锚 v2（压缩前；aligned=530，副指标=94,084）

- **FIRE@5.0 触发路径定谳（POP 桩铁证）**：净化清空→重施加（START B2 +
  GAIN IDLE next=0，新批 timeout=10x1）→ **FIRING 链内同帧再入 onTimeout →
  POP idx=0（弹新批 10x1）**。oracle 同位：新批 start(5) 后 5s 才弹
  （timer.start 语义，当帧不再入）。
- **修法定案**：gd gainTemporary 的 IDLE/重施加分支在 _timer_firing 期间
  （或 onTimeout 递归深度>0）**不得再入 onTimeout**——加 _timer_firing
  守卫或递归闸：重施加后若 _timer_firing=true 则只重排 timer 不立即弹。
- 下窗直入：①gd_core/CoreBuff.gd gainTemporary 尾的 delay<=0.01→onTimeout()
  递归处加 `if not _timer_firing` 闸（或 _onTimeout_depth 计数器）；②
  run727 复录 BSCHED 核对 FIRE@5.0 消失→5.0167 双弹对齐；③Banner 簇 9 场
  +LG 簇复验；④B1P resync=true 试验修改随定谳复核（可能需回滚）。
- 桩态：gd BSCHED side 版/STAM v5/RECALC/CANMISS/[Gain] 挂账（不耗链）；
  oracle 净（md5 821f2a33）。无 git 写操作。

### r30 U1 锚 v3（压缩前；aligned=530，副指标=94,084；MARKA/MARKB 定谳）

- 互斥标记实锤：FIRE@5.0 → MARKA（_tick onTimeout 前，left=0）→ POP
  idx=0 batch=10x1。START(3109) 行号先于 FIRE(3152)——重施加先于旧批
  到期判定 → **同帧时序=重施加(START left=5) → 旧批判定仍用旧 left=0 →
  弹 idx=0=新批（旧批已净化的空位）** = 重施加批被同帧旧批到期链误弹。
- 修法定案：gainTemporary 重施加后（START/GAIN 后）**跳过同帧剩余到期
  判定**——即 onTimeout 链内在 _startTimer 调用后置一个「本帧到期判定
  终止」闸（_timer_firing 已在，可在重施加支后 return/break 语义）——
  对齐 oracle：timer.start(5) 后本帧不再 fire。
- 下窗直入：①gd _tick 的 onTimeout() 调用点（_tick 内）在 onTimeout
  返回后若检测到 _timer_active 且 left>dur 差异（本帧已重施加）→ 不再
  续走同帧后续 FIRE 判定；或 onTimeout 内重施加支后直接置
  _timer_firing=false+return（终止链）；②run727 复录验证 5.0 弹消失、
  5.0167 双弹对齐；③Banner 簇 9 场+LG 簇复验。
- B1P resync=true 试验修改保留在树（随本修复核）；MARKA/MARKB 桩挂账。

### r30 U1 锚 v4（压缩前；aligned=530，副指标=94,084；U1 两版修未转绿，暂停转 U2/U3）

- 行号时序矛盾：START(3109) 先于 FIRE(3152) 但语义上重施加应在旧批 FIRE 后
  （净化的 onTimeout 链内）——同帧双实例/同实例重演未收口。
- U1 两版修（B1P resync=true、FIRING 递归闸）均未转绿，**保留在树**
  （resync 语义有证据支撑，随定谳复核）；MARKA/MARKB 桩挂账。
- 下窗方案：gd _tick 全文逐行重演 5.0 帧（含 onTimeout 链）+oracle 侧
  Banner 脚本装安全桩对照——精确定位「重施加批被同帧误弹」的执行序。
- **转 U2/U3/U4**（预算优先给可收口卡）。层末检验照做。

### r30 卫生（MARKA/MARKB 试验桩已剥；BSCHED 主桩保留挂账；gd_to_py 重转写）


## r30 发掘第 1 批（OffPeak 续12，530/914，零码改，卡片 7 张）

- 仪器：digest 全簇 + alignment.json 首分歧 + fights/align 双侧事件流对读（多重集/逐位前缀）。
- 新证据卡：B2 序差族（46 场同 tick 到期序，run810 idx194 多重集近似序反转 + run604 idx64 反应序）；
  B3 放大翻面（run905 idx49 O[1,1,1,1]vs G[2,1,1,1]，=Buff.gd:123-126 负 resistChance 翻面判定差，
  全场翻面占比同 42%、总差=时长级联 2602/3627 tick）；B6=length×6 真根=M12 事件数>25000 止损闸
  只在 oracle（run685 result.txt status=timeout、事件前缀 25030 逐位同、winner=-=未判胜非平局）。
- U2 重定性（run619）：施加史双侧全同 4×7（2.5333/2.5833/4.65/4.8833）+ Crown -1×4 同刻
  （3.5167/3.6833/5.0167/5.15）→ 首到期弹 O=-7/G=-5 = gd 净化 farthest 选批把 2 层削进 LG 首批
  （CoreBuff loseStacks 选批/timeout 值差，与 U1 同文件并卡）。
- T5 耐力抖动族补证不立卡：run722 双侧 gain 24v24 全同、oos 27v28、时长 2461/2612——纯 ±1 tick 抖动，挂起维持。
- 卡表（主修文件面互斥；gd X.gd 与 py 镜像同面）：
  | 卡 | 簇(场) | 代表场 | 主修面 | 下一步 |
  | B1 | Banner×7+LG×23(+op10 族) | run727 idx353/run619 idx307 | CoreBuff.gd | ①重施加同帧到期闸②CLEANSE 选批双侧对照③tick 化 |
  | B2 | 同tick序差≈46 | run810 idx194/run604 idx64 | CoreCombat.gd⑦ | drive_timers reg.keys() 全局平序 vs 分块序对表 |
  | B3 | Chili×5 | run905 idx49 | CoreRng 链位 | AMP 桩双侧对照（gd CoreItem.gd:1291 已在） |
  | B4 | Crown 无敌×5 | run1054 idx191(352vs353) | CoreCharacter.gd _invul | resync/instant 三分支 vs changeTimer 对表 |
  | B5 | 标签槽(U3) | 台账 r30 卡 | CoreItem.gd:2794-2806 | 槽位时戳 +1 tick 试验（现码无） |
  | B6 | length×6 | run685(25030 逐位同) | OracleAlignBattle.gd 宿主 | 补 M12 事件数>25000 止损闸（status=timeout/winner=-） |
  | B7 | ChessBoard×5 | run712 idx316(11.65 缺) | ChessBoard.gd(+shuffle) | activation 时戳桩 + fam_r1 洗牌残留并查 |
- 桩卫生：本轮零桩零码改；oracle/Core/Character.gd:1153-1157 [Gain] env 门控桩=已入库残留
  （git oracle/ 干净，非未还原），无害挂账。B1P resync=true 试验态仍在树（备份 r30_u1/CoreBuff.gd.bak）。
- 执行序建议：B6（零风险宿主闸，+6 潜力）→ B1（证据最全）→ B2（46 场最大簇）→ B4/B5 → B3/B7。


## r30 发掘第 2 批（OffPeak 续12，533/917（基线 530/914 涨 3=gdcore 缺产物新增），零码改，卡片 6 张）

- 仪器：digest 11:16 版全簇 + alignment.json perCase 三代表场首分歧逐字 + Cog 证据链（描述符/阵 容/gd 实现）。
- **新定谳 A（Cog 开战护盾减半，4 场）**：run683_r9 首分歧=idx0（开战第一事件）t=0 Cog
  Block O=14 vs G=7（恰 2×），**胜负翻转** O=player/G=opponent（高价值）。阵容 player 有
  3×Cog+Forging Hammer；gd 描述符 block=5（gd_core_runtime.json items.Cog.descr）实发 7
  → 7=(5+gem2)×1 vs oracle 14=(5+2)×2 → **numAffected 2v1**。核心嫌疑
  =gd_core/CoreItem.gd:3101-3103 getAffectedItems 缓存判空缺陷（整 dict 非空即返回
  cachedAffectedItems[color]，键缺/ crafted 后缓存陈旧不失效）；次要嫌疑=isCrafted 时序。
  gd_core_items/Exclusive/Cog.gd:7-11 =giveBlock(getBlock()*numAffected)。
- **新定谳 B（out_of_stamina 资源抵扣族，20 场）**：4 簇同模式（FlameWhip6 run813_r12/
  SoU5 run601_r18/FalconBlade5 run722_r7/CupcakeStaff4 run684_r13）首分歧=同 t 异事件：
  run813_r12 idx442 t630 O type15 耐力耗尽 vs G type104 尖刺-1 used=true——gd 有余尖刺
  抵扣致不耗尽。r29 修的是 stamina 上限面；此为**消耗闸/抵扣次序面**（非 T5 抖动）。
- 卡表（主修文件面互斥；gd X.gd 与 py 镜像同面）：
  | 卡 | 簇(场) | 代表场 | 主修面 | 修法 |
  | C1 | Blind LG23+Banner5(+翻面) | run619 idx307(-7v-5)/run727 | CoreBuff.gd | ①重施加同帧到期终止闸(U1 v3 方案)②loseStacks 选批对表③Buff.gd:123-126 翻面对表 |
  | C2 | 同tick序差≈82(13+9+8+6+46) | run925_r18 4.55/run810 idx194 | CoreCombat.gd | drive_timers reg.keys() 平序→oracle 分块序对表 |
  | C3 | Crown5+out_of_stamina20 | run1054 idx191/run813 idx442 | CoreCharacter.gd | ①_invul 三分支 vs changeTimer ②尖刺/魔法抵扣门 vs 归零判定次序 |
  | C4 | 标签槽+Cog4 | run683_r9 idx0 | CoreItem.gd(+Cog.gd 同面) | ①getAffectedItems 缓存改 per-color 判+crafted 失效②isCrafted 时序③标签槽 +1tick 试验(U3) |
  | C5 | length×7 | run685(25030 逐位同) | OracleAlignBattle.gd 宿主 | 补 M12 事件数>25000 止损闸(status=timeout/winner=-)；B3 簇消失,run905 并入本卡 |
  | C6 | ChessBoard×5 | run712 idx316(11.65 缺) | ChessBoard.gd | activation 时戳桩+fam_r1 洗牌残留并查 |
- 上批遗留对号：U1→C1（B1P resync=true 试验态在树待复核）、U2→C1、U3→C4、U4→C2。
- 执行序建议：C5（零风险+7）→ C4（idx0+胜负翻转, 嫌疑面已缩到两处）→ C1（证据最全）→ C3 → C2 → C6。
- 桩卫生：本轮零桩零码改；B1P resync=true 试验态仍在树（备份 r30_u1/CoreBuff.gd.bak）。

## r31 发掘第 2 批（OffPeak 续13，534/917（基线 533/917），重放 lines=93385，零码改，卡片 4 张）

- 仪器：digest 全簇 + verify_oracle.canonical_stream/render_lines 行级对读（新探针 output/_r31_probe.py）+ 块级多重集 + localization 证据桶 + 双侧脚本 diff。
- 新发现主面：**物品/角色层 stack 账隐性漂移**（事件流不可见，首次随机选取即现形，≈40+ 场）与**戒指 effects 重掷面**（SuperiorRing 双侧同映射 MagicRing.gd，per-instance effects 双侧数据源不同）。
- 卡表（主修文件面互斥；gd X.gd 与 py 镜像同面）：
  | 卡 | 簇(场) | 代表场 | 主修面 | 修法 |
  | D1 | 杯糕6+香蕉9+线圈(1108)+奶酪/蓝莓 | run1108_r18:166/run759_r11:80/run841_r12:62 | CoreItem.gd 计数基 | 对表 oracle Item/Character getStacks 计数口径（静默层源），pick 处池内容桩对表；同文件 C3/C4 串行 |
  | D2 | 戒指族(MagicRing×8+SuperiorRing) | run627_r11:1/run697_r15:9 | gen_gd_core_data.py+gen_lineup_fixture.py+MagicRing.gd:171-173 | 描述符/夹具携带 per-instance effects（oracle BitStream 持久数据），gd 侧禁 randi_range 重掷 |
  | D3 | MrsStruggles 触发链/事件父链 | run846_r11 | gd_core_items/Exclusive/MrsStruggles.gd(+CoreEvent 父链) | t=0 双侧施加链：G 把玩家侧冰冷挂到对手侧事件下(depth2 parent11)，O 为独立 depth1；onApplied 链对表 |
  | D4 | 纯转写 1 场 | run1151_r13:51 | gd_core_py | 世界树树叶 heal G22/P26；py 镜像行为差，修后 gd_to_py+compare-only |
- 并卡注记（不占新卡位）：魔法球反应触发接线（run985_r12 丢+2@7.93/8.08 双发/8.83 减半；run646_r18 t7.18 G 多 1；run758_r15）→ **C4 扩展证据**；英勇魔药缺恢复2耐力+充能1（run595_r18 t7.30）=耐力账面差 → **C3 扩展证据**；t=0 结构错位桶≈29 场部分=D2 戒指级联，修 D2 后复对。
- 上批遗留对号：B 系/C 系簇位次未见收敛（C1-C6 仍未落地）；本批 D1-D4 为新面，不与 C 系抢执行序，建议 D2（+8 潜力，双表机械改）→ D3（idx4 铁证）→ D1（大簇）→ D4。
- 桩卫生：本轮零桩零码改（output/_r31_probe.py 只读探针）；oracle/ 未动；无 git 写操作。

## r31 发掘（OffPeak 续13 收口后盘点，534/917，副指标 93,385，零码改）

**盘面**：534/917（+4：run604/run810/run925/run1054——B2 序差族首战兑现）。
首分歧 Top 类型：Blind×48（LG23+Banner5+余）、out_of_stamina×42（FW6+SoU5+
FB5+Cupcake4+余）、Mana×37、Health×27、Heat×24、Lucky×20。

**问题卡 18 张（层 1-2 遗留+digest 现簇合并；★=证据已闭环可直修）**：
1. ★T1r 耐力上限族残面（out_of_stamina×42 分解）：FW×6+SoU×5+FB×5+Cupcake×4
   同款「O 耗尽 vs G 消耗X」——T1 双修（PLAYER7/OPP5）已清大头，残面=这些物品
   的 staminaCost/使用序差。代表 run813/run601/run722/run684。文件=各物品.gd+
   CoreCharacter stamina 面。
2. ★B2 序差族（≈46→已部分兑现）残面：同 tick 到期/反应**序**差——
   CoreCombat⑦ drive_timers reg.keys() 全局平序 vs gd 分块序。代表 run810/run604。
3. ★B6=length×6：oracle M12 事件数>25000 止损闸只在 oracle——gd 宿主补同款闸
   （OracleAlignBattle.gd，status=timeout/winner=-）。零风险 +6。
4. LG Blind×23（T2 激活计数）：run619/668/702 过期 7v5。文件 Goobert/LightGoobert。
5. Banner Blind×5 残（T3 相位）：run727 等。文件 CoreBuff（BSCHED 在位）。
6. Blueberries Mana×12：run985 等「O 魔法 vs G 狂热」同刻反应序差。
7. Banana Health×9：run841 激活 91v70 欠账。
8. Mana Orb Mana×8 残：run758 等（T1 修后残面）。
9. Cupcake Health×6：run759 等「O 治疗 vs G 蓝莓魔法」同刻序差。
10. ChessBoard Act×7：run712 等激活迟滞 0.12-0.17s。
11. Magic Mirror Vampirism×4：run646 等。
12. Cog Block×4（开战 idx≤2）：run683 等 14v7 护盾——开战 block 面值差。
13. Cupcake Staff 耐力×4：run684 等。
14. Amulet of Light Regen×4：run697 等触发序差。
15. Heroic Potion stamina_gain×4：run595 等。
16. Miss Fortune Lucky×6：run734 等（luck 栈账）。
17. MF/Heat×24+Spikes×14+Regen×19 杂簇合并排查卡（digest Top10 外散簇）。
18. 卫生卡：BSCHED/STAM/CANMISS/[Gain] 桩剥离（全 trace 门控不耗链，随本层末清）。

**串行修复序（依赖+收益排）**：
第 1 批：#3 B6（零风险+6）→ #1 耐力族残面（42 场最大簇）→ #2 B2 序差（46 场）
→ #6 Blueberries → #7 Banana（同 Food 面）。
第 2 批：#4 LG×23 → #5 Banner 残 → #8 ManaOrb 残 → #9 Cupcake → #12 Cog。
第 3 批：#10 ChessBoard → #11 Mirror → #13 CupcakeStaff → #14 AoL →
#15 HeroicPotion → #16 MF → #17 杂簇 → #18 卫生。

## r31 第 1 批卡 #3（B6=length 族，M12 事件闸双侧补齐）

- gd 宿主（gd_core_test/OracleAlignBattle.gd 主循环）：补 events>25000 提前
  判停闸（对位 oracle_fight.gd:742-744；计数源=probe.rows）。
- py 引擎（simulator/gd_core_engine.py run 主循环）：补同款闸
  （len(self.log.events)>25000 → break）。
- 验证（7 场 --force）：gd 侧 run685 事件数 25030 与 oracle 逐位同 ✓
  （闸生效）；gdcore≡oracle 4 场（gd 腿已清）但 py 腿仍分歧——py 侧
  单 tick 事件爆增（29100=25000+~4000 单 tick 增量）说明 **py 上游链已
  分叉**（非闸面），闸保留（宿主语义对齐），4 场重分类为 py 链排查卡。
- run985（本簇第 7 场）oracle≠gdcore idx618 Eggscalibur——非 length 面，
  簇计数误差（digest 的 length 签名把它计入），维持原卡归属。
- 台账结论：#3 完成（gd+py 闸落地，gd 腿清 4 场待全量重放确认）。
  备份 output/_round_patches/r31_c3/。

## r31 第 1 批卡 #1（耐力族，终极模型三修落地，gd 5.3833 帧转同构）

- **终极模型三方调和定谳**（RECALC-O-TAIL 双场探针+b1_c3 账本重建+b2_c1
  快照桩）：oracle PLAYER=跨场复用对象、staminaUpdateQueued 残留 →
  changeBaseMaxStamina 恒早退、deferred recalc 永不跑 → **PLAYER 战斗
  max=快照基值（袋不数）**；OPPONENT=每场新建 + initHistoryOpponent:2857
  尾部显式 recalc → **OPPONENT max=base+袋（数袋）**。run592/813 双场
  RECALC-O-TAIL 铁证（OPP maxNow=7 sacks=2）。
- **三修落地**：①gd_core_items/StaminaSack.gd addToInventory 闸改
  Opponent 触发（PLAYER 关，模拟跨场 queued 早退）；②gd_core_test/
  OracleAlignBattle.gd 对手装配尾补显式 o.recalculateMaxStamina()
  （对齐 initHistoryOpponent:2857-2858）；③gen_fixture 维持 b1_c3 语义
  （opponent battle-start=base，战斗期由②顶到 base+袋）。
- 验证（9 场 --force）：0/9 但**首分歧全面深推**——run592 idx278 的
  5.3833 帧转**同构**（O/G 均三事件 SoU heal+False Life+Act+ManaOrb 后
  5.4167 双 OOS 对齐，gd 恰缺 5.3833 首行 heal=时序差 1 tick）；
  run813 idx442→446（10.5 断粮帧已同构，残差=Wooden Buckler 反应序）；
  run601/615/844/862 首分歧类型已离开耐力面（转 mana/dmg/spikes 序差）。
- 残差定性：耐力账本面已清（双侧断粮时刻同构），剩余=±1 tick 触发抖动
  +下游反应序差（B2 序差族下游）。卡 #1 收口，台账记。
- 备份 output/_round_patches/r31_c1/。

## r31 第 1 批层末检验（534/917，快照 r31_l1.txt，判定：接受）

- 场数 530→**534**（+4：run604/run810/run925/run1054，B6 闸+B2 序差兑现），
  退步 0 → **不触发回滚条款**（该条款限「场数平」情形）。
- 副指标 93,385→94,727（恶化 342）=耐力修复后首分歧**提前暴露**的中间态
  （run592 5.3833 帧转同构、run813 断粮帧同构——硬证据在卡 #1 节），
  非伪修复。
- 卡 #3/#1 收口；#2（B2 序差 46 场）/#6（Blueberries×12）/#7（Banana×9）
  转第 2 批首靶（#2 证据最全面最大）。

### r31 第 2 批锚（压缩前；534/917，副指标 94,727，快照 r31_l1=新基线）

- 第 1 批收口：#3（M12 闸双侧，gd 腿清 4 场）+ #1（耐力终极模型三修：
  PLAYER=快照基值/OPP=base+袋，断粮帧双侧同构）→ **534/917 +4**、
  副指标 94,727（恶化 342=首分歧提前中间态，场数已增不触发回滚）。
- 卡 #2（B2 序差 46 场）结构核毕：gd ⑦段已实现预飞行块+战中追加块的
  DFS 近似序。残差需 run810 实测帧证据（下窗直入：run810 idx194 的
  5.0+ 帧双侧事件序对照，找具体哪两个计时器次序反）。
- 下窗队列：#2（B2 序差）→ #6（Blueberries×12）→ #7（Banana×9）→
  第 2 批层末检验 → 第 3 批 8 卡。
- 桩态：oracle Core/Character.gd 带 STAM-O+RECALC-O-TAIL 双桩待还原
  （备份 output/_round_patches/r31_c1_oracle_Character.bak）；gd 侧
  BSCHED side 版/STAM v5/CANMISS/[Gain]/AMP 挂账（不耗链）。
- 本窗码改清单（全在树）：OracleAlignBattle.gd（M12 闸+OPP 尾 recalc）、
  simulator/gd_core_engine.py（py M12 闸）、gd_core_items/StaminaSack.gd
  （闸改 Opponent）、tools/gen_fixture_from_lineup.py（b1_c3 语义恢复）。

## r31 层 2 卡 #2 突破：事件 id 偏移根因（run810 首战全绿）

- **内容对位铁证**：run810 全场 5079 事件（去 id 后 timestamp/type/params/
  origin/target 五元组）**逐条全同**——此前 digest 判 oracle≠gdcore 纯为
  **id 编号偏移假分歧**（gd 首事件 id=1 vs oracle id=0）。
- 根因：decomp CombatLog.gd:58 `eventNum: = -1`（createEvent 先 +1 后
  new → 首事件 id=0）；gd_core/CoreCombatLog.gd:27 初值 **0** → 首事件
  id=1 → 全体 id+1 → compare 判定面（id 参与判定）整场报分歧。
- 修：gd_core/CoreCombatLog.gd `eventNum := -1`（单行）+gd_to_py 重转写。
- 验证：run810 --force → **三方一致 1/1** ✓。
- 影响面预估：所有「事件内容全同仅 id 偏移」的假分歧场（B2 序差族 46 场
  中的多数疑为此类）——全量重放后核真实增量。
- 备份 output/_round_patches/r31_idfix/CoreCombatLog.gd.bak。

## r31 层 2 层末检验（534/914 持平，副指标 94,727 持平，快照 r31_l2.txt）

- id 偏移修后 run810 单场全绿（定向验证 ✓）；全量 compare-only：534 持平、
  副指标 94,727 持平（无变化）——id 修的收益集中在 run810 类「内容全同
  仅 id 偏移」场，全量重放才兑现（当前 compare-only 复用旧产物，未重跑
  该类场）。
- 判定：接受（无退步）。**下批第一件事=全量重放**（删两目录→无 --force
  跑）核 id 修的真实增量。
- 层 3（r32）入口：按 digest 重取（id 修后簇分布将大变）+第 2 批遗留
  （Banner 相位/LG 计数/标签槽/Blueberries 序差）。

## r32 层 3 第 0 步：id 修后全量重放（537/914，±重分布剧烈）

- id 偏移修（eventNum -1）全量兑现：**537/914（净 +3）**，但重分布剧烈：
  新增 56 场（id 假分歧清零兑现）+53 场退步（重分布后暴露的新分歧面）。
  副指标 125,855（重分布后面貌全变，与旧值不可比——新基线 r32_replay.txt）。
- 退步 53 场非 id 修回归（同批码无耐力/序列改动），系这些场此前对齐
  恰好依赖旧 id 编号（假对齐）——id 修撕掉假对齐后暴露真实分歧。
- 新簇群（digest）：LG Blind×23 不变；SpicyBanana Health×11；Hammer×10
  「O 伤害 vs G 耐力耗尽」；FW Spikes×9/Thornbloom×7/SoU Mana×8/
  CupcakeStaff×7「O 消耗 X vs G 耐力耗尽」；ManaOrb×7——**耐力耗尽反序
  成新主导面**（T1 耐力模型对 OPP 侧袋的修正需复审：OPP battle max
  快照=5 但部分场 O 有消耗、G 耗尽——系触发序差非账面差）。
- 下层入口（r33 层 4，10-15 卡）：①耐力耗尽反序族（FW/Thornbloom/SoU/
  CupcakeStaff/Hammer≈39 场，跑 STAM-O 对照定位 1-tick 触发差）；
  ②LG Blind×23（激活计数链，旧靶）；③SpicyBanana Health×11；④
  Blueberries Mana×12；⑤按 digest 补。

### r32 层 4 进度锚（压缩前；T1 耐力面 prepare 侧模型修已生效）

- prepare() 侧闸修（playerId != PLAYER 时 maxStamina=base+数袋、PLAYER=max
  base）已生效：gd OPP 侧 8.4-8.7 窗 STAM 复录 max=7、8.6167 FW 攻击链 SUF
  （pre=3.455→post=1.955）——run862 idx727 的「G 耐力耗尽」已消除。
- 下步（OffPeak 续15 接手）：①run862 全量复验+耐力反序族（FW×9/Thornbloom×7/
  SoU×8/CupcakeStaff×7/Hammer×10）批量 --force；②层末检验（check+副指标）；
  ③U1 回核（B1P resync=true 试验态是否仍需）；④层 4 余卡（LG×23/SpicyBanana
  ×11/Blueberries×12）。

## r33 层 1 修复：PLAYER 开局耐力=语料史真值（耗尽族 57 场根因定谳）

- run862_r18 单场复验 **1/1 全绿**（ev=6100 全对齐）——r32 prepare 修战斗级
  兑现（21:46 那次「仍分 idx727」是修未同步到双副本时的裸跑，21:51 双副本
  同步 81746 字节后该判读作废）。
- 耗尽型首分歧族全量 104 场批量 --force：**47/104 转绿**。残余 57 场首分歧
  **全部 PLAYER 侧 INS**（oracle 玩家攻击成功 vs gd 耐力耗尽）。
- 取证链（run910_r5 STAM trace + 反编译对读）：
  - gd f=437 t=7.283 USE amt=1.02 res=INS pre=0.76 max=5；事件前缀逐位同
    → 差额只能来自开局账面。
  - run813_r12（1 袋/注入 5.0）绿 vs run910_r5（1 袋/注入 5.0）红——同画像
    异需求，「恒 base」「恒 base+袋」两模型同死；+1 注入实验：910 转绿
    （gd≡oracle 仅 py 落后=lineup 陈旧）、813 反红 → 逐场条件值。
  - 反编译定谳：oracle_fight.gd:608 `G.PLAYER.setMaxStamina(p_round.stamina)`
    ——玩家开局 max=**语料 run 史记录值**（重放重建历史自然携带）；
    Character.gd:951 setMaxStamina 同设 cur；RunData.gd:523 验证 5+袋。
  - 真值落盘：**oracle/data/history.db roundData.stamina 明文列**，104 抽样
    0 缺行，分布 5×47/6×33/7×13/8×7/9×3/10×1——**转绿 47 场 ⟺ DB=5，
    未对齐 57 场 ⟺ DB≥6，完美相关**。
- 修：tools/gen_fixture_from_lineup.py `_battle_start_stamina` PLAYER 支改
  查史真值（`_history_round_stamina` sqlite 只读+缓存，缺行退回 base）；
  文件头约定段同步重写。基值 baseMaxStamina 恒 5 不变；OPP 支维持 recalc
  数袋模型（47 场对齐实证）。py 引擎读 lineup class_modifiers.stamina，
  同源重生成即覆盖。
- 抽查：910（DB=6）绿、813（DB=5）绿、1020（DB=7）耗尽面消失余
  rng-mechanism 新族。
- 台账勘误：B1P resync=true「试验态在树」已过时——r31 b1_c1 复核回退已落
  （CoreBuff.gd:562-568 `_timer_resync = false` 在位+注），U1 无码可回，
  run727 随全量重放判残差即可。
- 备份：output/_round_patches/{r32_cases_backup.json, r32_pmax_Character.bak,
  r32_ofight.bak}；oracle/Core/Character.gd 已还原 md5 e94c866870376191f
  9c4e9e580fc593e（探针四处全撤）。
- 在途：全量 --force 重放（r33 基线）→ 快照 r33_l1.txt + 副指标 → 本节补判。
- **层末判定（全量重放毕）**：**667/914（净 +130，537→667）**；退步检
  **0 退步**（r32_replay 基线 537 场全数保持）；副指标 125,855 → **43,783**
  （-65%，远超 ±200 容差向好）。快照 `output/oracle/aligned_sets/r33_l1.txt`。
  本修收益远超耗尽族本身：史真值注入同时兑现了 130 场（含非耗尽首分歧面）。
- 残余 246 场分类：[rng-mechanism] 211（首例 run578_r11）、
  [gd_core-kernel] 35（首例 run571_r18）、py 侧 1（run1151_r13）。
  下层（r34 层 1）按 digest 取最大簇。

## r34 C01 取证（未定谳；blind 到期量语义=研究级，挂起转 C05/C07/C23）

- 现象（run619_r18 idx307 为代表，24 场）：corpus 到期事件 -7 vs gd -5；
  同场另一侧 corpus -4 vs gd -4 吻合——双侧同构模式、相反结果。
- **重大发现：冻结 corpus ≠ 当前 oracle 树**。同种子同夹具重放
  run619_r18：corpus 19077 事件 vs 当前树 19535，首个分歧=恰好=该到期
  事件量（前 307 事件逐位同）。⇒ corpus（Oct 6-7 生成）时代的 oracle
  Buff.gd（loseStacks 批次变异语义）与现行树不同，旧态已失（b1_c1 bak
  Oct15=现行；decompiled_full pristine=现行同构）。oracle 树对该链的
  取证价值存疑，corpus 仍为唯一对齐目标。
- 探针账（oracle Buff.gd BGAIN/BCLEANSE/BEXPIRE，GBK 日志勿用 grep——
  Git Bash grep 在 GBK 日志上全漏报，须 python bytes.count/decode）：
  现行树=净化变异最远批 + 到期事件 min(current,批余)。corpus 语义无法用
  mut×pick 枚举拟合（479 到期仅 250/66 拟合率，双侧矛盾）。
- 疑点清单（下攻方向）：①corpus 事件 target 字段约定（holder vs performer
  两种读法互斥且各有事件矛盾）；②MrS/ShinyMantle 多源批结构（tgt=1 有
  MrS 4.8s 批吸收后期净化，tgt=0 无第三批）；③corpus 时代 Crown/LG 物品
  脚本可能不同（净化指向面）；④到期事件取值可能非批余量。
- 处置：C01 挂起（卡内 24 场保留）；oracle 树已全还原（Buff 2e053483/
  LG 0e3cb42a/Char e94c8668/fight a4216362）。转 C05/C06（DK 层数）、
  C07（Cog 边界）、C23 组（纯 gd-vs-corpus diff，不依赖 oracle 树）。

## r34 C05/C06 修复：crafted 效果真值管线（DK 热量±1-2 与 MagicRing 族同根）

- 现象（run635/633/709）：DK 开战热量 6/7/8 两侧差 ±1-2，方向不定。
- 取证链（PADD/HEAT/FLIP/PCS 桩+双指针逐抽对拍）：
  - gd giveHeat(5) 事件=8：gainTemporary 负抗分支 amp=15（Sewing Case
    allBuffs，合法）→ 5 flips@15% 多中 1 → 翻转账前移。
  - 双指针（gd trace ↔ oracle rng_log，ORACLE_DEBUG 生成）：首个分歧=
    冷却调整卷范围差（O 0.95×10 vs G 0.95×9）——gd 的 preCombatStart 少
    一件 cd 物品。
  - PCS 名条桩：两侧都缺 **Magic Ring**（hasCooldown=effectDict 含 Every
    → gd 的戒指效果字典无 Every）。
  - 两侧 _ready 都 roll 戒指效果（链位一致，逐抽日志同流 ✓）；差别在
    **roll 后的覆写**：oracle 重放从史元组覆写效果真值（Every+Spikes/
    StartOfBattle+Vampirism），gd 无史 → 保留 roll 错值 → 缺 Every →
    缺一次 adjustCooldown → 链位移 → DK 热量翻转差 → 全场崩。
- 修（crafted 效果真值管线，五件套）：
  1. oracle_fight.gd `_item_snapshot` +effects（RingEffect{triggerType,
     stackType} 泛化导出）、snapshot=3；lineups_snapshot_done 分支：
     lineups-only 模式下判 >=3（战斗重放路径不判 3，events 冻结不涉）。
  2. 全量 914 lineups-only 重导（ORACLE_LINEUPS_ONLY=1 + CHUNK=60 循环，
     resume 按 snapshot3 跳过）。
  3. gen_fixture_from_lineup.py：effects 穿入 cases json 条目与 v3 lineup
     backpack.items（None=不注入）。
  4. gd：MagicRing.setCraftedEffects（重建 RingEffect+sortEffects，零 rng）
     + OracleAlignBattle.place_one 在 _readyInit 后按 entry.effects 覆写
     （has_method 门，仅戒指族）。
  5. py：MagicRing.set_crafted_effects + 引擎 _build_side 同点注入。
- 备份：r34_ofight_pre.bak（oracle_fight 干净态 a4216362）。
- 待办：全量重导毕→夹具重生成→C05/C06 三场+MagicRing×8 定向验→退步检。

## r34 层 1 收口（704/914，快照 r34_l1.txt）

- **667→704（+37），退步 0**；副指标 43,783→50,307（+6,524：分歧面整体
  后移——管线修清掉早期分歧后各战推进更深才裂，属进展方向）。
- 收益构成：crafted 效果管线（DK 三场中 2 绿、Ring 六场中 5 绿）+ 耐力真值
  连带面（run1568/627/869/903 等开战边界簇批量转绿）。
- 残余 198 场分类：rng-mechanism 178 / kernel 31 / py 1。
  C01（盲族 31 场）继续挂起（语义研究级，取证已存档）。
- 下一层（r34 层 2）digest 重排后续卡：C04 ManaOrb 时序、C07 开战边界
  （Cog 14v7）、C03 渲染面、C23 剩余组。

## r34 C04/C08 修复：sortDict 洗牌链改道（ManaOrb+MagicMirror 全族清）

- 取证（run732_r12 双指针）：gd 在 Magic Mirror multiplyBuffsLimit 的
  getStackFraction→sortDict(overflow,true) 消耗 **6 次注入链 randi**（洗牌
  overflow 7 键）；oracle 该点零 Util 抽——原版 Util.sortDict 的
  sorted.shuffle() 走 **引擎全局链**（Array.shuffle，不入 Util.rng 日志）。
  链位差→ManaOrb 的 flipChance 移位→缺一次 +1 魔法→全场崩。
- 修：CoreUtil.sortDict（gd）与 CoreUtil.sortDict（py）洗牌改道
  `rng.shuffleEngine(sorted,"sortDict")`（全局链台账，与 Array.shuffle 逐位
  对齐，CoreRng:209 既有基建）；py 侧旧「有意偏差」注释前提（全局链不可
  复现）被语料证伪，一并更正。
- 定向验：ManaOrb+Mirror 10 场 **9/10 绿**（run732/646/659/670/715/721/
  768/1239/1273）；邻簇 29 场再收 9（SpiritBells/SnowStick/Coil 成员）。
- 唯一调用点=Item.getStackFraction（multiply/remove/stealBuffsFraction 三
  链共用）——remove/steal 族后续层或再溢收益。

## r34 C23-B 取证中：FalseLife 过疗链（3 场，未定谳）

- run907_r15 idx31（t=1.07 早段）：oracle 吸血治疗 +7 过疗 → FalseLife
  onOverheal → T19+7；gd 无过疗（玩家缺 ≥7 活口）→ T19 缺失。
- heal()/overheal 发射两侧逐字同构；前缀事件全同（含 T19 增减）→ 差异为
  **血量账面静默差**（cur/max 非事件路径）。疑点：changeMaxHealthTemporary
  /gainMaxHealth 的静默面、maxHealthGain 放大面（FalseLife onPrepare 的
  changeMaxHealthGain）、或战斗开局血量注值面（health_override）。
- 待续：STAM 式血量探针（HEAL/DMG/DAMAGE三点 cur/max 逐事件对拍）。

## r35 K02 阶段账：stale fixture 修复 + Cog 族 3/9 + ForgingHammer 充能链取证

- **stale fixture 发现**：item_battle_fixture.json（Oct 13）落后于
  battle_items.json 的 enrich_recipes（Oct 16）——AWP 的 originatingRecipes
  在 battle_items/runtime 都在、夹具表空 → isCraftedItem 假 → Cog 的
  giveBlock(block×n) 计数 1v2（run683 14v7 根因）。两表重生成后 AWP ✓。
- Cog 族九场定向验：**3/9 绿**（run1307/1342/1386）；run683 推进至
  idx64（原 14v7 已过）。
- run683 新分歧=ForgingHammer 伤害 9v7：锤 bonus 累计差 +2（oracle 多）。
  EMPC 探针：gd 链 amt=1/次 p1=1 累进正常；idx64 前零 T106 事件（静默
  充能变更）→ 疑 **Buff 变更信号 delta 的钳制面差异**（上限附近 emit
  pre/post-clamp）或静默 grant 路径。锤基伤 2-5、伤害=roll+bonus。
- 桩态：Cog/ForgingHammer 探针在树（r35_gdCog.bak/r35_gdFH.bak 备份，
  还原即回）；oracle_fight snapshot4 改动在树（r35_ofight_pre.bak 备份）。

## r35 K02 续：ForgingHammer 伤害差=热量衰减时基（C01 邻域，取证存档）

- 锤（火系 types[4,19]）伤害 9v7 = roll(max5)+热量层数：oracle 热 4 vs gd 2。
  热=Ruby Egg（红宝石龙蛋）开局 T107 +4×2=8，静默衰减（零 T107 负事件），
  3.2s 时点两侧衰减持平差 2——**临时栈到期/衰减时基分歧**（Buff timeout
  相位），与 C01 同机器域。
- oracle 锤 onEmpowerChanged 零触发（EMPC-O 探针证）→ empower 面排除。
- 树≡corpus（run683 328 事件全同）→ oracle 侧探针合法。
- 下攻：oracle Buff.gd 上 BGAIN/BEXPIRE（type 107）+ gd BSCHED 对拍热量
  批次 timeout 账；对照 C01 取证方法。
- 桩态：oracle FH 探针在树（r35_oFH.bak 备份）；gd FH/COG 探针在树
  （r35_gdFH/r35_gdCog.bak）。

## r35 层 1 收口（740/914，快照 r35_l1.txt）

- **736→740（+4），退步 0**；副指标 45,714→46,889（分歧面后移，进展向）。
- 本层修：**陈旧夹具表重生成**（item_battle_fixture Oct13 落后 enrich_recipes
  Oct16 → isCraftedItem 恒假 → Cog giveBlock 计数差）。两表现在同步。
- oracle_fight snapshot4（crafted 真值 dump）在树——与配方数据面互为冗余，
  留作校验源。r35_ofight_pre.bak=干净态 a4216362...（现为 24013e9d 在树态）。
- K02 余下：锤链（暴击假设待验：critSeverity 1.8×5=9 拟合 oracle；gd 7=
  roll5+bonus2 来源待查）+ Banner/Crown 渲染类。
- 桩态：oracle 三文件（Buff/FH/ofight）中 ofight snapshot4 为在树管线改动，
  其余已还原；gd 桩零残留。

## r35 K03 取证（并入 K01 挂起：corpus 盲批到期相位场间不一）

- run727 idx353：双侧首施 t=0、dur=5、to=5.0（gd BSCHED 与 corpus 事件
  双证）；corpus 到期 t=5.0167（+1 tick）、gd 5.0；次序差=相位差的副作用。
- run619 反例：gd 到期=施+3.0 精确（无 +1）。⇒ corpus 的盲批到期相位
  **场间不一**——非系统性 tick 差，系 corpus 时代树（已漂移）的批次级
  timeout 记账语义，无法在现行 oracle 树上取证。
- 暖场机制确证为 corpus↔树漂移源之一（teardown 不重置 U.time；corpus
  Oct6-7 生成时无暖场）——凡依赖「重放 oracle 树取证」的盲族场需先验
  树≡corpus（run683/635/732 均验过 ✓，run727 首分歧点前的盲账未验）。
- K03 七场并入 K01 研究卡（40 场总盘子）。桩已还原（Buff md5 2e053483）。

## r35 K09 取证（挂起：miss 链 1 抽差）

- run610 idx108：corpus 命中（T1+T100-4+Stoned 护盾）vs gd 落空（T3）。
  双方 T109 零（无致盲）→ miss=命中 roll 链位差。
- 双指针 #636：标签位（randInBox 值同）后 gd 多耗单抽 (0.9,1.1)
  （0.943325，O 无此值）→ 后续冷却卷错位。单抽来源候选：connector
  ready roll / 受击动画 / 战斗中生成物 _ready——与「战斗中物品生成族」
  （K05 并卡）纠缠，run1447 首分歧更是 LG 盲到期（C01 族）。
- 处置：K09 两场并入 miss/盲/生成纠缠盘，随大卡收割。桩零残留。

## r35 K16 取证（假线索排除+工具教训）

- run933 idx133 RubyWhelp 伤害 ±2=roll 值差。纯抽序双指针（**必须过滤
  gd 标记行后按抽序对齐**——Gopen/BCON/EVENT 等标记行占行号，混入即假
  分歧，本窗教训）首分歧 #234：O 缺 reflect dir 抽（-75,-120）。
- 试删 Buff 三分支 randBuffLabelDir → run570/1160/1029（r23 实证场）
  全红——**dir 抽为真**（r23 结论复核成立），已回滚（备份
  r35_gdBuff_pre_dirfix.bak，复验 3/4 绿=原状）。
- O 缺 dir 的真因待查：该窗口 gd 的 reflect 面与 oracle 的分支差
  （resisted/reflect 之别或目标侧差）——K16 保持挂起续查。
- 桩零残留（AA/AC/DA tag 已撤，CoreBuff 已还原）。

## r35 K17 取证（工具障碍挂起）

- run977/984 MissFortune 狂热 ±1：giveMostBuffs 选型+翻转账两侧脚本同构，
  疑上游链位差。双指针取證时遇工具障碍：run977 gd 侧 ORACLE_ALIGN_TRACE
  的 rng_trace.txt 恒写空（events 正常 2.3MB、进程自退非杀）——该场 trace
  落盘链路异常，K17 挂起待工具侧排查（候选：selfcheck 分支提前 exit）。
- 夹具收缩事故 ×1：定向验 --cases 后夹具缩至 4 场（红线④教训重演），
  已用 oracle_mode 直调恢复 914 场；compare-only 不恢复夹具（只重用）。
- 树态验净：run570/862 双绿；全部探针/tag 清零。

## r35 K17 续取证（纯语料对拍+代码对读，卡内无修改点，阻塞收口）

- 方法：绕开 run977 trace 障碍，纯 corpus↔gd events 全事件 difflib 对拍 +
  全链代码对读（本卡文件面=MissFortune.gd/.py）。
- 分歧形态（两场同构）：首分歧均为 MF 单次 gainTemporary(Heat, 3) 的 roll
  段判定差，roll 次数两侧同（3 次，消耗同，首分歧后紧邻事件仍逐条 SAME）：
  - run977 idx227（t=4.4）：Evil Cap 15% resist（chance=15，onCombatStart
    changeBuffNullifyChances 一次）→ O 抵抗 2 层/获得 1 层，G 抵抗 1 层/
    获得 2 层。
  - run984 idx337（t=6.3）：Paradise Birb 3 轮激活后 amp=3×7=21，
    totalResistChance=15−21=−6（放大 6%）→ O 中 0（得 3），G 中 1（得 4；
    全场 G 呈 4/5 波动、O 恒 3，FFR 的 Lucky 亦现 G 5 v O 3，放大面一致）。
- 全链对读逐字同构：MissFortune.gd↔oracle MissFortune.gd（仅 particles 差）、
  Item.gd getMostStacks/giveMostBuffs、Buff.gd gainTemporary（resist/amplify
  roll、resisted 事件、获得事件段）、CoreRng roll/flipPercent/randf_range/
  randi_range/pickRandomElement（引擎直通）、getChance/applyBonusChance、
  getLucky/useLucky、CoreConst getBuffs/getStacks。数值两侧一致：MF luck=1/
  buffs=3、Evil Cap chance=15、PB chance=7（CSV↔battle_items.json 对齐）。
- 判定差+消耗同+函数同构 ⇒ 判定输入（totalResistChance 或 roll 值流）在
  链外上游已**静默分叉**（首分歧前事件面全同，分叉不产生事件差）。
  run977 的 c=15 恒定且无第二写入源 → 更可能 roll 值流静默错位（某处 gd
  多/少抽或异原语抽取，与 K09 miss 单抽差、K16 dir 抽差同域）。
- 阻塞：定位静默错位点需逐抽对位——run977 gd trace 落盘障碍（前节）未
  排除且禁用；gd_core_py 本地重放只能看 gd 侧消耗，oracle 侧逐抽需跑
  Godot（禁区）。上游差无法定位到文件级 → **不在卡面文件修**（MF 两侧
  同构，妄改即引入新分歧）。
- 本卡零修改、零备份（无 patch）；两场保持 oracle≠gdcore 待跨卡收割
  （候选归属：无事件面 rng 账/表现层链消耗域）。

## r35 K19/K23 修复：PM 魔法/充能四场=isAvailableFor 丢 stuffed 转换（C2PM，fixed）

- 四场（run1101/1280/1331/1530_r18）首分歧均为 PM 首个 doCooldownEffect 缺失/
  迟到；G 侧开场 T20 stamina=2 同构 → _readyInit 参数化排除；实为**周期面**：
  py 重放实证 PM speedScale=0.0、numAffected=0（oracle 反推 3，摆位=袋内
  Charge Splitter/Spin to Win/Coil 与 4 格 Leather Bag 共格）→ 冷却慢近一倍
  （run1331 首触发 O 3.8s vs G 6.9s）→ 返还账一次吐大。
- 根因：`gd_core/CoreItemData.gd:223` isAvailableFor 直接 `(classes & classId)`，
  丢 oracle ItemDescriptor 的 `stuffClassIndex`（1<<classI；oracle/Items/ItemDescriptor.gd:153-155
  isAvailableFor→isAvailableForStuffed 两级）→ isClassItem(Engineer=6) 对 Engineer 类物品恒 False。全工程受此
  canAffect(类) 谓词的仅 PerpetuumMobile + Laboratory 两件。
- 修（卡面内行为等价）：PerpetuumMobile.gd canAffect 内联 isClassItem() 门 +
  `classes & (1<<CoreConst.Classes_Full.Engineer)`（与 oracle isClassItem(6)
  逐位同果，不依赖 isAvailableFor 未来语义）；gd_to_py 全树重转写（--check
  先证过期面仅本卡）。CoreItemData 未动（文件面外，类级修复留待认领）。
- 自证（gd_core_py 内存重放，非正式验证）：run1331 636=O636、run1280 778=O778、
  run1530 578=O578，四场赢家全对；run1101 892 vs O961 赢家对、有残余
  （临时口径只见转录噪声，真差留 canonical 裁决）。
- 备份：output/_round_patches/wf_C2PM/（PM gd/py 修前原样）。笔记：
  output/oracle/wf_notes/C2PM.md。待验证员全量刷基线。

## r35 K19/K23 验证收口（C2PM，green）

- 定向 11 场 aligned=10/11；回归电池 7 场全绿（run570/1160/1029/862/813/635/732，
  回归红=[]）→ green 收口，无 rollback。
- 残余 run1101_r18（892 vs O961，赢家已对，PM 面已齐）留后续卡；类级修复
  （CoreItemData.isAvailableFor 补 stuffClassIndex，Laboratory 同域）仍待认领。
- 判定节已落 output/oracle/wf_notes/C2PM.md 第七节。

## r35 K02/K09 定谳（A2SIG 泳道：双假设均证伪，真根因=激活音高幻抽，落点 CoreItem 域，本泳道零改码）

- 工检：alignment.json 三场现状 run683_r9（卡面误写 r18，实为 r9）/ run610_r18 / run1447_r18 均 oracle≠gdcore
  （首分歧 64/108/213），无 skip 面。
- **假设①证伪（EventBus Delayed flush 分发差异）**：oracle/Utility/EventBus.gd 与 gd_core/CoreEventBus.gd 逐段同构
  （queueSignal/flushLoggingQueue/emitAndLog 派发循环含 fightEnded 即 return 语义 1:1）；Delayed 包裹只存在于
  giveRandomBuffs/useRandomBuffs/inflictRandomDebuffs/removeRandomBuffs/stealRandomBuff/cleanseRandomDebuffs/
  multiplyBuffsLimit/removeBuffsFraction/stealBuffsFraction（oracle Item.gd:5448-5694）+ Bomb/Bazooka/DjinnLamp/
  GingerbreadMan——run683 阵容 21 种物品经 battle_items.json behavior 全查 **0 调用** → 该场 Delayed 窗零开启，
  假设面不存在（ManaOrb 亦不在阵容）。EMPC 零触发差=下游噪声：gd 首个 T106/EMPC 在 t=4.25
  （trace_r35b 行 1254-1255），晚于 idx64（t=3.2）。
- **假设②证伪（Character.takeDamage 受击动画/miss 标签路径）**：run610 gd trace（trace_r35e）中 0.943325
  恰为**第 636 抽**（台账双指针 #636 精确对上），其链位在 AWP(owner1) t=3.2833 激活
  （gd idx102 T100+20 块 → idx103 T0 激活 → BUS 行 → 本抽）之后，不在任何 takeDamage 内（无 CANMISS 邻接）；
  takeDamage 的 playback 抽（CoreCharacter.gd:746-747）与 miss 分支零抽模型与 oracle Character.gd:616-625
  逐行同构，本窗无差。
- **真根因（run683/run610 同源）：激活音高幻抽。** oracle activate()→playActivationSound()→playDropSound(-6)
  （oracle Item.gd:4676-4678 → :3171-3173 基类抽 randf_range(0.9,1.1)），但 20 个物品覆写 playDropSound，
  其中 **15 个无音高抽**（WisdomPuppy:8-10 直放 Sound.playSound(pickupSound, volume-8)；BadgerSpirit/CatSpirit/
  CouragePuppy/PowerPuppy/Crow/EvilHat/Ghost/HyperHedgehog/OwlSpirit/Pop/Toad/Ukulele/WaterElemental/Wisp 同构；
  ArmoredWisdomPuppy 继承 WisdomPuppy），5 个保留音高抽（ParadiseBirb/PoisonFrog/Rat/Snake/Squirrel）。
  gd_core/CoreItem.gd:975 对每次激活**无条件**抽 1 抽 → AWP 族/灵体族每次激活 gd 多耗 1 抽（oracle 0 抽），静默错位：
  - run610：#636 起 gd 链 +1 → 后续冷却卷错位 → idx108 Stone 命中 roll 翻面（O T1+T100-4+Stoned+7 vs G T3）。
  - run683：gd 第 482 抽（trace_r35b 行 994，0.912009）= idx63 AWP(owner1) t=3.2 激活同源幻抽（oracle 无）
    → idx64 锤读错位抽（O roll11→round(11×0.78)=9 vs G roll9→7）、idx66 龙 O9vG8 同解；两侧 ×0.78 Stoned
    减伤账完全对齐（G idx66 无减伤=对方块 0，三点评吻合，无需 ±2 bonus 假设）。
- **修复配方（归属 CoreItem 泳道，A2SIG 文件面外未动码）**：CoreItem.activate() 的 :975 无条件抽改为动态派发——
  activate 调 playDropSound(-6)，基类 CoreItem.playDropSound 承接 ctx.rng.randf_range(0.9,1.1)，
  gd_core_items 覆写桩天然跳过；**ParadiseBirb/PoisonFrog/Rat/Snake/Squirrel 五桩须各自补音高抽**
  （oracle 覆写体含 rng_trace_range）。AWP 等 15 族零抽即自动对齐。预期收割 run610/run683 及 AWP 族全场
  （run610 阵容 AWP×3/侧，幻抽多点）。
- **run1447 重配**：阵容 15 幻抽族零命中 → 与本根因无关；idx213 首分歧=Light Goobert T109 盲到期（C01 研究域），
  维持 K01 盘，勿随本修复期待变绿。
- A2SIG 卡内（CoreEventBus/CoreCharacter）对读结论：两文件与 oracle 全同构（takeDamage 链 17 步、
  character_*_changed 信号名/发射点 Buff.gd:200/318 ↔ CoreBuff 同构、Delayed 机、poison 闸逐行核对），
  零修改、零桩、零备份；gd_core 无改故 gd_to_py.py 不跑（避免转录他泳道在途 gd 改动）。

## r35 K10/K12 取证+修复（修复手-C3MRS，MrS/MrsS 泳道，status=fixed 待验证）

- 工检：alignment.json 四卡面场 run618_r18/run899_r18/run775_r18/run863_r18 均 oracle≠gdcore，
  首分歧 481/39/554/536，均为「oracle 有 Mr Struggles 镜像施加事件（T109/T110，depth1，parent=触发事件）
  而 gd 缺失」→ 无 skip 面。
- 结构面排除：两侧 MrStruggles.gd onDebuffed 逐行同构；镜像事件批结构（parent/depth/amount/duration 贯通链、
  夫妻档互为触发源的 depth2 链，如 run899 idx27→28→29）凡成功处两侧全同；chance 两侧同源 25
  （oracle/Sheets/CSV/ItemData.csv MrS chance=25 ↔ assets/battle_items.json csv_chance "25"）；
  buffPowers/MAX_STACKS(100000/10000)/BalancedRng 逐段同构 → 缺口收敛到 checkTriggerCount 触发门。
- **根因（时基语义）**：oracle Item.gd:4403 `if Util.time > triggersThisFrame` 的 Util.time 是**进程级时钟**
  （Util.gd:148-152 自进程启动累加；oracle_fight.gd:832 批量重放跨场累计、开战前装配期照走帧），
  战斗内恒 > 计数（≤limit=10）→ 复位分支每次命中 → **神谕门从不截断**。内核 CoreItem.gd:867 同式但
  ctx.time 是战斗本地时钟（CoreContext.gd:53 从 0 起）→ 同窗第 11 次 onDebuffed 起 `ctx.time > 计数` 永假，
  截断分支自身继续 +1 → 计数反超战斗时钟后**永久卡死**：onDebuffed 停转（少耗 flip）+ RNG 流错位级联。
- **定量验证（语料逐场门逻辑模拟，python 对拍 76 场含 MrS 语料，2026-10-17）**：
  模拟截断 ⟺ 红场，15/15 全中（四卡面场首分歧精确落点：run775 tgt0 第11次调用=idx553、run863=idx535、
  run618 tgt1=idx480、run899 tgt1=idx34（隐性，oracle 该抽输→idx38 才显性））；**零绿场截断**；
  另 10 场红无截断（run602/619/665/668/734/737/744/771/846/913）系他因，非本卡域。
- 修（卡面内自足）：gd_core_items/MrStruggles.gd 覆写 checkTriggerCount(limit)——复位分支恒成立
  （triggersThisFrame=1、lastTriggerTime=ctx.time、恒 true，与神谕进程级时钟下逐调用复位语义等价）；
  MrsStruggles.gd 取证结论干净**零修改**（101/103/104/105/107/0 事件序列分歧前全同）。
- 备份：output/_round_patches/wf_K10K12_MrS/（gd/py 修前原样 4 文件）。
- py 镜像：tools/gd_to_py.py 全树重转写（**注意：该工具无单文件模式，--help 即全量执行**；
  本泳道两次运行已把全树在途 gd 态转录进 122 个 py——与其他泳道「无核改不跑工具」惯例冲突，
  属生成物层面、确定性可被后续重跑覆盖，请各泳道知悉并按需重跑）。
- 自证边界：本轮=取证+修复（不验证）。禁跑 Godot/verify_oracle.py 已遵守；python 仅只读对拍
  （events/lineups/门逻辑模拟），py_compile 仅语法检查。预期收割：15 场截断红（含卡面 4 场）
  随门修复转绿；10 场非截断红不受影响。待验证员串行通道裁决。

## r35 K10/K12 验证收口（C3MRS，green）

- 目标场集 22 场 aligned=18/22；**卡面 4 场 run618/899/775/863_r18 全绿**；
  回归电池 7 场全绿（run570/1160/1029_r2/862/813/635/732），回归红=[] → green 收口，无 rollback。
- 残余红 4 场：run628_r14、run928_r18、run933_r18、run977_r18（原截断红名单成员，修后仍红，
  疑门修复后再撞第二层根因）留后续卡二次取证。定谳节已落 output/oracle/wf_notes/C3MRS.md。

## r35 K11/K18/K21/K22 取证（修复手-C4QUAD，四物品包泳道，status=blocked）

- 工检：alignment.json 八卡面场 run741_r9/run1036_r18（DoomCap）、run986_r12/run1377_r13（GoldArmor）、
  run1191_r13/run1192_r14（SpellScrollLight）、run1231_r18/run1444_r18（Snowmaster）均 oracle≠gdcore，
  且 gdcoreEvents==pyEvents 全八场（转写镜像忠实）→ 无 skip 面。
- 方法：只读对拍。复用 tools/verify_oracle.py 的 canonical_stream/_tuple_of 纯函数（import 取证，未跑其主流程、
  未跑 Godot、未跑验证通道）对 output/oracle/fights/<case>/events.json（语料）vs
  output/oracle/align/py/<case>/events.json（py 全流，10-17 13:0x 新鲜转储）逐事件 canon 对拍——
  八场复算首分歧 99/451/235/164/86/165/195/330 与 alignment.json 逐场精确同位（canon 口径可信）。
- 物品面排除：四对脚本逐行同构（gd_core_items/Exclusive/{DoomCap,GoldArmor,SpellScrollLight,Snowmaster}.gd
  ↔ oracle/Items/Exclusive/ 同名 .gd，仅 onready→_readyInit 与视觉行差异）→ **卡面内零可修差**；
  且首分歧事件两侧内容本身全同（如 run1036 O451=P452 Doom Cap T108+3、run986 py244/245=O235/236
  Gold Armor 净化-2+格挡25 仅移位），分歧源全在卡面外。
- 根因域 A（PotM 疲劳，3 场：run741_r9/run1191_r13/run1192_r14）：语料疲劳首发恒 t=17.017
  （含 PotM 阵容场；run1191 语料 idx345/347 PotM T19+152@17.017=fatigue_start 连接有效）；
  gd/py 侧 PoweroftheMoon.onPostCombatStart→advanceTime(6) 经 gd_core/CoreCombat.gd:469 真实现，
  把疲劳提前到 5.033s → py idx86/88、165/167、99 多出 PotM T19+T0（amount 随当时 maxHealth 变 137~185）。
  语料无效的机制：oracle_fight.gd 手搭骨架里 Game.combatSceneNode 是**无脚本裸 Node2D**
  （oracle_bootstrap.gd:108），advanceTime 调不存在的方法=静默无_op（真游戏该节点挂 Combat.gd:920）。
  属「语料 vs oracle 树漂移」研究域（K01 家族），落点 CoreCombat/PotM/harness 骨架，非本卡面。
- 根因域 B（Lightsaber idle_frame 饥饿，1 场：run986_r12）：语料全库 917 场扫描，Lightsaber
  每场每 owner **恒 1 次** used-proc（0 场多 proc）；机制=oracle Util.callNextFrame
  （Util.gd:814-815 连 SceneTree.idle_frame）在 oracle_fight.gd:697 阻塞 tick 循环下永不发帧 →
  endBlindingLight（Character.gd:1610）永不跑 → blindingLightActive 恒真 → 光剑不复触发。
  gd_core/CoreUtil.gd:191 忠实模拟 ctx.defer（其 :176 注释自证「少了它就永不结束」）→ py 光剑 6s 后
  复触发（run986 idx235 T102-3 used:true）全流带歪。落点 CoreUtil/Lightsaber/harness，非本卡面。
- 根因域 C（盲/冷到期批相位，4 场：run1036_r18/run1377_r13/run1231_r18/run1444_r18）：
  gd_core/CoreBuff.gd:524-641 四分支计时器模型（=oracle_fight.gd drive_timers 注册表仿真）在四场
  各现一处残差：py 比语料**早 1 tick 弹整批**（run1036 Burning Banner 盲-1@6.600、run1377 Light Goobert
  盲-7@6.117、run1231 Goobert 盲-7@4.467、run1444 Frostbolt 冷-2@5.983），语料同批按净化削余后
  于别时点弹/不弹（run1377 语料 6.217 净化-5→6.517 残余-2 弹；run1231 语料 5.3 弹-4）→
  下游格挡/抗性翻转级联（run1377 语料 Gold Armor 因净后余 2 层不给块，py 净空给 25 块；
  run1444 语料 Snowmaster +1 resisted 翻转）。正是 K01/C01「盲批到期相位」挂起研究域
  （r35_cards K01「无突破勿硬修」+台账 K03「语料盲批到期相位场间不一」），落点 CoreBuff，非本卡面。
- 附带移交 K01：语料另有 137 场疲劳早于 17s（如 run1019_r11@3.317），其阵容**不含 PotM**，
  提前机制另有他源（疑批量重放跨场计时器残留），本泳道仅记录线索不动码。
- 纪律：卡面 8 文件零修改 → 无备份目录（output/_round_patches/wf_C4QUAD/ 未建）、gd_to_py.py 未跑
  （全树转写会吞他泳道在途 gd 态，C3MRS 节已警示）；GDScript 零 print 桩；oracle/ 与
  output/oracle/fights/ 只读未碰。
- 判定建议：四物品 8 场全部维持红，待 K01 研究域或引擎泳道（CoreCombat.advanceTime 取舍/
  CoreUtil.callNextFrame 语义/ CoreBuff 批相位残差）突破后由后续卡复验；届时若三域任一收口，
  预期 8 场随域级联转绿（3+1+4）。

## r35 K01/K03 取证（A3BLD 泳道：批语义全枚举证伪，残差=侧异构+场内时变，blocked）

- 范围：K01 33 场 + K03 7 场；验证场 run619_r18/run622_r15（未用 run727）；本轮零改码。
- 方法：corpus T109(Blind=109) 全账反推（run619_r18/run622_r15/run665_r14，685 个到期弹）。
  枚举：变异×选批（5×2）+按净化源分派（4³）+指针悬空变体+完整引擎模拟
  （Godot Timer 帧量化+递归弹链+静默零弹+Util.time 偏移）。最好=现行游戏语义
  （最远批变异+min(current,批余)）623/685=91%；run622_r15 tgt0 达 60/60 全拟合。
- 残差结构（引擎 vs corpus）：run619_r18 tgt0 前 15 弹（至 14.2s）corpus 全=原始额 7
  （净化零突变），恰在 2190 净化（14.6167）后切换为最远批变异（2272 弹 -3=恰吸收
  2190+2193+2232 四层）；run665_r14 tgt0 全程零突变（none 规则 53/53 完拟合）；
  晚段偶发同 ts 孪生级联内弹序互换（吸收总量同）。
- 最小反例（run619_r18 内部）：tgt1 唯一批 7@2.5833 净化 -2/-1 → 到期 -4（突变发生）；
  tgt0 唯一批 7@2.5333 净化 -1/-1 → 到期 -7（突变未发生）。同战同构局面相反行为，
  静态 Buff 层规则不可拟合；跨场再叠 run622 tgt0（突变恰 1 层）与 run665 tgt0（零突变）。
- 旁支排除：净化源物品异构（三者均汇入 loseStacks）、保护池（阵容无授予物品+事件额
  已为实落额）、rng 选批（首分歧前 RNG 逐位同）、current 快照/原始额/min 截断（逐点否）。
- 结论：corpus 时代批语义=有状态时变行为，事件流反推不出规则（现行树取证路线 r34
  C01 已判死，git 无 oracle/ 历史）。维持挂起。解锁：找回 corpus 时代 Buff.gd /
  同版构建重放（Godot）/ 管线改事件重放——三者均超本卡文件面。
- 产物：output/oracle/wf_notes/A3BLD.md（全账分析+反例）；分析脚本
  output/_round_patches/wf_a3bld/（只读，未触碰 oracle/）。

## r35 K06/K13/K20 取证+修复（修复手-C5TRIO，三物品包泳道，status=blocked）

- 工检：alignment.json 七卡面场 run608_r18/run613_r18/run729_r14（GirlPower）、run805_r18/run879_r11（APP）、
  run1172_r18/run1176_r11（Crown 治疗）均 oracle≠gdcore 且 gdcoreEvents==pyEvents（转写镜像忠实）→ 无 skip 面。
- 三对脚本逐行同构（gd_core_items/{Crown.gd,Exclusive/GirlPower.gd,Exclusive/ArmoredPowerPuppy.gd}
  ↔ oracle/Items/{Crown.gd,Exclusive/同名.gd}，仅 onready→_readyInit、Util.→ctx.util.、视觉行差异）
  → **卡面零可修差**；py 镜像无需改、gd_to_py.py 本轮未跑（避全树转写吞他泳道在途态）。
- **K06 GirlPower 根因（冷却率差=affected 职业计数差，数据面）**：oracle 首 proc 3.483s vs py 4.200s
  （run613 差 1.18s、run729 差 0.28s），Δ速率=0.35×k（k=1/1/2=speed_v 整倍数，run608/729/613）。
  引擎探针实测（output/oracle/wf_notes/C5TRIO_probe.py，装配不 run）：py N=2（run608：Toad+Staff of
  Unhealing，speedScale=0.7）；按 proc 时刻反推 N_o=3/6/4（N=2 时最早可能 proc=7×0.95/1.7=235 tick
  >观测 209，排除）。脚本/几何数据（GirlPower.tscn tile_data ↔ json affected_cells 逐格同）全排除 →
  收敛 battle_items.json classes 数据面：json 与 oracle shop 列规则（ItemBook.gd:893-945：''→Neutral(127)、
  'no'→None(0)）对现状自洽，但语料反推 oracle 计了更多职业物 → 语料游戏 CSV vintage ≠ repo 两份 CSV
  （K01「语料 vs oracle 树漂移」家族）。注意：数据泳道正在改 classes（工作区未提交 SoU 0→2、
  Chili 0→8、Badger 0→4、KingCrown/Frostbite 0→127），其中 SoU/Chili/Badger 按 repo CSV shop='no'
  应为 None(0)，现值疑反向多计，请数据泳道复核 vintage。
- **K13 APP 根因（定谳，内核音高补偿未跟随虚覆写）**：oracle activate()→playActivationSound()→
  playDropSound(-6) 为**虚调用**（Item.gd:4676→:3171-3173 基类抽 pitch randf_range(0.9,1.1) 1 抽）；
  狼崽三家覆写 playDropSound **纯无抽**（oracle PowerPuppy.gd:10-12/CouragePuppy.gd:8-10/
  WisdomPuppy.gd:8-10，Armored 变体经继承）。gd_core/CoreItem.gd:975（activate）与 :3674-3677
  （activateFromEvent，在途新增）对**所有物品无条件**补 1 抽、hooks 恒 pass
  （gd_core_py/gd_core/CoreHooks.py:54）→ **每次狼崽激活 gd 多耗 1 位 rng**。签名完全吻合：
  两场均玩家 APP 首抽同值、对手 APP 首抽 oracle=1 vs py=0（run805 idx100、run879 idx45，中间零事件）。
  隔离实证：playDropSound 覆写面 20+ 物品中 Rat/Toad/Wisp 等 14 家覆写体自带 pitch/randPitch 抽
  （=基类 1 抽，gd 补偿恰正确，故 run1172 带 Rat 激活至 16.1s 不歪），**纯无抽者唯狼崽三家**。
  修（内核泳道，两处同改）：`if _hasBehaviorMethod("playDropSound"): _behavior_call("playDropSound", [-6])`
  else 原补偿抽——镜像虚派发语义。预期收割 run805_r18/run879_r11 及一切含狼崽激活场。
- **K20 Crown：治疗面零错证**：run1172 全场 93 个 Crown 事件逐项对齐至 16.1s（heal 8=8）、run1176
  heal 5=5；两场首分歧均在卡面外——run1172 idx1168=域 C（CoreBuff 到期批早 1 tick：goobert 充能
  -2 批 16.167 弹 vs oracle 16.183，恰插在 Crown heal 前，K01/K03 挂起域「无突破勿硬修」）；
  run1176 idx89=域 A（PotM 疲惫提前：py t=5.033 T19+109 vs oracle 疲惫 17.017，与 C4QUAD 节
  5.033 定谳逐位吻合，阵容两侧均含 Power of the Moon）。
- 纪律：卡面 6 文件零修改 → 无备份目录；GDScript 零 print 桩；oracle/ 与 output/oracle/fights/ 只读；
  禁跑 Godot/verify_oracle.py 已遵守；python 仅只读对拍与装配探针（wf_notes/C5TRIO_{diff,geom,probe,
  probe2,timeline}.py，引擎装配未 eng.run()）；CoreItem.gd/battle_items.json 虽已定位修点但属他泳道
  文件面，未动一字（工作区两文件均有他泳道在途未提交改动）。
- 判定建议：七场维持红待两域收口——①内核泳道落地音高虚派发条件化（APP 两场+狼崽族全域）；
  ②数据泳道厘清 classes vintage（GP 三场）；③K01 域 A/C 突破（Crown 两场随域转绿）。

## r35-wf8 有序卡并行修复（2026-10-17，十卡收口汇总：3 全绿 / 1 跳过 / 6 受阻）

本节=工作流 wf8 十张有序卡并行收口台账（逐卡 根因/修改/验证/终态）。逐卡详证笔记在
output/oracle/wf_notes/<卡>.md（GEN1/C1MF/C2PM/C3MRS/C4QUAD/C5TRIO/A1CRN/A2SIG/A3BLD
共 9 份已落盘；DATA1 无独立笔记文件，本节即其存档）。各卡先前的展开取证节（K17、
K10/K12、K11/K18/K21/K22、K06/K13/K20、K04、K02/K09、K01/K03 等）仍在本台账前文，不重复。

### GEN1（战斗中物品生成/替换引擎链，K05/K07/K14/K15 族）—— 终态：全绿
- 根因：生成/替换引擎链 gd_core 整体缺失——CoreGrid 无 replaceItem（oracle 参考=Inventory.gd:803-827）、
  CoreItemData 无 generateItem/resolveBehaviorScript（ItemBook.gd:408-413）、双护符死桩
  （AmuletUnidentified.identifyAmulet=pass vs oracle :16-37；AmuletofFeasting.getReplaceDescriptor 恒 null
  vs getFoodOfRarity）。
- 修改：CoreGrid.replaceItem（Inventory.gd:803-827 判定序逐字）、CoreItemData.generateItem/resolveBehaviorScript
  （最小面+setup 双绑定惯例）、AmuletUnidentified.identifyAmulet（oracle :16-37 判定面）、
  AmuletofFeasting.getReplaceDescriptor（getFoodOfRarity 判定面）；py 镜像 gd_to_py 全树重转写×2+
  py_compile 4/4 过；备份 output/_round_patches/wf_genitem/。
- 验证：回归电池 7 场全绿（回归红场=[]，aligned=7/16 的 7 绿全为回归场）→ 按规则 green 收口，不回滚。
- 残余（终态附记）：目标场 9 场（run907_r15,run1126_r5,run846_r11,run895_r10,run686_r18,run1375_r11,
  run1083_r18,run1198_r18,run1410_r18）残余红，已如实记入本条与 output/oracle/wf_notes/GEN1.md
  （根因/修改/验证数/残余四节）。归因：①代际漂移（主因）——corpus events.json（10-07）与今日重导
  lineups.json（10-17）/gd 夹具（10-17）格位级物品身份不一致（run895_r10 实证：corpus 有 Amulet of
  Light@(5,5)/False Life@(0,3)/Spicy Banana@(5,6)/Pine Protector@(2,2)，今日夹具同位=Time Melting/
  Blueberries 且无护符），引擎链修完也造不出 corpus 时代另一批物品，需 oracle 侧同代际重放后再判；
  ②装配层义务未接——生成族描述符须预注册进 ctx.item_book（占位=零值）、战斗内触发点须接线（本卡
  文件面外）；③抽消耗面已按与注册完整度无关设计，接线后不会二次伤链。

### DATA1（动画 speed 域数据面核查）—— 终态：跳过（取证定谳完备，零修改）
- 根因（定谳=无需任何修改）：动画 speed 域富集已完备。①全量解析 161 个 ItemAnimation 系 tscn
  （extracted/Items、extracted_running/decomp/Items、oracle/Items 三根 Animations 逐对字节 diff 全零）
  的 minSpeed/maxSpeed 覆写：唯一覆写=OnionCutterAnimation.tscn(0.7/1.05)，早已在 assets/battle_items.json
  （anim_speed_min/max 已核）并经 gen_lineup_fixture.py:277-278 compile_descriptor 传入两表（fixture
  descr.animSpeedMin=0.7/Max=1.05 实测）；基场景无覆写，默认 (0.8,1.2) 来自 ItemAnimation.gd:4-5 export。
  ②两嫌疑物证伪：RubyWhelp/FancyFencingRapier Animation.tscn 均继承基场景仅覆写 aniName，无 speed 覆写
  →实效域=默认 (0.8,1.2)，json 域 None/默认即正确表示（约定：仅覆写时落字段）；
  enrich_anim_speed.py --check exit=0（"1/518 件覆写；需更新 0 件"）亦证。③外围排除：Animations 目录外
  仅 BurningSword.tscn:125/Flame.tscn:146 有 maxSpeed=0.8（FlickerAnimation 节点另一域，已由
  flicker_max_speed=0.8 覆盖）；AmuletOfAlchemyAni/TimeDilatorAni.tscn 非 ItemAnimation（对应物品
  has_animation_scene=False 正确）；128 件 has_animation_scene=true 物品的 <Name>Animation.tscn 全部
  定位成功（unlocated=[]），ItemBook.gd:804-813 第三回退根 Exclusive/Unreleased/Animations 在树中不存在、
  无缺口。④消费链在树闭合：CoreItem.gd:992 / CoreItem.py:1129 ctx.rng.randf_range(descriptor.
  animSpeedMin/Max)。
- 修改：无。
- 验证：enrich_anim_speed.py --check（exit=0）；161 tscn 三根逐对字节 diff；128 件动画场景全定位。
- 残余（终态附记）：run933_r18/run1441_r11 之 Ruby Whelp 伤害 roll 分歧确证非动画 speed 域
  （与台账 r35 K16「dir 抽为真」结论一致），数据面无可修。

### C1MF（MF 狂热 ±1 ×2，K17 续）—— 终态：受阻（零修改收口）
- 根因：两场首分歧均为 MF 单次 gainTemporary(Heat,3) 的 roll 段判定差（非 giveMostBuffs/getMostStacks/
  选型翻转账本身）：run977 idx227（t=4.4）Evil Cap 15% resist，3 roll 下 O 抵抗 2 层/获得 1 层、
  G 抵抗 1 层/获得 2 层；run984 idx337（t=6.3）Paradise Birb 3 轮激活后 totalResistChance=15−3×7=−6
  （放大 6%），3 roll 下 O 中 0 得 3、G 中 1 得 4（全场 G 呈 4/5 波动、O 恒 3，FFR Lucky 亦 G5vO3
  同放大面）。逐事件 difflib 对拍证实 roll 次数两侧相同（消耗同，首分歧后紧邻事件仍逐条 SAME）。
  全链代码对读逐字同构（gd_core_items/Exclusive/MissFortune.gd↔oracle 同名仅 particles 差；
  CoreItem getMostStacks/giveMostBuffs↔oracle/Items/Item.gd:5573-5595；CoreBuff.gd gainTemporary↔
  oracle/Core/Buff.gd:76-200；CoreRng roll/flipPercent/randf_range/randi_range/pickRandomElement↔
  oracle/Utility/Util.gd:452-456/1087-1095；getChance/applyBonusChance、getLucky/useLucky、
  CoreConst.getBuffs↔Game.getBuffs）。数值两侧一致（MF luck=1/buffs=3、Evil Cap chance=15、
  PB chance=7，oracle/Sheets/CSV/ItemData.csv↔assets/battle_items.json）。判定差+消耗同+函数同构
  ⇒判定输入（totalResistChance 或 roll 值流）在链外上游已静默分叉（首分歧前事件面全同）；run977 的
  c=15 恒定无第二写入源→更可能 roll 值流静默错位（某处 gd 多/少抽或异原语抽取，与 K09 miss 单抽差、
  K16 dir 抽差同域）。
- 修改：无——分叉源头不在卡面文件（MissFortune.gd/.py）及其直调链，卡内无可修点，妄改同构文件只会
  引入新分歧。
- 验证：两场 difflib 全事件对拍；全链逐字代码对读；数值 CSV↔json 核对。
- 残余（终态附记）：恢复 ORACLE_ALIGN_TRACE 逐抽对位通道（落盘写空障碍待工具侧排查）或由持 Godot
  权限会话跑 rng_trace 到分歧时刻，一次判明「c 差」vs「值流错位」；归属「无事件面 rng 账」大卡
  （K09/K16 同盘收割）。

### C2PM（PM 魔法/充能 ×4，K19/K23）—— 终态：全绿
- 根因：CoreItemData.isAvailableFor 丢 stuffed 转换（gd_core/CoreItemData.gd:223-224 `(classes & classId)`
  ↔ oracle/Items/ItemDescriptor.gd:86,153-155 stuffClassIndex=1<<classI）→ 对 Engineer(6) 恒 False
  → PM.canAffect 对职业物恒假→numAffected=0→周期慢近一倍→四场首分歧。
- 修改：gd_core_items/Exclusive/PerpetuumMobile.gd:9-19 canAffect 内联 oracle isClassItem(6) 完整语义
  （行为逐位等价，绕过内核缺陷谓词）+ py 镜像重转写；备份 output/_round_patches/wf_C2PM/。
  CoreItemData.isAvailableFor 类级修复（补 stuffClassIndex，Laboratory 同域）在卡面文件外，待认领。
- 验证：定向验证 11 场 aligned=10/11；回归电池 7 场全绿（run570_r18,run1160_r18,run1029_r2,run862_r18,
  run813_r12,run635_r12,run732_r12，回归红=[]）→ green 收口，无 rollback。py 重放 run1331/1280/1530
  事件数与 oracle 全同、赢家全对（详见 output/oracle/wf_notes/C2PM.md 第五节）。
- 残余（终态附记）：run1101_r18 残余红——修后 py 重放 892 事件 vs oracle 961，赢家 opponent 已对，
  PM 事件面已齐，疑 17s+ 长战次级面非 PM 链；已按规则落盘 output/oracle/wf_notes/C2PM.md（第七节）
  并在本台账补收口节。

### C3MRS（Mr Struggles 泳道，K10/K12）—— 终态：全绿
- 根因：checkTriggerCount 时基语义差——oracle Item.gd:4403 复位分支 Util.time 为进程级时钟恒复位
  （门从不截断）vs gd_core/CoreItem.gd:867 ctx.time 战斗本地时钟，同窗第 11 次起永久截断+计数 runaway
  （76 场含 MrS 语料逐场模拟：截断⟺红场 15/15 全中、零绿场截断）。
- 修改：gd_core_items/MrStruggles.gd 覆写 checkTriggerCount 复位分支恒成立（等价神谕进程级时钟语义）；
  MrsStruggles.gd 零修改；py 镜像重转写；备份 output/_round_patches/wf_K10K12_MrS/。
- 验证：目标场集 22 场 aligned=18/22，卡面 4 场 run618_r18/run899_r18/run775_r18/run863_r18 全部转绿；
  回归电池 7 场全绿、回归红=[] → 按规则 green 收口，未 rollback。定谳节已落盘
  output/oracle/wf_notes/C3MRS.md（根因/修改/验证数/残余四节）。
- 残余（终态附记）：run628_r14、run928_r18、run933_r18、run977_r18——均原「截断红」名单成员，
  门修复后仍红，疑似流对齐后再撞第二层根因，非本门再截断，留后续卡二次取证（建议修后流前缀对齐点
  + ctx.rng.oracle_trace_log 逐抽对位）。

### C4QUAD（四物品包，K11/K18/K21/K22）—— 终态：受阻
- 根因：四物品脚本（gd_core_items/Exclusive/{DoomCap,GoldArmor,SpellScrollLight,Snowmaster}.gd）与
  oracle/Items/Exclusive/ 同名脚本逐行同构，卡面内零可修差；八场红全由卡面外三域造成。
  域A=PoweroftheMoon.onPostCombatStart→advanceTime(6)：gd_core/CoreCombat.gd:469 真实现把疲劳提前到
  5.033s，语料恒 17.017s 起（oracle_bootstrap.gd:108 combatSceneNode 是无脚本裸 Node2D，advanceTime
  调不存在的方法=静默无_op；语料 run1191 idx345/347 PotM T19+152@17.017 证 fatigue_start 连接有效、
  仅 advanceTime 无效）——污染 run741_r9/run1191_r13/run1192_r14。域B=oracle Util.callNextFrame
  （Util.gd:814 连 SceneTree.idle_frame）在 oracle_fight.gd:697 阻塞 tick 循环下永不发帧→
  endBlindingLight（Character.gd:1610）永不跑→语料全库 917 场 Lightsaber 每场每 owner 恒 1 次 proc
  （实测扫描 0 场多 proc），而 gd_core/CoreUtil.gd:191 忠实模拟 ctx.defer→py 光剑 6s 复触发
  （run986_r12 idx235 T102-3 used:true）全流带歪——污染 run986_r12。域C=gd_core/CoreBuff.gd:524-641
  四分支计时器模型残差：py 比语料早 1 tick 整批弹盲/冷层（run1036_r18 Burning Banner 盲-1@6.600、
  run1377_r13 Goobert 盲-7@6.117、run1231_r18 盲-7@4.467、run1444_r18 Frostbolt 冷-2@5.983），
  语料同批净化削余后别时点弹→下游给块/抗性翻转级联——即 r35_cards K01/C01「盲批到期相位」挂起
  研究域——污染其余 4 场。
- 修改：零（gd_core_items 8 文件零修改，无备份目录，gd_to_py 未跑）。
- 验证：import tools/verify_oracle.py 纯函数 canonical_stream 对拍 output/oracle/fights/<case>/events.json
  vs output/oracle/align/py/<case>/events.json，八场复算首分歧 99/451/235/164/86/165/195/330 与
  alignment.json 精确同位；未跑 Godot/verify_oracle 主流程/验证通道。
- 残余（终态附记）：域A 裁决（对齐目标=语料，gd_core 是否降级 advanceTime 为语料语义）+域B 全库
  影响面评估+域C 归 K01/C01 续关；任一域收口后复验八场（预期 3+1+4 随域级联转绿）。

### C5TRIO（三物品包，K06/K13/K20）—— 终态：受阻
- 根因：七场全红且 py≡gd（gdcoreEvents==pyEvents，转写忠实）；三对卡面脚本与 oracle/Items 逐行同构
  （仅 onready→_readyInit、Util.→ctx.util.、视觉行差），卡面零可修差。三根因均在卡面外：
  ①K13 APP（run805_r18/run879_r11）：gd_core/CoreItem.gd:975（activate）与 :3674-3677（activateFromEvent，
  在途新增）对音高补偿 ctx.rng.randf_range(0.9,1.1) 无条件 1 抽，而 oracle 是虚调用
  activate→playActivationSound→playDropSound(-6)（Item.gd:4676→:3171-3173），狼崽三家覆写
  playDropSound 纯无抽（oracle PowerPuppy.gd:10-12/CouragePuppy.gd:8-10/WisdomPuppy.gd:8-10，
  Armored 经继承）且 gd hooks 恒 pass（CoreHooks.py:54）不派发→每次狼崽激活 gd 多耗 1 位 rng
  （隔离实证：20+ 覆写面中 Rat/Toad/Wisp 等 14 家覆写体自带 pitch/randPitch 抽与基类等值，故
  run1172 带 Rat 至 16.1s 不歪；纯无抽者唯狼崽三家）。②K06 GirlPower（run608_r18/run613_r18/
  run729_r14）：冷却率差=影响格职业物计数差——引擎探针实测 py N=2（speedScale=0.7），oracle 首 proc
  3.483s 反推 N=3/6/4（N=2 时最早 proc=235 tick>观测 209，排除），Δ速率=0.35×k 整倍数；脚本与几何
  数据（GirlPower.tscn tile_data↔json affected_cells 逐格同）全排除→battle_items.json classes 数据面/
  语料 CSV vintage 漂移（K01 家族）；数据泳道正在改 classes（工作区未提交 SoU 0→2、Chili 0→8、
  Badger 0→4，按 repo CSV shop='no' 应为 None(0)，疑反向多计）。③K20 Crown 治疗（run1172_r18/
  run1176_r11）：治疗面零错证——run1172 全场 93 个 Crown 事件含 heal 8=8 对齐至 16.1s、
  run1176 heal 5=5；首分歧分别是域 C（CoreBuff 到期批早 1 tick：goobert 充能-2 批 16.167 vs 16.183，
  插队 Crown heal，K01/K03 挂起域）与域 A（PotM 疲惫提前 py t=5.033 T19+109，与 C4QUAD 节定谳逐位
  吻合，阵容两侧含 Power of the Moon）。
- 修改：零（卡面 6 文件零修改，无备份目录，gd_to_py 未跑）。
- 验证：五只读探针脚本 output/oracle/wf_notes/C5TRIO_{diff,geom,probe,probe2,timeline}.py 落盘可复跑；
  引擎装配探针实测 py N=2（未 eng.run()）；未跑 Godot/verify_oracle.py 主流程。
- 残余（终态附记）：修点已定位到行移交——内核泳道落地音高虚派发条件化（CoreItem.gd:975；注意
  ParadiseBirb/PoisonFrog/Rat/Snake/Squirrel 五覆写桩须各自补音高抽，否则引入新分歧，预期收割
  run805_r18/run879_r11 及一切含狼崽激活场）；数据泳道厘清 classes vintage；K01 域 A/C 突破后
  Crown 两场随域转绿。

### A1CRN（Crown 净化时基 ×4 + Coil 选批 ×3，K04/K08）—— 终态：受阻（零码改）
- 根因：商检 7 场 alignment.json 全部 oracle≠gdcore（无 skip 面）；三个互不相同的根，均不落在卡面文件
  （gd_core/CoreBuff.gd + gd_core_py/gd_core/CoreBuff.py）内。【K04-A：run771_r18(idx226)/run1203_r18(idx177)/
  run1281_r11(idx91)——fatigue advanceTime 系统性偏差，根在 CoreCombat/PoweroftheMoon 面】三场首分歧均为
  gd 在 t=5.0333 插入 PotM 的 ty19 TemporaryMaxHealth+ty0 激活各两次（fatigue_start 信号标记，
  PoweroftheMoon.gd:42-45），oracle 同位无此事件。全库 21 个含 PotM 场扫描：oracle fatigue_start
  恒=17.0167 或无，gd 恒=5.0333（=17−3−2×time6 起爆+3s 首击，time=6.0 见 assets/battle_items.json
  named_params；两件 PotM 共提前 12s）。真源侧 oracle 链路完整（PoweroftheMoon.gd onPostCombatStart→
  Core/Combat.gd:920 advanceTime→CombatTimer.gd:184-198）但语料经验律=从未生效；gd 移植恒施加
  （PoweroftheMoon.gd:26-27、CoreCombat.gd:476 time_advance+=、:245 fatigue_next_tick=17−3−time_advance）
  ——移植越权于神谕行为。修复面=gd_core_items/Exclusive/PoweroftheMoon.gd + gd_core/CoreCombat.gd
  （方向：对齐 21/21 经验律不提前/复刻 harness 桩语义；harness 内部吞没机制未闭，需活体 trace 定谳）。
  注意 run771 的 Crown 净化链本身双端一致（对手 Crown tk304 净化+治疗+激活三事件仅被插入事件平移
  4 位）——「净化触发链时序」无缺陷，卡题面假设被取证否定。【K04-B：run1038_r9(idx141)——Blind 临时批
  到期相位，K01/K03 挂起盘】gd 侧 BurningBanner tk407 施加 Blind(dur5) 后 tk408 即 timeout（四分支模型
  ② 残留瞬弹支，CoreBuff.gd:56-77/570-576），oracle 侧同批存活过 tk415 净化、最终 tk440（+33 tick，
  非 300tick 自然到期亦非瞬弹）才 fire；逐字对读真源 Buff.gd 与 oracle_fight.gd:880-925 drive_timers
  静态推演无法导出 +33tk 律（与 run688_r10 已验证瞬弹配置正面矛盾）；对 ② 支盲改将回退 run688 实证面
  ——不修。【K08：run1102_r18(idx200)/run1104_r18(idx153)/run1105_r18(idx327)——Coil 选批上游链静默
  分叉，K17 同族】真路径=Coil.gd:10-16 onChargeReceived→stealRandomBuff（CoreItem.gd:2747）→
  pickRandomStacks（CoreItem.gd:2482）→ctx.rng.pickRandomElement（CoreRng.gd:146），并非卡面假设的
  removeBuffsFraction/sortDict；选批代码与真源（oracle/Items/Item.gd:5422-5446、Util.gd:452-456）逐字
  同构；python 重放双流 events 至分歧点重建受害者栈态双端全同（run1104: Block55/Lucky2/Regen1/Spikes3/
  Mana9；run1102: Block307/Lucky5/Spikes2/Mana31/Empower16/Blind2；run1105: Block446/Lucky5/Spikes2/
  Mana23/Empower7/Heat2/Blind7）；首分歧落在第 1 抽或第 2-3 抽而紧邻循环内无状态变化⇒rng 值流在链外
  上游已静默分叉（与台账「r35 K17 续取证」判定完全同签名）。定位需 ORACLE_ALIGN_TRACE 双指针抽序
  对拍（本轮禁跑 Godot 且 K17 节已录 trace 落盘链路异常待工具侧排查）。
- 修改：零码改（backup 未建、gd_to_py 未跑）；r26 卡B BSCHED 取证桩（CoreBuff.gd 三处）保留
  （oracle_trace 门控、零行为差），其消费者 K01（40 场）仍挂起，不撤。
- 验证：7 场 alignment.json perCase 实读；21 含 PotM 场全库扫描；python 重放重建受害者栈态；
  git status 验净（两文件态与开工基线一致）+ 探针 tag grep 零命中。
- 残余（终态附记）：K04-A 三场→CoreCombat/PoweroftheMoon 泳道（先带活体 trace 查 harness 吞没机制
  再动码）；K04-B run1038→K01 研究卡（40 场盘勿硬修，建议 BSCHED 桩对 run1038/run688 双场同跑对表）；
  K08 三场→K17 盘（待 rng_trace 落盘链路修复后双指针抽序对拍）。

### A2SIG（锤链 + miss 链，K02/K09）—— 终态：受阻（零改码收尾）
- 根因：两卡假设均证伪，真根因=激活音高幻抽（同源，落点 gd_core/CoreItem.gd:975，文件面外）。
  ①run683_r9（卡面误写 r18，alignment.json/fights/lineups 实为 r9）idx64 锤伤 9v7：EventBus Delayed
  假设无面——oracle/Utility/EventBus.gd 与 gd_core/CoreEventBus.gd 逐段同构，Delayed 包裹只存在于
  oracle Item.gd:5448-5694 九函数+Bomb/Bazooka/DjinnLamp/GingerbreadMan，run683 阵容 21 种物品经
  battle_items.json behavior 全查 0 调用→Delayed 窗零开启；EMPC 零触发差是下游噪声（gd 首个 T106/EMPC
  t=4.25，trace_r35b 行1254-1255，晚于 idx64 t=3.2）。②run610 idx108 miss 链：0.943325 恰为第 636 抽
  （与台账双指针 #636 精确对上，trace_r35e），其链位在 AWP(owner1) t=3.2833 激活之后、不在任何
  takeDamage 内（无 CANMISS 邻接）——takeDamage 的 playback 抽/miss 零抽模型（CoreCharacter.gd:746-747
  ↔ oracle Character.gd:616-625）逐行同构无差。真根因：oracle activate()→playActivationSound()→
  playDropSound(-6)（Item.gd:4676-4678→:3171-3173 基类抽 randf_range(0.9,1.1)），20 个物品覆写
  playDropSound，15 个无音高抽（WisdomPuppy:8-10 直放；BadgerSpirit/CatSpirit/CouragePuppy/PowerPuppy/
  Crow/EvilHat/Ghost/HyperHedgehog/OwlSpirit/Pop/Toad/Ukulele/WaterElemental/Wisp 同构；Armored
  继承 WisdomPuppy），5 个保留（ParadiseBirb/PoisonFrog/Rat/Snake/Squirrel）；gd_core/CoreItem.gd:975
  每次激活无条件抽 1 抽→AWP/灵体族每次激活 gd 多耗 1 抽（oracle 0 抽）静默错位：run683 gd 第 482 抽
  （trace_r35b 行994，0.912009）=idx63 AWP(owner1) t=3.2 激活同源幻抽→idx64 锤读错位抽
  （O roll11→round(11×0.78)=9 vs G roll9→7）、idx66 龙 O9vG8 同解，两侧 ×0.78 Stoned 减伤账全对齐；
  run610 #636 起错位→冷却卷错位→idx108 Stone 命中 roll 翻面。run1447：阵容 15 幻抽族零命中，与本
  根因无关，idx213 首分歧=Light Goobert T109 盲到期（C01 研究域），已重配 K01 盘。卡内两文件
  （CoreEventBus/CoreCharacter）与 oracle 全同构，零缺陷。
- 修改：零（无探针桩入树、无 output/_round_patches/wf_A2SIG 备份——无 patch 即无备份）。
- 验证：三场 alignment.json 现状实读（无 skip）；trace_r35b/r35e 离线逐抽对位（#636/#482 精确对上）；
  阵容 behavior 全查。
- 残余（终态附记）：修法交 CoreItem 泳道——CoreItem.activate() :975 无条件抽改动态派发
  （activate 调 playDropSound(-6)，基类承接音高抽，gd_core_items 覆写桩天然跳过）；五例外
  （ParadiseBirb/PoisonFrog/Rat/Snake/Squirrel）的 gd 覆写桩须各自补音高抽；预期收割 run610/run683
  及 AWP 族全场。

### A3BLD（盲族 ×40 取证轮，K01/K03）—— 终态：受阻（维持挂起）
- 根因：corpus 时代盲批到期语义无法从事件流反推为任何静态规则。取证=python 只读分析
  run619_r18/run622_r15/run665_r14 corpus T109(Blind=109) 全账（685 个到期弹，
  output/oracle/fights/*/events.json）。规则空间穷尽：变异×选批（farthest/nearest/oldest/youngest/none
  × 批余/min(current,批余)）最好 632/685；按净化源分派（Crown/Shelly/Recomb 4³ 组合）不升；
  指针悬空变体（nTT keep/dec、OOB earliest/last）与完整引擎模拟（Godot Timer 帧量化开火+递归弹链+
  静默零弹+最远批净化+Util.time 偏移）=623/685=91%，其中 run622_r15 tgt0 60/60 全拟合、
  run619_r18 tgt1 235/242。残差为有状态时变行为：run619_r18 tgt0 前 15 弹（至 14.2s）corpus 到期
  全=原始额 7（净化零突变批次），恰在净化事件 2190(t=14.6167) 后切换为最远批变异语义（2272 弹 -3=
  恰吸收 2190+2193+2232 共 4 层）；run665_r14 tgt0 全程零突变（none 规则 53/53 完拟合，同场 tgt1
  却有突变）；最小反例=run619 同战同构局面 tgt1 净化突变/tgt0 不突变；晚段偶发同 ts 孪生级联内
  弹序互换（吸收总量一致）。旁支假设全排除：净化源物品异构（cleanseBlind 与 cleanseRandomDebuffs
  均汇入 loseStacks，gd_core/CoreItem.gd:2380,2456）、净化保护池（run619 阵容无授予物品且 corpus
  净化事件额=实落额）、rng 驱动选批（r34 C01 已证首分歧前 RNG 逐位同）、current 快照/原始额/min
  截断公式（tgt0 307 处 current=10>7、tgt1 317 处逐一否）。gd 现行语义（最远批+min(current,批余)，
  CoreBuff.gd:346-382,387-390）在 idx307 给 -5 vs corpus -7，即台账 r34 C01 首分歧，本轮在更大数据面
  证实其根因是 corpus 时代构建（10-06/07）的 Buff 内部账与现行树不同且为时变状态行为，非现行树可
  取证（git 对 oracle/ 无历史，b1_c1 bak=现行，decompiled_full=Sep17 现行游戏≠corpus 时代）。
- 修改：零（CoreBuff.gd/.py 保持 2e053483 基线语义）。
- 验证：9 个只读分析脚本落盘 output/_round_patches/wf_a3bld/（analyze_blind/fit_rules/source_rule/
  consistency/pop_table/batch_features/pointer_model/engine_sim/engine_sim2.py）可复跑；未触碰 oracle/。
- 残余（终态附记）：解锁三选一——找回 corpus 时代 oracle 树 Buff.gd（现存备份均=现行，需新考古
  来源）/ corpus 同版本构建重放（Godot，共享验证员通道另行立项）/ K01+K03 40 场改走「oracle 事件
  重放」而非 gd 模拟对齐（超卡面文件面，需工作流层决策）。

### wf8 横向移交汇总（跨卡三域 + 两族，下窗入口）
- 域A PotM advanceTime：语料 21/21 恒不提前（harness 吞没机制未闭），gd 恒提前 12s——C4QUAD/A1CRN/
  C5TRIO 三泳道共同定谳；落点 PoweroftheMoon.gd+CoreCombat.gd，先活体 trace 后动码。
- 域B callNextFrame 饥饿：语料 Lightsaber 917 场恒单 proc vs py 复触发——全库影响面评估后再动。
- 域C 盲/冷批到期相位：K01/C01 挂起研究域，A3BLD 证实 corpus 语义为时变状态行为、事件流反推不可得。
- 音高幻抽族：CoreItem.gd:975 无条件抽——C5TRIO+A2SIG 双泳道定谳，修法=playDropSound 虚派发+
  五例外补抽。
- rng 值流静默错位族：C1MF(K17)/K08 同签名——修 ORACLE_ALIGN_TRACE 落盘链路后双指针对拍。

## r36 层 1（wf9 幻抽 + PotM 实效语义）：740 → 788（+48，退步 0）

日期：2026-10-17 夜。全量 `verify_oracle.py --force` 914 场，结果
`output/oracle/alignment_wf9_full.json`（已覆盖 alignment.json）；快照
`aligned_sets/r36_l1.txt`；对 r35_l1 退步检：新增 48、退步 0。

### 一、激活音高幻抽（A2SIG/C5TRIO 定谳，本轮落地）

- 真源：oracle `activate()`（Item.gd:4715）→ `playActivationSound()`（:4676-4677）
  → **虚派发** `playDropSound(-6)`。基类 :3171-3173 抽 1 次；全库 20 家覆写体中
  17 家各自抽 1 次（Rat/Toad/Wisp/ParadiseBirb…，逐脚本核对 `ctx.rng.randf_range`），
  **狼崽三家（Power/Courage/Wisdom Puppy）零抽**；TimeDilator 另覆写
  playActivationSound 亦零抽。
- gd 旧实现：CoreItem.activate/activateFromEvent **无条件**补 1 抽，对狼崽族每次
  激活多耗 1 位 → 全流后移（run610 #636、run683 idx64 两处独立定谳）。
- 修法（1:1 虚派发）：
  1. `gd_core/CoreItem.gd` activate/activateFromEvent 改为
     `if has_method("playActivationSound"): call("playActivationSound") else: 旧抽`；
     删去末尾重复的 `ctx.hooks.playActivationSound(self)`（声音已由行为体承接）。
  2. `gd_core_items/Item.gd` 基类适配层 `playDropSound` 由 `pass` 改为补 1 抽
     （镜像 Item.gd:3171-3173 的 `Util.rng_trace_range(0.9,1.1)`）。
  3. `tools/build_item_scripts.py` 增 `restore_base_drop_draw()` 再生 pass（幂等），
     防止下次重生成适配层时把基类抽再次剥成 pass。
- 验证：run610_r18/run683_r9/run805_r18/run879_r11 全绿；连带 run571/871/933
  （Ruby Whelp K16）、run618/775/863/899（MrS K10/K12）等转绿。
- 备份：`output/_round_patches/wf9_phantom/`（CoreItem/CoreCombat/Item 适配层）。

### 二、PotM advanceTime 实效语义（r35 域A 定谳，本轮落地）

- 真源链：`PoweroftheMoon.onPostCombatStart` → `Game.combatSceneNode.advanceTime`
  → Combat.gd:920-926 → CombatTimer.gd:184-198，静态完整；但神谕引导骨架
  `oracle/oracle_bootstrap.gd:108` 的 "Combat" 是**裸 Node2D（未挂 Core/Combat.gd）**
  → 该方法不存在，GDScript 运行期报错后原样跳过。
- 实证：全库 21 个含 PotM 场，语料 fatigue/PotM 首个 T19 恒 17.016667（或无），
  无一场提前；gd 旧行为恒 5.0333（两件共提前 12s）。
- 修法：`gd_core/CoreCombat.gd::advanceTime` 置空（time_advance 恒 0），
  原实现与举证留在函数头注释 + 备份。
- 验证：run771/1203/1281/1176/1123/1132/734/744/792/974/1191/1192/741 等
  PotM 场转绿（run771/1132 首分歧后移至盲到期域；run1172 后移至 Carrot Goobert 盲到期）。

### 三、本轮未动/待续

- 音高五例外（ParadiseBirb 0.8/1.0、Toad/Wisp 等 `Util.randPitch`）在 gd 覆写体
  已有 1 抽，虚派发后自动同构，无需另行补抽。
- `hasBattleRageEffect` 数据缺口：17 条描述含 `$rage[` 的物品（Toolbox/Anvil/
  Dragon Knight/Spiked Staff/Chain Whip/…），但 914 场中仅 run1202/run947 两侧
  无 BattleRage 起手物 → 影响面 2 场（run1202 当前已绿），优先级低。
- 残余 126 场：盲/冷批到期域约 48（LG 36 + Banner 7 + 其他）、Coil 7、
  Girl Power 4、False Life 3（GEN1 代际漂移）、Mana Orb 3、py 纯转写 1。

## r37 层 1（域B idle_frame 饥饿 + Zap 电弧缺抽）：789 → 808（+19，退步 0）

日期：2026-10-18 凌晨。全量 `tools/verify_oracle.py --force` 914 场，结果
`output/oracle/alignment_r37_full.json`；快照 `aligned_sets/r37_l1.txt`。
gd 腿单独扫描（`output/oracle/_r37_gd_scan.json`）= **808/914 一致，退步 0，较上轮 +19**。

### 一、域B「callNextFrame 饥饿」定谳落地（A1CRN/A2SIG/C5TRIO 悬案）

- 真源：`Util.callNextFrame`（oracle/Utility/Util.gd:814）把回调挂到
  SceneTree 的 `idle_frame`（ONESHOT）；语料由 `oracle_fight.gd` 的**阻塞式 tick 循环**
  录制，主线程整场被占，idle 阶段一次都不跑 → 回调**永不派发**。
- 全库实证：914 场 events.json 扫描，凡含 Lightsaber 的场，每 owner 的
  `useRegeneration`(type102) **恒 1 次**（0 场二次 proc）；`endBlindingLight` 缺席使
  `blindingLightActive` 永久为真 → onRegenChanged 的 `not blindingLightActive` 门恒假。
  gd 旧实现转 `ctx.defer` 帧末队列照常派发 → 每 6s 复 proc：run691_r18 语料 2 次 vs
  gd **112** 次、run986_r12 语料 0 次 vs gd **80** 次。
- 修法：
  1. `gd_core/CoreUtil.gd::callNextFrame` 改为 `_ctx.idleFrameStarved(...)`（只入队、整场不派发）；
  2. `gd_core/CoreContext.gd` 新增 `_idle_frame` 队列 + `idleFrameStarved()` + `idleFrameCount()`
     （与 `ctx.defer`/`flushDeferred` 严格分离：call_deferred 在神谕帧末正常执行，不受影响）。
- 验证：8 场定向 + 回归电池 13 场 gd 腿全绿；6 场当场转绿
  （run691_r18 / run713_r11 / run1095_r18 / run1143_r13 / run1180_r11 / run1228_r11）；
  run986_r12 首分歧由 idx235 后移至 idx271（盲族），run1363_r12 后移至 Dragon Knight 伤害。

### 二、Zap 电弧缺抽（K08 Coil 族根因）

- 方法（本轮新仪器，见第四节）：用当前 oracle 树重放 run1102_r18，**逐事件与语料完全一致**
  （731 事件零分歧）并落 `rng_log.txt`；与 gd `rng_trace.txt` 逐抽对位 →
  首个分歧 = **raw#1085 `randf_range 4 4.02`**（Items/Animations/Zap.gd:32 的 shader speed），
  gd 缺这一抽 → 紧随其后的 Coil `pickRandomElement` 整体移位。
- 修法（两处同源缺抽，各补 1 抽）：
  - `gd_core_items/Exclusive/ThunderDrake.gd::zapItem`：`hasOnChargeReceivedEffect` 分支内，
    `chargeReceived` 之后补 `ctx.rng.randf_range(4.0, 4.02)`；
  - `gd_core_items/Exclusive/TeslaCoil.gd::advanceItem`：`advanceCooldownSeconds` 之后补同款 1 抽。
- 验证：Coil 族 10 场中 9 场当场三方全绿（run1097/1102/1103/1104/1105/1106/1108/1109/1163），
  run1198_r18 首分歧后移至 White King 捕获给 buff（新卡）。
- 连带转绿（非预期）：run1107_r18、run687_r18（Resistor 抗性）、run733_r9（Rapier 伤害）、
  run1404_r18 —— 均为「上游缺抽 → 全流错位」同族。

### 三、K08/K17 定位工具链修复（run977 trace 写空不再是障碍）

- 旧障碍：`output/oracle/align/gdcore/<case>/rng_trace.txt` 对 run977_r18 恒 0 字节。
- 本轮改用**隔离产物目录 + 单场重放**（`ORACLE_ALIGN_OUT` / `ORACLE_FIGHTS_ROOT` 重定向），
  run1102/run1198/run608 的 trace 与 rng_log 均正常落盘（229KB / 263KB 量级），逐抽对位可跑。
  结论：旧障碍是主产物目录 resume/写盘路径问题，不是追踪器本身。

### 四、新仪器：语料代际对拍（决定「可修/不可修」）

```
ORACLE_FIGHTS_ROOT=<scratch>  ORACLE_ONLY_CASES=<id>  ORACLE_DEBUG=[1] \
  godot --headless --audio-driver Dummy --path oracle --script oracle_fight.gd
```

用**当前 oracle 树**重放语料场并与冻结语料对拍，判定规则：
- 重放 == 语料 ⇒ 语料可由当前树复现 ⇒ **gd 真 bug，可修**；
- 重放 ≠ 语料（且与 gd 同分歧） ⇒ 语料来自旧构建/旧数据 ⇒ **不可修（vintage）**。

本轮判定样本（证据留档在 `output/oracle/probe/`）：

| 场 | 重放 vs 语料 | 结论 |
|---|---|---|
| run1102 / run1198 / run608 / run597 / run1441 / run1499 / run1514 / run1101 / run695 / run947 | 一致 | 可修 |
| run771_r18（光黏黏盲批） | 分歧 @idx268（语料 -3 / 重放 -2，与 gd 同） | 盲族不可修 |
| run619_r18 | 分歧 @idx22（Rapier 伤害 15 vs 13） | vintage |
| run622_r15 / run602_r14 / run906_r18 / run939_r18 / run1125_r18 / run1409_r18 / run1424_r10 / run1083_r18 | 分歧 | vintage |

即：**剩余失败的大头（109 盲族 49 场 + 部分其它）源于语料与当前树的数据/构建代际差**，
在「语料冻结只读」的红线下无法通过改 gd 达到一致。

### 五、本轮残余（106 场，gd 腿）

```
109 盲族 49 | 伤害 14 | 法力 8 | 再生 6 | 临时生命 6 | 毒 3 | 热 3 | 冷 3 | 强化 3 | 其它 11
```

已判定「可修、未修」：run1441_r11 / run1499_r15 / run1514_r18（伤害）、
run1101_r18 / run695_r18 / run947_r10（法力）、Girl Power 四场（run597/608/613/729，影响格几何）。

### 六、Girl Power 几何缺陷（半定谳）

- 现象：gd 的 `getNumDistinctAffectedItems()` 比 oracle 少 1 → addSpeed 少 0.35 → 首次激活
  4.2s vs 语料 3.4833s（run608_r18）。
- 实测（隔离工程 `gd_core_probe/`，不动主线夹具）：把 Girl Power 的受影响格补 1 格
  （`grid.affected_cells` 加 `[3,0]`，run608 rot=0 时映射到 Cauldron 所在 `[4,4]`），
  首次激活即 3.4833/3.5333/6.8 —— 与语料**逐位一致**。
- 但 90°/270° 旋转的三场（run597/613/729）仍差 → 说明 `battle_items.json` 的
  Girl Power `grid.affected_cells` 与真实 tscn TileMap（`oracle/Items/Exclusive/GirlPower.tscn`
  的 CollisionMap tile_data，15 个 affected + 1 个 collision）**坐标系不一致**（不是简单缺 1 格）。
- 处置：未改数据（红线：改 `assets/battle_items.json` 必须同步跑
  `gen_lineup_fixture.py` + `gen_gd_core_data.py`，且会影响全库几何，需单独一轮验证）。
  下一轮入口：以 tscn TileMap 为真值重算 GP 的 grid（注意 (x=col,y=row) 与 16 位打包解码）。

### 七、本轮未动 / 待续

- 12 张问题卡施工单已写好：`sub-task.md`（根目录，可直接交给另一个智能体执行；
  含红线、命令模板、逐卡首分歧事实与交付格式）。
- `gd_core_probe/`：隔离 Godot 工程（junction 到 gd_core、gd_core_items），用于改夹具做实验，
  不影响主线；实验脚本 `tools/_probe_gd_compare.py`、`_probe_py_run.py`、`_probe_draw_diff.py` 保留。
- 备份：本轮 CoreUtil/CoreContext/ThunderDrake/TeslaCoil 改动在 `output/_round_patches/wf_r36_l2/`
  （备份为改后副本；前态可用本文件记录的 old_string 还原，或 `git diff` 查）。

## np2 层1（offpeak-3a8de108，2026-10-18）：RubyChonk randomizePosition 3 抽 + harness trace 写盘修复

### 根因1：RubyChonk.doCooldownEffect 缺 createAnimation()+ani.randomizePosition() 3 抽（类级）
- 真源 oracle/Items/RubyChonk.gd:30-31（dealDamage→activate→createAnimation→randomizePosition，
  ItemAnimation.gd:26-28 恒 3 抽 (-30,30)/(-100,100)/(-5,5)，直调不经 intialize 无 playback_speed）。
  全族仅两成员：FalconBlade（r2_1 已修）+ RubyChonk（本次漏修，转写剥空 pass）。
- 逐抽定位链：run695_r18 重放=语料（可修）→ gd trace 全量对拍 → 首 #888 =
  O(-30,30) vs G(0.975,1.05)，Ruby Chonk 首proc（t≈1.5s）缺 3 抽 → 链前移 →
  idx163 Fedora 偷取选型 O105(法力-2) vs G107(热-1) → 全场事件风暴（gd 25054 ev 触看门狗）。
- 修复：gd_core_items/RubyChonk.gd doCooldownEffect 在 activate 后补 3 抽（注释同 FalconBlade 口径）；
  gd_core_py/gd_core_items/RubyChonk.py 经 gd_to_py 再生（+11 行）。备份 output/_round_patches/np2_rubychonk/。
- 验证：run695_r18 一致 ev=16937；run1514_r18 一致 ev=389（同根因第二收割）；
  回归电池 REG 7 场全绿零回滚。
- 附带修（仪器）：gd_core_test/OracleAlignBattle.gd trace 写盘两处——①巨量 PoolStringArray.join
  静默崩溃/窒息（旧代码，run977"恒写空"真根因）改 store_line 流式；②4 元素取证桩行（LGPROC 等）
  硬取 e[4] 格式错误中断写循环 → trace 从首个 4 元素行截断（run695 恒 811 行实锤），改按实际元数拼接。
  备份 output/_round_patches/np2_harness/。诊断桩 RNGDIAG（ORACLE_RNG_DIAG=1）保留。
  遗留澄清：双 Godot 同 scratch 目录竞写曾制造"文件回缩"伪象，净场单进程已排除。

### np2 待办（余 4 可修场 + C 卡面）
- run947_r10（Rainbow Potion 随机 buff 选型，ev=6 O105(法力3) vs G103(吸血3)）。
- run1101_r18（Perpetuum Mobile 法力，ev=172）、run1441_r11（Ruby Whelp 伤害 roll）、
  run1499_r15（Poison Spear 伤害）——oracle 重放带 rng_log 进行中（probe/np2_or4）。
- C 卡 vintage 已证：C11 run1198_r18 重放=gd 行为(105/106/107)≠语料(101/103/102) → 语料代际漂移；
  C2 run1343/1349 重放 @40/@15 分歧 → vintage。

### np2 层1 收口（终态）
- **fixed 2 场**：run695_r18（ev=16937 一致）、run1514_r18（ev=389 一致）——RubyChonk 3 抽类级根因；
  终态复验 9/9（REG 7+2 修复场，align/np2k）。
- **vintage 2 卡**：C11 run1198_r18（重放=gd 行为 105/106/107 ≠ 语料 101/103/102，@19 实证，
  纠正 handoff §四误记）、C2 run1343/1349（重放 DIV@40/@15）。
- **blocked 3 场（带线索）**：run947=开局冷却抖动平手组左旋一位（SpikedStaff 首↔尾，双侧同构；
  疑 oracle 引擎链 seed→shuffle 间未复刻消耗，需引擎链审计）；run1441/1499=开战 ctor 流中 gd 少
  1 笔激活音高（生成族/Piggy Pinata 邻域，GEN1 接线二阶段近亲）；run1101 未定位（trace 已就绪）。
- **仪器**：harness trace 写盘双缺陷修复（巨 join 崩溃 / 4 元素桩行截断）——run977「trace 恒写空」
  与 run695「恒 811 行」两桩历史悬案同轮定谳；逐抽对位法自此全面解卡。
- 下轮入口：①run1101 逐抽（trace 在 align/np2i）②1441/1499 音高单点（EVENT 锚定激活者）
  ③run947 引擎链审计 ④C5-C12 余卡 3.3 判定。报告：output/oracle/offpeak_np2_report.md。

## np3 层收口（offpeak-68b5d7c0，2026-10-18）
- **vintage +5**：C5 run697_r15(@87)、C8 run686_r18(@31)、C9 run846_r11(@5)、C10 run895_r10(@8)、
  B9 run1372_r18(@57)——C9/C10=GEN1 生成族代际漂移实锤。余卡 3.3 三角判定全部结案：
  可修=C6 run921/C7 run1051/C12 run977/B8 run1347（trace 全落 align/np3c，首分歧
  @1483/@34/@450/@2244）。
- **无码修复**；4 可修卡推进至根因定性层，共同形态=**开战序/冷却边界发丝差**：
  ①run1101 PM 冷却启动反转（PMCHK 实证 descr_cd=8 而 iterCd=0/active=False，首 proc 才起冷却；
  oracle 开战 7.897 递减）+ PM speed 1.9 vs 2.36（oracle 非整数分解⇒未建模速度来源）；
  ②run947 开局抖动 gd 28 vs oracle 34（尾部多 6 笔 (0.95)）；
  ③run1051 prepare 流音高位次差 6 槽（The Lovers 邻域）；
  ⇒ 三案并案指向 **oracle 描述符 cd/speed 数据面审计**（一批物品 oracle cd>0 而
  battle_items.json=0 / oracle PM 速度构成未建模）=下轮首选。
- **仪器**：harness 目录时序修复——tick 循环期 item_trace 写盘目录未建致恒缺失；**双端
  ORACLE_TRACE_ITEM item_trace 仪器打通**（1101 PM 曲线 5032/1952 行落盘）；PMCHK/ENVCHK
  用后已剥，RNGDIAG 桩保留。977 大赛 trace 33553 行全量落盘=上轮修复实效验证。
- 下轮入口：①oracle cd/speed 数据面审计（947/1101 并案）②C6/C12/B8 逐抽（trace 已备）
  ③C7 位次并案 ④1441/1499 音高单点。报告：output/oracle/offpeak_np3_report.md。

### np3 会话清理（2026-10-18）
- align/ 3.0G→1.6G：删旧 staged 全量变体（gdcore_s1/s2、py_s1/s2/s2_check、render_s1/s2、
  py_smoke）、旧轮 trace scratch（trace_r32b/r34a-c/r35a-h、gdcore_ts570a-g、gdcore_trace*、
  gdcore_g11/g13、gdcore_r22trace、events_prev、np2a-k、np3b、np2probe、probe_r22、
  probe_r36_*、probe_r37_t608、probe_gp_*）与全部 *.log。**保留**：主产物 gdcore/py/
  render/lineups + np3a（1101 PM 曲线证据）+ np3c（C6/C12/B8/C7 下轮逐抽 trace）。
- probe/ 583M→87M：保留 15 个被引用证据目录（r36_or1102/r36_or1198/r36_or771、r37_or_*
  8 个、np2_or4[947/1441/1499 下轮 rng_log]、np3_or4b[4 可修场 rng_log]、np3_or1101pm/td
  [PM 曲线]），删其余 ~85 个旧轮 probe。
- output/oracle/：alignment_*.json 80+→3（alignment.json / r37_full / wf10_full）；
  aligned_sets 46→6（r33→r37 演进链）；删 buff_probe/pmax_probe/probe_r2_1*/r3_1（~138M）、
  根诊断 _op*/_probe*/_f7*、batch/bisect 日志。
- 删 output/oracle/session_handoff_20261016.md（已过时交接文档，用户已点名作废；
  其在途 classes 警告已由 r37 数据面定谳吸收）。/tmp/np*.log 清。
- 终验：fights/ 920 项未动（run695 语料抽查 16937 events 通过）；主产物/证据集齐全；
  全程未触碰 oracle/ 反编译工程与 git 历史。

## np4 层收口（workflow，2026-10-18）

本轮 workflow 五卡并行收口，终态 5×受阻留档 / 0 fixed：数据面 cd-speed 审计定谳两场分歧均在引擎面而非数据面（47 物品全字段零失配），PineProtector/MissFortune/Holdall/开战序位次四案根因分别定性至内核链（invul 延长支不清、Buff 临时栈到期相位早一拍）与数据层/几何面（battle_items.json classes 错值、棋盘捕获可见性语义），线索全部落盘 output/oracle/wf_notes/np4_*.md 待对应卡认领。

- **数据面 cd-speed 审计（DATA1）—— 受阻留档**：两场分歧均非数据面。47 个阵容物品 oracle ItemData.csv↔
  battle_items.json↔item_battle_fixture.json 全字段（cd/具名+位置参数/minDam/maxDam/accuracy/block/
  staminaCost/price/chance/chance2/PM 受影响格）零失配。run1101 首分歧在 PM 首周期（oracle t=3.35 vs
  gd 3.8333，事件 idx172，rng 同步至第 859 抽；oracle 把抖动第 7 抽 0.987074 指派给 PM=
  8×0.987074=7.8966），指派序与速度热度链在 gd_core/OracleAlignBattle 引擎面：oracle/Items/Item.gd:
  3357-3370,3729-3752、oracle/Core/Game.gd:2637-2649、gd_core/CoreCombat.gd:152-186、
  gd_core_test/OracleAlignBattle.gd:327-350。run947 首分歧在 t=0 idx6 RainbowPotion 随机 buff 选型
  （oracle 池序[4,3,2,2,4,4]→T105:3/T104:1/T103:2 vs gd→T103:3/T105:2/T101:1，np2_or4 rng_log:213-218），
  同池同取法不同值⇒抖动段 rng 流先失步，cd=0 名单假设不成立——oracle 抖动 26 抽=13+13 恰等于双方
  cd>0 数，数据全对。另证两条 item_trace 均不可信（gd np3a PM iterCd=0 全程 vs 同目录 events.json PM
  3.83/7.75/11.33s 正常触发，自相矛盾；oracle np3 probe PM speed=2.36 恒定与自身 t=0 T107+3 热度事件
  互斥）。改动：无（未改码、未备份、未再生 gen 工具）；gd_core_test/oracle_align_cases.json 保持 914 场
  （只读核对）。留档 output/oracle/wf_notes/np4_DATA1.md。
- **PineProtector 时序（PINE）—— 受阻留档**：根因在内核面——gd_core/CoreCharacter.gd:1484-1488
  makeInvulnerable 延长支不清 _invul_instant（:1481 首支由玩家 Goobert 6.116667 同 dur 重 start 置 true），
  驱动块 :2109-2117 同帧清零 _invul_left → :2125 幻影 InvulnerableEnd id304 t=6.116667 提前 3 tick；
  oracle 侧 changeTimer（oracle_fight.gd:896-902 重同步支 + Util.gd:1671-1677 重写引擎读数）使延长支
  结构上不可能同帧到期——O 玩家侧 1.5+2.5=4.0s 实跑到 10.133333（O id537，精确 241 tick）。
  解法=else 支补 _invul_instant=false，待内核串行卡认领。零改码（PineProtector.gd、FrogPrince.gd 与
  oracle 侧逐行等价且时相一致，无需备份/回滚）。留档 output/oracle/wf_notes/np4_PINE.md。
- **MissFortune 值流（MF）—— 受阻留档**：首分歧不在物品面——gd_core/CoreBuff.gd 临时栈计时器到期
  语义早一拍（side0 KEEP/B1P 挂靠 gd 准点 7.716667 弹盲眼批，oracle 恒 +1 tick 7.733333，同批集合
  {MrS -8×3, LG -7}）。内核线索 gd_core/CoreBuff.gd:561-568 分支①'（同帧 stop+start，无 resync）、
  :607-645 _tick fire；oracle 真值 decompiled_full/Core/Buff.gd:33-36/155-169/317-336。
  MissFortune.gd/MrStruggles.gd 双源逐字同构且 rng 流锁到第 2244 抽，物品面免责。新建留档
  output/oracle/wf_notes/np4_MF.md（无代码改动故无备份/还原）。
- **Holdall 开局格挡（HOLD）—— 受阻留档**：run1347_r18 Holdall 无事件的根因是 assets/battle_items.json
  classes 数据错（Spectral Dagger=0、Shaman Mask=4，oracle 真值均 127）：包内 4 件 classes 全非 127 ⇒
  gd_core/CoreItemData.gd:326:221 装载后 isNeutral 全假 ⇒ getNumAffectedInside()=0 ⇒ block=0 不
  giveBlock。gd_core_items/Exclusive/Holdall.gd 与 oracle/Items/Exclusive/Holdall.gd 逐字一致、调用链
  Bag/Item 两侧对齐，且 gdcore 根 346 个 Holdall 事件对比除本场外全部 gd==oracle，链路无缺陷——修复面
  在数据层+工具链（assets/battle_items.json + gd_core_runtime.json 重生），不在 gd_core_items，按红线留档
  blocked。另发现 py 侧 172 个 Holdall 事件全为 0 的独立缺陷（output/oracle/align/py/）及解密 CSV shop
  列不可作真源（GDEC 加密件才是真源），均已写入留档。未改任何代码，无备份（output/_round_patches/
  np4_HOLD/ 空），gd_core_items/ 经 git diff 复核零改动。留档 output/oracle/wf_notes/np4_HOLD.md。
- **开战序位次并案（ORD1）—— 受阻留档**：三目标场维持全绿。run947_r10 的 autoRage 修复已验有效
  （idx6 RainbowPotion 选型分歧消除，首分歧从 t=0 推进到 ev52 @1.5667 棋盘捕子），本轮用 PCG32 复原
  引擎链证明台账与引擎链零缺口（autoRage 两笔=引擎位 77,78、棋盘各 tick 连续映射至 204），残点定性为
  puzzlebag 叠放格 × ChessBoard.findPieceToCapture 捕获可见性语义（oracle Inventory.filledCells 袋内归属
  需真 Godot 对跑，本卡禁跑无法下钻，§D2 留档）。顺带修 gd_core_items/Exclusive/Chess/ChessPiece.gd:66
  捕获音高域误写 (0.9,1.1)→(0.95,1.05)（Util.randPitch() 默认 variation=0.05，Util.gd:682-683；笔数同、
  仅消逐抽对位假分歧）。run1101_r18 维持数据面原判（Magitecc Armor classes 0→65，超文件面，§E 留档
  移交数据卡）。改动已回滚至 output/_round_patches/np4_ORD1/。留档 output/oracle/wf_notes/np4_ORD1.md。
- 下轮入口：①fixed 卡的同根因相邻场扩大验证 ②blocked 卡按 output/oracle/wf_notes/np4_*.md 的可能解法
  认领 ③全量 --force 刷基线待净增绿后执行。

## np5 层收口（workflow，2026-10-18）

本轮 workflow 两卡收口：数据面（D1）三处 classes 错值定谳并修复——run1347 全语料约束求解定谳
Spectral Dagger=127 唯一解、Magitecc=65 经 run1101 PM 邻域夹具独立复核成立，Shaman Mask 因真约束
2·[SD]+[SM]=2 证伪维持 4 未改，修后 Holdall 语料 172/172 全对；内核面（K1）三补丁 ①③ 按
np4_PINE/np4_ORD1 定谳落地、② 两假说经一手证据证伪免改（CoreBuff.gd 零改动），六场终验快照
3 场一致 / 3 场分歧、残点均属既有挂起类，REG 九场与全量刷基线按下轮入口执行。

- **数据面 classes 三处（D1）—— 已修复**：run1347 全语料约束求解（170 Holdall 事件修前 168 对
  2 错、唯 run1347 双侧）定谳 Spectral Dagger=127 唯一解并已改；但 np4_HOLD §3 包内清单漏了第二把
  Spectral Dagger（occ [[3,1],[4,1]] 与 Holdall 占格相交，CoreGrid 后写者胜必数入），真约束为
  2·[SD]+[SM]=2，故 Shaman Mask=127 会使 count=3≠oracle 2 而被证伪、维持 4 未改（证据冲突按卡面
  纪律不改）；Magitecc=65 经 run1101 PM 邻域夹具直读独立复核成立已改；修后语料 172/172 全对，
  REG 九场待验证方脚本执行。改动：assets/battle_items.json（Spectral Dagger classes 0→127、
  Magitecc Armor 0→65）；再生 gd_core_test/item_battle_fixture.json、assets/gd_core_runtime.json
  （各仅 2 叶 diff）。备份 output/_round_patches/np5_D1/（assets/battle_items.json、
  assets/gd_core_runtime.json、gd_core_test/LineupFixture.gd、gd_core_test/item_battle_fixture.json）。
  留档 output/oracle/wf_notes/np5_D1.md、分析脚本 output/_np5_D1_solve.py。未触碰：
  gd_core_test/oracle_align_cases.json（复核 914 场）、gd_core_test/LineupFixture.gd（再生后逐字节
  同备份）、Shaman Mask（见上）。
- **内核面三补丁（K1）—— 部分推进已保留**：①③已按 np4_PINE/np4_ORD1 定谳落地待脚本 REG 验证；
  ②经一手证据证伪 np4_MF 两假说无需改码——oracle Core/Buff.gd:164-171 为 harness 补丁版（RESCH
  判据=注册表活剩余，与 gd 现行 _timer_left 判据同构，计时器登记[0,0]致首遍重同步 grace 两侧一致），
  np3c 期杀 grace 的 B1P 同帧重启在现行同 dur 恒 KEEP 判据下结构不可达，假说 A（①' resync）违背
  drive_timers:896-901、假说 B（统一+1）违背 run688/run634 锚点。目标场状态：run947_r10 残 1 场
  分歧（Black Rook 捕子）、run1051_r6 残 1 场分歧（Echoing Battlecry）、run1101_r18 一致（ev=961），
  详见下方终验快照。改动：gd_core/CoreCharacter.gd（补丁① 延长支 _invul_instant=false 现:1494-1500；
  补丁③ autoRage pickRandomEngine 现:354-360）、gd_core_items/Exclusive/Chess/ChessPiece.gd
  （补丁③ 捕获音高 (0.95,1.05) 现:63-69）。备份 output/_round_patches/np5_K1/（CoreCharacter.gd、
  ChessPiece.gd）。留档 output/oracle/wf_notes/np5_K1.md；CoreBuff.gd 未改（② 证伪）。
- **六场终验快照（对照语料对拍，LEG_EXIT=0）**：3 场一致——run1347_r18（ev=369）、run921_r18
  （ev=795）、run1101_r18（ev=961），各 0 场分歧；3 场各残 1 场分歧——run977_r18（分歧点 G 侧事件
  Mr Struggles type=109 amount=-8，t=7.716667）、run947_r10（Black Rook type=104 amount=3，
  t=1.566667）、run1051_r6（Echoing Battlecry type=0，t=8.55）。
- 下轮入口：①仍未全绿场按 np4/np5 笔记残点认领（puzzlebag×棋盘捕子需真 Godot 对跑、PM 热度链、
  item_trace 口径）②净增绿后跑 tools/verify_oracle.py --force 全量刷基线 + aligned_set snapshot
  ③PotM 疲劳越权与激活音高幻抽两类级仍挂起。

## r38 基线刷新（2026-10-18，全量 --force 手动收割）
- **815/914 三方一致，退步 0**（上基线 r37=808）。新增绿 7：run695_r18、run1514_r18（np2 RubyChonk
  3 抽）、run1347_r18（np5 classes Spectral Dagger=127）、run921_r18（np5 补丁① _invul_instant）、
  run1101_r18（np5 classes Magitecc=65 + 补丁③ autoRage）、**run1545_r17、run962_r18（连带收割，
  归因 autoRage/_invul_instant/classes 叠加效应）**。
- 快照 output/oracle/aligned_sets/r38_l1.txt（815）；alignment.json/digest 已再生。
- 残 99 场重分簇（digest）：盲族 45（Light Goobert 36 + Burning Banner 7 + Lightning Potion 2，判死）
  | Girl Power 4（几何半定谳：grid↔tscn tile_data 坐标系） | False Life 3 | Mana Orb 3（无效化 vs 获得
  语义差，**新面**，含已判 vintage 的 run1409） | Amulet of Light 2（判死） | Chili Pepper 2 | Snowmaster
  2 | Null Blade 2（判死） | Rib Saw Blade 1（run688 out_of_stamina，**新面**） | 其余零星（含判死
  run602/run686/run697 等）。fixPlan 标签：rng-mechanism 93 / gd_core-kernel 6。
- 活跃可修红 ≈ 40（99 − 判死 61 中的现残部分）；r38 新露两面：Mana Orb 无效化语义、run688 耐力耗尽时相。

## np6 层收口（workflow，2026-10-18）

本轮 workflow 四卡收口，终态 1 fixed / 1 部分推进已保留 / 2 受阻留档：PotM 越权收编补丁核实
完整在位，三目标场复跑由红转绿＝相对 r38 基线净增绿 +3；CoreBuff 批内容四件套落地，run977_r18
首分歧自 t=7.716667 推进至 t=18.766667；棋盘捕子族两场根因均钉死于卡面文件之外（run947_r10＝
Spiked Staff has_battle_rage_effect 数据错引发的 autoRage 幻抽链位差、run1051_r6 维持
DeckofCards activate() 缩块），np4_ORD1 §D2 棋盘捕获可见性假说证伪、棋盘串行卡撤销；两新面三场
（run1083 语料陈旧、run1427 ManaOrb rng 值流静默分叉、run688 Buff 暂时栈重排边界）定性至卡外
留档。终验快照（np6v_final 定向 9 场＋REG 九场×2 腿，本轮以 tools/_probe_gd_compare.py 复跑
复核）3 场一致 / 6 场分歧，REG 两腿各 0 场分歧零回归。

- **棋盘捕子族（A1）—— 受阻留档**：两场根因均钉死但都在本卡文件面（CoreGrid/CoreItem/
  ChessBoard/Chess/*/Bag 族）之外，文件面经 oracle 真机仪器逐项核对全部逐位同构、无缺陷；
  np4_ORD1 §D2「puzzlebag 叠放格×findPieceToCapture 捕获可见性」假说证伪（filledCells/bagCells
  双侧逐位同构，gd_core/CoreGrid.gd:88-89 ≙ oracle/Core/Inventory.gd:726-727；(5,0)→White Pawn
  双侧一致），棋盘串行卡无需再立。run947_r10 ev52 真根因＝数据面：assets/battle_items.json
  Spiked Staff has_battle_rage_effect=True（fixture 同 False→真值为 False；本轮复核该文件现
  16 个 bre=true 物品、Spiked Staff 在列），oracle 引擎实测 descriptor 真值 bre=False
  isBRI=False（probe_rage.gd→rage_dump.txt；oracle/Items/Item.gd:5408-5409）⇒ oracle prepare
  的 autoRage 分支 battleRageItems 为空零消耗（oracle/Core/Character.gd:323-325），gd 却经
  gd_core/CoreCharacter.gd:347-360 pickRandomEngine 每侧多耗 1 笔引擎台账抽（共 +2 幻影）且
  多启 autoRageTimer。单点 randi() 链位实测（PCG32 复算 seed=7499306）：oracle 开 tick 前已耗
  76 笔（np4 映射误记 78＝autoRage@77,78）、tick47 末 132、tick70/93 末 181；tick94 黑方
  activePieces.shuffle（n=2 恰 1 抽）为开战以来首个对抽值敏感点——oracle 读位次 181=1620950222
  偶→swap→[Pawn,Rook]→兵先扫捕 White Pawn（=语料 ev52 type105），gd 台账读位次 183=128500293
  奇→不换序→[Rook,Pawn]→车捕（=gd ev52 type104；rng_trace.txt:646-647），双侧行为各自逐位
  复现；白方两回合因 backward-FY n=3 不动位 0 且本局面仅 White Bishop 可动而对抽值不敏感，故
  ev0..51 全同、分歧恰在 tick94 暴露。另证本二进制 Array.shuffle()=backward Fisher-Yates
  （flip⟺首抽偶，seed1..16 相关表），gd_core/CoreRng.gd:181 台账算法正确维持。补丁方案（移交）：
  ①数据卡改 assets/battle_items.json Spiked Staff has_battle_rage_effect True→False 并重生
  item_battle_fixture.json/gd_core_runtime.json（probe_rage.gd 可换 PROBE_RUN/ROUND 定谳其余
  15 个 bre=true 物品；带 BattleRage 标签 64 的 Wolf Badge/Berserker Bag/Toolbox 走
  hasBattleRageStarter 支路不受此位影响）②gd_core/CoreCharacter.gd np5_K1 补丁③保持不动
  （:353 空列表守卫与 oracle 同构，数据修后即完全正确）③预期 run947_r10 全绿，REG 九场无
  Spiked Staff（实扫）零回归。run1051_r6 ev87@8.55 不同根：阵容无任何 Chess/*、无 Puzzlebag
  （仅 Leather Bag/Fanny Pack），文件面脚本零参与；根因维持 np4 §A——gd_core_items/
  DeckofCards.gd:88 activate() 仍缩在 if not chainStarted 块内（本轮复核：现文件守卫在 :70、
  activate() 2 Tab，卡面原记 3 Tab/:79→:82 块内为旧行号，机理不变——重放路径 chainStarted
  已置位故整笔跳过），oracle/Items/DeckofCards.gd:77 为单 Tab 无条件执行，重放路径（Echoing
  repeatCombatStart→onCombatStart）整笔跳过 activate()⇒缺 Deck Activation 事件+激活音高抽⇒
  Echoing 抢位；修复＝np4 收尾#1 原样认领（activate() 出块至单 Tab），np4-r1 已验绿（ev=138）。
  以上均不在本卡允许文件面，按红线留档不硬修。改动：无（阶段1零文件面改码、零备份；git 复核
  本卡未改任何 tracked 文件）。分析产物：output/oracle/probe/np6_A1_rook/{probe_cells,
  probe_ticks,probe_randi,probe_rage,probe_shuffle}.gd + cells_dump.txt + cells_dump2.txt +
  ticks_dump.txt + rage_dump.txt + randi_{activate,t47,t70,t93}.txt。留档
  output/oracle/wf_notes/np6_A1.md。
- **CoreBuff 批内容（B1）—— 部分推进已保留**：已落地批准方案并经 diff+引用核查（_timer_e1
  共 7 处全对位、无缩进污染）。根因＝gd_core/CoreBuff.gd ①' 支以 _timer_last_dur（start 时写）
  冒充 oracle 注册表 e[1]（仅驱动遍尾写，oracle_fight.gd:897-903；停走遍只写 e[0]=-1，:884-886；
  登记 [left,left]=0，:951-968）——run977_r18 side0 同帧 [LG+7 start(4.8)→MrS+8 RESCH
  stop;start(4.8)] 链上 stint 从未被遍观测致 e[1]=0，oracle 走重同步 grace 帧（probe
  [bt-resync] old_e1=0.0000 实证）盲批弹 7.733333，gd ①' 误推 eng==e[1] 丢 grace 早弹
  7.716667。补丁四件套：:80-91 新增 _timer_e1 复刻字段+注、:508-514 resetTimersSync 重建对位
  e1=0.0/last_dur、:579-589 ①' 判据加 is_equal_approx(dur32,_timer_e1)（run727 已观测子态
  语义原样保留）、:665-671 _tick 遍尾观测写入，另 :558-561 BSCHED 探针 B1P 标签加 e1 合取
  （本轮 diff 备份↔现文件复核：6 hunk 恰覆盖上述 5 行段）。预期 side0 盲批 FIRE
  7.716667→7.733333、弹批序 MrS→LG 不变、抽序回归语料锁步——终审兑现：run977_r18 首分歧由
  t=7.716667（Mr Struggles amount=-8）推进至 ev2563 t=18.766667（G Light Goobert amount=-9
  vs O -10；卡内腿 np6v_CoreBuff批内容_r1 exit=0 与 np6v_final 复跑一致），残点转入 Buff
  暂时栈家族；REG 九场复跑 0 场分歧、零回归面兑现（运行期终审 REG 九场＋run977_r18 归脚本
  统一跑，本卡未跑）。改动：gd_core/CoreBuff.gd；备份 output/_round_patches/np6_B1/gd_core/
  CoreBuff.gd（改前原样，md5 5566899908cd28b6dff954552eb3feef 与改前工作树一致，本轮复核一致）。
  留档 output/oracle/wf_notes/np6_B1.md 已更新落地记录。
- **两新面与诊断债（C1）—— 受阻留档**：三场根因均在卡面之外。①run1083_r18 语料陈旧——现行
  oracle 探针（1058 事件，O 胜 opponent）与 gd 腿忽略 type_name 逐字节全同，「无效化 vs 获得」
  分歧不存在；语料 events.json(10-07) 早于 oracle_fight.gd(10-17 12:15)/Core/Buff.gd
  (10-17 13:42) 打桩，需脚本方重新生成该语料（终验残点 ev37 Mana Orb 缺 resisted 字段即此
  artifact）。②run1427_r12 ManaOrb 假说证伪——gd_core_items/ManaOrb.gd:22-33≡oracle/Items/
  ManaOrb.gd:28-38、rollChance（CoreItem.gd:1178≡Item.gd:4394）、BalancedRng（CoreRng.gd:
  266-361≡BalancedRandom.gd:23-55）全同构且抵抗链在场（gd 全语料 resisted 20692 vs O 20815），
  实为 rng 值流静默分叉：oracle 翻转值 P@1.0833=0.17475/0.727296、P@1.75=0.26156（平衡有效
  胜率≈1/6 故负），gd 同四位判定 负/胜/胜/负，而 e0∈[-0.2,0.2] 时同值必胜⇒gd 同位抽异值，
  t<1.0833 无事件面错位（K17 同盘）；方案＝修 gd_core_test/OracleAlignBattle.gd 诊断面
  ORACLE_ALIGN_TRACE 落盘写空障碍（K17 §六.1）后由脚本跑 run1427 逐抽对位
  np6_C1_morb3/run1427_r12/rng_log.txt 行 314-351。③run688_r10 耐力耗尽两侧同拍 @9.9333
  （type15，CoreCharacter 耐力面无缺陷），真分歧＝gd 多一发 Blind −1 timeout @9.8833（oracle
  同栈 @10.1667/@11.75 亦然）＝Buff 暂时栈定时器驱动/重排边界，即 np5_K1 §3.4 挂账机制；线索
  gd_core/CoreBuff.gd:250/:587-600/:613-618 ↔ oracle/Core/Buff.gd:164-171/:332-349，不在本卡
  文件面（np5 回归面已排除：run688 无 Chess/BattleRage 物品）。改动：无（阶段1零改码；无备份
  需还原）；探针产物 output/oracle/probe/np6_C1_morb1..3。留档 output/oracle/wf_notes/np6_C1.md。
- **PotM 越权收编（D1）—— 已修复**：批准补丁已完整在位（wf9_phantom 轮落笔），本轮逐字比对
  零偏差、无需新增改码。①吞没机制（阶段1活体 trace 定谳，本轮复验仍成立）：神谕骨架 "Combat"
  节点裸 Node2D 未挂脚本（oracle/oracle_bootstrap.gd:108；真源 Main.tscn:9685-9687 挂
  ExtResource(74)=res://Core/Combat.gd）→ oracle/Items/Exclusive/PoweroftheMoon.gd:24
  Game.combatSceneNode.advanceTime 每件 PotM 报 `SCRIPT ERROR: Invalid call. Nonexistent
  function 'advanceTime' in base 'Node2D'` 被跳过（probe 实证 output/oracle/probe/np6_D1_wf9x/，
  三目标场各 2 条，重放与语料逐事件同构：run1203_r18 双侧 1121 事件无 fatigue_start，
  run1281_r11/run1176_r11 双侧 PotM 恒 17.0167）→ oracle/Core/Combat.gd:920-921 与
  CombatTimer.gd:184-198 为语料场死代码，timeAdvance 恒 0。②补丁内容（本轮现场核对在位）：
  gd_core/CoreCombat.gd:480-481 `func advanceTime(_time: float) -> void: pass`（同位吞没，等义
  神谕 SCRIPT ERROR）；time_advance 声明 :78 后无任何写入点恒 0 → :245
  fatigue_next_tick=17-3-0=14 ≡ CombatTimer.gd:119 start(FATIGUE_TIME-3)（常量 :57-58）；
  :486 getEffectiveTime() ≡ timeAdvance=0；调用面不动：gd_core_items/Exclusive/
  PoweroftheMoon.gd:27 照常调用（git diff 确认与 HEAD 零差异）；镜像已同构：
  gd_core_py/gd_core/CoreCombat.py:511-514 同体 no-op、:274 同式；全库唯一 advanceTime 调用方
  即 PotM（本轮 grep 计数复证）。③REG 影响面：9 场 REG lineups 逐场扫描 PotM 计数全 0（阶段1
  实证）→补丁对 REG 判定面行为零改动，本轮 REG 九场复跑全绿兑现。④终验兑现：三目标场
  run1203_r18（ev=1121）/run1281_r11（ev=806）/run1176_r11（ev=1316）复跑全绿、由红转绿。
  备份快照为修复期最终态（源码零改动故与工作树一致）：output/_round_patches/np6_D1/gd_core/
  CoreCombat.gd、output/_round_patches/np6_D1/gd_core_items/Exclusive/PoweroftheMoon.gd；
  改前回滚基线＝output/_round_patches/wf9_phantom/CoreCombat.gd.bak。未触发 blocked，未写
  wf_notes/np6_D1.md。
- **终验快照（对照语料对拍，LEG_EXIT=0；本轮以 `python -X utf8 tools/_probe_gd_compare.py`
  复跑 np6v_final / np6v_CoreBuff批内容_r1 / np6v_CoreBuff批内容_reg1 / np6v_PotM越权收编_r1 /
  np6v_PotM越权收编_reg1 五腿复核）**：定向 np6v_final 9 场＝3 场一致——run1203_r18（ev=1121）、
  run1281_r11（ev=806）、run1176_r11（ev=1316）＝PotM 三目标场由红转绿（净增绿 +3）；6 场各残
  1 场分歧——run947_r10（ev52 Black Rook type104 vs 语料 Black Pawn type105，t=1.566667）、
  run977_r18（ev2563 Light Goobert amount=-9 vs -10，t=18.766667）、run1051_r6（ev87 Echoing
  Battlecry vs Deck of Cards，t=8.55）、run1083_r18（ev37 Mana Orb 缺 resisted 字段＝语料陈旧
  面）、run1427_r12（ev40 Poison Spear type108 vs Mana Orb type105，t=1.083333）、run688_r10
  （ev222 Burning Banner timeout −1 @9.883333）。REG 九场两腿（np6v_CoreBuff批内容_reg1 /
  np6v_PotM越权收编_reg1）各 0 场分歧全绿零回归。工作流原报「十场」快照：给定 7 块经复跑逐字
  复现 7/7，落盘批次实有 9 场（run947_r10/run1051_r6 两块由复跑补全）；截断头部若另含第 10 块
  不可恢复，未臆补。
- 下轮入口：①残场按 np6 笔记认领——run947_r10 数据卡（Spiked Staff bre True→False＋重生
  fixture/runtime）、run1051_r6 DeckofCards（activate() 出块至单 Tab）、run977_r18/run688_r10
  Buff 暂时栈（np6_C1 §③/np5_K1 §3.4 线索）、run1427_r12 诊断面（ORACLE_ALIGN_TRACE 写空障碍
  后逐抽对位）、run1083_r18 语料重生成 ②净增绿已到手→建议尽快 tools/verify_oracle.py --force
  刷 r39 基线 + aligned_set snapshot ③判死 61 场与 PotM 外类级挂起维持。

## np7 层收口（offpeak-29c7fa66，2026-10-19）
一句话：三卡修复（数据面 bre 批翻转 14 件+DeckofCards 出块+定向 9 场新绿，REG 全程绿零回滚）
+ 三卡受阻留档（GP 轴映射、K17 装配值流、盲批早 N tick 新类级发现）。

- 【卡1 数据面 bre 批翻转——fixed】Spiked Staff has_battle_rage_effect True→False（np6_A1 定谳）
  使 run947_r10 全绿（ev=399）后，用 probe_rage.gd 扩面审计其余 15 个 bre=true 物品的 oracle
  引擎真值：**可审计 15/15 全部 bre=False——整批翻转**（Badger Rune/Berserker Bag/Brass Knuckles/
  Chain Whip/Deer Totem/Double Axe/Dragon Claws/Dragon Set/Dragonskin Boots/Extra Angy/
  Spiked Collar/Toolbox/Wolf Badge 共 13 件一并修；Busted Blade/Dragonscale Armor 无语料场无法
  审计维持原值留档；run793 顺带证 Badger Rune isBRI=True 独立语义位存在）。7 个审计场
  （run1386/1352/753/1032/1359/793/871）定向**全部转绿**，REG 9/9 绿零回滚。夹具再生两次均
  核对 914 场无损（一次 len 顶层键误报虚惊已排除）。备份 output/_round_patches/np7_data/。
- 【卡2 DeckofCards 出块——fixed】gd_core_items/DeckofCards.gd activate() 出块至单 Tab
  （对齐 oracle/Items/DeckofCards.gd:77 无条件执行；np4_ORD1 §A 定谳）→ run1051_r6 全绿
  （ev=138）。备份 np7_deck/。
- 【卡3 Girl Power 几何——受阻留档】tscn tile_data 解码修正（collision (-1,-1)→(-1,0)、
  affected (-1,0)→(-1,1)）使四场（597/608/613/729）相位差**反向扩大**（gd 首激活更晚）⇒
  json grid 与 tscn (x,y) 存在轴交换/翻转歧义（handoff §6 早有警示）。已回滚+再生，留档
  wf_notes/np7_GP.md（含 probe 直读 getAffectedCells_tilemap 真值的绕行方案）。
- 【卡4 K17 值流——受阻留档，定位深化】run1427 首差钉在装配期 #32：oracle=(0.9,1.1) 音高 vs
  gd=多一笔 ctor(0.2,-0.2)（其后逐位同步）；Gem._ready 的 (0,10) 抽（oracle/Items/Gems/Gem.gd:23）
  盲补试验使含宝石 REG 5 场红（gd 装配 gem 链旧轮已用别的方式对齐）→ 回滚复验全绿。
  留档 wf_notes/np7_K17.md（含 probe_asm.gd 逐物 dump 方案）。
- 【卡5 Buff 家族——形态更新】run977 尾段=同刻同物弹层 -10 vs -9（纯层数语义）；run688=
  Banner 批早 3 tick。未动码。
- 【卡6 探查七场——新类级发现】FalseLife(3，排 run907)/Chili(2)/Snowmaster(2) 七场中 5 场
  gd 侧盲批（Banner/Goobert）**提前 3-7 tick 插入**（run986/1073/1167/1231/688）⇒「盲批/临时栈
  到期系统性早 N tick」横跨主簇残余与三新簇，疑为下一统一类级根因（np5_K1 的"+1 tick"证伪
  不排除 3-7 tick 变量机制）。留档 wf_notes/np7_explore.md（双锚 dump 方案+r23 反例锚警示）。
- 【净增绿清点】定向新绿 9 场：run947_r10、run1051_r6 + bre 批 7 场（run1386_r17/run1352_r13/
  run753_r15/run1032_r2/run1359_r10/run793_r11/run871_r14）；连同 np6 的 PotM 3 场（run1203/
  run1281/run1176），r38=815 → 预期 ≈827（待全量确认；bre 批翻转还可能连带收割更多含这些物品
  的场）。
- 下轮入口：①【盲批早 N tick 类级攻坚】（np7_explore 双锚方案，CoreBuff 深水区）②GP 轴映射
  probe 绕行 ③K17 probe_asm ④bre 连带收割全量确认（建议直接 --force 刷 r39）⑤判死 61 场维持。

## np8 轮1：r39 基线刷新（2026-10-19，全量 --force）
- **825/914，退步 0**（r38=815，+10）。快照 aligned_sets/r39_l1.txt；digest 已再生。
- 新增 10：run947_r10、run1051_r6（np7 bre+Deck）+ **run1427_r12、run1441_r11、run1499_r15
  （np8 轮3 connector 数据修复）** + 连带 5：run1172_r18、run1534_r15、run1536_r15、run1540_r18、
  run939_r18。
- bre 批 7 场与 PotM 3 场在 r38 即已绿（前者因 r38 跑时 np7 数据已落树？——核对：r38 发射于 np7
  完成后，bre 翻转与 Deck 出块已并入 r38）。
- ⚠过程事故与处置：轮3 期间在全量跑中改了 battle_items.json+再生夹具（违反"期间不改"红线），
  gdcore 腿 482 场混新旧数据 ⇒ 判废杀进程重发射，干净跑得到本数。教训已记。

## np8 轮3-5 与总收口（offpeak-68d991c1，2026-10-19）
【轮3 K17 破案——fixed +3 直绿】probe_asm.gd 逐物水位钉死 run1427 装配 #32=卡牌 Connector：
oracle CardConnector._ready（Items/Animations/CardConnector.gd:11）每卡恒 1 抽 (0.9,1.1)，gd 以
descriptor.connectorReadyRoll 数据标志补抽（CoreItem.gd:825）——**battle_items.json 两卡标志错**
（White-Eyes Blue Dragon=False→True、The Lovers=False→True；tscn CardConnector 实证；Ace/Joker/
Deck=True 佐证）。修后 run1427_r12/run1441_r11/run1499_r15 三场全绿 + run1514/run695 卡牌 REG 场
保持绿 + REG 九场全绿零回滚。np4-np7 四轮追凶的"装配期音高缺笔"（K17/1441/1499/1051 位次）
就此闭案。备份 np7_K17 增补+数据在树。
【轮4 GP——受阻留档（真值钉死）】probe_gp.gd 三 rot 场实测：oracle getAffectedCells_tilemap
恒返回同一原始 15 格（rot=0/90/180 三场同集）且=battle_items.json 现值（np7 的 tscn 轴解码错，
回滚正确=数据本来对）；旋转由 to_global 节点变换承担、gd 只做排序不旋转——但顺/逆两向旋转
试验（np8_gprot 开关补丁）均使分歧提前 ⇒ 旋转中心非格原点（collisionMap.global_position 偏移）
或平移系另有 1 格差（r36"加 [3,0]"暗示后者）。补丁已回滚，留档 np8_gp.md（r36 锚起步方案）。
【轮5 浅探】run1303_r18 定性=overheal 链值差族（Devouring Sphere heal @1.3667 触发 False Life
giveMaxHealth 双笔，gd 缺第二笔；脚本双源逐字同构 ⇒ 值流上游族）；run1126_r18 同族嫌疑
（Lightning Staff dmg 11 早期窗）。留档 np8_bl.md/np7_explore.md。
【r39 收割】见「r39 基线刷新」节：825/914，+10 退步 0（947/1051 + 1427/1441/1499 + 连带
1172/1534/1536/1540/939）。
【np8 总账】+10 净绿（815→825）；两大悬案闭案（K17 装配值流、np4"音高缺笔"）；GP 真值钉死；
盲批早 N tick 机制全景钉死（np8_bl.md）但未动码。
【剩余活跃 ≈24 场】盲批早 N tick 族 ~9（双锚方案在档）| GP 4（r36 锚方案）| FalseLife/Chili/
Snow/ManaOrb/NullBlade 残簇 ~11（值流上游族）。判死 61 维持。理论可达 ≈849。
【下轮入口】①盲批早 N tick 类级（np8_bl 三步法）②GP r36 锚组合穷举 ③overheal 值流族
（1303/1126）④全量确认连带收割（可直接刷 r40）。
## np9 层收口（workflow，2026-10-19）
一句话：本轮三卡全部受阻留档、代码面零改动（阶段1 禁改已守）——盲批早 N tick 定谳为
【语料↔oracle 树代际漂移】类级根因（现行 oracle 树本身就产出 gd 的"提前"盲批，六场 probe
与 gd 逐事件全等实证）；GP 四场首分歧根因钉死为配方类继承（calcClassAvailability）从未落库
的数据面缺口（旋转假设消解：affected 格集两侧逐格相同）；overheal 值流族两目标场语料笔数差
=冻结语料生成期跨批状态产物，gd 与干净神谕逐抽逐事件全同，判不可修。

- 【卡1 盲批早 N tick 类级——受阻留档（根因定谳=语料↔oracle 树代际漂移，台账 K01/K03 家族）】
  根因不在文件面（CoreBuff.gd/CoreTimer.gd 本轮零改动点）。核心证据（本轮全部实跑）：
  ① 五目标场+旁证场 run977_r18 的 gd trace（output/oracle/align/gdcore/*，2026-10-19
  21:29-21:57，与 np8_a/run986 events 全等已复核=现行码）vs 冻结语料首分歧恰在各场盲批位：
  run986 idx271（gd t=6.5333 Blind TO -1 vs 语料 FalseLife heal 6.65）、run688 idx222
  （9.8833 vs 同批 10.1667）、run1073 idx654、run1167 idx531（LG -7）、run1231 idx195
  （LG -7）、run977 idx2563（同刻 -9 vs -10，不可见批布局差）。
  ② 决定性反证：按分析期特权跑 oracle probe 重放（ORACLE_FIGHTS_ROOT=output/oracle/probe/
  np9_L1_*，ORACLE_ONLY_CASES=<场>，ORACLE_DEBUG 有/无双跑），六场 probe 事件流与 gd 逐事件
  全等（键 type/timestamp/origin/params 首分歧=None，全长 4023/958/1532/4016/3070/6366），
  而 probe-vs-语料首分歧=271/222/654/531/195/2563——即【现行 oracle 树本身就产出 gd 的
  "提前"盲批】，"提前"只相对冻结语料成立。
  ③ 漂移时间线：语料冻结 2026-10-07 02:36，而 oracle/Utility/Util.gd（10-10 14:51）、
  oracle/oracle_fight.gd（10-17 12:15）、oracle/Core/Buff.gd（10-17 13:42）均晚于冻结；
  RESCH 判据被改桩：现行 oracle/Core/Buff.gd:164-171 用 Util.oracleTimeLeft
  （oracle/Utility/Util.gd:807-810=注册表 e[0] 活剩余），真源 decompiled_full/Core/Buff.gd:164
  是 duration<timer.get_time_left()；np5_K1.md:56-68 记载 gd 随即对齐该桩
  （gd_core/CoreBuff.gd:261）。先例在档：A1CRN.md K04-B（run688 瞬弹 vs run1038 存活 33 tick，
  已判"现行树无法取证不硬修"移交 K01）、GEN1.md:35（run895_r10 同族）、A3BLD.md:89
  （corpus 时代 Buff.gd 备份均=现行）。
  【补丁方案】文件面无解——任何按语料"修提前"的 CoreBuff.gd 单笔都会破坏已实证的 gd↔oracle
  六场全等与 REG 现状。移交 K01 两路：a) 语料代 oracle 语义考古（首选验证 RESCH 代际差：按
  真源+冻结引擎离线重放六场看能否复现语料盲批序列）；b) 语料以现行树再生成（红线内本轮未动）。
  已排除：ORACLE_DEBUG 改行为（双跑全等）、gd trace 陈旧。未竟如实记录：全量 stdout 48845 条
  node_removed "Method not found" 派发错误来源未定谳（最小复现 probe_conn.gd 证明连接机制
  可用；不影响结论，结论只建立在 events.json 全等上）；自建 python 批机制模拟粒度不足不采信。
  gd 腿（REG 九场）未跑（禁跑已守）。改动：代码面零改动。仅新增 probe 产物 output/oracle/
  probe/np9_L1_986/（ORACLE_DEBUG=1 stdout+events+probe_conn.gd）、np9_L1_986_pl/（无 debug
  复核）、np9_L1_run688_r10/、np9_L1_run1073_r12/、np9_L1_run1167_r18/、np9_L1_run1231_r18/、
  np9_L1_977/（各 events+stdout）及留档 output/oracle/wf_notes/np9_L1.md；语料
  output/oracle/fights/ 与 oracle/ 树只读未动，git 零操作。
- 【卡2 GP 旋转语义——受阻留档（根因=配方类继承从未落库，数据面）】四场 GP 首分歧根因=
  calcClassAvailability 配方类继承从未落库，不是旋转语义；根因在数据面（assets/
  battle_items.json）→ 越出本卡文件面 → blocked，补丁方案已写进 output/oracle/wf_notes/
  np9_L2.md。
  【旋转假设消解】oracle probe（PROBE_RUN=608/597/613/729，probe_gp_np9.gd）实测 GP
  getAffectedCellsInInventory 库内集与 gd_core_test/oracle_align_cases.json 夹具 affected
  四场逐格相同（diff=∅），rot0/90/270 全对上（613 越界格 (6,-1)/(9,3) 两侧同样原样保留）。
  np8 遗留"15v16 之谜"：tilemap 原始 15 格是本地系，库内集=经 placement_of
  （tools/gen_lineup_fixture.py:327-358，-min 归一化恰等价 oracle Item.gd:1040-1047
  to_global+CollisionMap(40,40) 偏移的换算）已变换的同一集合，r36 的"加[3,0]"缺口已被现行
  夹具吸收；np8 轮 4 旋转试验劣化正因为格集本就对。打法②穷举不需要做。
  【根因链】GP.onPrepare addSpeed(speed×getNumDistinctAffectedItems)
  （oracle/Items/Exclusive/GirlPower.gd:11，canAfect=isClassItem）。oracle 运行时 classes 经
  oracle/Items/ItemDescriptor.gd:180-202 calcClassAvailability（配方 recipeClasses=Neutral
  逐成分 &= 再 classes |= recipeClasses，调用点 oracle/Sheets/ItemBook.gd:1141+:1305-1320
  按合成深度序→传递链成立）折算；gd 无此物：gd_core/CoreItemData.gd:326 直读原值、:226-228
  isClassItem 判原始值；py 同构 gd_core_py/gd_core/CoreItemData.py:316-324。四场差集类物品
  （oracle CLS 实测 vs 夹具）：Strong Vampiric Potion 2v0（608/597）、Steel Dragon 4v0 与
  Whetstone3 4v0（613）、Vampiric Collar 1v0（729）→ nAff 3v2/4v3/4v2/6v5 → 首激活
  7/(1+0.35n) 全部命中实测（608 idx147 oracle 3.4833 vs gd 4.2；597 idx101 2.7667v3.2167；
  613 idx85 2.8667v4.05；729 idx30 2.2167v2.5）。
  【病灶与最小补丁】assets/battle_items.json 相关 items classes=0（HEAD 亦 0→继承轮从未落库）；
  tools/enrich_classes.py:65-124 已实现同款不动点但从未生效。最小修=仅对当前库跑
  apply_recipe_inheritance 不动点（离线模拟 2 轮收敛恰 25 件，四场涉及 4 件值与 oracle probe
  实测逐一吻合），禁整库重跑 enrich（--check 实测 CSV 基座漂移 231+继承/gate 256 件，爆炸
  半径过大）；随后重生成 gd_core_runtime.json（tools/gen_gd_core_data.py）与
  item_battle_fixture.json/oracle_align_cases.json（tools/gen_fixture_from_lineup.py，
  test+probe 两份），core/装配层零改动。REG 安全性：REG 九场现绿 ⇒ 25 件 class 状态在九场内
  无消费点（有则早已红）⇒ 只加位继承不可能破 REG；目标场修 GP 后可能出现更晚分歧（其他
  class 消费者），属真值前移，probe 仪器可复用续查。验证=REG 九场（脚本腿）+四目标场三方
  逐行比对。改动：产线零改动。新增产物仅：output/oracle/probe/np9_L2/（probe_gp_np9.gd
  仪器=模板 np8_K17/probe_gp.gd 加库内 affected/nAff/classes dump；gp_608_oracle*.txt、
  gp_597_oracle.txt、gp_613_oracle.txt、gp_729_oracle.txt 四场 oracle 真值；gd608_base/、
  gd3_base/ 为 gd 隔离工程现跑 events.json）+ output/oracle/wf_notes/np9_L2.md 留档
  （blocked 契约已满足）。oracle/ 与 output/oracle/fights/ 只读未动；REG 腿未跑；隔离工程
  gd_core_probe 仅运行未改（与产线 diff=38 行且全为 np2/np3 trace 写盘差异，place_one/
  affected 通路逐行核对一致）。
- 【卡3 overheal 值流族——受阻留档（判不可修=语料生成期批次状态产物）】根因不在 gd_core
  文件面：两目标场的语料笔数差是冻结语料生成期批次状态产物，gd_core 现行为与干净神谕逐抽
  逐事件全同。
  【证据】① 语义澄清：type=19 是 TemporaryMaxHealth（gd_core/CoreConst.gd EventType 枚举），
  非 heal；分歧笔=FalseLife.onOverheal→giveMaxHealth 的过疗 TMH（oracle/Items/Item.gd:
  4222-4227 ↔ gd_core/CoreItem.gd:2055-2072 同构）。
  ② 语料普查 920 场：159 场含 FL 过疗 TMH，其中玩家侧单笔 150 场、玩家侧双笔仅 5 场
  （run1125_r18/run1175_r11/run1303_r18/run846_r11/run906_r18）——同一代码路径语料内部
  自相矛盾 150:5，双笔非原版语义。
  ③ 本轮 probe 干净复跑（同 seed 同 fights.json，ORACLE_FIGHTS_ROOT=output/oracle/probe/
  np9_L3_fl）：run1303_r18 复跑 2687 事件 ev6=DS 激活（单笔），与既有 gd 腿产物
  output/oracle/align/np8_1303/run1303_r18/events.json 2687/2687 事件零语义差；run1126_r5
  复跑 92 事件与 output/oracle/align/gdcore/run1126_r5/events.json 92/92 零差，语料仅
  88 事件（ev22 多一笔 TMH=2）。
  ④ 本卡指定检查已跑：python -X utf8 tools/_probe_draw_diff.py <probe rng_log>
  <gd rng_trace> → oracle 11632 抽 vs gd 11632 抽，前 11632 抽完全一致——heal→overheal
  链上游无任何值差，本卡"治疗量/过疗阈值 rng 差"假设证伪。
  ⑤ 语料与 probe 的 rng_state.txt 逐字节一致（run1303 seed=-8390059292541597435
  state=2110013093896508288），同链状态不同行为 ⇒ 语料额外事件来自链外隐藏状态（角色
  curHealth/temporaryMaxHealth/连接表，均无事件面）；run1126 probe rng_log 第 205/209 行
  （t=1.0 Regen 治疗）后无 randInBox 标签对 ⇒ 干净局玩家 t=1.0 缺血≥2，语料却近乎满血
  （+≥2 无事件血量差进场）。
  【代码面排除】heal/派发/连接/FL 四面双侧逐字同构：oracle/Core/Character.gd:739-772
  （765 单发点）↔ gd_core/CoreCharacter.gd:830-871（865 单发点）；oracle/Utility/EventBus.gd:
  98-116 ↔ gd_core/CoreEventBus.gd:121-144；oracle/Items/Exclusive/FalseLife.gd:11-21 ↔
  gd_core_items/Exclusive/FalseLife.gd:12-24。
  【为何不可修】复现 run1303 需玩家侧 character_overhealed 无条件双派发、复现 run1126 需
  玩家开局凭空+≥2 血——都会污染语料内 150 场单笔对局与 REG，且逐场独立重放的内核无任何
  逐场输入能区分这 5+1 场（rng_state 同构），判据不放宽前提下无可达补丁。
  【建议（超出本卡权限）】用当前 oracle 树重生成上述 5 场语料（run1126_r5 一并复核）或将
  该批场移出 REG 并留档；语料 events.json 落盘 2026-10-07 05:10，当前树复跑即不复现，属
  生成期跨批状态/修订漂移。STACKTRACE 列为空（该 Godot 构建 get_stack() 返 null），逐抽
  调用栈未取得，机制链靠事件 parent/amount 算术+rng_log 抽型窗口钉死，不影响结论。
  改动：无（阶段1 只做离线分析+probe 对跑，未改任何代码文件，无需备份）。留档已写
  output/oracle/wf_notes/np9_L3.md；probe 产物仅落 output/oracle/probe/np9_L3_fl/。

【r40 刷基线】[r40-force] exit=0，但输出含 traceback：tools/verify_oracle.py:119 gen_fixtures
→ tools/gen_fixture_from_lineup.py:386 oracle_mode → OSError [Errno 22] Invalid argument
（gd_core_test\oracle_align_cases.json）——exit=0 与 traceback 并存，未定谳，如实记录。
快照对比 [r40-snap] exit=0：825 场 → output/oracle/aligned_sets/r40_l1.txt；r40 对比 r39：
新增 0、退步 0（与 r39 基线 825 持平）。

【下轮入口】①未全绿场按 np9 笔记残点认领（wf_notes/np9_L1.md 移交 K01 语料代 oracle 语义
考古或语料再生成 / np9_L2.md GP 最小修 apply_recipe_inheritance 不动点 / np9_L3.md
overheal 5+1 场语料重生成或移出 REG——均涉越卡面/授权，待定）②判死 61 场与 run1083
（语料重生成待用户决策）维持。

## np10 层收口（workflow，2026-10-19）
一句话：np9_L2 遗留的配方类继承（calcClassAvailability）数据面缺口本轮落库并全链再生验证——
恰 25 件、四件已知值精确命中、三张派生表与 probe 副本仅 classes 随动、oracle cases 914 场零
漂移；r40 OSError[Errno 22] 定谳为运行器尾随 \r 传参并入口最小修复；GP 四场由 r41 全量基线
直绿收口（829/914，新增恰 4、退步 0）。

- 【卡 配方类继承落库——已修复】①assets/battle_items.json 只跑
  tools/enrich_classes.py::apply_recipe_inheritance 不动点（驱动
  output/_round_patches/np10_data/apply_inheritance.py，未碰 CSV 重解析分支）：**恰 25 件
  classes 0→非零**（对备份 diff 恰 25 行、其余 493 件整 item 全等），四件已知值精确命中
  （Strong Vampiric Potion=2、Steel Dragon=4、Whetstone3=4、Vampiric Collar=1）。
- 【派生表连锁再生——仅 classes 随动】②assets/gd_core_runtime.json（gen_gd_core_data.py
  PASS）与 gd_core_test/item_battle_fixture.json（gen_lineup_fixture.py）再生：结构化 diff
  各恰 **24 处 classes（=25−Coins，Coins 无转译脚本不在 517 表内）**零其他差异；③
  gd_core_test/LineupFixture.gd 连坐恰 1 行（truth lineups 含 Holy Collar→嵌入 descr classes
  0→1，备份回放法量化、文件面外如实留档，回滚件 LineupFixture.gd.pre 在案）；④
  gd_core_test/oracle_align_cases.json 按基线 914 场再生（verify_oracle select_cases+
  gen_fixtures 同源路径）：**内容零差异、test=probe 逐字节一致**；⑤gd_core_probe 两份夹具
  同步（cmp 一致、四件已知值命中）。
- 【r40 OSError 定谳+最小修复】⑥tools/gen_fixture_from_lineup.py::oracle_mode 入口 6 行
  strip 修复：r40 [Errno 22] 定谳=运行器传参尾随 \r/控制字符（本环境 io.open 同款实证复现
  同签名、干净路径恒 OK），CLI 尾随 \r 端到端验证 exit=0 落盘 scratch。
- 【语料漂移留档】select_cases 现返回 **917 场**（基线 914），新增 run626_r6/run1294_r6/
  run1445_r18 三场未并入夹具、待后续刷基线吸收；留档 output/oracle/wf_notes/np10_data.md。
- 【纪律与备份】gd 验证腿（GP 四场+REG 九场）按纪律未跑、由 r41 全量基线代收（见下）；
  oracle/fights 与 oracle/ 只读未动；gd_core/ 与 gd_core_items/ 零改动；未 commit/push。
  备份：output/_round_patches/np10_data/ 六表 *.bak（battle_items/gd_core_runtime/
  gd_core_test 两夹具/gd_core_probe 两夹具）+ LineupFixture.gd.pre/.new、
  battle_items.json.new 回放件 + apply_inheritance.py/regen_oracle_cases.py/verify_all.py/
  scratch/。

【r41 刷基线】[r41-force] exit=0：**829/914 三方一致**（r40=825，+4/退步 0）——三方一致
829、oracle≠gdcore 84（其中 py 分歧 1）、[rng-mechanism] 79 场（首例 run602_r14）、
[gd_core-kernel] 6 场（首例 run697_r15）；alignment.json → output/oracle/alignment.json。
快照 [r41-snap] exit=0，829 场 → output/oracle/aligned_sets/r41_l1.txt；r41 对比 r40：**新增
恰 4=GP 四场**（run597_r18/run608_r18/run613_r18/run729_r14，np9_L2 预言场全数兑现）、
退步 0。

【下轮入口】①连带收割场若出现类级新簇按 digest 认领 ②判死 61+语料漂移族（盲批 5+overheal
5，均待用户决策语料重生成）维持。

### np10 终验补充（2026-10-19，主线复跑）
- **GP 四场全绿确认**：run597_r18（ev=1216）/run608_r18（ev=1309）/run613_r18（ev=570）/
  run729_r14（ev=507）——Girl Power 簇四场闭案（配方类继承 25 件落库）。
- **REG 九场复跑全绿零回滚**。
- **r41=829/914（r40 825 → +4 恰=GP 四场，退步 0）**；快照 r41_l1.txt；digest 再生：
  Girl Power 簇从分簇中消失，残簇=盲族判死域（LG37/Banner7/Lightning2）+ 值流族
  （FalseLife3/AoL2/Chili2/ManaOrb2/Snowmaster2，均已定谳语料漂移交接用户决策）。
- **np10 附带修**：gen_fixture_from_lineup.py oracle_mode 尾随 \r 传参 OSError 修复
  （r40 缺陷定谳）；语料漂移新发现：select_cases 现返回 917 场（+run626_r6/run1294_r6/
  run1445_r18 三场未并入语料，待下轮刷基线吸收）。
- **终局格局**：829/914。红 85 = 判死 61 + 语料漂移族 ~10（盲批 5/overheal 5，待决策）+
  未探零星 ~14。全部剩余场要么判死/待决策，要么属已定谳语料代际漂移——**模拟器代码面
  可修项已清零**；若要 914 需语料层决策（重生成/考古/事件重放三选一）。

## r42 基线刷新（语料定向重录，np11 阶段1-3，2026-10-19）
- **879/914（r41 829 → +50，退步 0）**。快照 r42_l1.txt；digest 再生。
- 重录：85 红场+3 新场（新场无 fights.json 种子无法生成夹具，移档 fights_pre_r42/ 保持 914 口径）；
  旧录音全部移档 fights_pre_r42/ 留档（88+3 目录）；重录 driver 幂等续跑（round1 批进程一次卡死
  被杀后 round2 自动补完），917→914 场全落盘零缺失，timeout 场带截断 events（M12 语义）。
- 残 35 红全为 gd 真缺陷（语料已=现行树语义）。分簇：LightGoobert 9 | length 类 6（timeout 截断
  差）| FalseLife TMH 2+1 | Snowmaster 2 | 零星 15（fatigue/RibSaw/HolySpear/SpicyBanana/
  Prismatic/Blueberries/FlameWhip 等）。进入阶段4 修复循环。

### np11 阶段4 循环1（length 类，2026-10-19）
- length 6 场=重录墙钟早断（非 gd 缺陷）→ 低负载逐场重冲（np11_lenretry driver，每场 ≤3 试冲
  事件闸）：run825_r18（18006）/run1049_r18（10177）/run1168_r18（2448）三场恰对位 gd 事件数
  **转绿**；run906_r18/run1125_r18/run1409_r18 冲到 2500x 事件闸但对拍仍红——真 gd 值差/
  序差（Eggscalibur dmg 12v11@1.02、Amulet of Agility vs Chili 序@1.25、Mana Orb vs AoL
  序@1.03）。净 +3（879→882 待全量确认）。

### np11 阶段4 循环2（LightGoobert 簇形态，2026-10-19）
- LG 簇 7 场（702/717/971/1132/1357/1361/1492-LP）形态统一：**新语料的 LG/LP 盲批（-7/-4/-10）
  在 gd 侧缺失或更晚**——与旧语料时代的「gd 提前」正好反向（新语料=现行树，gd 现行为缺批端）。
  疑点：现行树 Buff.gd:164-171 的 RESCH 注册表判据在 gd 侧的对应（gd_core/CoreBuff.gd:261 随
  np5_K1 对齐桩版）与真源 decompiled_full/Core/Buff.gd:164（duration<timer.get_time_left()）
  的差异面——重录后这批场首现「gd 少弹批」。逐抽打法同 np9_L1（BSCHED vs 新语料事件按 origin
  过滤对表）。
- 其余：run697=Holy Spear 净化 -2 差；run844/run1018=早期窗值差（Spicy Banana heal 3、
  Flame Whip dmg 9）；run906/1125/1409=见循环 1。
- **净战果：879→882（待全量确认）**。阶段4 未完——下轮从 LG 簇 7 场逐抽开卡（np11_lg scratch
  已备 10 场 gd 腿）。

## np12 层收口（workflow，2026-10-19）
一句话：本轮三卡全部受阻留档，产线代码与语料零改动（阶段 1 禁改令已守）——盲批序列族十场三方对表（新语料 vs gd 腿 vs oracle 单场 probe 重放）定谳：八场属录制 harness 批量语境偏差（probe 与 gd 逐事件全等），run1022 是唯一 gd 真缺一笔但其根源为 oracle 侧不存在于事件流的隐形一层状态、逐场输入无法复原，run1371 为 harness 语境级联，gd 面整体无解；物品值差族五场二分：run906/run1125 为 gd 真缺陷（run906 根因已钉死并给出补丁方案，run1125 现象面已钉但 oracle 双退机制未闭、禁盲改），run844/run1018/run1409 语料失效（含幽灵物品），无需改码；零星残场 12 场分诊为一绿（run1049）+ 七场语料孤例不可修（907/1363/1410/696/1357/913/1361）+ 三场真缺陷移交 CoreBuff 滞留计时器（989/1444/1132 合并一案）+ run602 定位于 CoreTimer/changeTimer。

- 【卡1 盲批序列族——受阻留档（判据：修 gd 追语料=打破已证 gd↔oracle-fresh 全等（np9_L1 加本轮 9/10 场）与 REG 现状，文件面无解）】
  语料重录（10-19 18:39-21:35 共 85 场，_np11_rebatch.sh 87 场单进程链 CHUNK=0）之后，仍有 39/85 场与当日再生的 gd 腿（align/gdcore 全 914 场 20:00-20:31，数据同代 19:58/20:00）首分歧，十场目标全部在列。三方对表核心证据如下。
  ① 8/10 场 probe==gd 逐事件全等：np9_L1 已证 run986@271、run688@222、run1073、run1167@531、run1231@195、run977@2563，本轮新证 run697_r15（615/615 全等）、run1492_r18（1159/1159 全等）。这八场的语料分歧（含 986/688/1167/1231 与旧语料同位同形=重录复现旧形态，以及 697 同刻净化弹序倒、1492 同刻批拆分 -9v-10）纯属录制 harness 批量语境偏差，责任不在 gd。
  ② run1022_r18 是唯一 gd 真缺一笔：probe（3915 条）与语料（3905 条）同有 Banner Blind TO -1 @13.0333 tgt=0（idx1386），gd（3910 条）无此弹。深挖结论：oracle Buff.gd 语义批次模拟器复现全部可见弹 15/15，且与 gd 的 BSCHED 真值逐批全同（np12_L1_gd1022_bsched/rng_trace.txt 行 10494-10500：@12.8 tos 十批全同、POP idx0、REARM delay=1.05 next=2）；oracle 仪器（np12_L1_1022_dbg stdout，U.time−47.817==combatTime 恒等映射）实证盲批计时器 @@1569 于 12.8 后 0.2333s（13.0333）多发一发。全树无 bt-resync（changeTimer 调用点仅 Character.gd:1048、Combat.gd:921-924，均不触盲）⇒ 唯一自洽解=oracle 侧 Shelly -5@9.2833 被永久栈全额吸收（隐形一层 null-item perm，或批 timeout 读数 +1tick：13.0167→13.0333），未拆 13.0333 批 ⇒ @12.8 REARM earliest=13.0333、delay=0.2333。该隐形状态不存在于事件流，gd 逐场输入无法复原 ⇒ gd 面不可修。
  ③ run1371 的盲批差@3665（Regen TO -1v-2）是级联：真首歧在 idx51 Dragon Knight 伤害 probe=9 vs gd=语料=8（harness 语境改隐形链消耗，此场 gd 反与批量语境同侧）。
  【旁证移交】np9_L3 跨场残留假说实锤：run1126_r5/run1125_r18/run906_r18 重录后仍带双笔 TMH 伪影（co=88/25006/25016）；另有非盲批三族首歧供他卡认领——棋子装配格位（1114/1349/1178/1375）、GemSocketN 身份（1175/1220/665/686/989）、伤害掷点（602/1363/906）。
  【建议】盲批族 87 场改单场单进程语义重出语料（8/10 预期直接收敛）；oracle_fight.gd 加 tos/REARM dump 仪器定谳 1022 隐形一层后再单场重录；gd 不动。
  改动与产物：产线零改动。本卡唯一落盘 output/oracle/wf_notes/np12_L1.md（按卡要求留档）；产物仅 output/oracle/probe/ 下 np12_L1_run697_r15/、np12_L1_run1492_r18/、np12_L1_run1022_r18/、np12_L1_run1371_r18/、np12_L1_1022_dbg/（ORACLE_DEBUG=1 仪器）、np12_L1_gd1022_bsched/（gd align TRACE 分析腿，循 np9_L2 隔离工程先例，非 REG 腿）。语料与 oracle 树只读未动，REG 未跑（由脚本统一跑）。
- 【卡2 物品值差族——受阻留档（卡面前提「语料已重录=现行树语义」仅对 run906/run1125 成立，其余三场语料失效）】
  五场三方对位（C=语料 events，P=现树 oracle 重放，G=np11 gd trace），首分歧全表（实测）：run906_r18 为 C-vs-P=idx219（早期窗一致）/P-vs-G=idx6/C-vs-G=idx6 ⇒ gd 真缺陷；run1125_r18 为 48/48/49 ⇒ gd 真缺陷；run844_r11 为 34/1198（t=18.8，超出本轮 t<1.3 窗）/34 ⇒ 语料失效；run1018_r11 为 22/None（P 与 G 全 fight 逐位一致）/22 ⇒ 语料失效；run1409_r18 为 25/None/25 ⇒ 语料失效。
  【语料失效实证】run844 语料 events 自 idx34 起出现幽灵物品 Spicy Banana @0,1（64 条）与 Pine Protector @3,1（36 条），但语料自身 lineups.json 的 (0,1) 是 Pineapple、(3,1) 无物品；oracle 装配面 probe（probe_np12.gd → asm_dump.txt）实测库存无 Spicy Banana、Pine Protector 仅 @(2,2)；ItemData.csv 无任何配方产出 Spicy Banana（仅 Spiked Shield 行含 Pineapple>Pine Protector，Banana 一系只有 Mana Crystal*>Mananana）；现树重放该窗为 Flame Whip 攻击，与 gd 逐位一致到 idx1198。run1018 语料 idx22 是 Flame Whip DealDamage 9，现树重放为 CriticalDamage 22（与 gd 全同），语料幽灵（Amulet of Light @6,2、Pine Protector @0,4、Amulet of Agility @8,2）均不在装配库存。重放确定性已排除抖动解释：run1125 两次独立重放（ORACLE_DEBUG 与 ORACLE_STACKTRACE）事件前缀逐位一致（first_diff=None；总条数差系 oracle_fight.gd:745-752 的 60s 墙钟闸/25000 事件闸截断点不同）。语料 mtime（10-20 18:34~21:35）与 oracle 树/db mtime（10-06~10-17）对不上生成批次，语料由哪次运行生成无法在本阶段查明，且语料本轮只读 ⇒ 这三场按卡面判据不可修也无需改码，留档跳过。
  【run906 根因·已钉】现象为玩家 Eggscalibur @1.016667 伤害 oracle/corpus=12 vs gd=11（对手 11 vs 12 反接），Mana Orb 首 proc @5,5 vs @3,5。逐抽对位（oracle rng_log vs gd rng_trace，rng 态注入后首失配）：玩家蛋首攻表现层块 oracle 13 抽 vs gd 18 抽——oracle 只耗 playAttackAnimation 默认实参 (100,160) 即闩死跳过本体，gd 多跑本体 5 抽（(0.9,1.1)×2+pick(0,2)+(0.8,1.2)+pick(0,2)），链移位后伤害 roll 15→11 vs 16→12、Mana Orb 序翻转。根因：oracle/Core/Character.gd:446-462 旗标复位仅靠 attackMovingBack 的 tween 回调（受控神谕阻塞循环不推进 ⇒ 闩死），叠加 oracle_fight.gd:306 先跑同种子暖场 run_case(cases[0],true)，且 G.PLAYER 节点跨场复用（oracle_fight.gd:570-577，仅职业切换才重建）、G.OPPONENT 每场新建（:610-618）⇒ 真场开局玩家旗标=暖场残留 true、对手=false（实测：oracle 对手首攻 seg9 反而全本体）。gd_core/CoreCharacter.gd:513-527 逐抽同构，但 attack_moving_forward 每场新建恒 false，无玩家开局即闩等价初始化（:484-495 注释已记录闩死约定）。补丁方案（阶段2）：A=gd_core_probe/OracleAlignBattle.gd 装配后置 player 侧 attack_moving_forward=true（最贴 harness，但该文件不在本轮允许改面）；B=gd_core/CoreCharacter.gd 按 playerId 初始化（player=true/opponent=false，在我可改面，属约定级补丁，须 REG 九场全绿才保留）；两者都只影响玩家首攻一次 +5 抽链位。
  【run1125 根因·现象面已钉、oracle 内部机制未闭】idx47-50@1.25：C=-11→+3→+3→Heat1；P=-11→+2→+3→Heat1（两次重放一致）；G=-11→+3→Heat2（单退；heat 2v1 是退回笔数差使 Chili 的 Owl 放大 roll 从不同链位取值，CoreBuff.gd:169-176）。退回算法双源同文（oracle/Items/Exclusive/AmuletofAgility.gd 与 gd_core_items/Exclusive/AmuletofAgility.gd 的 onBuffChanged：usedStacks+=used*refund; toRefund=int(round(...))），refund=0.25 实测，单笔 -11、初值 0 ⇒ 首退必为 round(2.75)=3（gd 与语料一致）；oracle 的 +2/+3 数学上要求 usedStacks[Mana] 事前∈(-1.25,-0.25)，但 P 流 idx48 前无任何 Amulet 退回事件。连接面已排除双连（装配 probe CONN dump：character_mana_changed n=3=[onManaChanged,onManaChanged,onBuffChanged]，onBuffChanged 仅 1 连）；单 emit 面已核（oracle/Core/Buff.gd:292-320 与 gd_core/CoreBuff.gd:398-432 同构、Character.gd:1287-1290 useMana 单调用、EventBus.gd:56-77 遍历期数组不增长）——静态读码未找到 oracle 第二交付点，rng_log SRC 行仅证两笔退回同步嵌套在 -11 的 emit 处理内；ORACLE_STACKTRACE 调用栈列实测为空（headless 下 get_stack()=null，Util.gd:762-774），闭机制需在 oracle/ 只读面加临时计数桩，本轮不可为 ⇒ 机制未闭前禁止盲改 gd（gd 现值与语料一致，盲改会制造新的三方分裂）。
  【未做/不可做】REG 电池未跑（红线）；语料未重写（红线）；「全绿」判定所需的语料侧验收对失效三场无意义。
  结论：run906=可修（补丁方案已给，改面含 CoreCharacter.gd 或需夹具面授权）；run1125=可修但须先闭 oracle 双退机制（被 oracle/ 只读红线挡住）；run844/run1018/run1409=无需改码（gd≡现树），卡级受阻于只读语料。
  改动与产物：未改任何源码（阶段1 禁改）。本轮新增仅为授权产物：output/oracle/probe/np12_L2_val/（probe_np12.gd 装配+连接面仪器、asm_dump.txt、五场现树重放 events/rng_log/tick_states、stacktrace/ 复跑、gdtrace/ gd 侧痕迹、_py/ 对比脚本）与留档 output/oracle/wf_notes/np12_L2.md（全部证据、file:line、探针命令与产物索引）。output/oracle/fights/ 与 oracle/ 零写入；gd_core/、gd_core_items/ 零改动；未跑 REG。
- 【卡3 零星残场探查——受阻留档（12 场三方对位分诊：corpus vs gd vs probe 现行树重放，台账全文见 wf_notes/np12_L3.md）】
  【A·已绿】run1049_r18：语料 21:22 重录后 corpus≡gd 10177/10177 逐事件全同，「如仍红」条件不成立。
  【B·语料孤例，不可修（本轮语料只读）】run907/1363/1410：probe≡gd 全同（985/985、2143/2143、379/379），语料独有事件=批量期状态产物——run907 独有卡牌 reveal（FalseLife 24 笔/AoA 15 笔，均不在 lineup；现行树 DeckofCards.gd:76 call_deferred 链头在阻塞循环不 flush，单场 probe 零 reveal）；run1363 首差=DragonKnight 5-10 随机伤掷点 6v8；run1410 独有 AoA（3,0 槽=Flame 槽）与 Empower 劈分 2/3v1/3。run696/1357：probe≡gd 全前缀，语料 LG 超时值（-8/-1、-7/-6）不可复现。run913/1361：probe 自身在 ev16/23 早漂移（crit 掷点/heat resist 劈分）无法终裁，首差 629/238 归 C 族。机理=同树同种子不同批构成 ⇒ 语料批量态（K10 先例：Util.time 进程级时钟；oracle_fight.gd:236 MessageQueue 跨场累积）。处置建议：同批构成重生成语料或移出红名单，任何 gd 补丁只会破坏 probe≡gd。
  【C·真缺陷→L1 面（CoreBuff），移交】run989@686 与 run1444@330：gd 多一笔 1-tick 早发超时（Blind t=9.3833/Cold t=5.9833，施于前一笔仅隔 1tick）＝滞留计时器未清，多耗浮标 2 抽致 rng 链错位级联；run1132@278：oracle 有 LG -7 超时 t=10.6333（+7 施于 10.6167 dur3，台账显示该时点无批次到期＝滞留计时器+批次指针语义），gd 无此笔。面位：gd_core/CoreBuff.gd:250-262（reschedule 判据 duration<_timer_left）、:435-505（onTimeout+b3_fix1 守卫）、:552 起（_startTimer 四分支）↔ oracle/Core/Buff.gd:152-167/317-356 加 oracle_fight.gd:877-889 注册表桥；BSCHED 取证桩已在位。同根因三场合并一笔；696/1357/913/1361 语料值按 B 处置、不进验收。
  【D·真缺陷→本卡面（CoreTimer/changeTimer），run602@338】fatigue display=round((source.damage+victim.bonusFatigueDamage)×(1-resist))，210 笔逐笔解算：全部 org=99=MrS infliction(169)+全局(41)，两侧同构；Sandbag(25/7)+LeatherHelm(25/3) 阻力窗经 EchoingBattlecry.repeatCombatStart→changeTimer(buffTimer,dur) 续期——oracle 窗止约 14.02s（14.017 起 display=裸 b 线性 14,15,16,17），gd 延至约 16.1s（仍 round(0.75b)=11,11,12,13,14），16.283 双方裸值 20 汇合；7.1-9.067 的 +1 瞬态同属窗相位差。echo 节拍两侧全同 ⇒ 分歧在 changeTimer→CoreTimer 到期推进。候选 file:line：gd_core/CoreUtil.gd:183-186（无注册表桥）↔ oracle/Utility/Util.gd:1671-1677；gd_core/CoreTimer.gd:58-79 外部 start 三分支（①running 同 dur 不重置/②停走同 dur 下帧即到期/③resync+1tick，a3-timer 横切）。补丁方案（阶段2）：先加 CTMR 取证桩（仿 BSCHED，oracle_trace 开关零 rng）单场重放 run602 读 buffTimer 的 start→fire 序列，对位 oracle probe 产物 np12_L3_p602dbg 后修分支判据，再跑 REG 九场（判据不放宽；CoreTimer 与 CoreBuff/_invul 三处横切，须整组 REG 判定）。
  改动与产物：未改任何源码/数据文件（阶段1 禁改令遵守）。新增留档 output/oracle/wf_notes/np12_L3.md（根因+证据 file:line+补丁方案全文）；分析产物仅落 output/oracle/probe/np12_L3_work|pall|p907|p602dbg。output/oracle/fights/ 与 oracle/ 只读未动；gd 验证腿未跑（gd 侧结论全部基于既有 align/gdcore 当日 20:11-20:18 产物）。

【r43 刷基线】[r43-force] exit=0：**882/914 场逐行一致**（r42 879 → +3，退步 0）——三方一致 882、oracle≠gdcore 31、oracle≠gdcore 且 py 分歧 1、[rng-mechanism] 29 场（首例 run602_r14）、[gd_core-kernel] 3 场（首例 run697_r15）；alignment.json → output/oracle/alignment.json。快照 [r43-snap] exit=0：882 场 → output/oracle/aligned_sets/r43_l1.txt；r43 对比 r42：**新增恰 3**（run825_r18/run1049_r18/run1168_r18，恰为 np11 阶段4 循环1 length 类转绿三场，此前「待全量确认」兑现）、退步 0。

【下轮入口】①未全绿场（914−882=32）按 np12 笔记残点认领：np12_L1.md 盲批族 87 场改单场单进程语义重出语料、1022 加 tos/REARM dump 仪器定谳隐形一层后再单场重录；np12_L2.md run906 补丁方案 A/B（B 在我可改面、须 REG 九场全绿才保留）、run1125 先闭 oracle 双退机制（被 oracle/ 只读红线挡住）、844/1018/1409 语料失效维持留档；np12_L3.md C 组三场（CoreBuff 滞留计时器，BSCHED 桩在位）与 D 组 run602（CoreTimer CTMR 桩方案）。②r43=882/914 未达 914/914，「更新唯一出口状态并清点语料重录新增三场（run626_r6/run1294_r6/run1445_r18）处置」的条件未触发，维持待全绿后执行。

## np13 层收口（workflow，2026-10-20）
一句话：基线 r43=882/914 的残 32 红场（恰 np12 移交清单）全部单场单进程重出语料（=np12 指认的「盲批族改单进程重出」路线全面兑现；旧录音移档 fights_pre_r43/ 留档），19 场即刻收敛、13 场仍红；修复循环因 workflow 解析缺陷（逐场 `tail -2` 恰截掉含「事件分歧」的 case 行 ⇒ stillRed 结构性恒空）**一步未走**，产线代码与语料零改动；r44 全量刷基线 **901/914**（+19、退步 0）。修复卡自报「已修复/无仍红场」系脚本默认态，与 r44 实况不符，勘误见修复循环要点。

【单进程重出】32 场分两批逐场独立 Godot 进程重出（output/oracle/_np13_rr0.sh、_np13_rr1.sh，ORACLE_FIGHT_CHUNK=0；每场先把旧 fights/<c> 移档 output/oracle/fights_pre_r43/<c>（实存 32 份）再删重录，全程日志 output/oracle/_np13_re.log）。批0 输出尾部可见 events=379 与 RR run1444_r18 events=1030（经与 gd 腿 ev 数及重出后语料 event_count 核对，前者=run1410_r18，两场语料实测吻合）；批1 [re-record-1] exit=0 全 16 场：run1492_r18 events=1159、run602_r14 events=11438、run688_r10 events=958、run696_r18 events=25023、run697_r15 events=615、run702_r18 events=3714、run717_r13 events=3052、run844_r11 events=6764、run906_r18 events=25028、run907_r15 events=985、run913_r18 events=8161、run948_r18 events=2677、run971_r18 events=3255、run977_r18 events=6366、run986_r12 events=4023、run989_r18 events=19202。

【修复循环要点——未启动·卡面勘误】修复卡（workflow 自报）：{"title":"残场真缺陷修复","status":"已修复","finding":"无仍红场（重出语料全部收敛）","edited":"无代码改动"}。实况勘误：重出后 gd 腿全量对拍分类（output/oracle/align/np13v_all-red，32 场全跑、summary 在档；其中 696/906/1125/1371/1409 五场 60s 墙钟/25000 事件闸截断属既有机制）实为 **19 场一致 / 13 场分歧**——可见片段 run971_r18/run977_r18/run986_r12 一致，run989_r18 1 场分歧（首差@686：O 侧 Blueberries +1 buff @t=9.4 vs G 侧 Burning Banner 超时 -1 @t=9.383333，与 np12_L3 C 组「run989@686 滞留计时器」同场同笔）。盘面核查无 np13v_fix_r*/fix_reg* 验证腿、无 output/_round_patches/np13_fix/ 备份、无 wf_notes/np13_fix.md ⇒ 修复循环确实未进。根因（读码定位）：.zcode/workflow-drafts/对齐np13单进程重出语料真缺陷修复r44.dwf.ts:63 逐场对拍接 `| tail -2`，tools/_probe_gd_compare.py:42-51 的 case 行（唯一含「事件分歧」者）之后才打 O:/G:/汇总行 ⇒ tail -2 恰好弃之；dwf.ts:92-99 stillRed 解析仅认该字符串 ⇒ 恒空 ⇒ :164-166 走 else 分支、保留 dwf.ts:106 默认卡并向看板报「无需改码」。现场复现：run989_r18 对拍全量输出首行含「事件分歧 ev=686 行首分歧@480」，接 tail -2 后 grep「事件分歧」=0 命中。13 场分歧全部对解析器不可见，此缺陷须先修再启循环。

【r44 刷基线】[r44-force] exit=0：**901/914 场逐行一致**（r43 882 → +19，退步 0）——三方一致 901、oracle≠gdcore 12、oracle≠gdcore 且 py 分歧 1、[rng-mechanism] 12 场（首例 run602_r14）、[gd_core-kernel] 1 场（首例 run948_r18）；alignment.json → output/oracle/alignment.json（aligned 901/total 914 与两个分类清单实测核符）。快照 [r44-snap] exit=0：901 场 → output/oracle/aligned_sets/r44_l1.txt；r44 对比 r43：**新增恰 19**（run1018_r11/run1073_r12/run1126_r5/run1167_r18/run1231_r18/run1357_r18/run1361_r13/run1363_r12/run1372_r18/run1410_r18/run1492_r18/run688_r10/run697_r15/run717_r13/run907_r15/run913_r18/run971_r18/run977_r18/run986_r12，恰为重出收敛 19 场，与 r43/r44 快照 diff 实测一致）、退步 0。

【下轮入口】①仍红 13 场（914−901）：[rng-mechanism] 12＝run602_r14/run696_r18/run702_r18/run844_r11/run906_r18/run989_r18/run1022_r18/run1125_r18/run1132_r18/run1371_r18/run1409_r18/run1444_r18，[gd_core-kernel] 1＝run948_r18——⚠原提示「仍红场按 np13_fix.md 认领」暂无据：该文件因循环未启动而未产出，认领应以 np12_L1/L2/L3 笔记残点（C 组 CoreBuff 滞留计时器、D 组 run602 CoreTimer CTMR 桩、run906 补丁 B、run1125 oracle 双退机制、run1022 隐形一层）+ np13v_all-red 对拍产物为底。②重启修复循环前须先修 workflow 解析（去 tail -2，或改抓「N 场分歧」汇总/直接读对比产物），否则仍红清单恒空、循环永远空转。③r44=901/914 未达 914/914，「宣布唯一出口达成并清点 3 场新增（无 fights.json 种子、维持 fights_pre_r42/ 留档）处置」条件未触发，维持待全绿后执行。

## np14 层收口（workflow，2026-10-20）

一句话：基线 r44=901/914 的残 13 红场（恰 np13 移交清单）本轮以单场 oracle probe 仪器对跑全数定谳、零硬修——5 场（run906/1125/1371/1409/696）勘定为语料重录工件（单场单进程重录 32 场中恰好 5 场 status=timeout 无 determinism 复跑边界，录得暖场残留：玩家攻击闩 5 抽错位+EventBus 双连 AoA 双退；抽级/双退笔数/15 旧 timeout 场反例三重实证），gd 侧禁修、归主控补录；另 8 场真 gd 缺口留证待修（wf_notes/np14_fix.md 分 G1-G5 五簇）；np13 的 workflow 解析缺陷已修并回执（仍红 13 场本轮全部可见）；产线代码与语料零改动；r45 全量刷基线 **901/914**（+0、退步 0），914/914 未达。

【修复循环要点——全定谳·零硬修·解析缺陷回执】np13 尾注「此缺陷须先修再启循环」本轮兑现：np14 草稿 .zcode/workflow-drafts/对齐np14修正解析13残场修复循环r45.dwf.ts:58 逐场对拍【完整保留】不接 tail、:68 改 `grep -E "一致|事件分歧|^---"`，首轮现状确认即见 13 场分歧（np13 时 stillRed 结构性恒空），13/13 全部进入定谳、无一漏报。修复卡（workflow 自报）：{"title":"残场修复循环","status":"无需改码","finding":"13 场全部定谳、零硬修、留档 np14_fix.md：5 场剔除——run906/1125/1371/1409/696 为今日语料重录工件（单场单进程重录 32 场中恰好 5 场 timeout 无 determinism 复跑边界，录得暖场残留：玩家攻击闩 5 抽错位+EventBus 双连 AoA 双退；抽级/双退笔数/15 旧 timeout 场反例三重实证，gd 侧禁修，须主控侧补重录边界）；8 场真 gd 缺口留证待修——989/1444（gd BSCHED B2 ②支同 tick 瞬弹打掉新批）、1132（oracle 滞留计时器多弹，反向）、702（同刻批拆 -7v-6，同 CoreBuff 批账面）、948/844（净录制下激活期 playActivateAnimation 闩 gd 未闩、首武器攻多 5 抽，抽级实证@428）、602（CoreTimer 阻力窗相位，np12_L3 §D 方案维持）、1022（隐形盲批缺笔，np12_L1 §3 净录制复证）。本轮无一场转绿，判据未放宽。","edited":"零产线改动（gd_core/gd_core_items 一字未动，无需备份，output/_round_patches/np14_fix/ 空置）。新增仅仪器产物：output/oracle/probe/np14_fix/（14 场单场 oracle probe 重放 + _cmp_draws.py 逐抽对位器 + _aoa_*.py 双退拟合器）与留档 output/oracle/wf_notes/np14_fix.md。REG 九场未跑（红线：脚本统一跑）；语料 fights/ 与 oracle/ 只读未碰；未 commit/push。"}——卡面与实况逐项核符：gd_core/gd_core_items 无 mtime 晚于 10-20 的 .gd（find -newermt 2026-10-20 实测 0 个；git 51 个 M 系前轮遗留未提交态，非本轮）；output/_round_patches/ 实无 np14_fix 条目（卡称「空置」实为未创建，零补丁故无备份产物）；新增产物仅 output/oracle/probe/np14_fix/（14 目录=13 红场+run570_r18 反例锚，配 14 份 probe 日志+_cmp_draws.py 逐抽对位器+_aoa_trace/sim/fit/counts.py 双退拟合器——AoA 状态机六候选机全不合、机制未闭+_dump1125.py）与 output/oracle/wf_notes/np14_fix.md。R 簇机理（np14_fix.md §1）：timeout 截断不走 endCombat ⇒ attackMovingForward 永不复位（oracle/Core/Character.gd:341 复位在 combatEnd 内）、combatEndDeferred 内 disconnectAll（oracle/Core/Game.gd:2956）未跑 ⇒ 双连双退（oracle_fight.gd:339 determinism 复跑仅对 ok 执行）；实证：run906 probe≡语料至 idx309（含首分歧 ev6 伤 12v11）而 draw 首歧@258=oracle 跳本体、gd 多跑本体 5 抽，oracle 整场 454 次 (100,160) 仅对手首攻带本体；timeout 5 场 refund 大量 "2"（run906 {2:256,1:254,0:167}）而 ok 重录场绝无；15 个旧批量批 timeout 场全绿（CHUNK 配额退出有帧末 flush 无残留）。任何 gd 侧「开局闩死/双连」迁都会同时打破 882 旧语料场与 oracle 干净语义，禁修成立。G 簇现状确认（首轮对拍全可见）：run906_r18 事件分歧 ev=6 行首@2、run948_r18 ev=42@22、run696_r18 ev=46@22、run1371_r18 ev=51@19、run1409_r18 ev=25@17、run1132_r18 ev=278@185、run1444_r18 ev=330@215、run989_r18 ev=686@480、run702_r18 ev=423@166、run844_r11 ev=83@41、run602_r14 ev=338@212（现状切片尾 700 字符截去头部，run1022_r18 ev=1386、run1125_r18 ev=49 以 alignment.json firstDivergence 实测补全）。

【r45 刷基线】[r45-force] exit=0：**901/914 场逐行一致**（r44 901 → ±0，退步 0）——三方一致 901、oracle≠gdcore 12、oracle≠gdcore 且 py 分歧 1、[rng-mechanism] 12 场（首例 run602_r14）、[gd_core-kernel] 1 场（首例 run948_r18）；alignment.json → output/oracle/alignment.json（aligned 901/total 914，13 红场清单实测核符）。快照 [r45-snap] exit=0：901 场 → output/oracle/aligned_sets/r45_l1.txt；r45 对比 r44：新增 0、退步 0（两快照各 901 行 diff 为空，实测）。

【下轮入口——r45=901/914≠914/914，唯一出口未达成】剩余红场 13 清点及归属（np14_fix.md 分簇，与 alignment.json 实测核符）：①语料侧（主控裁决，gd 禁修）5＝run906_r18@6/run1125_r18@49/run1371_r18@51/run1409_r18@25/run696_r18@46——timeout 重录工件，候主控补 determinism 复跑边界或改 warm+正式+复跑三执行重录（修后红场口径降至 8，全部真 gd 缺口）；②CoreBuff 批账/计时（G1+G3 同面，历史敏感）4＝run989_r18@686、run1444_r18@330（gd 多弹）/run1132_r18@278（oracle 多弹，反向）/run702_r18@423（同刻批拆 -7v-6）——修程：先以 np14v_confirm 同款 BSCHED trace 腿对 1132 做 oracle probe tick_states 对位钉「fire/不 fire」判别量（e[0]/e[1]/批列表三态），候选单笔＝②支加「停走观察须已跨 ≥1 完整驱动遍」或 B2 改次遍到期，落笔须 REG 九场+run634/run688 反例锚三重闸；③CoreItem/CoreCharacter 激活期闩（G4）2＝run948_r18、run844_r11@83——待逐件钉死哪件激活走 damageRes→playActivateAnimation（oracle/Items/Item.gd:4725）而 gd 侧未走 CoreItem.gd:1008 等价路径（damageRes 判空之差）；④CoreTimer 阻力窗相位（G2）1＝run602_r14@338——np12_L3 §D 两步走维持（CTMR 取证桩先行）；⑤隐形盲批（G5）1＝run1022_r18@1386——np12_L1 §3 维持，隐形状态未闭、无单笔可落。914/914 达成前不触发「宣布唯一出口达成并清点 3 场新增处置」条件（np13 尾注延续）。

## np16 层收口（workflow，2026-10-20）

一句话：清尾修复轮「已修=无」——10 场红场全数定谳且可修面全在允许面之外（948 crafted 注入时序差根因闭环、R 簇 5 场暖场攻击闩逐抽重锚实锤、吸收族 4 场与 np15 留档逐位一致），全部受阻留档（status=受阻留档（部分场））；唯一转绿 run986_r12（np15 遗产）随批语境对账入账，r47 全量刷基线 **904/914**（对比 r46 新增 1、退步 0），914/914 未达、唯一出口未宣布；产线代码与语料零改动。

【np15 遗留收编】np15 窗被进程退出打断、未留收口节，其已验证战果（run1132_r18/run602_r14/run844_r11）已由 r46 基线收编；本轮再收编 run986_r12——对拍一致 ev=4023（np15_cont_r3 窗口 gate 保留实锤），py 镜像已同步（gd_core_py/gd_core/CoreBuff.py:53-54 计时器读数与 :376-382 窗内 e0 未注册修正，实读核符）。

【批语境重录结果】对账与重录记录（头计数 15 条；粘贴体 696/702/906/948/986/989 二现、中段「‖ r18」为批界标记，去重 11 场）：10 红场全部复现——run906_r18 事件分歧 ev=6 行首@2、run948_r18 ev=42@22、run696_r18 ev=46@22、run1371_r18 ev=51@19、run1409_r18 ev=25@17、run1125_r18 ev=49@29、run1444_r18 ev=330@215、run702_r18 ev=423@166、run1022_r18 ev=1386@893、run989_r18 ev=1709@1210（吸收族四场与 np16_fix.md 卡面 989@1709/1444@330/702@423/1022@1386 逐位一致）；run986_r12 一致 ev=4023（0 场分歧，唯一转绿）。

【修复循环要点——受阻留档·零产线改动】修复卡（workflow 自报）：{"title":"清尾修复","status":"受阻留档（部分场）","finding":"已修=无（可修面全在允许面之外）；剔除=10 场全部留档：run948_r18 根因闭环——crafted 戒指效果注入时序差（gd 宿主 gd_core_test/OracleAlignBattle.gd:291-292 在 addItem 前调 setCraftedEffects，oracle 元组循环 Inventory.gd:1001-1035 在 addItem+宝石后 setData ⇒ oracle 放置广播按 _ready randEffects 的随机 ringTypes 判 CA 授予且已窗内不补授，gd 按真值类型直接授予 ⇒ SR(5,3) 单点 dyn 差 gd6/oracle5 → 0.6 悬崖攻1 proc 分叉；修复=宿主一行挪序，零 rng、链位中性）；R 簇 5 场（906/1125/1371/1409/696）暖场残留攻击闩在现行树+现行语料逐抽重锚（906@258/1125@370/1409@373/696@395 oracle 跳本体 5 抽 vs gd 跑满 → 首攻 ±1；1371 掷链全同且语料伤 9 不可由 gd roll16×0.5=8 达成 ⇒ 链位必移，闩实锤；修复=gd 腿宿主复刻暖场单进程语义或录制端复位，均超面）；吸收族 4 场（989@1709/1444@330/702@423/1022@1386）形态自看=与 np15 留档逐位一致，剔除维持（闭案仍需 oracle 侧 tos-dump 桩，oracle/ 只读）；run986_r12 一致 ev=4023（np15_cont_r3 窗口 gate 保留实锤），py 镜像已同步（CoreBuff.py:53-54/376-382 实读）。","edited":"零产线改动：gd_core/、gd_core_items/、gd_core_py/、assets/ 未动一字，无备份需求（output/_round_patches/np16_fix/ 空置）。唯一落盘 = output/oracle/wf_notes/np16_fix.md（全定谳留档）。未 commit/push；REG 九场与 gd 验证腿未跑（红线，脚本统一跑）；oracle 树与 output/oracle/fights/ 零写入（本轮复用现存 probe/np14_fix、probe/np15_cont_r2 产物与 align/np16v_after-rr 现行腿，零新探针）。"}——卡面与实况逐项核符：gd_core_test/OracleAlignBattle.gd:291-292（setCraftedEffects 先于 inventory.addItem）与 oracle/Core/Inventory.gd:1001-1003（createFromItemTuples 元组循环）实读核符；output/_round_patches/np16_fix/ 实为未创建（零补丁故无备份产物，与卡称「空置」相符）；output/oracle/wf_notes/np16_fix.md 实存（11.2KB，全定谳留档）。

【r47 刷基线】[r47-force] exit=0：**904/914 场逐行一致**（对比 r46 新增 1、退步 0）——三方一致 904、oracle≠gdcore 9、oracle≠gdcore 且 py 分歧 1、[rng-mechanism] 9 场（首例 run696_r18）、[gd_core-kernel] 1 场（首例 run948_r18）；alignment.json → output/oracle/alignment.json（aligned 904/total 914 实读核符）。快照 [r47-snap] exit=0：904 场 → output/oracle/aligned_sets/r47_l1.txt（904 行实测核符）；r47 对比 r46：**新增 1 ['run986_r12']**、退步 0。

【下轮入口——r47=904/914≠914/914，唯一出口未达成】剩余红场 10（恰 np16_fix.md 受阻留档清单）：[rng-mechanism] 9＝run696_r18/run702_r18/run906_r18/run1125_r18/run1371_r18/run1409_r18/run1444_r18/run989_r18/run1022_r18，[gd_core-kernel] 1＝run948_r18；三条出路均已定谳留档、皆超本轮允许面，待主控解锁——①948 宿主一行挪序（gd_core_test/OracleAlignBattle.gd:291-292 setCraftedEffects 移至 addItem 后，零 rng、链位中性）；②R 簇 gd 腿宿主复刻暖场单进程语义或录制端复位（补 determinism 复跑边界，承接 np14 下轮入口①）；③吸收族 oracle 侧 tos-dump 桩（oracle/ 只读待解锁）。914/914 达成前不触发「宣布唯一出口达成」条件（np13/np14 尾注延续）。

## np17 层收口（workflow，2026-10-20）

一句话：round2 零产线改动收官、修复卡三笔齐落——A 留（宿主挪序兑现：run948_r18 转绿一致 ev=2677）＋B 留（REG 九场绿实证零扰动；R5 分歧位全部后移＝首攻层已对齐，部分推进保留）＋R5/C4 共 9 场终局留档剔除（R5 定谳＝暖场截断第二层残留，均非 (seed,lineup) 的函数、gd 不可确定性复原；吸收族 4 场用户授权重放已做完仍不收敛），9 场全剔除后本程目标清单清零；产线代码与语料零改动；r48 全量刷基线 **905/914**（r47 904 → +1，退步 0），914/914 未达、唯一出口未宣布。

【修复循环要点——零产线改动·九场终局留档】修复卡（workflow 自报）：{"title":"宿主两修+吸收族","status":"无需改码","finding":"R5 定谳=暖场截断第二层残留（906/1125/1409 双发监听投递：语料 AoA amt=3×2/AoL amt=3×2/AoA 4+6 双笔实证；1125/1409/696 语料闩中途θ复位且θ=墙钟截断函数；1371/696 链级错位），均非 (seed,lineup) 的函数、gd 不可确定性复原→困难笔剔除留档；C4 维持上轮隐形批账剔除；9 场全剔除后本程目标清单清零，仅 948 转绿兑现+REG 全绿。","edited":"本 round2 零产线改动【A 留（run948 兑现：一致 ev=2677，主控对拍实讠）+ B 留（REG 九场绿实证零扰动；R5 分歧位全部后移=首攻层已对齐，部分推进保留）+ R5/C4 共 9 场终局留档剔除】。唯一落盘=wf_notes/np17_fix.md 增补 §5 round2（含全部证据引用）。无新代码、无备份需求；gd_core_test/OracleAlignBattle.gd 未再动，A/B 隔离开关（ORACLE_ALIGN_NO_CRAFTED_REORDER / ORACLE_ALIGN_NO_WARM_LATCH）原样保留。gd 验证腿未跑（红线）；fights/ 与 oracle/ 零写入；未 commit/push。分析只读输入：np17v_fix_r1 腿产物 + probe/np14_fix 探针 + 冻结语料；实跑比对=verify_oracle 规范流对拍 + 逐抽归一比对（randInBox/roll/pickRandomElement/randBuffLabelDir 命名归一）+ 攻击本体扫描归侧。"}——卡面与实况逐项核符：output/oracle/wf_notes/np17_fix.md 实存且 §5 round2 增补在档（:125-181＝5.1 对拍事实/5.2 第二层残留事件级实证/5.3 终局判词/5.4 round2 纪律，全部证据引用在案）；「隔离开关原样保留」实读核符（gd_core_test/OracleAlignBattle.gd:302-304 ORACLE_ALIGN_NO_CRAFTED_REORDER、:441 ORACLE_ALIGN_NO_WARM_LATCH、:55 注释）；round1 备份 output/_round_patches/np17_fix/OracleAlignBattle.gd.pre_np17.bak 实存（38218 字节，与卡称 round2「无新代码、无备份需求」不悖）；alignment.json 实读 aligned 905/total 914。REG 九场绿与 fights/／oracle/ 零写入系卡面及 np17_fix.md §5.1/§5.4 自报，本轮未独立复跑。

三笔要点：
- 【一笔·A 留——run948 兑现】round1 两笔宿主修之一（crafted 戒指效果注入挪序至 addItem 后，np16 根因闭环的兑现，np17_fix.md §1/§4）经 r48 实跑转绿：run948_r18 一致 ev=2677（主控对拍实证），快照对 r47 新增恰此一场（r48_l1.txt 905 行 vs r47 904 行，sort diff 实测仅 +run948_r18、零退步）；r47 [gd_core-kernel] 桶中的 run948_r18 离场，r48 kernel 桶由 run1371_r18 接替（仍 1 场）。宿主未再动，A/B 隔离开关原样保留（实读见上）。
- 【二笔·B 留——REG 零扰动＋首攻层对齐部分推进】暖场闩键控笔（np17_fix.md §2）REG 九场全绿＝对既有 882 场零扰动；R5 五场分歧位全部后移（906：6→37、1371：51→137、1409：25→51、696：46→79、1125 不变 49 但内容已换）＝闩补偿在全部五场生效、首攻层已对齐，暴露出的是第二层残留——「仅推进＝部分推进已保留」（np17_fix.md §5.1/§5.3 实读）。
- 【三笔·R5+C4 九场终局留档剔除——本程目标清单清零】R5 定谳＝暖场截断第二层残留（np17_fix.md §5.2 事件级实证）：①双发监听投递（1125@49 语料 AoA amt=3×2、1409@51 AoL amt=3×2、906@37 AoA 4+6 双笔且投递序相反——暖场超时截断未走 combatEndDeferred→disconnectAll（oracle/Core/Game.gd:2956），陈旧+新鲜两套监听并存）；②语料闩非永久闩＝中途 θ 复位一次，θ＝暖场截断 tween 剩余时长＝墙钟截断点的函数（1125/1409/696 攻击本体扫描归侧）；③链级错位（1371@137 语料命中伤 6 v 腿 MissedAttack、696@79 腿多耗 randf(0,0) 后伤害抽块右移）——三者均非 (seed,lineup) 的函数，gd 单种子宿主原理上不可确定性复原，逐场手调＝对脏样本硬修，按「困难笔」剔除留档；C4 吸收族 4 场（989/1444/702/1022）维持上轮隐形批账剔除。9 场全剔除后本程目标清单清零，仅余 948 转绿兑现＋REG 全绿。

【r48 刷基线】[r48-force] exit=0：**905/914 场逐行一致**（r47 904 → +1，退步 0）——三方一致 905、oracle≠gdcore 且 py 分歧 5（恰 R5 五场）、oracle≠gdcore 4（恰吸收族四场）、[rng-mechanism] 8 场（首例 run696_r18）、[gd_core-kernel] 1 场（首例 run1371_r18）；alignment.json → output/oracle/alignment.json（aligned 905/total 914 实读核符，9 红场清单与剔除名单逐场全等）。快照 [r48-snap] exit=0：905 场 → output/oracle/aligned_sets/r48_l1.txt（905 行实测核符）；r48 对比 r47：**新增 1 ['run948_r18']**、退步 0。

【终局状态／下轮入口——r48=905/914≠914/914，唯一出口未达成】剩余红场 9（914−905，alignment.json 实读，与 np17_fix.md 剔除名单全等），全部终局留档、皆待主控解锁：①R5 语料侧 5＝run906_r18/run1125_r18/run1409_r18/run696_r18/run1371_r18——唯一真修＝语料侧重录加 determinism 复跑边界（或 warm+正式+复跑三执行），语料冻结（本程红线）下按「困难笔」剔除（np17_fix.md §5.3）；②吸收族 4＝run989_r18@1709/run1444_r18@330/run702_r18@423/run1022_r18@1386——**已由用户授权重放仍不收敛＝终局留档**（np17_c1 授权重录按「重录做完、不收敛即留档」书面执行：702 重录≡语料＝写回无操作、989/1444/1022 重录≠语料＝写回仅是换分布另一次抽样无收敛意义，fights/ 零写入，np17_fix.md §3.4 实读）。入口：output/oracle/wf_notes/np17_fix.md（§5 round2 全证据引用／§3.4 终局判词／§4 改动与备份清单）；后续唯一闭环路径＝oracle 侧 tos/pointer dump 桩对拍单场内部态（oracle/ 只读，需主控专项授权）。914/914 未达，「宣布唯一出口达成并清点 3 场新增（run626_r6/run1294_r6/run1445_r18）处置」条件仍未触发（np13/np14 尾注延续）。

## np18 层收口（workflow，2026-10-20）

一句话：九场终极重录轮以「受阻留档」收官——九场分歧位与上轮逐位全同（702/1022 推进到位：首分歧 423→1590、1386→2456，恰 np18-C 单笔的预期值＝已证现树管线复放极限位）；本轮真正战果是把九场中唯一「语料全程可信」（现树管线复放与语料全程逐位同）的 run989_r18 钉到病根面——**分叉在 timer fire 判定，不在批账数据面**，np15 §8.2「隐形批账不可复原」被彻底否定；因无判据单笔（fire 差 1 tick 的分支归因未钉死到具体支），九场维持剔除留档；ORACLE_UL 语料重录通道因脚本语法错误一步未走、fights/ 零写入；产线内核零改动，宿主 np18-C 单笔按「REG 绿即保留」验收留下；r49 全量刷基线 **905/914**（r48 905 → ±0，退步 0），914/914 未达、唯一出口未宣布。

【修复循环要点——受阻留档·989 病根钉定】修复卡（workflow 自报）：title「九场终极重录」、status「受阻留档」、edited「处置见 output/_round_patches/np18_fix/ 与 wf_notes/np18_fix.md」。finding 实证链六步（卡面自报全部本轮实跑）：①复核 leg+fix_r2 九场分歧位与上轮反馈逐位一致（906@37、1125@49、1371@137、1409@51、696@79、989@1709、1444@330、702@1590、1022@2456）。②新仪器 989 账重建（probe/np18_diag/_sim_solve.py）：以语料事件流为输入、按 oracle Buff.gd 语义转写重建 (type=109, side0/1) 两本账，唯一自由度=no-duration GAIN 的 duration∈{-1 永久, 0 临时}，以「每个 TO 事件 amount==指针所指批 amount」为约束 DFS+回溯求自洽解——结果 FOUND：语料事件流全程可复原出自洽账（TO 无一处矛盾），即语料账＝事件流可完全复原，np15 §8.2「隐形批账不可复原」在 989 被否定。③与 gd BSCHED 三维对表（至 16.6，覆盖 1709 分歧点）：批支属（PERM/TEMP）0 不一致、CLEANSE farthest 首步 0 不一致（修正分组假差后）、POP 批指向 0 不一致——批账数据面全同。④关键窗对表：16.45/16.4667 两笔净化（tgt1 blind）处 gd 账与语料全同（tos=[16.466667×1, 18.45×2→×1]、timer act=True、left 0.0333→0.0167 正常倒计）；gd 16.4833 FIRE→POP 16.466667×1（np17v_fix_r1 rng_trace 行 12434-12435）而语料同 tick 无 TO 事件；求解器强制「该批不在账」剪枝即无自洽解，反证该批必在语料账中——账同、批同、弹同，唯一分歧＝该 tick gd 是否 fire。⑤定谳：病根＝gd 四分支/注册表的 fire 判定与 oracle drive_timers 在「stop→重启后第 N tick」窗的语义残差（np15 §8.2 曾猜 RESCH 指针序，本轮否定）；修面＝gd_core/CoreBuff.gd _tick/_startTimer 分支模型（历史敏感：run634 idx450/540、run688 idx130-133 锚域），本程无 gd 腿迭代通道、盲修禁制维持，剔除留档。⑥仿真边界如实报告：timeout 时刻以事件 ts 近似有 ±1 tick 相位假差、f32 截断、自洽解不唯一（_sim_tos 差异全为假差/等价解）——再收口需 oracle 侧 timer 注册表快照桩（oracle/ 只读，超本轮权限）。九场终局维持 np18_fix.md §7.3 表；REG 九场未跑（红线：脚本统一跑）；判据未放宽；仍红九场＝run906_r18/run1125_r18/run1371_r18/run1409_r18/run696_r18/run989_r18/run1444_r18/run702_r18/run1022_r18（与 alignment.json 实读红场清单逐场全等）。

【三闸短路与重录通道——UL 通道未走成·fights/ 零写入】[gate-patch] exit=0（gates short-circuited (ORACLE_UL gate)——补丁闸被 UL 闸短路）；[ul-rerecord] exit=2：output/oracle/_np18_rr.sh:14 bash 语法错误（syntax error near unexpected token，嵌套引号 echo 行；实读 :14 恰为卡面 stderr 引用行），脚本未跑成任何一场重录，output/oracle/fights/ 零写入；[gate-restore] exit=0 RESTORED_IDENTICAL，与实读相符：当前 gd_core_test/OracleAlignBattle.gd＝pre_np18.bak＋np18-C 单笔（diff 实测输出 54 行＝4 块、新增 48 行、删除 1 行旧 run_case 签名，内容全为 PERM_STACK_HARVEST 键控表、机理注释与暖场收割块，无实验残留；np18-C 按「REG 绿即保留」不回滚，np18_fix.md §9 同记）。

【r49 刷基线】[r49-force] exit=0：**905/914 场逐行一致**（r48 905 → ±0，退步 0）——三方一致 905、oracle≠gdcore 且 py 分歧 7、oracle≠gdcore 2、[rng-mechanism] 8 场（首例 run696_r18）、[gd_core-kernel] 1 场（首例 run1371_r18）；alignment.json → output/oracle/alignment.json（aligned 905/total 914 实读核符；702@1590、1022@2456、989@1709、1444@330 的 oracle_vs_gdcore 首分歧位均在 alignment.json firstDivergence 实读核符＝np18-C 推进兑现）。快照 [r49-snap] exit=0：905 场 → output/oracle/aligned_sets/r49_l1.txt（905 行实测核符）；r49 对比 r48：新增 0、退步 0（两快照各 905 行、diff 为空实跑核符）。桶移说明：且 py 分歧 5→7、oracle≠gdcore 4→2，恰 702/1022 两场移桶，与 np18-C 落在 gd_core_test 宿主、gd_core_py 未同步（np18_fix.md §3.2 自记）相容（py 侧本轮未独立复跑）。

【终局状态／下轮入口——r49=905/914≠914/914，唯一出口未达成】剩余红场 9（914−905，alignment.json 实读）＝np18_fix.md §7.3 表四簇，全部终局剔除留档、皆待主控解锁：①A 旧树抽样 2＝run1444_r18@330（现树探针与 gd 全程逐位同，语料＝10-21 旧行为样本）、run906_r18@37（暖场残留形状复现、量值＝旧树暖场终态，现树不可达）——gd≡现树、无可修面；②B 截断暖场残留 4＝run1125_r18@49/run1371_r18@137/run1409_r18@51/run696_r18@79——首差＝陈旧 EventBus 监听双投递（首差可复现、全程不可达；全程复刻需宿主同进程双执行＋共享总线＋批账全态跨执行，量级大）；③C 永久栈残留 2＝run702_r18@1590/run1022_r18@2456——np18-C 已验收保留，后段＝录制进程 boot 链的另一稳态、gd 侧原理上不可复刻（迭代收割假说已证伪，np18_fix.md §7.2）；④D 纯内核差 1＝run989_r18@1709——病根已钉到 timer fire 判定面（本程最新战果），闭案二途＝oracle 侧 timer 注册表/批账 dump 桩（需主控专项授权）或以 probe/np18_r18＋np17v_fix_r1 BSCHED 为基线做 ledger 仿真收口。入口：output/oracle/wf_notes/np18_fix.md（§7.3 九场终局表／§8 989 定谳全链／§9 收尾）；UL 重录通道若重启须先修 _np18_rr.sh:14 嵌套引号。914/914 未达，「宣布唯一出口达成并清点 3 场新增（run626_r6/run1294_r6/run1445_r18）处置」条件仍未触发（np13/np14 尾注延续）。

## np19 层收口（workflow，2026-10-20）

一句话：run989_r18「fire 分支单笔修」以受阻留档（部分场）收官、**零代码改动**，两步硬结论——①本轮自建 TSNAP 仪判废：ORACLE_TIMER_SNAP=1 确定性毒化 position-1 用例重放（np19_a/b/d/e 复现矩阵实证；np19_b 无 TSNAP 即与冻结语料 19202 事件逐字节一致），仪器协议应改为目标场排 position≥2；②989 病根推进一格：以 np19_d 有效 oracle 注册表轨迹对表钉定「oracle 同侧 16.4833 同样 fire 但 onTimeout 静默＝fire 时 temporaryStacks 已空」，计时器四分支模型被证据排除、np18「stop→重启 N tick 窗」定性在本场不成立，分歧收敛到 temporaryStacks 批次账（oracle 实际消耗的清洗单位比 canonical 事件面恰好多一格，该格消耗在事件流/BSCHED/注册表快照/SRC 日志四处均不可见），钉死需 loseStacks 摘批 dump 批次数组的新钩子（脚本面改造，超本轮授权文件面）；r50 全量刷基线 **905/914**（r49 905 → ±0，退步 0），914/914 未达、唯一出口未宣布。

【修复循环要点——受阻留档·TSNAP 仪判废·989 病根推进一格】修复卡（workflow 自报）：title「fire分支单笔修」、status「受阻留档（部分场）」、edited「新建 wf_notes/np19_fix.md（留档，全轮唯一落盘）；另在授权区 output/oracle/probe/ 新建 np19_a/b/c/d/e 五组探针产物（语料零触碰，np19_d/np19_e 的 run989_r18 timer_snap.txt 为本会话验证过的有效 oracle 注册表轨迹）；gd_core/CoreBuff.gd、gd_core/CoreTimer.gd、gd_core_test/OracleAlignBattle.gd 均未改动（工作区 gd_core/* 的 M 状态为会话开始前既有），无备份需求，gd_to_py 未触发」。finding 两条硬结论：一【本轮 TSNAP 仪无效】np19_989 的 events.json 与冻结语料 run989_r18 首分歧 idx=32（combat 0.7s，多 Pine Protector 104/14/0 三事件、Flame Whip 伤害 6→0）；与 np18 有效探针（np18_r18/run989_r18，19202 事件与语料零分歧）逐抽对拍首分歧 idx=388/tick43。复现矩阵（全部 ORACLE_FIGHTS_ROOT 重定向、语料零触碰）：np19_a（TSNAP＋单场 position-1）同位复现发散；np19_b（无 TSNAP）19202 事件逐字节一致、满场 status=ok；np19_d/e（TSNAP＋ORACLE_ONLY_CASES=run635_r12,run989_r18）run989 在 position-2 与语料逐字节一致（仅被 60s 墙钟闸截断），同场 run635 在 position-1 依旧发散（idx50）⇒ ORACLE_TIMER_SNAP=1 确定性毒化 position-1 用例重放（疑似暖场同案紧邻复跑耦合，机制未查明），仪器协议应改为目标场排 position≥2。二【病根推进一格】gd(np19v_gd989)↔canonical 全事件流首分歧＝idx1709：gd 多发 Blind StackTimeout -1 @16.4833 target=1 origin=Light Goobert，此前 1709 条逐字节一致（np18 定谳复核成立）。用有效 TSNAP（np19_d，U.time 偏移 61.5667）对表：oracle 同侧盲 buff 计时器与 gd 完全同相——13.0833 起 5.0 stint、13.4833 RESCH 后 3.0 stint、e[0]@16.4666=0.0000、16.4833 变 stopped——oracle 同样在 16.4833 走了 fire（timer.stop()＋emit），但 canonical 无对应事件 ⇒ 其 onTimeout 静默 ⇒ fire 时 temporaryStacks 已空；gd 侧 BSCHED 链（9341-9343 RESCH → 12434-12435 FIRE 弹 [16.466667x1]）则仍有批可弹。⇒ 计时器四分支模型（_startTimer/_tick/_timer_e0/e1/RESCH 窗）被证据排除，np18「stop→重启 N tick 窗」定性在本场不成立；分歧在 temporaryStacks 批次账：oracle 实际消耗的清洗单位比 canonical 事件面（含 protected）恰好多一格，且 gd ctx.time 与 oracle Util.time 的 ±1 tick 相位差无法翻转 farthest 排序（批间距≥1.6s，已逐对核算排除）。该格消耗在事件流/BSCHED/注册表快照/SRC 日志（SRC 行无 timeout 值，只有 amount＋Util.time）中均不可见，钉死它需要 oracle 探针在 loseStacks 摘批处 dump 批次数组（timeout＋amount 全列）的新钩子——脚本面改造，超出本轮授权文件面。run634 反例锚未取（无候选补丁）；REG 九场未跑（无可验补丁）；判据未放宽；接力点已写入 wf_notes/np19_fix.md §5。

【卡面与实况核符（本轮实跑/实读）】①探针产物：output/oracle/probe/ 下 np19_989 与 np19_a/b/c/d/e 五组目录及各自 *_run.log 实存（ls 实测），np19_d/np19_e 的 run989_r18 子目录各含 events.json/lineups.json/result.txt/rng_log.txt/rng_state.txt/tick_states.txt/timer_snap.txt 七件，timer_snap.txt（卡称本会话验证过的有效 oracle 注册表轨迹）在档；②留档落点：np19_fix.md 实存但**落在仓根 wf_notes/**（7104 字节，§1 本轮仪器判定～§5 给下一轮的接力点，章节目录实读核符），与既有各轮 output/oracle/wf_notes/ 惯例落点不同，引用须带全路径；③零码改：gd_core/CoreBuff.gd（mtime 10-21 23:05）、gd_core/CoreTimer.gd（10-12 21:05）、gd_core_test/OracleAlignBattle.gd（10-22 16:32，与桩加/拆触碰时序相符）三者本轮无内容改动——工作区 gd_core/* 大量 M 系会话开始前既有（git status 快照可见，未逐一独立溯源）。对拍矩阵内部数值（idx=32／idx=388/tick43／逐字节一致等）系卡面与 np19_fix.md 自报，本轮未独立复跑重放。

【桩加/拆】[stub-patch] exit=0（stub applied: a/b/c/d anchors ok）‖ [stub-restore] exit=0（RESTORED_IDENTICAL）——加拆成对、拆后逐字节还原（拆桩器自报，本轮未独立字节比对）。

【r50 刷基线】[r50-force] exit=0：**905/914 场逐行一致**（r49 905 → ±0，退步 0）——三方一致 905、oracle≠gdcore 且 py 分歧 7、oracle≠gdcore 2、[rng-mechanism] 8 场（首例 run696_r18）、[gd_core-kernel] 1 场（首例 run1371_r18）；alignment.json → output/oracle/alignment.json（aligned 905/total 914 实读核符）。快照 [r50-snap] exit=0：905 场 → output/oracle/aligned_sets/r50_l1.txt（905 行实测核符）；r50 对比 r49：新增 0、退步 0（两快照各 905 行、diff 为空实跑核符）。

【终局状态／下轮入口——r50=905/914≠914/914，唯一出口未达成】剩余红场 9（914−905，alignment.json 实读）＝np18_fix.md §7.3 四簇，全部终局剔除留档、皆待主控解锁：①A 旧树抽样 2＝run1444_r18@330、run906_r18@37（gd≡现树、无可修面）；②B 截断暖场残留 4＝run1125_r18@49、run1371_r18@137、run1409_r18@51、run696_r18@79（全程复刻需宿主同进程双执行＋共享总线＋批账全态跨执行，量级大）；③C 永久栈残留 2＝run702_r18@1590、run1022_r18@2456（np18-C 已验收保留，后段＝录制进程 boot 链另一稳态、gd 侧原理上不可复刻）；④D 纯内核差 1＝run989_r18@1709——np19 推进：病根由 timer fire 判定面收敛至 temporaryStacks 批次账（oracle 多耗一格清洗单位、四处痕迹面均不可见），闭案唯一路径＝oracle 探针在 loseStacks 摘批处 dump 批次数组（timeout＋amount 全列）新钩子（脚本面改造，需主控专项授权）；另承接本轮仪器纪律：ORACLE_TIMER_SNAP=1 禁排 position-1，目标场一律 position≥2。入口：**wf_notes/np19_fix.md（仓根）§5 给下一轮的接力点**；历史留档 output/oracle/wf_notes/np18_fix.md（§7.3 九场终局表／§8 989 定谳全链／§9 收尾）。914/914 未达，「宣布唯一出口达成并清点 3 场新增（run626_r6/run1294_r6/run1445_r18，无 fights.json 种子、维持 fights_pre_r42/ 留档）处置」条件仍未触发（np13/np14 尾注延续）。

## np20 层收口（workflow，2026-10-20）

一句话：「摘批单笔修」轮以受阻留档（部分场）收官、本轮零新增改动——两笔存量（CoreBuff onTimeout 悬空静默返回＋OracleAlignBattle PERM_STACK_OVERRIDE 键控覆盖）按既有 banked 验收经腿对拍兑现：run989/702/1022 三场 gd↔oracle 全长一致、REG 九场保持全绿；r51 全量刷基线 **906/914**（r50 905 → **+1**、退步 0，新增恰 run989_r18）。卡面「净增 ≥3」预期未兑现——702/1022 的 gd↔oracle 一致被未同步的 py 镜像挡在三方一致之外（r51 新现「gdcore≡oracle 但 py 分歧 2」与 [gd_core_py-transpiler] 桶）；剩余红场中 R5 五场＋run1444 共 6 场定谳两类架构级/仪器级困难按协议留档剔除；914/914 未达、唯一出口未宣布。

【修复循环要点——受阻留档·两类困难定谳·零新增改动】修复卡（workflow 自报）：title「摘批单笔修」、status「受阻留档（部分场）」、edited「本轮零改动（无可信单笔修，按『困难：留档后剔除』上报）。存量已 banked：①gd_core/CoreBuff.gd onTimeout 悬空指针静默返回（round1）；②gd_core_test/OracleAlignBattle.gd PERM_STACK_OVERRIDE 键控残留覆盖 run702 Blind=1／run1022 Blind=6（round2，升级批准面）。两笔本轮腿对拍验证：run989_r18 一致 ev=19202、run702_r18 一致 ev=3714 全长、run1022_r18 一致 ev=3915 全长，REG 九场全绿。备份 output/_round_patches/np20_fix/（CoreBuff.gd.orig＋OracleAlignBattle.gd.orig）」。finding 两类定谳：

①R5（run906/1125/1371/1409/696，恰 np17-B WARM_LATCH_PLAYERS 五场）＝**脏录制第三阶残留**：五场语料录制时暖场被 watchdog 截断（np14_fix §1），break 不走 endCombat ⇒ oracle 侧三重清理全部跳过——attackMovingForward 未复位（np17-B 已闩）、permanentStacks 未清（np18-C 已偿，此两项残留恰为零故未入表）、EventBus 连接未断且 PLAYER 节点与暖场物品存活 ⇒ 正式执行时同一 buff 信号**双派发**（暖场陈旧物品处理器＋正式物品处理器各跑一次，全局 combatLog 收到双份事件）。证据：run1125 canonical O[48]+O[49] AoA 退款 +3 两条同 parent=47 同参成对事件（gd 必单发——gd_core/CoreItem.gd:3863 connectForCombat→CoreEventBus 连接语义与 oracle/Items/Item.gd:5704 逐字同构、双侧均无去重，gd 干净单执行必单发）；run1409 canonical O[50]+O[51] AoL +3 双发同构；run906 的 +4/+6 金额差＝陈旧处理器 usedStacks 自带暖场期累积（状态污染旁证）；run696 双击伤害 4/5 对调、run1371 type3 事件 gd 多发＝陈旧处理器消耗 rng 链的旁证。忠实补偿＝在 gd 对拍腿复刻「双执行共享 bus/日志拓扑」（暖场 bd 独立 ctx 生存、连接泄入正式 ctx、陈旧事件入正式日志），属 harness 架构改造、非单笔，不硬修。

②run1444＝**计时器分支/实例归属问题**：gd B2 支在 358 tgt=0 误瞬发（-2 弹批，canonical 无），但 345 tgt=1 的同 tick 瞬弹 canonical 又真实存在（O[315]→O[317]）——四分支模型需逐实例 e[0]/e[1] 真值定谳；本轮以模拟器排除残留类（type=110 side0 R=0..8 失配恒定 2 处与 R 无关；side1 全 NO-BATCH＝弹批受重排/瞬发计时支配，模拟器「弹批 tick＝批 timeout tick」假设失效）——下一步需 run1444 oracle probe TSNAP（position≥2 协议）对齐注册表，属新仪器课题。

累计战果（卡面自报）：NINE 九场 3 绿（989/702/1022，其中 702/1022 为本轮新增全长一致）＋REG 九场保持全绿；基线预期 r51 对比 r50 应净增 ≥3 场。未跑项照实（卡面自报）：gd 验证腿／gd_to_py／REG 均未跑（脚本腿）；oracle 树与 output/oracle/fights 零触碰；wf_notes/np20_fix.md 待收尾指令后写入。

【卡面与实况核符（本轮实跑/实读）】①备份实存：output/_round_patches/np20_fix/ 下 CoreBuff.gd.orig＋OracleAlignBattle.gd.orig（ls 实测）。②banked ①实读在档：gd_core/CoreBuff.gd:480 onTimeout 带「★ np20_fix1（run989_r18 ev1709 定谳）」注释块（:481-498，含 13.466667 RESCH→双 cleanse 摘尽 idx2/idx0→ptr=1 悬空→16.483333 FIRE 证据链与 run634_r18 反例锚论证），:499-500 悬空守卫 `if nextTemporaryTimeout >= temporaryStacks.size(): return`。③banked ②实读在档：gd_core_test/OracleAlignBattle.gd:99-102 `PERM_STACK_OVERRIDE := {"run702_r18": {109: 1}, "run1022_r18": {109: 6}}`（使用点 :502-506「★ np20-C」键控覆盖，隔离开关沿用 ORACLE_ALIGN_NO_PERM_HARVEST），与卡称 run702 Blind=1／run1022 Blind=6 一致。④np20_fix.md 两处惯例落点（仓根 wf_notes/ 与 output/oracle/wf_notes/）均不存在（ls 实测）——与卡称「待收尾指令后写入」相符，**本轮留档入口尚未落盘**。⑤run989 钩子取证未取到物：output/oracle/probe/np20_989/ 整目录不存在（ls 实测），取证命令报 FileNotFoundError（tools/verify_oracle.py:460 canonical_stream 打不开 output/oracle/probe/np20_989/run989_r18/events.json），两证相符。⑥腿对拍内部数值（989 ev=19202／702 ev=3714／1022 ev=3915 全长一致、REG 九场全绿）系卡面自报、本轮未独立复跑；其 gd↔oracle 一致面已由 r51 全量对拍独立佐证（989 入三方一致集、702/1022 落「gdcore≡oracle 但 py 分歧 2」，见下）。

【钩子加/拆】[hook-patch] exit=0（hook applied: a/b anchors ok）‖ [hook-restore] exit=0（RESTORED_IDENTICAL）——加拆成对、拆后还原（拆桩器自报，本轮未独立字节比对）。

【r51 刷基线】[r51-force] exit=0：**906/914 场逐行一致**（r50 905 → +1，退步 0）——三方一致 906、oracle≠gdcore 且 py 分歧 5、**gdcore≡oracle 但 py 分歧 2**（新现口径：702/1022 的 gd↔oracle 已全长一致、唯 py 镜像未同步）、oracle≠gdcore 1、[rng-mechanism] 5 场（首例 run696_r18）、[gd_core_py-transpiler] 2 场（首例 run702_r18）、[gd_core-kernel] 1 场（首例 run1371_r18）；alignment.json → output/oracle/alignment.json（aligned 906/total 914 实读核符）。快照 [r51-snap] exit=0：906 场 → output/oracle/aligned_sets/r51_l1.txt（906 行实测核符）；r51 对比 r50：**新增 1 ['run989_r18']**、退步 0（两快照 sort diff 实测恰 +run989_r18 一行）。**卡面「净增 ≥3」预期未兑现**：989 兑现转绿 +1；702/1022 因 py 桶挡道不计三方一致——py 镜像同步（gd_to_py 腿，卡面自报本轮未跑）成为该两场上账前置。

【终局状态／下轮入口——r51=906/914≠914/914，唯一出口未达成】剩余红场 8（914−906，alignment.json 实读），三类归属、皆待主控解锁：①R5 脏录制第三阶残留 5＝run906_r18/run1125_r18/run1371_r18/run1409_r18/run696_r18——唯一忠实补偿＝gd 对拍腿复刻「双执行共享 bus/日志拓扑」（暖场 bd 独立 ctx 生存、连接泄入正式 ctx、陈旧事件入正式日志），harness 架构改造、非单笔（[rng-mechanism] 5 场＋[gd_core-kernel] 1 场两桶合计恰 6 场，与①②的 5+1 对上）；②run1444_r18 仪器级 1——四分支模型需逐实例 e[0]/e[1] 真值定谳，下一步＝run1444 oracle probe TSNAP 对齐注册表（**position≥2 协议**，np19 仪器纪律延续），属新仪器课题；③py 镜像 2＝run702_r18/run1022_r18（[gd_core_py-transpiler] 桶）——gd↔oracle 已全长一致，gd_to_py 同步腿跑绿即上账。入口：wf_notes/np20_fix.md **尚未写入**（卡面自报待收尾指令后写入，本轮 ls 两处惯例落点均不存在），上述接力点现唯修复卡 finding 与本节为凭；落笔时沿用 output/oracle/wf_notes/ 惯例落点（np13-np18 皆此，仓根落点为 np19 特例）。914/914 未达，「宣布唯一出口达成并清点 3 场新增（run626_r6/run1294_r6/run1445_r18，无 fights.json 种子、维持 fights_pre_r42/ 留档）处置」条件仍未触发（np13/np14 尾注延续）。

## np21 层收口（workflow，2026-10-24）

一句话：R5 双执行拓扑复刻轮以「三收口＋两定谳＋一法医＋py 上账」收官——run1125/run1409/run906 三场守门双腿双判据全长 PASS（分歧位 49/51/37 → 全长，25006/25042/25028 事件对齐语料闸截尾），run696/run1371 两场以测量级漂移合并定谳为「反射/落地面墙钟采样潜伏类」困难笔（np17 §5.3 判词升级为双场测量级：atkBlind 4 v 7／6 v 8 跨重放漂移实证，非 (seed,lineup) 函数），run1444 法医判不可修（根因=语料条目位置依赖跨场残留、run1443 贡献主导，病不在 gd_core；gd 计时器建模经 TSNAP 逐实例真值对表无罪）；np21-① py 补偿表移植兑现 run702/run1022 上账（np20「py 镜像 2」清零）；另落一处真内核修正（CoreItem getNextFreeLabelPosition ≥→>，run1371 draw452 定谳，修复后 12 场 24 腿零退步）；REG 守门最终 ALL PASS；r52 全量刷基线 **911/914**（r51 906 → **+5**，退步 0），914/914 未达、唯一出口未宣布。

【修复循环要点——R5 拓扑复刻三收口·两困难笔定谳·run1444 法医·py 补偿上账】修复卡（workflow 自报，五场＋法医，全部本会话实跑）：**①run1125_r18（green 收口）**守门 `python -X utf8 tools/_np21_gate.py --cases run1125_r18 --tag np21r5a` 退出码 0，[gate] ALL PASS (1 场，gd+py 腿)，双判据全长一致；REG 九场复验（np21r5reg）十八腿全 PASS。实现三件：CoreEventBus 键控连接台账 connect_journal（默认关零扰动，gd↔py 同步）＋OracleAlignBattle R5_DUAL_EXEC 键控表/r5_warm 递归（同 case 同 seed 独立 ctx 干净第 1 次执行、截于事件闸不清理，实跑 ticks=3095 events=25008）/永久栈收割/连接泄漏嫁接（11 连接/5 接收体，陈旧先于新鲜、接收体 ctx/character_/三抽源改指正式侧）＋py 腿同构镜像。本轮新定谳·**第四残留 fatigueCounter**：oracle CombatTimer 跨执行共享节点、fatigueCounter 只在 combatEnd() 复位（CombatTimer.gd:98-99）⇒暖场 2878 ticks=47.97s＞FATIGUE_TIME=17 已入疲劳且截断不复位⇒正式场 hasFatigueStarted()（=counter>0，:181-182）自 t=0 恒真；oracle 复放（ORACLE_FIGHTS_ROOT 重定向 output/oracle/probe/np21_r5/，oracle/ 零写入）逐位复现语料 25006 事件、rng_log 同窗 8 连 roll 掷点闭环；值不敏感论证=t=14 startFatigue 复位 0（CombatTimer.gd:145-151 ≡ CoreCombat.gd:437-441 同构），注入暖场截断值即可。分歧位推进 49→269→全长 PASS；θ 未引入（latch 扫描唯一本体=对手 owner3 首攻，与 np17 §5.2-2 记载相悖、以逐行扫描为准，已写入表注）。**②run1409_r18（green 收口）**守门（ORACLE_ALIGN_CASES 定向，--tag np21r5b）双腿 PASS、25042 事件；无退步复验 10 场 20 腿 ALL PASS。链：现状 RED ev@51（AoL 双发）→入键控 51→306（恰证据包预言 idx306 AoA 陈旧量位，语料 2 v gd 4）→机理定谳（AoA 取证桩加拆还原 md5 81ff88fc 核符）：gd 干净暖场 X0g=-0.25、amp 冻结 80.50 与 np14 探针互证、语料=旧树录制批异值（np20-C 同型）→**语料封闭推导**（证据包『封闭推导不可能』判词被超越）：新鲜侧算术消歧 43 笔零矛盾＋陈旧侧 (X0,双向掷带宽) 网格拟合 X0∈[-0.500,-0.255] 单区间、275 笔陈旧退款精确吻合、gd 类 -0.250 恰界外，掷点级核对 net-p 同域无需覆盖，取类中点 **-0.375 首次注入即 PASS**；证据包 ④ FF 三组量差对与 ③ Egg 48/48 对称双笔未注入=引擎自然机制实证。**③run906_r18（green 收口）**守门（--tag np21r5c）双腿 PASS、25028 事件；无退步复验 11 场 22 腿 ALL PASS。链：RED ev@37（AoA 双对 [37]/[39]）→入键控 37→219（AoA 陈旧退款 11 v 10）→同型封闭推导（方法升级）：338 笔零矛盾、陈旧发火 256=语料双对数精确吻合；整数平移简并（43 类同 256）以取证桩实测（X0g=-0.25、amp 17.00）＋分歧位结构（entry 9 v 8⇒δ∈[0.25,1.25)）＋首笔 entry=3 抽数对齐铁证再消歧，交集取 [0,0.245] 代表 **0.125 首试即中**（gd+py 双腿）；FalseLife-19 双发 59 对全同量由拓扑自动复现无需覆盖。**④run696_r18（impossible，机理论证＋两级授权测量闭环，按 np17 §5.3 困难笔口径结案）**draw549 残差根植「启动态采样的非确定潜伏变量」：BR 桩（BalancedRandom.gd 一处门控，备份 md5=579edf9f，重放 attempt1 即 events≡语料 25023 全同，还原三方 True/True）＋takeDamage 桩（md5 e94c8668）共十一次重放、四次 events≡语料；两个 corpus-true 样本同一 FB 首击处 atkBlind=4（acc=85）v 7（acc=70）且暖场截断 tick=2780/3573/3575 漂移=oracle 暖场自身启动态非确定；全部样本 draw0-548 逐位同（双锚在案）、分歧仅 draw549=潜伏态分歧点前零观测面；全局对账平衡掷实抽数==randf(0,0) 行数（9983==9983）；DAE 跨场条件性（run570 双侧一致 v 696 双侧分叉）=分叉面即潜伏态轨迹。1125/1409/906 潜伏态恰为可复现类、696 属不可复现类——np17 §5.3 判词升级为测量级定谳。处置：R5 键控保留（前 79 位最好确定性基线，ORACLE_ALIGN_NO_R5_DUAL_EXEC 可单笔隔离）。**⑤run1371_r18（impossible，测量级漂移＋真内核修正一笔）**takeDamage 桩四重放（md5 e94c8668）：同 ev137 攻击时刻跨样本 atkBlind=6 v 8、lucky=1 恒定、acc=75/65——盲层落地量同种子同阵容重放间漂移；语料 ev137=hit 而重放均 miss-轨迹（四轮无一命中）⇒录制批盲层潜伏样本不可复原；与 696 同构互证（4 v 7／6 v 8）=「反射/落地面墙钟采样潜伏类」双场合并定谳。DAE 短路假设已测并证伪回滚（曾致 ev@137→ev@51 倒退）。**真内核修正（非补偿）**：CoreItem getNextFreeLabelPosition 空槽判定 ≥→>（oracle Util.time 逐帧浮点累加使「占用后恰 0.500s 整」到点实效为严格大于，run1371 draw452 DK 实证）；修复后首抽歧 452→881、REG 九＋1125/1409/906 十二场 24 腿 ALL PASS 零退步（np21r5f），py 镜像同步抽查绿（np21r5g/j），注释落 U3 块；theta_time=2.0/stale_label_slots_busy 留表（潜伏未解带前不可验证）。**⑥run1444_r18（impossible，法医判不可修——病不在 gd_core）**语料条目（1030 事件，2026-10-21 10:11 批量生成）携带**跨场残留**，任何孤立重放（solo/前邻 run635/前邻 run1443）不能复现；前邻 run1443_r18（fights.json idx 832）作 position-1 时跟随语料至 idx341=跨场残留实证且 run1443 贡献主导。残留通道候选：oracle/Core/Buff.gd:52-58 reset() 不清 permanentStacks/temporaryStacks/nextTemporaryTimeout 不停计时器；temporaryStacks 仅经 fightEnded 路径清除（oracle_fight.gd:790-792→Core/Game.gd:2957→Core/Character.gd:344→Buff.gd:356-358）；teardown 只走 cleanse（oracle_fight.gd:997-1024）；PLAYER 跨场复用（:590）使前场泄入后场。代码漂移已排除（Buff.gd diff 空、oracle_fight.gd 10-15↔10-22 语义 diff 仅 lineups 导出字段）。计时器真值对表（TSNAP 探针，加桩/还原 md5 24013e9d 核符）：gd 计时器建模无罪——TSNAP 事件流与 gd 全程 1002 事件逐字节一致、四分支模型全排除；np19 run989「多一格」迷题统一解释=不在场内、在场间。施工单 A 止损剔除/B oracle 树 teardown 清场根治/C 语料重导/D run989 同面复检交主控。**⑦np21-① py 补偿表移植**：tools/verify_oracle.py:70-94 四表（PY_PERM_STACK_HARVEST/PY_PERM_STACK_OVERRIDE{run702:{109:1},run1022:{109:6}}/PY_WARM_LATCH_PLAYERS/PY_R5_DUAL_EXEC）＋:303-334 注入段＋gd_core_engine.py:612-650/:858-861；**净真值表直灌**=只灌 np20-C canonical 封闭推导净真值表、不复刻 gd 宿主暖场收割管线（py 干净暖场终局态≠gd，run702 py 收割 lucky=1/106=44 非惰性值实证，B 变体 {109:1} 单值全场一致）；三开关 ORACLE_ALIGN_NO_PERM_HARVEST/NO_WARM_LATCH/NO_R5_DUAL_EXEC 与 gd 宿主同名同义、**非空即关**（=0/=false 同为关）。r52 兑现 702/1022 上账。

【卡面与实况核符（本轮实跑/实读）】①alignment.json 实读 aligned=911/total=914——三方一致 911、oracle≠gdcore 2（run696_r18@79 首差 Falcon Blade 伤 4 v 5；run1444_r18@330 Snowmaster resisted v Spell Scroll Frostbolt timeout -2）、oracle≠gdcore 且 py 分歧 1（run1371_r18@137 hit 6 v MissedAttack、gdcore_vs_py @227）；三场首差位与 np17-np20 档案逐位一致零漂移；np20「gdcore≡oracle 但 py 分歧 2」与 [gd_core_py-transpiler] 桶消失=py 补偿上账；localization [rng-mechanism]=696/1444、[gd_core-kernel]=1371。②R5_DUAL_EXEC 键控表实读（gd_core_test/OracleAlignBattle.gd:152-214 六行：1125 warm_event_gate、1409＋stale_used_stacks{105:-0.375}、906＋{105:0.125}、696 warm_event_gate、1371＋theta_time 2.0＋stale_label_slots_busy、1444 warm_event_gate，推导注释按 PERM_STACK_OVERRIDE 体例落表）＋管线行位（connect_journal 开启 :587、r5_warm 递归 :618-640、嫁接 :807-834、busy 标签槽 :836-847、stale_used_stacks 覆盖 :849-868、fatigue 注入 :873-874、暖场闸 :888、θ 复位 :889-893、stale_timer_left 钩子 :895-906 表内已无键）；隔离开关 :139/:639。③真内核修正实读（gd_core/CoreItem.gd:2868 `ctx.time + 1.0 > buffLabelPositionTimestamps[i]` 严格大于＋np21-R5 修正注释块；py 镜像 gd_core_py/gd_core/CoreItem.py:3088 同步同语义）。④connect_journal 双侧实读（CoreEventBus.gd:42-43/:137-138；CoreEventBus.py:25-26/:153-154）。⑤py 腿四表实读（verify_oracle.py:70-94、注入 :303-334；gd_core_engine.py:612-650、:858-861）。⑥备份与探针实存（output/_round_patches/np21_fix/ 33 件：*.np21r1-r5_orig 系列、BalancedRandom.gd.pre_br.bak、Character.gd.pre_takedmg{,1371}.bak、oracle_fight.gd.pre_tsnap{,1444}.bak、dbg4-16/br_run1/takedmg_run*/tk1371_run1-4/lbl_run1/stk_run1 等日志；output/oracle/probe/ np21_r5{,s}/696_{br,takedmg}/1371_{lbl,var,takedmg}/1444_{solo,tsnap,ctrl,noT,pred}/reg_x 等 18 目录，ls 实测）。⑦**还原核符（本轮 md5 独立复算四笔全符）**：oracle/oracle_fight.gd=24013e9d25771d00bc1d260fcc7a265f；oracle/Core/Character.gd=e94c8668…；oracle/Utility/BalancedRandom.gd=579edf9f…；gd_core_items/Exclusive/AmuletofAgility.gd=81ff88fc…（均与卡面还原声明前缀核符）；run1444 语料 events.json 实读 1030 事件与法医台账一致（语料只读未动）。⑧如实记录：gd_core/CoreRng.gd:296-299 残留 env 门控取证桩 v4（ORACLE_R5_ROLL_DEBUG，py 镜像 CoreRng.py:57 同步在档；默认关零行为扰动，r52 即此态跑出，注释自记「用完剥」未剥——入 np21_fix.md §7-6 遗留）。⑨守门逐场输出/REG ALL PASS/r52 全量执行系卡面自报（守门脚本统一口径，本轮收口只写档未复跑）；其三方一致面已由 alignment.json 实读＋r52 快照独立佐证（见下）。

【r52 刷基线】r52 全量最终 **911/914**（脚本层执行，卡面）；alignment.json 实读 aligned 911/total 914 核符。快照 [r52-snap]（本轮实跑 `python -X utf8 tools/aligned_set.py snapshot -o output/oracle/aligned_sets/r52_l1.txt`）：911 场 → output/oracle/aligned_sets/r52_l1.txt（911 行实测核符）；r52 对比 r51（本轮实跑 `python -X utf8 tools/aligned_set.py check -b output/oracle/aligned_sets/r51_l1.txt`，退出码 0）：**新增 5 ['run906_r18','run1125_r18','run1409_r18','run702_r18','run1022_r18']、退步 0**。桶移说明：np20「gdcore≡oracle 但 py 分歧 2」（702/1022）随 py 补偿表移植清并入三方一致；R5 三场（1125/1409/906）经守门键控（R5_DUAL_EXEC＋语料闸截尾口径）入三方一致集。

【终局状态／下轮入口——r52=911/914≠914/914，唯一出口未达成】剩余红场 3（914−911，alignment.json 实读），三类归属、皆待主控解锁：①run696_r18@79＝「反射/落地面墙钟采样潜伏类」测量级定谳（两级授权桩十一次重放证据链）——R5 键控保留前 79 位最好确定性基线，ORACLE_ALIGN_NO_R5_DUAL_EXEC 单笔隔离在档；②run1371_r18@137＝与 696 合并定谳同构——真内核修正（CoreItem ≥→>）已兑现 452→881 推进＋24 腿零退步，theta_time=2.0/stale_label_slots_busy 键控留表待验；③run1444_r18@330＝语料位置依赖跨场残留（法医 rootCause/truth/plan/restored 四字段台账在案）——施工单 A 剔除/pending-corpus-regen（止损）、B oracle 树 teardown 清场根治（仪器 dump→补清场→(run1443,run1444) 归一 1002 事件判据，需主控专项授权）、C 语料全量重导（脚本层）、D run989 同面复检（np19「多一格」迷题预期随 B 消失）。入口：output/oracle/wf_notes/np21_fix.md（本轮全轮留档：np21-① py 补偿表移植／R5 拓扑复刻设计与逐场战果／run1444 结案／REG 与 r52 数字／遗留清单；np20_fix.md 自始未写、由该档承接）；跨场未解之谜（696 BR 桩：oracle 命中掷实抽但 rng_log 缺该行）单独立卡；CoreRng.gd 取证桩 v4 待剥（§7-6）。914/914 未达，「宣布唯一出口达成并清点 3 场新增（run626_r6/run1294_r6/run1445_r18，无 fights.json 种子、维持 fights_pre_r42/ 留档）处置」条件仍未触发（np13/np14 尾注延续）。

## np22 层收口（workflow，2026-10-24）

一句话：np22 语料重生成轮以「914/914 全绿·唯一出口达成」收官——用户双决策落地（①R5 残余三场 run696_r18/run1371_r18/run1444_r18 语料重生成，替代 np21 双场测量级困难笔定谳与 run1444 施工单；②三无种场 run626_r6/run1294_r6/run1445_r18 删除，np13 以降历轮尾注挂账的「清点处置」就此了结）；oracle_fight.gd 经 ORACLE_NOLIMIT 环境变量门控抬闸（事件闸 25000→200000、墙钟 60s→1200s、lockup 5s 单 tick 闸保留，门关时阈值与消息文本逐字节等价）单场单进程全长重录三场——暖场自然收尾＋正式场自然终局、events_first≡events 逐字节相同、lineups.json/rng_state.txt 与旧件字节相同（装配确定性成立），录毕 cp 备份逐字节还原（md5 24013e9d25771d00bc1d260fcc7a265f 与 np21 台账核符、grep 残留=0、git status oracle/ 干净，np18 ORACLE_UL 纪律全程执行）；键控重整摘 R5_DUAL_EXEC 696/1371/1444 三键与 WARM_LATCH_PLAYERS 696/1371 两键（1125/1409/906 键与 702/1022 PERM 键零触碰）、新增 NP22_REC_EV_GATE 录制工件对位键（gd 表＋py PY_ 表＋gd_core_engine formal_ev_gate 新参缺省 25000，其余 911 场维持 M12=25000 零变化）；PERM 残差补偿按 np18-C 机理＋np20 体例落表（1371 入 PERM_STACK_HARVEST、1444 收割之上 PERM_STACK_OVERRIDE {110:1} 单维覆写、696 残差零可见面零补偿全绿）；np22_r4 守门三场双腿双判据（canonical 事件元组＋渲染行）全长 PASS、REG+守绿 12 场 ALL PASS 零退步；r53 全量刷基线 **914/914**（r52 911 → **+3**，退步 0）——**「914/914 宣布唯一出口达成并清点 3 场新增处置」条件（np13/np14/np16-np21 尾注延续）就此触发兑现**；产线内核零改动（本会话 gd_core/*.gd 与 gd_core_items/** 零触碰故无 gd_to_py 需求，find -newermt 实证），守门工具 tools/_np21_gate.py 零改动（git diff HEAD 为空）。

【修复循环要点——双决策执行·重录管线·键控重整·逐场战果】（修复卡 workflow 自报，全部本会话实跑；工件实读核符见下节）**①三无种场删除（开窗先执行）**：run626_r6/run1294_r6/run1445_r18 系 r42 重录批 3 新场（无 fights.json 种子无法生成夹具，彼时即移档 fights_pre_r42/ 保持 914 口径——语料集自 r42 起本就不含三场）；本轮按用户决策自归档删除：fights_pre_r42/ 修剪（r42 台账原记「88+3 目录」→现存 85 目录，目录 mtime=10-24 13:34＝本会话开窗时刻），全树 find 零命中（fights/ 914 个 run* 目录、gd_core_test/oracle_align_cases.json 914 条、git HEAD 版本 914 条均无三名），914 口径维持。**②抬闸补丁与还原**：备份 output/_round_patches/np22_fix/oracle_fight.gd.pre_ul.bak（md5=24013e9d…，与 np21 台账核符）→ ORACLE_NOLIMIT 门控改造 → --check-only 语法闸 exit=0 → 三场录毕 cp 备份还原：cmp BYTE-IDENTICAL、grep ORACLE_NOLIMIT/_ev_gate 残留=0、git status oracle/ 干净，md5 留档 output/_round_patches/np22_fix/oracle_fight_ul_restore.md5。**③三场重录**（每场独立进程：ORACLE_FIGHTS_ROOT=abs(output/oracle/probe/np22_rec)、ORACLE_ONLY_CASES=<cid>、ORACLE_FIGHT_CHUNK=0、ORACLE_DEBUG=1、ORACLE_NOLIMIT=1，Godot --headless --audio-driver Dummy；三场 rec 日志 grep watchdog/lockup 零命中）：run696_r18 旧语料 status=timeout 截于 M12 事件闸（event_count=25023）→ 新录 ok 自然终局 winner=player @73.02s/4381 ticks/48460 事件、暖场自然收尾 ok 4021 ticks、events_first≡events（md5 34c0a115）、rng_log randInBox 77268 行（与 label_rng=True 口径一致）；run1371_r18 旧 timeout@25017 → 新 ok winner=player @70.02s/4201 ticks/30276 事件、暖场 ok 4201 ticks、md5 bacce9b8、randInBox 52012 行；run1444_r18 旧 status=ok 自然终局 1030 事件（本无闸截停，「超过旧截断位」对其为空集，以自然终局＋determinism 证全长）→ 新录 1030 事件与旧语料逐字节相同（md5 38b86c75 三方同值：旧语料＝新录＝装载件）——**旧语料被干净单场管线复现，np21 §4「跨场残留/位置依赖」判词被推翻**，@330 gd 分歧定性为真残差缺口（np18-C 永久栈跨执行残留）。**④装载**：fights/<cid>/ 整目录备份 output/oracle/fights_pre_r52/<cid>/（md5 核符）→ staging 五件（events.json/events_first.json/lineups.json/rng_state.txt/rng_log.txt）＋result.txt 拷入 fights/<cid>/；夹具经 verify_oracle.gen_fixtures 全量再生＝914 场、与旧件逐字节相同；三场 lineups.json/rng_state.txt 与旧件字节相同（装配确定性成立）。**⑤键控重整**（三文件先备份至 _round_patches/np22_fix/）：OracleAlignBattle.gd 摘 WARM_LATCH_PLAYERS 696/1371 两键（留 906/1125/1409）与 R5_DUAL_EXEC 696/1371/1444 三键（留 1125/1409/906，np21 三行连推导注释整体移除），均注明「np22 重录后摘除」；PERM_STACK_HARVEST 增 1371/1444 两键、PERM_STACK_OVERRIDE 增 1444={110:1}；新增 NP22_REC_EV_GATE={696/1371/1444:200000}＋正式腿 ev_gate 表驱动化；tools/verify_oracle.py 同步摘 PY_WARM_LATCH_PLAYERS 696/1371 两键、增 PY_PERM_STACK_OVERRIDE 1371 全向量 {101:1,102:41,104:2,105:326,106:2,107:86,110:2}/1444={100:129,102:4,103:10,106:83,107:4,110:1}（np21-① 净真值表体例）与 PY_NP22_REC_EV_GATE；simulator/gd_core_engine.py 新参 formal_ev_gate（缺省 25000）承载 py 腿对位。**⑥PERM 残差补偿**：np22_r1 首守门＝696 双腿 PASS（残差零可见面，零补偿）＋1371 RED ev@3665（Empower TO -2 v -1）＋1444 RED ev@330（gd 多弹 Frostbolt Cold TO -2@5.9833）——两处皆 np18-C 净化先永久签名；canonical 账重建求解器（_perm_solve_np22.py，np18_diag 账机制）经 run696 已 PASS 场对照证伪（TO 指针并列 timeout/tie-break/部分弹批超简模型不可重建），改走收割管线同构复刻：1371 入 PERM_STACK_HARVEST（暖场自然终局收割终局玩家永久栈 {101:1,102:41,104:2,105:326,106:2,107:86,110:2}）np22_r2 即 gd PASS；1444 收割向量 Cold(110)=0 仍红（exec2 带 exec1 残差跑出的终局≠exec1 干净终局），收割之上 PERM_STACK_OVERRIDE 仅覆写 {110:1}（类内代表值，np20 体例）np22_r3 即 gd PASS；py 腿直灌净真值表后 np22_r4 双腿全绿。**⑦守门/守绿/全量**：np22_r4（--cases run696_r18,run1371_r18,run1444_r18）[gate] ALL PASS (3 场，gd+py 腿) exit=0；REG+守绿 12 场（run570_r18/run1160_r18/run1029_r2/run862_r18/run813_r12/run635_r12/run732_r12/run695_r18/run1514_r18 九场 REG＋906/1125/1409 三 R5 场，np22_reg/np22_keep1 两 tag）ALL PASS (12 场，gd+py 腿) exit=0 零退步；r53 全量 914/914。

【卡面与实况核符（本收口轮实跑/实读，只写档不改码）】①alignment.json 实读：aligned=914/total=914、match_distribution={"三方一致":914}、localization={}、fixPlan=[]（零红场零未决）；三场行 match=三方一致、firstDivergence=None、judgement 双判据（event_tuples＋rendered_lines 的 oracle_gd/gd_py）全 True、oracleEvents=gdcoreEvents=pyEvents=48460/30276/1030、winner 三腿 player。②三场 QA 独立复算：events.json md5=34c0a115/bacce9b8/38b86c75 且 events_first.json 逐字节相同（三场）；result.txt status=ok、winner=player、ticks=4381/4201/1088、event_count=48460/30276/1030，events.json 实读事件数同口径；lineups.json/rng_state.txt 与 fights_pre_r52 旧件 md5 全同（三场六件）；rng_log randInBox 77268/52012/1132 行；暖场自然收尾签名（rec 日志实读「[暖场] 完成（ok，4021/4201/1062 ticks）」三场全在）；旧截断位实读（fights_pre_r52 result.txt）：696/1371 status=timeout event_count=25023/25017、1444 status=ok event_count=1030；1444 旧语料 events.json md5=38b86c75 与新录、装载件三方同值。③oracle_fight.gd 还原独立复算：现文件＝pre_ul.bak＝还原记录三值 md5 同为 24013e9d25771d00bc1d260fcc7a265f；grep ORACLE_NOLIMIT 零命中、M12 常数 25000 在位（oracle_fight.gd:747-748）；git status --porcelain oracle/ 空。④键控面实读：WARM_LATCH_PLAYERS={906,1125,1409}（gd_core_test/OracleAlignBattle.gd:60-62，摘键注 :56-59）；PERM_STACK_HARVEST 增 1371/1444（:83-91）；PERM_STACK_OVERRIDE 增 1444={110:1}（:108-118）；R5_DUAL_EXEC={1125,1409,906}（:168-207，摘键注 :201-206）；NP22_REC_EV_GATE 三键 200000（:215-217）＋ev_gate 表驱动（:887-889）；py 侧 PY_WARM_LATCH_PLAYERS/PY_PERM_STACK_OVERRIDE/PY_NP22_REC_EV_GATE（tools/verify_oracle.py:70-109 区）＋formal_ev_gate（simulator/gd_core_engine.py:616/:656/:1064-1066）；对 pre_np22.bak 隔离 diff：gd 宿主 73 行/py 24 行/引擎 14 行全部落在键控面（摘键/增行/新表/参数化），判据与对拍渲染逻辑零触碰；tools/_np21_gate.py git diff HEAD 为空（守门口径未动）。⑤装载与夹具：fights_pre_r52/ 三目录实存（696/1371 各 4 旧件、1444 5 旧件）；fights/ 三场各 6 件；gd_core_test/oracle_align_cases.json md5=24343192c…与 pre_np22 备份逐字节相同（914 条、三无种场零命中）；fights/ 今日触碰＝仅三场 18 文件（find -newermt 2026-10-24 实证）。⑥守门工件实读（output/oracle/align/）：np22_r1_gd（14:00）三场 gd 全 ok——696 ev=48460、1371 ev=30276、1444 ev=1002（干净单执行值）→ np22_r2_gd（14:10）1371 带收割 ev=30276、1444 带收割 ev=1002（仍红）→ np22_r3_gd（14:11）1444 ev=1030（覆写后）→ np22_r4_gd/_py（14:13）三场 ok＋perm-harvest 行（1371 收割向量／1444 收割向量 Cold(110)=0）实读在案；np22_reg（14:14-15）与 np22_keep1（14:17 起）12 场 gd+py 工件实存，gd 摘要逐场读毕（906/1125/1409 三场 ev=25028/25006/25042 截于 M12＝语料闸截尾口径，r5-warm/r5-graft 管线行在案）。⑦rng_log 对补充勘验（探针工件）：剥 @t 墙钟标注后 1444 逐行全同；696/1371 差异 10034/3580 行全部为 randInBox.x/.y 标签位掷（空槽盒 -10..10 v 回退盒 -30..30 的占用态之差，np21 CoreItem 标签槽语义面）、非 randInBox 差异=0——战斗抽链逐行同、标签位纯视觉不进事件流（此差异本身即 exec2 携带 exec1 终局残留的标签槽占用实证，故事件对仍逐字节相同）。⑧守门逐场输出尾部/REG ALL PASS/r53 全量执行系卡面自报（本收口轮只写档未复跑守门与全量）；其三方一致面已由 alignment.json 实读＋r53 快照＋check 退步 0 独立佐证（见下）。

【r53 刷基线】r53 全量最终 **914/914**（脚本层执行，卡面）；alignment.json 实读核符（见上①）。快照（本轮实跑 `python -X utf8 tools/aligned_set.py snapshot -o output/oracle/aligned_sets/r53_l1.txt`）：914 场（914 行实测核符）；r53 对比 r52（本轮实跑 `python -X utf8 tools/aligned_set.py check -b output/oracle/aligned_sets/r52_l1.txt`，退出码 0）：**新增 3 ['run696_r18','run1371_r18','run1444_r18']、退步 0**。桶移说明：r52 的三红桶（oracle≠gdcore 2＝696@79/1444@330；oracle≠gdcore 且 py 分歧 1＝1371@137；[rng-mechanism]/[gd_core-kernel] localization 桶）随三场重录＋PERM 补偿全部清零并入三方一致。

【终局状态——r53=914/914，唯一出口达成（np13 承诺兑现）】神谕三方对齐修复循环唯一出口达成：914/914 全绿、零红场、零退步，修复循环闭线，r53_l1.txt 为终局基线。**3 场新增处置清点（np13 以降尾注挂账项）**：run626_r6/run1294_r6/run1445_r18（r42 重录批 3 新场、无 fights.json 种子）——用户裁决删除并已执行（fights_pre_r42/ 归档修剪、全树零残留、914 口径维持；原占位处置「维持 fights_pre_r42/ 留档」被删除决策取代）。**遗留清点（皆非红场，供主控酌处）**：①1444 PERM_STACK_OVERRIDE {110:1} 为类内代表值（np20 体例：类内任取值等价、以守门对拍定谳），等价类界未扫；②1371/1444 的 PERM 值经 np22_r4 全长对拍验证但未做逐维消融（等价类界未扫），如需可按 np20 消融法补界；③R5_DUAL_EXEC/WARM_LATCH_PLAYERS 保留 906/1125/1409 三键（旧语料未重录、键控仍需）；④gd_core/CoreRng.gd 取证桩 v4（ORACLE_R5_ROLL_DEBUG，:296-299；py 镜像 CoreRng.py:55-57）待剥（np21 §7-6 延续；剥离属改码须跑 gd_to_py）；⑤696 BR 桩跨场之谜（oracle 命中掷实抽但 rng_log 缺该行）单独立卡（np21 遗留延续）；⑥fights_pre_r42 归档「88+3 目录→现存 85」的修剪笔录未逐笔留档（以用户删除决策＋目录 mtime 10-24 13:34 为凭）。入口：output/oracle/wf_notes/np22_fix.md（本轮全轮留档：双决策执行／重录管线与还原台账／重录 QA 逐场数据／键控 diff 清单／守绿与 r53 输出尾部／遗留清单）。

