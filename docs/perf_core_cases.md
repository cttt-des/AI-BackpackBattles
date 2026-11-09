# 确定性回归精选集（60 场）

> 用途：每次性能优化后，先用这 60 场快速过闸，全绿再跑 1690 全量。
> 生成脚本：[tools/_perf_pick_core.py](tools/_perf_pick_core.py)｜数据：[docs/perf_core_cases.json](perf_core_cases.json)｜id 列表：[output/perf/core_cases.txt](../output/perf/core_cases.txt)

## 1 精选集口径

从 `output/oracle/expand/fights` 的 **1690 场**新语料中，用**加权集合覆盖**选出 60 场，要求覆盖：

| 维度 | 目标 | 达成 |
|---|---|---|
| 事件类型（EventType 数值） | 全部 | **32 / 32** ✅ |
| 事件类型名 | 全部 | **32 / 32** ✅ |
| 参战物品（lineup 双方含宝石） | 全部 | **512 / 512** ✅ |
| 职业配对（7×7） | 尽量 | 39 / 49（名额约束） |
| 胜负分布 | 两侧都有 | player 36 / opponent 24 |
| 长局（combat_time ≥ 40 s） | ≥ 2 场 | 3 场（最长 44.5 s） |
| tick 极值 | 最短 + 最长 | 0 tick 与 2669 tick 各 1 场 |
| 事件密度 | 最高 | 1 场 |

注：语料实测 `combat_time` 最大仅 44.5 s，**不存在超时场**（180 s 上限未被触及），因此本集不含超时样本；需要覆盖超时路径只能靠合成场景。

## 2 选取算法

**阶段 1（覆盖，47 场）**：加权贪心。每个待覆盖元素（事件类型 / 类型名 / 物品）的权重取「出现场次数的倒数」——稀有元素权重高，保证长尾物品不被常见物品挤掉。每轮取边际加权收益最大的场次。

**阶段 2（加厚，13 场）**：剩余名额按固定优先级补空缺，目的是提高**突变检出率**而非覆盖：

1. 未覆盖的职业配对（每对取事件最多的一场）
2. 长局场（≥40 s）至少 2 场
3. 最短 tick / 最长 tick / 事件密度最高各 1 场
4. 仍有余额则按事件密度补满

这样在覆盖全量语义面的同时，还压住了边界：极短局（0 tick）、极长局（2669 tick）、事件最密集场，以及 39 种职业配对的双方行为差异。

## 3 首次使用就抓到了 14 场回归（重要）

把这 60 场第一次跑完三方对齐，结果是 **45 / 60**。用原全量夹具（`gd_core_test/expand_align_cases.json`，非切片）逐场复跑确认：

| 类别 | 场数 | 含义 |
|---|---|---|
| 三方一致 | 45 | 可作绿基线 |
| `gdcore≡oracle 但 py 分歧` | **13** | **纯转写层回归**：Godot 侧与神谕完全一致，Python 侧跑出不同事件流 |
| `py 缺产物` | 1 | py 腿未产出该场（`run604839_r16_o500204_r16`） |
| 历史红本次转绿 | 1 | `run101354_r14_o101073_r14`，历史账本红、本次绿，疑似偶发 |

对照历史账本 `output/oracle/expand/alignment_expand.json`（2026-11-08，**1684 / 1690 三方一致**），这 14 场**历史全绿、现在全红**，
落在 `gd_core_py` 转写层，时间上与 2026-11-09 落地的 C 组生成器优化（C6 内联 / C1 `_iter` 直发 / C15 垫片局部化 / C4 静态绑定）吻合。

**结论：精选集有效**——它用 60 场覆盖出了全量抽样（当时 24/24 绿）漏掉的回归，且每场都能指出首个分歧事件。
**但也说明当前 `gd_core_py` 不是可用的绿基线**：在定位并修复这 14 场之前，精选集只能当「红名单监视器」，不能当作可通过的闸门。

红名单与复跑明细：[output/perf/core_cases_redness.json](../output/perf/core_cases_redness.json)

14 场回归名单（可直接喂 `--cases` 做二分）：

