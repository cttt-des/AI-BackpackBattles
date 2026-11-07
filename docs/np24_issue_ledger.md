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

## 2. 当前状态与交接（2026-11-07 np49 压缩更新；现行期总账=§6m63-6m110 压缩版，唯一任务书）

- **主账 912/914**：残红 run602_r14+run1094_r9；统一根因、接续第一步、914 刷账与全绿后 P4 收口链全在**现行期总账节（§6m63-6m110）A/B 节**。
- **唯一出口** output/oracle/alignment.json（禁手写，只由 verify_oracle 产出）；54 长场独立账 output/oracle/long_alignment.json（54 场全绿）。
- **历史全文**：本文件已压缩的战报正文（2026-10-31~11-07 全部取证/证伪/探针细节）→ `git log -p docs/np24_issue_ledger.md`；探针材料 output/_round_patches/ 与 output/_offpeak/。

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

（以下 §4~§6m62 为已完结期的压缩存目：标题即结论，正文已压入 git 历史；现行期 §6m63-6m110 亦已于 2026-11-07 压缩为总账节。）

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
  （最终基线/修复总账/遗留禁区）；④np24_fix.md 留档；⑤README 更新；⑥commit+push；
  ⑦明确向用户声明（终局 914 战报）。
- REG 九场任何一轮退步即回滚肇事 commit（铁律 8）。
- commit 格式随当期前缀（现=`np49…`）；push 随每步执行（失败 sleep 10 重试 3 次）。
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

## 6m63-6m110. 现行期压缩总账（2026-11-07 二次压缩重写；原 380 行全文可溯 `git log -p docs/np24_issue_ledger.md`，压缩前快照=d64abf8e。后续新节自 §6m111 顺延。）

### A. 现状（912/914）
- **语料**：output/oracle/fights=914 场 np46 净化重录件（[M13] 逐案隔离：每场开战前 Util.time/永久栈/EventBus/疲劳钟等全归零 ⇒ 单场复放≡语料 by construction；事件闸 200000+墙钟 1200s）。备份 fights_pre_npur_20261106（初始）+fights_pre_np47_swap_backup（换目录前）。**语料只读；probe 取证走 ORACLE_FIGHTS_ROOT=<绝对路径> 重定向，再次写语料需用户批准**。
- **键控全退役**：OracleAlignBattle.gd+OracleAlignBattleLong.gd+verify_oracle.py PY_ 镜像的六表（WARMUP_TIME_TICKS/BUFF_STOP_CLEARS_SEEN/CLEANSE_BIGGEST_FIRST/PERM_STACK_OVERRIDE/PERM_STACK_HARVEST/WARM_LATCH_PLAYERS）全空。**改键控必查三处**（np46 漏过长场副本=键控对重录件反成分歧源前科）。
- **NP22_REC_EV_GATE/PY_NP22_REC_EV_GATE**=20 长场键 200000（914 全量扫描再生）。**闸扫描口径必须=夹具口径**（只扫主夹具曾致 20 长场长度型伪红）。
- **夹具** gd_core_test/oracle_align_cases.json=914 场已入库（ac7c3950）；**verify --cases/--force 会收缩夹具，用后 git checkout 还原**。
- **914 刷账命令**：`python -X utf8 tools/verify_oracle.py --skip-fixtures --force`（改引擎后必 --force；跑后 git checkout 夹具）。
- **已修大针**：checkTriggerCount 战斗钟直比（gd_core/CoreItem.gd，commit 2646581a）一修翻 16 场——np33 的 +40s 进程钟模拟被净化语料反转（oracle Util.time 亦从 0 起，熔断语义回归真实）。
- **gd_core 取证锚点**：activateItems 双侧 rebuildTimerSeen+逐 item（np38 补锚含宝石 Timer）；_fatigueTick=步骤⑧ idle 尾部；疲劳 dmg=counter（t<14s 未启动恒 0）+受方 bonus 累积；宝石计时器走 CoreItem tickTimersPass 的 _tickTimers+gem._tickTimers 遍历（≈:732）。

