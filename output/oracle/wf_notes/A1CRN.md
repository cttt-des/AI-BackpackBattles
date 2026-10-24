# A1CRN 取证存档 —— K04 Crown 净化时基 ×4 + K08 Coil 选批 ×3（受阻收口）

- 日期：2026-10-17。卡面文件：gd_core/CoreBuff.gd + gd_core_py/gd_core/CoreBuff.py。
- 结论：**blocked，零码改**。7 场全红（alignment.json perCase 实读），根因定谳为三族，
  均不落在卡面文件内。无备份、无 gd_to_py 重转写（无 gd_core 改动）。

## 一、根因假设

### K04-A（run771_r18 idx226 / run1203_r18 idx177 / run1281_r11 idx91）：fatigue advanceTime 越权
- 首分歧：gd 在 t=5.0333 插入 Power of the Moon 的 ty19 TemporaryMaxHealth + ty0 激活
  各两次；oracle 同位无此事件。PotM.onFatigueStarted（fatigue_start 信号监听）→
  giveMaxHealth+activate（gd_core_items/Exclusive/PoweroftheMoon.gd:42-45）。
- 经验律（全库 21 个含 PotM 场扫描）：oracle fatigue_start 恒 =17.0167
  （=FATIGUE_TIME 17 未提前，gd_core/CoreCombat.gd:57）或无（战斗早于 17s 结束）；
  gd 恒 =5.0333（=17−3−2×6 起爆 +3s 首击；time=6.0 见 assets/battle_items.json
  named_params；两件 PotM 共提前 12s）。
- 根：gd_core 移植恒施加 advanceTime（PoweroftheMoon.gd:26-27 onPostCombatStart →
  ctx.combat.advanceTime；CoreCombat.gd:476 `time_advance += _time`、:245
  `fatigue_next_tick = 17−3−time_advance`），而 oracle 语料侧从未生效。
- 真源链路（已逐字对读）：oracle/Items/Exclusive/PoweroftheMoon.gd onPostCombatStart
  → oracle/Core/Combat.gd:920-926 advanceTime → oracle/Interface/CombatTimer/
  CombatTimer.gd:184-198（registry 桩 Util.oracleTimeLeft 优先，start(timeLeft−time)）。
  Main.tscn 的 Combat 节点脚本确认为 Core/Combat.gd（ExtResource 74），链路完整，
  静态上"应当生效"却 21/21 不生效——**harness 内部吞没机制未闭**（候选：activateItems
  期 oracleTimeLeft 读到上场陈旧注册表、Engine 冻结读数、startFatigue else 支时序），
  需归属泳道带活体 trace 定谳。修法方向：gd_core 对齐 21/21 经验律（不提前/复刻
  harness 实效语义）。
- 重要否定：run771 的 Crown 净化链本身双端一致——对手 Crown tk304 净化+治疗+激活
  三事件 O idx226-228 ≡ G idx232-234，仅被 PotM 插入事件平移 4 位。卡题
  「净化触发链时序」假设不成立。

### K04-B（run1038_r9 idx141）：Blind 临时批到期相位（K01/K03 挂起盘）
- gd：BurningBanner tk407 施加 Blind(dur5) 后 tk408 即 timeout（b3_fix1 四分支模型
  ② 残留瞬弹支，CoreBuff.gd:56-77 注、:570-576 实现）。
- oracle：同批存活过 tk415 净化（永久栈 2 先耗，tempToCleanse=0），最终 tk440
  （=407+33 tick）才 fire——既非 300tick 自然到期，亦非瞬弹。
- 静态推演不可达：真源 oracle/Core/Buff.gd（gain 的 `timer.is_stopped()`→start 分支、
  loseStacks 清空 stop、onTimeout REARM）与 oracle/oracle_fight.gd:880-925
  drive_timers（stopped 每遍写 e[0]=-1；eng==e[1]→e[0]-=dt 瞬弹）与移植同构；
  按 e[1]=5/e[0]=-1 前置推演必然瞬弹，oracle 却 +33tk fire——无算术律
  （run1038 内其余 Banner 盲批 gap=301/267/118/64/104/78 tick，无规律）。

