# np15_fix · 首轮修复轮（阶段2：两笔产线补丁 + 三场剔除，2026-10-21）

## 结论（先答）

**round2 增补（同日，leg+fix_r1 对拍后）**：REG 绿、np15_fix1/2 保留；run1132/602 转绿实锤。
run989 分歧 686→710 移位定谳 = 同帧双施加下 e[0] 被 start 冲掉 → **np15_fix3**（CoreBuff
`_timer_e0` 注册表影子，e[1] 键控非激活 start + RESCH 读 e[0]）已落盘（语法闸 0 错，REG 待脚本）。
run1444@330 不变（预测命中：e[1]==3==dur，本笔不触碰）；run702@423/run1022@1386/run948@42/
run844@83 维持剔除。以下为首轮原文 + round2 增补节（§7）。

本卡 8 场分拣：**两笔补丁已落**——np15_fix1（gd_core/CoreBuff.gd，B2 判据 `_timer_last_dur`→`_timer_e1`，
覆盖 run989_r18/run1132_r18 双向）+ np15_fix2（gd_core_items/Exclusive/Sandbag.gd，BuffTimer
multi→普通，覆盖 run602_r14）；**四场剔除留档**——run948_r18/run844_r11（np14_fix 的闩源定谳
被其自家 rng_log 反驳，真根因未闭）、run1444_r18（oracle 侧探针双稳，语料样本不可由任何
确定性规则复现）、run702_r18（弹点无 B2 触达，同刻批拆根因未闭）、run1022_r18（np12_L1 §3
隐形盲批维持）。REG 九场未跑（脚本统一跑）；两笔补丁均通过 godot --check-only 语法闸。

## 1. np15_fix1 · CoreBuff B2 判据（run989_r18 / run1132_r18）

### 机理（oracle drive_timers 真值，oracle/oracle_fight.gd:880-919 逐行复读）

- 停走遍只写 `e[0]=-1`，`e[1]` 冻结在**上一已驱动 stint** 的 eng（=f32(wait)，引擎读数阻塞循环下
  恒定）；外部 start 后当遍 `eng==e[1]` 才落 `e[0]-=dt` 支（从 -1 起扣 → 当遍 fire）；
  `eng≠e[1]` 一律重同步（`e[0]=eng`，满时长重走）。`_timer_last_dur` 只记「最近一次 start 实参」，
  **同帧 start→stop 的夭折 stint 也写它**（从未被驱动遍观测）——gd 旧码 B2 用它冒充 e[1]。

### 双向实证

- **run989_r18@686（gd 多弹）**：np14v_confirm gd trace（rng_trace.txt 行 5295-5311/5466-5475）：
  9.0833 GAIN dur5（B3）同帧 CLEANSE 清空 STOP（left=5 保留，stint 零驱动 → `_timer_e1` 保留
  9.0833 前 dur3 stint 的 3.0）；9.3833 Burning Banner 同 dur5 重施加，旧码 B2（left=-1 且
  last=5==dur5）瞬弹打掉新批 → gd 独有 id686 Blind TO -1 @9.3833（语料 idx685/686 对位实测，
  语料 idx686 为 Blueberries @9.4）。oracle：eng(5)≠e[1](3) → 重同步满 5s 重走，语料同位无此弹。
  改后 gd 落 ③ resync，9.4167 Chili 的 -1 净化改拆该临时批（语料 O713 同位）→ 事件流应回到
  语料轨道。
- **run1132_r18@278（oracle 多弹，gd 漏弹）**：np14v gd trace 行 3514-3515：10.6333 GAIN +7 dur3
  的 START br=B3（pre left=-1 **last=2**）——10.0167 的 dur2 stint 同帧夭折写了 last=2，而 e[1]
  保留其前 dur3 stint 的 3.0。oracle：eng(3)==e[1](3) → 次遍 fire 打掉新批（语料 o278 Blind TO
  -7 @10.6333，增益 o275 @10.6167 后 1 tick，与 gd ② 瞬弹的事件位约定同构）。gd 旧码 last=2≠3
  落 ③ 漏弹。改后 e[1]==dur 命中 B2 补弹。
- **锚保全**：run688_r10 idx130-133（b3_fix1 的 ② 锚：净化清空前 stint 已驱动，e[1]==dur==last）
  改后仍命中 B2；自然 fire 尾 `e[1]` 保持本遍 eng=dur（CoreBuff._tick 遍尾写），同 dur 重施加
  仍 ②；run634 idx450/540（③/① 支）与 run727（①' 支，np6_B1）分支链零触碰。