### B. 残红 2 场（唯一主任务；统一根因=激活期宝石/物品冷却 Timer fire-tick 差 1 拍，np38 家族第 3 笔候选）
- **run602_r14（疲劳 dmg 3v4）**：idx334 t=429 玩家侧 fatigue dmg O=3/G=4，此前 333 事件全同。已实锤排除：rng 链 42434 抽锚定对齐零真分歧、疲劳事件 212 行全同位、MS 触发 171 行全同 ⇒ 唯一自由度=CC 宝石（Falcon Blade/Corrupted Crystal）Timer fire tick：t419 拍双侧同，t429 拍 gd 早 1 拍多触发一次静默 addFatigueDamage(1)。
- **run1094_r9（EB 首发侧翻转）**：EB 全战唯一触发 t=448，ora=opponent/gd=player，此前 134 事件全同；双方阵容镜像 ⇒ EB cooldown Timer fire 相位差 1 拍（同族）。
- **接续第一步（30 分钟级）**：①oracle 取 fire 序列：`ORACLE_FIGHTS_ROOT=<repo>/output/oracle/probe/np49_t602 ORACLE_ONLY_CASES=run602_r14 ORACLE_DEBUG=1 python -X utf8 tools/_np46_rerecord.py --cases run602_r14` → grep [timer-fire]/[cd-fire]；②gd 同法门控单场取 [TMR] fire；③双侧对比 Falcon Blade 宝石 Timer（path 含 @@/GemSocket）fire 时刻首拍+第二拍——gd 早 1 拍 ⇒ 修宝石 Timer f32 穿零/首拍递减/rebuildSeen 锚定（CoreItem/CoreTimer 宝石侧，四树+py 同步）→ 单场验证 run602；④同法验 run1094 的 EB；⑤备选（fire 全同仍差）：查 CC doCooldownEffect 调用前提与 gem.doCooldownEffect 驱动位。
- **每修一场后**：单场 verify 三方一致 → 914 全量刷账（A 节命令）零回归 → 台账+commit+push。
- **全绿后**：P4 收口链（见「6. 交付口径与收口」P4 协议，⑦=终局 914 战报）。

### C. 铁律（任务期）
- **914 全绿之前不许退出**（用户铁令）：每步完成/受阻=台账新节（自 §6m111 顺延，每节精简）+commit+push（失败 sleep 10 重试 3 次）；受阻写明阻塞点、绕行另一步；上下文过长靠台账接续，勿在会话内复述台账。
- 盲修禁制：同一假设两连证伪即停；反例锚先行；rng 数值同而状态分叉=有看不见的抽。
- 判读双验：单场 json PASS 必须配 gd 产物 events.json 非空+原始输出无 SCRIPT ERROR（Parse Error 空流=假 PASS 前科）；单场 harness「PASS」行不可信。
- 探针/临时改动用完即还原：git checkout 四树+`python -X utf8 tools/gd_to_py.py` 重生成（py grep=0 验证）。

