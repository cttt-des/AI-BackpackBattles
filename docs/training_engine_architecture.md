# 《背包乱斗》AI 训练引擎架构设计 v2

> 目标：重写核心引擎（**放置 + 战斗 + 商店**），支撑 AI 训练——**GPU 高并发批量仿真、单步快**。
> v2（2026-09-22）：在 v1 基础上并入第二轮深度调研（GPU 批量仿真框架、离线 RL/BC→RL 前沿、构筑游戏 AI 工业实践、KG 工程），技术选型有量化依据，训练管线细化到可执行的切换条件。
> 性质：架构设计。引擎层遵循"固定形状、无动态分配、host 零拷贝"三原则，因此对具体框架（JAX/PyTorch）保持可替换；选型倾向与证据见 §2.4。
> **定位说明（2026-09-22 重定向）**：本文是**远景架构素材**——按经验过早定架构意义不大。实际路线图：
> **高速模拟器 + 开放服务协议 → 启发式搜索 + 人工奖励设计 → 专家轨迹积累 → SL/BC-RL 阶段设计**。
> 本文档的价值是把后几个阶段的设计约束提前备好；各约束的调研依据见 [research/README.md](research/README.md)（问题-方法导向的 5 份专题报告）。
> 机制真值：[engine_truth.md](engine_truth.md)（战斗）+ [逆向源码逻辑地图](逆向源码逻辑地图.md)（商店经济，行号级）。

---

## 0. 调研结论速览（两轮调研合并）

**同类开源 + 经典论文（第一轮）**：orbit-wars-torch 是最像的单一模板（GPU batched 引擎三 ABC）；Super Auto Pets 生态验证 opponent 注入 + MaskablePPO；AlphaStar 验证 BC→league RL 与自回归动作分解；DECKARD 验证"crafting 世界模型→交互验证→注入 RL"。

**第二轮（本轮新增）关键量化结论**：

| 证据 | 数字 | 结论 |
|---|---|---|
| Craftax（JAX，含战斗/掉落/合成的 crafting 游戏，与本项目最同构） | RTX 4090 上 26~40 万 SPS（4096 env），10 亿交互 <1h | "固定实体上限+掩码"在同类游戏上可行且高效 |
| Pgx（JAX 游戏套件） | 单 A100 全环境 ≥10⁵ samples/s | 纯函数 step + 显式 PRNG key + legal_action_mask 是标准答案 |
| CPU 进程级 vec env | 5~10K SPS | 比 GPU 原生低 1~3 个数量级——只配当 debug 通道 |
| Sebulba（DeepMind Podracer） | 单机 TPU 200K FPS | **大 batch 提吞吐但伤数据效率——优先调网络/minibatch，不盲目堆 batch** |
| NLE（富交互游戏留 CPU） | ~5,600 SPS | 反面教材：引擎不进设备，训练必被采样卡死 |
| 决策/仿真时标 | 文献近空白（auto-battler 时标问题是开放点） | 采用 SMDP macro-step 方案（§4.3，有 Option-Critic/SMDP 理论依据） |
| LoCAM 搜索（2026.9） | 采样对手世界 + MC 搜索：胜率 26.8%→51.35% | "learned proposal + 模拟器 search"混合范式收益巨大 |
| ByteRL（LoCAM 冠军） | 构筑/战斗两阶段共享嵌入，γ=1.0，Bo5 胜 top-10 主播 | **阶段解耦 + 共享物品嵌入是被验证的设计** |

---

## 1. 总体架构

```
┌──────────────────────────────────────────────────────────────┐
│ L4 训练层    P0 数据引擎 → P1 BC → P2 离线RL → P3 O2O → P4 League │
│              （每阶段有量化验收与防崩 checklist，见 §5）           │
├──────────────────────────────────────────────────────────────┤
│ L3 策略层    阶段×流派二维解耦：Meta-Controller + 条件化子策略      │
│              共享物品嵌入（KG 初始化，端到端微调；FiLM 二期）        │
├──────────────────────────────────────────────────────────────┤
│ L2 环境封装层  ObservationEncoder │ Policy │ Opponent（三 ABC）    │
│              observation/internal-state 分离；合法掩码内建于引擎    │
├──────────────────────────────────────────────────────────────┤
│ L1 仿真内核层  BatchedEngine：状态=定长张量，战斗=lockstep scan     │
│              放置/商店/战斗三段；乐观重置池；terminal auto-reset    │
├──────────────────────────────────────────────────────────────┤
│ L0 真值层    decompiled_full/ (v1.1.7) + engine_truth.md         │
│              逻辑地图 + engine/（单 env 真值内核，冻结为对照物）     │
│              assets/kg/items_kg.json（物品 KG，M0 已建）           │
└──────────────────────────────────────────────────────────────┘
```

