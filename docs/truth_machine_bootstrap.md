# 真值机引导状态（godot_project 运行副本）

> 目标：把 clean v1.1.7 逆向工程跑成 **headless 真值机**（固定种子 + 战斗事件落盘），
> 作为 `engine/` 一致性验证的裁判（docs/consistency_verification.md）。
> 运行副本在仓库外：`C:\Users\slic\Documents\bpb\godot_project\decompiled_full\`（不入库）；
> Godot 3.6.2 便携版：`C:\Users\slic\Documents\bpb\Godot_v3.6.2-stable_win64.exe`；
> 完整资源包：`C:\Users\slic\Documents\bpb\decompiled_full.7z`（467M，含 .stex/.ogg/.import/.png 全量）。
> 最后更新：2026-09-22（引导中，未达可自动开战）。

## 已完成的补丁（全部只在运行副本，真值参考树未动）

1. **`Stub/Steam.gd` + autoload 注册**（project.godot [autoload] 首行 `Steam="*res://Stub/Steam.gd"`）：
   GodotSteam 原生库不在 pck 内，打离线桩。~40 个方法按"无 Steam"语义返回
   （`steamInit → {"status":0}`、`isSubscribed→false`、`loggedOn→false`、`getServerRealTime→OS.get_unix_time()`），
   15 个信号声明。关键签名（被调点校验）：`steamInit(1 bool)`、`downloadLeaderboardEntries(4 args)`、
   `uploadLeaderboardScore(4 args)`、`getQueryUGCMetadata(默认参数)`、`setLobbyMemberData→bool`。
2. **补齐 6 个原始 CSV**（`cp .assets/Sheets/CSV/{Items,Full,ExclusiveItems,Flavor,Keywords,Interface}.csv → Sheets/CSV/`）：
   GDRE 只放了 .import/.translation，游戏代码直接读 raw CSV；补齐后 gate 物品
   （Box of Riches / Customer Card 等）加载成功。

## 当前状态（drive4 探针实测）

- ✅ 全部解析级错误清零（820 脚本可加载）；Main.tscn 实例化、30+ 帧稳定；
  Game autoload 存活，`VERSION=1.1.7`，`CustomRules.reset()` 执行。
- ✅ `game.initPlayer()` + `startFreshRun(0)` 不再中途崩溃（persistent 默认值补齐）。
- ❌ 未到商店：`state=0`（Title）、PLAYER/OPPONENT 未创建、gold=0、shopSceneNode=Nil。
- ❌ 残留错误三层：
  1. `ItemBook.gd:1257 Game.buildHistory.isOpen`——buildHistory 节点是运行时动态实例化
     （Main.tscn 里只有 BuildHistoryPlaceholder），headless 下未实例化 → ItemBook._process 每帧报错（无害但吵）。
  2. ItemBook `items` 字典缺一批名字（Amulet 系等）——多表合入顺序/重复加载问题，
     待查 `ItemBook._ready` 的 sheet 加载链（注意 ItemData_e.csv 已是解密明文，
     但 `Table.gd` 的 sheetKey 是朴素 0..31，与出货 CSV 的 patch 密钥 0xC6/0xC3 不一致——
     见 reverse_engineering_2026-09.md，需确认代码路径是否对已解密文件二次解密）。
  3. startRun → `RunDatabase.sendRunRequest()` 依赖 SilentWolf 网络 → 离线挂起，
     `titleToShop` 未触发。**这是下一刀的位置**。

## 下一步（按序）

1. **RunDatabase 离线化**：照抄游戏自带兜底——`startRun/sendRunRequest` 短路到
   `getFallbackOpponent()`（DarkReflection=玩家自身镜像），或注入指定对手
   （`RunDatabase.gd` 有 `getManualHistoryOpponentRoundData` 2743 / `startHistoryRun` 2690 可参考）；
   同时在 Game.gd 运行副本加 `truth_setup(seed, player_items, opponent_items)` 方法：
   固定 `Util.rng.seed`+全局 `seed()` → initPlayer → instanceCharacter → 直接摆物品进 PLAYER.INVENTORY
   （绕过商店 UI）→ startRound 或直接 finishSwitchingToCombat。
2. **战斗事件落盘**：CombatLog 增量轮询（bridge v2 的 tap 思路，直接 GDScript 实现：
   autoload 每帧 dump `Game.combatLog.events` 增量 → 写 `user://truth_events.jsonl`）。
3. 验证一场自动化战斗：事件流非空、含攻击/伤害事件、时长合理（15-40s）。
4. 打通后与 `tools/dump_engine_fight.py`（被测侧）对接 diff。

## 运行方式

```bash
# 冒烟（Main 场景实例化 + 30 帧）
"/c/Users/slic/Documents/bpb/Godot_v3.6.2-stable_win64.exe" --no-window \
  --script <探针.gd> --path "C:\Users\slic\Documents\bpb\godot_project\decompiled_full"
# 已知噪音错误可忽略：Unreleased.*.translation 缺失（9 个语言文件 GDRE 未转出）、
# ItemBook buildHistory.isOpen、部分 UI 脚本空指针（DamageMeter 等）
```

## 探针模板

`extends SceneTree` 的 `_init()` 里：`load("res://Core/Main.tscn").instance()` →
`add_child` → `yield(self,"idle_frame")` 泵帧 → 调 Game 方法 → `quit(0)`。
注意属性是 camelCase（`curRound`/`curClass`），`--path` 与脚本路径都要绝对路径。
