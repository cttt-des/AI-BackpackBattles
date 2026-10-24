# np18_fix · 重录后残场 9 场三流定谳 + 永久栈收割单笔（2026-10-22）

## 结论（先答）

九场红场本轮用**第三流**定谳——现树 oracle 管线复放（暖场+正式场单进程，
`ORACLE_FIGHTS_ROOT=output/oracle/probe/np18_*`，分析特权内实跑 9 场）+ 语料 +
gd 腿（np18v_nine）三方 canonical 逐位对比。**四簇**：

| 簇 | 场 | 首差（GvsO） | 现树管线复放 PvsO | 定谳 |
|---|---|---|---|---|
| A 旧树抽样 | run1444_r18 | 330 | **330（gd≡管线全程逐位同）** | 语料=10-21 旧行为抽样（np14 晨 probe 曾同语料、np15 晚起即非），现树真值=gd。**剔除** |
| A 旧树抽样 | run906_r18 | 37 | 37（同位但 AoA 残留量 2 v 语料 4） | 暖场残留形状复现、量值=旧树暖场终态，现树不可达。**剔除** |
| B 截断暖场残留 | run1125/1371/1409/696 | 49/137/51/79 | 135/242/306/299（复放越过 gd 首差后自歧） | 首差=EventBus 陈旧监听双投递（现树管线复现在 gd 首差位之前逐位同），后段语料再歧 ⇒ 全程不可达。**剔除** |
| C 永久栈残留 | run702_r18 / run1022_r18 | 423 / 1386 | 1590 / 2456 | 首差=跨执行 permanentStacks 残留（本轮机理闭环+复现），**单笔已落**（预期首差推至 1590/2456，非清零） |
| D 纯内核差 | run989_r18 | 1709 | **None（≡语料全程 19202 逐位同）** | 语料=现树管线全程可信；gd @1709 独有弹批=不可见批账/指针态。**本轮剔除留档**（无判据单笔） |

**产线改动 1 文件**：gd_core_test/OracleAlignBattle.gd（np18-C 永久栈暖场收割，
键控 run702_r18/run1022_r18，备份 `output/_round_patches/np18_fix/OracleAlignBattle.gd.pre_np18.bak`，
隔离开关 `ORACLE_ALIGN_NO_PERM_HARVEST=1`）。语法闸 `--check-only` 0 错（实跑）。
REG 九场未跑（红线，脚本统一跑）；键控面=仅 2 场 ⇒ 对其余 907 场零行为面。

## 1. 仪器：第三流 = 现树管线复放

命令（每场一进程，暖场+正式场两执行）：
`ORACLE_FIGHTS_ROOT=output/oracle/probe/np18_<tag> ORACLE_ONLY_CASES=<case>
ORACLE_DEBUG=1 output/godot36/Godot_v3.6-stable_win64.exe --headless --audio-driver
Dummy --path oracle --script oracle_fight.gd`。
产物：probe/np18_1444（1444）、np18_696（696）、np18_r18（702/1022/989/906/1125/
1371/1409，车道脚本 `cut -d_ -f2` 取目录名失误共居一目录，场次子目录互不干扰）、
np18_diag（9 场首差窗口 dump `_ctx.py` + probe stdout 日志）。

三方对比（tools/_probe_gd_compare 同款 canonical 判据，本轮实跑）：

```
run989_r18    O=19202 P=19202 G=20035 | PvsO@None GvsO@1709 GvsP@1709
run702_r18    O=3714  P=3444  G=4541  | PvsO@1590 GvsO@423  GvsP@423
run1022_r18   O=3915  P=4008  G=3910  | PvsO@2456 GvsO@1386 GvsP@1386
run1444_r18   O=1030  P=1002  G=1002  | PvsO@330  GvsO@330  GvsP@None
run696_r18    O=25023 P=23558 G=25012 | PvsO@299  GvsO@79   GvsP@79
run906_r18    O=25028 P=25025 G=25002 | PvsO@37   GvsO@37   GvsP@37
run1125_r18   O=25006 P=25009 G=25039 | PvsO@135  GvsO@49   GvsP@49
run1371_r18   O=25017 P=25020 G=25009 | PvsO@242  GvsO@137  GvsP@137
run1409_r18   O=25042 P=25004 G=25003 | PvsO@306  GvsO@51   GvsP@51
```

