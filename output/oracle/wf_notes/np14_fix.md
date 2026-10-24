# np14_fix · 残场 13 场清零轮（阶段1：仪器对跑+根因定谳，2026-10-21）

## 结论（先答）

**本卡零产线改动（gd_core/gd_core_items 未动一个字节），13 场红场全部定谳并重新分簇：**

| 簇 | 场 | 定谳 | 可修面 |
|---|---|---|---|
| R 语料重录残留 | run906_r18 / run1125_r18 / run1371_r18 / run1409_r18 / run696_r18 | **语料侧录制工件，非 gd 缺口** | 语料侧（主控裁决），gd 侧禁修 |
| G1 滞留计时器 | run989_r18@686 / run1444_r18@330（gd 多弹）· run1132_r18@278（oracle 多弹） | 真 gd 缺口（CoreBuff 计时四分支/批账） | CoreBuff（历史敏感，留证待修程） |
| G2 阻力窗相位 | run602_r14@338 | 真 gd 缺口（np12_L3 §D 维持） | CoreTimer（两步走方案不变） |
| G3 同刻批拆 | run702_r18@423 | 真 gd 缺口（LG Blind 批拆 -7 v -6） | CoreBuff 同面 |
| G4 激活期闩 | run948_r18@42 / run844_r11@83 | 真 gd 缺口（激活期 playActivateAnimation 闩，gd 未闩→首武器攻多 5 抽） | CoreItem/CoreCharacter（待钉到件） |
| G5 隐形盲批 | run1022_r18@1386 | 真 gd 缺口（np12_L1 §3 维持，净录制下复证） | 未闭（隐形状态） |

## 1. R 簇定谳（本轮主发现）：语料重录残留的机理闭环

今日（10-21 09:52–10:32）语料只重录了 **32 场**（`find output/oracle/fights -name events.json -newermt 2026-10-21`），
其余 882 场仍是 10-06/07/09 旧批量批产物。32 场重录 = 单场单进程（暖场 + 正式场），
其中 **27 场 status=ok**（带 events_first.json = oracle_fight.gd:338-341 的 determinism 复跑，
语料 events = 第 3 次执行）,**5 场 status=timeout**（determinism 只对 ok 跑，oracle_fight.gd:339
`if first_res["status"] == "ok"`——语料 events = 第 2 次执行）。

**5 场 timeout 重录 = 今日红名单里的恰好 5 场**（906/1125/1371/1409/696）；27 场 ok 重录中 19 场绿。
机理：暖场若**自然结束**（endCombat→call_deferred("combatEndDeferred")），下一次执行开场前该
deferred 已被消化（combatEnd 复位 attackMovingForward=0、EventBus.disconnectAll() 清连）；暖场若
**超时截断**（事件闸 25000/墙钟 60s，watchdog break 不走 endCombat），第 2 次执行带着暖场残留：

- **攻击动画闩**：oracle_fight.gd 阻塞循环 tween 不推进，暖场把 PLAYER 节点
  attackMovingForward 置真后永不复位（oracle/Core/Character.gd:341 的复位在 combatEnd 里，
  超时路径不达）→ 正式场玩家首次武器攻**跳过本体 5 抽**（(0.9,1.1)×2+pick(0,2)+(0.8,1.2)+pick(0,2)）。
- **EventBus 双连**：disconnectAll（oracle/Core/Game.gd:2956，在 combatEndDeferred 内）未跑，
  暖场 prepare 的连接仍在 → 正式场每次 buff 变更**双份投递** → AoA 每笔 used 消耗双退。

证据（全部本轮实跑/实读）：
1. **结构性相关**：32 场重录清单 × status × 红绿 → 5/5 timeout 全红、19/27 ok 全绿
   （红名单另 8 场全部属于 27 ok 之内，见 G 簇各自根因）。
2. **抽级复现**（run906，probe=暖场+正式场单进程，ORACLE_FIGHTS_ROOT=output/oracle/probe/np14_fix）：
   probe 与语料在 idx0–309 全同（含首分歧 ev6 伤 12v11）；draw 级首分歧 @258——oracle 在
   (100,160) 后直接 randf×2（跳本体），gd 多跑 (0.9,1.1)×2+pick(0,2)+(0.8,1.2)+pick(0,2)
   共 5 抽 → 伤害掷 randi_range(15,16) 16 vs 15。整场 oracle 454 次 (100,160) 仅 1 次带本体
   （@47.233=对手首攻，对手节点每场新建不残留）。
