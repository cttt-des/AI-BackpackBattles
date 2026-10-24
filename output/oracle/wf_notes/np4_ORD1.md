# np4_ORD1 · 开战序/位次并案修复笔记（run1051_r6 + run1441_r11 + run1499_r15 + 顺带 run947_r10/run1101_r18，2026-10-18）

## r1 验证结果（脚本统一执行，output/oracle/align/np4v_开战序位次并案_r1/）

**三目标场全绿**：run1051_r6 一致（ev=138）、run1441_r11 一致（ev=301）、run1499_r15 一致（ev=233）。
顺带场 run947_r10（idx6 RainbowPotion 选型）与 run1101_r18（idx172 PM 首周期）仍红——r2 定位结论见
§D / §E：run947 已在本卡文件面内修复（CoreCharacter.gd autoRage 改道全局链台账）；run1101 根因
为数据面（Magitecc Armor classes 位），超出本卡文件面，留档移交数据卡。

## 结论（定性）

三场首分歧根因全部落在**开战装配期（prepare/ctor 流）的链消耗形状**，共两枚、均为 gd_core_items
物品脚本面（本卡文件面内），已改码待脚本验证（status=patched）：

1. **DeckofCards.onCombatStart 的 `activate()` 误缩进**（run1051_r6 ev87 根因）。
2. **夹具 `connectorReadyRoll` 漏标 The Lovers / White-Eyes Blue Dragon**（run1441_r11 /
   run1499_r15 首分歧根因；数据面错、按卡面授权在两张物品脚本内补抽并带自失效闸）。

与卡面假设池的对位：「prepare 期 activate() 的音高归属」一族命中两枚（重放激活音高 +
CardConnector 装配音高）；「同 tick 双到期驱动序」「tie-rotation」未命中——开战激活序
（activation_order 复刻）在 ev0..86 逐字相同，无需处置。

## 证据链（本轮实际执行）

### A. run1051_r6（重放=语料）——DeckofCards.activate() 误缩进

- 逐抽对位 `python -X utf8 tools/_probe_draw_diff.py output/oracle/probe/np3_or4b/run1051_r6/rng_log.txt
  output/oracle/align/np4v_ordpre/run1051_r6/rng_trace.txt 8` → 首分歧第 34 抽：O `(0.9,1.1)=0.938029`
  vs G `(0.2,-0.2)=0.123943`，其后 35..39 逐值仍同 ⇒ **底层链同 raw、只有消费方不同**（见 §C）。
- 事件对读（`np3_or4b` vs `np4v_ordpre` events.json，去 type_name 规整后）：ev0..86 全同；
  **ev87 首歧** @8.55：O=[ev86 Lucky(Deck) → ev87 **Activation(Deck)** → ev88 Activation(Echoing)]，
  G=[ev86 Lucky(Deck) → **ev87 Activation(Echoing)**]——gd 的 Deck 激活事件整笔缺失、Echoing 抢先。
  t=8.85 玩家侧同签名（O ev93/94/95 vs G ev91/92）。
- 根因：`gd_core_items/DeckofCards.gd:88` 旧码 `activate()` 缩在 `if not chainStarted:` 块内（2 Tab），
  而 oracle 真源 `oracle/Items/DeckofCards.gd:69-77`（cat -A 逐字节核验）`activate()` 为单 Tab＝
  函数体级、**无条件执行**。Echoing Battlecry 的 `doCooldownEffect → item.repeatCombatStart() →
  onCombatStart`（gd_core/CoreItem.gd:672-675 ≙ decompiled_full/Items/Item.gd:3416-3419，两侧同构）
  重放牌库开战钩子时，gd 只发 Lucky、缺 Deck 的 Activation 事件与激活音高抽，Echoing 的自激活
  随即插到前面。t=0 首战（chainStarted=false）两侧都调 activate()，故 ev0..86 不受影响。

### B. run1441_r11 / run1499_r15——CardConnector 装配音高漏抽（夹具漏标）

