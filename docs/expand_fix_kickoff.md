# 扩大语料修复起步参考（新 agent 交接）

> 写给**接手者**：这篇文档假设你只读过它，没参与上一轮扩样。
> 读完你应该能回答：这批语料是什么、验证到什么程度、下一步修什么、哪些坑踩过一次别再踩。
> 生成：2026-11-07 21:12（上一轮扩样收尾时）｜上一轮执行者留下的全部产物与结论如下。

---

## 0. 一句话现状

**1,194 场「全异阵容」扩样语料已生成并通过验收**（`output/oracle/expand/fights/`），
与 914 场镜像基线**完全隔离**。语料侧的覆盖面已经打满：物品 512/514、职业配对 49/49、
事件类型 32 种（= 可达全集）。**但语料还没接入三方对齐**——这是你接手的第一件事。

---

## 1. 你继承的资产

### 1.1 语料（只读，别改）

| 路径 | 内容 | 规模 |
|---|---|---|
| `output/oracle/expand/fights/<case_id>/` | 每场神谕语料：`events.json` / `lineups.json` / `result.txt` / `rng_state.txt` | 1,194 场，259 MB |
| `output/oracle/expand/cases.json` | 用例表（含 `pruning` 裁剪记录、`batch` 批次标记） | 1,194 条 |
| `output/oracle/expand/inventory.json` | 全库逐回合画像（7 库合并后 47,544 回合） | 29 MB |
| `output/oracle/expand/data/history.db` | **合并历史库**（runID 加偏移，神谕读的那份） | 7 MB |
| `output/oracle/expand/data/history_run_map.json` | 合并 runID → (源库, 原 runID) | — |
| `output/oracle/expand/acceptance_report.md` | 验收报告（当前 PASS） | — |
| `output/oracle/expand/README.md` | 目录速查表 | — |

**914 场基线未受任何影响**：`output/oracle/fights/`（914 场）、`output/oracle/alignment.json`、
`oracle/` 全部保持原状（`git status` 可见 `oracle/` 零改动）。

### 1.2 工具（都在 `tools/`，可直接复用）

| 工具 | 作用 | 耗时 |
|---|---|---|
| `expand_build_inventory.py` | 扫 `history/*.db` → 逐回合解码 → `inventory.json` | ~48 s |
| `expand_select_cases.py` | 覆盖优先选样（49 桶轮转贪心 + 配对铺开） | ~25 s |
| `expand_merge_history.py` | 7 库合并成神谕可读单库 | ~1 s |
| `expand_run_oracle.py` | **跑批**：隔离工程副本 + 分片并行 + 断点续跑 | 见 §5 |
| `expand_supplement.py` | 稀有物品定向补样（第二批入口） | ~3 s |
| `expand_accept.py` | 验收（完整性/异阵容/覆盖/质量） | ~11 s |

### 1.3 必读（按顺序，别跳）

1. `docs/expand_corpus_guide.md` —— **本批语料的权威口径**：合并规则、选样算法、跑批方式、
   超长场裁剪、稀有补样、事件类型不可达的源码证据。
2. `docs/扩大用例对齐规划.md` —— 上位规划：J1–J6 判据、三档并发预设、P0′–P4 阶段。
   **注意**：它写于 10-24，部分数字（914/914 证据重建、§2.4 事件闸）已在 11-07 收口，
   实际现状以 `README.md` §⑥ 与 `docs/np24_fix.md` 为准。
3. `docs/np24_fix.md` —— 914/914 的收口留档（架构、修复史、复现）。**改内核前必读**。
4. `docs/parallel_workflow.md` —— 三腿并行验证的无窗口启动与禁管道铁律。
5. `output/oracle/expand/acceptance_report.md` —— 当前语料的自证。

---

## 2. 这批语料的性质（三条必须理解的设定）

### 2.1 全部异阵容，对手是「同阶段跨 run 配对」

`history.db` **没有「这局打的是哪个对手 run」的指针**，所以对手是构造出来的：
从同回合阶段、不同 run 的真实摆盘里选，双方物品多重集保证不同（实测差异均值 30.9 种）。

- 证明的是「**任意两个真实摆盘对打**」，**不是**「历史实录对位复现」。
- 与 914 场（同 run 同回合**镜像**）口径相反，引用结论时必须标注。
- `cases.json` 的 `opp_run_id` / `opp_round_id` 就是对手侧，`case_id` 命名：
  `run<玩家run>_r<玩家回合>_o<对手run>_r<对手回合>`。

### 2.2 runID 是加过偏移的

`history/` 下 7 个库 runID 段重叠（1-291、192-254、1-235…），合并时按文件名排序加偏移：

    merged_run_id = 原 runID + 100000 * (库序号 + 1)

