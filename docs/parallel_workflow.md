# 并行验证工作流（gd / py / compare 三腿并行 + 无窗口启动，默认自动定路数）

> 生成：2026-10-29，**2026-11-06 修订**（窗口真相实测、卡死自动重跑、启动点治理、
> 并行度闸门、长场工具；隐藏桌面方案已被实测推翻）。
> 适用：`verify_oracle.py`、`_np23_shard_verify.py`、`oracle_chunk_driver.py`、
> `long_case_fix.py`、`run_gd_core.py`，以及所有经 `godot_headless` 启动 Godot 的工具。
> 核心：**默认就是并行**，并行度按当时 CPU 与可用内存实时决定，不需要手填；
> **所有 Godot 启动统一走 `tools/godot_headless.py`**。
>
> ⚠ **两个必须先知道的结论**：
> 1. 窗口**躲不掉**（隐藏桌面/虚拟桌面/外部压制全部失效，见 §1c）；
> 2. 但**被点了也不白跑**（卡死自动重跑，见 §1d）。

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

## 1b. 无窗口、无弹窗：机制与（已被推翻的）隐藏桌面方案

这是本工作流**最容易被绕过去**的一环，代价是屏幕被占 + 录制被弹窗卡住。

> ⚠ **先看结论**：本节的「独立隐藏桌面」在 2026-11-06 被实测**推翻**（`lpDesktop`
> 被 `CreateProcess` 忽略）。真正生效的只有 `SW_HIDE` + `--position` 屏外出生，
> 而且它们也**挡不住引擎在 ~25s 后把窗口搬回屏幕**。完整实测与替代方案见 §1c / §1d。

### 实测结论（2026-10-30，逐条验证过）

| 做法 | 结果 |
|---|---|
| `--headless` | ❌ **Godot 3.6 没这个参数**（4.x 才有）。写了不报错，被当位置参数忽略，引擎照常走窗口路径 |
| `--no-window` | ⚠️ **仍会创建可见窗口**（实测窗口类 `Engine`、标题 `<项目名>`，用户屏幕上真的看得到） |
| `--video-driver Dummy` | ❌ 非法值。3.6 只认 `GLES3`/`GLES2`，写 Dummy 直接 `Unknown video driver 'Dummy', aborting.`、rc=255 |
| `SW_HIDE` / `STARTF_USESHOWWINDOW` | ⚠️ 只影响初始显示状态，Godot 自己 `ShowWindow` 就又出来了 |
| 独立隐藏桌面（`CreateDesktopW` + `lpDesktop`） | ❌ **2026-11-06 实测推翻**：`CreateProcess` 忽略 `lpDesktop`，子进程仍在 `Default` 桌面（连记事本都进不去）。当时看到的「泄漏 0 条」是 `SW_HIDE` 让窗口不可见造成的假象 |
| **`--position -32000,-32000`（出生即在屏外）** | ✅ 有效（窗口一出生就在屏外）；但运行 20~30s 后引擎会把它搬回 (0,0)，见 §1c |

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

模块做的五件事，别在外面重做：

1. `--no-window --audio-driver Dummy --position -32000,-32000 --resolution 1280x720`
   （**不是** `--headless`；`--position` 让窗口出生即在屏外）
2. `STARTUPINFO`：`lpDesktop` 指向隐藏桌面 + `SW_HIDE`
   （★ `lpDesktop` 实测无效，真正起作用的是 `SW_HIDE`，详见 §1b 更正）
3. stdout/stderr **重定向到文件**（沙箱禁匿名管道）
4. `APPDATA` 按 PID+tag 隔离（`user://` 不互踩），**cwd** 设到
   `output/_recovery/cwd`（搜狗注入的 `debug.log` 就不落进仓库根目录了）
5. `--resolution 1280x720` 固定尺寸，只防它按默认尺寸铺满屏；
   **实测不影响事件流**（见 §1c 的确定性验证）

> 已经在用的地方：`verify_oracle.run_godot`、`oracle_chunk_driver`、
> `audit_oracle_bistable`、`verify_oracle_s2`、`run_truth_battle`。
> **新写启动 Godot 的脚本，一律 import 这个模块**——别再复制粘贴参数。

---

## 1c. 窗口到底会不会出现：完整实测（2026-11-06）

### 现象

