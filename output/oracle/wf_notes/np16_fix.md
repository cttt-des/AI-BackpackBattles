# np16_fix · 重出后 10 红场清尾轮（全定谳轮，2026-10-22）

## 结论（先答）

**本卡零产线改动**（gd_core/、gd_core_items/、gd_core_py/ 未动一字，无备份需求）。反馈红名单
10 场（986 已绿）全部定谳，三类归簇：

1. **run948_r18 根因闭环（本轮主发现）**：crafted 戒指（MagicRing 族）「效果真值注入时序」
   差。gd 宿主 place_one 在 addItem **之前**调 setCraftedEffects
   （gd_core_test/OracleAlignBattle.gd:291-292，addItem 在 :293）；oracle 元组循环是
   addItem→宝石→**之后**才 setData（oracle/Core/Inventory.gd:1001-1035
   createFromItemTuples）。后果链：oracle 放置广播瞬间 ringTypes=随机效果类型
   （_ready→randEffects 真抽，MagicRing.gd:167-176），CA 的授予判定按随机类型做出且
   此后不补授；gd 广播时已是真值类型 → CA 直接授予。单点组成差=SR(5,3)（合成圣环）：
   gd 双侧 dyn=[25]（Dark=6/6），oracle 仅 O 侧 dyn=[25]（P=5/O=6）→ 0.6 平衡悬崖 →
   攻 1 proc 分叉（np15_cont §10 的「为何 P 侧不授」至此闭合）。
   **修复=宿主单笔一行**（setCraftedEffects 块挪到 addItem+setGem 之后，镜像原版元组
   序），零 rng 消耗、链位中性；不在本卡允许面 → 留档待主控裁决。
2. **R 簇 5 场（906/1125/1371/1409/696）= 暖场残留攻击闩，本轮在现行树+现行语料下逐抽重锚**：
   oracle（语料/probe 同语义）在玩家首次武器攻跳过本体 5 抽，gd 跑满 → 首攻事件 ±1 伤害。
   修复面 = gd 腿宿主复刻「暖场+正式场单进程」语义（gd_core_test/，超面）或语料录制端
   修暖场复位（oracle/oracle_fight.gd，只读超面）。gd 内核无判据单笔（无条件闩=打破
   900 绿场，np14_fix §1 红线维持）。
3. **隐形吸收族 4 场（989@1709 / 1444@330 / 702@423 / 1022@1386）形态自看=与 np15_fix/
   np15_cont 留档逐位一致**，无新证据，剔除维持；闭案唯一路径仍为 oracle 侧
   tos-dump 桩（oracle/ 只读，超权限）。

run986_r12 一致 ev=4023（np15_cont_r3 窗口 gate 保留实锤）。gd_core_py 镜像已同步
（_timer_e0/_timer_e1 + 窗口 gate 于 gd_core_py/gd_core/CoreBuff.py:53-54/376-382 实读
确认），后续无需再提请。

## 1. 红名单终局表

| 场 | 首差 ev/行首 | 族 | 终局 |
|---|---|---|---|
| run948_r18 | 42/22 | crafted 戒指装配时序（宿主面） | 剔除留档 + 宿主单笔待主控 |
| run906_r18 | 6/2 | 暖场闩（@258 跳本体 5 抽） | 剔除留档（宿主/录制端） |
| run1125_r18 | 49/29 | 同闩（@370；np14 双退面为其次级签名） | 同上 |
| run1371_r18 | 51/19 | 同闩（掷链全同 + 「9 不可达」论证，§3.4） | 同上 |
| run1409_r18 | 25/17 | 同闩（@373） | 同上 |
| run696_r18 | 46/22 | 同闩（@395） | 同上 |
| run989_r18 | 1709/1210 | 隐形内部批账（np15_fix §8.2） | 剔除维持 |
| run1444_r18 | 330/215 | 双稳样本（np15_fix §2） | 剔除维持 |
| run702_r18 | 423/166 | 同刻批拆（np15_fix §7.3） | 剔除维持 |
| run1022_r18 | 1386/893 | 隐形盲批（np12_L1 §3） | 剔除维持 |
| run986_r12 | 一致 ev=4023 | — | 已绿 ✅ |

对拍复现：`python -X utf8 tools/_probe_gd_compare.py output/oracle/align/np16v_after-rr`
本轮实跑，10 场分歧位与反馈逐位一致、986 一致。

## 2. run948_r18 —— 证据链（全部本轮实读/实跑）

1. **gd 侧 ids 桩实弹**（np16v_after-rr/run948_r18/rng_trace.txt:291/:402，P/O 双剑）：
   `aff 25=6`（Dark=6），ids=`[Shiny Mantle[dyn25], Superior Ring[dyn25], False Life,
   Lucky Cat, AoL[dyn25], AoL[dyn25], Superior Ring[dyn=[]], AoL]` 双侧全同。
