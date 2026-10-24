# np10_data · 配方类继承补丁落库（轮10，2026-10-20，np9_L2 定谳的最小数据面修）

## 结论（一句话）

np9_L2 定谳的配方类继承（calcClassAvailability）不动点已落库：`assets/battle_items.json`
恰 **25 件** `classes` 由 0 折算为非零（真实增量 25 行，逐字段核对零其他漂移），GP 四场
涉及的 4 件全部精确命中（Strong Vampiric Potion=2、Steel Dragon=4、Whetstone3=4、
Vampiric Collar=1）；三张派生表（gd_core_runtime.json / item_battle_fixture.json /
probe 副本）再生后除 classes 外零差异，oracle_align_cases.json 914 场零内容差异；
附带项 r40 `OSError [Errno 22]` 已定谳为**运行器传参尾随控制字符**（本环境实证复现
同签名），并按卡面授权在 `oracle_mode` 入口做了最小剥字符修复+端到端验证。
**验证腿（GP 四场 + REG 九场）按纪律未跑，由脚本统一跑。**

## 一、落库明细

- 路径：只调 `tools/enrich_classes.py::apply_recipe_inheritance`（round3 函数本体，
  `tools/enrich_classes.py:65-124`），**未走 main() 的 CSV 基座重解析分支**（np9_L2
  警示的 231 件爆炸半径未触碰）。驱动：`output/_round_patches/np10_data/apply_inheritance.py`
  （deepcopy 干跑 → 三重断言 → 才写盘；写盘格式复刻现状 indent=2/CRLF/无尾换行，
  对备份逐行 diff 确认零格式漂移）。
- 不动点 1 轮收敛，恰 25 件，与 np9_L2 离线模拟名单逐一吻合：

| classes | 物品 |
|---|---|
| 0→1 | Vampiric Collar、Magic Collar、Holy Collar |
| 0→2 | Strong Vampiric Potion |
| 0→4 | Steel Dragon、Whetstone2、Whetstone3、Chain Whip、Dragonscale Armor、Dragon Claws、Dragonskin Boots、Busted Blade、Armored Courage/Power/Wisdom Puppy、Halberd |
| 0→64 | Cap of Brilliance、Arcane Boots、Thors Hammer、Automanaton、Mananana |
| 0→127 | Vampiric Potion、Coins、Box of Prosperity、Holdall |

- 四件已知值（oracle probe 实测口径）：SVP=2 ✓、Steel Dragon=4 ✓、Whetstone3=4 ✓、
  Vampiric Collar=1 ✓。其余 493 件整 item 全等 ✓（`verify_all.py` 断言）。

## 二、派生表再生

| 表 | 生成器 | 与备份结构化 diff |
|---|---|---|
| `assets/gd_core_runtime.json` | `tools/gen_gd_core_data.py`（PASS，公式对拍 21 探针一致） | 24 处 classes，0 处其他 |
| `gd_core_test/item_battle_fixture.json` | `tools/gen_lineup_fixture.py` | 24 处 classes，0 处其他 |
| `gd_core_test/oracle_align_cases.json` | `verify_oracle.select_cases+gen_fixtures`（同 r40 基线路径） | **0 处**（cases 不嵌 classes），914 场/序同 |
| `gd_core_probe/` 两份副本 | 逐字节拷贝 + cmp | 一致 |

- 24 = 25 − Coins：Coins 无转译脚本，本就不在 517 件可装配表内（生成器输出明示
  「无转译脚本 1 件：Coins」）；Holdall 确在两表且=127 ✓。
- **LineupFixture.gd 连坐增量 = 恰 1 行**：`gen_lineup_fixture.py` 与 fixture 表同进程
  产物，truth lineups 含 Holy Collar → 嵌入描述符 classes 0→1（`gd_core_test/LineupFixture.gd:1208`）。
  用备份回放法（旧 battle_items → 重生成 → 存 .pre → 还原新库 → 重生成）量化证明
  除该行外零差异；该文件不在本卡文件面，系派生连坐，如实留档（回滚若需：
  `output/_round_patches/np10_data/LineupFixture.gd.pre`）。
