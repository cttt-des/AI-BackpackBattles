# Backpack Battles 战斗模拟器

v0.6.0 提供针对游戏 **1.1.10** 的 Windows x64 原生 C++ 模拟器，以及 Python wheel。旧版自动游玩、战报导出与 Python/Cython 工具保留在仓库中。

## 下载和使用

- [BackpackSimulator.exe](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.6.0/BackpackSimulator.exe) 打开后选择玩家、对手的 v3/v4 阵容 JSON，设置起始种子和场数，查看胜率并保存逐场结果 JSON。界面使用单线程 C++ 批量内核，计算在后台执行。
- [Python wheel](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.6.0/backpack_battles_sim-0.6.0-cp314-cp314-win_amd64.whl) 适用于 CPython 3.14、Windows x64。

```bash
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
```

新版原生 GUI 输出胜率、胜负、时长和事件数量。旧 GUI 的游戏格式战报文本功能可使用 v0.5.4 发布包。wheel 中原有 `simulator` 接口保留旧 Python 内核语义，新版 C++ API 使用 `backpack_native`。

## 验收和性能

- 同一优化 DLL 完成基准 **914/914**、扩展 **1690/1690**，合计 **2604/2604** 逐事件验收，涵盖事件顺序、数值、因果链接、普通物品与宝石来源、胜负和自然终局。
- 验收使用冻结录制的阵容和初态。参照来自恢复的 1.1.10 工程，主要运行于复制的发行版 EXE，扩展保留 785 场通用 Godot 3.6 录制。相关宿主 RNG 输入按录制边界重放。
- 无录制输入的批量模拟从固定启动模型按种子运行，已核对单场、单线程和双线程批量的确定性。
- 本机 i5-8265U，固定 200 场、单线程、三轮交替对照，优化版中位 **38.31 场/秒**，最慢 **35.99 场/秒**。同轮基线中位 14.39 场/秒，每批 CPU 时间下降 62.5%，峰值工作集约 80.1 MiB。实际速度随阵容与硬件变化。

[逐事件总账](output/_v1110/native_hot_path_full_gate.json) · [性能记录](output/_v1110/native_hot_path_benchmark.json) · [修复与验收过程](docs/战斗触发与时序四方对齐计划.md)

## 开发与构建

原生发布包包含 `backpack_native/sim.py`、版本化数据和同一份已验收 DLL。DLL 为本机构建产物，源码修复、原生运行时和生成器在 `output/_v1110/sim_native/native_sim_cpp/`，构建配方为 `output/_v1110/rebuild_native_lovers_candidate.py --native-hot-path`。本地完整工作区保留这些输入，Git 中保存阶段修复脚本与验收报告。

```bash
python tools/build_native_release.py
BackpackSimulator.exe --selftest selftest_report.json
```

构建前将已验收的 `native_hot_path.dll` 放入 `backpack_native/libgdcore.dll`，与 `manifest.json` 的 SHA-256 一致。构建需要 setuptools、wheel 和 PyInstaller。发布 EXE 和 wheel 均包含 DLL。

## 工作区和历史版本

- `output/_v1110/decompiled` 保存安装版 1.1.10 的源码，`sim_native` 保存当前优化构建树。
- 根目录 `decompiled_full` 为 1.1.7，`oracle` 为 1.1.9 插桩工程。它们仍是旧生成器、资源提取和验证入口的输入。
- 根目录 `gd_core`、`gd_core_items`、`gd_core_py`、`native_sim_cpp` 支撑旧 Python/Cython、GUI 和比较工具。迁移这些调用前保留原路径。
- 历史实验工程、旧语料输出和旧发布包归档到本机 `_archive/20261119`，逐项原路径见该目录 `manifest.json`。需要复现历史工具时先恢复相应路径。归档目录被 Git 忽略。
- 新版原生 API 与旧版构建链有各自的数据和语义。选择对应版本的验证入口。

旧发布说明和旧 README 可从 Git 历史查看。项目用途为学习研究。