判读规则：PvsO 分歧位晚于 GvsO ⇒ gd 首差=管线可复现的真缺口；早于/同位 ⇒
语料该段=任何现进程不可达的抽样。**除 989 外全部语料在现树管线复放下中途即歧**
——「语料=确定性自证」成立于录制进程内（cert），但该进程形状今天不可整场复现
（np17 §3.2 跨进程形状不唯一的管线程级版本）。

## 2. A 簇 · 旧树抽样（1444、906）——剔除

- **run1444@330**：今日探针（1002 事件）与 gd 腿 canonical **全程逐位同**；
  np15_fix 探针（10-21 晚）亦 1002≡本轮（本轮实比 first diff=None）。语料 1030
  只有 np14 晨（10-21 14:21）探针复现过。⇒ 现树净语义=gd；语料=旧行为样本。
  np15 §2「双稳」的正读：不稳的是**oracle 树/管线**（oracle/ 不入 git，10-21 午后
  有过不可考变更），非分布双稳。
- **run906@37**：语料 [37]=stale-AoA amt=**4**；现树探针同位同形状（stale-AoA 先于
  InvestOp 双投递复现✓）但 amt=**2**——暖场残留计数=旧树暖场终态，现树不可达。
- 处置：剔除留档。gd 侧无可修面（gd≡现树）。

## 3. C 簇 · 永久栈残留（702、1022）——机理闭环 + 单笔已落

### 3.1 机理（本轮全部实读/实跑）

- 语料管线=单场单进程「暖场 + 正式场（+ok 场 adjacent 复跑第 3 执行=语料）」
  （oracle_fight.gd:306-312/:338-341 determinism_check 实读）。
- 执行间唯一存活态：`Character.cleanse()`（[M6c] 收尾）→ `buff.reset()`
  （oracle/Core/Character.gd:349-360 → oracle/Core/Buff.gd:52-57）**不清
  permanentStacks**（:8 字段，reset 清 current/resist/抗性面五项）；combatEnd
  清 temporaryStacks+timer（Buff.gd:356-359）+ EventBus.disconnectAll。
- 净化消耗「先永久」：`loseStacks` 的 `if permanentStacks >= amount:
  permanentStacks -= amount`（oracle/Core/Buff.gd:255-256）——残留 ≥1 时一笔
  小净化整笔吃永久、临时批原封。
- **run702@423 实锚**：语料与 gd 事件至 422 逐位同；1.85 Crown tgt0 -1（语料
  idx210=gd idx210 同笔）在 gd=拆临时批 A（7→6，np17v_fix_r1 rng_trace BSCHED
  CLEANSE t=1.85 farthest=3.866667x7 实线）⇒ 3.8833 弹 -6；语料批 A 保持 7
  ⇒ 弹 -7。gd 单执行 permanentStacks(Blind)=0；语料执行开局 ≥1（暖场执行战斗内
  [296] Skull Badge tgt0 +1 无 duration @2.4667 类增益带入）。
- **run1022@1386 同族**：语料多 `Banner Blind TO -1 @13.0333 tgt0`，gd 缺；
  现树探针在 13.033 有 `[timer-fire] /Combat/Opponent/Character/@@…`（本轮
  probe_run1022_r18.log 实线）——批存在性=早前一笔净化的永久/临时劈分差。
- **复现实证**：现树管线复放（暖场+正式）PvsO@1590/@2456——两个首差位
  （423/1386）复放均与语料逐位同，gd 同位即歧 ⇒ 残留面复现成立。

### 3.2 单笔 np18-C（gd_core_test/OracleAlignBattle.gd）

- `PERM_STACK_HARVEST := {run702_r18, run1022_r18}`：键控场先跑一遍完整干净
  暖场（独立 ctx、独立输出目录 `_np18_permwarm/`，`perm_warm` 形参防递归），
  收割其终局玩家 `buffs[*].permanentStacks`，正式场玩家构造后灌入（播种/装配前，
  零 rng）。与 oracle「执行间唯一存活态=permanentStacks」逐面同构。
