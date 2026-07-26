# 背包乱斗 AI — 项目记忆

## 项目概述
为游戏《背包乱斗》(Backpack Battles) 打造的外置 AI 机器人。不修改任何游戏文件，通过进程内存读取和坐标操作自动游玩。

## 技术栈
- **游戏引擎**: Godot 3.6.0 (x86-64, GDEC加密脚本)
- **语言**: Python 3.13
- **输入**: pyautogui (鼠标/键盘模拟)
- **内存**: ctypes + kernel32 ReadProcessMemory
- **GUI**: tkinter 原生桌面应用（深色主题）；★ 已从 Flask+SocketIO Web 控制台重构为原生 GUI

## 架构
```
游戏进程 ← 内存读取 + pyautogui输入 → Python Bot ← queue/线程 → tkinter GUI
```

## 项目结构
```
core/           — Python 核心模块
  bot.py        — 主机器人循环
  memory_reader.py — 进程内存读取（ctypes.Structure 版 MBI，含正确 argtypes）
  window_manager.py — 窗口管理+UI坐标计算
  actions.py    — 游戏操作（点击/拖拽/按键）
  state_tracker.py — 独立状态模型
  ai_interface.py — AI决策接口（Heuristic + LLM预留）
  paths.py      — 开发/打包路径兼容
gui/            — ★ 原生 GUI（当前入口）
  app.py        — BackpackAIApp 主窗口（状态卡+背包Canvas+日志+控制按钮）
  theme.py      — 深色主题配色/字体
dashboard/      — Web 控制台（旧方案，已弃用但保留）
tools/          — 逆向分析工具（ECFG解析/PCK提取等，已存档）
bridge/         — 桥接脚本（PCK注入方案，已存档）
launcher.py     — exe 入口（启动 gui.app.run）
build_exe.py    — 一键打包（--windowed，输出 dist/BackpackAI.exe ~13MB）
config.yaml     — 配置文件
```

## 关键决策
- 外置模式：不修改游戏文件，不依赖视觉识别
- 内存读取：金币/HP/回合 + 物品清单均结构性读取（core/item_reader.py）
- ★ 用户偏好：构建产物直接留在工作空间 dist/，不要单独 present exe 让用户另存
- AI 默认使用启发式策略（最便宜优先），预留 LLM 接口
- ★ GUI 改为 tkinter 原生应用（内置无额外依赖），Bot 后台线程 + queue 刷新 UI
- 打包用 PyInstaller --windowed --onefile；覆盖旧 exe 前先用 PowerShell Stop-Process 杀进程

## Godot 内存布局（2026-07-26 活体标定，本机 exe 构建有效）
```
OS::singleton RVA = 0x1eba290（版本更新会漂移，可自动扫描重定位）
链路: base+RVA → OS → +0x1d0 main_loop(SceneTree) → +0x148 root Viewport
     （注意 +0x230 是 current_scene 不是 root！）
Node: parent=+0xf0（非 0x8）, children=Vector<Node*>(CowData)@+0x108,
      name(StringName)=+0x130→_Data→String@+0x10(UTF-16), script_instance=+0x58
GDScriptInstance: script Ref=+0x10, members Vector<Variant>=+0x20
CowData: 元素数在 _ptr-4 (uint32)；Variant=24B (type u32 + union@+8)
Game = root.children[8]（autoload，按 res://Core/Game.gd BFS 定位更稳）
成员下标: gold=72, hp=68, round=65（簇 65..68=回合/胜/负/生命）
Node2D: 局部pos=+0x270(2×f32), 全局origin=+0x260；背包格80px
物品树: Main/Player/<物品>=摆盘, Main/Shop/Storagebox/<物品>=储物箱,
       Main/Shop/Items/<物品>=商店；物品脚本 res://Items/*.gd, 节点名=显示名
格坐标 = floor((物品pos − Player/Inventory pos(50,60)) / 80)
排除: SocketsNode/GemSocket/BagBorder/GooglyEye/ItemPushZone、/Tiles/、/Animations/
```

## 使用方式
```bash
python launcher.py            # 原生 GUI（推荐）
python -m gui.app             # 同上
python -m core.bot --verbose  # 命令行模式
python build_exe.py           # 打包/更新 exe → dist/BackpackAI.exe
```
