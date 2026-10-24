# np4_DATA1 · oracle 描述符 cd/speed 数据面审计笔记（run947_r10 + run1101_r18 并案，2026-10-18）

## 结论（定性）

**两场的分歧根因均不在数据面，判定 blocked（未改码，无备份需回滚）。**

对两场阵容物品全集（47 个去重物品名，双方镜像阵容）做了 oracle 真源 ↔ `assets/battle_items.json` ↔
`gd_core_test/item_battle_fixture.json` 的全字段对表，**零失配**：

- `cd` 列：47/47 一致（含 Perpetuum Mobile cd=8.0、Spiked Staff 1.8、Chess Board 0.9、Shelly 13 等全部 cd>0 项；其余 cd 缺省=0 一致）。命令：三表对表脚本（oracle `oracle/Sheets/CSV/ItemData.csv` vs `battle_items.json` vs fixture `descr.cd`）。
- 具名参数（p1..p10 带 `值:名` 格式）：逐项一致（PM `stamina=2/refund_buffs=30/refund_stamina=30/speed=30`、Uniquely Unique `speed=20/speed2=10`、Rainbow Potion、Fanny Pack `speed=10` 等）。
- 匿名参数（CSV 中 `6:` 这类无名字段）：按**位置数组**比对（fixture `descr.params` / battle `params`），6 个含匿名参的物品（Corrupted Crystal、Djinn Lamp、Fanny Pack、Mana Orb、Moon Shield、Piggybank）全部逐位一致。
- minDam/maxDam/accuracy/block/staminaCost/price/chance/chance2：零失配。
- PM 受影响格：fixture `affected={"0":[[-1,0],[0,-1],[0,1],[1,0]]}` 与 oracle 场景 `oracle/Items/Exclusive/PerpetuumMobile.tscn:40` 的 tile_data 解码归一后（tile3=自身格 (-1,-1)，tile4=受影响格，减去自身格）完全一致（上下左右四格）。

即：**开局冷却抖动的笔数口径、PM 的 cd/speed 参数，两场在数据面均无洞。**

## 证据链（本轮实际执行）

### run1101_r18（PM 开战冷却）

