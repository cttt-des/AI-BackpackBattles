# 对局语料记录器设计 v4（原样层 + 折叠层）

> 目标：纯外置只读地记录整局对局，产出两路真人语料——**局内决策**与**摆盘**，
> 分别对接两条 AI 训练路径。反复摆盘与反复切换锁定在**折叠层**归零，不进训练集。

---

## 0. 结论摘要

| 维度 | 决定 |
| --- | --- |
| 架构 | **双层**：`raw/`（原样、审计、可重放） + `corpus/`（折叠、直接喂模型） |
| 摆盘 | 只保留**开战瞬时快照**；拖动/移动/旋转过程在折叠层全部丢弃 |
| 锁定 | 原样层逐条记 `lock/unlock`；折叠层归并为每槽一条 `set_reserved(slot, final)`，净零则整段丢弃 |
| 买入/卖出/刷新/合成 | 真实资源消耗决策，**不压缩**（同名连续买可合并数量） |
| 训练路径 | 摆盘 → RL（模拟器自产为主，真人分布做基准/热启动）；决策 → 行为克隆 + 价值加权 |
| 状态表示 | 背包一律 v4 阵容（可直接 `ai/encoding.py`），决策侧另加商店/资源通道 |

---

## 1. 设计原则

1. **原始层永不失真**：所有采样与推断到的变化都落盘，出错可回查、可重放。
2. **折叠层只留决策**：训练集里每一条都对应"一个人做出的选择"，不含量化抖动、拖动轨迹、切换反复。
3. **每个样本自洽**：折叠后每条样本内嵌完整 `state`，不依赖前一行的状态。
4. **一条链可验证**：`snapshots` 锚点 + 原样事件 → 能重建任意时刻；折叠层产物能从原始层重算。
5. **两路 AI 共用编码**：摆盘与决策都用 v4 背包表示，避免两套几何。

---

## 2. 目录结构

```
output/records/<run_id>/              run_id = 20261028_180642_r01
├── meta.json
├── raw/                              ① 原样层（append-only，审计用，不进训练）
│   ├── R01.jsonl                     回合分片，逐事件 flush
│   ├── R01.jsonl.xz                  归档后压缩（标准库 lzma）
│   └── ...
├── snapshots/                        ② 快照（两层共用）
│   ├── R07_shop_open.json            回合开启：商店全貌 + 背包 + 资源（决策输入）
│   └── R07_combat_start.json         开战：双方 v4 阵容 + 商店残留（摆盘 & 标签归因）
└── corpus/                           ③ 折叠层（`tools/corpus_fold.py` 从 raw 重算，可随时重生成）
    ├── decisions.jsonl               局内决策样本
    ├── lineups.jsonl                 摆盘样本
    └── traces.jsonl                  可选：摆盘搜索轨迹（仅用于 RL 热启动）
```

**关键**：`corpus/` 是派生物，删了能重建；`raw/` 是唯一真值。

---

## 3. 原样层格式

### 3.1 meta.json

```jsonc
{
  "schema": 4,
  "run_id": "20261028_180642_r01",
  "started_at": "2026-10-28T18:06:42+08:00",
  "ended_at": "2026-10-28T18:29:03+08:00",
  "end_reason": "run_end",            // run_end | game_exit | user_stop | crash | limit
  "incomplete": false,
  "joined_mid_run": false,            // 是否中途开始录制
  "game": {"pid": 12345, "version": "1.1.8", "max_rounds": 18},
  "character": "Ranger",
  "mode": "ranked",                   // 用户标注，默认 unknown
  "source": "human",                  // human | bot | mixed
  "grid": [7, 9],
  "sampler": {"interval_ms": 400, "read_cost_ms_avg": 37, "gaps": 1},
  "recorder": {"version": "4.0.0", "config": { /* 生效配置 */ }},
  "notes": "hp 字段取 Game.tries(成员 68)，语义见 §11"
}
```

### 3.2 事件信封（`raw/R{nn}.jsonl`，一行一条，每条 flush）

```jsonc
{"seq":31,"t":412.87,"type":"buy","phase":"shop","round":7,
 "source":"diff","confidence":0.95,
 "action":{"slot":2,"id":"Dagger","price":3,"price_source":"decoded"},
 "delta":{"gold":-3,"shop":[{"op":"gone","slot":2}],
          "items":[{"op":"+","id":"Dagger","at":[2,3],"r":0}]},
 "anchor":"R07_shop_open",
 "evidence":{"saw_frames":2,"gold_before":12}}
```

