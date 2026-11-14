# A 阶段修复报告 — 22 场开关的两处真因与普适性修复

> 日期：2026-11-14　|　执行：按《普适性修复与内核迁移规划_ABC.md》A 阶段
> 结论先行：**22 场开关的真实根因只有两个**，均已在内核层修复，
> `gd_core_test/oracle_align_case_overrides.json` 清空为 `{}` 后全部对齐。

## 0 结果速览

| 项 | 修复前 | 修复后 |
|---|---|---|
| 22 场开关场（清空 override 表） | 大面积红 | **22/22 三方一致**（`output/_a1/alignment_22_final.json`） |
| 60 场快闸（清空 override 表） | 59/60（run101354 红） | **60/60 三方一致**（`output/perf/alignment_core_noov_final.json`） |
| 1690 全量（清空 override 表） | 依赖 22 场开关 | 见本文 §5（无开关验收） |
| 开关机制代码 | 6 个 env 门控散布四内核 | **全部删除**（py/gd/cpp 三腿行为零变化，实证见 §4） |

## 1 真因一：Coins 类「无根脚本覆盖」场景的装配多抽（20 场 flk_delay + run604585 + run300219）

### 1.1 机制（oracle [BARE]+[ITEMINIT] 全裸流取证实证）

Godot 3.6 场景继承的脚本覆盖会让**成员初始化器在该层重跑一遍**：

- `LeatherBag.tscn`（instance=Item.tscn，根节点 `script = Bag.gd`）：
  成员初始化器跑两遍（基 Item.gd 一遍 + 覆盖脚本一遍）→ 装配期抽 **2** 笔
  `randf_range(0.2,-0.2)`（BalancedRng ctor）。
- `Coins.tscn`（instance=Item.tscn，**根节点无 script 覆盖**，只有
  AutoHideParticles 子节点脚本）：基脚本绑定保留 → 只抽 **1** 笔。

全 651 个继承场景扫描（oracle/Items 递归）：无根脚本覆盖的**战斗物品只有
Coins 一件**（其余 132 个是 `*Animation`/RecipeBook 等非战斗场景）。

### 1.2 后果

旧内核模型（四腿一致）＝「每实例恒 2 抽 + 宝石 sceneDepth 补差」：
含 Coins 的场装配链位整体后移 **2 PCG 步（1 笔）** → 装配期抽出的
FlickerAnimation delay 值错位 → 战斗期 playAni 发火窗漂移 → 事件流分叉。
rng_state 注入只抹平装配期**终点**状态，抹不平「装配期抽出的 delay 值」
这一泄漏进战斗期的装配产物，故 20 场 flk_delay 逐场写死 delay 值。

### 1.3 修复

| 层 | 文件 | 修改 |
|---|---|---|
| 数据 | `tools/enrich_scene_depth.py` | 深度语义改为**脚本重绑定次数**：继承场景只有根节点写 `script = ExtResource(n)` 才 +1 层（Coins=1，宝石链=3） |
| 数据 | `assets/battle_items.json`、`assets/gd_core_runtime.json`、`gd_core_test/item_battle_fixture.json`、`native_sim_cpp/assets/gd_core_runtime.json` | Coins `scene_depth/sceneDepth` 2→1（重生成/同步） |
| py 内核 | `gd_core_py/gd_core/CoreItem.py setup()` | 抽数 = `1 + max(0, sceneDepth-1)`（原 `2 + max(0, sceneDepth-2)`）；已重编 .pyd |
| gd 内核 | `gd_core/CoreItem.gd`、`gd_core_test/gd_core/CoreItem.gd`、`native_sim_cpp/gd_core/CoreItem.gd` | 同上 |
| C++ 内核 | `native_sim_cpp/native_sim/gen/shards/shard_00.cpp`（生成代码手工修复） | 删第二笔无条件 ctor 抽 + range 上界 2→1 |

### 1.4 证据链

- oracle 重放取证（`tools/_a1_oracle_bare_case.py`，ORACLE_BARELOG+FLKPROBE+ITEMMARK）：
  run101354_r14 装配 262 笔/528 步（py 修前 265 笔/530 步，多 1 笔 ctor，
  SequenceMatcher 定位=Coins 窗口）；[FLKD] Burning Coal/ot3 delay=2.2284
  重放确定性复现（含暖场三次同值）。