- **绿场不变证**：绿场任何已发生的 ② fire 都与 oracle 事件逐位一致 ⇒ 其 e[1]==dur 必然成立
  （e1≠dur 的 ② 会产生 gd 独有 TO → 当场即红）⇒ 本笔对绿场零行为变化（REG 风险论证）。

### 改动与验证

- `gd_core/CoreBuff.gd`：B2 分支判据与 BSCHED 标签块 `_timer_last_dur` → `_timer_e1`（单点），
  注释更新（② 模型总注 + 分支内 np15_fix1 注）。备份
  `output/_round_patches/np15_fix/CoreBuff.gd.pre_b2fix.bak`。
- 语法闸：`godot --headless --path gd_core_probe --check-only --script res://../gd_core/CoreBuff.gd`
  → 0 SCRIPT ERROR（本轮实跑）。
- REG 九场：未跑（红线，脚本统一跑）。

## 2. run1444_r18 / run702_r18 —— ① 组内未闭残留（剔除留档）

- **run1444@330（gd 多弹 Frostbolt Cold TO -2 @5.9833）**：gd trace 行 2820-2834 B2 瞬弹，但
  该处 e[1]==3==dur（5.8833 净化清空前 stint 已驱动）——本笔判据改后 **仍命中 B2，不转绿**。
  语料侧无此弹，而纯 drive_timers 模型（stopped-observed + eng==e[1]）推演必弹 ⇒ 语料进程在该
  计时器上的隐形状态（批列表未清/注册表读数异）不可由可见事件流复现。**oracle 侧探针双稳实证**
  （本轮新发现）：同种子同 lineups 同树，本轮 `ORACLE_FIGHTS_ROOT=output/oracle/probe/np15_fix
  ORACLE_ONLY_CASES=run1444_r18 ORACLE_DEBUG=1` 探针产出 **gd 形 kill @idx330**（1002 事件，
  与 np14v gd 腿逐位同形），而 np14_fix 探针（今日 14:21 重跑，output/oracle/probe/np14_fix/
  run1444_r18/，events 1030）与语料逐位全同；去 DEBUG 复跑又得 1037 事件、首差推迟到 idx342
  （-2 v -1 批量差）。三跑三形 ⇒ 该场分歧点对进程态敏感，语料样本只是双稳分布的一次抽样。
  **处置建议**：reRecord 单场重录（同管线）取新样本；或按「语料批态已知缺陷」剔除。gd 侧禁修。
- **run702@423（LG Blind TO 同刻 -7 v -6）**：np14v gd trace 弹点前窗（2.0-4.0）BSCHED 分支
  实测 **B2 触达=0**（START 仅 2 笔皆 B3，弹出为自然 FIRE+REARM 链，行 3284-3290）——与本笔
  判据无关，改不改都一样。同刻批拆根因 = 同帧净化/弹出的相位序差（双方事件流至 idx422 逐位同），
  本轮未闭。维持 np9_L1 run977「同刻批布局不可见差」族归档，gd 侧禁盲修。

## 3. np15_fix2 · Sandbag BuffTimer 非 multi 化（run602_r14）

### 定谳（tscn 真值，np12_L3 §D 的 CoreTimer/changeTimer 假设面被推翻）

- oracle **Sandbag.tscn**：`[node name="BuffTimer" type="Timer"]`（:70，**无 MultiTimer 脚本**）+
  `[connection signal="timeout" ... method="buffEnded"]`（:89）——**普通一次性 Timer**。
- oracle **LeatherHelm.tscn**：BuffTimer 挂 MultiTimer.gd（:10）+ `signal="multi_timeout"`→buffEnded
  （:68/:84）。六个 LeatherHelm 子件 tscn 全查：StoneHelm/CapofBrilliance/NoRushPlease/
  SpiritBells/Turtle 均 MultiTimer，**唯 Sandbag 用普通 Timer**。
- gd 基类 LeatherHelm.gd:66 `newItemTimer("BuffTimer","buffEnded",true)`——Sandbag 连带建成
  multi。后果：EchoingBattlecry.repeatCombatStart → changeTimer(buffTimer, 7) 续期
  （gd_core/CoreUtil.gd:183-186 → CoreTimer.start）在 multi+running 下走**排队支**
  （CoreTimer.gd:95-97 只压 timestamps 不重置引擎），且引擎首爆时 _onTimeout 先
  `timestamps.clear()`（CoreTimer.gd:186，Battery×15 簇约定）——排队续期整段作废。
