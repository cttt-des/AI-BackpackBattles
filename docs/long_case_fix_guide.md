# 长场修复工具交接文档（long_case_fix.py）

> 写给接手长场修复的 agent。**先读完全文再动手**，这里有 5 个坑会让你白跑几小时。
>
> 生成：2026-11-05　适用：语料 914 场中被排除在夹具外的 54 场长场

---

## 1. 这个工具解决什么问题

语料有 914 场，但主夹具（`gd_core_test/oracle_align_cases.json`）只有 **860 场**。
差的 **54 场**是事件数爆炸、跑得慢的那批，被主动排除在每轮都要跑的主回路之外：

| 指标 | 54 场长场 |
|---|---|
| 体积 | 合计 372.7 MB，中位 6.6 MB，最大 **18.4 MB**（run894_r18） |
| 事件 | 合计 953,425 事件，最大 **48,297**（run894_r18） |
| 单场耗时 | 27–136 秒（主回路普通场只要 1–2 秒） |
| 当前状态 | **从未被验证过（覆盖空洞）** |

把它们塞回 `verify_oracle.py` 会把每轮迭代从分钟级拖到小时级，所以必须独立。

```
python -X utf8 tools/long_case_fix.py --list            # 1) 诊断：这 54 场是谁、多大
python -X utf8 tools/long_case_fix.py --prepare         # 2) 生成长场专属夹具（不动主夹具）
python -X utf8 tools/long_case_fix.py --focus <case>    # 3) 单场深挖：跑 gd+py，打印首分歧
python -X utf8 tools/long_case_fix.py --prefix <case>   # 4) 前缀重放：修复迭代主入口（秒级）
python -X utf8 tools/long_case_fix.py --run             # 5) 批量三腿验证（54 场全跑）
python -X utf8 tools/long_case_fix.py --report          # 6) 汇总：按分歧类型聚类
```

---

## 2. 架构：为什么完全不碰原工具

主人明确要求：**不要改原来的对拍工具**。所以本工具只新增、不改动：

| 事项 | 原工具 | 长场工具 |
|---|---|---|
| 重放脚本 | `gd_core_test/OracleAlignBattle.gd`（未改一字） | 新增副本 `OracleAlignBattleLong.gd` |
| 对拍驱动 | `tools/verify_oracle.py`（未改一字） | 只调用其函数，配置用 `_LongContext` 临时接管 |
| 夹具 | `gd_core_test/oracle_align_cases.json`（860 场） | `output/oracle/align_long/long_cases_fixture.json`（54 场） |
| 产物 | `output/oracle/align/` | `output/oracle/align_long/`（完全隔离） |
| 报告 | `output/oracle/alignment.json`（860 场基线，别碰） | `output/oracle/long_alignment.json` |

### 2.1 OracleAlignBattleLong.gd 加的两个开关

它是 `OracleAlignBattle.gd` 的逐字副本（1365 行）+ 两处小改：

| 环境变量 | 作用 | 为什么必须有 |
|---|---|---|
| `ORACLE_ALIGN_CASES_FILE` | 指定夹具路径（缺省仍是 `res://oracle_align_cases.json`） | 长场不在主夹具内，又不能改主夹具 |
| `ORACLE_ALIGN_MAX_TICKS` | 前缀重放上限（0/缺省 = 全长） | 只跑到分歧点就停，单场从分钟级降到秒级 |

> ⚠ `OS.get_environment()` **不是常量表达式**，不能写 `const`（GDScript 会报
> `Expected a constant expression`）。必须用 `var` 在 tick 循环前就地求值。

### 2.2 _LongContext 做什么

`verify_oracle.run_py` 读的是模块级全局（`V.CASES_JSON`、`V.PY_NP22_REC_EV_GATE`、
`V.GD_OUT`、`V.PY_OUT`）。长场工具用 `with _LongContext(...)` 临时换掉这些值，
退出时无条件还原：

```python
with _LongContext(GD_OUT, PY_OUT, fixture):
    V.run_py([fixture[cid]])   # 这里看到的是长场口径
# 出了 with，V 的一切恢复原状 —— 主流程零影响
```