四条硬约束（不变）：

1. L1 的一切行为必须能对照 L0 行号；新行为不许凭空发明。
2. 全部 RNG 状态可种子化、可序列化（BalancedRng 状态即对局状态）。
3. 从第一天建对账：批量内核 vs `engine/` 单 env 指纹回归；"工具全绿 ≠ parity"。
4. 7 个职业的差异（初始物品/血量/体力）M1 就进内核（Neural-BGSimulator 卡死"无英雄"的教训）。

---

## 2. L1 仿真内核层（放置 + 战斗 + 商店）

### 2.1 十条设计模式（违反任何一条都会踩已验证的坑）

1. **状态 = 单一结构体，形状编译期恒定**；动态集合一律"最大容量 + 存在掩码"（Craftax 铁律）。
2. **step/init 为纯函数；随机性显式 PRNG key 传入**，不藏 state 内（Pgx v2 模式，防信息泄漏）。
3. **observation 与 internal state 分离**（Jumanji 模式）：obs 给策略，state 给仿真器。
4. **观测用符号编码**（物品 ID 索引 + 属性数值），不做像素（Craftax 实测像素慢 10×）。
5. **合法动作掩码在环境内计算**随 obs 返回（购买/放置/合成的位置合法性）。
6. **乐观重置池**（M≪N，1:16）：重置时从预生成池采样，商店/对手生成成本均摊（Craftax 核心创新；200 步 episode 下池耗尽概率 <1e-10）。
7. **决策步与仿真步两级 API**：`decision_step`（商店+布阵）与内部 `combat_substeps`（定长 scan + 终止掩码）；战斗结果折叠为单转移（SMDP，§4.3）。
8. **引擎与任务/课程解耦**（MiniHack 模式）：物品池、对手强度、目标函数数据驱动注入；env 版本化注册（Jumanji 模式），平衡性实验可复现。
9. **动作 spec 分层**（Neural MMO 模式）：动作类型掩码 + 参数掩码。
10. **terminated 与 truncated 显式区分**；截断必须 bootstrap V(s) 并给剩余时间输入（Time Limits 论文，arXiv:1712.00378，否则回放/GAE 被污染）。

### 2.2 状态布局（候选，M0 评审冻结）

| 状态 | 形状 | 内容 |
|---|---|---|
| 背包格 | `(B, 2, 7, 9)` | filled 层（实例 id）+ bag 层（容器占格）；旋转查实例表 |
| 物品实例表 | `(B, N_item≈64, D)` padded+mask | item_id、row/col/w/h、rotated、owner、cooldown、charges、gems、持久参数 |
| 商店 | `(B, 5, D_shop)` | 槽位 descriptor id、价格、折扣、reserved、gate/unique 标记 |
| 角色 | `(B, 2, D_char)` | hp/stamina/11 维 Buff 栈/四元 BalancedRng 状态/经济统计 |
| 回合 | `(B, D_round)` | round、gold、wins/losses/tries、reroll 计数、bagPity、tradeChance、soldRoll |
| 战斗 | `(B, D_combat)` | combatTime、疲劳 counter、stun、battleRage、触发优先级序 |

dtype 纪律：物品 ID/血量 int16/int32，仅归一化字段 float32；热点规则表用 host 常量 + gather，避免 XLA 常量折叠膨胀计算图。

### 2.3 三段 kernel 要点

- **战斗**（优先做，有真值内核对照）：60Hz 固定 dt lockstep；冷却推进→触发（±5% 抖动、同帧限流 3 次、doubleActivation）→行为执行→角色 1s tick→疲劳引擎（17s 首击、60s 后 0.2、先对手后玩家）→17 步伤害链（顺序不可换）→判胜收尾。已结束 env 用 `fight_ended` mask 短路（早退只省算力不改语义）。
- **放置**：占用掩码、旋转交换 w/h、容器嵌套（bag filled 层查询）；`can_place` 输出 `(B, 7, 9, 2)` 合法掩码直接喂动作 mask；背包整体平移（shift_*）是真机制保留（`Inventory.gd:920-947`）；与 ottoblep/backpack-battles-solver（C++ 放置求解器）协作——策略输出"买什么"，placement 可由 solver 求解或生成监督数据。
- **商店**：rarityOdds 按回合查表 + categorical 采样；首店保底/unique 槽/gate/锻造锤 7%-20%/包保底 9 抽实现为 batched 条件分支（`Shop.gd:546-672`）；阶梯刷新价 1→2→3；促销 rollSale(0.1)；合成 Recipe 打分 + addIngredient 键合，`call_deferred` 改为批量"下 tick 队列"；易物 tradeChance 协议 + 差价 1-2 定价（`ChestnutTrade.gd:94-101`）M3 移植。**注意：v1.1.7 卖价=买价（`Item.gd:4228` 附近），写内核时以真值为准，勿凭直觉**。

