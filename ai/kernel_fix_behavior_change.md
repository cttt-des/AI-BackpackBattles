# gd_core_py 同 seed 复现性修复：**行为不保持**——同 (阵容, seed) 结局已翻转

【2026-10-03 · 缺陷修复轮补记。此前仓库内没有任何文档报告这一点，本文补上。】

## 一句话结论

2026-10-03 落地的 gd_core_py 同 seed 复现性修复（`gd_core_py/_rt.py` 的
`_MATH_BIND` / `_GID_CUR` / `_bind_battle` + `gd_core_py/gd_core/CoreContext.py::_init`
新增一行 `_bind_battle(_seed)`，战斗逻辑零改动）**只保证『同进程内同
(阵容, seed) 不再随历史漂移』，不保证『与修复前同 (阵容, seed) 同结局』**。
实测 25 个可测 (真值组, seed) 中 **2 局胜负翻转**（≈8%），另有 8 局非翻转局
时长差 >0.01s。**修复前后的一切引擎数字（胜负、时长、事件计数、eval 报告、
gen_dataset 标签）不可比。**

## 修复改了什么（越界检查已通过，此处只说行为）

* `gd_core_py/_rt.py`：全局 Math 流（物品脚本裸 `arr.shuffle()` /
  `Array.pick_random()` 的随机源）由「进程级、`DEFAULT_SEED` 起步、局间不重置」
  改为「`_bind_battle(seed)` 注入的**实例 seed** 起步」；`get_instance_id()`
  台账由「进程级单调计数、跨局只增不减」改为「每局换新台账（从 1 起步）」。
  无 ctx 的裸构造路径回落原进程级全局对象。
* `gd_core_py/gd_core/CoreContext.py:141-146`：`_init` 最早期调用
  `_bind_battle(_seed)`（必须在任何子对象创建之前）。
* 因果链：Math 流起点从「恒 `DEFAULT_SEED`」变成「本局 seed」、gid 序列从
  「跨局累积」变成「逐局从 1 起步」——两者都直接进入战斗的随机消费序列，
  故结局变化是**修复的必然结果**，不是实现偏差。

## 实测证据（本轮缺陷修复员现场复跑）

### 1) 快照对拍：ai/gd_outcomes_before.json vs ai/gd_outcomes_after.json

两份快照由 `ai/dump_gd_outcomes.py` 生成（seeds 42..46、25 组真值；其中 20 组
装配闸 `_MissingItem` 跳过，**25 个可测 (组, seed) 行**均来自 5 个可装配组）：

| 对比项 | 数字 |
|---|---|
| 胜负翻转 | **2/25**：`CombatLog_20261001_221121_R19_Loss` seed42 **1→0**、seed46 **0→1** |
| 时长差 >0.01s | 10 行（其中 2 行即上述翻转行，非翻转局 **8/25**；最大 \|Δ\|=6.29s：`002548` seed45 22.73s→29.02s） |
| reset vs no-reset（修复后内核） | `gd_outcomes_after.json` vs `gd_outcomes_after_noreset.json` 25 行逐条一致（重置≡不重置仍成立） |

### 2) 因果复现（同进程双语义对拍，2026-10-03 本轮实测）

`CombatLog_20261001_221121_R19_Loss` 原阵容，每局前 `reset_kernel_state()`：

| 语义 | seed 42 | seed 46 | 与哪份快照一致 |
|---|---|---|---|
| 现行内核 | (0, 9.93s) | (1, 14.48s) | `gd_outcomes_after.json` 逐位一致 |
| 修复前语义模拟 | (1, 14.2s) | (0, 13.15s) | `gd_outcomes_before.json` 逐位一致（胜负+时长） |

★ 复现口径注意：把 `_rt._bind_battle` 换成 no-op **无效**——`gd_core_py/gd_core/*.py`
一律 `from .._rt import *`，CoreContext 持有的是 import 期的直连引用。正确做法是
monkeypatch `_rt._math_rng` / `_rt._gid`（二者都经 `_rt` 模块全局名在调用期解析：
`_shuffle` 在 `_rt.py:606` 调 `_math_rng()`，`GodotObject.get_instance_id` 在
`_rt.py:1051-1052` 调 `_gid(self)`），强制回落进程级全局流/全局台账。

### 3) 翻转对真值对齐的净效应（说明『聚合指标掩盖翻转』）

对 5 个可装配真值组（真值胜负来自日志 `Win`/`Loss` 终事件，type 111/112）：

* 修复前快照：逐 (组,seed) 真值命中 **18/25**，逐组方向命中 **4/5**；
* 修复后快照：逐 (组,seed) 真值命中 **18/25**，逐组方向命中 **4/5**。

两行翻转一行从命中翻成未命中（seed46）、一行从未命中翻成命中（seed42），净效应
为零——**聚合对齐数看不出这次行为变化，但 eval / gen_dataset 消费的正是逐
(阵容, seed) 标签**，2/25（8%）的标签翻转对它们是实质变化。

