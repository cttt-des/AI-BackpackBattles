# A2SIG 泳道收尾分析（K02 锤链 + K09 miss 链；2026-10-17）

结局：**blocked（受阻）**——双假设均证伪，真根因已定谳并精确对位，但修复落点在卡面文件名单外（CoreItem 域），本泳道零改码收尾。完整证据链见台账「r35 K02/K09 定谳（A2SIG 泳道）」节。

## 一、工检基线

- alignment.json（output/oracle/alignment.json）三场现状：run683_r9、run610_r18、run1447_r18 均 `oracle≠gdcore`，首分歧 64/108/213。无 skip 面。
- 修复卡写「run683_r18」为笔误：alignment.json perCase、output/oracle/fights/run683_r9/、lineups 全部为 **r9**，全仓无 run683_r18。

## 二、根因假设（已证伪的两条）

### 假设① EventBus Delayed 日志模式 character_*_changed 信号 flush 分发差异（giveRandomBuffs→ManaOrb 充能授予面）

**证伪证据：**
1. 逐段对读 oracle/Utility/EventBus.gd ↔ gd_core/CoreEventBus.gd：queueSignal / flushLoggingQueue（先置 Instant 再 duplicate+clear 重放）/ emitAndLog 派发循环（含 fightEnded 即 return）1:1 同构，Delayed 机无行为差。
2. Delayed 窗只存在于 oracle Item.gd:5448-5694 九函数（giveRandomBuffs/useRandomBuffs/inflictRandomDebuffs/removeRandomBuffs/stealRandomBuff/cleanseRandomDebuffs/multiplyBuffsLimit/removeBuffsFraction/stealBuffsFraction）+ Bomb/Bazooka/DjinnLamp/GingerbreadMan 四物品；gd_core/CoreItem.gd 已镜像同批 set/flush（:2459/:2471/:2613…）。
3. **反例（决定性）**：run683 阵容 21 种物品（Leather Bag…Steel Dragon，两侧同构）经 battle_items.json behavior 全查 **0 调用**上述函数，四物品亦不在阵容（ManaOrb 同样不在）→ 该场 Delayed 窗零开启，假设面物理不存在。
4. EMPC 零触发差为下游噪声：gd 首个 T106/EMPC 在 t=4.25（trace_r35b 行 1254-1255），晚于 idx64（t=3.2）；且锤伤差异三点评（idx60 O9=G9、idx64 O9vG7、idx66 O9vG8）在「两侧 ×0.78 Stoned 减伤账 + roll 错位」下全部吻合，无需 empower/bonus ±2 假设。

### 假设② Character.takeDamage 受击动画/miss 标签路径多耗 (0.9,1.1) 单抽

**证伪证据：**
1. run610 gd trace（output/oracle/align/trace_r35e/run610_r18/rng_trace.txt）中 0.943325 恰为**第 636 抽**（纯抽行计数实测，与台账双指针 #636 精确对上）；其链位在 AWP(owner1) t=3.2833 激活序列（gd idx102 T100+20 块 → idx103 T0 激活 → BUS 行 → 本抽）之后，不在任何 takeDamage 内（无 CANMISS 标记邻接）。
2. takeDamage 的 playback 抽模型（gd_core/CoreCharacter.gd:746-747，Poison 闸 damage_anim_is_poison ↔ oracle Character.gd:616-625 的 current_animation!="Poison"）逐行同构；miss 分支两侧均零抽；本窗对拍无差。

## 三、真根因（两场同源，已定谳）

**激活音高幻抽**：oracle activate()→playActivationSound()→playDropSound(-6)（oracle Item.gd:4676-4678 → 基类 :3171-3173 抽 Util.rng_trace_range(0.9,1.1)）。20 个物品覆写 playDropSound，其中 **15 个无音高抽**（WisdomPuppy:8-10 直放 Sound.playSound(pickupSound, volume-8)；BadgerSpirit/CatSpirit/CouragePuppy/PowerPuppy/Crow/EvilHat/Ghost/HyperHedgehog/OwlSpirit/Pop/Toad/Ukulele/WaterElemental/Wisp 同构；ArmoredWisdomPuppy 继承 WisdomPuppy），5 个保留音高抽（ParadiseBirb/PoisonFrog/Rat/Snake/Squirrel）。gd_core/CoreItem.gd:975 对每次激活**无条件**抽 1 抽 → AWP 族/灵体族每次激活 gd 多耗 1 抽（oracle 0 抽），链静默 +1 错位：

- run610：#636 起错位 → 后续冷却卷错位 → idx108 Stone 命中 roll 翻面（O T1+T100-4+Stoned+7 vs G T3）。
- run683：gd 第 482 抽（trace_r35b 行 994，0.912009）= idx63 AWP(owner1) t=3.2 激活同源幻抽 → idx64 锤读错位抽（O roll11→round(11×0.78)=9 vs G roll9→7）、idx66 龙 O9vG8 同解。

## 四、建议（交 CoreItem 泳道执行）

1. CoreItem.activate() 的 :975 无条件抽改为动态派发：activate 调 playDropSound(-6)，基类 CoreItem.playDropSound 承接 ctx.rng.randf_range(0.9,1.1)，gd_core_items 覆写桩天然跳过。
2. **注意五例外**：ParadiseBirb/PoisonFrog/Rat/Snake/Squirrel 的 gd 覆写桩须各自补音高抽（oracle 覆写体含 rng_trace_range），否则引入新分歧。
3. 预期收割：run610（阵容 AWP×3/侧，幻抽多点）、run683 及 AWP 族全场。
4. run1447 **重配**：阵容 15 幻抽族零命中，与本根因无关；idx213 首分歧=Light Goobert T109 盲到期（C01 研究域），维持 K01 盘，勿随本修复期待变绿。
5. 验证注意：修后先跑 run610/run683 定向，再进共享验证员通道；夹具勿收缩（红线④）。

## 五、本泳道残留核查

- 代码零修改：本会话对 gd_core/CoreEventBus.gd、gd_core/CoreCharacter.gd、gd_core_py/gd_core/CoreEventBus.py、gd_core_py/gd_core/CoreCharacter.py 无任何 Edit/Write；无探针桩入树（未使用 oracle_trace_log 取证，全靠既有 trace 产物离线对拍）；无 output/_round_patches/wf_A2SIG 备份（无 patch 即无备份）。
- 唯一写盘：output/alignment_fix_log.md 追加「r35 K02/K09 定谳」节 + 本文件。
- gd_core 未改故未跑 tools/gd_to_py.py（避免转录他泳道在途 gd 改动）。