### D. 方法论与坑位（修复必读）
- **双链 trace 锚定对齐法**：oracle rng_log（`idx kind a b => val @t | path | st`）vs gd rng_trace（`idx kind a b val ? st`）；锚=ora 首抽的 (kind,a,b,v) 在 gd 流首现位；gd 流含装配期。**对齐器三件套缺一即假分歧**：①kind 归一（randInBox/roll/randBuffLabelDir/randBuffLabelPos/randPitch≡randf_range；pickRandomElement/pickRandomStacks/pickRandomEngine≡randi_range）②双向 skip≤12 ③零宽 (0,0) 行过滤；gd 行含 MARKER 列（SRC/LABEL/EVENT/BUS/BALROLL）非抽行。
- **数值基准**：PCG 全局链 INC=2885390081777926815；引擎 real_t=float32，定时器写入过 _f32eng 量化（f32(3.1) 穿零 186 帧≠f64 187）；间隔类 tick×60 跨侧可比。
- **净化语料语义**：语料=全新状态确定性执行——对拍分歧=引擎真 bug，修引擎四树，**勿再加键控/注入**（注入键已被 GA cleanse rng 级联证伪：扩容掷点数→链移位净退步）。
- **长场 playbook**：新场首验 `tools/long_case_fix.py --focus <case>` 三腿定谳（--prefix 首轮只跑 gd 腿=假「长度型分歧」）；py_ev_gate=int(语料事件数×1.2+1) 按自然全长算——语料重录后必须 --prepare 重算+**删该场旧 py 产物**（py resume 对闸/代码变化失明）；三件自洽≠良品；gd≡py 而重录探针≠gd 单点分歧 ⇒ 先查键控表再查引擎。
- **长场批量资源**：内存 peak≈1.1GB+墙钟×9MB/s（batch=2+显式 9000MB 稳过，手填小值必被杀）；「日志停滞 90s」看门狗会被刷屏打败，刷屏型卡死需日志增长率/墙钟硬闸；`long_case_fix.py --record` 分档+并行（--stall-seconds/--max-retries/--mem-limit-mb）；批量重录 `_np46_rerecord.py --cases`（resume 幂等=[M13]+status=ok 门；harness 层另有 events 非空 resume——**重录既有场必须换 fresh ORACLE_FIGHTS_ROOT**）。
- **np46 二分教训**：分片二分以 gd 对拍为准绳判读，单片对旧语料分歧≠该片有害（T0×CHAR 片交互伪差先例：attackSoundReadyTime 残留使职业攻击音闸整场闭死）。

### E. 已完结战报存目（正文=git 历史 @d64abf8e）
- §6m63-70：1120/1444 翻绿（T0 预载/PERM OVERRIDE 键控，已随净化重录退役）；986 攻坚三轮证伪（biggest-first/R 扫描鬼影=Parse Error 空判/碰撞域之墙）。
- §6m71-76：986 定谳链（sim986v1-v5 求解器、注入键证伪、[BGAIN] 表位对拍）→终谳=录制批残留场，铁律 9 停。
- §6m77-81：长场「语料截断·严格前缀」5 场收割（工具 length 分歧分流修复）。
- §6m82-86：np46 净化重录 Step1-4（隔离/全长闸/单例验证/批量包装器）+批量假 PASS 修正（[M13] 门）。
- §6m87-105：54 长场 19 场翻绿（零改动直绿 12+语料侧定向重录 7，§6m103 兼长场副本键控摘除）。
- §6m106-108：工作流收尾移交+np47 接力：860 重录收口、914 原子换目录+闸再生+夹具升 914、回补基线 876/914。
- §6m109：checkTriggerCount 一修翻 16→912/914+残红 playbook 初版。
- §6m110：run602 双链 trace 零真分歧实锤+统一根因收窄（=本节 B）。

## 6m111. ★★ run602_r14 翻绿（912→913）：Sandbag BuffTimer=普通 Timer 非 MultiTimer——gd multi 标志错标致 changeTimer 延长失效（2026-11-07 offpeak np49）

