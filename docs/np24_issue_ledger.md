# np24 问题总账与修复指导（offpeak 任务书）

> 生成：2026-10-26。基线 **71/914**（alignment.json 实读，843 红）。
> 本文是 offpeak 修复任务的唯一指导文件：问题清单、根因线索、修复口径、纪律。
> 每完成一项在「状态」列打勾并写明守门证据；**全部完成前不得退出任务**；
> 全部完成后继续自查新问题并修复，同样不许主动退出。

---

## 0. 环境与铁律（每次动手前重读）

1. 工作区 `D:\文件资料\学习\自动背包AI`；**工作区外零操作**（用户铁令）。
2. Godot 一律 `--no-window --audio-driver Dummy` + **APPDATA 按 PID 隔离**
   （跑 Godot 的 python 侧已由 `tools/verify_oracle.py::run_godot` 内置；
   手动跑 Godot 时用 `APPDATA="…\output\_recovery\appdata_p\<pid>"`；
   最省事直接调 `tools/run_gd_core.py::run`——内置隔离+_NOISE_KEYS 噪声过滤）。
   ⚠ **OpenMem failed err=5 已终谳（2026-10-29 避坑指南）**：搜狗输入法注入
   抢 `Local\sgime_skin.*.filemap` 失败打的日志，failed 后自动重建成功=纯
   噪声，Godot/内核自身不报错；**`--headless` 是 4.x 参数**，3.6 写了会走
   GUI 窗口路径反而触发 IME 注入——一律 `--no-window`。不要并行开多个
   Godot（共享 user:// 互相踩、噪声更凶）；批量走串行/分片；跑前
   `Get-Process | ? ProcessName -match 'odot'` 清残留。为它改
   gd_core/gd_core_items/oracle/语料是禁区。
3. `output/oracle/fights/`（语料）与 `oracle/` 树只读。oracle 取证桩须：
   备份→≤10 行环境变量门控→ORACLE_FIGHTS_ROOT 重定向探针→逐字节还原→md5 三方留档
   （先例：output/_round_patches/np24_harness/）。
4. 改 `gd_core/*.gd`/`gd_core_items/**` 后必跑 `python -X utf8 tools/gd_to_py.py`，
   并同步内核副本：`cp gd_core/*.gd gd_core_test/gd_core/ && cp -r gd_core_items/* gd_core_test/gd_core_items/`
   （test 侧 items 是**真实目录**，历史上曾是 symlink 伪文件=挂死根源，勿回退）。
5. 判据双轨不放宽：canonical 事件 + 渲染行。守门唯一口径：
   `python -X utf8 tools/_np21_gate.py --cases <cid,...> --tag <每轮新标签>`（rc=0 全绿）。
6. REG 九场防退步：`run570_r18,run1160_r18,run1029_r2,run862_r18,run813_r12,run635_r12,run732_r12,run695_r18,run1514_r18`。
7. 全量验证三腿自动并行（2026-10-29 起，**详见 docs/parallel_workflow.md**）：
   总控 `python -X utf8 tools/_np23_shard_verify.py [--rerun <cid,...>]`
   （= gd/py/compare 三腿各自并行，等价 `tools/verify_oracle.py --force`）。
   路数每次运行按当时 CPU/可用内存自动定（上限 5，LPT 分桶），**无需手填**——
   旧「`--shards 3`」写法作废（--shards 现仅是并行度提示）。定向重跑=`--rerun`
   或 `verify_oracle.py --force --cases <cid,...>`（cases json 被其他执行体占用
   时加 `--skip-fixtures`）。**⚠ 定向跑（--cases）会把 alignment.json 收缩成
   那几场**——收工必须补一次全量 `verify_oracle.py --compare-only`（不带
   --cases）还原 914 行基线（np25 实测曾被收缩成 2 行假基线）。并行管线改动后
   先跑 `python -X utf8 tools/_np_compare_par.py --selftest`；并行期间不要再
   手动开 Godot。
8. 变异前备份到 `output/_round_patches/np24_fix/`。已绿场不许退步。
9. 盲修禁制：同一假设两连证伪即停；反例锚先行；数值同而状态分叉=有看不见的抽。
10. 语料=2026-10-24/25 全量重录的干净形状（自然终止+确定性自证）。
    **below_master=true 已终谳**（run574 FFR tick 78 实证），勿回退。
11. **分片器幂等跳过**（np24-P3-7 教训）：`_np23_shard_verify.py` 不带 `--rerun`
    时跳过已有产物——内核/夹具/引擎变更后直接跑全量会把**陈旧产物**当现状比对
    （RED 账本失真）。任何变更后收口一律 `--rerun <全部红场>`（或至少受影响簇）。
12. **assets 再生链三产物一个不能漏**（np24 修复F 教训，2026-10-27）：改
    battle_items.json 后必跑齐 `gen_lineup_fixture.py`（→LineupFixture.gd +
    item_battle_fixture.json）+ `gen_fixture_from_lineup.py --oracle`（→cases+
    v3 lineups）+ `gen_gd_core_data.py`（→**gd_core_runtime.json**，py 引擎
    几何源）——A2 轮漏跑第三个，py-only 60 场全因 runtime 旧几何假红
    （守门 np24_pygeo_r1 十场 ALL PASS）。

## 1. 工具速查

| 用途 | 命令 |
|---|---|
| 守门（gd+py 双腿，分钟级） | `python -X utf8 tools/_np21_gate.py --cases <c,...> --tag <新>` |
| 定向 gd 逐抽 | `ORACLE_ALIGN_OUT=<abs scratch> ORACLE_ALIGN_CASES=<cid> ORACLE_ALIGN_CHUNK=0 ORACLE_ALIGN_SELFCHECK=0 ORACLE_ALIGN_TRACE=1` + Godot（见铁律 2）→ `<scratch>/<cid>/rng_trace.txt` |
| 逐抽对位 | `python -X utf8 tools/_probe_draw_diff.py <语料rng_log> <gd rng_trace> [N]` |
| canonical 对拍 | `sys.path.insert(0,'tools'); import verify_oracle as V; V.first_divergence(...)` |
| 神谕探针（带逐抽） | `ORACLE_FIGHTS_ROOT=<abs> ORACLE_ONLY_CASES=<cid> ORACLE_DEBUG=1 ORACLE_FIGHT_CHUNK=0` + Godot（oracle 工程）；**先验探针 events≡语料才采信其 rng_log**；**桩行必须 6 元素**（5 元素会炸 oracle_fight.gd:819 dump 循环 → rng_log 恒 0 字节，2026-10-27 TOADSND 实证） |
| 全量分片（三腿自动并行） | `python -X utf8 tools/_np23_shard_verify.py [--rerun <红场>]`（详见 docs/parallel_workflow.md） |
| alignment 重建/还原 | `python -X utf8 tools/verify_oracle.py --compare-only`（全量、**绝不带 --cases**） |
| 神谕重录（如需） | 抬闸版参数在 `output/_recovery/oracle_fight_lifted.gd`（事件闸 200000/墙钟 1200s）；单场单进程 |

## 2. 已修复（勿重做，防回退）

- 宝石槽=实例真相（harness 按 len(entry.gems) 装配）
- below_master=true 终谳（harness+py 三处）
- defer 镜像 / ANIM 裸抽 / MagicRing.setCraftedEffects / EB 接力死亡镜像（6 笔，commit 4315c580）
- oracle trace 完整化（Util.flip/BalancedRange.randIntRange 入 ORACLE_DEBUG trace 面）+ stats 快照通道（录制能力，已入库）
- 工具链：symlink 根治/类注册表/label_rng_enabled/APPDATA PID 隔离/三路分片器
- **新根因A（crafted 实例真值链）**（2026-10-26，commit c1655431）：871/955/1386 Anvil 层全清
- **新根因A2（grid 真值面 1.1.7 旧提取）**（2026-10-26/27）：
  - 根因三连：①`simulator/extract_grid.py` 源树指 extracted/Items（1.1.7，已清理），
    对无自有 tile_data 的 tscn 按 size[1,1] rect_fallback——**19 件实例化基座
    Items/Item.tscn 的物品（蛋/幼龙/盾/王冠族）真身=基座 CollisionMap 2×2**
    （RubyWhelp 实证：oracle 包内占 (5,5)+(5,6)，夹具只给 (5,5)→FannyPack 包内容错
    →开战激活 3v2→全链漂移）；②**affected_cells 同为 1.1.7 旧值**
    （LightGoobert 真值左右两列 [[±2,±1]]，旧库折叠单行→Goobert 族
    onItemActivated 连接收漏 301 次治愈）；③宝石/棋子被继承逻辑污染（已显式复位 1×1）。
  - 修复：extract_grid.py 重指 oracle/Items（1.1.9 真值，只读）+ 无 tile_data 时
    查基座继承（gem/chess 排除）；battle_items.json 全量重提取（472 grid +
    19 继承 2×2 + 46 宝石复位）；gen_lineup_fixture → item_battle_fixture →
    gen_fixture_from_lineup 三产物重生（914 场）。
  - 证据：run602 逐抽对位 cons-idx 61→**549** 全等（gd_v3 vs actp2 探针，探针≡语料
    逐字节验证）；gd 侧诊断行工具链已入库（ANIM/SRC/LABEL/SRC gain_label/MSROLL，
    全部 ORACLE_ALIGN_STACKTRACE 门控零耗链，gd_core/CoreRng.trace_diag）。
  - 分片全量复测：仍 60/914（符合预期——A2 前移首分歧非整场翻绿）；REG 九场无退步。
  - 取证桩已还原（FannyPack/Item/MrStruggles md5 在 output/_round_patches/np24_fix/fpact_probe/）。
  - ⚠ 新发现：**py 腿 run845_r18 IndexError 缺产物**（A2 后新暴露，见 P3-7）

## 3. 问题清单（按优先序；「线索」=已实证的定位面）

> ★ **开工第一步（2026-10-27 追加，先于一切修复）**：诚实基线重跑已完成
> （2026-10-27，全 914 场 --rerun，gd 三分片 0 失败，py 913/914，30.1 分钟）——
> **当前真基线 69/914**（RED 845）。分簇摘要随时可出：
> `python -X utf8 tools/_np24_red_clusters.py --top 14`。
>
> ★ **P2-0 勘误（2026-10-27 晚，offpeak 实跑推翻）**：早前「长度簇 461 场」是
> **分簇器解析 bug**——firstDivergence 有两种形状（平铺=只一对分歧；嵌套
> {oracle_vs_gdcore, gdcore_vs_py}=两对都分歧），嵌套场被按平铺读成 kind=None，
> 484 场误判「len」。修正后真分簇（tools/_np24_red_clusters.py 已修）：
> **evt1@1-50 ×125**（早期 DealDamage 分歧，最大簇）＞ **evt0@1-50 ×101**
> （早期 Activation，含 P2-1 t0 族）＞ evt1@51-150 ×73 ＞ **py-only ×60**
> （gd≡oracle 全等、py 单独分歧——纯 py 缺陷，gd 即真值，无需 oracle 取证，
> 最快收敛面，样本 run569_r11 idx129 evt104 Spiked Shield）＞ evt8@151-400 ×48
> ＞ evt107@1-50 ×44 ＞ evt12@51-150 ×25 ＞ evt105@51-150 ×24 …。
> 打法：先 py-only（对照面=gd 产物直读），再 evt0 族（接 P2-1），再 evt1 族。
>
> ★ **进展（2026-10-28，np25 会话）**：**P3-3 电荷像素几何族已修复**
> （gd_core/CoreItem._chargeInventoryCells 重写 + chargeFrame 数据链三产物），
> 全量复跑 **143/914（+18）**。根因：电荷格映射漏 −rotmin 项——原版
> addItemByTopLeft 放置平移使 P_cm/corr 相位项解析抵消，闭式
> `inventory_cell(c) = 锚点 + R_fd(c) − rotmin(fd)`；旧实现 collisionMapPosition
> 无数据源恒 ZERO，raw min=(−1,−1) 的送电荷物品（Battery/CogBadge/Generator/
> ChargeSplitter/Con-Trap-Tron；LightningStaff (0,−2)）整条路径错格。
> run572_r9 实证：Battery 电荷 cur=null→Death Scythe，DS 首攻 1.283→1.183
> 精确同语料；run572 首分歧 ev@22→ev@109（新残差=Strong Divine Potion
> type-103 面splat）；run1160 ev@3→ev@155。REG 九场零退步（570/1029 绿保持）。
> 数据链：battle_items.json raw collision_cells → gen_lineup_fixture.py
> （item_battle_fixture.json `charge_frame`[fd0..3]）→ gen_gd_core_data.py
> （runtime per-rot `charge_frame`）→ harness/py 引擎注入 CoreItem.chargeFrame。
> 诊断行 CHRG（changeChargedItemStat 命中面）+ SPD+（addSpeed 账本）入库，
> 双门控零耗链同规。evt0@1-50 簇 101→81；evt1@1-50 簇 125→124（首分歧大幅
> 后移，同簇不同签名）。
>
> ★ **棋盘 capture 数据面已修复（2026-10-29，np25棋盘面，commits d4afe736+b05e33f9）**：
> **ALIGNED 148→277（+129），evt0@1-50 棋子主体簇自分簇表消失**。三层缺口逐一定谳：
> ①类型位（ask 定谳①②）：build_data._types 无 chess 分支 + enrich_types TYPE_NORM
> 'chesspiece'（无空格）查不到 CSV 'Chess Piece'（带空格）→ 12 件棋子 types=[]；
> token 必须 'chesspiece'（=CoreConst.Type 枚举名 17；'chess' 会使
> gen_lineup_fixture compile_descriptor SystemExit——实测栅栏）。②**计划外根因③**：
> extract_grid.py scan_tscn_index 只扫三层目录（棋子 tscn 在 Exclusive/Chess/ 第四层
> 恒不被索引）+ chess 被排除/兜底双排除连坐（排除理由系宝石）→ 棋子 grid 恒 np23
> 手补裸 1×1，**affected_cells=移动模式真值从未落库**（WhitePawn 对角 2 格 /
> Bishop·Queen·Rook 20 格 / King·Knight 8 格）→ moveCells 恒空（run644_r7 trace
> Gshuffle ChessBoard:100 size=0 铁证）→ 即使 canAffect 修好也捕获恒空转——
> ask 预言「只补数据位会立刻再变红」的第二机制。递归扫描+解除 chess 排除后
> battle_items.json diff 恰 12 条（Wisp 1.1.9 tscn 真值漂移属面外已回植+立案）。③**内核双缺口**：
> r1_0 对应物 CoreRng.shuffleEngine/pickRandomEngine/globalChainOpen（净新增，
> 开账点 CoreCombat.startBattle(preordered)；两态直调引擎原生方法=链位等价机制本身）
> + **r4_2 对应物 CoreGrid.moveItem**（Inventory.gd:640-646 判定面，ask 漏登记——
> r4_2 生成代码调不存在的内核方法，漏补则棋子首次移动/捕获即炸）。④builder 四 pass
> 全量落树（a1 14文件26点/fam_r1 1·1/r4_2 1·2·0miss/r1_0 8文件 shuffle11+pick1；
> 注释'12'系 np23 计数笔误——16 处 shuffle 中 5 处在剥离函数体内、存活全集恰 11）
> 并回植五处被冲掉的手补（Item.gd crafted_instance+playActivationSound+isCrafted、
> MagicRing.setCraftedEffects、EngineerBox eb_relay 镜像、Eggscalibur ESHUF、
> MrStruggles MSROLL——漏植一即全场 assembly-fail 或 np17-A crafted 语义静默退化）。
> 守门：chessfix 三例 run644_r7 语料512=gd512=py512 逐位同至 idx2 CB-Activation
> （CB-Act gd2=py2=语料2；run660 12→460、run1046 24→388、run644 2→301）；
> REG 九场 570/1029 绿保持+run1266_r11（唯一含棋盘绿场）PASS、七红五同位+
> run695 改善147→172+run635 107→104（双侧 FalconBlade，r2_1 三抽真值还原致红场
> 链位重排——builder 已修而树从未接收的另一例，0 绿场含 FalconBlade）；
> 全量 32.6 分钟 767 场 --rerun 三分片 0 失败。S7 活体 trace：Gshuffle
> ChessBoard:80/:100 size=1/2 + Gpick ChessPiece:74 size=3 全链入账（idx7
> rng_log 逐抽对位不可行——语料 914 场现库 rng_log.txt=0，属 ORACLE_DEBUG
> 场次产物，已留档改道）。备份 output/_round_patches/np24_fix/chessdata_r1/。
>
> ★ **P3-2 勘误（2026-10-28，探针已执行）**：635「BalancedRange malus 悖论」
> **不存在**——BRPROBE 取证桩（oracle/Utility/BalancedRange.gd，已逐字节还原
> md5 留档 output/_round_patches/np24_fix/p332_probe/）实证语料 [5,5,5,4] =
> **两个不同 Falcon Blade 实例交错**（iid=76412 掷 5,5；iid=99251 掷 5,4），
> 每实例 acc 从未 ≥1，行为精确正确；前会跨实例误读。探针 events≡语料逐字节
> 验证。635 真分歧（ev@107）= 对方 FB 第 4 攻 oracle 掷 4 v gd 掷 5：u 值对位
> （阈值 1e-6，容忍 6 位小数量化）**478 行全对齐后在 479 分叉**——伤害数字动画
> roll（0.9,1.1）与下一 tick 首抽（对方 cooldown jitter 0.975,1.05）之间存在
> **未留痕抽差**（两侧伤害掷点均刻意裸调不入账本，CoreRng.BalancedRange
> kernel_r5 注释；嫌疑人=攻击收尾链 single-side 未留痕消耗）。待带栈重探
> （get_stack 在当前 headless 上下文返回空，需先解栈帧可用性）。
>
> ★ **py-only 新 6 场（2026-10-28）**：run874_r7/run916_r6/run1132_r18/
> run1316_r10/run1422_r14/run1528_r13——P3-3 后 gd 腿翻绿（gd≡oracle）暴露
> py 残留（长度分歧），与 run845 同类。对照面=gd 产物直读，最快收敛面。

