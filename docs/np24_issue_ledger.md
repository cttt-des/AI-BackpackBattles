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

## 2. 当前状态与交接（2026-11-06 np47 接力落笔）

- **主账 859/860 挂起**：np46 净化重录（用户已批准，语料写授权生效）进行中——harness 逐案隔离已落地（[M13] 标记+确定性自证，§6m82-85），批量全量重录未走完（probe 名单六场+长场定向补录数场，其余 860 主夹具语料仍 Oct31 旧件）；录制工件键控面已退役入库（ea11bcfe），故键控依赖场（702/1022/977/1444/1120）对旧语料预期红，重录完成后预期自然闭合。
- **唯一出口** output/oracle/alignment.json（禁手写，只由 verify_oracle 产出）；54 长场独立账 output/oracle/long_alignment.json（工具 --report 有只记末场缺陷，逐场以 align_long/{gdcore,py}/<case>/events.json 产物+台账为准）；长场已翻绿 19 场（§6m87-105）。
- **接续序列**：①核键控清空完整性（含 OracleAlignBattleLong.gd 副本）→②np46 全量重录续跑（tools/_np46_rerecord.py，判据=批摘要 PASS）→③回补基线（verify_oracle --force，跑后 git checkout 夹具）→④860/860→⑤P4 收口（§6）→⑥54 长场剩余循环攻→⑦终局战报。
- **历史全文**：本文件被压缩的战报正文（2026-10-31~11-05 全部取证/证伪/探针细节）→ `git log -p docs/np24_issue_ledger.md`；探针材料 output/_round_patches/ 与 output/_offpeak/。

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

（以下 §4~§6m62 为已完结期的压缩存目：标题即结论，正文已压入 git 历史；现行期 §6m63 起全文保留。）

## 4. 红场分簇与新问题清单（208 场 25 簇 → 12 问题；=offpeak 任务书本体）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
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
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 5c. 超长场剔除通道（2026-10-31 傍晚，用户指令）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 5d. offpeak-06e4dc89 十二面定性战报（2026-10-31 晚）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6. 交付口径与收口

- 唯一出口 alignment.json（914 行、perCase 保序）；三方全对齐=914/914。
- **914/914 达成时收口**（P4 协议）：①全量 `--compare-only` 复读确认；②`r55`
  快照（alignment.json+语料目录 md5 清单落 output/_recovery/）；③本台账加收口节
  （最终基线/修复总账/遗留禁区）；④np24_fix.md 留档；⑤明确向用户声明。
- REG 九场任何一轮退步即回滚肇事 commit（铁律 8）。
- commit 格式 `np25修复X：…`；push 由主会话统一（用户指令）。
- 禁区：README.md（主控在途）、语料再写（需用户批准）、P1-1 收缩版（同）。

## 5e. offpeak-735ad54f 九签名族战报（2026-10-31 深夜）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 5f. np26 挖掘轮战报（2026-11-01 凌晨；账面 712→715/860）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 5g. np26 循环轮战报 I（2026-11-01；账面 715→733/860）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 5h. np26 循环轮战报 II（2026-11-01；账面 749/860，剩 111 真差）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 5i. np26 循环轮终态（2026-11-01；749/860 收束）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 5j. np26 EVENT 哨兵突破（2026-11-01 凌晨）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 5k. np27 charge 时序机方案定谳（2026-11-01）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6a. offpeak 最终任务书（860 全绿收口；2026-11-01 移交）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6b. offpeak-b16489cf 循环轮战报（2026-11-01；账面 749→752/860）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6c. 108 红完整攻击序（2026-11-01 发掘；752/860 基线）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6d. offpeak-db0c6696 循环轮战报 I（2026-11-01；W1 破案+13）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6e. 循环轮战报 II（2026-11-01；W1 刷账 766/860 + W3 破案）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6f. 循环轮战报 III（2026-11-01；W3 刷账 796/860 + 收割 809/860）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6h. 循环轮战报 V（2026-11-01；W3 修复2+隐形抽定位法）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6l2. 循环轮战报 IX 收官（2026-11-02 14:00；session 净 +25：809→834）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6k. 循环轮战报 VIII（2026-11-02；W2 正解入账 815/45）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6j. 循环轮战报 VII+下一棒任务书（2026-11-02；W2 正解落地，860 全绿冲刺交接）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6i. 循环轮战报 VI（2026-11-02；回滚链闭环，基线回归 809/51）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6g. 循环轮战报 IV（2026-11-01；W2 激活链证据链+方案，转攻 W3/W4）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m2. 循环轮战报 X（2026-11-02 晚；offpeak-0bfcfee4 接棒，838→841/860）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m3. np29fC 工具链升级 + 947 结构定谳（2026-11-02 深夜；继 §6m2）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m4. §6m3 补正：947 激活期 BOX/掷块交错序精测（2026-11-02 深夜 ii）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m5. 947 链位锁步定谳：冷却批/激活音效一抽错位（2026-11-02 深夜 iii；§6m3/6m4 的最终收窄）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m6. ★ 947 fd@6 根因破案+修复：autoRage pick_random 误用主链（2026-11-03；offpeak-70fcff69 接力）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m7. fd@46 深挖：ChessBoard 回合 4/5 捕获选择分叉（2026-11-03 ii；继 §6m6）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m8. 1441 步距指纹+值序对位：X 处裸抽/pitch 分解差（2026-11-03 iii；早簇通用攻击面）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m9. §6m8 修正+本会话收口（2026-11-03 iv）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m10. 1441 H 抽收窄至激活期单点（2026-11-03 v；本轮接力终态）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m11. §6m10 勘误：跨 run 状态关联无效，单 trace 内 H 证据仍稳固（2026-11-03 vi）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m12. ★ 1441 H 抽单 run 内复现+宿主锁定至「Ruby cd 非激活调用方」（2026-11-03 vii；本轮最终态）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m13. ★ 跨进程非确定性发现（2026-11-03 viii；本轮最终收口）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m14. H 分析的 pass 拼接真相+最终交接（2026-11-03 ix；本轮绝对收口）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m15. H 窗口相位最终确认（2026-11-03 x；交接完毕）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m16. H 宿主二选一收敛+pass 混叠定谳（2026-11-03 xi；本轮终）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m17. ★★ 1441 H 宿主最终锁定：Oil Lamp flicker 战斗期派发 v oracle 装配期（2026-11-03 xii）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m18. ★★ 1441 fd@18 根因全链闭环：flicker 延时抽装配链位差（2026-11-03 xiii；本轮绝对终态）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m19. flicker 延时值差异的分组定性（2026-11-03 xiv；接力最终抓手）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m20. FLKD 前置态捕获+取值约定新层（2026-11-03 xv；接力交接数据全量）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m21. FLKD 数据全量捕获+逆推结论（2026-11-03 xv；≤14:00 限时轮收口）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m22. ≤14:00 限时轮：配对搜索与派发时刻数学（2026-11-03 xvi；本轮收口）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m23. ★★ 换位对显形：gd flicker 早 1 笔 chanceRng（2026-11-03 xvii；≤14:00 轮真正收口）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m24. 构造计数审计+深度差来源域锁定（2026-11-03 xviii；13:50 轮终）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m25. 深度窗结构显形（2026-11-03 xix；≤14:00 轮终）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m26. ★ 1441 装配段全量地图+两窗 +4 差定位（2026-11-03 xx；13:50 轮收口）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m27. 装配期 CR 计数与最终假设空间（2026-11-03 xx；≤14:00 收口）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m28. ≤14:00 轮终：宝石抽深度分段差全谱（2026-11-03 xxi；收口）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m29. ≤14:00 轮终：oracle 装配 GEM 锚定 10/14+4 不连通（2026-11-03 xxii；13:50 收口）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m30. ★★ 装配链位定谳：WEB Dragon/The Lovers 实例化 CardConnector 漏扫（2026-11-03 xxiii；修复落库）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m31. ★ 1514 定谳：攻击尾 createAnimation+randomizePosition 3 笔隐形抽（2026-11-03 xxiv）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m32. 947@46 ChessBoard 哨兵定谳：分歧在 captureCells/canAffect 语义域（2026-11-03 xxv）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m33. 22:59 收口（2026-11-03 xxvi；限时轮终）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m34. 947@46 黑窗分叉解剖至最后一步（2026-11-04 早轮；09:15 收口）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m35. 9:30 收口（2026-11-04 早轮终）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m36. 947 黑窗破案 halfway：j 分叉=窗 2 前 1 步全局链差额（2026-11-04 晚轮）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m37. ★ 947 数学终审：gd 锚后多 1 步全局链（双点验证）（2026-11-04 晚轮二）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m38. 数学终审修订：oracle prepare 期 ≥8 步全局链 vs gd 1 步（2026-11-04 晚轮三；收口）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m39. ★ 947 翻绿：autoRage 误标修复（2026-11-04 晚轮四；852/860）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m40. 702 井破案 halfway：FB 双击 miss 路径缺 takeDamage 3 抽（2026-11-04 晚轮五）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m41. 702 终审：FB 双击 rollDA flip 序列差（2026-11-04 晚轮六）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m42. ★ 702 机制链全通：DK acc flip→盲池记账（2026-11-04 晚轮七）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m43. 702 终审补遗：盲池账 diff 方法+假警报排除（2026-11-04 晚轮八）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m44. ★★ 702 真根因：双方 DK 触发次序翻转（2026-11-04 晚轮九；终版）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m45. 702 收敛终态：同位 strike 的 acc 值差=非盲分量（2026-11-04 晚轮十）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m46. 702 终态定谳：DK strike 序列 K1 起分歧+盲池离线重放图纸（2026-11-04 晚轮十一；收口）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m47. 盲池账数据完备+acc 快照语义澄清（2026-11-04 晚轮十二；交接）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m48. ★ 702 直接上游锁定：LG blind gain 间隔 tick 序列分歧（2026-11-04 晚轮十三）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m49. 702 再收敛：节奏差早于 DK 首.advance→speed/cd 推进速率嫌疑（2026-11-04 晚轮十四）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m50. ★★ 702 终版机制链闭合：heat−cold 差 1→LG speed→全部分歧（2026-11-04 晚轮十五）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m50 附言：Cheese Goobert heat +1 的投递 tick 差=最后一环（同轮终笔）

- getHeat/getCold 逐字同构；heat 事件流（含 +6/+2/+2/+5/−1/+1/−1 全量）双侧逐位同——**池的输入输出全同**。但 [LGA] 实测 spd 差（heat−cold 2 v 1）⇒ **读数时刻的池状态不同** ⇒ 唯一可能=**1.4667 的 +1（Cheese Goobert heat）在两侧的生效 tick 不同**（oracle 事件戳 1.466667=池即刻入账 v gd 的 +1 实际入账晚 1+ tick——或反之）——**bus 派发/池入账的 tick 边界差**。
- **下轮第一针**：双侧 gainTemporary(type=107) 的 [BGAIN] print t 值对比（+1 池的创建时刻差）——[BGAIN] 已有（np29t 两轮 log 在盘）——离线比对 type=107 的池账即可，零新跑。
- 机制链完整：+1 入账 tick 差 → heat−cold 差 1 → LG getSpeed 差 → cd 节奏差 → 盲池 to 序差 → Crown 选择差 → 盲层差 → DK acc 差 → rng 位差 → timeout 错 u → idx1118/1119。**+1 入账差的最上游=Cheese Goobert 的 heal/heat 链触发时刻**（Cheese Goobert=受击回heat?——its trigger 链的 tick 边界）。

## 6m51. heat 衰减调用点未定位（下轮首查）（2026-11-04 晚轮末）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m52. ★★ 702 FD 根因链最终闭合：DK Amethyst removeRandomBuffs（2026-11-04 晚轮终）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m53. ★ 702 核心不对称：oracle removeRandomBuffs(388 pick 行) v gd 0 行（2026-11-04 晚轮十六）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m53 附言（收口移交）：探测资产与本段结论索引

- **本段（offpeak #156+会话接力）702 挖掘资产**：双侧 traced log（np29r/np29t 系列：ora8/gd6 含 [BGAIN]/[BCLEANSE] 池账、gd13 含 [LGA] 攻击入口、ora3/gd5 含 [ACC]/[ACCO] acc+blind+bonus 快照）全部在 output/_offpeak/np29t_702/ 与 np29r_702/ ——离线可复分析，零新跑。
- **已定谳结论链**：①u 级首真分歧=DK acc roll（gd acc=5 消耗 v oracle acc=−5 短路，[ACC] 实证）②acc 差=盲层差（非 buff 分量）③盲层差=盲池 to 序/构成差 ④盲池 gain 间隔 tick 序列双侧分歧（首间隔 75 v 64，钟无关法）⑤**oracle removeRandomBuffs=388 pickRandomElement 主链行 v gd 0 行**（核心不对称——两侧 heat −1 路径不同）。
- **下轮第一动作**：diff gd_core_items/Gems/Amethyst.gd 的 rollChance 触发（gd rollChance 恒 false 嫌疑→removeRandomBuffs 从未执行→heat −1 另路）——**Amethyst csv_chance 数据面核对**（battle_items.json Amethyst 的 chance 字段 v oracle ItemData.csv chance 列）→缺则补→REG→860。
- 探针：np29fT 的 LightGoobert [LGA] 已随本笔还原；其余（FLP/RDA/ACC/ACCO/RDAO/BGAIN/BCLEANSE/DKA）已在前轮还原。树净、镜像同步。

## 6m54. ★★★ 702 FD 真根因终定：1 层 lucky 差（2026-11-04 晚轮十七）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m55. 702 级联结构显形+矛盾点锁定（2026-11-04 晚轮十八；交接）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m55 附言（收口）：树状态与下轮开工清单

- **探针已全部还原**（FLP/RDA/ACC/ACCO/RDAO/DKA/LGA 零残留；oracle Buff.gd 的 [BGAIN]/[BCLEANSE]=原生诊断非探针）；镜像 md5 同步；工作树仅剩长期文件（README/docs/tools 12 项）。
- **下轮开工即可用资产**：双侧 traced log 全套在 output/_offpeak/np29t_702/（ora8 含 [BGAIN]/[BCLEANSE]/[BEXPIRE]/[ACCO] 池账+快照；gd6 含同款 gd 侧；gd13 含 [LGA]）——离线可复分析。
- **第一动作**：Twine 的 totalChance 对拍——getBaseChance()+getNumAffectedItems(Affected.Secondary)×getBaseChance2()：双侧打 Twine onTriggerItemActivated 针（totalChance/roll 值/activate 与否）→ 同批 4 roll 的成败序列对照 → Secondary 数差=修复点（isNeutral=classes==Neutral 数据面核对）。
- 账面 852/860；8 红：702@1118/921@452/977@497/986@206/1022@2456/1118@422/1120@868/1444@342。

## 6m56. ★★★ 702 翻绿（852→853）：FD@1118 真根因=玩家盲永久残差真值过期（np20 的 R=1 → 4）（2026-11-05 offpeak 接力）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m57. ★★★ 921 翻绿（853→854）：无敌延长分支 base 语义——oracle 的 Util.changeTimer 是 harness 补丁版，np25 注释丢了 ≥0 判别（2026-11-05 offpeak 接力）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m58. ★ run986_r12 第一层翻进（FD 206→271）：激活窗重启分支基准——gd 新计时器初值 0.0 误当「注册表 ≥0」，oracle 实为未注册哨兵 −1→回落引擎读数（2026-11-05 offpeak）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m59. ★★★ run1022_r18 翻绿（855→856）：PERM_STACK_OVERRIDE run1022 {109:6}→{109:1}——np20 同批过期推导第 2 笔定谳（§6m56 提示① 闭环）；附 oracle harness 火拍模型全标定（f64 时钟+f32 引擎量化）（2026-11-05 offpeak）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m60. ★ run1118_r18 翻绿（856→857）：rebuild_timer_registry 的物品计时器补锚——np25 timeout1t 的 CoreTimer 漏网面（§6l2 tick1diff 簇第 2 笔同族定谳）（2026-11-05 offpeak）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m61. ★ workflow 收口移交 offpeak（2026-11-05 13:54；按用户指令 13:50 收口停止写台账）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
## 6m62. 残红 3 场 FD 结构定谳+池账对拍方法论落地（2026-11-05 offpeak）
  - （正文已压缩入库前快照；本节结论见标题，全文可查 git 历史：`git log -p docs/np24_issue_ledger.md`。）
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

## 6m85. ★ np46 净化重录 Step 4：批量包装器 tools/_np46_rerecord.py 落地——全集入口/可续跑/全长闸/_batch_summary PASS 口径（2026-11-06 净化重录工程师 p4）

- **包装器落地（tools/_np46_rerecord.py，275 行）**：按原批量入口语义（tools/oracle_chunk_driver.py 同族：oracle/fights.json 全集 + ORACLE_FIGHT_CHUNK 单进程配额 + ORACLE_ONLY_CASES 分片 + tools/godot_headless 隐藏桌面/独立 APPDATA/文件重定向 + resume 幂等），差异四处：①ORACLE_FIGHTS_ROOT 默认 <repo>/output/oracle/fights（env 可重定向——全新重录推荐 ORACLE_FIGHTS_ROOT=<repo>/output/oracle/fights_np46 跑满后由主脚本原子换目录，resume 幂等只用于中断续跑不能充当重录开关）；②事件闸全长由 harness 内置（[M14] 200000/1200s），包装器 --check 硬校验 harness 净化标记（reset_residual_state + "> 200000"，缺失即拒绝开跑）；③前置安全检查：备份目录 output/oracle/fights_pre_npur_20261106 缺失即拒绝开跑（实测在位 916 项）；④收尾写 <fights_root>/_batch_summary.txt：status=PASS 仅当本轮范围（--cases 定向时=定向清单）全部 case_done（events.json 非空+rng_state.txt 在位，与 harness case_events_done 同判据）且分片 rc 全零；两轮无进展即停。
- **验证（全部本轮实测）**：①py_compile 过；②--check：备份在位+harness 标记 OK+914 场（fights.json 实数；任务书 917 系口径差）+pending=0（现有语料 resume 视角全done）+不写 summary（防污染真实 PASS 口径）；③定向实跑冒烟（scratch 根 output/_offpeak/np46/wrapper_smoke，语料零触碰）：--cases run570_r18 → rc=0/PASS/548 事件 ≡ 冻结语料逐事件全等；--cases run570_r18,run894_r18 → PASS/2/2/pending=0，894 经 wrapper 全长 48297 事件 ≡ 冻结语料逐事件全等（wrapper 产物确定性双证）；④resume 幂等：同定向第二次实跑 wall=0s 直接 PASS（case_done 跳过生效）。
- **移交给主脚本的批量面**：`python -X utf8 tools/_np46_rerecord.py [chunk=60] [rounds=12] [jobs=0自动≤4]`——批量录制由主脚本统一跑（本工作流只做单例验证，per ask）；全新重录建议 ORACLE_FIGHTS_ROOT 指向新目录（主脚本原子换目录+备份已在位）；harness 每进程自带暖场+adjacent/批尾确定性自证，_progress.txt/_batch_summary.txt 双落盘。
- **边界与注记**：①fights.json 全集=914 场（预检剔除机制对不可解码场如实写 _preflight_dropped.txt，现网 0）；②wrapper 不做语料删除/换目录（语料生命周期归主脚本）；③_[M11] MessageQueue 配额退出语义沿用（chunk=60 默认）；④本步零 harness/引擎/夹具改动，工作树红线（verify_oracle.py/OracleAlignBattle.gd/主夹具）git diff 空。

