# np6_B1 —— run977_r18 残分歧定谳：CoreBuff ①' 支缺「e[1] 已观测」判据，同帧 RESCH 重启丢 grace 帧

日期：2026-10-19。卡片：修复·CoreBuff批内容（阶段1分析 → 阶段2已落地改码）。
结论：**patched（已改码，待脚本跑 REG+目标场终审）**。备份：
`output/_round_patches/np6_B1/gd_core/CoreBuff.gd`（改前原样，md5
5566899908cd28b6dff954552eb3feef 与改前工作树一致；diff 备份↔现文件=恰好 §5 四处）。
阶段1结论：根因钉到 `gd_core/CoreBuff.gd:561-569`（①' 支无重同步推断），
REG 回归面实测为零（§6）。**

## 1. 分歧现状（np5v_final 现行码复测）

- 工具：python 逐事件比对 `output/oracle/fights/run977_r18/events.json`（语料，6366 条）vs
  `output/oracle/align/np5v_final/run977_r18/events.json`（gd，5316 条），归一
  （去 type_name、GemSocket2→GemSocket）。首歧 **idx517**：
  - 语料 ev517-521 @7.716667 = Miss Fortune -1 / Toad ×2 / MF resisted / MF 0（纯物品相）；
  - gd ev517/518 @7.716667 = **MrS -8 timeout + LG -7 timeout（盲批早弹一拍）**，MF/Toad 被
    挤到 ev519-524；剩余 MrS -8 ×2 @7.733333（ev525/526）。
  - 语料全批 {MrS -8 ×3, LG -7} 弹在 **7.733333**（ev522-525；target=1 两批在前、
    target=0 两批在后）。
- 即 np5_K1 §3.5 的预期「相位差已在现行码消失」**被证伪**：②/③ 锚点路径没问题，
  偏差藏在第四条路——①'（B1P）支。

## 2. gd 侧批内容取证（BSCHED/LGPROC/LGDEC 现行桩，np5v_final trace）

side0 盲栈（type=109，Player 方）t=2.916667 同帧三连：

```
:1308 START t=2.916667 side=0 dur=4.8 br=B3  resync=True  pre act=F left=-1   ← LG +7 首挂（IDLE/③）
:1309 GAIN  amt=7  br=IDLE  n=1  act=T left=4.8
:1329 GAIN  amt=8  br=KEEP  n=2  act=T left=4.65              ← side1 的 buff（GAIN 行无 side；left=4.65=side1 自 2.75 起已扣 9 帧）
:1353 STOP  pre act=T left=4.8                                ← 下两行+本行 = RESCH 三连（stop→start→gain 打印序）
:1354 START t=2.916667 side=0 dur=4.8 br=B1P resync=True(pre) pre act=F left=4.8   ← ★ 误判点
:1355 GAIN  amt=8  br=RESCH next=1 n=2  act=T left=4.8
:1376 GAIN  amt=8  br=KEEP  n=3  act=T left=4.65              ← 再回 side1
:1390 LGDEC t=2.916667 blindP=14 blindT=[7@7.716667,8@7.716667] blindC=29
```

- 批内容定谳：side0 = [LG 7@7.716667, MrS 8@7.716667]（blindP=14 永久层为 MrS 反击永久盲，
  临时批共 2 个）；side1 = [7@7.55, 8, 8]。**批内容与语料完全一致，无缺批/多批。**
- RESCH 判定本身两侧一致为真：gd `duration(4.8 double=4.79999999999999982) <
  _timer_left(f32(4.8)=4.800000190734863)`（CoreBuff.gd:250）恒真；oracle
  `oracle/Core/Buff.gd:163-171` 同帧注册表 e[0]=-1（停走遍所写）→ 回退引擎冻结读数
  = f32(4.8) → 同判真。**两侧都走 RESCH（stop;start;next=size-1）→ 弹批序 MrS 先
  （next=1）与语料 ev524→ev525 一致。RESCH 无罪。**
- 罪在 RESCH 重启之后的第一遍：gd :1354 落 **①'（B1P）** 支 → `_timer_resync=false`
  （CoreBuff.gd:567）→ 起始帧即扣 → 289 次扣减后于 **7.716667** 过零
  （:4219 FIRE left=-0.016666，= 4.80000019 − 289/60）。

