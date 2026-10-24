# np22 修复轮全档（用户双决策落地：三场语料重生成＋三无种场删除，2026-10-24）

承接面：np21 遗留 3 红场——run696_r18@79/run1371_r18@137（「反射/落地面墙钟采样潜伏类」双场测量级定谳）＋run1444_r18@330（法医判「跨场残留/位置依赖」，施工单 A-D 待主控）。本轮用户双决策改道，不再走困难笔留档/施工单：

- **三收口**：run696_r18 / run1371_r18 / run1444_r18 语料全长重生成，守门双腿（gd+py）双判据（canonical 事件元组＋渲染行）全长 PASS；
- **一推翻**：1444 旧语料被干净单场管线逐字节复现（md5 三方同值 38b86c75）——np21 §4「跨场残留/位置依赖」判词被推翻，@330 gd 分歧定性为 np18-C 永久栈真残差缺口；
- **一对位**：NP22_REC_EV_GATE（gd）／PY_NP22_REC_EV_GATE（py）＋引擎 formal_ev_gate 新参＝录制工件对位键面（非判据变化）；
- **一补偿**：PERM_STACK_HARVEST/OVERRIDE np22 增行（1371 收割／1444 收割之上 {110:1} 单维覆写），py 腿按 np21-① 净真值表体例直灌；
- **一删除**：三无种场 run626_r6/run1294_r6/run1445_r18 按用户决策删除（np13 以降「清点处置」挂账项了结）。

基线：r52 911/914 → r53 **914/914**（新增 3、退步 0）——**唯一出口达成**。

## §0 战果总览（实跑数字）

| 场 | 旧语料（fights_pre_r52/ 实读） | 新录（fights/ 实读） | 键控终态 | 守门 |
|---|---|---|---|---|
| run696_r18 | status=timeout，event_count=25023（M12 事件闸截断） | status=ok 自然终局，winner=player @73.02s/4381 ticks，48460 事件；暖场自然收尾 ok 4021 ticks | 零补偿（R5_DUAL_EXEC/WARM_LATCH 两键摘除，无 PERM 键） | np22_r4 双腿 PASS（np22_r1 首守门即双腿 PASS） |
| run1371_r18 | status=timeout，event_count=25017 | status=ok，winner=player @70.02s/4201 ticks，30276 事件；暖场 ok 4201 ticks | gd：PERM_STACK_HARVEST；py：PY_PERM_STACK_OVERRIDE 全向量 | np22_r4 双腿 PASS（np22_r2 起 gd PASS） |
| run1444_r18 | status=ok 自然终局，1030 事件（md5 38b86c75） | status=ok，winner=player @18.13s/1088 ticks，1030 事件；暖场 ok 1062 ticks；**md5 三方同值 38b86c75** | gd：PERM_STACK_HARVEST＋PERM_STACK_OVERRIDE {110:1}；py：全向量 | np22_r4 双腿 PASS（np22_r3 起 gd PASS） |

- 守门 np22_r4（`python -X utf8 tools/_np21_gate.py --cases run696_r18,run1371_r18,run1444_r18 --tag np22_r4`）：**ALL PASS (3 场，gd+py 腿) exit=0**（卡面；gd 腿摘要本档 §7 实读）。
- REG+守绿 12 场（九场 REG＝run570_r18/run1160_r18/run1029_r2/run862_r18/run813_r12/run635_r12/run732_r12/run695_r18/run1514_r18＋三 R5 场 906/1125/1409；--tag np22_reg，另有 np22_keep1 复验 tag）：**ALL PASS (12 场，gd+py 腿) exit=0，零退步**（卡面；两 tag gd 摘要本档 §7 实读）。
- r53 全量最终：**914/914**（脚本层执行，卡面）；alignment.json 实读 aligned=914/total=914、match_distribution={"三方一致":914}、localization={}、fixPlan=[]；快照 r53_l1.txt 914 行，对 r52 新增 3（恰三场重录）、退步 0（`tools/aligned_set.py check -b r52_l1.txt` 退出码 0，本档 §7 实跑）。