### 2.4 技术选型（量化依据）

| 方案 | 代表 | 单卡吞吐 | 判定 |
|---|---|---|---|
| 全栈同设备编译（JAX 系） | Craftax/Pgx/PureJaxRL | 2.7万~40万 SPS | **默认倾向**：同类游戏成功先例最多，乐观重置/固定上限+mask 现成 |
| PyTorch 自定义 kernel | Isaac Gym 式 | 10万+ | 备选：自写 kernel 开发成本高一个量级；引擎层遵守 §2.1 三原则后仍可落地 |
| CPU vec env + 优化采样器 | Sample Factory | 10万（受 CPU 核数限） | 仅 baseline/debug |
| GPU env + 异步 learner | Sebulba 式 | 单机 200K FPS | 单机单卡无必要，同设备 interleave 更简单 |

**决议**：架构按"全栈同设备编译"设计（引擎与训练同图、零拷贝）；绑定 JAX 前先做一个 200 行的 spike：用现有 `engine/` 真值内核包 `vmap(step)` 测吞吐，验证 RTX 5080 上的可行性再定框架。若坚持 PyTorch，引擎层接口不变（三原则保证可移植），损失的是 jit/vmap 的免费批量。

---

## 3. L2 环境封装层

### 3.1 三 ABC（orbit-wars-torch 模式）

`ObservationEncoder(引擎 (B,...) 张量 → DecisionBatch)` / `Policy(nn.Module → logits+value)` / `Opponent(非学习席位动作)`，全部可替换。

### 3.2 观测编码（推荐混合方案）

- **物品集合 → transformer 编码**（AlphaStar 式）：每实例一行（item_id 嵌入 + 属性 + 坐标 + 朝向）。
- **背包 7×9 空间特征层** + 商店 5 槽序列 + 标量（金币/血量/回合/reroll 价）+ LSTM core 记跨回合经济。
- **GNN 读邻接协同**（格子=节点、协同边=attention），优势：背包尺寸/物品池变化可迁移（TransfQMix 跨规模迁移）。
- 与开源 STS 项目（card_id 归一化标量）相比，嵌入化是本架构的明确升级点。

### 3.3 物品 KG 与嵌入（M0 已建数据层，详见 §6）

- KG 嵌入（RotatE/CompGCN 预训练）→ 策略网络物品嵌入层**初始化** → 端到端微调（ByteRL 共享嵌入的升级版）。
- 二期：职业/流派嵌入做 FiLM 条件化（同一物品跨流派语义分化）。

### 3.4 动作空间：自回归分解 + pointer + 掩码

```
action_type ∈ {buy, place, move, sell, fuse, reroll, lock_shop, end_turn}
  ├─ buy  → pointer(商店 5 槽) → place 参数
  ├─ place→ pointer(背包实例表) → (row, col) → rotate
  ├─ sell → pointer(背包实例表)
  └─ fuse → pointer(主物品) → pointer(材料)
```

- 合法性掩码内建于引擎 step 之前；训练 MaskablePPO 或等价。
- 可选压缩：策略只出 buy/sell/fuse/reroll，`place` 交 solver——动作空间进一步缩小。

### 3.5 对手注入

`StaticPoolOpponent`（lineups/ 回归测试）/ `CheckpointPoolOpponent`（己方快照池，每 N update 同步）/ `LeagueOpponent`（main + main-exploiter + league-exploiter，AlphaStar league）。

---

## 4. L3 策略层：阶段×流派二维解耦

### 4.1 阶段解耦（必须）

| 阶段 | 类比 | 观测 | 决策 |
|---|---|---|---|
| 商店/构筑 | ByteRL CB 阶段 | 商店 5 槽 + 经济标量 | categorical over 可购物品 |
| 摆放/合成 | 中观层 | 网格邻接编码 + 合法掩码 | place/fuse/move |
| 战斗 | ByteRL BT 阶段 | **不动作**——模拟器 rollout | 不学（或轻学评估头） |

