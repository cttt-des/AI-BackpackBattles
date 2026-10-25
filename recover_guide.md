# 模拟器对齐 · 重新修复指南（2026-10-25 恢复后）

> 用途：工作区被误删、恢复到半月前版本并重录语料后，给"重新修复"的人一份最短路径。
> 只写**能直接指导动手**的东西；细节证据仍在台账与 wf_notes。

---

## 0. 先看清现在的盘面（别误判成"丢了"）

- **语料已全量重录**：`output/oracle/fights/` 914 场，写入时间 2026-10-24 20:14 ~ 10-25 00:08（新 oracle 1.1.9 构建）。
  `output/oracle/align/lineups/` 于 10-25 00:13 重新生成。
- `alignment.json` 现在 **3 / 914**，分布：py 分歧 531、oracle≠gdcore 298、py 缺产物 82。
- 含义：**不是数据被删，而是"新语料 + 旧内核"没重新对齐**。旧基线 815/914 是在旧语料上跑出来的，数值不可直接沿用。
- 已确认：我此前那几处内核补丁（idle_frame 饥饿、Zap 电弧抽）**已不在树里**，需要重做。

---

## 1. 重建次序（照这个顺序，别跳）

1. **先把 gd 腿跑通**（只跑 gd，不跑 py）：
   `tools/verify_oracle.py --skip-py --force` 或定向 `--cases`（定向会收缩夹具，收工后必须 `--force` 全量恢复）。
2. **同步 py 镜像**：`python -X utf8 tools/gd_to_py.py`（每次改 `.gd` 后必跑，这是 531 场 py 分歧的主因之一）。
3. **全量验证**：`tools/verify_oracle.py --force`（约 1~1.5 小时），再 `tools/alignment_digest.py` + `aligned_set.py snapshot`。
4. 每修一批就跑回归电池：`REG=run570_r18,run1160_r18,run1029_r2,run862_r18,run813_r12,run635_r12,run732_r12`。

> 经验：py 分歧数量大时，先怀疑"没跑 gd_to_py"，而不是逐个查 py。

---

## 2. 判定口径（唯一口径，不许放宽）

- **双判据**：①渲染战报逐行相等；②canonical 事件流逐条相等（`t` 按 1/60s tick 取整，type/side/origin/params/parent-depth 全等）。
- 三方：语料（`output/oracle/fights/`，**只读**）↔ `gd_core`（GDScript）↔ `gd_core_py`（Python）。
- 只看 gd 与语料不一致、且 py 与 gd 一致 ⇒ 是内核 bug（改 `.gd` 后重转写）。
- py 与 gd 不一致 ⇒ 转写层问题（`tools/gd_to_py.py` 或手改 py 未同步）。

---

## 3. 铁律：重放要"串行单场"

**踩过的坑（重要）**：`oracle_fight.gd` 用 `user://` 与对象池，**多个 Godot 实例并发会互相污染**。
同一场 run619 在 3 场并发批次里首分歧 idx22（错），串行单场两次都稳定 idx307（与 gd 同位置）。

- 一次只跑一个 Godot；批量用 `ORACLE_FIGHT_CHUNK` 串行分块，不要并行开多个进程。
- 产物目录必须重定向：`ORACLE_FIGHTS_ROOT=<scratch>`，**绝不写 `output/oracle/fights/`**。
- 命令模板：
  ```powershell
  $env:ORACLE_FIGHTS_ROOT = (Join-Path (Get-Location) 'output/oracle/probe/<tag>')
  $env:ORACLE_ONLY_CASES='<case>'
  $env:ORACLE_DEBUG=''          # 要 rng_log 就设 '1'
  $env:ORACLE_FIGHT_CHUNK='0'
  & output/godot36/Godot_v3.6-stable_win64.exe --headless --audio-driver Dummy --path oracle --script oracle_fight.gd
  ```

---

## 4. 定位方法（从粗到细）

1. **看首分歧**：`alignment.json` 的 `firstDivergence.index` + 事件内容，定位到"第几个事件、什么 type、什么 origin"。
2. **gd 事件 vs 语料**：`python -X utf8 tools/_probe_gd_compare.py <scratch目录> <case>`（若该探针还在；不在就按同样口径手写：canonical_stream + first_divergence）。
3. **逐抽对位**（查"静默多抽/少抽"唯一手段）：
   - 神谕侧：`ORACLE_DEBUG=1` → `rng_log.txt`（`序号 标签 from to => 值 @t=...`）
   - 内核侧：`ORACLE_ALIGN_TRACE=1` → `rng_trace.txt`
   - 对拍：`tools/_probe_draw_diff.py <rng_log> <rng_trace>` → 首个分歧抽号
   - 判读：一侧多/少 1 抽 ⇒ 表现层抽缺失/多余；区间不同 ⇒ 调用点参数不同；整体错位 ⇒ 前面静默多抽。
