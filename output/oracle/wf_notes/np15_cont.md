# np15_cont · 续修轮1（状态核验 + run948 深挖定谳 + reRecord 申请，2026-10-21）

## 结论（先答）

**本轮零产线改动**（gd_core/gd_core_items 未动一个字节，无备份需求）。核心工作三件：

1. **状态核验（亲跑比对，非转抄）**：现行树 = np15_fix1+2+3 三笔（gd_core/CoreBuff.gd
   `_timer_e1`/`_timer_e0` 影子 + gd_core_items/Exclusive/Sandbag.gd 非 multi，:47 实读确认）。
   用归一化键（type/timestamp/origin/params/parent/target，GemSocket\d*→GemSocket，忽略
   type_name 命名差）对拍语料（output/oracle/fights，10-21 10:32 批）vs np15v_fix_r2 腿
   （output/oracle/align/np15v_fix_r2，18:33，REG 九场同刻 reg2 全 PASS）：
   **run1132_r18 全同 2121 ✅、run602_r14 全同 11438 ✅**（np15_fix1/fix2 修复在本轮亲测复现）；
   run989@1709 / run702@423 / run948@42 / run844@83 / run1444@330 / run1022@1386 首差位与
   np15_fix.md §7/§8 留档逐一吻合（卡面红名单与 18:33 腿的差异 = 1132/602 两场实际已绿，
   红名单系 np13v/np14 时代快照未刷新）。
2. **run948_r18 深挖定谳（本轮主分析，新证据链）**：首分歧 = 玩家 Prismatic Sword
   `onPreDealDamage_early` 随攻 proc 的「触发与否 + chance 判定」在两侧随攻击序数**反向漂移**
   （详见 §2）。根因面 = gd 侧受影响集（affectedTypes 输入）/prepare 生命周期与 oracle 不同，
   钉死需 gd 侧装配仪器现跑（本卡禁 gd 腿/现跑）→ **剔除留档，不硬修**。run844_r11 同族
   （np14_fix §3 / np15_fix §4 维持）→ 同批剔除。
3. **reRecord 申请 6 场**：run906_r18 / run1125_r18 / run1371_r18 / run1409_r18 / run696_r18
   （np14_fix §1 R 簇：timeout 残留录制，无 determinism 边界）+ run1444_r18（np15_fix §2 双稳
   样本）。理由与预期见 §5。

## 1. 状态核验（本轮实跑）