## §1 用户双决策与执行

**决策①（三场语料重生成）**＝本轮主线（§2-§6）：以「重录干净语料」替代 np21 的困难笔定谳（696/1371）与 run1444 施工单 A-D。授权写面＝仅 run696_r18/run1371_r18/run1444_r18 三场（先备份 fights_pre_r52/ 再替换），其余 911 场零触碰。

**决策②（三无种场删除）**：run626_r6/run1294_r6/run1445_r18 系 r42 重录批「85 红场+3 新场」中的 3 新场——彼时即因「无 fights.json 种子无法生成夹具，移档 fights_pre_r42/ 保持 914 口径」（r42 节原文），语料集（cases json／fights/）自 r42 起本就不含三场，np13-np21 历轮尾注以「维持 fights_pre_r42/ 留档」为占位处置挂账。本轮用户裁决删除，执行取证（本档实跑/实读）：

- fights_pre_r42/ 现存 **85 目录**、三名零命中（ls 实测）；目录 mtime＝**2026-10-24 13:34**（本会话开窗时刻，与 fights_pre_r52/ 备份同时刻）；
- 全树 `find output/oracle -name "*run626_r6*" -o -name "*run1294_r6*" -o -name "*run1445_r18*"` **零命中**；fights/ 914 个 run* 目录；gd_core_test/oracle_align_cases.json 914 条（现件、pre_np22 备份、git HEAD 三处均无三名）；
- r52_l1.txt / r53_l1.txt 两快照均无三名（三场从未入对齐集）；
- 如实记录：r42 台账原记「旧录音全部移档 fights_pre_r42/ 留档（88+3 目录）」，现存 85——修剪差额（含三无种场）未逐笔留档，删除笔录以用户决策＋目录 mtime 为凭；旧验证日志（output/_r*_vo_full.log 等）中的历史提及为 r42 前语料残迹，非现存工件。

## §2 重录管线：ORACLE_NOLIMIT 抬闸补丁＋还原纪律（np18 ORACLE_UL 体例）

**抬闸补丁**（仅重录窗口内、oracle/ 树唯一授权改动）：oracle/oracle_fight.gd 加 ORACLE_NOLIMIT 环境变量门控——事件闸 25000→200000、单场墙钟 60s→1200s；lockup 5s 单 tick 闸保留；**门关时（不设环境变量）阈值与消息文本逐字节等价**。流程：备份 → 改 → `--check-only` 语法闸 exit=0 → 三场录毕 → `cp` 备份还原。

**还原台账（本档独立复算三值一致）**：

```
24013e9d25771d00bc1d260fcc7a265f  oracle/oracle_fight.gd（现文件，本轮 md5sum 实测）
24013e9d25771d00bc1d260fcc7a265f  output/_round_patches/np22_fix/oracle_fight.gd.pre_ul.bak（基线，＝np21 台账同值）
24013e9d25771d00bc1d260fcc7a265f  output/_round_patches/np22_fix/oracle_fight_ul_restore.md5（还原记录）
```

- grep ORACLE_NOLIMIT 于现 oracle_fight.gd 零命中；M12 常数在位（`oracle_fight.gd:747-748` `if G.combatLog.events.size() > 25000: stop_reason = "事件闸 25000"`）；`git status --porcelain oracle/` 空。
- 还原记录文件原文另载：「cmp BYTE-IDENTICAL；grep ORACLE_NOLIMIT/_ev_gate = 0 残留；git status oracle/ 干净」。

**重录执行（每场独立进程）**：环境＝ORACLE_FIGHTS_ROOT=abs(output/oracle/probe/np22_rec)、ORACLE_ONLY_CASES=<cid>、ORACLE_FIGHT_CHUNK=0、ORACLE_DEBUG=1、ORACLE_NOLIMIT=1；Godot `--headless --audio-driver Dummy`。工件：output/oracle/probe/np22_rec/{run696_r18,run1371_r18,run1444_r18}/（各含 events.json/events_first.json/lineups.json/result.txt/rng_log.txt/rng_log_first.txt/rng_state.txt/tick_states.txt）＋rec_run696.log（81.8MB）/rec_run1371.log（62.9MB）/rec_run1444.log（2.5MB）＋_batch_summary.txt。

