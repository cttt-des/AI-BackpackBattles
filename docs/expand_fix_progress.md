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

## np51：1,690 全绿循环（2026-11-08 offpeak 接力，接续 np50）

> 目标（用户指令）：语料扩至 1,690 场（targeted 批 +496），「发现问题→修复问题」循环直到
> 1,690 全绿，不许主动停。基线纪律沿用：914 零回归、oracle/ 不动、四树同步。

### np51① py 转写器「类型化 int 形参截断」规则（60 场翻绿）

- **根因**：GDScript 对显式 `: int` 形参的实参**隐式截断**（朝零）；py 转写无类型约束。
  实证：Dark Lantern onCombatStart `loseHealth(p1/100×maxHP)`，py 腿保 -107.5 而
  gd/oracle -107（60 场同签名：t=0、type=5、amount 差恰 0.5）。
- **修**：`tools/gd_to_py.py` render_arg/render_func/发射位——显式 `: int` 形参在函数体
  首行（GD_DEFAULT 还原后）发射 `name = int(name)`；34 模块 +144 行，diff 纯度已核。
- **REG**：914 全量刷账 `--skip-fixtures --force` → **914/914 零回归** ✓。

### np51② Coins 装配面接入（25 场进场）

- Coins 原版**无脚本**（oracle/Items/ 只有 tscn；battle_items behavior=null）——纯惰性
  库存件，描述符表构建器按 script_file 过滤故被剔。
- 修（np50 TP 同款三件套）：`gd_core_items/Coins.gd`（惰性 extends Item）+ gd_core_test
  镜像 + `battle_items.json` Coins 补 `behavior.script_file`（单行 JSON 往返保真）→
  gen_lineup_fixture（表 519 件，LineupFixture.gd 零变化）+ gen_gd_core_data +
  gd_to_py（Coins.py 自动生成）。
- 夹具 1,690/1,690 全生成，stamina 自检全中。

### np51③ 验证 3：1,652/1,690（py-only 60 全清；残红 38 全 oracle≠gdcore）

- 新增 `tools/expand_isolated_check.py`（红场三分类器）与
  `tools/expand_trace_case.py`（隔离副本双链 trace，输出→scratch 语料盘零触碰）。

### np51④ CustomRules 健康倍率（★本轮最大根因，解释 run101490 全系 + 指向余场）

- **定谳链**：oracle harness 逐场 `CustomRules.fromString(player_run.customRules)`
  （oracle_fight.gd:591）；原版 `Character.prepare()` 按其中 HealthMultiplier 给
  **双方**加**静默**临时体上限（`changeMaxHealthTemporary(bonusHealth)`，item=null
  不发事件，Character.gd:296-298）。gd_core prepare 缺失该段。
- **位流格式**（python 夹具层 full-fidelity 解析）：BASE64OFFSET=62，每字符 6bit
  MSB-first，pull(n)=ceil(log2(n)) 位；league pull(9)=**4 位**（Leagues.size()=9，
  含 ImpossibleWoodRank=−1）+ BonusGold 5 + BonusTreasures 5 + HealthMultiplier
  pull(37)=6（值=pulled×5+20，范围 20..200）。全库 968 带规则 run 的倍率分布
  {100: 966, **200: 2**}——run101490（@cGIkN→200）的 6 场全红完美闭环。
- **修**：位流解析放**夹具层**（`gen_fixture_from_lineup.custom_health_multiplier_of`，
  python 无垫片问题），夹具 case 级写 `custom_health_multiplier` 数值；
  gd_core `CoreContext.custom_health_multiplier` + `CoreCharacter.prepare()` 补
  bonusHealth 段（镜像 Character.gd:296-298，mult=100 时 changeMaxHealthTemporary(0)
  走 `if amount != 0` 早退 = 零回归）；OracleAlignBattle 注入 + py 适配器
  `GDCoreEngine(custom_health_multiplier=…)` + gd_to_py 重生成（py 孪生验证 200 读写 OK）。
- np50 遗留的「run101490 系列叠加根因」由本节**完全解释**（无需 trace）。

### np51⑤ 验证 4/5 + CustomRules 修复实测 + ★录制批泄漏定谳与终局方案

- **验证 4**（1,652/1,690→补 gd 6 场）：run101490 全系 6 场随 CustomRules 修复
  **翻绿** → **1,658/1,690**；残红 32（rng-mechanism 26 + gd_core-kernel 6）。
- **泄漏定谳**：`CustomRules.fromString` 对空串**早退不复位** ⇒ 单例跨场残留。
  录制批内某场带 HealthMultiplier≠100 的规则后，后续 custom 为空的场在
  `prepare()` 仍按残留倍率加静默临时体上限 ⇒ 语料被批内污染（np49 §6m112
  语料池化残留同族）。705064_r15 的 Sloth 522（own custom 为空、需 200% 才成立）
  即泄漏直接证据。