```
run704991_r8_o704410_r8, run300225_r6_o500231_r6, run101617_r16_o300168_r16,
run704847_r17_o704688_r17, run101710_r14_o100993_r14, run101617_r17_o704297_r17,
run704752_r14_o604627_r14, run101635_r11_o101268_r11, run604768_r17_o604707_r17,
run604839_r16_o500204_r16, run101702_r17_o101027_r17, run604796_r8_o300117_r8,
run704388_r14_o704267_r14, run704531_r15_o604621_r15
```

## 4 用法

> ⚠️ 两个坑（都踩过）：
> 1. **`--cases-json` 不要传全量夹具路径**——脚本会把夹具写回指定路径，传 `gd_core_test/expand_align_cases.json` 会被就地覆盖成 60 场（已用 `git checkout` 恢复）。
> 2. **不要重生成夹具**（不带 `--skip-fixtures`）：重算出的条目与历史夹具不一致（`affected` 变空、`stamina` 变 `5.0`、多出 `label_rng`），会凭空造出 13 场红。
> 正确姿势是 **`--skip-fixtures` + 原全量夹具**，只挑 `--cases`。

```bash
# 标准跑法：60 场 × 三方对齐（约 1 分钟）
IDS="$(cat output/perf/core_cases.txt)"
python -X utf8 tools/verify_oracle.py --cases "$IDS" --force --skip-fixtures \
  --fights-root output/oracle/expand/fights \
  --align-root output/oracle/align_expand \
  --cases-json gd_core_test/expand_align_cases.json \
  --alignment-out output/perf/alignment_core_cases.json
```

判读：`三方一致` 数等于 60 才算通过；出现 `gdcore≡oracle 但 py 分歧` 一律按回归处理（不是噪声）。

## 5 与 1690 全量的关系

| | 60 场精选 | 1690 全量 |
|---|---|---|
| 用途 | 每次提交后快速过闸 | 里程碑 / 合并前必须 |
| 事件类型与物品覆盖 | 100% | 100% |
| 配对覆盖 | 80% | 100% |
| 耗时 | 约 1 min | 约 11–20 min（py 腿） |

**精选集不能替代全量**：它保证「每一类事件与每一件物品都至少被触发一次」，但同一事件在不同时序下的组合路径（本项目的分歧主要来源）仍需要全量语料才能压住。它的定位是**快速失败**。

## 6 局限（写清楚，防误用）

1. **57 件物品从不产生事件**：语料 512 件参战物品中有 457 件出现在事件流里，其余仅存在于 lineup（沉默物品，例如被动加成类）。本集按 lineup 口径统计覆盖，因此 512/512 是「参战覆盖」，不等于「事件可观测覆盖」。
2. **超时路径无样本**：语料无 180 s 触顶场，需另行合成。
3. **10 个职业配对缺失**：名额被稀有物品占用；把脚本里 `LIMIT` 调至 70 重跑可补齐。
4. **不含 1.1.4 历史版本场**：语料为 expand 集（1.1.5–1.1.9），旧版对齐仍走原 914 场夹具。

## 7 产物清单

| 文件 | 内容 |
|---|---|
| [docs/perf_core_cases.json](perf_core_cases.json) | 60 场明细：case_id、入选理由、seed、tick、事件类型、物品列表 |
| [output/perf/core_cases.txt](../output/perf/core_cases.txt) | 逗号分隔 case_id，直接喂 `--cases` |
| [output/perf/core_cases_redness.json](../output/perf/core_cases_redness.json) | 14 场回归红名单 + 历史状态对照 |
| [output/perf/coverage_1690.json](../output/perf/coverage_1690.json) | 1690 场全量覆盖抽取（`tools/_perf_extract_cov.py` 产物） |
| [output/perf/alignment_core_cases.json](../output/perf/alignment_core_cases.json) | 本集最近一次三方对齐账本 |
| [tools/_perf_extract_cov.py](tools/_perf_extract_cov.py) / [tools/_perf_pick_core.py](tools/_perf_pick_core.py) | 抽取与选取脚本（可重跑复现） |