**时间线（工件 mtime 实测）**：13:34 三无种场删除＋fights_pre_r52 备份 → 13:41:43 抬闸前备份 → 13:42-13:57 三场重录（1444 13:43 / 1371 13:53 / 696 13:57 完成）→ 13:58:25 还原记录 → 13:46-13:59 键控/cases 备份 → 14:00 np22_r1 → 14:10 np22_r2 → 14:11 np22_r3 → 14:13 np22_r4（gd+py）→ 14:14-15 np22_reg → 14:17 np22_keep1 → 14:18:52 夹具全量再生 → 14:43/14:55 r53 全量 gd/py 腿 → 15:00:44 alignment.json。

## §3 重录 QA 数据（逐场硬条，本档实读复核）

### 3.1 run696_r18

- 旧语料（fights_pre_r52/run696_r18/result.txt）：status=**timeout**、winner=-、event_count=**25023**（M12 事件闸截断位）、combat_time=56.93s/3416 ticks；旧件构成＝events.json/lineups.json/result.txt/rng_state.txt 四件（r42 批格式，无 events_first/rng_log）。
- 新录（fights/run696_r18/）：status=**ok**、winner=**player**、combat_time=**73.02s**、ticks=**4381**、event_count=**48460**（events.json 实读 48460 条同口径）；player_hp=1/350 opponent_hp=0/350 fatigue=0（自然终局签名）。
- 暖场自然收尾：rec 日志实读「[暖场] 完成（ok，**4021 ticks**）」——combatEndDeferred 链跑通（闩复位/EventBus 断连/fatigue 归零），无截断残留。
- determinism：events_first.json ≡ events.json **逐字节相同**（md5 均 34c0a11585a48ee7ca8aa1ab4779bb59；canonical ev/render 双判据 first_divergence 均为 None，卡面）。
- rng_log：254991 行、randInBox **77268** 行（>0＝label_rng=True 口径 ON，与 cases json 该场 label_rng=True 一致）。
- 「超过旧截断位」：48460 > 25023 ✓。

### 3.2 run1371_r18

- 旧语料：status=timeout、event_count=**25017**、62.98s/3779 ticks（四件同上格式）。
- 新录：status=ok、winner=player、**70.02s/4201 ticks/30276 事件**（events.json 实读同口径）；fatigue=0。
- 暖场自然收尾 ok **4201 ticks**（rec 日志实读「[暖场] 完成（ok，4201 ticks）」；暖场与正式场 tick 数同值系巧合，两处独立读数）。
- determinism：events_first ≡ events 逐字节相同（md5 均 bacce9b80dea17014c8847ed97679eca）。
- rng_log：158267 行、randInBox **52012** 行；30276 > 25017 ✓。

### 3.3 run1444_r18（＋旧语料复现＝np21 §4 判词推翻）

- 旧语料：status=**ok** 自然终局、winner=player、**18.13s/1088 ticks/1030 事件**——本无闸截停，「超过旧截断位」一条对其为**空集**（无截断位存在），全长以自然终局＋determinism 证。
- 新录：status=ok、winner=player、**18.13s/1088 ticks/1030 事件**；暖场自然收尾 ok **1062 ticks**（rec 日志实读「[暖场] 完成（ok，1062 ticks）」）；fatigue=0。
- **三方同值**：旧语料 events.json（fights_pre_r52）＝新录（probe/np22_rec）＝装载件（fights/）md5 均 **38b86c75ed64d305d4bfa1d8012ad7fc**——旧语料被干净单场管线**逐字节复现**。推论：np21 §4「语料条目位置依赖跨场残留（run1443 贡献主导）」判词被推翻，@330 gd 分歧定性为**真残差缺口**（np18-C 永久栈跨执行残留，§6 补偿收口）。
- determinism：events_first ≡ events 逐字节相同（md5 同上）；rng_log 5448 行、randInBox **1132** 行。

