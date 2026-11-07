# 扩大语料（异阵容）执行手册

> 依据：`docs/扩大用例对齐规划.md` §4–§5。本文记录**本轮扩样的实际落地口径**：
> 数据来源、合并规则、选样算法、跑批方式、产物位置与验收判据。
> 生成：2026-11-07｜状态：**已完成**——1,194 场（首批 1,168 + 稀有补样 26），验收 PASS。

---

## 一、本轮口径（与 914 场基线的差别）

| 项 | 914 场基线 | 本轮扩样 |
|---|---|---|
| 对手 | **镜像**（同 run 同回合，`opp_* = 本场`） | **全部异阵容**：跨 run 配对，双方物品多重集必须不同 |
| 回合 | 每 run 只取最后一回合 | 全库逐回合（1–18 回合全阶段） |
| 数据源 | 单个 `oracle/data/history.db` | `history/` 下 7 个库合并（runID 加偏移） |
| 产物根 | `output/oracle/fights/` | `output/oracle/expand/fights/`（独立 root，**不改基线**） |
| 版本 | 1.1.4–1.1.9 | 玩家侧 1.1.5–1.1.9 为主（60/90/140/260/520），1.1.4 单列 100 场 |

**为什么独立 root**：规划 §8「扩样用例落独立 root，不改 `fights/`、不改 914 场口径」——
`verify_oracle.py` 与 `alignment.json` 继续只认 914 场，扩样单独出报告，两者不混算。

---

## 二、数据来源与合并规则

`history/` 下 7 个库的 runID 段互相重叠（如 1-291、192-254、1-235…），直接拼接会互踩，
因此按**文件名排序**给每个库一个偏移：

    merged_run_id = 原 runID + 100000 * (库序号 + 1)

| 库 | 偏移 | runs | rounds |
|---|---|---|---|
| history-01.db | 100000 | 1,001 | 15,161 |
| history-02.db | 200000 | 63 | 1,000 |
| history-03.db | 300000 | 235 | 3,256 |
| history-04.db | 400000 | 95 | 1,210 |
| history-05.db | 500000 | 291 | 4,513 |
| history-06.db | 600000 | 546 | 8,348 |
| history-07.db | 700000 | 1,001 | 15,396 |

合计 **3,232 run / 48,884 回合**；逐回合解码成功 **47,544**（失败 1,340 = 2.7%，
多来自旧版本位宽/索引空间不符，如实剔除，不伪装）。

映射表：`output/oracle/expand/data/history_run_map.json`（merged → 库 + 原 runID）。

---

## 三、工具链

| 步骤 | 工具 | 产物 |
|---|---|---|
| P0 预检 | `tools/expand_build_inventory.py` | `output/oracle/expand/inventory.json`（29 MB，逐回合画像） |
| P1 选样 | `tools/expand_select_cases.py` | `output/oracle/expand/cases.json` + `selection_report.md` |
| 合并库 | `tools/expand_merge_history.py` | `output/oracle/expand/data/history.db`（7 MB） |
| P2/P3 跑批 | `tools/expand_run_oracle.py` | `output/oracle/expand/fights/<case_id>/` |
| 验收 | `tools/expand_accept.py` | `output/oracle/expand/acceptance_report.md` + `acceptance.json` |

### 选样算法（覆盖优先 + 配对铺开）

1. 候选池：解码成功、`item_count ≥ 1`、版本 ∈ {1.1.5 … 1.1.9}；1.1.4 单列补充池。
2. 桶：**职业 × 回合阶段**（1 / 2-3 / 4-6 / 7-9 / 10-12 / 13-15 / 16-18）= 49 桶，
   每桶按「稀有物品得分」确定性抽样 140 个候选。
3. 轮转贪心：稀有物品权重 `w = clamp(40/freq, 0.5, 12)`（freq ≤ 40 才算稀有，
   常见物品给 0.5 保证不漏），每轮在 49 桶里各挑边际增益最大者，桶耗尽即退出。
4. 必含：全局 / 每职业的物品数极值、历史库出现 ≤2 次的超稀有物品。
5. 对手：同阶段、**不同 run**、双方物品多重集不同；评分 = 未覆盖物品增益
   + 未出现过的职业配对（+6.0，已铺开 +2.5）+ 异职业（+1.5）+ 同回合（+1.5）
   − 复用惩罚。
6. 断言：case_id 唯一、对局四元组唯一、镜像对局 0 场。