三者**共享物品嵌入**（θ_shop/θ_place 共享 θ_embed + 阶段指示 δ，ByteRL 已验证）。γ=1.0 用于终局胜负奖励（多阶段信用分配不偏，ByteRL 实证）。

### 4.2 流派条件化（子策略库）

- Meta-Controller 预测当前构筑子目标（macro-goals，MGG arXiv:2110.14221 的"示范→抽象→条件化"三步）；子目标种子与 `lineups/*.json` 命名一致（护甲墙/毒弓/匕首群/药水链接）。
- 长期：Voyager 式技能库——成熟小策略参数化入库（"第 6 回合前凑出某合成件"），蒸馏进大策略时保留可解释索引。
- DIAYN 互信息技能库（无监督学流派技能）作为备选增强。

### 4.3 信用分配：战斗 = SMDP macro-step（理论依据）

- 整段战斗折叠为单转移：段内回报 R=Σγᵏr，段间折扣 γ^τ（τ=段长），bootstrap 只在段终止处——**唯一理论上自洽**的做法（SMDP，Sutton 1999；Option-Critic 1609.05140）。
- 实践配比（AlphaStar/DeepMind 系）：策略层面段即决策单位；价值层面段内逐步 V-trace + 段级截断并用，不真把整段当一步更新价值。
- 全局 γ=0.99（18 回合 horizon 不长，macro 化主要为信用清晰而非省算力）；段内 GAE λ=0.9~0.95 单独调，与全局 γ 解耦。
- 截断语义：战斗设 substep 上限属 truncated，末端 bootstrap V(s) + 剩余时间输入。

### 4.4 与搜索混合（收益证据充分）

- **learned shop/摆放策略 + 模拟器 rollout 战斗评估**（sapai 范式）：战斗完全免学习。
- **采样对手世界 + MC 搜索**（LoCAM arXiv:2609.06816）：不完美信息下不枚举信念空间，从先验采样对手构成"世界"做完美信息搜索，胜率 +24.6 点且更抗 best-response 攻击。
- MCTS 只在关键决策点（决赛圈合成、大 D 摆位）按需调用；构筑终局可用 ILP/solver 做 teacher（Underlords NP-complete 论文）。

---

## 5. L4 训练管线：P0~P5（细化到切换条件）

### 5.1 阶段划分

| 阶段 | 内容 | 算法 | 量化验收 |
|---|---|---|---|
| P0 数据引擎 | 真值引擎+启发式批量自对局产日志；逆动力学/特权 teacher 打标 → 数据集 D0 | 特权信息蒸馏（Kickstarting 范式） | D0 覆盖 ≥80% P0 物品出场 |
| P1 BC 基线 | Filtered BC（过滤胜率<阈值轨迹） | 行为克隆 | 对脚本基线胜率 ≥55% |
| P2 离线 RL | IQL（in-sample，对合法掩码天然友好）或 CQL-discrete | 离线 RL | 对 π_BC ≥60%，且 OOD 动作 Q 值无尖峰 |
| P3 离线→在线 | Cal-QL 式微调或 PROTO 正则退火；replay 混合 1:1 起步线性退 | O2O | **切换触发**：在线平均 TD 误差 < 离线 2 倍 ∧ 对 π_BC 胜率 >70% 连续 3 评估窗 |
| P4 League 自博弈 | PFSP 采样（3-5 快照）+ V-trace + UPGO + SIL 辅助（top-10% 回合 BC，权重 0.1 退火） | 多智能体 RL | TrueSkill mu 上升；胜率矩阵报告 |
| P5 课程硬化 | PLR 按对手强度/起始池复杂度优先采样；1-2 个 exploiter 持续攻击 champion | 课程学习 | 对历史检查点矩阵 + 95% CI |

切换条件依据：O2O 三 regime 实证（arXiv:2510.01460——保护更强的一方同时保留可塑性，63 case 中 45 个符合）。决策 Transformer 调研结论：**不适合当主干**（固定 return 条件表达不了战斗方差、18 回合上下文易爆、Filtered BC 在稀疏奖励下打平 DT）；最多当 BC 初始化对比基线。

### 5.2 防崩 checklist（每阶段执行）

