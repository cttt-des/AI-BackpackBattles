# K17 MF 狂热±1 ×2 取证笔记（修复手-C1MF，2026-10-17）

场：run977_r18（O 2v1 无效化）、run984_r18（O 3v4 获得）。结论：blocked，卡内零修改。

## 一、分歧形态（语料对拍实证）

命令：对 `output/oracle/fights/<场>/events.json` 与 `output/oracle/align/gdcore/<场>/events.json`
做 difflib.SequenceMatcher 全事件对拍（key=type/timestamp/origin.name/target/parent_id/params）。

- 两场首分歧同构：均为 MF 单次 `gainTemporary(Heat, 3)` 的 roll 段判定差，roll 次数两侧同
  （3 次，消耗同——首分歧后紧邻事件仍逐条 SAME，证明 rng 消耗账未断）。
- run977 idx227（t=4.4）：Evil Cap 15% resist 模式。
  O：resisted 事件 amount=2 + 获得 amount=1；G：resisted amount=1 + 获得 amount=2。
- run984 idx337（t=6.3）：无 resisted 事件，O 获得 3、G 获得 4。
  全场 G 呈 4/5 波动（G[367]=4、G[381]=5、G[387]=4、G[390]=4），O 恒 3；
  FFR 的 Lucky 亦现 G 5 v O 3（G[375] vs O[385]），与「放大面」一致。

## 二、机制链（代码对读）

- `gd_core_items/Exclusive/MissFortune.gd:6-13`：getLucky≥luckNeeded → useLucky →
  giveMostBuffs(numBuffs, event)。与 `oracle/Items/Exclusive/MissFortune.gd:7-13`
  逐字同构（仅 activationParticles 表现差）。
- `gd_core/CoreItem.gd:2663-2668` giveMostBuffs → getMostStacks(:2544) →
  pickRandomElement → giveStacks(:1317，`round(amount*buffPowers[type])`)。
  ↔ `oracle/Items/Item.gd:5573-5595` 同构。
- `gd_core/CoreBuff.gd:138-271` gainTemporary：totalResistChance = resistChancePercent
  − item.getAmplificationChancePercent(type)；>0 每层 roll 抵抗，<0 每层 roll 命中
  amount+=1（「±1」来源）；resisted>0 发 createEvent_StackResistOrNullify（amount=被抗数），
  余量发 createEvent_Stack（amount=实得）。↔ `oracle/Core/Buff.gd:76-200` 同构。
- rng 原语：`gd_core/CoreRng.gd:68-70,121-147`（roll/flipPercent/randf_range/randi_range/
  pickRandomElement，引擎直通）↔ `oracle/Utility/Util.gd:452-456,1087-1095` 同构。
- getChance/applyBonusChance（`gd_core/CoreItem.gd:1144-1156` ↔ `oracle/Items/Item.gd:3848-3858`）、
  getLucky/useLucky（`gd_core/CoreCharacter.gd:1668-1686` ↔ Character.gd 同位）、
  CoreConst.getBuffs（:217，range(Lucky..Heat) ↔ `oracle/Core/Game.gd:4934`）全同构。

## 三、数值面（两侧一致，排除）

来源：`oracle/Sheets/CSV/ItemData.csv` ↔ `assets/battle_items.json`。
MF：luck=1 / buffs=3（⇒ 进入 roll 的 amount=3，与语料 resisted+获得=3 吻合）；
Evil Cap chance=15；Paradise Birb chance=7（allBuffs amplification，每次激活叠加）。

- run977（无 PB）：c=15 恒定，resist 模式。
- run984：PB 激活 3 轮（2.216/3.9+4.0/5.366+5.466，两侧事件全同）后
  totalResistChance = 15 − 3×7 = −6（放大 6%）。

## 四、根因假设

判定差 + 消耗同 + 全链函数/数值同构 ⇒ 判定输入（totalResistChance 或 roll 值流）
在链外上游已**静默分叉**——首分歧前事件面逐条全同，分叉点不产生事件差。
run977 的 c=15 恒定且无第二写入源，故更可能为 **roll 值流静默错位**：
某处 gd 多抽/少抽/异原语抽取，波及此后的 flipPercent 判定。
同域案例：K09 miss 链单抽差（run610 #636）、K16 dir 抽差（run933 #234）。

## 五、反例与已排除面

- 「pickRandomElement 候选序差」：两侧 getBuffs 同为 range(101..107)，且分歧行两侧
  均选中 Heat（107 事件），排除。
- 「数值源差」：CSV↔battle_items.json 四关键物品数值一致，排除。
- 「buffPowers 差」：giveBuffPower 全部调用方只涉 Poison/Block/Vampirism，
  两场无此类物品，Heat 的 buffPowers 恒 1.0，排除。
- 「MAX_STACKS 截断」：截断只会使获得变小，无法解释 G>O（4>3），排除。
- 「早期判定同 ⇒ c 恒同」不成立：c 不同时早期 roll 值可恰好同判，
  不能据此断定 c 分叉时刻；此为解释空间收窄的约束而非证据。

## 六、建议（后续卡/工具侧）

1. 修复 run977 gd 侧 ORACLE_ALIGN_TRACE 落盘写空障碍（K17 前节已挂），
   恢复逐抽对位通道——这是定位静默错位点的唯一低成本路径。
2. 或由持 Godot 权限的会话在 oracle 侧跑 rng_trace 到 t=4.4（run977）/
   t=6.3（run984），dump 三个 roll 值与 c，一次即可判明「c 差」还是「值流错位」。
3. 若证为值流错位，归属「无事件面 rng 账」大卡（K09/K16 同盘收割），
   非本卡文件面；MissFortune.gd/.py 保持同构勿动。

## 七、脏残留检查

本卡零修改：`gd_core_items/Exclusive/MissFortune.gd` 与
`gd_core_py/gd_core_items/Exclusive/MissFortune.py` 未编辑（无 Edit/Write 调用），
无备份产出（output/_round_patches/wf_K17/ 未创建），无探针/trace 桩植入。
仅写盘本笔记与台账 `output/alignment_fix_log.md` 末节「r35 K17 续取证」。
