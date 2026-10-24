# np21 修复轮全档（py 补偿表移植 ＋ R5 双执行拓扑复刻 ＋ run1444 法医收口，2026-10-22 → 2026-10-24）

承接面：np17-np20 遗留 8 红场——R5 五场（run906/run1125/run1371/run1409/run696）＋run1444＋py 镜像 2（run702/run1022，np20 末「gdcore≡oracle 但 py 分歧」桶）。本轮处置完毕：

- **三收口**：run1125_r18 / run1409_r18 / run906_r18 守门双腿（gd+py）双判据（canonical 事件元组＋渲染行）全长 PASS；
- **两定谳**：run696_r18 / run1371_r18 以测量级漂移实证合并定谳为「反射/落地面墙钟采样潜伏类」困难笔（np17 §5.3 判词升级为双场测量级）；
- **一法医**：run1444_r18 判不可修——根因不在 gd_core，在语料条目的位置依赖（生成批跨场残留）；
- **py 上账**：np21-① py 腿补偿表移植，run702/run1022 兑现三方一致（np20「py 镜像 2」清零）；
- **真内核修正一笔**：gd_core/CoreItem.gd getNextFreeLabelPosition 空槽判定 ≥→>（严格大于）。

基线：r51 906/914 → r52 **911/914**（新增 5、退步 0）。np20_fix.md 自始未落盘（np20 层收口节实读在案），本档承接 np20 round2 以后的全部台账。

## §0 战果总览（实跑数字）

| 场 | 结果 | 守门口径（tools/_np21_gate.py） | 关键数字 |
|---|---|---|---|
| run1125_r18 | green 收口 | `--cases run1125_r18 --tag np21r5a` 退出码 0，[gate] ALL PASS (1 场，gd+py 腿) | 25006 事件对齐语料闸截尾；暖场实跑 ticks=3095 events=25008 |
| run1409_r18 | green 收口 | `ORACLE_ALIGN_CASES=run1409_r18 … --tag np21r5b` 退出码 0 | 25042 事件；无退步复验 10 场 20 腿 ALL PASS |
| run906_r18 | green 收口 | `ORACLE_ALIGN_CASES=run906_r18 … --tag np21r5c` 退出码 0 | 25028 事件；无退步复验 11 场 22 腿 ALL PASS |
| run696_r18 | impossible（困难笔留档） | 机理论证＋两级授权测量闭环，本档 §3.4 即留档证据 | 十一次重放、四次 events≡语料；9983==9983 全局对账 |
| run1371_r18 | impossible（困难笔留档） | 测量级漂移四重放；真内核修正另入账 | 首抽歧 452→881；12 场 24 腿 ALL PASS（np21r5f） |
| run1444_r18 | impossible（法医判不可修） | `--cases run1444_r18 --tag np21_fr` 基线 gd/py 双腿 RED ev@330 ln@215（双判据同位） | 语料 1030 事件（events.json 实读）；gd 干净重放 1002 事件 |

- REG 守门最终：**ALL PASS**（np21r5reg 起累加复验：1125 轮 REG 九场十八腿 → 1409 轮 10 场二十腿 → 906 轮 11 场二十二腿 → 1371 修正后 12 场 24 腿，零退步）。
- r52 全量最终：**911/914**（脚本层执行）；alignment.json 实读 aligned 911/total 914；快照 r52_l1.txt 911 行，对 r51 新增 5（run906/run1125/run1409/run702/run1022）、退步 0（`tools/aligned_set.py check -b r51_l1.txt` 退出码 0）。

## §1 np21-①：py 腿补偿表移植（净真值表直灌＋开关语义）

**背景**：np20 末 run702/run1022 的 gd↔oracle 已全长一致，唯 py 镜像未同步（[gd_core_py-transpiler] 桶），挡在三方一致之外。np21-① 把 gd 宿主（gd_core_test/OracleAlignBattle.gd 文件头三表 WARM_LATCH_PLAYERS:56 / PERM_STACK_HARVEST:80 / PERM_STACK_OVERRIDE:99 ＋ :481-514 注入段）镜像到 py 腿。

**移植面（实读）**：tools/verify_oracle.py:70-94 四表——

- `PY_PERM_STACK_HARVEST = {"run702_r18": True, "run1022_r18": True}`（:75）；
- `PY_PERM_STACK_OVERRIDE = {"run702_r18": {109: 1}, "run1022_r18": {109: 6}}`（:76）；
- `PY_WARM_LATCH_PLAYERS`（R5 五场，:77-81）；
- `PY_R5_DUAL_EXEC`（现三键 1125/1409/906，:90-94）；

注入段 :303-334（构造 GDCoreEngine 时传 `warm_latch` / `perm_stack_override` / `r5_dual_exec`）；引擎侧参数与执行面在 simulator/gd_core_engine.py:612-650（r5_warm 递归）、:711-718（perm_stack_override 灌入）、:858-861（stale_used_stacks 覆盖）。

