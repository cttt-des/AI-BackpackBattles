# Backpack Battles AI（背包乱斗 AI）

为游戏《背包乱斗》(Backpack Battles) 打造的外置工具集：**战斗日志导出器**（游戏内存只读 → 游戏同格式战报）、**战斗模拟器**（基于逆向真值的对战模拟）与**外挂 AI**（自动游玩）。不修改任何游戏文件。

## ⚠️ 已知问题（使用前必读）

**确定性对齐现状（2026-11-09）**：模拟内核（gd_core）与逆向录制语料、Python 转写内核的**三方确定性对齐已达 1690/1690 场逐事件、逐 rng 抽一致**（总语料=914 场基线 + 776 场「全异阵容/稀薄物品」扩样；rng 序列逐位收敛；快照锚定 `output/_recovery/r55/r55_manifest.txt`，复现与留档见 [docs/np24_fix.md](docs/np24_fix.md) 与 [docs/expand_fix_progress.md](docs/expand_fix_progress.md)）。以下提醒针对「模拟 vs 游戏实机」的剩余边界：

1. **语料=录制回放语义**。1690 场语料由逆向 harness 录制（np46 起逐案隔离、全新状态确定性执行），三方一致保证的是模拟器与该录制管线逐位一致；与游戏实机在未覆盖的 UI/信号时序面上仍可能存在差异。

2. **模拟器对战结果请勿当作游戏的精确胜率参考**。实录对照工作流仍是发现实机差异的最终手段。

发现问题欢迎提 issue（附阵容 JSON 与种子可精确复现）。

## 下载（Releases）