- 注入后（post-injection）尾部逐抽对位：run1441 首歧 = gd `(0.3,1.0)=0.681945`（gd trace 行 424，
  战斗 t=0.75）vs oracle `(0.975,1.05)=1.015923`；run1499 首歧 = gd `(0.3,1.0)=0.437532` vs
  oracle `(0.95,1.05)=0.969647`。`(0.3,1.0)`＝FlickerAnimation.playAni 的 playback_speed 抽
  （`gd_core/CoreItem.gd:862`，flickerMinSpeed=0.3/flickerMaxSpeed=1.0）。oracle 的同族抽在
  战斗 t=1.65/2.9167（rng_log 行 543/770）——**同一族抽、不同时刻** ⇒ 战斗期链错位。
- 事件首分歧：run1441 ev18 = Ruby Whelp(ow3) DealDamage @1.3333 **O damage=5 vs G damage=6**；
  run1499 ev40 = Poison Spear @1.0167 同族值差。均为链错位后的首个掷点值漂移。
- 装配期盘点（关键）：gd 在 Gopen 前的装配抽＝86/224/216，oracle 抖动段（首个 0.95 抽）前＝
  **88/228/226**——各差 2/4/10＝每侧 1/2/5 抽，恰等于三场阵容里 `connectorReadyRoll=false`
  的卡实例数（run1051: The Lovers×1/侧；run1441: White-Eyes Blue Dragon×2/侧；
  run1499: The Lovers×1 + WEBD×4＝5/侧）。
- oracle 真源：全库仅 9 个 .tscn 场景挂连接器、全部为 Card 型（现场 glob 扫描）：
  Ace of Spades/Darkest Lotus/Deck of Cards/Holo Fire Lizard/The Fool/Joker/Reverse 场景
  （conn=true ✓）+ **TheLovers.tscn:312、White-EyesBlueDragon.tscn:286**（夹具误标 false ✗）。
  连接器 `_ready = Util.rng_trace_range(0.9,1.1)`（oracle/Items/Animations/CardConnector.gd:11）
  ⇒ 每实例装配期 1 抽。夹具实况：8 张卡 6 true 2 false， Potions 全 true——漏标恰为这 2 张。
- 逐抽形态互证（run1051）：oracle 装配 P 位 {34,41,80,87} ↔ gd（修复前）{40,85}；按装配序
  逐件推演（每件=2 抽 ctor+连接器 1 抽），oracle 34=玩家 The Lovers 连接器、41=Deck 连接器、
  80/87=对手侧同名——修复后 gd 应为 88 抽、P 位与 oracle 全同。run1441：oracle 58/61/64 =
  WEBD×2+Deck 连接器（gd 62=Deck，58/61 缺）。run1499：oracle 61=The Lovers 连接器。
- 传导机制：装配差被 rng_state 注入抹平（战斗期链态同源），**但装配期已定值的旁路对象泄漏**——
  FlickerAnimation 的 callDelayed 延迟（`CoreItem.gd:815-818`，实参求值即抽）取的是 gd 自己
  装配链位的值 ⇒ 缺连接器抽之后的延迟全部错值 ⇒ playAni 在错误时刻抽 `(0.3,1.0)` ⇒ 战斗期链错位。
  这正是 DATA1 笔记「抖动值→物品指派序/激活序排序复刻面」假设之外的第三条通路：**装配期形状差
  经 callDelayed 延迟值泄漏进战斗期**。

## 改码（均在卡面授权面内；备份 output/_round_patches/np4_ORD1/{gd_core_items,gd_core}/）

1. `gd_core_items/DeckofCards.gd`：`activate()` 移出 `if not chainStarted:` 块（单 Tab，与
   oracle/Items/DeckofCards.gd:77 同构），加注根因。t=0 行为不变；重放路径每次多 1 条
   Activation 事件 + 1 抽音高（oracle 同）。【r1 已验绿】
2. `gd_core_items/TheLovers.gd` / `gd_core_items/White-EyesBlueDragon.gd`：`_readyInit()` 在
   `._readyInit()` 之后补 `if not descriptor.connectorReadyRoll: ctx.rng.randf_range(0.9, 1.1)`。
   位置等价 oracle「子节点 _ready 先于根 _ready」（两卡 flicker/gemRoll 旗标均 false，无中间抽）；
   **旗标闸**保证数据卡日后把夹具改 true 后本行自动失效、不双抽。【r1 已验绿】