**净真值表直灌（设计要点，verify_oracle.py:303-310 注释原文依据）**：py 腿**只灌 np20-C canonical 封闭推导的净真值表**（PERM_STACK_OVERRIDE），**不复刻** gd 宿主的暖场收割管线。理由：py 干净暖场终局态 ≠ gd——如 run702 py 侧收割会得 lucky=1/106=44 等非惰性值，注入后先行消耗改变掷链；实测 B 变体 `{109:1}` 单值即全场一致；gd 侧收割值经 OVERRIDE 校正后净效果与真值表等价，语义同源。三者（真值表/暖场闩/R5 拓扑）皆录制工件补偿、键控生效、零 rng 消耗（播种前纯字段写）。

**开关语义（坑位记载）**：三个隔离开关 `ORACLE_ALIGN_NO_PERM_HARVEST` / `ORACLE_ALIGN_NO_WARM_LATCH` / `ORACLE_ALIGN_NO_R5_DUAL_EXEC` 与 gd 宿主**同名同义**，判定一律「环境变量置任意**非空**值即关对应补偿」（py：verify_oracle.py:313-315 `os.environ.get(...) != ""`；gd：OracleAlignBattle.gd:639 `OS.get_environment(...) == ""` 取反同义）。坑：NO_* 型开关**非空即关**——置 `=0`、`=false` 同样是关，不设或空串才是开；单笔隔离/复现实验时只以「不设」为开。另 gd 宿主侧 `ORACLE_ALIGN_NO_PERM_HARVEST` 是「关收割即关本覆盖」（OracleAlignBattle.gd:97 注释），py 腿同闸 OVERRIDE——开关名与作用面两侧一致，勿在 py 侧另起开关名。

**兑现**：r52 全量中 run702/run1022 入三方一致集（alignment.json 实读；np20 的「gdcore≡oracle 但 py 分歧 2」与 [gd_core_py-transpiler] 桶消失）。

## §2 R5 双执行拓扑复刻设计（gd 宿主管线 ＋ py 镜像）

**键控表 R5_DUAL_EXEC**（gd_core_test/OracleAlignBattle.gd:152-214，六行；参数全部语料侧封闭推导，注释按 PERM_STACK_OVERRIDE 体例落表；隔离开关 ORACLE_ALIGN_NO_R5_DUAL_EXEC=1 置非空值即关，:139）：

| case | 键 | 推导注要点（表注原文节录） |
|---|---|---|
| run1125_r18 | warm_event_gate=25000 | θ 未引入：latch 扫描唯一本体=对手 owner3 首攻，与 np17 §5.2-2 记载相悖，以逐行扫描为准（已写入表注） |
| run1409_r18 | ＋stale_used_stacks={Amulet of Agility:{105:-0.375}} | AoL 全双/AoA 分路径双发/Egg 48/48 对称双笔=合法机制勿注入；X0 封闭推导（§3.2） |
| run906_r18 | ＋stale_used_stacks={Amulet of Agility:{105:0.125}} | 同型推导，首试即中（§3.3） |
| run696_r18 | warm_event_gate=25000 | 双发面=∅，残差全落抽链（draw549），归属=潜伏类（§3.4） |
| run1371_r18 | ＋theta_time=2.0＋stale_label_slots_busy=true | θ 夹逼区间 (1.400,2.100) 内最后一个整 tick 阈；θ 为推断值以守门对拍为准 |
| run1444_r18 | warm_event_gate=25000 | 暖场自然收尾（1088 ticks 终局）⇒ 唯永久栈跨执行存活；stale_timer_left 已移除（§4） |

**管线五件（实读行位）**：