- **语料漂移（非本补丁造成，留档上报）**：`select_cases(0)` 现返回 **917** 场，基线
  （10-19 生成）为 914；新增 `run626_r6 / run1294_r6 / run1445_r18` 三场。按本卡
  「仍 914 场」口径，再生严格限定基线 914 场集合（保 fights.json 序），三场未并入，
  待后续轮次刷基线时统一吸收。

## 三、r40 `OSError [Errno 22]` 定谳与最小修复

- 现场记录：`output/alignment_fix_log.md:7845-7849`——r40 刷基线时
  `verify_oracle.py:119 gen_fixtures → gen_fixture_from_lineup.py:386 oracle_mode →
  OSError [Errno 22] Invalid argument（gd_core_test\oracle_align_cases.json）`，
  exit=0 与 traceback 并存。
- 机制实证（本环境，`io.open(path,"w",encoding="utf-8",newline="\n")` 同款）：
  路径**尾随 `\r`** → 恰 `[Errno 22] Invalid argument`；反斜杠相对路径经转义被吃
  （`\_`→`_`、`\n`→换行）→ 同样 22；干净路径（正/反斜杠、相对/绝对）恒 OK。
  即：**脚本打开方式/拼接本身无缺陷，异常签名指向运行器传入的 batch_out 带了
  控制字符**（CRLF 切分或转义被吃）。
- 同语句健康性证据：本次再生经同一调用路径（gen_fixtures→oracle_mode:386）成功
  写出 43,880,157 B × 2 次（含修复后复跑）。
- exit=0 与 traceback 并存的解释：`verify_oracle.py:927` 对 gen_fixtures 无 try 包裹，
  裸异常必非零退出；r40 走的是运行器侧自行 try/print 的直调形态（r40 系工作流轮次，
  非命令行 main()），exit 码由运行器决定。
- 修复（卡面授权「打开方式/路径拼接」）：`tools/gen_fixture_from_lineup.py::oracle_mode`
  入口对 `lineup_out`/`batch_out` 做 `strip()`（剥尾随 `\r`/空格，clean 路径行为不变）。
- 验证：CLI 形式 `--oracle output/oracle/fights/run569_r11 --lineup-out <scratch>\r
  --batch-out <scratch>probe_cases.json\r` → 修复后 exit=0、1 场生成、JSON 可读
  （修复前按机制实证必抛 22）；修复后基线再生复跑 914 场字节稳定。

## 四、纪律遵守

- `output/oracle/fights/` 与 `oracle/` 只读未动（仅读取 lineups.json/fights.json/events.json）。
- gd 验证腿（GP 四场 run597/608/613/729 + REG 九场）**未跑**，由脚本统一跑；
  判据未放宽。
- `gd_core/`、`gd_core_items/` 零改动（git status 中该 51 项均为会话前既有变更）。
- 未 commit/push，未改 git 历史。
- 改动文件全集：`assets/battle_items.json`（25 行 classes）、`assets/gd_core_runtime.json`、
  `gd_core_test/item_battle_fixture.json`（均再生，仅 classes）、`gd_core_test/LineupFixture.gd`
  （连坐 1 行）、`gd_core_probe/{item_battle_fixture,oracle_align_cases}.json`（同步副本）、
  `tools/gen_fixture_from_lineup.py`（6 行 strip 修复块）。
- 改动前备份（6 表，`output/_round_patches/np10_data/`，`*.bak` 后缀）：
  battle_items / gd_core_runtime / gd_core_test 两夹具 / gd_core_probe 两夹具；
  另存 `LineupFixture.gd.pre`（改前等价重建）、`LineupFixture.gd.new`、
  `battle_items.json.new`（回放中间件）。还原 = `cp <name>.bak <原路径>`。
- 工作脚本（可复跑）：`apply_inheritance.py`（落库）、`regen_oracle_cases.py`（914 场
  再生）、`verify_all.py`（全链终验）、`scratch/`（OSError 修复验证产物）。

## 五、验收移交

脚本腿跑 GP 四场（run597_r18/run608_r18/run613_r18/run729_r14）预期：oracle 与 gd
的 GP 首激活时点因 nAff 2→3、3→4、2→4、5→6 而前移对齐（np9_L2 §2 时序自洽校验的
gd 侧应随之收敛）；如出现**更晚**新分歧，按 np9_L2 §4 属预期内的「真值前移」，
用 `output/oracle/probe/np9_L2/probe_gp_np9.gd` 逐场续查，与 GP 语义无关。
