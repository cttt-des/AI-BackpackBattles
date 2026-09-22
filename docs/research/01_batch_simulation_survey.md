# 调研报告 01：批量仿真与训练系统工程

> 问题-方法导向。回答一个问题：**怎么让《背包乱斗》（483 物品、60Hz 战斗、18 回合构筑）的仿真在单张 RTX 5080 上支撑数千并发环境与 AI 训练**。
> 调研对象：Pgx、Jumanji、Craftax、Brax/MJX、Neural MMO、NLE/MiniHack、PureJaxRL、Sebulba/Podracer、Sample Factory、CleanRL、SBX、Isaac Gym、GRF 生态、Time Limits in RL（arXiv:1712.00378）。

---

## P1 问题清单

| # | 问题 | 一句话 |
|---|---|---|
| Q1 | 采样吞吐天花板在哪 | CPU 进程并行 vs GPU 原生差 1~3 个数量级 |
| Q2 | 不规则游戏规则怎么向量化 | 固定形状 + 掩码是铁律，动态列表是唯一禁区 |
| Q3 | episode 边界吃掉多少算力 | 乐观重置池把生成成本均摊掉 |
| Q4 | 决策步稀疏、仿真步密集怎么办 | auto-battler 时标问题无直接文献，用 SMDP/动作重复拼 |
| Q5 | 训练工程：batch 多大、loop 怎么写 | 大 batch 伤数据效率；PPO 有 32 个细节 |

---

## Q1 吞吐：CPU 进程并行 vs GPU 原生

**问题本质**：RL 需要 10⁵~10⁷ samples/s，而逐对象 Python 仿真是 10²~10³ 量级。瓶颈不是语言，是**驻留位置**——状态在 CPU 上，每个决策步都要跨设备拷贝。

**方法谱系与量化证据**：

| 方案 | 代表 | 实测吞吐 | 上限约束 |
|---|---|---|---|
| CPU 进程级 vec env | GFootball、SB3 SubprocVecEnv | 5~10K SPS | IPC/序列化，核数 |
| CPU env + 优化采样流水线 | Sample Factory | 10⁵~10⁶ SPS | 仍是 CPU 核数天花板 |
| GPU 原生 batched 引擎 | **Craftax**（RTX 4090，4096 env） | **266K~406K SPS** | 单卡算力 |
| GPU 原生（棋盘类） | Pgx（单 A100） | ≥10⁵ samples/s | 同上 |
| GPU 物理 | Isaac Gym / Brax | 10⁵+ 步/s | 任务适配性 |
| 分布式 TPU pod | Sebulba/Podracer | 43M FPS（2048 核） | 集群 |

**反面教材**：NetHack NLE——富交互游戏留在 CPU 进程内仿真，只有 ~5,600 SPS，训练必然被采样卡死。**结论：规则越富，越必须把引擎搬进设备**；对我们这种"物品行为密集"的游戏更是如此。

**对本项目**：目标 ≥10 万 substep/s/GPU（M1 验收）有先例支撑（Craftax 是含战斗/掉落/合成的 crafting 游戏，与我们同构）。

## Q2 向量化：状态与规则怎么写成设备程序

**问题本质**：jit/vmap 要求**编译期形状恒定**；游戏规则的动态性（场上单位数、掉落、背包物品增减）与之天然冲突。

**方法谱系**（各项目独立收敛到同一组模式）：

| 模式 | 出处 | 内容 |
|---|---|---|
| 固定容量 + 存在掩码 | Craftax（"每步恒算 3 僵尸/2 骷髅/3 箭，未生成用掩码"） | 动态集合的唯一正路；Brax 同理（固定 contact buffer + 激活掩码 + segment_sum） |
| 纯函数 step + 显式 PRNG key | Pgx API v2 | 随机性不藏 state 内（防规划算法信息泄漏），step 显式收 key |
| observation ≠ internal state | Jumanji | State 给仿真器，TimeStep/obs 给策略，严格分离 |
| 合法动作掩码随 obs 返回 | Pgx（legal_action_mask） | 稀疏动作空间（483 物品放置）的标准答案 |
| 符号观测，不渲染像素 | Craftax | 像素观测实测慢 10× |
| 环境版本化注册 + wrapper 组合 | Jumanji | 平衡性实验可复现；AutoReset/Vmap 组合叠加 |
| 引擎与任务解耦 | MiniHack | 同一仿真核，任务用配置注入（物品池/对手强度/目标函数） |

