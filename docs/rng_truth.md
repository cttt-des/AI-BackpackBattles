# RNG 语义真值（rng_truth）— P0 考古结论

> 目标：为确定性重放给出「单一全局 rng 链」的逐行源码证据 + `Util.rng.state` 的唯一内存定位方案。
> 真值依据：`decompiled_full/`（v1.1.7，主引用）、`extracted_running/decomp/`（1.1.8 运行版，交叉验证）、
> `output/godot_src/`（Godot 3.6 引擎源码节选）。
> 本文中每条结论均在本会话内核实（读取或运行），行号均可点击复核。
> 生成日期：2026-10-04

---

## 1. 单一全局 rng 链

### 1.1 声明与播种时点

| 事实 | 证据 |
|------|------|
| 全游戏唯一游戏 rng：`var rng = RandomNumberGenerator.new()` | `decompiled_full/Utility/Util.gd:6` |
| 启动时播种：`randomize()`（引擎全局链）+ `rng.randomize()`（Util.rng 链），都在 Util._ready | `decompiled_full/Utility/Util.gd:76-77` |
| 1.1.8 运行版行号完全一致 | `extracted_running/decomp/Utility/Util.gd:6`、`:76`、`:77`（本会话 grep 核实） |
| 全仓 grep `randomize`：除上述外只有 `addons/silent_wolf/utils/UUID.gd:2`（静态函数内，见 §1.4 例外） | 本会话 `grep -rn "randomize" decompiled_full --include="*.gd"` 输出 |
| 全仓 grep `rng.seed / rng.randomize / set_state / .seed(`：只有 `Util.gd:77` 一处 | 本会话 grep 输出（`decompiled_full` 全部 .gd） |

**结论**：`Util.rng` 在游戏启动后只播种一次（Util.gd:77），此后是一条确定的 PCG32 状态链。
游戏全程不存在对 `Util.rng` 的任何二次播种。

### 1.2 一切随机最终消费 Util.rng

| 入口 | 证据 |
|------|------|
| `Util.roll(maximum)` = `rng.randf_range(0, maximum)` | `Util.gd:1007-1008` |
| `Util.flip(chance)` = `rng.randf() <= chance` | `Util.gd:1010-1011` |
| `Util.flipPercent(chance)` = `roll() <= chance` | `Util.gd:1013-1014` |
| `Util.flipWeighted(weights)` = `rng.randf_range(0, sum)` | `Util.gd:1021-1033`（:1026） |
| `Util.pickRandomElement(array)` = `array[rng.randi_range(...)]` | `Util.gd:452-453` |

### 1.3 BalancedRandom 只是包着 Util.flip 的平衡器

`decompiled_full/Utility/BalancedRandom.gd`（1.1.8 版 `extracted_running/decomp/Utility/BalancedRandom.gd`
与 v1.1.7 逐字节相同，本会话 `diff` 输出为空）：

| 入口 | 消费点 | 证据 |
|------|--------|------|
| `roll(target)` | `var result = Util.flip(chance)` | `BalancedRandom.gd:18-52`（消费点 :43） |
| `roll2(target)` | `if Util.flip(chance)` | `BalancedRandom.gd:60-79`（消费点 :74） |
| `roll1(target)` | `if Util.flip(accChance)` | `BalancedRandom.gd:81-102`（消费点 :97） |
| 构造消耗 | `var expectedWins = Util.rng.randf_range(0.2, -0.2)` —— 每件物品 `BalancedRng.new()` 时消耗全局 rng 一次 | `BalancedRandom.gd:4`；`Item.gd:472` `var chanceRng = BalancedRng.new()`（1.1.8 同为 `Item.gd:472`） |
| **`reset()` 只清计数器，不重播种** | `reset()` 体只把 expectedWins/wins/lastResult/extraLuck/accChance/lastTarget 清零 | `BalancedRandom.gd:104-112` |

### 1.4 例外与注意（不影响 Util.rng 链，但影响复现）

1. **引擎全局链（第二条链）**：`Util.gd:76` 的 `randomize()` 播种的是引擎全局 RNG
   （GDScript 内建 `randi()/randf()/seed()` 与 `Array.shuffle()/pick_random()` 用的那条）。
   本会话已在原版 Godot 3.6 引擎（`output/godot36/Godot_v3.6-stable_win64.exe`，headless 探针
   `output/rng_truth_probe/Probe.gd`，输出 `out.txt`）实测：
   - `seed(k)` 后 `shuffle()`/`pick_random()` 可复现（消费全局链）；
   - `RandomNumberGenerator.set_state(...)` 完全不影响 `shuffle()`（两条链独立）。
2. **战斗开始时的 shuffle 消费全局链**：`Game.finishSwitchingToCombat` 里
   `playerItems.shuffle()`（`Game.gd:3012`）与 `opponentItems.shuffle()`（`Game.gd:3019`），
   随后 `sort_custom(ItemSort, "sort_TriggerPriority")`（:3013/:3020，非稳定排序）。
   ⇒ 物品激活顺序是全局链决定的**战斗输入**，但**不经过 Util.rng**；重放器只要复刻
   「读到的物品顺序」（或复刻 shuffle），就与 Util.rng.state 无关。