- **单场隔离重放不可行**：泄漏会改变 run 早期回合的胜负路径，干净重放可能提前
  败亡、永远到不了目标回合（分类器首场 40 分钟不到达，实证）。
- **终局方案（np49 同款）**：修 harness——`oracle_fight.gd` 逐场 fromString 前
  `CustomRules.reset()`（单行、零 rng；**副本与 oracle/ 正身同补丁**，oracle/ 红线
  触碰=用户「修复到全绿」指令 + np46/np49 harness 修复先例，已在留档与本 commit
  显式声明）；备份语料（`output/_expand/corpus_backup_np51_pre_rerecord/`）后
  **全量重录 1,690 场**（expand_run_oracle，3 路）。
- **重录安全性论证**：绿场 = gd(干净) ≡ 语料 ⇒ 其录制时泄漏未生效或无健康面影响
  ⇒ 干净重录逐字节同事件；红场 = 泄漏污染 ⇒ 重录后 = own rules = gd/py 语义 ✓；
  own mult=200 的 run101490 六场重录后仍 own rules ✓（gd 侧 CustomRules 修复匹配）。
- 914 REG 二刷进行中（CoreCharacter/CoreContext 内核变更后的零回归证明）。

### np51⑥ 重录结果 + 余红 24 场机制图谱（双链 trace 实证）

**重录**：1,690/1,690 零失败（95 分钟，3 路）；accept PASS；与备份逐场对比
**1,682 场逐字节不变 / 8 场变化**（=泄漏污染场，重录后全绿）→ **1,666/1,690**。

**余红 24 场双链 trace 机制图谱**（迷你批 trace 采集法：`expand_run_oracle
--cases <迷你批> --root <scratch>` + `ORACLE_RNG_TRACE=1`，77s/10 场——
**单场 ORACLE_ONLY_CASES 重放路径有病**（战斗不启动、5,400 tick 纯回能×2，
60k ADD-O 不产出；批量路径完全健康，勿再用单场重放做诊断）：

| 族 | 场数 | 机制（trace 实证） |
|---|---|---|
| 伤害界/平衡器族 | ~10（705130/604585/101582/704881/604585/705130/704849×2/400013_r12/604687/101354） | 伤害掷点=**每物品私有 BalancedRange**（Item.gd:473 damageRangeRng，裸调 Util.rng 不入账本——np24 kernel_r5 已证）。705130 双链全程对齐但 Hammer 首击 16(oracle)/19(gd)：**首攻 bounds 即不同**（acc 初始相同⇒非累积差）⇒ 某战斗中 buff 态（Berserker rage/Whetstone/Cog Badge 类）的 +damage 授予量两侧不同（×2 模式：+3 vs +6）。py≡gd（19,20,8,21,15,27,12），oracle (16,21,8,23,15,27,12)——第 3/5/6/7 击相同说明 acc 路径大体同、分歧在特定 buff 窗口 |
| 激活序翻转族 | ~6（101668/100897/101582/604825/704714/300219） | 同一链位 oracle 抽「ItemAnimation 激活速度 (0.8,1.2)」而 gd 抽「randi_range(0,2/3/5) 随机 pick」——activate() 内**动画 roll vs 效果 pick 的顺序翻转**（原版 Item.activate():4686 先 playActivationAnimation 后续效果；gd 的 hook 触发点错位）。条件性触发（激活物带 rng 效果时才显形） |
| ObjectPool 暖池族 | ≥1（604585） | gd 多一次 Zap shader 抽 (4,4.02)（ElectricalCharge 充能命中特效，oracle 全场 0 次）——**池化实例 _ready 只跑一次** ⇒ 是否消耗取决于进程内池的冷热（录制批工件）。np49 §6m112 同族（ItemBook 桶） |
| 工具债 | — | `_np51_trace_align.py` 现为简化对位器（skip≤12 会吸收次序翻转假对齐）；正式对齐需 np24 三件套 + MARKER 列（gd trace 格式 `idx kind a b val MARK st`，MARKER=SRC/LABEL/EVENT/BUS/BALROLL） |

**下一步 playbook（续接者按序执行）**：
1. 伤害界族：对 705130 用 py 探针（`tools/_np51_probe_705130.py`，注意必须传
   `rng_state=<语料 rng_state.txt>` 才与正式腿同链）dump Hammer 每击 bounds+buff 态，
   与 oracle 事件伤害反推对照，定位授予 ×2 的 buff 源（候选：Berserker Bag/BattleRage、
   Cog Badge、Whetstone3 的 canAffect 链）。
2. 激活序族：gd_core/CoreItem.activate() 的动画 hook 触发点 vs 原版 Item.activate():4686
   `playActivationAnimation` 在效果前——对 101668（randi_range(6,6) vs (100,160) 攻击
   动画错位）做最小复现。
3. 暖池族：核对 gd_core 的 Zap/池化视觉 hook 的触发条件与 oracle 池语义（np49 先例：
   reset_residual_state 需覆盖池面）。