1. gd 侧 np3a `rng_trace.txt` 第 289-306 行与 oracle probe `output/oracle/probe/np2_or4/run1101_r18/rng_log.txt` 第 254-271 行**逐值相同**：开局抖动 = 玩家 9 抽 (0.95,1.05) + 对手 9 抽 (0.975,1.05)，合计 18 抽 == 双方 cd>0 物品数（每侧 9 个：Stable Recombobulator/Charge Splitter/PM/Thunder Drake/Djinn Lamp/Mana Crystal/Lightning Staff/Magitecc Armor×2，由 lineups 装配序 + battle_items cd 推出）。gd 在开局抖动段的抽数与值与 oracle 完全同步。
2. 逐抽对位 `python -X utf8 tools/_probe_draw_diff.py output/oracle/probe/np2_or4/run1101_r18/rng_log.txt output/oracle/align/np3a/run1101_r18/rng_trace.txt 4`：**oracle 3416 抽 vs gd 3299 抽（差 -117），首个分歧在第 860 抽**（事件级分歧 idx 172、t=3.35 之后）。
3. 事件级首分歧：oracle probe `events.json` idx172 = t=3.35 PM 首个周期组（T105 mana=8 + T13 stamina=0.7 + T0）；gd np3a 同刻无此组，gd PM 首周期在 t=3.8333。此前 0..171 号事件（含全部 t=0 开战钩子序列 0-39）两侧逐字相同。
4. oracle PM 初始 iterCd：probe trace P=7.896588=8×0.987074、O=8.242555=8×1.030319。**0.987074/1.030319 恰为抖动段双方第 7 抽的值**（rng_log 260 行 / 271 行）——oracle 把 PM 排在排序后激活序的第 7 位抽抖动，而不是装配序的第 3 位（装配序 PM=#3，第 3 抽值 1.026013→8.2081）。这与 `oracle/Core/Game.gd:2637-2649`（duplicate → **shuffle() → sort_custom(ItemSort,"sort_TriggerPriority")**）的激活序一致；双方 t=0 事件流逐字相同证明 gd 的复刻序（`gd_core_test/OracleAlignBattle.gd:327-350` activation_order + `gd_core/CoreCombat.gd:152-186` preordered 直通）在 t=0 钩子面上与 oracle 同序。**gd PM 实际吃到的抖动值无法离线确认**（见第 5 条），但 gd 首周期 3.8333s ⇒ 若 iterCd=7.8966 则均速 2.060（heat-cold=+8），若 iterCd=8.2081 则均速 2.142（heat-cold=+12）；两条都指向 gd 侧 PM 速度/热度链与 oracle 不一致。
5. **两条 item_trace 都不可信（工具面问题，留给内核卡）**：
   - gd `output/oracle/align/np3a/run1101_r18/item_trace.txt`：PM 全程 iterCd=0/active=0/speed=1.9，但同目录 `events.json` 里 PM 在 3.8333/7.75/11.33s 正常周期触发——自相矛盾（写入方 `gd_core_test/OracleAlignBattle.gd:580-595`，列序 `tick triggerTime speed iterCd active ownerType combat_time`）。
   - oracle `output/oracle/probe/np3_or1101pm/run1101_r18/item_trace.txt`（列序 `side tick triggerTime speed iterCd is_physics combat_time`）：speed=2.36 从 tick1 恒定到 ~tick200，但同 probe 事件流 t=0 就有 T107 Heat(+3)（Resistor 受 Battery 充能），按 `oracle/Items/Item.gd:3729-3752` getSpeed=1+speedScale+(heat−cold)×0.02 应为 1.96 且随热度阶跃——2.36 与事件流互斥（2.36 需要 heat-cold=23 恒定，事件流无此来源；0.3×N 对 1.36 无整数解，speed 参=30 双侧一致）。该 trace 的 speed 面疑为 np3 探针期旧态/口径残留，**不能作为 PM speed 分歧的定谳证据**。
6. PM cd=8 的开局抖动 gd 有抽（第 1 点），`resetCombatState`（gd_core/CoreItem.gd:691，会清 iterationCooldown）全库无调用方（grep 实证）——「gd 开战冷却未启动」的表象来自不可信 trace，真实分歧是**首周期时长**（3.35 vs 3.8333）。

### run947_r10（开局抖动 28 vs 34）

1. oracle 抖动段实数：`np2_or4/run947_r10/rng_log.txt` 168-193 行 = **26 抽（玩家 13 + 对手 13）**，恰等于双方 cd>0 物品数（每侧 13：Blueberries/Book of Basics/Chess Board/Corrupted Crystal/False Life/Oil Lamp/Puzzlebox/Shelly/Shiny Shell/Spell Scroll Dark/Spiked Staff/Wand/Wand of Dissonance）。**cd=0 名单假设不成立**：oracle CSV cd>0 集合与 battle_items.json/fixture 完全一致，无「oracle cd>0 而夹具 cd=0」的物品。
2. probe == 语料：`np2_or4/run947_r10/events.json`（399 事件）与 `output/oracle/fights/run947_r10/events.json` 逐事件相同；run1101 同验（961==961）。「重放=语料」成立。
3. **事件级首分歧在 t=0 idx6（RainbowPotion 随机 buff 选型）**：oracle 语料 idx6-8 = T105:3 + T104:1 + T103:2；gd `output/oracle/align/gdcore/run947_r10/events.json`（2026-10-18 00:10 生成，用的是当前 17:46 fixture）= T103:3 + T105:2 + T101:1。数量同为 6 层（staffs=2×buffs=3）。
4. rng_log 213-218 行：这 6 层 = 6 连 `pickRandomElement(0,6)`，oracle 值序 **4,3,2,2,4,4** → 池=[101..107]（getBuffs=range(Lucky,Heat+1)，oracle/Core/Game.gd:4934 ↔ gd_core/CoreConst.gd:217，两侧同式）→ idx4=T105×3、idx3=T104×1、idx2=T103×2，与语料事件完全吻合。gd 出 T103:3/T105:2/T101:1 ⇒ gd 的 6 抽值序为 [2,2,2,4,4,0]。**同池同取法（oracle/Items/Item.gd:5454-5461 ↔ gd_core/CoreItem.gd:2519-526）不同值 ⇒ rng 流在此前（开局抖动/开战钩子段）已失步**——与卡面「gd=28 vs oracle=34」观察吻合，但失步源头不是 cd 数据（cd 全对），而是抖动段/开战段的**抽笔数或序**（引擎面）。SpikedStaff「oracle 段首、gd 段尾」同理：抖动值→物品的指派序差异，排序复刻面（见 run1101 第 4 条 file:line）。
5. 注意：本侧无 gd 端 run947 rng_trace 落盘（`output/oracle/align/gdcore/run947_r10/` 仅 events.json），「28/34」的具体窗线无法在本卡离线复算；但 idx6 的 buff 选型分歧独立成立，且把失步点钉死在 t=0 抖动/开战段。

