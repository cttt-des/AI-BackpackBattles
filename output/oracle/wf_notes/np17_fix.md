# np17_fix · 宿主两笔（crafted 挪序 + 暖场闩键控）+ 吸收族重录终局轮（2026-10-22）

## 结论（先答）

本卡落 **两笔宿主单笔**（均在允许面 gd_core_test/OracleAlignBattle.gd，备份
`output/_round_patches/np17_fix/OracleAlignBattle.gd.pre_np17.bak`，各带隔离开关）：

- **A 笔（run948_r18）**：place_one 的 crafted 效果真值覆写（setCraftedEffects）由
  addItem 前挪到 addItem+宝石之后，镜像 oracle 元组循环
  （oracle/Core/Inventory.gd:1001-1035，本轮逐行亲读复核：add_child→addItemByTopLeft
  →宝石→`setData(pd)` 每元组末位）。零 rng、链位中性。REG 暴露面实测：REG 九场中
  run635_r12（MagicRing P+O）、run695_r18（Superior Ring P+O）含 crafted 效果条目，
  去 leave 由脚本 REG 闸判定；隔离开关 `ORACLE_ALIGN_NO_CRAFTED_REORDER=1` 恢复
  np17 前次序供单笔隔离。
- **B 笔（R 簇 5 场：run906/1125/1371/1409/696）**：宿主常量键控表
  `WARM_LATCH_PLAYERS`，表内场玩家 `attack_moving_forward` 初始置真（零 rng；内核
  该标志本就无战斗内复位路径，与闩死语义一致）。**性质=对脏录音（2026-10-21 32 场
  重录中 5 场暖场超时截断，np14_fix §1）的受控补偿**，仅表内场生效、仅玩家侧，
  不触碰其余 882 场语义。隔离开关 `ORACLE_ALIGN_NO_WARM_LATCH=1`。EventBus 双连
  残留（np14_fix §1 同源残留之二）**未复刻**——本笔按任务书面只做闩；若 1125 的
  双退签名（np14 §1 证据 3）仍红，属本笔边界而非判据放宽对象。
- **C 组（run989/1444/702/1022）**：授权重录已做完（np17_c1，自暖场单进程
  ORACLE_DEBUG=1，4 场全 ok）→ **不收敛，终局剔除维持，语料零写回**。逐抽比对把
  注入点钉到 Blind/Cold 批计时器的**弹层段**（下详）；核心新证据：同种子同树同输入
  的 oracle 重放跨进程形状不唯一（1022 三跑三形、无一复现语料），隐形批账态既不可
  由事件流复原、也不可由进程输入确定性复原。
- 语法闸：`--path gd_core_test --check-only --script res://OracleAlignBattle.gd`
  → 0 错（本轮实跑）。REG 九场与 gd 验证腿未跑（红线，脚本统一跑）。

## 1. A 笔 · 挪序（证据与实现）

- np16_fix §2 证据链维持（SR(5,3) dyn 6v5 → 0.6 悬崖 → run948@42 攻 1 proc 分叉）。
  本轮新增亲读：oracle/Core/Inventory.gd `createFromItemTuples` 元组循环体内次序 =
  `add_child`（→_ready→MagicRing randEffects 随机 ringTypes）→ `addItemByTopLeft`
  （item_added 广播，CA 按随机类型判）→ 宝石 setGem → `if "pd" in tuple:
  item.setData(tuple["pd"])` 末位——与 gd_core_items/Exclusive/MagicRing.gd 的
  setCraftedEffects（:185-193，尾调 sortEffects→onItemTypeChanged 广播）组合后，
  gd 挪序即逐段镜像该循环。
- 实现：place_one 内 `setCraftedEffects` 调用移至 addItem+宝石循环之后；
  `_readyInit` 的 roll 照常消耗链位（装配期链与神谕零残差不变），覆写本身零 rng。
  隔离开关缺省走挪序分支，置位时按 np17 前次序先于 addItem 覆写。
- REG 暴露面（本轮 gd_core_test/oracle_align_cases.json 实测）：九场中仅
  run635_r12 / run695_r18 含 effects 条目（各 P+O 一件 crafted ring）；键控场
  run696/1371 亦含（与 B 笔同场叠加，属目标场预期内）。

