# Backpack Battles AI（背包乱斗 AI）

为游戏《背包乱斗》(Backpack Battles) 打造的外置工具集：**战斗日志导出器**（游戏内存只读 → 游戏同格式战报）、**战斗模拟器**（基于逆向真值的对战模拟）与**外挂 AI**（自动游玩）。不修改任何游戏文件。

## ⚠️ 已知问题（使用前必读）

模拟器尚未达到与游戏完全一致，当前存在以下**已知问题**：

1. **黏黏龙骑士（Dragon Knight）的冷却快进存在正反馈放大**。
   机制本身已按源码 1:1 复刻（每次场上物品激活，DK 冷却推进 15%），且 Twine(60% 链式激活)/Chili(heat 加速) 的联动环也已还原；但模拟器的随机数序列与游戏不一致，环增益的微小差异会被指数放大（实测 DK 攻击间隔衰减至 0.02s，真值稳定在 0.35s+）。完全收敛需要逐帧对齐游戏的 rng 序列。

2. **部分物品的效果仍有偏差。**
   518 个物品的行为虽由解包源码转译执行，但个别物品的数值、触发时序或条件判断仍与游戏实际表现有出入。

3. **模拟器对战结果请勿当作游戏的精确胜率参考**。自动验收探针（短场景固定用例）无法覆盖真实战斗中的信号时序问题——多个严重问题都是在工具全绿的状态下由实录对照发现的。

发现问题欢迎提 issue（附阵容 JSON 与种子可精确复现）。

## 下载（Releases）