打包好的独立 EXE 在 [GitHub Releases](https://github.com/cttt-des/AI-BackpackBattles/releases) 发布，无需 Python 环境：

| 版本 | 文件 | 说明 |
|------|------|------|
| **v0.5.4** | [`BackpackSimulator.exe`](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.5.4/BackpackSimulator.exe) · [`whl`](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.5.4/backpack_battles_sim-0.5.4-cp314-cp314-win_amd64.whl) | 战斗模拟器——**修复 62 场编译层回归**（`cpdef`+plain 子类零参 `super()` 三元组合致崩，生成器级 `_L2_BLOCKLIST` 永久止损；同时修正「1690/1690」假绿记录，验收改为回读账本 match 分布）；**装配优化**：`load_for` 索引化 7.5→0.18 ms（41x）+ `_place_of` 几何缓存（全量 2076 组合等价）+ 局部绑定；热循环注解式类型化（纯 py 臂零开销，`character()` 虚派发保留）；构建护栏（包根辅助模块拒绝编译成 pyd）；新增标准吞吐口径 `trainer/bench.py`（固定 200 场批量，tput/负载/cores_eff 三列同报）；**确定性 1690/1690 全量三方逐行一致**（发布前全量重跑，回读 1690 条分布实证） |
| **v0.5.3** | [`BackpackSimulator.exe`](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.5.3/BackpackSimulator.exe) · [`whl`](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.5.3/backpack_battles_sim-0.5.3-cp314-cp314-win_amd64.whl) | 战斗模拟器——**items 行为树 510 模块 cdef 槽位化**（实例免 `__dict__`，顺带修复 7 处潜伏 NameError）；事件路径剥离/内联/数组化（调用数 −7.2 万/3 场）；新增训练 API `run_mc_mem`（内存态阵容批量+统计回传）；修复 wheel 安装态 assets 路径（v0.5.2 同病）；exe 剔除 15 个未用标准库；**确定性 1690/1690 全量三方逐行一致**（发布前重跑）。单点热路径微基准 1.00x（L1-Q 判定，详见 docs/性能优化下一步规划.md） |
| **v0.5.2** | [`BackpackSimulator.exe`](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.5.2/BackpackSimulator.exe) | 战斗模拟器（阵容对战 / 蒙特卡洛胜率 / 物品联动 / 游戏格式战报）——**内核 Cython 化**：664 模块编译为 C 扩展（官方 MSVC 工具链），单场耗时约降 45%（378→207ms 健康段口径），**1690/1690 全量三方逐行一致**复验通过；含蒙特卡洛多进程并行、分层导入加速启动 |
| **v0.5.1** | [`BackpackSimulator.exe`](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.5.1/BackpackSimulator.exe) | 战斗模拟器（阵容对战 / 蒙特卡洛胜率 / 物品联动 / 游戏格式战报）——**1690/1690 重跑复验**三方逐行一致；修复体力上限取数链不同源导致的 13 场分歧；新增 60 场确定性精选集 |
| **v0.5.0** | [`BackpackSimulator.exe`](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.5.0/BackpackSimulator.exe) | 战斗模拟器（阵容对战 / 蒙特卡洛胜率 / 物品联动 / 游戏格式战报）——1690 场语料三方对齐全绿 |
| **v0.4.1** | [`BackpackSimulator.exe`](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.4.1/BackpackSimulator.exe) | 战斗模拟器（阵容对战 / 蒙特卡洛胜率 / 物品联动 / 游戏格式战报） |
| **v0.3.1** | [`BackpackCombatLog_v0.3.1.exe`](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.3.1/BackpackCombatLog_v0.3.1.exe) | 战斗日志导出器（游戏内真实战斗 → 游戏同格式战报 + 原始事件 JSON） |
| **v0.4.0** | [`BackpackAI.exe`](https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.4.0/BackpackAI.exe) | 外挂 AI 主程序（自动游玩 GUI） |

开发版随每次改动重新打包到 `dist/`（不带版本号）。

### 训练 / 二次开发（Python API）

要用模拟器**训练 AI 或做批量仿真**，请装 wheel 而不是用 exe——exe 只有 GUI，没有可 import 的接口：

```bash
pip install "https://github.com/cttt-des/AI-BackpackBattles/releases/download/v0.5.4/backpack_battles_sim-0.5.4-cp314-cp314-win_amd64.whl"

python - <<'PY'
from simulator.gd_core_engine import GDCoreEngine
from simulator.data import load_items, load_characters
from simulator.lineup import load_lineup

p = load_lineup("truth_20261001_220653_R19_player.json")
o = load_lineup("truth_20261001_220653_R19_opponent.json")
eng = GDCoreEngine(p, o, load_items(), load_characters(),
                   seed=20260923, max_time=90.0)
eng.run()
print("winner:", "player" if eng.player_wins() else "opponent",
      "| ticks:", eng._ticks, "| events:", len(eng.log.events))
PY
```

| 要点 | 说明 |
|---|---|
| **平台要求** | `cp314-win_amd64`：Python **3.14 x64 + Windows**。标签写死是为了让错误环境直接拒绝安装，而不是悄悄退回纯 Python 腿（慢 40% 且无提示） |
| **批量蒙特卡洛** | `simulator.simulate.run_mc_pool(player_path, opponent_path, seed, runs, workers)`，进程池并行、逐 seed 确定 |
| **数据目录** | 默认装在 `<prefix>/assets`；训练想换数据目录就设环境变量 `BACKPACK_ASSETS` |
| **改内核后重编** | `python -X utf8 tools/build_cython.py --list <清单>` 再 `python -X utf8 tools/build_wheel.py`；.pyd 是构建产物、不进 git（84MB 且与 ABI 绑定） |
| **纯 Python 腿** | 删掉任一 `.pyd` 即回落纯 Python（仍可跑，用于对照/调试）；或用 `GD_PURE_PY=1` 环境变量在进程内屏蔽扩展加载 |


## 成果总结

### ① 逆向基础（GDEC 解密 + 全源码可读）

- **2026-09-18 全量重逆向**：以官方原版 `BackpackBattles.pck`（clean v1.1.7）为真值重新解包——**9377/9377 个文件全部提取，MD5 逐条目校验零缺失**；另对**运行版（1.1.8）pck** 完成同规格提取与脚本反编译，支撑双版本真值对照
- **820 个 GDEC 加密脚本全部解密**（AES-256-ECB，脚本密钥经游戏进程 hook 动态确认，GDSC 魔数 + 全文件 MD5 双重验证）+ `ItemData_e.csv` 解密（518 物品行 MD5 吻合）
- **820/820 脚本反编译 + 3817 个资源全部转换成功**（`decompiled_full/`：.gd/.tscn/材质/翻译/着色器全文本可读）
- 内存布局活体标定：`OS::singleton` RVA 定位 → Godot 对象图遍历；密钥动态确认工具链：`tools/inject_gdec_hook.py`（x64 绝对跳转 hook，在启动解密风暴的约 29ms 窗口内捕获密钥）

### ② 战斗日志导出器（BackpackCombatLog）

游戏本身不把战斗日志落盘。本工具在游戏运行期间对 `CombatLog.events` 数组做**只读结构性读取**（Game 单例 → 按脚本路径锚定 CombatLog 节点 → 解析魔改 Godot 构建的 Variant/Array/Dictionary/对象槽内存布局），战斗结束后自动导出：

- `*.zh.txt / *.en.txt` —— 按 `CombatEvent.asText()` 复刻的游戏格式战报（中/英）
- `*.json` —— 原始事件流（id/时间戳/类型/origin/params）+ **双方阵容 JSON**（v4）

这些导出物同时是模拟器的**真值测试集**（见已知问题对照）。

### ③ 战斗模拟器（gd_core 内核）

- **战斗内核：`gd_core`** —— 原版战斗逻辑的 1:1 移植：运行版 .gde 逆向 → `gd_core/` 无头 GDScript 内核 → `tools/gd_to_py.py` 机械转写为 `gd_core_py/`。已用 56 局 Godot 基准逐字符校验（`tools/check_gd_core_engine.py`）
- 物品数据来自 `assets/gd_core_runtime.json`（531 件，含四色影响格/参数/转写形状）
- 输出：事件流 JSON、战斗结果 JSON、**游戏格式战报文本**（中/英，共享渲染层 `simulator/log_text.py`）
- 桌面 GUI（`battle_simulator.py`）：阵容选择、镜像对战、蒙特卡洛胜率、开战前占格重叠预检
- 历史 `engine/`（自研转译内核，`rng.flip` 缺失不可用）与依赖它的旧内核对照工具已于 **2026-11-10 整包删除**（判据渲染器迁到 `simulator/log_text.py`），需要时查 git 历史

### ④ 外挂 AI（自动游玩）

- 内存读取金币/HP/回合/**职业**；结构性物品读取精确捕获**位置、旋转、镶嵌宝石、袋内物品**
- **商店物品与价格读取**：读 ShopOffer 槽位脚本成员（item/原价/折后价/打折/预订/已购），价格经 Game.randnum 编码——解码带双重运行时自校验（半字签名一致 + gold_internal↔明文 gold 交叉验证），校验不过宁可缺价不出错值
- 启发式策略自动决策（预留 LLM 接口）；tkinter 深色主题桌面 GUI；**游戏进程自动连接**（启动后自动发现并连接，无需手动点初始化）
- 一键导出 **v4 阵容 JSON**；**从游戏历史记录导出阵容**（解析 `history.db` 的 buildInfo 位流）与**导出历史界面当前查看的回合**（活体读取 BuildHistory 选中状态）
- 桥接注入（可选）：PCK 补丁注入 GDScript TCP 桥接，进程内读取运行时数据

### ⑤ 真值对照与验收工具链

| 工具 | 作用 |
|------|------|
| `tools/compare_truth.py` | 真值实录 ↔ 模拟器对照（同阵容多种子：胜负/时长/逐类型事件量分布） |
| `tools/per_item_diff.py` | 逐物品激活次数/伤害总量归因（单组真值 vs 模拟中位数） |
| `tools/verify_linkage.py` | 联动语义固定用例 |
| `tools/audit_item_effects.py` | 源码→转译→运行时三层对账 |
| `tools/regression_baseline.py` | 固定种子 56 场战斗指纹比对（防回归） |
| `tools/check_gd_core_engine.py` | gd_core 内核 vs 56 局 Godot 基准逐字符校验 |
| `tools/repack_lineups.py` | 占格形状变更后内置阵容自动重摆 |
| `tools/extract_sprites.py` | 从全量反编译树重建 `assets/sprites/` 与 `assets/item_db.json`（多层贴图合成 + 物品原点，见 ⑧） |

> 这些工具证明的是"改动没有引入回归"。与游戏行为的最终对齐以 `output/combat_logs/` 实录对照为准——多个严重问题正是在固定用例全绿的状态下由实录发现的。

### ⑥ 三方确定性对齐（语料 ↔ gd_core ↔ gd_core_py）——**已收口 1690/1690**

- **对齐出口**：`output/oracle/alignment.json`（基线 914 场）与 `output/oracle/expand/alignment_expand.json`（扩样 776 场）—— 唯一账本（仅由 `tools/verify_oracle.py` 产出，禁手写），双判据（canonical 事件流 + 渲染行）逐场裁决，当前 **914/914 + 776/776 = 1690/1690 三方逐行一致**；54 场超长战斗的独立账为 `output/oracle/long_alignment.json`。
- **三方架构**：`oracle/`（Godot 受控神谕，手动 tick 驱动 v1.1.9 真源）↔ `gd_core/`（GDScript 无头内核）↔ `gd_core_py/`（Python 机械转写，`tools/gd_to_py.py` 生成 661 模块）——任一修复需四树同步（gd_core/、gd_core_test 双镜像、gd_core_items/）后重跑 gd_to_py。
- **REG gate**：`tools/_np21_gate.py` 基线 7 场 + 域代表场双腿（gd/py）防回归；全量刷账 `python -X utf8 tools/verify_oracle.py --skip-fixtures --force`。
- **收口留档**：[docs/np24_fix.md](docs/np24_fix.md)（目标/架构/修复史大针/方法论遗产/复现）；逐轮全史在 [docs/np24_issue_ledger.md](docs/np24_issue_ledger.md)（正文经 git 历史回溯）。
- **扩样对齐（2026-11-09 收口，独立账本不混算）**：「全异阵容/稀薄物品」扩样语料已增补至 **776 场**（`output/oracle/expand/fights/`，含针对稀薄物品的定向补场，物品/职业/事件类型覆盖可达全集），全部接入三方对齐并 **776/776 全绿**（连同基线 914 场 = **1690/1690 全绿**）。收口过程（旧语料 lib 污染翻案、火种精确计数门控、SPF 计时器相位补偿逐场开关等）见 [docs/expand_fix_progress.md](docs/expand_fix_progress.md)。扩样账本 `output/oracle/expand/alignment_expand.json`（**独立，绝不混入 `alignment.json`**）。管线新增（默认值全部不变、基线零回归实测）：`verify_oracle.py` 四参数（`--fights-root/--align-root/--cases-json/--alignment-out`）与逐场门控表 `gd_core_test/oracle_align_case_overrides.json`（flk_delay 火种队列 / flk_off 逐实例抑制 / no_phase_comp 计时器相位补偿开关）、`gen_fixture_from_lineup.py --history-db`（扩样合并库取 stamina）、`tools/expand_gen_fixtures.py`（分批夹具驱动+stamina 逐场自检）、`OracleAlignBattle.gd` 的 `ORACLE_ALIGN_CASES_JSON/ORACLE_ALIGN_FIGHTS_ROOT` 覆盖。扩样与判据升级（J2–J6）完整规划见 [docs/扩大用例对齐规划.md](docs/扩大用例对齐规划.md)。

### ⑦ 对局语料记录器（真人操作 → 训练数据）

主程序内置记录器：**纯外置只读**地记录整局操作（买/卖/刷新/锁定/合成）与操作时的完整状态
（回合、金币、生命、职业、摆盘、储物箱、商店 5 槽及价格/打折/锁定），产出两路语料：

| 输出 | 内容 | 给谁用 |
|------|------|--------|
| `raw/` | 原样事件流（含每一次摆放、每一次锁定切换），按回合分片 + lzma 归档 | 审计、回溯、可重算 |
| `corpus/decisions.jsonl` | 折叠后的**局内决策**样本（状态 + 净动作 + 下一状态 + 标签） | 局内决策 AI（行为克隆 → 价值加权） |
| `corpus/lineups.jsonl` | 每回合**开战瞬时摆盘**（v4 阵容 + 可用商店资源 + 结果标签） | 摆盘 AI（RL 的分布基准 / OOD 告警 / 评估集） |
| `corpus/traces.jsonl` | 可选：摆盘搜索轨迹（`--traces` 才导出） | 仅 RL 热启动 |

**关键设计**：反复摆盘、反复切换锁定不会污染训练集——折叠层按"决策点"（买/卖/刷新/合成/开战）
切段，段内净变化为零就整段丢弃；**摆盘过程不产生决策样本**（那是 RL 自己探索的领域），
只在 `next_state` 里体现结果。详见 [docs/recorder_design.md](docs/recorder_design.md)。

    # GUI：初始化后点「开始记录」即可（人类手动游玩也照常用），结束后点「停止记录」
    python launcher.py

    # 折叠 + 校验 + 统计（也可对整目录批量）
    python -X utf8 tools/corpus_fold.py  output/records/<run_id>
    python -X utf8 tools/corpus_check.py output/records/<run_id>
    python -X utf8 tools/corpus_stats.py output/records/<run_id>
    python -X utf8 tools/corpus_fold.py  --all output/records --traces

配置在 `config.yaml` 的 `recorder:` 段（采样间隔、压缩方式、是否也记录 AI 自身动作等）。

### ⑧ UI 贴图资产（物品渲染真值）

主程序背包摆盘的贴图来自 `assets/sprites/` + `assets/item_db.json`，由
`tools/extract_sprites.py` 从 `oracle/`（1.1.9 全量 GDRE 反编译树，含 png/tscn/CSV）
重新生成。三条曾经导致"贴图缺失 / 多层只画一层"的坑，已在生成器里处理：

1. **继承节点没有 type**：物品场景是 `Items/Xxx.tscn` 实例化 `res://Items/Item.tscn`
   再覆盖同名节点，子场景里 `[node name="Icon" parent="."]` 不带 `type`——
   只按 `type=="Sprite"` 收层会把绝大多数物品的主贴图整件漏掉。
2. **根节点属性含方括号**：根节点声明形如
   `[node name="Item" type="RigidBody2D" groups=["Item"]]`，用"非方括号字符类"
   的单条正则解析会在第一个 `]` 处提前截断，导致基类根节点认不出、整条继承链失效
   （生成器改为逐行状态机解析）。
3. **同名场景根 + shader 辅助层**：多个护符场景根名都是 `Amulet Unidentified`
   （靠 `.gd` 脚本路径区分）；`Assets/Pixel.png` 这类屏幕扭曲占位纹理必须排除，
   否则合成图会整张变白。

生成物：合成图**保留原始画布几何**（不裁透明边），并在 `item_db.json` 记录
`origin_px`（物品节点原点在图中的像素位置）与 `img_w/img_h`。GUI 据此把贴图
精确钉到物品原点、按 `CELL/80` 缩放、绕原点旋转——不再用"占格包围盒 contain"近似，
多格物品不再被压扁。

    python -X utf8 tools/extract_sprites.py     # 源 = oracle/（1.1.9 全量反编译树）

**两份反编译树的分工**（都只有一份，不重复）：

| 目录 | 版本 | 用途 |
|------|------|------|
| `decompiled_full/` | v1.1.7 | `gd_core` / `gd_core_py` 逐行转译的**文本基线**（1028 tscn + 820 gd，约 15MB） |
| `oracle/` | v1.1.9 | 战斗神谕真值 + UI 贴图提取源（15408 文件，含 2547 png） |

二者**不是副本**：`Core/Game.gd` 的 `VERSION` 分别为 1.1.7 / 1.1.9，忽略行尾仍有
32 个文件内容不同，覆盖会打断内核与真值的逐行对照。

> `decompiled_full/`（1.1.7）**不是过时垃圾**，理由有三（2026-10-29 实测）：
>
> 1. **它是构建链唯一输入**：`tools/build_item_scripts.py` → `gd_core_items/`、
>    `simulator/build_data.py` → `battle_items.json`、`tools/gen_core_item_book.py` →
>    `gd_core_py/CoreItemBook.py`，全仓 **28 处硬编码路径**指向它。运行时（core/gui/engine）
>    不读它——删了程序照跑，但**内核与数据再无法从源码重建/复核**。
> 2. **`oracle/` 不能当构建源**：它是**插桩过**的神谕工程（11 个 .gd 带
>    `ORACLE HARNESS`/`oracleRngLog`/`oracleTimeLeft`/`B2_SHUF_DBG`/`ORACLE_PROC_DEBUG`），
>    拿它再生会把调试桩灌进内核树。`decompiled_full` 全树 **0 处**插桩，是唯一的纯净反编译源。
> 3. **两者产物只差 5 个文件**（Eggscalibur/AmuletofDarkness/Eat-o-matic/EchoingBattlecry/Item
>    + 1 个新增 TimePendant），差的正是 oracle 的调试桩——再次说明差异来自插桩而非"版本更新更好"。
>
> 另注：`gd_core_items/` 里的 5 处手工回植（`★ np24/np25` 注释：Eggscalibur/EngineerBox/
> MagicRing/MrStruggles/Item）**任何源重建都会被冲掉**（builder 不生成它们），与版本无关，
> 重建后必须回植。

**模拟器当前对齐哪一版？** 分面混合：**行为逻辑 = 1.1.7 转译**，**数值/占格/贴图/真值对照 = 1.1.9**。
逐面证据（含 3104/3104 数值对拍、519/519 索引 id 对拍）见
[docs/version_alignment.md](docs/version_alignment.md)。

## 项目结构

```
gd_core/                    # ★ 无头战斗内核（原版 GDScript 1:1 移植，531 件物品）
gd_core_py/                 # ★ gd_core 的 Python 机械转写（模拟器实际加载的内核）
gd_core_items/              # 物品行为脚本（gd_core 侧）
gd_core_test/               # Godot 基准对局结果（56 局逐字符校验用）+ 对齐重放器
core/                       # 外挂 AI 核心（bot/memory_reader/item_reader/godot_reader/
                            #   combatlog_reader/build_history/item_db/…）
├── recorder.py             # ★ 对局语料记录器（采样/去抖/差分/局边界，纯只读）
├── store.py                #   记录写盘：回合分片 + lzma 归档 + 快照
└── lineup.py               #   ItemInfo → v4 阵容的唯一序列化实现
simulator/log_text.py       # 游戏格式战报渲染器（三方对齐主判据口径）
（engine/ 已于 2026-11-10 删除：渲染层迁入 simulator，旧内核随工具链下线）
simulator/                  # CLI/GUI 入口（simulate.py 单内核 gd_core）+ 数据管线
├── gd_core_engine.py       # gd_core 内核适配层
├── extract_linkage.py      # ★ 联动专项提取（四色影响格 + canAffect + 回调，含继承链）
└── build_data.py           # 从 wiki + 解包脚本生成 battle_items.json
combatlog_exporter.py       # 战斗日志导出器 GUI
build_exe.py                # 外挂 AI 打包        build_simulator_exe.py  # 模拟器打包
build_combatlog_exporter_exe.py  # 战斗日志导出器打包
launcher.py                 # 外挂 AI 入口        battle_simulator.py  # 模拟器 GUI 入口
bridge/                     # 桥接注入（可选）
decompiled_full/            # ★ v1.1.7 反编译文本基线（gd_core 转译真值，1028 tscn + 820 gd）
oracle/                     # ★ v1.1.9 全量反编译树（神谕真值 + 贴图提取源，含 2547 png）
assets/                     # 物品贴图、battle_items.json、gd_core_runtime.json、
                            #   item_index_map*.json（历史解码映射）、翻译表
dist/lineups/               # 内置与游戏历史阵容 JSON
tools/                      # 逆向工具 + 真值对照 + 验收链（见上表）
                            #   + corpus_fold/check/stats（对局语料折叠与校验）
docs/                       # 逆向记录、内核真值、对齐规划与台账、模拟器架构（见下）
```

### 文档索引（docs/）

| 文档 | 内容 |
|------|------|
| [np24_fix.md](docs/np24_fix.md) | **对齐收口留档**：目标/架构/修复史大针/方法论/复现 |
| [np24_issue_ledger.md](docs/np24_issue_ledger.md) | 逐轮问题台账（现行期总账 + 铁律 + playbook） |
| [扩大用例对齐规划.md](docs/扩大用例对齐规划.md) | **下一步**：覆盖优先扩样、J2–J6 判据升级、三档并发预设 |
| [gd_core_truth.md](docs/gd_core_truth.md) | gd_core 内核逆向真值规范 |
| [engine_truth.md](docs/engine_truth.md) | 引擎战斗真值规范（含反编译源码行号对照） |
| [rng_truth.md](docs/rng_truth.md) | PCG32 全局链与逐抽真值 |
| [version_alignment.md](docs/version_alignment.md) | 模拟器对齐 1.1.7 还是 1.1.9 的逐面证据 |
| [simulator_architecture.md](docs/simulator_architecture.md) | 阵容/物品库/战斗日志三套 JSON 架构规范 |
| [recorder_design.md](docs/recorder_design.md) | 对局记录器设计与语料格式 |
| [corpus_official_format.md](docs/corpus_official_format.md) | bpb 语料官方格式解码 |
| [long_case_fix_guide.md](docs/long_case_fix_guide.md) | 长场修复工具交接（54 场 playbook） |
| [parallel_workflow.md](docs/parallel_workflow.md) | 三腿并行验证工作流与无窗口启动 |
| [oracle_workflow.md](docs/oracle_workflow.md) / [consistency_workflow.md](docs/consistency_workflow.md) / [alignment_fix_workflow.md](docs/alignment_fix_workflow.md) / [deterministic_replay_workflow.md](docs/deterministic_replay_workflow.md) / [capture_protocol.md](docs/capture_protocol.md) | 历史方法论（仍被工具注释引用，保留） |
| [reverse_engineering_2026-09.md](docs/reverse_engineering_2026-09.md) | 2026-09 全量重逆向报告 |

## 快速开始

### 战斗日志导出器（游戏内真实战斗）

```bash
python combatlog_exporter.py   # 需游戏已开启；输出 output/combat_logs/
#   每场战斗一个子目录：双方阵容 JSON（v4）+ 游戏格式战报（zh/en）+ 原始事件流
```

### 战斗模拟器（不依赖游戏运行）

```bash
# 单场战斗（固定种子可复现）/ 蒙特卡洛 100 场
python -m simulator.simulate dist/lineups/毒矛冰\ 第18回合.json dist/lineups/猎鹰龙跳.json --seed 42
python -m simulator.simulate lineup_A.json lineup_B.json --runs 100

# 桌面 GUI（阵容选择、镜像对战、蒙特卡洛）
python battle_simulator.py

# 输出 *_log.json（事件流）、*_result.json（胜负/统计/HP 曲线）、*_log.txt（游戏格式战报）
```

### 批量仿真/训练（Python API，§9.6 训练专项）

```python
from simulator.simulate import run_mc_mem

# 内存态批量：lineup dict 直传（免每次读盘），只回传统计不落盘
agg = run_mc_mem(player_dict, opponent_dict, seed=20260923, runs=200,
                 workers=4, max_time=90.0)
agg["win_rate"]          # 玩家胜率
agg["ticks_p50"]         # 中位 tick 数（局长分布，reward shaping 用）

# 要逐场统计（伤害/治疗/暴击/未命中/体力耗尽/激活）时：
agg = run_mc_mem(player_dict, opponent_dict, seed=S, runs=100,
                 workers=4, want_stats=True)
agg["damage_dealt"]      # {"player": …, "opponent": …}（场均）
agg["records"][0]        # 逐场：{seed, win, ticks, combat_time, reason, …}
```

**训练推荐配置**（4 物理核/8 逻辑核机型实测）：
- `workers=物理核数`（进程池扩展受物理核限制，超订无益）
- 批量对拍基准：`python -X utf8 tools/bench_sim.py --n 128 --workers 4`
- 确定性口径：`seed_r = seed + r`，逐 seed 与串行/`run_mc_pool` 全等
- `want_stats=True` 单场变慢（退全量事件探针）；只做 reward 的胜负面用默认 light 口径

### 三方对齐复现

```bash
# 全量刷账（约 28 分钟；--force 才会重跑，正常先删旧产物）
python -X utf8 tools/verify_oracle.py --skip-fixtures --force
# 只比对（秒级），账本仍是 output/oracle/alignment.json
python -X utf8 tools/verify_oracle.py --compare-only
```

### 阵容格式（v4 推荐，v3 兼容）

```jsonc
// v4：平铺简洁；`in` 指向承载袋的数组下标（袋内联动显式化）
{
  "version": 4,
  "name": "我的阵容",
  "character": "Ranger",
  "round": 12,
  "grid": [7, 9],
  "items": [
    { "id": "Leather Bag", "at": [3, 3], "r": 0 },
    { "id": "Bow and Arrow", "at": [3, 3], "r": 0, "in": 0, "gems": ["Chipped Ruby"] }
  ]
}
```

- `gems` — 镶嵌宝石；`rotation`/`r` — 角度制（0/90/180/270）
- `(row,col)` 为旋转后占格左上角（对齐游戏 `topLeftCell` 存档语义）
- v3（嵌套 `contents`）仍完全兼容；游戏历史导出的阵容即此家族

### 打包

```bash
python build_exe.py                        # 外挂 AI → dist/BackpackAI.exe
python build_simulator_exe.py              # 模拟器 → dist/BackpackSimulator.exe
python build_combatlog_exporter_exe.py     # 日志导出器 → dist/BackpackCombatLog.exe
```

## 注意事项

- 游戏更新后 `OS::singleton` 偏移可能漂移，运行 `tools/sweep_offsets.py` 自动校准；日志导出器用 `tools/probe_combatlog.py` 重标定
- 改动内核/物品数据后，跑验收链（verify_linkage → audit_item_effects → regression_baseline --check）防回归；行为对齐以 `output/combat_logs/` 实录对照（compare_truth）为准
- **模拟器对战结果受已知问题影响，与游戏实际结果存在偏差**（模拟器与录制语料管线已 1690/1690 逐位一致；与游戏实机的未覆盖时序面仍可能有差异）
- 本软件仅供学习研究使用，请勿用于违反游戏服务条款的用途