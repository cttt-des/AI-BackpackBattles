# np6_A1 · 棋盘捕子族分析笔记（run947_r10 ev52 + run1051_r6 ev87，2026-10-19）

卡片：修复·棋盘捕子族（阶段1＝只做离线分析 + oracle probe 仪器对跑，禁改文件面）。
结论：**blocked（两场根因均已钉死到 file:line，但全部落在本卡文件面之外；未改任何文件面代码）**。
本卡文件面（CoreGrid/CoreItem/ChessBoard/Chess/*/Bag 族）经仪器逐项核对**全部与 oracle 逐位同构，无一处缺陷**；
np4_ORD1 §D2 的「puzzlebag 叠放格 × findPieceToCapture 捕获可见性」假说被证伪（见 §4），棋盘串行卡无需再立。

## 1. run947_r10 ev52 根因（定谳）

**gd 数据面 `Spiked Staff has_battle_rage_effect=true` 是错数据；oracle 真值 = false。**
由此 gd 在 prepare 期 autoRage 选品消耗 2 笔引擎台账抽（每侧 1 笔），oracle 消耗 **0 笔**（battleRageItems
为空、`if not battleRageItems.empty()` 不点火）⇒ gd 引擎链从 prepare 起整体 +2 幻影。棋盘黑方回合
（tick94，t=1.566667）的 `activePieces.shuffle()`（n=2，恰好 1 抽）是开战以来**第一个对抽值敏感**的
消费点：奇偶决定 Fisher-Yates 是否换序 ⇒ 双方读到的抽值不同 ⇒ activeBlackPieces 扫描序翻转 ⇒
捕获子翻转（G=Black Rook 捕 White Pawn T104+3，语料=Black Pawn 捕 White Pawn T105+3）。

### 1.1 证据链 A：oracle 引擎链真实位次（PCG32 定位）

用 tools/rng_golden_model.py 的 PCG 常量（MULT=6364136223846793005、INC=(1442695040888963407<<1)|1、
seed 播种 = pcg32_srandom_r 两笔铺垫）复算 seed=7499306 的引擎流，并在 oracle 真机（本卡 probe，
产物 output/oracle/probe/np6_A1_rook/）上用「单点 randi() 测量法」实测链位（每跑只测一个点，测后链
被本测量污染故不跨点复用）：

| 测量点 | probe 实测 next 值 | 流中 0-based 位次 p（=已消耗笔数） |
|---|---|---|
| activateItems 之后（开 tick 前） | 3875780676 | **76** |
| tick47 末（白方第 1 回合后） | 3492614071 | **132** |
| tick70 末（白方第 2 回合后） | 1620950222 | **181** |
| tick93 末（黑方回合前夜） | 1620950222 | **181**（70→93 引擎零消耗 ✓） |

对照 np4_ORD1 §D2 的映射（该映射 @N 即 0-based N−1，已用 128500293↔位次 183、3875780676↔位次 76
双点校准）：np4 把 autoRage 记在 @77,78（位次 76,77）⇒ tick1 窗口 @79..134、tick2 @135..183、
tick3 黑方洗牌 @184=128500293（奇→不换序→[Rook,Pawn]→车捕获＝gd 行为 ✓）。
**oracle 实测：prepare+activate 只消耗到位次 76（即 autoRage 一笔都没耗）**；tick1 窗口＝76..131
（56 笔，与 np4 窗口宽度一致 ✓）、tick2＝132..180（49 笔 ✓）。唯一分歧段＝prepare 的 autoRage 两笔。

**推演（全链复算，逐位对上双侧实况）**：
- oracle：tick94 黑方洗牌读**位次 181 = 1620950222（偶）**→ `j=rand()%2=0` → swap →
  activeBlackPieces 翻转为 [Pawn, Rook] → **兵先扫**：captureCells
  {(-1,-1),(1,-1)} 含 (5,0)=White Pawn（canAffect=true）→ 捕获 [BlackPawn, WhitePawn] →
  **＝语料 ev52（type105 Black Pawn amount 3）** ✓。随后 captureSounds.pick_random 耗位次 183。
- gd：台账流位次 183 = 128500293（奇）→ 不换序 → [Rook, Pawn] → 车先扫 → 捕 White Pawn →
  **＝gd np5v_final ev52（type104 Black Rook amount 3）** ✓（gd_core_test/OracleAlignBattle
  np5v_final/run947_r10/rng_trace.txt 行 646-647：`Gshuffle ChessBoard.gd:80 2 => 128500293`、
  `:100 20 => …`＝车 20 格洗牌后即捕获，兵未扫描）。
- 白方两回合（tick47/70）虽同样读到错位抽值，但 backward-FY 对 n=3 的位置 0 不动 + 本局面只有
  White Bishop 一个可动子 ⇒ 结果对抽值不敏感 ⇒ ev0..51 两侧全同——这解释了分歧为何**恰好**在
  tick94 才暴露。

### 1.2 证据链 B：autoRage 数据真值（oracle 引擎内直读）

probe_rage.gd（复刻装配+prepare 后逐物品 dump descriptor 真值，rage_dump.txt）：

```
RAGE P Spiked Staff bre=False tagBR=0 isBRI=False
```

oracle/Core/Character.gd:311-326：无 BattleRage 标签物品时收集 `isBattleRageItem()` 物品
（oracle/Items/Item.gd:5408-5409 ＝ `descriptor.hasBattleRageEffect`）⇒ run947 双侧
battleRageItems=**空** ⇒ `if not battleRageItems.empty()`（:324）不点火 ⇒ **0 抽、autoRageItem=null、
autoRageTimer 不 start**。
gd 侧现状：assets/battle_items.json `"Spiked Staff" … "has_battle_rage_effect": True`、
gd_core_test/item_battle_fixture.json `"Spiked Staff" descr.hasBattleRageEffect=True (tags=32)` ⇒
gd_core/CoreCharacter.gd:347-360 收进 1 元素 ⇒ :360 `ctx.rng.pickRandomEngine(battleRageItems,…)`
每侧耗 1 笔台账 + autoRageTimer 启动（行为面也多一个 oracle 没有的激怒）。
np4 §D 当年从 gd 数据反推「每侧恰 1 元素」——**方向反了：数据错、引擎真**。

### 1.3 修复方案（均不在本卡文件面，移交）

1. **数据卡**：assets/battle_items.json 的 `Spiked Staff.has_battle_rage_effect True→False`
   （唯一有本卡实测支撑的一条）；随后脚本统一重生 gd_core_test/item_battle_fixture.json 与
   assets/gd_core_runtime.json。改后 gd prepare：battleRageItems 空 → CoreCharacter.gd:353
   守卫跳过 → Util 链/引擎链双对齐（0 抽＝oracle）、autoRageTimer 不启动＝oracle 同构。
   其余 15 个 bre=true 物品（Wolf Badge/Berserker Bag/Toolbox/Spiked Collar/Double Axe/Chain Whip/
   Dragonscale Armor/Dragon Claws/Dragonskin Boots/Busted Blade/Deer Totem/Brass Knuckles/
   Badger Rune/Extra Angy/Dragon Set）**本卡未测**，移交数据卡用 probe_rage.gd（PROBE_RUN/
   PROBE_ROUND 可换场）按 np4_HOLD §5 全语料约束口径逐一定谳——其中带 BattleRage 标签(64)者
   （Wolf Badge/Berserker Bag/Toolbox）走 hasBattleRageStarter 支路、bre 位无关。
2. **gd_core/CoreCharacter.gd（np5_K1 补丁③）处置：保持不动**。:353 空列表守卫与 oracle :324
   同构；数据修复后 pickRandomEngine 仅在 battleRageItems 非空时点火，条件与 oracle pick_random
   完全一致 ⇒ 补丁③在正确数据下即正确，无需回退无需再改。
3. **预期验证锚点（脚本统一跑）**：run947_r10 全绿（ev52 捕获子回到 Black Pawn，白方两回合不受
   影响）；REG 九场含 Spiked Staff 者为零（实扫：run570=Toolbox+Spiked Collar、run635=Wolf Badge，
   均非 Spiked Staff）⇒ 本数据笔 REG 零回归面。

## 2. run1051_r6 ev87（@8.55 Echoing Battlecry 激活序翻转）——不同根，证据维持 np4 §A

- 阵容实扫（oracle_align_cases.json run1051_r6）：**无任何 Chess/* 棋子**，袋族仅 Leather Bag/
  Fanny Pack（非 Puzzlebag 族，且与捕获面无关）——本卡文件面的脚本在该场无一参与。
- 现状复核：gd_core_items/DeckofCards.gd:88 `activate()`（3 Tab）仍缩在 `if not chainStarted:`
  （:79，1 Tab）→`if not cards.empty():`（:82）块内；oracle/Items/DeckofCards.gd:77 `activate()`
  单 Tab 无条件执行。重放路径（Echoing repeatCombatStart→onCombatStart，chainStarted=true）下
  gd 整笔跳过 activate() ⇒ 缺 Deck Activation 事件与激活音高抽 ⇒ Echoing 自激活抢位 @8.55。
- 修复＝np4_ORD1 收尾 #1 原样认领：`activate()` 移出 if 块（单 Tab，oracle 同构）；np4-r1 已验绿
  （ev=138 一致），np4 收尾回滚后无人再认领。文件 gd_core_items/DeckofCards.gd 不在本卡文件面。

## 3. 本卡实际执行的仪器与命令（产物全部在 output/oracle/probe/np6_A1_rook/）

- probe_cells.gd / probe_ticks.gd / probe_randi.gd / probe_rage.gd / probe_shuffle.gd（本卡新写，
  放 probe 目录；oracle/ 树零写入；SceneTree 逐字复刻 oracle_fight.gd 装配/prepare/tick 驱动）。
- `PROBE_RUN=947 PROBE_ROUND=10 PROBE_OUT=… ./output/godot36/Godot_v3.6-stable_win64.exe --headless
  --audio-driver Dummy --path oracle --script <probe 绝对路径>`（外部绝对路径 --script 在该二进制
  可用，probe 首跑即验证）：
  - cells_dump.txt / cells_dump2.txt：双侧 filledCells/bagCells 全量、装配序、棋子
    pieceColor/occ/tlmap/moveCells、逐棋子静态扫描表、isTypeInInventory(Chess Master)=False。
  - ticks_dump.txt：tick 46/47/70/71/93/94 边界棋子+扫描表——**tick94 后 Black Pawn occ=(5,0)
    ＝真机自复现语料捕获行为**（probe 用逐字搬运的 tick 驱动跑真实战斗至 tick96）。
  - randi_{activate,t47,t70,t93}.txt：§1.1 的四个链位测点。
  - rage_dump.txt：§1.2 descriptor 真值。
  - probe_shuffle.gd 输出（stdout）：seed 1..16 上 n=2/n=3 shuffle 结果 vs 前两抽奇偶相关表——
    **flip ⟺ 首抽为偶** ⇒ 该二进制（Godot 3.6）Array.shuffle()＝backward Fisher-Yates
    （i=n-1..1，j=rand()%(i+1)），gd_core/CoreRng.gd:181-183 的注释与台账算法**正确**（维持，
    非缺陷）。
- 离线：tools/rng_golden_model.py PCG 复算 seed=7499306 流，定位 §1.1 各值位次；
  gd 台账对读 np5v_final/run947_r10/rng_trace.txt（行 487-505 白方两回合、646-647 黑方回合）；
  双侧 events 对读 output/oracle/fights/run947_r10/events.json 与
  output/oracle/align/np5v_final/run947_r10/events.json（ev51 全同、ev52 分歧、ev53 同为
  White Pawn tl(5,0)）。

## 4. 被证伪的候选（本轮逐项排除，均为仪器实证而非推测）

1. **np4 §D2「puzzlebag 叠放格 × filledCells 归属」**：cells_dump 证明双侧 filledCells/bagCells
   语义与内容完全同构（F (5,0)→White Pawn 双侧一致；bagCells 拆分、isCellEmpty、getItemInCell
   全同）⇒ 捕获可见性无差、残点不成立于格子语义。gd_core/CoreGrid.gd:38-40,74-75,88-89,188-194
   与 oracle/Core/Inventory.gd:621-627,716-717,726-727 逐行同构。
2. **装配序/activeBlackPieces 基序差**：lineups.json（oracle_fight.gd:1306-1323 快照
   getItems() 原序）与 gd 夹具序逐位相同（[Black Rook(33),…,Black Pawn(38)]）；BOARD dump
   black=[Black Rook,Black Pawn] 双侧一致。
3. **moveCells 形状/尺寸差**：BlackRook.tscn CollisionMap tile_data 解码＝20 格十字（tile4），
   与 gd 夹具 affected 20 格集合相同；cells_dump2 PIECE 行 moves=20/8/2 逐子一致。
4. **Chess Master 分流**：BOARD 行 master=False（findPieceToCapture 路径，双侧同）。
5. **shuffle 方向差**：§3 probe_shuffle 实证 backward-FY，双侧同算法（gd CoreRng 台账同构）。
6. **扫描序（captureCells 排列）**：车的可达集内可捕获目标仅 (5,0) White Pawn 一格
   （SCAN 全表：其余 aff=False），序不影响 findPieceToCapture 返回值——序差不是分歧原因。

## 5. 移交与残留

- 数据卡：§1.3-1（Spiked Staff 笔 + 其余 bre 物品的 probe 定谳流程）；工具 probe_rage.gd 随取。
- DeckofCards 卡（或任意可改 gd_core_items 的卡）：§2 的 activate() 出块（np4 收尾 #1 认领）。
- np4_ORD1 §D2「棋盘捕子残点需 Godot 对跑」已由本卡闭合：无需棋盘串行卡；np5_K1 §2 补丁③
  （ChessPiece 捕获音高 (0.95,1.05)）维持不变。
- 本卡零文件面改码、零备份需求（output/_round_patches/np6_A1/ 不设立）；git 状态复核无本卡
  引入的 tracked 改动。