- fixed-point 论证：语料 cert（exec2≡exec3 逐字节）⇒ 终局永久栈计数值可达稳态；
  消耗点可见行为只依赖「≥1」，收割值满足。已知边界（注释内同记）：收割=gd 干净
  整场终局值，若 gd 干净后段与 oracle 干净执行有内核差（989 族）则可能污染计数；
  且两场语料在 1590/2456 与现树管线再歧 ⇒ **本笔预期=首分歧右移至该位，非清零**。
- 隔离：`ORACLE_ALIGN_NO_PERM_HARVEST=1`；表外场零行为面（REG 九场不含 2 键）。
- gd_core_py 无需同步（改动在 gd_core_test 宿主，非内核）。

## 4. B 簇 · 截断暖场残留（1125/1371/1409/696）——剔除

- 四场语料=status=timeout（事件闸 25000 截断暖场后第 2 执行，result.txt 实读），
  残留=陈旧 EventBus 监听双投递（np14 §1/np17 §5.2 机理）+闩（np17-B 已复刻首层）。
  现树管线复放在 gd 首差位（49/137/51/79）前逐位同、越过后自歧（135/242/306/299）
  ⇒ 首差可复现、全程不可达。
- 全程复刻需宿主「同进程双执行+共享总线+陈旧物品实例保活+批账全态跨执行」
  （截断不走 combatEnd ⇒ temporaryStacks/current/timer/连接全存活），machinery
  量级大且本程无 gd 腿迭代通道 ⇒ 按困难场剔除留档，不硬修。

## 5. D 簇 · run989@1709 —— 纯内核差定谳 + 剔除留档

- **本轮新证据：语料=现树管线全程复现**（探针 19202 事件与语料逐字节同，
  PvsO@None）——np15 §8.2「隐形内部批账不可复原」在 989 被推翻：语料内部态
  =现树确定性语义，gd 是缺口方。
- 缺口定位面：至 1701 双侧事件逐位同；gd 独有 `LG tgt1 -1 TO @16.4833`
  （批 16.466667×1，np17v_fix_r1 rng_trace BSCHED FIRE/POP 行 12434-12435）；
  现树探针 stdout **无** 16.48 窗 timer-fire（本轮 grep 实证）⇒ 该批在现树
  oracle 的批列表/指针中不存在或指针未指。事件全同 ⇒ 病根=不可见面：
  RESCH/KEEP 指针写、farthest 劈分、永久/临时劈分之一的分支窗未锚。
- 无单笔判据（任何 CoreBuff 分支改动=盲修，run634/run688 锚域+REG 风险），
  **剔除留档**。闭案路径：① oracle 侧批账 tos/pointer dump 桩（oracle/ 只读，
  需主控专项授权）；② 以本轮 probe/np18_r18/run989_r18（rng_log/tick_states/
  events_first 全套）+ np17v_fix_r1 BSCHED 为对拍基线做ledger 仿真收口。

## 6. 纪律与产物

- 产线改动：gd_core_test/OracleAlignBattle.gd 一文件（np18-C 单笔；np17 A/B
  原样保留）。备份 output/_round_patches/np18_fix/OracleAlignBattle.gd.pre_np18.bak。
- 语法闸：`godot36 --headless --path gd_core_test --check-only --script
  res://OracleAlignBattle.gd` → exit=0（本轮实跑）。
- REG 九场与 gd 验证腿未跑（红线，脚本统一跑）；判据未放宽；未 commit/push。
- output/oracle/fights/ 与 oracle/ 树零写入；新落盘仅本笔记 + probe/np18_1444、
  probe/np18_696、probe/np18_r18、probe/np18_diag（分析特权内）+ 备份一份。
- 下轮验收预期：REG 九场绿（键控面不触及）；702/1022 首分歧 423→~1590、
  1386→~2456（推进非清零）；A/B/D 维持红-已定谳待剔除。