### K08（run1102_r18 idx200 / run1104_r18 idx153 / run1105_r18 idx327）：选批上游链静默分叉
- 真路径：Coil.gd:10-16 onChargeReceived → stealRandomBuff（CoreItem.gd:2747）→
  pickRandomStacks（CoreItem.gd:2482）→ ctx.rng.pickRandomElement（CoreRng.gd:146）。
  **并非卡面假设的 removeBuffsFraction/sortDict**；r34 层2 改道（CoreUtil.gd:99-109）
  无重复面。
- 证据：①选批代码与真源（oracle/Items/Item.gd:5422-5446、oracle/Utility/Util.gd:452-456）
  逐字同构；②python 重放双流 events 至分歧点重建受害者栈态双端全同
  （run1104: Block55/Lucky2/Regen1/Spikes3/Mana9；run1102: Block307/Lucky5/Spikes2/
  Mana31/Empower16/Blind2；run1105: Block446/Lucky5/Spikes2/Mana23/Empower7/Heat2/Blind7）；
  ③首分歧落在第 1 抽（run1104：O {Mana×2,Lucky×1} vs G {Spikes×2,Mana×1}）或
  第 2-3 抽（run1102：O {106:2,105:1,104:1} vs G {106:3,101:1}；run1105：
  O {106:1,105:2} vs G {106:1,107:1,101:1}）——紧邻循环内无状态变化而抽值异
  ⇒ rng 值流在链外上游已静默分叉（首分歧前事件面全同、消耗次数同、函数同构）。
- 同族判决：台账末节「r35 K17 续取证」同签名收口="卡内无修改点，阻塞收口"。

## 二、反例与矛盾记录

1. **run688_r10 vs run1038_r9 正面矛盾**：b3_fix1 ② 支由 run688 实证（净化清空致
   stop→同 dur 重施加→oracle 当遍瞬弹）；run1038 同形态前置（tk145 净化 stop、
   tk407 同 dur 重施加）oracle 却存活 33 tick。② 支判据不完备，第三因子未定
   （候选：永久栈并存、stop→start 间隔 262 tick 的注册表态、批布局差异）。
2. **run727 vs run619 相位场间不一**（台账 r35 K03 节在案）：corpus 盲批到期相位
   无跨场一致性，现行 oracle 树无法取证——故 run1038 不单独硬修。
3. **PotM harness 机制悖论**：静态链路完整（Combat 节点脚本=Core/Combat.gd，含
   advanceTime 转发）而语料恒不提前——任何"修 advanceTime 数学"的方案都无解释力，
   必须先以活体 trace 定位 harness 吞没点。

## 三、建议（移交面）

1. K04-A 三场 → CoreCombat/PoweroftheMoon 泳道：方向=对齐 oracle 经验律
   （fatigue 恒 17s 起爆）；先带 trace 查 harness 吞没机制再动码。
2. K04-B run1038 → K01 研究卡（40 场盘，勿硬修）：② 支需第三判据，
   建议 BSCHED 桩（仍在位，oracle_trace 门控）对 run1038/run688 双场同跑对表。
3. K08 三场 → K17 盘：待 rng_trace 落盘链路修复后双指针抽序对拍定位上游分叉点
   （候选面：roll/翻转账/标签位之外的隐形消耗）。
4. r26 卡B BSCHED 取证桩（CoreBuff.gd 三处）保留：K01 盘仍需，非本卡撤离对象。

## 四、树态验净记录

- 本会话对卡面两文件零 Edit/Write；根因取证全部为只读（Read/grep/python 只读对拍）。
- 验净检查：`git status --porcelain` 两文件态与开工前基线一致（M 态系并行泳道
  既有面）；CoreBuff.gd 内无临时探针 tag 残留（AA/AC/DA/MARKA/MARKB 等模式 grep 零命中）。
- CoreBuff.gd md5 留档供后续泳道比对（见确认回执）。