- 比对脚本（会话内 python -X utf8）：语料 events.json vs align/np15v_fix_r2/*/events.json，
  键归一化后逐位对拍。结果：
  | 场 | 结果 |
  |---|---|
  | run1132_r18 | 全同 2121 ✅ |
  | run602_r14 | 全同 11438 ✅ |
  | run989_r18 | 首差 1709（C=19202 G=20035）|
  | run702_r18 | 首差 423（C=3714 G=4541）|
  | run948_r18 | 首差 42（C=2677 G=2742）|
  | run844_r11 | 首差 83（C=6764 G=3986）|
  | run1444_r18 | 首差 330（C=1030 G=1002）|
  | run1022_r18 | 首差 1386（C=3915 G=3910）|
- R 簇 5 场（906/1125/1371/1409/696）：fix_r2 定向腿未覆盖（仅 8 场定向），最近 gd 对照 =
  np14v_confirm（13:11，fix1/2/3 之前）13/13 红。fix1/2/3 只触 CoreBuff._timer_e1/_timer_e0
  判据与 Sandbag BuffTimer multi 位，不达 attackMovingForward/EventBus 连接面 → 预期仍红，
  待脚本腿在现行树下复核（本卡未跑）。
- 语料 mtime 抽查：run1132=10-21 09:57、run602=10:14、run906=10:24、run989=10:32 —— 18:33
  腿与语料同代，对拍有效。

## 2. run948_r18 —— 随攻 proc 族深挖定谳（剔除）

### 2.1 证据链（全部本轮实跑/实读）

- **逐抽对位**（oracle=probe/np14_fix/run948_r18/rng_log.txt vs gd=align/np15v_fix_r2/
  run948_r18/rng_trace.txt，会话内逐行读）：
  - 攻1（玩家剑，combat t=1.5833 / U.time 84.317）：双侧至命中掷逐抽逐值全同
    （oracle #456-469 ≡ gd #855-870，含本体 5 抽 (0.9,1.1)×2+pick+(0.8,1.2)+pick——oracle
    攻1 本体照跑，np14_fix §3「激活闩」前提不成立的复核一致）。分歧：oracle #470 直取伤害掷
    randi_range(17,23)=>21；gd #871-874 插入 pickRandomElement(0,2)×4
    （=inflictRandomDebuffs(4)，debuffs=4.0，assets/battle_items.json Prismatic Sword
    named_params）再走后续。**两侧命中掷与 picks 之间均无 chance-flip 抽**。
  - 攻2（对手剑，t=1.6167 / 84.367）：双侧链逐值全同（gd #945-962 == oracle #538-555，
    np15_fix §4 复核一致），**同样无前置 flip**。
  - 攻3（玩家剑，t=3.1833/3.2）：oracle #685 flip 抽 randf 0 0=>0.366269 后 4 连 pick
    （proc 成功）；gd #1285-1286 命中掷后直取伤害掷 randi_range(19,25)=>19，**无 flip 无
    pick，但 gd 事件伤害=22 = 19+3（圣构加成在加）**（events t=3.2 type=1 damage=22 vs
    roll 19；oracle 同刻 roll 23 event 22）。
- **事件面**（corpus vs gd fix_r2 events.json）：oracle 攻1 事件 idx42-45 = mana+5 →
  False Life+1 → **damage 21 = 原始掷 21（无圣构加成）**；gd 攻1 = 108/110/109 三笔 debuff
  （inflictRandomDebuffs 产物）→ mana+4 → damage 17。oracle 攻1 无任何 108/109/110 事件。
- **归属件钉死（oracle 自带仪器，ORACLE_PROC_DEBUG=1，本轮实跑探针
  probe/np15_cont/run948_irdb.log）**：oracle 全场 inflictRandomDebuffs 107 次全部
  `[IRDb] item=Prismatic Sword`（[GStk] 伴随即 108/109/110 giveStacks）；oracle 首次 IRDb
  对应 rng_log 首个 pick 四连 @84.367（攻2）——**oracle 攻1 无调用实锤**。
- **装配面 dump（本轮新仪器 probe/np15_cont/probe_np15.gd，基于 np12_L2 probe_np12.gd
  模板，SceneTree 装配回放，产物 asm948.txt）**：post-prepareItems 后
  - 玩家剑 affTypes：Dark(25)=**5**、Holy(22)=7、Magic(23)=1、Vampiric(24)=1；
    chance2=10、bonusChance_mult=15（Amulet of Fortune affItems0=[Prismatic Sword,
    Amulet of Light] add_bonus_chance(15)）、add1=0 → chance=(10×5)×1.15=**57.5%**；
  - 对手剑 affTypes Dark=**6** → 69%；
  - Corrupted Armor curAff0=[Shelly, Shiny Mantle, Superior Ring, Amulet of Light,
    Amulet of Light]（动态 Dark 施与面）；剑受影响格 8 格
    [(7,4),(6,3),(6,5),(5,3),(5,5),(4,3),(4,5),(3,4)]，格内 dark 候选（lineups+动态面复算）
    至多 7 件。

### 2.2 定谳

- 判定闸（oracle/Utility/BalancedRandom.gd roll 与 gd_core/CoreRng.gd:292-322 逐字同构）：
  `target<=0 → false 零抽；target>=1 → true 零抽；否则 flip 必抽`。chance=(10×Dark)×1.15。
- oracle：攻1 **无 flip 无 proc 无圣构加成（damage 21=裸掷）** ⇒ onPreDealDamage_early 在攻1
  整体未生效（Dark=0 或触发未连接）；攻3 flip 0.366269 命中 ⇒ chance∈(36.6%,100%) ⇒
  Dark∈[4,8]。**Dark 随攻击序数从 0 漂到 [4,8]**。
- gd：攻1 零抽瞬弹 ⇒ target≥1 ⇒ Dark≥9；攻3 零抽零 proc 但圣构加成在（+3 ⇒ Holy≈9-10）
  ⇒ target≤0 ⇒ Dark=0。**Dark 随攻击序数从 ≥9 漂到 0，与 oracle 反向**。
- 而两侧 countTypes（oracle/Items/Item.gd:6529 ≡ gd_core/CoreItem.gd:3762，全 Type 键预置
  零）、getTypes（:3575 ≡ :1549，dynamicTypes.keys()+descriptor.types）、affectedTypes 写点
  （仅 onPrepare 一处）全部同构 ⇒ **静态代码面无差异可修**；差异只能在「onPrepare 执行时刻
  ×当时受影响集内容」的进程序（装配/激活期 currentAffectedItems 与动态 Dark 回流的时序），
  且两侧受影响集内容在攻击期与静态装配快照（Dark=5/6）都对不上。
- 钉死该族需 gd 侧装配/攻击期 affTypes dump 仪器现跑（CoreItem onPrepare 后 + 每次
  onPreDealDamage 前，仿 BSCHED 零抽桩）——gd 腿/现跑本卡禁跑 → **剔除**。认领建议：
  gd_core_probe 侧加 ASMTYPES 桩（affTypes/mult/add1/缓存清单，oracle_trace 开关）单场
  run948_r18 对位 oracle asm948.txt（本轮已产出静态基线）。

## 3. run844_r11 —— 同族维持剔除

np14_fix §3（首武器攻 1.117 面闩定谳被 np15_fix §4 推翻后）与 np15_fix §4 同批「随攻条件/
进程隐形态」。本轮补一个代际核验（亲跑）：现语料（10-21 10:22 重录批）== probe/np14_fix
单场回放 events **6764/6764 全同**（np12_L2 时代的幽灵物品失效语料已被替换）⇒ 844 现样本
忠实于现树单进程语义，分歧为 gd 侧真差。本轮未单独逐抽（预算计入 948）；按 §2 结论其归属
更新为「受影响集/prepare 生命周期族」候选，处置不变：**剔除**，待 §2 ASMTYPES 桩一并钉。

## 4. run1022 / run702 / run989 —— 隐形内部态族维持剔除（本轮增证）

- 本轮逐字比对 oracle/Core/Buff.gd:100-206 vs gd_core/CoreBuff.gd:171-330 gainTemporary：
  **入栈无条件（oracle :146-158 ≡ gd :255-267 permanent/temporary 分支）、事件门同位
  `if item:`（oracle :177 ≡ gd :300）、loseStacks 先永久后临时最远者拆（oracle :255-288 ≡
  gd 对应段）**——np12_L1 §3.3「null-item GAIN 永久栈」假说的 Buff 层在两侧结构性同构，
  差异（若成立）只能在调用点位/进程态，事件流不可见 ⇒ 无单笔可落。
- run989@1709 / run702@423 分歧位本轮在现行树复现（§1 表），np15_fix §7.3/§8.2 剔除判维持；
  oracle 侧 tos-dump 桩仍超本卡权限（oracle/ 只读）。

## 5. reRecord 申请（6 场）与预期

| 场 | 现状证据 | 重录预期 |
|---|---|---|
| run906_r18 | np14_fix §1：status=timeout，events=第 2 次执行，暖场超时残留（玩家开局闩+EventBus 双连）；probe≡corpus 证残留可复现 | 带 determinism 边界的已验证样本；语义仍为闩面（对 gd 预期仍红），但样本从「无验证残留」升格为「忠实可复现」，为后续 latch 语义裁决供数 |
| run1125_r18 | 同上（np14_fix §1 证据3：probe 亦双退 ⇒ 残留确定性复现）| 同上 |
| run1371_r18 | np14_fix §1 证据5：probe 与语料 ev51 即反叉 ⇒ 该场语料**非**现树单进程忠实样本 | 新样本有望贴合现树语义（np12_L1 §4 判级联，根差在首分歧）|
| run1409_r18 | np12_L2 §1：C-vs-P=25 而 **P≡G 全同** ⇒ 语料失效、现树两侧一致 | 重录大概率直接转绿 |
| run696_r18 | np14_fix §1 R 簇 timeout；np12_L3 §B.4 旧语料劈分差 | 同 R 簇处置 |
| run1444_r18 | np15_fix §2 三跑三形双稳实证（probe 1002/1030/1037）| 取新样本以闭「双稳分布抽样」歧义 |

**不申请**：run989/702/1022/948/844 —— 各自 probe≡corpus（样本忠实于现树单进程语义），
重录只会复现同分歧，浪费管线。

## 6. 仪器与纪律

- 本轮新增产物仅在 output/oracle/probe/np15_cont/：probe_np15.gd（装配面仪器，np12_L2 模板
  改装）、asm948.txt（post-prepare affTypes/mult/affCells 基线）、run948_irdb.log（ORACLE_
  PROC_DEBUG=1 探针 stdout）、probe_run.log。oracle 树零写入（仪器全部为 oracle 现存环境
  变量闸；ORACLE_FIGHTS_ROOT 输出重定向至 probe 目录）。
- **零产线改动**：gd_core/、gd_core_items/、assets/ 未动；未 commit/push；REG 九场与 gd 腿
  未跑（脚本统一跑）；判据未放宽。
- gd 侧诊断现跑（ASMTYPES 类）识别为下一轮首选取证手段，本轮因「gd 验证腿统一跑」红线未做。