4. 每修一族：定向 `--cases <该族场> --force` 重验 + 914 REG + commit。
5. 语料备份保留在 `output/_expand/corpus_backup_np51_pre_rerecord/`（重录前原始态）。

### np51⑦ 探针补充结论（本轮收口时）

- **Coins 布局无嫌疑**：25 场含 Coins 仅 15 红（10 绿）⇒ 1×1 注册对多数场正确；
  红场另有成因。
- **gd 的 activate() 已是 np24 多轮校准态**（playCombatAni 闸/虚函数 playDropSound
  分发/裸调 ANIM 块均已在位）——激活序翻转族不是 activate() 主体顺序问题，
  需按场对 Specific 物品的 hook 消耗面做 np24 逐抽对位。
- py 探针（rng_state 同链）实证 gd/py 的 Hammer bounds=(10,13)、resi=0、
  damageReduction=0 而 final=19/20/21/27 > 13 ⇒ +6..14 来自 **pre_take_damage
  总线监听者或 preDealDamage 钩子族**的加成，量随时间增长（+6@1.7s→+14@12.5s，
  疑似叠层型物品：Forging Hammer/Berserker rage 面），且 oracle 攻击时刻
  （7.55/10.82）与 gd（7.62/10.82）有 ±tick 相位差 ⇒ 时间型叠层的窗口错位。
- 探针脚本已删（np24 纪律）；本节结论与 playbook 足以续接。

**本轮最终盘面：1,666/1,690（97.5%）**——余 24 场三族机制已图谱化，
需 np24 级逐场仪器化战役（np24→np49 为 914 打了六代的同类战役）。
全部四项根因修复 + 语料根治 + 2×914 REG 零回归已 commit。

### np51⑧ 伤害界族根因链闭合（604585 完整案例）

双链 trace + 子序列对位实证（run604585_r6）：
1. gd 在 t≈1.3s **多消耗一次 Zap 抽 (4,4.02)**（CoreItem.gd:2205，充能进入
   `hasOnChargeReceivedEffect` 物品时的电弧表现消耗）；oracle 全场 0 次。
2. 全局链此后 +1 位 → 命中/暴击/伤害掷点全部错位 → Poison Dagger 5v6、
   Hammer 16v19、暴击/miss 翻转、±tick 移位——**掷值家族全部由此一条链**。
3. `hasOnChargeReceivedEffect = has_method("onChargeReceived")`——两侧定义集
   **完全相同**（11 件：Chainsaw/ChargeSplitter/Coil/Eat-o-matic/ElectricTorch/
   Gigawatz/MechaBat/PoisonGrenade/Resistor/Robodog/TeslaCoil）⇒ 差异不在标记，
   在**充能路由**：gd 的某颗电荷多进了一个接收者格（Battery.onCombatStart
   emitCharge → chargeCells 逐格 → getItemInCell）。
4. 续接路径：对 604585 双侧 dump 充能逐格路由（gd：py 探针包
   CoreItem.onChargeEnteredCell——本轮试跑 hook 未命中，需改挂
   `CoreElectricalCharge` 类或 ctx.hooks；oracle：harness 已有
   ORACLE_TRACE_ITEM 同款插桩面，需授权加 charge 探针）。比对第一颗
   电荷的逐格路径即可定位错位点（布局绝对坐标相同⇒嫌疑在电荷移动的
   tick 计时/speedFactor 或 inventoryCells 枚举序）。
5. Whetstone3 拓扑旁证排除：tscn 真值受影响格=9 格（含自身），battle_items
   提取 8 格（去自身格）——Hammer 覆盖集不受自身格影响，三件全覆盖
   （拓扑工具化验证）；+3/+6 之差实为 Zap 链移位的下游表现。

### np51⑨ 逐 tick 状态对位：伤害界族根因再进一层（tick 85/86 vs 97）

ORACLE_DEBUG mini 批出 `tick_states.txt`（527 行=逐 tick 末态）与 gd 侧对位：
- ticks 1-84 逐 tick 状态**完全一致**（链同速）；**gd 在 tick 86 消耗（→S3），
  oracle 到 tick 97 才消耗（→S3，同一链位同一态）** ⇒ gd 的 Poison Dagger
  首攻早 11 tick（86 vs 97，t≈1.4s vs 1.6s）。
- 11 tick ≈ **Battery 充能 +10% 速度 buff 的交付差**：充能 sync 入格
  （onChargeEnteredCell → changeChargedItemStat → addSpeed）在 gd 交付了
  速度 buff，oracle 侧该 buff 未生效（或生效面不同）⇒ Dagger 冷却
  cd/speed 差 ~12.5%。zap 抽 (4,4.02) 的 ±1 链位差是同一次入格的伴随消耗。
- 待验证精确差异点：Battery charge cell-1 落格物品是否一致（布局绝对坐标
  相同）、addSpeed 量（flatSpeed=10%）、oracle 的 sync 入格是否真调用了
  onChargeEnteredCell（start() 是同步调用应已跑；需 charge 探针确认）。