3. **SilentWolf UUID**：`addons/silent_wolf/utils/UUID.gd:2` 的 `randomize()` 位于
   `static func getRandomInt` 内，每次调用都会**重播种全局链**。该函数属于在线后端路径，
   离线历史对战（BuildHistory → startHistoryRun）不会调用；若在战斗窗口内被意外调用，
   只影响 shuffle 顺序，仍不触碰 Util.rng。
4. **视觉随机也消费 Util.rng**：如 `ItemAnimation.randomizePosition()`
   （`Items/Animations/ItemAnimation.gd:25-30`，命中动画抖动）、`BuildHistory.addAni`
   （`BuildHistory.gd:444`、`:447`、`:453`、`:456`）。这些调用按固定时序发生，是链上的
   正常消费，不影响「捕获 state 即可重放」的结论，但意味着捕获时刻必须精确（见 §4）。

---

## 2. Util.rng 的内存定位路径推导

### 2.1 Util 是 autoload 节点

- autoload 列表：`decompiled_full/project.godot:467-486`，`Util="*res://Utility/Util.gd"` 在 :470，
  是列表第 2 个 autoload（0 起下标 = **1**）。
- 旁证（既有标定）：`core/godot_reader.py:40-42` 注释「root 子节点 = 18 个 autoload + Main」、
  `:75-76` `game_child_index = 8`。autoload 列表第 9 个正是 `Game`（project.godot:477，下标 8），
  与 0 起下标顺序完全吻合 ⇒ **Util 节点 = root.children[1]**。
- 稳健定位法（推荐，沿用 `find_game_node` 的模式，`core/godot_reader.py:294-318`）：
  从 root BFS，按脚本资源路径 `res://Utility/Util.gd` 匹配（`node_script_path`，
  godot_reader.py:225-253），节点名 `Util` 做二次确认。

### 2.2 节点 → members 槽位（沿 godot_reader 既有标定链）

既有标定方法（`core/godot_reader.py:31-98`）：
`object_script_instance_off = 0x58`（:46）→ `gdscript_members_off = 0x20`（:63，CowData<Variant>，
长度在 `_ptr - 4`，:68）→ `variant_size = 24`（:65，type 4B + 对齐 + 16B union）。

**rng 的槽位推导 = 成员声明序下标 3**：

`Util.gd` 顶层 `var` 声明序（本会话按行号枚举）：`frameCounter`=0(:3)、`time`=1(:4)、
`clockTime`=2(:5)、**`rng`=3(:6)**、`file`=4(:7)、…（const 不占成员槽）。

「声明序 = 成员槽位」这一前提已被本仓 4 组活体标定交叉验证
（Game.gd 的成员下标，godot_reader.py:89-97）：

| 成员 | 声明序下标（本会话枚举 `grep -E "^(onready |export |)var "` 计数） | 活体标定值 |
|------|------|------|
| `curRound`（Game.gd:308） | 65 | `member_round = 65` ✓ |
| `tries`（Game.gd:311，= 剩余生命/命，开局 5，与标定读数 5 吻合） | 68 | `member_hp = 68` ✓ |
| `gold`（Game.gd:315） | 72 | `member_gold = 72` ✓ |
| `curClass`（Game.gd:326） | 83 | `member_cur_class = 83` ✓ |

⇒ **Util.members[3] 是 rng**（Variant，预期 `type = 17 OBJECT`）。

OBJECT Variant 的槽内布局（本仓既有实测）：对象指针在 `var_addr + 16`
（`core/build_history.py:104-107`：「type(4) id(4) 预留(8) obj*(8) —— 实测指针在 +16
（+8 为 ObjectID，非地址）」）；`core/combatlog_reader.py:274-281` 的 `_obj_at` 亦兼容
「+8 槽间址优先、+16 直读兜底」。读取时两个来源都试、取合法指针。

**注意**：members[4]（`file = File.new()`）、members[6]（`sharedBitstream`）、members[7]
（`sharedDirectory = Directory.new()`）同样是 OBJECT。区分 rng 与它们不能只靠 type=17，
必须做槽位语义验证（见 §6.1 的 LCG 校验，唯一满足者才是 rng）。

### 2.3 RandomNumberGenerator 对象内部布局（seed/state 两个 64 位字段）

引擎侧结构（`output/godot_src/`，Godot 3.6 官方源码节选）：

```cpp
class RandomNumberGenerator : public Reference {   // random_number_generator.h:37
    GDCLASS(RandomNumberGenerator, Reference);      // :38 —— 只加一个 StringName _class_name，无其它实例数据
protected:
    RandomPCG randbase;                             // :41 —— 唯一实例成员
    // state/state setter 直通：set_state→randbase.set_state→pcg.state  (random_number_generator.h:50-52)
};
class RandomPCG {                                   // random_pcg.h:62-65
    pcg32_random_t pcg;        // { uint64_t state; uint64_t inc; }   pcg.h:11
    uint64_t current_seed;     // 「当前 state 所来自的种子」
    uint64_t current_inc;
};
```

