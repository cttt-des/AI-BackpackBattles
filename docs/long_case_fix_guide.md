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
| 当前状态 | 部分验证过；其中 **10 场语料是被旧闸截断的**（`winner="-"`），需 `--record` 重录 |

把它们塞回 `verify_oracle.py` 会把每轮迭代从分钟级拖到小时级，所以必须独立。

```
python -X utf8 tools/long_case_fix.py --list            # 1) 诊断：这 54 场是谁、多大
python -X utf8 tools/long_case_fix.py --prepare         # 2) 生成长场专属夹具（不动主夹具）
python -X utf8 tools/long_case_fix.py --focus <case>    # 3) 单场深挖：跑 gd+py，打印首分歧
python -X utf8 tools/long_case_fix.py --prefix <case>   # 4) 前缀重放：修复迭代主入口（秒级）
python -X utf8 tools/long_case_fix.py --run             # 5) 批量三腿验证（54 场全跑）
python -X utf8 tools/long_case_fix.py --report          # 6) 汇总：按分歧类型聚类
python -X utf8 tools/long_case_fix.py --record          # 7) 长场重录（分档+并行+卡死重跑，见 §9）

# --record 的可调项（一般都不用填，全自动）
#   --batch N          每进程几场（0=自动挑最快值，见 §9.7）
#   --jobs N           并行度（0=自动；写死也会被内存闸压住，见 §9.8）
#   --stall-seconds N  卡死判据：日志停滞多少秒算卡死（默认 90，见 §9.4）
#   --max-retries N    单段卡死最多重跑几次（默认 2）
#   --mem-limit-mb N   单进程内存上限（0=按峰值模型 x1.3 自动推导，见 §9.7）
#   --only a,b,c       只重录指定场
#   --all-long         连主夹具内的场也重录
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

## 9. 长场重录（`--record`）

长场语料里有 **10 场是被旧闸截断的**（`winner="-"`），需要重录才能得到自然终局。
`--record` 就是干这个的，并且已经做了两处提速。

### 9.1 用法

```bash
# 重录全部 54 场长场（自动并行 + 分档）
python -X utf8 tools/long_case_fix.py --record --batch 3 --jobs 3

# 只重录指定的几场
python -X utf8 tools/long_case_fix.py --record --only run1015_r18,run1082_r18 --batch 2

# 卡死相关旋钮（见 §9.4）
python -X utf8 tools/long_case_fix.py --record --stall-seconds 90 --max-retries 2
```

### 9.2 提速 ①：分档（53/54 场只跑一遍）

`oracle_fight.gd` 的确定性自证**只对 `cases[0]` 执行**（`:342` 紧邻复跑 + `:355` 批尾复跑）。
所以把 N 场塞进**同一个进程**，只有第 1 场付复跑成本，其余 N−1 场只跑一遍 ——
**不需要改 oracle 任何代码**，只是换个喂法。单场 117s → 60s 的效果从这里来。

### 9.3 提速 ②：并行分桶（LPT）

按**事件数**做 LPT 分桶（事件数是耗时的最好代理），一桶一进程。
54 场游戏时间合计 2543.7s（42.4 分钟单进程下界），4 路并行约 **10.6 分钟**。

⚠ `--batch` **别调大**：`oracle_fight.gd` 的 MessageQueue 只在帧末 flush，
跨场累积会溢出（文档 M11 实测 ~116 场普通场后溢出；长场事件多，故默认 3）。

### 9.4 卡死自动重跑（与 `tools/godot_watchdog.py` 联动）

录制时 Godot 窗口会出现在屏幕上，**用户点一下就会让它未响应卡死**
（实测两次：墙钟 231s/161s，退出码 `0xCFFFFFFF`，`events.json` **0 事件**）。

`--record` 已内置看门狗：**日志文件 90 秒零增长**即判卡死，杀掉该段进程并重跑。

```
正常录制的日志停滞实测序列（秒）：3, 0, 4, 2, 7, 1, 6, 1, 0     <- 最长 7 秒
所以 90 秒阈值有 10 倍余量
```

> 不用 `IsHungAppWindow`：实测正常录制期间它**恒返回 1**（阻塞 tick 循环不处理消息，
> 系统据此就判未响应），是假信号，区分不了「在跑」和「真卡死」。

验证方式（用 `SuspendThread` 挂起 Godot 全部 25 个线程，真实模拟点击）：

```
[破坏者] 挂起 pid=22828 的 25 个线程（模拟点击未响应）
[看门狗] rec0_0 日志停滞 16.0s -> 判卡死，杀掉重跑
段 1/1 rec0_0 rc=0（累计 1 分钟）
[record] 完成：事件数一致 1 / 缺失 0 / 不一致 0
```

### 9.5 产物与安全

```
output/oracle/align_long/record/<case>/events.json   重录产物
```

**绝不覆盖**冻结语料 `output/oracle/fights/`。重录完成后逐场比对 `event_count`，
汇总输出「一致 / 缺失 / 不一致」。要替换语料请**人工确认后再搬**。

### 9.6 已知：截断场会被"跑长"

若某场语料是 `winner="-"`（被旧闸截断），重录会跑到自然终局，事件数**比语料多**。
这是**预期行为**，不是回归。实测 `run1082_r18`：

| | 事件数 | winner | combat_time |
|---|---|---|---|
| 语料（旧闸截断） | 14310 | `-` | 39.9s |
| 重录（现行闸 200000/1200s） | 29418 | opponent | 68.7s |

语料里 `winner` 为空的截断场共 **10 场**，全部在长场 54 场内：

```
run1015_r18 run1080_r18 run1082_r18 run1124_r18 run1125_r18
run1174_r18 run1194_r18 run1219_r18 run1302_r18 run1348_r18
```

### 9.7 内存模型（★ 最重要：跑久了卡顿的根因）

#### 实测数据（2026-11-07）

对比「单场」与「同进程两场」（run1015_r18）：

| 组 | 峰值 | **teardown 后** | 墙钟 |
|---|---|---|---|
| A 单场 | 2751 MB | **1131 MB** | 194s |
| B 两场 | 4434 MB | **1210 MB** | 372s |

**两条结论**：

1. **不是跨场泄漏** —— 结束基线只差 79 MB。`teardown_case()` 里 `_flush_queued()`
   逐树 `free()` 是有效的（源码注释实测「一场拆 ~15 万节点」）。
2. **峰值 ∝ 进程运行时长**：

```
(2751 - 1131) / 194s = 8.35 MB/s
(4434 - 1210) / 372s = 8.67 MB/s      → 取 9 MB/s（偏保守）

