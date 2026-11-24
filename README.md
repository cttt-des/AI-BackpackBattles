# Backpack Battles AI（背包乱斗 AI）

面向 Windows 的《背包乱斗》工具集：读取游戏状态、导出真实战报、记录对局、运行战斗模拟，以及研究摆盘搜索与训练。当前原生模拟器发布版本为 **v0.6.1**，战斗内核面向游戏 **1.1.10**。

## 原版解包源码在哪里

从 2026-11-24 起，**当前安装版 1.1.10 的解包源码统一放在根目录 `decompiled_full/`**。旧版本保留独立快照，生成器按版本读取，避免换目录时连带改变旧内核的输入。

| 路径 | 版本与用途 |
|---|---|
| `decompiled_full/` | 当前安装版 **1.1.10** 的解包工程；查阅新版源码和资源的入口 |
| `decompiled_legacy/1.1.7/` | 原根目录解包树的完整保留副本；旧 GDScript/Python 生成与审计工具固定读取这里 |
| `oracle/` | **1.1.9** 插桩工程；旧录制、资源提取与对照使用 |
| `output/_v1110/decompiled/` | 本机兼容目录链接，指向 `decompiled_full/`；沿用旧路径的 1.1.10 工具仍可运行 |
| `output/_v1110/oracle_project/` | 本机恢复的 1.1.10 录制工程，包含插桩；与解包快照分别维护 |
| `output/_v1110/sim_native/native_sim_cpp/` | 本机当前 1.1.10 C++ 优化与构建树 |

**来源边界：**1.1.10 快照来自本机已安装、带用户插件的游戏，Steam build 为 `26640819`。来源清单记录 `steam_depot_match=false`，因此不能将它称作经过 Steam depot 哈希认证的无插件原包。原 EXE/PCK 哈希、脚本解密数量和插件说明见 [1.1.10 来源清单](docs/decompiled_source_manifest_1.1.10.json)。这里的“当前”指本项目已核实的本地版本。

这次迁移完整移动本地解包树，保留二进制资源；Git 只收录脚本、场景、文本资源、配置与 CSV。克隆仓库后可以查阅源码，但运行完整 Godot 工程、重新录制和重建贴图仍需本地资源。

### 迁移校验与旧路径兼容

[迁移清单](docs/decompiled_sources_20261124.json) 保存迁移前两棵树的文件数、总字节数和集合 SHA-256。集合哈希包含排序后的相对路径、文件大小及逐文件 SHA-256；源码快照按原始字节保存，避免 Git 换行转换影响校验。

```powershell
# 克隆后的文本快照校验
python -X utf8 tools/verify_decompiled_sources.py

# 本机完整树校验（还需全部本地游戏资源）
python -X utf8 tools/verify_decompiled_sources.py --full
```

目录链接只存在于本机，不进入 Git。如果新工作区需要运行仍使用旧路径的 1.1.10 历史工具，在仓库根目录执行：

```powershell
# 仅在该路径尚不存在时创建；已有目录需先核对内容
New-Item -ItemType Junction -Path output/_v1110/decompiled -Target (Resolve-Path decompiled_full).Path
```

旧版生成器已显式固定到 `decompiled_legacy/1.1.7/`；不要将旧源码目录再指向新版，也不要仅通过更换输入目录重建旧运行时。新版行为升级需要配套迁移逻辑、数据、绑定和录制基准。历史文档中的 `decompiled_full/` 按当时版本理解，旧管线的版本关系见 [版本对齐说明](docs/version_alignment.md)。

## 项目能力与当前进度

| 模块 | 入口 | 状态与适用范围 |
|---|---|---|
| 原生战斗模拟 | `backpack_native/`、`native_simulator.py` | v0.6.1，1.1.10 C++ 内核；支持单场、固定种子、批量胜率与结果 JSON |
| 自动游玩 | `launcher.py`、`core/`、`gui/` | 游戏状态读取、启发式操作与桌面面板；升级游戏后需复核内存布局 |
| 真实战报导出 | `combatlog_exporter.py` | 从运行中游戏读取事件和阵容，输出游戏格式战报与 JSON |
| 对局操作记录 | `core/recorder.py`、`core/store.py`、`tools/corpus_*.py` | 记录并折叠买卖、刷新、锁定、合成与开战状态 |
| 历史采集 | `gripper/`、`core/build_history.py` | 解码历史与排行榜缓存，建立对手池；真实存档与数据库留在本地 |
| 摆盘搜索与训练 | `trainer/` | 合法性检查、随机种子共用评估、搜索、学习预筛和分层实验，仍在研究阶段 |
| 旧模拟器 | `simulator/`、`gd_core*`、`native_sim_cpp/` | 保留旧 Python/GDScript/Cython 管线；与新版原生运行时各有版本和输入 |

