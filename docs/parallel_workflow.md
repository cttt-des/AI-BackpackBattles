# 并行验证工作流（gd / py / compare 三腿并行 + 无窗口启动，默认自动定路数）

> 生成：2026-10-29，**2026-10-30 修订**（新增隐藏桌面启动器、oracle 录制并行、
> gd→py 流水线）。
> 适用：`tools/verify_oracle.py`、`tools/_np23_shard_verify.py`、`tools/oracle_chunk_driver.py`。
> 核心：**默认就是并行**，并行度**每次运行时按当时 CPU 与可用内存实时决定**，不需要手填；
> **所有 Godot 启动统一走 `tools/godot_headless.py`**，屏幕上不会出现窗口或弹窗。

---

## 1. 一句话用法

```bash
# 全量：gd 腿 → py 腿 → 比对，三条腿各自并行，路数自动
python -X utf8 tools/verify_oracle.py --force

# 只重算比对（产物已就绪，最常用）
python -X utf8 tools/verify_oracle.py --compare-only

# 定向若干场（并行同样生效）
python -X utf8 tools/verify_oracle.py --force --cases run570_r18,run906_r18

# 分片总控（三步串起来，等价于上面第一条，带耗时汇总）
python -X utf8 tools/_np23_shard_verify.py

# 神谕语料录制（914 场），并行 + 无窗口；参数 [chunk] [max_rounds] [jobs]
python -X utf8 tools/oracle_chunk_driver.py 60 12 0
```

**跑任何 Godot 之前先确认这一点**：窗口和 `OpenMem failed` 弹窗都不该出现在你屏幕上。
如果出现了，说明有人绕过了 `tools/godot_headless.py` 自己拼 `subprocess`（见 §7.1）。

不需要写 `--gd-jobs` / `--py-jobs` / `--compare-jobs`——**默认 0 表示自动**。

---

## 1b. 无窗口、无弹窗：为什么必须走隐藏桌面

这是本工作流**最容易被绕过去**的一环，代价是屏幕被占 + 录制被弹窗卡住。

### 实测结论（2026-10-30，逐条验证过）

| 做法 | 结果 |
|---|---|
| `--headless` | ❌ **Godot 3.6 没这个参数**（4.x 才有）。写了不报错，被当位置参数忽略，引擎照常走窗口路径 |
| `--no-window` | ⚠️ **仍会创建可见窗口**（实测窗口类 `Engine`、标题 `<项目名>`，用户屏幕上真的看得到） |
| `--video-driver Dummy` | ❌ 非法值。3.6 只认 `GLES3`/`GLES2`，写 Dummy 直接 `Unknown video driver 'Dummy', aborting.`、rc=255 |
| `SW_HIDE` / `STARTF_USESHOWWINDOW` | ⚠️ 只影响初始显示状态，Godot 自己 `ShowWindow` 就又出来了 |
| **独立隐藏桌面（`CreateDesktopW` + `lpDesktop`）** | ✅ **根治**：窗口和弹窗都只存在于那个桌面，用户桌面泄漏 **0 条** |

### `OpenMem failed` 弹窗到底是谁弹的

**不是 Godot**，是**搜狗输入法注入到宿进程里的 DLL** 调的 `MessageBox`：
窗口类 `#32770`（Windows 标准对话框类）、标题 `Error`、内容是
`t_skinfilemap.cpp(56) ... OpenMem failed, szNewMem:Local\sgime_skin.*.filemap`
（`err` 是 2=找不到文件，不是 5）。

它在**每个**宿进程里都注入，改 Godot 参数关不掉；但它弹的窗口同样只出现在
**当前桌面**上，所以隐藏桌面方案连它一起解决了。

### 用哪个 API

只用 `tools/godot_headless.py`，别自己拼 subprocess：

```python
import godot_headless as gh

# 同步跑一次（内部就是 spawn + wait）
rc, out, log = gh.run(gh.cmd(project="oracle", script="oracle_fight.gd"),
                      label="oracle", env_extra={"ORACLE_ONLY_CASES": cid})

# 异步起（并行时用这个，自己 wait）
p, log, fh = gh.spawn(gh.cmd(project="gd_core_test", script="OracleAlignBattle.gd"),
                      label="gd", tag="shard0",
                      env_extra={"ORACLE_ALIGN_OUT": GD_OUT})
rc = p.wait(); fh.close(); text = gh.read_log(log)
```