### 3.3 原样层事件集

| type | 判定 | 备注 |
| --- | --- | --- |
| `round_start` | `round` 递增且回 shop | 触发 `R{nn}_shop_open` 快照 |
| `buy` | 槽 `bought` false→true，或槽消失+背包/储物箱新增同 id+金币减少 | 价格与 `-gold_delta` 交叉校验 |
| `sell` | 物品消失+金币增加 | 价=金币增量 |
| `place` | 新物品出现在背包 | 来自 shop 还是 storage |
| `move` / `rotate` | 同物品 `(at,r)` 变化 | **仅原样层**，折叠层丢弃 |
| `storage_in` / `storage_out` | 背包↔储物箱 | 同上 |
| `reroll` | 商店槽整体更换 | 带 `cost`、`kept_slots` |
| `lock` / `unlock` | 槽 `reserved` 翻转 | 免费、跨回合保留；买走时游戏自动 unlock **不另记** |
| `combine` | 多消失一出现 | inputs/output |
| `combat_start` | CombatLog 事件数开始增长 | 触发 `R{nn}_combat_start` 快照 |
| `combat_end` | `finished` / phase→shop | `result`(Win/Loss)、HP 前后 |
| `carry_over` | 新回合承接上一回合锁定槽 | `slots:[{slot,id,reserved}]` |
| `gap` | 采样中断超阈值 | 不猜动作 |
| `unknown_change` | 有变化但不可归类 | `confidence:0` |
| `run_end` | 回标题/进程消失/停止/超限 | `end_reason` |

**判定顺序**（避免重复报事件）：round 变化 → buy（含买走导致 reserved 复位）→ reroll → sell → 背包多重集比对（place/move/rotate/storage_*）→ lock/unlock → combine → unknown_change。

### 3.4 快照内容

`R{nn}_shop_open.json`：
```jsonc
{
  "round": 7, "gold": 12, "hp": 22, "wins": 3, "losses": 2, "character": "Ranger",
  "backpack": {"version":4,"grid":[7,9],"items":[{"id":"Dagger","at":[3,4],"r":0,"gems":[]}]},
  "storage": [{"id":"Broom","at":0,"r":0}],
  "shop": [{"slot":0,"id":"Wooden Sword","price":3,"normal_price":3,"on_sale":false,
            "free":false,"bought":false,"reserved":false}],
  "shop_meta": {"reroll_cost":1,"rerolls_this_round":0}
}
```

`R{nn}_combat_start.json`：玩家 v4 + 对手 v4（`read_fight_lineups()`）+ 开战前商店残留 + 资源快照。

---

## 4. 折叠层格式（训练集）

折叠由 `tools/corpus_fold.py` 从 `raw/` + `snapshots/` 重算，**幂等**。

### 4.1 决策点定义（压缩的根）

```
决策点 = 资源或商店发生净变化的时刻
  ├─ round_start
  ├─ buy / sell / reroll / combine
  └─ combat_start（裁决点）
```

**摆盘操作与锁定切换不构成决策点**，只更新"当前快照"，在下一个决策点被结算。

### 4.2 折叠规则表（核心）

| 原样层情况 | 折叠层结果 |
| --- | --- |
| 反复取出/放回同一物品 10 次，最终不在背包 | 净变化为零 → **整段丢弃** |
| 摆 A→换 B→再换回 A | 只留净结果 A（与段首相同则整段丢弃） |
| 一个槽 `lock→unlock→lock→unlock` 最终未锁 | **整段丢弃**，不产动作 |
| `lock→unlock→lock` 最终锁定 | 一条 `set_reserved(slot, true)`，中间切换丢弃 |
| 同段多槽各自切换 | 每槽一条 `set_reserved` |
| 摆盘整体变化 | 不产动作，仅"当前快照"更新；若该段被采为样本，摆盘以 `state.layout` 体现 |
| 连续同名同价买入 | 合并为 `qty`（默认关，`merge_qty:false`） |
| 每次 reroll | **不压缩**（每次真实花钱，是独立决策） |
| 买走导致 reserved 复位 | 并入 `buy`，不产 `set_reserved(false)` |

### 4.3 decisions.jsonl（局内决策样本）