1. **r5_warm 递归**（:618-640）：同 case 同 seed 构造独立 ctx 跑**干净第 1 次执行**（暖场）——无闩、无任何键控补偿、无 rng_state 注入，截于暖场事件闸 T_w（表内 warm_event_gate）**不清理**；暖场递归自身禁止一切键控（r5_warm=true 分支在各键控点显式让路：:640/:843/:888/:891）。1125 实跑 ticks=3095、events=25008。
2. **永久栈收割灌入**（np18-C 语义：teardown 的 cleanse 不清永久栈；暖场玩家终局 permanentStacks 灌正式场，:630-632/:646-648）。
3. **连接泄漏嫁接**（:807-834）：暖场 ctx 打开连接台账 connect_journal（gd_core/CoreEventBus.gd:42-43/:137-138，默认关、非键控零扰动；py 镜像 gd_core_py/gd_core/CoreEventBus.py:25-26/:153-154 已同步）；筛「发射体=暖场玩家 ∧ 接收体=玩家侧物品」的存活连接（oracle 里 PLAYER 节点跨执行复用，暖场连接的发射体与正式发射体是同一节点），按暖场时序挂正式 bus 于 startBattle（:865）前＝**陈旧先于新鲜**，与语料投递序一致；陈旧接收体的 ctx/character_ 与 damageSource/chanceRng/damageRangeRng 三抽源改指正式侧（oracle 节点/Util.rng 进程级共享⇒天然指向正式；陈旧处理器消耗正式链 rng、应答入正式日志——run696@79/run1371@137 旁证）；BalancedRng 平衡态保留暖场值（正式 prepareItems 重置只遍历正式清单）。纯内存字段写＋bus 连接表追加，零 rng 消耗。1125 实跑 11 连接/5 接收体。
4. **第四残留 fatigueCounter 注入**（定谳注释 :619-637，注入 :873-874）：oracle 的 CombatTimer 是跨执行共享节点，fatigueCounter 只在 combatEnd() 复位（oracle/Interface/CombatTimer/CombatTimer.gd:98-99；start():114-119 与 initialize() 均不复位——本轮只读核对）⇒ 暖场 2878 ticks=47.97s＞FATIGUE_TIME=17 已入疲劳且截断不复位 ⇒ 正式场 hasFatigueStarted()（=counter>0，:181-182）自 t=0 恒真。实证链：语料 Owl Spirit 首冷即走 fatiguemana 分支（入场 round(8×1)=8＋放大掷：语料 12/11/10…16 v gd 干净场 mana=2 分支 2-4，事件 [269]/[273]）；oracle 复放（ORACLE_FIGHTS_ROOT 重定向 output/oracle/probe/np21_r5/，oracle/ 树零写入）逐位复现语料 25006 事件，rng_log 同窗 8 连 roll 掷点 4 赢=8+4=12 闭环。**值不敏感论证**：正式 t=14 startFatigue 把 counter 复位 0（CombatTimer.gd:145-151 ≡ gd_core/CoreCombat.gd:437-441 同构），残留仅经 hasFatigueStarted 面可观测——注入暖场截断值即可（gd 暖场截断 3095 ≠ oracle 2878 的两引擎暖场差异不影响本面）。注入点=startBattle 后（startBattle 清 counter：CoreCombat.gd:149；activateItems 只清 flag：:247）。辅证：GDScript for-in-可变-int 定点边界由 gd_core_probe/LoopBoundProbe.gd 实测定谳（iterations=2），排除活边界解释。
5. **键控覆盖件**：stale_used_stacks（:849-868，np20-C 同型：语料事件面推导真值覆盖陈旧实例计数器，仅 X0 一维，net-p 引擎内实时算）；stale_label_slots_busy（:836-847，run1371：把陈旧接收体五槽置「刚占用」ts=ctx.time+2.5，0.5s 后自然回收）；theta_time 一次性复位（:889-893，表内时刻把玩家闩复位一次，此后首攻跑完整本体并自动再闩）；stale_timer_left（:895-906 钩子在档、表内已无键——run1444 定谳后移除，见 §4）。

**py 腿同构镜像**：simulator/gd_core_engine.py:612-650（构造期 r5_warm 递归，_r5_warm/_r5_warm_gate 为内部参数外部不传；注释逐点同步三面回灌语义）＋:858-861（stale_used_stacks）；tools/verify_oracle.py:86-94（PY_R5_DUAL_EXEC，与 gd 表逐点同步，现三键 1125/1409/906）＋:313-334（开关与注入）。

**stale_used_stacks 封闭推导法（方法级沉淀，两场通用）**：①新鲜侧确定性算术（X 从 0 起、refund=25%）先消歧全部单发归属（零矛盾为铁则）；②陈旧侧 (X0, 双向掷带宽 [0,2×entry]) 网格拟合出候选区间；③等价类分析——区间内 entries 序列唯一性＋陈旧退款笔数与语料消歧数精确吻合（1409：275 笔；906：256 发火=语料 AoA 双对数），gd 类（X0=-0.250）恰界外则弃；④掷点级核对（gd trace 同 draws 同 wins ⇒ 陈旧 net-p 与 gd 同域，无需覆盖）；⑤仅覆盖 X0 一维，取类中点（类内任取值等价）。证据包「封闭推导不可能」「陈旧量只能逐位标定」两判词（1409/906 轮）均被该方法超越。

## §3 R5 逐场战果（全部本会话实跑）

### 3.1 run1125_r18——green（收口）

守门输出尾部（`python -X utf8 tools/_np21_gate.py --cases run1125_r18 --tag np21r5a`，退出码 0）：`[gate][gd] run1125_r18 PASS / [py] 完成 1/1 场 / [gate][py] run1125_r18 PASS / [gate] ALL PASS (1 场，gd+py 腿)`。判据双轨（canonical 事件元组＋渲染行）全长一致，事件数 25006 对齐语料闸截尾。REG 九场复验（--tag np21r5reg，退出码 0）：gd+py 十八腿全 PASS，零退步。

分歧位推进轨迹：**49（双发缺失）→ 269（嫁接后 Owl 疲劳分支）→ 全长 PASS**。第四残留 fatigueCounter 定谳链见 §2-4（gd↔语料@269→PASS 的最后一块）。

