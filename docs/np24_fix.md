# np24→np49 三方确定性对齐工程留档（2026-11-07 收口）

## 1. 目标与架构

**目标**：背包乱斗三方确定性对齐——语料（`output/oracle/fights`，914 场战斗回放）↔ `gd_core`（Godot 无头重放内核）↔ `gd_core_py`（Python 转写内核）三方逐事件、逐抽、逐渲染行一致。

**唯一出口**：`output/oracle/alignment.json`（914 行 perCase 保序，仅由 `tools/verify_oracle.py` 产出，禁手写）。长场独立账 `output/oracle/long_alignment.json`。

**最终状态：914/914 三方一致**（2026-11-07，r55 快照锚定 `output/_recovery/r55/r55_manifest.txt`）。

## 2. 三方语义

- **语料**：`oracle/oracle_fight.gd` 录制 harness 的回放件。np46 起逐案隔离（[M13] 标记）：每场开战前 Util.time/永久栈/EventBus/疲劳钟/ItemBook 注册桶全部归零 ⇒ **单场复放 ≡ 语料 by construction**。
- **gd_core**：`gd_core_test/OracleAlignBattle.gd` 重放器驱动 `gd_core/`（CoreTimer 注册表同构、CoreRng PCG 全局链、f32 定时器量化 `_f32eng` 等逆向真值面）。
- **gd_core_py**：`tools/gd_to_py.py` 转写（改 `gd_core/**` 后必须四树同步+重生成）。
- 守门：`tools/_np21_gate.py`（快速腿）；全量：`verify_oracle.py --skip-fixtures --force`。

## 3. 修复史大针（细节=commit 信息+台账 `docs/np24_issue_ledger.md` 全史）

| 面 | 代表修复 |
|---|---|
| rng 真值 | PCG 全局链（INC=2885390081777926815）、shuffleEngine/pickRandomEngine、逐抽对位法 |
| 计时器 | f01/f04/f11 计时器三定律、f32 存储镜像、注册表同构、np26fA multi 相位锚 |
| 物品语义 | 宝石槽实例真相、grid/棋盘真值面、heal 类型化截断、电荷几何、autoRage/盲池/热冷 |
| 装配期 | WEB CardConnector 漏扫、Flicker 延时抽、攻击尾隐形抽、activate 表现层链 |
| checkTriggerCount | np47 战斗钟直比（一修翻 16 场） |
| np46 净化重录 | harness 逐案隔离+事件闸 200000/墙钟 1200s+批量包装器（[M13] 门） |
| np49 收官 | ①Sandbag BuffTimer multi 错标（tscn 真身=普通 Timer）②语料池化残留（ItemBook 桶 freed 实例⇒EB 计数崩溃）→harness fresh instantiate+桶清空重注册+run1094 定向重录 |

## 4. 方法论遗产（详见台账 §6m63-6m110 压缩总账 D 节）

- 双链 trace 锚定对齐法+对齐器三件套（kind 归一/双向 skip/零宽过滤）
- 判读双验（events.json 非空+无 SCRIPT ERROR；Parse Error 空流=假 PASS）
- verify `--cases` 收缩夹具⇒用后 git checkout；幂等跳过三杀（先删产物）
- 探针纪律六步（备份→门控→重定向→还原→md5 留档）
- 长场 playbook（--focus 三腿定谳/py_ev_gate 按 1.2 倍全长/py resume 失明）
- 崩溃型静默分歧只留 SCRIPT ERROR 日志——日志检查不可省

## 5. 快照与复现

- r55 快照：`output/_recovery/r55/r55_manifest.txt`（alignment.json sha256+914 场语料逐件 sha256）
- 复现全量对齐：`python -X utf8 tools/verify_oracle.py --skip-fixtures --force` → 914/914
- 台账全史：`git log -p docs/np24_issue_ledger.md`
