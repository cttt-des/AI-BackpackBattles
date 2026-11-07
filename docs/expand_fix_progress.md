# 扩样语料接入三方对齐——修复过程留档（追加式）

> 任务：按 `docs/expand_fix_kickoff.md` §10 队列 1–4 执行（闲时任务 offpeak-5338e75f）。
> 纪律：任何情况下不自行退出；阻塞即留档并转下一项。本文件保证任意时刻中断后可恢复。
> 语料：`output/oracle/expand/fights/`（1,194 场，验收 PASS，只读）。
> 红线：`oracle/`、`output/oracle/fights/`（914）、`output/oracle/alignment.json`、`align/` 不碰；
> 扩样产物全部落独立 root。

## 0. 盘面核对（开工时）

- kickoff 指出的两处硬编码属实：`tools/verify_oracle.py:63-69` 五个路径常量、
  `tools/gen_fixture_from_lineup.py:188` `_HISTORY_DB`。
- **kickoff 未点名、但实测同样阻断的第 3 处**：`gen_fixture_from_lineup.py` oracle 模式
  解析玩家 run_id 用 `re.match(r"run(\d+)_r\d+$", case_id)`——扩样 case_id
  `run<玩家>_r<回合>_o<对手>_r<对手回合>` 带 `_o…` 后缀，`$` 锚定必不匹配 ⇒
  run_id=None ⇒ stamina 静默退回 base（§6.2 同型假分歧，即使修了 db 路径也踩）。
  修法：正则放宽为 `r"run(\d+)_r\d+(?:_o\d+_r\d+)?_$"`（基线形状仍匹配，零回归）。
- **kickoff 未点名的第 4 处**：`gd_core_test/OracleAlignBattle.gd:1212-1216` 硬编码读
  `res://oracle_align_cases.json`、`:1255` 硬编码 `_fights_root = res://../output/oracle/fights`
  （rng_state.txt 来源）。gd 腿若不能指到扩样夹具与扩样语料根，rng_state 注入静默缺失 ⇒
  gd 腿从开战分叉。修法：加两个**默认不变**的环境变量覆盖
  `ORACLE_ALIGN_CASES_JSON` / `ORACLE_ALIGN_FIGHTS_ROOT`（harness 驱动层参数化，
  np46 以来同类先例；gd_core 内核零改动，gd_to_py 无需重跑）。
- `tools/verify_oracle.py` `select_cases()` 还硬编码读 `oracle/fights.json`（914 用例表）——
  扩样 root 下必须改读语料旁的 `output/oracle/expand/cases.json`（格式含
  case_id/seed/round_id，已核实）。
- 基线完整性：`output/oracle/fights` 914 场、`git status oracle/` 干净、
  `output/oracle/align/gdcore` 914 场产物在盘（冒烟可幂等跳过）。
- 扩样 fights 目录 = 1,194 场 + `_batch_summary.{json,txt}`、`_progress.txt` 三个批处理文件。

## 1. Step 1/1b/2 改动清单（全部默认零回归）

| 文件 | 改动 |
|---|---|
| `tools/gen_fixture_from_lineup.py` | ① `_HISTORY_DB` 支持 `EXPAND_HISTORY_DB` 环境变量 + `--history-db` 参数 + `set_history_db()` 进程内覆盖（缺省=基线库）；② 玩家 run_id 正则放宽为 `run(\d+)_r\d+(?:_o\d+_r\d+)?$`（扩样 case_id 带 `_o…` 尾段，旧式 `$` 锚定必失配 ⇒ stamina 静默退 base） |
| `gd_core_test/OracleAlignBattle.gd` | harness 驱动层参数化（np46 以来同类先例，gd_core 内核零改动）：夹具路径 `ORACLE_ALIGN_CASES_JSON`、语料根 `ORACLE_ALIGN_FIGHTS_ROOT` 两个环境变量覆盖，缺省路径不变 |
| `tools/verify_oracle.py` | ① 四参数 `--fights-root/--align-root/--cases-json/--alignment-out`，main() 解析后重绑全局（worker 分发之前），只给 fights-root 时 align-root 自动落语料旁 `align_expand` 防污染基线；② `select_cases` root 感知：非默认语料根读旁表 `cases.json`，缺表报错不静默；③ worker 子进程经 `_root_cli_args()` 继承同组参数（gd/py/compare 三处）；④ gd 腿 env 下发 `ORACLE_ALIGN_FIGHTS_ROOT`+`ORACLE_ALIGN_CASES_JSON`（基线模式恒空） |
| `tools/expand_gen_fixtures.py` | 新增：分批（200/批）进程内驱动 oracle_mode，合并成 `gd_core_test/expand_align_cases.json`，label_rng=True 与 gen_fixtures 同口径；**收尾自检**=逐场比对夹具玩家 stamina vs 合并库直查（防 §6.2 假分歧复发，不符硬失败）；失败清单落 `output/oracle/align_expand/fixture_failures.json` |

