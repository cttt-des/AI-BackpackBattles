# 调研报告 04：同类游戏 AI 与经典系统架构

> 问题-方法导向。回答：**别人做同类游戏 AI 踩过什么坑、哪些架构被实战验证过、经典系统（AlphaStar/Five/绝悟）的哪些部件值得搬**。
> 调研对象：Backpack Battles 生态（cttt-des/puchat3k/ottoblep/olib79）、Super Auto Pets 系（sapai/sapai-gym/super-ml-pets/esterRozen）、TFT/炉石/STS 系（TFT-Copilot/RosettaStone/STS-RL/sts2-rl-agent/Neural-BGSimulator）、学术（Underlords NP-complete 2007.05020、CMA-ME×炉石 1912.02400、LoCAM 2305.11814、ByteRL 2303.04096、LoCAM 搜索 2609.06816）、经典系统（AlphaStar、OpenAI Five 1912.06680、绝悟 1912.09729/2011.12692/2110.14221、NetHack 系）。

---

## 问题清单

| # | 问题 | 一句话 |
|---|---|---|
| Q1 | 同类项目群像在告诉我们什么 | 引擎先行 + 验收文化；空壳与烂尾是常态 |
| Q2 | 引擎-策略-对手怎么解耦 | opponent 可注入是两次独立发明的共识 |
| Q3 | 模拟训练完怎么上真机 | sim 训练 → 内存/桥接部署，视觉方案脆弱 |
| Q4 | 构筑空间组合爆炸怎么办 | NP-complete 证明 + learned proposal + search |
| Q5 | 经典系统的哪些部件直接可用 | 动作分解/league/蒸馏/multi-head value 排序明确 |

---

## Q1 同类项目群像：正向范本与反面教材

**Backpack Battles 生态**：
- **cttt-des/AI-BackpackBattles（本项目）**：逆向+AST 转译 518 物品、v2 引擎无单例可 deepcopy"为 RL 铺路"、56 场固定种子指纹回归 + 三层对账。**教训：工具全绿 ≠ 与游戏一致**（README 诚实承认绳索/黏黏联动仍有偏差）——验收探针覆盖不了实战信号时序。
- puchat3k/backpack-battles-ai-lab（LLM 流派）：分阶段目标设计（tempo→converge→optimize）可借鉴；但 safeguard 在实时推理中不可靠，已暂停——**LLM 做动作头行不通，做先验/课程可以**。
- ottoblep/backpack-battles-solver：放置=组合优化（搜索+时限+多线程）——放置子问题解耦的现成件。
- olib79/Backpack-Battles-elo（空仓库）：Elo 评估是该社区自然想法但无人完成——评估基建是空白也是机会。
- utilForever 五连空壳（backpack/AlphaTFT/battlegrounds-rs/conquer-the-spire/RosettaStone 中四个）：**"simulator with some RL" 工程惯性——没有 gameplay-complete 引擎之前谈 RL 是通病**。

**Super Auto Pets 生态（机制最近：商店+摆放+自动战斗）**：
- manny405/sapai（品类事实标准引擎）：对象模型干净可 deepcopy、战斗确定性、单核 100~230 场/s、明确写着 "built with RL training in mind"。
- alexdriedger/sapai-gym：**opponent_generator 注入是引擎-策略-对手三方解耦的范本**；one-hot+归一化编码、扁平 63 动作 + `valid_actions_only` 掩码、MaskablePPO。
- andreped/super-ml-pets：sim 训练 → 截图视觉部署真机两段式；教训——视觉部署脆（分辨率/UI 版本耦合）。
- esterRozen/SuperAutoPetsAI：多算法并行尝试前先补满引擎测试覆盖。

**TFT/炉石/STS 系**：
- 中文 TFT 项目群（WJZ-P/TFT-Hextech-Helper 724★ 等）：**CV 感知+脚本执行，无引擎无学习**——无法产生训练数据，只适合挂机；真正的训练架构必须有自己的仿真器。
- RosettaStone（682★）：C++ 核心 + Python 双 API 的引擎-策略解耦成熟做法。
- STS-RL / sts2-rl-agent：BC→MaskablePPO 范式 + 详细观测/动作/奖励设计（见报告 02）；sts2 无头模拟器 ~50k 行实现 577 卡、1200 场/秒。
- Neural-BGSimulator：卡死在"无英雄"——**角色机制要尽早抽象进引擎核心**（对我们的 7 职业同理）。

