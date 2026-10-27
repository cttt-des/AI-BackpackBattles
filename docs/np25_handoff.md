# np24→np25 交接文档（会话续接参考）

> 生成：2026-10-27 晚。交接时基线 **125/914**（alignment.json 实读，RED 789）。
> 本文是新会话接续修复工作的参考；**运行时状态以实读为准，勿信记忆**。
> 唯一任务书/问题台账：`docs/np24_issue_ledger.md`（铁律 1-12 + 工具速查 + P1-P4 清单）。

---

## 1. 一句话现状

三方对齐工程（语料↔gd_core↔gd_core_py），唯一出口 alignment.json 914/914 全绿。
np24 轮已完成 6 笔修复入库（A/A2/C/D/E/F），基线从 60→125。当前头号根因已定谳：
**P3-3 电荷像素几何族**（预计连带 evt1×125 大簇）。排队中的 offpeak 任务
（offpeak-bedee8e2）读台账即接续；本会话若有指令则直接开修。

## 2. np24 轮已完成（勿重做，细节在台账§2）

| 修复 | commit | 一句话 |
|---|---|---|
| 根因A crafted 实例真值链 | c1655431 | Item.crafted_instance+夹具透传+两侧 addItem 前注入+type16 item="" 镜像；871/955/1386 Anvil 层清 |
| 根因A2 grid 真值面 | defdd5f7 | extract_grid 重指 oracle/1.1.9+基座 2×2 继承+affected 旧值；三产物重生 |
| 根因C py 裸类名双树抢占 | 82f17ddf | registry.reg 仲裁行为树优先；is Item/Card/Goobert 闸族修复（CorruptedCrystal/ManaPotion/ChainWhip/EvilHat/DeckofCards/SlimeTime） |
| 修复D 事件闸表+assert族+isX补遗 | 4ab2084c | 抬闸面补全 20 场（>25000 语料全集）；assert(false,msg) 恒真元组族 |
| 修复E 诚实基线+分簇工具 | d727b9b8 | 全 914 场 --rerun；真基线 69；`tools/_np24_red_clusters.py`（本地 tools） |
| 修复F runtime 漏重生 | be23196d | gd_core_runtime.json 是 py 引擎几何源，A2 后漏跑 gen_gd_core_data → py-only 60 场假红全灭 |

## 3. 头号待办（按序，全部有定谳面）

### P3-3 电荷像素几何族（头号，预计连带 evt1×125 + evt1@51-150×73）

- **定谳铁证**（run572_r9 TRIG 双侧桩，probe≡语料逐字节验证）：
  开战冷却抖动块逐值全等、cd 全等（Death Scythe 1.408125 精确同），
  唯 speed 差：DS oracle 1.2 v gd 1.1。Fanny Pack +10% 两侧同得；
  缺的是 **Battery 电荷路径 +10%**（Cauldron 双侧 1.3 = 电荷大体在走，漏过 DS 所在格）。
- **机制**：Battery/CogBadge 的 `sendCharge(dur, chargeCells, speedFactor, event)`
  沿像素格行走（chargeCells=本地格常量，经 getGlobalPointsForCells 节点旋转变换
  映射进背包），途经物品 `onChargeEnteredCell → addSpeed(value)`。
  gd 漏过 DS 所在格 ⇒ 物品原点像素/Battery.position 语义差（台账 P3-3 的
  已授权探针：打印 Battery.position/item 原点运行时值）。
- **正解路径**：执行 P3-3 探针 → 修 gd_core/CoreItem 电荷-像素映射 →
  gd_to_py+test 同步 → 守门 run572/616/622/623 + REG 九场。
- 样本场：run572_r9（player DS 在 FP(3,1) 包内）、run616_r18、run622_r15、run623_r6。

### evt0@1-50 ×101（次大）

- 样本 run618_r18 idx46：Miss Fortune 连续双激活（oracle）v 单激活+Amulet of
  Darkness 抢跑（gd）。run618 无 SpeakwithAnimals/BowlofTreats（doubleActivation
  授予者零在场）⇒ 与双激活无关，是**冷却亚 tick 边界到期序**（P2-2 深端）。
- 打法：run618 双探针（trace 已备）逐抽对位 idx46 前后，看两侧 Ms/Amulet 的
  triggerTime 到期顺序差。

### evt8@151-400 ×48、evt107@1-50 ×44、evt12@51-150 ×25、evt105@51-150 ×24 …

逐簇按 P2/P3 打法；`tools/_np24_red_clusters.py --top 14` 随时出新分簇。

### 其余遗留（台账有详情）

- run845_r18 py 残崩（IndexError CoreBuff.onTimeout；根因C 已修 gem Block 面，
  崩点独立；**先跑新鲜 gd 腿对位**）