3. `gd_core/CoreCharacter.gd`（r2）：prepare() autoRage 选品 `ctx.rng.pickRandomElement` →
   `ctx.rng.pickRandomEngine(battleRageItems, "Core/Character.gd:326")`（详见 §D）。
4. `gd_core_items/Exclusive/Chess/ChessPiece.gd`（r2）：onPieceCaptured 的捕获音高域
   `randf_range(0.9,1.1)` → `(0.95,1.05)`（Util.randPitch() 默认 variation=0.05，Util.gd:682-683；
   run947 逐抽 343 假分歧消歧，详见 §D2）。备份
   output/_round_patches/np4_ORD1/gd_core_items/Exclusive/Chess/ChessPiece.gd。
5. 未动夹具（`gd_core_test/item_battle_fixture.json`）与 `assets/battle_items.json`
   （均不在本卡文件面）。

## 预期验证锚点（脚本统一执行）

- run1051_r6：gd 装配抽 86→88；战斗期 t=8.55 出现 [Lucky, Deck Activation, Echoing Activation]
  三连；与 oracle 事件全绿。【r1 已验：一致 ev=138】
- run1441_r11：gd 装配抽 224→228；`(0.3,1.0)` 抽应移到战斗 t=1.65/2.9167（oracle 行 543/770）；
  ev18 Ruby Whelp damage 回到 5。【r1 已验：一致 ev=301】
- run1499_r15：gd 装配抽 216→226；Poison Spear 首分歧消失。【r1 已验：一致 ev=233】
- run947_r10（r2）：Gopen 后不再出现 `pickRandomElement 0 0`（autoRage 改台账 Gpick，不进
  数值抽）【r2 已验：idx6 RainbowPotion 选型分歧消除】；ChessPiece 捕获音高域修正后
  逐抽 343 的假分歧应消失（O/G 同为 randPitch(0.95,1.05) 同值）。
- run947_r10 棋盘捕子残点（§D2）：需真 Godot 对跑核查 puzzlebag 叠放格在
  Inventory.filledCells 的归属——非本卡离线可闭合，已留档。
- REG 九场：阵容扫描证明 **REG 无任何一场含 The Lovers / White-Eyes Blue Dragon**；
  仅 run1514_r18 含 Deck of Cards×2（无 Echoing Battlecry，onCombatStart 只跑一次，
  `chainStarted=false` 路径行为不变）；run570/run635 的 rage 物品带 BattleRage 标签，
  autoRage 选品不触发（§D）——预期零回归。

## 残留与移交线索

### D. run947_r10（r2 顺带场，已在本卡文件面内修复）

- 事件首分歧 idx6 @t=0：RainbowPotion 六连 `pickRandomElement(0,6)` 选值序 O `4,3,2,2,4,4` vs
  G `2,2,2,4,4,0`（T105:3+T104:1+T103:2 vs T103:3+T105:2+T101:1）。
- 逐抽对位（`tools/_probe_draw_diff.py output/oracle/probe/np2_or4/run947_r10/rng_log.txt
  output/oracle/align/np4v_开战序位次并案_r1/run947_r10/rng_trace.txt 10`）：首歧第 168 抽——
  O 直接进入抖动段 `randf_range(0.95,1.05)=1.012243`，G 在 Gopen 后先有**两笔
  `pickRandomElement 0 0 => 0`**（1 元素数组取物）。此后 G 的每一段取值 = O 的对应段**前移一位**
  （G 抖动 j1..j12 = O j2..j13、G 多一笔末位补偿；对手段同构）——底层 u32 流在 G 的两笔 pick
  （各 1 u32 = O 一笔 randf_range 的量）处整体错位一位。
- 根因：`gd_core/CoreCharacter.gd:354`（改前）autoRage 选品 `ctx.rng.pickRandomElement(
  battleRageItems)`——消耗 **Util.rng 链**；oracle 真源 `decompiled_full/Core/Character.gd:312-326`
  用 `battleRageItems.pick_random()`——走**引擎全局 RNG**（Math::rand，不进 Util.rng 日志）。
  run947 每侧 battleRageItems 恰 1 元素（Spiked Staff：tags=32 无 BattleRage 标签、
  hasBattleRageEffect=true ⇒ isBattleRageItem 成立且无 BattleRage 启动物）⇒ gd 每侧多耗 1 抽、
  两侧共 2 抽 ⇒ 抖动值→物品指派整体前移 ⇒ RainbowPotion 六连选型错位。
