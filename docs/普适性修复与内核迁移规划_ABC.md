# 模拟器普适性修复与内核迁移规划（A → B → C）

> 编写日期：2026-11-14　|　执行者：待指派　|　编写者：模拟器侧
> 目标：① **去掉全部 22 场针对性开关**，让对齐具备完全普适性；② 内核迁移到 C++ 版拿速度
>
> ## 阅读须知（三条硬规则）
>
> 1. **禁止新增任何 `case_id` / `run_id` 级别的开关。** 现有 22 场开关是待清除的**技术债**，不是范例。
> 2. **遇到疑难必须回到 GDScript 源码**（`oracle/` 目录，1.1.9 反编译全量工程）找真实逻辑，不许猜、不许用补丁凑。
> 3. **验收判据只认事件流**：`event_count` 差 `-1`（我方多 `emit_combat_end` 一条）且**类型序列前缀完全一致**。
>    ⚠️ **不要用 `ticks` 当判据** —— 神谕 `result.txt` 是 730、py 腿同场 881，但两者事件数 30/30 一致。

---

## 0 当前状态（执行前必读）

| 指标 | 数值 |
|---|---|
| py 内核对齐（1690 全量） | **1690/1690**，但**依赖 22 场开关** |
| py 内核普适性（清空开关后 60 场快闸） | **59/60**（1 场 `run101354_r14`） |
| C++ 版对齐（补 4 项接口后，30 场样本） | 18/30 |
| C++ 版对齐（1690 全量） | **1666/1690 = 98.58%**（winner 一致 1689/1690） |
| 性能差距（同口径实测） | C++ **1.81x**（固定 2.24x / 净 run 1.72x） |

**关键认知**：两边的「1700 场对齐」都**不是**纯普适的——我方有 22 场开关，C++ 有 24 场硬缺口。
本规划的 A 阶段就是把我方那 22 场开关**清零**，B 阶段让 C++ 达到同等水平。

---

## A 阶段：清除 22 场开关，回到源码修（预计 2–3 天）

### A.0 22 场开关的完整清单与性质

| 开关 | 场数 | 性质 | 处理 |
|---|---|---|---|
| `flk_delay` | **20** | 🟡 **口径类**（见 A.1 的机制说明） | 需重新推导来源 |
| `no_flkfire` | 1 | 🔴 **机制错配**（抑制一笔抽取） | 必删，回源码修 |
| `inj_item` + `inj_trigger_n` | 1 | 🔴 **机制补丁**（人为补一笔抽） | 必删，回源码修 |
| `flk_off` | 1 | 🟡 待查 | 查清后归类 |
| `no_phase_comp` | 1 | 🟡 待查 | 查清后归类 |

### A.1 先搞清 `flk_delay` 到底是什么（**这一步最关键，做错方向会浪费两天**）

**已实测确认的机制**（2026-11-14，`run101354_r14`）：

```
不设 override                   : 442 事件  ticks=757
Burning Coal/ot3=1.0           : 652 事件  ticks=1073
Burning Coal/ot3=2.2284        : 671 事件  ticks=1130   ← oracle 就是 671
Burning Coal/ot3=99.0          : 473 事件  ticks=850
不存在的键 Xxx/ot3=2.0          : 442 事件  ticks=757    ← 按 key 精确匹配，未命中则无效
```

**为什么改一个「延迟值」会改变事件总数？** 源码解释（`oracle/Items/Animations/FlickerAnimation.gd`）：

```gdscript
func onAnimationEnded(aniName):
    var d = Util.rng.randf_range(minDist, maxDist)   # ← 第1笔：装配期抽 delay
    Util.callDelayed(self, "playAni", d)              # ← 到点才触发 playAni

func playAni():
    var spd = Util.rng.randf_range(minSpeed, maxSpeed)  # ← 第2笔：只在这时抽
```

> **机制真相**：`playAni` 只在**战斗尚未结束**时才会被派发（`CoreContext._flushTimed` 里
> `elif not self.fight_ended`）。所以 **delay 越大 → playAni 越可能落到战后 → 那笔 speed 抽取就不发生**。
> 这不是「纯视觉参数」，而是**经验性地等价于「控制这笔抽发生与否」**。

**⚠️ 但它为什么需要逐场写死？** 因为 delay 的**真值**本该由 `randf_range(minDist,maxDist)` 在
装配期抽出，而我们的 `rng_state` 注入会抹掉装配期消耗，之后重放时抽出的 delay 未必等于录制时那个值。

**A.1 的任务**：验证这个推断。具体做法：