```jsonc
{
  "run_id":"20261028_180642_r01","seq":118,"round":7,"round_frac":0.39,
  "state": {                       // 决策时的完整可观测状态
    "gold":12,"hp":22,"wins":3,"losses":2,"character":"Ranger",
    "backpack":{"version":4,"grid":[7,9],"items":[...]},
    "storage":[...],
    "shop":[{"slot":0,"id":"Wooden Sword","price":3,"on_sale":false,"reserved":false}, ...],
    "shop_meta":{"reroll_cost":1,"rerolls_this_round":1}
  },
  "actions":[                       // 本决策点内的净动作（已折叠）
    {"kind":"set_reserved","slot":2,"value":true},
    {"kind":"buy","slot":0,"id":"Wooden Sword","price":3},
    {"kind":"reroll","cost":1}
  ],
  "next_state": { ... },            // 下一决策点的 state（末点则用 combat_start）
  "outcome": {                      // 标签
    "round_result":"Win",           // Win | Loss | unknown
    "hp_after":22,"tries_after":3,
    "final_rank":2,                 // 整局排名，局末回填
    "rounds_survived":18,
    "engine_winrate":0.61           // 可选：用模拟器对 combat_start 阵容重算
  },
  "provenance":{"source":"human","confidence":0.95,"anchor":"R07_shop_open"}
}
```

一条样本 = 一个决策点的状态 + 该点内的净动作序列 + 下一状态 + 标签。

### 4.4 lineups.jsonl（摆盘样本）

```jsonc
{
  "run_id":"...","round":7,"character":"Ranger",
  "lineup":{"version":4,"grid":[7,9],"items":[...]},     // 开战瞬时摆盘（可直接 encoding）
  "pool":{                                              // 该回合可用资源（RL 输入/curriculum）
    "gold_at_start":12,"shop_at_start":[...],"storage_at_start":[...]
  },
  "context":{"hp":22,"round":7,"wins":3,"losses":2},
  "label":{"round_result":"Win","final_rank":2,"engine_winrate":0.61}
}
```

**这是摆盘 AI 的主训练/评估数据**：状态=阵容，标签=结果/胜率。

### 4.5 traces.jsonl（可选，仅 RL 热启动）

只在 `export_traces:true` 时生成。压缩规则：保留**净变化单调段**（同一物品的连续微调只留首末），并标注 `noisy:true`。
用途：给 RL 一个"人类可行域"的先验，**不进决策集**。

### 4.6 体积

| 层 | 单回合 | 单局（18 回合） | 压缩后 |
| --- | --- | --- | --- |
| raw | ≈6 KB（含 move/rotate） | ≈110 KB | ≈12 KB（lzma） |
| corpus/decisions | ≈1.2 KB × ~25 样本 | ≈30 KB | ≈5 KB |
| corpus/lineups | ≈2 KB | ≈36 KB | ≈8 KB |

---

## 5. 状态表示

- 背包一律 **v4 阵容**：`{"version":4,"grid":[7,9],"items":[{"id","at","r","gems","in"}]}`，与 `ai/encoding.py` 输入一致；
- 实例身份 = `(id, at, r, gems, in)` **多重集**（`core/lineup.py::item_signature`）；
- **不引入节点地址**：差分只靠规范元组，`ItemInfo` 保持原样（实现时去掉了原计划里的
  `node_addr`，理由：格子互斥已足够区分，地址会随节点重建漂移且无法落盘）；
- 已知退化：两件同名同旋转互换位置 → 折叠为 `unknown_change` 或净零丢弃（不污染样本）；
- 价格缺值写 `null`，`price_source:"unknown"`，绝不估填。

---

## 6. 程序设计

### 6.1 模块

```
core/lineup.py              v4 平铺序列化唯一实现 + 规范元组/多重集键
core/recorder.py            采样、阶段状态机、去抖、多重集差分、局边界
core/store.py               写盘：局目录、回合分片、快照、lzma 归档、读取侧
core/godot_reader.py   [改] read_combat_stats()（wins/losses/state，值域校验）
core/bot.py            [改] get_state 加锁 + character/wins/losses/game_state；
                             make_recorder / start_recording / stop_recording；
                             _execute_action 内 recorder.emit_action
gui/app.py             [改] 「开始记录 / 停止记录」按钮 + 状态行 + 「目录」按钮
config.yaml            [改] recorder: 段（含 fold 子段）
tools/corpus_fold.py        折叠：raw → corpus（decisions / lineups / traces）
tools/corpus_check.py       校验：快照/序号/金币/锁定/编码结构/可折叠
tools/corpus_stats.py       统计：样本数、动作分布、物品覆盖、每回合样本
tools/tests/test_recorder.py        差分层 + normalize（22 例）
tools/tests/test_corpus_fold.py     折叠层（8 例）
tools/tests/test_recorder_lifecycle.py 端到端：假 bot → raw → 归档 → 折叠（3 例）
docs/recorder_design.md             本文档
```