## 6m86. ★ np46 净化重录后主线收口：批量假 PASS 实锤（908/914 语料未重录）+键控退役悬空未提交+860 快速腿账面未刷新（986 仍红）——P4 全绿收口暂缓（2026-11-06 收口员）

- **收口判读（主脚本）**：净化重录 Step1-4（§6m82-85，commit 35c493d9→950213cf）批量移交后，主线 860 快速腿未能全绿——账面 output/oracle/alignment.json（mtime 2026-11-05 21:59:19，本轮 stat 实测，早于 08:14 的 986 重录收割）仍 total=860/aligned=859，唯一红=run986_r12（oracle≠gdcore：oracleEv 4225=旧语料 vs gd/py 3937、winner oracle=opponent vs gd/py=player、FD@287=§6m75-era 旧红原样）→ 986 循环未翻绿，**P4 全绿收口不执行，转阶段收口**。README 不动、无快照、无全绿声明。
- **本工作流轮次实录（Step-4 提交 08:36 之后→09:38，产物在案本轮亲验）**：
  - **R0 批量假 PASS（08:37:43）**：按 §6m85 移交语义跑 tools/_np46_rerecord.py 全集 → output/oracle/fights/_batch_summary.txt：status=PASS、scope_done=914/914、pending=0、**wall_seconds=10**；语料 events.json mtime 普查（本轮实测 914 场全集）：10-31=850/11-01=55/11-02=3/**11-06=6**（np45 五长场 04:03-04:35+run986_r12 08:14）→ **908/914 未重录，「全集重录」实为 resume 假 PASS**。
  - **R1 spot3 零键控定向 3 场（08:50-08:52；红=基建缺口非对齐定谳）**：986/1120/1444 双腿 verify → gd 腿并行 spawn 崩溃 **AttributeError: module 'godot_headless' has no attribute 'py_popen'**（output/_offpeak/np46/spot3_gd.log 调用栈=verify_oracle.py:888 _spawn_workers←:922 run_godot_parallel←:1008←:1579）；退 --compare-only → **0/3 全「py 缺产物」**（spot3_cmp.log+alignment_np46_keyoff_spot.json total=3 aligned=0）；spot3_gdpair.log：986 ALL-GREEN（oracle=gd=4259）、1120/1444=RED 且 window_a=None（与 compare-only「py 缺产物」同源）。
  - **R2 假门实锤→完成度门修正（未提交）**：根因=wrapper case_done() 只查 events.json+rng_state.txt（旧语料双件俱全即被 resume 视为已完成）；修正（tools/_np46_rerecord.py 工作树 diff，其代码注已引「台账 §6m86」=本节序）：加查 result.txt 带 **[M13] 净化 harness 标记**；run986_r12/result.txt 实测含 [M13]（grep=1）→ 修正后 resume 视角待重录=908~913（986 在档带标记；np45 五长场是否带标记未逐一核）。
  - **R3 986 单例零键控双腿复证（09:37）**：**三方一致 1/1**（output/_offpeak/wf986/align_r1000.json：4259/4259/4259、winner=player×3、firstDivergence=null、judgement 事件+渲染双真）；gd 日志 output/_recovery/godot_logs/gd_r0_6016_1.log「PASS（实跑 1 场）+selfcheck 同种子复跑逐字节一致」；py 产物 output/oracle/align/py/run986_r12/events.json（09:37）→ **986 新语料+零键控闭合跨工作流复现成立**（§6m84 同判，两轮独立）。
  - **R4 13 场定向 wf986p20（09:38；三方对齐未定谳）**：gd 腿 13/13 ok+run1029_r2 selfcheck 字节一致 17.7s（output/oracle/align/wf986p20_gd/_align_gd_summary.txt；gd_r0_19200_1.log）；py 产物 13 目录已写（wf986p20_py）；**13 场 compare/账面写盘未发现**（今日新增 alignment*.json 仅 R1 两个 _offpeak 文件，find 实测）；键控退役幸存场 run1022/906/1125/1409 不在 13 清单内。
  - **全量腿未跑成**：860 账面零刷新（alignment.json mtime 未动）；output/oracle/align/gdcore/ 已清至仅存 run986_r12（09:37）+_np18_permwarm（11-05 22:09 遗留）→ 清场后全量重跑未发生/未完成。
- **假设与已排除分支**：①「批量已按 §6m85 完成全集重录」→排除（wall=10+mtime 普查 908 场停 10-31~11-02）；②「986 新语料/零键控对齐翻红」→排除（R3 三方一致+R1 gdpair ALL-GREEN）；③「spot3 的 1120/1444 红=对齐红」→排除（=py 缺产物崩溃连带，非对齐判据）；④「键控退役即可全绿」→现状不成立（退役前提「语料=全量重录干净形状」仅 6/914 成立）；⑤「完成度门洞」→已修未提交（[M13] 门）。**悬空（下一轮先修面）**：verify_oracle.py 三处 spawn 调用（:888/:1054/:1185）引用不存在的 godot_headless.py_popen——本轮实测 hasattr(godot_headless,'py_popen')=False、tools/godot_headless.py（mtime 07:25 后未动，全树唯一副本）确无此函数 → verify 全量 orchestration 走该路径必复崩（R1 已实证）；R3/R4 产物在案但发起命令未留痕（入口路径未定谳）。
- **工作树红线悬置（Step-4 后落地、守门前不入库）**：§6m85 时点（08:36）红线 diff 空（台账在案）；现工作树三文件：①gd_core_test/OracleAlignBattle.gd——六键控表清空（WARM_LATCH_PLAYERS/PERM_STACK_HARVEST/PERM_STACK_OVERRIDE/WARMUP_TIME_TICKS/BUFF_STOP_CLEARS_SEEN/CLEANSE_BIGGEST_FIRST）+NP22_REC_EV_GATE 再生 20→10 场（新语料 event_count>25000 实测分布）；②tools/verify_oracle.py——py 镜像七表同批清空（含 PY_R5_DUAL_EXEC 三键）+PY_NP22_REC_EV_GATE 同步再生；③tools/_np46_rerecord.py——case_done [M13] 门。
- **下一轮唯一闭合路径（顺序硬约束）**：①先修 spawn 面 py_popen 缺口（或直驱入口绕开 verify orchestration）；②跑真全集重录（[M13] 门生效后 pending 908~913；ORACLE_FIGHTS_ROOT 原子换目录语义 §6m85）；③红线三文件以 860 全量对拍守门后入库；④账面刷新判定全绿→P4。本轮收口：零语料写入、零引擎/夹具改动、账面零触碰；本节+收口 commit 为全部产出。

## 6m87. ★ np45 长场 run894_r18：净化重录后首次双腿对拍直接翻绿（全库最大长场 48297 事件，零改动零假设）（2026-11-06 长场修复 run894_r18 p1）

- **结论**：run894_r18（48297 事件，54 场长场中最大 18.4MB）净化重录后首度对拍即三方一致 1/1——语料=gd_core=gd_core_py 全 48297 事件、winner=player×3、firstDivergence=null（output/oracle/long_alignment.json total=1 aligned=1，独立账面未并入 alignment.json）。零代码/零引擎/零夹具改动，无分歧故无 prefix 迭代假设史（全量定谳覆盖全长，判据「前移/同位/后移」本轮不适用）。
- **判据与实测（本轮亲跑）**：①`python -X utf8 tools/long_case_fix.py --focus run894_r18`：gd 腿 rc=0（21s，ticks=4147 t=66.60 ev=48297）+「[selfcheck] run894_r18 同种子复跑逐字节一致」+PASS（实跑 1 场，跳过 0）；py 腿 8s 完成（_LongContext 注入夹具内联 py_ev_gate=57957 生效，48297 未触默认闸 25000——坑 2 当场核验）；V.compare_case 判「三方一致」，事件数 48297/48297/48297。②双验：gd 产物 output/oracle/align_long/gdcore/run894_r18/events.json=19,614,577 字节（>1KB 非空，py 腿 13,493,007 字节同在）；focus gd 日志 output/_recovery/godot_logs/focus_gd_focus_8048_1.log `grep -c "SCRIPT ERROR"` 零命中（rc=1，仅既有引擎退出噪声 ~List/ObjectDB/Resources）。③`python -X utf8 tools/long_case_fix.py --prefix run894_r18` 首轮全量定位分支走「已三方一致，无需迭代」exit=0（工具对绿场不记 progress.json，账本保持无本场记录）。
- **本场假设史（旧分歧记录作废口径）**：np45 首轮该场属「未验证覆盖空洞」（guide §10：54 场当时仅 run906 深挖过）；旧「语料截断收割」簇（§6m77-81 五场）对本场不适用——语料 output/oracle/fights/run894_r18/events.json 为 Oct 31 12:28 冻结件、本身即自然终局全长 48297（本轮 stat 复核 mtime 未动），净化重录 smoke（§6m85 ③）已证 wrapper 全长产物 ≡ 冻结语料逐事件全等故语料文件无需重写；本轮为净化 harness 语义下该场首度 py 腿对拍与三方定谳，无新假设被排除。
- **边界**：长场产物/报告均在 output/（.gitignore 内）不入库，本节为唯一入库产出；红线三文件（tools/verify_oracle.py、gd_core_test/OracleAlignBattle.gd 的 §6m86 键控退役悬空 diff + tools/_np46_rerecord.py 的 [M13] 门）本轮零触碰零并入，仍归 §6m86「下一轮唯一闭合路径」管；主夹具 860 场与主账 alignment.json 未动。

## 6m88. ★ np45 长场 run1408_r18：净化重录后首度双腿对拍直接翻绿（40827 事件，零改动零假设）（2026-11-06 长场修复 run1408_r18 p1）

- **结论**：run1408_r18（40827 事件，超默认闸 25000 的 9 场之一）净化重录（Nov 6 04:12 件）后首度对拍即三方一致 1/1——语料=gd_core=gd_core_py 全 40827 事件、winner=opponent×3、firstDivergence=null、judgement 事件+渲染双真（output/oracle/long_alignment.json total=1 aligned=1 独立账面，未并入 alignment.json）。零代码/零引擎/零夹具改动，无分歧故无 prefix 迭代假设史（全量定谳覆盖全长）。
- **判据与实测（本轮亲跑）**：①夹具 output/oracle/align_long/long_cases_fixture.json 本场 py_ev_gate=48993 内联在案（重录后 09:56 重生成），40827 未触默认闸 25000——坑 2 当场核验；语料 16533007 字节 mtime 04:12 本轮零写入。②`python -X utf8 tools/long_case_fix.py --focus run1408_r18`：gd 腿 rc=0（18s，ticks=3572 t=57.02 ev=40827，8145ms）+「[selfcheck] 同种子复跑逐字节一致」+PASS（实跑 1 场，跳过 0）；py 腿 6s 完成；V.compare_case 判「三方一致」40827/40827/40827。③双验：gd 产物 output/oracle/align_long/gdcore/run1408_r18/events.json=16,833,312 字节+py 腿 11,620,759 字节（均 >1KB）；focus 日志 output/_recovery/godot_logs/focus_gd_focus_14048_1.log 与 prefix 日志 prefix_gd_pfx_8424_1.log `grep -c "SCRIPT ERROR"` 均 0 命中（rc=1，仅既有 JoypadWindows 引擎噪声）。④`--prefix run1408_r18` 首轮全量定位分支：gd 腿 resume 跳过 1（复用 focus 新鲜产物，幂等合法）→「已三方一致，无需迭代」exit=0；工具对绿场不记 progress.json。
- **本场假设史（旧分歧记录作废口径）**：本场属「未验证（净化重录后无分歧数据）」簇，本轮为净化 harness 语义下首度 py 腿对拍与三方定谳；无新假设被排除、无改动故无回滚面。继 §6m87（run894_r18）之后连续第二场「净化重录后零改动直接翻绿」，佐证净化重录对长场簇的净化有效性。
- **边界**：长场产物/报告均在 output/（.gitignore 内）不入库，本节为唯一入库产出；红线三文件 §6m86 悬置 diff（OracleAlignBattle.gd 键控退役/verify_oracle.py py 镜像七表/_np46_rerecord.py [M13] 门）本轮零触碰零并入；主夹具 860 场与主账 alignment.json 未动。

## 6m89. ★ np45 长场 run1342_r18：净化重录后首度双腿对拍直接翻绿（38989 事件，零改动零假设）（2026-11-06 长场修复 run1342_r18 p1）

- **结论**：run1342_r18（38989 事件，超默认闸 25000 的 9 场之一）净化重录（Nov 6 04:21 件，15635068 字节）后首度对拍即三方一致 1/1——语料=gd_core=gd_core_py 全 38989 事件、firstDivergence=null（output/oracle/long_alignment.json total=1 aligned=1 独立账面，未并入 alignment.json）。零代码/零引擎/零夹具改动，无分歧故无 prefix 迭代假设史（全量定谳覆盖全长）。
- **判据与实测（本轮亲跑）**：①夹具 output/oracle/align_long/long_cases_fixture.json 本场 py_ev_gate=46787 内联在案，38989 未触默认闸 25000——坑 2 当场核验；语料 15635068 字节 mtime 04:21 本轮零写入。②`python -X utf8 tools/long_case_fix.py --focus run1342_r18`：gd 腿 rc=0（17s，ticks=3243 t=51.53 ev=38989，7571ms）+「[selfcheck] 同种子复跑逐字节一致」+PASS（实跑 1 场，跳过 0）；py 腿 6s 完成；V.compare_case 判「三方一致」38989/38989/38989。③双验：gd 产物 output/oracle/align_long/gdcore/run1342_r18/events.json=16,125,589 字节+py 腿 10,808,803 字节（均 >1KB）；focus 日志 output/_recovery/godot_logs/focus_gd_focus_5692_1.log 与 prefix 日志 prefix_gd_pfx_2868_1.log `grep -c "SCRIPT ERROR"` 均 0 命中（rc=1，仅既有 JoypadWindows 引擎噪声）。④`--prefix run1342_r18` 首轮全量定位分支：gd 腿 resume 复用 focus 新鲜产物（幂等合法）→「已三方一致，无需迭代」exit=0；工具对绿场不记 progress.json（本轮该文件仍不存在）。
- **本场假设史（旧分歧记录作废口径）**：本场属「未验证（净化重录后无分歧数据）」簇，本轮为净化 harness 语义下首度 py 腿对拍与三方定谳；无新假设被排除、无改动故无回滚面。继 §6m87（run894_r18）/§6m88（run1408_r18）之后连续第三场「净化重录后零改动直接翻绿」，进一步佐证净化重录对长场簇的净化有效性。
- **边界**：长场产物/报告均在 output/（.gitignore 内）不入库，本节为唯一入库产出；红线三文件 §6m86 悬置 diff（OracleAlignBattle.gd 键控退役/verify_oracle.py py 镜像七表/_np46_rerecord.py [M13] 门）本轮零触碰零并入；主夹具 860 场与主账 alignment.json 未动。

## 6m90. ★ np45 长场 run1374_r18：净化重录后首度对拍直接翻绿（37968事件，连续第四场零改动翻绿§6m90同形）（2026-11-06 长场修复 run1374_r18 p1）

- **结论**：run1374_r18（37968 事件，超默认闸 25000 的 9 场之一；guide §4 旧表记 37068 为净化重录前口径，重录件实测 37968 与情报一致）净化重录（Nov 6 04:03 件，15184757 字节）后首度对拍即三方一致 1/1——语料=gd_core=gd_core_py 全 37968 事件、winner=player×3、firstDivergence=null、judgement 事件+渲染双真（output/oracle/long_alignment.json total=1 aligned=1 独立账面，未并入 alignment.json）。零代码/零引擎/零夹具改动，无分歧故无 prefix 迭代假设史（全量定谳覆盖全长）。
- **判据与实测（本轮亲跑）**：①夹具 output/oracle/align_long/long_cases_fixture.json 本场 py_ev_gate=45562 内联在案（=int(37968×1.2+1)），37968 未触默认闸 25000——坑 2 当场核验；语料 15184757 字节 mtime 04:03 本轮零写入。②`python -X utf8 tools/long_case_fix.py --focus run1374_r18`：gd 腿 rc=0（17s，ticks=2844 t=44.88 ev=37968，7612ms）+「[selfcheck] run1374_r18 同种子复跑逐字节一致」+PASS（实跑 1 场，跳过 0）；py 腿 6s 完成（_LongContext 注入夹具内联闸生效）；判「三方一致」37968/37968/37968。③双验：gd 产物 output/oracle/align_long/gdcore/run1374_r18/events.json=15,649,546 字节+py 腿 10,476,875 字节（均 >1KB）；focus 日志 output/_recovery/godot_logs/focus_gd_focus_4248_1.log 与 prefix 日志 prefix_gd_pfx_15412_1.log 经 python str.count 核验「SCRIPT ERROR」均 0 命中（本轮 Git Bash 管道下 grep -c 输出被吞，改用 python 计数，两日志仅 1350/756 字节且尾部仅既有 JoypadWindows/List/ObjectDB/Resources 引擎退出噪声）。④`--prefix run1374_r18` 首轮全量定位分支：gd 腿 resume 复用 focus 新鲜产物（3s，幂等合法）→「已三方一致，无需迭代」exit=0；工具对绿场不记 progress.json。
- **本场假设史（旧分歧记录作废口径）**：本场属「未验证（净化重录后无分歧数据）」簇，本轮为净化 harness 语义下首度 py 腿对拍与三方定谳；无新假设被排除、无改动故无回滚面。继 §6m87（run894_r18）/§6m88（run1408_r18）/§6m89（run1342_r18）之后连续第四场「净化重录后零改动直接翻绿」，进一步佐证净化重录对长场簇的净化有效性。
- **边界**：长场产物/报告均在 output/（.gitignore 内）不入库，本节为唯一入库产出；红线三文件 §6m86 悬置 diff 本轮零触碰零并入；主夹具 860 场与主账 alignment.json 未动。

## 6m91. ★ np45 长场 run905_r18：净化重录后首度对拍直接翻绿（33819事件，连续第五场零改动翻绿§6m91同形）（2026-11-06 长场修复 run905_r18 p1）

- **结论**：run905_r18（33819 事件，超默认闸 25000 的 9 场之一，guide §4 旧表同记 33819 与情报一致）净化重录（Oct 31 12:27 冻结件，13821308 字节，即 §6m87 run894_r18 同款「Oct31冻结件=自然终局全长未截断」情形）后首度对拍即三方一致 1/1——语料=gd_core=gd_core_py 全 33819 事件、winner=player×3、firstDivergence=null、judgement 事件+渲染双真（output/oracle/long_alignment.json total=1 aligned=1 独立账面，未并入 alignment.json）。零代码/零引擎/零夹具改动，无分歧故无 prefix 迭代假设史（全量定谳覆盖全长）。
- **判据与实测（本轮亲跑）**：①夹具 output/oracle/align_long/long_cases_fixture.json 本场 py_ev_gate=40583 内联在案（=int(33819×1.2+1)），33819 未触默认闸 25000——坑 2 当场核验；语料 13821308 字节 mtime 2026-10-31 12:27:18 本轮零写入。②`python -X utf8 tools/long_case_fix.py --focus run905_r18`：gd 腿 rc=0（17s，ticks=3452 t=55.02 ev=33819，7339ms）+「[selfcheck] run905_r18 同种子复跑逐字节一致」+PASS（实跑 1 场，跳过 0）；py 腿 6s 完成（_LongContext 注入夹具内联闸生效）；判「三方一致」33819/33819/33819。③双验：gd 产物 output/oracle/align_long/gdcore/run905_r18/events.json=13,993,265 字节+py 腿 9,673,378 字节（均 >1KB）；focus 日志 output/_recovery/godot_logs/focus_gd_focus_16424_1.log（10:22:46）与 prefix 日志 prefix_gd_pfx_5548_1.log（10:23:21）经 python str.count 核验「SCRIPT ERROR」均 0 命中（沿用 §6m90 python 计数口径，两日志仅 1168/609 字节且尾部仅既有 JoypadWindows 引擎退出噪声）。④`--prefix run905_r18` 首轮全量定位分支：gd 腿 resume 复用 focus 新鲜产物（2s，幂等合法）→「已三方一致，无需迭代」exit=0；工具对绿场不记 progress.json。
- **本场假设史（旧分歧记录作废口径）**：本场属「未验证（净化重录后无分歧数据）」簇，本轮为净化 harness 语义下首度 py 腿对拍与三方定谳；无新假设被排除、无改动故无回滚面。继 §6m87（run894_r18）/§6m88（run1408_r18）/§6m89（run1342_r18）/§6m90（run1374_r18）之后连续第五场「净化重录后零改动直接翻绿」，进一步佐证净化重录对长场簇的净化有效性。
- **边界**：长场产物/报告均在 output/（.gitignore 内）不入库，本节为唯一入库产出；红线三文件 §6m86 悬置 diff（verify_oracle.py 34/28、OracleAlignBattle.gd 25/44 本轮 diff --numstat 零新增行）零触碰零并入；主夹具 860 场与主账 alignment.json 未动。

## 6m92. ★ np45 长场 run906_r18：净化重录后首度对拍直接翻绿（30538事件，连续第六场零改动翻绿§6m92同形）（2026-11-06 长场修复 run906_r18 p1）

- **结论**：run906_r18（30538 事件，超默认闸 25000 的 9 场之一，guide §4 旧表同记 30538 与情报一致）净化重录（Oct 31 12:32 冻结件，12593193 字节，即 §6m91 run905_r18 同款「Oct31冻结件=自然终局全长未截断」情形，event_count=30538 与 len(events) 自洽）后首度对拍即三方一致 1/1——语料=gd_core=gd_core_py 全 30538 事件、winner=player×3、firstDivergence=null、judgement 事件+渲染双真（output/oracle/long_alignment.json total=1 aligned=1 独立账面，未并入 alignment.json）。零代码/零引擎/零夹具改动，无分歧故无 prefix 迭代假设史（全量定谳覆盖全长）。
- **判据与实测（本轮亲跑）**：①夹具 output/oracle/align_long/long_cases_fixture.json 本场 py_ev_gate=36646 内联在案（=int(30538×1.2+1)），30538 未触默认闸 25000——坑 2 当场核验；语料 12593193 字节 mtime 2026-10-31 12:32:34 本轮零写入。②`python -X utf8 tools/long_case_fix.py --prefix run906_r18` 首轮全量定位分支：gd 腿 rc=0（16s）全量跑入 gdcore/，compare idx=None「无事件级分歧」；该轮 py 产物缺位系 prefix 首轮只跑 gd 腿的既定行为（long_case_fix.py prefix 分支无 py 腿），非长度型真分歧，随后由 focus 定谳。③`python -X utf8 tools/long_case_fix.py --focus run906_r18 --force`（单场级删除重跑，force 范围仅本场产物目录）：gd 腿 rc=0（16s，ticks=3437 t=54.77 ev=30538，6905ms）+「[selfcheck] run906_r18 同种子复跑逐字节一致」+PASS（实跑 1 场，跳过 0）；py 腿 6s 完成（_LongContext 注入夹具内联闸生效）；判「三方一致」30538/30538/30538。④双验：gd 产物 output/oracle/align_long/gdcore/run906_r18/events.json=12,743,786 字节+py 腿 8,732,499 字节（均 >1KB）；本轮三份 gd 日志 prefix_gd_pfx_11084_1.log（10:27）/focus_gd_focus_18920_1.log（10:28，resume 跳过场）/focus_gd_focus_14296_1.log（10:29，force 实跑）经 python str.count 核验「SCRIPT ERROR」均 0 命中（沿用 §6m90 python 计数口径，仅既有 JoypadWindows 引擎退出噪声）。工具对绿场不记 progress.json（该文件仍不存在）。
- **本场假设史（旧分歧记录作废口径）**：本场属「未验证（净化重录后无分歧数据）」簇（guide §10 旧口径「py 分歧 idx=6 荷包蛋圣锅」系 11-05 旧语料时代记录，本轮作废——新语料下无任何分歧，guide §10 所记旧分歧未复现）；align_long/prefix/run906_r18/ 下 11-05 旧前缀残留（3810 字节）未当证据，本轮 prefix 全量走 gdcore/ 目录未触碰该残留。无新假设被排除、无改动故无回滚面。继 §6m87（run894_r18）/§6m88（run1408_r18）/§6m89（run1342_r18）/§6m90（run1374_r18）/§6m91（run905_r18）之后连续第六场「净化重录后零改动直接翻绿」，进一步佐证净化重录对长场簇的净化有效性。
- **边界**：长场产物/报告均在 output/（.gitignore 内）不入库，本节为唯一入库产出；红线三文件 §6m86 悬置 diff（verify_oracle.py 34/28、OracleAlignBattle.gd 25/44 本轮 diff --numstat 零新增行）零触碰零并入；主夹具 860 场与主账 alignment.json 未动。

## 6m93. ★ np45 长场 run696_r18：净化重录后首度对拍直接翻绿（28977事件，连续第七场零改动翻绿§6m93同形）（2026-11-06 长场修复 run696_r18 p1）

- **结论**：run696_r18（28977 事件，超默认闸 25000 的 9 场之一，guide §4 旧表同记 28977 与情报一致）净化重录后首度对拍即三方一致 1/1——语料=gd_core=gd_core_py 全 28977 事件、winner=opponent×3、firstDivergence=null、judgement 事件元组+渲染双真（output/oracle/long_alignment.json total=1 aligned=1 独立账面，未并入 alignment.json）。零代码/零引擎/零夹具改动，无分歧故无 prefix 迭代假设史（全量定谳覆盖全长）。
- **判据与实测（本轮亲跑）**：①夹具 output/oracle/align_long/long_cases_fixture.json 本场 py_ev_gate=34773 内联在案（=int(28977×1.2+1)，与情报一致），28977 未触默认闸 25000——坑 2 当场核验；语料 11687186 字节 mtime 2026-10-31 12:07:45 冻结件（§6m91/6m92 同款「Oct31冻结件=自然终局全长未截断」情形，event_count=28977=len(events) 自洽，末事件 type=112 @t=66.016667=combat_time 自然终局）本轮零写入。②`python -X utf8 tools/long_case_fix.py --focus run696_r18`（情报指定先 focus 定谳）：gd 腿 rc=0（14s，ticks=4112 t=66.02 ev=28977，6365ms）+「[selfcheck] run696_r18 同种子复跑逐字节一致」+PASS（实跑 1 场，跳过 0）；py 腿 5s 完成（_LongContext 注入夹具内联闸生效）；判「三方一致」28977/28977/28977。语料元数据 ticks=3961 与 gd/py 产物 ticks=4112 系两侧计数口径不同（combat_time 66.016667 双侧一致、事件流 28977 全等，判据为事件级比较不受影响）。③`python -X utf8 tools/long_case_fix.py --prefix run696_r18` 首轮全量定位分支：账本无记录→gd 腿 resume 复用 focus 新鲜产物（2s，rc=0，幂等合法）→「已三方一致，无需迭代」exit=0。④双验：gd 产物 output/oracle/align_long/gdcore/run696_r18/events.json=11,946,449 字节+py 腿 7,982,198 字节（均 >1KB）；本轮三份 gd 日志 focus_gd_focus_5216_1.log（10:31:40，610B）/focus_gd_focus_6236_1.log（10:33:23，1166B）/prefix_gd_pfx_9892_1.log（10:33:58，609B）经 python str.count 核验「SCRIPT ERROR」均 0 命中（沿用 §6m90 python 计数口径，尾部仅既有 JoypadWindows/DirectInput 引擎退出噪声）。工具对绿场不记 progress.json（该文件仍不存在）。
- **本场假设史（旧分歧记录作废口径）**：本场属「未验证（净化重录后无分歧数据）」簇，本轮为净化 harness 语义下首度 py 腿对拍与三方定谳；无新假设被排除、无改动故无回滚面。继 §6m87（run894_r18）/§6m88（run1408_r18）/§6m89（run1342_r18）/§6m90（run1374_r18）/§6m91（run905_r18）/§6m92（run906_r18）之后连续第七场「净化重录后零改动直接翻绿」，进一步佐证净化重录对长场簇的净化有效性。
- **边界**：长场产物/报告均在 output/（.gitignore 内）不入库，本节为唯一入库产出；红线三文件 §6m86 悬置 diff（verify_oracle.py 34/28、OracleAlignBattle.gd 25/44 本轮 diff --numstat 零新增行）零触碰零并入；主夹具 860 场与主账 alignment.json 未动。

## 6m94. ★ np45 长场 run685_r18：净化重录后首度对拍直接翻绿（28295事件，连续第八场零改动翻绿§6m94同形）（2026-11-06 长场修复 run685_r18 p1）

- **结论**：run685_r18（28295 事件，超默认闸 25000 的 9 场之一，guide §4 旧表同记 28295 与情报一致）净化重录后首度对拍即三方一致 1/1——语料=gd_core=gd_core_py 全 28295 事件、winner=opponent×3、firstDivergence=null、judgement 事件元组+渲染双真（output/oracle/long_alignment.json total=1 aligned=1 独立账面，未并入 alignment.json）。零代码/零引擎/零夹具改动，无分歧故无 prefix 迭代假设史（全量定谳覆盖全长）。
- **判据与实测（本轮亲跑）**：①夹具 output/oracle/align_long/long_cases_fixture.json 本场 py_ev_gate=33955 内联在案（=int(28295×1.2+1)，与情报一致），28295 未触默认闸 25000——坑 2 当场核验；语料 11548539 字节 mtime 2026-10-31 12:08:01 冻结件（§6m93 run696_r18 同款「Oct31冻结件=自然终局全长未截断」情形，event_count=28295=len(events) 自洽，末事件 type=112 @t=48.133333=combat_time 自然终局）本轮零写入。②`python -X utf8 tools/long_case_fix.py --focus run685_r18`（情报指定先 focus 定谳）：gd 腿 rc=0（14s，ticks=3039 t=48.13 ev=28295，6164ms）+「[selfcheck] run685_r18 同种子复跑逐字节一致」+PASS（实跑 1 场，跳过 0）；py 腿 5s 完成（_LongContext 注入夹具内联闸生效）；判「三方一致」28295/28295/28295。③`python -X utf8 tools/long_case_fix.py --prefix run685_r18` 首轮全量定位分支：账本无记录→gd 腿 resume 复用 focus 新鲜产物（2s，rc=0，幂等合法）→「已三方一致，无需迭代」exit=0。④双验：gd 产物 output/oracle/align_long/gdcore/run685_r18/events.json=11,685,750 字节+py 腿 7,954,919 字节（均 >1KB，len(events)=28295、winner=opponent 双侧自洽）；本轮四份 gd 日志 focus_gd_focus_3088_1.log（610B）/focus_gd_focus_8980_1.log（1166B，force 实跑）/prefix_gd_pfx_9892_1.log（609B）/prefix_gd_pfx_11060_1.log（611B）经 python str.count 核验「SCRIPT ERROR」均 0 命中（沿用 §6m90 python 计数口径，尾部仅既有 JoypadWindows/DirectInput 引擎退出噪声）。工具对绿场不记 progress.json（该文件仍不存在）。
- **本场假设史（旧分歧记录作废口径）**：本场属「未验证（净化重录后无分歧数据）」簇，本轮为净化 harness 语义下首度 py 腿对拍与三方定谳；无新假设被排除、无改动故无回滚面。继 §6m87（run894_r18）/§6m88（run1408_r18）/§6m89（run1342_r18）/§6m90（run1374_r18）/§6m91（run905_r18）/§6m92（run906_r18）/§6m93（run696_r18）之后连续第八场「净化重录后零改动直接翻绿」，进一步佐证净化重录对长场簇的净化有效性。
- **边界**：长场产物/报告均在 output/（.gitignore 内）不入库，本节为唯一入库产出；红线三文件 §6m86 悬置 diff（verify_oracle.py 34/28、OracleAlignBattle.gd 25/44 本轮 diff --numstat 零新增行）零触碰零并入；主夹具 860 场与主账 alignment.json 未动。

## 6m95. ★ np45 长场 run845_r18：净化重录后首度对拍直接翻绿（27626事件，连续第九场零改动翻绿§6m95同形）（2026-11-06 长场修复 run845_r18 p1）

- **结论**：run845_r18（27626 事件，超默认闸 25000 的 9 场之一，guide §4 旧表同记 27626 与情报一致）净化重录后首度对拍即三方一致 1/1——语料=gd_core=gd_core_py 全 27626 事件、winner=opponent×3、firstDivergence=null、judgement 事件 type=112@t=68.016667+渲染双真（output/oracle/long_alignment.json total=1 aligned=1 独立账面，未并入 alignment.json）。零代码/零引擎/零夹具改动，无分歧故无 prefix 迭代假设史（全量定谳覆盖全长）。
- **判据与实测（本轮亲跑）**：①夹具 output/oracle/align_long/long_cases_fixture.json 本场 py_ev_gate=33152 内联在案（=int(27626×1.2+1)，与情报一致），27626 未触默认闸 25000——坑 2 当场核验；语料 11395684 字节 mtime 2026-10-31 12:25:38 冻结件（§6m93/6m94 同款「Oct31冻结件=自然终局全长未截断」情形，event_count=27626=len(events) 自洽，末事件 type=112 @t=68.016667=combat_time 自然终局）本轮零写入。②`python -X utf8 tools/long_case_fix.py --focus run845_r18`（情报指定先 focus 定谳）：gd 腿 rc=0（16s，ticks=4232 t=68.02 ev=27626，7228ms）+「[selfcheck] run845_r18 同种子复跑逐字节一致」+PASS（实跑 1 场，跳过 0）；py 腿 6s 完成（_LongContext 注入夹具内联闸生效）；判「三方一致」27626/27626/27626。③`python -X utf8 tools/long_case_fix.py --prefix run845_r18` 首轮全量定位分支：账本无记录→gd 腿 resume 复用 focus 新鲜产物（2s，rc=0，幂等合法）→「已三方一致，无需迭代」exit=0。④双验：gd 产物 output/oracle/align_long/gdcore/run845_r18/events.json=11,556,880 字节+py 腿 7,951,083 字节（均 >1KB，len(events)=27626、winner=opponent 双侧自洽）；本轮三份 gd 日志 focus_gd_focus_10108_1.log（10:40:13，612B）/focus_gd_focus_6300_1.log（10:41:35，1166B，selfcheck 复跑）/prefix_gd_pfx_11240_1.log（10:41:58，611B）经 python str.count 核验「SCRIPT ERROR」均 0 命中（沿用 §6m90 python 计数口径，尾部仅既有 JoypadWindows/DirectInput 引擎退出噪声）。工具对绿场不记 progress.json。
- **本场假设史（旧分歧记录作废口径）**：本场属「未验证（净化重录后无分歧数据）」簇，本轮为净化 harness 语义下首度 py 腿对拍与三方定谳；无新假设被排除、无改动故无回滚面。继 §6m87（run894_r18）/§6m88（run1408_r18）/§6m89（run1342_r18）/§6m90（run1374_r18）/§6m91（run905_r18）/§6m92（run906_r18）/§6m93（run696_r18）/§6m94（run685_r18）之后连续第九场「净化重录后零改动直接翻绿」，进一步佐证净化重录对长场簇的净化有效性。
- **边界**：长场产物/报告均在 output/（.gitignore 内）不入库，本节为唯一入库产出；红线三文件 §6m86 悬置 diff（verify_oracle.py 34/28、OracleAlignBattle.gd 25/44 本轮 diff --numstat 零新增行）零触碰零并入；主夹具 860 场与主账 alignment.json 未动。

## 6m96. ★ np45 长场 run1409_r18：语料残留旧闸截断件→定向净化重录补齐后翻绿（31496事件，首场「语料侧修复」非零改动翻绿，§6m87-95 连绿链修正案）（2026-11-06 长场修复 run1409_r18 p1）

- **结论**：run1409_r18 情报所述「语料已净化重录」对本场**不成立**——实测语料为 Oct31 13:43 旧 harness 残件：result.txt `status=timeout`、`winner=-`（[M12] 单场墙钟>60s 闸于 tick2597/t=43.28 处截断，event_count=26640，player_hp=4288/opponent_hp=3117/fatigue=76 双活中途硬切），不属于 §6m87-95 的「Oct31 冻结件=自然终局」情形。定向净化重录补齐后三方一致 1/1——语料=gd_core=gd_core_py 全 **31496** 事件（语料 26640→31496，guide §4 旧表同记 26640 已过时）、winner=player×3、combat_time=50.016667×3、firstDivergence=null（output/oracle/long_alignment.json total=1 aligned=1 独立账面，未并入 alignment.json）。本场改动面=**仅语料侧**（旧残件→净化重录件），零代码/零引擎/零夹具改动；§6m87-95 连绿链口径修正：该链 Oct31 件确为自然终局，而本场为同簇第 10 场却系旧闸截断残件——「净化重录」批（2026-11-06 04:03-04:35，仅 6 场：run1229_r11/run1334_r10/run1342_r18/run1374_r18/run1408_r18/run986_r12）漏掉本场。
- **判据与实测（本轮亲跑）**：①夹具 output/oracle/align_long/long_cases_fixture.json 本场 py_ev_gate=31969 内联在案（=int(26640×1.2+1)，与情报一致），重录后 31496 仍未触（31969>31496，闸未命中）——坑 2 当场核验。②`--focus` 首跑（旧语料）：gd 腿 rc=0（16s，ticks=3152 t=50.02 ev=31496，7228ms）+[selfcheck] 同种子复跑逐字节一致；gd=py 同为 31496，oracle=26640，首分歧 kind=length（index=None）。自证归因：自写归一化比对（gd id 从 1 起 vs 语料从 0 起、type_name 三方异文、parent_id 随 id 偏移；id/parent_id 哨兵 -1 不偏移、target 为实体序号不偏移）证语料前 26640 事件与 gd 腿逐事件内容全等，gd 超出段为同役自然延拓（t=43.3 起 Chili Pepper Heat/Banana 等）至 t=50.02 player 胜——**引擎侧零嫌疑，纯语料截断**。③语料残件实锤：output/oracle/fights/run1409_r18/result.txt（Oct31 mtime、备份 fights_pre_npur_20261106 同文）`status=timeout`+`winner=-`+[M12] 闸自述「单场墙钟>60s…被截断的战斗照常 dump 已产生事件，status 如实标 timeout」；现行 fights 树 914 场中仅 run986_r12 带 [M13] 净化标记、6 场 mtime 11-06（即上述漏批实证）；wrapper `--check` 报 pending=913。④定向重录：原地跑 `tools/_np46_rerecord.py --cases run1409_r18` 被 harness 自身 resume 闸（oracle_fight.gd case_events_done 见旧 events.json 非空即跳）拦空转两轮（rc=0 但三文件哈希零变化），两轮无进展自动停——**坑：wrapper 的 [M13] pending 判据与 harness 的 events 非空 resume 判据不一致，重录必须换 fresh out_root**。改用 `ORACLE_FIGHTS_ROOT=<repo>/output/oracle/probe/np46_run1409_r18`（绝对路径，harness oracle_fight.gd §373-381 授权的重定向面）再跑：wall=219s 一轮 PASS（pending 1→0，shard_rc=[0]），探针件 status=ok+[M13]+winner=player+combat_time=50.02+event_count=31496=len(events)，与 gd 腿产物归一化逐事件全等（31496/31496）。⑤发布：probe 三文件（events.json 13,056,151B/result.txt/rng_state.txt）cp 回 output/oracle/fights/run1409_r18/（语料写授权面=用户 2026-11-06 批准+备份在位），sha256 双侧逐一核对一致；fights 树内 §6m86 假 PASS 旧 _batch_summary.txt 未触碰（summary 写在 probe 根）。⑥`--focus` 复跑（新语料）：gd 腿 resume 复用首跑新鲜产物（2s，resume 跳过 1，幂等合法——gd 产物只依赖夹具不依赖语料，selfcheck 已在首跑自证）+PASS；py 腿重跑 1s；判「三方一致」31496/31496/31496。⑦`--prefix run1409_r18` 首轮全量定位分支：账本无记录→gd 腿 resume（2s，rc=0）→「已三方一致，无需迭代」exit=0。⑧双验：gd 产物 output/oracle/align_long/gdcore/run1409_r18/events.json=13,219,646 字节+py 腿 9,014,063 字节（均 >1KB，len(events)=31496、winner=player 双侧自洽）；本轮对拍腿 gd 日志 focus_gd_focus_12804_1.log（612B）/prefix_gd_pfx_17644_1.log（611B）经 python str.count 核验「SCRIPT ERROR」均 0 命中（§6m90 口径）；语料重录腿 oracle harness 日志（np46_r1_s0_2468_1.log 51MB）含 226 处 SCRIPT ERROR 系反编译全量工程既有拆除期噪声（result.txt modifications 自述同类；status=ok 且语料与独立 gd 重放逐事件全等即正确性定谳，不构成语料缺陷）。工具对绿场不记 progress.json（该文件不存在）。
- **本场假设史（旧分歧记录作废口径）**：H1「引擎侧行为分歧（gd/py 多跑 4856 事件系引擎 bug）」——排除（归一化前缀 26640 事件全等+超出段自然延拓，见②）；H2「py 腿事件闸未抬致截断伪分歧」——排除（夹具 31969 内联生效，py 产 31496 全长，见①）；H3「语料残缺应修引擎侧对齐」——否决（违 §11 红线且违背 §6m82-84「单场复放≡语料 by construction」语义）；H4「语料已净化重录，分歧即引擎问题」——证伪并翻转（本场语料从未被净化批触达：mtime Oct31/result.txt timeout/「914 场仅 1 场带 [M13]」三证齐全）；H5「原地定向重录可行」——证伪（harness resume 闸拦空转，见④），改 fresh out_root 成功。最终动作=语料侧定向净化重录，零代码改动、无回滚面。**继 §6m87-95 之后第 10 场翻绿，但系首场经「语料残件→净化重录补齐」路径**；警示：fights 树 pending=913，本簇后续场疑有余件同款 Oct31 timeout 残件，先核 result.txt status 是否 ok 再定预期。
- **边界**：长场产物/报告/探针目录均在 output/（.gitignore 内）不入库，本节为唯一入库产出；语料树改动仅 run1409_r18 三文件（备份 fights_pre_npur_20261106 留旧态可回滚）；红线三文件 §6m86 悬置 diff（verify_oracle.py 34/28、OracleAlignBattle.gd 25/44 本轮 diff --numstat 零新增行）零触碰零并入；主夹具 860 场与主账 alignment.json 未动；guide §4 旧表 run1409_r18=26640 一行被本场实测取代（31496），guide 本身未改。

## 6m97. ★ np45 长场 run1229_r11：净化重录后首度对拍直接翻绿（23893事件，连续第十场零改动翻绿，§6m96 语料侧修复后连绿链复归同形）（2026-11-06 长场修复 run1229_r11 p1）

- **结论**：run1229_r11（23893 事件，净化批 6 场名单之一，§6m96 在案）净化重录后首度对拍即三方一致 1/1——语料=gd_core=gd_core_py 全 23893 事件、winner=player×3、combat_time=65.016667×3、firstDivergence=null、judgement 事件元组+渲染双真（output/oracle/long_alignment.json total=1 aligned=1 独立账面，未并入 alignment.json）。零代码/零引擎/零夹具改动，无分歧故无 prefix 迭代假设史（全量定谳覆盖全长）。
- **判据与实测（本轮亲跑）**：①语料核对（§6m96 警示口径：先核 result.txt 再定预期）：events.json mtime 2026-11-06 04:29（净化批 04:03-04:35 窗口内），23893 事件=event_count 字段自洽、winner=player、末事件 type=111 @t=65.016667=combat_time 自然终局。新在案（一）：末事件 type=111 而非 §6m93-95 惯例的 type=112，四场语料比对证 111/112 与 winner 完美相关（winner=player↔111：run986_r12/run1229_r11；winner=opponent↔112：run1334_r10/run685_r18）——「末事件 type=112」系 opponent 胜场特例而非自然终局通例，player 胜场以 111 收尾同为自然终局（status=ok 的 run986_r12 末事件同为 111 同证）。新在案（二）：语料尾部 id 缺口（id 从 1 起、max 23894、恰缺 23893 一个），与绿场 run685_r18 语料尾部缺口（28293→28297 缺三个）同形，系 harness 计数正常行为非缺陷。②新在案（三）：本场 result.txt 系 Oct31 13:15 旧残件未随净化批更新——status=timeout、winner=-、event_count=20740（[M12] 60s 墙钟闸截断自述），与 events.json（Nov6、23893、winner=player）不一致；同批 run1334_r10 同款（events.json Nov6 04:35+result.txt Oct31 timeout），run986_r12 三文件齐 Nov6 08:14 status=ok——净化批发布只回填 events.json 未回填 result.txt/rng_state.txt；对拍 mechanics 只读 events.json，不构成语料缺陷，但 §6m96 式「核 result.txt 定预期」对净化批余场会误报 timeout 预期，核预期须以 events.json 本体自洽性为准。③夹具 output/oracle/align_long/long_cases_fixture.json 本场 py_ev_gate=28672 内联在案（=int(23893×1.2+1)，与情报一致），23893 未触默认闸 25000——坑 2 当场核验。④`python -X utf8 tools/long_case_fix.py --focus run1229_r11`（情报指定先 focus 定谳）：gd 腿 rc=0（13s，ticks=4052 t=65.02 ev=23893）+「[selfcheck] run1229_r11 同种子复跑逐字节一致」+PASS（实跑 1 场，跳过 0）；py 腿 5s 完成（_LongContext 注入夹具内联闸生效）；判「三方一致」23893/23893/23893。⑤`--prefix run1229_r11` 首轮全量定位分支：账本无记录→gd 腿 resume 复用 focus 新鲜产物（2s，rc=0，幂等合法）→「已三方一致，无需迭代」exit=0。⑥双验：gd 产物 output/oracle/align_long/gdcore/run1229_r11/events.json=10,005,439 字节+py 腿 6,785,542 字节（均 >1KB，len(events)=23893、winner=player 双侧自洽）；本轮三份 gd 日志 focus_gd_focus_8392_1.log（610B）/focus_gd_focus_13420_1.log（1169B，selfcheck 复跑）/prefix_gd_pfx_19376_1.log（611B）经 python str.count 核验「SCRIPT ERROR」均 0 命中（§6m90 口径，尾部仅既有 JoypadWindows/DirectInput 引擎退出噪声）。工具对绿场不记 progress.json（该文件仍不存在）。
- **本场假设史（旧分歧记录作废口径）**：本场属「未验证（净化重录后无分歧数据）」簇，本轮为净化 harness 语义下首度 py 腿对拍与三方定谳；无新假设被排除、无改动故无回滚面。继 §6m87（run894_r18）/§6m88（run1408_r18）/§6m89（run1342_r18）/§6m90（run1374_r18）/§6m91（run905_r18）/§6m92（run906_r18）/§6m93（run696_r18）/§6m94（run685_r18）/§6m95（run845_r18）连续九场零改动直绿与 §6m96（run1409_r18）语料侧修复之后第 11 场翻绿——零改动直绿链在 §6m96 插曲后复归同形（累计连续第十场零改动翻绿）。
- **边界**：长场产物/报告均在 output/（.gitignore 内）不入库，本节为唯一入库产出；红线三文件 §6m86 悬置 diff（verify_oracle.py 34/28、OracleAlignBattle.gd 25/44 本轮 diff --numstat 零新增行）零触碰零并入；主夹具 860 场与主账 alignment.json 未动。

## 6m98. ★ np45 长场 run1362_r18：语料「双重陈旧」残件（Oct31 timeout 截断 + 全程行为漂移，非 run1409 纯截断形）→ 定向净化重录 + 长场夹具闸重算后翻绿（79595事件，本簇最长场；新坑两条：闸按截断语料算不足 + py 腿 resume 对闸变化失明）（2026-11-06 长场修复 run1362_r18 p1）

- **结论**：run1362_r18 情报所述「语料已净化重录（23012 事件）」对本场**不成立**——实测语料为 Oct31 13:43 旧残件（与 run1409_r18 残件同分钟批次，§6m96 净化批 6 场名单再度漏掉本场），且系**双重陈旧**：①result.txt status=timeout、winner=-、ticks=2168、t=36.13、player_hp=4372/350、opponent_hp=4330/350 双活中途硬切（[M12] 60s 墙钟闸，events.json winner=- 末事件 type=0 本体即不自洽，§6m97「以 events.json 本体自洽性为准」口径直接命中）；②比 run1409 更糟——**全程行为漂移**，非纯截断（详②）。定向净化重录补齐 + 长场夹具 py_ev_gate 重算后三方一致 1/1——语料=gd_core=gd_core_py 全 **79595** 事件（语料 23012→79595，本簇 54 场中最长，超此前最大 run894_r18 的 48297）、winner=player×3、combat_time=74.016667×3、末事件 type=111 Win @t=74.016667=combat_time 自然终局（§6m97 111↔player 相关律再证）、firstDivergence=null（output/oracle/long_alignment.json total=1 aligned=1 独立账面，未并入 alignment.json）。本场改动面=**语料侧+长场夹具闸重算**，零代码/零引擎/零红线改动。
- **判据与实测（本轮亲跑）**：①语料残件实锤：events.json mtime Oct31 13:43:46（净化批 11-06 04:03-04:35 窗口外）、result.txt status=timeout 自述截断；备份 fights_pre_npur_20261106/run1362_r18 四件与现行语料 sha256 逐一相同（回滚面在位）。②旧语料 vs gd 腿全比对（自写归一化 key：type+ts+origin 语义元组+target+parent_id+params，id/parent_id 按 §6m96 偏移口径、-1 哨兵不偏移，type_name 三方异文忽略）：**23012 事件中仅 2286 对齐**，首内容分歧 idx=63/t=0.7（语料独有 GemSocket2 type105+110 对，parent=61），此后语料与 gd 腿渐行渐远（t=36.13 语料终点处 gd 已 25713 事件 vs 语料 23012；type 配比全面错开：105 −27/109 −1/102 +32/19 +34 等）——证旧残件录制时的引擎状态与现行 gd 重放全程不同，**旧语料整体作废**，不复具 run1409 式「前缀全等+尾部截断」结构（SequenceMatcher 对齐 delete 1160/insert 1201/replace 79267）。③`--focus` 首跑三腿：gd 腿 rc=0（32s，ticks=4592 t=74.02 ev=79595，winner=player）+「[selfcheck] run1362_r18 同种子复跑逐字节一致」；py 腿 27642 事件 winner=opponent t=37.58；oracle 23012。**gd≠py 非引擎分歧而是夹具旧闸伪分歧（新坑一）**：py 腿 payload player_hp=5284/5284、opponent_hp=5088/5088 双方满血无 judgement 事件（末事件 type=0 item_activate），simulator/gd_core_engine.py:1171-1173 `while…if len(self.log.events) > _gate: break` 逐 tick 查闸硬切（27642=闸 27615+27 恰一个 tick 批过冲），切后无条件 winner() 取未终局默认 opponent——指纹：**winner=opponent+双方满血+末事件非 111/112+event_count 贴闸**即闸切伪败。夹具闸 27615=int(23012×1.2+1) 按截断语料事件数计算，低于自然长度 79595——guide §4 闸公式前提「语料 event_count=自然长度」对截断残件场不成立。④py 腿与 gd 腿行为全等自证：27642 公共窗内行为签名（type/ts/target/parent/params 数值感知归一）**零分歧**（仅 59 处 origin 表形异文：gd 记原始实体序号、py 记 damage_source 字典，harness 表形差异非行为），py 流为 gd 流行为前缀——引擎零嫌疑。⑤定向净化重录：fresh probe 根 `ORACLE_FIGHTS_ROOT=<repo>/output/oracle/probe/np46_run1362_r18 python -X utf8 tools/_np46_rerecord.py --cases run1362_r18`（§6m96 playbook，原地必被 resume 闸拦），wall=433s 一轮 PASS（pending 1→0，resume_skipped=0，shard_rc=[0]），探针件 status=ok+winner=player+combat_time=74.02+ticks=4441+event_count=79595=len(events) 本体自洽；探针 vs gd 腿归一化全比 **79595/79595 零分歧**（探针 id 从 0 起无尾缺口，gd 从 1 起）。⑥发布：probe 三件（events.json 32,286,837B/result.txt/rng_state.txt）cp 回 output/oracle/fights/run1362_r18/，sha256 双侧逐一核对一致，lineups.json 语料/探针相同（零回填必要）；语料写授权面=用户 2026-11-06 批准+备份在位。⑦`--prepare` 重算长场夹具：py_ev_gate 仅两处变化——run1362_r18 27615→**95515**（=int(79595×1.2+1)）与 run1409_r18 31969→**37796**（§6m96 场语料已 31496 而闸未随该轮重算，本轮顺带补正），余 52 场闸逐一零变化（--prepare 前快照 diff 核验）。⑧`--focus` 复跑一波三折：首次复跑 py 腿 1s resume 复用旧闸截断产物（27642）仍判伪分歧——**新坑二：py 腿产物 resume 判据=文件存在+event_count>0，对夹具闸变化失明**，闸重算后必须删该场 output/oracle/align_long/py/<case>/events.json 再 focus；删除后复跑（gd 腿 resume 复用 11:19 首跑 selfcheck 产物合法+该产物与探针语料全等已由⑤独立裁定）py 腿 10s 产 79595，判「三方一致」79595/79595/79595。⑨`--prefix run1362_r18` 首轮全量定位分支：账本无记录→gd 腿 resume（4s，rc=0）→「已三方一致，无需迭代」exit=0。⑩双验：gd 产物 output/oracle/align_long/gdcore/run1362_r18/events.json=32,974,040 字节+py 腿 22,045,159 字节（均 >1KB，len(events)=79595、winner=player、末事件 111@74.016667 双侧自洽）；本轮四份 gd 日志 focus_gd_focus_14952_1.log（11:19:10，1169B，含 selfcheck 复跑）/focus_gd_focus_13460_1.log（11:41:30）/focus_gd_focus_6968_1.log（11:42:09）/prefix_gd_pfx_11364_1.log（11:42:59）经 python str.count 核验「SCRIPT ERROR」均 0 命中（§6m90 口径）；探针 harness 日志 np46_r1_s0_5664_1.log（114.5MB）SCRIPT ERROR 命中按 §6m96 口径不构成缺陷（反编译期既有噪声，status=ok 且探针≡gd 79595 全等即正确性定谳）。工具对绿场不记 progress.json。
- **本场假设史（旧分歧记录作废口径）**：H1「gd/py 引擎行为分歧（py 27642 winner=opponent 系真败北）」——排除（py 双方满血+末事件非 judgement+event_count 贴闸=闸切伪败指纹，见③；公共窗零行为分歧见④）；H2「语料仅截断、前缀应全等（run1409 同形预期）」——证伪（2286/23012 对齐、全程漂移，见②）；H3「引擎侧需修」——排除（零引擎改动即三方翻绿；gd selfcheck+探针≡gd 全等+py≡gd 前缀全等三证）；H4「夹具闸内联即充足（guide §4 公式）」——对截断残件场证伪，闸源（截断 event_count）即错，重录后 --prepare 重算方治本；H5「闸重算后 focus 自动生效」——证伪（py resume 失明），须删旧 py 产物。最终动作=语料侧定向净化重录+长场夹具闸重算，零代码改动、无代码回滚面。**继 §6m87-95（九场零改动直绿）/§6m96（run1409 语料侧修复）之后第 12 场翻绿**；在案两条新坑（闸按截断语料算不足/温 py 产物 resume 失明）对本簇余场（fights 树 pending=913 警示延续：凡 Oct31 timeout 残件场，重录后必须 --prepare 重算闸+删旧 py 腿产物）。
- **边界**：长场产物/报告/探针目录均在 output/（.gitignore 内）不入库；语料树改动仅 run1362_r18 三文件（备份 fights_pre_npur_20261106 留旧态可回滚）+长场夹具两场闸值重算（长场工具自有夹具，非红线主夹具）；红线三文件 §6m86 悬置 diff（verify_oracle.py 34/28、OracleAlignBattle.gd 25/44 本轮 diff --numstat 零新增行）零触碰零并入；主夹具 860 场与主账 alignment.json 未动；guide 本身未改（其 §4 闸公式前提缺陷由本节在案）。

## 6m99. ★ np45 长场 run902_r18：净化重录后首度对拍直接翻绿（22481事件，§6m98 语料侧插曲后零改动直绿链复归）+ 在案一条：prefix 首轮分支不跑 py 腿，新场首跑 prefix 必误报「长度型分歧」（2026-11-06 长场修复 run902_r18 p1）

- **结论**：run902_r18 情报所述「语料已净化重录（2026-11-06）」对本场**不成立**——实测语料 mtime Oct31 12:30、净化批 6 场名单（§6m96 在案）无本场；但系 §6m93-95 同形「**Oct31 冻结件=自然终局**」良品：result.txt status=ok、winner=player、ticks=4021（<5400）、player_hp=1/opponent_hp=0、event_count=22481 未触 [M12] 25000 闸——非 run1409/run1362 式 timeout 残件，无需语料侧修复。净化重录后首度对拍即三方一致 1/1——语料=gd_core=gd_core_py 全 **22481** 事件、winner=player×3、firstDivergence=null、judgement 事件元组+渲染双真（output/oracle/long_alignment.json total=1 aligned=1 独立账面，未并入 alignment.json）。零代码/零引擎/零夹具/零语料改动。
- **判据与实测（本轮亲跑）**：①语料本体自洽核（§6m97 口径「以 events.json 本体自洽性为准」）：len(events)=22481=event_count 字段自洽、winner=player、combat_time=67.016667、末事件 type=111 @t=67.016667=combat_time 自然终局（§6m97 111↔player 相关律再证）、seed=7142951 与夹具一致、result.txt status=ok 同口径三文件一致。②夹具 output/oracle/align_long/long_cases_fixture.json 本场 py_ev_gate=26978 内联在案（=int(22481×1.2+1)，本轮实算核对一致），22481 未触默认闸 25000——坑 2 当场核验。③`--prefix run902_r18` 首轮（账本无记录→全量定位分支）：gd 腿 rc=0（13s，ticks=4172 t=67.02 ev=22481，5824ms）+「[selfcheck] run902_r18 同种子复跑逐字节一致」+PASS（实跑 1 场，跳过 0）；compare_case 报「py 缺产物」入长度型分歧分支（tools/long_case_fix.py:589-598）——**新在案：prefix 首轮定位分支只跑 gd 腿（_run_gd_prefix，tools/long_case_fix.py:582）不跑 py 腿**，对从未产出过 py 腿产物的新场首跑 prefix 必误报「无事件级分歧但未一致——长度型分歧」，非真分歧（该分支未记账，progress.json 仍不存在）；台账 §6m96-98 诸场均因 focus 先行未踩此形，本场为首个 prefix 先行场次故首见。④`--focus run902_r18` 三腿定谳：gd 腿 resume 复用 prefix 首跑新鲜产物（2s，PASS 实跑 0 跳过 1，幂等合法——selfcheck 已在首跑自证，gd 产物只依赖夹具不依赖语料）；py 腿 4s 产 22481（_LongContext 注入夹具内联闸 26978 生效未触）；判「三方一致」22481/22481/22481。⑤`--prefix` 复跑收口：首轮定位分支→gd resume（2s，rc=0）→「已三方一致，无需迭代」exit=0。⑥双验：gd 产物 output/oracle/align_long/gdcore/run902_r18/events.json=9,605,984 字节+py 腿 6,464,050 字节（均 >1KB，len(events)=22481、winner=player、末事件 111@67.016667 双侧自洽）；本轮两份 gd 日志 prefix_gd_pfx_2440_1.log（1165B，11:48，含 selfcheck 复跑）/focus_gd_focus_1152_1.log（610B，11:49，resume）经 python str.count 核验「SCRIPT ERROR」均 0 命中（§6m90 口径，尾部仅 JoypadWindows/DirectInput 引擎退出噪声）。⑦新在案（观察，非缺陷）：gd 腿 ticks=4172 vs 语料 result.txt ticks=4021——录制 harness 与重放器 tick 计数口径差，事件流 22481 三方全等方为对齐通货（§6m96 gd ticks=3152 vs 探针 4441 同形在案）。工具对绿场不记 progress.json（该文件仍不存在）。
- **本场假设史（旧分歧记录作废口径）**：本场属「未验证（净化重录后无分歧数据）」簇；H1「prefix 首轮报长度型分歧=语料截断（run1409 同形预期）」——排除（compare 报文实因 py 腿产物缺失，focus 三腿后即三方一致，见③④）；H2「语料系净化批漏网残件需定向重录（run1409/run1362 同形预期）」——排除（Oct31 冻结件但 status=ok+自然终局+事件闸未触，本体自洽即良品，见①）。无引擎假设被排除、无改动故无回滚面。继 §6m87-95（九场零改动直绿）/§6m96（run1409 语料侧修复）/§6m97（run1229_r11 零改动直绿）/§6m98（run1362_r18 语料+夹具闸修复）之后第 13 场翻绿——零改动直绿累计第十一场（§6m98 语料侧插曲后复归）。警示延续：prefix 首轮「长度型分歧」报文对未跑过 py 腿的新场是假信号，**新场首验以 --focus 三腿定谳为准**（与 §6m96-98 playbook 一致）；fights 树 pending=913 警示（§6m96）不适用于本场（status=ok 良品）。
- **边界**：长场产物/报告均在 output/（.gitignore 内）不入库，本节为唯一入库产出；红线三文件 §6m86 悬置 diff（verify_oracle.py 34/28、OracleAlignBattle.gd 25/44 本轮 diff --numstat 零新增行）零触碰零并入；tools/_np46_rerecord.py 14/1 系本轮前既有改动未触碰；主夹具 860 场与主账 alignment.json 未动；guide 本身未改。

## 6m100. ★ np45 长场 run710_r18：语料「status=ok 三件自洽却行为陈旧」型残件（Oct31 12:08 旧 harness 盲池语义录件，净化批名单外）→ 定向净化重录 + 长场夹具闸重算后翻绿（22112事件；新在案：自洽≠良品，未验证簇只能靠对拍本体检出）（2026-11-06 长场修复 run710_r18 p1）

- **结论**：run710_r18 情报所述「语料已净化重录（2026-11-06）」对本场**不成立**——实测语料 mtime Oct31 12:08:33（净化批 11-06 04:03-04:35 窗口外、§6m96 六场名单无本场）。且本场**不同于 run1409/run1362 的 timeout 残件形**：result.txt status=ok/winner=player/event_count=22408 与 events.json 三件自洽、末事件 type=111 @68.016667=combat_time 自然终局（§6m97 口径下「本体自洽」全过）——但首度 `--focus` 对拍即 oracle≠gdcore（22408 vs 22112）：语料 7.6s 有 id=1064 致盲超时事件（109 amount=-6 timeout=True）而 gd/py 两腿无此事件，其后 561 块全程漂移（SequenceMatcher 归一化对齐仅小部分；两侧 winner=player×3、combat_time=68.016667×3 恒同）。定向净化重录（probe 根 wall=200s PASS）产 **22112** 事件≡gd 腿逐位置归一化零分歧→**旧语料系旧 harness 盲池行为录件整体作废**，发布后三方一致 1/1——语料=gd_core=gd_core_py 全 **22112** 事件、winner=player×3、末事件 type=111 @68.016667 自然终局、firstDivergence=null（output/oracle/long_alignment.json total=1 aligned=1 独立账面，未并入 alignment.json）。本场改动面=**语料侧+长场夹具闸重算**，零代码/零引擎/零红线改动。
- **判据与实测（本轮亲跑）**：①语料旧件核（当时口径）：mtime Oct31 12:08:33、len(events)=22408=event_count 自洽、result.txt 三件一致 status=ok、ticks=4081<5400、player_hp=1/350——按 §6m97「本体自洽」口径曾全过，恰证**自洽≠现役**（新在案，见假设史 H2）。②夹具 py_ev_gate=26890=int(22408×1.2+1) 当场实算一致、22408<25000 未触默认闸——坑 2 常规核验。③`--focus` 首跑三腿定谳（§6m99 playbook）：gd 腿 rc=0（13s，ticks=4232 t=68.02 ev=22112）+「[selfcheck] run710_r18 同种子复跑逐字节一致」；py 腿 22112=gd 同数（引擎双腿一致）；compare 判 oracle≠gdcore 首分歧 oracle_vs_gdcore（idx=456/t=456tick=7.6s，渲染行「[对手] 6 致盲持续时间结束(光之黏黏)」vs「[对手] 消耗1 幸运 （软呢帽）」）。④分歧归因（事件流考古）：语料与 gd 腿**前 1064 事件逐位置全等**（含 5.35/5.65/6.4667/6.4833/7.2333 五次致盲到期同位同量），首个差异=语料 id1064 的 6@2.9333 施加盲到期（2.9333+4.65=7.5833→7.6）在 gd 缺失；tgt0 盲账本 7.05s 前逐笔全等；Shelly 净化 -6@3.95/-6@4.3 事件双侧逐字节同在——分歧非引擎侧可归因（原版 oracle/Core/Buff.gd loseStacks:221-303 与 gd_core/CoreBuff.gd:294-373 逐行同构：先永久、临时最远 timeout 先吃；gainTemporary 抵抗分支同构、抵抗量均不入池）。⑤决定性实验（§6m96 playbook）：`ORACLE_FIGHTS_ROOT=<repo>/output/oracle/probe/np46_run710_r18 python -X utf8 tools/_np46_rerecord.py --cases run710_r18`，wall=200s 一轮 PASS（pending 1→0，shard_rc=[0]）；探针件 status=ok+winner=player+ticks=4081+event_count=22112=len(events) 本体自洽、末事件 111@68.016667；events.json≡events_first.json sha256 一致（harness 确定性自证）；**探针 vs gd 腿归一化全比 22112/22112 逐位置零分歧**（探针 id 从 0 起、gd 从 1 起，§6m96 偏移口径）——证旧语料 22408 件录制时的 harness 盲池语义与现行 harness（及镜像现行 harness 的 gd_core）不同，旧件整体作废，引擎零嫌疑。⑥发布：探针三件（events.json 9,009,916B/result.txt/rng_state.txt）cp 回 output/oracle/fights/run710_r18/，sha256 双侧逐一核对一致；lineups.json 语料/探针相同（零回填必要）；回滚面=fights_pre_npur_20261106/run710_r18 四件与旧语料 sha256 逐一相同（发布前核验在位）。⑦`--prepare` 重算长场夹具：py_ev_gate 26890→**26535**（=int(22112×1.2+1)）仅本场变化——台账在案六场闸（run845 33152/run1409 37796/run1229_r11 28672/run1362 95515/run902 26978/run894 57957）逐一零漂移核对（§6m98 坑一「闸按截断语料算不足」同构面：闸源=旧语料 22408 现随重录件修正）。⑧删该场旧 py 腿产物（§6m98 新坑二：py resume 对闸变化失明）后 `--focus` 复跑：gd 腿 resume 复用首跑 selfcheck 产物（2s，实跑 0 跳过 1，幂等合法——gd 腿只依赖夹具阵容不依赖语料，且首跑产物已由⑤探针全等独立裁定）+py 腿 4s 产 22112（新闸 26535 生效未触），判「三方一致」22112/22112/22112。⑨`--prefix run710_r18` 收口：首轮全量定位分支→gd resume（2s，rc=0）→「已三方一致，无需迭代」exit=0（prefix 首轮不跑 py 腿的 §6m99 假信号本场未踩——focus 先行）。⑩双验：gd 产物 output/oracle/align_long/gdcore/run710_r18/events.json=9,209,545 字节+py 腿 6,272,500 字节（均 >1KB，len=22112、winner=player、末事件 111@68.016667 双侧自洽）；本轮 gd 日志 focus_gd_focus_8868_1.log（610B resume）/prefix_gd_pfx_17704_1.log（611B）及首轮 focus 含 selfcheck 日志经 python str.count 核验「SCRIPT ERROR」均 0 命中（§6m90 口径）；探针 harness 日志 np46_r1_s0_12088_1.log（43MB，189 命中）按 §6m96 口径不构成缺陷（反编译期既有噪声，status=ok 且探针≡gd 22112 全等即正确性定谳）。工具对绿场不记 progress.json（该文件仍不存在）。
- **本场假设史（旧分歧记录作废口径）**：本场属「未验证（净化重录后无分歧数据）」簇。H1「gd_core 致盲到期机制缺失/Shelly 净化吃错叠（farthest-timeout-first 吃掉 6@2.9333 叠）＝引擎 bug」——排除（探针现行 harness 22112≡gd 逐位置零分歧，引擎与现行 harness 行为一致，见④⑤）；H2「语料 status=ok 三件自洽＝良品免检（§6m99 run902 同形预期）」——**证伪（新在案：Oct31 冻结件可三件自洽且自然终局、却整体承载旧 harness 行为，唯有对拍本体可检出；「核 result.txt 定预期」对这类场不构成免检资格）**；H3「夹具闸未抬致 py 伪分歧（§6m98 坑一预期）」——排除（py 腿 22112=gd 同数非贴闸截断形，闸重算后 26535 生效）；H4「prefix 首轮长度型分歧假信号（§6m99 新坑）」——未踩（focus 先行）。最终动作=语料侧定向净化重录+长场夹具闸重算+删旧 py 产物，零代码改动、无代码回滚面。**继 §6m87-95（九场零改动直绿）/§6m96（run1409）/§6m97（run1229_r11）/§6m98（run1362）/§6m99（run902）之后第 14 场翻绿、第 4 场语料侧修复（run710 加入手册：timeout 残件形之外新添「自洽陈旧件」形）**。警示延续：未验证簇余场凡 mtime 在净化批窗口外者，一律先 --focus 三腿对拍再定「良品/残件」，不得以三件自洽免检。
- **边界**：长场产物/报告/探针目录均在 output/（.gitignore 内）不入库，本节为唯一入库产出；语料树改动仅 run710_r18 三文件（备份 fights_pre_npur_20261106 留旧态可回滚，sha256 已核对）+长场夹具一场闸值重算（长场工具自有夹具，非红线主夹具）；红线三文件 §6m86 悬置 diff（verify_oracle.py 34/28、OracleAlignBattle.gd 25/44，本轮 diff --numstat 数值不变）零触碰零并入；主夹具 860 场与主账 alignment.json 未动；guide 本身未改。

## 6m101. ★ np45 长场 run629_r18：「自洽陈旧件」第二例（Oct31 12:03 旧 harness 盲池语义录件，与 run710 同分钟批次、净化批名单外）→ 定向净化重录后翻绿（20218事件；本轮新在案：分歧可收敛为「同位同型仅 amount 异」的微残件形，13/20218 位置、无结构漂移）（2026-11-06 长场修复 run629_r18 p1）

- **结论**：run629_r18 情报所述「语料已净化重录（2026-11-06）」对本场**不成立**——实测语料 mtime Oct31 12:03:46（净化批 11-06 04:03-04:35 窗口外、§6m96 六场名单无本场），与 §6m100 run710_r18（Oct31 12:08:33）同分钟批次。且系 §6m100「自洽陈旧件」同型：result.txt status=ok/winner=player/combat_time=47.02/ticks=2821<5400/event_count=20218 与 events.json 三件自洽、末事件 type=111 @47.016667=combat_time 自然终局——按 §6m100 警示「三件自洽≠免检」不放手，`--focus` 首跑对拍即 oracle≠gdcore 首分歧 idx=498/t=451tick=7.516667。定向净化重录（probe 根 wall=156s PASS）产 20218 事件≡gd 腿逐位置归一化零分歧→**旧语料 13 处致盲到期 amount 系旧 harness 盲池语义、整体作废**，发布后三方一致 1/1——语料=gd_core=gd_core_py 全 **20218** 事件、winner=player×3、firstDivergence=null（output/oracle/long_alignment.json total=1 aligned=1 独立账面，未并入 alignment.json）。本场改动面=**语料侧**，零代码/零引擎/零夹具闸改动。
- **判据与实测（本轮亲跑）**：①语料旧件核：mtime Oct31 12:03:46、len(events)=20218=event_count 自洽、result.txt 三件一致 status=ok、winner=player、末事件 111@47.016667；备份 fights_pre_npur_20261106/run629_r18 四件与旧语料 sha256 逐一相同（events 62c0a376…/result 35efeb97…/rng_state 72c5a800…，回滚面在位）。②夹具 py_ev_gate=25000 默认闸（20218<25000；int(20218×1.2+1)=24262<25000）——坑 2 常规核验；无 progress.json、无双腿旧产物系全新场。③`--focus` 首跑三腿定谳（§6m99 playbook，prefix 首轮不跑 py 腿的假信号规避）：gd 腿 rc=0（13s，ticks=2972 t=47.02 ev=20218，ticks 2972 vs 语料 2821 系录制/重放 tick 计数口径差 §6m99 在案，事件流方为通货）+「[selfcheck] run629_r18 同种子复跑逐字节一致」；py 腿 20218 同数；compare 判 oracle≠gdcore（index=498，渲染行「[对手] 4 致盲持续时间结束(光之黏黏)」vs「[对手] 1 致盲持续时间结束(光之黏黏)」）。④分歧归因（归一化 key：type+ts(数值感知 4 位)+origin 语义元组+target+params；id 偏移口径语料 0 起/gd 1 起）：**oracle vs gd 仅 13/20218 位置分歧**——全部为 type=109 致盲持续时间结束事件（同位/同 t/同物品 Light Goobert|Mr Struggles/同 target=0，仅 amount 异：语料 -4/-7/-7/-9/-9/-9/-9/-15/-13/-11/-18/-10/-16 vs gd -1/-4/-4/-8/-6/-4/-5/-12/-10/-7/-16/-7/-14），idx=3405/t=18.82 之后 16000+ 事件全对齐、事件数恒同 20218 无结构漂移（run710 形为语料独有事件致块漂移，本场更微：同位同型仅 amount 异）；**gd vs py 行为签名（type/ts/target/params 数值感知）0/20218 零分歧**（origin 表形异文另计：gd 记原始实体序号如 99、py 记 damage_source 字典如 {kind:damage_source,keyword:fatigue}，harness 表形差异非行为）——引擎双腿行为全等，零嫌疑。⑤决定性实验（§6m96/§6m100 playbook）：`ORACLE_FIGHTS_ROOT=<repo>/output/oracle/probe/np46_run629_r18 python -X utf8 tools/_np46_rerecord.py --cases run629_r18`，wall=156s 一轮 PASS（pending 1→0）；探针件 status=ok+winner=player+combat_time=47.02+ticks=2821+event_count=20218=len(events) 本体自洽、末事件 111@47.016667；events.json≡events_first.json sha256 一致（harness 确定性自证）；**探针 vs gd 腿归一化全比 20218/20218 逐位置零分歧**——证旧语料录制时的 harness 盲池语义与现行 harness（及镜像现行 harness 的 gd_core）不同，旧件整体作废（§6m100「自洽≠良品」再证+同批次第二例）。⑥发布：探针三件（events.json 8,511,766B/result.txt/rng_state.txt）cp 回 output/oracle/fights/run629_r18/，sha256 双侧逐一核对一致；lineups.json 语料/探针 sha256 相同（64056877…，零回填必要）。⑦`--prepare` 重算长场夹具：**闸零变化**（快照 diff+整夹具 deep-equal 双核，20218<25000 默认闸本就正确）——§6m98 坑一（闸按截断语料算不足）不适用：旧语料即自然全长非截断形，重录前后 event_count 恒 20218；坑二（py resume 对闸变化失明）同不触发（闸未变，py 产物合法温件且已由④行为零分歧独立裁定）。⑧`--focus` 复跑翻绿：gd 腿 resume 复用首跑 selfcheck 产物（2s，实跑 0 跳过 1，幂等合法——gd 腿只依赖夹具阵容不依赖语料，首跑产物已由⑤探针全等裁定）+py 腿 resume（1s），判「三方一致」20218/20218/20218。⑨`--prefix run629_r18` 收口：首轮全量定位分支→gd resume（2s，rc=0）→「已三方一致，无需迭代」exit=0（§6m99 假信号未踩——focus 先行）。⑩双验：gd 产物 output/oracle/align_long/gdcore/run629_r18/events.json=8,618,250 字节+py 腿 5,822,801 字节（均 >1KB，len=20218、winner=player、末事件 111@47.016667 双侧自洽，py 侧浮点尾差 47.01666666… 系 py float 表示）；本轮三份 gd 日志 focus_gd_focus_3140_1.log（1,166B 首跑含 selfcheck）/focus_gd_focus_6304_1.log（610B resume）/prefix_gd_pfx_13796_1.log（611B）经 python str.count 核验「SCRIPT ERROR」均 0 命中（§6m90 口径）；探针 harness 日志 np46_r1_s0_18092_1.log（31.7MB，163 命中）按 §6m96 口径不构成缺陷（反编译期既有噪声，status=ok 且探针≡gd 20218 全等即正确性定谳）。工具对绿场不记 progress.json（该文件仍不存在）。
- **本场假设史（旧分歧记录作废口径）**：本场属「未验证（净化重录后无分歧数据）」簇。H1「引擎致盲到期 loseStacks 语义分歧（语料到期删 4-18 叠 vs gd 删 1-16 叠）＝引擎 bug 需修」——排除（gd≡py 行为签名 0/20218 零分歧+探针现行 harness≡gd 20218/20218 零分歧双证，引擎与现行 harness 行为一致，残件在语料侧，见④⑤）；H2「语料三件自洽+自然终局＝良品免检（§6m99 run902 同形预期）」——证伪（§6m100「自洽≠良品」同批次第二例，唯有对拍本体可检出）；H3「语料截断残件（run1409/run1362 timeout 形预期）」——排除（status=ok 自然终局、重录前后 event_count 恒 20218、闸零变化）；H4「夹具闸未抬致 py 伪分歧（§6m98 坑一预期）」——排除（py 20218=gd 同数非贴闸形，行为零分歧）；H5「prefix 首轮长度型分歧假信号（§6m99 新坑）」——未踩（focus 先行）。最终动作=语料侧定向净化重录，零代码/零引擎/零夹具改动、无代码回滚面。**继 §6m87-95（九场零改动直绿）/§6m96（run1409）/§6m97（run1229_r11）/§6m98（run1362）/§6m99（run902）/§6m100（run710）之后第 15 场翻绿、第 5 场语料侧修复、「自洽陈旧件」形第 2 例（run629 与 run710 同分钟批次 Oct31 12:03-12:08，警示延续：未验证簇余场凡 mtime 在净化批窗口外者一律先 --focus 三腿对拍再定「良品/残件」）**。
- **边界**：长场产物/报告/探针目录均在 output/（.gitignore 内）不入库，本节为唯一入库产出；语料树改动仅 run629_r18 三文件（备份 fights_pre_npur_20261106 留旧态可回滚，sha256 已核对）；红线三文件 §6m86 悬置 diff（verify_oracle.py 34/28、OracleAlignBattle.gd 25/44，本轮 diff --numstat 数值不变）零触碰零并入；主夹具 860 场与主账 alignment.json 未动；guide 本身未改。

## 6m102. ★ np45 长场 run989_r18：「自洽陈旧件」第三例+首见**winner 翻转形**（Oct31 12:41 旧 harness 盲池语义录件，与 run710/run629 同日批次、净化批名单外；语料 player 胜 vs 现行三方 opponent 胜）→ 定向净化重录后翻绿（19202事件）（2026-11-06 长场修复 run989_r18 p1）

- **结论**：run989_r18 情报所述「语料已净化重录（2026-11-06）」对本场**不成立**——实测语料 mtime Oct31 12:41:17（净化批 11-06 04:03-04:35 窗口外、§6m96 名单无本场），与 §6m100 run710_r18（12:08）/§6m101 run629_r18（12:03）同 Oct31 12:xx 批次。且系 §6m100「自洽陈旧件」第三例并**升级**：result.txt status=ok/winner=player/combat_time=62.07/ticks=3724<5400/event_count=20119=len(events) 三件自洽、末事件 111@62.066667 自然终局——按 §6m97 口径曾全过——但 `--focus` 首跑对拍即 oracle≠gdcore（20119 vs 19202）且 **winner 翻转：语料 player 胜 vs gd/py 双腿 opponent 胜**（§6m100/§6m101 三方恒 player 的形态之外首见）。定向净化重录（probe 根 wall=190s PASS）产 19202 事件 winner=opponent ≡ gd 腿逐位置归一化零分歧→**旧语料 20119 件系旧 harness 行为录件整体作废**，发布后三方一致 1/1——语料=gd_core=gd_core_py 全 **19202** 事件、winner=opponent×3、末事件 112@60.066667、firstDivergence=null（output/oracle/long_alignment.json total=1 aligned=1 独立账面，未并入 alignment.json）。本场改动面=**语料侧**，零代码/零引擎/零夹具闸改动。
- **判据与实测（本轮亲跑）**：①语料旧件核：mtime Oct31 12:41:17、len(events)=20119=event_count 自洽、result.txt 三件一致 status=ok、winner=player、末事件 111@62.066667；备份 fights_pre_npur_20261106/run989_r18 四件与旧语料 sha256 逐一相同（events 4fdabe8d…/result 39a34541…/rng_state 7eda1a28…，回滚面在位）。②夹具 py_ev_gate=25000 默认闸（20119<25000；int(20119×1.2+1)=24143<25000）——坑 2 常规核验；无 progress.json、无双腿旧产物系全新场。③`--focus` 首跑三腿定谳（§6m99 playbook）：gd 腿 rc=0（12s，ticks=3755 t=60.07 ev=19202，ticks 口径差 §6m99 在案）+「[selfcheck] run989_r18 同种子复跑逐字节一致」；py 腿 19202=gd 同数；compare 判 oracle≠gdcore（首分歧 index=446，渲染行 oracle 6.77「[对手] 1 致盲持续时间结束(燃烧旗帜)」vs gd 6.83「[对手] 消耗1 魔法（光之花）」）。④分歧归因（归一化 key：type+ts 数值感知 4 位+origin 语义元组+target+params，id 剥除）：语料 idx=400-445 与 gd 逐事件全等，首个分歧=语料 idx=446 独有事件（type=109 致盲到期 Burning Banner owner_type=3 amount=-1 @6.766667）而 gd 无此件→其后全程块漂移（公共窗 19202 中 18734 位置分歧，§6m100 run710 块漂移形而非 §6m101 同位微残件形）；且光之花致盲到期 amount 亦异（语料 1/-2 vs gd 2/-1）——盲池语义残迹与 §6m101 同族；**gd vs py 行为签名（type/ts/target/params 数值感知，origin 表形异文另计）0/19202 零分歧**——引擎双腿行为全等，零嫌疑。⑤决定性实验（§6m96/§6m100/§6m101 playbook）：`ORACLE_FIGHTS_ROOT=<repo>/output/oracle/probe/np46_run989_r18 python -X utf8 tools/_np46_rerecord.py --cases run989_r18`，wall=190s 一轮 PASS（pending 1→0）；探针件 status=ok+**winner=opponent**+combat_time=60.07+ticks=3604+event_count=19202=len(events) 本体自洽、末事件 112@60.066667；events.json≡events_first.json sha256 一致（f1635d7a…，harness 确定性自证）；**探针 vs gd 腿归一化全比 19202/19202 逐位置零分歧（含/不含 origin 双口径均零）**——证旧语料录制时的 harness 行为与现行 harness（及镜像现行 harness 的 gd_core/gd_core_py）不同，旧件整体作废，winner 翻转亦系旧 harness 行为非引擎回归，引擎零嫌疑。⑥发布：探针三件（events.json sha256 f1635d7a…/result.txt/rng_state.txt）cp 回 output/oracle/fights/run989_r18/，sha256 双侧逐一核对一致；lineups.json 语料/探针 sha256 相同（fb6c9dc6…，零回填必要）；发布后语料 len=19202/winner=opponent/末事件 112。⑦`--prepare` 重算长场夹具：**闸零变化**（run989_r18 py_ev_gate=25000 默认闸，重录前后 int(ev×1.2+1) 均<25000）——§6m98 坑一/坑二均不适用（旧语料即自然全长非截断形、闸未变故 py 产物合法温件且已由④行为零分歧独立裁定，未删）；整夹具快照 diff：54 场逐场 deep-equal **零分歧，唯 cases 列表顺序漂移**（夹具生成顺序不稳定，按 case_id 比对无实质差异，观察在案非缺陷）。⑧`--focus` 复跑翻绿：gd 腿 resume（2s，实跑 0 跳过 1，幂等合法——gd 腿只依赖夹具阵容不依赖语料，首跑产物已由⑤探针全等裁定）+py 腿 resume（1s），判「三方一致」19202/19202/19202。⑨`--prefix run989_r18` 收口：首轮全量定位分支→gd resume（2s，rc=0）→「已三方一致，无需迭代」exit=0（§6m99 假信号未踩——focus 先行；工具对绿场不记 progress.json）。⑩双验：gd 产物 output/oracle/align_long/gdcore/run989_r18/events.json=8,040,423 字节+py 腿 5,560,608 字节（均 >1KB，len=19202、winner=opponent、末事件 112@60.066667 双侧自洽）；本轮四份 gd 日志 focus_gd_focus_3744/3800/564_1.log+prefix_gd_pfx_8988_1.log 经 python str.count 核验「SCRIPT ERROR」均 0 命中（§6m90 口径）；探针 harness 日志 np46_r1_s0_14896_1.log（35.6MB，848 命中）按 §6m96 口径不构成缺陷（反编译期既有噪声，status=ok 且探针≡gd 19202 全等即正确性定谳）。
- **本场假设史（旧分歧记录作废口径）**：本场属「未验证（净化重录后无分歧数据）」簇。H1「语料 player 胜 vs 双腿 opponent 胜＝引擎回合/伤害语义回归需修」——排除（gd≡py 行为签名 0/19202+探针现行 harness≡gd 19202/19202 零分歧双证，现行 harness 亦判 opponent 胜，winner 翻转源自旧 harness 行为，残件在语料侧，见④⑤）；H2「语料 status=ok 三件自洽+自然终局（111 收尾）＝良品免检（§6m99 run902 同形预期）」——证伪（§6m100「自洽≠良品」第三例，且 111 自然终局≠行为现役，旧 harness 可整场异构仍自洽收尾）；H3「语料截断残件（run1409/run1362 timeout 形预期）」——排除（status=ok 自然终局、探针 event_count 19202 与 gd 恒同非闸截断形）；H4「夹具闸未抬致 py 伪分歧（§6m98 坑一预期）」——排除（py 19202=gd 同数非贴闸形，闸零变化）；H5「prefix 首轮长度型分歧假信号（§6m99 新坑）」——未踩（focus 先行）。最终动作=语料侧定向净化重录，零代码/零引擎/零夹具改动、无代码回滚面。**继 §6m87-95（九场零改动直绿）/§6m96（run1409）/§6m97（run1229_r11）/§6m98（run1362）/§6m99（run902）/§6m100（run710）/§6m101（run629）之后第 16 场翻绿、第 6 场语料侧修复、「自洽陈旧件」形第 3 例（run989 与 run710/run629 同 Oct31 12:xx 批次；新亚形在案：winner 翻转——三件自洽+自然终局+winner 字段可整体承载旧 harness 异构行为，凡未验证簇 Oct31 冻结件不得以任何本体特征免检，唯对拍+探针可定谳）**。
- **边界**：长场产物/报告/探针目录均在 output/（.gitignore 内）不入库，本节为唯一入库产出；语料树改动仅 run989_r18 三文件（备份 fights_pre_npur_20261106 留旧态可回滚，sha256 已核对）；红线三文件 §6m86 悬置 diff（verify_oracle.py 34/28、OracleAlignBattle.gd 25/44，本轮 diff --numstat 数值不变）零触碰零并入；主夹具 860 场与主账 alignment.json 未动；guide 本身未改。

## 6m103. ★ np45 长场 run1371_r18：「timeout 截断残件 × np22 收割键控未随 np46 退役」双因残件（Oct31 13:39 旧 harness M12 墙钟截断录件，与 run1362 13:43 同分钟批次；情报『语料已净化重录 2026-11-06』不成立；引擎侧唯一改动面=长场重放器摘一键）→ 定向净化重录 + 长场夹具闸重算后翻绿（26356事件；新在案：主重放表/py 表 np46 清空时漏了长场副本 OracleAlignBattleLong.gd，键控补偿对 np46 新录件反成分歧源）（2026-11-06 长场修复 run1371_r18 p1）

- **结论**：run1371_r18 情报所述「语料已净化重录（2026-11-06，harness 逐案隔离+事件闸全长）」对本场**不成立**——实测语料 mtime Oct31 13:39:xx、result.txt 无 [M13] 标记、status=**timeout**/winner=-/ticks=3439<5400/combat_time=57.32/event_count=20042=len(events)、player_hp=3927/350 opponent_hp=3779/350 双方均存活、末事件 type=109 @57.32 非自然终局——旧 harness [M12] 单场墙钟 60s 闸截断形（§6m96 run1409/§6m98 run1362 同族），且系**非纯截断**：旧语料 vs gd 归一化逐位置仅 518/20042 对齐、首分歧 idx=426（§6m98 双重陈旧形）。定向净化重录（np46 probe 根 wall=225s 一轮 PASS，pending 1→0 shard_rc=[0]）产 **26356** 事件 status=ok/winner=player/combat_time=69.02/ticks=4141 自然终局 111@69.016667、events≡events_first sha256 一致（cb47c778…，harness 确定性自证）。但**探针≡gd 归一化全比非零分歧**：26356 件公共窗仅 1 处行为分歧 idx=4203（type=106 Empower 到期，Carrot Goobert tgt=0 @20.666667，探针 amount=-1 vs gd **-2**）+20 处 origin 表形异文（GemSocket vs GemSocket2 gem host str，type=105/110 成对，语义同位非行为）——本轮首见「重录后探针 vs gd 仍有单点真分歧」，归因不在引擎本体而在**长场重放器键控补偿**：gd_core_test/OracleAlignBattleLong.gd PERM_STACK_HARVEST 表仍留 np22 时代键 run1371_r18（np46 净化时主重放表 OracleAlignBattle.gd:86 与 py 表 verify_oracle.py:81 PY_PERM_STACK_HARVEST 均已清空，**唯长场副本漏同步**），其暖场收割残差 {106:1} 灌入正式场→12.866667 Fedora 偷取清洗（语料 idx1799 @12.85）走 loseStacks「先永久」支吃掉该 1 永久叠（BLND 面零 lose/partial 行），20.666667 到期批保持 2 叠→到期事件 -2，而 np46 干净录件（[M13] PERM 片每执行前双侧全 buff permanentStacks=0）同笔清洗 partial 吃最远临时批 2@20.666667→1→到期 -1。摘键后 gd 腿 13s 重放（ticks=4292）+selfcheck 同种子逐字节一致，`--focus` 判**三方一致** 26356/26356/26356 winner=player×3 firstDivergence=null（output/oracle/long_alignment.json total=1 aligned=1 独立账面，未并入 alignment.json）；`--prefix` 收口「已三方一致，无需迭代」exit=0。本场改动面=**语料三文件（output/ 不入库）+长场重放器摘一键+长场夹具闸一场重算**；主引擎四树零改动。
- **判据与实测（本轮亲跑）**：①语料旧件核：mtime Oct31 13:39、len(events)=20042=event_count 自洽、status=timeout winner=-、末事件 109@57.32；备份 fights_pre_npur_20261106/run1371_r18 四件与旧语料 sha256 逐一相同（events bde34196…/result 33a38489…/rng_state 044a0522…，回滚面在位）。②夹具闸旧值=25000 默认闸（int(20042×1.2+1)=24051<25000，闸源=截断语料——§6m98 坑一面）；--focus 首跑三腿：oracle 20042 / gd 26356（自然全长，winner=player 末 111@69.016667）/ py **25027 贴闸**（winner=opponent 默认、末事件 type=0 @66.6 mid-fight 硬切——坑一指纹四件套齐）。③决定性实验（§6m96 playbook）：`ORACLE_FIGHTS_ROOT=<repo>/output/oracle/probe/np46_run1371_r18 python -X utf8 tools/_np46_rerecord.py --cases run1371_r18`，wall=225s 一轮 PASS；探针件 status=ok+winner=player+combat_time=69.02+ticks=4141+event_count=26356=len(events) 本体自洽、末事件 111@69.016667；events.json≡events_first.json sha256 一致（cb47c778…）。④探针 vs gd 归一化（key=type+ts 数值感知 4 位+target+params，id 剥除）：**1/26356 行为分歧** idx=4203（探针 -1 vs gd -2，同位同型同 origin 仅 amount 异）；含 origin 双口径另现 20 处 GemSocket/GemSocket2 表形异文（全部 type=105/110 相邻对、同 kind=gem 同 socket_index，非行为面）。⑤分歧归因（harness 账本考古）：探针 harness 日志 np46_r1_s0_4320_1.log（54MB，暖场+正式+复跑三执行）正式场 `[BCLEANSE] t=12.866667 type=106 side=0 amt=1 pick_to=20.666667 pick_amt=2 n=7`——Fedora 偷 1 叠走「先永久」支不触发（永久=0）、吃最远临时批 2@20.666667 partial→1；该批 @12.666667 gain amt=2 dur=8 to=20.666667（语料 idx1741）为唯一来源，账目自洽。⑥gd 侧铁证：ORACLE_ALIGN_TRACE=1+ORACLE_ALIGN_STACKTRACE=1 scratch 跑 gd 腿（events.json sha256 6d43cf2c… 与正式 gd 产物**逐字节一致**→追踪零行为面），BLND p0 ty106 序列 fire@12.8(fr=768)→**无任何 lose/partial 行**→gain@13.233333(fr=794)：清洗被 permanentStacks≥1 吸收；且 focus 日志 `[perm-harvest] run1371_r18 暖场 status=ok 永久栈={100:0,101:1,102:55,103:3,104:0,105:313,106:1,107:96,108:0,109:0,110:0}`——旧键注入实证。⑦机理核：OracleAlignBattleLong.gd:84-92 表含 run1371_r18（np22 注「重录两场 exec3 携带 exec2 终局 permanentStacks 残留」）vs OracleAlignBattle.gd:86-89 np46 清空注「run702/1022/1371/1444 旧键已随旧语料退役」vs verify_oracle.py:78-81「np46 净化重录后清空（与 gd 宿主同步）PY_PERM_STACK_HARVEST={}」——主表/py 表 2026-11-06 已清、**长场副本漏网**；harness 侧 oracle_fight.gd reset_residual_state PERM 片（`chr.buffs[bt].permanentStacks = 0`）即新录件干净性的 by-construction 保障。⑧单点性解释：empowerDamage 本阵容默认 0（无 changeEmpowerDamage 调用者，CoreCharacter.gd:1667 getEmpower()*empowerDamage 零可见面），注入的 {101:1,102:55,103:3,105:313,107:96} 与 106:1 在全场的唯一可见面即此一笔清洗吸收——故 26356 件仅 1 处分歧（run696「残差零可见面」同构、本场=残差单可见面形）。⑨修复：OracleAlignBattleLong.gd 表摘 `"run1371_r18": true` 键（精确字符串替换，guide §7 规矩；np22 注块补 np47 摘键注），run702/1022/1444 三键**保留**（实测三场语料均无 [M13] 仍系旧录件，键控面继续有效）；该文件单副本无四树镜像面、非 gd_to_py 翻译面（grep 证），零重生成。⑩发布：探针三件（events.json 10,613,213B sha256 cb47c778…/result.txt/rng_state.txt 044a0522… 与旧语料同值）cp 回 output/oracle/fights/run1371_r18/，sha256 双侧逐一核对一致；lineups.json 语料/探针 sha256 相同（d02309e0…，零回填必要）。⑪`--prepare` 重算长场夹具：54/0 场，run1371_r18 py_ev_gate 25000→**31628**（=int(26356×1.2+1)，闸源随重录件修正——坑一修复）；其余 53 场闸零变化。⑫删旧产物三面：gdcore/run1371_r18（旧键控行为件——gd 腿 resume 只看夹具阵容对**代码变化**失明，§6m98 坑二同构面+1）、py/run1371_r18（贴闸截断件，坑二原文）、gdcore/_np18_permwarm/run1371_r18（旧键控暖场非正式残留，本场情报已标明）+本轮 _trace_gd scratch。⑬`--focus` 复跑翻绿：gd rc=0（13s，ticks=4292 t=69.02 ev=26356，实跑 1+selfcheck 复跑）+「[selfcheck] 同种子复跑逐字节一致」+**零 perm-harvest 行**；py 腿 4s 产 26356（新闸 31628 未触）；判「三方一致」1/1。⑭`--prefix` 收口：「账本无记录先全量定位」→gd resume 2s rc=0→「已三方一致，无需迭代」exit=0（§6m99 假信号未踩——focus 先行）。⑮双验：gd 产物 10,843,167B / py 产物 7,248,931B（均 >1KB，len=26356、winner=player、末事件 111@69.016667 三腿自洽）；本轮四份 gd 日志（tracedbg_gd_tracedbg_6972_1/focus_gd_focus_6804_1 翻绿轮/prefix_gd_pfx_2264_1/focus_gd_focus_7132_1 修复前轮）python str.count 核验「SCRIPT ERROR」均 0 命中（§6m90 口径）；探针 harness 日志 np46_r1_s0_4320_1.log（54MB，279 命中）按 §6m96 口径不构成缺陷（反编译期既有噪声，status=ok 且探针≡gd 26355/26356+摘键后三方全等即正确性定谳）。⑯红线核：`git diff --numstat tools/verify_oracle.py gd_core_test/OracleAlignBattle.gd` → 34/28、25/44 = §6m86 悬置值**数值不变**零触碰；主夹具 860 场与主账 alignment.json 未动。
- **本场假设史（旧分歧记录作废口径）**：本场属「未验证（净化重录后无分歧数据）」簇。H1「语料已净化重录＝真（ask 情报）」——证伪（mtime Oct31 13:39 在净化批窗口外、无 [M13]、status=timeout 截断形，§6m100-102 同款情报失实第四例）；H2「timeout 截断残件→重录即绿（run1409 形预期）」——部分证伪（重录后探针 vs gd 仍单点真分歧，引出 H3）；H3「探针≠gd＝引擎 Buff 到期/loseStacks 语义 bug 需修四树」——证伪（gd_core/CoreBuff.gd 与 oracle/Core/Buff.gd 逐行同构在案 §6m100④，分歧源=宿主侧长场重放器键控注入非引擎，单文件摘键即闭合零镜像面）；H4「py 25027 件＝py 引擎分歧」——证伪（贴闸截断形，坑一：闸源=截断语料 20042，重算 31628 后 py 自然全长）；H5「四键全摘」（表内 702/1022/1444 同步退役）——否（三场语料实测无 [M13] 仍需键控，仅摘本场，防误伤）；H6「prefix 首轮长度型假信号（§6m99 新坑）」——未踩（focus 先行）。最终动作=语料侧定向净化重录+长场重放器摘一键+夹具闸重算+删新旧产物，主引擎四树零改动、无代码回滚面（摘键前状态见 git 历史/本节⑨）。**继 §6m87-95（九场零改动直绿）/§6m96（run1409）/§6m97（run1229_r11）/§6m98（run1362）/§6m99（run902）/§6m100（run710）/§6m101（run629）/§6m102（run989）之后第 17 场翻绿、第 7 场语料侧修复；新在案两条：①「净化批漏长场副本」——np46 清空键控表时主重放/py 表清了、OracleAlignBattleLong.gd 漏了，凡主表已清的键在长场副本中一律视为待核（未重录键保留、已重录键摘除）；②「键控补偿对重录件反成分歧源」——收割/闩锁类键控是**旧录件残差的同构复刻**，语料一旦换血立即反转成 gd 侧伪差，未验证簇长场凡探针 vs gd 出「同位同型仅 amount 异」单点分歧且 gd 侧涉 loseStacks/清洗路径者，先查键控表再查引擎。**
- **边界**：长场产物/报告/探针目录均在 output/（.gitignore 内）不入库，本节为唯一入库产出；语料树改动仅 run1371_r18 三文件（备份 fights_pre_npur_20261106 留旧态可回滚，sha256 已核对）；代码改动仅 gd_core_test/OracleAlignBattleLong.gd 一文件一字符串段（未跟踪新文件，摘键面无镜像无重生成）；红线三文件 §6m86 悬置 diff（verify_oracle.py 34/28、OracleAlignBattle.gd 25/44，本轮 diff --numstat 数值不变）零触碰零并入；主夹具 860 场与主账 alignment.json 未动；guide 本身未改。

