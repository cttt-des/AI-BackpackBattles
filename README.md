# Backpack Battles AI (背包乱斗 AI)

为游戏《背包乱斗》(Backpack Battles) 打造的外置 AI 机器人。**不修改任何游戏文件**，通过进程内存读取和鼠标/键盘模拟实现自动游玩。

---

## 功能特性

- **外置运行** — 无需注入或修改游戏本体，纯外部进程操作
- **内存读取** — 通过 `ReadProcessMemory` 直接读取游戏进程的金币、HP、回合、物品清单等状态
- **桥接注入** — 可选通过 PCK 补丁注入 GDScript TCP 桥接，在游戏进程内读取运行时数据（价格、联动等）
- **启发式 AI** — 默认采用启发式策略自动决策（买最便宜的物品、偏好武器、自动卖垃圾等），预留 LLM 接口
- **原生桌面 GUI** — 基于 tkinter 的深色主题桌面应用，实时显示状态、背包网格、日志
- **打包分发** — 支持 PyInstaller 一键打包为独立 EXE

## 项目结构

```
.
├── core/                      # Python 核心模块
│   ├── bot.py                 # 主机器人循环
│   ├── memory_reader.py       # 进程内存读取
│   ├── window_manager.py      # 窗口管理 + 坐标计算
│   ├── actions.py             # 游戏操作（点击/拖拽/按键）
│   ├── state_tracker.py       # 状态管理
│   ├── ai_interface.py        # AI 决策接口（启发式 + LLM 预留）
│   ├── item_db.py             # 物品数据库
│   ├── item_reader.py         # 结构性物品读取
│   ├── godot_reader.py        # Godot 引擎对象图遍历
│   ├── godot_probe.py         # Godot 运行时探测器
│   ├── game_state.py          # 游戏状态模型
│   ├── bridge_client.py       # 桥接 TCP 客户端
│   └── paths.py               # 路径兼容
├── gui/                       # 原生桌面 GUI
│   ├── app.py                 # 主窗口（状态卡 + 背包 Canvas + 日志 + 控制按钮）
│   └── theme.py               # 深色主题配色
├── tools/                     # 逆向分析工具集
│   ├── probe_godot.py         # Godot 内存偏移量自动标定
│   ├── extract_assets.py      # 游戏资源提取
│   ├── pck_extractor.py       # PCK 解包
│   └── ...                    # 其他调试/分析工具
├── bridge/                    # 桥接模块
│   ├── bridge.gd              # GDScript 桥接脚本（注入到游戏）
│   ├── inject.py              # PCK 注入核心逻辑
│   ├── injector_app.py        # 桥接注入器 GUI 桌面程序
│   └── __init__.py
├── dashboard/                 # Web 控制台（旧版，已弃用但保留）
├── assets/                    # 游戏素材（物品图标等）
├── extracted/                 # 游戏反编译分析文件
├── config.yaml                # 配置文件
├── launcher.py                # 主程序入口
├── build_exe.py               # 主程序打包脚本
├── build_bridge_injector.py   # 桥接注入器打包脚本
└── README.md
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

### 打包为 EXE

```bash
# 主程序（~76 MB）
python build_exe.py

# 桥接注入器（~11 MB）
python build_bridge_injector.py
```

输出到 `dist/` 目录。

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

## 待解决问题

- **物品联动的读取和显示** — 游戏中的物品联动效果（合成/增益组合）尚未能正确从内存中解析并展示在 GUI 上
- **商店物品的价格无法正确读取** — 商店界面中物品的售价字段位于加密 GDScript 的运行时数据中，静态反编译无法提取，目前价格显示异常

## 许可

仅供学习研究使用。
