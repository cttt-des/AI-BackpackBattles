# C5TRIO 泳道定谳笔记（r35 K06/K13/K20，2026-10-17）

状态：**blocked**（三根因均在卡面外，修点已定位到行，移交对应泳道）。
配套：台账 `output/alignment_fix_log.md`「r35 K06/K13/K20 取证+修复」节；
取证脚本 `C5TRIO_diff.py / C5TRIO_geom.py / C5TRIO_probe.py / C5TRIO_probe2.py / C5TRIO_timeline.py`（同目录，只读）。

## 0. 工检基线

七卡面场（run608_r18/run613_r18/run729_r14＝GirlPower；run805_r18/run879_r11＝Armored Power Puppy；
run1172_r18/run1176_r11＝Crown 治疗）alignment.json 全部 `oracle≠gdcore`，且 gdcoreEvents==pyEvents、
judgement.gd_py==true → py 镜像忠实，分歧源在 gd_core（gd+py 同错）。
三对脚本逐行同构：`gd_core_items/{Crown.gd, Exclusive/GirlPower.gd, Exclusive/ArmoredPowerPuppy.gd}`
↔ `oracle/Items/{Crown.gd, Exclusive/同名.gd}`，仅 onready→_readyInit、`Util.`→`ctx.util.`、视觉行差异。
→ **卡面（6 文件）零可修差，零修改落地，无备份目录，gd_to_py.py 未跑**。

## 1. K13 APP 恢复（run805_r18 idx100 / run879_r11 idx45）——根因已定谳

### 根因
oracle 的激活音高消耗走**虚调用链**：
`activate() → playActivationSound()（oracle/Items/Item.gd:4676-4677）→ playDropSound(-6)`
基类实现 `Item.gd:3171-3173` 抽 `Util.rng_trace_range(0.9,1.1)` 1 位；
但狼崽三家**覆写 playDropSound 且纯无抽**（`oracle/Items/Exclusive/PowerPuppy.gd:10-12`、
`CouragePuppy.gd:8-10`、`WisdomPuppy.gd:8-10`；Armored 变体经 extends 继承该覆写）→ oracle 每次狼崽激活 **0 抽**。
gd_core 侧 `CoreItem.gd:975`（activate 内）对**所有物品无条件**补 1 抽 `ctx.rng.randf_range(0.9,1.1)`，
`:3674-3677`（activateFromEvent，他泳道在途新增）同模式；hooks 恒 pass（`gd_core_py/gd_core/CoreHooks.py:54`），
行为体的 playDropSound 在 gd 全链**从不被派发** → **每次狼崽激活 gd 多耗 1 位 rng，流整体后移一位**。

### 证据链
- 签名：两场均「玩家 APP 首抽同值（run805 idx94 双 T101；run879 idx43 双 T106），对手 APP 首抽
  oracle=1(恢复T102) vs py=0(幸运T101)」（run805 idx100、run879 idx45），两抽之间**零事件零其他可见消耗**——
  同种同源流同调用必同值，故必有隐形消耗差 1 位。
- 方向核对：gd 多耗 1 位（py 流领先），与「下一抽取值翻转、其后全流洗牌」一致（run879 之后事件数 629 vs 594 级联发散）。
- **隔离实证（反例组）**：playDropSound 覆写面 20+ 物品逐一读覆写体——Rat.gd:31-34/Toad.gd:59-61/
  Wisp.gd:64-66 等 14 家覆写体**自带** pitch/`Util.randPitch` 抽（=基类 1 抽，gd 无条件补偿对它们恰好正确；
  故 run1172_r18 含 Rat 多次激活仍逐项对齐至 16.1s）；**纯无抽者唯狼崽三家**。该 bug 的受害面=一切含
  狼崽激活的战斗，红场集合与狼崽出现面重合。

### 修法建议（内核泳道，两处同改，CoreItem.gd）
```gdscript
if _hasBehaviorMethod("playDropSound"):
    _behavior_call("playDropSound", [-6])   # 覆写体自带抽况（Rat 1 抽 / 狼崽 0 抽），镜像虚派发
else:
    ctx.rng.randf_range(0.9, 1.1)           # 基类音高
```
预期收割：run805_r18/run879_r11 及一切含狼崽激活场。
不采方案：在 ArmoredPowerPuppy.gd 内复刻基类 activate 跳过补偿——内核逻辑复制进物品脚本，
与内核侧修复互相冲突（他泳道工作区正有 activateFromEvent 新增补偿的未提交 diff），否决。

## 2. K06 GirlPower 充能（run608_r18 idx147 / run613_r18 idx85 / run729_r14 idx30）——数据面漂移

### 现象
oracle 首 proc（T106 充能+2）3.483s/2.867s/2.217s，py 4.200s/4.050s/2.500s——**时刻差**为主，
部分场叠 flip 取值差（run613 类型同、时刻不同；run608/729 时刻类型均异）。