模型：peak = 1.1GB + 墙钟 x 9MB/s
校验：A 预计 2872MB / 实测 2751MB（+4%）；B 预计 4474 / 实测 4434（+1%）
```

#### 推论：batch 越大，峰值越高

```
batch=1 -> 约 2.8 GB      batch=2 -> 约 4.5 GB
batch=3 -> 约 6.0 GB      batch=4 -> 约 6.8 GB
```

> ⚠ **这是「跑久了疯狂卡顿」的真因**：4 路 x batch=3 = 24~32 GB，
> 而物理内存只有 15.84 GB —— 必然换页，整机卡死。
> 实测当时的系统状态：占用 96%、可用 0.49 GB、提交区 28.52/32.39 GB。

#### 现在的自动化（2026-11-07 起）

**`--batch` 默认 0 = 自动挑最快值**（按当时可用内存算）：

```
[record] 自动选 batch=2（可用 7.7GB）：预计 2 路 / 约 2 分钟
[record] 最坏段预计墙钟 236s -> 单进程峰值预算 3.17 GB（模型 1.1GB+9MB/s）
[record] 内存上限 4220 MB（= 峰值预算 3.17GB x 1.3 自动推导）
```

为什么必须自动：**最优点随内存变化**（实测）：

| 可用内存 | 最快 batch | 路数 | 预计时长 |
|---|---|---|---|
| 7.5 GB | batch=1 | 2 | 85.9 分钟 |
| 11.0 GB | batch=1 | 3 | 57.2 分钟 |
| 14.0 GB | **batch=4** | 2 | 50.0 分钟 |

内存紧时 **小 batch 才能多开路**，内存松时 **大 batch 摊薄启动/复跑成本**。
这个不该让使用者硬记。

**`--mem-limit-mb` 默认 0 = 按模型 x1.3 自动推导**：超限由看门狗杀掉重跑。

> 踩过的坑：曾经把这值写死 2400MB，结果 batch=2 的段峰值约 3.2GB 被**连杀两次**，
> 白跑 4 分钟。写死的值必然错（batch=1 要 2.8GB、batch=4 要 6.8GB）。

#### 相关常量的位置（`tools/godot_headless.py`）

```python
ORACLE_BASE_MEM_GB = 1.1          # teardown 后的稳定基线
ORACLE_MEM_PER_SEC_GB = 9.0/1024  # 峰值增长速率（GB/秒墙钟）
oracle_job_mem_gb(est_wall_secs)  # 按预计墙钟换算峰值预算
```

> ⚠ 这两个常数是**本机实测值**。换机器（尤其内存/CPU 差异大）要重测：
> 跑一场长场，每 2 秒采 `godot_watchdog._rss_mb(pid)`，反推 `(峰值-基线)/墙钟`。

---

### 9.8 ⚠ 坑 6：显式 --jobs 也会被内存闸压住（特性，不是 bug）

```bash
python -X utf8 tools/long_case_fix.py --record --jobs 4
# [jobs] 请求 4 路，但可用内存仅 0.40 GB（每路预算 2.00 GB）
#        -> 压到 1 路；确实要 4 路请用 force=True
```

过去 `auto_jobs` 在 `requested > 0` 时**直接返回请求值、完全绕过内存闸**，
于是 `--jobs 4` 能把 4 个 1.7~2.8GB 的进程硬塞进 15.84GB 的机器。
现在显式请求也要过闸，被压住时会**打一行说明**（不静默降级）。

**建议：直接不写 `--jobs`**，让它按可用内存自动定。

---

## 9b. 典型修复流程

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

## 10. 当前已知状态（2026-11-06 更新）

### 10.1 修复侧：只深挖过 1 场

| 场次 | 结果 | 首分歧 |
|---|---|---|
| `run906_r18` | `gdcore≡oracle`，**py 分歧** | idx=6，gdcore 11 伤害 / py 12 伤害（荷包蛋圣锅） |
| 其余 53 场 | **未验证** | — |

### 10.2 重录侧：已验证 5 场（含 1 场截断场）

用 `--record --batch 3` 同进程跑 3 场（墙钟 7.7 分钟）：

| 场次 | 语料 | 重录 | 结论 |
|---|---|---|---|
| `run837_r18` | 9605 / player | 9605 / player | ✅ 一致 |
| `run1074_r18` | 13845 / player | 13845 / player | ✅ 一致 |
| `run1082_r18` | 14310 / **winner=-** | 29418 / opponent | ⚠ 预期（语料是旧闸截断的，见 §9.6） |

这说明：**同进程跑多场不破坏确定性**（两场逐项一致），且重录能把截断场补成自然终局。

### 10.3 接手建议顺序

1. 先 `--record` 重录那 10 场截断场（约 10–20 分钟），把语料补齐；
2. 再 `--run` 跑一遍拿到全貌（约 40–60 分钟，`--batch 4` + 自动并行度）；
3. 看 `--report` 的聚类，**从最大的簇开始修**；
4. 单场迭代用 `--prefix`（秒级），别用 `--focus`（每次都全量）。

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

---

## 12. 相关文档

| 文档 | 什么时候看 |
|---|---|
| `docs/parallel_workflow.md` | 并行度、启动成本、隐藏桌面/SW_HIDE、沙箱禁管道 |
| `docs/consistency_workflow.md` | 一致性总流程、里程碑定义 |
| `docs/alignment_fix_workflow.md` | 阶段1/阶段2 对齐方法论 |

---

## 13. 新接手的 agent 请先读这一节（5 分钟上手）

### 13.1 三条铁律

1. **不改 `tools/verify_oracle.py`、不改 `gd_core_test/OracleAlignBattle.gd`**
   —— 长场工具是**完全独立**的一套（自带夹具、自带产物目录、自带报告）。
   主基线 `alignment.json` 的 860 场不受影响。
2. **产物写 `output/oracle/align_long/` 下，绝不覆盖 `output/oracle/fights/`**
   —— 冻结语料要人工确认后才能替换。
3. **跑重录前不要手填 `--batch` / `--jobs`**
   —— 默认全自动，按当时可用内存选。硬填会被内存闸压住（见 §9.8）。

### 13.2 第一次上手做什么

```bash
# 1) 先看现状：这 54 场是什么、多大
python -X utf8 tools/long_case_fix.py --list