### 6.2 采样与阶段状态机

- 独立 daemon 线程；`interval_ms=400`，自适应 `max(200, 2×实测读取耗时)`；
- 阶段判定优先级：① `CombatLogReader.poll()`（事件数增长=开战，`finished`=结束，末事件 111/112=胜负）② `Game.state` ③ 场景启发式（商店槽有报价 / `read_fight_lineups()` 能读对手）④ `unknown` → `gap`；
- 战斗段降频 800ms，只采 HP/回合/双方阵容，**不做动作差分**；
- 去重：阶段签名不变则丢弃；
- **撕裂读防护 = 去抖（debounce）**：一次变化必须在下一帧仍然成立才提交为事件，只出现一帧就回退的抖动被丢弃（`confirm_frames=1` 关闭）。`_committed` 始终是最后一个已提交状态，diff 一律以它为基准，因此去抖**只延迟不丢动作**；
- 阶段判定优先用 `Game.state`（`member_state`，默认 -1 未标定）：0/1/2 → title/shop/combat，标定后比场景启发式更可靠。

### 6.3 局边界

首帧 `round==1` 开新局；`phase→title` / 进程消失 / 用户停止 / `max_events_per_run` 超限收尾；所有路径先归档当前回合、flush，再写 `meta.end_reason`；有 gap 则 `incomplete=true`。

### 6.4 配置

```yaml
recorder:
  enabled: false
  out_dir: "output/records"
  interval_ms: 400
  adaptive_interval: true
  combat_interval_ms: 800
  capture_bot: false
  confirm_frames: 2
  compress: "lzma"          # lzma | gzip | none
  auto_stop_on_title: true
  max_events_per_run: 20000
  gap_threshold_ms: 5000
  fold:                      # 折叠层参数
    export_traces: false
    merge_qty: false
    drop_zero_net: true      # 净零段丢弃（反复摆盘/反复锁定的过滤器）
    engine_winrate: false    # 是否调模拟器重算标签
```

---

## 7. 两条 AI 训练路径

### 7.1 摆盘 AI（强化学习）

**现状**：`ai/placer.py` 已是"形状类置换 + 宝石重挂"的搜索器，`ai/model.py` 是胜率代理，`ai/gen_dataset.py` 用 `GDCoreEngine` 自产数据。

| 环节 | 用真人数据做什么 |
| --- | --- |
| 状态/动作空间 | 沿用现有：状态=v4 阵容（`encoding.py`），动作=置换/换向/宝石重挂 |
| 环境 | 模拟器 `GDCoreEngine`（已有），可无限试错 |
| 训法 | RL（PPO 或自对弈），奖励=模拟胜率；真人数据**不直接用来训策略** |
| `lineups.jsonl` 用途 | ① **分布基准**：真人终局阵容的占格数/稀有度/宝石数分布，用于 curriculum 初态与采样校准；② **OOD 告警**：RL 产出的布局若与人类可行域偏离过大，提示可能过拟合模拟器漏洞；③ **评估集**：真人布局作为 held-out 对手池 |
| `traces.jsonl` 用途 | 仅热启动（行为预训练），必须与 RL 自我探索分开记录，便于今后消融 |

**为什么不学人类摆盘过程**：人类的试摆是低效搜索，RL 要学的是"摆放空间中的最优解"，不是"人怎么摸索"。

### 7.2 局内决策 AI（行为克隆 → 价值加权）

| 环节 | 内容 |
| --- | --- |
| 输入 | 新增 `ai/encode_decision.py`：背包走 `encoding.py` 得到张量，商店 5 槽（id one-hot + 价格 + 打折 + 锁定 + 已购）与资源标量（金币/HP/回合/胜负数）拼成额外通道 |
| 动作空间 | `{buy(slot), sell(item), set_reserved(slot,bool), reroll, end_shop}`，离散、定长；摆盘**不在**动作空间（交给摆盘 AI） |
| 训法 | ① 先 **BC**（`decisions.jsonl` 的 actions 作监督）；② 再 **价值加权/优势加权**（`outcome` 作粗标签）；③ 保险起见用 `engine_winrate` 或回合胜负在模拟器中重算，减少人类运气噪声 |
| 样本过滤 | `confidence < 0.8`、`unknown_change` 段、`incomplete` 局的样本默认不参与训练 |
| 数据量 | 一局约 450 决策样本 → 50 局约 2.2 万条，够做小规模 BC 验证 |