4. **神谕重放定"可修/不可修"**：串行单场重放 vs 语料
   - `i_r=None`（完全一致）⇒ gd 真 bug，可修；
   - `i_r == i_g`（与 gd 同位置同值）⇒ 语料外生（vintage），改 gd 修不到；
   - `i_r > i_g` ⇒ gd 提前错，可修；
   - `i_r < i_g` ⇒ 重放自己漂了，结论无效（多半并发污染，重跑）。

---

## 5. 已确认的类级根因（可直接照做的修复清单）

以下都是**已被证据定谳**、可以优先重做的（按收益排）：

1. **idle_frame 饥饿（域B）**：`Util.callNextFrame` 挂的是 SceneTree 的 `idle_frame`；语料由阻塞 tick 循环录制，回调**永不派发**。
   - 现象：Lightsaber 每 owner 只 proc 1 次，gd 旧实现每 6s 复 proc（run691 语料 2 次 vs gd 112 次）。
   - 修法：`gd_core/CoreUtil.gd::callNextFrame` 不派发（只记录），`CoreContext` 加 `idleFrameStarved`；与 `ctx.defer`（call_deferred）严格分开。
2. **Zap 电弧缺抽**：`Items/Animations/Zap.gd:32` 每次 zap 抽 1 次 `randf_range(4.0,4.02)`。
   - 落点：`gd_core_items/Exclusive/ThunderDrake.gd::zapItem`（hasOnChargeReceivedEffect 分支）、`TeslaCoil.gd::advanceItem`。
   - 曾一次修好 Coil 族 9 场。
3. **激活音高虚派发（幻抽）**：oracle `activate()` → `playActivationSound()` → 虚派发 `playDropSound(-6)`，基类抽 1 次 `randf_range(0.9,1.1)`；狼崽三家覆写零抽。
   - 修法：`CoreItem.activate/activateFromEvent` 改动态派发（`has_method`），`gd_core_items/Item.gd` 基类补 1 抽。
4. **PotM advanceTime 越权**：语料里 `advanceTime` 被 harness 吞没（Combat 是裸 Node2D），gd 却真的提前 12s。
   - 修法：`gd_core/CoreCombat.gd::advanceTime` 置空。
5. **转写层：形参类型强制**：GDScript `x: int` 传参即截断，py 丢了类型 ⇒ 除法变真除（Yggdrasil heal 21.6→21 等）。
   - 修法：`tools/gd_to_py.py` 在函数体首行插 `if x is not None: x = int(x)`；`:=` 推断默认值也要还原。
6. **classes 数据面**：`isClassItem()` 依赖 descriptor.classes（0=None、127=Neutral、其它=职业位）；Girl Power 的 `getNumDistinctAffectedItems` 直接吃这个数。
   - 注意：Girl Power 的 `grid.affected_cells` 与真实 tscn TileMap 坐标系**不一致**（半定谳，别当成简单缺 1 格）。

---

## 6. 已知"判死/vintage"族（别在上面白花时间）

在**旧语料**上已用串行单场重放证实"语料外生"（`i_r == i_g`）：
盲族到期（Light Goobert / Burning Banner / Lightning Potion，47 场左右）、Amulet of Light 事件序、False Life、Null Blade 部分、run628/run1231/run1349/run836 等。

⚠️ 但**新语料是重录的**，这批判定**必须在重录后的语料上重做**——重录后它们很可能直接变绿。
所以：先跑全量拿新基线，再决定哪些是新的 vintage。

---

## 7. 红线（跨会话有效）

- 禁 push/commit（除非用户明确要求）；`output/oracle/fights/` 与 `oracle/` 只读。
- 所有 Godot 一律 `--headless --audio-driver Dummy`（无窗口、静音）。
- 改 `.gd` 后**必跑** `tools/gd_to_py.py`。
- 改 `assets/battle_items.json` 后**必跑** `tools/gen_lineup_fixture.py` + `tools/gen_gd_core_data.py`。
- 全量验证用 `--force`；`--cases` 会收缩夹具，收工必须恢复。
- 删除/移动前先 `pwd` + 绝对路径双重确认，绝不针对工作区根目录做递归删除。

---

## 8. 还有哪些文档能查（都在盘上）

| 想看什么 | 去哪 |
|---|---|
| 全量对齐历史与逐轮证据 | `output/alignment_fix_log.md`（678KB，看尾部最新节） |
| 三阶段消耗链方法论 | `docs/alignment_fix_workflow.md` |
| RNG 真值（全局链、PCG、各类抽取点） | `docs/rng_truth.md` |
| 神谕 harness 语义 | `docs/oracle_workflow.md` |
| 确定性重放原理 | `docs/deterministic_replay_workflow.md` |
| 各卡定谳笔记 | `output/oracle/wf_notes/`（43 份，np6/np7/np9 最新） |
| 上一轮交接 | `output/oracle/offpeak_handoff.md`、`session_handoff_20261016.md` |
| 扩大用例/重录规划 | `扩大用例对齐规划.md` |