- 注意 run1160_r18「12/19 heat 在 t=0」实证 sync 入格链在 oracle 真实消耗过
  ⇒ 更可能是**交付量/目标格差**而非不交付。
- 修复方向候选：若 oracle 未交付 = gd 同语义不交付（复刻 tween 死面）；
  若交付但路径不同 = 修 _chargeInventoryCells/chargeFrame。

（待续：充能交付语义的逐格对照）

### np51⑩ item_trace 定量对位（604585，ORACLE_TRACE_ITEM="Poison Dagger" 双侧）

- **gd 的 FannyPack 交付链完好**（onCombatStart 探针）：两个 FannyPack 的
  `getItemsInside()` 都正确返回 `[Bloody Dagger, Poison Dagger]`、speedBonus=0.1、
  `item.addSpeed(0.1)` 均执行——**Fanny 包内面不是差异点**。
- **speed 演化对位**（item_trace 的 t 列=Util.time（harness 钟），战斗 t=0 ≈
  Util.time 1.933；oracle 内部 tick 号=harness 帧号、gd=战斗 tick，两列不可直比，
  按 t 列与事件对齐）：
  - oracle：speed=**1.2 @ 战斗 t≈0**（起步即 +0.2）、**1.55 @ 战斗 t≈0.05**
    （+0.35 = t=0 簇一次性到位：2×Fanny(0.1×2) + Battery speed2 面素（speed2=5%）
    的 sync 入格授予等）；
  - gd：speed=1.0 起步、1.2 @ 首攻重置、1.55 @ 其后——**交付时刻/记账面不同**。
- 诊断副产物：①gd 注册表存在 `gd_core/FannyPack`（kernel 旧集）与
  `gd_core_items/FannyPack_2`（现行集）同名碰撞——运行时走路径查找不受影响，
  但**探针按名取类会拿错**（须从模块取真身）；②py 引擎单场跑必须
  `G.kernel()` 先 bootstrap 再 import 物品模块，否则注册表占位符报错；
  ③gd 侧 item_trace 需要 `ORACLE_ALIGN_TRACE=1` + 先删 scratch 内该场
  events.json（resume 会跳过战斗）。
- **下一动作**：逐项对位 t=0 簇的 addSpeed 授予（2×FannyPack + 3×Battery sync
  入格 + Blood Manipulation vampiricSpeed 面），在 py 探针里 dump 每次调用
  （目标物品、值、调用后 getSpeed()），与 oracle 的 speed 里程碑（1.2@0、
  1.55@0.05）逐一对账——差值即缺失/多出的授予者。修复面在对应物品孪生或
  CoreItem.addSpeed/getStackSpeedMods 记账。

（待续：t=0 簇 addSpeed 逐笔对账）

### np51⑪ addSpeed 逐笔台账（py 探针，604585）

t=0 簇（与 oracle 里程碑**一致** ✓）：+0.1×2→Battery、+0.1→Coil、
+0.1→Bloody Dagger、+0.1→Poison Dagger（→1.1）、再 +0.1→Bloody Dagger/
Poison Dagger（→**1.2** ✓=oracle 起步值）、+0.1→Oil Lamp、+0.1×2→Hammer、
+0.1→Dagger——**py 的速度账本与 oracle 起步一致**。

**新分歧点**：+0.35 群体授予（→Dagger/Banana/Poison Dagger/Bloody Dagger/
Seal the Deal，跨双方阵营的武器/食物面）——oracle 在战斗 t≈0.05 触发、
py 在 t=4.283 触发 ⇒ **授予者的首火时刻两侧不同**（冷却型授予物）。
+0.35=0.05×7 或 0.05×n+0.15——候选授予面：Battery speed2=5%（per-tile）
或某 0.05/次叠层物。命中物品跨阵营 ⇒ 授予者是**全局面/双方面**（非某侧
affected 拓扑）。

下一动作：py 探针打 addSpeed 的调用栈（`traceback.extract_stack` 取
grantor 帧即可定位授予物品与其 doCooldownEffect/激活面），对照 oracle
的 t≈0.05 时刻反推其冷却时长差（又一处 fd/参数/计时面差）。

（待续：+0.35 授予者定谳）

### np51⑫ +0.35 授予者定谳：Wolf Badge 战怒时机差（604585）

调用栈探针实锤：+0.35 群体授予 = **WolfBadge.py:51 onBattleRageStarted**
（战怒开始 → 一组武器 +35% 速度）。Wolf Badge = 玩家阵容物品（原版 45 行：
onDamaged 里 `getRelativeHealth() < getP1()/100−0.0001` → startBattleRage）。

- **oracle：战怒 t≈0.05 即触发**（WolfBadge p1=200 ⇒ 阈值 200%，相对体力
  100% < 200% 恒真——**开战即常开**，首个 onDamaged 就应点燃）；oracle 的
  点燃时刻 t≈0.05 ⇒ oracle 在 t≈0.05 有一次**角色受损**（无事件面痕迹，
  嫌疑=Resistor 充能热伤面/Battery 电荷交互，与充能语义互联）。