---

## 3. 核心提速机制：前缀重放（--prefix）

### 3.1 原理

长场跑满 27–136 秒，但首分歧往往在很前面（几百~几千个事件）。修复一轮只需要
回答一个问题：**分歧位置有没有前移**。所以：

```
第 1 轮：全量跑一次 -> 记下首分歧 idx（写入账本 progress.json）
第 2 轮起：重放上限压到「上次分歧 idx + margin 事件」对应的 tick -> 秒级
```

实测（run906_r18，30538 事件）：全量单场仿真 9.9 s → 前缀 312 tick 只要 **0.6 s**。

### 3.2 判据（四种结局）

| 结局 | 含义 | 该怎么做 |
|---|---|---|
| 前移（new_idx < 上次） | 这轮修改有效 | 继续下一轮 |
| 同位置 | 修改没影响这条路径 | 换假设 |
| 后移（new_idx > 上次） | **退步！** | **立刻回滚**，别叠加 |
| 覆盖不足 | 前缀太短，没越过上次分歧点 | 加大 `--margin` 重跑 |

### 3.3 ⚠ 坑 1：--margin 是事件数不是 tick

长场前期事件稀疏：180 tick 里可能只有 6 个事件。按 tick 加余量会算出「前缀比分歧点还短」，
于是「前 N 个事件全等」——什么也没证明，却会误读成「修复有效」。**实测踩过这个坑。**

工具现在会拦这种情况，报 `⚠ 覆盖不足` 并返回 `rc=2`。看到它就把 `--margin` 加大。

---

## 4. ⚠ 坑 2：py 腿的事件闸（最重要，否则全是伪分歧）

py 引擎有事件闸 `formal_ev_gate`，默认 **25000**，超过就截断。
54 场里有 **9 场**语料事件数超过 25000：

```
run894_r18 48297   run1374_r18 37068   run905_r18 33819   run906_r18 30538
run696_r18 28977   run685_r18  28295   run845_r18 27626   run1409_r18 26640
run1408_r18 26269   （其余 45 场 <= 25000，默认闸即可）
```

**这 9 场若用默认闸跑 py，会被截断 → 事件数少于语料 → 报伪分歧，你会去修不存在的 bug。**

解法：`--prepare` 时逐场算好闸值内联进夹具（`py_ev_gate = max(25000, ev*1.2+1)`），
`_LongContext` 再把它们注入 `V.PY_NP22_REC_EV_GATE`。**不需要手工维护表。**

> 注意：gd 重放侧没有事件闸，只有 `MAX_TICKS=5400`。
> 所以「gd 有 30538 事件、py 只有 25000」这种差异，第一嫌疑就是闸没抬。

---

## 5. ⚠ 坑 3：启动成本（别一场一进程）

`oracle` 项目启动要扫 **15419 个文件 ≈ 25 秒**。所以：

| 做法 | 实测 |
|---|---|
| 一进程跑 4 场 | 23.0 s |
| 每场一进程（折合 4 场） | 96.8 s（**4.2x 更差**） |

故 `--run` 默认 `--batch 4`，并行度由 `gh.effective_jobs` 按「每片至少 4 场」把关。
**不要为了更快把 batch 调到 1。**

---

## 6. ⚠ 坑 4：分片清单必须真的下发

gd 腿只跑本片靠 `ORACLE_ALIGN_CASES`。历史上出过 bug：变量没下发，5 个分片
**各跑全量 860 场**，并行度 5 收益 0（详见 `docs/parallel_workflow.md`）。
本工具在每处 `env_extra` 都显式带了这个变量，改动时别删。

---

## 7. ⚠ 坑 5：改 GDScript 别用会截断的写法

2026-11-05 发生过一次事故：用 `read` 读完再整文件 `write`，但 `read` **有隐式字节上限**
（1365 行的文件只返回了 849 行），把 `OracleAlignBattle.gd` 截断了 516 行。

规矩：