1. 在 `output/oracle/fights/<case>/` 下找 `rng_log.txt`（若有），比对 delay 那一笔的取值
2. 若无 `rng_log`，用 `oracle` 的 `ORACLE_FLKPROBE` 环境变量重录一次该场，打印 `[FLKD] delay=`
3. 确认：**该场 delay 的真值是否可以由 `rng_state` + 装配序确定性地推出**
4. **若可以推出** ⇒ 说明我们的 `rng_state` 注入点或装配期消耗序有偏差，修那个偏差，`flk_delay` 全部可删
5. **若无法推出** ⇒ 说明录制时的 delay 依赖了某个我们没有建模的消耗，**找到那个消耗**（继续读源码）

**判定标准**：能解释「为什么这 20 场的 delay 恰好是这些值」 ⇒ 就找到了真实逻辑。

### A.2 修 `no_flkfire` / `inj_item`（run604585，1 场）

**已实测的四种组合**（`run604585_r6`，oracle=150 事件）：

| 组合 | 事件数 | idx=10 的 damage | 结论 |
|---|---|---|---|
| 无开关 | 150 | **6** ❌ | 错 |
| 只 `no_flkfire` | 95 | — ❌ | 错得更多 |
| 只 `inj_item` | 127 | — ❌ | 错 |
| **两个都开** | 150 | **5** ✅ | 与 oracle 一致 |

**两个开关缺一不可，且它们修的是不同位置**：
- `inj_item`：在 `Bloody Dagger` 第 1 次 trigger 后**补**一笔 `bare_randf_range(0,1)`
- `no_flkfire`：**抑制** `Oil Lamp` 的 flicker speed 抽取

> 一补一减恰好抵消了**事件总数**，但改对了**中间顺序**。这强烈暗示：
> **我们有两笔抽取的时机/归属搞错了**，一笔多了、一笔少了。

**A.2 的任务**：从源码找到这两笔的真实归属。

**线索 1（Bloody Dagger 多出的那笔）**：`oracle/Items/BloodyDagger.gd:13-18`

```gdscript
func onPreDealDamage_early(damageRes: DamageResult):
    if damageRes.hasHit():
        if vampirismStacks < getP2():
            giveVampirism(getP1())
            vampirismStacks += getP1()
            ObjectPool.particleOneShot(activationParticles, sprite)   # ← 这里
```

`ObjectPool.particleOneShot`（`oracle/Utility/ObjectPool.gd:70-81`）会 `add_child(particles)`，
触发粒子场景的 `_ready`。已查 `PooledScene.gd` **不抽 RNG**，但**粒子场景是否有其他子节点**尚未查完。
下一步：完整解析 `oracle/Items/Particles/BloodyDaggerActivationParticles.tscn` 的节点树，
以及 `HungryBladeActivationParticles.material` 可能引用的 shader/脚本。

**线索 2（Oil Lamp 少掉的那笔）**：`Oil Lamp` 是**对手侧宝石**（`Burning Coal` 也是），
枚举时必须用 `getItemsAndGems()` 而不是 `getItems()` —— **这一步我踩过坑，务必注意**：

```python
# ❌ 错：漏掉宝石
for it in ch.inventory.getItems():
# ✅ 对：含宝石
for it in ch.inventory.getItemsAndGems():
```

### A.3 查清 `flk_off` 与 `no_phase_comp`（各 1 场）

| 键 | 场次 | 源码位置 | 待查内容 |
|---|---|---|---|
| `flk_off` | `run300219_r6` | `CoreItem.py:1084-1088` | 按实例跳过 speed 抽。查源码：什么情况下实例没有对应 FlickerAnimation |
| `no_phase_comp` | `run704242_r18` | 待定位 | 查 `ORACLE_TIMER_NO_PHASE_COMP` 的消费点 |

### A.4 A 阶段验收

```bash
# 1. 把 override 表清空
echo '{}' > gd_core_test/oracle_align_case_overrides.json

# 2. 重跑 60 场快闸（约 1 分钟）
IDS="$(cat output/perf/core_cases.txt)"
python -X utf8 tools/verify_oracle.py --cases "$IDS" --force --skip-fixtures \
  --fights-root output/oracle/expand/fights \
  --align-root output/oracle/align_expand \
  --cases-json gd_core_test/expand_align_cases.json \
  --alignment-out output/perf/alignment_core_noov.json
# 期望：三方一致 60/60

# 3. 全量 1690（约 90 分钟）
#    期望：1690/1690，且 override 表为空
```

**⚠️ 验收时必读**：不要只看总数。必须回读 `alignment.json` 的 `perCase`，
确认**每一条 `match` 都是「三方一致」**。历史上「1690/1690」被假报过三次，都是因为只看了总数。

---

## B 阶段：让 C++ 版达到同等对齐（预计 3–5 天）

### B.0 前置：C++ 版现状