- [ ] Critic 切换期价值钳制（历史 Q 分位数内）
- [ ] 双轨监控：proxy 奖励 vs 真实胜率（冻结基线定期对局）——奖励 hacking 存在相变点（arXiv:2201.03544）
- [ ] 在线数据占比退火曲线写死，不依赖验证触发
- [ ] Q 值漂移 >3σ 即回滚快照并减半学习率
- [ ] 合法掩码训练/推理共用同一代码路径
- [ ] exploit 快照超 main 15% 时触发"针对训练"而非替换 main
- [ ] 战斗 shaping 小分与终局胜负奖励分账记录，hacking 可归因

### 5.3 评估工程

- 内部联赛 **TrueSkill**（mu 25/sigma 25/3 初始化，比 Elo 收敛快，OpenAI Five Arena 实践）。
- 版本报告 = 对 N 个历史检查点 + 脚本 bot 的**胜率矩阵 + 95% CI**；警惕 LoCAM 式"高平均胜率但高可利用性"（arXiv:2404.16689）——报告 best-response 攻击下的最低胜率。

---

## 6. 物品知识图谱（M0 已落地）

### 6.1 KG schema（已实现）

- **节点**：`Item`×518（属性 17 项：size/category/rarity/price/cd/伤害/材质/职业掩码等）、`Tag`×35、`Keyword`×251（named_params 键）、`Material`×15、`Character`×7。
- **data 边**（2946 条，`tools/build_item_kg.py` 产出 → `assets/kg/items_kg.json`）：SHARES_TYPE 1025 / USES_KEYWORD 1259 / MADE_OF 479 / EXCLUSIVE_TO 129 / HAS_TAG 54。
- **语义边占位**（空表 + TODO）：CRAFTS_INTO（从 CraftingManager.gd + CSV 抽取）、ADJACENT_SYNERGY（LLM propose + 模拟器共置 verify）、COUNTERS、CO_OCCURS（回放统计，权重=lift/交互胜率差，带时间窗）。

### 6.2 数据管线的 propose-verify 闭环

1. **确定性边**：配方/类型/职业——脚本从结构化字段与源码抽取（`data`）。
2. **LLM 只 propose 语义边**（协同/克制候选 + 每物品 1-2 句语义描述），**verify 用模拟器**（共置两物品跑胜率差）与规则校验，不信任 LLM 自评（KLPEG/THE-Tree 的 propose-verify 范式）。
3. **stats 边回填**：自博弈回放的共现/胜率统计给语义边供权重与置信度；KG 嵌入给低频组合提供相似度回退——两者互为正则。

### 6.3 嵌入方案

- 483~518 节点属极小规模：**CompGCN/R-GCN 关系感知编码**（首选，一次前向出节点+关系嵌入，遮蔽合成边做 link-prediction 自监督）或 **RotatE**（复现成本最低，对称/逆关系建模好）；node2vec 表达不了多关系，仅作 sanity check。
- 注入：**嵌入初始化 + 端到端微调**（主路线）→ 观测槽位拼接（冷启动备选）→ FiLM 流派条件化（二期）。
- 协同分公式：P(win|i,j 共存) − P(win|i) − P(win|j) + P(win)；强度分用时间衰减 Bayesian 胜率（先验=职业基准）。

---

## 7. 里程碑与验收（v2 修订）

| 里程碑 | 内容 | 验收标准 |
|---|---|---|
| M0 设计冻结 | 状态布局评审；P0 物品 top80 清单；KG v1（**✔ data 层已建**） | review 通过 |
| M0.5 框架 spike | 现有 `engine/` 包 vmap(step) 200 行吞吐测试（RTX 5080） | 数据决定 JAX/PyTorch 绑定 |
| M1 战斗内核 MVP | 战斗+放置 kernel + 职业抽象；P0 物品 20 个 | 单 env 与 `engine/` 指纹一致（≥20 场固定种子）；B=1024 跑通；≥10万 substep/s/GPU |
| M2 战斗全量 | P0 80 + P1 DSL 150 | 统计对账（胜率差 <2%，KS 检验）；56 场回归指纹全绿 |
| M3 商店域 | 抽池保底/阶梯价/促销/合成/易物 | 与逻辑地图 §5 逐条对账；经济数值指纹 |
| M4 环境封装 | 三 ABC + mask + opponent 注入 | MaskablePPO 在静态池上 > heuristic baseline |
| M5 BC 数据管线 | P0 真值引擎产数据 + Filtered BC | 克隆策略胜率接近 teacher（≥55% 对脚本基线） |
| M6 League RL | P4 全管线 + TrueSkill 联赛 | Elo/TrueSkill 上升；best-response 最低胜率报告 |