- **§6m110 的 CC 宝石假设三重证伪**：①run602 阵容无任何宝石（CC/FB=0）；②gd CC TRIG=0（从未触发）、oracle 亦无 CC 激活事件；③rng 链 42434 抽+疲劳钟 212 笔 counter 抽值与流内间隔逐位全同。
- **重定谳**：14 处分歧全为疲劳 dmg 数值，dmg=round((counter+bonus)×(1−resi))（DamageResult.reset 置 damage=0 ⇒ counter 抽+bonus 精确合成）；FAT 探针（双侧 add/take 172+212 笔）逐位全同 ⇒ (cnt,bonus) 全同 ⇒ **分歧=resi（damageResistance）窗口相位**。resi 唯一阵容写入者=Leather Helm(+25/dur3)+Sandbag(extends LH，自身+25+对手+25，EB 回声经 Util.changeTimer 延长)。
- **根因**：oracle 的 Sandbag.tscn BuffTimer=**普通 one_shot Timer+timeout 信号**（区别于 LH.tscn 的 MultiTimer+multi_timeout），gd 误继承 LH 的 `newItemTimer(..., multi=true)`——multi 运行中 start(t+left) 只 push timestamps 不改写引擎读数 ⇒ 注册表 eng==e[1] 不重同步 ⇒ EB 回声 changeTimer@5.5 后 SB 仍按原截止期 7.017 提前 fire（oracle 实证 eng→8.5167 重同步、14.017 才炸）⇒ resi 窗口错位 ⇒ 疲劳 dmg 14 处分歧。
- **修**：gd_core_items/Exclusive/Sandbag.gd `_readyInit` 重建 `newItemTimer("BuffTimer","buffEnded",false)`（四树+py 重生成）。单场 verify 三方一致。
- **方法论**：tscn 计时器真身（脚本+信号名）必须逐件核对，继承链不保真；「总量同、相位异」的补偿形分歧=resi/Timer 窗口相位差的指纹。

## 6m112. ★★ run1094_r9 翻绿（913→914 全绿）：语料池化残留——ItemBook 注册桶跨执行持有 freed 实例致 EB 计数崩溃，harness fresh instantiate+桶清空重注册+定向重录（2026-11-07 offpeak np49）

- **重定谳（非 EB 首发侧翻转）**：新视角=EB(Everburning) 火箭计数面——EB.doCooldownEffect `if numFlames > 0: giveHeat(heat×numFlames)`；oracle 正式执行 PLR-EB 触发（TRGE 探针 tt0=-0.0152）但 doCooldownEffect 不执行（EBCD 探针缺席）且 onPrepare 仅暖场执行（EBP 缺席）。
- **根因链（探针五连定谳）**：①ItemBook 注册桶跨执行残留 freed 实例（上一执行物品释放后未从桶摘除——摘除被 isOwnable() 闸）②下一执行 EB.onPrepare 的 countAllInInventoryOfType 迭代桶命中 freed 实例崩溃（日志实锤 `Invalid get index 'ownerType' (previously freed instance)` @ItemBook.gd:289）③numFlames=null ④`if numFlames > 0` null 比较再崩静默 abort ⑤无 Heat/无 FF 反应。不对称=对手侧 count_opponent 只取 .size() 不解引用 ⇒ OPP-EB 正常。TRGE@16/25/35s=每次跨越重复崩溃（不 deactivate）。
- **修（harness 两点+语料重录）**：①oracle/Core/Inventory.gd createFromItemTuples 战斗装配弃用池化实例（fresh `descriptor.instantiate()`+保持 item_instantiated_deferred 信号）；②reset_residual_state 增 ItemBook.ownableItems/opponentItems 清空+按当前 getItemsAndGems() 重注册（注意：必须经 `root.get_node("/root/ItemBook")` 运行时取 autoload——主场景脚本静态引用 ItemBook 会改 autoload 载入环序引发 Util.gd:28 「Expected a constant expression」级联 Parse Error，全工程崩）；③run1094_r9 定向重录（新语料 650 事件/winner=player/双侧 EB 三连，[M13]+ok，sha256 双侧核对）。
- **旧语料备份**：output/_offpeak/np49_corpus_backup/events_old_1094.json（旧 596 事件/winner=opponent）。单场 verify 三方一致 1/1。
- **教训入册**：①「单场复放≡语料」的 by-construction 依赖**每执行全新注册基线**——ItemBook 桶/池化实例是 register-visible 状态面，reset_residual_state 必须覆盖；②主场景脚本勿静态引用 autoload（环序敏感）；③崩溃型静默分歧（null 比较/下标 freed）不留事件痕迹，只留 SCRIPT ERROR 日志——判读双验纪律的 SCRIPT ERROR 检查不可省。