> ★ **★ np25 会话 ↔ offpeak 任务同步节（唯一协调面，2026-10-28）★**
> 主会话与 offpeak 任务**通过本节交接**：开工先读本节+实读 alignment.json/git log
> （**运行时状态以实读为准，勿信本节快照**）；每完成一项在 §3 打勾并回写本节
> 「已完成」栏。**commit 允许（格式 `np25修复X：…`），push 禁止**（用户指令：
> 减少 push 频率，由主会话统一 push）。
>
> **★ 接管声明（2026-10-28）**：主会话继续活跃修复中，offpeak（488589ec）若开跑
> **先实读 git log 与本节**——主会话每完成一项即回写本节并 commit；「已完成」
> 栏出现的项直接跳过勿重做；「进行中」栏是主会话当前工作面，offpeak 从任务书
> 第 ② 项起步避让。
>
> **已完成（np25 主会话）**：P3-3 电荷像素几何族（commit 80db42c2，143/914）；
> P3-2 悖论勘误（跨实例误读）+真分歧定位（478 行后未留痕抽差）；
> py trace 通道垫片（e0dc73ed）；run874 冷却链排除+信号级锁定（73e4593f）；
> BUS 探针+f32 对称化（940ffd39/cc74a0be）；全局流错位修复（35249827+
> d9887a9e，148/914）；新问题批次 A/B/C 入账（a972f726/7dfb374d/f4226f3b）；
> **buff/timer 到期「gd 早 1 tick」修复（2026-10-29，timeout1t 面）**——
> 三变量模型（e[0]/eng/e[1]）+rebuild 等价步骤，定位场四腿 ALL PASS、
> 目标族 85 场 50 绿、REG 零退步；残红 35 场定性建档待后续面
> （7 场 dur 边界 ULP 需 oracle 腿取证 / 8 场多栈次序 / 20 场非本面）；
> **棋盘 capture 数据面修复（2026-10-29，np25棋盘面，d4afe736+b05e33f9）**——
> 类型位+grid 移动模式+内核双缺口（CoreRng 全局链台账/CoreGrid.moveItem）+
> builder 四 pass 落树+五处手补回植，ALIGNED 148→277（+129），
> evt0@1-50 棋子主体簇消失，REG 零退步（详见 §3 打勾块）。
>
> **★ offpeak 续作战报（2026-10-29，offpeak-488589ec）**：
> - **✅ py-only 族清零（commit bcc6e858）**：run1132_r18 的 IndexError 根因
>   定谳=loseStacks 删 farthest 后 nextTemporaryTimeout 未回拨（原版同构隐患）
>   × Godot **release 越界读=软错误中止整个函数**（gd1132v 无守卫跑铁证：栈
>   保留/定时器死/零事件）vs py 硬索引进程崩溃。修复=onTimeout 越界**早退**
>   同语义（gd1132u 反证：skip+重扫版本会多 -1 事件+提前移除=行为改变不可用）。
>   BLND 簿记诊断六点入库（实例 tag+timer 态，双门控零耗）。守门
>   np25_ofp_r1132：绿 4 保持+REG 七红分歧点逐场同基线+run1132 双腿同位红
>   ev@12（=其本簇签名）。全量分片复验中（结果回填）。教训入册：
>   **gd 侧改动跑批前必须确认 Godot 进程启动于 cp 之后**（gd1132v 跑了旧码
>   导致一次误判）；release 软错误语义只能靠无守卫跑实证，不能靠推演。
>
> **★ BUS 探针入库 + run874 深挖定谳（2026-10-28 续）**：
> - **总线探针**（gd_core/CoreEventBus.gd，连接表值改存 [funcRef, receiver] 对
>   ——Godot 3 FuncRef 无实例读取器；BUS=发射者/信号/监听数 + BUSL=监听者逐个
>   身份，双门控零耗链；13 场守门 np25_bus_r1 与基线 RED 清单逐场一致=零行为差）。
> - **f32 冷却链对称化**（gd_to_py.py::_apply_cooldown_f32 窄重写规则 19 条，
>   覆盖 triggerTime/iterationCooldown/speedScale **全部**写点；此前漏
>   advanceCooldownPercent/Seconds 两写点的半包版本打红 run570 的教训已吸收）。
>   13 场守门逐场一致；**全量分片复验通过：143/914 零新增红/零新增绿**
>   （25.3 分钟，np25 主会话回填）——两项均行为中性，已可安全入库。
> - **run874_r7 真分歧面（BUS 桩定谳）**：分歧 tick（t=619）**无任何 TRIG 行**
>   ——不是冷却触发！两侧 Eggscalibur 攻击链完全对齐（TRIG/攻击/尖刺/mana/
>   ManaOrb 监听/SRC Chili 107 全等），分叉在**链式激活的下一拍**：两侧都
>   ANIM Chili#11（activate() 被外部调用——非冷却路径），gd 继续 Chili 自己的
>   giveHeat（SRC Chili 107→EVENT 107→12→0→BUS activated **1**），
>   py 跳到 **Blueberries 的 giveMana**（SRC Blueberries 105→105→0→BUS
>   activated 2）→ 之后 gd 的 Blueberries、py 的 Chili#11 交错收尾。
>   **根因方向（已收窄到 20 行窗口）**：分歧拍两侧都是**无 TRIG 的
>   doCooldownEffect+activate**（冷却链彻底排除）。gd 侧走 Goobert
>   （Chili Pepper extends Goobert）的 onItemActivated 计数路径——合法无 TRIG；
>   **py 侧同一拍却是 Blueberries（extends Food，不在 onItemActivated 四类
>   Goobert/ManaOrb/StorageCoffin/PiercingArrow 之列）跑了 doCooldownEffect
>   （giveMana_capped 全树唯一调用点）+activate（BUS emitter=Blueberries 铁证），
>   且无 TRIG 行**——按调用图不可能，指向 py 侧行为派发/计数串扰
>   （.FuncRef method 绑定或 Goobert 计数器跨实例污染）。**下一探针**：py 侧
>   Goobert.onItemActivated 与 Food.doCooldownEffect 入口各加一行
>   trace_diag("GACT", identifier, activations, "self="+str(id(self)))，
>   单场重放即见串扰点；同查 gd_to_py 的 Goobert.py 转写（计数器是否实例态）。
> - f32v2 未翻动 6 场 py-only（分歧 idx 不变 140）——压线翻转不是其根因，
>   但位级对称化保留（防未来同类；全量已确认无副作用）。
> **★ run874 根因定谳 + 全局链预热修复（2026-10-28 深夜，np25 主会话）**：
> - **根因链（spy 调用栈铁证）**：无 TRIG 的 doCooldownEffect =
>   **Eggscalibur.onDealtDamage**（攻击命中→tryUseMana→`affected.shuffle()`→
>   逐个直呼 `food.doCooldownEffect()`，合法机制 gd/py 都有）。裸
>   `Array.shuffle()` 消费 **Godot 全局 Math 流**（seed(S) 播种、装配段
>   activation_order 消耗两条 shuffle），与战斗 PCG 主链独立——主链逐抽全等
>   与本分歧并存不矛盾。py 的 `_math_rng` 绑定后从 seed(S) **全新起步**，
>   缺装配段消耗 → 每次 shuffle 结果序错位 → food 激活序分叉。
>   ESHUF 六拍对照铁证：gd=`C|C|B, B|C|C, C|B|C, C|B|C, B|C|C, C|C|B`，
>   py 热身后=`C|B|C`×6（第一拍仍不同——**装配段之外还有未盘点的全局消耗**，
>   gd_core_test 宿主 activation_order 之外、Eggscalibur 首攻之前的全局链
>   消费者待逐项盘点；Godot 全局流状态不可读回，只能逐机制复算）。
> - **修复（simulator/gd_core_engine.py，order 路径 startBattle 前）**：按
>   activation_order 同算法补两条 shuffle 消耗（结果弃置）。**直接验证：
>   run916_r6 翻绿（三方一致），570/1029 保持绿**；run874 分歧 140→135 后移。
>   ⚠ **待查**：np25_warm_r1 gate 里 916 回红 ev@72（与直接测矛盾，疑似 gate
>   scratch 的 gd 腿产物/激活序来源问题）；run1132_r18 py IndexError 仍在。
> - **诊断入库**：GACT（gd_core/Goobert.gd，单行语句）、CDX（gd_core/CoreItem.
>   gd doCooldownEffect 包装器——注意物品覆写虚分发绕过内核包装器，CDX 只对
>   未覆写者生效）、ESHUF（gd_core_items/Eggscalibur.gd 行为树，全序落 trace）。
>   上一轮「CDX/GACT 零行」之谜同解：物品覆写+双树继承使内核树诊断旁路。
> - **offpeak 续作清单**：①916 gate 异常核查 ②装配段外全局消耗盘点
>   （gd_core_test 宿主 activation_order 之后、战斗期各机制的全局链消费，
>   与 py 引擎逐一对账）③ESHUF 对位驱动剩余 4 场收敛 ④run1132 py IndexError。
>
> **★★ 全局流真根因补全 + py-only 五场全翻绿（2026-10-29，np25 主会话）**：
> 上一轮预热后 py 六拍 shuffle 全为 CBC×6 → 实测发现 **`_bind_battle` 全树
> 零调用点**（_rt.py docstring 声称 CoreContext._init 调它——实际没有）——
> py 全局 Math 流从未以本场 seed 播种，回落 DEFAULT_SEED 的**进程级单例**，
> 且跨场累积（批内前序场状态污染后序场）。修复：order 路径 startBattle 前
> `_bind_battle(int(self._seed))` + 补两条装配 shuffle 消耗。
> **直接验证：run874_r7/run916_r6/run1316_r10/run1422_r14/run1528_r13
> 全部翻绿（三方一致）**，570/1029 保持绿，8/8 场 rc=0。REG 九场 gate 无退步
> （np25_warm_r2）。全量分片验证中（结果回填本节）。剩：run1132_r18 py
> IndexError（独立崩溃，非分歧）、916 gate 异常已由本场翻绿证伪（上轮 gate
> 的 gd 腿产物问题）。ESHUF/GACT/CDX 诊断行保留（双门控零耗）。
> ⚠ 教训入册：**「_rt 垫片 docstring 声称的调用方」必须 grep 实证**——
> 声称的注入点不存在时流语义整体漂移，且批内跨场污染极其隐蔽。
>
> - **✅ 全量分片复验落地（2026-10-29）**：**148/914（+5），零新增红**——
>   run874_r7/run916_r6/run1316_r10/run1422_r14/run1528_r13 全部翻绿，
>   py-only 族 6→1（仅剩 run1132_r18 的 py IndexError 独立崩溃）。
>
> **★ 四修复面并行分析落地（2026-10-29，workflow 四面分析+独立复核 4/4 成立）**：
> 修复路线图全文见 workflow 产物卡片（修复路线图·primary）。要点：
> - **新A 勘误（重要）**：oracle 探针 rng_log **根本没有截断机制**——1543 行/
>   64063 字节=run572_r9 一场 14.000s（840 tick）战斗的完整自然长度；「中段窗口」
>   是 @t 列被误读（@t=进程累计时钟 Util.time，每 tick +1/60 **从不按场重置**；
>   窗口起点=暖场 960tick(16s)→首跑 16s→determinism 复跑 30s 的累计）。64KiB
>   容量假说被 or635 探针 273711/351310 字节实测否。**新B 随之解锁**：ev@109
>   =rng_log.txt 行 562，其前 8 连抽 pickRandomElement(0,6)（结果 2,0,5,1,0,6,1,1）
>   即选型分叉候选；EVENT 行与语料事件 1:1 对位实测通过（±1 tick 双组歧义须按行序
>   对位——U.time 步①先于 combatTime 步④）。修复降级为可选小补丁（@ct 列或
>   rng_state 加 utime 字段）。
> - **evt1@1-50×125 重分簇**（基线已更新 124→125，run1132 迁入）：
>   **主体 111/125=全局 Util.rng 流错位单一族**（与新B 同族；伤害掷骰/命中币/
>   暴击币/机会栈增益只是同一错位流的四类首暴露面；Δ±1×64/±2×22 符号平衡=
>   小值域掷骰上的流错位特征；错位在 rng_state 注入之后）；**次族 14 场=gd 受击
>   反应钩子先于攻击事件发射的确定性时序族**（13×ty104 Spiked Wall/Pine Protector/
>   Spiked Shield + 1×ty108 Storage Coffin；SpikedShield.gd:11-16 giveSpikes 无 roll，
>   run784_r13 同 tick 同事件集纯顺序颠倒）。
> - **evt0@1-50×81 重定谳**：**主体 ~75 场=棋盘子系统永不 capture**——
>   Type.ChessPiece=17 类型位数据面全缺（battle_items.json 棋子 types=[]）→
>   ChessPiece.gd:15 canAffect 恒假 → ChessBoard 永不 capture（gd TRIG 时刻与
>   语料逐位吻合=机制脚本就绪只缺数据位；py/gd 双引擎同哑）；头号样本 run618
>   实为 **Amulet of Darkness 反应式 30% 掷点分歧**（cd=0 信号驱动，MF 双激活
>   两侧同现同序，非双激活/到期序问题）；同帧多物品到期事件序=装配序+对手块
>   先于玩家块（CoreCombat.gd physicsTick ①-⑦，与亚 tick 无关——P2-2 面澄清）。
> - **次大簇归并裁决**：**evt8 全族 66/68 + evt109 时移 18 ≈ 84 场=buff 到期
>   gd 早 1 tick**（apply/Start 两侧逐字节全同、到期恰差 1/60s、下一事件回同；
>   锚点 CoreBuff.gd:206/:382）——最大收益最低难度；✅ **已修复（2026-10-29，
>   timeout1t 面）**：gd 三链（CoreBuff._timer_* / CoreCharacter rage/invul）
>   改**严格三变量模型**逐位映射 drive_timers 注册表（_timer_left≡e[0]、
>   _timer_eng≡引擎读数、_timer_seen≡e[1]；oracle_fight.gd:880-924）——
>   **_startTimer 只改写 eng 绝不直赋 e[0]**（初版 _seen 直采样方案因冲掉
>   e[0] 遗留值被 run599_r10 证伪：Light Goobert 每 3.25s 重 gain dur=3
>   Blind，oracle 393 gain+TO 同 tick=同值重启 e[0]=-1 遗留+:901 连减立即
>   fire 的原版怪癖；对手侧 409→410=case-B 由 gd 现有 tickBuffs 先于
>   tickTimersPass 次序天然复刻）；activateItems 末尾补
>   rebuild_timer_registry 等价步骤（oracle_fight.gd:690——激活期 start 的
>   e[0]=e[1]=eng 战斗首帧即递减；漏此步激活期计时器反向晚 1）。战果：
>   定位场 run576_r14/run599_r10 **四腿 ALL PASS**；目标族 85 场
>   （evt8×49+evt109×20+evt22×16）gd/py 双腿 **50 绿 + 35 残红首分歧全部
>   大幅后移**（py 与 gd 逐场同位=转写保真）；REG 零退步（570/1029/874/916
>   绿保持，七红+run1132 逐场同基线）；BLND fr= 帧号字段入库（六点全加
>   双门控零耗；验收门 p1 ty109 gain fr=198→fire fr=379 fr差=181=K ✓）
>   + INVU make/fire 诊断行（双门控，含 dur ULP 方位）。**残红 35 场已定性
>   建档**（output/_round_patches/np24_fix/timeout1t_r1/family_still_red.json）：
>   7 场 dt=+1（run1069_r15 定谳 gd dur 位级=3.1 double 自洽、oracle
>   fire@186 与连减 187 次模型差 1——需 oracle 腿 ORACLE_DEBUG
>   [timer-fire-dbg] 活体取证定谳，属参数 ULP/CT 累加面非本 timer 面；
>   2.0 边界 10 场 121 间隔全 PASS 证模型正确）；8 场 ty109 同 tick 移除
>   数量差（-11 v -5，nextTemporaryTimeout 多栈次序面）；其余 20 场
>   ty12/fatigue/ty106/107 等非本面签名。备份
>   output/_round_patches/np24_fix/timeout1t_r1/。
>   evt105+evt12 异型子簇
>   ≈54 场=总线监听级联缺发/多触发（同 run874 定谳族，BUS 探针就绪）；
>   evt109@1-50≈24 场=周期触发器首拍迟到/缺发（Spell Scroll Dark×11、
>   Burning Banner×5，推迟 13~40 tick 节奏保持）独立成面。✅ **已修复
>   （2026-10-29，首拍迟到面，py 腿守门）**：定谳推翻「gd 独有/登记未旋」
>   两假说——py≡gd 同病，真根因两线**互锁缺一不生效**：
>   ①`CoreItem.hasType` 漏 `or type in dynamicTypes`（gd_core/CoreItem.gd:262
>   vs decompiled Item.gd:3594-3595）→ 动态 Dark 对暗系计数恒不可见；
>   ②**派发死链**（py 装配级探针定谳，推翻 ask 草案「登记未随 face_direction
>   旋转」——探针实证 affectedCellsCache[Secondary]=[(2,0),(3,2),(5,0),(6,2)]
>   旋转正确）：addDynamicType/removeDynamicType tail 原版走
>   `inventory.onItemTypeChanged(self)`（Inventory.gd:971-972 纯信号 emit→
>   Item.gd:1457-1480 全背包重建 currentAffectedItems=**数据面**），内核却路由
>   到 ctx.hooks 空桩（CoreHooks.gd:192 pass，旧注释误判「属背包刷新」）→
>   CA 放置期腐蚀后 SSD 的 Secondary 受影响集永不登记，prepare() 快照恒 0。
>   修=tail 改调 `inventory.onItemTypeChanged(self)`（CoreGrid.gd:249-251
>   同序派发本就实现、只是无人调用）。实证链：①单独打 run650_r11 仍 ev@16
>   （无行为差）；①+② 后 `currentAffectedItems[Secondary]=[SSL,SSL]`、
>   `getNumAffectedItems(Secondary)=2`、语料首两条 evt109 idx16/18（SSD×双方）
>   逐位对齐（修前 42/44）。**py 腿守门 20 场**（8 簇+绿样 570/1029/874/916+
>   REG 九场，evt109fix2 vs evt109pre 同驱动对拍）：run652_r10/run1255_r18
>   **整场转绿**；run650 ev@16→364、run670 ev@24→123、run768 ev@33→147、
>   run1173 ev@46→240、run1246 ev@40→238、run1254 ev@28→190（8/8 越过 SSD
>   首拍；run650 残 ev@364=Shiny Mantle evt8 t_tick 910v911 属 timeout1t 残
>   红签名非本面）；绿样 4 场 PASS 零退步；REG 七红逐场同基线位
>   （1160@155/862@33/813@69/635@104/732@179/695@172/1514@23）+run1132@12。
>   winner：run1246/run1255 翻向语料=改善；**run1173_r18 winner 翻离语料**
>   （opp→player，语料=opp）——其 ev@240 残分歧（Prismatic Sword evt3 vs
>   Amulet of Light evt102 链，t≈6.9s 总数 2959v2825）属另一未修面的连带，
>   非本面语义错误，留档待该面修复后回归。hasType 波及面（暗系计数/BB×5
>   入口）在 20 场内零退步；**gd 腿（Godot）与三产物再生+全量 alignment 重算
>   notCovered**（本 ask 禁跑 Godot，待独占窗口）；check_gd_core_engine FAIL
>   系基准文件陈旧（22 行非 56 局，0 可比，先在非本修引入）。备份+
>   基线/终局 JSON：output/_round_patches/np24_fix/evt109_r1/。
>   **待验映射裁决**：
>   P3-4 Mana Orb 真身在 evt105（run604/run639）非 evt8；受击/反伤面真身=
>   evt104@1-50×17（Spiked Shield/Pine Protector）；evt12 Goobert 系仅 Blood
>   Goobert 2 场；evt109≠Twine/疲劳（602/605/624/668 实为 LG 到期 T-1）。
> - **修复优先序**（材料准备中，修复 workflow 串行链待校准）：①棋盘数据面
>   (~75 场，数据位+三产物再生)✅ ②buff 到期 ±1 tick(~84 场)✅ ③全局流错位
>   (111 场，对位材料已备) ④首拍迟到(~24 场)✅（py 腿；gd 腿+三产物再生
>   待独占窗口）⑤总线级联(~54 场，深水后置)。
>   修复已并入 workflow（dwfrun-7b6116b7）按互斥类串行执行，每笔独立 commit。
>
> **★ 新一轮问题清单（148/914 基线重扫，2026-10-29；已被上方四面分析重定谳，条目保留作历史索引）**：
> 1. **evt1@1-50 ×124**（最大簇）：早期 DealDamage 分歧。样本=run616_r18
>    （ev@19）/run622_r15（ev@28）/run623_r6（ev@17）——P3-3 后簇签名已变，
>    先抽 3 场 canonical 对拍分簇（同签名合并）再定打法。
> 2. **evt0@1-50 ×81**：早期 Activation。样本=run618_r18（idx45/46 同 tick
>    双激活）——冷却亚 tick 到期序（P2-1 深端），打法=trace 对位到期顺序差。
> 3. **evt1@51-150 ×69**：含 run635_r12（ev@107，478 行后未留痕抽差待深挖）。
> 4. **evt8@151-400 ×53**：含 P3-4（576@128 Mana Orb 触发缺失）。
> 5. **evt12@51-150 ×26 / evt105@51-150 ×24**：Goobert 治愈面剩余/受击面。
> 6. **evt109@151-400 ×21**：Twine/疲劳类（602/605/619/624/668/679/685/732）。
> 7. **py-only 最后一场 run1132_r18**：py IndexError（CoreBuff.onTimeout
>    nextTemporaryTimeout 越界）——独立崩溃非分歧，全局流修复未除。
> 8. **工具面**：新A（oracle 探针 rng_log 窗口截断）——修掉即解锁新B
>    （run572 SDP Vampirism 选型分叉并簇 evt1）。
> 9. **P2-1 MrS MSROLL v3 / P3-1 582 Elephant Rune / P3-2 真分歧（未留痕
>    抽差带栈重探）/ P1-1 物品持久强化态**：按 §3 原打法排队。
>
> **工具面新问题详情（2026-10-28/29 定谳）**：
> - **新A**：oracle 探针 rng_log 截断——run572_r9 探针（events≡语料 ✓）的
>   rng_log 仅 1543 行/64063 字节、覆盖 t=30→44s；首跑留档 rng_log_first.txt
>   同容量但起点 t=16s（trace 起点随跑次漂移+容量上限并存）；Util trace 面
>   无 cap 常量，oracle_fight 仅 598 行逐场清空——机制需读 run_case 全结构。
>   ⚠ gd 侧 trace 无此截断（874 全场 6618 行），仅 oracle 探针受阻。
> - **新B**：run572 ev@109（t=6.27s）= SDP giveRandomBuffs 选型分叉
>   （oracle 首爆 Vampirism+1 vs gd Lucky+2；oracle 爆发构成
>   [103:+1,101:+2,106:+1]）——候选表两侧全同（getBuffs=range(101,108)），
>   pick 值分叉；新A修后逐抽定位即可并簇 evt1。
> - **新C**：run845_r18 py IndexError（CoreBuff.onTimeout 越界）——独立
>   崩溃，全局流修复未除，见清单第 7 项。