## 根因归属（内核/宿主面，非数据面）

- 开局抖动的「笔数与值序」由 `preCombatStart`（oracle/Items/Item.gd:3357-3370 ↔ gd_core/CoreItem.gd:632-645，同构）在**排序后激活序**上执行；激活序 = duplicate→shuffle→sort_TriggerPriority（oracle/Core/Game.gd:2637-2649、oracle_fight.gd:645-648）。gd 由宿主复刻（gd_core_test/OracleAlignBattle.gd:327-350 `activation_order`，seed(S)→下标 shuffle→按 `int(getTriggerPriority())` 稳定复刻）+ `gd_core/CoreCombat.gd:152-186` preordered 直通。两场 t=0 事件流逐字相同说明开战钩子面同序，但 run947 的 rng 失步与 run1101 的 PM 首周期差表明**抖动段/速度链仍有引擎级差异**——需要持 ORACLE_ALIGN_TRACE/ORACLE_TRACE_ITEM 的真 Godot 对跑（本卡禁跑 Godot，无法下钻）。
- PM 速度/热度链：getSpeed=1+speedScale+(heat−cold)×0.02（oracle/Items/Item.gd:3729-3752 ↔ gd_core/CoreItem.gd:376-398）；speedScale 只由 PM.onPrepare `addSpeed(0.3×numAffectedItems)` 注入（两侧同构，numAffected=3 由 C2PM 卡修复）。run1101 oracle 首周期 3.35s 要求均速≈2.357，gd 3.8333s 要求均速≈2.06~2.14——差额落在热度累积或 trace 口径（第 5 条），均非数据面。

## 可能解法（供后续串行卡）

1. 以 ORACLE_ALIGN_TRACE=1 + ORACLE_TRACE_ITEM=Perpetuum Mobile 重跑 gd 单场（gd_core_test），核对 gd 抖动段第 1..18/26 抽的物品指派序与 oracle rng_log 逐抽对位（_probe_draw_diff 已就绪）；先修 `gd_core_test/OracleAlignBattle.gd` item_trace 写入口径（现产物与 events.json 自相矛盾，见上）。
2. 对 run947：在 gd 侧把开局窗口逐抽与 `np2_or4/run947_r10/rng_log.txt` 对位，找第一处值错位（预期在 26 抖动段内或开战钩子段的音效抽序），定位是 shuffle 复刻（全局链台账）还是 sort 并列次序。
3. PM speed：先重验 oracle probe item_trace 的 speed=2.36 口径（疑 np3 探针旧态）；再以 tick 级 heat（T107 事件账）核 gd heat 累积是否与 oracle 一致。
4. 数据面无需改动：gen 工具（gen_lineup_fixture.py / gen_gd_core_data.py）本卡未跑，`gd_core_test/oracle_align_cases.json` 保持 914 场（本轮只读核对，未再生）。