偏移推导（x64，MSVC 对齐；锚点 = 本仓实测 `script_instance @ obj+0x58`，godot_reader.py:46）。
除原有 6 个文件外，以下头文件节选本会话已从 Godot 3.6 官方源拉取并存入仓内
`output/godot_src/`（object.h、reference.h、ref_ptr.h、dictionary.h、safe_refcount.h），
关键成员行号均已核实在仓：

| 字段 | 偏移 | 依据 |
|------|------|------|
| `script`（RefPtr=char[8]，ref_ptr.h:45-48） | +0x60 | 紧随 script_instance |
| `metadata`（Dictionary=单指针 `_p`，dictionary.h:43） | +0x68 | |
| `_class_name`（StringName=单指针） | +0x70 | |
| `_class_ptr` | +0x78 | |
| `instance_binding_count`（SafeNumeric\<uint32\>=std::atomic 4B，safe_refcount.h:63） | +0x80 | |
| `_script_instance_bindings[8]` | +0x88..0xC8 | object.h:441 `MAX_SCRIPT_INSTANCE_BINDINGS=8`、:516-517 |
| `_is_queued_for_deletion`（bool） | +0xC8 | object.h:744 |
| **sizeof(Object)** | **0xD0** | object.h:498-502 成员序（script_instance→script→metadata→_class_name→_class_ptr） |
| `Reference.refcount` / `refcount_init`（SafeRefCount=4B ×2，reference.h:42-43） | +0xD0 / +0xD4 | |
| GDCLASS 加入的 `_class_name`（StringName，8B） | +0xD8 | object.h:268（GDCLASS 宏内 `mutable StringName _class_name`） |
| **`randbase`（RandomPCG）起点** | **+0xE0** | |
| **`pcg.state` ⇒ `get_state()/set_state()` 操作的字段** | **+0xE8** | pcg.h:11 字段序 `{state, inc}`；~~+0xE0~~ 勘误（2026-10-04 活体扫描标定：本构建 randbase 多 8B 对齐，见 core/godot_reader.py GODOT_OFFSETS 注释） |
| `pcg.inc` | +0xF0 | |
| `current_seed`（= `get_seed()`，random_pcg.h:77） | +0xF8 | |
| `current_inc` | +0x100 | |

**状态字段语义（本会话在原版 Godot 3.6 引擎上数值实测，探针 `output/rng_truth_probe/Probe.gd`，
输出 `out.txt`/`out3.txt`）**：

- 前进公式：`state' = state × 6364136223846793005 + (inc|1) (mod 2^64)`（pcg.cpp:6-15）。
  实测：`set_state(1000)` 后 `randi()` 得 `state' = 2894908498775624295`，与 Python 按
  `inc = (PCG_DEFAULT_INC_64<<1)|1 = 2885390081777926815`（pcg.h:9 + random_pcg.h:69 +
  pcg.cpp:21）复算**逐位一致**；连推 3 步全部吻合。
- `rand()` 每次先把 `current_seed = pcg.state`（前进前）再前进（random_pcg.h:83-86）。
  实测：`seed1 == s0`、`seed2 == s1` ✓。⇒ 内存里 `state(+0xE8)` 恒比 `current_seed(+0xF8)`
  「领先一步」，这也是区分两个字段的手段。
- `set_state(v)` 只写 `pcg.state`，不动 `current_seed`（random_number_generator.h:50-52）。
- **活体标定（2026-10-04，PID 7996，tools/probe_rng_state.py --diff-seconds 4 --interval 0.2）**：
  20 组相邻采样全部满足「读数不变 或 前进 k 步恰为 LCG 命中」（k=2..23），0 失败——
  state@+0xE8 / inc@+0xF0 / seed@+0xF8 为本构建实测值（tools/probe_rng_state.py 可复跑）。
  实测：`set_state(555555)` 后 `get_seed()` 仍返回旧值 ✓。
- 消耗计数：`randi()`=1 次 rand；`randf()` 常态=2 次（random_pcg.h:113-124，MSB/LSB 置位
  技巧），首输出为 0 时早退=1 次；`randf_range()/randd()` 常态=2 次（random_pcg.cpp:45-47 +
  random_pcg.h:100-112）。实测三者的落地 state 与上述逐一吻合（out3.txt F2/F3/F4）。
  ⇒ `Util.flip`（Util.gd:1011）常态一次消耗 2 步链。
- `RandomNumberGenerator.randomize()`（Util.gd:77 调用的）= `randbase.randomize()`
  （random_pcg.cpp:41-43）：用 `(unix_time + ticks_usec) × state + PCG_DEFAULT_INC_64`
  作新种子重播种，`inc` 仍取默认 ⇒ 启动后 `pcg.inc` 恒为 2885390081777926815（可用于校验）。