2. **oracle 基线**（probe/np15_cont_r2/asm948b.txt:103/:112）：P 剑 Dark=**5**、O 剑=**6**；
   affIds0 与 gd 逐名对位，唯一差 = 第 2 位 SR(5,3)：P 侧 `d=False dyn=[]`、O 侧
   `d=True dyn=[25]`；gd 双侧均 `d=True dyn=[25]`。
3. **几何与装配序**（gd_core_test/oracle_align_cases.json run948_r18 夹具 +
   语料 lineups.json，双方板面镜像全同）：CA@(4,1)（占 3×2），受影响 10 格
   [(3,1),(3,2),(4,0),(4,3),(5,0),(5,3),(6,0),(6,3),(7,1),(7,2)]——含 (5,3)、不含
   (4,5)；装配序（lineups items 数组即放置序）CA=idx28 **先于** SR(5,3)=idx30；
   SR(4,5)=idx43（合成暗：effects 109=Blind→Dark，ringTypes 真值面，非 dyn）；三 SR
   均无宝石，CA 自带双 Corrupted Crystal。CA 的 currentAffectedItems 终态含 SR(5,3)
   （curAff0 唯一 SR），两侧树一致；差的只是 dyn 授予。
4. **机制**（oracle 侧逐字读）：
   - `oracle/Items/Exclusive/MagicRing.gd`：`_ready`→`randEffects()`（:167-176，非
     ItemLibrary 且非 wasJustCrafted 时真抽 2×numEffects）；`sortEffects()`（:115-144）
     由 effects 推 ringTypes（stackToTypes :17-28：102 Regeneration→Holy、109 Blind→
     Dark…）并广播 `inventory.onItemTypeChanged(self)`；`hasType = ringTypes ∨ 基类`
     （:149-151）；序列化含 `getDataPersistent`（:283）⇒ 元组带 "pd" ⇒
     createFromItemTuples 走 `setData(pd)` 还原真效果（:265-278）。
   - `oracle/Core/Inventory.gd:1001-1035`：元组循环顺序 = 实例化/add_child（→_ready→
     **随机 ringTypes**）→ addItemByTopLeft（→item_added 广播→CA 按**随机类型**判）→
     宝石 → setData（→真 ringTypes→onItemTypeChanged 广播→CA 对**已窗内**者只走
     Item.gd:1477-1500 的保留性复检，不再授予）。
   - `oracle/Items/Item.gd:1428-1474`：onItemAdded=「未窗内 ∧ isItemAffected→加窗+
     onAffectedItemAdded」；CA（oracle/Items/CorruptedArmor.gd ≡
     gd_core_items/CorruptedArmor.gd，逐字 diff 仅命名差）onAffectedItemAdded 授予
     `holy ∧ ¬dark` ⇒ SR(5,3) 放置瞬间按随机类型判：进窗（canAffect 真）但不授
     （随机类型非 holy∧¬dark）；O 侧因链位不同随机抽不同，恰好满足授予——
     「oracle 自身双侧不对称」一次解释。
   - gd 宿主 `place_one`（gd_core_test/OracleAlignBattle.gd:259-301）把
     setCraftedEffects 放在 addItem 前（:291-293）⇒ 广播时 ringTypes 已真值 ⇒
     `holy ∧ ¬dark` 成立 ⇒ 授予。gd_core_items/Exclusive/MagicRing.gd 与 oracle 逐字
     同构（sortEffects :110-133 / hasType :141-143 / setCraftedEffects :185-193 注释
     自证「宿主在 _readyInit 之后调本方法」——时序面偏差在宿主）。
5. **修复单笔（超面，供主控）**：gd_core_test/OracleAlignBattle.gd place_one，
   将 :291-292（`if entry.get("effects") != null and it.has_method("setCraftedEffects"):
   it.setCraftedEffects(entry["effects"])`）移至 :300 宝石循环之后（镜像原版元组序
   addItem→宝石→setData）。setCraftedEffects 零 rng，链位中性；预期 gd P 剑 Dark
   6→5、@42 proc 分叉消失。风险闸=REG 九场+全量电池（所有含 crafted MagicRing 的场
   装配终态都可能变，语料=oracle 语义 ⇒ 严格更贴语料，但必须以 REG 实证）。

## 3. R 簇 5 场 —— 暖场闩逐抽重锚（本轮实跑）

