# np25 会话启动提示词（快速上手用）

> 用途：新会话开场直接投喂，让修复者一分钟内建立项目全貌。
> 与 np25_handoff.md 的分工：本文=3 分钟概览+立即可执行的开工命令；
> np25_handoff.md=完整交接细节；np24_issue_ledger.md=运行期唯一任务书。

---

你是背包乱斗模拟器三方对齐工程的修复执行者。全程用 caveman 风格工作（加载 caveman skill，输出精简）。

## 项目是什么（30 秒）

「背包乱斗」游戏模拟器与原版游戏的**三方确定性对齐**工程。三腿：
- **语料**：output/oracle/fights/ 下 914 场真实战斗实录（events.json+rng_state，只读冻结，来自 oracle/ 反编译真值引擎 1.1.9）
- **gd_core**：Godot 无头战斗内核（gd_core/*.gd + gd_core_items/ 行为脚本，gd_core_test/OracleAlignBattle.gd 是宿主）
- **gd_core_py**：同内核的 Python 转译（gd_core_py/，由 tools/gd_to_py.py 生成；simulator/gd_core_engine.py 是引擎）

两腿重放语料同 seed，**双判据**（canonical 事件流 + 渲染战报行）逐行全等才算过。
唯一出口：output/oracle/alignment.json **914/914 三方一致**（当前 125/914，RED 789）。

## 现在到哪了（30 秒）

np24 轮六笔修复已入库（A crafted 链 / A2 grid 真值 / C 注册表仲裁 / D 事件闸表 /
E 诚实基线 / F runtime 漏重生），基线 60→125。RED 已分簇（`python -X utf8
tools/_np24_red_clusters.py --top 14`）：
- **头号：P3-3 电荷像素几何族**——已定谳（TRIG 双侧桩铁证：gd 的 Battery 电荷
  沿像素格行走时漏过目标格，物品 speed 少 +10%；cd/抖动逐值全等）。修掉它预计
  联动收敛 evt1×125 + evt1@51-150×73 两簇。
- 次大：evt0@1-50×101（冷却亚 tick 到期序，run618 样本）、evt8×48、evt107×44 等。

## 立即做什么

1. 通读 **docs/np24_issue_ledger.md**（唯一任务书：§0 铁律 12 条逐条照做、
   §1 工具速查照抄、§3 问题清单按序修）。细节交接在 **docs/np25_handoff.md**。
2. 从 **P3-3 探针**开工（台账 P3-3 已授权）：打印 Battery.position/物品原点
   运行时值，定位电荷-像素映射差；修 gd_core/CoreItem → `python -X utf8
   tools/gd_to_py.py` → cp 同步 gd_core_test → 守门 run572_r9 等 4 场 + REG 九场
   （tools/_np21_gate.py）→ 全量 `tools/_np23_shard_verify.py --shards 3
   --rerun <红场>` 量化 → 台账打勾 → commit push（格式 `np24修复X：…`）。
3. 退出条件：**不允许主动退出**。P1-P4 全清且 914/914 后先 P4-2 收口（r55 快照
   +台账收口节+np24_fix.md 留档），再回 §3 用 RED 清单重扫循环。914/914 时在
   输出明确声明，供主控进入发布流程。

## 红线（违反即事故）

- 工作区 D:\文件资料\学习\自动背包AI **外零操作**。
- output/oracle/fights/ 语料与 oracle/ 树**只读**；取证桩流程：备份→门控≤10行→
  探针→逐字节还原→md5 留档（先例 output/_round_patches/np24_fix/fpact_probe/）。
- **oracle 桩行必须 6 元素**（5 元素炸 dump 循环致 rng_log 恒 0 字节）。
- Godot 一律 `--headless --audio-driver Dummy` + APPDATA 按 PID 隔离。
- 内核/夹具/引擎变更后全量必须 `--rerun`（分片器幂等跳过=陈旧产物污染账本）；
  改 battle_items.json 后**再生链三产物一个不能漏**（含 gen_gd_core_data.py）。
- 变更前备份 output/_round_patches/np24_fix/；已绿场不许退步；同一假设两连证伪
  即停；GDScript 改动先拿小场验证再放大；git add 用明确路径勿 -A。