**不确定性声明**：`randbase @ +0xE0` 是「对象头 = 0xD0 + 8B 引用计数 + 8B GDCLASS StringName」
的静态推导，依赖 MSVC 标准对齐与 3.6 头文件成员序（所引头文件节选均已存仓内
`output/godot_src/`，可复核；safe_refcount.h 对 SafeRefCount 有两个 `#if` 分支变体，
:164/:290，两分支均含单个 4B 计数字段，不影响结论）；
它必须在活体上一次性标定确认（§6.1 的验证会立刻证伪/证实），确认前不应写死进
`GODOT_OFFSETS`。

---

## 3. 历史对战输入面逐行核实

### 3.1 入口链（BuildHistory 界面内完成，全程离线）

```
BuildHistory.fightBuild()                       BuildHistory.gd:468
  └ Game.startHistoryRun(curData, curRoundNum)  BuildHistory.gd:475 → Game.gd:2690
BuildHistory.onFightPopupFightPressed()          BuildHistory.gd:507   （剪贴板构建码对打）
  └ Game.startHistoryRun(curData, curRoundNum,
      parsed, int(parsed.get("round",1)))        BuildHistory.gd:519
```

- `fightBuild` 守卫 `curData != null and not fighting`（:469），随后
  `Game.unpause + close(true) + suspendRunState(false)`（:470-474）——不进入任何在线模式。
- 对手另可选「标记历史条目为对手」：`setOpponentMark`（`BuildHistory.gd:323-331`，写
  `markedOpponentData/markedOpponentRound`，:60-61 声明）。

### 3.2 startHistoryRun（Game.gd:2690-2723）装配清单

| 行号 | 语句 | 输入含义 |
|------|------|----------|
| :2691 | `setMode(Mode.History)` | 模式锁定为历史（离线） |
| :2692-2696 | `curHistoryData / manualHistoryOpponentData / manualHistoryOpponentRound` | 记录对手数据（剪贴板路径） |
| :2697 | `curRound = roundNum` | **回合数** |
| :2698-2699 | `wins/losses = curHistoryData.getWins/Losses(roundNum-1)` | 双方此前胜负（无随机） |
| :2700-2703 | `tries = MAX_TRIES(=5, Game.gd:197) 或 getTries(roundNum-1)` | **初始生命（命数）** |
| :2707 | `instanceCharacter(curHistoryData.classI)` | **玩家职业** |
| :2708 | `CustomRules.fromString(...)` | 自定义规则（无随机） |
| :2709-2711 | `roundData = getRoundData(roundNum)`；`RunData.deserializeItems(roundData.items, version)["items"]`；`PLAYER.INVENTORY.createFromItemTuples(items, Owner.PlayerInventory)` | **玩家阵容**（物品、位置 c、朝向 f、宝石 g、数据 pd） |
| :2712 | `PLAYER.setMaxHealth(roundData.health)` | **玩家初始 HP** |
| :2713 | `PLAYER.setMaxStamina(roundData.stamina)` | **玩家初始体力** |
| :2714 | `initRoundResults()` | 回合结果数组（无随机） |
| :2717-2722 | 场景动画 `ShopToCombat` + `emit_signal("switching_to_combat")` | 进入战斗的信号时点（捕获锚点之一） |

**该函数内没有任何 `randomize`/`seed`/`set_state`**（§1.1 全仓 grep 已证）——
历史对战不重播种。✅（工作流文档 §0 表行「历史对战不重播种」成立）

### 3.3 对手装配（三条路径，均无重播种）

战斗切换的真正装配发生在 `finishSwitchingToCombat`（Game.gd:2928 起；`switchToCombat`
:2908 由动画/按钮触发，:2926 发 `combat_start_pressed`）：

1. **标记对手路径**：`if curMode == Mode.History and buildHistory.markedOpponentData != null:
   initHistoryOpponent()`（Game.gd:2991-2992）。
   `initHistoryOpponent`（Game.gd:3187-3219）：`OPPONENT.INVENTORY.reset()`(:3193)、
   `setMaxHealth(roundData.health)`(:3194)、`setMaxStamina(roundData.stamina)`(:3195)、
   `setClass(data.classI)`(:3196)、反序列化物品 `items.sort_custom(ItemSort,"sort_BagOrder")`
   (:3202)、逐件 `addOpponentItem`（:3221-3255：位置 `tuple["c"]`、朝向 `tuple["f"]`、
   校验、宝石 `tuple["g"]`(:3244-3250)、物品数据 `tuple["pd"]`(:3252-3253)）、
   `baseMaxStamina + recalculateMaxStamina`(:3212-3213)。
   ⇒ **对手阵容 + 初始 HP + 体力** 完全来自历史数据，无随机取值
   （但每件物品/宝石构造仍消耗链 2 步，见 §4.3）。