| 源库 | 偏移 |
|---|---|
| history-01.db | +100000 |
| history-02.db | +200000 |
| history-03.db | +300000 |
| history-04.db | +400000 |
| history-05.db | +500000 |
| history-06.db | +600000 |
| history-07.db | +700000 |

→ 精确映射见 `output/oracle/expand/data/history_run_map.json`。**任何要回查原始库的脚本，
都必须用这份映射或同样的偏移规则**，否则查到的是别的 run。

### 2.3 版本构成

玩家侧：1.1.5×60、1.1.6×90、1.1.7×140、1.1.8×260、1.1.9×520，另有 1.1.4 单列 100 场 + 补样 26 场。
库内 1.0.x–1.1.3 的回合（约 3,400 个）**没有进语料**——神谕 1.1.9 对旧版本位宽/索引空间不兼容，
预检剔除率会偏高；要纳入必须先做解码实测。

---

## 3. 已定谳结论（别再花时间去论证）

| 结论 | 证据 |
|---|---|
| **8 种事件类型在 `events.json` 面不可达** | `TakeDamage`/`AttackSpeed` 全树 0 引用；`DamIncrease` 唯一调用方恒传负值；`DamReduction` 需非空 `item`，全树 26 处 `changeDamageResistance` 调用均未传；`CooldownAdvance` 只走 `Util.spawnLabelOnItem`；`Unhealing`/`Fatigue`/`CriticalResisted` 只走 `spawnLabel` 与统计聚合。详见 `docs/expand_corpus_guide.md` §6 |
| 32 种已是可达全集 | 扩样 1,194 场与 914 场（913 份 events）**同集同数**，互相印证 |
| 物品 512/514 不是缺陷 | 差的 2 件 `Random Loadout Bag` / `Snowman` 解码可见但**装配不落盘**（原版语义），语料无法覆盖 |
| 描述符表 5 件永久不可覆盖 | `Amulet Unidentified`/`Book of Ice New`/`Hypercube`/`Lootbox`/`Unidentified Skill`，历史库从未出现，属 UI/特殊条目 |
| 超长场规则 = ticks ≥ 2700 删 | 已删 2 场（3,061 / 2,761 ticks），删后验过物品、配对、阶段均不掉；剩余最长 2,669 ticks / 44.5 s |
| 稀有物品（≤60 次）出场已补齐 | 30 件里 28 件 ≥3 次，剩 2 件即上述不可落盘物品 |

---

## 4. 当前语料的真实状态（验收数据）

| 维度 | 结果 |
|---|---|
| 完整性 | 1,194 / 1,194，预检剔除 0、解析错误 0 |
| 异阵容 | 双方物品多重集相同 = **0**；差异 11+ 件 = 1,156 场 |
| 物品 / 宝石 | 512 / 514 种；宝石 35 种 |
| 职业配对 | **49 / 49**（每对 ≥12 场） |
| 事件类型 | **32** 种 / 可达 32 |
| 胜负 | player 689 / opponent 505 / 平 0 |
| 事件量 | 总计 570,329；单场均值 478、最大 7,662 |
| 时长 | tick 均值 783、最大 2,669（≈44.5 s） |

复核命令（30 秒）：`python -X utf8 tools/expand_accept.py`

---

## 5. 怎么跑批（复现 / 补场）

### 5.1 核心约束：神谕固定读 `res://`

`oracle_fight.gd` 读 `res://fights.json` 与 `res://data/history.db`（`oracle/oracle_fight.gd:475`），
只有**输出**能用环境变量重定向（`ORACLE_FIGHTS_ROOT`，`:379`）。而 `oracle/` 是真值面（红线），
所以做法是：

    oracle/  ──复制──▶  output/_expand/oracle_proj/   （15,427 文件，583 MB）
                          只替换 fights.json 与 data/history.db
    ORACLE_FIGHTS_ROOT  ──▶  output/oracle/expand/fights/

`tools/expand_run_oracle.py` 自动完成注入（约 73 s 复制一次，之后复用），**不要**手工改 `oracle/`。

### 5.2 命令

    # 冒烟 20 场（等距抽样）
    python -X utf8 tools/expand_run_oracle.py --smoke 20

    # 全量（自动并行 + 断点续跑，events.json 非空即跳过）
    python -X utf8 tools/expand_run_oracle.py --chunk 60 --max-rounds 40

    # 补样批次（用例表可任意指定，仍写同一 root）
    python -X utf8 tools/expand_run_oracle.py --cases output/oracle/expand/supplement_cases.json

    # 验收
    python -X utf8 tools/expand_accept.py

### 5.3 实测吞吐（8 核 / 16 GB，可用内存 0.5–3.3 GB 波动）

| 阶段 | 场数 | 并行 | 耗时 |
|---|---|---|---|
| 首批 | 1,168 | 2→4 路自动 | ~1 h 50 min |
| 补样 1 | 24 | 4 路 | ~2.5 min |
| 补样 2 | 2 | 1 路 | ~1.5 min |

