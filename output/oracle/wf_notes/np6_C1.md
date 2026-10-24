# np6_C1 — Mana Orb 无效化面 ×2 + run688 耐力耗尽时相 取证笔记（修复·两新面与诊断债，2026-10-19）

阶段1（只分析+oracle probe 仪器对跑，零改码）。结论：**blocked（三场根因均指向本卡文件面之外；卡内零修改、无备份产出）**。
探针产物目录：`output/oracle/probe/np6_C1_morb1/`（run1083 基线 + `run1083_r18_rngdebug1/`）、
`np6_C1_morb2/`（run1427_r12 / run688_r10 / run1160_r18 基线）、`np6_C1_morb3/`（run1427_r12 ORACLE_DEBUG=1，含 rng_log.txt）。
探针命令（逐次）：
`ORACLE_FIGHTS_ROOT=.../output/oracle/probe/np6_C1_morb<N> ORACLE_ONLY_CASES='<场>' [ORACLE_DEBUG=1|ORACLE_RNG_DEBUG=1] ./output/godot36/Godot_v3.6-stable_win64.exe --headless --audio-driver Dummy --path oracle --script oracle_fight.gd`

## 0. 仪器自证（先于一切结论）

- 三场探针复跑逐字节自洽：run1083 rngdebug1 版 == 基线版（1058 事件全同）；
  run1427 ORACLE_DEBUG 版 == 基线版（193 事件全同）。debug 环境变量不扰局。
- 对照场 run1160_r18（REG 成员）：probe == 语料 == gd 三方全同（401 事件）⇒ 探针环境与语料批产环境同构。
- 对拍口径：events.json 忽略 `type_name`（oracle 出数字、gd 出枚举名，即 np4_DATA1 第 5 条双端口径，纯外观）。

## 1. run1083_r18 —— 语料陈旧，gd 无缺陷（clean 子项）

- 语料 events.json mtime=2026-10-07 04:20（1039 事件，O 胜 player，ev37「1 魔法被无效化」resisted:true）。
- 现行 oracle 探针（10-19）：**1058 事件、O 胜 opponent、ev37 无 resisted——与 gd 腿
  `output/oracle/align/gdcore/run1083_r18/events.json`（10-18 22:35，1058 事件）忽略 type_name 逐字节全同**。
- 即：卡片前提（O 抵抗 vs G 获得）在现行仪器下不存在；gd 与现行 oracle 已收敛。
- 时间线证据：`oracle/oracle_fight.gd` mtime 10-17 12:15、`oracle/Core/Buff.gd` 10-17 13:42
  （np5_K1 §3.2 所记 RESCH 注册表打桩即此批）、`oracle/Core/Character.gd` 10-16 23:47——全部晚于语料 10-07；
  oracle/ 不入 git（gitignore 现场核验），无历史可 diff。
- 同批 10-07 产出的 run1427/run688/run1160 语料被现行 oracle 逐字节复现 ⇒ 陈旧仅个例。
- **处置：`output/oracle/fights/run1083_r18/`（events.json/result.txt/rng_state.txt）需由持批产权限的脚本方
  按现行 oracle 重新生成**；本卡语料只读，不动。

## 2. run1427_r12 —— Mana Orb 判定面：卡面假说证伪，实为 K17 同类「值流静默分叉」

### 2.1 分歧形态（语料==现行 oracle，gd 独红）

- 语料 193 事件 == 探针 193 事件逐字节全同 ⇒ 语料现行、分歧真实。gd 194 事件，O 胜 opponent vs G 胜 player。
- 首分歧 idx40（t=1.0833）：O 有 `Mana Orb(own1) 105 +1 → tgt0`；gd 缺该事件直接进对手 Poison Spear 链。
- Mana Orb 机制（oracle/Items/ManaOrb.gd:28-38 ≡ gd_core_items/ManaOrb.gd:22-33）：
  onItemActivated → `rollChance()`（50%，csv_chance）→ giveMana(1)=giveStacks(Mana)（oracle Item.gd:5063-5065）。
  逐次激活各抽 1 次，胜则发 105 事件。