## 数字不可比声明（仓库产物的年代线，按 mtime 实测）

| 产物 | 时间 | 内核口径 |
|---|---|---|
| `data/*.v0*.jsonl`（dataset_v1.v0/v0b/v0c、pilot.v0/v0b/v0c、dataset_v2、dataset_v3.v0b/v0c、gen_dataset.v0） | 10-02 ～ 10-03 10:13 | **修复前**（且属旧分布，本就按『旧数据隔离』归档，见 ai/gen_dataset.py 文件头） |
| 复现性修复落地（`gd_core_py/_rt.py`、`CoreContext.py`） | 10-03 14:39 | — |
| `ai/gd_outcomes_before/after/after_noreset.json` | 10-03 14:39 | before=修复前、after×2=修复后 |
| `data/dataset_v3.jsonl` / `data/pilot.jsonl` / `data/dataset_v1.jsonl` | 10-03 15:37 / 15:42 / 16:14 | **修复后** |
| `ai/eval_report.json`（17:35）、`ai/eval_report_seedcheck_rerun.json`（18:17，seeds 101..110、interrupted=false） | 10-03 | **修复后**（修复后唯一有效 eval 基线：5 组可评测，mean_delta −0.16） |

修复前的一切引擎数字（含上表第一行的数据集标签、更早的 eval 报告与对照报告）
**只能描述修复前内核，不得与修复后数字混用或直接对比**。

## 真值对齐现状（此前缺口：修复后的 gd_core 内核没有任何真值对齐数）

* `tools/compare_truth.py:90` 驱动的是**旧引擎** `engine.combat.CombatEngine`
  （不 import gd_core_py）——它根本测不到被修的内核。本轮实跑复测其方向命中为
  **15/25 组**（胜率多数 vs 真值），仅供旧引擎参照。
* 新增 **`ai/compare_gd_truth.py`**：协议与 tools/compare_truth.py 同款（同真值
  组、同 seeds 42..46、同事件类型映射），被测引擎换成 `GDCoreEngine`（每局前
  `reset_kernel_state()`）。本轮实跑（报告落盘 `ai/gd_truth_compare.json`）：
  * 25 组中 **20 组装配闸 `_MissingItem` 跳过**（真值实录混有不可装配件），
    可测 5 组；
  * **逐组方向命中 4/5**（唯一未命中：`CombatLog_20261002_003030_R19_Win`，
    sim 胜率 0/5 vs 真值 Win）；**逐 (组,seed) 胜负命中 18/25**；
  * 时长中位数与真值逐组差异 1.6s ～ 22s（`002548` 组 sim 22.0s vs 真值 44.0s
    为最大），逐类型事件分布比详报告。
  * 局限：可测子集仅 5/25 组，这些数**不是**全量真值对齐率，不得外推为
    『gd_core 命中率 72%』之类。

## 本轮（缺陷修复轮）改动清单

1. 本文档（新增）。
2. `ai/kernel_reset.py` 头注释：补「修复不保持参战路径行为」声明。
3. `ai/dump_gd_outcomes.py` 头注释：用途由「行为保持对照」改为「行为变化对照」。
4. `gd_core_py/_rt.py`：`_MATH_BIND` 注释与 `_bind_battle` docstring 补同一声明
   （仅注释，行为零改动）。
5. 新增 `ai/compare_gd_truth.py` + 首轮报告 `ai/gd_truth_compare.json`。

## 本轮重跑记录（受影响的验证，均本轮实跑）

* `python -m unittest ai.tests.test_kernel_reset -v` —— **6/6 通过**（51.6s；
  pytest 未安装，仓库该测试文件本就按 unittest 直跑设计）。
* `python ai/dump_gd_outcomes.py --out ai/_tmp_gd_outcomes_check.json` ——
  125 行（25 可测）与 `ai/gd_outcomes_after.json` **逐位一致**（注释改动零
  行为影响；临时文件已删）。
* `python ai/compare_gd_truth.py` —— 方向 4/5、逐行 18/25（上文；报告落盘
  `ai/gd_truth_compare.json`）。
* `python tools/compare_truth.py` —— 15/25（旧引擎参照，上文）。
* `python ai/eval.py --seeds 2 --limit 2` —— 自测通过（SKIP 1 + EVAL 1，
  SUMMARY 0.000 0/1）。★ 注意：eval.py 默认 `--out ai/eval_report.json`，
  自测**覆盖**了 17:35 的全量报告；全量基线数据仍在
  `ai/eval_report_seedcheck_rerun.json`（18:17，seeds 101..110）。为恢复
  该产物，本轮随后用默认参数重跑了**全量 eval**（结果见下）。
* 全量 `python ai/eval.py`（本轮重跑，约 18 分钟）—— 汇总：5 组可评测、
  mean_delta −0.16、improved 0/5、1 组 delta CI95 不含 0（与修复后既有
  基线 `eval_report_seedcheck_rerun.json` 的汇总一致）；`ai/eval_report.json`
  由此恢复为全量口径。
