# A3BLD 泳道笔记 —— K01/K03 盲族 ×40（取证轮，结论=blocked）

日期：2026-10-17。卡面文件面：gd_core/CoreBuff.gd + gd_core_py/gd_core/CoreBuff.py（本轮零改码）。
验证场：run619_r18, run622_r15（另取 run665_r14 作纯化对照，未用 run727——台账既定漂移场）。

## 1. 数据面与口径

- corpus 冻结事件：`output/oracle/fights/<场>/events.json`（只读）。T109=EventType.Blind=109
  （gd_core/CoreConst.gd:59）。事件三形态：
  - 正额+`duration` = 施加（临时批，amount=施加事件额，已含抗性/反射后净额）；
  - 负额+`timeout:true` = 到期弹批（`timeout` 是 bool 参数，非绝对时刻，
    gd_core/CoreCombatLog.gd:162-166 createEvent_StackTimeout）；
  - 负额无 timeout = 净化（Crown/Shelly/Unstable Recombobulator 等）。
  - 本三场无 used=true 消耗事件、无 resisted/protected 事件（corpus 导出即如此）。
- 到期量现状（gd）：changeCurrentLogShowLabel 的 `min(current, 批余)`
  （gd_core/CoreBuff.gd:387-390），批变异=净化走最远批（CoreBuff.gd:346-382）。
- alignment.json perCase：卡内 40 场（K01 33 + K03 7）当前 match 全部=「oracle≠gdcore」，
  无 skip 情形。

## 2. 规则枚举（全部证伪为「全拟合」候选）

对三场 6 个 (fight,target) 账面、共 685 个到期弹：

| 候选语义 | 拟合 |
|---|---|
| 净化变异×选批（farthest/nearest/oldest/youngest/none）× 量值（批余 / min(current,批余)） | 最好=farthest+rem 632/685（91%），其余 ≤606 |
| 按净化源物品（Crown/Shelly/Recomb）分派变异方向（4³ 组合） | 最好仍=三者全 farthest 632/685 |
| 指针模型（nTT 悬空 keep/dec、OOB earliest/last、resched gd/always/never，以 corpus 弹为钟） | 623/685 |
| 完整引擎模拟（Godot Timer 帧量化开火+递归弹链+静默零弹+最远批净化+Util.time 偏移 δ） | 623/685（δ 不敏感） |

脚本（只读分析，未触碰 oracle/）：`output/_round_patches/wf_a3bld/`：
analyze_blind.py / fit_rules.py / source_rule.py / consistency.py / pop_table.py /
batch_features.py / pointer_model.py / engine_sim.py / engine_sim2.py。

### 分账户残差结构（引擎模拟 vs corpus，按序对拍 item+amount）

- run622_r15 tgt0：**60/60 全拟合**（最远批净化+指针弹批+静默零弹，完整引擎）。
- run622_r15 tgt1：54/56（残差=同 ts 孪生级联内弹序互换，吸收总量一致）。
- run619_r18 tgt1：235/242（同上，残差同为级联弹序互换）。
- run619_r18 tgt0：219/237，但 **18 个分歧中 12 个集中在 14.6167s 之前**：
  前 15 弹 corpus 全部=原始额 7（净化完全不突变批次），恰在净化事件 2190（t=14.6167，
  Crown o1 -1）之后突变为「最远批变异」语义，此后与引擎一致（2272 弹 -3=吸收恰为
  2190+2193+2232 共 4 层）。晚段 6 分歧仍是孪生级联弹序互换。
- run665_r14 tgt0：**53/53 全程零突变**（none 规则完美；对照：同场 tgt1 有突变）。
  已按施加额 FIFO 消耗复核 53/53。
- run665_r14 tgt1：33/37。

## 3. 最小反例（同一战、同构局面、相反行为——静态规则不可拟合）

run619_r18（镜像阵容，双方各有 Light Goobert×1 + Crown×2）：

- tgt1（对手侧）：唯一盲批 L1=7@2.5833（事件 86），净化 -2@3.4（141）+ -1@3.5（164）
  全落批上 → corpus 到期 -4@5.6（317）= 7−3，**突变发生**。
- tgt0（玩家侧）：唯一盲批 A=7@2.5333（事件 73），净化 -1@3.5167（167）+ -1@3.6833（176）
  → corpus 到期 -7@5.5667（307）= 原始额，**突变未发生**。

两侧批结构、批数（1）、净化源（己方 Crown）、施加源（敌方 LG）、时刻几何（净化均在
批存活的第 1 秒）全部同构，任何 Buff 层静态规则（分配方向×量值公式）对两侧只能给出
同一行为。gd 现行语义在 307 位给 -5（最远批变异+min(current,批余)，与 corpus -7 相差
即台账 r34 C01 的首分歧）。

再叠加跨场矛盾：run622_r15 tgt0 的同类「唯一批+净化」**发生了**恰好 1 层突变
（8→7，事件 260），run665_r14 tgt0 则全程零突变。即 corpus 时代语义不仅非静态，
还随场/随侧**时变开关**，事件流内不存在可解析的状态变量（无保护类事件、无 used
事件、RNG 流在首分歧前与 gd 逐位一致——r34 C01 已证——排除 rng 驱动的选批）。

## 4. 已核查的旁支假设（全部排除）

- 净化源异构：Crown=cleanseBlind（gd_core_items/Crown.gd:40-43）、
  Shelly/Recomb=cleanseRandomDebuffs（两脚本 :10/:35）——三者最终都进 Buff.loseStacks
  （gd_core/CoreItem.gd:2380-2388、2456-2464），物品层无分异。
- buffProtectStacks/cleanseProtection 池：run619 阵容无授予物品
  （grep gd_core_items 仅 BurningBanner/KingCrown/KingGoobert/LightFlower/ShepherdsCrook）；
  且 corpus 净化事件额已是实落额，池吸收需以「事件额=池前额」为前提，与 run665_r14
  tgt1 早期突变、后期不突变矛盾。
- current 快照说/原始额说/min(current,原始)说：tgt0 idx307 处 current=10>7、
  tgt1 idx317 处 7−3=4≠快照 11、≠原始 7，逐一否。
- current==Σ批不变量在 corpus 不成立（净化后 current 低于存活批总额），由
  「静默零弹」（change=0 不出事件但弹批）+弹批 min 截断共同解释——引擎模拟已复现该解耦。

## 5. 结论与解锁条件

corpus 时代（10-06/07 生成）的 Buff 批变异/超时内部账与现行树（=反编译现行游戏
decompiled_full/Core/Buff.gd，199-260 行 loseStacks=最远批）不同，且差异是
**有状态的时变行为**（同战双侧异、中途开闸），事件流反推不出规则。现行树取证路线
r34 C01 已判死（b1_c1 bak=现行；git 对 oracle/ 无历史；decompiled=Sep17 版≠corpus 时代）。

本轮维持挂起，未改码（CoreBuff.gd/py 保持 2e053483 基线语义）。解锁三选一：
1. 找回 corpus 时代 oracle 树 Buff.gd（现存备份均=现行，需新的考古来源）；
2. 用 corpus 同版本构建重放（Godot，需走共享验证员通道另行立项）；
3. 管线级方案：K01/K03 40 场改走「oracle 事件重放」而非 gd 模拟对齐（超出本卡文件面，
   需工作流层决策）。
