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
> ★ **头号目标 P2-0（新，2026-10-27 分簇定谳）：长度簇 461 场**——
> firstDivergence.kind=length，即**事件前缀全等、仅战斗总长/尾部不同**。
> 细分（关系签名）：G>O_P<G win同 97 / G<O_P<G win同 82 / G>O_P<G win翻转 75 /
> G<O_P>G win同 62 / G<O_P<G win翻转 49 / G<O_P>G win翻转 45 / G>O_P>G 51 /
> 其余零头。**铁线索**：其中 199 场 win 翻转——前缀逐事件全等但 winner() 不同
> ⇒ **判胜与事件流脱钩**（血量账本不可见面/同时死亡判定/fight_ended 语义）。
> 打法：各取 2 场样本（win同 G≠O 一场、win翻转一场），ORACLE_ALIGN_TRACE 尾段
> 逐抽对位 + 血量轨迹对拍，定位判胜时刻差。修掉此簇 = 一次性收敛 ~461 场。
> 次大簇：evt0@1-50 ×55、evt1@1-50 ×43（t0 族残余，接 P2-1 打法）、
> evt1@51-150 ×28、evt12 ×26、evt8@151-400 ×26（按簇成员逐簇）。

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
