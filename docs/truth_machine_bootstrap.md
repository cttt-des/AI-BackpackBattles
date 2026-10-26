# 真值机引导状态（godot_project 运行副本）

> 目标：把 clean v1.1.7 逆向工程跑成 **headless 真值机**（确定性战斗 + 结构化事件落盘），
> 作为 `engine/` 一致性验证的裁判（docs/consistency_verification.md）。
> 运行副本在仓库外：`C:\Users\slic\Documents\bpb\godot_project\decompiled_full\`（不入库）；
> Godot 3.6.2：`C:\Users\slic\Documents\bpb\Godot_v3.6.2-stable_win64.exe`；
> 完整资源包：`C:\Users\slic\Documents\bpb\decompiled_full.7z`（467M）。
> 补丁一键重放：`python tools/apply_truth_patches.py <godot_project>\decompiled_full`
> 最后更新：2026-09-23（第 4 轮：战斗确定性打通 ✅）

## 当前状态

| 域 | 状态 | 验证 |
|---|---|---|
| 引导（820 脚本解析/主场景/autoload 时序） | ✅ | Main.tscn 30+ 帧稳定，VERSION 1.1.7 |
| 商店域（金币表/抽池/reroll 阶梯价） | ✅ | state=Shop gold=13（对账 goldGain）；reroll 出 5 槽真实物品 |
| 战斗域（自动开战/事件流） | ✅ | DarkReflection 对手自动创建；combatLog 结构化 JSONL |
| **战斗确定性** | ✅ | 注入阵容+fight_seed 隔离，两遍 13 事件逐字节一致 |

## 确定性协议（真值键）

**`(player_items, opponent_items, fight_seed, round)`** —— engine/ 对账以同键复放
（engine 战斗 RNG 从 fight_seed 初始化）。

驱动流程（`tools/truth_drive_combat.gd`）：
```
boot → truth_late_init（内含 TRUTH_SEED 播种，必须在 ready_deferred 初始物品抽取之前）
→ initPlayer → startFreshRun → 池预热 300 帧
→ fight_seed 隔离（Util.rng.seed=777; seed(777)）
→ finishSwitchingToCombat（跳过转场动画）
→ COMBAT_DELAY(2.5s≈150帧) 内注入双方固定阵容
   （INVENTORY.tryAddItem + ItemBook.instantiateItem， wipe 原有物品）
→ 逐帧 dump combatLog.events 增量 → user://truth_S42.jsonl → fightEnded 退出
```

## 已定位的方差源（绕过而非修复，低优）

1. **DarkReflection 对手构建有未播种方差**——对手物品集每轮不同（非确定性镜像），
   来源待查（可疑：serializeRound 含储物箱/Util.clockTime 浮点分支/物品统计数组）。
   → 绕过：注入固定对手阵容（真值机本来就需要指定阵容）。
2. **商店阶段帧级消费差**——ItemBook 每帧 `prepareItemInstances` 的 RNG 消费 ×
   转场动画落帧方差（墙钟定时器 vs 帧率），商店序列不可复现。
   → 缓解：Engine.target_fps=60 + 固定帧 reroll；彻底解决需另开一期。
3. 播种时机敏感性：初始 loadout 抽取在 ready_deferred（frame~1），
   播种必须在此之前（truth_late_init 在 _ready 队列首位）。

## 补丁清单（tools/apply_truth_patches.py，幂等）

1. `Stub/Steam.gd` 离线桩（~40 方法/15 信号，签名按调用点校验）+ autoload 首行注册；
2. `Core/Game.gd`：TRUTH_HEADLESS/TRUTH_SEED const、lobbies 空值守卫×2、
   `_ready` 顶部 call_deferred(truth_late_init)、initPlayer 提前、
   MaterialCompiler 等待门控、loadRunState×2 门控、27 个 onready 空安全化、
   truth_late_init 追加（30 变量重取 + 播种 + target_fps=60）；
3. `Sheets/ItemBook.gd`：ItemData_e.csv 明文加载（7z 内已是解密明文）、
   validateResources 写保护（EDITOR=true 时会重写工程文件——曾清空 ItemData_e.csv、
   覆盖 DataValidator.gd，**不要改 EDITOR=false，会启动即退出**）；
4. 从 .assets 补 6 个 raw CSV。

## 运行方式

```bash
"/c/Users/slic/Documents/bpb/Godot_v3.6.2-stable_win64.exe" --no-window \
  --script <探针.gd> --path "C:\Users\slic\Documents\bpb\godot_project\decompiled_full"
```
- user:// 输出在 `%APPDATA%\Godot\app_userdata\Backpack Battles\`。
- GDScript 注意：`log` 是保留字；属性 camelCase（curRound）；--path 与脚本都要绝对路径。
- 已知噪音错误（可忽略）：Unreleased 翻译缺失、ItemBook buildHistory.isOpen、
  部分 UI 空指针（RarityHint/RerollRope/fastButton）、个别物品 scene 缺失（BookofIce）。

## 下一步（按序）

1. **engine/ 对账首战**：tools/dump_engine_fight.py 以同阵容 + fight_seed 跑 engine/ →
   与 truth JSONL diff → per-item 偏差榜（consistency_verification.md 阶段 2）。
2. **探针参数化**：阵容从 lineups/*.json（v3/v4 schema）读入，支持任意双方阵容。
3. 价格对齐（ShopOffer.calcPrice 读取路径）；商店确定性另开一期。
