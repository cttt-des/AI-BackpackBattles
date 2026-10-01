# 背包乱斗 AI — 项目记忆

## 一句话
《Backpack Battles》外置 AI：逆向 .gde → `gd_core` 无头内核（GDScript）→ `gd_core_py` 转写 → 模拟器（**唯一内核 gd_core**）。取证文档 `docs/gd_core_truth.md`（17 道闸门、§6 已知偏差、§10-11）。

## 运行环境（每次会话必用）
- PATH 前缀：`export PATH="/c/Users/Windows/.workbuddy/binaries/PortableGit/versions/1.2.0/usr/bin:/c/Windows/System32:$PATH"`
- Python：`C:/Users/Windows/.workbuddy/binaries/python/versions/3.13.12/python.exe`（含 pycryptodome 的：`.../envs/default/Scripts/python.exe`）
- Godot 3.6：`output/godot36/Godot_v3.6-stable_win64.exe`；长命令一律 `timeout N`
- ★ heredoc 吞反斜杠 → 正则/脚本写成文件再跑；并行 Edit 同文件会丢改动；`rm -rf <dir>` 触发 SIGTERM
- 流水线：`python tools/run_gd_core.py` = 17 道闸门须 EXIT=0（≈8 分钟，后台跑扫 log）

## 核心资产与架构
- `decompiled_full/` 820 个 .gd = **权威源码**；GDEC 密钥在 `tools/script_key.txt`（另 `csv_key.txt`）
- `gd_core/`（GDScript 内核）+ `gd_core_items/`（503 份直挂物品脚本，逐字不改）+ `gd_core_py/`（Python 转写，转写器 `tools/gd_to_py.py`）
- `simulator/`：`simulate.py`（ENGINES=("gd_core",) 唯一内核，2026-09-28 收敛）/ `gd_core_engine.py`（事件桥 `_LogMixin`）/ `gui.py`（无内核下拉框）；`engine/log_text.py` = 共享渲染层（gd_core 也走它）；`engine/`、`simulator/combat.py` 旧内核文件保留但已下线
- `tools/build_item_scripts.py`：SALVAGE_FUNCS 点名抢救机制（整函数剥离误伤 → 语句级抢救；2026-09-28 救回 MagicRing.sortEffects/randEffects、ManaOrb.onManaChanged、AmuletofDarkness.onItemActivated、ChessPiece.onEliminatededBy）

## ★ 2026-09-28 修复台账
1. **坐标系互换（联动失效根因之一）**：`gd_core_engine._place_of` 与 `tools/gen_lineup_fixture.placement_of` 的 `occupied` 曾是 (row,col) 而 collision/affected 是 (x=col,y=row) → filledCells 键与 affected 查询格错位 → 1×1 物品 `getAffectedItems()` 恒空且零报错。已修（occupied 改 (x+col,y+row)）；`run_gd_py.py` 越界断言同步（x<10,y<7）。**两侧同源偏差，逐事件对照抓不到**
2. **Buff 信号名断裂（根因之二）**：`gd_core/CoreCharacter.gd` 把 Buff signalName 写成 `_stacks_changed_%d`（无订阅者）而物品脚本订阅原版名 `character_mana_changed` 等 → ManaOrb/Crown/Sapphire 等 ≥7 件静默失效。已修（就地反查 EventType 拼原版名）
3. **日志格式**：桥层 `_origin_key` 数字 origin 按 typeToKeyword keyword 化（fatigue 等，用 `kernel()["ET_NAME"]` ★不是 `_LogMixin._ET_NAME`——那是基类空 dict）；`log_text.py` 修 stamina 参数名（兼容 stamina/amount）、补 damage_buff/dam_increase/dam_reduction/temporary_max_stamina/battle_rage 分支、疲劳渲染 "Fatigue Damage: N"（官方 LOG_Health/LoseHealth/FatigueDamage/CriticalResisted/TemporaryMaxHealth 键**不存在**且 Util.tra 缺键返回空 → 原版这些行显示空文本，我们保留可读兜底已登记）
4. **stun 漏发信号（联动排查唯一实锤断点，已修 d3aff49）**：`CoreCharacter.stun()` 非抵挡分支曾 `ctx.bus.logEvent(event)`，应为 `ctx.bus.emitEvent(self,"character_stunned",event,[event])`（原版 Character.gd:1080）→ Dagger.onStun 静默失效。三副本同步（gd_core/gd_core_py/gd_core_test）
5. **zh 激活行可读兜底**：官方 LOG_Activation zh「{origin}以显示。」是机翻瑕疵 → log_text.py 渲染改「{origin}已激活。」（truth §6.22；判定不变）。联动系统性排查结论：**282 件联动物品信号订阅零断点**（verify_linkage_subs.py）；转写函数完整性 517 份零缺失（verify_transpile_funcs.py）；黑暗护符=上方扇形、魔法球=四角对角 = 原版机制非 bug

## ★ 铁律（多轮踩坑换来）
- **「零报错 ≠ 生效」**：信号/折叠没接上会安静跑完整场零报错 → 联动要靠激活计数取证
- **判据的判据**：「0 命中」= 真没有或扫描器坏了 → 0 命中即通过的判据必须配正对照
- **断言双侧**、生成物不写死核算结论（现算）、静态覆盖 ≠ 分支覆盖、注释里的 N 必须可现算（`survey_gd_syntax.py --verify` 21 个数字进流水线）
- **两侧同源偏差**：双引擎对照抓不到装配层共同错误
- GDScript `var speed` 与 `func speed()` 两张表可共存，Python 转写必崩 → R8 消歧 speed_v
- 生成器两个静默坑：mask_strings 先换字符串字面量（依赖引号的正则恒不命中）；find_block_end 纯缩进判块（多行字面量整行丢）
- Godot：只报首个 parse error；Nonexistent function 后继续跑退出码 0 → 必须扫 stdout；报错行号取自函数真正定义的脚本

## 尚不得宣称 gd_core 等价原版
双引擎逐事件一致（56 局）+ 冷却双取证已做；缺：① 517 件数值一致性（闸门 17 只判不崩）；② 物品自带分支无逐条对照；③ 冷却外判定路径无逐帧恒等式。张力 20（_physics_process 谓词）待活体观察原版。

## Godot 内存布局（2026-07-26 本机标定）
OS RVA=0x1eba290→+0x1d0 main_loop→+0x148 root；Node script_instance=+0xf0 parent/+0x58；GDScriptInstance members=+0x20；Game=root.children[8]；gold=72,hp=68,round=65；背包格 80px；格坐标=floor((pos−(50,60))/80)

## GitHub Release
`gh_tmp/bin/gh.exe`；凭据在 keyring（cttt-des/repo）无需 PAT；github.com 主站常挂但 api/uploads 稳定；流程：create --draft → upload --clobber → edit --draft=false；判定下载可用以「实测 HTTP 200」为准；已发 v0.0.1~v0.3.0

## 用户偏好（工程）
「如没有则先不实现」「宁可少删」；与原版逐项对齐，不确定宁可暂缓不臆测；权威源 = wiki.gg + iyingdi.com + 逆向代码三方交叉；结构化表格/分步骤/根因分析；常一次抛多个编号问题按序处理