- 修复（r2）：`gd_core/CoreCharacter.gd` prepare() 的 autoRage 选品改道
  `ctx.rng.pickRandomEngine(battleRageItems, "Core/Character.gd:326")`——开账路径走全局链台账
  （globalChainOpen 已按开局 shuffle 同额燃烧，与引擎链同链位，逐位等价 `Array.pick_random`
  且同种子可复现）；未开账路径直通 `Array.pick_random()`（与原版逐位一致）。
  回归面核查：autoRage 选品仅在「无 BattleRage 标签物品且有 isBattleRageItem 物品」时触发；
  REG 九场中含 rage 物品者（run570: Toolbox tags=64、run635: Wolf Badge tags=64）均带
  BattleRage 标签 ⇒ 选品不触发 ⇒ 零回归面。
- 备份：output/_round_patches/np4_ORD1/gd_core/CoreCharacter.gd。

### D2. run947_r10 r2 复验与新残点（r2 验证输出 + 本轮追踪）

- r2 复验：**idx6 RainbowPotion 选型分歧已消除**（CoreCharacter.gd autoRage 改道的直接效果）；
  事件首分歧从 t=0 推进到 **ev52 @1.566667**：对手棋盘（ow=3）黑方回合的捕获子不同——
  O=Black Pawn 捕 White Pawn（T105 mana+3），G=Black Rook 捕 White Pawn（T104+3）。
- 逐抽对位（r2 trace）：第 0..342 抽逐值全同；第 343 抽起 O=`randPitch(0.95,1.05)`（Util 链，
  ChessPiece.gd:74 的捕获音高）vs G=`randf_range(0.9,1.1)`（**gd_core_items/Exclusive/Chess/
  ChessPiece.gd:76 把 randPitch 误写为激活音高域 (0.9,1.1)**——注意 oracle Util.randPitch()
  默认域为 (0.95,1.05)，参照 decompiled_full/Utility/Util.gd:682-683 的 randPitch(0.3)=(0.7,1.3)；
  此差异只改映射不改笔数，Util 链在 344+ 重新逐值对齐）。
- **台账对齐证明（新工具结论）**：用 repo 内 output/godot_src/pcg.cpp 的 PCG32 常量
  （mult=6364136223846793005、inc=(1442695040888963407<<1)|1，python 复算）从本场 seed
  7499306 复原引擎链，gd r2 trace 的全部台账抽逐笔映射到**连续引擎位**：
  autoRage 两笔=@77,78（3875780676/2797622764）、tick1 白方静默调位=@79..134、
  tick2 白方=@135..183、tick3 黑方洗牌=@184（128500293，奇→reverse Fisher-Yates 不换序）
  ——**台账＝引擎链零缺口**。故捕子分歧不在链，而在棋盘/棋子语义输入：
  activeBlackPieces 基序（双方同 fixture 装配序 [Black Rook, Black Pawn]）+ 同一奇数抽
  ⇒ gd 与 oracle 应同序 [Rook,Pawn] ⇒ Rook 先扫；oracle 却以 Pawn 捕获 ⇒ oracle 的 Rook
  扫描未命中可捕目标（White Pawn 在 Puzzlebag L 的叠放格 [5,0]）。gd 的扁平格模型
  （夹具把袋内物品展平为与袋体同格的 overlap，CoreGrid filledCells 后写者胜）使
  `getItemInCell([5,0])` 命中 White Pawn；oracle 的 Inventory.filledCells
  （decompiled_full/Core/Inventory.gd:726-727）在叠放（puzzlebag 袋内物品）语义下
  同格归属存疑——需要真 Godot 对跑核查袋内叠放物品在 filledCells 的归属与
  ChessBoard.findPieceToCapture 的可见性（本卡禁跑 Godot，无法下钻）。
- 结论：run947 的棋盘残点定性为「puzzlebag 叠放格 × ChessBoard 捕获可见性」语义面，
  留给后续棋盘/袋子串行卡（带 Godot 对跑条件）。本卡 autoRage 修复保持有效且必要。