| 项 | 状态 |
|---|---|
| 源码位置 | `native_sim_cpp/`（**未纳入 git**，需单独索取） |
| 构建 | `build_windows.py`（我方补的，作者包内只有 macOS 的 `build.py`） |
| Windows dll | 作者包**不含**，需自行编译（MinGW，全量约 133 秒） |
| 已对齐（补接口后） | 30 场样本 18/30；全量 1666/1690 |
| 缺的接口 | `activation_order` / `rng_state` / `gem_lens`（**作者版至今没有**） |

**已有可用补丁**：`docs/cpp_cover_patch/engine_wrapper.cpp` + `sim.py`
（含三项接口 + `custom_health_multiplier` 传参 + reorder 副本 + 全局 Math 链对齐）。
这批补丁已验证：补后 30 场 18/30，与本地一致。

### B.1 必做的第一件事：补三项接口

| 字段 | 位置 | 语义 | 坑 |
|---|---|---|---|
| `PackedSide.n_activation_order` + `activation_order` | 结构体 + `startBattle` 前 | 真 Godot 洗牌终序直通 | `startBattle` 第 3 参数必须传 `true`（preordered），否则会再洗一次 |
| `BattleOptions.rng_state` + `has_rng_state` | 结构体 + 装配完成后 | `ctx.set_state` 直灌 | **值是 uint64，负值合法**！不能用 `-1` 当哨兵（我踩过） |
| `PackedItem.n_sockets` | 结构体 + `build_single_item_obj` | 插槽数用实例真值 | `proto.sockets`（脚本容量）与 `len(gems)` **95.5% 不同** |

**另外两个必须对齐的点（容易漏）**：

1. **`activation_order` 必须重排副本，不能就地改 `p_items`**
   —— `p_items` 是 inventory 的内容，就地改会把 inventory 顺序也改掉。
   py 的 `prepareItems` 有 `if item.placed: continue` ⇒ **inventory 恒为装配序**。
2. **全局 Math 链要在装配完成后重绑**
   —— py 在 `gd_core_engine.py:1273-1278` 做了两件事：
   `_bind_battle(seed)`（抹掉装配期消耗）+ 两侧各补一条 Fisher-Yates 消耗。
   C++ 的 `reset_for_battle()` 在装配**之前**，不等价。
   ⚠️ **必须用 `battle.math_rng`，不是 `ctx.rng`** —— 这是两条独立随机流（我踩过这个坑，白试一轮）。

### B.2 修 C++ 的 24 场硬缺口

当前 C++ 未对齐的 24 场（`delta` = C++ 事件数 − py 事件数）：

| delta 区间 | 场数 | 代表 |
|---|---|---|
| ≤ −100 | 3 | `run101710`(−877)、`run101354`(−230)、`run101710`(−1437) |
| −100 ~ −10 | 6 | `run604687`(−36)、`run704933`(−21)、`run101635`(−17) |
| −10 ~ 0 | 3 | `run101668_r8`(−1)、`run101702`(−3) |
| 0 ~ +10 | 4 | `run300219`(+2)、`run704881`(+3)、`run101571`(+5)、`run704504`(+9) |
| > +10 | 8 | `run704714`(+273)、`run101582`(+27)、`run604825`(+33) |

**1 场 winner 不同**：`run101702_r17_o101027_r17`（C++=opponent / py=player）。

### B.3 分工策略：**用 A 阶段的结论，不要重新发现**

A 阶段会产出「22 场开关的真实逻辑」。B 阶段直接拿这些结论去改 C++，而不是重新查一遍。

**顺序建议**（按收益从高到低）：

| 序 | 目标 | 依据 |
|---|---|---|
| 1 | 让 C++ 支持 flicker 抽取（`flickerAni` → delay + speed 两笔） | C++ 的 `build_single_item_obj` **完全没有 flicker 抽取**，天生少两笔。先对齐这个，可能一口气修好多场 |
| 2 | `run101354_r14`(−230) | A.1 会给出 delay 的真实来源，直接移植 |
| 3 | `run704714`(+273) | delta 最大的正偏差，可能是多发 |
| 4 | 剩余按 delta 从大到小 | — |

### B.4 B 阶段验收

```bash
# 跑全量 1690（约 130 秒，比 py 快得多）
python -X utf8 tools/_full1690.py <cpp_pkg_root> output/perf/_cpp1690.json

# 期望：1666/1690 → 提升到 1690/1690
# 且：override 表为空（C++ 侧不需要任何场次开关）
```

**注意**：C++ 侧的 `_full1690.py` 需要传 4 项覆盖（`gem_lens`/`activation_order`/`rng_state`/`mult`），
这些是**先写死成夹具读取**的，不是场次开关。

---

## C 阶段：决定是否替换内核（决策点，0.5 天）

### C.1 前提条件（不满足就不替换）

| 条件 | 要求 |
|---|---|
| A 完成 | py 内核 1690/1690 **且 override 表为空** |
| B 完成 | C++ 内核 1690/1690 **且无需场次开关** |
| 性能复测 | C++ 仍保持 1.8x 以上优势（同口径交错 A/B） |