**性能预算**（Craftax 证据上调）：单卡 B≥4096 envs；单决策步（含一场战斗）≤10ms；内核 substep 吞吐 ≥10万/s。

---

## 8. 风险清单（v2 修订）

1. **行为向量化心智负担**：top80 是估计，长尾联动可能漏（Goobert 族联动失效教训）。对策：探针验"回调真实执行计数"，不只验"路径通"。
2. **批量 vs 单 env 语义漂移**：lockstep mask 与早退最易引入 subtle bug。对策：固定种子单 env 批量/非批量逐 substep 断言。
3. **大 batch 伤数据效率**（Sebulba 教训）：吞吐不达标时优先调网络/minibatch，不盲目加 env。
4. **截断语义污染**（Time Limits）：truncated 不 bootstrap 会让回放/GAE 失效。
5. **BC→RL 切换崩溃**（价值外推）：用 Cal-QL/PROTO 式约束 + checklist §5.2。
6. **league 存储/算力开销 ≈ 单训练 2-3 倍**：先用"少量快照池 + PFSP"简化版。
7. **易物/促销语义在 UI 层**：移植按逻辑地图 §6.2 下迁，勿自行发明。
8. **版本漂移**：KG + 数据表驱动使更新 = 重导数据 + 重跑对账。
9. **reward hacking 相变点**：能力越强 proxy 回报越高、真实回报越低——双轨监控是硬性要求。
10. **NP-complete 构筑空间**：保留 solver/ILP 混合路径，纯 RL 探索会样本饥饿。

---

## 9. 与现有代码的关系（已获重构授权）

- `engine/`（单 env 真值内核）**冻结为 L0 对照物**，只接受致命 bug 修复。
- 批量内核新建 `engine_batch/`（骨架已建：README + 状态布局入口），不侵入 `engine/`。
- `simulator/` 冻结保留为历史回归基线。
- `tools/compare_engines.py` 增加 `--engine batch` 模式；`regression_baseline.py` 56 场指纹复用为 M2 验收。
- `lineups/` 是 StaticPoolOpponent 首批数据；`assets/kg/items_kg.json` 是策略层嵌入起点。
- 验收纪律：新行为必附 `decompiled_full/` 行号引用；回归指纹变更必须附归因说明（v2 引擎已有先例）。

---

## 10. 调研参考

**GPU 批量仿真/训练工程**：Pgx（sotetsuk/pgx）、Jumanji（InstaDeep）、Craftax、Brax/MJX、Neural MMO、NLE/MiniHack、PureJaxRL、Sebulba/Podracer（arXiv:2104.06272）、Sample Factory、CleanRL、SBX、Time Limits in RL（arXiv:1712.00378）、Isaac Gym。
**离线 RL / BC→RL**：CQL（2006.04779）、IQL（2110.06169）、TD3+BC（2106.06860）、Cal-QL（2303.05479）、PEX（2302.00935）、PROTO（2305.15669）、O2O 三 regime（2510.01460）、DT（2106.01345）及批评（2305.14550、2507.10174）、DQfD（1804.05685）、Kickstarting（1803.04722）、SIL（1806.05635）、VPT（2206.11795）、DeepNash（2206.15378）、遗忘缓解（2402.02868）。
**层次化/模块化**：SMDP（Sutton 1999）、Option-Critic（1609.05140）、FuN（1703.01161）、HIRO（1805.08296）、DIAYN（1802.06070）、MGG 宏观目标（2110.14221）、PLR（2010.03934）。
**游戏 AI 主干**：AlphaStar（Nature 2019）、OpenAI Five（1912.06680）、绝悟 1v1（1912.09729）/全局版（2011.12692）、ByteRL（2303.04096）、LoCAM 竞赛（2305.11814）/搜索（2609.06816）/可利用性（2404.16689）、Underlords NP-complete（2007.05020）、CMA-ME×炉石（1912.02400）。
**KG/嵌入**：DECKARD（2301.12050）、Voyager（2305.16291）、KLPEG（2511.02534）、THE-Tree（2506.21763）、DeepPath（1707.06690）、CompGCN/RotatE、FiLM（AAAI 2018）。
**同类开源**：orbit-wars-torch、manny405/sapai、alexdriedger/sapai-gym、andreped/super-ml-pets、ottoblep/backpack-battles-solver、puchat3k/backpack-battles-ai-lab、PufferLib、RosettaStone、San-sin-sun/STS-RL、sts2-rl-agent。
