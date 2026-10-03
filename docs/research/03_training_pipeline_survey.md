# 调研报告 03：训练管线——冷启动、BC→RL 切换、自博弈与评估

> 问题-方法导向。回答：**没有人类 replay 的构筑类游戏，怎么从冷启动走到稳定的自博弈 RL，且不崩、不 hack、不循环**。
> 调研对象：CQL/IQL/TD3+BC、Cal-QL/PEX/PROTO/O2O 三 regime、Decision Transformer 及批评、VPT/STEVE-1、Kickstarting/DQfD/SIL/DeepNash、AlphaStar league、OpenAI Five Arena、TrueSkill、奖励 misspecification（2201.03544）、PLR/ACCEL/PAIRED、LoCAM 可利用性研究（2404.16689）。

---

## 问题清单

| # | 问题 | 一句话 |
|---|---|---|
| Q1 | 没有人类数据怎么冷启动 | 自对弈产数据 + 特权 teacher 蒸馏是性价比之王 |
| Q2 | BC→RL 切换为什么崩、怎么不崩 | 价值外推是根因；约束/校准 critic 比蒸馏 actor 稳 |
| Q3 | Decision Transformer 能不能当主干 | 不能；Filtered BC 在稀疏奖励下就打平它 |
| Q4 | 自博弈怎么防策略循环 | league 三类对手 + 快照池采样 |
| Q5 | 强度怎么评才不作假 | TrueSkill + 胜率矩阵 + best-response 最低胜率 |
| Q6 | 奖励 hacking 怎么办 | 存在相变点；proxy 与真实胜率双轨监控 |
| Q7 | 课程怎么排 | PLR 按 TD 误差优先采样关卡 |

---

## Q1 冷启动：没有人类 replay

**问题本质**：构筑类游戏没有现成 replay 数据集（AlphaStar 的 97 万盘人类数据是奢侈 exception）；随机策略的探索在组合空间里无效。

**方法谱系**：

| 方法 | 出处 | 机制 | 成本/效果 |
|---|---|---|---|
| 规则 bot 自产数据 | STS-RL（启发式 ~97% 胜率产 demonstration → BC → PPO）、sapai 系 | 引擎 + 脚本策略批量自对局 | **最便宜、即时可得**；数据分布受限于 bot 水平 |
| 逆动力学伪标签 | VPT（2206.11795）、STEVE-1（2212.13326） | 逆动力学模型给无标注轨迹自动打动作标签；hindsight relabeling | 自举标签比专家标签便宜几个量级 |
| 特权 teacher 蒸馏 | Kickstarting（1803.04722）范式 | teacher 看特权特征（隐藏信息、RNG、未来刷新），student 只看真实观测；KL 蒸馏 + 系数退火 | 构筑游戏天然有特权信息，**性价比最高的专家构造法** |
| 自对弈自举 | SIL（1806.05635，对自己历史高回报轨迹 BC）、Expert Iteration（1705.09327）、IER/TSIL（近期变体） | 成功片段自我蒸馏持续供给 | 与 RL 互补，缓解 demonstration 枯竭 |
| 零人类数据极限 | DeepNash（2206.15378） | 纯自对弈 + R-NaD 打到 Stratego 顶级 | 证明规则可完美仿真时自对弈本身可产生全部监督信号 |

**对本项目**：P0 = 真值引擎 + 启发式批量自对局产日志 → 特权 teacher 打标 → D0；SIL 式辅助贯穿后续阶段（架构文档 §5.1 已定）。

## Q2 BC→RL 切换：崩的机制与对策

**问题本质**：离线预训练策略上线后，critic 在 OOD 动作上 bootstrap → Q 膨胀 → 策略追逐虚高值 → 崩溃。这是 2022 后离线 RL 文献的核心战场。

**方法谱系（按干预位置分三族）**：

| 族 | 方法 | arXiv | 机制 |
|---|---|---|---|
| 悲观 | CQL | 2006.04779 | Bellman 误差上加正则，压低数据集不支持的 Q（保守下界）；原生支持离散动作 |
| 隐式 in-sample | **IQL** | 2110.06169 | expectile 回归隐式做样本内 max → advantage-weighted BC；**从不查询 OOD 动作**，对合法掩码天然友好；社区公认最适合 offline→online 初始化 |
| 显式约束 | TD3+BC / CRR | 2106.06860 / 2006.15134 | BC 项写进 actor 目标 / 按 advantage 过滤 BC；本质是"带约束的 BC"，多峰数据会被拉向平均 |
| **校准（切换专用）** | **Cal-QL** | 2303.05479 | 离线阶段让 Q **低于真值但高于 BC 策略**——上线后 critic 不因在线早期噪声崩；11 benchmark 赢 9 个，**O2O 默认件** |
| 结构隔离 | PEX | 2302.00935 | 不动原策略，新长在线策略头组合行动，从结构上防破坏 |
| 退火 | PROTO | 2305.15669 | trust-region 式逐步放松 BC 正则，任意离线 RL 平滑变 O2O |
| 传统蒸馏 | DQfD / Kickstarting | 1804.05685 / 1803.04722 | margin loss + 预填充 replay / KL 蒸馏退火；仍有效但 2022 后共识是"约束 critic"比"蒸馏 actor"稳 |

