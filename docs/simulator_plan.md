# 模拟器后续任务计划

> 更新：2026-09-09。本文件是战斗模拟器的工作路线图与工程约定。

## 工程约定（每次任务必须遵守）

1. **打包约定**：每次完成任务后，若改动涉及 `simulator/`、`assets/`、`battle_simulator.py`、
   `lineups/`，必须重新打包 exe：
   ```
   python build_simulator_exe.py
   ```
   输出固定为 `dist/BackpackSimulator.exe`（名称不变、不带版本号）。
   打包后烟测：确认 exe 能启动（GUI 进程出现）再收尾。
2. **验收四件套**（改动行为/联动/数据后必跑）：
   - `python tools/verify_timing.py` —— 冷却/时序不变量 5 用例（含"onready 不得
     覆盖引擎状态"通用防回归断言），全过才算完成；
   - `python tools/verify_linkage.py` —— 13 个联动对照用例，全过才算完成；
   - `python tools/regression_baseline.py --save` —— 重建基线（56 场 0 异常）；
   - `python tools/audit_item_effects.py` —— 运行时报错物品数不得回涨（当前 1：
     Time Dilator 孤立场景误报）。
   - ⚠️ 历史事故（2026-09-09）：onready typed_defaults
     （`_item.baseCooldownOverride=0.0` 等）经 `__setattr__` 重定向清零引擎
     冷却状态，所有物品每帧触发（"冷却只有 0.01s"）。根因之二：以
     `python simulator/extract_items.py` 直接运行时模块名为 `__main__`，
     `from .item import Item` 相对导入失败使过滤静默失效（已修，
     `_import_engine_item` 回退绝对导入）。
3. **数据再生成**：改 `simulator/extract_items.py` 转译规则后必须重跑
   `python simulator/extract_items.py`（会同时重建 `class_methods` 池）。
   注意该脚本会读写 `assets/battle_items.json`，不要并发运行。

## 当前状态（2026-09-09）

- 行为修复完成：GDScript 继承链（46 个基类脚本入 `class_methods` 池）、
  camelCase 属性重定向、onready 状态保护、约 20 个缺失战斗 API、
  战怒信号、电荷传播全部落地。
- 联动验证 13/13 通过；56 场阵容对战斗 0 异常；运行时报错物品 1（Time Dilator
  孤立场景误报，真实战斗不会触发）。
- 中文翻译：日志模板 40/41 条已换官方 `Interface.csv` 译文；buff 名按官方
  `Keywords` 表修正 6 处；官方物品名数据集已提取至
  `assets/official_zh_names.json` / `assets/items_zh_official.json`。

## P0 — 物品名翻译全量精确对齐（需要开游戏配合）

现状：`battle_items.json` 的 `zh` 字段仍有约 404 项与官方译名集（539 条）不匹配。
PHashTranslation 的私有 hash 无法离线复现，记录级配对率不足。

方案（按优先级）：
1. **运行时翻译表内存扫描**（推荐）：用户开启游戏进程并切到简体中文，
   用 `tools/live_scan.py` 扫描 `PHashTranslation.messages` 字典
   （msgid -> msgstr 的键值对在运行时是明文），直接导出全量英中对照。
   产出 `assets/items_zh_runtime.json`，与 `zh_override.json` 合并后写回 db。
2. 备选：逆向 Godot 的 bucket hash 函数（`func` 字段指示多个哈希函数之一，
   PHashTranslation 用 5 个哈希函数探测），离线复现后按 key 精确配对。
3. 兜底：以 `official_zh_names.json` + `zh_override.json` 人工校对剩余项。

验收：518 个物品的 `zh` 全部命中官方译名集；`tools/verify_linkage.py` 不回退。

## P1 — 战斗联动深水区（游戏对照验证）

- **Threat Drake/Gold Cube/Chrome Cube/Hogus Bogus/Laboratory/Wisp** 等依赖
  `getBaseCooldownIndex`（extraCds）的物品：CSV `extra_cds` 列尚未入库，
  需从 `ItemData_e.csv` 补列（`cd2`？确认列名）后重建数据。
- **Shop 阶段行为**（Amulet Unidentified 鉴定、Recombobulator、Anvil、
  Portable Altar、Random Loadout Bag）：当前模拟器只模拟战斗，
  这些物品的 `wasAddedToInventory/finishReplacement/pushToStorage` 等为安全空实现。
  若要做"整回合（准备+战斗）"模拟，需引入库存变更事件模型。
- **与游戏实测对照**：用户开游戏录制若干场对局（固定阵容），
  与模拟器同种子输出对比血量曲线/关键事件，产出偏差清单。

## P2 — 工程化与体验

- `tools/run_checks.py`：一条命令跑完三件套 + 数据再生成检查 + 打包，
  作为每次收尾的标准动作。
- GUI：日志双语切换按钮、影响格可视化叠加层（当前 GUI 已有基础）。
- 异常可见化：把 `BehaviorExecutor.failures` 暴露到 GUI 的诊断面板，
  避免静默降级难以察觉。

## 已知边界（有意为之，勿当 bug 修）

- Shop/合成阶段方法（`wasAddedToInventory`、`finishReplacement`、
  `pushToStorage`、`onCraft` 等）为安全空实现——战斗模拟不涉及。
- `adjustCooldown` 不含原版 ±5% 随机抖动（不影响结果正确性，见代码注释）。
- `Time Dilator` 在"背包无任何冷却物品"的孤立测试下会失败（真实战斗自身
  有冷却，不触发）。