2. **剪贴板构建码路径**：`RunDatabase.getNextOpponentData`（RunDatabase.gd:352-363）：
   `Mode.History` 时先取 `Game.getManualHistoryOpponentRoundData()`（Game.gd:2743-2782：
   对手 round 的 items/health + `calculateMaxStaminaFromItemTuples` 算体力（:2726-2741）+
   class/loadout/name/chibi/skins），非空则用它；否则落回本地池。
3. **本地池路径**（无标记、无剪贴码时的默认）：`RunDatabase.sortOpponents()`
   （Game.gd:2994，纯本地 runs 数据排序，`Util.sharedBitstream.serializeString` 不随机）
   + `initOpponent` 循环（Game.gd:2996-3000）。对手 = 本地历史库中的另一 run 快照
   （`getNextOpponentDataFromPool`，RunDatabase.gd:365-394）。选人本身确定性，但装配
   阶段**可能消耗 Util.rng**，重放步数核算必须计入：
   - `droppedItems >= 1` 时 `dropIndex = Util.rng.randi_range(0, size-1)`（1 步）并丢弃
     对手一件物品（Game.gd:3139）；
   - 对手快照为 chibi 且本地隐藏 chibi 时，每个 skin slot 经
     `SkinBook.getRandomSkinFor → Util.pickRandomElement`（Game.gd:3169-3171 →
     SkinBook.gd:18-24，`Util.pickRandomElement` = `randi_range`，Util.gd:452-453）
     再消耗 1 步/slot；
   - `roundReduction > 0` 时对手阵容 items 会替换为**同一 run 更早回合**的 items
     （RunDatabase.gd:387-392）——即对手快照不一定是所选回合的原始阵容；
   - `droppedItems/roundReduction` 由 Game.gd:2962-2976 的
     `isItemHandicapStats`（:2882-2887，只看 wins/losses 组合）/`isSoftballRound`（:2862）/
     `isSoftballStats`（:2878）计算；历史池对战中 wins/losses 来自 `curHistoryData`
     （Game.gd:2698-2699），故这些消耗在历史对战中**可达**。
4. **黑映像兜底路径**：`faceDarkReflection == true`（RunDatabase.gd:42，:367-368）或本地池
   耗尽（:380-381）时走 `getDarkReflectionData`（RunDatabase.gd:396 起）：由玩家自身
   `serializeRound` 快照生成对手（:397 起，class/name/chibi/skins 取自当前玩家）。
   确定性、无 rng 消耗，但属于对手装配路径清单的一部分（对手=玩家自己的镜像阵容）。

其余战斗前装配：`OPPONENT = opponentScene.instance()`（Game.gd:2981，**消耗 Util.rng：
Character 成员初始化器 4 个 BalancedRng，见下 §4.1 步数表**）、互相 `setOpponent`、连
`character_died → endCombat`（Game.gd:2981-2986）——除上述 rng 消耗外无随机。

### 3.4 物品激活顺序（战斗的隐藏输入，走全局链）

Game.gd:3011-3020：双方 `getItems().duplicate()` → `shuffle()` →
`sort_custom(ItemSort, "sort_TriggerPriority")`；随后 `call_deferred("prepareItems", ...)`
（:3023）与 `Util.callDelayed(self, "activateItems", COMBAT_DELAY, ...)`（:3024）。
`shuffle()` 消费**引擎全局链**（§1.4-2，已实测其与 Util.rng 独立）。
重放器的输入面因此是：**「双方物品的最终顺序」**（可从捕获/库存结构读出），而非全局链状态。

### 3.5 1.1.8 运行版差异（重要）

1.1.8 的 `Game.gd/BuildHistory.gd` 行号与功能面有漂移（本会话 diff 全文 953 行差异 + grep 定位）：

| 项 | v1.1.7（decompiled_full） | 1.1.8（extracted_running/decomp） |
|----|----|----|
| `MAX_TRIES = 5` | Game.gd:197 | Game.gd:188 |
| `COMBAT_DELAY = 2.5` | Game.gd:201 | Game.gd:192 |
| `startHistoryRun` | Game.gd:2690 | Game.gd:2402（**签名保留 opponentData 但函数体完全不用它**） |
| `switchToCombat` / `finishSwitchingToCombat` | :2908 / :2928 | :2555 / :2575 |
| `markedOpponentData != null` 分支 | :2991 | :2638 |
| `playerItems.shuffle()` / `opponentItems.shuffle()` | :3012 / :3019 | :2659 / :2666 |
| `initHistoryOpponent` | :3187 | :2829 |
| `prepareItems` / `activateItems` | :3257 / :3264 | :2898 / :2905 |
| `fightBuild` | BuildHistory.gd:468（:475 调 startHistoryRun） | BuildHistory.gd:309（调两参版 startHistoryRun） |
| `setOpponentMark` | BuildHistory.gd:323 | BuildHistory.gd:195（`markedOpponentData = buildEntry.data` 在 :199） |
| 剪贴板对打（FightPopUI / getManualHistoryOpponentRoundData） | 有 | **无**（grep 零命中） |
| `adjustCooldown` | Item.gd:3805 | Item.gd:3789 |
| `var chanceRng = BalancedRng.new()` | Item.gd:472 | Item.gd:472 |