## 3. oracle 侧仪器实证（本卡新跑 probe）

命令（分析期特权，产物只进 probe 目录）：

```
ORACLE_FIGHTS_ROOT="D:/文件资料/学习/自动背包AI/output/oracle/probe/np6_B1_b1_dbg" \
ORACLE_ONLY_CASES='run977_r18' ORACLE_DEBUG=1 \
./output/godot36/Godot_v3.6-stable_win64.exe --headless --audio-driver Dummy --path oracle --script oracle_fight.gd
```

stdout 关键行：

```
[bt-resync] t=2.8000 /root/Main/Combat/Opponent/Character/@@1797 eng=4.8000 old_e0=-1.0000 old_e1=0.0000   ← side1 首挂重同步
[bt-resync] t=2.9167 /root/Main/Player/Character/@@1569    eng=4.8000 old_e0=-1.0000 old_e1=0.0000   ← ★ side0 同帧 RESCH 重启后的第一遍
[timer-fire] t=7.733 @@1797   ← side1 第 2 批
[timer-fire] t=7.733 @@1569   ← side0 盲批（+1 帧）
```

**old_e1=0.0000 是决定性证据**：oracle 重同步判据 `eng != e[1]`（oracle_fight.gd:897-903）
里 e[1] 是「上一驱动遍读数」，停走遍只写 e[0]=-1（:884-886，e[1] 不动），同帧
start→RESCH stop+start 链上没有任何遍观测过 running stint → e[1] 仍是登记值 0 →
eng(4.8000)≠0 → **重同步支（grace 帧，e[0]=eng 不扣）** → 289 扣于第 290 遍过零 →
**7.733333**。gd ①' 支把「left≠-1 且同 dur」误当「eng==e[1]」，给了无重同步
（起始帧即扣）→ **7.716667**。恰差一物理帧。

辅证：

- `ORACLE_RNG_DEBUG=1` probe（np6_B1_b1_rng）注册序 dump：Opponent 块
  （TickTimer:4247 → Buff 计时器 @@1788-@@1797:4251-4260）整块先于 Player 块
  （@@1560-…:5362+，@@1569:5371）→ 同帧双 fire 弹批序 = side1 先 side0，
  与语料 ev522/523(target=1) → ev524/525(target=0) 一致；gd CoreCombat.gd:359
  `for character in [opponent, player]` 同序复刻 ✓。
- probe events.json vs 语料：**0..2562 全同**（目标窗内逐条相同）；
  2563+ 有 16 处 -9/-10 级差（t=18.77+，单场 probe 与批量语料的 PLAYER 过场态噪声，
  winner/ticks 相同）——不属本卡目标窗，留档主线复核。
- 该退出码 EXIT=1 为退出期 LocalizedControl 泄漏噪声，战斗产物完整。

## 4. 根因（真源 file:line）

- **缺陷**：`gd_core/CoreBuff.gd:561-569` —— ①' 支判据
  `not _timer_active and _timer_left != -1.0 and is_equal_approx(dur32, _timer_last_dur)`
  用 `_timer_last_dur`（start 时写）冒充 e[1]（驱动遍才写）。stint 未被任何遍观测时
  二者不等价 → 本应落 ③（resync grace）的同帧重启被误判为「原剩余续扣」。
- **oracle 真值**：`oracle/oracle_fight.gd:884-886`（停走遍 e[0]=-1、e[1] 不动）、
  `:897-903`（resync 判据 eng!=e[1]；e[1]=eng 每遍尾写）、`:910-912`（处理器内重启
  e[0]=e[1]=get_time_left()）、`:951-968/:979-983`（登记/重建 [left,left]，未驱动=0）；
  `oracle/Core/Buff.gd:157-171`（RESCH：e[0]≥0 用注册表，否则回退引擎冻结读数）。
- **触发链（本场）**：LGPROC blind=7（:1293）→ GAIN#1 IDLE/③ start(4.8)（:1308）→
  同帧 MrS onDebuffed +8 → RESCH（:1353-1355，两侧同判）→ gd ①' 无 grace 早一帧；
  oracle e[1]=0 → grace → 语料相位。