## 2. B 笔 · 暖场闩键控（证据与实现）

- 机理引 np14_fix §1（本轮复读）：5 场语料=单进程「暖场+正式场」，暖场被
  watchdog 超时截断不走 endCombat ⇒ PLAYER.attackMovingForward 暖场置真后永不复位
  （oracle/Core/Character.gd:341 复位在 combatEnd 内）⇒ 正式场玩家首次武器攻跳本体
  5 抽（(0.9,1.1)×2+pick(0,2)+(0.8,1.2)+pick(0,N)）；np16_fix §3 已在现行树+现行
  语料逐抽重锚（906@258 / 1125@370 / 1409@373 / 696@395；1371 掷链全同+「伤 9
  不可达」）。
- 实现：`WARM_LATCH_PLAYERS` 常量表（5 场 case_id）+ run_case 内玩家角色构造后
  置 `p.attack_moving_forward = true`。落位在装配之前，链零消耗；首次
  playAttackAnimation 只耗默认实参 (100,160) 一抽，与语料闩态逐位同构。
- np14_fix §1「禁 gd 侧迁就」的红线针对**无条件**闩（会破 882 旧语料场）；键控表
  版不触表外场，与该红线不冲突。本笔是录音工件补偿，不改内核判据。

## 3. C 组 · 重录与逐抽定谳（本轮实跑）

### 3.1 重录执行

命令：`ORACLE_FIGHTS_ROOT=D:/文件资料/学习/自动背包AI/output/oracle/probe/np17_c1
ORACLE_ONLY_CASES=run989_r18,run1444_r18,run702_r18,run1022_r18 ORACLE_DEBUG=1
output/godot36/Godot_v3.6-stable_win64.exe --headless --path oracle --script
oracle_fight.gd`。结果 PASS：暖场=run702（丢弃）；run702 ok 2205 ticks ev=3444
（adjacent 复跑逐字节一致）；run989 ok ev=20072；run1022 ok ev=3910；run1444 ok
ev=1047。

### 3.2 形状表（events.json sha256 前 16 位，本轮实算）

| 场 | 语料 | np14 probe（单场自暖） | np17_c1（本轮） | gd 腿 np16v |
|---|---|---|---|---|
| run989_r18 | f1635d7ab4257b72 | **同语料** | c5ea027a9de55757 | —（div@1709） |
| run1444_r18 | 8fc1ad6b8432125d | **同语料** | c7bf4e545f8c5576 | —（div@330） |
| run702_r18 | 73968f90105de3e4 | 9e73423edf4204d9 | **同语料（逐字节）** | —（div@423） |
| run1022_r18 | aa72f0761a09e4f5 | 5aac01c6a17a85aa | c57893cec7555d3d | —（div@1386） |

- run702 首次被重放逐字节复现（np17_c1）；np14 同模式前缀（自暖+正式+复跑）却
  3444 形（div@1590）——同模式跨进程形状不唯一实锤。
- run1022 三跑三形、无一复现语料；其 np17_c1 形在族点 @1386 与 gd 同向（同样缺
  语料的 Banner Blind TO -1 @13.0333，语料 [1386] vs np17_c1 [1386]=Paradise Birb
  @13.0667），但后段 @3349 与 gd 再歧——「gd 形」亦不稳定抽样。
- run989/1444 np17_c1 又添新形（20072/1047），两场各已集齐 ≥3 形
  （np14/np15/np17 进程）。

### 3.3 逐抽注入点（np14 rng_log vs np17_c1 rng_log，去进程时钟 @t 后逐行比对）

逐抽链在首个分歧前**零差异**；首个结构差全部落在 EVENT 边界（弹出层）：