1.1.8 的 `startHistoryRun`（Game.gd:2402-2427）逐句与 v1.1.7 相同
（setMode(History)→curRound→wins/losses→tries→instanceCharacter→CustomRules→
createFromItemTuples→setMaxHealth→setMaxStamina→initRoundResults→switching_to_combat），
同样**无任何重播种**；`activateItems`/`adjustCooldown` 语义逐行一致。
⇒ 本文所有结论对两个版本同等成立；运行版捕获按 1.1.8 行号/更窄输入面（无剪贴板路径）理解。

---

## 4. 战斗开始边界：捕获必须早于首个 roll

### 4.1 时间线（v1.1.7 行号；1.1.8 等价行号见 §3.5）

```
startHistoryRun (Game.gd:2690)
  └ emit "switching_to_combat"                         :2722      ← 捕获锚点 A
switchToCombat (Game.gd:2908) → emit "combat_start_pressed" :2926
finishSwitchingToCombat (Game.gd:2928)
  ├ 对手装配（§3.3，含 rng 消耗，见 §4.3 步数表）        :2981-3000
  ├ emit "shop_closed"/"switching_to_combat"            :3005-3006  ← 捕获锚点 B
  ├ combatTimer.initialize() / PLAYER.shopToCombat()    :3008-3009
  ├ shuffle + sort（全局链，非 Util.rng）                :3011-3020
  ├ call_deferred("prepareItems")                       :3023       ← ★首个 Util.rng 消差点（deferred ≈ 本帧末）
  └ Util.callDelayed("activateItems", COMBAT_DELAY=2.5) :3024       ← +2.5s
prepareItems (Game.gd:3257-3262)：PLAYER/OPPONENT.prepare()（Character.gd:294-317，BalancedRng.reset
  ×4，无消耗）+ 每件 item.prepare()（Item.gd:3361-3369，reset 无消耗）+ onPrepare() 钩子
  ——onPrepare 直接消耗 Util.rng 的物品：LightningPotion（Exclusive/LightningPotion.gd:22-25，
  baseCooldownOverride = Util.rng.randf_range(...)）。反例核实：BowandArrow.gd:15-17、
  Exclusive/AmuletofDarkness.gd:16-23 的 onPrepare 均无 rng 消耗（二者的 rollChance/
  rollDoubleAttackEffect 在战斗期钩子里才调用）                  ← ★已开始消耗
activateItems (Game.gd:3264-3280)：emit "combat_start"(:3267) → combatTimer.start()(:3268)
  → 每件 item.preCombatStart()(:3274) —— hasCooldown() 者必消耗：
  Item.adjustCooldown 双分支（Item.gd:3805-3811）：ownerType==Opponent 且
  isBelowLeague(Master)（或 Lobbies 模式）用 randf_range(0.975,1.05)（:3807-3808），
  否则 randf_range(0.95,1.05)（:3809-3810）——重放器复刻对手冷却必须实现该分支
  → combatStart/postCombatStart 钩子（各种 onCombatStart roll）
```

`COMBAT_DELAY = 2.5`（Game.gd:201）。Combat.gd 侧对 COMBAT_DELAY 的唯一使用是背景动画定位
（`Combat.gd:949`，`backgroundAnimation.seek(Game.COMBAT_DELAY + ...)`，纯视觉）；Combat 场景
经 `shop_closed/combat_scene_entered/combat_start` 信号驱动（`Combat.gd:112-118`，
信号声明 Game.gd:61/64/73）。

### 4.2 边界结论

1. **「首个 roll」不在 2.5s 延迟之后，而在 `prepareItems`（Game.gd:3023 deferred → :3257）**，
   即 `finishSwitchingToCombat` 后约一帧之内；2.5s 的 COMBAT_DELAY 只推迟
   `activateItems`（:3024）里的 preCombatStart/combatStart 批次（adjustCooldown 是确定存在
   的首批大量消耗，Item.gd:3805-3810）。
2. 因此**捕获必须早于 finishSwitchingToCombat 的 deferred prepareItems**：
   - 可靠锚点 = `switching_to_combat` 信号（startHistoryRun:2722 或 :3006）发出后、
     对手装配完成前的瞬间；锚点 B 之后、prepareItems 之前的装配期消耗按 §4.3 的
     步数表核算（物品/宝石件数可由阵容读出，droppedItems/chibi 重掷取决于对手快照）；
     若在「shop_closed(:3005) 后、prepareItems 前」
     捕获则无此顾虑，但窗口只有一帧级。
   - 工程取法（与工作流 P2 设计一致）：战斗检测后以 ≤10ms 级密集轮询 `Util.rng.state`，
     取「检测到进入战斗前最后一次读到的 state」；§4.3 的步数核算只作**诊断参考**，
     **弃场判据只能是「重放首事件即分叉」**（deterministic_replay_workflow.md §3 风险表同款对策）——
     静态步数表无法覆盖 prepare/combatStart 钩子里的全部条件消耗，把它当硬闸会误弃正常捕获。