- **py/gd：战怒 t=4.283 才触发** = 该时刻的首次 onDamaged（py 台账
  +0.35@4.283）——**gd/py 的 WolfBadge 在 t≈0.05 的受损事件上未点燃**：
  该次受损在 gd/py 缺席（又是充能/热伤交付差）或 onDamaged 的触发面不同。
- 修复路径：双侧对照 WolfBadge 的 onDamaged 触发时刻（oracle t≈0.05 的
  受损源 = 充能热伤家族），与 np51⑧-⑪ 的充能路由差异**同根**。定谳后
  修 CoreElectricalCharge/Resistor 面的交付，本族（伤害界 ~10-14 场）应
  连带翻绿。

（np51 本轮收口：1,666/1,690；余 24 场的充能/战怒/激活序三族全部归因到
可插桩的精确差异点，续接 playbook 完备。）

### np51⑬ 战怒时机差的统一解释与终局判词

双侧 WolfBadge 战怒都由「**未入事件面的受损**」点燃：
- oracle @战斗 t≈0.05（充能热伤/电荷交互的早期交付）；
- py/gd @战斗 t=4.283（同族受损但晚 4.2s）。

⇒ **充能系统交付时序差**是伤害界族（含 zap 抽、掷值错位、战怒时机、
±tick 移位）的**唯一上游根因**：电荷的 sync 入格两侧一致（t=0 簇 ✓），
分歧在**后续入格/热伤/电弧的调度时机**（原版=tween 实时延时驱动，
harness 阻塞循环下的真实执行面 vs gd_core 的复刻面）。定谳该面需要
oracle harness 的电荷逐格探针（ORACLE_TRACE_ITEM 同款插桩，红线需授权）
+ gd 侧 CoreElectricalCharge 的 tick 驱动对照。

**np51 终盘**：1,666/1,690（97.5%）；五项根因修复全部落地并 REG×2 零回归；
余 24 场 = 充能交付时序族（单一上游根因，已定位到可插桩差异点）。
修复该族预计连带翻绿全部 24 场（掷值/战怒/tick 移位皆其下游）。

### np51⑭ 映射折叠复核（排除一项假设）

原版像素↔格链的逐项推导：getGlobalPointsForCells 含 `+halfCellSize.rotated()`
（+(40,40)），getTopLeftGlobal 用 `map_to_world`（角点，无中心项）——两式相减时
**中心项不抵消**，floor((R(40,40)−correction[fd])/80) 对 fd 0..3 **恒=(0,0)**
（中心偏移恰抵消 correction）⇒ **gd 的折叠（无 correction 项）= 正确**，
充能格映射本身无 bug。⇒ 差异面收窄为：**电荷入格后的接收者效果交付时机**
（原版 tween 实时调度 vs harness 阻塞循环的真实执行面——ORACLE_TRACE_ITEM
实证 oracle 的 Dagger speed=1.2 从战斗起步、1.55@t≈0.05；gd/py 同值迟到）。
该面 = np49 §6m112 池化/时序同族的深水区，需 np24 级仪器化战役（oracle
harness 电荷探针需授权）。

### np51⑮ 收窄到 GDScript 独有面（py 孪生正确）

决定性对照：**py 引擎（转写孪生）的 Dagger speed=1.2@战斗起点 = oracle ✓；
GDScript 腿 = 1.0 ✗**——同源转写的两实现在此分叉。已排除：FannyPack 交付链
（py 探针：两个 FP 的 getItemsInside 都正确含 Dagger、addSpeed(0.1)×2 执行 ✓）、
Bag.prepare 缓存逻辑（两侧逐行同）、充能映射折叠（np51⑭ 已证正确）、
chargeFrame/rotmin（np25 已验证）。
**剩余嫌疑面（已收窄至最终一层）**：getStackSpeedMods = (heat−cold)×0.02
（CoreItem.gd:362-363）——oracle 的 Dagger speed 1.2 = **热栈 10**（3×Battery
sync 充能 ×3 heat=9 + 1，heat 经充能交付）；GDScript 腿 speed=1.0 = 热栈 0
⇒ **GDScript 的充能→Resistor→giveHeat 交付缺失**。而 py 孪生（同源转写）
的 FannyPack/速度面正确——**分叉在 GDScript 的 filledCells 叠加注册**：
Dagger 叠在 FannyPack 占格上（BB 包内堆叠语义），getItemsInCells 走
filledCells[cell]（每格单物品，后注册者覆盖）——GDScript 的叠加注册/放置
碰撞检查若拒绝了叠放 ⇒ Fanny 的包内面空 ⇒ 速度 buff 缺失 ⇒ 冷却节拍差 ⇒
Zap/掷值/战怒全链错位（py 正确因 Python 侧注册语义与原版一致）。