## 2. 冒烟记录

| 冒烟 | 命令要点 | 结果 |
|---|---|---|
| 基线零回归 | `verify_oracle.py --limit 3 --skip-fixtures`（默认 root，报告落 `output/_expand/smoke_default3.json`） | **3/3 三方一致**；`output/oracle/alignment.json` 与 `gd_core_test/oracle_align_cases.json` sha256 前后一致（6c1a1e94…/92bd5d62…），零扰动 |
| 取数链自检 | 进程内实测 | 扩样合并库 `run604589_r16→9.0`、`run101500_r18→8.0`（偏移 runID 可查）；基线库 `run570_r18→5.0` 照常 |
| 夹具驱动 | `expand_gen_fixtures.py --limit 6` | 6/6 生成、0 失败、stamina 库命中 6/6 数值零误差 |
| 扩样 3 场烟雾 | `verify_oracle.py --fights-root … --align-root … --cases-json … --alignment-out … --skip-fixtures --force --cases <3 场>`（含 run604589_r16，stamina=9≠base=5，专门验证注入链） | **3/3 三方一致** |

### 踩坑记录（本次修复期）

- 比对 worker（`--compare-worker`）的 spawn 命令最初漏拼 `_root_cli_args()` ⇒
  worker 用默认 914 root 找语料 ⇒ 3 场烟雾全报「oracle 缺产物」。已修
  （compare_cases 内 spawn 追加 `_root_cli_args()`）。教训：四参数重绑的传递面
  有三处 worker 入口，新增参数时三处都要接。

## 3. Step 3 全量夹具生成（完成）

- `python -X utf8 tools/expand_gen_fixtures.py` → **1,174/1,194 场生成**，
  stamina 自检 **1,174 命中 / 0 缺行 / 0 数值不符**（kickoff §6.2 假分歧根治实证）。
- 20 场失败，原因全部 = `物品不在 gd_core 描述符表：['Coins']`（kickoff §6.3 预期语义：
  装配后派生成别的 item，记报告剔除、不改内核）→
  `output/oracle/align_expand/fixture_failures.json`。
- 新发现告警面：**61 场** lineup 含 `Time Pendant`，该物品不在 `assets/battle_items.json`
  （py 侧描述符表没有）→ 夹具期两侧一致剔除并告警。914 基线夹具 0 场含此物品，
  扩样是首次暴露；若这 61 场出现分歧，归因时优先核对 Time Pendant 的战斗面效果
  与邻格影响（预案已记 `output/oracle/align_expand/time_pendant_cases.txt`）。
- 产物：`gd_core_test/expand_align_cases.json`（1,174 场，format oracle-align-cases/1，
  label_rng=True 全量注入）；批 tmp 与逐批日志留
  `output/oracle/align_expand/_fixture_batches/`。

## 4. 环境备忘（本沙箱实测）

- **沙箱内 `GlobalMemoryStatusEx` 调用失败**（返回全零：memload 0%/avail 0.00 GB 不可能），
  `verify_oracle._avail_mem_gb` 按设计退回 8.0 GB → auto_jobs 上限偏乐观。
  故全量跑显式指定 `--gd-jobs 3 --py-jobs 2 --compare-jobs 3`（kickoff §7.5：
  别硬压 4 路；机器历史实测档位内）。
- git-bash 的 `while read` 循环变量带 CRLF ⇒ `"$f"` 打不开文件（ugrep No such file）；
  对 glob 一次性 grep 即可。

## 5. Step 4 全量验证（完成，墙钟 ~13 分钟）

- gd 腿 1,174 场 3 路 359–466s；py 腿分片流水跟随 682s 共 6 片失败 0；比对 3 路 75s。
- **结果：三方一致 1,087 / 1,174（92.6%）**；oracle≠gdcore 74、gdcore≡oracle 但 py 分歧 13。
- 账本独立落盘 `output/oracle/expand/alignment_expand.json`；日志
  `output/oracle/align_expand/full_verify.log`；主运行耗时与并行决策见该日志。

## 6. Step 5 逐场归因（完成，87/87 归位）