3. 依据小结：「捕获必须早于首个 roll」的硬证据 =
   `Game.gd:3023（deferred prepareItems）` + `Game.gd:3257-3262 → Item.gd onPrepare 消耗`
   + `Game.gd:3024 COMBAT_DELAY 只延迟 activateItems` + `Item.gd:3805-3811 preCombatStart 必消耗`。

### 4.3 装配期 Util.rng 消耗步数表（诊断用，非弃场闸）

「锚点 B（Game.gd:3006）→ prepareItems」之间，以及锚点 A→B 之间，Util.rng 的
可静态枚举消耗（每步 = 1 次 PCG `rand()`；randf_range 常态 2 步、randi 1 步，§2.3）：

| 消耗点 | 步数 | 触发条件 | 证据 |
|--------|------|----------|------|
| 每个 Character 实例化（成员初始化器 4 个 `BalancedRng.new()`） | 8 | `opponentScene.instance()`（对手，Game.gd:2981）；玩家侧在 `instanceCharacter`（startHistoryRun:2707，早于锚点 A） | Character.gd:94-97（1.1.8 同为 Character.gd:94-97）→ BalancedRandom.gd:4 `randf_range` |
| 每件物品 / 每颗宝石构造（`chanceRng = BalancedRng.new()`；`damageRangeRng = BalancedRange.new()` 构造**不**消耗——BalancedRange.gd:2-5 只有 `var acc`） | 2/件 | 玩家侧早于锚点 A；对手侧在 addOpponentItem/initOpponent 装配中（宝石 `extends Item`，Game.gd:3244-3250 等） | Item.gd:472-473；Gems/Gem.gd:1 |
| 对手物品丢弃抽签 | 1 | `droppedItems >= 1`（本地池路径可达，见 §3.3-3） | Game.gd:3139（1.1.8：Game.gd:2788） |
| 对手皮肤重掷 | 1/slot | 对手快照 chibi 且本地隐藏 chibi | Game.gd:3169-3171（1.1.8：:2817）→ SkinBook.gd:18-24 |
| shuffle ×2 | 0 | 每次战斗开始（走引擎全局链，§1.4-2） | Game.gd:3012/3019 |
| `roundReduction` 阵容替换 | 0 | 换用同 run 更早回合 items（无 rng，但改变阵容输入） | RunDatabase.gd:387-392 |

用途限制：本表只用于「捕获 state 与首事件之间步数是否合理」的事后诊断与 PCG 反向步进
校验（§6.2）；prepare/combatStart 钩子的消耗依阵容与物品而定，无法静态精确枚举。

---

## 5. 内存定位方案（P2 read_rng_state 实施规格）

```
模块基址 (module_base)
  └ + os_singleton_rva            → OS*                     [godot_reader.py:141-145，RVA 仍需 probe 标定]
      └ +0x1D0 main_loop          → SceneTree*              [os_main_loop_off, godot_reader.py:38]
          └ +0x148 root           → Viewport*               [scenetree_root_off, godot_reader.py:42]
              └ children[1]       → Util 节点               [node_children_off=0x108, godot_reader.py:52；
                       │                                     稳健法：BFS 按 "res://Utility/Util.gd"（§2.1）]
                  +0x58           → GDScriptInstance*       [object_script_instance_off, :46]
                      +0x20       → members (CowData<Variant>) [gdscript_members_off, :63；个数在 ptr-4, :68]
                          slot 3  → Variant                [24B/槽, :65；type@+0 == 17(OBJECT)，
                              │                        ObjectID@+8, 对象指针@+16（build_history.py:104-107 实测）]
                              └→ RandomNumberGenerator*
                                  +0xE0  state  (u64)   ★重放唯一所需
                                  +0xE8  inc    (u64)   应恒 = 2885390081777926815（校验用）
                                  +0xF0  current_seed(u64) = 上一步前进前 state（校验用）
                                  +0xF8  current_inc(u64)
```

- `state` 即 Godot `RandomNumberGenerator.state` 属性直通字段
  （random_number_generator.h:50-52 → random_pcg.h:79-80 → pcg.h:11）；
  P1 注入语义 = 把捕获的 u64 直接写 +0xE0，下一次 rand 从该值前进（本会话探针 A3/B2 实测吻合）。
- `randbase @ +0xE0` 为静态推导（§2.3），**首次活体标定确认前以「扫描+LCG 校验」定位**（§6.1），
  确认后写进 `GODOT_OFFSETS`（沿用 config.yaml `godot:` 覆盖机制，godot_reader.py:17-18）。
- 只读操作；全程通过历史记录界面由用户手动开战（约束同 deterministic_replay_workflow.md §1）。

## 6. 验证方法

### 6.1 活体一次性标定（区分 rng 槽位 + 确认 randbase 偏移）

