# Backpack Battles AI（背包乱斗 AI）

为游戏《背包乱斗》(Backpack Battles) 打造的外置 AI 机器人 + 战斗模拟器。**不修改任何游戏文件**：通过进程内存读取与输入模拟实现自动游玩，战斗模拟系统基于逆向工程逐行复刻。

## ⚠️ 已知问题（使用前必读）

模拟器尚未达到与游戏完全一致，当前存在以下**已知问题**：

1. **部分物品的效果仍然存在问题。**
   518 个物品的行为虽由解包源码转译执行，但部分物品的数值、触发时序或条件判断仍与游戏实际表现有出入，具体范围尚未完全摸清。

2. **物品之间的联动存在较大的错误**，包括但不限于：
   - **绳索（Rope）无法正确激活**；
   - **黏黏（Goobert 系）会错误地触发两次**（表现为联动治疗/效果翻倍）；
   - 其他联动类物品也可能存在类似的触发次数、触发时机错误。

   注意：自动验收探针（短场景固定用例）无法覆盖真实战斗中的信号时序问题，**模拟器对战结果请勿当作游戏的精确胜率参考**。

发现问题欢迎提 issue（附阵容 JSON 与种子可精确复现）。

## 下载（Releases）

打包好的独立 EXE 在 [GitHub Releases](https://github.com/cttt-des/AI-BackpackBattles/releases) 发布，无需 Python 环境：

| 版本 | 文件 | 说明 |
|------|------|------|
| **v0.1.2** | [`BackpackSimulator_v0.1.2.exe`](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.1.2/BackpackSimulator_v0.1.2.exe) | 战斗模拟器（阵容对战 / 蒙特卡洛胜率 / 物品联动） |
| **v0.1.1** | [`BackpackAI_v0.1.1.exe`](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.1.1/BackpackAI_v0.1.1.exe) | 外挂 AI 主程序（自动游玩 GUI） |

开发版模拟器随每次改动重新打包为 `dist/BackpackSimulator.exe`（不带版本号）。

## 成果总结

### ① 逆向基础（GDEC 解密 + 全源码可读）

- **2026-09-18 全量重逆向**：以官方原版 `BackpackBattles.pck.bak`（clean v1.1.7）为真值重新解包——**9377/9377 个文件全部提取，MD5 逐条目校验零缺失**
- **820 个 GDEC 加密脚本全部解密**（AES-256-ECB，脚本密钥经游戏进程 hook 动态确认，GDSC 魔数 + 全文件 MD5 双重验证）+ `ItemData_e.csv` 解密（518 物品行 MD5 吻合）
- **820/820 脚本反编译 + 3817 个资源全部转换成功**（`decompiled_full/`：.gd/.tscn/材质/翻译/着色器全文本可读）
- 内存布局活体标定：`OS::singleton` RVA 定位 → Godot 对象图遍历；密钥动态确认工具链：`tools/inject_gdec_hook.py`（x64 绝对跳转 hook，在启动解密风暴的约 29ms 窗口内捕获密钥）

### ② 外挂 AI（自动游玩）

- 内存读取金币/HP/回合/物品清单；结构性物品读取精确捕获**位置、旋转、镶嵌宝石、袋内物品**
- 启发式策略自动决策（预留 LLM 接口）；tkinter 深色主题桌面 GUI
- 一键导出 **v3/v4 阵容 JSON**（含 gems/contents/class_modifiers/round），直接喂给模拟器
- 桥接注入（可选）：PCK 补丁注入 GDScript TCP 桥接，进程内读取运行时数据

### ③ 战斗模拟器（v2 引擎）

- **v2 引擎（`engine/`）**：编译期代码生成（3174 个转译行为函数常驻 import）+ fail-fast（行为异常计入 failures 可观测）+ 无进程级单例（可 deepcopy/多进程，为 RL 铺路）。详见 [docs/engine_v2.md](docs/engine_v2.md)
- 60Hz 冷却系统（±5% 抖动）、伤害结算链（命中/闪避/暴击/抗性/格挡/反伤/吸血/疲劳）、Buff 栈、平衡随机 RNG、惰性事件日志、游戏格式战斗日志
- 物品行为由 `Items/*.gd` 方法体 AST 级转译为 Python 模块执行
- 物品联动（Affected）：四色影响格、脚本覆写 `getAffectedCellsAfterRotate`（含 extends 继承链）、`canAffect` 过滤、`onAffectedItemAdded` 回调、动态类型（**存在上述已知联动问题**）
- 桌面 GUI：阵容选择、镜像对战、开战前占格重叠预检
- 旧内核 `simulator/` 保留可回退（`--engine simulator`）

### ④ 验收工具链（防回归，非"与游戏一致"的证明）

| 工具 | 作用 | 状态 |
|------|------|------|
| `tools/verify_linkage.py` | 联动语义固定用例（已切 v2 引擎） | 18/18 通过（短场景，覆盖不了实战时序问题） |
| `tools/audit_item_effects.py` | 源码→转译→运行时三层对账 | 518 物品运行时 0 异常（不代表行为全对） |
| `tools/regression_baseline.py` | 固定种子 56 场战斗指纹比对（双内核 `--engine`） | 旧内核无差异 / 新内核基线可复现 |
| `tools/compare_engines.py` | 旧 vs 新内核同种子对照归因 | 56 场差异均有归因项 |
| `tools/repack_lineups.py` | 占格形状变更后内置阵容自动重摆 | 18 个阵容预检零冲突 |

> 这些工具证明的是"改动没有引入回归"，**不等于**"与游戏行为一致"——绳索/黏黏等联动问题就是在工具全绿的状态下由实测发现的。

## 项目结构

```
core/                       # 外挂 AI 核心（bot/memory_reader/item_reader/godot_reader/ai_interface 等）
engine/                     # ★ v2 战斗内核（gen/ 转译行为 + behavior/item/character/combat/context…）
simulator/                  # 旧战斗内核（冻结保留，回归对照基线）+ CLI/GUI 入口
├── extract_linkage.py      # ★ 联动专项提取（四色影响格 + canAffect + 回调，含继承链）
└── build_data.py           # 从 wiki + 解包脚本生成 battle_items.json
gui/                        # 外挂 AI 桌面 GUI（主窗口 + 深色主题）
bridge/                     # 桥接注入（可选）
decompiled_full/            # ★ 820 个反编译源码 + 全量恢复的场景/资源（clean v1.1.7）
extracted/                  # ★ 原版 pck 全量原始提取（9377 文件，MD5 校验零缺失）
assets/                     # 物品贴图、battle_items.json、角色数据、翻译表
lineups/                    # 内置阵容 JSON；dist/lineups/ 另含游戏历史导出阵容
examples/                   # 示例阵容
tools/                      # 逆向工具 + 验收链（见上表）+ 解密/解包/数据抓取
docs/                       # 游戏机制逆向参考、模拟器架构（engine_v2.md）、阵容格式
launcher.py                 # 外挂 AI 入口        battle_simulator.py  # 模拟器 GUI 入口
build_exe.py                # 外挂 AI 打包        build_simulator_exe.py  # 模拟器打包
```

## 快速开始

### 外挂 AI

```bash
pip install pyautogui pyyaml pillow
python launcher.py                # GUI（需游戏已运行）
python -m core.bot --verbose      # 或命令行模式
```

### 战斗模拟器（不依赖游戏运行）

```bash
# 单场战斗（固定种子可复现）/ 蒙特卡洛 100 场
python -m simulator.simulate lineups/lineup_dagger_swarm.json lineups/lineup_greatsword_tank.json --seed 42
python -m simulator.simulate lineup_A.json lineup_B.json --runs 100

# 桌面 GUI（从 lineups/ 选择阵容，支持同阵容镜像对战）
python battle_simulator.py

# 输出 output/*_log.json（事件流）、*_result.json（胜负/统计/HP 曲线）、*_log.txt（游戏格式战报）
```

### 阵容格式（v4 推荐，v3 兼容）

```jsonc
// v4：平铺简洁；`in` 指向承载袋的数组下标（袋内联动显式化）
{
  "version": 4,
  "name": "我的阵容",
  "character": "Ranger",
  "round": 12,
  "grid": [8, 10],
  "items": [
    { "id": "Leather Bag", "at": [3, 3], "r": 0 },
    { "id": "Bow and Arrow", "at": [3, 3], "r": 0, "in": 0, "gems": ["Chipped Ruby"] }
  ]
}
```

```jsonc
// v3（仍完全兼容）：嵌套 contents
{
  "version": 3,
  "meta": { "name": "...", "source": "...", "unknown_items": [] },
  "character": "Reaper",
  "round": 12,
  "class_modifiers": { "health": 100, "stamina": 50, "stamina_regen": 5 },
  "backpack": {
    "grid": { "rows": 8, "cols": 8 },
    "items": [
      { "id": "PoisonDagger", "row": 0, "col": 0, "rotation": 0,
        "quantity": 1, "container": false, "contents": [], "gems": [] }
    ]
  },
  "storage": []
}
```

- `gems` — 镶嵌宝石；`contents` — 袋内物品（递归同 schema）；`rotation` — 角度制（0/90/180/270）
- `(row,col)` 为旋转后占格左上角（对齐游戏 `topLeftCell` 存档语义）

### 打包

```bash
python build_exe.py              # 外挂 AI → dist/BackpackAI.exe
python build_simulator_exe.py    # 模拟器 → dist/BackpackSimulator.exe
```

## 配置说明

编辑 `config.yaml`：AI 策略（`heuristic`/`llm`）、购买优先级、Godot 内存布局（已活体标定，通常无需调整）。

## 注意事项

- 游戏更新后 `OS::singleton` 偏移可能漂移，运行 `tools/sweep_offsets.py` 自动校准
- 模拟器改动物品行为/占格逻辑后，跑一遍验收链（verify_linkage → audit_item_effects → regression_baseline --check）防回归
- **模拟器对战结果受上述已知问题影响，与游戏实际结果存在偏差**
- 本软件仅供学习研究使用，请勿用于违反游戏服务条款的用途