## 6m104. ★ np45 长场 run1241_r18：**零改动直绿**（Oct31 13:15 冻结件三腿对拍即现行行为；情报『语料已净化重录 2026-11-06』不成立第五例——备份在册但 np46 重录名单未含本场）（19580事件；新在案：备份名单≠重录名单）（2026-11-06 长场修复 run1241_r18 p1）

- **结论**：run1241_r18 情报所述「语料已净化重录（2026-11-06，harness 逐案隔离+事件闸全长）」对本场**不成立**——实测语料 mtime Oct31 13:15:21（净化批 11-06 04:03-04:35 窗口外），备份 fights_pre_npur_20261106/run1241_r18 四件与现语料 sha256 逐一相同且 mtime 未变（批只备份、未写入本场），probe 无 np46_run1241_r18 目录（np46 实际重录=1362/1371/1409/629/710/989 六场、不含本场）——§6m100-103 同款情报失实**第五例**。但与「自洽陈旧件」三例（§6m100-102）走向相反：本件 Oct31 13:15 冻结件（status=ok/winner=player/末事件 111@43.383333 自然终局/19580=event_count 三件自洽，与 run1371 13:39 同 Oct31 13:xx 批次）按 §6m99 playbook `--focus` 首跑三腿**直接翻绿**——语料=gd_core=gd_core_py **19580/19580/19580**、winner=player×3、firstDivergence=null（output/oracle/long_alignment.json total=1 aligned=1 独立账面，未并入 alignment.json），`--prefix` 收口 exit=0，**全场零改动**（§6m99 run902 同形：Oct31 冻结件可即现行行为；但免检资格由对拍本体给予，非本体特征自证）。
- **判据与实测（本轮亲跑）**：①语料本体核：result.txt status=ok/winner=player/combat_time=43.38/ticks=2603<5400/event_count=19580=len(events)、player_hp=1972/350 opponent_hp=0/350、末事件 type=111 @43.383333 自然终局；mtime Oct31 13:15:21；备份四件（events ed6b88e2…/result 4cdce164…/rng_state 25334856…/lineups b5abaa1e…）与现语料 sha256 逐一相同且 mtime 原样。②夹具 py_ev_gate=25000 默认闸正确（int(19580×1.2+1)=23497<25000）——坑 2 常规核验；无 progress.json、无双腿旧产物系全新场。③`--focus` 首跑三腿定谳：gd 腿 rc=0（10s，ticks=2754 t=43.38 ev=19580，实跑 1 跳过 0；ticks 口径差 §6m99 在案，事件流方为通货）+「[selfcheck] 同种子复跑逐字节一致」；py 腿 19580 同数（3s）；判「三方一致」19580×3。④`--prefix` 收口：「账本无记录先全量定位」→gd resume 2s rc=0→「已三方一致，无需迭代」exit=0（§6m99 假信号未踩——focus 先行；工具对绿场不记 progress.json，该文件仍不存在）。⑤双验：gd 产物 output/oracle/align_long/gdcore/run1241_r18/events.json=8,183,607B / py 腿 5,519,372B（均 >1KB，len=19580、winner=player、末事件 111@43.383333 双侧自洽，py 浮点尾差 43.38333333332… 系 py float 表示 §6m101 在案）；本轮 gd 日志 focus_gd_focus_4508_1.log（1166B 含 selfcheck）/prefix_gd_pfx_9464_1.log（609B resume）python str.count 核验「SCRIPT ERROR」均 0 命中（§6m90 口径）。⑥红线核：`git diff --numstat tools/verify_oracle.py gd_core_test/OracleAlignBattle.gd` → 34/28、25/44 = §6m86 悬置值**数值不变**零触碰；主夹具 860 场与主账 alignment.json 未动。
- **本场假设史（旧分歧记录作废口径）**：本场属「未验证（净化重录后无分歧数据）」簇。H1「语料已净化重录＝真（ask 情报）」——证伪（mtime Oct31 13:15 在净化批窗口外、备份逐字节相同且 mtime 未变=批未写入、probe 无本场 np46 目录=重录名单未含，情报失实第五例）；H2「Oct31 13:xx 批次（与 run1371 13:39 同期）＝自洽陈旧件必分歧（§6m100-103 预期）」——排除（三腿对拍直接全等：冻结件≠必然陈旧，本件录制 harness 行为与现行引擎恰一致；「自洽≠良品」警示仍有效——本场免检系对拍定谳非本体特征）；H3「夹具闸未抬致 py 伪分歧（§6m98 坑一预期）」——排除（py 19580=gd 同数非贴闸形，闸零变化）；H4「prefix 首轮长度型假信号（§6m99 新坑）」——未踩（focus 先行）。最终动作=**零**（零代码/零引擎/零夹具/零语料改动、无回滚面）。**继 §6m87-95（九场零改动直绿）/§6m96（run1409）/§6m97（run1229_r11）/§6m98（run1362）/§6m99（run902）/§6m100（run710）/§6m101（run629）/§6m102（run989）/§6m103（run1371）之后第 18 场翻绿、零改动直绿再 +1；新在案一条：「备份名单≠重录名单」——fights_pre_npur_20261106 备份覆盖面大于 np46 实际重录六场，凡备份目录有件而 probe 无 np46_dir 者，情报『已净化重录』一律视为未证实，先核 mtime+probe 目录再定族（本场=「名单外冻结件恰为良品」形，与 run902 同族但补证：同 Oct31 13:xx 批次内良品/残件并存，批次特征不可外推到件）。**
- **边界**：长场产物/报告均在 output/（.gitignore 内）不入库，本节为唯一入库产出；本轮零改动（语料/代码/夹具/引擎四树全未触碰，工作树仅既有悬置项+本 ledger 节）；红线三文件 §6m86 悬置 diff（verify_oracle.py 34/28、OracleAlignBattle.gd 25/44，本轮 diff --numstat 数值不变）零触碰零并入；主夹具 860 场与主账 alignment.json 未动；guide 本身未改。