### 跑批方式（隔离工程 + 并行分片 + 断点续跑）

`oracle_fight.gd` 固定读 `res://fights.json` 与 `res://data/history.db`，而 `oracle/`
是真值面（红线），因此：

- 把 `oracle/` 整体复制到 **`output/_expand/oracle_proj/`**（15,427 文件，约 578 MB）；
- 只替换副本里的 `fights.json`（= 扩样用例表）与 `data/history.db`（= 合并库），
  **脚本一字不改**；
- 输出用 `ORACLE_FIGHTS_ROOT` 重定向到 `output/oracle/expand/fights/`；
- 分片并行：`ORACLE_ONLY_CASES` 分桶 + `ORACLE_FIGHT_CHUNK=60`（防 MessageQueue
  跨场累积劣化）；每进程独立 APPDATA + 隐藏桌面（`tools/godot_headless.py`）；
- resume 幂等：`events.json` 存在且 `event_count > 0` 即跳过，中断可原地续跑。

---

## 四、选样结果（`cases.json`）

| 指标 | 值 |
|---|---|
| 用例数（首批） | **1,168**（选样 1,170，删 2 场超长场后） |
| 补样（第二批） | **+26 场**（稀有物品定向，见 §4.2） |
| 最终用例数 | **1,194** |
| 镜像对局 | **0** |
| 对局四元组重复 | 0 |
| seed 重复 | 0 |
| 对手回合重复 | 0（reuse max = 1） |
| 物品覆盖 | **514 / 514**（历史库可解码物品种类全覆盖） |
| 稀有物品（≤40 次）未覆盖 | 0 |
| 职业配对 | **49 / 49**（每对 ≥ 12 场） |
| 职业分布（玩家） | 7 职业各 149–157 场 |
| 回合阶段 | 7 档各 150–158 场 |

---

### 4.1 超长场裁剪（主人指令：标准高一些）

判据：**ticks ≥ 2700**（约 45 s 游戏时间）视为超长，删除不做语料。删前逐项验证
「删掉后物品是否归零 / 配对是否掉 / 阶段是否掉」，结果全部为否，删除安全。

| 删除场次 | ticks | events | combat_time |
|---|---|---|---|
| run101500_r18_o604508_r18 | 3,061 | 6,178 | 51.0 s |
| run704206_r17_o704790_r17 | 2,761 | 1,843 | 46.0 s |

删后剩余批次最长 **2,669 ticks / 44.5 s**，全部低于 914 场基线里的 54 场长场
（其事件数下限 7,557）。判据写进 `cases.json` 的 `pruning` 段，可复核。

### 4.2 稀有物品补样（第二批 26 场）

首批里 30 件稀有物品（历史库频次 ≤60）有 19 件出场 <3 次。定向补样后：

| 项 | 补样前 | 补样后 |
|---|---|---|
| 稀有物品出场 <3 次 | 19 件 | **2 件** |
| 其中不可达 | — | `Random Loadout Bag`、`Snowman`（装配不落盘） |

补样规则（`tools/expand_supplement.py`）：候选回合与首批**不重复**、对手同阶段
不同 run 且阵容不同；对手也带同一稀有物品时优先（一场补两件）。

---

## 五、复现顺序

```bash
python -X utf8 tools/expand_build_inventory.py     # 1. 逐回合画像（~48s）
python -X utf8 tools/expand_select_cases.py        # 2. 选样（~25s）
python -X utf8 tools/expand_merge_history.py       # 3. 合并库（~1s）
python -X utf8 tools/expand_run_oracle.py          # 4. 跑批（断点续跑）
python -X utf8 tools/expand_supplement.py          # 5. 稀有物品补样（第二批）
python -X utf8 tools/expand_run_oracle.py --cases output/oracle/expand/supplement_cases.json
python -X utf8 tools/expand_accept.py              # 6. 验收
```

冒烟（前 20 场）：`python -X utf8 tools/expand_run_oracle.py --smoke 20`

---

## 六、验收结果（2026-11-07 20:31，已跑完）