| 组 | 场数 | 根因 | 关键证据 |
|---|---|---|---|
| A Time Pendant 未实现 | 61 | 物品不在 `assets/battle_items.json` ⇒ 夹具两侧一致剔除，但神谕语料含其实战激活（≤14 次/场）⇒ gd/py 装配起少一件 ⇒ t=0 激活链错位 | 61/61 首分歧 t≈0（index 中位 4）；oracle events 实证 TP 激活；16/61 胜方翻转；914 基线 0 场含 TP（首次暴露非回归） |
| B Dark Lantern py 取整差 | 13 | t=0 lose_health amount：gd/-神喻 = 整数（-107），py 保留 0.5 尾数（-107.5）——转写层取整口径差 | 13/13 同型签名（t=0、type=5、Dark Lantern、差恰 0.5）；事件数 o=g=py 全等；914 基线仅 1 场含 Dark Lantern（未触发） |
| C 真分歧 | 13 | C1 Time Dilator ×2（914 零覆盖，激活 tick 差）；C2 判胜时机 ×3（gd 当拍 win vs 原版等当前链走完）；C3 Sloth 临时体上限 522 vs 262 ×1；C4 Hogus Bogus 掷值 49 vs 27 ×1；C5 链位/计时漂移 ×6 | 逐场首分歧签名 + 结构化清单 `output/oracle/expand/divergence_cases.json` |

四个常见误因排除：①stamina 取数 ✔（1,174/1,174 逐场对库相符）②物品未实现 ✔（正是 A/C1）
③长场 tick 上限 ✔ 排除（87 场首分歧全 kind=event，无 length；最长 2,669<5,400）
④装配顺序 ✔ 排除（夹具保序 + 1,087 场全链一致）。

正式报告：`output/oracle/expand/expand_alignment_report.md`（含 87 场逐场附录）。

## 7. 交付物核对（任务收口时全部在盘）

1. ✅ `tools/gen_fixture_from_lineup.py`：`--history-db`/`EXPAND_HISTORY_DB`/`set_history_db` + 扩样 case_id 正则；默认零回归（基线冒烟 3/3 + sha256 前后一致）
2. ✅ `tools/verify_oracle.py`：四参数 + root 感知选样 + worker 参数传播（gd/py/compare 三处）+ gd env 下发；默认零回归同上
3. ✅ `gd_core_test/expand_align_cases.json`（1,174 场；`gd_core_test/oracle_align_cases.json` sha256 未变）
4. ✅ `output/oracle/align_expand/`（gdcore/py/render/lineups/_gd_shards/_py_shards/_cmp_shards）+ `output/oracle/expand/alignment_expand.json`
5. ✅ `output/oracle/expand/expand_alignment_report.md` + `divergence_cases.json` + `fixture_failures.json`
6. ✅ 本留档 + README §⑥ 更新

**基线完整性（收口终检）**：`output/oracle/alignment.json` sha256=6c1a1e94…（未变）、
`gd_core_test/oracle_align_cases.json` sha256=92bd5d62…（未变）、`git status oracle/` 干净、
914 场语料与 gd 腿产物原数在盘。`oracle/` 真值面零改动；gd_core 内核零改动
（`OracleAlignBattle.gd` 为 harness 参数化，env 缺省路径不变）。

**剩余风险与下一步**：见报告 §3/§6——B 组单点修复（预期 +13 场翻绿）、
A 组 Time Pendant 实现（需授权动内核四树）、C 组 np24 式双链 trace 逐场定谳；
扩样是否纳入日常 gate 由主人定夺。

## 8. 外部改动发现（2026-11-07，任务收口后盘点覆盖面时发现）

- **主人确认：仓库内有另一个 agent 在工作。** 收口终检之后覆盖面复扫时发现：
  `assets/battle_items.json`（+73,181 行）与 `assets/gd_core_runtime.json`（单行重生成）
  于 **22:54:07** 被改动（本会话开始时 git 快照 assets/ 干净；非本任务产物）。
  改动内容为数据面重生成：battle_items.json 新增 `Time Pendant`、`Coins` 等条目。
- **对本留档结论的影响**：§6 A 组归因「Time Pendant 不在 battle_items.json」在
  **对齐运行时点成立**（夹具生成与全量验证均早于 22:54，61 场告警与分歧为实证）；
  22:54 之后该物品已在表中——另一 agent 显然正在处理数据面。
  `output/oracle/expand/alignment_expand.json` 与报告反映的是 **22:54 之前的表状态**。
- **本任务不做的**：不触碰 assets/、不 checkout/回滚外部改动、不重跑夹具与两腿
  （可能与另一 agent 冲突）。A 组 61 场在新表下是否翻绿，待对方工作落地后另行验证。
