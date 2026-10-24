# np9_L3 — FalseLife overheal→giveMaxHealth 族（run1303_r18 / run1126_r5）根因取证

结论先行：**blocked（根因在冻结语料侧的生成期批次状态，不在 gd_core 文件面；阶段1 未改任何文件）**。
gd_core 当前行为与「同种子、同 rng_state 的干净神谕复跑」逐抽逐事件全同；语料里多出来的
TMH（TemporaryMaxHealth, type=19）事件是语料生成那次批跑的跨场残留/修订产物，任何 gd 侧补丁
若强行复现这 2 场，必然破坏语料内其余 150 场同路径对局与 REG（判据不可放宽 → 不可修）。

## 1. 事件语义澄清（本卡前提修正）

type=19 是 `TemporaryMaxHealth`（非 heal，heal 是 type=12 Health，见 gd_core/CoreConst.gd
EventType 枚举、oracle/Core/Game.gd:441-484 同源）。目标场的首分歧笔：

- 语料 run1303_r18 @1.366667：ev4 = DS 吸血治疗 10（type12）→ ev5+ev6 = FalseLife
  TMH amount=12 **两笔**（parent 都是 ev4）→ ev7 = DS Activation。
- gd / 干净复跑：ev5 = TMH 12 **一笔** → ev6 = DS Activation。
- 机制链：Character.heal 过疗 → emitSignal("character_overhealed") → FalseLife.onOverheal
  → Item.giveMaxHealth(overheal) → changeMaxHealthTemporary → TMH 事件
  （oracle/Items/Item.gd:4222-4227；gd_core/CoreItem.gd:2055-2072）。

## 2. 关键实测（本轮全部跑过，命令见 §5）

1. **语料普查**：920 场语料中 159 场含 FalseLife 过疗 TMH；按 (parent,owner) 分组——
   玩家侧单笔 150 场 / **玩家侧双笔仅 5 场**（run1125_r18、run1175_r11、run1303_r18、
   run846_r11、run906_r18）/ 4 场仅对手侧。同一条代码路径在语料内部自相矛盾（150:5），
   双笔不可能是原版确定性语义。
2. **干净复跑（probe）**：`ORACLE_FIGHTS_ROOT=output/oracle/probe/np9_L3_fl` 重跑两目标场
   （同 seed、同 fights.json）：
   - run1303_r18：probe events=2687，ev6=DS Activation（**单笔**）；与
     output/oracle/align/np8_1303/run1303_r18/events.json（gd 腿）**2687/2687 事件零语义差**
     （仅 type_name 字段格式不同）。
   - run1126_r5：probe events=92 与 output/oracle/align/gdcore/run1126_r5/events.json
     **92/92 零语义差**；语料只有 88 场，首分歧在 ev22（语料多一笔 FL TMH=2）。
3. **逐抽对位**（本卡指定检查）：`python -X utf8 tools/_probe_draw_diff.py
   output/oracle/probe/np9_L3_fl/run1303_r18/rng_log.txt
   output/oracle/align/np8_1303/run1303_r18/rng_trace.txt` →
   **oracle 数值抽 11632，gd 数值抽 11632（差 +0），前 11632 抽完全一致**。
   heal→overheal 链上游不存在任何值差——本卡「治疗量计算/过疗阈值 rng 差」假设证伪。
4. **rng_state 逐字节一致**：语料与 probe 的 run1303_r18 / run1126_r5 rng_state.txt
   完全相同（run1303: seed=-8390059292541597435 state=2110013093896508288）。同链状态 +
   同代码 → 两种不同事件流，证明语料的额外事件来自**链状态之外**的隐藏状态
   （角色 curHealth/temporaryMaxHealth/temporaryMaxHealthGain/连接表——全是无事件面）。
