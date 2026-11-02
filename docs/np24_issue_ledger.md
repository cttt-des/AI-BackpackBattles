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
## 6k. 循环轮战报 VIII（2026-11-02；W2 正解入账 815/45）

- **W2 正解净账 ✅**：op14b 全量=**814/860**（净 +5：1097/1105/1106/1107/1269 翻绿，零退步）——文件序全链保序（aaeaf731）实效验证。**+收割 run1129（重录）=815/860**（--compare-only 合并）。
- **46 红重聚类（reds_op14b.json/reds46_cluster.txt）**：W3 隐形抽族（damage 值差）12 场=1441/1534/1536/1545/733/846/933/962/1118/1499/1507/1427；W2 charge 残余 8 场=1101/1102/1104/1163/1280/1290/1331/1530；W4 真长尾 22 场=578/618/622/687/702/760/775/848/899/921/939/947/977/981/986/1022/1120/1253/1444/1487/1491/1540；1514 基线红。run1104 no-probe 已补重放（corpus 新鲜，REAL@180 归 charge 残余）。
- **W2 charge 残余模式（1101/1102 窗口）**：oracle PM@201/255 激活（105+13+t0），gd 的 PM 缺位/迟激活——PerpetuumMobile.onPrepare 的 connectToCharacterBuffs(onBuffChanged)+character_used_stamina 连接面+doCooldownEffect 循环（usedStacks refund→giveStacks；giveStamina→activate）逐抽对位待做；1104=Djinn Lamp 101@250 v gd Mana Orb 105 次序差。
- **隐形抽定位暂停**（Healthbar/DamageMeter/Game.gd:4969 等排除，属商店面）——两轮对拍法（MARK 桩/全场扫描）均已证伪，值指纹法（0.738357 同源序列）留下轮。
- **下一棒**：offpeak-2cbf06c9 任务书（§6j 攻击序+本节更新）——①W2 charge 残余 8 场逐抽（PM 连接面优先，1104 次序差次之）②W4 长尾 22 场分流聚类 ③W3 隐形抽值指纹。860 全绿后：夹具还原 914→--compare-only 全量账→README 重写→commit/push→超长场通道（54 场 --force --cases 逐场）。
- **★ PM 面定谳（本轮收尾）**：run1101 全 PM 事件对拍——oracle 首激活@3.35 且激活间隔 0.13s（高加速）；gd 首激活@6.63 间隔 0.5s（无加速）——**gd 的 PerpetuumMobile.onPrepare addSpeed(speed×getNumAffectedItems()) 未生效**（affected=Engineer 色邻接，gd 侧计数 0 或夹具 affected 空）。攻击点：PM.tscn tile_data 的 Engineer 色 tid→夹具 affected 键→getNumAffectedItems 链。1104 的 DjinnLamp 101@250 次序差疑似同源（PM 激活慢→全场冷却链慢）。
- **op17 分流**：39 红=fPbatch 对比全 REAL（0 HARVEST）。
- **★ checkTriggerCount 修复 ✅（np33 修复2，op18=834/860 净 +13 零退步）**：oracle 比较基准 Util.time 是**进程钟**（战斗开跑已累积装配耗时 ≈42s>fW3fin 实测），time>count(≤10) 恒真=**limit 恒不熔断**；gd ctx.time 战斗钟 0 起→前 10s 恒 false→永久熔断。修=+40s 偏移复刻（全场唯一调用者 MrStruggles 零全局风险）。翻绿 13 场：578/618/628/775/846/848/899/933/981/984/1487/1491/1507。REG np33ctc2 双腿 18/18。
- **账面**：**834/860**（26 红：947 三色/隐形抽族 733-1545 残余/W2 charge 1104+1163/W4 长尾 622-1022/基线红 1514）。
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