- **覆盖面复扫结论（2026-11-07，基于语料实测，与资产表改动无关）**：
  物品 519 表内未覆盖 **7 件**（5 件 UI/特殊条目 Amulet Unidentified / Book of Ice New /
  Hypercube / Lootbox / Unidentified Skill + 2 件装配不落盘 Random Loadout Bag / Snowman，
  两批语料均 0 场）；宝石 34/34 并集全覆盖；扩样物品集 ⊇ 914 基线（仅 914 有 = 无）；
  事件 32 可达全绿（最稀 Reincarnate 28 次），8 种定义不可达
  （4 TakeDamage / 6 AttackSpeed / 11 CriticalResisted / 17 DamReduction / 18 DamIncrease /
  24 CooldownAdvance / 98 Unhealing / 99 Fatigue）；装配面缺口：Coins 至今不在
  gd_core 夹具表 item_battle_fixture.json（20 场剔除维持），Time Pendant 22:54 起
  两表均有（此前仅 gd 夹具表有、battle_items.json 缺）。

## np50｜A 组 Time Pendant 内核落地（2026-11-07 23:0x）

**触发**：主人确认「1.1.9 物品终须实现」，先跑第一步（定点补 Time Pendant，不整树换基线）。

**真值来源（联网解包，未动游戏目录）**
- Steam 当前 pck（`/d/Steam/steamapps/common/Backpack Battles/BackpackBattles.pck`，只读）与工作区 `output/game_copy/` 副本 **MD5 相同**（cbbc259e…），确认是 1.1.9（含 TimePendant）。
- 自研 `tools/pck_full_extract.py` 解包：**9397 条目 MD5 全对**（`output/_re_extract/full/`）。
- 下载 GDRE Tools v2.7.4（`tools/gdre/`，已 gitignore）`--recover --key` 完整恢复：**821 个干净 .gd**（`output/_re_extract/gdre119/`），与 `oracle/` 787/821 逐字节相同，34 个不同者正是插桩件；`oracle/` 独有 13 个为 harness 自有文件。tscn/tres 1201 个全同。
- **结论**：1.1.7→1.1.9 真实差异仅 **13 文件 / 106 行**，战斗相关只有 `Item.gd` 两处（标签 `reduction/getSpeed()`、装配期 rotation 归零）与 `ChessMaster.gd` 的 `weights[0] 3→1`；1.1.9 独有脚本只有 `TimePendant.gd`（12 行）。

**改动（四树同步 + 两级夹具重建）**
1. `gd_core_items/Exclusive/TimePendant.gd`（新建，按 1.1.9 干净版转译形态）+ `gd_core_test/gd_core_items/` 镜像。
2. `assets/battle_items.json`：+Time Pendant（cdadvance=1.0 / price=8 / cd=2 / rarity=Unique / material=Jewelry / 1×1 / behavior.script_file），并由 `simulator/extract_grid.py` 从 oracle/Items tscn 补 grid（collision [[-1,-1]]、affected [[-1,0]]）。
3. `assets/gd_core_runtime.json`：由 `tools/gen_gd_core_data.py` **重新生成**（必须——py 腿 `_place_of` 读 `items[key]["rot"]`，手写条目会 KeyError: 'rot'）。
4. `tools/gd_to_py.py` 重生成 → `gd_core_py/gd_core_items/Exclusive/TimePendant.py`。
5. 夹具两级重建：`gen_lineup_fixture.py`（描述符表 518 件，仅 Coins 无脚本）→ `expand_gen_fixtures.py --force`（**1,174/1,194**，20 场 Coins 剔除，与修复前一致；含 TP 的场次从 0 → **61**）。

**结果**

| 指标 | 修复前 | 修复后 |
|---|---|---|
| 扩样三方一致 | 1,087 / 1,174（92.6%） | **1,143 / 1,174（97.4%）** |
| oracle≠gdcore | 74 | **18** |
| gd≡oracle 但 py 分歧 | 13 | 13（未动） |
| 914 基线 | 914/914 | **914/914**（REG 九场 gd+py 全 PASS；抽样 6/6 全绿） |

A 组 61 场转绿 **56** 场；残余 5 场 `run101490_r5/r6/r8/r9/r12` 与 C 组 `run101490_r3` 同玩家，属叠加根因，已并入 C 组待 trace。

**踩坑记录（供后续物品补建复用）**
1. 只补 `battle_items.json` 不够：`gen_lineup_fixture.py` 靠 `behavior.script_file` 找转译产物，缺该字段则该物品被 `skipped`（夹具重新生成会从 1,174 掉到 1,113）。
2. `types` 只能写 CoreConst.Type 枚举名（`accessory`），`jewelry` 是 material，写了会 `未知类型名` 硬失败。
3. 手写 `gd_core_runtime.json` 条目必须带 `rot` 四朝向，否则 py 腿 `_place_of` 抛 `KeyError: 'rot'`；正解是跑 `gen_gd_core_data.py` 生成而非手写。
4. `battle_items.json` 是**单行紧凑 JSON**（无缩进），用 indent 重写会产生 7 万行假 diff（语义零变化）。
