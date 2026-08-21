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
- ★ 商店价格与联动功能：经核查逆向文件，关键数据（价格/打折字段、联动形状与匹配规则）位于加密运行期 GDScript 中，静态 tscn 无法提取，因此两项功能已被移除，不实现
- ★ 2026-07-27 桥接注入方案：通过 PCK 补丁注入 GDScript TCP 桥接（参考 bpb_enhance），在游戏进程内读取价格+联动运行时数据暴露给外部 Python bot。桥接端口 19527。见 `bridge/inject.py` + `core/bridge_client.py`

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

- ★ 2026-07-29 战斗模拟器（simulator/）已按用户要求删除。保留：「导出阵容」按钮（items_db 路径改为 assets/items_db_sim.json）、游戏机制参考文档（docs/game_mechanics_reference.md）、scrape_items.py
- ★★ 2026-08-18 **GDEC 脚本全部解密成功**！真实密钥 `8671424952511006d39f4c9e918f821391e2b06a80d946d693fb8757154ce849`（tools/script_key.txt）。exe 中混淆存储，运行时由 GDEC 解密函数重建；通过 hook 该函数入口（RVA 0x1621820）抓 this+0x20 的 Vector<uint8_t> 获得。815 个 .gde 全部解密+反编译成功 → `decompiled_full/`（含 Core/Combat.gd, Character.gd, Buff.gd, Game.gd 等完整战斗逻辑源码）。GDEC = AES-256-ECB 无 IV（[4 GDEC][4 ver][16 md5][8 len][密文]）。工具：C:/tmp/bb/grabkey.c + inject_cap.c；批量解密 tools/decrypt_gde.py --key ... --dir extracted --ext .gdc

## 使用方式
```bash
python launcher.py            # 原生 GUI（推荐）
python -m gui.app             # 同上
python -m core.bot --verbose  # 命令行模式
python build_exe.py           # 打包/更新 exe → dist/BackpackAI.exe
```

- ★★ 2026-08-19 **物品行为全量提取（4%→94.2%）**：`simulator/extract_items.py` 把 decompiled Items/*.gd（含 Exclusive/Gems 子目录）方法体转译成调用引擎 API 的 Python 函数，写入 battle_items.json 的 `behavior.methods`（`simulator/behavior.py` BehaviorExecutor 运行时编译执行，异常只告警）。关键约定：getP1()=get_p(0)（索引从0起）；GDScript `character()` → 引擎 `Item.character_`（`character` 是属性！）；preDealDamage_early 在命中判定后调（原版顺序）；引擎 API 签名对齐 GDScript 参数序（heal(amount, triggerEvent)）。信号系统：Character/Item 各带 connect_signal/emit_signal，connectForCombat 还原。check_triggers 在有 behavior 时跳过。剩余阶段2：网格邻接/宝石/联动（get_affected_items 暂返回空）。
- ★★ 2026-08-19 晚 **邻接联动+宝石已建模（阶段2完成）**：真值源 = tscn CollisionMap.tile_data（tile 2=Extension/bag占格、3=Collision、4=Affected、6=AffectedSecondary）+ Gem.gd。**40px 精细 tile → 80px 背包格 = 坐标 //2 合并**；tscn 格 (x,y)→背包格 (row,col)=(y+row,x+col)。占格=unique(归一化(旋转后碰撞格)//2)。lineup (row,col)=左上角。同名物品多份按 _lineup_entry 序挂载。宝石：宿主 prepare→gem.prepare→prepareWeapon/Armor/Inventory（按 getGemMode），嵌在武器/护甲上不走自身冷却；consume_potion 触发相邻药水联动。canAffect 执行行为函数（has_type 兼容 Type 枚举 int）。工具：simulator/extract_grid.py + grid.py + enrich_types.py（CSV 补 types/tags，506/518）。验证：8阵容×双向56场 0告警；示例 lineup_gem_test.json / lineup_potion_link_test.json。
- ★★★ 2026-08-19 晚 **冷却全面核对 + passive 重大 bug 修复**：① 战斗日志 to_text(dual=True) 默认双显示（[玩家]/[对手] 侧标，子事件继承）。② 冷却真相：adjustCooldown = cd×randf_range(0.95,1.05)（±5%，原版 Item.gd），递减乘 getSpeed（heat/cold 修正），trigger 累加补偿，60Hz。③ **CSV gain 列 = gainedStacks 联动标志（ItemBook.getFlags，canAffect 用 gainsStack 检查），NOT prepare 给 buff**——此前误提取为 passive 并在 prepare 给角色加 heat/cold/mana/spikes（176 物品双重叠加 + 冷却速度修正错误），已移除（build_data passive=None + item.py 删 _apply_passive + DB 清理）。④ tools/verify_cooldowns.py 全物品首触发 ∈ [cd×0.95, cd×1.05] 验证 271/271。⑤ 中文名补：Poison Bow=颠茄剧毒弓、Amulet of the Wild=自然护符；DamageResult camelCase 别名（triggerOnAttacked 等）。
- ★★★ 2026-08-19 深夜 **RNG 语义定论（用户确认）**：冷却时长固定 = cd，RNG 只决定同帧触发先后（combat.ordered_items shuffle+TriggerPriority）。原版 adjustCooldown 代码有 ±5%（exe 字节 0.95/1.05 double 相邻确认），但按用户对游戏实际行为的确认，模拟器 adjust_cooldown() 改为返回固定 get_cooldown()。速度修正（heat/cold/speed 加成）保留——onCombatStart 给 heat 的物品（Oil Lamp/Ruby Whelp/Dancing Dragon）首触发 = cd/speed。验证：tools/verify_cooldowns.py v2（状态链期望 vs 实战）271/271；4 把匕首同帧齐射。
- ★★★ 2026-08-20 **物品效果运行时 31 告警 → 0**（verify_cooldowns 274/274 ok）。流水线：`tools/regen_behaviors.py`（重转译全部行为）→ `tools/audit_effects.py`（编译级审计）→ `tools/verify_cooldowns.py`（实战级校验：274 有cd物品逐一上场 vs 空手对手，查首触发时间 ±0.03 及运行时异常）。关键架构约定：**脚本内定义的 sibling 方法经 `_item._behavior_call("Name",...)` 派发**（不能 `_item.<name>()`，行为方法不是 Item 的 Python 方法）；METHOD_RENAME 只映射引擎基类方法，sibling 跳过；多行 dict/list 字面量（onready/const）由 collect_instance_vars 按括号闭合收集；`Vector2`→`_Vector2(tuple)` 支持 .DOWN/.rotated()；`for i in X.size()` 需包 `_range_or_value`；`.size()`→`.__len__()`、`.pop_back()`→`.pop()`、`.duplicate()`→`.copy()`、`.append_array()`→`.extend()`；视觉方法（updateShaderRotation 等）进 skip 清单；buff 变化信号 event 为 None 时用 `_OriginEvent(item)` 包装（getOrigin 可用）；send_charge 只做"命中格物品 num_charges+1 + onChargeReceived"，电荷动画不建模。遗留：5 个无脚本物品（Leather Bag/Coins/Shortbow/Goobling/Superior Ring）为基类物品，效果由引擎基类承载（合法）；8 个商店/视觉方法编译失败不影响战斗。