3. **双退复现**：run1125 语料/我的 probe 都在首笔 -11 处双退 +3/+3（np12_L2 §3 的"+2/+3"系
   其 probe 进程里前场残留，非本征）；语料与 probe 在 ev135 后再歧（+2 vs +3，双实例/单实例
   usedStacks 记账之差，见 §4 未闭项）。refund 笔数统计（每笔 used 消耗后的退回数）：
   timeout 5 场大量 "2"（run906 {2:256,1:254,0:167}、run1125 {2:121,1:350,0:315}、
   run1409 {0:145,2:254,1:305}），ok 重录场绝无 "2"（run989 {0:332,1:118}、run1022 {1:2}）。
4. **反例锚**：15 个旧批量批 timeout 场（run1082/run1124/run685/run845/run894/run905 等）
   全绿——旧批量批经 CHUNK 配额退出有帧末 flush（oracle_fight.gd:236-239 注），无残留；
   run570_r18（旧语料，10-07）首武器攻 t=19.95 带本体=未闩，与 gd 逐事件全同（本轮 probe 实证）。
5. run1371 probe 在 ev51 与语料即歧（probe 8=语料 9 的反叉）——该场 probe 进程形状与录制批
   不完全同构，但 np12_L1 §4 已在旧语料时代独立证得「oracle 单进程=9、gd=8」，本簇判定不变。

**处置建议（超出本卡权限，供主控裁决）**：R 簇 5 场按「同构成重录」修语料——给 timeout 场
补一次 determinism 复跑边界（跑第 3 次执行取落盘），或重录驱动改成 warm+正式场+复跑三执行。
**禁 gd 侧迁就**：任何「玩家开局闩死/EventBus 双连」的 gd 补丁都会同时打破 882 旧语料场
（含 REG 九场）与 oracle 干净语义——np12_L2 §2 方案 B 在「语料=单进程混录」前提下已失效。

## 2. G1 滞留计时器（989/1444 gd 多弹；1132 oracle 多弹）

run989 实弹（np14v_confirm/run989_r18/rng_trace.txt BSCHED 行 5432–5475，今日 REG 同款 trace 腿）：

```
9.0833  GAIN +1 dur=5 → 批 14.0833x1 → 同刻 CLEANSE 清空 → STOP（act=F，left 保留 5）
…       停走观察遍：left→-1（last=5 保留）
9.3667  Burning Banner +1（事件 id685，双方同形；批 timeout=ctx.time+5=14.3833）
9.3833  BSCHED START br=B2（act=F left=-1 last=5）→ ②支 _timer_instant=true
        → 同 tick FIRE → POP 批 14.3833x1 → gd 多弹 id686 Blind TO -1 @9.3833
oracle  同位无此弹（@9.4 也无）
```

- gd ② 支（CoreBuff.gd:583-592，run688_r10 锚定「停走已观察+同 dur→残留下帧到期」）在
  run989 形状（清空→停走观察→一 tick 后新批 same-dur GAIN）下给**同 tick 瞬弹**并打掉新批；
  oracle drive_timers（oracle_fight.gd:880-919）同形状的引擎真值推演为 e[0]=-1→start(5)→
  eng==e[1]→e[0]=-1-dt→次遍 fire（@9.4），实测两处都无 → oracle 侧必有本卡未闭的隐形状态
  （候选：净化保护 flipPercent 使 oracle 批列表未清空/计时器未停；或 e[1] 非 5.0 的 f32 漂移）。
