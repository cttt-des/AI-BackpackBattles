# np5_K1 — 内核面三补丁落地（① PINE 延长支 instant 清除；③ ORD1 autoRage/棋子音高恢复；② MF 证伪不改）

日期：2026-10-18。卡片：修复·内核面三补丁。
结论：**patched（①③ 已改码待脚本验证；② 经一手证据复核证伪 np4_MF 两假说，不改码）**。
备份：output/_round_patches/np5_K1/{gd_core/CoreCharacter.gd, gd_core_items/Exclusive/Chess/ChessPiece.gd}
（改前原样，diff 已核验补丁精确落地）。

## 1. 补丁① — CoreCharacter.gd makeInvulnerable 延长支补 `_invul_instant = false`

- 落点：`gd_core/CoreCharacter.gd` 延长支（原 :1484-1488，改后 :1484-1494），在
  `_invul_resync = true` 之后补一行 `_invul_instant = false`。
- 机理（np4_PINE.md 证据链，本轮逐行复核成立）：首次授予支（:1481）按 run634 修复
  `_invul_instant = _invul_fired and is_equal_approx(invuDur, _invul_last_dur)`；同帧
  Goobert start(1.5) → Frog Prince makeInvulnerable(2.5) 走延长支时该残留不清理，
  驱动块（改后 :2115-2123）同帧 resync 支见 instant → `_invul_left = 0` → 幻影
  InvulnerableEnd（run921_r18 id304 @6.116667 与 Start 同 tick；语料玩家侧 End 在
  id537 @10.133333 = 4.0s 重同步倒计时精确值）。
- oracle 语义核对：延长支 = Util.changeTimer = start(t+timeLeft)（oracle/Utility/Util.gd
  :1671-1677），引擎读数被重写为新和值 ≠ 残留 e[1] → drive_timers（oracle/oracle_fight.gd
  :896-901）走重同步支 `e[0]=eng`，结构上不可能同帧到期；oracle/Core/Character.gd
  :1039-1059 发火即 `invulnerable=false`，changeTimer 支只在计时器仍走时可达。清除恒为
  对齐；run634 锚点走首授予支不受影响。

## 2. 补丁③ — np4_ORD1 两笔恢复（r2 已验消除 run947_r10 idx6 分歧）

np4_ORD1 备份与改前现场 diff 为空（np4 回滚后无人再动），按笔记重放：

- `gd_core/CoreCharacter.gd` prepare() autoRage 选品（原 :354）：
  `ctx.rng.pickRandomElement(battleRageItems)` →
  `ctx.rng.pickRandomEngine(battleRageItems, "Core/Character.gd:326")`。
  真源 decompiled_full/Core/Character.gd:326 = `battleRageItems.pick_random()`（引擎全局
  链，不进 Util.rng 日志）；run947 每侧恰 1 元素 ⇒ 旧码每侧多耗 1 抽 ⇒ 抖动值→物品指派
  整体前移 ⇒ RainbowPotion 六连选型分歧。pickRandomEngine 未开账路径直通
  `Array.pick_random()`（gd_core/CoreRng.gd:235）。
- `gd_core_items/Exclusive/Chess/ChessPiece.gd` onPieceCaptured 捕获音高（原 :66）：
  `randf_range(0.9,1.1)` → `randf_range(0.95,1.05)`（oracle Util.randPitch() 默认
  variation=0.05，oracle/Utility/Util.gd:685-686；run947 逐抽 343 假分歧消歧，只改映射
  不改笔数）。
