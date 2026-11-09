# 任务提示词：定位并修复 60 场精选集中的 14 场 py 腿回归

（把下面“从这一行开始”到文件末尾整段复制给另一个 agent）

---从这一行开始---

你是本项目（`D:\文件资料\学习\自动背包AI`，Windows + MSYS bash，Python 3.14）的回归定位工程师。
任务：**找出让 14 场 Python 腿回归的确切代码改动，修复它，并证明 60 场精选集全绿、1690 全量不劣化。**

## 一、项目结构与必须遵守的硬约束

- `gd_core/*.gd` + `gd_core_items/*.gd` 是**唯一真源**（GDScript）。
- `tools/gd_to_py.py` 是**唯一转写入口**，产出 673 个 `gd_core_py/**` 模块（文件头写「自动生成，勿手改」）。
- `gd_core_py/_rt.py` 是 GDScript 语义垫片（float32、int 溢出、`_div/_mod` 符号、PCG32 等），**是语义规格说明**。
- **绝对禁止手改 `gd_core_py/` 下生成的 673 个模块**。要改就改生成器或 `_rt.py`，然后 `python tools/gd_to_py.py` 重转写。
- **逐位确定性不可破**：PCG32 逐位、`f32` float32 舍入、f64 左结合累加链（`ctx.time += DT`）、GDScript int/float 语义。任何优化不得改变求值次序与数值语义。
- 纯 Python 腿是永久对照实现，不许以“反正要换 Cython”为理由改行为。

## 二、当前状态（已确认的事实，不要重复验证）

1. 语料：`output/oracle/expand/fights/` 共 **1690 场**（expand 集，游戏版本 1.1.5–1.1.9），每场有 `events.json`（神谕真值）、`lineups.json`、`result.txt`、`rng_state.txt`。
2. 精简验证集：`docs/perf_core_cases.json`（60 场，覆盖全部 32 种事件类型与全部 512 件参战物品），id 列表在 `output/perf/core_cases.txt`。
3. **60 场当前只有 45 场三方一致**，14 场红（红名单 `output/perf/core_cases_redness.json`）。
4. 历史账本 `output/oracle/expand/alignment_expand.json`（2026-11-08）是 **1684/1690 三方一致**——这 14 场在历史里是**绿的**。
5. 红场类别：13 场 `gdcore≡oracle 但 py 分歧`（Godot 侧与语料完全一致，只有 Python 转写腿跑出不同事件流，属**纯转写层问题**）+ 1 场 `py 缺产物`（`run604839_r16_o500204_r16`）。
6. 时间上，回归出现在 2026-11-09 落地的 C 组生成器优化之后，涉及四趟：**C6 内联访问器 / C1 `_iter` 直发 / C15 垫片局部化 / C4 类引用静态绑定**。首发嫌疑是这四趟之一，但**必须用实验证明，不许凭直觉认定**。
7. 14 场回归名单：

```
run704991_r8_o704410_r8, run300225_r6_o500231_r6, run101617_r16_o300168_r16,
run704847_r17_o704688_r17, run101710_r14_o100993_r14, run101617_r17_o704297_r17,
run704752_r14_o604627_r14, run101635_r11_o101268_r11, run604768_r17_o604707_r17,
run604839_r16_o500204_r16, run101702_r17_o101027_r17, run604796_r8_o300117_r8,
run704388_r14_o704267_r14, run704531_r15_o604621_r15
```

## 三、跑验证的标准命令（照抄，别自创参数）

```bash
export MSYS_NO_PATHCONV=1; cd "D:/文件资料/学习/自动背包AI"
IDS="$(cat output/perf/core_cases.txt)"
python -X utf8 tools/verify_oracle.py --cases "$IDS" --force --skip-fixtures \
  --fights-root output/oracle/expand/fights \
  --align-root output/oracle/align_expand \
  --cases-json gd_core_test/expand_align_cases.json \
  --alignment-out output/perf/alignment_core_cases.json
```

只跑 14 场红名单时把 `--cases` 换成那串 id（逗号分隔，不带空格）。
判读：**`三方一致` 必须等于场次总数**。出现 `gdcore≡oracle 但 py 分歧` 一律按回归处理，不是噪声。
单场定位首个分歧点时看账本里的 `firstDivergence`（含 `t`、`type`、`actor`、`origin`、`params`、`parent`、`depth`，以及事件窗口），它会指出分歧发生在哪个 tick 的哪类事件上。

## 四、四个已经踩过的坑（不要重复踩）