### C.2 两个方案

| 方案 | 做法 | 收益 | 风险 |
|---|---|---|---|
| **保守（推荐）** | 保留 py 内核作对齐/调试引擎；C++ 作批量引擎（训练/评测） | 1.8x 速度 + 保留 Python 可调试性 | 低（两套代码，需同步维护） |
| **激进** | 完全换成 C++ 内核 | 1.8x + 更低内存占用 | 失去 Python 探针/单步调试；改一个字段要动 ctypes 结构 + 重编 133 秒 |

**推荐的决策依据**：

> 如果 C++ 版能做到 **1690/1690 且零开关**，那么它在「正确性」上与 py 平权。
> 此时选择保守方案的理由是：**排查新分歧的成本**。
> py 可以随时加探针读中间状态；C++ 只能改源码重编（133 秒/次）。
> 本项目成本最高的环节是「定位分歧」，不是「跑得快」。

### C.3 若选择激进方案，需要额外做的事

| 项 | 说明 |
|---|---|
| 保留 py 内核 | 不删除，作为回归对照（新改动先用 py 验，再用 C++ 跑全量） |
| 迁移探针能力 | C++ 需要补：逐抽 RNG 追踪、装配态 dump、事件流导出（调试导出已有雏形） |
| 跨平台构建 | 作者包只有 macOS dylib；需固化 Windows 构建脚本（现有 `build_windows.py`） |
| 打包规范 | 库里应有 `libgdcore.dll`，且 `sim.py` 按平台选库（作者版硬编码 `.dylib`，Windows 报 `WinError 193`） |

---

## 附 A：必读的源码位置

| 主题 | 文件 |
|---|---|
| FlickerAnimation 抽取 | `oracle/Items/Animations/FlickerAnimation.gd`（全文 31 行） |
| Bloody Dagger 粒子触发 | `oracle/Items/BloodyDagger.gd:13-18` |
| ObjectPool | `oracle/Utility/ObjectPool.gd:70-81`、`oracle/Utility/PooledScene.gd` |
| 物品入树/装配 | `oracle/Core/Inventory.gd:810,839,1262`（`add_child`） |
| 宝石入树 | `oracle/Item.gd:3043`（`sockets[socketId].add_child(gem)`） |
| 延迟回调 | `oracle/Utility/Util.gd`（`callDelayed`）、`oracle_fight.gd:939-953`（`drive_delayed`） |
| py 侧镜像 | `gd_core_py/gd_core/CoreItem.py:974-1090`、`CoreContext.py:350-390` |
| C++ 侧对应 | `native_sim_cpp/native_sim/engine_wrapper.cpp`（`build_single_item_obj` / `startBattle`） |

## 附 B：我踩过的坑（避免重复）

| 坑 | 症状 | 教训 |
|---|---|---|
| 用 `getItems()` 枚举 | 漏掉宝石，以为「该场没有 flicker 物品」（`Burning Coal` 是宝石 `ot=7`） | **用 `getItemsAndGems()`** |
| 用 `ticks` 当判据 | 神谕 730 vs py 881，但事件数 30/30 一致 | 只认事件流 |
| `rng_state` 用 `-1` 当哨兵 | 它是 uint64，负值合法 ⇒ 注入被静默跳过 | 用独立 `has_rng_state` 标志 |
| `startBattle` 第 3 参数传 `false` | 顺序全乱 | py 传的是 `true`（preordered） |
| 就地重排 `p_items` | inventory 顺序被一起改掉 | 重排**副本** |
| 全局 Math 链用 `ctx.rng` | 无效 | 必须 `battle.math_rng` |
| 探针取错对象 | dump 到全 0，白折腾两轮 | 先验证探针取对了东西 |
| grep 漏 `alignas` | 误判「`GdVal` 定义不在包内」 | 搜索模式要宽松些 |

## 附 C：常用命令

```bash
# py 侧 60 场快闸
IDS="$(cat output/perf/core_cases.txt)"
python -X utf8 tools/verify_oracle.py --cases "$IDS" --force --skip-fixtures \
  --fights-root output/oracle/expand/fights \
  --align-root output/oracle/align_expand \
  --cases-json gd_core_test/expand_align_cases.json \
  --alignment-out output/perf/alignment_core_cases.json

# 种子双态（秒级，最快的健全性检查）
python -X utf8 tools/check_seed_dual.py
# 期望：907 tick/1548 事件 与 1042 tick/1991 事件

# C++ 全量 1690
python -X utf8 tools/_full1690.py <cpp_pkg_root> output/perf/_cpp1690.json

# C++ 编译（增量约 10 秒）
cd native_sim_cpp
NATIVE_SIM_OBJ=/tmp/native_sim_obj python -X utf8 native_sim/build_windows.py
```