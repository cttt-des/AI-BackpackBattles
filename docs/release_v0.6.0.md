# v0.6.0 — 1.1.10 原生 C++ 内核 + 2604 场逐事件验收

Windows x64 战斗模拟器，支持阵容对战、批量胜率和逐场结果 JSON 导出。

## 修复

- 对齐 1.1.10 的战斗机制和物品数据，修复光剑同帧回调顺序、戒指恢复词条前的动态类型，以及临时减益到期后重扫剩余层数。
- 原生 GUI 提供玩家和对手阵容 JSON 选择、固定种子及场数设置、后台计算和结果保存。
- wheel 新增 `backpack_native.run_mc`，包含匹配的 DLL、版本化数据和校验清单。原有 `simulator` 接口保留旧 Python 内核语义。

## 性能

- i5-8265U 本机固定 200 场、单线程、三轮交替对照，中位 38.31 场/秒，最慢一轮 35.99 场/秒。
- 同轮优化前中位 14.39 场/秒，每批 CPU 时间从 13.70 秒降至 5.14 秒，峰值工作集从 85.1 MiB 降至 80.1 MiB。
- 优化固定枚举读取、不可变字符串和冷却循环的动态派发，保留事件顺序与数值运算语义。速度随阵容、硬件和后台负载变化。

## 确定性

- 同一 DLL 通过基准 914/914、扩展 1690/1690，共 2604 场逐事件核验，覆盖事件顺序、数值、因果关系、物品与宝石来源、胜负和自然终局。
- 参照为恢复的 1.1.10 工程的固定 60 Hz 录制，主要运行于复制的发行版 EXE。扩展保留 785 场通用 Godot 3.6 录制。验收按冻结初态和已观测宿主 RNG 边界重放。
- 独立种子模拟使用固定启动模型，已核对单场、单线程和双线程批量一致。

## 安装

- GUI 下载 `BackpackSimulator.exe`。选择 v3/v4 玩家和对手阵容 JSON 即可模拟。新版提供结果 JSON，旧版游戏格式战报文本可使用 v0.5.4。
- wheel 需要 CPython 3.14、Windows x64。原生 DLL 使用本机 i5-8265U 编译选项，建议具有 AVX2 的处理器。

```bash
pip install "https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.6.0/backpack_battles_sim-0.6.0-cp314-cp314-win_amd64.whl"
```

```python
from backpack_native import run_mc
result = run_mc(player_dict, opponent_dict, seed=42, runs=200, workers=1)
print(result["win_rate"])
```

发布包包含复杂阵容自检输入，可执行 `BackpackSimulator.exe --selftest report.json`。本地历史实验和旧包的归档映射见 `docs/workspace_archive_20261119.json`。
