# np24 问题总账与修复指导（offpeak 任务书）

> 生成：2026-10-26。基线 **71/914**（alignment.json 实读，843 红）。
> 本文是 offpeak 修复任务的唯一指导文件：问题清单、根因线索、修复口径、纪律。
> 每完成一项在「状态」列打勾并写明守门证据；**全部完成前不得退出任务**；
> 全部完成后继续自查新问题并修复，同样不许主动退出。

---

## 0. 环境与铁律（每次动手前重读）

1. 工作区 `D:\文件资料\学习\自动背包AI`；**工作区外零操作**（用户铁令）。
2. Godot 一律 `--headless --audio-driver Dummy` + **APPDATA 按 PID 隔离**
   （跑 Godot 的 python 侧已由 `tools/verify_oracle.py::run_godot` 内置；
   手动跑 Godot 时用 `APPDATA="…\output\_recovery\appdata_p\<pid>"`）。
   并行 Godot 共享 user:// 日志目录会弹 openmem err=5 风暴——已根治勿回退。
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
> py trace 通道垫片（e0dc73ed）；run874 冷却链排除+信号级锁定（73e4593f）。
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
> **★ 新发现的问题批次（2026-10-29，np25 主会话寻 新问题轮）**：
> - **新A：oracle 探针 rng_log 只覆盖战斗中段窗口**——run572_r9 探针
>   （events≡语料逐字节 ✓）的 rng_log 仅 1544 行、t=30.0→44.0s，而战斗
>   更长且分歧点在 6.27s——窗口外分叉无法逐抽对位。根因疑似 harness 的
>   first-pass/resume 快照机制只留了 resume 窗口的 trace（rng_log_first.txt
>   分档线索 oracle_fight.gd:1086-1091）。**修法方向**：给探针加
>   ORACLE_FULL_TRACE 开关（首跑即开 trace、禁用覆盖式分档），或查清
>   resume 窗口的起点约定。
> - **新B：run572_r9 ev@109 = Strong Divine Potion giveRandomBuffs 选型分叉**
>   （oracle 首爆 Vampirism+1 vs gd Lucky+2；爆发构成 oracle
>   [103:+1,101:+2,106:+1]）——候选列表两侧全同（getBuffs=range(101,108)），
>   是 pick 值分叉，被新A阻挡逐抽定位；新A修后即可并簇 evt1。
> - **新C：run845_r18 py IndexError 重测被阻**——gd 产物正被全量重建，
>   全量落地后第一件事重测（全局流修复可能已顺带改变其状态）。
> - **待验证**：全局流修复的全量分片复验运行中（预期 ≥148/914，即
>   +5 场 py-only 翻绿）；落地后按新簇签名重扫。

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