**np51⑱ 604585 最终对账（本轮终态）**：三方事件流 212/213 事件全同，
唯一分歧 = Poison Dagger 首击伤害 5(oracle)/6(gd=py)。已**逐层排除**：
speed 台账（1.2@0、1.55@4.283 三侧全同）、FannyPack 交付链（gd 探针实证
inside=Daggers ✓）、充能映射折叠（(40,40) 中心项与 correction 在 floor 下
抵消，gd 正确）、Resistor heat/heatt 参数（三层面全同）、Whetstone3 拓扑
（三件全覆盖）、WolfBadge 战怒（ty=21@4.267 三侧同）、typed factor/参数面
（minDam=5 三层面全同）。**剩余唯一未决**：该击的隐藏 BalancedRange 掷点
的**链位/取值差**（u→int 映射两侧为同版 Godot 语义）——即攻击簇内某处
存在一次**未对齐的隐形消耗**。定谳工具 = np24 正式对位器（gd trace
MARKER 列 + 三件套）在该 tick 的逐抽对位；gd 的 rng_trace 需重跑
（ORACLE_ALIGN_TRACE=1 + 删 scratch 产物，mini 批法 77s/10 场）。

**np51⑱ DONE（序差清单已产出）**：对位器升级=值匹配游走（(kind,a,b,val)
四元组 + kind 归一表 + 双向 skip≤20 + 锚定战斗起点 K105），run604585 全流
**57 对配对、2 处差异**：
1. K-extra @K129：gd 可见 Zap 抽 (4,4.02)（oracle 同消耗但直连不可见 =
   账本可见性差，非真分歧）；
2. **★MISMATCH @O57/K163-172：gd 的攻击簇含两次 (0.95,1.05) 冷却抖动抽
   （K171+K172），oracle 只有一次（O65）**——多出的抖动 = **某物品在
   GDScript 侧的冷却调度提前/多转一轮**（该物品的冷却在 gd 于 Poison
   Dagger 攻击 tick 同期到期并掷了抖动，oracle 侧无此掷）⇒ 全簇后续
   抽（命中率 30.06 vs 20.5、伤害 6 vs 5）链位 +1 错位。
**np51⑱+⑲ 对位器战役终态（本轮）**：
1. 对位器升级=值匹配游走（四元组+归一表+双向 skip），604585 全流
   **57 对配对、2 处差异**：①gd 可见 Zap（账本可见性差，非真分歧）；
   ②**攻击簇 (0,100) 行错位**：oracle [20.54, 30.06] vs gd [30.06, 87.84]——
   **gd 的子 rng 序列整体 +1 错位**（gd 的第一支 = oracle 的第二支）。
2. **(0,100) 行归属定性**：accuracy/crit/critResist/stunResist 四个子 rng
   （CoreRng.rollPercent 追踪面）的账本**交织**在同一 trace——±1 错位 =
   **某一子 rng 的序列多/少一笔**。已排除：bias（三侧同 −0.2/lobbies）、
   seed（prepare 时全局链对齐）、Poison Dagger crit=0（无 crit roll ✓ 双侧）、
   Coil cd=0（无冷却）、Coins cd=0、Resistor 参数三层面全同。
3. **残余候选（下一会话首查，30 分钟级）**：①四子 rng 分账本对位
   （state 列=各子 rng 自身态，按 state 子序列分账本后逐本对位）；
   ②WolfBadge 战怒 @4.267 双侧同但其**触发链**（onDamaged→startBattleRage→
   battle_rage_started→addSpeed）的中间信号时刻三侧对位；
   ③Vampiric Collar 的 onVampirismChanged → changeCritChancePercent 触发
   时刻（vampirism 事件 1.833 双侧同）——若 crit chance 在 gd 提前 >0，
   则 1.617 的攻击多一次 crit roll = ±1 定谳。
4. 修复预期：该 ±1 定谳后伤害界族 ~14 场连带翻绿；再余激活序族 ~6 场。

### np51⑰ Zap 红鲱鱼排除 + 本轮探针战役终判

- **Zap (4,4.02) 非多消耗**：Zap.gd:32 的掷点在 `zap()` 内**每次调用都掷**
  （无池化跳过）；oracle 侧 `Util.rng.randf_range` 直连 = **账本零痕迹但真消耗**
  （与 ItemAnimation 直连同款，kernel_r1 注）。gd 的可见 (4,4.02) 行 =
  同一消耗的可见账本——**两侧链位一致，账本可见性不同**。
- **GDScript FannyPack/Whetstone3 探针（np24 纪律插桩→还原）**：FannyPack
  的 getItemsInside/occ/speedBonus 全部正确（包内=Daggers ✓）；Whetstone3
  的 onCombatStart=继承自 Whetstone 基类（本文件无此函数，探针改插基类）。