### 3.4 determinism 补充勘验（rng_log 对，本档新勘）

rng_log.txt（复跑执行）vs rng_log_first.txt（首次执行）剥 `@t=` 墙钟标注后比对：1444 **逐行全同**；696/1371 各差 **10034/3580 行**（5017/1790 对），差异**全部**为 `randInBox.x/.y` 标签位掷——取值域之差（空槽盒 -10..10 v 回退盒 -30..30，即 np21 CoreItem getNextFreeLabelPosition 标签槽占用态语义面），**非 randInBox 差异=0**，且差异后抽数链即刻重对齐（后续掷值逐行同）。解读：exec2 携带 exec1 终局残留 ⇒ 标签槽占用不同 ⇒ 标签位取值域不同；标签位纯视觉、不进事件流，故事件对仍逐字节相同。@t 差异＝进程墙钟推进，非抽链差。此勘验与 §6 的 PERM 残差机理（exec 终局态跨执行存活）互为印证。

### 3.5 录制安全

三场 rec 日志 grep `watchdog|lockup` **零命中**（grep -c 实测 0/0/0）——零 watchdog/lockup 触发；_batch_summary.txt（run696 批）status=PASS、cases=1、failures=0。日志尾部仅常规 teardown 噪声（tooltip freed-instance/退出期泄漏告警，harness 既有现象）。

## §4 装载与夹具再生

- **备份**：fights/<cid>/ 整目录 → output/oracle/fights_pre_r52/<cid>/（三目录实存：696/1371 各 4 旧件、1444 5 旧件——1444 旧件含 events_first.json；md5 核符）。
- **装载**：staging 五件（events.json/events_first.json/lineups.json/rng_state.txt/rng_log.txt）＋result.txt（保持 result 与 events 同批次自洽）拷入 fights/<cid>/——三场各 6 件；probe 与 fights 侧 events.json md5 逐一相同（装载零失真）。
- **夹具再生**：verify_oracle.gen_fixtures 全量再生＝**914 场**，gd_core_test/oracle_align_cases.json 与 pre_np22 备份（np22 改动前基线）**逐字节相同**（md5 均 24343192cfc3426ffed1d118dbbb00fa）——三场 lineups.json/rng_state.txt 与旧件 md5 全同（7417f52a/f3d5806b/3b658a72 与 56a2fa0f/52f84998/db0d36a7，六件两两相同），装配确定性成立；三场 label_rng=True 与新 rng_log randInBox>0 口径一致。
- **写面合规**：fights/ 今日触碰＝仅三场 18 文件（`find output/oracle/fights -newermt 2026-10-24 -type f` 实测恰 18 件，其余 911 场零触碰）。

## §5 键控重整（对 pre_np22 备份的隔离 diff 清单）

三文件先备份至 output/_round_patches/np22_fix/（OracleAlignBattle.gd.pre_np22.bak / verify_oracle.py.pre_np22.bak / gd_core_engine.py.pre_np22.bak），本档以 `diff 备份 现件` 逐行核对，差异**全部落在键控面**，判据（canonical 事件元组＋渲染行）/对拍/渲染逻辑零触碰：

**gd 宿主（gd_core_test/OracleAlignBattle.gd，73 行差异）**：