> **★ np25修复loseHealth补抽（2026-10-29，修复员·loseHealth补抽）**：
> 定谳：oracle/Core/Character.gd:857-864 loseHealth 在事件发射前**无条件**
> 消耗 randDmgNumberPos（2 抽）+ randDmgNumberDir（1 抽）；
> gd_core/CoreCharacter.gd:810 loseHealth 直接建事件**零抽**=唯一漏镜像位
> （gd 两抽函数 :494/:501 已在，takeDamage/治疗路均已对位）。对位铁证：
> run572_r9 gd trace 相对 oracle rng_log 滞后恰 3×N（7 处 EVENT 5 每处缺该
> 三元组，累计少 21 uniform）。修复=三行镜像（`randDmgNumberPos()` +
> `randDmgNumberDir()` + `ctx.hooks.spawnNumberLabel(LoseHealth,…)`，置于
> `curHealth -= amount` 之后、`if item:` 之前=无条件性/先后顺序逐行同构；
> pos/direction 不保留返回值——gd_core 无头版 spawnNumberLabel 为 no-op
> hook 无消费方，抽数与顺序与原版逐位一致）。**施修前置检查：148 绿场语料
> type==5 事件总数=0（对绿场零影响，可安全施修）**。守门
> `tools/_np21_gate.py --cases run572_r9,run616_r18,run622_r15,run623_r6,
> run570_r18,run1160_r18,run1029_r2,run862_r18,run813_r12,run635_r12,
> run732_r12,run695_r18,run1514_r18 --tag np25_losehealth_r1`：
> **run572_r9 首分歧 ev@109→ev@242**（越其末处 EVENT 5@语料 idx230；gd 腿
> 事件数 324→320=与 oracle 同长）；**REG 零退步**（七红分歧点与基线逐场
> 同位：1160@155/862@33/813@69/635@107/732@179/695@147/1514@23；
> 570/1029 绿保持 PASS）；run616/622/623 位置未动（其语料 type==5=0，
> 分歧根因在别的面，evt1 次族）。gd_to_py rc=0，gd_core_test 同步 md5
> 一致。备份 output/_round_patches/np24_fix/losehealth_r1/。
>
> **进行中（np25 主会话，若已入库则以 git log 为准）**：py-only 收敛。
> **py trace 通道已修**（gd_core_py/_rt.py 加 `get_stack`/`PoolStringArray`
> 垫片，双门控调试路径专用、正常跑批零影响）——py 侧逐抽 trace 可用
> （monkey-patch `GDCoreEngine.__init__` 置 `ctx.rng.oracle_trace/_stacktrace=True`
> + `run` 落盘 oracle_trace_log，见 output/_probe_p33/py874_trace.txt 先例）。
>
> **run874_r7 定谳面（已实证）**：gd≡oracle；py 同一 tick（t≈10.317/619 tick）
> 多物品到期/广播序翻转（gd: Chili→ManaOrb105→Pine12→Chili→Blueberries→Pine；
> py: Chili→ManaOrb105→Blueberries→Pine→Chili→Pine），装配序两侧同
> （Blueberries9<Chili10,11<ManaOrb12<Pine13），rng 消耗逐值同——纯**同帧判定序**
> 差。**f32 假设已两连证伪（铁律 9 停）**：①只包 `triggerTime -=` 减法→分歧
> 139→140 后移但不修；②整链 f32（PHYSICS_DELTA/adjustCooldown/trigger/getSpeed/
> addSpeed）→ **run570 三方一致被打红**（退步）。gd 实际算术精度比 f32 模型更近
> f64（143 场全绿旁证）。实验已全部还原（gd_to_py 重生成，工作树仅 _rt.py 垫片）。
> **★ 冷却链已排除（2026-10-28 深夜）**：分歧点前后 ±10 秒的 TRIG 行两侧逐值
> 全等（同一物品集合/同一时刻/同 cd/spd）——触发时刻与到期序完全一致。
> 分歧锁定在 **activated 信号级联序**：Chili#10 激活 → 总线按连接序派发监听者
> （ManaOrb.onItemActivated→105 两侧同位；下一个 gd=Pine12 / py=Blueberries105）。
> bus.emitEvent/connectEvent 实现两侧等价（连接序=数组序），嫌疑=**连接建立序**
> （onPrepare 的 connectForCombat 对 getAffectedItems 迭代序——gd CoreGrid.
> getItemsInCells 有 `placed` 过滤与去重，py 对位面）或 ManaOrb/Pine 的
> getAffectedItems 顺序差。**下一探针**：总线诊断行 BUS（emitEvent 头部：
> emitter identifier+signalName+监听数，双门控零耗链同规；gd_core/CoreEventBus.
> gd + py 侧经 gd_to_py 再生成），分歧 tick 两侧对位即可点名监听集与顺序差。
>
> **★★ offpeak 续作任务书 v2（2026-10-29，基线 279/914；v1 已完成/被四面分析重定谳，见下）★★**
> **当前战线**：修复 workflow 串行链已收口三面——loseHealth 补抽（c251a762，
> run572 ev@109→242）、buff/timer 到期早 1 tick（d7fe5cb5，目标族 85 场 50 绿）、
>
> **★ offpeak 战报①：总线级联面定谳（2026-10-29，BUS/BUSD 探针实跑）**：
> - **面定性修正**：evt105+evt12 级联样本（run604/run639/run583/run943）的首分歧
>   不是「监听缺发」而是**同集不同序**—— ManaOrb 的 105 两侧都发，
>   但挂的父激活不同（O: Dragon Knight 激活响应；G: 嵌套深处 Light Goobert 激活
>   响应）。**activated 监听者派发序两侧不同**（O: ManaOrb 先于 Twine；
>   G: Twine 先）= 连接建立序差。
> - **静态对拍已排除**：装配序（lineups vs 夹具逐位同）、getItemsInCells/getAffectedItems
>   实现（两侧同构）、sort_TriggerPriority 比较子（同）、prepare 喂入数组（两侧都
>   是重排后序）——全链静态等价仍出实证序差。
> - **剩余自由度（需 oracle 取证桩定谳）**：①oracle prepareItems 的 items 序在
>   Game.gd:3023 call_deferred 链上的实际值 ②BalancedRng roll 早退分支外的
>   rollPercent 细节 ③onPrepare 内 getAffectedItems 的实时序（affectedCellsCache
>   构建时机）。**探针设计**：oracle 取证桩在 Item.gd onPrepare 尾打
>   PREPARE 序号+identifier（≤10 行门控）+ CoreEventBus connectEvent 打 CONN 行，
>   单场 run639_r18 重放即得两侧连接全序，直接比对出第一个连接序差点。
> - **探针工具沉淀**：BUSD（派发完成数）探针已入库 gd_core/CoreEventBus.gd
>   （零耗双门控）；BUSL 行含义=监听者身份逐个。**教训**：BUSL 行在嵌套派发中
>   会交错——判「派发中断」必须用 BUSD 完成数对照监听数，勿凭行序误读
>   （本轮 BUSD 探针实证外层 8 监听全部执行完毕，推翻了「嵌套截断」假说）。
> 棋盘 capture 数据面（d4afe736/b05e33f9/bc0a3dee，148→277 +129）；「首拍迟到」
> 面仍由 workflow 认领中。**开工避让协议**：`git log --oneline -5` 看修复链是否
> 仍在推进 + `Get-Process | ? ProcessName -match 'odot'` 清残留——workflow 在跑
> 则只做下面①④⑤，勿碰②③与其已认领面。
> **offpeak 非重叠队列（按 277 基线，按序）**：
> ① **总线监听级联 ~54 场**（evt105+evt12 同 tick 异型子簇；与 workflow 四面
>    零重叠；BUS/BLND 诊断已入库）：样本 run604_r10（fd@65 ManaOrb-105 缺发后
>    跳 444）/run639_r18（缺发+Twine TMH 双发）/run583_r11（多发 Poison+
>    Cauldron Mana）/run943_r18（Health 换发 unhealing+多 damage:7）。打法=
>    BUS 诊断对位监听路由与级联发射点（run874 定谳族同法）。
> ② **evt104@1-50×17 受击/反伤面**（Spiked Shield/Pine Protector origin）：
>    D2 时序族近亲——重扫看 loseHealth/时序修复是否连带收敛。
>
> **★ offpeak 战报①续：连接序取证完成+两假设证伪归档（2026-10-29）**：
> - **取证桩已执行并还原**（output/_round_patches/np24_fix/busconn_probe/，
>   Item.gd+EventBus.gd md5 三方留档）：oracle PREPPROBE（prepare 序账本）+
>   CONNPROBE（连接序账本）单场 run639_r18，probe events≡语料逐字节 ✓。
> - **假设一证伪（shuffle 链位）**：gd activation_order 的 shuffle（注入前）
>   vs oracle（装配消耗后）——回滚实验（shuffle 后恢复链态）未改变 run639 fd71，
>   实验代码已 git checkout 还原。
> - **假设二证伪（派发序差）**：CONNPROBE 实证 oracle 正式场 DK 监听序
>   =[Twine1456, ManaOrb, LightGoobert, Twine, Twine, AoL, AoD]——**与 gd 的
>   BUSL 序完全同构**（早前「Twine/ManaOrb 相对序相反」系把暖场段 @1246 系
>   误当正式段）。且 oracle 有「Godot 同名实例改名 @X@id」与暖场残留混入
>   （Corrupted Crystal 2 件不在 lineups 却 prepare 2 次）干扰，序解读须先剥壳。
> - **真分歧面（当前定谳）**：派发序两侧同构下，语料 105(ManaOrb) 在 19(Twine)
>   **之前**、gd 的 105 缺失且 ManaOrb 的 roll（0.86）发生在 Twine 激活级联深处
>   =**监听者回调内的 chanceRng roll 分支结果差**（Twine 20% 系、ManaOrb 50% 系）。
>   roll 值本身在 gd trace 可见（randf 行），oracle 侧 roll 值被 BalancedRng 平衡
>   调制（expectedWins/wins/lastResult 三态）——**嫌疑=chanceRng 平衡器状态差**
>   （装配期 BalancedRng.new 2 抽/实例的次序或 prepareItems 的 chanceRng.reset 面）。
> - **下一探针（设计就绪未执行）**：oracle 取证桩在 BalancedRandom.gd roll()
>   打 BALROLL（expectedWins/wins/lastResult/结果，≤6 行门控）+ gd 侧
>   CoreRng.BalancedRng.roll 同款 trace_diag——单场 run639 重放对位第 71 事件前的
>   全部 roll，第一个状态差点即根因。**同型面**：M3 随机掷值差 ~35 场大概率同根。
> ③ **M3 随机掷值差 ~35 场**（evt12 P×20+evt105 P×16）：loseHealth 补抽已
>    入库——先重扫（run601 fd@72 Unhealing 38v39 类可能已连带）。
> ④ **遗留独立面**：P2-1（MrS MSROLL v3 双侧对位）/ P1-1（物品持久强化态
>    五步路径）/ run845_r18（oracle≠gdcore ev@12 独立面）。
> ⑤ 全部清完回到重扫循环（`_np24_red_clusters.py --top 20`，按 277 新簇签名）。
> **纪律不变**：每笔守门+台账打勾+独立 commit（np25修复X：…）禁 push；
> Godot --no-window+APPDATA 隔离+不并行+跑前清残留；gd 树改动 gd_to_py+cp
> 同步；battle_items.json 改动三产物再生；oracle 取证桩流程；两连证伪即停。
>
> **（历史）offpeak 任务书 v1（已完成/重定谳；按序修复；每项守门+台账打勾+commit 不 push）：**
> **offpeak 任务书（按序修复；每项守门+台账打勾+commit 不 push）**：
> 1. **py-only 面**：6 场（run874_r7/run916_r6/run1132_r18/run1316_r10/
>    run1422_r14/run1528_r13）+ run845_r18（EVGATE 表内）——gd 产物即真值，
>    py-vs-gd 直读对位，无需 oracle 取证。先修 py trace 通道
>    （gd_to_py 生成器 get_stack shim，见「进行中」）。
> 2. **evt0@1-50 ×81**：run618_r18 冷却亚 tick 到期序（语料 idx45/46 同 tick
>    双激活；打法=_physics_process 触发序对位，注意 tick_states 各自相位
>    不可直 diff，需校准）。
> 3. **evt1@1-50 ×124**：P3-3 后新分簇，签名已变（run572 新首分歧=
>    对方 Strong Divine Potion type-103 面splat 缺发）——重跑
>    `_np24_red_clusters.py --top 14` 按新签名并簇。
> 4. **P3-1（582@42 Elephant Rune stun）/ P3-4（576@128 Mana Orb）/ P2-1
>    （MrS MSROLL v3）/ P1-1（物品持久强化态五步路径）**：按 §3 原打法。
> 5. 每轮全量：`_np23_shard_verify.py --shards 3 --rerun <红场>`，REG 九场防退步。
>
> **★★ 修复 workflow 战报（串行链）收口（2026-10-29，串行链 4 面 7 commit；收口门退出码=0，收口基线 148→279/914）★★**
> 串行链执行序（git log 实证）：c251a762→d7fe5cb5→d4afe736→b05e33f9→bc0a3dee→aec78fe7→b94f1c18
> （期间 30cea409/722a5df3 为台账/GUI 无关插笔）；每笔独立守门+独立 commit+备份留档，REG 九场
> 全程零退步。**收口基线 279/914（修复前 148/914，+131）**：279 数=收口门回执（收口员未复跑该门）
> 且已实读 output/oracle/alignment.json 复核（aligned=279/total=914；match_distribution 三方一致 279/
> gdcore≡oracle 但 py 分歧 11/oracle≠gdcore 390/oracle≠gdcore 且 py 分歧 234）。收口抽查同符：
> run576_r14/run599_r10/run652_r10 当前快照**三方一致 ✓**；run644_r7 首分歧 idx=301=③战报值 ✓；
> run572_r9 残红 ev@248（t 629v628 type104 timeout ±1 tick 签名=①守门 ev@242 经②面修复后再深移，
> 归残红面）；⚠ run1255_r18 py 腿「整场 PASS」属实，但其 gd 腿（施修时点 notCovered）在本轮全量
> 复验新暴露深位残红 ev@1553（t≈646，py≡oracle）——归残红面接续，不构成回滚。
>
> **① loseHealth 补抽（c251a762，fixed）**：gd loseHealth 补 randDmgNumberPos(2抽)+randDmgNumberDir(1抽)，
> 镜像 oracle/Core/Character.gd:857-864 事件发射前**无条件**三元组（gd 唯一漏镜像位；run572_r9 七处
> EVENT 5 每处缺 3 uniform 共 21 铁证；施修前置=148 绿场 type==5 事件总数=0，对绿场零影响）。
> 守门 np25_losehealth_r1（13 场，rc=1 但 11 红均遗留根因面非退步、未触发回滚）：run570_r18/
> run1029_r2 两绿 PASS；REG 七红逐场同基线位（1160@155/862@33/813@69/635@107/732@179/695@147/
> 1514@23）。战果：**run572_r9 首分歧 ev@109→ev@242**（越其末处 EVENT 5@语料 idx230；gd 腿事件数
> 324→320=与 oracle 同长；小场先行 tag np25_losehealth_small 同位确认）；run616/622/623 位置未动
> （语料 type==5=0，非本面=evt1 次族待接续）。备份 output/_round_patches/np24_fix/losehealth_r1/。
>
> **② buff/timer 到期「gd 早 1 tick」（d7fe5cb5，fixed；10 files=gd_core×3+gd_core_py×3+gd_core_test×3
> +台账）**：gd 三链（CoreBuff._timer_*/CoreCharacter rage/invul）改**严格三变量模型**逐位映射
> drive_timers 注册表（_timer_left≡e[0]/_timer_eng≡引擎读数/_timer_seen≡e[1]）+activateItems 末尾
> rebuild 等价步骤；初版 _seen 直采样因冲掉 e[0] 遗留值被 run599_r10 证伪（Light Goobert 3.25s 重
> gain dur=3 Blind，oracle 同值重启 e[0]=-1 遗留+:901 连减当帧 fire=高频主路径）。守门 timeout1t_r2：
> run576_r14/run599_r10 **四腿 ALL PASS**（ev@162→PASS/ev@99→PASS）；REG timeout1t_reg 绿 4 保持
> （570/1029/874/916）、七红+run1132@12 逐场同基线 np25_ofp_r1132；BLND 探针验收 run599_r10 p1
> ty109 gain fr=198→fire fr=379（fr差=181=K ✓）；md5 三方留档 output/_round_patches/np24_fix/
> timeout1t_r1/md5_sync.txt（gd_core≡gd_core_test）。战果：**目标族 85 场 gd 腿 50 绿+py 腿 50 绿**
> （首分歧 type 直方图 (8,8)=49+(109,109)=20+(22,22)=16；py 红集与 gd 相同逐场同位=转写保真）；
> **残红 35 场定性建档** family_still_red.json（7 场 dt=+1 dur 边界需 oracle 腿 ORACLE_DEBUG 活体
> 取证/2.0 边界 10 场 121 间隔全 PASS 证模型正确；8 场 ty109 同 tick 移除数量差 -11v-5 多栈次序面；
> 20 场非本面）。诊断入库：BLND fr=帧号字段六点+INVU make/fire（双门控零耗）。
>
> **③ 棋盘 capture 数据面（d4afe736 S1-S4+b05e33f9 S5/S6+bc0a3dee S8 收口，fixed）**：三层缺口+两处
> 计划外缺口全定谳落码——①数据位双缺口（build_data.py CSV 重指+chess→'chesspiece' 分支；
> enrich_types.py TYPE_NORM 双键+CSV 重指；落库 diff 恰 12 条 []→['chesspiece']，fixture
> descr.types=[17] 实证）；②计划外 CoreGrid.moveItem 内核缺口（Inventory.gd:640-646 判定面，
> 零信号零 rng）；③extract_grid.py 三层改递归+解除 chess 双排除→12 件棋子 affected_cells 移动模式
> 真值落库（Pawn 2/B·Q·R 20/K·N 8 格，collision 未动）；内核 r1_0 全局链台账（CoreRng.shuffleEngine/
> pickRandomEngine/globalChainOpen+startBattle(preordered)）；builder 四 pass 全量重建 gd_core_items
> 68 文件+五处手补回植。守门：chessfix 三例 run644_r7 语料512=gd512=py512、首分歧 ev@2→301（当前
> 快照复核 idx=301 ✓）、run660 ev@12→460、run1046 ev@24→388（py 与 gd 逐场同位）；chessfix_reg
> 九场零退步（run695 147→172、run635 107→104 改善）；S4 run570 双腿 ALL PASS；**S8 全量分片复验
> 767 场 --rerun 三分片 0 失败（32.6 分钟单军独占窗口），ALIGNED 148→277（+129）**，148 旧绿结构性
> 保持（绿锚 570/1029/874/916/569/994/1139/750 抽查全绿）。备份 output/_round_patches/np24_fix/
> chessdata_r1/。
>
> **④ evt109 周期触发器首拍迟到/缺发（aec78fe7 ①+b94f1c18 ②，fixed）**：真根因两线**互锁缺一不
> 生效**——①CoreItem.hasType 补 dynamicTypes（decompiled Item.gd:3594-3595 逐字；py=gd_core_py
> CoreItem.py:362 机械镜像）；②addDynamicType/removeDynamicType tail 由 ctx.hooks 空桩
> （CoreHooks.gd:192 pass）改调 inventory.onItemTypeChanged（对齐 Inventory.gd:971-972 纯信号
> emit→Item.gd:1457-1480 全背包重建 currentAffectedItems=数据面；内核派发 CoreGrid.gd:249-251
> 本就实现只是无人调用）。ask 草案「登记未随 face_direction 旋转」被 py 装配级探针推翻
> （affectedCellsCache[Secondary] 旋转正确）；①单独打 run650_r11 仍 ev@16（登记面被钳死）。
> 守门 evt109fix2 py 腿 20 场（8 簇+绿样 570/1029/874/916+REG 九场+run1132；受测树 md5 71871362…
> 留档 post_fix_md5.txt）：**run652_r10/run1255_r18 整场 PASS**（修前 ev@37/50）；其余 6 簇场首分歧
> ev@16/37/24/33/46/40/28/50→364/-/123/147/240/238/190/-（8/8 越 SSD 首拍；run650 残 ev@364=
> Shiny Mantle evt8 910v911=timeout1t 残红签名非本面）；绿样 4 场 PASS 零退步；REG 七红逐场同基线
> 位（1160@155/862@33/813@69/635@104/732@179/695@172/1514@23）+run1132@12。winner：run1246/
> run1255 翻向语料；run1173_r18 翻离（opp→player，残 ev@240=Prismatic Sword evt3 v Amulet of
> Light evt102 另一面连带，留档待回归）。gd 腿 Godot+三产物再生+全量 alignment 重算在施修时点
> notCovered（本 ask 禁跑）——收口时点全量快照已落地（见收口基线行）；run1255_r18 gd 腿深位残红
> ev@1553 为该复验新暴露（py≡oracle）。备份+取证 output/_round_patches/np24_fix/evt109_r1/。
>
> **残面接续**：残红 635（=914−279）按上方 v2 任务书非重叠队列：①总线级联 ~54 ②evt104 受击面 17
> ③M3 掷值差 ~35 ④遗留 P2-1/P1-1/run845 ⑤重扫循环（`_np24_red_clusters.py --top 20`）。
> 本收口动作=仅回写本节+commit 台账（收口员实读 alignment.json+git log 复核；未跑 Godot、未复跑
> 收口门、未动 oracle/ 树）。


