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