## 6m105. ★ np45 长场 run619_r18：「自洽陈旧件」第四例+**winner 翻转第二例**（Oct31 12:02 旧 harness 盲池语义录件，与 run629 12:03 同分钟批次、情报『已净化重录』第六例失实）→ 定向净化重录后翻绿（19535事件；语料侧修复，零代码改动）（2026-11-06 长场修复 run619_r18 p1）

- **结论**：run619_r18 情报所述「语料已净化重录（2026-11-06，harness 逐案隔离+事件闸全长）」对本场**不成立**——实测语料 mtime Oct31 12:02:xx（净化批 11-06 04:03-04:35 窗口外），备份 fights_pre_npur_20261106/run619_r18 四件与现语料 sha256 逐一相同且 mtime 未变（批只备份未写入，§6m104 名单口径），probe 无 np46_run619_r18 目录（np46 实际重录六场不含本场），result.txt 无 [M13] 标记——§6m100-104 同款情报失实**第六例**。本件 Oct31 12:02 冻结件（status=ok/winner=player/combat_time=49.02/ticks=2941<5400/event_count=19077=len(events)、player_hp=664/350 opponent_hp=0/350、末事件 111@49.016667 自然终局三件自洽）按 §6m99 playbook `--focus` 首跑三腿**oracle≠gdcore**：19077 vs **19535**（gd=py 同数）、**winner 翻转**（语料 player 胜 vs gd/py 双腿 opponent 胜，§6m102 run989 同族第二例）、首分歧 idx≈307（渲染行 5.57s「[对手] 7 致盲持续时间结束(光之黏黏)」vs gd「5 致盲」，同位同型仅 amount 异的致盲到期面，§6m101 run629 微残件同族）；gd_core_test/OracleAlignBattleLong.gd PERM_STACK_HARVEST 表无 run619 键（键控面排除，§6m103 新在案①先查）。定向净化重录（np46 probe 根 wall=150s 一轮 PASS，pending 1→0）产 **19535** 事件 status=ok/**winner=opponent**/combat_time=49.35/ticks=2961 自然终局 112、[M13] 标记在位、events≡events_first sha256 一致（069f0c17…，harness 确定性自证）；**探针 vs gd 归一化全比双口径零分歧**（key=type+ts 4 位数值感知+target+params，id 剥除：不含 origin 0/19535、含 origin 亦 0/19535——本场连表形异文都没有，§6m103 的 20 处 GemSocket 形本场为零）→ 旧语料整体作废定谳。发布探针三件回语料（sha256 双侧逐一核对一致；lineups.json 语料/探针 sha256 相同 c1ec3739… 零回填必要）→ `--prepare` 重算长场夹具 **闸零变化**（int(19535×1.2+1)=23443<25000 默认闸，且 54 场逐一比对零变化——坑一/坑二均不适用）→ `--focus` 复跑**三方一致** 19535/19535/19535 winner=opponent×3 firstDivergence=null（output/oracle/long_alignment.json total=1 aligned=1 独立账面，未并入 alignment.json）→ `--prefix` 收口「已三方一致，无需迭代」exit=0。本场改动面=**语料三文件（output/ 不入库）**，零代码/零引擎/零夹具闸改动。
- **判据与实测（本轮亲跑）**：①语料旧件核：mtime Oct31 12:02、len(events)=19077=event_count 自洽、status=ok/winner=player、末事件 111@49.016667、无 [M13]；备份四件（events b11dbe65…/result 6249d106…/rng_state d81c26cd…/lineups c1ec3739…）与旧语料 sha256 逐一相同且 mtime 原样（回滚面在位）。②夹具 py_ev_gate=25000 默认闸（int(19077×1.2+1)=22893<25000）——坑 2 常规核验；无 progress.json、无双腿旧产物系全新场。③`--focus` 首跑三腿定谳：gd 腿 rc=0（11s，ticks=3112 t=49.35 ev=19535，实跑 1+selfcheck「同种子复跑逐字节一致」；ticks 口径差 §6m99 在案）+py 腿 19535 同数（6s）；判 oracle≠gdcore、首分歧渲染行如上。④gd≡py 双证：归一化 key（type+ts 数值感知+target+params，id/type_name 剥除）不含 origin **0/19535** 零分歧、含 origin 384/19535 全部为 damage_source keyword dict（py）vs int 99（gd）及 item name/identifier 表形异文非行为——引擎双腿行为全等，零嫌疑（§6m103 口径）。⑤键控面排除：OracleAlignBattleLong.gd PERM_STACK_HARVEST 表（L84-96）仅 run702/1022/1444 三键（run1371 已 §6m103 摘除），grep run619 零命中——§6m103 新在案②「先查键控表再查引擎」照办，非键控伪差。⑥决定性实验（§6m96 playbook）：`ORACLE_FIGHTS_ROOT=<repo>/output/oracle/probe/np46_run619_r18 python -X utf8 tools/_np46_rerecord.py --cases run619_r18`，wall=150s 一轮 PASS；探针件 status=ok+winner=opponent+combat_time=49.35+ticks=2961+event_count=19535=len(events) 本体自洽、player_hp=0/350 opponent_hp=119/350、末事件 112@49.35 自然终局、[M13] 在位；events.json≡events_first.json sha256 一致（069f0c17…）。⑦探针 vs gd 归一化双口径零分歧（同④口径：不含 origin 0/19535+含 origin 0/19535）——现行 harness 行为≡现行引擎双腿，winner 翻转源自旧 harness 行为非引擎回归，旧件整体作废（§6m102 同构定谳路径）。⑧发布：探针三件（events.json sha256 069f0c17…/result.txt 20f046df…/rng_state.txt d81c26cd… 与旧语料同值）cp 回 output/oracle/fights/run619_r18/，sha256 双侧逐一核对一致；lineups.json 语料/探针 sha256 相同（c1ec3739…，零回填必要）。⑨`--prepare` 重算长场夹具：54/0 场，**闸零变化**（run619_r18 与全部 53 场逐一比对 py_ev_gate 均不变，int(19535×1.2+1)=23443<25000 默认闸仍正确）；gd/py 旧产物未删（零代码改动+闸未变，resume 对现状合法幂等——§6m103 ⑫删面两因均不适用）。⑩`--focus` 复跑翻绿：gd 腿 resume（2s，实跑 0 跳过 1，幂等合法）+py 腿 resume（1s），判「三方一致」19535×3；报告 perCase winner={oracle:opponent, gdcore:opponent, py:opponent}、firstDivergence=null、event_tuples/rendered_lines 双 true。⑪`--prefix` 收口：「账本无记录先全量定位」→gd resume 2s rc=0→「已三方一致，无需迭代」exit=0（§6m99 假信号未踩——focus 先行）。⑫双验：gd 产物 output/oracle/align_long/gdcore/run619_r18/events.json=8,306,004B / py 腿 5,637,252B（均 >1KB，len=19535、winner=opponent、末事件 112 双侧自洽，py 浮点尾差 49.34999999999… 系 py float 表示 §6m101 在案）；本轮 gd 日志 focus_gd_focus_10336_1.log（1167B 含 selfcheck）/focus_gd_focus_14368_1.log（612B resume）/prefix_gd_pfx_4332_1.log（609B resume）python str.count 核验「SCRIPT ERROR」均 0 命中（§6m90 口径）；探针 harness 日志 np46_r1_s0_15632_1.log（30.1MB，1396 命中）按 §6m96 口径不构成缺陷（反编译期既有噪声，status=ok 且探针≡gd 19535 双口径全等即正确性定谳）。⑬红线核：`git diff --numstat tools/verify_oracle.py gd_core_test/OracleAlignBattle.gd` → 34/28、25/44 = §6m86 悬置值**数值不变**零触碰；主夹具 860 场与主账 alignment.json 未动；引擎四树零改动（git status 引擎树仅既有悬置项+既有未跟踪件）。
- **本场假设史（旧分歧记录作废口径）**：本场属「未验证（净化重录后无分歧数据）」簇。H1「语料已净化重录＝真（ask 情报）」——证伪（mtime Oct31 12:02 在净化批窗口外、备份逐字节相同且 mtime 未变=批未写入、probe 无本场 np46 目录、无 [M13]，情报失实第六例，§6m104「备份名单≠重录名单」口径照办）；H2「Oct31 12:xx 批次（run629 12:03 同分钟、run710 12:08、run989 12:41）＝必分歧」——成立（三腿对拍即分歧；本场=该批次第 4 场检出、「自洽陈旧件」第 4 例）；H3「winner 翻转＝引擎回合/伤害/致盲语义回归需修四树」——证伪（gd≡py 不含 origin 0/19535+探针现行 harness≡gd 双口径 0/19535 双证，现行 harness 亦判 opponent 胜，翻转源自旧 harness 盲池语义，残件在语料侧）；H4「语料 status=ok 三件自洽+自然终局＝良品免检」——证伪（§6m100「自洽≠良品」第 4 例；winner 字段再次整体承载旧 harness 异构行为）；H5「长场重放器键控注入伪差（§6m103 形）」——排除（表无 run619 键）；H6「夹具闸未抬致 py 伪分歧（坑一）」——排除（py 19535=gd 同数非贴闸形，重录后闸重算仍零变化）；H7「prefix 首轮长度型假信号（§6m99）」——未踩（focus 先行）。最终动作=语料侧定向净化重录+发布，零代码/零引擎/零夹具改动、无代码回滚面。**继 §6m87-95（九场零改动直绿）/§6m96（run1409）/§6m97（run1229_r11）/§6m98（run1362）/§6m99（run902）/§6m100（run710）/§6m101（run629）/§6m102（run989）/§6m103（run1371）/§6m104（run1241）之后第 19 场翻绿、第 8 场语料侧修复、「自洽陈旧件」第 4 例、winner 翻转第 2 例（run989 同族）；批次口径更新：Oct31 12:xx 批次四场（run619/run629/run710/run989）现已全部检出残件并翻绿，该批次无良品例外（run1241 13:15 例外属 13:xx 批次）。**
- **边界**：长场产物/报告/探针目录均在 output/（.gitignore 内）不入库，本节为唯一入库产出；语料树改动仅 run619_r18 三文件（备份 fights_pre_npur_20261106 留旧态可回滚，sha256 已核对）；零代码/零引擎/零夹具改动（guide 本身未改）；红线三文件 §6m86 悬置 diff（verify_oracle.py 34/28、OracleAlignBattle.gd 25/44，本轮 diff --numstat 数值不变）零触碰零并入；主夹具 860 场与主账 alignment.json 未动。

