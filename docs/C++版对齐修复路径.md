# C++ 版对齐修复路径（剩余 12 场）

> 对象：`native_sim_cpp/` 的对齐缺口　|　状态日期：2026-11-14 17:00　|　进度：**18/30**
>
> 本文档只讲**下一步怎么做**。历史过程（错在哪、为什么错）见
> [`性能优化下一步规划.md`](性能优化下一步规划.md) §4.10。

---

## 1 现在到哪了

| 里程碑 | 已对齐 | 关键提交 |
|---|---|---|
| 起点（原报告） | **0/30**（数据不可用） | — |
| 补三项覆盖 | 8/30 | `2339a5ee` |
| 补 `custom_health_multiplier` + 修 reorder | 13/30 | `561e60c2` |
| **补全局 Math 流** | **18/30** | `1730feea` |

**已修的四类根因**（都在调用方，不是 C++ 内核缺陷）：

| # | 根因 | 影响面 |
|---|---|---|
| 1 | `PackedSide` 缺 `activation_order`/`rng_state`/`gem_lens` 三项覆盖 | 全部 30 场 |
| 2 | `custom_health_multiplier` 漏传（值是 200 不是默认 100） | `run101490_*` 全族 5 场 |
| 3 | `activation_order` 就地重排污染 `inventory`（应为副本） | 部分场次顺序 |
| 4 | **全局 Math 流未对齐**（装配后未重绑 + 缺两条 shuffle 消耗） | 5 场（含 −389 那场） |

**交付物**：

| 文件 | 内容 |
|---|---|
| [`docs/cpp_cover_patch/engine_wrapper.cpp`](cpp_cover_patch/engine_wrapper.cpp) | 改后的 C++（干净版，无调试代码） |
| [`docs/cpp_cover_patch/sim.py`](cpp_cover_patch/sim.py) | 改后的 ctypes 绑定 |
| `native_sim_cpp/native_sim/libgdcore_withcover.dll` | 编译产物 |
| `native_sim_cpp/native_sim/libgdcore_orig_backup.dll` | 原始备份（可回退） |
| [`output/perf/_cpp30_final.json`](../output/perf/_cpp30_final.json) | 30 场逐场结果 |

**重编方法**（增量，只重编改动单文件 ≈10 秒）：

```bash
cd native_sim_cpp
NATIVE_SIM_OBJ=/tmp/native_sim_obj python -X utf8 native_sim/build_windows.py
```

---

## 2 剩余 12 场的分类

### 2.1 按 delta 大小

| 类 | 场数 | 场次 |
|---|---|---|
| **大幅**（\|delta\| ≥ 20） | 6 | `run704714`(+273)、`run101354`(−230)、`run604687`(−36)、`run604825`(+33)、`run101582`(+27)、`run704933`(−21) |
| **小幅**（\|delta\| < 20） | 6 | `run101668_r8`(−1)、`run300219`(+2)、`run704881`(+3)、`run101571`(+5)、`run704504`(+9)、`run704990`(−16) |

### 2.2 按首个分歧的形态

| 形态 | 场数 | 说明 |
|---|---|---|
| **同 tick，但事件类型不同** | 7 | 两侧在同一时刻发出了**不同种类**的事件 |
| **同 tick，类型序列错位** | 2 | 同一时刻的顺序不同（内含类型切换） |
| **时间戳差 1–17 tick** | 3 | `run101668_r8`(−0.033s)、`run604825`(+0.133s)、`run704933`(−0.1s)、`run704990`(−0.017s) |

### 2.3 七个「类型不同」的场，具体差在哪

| 场次 | C++ 发出 | py 发出 | 指向的物品 |
|---|---|---|---|
| `run704714_r9` | `102 Regeneration` amount=−1 | `106 Empower` amount=−1 | **Fedora** |
| `run704504_r15` | `104 Spikes` amount=−1 | `106 Empower` amount=−2 | **Fedora** |
| `run101582_r9` | `105 Mana` amount=−1 | `106 Empower` amount=−1 | Perfect Amethyst |
| `run300219_r6` | `1 DealDamage` dmg=6 | `107 Heat` amount=1 | Burning Sword |
| `run704881_r6` | `1 DealDamage` dmg=2 | `100 Block` amount=−4 | Stone |
| `run604687_r10` | `2 CriticalDamage` dmg=10 | `1 DealDamage` dmg=5 | Poison Dagger |
| `run101571_r11` | `12 Health` amount=26 | `105 Mana` amount=4 | Strong Health Potion |

