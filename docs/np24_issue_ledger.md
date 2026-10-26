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

## 1. 工具速查

| 用途 | 命令 |
|---|---|
| 守门（gd+py 双腿，分钟级） | `python -X utf8 tools/_np21_gate.py --cases <c,...> --tag <新>` |
| 定向 gd 逐抽 | `ORACLE_ALIGN_OUT=<abs scratch> ORACLE_ALIGN_CASES=<cid> ORACLE_ALIGN_CHUNK=0 ORACLE_ALIGN_SELFCHECK=0 ORACLE_ALIGN_TRACE=1` + Godot（见铁律 2）→ `<scratch>/<cid>/rng_trace.txt` |
| 逐抽对位 | `python -X utf8 tools/_probe_draw_diff.py <语料rng_log> <gd rng_trace> [N]` |
| canonical 对拍 | `sys.path.insert(0,'tools'); import verify_oracle as V; V.first_divergence(...)` |
| 神谕探针（带逐抽） | `ORACLE_FIGHTS_ROOT=<abs> ORACLE_ONLY_CASES=<cid> ORACLE_DEBUG=1 ORACLE_FIGHT_CHUNK=0` + Godot（oracle 工程）；**先验探针 events≡语料才采信其 rng_log** |
| 全量分片 | `python -X utf8 tools/_np23_shard_verify.py --shards 3 [--rerun <红场>]` |
| 神谕重录（如需） | 抬闸版参数在 `output/_recovery/oracle_fight_lifted.gd`（事件闸 200000/墙钟 1200s）；单场单进程 |

## 2. 已修复（勿重做，防回退）

- 宝石槽=实例真相（harness 按 len(entry.gems) 装配）
- below_master=true 终谳（harness+py 三处）
- defer 镜像 / ANIM 裸抽 / MagicRing.setCraftedEffects / EB 接力死亡镜像（6 笔，commit 4315c580）
- oracle trace 完整化（Util.flip/BalancedRange.randIntRange 入 ORACLE_DEBUG trace 面）+ stats 快照通道（录制能力，已入库）
- 工具链：symlink 根治/类注册表/label_rng_enabled/APPDATA PID 隔离/三路分片器

## 3. 问题清单（按优先序；「线索」=已实证的定位面）

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

- [ ] **P2-1 开战段调用点分配序**：rng_state 注入后、首事件前，同一 u 抽链被三腿以不同顺序消费
  （冷却抖动(0.95,1.05)↔动画(0.9,1.1)↔标签盒(-10,10) 互换位）。打法：绿场（570/574/1029）
  与红场各取一场，ORACLE_ALIGN_TRACE 逐抽对位首 20 抽，按「区间签名」定位互换对，
  修 gd 装配调用序（gd_core/CoreCombat.gd startBattle 段）。
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