诚实备注：gd 暖场与 oracle 暖场在截断点存在 tick 差（3095 v 2878），本场经守门实证其可观测面（AoA/FL 陈旧 usedStacks 退款量、永久栈、疲劳非零性）不受影响。

### 3.2 run1409_r18——green（收口）

守门（`ORACLE_ALIGN_CASES=run1409_r18 python -X utf8 tools/_np21_gate.py --cases run1409_r18 --tag np21r5b`，退出码 0）双腿 PASS，25042 事件对齐语料闸截尾；无退步复验（同 tag）：run1125_r18＋REG 九场共 10 场 20 腿 ALL PASS。

证据链：①现状守门 RED ev@51 ln@37（与 np17 §5.1 档案一致，首分歧=语料 [50]/[51] AoL 双发）；②入 R5_DUAL_EXEC 后 51→306——恰为证据包预言的 idx306 AoA 陈旧量位（语料 2 v gd 4）；③机理定谳（备份 AmuletofAgility.gd.np21r2_orig → 临时取证桩 ORACLE_R5_AOA_DEBUG → 取证 → 字节级还原 md5 81ff88fc 核符＋gd_to_py 重同步）：gd 干净暖场陈旧 AoA usedStacks[105] 收官 X0g=-0.25、陈旧 amp 冻结 80.50（暖场 Birb×8.05×10，正式期不再增长），与 np14 探针互证=两次干净重放同值；语料（2）=旧树录制批异值（np20-C「收割值≠真值」同型）；④语料封闭推导（证据包『封闭推导不可能』判词被新方法超越）：新鲜侧先消歧 43 笔单发（全=新鲜，零矛盾）；陈旧侧拟合 X0 单区间 [-0.500,-0.255]，等价类内 275 笔陈旧退款=语料消歧后 275 精确吻合，X0=-0.250（gd 类，285 笔）恰界外；掷点级核对首两笔同 draws 同 wins（[68.53,94.09,49.35]→1 赢、[11.88,57.90,95.75]→2 赢）⇒陈旧 net-p 与 gd 同域 [57.90,68.53) 无需覆盖——仅覆盖 X0 一维，取类中点 **-0.375 首次注入即 PASS**；⑤键控落表 stale_used_stacks={Amulet of Agility:{105:-0.375}}（:167-168），py 腿同构镜像。证据包 ④ 三组 FF 量差对与 ③ Egg 48/48 对称双笔均未注入——守门全长 PASS 实证其为引擎自然机制。

诚实备注：gd 暖场（2605 ticks/25013 事件）与探针暖场（2473）存在截断点差异，本场经封闭覆盖后可观测面全闭。

### 3.3 run906_r18——green（收口）

守门（`ORACLE_ALIGN_CASES=run906_r18 python -X utf8 tools/_np21_gate.py --cases run906_r18 --tag np21r5c`，退出码 0）双腿 PASS，25028 事件；无退步复验（同 tag）：11 场 22 腿 ALL PASS。

证据链：①现状 RED ev@37 ln@22（与 np17 §5.1「906 6→37」及证据包 doubles 首对 [37]/[39] 一致）；②入键控 37→219——语料 [219] AoA 陈旧退款 11 v gd 10（parent=218 ManaOrb 花费 -35，后续 giveRandomBuffs 簇链漂移）；③同型封闭推导（1409 方法升级）：新鲜侧 338 笔花费消歧零矛盾；陈旧发火数 256=语料 AoA 双对数精确吻合；大额花费（-35→+8.75）致整数平移简并（43 类同 256 发火）需额外判据——取证桩（备份→桩→还原 md5 81ff88fc 核符）实测 X0g=-0.25（与 1409 同值）、amp 冻结 17.00；分歧位结构（entry 9 v 8）⇒语料残差高 δ∈[0.25,1.25)；首笔陈旧 entry=3（前缀事件含退款量全同⇒抽数对齐铁证，排除 entry=2/4 类）⇒X0c∈[-0.25,0.75)；交集剩两子区间 [0,0.245]/[0.25,0.495]，取 [0,0.245] 代表 **0.125 首次注入即 PASS**（gd 腿），py 腿镜像同值亦 PASS；FalseLife-19 双发 59 对全同量由拓扑自动复现（无记账无需覆盖）。④键控落表（:183-184）。

诚实备注：gd 自身陈旧发火 258 v 语料 256（自身演化异，经覆盖后可观测面全闭）；gd 暖场截断点与探针（2771 ticks）有差。

### 3.4 run696_r18——impossible（机理论证＋两级授权测量闭环；按 np17 §5.3 困难笔口径结案，本节即留档证据）

核心论证：696 的 draw549 残差根植于一个「**启动态采样的非确定潜伏变量**」，非 (seed,lineup,truncation) 的函数，事件面与抽面前缀均无其投影，机理上不可从冻结语料确定性复原。