5. **run1126_r5 细节**：probe rng_log 第 205/209 行（t=1.0 两笔 Regen 治疗 type12）之后
   **无 randInBox 物品标签对** → 两侧过疗均未发生 → 玩家在 t=1.0 缺血 ≥2；语料却有
   TMH=2（过疗 ∈[1.67,2.08] → 玩家近乎满血）。语料生成时玩家带了 +≥2 的无事件血量差
   进场（跨场残留面）。注意语料 lineups.json（10-17 lineups-only 补导）与战斗 events
   （10-07 批）非同一次产物，hp 字段不可互证。

## 3. 为什么 gd 侧不可修（判据不放宽前提）

- 复现 run1303_r18 的「玩家侧过疗双笔」需要**无条件给玩家侧 character_overhealed 双派发**
  （oracle/Core/Character.gd:765 / gd_core/CoreCharacter.gd:865 单发点；EventBus
  connectEvent 唯一调用链 oracle/Items/Item.gd:5705 → oracle/Utility/EventBus.gd:98-109，
  FalseLife.gd:13 是唯一过疗连接点）——这会同时污染语料里 150 场单笔对局与 REG 全部
  FalseLife 相关场。
- 复现 run1126_r5 需要让玩家开局凭空多 ≥2 血——只能靠语料生成期的跨场状态，逐场独立
  重放的 gd 内核没有任何逐场输入能区分这 5+1 场与其余场（rng_state 同构）。
- 双笔五场与单笔 150 场在语料里共存 ⇒ 不存在能同时满足语料自身的确定性规则。

## 4. 根因定位（file:line 线索）

- 派发/连接面（两侧逐字同构，排除）：oracle/Core/Character.gd:739-772 ↔
  gd_core/CoreCharacter.gd:830-871；oracle/Utility/EventBus.gd:98-116 ↔
  gd_core/CoreEventBus.gd:121-144；oracle/Items/Exclusive/FalseLife.gd:11-21 ↔
  gd_core_items/Exclusive/FalseLife.gd:12-24；oracle/Items/Item.gd:4222-4227 ↔
  gd_core/CoreItem.gd:2055-2072。
- 真根因面：**冻结语料 run1303_r18/run1126_r5（events.json 落盘 2026-10-07 05:10）生成
  那一批进程的隐藏战斗外状态**（玩家侧健康/连接表/引擎修订），非当前 oracle 树行为——
  当前树复跑即不复现。result.txt 所记 [M6c]/[M7] 的 cleanse+逐字节自检只能保证
  「同进程自洽」，拦不住「跨进程/跨修订」漂移。
- 待办建议（超出本卡权限，供主控裁决）：
  a) 用当前 oracle 树重生成 run1125_r18、run1175_r11、run1303_r18、run846_r11、run906_r18
     （及 run1126_r5 一并复核）的语料 events.json/rng_state.txt；或
  b) 将上述场移出 REG/目标集并留档（语料内部不一致属已知缺陷）。

## 5. 本轮实际执行记录

- probe 复跑（产物仅在 output/oracle/probe/np9_L3_fl/）：
  `ORACLE_FIGHTS_ROOT=…/output/oracle/probe/np9_L3_fl ORACLE_ONLY_CASES=run1303_r18,run1126_r5
  ORACLE_DEBUG=1 ORACLE_STACKTRACE=1 ./output/godot36/Godot_v3.6-stable_win64.exe --headless
  --audio-driver Dummy --path oracle --script oracle_fight.gd` → PASS，两场 ok
  （run1126 563 ticks / run1303 2075 ticks）。
- 逐抽对位：见 §2.3（11632/11632 一致）。
- 语料普查脚本：遍历 output/oracle/fights/*/events.json 统计 (parent,owner) 分组（§2.1 数字）。
- STACKTRACE 列为空（该 Godot 构建下 get_stack() 返 null），未获逐抽调用栈；机制链靠
  事件 parent/amount 算术 + rng_log 抽型窗口钉死，不影响结论。
- 红线遵守：output/oracle/fights/ 与 oracle/ 只读未动；未跑 gd 验证腿（用既有
  np8_1303/gdcore 产物）；未改任何代码文件（阶段1）。