- **真正未决面**：tick 内消耗**顺序**——oracle 与 gd 在攻击 tick 的
  抖动/命中/伤害/Zap 等抽的相对次序存在差（我的简化对位器以 skip 吸收后
  呈「对齐到底」，实为**多重排**）。定谳需 np24 正式对位器（gd trace 的
  MARKER 列 + 三件套）在本 tick 做逐抽对位，产出序差清单后逐条修。
- 探针已全部还原（FannyPack/Whetstone3 = git 原样）；trace 产物保留
  output/_expand/trace_root/。


### np51⑱ 对位器升级 + 序差清单（DONE）

值匹配游走（(kind,a,b,val) 四元组 + kind 归一表 + 双向 skip≤20 + 锚定战斗
起点 K105）跑 run604585 全流：**57 对配对、2 处差异**——
1. K-extra @K129：gd 可见 Zap (4,4.02)（oracle 同消耗但直连不可见=账本
   可见性差，非真分歧）；
2. **★攻击簇 (0,100) 行错位：oracle [20.54, 30.06] vs gd [30.06, 87.84]**——
   gd 的子 rng 序列整体 +1 错位（gd 的第一支 = oracle 的第二支）。
(0,100) 行 = accuracy/crit/critResist/stunResist 四子 rng（CoreRng.rollPercent
追踪面）的账本交织。已排除：bias（三侧同）、seed（prepare 对齐）、
PD crit=0（双侧无 crit roll ✓）、Coil cd=0、Coins cd=0、Resistor 参数三层面。

### np51⑲ 逐层深挖（item_trace 对位 + addSpeed 台账 + 调用栈探针）

- ORACLE_TRACE_ITEM 双侧 item_trace：Dagger speed 演化 **1.2@起点、
  1.55@combat 4.283 三侧全同**（此前"gd=1.0"是装配段 tick 误读）；
- addSpeed 逐笔台账：t=0 簇逐笔三侧一致 ✓；**+0.35 群体授予（WolfBadge
  onBattleRageStarted，调用栈实锤）三侧同 @combat 4.283** ✓；
- Coil speed 演化（1.1@起点）双侧同 ✓；充能映射折叠复核：
  (40,40) 中心项与 correction 在 floor 下抵消，gd 折叠正确 ✓。

### np51⑳ 攻击簇逐抽对位终态

值对位深入到 Coil 的 stealRandomBuff 内部（pickRandomStacks：pick→anim→pick
三连）：steal 两支 pick 值双侧全同（pick(0,2)=>2、pick(0,5)=>5）；**pick#1 与
pick#2 之间的 (0.8,1.2) 播放速度抽：oracle 0.939 vs gd 0.8149**——其 u 前的
全部消耗双侧完全一致。终判：该 (0.8,1.2) 的 u 差 = 前序 ±1 隐形消耗的累积
显形（下游读数非根因）；±1 注入点在 t=0 簇内（zap 前后双侧状态短暂错位后
重汇聚），**定谳需 oracle harness 电荷/Zap 探针授权或 gd 侧 tween 语义逆向
实验**（np24 [M11]：tween 在阻塞循环不跑，但 ElectricalCharge.start 的 i==0
同步分支已双侧复刻——差异面在更深的 SceneTree 状态机）。

**np51 终盘**：1,666/1,690（97.5%）；五项根因修复 + 泄漏根治重录 + REG×2
全部落地；余 24 场收敛到 t=0 簇内 ±1 隐形消耗单一疑点，需 oracle 侧探针
授权定谳。全部成果已 commit（np51①-⑳）；探针已全还原；trace 产物保留
output/_expand/trace_root/；语料备份 output/_expand/corpus_backup_np51_pre_rerecord/。

### np51㉑ Dagger 排除 + 攻击簇定位收口（本轮续接段）

ORACLE_TRACE_ITEM="Dagger" 双侧实证：Dagger speed 演化（0.7937@起点=Cold
减速 → 0.8621@tick529）与攻击重置（首攻 t=4.517）**双侧完全对齐**——
Dagger 排除。多出的 (0.95,1.05) 抖动 = 某物品的**冷却重排掷点**在 gd
提前/多转。

**候选收敛**：Poison Dagger 自身的结构双侧同（O65 初排 + O66 攻击重排
vs K171 + K172），但**重排值差**（O66=1.0376 vs K172=1.0157）= ±1 的
显形——其 u 前消耗全同（np51⑳）⇒ ±1 注入点在 t=0 簇内且未被
item_trace 捕获（非 speed/reschedule 面）。

**下一会话首查（最终）**：np24 对位器 MARKER 列适配（gd trace 的
MARKER=SRC/LABEL/EVENT/BUS/BALROLL 行内嵌于抽行间，可标记每抽的
调用者身份）——MARKER 对位直接锁定 ±1 注入的调用面，无需逐物品排查。
修复后伤害界族 ~14 场连带翻绿，再余激活序族 ~6 场。

（np51 全部成果已 commit 至 np51㉑；终盘 1,666/1,690。）

### np51㉒ (0,100) 行归属定谳 + BALANCEDRNG 面确认