| 层 | 判据 | 实测 |
|---|---|---|
| A 完整性 | 全部产出 `events.json`（`event_count > 0`） | **1,194 / 1,194**（首批 1,168 + 补样 26），预检剔除 0、失败 0 |
| B 异阵容 | 逐场比对 `lineups.json` 双方物品多重集，必须不同 | 违例 **0**；双方差异均值 30.9 种、最小 5、最大 57；1,132 场差异 ≥11 件 |
| C 覆盖 | 物品 / 职业配对 / 事件类型 | 物品 **512**（历史库 514）、职业配对 **49/49**、事件类型 **32** 种 |
| D 质量 | winner 可知率、事件数与 ticks | winner 100%（player 677 / opponent 493 / 平 0）；事件总数 565,800，单场均值 484、最大 7,662；tick 均值 786、最大 3,061 |

总耗时：首批约 **1 小时 50 分**（2→4 路自动并发，8 轮分块退出）+ 补样 2 批约 4 分钟。

### 事件类型：与 914 场基线完全同集

本批 32 种事件类型与 914 场语料（913 场 events）的 32 种**完全相同**。8 种定义内
但两批都没触发的类型是：`TakeDamage` / `AttackSpeed` / `CriticalResisted` /
`DamReduction` / `DamIncrease` / `CooldownAdvance` / `Unhealing` / `Fatigue`。

**源码核查结论：这 8 种在 events.json 面不可达**，不是覆盖不足：

| 类型 | 源码证据 | 判定 |
|---|---|---|
| `TakeDamage` / `AttackSpeed` | 全树 `EventType.XXX` 引用 **0 处**（伤害统一走 `createEvent_Damage`） | 死类型 |
| `DamIncrease` | 只在 `createEvent_DamChange` 的 `amount > 0` 分支产生，唯一调用方 `Character.gd:1384` 恒传 `-amount` | 不可达 |
| `DamReduction` | 需 `changeDamageResistance(..., item)` 且传非空 item；全树 26 处调用**均未传 item** ⇒ 事件根本不生成 | 不可达 |
| `CooldownAdvance` | 仅 `Item.gd:4496/4508` 的 `Util.spawnLabelOnItem`（UI 飘字），不落 CombatLog | 不可达 |
| `Unhealing` / `Fatigue` / `CriticalResisted` | 只走 `spawnLabel` / `CombatStatLogger` 聚合；疲劳伤害以 `createEvent_Damage` 记成普通伤害 | 不可达 |

⇒ 32 种已是**可达全集**，补样不可能再增加类型；914 场 0 次与本次 0 次互相印证。

### 物品 512 / 514 的成因（不是缺陷，且不可补）

`inventory.json` 统计的是 **buildInfo 解码出的物品**，`lineups.json` 统计的是
**神谕装配后的库存**。两者差 2 件：

| 物品 | 现象 |
|---|---|
| `Random Loadout Bag` | 解码可见，原版 `deserializeItems` 装配时被展开成其它随机物品（本场 30 件 → 装配 29 件） |
| `Snowman` | 解码可见，装配后不入库存（同类季节/特殊条目） |

二者都是原版语义的**正常差异**，语料本身无缺陷。

**残差说明**：`assets/item_index_map_live.json` 里另有 5 件描述符表物品在历史库从未
出现（`Amulet Unidentified` / `Book of Ice New` / `Hypercube` / `Lootbox` /
`Unidentified Skill`，均为 UI/特殊条目），真实语料无法覆盖，按规划 §5.3 只能靠
合成补充样本，**不混入本轮统计**。

### 配对语义说明（如实记录）

`history.db` **没有「这一局打的是哪个对手 run」的指针**，因此本批对手是
「同回合阶段、不同 run」的跨 run 配对（评分优先未出现过的职业配对 + 未覆盖物品
+ 同回合），而不是同一局的真实对位。这是规划 §5.2 第 5 条允许的配对方式
（`同回合跨 run 配对`），但它证明的是「任意两个真实摆盘对打」，不是「历史实录
对位复现」——与 914 场镜像口径的差异必须在引用时如实标注。

---

## 七、与后续判据升级（J2–J6）的衔接

本轮只产出**神谕侧语料**（`events.json` / `lineups.json` / `result.txt` /
`rng_state.txt`）。要让扩样参与三方对齐，需要：

1. 由 `lineups.json` 生成 `gd_core_test/oracle_align_cases.json`（扩样版，独立文件）；
2. 跑 gd 腿 + py 腿，比对输出到独立的 `alignment_expand.json`；
3. 按规划 §8 P3 的口径出「扩样覆盖报告」，不与 914 场混算。

详见 `docs/扩大用例对齐规划.md` §6、§8。