1. 改 `.gd` 只许用 `edit`（精确字符串替换），**不要 read 全文再 write**；
2. 万不得已要整写，必须分块读（`offset`/`limit` 循环）并核对总行数；
3. 改完立刻比对：`git hash-object <file>` 与 `git rev-parse HEAD:<file>`。

---

## 8. 产物与账本

```
output/oracle/align_long/
├── long_cases_fixture.json    长场夹具（54 场，含 py_ev_gate）
├── gdcore/<case>/events.json  gd 腿产物（全量）
├── py/<case>/events.json      py 腿产物
├── prefix/<case>/events.json  前缀重放产物（只是前缀，不能当完整产物用）
├── lineups/                   长场阵容
└── progress.json              迭代账本：每场首分歧 idx / 轮次 / 耗时

output/oracle/long_cases.json      清单 + 规模元数据
output/oracle/long_alignment.json  长场报告（独立于 alignment.json）
```

> `progress.json` 是跨轮状态，别随手删——删了下一轮会退回全量重放。
> 想强制重新定位用 `--force-full`。

---

## 9. 典型修复流程

```bash
# 0) 一次性准备
python -X utf8 tools/long_case_fix.py --list       # 看 54 场清单，挑目标
python -X utf8 tools/long_case_fix.py --prepare    # 生成夹具（54 场 / 0 失败 / 2437 件物品）

# 1) 定位：跑一场，看分歧在哪
python -X utf8 tools/long_case_fix.py --focus run906_r18
#   输出示例：gdcore≡oracle 但 py 分歧，首分歧 idx=6，
#             gdcore 造成 11 点伤害 / py 造成 12 点伤害

# 2) 改代码（看分歧在哪一侧：gd_core / gd_core_py）

# 3) 迭代：每轮只看「分歧有没有前移」
python -X utf8 tools/long_case_fix.py --prefix run906_r18
#   首轮：全量定位并记账（记 idx）
#   之后：只跑前缀，秒级返回 前移 / 退步

# 4) 收敛后跑全量验收
python -X utf8 tools/long_case_fix.py --run --force
python -X utf8 tools/long_case_fix.py --report
```

---

## 10. 当前已知状态（2026-11-05）

只深挖过 1 场，**54 场整体还没跑过**：

| 场次 | 结果 | 首分歧 |
|---|---|---|
| `run906_r18` | `gdcore≡oracle`，**py 分歧** | idx=6，gdcore 11 伤害 / py 12 伤害（荷包蛋圣锅） |
| 其余 53 场 | **未验证** | — |

接手建议顺序：

1. 先 `--run` 跑一遍拿到全貌（约 40–60 分钟，`--batch 4` + 自动并行度）；
2. 看 `--report` 的聚类，**从最大的簇开始修**；
3. 单场迭代用 `--prefix`（秒级），别用 `--focus`（每次都全量）。

---

## 11. 与主流程的关系（务必守住）

| 红线 | 说明 |
|---|---|
| **不许改** `tools/verify_oracle.py` | 主对拍工具，860 场基线靠它 |
| **不许改** `gd_core_test/OracleAlignBattle.gd` | 主重放器；要加开关请改 `OracleAlignBattleLong.gd` |
| **不许动** `output/oracle/alignment.json` | 当前 **859/860**，长场结果另存 `long_alignment.json` |
| 长场修完后 | 是否并入主基线需另行讨论（影响每轮耗时），**不要擅自合并** |

验证主流程没被波及：

```bash
git diff --numstat tools/verify_oracle.py gd_core_test/OracleAlignBattle.gd
# 输出为空 = 两者均未改动（这是本工具的正常状态）
```

---

## 12. 相关文档

| 文档 | 什么时候看 |
|---|---|
| `docs/parallel_workflow.md` | 并行度、启动成本、隐藏桌面/SW_HIDE、沙箱禁管道 |
| `docs/consistency_workflow.md` | 一致性总流程、里程碑定义 |
| `docs/alignment_fix_workflow.md` | 阶段1/阶段2 对齐方法论 |