- 步数闭合：set_seed → rng_state 反推 = 528 步；py 修复后装配 528 步逐位对齐
  （`tools/_a1_measure_asm_steps.py`：5 场 asm_delta 全 0，与「阵容含 Coins」完全相关）。
- run101354 无开关重放：py=gd=oracle=671 事件、winner=opponent、逐行一致。

## 2 真因二：CoreTimer 相位补偿违反 harness 登记拍语义（run704242）

### 2.1 机制（oracle drive_timers 源码 + [timer-reg]/[timer-poll] 探针实证）

oracle harness `drive_timers`（oracle_fight.gd:897-905）登记拍语义**均匀**：
`eng != e[1] ⇒ e[0]=eng`（不递减），递减恒从下一拍开始。
内核 np26fA「相位补偿」在「start 后隔拍登记」时把登记拍多减 1 delta
⇒ multi 计时器恒**早 1 tick** 发火（run704242 SPF 毒 271 v oracle 272）。

实证（`tools/_a1_oracle_bare_case.py` + ORACLE_TIMER_POLL/DEBUG）：
- run583_r11：[timer-reg] t=2.0000（不递减）→ 首减 2.0167 → f64 尘埃
  k=211 发火 5.5167（=语料值）； uncompensated 内核同律即对齐。
- run704242：[timer-reg] t=1.0167 → 发火 4.5333（tick 272）；
  补偿使内核发火 271。
- np26fA 时代「全局移除→541 场反弹」实为真因一的 Coins 多抽被补偿掩盖——
  Coins 修复后补偿再无正例。

### 2.2 修复

| 层 | 文件 | 修改 |
|---|---|---|
| py 内核 | `gd_core_py/gd_core/CoreTimer.py tick()` | 补偿段整删（登记拍不递减语义保留）；ORACLE_TIMER_NO_PHASE_COMP 门控随删；已重编 .pyd |
| gd 内核 | `gd_core/CoreTimer.gd`、`gd_core_test/gd_core/CoreTimer.gd`、`native_sim_cpp/gd_core/CoreTimer.gd` | 同上 |
| C++ 内核 | `native_sim_cpp/native_sim/gen/shards/shard_05.cpp` | 删恒真 if 的补偿赋值（转译时 env 比较被常量折叠成 ""==""，补偿恒生效=24 场硬缺口之一） |

## 3 开关机制清除（死代码，行为零变化）

- `gd_core_py/gd_core/CoreItem.py`：ORACLE_FLK_DELAY / ORACLE_FLK_OFF /
  ORACLE_NO_FLKFIRE / ORACLE_INJ_ITEM / ORACLE_INJ_TRIGGER_N 全部消费点删除；
  `_inj_*` 字段删除；CoreContext.flk_delay_cursor 删除（均重编 .pyd）。
- `tools/verify_oracle.py`：case_overrides 装载 + _OV_KEYS 逐场 set/pop 删除。
- `gd_core_test/OracleAlignBattle.gd`：门控表装载 + run_case 应用块 + env 基线快照删除。
- `gd_core/CoreItem.gd`、`gd_core_test/gd_core/CoreItem.gd`、
  `native_sim_cpp/gd_core/CoreItem.gd`：同名开关代码删除。
- lib_fires 机制保留（`lib_fires_overrides.json` 恒空、非 22 场开关范畴）。
- C++ 生成代码内的开关块因转译期常量折叠天然惰性，保留（已核实零行为）。

## 4 行为零变化交叉验证

开关机制删除后重跑：22 场开关场 **22/22**、60 场快闸 **60/60** 全三方一致；
种子双态 `tools/check_seed_dual.py` FAILS=0（907/1548 与 1042/1991 符合基线）。

## 5 1690 全量验收（无开关）

结果：见 `output/perf/alignment_1690_noov_final.json`（运行日志
`output/_a1/_full1690_run.log`）。**回读 perCase 逐条核对**：total=1690、
perCase 1690 行、aligned=1690、非「三方一致」行 **0**（规划 A.4 硬性要求：
不许只看总数）。

## 8 最大体力上限真实逻辑核实（2026-11-14 用户质询专项）

### 8.1 源码定谳（oracle/ 1.1.9 反编译工程）

