# np4_PINE — run921_r18 首分歧：幻影 InvulnerableEnd（内核面，本卡 blocked）

- 目标场：run921_r18（神谕重放 MATCH，语料可信）。
- 表象：gd 首分歧 ev=304。probe（`python -X utf8 tools/_probe_draw_diff.py output/oracle/probe/np3_or4b/run921_r18/rng_log.txt output/oracle/align/np3c/run921_r18/rng_trace.txt 12`）：O 3436 抽 / G 3481 抽（+45），逐抽首分歧=probe 序号 1483（probe 打印为 0 基下标，即第 1484 抽）：O 续 (0.9,1.1)，G 多出 (-50,50)、(-70,70)、(-0.366519,-0.05236)、randi(1,1)、(0.9,1.1) 五抽（Rapier 命中 FX+治疗），全部为事件分歧的下游噪声。

## 根因定性

**gd_core 内核 makeInvulnerable 的「fired 后同 dur 重 start → 同帧到期」残留标志 `_invul_instant`，在 extend 分支（已无敌时 changeTimer 延长）未被清除，导致本应重同步倒计时的延长授予被当成同帧到期，凭空提前 3 tick 发出玩家侧 Frog Prince 的 InvulnerableEnd。** PineProtector / FrogPrince 物品脚本与 oracle 逐行等价、触发时相完全一致，物面无需改码。

## 事件级证据（双方 events.json）

逐 id 对照（O=语料 output/oracle/probe/np3_or4b/run921_r18/events.json，G=gd output/oracle/align/np3c/run921_r18/events.json）：

1. id85–id303 双方完全一致（含玩家 Goobert id94 t=2.55 start(1.5) → 玩家 id185 End t=4.066667；对手侧 5 组 start/end 亦一致）——内核 invuln 常规路径对齐无误。
2. t=6.116667 玩家侧激活链：Goobert type12(-4 mana) → id293 Goobert InvulnerableStart(1.5) → id294 mana used=true → id295/296 Frog Lucky(5)/Mana(5) → id297 Frog InvulnerableStart(2.5, parent=294)——双方 id/time/parent 全同（Frog 由「耗蓝触发 use 阈值」链激活，非抢跑）。
3. **分歧点**：G 多出 `id304 type8 InvulnerableEnd src=Frog Prince ow=1 t=6.116667`（与 Start 同 tick！）；O 玩家侧该无敌直到 **id537 End t=10.133333（ow=1）**。10.133333 − 6.116667 = 0.016667×241 tick = 1.5+2.5 延长后 4.0s 的「重同步帧 + 240 扣减 + 发火帧」精确值——O 走的是正常延长倒计时。
4. id496 End t=9.45 为对手侧（ow=3）Frog 的正常到期（6.916667+2.533333），与玩家侧无关；双方一致。
5. 下游：O ev304 尖刺(6.166667) ↔ G ev305 尖刺(6.166667) 同 tick，Pine Protector 相位无偏；幻影 End 使 G 玩家 6.166667 起提前可受击 → Rapier 命中管线多跑（trace L3202 CANMISS src=[Reference:1316]+FX）→ RNG 流错位 5 抽。

## 机理定位（file:line）

- gd_core/CoreCharacter.gd:1481 首次授予支：`_invul_instant = _invul_fired and is_equal_approx(invuDur, _invul_last_dur)`——run634_r18 idx510 修的「fired 后同 dur 重 start 同帧到期」复刻，本身正确。
- 本场入口：玩家上次 End 在 4.066667（`invulnerabilityEnded`，CoreCharacter.gd:1501-1503 置 `_invul_fired=true`；`_invul_last_dur`=1.5 来自 id94）→ 6.116667 Goobert start(1.5) 走首次支 → `_invul_instant=true`。
- **Bug 行 gd_core/CoreCharacter.gd:1484-1488**（extend/else 支）：只做 `_invul_left=_f32(2.5+1.5)`、`_invul_resync=true`，**不碰 `_invul_instant`** → 残留 true。
- 驱动块 gd_core/CoreCharacter.gd:2109-2117：同帧 `_invul_resync` 支内见 `_invul_instant=true` → `_invul_left=0` → :2122-2125 `invulnerabilityEnded()` → 幻影 End id304。
- oracle 真源两处互证：
  - oracle/oracle_fight.gd:896-902：`if eng != e[1]: e[0] = eng`（重同步）`else: e[0] = e[0] - dt`。同帧到期只在 `e[0]≤0`（即上次发火残留 e[0]=-1）且 `eng==e[1]` 时发生；changeTimer 的 `start(t+timeLeft)`（oracle/Utility/Util.gd:1671-1677）会把引擎读数重写为 4.0 ≠ 残留 e[1]=1.5 → 驱动遍走重同步支，不可能同帧发火。
  - oracle/Core/Character.gd:1039-1050 + :1051-1059：发火必置 `invulnerable=false` → 再次授予必走 start 首支（:1043）而 `invulnerable==true` 的 else 支（:1048 changeTimer）只在计时器**仍在走**（e[0]>0）时可达 → oracle 的延长支在结构上不可能同帧到期。

## 可能解法（内核面，待后续串行卡认领）

gd_core/CoreCharacter.gd:1484-1488 else 支内补一行 `_invul_instant = false`（oracle 语义：changeTimer 重写引擎读数 → 重同步覆盖同帧残留；oracle 中延长支结构上不可达同帧发火，清除恒为对齐，对已过场 run634_r18 的首支 instant 无影响）。预期修复后 G 玩家侧 6.116667 授予按 4.0s 倒计时于 10.133333 发 End（=O id537）。

## 本卡处置

- 根因全部落在 gd_core/CoreCharacter.gd（内核面），非 PineProtector/FrogPrince 物面可修 → 按红线不越面，未改任何代码，无需备份/回滚。
- 物面核对结论：gd_core_items/Exclusive/PineProtector.gd 与 oracle/Items/Exclusive/PineProtector.gd、gd_core_items/Exclusive/FrogPrince.gd 与 oracle/Items/Exclusive/FrogPrince.gd 逻辑逐行等价（仅视觉差异：oracle 侧 activationParticles/light/createPulse），触发时相双方一致，物面 clean。
- 回归电池 REG 未跑（无改码，无从验证）。