**性能陷阱**（Isaac Gym 论文量化为 2~3 个数量级差距的来源）：CPU↔GPU 每步同步传输；XLA 常量折叠把查表型规则展开成冗长计算图（热点规则表用 host 常量 + gather）。

## Q3 episode 边界：重置成本

**问题本质**：每局结束生成新商店/新对手/新背包，若逐步即时生成，大量算力耗在 episode 边界。

**方法**：**乐观重置（Optimistic Reset）**——Craftax 核心创新：每步不为全部 N 个 worker 生成重置态，而生成 M≪N（1:16，如 1024 worker 生成 64 个）存入池中，重置时从池采样；200 步 episode 下"池不够用"概率 <1e-10。世界生成（我们对应商店生成/对手采样）成本被均摊 16 倍。

**对本项目**：商店 rollItems 与对手选择全部走重置池；池内容物（商店种子、对手 run）可离线预生成。

## Q4 时标：决策步稀疏（每回合一次）× 仿真步密集（战斗几千 substep）

**问题本质**：auto-battler 的策略只在构筑阶段动作，战斗是纯仿真。暴露 substep 会拉爆 rollout buffer 且 GAE 方差爆炸；折叠成一步又面临信用分配理论问题。**直接文献几乎为零**（arXiv 仅检索到玩家行为分析），方案须从通用时标技术拼出。

**方法谱系**：

| 方法 | 出处 | 机制 |
|---|---|---|
| 动作重复/抽稀（decimation） | OpenAI Five（30Hz 仿真、每 4 tick 决策）；AlphaStar（LSTM 吸收错位） | 仿真与推理异步解耦；**战斗 substep 不暴露给网络** |
| **SMDP macro-step** | Sutton/Precup/Singh 1999；Option-Critic（1609.05140） | 战斗段=option：段内回报 R=Σγᵏr、段间折扣 γ^τ、bootstrap 只在段终止处——**唯一理论上自洽**的折叠 |
| 截断 + bootstrap | Time Limits in RL（1712.00378） | 人为时间截断必须 bootstrap 末端 V(s) 且给剩余时间输入，否则回放/GAE 被污染 |
| 段内逐步 + 段级截断并用 | AlphaStar/IMPALA 实践 | 策略层面段即决策单位；价值层面段内 V-trace + 段级截断，不真把整段当一步更新价值 |
| 课程 | substep 预算从短到长 | 先 100 substep 上限后放宽，规避早期长仿真方差爆炸 |

**对本项目**（已写入架构文档 §4.3）：战斗 = 定长 scan + 终止掩码 + 结果折叠为单转移；全局 γ=0.99（18 回合 horizon 不长），段内 GAE λ=0.9~0.95 单独调；战斗 substep 上限属 truncated，末端 bootstrap。

## Q5 训练工程：batch、loop 与 PPO 细节

**问题本质**：仿真快了之后，训练侧成为新瓶颈；且 PPO 在大 batch/长 horizon 下有大量已知坑。

**方法谱系**：

- **Sebulba 的教训（arXiv:2104.06272）**：增大 batch 提吞吐但**伤数据效率**；优先用大网络/调 minibatch 而非堆 batch。MuZero 解耦 acting/learning batch size（learner 端 N 次小更新）。
- **单卡全栈参考实现**：PureJaxRL——环境+网络+更新全在设备上，`jit+vmap+scan` 包一切；非向量化已比 PyTorch CleanRL 快 10×，2048 agent 同卡训练（Craftax baseline 即其 PPO）。
- **PPO 32 个细节**（CleanRL/costa.sh 综述）：优势 minibatch 级归一化、truncation 时 dones 处理、0.5 grad clip、正交初始化……写训练循环时逐条对照。
- **中间路线**（若不 GPU 原生）：PufferLib 式"C/Rust 引擎核 + 进程内向量环境"，单节点吞吐远超 SubprocVecEnv；Sample Factory 的异步推理-采样重叠。

---

## 结论：对本项目的工程模式清单

**必须遵守**（违反即有已验证的坑）：固定容量+掩码；纯函数 step + 显式 key；obs/state 分离；合法掩码环境内计算；乐观重置池 1:16；决策/仿真两级 API + SMDP 折叠；引擎-任务解耦 + 版本化；terminated/truncated 区分；全设备驻留零拷贝；符号观测。

**量化目标有据**：M1 验收 ≥10 万 substep/s/GPU（Craftax 4090 实测 266K+）；B≥4096 envs；单决策步 ≤10ms。

**下一步**：M0.5 spike——用 `engine/` 真值内核包 vmap 式批量实测 RTX 5080，数据决定 JAX/PyTorch 绑定。