| 事实 | 证据 |
|---|---|
| 战斗开始前 base 上限 = **5**，全部职业 | `oracle/CharacterClasses/*/*.tres` 的 `stamina = 5`（7 职业逐一核实）；`Character.gd:62 maxStamina=5.0` 默认 |
| 开战时唯一发放源 = **Stamina Sack**（+1/件） | `Character.recalculateMaxStamina()`（Character.gd:983-990）：`maxStamina = getBaseMaxStamina() + (1 per descriptor==staminaSackDescriptor 的背包物品)`；`curStamina = maxStamina`（顺带回满） |
| 对手侧：装配后**显式重算** | `Game.initHistoryOpponent`（Game.gd:3213-3214）：`baseMaxStamina = classResources[class].stamina; recalculateMaxStamina()` |
| 玩家侧：**历史存档值直读** | `startHistoryRun`（Game.gd:2714）/`oracle_fight.gd:619`：`setMaxStamina(roundData.stamina)`——玩家背包内的囊在装配期只排队 `call_deferred(recalculate)`（Character.gd:979，仅 PLAYER 分支），阻塞回放下不执行 ⇒ 生效值 = 存档列真值 |
| 战斗中的额外上限 = **临时池** | `gainMaxStaminaTemporary`（Character.gd:993+）→ `temporaryMaxStamina`；有效上限 = `maxStamina + temporaryMaxStamina`（:801）。发放物品：Bag of Giving（onItemInsideActivated）、Bionic Armor（格挡 proc）、Perpetuum Mobile（onCombatStart）、White Knight（棋子被吃）、Rainbow Potion（书本数）——全部为物品脚本 |
| 存档 stamina 的写入公式 | `Game.calculateMaxStaminaFromItemTuples`（Game.gd:2727）：`classResources[classI].stamina + 1/囊`——BuildHistory 存档时从物品元组重算 |

### 8.2 「玩家 stamina=5 而袋里有囊」不是 bug

全量核对（1690 场）：**对手侧 0 不匹配**（fixture stamina ≡ 5+囊数，与显式
recalculate 等价）；**玩家侧 376 面** fixture stamina=5.0 而袋内有 1-6 囊——
抽查 run100786 r15 的 history.db 明文列就是 5（该 run 全 15 回合恒 5）。
即：**语料史真值本身就是 5**（存档时点与购囊时点错位的历史产物），oracle
harness 照 inject。夹具生成器（`tools/gen_fixture_from_lineup.py:40-53`）
的 r33 定谳早已证伪「恒 base」与「恒 base+袋」两个模型（813/910 同画像异值）——
**玩家侧必须按存档列真值注入，不能重算**。

### 8.3 三腿实现一致性

| 腿 | 开战 max | 开战 baseMax | 战斗中临时池 | 结论 |
|---|---|---|---|---|
| oracle | `setMaxStamina(roundData.stamina)`（玩家）/ 重算（对手） | 类表 5 | 物品脚本 | 真值 |
| py | `p_stats['stamina']` = 夹具列（2026-11-09 修） | `lineup.base_max_stamina`=5 | 转译脚本 | **一致** |
| C++ | `pack_side` v3/v4 分支此前只取 class base ⇒ **缺夹具直通**（B 阶段 13 场 OutofStamina 分歧根因） | 同左 | 转译脚本 | **修后一致** |

修复：`native_sim_cpp/native_sim/sim.py pack_side()` 补
`side["stamina"]/["health"]/["regen"]` 直通（镜像 py 引擎 p_stats/o_stats，
键缺省=原行为）；`tools/_full1690.py`、`tools/_b2_probe_native.py` 注入夹具值。
修复后三场探针（run704991/run704752/run300225）native vs py **逐位一致**。

### 8.4 深挖（用户质询第二轮）：db 明文列 ≠ 位流内嵌真值

run100786_r15 取证发现：**同一 db 行里两处 stamina 语义不同**——

| 载体 | 值 | 写入方 |
|---|---|---|
| buildInfo 位流内嵌 stamina | **6**（=5+1 囊，真实游戏序列化时刻的真值） | `RunDatabase.serializeRound`（RunDatabase.gd:620 push `getMaxBaseStamina()`=maxStamina） |
| sqlite `stamina` 明文列 | **5**（类 base 常量） | `Game.createPreviousRoundsHistory`（Game.gd:4376 `dict["stamina"] = classResources[curClass].stamina`）等路径 |