证据链（全部实跑）：①两桩授权取证——BR 桩（oracle/Utility/BalancedRandom.gd roll() 一处环境变量门控 ≤5 行，备份 BalancedRandom.gd.pre_br.bak 基线 md5=579edf9f，重放 attempt1 即 events≡语料 25023 条全同；取证后还原三方比对 True/True、grep=0、git status oracle/ 干净）＋前轮 takeDamage 桩（同纪律，md5 e94c8668 三方一致）——两桩共十一次重放、四次 events≡语料样本；②潜伏态非确定直接实测：两个 corpus-true 样本（run8B/run9A＋BR-run1，事件均与语料逐位全同）在同一 FB 首击处携带不同内部态——atkBlind=4（acc=85）v atkBlind=7（acc=70，BR 桩 target=0.7 实测），且暖场截断 tick=2780/3573/3575 漂移（oracle 暖场自身启动态非确定）；③潜伏态无投影：全部样本 draw0-548 逐位同（含 (100,160)=150.673248 与 0.286585 双锚），分歧仅在 draw549 的抽数（语料类 1 v gd 类 2）——潜伏态在分歧点前零观测面；④全局对账：corpus-true 重放正式场平衡掷实抽数==日志 randf(0,0) 行数（9983==9983 精确）；DAE 掷的缺席/在场跨场条件性（run570 交叉验证：oracle 重放与 gd 同型 {0:2,1:77} 双侧一致；696 双侧分叉 {0:1,1:2154,2:57} v {0:1,1:2179,2:35}）——分叉面即潜伏态轨迹。

结论：语料录制批的暖场（旧树＋彼时机器启动态）采到的潜伏样本，与 gd 任何确定性暖场不可保证同分布同样本；1125/1409/906 三场的潜伏态恰为可复现类（X0 类问题、封闭推导已收口），696 属不可复现类——np17 §5.3「非 (seed,lineup) 函数」判词在本场升级为**测量级定谳**。

处置：R5_DUAL_EXEC 保留 696 现行键控（warm_event_gate=25000，事件面前 79 位对齐的最好确定性基线，ORACLE_ALIGN_NO_R5_DUAL_EXEC 可单笔隔离）；本场按困难笔留档剔除。探针 output/oracle/probe/np21_696_br 与 np21_696_takedmg；日志 br_run1/takedmg_run8B/9A 存 output/_round_patches/np21_fix/。

### 3.5 run1371_r18——impossible（测量级漂移定谳＋真内核修正一笔入账）

核心证据（全部实跑）：①漂移定谳（授权桩四重放）：oracle/Core/Character.gd takeDamage 桩（ORACLE_TAKEDMG_DEBUG 门控 ≤10 行，备份 Character.gd.pre_takedmg1371.bak 基线 md5=e94c8668，取证后还原三方比对 True/True、grep=0）——同一 ev137 攻击时刻跨样本 atkBlind=6（run3/run4）v 8（run1）且 lucky=1 恒定、acc=75/65——盲层落地量在同种子同阵容重放间漂移，非 (seed,lineup) 函数；gd 侧 CANMISS 实测 lucky=1/blind=6/acc=75（恰在 oracle 样本范围内），语料侧 ev137=hit 而重放样本均 miss-轨迹（DIFF@51/219/236/242 全部非 corpus-true，四轮无一命中语料样本）⇒语料录制批的盲层潜伏样本不可复原；②与 696 定谳同构互证（696 测得 corpus-true 样本 atkBlind=4 v 7；1371 又见 6 v 8）——R5 后两场共享同一反射/落地面墙钟采样潜伏机理，判定同类困难笔；③DAE 短路假设已测并证伪回滚（若 DAE 不抽则首攻应 1 掷，语料首攻窗实抽 2 掷（draw446-447）⇒oracle DAE 恒抽；该假设曾使 ev@137→ev@51 倒退，已回滚并复验）——这一负结果同时否定「可修移植差」路径。

**真内核修正（非补偿）**：gd_core/CoreItem.gd getNextFreeLabelPosition 空槽判定 ≥→>（严格大于，现 :2868 `if ctx.time + 1.0 > buffLabelPositionTimestamps[i]:`）——oracle Util.time 逐帧浮点累加（Util.gd:145-152）使「占用后恰 0.500s 整」到点实效为严格大于（run1371 draw452 DK 实证：oracle 走回退 (30,30)、>= 语义走空槽 (10,10)→链值即歧）。修复后 run1371 首抽歧 452→881（=ev137 攻击），REG 九＋1125/1409/906 共 12 场 24 腿 ALL PASS 零退步（np21r5f）；py 镜像同步（gd_to_py，gd_core_py/gd_core/CoreItem.py:3088 同为严格大于）后抽查绿（np21r5g/j）；注释已落 U3 块（CoreItem.gd:2859-2867）。