| 场 | 首构差（draw） | 其前 EVENT 计数 | 语料规范流首歧 | 注入点段位 |
|---|---|---|---|---|
| run989 | 2313：np14 抽 (0.975,1.05)+(0.8,1) 后 EVENT 0；np17_c1 直接 EVENT 109 | 双侧 446 | 446 | 弹层：Banner Blind +1 dur5（语料[445] @6.6667）后，np17_c1 的批 @6.7667 提前 2 tick 弹 -1，语料批存活过 [446] Birb @6.8 |
| run1444 | 2028：np14 抽 (0.95,1.05)；np17_c1 直接 EVENT 110 | 双侧 347 | 342（-1 v -3） | 弹层：Frostbolt Cold +3 dur3 与抵抗 +1（[338-339] @6.2333）后，语料拆弹 -3@6.2333 + -1@6.35（[341-342]），np17_c1 并弹 -3@6.35 |
| run702 | 591：randInBox ±30 v ±10 视觉偶对（值域差、链不移位，np16 §3 构造排除）；后段反向同对 @738 | — | 无（≡语料） | vs gd @423：语料 [423] Light Goobert Blind TO **-7** @3.8833，gd -6（上游净化吃永久栈 v 拆临时批，np15 §7.3 维持） |
| run1022 | 6633：np14 EVENT 109；np17_c1 抽 (0.95,1.05) | 双侧 **1386** | 1386 | 弹层：语料 [1386] Banner Blind TO **-1** @13.0333 多弹一枚（1 tick 相位差），np17_c1 与 gd 同缺；np17_c1 首枚 Banner 弹在 [1387] @13.1167 |

### 3.4 终局判词

1. 施加/净化段的**可见事件与逐抽链均不携带差异**（弹出边界前零抽差）——隐形批账
   （永久栈/临时批劈分、timeout 指针相位）的写入发生在施加/净化时刻，但只在弹层的
   数量/时刻读数上显现 ⇒ 注入点=弹层段，病根=施加/净化的不可见内部劈分。
2. 该内部态**跨同配置 oracle 进程不唯一**（§3.2 形状表），故既不可由事件流复原、
   亦不可由进程输入确定性复原；gd 侧任何单笔无判据（盲修），**剔除维持**。
3. 语料零写回：702 重录≡语料（写回=无操作）；989/1444/1022 重录≠语料（写回=把
   语料换成分布的另一次抽样，无收敛意义）。授权已按「重录做完、不收敛即留档」的
   任务书面执行，fights/ 目录本轮零写入。
4. 后续唯一闭环路径不变（np15 §7.3/np16 §4）：oracle 侧 tos/pointer dump 桩
   （oracle/ 只读，需主控专项授权）对拍单场内部态。

## 4. 改动与备份清单

| 文件 | 改动 | 备份 |
|---|---|---|
| gd_core_test/OracleAlignBattle.gd | A 挪序 + B 键控表（同一文件两笔，各有隔离开关可独立撤） | output/_round_patches/np17_fix/OracleAlignBattle.gd.pre_np17.bak |

- gd_core/、gd_core_items/、gd_core_py/、assets/ 本轮零改动（A/B 均宿主面，
  内核单笔不需要——闩语义经攻击/激活动画入口已全覆盖）。
- 语法闸 0 错（`--path gd_core_test --check-only`，本轮实跑）。
- REG 九场未跑、gd 验证腿未跑（红线）；判据未放宽；未 commit/push。
- oracle/ 树只读未触；output/oracle/fights/ 本轮零写入；新落盘仅本笔记 +
  probe/np17_c1/（分析特权内）+ 备份一份。

## 5. round2 增补（leg+fix_r1 对拍后，2026-10-22）：R 簇 5 场终局留档剔除

### 5.1 对拍事实（主控反馈 + np17v_fix_r1 腿复核）

REG 九场绿（A/B 两笔保留）；run948_r18 一致 ev=2677（A 笔兑现 ✅）。仍红 9 场：
C 组 4 场（989/1444/702/1022，§3 终局维持）+ R 簇 5 场。R 簇分歧位全部后移
（906：6→37、1371：51→137、1409：25→51、696：46→79；1125 不变 49 但内容已换）——
**B 笔闩补偿在全部五场生效**，首攻层已对齐，暴露出暖场残留的**第二层**。

### 5.2 第二层残留·事件级实证（corpus vs np17v_fix_r1 逐行实读）

