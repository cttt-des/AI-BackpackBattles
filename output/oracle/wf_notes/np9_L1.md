# np9_L1 · 盲批早 N tick 五场定谳留档（阶段1 分析，2026-10-20）

## 结论（先答）

**卡面（gd_core/CoreBuff.gd / CoreTimer.gd）零改动点，判 blocked。**

「gd 盲批（Burning Banner/Light Goobert）系统性提前插入」不是 gd 相对 oracle 的偏差——
**现行 oracle 树与 gd 在全部六张验证场上逐事件全同**；「提前」只存在于 gd/现行 oracle 树
**相对于冻结语料**（output/oracle/fights/，2026-10-07 02:36 冻结）。根因是
**语料 ↔ oracle 树代际漂移（台账 K01/K03 家族）**，不落在任何 gd 内核文件里。

判据：oracle 侧 probe 重放（现行树，确定性自证）产出的事件流与 gd trace **逐事件全等**
（6 场 × 全长，键 (type,timestamp,origin,params) 首分歧=None），而 probe-vs-语料的首分歧
恰好落在各场盲批提前位（271/222/654/531/195/2563）。若按本卡在 CoreBuff.gd 上
「修提前」，等于把 gd 从与现行 oracle 全等推向两边不讨好——文件面无解。

## 证据一：三方对表（gd trace vs 语料 vs probe 重放）

gd trace 取 output/oracle/align/gdcore/<case>/events.json（2026-10-19 21:29–21:57 生成，
np8 现行码；np8_a/run986_r12/events.json 与之 events 全等已验，故 trace 反映现行代码）。

| 场 | gd/语料首分歧 | gd 侧插入事件 | 语料同位事件 | probe-vs-语料首分歧 | probe-vs-gd |
|---|---|---|---|---|---|
| run986_r12 | idx271 | t=6.5333 Blind TO -1（Burning Banner） | t=6.6500 False Life heal | **271** | **None** |
| run688_r10 | idx222 | t=9.8833 Blind TO -1 | t=10.1667 Blind TO（同批晚 17 tick） | **222** | **None** |
| run1073_r12 | idx654 | t=12.7000 Blind TO -1 | t=12.7667 Chili Pepper | **654** | **None** |
| run1167_r18 | idx531 | t=5.2833 Blind TO -7（Light Goobert） | t=5.2833 Chili Pepper 链 | **531** | **None** |
| run1231_r18 | idx195 | t=4.4667 Blind TO -7 | t=4.4667 Snowmaster 链 | **195** | **None** |
| run977_r18（旁证） | idx2563 | t=18.7667 LG Blind TO **-9** | 同刻 LG Blind TO **-10** | **2563** | **None** |

- 六场 probe 与 gd 全长一致（4023/958/1532/4016/3070/6366），首分歧 None = 全等到底。
- run977 形态不同（同刻弹量 -9 vs -10）：分歧前事件面全同 ⇒ 批布局差异不可见
  （同总量的批拆分/并批在弹出前无事件痕迹）——同属语料代际差，非 gd 内核判据面。

## 证据二：probe 重放命令与产物

分析期特权内执行（产物只进 probe 目录）：

```
ORACLE_FIGHTS_ROOT="D:/文件资料/学习/自动背包AI/output/oracle/probe/np9_L1_986[_pl]"
ORACLE_ONLY_CASES='run986_r12' [ORACLE_DEBUG=1] \
  ./output/godot36/Godot_v3.6-stable_win64.exe --headless --audio-driver Dummy \
  --path oracle --script oracle_fight.gd
```

- run986_r12：debug 版（np9_L1_986）与无 debug 版（np9_L1_986_pl）events **互相全等**，
  且都与 gd 全等、与语料分歧于 idx271——排除 ORACLE_DEBUG 改行为。
- run688_r10/run1073_r12/run1167_r18/run1231_r18/run977_r18：np9_L1_<case>/ 同法，全部
  probe==gd、首分歧=盲批位。run986 另有 probe_conn.gd（SceneTree node_added/node_removed
  自连最小复现：added=2 removed=2，连接机制本身可用）。

## 证据三：漂移时间线（语料冻结早于树改）

```
output/oracle/fights/run*/events.json   mtime 2026-10-07 02:36（冻结语料）
oracle/Utility/Util.gd                  mtime 2026-10-10 14:51
oracle/oracle_fight.gd                  mtime 2026-10-17 12:15
oracle/Core/Buff.gd                     mtime 2026-10-17 13:42   ← 全部晚于冻结
```