# 2) 生成夹具（一次就够，已存在会跳过）
python -X utf8 tools/long_case_fix.py --prepare

# 3) 重录那 10 场截断场（语料 winner="-" 的，见 §9.6）
python -X utf8 tools/long_case_fix.py --record \
    --only run1015_r18,run1080_r18,run1082_r18,run1124_r18,run1125_r18,\
run1174_r18,run1194_r18,run1219_r18,run1302_r18,run1348_r18

# 4) 批量三腿验证，拿到全貌
python -X utf8 tools/long_case_fix.py --run

# 5) 看报告，从最大的簇开始修
python -X utf8 tools/long_case_fix.py --report
```

### 13.3 修复迭代的正确姿势

```bash
# ❌ 不要：每次都 --focus（每轮全量跑，几十秒到几分钟）
# ✅ 要这样：
python -X utf8 tools/long_case_fix.py --focus  run906_r18   # 首轮：定位首分歧，记账
# ...改代码...
python -X utf8 tools/long_case_fix.py --prefix run906_r18   # 之后每轮：只跑前缀，秒级
#   输出「前移 / 未动 / 退步」，退步要立刻回滚
```

### 13.4 六个坑（都已经踩过，别重踩）

| # | 坑 | 文档位置 |
|---|---|---|
| 1 | `--margin` 是**事件数**不是 tick | §3.3 |
| 2 | py 腿事件闸不抬 → 全是**伪分歧** | §4 |
| 3 | 一场一进程 → 启动成本吃掉全部收益 | §5 |
| 4 | 分片清单没真的下发 → N 个进程各跑全量 | §6 |
| 5 | 用 `read` 改 `.gd` 会**截断**（隐式字节上限） | §7 |
| 6 | 显式 `--jobs` 绕过内存闸 → 整机卡死 | §9.8 |

### 13.5 出问题先看哪里

| 症状 | 先查 |
|---|---|
| 跑着跑着整机卡 | 可用内存；`--batch` 是否被手填太大（§9.7） |
| 某段一直重跑 | 看门狗日志的「内存超限」还是「日志停滞」（§9.4） |
| 事件数比语料多 | 多半是截断场，预期行为（§9.6） |
| 分歧位置来回变 | 用 `--prefix` 看是「前移」还是「退步」，退步立即回滚 |
| 产物缺失 | 看 `output/_recovery/godot_logs/long_rec_*.log` 的 tail |