工程面：R5_DUAL_EXEC[run1371]={warm_event_gate:25000, theta_time:2.0, stale_label_slots_busy:true}（θ 在潜伏未解带前不可验证，留表）；CoreItem 修复前备份 CoreItem.gd.np21r5_orig；探针 output/oracle/probe/np21_1371_{lbl,var,takedmg}/；日志 tk1371_run1-4＋var_run1-3＋lbl_run1 存 output/_round_patches/np21_fix/。

建议主控：696＋1371 两场以「反射/落地面墙钟采样潜伏类」合并留档（np17 §5.3 判词升级为双场测量级定谳）；R5 最终战果=1125/1409/906 三场收口双绿＋一处真内核修正＋两场困难笔定谳。

## §4 run1444_r18 结案（法医判不可修）

**判词**：根因不在 gd_core，在语料条目的**位置依赖**——output/oracle/fights/run1444_r18/events.json（1030 事件，本轮实读核符；2026-10-21 10:11 批量生成）携带生成批**跨场残留**，任何孤立重放配置（solo／前邻 run635／前邻 run1443）都不能复现它。前邻 run1443_r18（语料批量序真实前邻，fights.json idx 832）作 position-1 时，run1444 重放跟随语料模式至 idx341（P330==C330：无 5.9833 瞬弹；P335 amount=2 同语料）——实证跨场残留真实存在且 run1443 贡献主导，残留首咬点即寒冷计时器 5.88-5.98 批账窗。

**残留通道候选（未完全钉死到单一字段）**：oracle/Core/Buff.gd:52-58 reset() 只 setStacks(0)＋清 resistStacks/三 chance，不清 permanentStacks/temporaryStacks/nextTemporaryTimeout、不停计时器；temporaryStacks 仅经 fightEnded 路径的 combatEndDeferred（oracle_fight.gd:790-792→Core/Game.gd:2957→Core/Character.gd:344→Buff.gd:356-358）清除；teardown（oracle_fight.gd:997-1024）只走 cleanse；PLAYER 跨场复用（oracle_fight.gd:590 instanceCharacter）使前场状态泄入后场。代码漂移假设已排除：oracle/Core/Buff.gd 与 10-15 备份 diff 为空；oracle_fight.gd 10-15↔10-22 语义 diff 仅 lineups 导出字段（snapshot 版次/crafted），战斗重放语义零变化——语料分歧只能来自生成态残留。**np19 对 run989 的「多出一格不可见清洗消耗」迷题由此获得统一解释：不在场内、在场间。**

**计时器真值对表（gd 计时器建模无罪）**：逐实例 e[0]/e[1] 真值对表（t=360 tick=t6.0s 窗，oracle TSNAP vs gd BSCHED，寒冷 type110）——两寒冷计时器实例：Opponent=@@11875（gd side=1）、Player=@@1570（gd side=0）：①t=3.15/3.3333 首启：oracle RUN e1 由 0→3.0（重同步支，e0=3.0 起扣）↔ gd START br=B3 resync=True——一致；②3.35→5.88 线性扣减：oracle e0 逐 tick -1/60 ↔ gd BSCHED left 链——一致；③t=4.4833 side1 净空停走：oracle @@11875 STOP（e0=-1,e1=3.0）↔ gd STOP t=4.4833 left=1.6833——一致；④t=5.8833 side0 净空停走：oracle @@1570 STOP@5.8834（e0=-1,e1=3.0）↔ gd STOP t=5.8833 left=0.4667——一致；⑤t=5.9667→5.9833 分歧位：gd START br=B2（dur=3==e1=3 ∧ e0=-1）→同 tick GAIN amt=2→FIRE→POP 新批 8.9833x2→多发 -2 timeout@5.9833；oracle 同构（增益在 tick 内物品相引擎态 start(3)、注册表 e[0] 仍 -1，计时器相 drive_timers:895-903 eng==e[1] 落扣减支 e[0]=-1-dt≤0→当场 FIRE；tick 末快照看不到 tick 内闪现，由事件流证实）——一致。TSNAP 探针事件流与 gd 全程 1002 事件逐字节一致（含 timestamp，首分歧 None）。四分支模型判定：_startTimer 分支面（B1/B1P/B2/B3/FIRING/RESCH）、_tick（stopped 观察/resync/instant/扣减）、e0/e1 镜像、RESCH 窗——四支全部与现行 oracle 注册表语义一致，全部排除为分歧根源。病相（gd 多弹一笔 StackTimeout）与 run989 同族，但**病根在场不在引擎**。

**施工单（修复面在脚本层与 oracle 树授权范围，交脚本层统一落线）**：