模块做的四件事，别在外面重做：

1. `--no-window --audio-driver Dummy`（不是 `--headless`）
2. `STARTUPINFO.lpDesktop` 指向隐藏桌面 `dsh_godot_hidden` + `SW_HIDE`
3. stdout/stderr **重定向到文件**（沙箱禁匿名管道）
4. `APPDATA` 按 PID+tag 隔离（`user://` 不互踩），**cwd** 设到
   `output/_recovery/cwd`（搜狗注入的 `debug.log` 就不落进仓库根目录了）

> 已经在用的地方：`verify_oracle.run_godot`、`oracle_chunk_driver`、
> `audit_oracle_bistable`、`verify_oracle_s2`、`run_truth_battle`。
> **新写启动 Godot 的脚本，一律 import 这个模块**——别再复制粘贴参数。

---

## 2. 自动并行度怎么算

```
jobs = min( PARALLEL_MAX_JOBS(5),
            max(1, cpu_count - 1),          # 留一核给系统和主进程
            max(1, 可用内存_GB // 1.2),      # 每 worker 峰值预算 1.2GB
            case 数 )
```

- **上限恒为 5**（收益递减 + 内存峰值随路数线性放大），任何情况下不会超过。
- 可用内存用 `GlobalMemoryStatusEx` 实时读（Windows）；探测失败退回 8GB 保守估计。
- 想压过自动值（例如机器空闲想跑满 5 路），显式给数即可：`--compare-jobs 5`。
- 想退回完全串行：`--compare-jobs 1`（其余两腿同理）。

实测参考（8 核 / 可用内存 4.4GB）：自动 **3 路**；同机 5 路实测 914 场比对 **279s→243s**。

启动时日志会打印决策结果，例如：
```
[compare] 并行 3 路，分桶负载（MB）：173.4, 173.2, 173.1
[godot]  并行 3 路，分桶负载（MB）：...
[py]     并行 3 路，分桶负载（MB）：...
```

---

## 3. 三条腿各自怎么并行

| 腿 | 入口 | 并行方式 | 幂等/续跑 |
|---|---|---|---|
| gd_core(Godot) | `run_godot_parallel()` | 按 case 分片，每片一个子进程，子进程内 `run_godot(chunk=0)` 跑整片 | 产物存在即跳过（`events.json` 非空） |
| gd_core_py | `run_py_parallel()` | 按 case 分片，每片一个子进程，子进程内 `run_py(subset)` | 同上 |
| compare | `compare_cases()` | 按 case 分片，每片一个子进程，结果写 `_cmp_shards/shard_N.out.json` 后按原顺序还原 | 纯计算，无产物 |

### 3b. gd → py 是**流水线**，不是整段重叠（重要）

**py 腿依赖 gd 腿产物**：`run_py` 要读 gd 侧 `events.json` 里的
`activation_order`（激活顺序来源，`verify_oracle.py:318-322`）；gd 产物不存在
就直接 `[py][skip] ... 缺 gd_core 侧产物`。

所以两条腿**不能整段并发**（试过，py 全 skip，白跑）。现在的做法是
`_run_both_legs()` 的**分片流水线**：

```
gd 片0 ──完成──▶ py 接手片0（再按 py_n 切成小批并发）
gd 片1 ──完成──▶ py 接手片1
gd 片2 ──完成──▶ ...
        （gd 后面的片仍在跑，与前面的 py 批重叠）
```

- 入口：`verify_oracle.py` 主流程自动走这条（`--gd-jobs`/`--py-jobs` 仍可指定）。
- 只有一腿（`--skip-godot` / `--skip-py`）或两腿都算成 1 路时，退化为
  `_run_legs_serial()`（gd 跑完再 py），语义不变。
- 日志里看得到：`[legs] gd 片 0 完成…——py 接手该片`、`[legs] 流水线完成，总墙钟 Ns`。

