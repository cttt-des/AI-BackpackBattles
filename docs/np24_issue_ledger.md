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
7. 全量验证用分片器（**勿用 verify_oracle --force**，其 gd 腿单进程慢且占锁）：
   `python -X utf8 tools/_np23_shard_verify.py --shards 3 [--rerun <cid,...>]`（约 16 分钟）。
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
| 全量分片 | `python -X utf8 tools/_np23_shard_verify.py --shards 3 [--rerun <红场>]` |
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