- P3-2（635 BalancedRange acc 探针，已授权未执行）
- P1-1 物品持久强化态（五步路径在台账：字段清单→db 圈定→_item_snapshot 扩→
  重录→夹具再生+消费）
- P2-1 MrS 监听路由（MSROLL v3 双侧=父事件id+roll结果+flip值）
- evt12@51-150 ×25（Goobert 治愈面剩余）

## 4. 关键教训（本轮实证，勿重蹈）

1. **铁律 11**：分片器幂等跳过旧产物——任何内核/夹具/引擎变更后，全量必须
   `--rerun <全部红场>`（或受影响簇），否则陈旧产物污染账本。
2. **铁律 12**：改 battle_items.json 后再生链**三产物一个不能漏**：
   `gen_lineup_fixture.py` + `gen_fixture_from_lineup.py --oracle` +
   `gen_gd_core_data.py`（py 引擎几何源 gd_core_runtime.json）。
3. **oracle 取证桩必须 6 元素行**：5 元素炸 oracle_fight.gd:819 dump 循环，
   rng_log 恒 0 字节（TOADSND 实证）。
4. **oracle 探针先验 ≡ 语料**（events 逐字节）才可采信其 rng_log。
5. **firstDivergence 有两种形状**：平铺（一对分歧，含 pair 键）与嵌套
   `{oracle_vs_gdcore:{…},gdcore_vs_py:{…}}`（两对都分歧）。解析必须
   兼容嵌套（`_np24_red_clusters.py` 已修）。
6. **tick_states 起点即异**（各自相位），直接 diff 不可用，需校准后对位。
7. **git add 用明确路径**，勿 `-A`（根目录可能有用户临时脚本）。

## 5. 工具速查（本地 tools/_*.py，按约定不入库 git）

| 用途 | 命令 |
|---|---|
| 守门 | `python -X utf8 tools/_np21_gate.py --cases <cid,...> --tag <新标签>` |
| 全量分片 | `python -X utf8 tools/_np23_shard_verify.py --shards 3 --rerun <cid,...>`（全量 ~30-60 分钟） |
| RED 分簇 | `python -X utf8 tools/_np24_red_clusters.py --top 14` |
| gd 逐抽 trace | env `ORACLE_ALIGN_OUT=<scratch> ORACLE_ALIGN_CASES=<cid> ORACLE_ALIGN_CHUNK=0 ORACLE_ALIGN_SELFCHECK=0 ORACLE_ALIGN_TRACE=1 [ORACLE_ALIGN_STACKTRACE=1]` + Godot（gd_core_test） |
| oracle 探针 | env `ORACLE_FIGHTS_ROOT=<scratch> ORACLE_ONLY_CASES=<cid> ORACLE_DEBUG=1 ORACLE_FIGHT_CHUNK=0 [ORACLE_STACKTRACE=1]` + Godot（oracle 工程） |
| 诊断行（gd 侧已入库） | `CoreRng.trace_diag(kind,a,b,c)`：ANIM/SRC/LABEL/SRC gain_label/MSROLL/TRIG，双门控（ORACLE_ALIGN_TRACE+STACKTRACE）零耗链；改 gd 后必跑 gd_to_py+cp 同步 |

## 6. 事故红线（重申）

- 工作区 `D:\文件资料\学习\自动背包AI` 外零操作。
- `output/oracle/fights/` 语料与 `oracle/` 树只读；取证桩流程：备份→门控≤10行→
  探针→**逐字节还原→md5 留档**（先例 `output/_round_patches/np24_fix/fpact_probe/`）。
- 备份到 `output/_round_patches/np24_fix/`；已绿场不许退步。
- 同一假设两连证伪即停（盲修禁制）。
- GDScript 运行时错误沙箱下挂死引擎：改 gd 先拿小场（run602/run618/run572）验证。
- Godot 一律 `--headless --audio-driver Dummy` + APPDATA 按 PID 隔离。

## 7. 环境快照（交接时验证过）

- alignment.json：125/914；工作树干净（0 脏文件）；oracle 四份主桩 md5 已验还原：
  Item.gd=605a8958…、FannyPack.gd=8cc44a46…、MrStruggles.gd=45e70334…、Toad.gd=f5377fb0…
- 备份链齐全：`output/_round_patches/np24_fix/`（A2/A/F 各 pre_*.bak+fpact_probe/）
- 神谕探针基准：单场 ~25s；全量分片 3 路 ~30-60 分钟（事件闸表扩到 20 场后变长）
- 退出条件（offpeak 任务书）：不允许主动退出；P1-P4 全清且 914/914 后做 P4-2 收口
  （r55 快照+台账收口节+np24_fix.md 留档），再按 P4-3 重扫循环；914/914 时输出中
  明确声明供主控进入发布流程（README/.gitignore/3 exe/v0.4.0 由主控执行）。
