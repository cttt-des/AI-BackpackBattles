# np25 问题总账与执行手册（2026-10-31 压缩重写；基线 706/914）

> 本文件=唯一任务书。2026-10-31 压缩重写：1849 行历史战报块已删，**全文可追溯**
> ——`git log --follow -p docs/np24_issue_ledger.md`（压缩前基线快照=1a49e8d7，
> 历次战报的取证细节/探针材料/证伪过程全在其中）。宁少删勿多删原则下，本版
> 只保留：铁律、工具速查、当前状态、防回退清单、红场分簇与问题清单、定谳
> 知识库、交付口径。

## 0. 环境与铁律（每次动手前重读）

1. 工作区 `D:\文件资料\学习\自动背包AI`；**工作区外零操作**（用户铁令）。
2. Godot 一律 `tools/godot_headless.py`（`--no-window --audio-driver Dummy` +
   **独立隐藏桌面** + stdout 重定向文件 + APPDATA 按 PID 隔离 + cwd=output/_recovery/cwd）。
   ⚠ **OpenMem 弹窗**=搜狗 DLL 宿主注入（err=2 纯噪声），隐藏桌面根治；
   `--headless`（4.x 参数）/`--video-driver Dummy`（rc=255）/'只 --no-window'（仍出窗）三坑勿踩。
   ⚠ **启动器三重加固（2026-10-31，da6e7c7d）**：桌面创建失败重试 3 次后**响亮抛错**
   （绝不静默回退可见桌面）；桌面名按进程唯一 `dsh_godot_hidden_<pid>`（共享桌面
   desktop heap 被数百场泄漏对象撑爆 ⇒ 并发子进程被 Windows 摔回默认桌面=漏窗，
   单发恒静默、4 路并发必漏实测定谳）；spawn 落 `[gh] provenance` 日志头（排障）。
   ⚠ **wintab32 楔死（2026-10-31 定谳）**：Godot 全项目启动挂死 banner 后零输出=
   主线程卡 `wintab32.dll`（数位板服务 WTInfo 查询挂死，**非 GL**：NVIDIA/Mesa
   llvmpipe/双桌面同卡、`--version` 正常）。根治=`output/godot36/wintab32.dll`
   （30 字节 stub 劫持 DLL 搜索序→优雅跳过笔输入）；用户侧修好数位板服务后删此
   文件还原。线程栈回溯法（dbghelp+模块基址映射）为此类「机器级楔死」标准诊断。
3. `output/oracle/fights/`（语料）与 `oracle/` 树只读——**例外（2026-10-31 起）**：
   语料已整体重录一次（用户授权），重录基建改动（oracle_fight.gd teardown 清扫/
   冲池/闸门校准）已入库；**再次写语料仍需用户批准**。oracle 取证桩六步：备份→
   ≤10 行环境变量门控→ORACLE_FIGHTS_ROOT 重定向（**必须绝对路径**）→逐字节还原→
   md5 三方留档（先例 output/_round_patches/np24_fix/ 各 *_probe/）。
4. 改 `gd_core/*.gd`/`gd_core_items/**` 后必跑 `python -X utf8 tools/gd_to_py.py`，
   并同步 `cp gd_core/*.gd gd_core_test/gd_core/`（**只拷 .gd**——误拷 .py 进
   Godot 工程有前科）。
5. 判据双轨不放宽：canonical 事件 + 渲染行。守门唯一口径：
   `python -X utf8 tools/_np21_gate.py --cases <cid,...> --tag <每轮新标签>`（rc=0 全绿）。
6. REG 九场防退步：`run570_r18,run1160_r18,run1029_r2,run862_r18,run813_r12,run635_r12,run732_r12,run695_r18,run1514_r18`。
7. 全量验证三腿自动并行：`python -X utf8 tools/verify_oracle.py --force`（改内核/
   夹具/语料后必须 --force，幂等跳过会把陈旧产物当现状，铁律 11）；
   只重比对=`--compare-only`（不带 --cases）。⚠ `--force --cases` 会把
   gd_core_test/oracle_align_cases.json **收缩成那几场**（实测 1 场假基线）——
   被占用时加 `--skip-fixtures`；已收缩用 `git checkout` 恢复（914 场版=823bfe33）。
8. 变异前备份到 `output/_round_patches/np24_fix/`。已绿场不许退步。
9. 盲修禁制：同一假设两连证伪即停；反例锚先行；数值同而状态分叉=有看不见的抽。
10. 语料=**2026-10-31 全量重录版**（914 场，冲池后定位无关语义；旧版 1.3GB 备份
    `output/oracle/fights_pre_rerecord_20261031/`）。below_master=true 终谳勿回退。
11. 幂等跳过三杀：分片器/驱动/守门全都有「产物存在即跳过」——**任何变更后重跑
    前先删目标产物**（教训×3：假探针零行、假基线、假 PASS）。
12. assets 再生链三产物一个不能漏：gen_lineup_fixture → gen_fixture_from_lineup
    （`--oracle <用例目录列表>`——**别传父目录**，会 0 场覆写）→ gen_gd_core_data。
13. **TaskStop/后台任务孤儿**：停后台任务只杀 bash 管道壳，driver python 存活
    （2026-10-31 实测 14 个孤儿并发录制=进度 pid 乱跳+窗口杀不尽的真凶）。
    杀进程必须 **bash 级 taskkill**（python 内 subprocess 传 `//F` 不经 MSYS 转换
    =「无效参数」静默空操作）；wmic 快照含幽灵条目，验尸以创建时间+父链为准。
14. 长任务看门狗：录制/全量验证每 30-60s 查一次进度文件与日志增量，静默 >10 分钟
    即介入（本次 wintab 楔死与僵局场爬行都靠它发现）。
15. **长场检验禁令（2026-10-31 深夜用户令）**：**全量 914 `--force` 与 54 长场
    （output/_recovery/excluded_long_cases.json 清单）的任何检验，未经用户明示
    许可不得启动**。快速腿账面刷新只用 860 夹具路径；长场/全量通道恢复=等用户
    指令。清场时 py-worker 孤儿同样要杀（主驱动死后 py 腿 worker 存活续跑，
    铁律 13 的 py-worker 变体）。

## 1. 工具速查

| 用途 | 命令 |
|---|---|
| 守门（gd+py 双腿，分钟级） | `python -X utf8 tools/_np21_gate.py --cases <c,...> --tag <新>` |
| 全量三腿（改内核后） | `python -X utf8 tools/verify_oracle.py --force`（分片流水线，LPT） |
| 只重比对（产物就绪） | `python -X utf8 tools/verify_oracle.py --compare-only`（**绝不带 --cases**） |
| 红场分簇 | `python -X utf8 tools/_np24_red_clusters.py --top 25` |
| 单场神谕复跑（统一入口） | `python -X utf8 tools/run_godot_script.py oracle_fight.gd --project oracle --env ORACLE_ONLY_CASES=<cid> --quiet`（或 `ORACLE_ONLY_CASES=<cid> python -X utf8 tools/oracle_chunk_driver.py 1 1 1`） |
| 语料重录 | `python -X utf8 tools/oracle_chunk_driver.py 60 12 0`（后台跑；闸门已校准：单场墙钟 60s/事件 200k——**僵局场会被截断并如实标 timeout**） |
| 逐抽对位 | `python -X utf8 tools/_probe_draw_diff.py <语料rng_log> <gd rng_trace> [N]` |
| canonical 对拍 | `sys.path.insert(0,'tools'); import verify_oracle as V; V.first_divergence(...)` |
| 神谕探针 | ORACLE_FIGHTS_ROOT=**绝对路径** + ORACLE_ONLY_CASES + ORACLE_DEBUG=1 + ORACLE_FIGHT_CHUNK=0，经 gh 直跑（chunk driver 对已有产物幂等跳过！）；**先验探针 events≡语料才采信**；桩行必须 6 元素 |
| 线程栈回溯（楔死诊断） | python ctypes：SuspendThread+GetThreadContext+ReadProcessMemory 扫栈→模块基址映射（先例见 1a49e8d7 会话） |
| GitHub API | `gh` CLI（已登录 cttt-des）；**禁 git credential fill**（弹 GCM 窗） |

## 2. 当前状态与交接（2026-10-31 压缩版落笔时）

- **基线 706/914**（RED 208）——本日三连后全量 `--force` 实测：
  ①语料整体重录（**位置依赖根治**：teardown 冲 ObjectPool——动画实例跨场存活、
  `_ready` 只跑一次吃 RNG=Flicker delay 等——链状态按场序漂移；单场重录≠批内位置
  录制=f02「不可单场复现」/f06 幻影/f11 三案同源，冲池后 E=F 实证定位无关）；
  ②gd CoreTimer 注册表同构模型（f11，commit 48c72e13）；③工作流波 1-4 收割入库
  （f01/f03/f04/f05/f08/f09/f10，约 40+ 场——461 账早已过期）。
- **工程三方**：语料 output/oracle/fights/（914 场，每场 events.json+lineups.json+
  result.txt+rng_state.txt）↔ gd_core（Godot 无头重放）↔ gd_core_py（Python 转写）。
  唯一出口 `output/oracle/alignment.json`（**禁手写**；只由 verify_oracle 产出）。
- **判据**：canonical 事件流逐行 + 渲染战报行逐行，双轨全对齐才算绿场。
- **工作流状态**：批次 v2 修复工作流已收尾停机（run dwfrun-f2c47064，可恢复但
  语料已换代，恢复价值低）；后续执行体=offpeak 任务（见 §4 任务书）。
- **遗留禁区/待批**：P1-1 收缩版（语料写=需用户批准窗口）；wintab32 stub 待用户
  修好数位板服务后删除。
- **历史全文**：本文件被删的 35+ 战报块（2026-10-28~10-31 全部取证/证伪/探针
  细节）→ `git log --follow -p docs/np24_issue_ledger.md`；探针材料落盘
  `output/_round_patches/np24_fix/` 各 *_probe/。

## 3. 已修复防回退（一行一针；细节=对应 commit 信息与 git show）

- 宝石槽=实例真相 / below_master=true 终谳 / defer 镜像+ANIM+MagicRing+EB 接力
  （4315c580）/ crafted 实例真值链（c1655431）
- A2 grid 真值面：extract_grid 重指 1.1.9、19 件基座 2×2、affected_cells 真值、
  46 宝石复位（→f05 又发现 Wisp t4 连坐清空，aba6d2b4 回植）
- 棋盘 capture 面：12 件棋子 types+递归扫四层目录+moveCells 真值+CoreRng 全局链
  shuffleEngine/pickRandomEngine+CoreGrid.moveItem（d4afe736+b05e33f9）
- 电荷像素几何：inventory_cell=锚+R_fd(c)−rotmin(fd)（143/914 时 +18）
- loseHealth 补抽 / 全局链预热 / sceneDepth 装配缺抽 / f64 直译（f32 对称化停用）/
  StaminaSack / heal 类型化形参分支截断（edfc0784——默认实参直通、显式 float
  实参 int() 向零截断，20+ heal 调用点）
- f01 CoreTimer 叠加到期（167b7f6e）→ **f11 CoreTimer 注册表同构模型**（48c72e13，
  本日最大定谳）：冻结时钟下 eng 仅 start/stop 改写；运行中**同值 start=注册表
  盲区（重启丢失，旧截止期存活）**；停走 pass e[0]=-1；post-emit 重挂 e[0]=e[1]=eng
  无条件满计数；stop 不清 e[0]；multi 路径维持 f01 语义
- f04 Timer f32 存储镜像+fire 后重同步（c0392d3b，18/25 翻绿）
- f08 classes 派生链+getStackFraction overflow 洗牌走引擎全局链（823bfe33）
- f09 TileMap used_cells_by_id RB 树序（2b259654，16 场）
- f10 PotM advanceTime 死调用镜像（6f82a29c）——harness 里 PotM.onPostCombatStart
  的 advanceTime 是死调用（bootstrap 裸 Node2D），语料疲劳起点恒 14s
- **语料重录基建**（48c72e13+da6e7c7d）：teardown shopEntered 双侧清扫 +
  ObjectPool/prepareQueue 冲池 + 墙钟/事件闸校准（60s/200k）+ 启动器三重加固
- GUI：共用脚本物品贴图串货+开录误录误停（34002597）

## 4. 红场分簇与新问题清单（208 场 25 簇 → 12 问题；=offpeak 任务书本体）

> 分簇命令：`python -X utf8 tools/_np24_red_clusters.py --top 25`（2026-10-31
> 706/914 实读）。**旧语料时代的定性（evt109 计数死锁/timeout1t 时基差/总线
> 级联等）一律需在新语料下重验**——语料链已整体移位。样本场守门先于一切。

1. **evt109@151-400 ×33**（最大单簇）：样本 run605_r15/run619_r18/run622_r15。
   旧定性=Goobert 计数路径死锁挂总线面（旧语料）——新语料下先 canonical 对拍
   重新定性；evt109=毒/触发投掷面，与 f01/f11 的 CoreTimer 家族强相关。
2. **evt109@401-1200 ×19**：样本 run629_r18/run702_r18/run744_r18。与问题 1 同族
   后段，先并簇再拆签名。
3. **evt109@51-150 ×9 + @1201+ ×2**：样本 run688_r10/run726_r18。
4. **evt0@151-400 ×23**：样本 run601_r18/run1097_r18/run1107_r18。Unhealing
   反射族残差（CoreTimer 修复后仍红）——反射序/双实例/池差方向，F11 探针
   （UNHEAL_TRACE py 侧 4 处+F11HEALID/F11DMGID oracle 侧材料）可续用。
5. **evt0@51-150 ×10 + @401-1200 ×2**：样本 run1119_r6/run691_r18。
6. **evt1 四簇 ×38**（11@1-50+9×3）：早期 DealDamage 分歧、签名异质——**先
   canonical 对拍并簇**（勿直接开修），样本 run1084_r14/run579_r18/run595_r18/run628_r14。
7. **evt108/evt12 残量 ×14**（6+4+2+2+1+1）：SPF/毒批族残差。样本 run578_r11
   （语料 ty12 amount42 系新语料重录位）/run590_r13。f10 遗留单点=OilLamp._ready
   边界桩定谳 flicker delay 隔字抽身份（1540/962）。
8. **evt19@1-50 ×6**：开战激活序。样本 run1015_r18/run1128_r18。
9. **evt105 ×10**（5+3+2）：ManaOrb/连接集。样本 run1101_r18/run947_r10/run1253_r11。
10. **evt103 ×4**：**f07 定谳域**——SVP lifestealTimer fire/wipe/pop 语义差+37s
    新实例顶替分裂（定谳材料 output/_round_patches/np24_fix/f07_probe/）；
    CoreTimer 新模型已落，先重对拍看残差是否已被新语义吸收。样本 run594_r12。
11. **长度分歧 win 翻转 ×10**（len G>O P=G）：新语料特有面——gd 事件更多且胜负
    翻转=池冲洗链移位后的行为差。样本 run1082_r18/run1124_r18/run1174_r18。
12. **py-only ×2**（run906_r18/run1151_r13）：gd≡oracle、py 单独分歧——gd 产物
    直读对照，最快收敛面。

## 5. 定谳知识库（蒸馏；一条一句+指针，细节见 commit/历史）

- **计时器三定律**（f01/f04/f11 合并定谳，全部语料实证）：
  ①冻结时钟下引擎 time_left 仅 start/stop 改写，harness 注册表以 `eng!=e[1]`
  判外部 start——**运行中同值 start=盲区（重启丢失）**；②引擎 real_t=float32
  存储（f32(3.1) 穿零 186 帧≠f64 187）——eng 写入点过 _f32eng；③fire 后处理器
  内重挂=当拍 e[0]=e[1]=新 eng 重同步；到点段先 stop() 再 emit（叠加排队全丢）。
- **SVP lifestealTimer**（f07 定谳未修，材料 f07_probe/）：fire/wipe/pop 语义差
  +37s 新实例顶替分裂——CoreTimer 新模型下重对拍（问题 10）。
- **事件语义**：ty1 的 target=**伤害制造者**（createEvent_Damage setTarget(damagingPlayerId)）；
  unhealing 反射事件 origin=DamageSource.Type.Unhealing **枚举值 98**（int，grep
  字符串会漏）；语料 id==eventNum 稠密（0..N）但 heal() 调用数≈入账数×3
  （快照等创建不记日志——对位用 id 别用调用序）。
- **物品实例生命周期**：阻塞循环无帧时钟→prepareItemInstances 恒死→**战斗物品
  每场全新**（池复用理论对物品不成立）；**ObjectPool 动画/粒子实例跨场存活**=
  位置依赖载体（已冲池）。
- **harness 结构**：oracle_fight.gd=SceneTree 手动 tick（步骤①-⑧）；
  drive_timers 注册表=U.oracleTimerLefts[e0,e1]；暖场=cases[0] 丢弃跑；
  determinism_check 复跑首场并覆写 events.json；`Game.combatLog.logEvent` 的
  `visible` 延迟队列；fightEnded 后事件照常 createEvent 不入账。
- **gd_core 对应物**：CoreTimer（注册表同构，48c72e13）；CoreCharacter/_f32eng
  （c0392d3b）；CoreRng.shuffleEngine 全局链（823bfe33②）；CoreItem.heal 分支
  截断（edfc0784）；CoreItem.getAffectedCells_tilemap yx 序（2b259654）。
- **诊断工具链**（双门控零耗，ORACLE_ALIGN_TRACE/STACKTRACE 门控）：ANIM/SRC/
  LABEL/MSROLL/CHRG/SPD+/AFFL/EBARR/BALROLL/GRD/BUSL/CDX；oracle 侧
  ORACLE_DEBUG+ORACLE_RNG_DEBUG+各面 PROBE 桩。UNHEAL_TRACE（py 侧 4 处，
  48c72e13 时代入树）。
- **已永停面**（勿重开，除非新语料翻案）：总线级联面五连证伪（FuncRef 绕过/
  CALLDONE/削切落点/连接序/计数死锁——2026-10-30 五循环全闭环）；timeout1t
  「时基差」前提（gd/py↔oracle 逐位零差证伪——旧语料时代，新语料下 evt109 面
  重新定性时先复验此结论）。
- **分簇器**：firstDivergence 有平铺/嵌套两种形状（嵌套=两对都分歧），解析已修
  勿回退。

## 5b. offpeak 会话战报（2026-10-31 下午；任务书=本文件 §4 十二问题）

- **p1 evt109@151-400 ×33 → 定谳+基建修（76e2d76d）**：run605_r15 语料（批内
  5683 事件）≠oracle 单场重放（5455）且 **gd≡oracle 单场逐字节全等** ⇒ 分歧不在
  引擎、在**语料批内残留态**。载体=oracle Buff.reset 只清 current 不清
  temporaryStacks/nextTemporaryTimeout/permanentStacks+timer（阻塞循环无帧时钟
  ⇒ 上一场终局未到期临时栈跨场渗入；真游戏=商店期帧时钟自然到期清空）。
  修后 37 场 manifest 前缀重放 ≡ 单场（5455）验证通过。**语料残留态场需下一轮
  重录收割（用户批准窗口）**；同簇 run622_r15 三方三值（oracle 单场 4797/gd
  4682/语料 4792）=真实引擎差另根，留 u 流深挖。
- **p5 evt0@51-150 ×10 → ✅fixed（3d270e81）**：np24「EB 接力死亡镜像」手补
  （eb_relay_mirrored=true）的探针前提全部换代——新语料 run1119_r6 实证录制侧
  EngineerBox 接力**活跃**（Battery 开战发射→EB.chargeTimer delay=5s 接力
  emitCharge→Battery@5.0167 再激活→Eggscalibur damage 15→16）。三处开关翻转
  true→false。守门：run1119_r6 双腿 PASS + **run1160_r18 附带翻绿**；
  p5b 扩验 6/8 翻绿（1287/1305/1312/1314/1319/1329 PASS，1283@198/1130@502 残）；
  p5c 扩验 run1282_r18 PASS。**合计 +9 场（守门口径）**，REG 零退步。
- **全量基线**：EB 恢复后全量 --force 重跑中（本节落笔时），数字以重跑后
  alignment.json 为准（预期 ≥706+9）。
- **方法论沉淀**：「单场语义定性器」——gd vs oracle **单场**（无批内残留）对拍：
  单场逐字节全等 ⇒ 语料残留态（重录收割）；单场≠ ⇒ 真实引擎差（可修）。批量
  定性脚本模式见本会话（oracle 侧 ORACLE_FIGHTS_ROOT 重定向 + gd 侧
  ORACLE_ALIGN_OUT 重定向 + ORACLE_ALIGN_CASES 显式限场——**勿用
  run_godot(case_ids=) 裸调**，它会跑全量 914 场 37 分钟）。

## 5c. 超长场剔除通道（2026-10-31 傍晚，用户指令）

- **方案**：events.json ≥3MB 的 54 场从对齐夹具临时剔除（清单
  output/_recovery/excluded_long_cases.json；全量夹具备份
  output/_recovery/oracle_align_cases_full_backup.json）——并行腿速度的杀手
  不是腿数（三腿本就 ≤5 路分片并行）而是**片内串行撞上超长场**（run629 一场
  爬 6.6GB 内存/数十分钟）。
- **快速腿结果**：707/860（153 红；rng-mechanism 139/gd_core-kernel 13/
  py-transpiler 1）。
- **54 场专用通道**（2026-10-31 傍晚用户令：**暂停**——860 场未全对齐前不处理
  长场）：全量夹具已恢复（914 行账待 860 全绿后一次 `--compare-only` 合并出账）；
  54 场陈旧产物已清；通道待重启（届时 `--force --cases <54> --skip-fixtures`，
  清单 output/_recovery/excluded_long_cases.json）。offpeak-06e4dc89 任务面=
  860 快速腿的 153 红处置，与长场无关。

## 5d. offpeak-06e4dc89 十二面定性战报（2026-10-31 晚）

**单场语义定性器批量结果（18 样本场，全部 REAL-DIFF——上轮 p1「残留态」解释
只适用 run605 类少数场，153 红绝大多数=gd 真实引擎差，语料 12/18 场≡oracle
单场=干净可比基准）**。逐面三态：

1. evt109@151-400 ×30：⏸混合——run633 fd@215（对手 LG blind ty109 timeout
   缺发）/run622 fd@276（FFR miss 判定）真实差；run605=残留态（上轮已证）。
2. evt109@401-1200 ×13：⏸真实差——run702 语料短(3590)=60s 截断场；run823 三数
   同(3615)三字节异。
3. evt109@51-150 ×7+×2：⏸真实差——run688 fd@131 三方三值；run726 三数同三字节异。
4. evt1@1-50 ×11：⏸真实差——run1084 语料 3803=截断场（gd/oracle 单场均 5579
   同数异字节）；run1086 语料 2499 截断。
5. evt1@151-400 ×9+@51-150 ×9：⏸真实差——run595 fd@187 SVP lifesteal 链
   （gd 缺 heal 段转 PF 108）；run628 fd@105 FFR oracle 命中11 v gd Miss。
6. evt1@401-1200 ×7：⏸真实差——run579 fd@595 SVP heal 三份97（oracle 双份
   49/97）。
7. evt0@151-400 ×7+×2：⏸混合——run601 fd@186（gd 缺 Battery@5.0167 再激活=
   EB 接力域，p5 修复后需重验）；run1283 fd@198/run1130 fd@502。
8. evt108 ×10：⏸真实差——run578 fd@80（gd 缺 Storage Coffin ty108）/run590
   fd@208（SPF 双发 t=4.9833 v gd 4.9667=**1 tick 早**）/run597 fd@161（同
   SPF 1-tick：3.9667 v 3.9500）/run981 fd@231（gd 多 Coffin ty108）——
   **SPF/PF 触发时刻 1-tick 差=独立签名族**（f11 注册表模型的残余 corner）。
9. evt19@1-50 ×5：⏸真实差——run1128 同数异字节（prefix 到 1022 全等=尾部差）。
10. evt105 ×8：⏸真实差——run1101 fd@172（同拍 PM 105/13 v Thunder Drake 攻击
   序）/run947 fd@6（**开战期 Rainbow Potion 栈施加序**：oracle 105/20/105/
   104/103 v gd 105/20/103/105/101）。
11. evt103 ×4：⏸受阻（f07 域继承）——run594 深挖：两侧 SVP heal 前 13 笔逐
   值同时刻全同；分叉=15.917 Frostbite31 oracle 无 SVP heal（curLifesteal=0）
   而 15.75 的 ty103 add 已发生——add 时序与 heal 判定归属歧义（own1/own3 分
   桶仍有矛盾），两连证伪接近即停；f07 材料（infer_cur.py+u_align2.py）完备
   可续，下轮用活体探针逐实例追踪 lifestealTimer。
12. evt102/12/101 小簇+py-only：⏸真实差——run597 fd@161（归面 8 SPF 1-tick）/
   run981（归面 8 Coffin）/run1104 fd@155（**Coil 栈转移类型**：oracle
   101(-2)/101(2)/104(-1) v gd 105(-1)/105(1)/101(-1)）/run1151 深挖=**py 真差
   落点**：Yggdrasil Leaf heal amount 29(py) v 24(oracle/gd 同)@t=2.7667
   （f03 heal 分支截断的 py 转写残缺，id/type_name/parent 偏移系序列化化妆品
   已被 canonical_stream 归一）；run1128 同法待查（prefix 1022 全等）。

**★ GemSocket 化石发现（面 12 副产品，重要）**：gd_core_test/OracleAlignBattle.gd::_j
与 simulator/gd_core_engine.py 两处 gem origin **硬编码 "GemSocket2"**——其依据
（旧语料 21164/21164 全为 GemSocket2）系**旧批内残留态化石**（前场残留 socket
节点挤占 Godot 自动命名）；新语料全扫=动态命名分布
{GemSocket:12543, 2:6266, 3:952, 4:101, 5:38, 6:38, **1:667**}。
待办：两处 dump 需按「宿主物品第 N 槽→节点自动名」动态化（或 canonical 层把
host.str 归一——比对口径不应被节点命名噪声劫持）。当前 gd 腿 PASS 说明
_origin_canon 已容忍该差异，py 腿红另有真因（见上 run1151）。

**签名族归并（供下轮立项）**：A.SPF/PF 1-tick 触发差（590/597/594 邻域）；
B.SVP lifestealTimer 生命周期（595/579/594，f07 域）；C.FFR accuracy/miss
（628/622）；D.开战期栈施加序（947/1104）；E.Coffin 触发有无（578/981）；
F.Goobert blind 到期缺发（633）；G.同拍物品激活序（1101）；H.尾部/渲染行差
（1151/1128/726/823）；I.截断场×5（1084/1086/702 语料短——60s 墙钟产物，
随重录收割）。

## 6. 交付口径与收口

- 唯一出口 alignment.json（914 行、perCase 保序）；三方全对齐=914/914。
- **914/914 达成时收口**（P4 协议）：①全量 `--compare-only` 复读确认；②`r55`
  快照（alignment.json+语料目录 md5 清单落 output/_recovery/）；③本台账加收口节
  （最终基线/修复总账/遗留禁区）；④np24_fix.md 留档；⑤明确向用户声明。
- REG 九场任何一轮退步即回滚肇事 commit（铁律 8）。
- commit 格式 `np25修复X：…`；push 由主会话统一（用户指令）。
- 禁区：README.md（主控在途）、语料再写（需用户批准）、P1-1 收缩版（同）。

## 5e. offpeak-735ad54f 九签名族战报（2026-10-31 深夜）

**开工**：REG 守门 np26a0 7 绿+run695（54 长场清单成员，不在 860 账）/run1514（快速腿基线红）——无退步。run695_r18 实为 54 剔除清单成员（25029 事件），其守门红与 860 无关。

- **杂项 GemSocket（9c79ed19）**：canonical 双层（_origin_canon 只取 host_identifier/socket_index、render_lines 走 canonical 元组）实证**均不消费 host.str**——归一路线=占位字面+实证注释（gd _j/py verify_oracle 两处）；新语料 80 场抽样分布 {GemSocket2:1704, GemSocket:931, GemSocket1:382, GemSocket3:56}、socket_index 恒 -1；台账 §5d 旧分布数字（含纯数字名）与抽样不符按实证修正；**simulator/gd_core_engine.py 并无硬编码**（_origin_key 已动态，台账该条记录有偏）。py 内核真值 _OriginRef(host_key,slot) 不可写 host.identifier（会破坏三方元组等价）。
- **族 A SPF/PF 1-tick ✅（3b31b638）**：**f11 multi 分支漏写 _eng**——multi 停止态 start 的 `_left=wait_time` 直赋后同帧 tickTimersPass 里 eng(0.0)==_seen(0.0) 走递减分支=登记拍同帧递减恒早 1 tick（f01 的 _started_frame 机制在 f11 退役后未补 eng/_seen 等价物）。修复=multi start 补 `_eng=wait_time`+**_multi_start_time 相位锚**：start 发生在 tickTimersPass 之后（EB ChargeTimer=charge_emitted 回调链）时下一拍登记拍照常递减补 1 拍（语料事件 t=(fire拍-1)×dt combatTime 落后 v gd=fire拍×dt 领先，口径差吸收）；同拍 start（SPF poisonTimer=character_healed 链）登记不递减。**验证 np26fa3 ALL PASS 8 场**：run590/597 SPF 层+run1160 EB 相位锚+REG 6 场。SPF tscn PoisonTimer 挂 MultiTimer 脚本（multi_timeout 连接）实证。fd 探针材料 output/_round_patches/np24_fix/fA_probe/。
- **族 H py 转写 int 整除 ✅（9dd78493）**：run1151 Ygg heal 29v24 定谳=**GDScript int/int 整除 v Python 真除**——gd manaUsed(int 推断)+=-int 信号量→_div 等价整除→activations 恒 int（heal-in 恒 20）；py 事件 amount=float（mana 系统 float 化）→manaUsed 浮化→activations 1.2/1.4 浮动→heal 29/34/24 波动。YggdrasilLeaf.py 累计点截断回 int。验证：py 单场（新 gd order）formal-tuple 584=584 逐位全同≡语料。**run906 在 54 剔除清单**（py-only ×2 的另一半随长场通道）。
- **族 B SVP ⏸ f07 区即停**：run594@384 定性=gd curLifesteal 累积未清（damage31 吸血 heal11=35%×7 笔存量）v 语料不 heal——**canApplyLifesteal 两侧逐字同构、SVP 逻辑同构而行为分叉**=f07 已两连证伪域（台账纪律即停）。SVPT 活体探针（timeout/trigger 全序列）已存 f07_probe/StrongVampiricPotion.svpt_probe_note.gd.bak。run595@480=SDP 六连净化组缺失（Amulet 域，归族 D）。
- **族 C/G roll 域 ⏸**：run628@105=**Miss 判定差**（语料 ty1 damage11 v gd ty3 Miss+ty101 lucky）；run1101@172=**同拍序+暴击 roll**（gd damage10=5×2 暴击 v 语料 5）——accuracy/crit roll 链位差，与族 D 的 rollChance 同域（chanceRng 独立链对位是共同前提）。
- **族 D Amulet rollChance 链 ⏸（材料最全的待续面）**：run597 SMP 二喝/run595 SDP 净化组=**Amulet onPotionEmptied→rollChance→potionTriggerTimer(multi, delay=2.5 实证)→triggerNextPotion** 链。4 轮探针实证：gd@4.3833 roll=T→fire@6.8833；语料 SMP 二喝@同拍 4.3833（par-1 形状=triggerPotion() 无 event）——**roll 值序列差待 chanceRng 逐抽对位**（语料无 rollPercent 日志，需 oracle 侧取证桩六步）。947/1104 开战栈序本轮未深挖。
- **族 E Coffin 对偶签名 ⏸**：run578@80=gd **缺** 2.4167 ty108 毒（Coffin 缺发）；run981@231=gd **多** 6.55 ty108（多发）——触发判定差的对偶两面。
- **族 F Goobert blind ⏸**：run633_r18@215（注意 r18 非 r15，任务书笔误）=gd 缺 1.9833 ty109 -5（blind 到期 stack timeout 缺发）。
- **族 I 重定谳 ✅（定性作废）**：run1084/702/1086_r11 语料**全有 ty111 正常终局**（20.7s/40.0s/35.75s player 胜）——「60s 墙钟截断场」定性**作废**（§5d 笔误 run1086_r14 应 r11）；真实签名=**gd 终局时刻偏晚**（语料致胜击杀时 gd 同击未杀→战斗延长；winner 三方全=player）——上游引擎差（roll/curLifesteal/终局伤害链）修复后自然收敛，非独立根因。
- **守门补记**：run633_r15 不存在（夹具 914 无此 id），族 F 样本=run633_r18。

**本轮净账**：修复 2+杂项 1=3 commit（9c79ed19/3b31b638/9dd78493）；REG 零退步（np26final 7 绿+2 基线红）。**全量 --force 被用户叫停**（铁律 15）：alignment.json 保持 707/860 旧账未覆写；中断现场=gd 产物 588/914、py 533/914 半新半旧（**下次快速腿重跑前必须 --force 或删目标产物**，半新产物会被幂等跳过当现状）；夹具 914 完好。快速腿 860 刷新与长场通道均待用户指令。

## 5f. np26 挖掘轮战报（2026-11-01 凌晨；账面 712→715/860）

- **账面刷新（用户令）**：860 夹具+`--skip-fixtures` 幂等跑（中断跑产物新鲜度验证后跳过合法）→ 712/860；**py 腿全量重刷**（坏产物事件，见下）→ **715/860**（py-only 4 场翻绿 3，剩 run1151=gd_to_py 冲手补，a05b0774 源码级修复恢复）。143 oracle≠gdcore+1 混合=新签名族待修。
- **★ py 腿坏产物事件（机理存疑，已重刷兜底）**：fastleg py 腿写的 run1246 产物与单场复跑/探针不一致（961 v 1190 事件）——单场复跑、分片复跑、PYTHONHASHSEED 0/1/42、pyc 陈旧均排除；hashseed 无关；**py-worker 顺序/竞态未定谳**，全量重刷后未复现。**教训：py 腿产物可疑时先单场复跑再定性，防把坏产物当真差。**
- **★ gh env 铁律 16**：`gh.run(env_extra=)` **勿传 os.environ**——其中 APPDATA 键覆盖 gh 的 PID 隔离 → oracle 侧 history.db 拷贝 err=12（批量定性 31 场全灭两轮的根因）；传最小 dict（探针模式）。
- **★ PCG 引擎语义标定（重大基础设施，fJ1102 取证）**：gd/oracle 同 exe 实测——RandomPCG 推进 `state=state*6364136223846793005+inc`、**inc=2885390081777926815**（=2×标准 PCG inc+1，Godot 3.6 实测）；**randi_range(from,to)=1 步、输出接受语义无 pcg32_boundedrand 拒绝**（B 点实锤：输出 2554588096≥2^31 仍 1 步出 0=2554588096%4）；**randf_range=2 步**（53 位双抽，C/D 点实锤）。**PCG32 推演器**：output/_offpeak/_pcg32_walk.py（给定 state 可复算任意后续抽值/state）。
- **族 Coil ×10（真引擎差，run1102 定谳）**：语料≡oracle 单场（731 全同）→gd 独红@200。现场=Thunder Drake 打击后 Coil 三连偷：语料偷 106×2→105→104；gd 偷 106×2→**106→101**。**state 桩对位+PCG 推演定谳**：第二次偷抽共同前驱 state=-8602199838085342062（两侧全同至第一次偷+4 label 抽），oracle 侧在 EVENT flush 链内**多一个隐藏 randf_range（2 步，f=0.46907；0.9-1.1 域=0.993814/-10..10 域=-0.618577）**→gd 缺此抽→偷栈 pickRandomElement 拿到不同 index（oracle 2,1 v gd 3,0）。**隐藏抽调用点未定**（Amulet of Agility/Perpetuum Mobile/Puzzlebag T 响应链逐查无抽；RngSpy 全包裹破坏 oracle bootstrap 受挫）——**下轮：轻量 spy（只包 randf_range 不抓栈）+从 refund giveStacks 的 label 链反查**。取证材料 output/_round_patches/np24_fix/fA_probe/（oracle_Util/CoreRng pre_rstate.bak）+output/oracle/probe/fJ1102s+fJ1102gs。
- **族 Light Goobert blind ×23（临时红单最大簇）→ 已全量定性（31 场批，第三轮）**：**RESIDUE 17 场**（oracle 单场≡gd≠语料：run1020/1112/1128/1155/1168/605/665/668/726/737/745/771/774/801/823/913/992）→**语料残留态，重录收割待批**；**REAL-DIFF 14 场**（run1018/1038/1132/1171/595/622/633/688/702/717/718/747/971/1120）→真引擎差，签名 ty109/Crown/blind/Eggscalibur 域——与 Coil 偷栈域相邻（flush 链表现层抽缺失族）。定性产物 output/oracle/probe/fJbatch/。
- **取证桩全部还原**（oracle Util.gd/oracle_fight.gd 写循环/gd CoreRng.gd md5 三方一致）；BLND/state 桩的 gd 侧保留在历史 commit 可复用。

## 5g. np26 循环轮战报 I（2026-11-01；账面 715→733/860）

- **重录收割 ✅（用户「860 全绿」令=授权）**：17 残留态场删 events 重录（oracle_chunk 语义）——**16 场立即翻绿**（语料新=oracle 单场≡gd）+run771 补录（重录批 events 悬案消失一次，补录恢复）+run1120 重录后仍红（=真差非残留）。**账面 733/860**（REG 860 内 7 场全绿无退步；run1514/run695 基线红）。
- **py-only 快赢 ✅**：run1151 py 产物刷新（a05b0774 修复兑现）+1。**教训：py 产物可疑时删产物重跑 py 腿（勿拷 gd 产物冒充——pytmp 事故）。**
- **★ compare-only 无夹具过滤**：`--compare-only` 不走夹具过滤（select_cases 全量 914）——**正式账刷新必须走完整跑**（幂等腿跳过+自动 compare=860 行干净账）；compare-only 出的 913 行账含长场陈旧行，勿用作口径。
- **Coil 偷栈链终局定谳（PCG 全链自洽）**：rdiv_probe 的 `& 0xFFFFFFFFFFFFFFFF` 字面量溢出坑（GDScript 3.6 整数字面量>int64 行为未定义）→早前「引擎 1 步出 2」误判；**rdiv2（负数字面量直传）实锤：gd 2961 输入 -8602→出 3；oracle 1132 输入 7014→出 2；7014=-8602+2 步——oracle 偷栈链多一个隐藏 randf_range（2 步，f53=0.46907114，域未定）**。spy 三连败（v1 Nil 风暴/v2 超时/v5 行为差）挂起（铁律 9）——**下轮：spy v6=独立文件即时写+时间窗+无栈+只包 randf_range**。
- **Burning Banner 簇 ×15（ty109）**：run1038 定谳=**doCooldownEffect→removeRandomBuffs(2) 的 pickRandomStacks 链位差**（自清 blind 1 层，语料 -1@6.8 origin=Burning Banner=removeRandomBuffs）——**与 Coil 同根因**（pickRandom 前的链位差）。防护链（cleanseProtection flip）排除（run1102 无 Banner）。
- **spikes 簇 ×5**：run1134=Snow Stick 攻击反伤 7 v 5——**victim spikes 栈数隐形差 2**（ty104 事件全同，消耗路径不可见差）——深井挂起。
- **Light Goobert ×20（fd 聚类新面孔）**：与已收割 17 不相交——**批量定性分拣中**（127 场，fNbatch）。
- **fd 全红聚类（127 场）**：LightGoobert ty109×20/BurningBanner ty109×15/spikes×5/Eggscalibur×5/FFR×3/poison×3/RubyWhelp×3/ChargeSplitter×3/Coil×6/长尾——**盲栈到期+pickRandom+隐形栈三大族**。

## 5h. np26 循环轮战报 II（2026-11-01；账面 749/860，剩 111 真差）

- **第二批重录 ✅**：定性批（127 场 oracle 单场分拣，fNbatch 并行 3 路 20 分钟）→**RESIDUE 16+REAL-DIFF 111**；16 残留态重录全绿 → **749/860**（累计 +42 自 707）。
- **fd 全聚类（111 真差，四大深井）**：
  1. **pickRandom 链位差**（Coil 偷栈 ×6+BurningBanner removeRandomBuffs ×15+LightGoobert 残余 ~17+spikes×5=**~40 场**）：PCG 全链自洽铁证=oracle 在 pickRandomStacks 前多一个隐藏 randf_range（2 步，f53=0.46907114）；**调用点穷尽未果**（handler/label/metric/snapshot/charge/localizeFonts 全查无抽）；**spy 系四连败**（v1 内类裸引用 Nil 风暴/v2+栈超时/v5 行为差 fd@10 AmuletSteel amount 3v2/v6 同败）——**铁律 9 硬停**。GDScript 3.6 坑：内类裸引用外实例成员=Nil；0xFFFFFFFFFFFFFFFF 字面量溢出。
  2. **格重叠 affected 判定**（Eggscalibur damage 40v30=P1(1)×affected 差 10——**10 格全灭**；Cupcake 与 Eggscalibur 同格 (3,3) 重叠）——A2 格真值面深水区。
  3. **charge 到达序**（ChargeSplitter 首充 activate 与 Coil gain 同拍序差；gd 的 _chargeEnterCell 简化 vs oracle 真实飞行）。
  4. **隐形栈数差**（spikes 反伤 7v5，ty104 事件全同）。
- **下轮攻击序**：①spy v7（先自证行为无害——单独 bare RandomNumberGenerator 对照实验定位 spy 行为差真因，再上）②格重叠井（Eggscalibur 10 格判定）③charge 序井 ④隐形栈井。**资产：PCG 推演器 _pcg32_walk.py+全链自洽方法论**。
- **取证现场**：oracle/Utility/Util.gd 已还原（pre_rstate.bak）；Coil 已还原；fNbatch 127 场 probe 保留 output/oracle/probe/fNbatch/。

## 5i. np26 循环轮终态（2026-11-01；749/860 收束）

- **Eggscalibur 簇改判**：双面 PAN 探针（oracle probe≡corpus 先验 ✓）实证**两侧 affected 完全一致（n=8，同 items 串）**——「格重叠井」排除；damage 40v30 的差=**randDamage 的 roll 链位差**（BalancedRange 裸调同构、独立链也走主链 PCG）——**与 Coil/Banner 同一「隐藏 randf_range 链位差」大井**（四井合一：pickRandom/roll 域 ~45 场）。
- **spy 系终局**：v6/v7 行为差根因未破（v6 fd@10 AmuletSteel amount 3v2；v7 卡死=抽间动态分派+IO 放大 2.5 倍致 240s 不足）；**A/B/C 对照实验（bare vs spy vs 带钩子）三等**——透传无害已证，行为差在 oracle 工程的更深交互。**教训链**：/tmp 路径在 Godot Windows=open 失败每抽重试卡死；内类动态分派全程减速 ~2.5x 需 timeout×3；GDScript 字面量 0xFFFFFFFFFFFFFFFF 溢出陷阱。
- **oracle/Core/Character.gd:812 [ADD-O] 桩=np 时代遗留未还原**（无害但违六步——下轮顺手清）。
- **终态账面 749/860**（本会话累计 +42：重录 33+py 修复 4+族 A/H 等）；**剩 111 真差聚焦一大井（roll/pickRandom 链位差 ~45 场）+charge 序+隐形栈+长尾**。
- **钥匙资产**：PCG 推演器（_pcg32_walk.py，常数已标定 inc=2885390081777926815）+全链自洽方法论+双面 PAN 探针模式（oracle probe≡corpus 先验）+定性批并行器（_classify_all_reds.py 3 路）。
- **下轮首攻**：spy v8=**预计算窗口内抽次+批次快照**（避免每抽 IO：仅记录窗口内抽值到内存数组、场末一次性落盘）；或 oracle 侧「state 哨兵」——在 Character.playAttackAnimation/activate/EventBus 等 5 个链上必经点加 state 快照桩（≤10 行×六步），与 gd 同点对照把隐藏 2 步夹到函数级。

## 5j. np26 EVENT 哨兵突破（2026-11-01 凌晨）

- **EVENT 行 state 哨兵一击定谳**：oracle CombatLog.logEvent 的 EVENT 行+gd trace_event 各附 rng.state（六步，已还原；gd 写循环改全行 join 兜底——固定列格式化在抽行第 3 行崩且原因未明，join 零风险已入库 OracleAlignBattle）——**同 index EVENT 对照（run1102）：EVENT 197/198/199（ty1/106/106）两侧 state 全同；EVENT 200 分叉（gd ty106 st=8908…v oracle ty105 st=8729…）**——**隐藏 2 步 randf_range 锁定在「第一次偷的 +2 事件 flush 完成后 → 第二次 stealRandomBuff 的 pickRandom 之前」= charge 飞行/到达段（ElectricalCharge 移动→下一 cell→chargeReceived）或该段 handler**。
- **下轮首攻**：oracle 的 Item.chargeReceived/ElectricalCharge cell 切换点加 state 哨兵（1 行×六步）+gd 的 chargeReceived 同点——把 2 步夹到 charge 链的具体函数；**ElectricalCharge.gd 此前 grep 无 randf——嫌疑=charge.start/_physics_process 的粒子/位移或 chargeReceived 的某个默认实参抽**。
- **修成杠杆**：pickRandom 域 ~45 场（Coil×6/Banner×15/LightGoobert 残余/Eggscalibur×5/spikes×5——Egg 簇已改判入本井：双面 PAN 探针实证 affected 一致 n=8，damage 40v30=roll 链位差）。

## 5k. np27 charge 时序机方案定谳（2026-11-01）

- **Zap 抽已证**：oracle 隐藏 2 步=Zap.gd:32 randf_range(4.0,4.02)（f53=0.46907114→4.00938 域匹配），触发=charge 换主（ElectricalCharge.onNewCellEntered 的 curChargedItem 变更后）。
- **gd 单 cell1 模型+盲插 zap ✓已有**；**全 cell 瞬时循环化失败**（fd@1——oracle 的 cell 推进是跨物理 tick 的 tween 时序：halfCellDur=0.5×dur/(cells-1)，每 cell 间隔=duration/(cells-1)，非同拍）。
- **正确方案=CoreElectricalCharge 时序机**：charge 对象带 progress/cells/inv_cells 状态，physicsTick 按 dt 推进 cellIndex（每跨 cell 阈值→_chargeEnterCell(cell)+换主判定+zap），duration 到→returnToObjectPool。**工程量 1-2 小时**，REG+charge 场全量回归必跑。
- **下轮实现要点**：①CoreElectricalCharge 扩 progress/inv_cells/duration ②CoreCombat.physicsTick 的 charge 步骤（activateItems 后）③sendCharge 只建 charge 不瞬时进 cell（cell1 由首个 tick 推进）④seek/replaying 分支（录音带场景）注意。

## 6a. offpeak 最终任务书（860 全绿收口；2026-11-01 移交）

> 本节=**下一棒 offpeak 的完整任务书**。现场已核：夹具 914（收缩用 §5c 清单）、
> 无 godot 孤儿、探针全还原（oracle Util/CombatLog/Pan + gd CoreItem/Coil/Pan
> md5 三方一致）、OracleAlignBattle join-all 已入库（eaea5fe1）、
> oracle_fight.gd 工作树含未提交的哨兵写循环扩展（无害，勿回退勿提交）。

【账面】749/860 绿；剩 111 真差，**主井=roll/pickRandom 链位差（~45 场）**。
【首攻=charge 时序机（§5k 方案，杠杆最大）】
1. CoreElectricalCharge（CoreItem.gd:2072 内类）扩状态：cells/inv_cells/duration/
   cell_index(progress)/emitter。
2. CoreCombat.physicsTick 加电荷推进步骤（activateItems 后）：按 dt 累计，
   每跨 halfCellDur=0.5×duration/(cells-1) 推进一格 cellIndex→
   _chargeEnterCell(charge, cellIndex, inv_cells)（换主判定+zap
   randf_range(4.0,4.02)+chargeLeft/Received 全在既有实现）。
3. sendCharge 改为：只建 charge 注册+音效 4 步（-12,-5 与 0.7,1.3 保留）+
   **立即同步 _chargeEnterCell(cellIndex=1)**（对齐 oracle start 的 i==0 同步分支——
   这是大量绿场的既有语义，勿丢）。
4. duration 到→charge 出清（cur=null 收尾对齐 cellIndex==size 分支）。
5. 验证序：单场 run1097/1102/1107 → 同簇 run1103/1104/1105/1106/1108/1109/1163
   → REG 8 场 → 860 夹具收缩（§5c 清单）+`--skip-fixtures` 完整跑刷账。
6. 预期翻绿：Coil×6/Banner×15/LightGoobert 残余/Egg×5/spikes×5 ≈ 35-45 场。
【次攻】新索单逐簇：同一「roll 链位差」签名继续用 charge/事件哨兵法；RESIDUE
新发现继续重录（已授权至全绿）；Eggscalibur 同款 affected 探针法已证伪格井。
【铁律】§0 全部+§5f-5k 教训（gh env 勿传 os.environ；幂等三杀；GDScript 三坑；
spy 系五败勿重蹈——新探针先自证 probe≡corpus；每井 ≥1 commit；账面刷新用
完整跑勿 compare-only）。
【退出】860/860（REG 全绿+账面确认）→ 夹具还原 914 → 收口协议（§6 P4）→ 战报。

## 6b. offpeak-b16489cf 循环轮战报（2026-11-01；账面 749→752/860）

- **zap 破案 ✅（0fa3be1a，本轮最大成果）**：**ThunderDrake.zapItem 的 Zap rng 消耗被转写剥除**（Zap.gd:32 randf_range(4.0,4.02)=2 步/次）——EVENT state 哨兵+GCOIL/ZDBG 双桩定谳（oracle COILR#1 st=3941→偷×2→zap→7014→COILR#2；gd 无 zap 直通-8602→偷2 pick(3,0) 选错栈）。**修=补 ctx.rng.randf_range(4.0,4.02)（表现层照剥）**。验证：run1103/1108 PASS 翻绿、run1102 fd200→205、run1104 fd155→180；REG np28z1 零退步；860 全量 --force → **752/860**（py-only 清零）。
- **方法论闭环**：oracle Coil.onChargeReceived 入口哨兵（COILR 行带 state）——**一次跑把隐藏抽夹到函数级**（zap 在 COILR#1 与 COILR#2 之间、量=2 步、域 4.0-4.02 三重匹配）。**同类剥抽排查清单**：zapItem 系（ThunderDrake✅已修/MechaBat/ElectricTorch/Gigawatz——同款 hasOnChargeReceivedEffect+zap 结构逐个 grep Zap 场景调用）；lightningMultiplicity 的 reduceSpeed 链。
- **剩余 108 红簇清单（下轮）**：LightGoobert ty109×16+Banner ty109×13=**盲栈 timer 清算份批域**（np25 ntp 守卫后的残余——temporaryStacks fire 次序/量差，建议 temporaryStacks 全生命周期 state 哨兵同法）；spikes×5（隐形栈数差）；ChargeSplitter×5（charge 到达序——§5k 时序机方案仍有效）；FFR×3/poison×3/Egg×3（roll 链位残差）；PM ty105×3（refund round 边界——zap 修复后的下游推进）；长尾小簇。
- **现场**：探针全还原（Coil/CoreItem git checkout+两树 md5 一致 4b108afc）；夹具已还原 914；ZDBG/GCOIL 桩已撤。

## 6c. 108 红完整攻击序（2026-11-01 发掘；752/860 基线）

- **发掘方法**：alignment.json 108 红全量按 fd 处 origin 物品聚类（74 簇→4 井）→ **新鲜 oracle 单场重放定性**（`output/_offpeak/_classify_108_fresh.py`，fPbatch，RESIDUE/REAL-DIFF 分流=op4_classify_108.json）。
- **攻击清单（机读）**：`output/_offpeak/reds108_attack_manifest.json`（井/证据/机制/方法/攻击点/代表场/循环与退出协议）。
- **W1 盲栈 temporaryStacks 生命周期域（最大簇 ~21-31 场）**：t109 amount 差（ora -7 v gd -6/-5）=批次边界/timeout 值差/漏 gain（Banner rollChance 抽）。方法=BLND 全生命周期哨兵（oracle [BGAIN]/[BEXPIRE] 与 gd _blnd_snap trace_diag 均已在树；py _py_blnd_probe.py 模式）。代表场 run622_r15（三方三值）/run633_r18/run876_r18。
- **W2 charge 电荷级联域（~16 场）**：**窗口证据定谳（run1097_r18 fd279）**：oracle CS 激活 t=314→Coil 收电 t=320（6 tick 电荷飞行）；gd 同 tick 瞬时收电（Coil t104 提前、CS t0/Mana Orb 缺位）——**§5k 时序机（CoreElectricalCharge progress/inv_cells/duration + physicsTick 推进）实证必需**，辅以 COILR 哨兵逐场定位（run1130_r14 型=gd Battery 激活缺位）。
- **W3 roll 链位域（~30 场）**：t1 damage 值差（Egg 40v30/20v15 同比 4:3、spikes 7v5/8v6 CanCrit、poison 16v8、FFR/HolySpear/武器单发）。方法=zap 同款：damage 事件 state 哨兵（前事件 state 同+本事件值差⇒两抽之间隐藏抽）+_pcg32_walk.py 回推。剥抽排查清单：MechaBat/ElectricTorch/Gigawatz。
- **W4 次序型单发域（~40 场）**：按机制二次聚类（StorageCoffin×3 延迟释放/ManaOrb 系×4/Amulet 系×3…）逐域小哨兵。
- **★ op4 定性终谳（fPbatch 108/108）**：**RESIDUE=0**（残留态已收割尽，无免费翻绿）；**REAL-DIFF=107**+run1104_r18 no-probe（oracle 重放未出 events，归 REAL-DIFF 池）。**新发现=29 场双分歧**（corpus≠oracle 且 X≈fd_og：run996/702/747/727/1167/996 等）——语料是 76e2d76d reset 修复**前**批录的（跨场残留仍在事件流里）；这 29 场在引擎修好后**必须重录**才可能翻绿（重录协议进每口井收尾，非独立收割）。78 场 corpus==oracle(sg) 修 gd 即翻绿。产物：output/_offpeak/op4_classify_108.json。
- **循环协议**：每井修复→gd_to_py 三树同步→REG gate（7 核心场+域代表场；run695/run1514 基线红）→860 收缩刷账（verify_oracle --skip-fixtures --force）→新索单聚类回流队首。
- **退出协议**：860/860 全绿→夹具还原 914→P4 收口（--compare-only 复读/r55 快照/台账收口节/战报）→停止。

## 6d. offpeak-db0c6696 循环轮战报 I（2026-11-01；W1 破案+13）

- **W1 盲栈碰撞语义破案 ✅（8d8324ac）**：`CoreBuff._tick` 停止分支补 `_timer_left=-1.0`（对齐 oracle drive_timers:889-891 **停止期每帧 e[0]=-1**）——此前批A dispel→stop 后遗留运行中值（1.98），下一批同 dur start（LightGoobert/Banner 恒 dur_blind=3）走 eng==seen 碰撞分支减的是遗留值 → 不立即 fire。oracle 侧：stop 期间 e[0] 已=-1 → 同值 start 后 -1-dt≤0 **当拍 fire**。BLND 全生命周期哨兵定谳（fQ633：gain 时 stopped=True reg=-1、批A 无声消失=Stable Recombo dispel、fire=gain 同拍）。**语料 TO=gain+1tick 全序列铁证**。验证：W1 簇 19 场中 **13 场 oracle_sg≡gd 逐字节全等**（run633 fd215→999 残位转 poison 值差=W3）；REG np30w1g **双腿 14/14 全绿**；重录 9 场双分歧 SAME（876/826/727/1036/1075/1079/717/1132/1171）**9/9 三方一致**+4 场直接翻绿（999/1018/1038/1073）=**W1 净 +13**。
- **★ §5k 时序机伪命题定谳（fS1097 CHRG 探针）**：run1097 单场 76 次 onNewCellEntered **全部 idx=1**——受控神谕下 **cell2+ 从不发生**（tween 不驱动），run1160 实证复核成立。§5k「charge 跨 tick 飞行」模型废弃；W2 重定义为**激活/到达链细节**（run1097@320 的 oracle 序 CS t0→ManaOrb→Coil vs gd 序 Coil→CS=同 tick 激活次序+冷却进度链；run1130 Battery@473 缺激活）——需逐抽对位（rng_log）定位，非时序机。
- **运维铁律新增**：`verify_oracle --cases` **会改写夹具**（定向清单写回 oracle_align_cases.json）——每次 --cases 后必须 git checkout+重收缩；fPbatch 定性/批量验证后夹具曾两次被缩到 5/1 场（op4_full_w1 首跑跑歪根因）。

## 6e. 循环轮战报 II（2026-11-01；W1 刷账 766/860 + W3 破案）

- **W1 全量刷账 ✅**：**766/860**（W1 净 +14：9 重录+4 直接+1 连带）。94 红聚类：W3 roll≈28 / W2 激活链≈18 / W1 残余 blind 量差≈13 / W4 长尾≈35。
- **W3 破案 ✅（2c39b3e5，spikes 簇 3 场全等）**：**CoreTimer.start() multi 停止态重启的碰撞语义缺失**。哨兵链：①EVENT state 哨兵（oracle CombatLog.logEvent 第 8 列+gd trace_event 第 8 列）证 fd 前 state 双侧全同（rng 链零差）；②SPK 栈哨兵证 gd 的 Spikes 栈=7 正确；③SPKA applySpikes 桩证 spikeDam=7 正确；④SPKR changeDamageResistance 桩双侧对拍——**Echoing Battlecry 重放 LeatherHelm→onPreCombatStart→BuffTimer(MultiTimer).start(3)**：oracle 重启走 eng==e[1] 碰撞立即 fire（fW1134 SPKR 890/895 同 t=6.583 +25/-25 同拍抵消铁证）；gd 旧码 multi 分支 `_left=wait_time` 直赋冲掉 -1 遗留→3s 后才 fire→fd@7.67 p0 DR 残留 25→spikes 反弹 round(7×0.75)=5 v 语料 7。**修=multi 重启不直赋 _left**（交 tick() eng vs _seen 判定；f01 首启 _seen=0 恒走登记分支语义不变；np26fA 相位补偿保持）。
- **W2 范式订正（fS1097 CHRG 探针）**：run1097 单场 76 次 onNewCellEntered **全部 idx=1**——受控神谕下 charge 的 cell2+ **从不发生**（tween 不驱动）——**§5k 时序机=伪命题**（§6d 已录）。Battery 多次 t0=Echoing 重放链（run1130：Battery t0@0/301/473/503/679/727=Echoing 逐次重放 combatStart→emitCharge→activate）——gd 的 Echoing@473 未触发=affected.size/speed 面差（W4 域）。
- **方法论沉淀**：①EVENT state 哨兵双侧桩（oracle CombatLog.gd 第 8 列+gd CoreRng.trace_event 第 8 列）=W3 标配开场（fd 前 state 全同⇒差在确定性计算面非 rng）；②SPK/SPKA/SPKR 三层桩逐层排除（栈→applySpikes→DR）到单点；③SPKR 双侧对拍是「静默数值面」（无事件无 rng）的唯一观测窗。

## 6f. 循环轮战报 III（2026-11-01；W3 刷账 796/860 + 收割 809/860）

- **W3 全量刷账 ✅**：**796/860**（W3 净 +30：spikes 簇 3+连带 27——CoreTimer multi 重启碰撞修复波及全部 MultiTimer 场）。64 红重新聚类。
- **W1 残余盲栈破案定谳（fX622/fY622 BLC 哨兵）**：run622 型「O -7 v G -6」=**语料双分歧残留**（op4 的 29 场双分歧之一）——fY622 oracle 单场重放自身 fire 批=6（BLND fire p0 amt=6 + BLC pick_amt=7→partial 削 1），与 gd -6 全同；语料 -7 是 76e2d76d reset 修复前批录的跨场残留（上一场渗入 1 层）。**引擎已对，收割即绿**。
- **收割轮 ✅（+13 → 809/860）**：op5 分流（fPbatch 探针对比新 gd 产物——oracle 引擎未变、探针仍有效）：64 红=**13 HARVEST**（oracle_sg≡gd）+50 REAL+1 noprobe（run1104）。13 场删 events 重录→**13/13 三方一致**（688/718/747/971/996/1086/1167/1178/1233/1352/1361/1377/1447）。
- **剩余 51 红面（下一棒）**：50 REAL（fPbatch fd 位=output/_offpeak/op5_harvest_64.json）+run1104（oracle 重放无产物，先单独取证）。分域：W1 真差残余（run622@289/run1120@868）、W2 激活链（run1097/1101/1102/1105/1106/1107/1163/1280/1290…）、W3 roll（FFR/RubyWhelp/HolySpear/FlameWhip/Automanaton/Egg）、W4 长尾（StorageCoffin/Amulet/MrStruggles/RainbowPotion/Toad/Badger/Wand/MissFortune/Wolpertinger/CursedDagger…）。


## 6h. 循环轮战报 V（2026-11-01；W3 修复2+隐形抽定位法）

- **W3 修复2 ✅（984fbdce）**：`spawnLabel_native` 走 item 的**有状态槽位逻辑**（getNextFreeLabelPosition：5 槽 0.5s 窗、闲槽 randInBox(10,10)/全忙兜底 randInBox(30,30)）——此前无状态硬编码 2 抽 randf_range(-10,10)。逐抽 state 对拍定谳（run733 fd@87 锚后窗口：oracle 兜底 -30,30 vs gd 硬编码 -10,10）。run1129 fd310→59（推进 251 事件）；REG 8/8。860 全量刷账 809/51（fd 全面推进、暂无翻绿）。
- **★ 每抽 state 哨兵升级**：oracle rng_trace_range/irange/f/i 全部第 8 列附 rng.get_state()+oracle_fight fmt 的 e.size()>7 分支——**state 跳数法**（前行后 state→本行后 state 的 PCG 步数 vs 行类型正常步数）直接暴露隐形抽。PCG 常数定谳：INC=2885390081777926815（state 转移验证）、randf_range/randf=2 步、randi_range/randi=1 步（裸 Godot 3.6 实测）。
- **BalancedRange 定谳**：oracle Utility/BalancedRange.gd:14 `Util.rng.randi_range` **裸调不入账本**=伤害掷点隐形 +1 步/次；gd 侧 kernel_r5 已同构（CoreRng BalancedRange 裸调 `_rng.rng.randi_range`）——**两侧同构非分歧**。
- **W3 真分歧=每伤害帧一次隐形 randf_range(+2 步)**：run733 锚后窗口 oracle O424（受击动画 playback_speed 抽）→**+2 隐形**→O425（冷却 jitter）。gd 同区间 0 隐形。调用点未定谳（oracle 裸调用检索无果：playGlitterSound 死代码/Game.gd 装配段/Character._physics_process 均排除）——下轮：①给 oracle Item._physics_process/冷却 tick 路径补临时 state 桩二分；②或 ORACLE_ROLL_STACK 环境窗打印栈（Util.roll 已有 [ROLLSTACK] 钩子，60s 窗改到 fd tick）。
- **W2 方案 A/B/C 不变（§6g）**：三件消失之谜（gd p1 的 Coil#2/ManaCrystal/AmuletOfDarkness 装配后静默消失、非 moveItem 路径）+ affected 格序（TileMap 涂格序 v yx sort）。
- **op6 分流**：51 红=fPbatch 探针对新账面 gd 全 REAL（0 HARVEST）——残留态已彻底收割尽。
- **★ W2 序来源定谳（本轮突破）**：两场实测矛盾调和=**涂色路径分来源**——①1097 的 T Lightning 格=tscn tile_data **静态涂色**→oracle 序=x 升分组、组内 y **降**（[(1,0),(2,1),(2,0),(3,2)...]=Godot tile_data 存储序）；②604 的 ManaOrb Primary 格=**运行时涂色**（onPrepare 动态 set_cell）→涂色循环序=y 行优先 x 升（[(5,3),(7,3),(5,5),(7,5)]，与现 sort 的 yx 升巧合匹配→604 绿）。**夹具 affected 数组序已被 extract_grid parse_tile_data 末行 sorted([x,y]) 破坏**（f09 时发现未深究）——gd 侧透传夹具序≠真 tile_data 序。**下轮修复**：①extract_grid 重提取 tile_data **原始文件序**（去 sorted）→夹具再生；②gd getAffectedCells_tilemap 删 sort 透传（静态涂色场=tile_data 序 ✓）；③运行时涂色场（ManaOrb 系）gd 需补涂色路径（onPrepare set_cell 循环序=oracle 同构）或保留 sort 仅对该面。**1097/1105 等 Lightning/T 静态场预期翻绿**。
- **op7 复分流 ✅**：新 gd 账面（spawnLabel 修复后）对 fPbatch oracle_sg 再分流——**仍 0 HARVEST**（51 红全 REAL 确认，无免费收割）。
- **W2 序之谜实证矛盾（比较子实验）**：比较子改「x 优先、同 x y 降」→run1097/1105 **SAME ✓**（W2 突破！）但 run604 退步（f09 面）；f604aff 实测 ManaOrb 序=[(5,3),(7,3),(5,5),(7,5)]=y 行优先、组内 x 升——**两场 oracle 序规则不同**（1097 的 T Lightning=x 组 y 降、604 的 ManaOrb Primary=y 行 x 升），与 RB 树遍历恒序定理冲突⇒TileMap 内部序与涂色路径相关（tile_data 初始涂色 v 运行时涂色）。**回滚比较子保 f09 的 16 场**（604/827 复验 SAME ✓）；1097/1105 的序真值下轮实测 tile_data 文件序定谳（ AFFC 桩已可复用）。**关键更新：三件消失之谜已被 spawnLabel 修复连带解决**（T150 dump：gd o 侧 (4,2)=Coil/(5,2)=ManaCrystal/(6,1)=AmuletOfDarkness 全在——修复前 AFFM 的 null 是链位错位的下游）。
- **★ W3 隐形抽值反推定谳（本轮）**：randf_range 消耗模型定谳=**每抽 2 步：第 1 步弃、第 2 步为值**（run733 锚后 out[1]/2^32=0.517482=424 值 1.003496 的 f ✓ 6 位精确；out[5]=0.700327=425 值 f ✓）。隐形抽=outs[2](弃)+outs[3](用)→**值=0.738357（(0,1) 归一）**；若域 (0.9,1.1)=1.0477、(0.9,1.0)=0.9738、(0.975,1.05)=1.0033、(0.95,1.05)=1.0179——与全部已知裸调域（grep 全量 12 处）的语义位置（受击动画→下一 trigger 之间）无匹配⇒**该裸调不在 gd 源码 grep 面**（嫌疑：oracle 场景树某个 .tscn 内联脚本/信号回调）。下轮：①用 v=0.738357 对照 425 后续每抽值找同源二次出现（若每伤害帧一次则值序列可交叉验证调用者身份）；②Instrument Util.flip 的调用方日志。
- **W3 隐形抽终局方案（下轮执行）**：oracle Util.gd 的 `var rng` 换**追踪包装器**（class RngTrace extends Reference：base=RandomNumberGenerator，randf/randf_range/randi/randi_range/get_state/set_state/seed 全方法代理+每次调用 push log（tag=RNGX））——一次性消灭「裸调不入账」盲区，隐形 +2 的调用点一次跑现形。风险面：grep Util.rng 全方法面覆盖后替换；ORACLE_DEBUG 门控（非 debug 走裸 rng 同一对象）。MARK 桩法（Character takeDamage A/B/C 点）已试因『isOpen on Nil』偶发崩溃弃用（桩已撤净，原因未定谳疑与长跑节点复用相关，下轮可再用短跑）。
- **现场**：oracle 探针（rng_trace_* state 列+fmt 分支）**仍在树上未还原**（下轮直接复用）；gd 侧无探针残留；夹具=860 收缩版。
## 6l2. 循环轮战报 IX 收官（2026-11-02 14:00；session 净 +25：809→834）

- **三笔修复两净正一教训**：
  1. **isAvailableFor 位变换（aac9e02f）净 +6**：stuffClassIndex(1<<classId) 缺失→isClassItem(职业) 全拒→PM 簇 6 场（1101/1102/1280/1290/1331/1530）。
  2. **checkTriggerCount 进程钟语义（3f9b605a）净 +13**：oracle Util.time 进程钟起点 42s>limit=10 恒真=恒过；gd 战斗钟 0 起前 10s 永久熔断（run899 MS 133 进 5 发 v oracle 27 发）→+40s 偏移复刻。翻绿：578/618/628/775/846/848/899/933/981/984/1487/1491/1507。
  3. **checkActivationLimit +40s（f549874d）净 -45 → 回滚（b5876136）**：量纲分析教训——checkTriggerCount 的 count 上限(10)<进程钟起点(42) 恒真成立；checkActivationLimit 的 lastActivationTime 是**移动基准**（每次激活更新为当前时刻），同 tick 第 2+ 次 time==基准走 else=oracle 真熔断，+40 偏移误改。op19=789 → 回滚 → op20=834 复确认。
- **★ tick1diff 簇（9 场）定谳进展（BTC 桩，2026-11-02 晚）**：run1253 Badger 双侧每 tick triggerTime/spd 桩对拍——rng state 序列全同、jitter 全同，但同战斗时刻 gd 的 tt 比 oracle **少减 1 次**（差=0.016667×1.12=一次完整递减），分歧起点=速度变更边界（combat t≈1.5667 减速生效拍）——**「变更拍是否用新速度递减」两侧语义差**（oracle 变更拍仍用旧速度；gd 当拍即用新速度）。9 场 tick1diff（760/1118/1163/1253 gd 早 1 tick；986 gd 晚；921/939/1540 级联）同根。**下轮修复**：physicsTick 递减用「本 tick 开始时的速度」快照（speed 变更延后一拍生效），REG+9 场验证。
- **★ tick1diff 根因精确定位（BTC 窗口起点对拍）**：减速窗起点——oracle 在 combat 1.55→1.5667 的递减**已用新速度 1.12**（tt 1.725413→1.706746，差=delta×1.12）；gd 在 1.5667→1.5833 才用新速度（1.690079→1.671413）——**Slime Time（PLR）的 reduceSpeed 生效拍差 1 tick**（oracle tick 1.55 生效 v gd tick 1.5667）→Badger 剩余倒计时整段偏 1 递减→激活差 1 tick。**下轮**：追 Slime Time 首激活时刻差的上游（其冷却相位/首ativation 链），或 Slime.gd 的激活语义（**1253 阵容实无 Slime Time——减速源候选=Time Melting**，其首激活时刻差/语义对拍留下轮）。
- **EATI 桩方法论升级**：oracle tick_battle ③⑤ 与 gd physicsTick ③⑥ 的 per-item EATI 双侧实现（临时桩已还原）；时差对齐后逐物品锁定首个消耗分歧——本轮定位 TeslaCoil.advanceItem（fb29b6a2 已修）+tick1diff 簇（本条）。
- **834/860（26 红）分域**：隐形抽族残余（733/846/933/1118/1427/1441/1499/1534/1536/1545）+W2 charge（1104/1163/1130 已绿）+W4（622/687/702/760/921/939/947/962/977/986/1022/1120/1253/1444/1499/1540/1514 基线）。
- **交接**：offpeak-2cbf06c9（§6j 任务书+§6k/§6l/§6l2 进度）。下一棒攻击序：①隐形抽值指纹（0.738357）②1104/1163 新 fd ③W4 逐场分流 ④914 全量合并。860 全绿后：README 重写→commit/push→超长场。
## 6k. 循环轮战报 VIII（2026-11-02；W2 正解入账 815/45）

- **W2 正解净账 ✅**：op14b 全量=**814/860**（净 +5：1097/1105/1106/1107/1269 翻绿，零退步）——文件序全链保序（aaeaf731）实效验证。**+收割 run1129（重录）=815/860**（--compare-only 合并）。
- **46 红重聚类（reds_op14b.json/reds46_cluster.txt）**：W3 隐形抽族（damage 值差）12 场=1441/1534/1536/1545/733/846/933/962/1118/1499/1507/1427；W2 charge 残余 8 场=1101/1102/1104/1163/1280/1290/1331/1530；W4 真长尾 22 场=578/618/622/687/702/760/775/848/899/921/939/947/977/981/986/1022/1120/1253/1444/1487/1491/1540；1514 基线红。run1104 no-probe 已补重放（corpus 新鲜，REAL@180 归 charge 残余）。
- **W2 charge 残余模式（1101/1102 窗口）**：oracle PM@201/255 激活（105+13+t0），gd 的 PM 缺位/迟激活——PerpetuumMobile.onPrepare 的 connectToCharacterBuffs(onBuffChanged)+character_used_stamina 连接面+doCooldownEffect 循环（usedStacks refund→giveStacks；giveStamina→activate）逐抽对位待做；1104=Djinn Lamp 101@250 v gd Mana Orb 105 次序差。
- **隐形抽定位暂停**（Healthbar/DamageMeter/Game.gd:4969 等排除，属商店面）——两轮对拍法（MARK 桩/全场扫描）均已证伪，值指纹法（0.738357 同源序列）留下轮。
- **下一棒**：offpeak-2cbf06c9 任务书（§6j 攻击序+本节更新）——①W2 charge 残余 8 场逐抽（PM 连接面优先，1104 次序差次之）②W4 长尾 22 场分流聚类 ③W3 隐形抽值指纹。860 全绿后：夹具还原 914→--compare-only 全量账→README 重写→commit/push→超长场通道（54 场 --force --cases 逐场）。
- **★ PM 面定谳（本轮收尾）**：run1101 全 PM 事件对拍——oracle 首激活@3.35 且激活间隔 0.13s（高加速）；gd 首激活@6.63 间隔 0.5s（无加速）——**gd 的 PerpetuumMobile.onPrepare addSpeed(speed×getNumAffectedItems()) 未生效**（affected=Engineer 色邻接，gd 侧计数 0 或夹具 affected 空）。攻击点：PM.tscn tile_data 的 Engineer 色 tid→夹具 affected 键→getNumAffectedItems 链。1104 的 DjinnLamp 101@250 次序差疑似同源（PM 激活慢→全场冷却链慢）。
- **op17 分流**：39 红=fPbatch 对比全 REAL（0 HARVEST）。
- **★ checkTriggerCount 修复 ✅（np33 修复2，op18=834/860 净 +13 零退步）**：oracle 比较基准 Util.time 是**进程钟**（战斗开跑已累积装配耗时 ≈42s>fW3fin 实测），time>count(≤10) 恒真=**limit 恒不熔断**；gd ctx.time 战斗钟 0 起→前 10s 恒 false→永久熔断。修=+40s 偏移复刻（全场唯一调用者 MrStruggles 零全局风险）。翻绿 13 场：578/618/628/775/846/848/899/933/981/984/1487/1491/1507。REG np33ctc2 双腿 18/18。
- **收割轮 ✅（op21 分流后）**：run622_r15 变 HARVEST（isAvailableFor/文件序修复后 oracle_sg≡gd）→重录翻绿；run1104 补重放（语料新鲜仍 REAL@180）。**账面=835/860（25 红）**。
- **进程钟语义面收官 ✅**：gd 全树 `ctx.time >` 比较逐个量纲核验（attack_sound_ready_time/buffLabelPositionTimestamps/lastActivationTime 均为相对间隔或移动基准=量纲无关；checkTriggerCount 是唯一 absolute-vs-count 错配已修）——进程钟面收割完毕。
- **25 红全部 gd≡py**（转写零分歧，纯引擎差）；op17 分流 0 HARVEST。**1104 窗口证据**（CHRG 桩 f1104c）：fd@180=gd 在 Coil 105 后多插 Mana Orb 105 tgt1（oracle 同位无此事件、Mana Orb 激活面/mana 链差另根）；**947 归档**：fd@6=Rainbow Potion giveRandomBuffs 选型（oracle 4 类型恰不重复 v gd 3 类型=抽到重复）=随机链位差（归隐形抽族）。**899 归档**：fd@39 已修（checkTriggerCount）。
- **★ 隐形抽精确到函数 ✅（EATI 双侧对拍，本轮收官突破）**：oracle_fight tick_battle 步骤③⑥ 与 gd CoreCombat physicsTick 步骤③⑥ 各加 per-item EATI 桩（physicsTick 前后 state 差时记 [idx,EATI,t,side+name,,time,,state]）→ run733 双侧 EATI 序列对拍（时差偏移 40.5 对齐后）：**前 15 行 state 逐位全同，首个分歧=PLR Tesla Coil 的 physicsTick**（O t=45.450 st=313172890116 v G t=4.383 st=114819286709——同一次 Coil 冷却 tick，oracle 多消耗/不同抽）。**隐形抽调用点=Tesla Coil 的 physicsTick→trigger→doCooldownEffect 链内**（Coil 冷却激活 stealRandomBuff/miniActivate 前后）。下一棒：对该 tick 用 COILR+MKT 逐抽桩（两侧）一步钉死行。
- **★ TeslaCoil zap 修复 ✅（op22=838/860 净 +3 零退步）**：advanceItem 补 randf_range(4.0,4.02)（Zap.gd:32 剥抽，np27 zapItem 同构）——翻绿 733/846/933（fd87/213/133 全消）。EATI 对拍法首战全胜（定位→修复→验证闭环 40 分钟）。
- **op23 复分流**：22 红全 REAL 0 HARVEST；**962 fd@83 在 t=0 激活期**（activateItems 链内非 tick 循环，EATI 不覆盖）——激活期隐形抽需独立通道（activateItems 链的 EATI 桩或 COILR 式入口哨兵）。
- **账面**：**838/860**（22 红：隐形抽族残余 947/962/1118/1427/1441/1499/1534/1536/1545、charge 残余 1104/1163/702/986/1120/977、长尾 687/760/921/939/977/1022/1253/1444/1540/1514 基线）。
- **隐形抽监听链排除（本轮收网）**：run733 阵容全部 EventBus 监听者（MrStruggles.onDamaged/Shield.onCharacterAttacked/CriticalPoison/Toad/FortunasKiss）逐个查证**零 rng**；Healthbar.onHealthChanged 无 rng（call_deferred updateBar 纯 tween）。隐形抽调用者只剩 tscn 内联脚本/动画帧回调两条暗路——值指纹法（0.738357）是唯一低成本剩招。
- **947 线索**：fd@6=Rainbow Potion 三色物品（Primary 覆写 getAffectedCellsAfterRotate_primary+Secondary/ Tertiary）开战激活链 buff 类型序差（oracle [105,104,103,101] v gd [103,105,101]）——多色物品的受影响序/连接序独立面，与 Lightning 面无关。
- **899 线索**：fd@39=t0 阶段 Snowball 给 blind 后 Mr Struggles.onDebuffed 未响应（oracle 同拍 t110 tgt=0 amt=2，gd 缺）——debuff 信号连接在 t0 激活链的生效时机差（连接于 onPrepare 装配期应已生效；疑 rollChance/ BalancedRng 首抽位差）。MSROLL 桩（gd trace_diag）可复用对拍。
- **isAvailableFor 修复的连带提醒**：该修复影响**全部** isClassItem(某职业) 判定（PM 系 6 场翻绿；其它职业判定物品——Crown/RubyWhelp 等用 Class 判定的——注意 REG 已 20/20 无退步，判定面此前恒 false 的连接现在开始生效，后续聚类若现新红先查此面）。
## 6j. 循环轮战报 VII+下一棒任务书（2026-11-02；W2 正解落地，860 全绿冲刺交接）

- **★ W2 正解落地（aaeaf731）**：「三场三序矛盾」终谳=**全部=tile_data 文件序**（此前 yx 排序/按色分都是误判）——①extract_grid parse_tscn_grid 保序（set→list，去 norm_cells sorted）；②gen_lineup_fixture placement_of 保序变换（去 set+sorted）；③三产物再生（battle_items+item_battle_fixture+LineupFixture+oracle_align_cases 914 场+lineups+gd_core_runtime——**铁律 12 全链一个不漏**）；④gd getAffectedCells_tilemap 删 sort 透传。实证：cases 的 T affected.3 序=oracle fAffC 实测**逐位同构**；**1097/604/827/1105/1106/1107/1130/1283 八场双腿 SAME**（f09 ManaOrb 面+Lightning 面同绿）；REG np32w2reg 20/20 全绿。
- **label 修复二滚定谳（2b88a742→331227b5）**：干净实验 op12（807/42，新退 0，翻绿 9 场中 7 场真绿）但四场 CS/Coil 仅剩 py 分歧=TD v2 桩破坏（撤 176b6f44 后三路复核 corpus_vs_gd 仍 279）——**无 TD 桩+文件序时 fd 回 279 的残余=无序干扰下的真链位差**，净 -2 出局。定谳事实保留：oracle LABEL 兜底分支真值、槽位逻辑（getNextFreeLabelPosition 5 槽 0.5s 窗）。
- **账面**：op13=809/51 基线复确认；**op14b 全量刷账（夹具再生后首次）运行中——预期 ≥816**（八场 SAME 入账+1163/1130 等推进）。
- **现场**：夹具 860 收缩版；三树一致（aaeaf731）；现役探针=EVENT state 桩两侧+oracle rng_trace 第 8 列（b499a6ab）；TD 无桩。
- **下一棒任务书（W3 隐形抽+W4 长尾冲刺 860）**：
  1. **W3 隐形抽（~15 场 damage 值差）**：隐形 randf_range(+2 步) 值=0.738357（(0,1) 归一，out[3]/2^32 反推 6 位精确互证），位置=受击动画抽(625)→下一 trigger 之间，grep 全量 12 处裸调无匹配⇒嫌疑 tscn 内联脚本。方法：①值序列交叉验证（多场多帧隐形值若同源可指纹识别调用者）；②oracle Util.roll 的 [ROLLSTACK] 钩子改窗到 fd tick+get_stack。
  2. **W4 长尾（~30 场）**：逐场 oracle 单场重放分流（≡→重录收割；≠→按机制聚类小哨兵）。StorageCoffin×3/Amulet×2/MrStruggles×2/GirlPower×2/MissFortune×2 优先。
  3. **1163 fd440/1130 fd157 等推进场**：W2 修复后的新 fd 面逐个哨兵。
  4. 每循环：修复→gd_to_py→REG（_np21_gate 8 场+域代表场）→860 刷账（--skip-fixtures --force）→重聚类→台账追记。
  5. **860 全绿后**：夹具还原 914→--compare-only 全量账→P4 收口（--compare-only 复读/r55 快照/台账收口节/战报）。
- **运维铁律**：verify --cases 改写夹具用后还原+重收缩；回滚提交 diff 校验全部 touched 文件；跨树 cp 验证目标内容；批量 oracle 重放逐场单进程；gh.run 勿传 os.environ。
## 6i. 循环轮战报 VI（2026-11-02；回滚链闭环，基线回归 809/51）

- **回滚决策链（全部闭环，REG 双腿 16/16+op11 全量 809/51 复基线）**：
  1. **W2 全局按色分（9c447568）净 -62**→回滚（84b2061e）；
  2. **TD 局部序桩**：cp 路径错未生效（gd 跑旧版）+py 版排序物品列表用 vec2 比较子崩（AttributeError x）→撤（3d7b1d21）；
  3. **label 修复（984fbdce）净 -51**（+4 CS/Coil 簇 1097/1105/1106/1107 vs -55 run615@363 型链位连锁）→revert（5a1da85f）；
  4. **★ 84b2061e 回滚漏 CoreUtil**（vec2_less_yx 残留 tile_data 序版=op10 747 真因）→三树恢复 f09 原版（846d237a）+py 缩进修补。
- **工程铁律新增**：①回滚提交必须 diff 校验**全部 touched 文件**（84b2061e 只核了 CoreItem 漏了 CoreUtil）；②跨树 cp 必须验证目标文件内容（TD 桩 cp 路径错被 `2>/dev/null || true` 吞掉）；③净评估以**全量刷账**为准（单跑 SAME+REG 绿不能外推全量）。
- **保留的正资产**：W2 序来源定谳（§6h 补4：tile_data 静态=x组y降 v 运行时涂色=y行x升）——1097/1105/1106/1107 四场在 label 修复存续期曾 SAME（其 fd 分歧面=TD zapItem 序×label 取位交互），回滚后重回 51 红池待（槽位历史对齐+运行时涂色路径）联合修复；W3 隐形抽值 0.738357+消耗模型（第1步弃第2步用）不变。
- **W3 逐间隙隐形对拍方法评估（本轮结论）**：全场 77/422 间隙有隐形、双侧对拍 351 间隙「分歧」——**绝大多数=两侧账本可见性差异**（gd 的 CoreRng.shuffle 内部 rng.randi 直调不进 trace v oracle shuffle=rng_trace_i 可见；oracle 裸调反之）——信噪比不足，**该法仅适用于「锚后单窗口小区间」**（fd 附近的 +2 定位即此法成功案例），全场扫描不可用。隐形抽调用点定位仍需：值 0.738357 的同源序列交叉验证或 debug 模板 get_stack。
- **账面**：809/860（51 红同 op6/op7 分域）。
## 6g. 循环轮战报 IV（2026-11-01；W2 激活链证据链+方案，转攻 W3/W4）

- **run1104 取证 ✅**：corpus==oracle_sg（语料新鲜）、REAL-DIFF@180（归 W2 Coil 域）。op4 的 no-probe 为偶发，重放正常。
- **W2 激活链证据链（fZ1097/fZa1097/fAffO2/fAffC/fAffM2 五轮哨兵）**：
  1. **EVENT state 哨兵**：fd@279 前 [276-278] state 双侧全同（5420...）——差在确定性计算面。
  2. **CS 的 t0 双来源定谳**：①doCooldownEffect→onAfterEffectFinished→**consume()→activate()**（冷却链，heat 够时）；②onChargeReceived→emitCharge→activate（charge 到达）。CSRX 哨兵 4 次=tick 320/547/841/1137。**fd@279 的 CS t0=CSRX 紧跟 ThunderDrake t1（row1277→1278）——触发者=ThunderDrake.zapItem→item.chargeReceived(self)**（zapItem 循环里逐件 chargeReceived）。
  3. **根因=ThunderDrake.getAffectedItems(Lightning) 的序+集差**（AFF 哨兵）：oracle=[DjinnLamp, MagiteccArmor, LightningStaff, **ChargeSplitter, Coil, Coil, ManaCrystal**]（7 件）；gd=[DjinnLamp, LightningStaff, MagiteccArmor, **Coil, ChargeSplitter**]（5 件）——**gd 的 Coil 在 CS 前**→zapItem 循环里 Coil 的 chargeReceived（steal 104×2）先于 CS 的 chargeReceived（emitCharge t0）→事件序分叉。
  4. **格集相同、序不同、命中差**（AFFC/AFFM 哨兵）：两侧 affected 格集=同 16 格；**oracle 序=Godot TileMap get_used_cells_by_id 原生序**（[(1,0),(2,1),(2,0),(3,2),...]，x 优先 y 乱序）；**gd 序=sort(vec2_less_yx)**（yx 排序，顺序必然不同）。**gd 的 (4,2)=Coil#2、(5,2)=ManaCrystal、(6,1)=AmuletOfDarkness 三格 null**（oracle 三格有件）。
  5. **摆放排除**（PLACE/MV29 桩）：gd 装配时三件 occ 正确+filledCells 命中（inv=True）；战斗中 moveItem/removeItem 对三件**零调用**——三格在装配后、AFFM 采样（tick150）前消失，**清空路径不经 moveItem/removeItem**。
- **W2 修复方案（下一棒执行）**：
  A. **三件消失之谜**：在 gd 装配尾部与战斗 tick1/tick150 各 dump 一次 p1 filledCells 全表 diff，锁定清空点（嫌疑：开战激活链中 inventory 重建、或某处直接写 filledCells/occupiedCells 绕过 moveItem）。
  B. **序对齐**：oracle 用 TileMap 原生序——gd 的 getAffectedCells_tilemap 的 `sort_custom(vec2_less_yx)` 与 oracle 不符；需打 oracle 的 TileMap 涂格原始序（tscn tile_data 序）与夹具 affected 数组序对照，让 gd 的 affectedTileCells 序=涂格序（去掉 yx sort 或改为涂格序）。
  C. 修后 affected 序→zapItem 循环序→CS/Coil 事件序全链对齐；REG+charge 域 9 场验证。
- **转攻 W3 roll 残余（~8 场）**：FFR（733/846/628）、RubyWhelp（933/1441）、HolySpear（1118/1322）、FlameWhip（1086）、Automanaton（1129）、Egg（1507）、单发武器（1534/1536/1545/1499/962）。同 spikes 的 DR/crit 确定性面模式（fd 前 state 全同），SPK/SPKA/SPKR 桩法直接复用。
## 6m2. 循环轮战报 X（2026-11-02 晚；offpeak-0bfcfee4 接棒，838→841/860）

- **★ tick1diff 簇（9 场）根因定谳 + 修复 ✅（841/860，净 +3：760/1163/1253 翻绿）**：**引擎 Timer real_t(float32) 量化缺位**。§6l2 两条约定矛盾（452「oracle 变更拍用旧速度」v 453「oracle 1.55 已用新速度」）经 SPDT 全物品 (tt,spd) 流复测裁决——spd 值流双侧逐位一致、分歧纯在**触发拍**：减速源=对方 Amulet of Agility（onCombatStart addSpeed(+1.0)→BuffTimer 超时 reduceSpeed(1.0)，2.12→1.12 精确 -1.00；Time Melting 是 modifyParam("dur",+0.55) 的 dur 乘数来源，非减速源）。[timer-fire-dbg] 铁证：oracle BuffTimer eng=**f32(1.55)=1.5499999523**，93 拍 e[0] 即穿零（e0 打印 -0.000000）；gd 全 64 位 93 拍剩 +5.5e-16 → 94 拍才 fire（[tfire] left=-0.016667 逐位吻合）。np25w_f04 的 f32 量化只补了 rage/invul/Buff 域，**CoreTimer（物品计时器）漏网**。修=CoreTimer._f32eng（PoolRealArray 穿针三行模板，np25w_f04 同款）：start() 两处 _eng、_onTimeout post-emit 三值全部过 f32；gd_to_py op11 自动转写 f32(x)。REG np29f32 双腿 19 场：7 基线全绿零退。**教训**：§6l2 的「speed 快照延后一拍」方案方向反了（会把 gd 推得更晚）——量纲分析先行救了一把；两树探针同步（gd_core_test/gd_core）本会话又踩两次，第 3 次起 cp 后必须 grep 桩名计数验证。
- **SPDT/TMR 桩升级为常驻基建（env 门控零耗）**：oracle_fight.gd _dbg_spdt/ORACLE_SPDT（tick_battle ③⑤ 全物品递减后 (tt,spd) 流，CT.combatTime 对轴）；gd_core/CoreCombat.gd _dbg_spdt/GD_SPDT（步③⑥ 同构，`_cooldown_active` 门=oracle is_physics_processing 同义）；gd_core/CoreTimer.gd _dbg/GD_TMR（[tstart]/[tfire] wt/left/t 流）。与既有 [eat]/[timer-fire]/ORACLE_RNG_DEBUG 同族。
- **★ 残余 19 红定谳（841 后全量）：全部 gd≡py（gd_py:True）= 真引擎语义差**，聚类：fd@6-84 早簇 10 场（947/1441/1534/1514/1427/1499/1536/1545/962/1540）+中晚簇（977@497/1118@422/986@206/921@452/939@91/702@1118/1022@2456/1444@342/1545）。**1540 剖剖（COF 棺材桩）**：fd@84 面上=gd 棺材掷中补毒 oracle 未掷；桩升级（onPrepare inside 清单+掷点 src/state 流）后实证——**掷前 state 已分叉**（GD st_before=-6982501255656572049 v ORA -2035187042715667355），最后公共态=t=0 第 4 掷后 4405120321889562169；PCG 步数法（mult=6364136223846793005/INC=2885390081777926815）：gd 350 步 v oracle 364 步=**窗口 (0.017,2.5667) 内 oracle 多 14 裸步**（≈7 次 2 步抽或 5×2+4×1）——隐形抽族 §6b 清单扩展：怀疑面=flicker playback_speed（每攻 2 步）/受击动画 spawnLabel 面，下一步=事件锚 state 桩（activate/takeDamage 双侧 state 流）对窗二分。**coffin 掷点 chance=22 双侧一致**（runtime 132/132 csv_chance→chance 映射完好，虚惊排除）。探针还原完毕（COF/COFP 三处 git checkout+镜像 cp+gd_to_py 重转写）。
- **交接（下一棒攻击序）**：①早簇 10 场逐场事件锚 state 桩二分（1540 窗口法已验证，14 步差已量化）②窗口内裸抽清单=flicker/spawnLabel/受击动画族③中晚簇按同法④914 全量合并+README+push（860 后）。工具遗产量化：oracle 364 v gd 350——修复方向=gd 补抽，不是 oracle 减抽。

## 6m3. np29fC 工具链升级 + 947 结构定谳（2026-11-02 深夜；继 §6m2）

- **ORACLE_RNG_TRACE 独立门控 ✅（oracle_fight.gd）**：`U.oracleRngTrace` 与 rng_log.txt 落盘改 `_dbg_delayed or ORACLE_RNG_TRACE`——绕开 ORACLE_DEBUG 的逐 tick 噪声（947 单场 ORACLE_DEBUG+RNG_DEBUG 4MB stdout 超时被杀的教训）。ORACLE_STACKTRACE=1 栈列实测空（release 构建 get_stack()=null，双侧同）——调用栈归属此路不通，改用**后态互检+步距指纹**。
- **pickRandomElement 桩 v2（Util.gd，ORACLE_RNG_DEBUG 门控）**：[pick] 行带 idx/val/后态。GDScript 3 坑再录：无返回类型注解的函数返回值不能 `:=` 推断（rng_trace_irange→var 用 `=`）。
- **★ 947（Rainbow Potion，fd@6）结构定谳**：**t=0 激活期发射记账结构差，非选型算法差**。①pickRandomElement 机制两侧逐位同（pickRandomStacksToGive/pool[101..107]/同链同 idx——同链位 pick 10/10 全一致）；②buffs=7/staffs=1 两侧同，块长恒 7；③**链位错后 2 掷**：oracle 7 掷块起于链头（states -9103→3550→1117→…，值 105,104,103,103,105,105,101），gd 同块起于 oracle 第 3 掷的链位（1117…，值 103,103,105,105,101,103,103）——gd 在链头把 oracle 的前 2 掷换成 1 次 randf_range(-10,10)=randInBox label 位置抽（2 步）；④后态互检法：oracle 62 pick 后态仅 10 个在 gd 有 pick，gd 42/52 pick 后态 oracle 没有——pick 调用点在激活期整体错位。**根因方向**：activation 期 buff/label 的发射-抽取交错序两侧不同（oracle 先掷完 7 再发射 label，gd 把 label 抽插进了掷块之前）——下一步=对 947 t=0 窗口做「发射事件×抽取」全序对拍（给 giveStacks/spawnBuffLabel_item/randInBox 上序号桩），锁定谁先谁后；同类 probable 覆盖 962/1427/1499/1534/1536/1545（fd@30-84 早簇同域）。
- **步距指纹法（新，可机制化）**：相邻记帐行的 PCG 步距序列=含裸抽的完整链指纹（randi 系 1 步/randf 系 2 步；-1=超窗）。两侧 dist 序列直接 diff 即定位结构性错位点，比 u 子序列对位更锐（u 对位受插删块噪声淹没，947 实证 0 前缀）。工具化建议：tools/_np29_chain_diff.py（输入 rng_log+rng_trace，输出首分歧 dist 对）。

## 6m4. §6m3 补正：947 激活期 BOX/掷块交错序精测（2026-11-02 深夜 ii）

- **t=0 窗口双侧值流精确对照（rng_log v rng_trace 原始行）**：BOX(randInBox ±10) 值流——oracle: 8.757147,-4.315774 | 4.707777,-8.546022 | 9.305531,7.543394 →掷块[4,3,2,2,4,4,0]→ -5.01656,4.665003 | 5.087511,-6.442901 | 3.535778,5.4525 | -20.165668,17.266853(±30 兜底槽!)；gd: -0.707928 | -4.315774,**7.698681** | -8.546022,9.305531 | 7.543394,**-7.681458** →掷块[2,2,4,4,0,2,2]→ 4.665003,5.087511 | -6.442901,3.535778 | …。**gd 多 2 笔 BOX（7.698681/-7.681458，oracle 无此二值），oracle 多 2 掷在块前；中段值流逐位同（-4.315774/-8.546022/9.305531/7.543394 双侧共有的槽位错位=gd 槽序比 oracle 深 1 抽）**。步账：gd 块前多 4 步（2 randf）而链需与 oracle 块前 2 步（2 pick）平衡 ⇒ 更早处 gd 还少 2 步（候选=oracle Piggybank label 的 BOX 对或 cooldown 批差异）。
- **已知修正**：§6m3「gd 把 oracle 前 2 掷换成 1 次 randf_range」不准确——实为 gd 块前多 2 笔 randInBox（4 步）+更早少 2 步的复合错位；中段 5 掷 (2,2,4,4,0) 双侧同链同值铁证不变。
- **下一步精确抓手**：①给 oracle `Item.getNextFreeLabelPosition`/`Character.randBuffLabelPos` 与 gd 对应钩子上「调用点+槽位分支(±10 槽/±30 兜底)」序号桩，t=0 窗口逐 label 对账（谁的 label 多抽/少抽/走兜底）；②oracle randInBox 行无 st 列=ORACLE_STACKTRACE=1 时走 7 元素栈分支（栈空）所致——复跑时**去掉 ORACLE_STACKTRACE** 即得全量 st 列（本次教训）；③±30 兜底槽（oracle row -20.17/17.27）gd 侧是否同拍走兜底待查——槽位占用期 0.5s 的时钟语义（Util.time v ctx.time）在激活期 t=0 的判定差是头号嫌疑。

## 6m5. 947 链位锁步定谳：冷却批/激活音效一抽错位（2026-11-02 深夜 iii；§6m3/6m4 的最终收窄）

- **★ 根因收窄到单一链位（双侧后态逐行锁步实证）**：激活窗 t=0 的两侧 rng_trace 后态序列**逐行完全相同**（-6444→5936→8878→2416→-6269→1126→-5284→6388→5800→7855→-9198→-4465→-3642→…），分歧=**pre-state 5861180806958685480 处的「那一抽」**：oracle 抽 `randf_range(0.9,1.1)`（Puzzlebag L 激活音效 randPitch，后态 -6444608296615875846）；gd 抽 `randf_range(0.975,1.05)`（adjustCooldown 冷却抖动，同后态 -6444…）。此后的每一抽「类型」错位连锁：gd 的 label BOX 值流整体右移一槽（gd 的 Puzzlebag x=oracle 的 y 值 -4.568449…），gd 末尾多一笔 BOX(-7.681458) 吃掉 oracle PICK#2 的链位(state 3550)，gd 掷块起于 oracle PICK#3(state 1117) → 选型 dict 3 型 v oracle 4 型 → fd@6。**冷却批/音效在一抽上的次序互换，下游全部错位**。
- **ACD 桩（adjustCooldown 物品名单）双侧完全一致**：28 件（ot=1 13+ot=3 13+Corrupted Crystal ot=1/3 各 1 重复）、同序——多出的那笔 0.975 **不是名单差**，而是同一物品的 adjustCooldown 在 gd 的**调用时机**不同（gd 在音效前、oracle 在音效后；或 gd 多调一次而 oracle 该位被 pitch 占据）。oracle 侧同链位的 pitch 行在 rng_log row 26（0.9,1.1 → -6444），gd 侧冷却行 rng_trace row 195（0.975,1.05 → -6444）。
- **SLT 桩（label 槽位分支）**：两侧槽位系统行为一致（全 free 分支、无 busy30 于开局段；oracle Rainbow 6 label（slot0-4+busy30，±30 兜底值 -20.165668/17.266853）v gd 5 label——**6v5 的差=掷块 dict 类型数差的下游结果，非独立 bug**）。槽位时间戳初始化双侧同为 [0.0×5]；语料 vs 新鲜单场复跑 events 逐字节一致（批录无残留，1540 的 9 场同族推断亦适用）。
- **下一步（下一棒直接照做）**：①给 ACD 桩补**前置态**打印（oracle `Util.rng.get_state()`/gd `ctx.rng.rng.get_state()`，在 adjustCooldown 抽前取），按前置态=5861180806958685480 精确匹配 gd 侧那一抽属于哪件物品→对照 oracle 该物品的 adjustCooldown 调用时机（oracle 调用点 Item.gd:3364/4411/4432 v gd CoreItem.gd:457/587/850——逐调用点映射生命周期）；②方向预判：gd 某物品的 adjustCooldown 在「激活音效前」调用而 oracle 在「音效后」（或 gd 多调一次/oracle 少调一次）——修=对齐该调用点顺序，其余全部错位应连锁自愈（label 值、掷块起点、dict 型数、第 6 label/busy30 全部回归）；③修后 REG：947+962/1427/1499/1534/1536/1545（同域早簇）+基线 7 场；④SLT/ACD 桩已还原（git checkout+镜像 cp），复用时按本节重打。
- **工具备忘**：oracle rng_log 全 state 列=不带 ORACLE_STACKTRACE 的 ORACLE_RNG_TRACE 跑（STACKTRACE=1 走 7 元素分支丢 st，两次踩坑）；gd 全 state trace=ORACLE_ALIGN_TRACE=1；诊断产物在 output/_offpeak/probe_spdt/（未跟踪）。

## 6m6. ★ 947 fd@6 根因破案+修复：autoRage pick_random 误用主链（2026-11-03；offpeak-70fcff69 接力）

- **★ 根因定谳（ACD3 全息桩链位锁步实证）**：oracle `Character.prepare()`（Character.gd:327）的 autoRage 选品用**引擎内建 `Array.pick_random()`**——消耗 `seed(S)` 种子化的**引擎全局链**（oracle_fight.gd:595 显式播种，与装配期 playerItems/opponentItems.shuffle() 同流），**主链零消耗**。gd_core/CoreCharacter.gd:309 误用 `ctx.rng.pickRandomElement`（早年注释「改用注入 rng 以保证同种子可复现」——前提已被 harness 全局链播种机制推翻：gd harness OracleAlignBattle.gd:523 同样 seed(S)，全局链双侧同源可复现）→ gd 每场多消耗主链 2 步（双方各 1 抽）→ **开局冷却批整体晚 2 步** → 批内「物品-抖动值」错位一件（链位锁步：gd real 批 v 序=oracle v 序[2:]，26 笔同值）→ Rainbow Potion 的 giveRandomBuffs 掷块错位 → 选型 dict 3 型 v 4 型 → **fd@6**。
- **修复**：CoreCharacter.gd:309 → `ctx.rng.pickRandomEngine(battleRageItems, "Character.gd:327")`（pickRandomEngine=CoreRng 现成基建，调 array.pick_random() 走全局链零主链耗；py 侧 _rt 已有 _pick_random 模拟）。三树同步（gd_core+gd_core_test 镜像+gd_to_py 全量转写+check_gd_py 全过）。
- **REG np29fd（gd 腿 14 场）**：基线 7 场全绿**零退**；**947 fd 6→46**（前 46 事件=装配+激活期全对齐），早簇 962/1427/1499/1534/1536/1545 的 fd 全部后移或持平（修复方向证实）。860 全量刷账进行中。
- **947 残余 fd@46（下一棒攻击面）**：t=89 Chess Board 首回合**捕获者身份差**（oracle=Black Pawn gain105/3 v gd=Black Rook gain104/3；后续 Spiked Staff 对拼链内容平移错位）。947 阵容双方各带 6 棋子+ChessBoard（WB/BP/WK/WP/BR/ChessBoard）。已核：两侧 ChessBoard.doCooldownEffect 的 activePieces.shuffle()/findPieceToCapture 的 captureCells.shuffle() 均已走 shuffleEngine（全局链 ✓）；捕获者=shuffle 后第一个可捕获者 → **全局链在 ChessBoard 首回合 shuffle 处失步**或 **装配 sort_TriggerPriority 的同优先级段保序差**（棋子 Pawn/Rook/Knight/Bishop 若同优先级，其相对序由 shuffle 残留序决定——gd IdxSort 模拟的保序性 vs oracle Godot sort_custom 的实际行为需对拍；棋子 inventory 序=getPiecesForColor 的输入序）。攻击抓手：①双侧打印 ChessBoard.doCooldownEffect 入口的 activePieces 序+长度（env 门控桩，打点后对拍 shuffle 输入）②对比两侧 getPiecesForColor 过滤序 ③autoRageItem 选中结果对拍（battleRageItems 若多元素，选中差会改 AutoRage 触发行为）④gd IdxSort 与 Godot sort_custom 的同优先级稳定性逐元素对拍（用 947 装配数组实测）。
- **教训**：①ACD2/ACD3 桩的 pre 与 rng_log 的 st 列**不可互推**（BalancedRng.get_state() 语义与 PCG 内核态的映射非恒等）——全息桩必须 pre+post+值一行打全（ACD3 模式）；②stdout 解析必须 finditer 不锚行首（SCRIPT ERROR 行会拼接污染）；③oracle 的 Array.pick_random()/shuffle()=全局链族，gd 对应物=pickRandomEngine/shuffleEngine（CoreRng 现成），转写时**逐处核对**（本例一处漏改埋了 46+ 场的雷）。

## 6m7. fd@46 深挖：ChessBoard 回合 4/5 捕获选择分叉（2026-11-03 ii；继 §6m6）

- **CBS 桩（ChessBoard.doCooldownEffect 入口 activePieces 序，env 门控）双侧对拍（run947 real 遍，按 onPrepare 时刻切遍）**：**回合 0-5 完全一致**（棋子序逐位同：白[WB,WK,WP]→黑[BR,BP]→白[WK,WB]→…）；**回合 4/5 的捕获选择分叉**——gd 白方回合吃 Black Rook（回合 6 黑方剩 [BP]）、oracle 吃 Black Pawn（回合 6 黑方剩 [BR]）→回合 6 起黑方序互换→t=89 回合捕获者身份差（Black Pawn v Black Rook）→棋子 doCapturingEffect 的 gain buff 事件不同→**fd@46**。oracle 比 gd 多 5 回合=**回合 6 起 oracle 的若干空回合（[]）**（棋子早被吃完的分支节奏差，空回合 shuffle(空数组) 零全局消耗不引入新偏）。
- **捕获差定性**：回合 4 的捕获目标由 `activePieces.shuffle()`（全局链）+逐 piece `captureCells.shuffle()`（全局链）+canAffect 判定决定——回合 0-3 序全同=**全局链到回合 3 末同步**；回合 4 的 shuffle 输入（[WK,WB]）双侧同 → **失步点在回合 0-3 的全局链消耗数差**（某回合 captureCells/moveCells 数组长度双侧不同=棋子位置差（边界裁剪 cells 数）或 cells 生成差），或 **回合 4 的 shuffle 结果相同但 canAffect/getItemInCell 判定差**（棋盘布局/物品占格差——但回合 0-3 的移动落格由同链同 cells 决定，应同）。**下一棒取证桩**（打点后还原，gd_core_test 镜像同步）：①findPieceToCapture/findSpaceToMove 每 piece 的 (cells 序, 首个目标, 返回结果) 全打印（[CFC] 桩）②回合 0-3 逐回合全局链消耗数（gd 侧在 shuffleEngine/pickRandomEngine 加计数器 print；oracle 侧 Array.shuffle/pick_random 内建不可拦——改在 ChessBoard 各调用点数 shuffle/cells 长度）③棋子 occupiedCells/位置逐回合快照（[CPOS] 桩）——三桩对拍锁定首个 cells 长度差或目标差。
- ** CBS/ACD 探针已全部还原**（ChessBoard×2、Item×2 checkout+镜像 cp+重转写零残留）。**860 全量（np29fD 修复后）= 841/860，红场集合与修复前完全一致**（fd 全部后移：947 6→46，其余持平）——autoRage 修复方向正确但单笔不足以翻绿早簇；早簇 1441@18/1427@40/1499@40/1534@30/1536@42/1545@63/962@83/1540@84/1514@36 的 fd 均在 t=0 激活期同域（§6m3/§6m4 的发射记账错位族），**修复 947 的 fd@46 与早簇其余场是两条独立的残余链**。
- **交接（下一棒攻击序）**：①fd@46 三桩取证（本节抓手，回合 0-3 全局链消耗对账）②早簇 t=0 激活期发射记账错位族（§6m4 的 label 槽位/发射序精测，947 已提供模板）③中晚簇（702@1118/1022@2456/1118@422/977@497/1120@868/986@206/921@452/939@91/1444@342）逐场事件锚 state 桩二分（§6m2 窗口法+步距指纹法现成）。

## 6m8. 1441 步距指纹+值序对位：X 处裸抽/pitch 分解差（2026-11-03 iii；早簇通用攻击面）

- **方法**（值序对齐法，比步距指纹锐）：gd trace 从冷却批首（首笔 0.95 行=oracle row0 同链起）与 oracle rng_log **逐行值序对齐**（比较 from+值，忽略 tag 命名差——oracle randInBox.x/y=gd randf_range 同抽不同 tag；**务必过滤 EVENT/SRC/LABEL/ANIM/BUS* 标记行**，oracle 行的值列=p2[5] gd=p2[4]）。
- **1441 结果**：**前 90 笔 post 链逐笔全同**（真同步，autoRage 修复后装配+激活期已齐）；**+90 处分叉**——上下文：`[0.95:1.035047, 0.95:0.997612 | ora:0.975:1.015923 → (100,143):143.077 → 0.9:1.022107 → 0.9:1.068183 → pick(2)] v [gd: 0.975:1.028847 → (100,143):136.632 → 0.9:1.068183 → 0.9:1.083592 → randi(1)]`。**PCG 解算**：X（第 90 笔 post=第 91 笔 pre）→ora91=X+2 步（正常 randf）→**gd91=X+4 步=gd 在第 90/91 笔之间多 1 笔 2 步裸抽**（trace 无此行=绕过包装）；且**后续 ora 多 1 笔 pitch(1.022107) gd 无**——**净步数同（+2−2），内容分解差**。
- **归属**：+90 链=t=80 Ruby Whelp 首触发（0.975=opponent trigger 的 adjustCooldown、(100,143)=攻击伤害掷 randf(minDam,maxDam) 值 136.6/143.1 → 事件 fd@18 damage 5v6、pitch=音效）。**gd 多的裸抽候选**=flicker speed（CoreItem.gd:820 `ctx.rng.rng.randf_range(minSpeed,maxSpeed)`，callDelayed 到点派发）或 activate 动画 4 连的错位（CoreItem.gd:1001-1004）；**gd 少的 pitch**=Ruby 攻击链的 playAttackSound/音效抽（oracle 攻击链 2 笔 pitch gd 1 笔）。两侧 RubyWhelp.gd/Weapon 基类脚本同构——差在**引擎调用面**（Sound.playSound 的包装/裸调差异或 Weapon.attack 的音效链）。
- **下一棒取证桩**（打点后必须还原+镜像同步）：①[ACT] 桩两侧 Ruby Whelp trigger 全链逐抽打点（adjustCooldown 前后/attackSound/animation/damage 各面，ACD3 全息模式 pre+post+值一行）——先锁「gd 多的裸抽」的精确值域（flicker speed=(minSpeed,maxSpeed) 特征值域 vs 动画 4 连=(-30,30)等）②双侧 Weapon.attack/doCooldownEffect 的音效调用面逐行对照（oracle Item.gd playAttackSound 族）③修=gd 补漏的 pitch 或删多的裸抽（按 oracle 分解对齐）。
- **通用性**：值序对齐法+PCG 步数解算（X+2 v X+4）的组合**可直接复用于早簇其余场**（1427/1499@40、1534@30、1536@42、1545@63、962@83、1540@84、1514@36）——每场 30 分钟内可锁定「多/少/分解差」的具体抽面。1540 的「oracle 多 14 裸步」（§6m2）与本例「gd 多 2 步+少 pitch」**方向相反**——隐形抽面不是单一方向，须逐场定量。
- **账面**：841/860（红场集合不变）；本节纯诊断无桩残留（1441 双侧 trace 为 env 门控产物，工作树零改动）。

## 6m9. §6m8 修正+本会话收口（2026-11-03 iv）

- **§6m8 的 PCG 解算修正**：X→ora91=X+2/gd91=X+4 的解读基于「randf_range=2 步」假设；但用 Godot randf_range 取值公式反算，**ora91 的值 1.015923 从 X 出发 1-4 步的 u 都映射不出**——**ora91 的 pre≠X=oracle 侧 X→ora91 之间同样存在 log 零痕迹抽（隐形抽是双侧的）**。1441 的 X 段纯离线推理已到极限，**必须 [ACT] 全息桩实测**：两侧 Ruby Whelp trigger 链（adjustCooldown/attack/音效/动画面）逐抽 pre+post+值一行打点（ACD3 模式），单场对拍即可锁定双侧隐形抽的精确位置与值域。flicker 已排除（1441 零 FLKFIRE=阵容无 flickerAni）。
- **本会话（offpeak-70fcff69 接力）总战果**：①**autoRage 修复**（dc77fc16，np29fD）：oracle Array.pick_random=引擎全局链（seed(S) 播种）主链零耗，gd 误用主链 1 抽×双方→冷却批晚 2 步→Rainbow 掷块错位 fd@6；修=pickRandomEngine。REG 基线 7 场零退；947 fd 6→46；860 全量 841/860（红场集合不变）。②fd@46 深挖（037b4cdf，§6m7）：CBS 桩证回合 0-5 棋子序全同、回合 4/5 捕获选择分叉（gd 吃 BR/ora 吃 BP）→t=89 捕获者差。③1441 值序对位（5f3f9864，§6m8/§6m9）：前 90 笔 post 链全同（修复后装配+激活期已齐）；X 处双侧隐形抽复合（gd 多 1 笔+ora 有隐形）→伤害掷错位→fd@18 5v6。④方法论沉淀：**值序对齐法**（from+值逐行比，忽略 tag；过滤标记行）+**post 链验证**（防值碰撞假同步）+**PCG 步数解算**（X+k 定位隐形抽）三件套，可复用于早簇全部场。
- **下一棒**：①[ACT] 全息桩打 1441 X 段（本轮即可修——gd 补 pitch/删多余裸抽按实测对齐）②fd@46 的 ChessBoard 三桩（§6m7 抓手）③两根因修后 860 刷账→预期早簇多场翻绿→继续向 860 推进。

## 6m10. 1441 H 抽收窄至激活期单点（2026-11-03 v；本轮接力终态）

- **方法升级（PCS/ACD/ACT/TK 四层探针，均已还原）**：①`[PCS0/1/2]` Item.preCombatStart 入口/宝石循环后/cd 后带物品名+state（双侧同款）②`[ACD]` adjustCooldown 物品名+pre ③`[ACT0/1]` CoreCombat 激活三循环逐物品前后态 ④`[TK2/3/5/6]` tick 相位态。
- **★ 定谳事实链（state 链级，免疫值公式噪声）**：autoRage 修复后，1441 双侧值序从游戏首抽对齐 **90 笔**（gd trace 行 225-331 ↔ ora rng_log 行 0-102 逐值全同，含四连 0.95 cd 批）；**首个分歧=gd 在四连 0.95 末态 X(=-8589913982054635222) 与下一笔 0.975 cd 之间多消耗恰好 2 步**（ACD 桩：ora 的 Ruby Whelp ot3 cd pre=X 直抽；gd 同一 cd pre=X+2；PCG 数值解算 X→gd cd post=4 步=X+2）。此后内容序列双侧**完全同构**（cd,anim(100,160),P,P,pick,A(0.8,1.2),pick,randf,pos50,pos70,dir,boxx(3步!),boxy,P,EV,P——boxx 的 3 步跨度双侧一致=公共隐形抽，非分歧源），仅整体在 u 流上错后一抽位——pick/A 吃错 u → Ruby 伤害 5v6 → fd@18。
- **已排除**：①宝石循环（PCS0=PCS1 双侧全同，Regular Topaz 无 preCombatStart 抽）②Ruby preCombatStart 本体（双侧 PCS0→PCS2 均 2 步恒等）③expectedWins (0.2,-0.2)（gd trace 202 笔全在装配期行 1-224，oracle 裸抽同点位；中途零构造）④flicker（1441 零 FLKFIRE）⑤动画 4 连裸抽（8 步≠2 步）⑥BalancedRange randi（1 步）。H=激活期、四连 0.95 与下一 opp cd 之间的**2 步裸抽**，gd 独有。
- **★ 关键教训（下一棒必读）**：本工程 gd harness 每场跑 **4 个 pass**（warmup 收割/real(latched)/selfcheck×2，real+selfcheck 有 WARM_LATCH `attack_moving_forward=true`），**探针行必须带 pass 序号**（本轮 ACT/ACD 跨 pass 关联两次误判的根源）；rng_trace.txt=real pass；stdout=全部 pass 混杂。oracle playAttackAnimation 的 `distance=Util.rng_trace_range(100,160)` 是**默认实参抽，先于 attackMovingForward 闸**——被闸的调用仍消耗 2 步（gate 前置抽），对账时勿漏。
- **下一棒抓手**：①探针加 pass 计数器（harness 在 pass 开始时 set 一个 env 或 ctx 计数，探针行前缀 p0/p1/p2/p3），重跑 PCS+ACD 双侧，**同 pass 内**对齐四连 0.95 批→Ruby cd 段，锁定 H 的宿主物品与 hook ②H=2 步裸抽候选兜底排查：在 CoreRng 增加临时 `raw_draw_counter`（构造 RandomNumberGenerator 包装对象替换 rng 成员——慎用，须事后完全还原），或逐项 grep gd_core 全部 `rng.rng.` 已穷尽（6 处）→ 若宿主是 gd_core_items 脚本层的引擎调用（如 `array.pick_random()` 全局链误用主链的反向案例），按 §6m6 同法修 ③修后 REG（1441+947+早簇+基线 7）→860 刷账。
- **账面**：841/860（19 红，集合不变）。本轮全部探针已还原（CoreItem/CoreCombat/Item 三处 checkout+镜像 cp+重转写零残留），offpeak-70fcff69/#215 与 offpeak-0bfcfee4/#306 按本节接力。

## 6m11. §6m10 勘误：跨 run 状态关联无效，单 trace 内 H 证据仍稳固（2026-11-03 vi）

- **勘误**：§6m10 的「ACD 桩 ora Ruby cd pre=X v gd pre=X+2」是**跨 run 对比**——本轮实测同一 case 的两次 harness 调用，其 rng_trace.txt 行布局不同（首次 0.975 行号 332 v 244，pass 构成/latch 状态差异），**X/X+2 等绝对态值不可跨 run 关联**。PCS 跑内 Ruby cd pre 双侧同=609c（该 run 的 pass 里无 H 或 H 在别的 pass）。
- **仍然稳固的证据（全部单文件内）**：①原始 trace（trace-run）内四连 0.95 末态 X → 下一 0.975 距离恰 4 步（多 2 步）；②ora rng_log 内同位置距离 2 步；③值序对齐 90 笔后首分歧即该 0.975；④其后攻击链内容双侧同构（含 boxx 3 步公共隐形）。H=gd trace 该 pass 内、四连 0.95 与下一 opp cd 之间的 2 步裸抽——**结论不变**。
- **下一棒修正案**：①所有探针行必须内嵌 pass 序号+trace 行号可回溯（harness 在每 pass 开始 print `===PASS n (latch=?)===` 到 stdout，并把 pass 号写进每条探针行）②**只做单 run 内分析**：同一次双侧跑的 trace+stdout，按 pass 切分后对齐 ③H 宿主=四连 0.95 cd 物品与下一 opp cd 物品之间的 hook 链——用同 run 的 [PCS0/1/2]+[ACD] 行（带 pass 号）直接读出 state 跳变发生在哪个物品的哪段 ④若 H 在 PCS0→PCS1 之间=宝石循环内某宝石抽（1441 Ruby 镶 Regular Topaz——单 run 内验证 PCS0≠PCS1 即实锤）。

## 6m12. ★ 1441 H 抽单 run 内复现+宿主锁定至「Ruby cd 非激活调用方」（2026-11-03 vii；本轮最终态）

- **★ 单 run 内复现（跨 run 关联问题终结）**：同一次双侧跑（PCS0/PCS1+ACD 探针）内，模式「0.975+4×0.95+0.975」双侧命中——gd 跳点 dist(4th 0.95 post→下一 0.975 post)=**4 步**、ora=**2 步**。批构成双侧逐物品全同：Chipped Emerald(ot3,0.975) → Corrupted Crystal/Chipped Ruby/Chipped Emerald/Chipped Amethyst(四宝石 ot7,各 0.95) → Ruby Whelp(ot3,0.975)——**宝石 cd=宝石自身继承 Item.preCombatStart 的 hasCooldown 分支**（Gems extends Item）。
- **★ H 宿主性质判定（决定性）**：gd 的 Ruby Whelp cd pre=Xp+2（Xp=Chipped Amethyst cd post=88ca7ebea078e92a，跨 run 恒定复现=确定性无疑）——但该 run 的 **[PCS0] 探针在 Xp/Xp+2 均无行**（gd Ruby PCS0 仅 2 行且 st=609c，属于另外的 pass）⟹ **Ruby 的这笔 0.975 cd 不是 preCombatStart 发出的**（PCS0 必在 ACD 之前打点却缺席）——来自 **adjustCooldown 的其他调用方：trigger()/updateBaseCooldown()（setBaseCooldown/resetBaseCooldown→updateBaseCooldown）**。2 步隐藏消耗在其间的路径里：Chipped Amethyst post-cd 段（activateCooldown/snapshotItemTooltipStat/onPreCombatStart）或 Ruby 的非激活 cd 调用方前置段。
- **已排除（本 run 内实证）**：宝石脚本层（Amethyst/Topaz 无 preCombatStart 抽、gd Regular Topaz cd=0 无 cd 分支）、Regular Topaz 的宝石循环（PCS0=PCS1 的 pass 内）、BalancedRange.randIntRange（全树零调用方）、flicker/动画 4 连/expectedWins 中途构造。
- **下一棒（最小闭环）**：①[UBC] 探针打 `updateBaseCooldown`/`setBaseCooldown`/`resetBaseCooldown` 入口（物品名+state，双侧）+Ruby 的 [PCS0]——单 run 内看 Ruby cd 的真实调用方与其前置段的 state 落差 ②同一探针轮里打 `[SNAP]` `snapshotItemTooltipStat` 入口（Amethyst cd 后那笔）——若落差在其内=stat logger 路径有裸抽 ③修=对齐该调用方的抽耗（gd 补/删按 oracle）④REG（1441+947+基线 7）→860 刷账。**跨 run 关联禁令维持**：一切分析限单 run 双侧同跑。
- **账面 841/860**；探针已全还原（CoreItem/Item checkout+镜像+重转写零残留）。本轮 session 净 +3（838→841，autoRage）+ fd@46 回合定位 + 1441 H 单点锁定；offpeak-70fcff69(#215)/0bfcfee4(#306) 按本节接力冲 860。

## 6m13. ★ 跨进程非确定性发现（2026-11-03 viii；本轮最终收口）

- **★ 重大发现**：同一 case（run1441_r11）两次独立 harness 调用，其 rng_trace 的**同位置链态不同**（跳点 Xp 一次=88ca7ebea078e92a、另一次=7e54c627cc125bd8）——**进程间 trace 链不可复现**，而进程内 selfcheck（同种子复跑）逐字节一致。⟹ 差异源=**进程级状态**：APPDATA 按 PID 隔离（user:// 下有跨调用持久态：RunDatabaseStub.run 历史/暖场收割缓存/latch 表）或 pass 构成随环境变化。**这可能是早簇多场的共同根因**：若 gd real pass 链依赖进程历史，而语料=特定历史下的录制，对齐断点会随调用漂移。
- **H 证据最终状态**：单 trace 内「0.975+4×0.95+0.975」跳变（4 步 v ora 2 步）**在该 trace 的 pass 内成立**；跳点两侧 ACD 物品（Chipped Amethyst → Ruby Whelp）双侧全同；Ruby 该笔 cd 的调用方仍未锁定（PCS0/TRG 探针在跳点段的缺席/错位=pass 关联未解决）。
- **下一棒（最高优先）**：①**进程级状态审计**：diff 两次调用的 APPDATA 目录（output/_recovery/appdata_p/<pid>/）——找出 user:// 持久文件；grep harness 对 user:// 的读写（ConfigFile/Store）② harness 的 pass 序号显式化（每 pass print ===PASS n===）+ 探针带 pass 号 ③若确认 user:// 态影响 real pass 链 → 修=隔离/清空（对齐语料的录制条件）④之后按 §6m12 抓手继续 H 宿主定位。
- 账面 841/860；探针已全还原（checkout+镜像+重转写零残留）。

## 6m14. H 分析的 pass 拼接真相+最终交接（2026-11-03 ix；本轮绝对收口）

- **★ trace 结构真相**：gd rng_trace.txt = **real+selfcheck 两 pass 拼接**（1891 行≈2×945；state 在 pass 边界重置）。本轮全部探针（PCS0/1/2+TRG+ACD）的状态→trace 行号映射显示：**跳点段（trace 行 331→333，dist=4）无任何探针行映射**——即 traced pass 的激活段与其他 pass 的探针态对不上。两种解释：①trace 的 pass 与探针 pass 不同源（dump 选错了 ctx）②traced pass 的激活走了绕过 Item.preCombatStart 的路径。
- **稳定不变的事实**（跨 run 复现）：①「0.975+4×0.95+0.975」模式跳点 gd=4 步（本轮一次实测 6 步=跳距亦随 pass 漂移）v ora=2 步；②跳点两侧 ACD 物品双侧全同（Chipped Emerald3→四宝石 ot7→Ruby Whelp3）；③批内第二 case 检验：H 不消失（非进程历史问题）；④flipWeighted 记账不对称（gd CoreRng 无 _trace v ora rng_trace_range）——**独立待修雷**（Shovel/Robodog 商店期，1441 不涉但其他场可能涉）。
- **下一棒（最短路径）**：①harness dump 处加 pass 标识（rng_trace.txt 首行写 `#pass=N latch=?`；或每 pass 独立文件）②重跑 PCS+ACD+TRG 探针，**在 traced pass 内**读跳点段的探针缺口——缺口即 H 宿主 ③若 traced pass 绕过 preCombatStart→审计 real pass 的物品构造/灌入路径（「正式场玩家构造后灌入」的代码路径是否直调 adjustCooldown）④修后 REG→860 刷账。**flipWeighted 补 _trace**（一行：`var val = randf_range(0, sum, "flipWeighted")` 对齐 ora Util.gd:1115）可顺带落。
- 账面 841/860；探针全还原；本轮 session 净 +3（838→841）+ 三层根因收敛（autoRage 修复落地、fd@46 回合定位、1441 H 收窄至 traced pass 激活段）。

## 6m15. H 窗口相位最终确认（2026-11-03 x；交接完毕）

- **相位定谳**：四连 0.95=**宝石 combatStart 的 adjustCooldown 重掷**（Gem.gd:312 combatStart→.combatStart()→adjustCooldown，Inventory/Weapon/Armor 分支双侧同构）；Ruby 的 0.975=**其首次 trigger() 的 adjustCooldown**（Item.combatStart 不调 adjustCooldown）。H=两者之间的 2 步裸抽，窗口=「combatStart/postCombatStart 相位尾+tick0+tick1 头」。该窗口无探针覆盖（PCS 只探 preCombatStart；[spdt] 行无 state 列）。
- **下一棒（3 步闭环）**：①[spdt] 探针补 state 列（一行改：print 加 `st=%s` % ctx.rng.rng.get_state()——注意 CoreCombat 两处+镜像）②重跑 GD_SPDT=1，跳点 Xp/Xq（trace 内）之间的 [spdt] 行即宿主物品 ③按宿主修（gd 补/删抽对齐 oracle）。备选嫌疑：cbt/post 相位的某 item hook、首 tick 的 callDelayed 派发、Wolpertinger/Toad/Relic Case 等 onCombatStart 物品的隐形抽。
- 账面 841/860。本轮 session（goal 接续）累计：autoRage 修复（净+3）+ flipWeighted 记账对称 + fd@46 回合定位 + 1441 H 三层收敛至相位窗口。工作树零残留，offpeak-70fcff69(#215)/0bfcfee4(#306) 接力。

## 6m16. H 宿主二选一收敛+pass 混叠定谳（2026-11-03 xi；本轮终）

- **★ 收敛**：CBT/PST 探针（本轮）锁点——四连 0.95=**四颗独立宝石 item 的 combatStart cd**（Chipped Emerald/Corrupted Crystal/Chipped Ruby/Chipped Amethyst，各自 CBT0/CBT1 行实证）；跳点=「Amethyst（Cursed Dagger 的宝石）combatStart cd」→「Ruby Whelp 首笔 0.975 cd」之间。Ruby 该笔 cd 的调用方=preCombatStart/trigger/updateBaseCooldown 三选一——**PCS0/TRG 探针在其邻域缺席=pass 混叠**（同一 state 在 real/selfcheck 两 pass 各出现一次，state→行号映射把两 pass 折叠，时序不可分）。
- **解法（唯一障碍，下一棒第一步）**：harness `run_case` 入口 `pass_index += 1`（ctx 或全局变量），**全部探针行前缀 `p%d`**；重跑一次 PCS0/1/2+ACD+TRG+CBT/PST 双侧——同 pass 内跳点段的探针缺口即 H 宿主（预期二选一：①Ruby preCombatStart 的宝石循环（Topaz 无 cd 已排除→若缺口在 PCS0 前则 Ruby 的 cd 来自 preCombatStart 而其宝石循环有隐形抽）②Ruby 首次 trigger 前置段）。
- **已固化事实**（不再重查）：四宝石 combatStart cd 双侧全同；Ruby 首触发链内容双侧同构；跳距 gd 4/6 步（随 pass 漂移）v ora 2 步；批内第二 case 检验 H 不消失；flipWeighted 已修（c1a72146）。账面 841/860。

## 6m17. ★★ 1441 H 宿主最终锁定：Oil Lamp flicker 战斗期派发 v oracle 装配期（2026-11-03 xii）

- **★ 全息桩闭环（本 run 内）**：pass 序号内嵌（harness probe_pass_idx+ctx.probe_pass）后，同 pass 内跳点段夹逼：`[spdt+st]` 逐物品+`[S2/S5/S7a-d/S8/S9/SFE]` 步骤级+`[FLU]` callDelayed 派发物——**H=t=0.75 时 `ctx._flushTimed()` 派发的 `Oil Lamp.flickerPlayAni`（裸 randf_range(minSpeed,maxSpeed)=2 步，trace 无行）**。FLU 探针实证：`[FLU] t=0.7500 obj=Oil Lamp m=flickerPlayAni rem=0.0106`。
- **★ 机制定谳**：gd 侧 flicker 的 callDelayed（kernel_r6 注册于 _readyInit）在**战斗循环内按 PHYSICS_DELTA 递减**→t=0.75s 战斗期派发。oracle 侧 Util.callDelayed=真实引擎 `get_tree().create_timer` 语义——flicker 注册于**装配期**（Item._ready），0.1-3.0s 的 delay 在**装配真实帧流**中到期（装配真实时长≫3s）→flicker 抽落在**装配链位**（rng_log 不可见=裸抽），**不在战斗段**。两侧消耗集合相同（每件 flicker 物品恰 2 步），**链位不同**=值序错位→Ruby 掷/pick 吃错 u→伤害 5v6→fd@18。
- **np25 kernel_r6（run784）与本例的关系**：run784 曾实证「战斗窗内 oracle 恰多 1 次隐形抽」——不矛盾：oracle 的 drive_delayed（step⑧）驱动的是 U.oracleDelayedTimers（**战斗开始后新注册**的 callDelayed 才入战）；而 flicker 注册于装配期，走真实 SceneTreeTimer=装配期到期。两条路径并存，gd 的 ctx.callDelayed 把两者混成一条战斗期递减队列=根因。
- **★ 修复方向（下一棒）**：gd 的 `ctx.callDelayed` 需区分注册相位——**装配期注册的 callDelayed 不入战斗递减队列**（对齐真实引擎：装配期注册的 timer 在装配期到期=其抽耗落在装配链位）。具体：harness 装配段结束时把 _timed 中剩余条目**立即派发**（或按 oracle 语义在装配末帧结算），战斗期注册的照旧递减。修后 1441 早簇（1441/1427/1499/1534/1536/1545/962/1540/1514——阵容全带 Oil Lamp 系 flicker 物品的场）预期连锁翻绿。**注意 run784 场的回归**：kernel_r6 为 run784 打的补丁若被本修复覆盖，需用 run784 重验（其 flicker 注册可能在战斗期=照旧递减）。
- **已固化**：跳点批构成/ACD 名单/物品-值错位链全部不变；flipWeighted 已修（c1a72146）；账面 841/860。探针已全部还原（CoreItem/CoreCombat/CoreContext checkout+镜像+重转写零残留）。

## 6m18. ★★ 1441 fd@18 根因全链闭环：flicker 延时抽装配链位差（2026-11-03 xiii；本轮绝对终态）

- **★ 根因（全证据链闭环）**：**flicker 延时抽（`randf_range(0.1,3.0)`，FlickerAnimation._ready）的装配链位两侧不同**。gd 在 `CoreItem._readyInit` 内联画（trace 可见：row95=1.842785、row209=0.743884）；oracle 在 **FlickerAnimation 子节点 _ready** 画（`Util.rng.randf_range` 裸调=rng_log 不可见，派生延时值 1.65/2.92——由 [CDF] 派发时刻反推）。**Godot 子节点 _ready 先于父脚本 _ready** → oracle 的 flicker 延时抽在其物品创建序的「子节点 ready」位，gd 在「CoreItem._readyInit 开头」位——两位置之间夹着其他装配抽（connector/gem/socket 族）→ 延时值不同。
- **连锁（全数学闭环）**：延时值差 → 战斗期派发时刻差（gd FLU：t=0.75/1.85 v oracle CDF：battle-t=1.65/2.92——drive_delayed 与 _flushTimed 递减语义双侧同构）→ 派发抽（裸 2 步）落不同战斗链位 → Ruby Whelp 首触发链（cd/anim/pitch/pick）整体吃错 u → 伤害 5v6 → **fd@18**。947 的 autoRage（已修）与本根因正交。
- **★ 修复方案（下一棒第一步，具体到行）**：gd 的 flicker 延时抽从 CoreItem._readyInit 开头移到**oracle 的子节点 _ready 等价位**——读 `oracle/Items/Exclusive/OilLamp.tscn`（及其他 flickerAni 物品的 tscn）的**节点树序**，找 FlickerAnimation 相对其他「_ready 期抽节点」（Connector/宝石）的位置，把 gd 的 `flicker_delay` 抽挪到 _readyInit 内对应序位（connector/gem 抽之间）。注意：仅 40/517 物品有 flickerAni=True，**移位只影响有 flicker 的物品的物品内序**，无 flicker 物品零影响。修后 REG：1441+947+早簇+基线 7 → 860 刷账（预期早簇多场连锁翻绿）。**再注意**：若 tscn 里 FlickerAnimation 位于所有抽节点之前/之后的一致位，gd 现状（_readyInit 开头）可能本就等价——则分歧在别处（宝石 socket 抽的相对位），用同一探针法在**装配期**（[RDY] 桩打 Item._ready/FlickerAnimation._ready/connector/gem 各抽的物品名+state）双侧对拍一个 Oil Lamp 的创建序即可终判。
- **方法论沉淀（本轮新增）**：①pass 序号内嵌（harness probe_pass_idx+ctx.probe_pass，探针行首 p<N>）②值序对齐法（from+值逐行比，忽略 tag 差异，过滤 EVENT/SRC/LABEL/ANIM/BUS* 标记行）③post 链验证 ④PCG 步数解算（X+k 定位隐形抽）⑤相邻 spdt 行链扫（tick 内/tick 间 0 消耗段直接跳过）⑥S2/S5/S7/S8/S9/SFE 步骤级夹逼——六件套可将任意早簇场的根因定位压到 1-2 小时。
- **账面 841/860**。本轮 session 全部探针已还原（CoreItem/CoreCombat/CoreContext checkout+镜像 cp+重转写零残留）；offpeak-1476e382(#150)/70fcff69(#215)/0bfcfee4(#306) 按本节接力。

## 6m19. flicker 延时值差异的分组定性（2026-11-03 xiv；接力最终抓手）

- **tscn 结构核实**：OilLamp.tscn 的 FlickerAnimation=Icon/TorchLight 的子节点（index=0 覆盖插入），树序 CollisionMap→Icon→Sockets→TorchLight→**FlickerAnimation**→…→root——flicker 延时抽在 oracle 也是**该物品创建的首笔 rng 抽**（前序子节点无 rng 调用）——与 gd `_readyInit` 开头位**同位**。⟹ **物品内位差排除**。
- **真正分歧面（数值实锤）**：gd flicker 延时值 u=0.601/0.222（trace row95=1.842785、row209=0.743884，可=nil→battle 1.85/0.75 派发）；oracle u=0.5345/0.9724（→battle 1.65/2.92 派发）。**同一物品、同物品内位、不同 u** ⟹ 前序链消耗分组不同：gd 的 Oil Lamp 延时抽之前（含上一物品尾段+Oil Lamp 前段）与 oracle 的对应段，**消耗总数相同（battle-start 链态对齐铁证）但中间某几笔的次序/归属不同**——即装配期存在「成对换位」的抽（A、B 两笔在 gd 是 [A,B]、oracle 是 [B,A]——总量同、逐值异）。候选换位对：①上一物品的 connector/gem 抽 vs flicker 延时抽 ②双 Oil Lamp（镜像阵容各一）的创建序 ③`Extra Bags`/`Piggybank` 类无抽物品的 _ready 分支差。
- **下一棒（终判桩，2 步）**：①双侧 FlickerAnimation 延时抽 pre 态打印（oracle/Items/Animations/FlickerAnimation.gd:14 前加 `print("[FLKD] p%d st=%s" % [Util.probePass, str(Util.rng.get_state())])`；gd CoreItem.gd _readyInit flicker 段同款）——得到双侧延时抽的**前置态**②用 PCG 逆推（MINV 已有）从双侧前置态各回退 N 步到上一公共锚点，N 差值+中间抽的值序列=换位对的精确内容 → 按内容修 gd 装配序。
- 账面 841/860。pass 基建已持久化（3f1fea9c：harness probe_pass_idx+ctx.probe_pass/Util.probePass+[CDF] 探针门控）；本轮探针零残留。

## 6m20. FLKD 前置态捕获+取值约定新层（2026-11-03 xv；接力交接数据全量）

- **★ FLKD 桩双侧捕获成功**：gd flicker 延时抽前置态 p1/p2 重复稳定=**-6989916417164439028 / 6732581090020881056**（两颗 Oil Lamp）；oracle 侧捕获 8 行（p0 起多 pass，含 -7096985976994206990 等）。oracle FLKD 首跑 0 行的坑=**上轮收尾 checkout 掉了 Util.probePass 而 FLKD 引用它→每次调用 Invalid 静默炸**（55 个 Invalid 错误）——探针引用的成员必须与基建同 commit。
- **★ 取值约定新层（重要）**：PCG 步距 2 步内、延时值 1.842785 = **f(pre+1) XOR 0x80000000**（u=0.600960，val=0.1+2.9*0.600960=1.842784 精确）；而 anim 族（100,160）=f(pre+1) 无 XOR。**XOR 高位=有符号/无符号两种 randf 映射并存**——battle 窗内此前 90 笔对齐不受影响（gd trace/ora log 双侧同约定、同错同对），但**离线 u 反解必须双约定尝试**。oracle 延时值 1.65/2.92 的对应 pre 态已在捕获集中（待双约定解算定位）。
- **下一棒（数据全备，纯离线即可终判）**： captured 数据文件=output/_offpeak/probe_spdt/{gd,ora}_1441_stdout.log（[FLKD] 行）。①oracle 8 个 pre 态逐个双约定解算 delay 值→与 [CDF] 派发时刻（1.65/2.92）对上者=真 pre ②从真 pre 用 MINV 逆推到与 gd pre1(-6989…) 的公共锚点→两 pre 间的步距差与中间值序列=换位对的精确内容→按内容修 gd 装配序（预期=某几笔装配抽在 gd/oracle 间次序互换，修=对齐次序）③修后 REG（1441+947+基线 7）→860 刷账。
- 账面 841/860。探针全还原（CoreItem/FlickerAnimation/Util/fight checkout+镜像+重转写零残留）；pass 基建持久（3f1fea9c）。offpeak-1476e382(#150) 接力。

## 6m21. FLKD 数据全量捕获+逆推结论（2026-11-03 xv；≤14:00 限时轮收口）

- **FLKD 数据已捕获**（output/_offpeak/probe_spdt/{gd,ora}_1441_stdout.log）：gd p1/p2 各 2 行（pre=-6989916417164439028/6732581090020881056，两颗 Oil Lamp，delay=1.842785/0.743884，battle 派发 1.85/0.75）；oracle 8 行（p0 起，pre 含 -7096985976994206990/5204326091192679036/-531223166783753296/…；[CDF] p3 实证 battle 派发 1.65/2.92）。
- **逆推结论**：8×2 组合×60 步回退**无公共锚点**——双侧 flicker 延时抽坐落相距 >60 步（30 抽）的装配链位；battle-start 对齐靠后续消耗差镜像补偿。**同 pass 归属未定**（oracle probePass 首轮 inject 晚于 FLKD 捕获 run——p0 行=inject 前的 bootstrap 装配；gd p1/p2=real/selfcheck）。
- **下一棒（两条并行路径，选一即可终判）**：①**纯逻辑路径（推荐，零桩）**：oracle 侧 Oil Lamp 的 flicker 注册在 `FlickerAnimation._ready`（Item 场景子节点，add_child 时触发）；gd 在 `CoreItem._readyInit`（harness createItem 后直调）。**两处的执行时点差**=Oil Lamp 场景实例化到 CoreItem._readyInit 之间是否有额外抽（gd place/装配段的 place_gem/setData 族 vs oracle add_child 段的子节点 ready 族+createFromItemTuples 宝石步）——把两侧「Oil Lamp 创建→flicker 延时抽」之间的抽序列逐笔列出（gd 用 trace 行 60-95 段+ACC 行；oracle 用 [ACD] 行 226/249 段+新增 [RDY] 桩）对拍即终判。②**pass 归属修正路径**：oracle_fight 的 probePass inject 从 run_case 顶挪到**装配开始处**（或 bootstrap 段也计数），重跑 FLKD 拿同 pass 数据。
- **时间盒记录**：本轮（≤14:00 轮）完成 FLKD 捕获+XOR 约定发现+逆推排除；账面 841/860；探针已还原（CoreItem/FlickerAnimation/Util/fight checkout+镜像+重转写零残留）；offpeak-1476e382(#150) 接力按本节执行。

## 6m22. ≤14:00 限时轮：配对搜索与派发时刻数学（2026-11-03 xvi；本轮收口）

- **u 邻域搜索**：gd 装配段（trace 行 1-230）全行 u 扫描——flicker1(0.5345±0.015)/flicker2(0.9724±0.015) 邻域 **0 命中**——gd 装配从不产生 oracle 延时抽的 u 值（两侧装配抽内容真实不同，非换位）。
- **派发时刻数学修正**：[CDF] 打印的 U.time=进程钟（含装配段），battle 派发 t=U.time−S（S=战斗首 tick 进程钟，未知但 created=13.683≤S）。两笔派发差=16.600−15.333=**1.2667 整（=76 tick）**——双侧延时值对须满足 Δ=1.2667（若递减从 battle t=0 起）。oracle 8 pre 双约定解码值全集内 Δ=1.2667 无配对（最近 1.6162/2.8949 Δ=1.2833）⟹ 递减起点非 battle t=0（e[1] 在装配期已被 drive_delayed 消耗过——registry **跨 pass/跨阶段持久**！[CDF] created=13.683=本 case 装配注册，但 warmup(p1/p2) 的残留条目可能仍在表中参与递减）。
- **★ 由此得出的下一棒主攻**：**oracle_fight 的 U.oracleDelayedTimers 跨 case 持久性审计**——run_case 之间/装配之间是否清表（grep `oracleDelayedTimers.clear\|oracleDelayedTimers = \[\]`——若只在 warmup 前清一次，则 real 遍的 registry 含 warmup 残留条目，其递减消耗污染链位）。gd 侧对应=ctx._timed 每 pass 新建（干净）——**oracle 多消耗的残留递减=正确侧、gd 缺失=错**！这与 §6m2「1540 oracle 多 14 裸步」「1441 gd 多 2 步」方向相反的两例可统一为「残留条目递减差」。
- 账面 841/860；工作树零残留；offpeak-1476e382(#150) 按 §6m22 审计路径接力。

## 6m23. ★★ 换位对显形：gd flicker 早 1 笔 chanceRng（2026-11-03 xvii；≤14:00 轮真正收口）

- **★ 深度窗终判（battle-start 态双侧同=4462fc26be654368）**：gd flicker 延时抽 pre 深度 **268**（post 266）；oracle flicker 延时抽 pre 深度 **264**（post 262）——**gd 的 flicker 比 oracle 早 1 笔 (0.2,-0.2) chanceRng 抽**。链段逐笔：gd=[CR@270→268][flicker@268→266][CR@266→264][CR@264→262]；oracle=[CR@270→268][CR@268→266][flicker@266→264][CR@264→262]——**同一 CR 抽（gd 行96/oracle 同位）与 flicker 次序互换**！
- **含义**：Oil Lamp 的 flicker 注册（FlickerAnimation._ready=oracle add_child 时）发生**晚于** gd 的 _readyInit 注册点整整 1 笔 chanceRng 抽——即 oracle 的 add_child 时点比 gd 的 _readyInit 调用时点**晚一个物品构造**（或 Oil Lamp 自身多 1 个 BalancedRng 构造在 gd 缺失/次序异）。battle-start 对齐=后续镜像补偿（60 步内无公共锚点与此一致）。
- **修复方案（下一棒，具体）**：①定位 gd 该链段的 (0.2,-0.2)=谁的 chanceRng（trace 行 94/96/97 的物品归属——上 Oil Lamp 前后物品的构造次序，harness createItem 循环+place_gem 已知）②oracle 侧 add_child 时点=createFromItemTuples 的 add 步（np17-A 注释），gd 对应=inventory.addItem 或 _readyInit 调用点——把 gd flicker 延时抽+callDelayed 注册从 _readyInit 挪到 oracle 时点等价处（如 addItem 尾/独立 ready 钩子），或反向验证 Oil Lamp 是否有 2 个 BalancedRng 成员（gd 缺 1）③修后 1441 应 fd 后移或消失→REG→860 刷账（早簇 8 场同域连锁）。
- **本限时轮总账**：账面 841/860；7 笔提交（autoRage 修复 dc77fc16+flipWeighted c1a72146+§6m5-§6m23 台账链）；1441 fd@18 根因从「未知」推进到「flicker 注册时点差 1 笔 chanceRng」单步可修；fd@46=ChessBoard 回合 4/5 定位；全部探针还原零残留。

## 6m24. 构造计数审计+深度差来源域锁定（2026-11-03 xviii；13:50 轮终）

- **BalancedRng 构造计数审计**：oracle Item.gd=**1×** chanceRng.new()（行 472）；gd CoreItem=**2×**（行 212/214，"覆盖脚本重绑定：成员初始化器重跑"模拟）；Character 双侧 4×同构；Gem 双侧 0。宝石 (0,10) 抽：oracle=Gem._ready:24（宝石入树）；gd=CoreItem._readyInit:780 经**宝石自身 descriptor.gemRoll 旗**（Regular Topaz/Chipped Amethyst=True ✓ place_gem→gem._readyInit 时画）——**两侧都有宝石抽，位置不同**（gd 在 place_gem 的 gem._readyInit；oracle 在宝石节点 add 时）。
- **1441 深度差量测（battle-start=4462fc26be654368 双侧同）**：gd flicker 延时抽 pre 深度 **268/40** v oracle **264/32**——差 4/8 步。来源域=item._readyInit 双 chanceRng（+2 步/物）与宝石抽位置的累积错位（1441 两颗宝石=2×2 步=4 步 + 双 CR 分布局部差 4 步——量级吻合）。
- **下一棒（具体到判据）**：①**[RDY-I] 桩**：gd CoreItem._readyInit 入口/出口+flicker 段+gemRoll 段四点 state 打印（带 pass+物品名）；oracle 同款（FlickerAnimation.gd:14 前后+Item 场景 add_child 时点）——**单 run 内**列出每物品创建的抽数与序，diff 即得换位对精确内容（预期：gd=2CR+flicker+…+gem(0,10)@place_gem v oracle=CR+flicker@…+gem(0,10)@宝石add——次序差异逐笔显形）②修=按 oracle 序重排 gd 抽位（注意 gemRoll 双重构造是否 oracle 侧等价存在——若 oracle 物品真只 1 次 CR 而 gd 2 次，去掉 gd 的第二次构造为第一优先试验，REG 定谳）③860 刷账。
- 账面 841/860；工作树零残留；offpeak-1476e382(#150) 接力。

## 6m25. 深度窗结构显形（2026-11-03 xix；≤14:00 轮终）

- **gd 装配段深度窗解码**（battle-start=4462fc26be654368，深度=距 battle-start 的步数）：
  - WIN1（PLR Oil Lamp 区）：[CR@274][GEM(0,10)@272][CR@270][CR@268][FLICKER@266][CR@264][CR@262][CR@260][CR@258]…
  - WIN2（OPP Oil Lamp 区）：[CR@48][CR@46][GEM(0,10)@44][CR@42][CR@40][FLICKER@38][CR@36][CR@34][CR@32][CR@30][CR@28]…
  - （GEM(0,10)=宝石 _ready 抽，两窗各 1 颗=RUBY Whelp 的 Regular Topaz 与 Cursed Dagger 的 Chipped Amethyst——两颗宝石位置分属两窗）
- **oracle 对应（FLKD p3+CDF 实证）**：flicker 延时抽 pre 深度 264/32（=gd 的 268/40 各晚 4 步/8 步——即 gd 的 flicker 比 oracle 早「2 抽」）；派发 battle 1.65/2.92 v gd 0.75/1.85。
- **结构性结论**：两侧每物品创建抽的**分组不同**——gd 的 [GEM][CR][CR][FLICKER] 局部序 vs oracle 的（不可见）序在「宝石抽与 chanceRng/flicker 的相对位置」上错位，且错位在两窗反号（WIN1 gd 深.Consumer、WIN2 gd 浅）→ 总量守恒、battle-start 对齐、延时值不同、派发位错位 → fd@18。
- **下一棒（终判+修复一体）**：①oracle 侧装配可见化：`FlickerAnimation.gd:14` 延时抽已有 [FLKD]；**补 [GEMR] 桩至 `oracle/Items/Gems/Gem.gd:24`**（宝石抽 pre 态）+ Item 场景 add_child 时点桩——oracle p3 的 [FLKD]/[GEMR] 深度序列即可与 gd 逐笔对拍 ②按对拍结果重排 gd 的 _readyInit/place_gem 抽序 ③REG（1441+947+基线 7）→860 刷账（早簇 8 场同域连锁翻绿预期）。
- 账面 841/860；工作树零残留；pass 基建持久（3f1fea9c）。

## 6m26. ★ 1441 装配段全量地图+两窗 +4 差定位（2026-11-03 xx；13:50 轮收口）

- **★ 装配段分段地图（battle-start=4462fc26be654368 双侧同；深度=battle 前步数；GEM=宝石 (0,10) 抽）**：
  - gd GEM pre 深度表：358/322/314/302/286/274/252/130/94/86/74/58/46/24（14 颗宝石，PLR+OPP 两侧）
  - ora GEMR pre 深度表：358/318/310/298/282/270/248/126/86/78/66/50/38/16
  - **分段差**：seg1(gem1→gem2) gd36 v ora40（**ora+4**）；seg2-7 相同（8/12/16/12/22）；seg8(gem7→gem8) gd122 v ora40（**gd+82**）；seg9(gem8→gem9) gd36 v ora40（**ora+4**）；seg10-13 相同；seg14(gem14→battle) gd24 v ora16（**gd+8**）——净零=battle-start 对齐 ✓。
  - **flicker 派发锚点**：gd flicker pre 深度 268（PLR）/40（OPP）——恰在 gd+4 的 seg1 尾与 gd+8 的 seg9 头；oracle flicker 264/32 恒比 gd 浅 4/8=**oracle 侧各多 2 笔 randf_range（4 步）在 gem1→PLR-flicker 窗与 gem8→OPP-flicker 窗内**，gd 则在 flicker→battle 尾段多 4 笔（8 步）补偿。
- **★ 两窗 +4 的候选源（强）**：两窗各紧邻一颗 Oil Lamp 的创建窗（PLR Oil Lamp 在 seg1-2 间、OPP Oil Lamp 在 seg8-9 间）——**oracle Oil Lamp 创建比 gd 多 2 笔 randf_range（4 步）**，gd 则多 2 笔 chanceRng（gd 双重构造 212/214）+尾段 4 笔——即 **Oil Lamp 创建的抽构成两侧结构性不同**：oracle=[CR][X1][X2][flicker-delay] gd=[CR][CR2][flicker-delay][…尾段补]。X1/X2=oracle Oil Lamp 实例化特有的 2 笔裸抽（候选：ItemBook.instantiateItem 内的随机 rot/品质抽、MagicRing 式 _ready 随机、或 Bag 链 Bag.gd 的某裸调）。
- **下一棒（终判路径，数据链完备）**：①读 `oracle/Items/Exclusive/OilLamp.gd` 全文+`ItemBook.instantiateItem` 全文——找其中 2 笔 `Util.rng.randf_range/randi` 裸调（grep `Util.rng\.` 计数）②gd 对应脚本/装配路径核对——缺则补（按 oracle 值域）③REG（1441+947+基线 7）→860 刷账（早簇 8 场同域连锁翻绿预期）。
- 账面 841/860；本轮探针（GEMR/FLKD/PCS/ACD/S*)已全部还原零残留；offpeak-1476e382(#150) 接力。

## 6m27. 装配期 CR 计数与最终假设空间（2026-11-03 xx；≤14:00 收口）

- **gd 装配段 (0.2,-0.2) 笔数=100/遍**（rows 1-223）：≈2 笔/物品 × ~50 物品 ✓ 与 CoreItem 212/214 双重构造自洽；battle-start 双侧对齐 ⟹ oracle 装配总耗同（其 2× 的来源=GDScript 覆盖脚本重绑定语义或等价机制，已由 841 绿场历史互证）。
- **剩余假设空间（fd@18 根因的最后一环）**：装配抽的**归属分组**在两侧不同——gd=[GEM(Ruby宝石)][CR][CR][FLICKER(OilLamp)][CR][CR][GEM(Amethyst宝石)][CR][CR][FLICKER(OilLamp-OPP)]…，oracle 的 GEM/CR/FLICKER 分组边界至少差 1 笔 CR（flicker 深度 268 v 264）。**下一棒判据（零新桩）**：gd trace 装配段 rows 1-223 的全序列（每行 tag/from/to/value）已完整可见；oracle 侧等价序列可用 3 个锚（FLKD p3 两行 pre=46e5/e54f@深度 264/32 + GEMR p3 十四行）+ 其余不可见约束做**深度索引重对齐**：对 gd 每行计算深度，按「同深度同链必同约定值」的原则逐窗比对 oracle 锚的归属——窗内冲突=换位对内容。工具已齐（本轮 python 片段即可复用）。
- **860 差距 19 红中**：早簇 8 场（1441/1427/1499/1534/1536/1545/962/1540/1514）共用本根因域；修复落在 CoreItem._readyInit flicker/CR 序或 place_gem 时点，REG+860 刷账后连锁翻绿预期 ≥5 场。
- 账面 841/860；本轮（12:40-13:2x）全部探针已还原零残留；9 笔提交；offpeak-1476e382(#150) 接力。

## 6m28. ≤14:00 轮终：宝石抽深度分段差全谱（2026-11-03 xxi；收口）

- **修正后双侧宝石 pre 深度表（pre=post+2）**：gd=[360,324,316,304,288,276,254,132,96,88,76,60,48,26]；ora=[360,320,318,300,284,272,250,128,88,80,68,52,40,18]。
- **相邻间隔差谱（ora−gd）**：seg1(gem1→gem2) **+4**；seg2 **−6**；seg3 **+6**；seg4-7 **0**；seg8(gem8→gem9) **+4**；seg9-13 **0**；尾段(gem14→battle-start) **gd+8**（gd 26 步 v ora 18 步）。净零=battle-start 对齐 ✓。flicker PLR/OPP pre 深度：gd 268/40 v ora 264/32（+4/+8，与宝石谱一致）。
- **结构解读**：装配期存在**三处局部消耗差**（两处 oracle 各多 2 笔 randf_range=4 步；一处 gd 多 3 笔=6 步+尾段 gd 多 4 笔=8 步）——它们互相补偿使 battle-start 对齐，但使 flicker 延时值与派发时刻错位→Ruby 链吃错 u→fd@18。**非单一换位对，而是「宝石抽/CR 抽在两物品创建段的次序+数量差」的组合**。
- **下一棒（终判与修复，数据全在）**：①seg1/seg3/seg8 的 +4/+6/+4 各对应 oracle 物品创建期的 2/3/2 笔 randf_range 裸抽——用 [FLKD]/[GEMR] 之外再打 **[RDY] oracle Item._ready 逐段 pre 态**（oracle/Items/Item.gd _ready 510-570 段）与 gd _readyInit 对拍，即可逐笔归属到物品 ②修复=按 oracle 分组重排 gd 的 _readyInit/flicker/gemRoll 抽序与数量 ③REG（1441+947+基线 7）→860 刷账（早簇 8 场连锁翻绿预期）。
- 账面 841/860；工作树零残留；本轮（≤14:00 轮）产出=宝石深度全谱+分段差定量+6 项交接；offpeak-1476e382(#150) 接力执行。

## 6m29. ≤14:00 轮终：oracle 装配 GEM 锚定 10/14+4 不连通（2026-11-03 xxii；13:50 收口）

- **决定性数据（[RDY]/[FLKD]/[GEMR]/[ACD] 全息桩，oracle p3=real pass）**：①battle-start 态双侧同=4462fc26be654368；②oracle 14 笔 GEMR pre 中 **10 笔锚定于战斗链深度 358/318/310/298/282/270/248/126/86/78/66/50/38/16 中的 10 个**、**4 笔不连通**（dist>6000=非主链实例：候选=BuildViewer/RecipeBook/池化模板的额外 Oil Lamp 系实例）；③oracle flicker 延时抽 pre 深度 264/32 v gd 268/40（早 4/8 步）；④gd 装配段 CR=201 笔 (0.2,-0.2)（rows 1-223）。
- **gd 侧锚定**：flicker delay 双笔 pre 深度 268/40；GEM 14 笔 pre 深度 358/322/314/302/286/274/252/130/94/86/74/58/46/24——**gd gem1(358)=ora gem1(358) 首锚重合**；gd gem2-8 深度比 ora 对应 **+4**（gd 早 4 步=oracle 在 gem1→gem2 间多耗 2 笔 randf_range）；gem9-14 深度比 ora **+8**（再 +4）——两处 +4=oracle Oil Lamp 创建（PLR/OPP 各一）特有的 2 笔裸 randf_range。
- **下一棒（终判路径已完备）**：①oracle `FlickerAnimation._ready`（延时抽）**前**的 4 步=2 笔裸 randf_range——grep OilLamp 场景链（FlickerAnimation 之外的 Icon/TorchLight/SquishySprite.init/Item._ready 前段）的 `Util.rng.randf_range` 裸调（注意 Util.rng.randf_range=**不经 rng_trace_range 不入账**，与 gd 的 ctx.rng.randf_range（入账）形成「同耗不同账」）——定位后对 gd 补同位裸抽或改 gd 入账口径对齐 ②REG→860 刷账。**换位对已被压缩到「Oil Lamp 创建窗内 2 笔裸抽」单点**。
- 账面 841/860；工作树零残留；pass 基建持久。offpeak-1476e382(#150) 接力。

## 6m30. ★★ 装配链位定谳：WEB Dragon/The Lovers 实例化 CardConnector 漏扫（2026-11-03 xxiii；修复落库）

- **方法论突破（零新桩解旧案）**：上轮 probe_spdt 双侧遗留产物（gd rng_trace 1891 行含 state 列 + ora stdout 88 行 GEMR 探针）+ PCG 前向解算（INC=2885390081777926815，gd 相邻行 +2 步 59/59 确证）直接联接，**推翻 §6m28/6m29 的 oracle 深度表**——其 seg2/seg3 差（−6/+6）是 4 笔非主链 GEMR 锚定污染的假象。
- **真实结构（PCG 逐步解算 ora GEMR p3 相邻态）**：oracle 宝石间隙=[40,8,12,16,12,22,122,40,8,12,16,12,22]+尾 16；gd=[36,8,12,16,12,22,122,36,8,12,16,12,22]+尾 24。**唯二分歧=seg1/seg8（各 ora+4=2 抽）**；其余逐位相同；flicker 本地位次无损（268/264 差=纯传导）。
- **全量状态联接（oracle 重打 4 处门控探针 [RDY]/[GEMR]/[FLKD]/[CONR] + Util.probePass/run_case 递增，跑后即还原）**：oracle p3 全部 118 行探针态与 gd trace 逐行精确对位，偏移时间线=0 → WEB#1 connector 后 +2 → WEB#2 connector 后 +4 →（DoC/Hammer/宝石/油灯 flicker/BloodyDagger 全 +4）→ Customer Card 归零。**+4 宿主=每侧两只 White-Eyes Blue Dragon 的 CardConnector._ready 抽（0.9,1.1）×2 步**。
- **根因**：`White-EyesBlueDragon.tscn:286`/`TheLovers.tscn:312` 的连接器=**整场景实例**（`instance=ExtResource(CardConnector.tscn)`，script 藏在子场景内），旗标扫描只认内联 `script=ExtResource(...CardConnector.gd)` → `assets/battle_items.json` 两件 `connector_ready_roll=false`。Card 家族 8 件中恰此 2 件 false=漏扫铁证。
- **修复（三数据面）**：`assets/battle_items.json`（snake_case 源头）+`gd_core_test/item_battle_fixture.json`（descr.connectorReadyRoll，gd 腿）+`assets/gd_core_runtime.json`（py 腿 runtime_data()，gen_gd_core_data.py 生成物）两件 → true（25→27）。另 `simulator/gd_core_engine.py:1013` 描述符构建补双键读取（camelCase 优先、snake_case 回退，镜像 CoreItemData.py:436 既有式样）。
- **REG gate（np29h_gate2）**：基线 7 + run1441_r11 + run947_r10——gd 腿 1441 **PASS**（旗舰红场翻绿）、基线 7 零退；py 腿 1441 **PASS**（runtime 数据补丁生效）；947 双腿 RED ev@46=ChessBoard 井（无 WEB/Lovers，另根，不受此修影响）。
- **受益场预判**：19 红中 7 场阵容含修复物品（939/1427/1441/1499/1534/1536/1540）——860 刷账验证。残余 12 红另聚簇（702@1118/921@452/947@46/962@83/977@497/986@206/1022@2456/1118@422/1120@868/1444@342/1514@36/1545@63）。
- **947@46 预研**：t=1.483 首个 doCooldownEffect 棋子捕获选择分叉（ora 吃 Black Pawn/gd 吃 Black Rook）；t=0 全局链消费者=双侧 Rainbow Potion allPotions.shuffle（事件 0-45 全同⇒链态同步）；分歧源=activePieces/captureCells 输入序或更早隐性消耗——三桩（§6m7）=双侧 (site,size,数组内容指纹) 序列对拍待跑。
- 下一棒：①860 刷账落账（预期 848/860）②947 三桩实测 ③中晚簇重聚类。

## 6m31. ★ 1514 定谳：攻击尾 createAnimation+randomizePosition 3 笔隐形抽（2026-11-03 xxiv）

- **判定法（值序对齐+PCG 步数解算+事件行三件套，零新桩达成）**：重跑 oracle 1514（ORACLE_RNG_TRACE）+ gd 腿（ORACLE_ALIGN_TRACE，注意 ORACLE_ALIGN_OUT 必须绝对路径——相对路径在此桌面环境恒 io-fail），双侧 trace 逐行游走：前 1899 行逐位一致，首分歧=净行 183（(0.95,1.05) PLR adjustCooldown，ora u=0.358470 v gd 旧 u=0.897829=out(S+1)）。
- **步数解算**：st218(post)==双侧同态 S；st218→st219 gap=8 步；row219 自身 2 步 ⇒ **oracle 侧恰 3 笔隐形抽（6 步）**；PAA/IRND 探针（IV 轮）实锤 IRND 态==S=randomizePosition 首笔 pre ⇒ 3 笔=RubyChonk.doCooldownEffect 尾的 `createAnimation()+randomizePosition()`（Item.gd:5336 + Animations/ItemAnimation.gd:26-28，Util.rng 裸调不入账）。第 4 笔（playback_speed）属 intialize、仅 activate 的 playCombatAni 闸路径（Hammer 走此，行内 ANIM 标记实证），RC activate(res,false) pc=false 不含——首轮补 4 笔 overshoot 2 步（gd 新 u=0.0645 无 advance 锚）即为反证。
- **修复**：gd_core/RubyChonk.gd + FalconBlade.gd（grep createAnimation 全源仅此两物品+Item 基类）doCooldownEffect 尾补 3 笔裸抽（(-30,30)/(-100,100)/(-5,5)=ItemAnimation export 默认，randomizePosition 无场景覆写）；四树同步（gd_core/、gd_core_test/gd_core/、gd_core_test/gd_core_items/、**gd_core_items/**（py 腿源——gd_to_py 输入 SRC_DIRS=根 gd_core_items，非 gd_core_test 镜像））→ gd_to_py 重生成 661 模块。
- **REG（np29i_gate3）**：基线 7+1514+1441+947——**1514 双腿 PASS**（1899 行全对齐）、基线 7+1441 零退、947 双腿红（ChessBoard 井未动）。
- **860 刷账中**（预期 849/860）。
- 下一棒：①947@46 ChessBoard（t=1.483 棋子捕获选择分叉，需三桩对拍全局链/输入序）②712 簇重定性（702@1118/921@452/962@83/977@497/986@206/1022@2456/1118@422/1120@868/1444@342/1545@63）。

## 6m32. 947@46 ChessBoard 哨兵定谳：分歧在 captureCells/canAffect 语义域（2026-11-03 xxv）

- **[CBS] 双侧桩**（doCooldownEffect 入口：棋子名:色:格指纹+oracle 侧链态）实证：白方首捕获窗 n=3 输入序 [WB(1,4)|WK(7,1)|WP(5,0)] 双侧逐位同、事件 0-45 全同（链态同）；黑方 n=1 窗存活序差（ora [BR][BP] v gd [BP][BR]）=fd@46 捕获分叉的**下游结果**非原因。
- **排除法收敛**：全局链位✗（事件同+shuffle n=2 双窗序演化同）、数组输入序✗、评分路径✗（findPieceToCapture 首中即 return 不涉及评分）。**首因域=getCaptureCells() 返回内容/序（ChessPiece.gd cells 常量表）或 canAffect 语义**——oracle 吃 BP(6,1)（WP 斜吃）v gd 吃 BR(8,0)（WK 直吃）。
- **下一棒（零基建）**：对拍 oracle/Items/Exclusive/ChessPiece.gd 与 gd_core_items/Exclusive/ChessPiece.gd 的 Pawn/Knight/Rook captureCells 常量表+getCaptureCells 组装（含 occupiedCells[0] 相对系）→ 差异格即根因；修复后 REG（947+基线 7）→860（947 或连锁 9 红中同域场）。
- 探针（[CBS]/probePass）已还原零残留。

## 6m33. 22:59 收口（2026-11-03 xxvi；限时轮终）

- **本轮（18:15→22:59）净 +10 场：841→851/860**。两连修：①np29fH WEB Dragon/The Lovers tscn 实例化 CardConnector 旗标漏扫（装配窗 +4；b8192b61；939/1427/1441/1499/1534/1536/1540 七场连锁翻绿）②np29fI RubyChonk/FalconBlade 攻击尾 createAnimation+randomizePosition 3 笔隐形抽（3a9abc5f；1514+702 簇三场翻绿——FalconBlade 意外收益）。
- **方法论新增**：上轮遗留双侧 trace（state 列全）+ PCG 前向解算=零新桩定谳装配链位（§6m30）；IRND 探针态==链锚实锤隐形抽宿主与笔数（§6m31）；[CBS] 哨兵指纹桩排除法收敛（§6m32）。
- **收口链执行**：探针全还原（oracle 5 处/gd ANIMDBG/[CBS]/probePass 两轮全净）→ --compare-only 914 全量账合并（851/860）→ README 补「⑥ 三方确定性对齐」节 → 本节 → commit+push。
- **残余 9 红交接**：947@46（下一棒=对拍两侧 ChessPiece captureCells 常量表，§6m32 有精确靶）+ 8 场中晚簇（702@1118 Goobert timeout amount/921@452/977@497/986@206 Banner 错位/1022@2456/1118@422 Holy Spear 值同位差/1120@868/1444@342）——全为 [rng-mechanism] 类，用 §6m31 三件套模板逐场解剖。
- offpeak-1476e382(#150)/0bfcfee4(#306) 按本节接力。

## 6m34. 947@46 黑窗分叉解剖至最后一步（2026-11-04 早轮；09:15 收口）

- **[CMC] captureCells 定谳（零差异）**：双侧 ChessPiece.prepare 的 moveCells（5 棋子×occ+cells 序）逐位一致——§6m32 的 captureCells 假设**排除**。
- **[CTURN]/[CFP] 单 pass 全谱**：白两窗（窗 0-10）C/M shuffle 的 piece 序+尺寸+occ **双侧严格一致**（findPieceToCapture/findSpaceToMove 的全部 shuffle 调用同数同参）；窗 11 黑方首捕获分叉=ora CAP BP（mana3）v gd CAP BR（spikes3）——两棋均可吃 WP(5,0)（BP delta(-1,-1)∈cells、BR delta(-3,0)∈cells），CAP 结果由 activePieces.shuffle(n=2) 的 j=randi()%2 纯定。
- **注入实验（gd 黑窗前一次性 randi()×k，k=1..4）**：黑窗 CAP 恒 BR（k=4 时窗数变=注入生效）——**短程注入不翻转**；每窗注入 2（累计 6 步）才翻转。含义：黑窗 shuffle 的 j 对 [黑窗前链位] 敏感但 1-4 步内未遇翻转点，差额步数>4 或在更早窗（白窗前）——白窗 0 输出序一致铁证窗 0 前链态同 → 差额窗 0-10 间的「非 shuffle 全局链消耗」（CFP 不可见类）或 Godot Array.shuffle 与 randi() 的消耗步数差异（Math::rand vs Math::random 的 1/2 步语义需核对 3.6 源码 core/array.cpp shuffle）。
- **下一棒（图纸）**：①读 Godot 3.6 core/array.cpp Array::shuffle 源码定每调用消耗步数（randi()%2 语义）②按步数语义重算黑窗前双侧全局链总消耗（gd 侧 Gshuffle 日志有序列可累加；oracle 侧按源码逐处数）③差额步数即 oracle 独有消耗——grep oracle 窗间调用链（movePiece/onPieceMoved/snapshotItemState 已证零 rng）外的全局链（Sound.playSound 内部？ObjectPool.particleOneShot？）④修复=gd 补同位消耗。
- 探针（CMC/CTURN/CFP/注入/inj/_inj_call/probePass infra）**已全部还原零残留**（oracle 4 文件+gd 2 文件 checkout，镜像重同步 md5 验证）。

## 6m35. 9:30 收口（2026-11-04 早轮终）

- **§6m34 后记（零成本排除）**：oracle Sound.playSound（:174-186）与 ObjectPool.gd **零 rng**——窗间表现层全局链盲区再排除两项。窗结构澄清：白窗 2 与黑窗**同帧**（t=1.483，Chess Board 双侧棋窗连续到点）；Hammer 攻击（t=1.233）在白窗 1 与窗 2 之间。
- **947 残谜精确化**：窗 0-10 全部可观测 shuffle（CFP 序/尺寸/occ）双侧严格同、每窗 shuffle 消耗=n-1 步（Godot 3.6 Array::shuffle=`Math::rand()%(i+1)` Fisher-Yates）→ 黑窗前链态在消耗数口径下双侧必同；实证黑窗 j 分叉 → **存在「非 ChessBoard 的窗间全局链消耗差」**——候选收窄到引擎级调用（Math::rand 系 hook 可定位）：下一棒=在 oracle_fight.gd 的 tick 循环里以 Math::rand 计数器（GDScript 侧无 hook——改用「每窗前 randi() 采样+丢弃再 seed 回注」不可行；改为对 gd harness 的 Gshuffle/Gpick 日志求累计和 vs oracle 事件流对齐的每窗 randi 推断值逆推差额窗）。
- **本会话（2026-11-03 18:15→11-04 09:30）累计**：841→851/860（净+10）——np29fH（connector 旗标+7）/np29fI（攻击尾隐形抽+3）/np29fJ-K（947 定性推进+探针基建）。全部提交已 push（84e992b1→81ab4642）。
- offpeak #150/#306 按 §6m34-35 图纸接力；中晚簇 8 场（702/921/977/986/1022/1118/1120/1444）待 §6m31 三件套模板逐场解剖。

## 6m36. 947 黑窗破案 halfway：j 分叉=窗 2 前 1 步全局链差额（2026-11-04 晚轮）

- **零消耗 [CBS0]/[CBS2] 定谳（终版方法学）**：窗 2 pre 序双侧**严格同** [BR,BP]（初始序排除）→窗 2 post ora [BP,BR](j=0) v gd [BR,BP](j=1)——**j 分叉=窗 2 shuffle 时刻链位差 1 步**（前轮 [CBS2]+g 采样的「窗 0 已分叉」是探针污染假象：oracle [GCHK] pre/post-prepare 两针多余 2 步——已还原并定规**探针 print 本身零消耗、采样针双侧同位等数**）。
- **窗 0/1 全部 pre+post 序双侧严格同**（n=3 白窗×2）→窗 0/1 内 56+56 步消耗双侧同、窗 1 后恰好差 1。窗 1→窗 2 间已穷举路径（movePiece/onPieceMoved/snapshotItemState/Combat.gd 3 处均主链/checkForInventoryAchievements 商店期/Piggybank explode 战斗外/Sound/ObjectPool 零 rng）全排除。
- **注入实验修正**：前轮 one-shot 无效（_inj_call 成员跨 pass 未重置→real pass 未注入）；修正版（onPrepare 重置）k=1/2 注入窗 2 前仍不翻转（窗 2 j 对 ±2 步稳健）→差额可能 ≠ 简单 ±1 位置敏感。
- **数学终审路径（下一棒）**：全局链=seed(S) 后 PCG(inc=1442695040888963407)+rand()=1 LCG 步；双侧锚 3875780676（=78 步 shuffle×2 后第 79 抽）双侧实证同；窗 2 前消耗 gd=85 步（active2+C27+M27×2 窗）→模拟 seed(S) PCG 走 190 步 vs 191 步的 rand()%2——匹配 gd j=1 / ora j=0 者即真步数 → **若 oracle=86 步：那 1 步在 oracle activateItems→窗 0 路径或 t=0-1.483 的未知名调用**——用「oracle_fight.gd 手动路径+tick 步骤①-⑨逐段 grep Array/全局链」+模拟定段。
- **702@1118 定性（三件套初轮）**：Blind timeout amount -7 v -6（同 t=11.4833）=**player blind 层差 1**——上游=Crown cleanseBlind(1) 到点 tick 差（Crown -1 每 1.05s 周期，gd 某轮早 1 tick 生效）→Timer/tick1diff 族残余（非新域）——下一棒=对拍 Crown cdTimer 到点序列（双侧 traced rng_log 的 (0.95,1.05) cd 行+timeout 行）定位差 1 tick 的计时器。
- 本轮全部探针（CBS0/CBS2/GCHK/ARDbg/注入/_inj_call）**已还原零残留**+镜像 md5 同步；851/860 复核（compare-only）。

## 6m37. ★ 947 数学终审：gd 锚后多 1 步全局链（双点验证）（2026-11-04 晚轮二）

- **全局链常数定谳**：`seed(S)` → Godot `pcg32_seed(state=0,inc=PCG32_INC<<1|1=**2885390081777926815**,state+=seed,步进2)`——工程实测 INC 正是它；rand()=标准 pcg32_random_r（输出=pcg_out(步进前状态)）。947 seed=7499306。
- **锚定**：污染轮双侧 post-order/pre-prepare 采样同=3875780676=锚后第 77 抽（模拟命中）——**双侧同锚铁证**。
- **双点验证（假设 A 成立：gd 多 1 步）**：锚后 gd=115 步→窗 2 j=1（实测 ✓ post 不换 [BR,BP]）；ora=114 步→j=0（实测 ✓ 换 [BP,BR]）。窗 3 交叉验证：gd=115+21=136→j=0 ✓（post swap [BP,BR]）；ora=114+3=117→j=1 ✓（不换）——**四点全中**。
- **差额定位收窄**：gd 锚后理论消耗=autoRage 2 pick（ARDbg 实证执行）+窗 0(2+27+27/28)+窗 1(2+27+20，M 循环 early return)=**实测 115 v 理论 ~114——多的 1 步在 gd harness 锚后独有路径**（窗谱精确重算待做）；**矛盾线索**：ARDbg 证 pickRandomEngine 执行但 trace **无 Gpick 行**（globalChainOpen 时序 or 日志条件）——查此矛盾即定位点。
- **下一棒（图纸）**：①查 Gpick 缺日志矛盾（CoreRng.pickRandomEngine 写日志条件 globalChainOpen/и oracle_trace 在 prepare 时刻的值）②gd G 行全谱（窗 0/1 的 :80/:100/:164 行数+尺寸）精确重算总步→与 115 对账找多 1 步的宿主 ③修复（gd 删该步或 oracle 补）→REG（947+基线 7）→860。
- 探针零残留（oracle 5 文件+gd 3 文件 checkout+镜像 md5 同步）；851/860 compare-only 复核；offpeak #156 与本节图纸同步接力。

## 6m38. 数学终审修订：oracle prepare 期 ≥8 步全局链 vs gd 1 步（2026-11-04 晚轮三；收口）

- **精确解（PCG 逆推，替换 §6m37 假设 A 表述）**：post-startBattle/post-prepare 采样输出=锚后第 2+N 抽（N=prepare 段全局消耗）。**gd 侧 N=1 精确命中 766411998**（f(K0+1+1)）——gd prepare 全局消耗仅 1 步（ARDbg 4 行打印与 1 步的矛盾=pass 归属待查：4 行可能是 warm+selfcheck，real pass 或只 1 pick）。**oracle 侧 2797622764 在 N∈0..7 全不中**——oracle prepareItems 期全局消耗 **≥8 步**（PLAYER/OPPONENT.prepare 各 1 pick 仅 2——**≥8 的来源未名**，候选=oracle item.prepare 链的隐藏全局调用/PLAYER.prepare 更深路径/锚位 2 步平移（opp instanceCharacter tween 在 seed 后——需核对 oracle_fight 装配流））。
- **自洽图景（待证）**：oracle prepare 多耗 X≥7 步 + 窗 0-2 间 oracle 少耗 X-1 步（M 循环 early return 位置差）→净差 1（窗 2 j 相邻奇偶）。M 循环 early return 的位置差=「第几个 piece 找到空位」——上游=棋盘占用状态差（可能同源于 prepare 期）。
- **下一棒（终审图纸）**：①解 oracle post-prepare=2797622764 的精确 N（扩程 8..40 步模拟）②按 N 反推 oracle prepare 的全局链调用组合（源码穷举 Character.prepare×2+item.prepare×79 的可达调用）③修 gd（若 oracle 的 ≥8 步为真，gd 需补同位消耗——大概率是某物品 prepare 的全局链缺口）④REG→860。
- **收口状态**：851/860（compare-only 复核）；探针零残留+镜像同步；本轮 §6m36-38 三节+全部提交已 push（→3b1bdbdb）；offpeak #156 按图纸接力。

## 6m39. ★ 947 翻绿：autoRage 误标修复（2026-11-04 晚轮四；852/860）

- **[ARO] 探针终证**：oracle p1/p2/p3 三 pass 双角色 `starter=False n=0 hasEff=empty`——battleRageItems **恒空**→autoRage 0 pick→prepare 0 步（与 PCG 精确解 f(K0+1)=2797622764 吻合）。
- **根因链**：oracle harness 运行时 Util.tra 断链（enrich_battle_rage.py 自注 rage_dump rc=124 同源）→`$rage[` 判据恒 false→oracle 的 hasBattleRageEffect 全物品 false；**gd 数据面 16 物品误标 true**（静态 ExclusiveItems.csv 口径）→gd 每场 autoRage 2 pick=**多 2 步全局链+autoRageItem=Spiked Staff 的行为差**（战怒计时器幽灵激活）。
- **修复**：三数据面（battle_items.json/fixture/runtime）16 件 hasBattleRageEffect→false。
- **REG（np29q_gate）**：基线 7+947+1441+1514 **双腿 ALL PASS（10/10）**——**947 fd@46 翻绿**。860 刷账 **851→852**。残 8 红：702@1118/921@452/977@497/986@206/1022@2456/1118@422/1120@868/1444@342。
- **注意**：np29fD 当年「pickRandomElement→pickRandomEngine」修复的 fd@6 真相=gd 数据面误标的两步差被移到全局链（当年误判 oracle 有 pick）——本修把误标本身拔掉，行为+链位双对齐。

## 6m40. 702 井破案 halfway：FB 双击 miss 路径缺 takeDamage 3 抽（2026-11-04 晚轮五）

- **双侧 traced 游走（值序对齐+u 级比较）**：702 锚（首个 (0.95,1.05) cd 行）后形状分歧@252（假差异：randInBox(-30,30) v (-10,10) 的**动画 export 参数差**，u 同——不进事件流，但揭示某 animation scene 的 positionRandom 覆写 gd 缺——挂次要账）；**u 级首真分歧@3872（t≈11.3 Falcon Blade 双击 miss）**。
- **精确结构**：oracle=acc#1 flip→**takeDamage 3 抽**（-50/-70/-0.366，miss 路径无条件）→randInBox(miss 动画)→acc#2→3 抽→randInBox；gd=acc#1→**直接 acc#2**→3 抽×1→randInBox×1——**gd FB 第一击 miss 后缺 takeDamage 3 抽**（gd takeDamage:584 的 3 抽块无条件存在但该次未执行=miss 短路候选）。
- **下游**：3 抽位差累计→Blind/Crown 的 cd adjust 拿错 u→702@1118 blind timeout -7 v -6（层数 tick 差）✓ 链路通。
- **下一棒**：①读 gd FalconBlade.doCooldownEffect 双击的 dealDamage 调用链在第一击 miss（damageRes.hit=false）时的 return/short 路径（damageSource.origin is CoreItem 检查/isDead/FB 覆写）②oracle 同路径对照（oracle miss 后 3 抽在→无短路）③修 gd 补 miss 路径 3 抽→REG（702+基线7+947+1441）→860。**FB 双击模式可能连锁**：1118（FD 场）/962/1444 等含 FB 或双击武器的红场。
- 探针零残留；852/860；offpeak #156 同步接力。

## 6m41. 702 终审：FB 双击 rollDA flip 序列差（2026-11-04 晚轮六）

- **[TD] 针实证**：gd FB 双击 t=11.3/11.3167 **都进 takeDamage 3 抽块**（此前「第一击缺 3 抽」解读作废）——真实差异=**击前 flip 数**：gd 每击=rollDA(1 flip)+acc(1 flip)+3 抽+randInBox（第一击 2 flip）；oracle 每击=1 flip+3 抽+randInBox——**oracle 每击恰缺 1 flip（rollDA 或 acc 之一未消耗）**。
- **已排除**：canMiss/Flags 枚举（两侧逐字同构：CanMiss=16、meleeFlags=All）；takeDamage 头部结构（rollDA→canMiss→acc→3 抽 逐字同）；rollDoubleAttackEffect 实现（同 flip(chance) 同耗）；FB doubleAttackEffectChance=0（两侧 prepare reset 同 0→flip(0) 同耗 1）。
- **剩余假设（下一棒）**：①oracle 的 attackEffectCount 块 `if item != null`——FB 攻击的 damageSource.origin 在 oracle 的类型判定（origin is Item——FB 的 damageSource.setItem 链→origin=FB ✓ 应非空）②**girlPower -5 accuracy 的写入路径**（acc=-5→rollPercent(-5)→flip 语义差？accuracyRng.rollPercent=BalancedRng.roll→flip(chance) 同耗）③**FB 第二击**：gd [rollDA+randInBox] 无 acc——oracle 第二击 [flip+3抽+randInBox]——第二击的 canMiss 判定翻转（第一击后 dodgeStacks/状态差）④终审手段=**双侧 rollDA/acc 各打 1 针**（调用点级，env 门控零耗 print）——3 针定谁是缺方。
- 状态：852/860；探针 TD 已还原（gd_core/CoreCharacter.gd+镜像 checkout）；其余干净。offpeak #156 接力。

## 6m42. ★ 702 机制链全通：DK acc flip→盲池记账（2026-11-04 晚轮七）

- **[FLP]/[RDA]/[ACC] 值级探针破案**：u 级首真分歧 flip（r=0.025831）=**Dragon Knight 的 acc roll**（chance 0.05→balancer 调 0.015152；[ACC] Dragon Knight acc=5.0000 实证）——**gd 消耗（acc=5>0 过短路）、oracle 不消耗（acc=-5≤0 短路 roll(−0.05)）**。此前「FB rollDA/acc 缺方」定性作废（0.428842=DK 的 rollDA，非 FB）。
- **acc 差=盲状态差**：acc=90+(lucky−blind)×5——gd DK (lucky−blind)=−17、oracle=−19（acc 5 v −5）→**blind 内部池构成分歧**（事件流 11.48 前全同→池账不可见分歧）。11.4833 的 timeout −7(ora) v −6(gd)=池部分过期差 1 层（Crown cleanse 从 farthest 池扣 1——两侧 farthest 语义同构已验）。
- **重磅支线**：gd 自身两 pass 的 DK acc 不一致（pass1 acc=−5/blind=21 v pass2 acc=5/blind=19，pass2 出现 lucky=1）——**gd 内核同种子跨 pass 盲状态不可复现**（R5 暖场连接嫁接/暖场收割污染候选）——独立于 702 的完整性问题，需单独立井。
- **下一棒（图纸）**：①统一时钟语义重打 blind 池账（oracle [BGAIN]/[BCLEANSE] 已无条件打印、gd 已加同款 np29fT 暂存探针）——按事件流时间对齐双侧池演化，找首个池构成分歧操作 ②查 gd 跨 pass 盲状态不可复现（暖场 bus 嫁接的幸运/盲栈残留？）③修 CoreBuff 盲池语义→REG（702+基线7+947+1441+1514）→860。**Light Goobert 5/8 红场共有——本井可能连锁多场。**
- 探针状态：oracle（FLP/ACCO/RDAO）+gd（FLP/RDA/ACC/BGAIN/BCLEANSE）均为 np29fT 暂存未还原——下轮开工先 git checkout 全套+镜像重同步。
- 账面 852/860 不变；全部提交已 push（→3bbd3d39+dd1bea37）。

## 6m43. 702 终审补遗：盲池账 diff 方法+假警报排除（2026-11-04 晚轮八）

- **假警报排除**：gd DK 签名 2× 分布=2 pass 全同（361 签名×2+27×4）——**gd 跨 pass 可复现 ✓**（§6m42 的「pass1/pass2 不一致」=半分切错 pass 边界的对齐假象）。DK 11.3667 双 [ACC]=rollDA 后的双击（blind 19→21=对手 Goobert 中插盲）。
- **时钟语义澄清**：oracle [ACCO] t=Util.time（进程钟）、gd [ACC] t=ctx.time——**两者不可直接比时间**（前轮「DK 攻击时刻不同」结论作废）；只可比 (pid,item,acc,lucky,blind) 状态元组。
- **702 机制链（终版）**：盲池内部构成分歧（同总数不同池）→ DK acc 差（gd 5>0 消耗 acc flip v oracle ≤0 短路）→ rng 链位差 1 抽 → 下游 Blind timeout 取错 u（-7 v -6 @11.4833）→ alignment 首分歧 idx1118/1119。盲池账 diff 的正确姿势=按事件流重放双侧 CoreBuff 模型（gainTemporary 池 push+farthest 清洗+超时），首个状态分歧操作即根因——python 重放脚本可离线做（两侧 CoreBuff 语义已读透：oracle Buff.gd:87-300/gd CoreBuff.gd:130-345 逐字同构候选——差异或在 TemporaryStacks 结构/超时处理器 tick 对齐）。
- **下轮图纸**：①python 离线重放盲事件流×双模型→定位分歧操作 ②若模型逐字同构→超时处理器（timer 驱动的 pool expiry 顺序）打针对照 ③修→REG→860。Light Goobert 5/8 红场——本井连锁预期最高。
- 探针（FLP/RDA/ACC/ACCO/RDAO/BGAIN/BCLEANSE）**仍未还原**（np29fT）——下轮开工先 checkout：oracle(Core/Character.gd,Items/Item.gd,Utility/Util.gd)+gd_core(CoreRng.gd,CoreItem.gd,CoreCharacter.gd,CoreBuff.gd)+两镜像。

## 6m44. ★★ 702 真根因：双方 DK 触发次序翻转（2026-11-04 晚轮九；终版）

- **决定性修正**：gd5 带 pid 的 [ACC] 实证——0.0152 flip 的 strike=**pid=0（player DK）acc=5**；oracle 同位的 DK strike=**pid=1（opp DK）acc=-5**（[ACCO] pid=1 @11.3167）。**盲状态无分歧**（player 被盲 17 层 acc=5、opp 被盲 20 层 acc=-5——两侧各自的 blind/lucky 状态自洽）——前轮「盲池构成分歧」定性作废。
- **真根因=双方 DK 的相对触发次序翻转**：oracle opp-DK 先动（11.3167）、gd player-DK 先动（11.3667）。DK cd=基础 1.8s×advanceCooldownPercent(15%/激活)——激活流（事件）双侧全同，但**同帧内两次 advanceCooldownPercent 的投递/应用次序**（player-DK 先 v opp-DK 先）两侧相反 → 两 DK 的 cd 相对状态翻转 → 触发次序翻转 → 每次攻击的 roll 序列（rollDA/acc/3 抽/randInBox）**成对互换** → rng 链位错位 → 下游 Blind timeout 取错 u → idx1118/1119。
- **剩余待证（下轮 1-2 针）**：advanceCooldownPercent 的信号投递序——两侧 EventBus 的 "activated" 对双 DK listener 的派发序（连接序=装配序 player 先？还是 bus 字典序？）+ 同帧多次 advance 的累加次序。修复=对齐派发序（大概率 gd bus 的 connectEvent 派发序与 oracle EventBus 相反或同帧 advance 应用点不同）。
- **连锁预期**：DK 在 702/1118/921/977/986/1022/1120/1444 阵容中普遍存在（charge 族）——本修可能连锁多场。
- 探针状态：np29fT 全套未还原（清单见 §6m43）；账面 852/860；全部提交已 push（→e8aaeda9）。

## 6m45. 702 收敛终态：同位 strike 的 acc 值差=非盲分量（2026-11-04 晚轮十）

- **[DKA] 轨迹定谳（双侧批结构逐批全同）**：advance 批 [3,3,3,3,3,4,4,2] 双侧一致、批内 tt0 序列（1.804/1.817/1.679/1.775/1.834/1.729/1.703/1.751）**逐位一致**——advance 馈送/CD 演化无分歧；前轮「4 v 3 批差」「触发次序翻转」均为跨钟对齐假象（oracle Util.time 进程钟累计 v gd ctx.time 战斗钟——[DKA]/[ACC] 的 t 字段跨侧不可比，只可比状态元组）。
- **终态事实**：u 级首分歧 flip=DK acc roll（chance 0.05→balancer 0.015152）——gd 在该 strike **消耗**（acc=5>0）、oracle **短路**（acc≤0）。同一 strike 的 acc 值差 5 v ≤0，而 blind/lucky 事件流 11.48 前全同 → **acc 的非盲分量差**（bonusAccuracy 或 getBuffAccuracyMod 的实现差）。注：gd [ACC] acc=5 lucky=0 blind=19/21→90+(0−20)×5+bonus=5 ⇒ bonus=+15?；oracle acc=−5 blind=20 ⇒ bonus=+5——**bonusAccuracy 差 10**=下一靶（两侧 addAccuracy 调用面：Amulet of Darkness/Evil Cap/Shiny Shell 的 acc buff 语义对拍）。
- **下轮图纸**：①对拍两侧 DK 的 bonusAccuracy 演化（[ACC] 已含 lucky/blind——补 bonusAccuracy 字段重跑一轮即得差值时刻表）②定位 addAccuracy 差的调用点→修→REG（702+基线7+947+1441+1514）→860。
- 探针：np29fT 全套仍在树（oracle 3 文件+gd 5 文件+镜像）——下轮开工先 checkout 全套+镜像重同步（清单同 §6m43）。
- 账面 852/860；全部提交已 push（→376e7909）。

## 6m46. 702 终态定谳：DK strike 序列 K1 起分歧+盲池离线重放图纸（2026-11-04 晚轮十一；收口）

- **[ACC]+bonus 字段终测**：DK strike 序列（按序号,忽略钟）——oracle pid0 K1=(acc−40,blind22) v gd K1=(0,20)；oracle pid1 K1=(−10,23) v gd (0,21)——**自 K1 起两侧 acc/blind 序列全面分歧**（blind 差达 8=整池），而 blind/lucky 事件流（type 109/101 全量）11.48 前逐位同。
- **逻辑终审**：盲状态=f(盲事件流)——事件全同+状态分歧 ⇒ **两侧 CoreBuff 盲池内部记账语义有差**（gainTemporary 的 MAX_STACKS 截断/resist/reflect 分支/TemporaryStacks 结构/超时处理器驱动方式之一）——表现为同刻 blind 数差（DK acc 随之差→acc roll 消耗差→rng 链位差→timeout 错 u→idx1118）。
- **下轮主攻（离线零成本）**：python 离线重放——提取 702 双侧盲事件流（全同），分别按 oracle Buff.gd:87-300 与 gd CoreBuff.gd:130-345 语义建模（重点：MAX_STACKS 截断、resistStacks/debuffReflectStacks 分支、temporaryStacks 的 farthest 清洗、超时 handler 的池遍历序、timer.start/stop 的 nextTemporaryTimeout 指针），逐步对账找首个状态分歧操作——该操作即修复点。**Light Goobert 5/8 红场——本修连锁预期最高。**
- 探针终还原清单（np29fT 全套）：oracle(Core/Character.gd,Items/Item.gd,Utility/Util.gd,Items/Exclusive/DragonKnight.gd,oracle_fight.gd)+gd_core(CoreRng.gd,CoreItem.gd,CoreCharacter.gd,CoreBuff.gd)+gd_core_items(Exclusive/DragonKnight.gd,Exclusive/ChessBoard.gd,Exclusive/Chess/ChessPiece.gd)+两镜像——**下轮开工先 git checkout 全套+cp 镜像重同步**。
- 账面 852/860；全部提交已 push（→5ad148cb）。offpeak #156 接力。

## 6m47. 盲池账数据完备+acc 快照语义澄清（2026-11-04 晚轮十二；交接）

- **oracle 池账全史已提取**（np29t_ora8 stdout）：side0 blind 的 [BGAIN]（10 池:to=3.767…13.85）/ [BCLEANSE]（7 次 farthest）/ [BEXPIRE]（242 行全量）——DK strike 时刻的盲数重构：@9.3167=22（expiry 前）→@9.8167=16（−7 ✓）→@10.1833=22（+7−1 ✓）→@10.7833=22→@11.15=15（10.85 expiry −7 后、+7 增益未计入？？）——**@11.15 的 15 vs 池账预期 22 = 6 层缺口=分歧操作所在窗**（10.85 的 expiry/gain 顺序或 MAX_STACKS 截断）。
- **acc 快照语义**：accuracy=updateItem 时的 getAccuracy() 快照（盲旧值）；[ACCO] 的 blind=print 时活值——两者可跨 expiry 窗（print acc=−5=快照时 blind 21、print blind=15=expiry 后）——**读 acc 差必须用快照时刻的盲值**。
- **下轮主攻（不变）**：python 离线重放盲事件流×双 CoreBuff 模型——10.85 窗的顺序（gain 先 v expiry 先：oracle tick ③物品激活 vs ⑦计时器）与 MAX_STACKS 截断值（grep MAX_STACKS 常数）为首要嫌疑——gd 侧 tick 序（CoreCombat.physicsTick ③物品→⑦计时器）与 oracle 2c（①钟②角色③物品…⑥⑦计时器）**同为物品先**——但 gd 的 Buff 计时器=_timer_active 自管（tickBuffs ⑦）而 oracle=注册表 Timer（⑥⑦ drive_timers）——**fire 的 tick 边界差=嫌疑核心**。
- 探针 np29fT 全套仍未还原（§6m46 清单）；账面 852/860；全部 push（→78610d6d）。

## 6m48. ★ 702 直接上游锁定：LG blind gain 间隔 tick 序列分歧（2026-11-04 晚轮十三）

- **钟无关终比（间隔 tick 数）**：side0 blind 7-池的相邻创建间隔（×60 tick）——oracle=[75,49,66,74,70,61,56,70,57,59,96,78,60,59]（pass1，进程钟连续段）；gd real=[64,68,46,72,77,79,49,83,56,64,75,49,66,74]——**模式完全不同，首间隔差 11 tick**。gd pass0≡pass2、pass1≡pass3（确定性 ✓）。
- **语义**：盲池创建=LG 的 blind 攻击（7 池/次）——间隔=LG cd 到点节奏。**LG cd 被 DK advanceCooldownPercent(15%) 推进**——advance 批次结构虽双侧同（§6m45），但**同帧内 advance 相对 LG 所在 tick 边界的应用位置**不同步→LG 第 2 次攻击时刻差 11 tick→盲池 to 序差→Crown farthest 清洗选择差→池构成差→timeout −7/−6→idx1118/1119。**FD@1118 直接上游=LG 攻击节奏差。**
- **修复方向（下轮直击）**：DK 的 advanceCooldownPercent 经 EventBus "activated" 派发（DK onItemActivated←connectForCombat(item,"activated")）——同帧内 LG activate()→事件派发→DK advance 的链路：oracle EventBus 派发序/时点 vs gd ctx.bus 的 connectEvent 派发——**重点对拍 advance 生效的 tick 边界**（oracle advance 在 LG 攻击同帧立即生效、gd 是否 defer 到帧末/下帧——或反之）。修=对齐 advance 的生效 tick。
- **方法资产**：钟无关比较=间隔 tick 序列（×60）——本轮所有跨钟假象的根治手段；[BGAIN] 池账 print（np29fT）双侧已验证可用。
- 探针 np29fT 全套仍未还原（§6m46 清单+DragonKnight.gd 两侧+镜像）。账面 852/860；全部 push（→0a5f2744）。

## 6m49. 702 再收敛：节奏差早于 DK 首.advance→speed/cd 推进速率嫌疑（2026-11-04 晚轮十四）

- **时间线精排**：首池 t ora=0.7667 v gd=0.8833（差 7 tick）；第 1→2 池间隔 ora=74 tick v gd=64 tick（差 10）——**分歧从开局即存在，早于 DK 首次 advance（gd 批首=2.400）→DK 假设（§6m44）排除**。
- **LG 首攻事件戳双侧同**（0.866667）而内钟 print 差 7 tick（ora 0.7667/gd 0.8833——各侧 print 钟与事件钟不同轴已二次确认）→**事件流无法反映 cd 到点的真实 tick**——「事件流全同」只保证逻辑分支一致，**不保证 cd 到点 tick 一致**。
- **新主嫌疑=speed/cd 推进速率**：LG 的 cd 到点节奏差→getSpeed()/speedScale 状态差（702 有 Gloves of Haste——giveSpeed 链）→**speed 不进事件流**→完全可静默分歧。次嫌疑=LG 首 cd 的 adjustCooldown 抽（已证锚后值序同——但 LG 具体取哪个抽未定位）。
- **下轮图纸**：①双侧打 LG getSpeed() 每帧针（env 门控）+首攻到点 tick 针→定 speed 差与首攻 tick 差 ②若 speed 同→对拍 LG 首 cd 值（prepare 时的 iterationCooldown——[ACD] 类针）③修→REG→860。**speed/cd 推进速率差候选=中晚簇全部 8 场的共同机制**（cd 驱动物品普遍）。
- 探针 np29fT 全套仍在树（清单 §6m46）；账面 852/860；全部 push（→31a34c66）。

## 6m50. ★★ 702 终版机制链闭合：heat−cold 差 1→LG speed→全部分歧（2026-11-04 晚轮十五）

- **[LGA] 双侧终测**：LG 前 4 攻 spd=0.9804 双侧同；**第 5 攻起分歧**（ora pid0=0.9804 恒 v gd=0.9615；第 6 攻 ora pid1=0.9091 v gd=0.8929）。getSpeed=getStackSpeedMods=(**heat−cold**)×0.02 的 1/(1−x) 分支——spd 差=**heat−cold 差 1**（gd=2 v ora=1）。
- **热事件流双侧全同**（type 107 全量：DK +6/+5、油灯 +2×2、衰减 −1 序列——逐位同）→**heat/cold 池状态差=池内部记账/衰减驱动差**（同盲池=同一 CoreBuff 类）——**Blind 池差与 Heat 池差同根**。
- **完整机制链（终版）**：CoreBuff 池语义/衰减驱动差 → heat−cold 差 1 → LG getSpeed 差 0.02 → LG cd 到点节奏差（首池 7 tick、间隔 10 tick）→ 盲池 to 序差 → Crown farthest 清洗选择差 → 盲层差 → DK acc 差 → acc roll 消耗差 → rng 链位差 → Blind timeout 取错 u → idx1118/1119。
- **下轮主攻（收敛后的唯一靶）**：CoreBuff 的 **heat 衰减驱动对照**——oracle=Heat buff 的 timer（drive_timers 注册表 ⑥⑦，Util.oracleTimeLeft 注册表语义）+ onTimeout 池重扫；gd=_tick 自管 timer（tickBuffs ⑦）——**fire 的 tick 边界/池遍历**。方法=离线重放 type=107 事件流×双模型（§6m46 方法，type 换 107——heat 事件少、重放快）。
- 探针 np29fT 全套（oracle 5 文件+gd 5 文件+DragonKnight/LightGoobert 两侧+镜像）**仍未还原**——下轮开工先全套 checkout+镜像重同步。
- 账面 852/860；全部 push（→6aef10c2）。

## 6m50 附言：Cheese Goobert heat +1 的投递 tick 差=最后一环（同轮终笔）

- getHeat/getCold 逐字同构；heat 事件流（含 +6/+2/+2/+5/−1/+1/−1 全量）双侧逐位同——**池的输入输出全同**。但 [LGA] 实测 spd 差（heat−cold 2 v 1）⇒ **读数时刻的池状态不同** ⇒ 唯一可能=**1.4667 的 +1（Cheese Goobert heat）在两侧的生效 tick 不同**（oracle 事件戳 1.466667=池即刻入账 v gd 的 +1 实际入账晚 1+ tick——或反之）——**bus 派发/池入账的 tick 边界差**。
- **下轮第一针**：双侧 gainTemporary(type=107) 的 [BGAIN] print t 值对比（+1 池的创建时刻差）——[BGAIN] 已有（np29t 两轮 log 在盘）——离线比对 type=107 的池账即可，零新跑。
- 机制链完整：+1 入账 tick 差 → heat−cold 差 1 → LG getSpeed 差 → cd 节奏差 → 盲池 to 序差 → Crown 选择差 → 盲层差 → DK acc 差 → rng 位差 → timeout 错 u → idx1118/1119。**+1 入账差的最上游=Cheese Goobert 的 heal/heat 链触发时刻**（Cheese Goobert=受击回heat?——its trigger 链的 tick 边界）。

## 6m51. heat 衰减调用点未定位（下轮首查）（2026-11-04 晚轮末）

- **heat 语义**：gainHeat=gainStacks(**永久池**,非 temporary——[BGAIN] 0 行的原因)；−1 衰减事件（t=0.35/1.4667/2.1833，used=False）的调用点**未定位**（loseHeat 全源=Item.gd:5111 item 层封装；Character 内部无 decay tick；GingerbreadMan 的 useHeat=used=True 事件非衰减）——衰减可能来自 **Item.gd 的 heat item 覆写**（某 heat 物品的 onTick/onCooldownEffect 调 loseHeat——如 Oil Lamp doCooldownEffect？或 RubyWhelp heat 的被动衰减在 **Character.gd _physics_process 之外**（Combat.gd tick 步骤②角色的 heat 衰减——oracle Core/Combat.gd 的 onTick）——**下轮首查=oracle Core/Combat.gd 全文 heat/107 引用+衰减物品定位**（t=0.35 的 −1 origin 为空名——origin=衰减物品！事件 origin 打印空=origin 结构非 dict（kind=item 但 name 缺？）——**用 raw json 查该事件 origin**即得衰减物品名。
- 下轮首查 2 分钟内可完成：python 读 run702 events.json i=70 的 origin 字段 → 衰减物品名 → 对拍其脚本两侧 → 修。
- 探针 np29fT 全套未还原（清单 §6m46+DragonKnight/LightGoobert 两侧）；账面 852/860；全部 push（→4c1addf4）。

## 6m52. ★★ 702 FD 根因链最终闭合：DK Amethyst removeRandomBuffs（2026-11-04 晚轮终）

- **heat −1 源定谳**：parent 链 i=67(DK 攻击 damage4)→i=69(102 −1)+i=70(**107 −1**)=**DK 双 Amethyst 宝石的 onAttack→removeRandomBuffs(buffRemoval=2)**——随机移除 2 个 buff（本例=Regeneration 1+Heat 1，双侧本例同选）。
- **FD@1118 完整根因链（终版）**：DK Amethyst 的 `removeRandomBuffs(2)` 随机移除→**候选池构成/选择序列双侧分歧**（某次移除：oracle 移了 heat 层、gd 移了别的——或反之）→heat−cold 差 1→LG getSpeed 差→LG cd 节奏差→盲池 to 序差→Crown farthest 清洗选择差→盲层差→DK acc 差→acc roll 消耗差→rng 链位差→Blind timeout 错 u→idx1118/1119。
- **下轮唯一靶（图纸终版）**：①读 removeRandomBuffs 实现（oracle Util/Core+gd 对应——随机选择的 rng 用法与候选池枚举序）②双侧打该函数针（候选池名表+选中名）→首个选择分歧点=池构成差的首证据 ③按差修（候选枚举序 or 移除规则）→REG（702+基线7+947+1441+1514）→860。**removeRandomBuffs 的随机枚举序（Array.shuffle? pick_random×n? 主链 roll?）是关键**——它在 trace 里的消耗面（roll 行）已证值序同→分歧在**候选集合**（池构成回环）——需先修池构成差的首环：**回环起点=最早一次「候选池构成差→选择差→池差」的自激**——离线重放 removeRandomBuffs 序列（双侧 trace 的 roll 值+当时池集合）可解。
- 探针 np29fT 全套未还原（清单 §6m46+DragonKnight/LightGoobert 两侧+镜像）；账面 852/860；全部 push（→e45d649d+本笔）。

## 6m53. ★ 702 核心不对称：oracle removeRandomBuffs(388 pick 行) v gd 0 行（2026-11-04 晚轮十六）

- **决定性计数**：oracle 702 rng_log 的 `pickRandomElement` 行=**388**（=DK 双 Amethyst 的 onAttack rollChance 命中后的 removeRandomBuffs→pickRandomStacks→pickRandomElement×2/次 + 其他调用面）；**gd trace 的 pickRandomElement 行=0、Gpick 行=0**——**gd 的 pickRandomStacks 在 702 全场从未执行**（gd_core/CoreRng.gd:141 pickRandomElement=randi_range 追踪版，若执行必留行）。
- **双侧 heat −1 事件都在**（i=70/71 同）→**两侧的 heat −1 走不同路径**：oracle=Amethyst onAttack(rollChance 命中)→removeRandomBuffs(2)（候选=opponent buffs，pickRandomElement 主链 2 抽/次）；gd=**未知路径**（候选：①Amethyst onAttack 的 rollChance 恒 false→removeRandomBuffs 不执行→−1 来自别处 ②gd 的 Amethyst.gd 行为差异）。**gd_core_items/Gems/Amethyst.gd 需逐行对拍 oracle**（onAttack 的 rollChance 条件/attach 的信号）。
- **语义后果**：oracle 的 removeRandomBuffs 移除「随机 2 buff」（可含 Heat/Regen 任意）——gd 若走另一路径（如确定性移除 heat）→池演化分歧起点=**第一场带 Amethyst+DK 的攻击命中**（t=0.35）——比盲池/Crown 更早！**FD@1118 首环=此处**。
- **下轮图纸**：①diff gd_core_items/Gems/Amethyst.gd v oracle（rollChance 条件/信号连接/buffRemoval 参数）②gd 侧给 Amethyst onAttack 打针（触发次/rollChance 值/removeRandomBuffs 入口）③对齐路径→REG（702+基线7+947+1441+1514）→860。**Amethyst 是 702 DK 宝石——1118 红场直接受益；其他红场的宝石构成待查**。
- 探针 np29fT 全套仍未还原（§6m46 清单+DragonKnight/LightGoobert）；账面 852/860；全部 push（→31a34c66/6aef10c2/…）。

## 6m53 附言（收口移交）：探测资产与本段结论索引

- **本段（offpeak #156+会话接力）702 挖掘资产**：双侧 traced log（np29r/np29t 系列：ora8/gd6 含 [BGAIN]/[BCLEANSE] 池账、gd13 含 [LGA] 攻击入口、ora3/gd5 含 [ACC]/[ACCO] acc+blind+bonus 快照）全部在 output/_offpeak/np29t_702/ 与 np29r_702/ ——离线可复分析，零新跑。
- **已定谳结论链**：①u 级首真分歧=DK acc roll（gd acc=5 消耗 v oracle acc=−5 短路，[ACC] 实证）②acc 差=盲层差（非 buff 分量）③盲层差=盲池 to 序/构成差 ④盲池 gain 间隔 tick 序列双侧分歧（首间隔 75 v 64，钟无关法）⑤**oracle removeRandomBuffs=388 pickRandomElement 主链行 v gd 0 行**（核心不对称——两侧 heat −1 路径不同）。
- **下轮第一动作**：diff gd_core_items/Gems/Amethyst.gd 的 rollChance 触发（gd rollChance 恒 false 嫌疑→removeRandomBuffs 从未执行→heat −1 另路）——**Amethyst csv_chance 数据面核对**（battle_items.json Amethyst 的 chance 字段 v oracle ItemData.csv chance 列）→缺则补→REG→860。
- 探针：np29fT 的 LightGoobert [LGA] 已随本笔还原；其余（FLP/RDA/ACC/ACCO/RDAO/BGAIN/BCLEANSE/DKA）已在前轮还原。树净、镜像同步。

## 6m54. ★★★ 702 FD 真根因终定：1 层 lucky 差（2026-11-04 晚轮十七）

- **决定性元组**（分歧 strike=DK rollDA r=0.428842 同链位双侧实证）：oracle [ACCO] pid=1 acc=0 lucky=1 blind=21 bonus=10 v gd real pass [ACC] pid=0 acc=5 lucky=0 blind=21（bonus=10 推算）——**blind 相同、唯一差=lucky 1 v 0**。acc 公式双验证：90+10+(1−21)×5=0（短路不抽 ✓）；90+10+(0−21)×5=−5（roll(−0.05)…wait acc=5 ⇒ lucky−blind=−19 ⇒ blind=19?——gd real pass 盲 19/21 两读数=strike 前后快照差，需下轮钉死；核心不变：**lucky 差 1→acc 差 5→roll 消耗差**）。
- **前轮修正**：①"gd removeRandomBuffs 未执行"=探针文本假象（gd trace 491/493=randi_range(0,2)/(0,3) 双侧同值同选 ✓ removeRandomBuffs 正常）②"盲池 gain 间隔分歧"=print 钟抖动假象（间隔和 930 v 922 仅漂移）③盲层差假设作废（blind 双侧 21 同）——**真根因=lucky 栈记账差 1 层**。
- **lucky 差的来源嫌疑（下轮图纸）**：①Cheese Goobert +1 lucky（t=5.7667）的 duration/过期语义（temporary lucky 过期 tick 差）②Lucky Cat 的 useStacks 消耗时机（lucky>0 闸的 tick 差）③Fedora +5 的池构成。**离线重放 lucky 事件流（type=101 全量）×双模型**——方法同 §6m46（事件流全同已验，状态差=模型差）。
- **连锁**：lucky→getBuffAccuracyMod→acc→命中 roll→攻击节奏——所有含 LuckyCat/Cheese Goobert/Fedora 的红场（8 红全含概率高）。
- 探针 np29fT 全套仍未还原（§6m46 清单）；账面 852/860；全部 push（→9a8f123f）。

## 6m55. 702 级联结构显形+矛盾点锁定（2026-11-04 晚轮十八；交接）

- **前轮修正**：gd removeRandomBuffs **有执行**（trace 491/493=randi_range(0,2)/(0,3)，值与 oracle 同——"0 行"=tag 文本匹配假象）；oracle 批 4 advance 的 srcs=4 个**不同** Twine（@9845/@9847/@9797/@9839，无重复投递）。
- **级联结构**：Light Goobert 激活 → 4 Twine（DK affected）各自 onTriggerItemActivated→rollChance(totalChance=base+Secondary数×chance2) → 成功者 activate()（type 0 事件）→ DK "activated"→advance。**DK 的 advance 批=Twine 级联成功数**。
- **矛盾点（下轮靶心）**：gd 批=3 advance v oracle 批=4，而 4 次 rollChance 的 flip 值 u 级全同（net 3860-3870 匹配）——同 roll 结果应同成功数！嫌疑：①oracle 的 Twine affectedSecondary 数≠gd（totalChance 不同→成功阈值不同——但 flip 值同、chance 不同→成功判定可不同！）②第 4 个 advance 的 src Twine 在 gd 该 tick 未激活（激活事件在别 tick——事件流匹配仅到 11.48，批内 tick 归属未逐一对齐）。
- **下轮图纸**：①双侧打 Twine.onTriggerItemActivated 针（totalChance/roll 结果/是否 activate）→ 同批 4 roll 的成败序列对照 ②核对 Twine 的 Secondary affected 数（getAffectedItems(Affected.Secondary)=isNeutral() 物品——两侧 neutral 集合差=totalChance 差=成功数差的直接机制）③修→REG→860。
- 探针 np29fT 全套仍在树（§6m46 清单+DragonKnight/LightGoobert/ChessBoard/ChessPiece）；账面 852/860；全部 push（→310e441b）。

## 6m55 附言（收口）：树状态与下轮开工清单

- **探针已全部还原**（FLP/RDA/ACC/ACCO/RDAO/DKA/LGA 零残留；oracle Buff.gd 的 [BGAIN]/[BCLEANSE]=原生诊断非探针）；镜像 md5 同步；工作树仅剩长期文件（README/docs/tools 12 项）。
- **下轮开工即可用资产**：双侧 traced log 全套在 output/_offpeak/np29t_702/（ora8 含 [BGAIN]/[BCLEANSE]/[BEXPIRE]/[ACCO] 池账+快照；gd6 含同款 gd 侧；gd13 含 [LGA]）——离线可复分析。
- **第一动作**：Twine 的 totalChance 对拍——getBaseChance()+getNumAffectedItems(Affected.Secondary)×getBaseChance2()：双侧打 Twine onTriggerItemActivated 针（totalChance/roll 值/activate 与否）→ 同批 4 roll 的成败序列对照 → Secondary 数差=修复点（isNeutral=classes==Neutral 数据面核对）。
- 账面 852/860；8 红：702@1118/921@452/977@497/986@206/1022@2456/1118@422/1120@868/1444@342。

## 6m56. ★★★ 702 翻绿（852→853）：FD@1118 真根因=玩家盲永久残差真值过期（np20 的 R=1 → 4）（2026-11-05 offpeak 接力）

- **§6m55 第一嫌疑定谳前先证伪**：①Twine totalChance 数据面零差异——离线按 ItemBook 语义（shop 列→classes 基值、gateItem 继承、fusedItem classes|=各 ingredient AND、class_override 尾覆盖）重导 oracle 全阵容 classes，与 gd battle_items.json 逐件全等（50 件 0 diff）；Twine Secondary 几何双侧同构（tscn tile3=collision/4=primary/6=secondary，secondary=同排左侧 3 格）。②事件流零成本对拍（output/oracle/fights vs align/gdcore，canonical id 归一）：**FD 前全流逐位同**，FD 批（parent=DK 激活 @11.35）Twine 成功 **3 v 3 全同**——「gd 批 3 v ora 批 4」（§6m55）系 id 空间未归一的假象。首分歧=**idx1118 LG Blind timeout amount -7(ora) v -6(gd) @t=11.4833**——§6m54 的 lucky/acc 差等全部为该分歧的下游噪声假设，本轮一并关闭。
- **决定性取证（双侧 traced）**：oracle 腿复跑（ORACLE_FIGHTS_ROOT scratch + ORACLE_RNG_TRACE=1，stdout 含原生 [BGAIN]/[BCLEANSE]/[BEXPIRE]）+ gd 腿（ORACLE_ALIGN_TRACE+STACKTRACE → rng_trace.txt [BLND] 池账 + 临时 BLNDX 探针打 gainTemporary/loseStacks 入口 current/perm）。gd 真实 pass 池账完全自洽：9.5667 的玩家 Crown 清洗因 perm=0 打中 FD 池（partial 7→6）→ 11.4833 到期 -6；oracle 语料同一清洗未打池（该池 -7 到期）⇒ **分歧=玩家侧盲永久层存量**。
- **离线求解（Buff 语义模拟器逐笔对拍语料）**：玩家侧盲残差 **R=4** 全中（31/31 笔到期额逐笔同；R=3 首失配 @24.867，R=2 @13.8，R=1 @11.483=FD 本身，R=0 @6.083；R≥4 在语料视野内不可分辨取最小值）；**对手侧 R=0** 全中（34 笔含 4 笔 -6 @6.867/9.033/12.833/20.6 全由 temp 清洗自然产生）——与录制机理互证（PLAYER 节点跨执行复用携残差、OPPONENT teardown free 零残差，oracle_fight.gd:563-590/:1004-1009）。
- **根因**：PERM_STACK_OVERRIDE 的 run702 {109:1}（np20-C 推导）引用面（-6@971/-6@1085/…）在现行语料中不存在（raw[971]=LG+7 gain、raw[1085]=DK 激活，非到期行）——系对旧管线流的推导残留；R=1 使 9.5667 清洗拆了 FD 临时批 → -6 v -7。np29f 系（§6m40-6m55 Twine/lucky/heat/盲池间隔）全部为其下游。
- **修复（2 文件纯数据面）**：gd_core_test/OracleAlignBattle.gd PERM_STACK_OVERRIDE run702 {109: 1→4}（+np30 重定谳表注）；tools/verify_oracle.py PY_PERM_STACK_OVERRIDE 同步 1→4。**REG**：np30_fix 门 702 双腿 PASS + 基线 7（570/1160/1029/862/813/635/732）+947+1441+1514 **双腿 10/10 ALL PASS 零退**。**860 刷账 852→853**；残 7 红：921@452/977@497/986@206/1022@2456/1118@422/1120@868/1444@342。
- **下轮提示**：①run1022_r18 的 {109:6} 同族同源（np20 同批推导）——其引用面同样值得用本轮求解器（语料到期额逐笔对拍）复验，图纸=把 simulate_full 求解器落成 tools 常驻脚本；②本轮取证资产：output/_np30_scratch/（oracle_stdout.log 含 BGAIN/BCLEANSE/BEXPIRE 全场池账、gd BLND/BLNDX、离线求解脚本 derive_oracle_classes.py+求解器内联）；③oracle 腿复跑在 ORACLE_RNG_TRACE=1 下与语料在 idx619 即歧（4630 v 3590 事件）——复跑≠语料（暖场/标签位差），**池账取证只能用「print 对照同跑自身事件」法，勿直接对语料**。
- 探针 BLNDX（gd CoreBuff.gd gainTemporary/loseStacks 入口 print）已全还原：gd_core/CoreBuff.gd、gd_core_test/gd_core/CoreBuff.gd、gd_core_py/gd_core/CoreBuff.py git checkout+md5 同步；误建的未跟踪 gd_core_test/CoreBuff.gd 已删除（gd_core_test 工程实际加载 res://gd_core/CoreBuff.gd）。账面 853/860。

## 6m57. ★★★ 921 翻绿（853→854）：无敌延长分支 base 语义——oracle 的 Util.changeTimer 是 harness 补丁版，np25 注释丢了 ≥0 判别（2026-11-05 offpeak 接力）

- **FD 结构（零新桩开局）**：921@452 双侧 idx451 前逐位同 → gd idx452/453 多弹两条 Frog Prince `invulnerable_end`（t=506，tgt1+tgt0）而 oracle 同位无（其 END 在 idx512/513=t598）。全语料 type7/8 配对扫描（860 场）→ **延长形（invulnerable 期间二次 makeInvulnerable）仅 10 例**：run1116×1、run1264×7、run921×2——run921 唯一「同拍 start+extend」形（King Goobert start(1.5) 与 Frog Prince extend(2.5) 同 tick，父链=King Goobert 激活→mana 消耗→Toad/Frog Prince 反应）。
- **gd 侧 live trace（常驻 INVU 双门控诊断，零新增探针）**：np34invu 门 gd 腿 rng_trace——fr=357 `make p1 dur=2.5 eng=2.466667 left=-0.033333`：延长分支基准读了**发火遗留值** −0.033333 → eng=f32(2.5−0.0333)=2.4667 → fire@fr506=FD 位（语料 506 ✓ 复现）。
- **oracle 侧 live trace（ORACLE_DEBUG=1+ORACLE_ONLY_CASES+ORACLE_FIGHTS_ROOT 单场复跑→scratch）**：`[bt-resync] t=6.1333 Player/Character/InvulnerabilityTimer eng=4.0000 old_e0=-1.0000 old_e1=1.5000`——changeTimer 的 base 走了 **fallback=引擎冻结读数 1.5**（oLeft=−1.0<0），非注册表遗留。
- **根因定谳**：oracle 的 `Util.changeTimer` 是 **harness 补丁版**（oracle/Utility/Util.gd:1680-1686）：`timeLeft=get_time_left(); oLeft=oracleTimeLeft(timer)（=U.oracleTimerLefts[timer][0] 即注册表 e[0]）; if oLeft>=0.0: timeLeft=oLeft; timer.start(t+timeLeft)`——decompiled 版（:1591-1593）无此补丁。**base=e[0] 仅当 ≥0；<0（停走遗留/同拍 start 尚未经 drive pass 登记）回落引擎冻结读数（=最后一次 start 写入值，引擎读数仅 start/stop 改写=计时器三定律①不变）**。np25 timeout1t 的「延长分支基准=_invul_left（e[0]）优先」注释丢掉了 ≥0 判别——run1069 定谳材料（f32 3.1 ULP 穿零）不覆盖延长形；全语料延长形 10 例中 8 例（1116/1264 链式延长）e[0]≥0 恒走 e[0] 基准（gd 旧码对该 8 例同行为=已绿，逐位复验 ✓），唯 run921 同拍形 oLeft<0 暴露缺口。
- **f64 穿零校验（fire@598 逐位命中机理）**：eng=f32(4.0)=4.0 精确；stepper 自 resync 拍起逐拍减 dt=1/60(f64)，240×dt=3.9999999999999996<4.0（差 1 ULP）→ 第 241 拍 left=−0.016667 穿零 → gd fire fr=357+241=**598**=语料 END@598 ✓（oracle 复跑 fire t=10.15−resync t=6.1333=241 拍同构）。
- **修复（1 文件×3 树，gd_core/CoreCharacter.gd）**：①makeInvulnerable 延长分支 `base=_invul_left（≥0）/ _invul_eng（<0 fallback）`——GDScript 3 无三元，两行 if 实现；②tickPhysicsTimers 补停走 else（`_invul_left=-1.0`，镜像 oracle_fight.gd:898-900 每拍刷新——覆盖「无前序发火周期的同拍形」的 rebuild-0.0 陷阱；对既有路径惰性：发火遗留/盲区同值重启立即 fire 的框架均不变）。cp 镜像 md5 同步（12d97ee4 ×2）+ gd_to_py 重生成 661 模块 rc=0（np34 标记 grep 2/2/2；CoreBuff.py 疑似改动=LF/CRLF 噪声，md5==HEAD 实证零内容差）。
- **REG（np34fix 门）**：run921_r18 + **run1116_r18 + run1264_r18**（延长面 8 例回归网）+ 基线 7（570/1160/1029_r2/862/813_r12/635_r12/732_r12）+947+1441+1514 **13 场 gd+py 双腿 ALL PASS 零退**；run921 双腿 795=795 逐位全同（三方一致）。门运行注意：基线 id 的 round 后缀以 np30_fix_gd summary 为准（r2/r12 变体，写 r18 会被夹具剔除→定向数对不上自检中止）。
- **860 刷账 853→854**（--compare-only 全量 55s）；残 6 红：977@497/986@206/1022@2456/1118@422/1120@868/1444@342。
- **下轮提示**：①同族嫌疑面 2 处**未动**（无语料实证不盲改）：(a) gd `_setRageTimer` 延长分支（_rage_active 时 `start(t+_rage_left)`，而 oracle startBattleRage=Timer.start 纯重启（decompiled/oracle 两份 Character.gd 逐字同）——rage「活跃中重启」形语料案例待找，建议全语料 ty21/22 配对扫描）；(b) gd CoreUtil.changeTimer（CritwoodStaff/Sandbag 用）——现实现已核对等价：停走 CoreTimer.get_time_left()=0.0=Godot stop() 归零（本地 3.6 实测 RUN=2.5/STOP=0/RESTART=1.5）≡oracle fallback 读数 ✓、运行中 _left=活余量 ≡e[0] ✓；4 个 changeTimer 调用面（Character invuln/Combat:924 animationTimer（表现，未建模）/CritwoodStaff/Sandbag）均无可达同拍 start+extend 形——若未来物品计时器出现该形需同款 fallback。②run1022 的 {109:6} 同族复验（§6m56 提示①）仍待做。③oracle 复跑≠语料再证（本例 resync t=6.1333 v 语料 5.9333，暖场漂移 ~12 tick）——**计时器机制取证有效、事件流逐位对拍无效**。④本轮取证资产：output/_np34_ora_scratch/（oracle 复跑 events+tick_states）、output/oracle/align/np34invu_gd/（gd INVU 全史）、output/_np34_scratch/（timertest Godot Timer 读数实测）。

## 6m58. ★ run986_r12 第一层翻进（FD 206→271）：激活窗重启分支基准——gd 新计时器初值 0.0 误当「注册表 ≥0」，oracle 实为未注册哨兵 −1→回落引擎读数（2026-11-05 offpeak）

- **FD 结构**：oracle idx206-209 四连 type=109 timeout（Burning Banner −1×2 p 池 + −1×2 o 池）@t=301（=战前 Lightsaber 8@6 + Banner 1@5×2 双侧同构 gain 后的 5s 池到期），gd 同位无→首个 109 TO @t=361（=6s 池到期，+60tick 整）；事件流 idx0-205 逐位同。渲染行 "5.02: [玩家] 1 致盲持续时间结束(燃烧旗帜)"。
- **决定性取证（零新桩，常驻 [BLND] 双门控）**：gd 腿 np36blnd（ORACLE_ALIGN_TRACE=1+STACKTRACE，tools/_np21_gate.py --cases run986_r12）rng_trace 行 308：`BLND p1 ty109 gain 6 len=1 ntp=0 tm=True/0/e6/s0 fr=0 (8@6)`——LS 先 gain（timer start(6)，e6）→ Banner gain 5 时 np35 重启分支基准读 `_timer_left=0.0`（GDScript 新建 var 初值）→ `5<0` 假→**不重启，nTT 停 0**→首火指向 6s 残池→+60tick。oracle 侧同窗：注册表此际=**未入册**（rebuild_timer_registry 在 activateItems **之后**，oracle_fight.gd:690/:968；战前 gain 时 Buff timer 未注册）→ `Util.oracleTimeLeft` 未命中返 **−1.0 哨兵**（Util.gd:810-813）→ np35 同款 `<0 回落引擎读数`（=6.0）→ `5<6` **重启**，nTT=size−1=1→(1@5) 先火。**语料自证重启**：idx206/207=BB −1×2 @301 先于 idx233/234=Lightsaber −1/−2 @361（不重启则 8@6 池先火、序颠倒）。
- **修复（1 文件×3 树，gd_core/CoreBuff.gd）**：`var _timer_left: float = - 1.0`（原 0.0）+np36 注——初值=oracle「未注册」哨兵语义；中途首 gain 形（eng=0.0 回落）恒等零影响；运行中（left≥0 优先）/发火遗留（<0 回落 eng=0）/停走（np26W1 每拍 −1）三路径全不变；rebuildTimerSeen 后 stopped=0.0 面与 oracle 入册 [0,0] 逐位同。cp 镜像 md5 同步（d94f0654 ×2）+ gd_to_py 重生成（np36 标记 grep 1/1/1；py 行 50 `self._timer_left = - 1.0`）。
- **REG（np36reg 门，16 场双腿）**：run921/1116/1264/1514/570/1160/1029_r2/862/813_r12/635_r12/732_r12/947_r10/1441_r11/977/702 **15 场 ALL PASS 零退**（含 921/977/702 防退+延长面 1116/1264）；run986_r12 双腿仍红但 FD **ev@206→ev@271**（gd 4214→4259，gd/py 双腿互相一致）。行为面论证：激活窗同 tick 多笔 gain 的 case 极稀（Banner 盲需 rollChance 命中且落在激活 tick），绿场不受影响——REG 实证。
- **第二层（@271，未闭环）**：修后 gd 暴露「停走后同值重启立即 fire 形」多一发：语料 p0 池 TO 序=301/301/361(−2 LS)/426(7.1)/550(9.1667)/692(11.0833)/712(11.5333)，gd=301/301/361/−1@**6.5333**（多）/…。机理：gd 361 火时池空（无 rearm→`_timer_seen` 停留 5.0）→6.5333 同 dur gain start(5) 后首 tick `eng==seen`→`_timer_left=−1−dt`→当拍 fire（np25 同值重启怪癖）；oracle 同形经 rerun [bt-resync]（`eng=5.0000 old_e0=-1.0000 old_e1=3.3667`，oracle_fight.gd:904-907）实证 e[1] 保**上次 rearm 的 delay**≠5→resync 不 fire。**池编排差**：gd 6.0-GA −1（GoldArmor cleanseRandomDebuffs，Item.gd:5517=pickRandomStacks 跨 debuff 类型随机摘+Buff.loseStacks 远到期优先）摘掉了 (1@9.15)→361 火后池空；语料 426/550 双火要求 (1@7.083) 与 (1@9.15) 同时活到 6.0167 后→语料 GA 的随机摘除**栈级落点与语料事件流（+N protected/−M 聚合行）不可互推**（离线求解器 output/_np36_scratch/solve_p0.py R=0..8 全败：farthest-first+perm-first 无解⇒随机摘除的池内选择不可从事件流重建）。闭环需录制器级池账（oracle 录制管线加 ORACLE_DEBUG 级 [BCLEANSE] 全量埋点重录本场）——超出本轮范围。
- **下轮图纸**：①oracle 录制管线加临时池账埋点（oracle/Core/Buff.gd [BGAIN]/[BCLEANSE]/[BEXPIRE] 已有——确认录制时 ORACLE_RNG_TRACE/DEBUG 是否带 stdout 落盘；无则补 env 门控重录 run986_r12 单场）→ 拿语料级每笔 gain/cleanse 的 (pick_to, pick_amt, n) 序列 → 对 gd np36fix 腿同位对拍 → 首个池编排分歧点=第二层根因（候选：随机摘除的类型键序 dict.keys() 插入序差 / ctx.time vs Util.time 相位差（激活窗 oracle=+1tick：rerun [BGAIN] t=0.016667 to=6.016667 v gd fr=0 to=6.0——序不变但 f32 火拍可差 1）/ 保护 roll 落栈差）；②若第二层闭环翻绿→860 刷账 855→856；③RL 门注意：p0/p1 池的 +1tick 时钟偏移两侧同构（opponent 物品相位在 combat_time++ 前），勿误当 gd bug 盲改。
- 探针零新增（全程只用常驻 [BLND]/INVU + ORACLE_DEBUG 原生打印）；工作树改动=gd_core/CoreBuff.gd + gd_core_test/gd_core/CoreBuff.gd（镜像 md5 同）+ gd_core_py/gd_core/CoreBuff.py（重生成）+ 本台账。取证资产：output/_np36_ora_scratch_stdout.log（oracle 单场复跑全池账，ORACLE_DEBUG=1）、output/oracle/align/np36blnd_gd/ np36blnd2_gd/（gd [BLND] 全史 pre/post-fix）、output/_np36_scratch/solve_p0.py（离线 R 求解器=§6m56 提示①「常驻化」的起点，含 f64 stepper 火拍模型）。账面 855/860 未变（run986 未翻绿，FD 推进 65 事件）。

## 6m59. ★★★ run1022_r18 翻绿（855→856）：PERM_STACK_OVERRIDE run1022 {109:6}→{109:1}——np20 同批过期推导第 2 笔定谳（§6m56 提示① 闭环）；附 oracle harness 火拍模型全标定（f64 时钟+f32 引擎量化）（2026-11-05 offpeak）

- **FD 结构（零新桩开局）**：run1022_r18@2456（oracle 4008 v gd 3915）——oracle idx2456=Skull Badge +1 致盲 gain、gd 同位=**多一发 Burning Banner 致盲 TO −1**（t=1118=18.6333，timeout=true）；idx0-2455 双侧逐位同。初判注意：FD 窗内 SB 的毒/盲轮换（type108 Poison v 109 Blind）两侧全 fight 逐位一致非分歧；Shelly −4/−2 清洗（idx2451/2452）两侧同在。
- **池账取证（gd 腿 BLND 全史，np37blnd 门）**：p0 池（=语料 target=0，holder=玩家 Character）fr=1118 序列=**先 `lose idx15`（清洗摘最远条目 (1@22.98)，perm 吃 3 余 1 落临时）→ 再 `fire idx0` 弹 (1@18.63)**=FD 事件逐位；而语料同窗 ct1118 **无 BB TO**、下一发 p0 TO=ct1119 LG(7@18.65)（idx2478）。⇒ 语料池在 ct1118 时 (1@18.63)（=BB@ct817/to=ct1118 条目）**已被更早清洗吃掉**。
- **决定性机理（oracle 单场复跑 ORACLE_DEBUG=1 → output/_np37_ora_scratch/，registry 全 trace）**：harness 火拍模型逐帧标定——①`U.time`/`to`/`delay`/注册表递减全 **f64**（Variant double；[BGAIN] t=24.9500 的 %.4f 打印铁证 f32 累积漂移不符）；②`start()` 后注册表 resync 值=`f32(get_time_left())`（引擎 real_t 量化——rearm delay 也过引擎，f32(1.0500000000002245)=1.04999995）；③resync 拍不递减、次拍起 `e[0] -= dt`（f64）至 ≤0 火；④fire 后 harness :923-925 **同拍立即** e[0]=e[1]=新 eng；⑤gain/cleanse 事件时间戳=combatTime（每场清零，phase ②③=combatTime++ 前 ⇒ 事件 ct=帧−battle_start−1）、fire 时间戳=帧−battle_start（⑥ 在 combatTime++ 后）——battle_start=1403 由 rerun 三锚点（BGAIN 1497↔ct93、fire 1734↔ct331、fire 1797↔ct394）解出。三笔 rearm 步数（63/39/17）在该模型下全中，f64-不量化与全 f32 两假设各错 1 笔——**标定=可复现实验**。
- **真值求解（sim1022v4，output/_np37_scratch/）**：用标定模型重放语料 p0 池 ledger（107 gain+17 cleanse+48 TO）扫初始永久残差 R：**R=1 全中 48/48（tick+amount+origin 三元组；0..15 唯一）**；R=0 LEN 47≠48；R≥2 超产错位单调恶化。**R=6（现 OVERRIDE）的首失配=#29=(ct1118,1,BB)=账面 FD 逐位**——因果链机器级闭环：R=6 时 ct898 Shelly −6 被 perm 全吸（≈R+SB增益−前清洗≈9≥6）→ BB(to=ct1118) 存活→ct1080 fire LG(7@17.98) 后 rearm 武装它→ct1118 火=FD；R=1 时 perm ct898 耗尽→最远优先吃 3 条（to=43.0167/42.9167/**42.0167=ct1118**）→rearm 武装 LG(7@18.65)→ct1119 火=语料。
- **根因**：np20-C 的 run1022 R=6 推导过期（与 np30 撤回的 run702 R=1 同批——「R=6 起全洁」系弹批对 R≥6 不敏感处的**最小可分辨值**而非真值）；§6m56 提示①「run1022 {109:6} 同族复验」本轮闭环。np30 的教训（推导引用面须对现行语料逐笔复验）第 2 次命中。
- **修复（2 文件纯数据面）**：gd_core_test/OracleAlignBattle.gd PERM_STACK_OVERRIDE run1022 {109: 6→1}（+np37 表注：推导+FD 机理）；tools/verify_oracle.py PY_PERM_STACK_OVERRIDE 同步 6→1（+np37 注）。**REG**：np37fix 门 run1022_r18 **gd+py 双腿 PASS 翻绿**；np37reg 门 15 场（921/1116/1264/1514/570/1160/1029_r2/862/813_r12/635_r12/732_r12/947_r10/1441_r11/977/702）**双腿 ALL PASS 零退**（含 921/977/702 防退+延长面 1116/1264）。**860 刷账 855→856**；残 4 红：986@206（deferred）/1118@422/1120@868/1444@342。
- **本轮工具事故与恢复（如实记）**：`--cases run1022_r18 --force` 把 oracle_align_cases.json 夹具覆盖成 1 场、后续 `--skip-godot --skip-py` 又触发 gen_fixtures 重建成 914 场（HEAD 夹具=860）——均以 `git checkout -- gd_core_test/oracle_align_cases.json` 还原后 `--compare-only` 重刷（860 口径 59.3s）。教训：定向跑批后**必须核对夹具未被改写**再刷账。
- **提交附带（透明记账）**：工作树 verify_oracle.py/OracleAlignBattle.gd 尚含 np35 轮未提交的 py 镜像行（run977 {109:18}）与 np21 期 CASES 定向下发修——系当前**已验证状态**的组成部分（np37reg 的 run977 双腿 PASS 依赖该行），随本笔一并入库避免丢失；gd_core/gd_core_items/gd_core_py/gd_core_test/gd_core 引擎四树本轮**零改动零探针**（全程只用常驻 BLND/INVU + ORACLE_DEBUG 原生打印）。
- **下轮提示**：①sim1022v4 = 「常驻化」完成的离线池求解器（np30 的 run702/np35 的 run977/本笔 run1022 同一器可解），残红 4 场优先复用：**run1444@342**（Cold 池 TO amount −3 v −1——其 OVERRIDE {100:129,102:4,103:10,106:83,107:4,110:1} 多维真值值得同款逐维重推）、**run1120@868**（盲池 TO 序 LG/BB 颠倒——同族池编排差）、**run1118@422**（同位事件落点 tick 差=冷却/速度掷点分叉，非池族）、run986@206 第二层（§6m58 随机摘除不可重建面仍需录制器级池账）。②oracle 单场复跑+ORACLE_DEBUG 的 registry trace（[bt-resync]/[timer-fire]/[BGAIN to=]）+事件时间戳双钟映射 = 池账取证通用图纸；注意复跑≠语料（暖场/残差态差），**只用复跑标定机理、真值对拍永远用语料 ledger**。③121444 类「visible 清洗恒发事件」语义（loseStacks 全额被 perm 吸收也弹 −N 行）=事件流完整性的关键前提，求解器依赖它；勿在 gd 镜像里「优化」掉。


## 6m60. ★ run1118_r18 翻绿（856→857）：rebuild_timer_registry 的物品计时器补锚——np25 timeout1t 的 CoreTimer 漏网面（§6l2 tick1diff 簇第 2 笔同族定谳）（2026-11-05 offpeak）

- **FD 结构（零新桩开局）**：run1118_r18@422——oracle idx422=玩家 Holy Spear 攻击（ty100 remove_block −40）t=4.1000，gd 同位事件**逐位同但 t=4.0833（早 1 tick）**；idx0-421 双侧逐位同。§6m59 下轮提示①预判命中（「冷却/速度掷点分叉，非池族」）。
- **双侧 SPDT 单场 traced（output/_np38_scratch/{ora,gd}_1118_stdout.log）**：①oracle 批日志含 3 战（暖场 Win+语料 Loss+确定性复跑），**语料条件=第 2 战**（[spdt] seg1：复跑 events.json 与冻结语料逐字节同=确定性自证）；②PLR spear tt 流 3.30→4.1 窗两侧 dtt 逐帧同形（spd 2.36→2.38@3.7833→2.40@3.8 同拍变更），但 gd 的 tt 全窗恒少 0.016667——注入点=row181 t=3.0333：**invu 结束（语料 ty8@3.0167 两侧同帧）后的 reduce_speed 生效拍，oracle 3.0333 帧递减已用新速 2.36，gd 3.0333 仍用 3.36、3.05 才切**——gd 的 spear buffTimer（buffEnded→reduceSpeed）晚火 1 帧。
- **计时器火拍双桩对拍（GD_TMR/[tstart][tfire] v ORACLE_DEBUG/[timer-fire][timer-fire-dbg]）**：gd `[tfire] BuffTimer wt=3.0 t=3.033333`（Holy Spear，ctx.time=combatTime 同帧口径），oracle `Player/Character/InvulnerabilityTimer` 与 `Player/Holy Spear/BuffTimer` **同一 registry pass 火**（[timer-fire] 相邻行同 U.time）→ buffEnded 当帧→下一帧冷却递减用新速。f64 数值实验（wt=3 登记拍不递减语义）复演 oracle [timer-fire-dbg] e0=−0.016667 逐位——模型闭环。
- **决定性机理**：oracle harness `rebuild_timer_registry`（oracle_fight.gd:969-987，np36 注已证 rebuild 在 activateItems 后）把 Main 树**全部** Timer 以 [left,left]=[eng,eng] 重入册 → **开局 setup 期（激活窗内）start 的计时器战斗首拍即递减**（首拍 eng==e[1] 走递减分支）；gd np25 timeout1t 的等价锚 `rebuildTimerSeen`（CoreCombat.gd:258-259）只锚角色影子链（rage/invul/Buff 栈），**物品 CoreTimer 漏网**——_seen 恒 0 → 首拍被 eng!=_seen 判「外部 start」只登记不递减 → 一切激活期 start 的物品计时器恒晚 1 拍。**反面控制组**：战中断 start 的 Crown BuffTimer（wt=2@3.0167→语料 ty8@5.0333）双侧全对（rebuild 后的 start 走 eng!=_seen 当拍登记，同构）——只有 setup-start 型错。wt=3 需 181 次递减才穿零（f64 累积 +5.65e-15>0），1 拍延迟恰好把 spear 减速拍与 4.0833 火点同时推后——§6l2 教训重演（量纲先行：本题差值恰=dt×Δspd，非 f32 量化）。
- **修复（3 文件纯引擎面，126 行含注）**：gd_core/CoreTimer.gd +rebuildSeen()（_left=_eng; _seen=_eng=rebuild 登记 [left,left] 等价）；gd_core/CoreItem.gd +rebuildTimerSeen()（timers+gems 递归=场景树 DFS 同构）；gd_core/CoreCombat.gd activateItems 末尾（player/opponent.rebuildTimerSeen 同点）逐参战物品委托。镜像 gd_core_test/gd_core ×3（md5 同）+ gd_to_py 重生成（grep：CoreTimer.py:241/CoreItem.py:846/CoreCombat.py:297）。
- **REG**：np38fix 门 run1118_r18 **gd+py 双腿 PASS 翻绿**（760 事件全同）；np38reg 门 16 场双腿 ALL PASS 零退（921/1116/1264/1514/570/1160/1029_r2/862/813_r12/635_r12/732_r12/947_r10/1441_r11/977/702/1022）；np38red 门 986_r12/1120_r18/1444_r18 FD 位置不变（271/868/342=各自原位，池族另根）。**860 全量刷账**：夹具先被 gen_fixtures 重建为 914（fights/ 在 np37 后新增 ~54 录制场——本会话第 2 次踩 §6m59 事故面，git checkout 还原 860 后 --compare-only 重刷 62.2s）；**860 口径 857/860 逐行一致（856→857）**，账面残 3 红 986@271/1120@868/1444@342；914 里的另 25 红全部不在 HEAD-860 账面（新录制场，含 rng-mechanism 已知族，留待语料扩容后另立项）。
- **下轮提示**：①986@271 层二（§6m58「停走后同值重启立即 fire 形」）与 1120@868/1444@342（池族）仍按 §6m59 提示① 路线（sim1022v4 求解器+录制器级池账）；②本轮修复后**激活期 start 的物品计时器全部提前 1 拍**——凡「同位事件落点 tick 差」类新红场优先怀疑此族残余（[tfire]/[timer-fire] 双桩直接定谳，成本 ~2h）；③新录制 54 场未入账面，入账前须先过 gen_fixture 预检（events 非空）与排除族归类（run906_r18=gd_core_py-transpiler 转写已知）。

## 6m61. ★ workflow 收口移交 offpeak（2026-11-05 13:54；按用户指令 13:50 收口停止写台账）

- **workflow（dwfrun 系列）战果**：R1 702@1118 翻绿（盲永久残差真值 R=4，4ba4a104）→ R2 921@452 翻绿（makeInvulnerable 延长分支 fallback+停走 else，99eb6f14）→ R3' 977@497 翻绿（CoreBuff 重启分支基准=注册表 e[0] 优先+<0 回落 _timer_eng，e5a6ba4d）→ R4' 1118@422 翻绿（rebuild_timer_registry 物品计时器补锚，b97345a7/§6m60）——**账面 852→857/860，本段 +5 场**。
- **移交时账面**：857/860，残红 3=run986_r12@206、run1120_r18@868、run1444_r18@342。
- **工作树状态**：引擎四树（gd_core/gd_core_items/gd_core_py/gd_core_test）零探针零 WIP ✓（R4 重跑攻关员在定位阶段被停，无文件残留）；tools/docs 的 M=并行会话沉积与本段台账改动。
- **未 push 事项**：本地 commit 至 b97345a7+本移交节 commit——**offpeak 开工先 git push（含前序全部本地 commit）**。
- **offpeak 铁律（重申）**：修复完所有问题（860 全绿+收口链）前不可主动退出。
- **下轮图纸（残红 3）**：①第一嫌疑=Buff 计时器族（已三连翻绿：盲残差真值 R 标定/invul 延长分支 fallback/CoreTimer rebuildSeen 补锚——986@271 与 1120@868 的首分歧读台账 §6m59 前后）②§6m55 Twine totalChance 对拍备用 ③REG=基线7+本井+702/921/977/1022/1118 防退 ④860 全绿后收口链（compare-only→P4→README→commit→**push 含前序**→54 超长场）。
- **workflow 教训（资产）**：①Amend 改任务书文本会使全缓存 miss（攻关员-RN 全重跑）——改任务书措辞前先想清楚 ②跑长循环的 workflow 到硬时限时用 Amend 收口（本轮即此模式）③探针 print 与 trace tag 匹配要用内容子串（tag 名双侧不同构）。

## 6m62. 残红 3 场 FD 结构定谳+池账对拍方法论落地（2026-11-05 offpeak）

- **池账对拍基建建成**：oracle 录制管线的 [BGAIN]/[BCLEANSE]/[BEXPIRE] 原生打印已验证可提取（np36 scratch log）；gd 侧同款 print 已入 gd_core/CoreBuff.gd（np42 temp，已还原）并跑通 run986 单场（np42_gd3 log 314 BEXPIRE）。**战斗时间归一**：oracle 进程钟−战起点（LS 8@6 gain 时刻，986 战 2=59.0333）=gd ctx.time——验证过 5 笔 cleanse/4 笔 expire 的 pick_to/to 逐一对齐。
- **np36 修正**：§6m58 的「gd 多一发@6.5333」在 np36 修复后**已消失**（BEXPIRE 序列 5.0167×2/6.0167 amt=2/6.5333 amt=1 双侧逐位同；5 笔 cleanse 同池同量）——盲池账在 FD 窗已对齐，986 的残红在**更上游或别类型池**。
- **残红 3 场 FD 结构（当前 alignment.json 实测）**：
  - **986@271**：ora idx271=False Life Health+10 v gd 同位=Burning Banner Blind TO −1——gd 多一发盲 TO（Banner 池）在 oracle 无此火的时刻。np36 后盲池账对齐 ⇒ 分歧池=**战内 t≈300+ 的后段池**（np36 scratch log 只覆盖战内 0-118，后段需重录）。
  - **1120@868**：ora=Light Goobert Blind TO **−11**（单事件 11 层合并池）v gd=Burning Banner TO −1——**池合并粒度差**（oracle 单池 11 层同 to；gd 拆小池各自到期）——LG 盲 gain 的 dur/入池路径对拍是靶。
  - **1444@342**：Frostbolt Cold TO **−3 v −1**——Cold 池到期时余量差 2 层（事件流同→池内构成/清洗落点差）。
- **下轮图纸**：①1120 最锋利——LG 盲 gain 的 amount/dur 序列双侧对拍（events 的 +N gain 事件已全同→入池 dur 或合并行为差）——查 LightGoobert.gd 的 blind 施加（gainTemporary amount/dur）与 gd 同位；②986 需重录 oracle 全战池账（np36 scratch 覆盖不足，重跑 ORACLE_DEBUG 单场到战终）；③1444 对拍 Cold 池的 cleanse 落点（spell scroll frostbolt 的 cold 施加+FA 清洗）。
- 探针 np42（gd CoreBuff BGAIN/BCLEANSE/BEXPIRE）**已还原**；账面 857/860；全部 push（→8307625b）。

## 6m63. ★ run1120_r18 翻绿（857→858）：绝对钟 T0 预载键控——Buff 池 to 尘埃序的录制批不可复现面（2026-11-05 offpeak #372）

- **1120@868 定谳（修正 §6m62 的「池合并粒度差」误判）**：FD 实为**同刻双池超时的火序差**——t=14.6667 双侧都有 LG Blind TO −11（9.10 gain 池）与 Banner TO −1（5.40 gain 池），金额全同，只差顺序：ora 先 LG 后 Banner，gd 反序。§6m62 的「−11 单池合并 v −1」系 FD 窗只读半边的假象。
- **机理**：池 to=Util.time+dur（f64）；两池数学同 to（5.40+9.25 = 9.10+5.55 = 14.65），f64 尘埃决定 onTimeout 重扫严格 `<` 的并列序。gd ctx.time 从 0 起累（T0=0）⇒ B2.to<P_B.to⇒Banner 先；语料录制批的 Util.time **跨场不清零**（Util.gd:148-152，[M7] 暖场整场 tick 预累积）⇒ T0=acc(K) 改变尘埃序 ⇒ LG 先。全战扫描 k∈[0,3M]：LG-first 窗占 61%；**K=2553（暖场=自身同 seed 整场，chunk=1 假说）⇒ P_B.to−B2.to=−2.13e-13（LG 先）=语料 ✓**。全战唯一尘埃对撞即此一处（跨 dur 对撞枚举：LG 5.55×Banner 9.25 tick 差 222 仅此一对）；f32 定时器 ULP≈1e-7≫尘埃 1e-13 ⇒ 火 tick 窗内不漂。
- **修（键控表 WARMUP_TIME_TICKS，gd_core_test/OracleAlignBattle.gd）**：开战前 ctx.time 逐次 += PHYSICS_DELTA 共 K 次（与神谕 Util.time 同一左结合 f64 链逐位同构）；py 腿镜像 PY_WARMUP_TIME_TICKS→simulator/gd_core_engine.py warmup_time_ticks（run() 开战前预载）。验证：单场 verify --cases **三方一致**（3466/3466）；REG np43t0 11 场 gd+py 双腿 ALL PASS；860 全量刷账 **858/860**（残红 986/1444）。
- **坑位加固**：verify --cases 改写夹具事故第 3 次踩（986 单场验证后未还原→后续 REG 的 gd 腿只见 1 场「定向 → 1 场」→expect 检查 rc=1）——git checkout 还原后 REG 恢复；铁律 11 再确认。
- **986@271 部分推进+受阻（FD 271→287）**：FD 实为 **gd 多一发幻影 TO**——6.4833 清洗（Chili Pepper −1，type 109=Blind）清空盲池→stop 后，6.5167 同 dur(5) gain 走 np26W1 碰撞支（eng==seen=5、left=−1 续减）→当拍 fire 吃掉新池；语料无此火（H 池满 5s 于 11.5333 到期=idx494）。修（键控表 BUFF_STOP_CLEARS_SEEN→ctx.keyed_stop_clears_seen，CoreBuff._stopTimer 清 _timer_seen 使下次 start 恒走重同步支）后 FD 271→287，gd≡py 双腿同位。REG np43scs 12 场：11 PASS 双腿、986 RED@287 零退步。
- **986 残余阻塞点（已排除分支全录）**：新 FD=ora 在 7.1 有一发盲 TO（D 池 1@7.0833 自然到期）⇒ **oracle 的 4.1 Gold Armor −4 未打 D 池**（gd 打了 E+D+A(2)）。约束解算：语料盲 TO 全序列（B/C@5.0167、A −2@6.0167、D@7.1、F@9.1667、G@11.0833、H@11.5333 全自然到期，唯 E 被清）与现行 oracle/Core/Buff.gd farthest-first 语义**余额守恒不可同时成立**（gains 15 = TOs 8 + 清洗落地 10 → 超支 3；静态 perm 残留 R∈{0,1,2,6} 全部与 A −2@6.0167 矛盾）。furthermore 单场重跑（现行 harness）在 2.0333 清洗即与语料分叉（amt 3 v 4）且呈现病态同拍 fire 循环——**录制批（10-31 12:03-12:34，np25-p1 后）的池语义/注册表态存在不可复原差**，远端重建失败。绕行 1444；回修入口=①PERM_STACK_HARVEST 收割面重审（np22 三场先例）②录制批 chunk/T0 结构考古 ③986 专用键控池账补偿（下策）。
- 探针资产：tools/_np43_1120.py（oracle 单场 [B*] 提取）、tools/_np43_gdsingle.py（gd 单场 BLND trace，scratch OUT 并行安全）；output/_offpeak/np43_1120/、np43_986/。引擎树改动=CoreContext.gd（keyed_stop_clears_seen 字段）+CoreBuff.gd（_stopTimer 键控清 seen）×2 树镜像+py 重生成 grep 验证；OracleAlignBattle.gd 双表+WARMUP/BUFF 键控；verify_oracle.py+gd_core_engine.py py 侧镜像。

## 6m64. 残红 2 场（986/1444）同根定谳：三执行链收割拓扑缺中间层（2026-11-05 offpeak #372 续）

- **860 刷账终态：858/860**（986@287+1444@342，本段净 +1；986 键控 seen-clear 已含入账零退）。
- **1444@342 解剖**：FD=6.35 Frostbolt Cold TO −3 v −1（首 Frostbolt 池 +3@3.3167 dur3 到期时余量差 2 层）。约束：4.5 Gold Armor −5（无 protect，落地 5）后语料要求 P1=3@6.35、P2=3@6.5 ⇒ 清洗落点=perm−4+P2−1（farthest-first 下 P2(4 层,to 6.5) 是最晚池必先吃 4 层 ⇒ 语义不可达，与 986 同型）。全战 Cold 账：temp 6 池 13 层、TO 仅 3 笔（−3/−3/−1）、dance ±1 无 dur（perm 域，净 0）。
- **统一根因假设（两场汇合）**：np22 注已言明「新语料（10-31 重录）=**exec3** 携带 exec2 终局残差」，而现行 PERM_STACK_HARVEST/R5 管线只做 **exec1 单层收割**（暖场干净终局）——三执行链的中间层残差（exec2 带着 exec1 残差跑出的净化路径→自身终局残差）缺位，{110:1}/{109:18} 等静态 OVERRIDE 只是该缺位的净值近似。986 的盲池清洗落点差同属此族：录制批 exec3 开局的 Buff 态（perm 及可能的注册表残留）不可由单层收割复原。
- **下轮图纸（按序）**：①**收割链扩展**——PERM_STACK_HARVEST/R5 管线加深到 exec2：warm1（干净）→收割 h1→warm2（初态=h1，R5 嫁接语义）→收割 h2→正式场（初态=h2）；oracle 侧机理=录制批每 case 的暖场+正式同进程连续三执行（ Buff.reset 只在 case 装配段跑，exec 链内无 reset——**需先验证 oracle_fight.gd 的 case 内多执行结构**，fights/<case>/result.txt+np22 证据包）。②986/1444 逐笔对拍验证 h2 终局值（np37 离线模拟器法，PERM_OVERRIDE 现值 {109:?}/{110:1} 应与 h2 自然吻合——若吻合则键控表可全撤）。③若收割链仍不闭合，再评估 986 专用键控池账补偿（下策，台账 §6m63 阻塞点）。
- 关键文件：PERM_STACK_HARVEST/R5_DUAL_EXEC（OracleAlignBattle.gd 文件头注+注入段）、PY_PERM_STACK_OVERRIDE（verify_oracle.py:90）、simulator/gd_core_engine.py r5 双执行段；1444 语料约束=idx 141/281 两笔 Gold Armor 落地 4/5 + TO 342/347/…（−3@6.35/−3@6.5）。

## 6m65. 1444 补充约束：OVERRIDE 现值有效性确认+R 拟合矩阵（2026-11-05 offpeak #372 续2）

- **{110:1} 现值有效性实验**：ORACLE_ALIGN_NO_PERM_HARVEST=1 单场复跑 → FD 342→**330 前移**（gd 多一发 Frostbolt Cold TO −2@5.9833 Snowmaster 段）⇒ np22 的 {110:1} 对现行语料仍有效（330-341 被它救回），残差 342+ 另有自由度。
- **R 拟合矩阵（gd 侧 trace 推演）**：R=1（现值）→4.5 清洗 perm1+P2−4（P2 整池删除）✗；R=9 → 4.5 perm4+P2−1 完美（P1=3/P2=3 ✓✓）但 291@4.9167 dance −1 落 P2→2 ✗；R=10 → 291 吃 P2 得 3 ✓ 但 319@5.8833 再吃 P2→2 ✗ 且 P2 应火 −4 ✗。**结论：static R 无解——dance −1 的损耗目标规则本身是缺失自由度**（现码=farthest-first；语料要求某几笔 −1 落 perm、某几笔落 temp 的精确交错）。
- **下轮主攻（替代 §6m64 图纸①的先行步）**：np37 法离线模拟器（sim1444v1）：喂全战 type-110 tgt=0 事件序（temp 6 池 13 层+dance ±1+两笔 Gold Armor+TO 3 笔），双自由度 (R, dance-loss-rule∈{farthest,earliest,newest,perm-first-else-X}) 逐笔对拍 TO 序（−3@6.35/−3@6.5/−1@9）+330 前的 Snowmaster 段；**若 (R,rule) 唯一解 → 986 同法（dance-rule=清洗落点差的更一般表述）**；若仍不闭合 → 回收割链扩展（§6m64 图纸①）。
- 语料事实补充：1444 两笔 Gold Armor（2.2667 −4 / 4.5 −5）tgt=0 均无 protect 前置事件（落地=全额）；dance 序列 tgt=0 ±1 共 ~30 笔（resisted +1 不入账）；perm gains 30/losses 34 含清洗。

## 6m66. ★ run1444_r18 翻绿（858→859）：{110:1}→{110:6} 重标定+清洗落池规则破案（biggest-first，986 完美拟合但跨侧矛盾回退）（2026-11-05 offpeak #372 续3）

- **1444 翻绿**：np37 法离线模拟器（output/_offpeak/np43_1120/sim1444v1.py+cold1444_ledger.txt）R 扫描 → **{110:6}**（现值 {110:1} 系 np22 旧标定）单场 verify **三方一致**；REG np44reg 13 场 gd+py 双腿 12 PASS（986 已知残差）零退。PY_PERM_STACK_OVERRIDE 同步 110:6。
- **清洗落池规则破案（np44 线索，未落地）**：986 盲账（blind986_ledger.txt，含此前漏抽的 GP 永久 gain 行 2.0333 +1/4.1 +1/6.0 +2——Gold Armor 清洗同拍补充，余额悖论前提崩塌）**biggest-first+R=0 零失配**（oldest 同）；1444 biggest+R=6=farthest+R=6（残 1 笔@t=9 系模拟器简化伪差，引擎实测全过）。**引擎试落（CoreBuff loseStacks farthest→biggest+镜像+py 重生成）：1444 保持绿 ✓ 但 986 tgt=1 侧前移破到 FD@233**（本求解只做了 tgt=0）→ 已回退（git checkout+镜像+py 重生成，verify 确认 986 回 287/1444 保持绿）。
- **986 下轮精确入口**：biggest-first 在 tgt=0 完美、tgt=1 破 → **双侧联合拟合**（tgt=1 盲账同法提取→(R_player, R_opp, rule) 三自由度；PERM_OVERRIDE 注入面=玩家侧 p.buffs，对手侧残差载体需查 harvest 链/R5 语义）→ 若闭合则引擎 biggest-first+双侧 R 全落地；若跨侧仍矛盾 → 录制批侧侧间差另查。bonus：986 的 BUFF_STOP_CLEARS_SEEN 键控在 biggest 落地后可能可撤（重验）。
- 坑位复训：verify --cases 改写夹具（本段 2 次还原）；单场 harness「PASS」行不可信（scratch 模式比对缺失），手工 canonical diff 为准。
- 引擎树终态：CoreBuff.gd=farthest 原样（np44 注释未留，回退干净）；OracleAlignBattle.gd PERM_STACK_OVERRIDE {110:6}；verify_oracle.py PY 表 {110:6}。

## 6m67. 859/860 终态锁定+986 R 扫描鬼影警示（2026-11-05 offpeak #372 收口）

- **859/860 确认**（sweep860_np44.log：三方一致 859，oracle≠gdcore 1=run986_r12@287）：本段净 **+2**（1120 T0 预载键控、1444 {110:6} 重标定）。
- **986 R 扫描鬼影（重要教训）**：biggest-first 无条件落地+{109:R}（R=0..5）临时行时单场 verify 六连「PASS」（firstDivergence=null），但该态**不可复现**——回退后同条件（forced unconditional+{109:0}+无 harvest）gd 腿 FD@233（tgt=1 Lightsaber TO v Gold Armor protect）。疑点=当时 py 镜像/夹具态与时序差异，**单场 json 的 PASS 判读必须配 verify 原始输出与手工 canonical diff 双验**（本段已双验确认当前真态）。引擎已回退 committed farthest（gd_core/CoreBuff.gd 零 biggest 残留，py grep=0），1444 保持绿。
- **当前工作树增量（全部惰性/已验证）**：CoreContext.gd+CoreBuff.py 的 keyed_cleanse_biggest_first 字段（引擎已回退不读，py 字段惰性）；harness CLEANSE_BIGGEST_FIRST {986}+say 线（引擎不读）；PERM_OVERRIDE {109:0} 双表（净零注入）；gd_core_engine.py keyed 参数（惰性）。功能态=859 sweep 逐位同。
- **986 下轮入口（更新）**：①biggest-first 对 tgt=0 的完美拟合依然成立（模拟器层），但 tgt=1=碰撞立即火主导（np26W1 域），纸面模拟不适定——**引擎级迭代**：biggest-first 落地后 tgt=1 破@233（ora Lightsaber TO −1@6.0167 v gd Gold Armor protect@6.0667——gd 的 tgt=1 池被 biggest 多吃）→ 需 tgt=1 的对手侧残差载体（PERM_OVERRIDE 注入面=玩家侧 p.buffs，对手侧=free 重建无残差 ⇒ **tgt=1 破法=对手侧盲池在 biggest 下的初始态差** → 查 R5/暖场对手侧语义）②或 986 专用双序键控（tgt=0 biggest/tgt=1 farthest——需 ctx 按侧分旗，机理若成立则记录批两序并存的物理根源）。③鬼影复现实验：精确重建 R 扫描态（无条件 biggest+临时行）并以原始输出+手工 diff 双验。

## 6m68. 986 鬼影定谳：R 扫描六连 PASS=Parse Error 空判（2026-11-05 offpeak #372 收口2）

- **根因**：R 扫描的首个 biggest-first 补丁的 replace 链只改了 _blnd_snap 两处实参，**漏改 `temporaryStacks.remove(farthestIndex)`** → GDScript Parse Error（「farthestIndex isn't declared」）→ gd 腿零事件产物 → verify 的 compare 对空流判 firstDivergence=null → 单场 json 假 PASS。第二个补丁（修好 remove 行）后的引擎实测=真 FD@233（tgt=1）。**验证纪律追加：单场 json PASS 判读必须先核 gd 产物 events.json 非空+verify 原始 tail 无 SCRIPT ERROR**（本段第 3 次工具链坑位，与 np29 探针自炸/夹具改写同列入册）。
- **986 真态不变**：859/860，FD@287（farthest 基线）。biggest-first 的唯一真实引擎实测=tgt=1 破@233（§6m67 入口①不变）。

## 6m69. 986 biggest+R=1 引擎实测不迁移+稳态回退确认（2026-11-05 offpeak #372 收口3）

- **实验**：键控 biggest-first（parse-safe 全三处替换，py grep=0 残留）+ {109:1} 双表 → 986 单场仍 **FD@233**（与无 override 的 biggest 实测同位）——tgt=1 早期窗模拟器拟合（biggest+R=1 零失配）**不迁移引擎**：tgt=1=碰撞立即火主导域（np26W1），纸面池账模拟不适定（fire 时刻/池识别由 f32 计时器+碰撞支决定，非纯池量）。模拟器方法论边界入册：**碰撞域侧只能引擎级迭代**。
- **稳态回退确认**：引擎/表全回 committed（grep=0），三井复验 1120 PASS+1444 PASS+986 FD@287 = 859/860 账面（sweep860_np44.log 已证）。
- **本段（offpeak #372）总结**：857→**859**（1120 T0 预载键控 §6m63、1444 {110:6} 重标定 §6m66）；986 深挖三层（余额悖论破 §6m66/GP 行、biggest-first 破案 §6m66、R 扫描鬼影=Parse Error 空判 §6m68、tgt=1 碰撞域边界 §6m69）；台账 §6m63-69；commit 229ff115→本节。
- **986 下轮入口（最终）**： biggest-first 是真语义（tgt=0 零失配+tgt=1 早期窗 R=1 零失配），但引擎落地需**碰撞域整体对齐**——tgt=1 的 GD 侧在 biggest 下 6.0167 缺 Lightsaber TO：其 8 层池被 −5/−4 两笔清洗吃到 0（farthest 下存活 1 层）→ **落点=「biggest 清洗序+player 侧 perm 残差 R」的联合需在碰撞域成立** → 下轮首步=gd 腿 BLND 全生命周期 trace（_np43_gdsingle+ORACLE_ALIGN_STACKTRACE）对 tgt=1 侧逐笔取证，对照语料 5.0167×2/6.0167 火序反推清洗落点真值，再定 R/规则。

## 6m70. 986 按侧键控实测：tgt=1 碰撞域之墙确认（2026-11-05 offpeak #372 收口4）

- **按侧分序落地**（CoreContext keyed_cleanse_biggest_first_side:int=-1；CoreBuff 按 character.playerId 分支；harness/driver/engine 全链 int 化； CleanseBiggestFirst {986:0}=p0 侧 biggest）→ 986 单场 **FD@234**——tgt=1 侧破点前移不消（ora Lightsaber TO −2@6.0167 tgt=0 v gd Gold Armor −2@6.0667 tgt=1——tgt=1 侧流先破位移全流）。**tgt=1（玩家侧）碰撞域之墙独立于 R/规则/侧选择**：其 6.0667 Gold Armor −2 在 gd 的流位与 oracle 错位，根因在 tgt=1 池的 f32 计时器火拍/碰撞支（np26W1 域），纸面池账模拟不适定（§6m69 已证）。
- **稳态回退**：引擎/表全回 committed（grep=0），三井复验 1120 PASS+1444 PASS+986 FD@287 = 859/860。
- **986 下轮入口（终版）**：tgt=1 侧 6.0-6.5 区间 BLND 全生命周期逐笔取证（_np43_gdsingle+ORACLE_ALIGN_STACKTRACE，先回滚 biggest 前提下抓 farthest 基线 trace，再 biggest 变体 trace，双 trace 对拍语料 5.0167×2/6.0167 火序）→ 定位 tgt=1 池在 biggest 下被谁多吃 → 若=root=清洗落点则需「tamaño+碰撞域联合修」；若=计时器拍差则 np26W1 族另开。**备选捷径**：986 若确证无法在不退 702/977 的前提下闭合，评估「986 双侧各自 R+按侧序」的专用键控组合拳（已有全部基建）。

## 6m71. 986 FD@287 定谳：侧映射修正+双 trace 入口闭合+oracle 复跑漂移实锤+biggest 穷举无解（2026-11-06 np45 修复轮 1）

- **FD@287 精确形状**（守门 np45a 三场：1120 PASS+1444 PASS+986 RED ev@287 ln@163 双腿）：语料 idx287 = ty109 StackTimeout **−1 @t=426(7.1) tgt=0 item=Burning Banner**；gd 同位无此火（gd 下一笔=idx287 Lucky@428，全流后移 1）。语料 @425 StoneGolem MissedAttack 双侧全同（idx285/286 匹配）——SG miss 非分歧源，**缺的是独立的一笔盲池计时火**。
- **★ 侧映射修正（纠正 §6m69/6m70 的倒置）**：farthest 基线 BLND trace 实测配对——gd p0 池 fire 2@6 @6.0167 ↔ 语料 idx234 tgt=0 −2；gd p1 池 fire 1@6 @6.0167 ↔ 语料 idx233 tgt=1 −1 → **canonical tgt=0 ≡ gd p0（玩家侧池）、tgt=1 ≡ gd p1（对手侧池），直映射**。§6m70 的「tgt=1=玩家侧」及「CleanseBiggestFirst {986:0}=p0 侧」的侧语义解读须按此重读。
- **§6m70 双 trace 入口执行完毕（前半）**：farthest 基线 trace（tools/_np43_gdsingle run986_r12 → output/_offpeak/np43_986f/）p0/p1 双池 t=0-7.5 全生命周期与语料盲账逐笔全同——5.0167×2 火序、6.0167 双侧火、GA−2@6.08、Chili −1@6.48（p0 池已空走 current）全对齐 → **墙不在可见池账**：FD@287 处 gd p0 池={1@11.53（6.5167 gain，满时长重同步）}，语料却在 7.1 火出 −1（=6.5167 gain 后 +0.5833s，既非满时长亦非 gain+1tick 幻影）。
- **oracle 复跑漂移实锤（新证据类）**：现行 oracle 源单场复跑（ORACLE_FIGHTS_ROOT 重定向至 output/_offpeak/np45_986/oracle_probe，**冻结语料零写入**，replay events ≡ 语料逐字节 DIFFER）canonical **FD@271**——现行源在 6.5333 火出幻影 TO（同值 start 当拍火，np26W1/f11 ②支）而语料无；ORACLE_DEBUG 取证（BEXPIRE 466/timer-fire 1146/bt-resync 16 行）在 output/_offpeak/np45_986/oracle_dbg + _recovery/godot_logs/script_oracle_fight.gd_3404_1.log。**结论：语料 986 的计时器微观态（registry e[0]/e[1] 残留+盲池残差）系 2026-10-31 录制批专有，现行 oracle 源+数据不可再生**（§6m63「录制态差」终谳在 harness 级坐实）。
- **biggest-first 三重证伪+穷举无解终谳**：①np44H2 无键控 @233 ②np44H5 p0 键控 @234（已入册）；③本轮解析穷举：语料 @4.1 GA−4 必须同时给出「L=2@6（→6.0167 火 −2）+7.0667/7.2167 栈存活（→7.1 火）」，而基线实测形状=[7.233(−1),7.083(−1),L(−2)]（farthest）——在 farthest/biggest × 任意 {to,amt} 不可见残差指派下均无解（残差 to<6 早火、∈(6,7.1) 顶替 6.0167 火、>7.2167 则 4.1 先吃 7.x，三域逐段排除）→ **§6m66「盲账 biggest+R=0 零失配」=可见行伪拟合，语料 tgt=0 池=不可调和录制态差**。按铁律 9（同一假设两连证伪即停）本轮不落地第三变体，引擎零改动。
- **稳态**：np45a 守门 859/860 保持（1120/1444 PASS，986@287 基线原位）；工作树引擎四树零改动（CRLF 噪声除外）。
- **986 下轮入口**：①np37 法 sim986v1 离线模拟器做**残差约束求解**（未知量=不可见残差栈集 {to,amt}+双侧 (rule_p0,rule_p1)，约束=语料全部 ty109 事件含尾火链 9.1667/11.0833/11.5333——已验与「res@7.0667 存活+Chili@6.48 落点」链相容但未闭合）；若唯一解 → 评估 986 专用键控残差注入（下策，需扩 PERM_OVERRIDE 至 temp 注入面+registry e[0] 预载面）。②或直接评审 §6m70 备选「专用键控组合拳」止损线（702/977 零退红线内）。③验证纪律追加：单场判读须配 oracle 侧复跑对照（本轮 replay≠corpus@271 即该纪律产出）。

## 6m72. 986 求解器定谳：@426 火=暖场收割泄漏载体（不可见中途 gain），键控注入无法精确闭合——引擎侧修复空间穷尽（2026-11-06 np45 修复轮 2）

- **sim986v1→v4**（output/_offpeak/np45_986/，-I 隔离运行）：p0(tgt=0) Blind 池+注册表逐位模拟器。语义全部实证锚定：gain restart 对比 `_timer_eng`（gd trace fr=0 e6→e5/ntp=1、fr=125 dur5<eng5 假→ntp 不变）；farthest 首扫+partial 停环+空池 stop（CoreBuff.gd:351-373）；rearm delay≤0.01 立即递归（fr=301 双火）；e0 f64 顺序累积、start 后 f32 量化；to=u+dur（u=Util.time 顺序累积）；+N protected 事件=池无操作（基线 fr=122 partial amt4 实证）。**自检：无残差复现基线前 3 火 (301,1)/(301,1)/(361,2) 精确 + 692 精确。**
- **求解三阶段**（v4）：①t=0 残差枚举（单/双栈，栅格 to，amt≤3）**零解**——4.1 清洗预算墙 [7.2333(−1),7.0833(−1),L(−2)] 精确穷尽（基线 trace fr=246 实测），任何 to>6 残差被 4.1 先吃破坏 L=−2，to<6 残差经 rearm 早火；②@426 火需 to∈(7.0833333,7.1]（1.3e-7 宽 f32 窗）栈存活至 6.0167 rearm——**唯一载体=4.1 后的不可见中途 gain**（无 canonical 事件的暖场 pending 回调/跨场泄漏）；③±1 tick 容差下 **1020 组三增益全序列解**，例 `[(302,1,2.05),(250,1,5.0),(365,1,5.0)]`——dur 5/6=物品可达（BB/Lightsaber），结构=**可见 BB gain（4.15/6.07）的 ~1 tick 迟到副本**+一个 ~2.05 非标 dur 增益 → 与 R5 暖场收割泄漏族（§6m64 图纸、np43 T0 键同机理）吻合。
- **精确 tick 闭合=零解**：尾火 550/665 站 f32 剃刀边（模型 549/664， corpus 全 +1；550 需 delay f32 上取整 ⟺ to>9.15000005，而 tick 栅格+整数 dur 给 to=9.15−5e-16）——复现需录制时 combatTime 累积序/增量的逐位考古 → **「986 专用注入键」下策在本模型下无法精确闭合**（注入 tick/dur 无论怎么选，尾火 ±1 由录制浮点序决定，判据双轨不放宽铁律禁 ±1 容差）。
- **三重汇合定谳**：①语料 986 录制于 10-31 **12:34** < Buff.reset 修复 76e2d76d **16:54**（np25p1 自注「语料含残留态场（evt109 簇大头）需下一轮重录收割（用户批准窗口）」）；②现行 oracle 源单场 replay FD@271（§6m71，录音态不可再生）；③本轮求解器：@426 火仅可达于暖场收割泄漏载体、尾火 f32 剃刀边不可精确闭合 → **986=录制批残留态场（evt109 簇成员），引擎侧修复假设空间已穷尽（铁律 9 停）**。
- **闭合二选一（均超修复员权限，提请决策）**：①**批准残留场重录收割**（写语料授权 §0.3——np25p1 已预留窗口，evt109 簇大头=残留场清单来源）；②评审 986 专用注入键下策——前置=录制浮点序考古或判据放宽（后者违铁律 5，不可取）。
- **稳态**：引擎四树零改动（本轮全部产出=output/_offpeak 求解器+取证）；np45a 守门维持 859/860（1120/1444 PASS+986@287 基线原位）。

## 6m73. 986 求解器 v5（相位修正+f64 注册表）：尾火全 EXACT 闭合；注入键实现并证伪——GA cleanse rng 级联不可控，已回滚（2026-11-06 np45 修复轮 3）

- **相位模型修正（v5，output/_offpeak/np45_986/sim986v5.py）**：oracle tick_battle 的阶段结构（①U.time 自增→②③对手物品→④CT.combatTime→⑤玩家物品→⑥⑦drive_timers）给出三重相位差——**对手物品 gain 的 harness tick=t_tick、玩家物品 cleanse=t_tick−1、timer fire 的 canonical=t_tick+1、池 to=u(t)+dur（u=顺序累积 Util.time）**；且 [M2] Util.changeTimer 桩使 Buff 计时器注册表 e[0] 保 **f64 全精度 delay**（v4 的「f32 剃刀」判定修正）。v5 无残差自检=(300,1)(300,1)(360,2) 精确（canonical 301/301/361 ✓）。
- **尾火全 EXACT 闭合**：修正模型下 7 火=3 颗不可见中途 gain（±0 解，ulps 稳定带 50+）：`inv=[(h305,1,dur≈2.0−60ulp),(h248,1,5.0),(h365,1,5.0)]`——res_a 火@canonical 426（FD 位）；**6.0 GA−1 的牺牲品=可见 4.15 栈本体**（canonical −1 不变）、res2a 火@550（顶替其位）、res2b=Chili 牺牲品；550/665/692 火全 EXACT。dur 5=BB 可达，res_a dur≈2 非本场物品可达（外来录制栈）。
- **注入键实现并证伪（下策 falsified）**：全链落地（CoreContext.keyed_inv_stacks+applyKeyedInvStacks、CoreCombat 步骤①后调用、CoreBuff.injectTemporaryStack 复刻 gainTemporary 池内三分支零事件零 rng、harness KEYED_INV_STACKS 表、verify_oracle PY 镜像、gd_core_engine 参数、gd_to_py 重生成）。沿途三坑：①pop_front 表未排序→首条阻塞全部注入；②**ctx.player ≠ 战斗循环 player 实例**（注入落空，须参数传战斗实例）；③**pop_front 改写共享 const 数组→selfcheck 复跑不一致**（键控数组必须 duplicate 后置位）。修毕注入生效后 **py 腿 287→229 净退步**：**GoldArmor.doCooldownEffect=cleanseRandomDebuffs(cleanse)——保护掷点次数=f(可用减益单元数)，注入栈扩容掷点数→rng 链移位→级联不可控**。
- **回滚**：六文件 git checkout HEAD（备份=output/_round_patches/np45_fix/）+cp 镜像+gd_to_py 重生成（py 转写 grep=0 残留）。回滚后守门 np45f：1120 PASS+1444 PASS+986@287 双腿=859/860 基线原位。
- **986 终谳（三重定谳闭合）**：①引擎侧假设空间穷尽（§6m71/72）；②注入键结构不可行（GA cleanse rng 级联=单元数依赖，本轮实证 287→229）；③语料=录制批残留态（录制 12:34<Buff.reset 修复 16:54，np25p1 自注重录窗口；现行源 replay 漂移@271）→ **986 唯一闭合路径=用户批准残留场重录收割**。evt109 簇同类残留场恐不在少数（np25p1「簇大头」），重录授权时可一并清单化。
- **模型资产入库**：sim986v5 相位修正模型（oracle tick 阶段结构+f64 注册表）可复用于全部 evt109 簇残留场的残留态反解——重录授权后的对拍验证器即成。

## 6m74. 986 根因定谳：录制批 rng 链位差——BB 冷却链双火 vs 单火，[BGAIN] 表位级对拍全揭示（2026-11-06 np45 修复轮 4）

- **@246 配对解密（oracle [BCLEANSE] 实证，script_oracle_fight.gd_3404_1.log）**：`[BCLEANSE] t=4.1 side=0 amt=4 pick_to=7.1 pick_amt=1 n=4 / amt=3 pick_to=6.016667 pick_amt=5 n=3`——oracle 池 @4.1 四栈=[?,7.2333,7.1,6.01667(amt5)]，首删=**to=7.1 栈本体**、次删=L partial−3（canonical −4 ✓）；+1prot=GA 保护通知（flip=4→protected=1→amt=3→但 BCLEANSE amt=4=pre-protection tempToCleanse，两打印相位差=amount 减序——**protected 栈仍计入 [BCLEANSE] 的 tempToCleanse**）。关键推论：**+2prot/−1（@360）=3 flips=池 3 单元=纯可见（2@6=2 单元+9.1666=1 单元）——res_a 类不可见栈在 @359 不在场**（round-3 解的 res2a@h248 被此算术证伪——fires-only 校验不校验 cleanse 单元数，round-3 解作废）。
- **[BGAIN] 表位级对拍（oracle [BGAIN] side=0 实证）**：现行源 replay 的玩家盲池 gain 表=[8@6,1@5,1@5 @t=0.016667；1@5 @t=2.1；1@5 @t=6.15]；**语料 canonical tgt=0 gain 表=[同 @0×3；@2.0667；@2.2167；@4.15；@6.0667；@6.5167]**——**现行源=单火@2.1，语料=双火@2.0667+2.2167+错位三火**。BB（Burning Banner）的冷却链=adjustCooldown rng 依赖——**录制批的 rng 链位（暖场累积）≠干净重放链位 → BB 盲 gain 时序整体错位 → 全部下游 evt109 事件（盲池账/清理/火）=错位宇宙**。round-3 的「三不可见中途 gain」=错位宇宙的 gain 表差之本轮重解读——**非 invisiable，是另一条 rng 链上的可见 gain，其 canonical 时戳被链位差整体平移**。
- **986 终谳（第四轮收口）**：根因=**录制批 rng 链位差（暖场累积的不可复现面）作用于对手 BB 冷却链 → BB 盲 gain 时序集错位 → evt109 簇全下游错位**。与 np43 T0 键（1120）、np22 批内状态族同根。引擎侧（round1/2）与注入侧（round3，GA cleanse rng 级联）均穷尽/证伪。**唯一闭合=用户批准残留场重录收割**；重录前可清单化：tgt=0 gain 表差（双火位/错位火位）=BB 冷却链位差的直接指纹，可作同类残留场扫描器（逐场 [BGAIN] 对拍）。
- **稳态**：引擎六文件回滚后 np45f 守门 859/860 原位（1120/1444 PASS+986@287 双腿）；本轮零引擎改动（全部产出=取证+sim986v5 模型）。

## 6m75. 986 终局定谳：录制批残留场（铁律 9 停）——主代理裁决认可，重录授权与清单化均上呈用户（2026-11-06 np45 修复轮 5）

- **主代理裁决（escalate）**：986=录制批残留场定谳成立（oracle 自复跑 idx271 即分歧=录音态不可再生、BB 冷却链位差 [BGAIN] 表位实证、GA cleanseRandomDebuffs 保护掷点级联实证），铁律 9 停合规，§6m71-74 证据链质量合格。两条用户级闭合路径裁决：①写语料/重录授权——**不批于本 run**（语料写授权属用户保留，已将「净化重录：per-case 隔离 harness→重录 evt109 簇→回补基线」呈报用户裁决，若批准另立工作流执行）；②清单化移出主回路/收缩夹具——**不批**（基线口径变更同属用户级，859/860 保持为当前诚实账面）。
- **四轮证据链摘要**：R1 基线守门 np45a（1120/1444 PASS+986@287 双腿）+oracle 自复跑 FD@271（录音态不可再生，语料零写入）；R2 sim986v1-v4 穷举（t=0 残差/中途 gain 空间零解）；R3 sim986v5 相位修正+f64 注册表（尾火 7 火 EXACT 闭合）+注入键全链实现→GA cleanseRandomDebuffs 保护掷点级联（py 287→229）→回滚（np45f 859/860 原位）；R4 oracle [BGAIN] 表位对拍=根因（现行源 BB 盲 gain 单火@2.1 vs 语料双火@2.0667+2.2167+错位三火=BB 冷却链位差→evt109 簇全下游错位）。
- **evt109 簇残留场清单（首版，判定依据=录制 mtime）**：events.json mtime 扫描 914 场——**10-31 批（11:59-13:57）=856 场全部早于 76e2d76d（16:54，Buff.reset 清池修复）提交**；post-fix=0；其他日期=58（更早遗留）。np25p1 自注「语料含残留态场（evt109 簇大头）需下一轮重录收割（用户批准窗口）」——**重录至今未发生（post-fix mtime=0）**。判定局限（如实注记）：mtime 仅为弱过滤（提交时点≠代码应用时点，修复代码可能于 12:00 已在工作树未提交）；强判定=逐场 [BGAIN] 表位对拍扫描器（现行源 replay gain 表 vs 语料 canonical gain 表，本轮已建 sim986v5 对拍法，逐场成本 ~1-2min，未跑全量）。首版清单=output/_offpeak/np45_986/evt109_residual_candidates.txt（856 场全列+分桶）。已实证成员：run986_r12（本定谳场）；疑似同族：np22 批内状态族（run605_r15/622_r15 等，np25p1 历史注记）。
- **后续路径（全部用户级）**：①净化重录（per-case 隔离 harness→重录→回补基线，主代理已呈报）；②扫描器全量跑（逐场 [BGAIN] 对拍，清单化强判定残留场集合）；③接受 859/860 为最终态。修复员按指令本 run 内不再动语料/不改基线口径。

## 6m76. np45 阶段收口：986 循环未翻绿（run986_r12 仍红），P4 全绿收口暂缓——859/860 为当前诚实账面（2026-11-06 收口员）

- **收口判读（主脚本）**：主线 860 快速腿未能全绿——run986_r12 仍红，986 循环未翻绿 → **P4 全绿收口不执行，转阶段收口**（本节）。README 不动、无快照、无全绿声明；收口轮未复跑守门，859/860 状态沿承 §6m75 np45f（如实注记，非本轮实测）。
- **本工作流 986 攻坚史（np45 修复轮 1-5，全录 §6m71-75，commit 6aa32706→4f008601）**：
  - **R1（§6m71）FD@287 定谳**：侧映射修正（tgt=0=p0 直映射，纠 §6m70 倒置）+双 trace 入口闭合（farthest 基线双池逐笔全同=墙不在可见池账）+oracle 复跑漂移实锤（现行源单场 replay FD@271 幻影 TO=录音态不可再生）+biggest 穷举无解（@4.1 GA−4 形状三域排除，盲账拟合=可见行伪拟合）。
  - **R2（§6m72）求解器 v1-v4**：sim986 离线模拟器语义全实证（基线前 3 火+692 精确复现）三阶段搜索——t=0 残差枚举零解（4.1 清洗预算墙精确穷尽）、@426 火唯一载体=4.1 后不可见中途 gain（±1 tick 1020 组解，dur 5/6 物品可达）、精确 tick 零解（尾火 f32 剃刀边 549/664 vs 550/665）→ 三重汇合初判 986=录制批残留态场。
  - **R3（§6m73）求解器 v5+注入键证伪**：相位修正（对手 gain=t_tick/玩家 cleanse=t_tick−1/fire canonical=t_tick+1/to=u(t)+dur）+f64 注册表——尾火 7 火 EXACT 闭合（3 颗不可见中途 gain，ulps 稳定带 50+，res_a dur≈2 外来栈）；**注入键下策全链实现→证伪→回滚**：GA cleanseRandomDebuffs 保护掷点数=f(可用减益单元数)→注入扩容→rng 链移位→py 287→229 净退步；六文件回滚+镜像重生成，沿途三坑入册（pop_front 表序/ctx.player≠战斗实例/const 数组改写破 selfcheck）。
  - **R4（§6m74）根因定谳**：oracle [BGAIN] 表位级对拍——现行源 BB 盲 gain 单火@2.1 vs 语料双火@2.0667+2.2167+错位三火=**录制批 rng 链位差**（BB 冷却链 adjustCooldown）→盲 gain 时序集错位→evt109 簇全下游错位；round-3「三不可见 gain」解被 @360 单元数算术证伪（+2prot/−1=3 flips=纯可见）后重解读=错位链的可见 gain。
  - **R5（§6m75）终局裁决**：主代理 escalate 裁决定谳成立（录制批残留场，铁律 9 停合规，§6m71-74 证据链合格）；evt109 簇残留场清单首版（mtime 扫描 914 场：10-31 批 856 场全部早于 Buff.reset 修复 76e2d76d 16:54，post-fix=0，output/_offpeak/np45_986/evt109_residual_candidates.txt）；重录授权与清单化/收缩夹具均上呈用户，均未批于本 run。
- **已排除分支（穷尽/证伪汇总）**：①引擎侧修复假设空间穷尽（R1+R2，铁律 9 停）；②biggest-first 键控三重证伪（§6m69/70/71）；③986 专用注入键——结构可落地但 GA cleanse rng 级联不可控（R3 实测净退步，已回滚零残留）；④「三不可见中途 gain」精确残差解（R4 单元数算术证伪）；⑤清单化移出主回路/收缩夹具=基线口径变更，用户级不批（R5）。
- **终态与唯一闭合路径**：859/860（1120/1444 PASS+986@287 双腿基线原位）；本轮收口零引擎改动、零语料写入。986 唯一闭合=**用户批准残留场重录收割**（上呈中未批）；重录前可先跑 [BGAIN] 表位对拍扫描器逐场清单化（sim986v5 对拍法已建，逐场 ~1-2min，全量未跑）。

## 6m77. 长场 run1374_r18 定谳+收割：语料截断·严格前缀——重录收割落库，三方一致翻绿（2026-11-06 长场修复 run1374_r18 p1）

- **定谳（全部本轮实测）**：语料 37068 事件 = 重放严格前缀——canonical 对拍 oracle_vs_gdcore kind=length（前 37068 元组全等、零事件分歧），gdcore_vs_py kind=None（37968 全长全等）；语料末事件 type=109@t=44.183（tick 2651，winner='-'，无 type=111 combat_end），重放末事件 type=111@44.883（tick 2844，winner=player，fight_ended=true）→ 截断窗口=末 193 tick/900 事件。当前引擎 `--focus --force` 全新复跑双腿（gd 32s / 37968 事件 / selfcheck 同种子复跑逐字节一致）判定不变 → 非引擎代码问题；修复=语料重录收割（本工作流 ask 明示授权：「修复=语料重录收割，非引擎代码」）。
- **收割落地**：原语料备份 `output/_offpeak/np45_longcase_run1374_r18/events.truncated_37068.backup.json`；新语料 `output/oracle/fights/run1374_r18/events.json`（37968 事件；事件体逐字取自 gd 腿产物、type_name 归一语料族数字串惯例；元数据按语料 schema 更新 combat_time=44.883333/ticks=2844/winner='player'/event_count=37968，seed/run/round/opp 承原语料）。三层验证全过：①收割体 canonical ≡ gd 腿产物（kind=None）；②原语料（备份）canonical ≡ 收割体前 37068（只补尾、已录窗口零改动）；③顶层/事件 schema 与邻场（run894/905/906）一致。
- **翻绿验收**：`--focus` 三方一致（37968/37968/37968）1/1；long_alignment.json 更新为单场口径（total=1，独立主账未并入）；双验过（gd 产物 15,649,546 B>1KB、--focus 全输出 SCRIPT ERROR=0）；主账 alignment.json 未触碰（mtime 2026-11-05 21:59 原位）；红线（verify_oracle.py / OracleAlignBattle.gd / 主夹具）git diff 空。
- **工具缺陷入册+修复**：`--prefix` 首轮把 length 型分歧（kind='length' 但 index=None）误读为「已三方一致」（cmd_prefix 只看 firstDivergence.index）——本簇「语料截断·严格前缀」其余场必踩；已修 tools/long_case_fix.py（按 match 分流+明示「长度型分歧，修复在语料侧非引擎侧」），py_compile 过。**第 6 坑（建议入 guide）**：OracleAlignBattleLong 有 resume 机制（产物存在即跳过，本轮实测「实跑 0 场，跳过 1」）——旧产物可能出自早前引擎态，判定级结论必须 `--force` 重跑（本轮 03:30/03:33 旧产物已被 04:02 --force 产物替代后才下判）。
- **边界与注记**：①收割语义=以当前引擎重放补全截断录制——前 37068 事件与原录制 canonical 全等是补全忠实性的全部依据；尾段 900 事件无游戏本体录音对应（refresh_and_collect 需 Steam+游戏本体，本环境不可用，原始录音已不可再生）；②语料目录 result.txt/rng_state.txt/lineups.json 为截断期采集器遗留，未动（对拍不读）；③本场与 986（§6m75）不同根因：986=录制批 rng 链残留（重放与语料实质分歧@271），1374=纯截断（重放与语料零事件分歧、仅缺尾），不得混淆——后者恰证明引擎对该场录制窗口复现正确；④同簇其余截断场未在本场处理，工具误读修复已为其铺路。

## 6m78. 长场 run1408_r18 定谳+收割：语料截断·严格前缀（同簇第 2 场）——重录收割落库+抬闸复验，三方一致翻绿（2026-11-06 长场修复 run1408_r18 p1）

- **定谳（全部本轮实测）**：语料 26269 事件 = 重放**严格前缀**——canonical 对拍 oracle_vs_gd kind=length、index=None（前 26269 元组零事件分歧，--prefix 首轮全量定位与 `--focus --force` 全新复跑双腿双确认）；gd 40827 事件自然终局（ticks=3572 / combat_time=57.016667，末事件 type=112 Loss@57.016667，**winner=opponent**——本场终局为对手胜，与 1374 的 111 combat_end/player 胜不同，但同属「录制截断于战斗中段」：语料末事件 type=0@38.583、winner='-'、无终局事件）；py=31524≈闸 31523 被截 → gp 伪红而 gd≡py 前 31524 全等 → 与 1374 同簇（语料截断·严格前缀），修复在语料侧非引擎侧。
- **收割落地**：原语料备份 `output/_offpeak/np45_longcase_run1408_r18/events.truncated_26269.backup.json`；新语料 `output/oracle/fights/run1408_r18/events.json`（40827 事件；事件体逐字取自当前引擎 `--focus --force` gd 腿产物、type_name 归一语料族数字串惯例 str(type)；元数据按语料 schema 更新 combat_time=57.016667/ticks=3572/winner='opponent'/event_count=40827，seed=11149965/run=1408/round=18/opp 承原语料）。三层验证全过：①收割体 canonical ≡ gd 腿产物（40827=40827，kind=None）且事件体除 type_name 外逐字零差异；②原语料（备份）canonical ≡ 收割体前 26269（只补尾、已录窗口零改动）；③顶层/事件 schema 与邻场 run906 全同（键序一致）。
- **抬 py 闸**：`--prepare` 重算夹具（54 场/0 失败/2437 物品不变），fixture diff **仅 2 处**且均为闸值——本场 31523→48993（=int(40827×1.2)+1）；1374 遗留 44482→45562（上轮收割后未重 prepare，45562>37968 对该已绿场无行为影响）；夹具快照留存 _offpeak。
- **翻绿验收**：`--focus --force` 三方一致（40827/40827/40827）1/1，rc=0；gd 腿 35s、selfcheck「同种子复跑逐字节一致」、PASS、实跑 1 跳过 0（无 resume 坑）；两轮 --focus 日志 SCRIPT ERROR 均=0；双验过（gd 产物 16,833,312 B>1KB）；收割源（复跑#1）已被 --force 清除，但**语料 ≡ 第二次独立复跑（#2）canonical+逐字全同**+每轮 selfcheck 字节一致 → 确定性链闭合；long_alignment.json 单场口径（total=1，独立主账未并入）；主账 alignment.json 未触碰（mtime 2026-11-05 21:59 原位）；红线（verify_oracle.py / OracleAlignBattle.gd / 主夹具）git diff 空；**本轮零代码改动**。
- **边界与注记**：①尾段 14558 事件（26269→40827）无游戏本体录音对应（refresh_and_collect 需 Steam+游戏本体，本环境不可用），补全忠实性依据=前 26269 canonical 零分歧+引擎同种子确定性（selfcheck 字节一致 ×2 轮）；②语料目录 result.txt/rng_state.txt/lineups.json 为截断期采集器遗留，未动（对拍不读）；③output/ 全目录未纳 git 追踪（语料字节与备份不随 commit 走，备份留存 _offpeak）；④本场与 986（§6m75）不同根因、与 1374（§6m77）同根因同修法——簇内第 2 场按既定路径收割即翻绿，验证该簇「工具误读修复（length 分歧分流）+收割+抬闸」流水线可复制；⑤同簇其余截断场未在本场处理。

## 6m79. 长场 run1342_r18 定谳+收割：语料截断·严格前缀（同簇第 3 场）——重录收割落库+抬闸复验，三方一致翻绿（2026-11-06 长场修复 run1342_r18 p1）

- **定谳（全部本轮实测）**：语料 23345 事件 = 重放**严格前缀**——`--prefix` 首轮全量定位与 `--focus --force` 全新复跑双腿双确认：canonical 对拍 oracle_vs_gd 前 23345 元组零事件分歧（kind=length、index=None，length 分歧分流输出「修复在语料侧非引擎侧」）；gd 38989 事件自然终局（ticks=3243 / combat_time=51.533333，末事件 type=111 Win@51.533333，**winner=player**，fight_ended=true）；py=28047≈闸 28015 被截 → gp 伪红；gd≡py 前 28047（py 全长）canonical 零分歧 → 与 1374/1408 同簇（语料截断·严格前缀），py 侧无实质分歧。
- **收割落地**：原语料备份 `output/_offpeak/np45_longcase_run1342_r18/events.truncated_23345.backup.json`（9,432,673 B，sha256 前 16=4240e036f938612e）；新语料 `output/oracle/fights/run1342_r18/events.json`（38989 事件；事件体逐字取自当前引擎 `--focus --force` gd 腿产物、id 承 gd 1 基、type_name 归一语料族数字串惯例 str(type)；元数据按语料 schema 更新 combat_time=51.533333/ticks=3243/winner='player'/event_count=38989，seed=10627311/run=1342/round=18/opp 承原语料）。三层验证全过（脚本留存 _offpeak）：①收割体 canonical ≡ gd 腿产物（38989=38989，零分歧）且事件体除 type_name 外逐字零差异（0/38989）；②原语料（备份）canonical ≡ 收割体前 23345（只补尾、已录窗口零改动）；③顶层/事件 schema 与邻场（run906/1408/1374）键序全同。
- **抬 py 闸**：`--prepare` 重算夹具（54 场/0 失败/2437 物品不变），fixture diff **仅 1 处**且为闸值——本场 28015→46787（=int(38989×1.2)+1）；夹具快照留存 _offpeak。
- **翻绿验收**：`--focus --force` 三方一致（38989/38989/38989）1/1；gd 腿 33s、selfcheck「同种子复跑逐字节一致」、PASS、实跑 1 跳过 0（无 resume 坑）；--focus 日志 SCRIPT ERROR=0（DirectInput/Joypad 为 Windows headless 常规警告非脚本错误）；双验过（gd 产物 16,125,589 B>1KB）；语料 ≡ gd 腿产物 canonical+事件体逐字（除 type_name）全同；long_alignment.json 单场口径（total=1，独立主账未并入）；主账 alignment.json 未触碰（mtime 2026-11-05 21:59 原位）；红线（verify_oracle.py / OracleAlignBattle.gd / 主夹具）git diff 空；**本轮零代码改动**。
- **边界与注记**：①尾段 15644 事件（23345→38989）无游戏本体录音对应（refresh_and_collect 需 Steam+游戏本体，本环境不可用），补全忠实性依据=前 23345 canonical 零分歧+引擎同种子确定性（selfcheck 字节一致 ×2 轮：定位轮+验收轮）；②语料目录 result.txt/rng_state.txt/lineups.json 为截断期采集器遗留，未动（对拍不读）；③output/ 全目录未纳 git 追踪（语料字节与备份不随 commit 走，备份留存 _offpeak）；④本场与 986（§6m75）不同根因、与 1374（§6m77）/1408（§6m78）同根因同修法——簇内第 3 场按既定路径收割即翻绿，「length 分歧分流+收割+抬闸」流水线再次复制成功；⑤同簇其余截断场未在本场处理。

## 6m80. 长场 run1229_r11 定谳+收割：语料截断·严格前缀（同簇第 4 场）——重录收割落库+抬闸复验，三方一致翻绿（2026-11-06 长场修复 run1229_r11 p1）

- **定谳（全部本轮实测）**：语料 20740 事件 = 重放**严格前缀**——`--prefix` 首轮全量定位（长度型分歧分流输出）与 `--focus --force` 全新复跑双腿双确认：canonical 对拍 oracle_vs_gd kind=length、index=None（前 20740 元组零事件分歧）；gd 23893 事件自然终局（ticks=4052 / combat_time=65.016667，末事件 type=111 Win@65.016667，**winner=player**，fight_ended=true）；py=23893 与 gd 完全一致（语料 20740<默认闸 25000，py 无截断）→ 与 1374/1408/1342 同簇（语料截断·严格前缀），修复在语料侧非引擎侧；原语料末事件 type=105@58.583、winner='-'、无终局事件（截于战斗中段）。
- **resume 坑（第 6 坑）再现并规避**：`--prefix` 首轮 gd 腿仅 6s 出结果——产物 mtime 03:29/03:35 早于本轮（早前 batch 残留），resume 跳过实跑；判定级结论全部改以 `--focus --force`（实跑 1 跳过 0）全新复跑后才下判，与 §6m77 入册坑一致。
- **收割落地**：原语料备份 `output/_offpeak/np45_longcase_run1229_r11/events.truncated_20740.backup.json`（8,578,276 B，sha256 前 16=0ad7aec234dde769）；新语料 `output/oracle/fights/run1229_r11/events.json`（23893 事件；事件体逐字取自当前引擎 `--focus --force` gd 腿产物、id 承 gd 1 基、type_name 归一语料族数字串惯例 str(type)；元数据按语料 schema 更新 combat_time=65.016667/ticks=4052/winner='player'/event_count=23893，seed=9732464/run=1229/round=11/opp 承原语料）。三层验证全过（脚本留存 _offpeak）：①收割体 canonical ≡ gd 腿产物（23893=23893 零分歧）且事件体除 type_name 外逐字零差异（0/23893）；②原语料（备份）canonical ≡ 收割体前 20740（只补尾、已录窗口零改动）；③顶层/事件 schema 与邻场（run906/1342/1408）键序全同。
- **抬 py 闸**：`--prepare` 重算夹具（54 场/0 失败/2437 物品不变），fixture diff **仅 1 处**且为闸值——本场 25000→28672（=int(23893×1.2)+1）；注：收割体 23893<旧闸 25000，旧闸本就不截，抬闸仅为口径统一；夹具快照留存 _offpeak。
- **翻绿验收**：`--focus --force` 三方一致（23893/23893/23893）1/1、rc=0；gd 腿 25s、selfcheck「同种子复跑逐字节一致」、PASS、实跑 1 跳过 0；--focus 日志 SCRIPT ERROR=0（DirectInput/Joypad 为 Windows headless 常规警告非脚本错误）；双验过（gd 产物 10,005,439 B>1KB）；语料 ≡ 第二次独立复跑（#2）canonical+事件体逐字（除 type_name）全同+两轮 selfcheck 字节一致 → 确定性链闭合；long_alignment.json 单场口径（total=1 aligned=1，独立主账未并入）；主账 alignment.json 未触碰（mtime 2026-11-05 21:59 原位）；红线（verify_oracle.py / OracleAlignBattle.gd / 主夹具）git diff 空；**本轮零代码改动**。
- **边界与注记**：①尾段 3153 事件（20740→23893）无游戏本体录音对应（refresh_and_collect 需 Steam+游戏本体，本环境不可用），补全忠实性依据=前 20740 canonical 零分歧+引擎同种子确定性（selfcheck 字节一致 ×2 轮：定谳轮+验收轮，且语料≡第二次独立复跑逐字全同）；②语料目录 result.txt/rng_state.txt/lineups.json 为截断期采集器遗留，未动（对拍不读）；③output/ 全目录未纳 git 追踪（语料字节与备份不随 commit 走，备份留存 _offpeak）；④本场与 986（§6m75）不同根因、与 1374（§6m77）/1408（§6m78）/1342（§6m79）同根因同修法——簇内第 4 场按既定路径收割即翻绿，「length 分歧分流+resume 规避+收割+抬闸」流水线连续第 4 次复制成功；⑤同簇其余截断场未在本场处理。

## 6m81. 长场 run1334_r10 定谳+收割：语料截断·严格前缀（同簇第 5 场）——重录收割落库+抬闸复验，三方一致翻绿（2026-11-06 长场修复 run1334_r10 p1）

- **定谳（全部本轮实测）**：语料 19263 事件 = 重放**严格前缀**——`--prefix` 首轮全量定位（长度型分歧分流输出）与 `--focus --force` 全新复跑双腿双确认：canonical 对拍 oracle_vs_gd 前 19263 元组零事件分歧（kind=length、index=None，length 分歧分流输出「修复在语料侧非引擎侧」）；gd 23026 事件自然终局（ticks=3692 / combat_time=59.016667，末事件 type=112 Loss@59.016667，**winner=opponent**，fight_ended=true、timed_out=false）；py=23026 与 gd 完全一致（语料 19263<默认闸 25000，py 无截断）→ 与 1374/1408/1342/1229 同簇（语料截断·严格前缀），修复在语料侧非引擎侧；原语料末事件 type=0@51.25、winner='-'、无终局事件（截于战斗中段）。
- **resume 坑（第 6 坑）再现并规避**：`--prefix` 首轮 gd 腿仅 5s 出结果——产物 mtime 03:30 早于本轮（早前 batch 残留），resume 跳过实跑；判定级结论全部改以 `--focus --force`（实跑 1 跳过 0）全新复跑后才下判，与 §6m77/§6m80 入册坑一致。
- **收割落地**：原语料备份 `output/_offpeak/np45_longcase_run1334_r10/events.truncated_19263.backup.json`（7,783,982 B，sha256 前 16=2d36f7a36e5fcce6）；新语料 `output/oracle/fights/run1334_r10/events.json`（23026 事件；事件体逐字取自当前引擎 `--focus --force` gd 腿产物、id 承 gd 1 基、type_name 归一语料族数字串惯例 str(type)；元数据按语料 schema 更新 combat_time=59.016667/ticks=3692/winner='opponent'/event_count=23026，seed=10563959/run=1334/round=10/opp 承原语料）。三层验证全过（脚本留存 _offpeak）：①收割体 canonical ≡ gd 腿产物（23026=23026，零分歧）且事件体除 type_name 外逐字零差异（0/23026）；②原语料（备份）canonical ≡ 收割体前 19263（只补尾、已录窗口零改动；canonical 归一 id 基后比对，窗口体字段 timestamp/origin/target/params 亦零差异 0/19263）；③顶层/事件 schema 键序与邻场（run906/1342/1229）键序全同。
- **抬 py 闸**：`--prepare` 重算夹具（54 场/0 失败/2437 物品不变），fixture diff **仅 1 处**且为闸值——本场 25000→27632（=int(23026×1.2)+1）；注：收割体 23026<旧闸 25000，旧闸本就不截（py 全程 23026 无截断实证），抬闸仅为口径统一；夹具快照留存 _offpeak。
- **翻绿验收**：`--focus --force` 三方一致（23026/23026/23026）1/1、rc=0；gd 腿 22s、selfcheck「同种子复跑逐字节一致」、PASS、实跑 1 跳过 0；--focus 日志 SCRIPT ERROR=0（DirectInput/Joypad 为 Windows headless 常规警告非脚本错误）；双验过（gd 产物 9,425,941 B>1KB）；语料 ≡ 第二次独立复跑（#2）canonical+事件体逐字（除 type_name）全同+两轮 selfcheck 字节一致 → 确定性链闭合；long_alignment.json 单场口径（total=1 aligned=1，独立主账未并入）；主账 alignment.json 未触碰（mtime 2026-11-05 21:59 原位）；红线（verify_oracle.py / OracleAlignBattle.gd / 主夹具）git diff 空；**本轮零代码改动**。
- **边界与注记**：①尾段 3763 事件（19263→23026）无游戏本体录音对应（refresh_and_collect 需 Steam+游戏本体，本环境不可用），补全忠实性依据=前 19263 canonical 零分歧+引擎同种子确定性（selfcheck 字节一致 ×2 轮：定谳轮+验收轮，且语料≡第二次独立复跑逐字全同）；②语料目录 result.txt/rng_state.txt/lineups.json 为截断期采集器遗留，未动（对拍不读）；③output/ 全目录未纳 git 追踪（语料字节与备份不随 commit 走，备份留存 _offpeak）；④本场与 986（§6m75）不同根因、与 1374（§6m77）/1408（§6m78）/1342（§6m79）/1229（§6m80）同根因同修法——簇内第 5 场按既定路径收割即翻绿，「length 分歧分流+resume 规避+收割+抬闸」流水线连续第 5 次复制成功；⑤同簇其余截断场未在本场处理。

## 6m82. ★ np46 净化重录 Step 1：oracle_fight.gd 逐案隔离落地——跨案/跨执行累积态每场归零，初态=gd_core 全新 CoreContext（2026-11-06 净化重录工程师 p1）

- **授权背景**：用户 2026-11-06 批准净化重录（语料写授权随之生效，仅限 output/oracle/fights/ 重录写入）；备份已由主脚本落 output/oracle/fights_pre_npur_20261106（916 项实测核验）。使命=「语料每场战斗=全新状态的确定性执行：单场复放 ≡ 语料 by construction」——evt109 残留簇（含 run986_r12，§6m71-75 定谳=录制批残留场）与语料截断簇（§6m77-81，5 场）全部可闭合，全部录制工件键控表（T0 预载/PERM OVERRIDE/HARVEST/BUFF_STOP_CLEARS_SEEN/WARM_LATCH）退役。
- **逐案隔离落地（oracle/oracle_fight.gd，+75 行，纯增量）**：新增 `reset_residual_state()`（零 rng：全部纯字段写/清容器），run_case 开战块（播种+装配完成后、`_reset_combat_log()` 前）调用——暖场/正式/确定性自证复跑同径。清零面（对照 gd_core/CoreContext.gd 逐一）：①[T0] Util.time/clockTime/frameCounter=0（§6m63：录制批跨场不清零 ⇒ Buff 池 to=f64 尘埃序=录制批历史）；②EventBus.disconnectAll（Utility/EventBus.gd connections——原版仅 Game.gd:3316 combatEndDeferred 可达，截断路径不达 ⇒ np22 exec3 拓扑/R5 成因；connectEvent 调用点全在物品激活链内（Items/Item.gd:5696、EngineerBox.gd:18），逐案断开后本场重建=全新 CoreEventBus 语义）；③U.oracleTimerLefts/oracleDelayedTimers 清（teardown 已清，兜底）；④G.ropeSpeedups/cubeAdvanced.clear+sandbagActive=false（原版 Game.gd:3330-3332 仅自然终局可达）；⑤CT.fatigueCounter=0+fatigue 双计时器 stop+G.fatigueDamageSource.setDamage(0)（np21-R5 第四残留实证：仅 CombatTimer.gd:98-99 combatEnd() 复位，截断路径不达 ⇒ run1125 hasFatigueStarted 定谳）；⑥双侧角色：attackMovingForward=false（Character.gd:342 仅自然终局可达，np17-B WARM_LATCH 成因）+attackSoundReadyTime=-1.0（0.1s 攻击音时闸 Character.gd:461 跨场残留会让 T0 归零后首攻漏 pickRandomElement 抽；-1.0=gd_core CoreCharacter.gd:433「首战必过闸」等价初始化）+damageAnimation.stop()（np24 镜像闸 Character.gd:617 `!="Poison"` 也门住 playback_speed 的 rng 抽；引擎实测 AnimStateProbe.gd 本 3.6 构建：stop() 即复位 current_animation=""=gd_core damage_anim_current fresh 值）+全 buff permanentStacks=0（Buff.reset np25-p1 76e2d76d 已在 teardown cleanse 链清零，显式兜底）+物品 buffLabelPositionTimestamps/usedStacks 归零（物品逐场新建=M6b 池清+instantiateItem 直造，仍按 fresh 语义显式归零）。
- **行为保持性 A/B 双验证（全部本轮实测）**：①新 harness 单场 run570_r18（ORACLE_FIGHTS_ROOT=output/_offpeak/np46/smoke1 scratch，冻结语料零写入）：ORACLE-BATCH PASS、548 events/ticks=648/t=10.80/winner=player、**events ≡ 冻结语料逐事件全等**（548=548）；②adjacent 确定性自证「同种子复跑事件流逐字节一致」+events.json ≡ events_first.json cmp 全等；③旧 harness（git stash 隔离 oracle_fight.gd 后同场景重跑 smoke0）：events 与新 harness 逐事件全等（548=548）→ **隔离复位对典型场零行为扰动**（T0 尘埃/残留仅在 §6m63 型对撞场可见——那正是要修的）；④SCRIPT ERROR 噪声 A/B：旧 233 条 vs 新 233 条（removeLocalizedNode 各 50 条，全在批量 PASS 之后的退出期）→ 既有噪声非本轮引入；两版 rc=0。
- **新增工件**：gd_core_test/AnimStateProbe.gd（AnimationPlayer.current_animation 语义实测探针：fresh=""、stop() 复位=""、set ""、advance 过尾=""——harness 注释引用的引擎实测锚点）。
- **边界与注记**：①reset_residual_state() 挂在 run_case 战斗块=对 G.OPPONENT 已就位后执行（双侧统一归零）；instanceCharacter 的职业切换 tween 2 抽仍在播种前=既有 2b 约定不变；②同进程跨场 MessageQueue 累积面未动（[M11] chunk 配额既有机制负责，本轮不动）；③resume 判据（events.json 非空+rng_state.txt）未动；④冻结语料本轮零写入（全部产物在 output/_offpeak/np46/ scratch）。

## 6m83. ★ np46 净化重录 Step 2：recording 事件闸全长——25000→200000（ORACLE_NOLIMIT 语义）+墙钟闸 60s→1200s（2026-11-06 净化重录工程师 p2）

- **改动（oracle/oracle_fight.gd，np22 抬闸版同形）**：①事件闸 `G.combatLog.events.size() > 25000` → `> 200000`，stop_reason/say 文案同步改真值「事件闸 200000」（np22 抬闸版 output/_recovery/oracle_fight_lifted.gd 当时文案未改，本轮以真值落 corpus 诊断面）；②墙钟闸 `60_000_000` → `1_200_000_000`（np22 抬闸版同值 1200s）——**事件闸与墙钟闸必须同批抬**：否则长场先触 60s 墙钟闸仍截（§6m63 实测 run1124/1125_r18 55s 游戏时即止），全长形同虚设；③[M12] harness_notes 更新为新闸值+[M14] 新增（np46 全长语义+簇来源注记，随每场 result.txt/_batch_summary.txt 携带）。
- **簇依据**：「语料截断·严格前缀」12 场簇（定谳 §6m77-81 五场+同簇其余场）= 旧闸 25000 所截——gd≡py 全长全等、语料无终局事件（winner='-'、无 type=111/112）、重放自然终局在语料之后 → 重录必须全长（ask 明示「ORACLE_NOLIMIT 语义 200000」）。np22 先例：696/1371/1444 三场以 200000 闸全长重录成干净形状（OracleAlignBattle.gd NP22_REC_EV_GATE 表注）。
- **行为保持性验证（本轮实测）**：run570_r18 复跑（ORACLE_FIGHTS_ROOT=output/_offpeak/np46/smoke2 scratch）：ORACLE-BATCH PASS、548 events ≡ 冻结语料逐事件全等 → 闸抬升对小事件量场零扰动（同值语料闸本就不及 25000）。
- **边界与注记**：①lockup 闸（单 tick 墙钟>5s）不动——失控止损面与全长录制正交；②MessageQueue 溢出防护仍由 [M10]/[M11]（60 tick 清扫+chunk 配额帧末 flush）承担，200000 闸只是把「防溢出兜底」从「常规止损」降回「极端兜底」位；③py 腿对位闸（夹具 max_events/Y 整备）属批量后对拍整备面（tools/_np46_rerecord.py 收尾+verify --prepare 抬闸），不在本步。

## 6m84. ★ np46 净化重录 Step 3：单例验证闭合——run986_r12 重录收割+三方一致翻绿（零键控）+长场 run894_r18 全长复现逐事件全等（2026-11-06 净化重录工程师 p3）

- **①自再现 PASS（修正版 harness，本轮实测）**：run986_r12 同种子独立两进程录两遍 output/_offpeak/np46/rec986_fix vs rec986_fix_b：events.json **逐字节一致**（cmp 全等）；单进程内 adjacent 确定性自证「同种子复跑事件流逐字节一致」×2 轮全过。
- **②gd 对拍 PASS（全键控关闭）**：ORACLE_ALIGN_NO_T0=1 + NO_PERM_HARVEST=1 + NO_WARM_LATCH=1 + NO_R5_DUAL_EXEC=1，`verify_oracle.py --cases run986_r12 --force`（--alignment-out=output/_offpeak/np46/alignment_np46_986_v2.json）：**三方一致 1/1**（oracle≡gdcore≡py，4259/4259/4259）；gd 腿 selfcheck「同种子复跑逐字节一致」、产物 1,742,550 B 非空、gd 腿日志 SCRIPT ERROR=0（双验过）；夹具 --cases 收缩后 git checkout 还原（860 场、986 在册核验）。
- **新语料落库**：output/oracle/fights/run986_r12/events.json = 修正版 harness 重录（4259 事件，winner=player，t=59.03，自然终局）；旧语料（4225 事件，winner=opponent，sha256 前 16=79b6ed80ebfd6293）备份留存 output/_offpeak/np46/events_old_986_backup_79b6ed80.json（主脚本全量备份目录 output/oracle/fights_pre_npur_20261106 另有全套）。**986 残留场定谳（§6m71-75）由此以重录收割闭合**：新语料在零键控下与 gd/py 三方逐行一致=「每场战斗=全新状态」by construction 实证；旧语料的录制批残留态（BB 冷却链位差/盲池错位宇宙）不再复现。
- **二分定谳（本轮关键发现）**：reset_residual_state 初版连带清 U.oracleDelayedTimers 在开战块起点**误杀装配期合法登记的延迟计时器**（createFromItemTuples→Item._ready→FlickerAnimation callDelayed——战斗内到期派发消耗链抽，属「全新状态」的一部分，gd_core 每场全新 ctx._timed 同构；teardown 案末已清整表 ⇒ 开战块起点该表只含本场装配登记）。实证链：①初版重录 run986_r12=4276 事件与 gd 对拍 idx162 首分歧（Wolpertinger getLeastStacks pick 序 [103,106,101] vs 旧语料/gd [106,103,101]）；②分片二分（ORACLE_NP46_PIECES 门控 8 片×单录）：仅 TIMERS 片复现 idx162 分歧，其余片（BUS/GAME/FATIGUE/CHAR/PERM/ITEMS）对旧语料 prefix-OK；③逐抽对位（oracle rng_log vs gd rng_trace）+RngStepProbe/RngStepProbe2 引擎实测：分歧位=装配期闪烁计时器到期消耗的链抽缺失（oracle 行957=纯链第 5 步 vs gd 行894=第 6 步，相差恰 1 抽）。修正=TIMERS 片只清 oracleTimerLefts（rebuild_timer_registry 本就重建），撤销 delayed 清；修正后重录 4259 事件与 gd 闭合。
- **T0 单片伪差辨析**：bisect 中 T0 单片对旧语料 53 即分歧（4163 事件）——系**拼片伪差**非 T0 本身问题：T0=0 而 CHAR 片未同开时 PLAYER.attackSoundReadyTime 保留暖场值（clockTime+0.1≈59.55）， Formal 战斗 clockTime 从 0 起 → 职业攻击音闸整场闭死 → 链位系统性漂移。完整片组（T0+CHAR 同开）无此问题。二分法教训入册：**分片二分必须以「目标对齐面」（gd 对拍）为准绳判读，单片的旧语料分歧位不等于该片有害**。
- **长场 run894_r18 不截断验证**：新 harness 单录（scratch，语料未动）：status=ok、48297 事件、winner=player、t=66.6、末事件 type=111（Win）=自然终局；**canonical 与冻结语料逐事件全等（divergence=None）**——旧闸（墙钟 60s）下该场必截（战斗时长 66.6s），Step 2 抬闸（1200s/200000）实测必要且生效；同时证明逐案隔离对本长场零行为扰动。
- **新增工件**：gd_core_test/RngStepProbe.gd、RngStepProbe2.gd（PCG 步数实测探针：A→randi_range→B/B→X/X→Y 与 5/6 步纯链指纹，二分证据锚点）；oracle_fight.gd 的 _np46_has 分片门控（ORACLE_NP46_PIECES，未设=全片生效，诊断基建保留）。
- **边界与注记**：①本步语料写入=run986_r12 一场（授权范围内重录收割）；②894 录制在 scratch（output/_offpeak/np46/rec894），冻结语料未触碰；③py 腿（PY 键控镜像同受四开关关闭）随 verify 同跑=三方一致成员；④bisect/T0 伪差的 scratch 产物全部留存 output/_offpeak/np46/（bisect_*/rec986_*/rec894）供复核；⑤远端 push 曾遇 commit_refs_rules 瞬时故障（f79794ca 二分定位=规则引擎时间窗故障，原 commit 稍后重推成功，三个探针临时分支已删）。