1. **不要把 `gd_core_test/expand_align_cases.json` 传给 `--cases-json`**：脚本会把夹具**写回该路径**，会把它就地覆盖成 60 场（已发生过，用 `git checkout -- gd_core_test/expand_align_cases.json` 恢复）。只读使用、并配 `--skip-fixtures` 是安全的。
2. **不要重生成夹具**（去掉 `--skip-fixtures`）：重算出的条目与历史夹具不一致（`affected` 变空、`stamina` 变 5.0、多出 `label_rng`），会凭空造出十几场假红。
3. **`--force` 不可与 `--skip-godot` 同用**：删了产物又不补，会产生 `gdcore 缺产物` 的假阳性。py 腿依赖 Godot 侧产物提供激活顺序，所以必须连 gd 腿一起跑。
4. **`tools/_np21_gate.py` 单场不可靠**：它会因「定向清单没生效」中止。需要单场时用 `verify_oracle.py --cases <单场>`。

## 五、二分工序（生成器已内置开关）

`tools/gd_to_py.py` 支持按趟关闭优化：

```bash
GD_SKIP_PASSES=C6,C1,C15,C4 python tools/gd_to_py.py   # 逗号分隔，按趟跳过
python tools/gd_to_py.py --check                        # 只检查产物是否与真源同步，不写盘
```

趟名含义：`C6`=访问器内联、`C1`=`_iter` 直发、`C15`=垫片局部化、`C4`=类引用静态绑定。

**工序**：

1. `git status --porcelain` 确认 `gd_core_py/` 干净（有改动先 `git checkout -- gd_core_py`）。
2. 逐个单趟跳过：`GD_SKIP_PASSES=C15 python tools/gd_to_py.py` → 跑 14 场 → 记录结果；对 C1、C4、C6 重复。
3. 哪一趟跳过就变绿，哪一趟就是元凶；若单趟都不变绿，试两两组合（可疑：`C6+C15`、`C1+C15`），判断是否交互效应。
4. 定位到趟之后，读该趟在 `tools/gd_to_py.py` 里的实现（`_inline_accessors` / `_iter_inline` / `_shim_locals` / `_hoist_classrefs`），对照 `firstDivergence` 的事件类型与物品，找出**哪条改写规则在那个上下文里错了**。
5. 修生成器 → `python tools/gd_to_py.py` 重转写 → 先跑 14 场，再跑 60 场，全绿后跑全量。

**每次二分结束必须 `git checkout -- gd_core_py` 或重跑一次不带 env 的完整转写，让产物回到 HEAD 状态**，别把调试产物留在工作区。

## 六、允许的动作范围

- 允许改：`tools/gd_to_py.py`（转写规则）、`gd_core_py/_rt.py`（语义垫片，仅在证明垫片本身错时）。
- 允许临时改 `gd_core/*.gd` 做实验，**但修复方案不得依赖改真源来掩盖转写错误**——除非能证明真源与 Godot 行为不符，且修复后 gd 腿仍与语料一致。
- 不允许改：语料 `output/oracle/expand/fights/**`、夹具 `gd_core_test/*.json`、账本历史文件、任何 `output/perf/` 下的既有证据文件。

## 七、交付要求

1. **定位报告**：写进 `docs/perf_core_cases_regression_report.md`——哪一趟优化、哪条规则、在什么语法形态下出错、首个分歧场与分歧事件的证据、为什么历史 REG 九场没抓到。
2. **最小复现**：一段能独立跑出分歧的最小命令（单场 + 账本路径）。
3. **修复 diff**：`tools/gd_to_py.py`（或 `_rt.py`）的改动，附一句「为什么这样改不改变其他形态的语义」。
4. **验证证据**（缺一不可）：
   - 14 场 → 全绿；
   - 60 场精选集 → **60/60 三方一致**；
   - 全量 1690 → `aligned` 数 **≥ 1684**（历史基线；目标是 1690，若 1684 与 1690 的差值仍是历史那几场，需逐一核对是否与本次改动无关）；
   - 若碰过 PCG32 或 `f32`：`python tools/verify_godot_rng.py` 逐位通过。
5. **更新** `docs/perf_core_cases.md` 第 3 节，把「14 场回归」标记为已修复并写清根因。

## 八、止损与红线

- **投入 2 天仍未定位到具体规则 → 停止**，把唯一确定当的结论写进报告（例如「C15 单独跳过即全绿」），并附上二分矩阵全表；不要无休止试错。
- **不许为了变绿而放宽判据**（改 `canonical_stream`、改 `render_lines`、改比对口径、改语料）——那是作弊，比不修更糟。
- **不许把 `--skip-fixtures` 换成重生成夹具来“修”问题**。
- 若发现分歧其实源于历史账本本身过时（例如它生成时用的是不同代码），先用 `git stash`/`git worktree` 在历史提交上复跑一次来**证明**这一点，再改口，不要直接结论。
- 汇报时把「已验证」和「推测」分开写，验不过的数字不要出现在报告里。

## 九、开工第一件事

```bash
cd "D:/文件资料/学习/自动背包AI"
git status --porcelain | head
python -X utf8 tools/gd_to_py.py --check
```

确认产物与真源同步、工作区没有别人未提交的生成代码，再开始二分。

---到此结束---