1. 读 Util.members 槽 3（以及 0..15 兜底扫描）里所有 type=17 的 Variant，按 §5 取对象指针，
   排除 `script_instance(obj+0x58) != 0` 的对象（脚本类 BitStream 可据此剔除；
   File/Directory 与 rng 同为原生对象，靠下述校验区分）。
2. 对每个候选对象，在 +0x00..+0x110 以 8B 步进取 (u64 a, u64 b, u64 c)，检验
   **LCG 不变式**：`a == c × 6364136223846793005 + 2885390081777926815 (mod 2^64)`
   且 `b == 2885390081777926815`（inc 恒定，§2.3）。
   唯一满足者即 rng 对象，此时 a 的偏移即 `state`（预期 +0xE0），c 即 `current_seed`（预期 +0xF0）。
   —— 该不变式已在原版引擎上数值验证（§2.3 探针），误报率≈0。
3. 差分确认：战斗外（历史界面静置）连续读 state，读数稳定 ⇒ 读到的是字段而非垃圾；
   战斗内 state 单调按 LCG 前进 ⇒ 前向性成立。

### 6.2 会话内持续校验（combatlog_exporter 集成后）

- **消耗数诊断（非弃场判据）**：已知事件流的 roll 组成（flip=2 步、roll/randf_range=2 步、
  randi=1 步，早退路径 1 步，§2.3）+ §4.3 步数表（Character +8、物品/宝石 +2/件、
  droppedItems 抽签 +1、chibi 皮肤重掷 +1/slot）可以反推「捕获 state → 首事件」间的
  链步数**期望值**；偏差只用于诊断捕获时机/漏算来源，**弃场判据只能是重放首事件分叉**
  （静态表无法覆盖 prepare/combatStart 钩子的条件消耗，硬套会误判）。
- **PCG 反向步进校验**：`state_prev = (state - inc) × M⁻¹ (mod 2^64)`（M⁻¹ 可预计算），
  可从战斗结束时刻 state 反推开战时刻 state，作为「最早捕获值」的交叉验证。
- **P1 逐位闸门**：`gd_core_test` 的 Godot 原生 `RandomNumberGenerator.set_state(s)` 跑 N 步
  vs gd_core 内核同 state 跑 N 步逐位比对（deterministic_replay_workflow.md P1）；
  本会话探针（output/rng_truth_probe/）已把 state/seed 语义基准钉死，闸门直接对表。

### 6.3 本会话已执行的检查清单

| 检查 | 命令/方式 | 结果 |
|------|-----------|------|
| v1.1.7 关键行号 | Read Util.gd / BalancedRandom.gd / Game.gd / BuildHistory.gd / Item.gd / Combat.gd | 全部如文中行号 |
| 1.1.8 行号与语义 | grep + sed + diff（BalancedRandom 两版逐字节相同；Game.gd 953 行 diff 后逐点定位） | 见 §3.5 |
| 全仓 randomize 重播种排查 | `grep -rn randomize`（两版） | 仅 Util.gd:76-77 与 silent_wolf/UUID.gd:2 |
| 声明序=槽位验证 | 枚举 Game.gd var 序并与 godot_reader.py 标定值比对 | 65/68/72/83 四组全中 |
| 引擎语义探针 | `output/godot36/Godot_v3.6-stable_win64.exe --headless --path output/rng_truth_probe -s res://Probe.gd`（跑 3 轮：out.txt / out2.txt / out3.txt） | LCG 前进式、current_seed 语义、set_state 直通、randf/randf_range=2 步、shuffle/pick_random 走全局链且与 RNG 对象独立 —— 全部实测成立（含 Python 复算比对） |
| 评审修复轮核实（本会话第二轮） | sed/grep 复核：BowandArrow.gd:15-17、Exclusive/AmuletofDarkness.gd:16-23（onPrepare 无 rng）、Exclusive/LightningPotion.gd:22-25（有）、Character.gd:94-97、Gems/Gem.gd:1、Utility/BalancedRange.gd:2-5、Game.gd:3139/:3169-3171/:2962-2976/:2882-2887、RunDatabase.gd:352-363/:365-394/:387-392/:396-399、SkinBook.gd:18-24、Item.gd:3805-3811 双分支、1.1.8 BuildHistory.gd:195 | 评审 7 条全部属实并已按其修订 §2.3/§3.3/§4.1/§4.2/§4.3/§6.2 |
| 头文件节选入库 | curl 从 godotengine/godot 3.6 分支拉取 5 个头文件存入 `output/godot_src/`（object.h 45882B、reference.h、ref_ptr.h、dictionary.h、safe_refcount.h），grep 复核关键成员行号 | object.h:441/:498-502/:516-517/:744、reference.h:42-43、ref_ptr.h:45-48、dictionary.h:43、safe_refcount.h:63 全部在仓可复核 |
| 未做（如实声明） | 活体读取运行中游戏进程的 Util.rng | 属 P2 阶段；`randbase @ +0xE0` 的静态推导待 §6.1 一次性标定；本会话未启动游戏、未触碰任何在线模式 |