## 6m106. 工作流（np45/np46）收尾移交：两代 run 终态、np46 悬置面、热循环事故与接续图纸（2026-11-06 用户指令收尾）

- **本工作流（dwfrun 系列 3 代）总战果**：986 定谳链 §6m71-75（四轮证据+铁律9停，commit 6aa32706→4f008601）；用户批准净化重录后 np46 主体落地——harness 逐案隔离改造（[M13] 标记+确定性自证）、备份 fights_pre_npur_20261106、键控面退役（本 commit 并入：gd 宿主 WARM_LATCH_PLAYERS/PERM_STACK_HARVEST/PERM_STACK_OVERRIDE 清空+PY_ 镜像同步+_np46_rerecord.py 假门修正[case_done 要求 result.txt 含 [M13]，防旧语料 10 秒假 PASS]、PY_WARMUP_TIME_TICKS 等其余 PY_ 表按同口径清空）；54 长场 **19 场翻绿**（§6m87-105：零改动直绿 9+定向重录翻绿 8+键控摘除 1+零改动 1，全部 probe≡gd 归一化双口径定谳）；新坑入册 12+ 条（§6m96-105：py_ev_gate 按截断语料/resume 对代码变化失明/prefix 首轮只跑 gd/自洽≠良品/备份名单≠重录名单/键控补偿语料换血后反转成伪差等）。
- **np46 现状（未闭合，接续第一要务）**：批量 status=FAIL（_batch_summary），实际全量重录未完成——截至收尾 probe 名单仅 1362/1371/1409/629/710/989 六场+长场子代理定向补录数场（run619 等），**主夹具 860 场语料大部分仍为 Oct31 旧件**。本 commit 并入的键控清空使工作树进入「键控退役 vs 语料混合态」：run702/1022/977/1444/1120 等键控依赖场对旧语料预期红——**860 基线在当前工作树挂起**，接续必须先跑完 np46 全量重录（tools/_np46_rerecord.py 可续跑+假门已修）→ 回补基线（夹具再生+gd+py 全量+比对）→ 再谈全绿。接续第一动作=核 WARMUP_TIME_TICKS/BUFF_STOP_CLEARS_SEEN/CLEANSE_BIGGEST_FIRST/NP22_REC_EV_GATE 及全部 PY_ 镜像的清空完整性（§6m103 漏长场副本前科）。
- **热循环事故（设计失误，入册防重蹈）**：工作流 phase2.6 复用 986修复员（上下文已 ~40M tokens）→ 每次必 ContextLimit → askFixRound 兜底返回「ask 异常」且循环无连续失败中止 → ~1000 轮空转刷 report（reports[8]-[1096] 全垃圾）+烧配额（provider 1005 两度耗尽的帮凶）。教训三条：①工作流子代理单上下文寿命有限，长循环必须换名重建（缓存键=名字+逐字节 ask）；②ask 兜底必须计数中止（如连续 3 次 ask 异常即 break+如实上报）；③回补基线门不得只查 json 可加载，必须查 aligned==860。
- **接续图纸（offpeak 任务书已下）**：①核键控清空完整性→②np46 全量重录续跑（917 场，[M13] 假门已修，wall 数小时）→③回补基线（--force 全量，预期红场=键控退役后旧语料场，若重录完整应全绿；残余红场按引擎真 bug 修）→④860/860→⑤P4 收口（compare-only/r55 快照/台账收口节/README/commit/push）→⑥54 长场剩余 ~35 场循环攻（§6m99 playbook：focus 先行+双验+键控表先查；定向重录授权已由净化重录批准覆盖）→⑦终局 914 全量口径战报。
- **边界**：本收尾 commit=悬置 np46 面（键控清空×2 文件+假门修正+本节）一次性入库；alignment.json/主夹具/语料树收尾时零改动；红线纪律对 verify_oracle.py/OracleAlignBattle.gd 的**逻辑**仍禁改（本 commit 仅键控表注释化清空，np46 获批面）。