### 7.3 分布偏移对策（务必写进训练脚本注释）

1. 决策器只训 **价值/优势估计**，不做长期直接模仿；摆盘由 RL 独立产出；
2. 真人语料与 RL 摆盘的状态分布不一致，训练决策器时**混入一部分 RL 布局**作为状态增强；
3. 标签优先用"最终摆盘在模拟器中的胜率"，其次用回合胜负——真人胜负含运气与对手强度噪声。

---

## 8. 校验与工具

| 工具 | 内容 |
| --- | --- |
| `corpus_check.py <run>` | raw 的 seq/t 单调；每回合有 `shop_open` 与 `combat_start` 快照；金币收支与买卖价/reroll 成本一致；lock/unlock 与 `reserved` 闭合；`corpus/` 可由 raw 重算且逐字节一致 |
| `corpus_fold.py <run>` | 生成 `corpus/`；输出丢弃统计（净零段数、折叠掉的锁定切换数）——用来验证"噪声确实被过滤" |
| `corpus_stats.py <run|dir>` | 样本数、物品/动作覆盖、各动作占比、per-round 样本分布 |
| `test_recorder.py` | 合成帧覆盖：buy/sell/place/move/rotate/reroll/lock/unlock/combine/unknown；**反复摆盘归零**、**反复锁定归零**、锁→解锁→锁折叠为一条、撕裂帧、round 回落、phase 往返 |

**验收**：单测全绿；实机 5 局（含袋内物品、宝石、合成、卖储物箱件、连续刷新、锁定 3 回合、掉血、中途关闭）；抽查 20 条样本与画面一致；`corpus_fold` 的丢弃统计能对上人工预期；`decisions` 可直接被 `encode_decision.py` 读入。

---

## 9. 实施里程碑

| 里程碑 | 内容 | 验收 |
| --- | --- | --- |
| M1 | `core/lineup.py` + `core/store.py` + `core/recorder.py`（采样/差分/写盘）+ 单测 | 合成帧全部单测通过；实机 1 局能出完整 raw |
| M2 | `tools/corpus_fold.py` + `corpus_check.py` + `corpus_stats.py` | 折叠幂等；净零段正确丢弃；check 全绿 |
| M3 | GUI 开关 + config + 实机 5 局 | 无需干预自动分局；抽查通过 |
| M4 | 导出对接：`lineups.jsonl` 直接喂 `encoding.py`；`decisions.jsonl` 的最小 BC 脚本（可后置） | 编码无报错；BC 能跑通 1 epoch |

---

## 10. 明确假设与已知局限

1. 人类手动游玩时主程序保持运行（纯只读采样，不操作游戏）；
2. 不记像素轨迹与毫秒级时序，只记状态变化；
3. **不读物品实例内部数据**（`DragonEgg`/`Solaris` 等 `getData/setData`），同名蛋的状态差异无法表达——记录器如实不猜；
4. 战斗内细节不记录（已有 `combatlog_exporter.py` 独立负责），本记录器只取战斗起止与双方阵容；
5. `member_state` 标定为可选，失败退回 CombatLog + 场景启发式，功能不降级；
6. 折叠层的"净零丢弃"以 `diff(段首, 段尾)` 为空为准；若真人最终布局与段首不同但过程来回 20 次，只留 1 条净结果。

---

## 11. 实现状态（2026-10-28）

### 11.1 已落地