> **最强信号：`Fedora` 出现 2 次**，两次都是「C++ 发 102/104、py 发 106」。
> Fedora 的 `doCooldownEffect` 走 `stealRandomBuff(numBuffs, event, buffs)` 其中 `buffs = getBuffs() 去掉 Lucky`。
> `stealRandomBuff` → `pickRandomStacks(possibleBuffs, numBuffs, opponent(), priorityBuff)` →
> 内部 `self.ctx.rng.pickRandomElement(list(stacks.keys()))`。
> ⇒ **差异来自「偷哪个 buff」的随机选择结果不同**。

---

## 3 修复路径（按性价比排序）

### ~~路径 A：`stacks.keys()` 的迭代顺序~~（**已排除，2026-11-14 17:05 验完**）

> **结论：不是它。** 读 `gd_rt.cpp:1037-1041` —— `GdDict::keys()` 是
> `for (i = 0; i < len; ++i) a->data[i] = entries[i].key;`，**严格按插入序**返回；
> `GdDict::set` 也是 `entries[len++] = {key, val, h}` 追加。与 py `Dictionary` 的插入序语义一致。
> ⇒ 键序不是差异来源，**这条线不用再查**。

以下是原假设（留档）：

**为什么怀疑它**：`pickRandomStacks` 用 `list(stacks.keys())` 做随机取元素，**键的顺序直接决定取到谁**。
`stacks` 是 `Dictionary`，由 `for stackType in stackTypes`（即 `getBuffs()` 的 101..107）按 `_current > 0` 填充。

**要验证什么**：

1. C++ 的 `GdDict` 是否**严格按插入序**迭代（`keys()` 是否返回 `entries[0..len)` 顺序）
2. py 的 `Dictionary` 是否同样按插入序（GDScript 语义是插入序，但要确认内核实现没改成别的）
3. `stacks` 的填充顺序在两侧是否一致（取决于 `getBuffs()` 的区间端点与 `_current > 0` 判定）

**已验证的部分**（省时间）：

- `CoreConst.getBuffs()` py 返回 `_gd_range(EV_LUCKY, EV_HEAT+1)` = `[101..107]`；
  C++ `sf_getBuffs` 用 `SYM_GEN_Lucky` 起、`gd_add(...)` 止，结构一致 ⇒ **端点没问题**
- C++ `GdDict::set` 用 `entries[len++] = ...` **追加**，`keys()` 应是插入序 ⇒ 需最终确认 `keys()` 实现

**怎么改**：若确认迭代序不一致，优先让 C++ 的 `keys()` 严格按 `entries` 下标返回；
若一致，则差异在**别的路径**（见 B/C/D）。

### 路径 B：`Delayed` 日志队列的 flush 时机（**首选**）

**为什么怀疑它**：`stealRandomBuff` 里有这么一段——

```python
self.ctx.bus.setLoggingMode(Delayed)      # 切成延迟模式
for buff in removedStacks:
    opponent.loseStacks(buff, ...)
    self.giveStacks(character(), buff, ...)
self.ctx.bus.flushLoggingQueue()          # 一次性刷出
```

⇒ `loseStacks`/`giveStacks` 的事件被**攒起来**，在 `flushLoggingQueue` 时统一发出。
若 C++ 的 `loggingMode` 切换或 `flushLoggingQueue` 的**遍历顺序**不同（队列是数组，按 push 序），
事件顺序就会变。**这能解释「同 tick 类型不同」的形态**。

**要验证什么**：

1. `setLoggingMode(Delayed)` 在 C++ 是否真的切了（读 `SYM_GEN_setLoggingMode` → `f_loggingMode`）
2. `flushLoggingQueue` 里 `queueDuplicate` 的遍历是否按 push 序（C++ `gd_iter_seq` 对 Arr 是 `0..n-1`，应一致）
3. `emitAndLog` 在 Delayed 模式下是否**只入队不发**（若不慎两处都发 ⇒ 重复）

### 路径 C：`getBuffs()` 的「当前值」来源

`pickRandomStacks` 里 `numTargetStacks = target.buffs[stackType]._current`。
若 C++ 的 `_current` 与 py 的 `Buff._current` 在某时刻不同（例如 `steal` 后未同步），
则「哪些 buff 进 stacks」就不同。