仪器：oracle=probe/np14_fix/<case>/rng_log.txt（现行语料单场回放，probe≡语料已由
np14_fix §1 实证），gd=align/np16v_after-rr/<case>/rng_trace.txt（现行树 10-22 腿）。
对位法：数值链逐位 + 平移再对齐（「链不移位、仅值域差」的 randInBox(±30,30) vs
randf_range(±10,10) 视觉偶对按构造排除，与 np15_fix §7.3 run702 同款）。

1. **run906@258 / run1125@370 / run1409@373 / run696@395**：oracle 在 (100,160) 后
   **直取 randf×2+伤害掷**（跳本体 5 抽 (0.9,1.1)×2+pick(0,2)+(0.8,1.2)+pick(0,N)），
   gd 跑满 5 抽 ⇒ 伤害掷错位（906：O randi_range(15,16)=>16 vs G =>15 → 伤 12v11=ev6；
   1125：O (16,17)=>16 vs G =>17；1409：O (17,18)=>17；696：O (5,10)=>8）。与
   np14_fix §1 的 attackMovingForward 暖场残留闩形状逐位吻合（现行树+现行语料复现，
   非 np13 时代快照）。
2. **run1371 特证（无需语料 rng 的闩实锤）**：双侧掷链至伤害掷**逐位全同**
   （randi_range(13,18) 前四发 16/18/15/15 完全一致），gd roll=16 → 事件伤 8
   （=round(16×0.5)，EvilCap+LeatherHelm 各 +25% resi，CoreCharacter.gd:703-705 与
   oracle/Core/Character.gd:563-565 公式逐字同构）；语料事件=伤 **9**。16×0.5=8 精确，
   ⇒ 语料该掷必非 16 ⇒ 语料链在首武器攻处与 gd **必不等** ⇒ 语料带闩语义实锤
   （闩后掷位后移，17/18×0.5=round 9 吻合）。probe 的 np14 腿（无闩）=8=gd，与此
   自洽（np14_fix §1 证据 5「1371 probe 反叉」由本论证吸收）。
3. **修复面（超面）**：(a) gd 腿宿主（OracleAlignBattle.gd）复刻「暖场+正式场」单进程
   语义——暖场超时截断不复位 attackMovingForward/EventBus，正式场继承；与语料定义
   「语料=现行树单进程语义」严格一致。(b) 或语料录制端（oracle_fight.gd，只读）在
   暖场与正式场之间补复位边界，使语料=净单场语义。(a)(b) 二选一后本簇 5 场预期
   全转绿或全转红-可复现；gd 内核面无可落单笔。
4. 「工件论已消解」正读：语料定义含暖场链 ⇒ 闩是语料语义的**组成部分**而非缺陷；
   reRecord（同管线带暖场）确定性复现同残留 ⇒ 本簇**不进 reRecord**。

## 4. 隐形吸收族 4 场 —— 形态自看结果（剔除维持）

本轮 `_probe_gd_compare.py` 实跑首差形态与 np15 留档逐位一致，无新证据：

- run989@1709：gd 多 `LG tgt1 -1 TO @16.4833`（批 16.466667×1 残量）——np15_fix §8.2
  隐形内部劈分。
- run1444@330：gd 多 `Frostbolt Cold TO -2 @5.9833`（e[1]==3==dur，纯模型必弹，
  语料无）——np15_fix §2 双稳族。
- run702@423：`LG Blind TO -7`（语料）v `-6`（gd）同刻批拆——np15_fix §7.3。
- run1022@1386：语料多 `Banner Blind TO -1 @13.0333`（gd 缺）——np12_L1 §3 隐形
  永久栈/批读数。
- 闭案唯一路径仍为 oracle 侧 tos/REARM dump 桩（oracle/ 只读，超本卡权限）；gd 侧
  任何单笔无判据支撑（盲修）。

## 5. 纪律与仪器

- **零产线改动**：gd_core/、gd_core_items/、gd_core_py/、assets/ 未动；未 commit/push；
  REG 九场与 gd 验证腿未跑（红线，脚本统一跑）；判据未放宽。
- 语料 output/oracle/fights/ 与 oracle/ 树只读未触（本轮零 oracle 探针新跑，全部复用
  现存 probe/np14_fix、probe/np15_cont_r2 产物与现行腿 align/np16v_after-rr）。
- 本轮落盘仅本笔记（output/oracle/wf_notes/np16_fix.md）。分析工具：tools/
  _probe_gd_compare.py（只读）+ 会话内逐抽对位脚本（只读，模式同 probe/np14_fix/
  _cmp_draws.py 加平移再对齐）。
- 下轮建议（供主控裁决）：① 落 §2.5 宿主单笔（948）+ §3.3 (a) 腿宿主暖场复刻
  （R 簇），或 §3.3 (b) 录制端复位；② 三笔均需 REG+全量电池闸。