单场墙钟：装配约 10 s + 战斗 6–51 s。**进程启动与资源导入约 60–80 s**，所以每块跑得多才划算。

---

## 6. 你的第一件事：把语料接进三方对齐

### 6.1 现状缺口

`tools/verify_oracle.py` 的路径**全部硬编码**，没有 `--fights-root`：

| 常量 | 行 | 值 |
|---|---|---|
| `FIGHTS_DIR` | 63 | `output/oracle/fights` |
| `ALIGN_DIR` | 64 | `output/oracle/align` |
| `CASES_JSON` | 69 | `gd_core_test/oracle_align_cases.json` |

直接拿它跑扩样会**读错语料、写脏 914 的产物**。

### 6.2 ⚠️ 已知阻断点（必须先修，否则会产出假分歧）

`tools/gen_fixture_from_lineup.py:188`：

    _HISTORY_DB = os.path.join(ROOT, "oracle", "data", "history.db")

夹具生成要用**玩家回合开局 stamina**（`roundData.stamina` 明文列）。扩样的 run_id 只在
`output/oracle/expand/data/history.db` 里，用旧库**查不到** → 静默退回 base stamina →
gd 腿与神谕从开战就不同源 → 你会看到一批莫名其妙的「分歧」，其实是取数取错了。

**修法（按推荐度）**：
1. 给 `gen_fixture_from_lineup.py` 加 `--history-db` 参数（默认仍是原值，零回归）；
2. 或者给 `_HISTORY_DB` 加环境变量覆盖（`EXPAND_HISTORY_DB`），扩样脚本显式传入；
3. 不要复制覆盖 `oracle/data/history.db`——那会让 914 场口径失效。

### 6.3 落地步骤（建议顺序）

**Step 1｜生成扩样夹具**

    python -X utf8 tools/gen_fixture_from_lineup.py --oracle \
        output/oracle/expand/fights/run<...>_o<...>/ ...

- 不要一次塞 1,194 个目录进命令行（会超长）——写个小驱动按 200 场一批调用；
- 输出到**独立文件**：`gd_core_test/expand_align_cases.json`（别碰 `oracle_align_cases.json`）；
- 若报「物品不在 gd_core 描述符表」，说明该物品装配后派生成了别的 item（正常语义），
  把该场记入报告剔除，不要为它改内核。

**Step 2｜改 `verify_oracle.py` 支持独立 root**（规划 §7.2 早就列了，一直没做）

最小改动：新增 `--fights-root`、`--align-root`、`--cases-json`、`--alignment-out` 四个参数，
默认值保持现状（零回归），全量仓库调用照旧。

**Step 3｜跑腿 + 比对**

    python -X utf8 tools/verify_oracle.py --fights-root output/oracle/expand/fights \
        --align-root output/oracle/align_expand \
        --cases-json gd_core_test/expand_align_cases.json \
        --alignment-out output/oracle/expand/alignment_expand.json

**Step 4｜出独立报告，不混算**

规划 §8 的硬约定：扩样账本独立、报告独立，**绝不把扩样场次加进 `alignment.json`**。
先出「扩样分歧清单」，逐场归因后再谈闸门。

### 6.4 判据预期（重要）

914 场是**逐案隔离重录**的干净形状（`np46` 起）。扩样语料走的是同一条录制管线
（同一个 `oracle_fight.gd`、同样逐案隔离），所以**理论上应该同样全绿**；若出现分歧，
优先怀疑：① 上面的 stamina 取数错；② 某物品在 gd_core 侧未实现；③ 长场 tick 上限；
④ 装配顺序（`lineups.json` 的 items 顺序即装配顺序，夹具必须原样保持）。

---

## 7. 环境铁律（踩过就疼）

1. **Godot 3.6 没有 `--headless`**。写了会被当位置参数忽略 → 真的弹出窗口。一律走
   `tools/godot_headless.py`（隐藏桌面 + 屏外 `--position` + 静音音频）。
2. **禁匿名管道**。`subprocess` 的 `capture_output=True` / `PIPE` 一律 `WinError 5`；
   输出必须重定向到文件再读回。
3. **并行必须独立 APPDATA**（`gh.env(tag)` 已封装），否则 `user://` 互踩、日志句柄冲突。
4. **`ORACLE_FIGHT_CHUNK` 必须小**（本项目用 60）。MessageQueue 跨场累积，实测约 116 场后
   单场劣化到 500 s+/800 MB。
5. **内存闸**：单 Godot 峰值约 300–600 MB；本机可用内存会随浏览器/ZCode 波动到 0.5 GB，
   `expand_run_oracle.py` 按 1.5 GB/路保守估算自动决定并行度（上限 4）。别硬压 4 路。