### E. run1101_r18（r2 复验：idx172 不变，数据面根因维持 §E 原判）

- 事件首分歧 idx172 @3.35：O 玩家 PM（Perpetuum Mobile）首周期三元组（T105 mana+8 → T13
  stamina → Activation）在场，gd 同刻无（gd 首周期 3.8333，T105 amount 还差 8 vs 9）。
  事件 0..171 逐字相同（含全部 t=0 钩子）。
- 逐抽对位（np2_or4 rng_log vs np4v_开战序位次并案_r1 rng_trace）：首歧第 860 抽——
  O `(-10,10)`（randInBox.x 标签）vs G `(100,160)`（挥击动画距离，CoreCharacter.gd:508 默认实参）
  ——同 tick 内消费方不同，为事件分歧的下游表现；第 0..859 抽逐值全同 ⇒ 装配/开战段无洞。
- 机化核算（本轮完成，接 np4_DATA1 §run1101 第 3/4 条）：PM 首周期 iterCd = 8×0.987074
  （激活序第 7 个 cd>0 物品，activation_order + rng_log 242.. 行复算，两侧同值）。
  - O：tick201（t=3.35）发火 ⇒ speed = 7.8966/(201/60) = 2.3572 ⇒ speedScale = 2.3572−1−
    (heat−cold)×0.02。取 heat−cold=8（DATA1 同款口径）⇒ speedScale = **1.1972 ≈ 1.2 = 0.3×4**。
  - G：tick230（t=3.8333）发火 ⇒ speed = 2.0604 ⇒ speedScale = **0.9004 ≈ 0.9 = 0.3×3**。
  - Δ 恰为一个受影响物品（0.3）。PM 四邻（fixture affected color0）：[3,3]=Magitecc Armor、
    [4,2]=Coil、[4,4]=Thunder Drake、[5,3]=Coil。gd 侧 classes：Coil=64、TD=64、**Magitecc
    Armor=0**（assets/battle_items.json 与 item_battle_fixture.json 同为 0）⇒ canAfect
    （isClassItem(Engineer)，gd_core_items/Exclusive/PerpetuumMobile.gd 内联
    `classes & (1<<6)`）漏数 Magitecc ⇒ numAffected 3 vs 4。
  - oracle 侧 Magitecc 必为 Engineer（classes 含 bit64；解密 CSV 该行 classes 列 = 65 = 64+1，
    与 np4_HOLD 同款「解密 CSV 可作旁证不可作真源」口径）⇒ **数据面错：Magitecc Armor
    classes 0 → 65**。
- 移交（数据卡，与 np4_HOLD 同族）：改 `assets/battle_items.json` 的 Magitecc Armor classes
  0→65，重生 `gd_core_test/item_battle_fixture.json`（gen_fixture 链）与
  `assets/gd_core_runtime.json`（脚本统一执行）。改前建议按 np4_HOLD §5 的全语料约束求解
  把 classes 位一并清干净（本场地已提供一条硬约束：Magitecc ∈ Engineer）。
  与 np4_DATA1 的「可能解法」关系：本条覆盖其第 3 条（PM speed 热度/口径面）——热度(8)双侧一致，
  差额全在 numAffected。
- 本卡未动 Magitecc 数据/脚本（按 np4_HOLD 先例：不在物品脚本里手写 classes 白名单绕过数据）。

### F. 其它残留

1. **夹具 connectorReadyRoll 漏标**（§B/改码 2 的上游）：数据卡修 The Lovers / White-Eyes
   Blue Dragon 为 true 后，两卡脚本的条件抽自动失效（旗标闸），无需回改脚本。
2. **harness item_trace 写入口径**（np4_DATA1 判两条 item_trace 不可信）：OracleAlignBattle.gd
   的 ORACLE_TRACE_ITEM 写入面仍在（诊断面，本卡文件面内），本轮未动——它不进判定链，
   留给后续需要 F7 曲线的卡片顺手修。
3. py 腿（gd_core_py）：CoreCharacter.prepare 的 pickRandomElement 同样错 chain，需转写器
   重跑同步（本卡禁跑 gd_to_py.py）。