## 6m107. np47 接力开工：np48 现状侦查+860 定向重录续跑（2026-11-06 offpeak np47）

- **np48 现状侦查**：本会话压缩台账（a75a0264）+①键控核（af062a6c：主重放器+verify_oracle 全清 ✓）之后，另一执行体已推进 np48 四 commit——94c4c435 长场工具链+Godot 静默压制（屏外+看门狗）+启动点静态检查、a9bc3fba 长场重录 `long_case_fix.py --record` 分档（确定性自证只对 cases[0] 付成本）+LPT 并行、4d491b4a 卡死自动重跑（日志停滞判据）+窗口置顶（用户点窗口冻结问题的工具层解）、8bc99758 文档。**台账此前无 np48 节，本节补记。**
- **fights_np46 清点**：141 目录，137 场 [M13]+ok 完成（860 主夹具 129/860；54 长场 8/54），4 残场（run575_r18/run734_r18/run753_r15/run771_r18 无 result.txt=被杀残件，续跑自动重录覆盖）。
- **续跑**：`_np46_rerecord.py --cases <860 清单>`（ORACLE_FIGHTS_ROOT=fights_np46，resume 幂等，129 跳过）后台进行；完成后续 54 长场用 np48 的 `--record` 入口（分档+并行省自证成本）。
- **纪律不变**：重录完成后→NP22_REC_EV_GATE 按新 event_count 再生→原子换目录→回补基线（--force）→860/860→P4→54 长场剩余。