6. **`robocopy` 在 git-bash 下会把 `/E` 当路径**（rc=16）→ 用 `shutil.copytree`。
7. **`run_code` 内 `sleep` 上限**：单次程序有执行时限（默认 120 s，可传 `timeoutMs` 上限 600 s），
   长等待要用后台 job + `job_output(wait)`，别在程序里裸 sleep 超过时限。

---

## 8. 坑清单（Checklist：动手前逐条核对）

- [ ] 我要读的语料 root 是哪个？扩样 `output/oracle/expand/fights/`，基线 `output/oracle/fights/`——**别混**。
- [ ] 我查 run 原始 ID 了吗？合并库的 run_id 有 `+100000×库序号` 偏移。
- [ ] 我的夹具用哪份 history.db 取 stamina？扩样必须用 `output/oracle/expand/data/history.db`。
- [ ] 我的输出写到哪里？扩样必须独立 root；不要覆盖 `alignment.json`、`align/`。
- [ ] 我改的是 `oracle/` 吗？**那是红线**，除授权外一律只改副本 `output/_expand/oracle_proj/`。
- [ ] 我是否在给「不可达事件类型」写补样逻辑？省下这个时间（§3 已证）。
- [ ] 我是否在给 `Random Loadout Bag`/`Snowman` 做覆盖？不可能覆盖（§3）。
- [ ] 跑批前确认 `events.json` 已存在且非空的场会被跳过（resume 幂等），`--force` 语义另论。
- [ ] 并行度是不是又硬写了 4？看当时可用内存。

---

## 9. 红线与授权边界

| 对象 | 规则 |
|---|---|
| `oracle/`（真值面） | 默认不动。改脚本/改 `fights.json`/改 `data/history.db` 都需主人授权 |
| `output/oracle/fights/`（914 基线语料） | 只读。任何重录需备份 + 单独授权 |
| `output/oracle/alignment.json` | 只能由 `verify_oracle.py` 产出，**禁手写** |
| 内核四树 `gd_core/` `gd_core_test/` `gd_core_items/` `gd_core_py/` | 改动需四树同步后重跑 `tools/gd_to_py.py`，并跑 REG gate |
| `history/*.db`（主人给的数据） | 只读（脚本都用 `?mode=ro`） |
| 本批扩样产物 | 可增删（补样/裁剪），但每次改动要重跑 `expand_accept.py` 并更新报告 |

---

## 10. 建议的任务队列（按收益排序）

| # | 任务 | 收益 | 预估 |
|---|---|---|---|
| 1 | 修 `gen_fixture_from_lineup.py` 的 `_HISTORY_DB` 硬编码（加 `--history-db`） | 解锁扩样对齐 | 30 min |
| 2 | `verify_oracle.py` 加 `--fights-root` 等四个参数（默认值不变） | 同上，零回归 | 1 h |
| 3 | 生成扩样夹具 + 跑 gd/py 腿 + 比对，出 `alignment_expand.json` 与分歧清单 | **核心目标** | 2–4 h |
| 4 | 对分歧逐场归因（先排除 §6.4 的四个常见误因） | 修复起点 | 视分歧数 |
| 5 | 规划 §6 的 J2–J6 判据升级（tick 状态 dump / 逐抽 rng / 不变量 / 变异灵敏度） | 判据从「事件面」升到「状态面」 | 大工程，需授权 |

**不要做的**：继续扩场次（覆盖面已满）、追不可达事件类型、重跑 914 基线、
为凑数合成摆盘（规划 §5.3 允许但要求单独标注、不混入真实分布结论）。

---

## 11. 五个常用自检命令

    # 1. 语料还在吗、多少场
    ls output/oracle/expand/fights | wc -l

    # 2. 验收（完整性/异阵容/覆盖）
    python -X utf8 tools/expand_accept.py

    # 3. 用例表统计（批次、裁剪记录）
    python -X utf8 -c "import json;d=json.load(open('output/oracle/expand/cases.json',encoding='utf-8'));print(len(d['cases']),d.get('pruning'),d.get('totals'))"

    # 4. 单场结果速看
    head -12 output/oracle/expand/fights/<case_id>/result.txt

    # 5. 基线有没有被动过（应为 914 场、git 无 oracle/ 改动）
    ls output/oracle/fights | wc -l && git status --short oracle/

---

## 12. 交接备忘（上一轮的执行者的话）

- 语料这一层的**覆盖已经打满**，剩下的价值全在「接进三方对齐 + 找真分歧」。
- 我踩过最贵的坑是 **stamina 取数来源**（§6.2）——它不会报错，只会让你看到假分歧，
  排查方向会一路歪到内核里去。动手前先把这一行改掉。
- 跑批本身很稳（1,194 场零失败），不稳定的只有环境：内存、弹窗、MessagePool。
  遇到怪事，先怀疑这三样，再怀疑内核。
