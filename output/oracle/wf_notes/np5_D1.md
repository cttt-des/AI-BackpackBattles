# np5_D1 — battle_items.json classes 数据修复（Spectral Dagger、Magitecc Armor；Shaman Mask 证伪不改）

日期：2026-10-18
卡片：修复·数据面classes三处
结论：**patched（2/3）**。Spectral Dagger 0→127、Magitecc Armor 0→65 已改并再生；
Shaman Mask 4→127 **被全语料约束证伪，未改**（见 §3，np4_HOLD §5.1 的该项结论有误）。

## 1. 改动与再生

- `assets/battle_items.json`：Spectral Dagger `classes` 0→127；Magitecc Armor `classes` 0→65。
  外科式文本替换（各 1 处，net +3 字节），Shaman Mask 保持 4。
- 再生：`python -X utf8 tools/gen_lineup_fixture.py`（重写 gd_core_test/item_battle_fixture.json；
  gd_core_test/LineupFixture.gd 逐字节不变——其 53 件嵌入物品不含这两件）、
  `python -X utf8 tools/gen_gd_core_data.py`（重写 assets/gd_core_runtime.json）。
  产物结构 diff 各仅 2 个叶子（两处 classes），无其他漂移。
- `gd_core_test/oracle_align_cases.json` 核对仍为 **914 场**（本卡未触碰该文件；
  case 条目不含 classes 字段，无需再生）。
- 备份：output/_round_patches/np5_D1/{assets/battle_items.json, assets/gd_core_runtime.json,
  gd_core_test/LineupFixture.gd, gd_core_test/item_battle_fixture.json}。

## 2. Spectral Dagger=127 的定谳（全语料 Holdall 约束求解）

分析脚本 output/_np5_D1_solve.py（只读，对 914 场逐场重放 gd_core/CoreGrid.gd 的
filledCells 语义：装配序逐件写入 occupied 格、后写者胜；Holdall 6 格去重最终占用者；
count=classes==127 件数；oracle 量=amount/8，Holdall block=8）：

- 修复前：全语料 **170 个 Holdall 事件中 168 对 2 错**，唯二错处=run1347_r18 双侧
  （oracle count=2，gd count=0；包内 5 件：Spectral Dagger×2、Steel Dragon、Tiger Rune、
  Shaman Mask）。其余任何场都没有 SD/SM 进包（有包内含物的对上事件仅 run782、run1347）。
- run782_r18 的 (7,2) Holdall：包内={Heroic Potion(127), Steel Dragon, Tiger Rune}，
  oracle count=1=gd count=1 ⇒ **Steel Dragon、Tiger Rune 非 127**（np4_HOLD 的该条排除法
  经现夹具复核成立）。
- ⇒ run1347 约束：2·[SD=127] + [SM=127] = 2（SD 有两件在包内）⇒ **SD=127 唯一解**。
- 修复后重跑：**172/172 全对，0 错**。14 个无配对 Holdall（run691/841/961/1077/1121/1132/1317）
  修复前后 gd count 均=0 且不含 SD/SM（双侧无事件，互洽）。

## 3. Shaman Mask 4→127 证伪（np4_HOLD §5.1 该项结论撤销）

np4_HOLD §3 把 run1347 包内列为 4 件（Spectral Dagger(4,0) 一件、Steel Dragon、Tiger Rune、
Shaman Mask），按「恰 2 件中立」推出 SD+SM=127。**该清单漏了一件**：夹具中第二把
Spectral Dagger occ=[[3,1],[4,1]]，其占格 (4,1) 与 Holdall occ（[[4,0],[4,1],[5,0],[5,1],
[6,0],[6,1]]）相交；gd 运行时装配链 `OracleAlignBattle.gd:278,293` → `CoreGrid.addItemCells`
（gd_core/CoreGrid.gd:188-194，包→bagCells、非包→filledCells，**无重叠拒绝、后写者胜**）→
`CoreGrid.getItemsInCells`（仅读 filledCells，gd_core/CoreGrid.gd:93-101）必把它数入。
若 SM=127：count=SD×2+SM=3 ⇒ block=24 ≠ oracle 16，run1347 仍旧分歧。
np4_HOLD 的 4 件清单系按 top_left 落点归包（SD#43 top_left=(3,1) 在 Holdall 区外），
与 gd 运行时的占格相交口径不符——现夹具下该项推论作废。SM 维持 4，**待新的独立约束
（如未来出现含 SM 的其他包内对上场）再定其真值**。

## 4. Magitecc Armor=65 的复核（独立于 np4_ORD1 §E 复算）

从 gd_core_test/oracle_align_cases.json run1101_r18 直读：双侧 PM occ=[(4,3)]、affected
color0={(3,3),(4,2),(4,4),(5,3)}，命中物品=Magitecc Armor(3,3)、Coil(4,2)(5,3)、
Thunder Drake(4,4)（另有 Leather Bag/Stamina Sack/Fanny Pack 重叠，均无 Engineer 位）。
gd 侧 classes：Coil=64、TD=64、Magitecc=0 ⇒ PM 内联 canAffect（gd_core_items/Exclusive/
PerpetuumMobile.gd:20，isClassItem 门 + classes&(1<<6)）数 3；oracle 数 4（np4_ORD1 §E
机化核算 speedScale 1.2=0.3×4）⇒ Magitecc 必含 bit64(Engineer)。65=64|1，其 bit0(Ranger)
在战斗链无消费方（isClassItem()/isAvailableFor 的战斗内调用只有 Engineer 位：
TeslaCoil/Laboratory/PM），64 与 65 不可区分、无冲突，从卡面取 65。
另注意：decompiled_full/Sheets/CSV/ItemData_e.csv **没有 classes 列**（46 列头核验），
np4_ORD1 §E 所引「解密 CSV classes 列=65」实为该行 block 列值（Magitecc block=65），
旁证引用有误但结论不依赖它。oracle 真源 ItemData_e.csv 为 GDEC 加密（头字节现场核验），
离线不可读；output/ 下两份 _live/_dec 转储亦为密文。

## 5. 风险面与判据

- classes 翻正只能向 oracle 真值收敛：对任一「假绿」场，若消费方读该物品 classes，
  oracle 侧同链同输入必早已分歧（真值不同）；故翻正不会破坏真绿场。
  SD=127 新增的 isNeutral 消费面（Twine canAffect_secondary、Holdall 之外）同理对齐。
- 回归电池 REG 九场由验证方脚本执行（本卡禁跑 Godot）；目标场 run1347_r18 预期
  Holdall 事件对齐（count 2=2），能否全绿取决于该场其余 latent 分歧。
- py 腿（gd_core_py）运行时直读 assets/battle_items.json，自动随新值；其 Holdall
  从不触发的独立缺陷归 np4_HOLD §5.2 另卡。