## 6m108. np47②③完成：914 净化语料换目录+闸再生+回补基线 876/914（38 红两簇）（2026-11-07 offpeak np47）

- **np46 全量重录收口**：860 主夹具定向重录 PASS（fights_np46，resume 三段累计 wall≈80min，速率 ~9.7 场/分）；54 长场经 np48 --record 分档+并行完成（53 场 [M13]+status=ok + run1374 探针单录 37968 事件自然终局——批量段内 lockup@tick2579 系内存压力伪障，单场路径 §6m77 同证可录）。**内存闸血训并入 guide §9.7 模型**：自动推导 5999MB 对全长场低估（截断语料场全长更长，实测峰值 6GB+），batch=2+显式 9000MB 稳过；看门狗「日志停滞」判据会被错误循环刷屏打败（rec0_0 段 run1374 lockup 后 deferred 回调风暴刷 2.6GB 日志永不触发停滞判据）——刷屏型卡死需「日志增长率」或墙钟硬闸兜底（下轮工具改进项）。
- **914 语料原子换目录**：tools/_np47_swap_rebase.py（自校验 860 [M13]+ok + 54 两源取优 + 备份在位）→ fights = np46 干净语料 914 场（旧件 → fights_pre_np47_swap_backup；初始备份 fights_pre_npur_20261106 不动）。坑修正：短场合法事件数可 <100（r2/r1 轮 36/47 事件），validity 阈值 >100 误杀 21 场——schema 校验（events 列表≥1）替代行数阈值。
- **NP22 闸再生**：914 全量扫描 → >25000 共 20 场（=54 长场全长件）→ gd 宿主+PY 镜像同表 200000。教训：第一版只扫 860 主夹具漏长场 → 20 场长度型伪红（idx=None）——闸扫描必须跟 fixture 口径一致。
- **夹具升 914**：gen_fixtures(select_cases(0)) → oracle_align_cases.json=914 场（本 commit 入库=新基线口径；P4 §6「唯一出口 alignment.json 914 行」回归本位）。
- **回补基线（914 口径）**：verify --force 全量 → **876/914**（118.6s compare）。38 红=两簇：①20 长场 idx=None 长度型（闸漏扫伪红，已随闸再生修复，待重跑腿）②18 主夹具真引擎分歧（净化语料暴露的真 bug，修复循环主菜：run578/602/618/622/628/775/846/848/899/928/933/977/981/984/1094/1487/1491/1507——签名含 ty106/102 型混、Amulet Dark/Light 件身份、Miss Fortune amt 差、Storage Coffin 8-tick 相移等）。
- **红线核对**：verify_oracle.py/OracleAlignBattle.gd 本轮仅键控表面再生成（np46 获批面）；语料树=np46 授权重录面。