- 树与真源的差异点（RESCH 判据）：现行 oracle/Core/Buff.gd:164-171 用
  `Util.oracleTimeLeft`（= oracle_fight.gd:881 注册表 e[0] 活剩余；oracle/Utility/Util.gd:807-810），
  真源 decompiled_full/Core/Buff.gd:164 是 `if duration < timer.get_time_left():`。
  np5_K1.md:56-68 记载 gd 侧随即对齐该桩（gd_core/CoreBuff.gd:261
  `_bsched_resch = duration < _timer_left`）。
- 家族先例（均有档）：
  - A1CRN.md（2026-10-17）K04-B：run1038_r9 同形态盲批矛盾（run688 当遍瞬弹 vs
    run1038 存活 33 tick），已明示「现行 oracle 树无法取证——不硬修」，移交 K01。
  - GEN1.md:35：run895_r10 语料(10-07) vs 今日重导 lineups(10-17) 格位级物品身份不一致
    ——同一代际漂移家族。
  - A3BLD.md:89：「找回 corpus 时代 oracle 树 Buff.gd（现存备份均=现行）」考古已碰壁。
- 台账 K03/r35 早已记录「corpus 盲批到期相位无跨场一致性」。

## 机制面 file:line 备查（本轮逐字读过的判据面）

- gd_core/CoreBuff.gd:261（RESCH 判据）、:541-607（_startTimer 四分支 ①/①'/②/③）、
  :56-96（四分支模型注）、:610-623（_stopTimer 保留 left）、:630-671（_tick：stopped 观察
  写 -1 / resync 不扣 / fire / 遍尾 e[1]）
- oracle/Core/Buff.gd:160-173（gainTemporary idle/RESCH，含 164-171 HARNESS 桩）、
  :286-288（净化清空 stop）、:331-354（onTimeout 递归/REARM）
- oracle/oracle_fight.gd:880-925（drive_timers：stopped e[0]=-1 / eng≠e[1] 重同步 /
  e[0]-=dt / 处理器重启支）、:956-992（registry 重建与 node_added/removed 登记）
- decompiled_full/Core/Buff.gd:160-167（真源 RESCH 用引擎读数）

## 已排除与未竟事项（如实记录）

1. **已排除**：ORACLE_DEBUG 影响重放（双跑全等）；gd trace 陈旧（np8_a 全等复核）。
2. **未竟 a**：全量跑 stdout 有 48845 条 `node_removed→'SceneTree::_on_node_removed':
   Method not found` 派发错误；最小复现（probe_conn.gd）证明该连接方式本身可用，
   错误来源未定谳。**不影响结论**（结论建立在 events.json 全等上，stdout [timer-fire]
   行稀疏仅作仪器观察，勿据此做逐拍取证）。
3. **未竟 b**：本轮自建 python 批机制模拟（FROZEN-wait vs LIVE-stub 两种 RESCH 语义）
   粒度不足（净化/保护/反射链还原不全），**不采信为仲裁**——最终仲裁只用 probe 全流
   逐事件对表。RESCH 判据代际差是否即语料差的主因，留 K01 用可整套复刻的仪器定谳。
4. **禁跑腿已守**：gd 验证腿（REG 九场）未跑（脚本统一跑）；语料/oracle 树零写入；
   git 零操作。

## 移交建议（K01 盘归并）

1. 本卡六场并入 K01 证据集：gd↔现行树全等 ×6，语料分歧位 ×6（上表）。
2. 语料真值重建议的两条路（均在本卡文件面之外）：
   a) **语料代 oracle 树考古**：重点候选=RESCH 判据代际差（decompiled_full/Core/Buff.gd:164
      引擎读数在阻塞循环下=wait_time 冻结值 vs 现行桩的注册表活剩余）；可用「按真源原样
      + 冻结引擎」语义离线重放六场，若能复现语料盲批序列即定谳。
   b) **语料再生成**：以现行树重出 output/oracle/fights/（红线：本轮只读，未动）。
3. 在 2 定谳前，任何针对盲批的 gd 内核单笔修改都会破坏已证实的 gd↔oracle 全等与
   REG 现状——不建议。

## probe 产物清单

- output/oracle/probe/np9_L1_986/（ORACLE_DEBUG=1 全量 stdout + events + probe_conn.gd）
- output/oracle/probe/np9_L1_986_pl/（无 debug 复核）
- output/oracle/probe/np9_L1_run688_r10/、np9_L1_run1073_r12/、np9_L1_run1167_r18/、
  np9_L1_run1231_r18/、np9_L1_977/（各 events + stdout_plain.txt）