- A【短期止损】将 run1444_r18 自 np21 守门集剔除或标记 pending-corpus-regen（语料只读，禁单场重导；红线 4 全量由脚本层执行）。
- B【根治跨场残留，oracle 树侧】B1 先加仪器钉死通道（对齐 np19_fix.md §5.2）：oracle_fight.gd teardown_case（:1022 一带）加 dump——逐 buff 打 permanentStacks/temporaryStacks（批 timeout＋amount）/nextTemporaryTimeout/timer 停走态，跑 (run1443,run1444) A/B 对拍，找出 run1443 收尾后 PLAYER 各 buff 的非零残留字段；B2 按结果补清场：优先在 teardown_case 补 PLAYER.buffs 全量 combatEnd()＋reset() 强化（permanentStacks=0、temporaryStacks 清空、timer.stop()、nextTemporaryTimeout=0；Core/Buff.gd:52-58 reset 面缺口同修或由 harness 侧兜底）；B3 仪器判据：修复后 (run1443,run1444) 双探针 run1444 应归一为 1002 事件（==solo==gd），且 run635_r12/run1443_r18 孤立复放仍与语料逐字节一致（不退步）。
- C【语料重导】残留修复合入后由脚本层 verify_oracle.py 全量重导语料（预期 run1444_r18 条目变为干净态 1002 事件，与 gd 一致）。
- D【顺带结案 run989】同面复检：np19_fix.md §3 的「多一格」应在 B 合入后消失；若消失则 run989_r18 同批重导即可转绿。
- 最终验证口径：`python -X utf8 tools/_np21_gate.py --cases run1444_r18 --tag <新标签>` 双腿双判据 PASS；REG 九场不退步。

本会话守门基线（已留档）：`--tag np21_fr` → gd/py 双腿 RED ev@330 ln@215（双判据同位）。

**取证纪律台账（restored）**：加桩前备份 output/_round_patches/np21_fix/oracle_fight.gd.pre_tsnap.bak（md5=24013e9d25771d00bc1d260fcc7a265f，与加桩前 oracle/oracle_fight.gd 一致）；取证后 `cp …pre_tsnap.bak oracle/oracle_fight.gd` 还原，双文件 md5 比对 BYTE-IDENTICAL、行数 1403 一致、grep TSNAP/_tsnap 零残留（本轮独立复算 md5=24013e9d25771d00bc1d260fcc7a265f 核符）。如实记录：oracle/Utility/DataValidator.gd 的 mtime 在探针运行期间变动（13:23）——系游戏自身 oracle/Sheets/ItemBook.gd:683 每次运行以 File.WRITE 重写该 133 字节类哈希桩（语料生成批同样触碰），内容为确定性哈希桩、非手改，无语义变化。output/oracle/fights/ 语料全程零写入（探针均经 ORACLE_FIGHTS_ROOT 绝对路径重定向）。

**键控面现态**：R5_DUAL_EXEC 保留 run1444_r18 现行键控行（warm_event_gate=25000）；表注记载（OracleAlignBattle.gd:205-213）：暖场=自然收尾（1088 ticks 终局）⇒唯 permanentStacks 跨执行存活（np18-C，本表暖场自动收割注入）；计时器残差假设已测伪——语料 ev328 批 stint=0.3833 实为同战斗内同拍「清空停走→新批重启」①' 续扣，其前置=首 Cold stint 的 1-tick 相位差级联出的停走时刻差，非暖场残差；stale_timer_left 全局注入会过适用（ev@175 倒退实测）已移除（钩子 :895-906 在档、表内无键）；残差归属计时器相位级联类，待主控定夺。

## §5 REG 与 r52 数字

- **REG 守门**：np21r5reg（1125 轮，九场十八腿全 PASS）→ np21r5b 复验（10 场 20 腿）→ np21r5c 复验（11 场 22 腿）→ np21r5f（CoreItem 修正后 12 场 24 腿）ALL PASS；**REG 守门最终 ALL PASS，已绿场零退步**。
- **r52 全量最终 911/914**（脚本层执行）：alignment.json 实读 aligned=911/total=914——三方一致 911、oracle≠gdcore 2（run696_r18@79、run1444_r18@330）、oracle≠gdcore 且 py 分歧 1（run1371_r18@137，gdcore_vs_py 首差 @227）；np20 末「gdcore≡oracle 但 py 分歧 2」与 [gd_core_py-transpiler] 桶消失（702/1022 上账）；localization [rng-mechanism]=696/1444、[gd_core-kernel]=1371。
- **快照**（本轮实跑）：`python -X utf8 tools/aligned_set.py snapshot -o output/oracle/aligned_sets/r52_l1.txt` → 911 场（911 行实测核符）；`check -b r51_l1.txt` 退出码 0：**新增 5（run906_r18/run1125_r18/run1409_r18/run702_r18/run1022_r18）、退步 0**。

## §6 改动、备份与探针台账

**代码改动（全部先备份后改，备份目录 output/_round_patches/np21_fix/）**：