打包好的独立 EXE 在 [GitHub Releases](https://github.com/cttt-des/AI-BackpackBattles/releases) 发布，无需 Python 环境：

| 版本 | 文件 | 说明 |
|------|------|------|
| **v0.3.1** | [`BackpackSimulator_v0.3.1.exe`](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.3.1/BackpackSimulator_v0.3.1.exe) | 战斗模拟器（阵容对战 / 蒙特卡洛胜率 / 物品联动 / 游戏格式战报） |
| **v0.3.1** | [`BackpackCombatLog_v0.3.1.exe`](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.3.1/BackpackCombatLog_v0.3.1.exe) | 战斗日志导出器（游戏内真实战斗 → 游戏同格式战报 + 原始事件 JSON） |
| **v0.3.1** | [`BackpackAI_v0.3.1.exe`](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.3.1/BackpackAI_v0.3.1.exe) | 外挂 AI 主程序（自动游玩 GUI） |

开发版随每次改动重新打包到 `dist/`（不带版本号）。

## 成果总结

### ① 逆向基础（GDEC 解密 + 全源码可读）

- **2026-09-18 全量重逆向**：以官方原版 `BackpackBattles.pck`（clean v1.1.7）为真值重新解包——**9377/9377 个文件全部提取，MD5 逐条目校验零缺失**；另对**运行版（1.1.8）pck** 完成同规格提取与脚本反编译（`extracted_running/decomp/`），支撑双版本真值对照
- **820 个 GDEC 加密脚本全部解密**（AES-256-ECB，脚本密钥经游戏进程 hook 动态确认，GDSC 魔数 + 全文件 MD5 双重验证）+ `ItemData_e.csv` 解密（518 物品行 MD5 吻合）
- **820/820 脚本反编译 + 3817 个资源全部转换成功**（`decompiled_full/`：.gd/.tscn/材质/翻译/着色器全文本可读）
- 内存布局活体标定：`OS::singleton` RVA 定位 → Godot 对象图遍历；密钥动态确认工具链：`tools/inject_gdec_hook.py`（x64 绝对跳转 hook，在启动解密风暴的约 29ms 窗口内捕获密钥）

### ② 战斗日志导出器（BackpackCombatLog）

游戏本身不把战斗日志落盘。本工具在游戏运行期间对 `CombatLog.events` 数组做**只读结构性读取**（Game 单例 → 按脚本路径锚定 CombatLog 节点 → 解析魔改 Godot 构建的 Variant/Array/Dictionary/对象槽内存布局），战斗结束后自动导出：

- `*.zh.txt / *.en.txt` —— 按 `CombatEvent.asText()` 复刻的游戏格式战报（中/英）
- `*.json` —— 原始事件流（id/时间戳/类型/origin/params）+ **双方阵容 JSON**（v4）

这些导出物同时是模拟器的**真值测试集**（见已知问题对照）。

### ③ 战斗模拟器（gd_core 内核）

- **战斗内核：`gd_core`** —— 原版战斗逻辑的 1:1 移植：运行版 .gde 逆向 → `gd_core/` 无头 GDScript 内核 → `tools/gd_to_py.py` 机械转写为 `gd_core_py/`。已用 56 局 Godot 基准逐字符校验（`tools/check_gd_core_engine.py`）
- 物品数据来自 `assets/gd_core_runtime.json`（531 件，含四色影响格/参数/转写形状）
- 输出：事件流 JSON、战斗结果 JSON、**游戏格式战报文本**（中/英，共享渲染层 `engine/log_text.py`）
- 桌面 GUI（`battle_simulator.py`）：阵容选择、镜像对战、蒙特卡洛胜率、开战前占格重叠预检
- 历史 `engine/`（自研转译内核）与 `simulator/combat.py` 旧内核已下线，文件保留作参考

### ④ 外挂 AI（自动游玩）

- 内存读取金币/HP/回合/**职业**；结构性物品读取精确捕获**位置、旋转、镶嵌宝石、袋内物品**
- 启发式策略自动决策（预留 LLM 接口）；tkinter 深色主题桌面 GUI；**游戏进程自动连接**（启动后自动发现并连接，无需手动点初始化）
- 一键导出 **v4 阵容 JSON**；**从游戏历史记录导出阵容**（解析 `history.db` 的 buildInfo 位流）与**导出历史界面当前查看的回合**（活体读取 BuildHistory 选中状态）
- 桥接注入（可选）：PCK 补丁注入 GDScript TCP 桥接，进程内读取运行时数据

### ⑤ 真值对照与验收工具链

| 工具 | 作用 |
|------|------|
| `tools/compare_truth.py` | 真值实录 ↔ 模拟器对照（同阵容多种子：胜负/时长/逐类型事件量分布） |
| `tools/per_item_diff.py` | 逐物品激活次数/伤害总量归因（单组真值 vs 模拟中位数） |
| `tools/verify_linkage.py` | 联动语义固定用例 | 
| `tools/audit_item_effects.py` | 源码→转译→运行时三层对账 |
| `tools/regression_baseline.py` | 固定种子 56 场战斗指纹比对（防回归） |
| `tools/check_gd_core_engine.py` | gd_core 内核 vs 56 局 Godot 基准逐字符校验 |
| `tools/repack_lineups.py` | 占格形状变更后内置阵容自动重摆 |

> 这些工具证明的是"改动没有引入回归"。与游戏行为的最终对齐以 `output/combat_logs/` 实录对照为准——多个严重问题正是在固定用例全绿的状态下由实录发现的。

## 项目结构

```
gd_core/                    # ★ 无头战斗内核（原版 GDScript 1:1 移植，531 件物品）
gd_core_py/                 # ★ gd_core 的 Python 机械转写（模拟器实际加载的内核）
gd_core_items/              # 物品行为脚本（gd_core 侧）
gd_core_test/               # Godot 基准对局结果（56 局逐字符校验用）
core/                       # 外挂 AI 核心（bot/memory_reader/item_reader/godot_reader/
                            #   combatlog_reader/build_history/item_db/…）
engine/                     # 共享渲染层（log_text 游戏格式战报/i18n）+ 历史转译内核（已下线）
simulator/                  # CLI/GUI 入口（simulate.py 单内核 gd_core）+ 数据管线
├── gd_core_engine.py       # gd_core 内核适配层
├── extract_linkage.py      # ★ 联动专项提取（四色影响格 + canAffect + 回调，含继承链）
└── build_data.py           # 从 wiki + 解包脚本生成 battle_items.json
combatlog_exporter.py       # 战斗日志导出器 GUI
build_exe.py                # 外挂 AI 打包        build_simulator_exe.py  # 模拟器打包
build_combatlog_exporter_exe.py  # 战斗日志导出器打包
launcher.py                 # 外挂 AI 入口        battle_simulator.py  # 模拟器 GUI 入口
bridge/                     # 桥接注入（可选）
decompiled_full/            # ★ v1.1.7 反编译源码 + 资源（全文本可读）
extracted/                  # ★ v1.1.7 原版 pck 全量原始提取（9377 文件）
extracted_running/decomp/   # ★ 运行版（1.1.8）反编译产物
assets/                     # 物品贴图、battle_items.json、gd_core_runtime.json、
                            #   item_index_map*.json（历史解码映射）、翻译表
dist/lineups/               # 内置与游戏历史阵容 JSON
tools/                      # 逆向工具 + 真值对照 + 验收链（见上表）
docs/                       # 逆向记录、内核真值（engine_truth/gd_core_truth/
                            #   engine_v2）、模拟器架构、阵容格式
```

## 快速开始

### 战斗日志导出器（游戏内真实战斗）

```bash
python combatlog_exporter.py   # 需游戏已开启；输出 output/combat_logs/
#   每场战斗一个子目录：双方阵容 JSON（v4）+ 游戏格式战报（zh/en）+ 原始事件流
```

### 战斗模拟器（不依赖游戏运行）

```bash
# 单场战斗（固定种子可复现）/ 蒙特卡洛 100 场
python -m simulator.simulate dist/lineups/毒矛冰\ 第18回合.json dist/lineups/猎鹰龙跳.json --seed 42
python -m simulator.simulate lineup_A.json lineup_B.json --runs 100

# 桌面 GUI（阵容选择、镜像对战、蒙特卡洛）
python battle_simulator.py

# 输出 *_log.json（事件流）、*_result.json（胜负/统计/HP 曲线）、*_log.txt（游戏格式战报）
```

### 阵容格式（v4 推荐，v3 兼容）

```jsonc
// v4：平铺简洁；`in` 指向承载袋的数组下标（袋内联动显式化）
{
  "version": 4,
  "name": "我的阵容",
  "character": "Ranger",
  "round": 12,
  "grid": [7, 9],
  "items": [
    { "id": "Leather Bag", "at": [3, 3], "r": 0 },
    { "id": "Bow and Arrow", "at": [3, 3], "r": 0, "in": 0, "gems": ["Chipped Ruby"] }
  ]
}
```

- `gems` — 镶嵌宝石；`rotation`/`r` — 角度制（0/90/180/270）
- `(row,col)` 为旋转后占格左上角（对齐游戏 `topLeftCell` 存档语义）
- v3（嵌套 `contents`）仍完全兼容；游戏历史导出的阵容即此家族

### 打包

```bash
python build_exe.py                        # 外挂 AI → dist/BackpackAI.exe
python build_simulator_exe.py              # 模拟器 → dist/BackpackSimulator.exe
python build_combatlog_exporter_exe.py     # 日志导出器 → dist/BackpackCombatLog.exe
```

## 注意事项

- 游戏更新后 `OS::singleton` 偏移可能漂移，运行 `tools/sweep_offsets.py` 自动校准；日志导出器用 `tools/probe_combatlog.py` 重标定
- 改动内核/物品数据后，跑验收链（verify_linkage → audit_item_effects → regression_baseline --check）防回归；行为对齐以 `output/combat_logs/` 实录对照（compare_truth）为准
- **模拟器对战结果受已知问题影响，与游戏实际结果存在偏差**
- 本软件仅供学习研究使用，请勿用于违反游戏服务条款的用途
