# 模拟器版本对齐现状（2026-10-29 实测）

> 本文回答一个问题：**模拟器到底对齐 1.1.7 还是 1.1.9？**
> 答案：**分面混合**——行为逻辑基底 = 1.1.7，数值/占格/真值对照 = 1.1.9。
> 逐面证据如下（全部由现场 grep + 数据抽查得出，非文档推断）。

## 一、总览

| 面 | 版本 | 证据 |
|---|---|---|
| 物品行为脚本（`gd_core_items/`） | **1.1.7** | 生成器 `tools/build_item_scripts.py:47` 的 `SRC = decompiled_full/Items` |
| 内核基类（`gd_core/`） | **1.1.7** | 同上转译链；`gen_core_item_book` 也读 `decompiled_full/Sheets/ItemBook.gd` |
| 物品数值（`battle_items.json`） | **1.1.9** | `simulator/build_data.py:23` 的 `CSV_PATH = oracle/Sheets/CSV/ItemData.csv` |
| 占格/影响格（`collision_cells`/`affected_cells`） | **1.1.9** | `simulator/extract_grid.py:26` `EXTRACTED = oracle/Items`（np24 根因A2 修复） |
| 宝石槽数（sockets） | **1.1.9** | `tools/gen_lineup_fixture.py:72` `EXTRACTED_ITEMS = oracle/Items`（np23 data_r1） |
| 真值对照神谕（oracle） | **1.1.9** | `oracle/Core/Game.gd:10` `var VERSION = "1.1.9"` |
| 物品索引表（静态） | 1.1.7 生成但**与 1.1.9 id 全等** | 518/518 与 1.1.9 CSV 的 `id` 列一致 |
| 物品索引表（活体） | 1.1.9 | 519 条、含 Time Pendant，与 1.1.9 CSV id 519/519 一致 |
| UI 贴图（`assets/sprites`） | **1.1.9** | `tools/extract_sprites.py` `SRC_ROOT = oracle` |

## 二、为什么逻辑留在 1.1.7

`oracle/` 是**插桩过**的神谕工程：11 个 `.gd` 含
`ORACLE HARNESS`/`oracleRngLog`/`oracleTimeLeft`/`B2_SHUF_DBG`/`ORACLE_PROC_DEBUG`；
`decompiled_full/` 全树 **0 处**插桩。用两棵树各跑一次 `build_item_scripts`，
产物只差 5 个文件（Eggscalibur/AmuletofDarkness/Eat-o-matic/EchoingBattlecry/Item）
+ 1 个新增（TimePendant），差异内容正是那些调试块与空桩。

**结论**：两版物品逻辑本身几乎无行为差异（差异来自插桩而非版本），
所以"逻辑留在 1.1.7 纯净树 + 数值/占格取 1.1.9"是当前最稳的组合。

## 三、数值确实落在 1.1.9（抽查证据）

1.1.9 与 1.1.7 两份 `ItemData` 的真实差异（按列统计物品数）：
`p2` 13、`cd` 12、`p3` 11、`maxDam` 4、`p1` 4、`p4` 4、`chance` 4、`minDam` 3、`block` 2…
抽查 `battle_items.json` 落到 **1.1.9** 侧：

| 物品 | 1.1.7 | 1.1.9 | battle_items 实际 |
|---|---|---|---|
| Cat Spirit | cd=2.4 | cd=2.1 | **2.1** |
| Dragonskin Boots | block=20 | block=25 | **25** |
| Hogus Bogus | p1=8 / p4=0.5 | p1=6 / p4=0.8 | **6 / 0.8** |
| Wisp | p5=30 | p5=32 | **32** |
| Long Spear | max_dam=12 | max_dam=16 | **16** |

**系统核查（不是抽查）**：把 `battle_items.json` 的
`cd`/`max_dam`/`min_dam`/`block`/`stamina_cost`/`price` 六类字段
与 `oracle/Sheets/CSV/ItemData.csv`（1.1.9）逐物品对拍：

> **3104 / 3104 全部一致，0 处不一致。**

即数值面**已完整对齐 1.1.9**（`price` 两版就相同，不构成判据）。
（注：字段名是下划线风格 `max_dam`/`min_dam`/`stamina_cost`，早期核查若误用驼峰名
会查不到值而误判，此处已订正。）

## 四、唯一已知缺口

`Time Pendant`（1.1.9 新增物品）：
- 贴图/条目：**已有**（`assets/sprites/TimePendant.png`、`item_db.json` 「时间吊坠」）
- 内核脚本：**无**（`gd_core_items` 0 命中）
- 战斗数值：**无**（`battle_items` 518 条不含它）
- 台账口径：`docs/np24_issue_ledger.md` P1-2 「Time Pendant 语料零引用不处理」

即：**当前 914 场对齐语料里一次都没出现它**，故不影响 279/914 的成绩；
但若将来语料包含它，会因缺脚本/数值而装配失败。

## 五、文档滞后提示

代码与文档里仍有若干「1.1.8」字样（`tools/verify_oracle.py` 文件头、
`docs/oracle_workflow.md`），指的都是**同一个 oracle 工程**，而该工程
`Core/Game.gd` 现为 `VERSION = "1.1.9"`（`git log 67b9d59d`：「oracle 1.1.9 终建」）。
这些是**历史文案遗留**，不是另有 1.1.8 树。

## 六、运行时面（主程序/GUI）：面向 1.1.9 运行游戏

主程序不跑模拟器，它读**运行中的游戏**，因此天然面向 1.1.9：

| 机制 | 版本鲁棒性 |
|---|---|
| 物品索引（`item_index_map_live.json`） | 由 `core/build_history.live_item_index_map()` 从**运行中游戏**的 `ItemBook.descriptorList` 实测生成（519 条），天然跟随版本；静态表 `item_index_map.json` 虽标 v1.1.7，但与 1.1.9 的 `id` 列 **518/518 全等**，可安全回退 |
| 物品贴图/中文名 | `ItemDB` ← `assets/item_db.json`（1.1.9 提取，521 条含 Time Pendant） |
| 商店价格解码 | `core/godot_reader.py` 的 `Game.gd:4784` encode 公式（1:1 复刻），1.1.7/1.1.9 该公式一致 |
| 占格（GUI 摆盘校验） | `item_db.cell_px` ← 1.1.9 tscn |

**即：主程序 = 纯 1.1.9 面向。** 只有模拟器内核是 1.1.7 逻辑基底。

## 七、一句话结论

> 模拟器 = **逻辑按 1.1.7 转译 + 数值/占格/贴图/真值对照全部按 1.1.9**，
> 对齐成绩 279/914 是"对 1.1.9 神谕"的成绩；唯一缺口是 1.1.9 新增的 Time Pendant（语料零引用）。