全量核对（3380 个去重侧）：**位流内嵌 = 5+囊数 3377/3380（99.9%）**——
用户的公式就是真实游戏的规则（3 个例外疑似旧版本语义，version 1001004-5）；
**明文列 = 5+囊数 仅 2602/3380（77%）**——23% 的面（几乎全为玩家侧）列值
被合成历史路径写成类 base 常量。

**oracle harness 取的是明文列**（oracle_fight.gd:531
`addRoundData(..., row["stamina"], ...)` → :619 `setMaxStamina(列值)`），
位流内嵌真值在战斗装配面被忽略（buildInfo 只用于 deserializeItems）。
[PMAX-O] 探针实拍 run100786_r15：开战时 `side=0 max=5 cur=5 base=5
queued=True`——囊的 deferred 重算（Character.gd:979，仅 PLAYER 分支）在阻塞
回放下整场未执行（全日志无 `RECALC-O side=0`）。

**结论**：
- 真实游戏规则（用户模型）✅：base 5 + 每囊 1（位流 99.9% 实证）+ 战斗中临时池。
- 模拟器三腿跟随 oracle（明文列）→ 与语料逐位一致（1690/1690）。
- 两者在约 23% 的玩家侧面上分歧（列 5 vs 位流 6/7/8）——这是**录制管线的
  保真度缺口**（oracle 用列值、位流真值被忽略），不是模拟器逻辑错误。
  若要让语料贴合真实游戏，需改 oracle 取数（位流 stamina）并全量重录——
  基准重定，待用户决策，未擅自改动。

### 8.5 用户定案与执行（2026-11-15）：oracle 改贴游戏真值 + 全量重录

用户决策：「oracle 本身就应该贴合游戏真值，按方案执行」。已实施：

1. **oracle_fight.gd:619**：玩家开战 stamina 改 `setMaxStamina(p_deser["stamina"])`
   （= 同一 decode 产物里的位流内嵌值，与物品元组同源同版本；单场验证
   run100786_r15：`[SETMAX] side=0 new=6 old=5`、`[PMAX-O] max=6 cur=6`）。
2. **夹具生成器同步**：`tools/gen_fixture_from_lineup.py::_history_round_stamina`
   与 `tools/gen_oracle_cases.py` 的 stamina 改位流解码（`decode_build_info`，
   解码失败回退明文列）。
3. **全量重录**：914 + 1690（语料保护性拷贝于 `output/_backup_pre_stamina_rerecord/`，
   代码改动 push 于 commit 77bf6a90 之后的 stamina-fix 提交）。

### 8.6 其它 oracle-vs-游戏本体偏差排查（用户随附指令）

逐项核查 harness 的 [M1]-[M14] 修改与残留语义，按影响分级：

| 项 | 性质 | 影响面 | 处置 |
|---|---|---|---|
| **战斗期 call_deferred 不执行**（[M11] 阻塞循环无帧） | 🔴 语义级 | **Deck of Cards 204 个侧**（startActivation 卡链永不启动——真实游戏下一帧即启动）；DragonEgg/Card 语料 0 侧 | **结构性，未修**：修复需 harness 改帧驱动（yield 每帧），会重引入墙钟依赖（idle 型 Timer 的 delta 计时随 vsync 抖动），与 [M2]/[M6] 的确定性设计冲突。已量化待用户决策 |
| **AnimationSpeedTimer 停用**（[M6]） | 🟡 链消耗级 | 真实游戏每 2-5s 消耗 4 步链（Character.gd:1562-1564 `randAnimationSpeed`）；其相位依赖会话帧历史，**不可复现** | **维持 [M6]**：无单一真值目标（相位≠任何确定值）；harness 停用=双方约定。已记录 |
| ItemLibrary UI 实例 flicker 抽（np51㊳ 跳过） | ✅ 已定谳 | 冷启动期抽耗被 per-case set_seed 抹平；战斗期 UI 库不参战 | 无动作 |
| [M5] UI/音频 rng 按原版保留 | ✅ 保留 | — | 无动作 |
| [M6b] 池清空 / [M13] 跨场归零 | ✅ 等价冷启动/全新 CoreContext | — | 无动作 |
| [M2] Timer 读数注册表 / [M1] callDelayed 登记 | ✅ 阻塞循环等价实现 | — | 无动作 |
| 对手装配 initHistoryOpponent | ✅ 原版函数本体（含显式 recalculate） | — | 无动作 |
| sus-run 预检（RunData.deserializeRound 校验） | ✅ 用位流内嵌值校验（5+囊数） | — | 无动作 |