长场录制时会有一个 `Engine` 类窗口出现在屏幕 `(0,0)`，尺寸 **1280×720（满屏）**，
显示的还是游戏开场图。用户若点了它，Godot 卡在阻塞 tick 循环里彻底未响应：
实测两次墙钟 231s / 161s，退出码 `0xFFFFFFFF` / `0xCFFFFFFF`，`events.json` **0 事件**，
日志停在 `t=63.3s`（整场 66.6s，差最后 3 秒）。

### 时间线（多次复现，数值随机器负载浮动）

```
t=0.1s    窗口创建，位置 (209,116)，不可见
t=0.6s    --position 生效 -> (-21333,-21333)，不可见   ✅
t≈20-30s  引擎把它搬回 (0,0,1280,720) 并显示            ❌ 用户看到全屏开场图
```

### 试过的所有办法（逐条实测，别重复踩）

| 手段 | 结果 |
|---|---|
| `--position -32000,-32000` | ✅ 出生即屏外，但 ~25s 后被引擎搬回 |
| 外部 `ShowWindow(SW_HIDE)` | ❌ 在阻塞 tick 期间**阻塞 222 秒**（不是不生效，是排队） |
| 外部 `SetWindowPos`（不带 ASYNC） | ❌ 阻塞 1.08s |
| `SetWindowPos` + `SWP_ASYNCWINDOWPOS` | ⚠️ 不阻塞（0.0006s），但**请求不被目标线程处理**，窗口位置不变 |
| `SetWindowLongW` 改 `GWL_EXSTYLE` | ❌ 阻塞 1.14s，且**触发窗口重排**，反而把窗口搬到屏幕正中 |
| `DwmSetWindowAttribute(DWMWA_CLOAK)` | ❌ 跨进程 `hr=0x80070005` 权限不足 |
| `OS.set_window_visible` | ❌ Godot 3.6 **不存在**这个 API |
| `lpDesktop` 独立隐藏桌面 | ❌ `CreateProcess` 忽略该参数（见 §1b 更正） |
| 虚拟桌面 `MoveWindowToDesktop` | ❌ 只能移动**自己进程**的窗口（自己的成功，记事本/Godot 均 `E_ACCESSDENIED`） |
| `IVirtualDesktopManagerInternal`（未公开） | ❌ 本机三个已知 IID 全 `E_NOINTERFACE` |
| `HWND_BOTTOM` 沉底（含抢在出现瞬间） | ❌ 引擎创建窗口时会主动带到前台，rank 仍是 1~2 |
| 预写配置 `window_mode="windowed"` | ❌ `clipToScreen()` 把它夹回 (0,0)，67% 时间可见 |
| 预写配置 `window_mode="fullscreen"` | ❌ 同样 67% 时间可见 |

**根因**：Godot 录制主循环是**手动 tick 的阻塞循环**（整场战斗不返回消息循环），
所以任何跨进程窗口操作都只能排队失效；而窗口是引擎自己创建并主动显示的。

> ⚠️ 想真正隐藏窗口，只有**从引擎内部**做（在 `oracle_fight.gd` 主循环里调
> `OS.set_window_position`）。**当前决定不做**（用户要求不动 oracle 项目）。
> 替代方案见 §1d：卡死自动重跑。

### 确定性：窗口参数**不影响事件流**

三组配置跑同一场（run570_r18），`events.json` 的 sha1 **完全相同**：

| 配置 | event_count | winner | ticks | sha1 |
|---|---|---|---|---|
| 仅 `--position` | 548 | player | 648 | `1bdb30f9…` |
| `--position` + `--resolution` | 548 | player | 648 | `1bdb30f9…` |
| 原始基线（只有 `--no-window`） | 548 | player | 648 | `1bdb30f9…` |

**结论：窗口看着烦，但不污染语料。**（`globalPosToScreenPos` 只是坐标换算，不吃 RNG）

---

## 1d. 卡死自动重跑（`tools/godot_watchdog.py`）

既然窗口躲不掉，就保证「被点了也不白跑」。

```bash
# 长场重录自动带看门狗
python -X utf8 tools/long_case_fix.py --record --batch 3 --jobs 3
# 可调：--stall-seconds 90  --max-retries 2
```

### 判据：日志停滞（**不是** `IsHungAppWindow`）

`IsHungAppWindow` 实测是**假信号**——正常录制期间（t=5s~40s，日志持续增长、产物正常）
它**恒返回 1**。原因同上：阻塞 tick 循环不处理消息，系统据此就判未响应。

改用**日志文件零增长**。正常录制的日志停滞实测序列：

```
停滞时长（秒）：3, 0, 4, 2, 7, 1, 6, 1, 0      <- 最长 7 秒
```

