# Backpack Battles AI (背包乱斗 AI)

为游戏《背包乱斗》(Backpack Battles) 打造的外置 AI 机器人 + 战斗模拟器。**不修改任何游戏文件**，通过进程内存读取和鼠标/键盘模拟实现自动游玩，并通过逆向工程还原了完整的战斗模拟系统。

---

## 功能特性

- **外置运行** — 无需注入或修改游戏本体，纯外部进程操作
- **内存读取** — 通过 `ReadProcessMemory` 直接读取游戏进程的金币、HP、回合、物品清单等状态
- **导出阵容** — 将当前读取到的背包摆盘导出为 JSON 格式，可直接作为模拟器输入
- **启发式 AI** — 默认采用启发式策略自动决策（买最便宜的物品、偏好武器、自动卖垃圾等），预留 LLM 接口
- **原生桌面 GUI** — 基于 tkinter 的深色主题桌面应用（BackpackAI + BackpackSimulator 双程序）
- **战斗模拟器** — 基于逆向源码 100% 复刻的战斗引擎，输入两个阵容 JSON 输出完整战斗日志 + 蒙特卡洛胜率
- **GDEC 脚本解密** — 已成功解密并反编译全部 815 个游戏加密脚本（`decompiled_full/`），战斗逻辑全源码可读
- **桥接注入（可选）** — 通过 PCK 补丁注入 GDScript TCP 桥接，可在游戏进程内读取运行时数据（端口 19527）
- **打包分发** — 支持 PyInstaller 一键打包为独立 EXE

## 项目结构

```
core/                       # 外挂 AI 核心模块
├── bot.py                  # 主机器人循环
├── memory_reader.py        # 进程内存读取
├── window_manager.py       # 窗口管理 + 坐标计算
├── actions.py              # 游戏操作（点击/拖拽/按键）
├── state_tracker.py        # 状态管理
├── ai_interface.py         # AI 决策接口（启发式 + LLM 预留）
├── item_db.py              # 物品数据库
├── item_reader.py          # 结构性物品读取
├── godot_reader.py         # Godot 引擎对象图遍历
├── game_state.py           # 游戏状态模型
├── bridge_client.py        # 桥接 TCP 客户端（可选）
└── paths.py                # 路径兼容
simulator/                  # ★ 战斗模拟器（输入两阵容 JSON → 战斗日志+结果）
├── simulate.py             # CLI 入口
├── gui.py                  # 桌面 GUI 入口
├── combat.py               # 战斗引擎主循环（对齐 Game.gd + CombatTimer.gd）
├── character.py            # 角色（对齐 Character.gd takeDamage 全流程）
├── item.py                 # 物品（对齐 Item.gd 冷却/触发/武器模板）
├── effects.py              # 效果 DSL 执行器
├── behavior.py             # 物品行为方法运行时编译执行（Items/*.gd 转译）
├── buff.py                 # Buff 栈系统（对齐 Buff.gd）
├── damage.py               # DamageSource/DamageResult（暴击倍率 2.0）
├── rng.py                  # 平衡随机（对齐 BalancedRandom.gd）
├── events.py               # 战斗事件日志（对齐 CombatEvent/CombatLog）
├── lineup.py               # 阵容 JSON 加载/校验
├── grid.py                 # 背包网格/邻接/宝石（40px 精细 tile → 80px 背包格）
├── data.py                 # 物品/角色数据加载
└── build_data.py           # 从 wiki 数据 + 解包脚本生成 battle_items.json
gui/                        # 外挂 AI 原生桌面 GUI
├── app.py                  # 主窗口（状态卡 + 背包 Canvas + 日志 + 控制按钮）
└── theme.py                # 深色主题配色
bridge/                     # 桥接注入模块（可选）
├── bridge.gd               # GDScript 桥接脚本
├── inject.py               # PCK 注入核心
├── injector_app.py         # 桥接注入器 GUI
└── __init__.py
decompiled_full/            # ★ 815 个游戏脚本反编译源码（GDEC 解密成果）
├── Core/Combat.gd          # 战斗 UI/流程层
├── Core/Character.gd       # 战斗机制核心（伤害/暴击/抗性/疲劳）
├── Core/Game.gd            # 主游戏逻辑（138KB）
├── Items/                  # 全部物品脚本（含 Exclusive/、Gems/）
└── ...                     # 其余脚本（Interface/Utility/addons 等）
assets/                     # 数据与素材
├── sprites/                # 物品贴图（556 个 PNG）
├── battle_items.json       # 模拟器物品数据库（含行为方法转译）
├── items_db_sim.json       # 导出阵容用物品校验库
├── item_db.json            # 游戏提取物品数据库
├── characters.json         # 角色数据
├── zh_override.json        # 中文名覆盖表
└── zh_pairs.json           # 中英翻译对
examples/                   # 示例阵容 JSON（模拟器输入）
lineups/                    # 常用阵容 JSON（模拟器 GUI 选择列表）
output/                     # 模拟器运行输出（战斗日志/结果，可再生成）
tools/                      # 逆向分析 & 数据生成工具
├── decrypt_gde.py          # GDEC 脚本批量解密（AES-256-ECB）
├── dump_decrypted.py       # 解密脚本导出
├── dump_items.py           # 物品数据 dump
├── pck_extractor.py        # PCK 解包
├── sweep_offsets.py        # 版本更新时自动扫描偏移量
├── scrape_items.py         # 营地/社区物品数据抓取
├── regen_behaviors.py      # 物品行为全量重转译（Items/*.gd → battle_items.json）
├── audit_effects.py        # 效果编译级审计
├── verify_cooldowns.py     # 冷却实战校验（274 物品逐一上场验证）
├── parse_translations.py   # 游戏翻译文件解析
├── fix_zh_names.py         # 中文名修正
├── aes256.c/.h             # AES 参考实现
└── script_key.txt          # 解密密钥记录
dashboard/                  # Web 控制台（旧版，已弃用但保留）
docs/                       # 文档
├── game_mechanics_reference.md   # 游戏机制逆向参考
└── simulator_architecture.md     # 模拟器架构与阵容格式
config.yaml                 # 配置文件
launcher.py                 # 外挂 AI 主程序入口
battle_simulator.py         # 模拟器 GUI 入口
build_exe.py                # 外挂 AI 打包脚本
build_simulator_exe.py      # 模拟器打包脚本
```

