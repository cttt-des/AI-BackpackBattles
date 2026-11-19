# Backpack Battles AI（背包乱斗 AI）

围绕《背包乱斗》（Backpack Battles）开发的 Windows 工具集，覆盖游戏状态读取、战斗日志导出、对局语料采集、战斗模拟、摆盘搜索与自动游玩。长期目标是以接近原版的高速 C++ 战斗内核提供胜率评估，支持摆盘 AI 的训练和使用。

## 项目全貌

| 模块 | 功能 | 入口与状态 |
|---|---|---|
| 自动游玩与控制面板 | 读取金币、生命、职业、商店及物品位置；执行启发式决策；展示背包；导出阵容和历史回合 | `launcher.py`、`core/`、`gui/`；已有实现，游戏升级后需要复核内存布局 |
| 战斗日志导出器 | 从游戏进程只读提取真实事件、双方阵容，导出中英文游戏格式战报和 JSON | `combatlog_exporter.py`；独立于模拟器，是实机对照工具 |
| 战斗模拟器 | 阵容对战、固定种子复现、批量胜率和结果导出 | v0.6.0 的 `backpack_native/` 使用 1.1.10 C++ 内核；旧 Python/GDScript/Cython 路径保留 |
| 对局操作记录器 | 记录真人或 AI 的买卖、刷新、锁定、合成与开战状态，折叠为训练样本 | `core/recorder.py`、`core/store.py`、`tools/corpus_*.py` |
| 历史采集与解码 | 采集排行榜缓存、解析历史数据库、建立对手池和阵容样本 | `gripper/`、`core/build_history.py`；真实存档与数据库留在本地 |
| 摆盘搜索与训练 | 给定持有物品，联合搜索上场子集、包布局、物品位置与朝向，以模拟胜率评价 | `trainer/`；已有合法性、评估、搜索、学习预筛和分层实验，处于研究阶段 |
| 逆向与一致性验证 | 解包、反编译、数据提取、录制参照、逐事件差分和性能测量 | `tools/`、`docs/` 与本地 `output/_v1110/` |

外置读取和操作是主程序的常用路径；本地还保留可选桥接注入实验。模拟器可脱离游戏运行。自动游玩、日志导出和模拟器分别有自己的入口与发布版本。

## 当前进度与适用范围

### 战斗内核

当前重点是 **1.1.10 原版战斗逻辑与 C++ 内核逐事件一致，以及一致前提下的速度优化**。

- 当前优化 DLL 通过基准 **914/914**、扩展 **1690/1690**，共 **2604/2604** 场逐事件核验，覆盖事件顺序、数值、因果链接、普通物品与宝石来源、胜负和自然终局。
- 验收参照来自恢复的 1.1.10 工程，主要运行于复制的发行版 EXE；扩展保留 785 场通用 Godot 3.6 录制。核验使用冻结阵容、初态和已观测宿主 RNG 边界重放。
- 无录制输入的批量模拟从固定启动模型按种子运行，已检查单场、单线程和双线程批量确定性。现有语料通过的结论有上述输入范围，新增机制、版本和场景仍需实机对照。
- v0.6.0 发布基准使用本机 i5-8265U 和固定 200 场，单线程三轮交替对照的中位速度为 **38.31 场/秒**，最慢一轮为 **35.99 场/秒**。同轮优化前中位数为 14.39 场/秒，每批 CPU 时间下降 62.5%，峰值工作集约 80.1 MiB。速度随阵容、硬件和后台负载变化。

[逐事件总账](output/_v1110/native_hot_path_full_gate.json) · [性能记录](output/_v1110/native_hot_path_benchmark.json) · [修复与验收过程](docs/战斗触发与时序四方对齐计划.md) · [C++ 性能优化清单](docs/C++模拟器性能优化清单.md)

历史文档中的“1690 场三方对齐”属于旧版 Oracle/GD/Python 管线，口径为 914 基线加 776 扩样；当前 2604 场为 914 基线加 1690 扩展。旧结论、数据和 API 各有对应版本。

### 摆盘 AI

摆盘任务以**当前持有物品（含包）**为输入，输出上场子集及位置、朝向，目标是提升给定回合和对手分布下的胜率。研究范围包括包与物品的双层几何约束、跨包加成、冷启动搜索、学习预筛和对手池评估。