**别把它改回"两腿一起 start 再 join"**——py 会全 skip，比串行还慢。

**分桶用 LPT**（Longest Processing Time first）：按语料 `events.json` 体积降序，依次投给当前最轻的桶。
理由：长战（如 `run906_r18` 25026 事件 / 8MB）若和别的场挤一片，该片就决定总时长；
LPT 让各片负载近似相等（实测 914 场 5 片各 173MB，同时收尾）。
轮转分片（`cases[i::N]`）实测 384s，LPT 242s，差 37%。

---

## 4. 沙箱禁令：不能用管道（这是本环境最硬的约束）

本环境**禁止匿名管道**：任何 `subprocess.run(..., capture_output=True)`、
`multiprocessing.Pipe`、`ProcessPoolExecutor` 都会在 `CreatePipe` 处抛
`PermissionError: [WinError 5]`。所以：

- **不要**用 `capture_output=True` 捕获 Godot/python 子进程输出 → **重定向到文件**再读回：
  ```python
  with open(log_path, "wb") as lf:
      rc = subprocess.run(cmd, stdout=lf, stderr=subprocess.STDOUT).returncode
  ```
  （`verify_oracle.run_godot` 与 `run_gd_core.run` 已按此改造，日志落在
  `output/_recovery/godot_logs/`、`output/_recovery/gdcore_run_logs/`）
- **不要**用 `ProcessPoolExecutor` 做并行 → 用 **独立子进程 + 真实文件交换**（见 §5）。

---

## 4b. 为什么不用 ProcessPoolExecutor

本环境（DSH 沙箱）**禁止命名管道**：`multiprocessing.Pipe` 直接 `PermissionError: [WinError 5]`。
所以并行实现是 **独立子进程 + 真实文件交换**：

```
主进程 → 写 shard_N.in.json（case 清单）
       → subprocess.Popen(python tools/verify_oracle.py --gd-worker shard_N.in.json)
       → 子进程跑完写 shard_N.out.json（比对腿）或直接落产物（重放腿）
       → 主进程按原顺序读回 / 汇总
```

**不要"优化"成线程池或 ProcessPool**——会在这个沙箱里直接失败。

---

## 5. 子进程入口（内部用，别手工敲）

| 子命令 | 作用 |
|---|---|
| `--gd-worker <list.json>` | gd 腿一个分片 |
| `--py-worker <list.json>` | py 腿一个分片 |
| `--compare-worker <list.json> <out.json>` | 比对一个分片，结果写 out.json |

这些参数在 `--help` 里被 SUPPRESS 隐藏，是给主进程 spawn 用的。

---

## 6. 分片产物落点（可安全清理，非基线）

```
output/oracle/align/_gd_shards/     gd 分片清单与子进程日志
output/oracle/align/_py_shards/     py 分片清单与子进程日志
output/oracle/align/_cmp_shards/    比对分片清单与结果
```

子进程 stdout 重定向到 `*_shards/<prefix>_N.log`，排查分片失败**先看这里**。

---

## 7. 必须遵守（踩过的坑）

1. **Godot 一律走 `tools/godot_headless.py`**。它内部用
   `--no-window --audio-driver Dummy` + **独立隐藏桌面**；
   - 不要写 `--headless`（3.6 没这参数，会被忽略、照常出窗口）；
   - 也不要以为 `--no-window` 就够了（实测仍出可见窗口，见 §1b）；
   - `--video-driver Dummy` 是**非法值**（rc=255），别试。
2. **APPDATA 按 PID 隔离**已内置在 `run_godot`，不要绕过它自己 spawn Godot。
3. **`--force` 删产物 + 生成夹具必须串行做**（现在就在起子进程之前完成），
   并行只发生在"已有确定输入"的阶段。
4. **`--compare-only` 不要与 `--force` 同时用**（互斥已在代码里拦）。
5. 并行期间**不要再手动开 Godot**，否则两套隔离机制混用。
   手动排查单场也用 `python -X utf8 tools/godot_headless.py` 里的 API，
   或直接 `ORACLE_ONLY_CASES=<cid> python -X utf8 tools/oracle_chunk_driver.py 1 1 1`。