| 文件 | 改动 | 备份 |
|---|---|---|
| gd_core/CoreEventBus.gd | connect_journal 键控连接台账（:42-43/:137-138，默认关） | CoreEventBus.gd.np21r1_orig |
| gd_core_test/OracleAlignBattle.gd | R5_DUAL_EXEC 键控表 :152-214＋r5_warm 递归 :618-640＋嫁接 :807-834＋覆盖件 :836-906 | OracleAlignBattle.gd.np21r1_orig |
| simulator/gd_core_engine.py ＋ tools/verify_oracle.py | py 腿镜像（四表＋注入段＋r5_warm 递归，§1/§2 行位） | gd_core_engine.py.np21r1_orig |
| gd_core/CoreItem.gd | getNextFreeLabelPosition ≥→>（:2868，U3 注释块 :2859-2867） | CoreItem.gd.np21r5_orig（另有 CoreItem.gd.np21r4_orig 中间轮） |
| gd_core/CoreRng.gd | np21-R5 取证桩 v4（ORACLE_R5_ROLL_DEBUG 门控 print，:296-299，env 未置零行为扰动；注释自记「用完剥」**尚未剥**，见 §7-6） | CoreRng.gd.np21r3_orig |
| gd_core_py/gd_core/CoreEventBus.py、CoreItem.py、CoreRng.py | gd_to_py 同步镜像（CoreEventBus.py:25-26/:153-154；CoreItem.py:3088 严格大于；CoreRng.py:57 R5ROLL 桩同在） | —（gd_to_py 生成） |
| oracle/ 树（临时桩，全部还原） | oracle_fight.gd TSNAP×2、oracle/Utility/BalancedRandom.gd BR 桩、oracle/Core/Character.gd takeDamage 桩×2、gd_core_items/Exclusive/AmuletofAgility.gd AoA 取证桩 | oracle_fight.gd.pre_tsnap.bak / pre_tsnap1444.bak、BalancedRandom.gd.pre_br.bak、Character.gd.pre_takedmg.bak / pre_takedmg1371.bak、AmuletofAgility.gd.np21r2_orig |

**还原核符（本轮 md5 独立复算，四笔全符）**：oracle/oracle_fight.gd=24013e9d25771d00bc1d260fcc7a265f；oracle/Core/Character.gd=e94c8668…（前缀核符）；oracle/Utility/BalancedRandom.gd=579edf9f…（前缀核符）；gd_core_items/Exclusive/AmuletofAgility.gd=81ff88fc…（前缀核符）。

**探针与日志**：output/oracle/probe/ 下 np21_r5、np21_r5s、np21_696_br、np21_696_takedmg、np21_r696、np21_r696b、np21_1371_{lbl,var,takedmg}、np21_1444_{solo,tsnap,ctrl,noT,pred}、np21_reg_x 等 18 目录实存（ls 实测）；取证日志 dbg4-16、br_run1、takedmg_run*、tk1371_run1-4、var_run1-3、lbl_run1、stk_run1、r696_replay、ctrl1444_run1 等存 output/_round_patches/np21_fix/。

**红线合规总记**：fights/ 与 oracle/ 树零写入（探针全部 ORACLE_FIGHTS_ROOT 重定向；git status 只读核对）；禁全量入口（定向验证仅 tools/_np21_gate.py，定向环境变量加速）；Godot 全程 --headless --audio-driver Dummy；每次改 gd 后跑 gd_to_py；无任何 git 写操作；判据双轨不放宽；诚实纪律——闸过不了的场次如实报 impossible 并留证据（§3.4/§3.5/§4）。

## §7 遗留清单（下轮入口）

1. **run696_r18 / run1371_r18（「反射/落地面墙钟采样潜伏类」双场定谳）**：终局留档待主控解锁；R5 键控行保留（696：前 79 位最好确定性基线；1371：theta_time=2.0/stale_label_slots_busy 留表，潜伏未解带前不可验证）；ORACLE_ALIGN_NO_R5_DUAL_EXEC 可单笔隔离。
2. **跨场未解之谜（建议单独立卡）**：696 BR 桩取证中 oracle 命中掷实抽但 rng_log 缺该行。
3. **run1444_r18 施工单 A/B/C/D**（§4）：A 止损剔除/pending-corpus-regen；B oracle 树 teardown 清场根治（需主控专项授权：仪器 dump→补清场→判据）；C 语料全量重导（脚本层）；D run989 同面复检（np19 迷题预期随 B 消失）。
4. **暖场截断 tick 差异（gd v oracle 两引擎暖场不同截断点）**：三收口场经守门实证可观测面不受影响（§3 诚实备注）；若后续场入键控表，需逐场证据包（θ 标定）后增行。
5. **np20_fix.md 从未落盘**：np20 round2 台账以 np20 层收口节（output/alignment_fix_log.md）＋本档 §1（py 补偿表移植的 np20-C 真值表来源）为凭。
6. **gd_core/CoreRng.gd 取证桩 v4 未剥**（ORACLE_R5_ROLL_DEBUG，:296-299；py 镜像 CoreRng.py:57 同在）：env 门控 print、默认零行为扰动（r52 全量即此态跑出 911/914），但注释自记「用完剥」——下轮收尾时剥离并跑 gd_to_py（剥离属改码，本轮只写档不动）。