- 四次 orb 判定对拍（P=玩家球，O=对手球；激活源=相邻可激活物 PS(1,2)/Crown(4,0)，球(4,1)）：
  - oracle（rng_log 逐抽，`randf 0 0` 行即 Util.flip）：P@1.0833 抽 0.17475→胜（idx40）；
    O@1.0833 抽 0.727296→负（无事件）；P@1.75 抽 0.26156→**负**；O@1.75 抽 0.874801→负。
  - gd：P@1.0833 负、O@1.0833 **胜**（gd idx45）、P@1.75 **胜**（gd idx48）、O@1.75 负。
- 平衡随机数核算（BalancedRng.roll，oracle/Utility/BalancedRandom.gd:23-55）：e0∈[-0.2,0.2] 时
  P 球 1.0833 判定有效胜率 = 0.5/(3×(0.5−e0)) ∈ [0.238,0.556] **恒 > 0.17475** ⇒
  若 gd 同位抽到同值 0.17475 必判胜。gd 判负 ⇒ gd 该位抽值为异值 ⇒ **Util.rng 值流在 t<1.0833 已静默错位**
  （可见事件 0..39 逐条全同，含整条 PS 攻击链 poison3/2、block−10、damage8）。

### 2.2 卡面假说逐项证伪（全部实读代码）

- 「ManaOrb 缺无效化/烧魔分支」：两侧 ManaOrb.gd 逐行同构（仅光效/pulse 表现差）；
  O 侧「被无效化」实为 EvilCap nullify 链（oracle/Items/EvilCap.gd:17-19 → Character.gd:1180
  changeBuffNullifyChances → Buff.gd:83-143 抵抗翻转 → CombatLog.gd:770-774 resisted 事件），
  gd 侧同链 gd_core/CoreCharacter.gd:2030-2032、CoreBuff.gd:151-226 同构且**在场**：
  gd 全语料 resisted 事件 20692 vs oracle 20815（914 场全量对拍），run1083 旧语料 ev7（Vampirism 抵抗）
  两侧同现——抵抗机制 gd 不缺。
- 「giveRandomBuffs/stackTypes 池差」：gd_core/CoreItem.gd:2710-2724 ≡ oracle Item.gd:5462-5470；
  CoreConst.getBuffs()=range(Lucky..Heat) 含 Mana，两侧同（gd_core/CoreConst.gd:217 ↔ oracle Game.gd:4934）。
- 「rollChance/BalancedRng 差」：gd_core/CoreItem.gd:1178-1182 ≡ oracle Item.gd:4394-4396；
  gd_core/CoreRng.gd:266-361 BalancedRng 逐行保真（e0 同链位 `randf_range(0.2,-0.2)`、dif 调制、
  lastResult 半率/倍率、reset 语义）；`BalancedRng.new(ctx.rng)` 注入同一 Util.rng 流（CoreItem.gd:262）。
- 「连接集差（球连 Crown 不连 PS）」：两侧同为 getAffectedItems（邻接+canActivate），
  oracle Item.gd:1161-1172 ≡ gd_core/CoreItem.gd:3116-3126；PS dir1 横陈 (1,2)-(3,2)，(3,2) 在球邻域内——两侧同。
- 「装配期 e0 抽数差」：若装配流错位，t=0 的十余个判定（雪球 Cold、Lucky+2、双球 t=0 胜、Cog −10）不可能全同——排除。
- 「FlickerAnimation (0.3,1.0) 幽灵抽」：oracle 唯一无调用方可查的战斗期抽（rng_log 行316 @t≈0.217）已定位
  oracle/Items/Animations/FlickerAnimation.gd:6-17（minDist/maxDist callDelayed + minSpeed/maxSpeed speed 抽）；
  gd 侧 gd_core/CoreItem.gd:807-862（_readyInit 延迟抽 + flickerPlayAni 到点抽 + ctx._flushTimed 派发）同构——非缺口。
- 「攻击表现链抽差」：PS 攻击链 17 连抽（rng_log 行317-333：(0.95,1.05)音高、(100,160)挥距、(0.9,1.1)×2、
  pickRandom(0,2)×2、(0.8,1.2)、randf×2、(-50,50)/(-70,70)/dir 伤害飘字、randi(9,14)伤害、randf、roll×3）
  与 gd_core/CoreCharacter.gd:499-529 playAttackAnimation、:676-695 飘字三抽、takeDamage 链
  （:600-700 rollDoubleAttackEffect→accuracy→飘字→randDamage→crit）逐位对得上——未见结构性缺抽。