| 模块 | 状态 | 单测 |
| --- | --- | --- |
| `core/lineup.py` | ✅ v4 序列化 + `item_signature` / `flatten_v4` / `lineup_key` | 间接覆盖 |
| `core/store.py` | ✅ 局目录、回合分片（逐条 flush）、原子写快照、lzma 归档（压缩后校验字节数）、读取侧 `iter_run_events` | 间接覆盖 |
| `core/recorder.py` | ✅ 采样线程、去抖、阶段状态机、多重集差分、战斗起止、局边界、事件上限 | `test_recorder.py` 22 例 |
| `core/godot_reader.py` | ✅ `read_combat_stats()` / `read_state()`（越界返回 `None`） | — |
| `core/bot.py` | ✅ `get_state` 加锁、记录器钩子、动作上报 | — |
| `gui/app.py` | ✅ 记录按钮/状态行/打开目录；初始化后自动建记录器，`enabled: true` 自动开录 | — |
| `tools/corpus_fold.py` | ✅ 决策点切分、净零丢弃、锁定独立成决策、可选 traces、`--dry-run/--traces/--keep-zero-net` | `test_corpus_fold.py` 8 例 |
| `tools/corpus_check.py` | ✅ 9 项检查（见下） | 端到端 |
| `tools/corpus_stats.py` | ✅ 样本量/动作分布/每回合分布/高频物品 | — |
| 端到端 | ✅ 假 bot → raw 分片 → 回合归档 → 折叠 | `test_recorder_lifecycle.py` 3 例 |

跑测试（测试放在 `tools/tests/` 而不是 `ai/tests/`：仓库的 .gitignore 里有 `/ai/`，
放那里的测试不会进版本库）：

    python -X utf8 -m unittest tools.tests.test_recorder ai.tests.test_corpus_fold ai.tests.test_recorder_lifecycle

### 11.2 与 §1–§10 设计相比的偏差（都是有意的）

1. **不做"确认两帧才提交"的旧方案**，改去抖（§6.2）：旧方案在连续变化时
   只提交首帧，会丢动作；去抖只延迟一个采样周期。
2. **折叠层把"净锁定变化"单独成一条决策样本**：真人"锁不锁这个物品"是真实决策
   （免费、跨回合生效、影响下回合可购买集合），丢掉它会让决策集不完整。
   摆盘净变化仍不产样本（交给 RL），只作为下一个决策的 `state`。
3. **只有摆盘变化的段不打断前一个决策**：其 `next_state` 仍是下一个决策点前的状态，
   因此"买完再摆盘"的样本里，`next_state.backpack` 已含摆放结果。
4. **`node_addr` 未加入 `ItemInfo`**（§5）：差分改用规范元组多重集。
5. **`merge_qty` 未实现**：配置项已存在并会被读取，但当前不生效（连续同名同价
   买入仍记两条）。实现前不会被误用——需要时补 `fold_decisions` 后处理即可。
6. **`corpus_check` 的"逐字节一致"未做**：改为"可折叠 + 结构自检"，因为
   `fold_run` 是纯函数、raw 只增不改，逐字节比对意义不大且实现成本高。

### 11.3 已知问题（记录器外部，会间接影响本功能）

| 问题 | 影响 | 处置 |
| --- | --- | --- |
| `ai/encoding.py` 第 358 行 `for color, cells in geo["affected"].items():` 缺循环体，**当前无法 import** | `corpus_check` 的"编码兼容"退化为结构自检；`lineups.jsonl` 暂时无法直接喂编码层 | 属既有问题（本功能未改动该文件）。修复后检查项自动升级为真编码 |
| `member_wins`=66 / `member_losses`=67 为推定值（由 `curRound`=65 的位置推得，未活体标定） | 语料里的胜负计数标签可能是 `null` | `read_combat_stats` 做值域校验，不合理即返回 `None`；标定后可改 config |
| `member_state` 默认 -1（未标定） | 阶段判定少一路信号 | 退回 CombatLog + 场景启发式，功能可用；标定方法见 §11.4 |
| `rerollsThisRound` 未读取 | `reroll` 事件的 `cost` 取金币差值，同日多次刷新后仍是 `-1/-2` 的真值，但不区分"第几次刷新" | 需要时从 Shop 节点成员读（已定位到 Shop.gd 成员序），非必需 |
| `Game.tries` 与 `member_hp`=68 同槽 | `hp` 标签语义是"剩余生命次数"而非战斗血量 | meta.notes 已注明，训练侧按 `tries` 用 |

### 11.4 如何标定 `member_state`

1. 进游戏，分别停在标题界面 / 商店 / 战斗各一次；
2. 对每次取样 `read_members(game_node)` 的整数列表，找"只在 0/1/2 之间变化、
   且与界面一一对应"的下标；
3. 把下标填进 `config.yaml` 的 `godot.member_state`（当前默认 -1 = 关闭）。

标定后 `read_state()` 生效，阶段判定第一顺位用它；不标定则用 CombatLog。