6. 结果必须按 `cases` 原顺序还原——`alignment.json` 的 `perCase` 顺序是可比基线，
   并行实现里那条"保序"注释别删。
7. ⚠ **定向跑（`--cases`）会把 `alignment.json` 收缩成那几场**，收工后必须补一次
   `python -X utf8 tools/verify_oracle.py --compare-only`（全量、无 `--cases`）把基线还原，
   否则下一个人看到的是"只剩 2 场"的假基线。
8. ⚠ **`--force --cases` 会尝试重写 `gd_core_test/oracle_align_cases.json`**，
   该文件被别的进程占用时（另一 agent 正在跑）会 `PermissionError`；
   此时加 `--skip-fixtures` 复用现有夹具即可。

---

## 8. 验收：并行结果必须与串行逐字节一致

```bash
# 独立对照器：跑 1 路 vs N 路，逐字节比对，不一致会打印首个差异行
python -X utf8 tools/_np_compare_par.py --selftest --jobs 5

# 只对几场做快速自检
python -X utf8 tools/_np_compare_par.py --selftest --cases run570_r18,run906_r18 --jobs 5
```

**任何并行改动后，先跑这条自检，PASS 才算可上线。**
历史验收记录（2026-10-29）：914 场 1 路 vs 5 路，`perCase`（caseId/match/首分歧 index）、
`localization`、`fixPlan` **全等**，已用并行版重写主 `alignment.json`。

### 隐藏桌面 + 并发录制的验收（2026-10-30）

录制确定性是硬底线——**窗口藏起来不能让事件流变样**。实测四组，全部逐字节一致：

| 用例 | 启动方式 | 与冻结语料 `events.json` |
|---|---|---|
| run569_r11 | 隐藏桌面（单进程） | ✅ 逐字节一致 |
| run569_r11 | `--no-window` 老方式 | ✅ 逐字节一致 |
| run570_r18 | **隐藏桌面 + 与 run571_r18 同时并发** | ✅ 逐字节一致 |
| run571_r18 | **隐藏桌面 + 与 run570_r18 同时并发** | ✅ 逐字节一致 |

并发墙钟 96s 跑完两场（两个 Godot 进程同时），同时用户桌面窗口泄漏 **0 条**。
另外全量 `--compare-only` 4 路 LPT 跑出 **461/914**，与改造前基线完全相同。

---

## 9. 性能基线（8 核 / 可用内存 4.4~5.6GB）

| 阶段 | 串行 | 并行 |
|---|---|---|
| compare 914 场 | ~600s | **195~279s**（自动 2~4 路 + LPT） |
| gd 腿 914 场 | ~16 min | 自动 3~5 路（每片独立子进程） |
| py 腿 914 场 | 单进程 | 自动 3~5 路（每片独立跑子集） |
| gd+py 全量 | ≈ gd + py（串行） | **分片流水线**，py 跟在 gd 每片后面，省掉 py 的首个等待段 |
| oracle 录制 914 场 | 单进程块循环 | `oracle_chunk_driver.py` 并行（上限 4 路，每路独立 APPDATA） |

> 对照记录（2026-10-30）：全量 `--compare-only` 4 路 LPT 实测 **260.4s**，
> 结果 461/914 与并行改造前完全一致（基线未被改动污染）。

> 实测（2026-10-29）：自动判定 3 路时 compare 243s；判定 4 路时 **195.6s**；
> 单场（run906_r18 25026 事件）是最慢单元，LPT 让它单独占一片，避免拖累其他片。

### 自动并行度的边界行为

- 内存紧张（可用 < 3.6GB）→ 自动降到 **2 路**；再紧 → **1 路（串行）**。
- 笔记本切省电模式、或另一 agent 正在吃 CPU/内存时，路数会自动变小，**这是设计行为**。
- 想固定路数：`--compare-jobs 5`（仍受上限 5 约束，不会超）。

> 注：compare 的收益与"最长单场"强相关，LPT 分桶是收益关键；gd/py 腿受磁盘与 CPU 双重约束，
> 路数超过 5 收益明显递减。