### 根因（计数差，非脚本差）
- GirlPower cd=7.0、speed=35/100（两侧 battle_items.json / CSV 同值）；`doCooldownEffect` 的
  empower/regen=2 两侧同（层数面无差，首 proc 双方均 emp=regen=0 走 flip）。
- 速率差 Δ=0.35×k（run608/729 k=1、run613 k=2）＝恰好整数个 speed_v → 影响格内**distinct 职业物计数差**。
- 引擎装配探针（C5TRIO_probe.py，只装配不 run）实测：py N=2（run608：Toad + Staff of Unhealing，
  speedScale=0.7，onPrepare 已生效）。
- oracle 反推：N=2 时最早可能首 proc=7×0.95/1.7×60≈235 tick＞观测 209 tick → N_o≥3；由双 proc 时刻
  区间解得 N_o=3/6/4（run608/729/613），Δ=1/1/2 与速率差全吻合。
- 排除清单：脚本同构；几何同源（GirlPower.tscn tile_data ↔ json affected_cells 15 格逐格一致；
  C5TRIO_geom.py 第一版坐标系想当然得出「10 key 命中」是**错的**，引擎真值只有 2 件，已弃）；
  `_DESCR_CACHE` 共享单例疑点排除（oracle ItemBook.items[itemName] 同样每 key 单例，去重语义两侧等价）；
  回扫链排除（oracle Item.gd:1348-1352 addToInventory 回扫 ↔ gd_core/CoreItem.gd:596-599 同构，
  CoreGrid.addItem:201-208 广播同构，实测缓存 {Toad,SoU} 与 json classes 判定完全一致）；
  adjustCooldown 抽（Item.gd:3792-3799 ↔ CoreItem.gd:474-486）同构且无法解释 Δ=k×0.35 的整数结构。

### 收敛
剩余自由度＝**哪些物品算职业物**：oracle 真规则=CSV shop 列（ItemBook.gd:893-945：''→Neutral(127)、
'no'→None(0)、'Class'→1<<classI）；repo 两份 CSV（oracle/Sheets/CSV/ItemData.csv 与
decompiled_full/.../ItemData_e.csv）shop 列一致，且按此规则 py 现值自洽——但语料反推 oracle 计了
**更多**职业物 → 语料游戏的数据 vintage ≠ repo 两份 CSV。属 K01「语料 vs oracle 树漂移」家族。

### 建议（数据泳道）
工作区未提交的 classes 批改（SoU 0→2、Chili Goobert 0→8、Badger Rune 0→4、KingCrown/Frostbite 0→127）
按 repo CSV shop='no' 应为 None(0)，现值疑**反向多计**（py 会多抽计数）——请对照语料反推的 N_o
（run608=3、run729=6、run613=4，可用本目录 C5TRIO_probe.py 复测 N_py）逐 vintage 校准；注意
KingCrown 0↔127 两侧同为「非职业」，此类翻转无行为影响，白改。

## 3. K20 Crown 治疗（run1172_r18 idx1168 / run1176_r11 idx89）——治疗面零错证

### 结论
**治疗面（doCooldownEffect: cleanseBlind(1); heal(); activate()）完全干净**：
- run1172：全场 93 个 Crown 事件逐项对齐至 16.1s，heal 金额 8=8；
- run1176：heal 5=5 全对齐。
首分歧均在他面：
- run1172 idx1168＝**域 C**（CoreBuff 到期批相位）：Carrot Goobert 充能-2 超时批 py 于 16.167 弹出、
  oracle 16.183，恰插在 Crown heal(16.167) 之前/后互换次序——与 C4QUAD 节「py 比语料早 1 tick 弹整批」
  同病，属 K01/K03 挂起研究域（r35_cards 明令无突破勿硬修）。
- run1176 idx89＝**域 A**（PotM 疲惫提前）：py t=5.033 发 T19 amount=109（Power of the Moon 疲惫），
  oracle 疲惫在 17.017s——与 C4QUAD 节 5.033 定谳逐位吻合；已核实 run1176 阵容两侧均含 Power of the Moon。

### 建议
随 K01 域 A（CoreCombat/PotM advanceTime 取舍）与域 C（CoreBuff 四分支计时器批相位）突破自动转绿；
Crown.gd 治疗面与净化面本轮均无需动（净化面归 CORE 泳道 K04，未触碰）。

## 4. 纪律自检

- 卡面 6 文件零修改（本会话仅写 wf_notes 5 个取证脚本 + 台账追加一节）；
- GDScript 零 print 桩；oracle/ 与 output/oracle/fights/ 只读；未跑 Godot、未跑 verify_oracle.py
  （仅 import 其 canonical_stream/_tuple_of 纯函数，C4QUAD 先例）；引擎装配探针未 eng.run()；
- python 只读对拍共 5 脚本，全部落盘本目录可复跑。