**遗留决策点**（未擅动）：战斗期 deferred 语义（Deck of Cards 204 侧）若要
贴合真实游戏，需要「帧驱动 harness」重设计——收益是 204 侧卡链真实化，代价是
录制确定性与空闲型 Timer 的墙钟依赖。待用户另案决策。

## 9 B 阶段结果（C++ 内核 1690/1690）

| 项 | 修复前 | 修复后 |
|---|---|---|
| 全量 1690（event_count 差 −1 且 winner 一致） | 1666/1690 = 98.58% | **1690/1690 = 100%**（`output/perf/_cpp1690_final3.json`） |
| 三闸（seed 双态 / REG9 / 60 场） | 59/60 | **全 GREEN**（`native_sim_cpp/output/three_gates_result.json`） |

C++ 侧修复（四项，均无场次开关）：
1. `gen/shards/shard_00.cpp` CoreItem.setup：场景深度新模型（1 + max(0,depth−1)）；
2. `gen/shards/shard_05.cpp` CoreTimer.tick：相位补偿删除（转译期 env 比较
   被常量折叠成 ""==""，补偿在 C++ 里**恒生效**——24 场硬缺口的主因之一）；
3. `assets/gd_core_runtime.json`：Coins sceneDepth 2→1；
4. `native_sim/sim.py` pack_side + `tools/_full1690.py`：体力/血量/回复夹具真值直通。

## 10 C 阶段决策：采用保守方案（py=对齐/调试引擎，C++=批量引擎）

C.1 三前提全部满足：
- A：py 1690/1690 且 override 表为空 ✓
- B：C++ 1690/1690 且零场次开关 ✓
- 性能：同口径交错 A/B 复测（`tools/_c1_perf_ab.py`，60 场）——
  py 127.2 ms/场 vs native 70.6 ms/场 = **1.80x** ✓（≥1.8x 门槛）

决策依据（同规划 C.2 推荐）：两内核在「正确性」上已平权；本项目成本最高的
环节是**定位新分歧**——py 可随时加探针/单步（本次 A 阶段全部取证都在 py/gd
腿完成），C++ 每改一处要动生成代码并重编（本次 20.9s 增量编）。故：
训练/评测批跑走 C++（1.8x），对齐排查与探针走 py；两内核同步维护点收敛为
「场景深度表 + 物品脚本转译」两处生成链。

## 6 附：取证工具（本次新增，可复用）

| 工具 | 用途 |
|---|---|
| `tools/_a1_oracle_bare_case.py` | 单场 oracle [BARE] 全裸流重放（隔离工程副本，BARESTACK/ITEMMARK/ITEMINIT/CONNREADY/TRIGMARK 探针，零 rng 消耗） |
| `tools/_a1_measure_asm_steps.py` | py 装配期 PCG 总步数 vs oracle（rng_state 反推），A1_GDRAW=1 出 [GDRAW] 逐抽流 |
| `tools/_a1_align_asm.py` | oracle [BARE]+归属标记 vs py [GDRAW] 逐笔对位，定位首个分歧 |
| `output/_a1/overrides_backup.json` | 原 22 场开关表备份（已清空的表可由此回滚） |

## 7 教训（对应规划附 B 的补充）

| 坑 | 教训 |
|---|---|
| stdout 粘行 | Godot 的 ERROR 输出与 print 会粘在同一行，[BARE] 解析必须 finditer 全文搜索而非 startswith |
| get_stack() 为空 | 该 Godot 构建下 Reference 派生类的 get_stack() 返回 null——逐抽归属必须用「源码内打点」而非栈帧 |
| 旧语料 vs 扩样语料 | 旧 914 场在 oracle/fights.json（历史库=oracle/data/history.db），扩样场需隔离副本+换库；两者用例键名不同 |
| 生成代码修补 | C++ 生成代码的 env 门控被转译期常量折叠（""==""恒真）——「行为对齐」不能只看源码字面，要核折叠后的真值 |
| 验收判据 | 「pcg 推进步数闭合」（seed→state 反推）是装配链对齐的最强单指标：步数不等必分歧，步数相等+事件流一致≈链位逐位一致 |