### 2.3 定位路径（下一手，非本卡可闭合）

静默错位点在 t∈(0,1.0833) 的无事件面抽账内，事件面无法进一步收窄——与 K17（C1MF.md）run977 同盘。
唯一低成本通道 = gd 侧逐抽台账对位：**修 `gd_core_test/OracleAlignBattle.gd` 诊断面的
ORACLE_ALIGN_TRACE 落盘写空障碍（K17 §六.1 已挂账）**，对 run1427 出 gd 侧 rng 台账，
与 `np6_C1_morb3/run1427_r12/rng_log.txt` 行 314-351 窗口逐抽对位（oracle 基准值序列已在 §2.1），
首个异值行即错位点。OracleAlignBattle.gd 在本卡文件面内，但阶段1禁改码、且 gd 腿只能脚本跑——移交修复期。

## 3. run688_r10 —— 耗尽时相无差，实为 gd 多一发 Blind 到期（CoreBuff 面，卡外）

- 语料 939 事件 == 探针逐字节全同 ⇒ 语料现行。gd 958 事件（整场多 19 条，O/G 同胜 player）。
- 首分歧 idx222：**gd 多 `Burning Banner(own3) 109 −1 timeout @9.8833 → tgt0`**；
  oracle 同栈到期在 @10.1667（idx226）或更后，9.8833 处无事件。
- **耐力耗尽本身两侧同拍**：type15 OutofStamina 双方都在 @9.9333（oracle idx222 / gd idx223）——
  卡面「耗尽时相/顺序差」的对拍不成立，耐力面（CoreCharacter.gd）无缺陷。
- Blind 台账（109 事件全列对拍）：0..idx221 两侧逐条全同；玩家侧施加 @2.0833/4.1667/5.1667/9.8667/11.7333、
  Crown 减益 @4.1667/6.1。gd 在 @9.8833 与 @11.75 各多发一次 −1 timeout（均在施加拍 +1 tick），
  oracle 无；oracle @10.1667 的到期 gd 无。到期日程内部分歧 = **Buff 暂时栈定时器驱动/重排边界**，
  即 np5_K1 §3.4 已挂账的「指针模型/弹批序源码级未解，留待 Godot 对跑」同类：
  线索 gd_core/CoreBuff.gd:250（RESCH 判据）/:587-600（_stopTimer）/:613-618（resync 支）
  ↔ oracle/Core/Buff.gd:164-171（注册表 RESCH）/：332-349（onTimeout 递归 delay≤0.01）。
- 多发的 timeout 经表现层标签链（spawnBuffLabel 系）多耗抽 ⇒ 后续 rng 流错位 ⇒ idx224 起 damage 16→15 等
  全面细节漂移（故整场 +19 条）。
- np5 补丁回归面排除：run688 双方阵容无 Chess/*、无 BattleRage 物品（21 种物品清单现场核验），
  np5 ①③ 无接触面。
- **处置：CoreBuff.gd 不在本卡文件面 → blocked 留档；归「无事件面 rng 账 / Buff 定时器」大卡。**

## 4. 可选诊断债核对（本卡未做，如实记录）

- harness item_trace 双端口径（np4_DATA1 第 5 条）：本轮对拍统一走「忽略 type_name」脚本口径，
  未改 harness 写入口径本身。
- py 腿 Holdall 172 事件全 0 排查：未触（与本卡三场根因无关，时间未花在这）。

## 5. 脏残留检查

卡内零修改：gd_core_items/ManaOrb.gd、gd_core/CoreCharacter.gd、gd_core_test/OracleAlignBattle.gd、
tools/gd_to_py.py 均未编辑；无 output/_round_patches/np6_C1/ 备份（无可还原物）；
未触语料/oracle 写面、未跑 gd 腿、未动 git。仅写盘本笔记与探针目录（probe/np6_C1_morb1-3）。