**怎么验证**：在 Fedora 触发前一刻，dump 双方 `opponent.buffs[t]._current`（t=101..107）逐项对比。
这是**可以确定的探针**——比 dump inventory 更可靠（那个取错对象白折腾了很久）。

### 路径 D：`CriticalDamage` vs `DealDamage`（`run604687`）

`run604687_r10` 是 C++ 发 `2 CriticalDamage dmg=10`、py 发 `1 DealDamage dmg=5`。
这不是「偷 buff」问题，而是**暴击判定不同**。伤害值 10 vs 5 说明 C++ 判定为暴击（×2）。

**怎么查**：对比 `critRng` 的消耗次数与 `critResistanceRng`，以及 `getCritChance()` 的组成。
注意 py 侧 `below_master` 会给对手 `critRng.setBias(+0.2)`、玩家 `(−0.2)` —— 已确认传了 `below_master=True`。

### 路径 E：三个时间戳偏移场

`run101668_r8`、`run604825`、`run704933`、`run704990` 的 ts 差 1–17 tick。
**先做 A/B 再看它们** —— 若 A 修好了，这些可能是连带现象。

---

## 4 已排除的方向（**不要再查**）

| 假设 | 检验方法 | 结论 |
|---|---|---|
| `inventory` 顺序不同 | dump C++ `chr->f_inventory.getItems()` 与 cases 装配序逐项比对 | ❌ **37/37 完全一致** |
| 物品 `speed`/`triggerTime` 不同 | 装配完成态逐物品对比 37 项 | ❌ **37/37 完全一致** |
| 冷却推进逻辑不同 | 读 C++ `Item::physicsTick` 与 py `physicsTick` 步骤③⑥ | ❌ 逐行同构 |
| `shuffle` 算法不同 | C++ `shuffle_array` vs py `_shuffle` | ❌ 逐行同构（Fisher-Yates 自后向前） |
| `GdVal` 定义缺失 | — | ❌ 在 `gd_rt.hpp:169`（`struct alignas(8) GdVal`） |
| `pickRandomElement` 不同 | C++ `fn_pickRandomElement` vs py `array[randi_range(0,n-1)]` | ❌ 结构对齐 |
| `getBuffs()` 端点不同 | py `[101..107]` vs C++ `Lucky..+` | ❌ 一致 |
| `GdDict` 不保持插入序 | 读 `GdDict::set` | ❌ 用 `entries[len++]` 追加 |

---

## 5 建议的执行顺序

```
① 路径 B（Delayed 队列 flush 顺序）——**现在的最强候选**，见下
② 路径 C（buffs._current 逐项 dump）—— 与 B 可并行，探针成本低
③ 路径 D（暴击判定）—— 独立问题，单独修 run604687
④ 路径 E（时间戳偏移）—— 最后看，可能是 B–D 的连带

已排除：路径 A（GdDict.keys 严格按插入序，与 py 一致）
```

**验收判据**（每步都跑）：

```python
# 1. 跑 30 场，看对齐数
python -X utf8 tools/_cpp30_v2.py

# 2. 判据：delta == -1（= 我方多 emit_combat_end 一条）且类型序列前缀完全一致
#    满足 => ✅ 已对齐
#    ❌ ticks 不可比：神谕 result.txt 是 730，py 腿同场 881，但事件数 30/30 一致
```

---

## 6 三条纪律（本轮踩出来的）

| 纪律 | 事故 |
|---|---|
| **跨实现对比必须逐字段证明输入同源，不只「物品数一样」** | 原 30 场报告里 ticks 只有 1/30 相同 —— 29 场不是同一局，结论全部作废 |
| **说「做不到」之前先查工具链** | 「GdVal 定义不在 bundle」是 grep 漏了 `alignas(8)`；「无法逐抽追踪」是没查 `g++`/`build_windows.py` 就在仓库里 |
| **探针要先验证自己取对了对象** | dump inventory 时取了错的对象，抓到全 0，白折腾两轮；改用 `chr->f_inventory` 才对 |

---

## 7 一句话

> **18/30 已对齐，全部四类根因都在「调用方传参」而非 C++ 内核。**
> 剩余 12 场里有 **7 场是「同 tick 发出不同事件」**，最强线索是 `Fedora` 的
> `stealRandomBuff` 随机选择结果不同 —— 它走 `ctx.rng.pickRandomElement(list(stacks.keys()))`，
> 键序或 `_current` 值任一不同都会导致偷到不同的 buff。
> 建议从**路径 A（keys 迭代序）**入手，半天内可验证。