1. **双发监听投递（陈旧连接）**：
   - run1125@49：语料 [48]/[49] = `Amulet of Agility Mana amt=3` **两笔**（同 par=47、
     同 @1.25）；腿只有一笔 → 首笔 used 消耗的退还监听**双份投递**。
   - run1409@51：语料 [50]/[51] = `Amulet of Light TemporaryMaxHealth amt=3` 两笔
     （同 par=49）；腿一笔。同族。
   - run906@37：语料 [37] AoA amt=4 → [38] InvestOp → [39] AoA **amt=6**（双笔且
     **量不同**、且 AoA(4) 先于 InvestOp = 投递序也与腿相反）；腿 = InvestOp →
     AoA(4) 单笔。机理 = 暖场超时截断未走 combatEndDeferred → EventBus
     disconnectAll（oracle/Core/Game.gd:2956）未跑 → **暖场物品实例的连接仍在**，
     正式场每次 buff 变更/used 投递给陈旧+新鲜两套监听；陈旧实例的应答量带暖场期
     累积态（4 v 6），连接序=陈旧先于新鲜（np14_fix §1 预言的第二残留，逐位兑现）。
2. **闩不是永久闩——语料存在中途复位**：对 np14 probe rng_log 做「(100,160)+双
   (0.9,1.1) 攻击本体」扫描并按物品名归侧：906 探针全场仅 1 次本体（=对手首攻，
   np14 §1 同归属），**玩家全程闩死**；而 1125/1409/696 探针（首攻跳本体
   =闩，np16 §3 锚）在后续**玩家物品**攻跑出完整本体——1125 Eggscalibur、1409
   Eggscalibur、696 Dragon Knight。即语料闩语义 = 继承闩 → 在首攻与次攻之间的某时刻
   θ **复位一次**（暖场最后一击的 tween 跨截断边界补完 → attackMovingBack）→ 次攻
   重建闩 → 此后新 tween 不再补完（阻塞循环）恒闩。θ = 暖场截断瞬间该 tween 的
   剩余时长，**墙钟（60s watchdog）截断点的函数**。1371 探针本体全开（np14 §1 证据 5
   「反叉」/np16 §3.2：probe 无闩）——该场探针连第一层残留都未复现，probe≠语料。
3. **链级错位**：run1371@137 = 语料 Falcon Blade 命中伤 6 v 腿 MissedAttack；
   run696@79 = 语料伤 4 v 腿伤 5，且逐抽比对（np14 probe rng_log vs 腿 rng_trace，
   命名归一 randInBox/roll/pick/randBuffLabelDir 后）显示 696 在腿侧多耗一支
   randf(0,0)（@draw549）后整块伤害数字抽右移——件级/子系统性错位，与双发/闩复位
   同属录音工件面。

### 5.3 终局判词：R5 剔除，B 笔保留（部分推进）

- 双发投递的应答量 = 陈旧实例暖场期状态（4 v 6），复位时刻 θ = 墙钟截断函数；
  两者都**不是 (seed, lineup) 的函数**，gd 单种子宿主原理上不可确定性复原
  （同构 np15 §2 双稳论）。逐场手调阈值表 = 对一份脏样本的硬修，违反本程
  「不硬修」纪律。
- 唯一真修 = np14_fix §1 原议的**语料侧**重录加 determinism 复跑边界（或驱动改
  warm+正式+复跑三执行）；语料冻结（本程红线）下 R5 按「困难笔」剔除留档。
- **B 笔保留**：REG 九场绿实证其对 882 场零扰动；对 R5 完成首攻层对齐（四场分歧
  位后移、1125 首攻伤值已齐），属「仅推进=部分推进已保留」。**本 round2 零产线
  改动**（无新单笔，A/B 维持 round1 状态）。
- C 组 4 场维持 §3 终局（隐形批账不可复原）。

### 5.4 round2 纪律

- 本轮零产线文件改动；gd_core_test/OracleAlignBattle.gd 未再动（A/B 隔离开关
  原样保留，供脚本侧单笔隔离）。gd 验证腿未跑（主控统一跑）；fights/ 与 oracle/
  零写入；未 commit/push。分析输入 = np17v_fix_r1 腿产物、probe/np14_fix 探针、
  冻结语料（全部只读）；比对手法 = verify_oracle 规范流 + 会话内逐抽归一比对 +
  攻击本体扫描（只读）。