当前 1.1.10 原生内核的既有验收为基准 **914/914**、扩展 **1690/1690**，共 **2604/2604** 场逐事件一致，涵盖顺序、数值、因果链接、物品与宝石来源、胜负和自然终局。

该结论针对冻结阵容、初态和已观测宿主 RNG 边界重放；参照主要来自恢复工程运行于复制的发行版 EXE，扩展中保留 785 场 Godot 3.6 录制。新增版本、机制和场景仍需对应语料验证。无录制批量模拟使用固定启动模型，已有单场、单线程和双线程确定性检查。**本次源码迁移没有重新生成内核或重新宣称全量验收。**

[逐事件总账（本地）](output/_v1110/native_perf50/lazy_diagnostics_bundle/bundle_full_gate.json) · [修复与验收记录](docs/战斗触发与时序四方对齐计划.md) · [性能优化清单](docs/C++模拟器性能优化清单.md)

历史“1690 场三方对齐”指旧管线的 914 基线加 776 扩样；新版的 2604 场是 914 基线加 1690 扩展，阅读报告时请核对口径。

## 下载与运行

独立 EXE 无需安装 Python。历史发布包见 [GitHub Releases](https://github.com/cttt-des/AI-BackpackBattles/releases)。

| 组件 | 下载与用途 |
|---|---|
| v0.6.1 原生模拟器 | [EXE](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.6.1/BackpackSimulator.exe) · [wheel](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.6.1/backpack_battles_sim-0.6.1-cp314-cp314-win_amd64.whl)；1.1.10 C++ 内核 |
| v0.5.4 旧模拟器 | [EXE](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.5.4/BackpackSimulator.exe) · [wheel](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.5.4/backpack_battles_sim-0.5.4-cp314-cp314-win_amd64.whl)；旧 Python/Cython 内核及游戏格式战报 |
| v0.4.0 自动游玩 | [EXE](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.4.0/BackpackAI.exe)；历史 GUI 发布包 |
| v0.3.1 战报导出器 | [EXE](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.3.1/BackpackCombatLog_v0.3.1.exe)；真实战斗日志与阵容导出 |

v0.6.1 wheel 适用于 **CPython 3.14、Windows x64**，DLL 使用本机 i5-8265U 编译选项，建议使用支持 AVX2 的处理器。自动游玩和导出器的历史包需另外验证当前游戏兼容性。

打开原生模拟器 EXE，选择双方 v3/v4 阵容 JSON、起始种子与场数，即可计算胜率并保存逐场结果。Python 调用方式：

```powershell
pip install "https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.6.1/backpack_battles_sim-0.6.1-cp314-cp314-win_amd64.whl"
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

结果包括胜率、胜场数及逐种子的胜负、时长、事件数和超时标记。wheel 中的 `simulator` 接口仍使用旧内核语义；1.1.10 C++ API 入口为 `backpack_native`。

源码工作区的常用入口如下，按对应模块安装依赖并准备本地资源：

```powershell
python launcher.py                 # 自动游玩 GUI，连接运行中的游戏
python combatlog_exporter.py       # 真实战报导出至 output/combat_logs/
python native_simulator.py         # 原生模拟器 GUI，需要匹配的 DLL
python battle_simulator.py         # 旧版模拟器 GUI
python -m simulator.simulate player.json opponent.json --seed 42
python -m simulator.simulate player.json opponent.json --runs 100
```

旧内核支持事件 JSON、中英文游戏格式战报、`run_mc_pool` 和 `run_mc_mem`；构建见 [Cython 用法](docs/build_cython_用法.md)。

## 采集、记录与训练

主程序 GUI 可开始或停止对局记录，跟随真人或 AI，按买卖、刷新、合成、开战等决策点折叠，过滤摆放或锁定中的净零变化。配置在 `config.yaml` 的 `recorder:` 段。

| 路径（相对于 `output/records/<run_id>/`） | 内容 |
|---|---|
| `raw/` | 按回合分片的原始事件及压缩归档 |
| `corpus/decisions.jsonl` | 状态、净动作、下一状态与标签 |
| `corpus/lineups.jsonl` | 开战瞬时 v4 阵容与结果 |
| `corpus/traces.jsonl` | 可选摆盘轨迹，通过 `--traces` 导出 |

```powershell
python -X utf8 tools/corpus_fold.py output/records/<run_id>
python -X utf8 tools/corpus_check.py output/records/<run_id>
python -X utf8 tools/corpus_stats.py output/records/<run_id>
```

`gripper/` 处理本地 `runs_steam.cache`，`core/build_history.py` 处理游戏历史与回合阵容；筛选对手池时应核对职业、回合、段位和记录版本。[采集说明](gripper/README_fixed.md) 介绍数据库字段与 Windows 操作。`history/`、`database/` 和真人语料不进入 Git。

摆盘训练以**当前持有物品（含包）**为输入，搜索上场子集、包布局、位置和朝向，以给定回合及对手分布下的胜率评价。`trainer/` 已有 P0 合法性、P1 共用随机种子评估、P2 搜索、P3 学习预筛及 P4/P5 分层与换包实验。早期绝对胜率需结合回合、基础生命及职业映射修订阅读。

```powershell
python -X utf8 trainer/bench.py --n 200 --workers 1 --json output/perf/trainer_bench.json
python -X utf8 trainer/p2_search.py --workers 1
```

训练依赖本地数据库与运行时。`trainer/native_backend.py` 默认使用 `dist/native_1_1_10`，可通过 `BACKPACK_TRAINER_BACKEND` 选择后端；切换时核对 DLL、绑定、数据及清单。旧 `ai/` 是本地历史实验，当前研究入口以 `trainer/` 为准。

## 数据与目录约定

阵容采用 v4 平铺格式，兼容 v3 嵌套格式；`in` 指向承载袋的数组下标，`gems` 保存镶嵌宝石，`r`/`rotation` 为 0/90/180/270 度，位置对应旋转后占格左上角。字段见 [模拟器架构](docs/simulator_architecture.md) 与 `core/lineup.py`。

`assets/` 保存运行时数据、索引、翻译与贴图。旧资源提取器 `tools/extract_sprites.py` 继续读取 1.1.9 Oracle，缺失场景回退到 1.1.7 快照；本次源码迁移不会自动重建这些资源。内存布局、物品索引、贴图和内核数据需分别核对版本。

```text
decompiled_full/             当前安装版 1.1.10 解包源码与本地完整资源
decompiled_legacy/1.1.7/     旧生成链固定使用的源码快照
oracle/                      1.1.9 插桩录制与旧资源提取工程
backpack_native/             原生绑定、版本化数据、校验清单与 GUI
core/、gui/                  游戏读取、操作、记录与自动游玩界面
simulator/、gd_core*/         旧模拟器、转写与验证管线
native_sim_cpp/              旧 C++ 构建链及比较工具输入
trainer/、gripper/            摆盘研究与历史采集
assets/、lineups/             运行时资源与示例阵容
tools/、docs/                 生成、逆向、验证与文档
output/_v1110/               本地新版构建、录制、验收及历史实验
dist/                        本机发布包及训练运行时
_archive/20261119/           本机历史工程与旧包归档
```

## 构建与维护

原生发布包需要版本匹配的 DLL、绑定和运行数据。构建前，从已验收的 `dist/native_1_1_10` 同步至 `backpack_native/` 并核对 `manifest.json` 的 SHA-256；本机完整优化配方在 `output/_v1110/rebuild_native_lovers_candidate.py --native-perf50`。

```powershell
# 需要 setuptools、wheel、PyInstaller 和对应本地运行时
python tools/build_native_release.py
python tools/verify_native_release.py
.\dist\BackpackSimulator.exe --selftest selftest_report.json
```

其他组件历史入口为 `build_exe.py`、`build_combatlog_exporter_exe.py` 和 `build_simulator_exe.py`。其中旧模拟器构建也写入 `dist/BackpackSimulator.exe`，请按所需版本选择入口。

机制修复按用例定位、逐事件对照、全量语料回归推进；性能实验保留语义核验，并记录固定负载的墙钟、CPU 与内存。旧验证工具如 `tools/verify_oracle.py`、`tools/verify_cooldowns_gd.py` 继续采用各自的旧版输入，不能用于宣称新版内核已验收。

本地冻结录制、完整游戏资源与数据库需要单独保管。历史归档映射见 [归档清单](docs/workspace_archive_20261119.json)；恢复旧工具时需同时恢复它依赖的输入。

## 文档导航

| 主题 | 文档 |
|---|---|
| 源码迁移与来源 | [迁移清单](docs/decompiled_sources_20261124.json)、[1.1.10 来源](docs/decompiled_source_manifest_1.1.10.json)、[旧版对齐](docs/version_alignment.md) |
| 战斗修复与性能 | [四方对齐计划](docs/战斗触发与时序四方对齐计划.md)、[性能清单](docs/C++模拟器性能优化清单.md) |
| 训练与样本 | [训练路径](docs/训练路径规划.md)、[初步报告](trainer/训练初步报告.md)、[标尺任务](docs/摆盘标尺样本采集_开发任务书.md) |
| 格式与记录器 | [架构](docs/simulator_architecture.md)、[语料格式](docs/corpus_official_format.md)、[记录器](docs/recorder_design.md) |
| 机制与历史验证 | [gd_core 真值](docs/gd_core_truth.md)、[机制真值](docs/engine_truth.md)、[RNG](docs/rng_truth.md)、[np24](docs/np24_fix.md) |
| 构建与发布 | [v0.6.1](docs/release_v0.6.1.md)、[发布验收](docs/release_v0.6.1_verification.json)、[Cython](docs/build_cython_用法.md) |

历史文档保留当时的版本和结论。本项目用于学习研究。