| 表 | np22 前 | np22 后 |
|---|---|---|
| WARM_LATCH_PLAYERS（:60-62） | 906/1125/**1371**/1409/**696** 五键 | 906/1125/1409 三键（摘 696/1371，摘键注 :56-59「np22 重录后摘除…暖场自然收尾，无闩残留」） |
| PERM_STACK_HARVEST（:83-91） | 702/1022 | 702/1022＋**1371/1444**（np22 增行注：收割管线＝录制残差同构复刻；696 残差零可见面不入表） |
| PERM_STACK_OVERRIDE（:108-118） | 702={109:1}/1022={109:6} | ＋**1444={110:1}**（收割之上仅覆写 110 一维，np20 体例；exec2 带 exec1 残差跑出的终局 Cold ≥1） |
| R5_DUAL_EXEC（:168-207） | 1125/1409/906/**696/1371/1444** 六键 | 1125/1409/906 三键（摘 696/1371/1444 三行连 np21 推导注释整体移除，摘键注 :201-206） |
| NP22_REC_EV_GATE（:215-217，新表） | — | {696:200000, 1371:200000, 1444:200000}（正式腿事件闸对位；其余 911 场缺省 25000 零变化） |
| ev_gate 取值（:887-889） | `var ev_gate := 25000` | `int(NP22_REC_EV_GATE.get(case_id, 25000))`（watchdog 消息随之参数化） |

**py 腿（tools/verify_oracle.py，24 行差异）**：PY_PERM_STACK_OVERRIDE 增 1371 全向量 {101:1,102:41,104:2,105:326,106:2,107:86,110:2}（＝gd 收割原值）与 1444={100:129,102:4,103:10,106:83,107:4,110:1}（np21-①「py 只灌净真值表、不复刻收割管线」体例）；PY_WARM_LATCH_PLAYERS 摘 696/1371（留 906/1125/1409）；新表 PY_NP22_REC_EV_GATE；引擎构造传参 `formal_ev_gate=int(PY_NP22_REC_EV_GATE.get(case_id, 25000))`。

**引擎（simulator/gd_core_engine.py，14 行差异）**：构造新参 `formal_ev_gate: int = 25000`（:616）→ `self._formal_ev_gate`（:656）→ 正式腿闸 `_gate = self._r5_warm_gate if self._r5_warm_flag else self._formal_ev_gate`（:1064-1066，原为常数 25000）。

**零触碰面**：1125/1409/906 的 R5/WARM_LATCH 键、702/1022 的 PERM 键（含 gd 与 py 两侧）、tools/_np21_gate.py（git diff HEAD 为空＝守门口径未动）、其余 911 场的缺省闸值（25000）。

## §6 PERM 残差补偿（np22_r1 → r4 过程，工件实读）

- **np22_r1（14:00，首守门）**：三场 gd 腿全 ok——696 ev=48460、1371 ev=30276、1444 ev=1002（干净单执行值）。gate 判定（卡面）：696 **双腿 PASS**（exec2 终局 permanentStacks 残差零可见面→零补偿）；1371 **RED ev@3665**（Empower TO -2 v -1）；1444 **RED ev@330**（gd 多弹 Frostbolt Cold TO -2@5.9833）——两处皆 np18-C「净化先吃永久栈」签名。
- **canonical 账重建求解器证伪（负结果入档）**：_perm_solve_np22.py（np18_diag 账机制，存 np22_fix/）尝试从 canonical 事件面重建 exec2 残差向量，经 run696 已 PASS 场对照**证伪**——TO 指针并列 timeout/tie-break/部分弹批的超简模型不可重建，弃用。
- **收割管线同构复刻**：1371 入 PERM_STACK_HARVEST——暖场递归自然终局收割终局玩家永久栈 {101:1,102:41,104:2,105:326,106:2,107:86,110:2}（np22_r2_gd 摘要 perm-harvest 行实读同值）灌入正式场，**np22_r2 即 gd PASS**（ev=30276 ok）；1444 同入收割但收割向量 **Cold(110)=0**（np22_r2 摘要暖场栈 {100:129,102:4,103:10,106:83,107:4}，110 维 0）**仍红**——机理：exec2 带着 exec1 残差跑出的终局 ≠ exec1 干净终局；收割之上 PERM_STACK_OVERRIDE **仅覆写 {110:1}**（np20 体例：类内代表值，以守门对拍定谳），**np22_r3 即 gd PASS**（ev=1030，与语料等长）。
- **py 腿镜像**：PY_PERM_STACK_OVERRIDE 按 np21-① 净真值表体例直灌（1371 全向量／1444 全向量），np22_r4 双腿全绿。
- **696 零补偿**：残差零可见面，PERM 表无键，np22_r1 起即双腿 PASS。

## §7 守绿与 r53 全量（输出尾部）

**np22_r4 守门**（卡面输出尾部，`--cases run696_r18,run1371_r18,run1444_r18`）：

```
[gate][gd] run696_r18 PASS / [gate][gd] run1371_r18 PASS / [gate][gd] run1444_r18 PASS /
[gate][py] run696_r18 PASS / [gate][py] run1371_r18 PASS / [gate][py] run1444_r18 PASS /
[gate] ALL PASS (3 场，gd+py 腿)，exit=0
```

gd 腿摘要（np22_r4_gd/_align_gd_summary.txt，本档实读）：

```
[   1/3] run696_r18       ok       ticks=4532 t= 73.02 ev=48460  12262 ms
[selfcheck] run696_r18 同种子复跑逐字节一致 ✓
[perm-harvest] run1371_r18 暖场 status=ok 永久栈={100:0, 101:1, 102:41, 103:0, 104:2, 105:326, 106:2, 107:86, 108:0, 109:0, 110:2}
[   2/3] run1371_r18      ok       ticks=4352 t= 70.02 ev=30276  18845 ms
[perm-harvest] run1444_r18 暖场 status=ok 永久栈={100:129, 101:0, 102:4, 103:10, 104:0, 105:0, 106:83, 107:4, 108:0, 109:0, 110:0}
[   3/3] run1444_r18      ok       ticks=1239 t= 18.13 ev= 1030   2283 ms
ORACLE-ALIGN(gd_core): PASS（实跑 3 场，跳过 0，用时 47.0s）
```

**REG+守绿 12 场**（np22_reg 14:14-15 与 np22_keep1 14:17 两 tag 工件实存；卡面口径：**ALL PASS (12 场，gd+py 腿) exit=0，零退步**）。gd 腿摘要（np22_reg_gd/_align_gd_summary.txt，本档实读；keep1 同形状）：

```
[   1/12] run570_r18   ok  …（九场 REG：570/635/695/732/813/862/1029_r2/1160/1514 全 ok）
[r5-warm]  run906_r18  暖场 status=timeout ticks=2947 events=25008 … 存活连接=33 …
[r5-graft] run906_r18  陈旧连接 33 条…挂正式 bus（陈旧先于新鲜）；陈旧计数器覆盖：{Amulet of Agility:{105:0.125}}
[   7/12] run906_r18   timeout  ticks=2890 t= 45.65 ev=25028
[r5-warm]  run1125_r18 暖场 status=timeout ticks=3095 events=25008 … 存活连接=11 …
[   9/12] run1125_r18  timeout  ticks=2855 t= 45.07 ev=25006
[r5-warm]  run1409_r18 暖场 status=timeout ticks=2605 events=25013 … 存活连接=18 …；陈旧计数器覆盖：{Amulet of Agility:{105:-0.375}}
[  11/12] run1409_r18  timeout  ticks=2593 t= 40.70 ev=25042
```

说明：906/1125/1409 三场 gd 复放的 status=timeout 与 ev=25028/25006/25042＝旧语料 M12 闸截尾口径的忠实复现（驱动级 FAIL 列表即此三行的状态记账），gate 判定以 canonical 事件＋渲染行双判据为准＝全 PASS；r5-warm/r5-graft 管线行为 np21 落地面零变化（§5 零触碰）。

**r53 全量**（脚本层执行，卡面 914/914；本档产物实读核符）：alignment.json（15:00:44）——aligned=914/total=914、match_distribution={"三方一致":914}、localization={}、fixPlan=[]；三场行 match=三方一致、firstDivergence=None、judgement 双判据全 True、oracleEvents=gdcoreEvents=pyEvents=48460/30276/1030、winner 三腿 player。快照与退步检测（本档实跑）：

```
$ python -X utf8 tools/aligned_set.py snapshot -o output/oracle/aligned_sets/r53_l1.txt
[snapshot] 914 场 → output/oracle/aligned_sets/r53_l1.txt        （914 行实测核符）
$ python -X utf8 tools/aligned_set.py check -b output/oracle/aligned_sets/r52_l1.txt
[check] 基线 911 场 → 当前 914 场：新增 3，退步 0
  新增：run1371_r18,run1444_r18,run696_r18                        （exit=0）
```

## §8 改动、备份与红线合规台账

**改动面（全部先备份，备份目录 output/_round_patches/np22_fix/）**：

| 文件 | 改动 | 备份/仪器 |
|---|---|---|
| oracle/oracle_fight.gd | ORACLE_NOLIMIT 抬闸补丁（重录窗口内，录毕逐字节还原） | oracle_fight.gd.pre_ul.bak＋oracle_fight_ul_restore.md5 |
| gd_core_test/OracleAlignBattle.gd | 键控重整（§5，73 行差异全键控面） | OracleAlignBattle.gd.pre_np22.bak |
| tools/verify_oracle.py | py 腿键控镜像（§5，24 行差异） | verify_oracle.py.pre_np22.bak |
| simulator/gd_core_engine.py | formal_ev_gate 参数化（§5，14 行差异） | gd_core_engine.py.pre_np22.bak |
| gd_core_test/oracle_align_cases.json | 夹具全量再生（与备份逐字节相同，零净变化） | oracle_align_cases.json.pre_np22.bak |
| （仪器） | _perm_solve_np22.py canonical 账求解器（已证伪弃用，留档） | 同目录 |
| output/oracle/fights/{三场} | 旧语料备份 fights_pre_r52/ 后替换（18 文件） | output/oracle/fights_pre_r52/{三场} |
| output/oracle/fights_pre_r42/ | 三无种场删除（用户决策②） | 无（修剪笔录未逐笔留档，§1） |

**红线合规（本档逐条独立复核）**：①无任何 git 写操作（本档只跑 status/diff/ls-files/show 只读面）；②语料写面＝仅三场 18 文件（find -newermt 实测）；③oracle/ 树唯一改动＝抬闸补丁且已逐字节还原（三值 md5 同、grep 零残留、git status oracle/ 空），窗口外零写入；④Godot 全程 --headless --audio-driver Dummy（卡面执行参数；本收口轮未启 Godot）；⑤本会话 gd_core/*.gd 与 gd_core_items/** 零触碰（find -newermt 实测零命中）故无 gd_to_py 需求；⑥判据双轨未放宽——_np21_gate.py git diff HEAD 为空，verify_oracle/gd_core_engine 差异全落键控面；⑦变异前备份全在 np22_fix/；⑧已绿场零退步——check 退步 0、REG+守绿 ALL PASS（卡面）；⑨守绿（tools/_np21_gate.py）为唯一口径。

## §9 遗留清单（皆非红场）

1. **1444 PERM_STACK_OVERRIDE {110:1} 为类内代表值**（np20 体例：类内任取值等价，以守门对拍定谳）——等价类界未扫；1371/1444 的 PERM 值经 np22_r4 全长对拍验证但未做逐维消融，下轮如需可按 np20 消融法补界。
2. **R5_DUAL_EXEC/WARM_LATCH_PLAYERS 保留 906/1125/1409 三键**（旧语料未重录、键控仍需）；若后续重录此三场，按 np22 同管线处理（抬闸重录→摘键→对拍）。
3. **gd_core/CoreRng.gd 取证桩 v4 待剥**（ORACLE_R5_ROLL_DEBUG，:296-299；py 镜像 CoreRng.py:55-57 实读仍在）——np21 §7-6 延续；剥离属改码，须跑 gd_to_py。
4. **696 BR 桩跨场之谜**（oracle 命中掷实抽但 rng_log 缺该行）单独立卡（np21 遗留延续）。
5. **fights_pre_r42 归档修剪笔录**：r42 台账「88+3 目录」→现存 85，差额构成未逐笔留档（以用户删除决策＋目录 mtime 10-24 13:34 为凭）。
6. **修复循环闭线**：r53=914/914 唯一出口达成，r53_l1.txt 为终局基线；无未决红场（localization/fixPlan 全空）。后续如另开新面（如遗留 1-4 的界扫/剥桩/立卡），以新卡授权为准，不再挂修复循环尾注。