- run1444@330 同形（gd 多弹 Frostbolt Cold TO -2 @5.9833，批 +2 @5.9667 dur=3）；
- run1132@278 反向（oracle 多弹 LG Blind TO -7 @10.6333 整批打掉，gd 无）。
- **修程建议**（CoreBuff，历史敏感）：①先用 np14v_confirm 同款 BSCHED trace 腿对 1132 做
  oracle probe tick_states 对位，把 oracle「fire/不 fire」的判别量钉到 e[0]/e[1]/批列表三态；
  ②候选单笔：② 支加「停走观察须已跨 ≥1 个完整驱动遍」或 B2 改「次遍到期」（同 tick 不弹）——
  两者都动 run688_r10 ② 锚与 run634 idx450/540 ③ 锚的邻域，必须 REG 九场+run634/run688
  反例锚三重闸，本卡未动。

## 3. G4 激活期闩（948/844）——净录制下的新根因

run948（语料=ok 第 3 次执行=净语义；probe≡corpus 2677/2677 全同）：
- draw 级首分歧 @428 = 玩家首武器攻（Prismatic Sword @1.5833）：oracle **跳本体**直取
  randi_range(17,23)（伤 roll），gd 多跑本体 → 事件级 idx42 分叉（oracle +5 mana vs gd 毒 1）。
- oracle 闩源：战斗 t=0 激活相（进程钟 82.733=战斗 0）有 (0.9,1.1)×2 对（rng_log 行 446-447，
  后随 roll(0,100)×2，无 pick=非攻击体）= 某件带 damageRes 的激活调 playActivateAnimation
  （oracle/Items/Item.gd:4725 `if damageRes: character().playActivateAnimation()`）→ 闩死。
- gd 同窗同位置抽对存在（前缀至 427 全同）但 gd 旗标未闩（首攻跑了本体）⇒ gd 的该激活
  **没走 CoreItem.gd:1008 的 playActivateAnimation**（damageRes 判空路径与 oracle 不一致）
  或等价 2 抽来自别处。候选修面：CoreItem.activate 的 damageRes 构成（须逐件对位钉死哪件
  激活、gd 为何 damageRes=null）。run844@83（首武器攻 1.117，首事件分叉 2.9333）同族待同法钉。
- COMBAT_DELAY=2.5 在装配期烧完，激活相实际在战斗 t≈0（oracle_fight.gd:2671 callDelayed 链）。

## 4. 其余场（G2/G3/G5）维持旧判 + 本轮增量

- **run602@338**：np12_L3 §D 维持（疲劳显示阻力窗相位，CoreTimer changeTimer 语义）。
  本轮复证：语料=ok 净录制（11438 事件，probe≡corpus 全同），分歧不变（fatigue 3 v 4 @7.1）。
  修程仍按 §D 两步走（CoreTimer CTMR 取证桩先行）。
- **run702@423**：probe≡corpus 至 1589（@423 覆盖），LG Blind TO 同刻 -7（oracle）v -6（gd），
  同刻批拆/批账面，归 G1 同面（CoreBuff 批账）一并修程。
- **run1022@1386**：np12_L1 §3 维持——本轮复证语料=ok 净录制且 probe 与语料在 1385 前全同，
  gd 缺 Banner Blind TO -1 @13.0333 的结论在净录制下不变；隐形状态（null-item GAIN/
  批 timeout 读数）仍未闭，本卡无单笔可落。

## 5. 本卡执行记录与纪律

- **零产线改动**：gd_core/、gd_core_items/ 未改；未 commit/push；REG 九场未跑（脚本统一跑）。
- 语料 output/oracle/fights/ 与 oracle/ 树只读未动。
- 新增产物仅在 output/oracle/probe/np14_fix/：12 场单场 probe（906/948/844/570/989/1444/1132/
  602/702/1022/1371/1409/696/1125 中 14 目录）+ 仪器脚本 _cmp_draws.py（oracle rng_log↔gd
  rng_trace 逐抽对位）、_dump1125.py、_aoa_trace.py、_aoa_sim.py、_aoa_fit.py、_aoa_counts.py
  （AoA 双退状态机拟合，六个候选机全不合，机制未闭）+ 各 probe_*.log。
- 三方对位复跑：tools/_probe_gd_compare.py 对 np14v_confirm（今日 gd 腿，13/13 分歧复现）
  与 np14_fix probe（9 场全同、3 场窗口内同形、1371 反叉已注）。
- 判据未放宽；GDScript 面零补丁 ⇒ 无备份需求（output/_round_patches/np14_fix/ 空置待用）。