`trainer/` 已有 P0 合法性验证、P1 共用随机种子评估、P2 搜索、P3 学习预筛以及 P4/P5 分层与换包实验。早期报告中的绝对胜率受回合、基础生命和职业映射修正影响，阅读时应连同修订说明核对。增量摆盘与完整产品化仍是后续工作。

训练适配层 `trainer/native_backend.py` 支持原生运行时，默认目录为本机 `dist/native_1_1_10`，可由 `BACKPACK_TRAINER_BACKEND` 选择后端。该目录与发布包 `backpack_native` 有各自的清单，切换时需要核对 DLL、绑定和数据版本。

[训练路径规划](docs/训练路径规划.md) · [训练初步报告](trainer/训练初步报告.md) · [真人标尺样本任务](docs/摆盘标尺样本采集_开发任务书.md)

## 下载

独立 EXE 无需安装 Python；Python 开发和批量调用使用 wheel。各组件历史包见 [GitHub Releases](https://github.com/cttt-des/AI-BackpackBattles/releases)。

| 组件版本 | 下载 | 用途 |
|---|---|---|
| v0.6.0 原生模拟器 | [EXE](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.6.0/BackpackSimulator.exe) · [wheel](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.6.0/backpack_battles_sim-0.6.0-cp314-cp314-win_amd64.whl) | 1.1.10 C++ 内核；阵容 JSON、批量胜率与逐场结果 JSON |
| v0.5.4 旧模拟器 | [EXE](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.5.4/BackpackSimulator.exe) · [wheel](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.5.4/backpack_battles_sim-0.5.4-cp314-cp314-win_amd64.whl) | 旧 Python/Cython 路径；镜像对战、物品联动和游戏格式战报文本 |
| v0.4.0 自动游玩 | [BackpackAI.exe](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.4.0/BackpackAI.exe) | 自动游玩 GUI 的历史发布包 |
| v0.3.1 日志导出器 | [BackpackCombatLog_v0.3.1.exe](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.3.1/BackpackCombatLog_v0.3.1.exe) | 游戏真实战斗日志与阵容导出 |

v0.6.0 wheel 适用于 **CPython 3.14、Windows x64**。DLL 使用本机 i5-8265U 编译选项，建议具有 AVX2 的处理器。自动游玩与导出器的历史发布版本不代表已经验收新版游戏兼容性。

## 快速使用

### 原生模拟器与 Python API

打开 v0.6.0 EXE，选择玩家、对手的 v3/v4 阵容 JSON，设置起始种子和场数，查看胜率并保存逐场结果。界面使用单线程 C++ 批量内核，计算在后台执行。

```powershell
pip install "https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.6.0/backpack_battles_sim-0.6.0-cp314-cp314-win_amd64.whl"
```

```python
import json
from pathlib import Path
from backpack_native import run_mc

player = json.loads(Path("player.json").read_text("utf-8-sig"))
opponent = json.loads(Path("opponent.json").read_text("utf-8-sig"))
result = run_mc(player, opponent, seed=42, runs=200, workers=1)
print(result["win_rate"])
print(result["results"][0])
```

结果包含胜率、胜场数以及每个种子的胜负、时长、事件数和超时标记。wheel 中原有 `simulator` 接口保留旧 Python 内核语义；新版 C++ API 使用 `backpack_native`。

### 源码入口与旧模拟器

下列入口按各自依赖运行；完整工作区还包含本地资源与构建产物，Git 克隆不包含全部游戏资源与数据库。

```powershell
python launcher.py                 # 自动游玩 GUI；连接运行中的游戏
python combatlog_exporter.py       # 真实战斗导出到 output/combat_logs/
python native_simulator.py         # 新版模拟器 GUI；需匹配的 DLL
python battle_simulator.py         # 旧版模拟器 GUI
python -m simulator.simulate player.json opponent.json --seed 42
python -m simulator.simulate player.json opponent.json --runs 100
```

旧模拟器支持事件 JSON、胜负统计与中英文游戏格式战报，渲染层在 `simulator/log_text.py`。批量接口有 `run_mc_pool` 和内存态 `run_mc_mem`，例如：

```python
from simulator.simulate import run_mc_mem
summary = run_mc_mem(player, opponent, seed=42, runs=200, workers=1)
print(summary["win_rate"])
```

旧内核与 Cython 构建说明见 [build_cython_用法](docs/build_cython_用法.md)。并发数应结合 CPU 实际负载和固定批量基准选择。

## 记录、采集与训练数据

### 对局操作记录器

在主程序 GUI 中开始、停止记录，可跟随真人或 AI 操作。记录完整状态和原始动作，再按买卖、刷新、合成、开战等决策点折叠；反复摆放或锁定中的净零变化会被过滤。

| 输出 | 内容与用途 |
|---|---|
| `output/records/<run_id>/raw/` | 按回合分片的事件与压缩归档，用于审计和重算 |
| `corpus/decisions.jsonl` | 状态、净动作、下一状态和标签，供局内决策训练 |
| `corpus/lineups.jsonl` | 开战瞬时 v4 阵容和结果，供摆盘分布与评估 |
| `corpus/traces.jsonl` | 可选摆盘轨迹，使用 `--traces` 导出 |

```powershell
python -X utf8 tools/corpus_fold.py output/records/<run_id>
python -X utf8 tools/corpus_check.py output/records/<run_id>
python -X utf8 tools/corpus_stats.py output/records/<run_id>
```

配置在 `config.yaml` 的 `recorder:` 段。格式与折叠规则见 [记录器设计](docs/recorder_design.md)。

### 历史阵容与排行榜缓存

`core/build_history.py` 处理游戏历史记录和回合阵容导出。`gripper/` 从本地 `runs_steam.cache` 解码数据、入库和导出，形成训练对手池；排行榜窗口代表最近上传对局，需要按职业、回合、段位和记录版本筛选。

本地 `history/`、`database/` 保存真实存档与语料，不进入 Git。采集流程、数据库字段及 Windows 用法见 [gripper 说明](gripper/README_fixed.md)。本机另有被 Git 忽略的一键刷新脚本，使用前注意其包含游戏启动与退出操作。

### 摆盘训练入口

`trainer/layout_rules.py` 提供双层布局合法性、包加成指派与解析预筛；`evaluator.py` 管理对手池、种子和胜率评价；`actions.py`、`p2_search.py`、`p3_search.py` 实现搜索动作与预筛流程。示例：

```powershell
python -X utf8 trainer/bench.py --n 200 --workers 1 --json output/perf/trainer_bench.json
python -X utf8 trainer/p2_search.py --workers 1
```

这些入口依赖本地数据库和运行时。旧 `ai/` 是本地历史实验目录，当前训练路径以 `trainer/` 为准；早期实验结论与待办见训练报告。

## 阵容与资源约定

阵容采用 v4 平铺格式，兼容 v3 嵌套格式。`in` 指向承载袋的数组下标，`gems` 保存镶嵌宝石，`r`/`rotation` 使用 0/90/180/270 度；位置对应旋转后占格左上角。详细字段以 [模拟器架构](docs/simulator_architecture.md) 和 `core/lineup.py` 为准。

`assets/` 保存物品数据、索引映射、翻译和贴图。`tools/extract_sprites.py` 从本地 Oracle 工程提取贴图，保留画布几何和物品原点，供 GUI 正确旋转和定位。游戏更新后的内存布局、物品索引与资源版本需要分别复核。

## 源码、参照与项目结构

```text
core/                       游戏读取、操作、历史解析、记录器与阵容序列化
gui/                        自动游玩桌面界面
backpack_native/            v0.6.0 原生绑定、版本化数据、校验清单与 GUI
simulator/                  旧模拟器适配层、CLI、数据管线和战报渲染
gd_core/、gd_core_items/     旧版无头 GDScript 战斗逻辑与物品脚本
gd_core_py/                 Python 转写与本地 Cython 扩展
gd_core_test/               旧版基准与对齐重放器
native_sim_cpp/             旧 C++ 构建链和比较工具输入
trainer/                    摆盘规则、评估器、搜索和实验报告
gripper/                    对局缓存采集、解码与数据库工具
assets/、lineups/            运行时资源与示例阵容
tools/、docs/                逆向、生成、验证、性能工具与文档
output/_v1110/              本地 1.1.10 源码、构建树、录制与验收
dist/                       本机发布包和训练运行时
_archive/20261119/          本地历史工程、实验与旧包归档
```

| 源码或构建树 | 定位 |
|---|---|
| 本地 `output/_v1110/decompiled` | 当前安装版 1.1.10 反编译源码 |
| 本地 `output/_v1110/sim_native/native_sim_cpp/` | 当前优化 C++ 源码、原生运行时和生成器 |
| 根目录 `decompiled_full/` | 1.1.7 反编译文本；仍为旧生成器与资源重建输入 |
| 根目录 `oracle/` | 1.1.9 插桩工程；服务旧录制、资源提取与验证 |

旧版逻辑、数据和贴图的版本关系见 [版本对齐说明](docs/version_alignment.md)。这些树有不同依赖与插桩，整理时应先检查调用关系。

## 构建、验证与维护

原生发布包使用匹配的 DLL、绑定源码与运行数据。构建前将已验收 `native_hot_path.dll` 放入 `backpack_native/libgdcore.dll`，确认与 `manifest.json` 的 SHA-256 一致。完整本地构建树中的优化配方为 `output/_v1110/rebuild_native_lovers_candidate.py --native-hot-path`；Git 保留阶段修复脚本与验收报告。

```powershell
# 需要 setuptools、wheel、PyInstaller，以及匹配的本地运行时
python tools/build_native_release.py
python tools/verify_native_release.py
.\dist\BackpackSimulator.exe --selftest selftest_report.json

# 其它组件的历史构建入口
python build_exe.py
python build_combatlog_exporter_exe.py
python build_simulator_exe.py
```

`build_simulator_exe.py` 构建旧版 GUI，也会写入 `dist/BackpackSimulator.exe`；按所需版本选择构建入口。发布验证脚本检查 EXE 与 wheel 的完整性，并在临时目录中运行部署后的自检，结果见 [发布包验收记录](docs/release_v0.6.0_verification.json)。

一致性工作以原版行为为参照，修复后先定位用例，再回归全部语料；速度优化需保留逐事件语义，记录固定负载下的墙钟、CPU 时间和内存。历史工具包括 `tools/_cpp_verify_events.py`、`compare_truth.py`、`per_item_diff.py`、`verify_oracle.py`，运行时应核对版本、语料与路径。

历史工程和旧包已逐项归档到本机 `_archive/20261119`，映射见 [归档清单](docs/workspace_archive_20261119.json) 和本机归档目录的 `manifest.json`。旧工具引用归档路径时需先恢复对应输入。归档目录、真实存档、数据库和大部分运行产物由 `.gitignore` 排除；冻结录制与本地游戏资源需要单独保管。

## 文档导航

| 主题 | 文档 |
|---|---|
| 当前战斗修复与验收 | [战斗触发与时序四方对齐计划](docs/战斗触发与时序四方对齐计划.md) |
| 摆盘训练与后续路径 | [训练路径规划](docs/训练路径规划.md)、[训练初步报告](trainer/训练初步报告.md) |
| 阵容、数据与日志格式 | [模拟器架构](docs/simulator_architecture.md)、[官方语料格式](docs/corpus_official_format.md) |
| 真人记录与标尺样本 | [记录器设计](docs/recorder_design.md)、[标尺任务书](docs/摆盘标尺样本采集_开发任务书.md) |
| 原版机制与 RNG | [gd_core 真值](docs/gd_core_truth.md)、[战斗机制真值](docs/engine_truth.md)、[RNG 真值](docs/rng_truth.md) |
| 历史对齐方法与证据 | [np24 留档](docs/np24_fix.md)、[扩样进度](docs/expand_fix_progress.md)、[版本对齐](docs/version_alignment.md) |
| 逆向、采集和编译 | [逆向报告](docs/reverse_engineering_2026-09.md)、[采集说明](gripper/README_fixed.md)、[Cython 构建](docs/build_cython_用法.md) |
| 发布与归档 | [v0.6.0 说明](docs/release_v0.6.0.md)、[发布验收](docs/release_v0.6.0_verification.json)、[归档映射](docs/workspace_archive_20261119.json) |

历史文档保留当时的版本、结论与待办，当前状态以对应版本的最新验收记录为准。本项目用于学习研究。
