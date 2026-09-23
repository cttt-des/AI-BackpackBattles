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

## 当前状态（2026-09-22 深夜，第 2 轮迭代后）

**已验证可用的零件**（探针 drive11/14 实测）：
- 28 个 onready UI 引用 `truth_late_init()` 手动重取全部成功（动画表齐全：TitleToShop 等 7 个）。
- `instanceCharacter(0)` 手动调用 → PLAYER 创建成功；`titleToShop()` → 动画实际播放（playing=True，进度推进）。
- `initPlayer()` 的 persistent 默认值就位（selectedClass=0 等）。

**已打补丁（运行副本 Game.gd 等，累计 5 处）**：
1. `Stub/Steam.gd` 离线桩 + autoload 首行注册（签名按调用点校验：steamInit→Dictionary、downloadLeaderboardEntries 4 参、uploadLeaderboardScore 4 参、getQueryUGCMetadata 带默认参、setLobbyMemberData→bool）。
2. 补 6 个 raw CSV（.assets → Sheets/CSV/）。
3. Game.gd 两处 lobbies 空值守卫（2830 行 startRun、isInLobby 函数）。
4. Game.gd 追加 `truth_late_init()`（30 个 onready 重取，幂等）+ `_ready` 顶部 `call_deferred`。
5. `_ready` 内 `initPlayer()` 提前 + `const TRUTH_HEADLESS = true` + ready_deferred 跳过 MaterialCompiler 等待。

**根因链（已定位，未完全打通）**：
`ready_deferred()`（Game.gd:2456，原版解决 autoload 时序的官方入口）推进到
`loadRunState(Mode.Unranked)` → RunDatabase/SilentWolf **HTTP 阻塞**（进程 943MB 挂起、
无输出）。original 启动链 = 标题 UI → startFreshRun → 动画回调 → switchToShop，
全链路对 UI/网络的重依赖不适合 headless 复刻。

## 下一步：专用 headless 驱动场景（不再复刻启动链）

新建 `Stub/TruthDrive.gd`（SceneTree 脚本，--script 入口），**绕过标题/商店/网络，
直接组装战斗**（全部使用游戏自身类，战斗代码 100% 原版）：

```
1. seed_rng: Util.rng.seed=S; seed(S)           # 确定性
2. truth_late_init(); initPlayer()
3. Game.instanceCharacter(class)                  # PLAYER（已验证可用）
4. Game.initStartInventory(loadout)               # 起始物品
5. 对手：Game.instanceOpponent? 或直接 Game.OPPONENT = opponentScene.instance()
   + 从 lineup JSON 用 ItemBook.instantiateItem(name) 摆进双方 INVENTORY
   （摆位用 INVENTORY.tryAddItem/addItemByTopLeft，宝石用 setGem）
6. Game.call("finishSwitchingToCombat") 或 prepareItems→activateItems 序列
   （对照 Game.gd:2928-3032 的 finishSwitchingToCombat 复刻最小等价调用）
7. 战斗事件落盘：逐帧 diff Game.combatLog.events 增量 → user://truth_events.jsonl
   （另起一个 autoload 或在 TruthDrive 的 _process 里做）
8. fightEnded 后：result_json（双方血量/时长/胜负）写 user://truth_result.json → quit()
```

关键引用：finishSwitchingToCombat `Game.gd:2928-3032`（保存 run/instance 对手/
ItemSort 触发序/prepareItems/activateItems/COMBAT_DELAY 2.5s）；
摆物品参考 `Inventory.gd:408-637`（tryAddItem/addItemByTopLeft/addItemCells）；
 lineup 格式见 repo-review/lineups/*.json（v3/v4 schema）。

验证标准：truth_events.jsonl 非空、含 Attack/Damage 事件、时长 15-40s；
同种子两场事件流逐字节一致（阶段 0 游戏自洽性）。

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