- 历史包袱澄清：r31 回退（B1P 全局 resync=true）与 np5 §3.5 假说 A 证伪都只覆盖
  「e[1]==dur32（stint 已被驱动过）」的 ①'——那一支 r31 方向正确、本补丁保留其语义；
  本案是同一分支标签下的**另一子态**（stint 从未驱动，e[1]=0），旧判据无法区分。

## 5. 补丁方案（全部在 gd_core/CoreBuff.gd，共 4 处）

1. **新增字段**（`_timer_last_dur` 声明旁）：
   ```
   # ★ np6_B1（run977_r18 ev517 定谳）：注册表 e[1] 复刻 = 上一「已驱动遍」观测到的
   #   引擎读数（frozen-engine 下 = 现行 stint 的 f32 wait）。停走遍不写
   #   （oracle_fight.gd:884-886 只写 e[0]=-1）；驱动遍尾写 e[1]=eng（:897-903）；
   #   处理器内重启支 e[0]=e[1]=读数（:910-912）。登记/重建为 [left,left]，
   #   从未驱动的 Buff 计时器恒 0。
   var _timer_e1: float = 0.0
   ```
2. **resetTimersSync（:491-497）**补重建对位：`if not _timer_active: _timer_last_dur=-1.0; _timer_e1=0.0`，
   `else: _timer_e1=_timer_last_dur`（引擎冻结读数=f32(现行 wait)，非剩余）。
3. **①' 支判据（:561-562）**加一合取：
   `and is_equal_approx(dur32, _timer_e1)` —— stint 已被驱动观测（e[1]==dur32，run688
   b3_fix1 锚点类）才走「原剩余续扣」；否则下落 ③（resync grace）。BSCHED 探针标签
   B1P（:541-543）同步加同一合取（print-only，保取证真值）。
4. **_tick 尾（:624-641 后）**加：
   ```
   if _timer_active:
       _timer_e1 = _timer_last_dur
   ```
   （未到点遍/重同步遍/②瞬弹遍/处理器内重启遍统一在遍尾观测现行 stint；停走遍走
   :607-612 早 return 不达此行 = oracle 停走遍不写 e[1]；fire 未重启遍 active=false
   不写 = oracle one-shot 尾 e[1] 保持本遍 eng。）

预期：GAIN#3 的 _startTimer 落 ③（BSCHED 标签 B1P→B3），side0 盲批 FIRE 由 7.716667
→ **7.733333**，弹批序仍 idx=1(MrS)→idx=0(LG)，事件与抽序回归语料锁步；side1 及全部
REARM/FIRING 路径零变化（e1 写入值与原隐含值恒等）。

## 6. 回归面实测（现行 np5v trace 全扫）

- REG 九场（np5v_内核面三补丁_reg1）：`grep -c "br=B1P"` = **全部 0**。
- np5v_final 六场：唯 run977_r18 一处 B1P（:1354，即本案）。
- ⇒ ①' 加密只影响「stint 从未驱动」子态，REG 现录 trace 触达为零，理论回归面=空；
  REG 重跑由脚本统一执行终审。

## 7. 本卡动作

- 阶段1：跑 probe ×2（np6_B1_b1_dbg / np6_B1_b1_rng，产物均在 output/oracle/probe/ 下）；
  python 只读比对语料/gd 事件与双侧 trace；未跑 Godot gd 侧、未跑 OracleAlignBattle、
  未跑 gd_to_py.py、未写语料/oracle 树、未动 git。
- 阶段2（落地）：先备份 `output/_round_patches/np6_B1/gd_core/CoreBuff.gd`（md5 同
  改前工作树），后按 §5 落 4 处补丁；`diff -u 备份 现文件` 复核 = 恰 4 处、无杂散；
  `_timer_e1` 引用 7 处全对位（:90 声明、:509/:513 重建、:560 探针、:581 ①'、:671
  遍尾），全文无空格缩进污染。运行期验证（REG 九场 + run977_r18）由脚本统一跑，
  本卡未跑。
- py 孪生（gd_core_py/gd_core/CoreBuff.py）随主线 gd_to_py.py 再生，不在本卡面。