## 快速开始

### 环境要求

- Python 3.13+
- 游戏《Backpack Battles》已运行（外挂 AI 模式需要）

### 外挂 AI（自动游玩）

```bash
# 安装依赖
pip install pyautogui pyyaml pillow

# 启动 GUI
python launcher.py

# 或命令行模式
python -m core.bot --verbose
```

### 战斗模拟器（不依赖游戏运行）

```bash
# 单场战斗（固定种子可复现）
python -m simulator.simulate lineups/lineup_dagger_swarm.json lineups/lineup_greatsword_tank.json --seed 42

# 蒙特卡洛胜率（100 场）
python -m simulator.simulate lineups/lineup_dagger_swarm.json lineups/lineup_greatsword_tank.json --runs 100

# 桌面 GUI（从 lineups/ 选择阵容）
python battle_simulator.py

# 输出
#   output/*_log.json      战斗过程日志（事件流）
#   output/*_result.json   战斗结果（胜负/血量/统计/HP 曲线）
#   output/*_log.txt       人类可读日志
```

### 导出阵容

在外挂 AI GUI 中点击「导出阵容 (模拟器 JSON)」，将当前读取到的所有物品（摆盘 + 储物箱）保存为 JSON，可直接作为模拟器输入。

### 打包为 EXE

```bash
python build_exe.py              # 外挂 AI → dist/BackpackAI.exe
python build_simulator_exe.py    # 模拟器 → dist/BackpackSimulator.exe
```

## 模拟器还原度

模拟器战斗逻辑逐行对齐 `decompiled_full/` 解包源码：

- **冷却系统** — 60Hz tick、物品独立触发、heat/cold 速度修正（274 物品全部实战校验通过）
- **伤害结算全链** — 命中/闪避/暴击×2.0/抗性/格挡/反伤/吸血/疲劳（14s→17s→每1s递增）
- **Buff 栈系统** — 抗性/反射/临时栈超时
- **物品行为 94.2%** — `Items/*.gd` 方法体自动转译为 Python（`behavior.py` 运行时编译执行）
- **邻接/联动/宝石** — 40px 精细 tile 网格 → 80px 背包格，宝石嵌槽、药水联动、`gainedStacks` 标志
- **RNG 语义** — 冷却时长固定 = cd，随机只决定同帧触发先后

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
- 脚本解密：AES-256-ECB（GDEC 容器，密钥已通过运行时 hook 获取）

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

## 待解决问题

- **物品联动的读取和显示** — 联动数据位于加密运行期 GDScript 中，静态提取受限，桥接注入方案可突破（见 `bridge/`）
- **商店物品的价格无法正确读取** — 价格/打折字段位于运行期数据，需通过桥接在游戏内读取

## 注意事项

- 游戏更新后 `OS::singleton` 偏移可能变化，运行 `tools/sweep_offsets.py` 自动校准
- 本软件仅供学习研究使用，请勿用于违反游戏服务条款的用途