**学术构筑工作**：
- Dota Underlords is NP-complete（2007.05020）：最优阵容=整数规划，归约到 max edge-weighted clique——构筑选择含组合爆炸，**学习+搜索混合比纯 RL 实际**。
- CMA-ME×炉石（1912.02400）：质量多样性发现更多样化高质策略——QD 防流派塌缩。
- LoCAM（2305.11814）+ ByteRL 冠军（2303.04096）：两阶段共享嵌入、自回归 (type,target) 动作、γ=1.0、Bo5 胜 top-10 主播——**构筑类游戏最强的公开学术系统，我们的阶段解耦设计同构**。
- LoCAM 搜索（2609.06816，2026.9）：不完美信息下采样对手世界做完美信息 MC 搜索，胜率 26.8%→51.35%，且更抗 best-response——"理论上 unsound 的搜索"实际非常有效。

## Q2-Q3 解耦与部署

- **opponent 可注入**：sapai-gym 的 opponent_generator 与 orbit-wars-torch 的 Opponent ABC 是同一思想的两次独立发明；自博弈 = learner 每 N update 同步快照到对手池（TiZero/orbit-wars 均如此）。
- **部署通道**：sim-to-game 优先**内存读取/进程内桥接**（本仓库已有 GDScript TCP 桥与内存读取两套方案）；视觉方案不可用于训练数据采集。

## Q4 构筑组合爆炸

三条互补路径（架构文档 §4.4 已定组合）：① learned proposal + 模拟器 search（LoCAM +24.6 点证据）；② solver/ILP 做 teacher 或合法掩码收紧（Underlords NP-complete）；③ 质量多样性保流派空间不塌缩（CMA-ME）。

## Q5 经典系统部件拆解

| 系统 | 可搬部件 | 对本项目的用法 |
|---|---|---|
| **AlphaStar**（Nature 2019） | transformer torso + LSTM core；自回归动作分解 + pointer；replay BC → league RL；league 三类对手 | 观测/动作主干；P0→P4 管线模板 |
| **OpenAI Five**（1912.06680） | 动作头分解；**脚本化子系统（courier）的"裁剪+脚本化"原则**；快照混合匹配 | 放置可脚本化/solver 化的依据 |
| **绝悟 1v1**（1912.09729） | 四关键词：控制依赖解耦、action mask、target attention、dual-clip PPO | mask 与 target attention 的工程背书 |
| **绝悟全局版**（2011.12692） | curriculum self-play（按英雄池扩展）、policy distillation（大池→单英雄）、multi-head value（按子目标分估）、MCTS 融合 | 职业/流派分批开放课程；流派子目标分头估值 |
| **MGG 宏观目标**（2110.14221） | 示范→抽象宏观目标→Meta-Controller 条件化子策略 | 子策略库三步模板 |
| **NetHack 系**（NLE/挑战报告/LuckyMera） | **符号/知识驱动组件仍碾压纯端到端 DRL**——混合式（符号先验+神经策略）是现实最优 | KG 先验注入的总论据 |

**启示排序**：action mask（必做）＞ 阶段解耦+共享嵌入 ＞ 课程式自博弈 ＞ 蒸馏压缩 ＞ MCTS 融合（仅当模拟器足够快，我们有 batched 引擎正合适）。

---

## 结论

1. 本仓库的"重验收 + 无单例引擎"路线在同类中已是正态分布右尾；新架构要守住"工具全绿 ≠ parity"的清醒。
2. 对手注入、MaskablePPO、BC→PPO、阶段共享嵌入四个模式都有双份独立验证，直接采用。
3. 放置走 solver 混合、评估走 TrueSkill+胜率矩阵、流派防塌缩走 QD/league——每个问题都有对应的方法族，无一处需要发明。