**切换条件的实证依据**：O2O 三 regime（2510.01460）——切区取决于"离线数据 vs 预训练策略谁更强"；保护更强一方同时保留可塑性；63 case 中 45 个符合。**本项目切换触发**：在线平均 TD 误差 < 离线 2 倍 ∧ 对 π_BC 胜率 >70% 连续 3 评估窗。

**工程注意**：切换瞬间 replay 混合（在线:离线 ≈1:1 起步渐退）、critic early 阶段价值钳制、监控在线 TD 误差突增作为崩前信号。

## Q3 Decision Transformer 路线判定

**问题本质**：把 RL 变成 return-to-go 条件化的序列建模，规避 Bellman 备份，看似适合长决策序列（18 回合构筑）。

**调研结论：不当主干**。证据链：QDT（2209.03993，用 DP 重标 return 补 stitching 缺陷）说明纯条件化丢值信息 → RvS（2112.10751）证明简单 MLP+监督匹配 DT → Meta 的 "When should we prefer DT"（2305.14550）：DT 比 CQL 更吃数据量，高随机性下 CQL 更好 → "Should We Ever Prefer DT"（2507.10174）：Filtered BC 在稀疏奖励下打平甚至超过 DT。对本项目，战斗随机性大（命中/暴击/疲劳），DT 的固定 return 条件表达不了方差；18 回合 × 物品集容易顶爆上下文。**定位：BC 初始化的对比基线，可选。**

## Q4 自博弈防循环

**问题本质**：单一当前对手自博弈会出现策略循环（石头剪刀布震荡）与非传递性陷阱。

**方法谱系**：

- **AlphaStar league**：main agents（对全 league 采样）+ main exploiters（专打 main）+ league exploiters（打全历史）；agent 从旧 agent 分叉并继承个性化目标；最终从 Nash 分布采样。损失 = V-trace（IMPALA, 1802.01561）+ UPGO（只推"比预期好"的动作，天然悲观抗自举噪声）+ 对对手 KL（exploiter 用）。
- **OpenAI Five**：历史策略快照混合匹配（PBT 式），防循环。
- **简化版（本项目首选起步）**：3-5 个快照的 PFSP 采样池 + 1-2 个 exploit 角色；存储/算力开销约为单训练 2-3 倍（league 全量版的代价，先用简化版）。

## Q5 强度评估：怎么不作假

**问题本质**：只看平均胜率会漏掉可利用性——LoCAM 冠军 ByteRL 被证明"高度可被利用"（2404.16689）。

**方法谱系**：Elo < **TrueSkill**（OpenAI Five Arena 实践：mu/sigma、组队修正、小样本收敛快——单局分钟级、算力有限时尤其合适）；LoCAM 搜索论文（2609.06816）的 1 万局预注册评估 + 95% CI 是报告模板。**本项目报告纪律**：对 N 个历史检查点 + 脚本 bot 的胜率矩阵 + 95% CI + best-response 攻击下的最低胜率。

## Q6 奖励 hacking

**问题本质**：代理奖励与真实目标错位时，能力越强的 agent proxy 回报越高但真实回报越低——**存在相变点**（Pan/Steinhardt 2201.03544）；经典案例：CoastRunners 撞墙刷分、Sonic 原地刷环。

**方法**：对策不在"设计得更精巧的奖励"，而在监控——**proxy 奖励与真实胜率双轨**，训练期间定期与冻结基线/脚本对手对局测真实强度；shaping 项与终局奖励分账记录，hacking 发生时可归因（架构文档 §5.2 checklist）。

## Q7 课程

**方法**：PLR（2010.03934，按 TD 误差优先采样关卡，涌现由易到难课程）、ACCEL（2007.03637，对抗式关卡生成）、PAIRED（三方 regret，零样本迁移最强但工程重）。**本项目映射**：课程轴 = 对手强度 / 起始池复杂度 / substep 预算（报告 01 Q4）；绝悟全局版的 curriculum self-play（按英雄池逐步扩展）对应按职业分批放开。

---

## 结论：P0~P5 管线（已写入架构文档 §5）

P0 数据引擎（特权 teacher）→ P1 Filtered BC（≥55% 对脚本基线）→ P2 IQL/CQL-discrete（≥60% 对 BC）→ P3 Cal-QL/PROTO O2O（量化切换条件）→ P4 league（V-trace+UPGO+SIL）→ P5 PLR 课程硬化。防崩 checklist 七条为硬性执行项。
