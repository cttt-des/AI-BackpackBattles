# np4_MF —— run977_r18 首分歧定位（MissFortune / MrStruggles 卡）

日期：2026-10-18。结论先行：**首分歧不在 MissFortune / MrStruggles 物品面，在 gd_core 内核
CoreBuff.gd 的临时栈计时器到期 tick 语义**（side=0 致盲批 gd 准点弹出，oracle 恒晚一拍）。
未改任何代码，无备份、无还原动作。

## 1. 分歧定位

工具（只读）：

```
python -X utf8 tools/_probe_draw_diff.py output/oracle/probe/np3_or4b/run977_r18/rng_log.txt output/oracle/align/np3c/run977_r18/rng_trace.txt 12
```

输出：oracle 数值抽 25637，gd 数值抽 20949（差 -4688）；首个分歧第 2244 抽（0 起）：

- O idx2244 = `rng_log.txt:2762` `randf_range 0.975 1.05 => 1.027993 @t=49.117`
  ——对手物品冷却扰动 roll（decompiled_full/Items/Item.gd:3805-3811，
  `ownerType == Owner.Opponent and below Master` 走 0.975 分支）。
- G idx2244 = `rng_trace.txt:4223` `randf 0 0 => 0.706574`（盲眼批弹出）。

两侧第 0..2243 抽（共 2244 抽）逐值逐区间全同 ⇒ 分歧前一切物品级触发时序与取值与神谕
完全锁步。

## 2. canonical 事件侧证

events.json（去 type_name、GemSocket2 字符串归一后逐条比）：

- ev0..ev516 全同；**ev517 首歧**：
  - O ev517：type 101，Miss Fortune 幸运 -1（used=true）@7.716667；
  - G ev517：type 109，Mr Struggles 致盲 -8（timeout=true）@7.716667。
- 同一批到期弹出的落点：
  - O：ev522/523/524（Mr Struggles -8 ×3）+ ev525（Light Goobert -7）全部 @**7.733333**；
  - G：ev517（MrS -8）+ ev518（LG -7）@**7.716667**，其余 MrS -8 ×2 @7.733333（ev525/526）。
- 批集合相同（{MrS -8 ×3, LG -7 ×1}），**只有到期 fire tick 差一拍**：名义到期 =
  施加时刻 2.916667 + dur 4.8 = 7.716667，oracle 实弹 7.733333（+1 物理帧）。

## 3. gd 侧内部不一致（最锐线索）

gd 的盲眼计时器两条挂靠链（output/oracle/align/np3c/run977_r18/rng_trace.txt）：

- side=1 首挂（B3 支）：`:1218-1219` START t=2.75 dur=4.8 resync=True → 名义 7.55，
  实弹 `:4012` t=7.566667（+1 tick，left=-0.016666）——**与 oracle 同拍**（O ev487
  LG -7 @7.566667，两侧 ev 完全一致）。⇒ gd 的 resync +1 tick 机制存在且在该路径正确。
- side=0 本次挂靠：`:1309-1310` START(B3)+GAIN(amt=7)，`:1330` GAIN(amt=8, KEEP，
  账面 left=4.65)，`:1353-1356` STOP→START(B1P)+GAIN(RESCH)，`:1377` GAIN(amt=8, KEEP，
  left=4.65) → fire 在 `:4220-4226` t=**7.716667**（准点，无 +1）。oracle 同批在 7.733333。

即：同为「同帧多批施加、同 dur」的挂靠，B3 路径 gd 给了 +1 tick，KEEP/B1P 路径没给。
且 `:1330`/`:1377` 的 left=4.65（= 4.8 − 0.15，恰 9 帧）在无任何 BSCHED 行的间隙里被扣减，
扣减来源未明，属内核账面问题。

## 4. 根因落点（file:line）

gd 内核（越面，未改）：

- gd_core/CoreBuff.gd:53-85 —— 内核计时器字段与「四分支模型」注；
- gd_core/CoreBuff.gd:244-267 —— gainTemporary 的 IDLE / RESCH / KEEP 分支（RESCH 判
  `duration < _timer_left`）；
- gd_core/CoreBuff.gd:524-584 —— `_startTimer`：①'（561-568，同帧 stop+start 同 dur，
  resync=false 原剩余续扣）、②（570-577）、③（579-581，resync +1 tick）；
- gd_core/CoreBuff.gd:587-604 —— `_stopTimer`（b3_fix1：只停走、保留 _timer_left）；
- gd_core/CoreBuff.gd:607-645 —— `_tick`：resync 帧不扣（= +1 tick 机制）、`<= 0` 即 fire。

oracle 真值面：

- decompiled_full/Core/Buff.gd:33-36 —— Godot `Timer`（one_shot + TIMER_PROCESS_PHYSICS）；
- decompiled_full/Core/Buff.gd:155-169 —— 临时栈 timeout=Util.time+duration；
  start / 同 dur 更短才重排；
- decompiled_full/Core/Buff.gd:317-336 —— onTimeout：弹最早到期批，delay ≤0.01 递归，
  否则 timer.start(delay)。

历史包袱线索：CoreBuff.gd:562-566 注记 r30 曾把 B1P 改 resync=true、r31 因 run727 未转绿
回退。本场证据（§3）说明 KEEP/B1P 路径在 oracle 侧同样 +1 tick，与 ①' 的「无重同步帧」
定性冲突——两场分支位形不同，需内核卡按「stop 是否已被 tick 遍观察」与 0.15 残差扣减
来源一并复核。

物品面免责：

- gd_core_items/MrStruggles.gd:45-51（onDebuffed）≡ decompiled_full/Items/MrStruggles.gd:46-51
  逐字同构；r35/K10 覆写仅动 checkTriggerCount（gd_core_items/MrStruggles.gd:53-68），
  而 rng 流锁到第 2244 抽证明该覆写在本场无时序漂移。
- gd_core_items/Exclusive/MissFortune.gd:6-11 ≡ decompiled_full/Items/Exclusive/MissFortune.gd:6-12
  （仅少 `activationParticles.activate()` 纯表现调用，不进判定路径）。
- 盲眼镜像链 giveStacksTemporary / gainTemporary 全在内核基类，物品脚本无计时器杠杆。

## 5. 全场缺抽 4688 的定性

首分歧前流全同 ⇒ 4688 缺抽为下游连锁，非独立第二根因：分歧后战局演化不同，盲眼施加
总量随之变少（O 盲眼 timeout 弹出 97 次 vs G 74；EVENT109 标记 O 393 vs G 312）。

## 6. 可能解法（给内核串行卡）

- 假说 A：①' 支（CoreBuff.gd:561-568）在本位形（stop 与 start 同帧、中间无 tick 遍观察）
  也应 resync（+1 tick）；r30 的 run727 反例位形不同，需按观察态细分而非全局回退。
- 假说 B：fire 判定改「过零后的下一处理遍」（统一 +1 tick），同时查明 `:1330`/`:1377`
  left=4.65（−0.15）的账面扣减从何而来——它使 KEEP 路径名义到期与 4.8 全长不再同源。
- 复核锚点：run977_r18 side0 挂靠链 rng_trace.txt:1309-1377 与 side1 对照 :1218-1219 /
  :4012-4019；oracle ev487（同拍）与 ev522-525（+1 拍）。

## 7. 本卡动作

- 只跑只读分析（_probe_draw_diff.py、python 分片读 trace、GBK bytes 读语料）；
  未跑 Godot、未跑 tools/gd_to_py.py、未写语料/oracle 目录、未动 git。
- 未改码 ⇒ 无备份、无还原。