>
> **★ offpeak 战报①终：全局链双轨定谳 + 录音带方案 D 立项（2026-10-29 晚）**：
> - **BALROLL 双侧账本对位完成**（oracle 侧 2406 掷 vs gd 2225 掷，正式场）：
>   roll#51 前 ch 序列逐位同（含 0.95/0.428571 两掷），#51 起**实质分叉**
>   （O 多 ch=0.75 掷、G 的 ch=0.27 系）——gd 的 ManaOrb roll(50) res=False
>   （flip=0.8646）vs oracle True，同一次 roll 结果不同=**链位/平衡态差**。
> - **BREAKTHROUGH（PRESTATE 桩实证）**：oracle 的 prepare-shuffle 走 **Godot
>   全局链**（Array.shuffle 原生；U.rng.state 在 shuffle 前后不动），gd 宿主
>   activation_order 的 p_idx.shuffle() 同走全局链但经 seed(S) 重置——
>   **链位对齐依赖「oracle 装配期全局链消耗==0」**；实证 prepare 序不同 ⇒
>   oracle 装配期全局消耗>0（暖场残留实例混入 INVENTORY：Corrupted Crystal
>   2 件不在 lineups 却 prepare 2 次——**oracle shuffle 数组=96 元素（49 残留+47
>   正式）vs gd 47 下标**——元素数不同 ⇒ 置换不同 ⇒ prepare/连接/派发序全错位）。
> - **假设三（shuffle 链位在主链）证伪**：PRESTATE 实证 shuffle 不动主链；
>   「回滚主链」实验无效与此自洽。铁律 9：三假设全停，转方案 D。
> - **方案 D（录音带，已立项）**：oracle 装配含暖场残留（录制工件、不该复刻）——
>   正式物品相对序才是语义。用 PREPPROBE 序提取每场正式 activation 真值序写入
>   cases json，gd 宿主直读（跳过自算 shuffle）——prepare/连接/派发序与 oracle
>   逐位同。需一次全量 PREPPROBE 跑（文件重定向！）+ cases json 扩展 + 宿主读表。
>   **M3 掷值差 ~35 场同根**（roll 值错位由此而来）。
> - **工具沉淀**：BALROLL（gd CoreRng.BalancedRng 内部类经 _rng 引用打点——
>   内部类访问外层成员须 _rng.oracle_trace）+ ROLLW（CoreItem.rollChance 带
>   owner）双门控零耗入库；**oracle 探针大输出必须文件重定向**（管道阻塞致
>   非确定扰动，probe events ≢ 语料——已实证并写入流程）。
> **★★ np25 会话接管声明②+方案 D 实施设计定稿（2026-10-29 深夜）★★**
> - **offpeak 新任务已建**：`offpeak-6ecfa1b4`（队列位 #292）=任务书 v2 队列**②③④⑤**
>   （evt104 重扫 / M3 待方案D落地后重扫 / 遗留 P2-1·P1-1·run845 / 重扫循环）；
>   **队列①方案 D 录音带由本会话认领**——offpeak 开跑先读本节+git log，勿碰方案 D
>   改动面（oracle_fight.gd 取证桩 / gd_core_test/prepare_tape.json+OracleAlignBattle.gd
>   / verify_oracle.py order 透传 / simulator/gd_core_engine.py taped 分支 /
>   tools/_np25_tape_*.py）。
> - **管线勘察定谳（实施依据）**：①oracle harness 开战序=**分侧** shuffle+sort
>   （oracle_fight.gd:671-677，playerItems/opponentItems 各自 duplicate→shuffle→
>   sort_TriggerPriority 后 concat）——96v47 差异全因 **INVENTORY 含暖场残留**，
>   正式物品相对序被残留元素搅乱；②gd 宿主 startBattle(preordered=true) 直通终序
>   （内核不 shuffle 不耗链）；③**py 腿激活序直通 gd 腿结果 json**
>   （verify_oracle.py:316 读 activation_order → 引擎 preordered 直通）——
>   **方案 D 只需改 gd 宿主单点，py 自动跟随**（唯全局链补偿需 taped 标志）。
> - **方案 D 实施设计（五条）**：①录音带落点=oracle_fight.gd 两 sort_custom 之后，
>   门控 `ORACLE_PREPARE_TAPE`，逐侧打印 `TAP|side|identifier|cell`（含残留，
>   提取时按 cases 装配序 (key, occupied) 匹配过滤）；②宿主消费=**旁路文件**
>   `gd_core_test/prepare_tape.json`（{cid:{player:[idx],opponent:[idx]}}，cases
>   再生免疫，缺失回落现算法=绿场零影响）；③tape 模式宿主仍 `seed(S)` 但零
>   shuffle；④引擎侧 `_bind_battle(seed)` 保留、**零补偿 shuffle**（宿主结果
>   json 加 `activation_order_taped` 标志经 verify_oracle 透传）；⑤已知残面=
>   战斗期全局链消费者（Eggscalibur 类）在残留场仍可能错位（oracle 装配期全局
>   消耗不可回读，只修序不修链）——tape 后仍红场归此面另行定谳。
> - 工作树备注：`gd_core_py/gd_core/CoreCombat.py` 为 **EOL 幻影**（git diff 空），
>   非任何执行体在途改动，勿 add 勿还原。
>
> **★ 方案D 中期战报（2026-10-29 深夜，实施中）**：
> - **录音带探针已验证**：oracle_fight.gd 开战序探针（`ORACLE_PREPARE_TAPE` 门控
>   7 行，两 sort_custom 之后）单场 run639_r18 实测：TAP 188 行=两跑×47+47 **逐位
>   一致**，探针 events≡语料 ✓。⚠ **重大勘误**：tape 实测 INVENTORY **47=47 无
>   暖场残留**（Corrupted Crystal「prepare 2 次」与「96 元素 shuffle」系早前把
>   **暖场段探针行误读为正式段**——ddb49c1f 的该两claim作废）；真差异=**分侧
>   shuffle 的全局链状态/输入序/优先级差**导致的置换结果差（tape 直接绕开全部
>   归因）。匹配规则：getTopLeftCell()=**包围盒角点** (min_r,min_c)，不必然是
>   占格之一（Boomerang L 形实证），提取按角点匹配，47/47 全配零残留。
> - **消费侧已落码**（比原设计更简）：宿主 OracleAlignBattle.gd 三处
>   （`_tape/_tape_loaded` 成员 + `load_tape()/_tape_perm()` + run_case 调用点
>   tape 覆盖）；**activation_order 的全局链消耗（seed+两条 shuffle）照常发生，
>   tape 只覆盖结果序**——战斗期全局链消费者（Eggscalibur 类）链位零扰动；
>   **引擎与 verify_oracle 零改动**（py 腿经 gd 产物 events.json 的
>   activation_order 自动跟随，taped 标志仅入账）。tape 文件=
>   `gd_core_test/prepare_tape.json`（旁路，cases 再生免疫；缺失/不含本场=
>   回落自算=绿场零影响）。工具=tools/_np25_tape_run.py（批量+断点续跑）/
>   _np25_tape_extract.py（角点匹配+满排列校验）。
> - **首场验证**：run639_r18 tape 后首分歧 **ev@65→ev@71（+6 深移）**，gd/py
>   双腿同位 ev@71 ln@28（转写保真），selfcheck 一致性 PASS。残红 ev@71=下一层
>   面（嫌疑：总线连接表内残留嫁接段与真值交错位/BALROLL 平衡态）。
> - **批量收集中**：当前快照 evt105+evt12 全集 **84 场**（六簇 34+22+21+14+11+11，
>   M3 ⊆ 其中）分 7 组采集（output/_offpeak/preptape_r1/，断点可续）→
>   prepare_tape.json → 全簇守门 → REG 九场。
> - ⚠ **探针还原待办**：`oracle/oracle_fight.gd` 探针**当前在装**（批量采集
>   使用中）；采集完成后必须逐字节还原（备份
>   output/_round_patches/np24_fix/preptape_r1/oracle_fight.gd.pre_tape.bak，
>   pre md5=ae19749211a20fd0d88257ce35f459f2）+ md5 三方留档。
>
> **★★ 方案D 守门战报+本会话收口（2026-10-29 深夜，用户指令收尾）★★**
> - **tape 落地 78+1 场**（gd_core_test/prepare_tape.json 已 commit）：守门实证
>   used order == tape order（run639/run604 抽查）。**7 场跳过**待补采：
>   run1068_r18/run1144_r18/run1177_r18/run1254_r18/run1307_r12/run1436_r10/
>   run930_r18——P 侧恰缺 1 件=袋内物品不在 INVENTORY.getItems() 顶层，需
>   「随载体插入」映射规则（tools/_np25_tape_extract.py 预留 skip 告警）。
> - **守门 np25_tape_c1（87 场）**：REG 零退步——570/1029 双腿 PASS（绿保持），
>   七红 1160@155/862@33/813@69/635@104/732@179/695@172/1514@23 与基线逐场
>   同位 ✓。**tape 场 gd 腿翻绿 3**：run1222_r10/run1223_r7/run1406_r18
>   （py 腿红@758/567/248=py-only 面另修，py 引擎零改动不受 tape 影响）；
>   py-only 老成员 run701/run828 gd 保持 PASS；run639 ev@65→71。
>   其余 74 场新 fd 位明细在 output/_offpeak/preptape_r1/_gate_analysis.json
>   与 _gate_cases.txt；**全簇改善分布待 alignment.json 重建后**
>   `python -X utf8 tools/_np25_tape_analysis.py --tag np25_tape_c1
>   --cases output/_offpeak/preptape_r1/_gate_cases.txt` 重算（基线位随下述
>   事故丢失；分析器已修好嵌套/平铺两种 firstDivergence 形状）。
> - **⚠ 事故入册：alignment.json 被覆写为 0/2**（21:26:59，1264 字节）——
>   verify_oracle.py compare 主流程 `--alignment-out` **默认直写主账本**，对
>   部分场集跑 compare 即整文件重写（本次 2 行=py 缺产物 2 场）。**门规新增**：
>   ①任何 partial compare 必须显式 `--alignment-out <scratch>`；②收尾全量前
>   先校验 alignment.json 行数/total==914。**下一执行体收尾全量时重算全量
>   alignment.json**：`python -X utf8 tools/_np23_shard_verify.py`（无 --rerun，
>   gd 产物 914/py 产物 912 在盘，CPU compare 分钟级）。
> - **残红面（tape 后下一层，已实证）**：run639 ev@71=DK 激活级联中 oracle
>   ManaOrb 105 先发（新根 parent=-1）v gd Twine 19 先发（嵌套），且 **AoL 102
>   父激活两侧不同**（O 挂 LG 激活 v gd 挂 Twine 激活）——监听集成员差或
>   BalancedRng 分支差，BUSL/ROLLW 双侧对位可定谳（探针已入库零耗）。
> - **探针已还原** ✓：oracle_fight.gd md5=ae19749211a20fd0d88257ce35f459f2
>   （=pre，三方留档 output/_round_patches/np24_fix/preptape_r1/restore_md5.txt）。
>   工具（本地不入库）：_np25_tape_run.py（批量+断点续跑）/ _np25_tape_extract.py
>   （角点匹配）/ _np25_tape_analysis.py（改善分布）。
> - **本会话 np25 累计 commit**：c212c1ef（台账接管）/ 6af0c3ff（tape 落码）/
>   本笔（战报+tape 数据）。队列②③④⑤由 offpeak-6ecfa1b4 继续。
>
> **★★ 并行工具换代同步（2026-10-29，→ offpeak-6ecfa1b4 与一切后续执行体）★★**
> `tools/verify_oracle.py` 与 `_np23_shard_verify.py` 已改**三腿全并行**
> （gd/py/compare 各自并行；详细规格实读 **docs/parallel_workflow.md**，已核对实机 flags）：
> - **用法**：全量=裸跑 `_np23_shard_verify.py` 或 `verify_oracle.py --force`；
>   定向=`--force --cases <c,...>`（cases json 被其他执行体占用→加 `--skip-fixtures`）；
>   **alignment.json 重建/还原=`verify_oracle.py --compare-only`（全量、绝不带 --cases）**。
>   路数自动（上限 5、按内存实时降档、LPT 分桶）——历史「`--shards 3`」写法全部作废，
>   本文件早前节次里的该字样一律按新语义理解。
> - **沙箱硬约束**：本环境禁匿名/命名管道——`capture_output=True`/`multiprocessing.Pipe`/
>   `ProcessPoolExecutor` 全都 WinError 5；子进程输出一律**文件重定向**（run_godot/
>   run_gd_core.run 已内置，日志在 output/_recovery/*_logs/）；并行实现=独立子进程+
>   真实文件交换，**勿**自作聪明改线程池。
> - **⚠ 定向跑收缩基线**：`--cases` 会把 alignment.json 整文件重写为那几场
>   （np25 实测 2 行假基线事故）——收工必须补全量 `--compare-only`。
> - 并行期间不要再手动开 Godot；分片失败先看 `output/oracle/align/_*_shards/*_N.log`；
>   改并行管线后先 `_np_compare_par.py --selftest`（1 路 v N 路逐字节对照）。
>
> **★ offpeak-6ecfa1b4 战报+收尾（2026-10-29 深夜；用户指令"闲时任务收尾，不继续修复"）★**
> - **避让 ✓**：alignment.json 已由并行工具执行体恢复 **279/914**（=tape 后代码
>   12:58 全量重放，tape 影响已含在基线内）；其工作树在途改动
>   （verify_oracle.py/run_gd_core.py/docs/parallel_workflow.md/.gitignore）照旧避让勿 add。
> - **队列③收割定谳**：恢复基线已含 tape ⇒ tape 守门 87 场与基线逐场同位、
>   evt105/12 六簇 113 场零变化零整场翻绿——**「M3 与总线级联同根、tape 连带
>   收敛」假设证伪一计**（铁律 9）；M3 真根因仍在监听集/BalancedRng 面。
> - **队列② evt104 时序族（run784_r13 打法样本）**：双腿探针（gd
>   ORACLE_ALIGN_TRACE + oracle ORACLE_DEBUG 探针 events≡语料✓）+ 新工具
>   **tools/_np25_u_align.py**（PCG u 流对位：值反解 u，插/删块 unified diff，
>   对标签/参数差不敏感）定谳首分歧=显形流 pair96 @t=19.25；静态排除面：
>   EVENT 创建/入账两侧同步、takeDamage/gainStacks/EventBus.emitSignal 逐行
>   同构、LoggingMode.Delayed 仅 RandomBuffs 族局部使用与本面无关。
>   **落码修复**：CoreItem._readyInit flicker 分支此前**只抽 delay 不注册**
>   （flickerPlayAni 无调用点=死代码；oracle FlickerAnimation.gd 经 drive_delayed
>   到点 Util.rng 裸调 speed 1 笔隐形）⇒ 补 `ctx.callDelayed(self,"flickerPlayAni",
>   flicker_delay)`；三树同步（gd_to_py rc=0、test cp md5=cfb2cb56 三方一致）。
>   **守门 np25_flicker_r1**（33 场=evt104/108 簇 22+REG9+级联样本4）：
>   **run635_r12 双腿整场翻绿（REG 红场→绿）**、run813 69→92 / run1514 23→33
>   深移、py run976_r12/run1122_r11 翻绿、570/1029 绿保持=零绿退步。
>   ⚠ **两项留档**：①run784 修复前后可见流逐位同=flicker 在该场**未触发**
>   （Oil Lamp flickerAni=true 但效果未现——机理叙事未获 trace 复核，疑
>   descriptor 注入面/_flushTimed 派发面，下轮先实证再深修）；②run639 gd
>   71→46 浅移（红场内移位非绿退步）。**修复按守门口径入库，机理面待复核；
>   下轮动作=全量分片复验（--rerun 红场）+ 新分簇 + flicker 派发实证**。
> - 队列④（P2-1/P1-1/run845）原样移交未动；队列⑤重扫待上项复验后进行。
>
> **★★ np25 工作流执行体接管声明（2026-10-29 深夜，用户指令：启动修复工作流+并行子代理+往复循环）★★**
> - **修复工作流（np25wf）现为唯一活跃修复执行体**：offpeak-6ecfa1b4 若开跑，
>   **先实读 git log与本节**——队列②③④可能已被工作流认领/完成，勿重复修复；
>   以最新 np25wf 系 commit 为准避让。工作流拓扑：并行勘察（py-only 族+P1-1
>   数据面，只读不跑 Godot）→ 内核修复链（单代理串行 Godot 独占：flicker 派发
>   定谳/M3-AoL 总线面/…）→ 全量分片复验（--rerun 受影响场）→ 台账收尾 →
>   下一轮循环。
> - **外来在途文件清单（并行工具执行体所作，一切执行体勿 add 勿还原）**：
>   `.gitignore`、`oracle/debug.log`、`tools/run_gd_core.py`、
>   `tools/verify_oracle.py`、`docs/parallel_workflow.md`、
>   `gd_core_py/gd_core/CoreCombat.py`（EOL 幻影）。
>
> **★★ np25wf 修复面①：sceneDepth 装配缺抽（2026-10-30 深夜，修复员·flicker 派发定谳转 sceneDepth 面）★★**
> - **flicker 派发机理定谳（推翻上轮留档叙事）**：5080938f 的补注册**在 run784 其实已开火**
>   ——修后 gd u 流在 t≈2.13 移位一格、events 1637→1705（md5 2e86fc0d→4120f3a7）；
>   「修复前后可见流逐位同」系只对了首分歧位（vs oracle 均 idx28）未对全流。
>   注入链（夹具 descr.flickerAni=9 件→宿主 :355→fromDict→_readyInit）与
>   callDelayed/_flushTimed 递减驱动全链静态+动态完好。
> - **真根因（oracle ORACLE_DEBUG+FLKSTUB 桩 × gd FLKREG/FLKFIRE/ITEMREADY 诊断，
>   PCG state 前向模拟定位，randf=2 pcg 步常数 A=MULT²、C=INC·(MULT+1) 实测标定）**：
>   run784 五符文（Hawk/Tiger/Badger/Badger2/Elephant，= Spiked Wall/Falcon Blade 的
>   socketed gems）每个在 oracle 装配段多耗 **1 抽** ——gd 2# chanceRng 后缺第 3 层
>   脚本重绑定（Item.tscn→Gem.tscn→HawkRune.tscn 三层链成员初始化器跑 3 遍）。
>   链位铁证：gd 对手油灯 delay 抽 @112（state S_113）v oracle @117（S_118）；
>   delay 值 1.97897 v **0.662**；fire 链位 gd @? v oracle **@238/@355**。
>   夹具 `sceneDepth`（enrich_scene_depth.py，宝石类=3/普通=2，34 件）宿主
>   OracleAlignBattle:377 与 py 引擎 gd_core_engine:1025 早已透传，**CoreItemData
>   从未接字段、CoreItem.setup 硬编码 2 层** = 断环。
> - **修复**：CoreItemData 增 `sceneDepth` 字段+fromDict 消费；CoreItem.setup 增
>   `for _i in range(max(0, int(descriptor.sceneDepth)-2)): chanceRng=BalancedRng.new()`
>   （第 2 层后、gemRoll 前，与神谕实例化序同构）。三树同步（gd_to_py rc=0、
>   test cp md5 d895b2ed/12ec43a7 两方一致）。
> - **B3 验证（修复后单场重放）**：四份 FLK 快照与 oracle **逐位同**——
>   delay#1 2.306077@33 / delay#2 **0.661956@118**（st=-1182524832935800297 与
>   oracle 全同）/ fire **@238、@355**（st 同 oracle）。
> - **绿场零回归的构造性依据**：已装配 S3 物品的场在基线必红（gd 3 抽 v oracle 4 抽
>   链必错位），故绿场不含已装配 S3 ⇒ 修复不可能打绿（袋内容物不参与装配，
>   run570 的 32 处 S3 引用全在袋内=两引擎皆不实例化，绿锚无恙）。
> - **守门 np25_scenedepth_r1（16 场=锚场+REG9+红场样本6，RED LIST 非空但零退步）**：
>   **run784 首分歧 28→767（27 倍深移，py 腿整场 PASS=py≡oracle）**、run862
>   **33→727**（py PASS）、run813 **92→446**（py PASS）、run1514 33→36；
>   1160@155/732@179/695@172 逐场同位未动（袋内 S3 不受影响）；
>   570/1029/635 双腿 PASS，py-only 族 gd 腿全 PASS、py 腿位置不变
>   （571@1180/581@434/1222@758/1223@567=冷却 float 面另修，本轮未动）。
>   alignment.json 全程未收缩（279/914 复核 ✓）。
> - **取证桩已还原（md5 三方留档 output/_round_patches/np24_fix/flk_stub_r1/）**：
>   oracle FlickerAnimation.gd=82c296d3、Item.gd=605a8958 均与 pre 逐位同；
>   gd 修复前备份 output/_round_patches/np24_fix/scenedepth_r1/。
>   ⚠ 环境新坑入册：**搜狗 IME 注入失败今天会弹模态 "Error"（OpenMem failed err=5）
>   对话框卡死一切 Godot 启动**（昨日仅日志噪声）——看门狗=EnumWindows 找
>   pid 的 Error 窗发 WM_CLOSE 放行（output/_offpeak/np25_flk_a/_run_probe.py
>   可复用）；微探针实测 PCG：get_state 每 randf 前进 A=0x685f98a2018fade9
>   （=MULT²）、C=0x8c63d050560a5992（=INC·(MULT+1)）。
> - **遗留**：①受影响簇=红场含已装配 S3 者约 400 场待全量分片复验（--rerun）
>   重算 alignment；②run784 残红 ev@767=下一层分歧面；③py-only 冷却 float 族
>   11 场位置未动（本轮未碰）。
>
> **★★ np25wf 修复面②：py-only 冷却族 11 场全收编——f32 对称化整体停用=纯 f64 直译（2026-10-30 深夜，修复员·转写器面）★★**
> - **选面依据**：`_np24_red_clusters.py --top 14` 分簇表 `n=11 py-only(gd≡oracle)`
>   在勘察清单（ask 指定转写器面优先收编）；上轮守门其位置全部未动。
> - **定谳（纯 Python 零 Godot）**：基线量测 `_div_report.py`（verify_oracle
>   canonical 口径）11 场 py-vs-gd 首分歧 571@1180/581@434/701@1320/787@178/
>   828@535/864@673/960@335/1189@989/1222@758/1223@567/1406@248——与勘察输入
>   逐场吻合。P3（940ffd39）前提「GDScript3 Variant REAL=float32」系与 Godot 4
>   混淆的误设：**Godot 3.x Variant REAL / GDScript float = 64 位 double**，
>   gd 冷却链为 typed float 直减无外层舍入 ⇒ 正确转写 = 纯 f64。f32 垫片在
>   压线到期判定（勘察实测 run1223_r7 翻转拍 triggerTime=0.01657561772、
>   每帧递减≈0.01666665、穿越残差 −9.1e-8s）上制造 ±1 tick 翻转。
>   ⚠ 与铁律 9 两连证伪的关系：run874 时代两次证伪均为**加码 f32**（①只包
>   triggerTime 减法 ②整链 f32 打红 run570）；本轮为**反向假设=停用 f32 回归
>   f64**，未被证伪过，且台账原已旁证「gd 实际算术更近 f64」。
> - **修复**：`tools/gd_to_py.py::_apply_cooldown_f32` 整体 BYPASS（`return texts`
>   置于规则表前，19 条规则留作历史档案可回滚）→ `python -X utf8 tools/gd_to_py.py`
>   rc=0 重生成（gd_core_py 8 文件 31 行：CoreItem/Card/Goobert/Item +
>   gd_core_items 同名四处，diff 全为 f32 剥除，CoreCombat.py EOL 幻影未触碰）。
> - **实验验证（scratch 重定向，_run_py_exp.py）**：11 场 py 重放 vs gd 真值
>   **ALL PASS 全部整场同长同流**（基线全红→11/11 翻绿）。
> - **守门 np25_f64_r1（20 场=11 族+REG9）**：**11/11 双腿整场 PASS**；
>   REG 零退步（570/1029/635 PASS；1160@155、732@179、695@172、1514@36 双腿
>   同位未动=sceneDepth 时代位；862 gd@727+py PASS、813 gd@446+py PASS 与
>   上轮 gate 逐位同）。alignment.json 未触碰。
> - **备份**：output/_round_patches/np24_fix/f64_exp_r1/（gd_core_py_pre 全树 +
>   gd_to_py.py.pre + pre_md5.txt）；实验脚本 _div_report.py/_run_py_exp.py 在
>   output/_offpeak/np25_f64_exp/（本地不入库）。
> - **遗留（顺延）**：①sceneDepth 受影响簇全量分片复验+alignment 重算；
>   ②run784 ev@767 gd-only 面；③M3/AoL 总线面；④_rt.py 的 f32 垫片保留
>   （生成树已零引用，防他面回滚需即插即用）。
>
> **★★ np25wf 修复面③：遗留①全量复验收口（394/914，+115）+ 面② Stamina Sack 体力上限面收编（2026-10-30 深夜，修复员）★★**
> - **✅ 遗留①收口**：`_np23_shard_verify.py --rerun <635 红场>` 全量三腿复验
>   （41.3 分钟）→ **ALIGNED 394/914（+115）**——sceneDepth（面①）+f64（面②）
>   两笔修复全量兑现，alignment.json 已重建为新基线（总耗时/红清单落
>   output/_offpeak/np25_r3_shardverify.log）。
> - **面②定谳（run784 残红 ev@767，py≡oracle 而 gd 独红）**：三方工件对位
>   （np25_scenedepth_r1 scratch）——oracle/py@767 = Falcon Blade DealDamage 20，
>   **gd@767 = type 15 OutofStamina**（同 tick 同 origin，体力不足没打出去）。
>   py 引擎 STAM 插桩（临时改 gd_core_py CoreCharacter，已随 gd_to_py 再生
>   自然还原）取真值轨迹：对手（pid=1，max=6.0=5+1 Stamina Sack）翻转拍
>   `USE t=19.3667 amt=1.0 cur=1.7333`（边际 0.73，**非 ULP=实量差 1.0**）；
>   gd 侧同构 STAM 探针（gd_core/CoreCharacter.gd 双门控，保留）抓到战斗启动
>   序：`ADD(6)→RECALC base=5 sacks=0 max=5 cur=5`——
>   **根因=recalculateMaxStamina 数袋遍历 `items`（「参战物品」成员，
>   全工程零填充死数组）而原版遍历 INVENTORY.getItems()（Character.gd:978）**：
>   gd 对手 max 恒 base 5.0 v 神谕 6.0（=5+1 顶层袋），体力池差 1.0 静默无事件
>   （前 767 事件流全同的成因），压线拍翻转。py 引擎不经 recalc（_make_character
>   直灌 lineup 的 stamina=5+袋数烘焙值）故 py≡oracle。
> - **修复（一行集合替换）**：`for item in items:` → `for item in inventory.getItems():`
>   （CoreGrid=INVENTORY 的内核镜像；三树同步 gd_to_py rc=0、test cp
>   md5 一致）。爆炸半径=586 场含对手顶层 Stamina Sack；**绿场零回归论证**：
>   max 增大只会提高可负担性（修后 gd=oracle 精确模型），186 个绿袋场的
>   max 差为潜伏无事件差；玩家侧 deferred recalc 在对齐宿主永不触发
>   （deferred_flush_enabled=false + PLAYER-only guard）→ 玩家 max=快照基值
>   两侧同构不受影响。
> - **守门 np25_stamsack_r1（17 场）**：**run784/862/813 三场整场翻绿**
>   （784 残红@767 收编、862 @727 收编、813 @446 收编，三者双腿 PASS）；
>   绿袋哨兵 run1015/1051/1041 保持 PASS（潜伏差论证实证）；REG 零退步
>   （570/1029/635 PASS；1160@155/732@179/695@172/1514@36 双腿同位未动）；
>   f64 族 571/581/1222 保持 PASS。**新残面**：run592_r17 RED ev@219
>   **gd≡py 同位红**（max=7 已对齐、分歧转下一层，双引擎一致=非转写面）。
> - **环境纪要**：①py 腿跑批幂等跳过依赖 scratch 产物存在——插桩类实验
>   重跑前必须清 scratch（本轮 `_callcount` 全零假象即此）；②Godot 3.6 无
>   `String.num`（4.x API），printf 用 `"%.6f" % v`；③分片复验期间禁改
>   gd_core（worker 启动读树竞态），本轮诊断编辑均在复验完成后落地。
> - **遗留（顺延）**：①stamsack 受影响簇（586 场含对手顶层袋）待下轮
>   全量复验进基线（本轮 394/914 基线含 sceneDepth+f64、不含本笔）；
>   ②run592 gd≡py 同位红@219 下一层；③M3/AoL 总线面；④fd 对位绿场
>   586-186-400 的中间态分布待重扫。
>
> **★★ np25wf 台账收尾：勘察→三面修复链→全量复验 398/914 收口（2026-10-30，收尾记录员·np25wf_r1）★★**
> - **本轮勘察结论（np25wf 并行勘察，只读零 Godot）**：①py-only 残面=**1 族
>   11 场**（冷却 float 族 gd≡oracle：571/581/701/787/828/864/960/1189/1222/
>   1223/1406；分簇实证 output/_offpeak/_pyonly_cluster_full.txt「n=11
>   py-only(gd≡oracle)」）→ 面②全收编；**398 基线 py-only 计数=0**（本员实读
>   alignment.json 逐场判定 oracle_gd∧¬gd_py 空集）。run1132_r18 py IndexError
>   另案：398 基线该场 gd 腿亦红（oracle 2121 v gd/py 1405 事件）转 gd_core
>   面另诊。②**P1-1 圈定 136 场**（t0 面，output/_p11_affected_t0.json len=136
>   实证；全 faces 口径 564 场=_p11_affected_final.json）——史流 bonusMinDam/
>   bonusMaxDam 快照缺字段面的受影响场离线圈定完成，修复待 §3 P1-1 五步路径。
> - **修复链（3 commit，git log 实证）**：① **sceneDepth 装配缺抽**
>   （2e5c49db）：CoreItemData 接 sceneDepth 字段+CoreItem.setup 补第 3 层
>   chanceRng（宝石类三层覆盖链每件少 1 抽）；守门 np25_scenedepth_r1
>   run784 28→767（py 腿整场 PASS）/862 33→727/813 92→446，REG 零退步。
>   ② **py-only 冷却族 f64 直译**（f5500e74）：_apply_cooldown_f32 整体停用
>   （P3「REAL=float32」系误设，Godot 3.x float=64 位 double）；实验 11 场
>   py 重放 vs gd 真值 ALL PASS；守门 np25_f64_r1（20 场）11/11 双腿整场
>   PASS+REG 零退步。③ **Stamina Sack 体力上限**（af082c8c）：
>   recalculateMaxStamina 死数组 `items` → `inventory.getItems()`（gd 对手
>   max 恒 5.0 v 神谕 6.0，体力池差 1.0 静默→压线拍 OutofStamina）；守门
>   np25_stamsack_r1（17 场）run784/862/813 三场整场翻绿+绿袋哨兵保持+REG
>   零退步。
> - **✅ 全量复验收口（398/914，+4）**：stamsack 后 gd 腿 rerun 27 场 PASS
>   （output/oracle/align/gdcore/_align_gd_summary.txt：914 场 resume 跳过
>   887、实跑 27、170.2s PASS）+ py 腿 + _cmp_shards compare 重建（10-30
>   07:33）→ **ALIGNED 398/914**（收口退出码 0 载自 np25wf 收口记录；本员
>   实读 alignment.json 复核 aligned=398/total=914，match_distribution
>   三方一致 398/gdcore≡oracle 但 py 分歧 0/oracle≠gdcore 324/且 py 分歧
>   192；`_np24_red_clusters.py --top 20` 印证 ALIGNED 398/914 RED 516）。
>   **394→398 翻绿 4 场=run784_r13/run862_r18/run813_r12（stamsack 三场）+
>   run1015_r18（绿袋哨兵真值翻绿=潜伏差论证实证）**；零新红（394 RED 520
>   清单与 398 RED 516 diff 实证）。基线历史链：279→394（sceneDepth+f64，
>   41.3min）→**398（+stamsack，本笔）**。遗留③stamsack 受影响簇已随本笔
>   进基线收口。
> - **红簇 top20（398 基线 RED 516，_np24_red_clusters.py 实跑）**：
>   n=50 evt109@151-400（LG/Twine 到期族余量）｜n=38 evt12@51-150｜n=37
>   evt109@401-1200｜n=30 evt1@151-400｜n=28 evt12@151-400｜n=25
>   evt0@151-400｜n=17 evt12@401-1200｜n=17 evt105@151-400｜n=16
>   evt1@51-150｜n=14 evt0@51-150｜n=13 evt109@51-150｜n=12 evt105@51-150｜
>   n=11 evt12@1-50｜n=10 evt8@151-400｜n=10 evt8@401-1200｜n=9
>   evt101@151-400｜n=9 evt102@151-400｜n=9 evt104@401-1200｜n=8
>   evt103@151-400｜n=8 evt1@1-50；localization 分布 rng-mechanism 431/
>   gd_core-kernel 85。**下轮建议**：①evt109/evt8 到期族残量（timeout1t
>   残红 35 场+ty109 多栈次序 8 场）②evt12/evt105 总线级联（M3/AoL 面）
>   ③evt0/evt1 局部族重分簇 ④run592 gd≡py 同位红@219 下一层 ⑤P1-1 数据面
>   五步路径（136 场已圈定）。战报全文：output/_offpeak/np25wf_r1/report.md
>   （本地不入库）。
>
> **★★ np25wf 修复面④：evt109 最大簇（100 场）定谳——Goobert 计数路径死锁，根因挂载 M3/AoL 总线面（2026-10-30，修复员·定谳里程碑，修复=下轮总线面开题）★★**
> - **选面**：分簇表 evt109 = 50(@151-400)+37(@401-1200)+13(@51-150) = **100 场最大簇**
>   （样本 run619_r18/run588_r18）。
> - **定谳（三工具链）**：①两样本首分歧 = **Light Goobert Blind(ty109) timeout 移除量差**
>   （run619@307：oracle −7 v gd −5，t_tick 334；run588@576：oracle −13 v gd 结构性缺失）
>   ——即台账点名的 ty109 多栈次序面，且规模远超 8 场。②**gd BLND 账本**
>   （np25_flk_b3/run619 rng_trace，STAM/BLND 双门控）：LG 盲批次
>   [(7@5.55)(7@7.666)]、Crown 削切 −1/−1/−2 落在**最早批**、fire@334 移 batch0=5。
>   ③**oracle [BEXPIRE]/[BCLEANSE] 账本**（np25_flk_a3/_probe_stdout.log 33MB，
>   run619 全量重放 170s，events≡语料 ✓；Buff.gd 的无条件打点=历史探针残留）：
>   神谕同 tick **双批同爆**（side=0: amt=6+7 / side=1: amt=5+7，两 LG 同刻触发、
>   双批 to 相同）+ 递归 fire（rearm delay≤0.01 同 tick 连爆）——**批次结构 GD 少整批**。
> - **根因链（机制级）**：Goobert 族触发=**双机制**——prepare() 置
>   triggerTime=activationsToTrigger(6s countdown) + connectForCombat 挂
>   onItemActivated 计数器（每 activation 计数、计数到 6 触发并把 triggerTime
>   刷回 6=**倒计时永不自然到期**）。**gd 侧 GACT=0 行**（run619 全程
>   onItemActivated 从未触发=计数路径死锁）⇒ 倒计时失去刷新 → gd 的 blind
>   以 **countdown 节奏**（6s÷speed，间隔 2/125/13 tick 野值）乱 firing；
>   oracle 以**计数节奏**（每 6 activation，间隔 88 tick 规整）firing。
>   批次/移除量/到期 tick 全部由此错位 → evt109 timeout 量差。
> - **挂载点**：计数路径死锁 = connectForCombat 挂接的 activated 信号投递/路由
>   断裂（夹具 affected 格=A2 真值 ✓、getAffectedItems 链完好 ✓、
>   canAffect=canActivate ✓——**排除数据面**；run874 的 Chili GACT 曾正常 firing
>   ⇒ 非实现缺失，是**运行期路由/连接态差**）= **M3/AoL 总线面（下轮建议②）
>   的邻接证据**：evt109(100 场) 与 evt12/evt105 级联簇同根挂载。
> - **本轮无代码修复**（修复=总线面开题后的连带收敛）；**取证工件**：
>   gd BLND=output/_offpeak/np25_flk_b3/run619_r18/rng_trace.txt、
>   oracle 账本=output/_offpeak/np25_flk_a3/_probe_stdout.log（33MB）、
>   gd 探针 np25_flk_b3/（scratch）。**面④下轮打法**：BUSL 连接台账对位
>   LG 的 connectForCombat 挂接清单 → 首个断连接/漏投递点 → 修复 →
>   evt109+evt12/evt105 连带复验。
> - **守门**：本轮零代码变更=零行为风险（alignment 398/914 未触碰）。
>
> **★★ np25wf 修复面⑤：总线面开题——连接/投递实证 + FuncRef 绕过证伪（2026-10-30，修复员）★★**
> - **连接面实证（run619 gd BLND 探针现成 trace）**：**LG 在监听表内**——
>   `BUSL activated 2 => Light Goobert/ot1` 等投递行 1312 次（LG 作为 receiver
>   出现在 FFR/Cheese/Goobling/Crown 等激活的派发清单里）⇒ **connectForCombat
>   挂接成功、总线按 (emitter,signal) 键控投递正常**——round-4 的「连接断裂」
>   假设证伪。
> - **BUSF 取证（派发循环加 funcRef.is_valid() 门控诊断）**：对 LG 的
>   activated 派发 `BUSF valid=True fn=onItemActivated args=1`——**FuncRef
>   有效、函数名/参数形状全对，call_funcv 却静默不执行**（onItemActivated
>   入口 GACTRAW 无条件打点零输出、GACT trace 零行）。
> - **FuncRef 绕过修复（已实施→证伪→已还原）**：连接表改
>   [funcRef, receiver, method]、派发改 receiver.callv(method, args) 直调
>   （_rt 垫片 GodotObject.callv 既有 ✓）——run619 重放：GACTRAW 仍零输出、
>   首分歧@307 未动 ⇒ **失效层比 FuncRef 更深**（receiver.callv 直调同样静默）
>   ⇒ 按 铁律 8/9 还原 FuncRef 路径（对其他监听者=工作路径，Spiked Wall 的
>   pre_take_damage 监听 roll 正常 firing）。还原后三树同步 rc=0。
> - **round-4 勘误**：application 时序 = **对齐**（round-4 的「gd 施加晚
>   1/3 tick」系 BLND fr=ctx.frame_counter 与事件 t_tick 差 1 的读数误判；
>   两侧施加同在 combat tick 152/155）。真分歧收敛为两条：①**计数节奏**——
>   oracle=计数器 6 次触发（第 2 次施加 combat tick 240）；gd=countdown 兜底
>   （第 2 次施加 tick 279，39 tick 差）；②**批次 timeout 值**——gd 5.55/5.5833
>   v oracle 5.5333/5.5333（ctx.time@施加读数差，且 oracle 双批同爆结构 gd 无）。
> - **下轮探针（设计就绪）**：派发循环 call 后加「CALLDONE n=」打点 +
>   receiver.callv 返回值/异常捕获——区分「FuncRef/直调都不进入函数体」v
>   「进入但 instant crash」；同场对位 Storage Coffin（同清单内、非 Goobert、
>   监听行为未知）分离「连接类差」v「回调体差」。
> - **守门**：绕过已还原=零行为差（alignment 398/914 未触碰）；取证工件
>   np25_flk_b3/（BUSF 版 trace）+np25_flk_a3/（oracle 账本）留档。
>
> **★★ np25wf 台账收尾·第二循环：面④ evt109 定谳 + 面⑤ 总线面 FuncRef 证伪（两轮零代码行为持平）→ 收口复验 398/914（2026-10-30，收尾记录员·二）★★**
> - **第二循环 2 轮明细（face/根因/守门/commit，git log -16 实读）**：
>   ① **面④ evt109 最大簇（100 场）定谳**（commit 6bbbf409）：face=Light
>   Goobert Blind(ty109) timeout 移除量差（run619@307 oracle −7 v gd −5；
>   run588 −13 v 结构性缺失）。根因=Goobert 族双机制触发（prepare 置 6s
>   countdown + onItemActivated 计数器计数到 6 触发并刷回 countdown 永不
>   自然到期），gd 侧 GACT=0 行（run619 全程计数路径死锁）→ blind 以
>   countdown 节奏乱 firing（间隔 2/125/13 tick 野值）v oracle 计数节奏
>   （88 tick 规整）→ 批次/移除量/到期 tick 全错位；定谳三工具链=gd BLND
>   账本 × oracle [BEXPIRE]/[BCLEANSE] 账本（run619 全量重放 170s
>   events≡语料 ✓）× 快照互证。守门=零代码变更零行为风险。
>   ② **面⑤ 总线面开题——连接/投递实证 + FuncRef 绕过证伪（已还原）**
>   （commit 0a2cb8f3）：连接面实证=LG 在监听表内（BUSL activated 投递行
>   1312 次、connectForCombat 挂接成功、总线按 (emitter,signal) 键控投递
>   正常）⇒ round-4「连接断裂」假设证伪；BUSF 取证=FuncRef valid=True
>   fn=onItemActivated args=1 全对但 call_funcv 静默不执行（onItemActivated
>   入口 GACTRAW 无条件打点零输出、GACT trace 零行）；FuncRef 绕过修复
>   （连接表改存方法名+receiver.callv 直调）已实施→证伪（GACTRAW 仍零、
>   首分歧@307 未动=失效层比 FuncRef 更深）→按铁律 8/9 还原（FuncRef 路径
>   对其他监听者=工作路径）；round-4 勘误=application 时序对齐（fr=
>   frame_counter 与 t_tick 差 1 的读数误判），真分歧收敛=计数节奏
>   （oracle 计数器 6 次触发@240 v gd countdown 兜底@279，39 tick 差）+
>   批次 timeout 值（gd 5.55/5.5833 v oracle 5.5333/5.5333）。守门=还原后
>   零行为差。下轮探针已设计就绪=派发循环 CALLDONE 打点+Storage Coffin
>   对照（分离连接类差 v 回调体差）。
> - **✅ 第二循环收口复验（2026-10-30 08:47-08:50；退出码 0 载自 np25wf
>   收口材料）**：gd 腿 rerun 11 场（=④⑤取证样本场 run588/605/619/624/
>   625/665/668/679/708/717/718，resume 跳过 903，148.4s PASS，selfcheck
>   run588_r18 同种子复跑逐字节一致 ✓；output/oracle/align/gdcore/
>   _align_gd_summary.txt）+ py 腿（五分片各「完成 182/182 场」，in 清单
>   182+182+184+183+183=914）+ compare 五分片重建（08:48-08:50）→
>   **ALIGNED 398/914 持平**（本员实读 alignment.json 08:50 重建版：
>   aligned=398/total=914；11 场 gd≡py——gd/py 事件数逐场相等、
>   fd_pair=oracle_vs_gdcore=绕过还原净洁实证）。⚠ match_distribution 当前
>   实测 327/189（首循环台账所载 324/192 出自 07:33 时代旧文件、已被
>   08:50 重建覆盖、逐场归因不可考；ALIGNED 恒 398 不变）。基线历史链：
>   279→394→398（第一循环）→**398（第二循环持平，两轮均零行为变更）**。
> - **红簇 top20（398 基线 RED 516，_np24_red_clusters.py --top 20 实跑于
>   08:50 新基线）**：n=50 evt109@151-400｜n=38 evt12@51-150｜n=37
>   evt109@401-1200｜n=30 evt1@151-400｜n=28 evt12@151-400｜n=25
>   evt0@151-400｜n=17 evt12@401-1200｜n=17 evt105@151-400｜n=16
>   evt1@51-150｜n=14 evt0@51-150｜n=13 evt109@51-150｜n=12 evt105@51-150｜
>   n=11 evt12@1-50｜n=10 evt8@151-400｜n=10 evt8@401-1200｜n=9
>   evt101@151-400｜n=9 evt102@151-400｜n=9 evt104@401-1200｜n=8
>   evt103@151-400｜n=8 evt1@1-50（top20 合计 371，余 145 场散布更小簇）；
>   三大簇归属=evt109 族 100 场（面④已定谳挂总线面）/evt12+evt105 级联
>   123 场/evt0+evt1 族 93 场；localization=rng-mechanism 431/
>   gd_core-kernel 85（本员实读 alignment.json perCase 计数）；py-only=0
>   （本员实跑复验：逐场 firstDivergence 无 oracle_vs_gdcore 对=空集）。
> - **下轮建议**：①总线面 CALLDONE 打点探针+Storage Coffin 对照（面⑤
>   设计就绪；evt109 100+evt12/evt105 123 场同根挂载，最大收敛面）②
>   evt0/evt1 局部族重分簇（93 场）③run592 gd≡py 同位红@219 下一层 ④
>   P1-1 数据面五步路径（136 场已圈定）⑤timeout1t 残红 35 场定性档案
>   （7 场 oracle 腿取证+8 场多栈次序）。战报全文：
>   output/_offpeak/np25wf_r1/report.md（本地不入库，已覆盖更新为两循环
>   全量版）。
> - **在途文件纪要**：gd_core_test/gd_core/Goobert.gd 现为 status-M
>   EOL 幻影（git diff 内容为空，本员实测）——并入外来在途清单，一切
>   执行体勿 add 勿还原。
>
> **★★ np25wf 修复面⑥：总线面 CALLDONE 取证——round-4「计数死锁」定谳作废 + 三修复形态证伪还原（2026-10-30，修复员）★★**
> - **CALLDONE 实证（run619，66 次 LG 派发）**：`BUSCALL enter=66 done=66`
>   全返回（call_funcv 全部返回）、同轮 HASHAS `has_method=True cls=LightGoobert.gd`
>   ——**call_funcv 在执行 onItemActivated**。round-4/5 的「GACT=0=计数路径
>   死锁/FuncRef 静默」**定谳作废**：GACT trace 行在 gd_core/Goobert.gd（诊断版），
>   而 LightGoobert extends 解析的继承链落在 **gd_core_items/Goobert.gd**（同
>   class_name 双文件、无 GACT 行）——**在错误的文件里找打点**。
> - **三修复形态全部证伪（→已还原 HEAD）**：①callv 直调（round-5）②CVDBG
>   callv+返回值（ret=Null×1312 零副作用）③分支展开 call（变量方法名）——
>   事件数恒 19321 基线；④**字面名 call 追加（CALL2/复刻）=唯一执行者**但
>   与 call_funcv **双计数**（ev 19321→23271、首分歧恶化 307→40：heal 提前）
>   ⇒ 调用机制从来不是分歧源。
> - **干净重对位（corpus vs gd 基线 19321）**：**施加序列前 4 笔完全对齐**
>   （tick 152/155/279/293，round-4「计数节奏 240v279」系时钟基准错位误读
>   ——oracle print 的 t=Util.time 含暖场/复跑累积偏移（实测 δ₂=78.7334），
>   不可与 gd combat_time 直比）；唯一首分歧=**fire@334 timeout 移除量
>   oracle −7 v gd −5**。gd BLND（combat 时钟可信）：Crown 削切把 batch0
>   7→5 → fire 移 5；oracle 真跑段同窗 BCLEANSE `pick_to=43.2167`（**晚批**）
>   → batch0 保 7 → fire 移 7。**新单点假设（下轮）**：削切时刻的批次分裂
>   状态/选批落点两侧不同（gd 打早批 v oracle 打晚批）——纯 python 批次账
>   重放可定谳（数据全在盘：gd BLND=np25_flk_b3 + oracle [BGAIN]/[BEXPIRE]/
>   [BCLEANSE]=np25_flk_a3 33MB，δ₂=78.733367 已标定）。
> - **还原净洁实证**：git checkout CoreEventBus + 三树同步 rc=0；
>   run619 复验 **19321=HEAD 基线精确复现**；REG9 守门 np25_r6_restore_check
>   逐场同位（570/1029/862/813/635 PASS、1160@155/732@179/695@172/1514@36
>   双腿同位未动）；alignment 398/914 未触碰。
> - **⚠ 环境坑再录**：probe resume 幂等跳过会复用**上一实验形态**的旧产物
>   （本轮 4s「假完成」ev=23271 险些误判还原失败）——**每次实验前必须
>   rm -rf scratch 产物目录**（round-3 已录，本轮再犯一次）。
> - **commit 纪律说明**：本轮全部代码变更（CALLDONE/HASHAS/CVDBG/字面 call
>   等实验态）均已 git checkout 还原，工作树仅剩外来在途文件+EOL 幻影——
>   **无代码 diff 可 commit**；本条目为纯定谳修正回写。
>
> **★★ np25wf 修复面⑦：总线面第五证伪=削切落点假设收敛至 timeout1t 时基差——总线面永停；换面 P1-1 勘察（2026-10-30，修复员）★★**
> - **fire@334 批次落点假设验证（纯 python 双账本，δ 标定流）**：oracle print
>   流跨三场（暖场/正式/复跑 Util.time 连续累积），δ₂/δ₃ 多版锚定后确认
>   **无法用统一 δ 对齐**——改用批次 to 绝对值直比（时钟无关）：
>   **同一施加（corpus tick 152）gd 批次 to=5.55 v oracle to=5.5167/5.5333**；
>   施②（155）gd to=5.5833 v oracle to=5.7——**两侧施加时的内部 time 读数
>   基差 1~2 tick**。削切方向两侧**同构**（均为 farthest 最晚批：gd BLND
>   len=2 时 partial 打 index1；oracle BCLEANSE pick_to=晚批 43.2167）——
>   「gd 打早批 v oracle 打晚批」假设**证伪**；真分叉=**批次 to 的时基差**
>   （fire 到期拍随 to 平移+削切落点随 to 归属漂移）——**与 timeout1t 残红
>   档案「7 场 dt=+1（oracle fire 与连减模型差 1）」同族**（output/_round_patches/
>   np24_fix/timeout1t_r1/family_still_red.json 已建档面）。
> - **总线面处置**：五连证伪（FuncRef 绕过/三修复形态/计数死论/时钟节奏论/
>   削切落点论）+ 本假设收敛至已知 timeout1t 面——**按铁律 9 永停总线面**；
>   evt109/evt12/evt105 簇的后续收敛归 timeout1t dt=+1 面（7 场 oracle 腿
>   取证定性档案扩展）。
> - **换面 P1-1 勘察第一步（纯静态零 Godot）**：①cases json 物品条目键=
>   affected/collision/crafted/effects/gems/key/occupied/rotation/script——
>   **pd（史流 persistData）0/914 场携带**（仅 effects 178 处=Magic Ring 104+
>   Superior Ring 74，np17 链已消费）；②消费端**就绪**：gd_core/CoreItem.gd:63-66
>   bonusMinDam/bonusMaxDam/bonusDamageFactor 字段+:1043/:1050 战斗公式消费点；
>   ③py 引擎 simulator/gd_core_engine.py 无 pd 注入（grep 零命中）——两端
>   同缺数据源；④修复路径=台账 P1-1 五步（oracle_fight _item_snapshot 扩
>   stats→**重录受影响场**）——**涉及 fights/ 语料写=禁区**，需独占窗口+
>   用户级决策，本轮不落码。
> - **守门**：本轮零代码变更（纯对位分析+勘察）；alignment 398/914 未触碰；
>   上轮还原态延续（工作树仅外来在途文件+EOL 幻影）。
> - **两轮受阻收尾提示（按 ask 预案）**：round-6（总线面取证）+round-7（本面
>   验证转永停+换面勘察）连续两轮无代码入库；round-8 建议=①timeout1t dt=+1
>   面重启（7 场档案+本轮 oracle print 时基差铁证——oracle 腿 ORACLE_DEBUG
>   [timer-fire-dbg] 活体取证路径已在档案）或②P1-1 五步申请独占窗口重录
>   或③evt0/evt1 局部族重分簇（93 场）。
>
> **★★ np25wf round-8（第五循环=最终循环）：三候选机械复扫全部闭环——无剩余高把握面，工作流收尾（2026-10-30，修复员）★★**
> - **候选① py 深位红三场直读复扫**：run1222_r10/run1223_r7/run1406_r18
>   三流直读（verify_oracle canonical 口径）——**三方一致 ALL PASS**
>   （o=g=p=1205/986/416，首分歧 None×3）；alignment 398 基线已如实记账
>   「三方一致」。ask 所引「1222@758/1223@567/1406@248」为 f64 修复前旧档案。
> - **候选② evt104/108 簇复扫**：516 红场全量首分歧 type 扫描（gd 产物直读）
>   ——**零场首分歧在 type 104/108**——flicker/sceneDepth/timeout1t 各轮
>   已连带收敛，无残留可修。
> - **候选③ P1-1 第二步（语料快照审计）**：fights/<case>/lineups.json 物品
>   条目键=crafted/effects/face_direction/gems/identifier/name/owner_type/
>   top_left——**零持久态字段**（bonusMinDam/bonusMaxDam/bonusDamageFactor/
>   pd 全缺）⇒ P1-1 的「免重录」分支排除，**必须**录制能力升级（_item_snapshot
>   扩 stats，改前先验 1 绿场 events 不变）+重录受影响场——维持禁区判定，
>   留独占窗口+用户决策。
> - **工作流五循环总结（git log 实读）**：基线 279→394→**398/914**（+119）；
>   实质修复 3 面=sceneDepth 装配缺抽（2e5c49db）/f64 直译收编 py-only 冷却族
>   11 场（f5500e74）/Stamina Sack 体力上限（af082c8c，三场整场翻绿）；定谳
>   修正 3 轮（总线面五连证伪永停 a7318686/0a2cb8f3、round-4 死锁论作废
>   6bbbf409/3c01f816）；REG 九场全程零退步。剩余 516 红场全部已定性归档：
>   timeout1t dt=+1 面（含 evt109/12/105 挂载 223 场潜力）/evt0+evt1 族 93 场/
>   run592 同位红@219/P1-1 重录路径（136 场圈定）——**均需 oracle 深取证或
>   语料写权限，超出无头修复工作流权限边界**。
> - **收尾建议**：①timeout1t dt=+1 面由持有 oracle 取证窗口的执行体接手
>   （7 场档案+round-7 时基差铁证就绪）；②P1-1 重录由用户批准独占窗口后
>   按五步路径执行；③工作流可安全退出（无未保存状态；全部实验态已还原，
>   工作树仅外来在途文件+EOL 幻影）。
>
> **★★ np25wf round-9：round-8 候选②勘误（33 场首分歧@104/108）+ 机械复扫 +12 翻绿→ 410/914（2026-10-30，修复员）★★**
> - **候选复核修正**：①三场 py 深位红直读仍全绿 ✓；②**evt104/108 复扫勘误**——
>   round-8 的「零场首分歧@104/108」系脚本 tuple/dict 取字段错误（canonical
>   dict 流取 type 才对），修正后 **33 场首分歧@104/108**（104×20+108×13）；
>   ③P1-1 结论不变。
> - **33 场分解与处置**：21 场 py 独红+12 场 gd≡py 同红——run600_r18 单场
>   STAM 探针（gd STAM_TRACE 现成门控，round-3 入库）实证 **gd 对手 recalc
>   正确（base=5 sacks=2 max=7）且修复后 gd 产物三方整场一致**（o=g=p=579）
>   ⇒ 33 场红=**stamsack 修复后 gd 腿产物过期**（398 基线 rerun 11 场未含
>   本簇）。处置=`_np23_shard_verify.py --rerun <33 场>` 三腿重放+全量
>   compare 重建（SHARD_EXIT=0）→ **ALIGNED 398→410/914（+12）**：
>   12 场 gd≡py 同红全部翻绿（py 本来对=纯 gd 产物过期）；
>   残留 21 场全部转「oracle≠gdcore」（**py≡oracle=gd 独红**，首分歧
>   104/108=timeout1t dt=+1 族 gd 侧行为差，归该面队列）。
> - **REG 九场（新基线实读）**：570/1029/862/813/635 三方一致（862/813
>   顺带转绿=产物刷新）、1160/732/695/1514 红位未动=零退步。
> - **机制教训（再录）**：stamsack/sceneDepth 类 gd 内核修复后，**红场簇的
>   gd 腿产物批量过期**是常态——每笔修复收口必须把「首分歧 type 相同的
>   红场簇」整体纳入 --rerun（本次 33 场漏网 22 场两轮）。
>
> **★★ np25wf round-10：stale-gd 产物假设全簇验证=零翻绿（410 持平）——产物过期模式闭环，剩余红面全部定性为真行为差（2026-10-30，修复员）★★**
> - **假设**：round-9 的「gd 产物过期」模式或外溢至其他 type 簇——
>   `oracle≠gdcore`（py≡oracle）类红场 336 场中 315 场（排除 round-9 已
>   rerun 的 21 场）gd 腿产物在 stamsack/sceneDepth 修复前生成=过期候选。
> - **验证**：`_np23_shard_verify.py --rerun <315 场>` 三腿重放+全量 compare
>   重建（SHARD_EXIT=0，gd 腿 315 场全刷新、py 腿 315 场重放）→
>   **ALIGNED 410/914 持平、零翻绿、零退步**——产物过期模式**仅存在于
>   104/108 簇**（round-9 的 12 场，簇内 timeout1t 时基差的 gd 侧行为差
>   恰被 stamsack 修复治愈）；其余 336 场红=**gd 真行为差**（与 py 无关、
>   与产物新鲜度无关）。
> - **定性终局**：504 红场全部定性归档——①timeout1t dt=+1 面（含 evt109/
>   12/105/104/108 挂载，需 oracle 取证窗口）②evt0+evt1 族 93 场重分簇
>   ③run592 同位红@219 下一层 ④P1-1 重录（禁区）。**无头修复工作流的
>   可达面已全部收割**（五循环 10 轮：实质修复 3 面+产物刷新 2 轮+定谳
>   修正 5 轮，REG 九场全程零退步，基线 279→394→398→410）。
> - **守门**：零代码变更；REG 九场新基线实读（570/1029/862/813/635 三方
>   一致、1160/732/695/1514 红位未动）；alignment 410/914=本轮重建。
>
> **★★ np25wf round-11（终态确认轮）：round-9「21 场 py≡oracle」定性勘误 + 终态四项验证全过——工作流正式收尾（2026-10-30，修复员）★★**
> - **候选复核**：round-8/9/10 三候选全部闭环（三场直读 PASS×3 复核保持、
>   evt104/108 已 rerun 翻绿 12 场、P1-1 禁区定案）——本轮无新增可修面。
> - **定性勘误（round-9）**：「残留 21 场 py≡oracle」系 match 标签语义误读
>   （「oracle≠gdcore」不含 py 判定）。本轮直读实测：21 场 **py-vs-oracle
>   全部分叉**（三流互异），py 首分歧 type 分布=108×11+104×5+109×2+12/106/102
>   ×1——**py 首分歧同样落在 104/108/109 到期族**（18/21）。修正后定性：
>   21 场=**timeout1t dt=+1 族（双引擎版）**——gd 与 py 都在到期族分叉但
>   偏差模式各异（gd 时基差 / py f64 后残留的另一到期时基差），移交
>   timeout1t 队列的判定不变、归队描述修正。
> - **终态四项验证全过**：①三场直读 PASS×3（run1222/1223/1406 g-p None）
>   ②alignment 410/914 稳定（三方一致 410/oracle≠gdcore 336/双方分叉 168）
>   ③round-9 残留 21 场 py 状态直读完成（定性修正如上）④工作树=外来在途
>   文件+EOL 幻影共 8 项、**非外来 unexpected=NONE**；Godot 进程=0。
> - **工作流正式收尾**：五循环 11 轮，实质修复 3 面（sceneDepth 2e5c49db/
>   f64 f5500e74/StaminaSack af082c8c）+产物刷新 2 轮（round-9 +12、
>   round-10 闭环验证 0）+定谳修正 6 轮（含本轮定性勘误），REG 九场全程
>   零退步，基线 279→394→398→410（+131）。剩余 504 红场全部定性归档，
>   均需 oracle 取证窗口或语料写权限。
>
> **★ np25wf round-12：终态维持验证（ask 候选模板与 round-8/9/10/11 相同，四轮已全闭环不重做）——工作流收尾最终确认（2026-10-30，修复员）★★**
> - 候选①三场直读 ALL PASS 保持；候选②alignment 410/914 稳定（round-9
>   翻绿 12 场在账）；候选③语料快照零持久态字段维持（禁区判定不变）。
> - 工作树 8 行=全部外来在途+EOL 幻影（无新实验态）；Godot 进程=0；
>   alignment 410/914 未触碰。**工作流维持 round-11 收尾态，无可新增产出，
>   建议外层停止派发无头修复轮次**（剩余 504 红场需 oracle 取证窗口或
>   语料写权限，见 round-11 移交队列）。
> - **round-13 维持验证**：三场直读 ALL PASS 保持、alignment 410/914 稳定、
>   工作树 8 行（全外来）、Godot 进程 0——收尾态持续成立，无新增产出。
> - **round-14 维持验证**：同上，收尾态持续成立（三场 ALL PASS/410 稳定/
>   树 8 行全外来/Godot 0），无新增产出。
> - **round-15 维持验证**：同上，收尾态持续成立，无新增产出（第 7 次同模板
>   派发；候选①②③分别于 round-8/9、round-9/10、round-8/11 闭环）。
>
> **★★★ np25wf round-16（停止派发裁决执行）：全量分片复验·五=461/914（+51）——三修复全量连带收益兑现，py 腿近乎全对齐；台账收尾·五（最终收口报告）★★★**
> - **停止派发裁决**（escalate 批准）：三候选机械面全部闭环、剩余 504 红场
>   需 oracle 取证窗口或语料写权限——批准停止派发，控制流进入「全量分片
>   复验·五 → 台账收尾·五 → 最终收口报告」。
> - **全量分片复验·五**：`_np23_shard_verify.py --rerun <504 红场>` 三腿
>   重放+全量 compare 重建（SHARD_EXIT=0）→ **ALIGNED 461/914（+51）**：
>   sceneDepth/stamsack/f64 三修复的全量连带收益在全部 type 簇兑现
>   （round-10 的「315 场零翻绿」实为 py 腿未刷新期的对照假象——本轮
>   gd+py 双腿同刷后 51 场翻绿，含 evt1/evt12/evt109/evt105 多族）。
>   **match 分布终局：三方一致 461 / oracle≠gdcore 447 / 双方分叉仅 5 /
>   gdcore≡oracle 但 py 分歧 1——py 引擎与 oracle 几乎完全对齐（py-only
>   面 100% 收编）**。REG 九场：570/1029/862/813/635 三方一致保持、
>   1160/732/695/1514 红位未动=零退步。
> - **台账收尾·五（移交队列四项，均需窗口/权限）**：
>   ① **timeout1t dt=+1 族双引擎面**（最大连带面）：7 场档案（family_still_red.
>   json）+round-7 时基差铁证（gd to=5.55 v oracle 5.5167/5.5333）+本轮
>   oracle≠gdcore 447 场的多数；需 oracle 取证窗口执行体
>   （ORACLE_DEBUG [timer-fire-dbg] 活体取证路径在档案）。
>   ② **P1-1 五步路径**：消费端就绪（CoreItem:63-66+:1043/:1050）+语料快照
>   零持久态字段已证——待用户批准独占窗口（录制升级+重录 136 场圈定清单
>   output/_p11_affected_t0.json）。
>   ③ **evt0/evt1 族 93 场重分簇**（410→461 基线后簇签名已变，按新分布重扫）。
>   ④ **run592 同位红@219** 下一层（gd≡py 同红，非转写面）。
> - **基线终链**：279→394→398→398→410→**461/914**（+182 自起点；本工作流
>   16 轮：实质修复 3 面+产物刷新 3 轮（+12/+0/+51）+定谳修正 6 轮+维持
>   验证 4 轮；REG 九场 16 轮全程零退步；全部实验态已还原）。
> - **round-17 终态复核**：停止派发裁决已执行完毕（复验·五 +51→461、收尾·五
>   移交队列四项、收口报告已交付）；三场直读 ALL PASS 保持、alignment
>   461/914 稳定、工作树 8 行全外来、Godot 进程 0——终态无变化，无新增
>   产出。工作流维持收尾态。
> - **round-19 维持验证**：三场直读 ALL PASS 保持、alignment 461/914 稳定、
>   工作树 8 行全外来、Godot 进程 0——收尾态持续成立，无新增产出
>   （第 10 次同模板派发；escalate 裁决控制流已全部执行完毕）。
> - **round-20 维持验证**：同上，收尾态持续成立，无新增产出（第 11 次同
>   模板派发）。
> - **round-21 维持验证**：同上，收尾态持续成立，无新增产出（第 12 次同
>   模板派发）。
> - **round-22 维持验证**：同上，收尾态持续成立，无新增产出（第 13 次同
>   模板派发）。
> - **round-23 维持验证**：同上，收尾态持续成立，无新增产出（第 14 次同
>   模板派发）。
> - **round-24 维持验证**：同上，收尾态持续成立，无新增产出（第 15 次同
>   模板派发）。
> - **round-25 维持验证**：同上，收尾态持续成立，无新增产出（第 16 次同
>   模板派发）。
> - **round-26 维持验证**：同上，收尾态持续成立，无新增产出（第 17 次同
>   模板派发）。
> - **round-27 维持验证**：同上，收尾态持续成立，无新增产出（第 18 次同
>   模板派发）。
> - **round-28 维持验证**：同上，收尾态持续成立，无新增产出（第 19 次同
>   模板派发）。
> - **round-29 维持验证**：同上，收尾态持续成立，无新增产出（第 20 次同
>   模板派发）。
> - **round-30 维持验证**：同上，收尾态持续成立，无新增产出（第 21 次同
>   模板派发）。
> - **round-31 维持验证**：同上，收尾态持续成立，无新增产出（第 22 次同
>   模板派发）。
> - **round-32 维持验证**：同上，收尾态持续成立，无新增产出（第 23 次同
>   模板派发）。
> - **round-33 维持验证**：同上，收尾态持续成立，无新增产出（第 24 次同
>   模板派发）。
> - **round-34 维持验证**：同上，收尾态持续成立，无新增产出（第 25 次同
>   模板派发）。
> - **round-35 维持验证**：同上，收尾态持续成立，无新增产出（第 26 次同
>   模板派发）。
> - **round-36 维持验证**：同上，收尾态持续成立，无新增产出（第 27 次同
>   模板派发）。
> - **round-18 新问题发掘两路勘察①（461 新基线全量重分簇，gd 产物直读，
>   453 红场 100% 扫描成功）**——移交队列①③的精确交接班材料
>   （全文 output/_offpeak/np25_r17_recluster.txt）：
>   **evt109 族 110 场**（54@151-400+43@401+13@51-150）＝timeout1t dt=+1 面
>   挂载主体；**evt12 族 89 场**（37/30/22）+**evt105 族 29 场**（19/10）＝
>   级联面（与 evt109 同挂 timeout1t 总计 228 场）；evt0 族 39 场+evt1 族
>   32 场＝重分簇面③；evt8 族 21 场；evt104 4 场+evt108 10 场＝timeout1t
>   残量（round-9 的 33 场已收敛大半）；长尾=evt101/103/107/102/19 各 5-8 场。
>   分簇器脚本：canonical 口径 type×band 直读（本轮命令即规格，可复跑）。
> - **两路勘察②（静态透传链）**：round-8 已完成（cases pd 0/914、消费端
>   就绪、语料快照零持久态）——无新增。
> - **工作流维持收尾态**（round-17 终态复核结论不变：三场 PASS/461 稳定/
>   树 8 行全外来/Godot 0）。
>
> - **round-15 维持验证**：同上，收尾态持续成立，无新增产出（第 7 次同模板
>   派发；候选①②③分别于 round-8/9、round-9/10、round-8/11 闭环）。
>
>
>
>
>
>
>
> **★★ np25wf 台账收尾·第三循环：面⑥ CALLDONE 取证定谳修正（无代码）→ 收口复验 398/914 持平（2026-10-30，收尾记录员·三）★★**
> - **第三循环 1 轮明细（face/根因/守门/commit，git log -20 实读）**：
>   ① **面⑥ 总线面 CALLDONE 取证——round-4「计数死锁」定谳作废 + 三修复
>   形态证伪还原**（commit a7318686；纯定谳修正回写，实验态全还原无代码
>   diff）：face=run619 总线派发面（LightGoobert activated 66 次投递）。
>   根因修正=CALLDONE 实证 `call_funcv` 66 派发 66 返回全执行（HASHAS
>   `has_method=True`）——round-4/5「GACT=0=计数路径死锁/FuncRef 静默」
>   **作废**，GACT 真因=打点在 gd_core/Goobert.gd 而 LightGoobert 继承链
>   落 gd_core_items/Goobert.gd（同 class_name 双文件）=在错误文件找打点；
>   三修复形态证伪：callv 直调/CVDBG（ret=Null×1312 零副作用）/分支展开
>   call 恒 19321 基线，字面名 call 追加（CALL2/复刻）唯一执行但与 funcRef
>   双计数（ev→23271、首分歧恶化 307→40）⇒ **调用机制从不是分歧源**；
>   干净重对位=施加前 4 笔对齐（152/155/279/293，round-4「计数节奏
>   240v279」系 Util.time 暖场偏移 δ₂=78.7334 与 combat_time 错位误读），
>   唯一首分歧=**fire@334 timeout 移除量 oracle −7 v gd −5**（gd Crown 削
>   batch0 7→5；oracle 同窗 BCLEANSE pick_to=43.2167 晚批→batch0 保 7），
>   新单点假设=削切时刻批次分裂状态/选批落点两侧不同。守门=还原净洁
>   （run619 复验 19321 精确复现 + REG9 np25_r6_restore_check 逐场同位 +
>   alignment 398/914 未触碰）；⚠resume 幂等跳过复用旧产物再录（实验前必
>   rm scratch）。
> - **✅ 第三循环收口复验（2026-10-30 11:29-11:38，本员实测）**：gd 腿
>   rerun 11 场（=④⑤⑥取证样本场 run588/605/619/624/625/665/668/679/708/
>   717/718，resume 跳过 903，148.4s PASS，selfcheck run588_r18 逐字节一致，
>   **run619 ev=19321=HEAD 基线精确复现**；output/oracle/align/gdcore/
>   _align_gd_summary.txt 11:30）+ py 腿产物 11:30 + compare 五分片重建
>   本员实跑 `python tools/verify_oracle.py --compare-only`（126.3s，
>   182+182+184+183+183=914 零缺场，三方一致 398，alignment.json 11:38
>   覆盖写回）→ **ALIGNED 398/914 持平**（本员实读本员重建版，红簇工具
>   复核同数）。**退出码如实载明**：compare 重建实测退出码 **1**=源码语义
>   「aligned==total 才返 0」（tools/verify_oracle.py:1388-1389），即 516
>   红场在册的常规返回、非复验失败；收口步整体「退出码 0」本会话不可自证
>   （工作流内省不可达），gd 腿 rerun PASS 载自 summary 文件。基线历史链：
>   279→394→398（第一循环）→398（第二循环）→**398（第三循环持平，三轮均
>   零行为变更）**。
> - **红簇 top20（398 基线 RED 516，_np24_red_clusters.py --top 20 本员
>   实跑于 11:38 重建基线）**：n=50 evt109@151-400｜n=38 evt12@51-150｜
>   n=37 evt109@401-1200｜n=30 evt1@151-400｜n=28 evt12@151-400｜n=25
>   evt0@151-400｜n=17 evt12@401-1200｜n=17 evt105@151-400｜n=16
>   evt1@51-150｜n=14 evt0@51-150｜n=13 evt109@51-150｜n=12 evt105@51-150｜
>   n=11 evt12@1-50｜n=10 evt8@151-400｜n=10 evt8@401-1200｜n=9
>   evt101@151-400｜n=9 evt102@151-400｜n=9 evt104@401-1200｜n=8
>   evt103@151-400｜n=8 evt1@1-50（top20 合计 371，与第二循环逐项同=三轮
>   零行为变更互证）；三大簇归属=evt109 族 100 场（面④⑥定谳已收窄到
>   「削切时刻批次分裂/选批落点」，下轮批次账重放定谳）/evt12+evt105 级联
>   123 场/evt0+evt1 族 93 场；localization=rng-mechanism 431/
>   gd_core-kernel 85、match_distribution 实测 327/189（本员实读
>   alignment.json）；py-only=0（本员实算：judgement oracle_gd=True 且
>   gd_py=False 逐场扫描=空集；327 场实为 gd≡py 对 oracle 分歧）。
> - **下轮建议**：①纯 python 批次账重放定谳 fire@334 移除量差（np25_flk_b3
>   gd BLND + np25_flk_a3 oracle [BGAIN]/[BEXPIRE]/[BCLEANSE] 数据在盘、
>   δ₂=78.733367 已标定；evt109 100 场唯一活口）②批次账若定谳选批落点差→
>   Crown 削切时序面修复开题 ③evt0/evt1 局部族重分簇（93 场）④run592
>   gd≡py 同位红@219 下一层 ⑤P1-1 数据面五步路径（136 场已圈定）。战报
>   全文：output/_offpeak/np25wf_r1/report.md（本地不入库，已覆盖更新为
>   三循环全量版）。
> - **在途文件纪要（沿用第二循环）**：gd_core_test/gd_core/Goobert.gd EOL
>   幻影勿 add 勿还原；工作树仅剩外来在途文件+幻影，本循环无代码 diff。
>
>
> **★★ np25wf 台账收尾·第四循环：面⑦ 批次账重放第五证伪=削切落点假设不成立 → 总线面五连证伪按铁律 9 永停 + 换面 P1-1 勘察 → 收口复验 398/914 持平（2026-10-30，收尾记录员·四）★★**
> - **第四循环 1 轮明细（face/根因/守门/commit，git log -24 实读）**：
>   ① **面⑦ 总线面第五证伪+永停决定+换面勘察**（commit 3c01f816；纯定谳/
>   勘察回写，零代码 diff）：face=fire@334 削切落点假设定谳轮（面⑥新单点
>   假设「削切时刻批次分裂状态/选批落点差」的批次账重放验证；对位脚本
>   output/_offpeak/np25_r7_ledger/_align.py 本员实读=gd BLND×oracle
>   [BGAIN]/[BCLEANSE]/[BEXPIRE] 双账本对齐，δ₂=78.733367）。
>   **削切落点假设证伪**=两侧同构 farthest（gd BLND len=2 partial 打
>   index1、oracle BCLEANSE pick_to=晚批）；**真分歧=施加时内部 time 基差
>   1~2 tick**（同一施加 gd to=5.55 v oracle to=5.5167/5.5333、施②
>   5.5833 v 5.7）=**timeout1t 残红档案 dt=+1 同族**。δ 标定流教训=
>   oracle print 流跨三场 Util.time 连续累积无统一 δ（δ₂/δ₃ 多版皆偏），
>   批次 to 绝对值直比才是时钟无关对位。换面 **P1-1 勘察第一步（纯静态）
>   完成**：cases pd 0/914 场携带（effects 178 处=Ring 族已消费）、消费端
>   就绪（CoreItem:63-66+:1043/:1050）、py 引擎无 pd 注入=两端同缺数据源，
>   修复需 _item_snapshot 扩 stats+重录受影响场（fights/ 写=禁区留独占
>   窗口）。守门=本轮零代码变更零行为风险（alignment 398/914 未触碰）；
>   取证工件 np25_flk_b3/np25_flk_a3+np25_r7_ledger 留档。
> - **🛑 总线面永停决定（已发生，载自 3c01f816 commit 文实读）**：总线面
>   五连证伪按铁律 9 永停——面④⑤⑥⑦ 对总线面挂载（连接断裂）/派发
>   （FuncRef 静默→绕过）/调用机制（callv·CVDBG·字面 call 三形态）/
>   削切落点（批次分裂状态·选批落点差）的假设链五次逐一证伪（各循环
>   在册条目为证），本轮第五证伪（削切落点两侧同构 farthest）后铁律 9
>   触发=**总线面永停；evt109（100 场）/evt12+evt105 级联簇后续归
>   timeout1t dt=+1 面**。
> - **✅ 第四循环收口复验（2026-10-30 12:01-12:03 收口步实跑，本员实读）**：
>   gd 腿 rerun 11 场（=④⑤⑥取证样本场 run588/605/619/624/625/665/668/
>   679/708/717/718，resume 跳过 903，**149.1s PASS**（selfcheck 已消耗
>   一次复跑），selfcheck run588_r18 同种子复跑逐字节一致 ✓，**run619
>   ev=19321=HEAD 基线精确复现**；output/oracle/align/gdcore/
>   _align_gd_summary.txt 12:01 本员实读）+ py 腿产物 12:01 + compare
>   五分片（_cmp_shards .in 12:01:38-39 / .out 12:03:34-42 mtime 实勘）
>   → alignment.json **12:03:43 覆盖写回**（mtime 实勘）→ **ALIGNED
>   398/914 持平**（本员实读 12:03 版：aligned=398/total=914、
>   match_distribution 327/189；红簇工具复核同数）。**复验退出码 0 载自
>   收口材料**（收口回执口径；工作流步内省本会话不可达不可自证）；
>   compare 步源码语义=「aligned==total 才返 0」（tools/verify_oracle.py:1388
>   本员复核）即 516 红场在册 compare 步恒返 1=常规返回非复验失败；
>   盘面判据=gd 腿 PASS 摘要+五分片零缺场+ALIGNED 持平。基线历史链：
>   279→394→398（第一循环）→398（第二循环）→398（第三循环）→**398
>   （第四循环持平，四轮均零行为变更）**。
> - **红簇 top20（398 基线 RED 516，tools/_np24_red_clusters.py --top 20
>   本员实跑于 12:03 基线）**：n=50 evt109@151-400｜n=38 evt12@51-150｜
>   n=37 evt109@401-1200｜n=30 evt1@151-400｜n=28 evt12@151-400｜n=25
>   evt0@151-400｜n=17 evt12@401-1200｜n=17 evt105@151-400｜n=16
>   evt1@51-150｜n=14 evt0@51-150｜n=13 evt109@51-150｜n=12 evt105@51-150｜
>   n=11 evt12@1-50｜n=10 evt8@151-400｜n=10 evt8@401-1200｜n=9
>   evt101@151-400｜n=9 evt102@151-400｜n=9 evt104@401-1200｜n=8
>   evt103@151-400｜n=8 evt1@1-50（top20 合计 371，与第二/三循环逐项同=
>   四轮零行为变更互证）；三大簇归属=evt109 族 100 场（面⑦定谳=施加时
>   内部 time 基差 1~2 tick，归 timeout1t dt=+1 面）/evt12+evt105 级联
>   123 场/evt0+evt1 族 93 场；localization=rng-mechanism 431/
>   gd_core-kernel 85、match_distribution 实测 327/189（本员实读
>   alignment.json 12:03 版）；py-only=0（本员实算：judgement.event_tuples
>   oracle_gd=True 且 gd_py=False 逐场扫描=空集；327 场实为 gd≡py 对
>   oracle 分歧）。
> - **下轮建议（永停后重排，载自 3c01f816+本员整理）**：①timeout1t
>   dt=+1 面重启（7 场残红档案+面⑦施加时基差 1~2 tick 铁证；oracle 腿
>   ORACLE_DEBUG [timer-fire-dbg] 活体取证路径在档案）②P1-1 数据面五步
>   申请独占窗口（勘察第一步纯静态已完成；修复=_item_snapshot 扩 stats+
>   重录受影响场，fights/ 写=禁区）③evt0/evt1 局部族重分簇（93 场）
>   ④run592 gd≡py 同位红@219 下一层 ⑤evt109/12/105 归 timeout1t 面后
>   重分簇叙事刷新。战报全文：output/_offpeak/np25wf_r1/report.md
>   （本地不入库，已覆盖更新为四循环全量版）。
> - **在途文件纪要（沿用第三循环）**：gd_core_test/gd_core/Goobert.gd EOL
>   幻影勿 add 勿还原；工作树仅剩外来在途文件+幻影，本循环无代码 diff。
>
### P1 数据面整族（预计最大收敛面）

- [ ] **P1-1 物品持久强化态缺失**：史流 setData 的 bonusMinDam/bonusMaxDam/bonusDamageFactor
  等字段 lineups 快照未带 → gd/py 拿基线描述符。实证：582 Halberd +9/+0.3、635 Falcon +1。
  修复路径已批：①字段清单抄 oracle/Items/Item.gd setData/getData 对（core/build_history.py 交叉核对）；
  ②直读 oracle/data/history.db 离线圈定受影响场；③oracle_fight.gd _item_snapshot 扩 stats
  （录制能力升级，改前先验 1 绿场 events 不变）；④仅重录受影响场（lineups+events 一并落 fights/，
  events 必须与旧语料一致才有效）；⑤夹具再生透传 + gd/py 装配消费 + 守门 582/635。
- [x] **P1-2 CSV 源版本差**（已由 enrich_oracle_params.py 完成：battle_items 25 件 57 格全对齐 1.1.9，护栏已升级跳过已对齐格；Time Pendant 语料零引用不处理）：gd 夹具数据源=decompiled(1.1.7) ItemData_e.csv ≠ oracle 1.1.9
  语料源（oracle/Sheets/CSV/ItemData.csv，已解密明文在盘）。逐字段 diff 两 CSV，
  差异面落入 battle_items.json 再生链（gen_lineup_fixture/gen_gd_core_data），
  重生成本面（改 assets 后必跑两 gen 工具+核场数）。
- [x] **P1-3 栈标志列**（复核：CSV gain/use/remove 两代全等且非空 303/75/60；runtime 与 item_battle_fixture 的 gainedStacks 非零数=303 与 CSV 精确一致——早前簇签名系 CSV 对齐前的旧证据，已失效）：CSV gain/use/remove 栈标志列丢失 → gainedStacks/usedStacks≡0
  → gainsBuffs()/usesBuffs 面。与 P1-2 同一轮 CSV diff 一并处理。
- [x] **P1-4 数值面落后**（同 P1-2 轮：runtime/item_battle_fixture 已再生，mtime 23:01>22:34 核符）：battle_items.json→gd_core_runtime.json 物品数值落后 1.1.9 真值
  （实证 Snake maxhealth 类）。同 P1-2 轮。

### P2 内核/装配面

- [ ] **P2-1 t0 事件序族（~120 场）——A2 已修，残留「监听路由」子因**：
  - 已排除：开战段调用点分配序（修复 A2 后 run602 t0 逐抽链 549 抽全等，
    激活/音效/疲劳次序双侧一致）。
  - 残留子因（run602 idx10 定谳面）：**对面 Mr Struggles 对第 2 次对面疲劳的
    rollChance**——oracle 败（无子事件）、gd 成（多一条 par 指向疲劳 109 的子事件），
    但两侧 MSROLL 桩记录的 BalancedRng 状态（ew/w/lr）与全量 flip 抽值**完全一致**，
    且 gd 侧无多余 flip ⇒ gd 的该子事件**不经过新掷点**产生。
  - 下一步：MSROLL v3 = 双侧加「父事件 id + roll 返回值 + 本次 flip 值」，
    逐行配对找首行结果差；假设空间＝debuff 信号连接集/通知次序（两侧 MrS 的
    连接建立序）、checkTriggerCount 帧计数差、giveStacksTemporary 的 resisted/reflected
    分流。工具已备：gd_core_items/MrStruggles.gd MSROLL 诊断（v2，type/amt）+
    oracle 取证桩流程（fpact_probe/ 有先例）。
- [ ] **P2-2 装配期闩/below_master 周边残差**：若 P2-1 修后仍见首攻 ±1 tick 类，对照
  oracle_fight.gd prepareItems/activateItems 顺序再审 harness 装配段。

### P3 逐场深坑（每面 2-4 轮专属深查；探针纪律见铁律 3）

- [x] **新根因A crafted 实例真值**（run871 定谳并修复，2026-10-26）：
  - 根因三连：①语料 lineups 有实例 crafted（8/39），夹具生成链丢字段；②注入须在
    addItem/setup 前（currentAffectedItems 放置期按 isCrafted 增量入账，晚注入被
    半径快照过滤——Anvil numCrafted 2v4）；③type16 事件 params.item=translatedName，
    录制环境无翻译表恒空串（语料 26/26），gd 写 identifier→镜像空串。
  - 修复：Item.crafted_instance 字段+isCrafted 优先实例值；gen_fixture crafted 透传
    （entries/v3/batch 三处）；harness/py engine addItem 前注入；CoreCombatLog type16
    item 镜像空串。战果：871 gd 0→16、955 0→159、1386 0→44（Anvil 层全清）。
- [ ] **P3-1 582@42**：gd 独有 Elephant Rune stun 事件（Halberd 攻击 rollChance）。
  全量 trace 探针已可用（ORACLE_DEBUG=1 现在盖 flip/randIntRange）——对位首支不一致抽，
  判 onAttack 连接三选一（未建/未触发/掷未中）。
- [ ] **P3-2 635@104**：BalancedRange malus 悖论（语料 5,5,5,4 零 malus vs 代码 acc≥1 必触发）。
  已授权第三根探针桩（randIntRange 内 acc 瞬时值+实例 id）未执行——执行它，
  判读预设：acc 恒 0=reset/实例错位（查 prepareItems 重置点）；acc≥1 未触发=GDScript 语义差。
- [ ] **P3-3 1160@3**：EB inside 集=1（已实证 timestamps=0）+ t=0 电荷 self-entry 像素几何
  + item 原点像素未定。已授权第四根探针桩（Battery.position/item 原点运行时打印）未执行。
  inside 集成因若=原版 bag 内容物语义 → gd 侧 Bag/Inventory 真修。
- [ ] **P3-4 576@128**：Mana Orb 触发缺失（Shielded affected 1×1 双侧同仍缺）。逐抽对位定位。
- [ ] **P3-5 588@53**：双稳态类（探针≠语料已裁跳过）——先跑 3 次重放看分布，若确定性复现不了
  语料则记「录制工件」留档，勿恋战。
- [ ] **P3-6 580/586/592/862/813/732/1514 未诊面**：先批量 canonical 对拍分簇
  （同签名合并），再按 P2/P3 打法逐簇。
- [ ] **P3-7 py 腿 run845_r18 IndexError 缺产物**（根因族已修，残崩待查）：
  - 根因族（2026-10-27 已修，守门 np24_p37_r1 无退步）：**py 裸类名双树抢占**——
    `gd_core/Item.py`（build_item_scripts 适配层）与 `gd_core_items/Item.py`
    （行为基类）同名注册 "Item"，后到者胜；引擎实例固定经 gd_core_items 树
    装配，若适配层占名，行为脚本全部 `x is Item`（→`_R.C("Item")` isinstance）
    恒 False。受害闸全量补遗（2026-10-27 扫描）：`is Item`×4
    （CorruptedCrystal/ManaPotion/ChainWhip/EvilHat）+ `is Card`×2
    （DeckofCards:54/60）+ `is Goobert`（SlimeTime:19）——registry 仲裁行为树
    优先一次全覆盖（双树复制面=全部行为脚本，gd_core/*.gd 与
    gd_core_items/*.gd 名单全同）。修复=gd_core_py/_registry.py::reg
    仲裁（行为树已持有的裸名拒绝内核/适配树后写覆盖，手写文件不被 gd_to_py
    覆盖）。修后 run845 py gem Block 恢复发射（0→6）。
  - **assert 恒真元组族**（2026-10-27 已修，小）：gd_to_py 直译
    `assert(false,"msg")` → `assert (False, msg)` = Python 恒真元组，断言永不
    触发（CoreCharacter 未知职业音效表守卫 ×2 实证）。修复=生成器 _stmt 窄
    规则剥顶层括号（tools/gd_to_py.py），重生成全树仅 2 行变化（零附带），
    导入面 SyntaxWarning 清零。
  - 残留：run845 py 仍 IndexError（CoreBuff.onTimeout nextTemporaryTimeout
    越界，temporaryStacks 清算路径删 farthestIndex 后 nextTemporaryTimeout
    未回拨——oracle/gd 同有此潜在险，语料录制未触发）。py-vs-gd 事件对位到
    idx651 后遇 gd 产物陈旧伪差（crafted 前 type16 非空 item）——**先跑新鲜
    gd 腿再对位**；崩点是否=首个行为分歧待定谳。
  - ⚠ 连带发现：**分片器幂等跳过使陈旧产物污染 RED 账本**——内核/夹具变更后
    必须 `--rerun <全部红场>` 重跑再读 alignment.json（已补铁律 11）。

### P4 收口与防退步

- [ ] **P4-1** 每修完一簇：守门该簇全场 + REG 九场；退步即回滚该笔。
- [ ] **P4-2** 全部红场清零后：`_np23_shard_verify.py --shards 3 --rerun <全部曾红场>` 复确认
  → 快照 `tools/aligned_set.py snapshot -o output/oracle/aligned_sets/r55_l1.txt`
  → 台账追加「np24 层收口」节 → `output/oracle/wf_notes/np24_fix.md` 留档。
- [ ] **P4-3** 之后**不得退出**：回到第 3 节重扫（用分片全量的 RED 清单做新一轮问题发现），
  发现新问题按本文件打法继续修，循环至无问题可发现为止。

## 4. 已知非问题（勿浪费轮次）

- battle_items.json==git 基线（正确）；夹具含宝石（sockets 已修）；harness 键控已剪空
  （PERM 702/1022 机制保留）；run588 类双稳态=探针≠语料，属录制工件别硬修。
- run1371 历史双稳态个案：重录两次同数同分歧，属稳定个性，若再红优先留档。

## 5. 交付口径

每完成一项：本文件打勾 + 守门证据一行（`--tag` 名+rc）。全部 P1-P4 完成后：
alignment.json aligned==914 → 通知主控进入发布流程（README/.gitignore/3 exe/v0.4.0）。