- run602_r14 数据面（本轮从语料/gd 腿 events 实测）：疲劳 display 双侧逐笔全同至 13.6333；
  oracle tgt0 阻力窗止于 **14.0167**（=5.5 续期 + 8.5167=7+oLeft(≈1.5167)，普通 Timer
  changeTimer → start(dur+oLeft) 引擎重置，oracle/Utility/Util.gd:1671-1677 读注册表 oLeft）；
  gd 腿窗延至 ~16.2（np14v events：15.9833 仍 0.75b、16.2833 首个裸值）。改动后 gd 走
  CoreTimer ③ resync（非 stopped、dur8.5167≠last7），引擎重置 +1 tick grace，
  与 oracle harness resync 逐点同构，预期窗止对齐 14.0167+grace。

### 改动与验证

- `gd_core_items/Exclusive/Sandbag.gd` `_readyInit` 尾部按 tscn 真值重建
  `buffTimer = newItemTimer("BuffTimer","buffEnded",false)`（newItemTimer 自带同名旧器
  stop+erase，gd_core/CoreItem.gd:753-764）。备份
  `output/_round_patches/np15_fix/Sandbag.gd.pre.bak`。
- 语法闸：`--check-only --script res://../gd_core_items/Exclusive/Sandbag.gd` → 无错误（实跑）。
- run602 + REG 九场：未跑（红线，脚本统一跑）。其余 multi 计时器件（EvilCap/AmuletofAgility/
  EngineerBox/Rope/StrongVampiricPotion/StrongDemonicFlask/StrongPestilenceFlask/
  AmuletofAlchemy）本轮无证据指向，未动。

## 4. run948_r18 / run844_r11 —— ② 组剔除（np14_fix 闩源定谳被反驳）

- np14_fix §3 称「oracle 激活相 playActivateAnimation 闩死 → 首武器攻跳本体（+5 抽）」。
  本轮用其自家 probe 的 rng_log 复核（output/oracle/probe/np14_fix/run948_r18/rng_log.txt
  行 456-469，U.time 84.317=战斗 1.5833）：oracle 首武器攻 **本体 5 抽全跑**
  （(100,160)→(0.9,1.1)×2→pick(0,2)→(0.8,1.2)→pick(0,2)）——**闩根本没闩**，定谳前提不成立。
- 本轮逐抽对位（oracle rng_log vs gd np13v_all-red/run948_r18/rng_trace.txt，自写对位脚本，
  首 diff @draw428）：双侧至首攻冲击块逐抽全同；分歧 = 冲击后 oracle 直取伤害掷
  randi_range(17,23)=>21（#470），gd 插入 pickRandomElement(0,2)×4（#871-874）再走后续。
  该 4-pick+procs 链在**第二次** Prismatic 攻（84.367）双侧逐值全同（gd #945-962 == oracle
  #538-555）——即某件随攻 proc 链在 oracle 的**首次**攻未触发、gd 触发，属随攻条件/进程隐形态
  一族，非闩语义。
- gd 侧闩语义本就与 oracle 同构：gd_core/CoreCharacter.gd:553-559 playActivateAnimation
  （`if attack_moving_forward: return` + 2×rng(0.9,1.1) + 尾置 flag）≡ oracle/Core/Character.gd
  :464-481。**无可落补丁**，两场剔除；后续认领建议用 ORACLE_RNG_DEBUG/[eat] 仪器钉 proc 链
  归属件（本卡分析特权不含 gd 侧现跑）。

## 5. run1022_r18 —— ④ 组剔除

np12_L1 §3 维持：oracle @13.0333 多弹 Banner Blind TO -1 由事件流不可见的隐形状态
（null-item GAIN 永久栈 / 批 timeout 读数 1 tick 差）产生，gd 逐场输入无法复原。本轮无新证据，
无单笔可落，剔除。

## 6. 仪器与纪律

- 本轮 oracle 探针（分析特权内）：np15_fix（run1444_r18 ORACLE_DEBUG=1）、np15_fix_nodebug
  （run1444_r18 无 DEBUG）——两跑互异 + 与语料/np14_fix probe 三形，产双稳证据链；
  探针运行会写 output/oracle/probe/np15_fix*/，未触 fights/ 与 oracle/ 树。
- 离线分析器 output/oracle/probe/np15_fix/_bsched_sim.py（gd CoreBuff 批账面 Python 复刻，
  含 B2 变体开关）：本轮完成事件↔BSCHED 行配对框架，批账面逐帧仿真未达逐笔复现
  gd TO 流的保真度（帧心配对的 ±1 帧类未收口），**其输出未作为任何定谳依据**；
  保留供后续认领继续。
- 产线改动仅 2 文件（gd_core/CoreBuff.gd、gd_core_items/Exclusive/Sandbag.gd），均有
  pre-bak；gd_core_py 镜像不在本卡允许面，未同步（提请主控知悉）。
- 未 commit/push；REG 判据未放宽；gd 验证腿未跑。