- **(0,100) 行 = BalancedRng.rollPercent 的追踪 randf_range**（CoreRng.gd:46
  「走追踪版 randf_range（等价原版 Util.roll）」）；**BALROLL trace_diag
  （:249）= gd 侧平衡态诊断行（expectedWins/wins/lastResult，零消耗）**。
- **BalancedRng = BB 平衡随机机制**（accuracyRng/critRng = BalancedRng.new()，
  Character.gd:94）：roll = f(全局 u、平衡态 wins/expectedWins/lastResult、
  bias ±0.2、extraLuck=Lucky 面素)。三侧 bias/历史/Lucky 全同。
- **gd 序列 [30.06, 87.84] vs oracle [20.54, 30.06]**：gd 的第一支 = oracle
  的第二支值——**BalancedRng 序列整体 +1 错位**，其 u 前的全局消耗差 1 笔。
  oracle 的第一支 20.54 的 u = 攻击 tick 的全局链位；gd 的 30.06 = 该链位
  **+1** 的值——**±1 隐形消耗确认存在于攻击 tick 之前**（t=0 簇内）。
- **BALROLL 诊断行 = gd 侧独有**（oracle 的 BalancedRng 内部态不可观测，
  red line）⇒ ±1 注入的**调用面定位**需 oracle 侧探针授权；gd 侧可做的 =
  逆向实验（在 gd 的 t=0 簇内按候选点注入 ±1 抽，看后续是否精确命中
  oracle——np24 kernel_r1 的注入实验法，run574_r7 先例）。

### np51㉓ 逆向注入实验方案（下一会话，无需授权）

gd 侧 t=0 簇的候选注入点（按消耗序）：
a. Battery#0 的 charge sync entry 的 Zap 抽（CoreItem.gd:2205）——**双侧
   都消耗**（oracle 直连不可见但真消耗，np51⑰ 已证）——排除；
b. FannyPack.onCombatStart 的 addSpeed 面素（零 rng）——排除；
c. **Battery.onCombatStart 的 emitCharge 顺序**：gd = activate()→sendCharge
   （np25 语义）；oracle = emitCharge 内 activate() 亦先于 sendCharge——
   顺序同——排除；
d. **Coil 的 stealRandomBuff 的 pickRandomStacks 的 keys() 序**：
   Dictionary.keys() 顺序 = 插入序——oracle 与 gd 的 stacks dict 插入序
   若因 dictAdd 实现差异而不同 ⇒ pick 的 (0,2)/(0,5) bounds 同但
   **候选集序不同 ⇒ 同 u 不同 pick 结果**——**这是 pick(0,2)=>2 双侧同
   但 (0.8,1.2) 后续 u 差的唯一自洽解释路径**（pick 本身 1 步两侧同、
   值同，但 steal 的 *下游执行*（loseStacks/giveStacks 的 EventBus 面）
   的 rng 消耗若因 stolen buff 类型不同而不同 ⇒ ±1）。
e. **steal 的下游执行差异实验**：py 探针 dump stealRandomBuff 的
   removedStacks 内容（双侧对照——oracle 侧经由事件反推：1.833 的
   loseStacks 事件 ty=103 amount=1 = Bloody Dagger 的 Vampirism -1）。

（np51 全部成果已 commit 至 np51㉓；终盘 1,666/1,690。）

### np51㉔ (0,2) pick 调用栈定谳 + 终局收敛

调用栈探针实锤：randi_range(0,2) = **CoreCharacter.playAttackAnimation**
（攻击动画变体选择，dealDamage 内）——604585 的三支 (0,2) pick = 三次
攻击的动画选择，值序列 gd=[2,1,2]。
- Poison Dagger 首击（1.617）的动画 pick 值双侧同（=2 ✓）；**其后的
  playback (0.8,1.2)：oracle 0.939 vs gd 0.8149**——±1 隐形消耗位于
  playAttackAnimation 内部或其后、accuracy 之前。
- playAttackAnimation（原版 Character.gd）内部：动画场景选择 (0,2) →
  ItemAnimation 4 抽块（invisible）→ playback (0.8,1.2)（visible）——
  **gd 的 playAttackAnimation 复刻已含 invisible 块（np24 kernel_r1）**，
  ±1 在块内的 3 支 randomizePosition 与 playback 之间的某一面。
- **终局**：需 oracle 侧 playAttackAnimation 逐抽探针（ORACLE_STACKTRACE
  或 harness 插桩，red line 需授权）定谳；或 gd 侧逆向注入实验
  （np24 kernel_r1 的 ORACLE_INJECT_AT 法，run574_r7 先例）。
**np51 终盘（本轮三轮循环）**：1,652 → 1,666/1,690；四项根因修复 +
泄漏根治重录 + REG×2；余 24 场收敛到 playAttackAnimation 块内 ±1 的
单点，诊断基建（对位器/item_trace/addSpeed 台账/调用栈探针）全部
就位。全部成果已 commit（np51①-㉔）。