故阈值取 **90 秒**（10 倍余量）。命中即 `Popen.kill()`（只杀自己起的进程，
不按进程名扫，避免误伤）并重跑该段。

### 验证方式与结果

用 `SuspendThread` 挂起 Godot 全部 25 个线程，真实模拟「被点一下未响应」：

```
[破坏者] 挂起 pid=22828 的 25 个线程（模拟点击未响应）
[看门狗] rec0_0 日志停滞 16.0s -> 判卡死，杀掉重跑
段 1/1 rec0_0 rc=0（累计 1 分钟）
[record] 完成：事件数一致 1 / 缺失 0 / 不一致 0
```

### Python API

```python
import godot_watchdog as wd

res = wd.run_with_watchdog(
    specs, label='long_rec', max_parallel=3,
    stall_seconds=wd.DEFAULT_STALL_SECONDS,   # 90
    max_retries=wd.DEFAULT_MAX_RETRIES,       # 2
    on_event=lambda kind, p: print(kind, p))  # kind: done / stalled / timeout
# res[i] = {index, tag, rc, log, tail, secs, retries, killed, verdict}
```

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

### 2b. 启动成本闸门：`gh.effective_jobs()`（**必读，防负优化**）

上面算出的是**理论上限**。真正能开几路，还要过一道闸：

```python
jobs = gh.effective_jobs(n_items, gh.auto_jobs(n_items, requested),
                         min_items_per_job=8)
```

**为什么必须有这道闸**（2026-10-31 实测教训）：Godot 的启动成本随项目体积走，
不是常数 —— 而「每片一个进程」的分片方式会把启动成本乘上片数。

| 项目 | 体积 / 文件数 | 单次启动（含 `res://` 扫描） |
|---|---|---|
| `gd_core_test` | 45 MB / 701 | **≈ 1 s** |
| `oracle` | 544 MB / **15419** | **≈ 25 s** |

实测负优化两例：

| 场景 | 串行 | 分片 | 结果 |
|---|---|---|---|
| oracle 两场，每场一进程 | 6.12 s | 8.49 s | **0.72x 更慢** |
| 物品解析 3 路 | 8.48 s | 11.22 s | **0.76x 更慢** |
| 四个轻闸门（每道都是完整启动） | 7.51 s | **2.86 s**（4 路） | 2.6x 更快 ✅ |

判据：

```
每片成本 = 启动成本 + 该片任务成本
分片有收益  <=>  启动成本 < 单片任务成本 x (1 - 1/jobs)
```

| 调用点 | `min_items_per_job` | 理由 |
|---|---|---|
| `verify_oracle_s1/s2` 的 gd 腿 | `MIN_CASES_PER_SHARD = 8` | oracle 启动 25 s |
| `verify_oracle_s1/s2` 的 py 腿与比对 | 2 | 无 Godot 启动，但要避免只起线程 |
| `long_case_fix --record` | `--batch`（默认 3） | 长场事件多，防 MessageQueue 溢出 |
| `run_item_parse` | **默认 1 路** | 分片不能少干活，只是多付启动 |

### 2c. `gh.run_many()` 的正确用法（完成顺序补位）

```python
res = gh.run_many(
    specs,                          # [{cmd, tag, env_extra, timeout}, ...]
    label='myjob',
    max_parallel=3,                 # 在途上限（0=一起起齐）
    on_done=lambda r: print(r['index'], r['rc']),   # 完成即回调
)
# 返回 [{index, tag, rc, log, tail, secs}, ...]，**按完成顺序**；要原顺序按 index 排序
```

> ⚠ **别写「一次起齐、再按启动顺序 `wait()`」**：队首慢任务会把槽位空占住，
> 后面的任务干等不补位。实测（队首 4s 慢活 + 6 个 0.5s 快活、上限 2）：
> 按序回收 **5.78 s**，完成补位 **4.18 s**（理想 4.0 s）—— 多花 **44%**。

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

---

## 10. 启动点治理：别让脚本绕过统一入口

### 10.1 静态检查：`tools/check_godot_launch.py`

```bash
python -X utf8 tools/check_godot_launch.py        # 扫全仓，有违规 rc=1
python -X utf8 tools/check_godot_launch.py --all  # 连 output/ 历史脚本一起扫
```

**为什么需要它**（2026-11-06 事故复盘）：`output/_offpeak/`、`output/_round_patches/`
下有 8 个历史探针脚本自己拼 Godot 路径裸 `Popen`，同时丢掉了三样东西：

