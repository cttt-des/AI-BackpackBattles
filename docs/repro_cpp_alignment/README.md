# 30 场对齐差异：独立复现包

> 给 `native_sim_cpp/` 作者。**不需要主仓库，只依赖 `native_sim_cpp/`。**
> 配套文字报告见主仓库 `docs/C++版对齐差异报告_30场.md`。

## 这个包里有什么

| 文件 | 内容 |
|---|---|
| `cases.json` | **30 场的完整输入**：`case_id` / `seed` / `round_id` / `player` / `opponent`（side dict 可直接喂 `sim.run_one`） |
| `expected_py.json` | **参考事件流**（主仓库 py 腿产出，**已与神谕逐行一致**）+ 每场的 `ticks` / `event_count` / `winner` |
| `actual_cpp.json` | 我这边用你的 `libgdcore.dll` 跑出的结果（含 `gd_sim_dbg_event_line` 的 canonical 行），**供你直接对比、不必先跑** |
| `verify.py` | **校验脚本**：重跑这 30 场并逐场报告 winner / 事件数 / 首个 `type` 序列分歧位置 |
| `table.md` | 30 场差异一览表（delta / 首个分歧 idx / 两侧事件类型） |

## 怎么跑

把本目录与 `native_sim_cpp/` 放在**同一级**（或本目录放进 bundle 内部），然后：

```bash
# 1) 全部 30 场，只报结果表
python verify.py

# 2) 单场并排打印（推荐从这场入手：第 2 条事件就分叉）
python verify.py --case run101668_r7_o604708_r7 --ctx 6

# 3) 想看更长的上下文
python verify.py --case run704879_r14_o704504_r14 --ctx 20
```

退出码：`0` = 与参考一致，`1` = 有实质分歧。

## 判据（重要，先说清口径）

**`expected_py.json` 的 `event_count` 比 C++ 侧多 1 是正常的**——主仓库 `run()` 末尾会补一条
`emit_combat_end`，C++ 侧没有这个事件。所以：

| 差值 | 含义 |
|---|---|
| `delta == -1` | ✅ 正常（口径差） |
| `delta != -1` | ❌ 这就是本包要查的 30 场 |

**调用参数必须对齐**（`verify.py` 里已写死）：

```python
sim.run_one(player, opponent, seed=..., round_id=...,
            below_master=True,                    # ★ 关键，见下
            native_activation_order=True,
            reseed_after_player_character=True,
            formal_ev_gate=500000, max_time=90.0)
```

> ⚠️ **`below_master=True` 是关键**。`alignment_expand.json` 的 `convention` 里写的是 `false`，
> 但那是**陈旧记载**——实测 `true` 才能复现账本（我第一轮漏传它，一致率只有 92.1%、134 场假失败）。
> 如果你的验证脚本用的是 `false`，先修这个参数再看代码。

## 已知结论（我这边测的）

| 指标 | 结果 |
|---|---|
| 自洽确定性（同输入连跑两遍逐位相等） | **1690 / 1690 全过** |
| winner 与神谕一致 | **1688 / 1690（99.88%）** |
| 事件数差 ≠ −1 | **30 场（1.8%）** ← 本包 |

## 30 场的共性（比逐场列表更重要）

1. **首个分歧点之前的事件序列完全一致**（type / timestamp / origin 全同）。
2. 从该点起**事件集合基本不变，只是相对顺序交换**——不是"算错了"，是"同样的事发得早/晚一点"。
3. 按 C++ 抢发的事件类型分三类：

| 类别 | 场数 | C++ 抢先发出 | 参考侧在同一位置发出 |
|---|---|---|---|
| **A** | **15** | 栈事件（100–110） | `item_activate` 或 `stack_gain` |
| **B** | **6** | `DealDamage`（type=1） | `stack_gain` / `heal` / `missed` |
| **C** | **8** | 其他状态事件 | 各异 |

**A 类占一半**，最集中的模式是「C++ 先发栈事件，参考侧先发 `Activation`」。
建议查 `CoreEventBus` 里两条路径的时序：栈事件走 `logEvent`（`Delayed` 模式下 `queueSignal`），
`Activation` 走 `emitSignal`（直接 `emitEvent`）——若 `loggingMode` 的切换时机与 Python 不同，
正好会产生这个现象。

## 事件行格式（C++ 侧 `gd_sim_dbg_event_line`）

```
ts=f:<16位hex>|type=<int>|id=<int>|tgt=<int>|parent=<int>|origin=<...>|params=<...>
```

- `origin` 形如 `o:item:<名字>#<实例号>`、`i:<整数>`（整数 = `DamageSource.Type` 转 keyword）
- `params` 形如 `d:{amount=i:1,refused=b:0,...}`，`i:`=int / `b:`=bool / `f:`=float
- `expected_py.json` 里对应字段已精简为 `[type, timestamp, parent_id, target, origin, params]`，
  `origin` 为 `[kind, identifier]` 或裸整数

## 我这边的可观测性缺口

| 缺什么 | 影响 |
|---|---|
| 库只导出 6 个接口（`gd_sim_init/register_item/register_character/reset_registry/run_one/run_batch`） | 读不到 RNG 状态、无逐抽追踪，只能靠事件反推 |
| 该 case 的神谕侧只有 `events.json`、无 `rng_log` | 没有真值抽取序列可比 |
| `GdVal` 完整定义不在 bundle 内 | 无法确认值语义细节（如 `min(int,float)` 的截断方向） |

若能补前两项任意一项，定位会快很多。

## 建议排查顺序

1. **先确认 `below_master=True`**
2. **从 `run101668_r7_o604708_r7` 入手**——第 2 条事件就分叉，且是纯顺序对调，最小复现
3. **重点看 A 类（15 场）**——栈事件 vs `Activation` 的派发先后
4. **`run704879_r14_o704504_r14`（delta +475）** 作为压力用例，修完 A 类看它是否自然收敛