- 回归面（本轮实扫 gd_core_test/oracle_align_cases.json）：REG 九场无任何 Chess/* 棋子
  （run635/run695 的 "Dragon Knight" 非棋族，仅同名含 Knight）；rage 物品（run570
  Toolbox、run635 Wolf Badge）带 BattleRage 标签 ⇒ autoRage 选品不触发 ⇒ 两笔零回归面。

## 3. 补丁② — 证伪 np4_MF，不改码（clean，留档）

### 3.1 np4_MF 的证据基座是 np3c 旧码产物

np3c trace（output/oracle/align/np3c/run977_r18/rng_trace.txt :1309-:1356/:4220）内部的
B1P 同帧重启 + left 账面回弹（4.65→4.8，中间无 START 行）与 left>4.8 才可能触发的
RESCH 行，均与现行 CoreBuff.gd 逐行对不上：现行 `_stopTimer` 只停走、保留 `_timer_left`
（b3_fix1，:587-600）；RESCH 判据 `duration < _timer_left`（:250）下同 dur 重施加恒
KEEP（dur==last_dur≥live left ⇒ 判据恒假）⇒ np3c 期"杀 grace 的 B1P 重启"在现行码
**结构上不可达**，side0 幻影准点弹（7.716667）不会重现。

### 3.2 oracle 真源是 harness 补丁版：RESCH 判据 = 注册表活剩余

diff oracle/Core/Buff.gd vs decompiled_full/Core/Buff.gd：oracle :164-171 被打桩——

```
var timerLeft = timer.get_time_left()          # 引擎读数（阻塞循环里冻结=wait_time）
var oracleLeft = Util.oracleTimeLeft(timer)    # drive_timers 注册表 e[0]（活剩余）
if oracleLeft >= 0.0: timerLeft = oracleLeft
if duration < timerLeft: timer.stop(); timer.start(duration); next=…-1
```

Util.oracleTimeLeft（oracle/Utility/Util.gd:807-810）= oracleTimerLefts[timer][0] =
oracle_fight.gd:881 注册表剩余、:984-987 新节点登记 [left,left]、:972-976 开战重建。
即 **oracle 的 RESCH 判据 = 活剩余**，与 gd 现行 `duration < _timer_left`（:250）**同构**，
而非冻结 wait_time（np4_MF §3 的猜测方向之一被排除）。

### 3.3 新计时器 grace：两侧一致（+1 tick 语义的真正来源）

Buff 的 Timer 在 buff 构造时创建且从未 start（decompiled_full/Core/Buff.gd:32-36）⇒
注册表登记 [0,0]；之后 start(4.8) 不改注册表 ⇒ 首 drive 遍 eng(4.8) ≠ e[1](0) →
**重同步支（grace 帧，不扣）** ⇒ 到期 = 施加帧 + dur + 1 tick。gd 侧 ③ 分支 resync 帧
不扣（CoreBuff.gd:613-618）逐点等价。实证：side1 首挂（B3）双方同拍（语料 ev487 @7.566667
= gd fire :4012 同值）；np4_MF 所谓"oracle 恒 +1 tick"即此 grace，gd 本就有。

### 3.4 施加序与弹批序

- oracle rng_log（GBK，全局钟 41.383 起）rows 813-835 @44.300：LG+7 的标签 2 抽 +
  EVENT 109 在前，MrS+8 的在后——**同帧、LG 先**；且双方 events ev0..516 全同 ⇒ 施加序
  一致，批数组 = [LG7, MrS8, LG8, MrS9, LG10, LG9]（6 批全部有事件，无隐形批）。
- 语料弹批序 side0 = [MrS -8 (ev524), LG -7 (ev525)]：按指针模型需 pointer=1，而
  RESCH 在上述判据下对同 dur 恒假，静态分析无法从源码推出 pointer=1 的成因（此点
  源码级未解，留待 Godot 对跑）。但 gd 与 oracle 的指针演化逻辑逐行同构
  （IDLE→0 / RESCH→size-1 / KEEP 不动 / onTimeout 重选最早：gd :248/:254/:432-461 ≡
  oracle Buff.gd :162/:167/:332-349），**相同输入必得相同弹批序**——该未解机制两侧共有，
  不构成 gd 侧缺陷，也不在本卡文件面。
- 语料 rng_log :917/:918、:982-983 亦可见 randPitch(0.9,1.1) 与 randPitch(0.95,1.05)
  两族并存，佐证补丁③的域修正方向。

### 3.5 两假说逐条证伪

- 假说 A（①' 改 resync=true，:561-568）：违背 drive_timers 真值——同帧 stop+start 同
  dur 时 eng==e[1] → `e[0]-=dt` 残留续扣、**无重同步帧**（oracle_fight.gd:896-901）。
  r31 当年回退方向正确；np5 若再翻上等于给 oracle 没有的 grace。
- 假说 B（fire 判改"过零后下一遍"，统一 +1）：违背停走观察支（drive_timers:890-892
  `e[0]=-1` → 残留 -1 起扣当遍 fire）与 run688_r10 ② 锚点、run634 idx450/540 ③ 锚点。
- 结论：现行 gd 四分支模型与 drive_timers 在 ①/①'/②/③/FIRING 各支逐点等价；
  **run977 的到期相位缺陷在现行码已不存在**，② 无需改码。预期脚本重跑 run977_r18 时
  ev517 的相位差（7.716667 vs 7.733333）消失；若该场仍红，剩余候选即 §3.4 弹批序
  未解机制（需真 Godot 对跑，非本卡可闭合）。

## 4. 本卡动作与移交

- 改码：仅 §1/§2 两文件（备份见文件头）；CoreBuff.gd、OracleAlignBattle.gd、assets、
  gen 工具一概未动；未跑 Godot、未跑 gd_to_py.py、未触语料/oracle 目录写面、未动 git。
- 可选第 4 项（DATA1 harness item_trace 写入口径）未做——诊断债不阻塞，留后续卡。
- 主线已修事实未回退：CoreUtil.callNextFrame / RubyChonk 3 抽 / PerpetuumMobile
  canAffect 内联均不在本轮触碰面。
- 验证锚点（脚本统一执行）：REG 九场绿 = 全保留；run921_r18 预期由 ① 转绿；
  run947_r10 idx6 + 逐抽 343 由 ③ 消除（棋盘捕子残点 puzzlebag×filledCells 仍留档）；
  run977_r18 预期相位差消失（② 分析），若仅剩弹批序差异按 §3.4 移交。
