# Backpack Battles AI (背包乱斗 AI)

为游戏《背包乱斗》(Backpack Battles) 打造的外置 AI 机器人。**不修改任何游戏文件**，通过进程内存读取和鼠标/键盘模拟实现自动游玩。

---

## 功能特性

- **外置运行** — 无需注入或修改游戏本体，纯外部进程操作
- **内存读取** — 通过 `ReadProcessMemory` 直接读取游戏进程的金币、HP、回合、物品清单等状态
- **导出阵容** — 将当前读取到的背包摆盘导出为 JSON 格式，可用于阵容分享与分析
- **启发式 AI** — 默认采用启发式策略自动决策（买最便宜的物品、偏好武器、自动卖垃圾等），预留 LLM 接口
- **原生桌面 GUI** — 基于 tkinter 的深色主题桌面应用，实时显示状态、背包网格、日志
- **桥接注入（可选）** — 通过 PCK 补丁注入 GDScript TCP 桥接，可在游戏进程内读取运行时数据（端口 19527）
- **打包分发** — 支持 PyInstaller 一键打包为独立 EXE

## 项目结构

```
core/                       # Python 核心模块
├── bot.py                  # 主机器人循环
├── memory_reader.py        # 进程内存读取
├── window_manager.py       # 窗口管理 + 坐标计算
├── actions.py              # 游戏操作（点击/拖拽/按键）
├── state_tracker.py        # 状态管理
├── ai_interface.py         # AI 决策接口（启发式 + LLM 预留）
├── item_db.py              # 物品数据库
├── item_reader.py          # 结构性物品读取
├── godot_reader.py         # Godot 引擎对象图遍历
├── godot_probe.py          # Godot 运行时探测器
├── game_state.py           # 游戏状态模型
├── bridge_client.py        # 桥接 TCP 客户端（可选）
└── paths.py                # 路径兼容
gui/                        # 原生桌面 GUI
├── app.py                  # 主窗口（状态卡 + 背包 Canvas + 日志 + 控制按钮）
└── theme.py                # 深色主题配色
tools/                      # 逆向分析 & 调试工具
├── extract_assets.py       # 游戏贴图资源提取
├── pck_extractor.py        # PCK 解包
├── sweep_offsets.py        # 版本更新时自动扫描偏移量
├── decrypt_gde.py          # GDEC 脚本解密框架
├── probe_godot.py          # Godot 运行时探测
├── find_game_node.py       # 自动定位 Game 节点
├── script_paths.py         # 脚本路径索引
├── dump_items.py           # 物品数据 dump
├── dump_game_full.py       # 完整游戏状态 dump
├── item_pos_probe.py       # 物品坐标标定
├── verify_item_pos.py      # 物品位置验证
├── scrape_items.py         # 营地/社区物品数据抓取
└── diag_singleton.py       # OS::singleton 偏移诊断
bridge/                     # 桥接注入模块（可选，已存档）
├── bridge.gd               # GDScript 桥接脚本
├── inject.py               # PCK 注入核心
├── injector_app.py         # 桥接注入器 GUI
└── __init__.py
dashboard/                  # Web 控制台（旧版，已弃用但保留）
assets/                     # 游戏素材（物品图标等）
├── sprites/                # 物品贴图
├── item_db.json            # 游戏提取物品数据库（483 个真实物品）
└── items_db_sim.json       # 导出阵容用物品校验库
docs/                       # 游戏机制参考文档
config.yaml                 # 配置文件
launcher.py                 # 主程序入口
build_exe.py                # 一键打包脚本
```

## 快速开始

### 环境要求

- Python 3.13+
- 游戏《Backpack Battles》已运行

### 安装与运行

```bash
# 安装依赖
pip install pyautogui pyyaml pillow

# 启动 GUI
python launcher.py

# 或直接使用核心模块（命令行模式）
python -m core.bot --verbose
```

### 导出阵容

在 GUI 界面中，点击「导出阵容 (模拟器 JSON)」按钮，将当前读取到的所有物品（摆盘 + 储物箱）保存为 JSON 文件，便于存档与分析。

### 打包为 EXE

```bash
# 一键打包（~73 MB，含全部资源）
python build_exe.py
```

输出到 `dist/BackpackAI.exe`。打包后无需 Python 环境，双击即可运行。

## 配置说明

编辑 `config.yaml` 调整 AI 行为和内存参数：

- **AI 策略**：`heuristic`（启发式）或 `llm`（需配置 API）
- **购买优先级**：`cheapest_first` / `highest_value` / `balanced`
- **Godot 内存布局**：已活体标定，通常无需手动调整

## 技术架构

```
游戏进程 ← 内存读取 + pyautogui 输入 → Python Bot ← queue/线程 → tkinter GUI
                     ↑
                 桥接 TCP (端口 19527，可选)
```

- 游戏引擎：Godot 3.6.0（x86-64，GDEC 加密脚本）
- 输入模拟：pyautogui（鼠标点击/拖拽/键盘）
- 内存读取：ctypes + kernel32 ReadProcessMemory
- GUI 框架：tkinter（深色主题）

### Godot 内存布局（活体标定）

```
OS::singleton RVA = 0x1eba290（版本更新会漂移，可自动扫描重定位）
链路: base+RVA → OS → +0x1d0 main_loop(SceneTree) → +0x148 root Viewport
Node: parent=+0xf0, children=Vector<Node*>(CowData)@+0x108,
      name=+0x130→_Data→String@+0x10(UTF-16), script_instance=+0x58
GDScriptInstance: members Vector<Variant>=+0x20, CowData 元素数在 _ptr-4
Game = root.children[8]（autoload，BFS 定位更稳）
成员下标: gold=72, hp=68, round=65
Node2D: 局部pos=+0x270(2×f32), 全局origin=+0x260；背包格80px
```

## 注意事项

- 物品联动和商店价格位于加密 GDScript 运行时数据中，静态提取受限，可选桥接注入方案突破
- 游戏更新后 `OS::singleton` 偏移可能变化，运行 `tools/sweep_offsets.py` 自动校准
- 本软件仅供学习研究使用，请勿用于违反游戏服务条款的用途