| 丢掉的东西 | 后果 |
|---|---|
| `startupinfo` | 窗口**直接弹到屏幕**，用户一点就未响应卡死 |
| `APPDATA` 隔离 | `user://` 互踩、IME 弹窗无人压制 |
| 文件重定向 | 沙箱禁匿名管道，`capture_output` 会 `WinError 5` |

而且它们大多还写着 `--headless` —— Godot 3.6 **没有这个参数**，
写了等于走普通窗口路径，比不写更糟。

判据（只认真正起进程的代码，**不误报注释**）：

1. `subprocess.Popen/run` + 同一处出现 Godot 可执行名或 `GODOT` 变量 → 必须走 gh；
2. 起进程的上下文没有 `startupinfo` / `py_popen` / `gh.` → 报违规；
3. 命令行里出现**带引号的** `--headless` 字面量 → 报违规。

### 10.2 单脚本统一入口：`tools/run_godot_script.py`

别再手敲引擎命令行（少写一个参数就出窗口）：

```bash
# 跑一个 gd_core_test 脚本
python -X utf8 tools/run_godot_script.py RngProbe.gd --quiet

# 换项目 + 传环境变量（单场神谕复跑）
python -X utf8 tools/run_godot_script.py oracle_fight.gd --project oracle \
    --env ORACLE_ONLY_CASES=run570_r18 --quiet

# 有墙钟上限的
python -X utf8 tools/run_godot_script.py TruthBattle.gd --timeout 3600 --quiet
```

它内部就是 `gh.cmd` + `gh.run`，日志自动落 `output/_recovery/godot_logs/`。

### 10.3 子进程也要藏：`gh.py_popen` / `gh.worker_startupinfo`

搜狗 IME 是**往每个宿进程注入**的。过去只有 Godot 走 `_startupinfo()`，而启动它的
python worker（`--gd-worker` / `--py-worker` / `--compare-worker`）是裸 `Popen` ——
worker 留在用户桌面，被注入后弹框就落到用户屏幕上。

```python
# 起 Python 子进程时用它，别用裸 subprocess.Popen
p = gh.py_popen([sys.executable, worker_py, "--gd-worker", lst],
                cwd=ROOT, stdout=log, stderr=subprocess.STDOUT, env=e)
```

已改用它的地方：`verify_oracle` 三处 worker、`verify_oracle_s1`、`_np_compare_par`、
`verify_parallel_safety`、`_np23_shard_verify`、`oracle_run_guarded`。

> ⚠ `capture_replay.py` / `launch_fresh_and_scan.py` / `live_scan*.py` 那类**需要真实可见**
> **窗口与人类输入**的工具，**必须保持默认桌面**，不要套这一层。

---

## 11. 并行安全验收：`tools/verify_parallel_safety.py`

```bash
python -X utf8 tools/verify_parallel_safety.py --jobs 3
# 单项：--only byte | --only leak | --only itemparse
```

任何并行/窗口相关的改动之后都该跑它：

| 项 | 判据 |
|---|---|
| `byte` | 同一批闸门 1 路 vs N 路，产物文件**逐字节相同** |
| `leak` | N 路并发期间用户桌面**新增可见窗口 0 条** |
| `itemparse` | 显式分片时各片「待解析」之和 == 全量（证明没漏切文件） |

> 注：`leak` 判据只查**可见**窗口。若要看「窗口是否出现在屏内」，需另查
> `GetWindowRect`（`--position` 让窗口在屏外时，它仍然"存在但不可见"）。

---

## 12. 相关工具索引（2026-11-06 现状）

| 工具 | 一句话 |
|---|---|
| `tools/godot_headless.py` | **唯一**启动 Godot 的入口（spawn/run/cmd/env/py_popen/run_many/effective_jobs/lpt_buckets） |
| `tools/godot_quiet.py` | 窗口静默层（`install()` 包一层 spawn；只做不阻塞的 `SetWindowPos(ASYNC)`） |
| `tools/godot_watchdog.py` | **卡死自动重跑**（日志停滞判据，见 §1d） |
| `tools/run_godot_script.py` | 单脚本统一入口（见 §10.2） |
| `tools/check_godot_launch.py` | 启动点静态检查（见 §10.1） |
| `tools/verify_parallel_safety.py` | 三项并行安全验收（见 §11） |
| `tools/long_case_fix.py` | **长场专项**（诊断/夹具/验证/前缀重放/重录），见 `docs/long_case_fix_guide.md` |
