# C++ 模拟器性能优化清单

本轮针对 1.1.10 的 C++ 内核，源码位于 `output/_v1110/sim_native/native_sim_cpp/native_sim`。以改动前已通过全量核验的 `bb677d7b…` DLL 为对照。

| 项目 | 采样中的热点 | 改动 | 一致性检查 |
| --- | --- | --- | --- |
| 入包联动通知 | `CoreItem::onItemAdded` 为每个通知创建颜色枚举数组和结果字典 | 使用四个栈上布尔值，命中受影响格缓存时直接取值 | 先查询所有颜色，再按原顺序写入并调用联动回调 |
| 受影响物品判定 | `isItemAffected`、`canAffect_color` 和基类行为探测反复走动态派发 | 直接调用无覆写的内部方法，基类仅在注入行为存在时探测对应方法 | 保留具体物品的虚派发、格集合遍历顺序和注入行为 |
| 战斗帧调度 | `CoreCombat::physicsTick` 每帧经通用接口读取上下文、调用角色和库存方法 | 对内核构建的具体对象直接访问字段并调用方法 | 保留双方计时器、疲劳、冷却、空闲回调和宿主 RNG 的顺序 |
| 角色计时和体力回复 | 每帧重建计时掩码、调用体力上限查询并分配调试守卫用的空字符串 | 直接计算掩码，对浮点体力值使用等价的加法与夹取，其他类型使用原运算 | 每次触发前重新读掩码，保留夹取比较顺序和计时回调 |
| 局部链接时优化 | 跨编译单元的运行时辅助函数与战斗帧调度反复调用 | 对采样中的六个热点编译单元启用 LTO | 保留浮点编译选项、全部 22 个 `gd_sim_*` ABI 符号和逐场事件哈希 |
| 基于样本的编译优化 | 热路径上的调用和分支缺少实际频率信息 | 用原版回放和训练批量入口采集计数，对热点编译单元启用 PGO | 输入、编译浮点选项和 ABI 一致，用逐事件语料验证生成的 DLL |
| 事件总线 | 同一个信号重复查表，部分事件在没有监听器时仍分配空列表并构造诊断身份 | 合并查表、直接调用无覆写的方法，无监听且关闭诊断时提前返回 | 保留事件入日志顺序、发射者 ID 分配、监听器顺序、终局检查和诊断路径 |

优化脚本会检查待替换的生成代码和相关方法声明。原始 C++、生成代码和 DLL 已备份到远端 `codex/native-perf50-baseline`（`cd9dfad4`），角色数值路径改动前另在远端 `codex/native-perf50-frames` 保存了入包和调度候选（`811813ec`）。

## 测量口径

- 旧基准固定一套玩家阵容、25 套对手、每套 8 个种子。使用单线程训练批量入口，包含 DLL 加载和阵容打包。战斗时长均值 8.40 秒、中位数 9.96 秒。
- 平均时长基准从 2,604 场冻结原版录制中按战斗时长分位点固定抽取 200 场。使用单线程原版回放入口，输入预先打包，计时区间包括 Python 绑定和 C++ 模拟。逐场核对原版胜负和自然终局，并比对优化前后的完整结果结构哈希。全语料时长均值 16.12 秒、中位数 12.81 秒。
- 30、40、50 场/秒三档均按同一批回放的单线程实测验收。以整轮吞吐计量，稳定达标以重复测量中最慢一轮为准。
- 全量原版一致性核验覆盖基准 914 场和扩展 1,690 场，包括事件顺序、帧、数值、父事件、普通物品与宝石来源、胜负和自然终局。二进制以 SHA-256 关联到验收报告。

## 实测记录

首轮平均时长基准在本机 i5-8265U 的电池供电状态下测量。三套 DLL 交替跑三轮，200 场实际战斗时长均值为 16.11 秒，中位数为 12.81 秒。每场胜负和终局与原版一致，三套 DLL 的完整结果哈希相同。

| 累计改动 | 单线程中位数（场/秒） | 单线程范围（场/秒） | 每 200 场 CPU 时间中位数 |
| --- | ---: | ---: | ---: |
| 原基线 | 25.25 | 24.26–25.30 | 7.55 秒 |
| 入包判定和帧调度 | 26.82 | 26.35–28.52 | 7.00 秒 |
| 再加角色计时和体力优化 | 28.28 | 27.95–28.91 | 6.73 秒 |

含角色计时和体力优化的常规链接版本，四线程原版回放三轮为 59.74、75.54 和 69.26 场/秒，中位数为 **69.26 场/秒**，胜负、终局和完整结果哈希与单线程相同。

局部链接时优化的首轮三组交替测试中，单线程中位数由 28.00 升到 **29.53 场/秒**，200 场 CPU 时间由 6.75 降至 6.30 秒。该 DLL 通过原版 2,604 场逐事件核验，逐场 C++ 事件流水 SHA-256 全部等于基线。

另行评估了 295 处物品自身方法派发。加入角色版本后的两轮为 27.43 和 27.05 场/秒，角色版本同轮为 26.96 和 27.86 场/秒，样本未显示稳定收益。

使用同一批平均 16.11 秒的 200 场回放交替比较 LTO 和 PGO，供电始终为电池。每一轮均通过原版胜负和自然终局检查，各组完整结果哈希相同。

| 构建 | 线程数 | 三轮中位数（场/秒） | 三轮范围（场/秒） |
| --- | ---: | ---: | ---: |
| 局部 LTO | 1 | 29.89 | 28.96–30.29 |
| 局部 LTO | 4 | 78.67 | 77.92–79.13 |
| 局部 LTO + PGO | 1 | **31.76** | 29.11–32.65 |
| 局部 LTO + PGO | 4 | **88.29** | 85.05–89.54 |

上表保留四线程数据供参考。电池供电下，该次 PGO 测量的单线程中位数超过 30 场/秒，最慢一轮为 29.11 场/秒。该版本的基准 914 场和扩展 1,690 场全部通过严格逐事件核验，2,604 份 C++ 事件流水哈希与优化前完全相同。

## 本机构建与复测

在仓库根目录运行以下命令。PGO 采样复用本地验收夹具和两套基准的种子数据。

```powershell
$stage = 'output/_v1110'
$native = "$stage/sim_native/native_sim_cpp/native_sim"
python "$stage/build_native_hot_lto.py" $native --pgo --out "$stage/native_perf50/rebuilt-pgo.dll"
python "$stage/bench_native_corpus.py" --dll "$stage/native_perf50/rebuilt-pgo.dll" --workers 1 --repeat 24 --out "$stage/native_perf50/rebuilt-perf.json"
```

## 单线程稳定性与 CPU 负载

接电后，对 PGO 版运行了 5 批初测、6 批独立进程复测和 24 批连续回放。三组最慢一轮分别是 16.34、40.64 和 31.74 场/秒。初测最慢两轮附近的系统负载接近 100%。连续 24 批的中位数为 59.32 场/秒，降到 31.74 场/秒的一轮整机负载为 68.8%。各轮使用相同的 200 场、输入哈希和完整结果哈希。[单线程原始记录](../output/_v1110/native_perf50_serial_ac_baseline.json)

以连续 24 批拟合整机 CPU 负载与耗时的关系。在本机接电、负载 28.8%–68.8% 的观测范围内，负载每增加 10 个百分点，模型估计耗时增加约 18.5%。按连续四批分组留出验证，耗时预测的绝对相对误差中位数为 5.7%，第 90 百分位为 18.7%。34.75% 参考负载下估计为 60.58 场/秒。校正值用于比较，三档阈值以未校正的单线程实测值验收。[拟合脚本](../output/_v1110/fit_native_serial_load.py) · [拟合结果](../output/_v1110/native_perf50_serial_load_fit.json)

新版基准的 `--repeat` 会复用已打包的 200 场，记录每批的墙钟时间、主线程 CPU 时间、整机负载与估算后台负载。比较新旧版本时短间隔交替执行，检查成对耗时差和负载差。降频和同核竞争都会影响同一负载下能完成的工作量。[微软对 CPU 时间与实际处理能力的说明](https://learn.microsoft.com/en-us/troubleshoot/windows-client/performance/cpu-usage-exceeds-100)

事件总线的八组交替单线程对照，成对墙钟耗时中位数下降 3.4%，成对 CPU 时间中位数下降 2.7%。以估算后台负载差拟合成对耗时比，在接近相同负载时，探索性估计为耗时下降 3.0%。[事件总线 A/B](../output/_v1110/native_perf50_event_bus_ab.json)

事件总线版接电连续 24 批的单线程中位数为 **79.17 场/秒**，最慢为 **54.37 场/秒**。估算后台负载覆盖 3.8%–36.5%，每个批次均实际超过 50 场/秒，输入和结果哈希与前版相同。按估算后台负载拟合，每增加 10 个百分点，耗时估计增加 18.9%，留出误差中位数为 3.4%，第 90 百分位为 11.0%。[连续单线程记录](../output/_v1110/native_perf50_event_bus_serial.json) · [后台负载拟合](../output/_v1110/native_perf50_event_bus_load_fit.json)

事件总线版已更新至本地默认训练运行时 `dist/native_1_1_10`，通过全部 2,604 场严格逐事件核验，逐场 C++ 事件哈希保持一致。改动前的 C++ 源码和 DLL 已提交并推送到了 `codex/native-perf50-verified` 的 `b17613ae`。[事件总线源码生成](../output/_v1110/optimize_native_event_bus.py) · [事件总线全量验收](../output/_v1110/native_perf50_event_bus_full_gate.json) · [事件哈希](../output/_v1110/native_perf50_event_bus_event_hashes.json)

[首轮 A/B](../output/_v1110/native_perf50_battery_ab.json) · [LTO 对照](../output/_v1110/native_perf50_lto_ab.json) · [最终性能记录](../output/_v1110/native_perf50_final_benchmark.json) · [全量验收](../output/_v1110/native_perf50_pgo_full_gate.json) · [事件哈希比对](../output/_v1110/native_perf50_pgo_event_hashes.json)

[入包优化](../output/_v1110/optimize_native_placement.py) · [逐帧优化](../output/_v1110/optimize_native_frames.py) · [LTO 和 PGO 构建](../output/_v1110/build_native_hot_lto.py) · [训练基准](../output/_v1110/bench_native_hot_path.py) · [平均时长基准](../output/_v1110/bench_native_corpus.py)

## 事件总线版的后续优化

本轮从 DLL `04b332ba…` 开始。实验前核对了远端 `codex/native-perf50-verified` 上的 `d9ec7b55` 备份，活跃 C++ 源码目录内的 704 个归档文件逐字节一致。固定输入仍为原版时长分层的 200 场，平均战斗时长 16.11 秒。

正式基线采样共取得 1,062 个有效栈样本。叶节点包括 `CoreCombat::physicsTick`（90）、`CoreItem::call_method`（51）、`CoreItem::physicsTick`（41）、`GdEnum::get`（14）及 `EmitAndLog`（12）。`CoreBuff::gainTemporary` 和 `gd_str_fn` 的包含样本分别为 110 和 103。包含样本可同时计入多个调用层。[基线采样](../output/_v1110/native_perf50/followup_baseline_profile.json)

独立计数构建在同一批回放中测得战斗推进 83.08%、场景装配 16.03%、结果导出约 0.01%。Python、FFI 和原生入口的剩余时间合计 0.88%，其中 Python 侧位于 ctypes 调用外的时间为 0.76%。计数构建替换了三个编译单元，比例用于定位。空闲队列、延迟队列、动作队列的空访问比例分别为 223,349/223,352、61,925/132,161、84,240/193,353。计时器扫描遇到 14,181,456 次有效对象访问，其中 683,532 次有计时器（4.82%）。[耗时拆分与计数](../output/_v1110/native_perf50/followup/probe.json)

扩展计数中，描述符登记为 10.49 毫秒，占全程 0.33%。物品与宝石装配为 386.29 毫秒，占全程 12.19%。现有进程级 `ItemProto` 已复用静态原型，描述符也在场内复用。下一步应优先拆分物品装配中的对象构造、摆放和效果应用，再定位可跨场共享的不可变数据。以 Python、FFI 和原生入口合计的 0.88% 上限估算，批量回放 ABI 延后。

200 场记录到 736 次物品计时器创建、1,256 次从停止状态发起的启动请求、311 次运行中再次启动的请求，以及 1,919 次停止倒计时请求。计时器遍历期间有 122 次启动、4 次再次启动、667 次停止请求，未观测到创建。稀疏索引需要覆盖遍历中的这些变化，并额外用同帧创建用例验证；当前继续使用顺序遍历。[扩展装配与计时器计数](../output/_v1110/native_perf50/followup/probe_extended.json)

每个候选用同样的 200 场和正式优化 DLL 测量，一组包含相邻的基线与候选各一批。8 组交替 AB／BA，复测时反转起始顺序。两边逐批检查原版终局和完整回放结果哈希。表中的百分比是成对耗时降幅的中位数，负值代表耗时增加。

| 候选 | 主线程 CPU 耗时降幅 | 墙钟耗时降幅 | CPU 耗时更低的组数 |
| --- | ---: | ---: | ---: |
| 折叠 264 处静态枚举读取 | 7.10% | 7.10% | 7/8 |
| 三条空队列早退，首测 | 5.27% | 4.92% | 5/8（1 组持平） |
| 三条空队列早退，复测 | −5.64% | −5.22% | 2/8 |
| 将 `shard_05` 和 `shard_12` 加入 LTO／PGO，首测 | −0.58% | −0.18% | 3/8 |
| 扩展 LTO／PGO，复测 | 2.68% | 2.94% | 4/8（1 组持平） |

首批保留静态枚举折叠。空路径和编译单元扩展在两轮对照中的方向相反，本轮排除。枚举版重采样 1,123 栈，`gd_str_fn` 与 `CoreBuff::call_method` 仍分别有 128 和 134 个包含样本。[枚举对照](../output/_v1110/native_perf50/followup/enums_ab.json) · [枚举版采样](../output/_v1110/native_perf50/followup/enums_profile.json) · [空队列首测](../output/_v1110/native_perf50/followup/queues_ab.json) · [空队列复测](../output/_v1110/native_perf50/followup/queues_ab_repeat.json) · [编译配置首测](../output/_v1110/native_perf50/followup/expanded_ab.json) · [编译配置复测](../output/_v1110/native_perf50/followup/expanded_ab_repeat.json)

第二批以枚举版为基线。`CoreItem::trigger` 和 `CoreItem::doCooldownEffect` 按原有 `oracle_trace` 与 `_stacktrace` 条件再构造诊断参数。触发路径在诊断关闭时仍执行原 `getSpeed` 动态调用。独立对照的 CPU 耗时降幅为 13.50%，墙钟耗时降幅为 12.11%，两项均有 7/8 组降低。[诊断格式化对照](../output/_v1110/native_perf50/followup/diagnostics_ab.json)

`CoreBuff::gainStacks` 到 `gainTemporary` 的单条直调，CPU 耗时首测下降 3.33%，反转顺序后复测上升 1.43%，本轮排除。上述五种候选均通过三场定向逐事件回放。[Buff 首测](../output/_v1110/native_perf50/followup/buff_ab.json) · [Buff 复测](../output/_v1110/native_perf50/followup/buff_ab_repeat.json)

最终候选包含枚举折叠和延迟诊断格式化。直接与起始事件总线版做 8 组 AB／BA，主线程 CPU 耗时的成对中位数下降 **21.47%**，墙钟下降 **21.50%**，两项均为 8/8 组降低。估算后台负载为 1.9%–8.9%。[最终 A/B](../output/_v1110/native_perf50/followup/final_ab.json)

基准 914 场和扩展 1,690 场全部通过原版严格逐事件验收。2,604 场的 C++ 事件哈希逐场比较一致，整组事件哈希摘要为 `b8066c9224bc418923c62f5a3dafb8912100b21bb0026c3b13669872f90e2f54`。`--native-perf50` 的源码再生成已接入两项优化。[全量验收](../output/_v1110/native_perf50/followup/diagnostics_full_gate.json) · [逐场事件哈希比对](../output/_v1110/native_perf50/followup/diagnostics_event_hashes.json)

最终候选重采样 1,017 栈，`gd_str_fn` 的包含样本由枚举版的 128/1,123 降至 33/1,017。`CoreCombat::physicsTick` 和物品的动态派发仍是热点。下一轮可先在物品与宝石装配阶段分开量测对象构造、摆放与效果应用，再选一条高频派发链验证。稀疏计时器索引需单独覆盖同帧变更，`GdVal`、字典和分配器仍需局部成本数据。[最终候选采样](../output/_v1110/native_perf50/followup/diagnostics_profile.json)

接电的首次连续 24 批中位数为 92.27 场/秒。第 3 批估算后台负载达到 65.2%，实测速率 37.98 场/秒，低于发布门槛，其余 23 批均超过 50 场/秒。整次后台负载范围为 4.3%–65.2%。对整组数据拟合，后台负载每增加 10 个百分点，耗时估计增加 16.4%，按连续四批分组留出的相对耗时误差中位数为 1.84%。负载拟合用于解释波动，验收采用逐批原始吞吐。[首次持续测速](../output/_v1110/native_perf50/followup/diagnostics_serial.json) · [负载拟合](../output/_v1110/native_perf50/followup/diagnostics_load_fit.json)

接电后独立复测完整 24 批。估算后台负载为 1.7%–27.5%，中位数 **94.25 场/秒**，最慢 **68.70 场/秒**，24 批均超过 50 场/秒。发布条件在该复测范围内通过。[持续测速复测](../output/_v1110/native_perf50/followup/diagnostics_serial_retest.json)

已部署至 `dist/native_1_1_10`，DLL SHA-256 为 `a2556667fb9a461d62a77f3687a01636e362ea220a1f23f75035c828f53fd9b7`，与源码目录内的 DLL、验收报告及运行时清单一致。正常训练评估 12 场无装配失败，另有 12 场固定种子逐场胜负与旧版一致。旧运行时保留于 `dist/native_1_1_10_before_followup`。[部署与训练验证](../output/_v1110/native_perf50/followup/diagnostics_installation.json)

## 物品和宝石装配优化

本轮基线为 `a2556667…`，远端源码与 DLL 备份为 `8eb8758f`。计数构建仅修改独立副本的包装单元，使用固定 200 场，包含 14,120 件物品、813 颗宝石和 36 项保存效果。测量是在各操作原有位置插入计时，包含摆放触发的回调。总装配时间 383.66 毫秒，各阶段如下。

| 环节 | 毫秒 | 占总装配时间 |
| --- | ---: | ---: |
| 对象构造 | 46.82 | 12.20% |
| 字段设置与 setup | 37.68 | 9.82% |
| readyInit | 53.22 | 13.87% |
| 坐标数组填充 | 3.50 | 0.91% |
| 摆放与同步回调 | 230.31 | 60.03% |
| 保存效果应用 | 0.45 | 0.12% |
| 宝石安装回调 | 0.45 | 0.12% |
| 其余循环与容器操作 | 11.23 | 2.93% |

对象构造、setup 和 readyInit 均包含物品与宝石。保存效果应用包括摆放前恢复和摆放后恢复。摆放回调所触发的效果计入摆放。计时探针有开销，正式吞吐使用独立优化构建。[装配计数](../output/_v1110/native_perf50/assembly/probe.json)

优先优化摆放的 `isItemAffected`。它在影响范围缓存缺失时构造空数组，并继续遍历目标物品的格子。候选直接在字典缺失时返回 false，在已缓存范围为空数组时返回 false。`isBag` 和颜色判断仍在范围读取前执行，非字典缓存沿用原查询。生成脚本校验目标函数内容和无覆写条件。[源码变换](../output/_v1110/optimize_native_assembly.py)

最终候选进一步将同一目标的背包类型判断复用于四种颜色。生成脚本检查全部三种 `isBag` 实现都只返回固定布尔值。每种颜色的查询仍先于影响回调完成。仅处理空缓存的首候选，首轮 CPU 耗时中位数增加 0.85%，复测下降 5.32%，本轮采用背包类型复用候选继续验收。

| 背包类型复用候选 | CPU 耗时降幅 | 墙钟耗时降幅 | CPU 更快组数 |
| --- | ---: | ---: | ---: |
| 首轮 8 组 AB／BA | 3.92% | 4.64% | 6/8 |
| 反转起始顺序复测 8 组 | 1.52% | 0.82% | 5/8 |
| 独立确认 8 组 | 3.50% | 3.45% | 6/8 |
| 合计 24 组的成对中位数 | 2.36% | 2.96% | 17/24 |

两种候选均通过三场定向逐事件回放。正式测速逐批校验原版终局、固定输入哈希和完整结果哈希。[首轮对照](../output/_v1110/native_perf50/assembly/fused_ab.json) · [反转复测](../output/_v1110/native_perf50/assembly/fused_ab_repeat.json) · [独立确认](../output/_v1110/native_perf50/assembly/fused_ab_confirm.json)

最终候选通过原版 914 + 1,690 场严格逐事件验收，与本轮基线的 2,604 份 C++ 事件哈希逐场一致。接电连续运行 24 批，中位数 **102.89 场/秒**，最慢 **88.84 场/秒**，每批均超过 50 场/秒。估算后台负载为 4.0%–19.9%。[全量验收](../output/_v1110/native_perf50/assembly/fused_full_gate.json) · [事件哈希](../output/_v1110/native_perf50/assembly/fused_event_hashes.json) · [持续吞吐](../output/_v1110/native_perf50/assembly/fused_serial.json)

已更新默认训练运行时，部署与验收 DLL 的 SHA-256 均为 `747d52d526ff017f632ffcd3462fdfb34a163ce957d02a99853cf1a017531eb4`。正常训练评估 12 场无错误，另有 12 场固定种子逐场胜负与基线一致。旧运行时保留于 `dist/native_1_1_10_before_assembly`。`--native-perf50` 再生成入口已接入该优化。[部署记录](../output/_v1110/native_perf50/assembly/fused_installation.json)

## 100／125 场每秒的循环优化

目标采用估算后台 CPU 负载 20% 的换算吞吐。每个正式候选仍需完成固定 200 场单线程交替对照、2,604 场严格逐事件验收、逐场 C++ 事件哈希比对，以及连续 24 批原始吞吐均达到 50 场/秒的部署检查。20% 换算使用同一 DLL 的实际负载范围和分组留出误差，记录实际供电条件。

本轮起点为 `747d52d5…`，远端备份为 `d7f51d1c`。重采样共取得 1,648 个栈样本。叶节点中 `CoreCombat::physicsTick` 命中 137 次，通用 `call_method` 命中 88 次，物品 `physicsTick` 命中 88 次，物品 `call_method` 命中 68 次。动态派发仍是主要候选。[本轮基线采样](../output/_v1110/native_perf50/cycles/baseline_profile.json)

首批独立候选包括 Buff 的 18 处自调用、角色的 152 处自调用、事件总线的 15 处上下文属性读取，以及两处九元素行为白名单查询。自调用候选校验类没有生成子类，属性读取候选以确切类型判断保留通用读取回退，白名单候选只折叠已验证的字面字符串数组成员查询。[候选生成脚本](../output/_v1110/optimize_native_leaf_dispatch.py)

本轮基线接电持续 24 批，中位数 67.92 场/秒，最慢 47.51 场/秒。估算后台负载覆盖 12.2%–47.5%，按同版样本拟合至 20% 后为 **74.78 场/秒**。连续四批分组留出的预测误差中位数为 1.83%，第 90 百分位为 5.43%。该原始记录包含一批低于部署门槛的测量。[基线持续测速](../output/_v1110/native_perf50/cycles/baseline_serial.json) · [20% 换算](../output/_v1110/native_perf50/cycles/baseline_load20.json)

Buff 自调用首轮 CPU 耗时增加 8.48%，事件总线上下文读取增加 4.39%，均排除。角色自调用三轮各 8 组的 CPU 降幅分别为 1.13%、9.41%、3.94%，合计成对中位数下降 **5.21%**，墙钟下降 **4.43%**。白名单三轮 CPU 降幅分别为 4.31%、3.16%、1.73%，合计中位数下降 2.38%，墙钟下降 1.36%。[角色首测](../output/_v1110/native_perf50/cycles/character_ab.json) · [角色复测](../output/_v1110/native_perf50/cycles/character_ab_repeat.json) · [角色确认](../output/_v1110/native_perf50/cycles/character_ab_confirm.json)

两项合并后的整版首测 CPU 耗时增加 0.75%，墙钟下降 0.44%，反转顺序复测也未显示稳定收益。因此仅角色自调用进入全量验收，合并版和白名单改动本轮排除。[合并版首测](../output/_v1110/native_perf50/cycles/round01_ab.json) · [合并版复测](../output/_v1110/native_perf50/cycles/round01_ab_repeat.json)

角色候选通过 914 + 1,690 场原版严格逐事件验收，2,604 场 C++ 事件哈希逐场一致。接电连续 24 批中位数 97.34 场/秒，最慢 72.05 场/秒，均超过 50 场/秒。估算后台负载覆盖 5.3%–27.2%，同版样本拟合到 20% 后为 **82.69 场/秒**，分组留出预测误差中位数 1.87%，第 90 百分位 3.63%。100 和 125 的目标继续推进。[验收](../output/_v1110/native_perf50/cycles/character_full_gate.json) · [事件哈希](../output/_v1110/native_perf50/cycles/character_event_hashes.json) · [连续吞吐](../output/_v1110/native_perf50/cycles/character_serial.json) · [20% 换算](../output/_v1110/native_perf50/cycles/character_load20.json)

已部署 DLL `ef599b44623242e43c108e7eb05dc012fa6384bebd66aee4dcc03c483553f7cf`，正常训练评估和固定种子检查通过，旧运行时保留在 `dist/native_1_1_10_before_cycle01`。[部署记录](../output/_v1110/native_perf50/cycles/character_installation.json)

下一轮计数构建使用角色候选的对象文件，仅替换 `gd_rt` 计数单元。固定 200 场中，通用 `empty` 调用 1,379,695 次，`randf_range` 1,250,894 次，计时器 `tick` 1,022,970 次，`_tickChargePath` 320,482 次。`nextCell`、`elapsed` 的属性读取分别为 651,690 次和 643,344 次。充能路径被选为下一批候选。[方法与属性调用计数](../output/_v1110/native_perf50/cycles/dispatch_counts.json)

### 第二轮

起点 DLL 为 `ef599b44…`，远端备份为 `b45a2143`。充能路径候选把 9 处读取和 5 处写入替换成确切类型的字段访问，并保留其他类型回退。它通过原有三场定向回放和额外五场高充能调用回放，但两轮 CPU 耗时降幅分别为 −1.18% 和 0.88%，本轮排除。仅 RNG 自调用的两轮降幅为 2.48% 和约 0%，也排除。

原生 RNG 候选包含 15 处已证明无覆写的自调用，并在底层接收器为 `GdRng` 时直接调用同一 `randf_range` 实现。参数转换、随机调用数量和顺序均保留，其他接收器走原通用路径。三轮各 8 组 CPU 降幅分别为 1.26%、3.56%、2.95%，合计成对中位数下降 **2.91%**，墙钟下降 **1.52%**。[首测](../output/_v1110/native_perf50/cycles02/rng_native_ab.json) · [复测](../output/_v1110/native_perf50/cycles02/rng_native_ab_repeat.json) · [确认](../output/_v1110/native_perf50/cycles02/rng_native_ab_confirm.json)

该候选通过 914 + 1,690 场严格逐事件核验，与第一轮的逐场 C++ 事件哈希完全一致。接电、自然后台负载 5.3%–16.7% 下连续 24 批，中位数 **104.81 场/秒**，最慢 **90.85 场/秒**，全部达到部署门槛。20% 的换算使用以下补充校准数据。[验收](../output/_v1110/native_perf50/cycles02/rng_native_full_gate.json) · [事件哈希](../output/_v1110/native_perf50/cycles02/rng_native_event_hashes.json) · [自然负载 24 批](../output/_v1110/native_perf50/cycles02/rng_native_serial.json)

补充负载校准使用两个低优先级进程，以 20 毫秒周期、20%／85% 工作占比交替运行，单次最多 120 秒，结束后退出。首次校准的留出误差中位数为 5.54%，第 90 百分位为 22.25%。增加 30 秒预热后的完整 24 批，估算后台负载为 9.0%–37.3%，实测中位数 96.86、最慢 72.73 场/秒。20% 换算值为 **90.11 场/秒**，留出误差中位数 2.67%，第 90 百分位 6.27%。该值对应本机此受控负载采样条件。[首次校准](../output/_v1110/native_perf50/cycles02/rng_native_load_calibration.json) · [预热校准](../output/_v1110/native_perf50/cycles02/rng_native_load_calibration_warm.json) · [20% 换算](../output/_v1110/native_perf50/cycles02/rng_native_load20_warm.json) · [校准脚本](../output/_v1110/bench_native_load_calibration.py)

已部署 DLL `201b390883f77eb6883a751503a4e4c049a8192297647a11b6ff73c556230e34`，正常训练评估及固定种子检查通过。旧运行时保留在 `dist/native_1_1_10_before_cycle02`。下一轮对已部署版本采集至少 6,000 个栈样本，并保留叶节点指令偏移。[部署记录](../output/_v1110/native_perf50/cycles02/rng_native_installation.json)


### 第三轮

起点 DLL 为 `201b3908…`，远端备份为 `81144856`。该版取得 6,013 个带叶节点指令偏移的栈样本，固定 200 场共运行 54 批。热点仍包括战斗逐帧、物品逐帧及通用派发。指令位置命中计时器数组长度读取、冷却活跃状态判断和宝石类型查询。[细粒度采样](../output/_v1110/native_perf50/cycles02/rng_native_profile_instructions.json)

数组 `size`／`empty` 的 80 处内联查询保留其他类型的原通用回退。编译进程同时运行时的初测 CPU 耗时下降 4.56%，编译结束后的独立复测 CPU 耗时增加 0.45%、墙钟增加 1.22%，本轮排除。[有编译后台的初测](../output/_v1110/native_perf50/cycles03/array_queries_ab_compile_background.json) · [独立复测](../output/_v1110/native_perf50/cycles03/array_queries_ab.json)

最终采用全生成分片 LTO／PGO。热点编译单元由 6 个扩大至 `gd_rt`、`engine_wrapper` 和全部 16 个生成分片，共 18 个，`sym_ids` 和 `register_all` 沿用普通编译。源码及浮点选项不变。采样工作负载仍为三场定向回放、固定 200 场和 200 场训练。22 个 C ABI 符号与基线相同，DLL 从 10,413,483 字节减至 9,419,176 字节。构建脚本默认采用此配置，`--hot-preset legacy` 可复现此前的六单元配置。[ABI 比较](../output/_v1110/native_perf50/cycles03/full_pgo_abi.json) · [构建脚本](../output/_v1110/build_native_hot_lto.py)

两轮各 8 组 AB／BA，主线程 CPU 耗时降幅分别为 6.60%、5.82%，墙钟降幅分别为 5.76%、5.15%。合计 16 组成对中位数 CPU 下降 **6.25%**，墙钟下降 **5.58%**。[首测](../output/_v1110/native_perf50/cycles03/full_pgo_ab.json) · [反转复测](../output/_v1110/native_perf50/cycles03/full_pgo_ab_repeat.json)

914 + 1,690 场原版严格逐事件核验全部通过，逐场 C++ 事件哈希全部一致。接电、自然后台负载 3.6%–27.8% 下连续 24 批，中位数 **115.58 场/秒**，最慢 **82.52 场/秒**，全部达到部署门槛。同一 DLL 的自然负载样本拟合至 20% 为 **94.03 场/秒**，连续四批分组留出的耗时相对误差中位数为 1.28%，第 90 百分位为 4.88%。[全量验收](../output/_v1110/native_perf50/cycles03/full_pgo_full_gate.json) · [事件哈希](../output/_v1110/native_perf50/cycles03/full_pgo_event_hashes.json) · [持续吞吐](../output/_v1110/native_perf50/cycles03/full_pgo_serial.json) · [20% 换算](../output/_v1110/native_perf50/cycles03/full_pgo_load20.json)

已部署 DLL `4ccdaf2bef6ad526a5740355bc413e18015d341f5d98182cdc68e7688570e038`。正常训练评估 12 场无错误，另 12 场固定种子胜负与基线一致，运行时清单与验收 DLL 哈希相同。旧版保留于 `dist/native_1_1_10_before_cycle03`。继续从该已部署版本采样下一轮。[部署记录](../output/_v1110/native_perf50/cycles03/full_pgo_installation.json)


### 第四轮

起点 DLL 为 `4ccdaf2b…`，远端备份为 `6f26c12a`。已部署版本新采样取得 6,052 个栈样本、56 批固定回放。热点继续包括计时器数组读取、冷却标志通用判断、物品派发及符号查询互斥锁。[已部署版本采样](../output/_v1110/native_perf50/cycles03/full_pgo_profile.json)

五处冷却标志的布尔快速路径保留其他类型回退。三场定向回放通过。首测末段与一次反汇编重叠，CPU 耗时下降 1.86%，已在报告中标记；独立反转复测 CPU 耗时增加 4.11%，本轮排除。首次定向命令漏带 `run948` 摆放观测参数，补齐后的三场严格核验通过。[有反汇编重叠的初测](../output/_v1110/native_perf50/cycles04/cooldown_flags_ab.json) · [独立复测](../output/_v1110/native_perf50/cycles04/cooldown_flags_ab_repeat.json)

线程局部符号缓存的三轮 CPU 耗时降幅分别为 −2.29%、3.35%、−3.76%，本轮排除。[首测](../output/_v1110/native_perf50/cycles04/symbol_cache_ab.json) · [复测](../output/_v1110/native_perf50/cycles04/symbol_cache_ab_repeat.json) · [确认](../output/_v1110/native_perf50/cycles04/symbol_cache_ab_confirm.json)

最终采用进程级原子符号读取表。已注册名称和不可变查询项保留在进程静态内存中，注册写入继续加锁。读表前后验证写入版本号，写入重叠、未命中、槽冲突或超出名称表范围均使用原加锁路径。保留内建符号初始化、旧名称别名及动态重注册语义。生成脚本校验原注册实现及重复应用的内容哈希。[源码生成](../output/_v1110/optimize_native_atomic_symbols.py)

定向测试覆盖内建初始化、改名、同名重注册、临时字符串、槽冲突、内嵌空字符、大 ID 回退，以及八线程读取和同时注册。三场定向逐事件回放通过，22 个 C ABI 符号保持一致。重新生成的 C++ 与受测副本逐字节相同，重复执行生成脚本保持字节不变。[并发测试源码](../output/_v1110/test_native_symbol_cache.cpp) · [测试结果](../output/_v1110/native_perf50/cycles04/symbol_atomic_test.json) · [ABI](../output/_v1110/native_perf50/cycles04/symbol_atomic_abi.json)

三轮各 8 组 AB／BA，CPU 耗时降幅分别为 0.43%、6.36%、7.18%，墙钟降幅分别为 1.38%、6.93%、6.10%。合计 24 组成对中位数 CPU 下降 **4.52%**，墙钟下降 **3.85%**。[首测](../output/_v1110/native_perf50/cycles04/symbol_atomic_ab.json) · [反转复测](../output/_v1110/native_perf50/cycles04/symbol_atomic_ab_repeat.json) · [确认](../output/_v1110/native_perf50/cycles04/symbol_atomic_ab_confirm.json)

914 + 1,690 场原版严格逐事件核验全部通过，逐场 C++ 事件哈希完全一致。接电、自然负载连续 24 批，中位数 **112.59 场/秒**，最慢 **100.35 场/秒**，全部达到部署门槛。自然样本未覆盖 20%，保留拟合拒绝结果，补充与第二轮同设置的 30 秒预热受控负载校准。[全量验收](../output/_v1110/native_perf50/cycles04/symbol_atomic_full_gate.json) · [事件哈希](../output/_v1110/native_perf50/cycles04/symbol_atomic_event_hashes.json) · [自然负载测速](../output/_v1110/native_perf50/cycles04/symbol_atomic_serial.json)

补充校准的估算后台负载为 9.5%–36.0%，24 批原始吞吐中位数 **102.99**、最慢 **70.43 场/秒**。20% 换算值为 **92.70 场/秒**，连续四批分组留出预测误差中位数为 2.66%，第 90 百分位为 4.86%。该换算对应受控负载采样条件，与第三轮自然负载模型分别记录。100／125 换算目标继续推进。[受控校准](../output/_v1110/native_perf50/cycles04/symbol_atomic_load_calibration_warm.json) · [20% 换算](../output/_v1110/native_perf50/cycles04/symbol_atomic_load20_warm.json)

已部署 DLL `1291ef1b6ae50856e9e3585d9193734b64a4a1c15cf98ebca1ebedf7333ce940`，正常训练评估 12 场无错误，另 12 场固定种子胜负与基线一致，部署、验收与运行时清单的 DLL 哈希相同。旧版保留于 `dist/native_1_1_10_before_cycle04`。下一轮从该版重采样，并用独立诊断构建量化计时器索引可复用的机会。[部署记录](../output/_v1110/native_perf50/cycles04/symbol_atomic_installation.json)


### 第五轮（未替换运行时）

基线仍为第四轮 `1291ef1b…`，远端备份为 `5e2ab6b3`。新采样取得 6,035 个栈样本、58 批固定回放。战斗逐帧叶节点为 665，物品逐帧为 325，仍优先检查遍历成本。[当前版采样](../output/_v1110/native_perf50/cycles04/symbol_atomic_profile.json)

数组变更计数构建记录到 386,704 次角色计时器阶段和 3,811,229 次受监测变更。只有 143,948 次阶段与同角色上次阶段的数组版本相同，占 37.2%。探针覆盖数组成员修改、清空、洗牌、排序回调及四类通用属性写入；直接生成字段赋值未计入。计数构建逐场终局和完整结果哈希与固定 200 场相同。以全局数组版本维持索引需要频繁重建，本轮未实施。[计数](../output/_v1110/native_perf50/cycles05/timer_index_counts.json) · [计数脚本](../output/_v1110/probe_native_timer_index.py)

另一独立计数构建记录真实 `CoreTimer::tick` 683,532 次，其中 493,011 次处于停止状态，占 72.1%；全部停止标志为布尔值。190,521 次活动调用的上下文均为确切 `CoreContext`，仅 43 次等待首次生效帧。计数构建仍保持固定输入和完整结果哈希。[计时器分支计数](../output/_v1110/native_perf50/cycles05/timer_tick_counts.json)

候选保留数组遍历、长度快照及原位置的状态读取，对确切 CoreTimer 的停止分支提前返回，活动分支直接调用相同方法。计时器方法对确切 CoreContext 直接读取同一 epoch 字段，其余接收器及上下文保留原通用派发。减法、首次生效判断、超时调用和浮点选项保持原实现。[候选生成](../output/_v1110/optimize_native_timer_dispatch.py)

原版及候选均通过 C++ 定向测试，覆盖同帧启动、停用、重启、首次生效、追加、替换后续条目、超时回调、非布尔真值及其他上下文的可观察属性读取。候选另通过三场原版严格逐事件回放。[测试源码](../output/_v1110/test_native_timer_dispatch.cpp) · [基线测试](../output/_v1110/native_perf50/cycles05/timer_baseline_test.json) · [候选测试](../output/_v1110/native_perf50/cycles05/timer_native_test.json) · [三场回放](../output/_v1110/native_perf50/cycles05/timer_native_target/summary.json)

两轮各 8 组 AB／BA，均先对两版交替预热至少 20 秒，每次预热和测速仍使用固定 200 场并验证完整结果哈希。CPU 耗时分别增加 **4.03%**、**0.98%**，墙钟分别增加 **4.57%**、**1.33%**，本轮排除。没有进入全量发布门槛，运行时保持第四轮版本。下一轮独立检验物品热字段布局。[首测](../output/_v1110/native_perf50/cycles05/timer_native_ab.json) · [反转复测](../output/_v1110/native_perf50/cycles05/timer_native_ab_repeat.json)


### 第六轮（保持第四轮 DLL，修复构建依赖）

基线仍为 `1291ef1b…`，远端备份为 `f5763a7d`。字段布局候选只改 CoreItem 头文件，保留全部函数体和浮点选项，对 20 个依赖编译单元全量重建并重采样 PGO。11 个热字段的地址跨度由 1,536 字节缩至 264 字节，CoreItem 大小保持 1,696 字节、派生 Item 保持 3,856 字节。生成脚本校验 69 个字段集合和 GdVal 纯默认初始化。[布局脚本](../output/_v1110/optimize_native_item_layout.py) · [布局实测](../output/_v1110/native_perf50/cycles06/item_layout_offsets.json)

用 Git 原始对象逐字节核对了 699 份基线源码及构建文件。初次 `git archive` 导出触发换行转换，后改用 `git cat-file --batch` 校验原始对象。候选已用新头文件重新编译并通过计时器同帧行为测试，另通过三场严格原版回放，22 个 C ABI 符号保持一致。[基线源码哈希](../output/_v1110/native_perf50/cycles06/item_layout_baseline_archive.json) · [同帧测试](../output/_v1110/native_perf50/cycles06/item_layout_timer_test.json) · [三场回放](../output/_v1110/native_perf50/cycles06/item_layout_target/summary.json) · [C ABI](../output/_v1110/native_perf50/cycles06/item_layout_abi.json)

同一 DLL 的复制件在同进程 A/A 中，CPU／墙钟成对中位差分别为 −3.35%／−3.53%。新增进程隔离比较，每个进程仅载入一个 DLL，每次只测一个工作进程，固定输入和完整结果哈希不变。首两组隔离 A/A 的 CPU 差值为 −1.96%、4.51%，仍有后台波动。[同进程控制](../output/_v1110/native_perf50/cycles06/control_aa.json) · [隔离控制](../output/_v1110/native_perf50/cycles06/control_aa_isolated.json) · [反转控制](../output/_v1110/native_perf50/cycles06/control_aa_isolated_repeat.json)

为减少启动瞬态及计时中的报告写盘，隔离工具改为默认交替预热 60 秒，整组结束后才写 JSON，仍保持八组 AB／BA。记录正常优先级、进程启动顺序、CPU 亲和性和两个独立 PID。两组相同 DLL 的控制 CPU 差值为 0.64%、−0.71%，墙钟为 0.93%、−0.67%。这些是控制波动，不表示相同代码存在提速。[比较工具](../output/_v1110/compare_native_isolated.py) · [控制一](../output/_v1110/native_perf50/cycles06/control_aa_deferred_warm.json) · [控制二](../output/_v1110/native_perf50/cycles06/control_aa_deferred_warm_repeat.json)

字段布局在原 20 秒预热流程下首测 CPU 下降 1.95%、墙钟下降 2.17%。改进测量流程后的两组 CPU 降幅为 **−0.31%、1.02%**，墙钟为 **0.19%、0.17%**，没有显示可重复收益。本轮排除字段布局，未进入全量发布门槛，DLL 维持第四轮版本。[初测](../output/_v1110/native_perf50/cycles06/item_layout_ab.json) · [稳态对照](../output/_v1110/native_perf50/cycles06/item_layout_ab_steady.json) · [反转复测](../output/_v1110/native_perf50/cycles06/item_layout_ab_steady_repeat.json)

同时复现并修复真实构建缺陷。旧 Windows 构建只跟踪四个公共头文件，生成类头改动后仍复用对象文件。真实小型 DLL 实验在头文件调整字段顺序后仍返回旧偏移 4；补齐生成类头依赖后会重新编译，返回正确偏移 0，C++ 源文件未变。该构建脚本修复已应用，698 份 C++／头文件与已验收版逐字节一致，运行时 DLL 哈希保持不变。[修复脚本](../output/_v1110/optimize_native_header_dependencies.py) · [真实编译测试](../output/_v1110/test_native_header_dependencies.py) · [测试结果](../output/_v1110/native_perf50/cycles06/header_dependency_test.json) · [构建支持更新](../output/_v1110/native_perf50/cycles06/build_support_installation.json)


### 第七轮

基线仍为第四轮 `1291ef1b…`，源码及 DLL 已备份至远端 `c5101b34`。沿用该版本 6,035 个有效栈样本；第五、六轮未替换 DLL，因此采样仍对应当前运行版本。

独立重试物品行为白名单常量比较。两处九元素临时数组成员查询改为同顺序的固定字符串比较，保留其他派发；22 个 C ABI 符号相同，三场原版严格逐事件回放通过。两轮各八组进程隔离 AB／BA，均先交替预热至少 60 秒。CPU 耗时分别增加 **1.01%、0.01%**，墙钟增加 **1.30%、0.14%**，不部署该候选。[首测](../output/_v1110/native_perf50/cycles07/behavior_constants_ab.json) · [反转复测](../output/_v1110/native_perf50/cycles07/behavior_constants_ab_repeat.json) · [ABI](../output/_v1110/native_perf50/cycles07/behavior_constants_abi.json) · [三场回放](../output/_v1110/native_perf50/cycles07/behavior_constants_target/summary.json)

最终采用原生空快照的参数准备省略。CoreCombatLog 每次创建事件时原本还会创建双角色临时数组、读取角色及 Stamina 类型，再调用两次角色快照。NativeBattleHooks 为 final，除 logEvent 外均调用 CoreHooks；角色快照方法仅复制参数并返回空值，在普通和调试模式均无效果。仅确切 CoreContext 加确切 NativeBattleHooks 命中快速路径，使用 RTTI 地址比较，保留事件创建、编号、参数、来源、时间、日志和 RNG。其他类型继续执行原路径；特意保留动态 logEvent 与角色快照 ID 冲突时的回退。生成脚本校验相关方法及属性读取实现，重复应用字节不变，并已接入重建入口。[生成脚本](../output/_v1110/optimize_native_noop_snapshots.py)

原版与候选均通过定向 C++ 测试，覆盖继承相同元数据但重写回调的自定义钩子、第一次快照回调中替换钩子，以及上下文属性读取次数与顺序。22 个 C ABI 不变，三场原版严格逐事件回放通过。[测试源码](../output/_v1110/test_native_noop_snapshots.cpp) · [基线测试](../output/_v1110/native_perf50/cycles07/snapshot_baseline_test.json) · [候选测试](../output/_v1110/native_perf50/cycles07/snapshot_candidate_test.json) · [ABI 与幂等性](../output/_v1110/native_perf50/cycles07/noop_snapshots_abi.json)

三轮各八组隔离 AB／BA，CPU 耗时降幅分别为 **4.61%、1.63%、1.78%**，墙钟为 **4.45%、0.99%、3.84%**。合计 24 对中位数 CPU 下降 **1.88%**、墙钟下降 **2.69%**，CPU 胜出 17 对。第三组存在较大背景波动，所有样本均保留，未按速度筛选。[首测](../output/_v1110/native_perf50/cycles07/noop_snapshots_ab.json) · [反转复测](../output/_v1110/native_perf50/cycles07/noop_snapshots_ab_repeat.json) · [确认](../output/_v1110/native_perf50/cycles07/noop_snapshots_ab_confirm.json) · [汇总](../output/_v1110/native_perf50/cycles07/noop_snapshots_ab_pooled.json)

914 + 1,690 场原版严格逐事件验收全部通过，逐场 C++ 事件哈希全部一致。接电、自然后台负载 **10.0%–23.0%** 下连续 24 批，原始吞吐中位数 **81.42 场/秒**、最慢 **75.45 场/秒**，全部达到 50 场/秒门槛。本组负载覆盖 20%，拟合值为 **80.73 场/秒**；分组留出误差中位数 1.79%，第 90 百分位 4.11%。绝对吞吐低于历史不同时间的采样，现有负载拟合无法消除频率、温度及其他未测条件的影响，本轮代码收益以同轮配对对照为依据。100／125 换算目标尚未达到。[全量验收](../output/_v1110/native_perf50/cycles07/noop_snapshots_full_gate.json) · [事件哈希](../output/_v1110/native_perf50/cycles07/noop_snapshots_event_hashes.json) · [24 批吞吐](../output/_v1110/native_perf50/cycles07/noop_snapshots_serial.json) · [20% 换算](../output/_v1110/native_perf50/cycles07/noop_snapshots_load20.json)

已部署 DLL `9ffe3242ea2d2996b19ddda6ddc6f269afca4c5439b858059b03e029c03f1899`。正常训练评估 12 场无错误，另 12 场固定种子结果与基线一致；部署 DLL、验收报告和运行时清单的 SHA-256 匹配，源码与受测副本相同。旧版保留于 `dist/native_1_1_10_before_cycle07`。继续从新部署版重采样，下一轮优先量化整数键字典的直接定位机会。[部署记录](../output/_v1110/native_perf50/cycles07/noop_snapshots_installation.json)


### 第八轮（未替换运行时）

起点为第七轮 `9ffe3242…`，远端备份 `d9ff738b`。新采样取得 6,064 个有效栈样本、38 批固定回放。字典写入、查找、哈希分别有 83、60、28 个叶节点样本，索引读取也仍频繁出现。[新版本采样](../output/_v1110/native_perf50/cycles07/noop_snapshots_profile.json)

在固定输入打包后重置计数，200 场 C++ 装配、推进和导出共记录 2,490,270 次字典读取，其中 1,846,017 次整数键、1,151,574 次整数键恰好等于对应下标保存的整数键，占全部读取 46.2%。所有查找含写入共 6,424,063 次，满足相同下标与哈希条件为 1,267,823 次，故候选仅优化读取。诊断构建终局和完整结果哈希相同。[计数](../output/_v1110/native_perf50/cycles08/dict_indices_counts.json) · [计数脚本](../output/_v1110/probe_native_dict_indices.py)

候选仅修改 GdDict::get：整数键转无符号后在 len 内，且该位置存储的键为相同整数时直接返回值，其余执行原查找。没有新增状态或修改布局。原版和候选均通过扩容、删除重插入及顺序、默认值、复制、清空、混合键、布尔／浮点等价键、超大整数、NaN 和显式错误哈希的测试；候选三场原版严格回放通过，22 个 C ABI 保持一致，生成脚本幂等。[候选脚本](../output/_v1110/optimize_native_dict_indices.py) · [测试源码](../output/_v1110/test_native_dict_indices.cpp) · [基线测试](../output/_v1110/native_perf50/cycles08/dict_baseline_test.json) · [候选测试](../output/_v1110/native_perf50/cycles08/dict_candidate_test.json) · [ABI](../output/_v1110/native_perf50/cycles08/dict_indices_abi.json)

三轮各八组隔离 AB／BA，CPU 耗时降幅为 **0.61%、4.83%、−3.40%**，墙钟为 **1.26%、4.55%、−3.56%**。未取得方向一致的可重复收益，本轮排除；不进入全量发布门槛，运行时保持第七轮。下一轮检查 Buff 按层数循环为整数迭代分配临时数组的成本，必须保留进入循环时的次数快照及每次回调／RNG 顺序。[首测](../output/_v1110/native_perf50/cycles08/dict_indices_ab.json) · [反转复测](../output/_v1110/native_perf50/cycles08/dict_indices_ab_repeat.json) · [确认](../output/_v1110/native_perf50/cycles08/dict_indices_ab_confirm.json)


### 第九轮（未替换运行时）

基线仍为第七轮 `9ffe3242…`，远端备份 `45ecf1a4`。先对 Buff 抵抗、放大、反射的三个整数循环计数，分别调用 8,351／13,295／6,659 次，共构造 51,411 个整数元素，仅约 1.18 MiB 数据。未直接采用该局部候选。[Buff 计数](../output/_v1110/native_perf50/cycles09/buff_ranges_counts.json) · [基线快照／RNG 测试](../output/_v1110/native_perf50/cycles09/range_baseline_test.json)

补充全局整数迭代调用点计数，共 131,502 次、481,464 个整数元素。最高为 CoreItem::getNextFreeLabelPosition：78,937 次，占调用 60.0%，394,685 个元素占 82.0%。诊断 DLL 的固定输入、终局及完整结果哈希不变。符号解析初次读取了 Windows 已重定位的内存 PE 基址，后改为读取磁盘 PE 头的首选基址，重新运行验证计数和调用 RVA 相同，仅修正函数名映射。[全局计数](../output/_v1110/native_perf50/cycles09/range_sites_counts_resolved.json) · [计数器](../output/_v1110/probe_native_range_sites.py)

正式候选只优化浮字位置循环，仍先调用原 size() 一次，再对不超过 UINT32_MAX 的整数返回值直接产生索引，长度保持进入循环时的快照；非整数及超大整数仍调用原 gd_iter_seq。时间读取、时间戳更新、提前返回、随机调用和浮点表达式保持原代码。生成脚本校验完整方法及整数迭代实现，重复应用字节不变。[候选生成](../output/_v1110/optimize_native_label_ranges.py) · [范围转换工具](../output/_v1110/optimize_native_integer_ranges.py)

原版及候选均通过定向测试：首个／后续空位、全占用、空数组、回调追加元素不扩大遍历、修改后续值立即可见、替换数组、字典及空值输入，并核对属性读取次数、character 回调、诊断调用及两次随机调用的范围与顺序。三场原版严格回放通过，22 个 C ABI 保持一致。[测试源码](../output/_v1110/test_native_label_ranges.cpp) · [基线测试](../output/_v1110/native_perf50/cycles09/label_baseline_test.json) · [候选测试](../output/_v1110/native_perf50/cycles09/label_candidate_test.json) · [ABI](../output/_v1110/native_perf50/cycles09/label_ranges_abi.json)

三轮各八组隔离 AB／BA，CPU 耗时降幅为 **2.56%、−0.64%、0.35%**，墙钟为 **0.87%、0.36%、0.07%**。后两轮没有重复首轮收益，因此排除，不进入全量发布门槛，运行时仍为第七轮。下一轮依据现有指令采样检查逐帧遍历的内存读取路径；当前 CoreItem 冷却推进本身已经使用原生数值计算，避免重复改写已优化逻辑。[首测](../output/_v1110/native_perf50/cycles09/label_ranges_ab.json) · [反转复测](../output/_v1110/native_perf50/cycles09/label_ranges_ab_repeat.json) · [确认](../output/_v1110/native_perf50/cycles09/label_ranges_ab_confirm.json)


### 第十轮（未替换运行时）

基线仍为第七轮 `9ffe3242…`，远端备份 `bd73c3a5`。对现有指令采样逐条核对反汇编，命中计时器数组指针与长度、宝石数组长度，以及冷却状态的类型分派。采样位置只能支持访存假设，不能代替缓存未命中计数。[反汇编核对](../output/_v1110/native_perf50/cycles10/combat_hot_disassembly.txt)

候选仅在角色计时器遍历中预取后方两个物品的计时器与宝石字段地址，不提前解引用后续对象，不复用预取时的值。由有效当前物品计算字段偏移，未来位置同时受捕获长度和实时长度约束；实际遍历仍重新读取数组条目和字段。GCC 对预取目标的无故障保证不免除地址表达式本身合法的要求。[GCC 说明](https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html) · [候选脚本](../output/_v1110/optimize_native_item_prefetch.py)

基线及候选均通过回调定向测试，覆盖先放无效占位地址、由前序回调修复后才真正访问，替换后续条目，追加，停用后续计时器，整体替换数组，同帧加入宝石，以及缩短数组后仍遵循捕获长度。三场原版严格回放通过，22 个 C ABI 不变，重复生成字节不变。[测试源码](../output/_v1110/test_native_item_prefetch.cpp) · [基线测试](../output/_v1110/native_perf50/cycles10/prefetch_baseline_test.json) · [候选测试](../output/_v1110/native_perf50/cycles10/prefetch_candidate_test.json) · [ABI](../output/_v1110/native_perf50/cycles10/item_prefetch_abi.json)

两轮各八组隔离 AB／BA，CPU 耗时分别增加 **5.31%、3.00%**，墙钟增加 **5.09%、3.17%**。本轮排除，不进入全量发布门槛，运行时保持第七轮。下一轮先备份已验收源码与 DLL，再检验原生物品计时器数组头与物品存储相邻的局部方案；不改战斗步骤、回调、RNG 或浮点计算，需专门验证数组别名、重复初始化及生命周期。[首测](../output/_v1110/native_perf50/cycles10/item_prefetch_ab.json) · [反转复测](../output/_v1110/native_perf50/cycles10/item_prefetch_ab_repeat.json)


### 第十一轮

开始结构改动前，已提交并推送当前已验收版至 `bc5082fd`，用 Git 原始对象逐字节核对 698 份 C++／头文件、构建脚本及 DLL 共 700 份文件，DLL 为第七轮 `9ffe3242…`。[备份核对](../output/_v1110/native_perf50/cycles11/verified_baseline.json)

采用原生物品首个计时器数组头与物品相邻的布局。仅桥接内部启用的战斗上下文、且物品存储属于该战斗 arena 时使用对象内的首个空数组头；其他上下文及栈对象保持独立 arena 数组头。桥接内部物品随整个战斗内存区存活，未改战斗推进、回调、RNG 和浮点表达式。对象内数组头一旦用过便不再复用，重复初始化继续分配新头，保留旧别名。重建入口已接入该生成步骤，重复应用保持源码字节及修改时间不变。[生成脚本](../output/_v1110/optimize_native_inline_timers.py)

CoreItem 从 1,696 字节、8 字节对齐改为 1,792 字节、64 字节对齐；`Gd__gd_core__Item` 从 3,832 改为 3,904 字节。计时器 GdVal 位于偏移 1,600，内置头位于 1,624，长度字段位于 1,632，处于同一 64 字节行。新布局要求更高分配对齐，候选据实际块基址计算高对齐偏移，普通对齐继续使用原快速路径。8–256 字节对齐、跨块、重置复用和存储归属专测通过：旧分配器对新对齐请求出现 73 处错位，候选为 0。[基线布局／分配探针](../output/_v1110/native_perf50/cycles11/arena_baseline_test.json) · [候选布局／分配测试](../output/_v1110/native_perf50/cycles11/arena_candidate_test.json)

已对 20 个依赖单元全量重建，并重新收集全部 18 个热点单元的 PGO 数据，保持浮点选项。所有 C++ 定向测试均以候选头文件重新编译，覆盖外部对象析构后的数组引用、原生数组身份与缓存行、重复初始化、复制／移动、跨 arena 初始化、同帧新增后续计时器，以及此前的计时器首次生效、启动／停用／重启、追加／替换、自定义上下文和钩子回退。三场原版严格回放通过，22 个 C ABI 相同。[别名测试源码](../output/_v1110/test_native_inline_timers.cpp) · [候选测试](../output/_v1110/native_perf50/cycles11/inline_candidate_test.json) · [计时器回归](../output/_v1110/native_perf50/cycles11/timer_regression_test.json) · [遍历回归](../output/_v1110/native_perf50/cycles11/traversal_regression_test.json) · [快照回归](../output/_v1110/native_perf50/cycles11/snapshot_regression_test.json) · [ABI](../output/_v1110/native_perf50/cycles11/inline_timers_abi.json)

三轮各八组隔离 AB／BA，CPU 耗时降幅为 **2.69%、2.59%、1.01%**，墙钟为 **2.31%、3.51%、0.79%**。合计 24 对中位数 CPU 下降 **1.63%**、墙钟下降 **2.08%**，所有波动样本保留。[首测](../output/_v1110/native_perf50/cycles11/inline_timers_ab.json) · [反转复测](../output/_v1110/native_perf50/cycles11/inline_timers_ab_repeat.json) · [确认](../output/_v1110/native_perf50/cycles11/inline_timers_ab_confirm.json) · [汇总](../output/_v1110/native_perf50/cycles11/inline_timers_ab_pooled.json)

914 + 1,690 场严格逐事件验收全部通过，逐场 C++ 事件哈希全部一致。接电、自然后台负载 **9.7%–19.5%** 下连续 24 批，吞吐中位数 **87.86 场/秒**、最慢 **79.35 场/秒**。自然范围不含 20%，拒绝外推并补充相同设置的受控负载校准。[全量验收](../output/_v1110/native_perf50/cycles11/inline_timers_full_gate.json) · [事件哈希](../output/_v1110/native_perf50/cycles11/inline_timers_event_hashes.json) · [正式吞吐](../output/_v1110/native_perf50/cycles11/inline_timers_serial.json) · [自然样本拒绝外推](../output/_v1110/native_perf50/cycles11/inline_timers_natural_load20_rejected.json)

补充校准采用 30 秒预热、两个低优先级负载进程，整个采样在 120 秒进程上限内完成。接电、估算负载 **16.0%–41.7%**，24 批原始吞吐中位数 **77.49**、最慢 **61.56 场/秒**，全部高于门槛。20% 换算 **79.71 场/秒**，分组留出误差中位数 **1.83%**、第 90 百分位 **4.83%**。换算只解释这组条件下的负载波动，100／125 目标继续推进。[受控采样](../output/_v1110/native_perf50/cycles11/inline_timers_load_calibration_warm.json) · [20% 换算](../output/_v1110/native_perf50/cycles11/inline_timers_load20_warm.json)

已部署 DLL `58383a1158e951d7aae8b4d4c34df4d52332446156946d31a488f5dff323ec39`。正常训练 12 场无错误，另 12 场固定种子结果与基线一致，部署清单、验收报告及 DLL SHA-256 相同，源码与受测副本一致。旧版保留于 `dist/native_1_1_10_before_cycle11`。下一轮从该版重新采样，先计数仅针对物品／宝石／计时器相关数组的变更与可跳过条目，再评估保持原顺序、同帧变更后回退原遍历的稀疏计时器路径。[部署记录](../output/_v1110/native_perf50/cycles11/inline_timers_installation.json)


### 第十二轮（未替换运行时）

起点为第十一轮 `58383a11…`，远端备份 `8ada702c` 的原始 DLL 与本地逐字节相同。新采样取得 **6,038** 个有效栈样本、43 批固定回放；CoreCombat.physicsTick 仍有 644 个叶节点样本，CoreItem.physicsTick 为 344。先诊断相关数组，正式候选采用独立副本，未改变正在运行的 DLL。[备份核对](../output/_v1110/native_perf50/cycles12/verified_baseline.json) · [新采样](../output/_v1110/native_perf50/cycles11/inline_timers_profile.json)

固定 200 场记录 **386,704** 次角色计时器阶段、**13,473,218** 次物品访问，其中自身或宝石带非空计时器数组的物品访问 **682,897** 次，占 **5.07%**。仅追踪物品、宝石、计时器相关数组后，前后阶段 epoch 可复用 **386,104** 次，占 **99.84%**；这批语料中未观察到遍历中途相关数组变更。记录 1,619 次相关数组修改入口和 45,199 次相关字段赋值，修改入口包含空操作及嵌套调用，不等于独立语义修改次数。诊断完整结果哈希相同，不用其吞吐作收益结论。[诊断脚本](../output/_v1110/probe_native_selective_timer_scan.py) · [计数](../output/_v1110/native_perf50/cycles12/selective_timer_counts.json)

原型为每个角色缓存升序物理下标，仅跳过自身和所有宝石计时器数组均为空的物品。停止状态的计时器仍保留；数组别名修改及字段替换均使索引失效。中途变更后，从已访问位置的下一项恢复原顺序扫描，保留最初捕获长度。嵌套阶段或排序回调期间直接使用原路径，epoch 饱和后永久回退。仅桥接内部启用，外部上下文保留原行为。GdArr 使用既有填充区标记，sizeof 仍为 24；由于构造语义及角色缓存布局变化，对全部 20 个依赖单元全量重建并重新训练 18 个热点单元，浮点选项不变。[原型生成脚本](../output/_v1110/optimize_native_sparse_timers.py) · [设计与不变量](../output/_v1110/native_perf50/cycles12/sparse_timer_design.json)

24 组索引／原顺序扫描对照和 21 组饱和回退用例均通过，覆盖别名、同帧新增／替换、数组重排／缩短、未来占位对象修复、嵌套及排序回调。数组所有修改入口、清空、洗牌 RNG、排序、字段替换测试通过；此前计时器启动／停止／重启、首次生效及数组别名生命周期回归也通过。三场原版严格逐事件检查通过，22 个 C ABI 不变。重复生成保持字节及修改时间。[对照测试源码](../output/_v1110/test_native_sparse_timers.cpp) · [对照结果](../output/_v1110/native_perf50/cycles12/sparse_differential_test.json) · [数组追踪测试](../output/_v1110/native_perf50/cycles12/tracking_test.json) · [ABI](../output/_v1110/native_perf50/cycles12/sparse_timers_abi.json)

三轮各八组隔离 AB／BA，CPU 耗时降幅 **−3.21%、2.69%、2.07%**，墙钟降幅 **−1.27%、0.12%、1.14%**。合计 24 对全部保留，CPU 中位数仅降低 **0.73%**，墙钟 **0.89%**，未取得方向一致的可重复收益，故不合入。没有进入 2,604 场和 24 批发布门槛，运行时保持第十一轮；原型未接入默认重建流程。反汇编确认普通数组 push_back 的追踪判断已内联，未发现每次空追踪都无条件进入 TLS 的额外调用，不能把收益不足直接归因于该猜测。下一轮单独计数更热的冷却物品遍历，核对资格变化与同帧回调后再选择实现。[首测](../output/_v1110/native_perf50/cycles12/sparse_timers_ab.json) · [反转复测](../output/_v1110/native_perf50/cycles12/sparse_timers_ab_repeat.json) · [确认](../output/_v1110/native_perf50/cycles12/sparse_timers_ab_confirm.json) · [汇总](../output/_v1110/native_perf50/cycles12/sparse_timers_ab_pooled.json) · [未部署记录](../output/_v1110/native_perf50/cycles12/sparse_timers_installation.json)


### 第十三轮（未替换运行时，修复构建依赖）

基线仍为第十一轮 `58383a11…`，远端备份 `5352d59b`。继续诊断冷却物品遍历：固定 200 场共 386,704 个角色阶段、13,473,218 次物品访问，父物品或宝石活跃的访问为 3,635,044 次，占 **26.98%**；自身活跃 3,633,565 次。相关数组和冷却状态的组合 epoch 可复用 **99.51%**，遍历中途相关修改 **760** 次。冷却字段赋值 35,007 次，其中类型改变或布尔变化 23,435 次，语料未出现非布尔冷却状态。已核对全部四处赋值及两段循环，诊断完整结果哈希相同。[诊断脚本](../output/_v1110/probe_native_cooldown_scan.py) · [计数](../output/_v1110/native_perf50/cycles13/cooldown_counts.json)

独立候选仅对冷却遍历建立父物品下标索引，保留两段原始处理体，缓存追加在 CoreCombat 字段末尾，不改变角色现有字段布局。只跳过布尔 false 且所有非空宝石同样布尔 false 的物品，未知种类或非原生对象保守保留。相关数组别名及四处冷却状态变化均失效索引；同帧变更从当前位置下一项转为原顺序扫描，保留原捕获长度和数组引用。嵌套、排序回调和 epoch 饱和使用原路径。仅原生桥接内部启用，对全部 20 个依赖单元重新构建、18 个热点单元重新采集 PGO，浮点选项不变。[原型脚本](../output/_v1110/optimize_native_sparse_cooldowns.py)

正式候选通过 28 组原顺序／索引对照及 28 组饱和回退用例，覆盖激活、停用及重启后续物品，同帧宝石变化，数组修改／替换／缩短，未来占位修复，嵌套及排序回调，非布尔值，以及回调重置缓存。所有数组修改入口和洗牌 RNG 测试、此前的计时器及别名生命周期回归均通过，三场原版严格逐事件检查通过，22 个 C ABI 不变。[对照源码](../output/_v1110/test_native_sparse_cooldowns.cpp) · [对照结果](../output/_v1110/native_perf50/cycles13/cooldown_differential_test.json) · [数组／字段追踪测试](../output/_v1110/native_perf50/cycles13/cooldown_tracking_test.json) · [ABI](../output/_v1110/native_perf50/cycles13/sparse_cooldowns_v2_abi.json)

三轮各八组隔离 AB／BA，CPU 降幅 **−3.85%、7.65%、1.27%**，墙钟 **−3.01%、7.76%、1.85%**。保留全部 24 对后，CPU **−0.006%**、墙钟 **−0.032%**，没有净收益，故不合入，也未进入 2,604 场及 24 批发布门槛。[首测](../output/_v1110/native_perf50/cycles13/sparse_cooldowns_v2_ab.json) · [反转复测](../output/_v1110/native_perf50/cycles13/sparse_cooldowns_v2_ab_repeat.json) · [确认](../output/_v1110/native_perf50/cycles13/sparse_cooldowns_v2_ab_confirm.json) · [汇总](../output/_v1110/native_perf50/cycles13/sparse_cooldowns_v2_ab_pooled.json)

为检查调度噪声，测速工具增加可选 `--logical-cpu`，默认行为保持原设置。先以相同 DLL 固定到逻辑核 6 做独立 A/A：两臂实测掩码均为 `[6]`，CPU 成对差异范围仍达 **−50.67% 至 26.61%**，未得到稳定控制条件，因此没有据此补做候选收益测试，也未用它修正、替换或筛除原 A/B 结果。硬件为本地读取的 i5-8265U、4 核 8 线程。该实验进一步说明单一后台占用拟合无法消除全部运行条件差异。[同核 A/A](../output/_v1110/native_perf50/cycles13/pinned_aa.json) · [测速工具](../output/_v1110/compare_native_isolated.py)

单独保留构建依赖修复：旧脚本固定追踪两个根目录头文件，新增辅助头文件会漏编；改为追踪根目录全部 `.hpp`，其余编译及链接选项相同。用真实编译器和五个编译单元复现：首次 DLL 字段偏移 4，修改新头文件后旧脚本编译 0/5、仍读到 4；修复后编译 5/5、读到 0，C++ 源码未改。当前 DLL 和运行时没有替换。两个索引原型均未接入默认重建流程；下一轮转向分配器常见路径及慢路径代码体积，继续保持分配次序、对齐、回调、RNG 和浮点运算。[构建修复脚本](../output/_v1110/optimize_native_root_header_dependencies.py) · [真实 DLL 测试](../output/_v1110/native_perf50/cycles13/root_header_dependency_test.json) · [本轮记录](../output/_v1110/native_perf50/cycles13/sparse_cooldowns_v2_installation.json)


### 第十四轮（正确性通过，性能复测反向，未替换运行时）

起点仍为第十一轮 `58383a11…`，远端备份 `0f34bed6`。已逐字节核对远端 DLL 与本地运行时，并以 Git 原始对象核对 698 份 C++／头文件及构建脚本共 699 份源码文件。当前采样中 GdArr.from_init 有 71 个叶节点样本，build_side_items 有 880 个包含样本；本轮检验内联分配代码体积的假设，未把包含样本当作纯分配成本。[备份核对](../output/_v1110/native_perf50/cycles14/verified_baseline.json) · [起点采样](../output/_v1110/native_perf50/cycles11/inline_timers_profile.json)

候选只修改 gd_rt.hpp 中 BattleArena 的分配实现：常见无锁分配在当前块有空间时直接返回；扩块、遍历后续块和加锁路径放到不可内联的辅助函数。保留块大小、分配次序、对齐公式、零字节规则、重置复用以及异常时的锁释放；未改战斗步骤、回调、RNG 或浮点表达式。全部 20 个依赖单元重新构建，18 个热点单元重新采集 PGO。独立生成脚本有整头文件及区域散列保护，重复应用不改字节或修改时间。另准备并验证了与现有内联计时器生成步骤的组合，但因性能未通过，未接入默认重建入口。[候选脚本](../output/_v1110/optimize_native_arena_split.py) · [生成组合测试](../output/_v1110/native_perf50/cycles14/arena_split_pipeline_test.json)

基线及候选的内存区对象均为 48 字节，两者通过 12,001 次分配、同序列重置后地址逐项复用、最高 4,096 字节对齐、零字节与超块分配、内容及归属检查、8,000 次多线程分配不重叠，以及持锁分配结束后的递归构造分配测试。物品布局、计时器和别名生命周期回归、三场原版严格回放及 22 个 C ABI 检查通过。[压力测试源码](../output/_v1110/test_native_arena_split.cpp) · [基线](../output/_v1110/native_perf50/cycles14/arena_baseline_stress.json) · [候选](../output/_v1110/native_perf50/cycles14/arena_allocation_test.json) · [ABI](../output/_v1110/native_perf50/cycles14/arena_split_abi.json)

继续检查测速条件：工具增加可选静默计时，预热延长至 120 秒，保留默认调度。相同 DLL 的 A/A 仍出现 CPU 中位差异 −7.44%、成对差异绝对值中位数 12.60%，说明这些措施没有消除当前环境波动。计时边界已核对：预打包、终局检查和结果哈希在窗口外；窗口内为完整回放调用。没有用 A/A、负载拟合或样本筛除去修正候选结果。[静默 A/A](../output/_v1110/native_perf50/cycles14/quiet_aa.json)

前三轮各八组隔离 AB／BA，CPU 降幅 **2.20%、3.67%、1.48%**，墙钟 **2.06%、3.49%、−1.42%**。前三轮 24 对合计 CPU **2.20%**、墙钟 **1.69%**；第三组墙钟反向，因此在最终独立试验前记录接受条件：四组 CPU 中位数均降低，至少三组墙钟降低，合计均降低，随后仍须完整发布门槛。[前三轮汇总](../output/_v1110/native_perf50/cycles14/arena_split_ab_pooled_24.json) · [预先记录的最终判定](../output/_v1110/native_perf50/cycles14/arena_split_final_trial_policy.json)

914 + 1,690 场严格逐事件验收全部通过，逐场 C++ 事件哈希 2,604 场全部与基线一致，汇总根仍为 `b8066c92…`。随后最终独立八组反转加载顺序，CPU **增加 3.00%**、墙钟 **增加 2.73%**，未通过预先记录的条件。四轮共 32 对全部保留，不以合计中位数掩盖复测反向，故不合入；未运行发布用 24 批，不部署，默认重建及运行 DLL 保持第十一轮。下一轮检查 CoreBuff.gainTemporary 中已被强制转换为整数／布尔的局部值，减少通用值封装，继续保留所有运算、RNG 次数及回调次序。[全量验收](../output/_v1110/native_perf50/cycles14/arena_split_full_gate.json) · [事件哈希](../output/_v1110/native_perf50/cycles14/arena_split_event_hashes.json) · [最终复测](../output/_v1110/native_perf50/cycles14/arena_split_ab_final.json) · [32 对汇总](../output/_v1110/native_perf50/cycles14/arena_split_ab_pooled.json) · [未部署记录](../output/_v1110/native_perf50/cycles14/arena_split_installation.json)


### 第十五轮（未替换运行时）

仍以第十一轮 `58383a11…` 为基线，先核对远端备份 `79dbf3b2` 的 DLL 原始字节，并核对 699 份源码／构建文件。热点沿用当前运行版的 6,038 栈采样，CoreBuff.gainTemporary 包含样本仍支持对该链提出局部优化假设。[备份核对](../output/_v1110/native_perf50/cycles15/verified_baseline.json)

候选仅修改 CoreBuff.gainTemporary 的 amount、reflect 两个局部变量存储：前者入口和所有后续赋值原本均已强制转换为 Int，后者入口转换为 Bool 且后续无赋值。改为 8 字节整数／1 字节布尔局部包装，在通用 API 边界重建原类型 GdVal；保留原强制转换、数值运算辅助函数、浮点表达式、RNG 循环及全部回调次序。只简化已证明为 Int 的零值相等判断及 Bool 取反。生成脚本校验完整方法散列、转换函数实现，支持严格逆变换及字节／修改时间幂等。没有改头文件和对象布局，核对全部头文件与已验收对象缓存相同，仅重编译并重新训练改动的 shard_00，未混用布局不同的试验缓存。[候选脚本](../output/_v1110/optimize_native_buff_scalar_locals.py) · [类型约束](../output/_v1110/native_perf50/cycles15/buff_scalar_invariants.json) · [对象兼容核对](../output/_v1110/native_perf50/cycles15/buff_scalar_object_compatibility.json)

基线与候选的 441 组参数转换／临时计时器／状态／RNG 边界测试完全相同，含空值、布尔、字符串、浮点、NaN、int64 极值、分数抵抗层数、反射真假及负零时长；状态及 RNG 汇总值相同，共 130 次 RNG 调用。抵抗过程替换 RNG 对象、放大时仍按初始次数循环、反射概率同帧变化等回归通过；原有计时器和别名回归、三场原版严格逐事件检查及 22 个 C ABI 检查通过。[边界测试源码](../output/_v1110/test_native_buff_scalar_locals.cpp) · [两版边界对照](../output/_v1110/native_perf50/cycles15/buff_scalar_boundary_test.json) · [RNG 回归](../output/_v1110/native_perf50/cycles15/buff_rng_regression_test.json) · [ABI](../output/_v1110/native_perf50/cycles15/buff_scalar_locals_abi.json)

在测速前记录判定条件。两轮各八组、120 秒预热、静默隔离 AB／BA，CPU 耗时分别增加 **1.01%、1.04%**，墙钟降幅 **0.41%、−1.83%**。两轮均未减少主线程 CPU，达到预先记录的早停排除条件；保留全部 16 对，不合入，不进入 2,604 场和 24 批发布门槛，运行时保持第十一轮。下一轮从该基线重新检查高频 Buff 方法中的上下文属性读取，先明确原生调用域及上下文对象生命周期，保留外部 getter 与回调替换的可观察行为。[试验判定](../output/_v1110/native_perf50/cycles15/buff_scalar_trial_policy.json) · [首测](../output/_v1110/native_perf50/cycles15/buff_scalar_locals_ab.json) · [反转复测](../output/_v1110/native_perf50/cycles15/buff_scalar_locals_ab_repeat.json) · [汇总](../output/_v1110/native_perf50/cycles15/buff_scalar_locals_ab_pooled.json) · [未部署记录](../output/_v1110/native_perf50/cycles15/buff_scalar_locals_installation.json)


### 第十六轮（未替换运行时）

仍以第十一轮 `58383a11…` 为基线，已核对远端备份 `c7b62a28` 的 DLL 和 699 份源码／构建文件。候选仅改两个 C++ 单元：在原生回放入口建立可嵌套、异常安全的调用域，在 CoreBuff.gainTemporary 首次实际读取上下文时确认精确 CoreContext 类型；15 处属性读取改为直接读取六个当前字段。每次仍检查接收者身份，回调替换上下文后恢复原 getter，不缓存字段值，外部 C++ 调用继续原路径。未改头文件、浮点表达式、RNG 或回调顺序；重新训练两个改动单元的 PGO。[候选脚本](../output/_v1110/optimize_native_buff_context.py) · [设计约束](../output/_v1110/native_perf50/cycles16/buff_context_design.json) · [备份核对](../output/_v1110/native_perf50/cycles16/verified_baseline.json)

基线与候选 444 组转换、计时器、状态、RNG 及 getter 顺序对照相同，共 133 次 RNG 调用；覆盖 getter 内替换上下文、无效上下文在零值／上限提前返回路径不应被访问、外部自定义 getter。原有回归、三场严格逐事件检查和 22 个 C ABI 检查通过。[边界测试](../output/_v1110/native_perf50/cycles16/buff_context_boundary_test.json) · [ABI](../output/_v1110/native_perf50/cycles16/buff_context_abi.json)

两轮各八组、120 秒预热、静默隔离 AB／BA，CPU 耗时分别增加 **3.07%、0.53%**，墙钟降幅 **−2.02%、0.17%**，触发预先记录的早停排除条件。保留全部 16 对，不合入，不进入 2,604 场及 24 批发布门槛，也未接入默认生成流程。下一轮先计数冷却阶段中相同角色加速／减速层数的重复计算，核对回调之间的有效复用区间，再决定是否值得缓存。[试验条件](../output/_v1110/native_perf50/cycles16/buff_context_trial_policy.json) · [首测](../output/_v1110/native_perf50/cycles16/buff_context_ab.json) · [反转复测](../output/_v1110/native_perf50/cycles16/buff_context_ab_repeat.json) · [汇总](../output/_v1110/native_perf50/cycles16/buff_context_ab_pooled.json) · [未部署记录](../output/_v1110/native_perf50/cycles16/buff_context_installation.json)


### 第十七轮（未替换运行时）

仍以第十一轮 `58383a11…` 为基线，先核对远端 `28b2736b` 的 DLL 原始字节和 699 份源码／构建文件。固定 200 场计数共有 **3,583,917** 次正常速度计算，回调之间可复用同一角色加减速项 **3,080,447** 次，占 **85.95%**；相同倍率下可复用最终速度为 **23.32%**。所有计算仍执行，未观察到标记回调边界之间的层数或同键速度变化。计数 DLL 只用于诊断。[计数](../output/_v1110/native_perf50/cycles17/shared_speed_counts.json) · [备份核对](../output/_v1110/native_perf50/cycles17/verified_baseline.json)

候选只缓存 `double(stacks(107)-stacks(110))*0.02`，缓存放在对手／玩家各自冷却遍历的栈上，按角色身份区分。物品速度倍率、加法、分支和限幅仍逐件计算。宝石 character getter、回退 getSpeed、显示钩子和 trigger 回调前后均清空缓存，嵌套阶段使用独立栈。原生桥接显式启用，外部调用默认走无缓存实现。头文件增加内部标志并在重置时关闭，全部 20 个单元重建、18 个热点单元重新训练 PGO，浮点选项不变。逐一核对全部 674 个生成 meta 方法均仅返回常量。[实现](../output/_v1110/optimize_native_shared_speed.py) · [设计](../output/_v1110/native_perf50/cycles17/shared_speed_design.json)

基线、无缓存候选及缓存候选的 **684** 组位级状态／回调对照一致，覆盖字典顺序、替换 Buff／字典、触发、显示与宝石 getter 的嵌套调用、无角色回退、禁用、阻塞、眩晕、倍率变化、NaN 和负零。旧回归、三场严格逐事件及 22 个 C ABI 检查通过。待接入的生成流程组合已从旧版及当前版输入验证，重复应用字节和修改时间不变；因性能条件未通过，没有接入。[定向测试](../output/_v1110/native_perf50/cycles17/shared_speed_boundary_test.json) · [ABI](../output/_v1110/native_perf50/cycles17/shared_speed_abi.json) · [生成组合](../output/_v1110/native_perf50/cycles17/shared_speed_pipeline_test.json)

三轮各八组、120 秒预热、静默隔离 AB／BA，CPU 降幅 **−3.50%、2.04%、5.62%**，墙钟 **−1.97%、0.33%、3.49%**。首测反向，未满足测速前记录的各独立组方向一致条件；保留全部 24 对，不以合计中位数替代预设条件，不合入，不进入 2,604 场及 24 批发布门槛。[条件](../output/_v1110/native_perf50/cycles17/shared_speed_trial_policy.json) · [首测](../output/_v1110/native_perf50/cycles17/shared_speed_ab.json) · [复测](../output/_v1110/native_perf50/cycles17/shared_speed_ab_repeat.json) · [第三组](../output/_v1110/native_perf50/cycles17/shared_speed_ab_confirm.json) · [汇总](../output/_v1110/native_perf50/cycles17/shared_speed_ab_pooled.json) · [未部署记录](../output/_v1110/native_perf50/cycles17/shared_speed_installation.json)

采样工具新增可选完整输出，保留全部函数、直接叶节点调用者和解析后的栈。补采当前版得到 **6,124** 个有效栈、29 批固定回放；采样与低优先级编译并行，仅用于热点归属，不作吞吐成绩。字符串格式化的来源包括 addSpeed 91 个包含样本、readyInit 38 个；GdEnum::get 的来源包括角色初始化 22 个。源码显示每种 Buff 初始化会分配 EventType 的全部键，再反复按字符串找值以反查名称。下一轮优先验证该静态反向映射，可在保留未知值原路径的条件下跳过数组和重复查找；随后再评估剩余诊断参数。[完整采样](../output/_v1110/native_perf50/cycles17/baseline_profile_full.json) · [采样条件](../output/_v1110/native_perf50/cycles17/baseline_profile_conditions.json)


### 第十八轮（正确性与 A/B 通过，吞吐发布门槛未通过）

仍以部署版 `58383a11…` 为起点，先核对远端备份 `445ddf7f` 的 DLL 原始字节及 699 份源码／构建文件。完整采样指出角色初始化反复枚举 EventType 的全部键，并按字符串逐一找值以反查 Buff 名称。对已验证的 40 个常量整数值生成反向映射，保留最先出现的名称；非整数及未知整数继续原循环。保留 Buff 创建位置、外层遍历、to_lower、信号名拼接、Buff.init、RNG 与事件来源。只改 shard_02，全部头文件与已验收缓存一致，重新训练该单元的 PGO，未接入失败的冷却缓存或稀疏索引。[实现](../output/_v1110/optimize_native_reverse_stack_names.py) · [常量与语义约束](../output/_v1110/native_perf50/cycles18/reverse_stack_names_design.json) · [备份核对](../output/_v1110/native_perf50/cycles18/verified_baseline.json)

401 组查询及 9 组完整角色构造对照通过，含布尔、浮点、NaN、未知整数、极值及全部已知名称；名称、对象 ID、RNG 汇总与基线相同。旧回归、三场严格逐事件、22 个 C ABI 检查通过。三轮各八组隔离 AB／BA，CPU 降幅 **1.94%、4.51%、8.75%**，墙钟 **0.66%、7.07%、11.43%**，满足测速前记录的条件。全部 24 对合计 CPU 中位降幅 **5.21%**、墙钟 **5.82%**，两项均 18/24 对降低；第三组波动较大，原始极端样本全部保留，合计值不代表固定条件下的精确收益。[定向对照](../output/_v1110/native_perf50/cycles18/reverse_stack_names_boundary_test.json) · [判定条件](../output/_v1110/native_perf50/cycles18/reverse_stack_names_trial_policy.json) · [A/B 汇总](../output/_v1110/native_perf50/cycles18/reverse_stack_names_ab_pooled.json)

914 + 1,690 场原版严格逐事件验收全部通过，2,604 场 C++ 事件哈希全部与部署版相同，汇总根仍为 `b8066c92…`。[全量验收](../output/_v1110/native_perf50/cycles18/reverse_stack_names_full_gate.json) · [事件哈希](../output/_v1110/native_perf50/cycles18/reverse_stack_names_event_hashes.json)

随后连续 24 批原始吞吐 **未通过发布条件**：中位数 **62.59 场/秒**、最慢 **43.40 场/秒**。供电全程接电，估算后台负载 **20.9%–52.8%**，最慢为第一批，负载 52.8%、主线程 CPU 3.828 秒、墙钟 4.608 秒。所有终局及完整结果哈希仍相同。由于每一批至少 50 场/秒的门槛未通过，没有部署、没有接入默认生成流程，当前运行 DLL 仍为 `58383a11…`；不丢弃首批，也不重复同一候选测试直到通过。20% 超出观测范围，拟合工具明确拒绝外推。保留此版本作为已通过语义和 A/B 的独立实验基线，后续候选仍须独立验证并重新通过全部发布门槛。[原始 24 批](../output/_v1110/native_perf50/cycles18/reverse_stack_names_serial.json) · [拒绝外推](../output/_v1110/native_perf50/cycles18/reverse_stack_names_load20_rejected.json) · [未部署记录](../output/_v1110/native_perf50/cycles18/reverse_stack_names_installation.json)


### 第十九轮（淘汰链接优化选项，保留构建缓存修复）

先核对远端备份 `76847e3b`：第十八轮隔离候选 DLL `7213d946…` 的原始字节已备份，699 份源码／构建文件通过 Git 原始对象逐一核对，角色单元使用该候选已备份的源码，其余沿用已验收源码。部署版仍为 `58383a11…`。本轮以第十八轮候选为实验基线，仅新增 GCC 的 `-fdevirtualize-at-ltrans`，全部 C++／头文件字节相同，保留浮点设置。全部 20 个单元重建、18 个热点单元重新训练 PGO；本地查询该选项默认关闭，GCC 文档说明它会为链接阶段的去虚拟化传递额外信息。[构建与备份核对](../output/_v1110/native_perf50/cycles19/ltrans_devirt_baseline_archive.json) · [配置](../output/_v1110/native_perf50/cycles19/ltrans_devirt_design.json) · [GCC 16.1 文档](https://gcc.gnu.org/onlinedocs/gcc-16.1.0/gcc/Optimize-Options.html#index-fdevirtualize-at-ltrans)

候选通过全部旧回归，含外部自定义上下文、共享基础 metadata 的钩子、回调替换及同帧变更；401 组查询、9 组完整构造、三场严格逐事件和 22 个 C ABI 检查通过。[定向结果](../output/_v1110/native_perf50/cycles19/ltrans_devirt_boundary_test.json) · [ABI](../output/_v1110/native_perf50/cycles19/ltrans_devirt_abi.json)

两轮各八组、120 秒预热、静默隔离 AB／BA，CPU 耗时增加 **0.54%、12.44%**，墙钟增加 **1.22%、14.18%**；第二组全部 8 对更慢。达到预先记录的早停排除条件，保留全部 16 对，不合入该选项，不运行后续累计对照、2,604 场及 24 批发布门槛，也不启用第十八轮尚未通过发布门槛的运行 DLL。[判定条件](../output/_v1110/native_perf50/cycles19/ltrans_devirt_trial_policy.json) · [首测](../output/_v1110/native_perf50/cycles19/ltrans_devirt_ab.json) · [反转复测](../output/_v1110/native_perf50/cycles19/ltrans_devirt_ab_repeat.json) · [汇总](../output/_v1110/native_perf50/cycles19/ltrans_devirt_ab_pooled.json)

单独修复 Windows 构建脚本未追踪自身配置修改的问题：将 build_windows.py 本身列为对象依赖，脚本内编译参数变化后重新编译。真实编译器与五个单元复现，仅改宏参数时旧脚本编译 0/5、仍返回旧值 0；修复后编译 5/5、返回 1；未改动再编译 0/5，随后再次仅改参数则编译 5/5、返回 2，C++ 源码始终未改。生产修复单独提取、复验，已接入默认性能重建流程，字节和修改时间幂等。698 份 C++／头文件及现有 DLL 均未变，编译参数也未变，没有启用失败的链接选项。下一轮继续检查 61 处已确认所有者和成员的 ClassRef 静态枚举读取，以第十八轮隔离候选为实验基线。[生产修复脚本](../output/_v1110/optimize_native_build_config_dependencies.py) · [真实编译验证](../output/_v1110/native_perf50/cycles19/build_config_dependency_test_production.json) · [源码修复记录](../output/_v1110/native_perf50/cycles19/build_config_fix_installation.json) · [本轮记录](../output/_v1110/native_perf50/cycles19/ltrans_devirt_installation.json)


## 架构复盘（2026-11-21）

最近多轮没有新的 DLL 通过全部发布门槛并替换运行时。第十八轮 CPU A/B 有收益且 2,604 场逐事件通过，但原始 24 批最低 43.40 场/秒未达标，因此未部署；构建依赖修复属于工程可靠性，不计作模拟器速度提升。停止微小常量、局部变量和编译参数轮番试验，第 20 轮已准备的 61 处枚举折叠暂不编译测速。部署版继续为 `58383a11…`，语义研究基线可使用已备份且逐事件通过的 `7213d946…`。

补查发现旧采样最多回溯 12 层，6,124 个样本中 3,599 个达到上限，叶节点仍有效，父调用归属不充分。采样工具新增可选深度及上限命中计数，保持默认行为。对第十八轮候选单独采集 64 层调用栈，取得 6,020 个有效样本，56 个达到上限；51 个未回溯到回放根调用，其中能识别阶段的仍归入相应阶段，剩余 44 个单列为未归属。该采样用于定位，不作吞吐成绩。[深栈采样](../output/_v1110/native_perf50/architecture_review/experimental18_profile_depth64.json) · [互斥归属](../output/_v1110/native_perf50/architecture_review/architecture_sample_breakdown.json)

互斥归属约为：物品／宝石装配 **17.7%**，帧内物品触发链 **43.2%**，帧内其他工作 **34.0%**，其他初始化／导出 **4.3%**，未归属 **0.7%**。其他帧内工作仍含计时器、Buff 回调及视觉运动，不能全部算成可跳过的空帧。触发链中的主要叶节点包括通用方法派发、上下文属性读取、索引、事件总线及战报。仅替换帧循环或容器，不能消除这些成本，也不足以据此承诺数量级加速。旧版插桩曾测得装配约 1.9 毫秒/场，但它不是当前版本的精确下限，需重测；至少说明评估亚毫秒目标必须包含装配，不能只比较推进内核。

新路径优先做一个原生事件执行内核原型，覆盖完整的 trigger／伤害／Buff 事件链，减少通用动态值、容器及反复方法解析。第一阶段继续原固定物理帧、原回调次序、原浮点运算和 RNG，参考实现保留。以总主线程 CPU 降幅至少 20% 为原型扩展目标，达不到则重新评估，不再靠大量 1% 左右的试验续推。必须记录快速路径实际覆盖率，避免全部通过旧路径回退而产生虚假的验收通过。

确定性的混合事件调度作为第二条原型路线：调度键要包含帧、阶段和原物品／宝石顺序；同帧启停、重启、新增及变更需与原遍历一致。CoreTimer 的过期条件为 `<0`，物品冷却为 `<=0`。批量推进必须与逐帧浮点加减结果一致，不能直接替换为 n×delta；宿主 RNG、视觉运动及回放 before/after-frame 注入也需保留。先验证精确推进与原帧循环的状态差分，无法证明等效的区间继续原路径，不降低确定性标准。

装配路线另评估不可变阵容模板，现有 ItemProto 已缓存，不重复泛化构造缓存；保留每场可变状态、初始化回调、对象 ID 与 RNG，分别报告冷启动和复用成本。切换到 Rust 本身不会去掉现有架构的这些开销。其他事件流模拟器的名称、口径及源码暂无信息，不据此作直接速度比较。

所有原型仍以固定 200 场 A/B、2,604 场原版逐事件及逐场事件哈希、连续 24 批全部不低于 50 场/秒、SHA 核对与正常训练为发布条件。确定性指与真值一致，不只指同种子自身可重复。[架构决策记录](../output/_v1110/native_perf50/architecture_review/architecture_decision.json)

### 原生事件处理链首版（已验收，尚未部署）

以已备份的第十八轮隔离候选 `7213d946…` 为基线，生成原生桥接专用路径，覆盖 9 个核心类的 148 个方法、730 处属性／方法操作。已知精确类型直接读取原字段或调用原方法；数值、容器和帧循环仍沿用原实现，浮点表达式、回调嵌套与 RNG 位置保持不变。通用 C++ 调用继续原路径。全部 20 个单元重建，18 个热点单元重新训练 PGO，候选 DLL 为 `2b48ccf3…`。这属于减少整条事件链动态查找的首版原型，尚未实现无动态值的完整战斗内核。[转换记录](../output/_v1110/native_perf50/native_event_kernel_a/event_kernel_transform.json) · [备份及源码核对](../output/_v1110/native_perf50/native_event_kernel_a/event_kernel_baseline_archive.json)

回调追加、未来槽位替换、绑定参数、嵌套派发和同帧终局中断的两路径对照通过，旧回归与 22 个 C ABI 检查通过。914 + 1,690 场原版严格逐事件通过，全部 2,604 场 C++ 事件哈希不变，根仍为 `b8066c92…`。全量开启接收者精确类型审计，累计事件总线 5,598,805 次、受伤处理 318,534 次、临时 Buff 857,051 次、事件创建 3,079,126 次，类型不匹配为零，确认实际执行了新路径。[回调测试](../output/_v1110/test_native_event_kernel.cpp) · [全量验收](../output/_v1110/native_perf50/native_event_kernel_a/event_kernel_full_gate.json) · [事件哈希](../output/_v1110/native_perf50/native_event_kernel_a/event_kernel_event_hashes.json) · [类型审计](../output/_v1110/native_perf50/native_event_kernel_a/full_type_audit.json)

三组各八对、120 秒预热、静默隔离 AB／BA，相对第十八轮 CPU 成对耗时降幅中位数为 **7.76%、7.57%、4.34%**，墙钟为 **3.89%、3.80%、1.57%**；合计 24 对 CPU 中位降幅 **7.76%**，18 对更快，墙钟 **3.89%**，15 对更快。全部样本合计时间的降幅另为 CPU 8.15%、墙钟 7.55%，不与成对中位数混用。直接对照当前部署版的独立八对，CPU 中位降幅 **16.33%**、墙钟 **19.40%**，均 6/8 对更快。负载和频率波动仍影响估计，不将其解释成固定精确收益。[三组汇总](../output/_v1110/native_perf50/native_event_kernel_a/ab_assessment.json) · [部署版累计对照](../output/_v1110/native_perf50/native_event_kernel_a/ab_deployed.json)

连续 24 批吞吐中位数 **64.01 场/秒**，最低 **39.68 场/秒**，3 批低于 50；全程接电，估算后台负载 **13.1%–61.5%**。结果哈希和终局仍一致。未通过原始发布门槛，未部署、未接入默认生成流程，不重跑同一候选直到通过。观测范围内拟合到 20% 后台负载为 **81.89 场/秒**，仅用于解释波动，不能替代原始门槛或视为达到 100 场/秒。[原始 24 批](../output/_v1110/native_perf50/native_event_kernel_a/event_kernel_serial.json) · [负载拟合](../output/_v1110/native_perf50/native_event_kernel_a/event_kernel_load20.json) · [未部署及保留记录](../output/_v1110/native_perf50/native_event_kernel_a/event_kernel_installation.json)

用户随后要求避免过于保守地排除真实收益。后续调整为：**20% 是选路目标，不是单项淘汰线；综合全部配对数据、组间波动与负载，不因一组反向或区间跨零就直接丢弃候选。** 已通过确定性且有正收益证据的改动保留为组合基线，未明确的改动列为待定并以有上限的补测区分，不与明确变慢混为一类。本轮保留 `2b48ccf3…` 为下一轮隔离研究基线，重新采样后继续优化；确定性混合调度仍需先证明逐帧浮点等效及阶段顺序。以上不修改已经产生的原始结果，也不降低逐事件真值与 24 批部署要求。

### 按新标准复查旧候选及客户端更新检查点

只读取既有数据，复查了 97 份结构化对照记录、41 组不同基线／候选 SHA 组合，共 776 对，其中 56 对为同 DLL 的 A/A 控制。未启动新的编译、测速或优化。按完全相同的两份 DLL 分组合并，保留负向样本；不同预热／进程协议、已知编译或反汇编干扰单列，不将汇总文件重复计入。当前可比数据中，未发现已经充分证实、却被误丢弃的 10% 级提升；有数项约 1%–2% 的候选应从“淘汰”改为“待组合复核”。[完整数据矩阵及原报告哈希](../output/_v1110/native_perf50/reassessment_20261121/prior_trials_matrix.json)

下表均为成对耗时降幅中位数，正值表示减少耗时；不是承诺组合后仍有相同收益。

| 候选 | 原有数据 | 新判断与后续处理 |
| --- | --- | --- |
| arena 分配路径拆分 | 32 对，CPU +2.07%、墙钟 +0.70%；累计总 CPU 时间 −0.06%，总墙钟 −0.33%；已过 2,604 场及哈希 | 最值得恢复的已验收候选之一。原四组 CPU 必须全正的规则偏严；现有整体时间也接近零，收益仍待定。在新事件链基线上组合验证，不称为已证实的 2% 固定收益。 |
| 字典整数索引 | 24 对，CPU +1.49%、墙钟 +2.48%；累计总 CPU +1.38%、墙钟 +1.03%；已过容器边界、ABI 和定向回放 | 恢复为优先组合候选。此前有一组反向不足以直接淘汰；组合后补齐全量真值验收。 |
| 行为白名单常量化 | 早期 24 对 CPU +2.38%、墙钟 +1.36%；与角色版合并后 CPU −0.37%；较新独立版 16 对 CPU −0.34% | 保留为上下文相关候选；早期正收益不能直接迁移到新基线，也不能只选最好一版。可与新调用链小组组合，优先级低于前两项。 |
| 物品热字段布局 | 正式稳态 16 对 CPU +1.02%、墙钟 +0.17%；更早测量协议另列 | 小收益待定；当前已内嵌计时器，布局与旧版不同，需要重新设计与全量重建，先排在低成本组合之后。 |
| 标签整数迭代／稀疏计时器／共享速度项 | 分别 CPU +1.29%／+0.73%／+0.80%，墙钟 +0.19%／+0.89%／−0.50%；若干累计总时间接近零或反向 | 保留待定，不再因一组反向永久排除，也不将它们描述成已找到的大收益。共享速度和稀疏索引可随调度结构变化再评估。 |
| 稀疏冷却索引 | 最好单组 CPU +7.65%，但完整 24 对 CPU −0.006%、墙钟 −0.032% | 未发现约 8% 的净收益证据；保留结构思路，不能采用最好单组作为收益估计。 |
| 数组查询内联 | 有编译后台的单组 CPU +4.56%；独立组 CPU −0.45%、墙钟 −1.22% | 保留为待定；已知干扰组与独立组分别记录，不能把两组粗并后的 +2.55% 当作可靠提升。 |
| 第十八轮反查枚举与当前原生事件链 | 分别 CPU +5.21%、+7.76%；组合版对部署版独立八对 CPU +16.33%、墙钟 +19.40%；两版均过 2,604 场 | 已保留并叠加在 `2b48ccf3…`，是当前最有价值的组合基线；原始 24 批未过，因此仍未部署。不是遗漏项，也不把这三个百分数重复相加。 |

小收益可以叠加，后续以当前已验收候选为固定研究基线，每批选 2–3 项兼容修改形成组合；共享热点、代码布局、PGO 和缓存交互会使实际收益放大、抵消或重叠。先测组合，再在需要时拆分定位；不再要求每笔小改动都独立达到严格的组间全正条件。组合必须重新完成逐事件与事件哈希验收，不能直接相加旧百分比，也不能混用改变头文件前后的对象缓存。

用户要求暂停以更新客户端。当前运行 DLL 仍为 `58383a11…`，隔离研究候选为 `2b48ccf3…`；所有编译、测速和验收任务已结束。恢复时先核对检查点与哈希，再按上述优先级选择组合或结构原型；本次收尾不继续运行新任务。[恢复检查点](../output/_v1110/native_perf50/reassessment_20261121/resume_after_client_update.json)

### 恢复后的组合优化（已部署）

从已验收研究候选 `2b48ccf3…` 继续，把 arena 增长／加锁路径外提、字典存储整数索引、标签整数迭代三项合成一份候选。只改 `gd_rt.hpp`、`gd_rt.cpp`、`shard_00.cpp`，不要求各组件先独立测出收益。核对远端备份 `a5b108d2` 与 700 份源码／构建文件，全部 20 个单元重建、18 个热点单元训练 PGO，浮点设置不变。组合 DLL 为 `486dfce9…`。[构建与备份核对](../output/_v1110/native_perf50/bundle_arena_dict_labels/baseline_verified.json) · [组合变换](../output/_v1110/native_perf50/bundle_arena_dict_labels/transform.json)

分配对齐／重置／多线程、字典扩容与数值别名、标签容器回调修改及 RNG 顺序、旧生命周期与计时器、事件嵌套等回归通过。914 + 1,690 场原版严格逐事件通过，2,604 场 C++ 事件哈希保持不变，根仍为 `b8066c92…`；全语料类型不匹配为零。[全量验收](../output/_v1110/native_perf50/bundle_arena_dict_labels/bundle_full_gate.json) · [事件哈希](../output/_v1110/native_perf50/bundle_arena_dict_labels/bundle_event_hashes.json) · [类型审计](../output/_v1110/native_perf50/bundle_arena_dict_labels/full_type_audit.json)

相对研究基线，四组共 32 对固定 200 场、单线程、120 秒预热的隔离 AB／BA，墙钟成对中位降幅 **1.31%**，24 对更快，四组墙钟中位数均为正。CPU 成对中位降幅为 **0%**，15 对更快、9 对持平、8 对更慢；累计 CPU 时间减少 **0.43%**，累计墙钟减少 **0.64%**。因此保留“小幅墙钟改善、CPU 幅度未定”的判断，没有因 CPU 中位数为零或其中一组反向而丢弃组合，也不声称三项各自都有效。相对实际部署旧版 `58383a11…` 的独立八对，CPU 中位降幅 **11.63%**、墙钟 **11.55%**，两项均 8/8 对更快；它包含此前尚未部署的反向枚举与原生事件链收益，不归因给本轮三项小改动。[32 对完整汇总](../output/_v1110/native_perf50/bundle_arena_dict_labels/ab_assessment_4groups.json) · [推进验收的判断](../output/_v1110/native_perf50/bundle_arena_dict_labels/validation_decision.json) · [相对部署版](../output/_v1110/native_perf50/bundle_arena_dict_labels/ab_deployed.json)

正式连续 24 批全部通过原始吞吐门槛：中位数 **152.57 场/秒**、最慢 **147.27 场/秒**，全程接电，估算后台负载 **1.8%–15.4%**。此范围未覆盖 20%，故另做受控后台负载校准，保留原始发布报告。校准覆盖 **5.8%–25.4%**，24 批最慢 **111.59 场/秒**；20% 拟合值 **124.88 场/秒**，R² 为 0.59，留出相对耗时误差中位数 3.44%、P90 为 16.96%。可报告约 125 的水平，不能据此宣称最终 140 已完成；也不能把低负载下的 152.57 当成 20% 负载成绩。[发布 24 批](../output/_v1110/native_perf50/bundle_arena_dict_labels/bundle_serial.json) · [受控校准](../output/_v1110/native_perf50/bundle_arena_dict_labels/bundle_load_calibration.json) · [20% 拟合](../output/_v1110/native_perf50/bundle_arena_dict_labels/bundle_load20.json)

已将候选原子替换到源码目录和 `dist/native_1_1_10`，旧运行时留在 `dist/native_1_1_10_before_bundle_20261121`。DLL 与门槛报告、清单 SHA 均一致。正常训练入口 12 场评估零错误，另 12 场固定种子胜负与旧版一致。默认性能再生成流程接入版本受限的已审阅源码变换：准备阶段仅恢复三份运行时输入，既有生成步骤后应用已验收变换；未知源码编辑在写入前拒绝，防止覆盖新修改。700 份源码匹配已验收候选，字节与时间幂等、旧／新输入及末尾性能步骤衔接检查通过；本轮没有重新执行整条 GDScript 转译链，不将此局部检查称为全链路重建验收。[部署与训练](../output/_v1110/native_perf50/bundle_arena_dict_labels/bundle_installation.json) · [再生成约束](../output/_v1110/optimize_native_verified_bundle.py) · [再生成验证](../output/_v1110/native_perf50/bundle_arena_dict_labels/regeneration_test.json) · [末尾步骤衔接](../output/_v1110/native_perf50/bundle_arena_dict_labels/pipeline_composition_test.json)

下一轮以 `486dfce9…` 为实际运行基线，先重新采样，继续保留可组合的小收益，优先攻克足以推动 20% 负载下约 125 向 140 的热点。目标保持进行中。

已对部署版重采样：共 **6,033 栈**，64 层上限，12 栈达到上限；6,020 栈包含回放根。主要叶节点为 CoreCombat.physicsTick 678（11.24%）、CoreItem.physicsTick 359（5.95%）、CoreItem.call_method 217（3.60%），两个通用调用克隆分别 214／189；这些叶节点可比较，不能把包含样本重复相加成预期收益。装配 build_side_items 的包含样本为 1,199（19.87%），也仍值得关注。[部署版采样](../output/_v1110/native_perf50/post_bundle_profile/profile_depth64.json)

下一原型选择按精确生成类型缓存已解析的方法表，处理 CoreItem 及其派生类的重复方法查找，而非假定物品没有子类。源码审计覆盖 **674 类**，其派发器与父调用均为纯生成 switch；解析最派生实现，静态方法覆写也必须阻止错误回落到父实例方法。先选 32 条采样链及 16 个高静态调用频次的方法，保留原方法体与参数／绑定构造。对象第一次命中时用精确 RTTI 解析，未知 C++ 类型缓存空表，避免仅凭共享 metadata 绕过自定义 Hooks。源码续查确认 ItemProto 缓存不可变描述／几何输入，每场仍构造新对象并回填字段，并非整对象 memcpy 克隆；已修正此前设计假设。懒初始化在实际调用前建立缓存；普通复制／赋值需重置内部缓存，防止切片后保留错误的派生表。该项目前完成源码分析，**尚未构建或证明运行时等效**；全量重建、定向覆写／复制／回调测试、覆盖计数和原有发布验收仍不可省略。修改前的已部署源码／DLL 已备份到远端 `36c1f597`。[继承解析审计](../output/_v1110/native_perf50/post_bundle_profile/resolved_dispatch_design.json) · [原型约束](../output/_v1110/native_perf50/post_bundle_profile/next_prototype_plan.json)

### 精确类型方法表（已部署）

原型现已实现并验收。以部署版 `486dfce9…` 为基线，核对远端 `0b1a6c0a` 的 DLL 和 700 份源码。48 个方法按 674 个生成类的实际继承关系解析，得到 655 份不可变方法表，保留最派生覆写和静态方法遮蔽。普通对象方法与 FuncRef 都使用同一表，参数和绑定仍按原顺序构造。对象首次命中时以精确 RTTI 指针查表，未知 C++ 类型缓存空表，不调用 metadata getter；复制／赋值只重置内部缓存，原上下文、ID 和连接字段仍复制。非原生调用默认走旧路径。改变 GdObj 内部布局，全部 20 单元重建、18 热点单元重新训练 PGO，数值运算及浮点选项不变。正式 DLL 为 `6e232391…`。[实现](../output/_v1110/prototype_native_resolved_dispatch.py) · [变换与解析](../output/_v1110/native_perf50/resolved_dispatch_a/resolved_transform.json) · [备份核对](../output/_v1110/native_perf50/resolved_dispatch_a/baseline_verified.json)

生成类宝石／魔戒覆写、共享 metadata 的 C++ 覆写、切片／复制／赋值、FuncRef 换接收者及绑定、未知方法和关闭回退的测试通过，旧分配、容器、计时器、别名、回调顺序等回归通过，22 个 C ABI 符号不变。914 + 1,690 场原版严格逐事件通过，全部 2,604 场 C++ 事件哈希分别与当前部署基线及早期真值基线一致，根仍为 `b8066c92…`。全量审计新路径实际命中普通方法 **41,433,728** 次、回调 **976,034** 次，类型不匹配为零；旧事件内核类型审计也为零。测速进程关闭审计与计数。[覆写与复制测试](../output/_v1110/test_native_resolved_dispatch.cpp) · [全量验收](../output/_v1110/native_perf50/resolved_dispatch_a/resolved_full_gate.json) · [相对部署版事件哈希](../output/_v1110/native_perf50/resolved_dispatch_a/resolved_vs_deployed_hashes.json) · [全量覆盖](../output/_v1110/native_perf50/resolved_dispatch_a/full_type_audit.json)

三组各八对、120 秒预热、静默隔离 AB／BA：CPU 降幅 **5.05%、4.06%、5.36%**，墙钟 **4.07%、4.17%、4.34%**。24 对 CPU 和墙钟均全部更快，成对中位降幅分别 **4.68%、4.24%**，累计总时间降幅 **4.74%、4.23%**；观测后台负载 **1.7%–8.8%**，全程接电。这是相对上一轮已部署组合的增量，不与先前百分数直接相加。[对照汇总](../output/_v1110/native_perf50/resolved_dispatch_a/ab_assessment.json)

正式连续 24 批全部通过：中位 **159.65 场/秒**、最慢 **156.16 场/秒**，全程接电、后台负载 **2.5%–8.0%**。受控校准另覆盖 **6.1%–50.1%**，24 批中位 **125.99**、最慢 **91.97 场/秒**；20% 拟合值 **124.77 场/秒**，R² **0.92**，留出耗时误差中位数 **2.91%**、P90 **5.66%**。此绝对估计与上轮约 124.88 接近，不能将不同负载构成、时间段和模型误差下的两次拟合之差，替代同条件 A/B 的代码收益；最终 140 目标仍未完成。[发布吞吐](../output/_v1110/native_perf50/resolved_dispatch_a/resolved_serial.json) · [校准](../output/_v1110/native_perf50/resolved_dispatch_a/resolved_load_calibration.json) · [20% 拟合](../output/_v1110/native_perf50/resolved_dispatch_a/resolved_load20.json)

默认性能再生成流程已更新，新增完整源码库存保护，避免未修改分片中出现新覆写时仍沿用旧表。完整 GDScript 转译及既有性能处理在隔离副本中连续运行两次，**701 份源码／配置与已编译候选一致，重复字节及修改时间不变**；未知未修改分片的编辑会在应用变换前被拒绝。本轮没有为此额外编译 DLL，完整源文本验证与先前候选全量编译配合使用。[完整再生成检查](../output/_v1110/native_perf50/resolved_dispatch_a/full_regeneration_test.json) · [全库存保护](../output/_v1110/native_perf50/resolved_dispatch_a/regeneration_test.json)

新源码及 DLL 已原子部署到训练运行时，旧版保留在 `dist/native_1_1_10_before_resolved_20261121`。验收报告、运行时清单与 DLL SHA 一致；正常训练入口 12 场零错误，另 12 场固定种子结果与基线一致。下一轮继续基于新部署版重新采样并组合优化，目标保持进行中。[部署及训练](../output/_v1110/native_perf50/resolved_dispatch_a/resolved_installation.json)

部署版再采样取得 6,043 个包含回放根的栈，主要叶节点仍为逐帧 CoreCombat（719）、CoreItem（371）及通用调用克隆（289／255）。独立诊断 DLL 只在 gd_rt 单元增加未覆盖方法计数，头文件布局和其余源码均与缓存一致，复用 19 个已验收对象；只用于定位，不作吞吐成绩，也未替换运行 DLL。固定 200 场结果哈希保持一致。发现目前还有 **8,931,122** 次未覆盖调用，最频繁的是 tick 1,022,970、isBag 372,673、getStacks 368,123，继而是 has_method、randf_range 与影响区域查询；此前按包含耗时及静态站点挑选的方法，遗漏了高频但短小的调用。[新采样](../output/_v1110/native_perf50/post_resolved_profile/profile_depth64.json) · [诊断实现](../output/_v1110/native_perf50/post_resolved_profile/probe_dispatch_misses.py) · [未覆盖频次](../output/_v1110/native_perf50/post_resolved_profile/uncovered_method_counts.json)

下一组合据此保留原 48 方法，再加入 64 个具有生成实例实现的高频方法，并评估 Array／Int 索引的等价内联路径。新增的方法名在该批次出现约 **703 万次**，这不是快速路径命中承诺：部分调用接收者是自定义 NativeBattleHooks 等 C++ 类型，仍须回退并以诊断确认实际覆盖。112 个槽位仍在有符号 8 位索引范围内；预计 665 份只读行、约 596 KiB 函数指针，也可能增加缓存成本，须整体 A/B，不能按调用次数直接折算收益。数组路径需保留负索引、越界、空数组与非整数／非数组回退，数学及 RNG 保持原实现。本组合目前仅完成选择和解析，尚未构建；已部署版仍为 `6e232391…`，修改前备份为 `75f025d5`。[下一组合选择](../output/_v1110/native_perf50/post_resolved_profile/next_bundle_selection.json)

### 高频短方法与数组索引组合（已部署）

已把上述两项作为一个候选包实现，未要求每一笔先独立达到可见收益。修改前核对远端 `75f025d5` 的 701 份源码及当前运行 DLL；方法表扩展到 112 槽、665 行，精确类型、继承覆写、静态遮蔽与自定义 C++ 回退规则保持不变。459 处生成索引调用使用 Array＋Int 的等价内联路径，其余键／接收者仍调用原实现；保留参数表达式和求值方式，不新增逐次索引计数。全量 20 单元编译、18 热点单元 PGO，浮点选项不变。正式候选为 `0904c29d…`。[实现](../output/_v1110/prototype_native_dispatch_array_bundle.py) · [完整变换](../output/_v1110/native_perf50/dispatch_array_bundle/transform.json) · [固定测量方案](../output/_v1110/native_perf50/dispatch_array_bundle/evaluation_plan.json)

定向检查通过：512 次 RNG 逐位及状态比较、32 次计时器推进、280 个索引差分用例、负索引及整数边界、空／非整数／非数组回退、getter 调用次数、引用别名，以及既有覆写、复制、FuncRef、回调、分配与容器回归。固定 200 场方法表实际命中普通方法 **9,300,441** 次、FuncRef **100,900** 次，类型不匹配零；200 个未知 C++ 类型和 233,004 次选中但不支持的方法仍回退，不以命中次数宣称收益。[索引边界](../output/_v1110/native_perf50/dispatch_array_bundle/array_index_test.json) · [RNG／计时器／覆写](../output/_v1110/native_perf50/dispatch_array_bundle/expanded_dispatch_test.json) · [正式候选诊断](../output/_v1110/native_perf50/dispatch_array_bundle/release_audit.json)

三组各八对固定 200 场单线程隔离 AB／BA，均先交替预热 120 秒。第一组 CPU／墙钟耗时降幅 **−1.11%／−0.24%**，第二组 **4.97%／5.07%**，第三组 **5.45%／5.07%**。完整 24 对成对中位降幅为 **4.94% CPU、4.92% 墙钟**，累计总时间降幅 **4.33%／4.11%**，分别 18／19 对更快；全程接电，观测后台负载 **1.65%–29.83%**。保留第一组反向数据，未按组间必须全正淘汰，也不把两项旧收益相加或声称各项都有效。[完整组合对照](../output/_v1110/native_perf50/dispatch_array_bundle/ab_assessment.json)

914 + 1,690 场原版严格逐事件核验通过；2,604 场 C++ 事件哈希分别与当前部署 `6e232391…` 及早期 `58383a11…` 完全一致，根仍为 `b8066c92…`。全量新路径普通调用 142,269,767 次、FuncRef 2,143,020 次，类型不匹配零，旧事件内核审计也为零。正式测速关闭计数和审计。[全量真值](../output/_v1110/native_perf50/dispatch_array_bundle/bundle_full_gate.json) · [相对当前运行版事件哈希](../output/_v1110/native_perf50/dispatch_array_bundle/bundle_vs_deployed_hashes.json) · [全量类型审计](../output/_v1110/native_perf50/dispatch_array_bundle/full_type_audit.json)

正式连续 24 批全部通过原始门槛：中位 **153.90 场/秒**、最慢 **127.12 场/秒**，全程接电，后台负载 **1.63%–17.79%**。另行受控校准覆盖 **6.59%–28.64%**，24 批中位 **138.67**、最慢 **100.47 场/秒**；20% 拟合为 **119.97 场/秒**，R² **0.892**，留出耗时误差中位 **4.43%**、P90 **6.54%**。如实保留该拟合及较低原始吞吐，不用它宣称 125 或 140 达标，也不重跑到出现较好数字。[发布原始吞吐](../output/_v1110/native_perf50/dispatch_array_bundle/bundle_serial.json) · [独立校准](../output/_v1110/native_perf50/dispatch_array_bundle/bundle_load_calibration.json) · [20% 估计](../output/_v1110/native_perf50/dispatch_array_bundle/bundle_load20.json)

因本次独立 20% 拟合低于上轮约 124.77，而主要 A/B 为正，追加一组**共享受控负载**的新旧版直接对照，保留为不同协议，不混入主要 24 对。两条低优先级后台任务在 20%／85% 占空比之间切换、最长 240 秒，DLL 仍各自单线程、正常优先级，交替预热 120 秒后运行 16 对。CPU 耗时中位下降 **4.32%**、墙钟下降 **4.07%**，分别 11／10 对更快；累计 CPU 仅减少 **0.79%**、累计墙钟仅减少 **0.08%**，说明较大的负向波动抵消了多数对的改善，不能将中位数解读为稳定的高负载总吞吐提升。全程接电，负载 **7.68%–29.87%**。主要 A/B 的累计与中位证据仍为正，本组保留幅度不稳的判断，也不能把跨时段独立模型之差直接当成同条件代码退化证据；当前绝对 20% 成绩仍按本次约 120 记录，目标继续进行。[共享负载协议](../output/_v1110/native_perf50/dispatch_array_bundle/shared_load_protocol.json) · [对照](../output/_v1110/native_perf50/dispatch_array_bundle/shared_load_assessment.json)

完整源码生成流程在隔离目录运行两遍，702 份源码／构建文件与编译候选一致，重复字节与修改时间不变；对未修改类头文件添加未知编辑时，准备和应用阶段均在写入前拒绝。版本受限源码变换保存 22 份必要文件，运行时默认生成器已切换到新库存。[全链路生成](../output/_v1110/native_perf50/dispatch_array_bundle/full_regeneration_test.json) · [编辑保护](../output/_v1110/native_perf50/dispatch_array_bundle/regeneration_test.json)

已部署到默认训练运行时，旧版留在 `dist/native_1_1_10_before_dispatch_array_20261121`。DLL、门槛报告、运行时清单 SHA 一致；正常训练入口 12 场零错误，另 12 场固定种子胜负与旧版一致。下一轮重新采样已部署候选，继续从高频调用和战斗推进中选择兼容的小组合；本轮不拆分否定单项收益。[部署与训练检查](../output/_v1110/native_perf50/dispatch_array_bundle/bundle_installation.json)

此部署检查点已提交 `f8b19bbe`，推送至 `codex/native-perf50-verified` 的 `611d698f`，702 份生产源码、DLL 及已打包报告／清单均核对远端原始字节一致。

### 基础值比较与数组写入（小幅迹象，保留继续组合）

对 `0904c29d…` 重采样取得 **6,005 栈**、其中 5,996 栈包含回放根。CoreItem.call_method 叶节点从上轮 177 降至 61；新的主要叶节点为 CoreCombat.physicsTick 743、CoreItem.physicsTick 386、通用调用克隆 300／275，相等比较 141、索引写入 99。包含样本仍不能相加为预期收益。首次采样在写报告时因输出目录未创建而失败；补上目录创建后重跑，只有第二次生成的完整报告用于分析。[部署版新采样](../output/_v1110/native_perf50/post_dispatch_array_profile/profile_depth64.json)

下一隔离候选合并两项：958 处基础值相等／不等比较，仅在双方同为 Null、Bool、Int、Float 时内联原比较；110 处 Array＋Int 写入内联原负索引、越界与数据赋值。其余比较及写入仍回到原实现，尤其保留混合数值转换及数组递归相等。未触碰大小比较、算术、FMA、帧顺序或 RNG。修改前核对远端 `611d698f` 的 702 份源码与当前 DLL，全部 20 单元重建、18 热点 PGO，候选为 `464add2e…`。[实现](../output/_v1110/prototype_native_scalar_array_bundle.py) · [变换](../output/_v1110/native_perf50/scalar_array_bundle/transform.json)

841 对相等／不等比较、78 组写入差分用例覆盖 NaN、正负零、极值整数、超过 2^53 的混合整数／浮点、容器相等、未知对象 setter 及接收者自身被覆盖时的别名；全部通过。既有 RNG、计时器、覆写、复制、回调与容器回归也通过，固定 200 场结果哈希一致、类型不匹配零。完整源码生成两遍得到 703 份一致源码／配置，字节与修改时间稳定，未知编辑保护通过。本候选**尚未跑 2,604 场及发布 24 批，也未部署**。[差分检查](../output/_v1110/native_perf50/scalar_array_bundle/scalar_array_test.json) · [生成流程](../output/_v1110/native_perf50/scalar_array_bundle/full_regeneration_test.json)

三组各八对隔离 AB／BA 的 CPU 中位降幅为 **0.66%、0%、1.32%**，墙钟为 **0.67%、−0.03%、0.99%**。完整 24 对 CPU 中位 **0%**，11 对更快、9 对持平、4 对更慢，累计 CPU 时间减少 **0.44%**；墙钟中位减少 **0.70%**、累计减少 **0.35%**、17 对更快。去掉某一组后 CPU 累计约 −0.08%，体现幅度较小，不能宣称稳定的 1% CPU 提升。但两项没有因此被淘汰：保留这份候选，继续与兼容改动组合，比较更大组合相对当前部署版的净效果。[全部 24 对](../output/_v1110/native_perf50/scalar_array_bundle/ab_assessment.json) · [继续组合的决定与源码审计](../output/_v1110/native_perf50/scalar_array_bundle/composition_decision.json)

后续组合方向为：空值与非空值比较直接给出原实现的 false；对精确已知生成类型的 has_method／get_instance_id，跳过已证明不会命中的用户方法派发链，进入原内建实现。已审计全部 674 份派发器及父回退均为纯生成分支，目标内建方法没有生成覆写。未知 C++ 类型必须继续回退，FuncRef 原来没有这些内建语义，不能因复用快速路径而新增行为；必须补上自定义覆写、缺参／非法参数、ID 顺序与 epoch 的差分测试。此扩展目前只有设计和源码审计，尚未实现。当前默认运行时保持已验收的 `0904c29d…`，目标继续进行。

### 空值与内建方法追加组合（未测出明确收益，保留）

已将上述扩展与 `464add2e…` 的比较／写入两项合并。修改前再次核对远端 `42ea3518` 的 702 份生产源码及 `0904c29d…` DLL；首次 SSH 查询超时后确认构建进程已失败退出，再恢复查询并重新运行，保留失败日志。全量 20 单元编译、18 热点 PGO，浮点及布局不变，候选为 `99ef4afd…`。[组合实现](../output/_v1110/prototype_native_scalar_builtin_bundle.py) · [变换](../output/_v1110/native_perf50/scalar_builtin_bundle/transform.json)

空值与非空值直接返回原实现的 false，其他类型转换不变；只有泛用对象调用中的精确已知生成类型才能走两种内建捷径，仍调用原 has_own_method／get_instance_id；未知 C++ 类型和 FuncRef 保持旧路径。34 个新增差分检查覆盖共享 metadata 的 C++ 覆写、缺参／非法参数、FuncRef 的原 Null 行为、换接收者与 ID 的分配顺序、epoch／回绕。既有 841 对比较、78 组写入、512 次 RNG 等回归通过。固定 200 场结果哈希保持一致，新增内建命中 **469,905** 次，恰与该批两种内建调用之和相符；类型不匹配零。703 份源码的完整再生成两遍与未知编辑保护通过。[内建差分检查](../output/_v1110/native_perf50/scalar_builtin_bundle/builtin_dispatch_test.json) · [正式候选诊断](../output/_v1110/native_perf50/scalar_builtin_bundle/release_audit.json) · [生成流程](../output/_v1110/native_perf50/scalar_builtin_bundle/full_regeneration_test.json)

三组各八对固定 200 场隔离 AB／BA：CPU 中位降幅 **0%、−1.33%、0.67%**，墙钟 **0.18%、0.62%、−0.22%**。完整 24 对 CPU 中位和累计耗时均持平，9 对更快、4 对持平、11 对更慢；墙钟中位减少 **0.09%**、累计减少 **0.16%**、14 对更快。全程接电，背景负载 **1.50%–8.85%**。没有测出明确净收益，不推进替换；也不将前一包约 0.7% 与本包约 0.1% 的差直接解释为新单项必然有害，保留分支供组合验证。此候选只过定向和固定 200 场检查，**未跑 2,604 场发布核验及 24 批，未部署**。[24 对完整汇总](../output/_v1110/native_perf50/scalar_builtin_bundle/ab_assessment.json) · [后续决定](../output/_v1110/native_perf50/scalar_builtin_bundle/composition_decision.json)

接下来优先尝试更大的调用结构优化：当前采样中通用调用四类叶节点合计 **766／6,005**，先暴露 112 个方法槽位及只读行布局给生成调用位置，使常量方法编号能够在调用点折叠，并由调用点直接返回已缓存函数的原结果，减少统一包装和返回值中转，也给 PGO 留下按调用点识别目标的机会。行内容、精确类型缓存、最派生覆写与原方法体不变；未缓存、不支持、非对象或关闭路径仍只调用一次原派发；审计在解引用行前检查精确 RTTI。不是跳帧、重排或改变浮点。已写隔离变换，尚未构建／验证收益，后续仍用相同门槛决定是否合入。若此层收益仍有限，再以计数构建量化 Buff／物品逐帧扫描的活跃比例与变更频率，评估保持同帧可见性的稀疏遍历。[调用位置原型](../output/_v1110/prototype_native_inline_dispatch_bundle.py)

### 调用位置的缓存派发（已部署）

已将前述保留组合与调用结构原型合并实现，修改前核对远端 `e48ae607` 的 702 份生产源码和 `0904c29d…` DLL。10,325 处生成调用使用内联包装；112 槽只读行的内容及布局不变，槽位映射移入共享头文件，常量方法编号可在调用位置折叠，缓存命中直接返回原函数结果。未缓存、不支持、非对象或关闭时仍只调用一次原派发；精确 RTTI 审计在读取行内容之前进行。继承、静态遮蔽、未知 C++ 回退、绑定、参数表达式及原方法体保留。全部 20 单元编译、18 热点 PGO，浮点设置不变，正式候选为 `1be75dce…`。DLL 从 10,791,543 增至 12,325,322 字节，记录体积成本，不以调用次数代替收益。[实现](../output/_v1110/prototype_native_inline_dispatch_bundle.py) · [变换](../output/_v1110/native_perf50/inline_dispatch_bundle/transform.json)

新增差分检查覆盖缓存／未缓存、已知派生与共享 metadata 的 C++ 覆写、一次回退、切片／赋值、故意设置非法行地址时先审计再读取、空对象／数组／字典／关闭路径，以及正负零与 NaN payload 的返回位模式；审计关闭时的 512 次 RNG 对照也通过。原有 34 个内建、841 对比较、78 组写入、计时器及回调／分配／容器回归通过。固定 200 场结果及全部六项覆盖计数与上一保留组合一致，没有新增漏调用、重复调用或类型不匹配。704 份源码／构建文件的完整生成流程运行两遍，字节和修改时间稳定，未知编辑保护通过。[内联差分检查](../output/_v1110/native_perf50/inline_dispatch_bundle/inline_dispatch_test.json) · [诊断覆盖](../output/_v1110/native_perf50/inline_dispatch_bundle/release_audit.json) · [完整生成](../output/_v1110/native_perf50/inline_dispatch_bundle/full_regeneration_test.json)

三组各八对固定 200 场单线程隔离 AB／BA，交替预热 120 秒后采样：CPU 耗时中位降幅 **5.88%、6.58%、4.63%**，墙钟 **5.44%、5.48%、5.24%**。完整 24 对 CPU／墙钟分别中位减少 **5.30%／5.44%**，累计总时间减少 **6.39%／6.73%**，两项均 24 对全部更快。全程接电，后台负载 **1.22%–19.62%**。是整个组合相对当前部署版的增量，未把此前小收益相加，也不能认定每项分别有效。[完整对照](../output/_v1110/native_perf50/inline_dispatch_bundle/ab_assessment.json)

914 + 1,690 场原版严格逐事件核验通过；全部 2,604 场 C++ 事件哈希与当前部署 `0904c29d…` 及早期 `58383a11…` 一致，根仍为 `b8066c92…`。全量诊断普通快速调用 149,634,797 次、FuncRef 2,143,020 次，类型不匹配零；旧事件内核审计也为零。正式测速关闭诊断计数和审计。[全量真值](../output/_v1110/native_perf50/inline_dispatch_bundle/bundle_full_gate.json) · [相对当前版逐场哈希](../output/_v1110/native_perf50/inline_dispatch_bundle/bundle_vs_deployed_hashes.json) · [类型审计](../output/_v1110/native_perf50/inline_dispatch_bundle/full_type_audit.json)

正式连续 24 批通过：中位 **178.72 场/秒**、最慢 **165.96 场/秒**，全程接电，后台负载 **1.47%–16.48%**。另行受控校准覆盖 **4.82%–25.01%**，24 批中位 **161.13**、最慢 **128.14 场/秒**；20% 拟合为 **139.94005 场/秒**，R² **0.856**，留出耗时误差中位 **3.31%**、P90 **7.27%**。接近 140，但本次估计略低于目标，不以四舍五入作最终完成证据，目标继续保持进行中；也不能把本次与上轮独立拟合之差全部归因于代码，代码收益以同条件 A/B 为依据。[发布 24 批](../output/_v1110/native_perf50/inline_dispatch_bundle/bundle_serial.json) · [受控校准](../output/_v1110/native_perf50/inline_dispatch_bundle/bundle_load_calibration.json) · [20% 换算](../output/_v1110/native_perf50/inline_dispatch_bundle/bundle_load20.json)

已原子部署到默认训练运行时及生产 C++ 目录，旧版保留为 `dist/native_1_1_10_before_inline_dispatch_20261121`。DLL、报告与运行时清单 SHA 一致；正常训练入口 12 场零错误，另 12 场固定种子结果与旧版一致。默认源生成器切换到新 704 份库存与 24 份变换图像。下一轮从新部署版采样，优先审视剩余泛用容器调用和逐帧扫描，在不改变数学、RNG、回调和同帧可见性的前提下继续组合验证。[部署检查](../output/_v1110/native_perf50/inline_dispatch_bundle/bundle_installation.json)

已提交 `fc84ad76` 并推送远端 `4f57fdd2`，704 份生产源码、DLL、打包报告与清单均核对原始字节一致。新部署版重采样共 6,010 栈、6,008 个回放根有效栈。通用调用叶节点合计从上轮 766 降至 336，CoreCombat.physicsTick 847、CoreItem.physicsTick 396、EventBus.emitAndLog 112、Dict.set 94、相等比较 87；没有独立 set_index 叶节点。函数边界随内联变化，不能由叶样本差直接计算收益，也不把 CoreCombat 叶样本上升当作总 CPU 退化。[新采样](../output/_v1110/native_perf50/post_inline_dispatch_profile/profile_depth64.json)

下一轮优先组合容器纯查询和静态 ClassRef 调用通道：在调用位置复制原来的 size／empty／has／front／back／get 规则；非 new 的 ClassRef 原静态回调只执行一次，返回 false 时直接保持原 Null，不能再调用原总入口造成二次副作用。继续保留空指针、缺参、默认值、未知对象覆写、关闭路径与构造入口。若该层收益有限，再计数 Buff／物品逐帧扫描的活跃率和变更；可先试无持久索引的短路分块预筛，在遇到活跃项前停止预读、随后回到原遍历，保持回调对后续项的同帧影响。当前只有选择和源码审视，没有实施下一包。140 目标保持进行中。[后续组合计划](../output/_v1110/native_perf50/post_inline_dispatch_profile/next_bundle_plan.json)

### 容器查询与静态调用组合（已测，保留继续组合）

上述组合已经实现，候选为 `8bdcd96d…`，当前部署仍为 `1be75dce…`。保留原参数、空值、默认值与回退规则，静态回调最多执行一次；1,034 个新增差分检查及既有 RNG、回调、容器等回归通过。固定 200 场签名一致，新增路径实际覆盖 3,311,383 次；覆盖次数不作为收益证明。完整 704 份源码再生成两次通过。PGO 计数 DLL 首次链接遇到 Windows 导出序号上限，改为仅对计数 DLL 显式导出所需 C 接口后完成；正式 DLL 保持原导出与浮点设置。[新增差分检查](../output/_v1110/native_perf50/variant_inline_bundle/variant_inline_test.json) · [正式覆盖](../output/_v1110/native_perf50/variant_inline_bundle/release_audit.json)

三组各八对固定 200 场单线程隔离 AB／BA 全部完成。24 对 CPU 耗时中位持平、累计减少 **0.81%**；墙钟中位增加 **0.32%**、累计减少 **0.31%**。CPU 和墙钟分别仅 8 对更快，全程接电，后台负载 **1.13%–19.65%**。累计时间受较大波动影响，尚不能确认组合有稳定净收益；保留全部正反结果，也保留各项供后续叠加，未部署、未运行本候选的 2,604 场发布验收及发布 24 批。[完整对照](../output/_v1110/native_perf50/variant_inline_bundle/ab_assessment.json) · [组合决定](../output/_v1110/native_perf50/variant_inline_bundle/composition_decision.json)

按用户澄清继续执行：单笔小收益可以先叠加，再直接测整个组合相对部署版的净效果，不要求每笔先通过独立显著性门槛。组合通过只能证明整体有效；若需要定位贡献，再撤掉某项做对照，不把历史百分比直接相加。下一方向先量化 Buff／物品计时器的无效扫描，再选择保持同帧回调语义的兼容改动。

计数构建已完成，仅重编译两个扫描所在单元并复用当前版其余对象，未用于吞吐判断。固定 200 场输入／结果签名一致：386,704 次 Buff 扫描访问 4,253,744 项，实际计时 43,699 次，非布尔标志零；386,704 个完整八项组中 385,806 组全部停用（99.77%）。物品扫描 13,473,218 次，668,131 次带计时器（4.96%）；宝石对象扫描 708,238 次，15,401 次带计时器（2.17%）。不能由次数比例推算总耗时收益。下一原型把 Buff 八项短路预筛与已保留容器／静态调用、此前单测反向的五处布尔冷却判断组合，重新直接比较整个组合；不沿用旧收益或旧淘汰结论。修改战斗路径前再次保存当前验收版与试验记录。[本轮扫描计数](../output/_v1110/native_perf50/scan_activity_probe/scan_counts.json)

### Buff 空扫描与保留改动组合（已部署）

修改前已提交 `7ec6c42f` 并推送远端 `33b49c8c`，逐字节核对 704 份生产源码、当前 `1be75dce…` DLL 和运行时清单。新组合为 Buff 八项短路预筛、此前保留的容器／静态调用，以及早期单测反向的五处布尔冷却判断。预筛仅在八项全为 Bool false 时跳过；遇到第一项活跃或非 Bool 就停止预读，按原循环顺序实时检查整组。保留原 entries 指针、长度捕获及回调对未来项的同帧可见性，无持久资格缓存，不改浮点、计时方法体或 RNG。全部 20 单元编译、18 热点 PGO，正式候选 `7af5ff94…`。[组合实现](../output/_v1110/prototype_native_scan_bundle.py) · [变换](../output/_v1110/native_perf50/scan_bundle/transform.json)

1,624 个 Buff 差分用例覆盖组／尾部边界、混合标志、回调新增／停用／重启、替换未来项、修复未来空占位、字典擦除／扩容／替换及嵌套推进；另 40 个冷却标志检查覆盖原来的非 Bool 真假转换和容器内容变化。两版状态与回调摘要一致。既有 RNG、派发、容器、计时器、生命周期回归及三场原版严格逐事件检查通过，固定 200 场签名一致；704 份源码的完整再生成两遍及未知编辑保护通过。[新增差分检查](../output/_v1110/native_perf50/scan_bundle/buff_chunk_differential.json) · [完整再生成](../output/_v1110/native_perf50/scan_bundle/full_regeneration_test.json)

三组各八对固定 200 场单线程隔离 AB／BA 均完成，交替预热 120 秒、普通优先级、全八逻辑 CPU、无编译／采样重叠。三组 CPU 中位降幅 **0%、1.33%、3.33%**，墙钟 **0.83%、1.18%、2.43%**。完整 24 对 CPU 中位减少 **1.36%**、累计减少 **1.70%**，14 对更快、6 对持平、4 对更慢；墙钟中位减少 **1.36%**、累计减少 **1.65%**，23 对更快。去掉任一组后，CPU／墙钟累计耗时仍均减少。全程接电，后台负载 **1.26%–7.08%**。这是整个组合相对部署版的增量，不证明各项均有效，不把历史百分比相加；第一组 CPU 中位持平没有被单独作为淘汰条件。[全部 24 对](../output/_v1110/native_perf50/scan_bundle/ab_assessment.json) · [继续验收的决定](../output/_v1110/native_perf50/scan_bundle/composition_decision.json)

914 + 1,690 场原版严格逐事件验收全部通过；2,604 场 C++ 事件哈希与当前部署 `1be75dce…` 和早期 `58383a11…` 均一致，根仍为 `b8066c92…`。全量新方法表及旧事件内核的类型不匹配均为零。[全量验收](../output/_v1110/native_perf50/scan_bundle/bundle_full_gate.json) · [相对部署版逐场哈希](../output/_v1110/native_perf50/scan_bundle/bundle_vs_deployed_hashes.json) · [全量审计](../output/_v1110/native_perf50/scan_bundle/full_type_audit.json)

单次连续 24 批发布测速通过：中位 **163.92 场/秒**、最慢 **135.78 场/秒**，全程接电，后台负载 **1.46%–14.00%**。单次受控校准覆盖 **5.98%–24.22%**，24 批中位 **146.09**、最慢 **117.35 场/秒**；20% 拟合 **127.32799 场/秒**，R² **0.915**，留出耗时误差中位 **1.60%**、P90 **6.14%**。保留这份低于 140 的结果，不重跑至过线；目标仍在进行。不同时间的独立拟合不能直接当作代码的因果比较。[原始 24 批](../output/_v1110/native_perf50/scan_bundle/bundle_serial.json) · [受控校准](../output/_v1110/native_perf50/scan_bundle/bundle_load_calibration.json) · [20% 换算](../output/_v1110/native_perf50/scan_bundle/bundle_load20.json)

因本轮拟合低于上轮，部署前另行预先记录一次共用固定负载的 16 对 AB／BA，而非覆盖原校准或追加直到有利。两条低优先级后台任务各 72% 占空比、普通单线程模拟、交替预热 120 秒；实际后台负载 **17.09%–38.78%**，全程接电，全部样本保留。CPU 中位／累计耗时减少 **0.53%／1.06%**，8 对更快、3 对持平；墙钟中位／累计减少 **0.73%／0.54%**，10 对更快。波动较大，支持小幅组合收益，没有证明精确的 20% 绝对速度，也未见独立拟合差值暗示的约 9% 代码退化。[预先方案](../output/_v1110/native_perf50/scan_bundle/target_load_protocol.json) · [完整对照](../output/_v1110/native_perf50/scan_bundle/target_load_assessment.json)

满足一致性、主要成对收益和原始吞吐门槛后，已原子部署 `7af5ff94…` 到默认训练运行时及生产 C++ 目录，旧版保留在 `dist/native_1_1_10_before_scan_bundle_20261121`。默认 DLL、生产 DLL、报告及运行时清单 SHA 对应一致；正常训练入口 12 场零错误，另 12 场固定种子结果与旧版一致。默认再生成器使用新 704 份库存和 24 份变换图像。下一轮从新部署版重采样，寻找更大的可叠加热点，继续保留逐事件确定性。[部署记录](../output/_v1110/native_perf50/scan_bundle/bundle_installation.json)

已提交 `f1b671ca` 并推送远端 `53b16a2c`，704 份生产源码、两处 DLL、发布报告及运行时清单均核对原始字节一致。

### 稀疏物品计时器与分配时方法表预填（构建中）

新部署版重采样取得 **6,036 栈**、其中 **6,030 个回放根**。主要叶节点为 CoreCombat.physicsTick 393、CoreItem.physicsTick 368、CoreCombat._tickCharacterTimers 323；通用调用三类叶节点合计 236，字典 set/get/find_index 为 100/81/71，相等比较 104。函数边界会随内联变化，尤其角色计时器由上一轮物理帧函数内部移为独立叶节点，不能只用单个叶节点的增减推算收益。[新采样](../output/_v1110/native_perf50/post_scan_bundle_profile/profile_depth64.json)

本轮重新组合旧稀疏物品计时器原型与生成分配器的方法表预填：旧原型的完整 24 对 CPU／墙钟中位改善约 0.73%／0.89%，当时因组间波动未合入；按新标准保留并重测，未宣称其已有稳定大收益。索引按原升序下标记录自身或宝石带计时器的物品；修改期间从已访问位置之后回到原顺序遍历，保留捕获长度。未知／未来占位项保守保留，嵌套、排序回调与 epoch 饱和时使用原路径。停止状态的计时器仍参与原遍历，不改变启动／停止／重启与首次生效规则。

源码审查补齐了旧原型未覆盖的现版数组内联写入。未知 C++ 对象的 getter／setter／方法／FuncRef、未知 ClassRef 静态回调进入前使索引失效，即使它们直接写公开字段或发生在计时器阶段之外也不能复用旧资格。已知生成类仍靠实际数组修改、字段替换及排序的追踪来失效。674 个生成分配器可预填现有的 665 份去重方法行；自定义分配器、栈对象和未知派生仍保留原惰性 RTTI 路径，审计在解引用行前进行。

修改前再次核对远端 `53b16a2c` 的当前 DLL 与全部 704 份源码。准备阶段发现旧注释锚点及“类型数等于去重行数”的假设过时，已按实际源码修正并通过完整变换预检，原失败日志保留。由于 BattleCtx 开关及角色索引缓存改变布局，正在全部 20 单元重建并训练 18 个热点单元；浮点、RNG、计时方法体和物理帧阶段不变。定向检查已安排旧索引／别名用例、674 类分配的开关对照、未知回调直接替换字段及内联写入失效用例，尚未运行。本候选尚无正式 A/B／全量验收／发布吞吐结果，未部署；当前运行时保持 `7af5ff94…`。[组合实现](../output/_v1110/prototype_native_sparse_timer_bundle.py) · [预先测量方案](../output/_v1110/native_perf50/sparse_timer_bundle/evaluation_plan.json)

继续审查时发现两个旧索引原型的边界问题，均在进入正式测速前处理：默认复制缓存会共享下标缓冲区，已用四项复制／移动／赋值负例复现，补充清空私有缓存的语义后四项正例通过；资格预检查会额外调用未知 C++ 对象的虚 `meta()`，负例实际记录到一次原遍历没有的调用。新预检查先要求已有精确生成类型证明，未知项保守保留，避免新增虚回调。另补上未知 `FuncRef.is_valid()` 回调的失效通知，并将旧索引差分用例改用生产路径的生成分配器，以同时验证预填方法表和实际跳过空项。

缓存修复已完成全部 20 单元重编译；后续两个单元的位置变化被编译器的 coverage-mismatch 检查明确拒绝复用旧 PGO 数据。现已从最终一致源码重新进行完整计数构建、18 单元训练和正式构建，保留旧产物与失败日志。临时负例检查第一次链接误用了中文 DLL 路径，改为 ASCII 临时副本后成功复现；运行时未受影响。完整验证、再生成与 A/B 串行安排在最终构建之后，尚无可发布的速度结论。[复制负／正例](../output/_v1110/native_perf50/sparse_timer_bundle/copy_fix_preflight.json) · [额外回调负例](../output/_v1110/native_perf50/sparse_timer_bundle/metadata_purity_preflight.json)

最终候选 `4c14b0da…` 已完成与训练源码一致的全新 PGO。1,348 次生成分配开关检查、10 种阶段外未知回调、4 种角色复制、24 组索引／原遍历与 21 组饱和回退、数组别名和内联写入追踪均通过；额外 meta 调用降为零，原有 RNG／派发／容器／计时器回归和三场原版严格逐事件检查通过。固定 200 场输入与结果签名一致，704 份源码完整再生成两遍通过。[新训练来源](../output/_v1110/native_perf50/sparse_timer_bundle/fresh_profile_source.json) · [未知回调／复制](../output/_v1110/native_perf50/sparse_timer_bundle/sparse_external_callbacks_test.json) · [meta 无副作用](../output/_v1110/native_perf50/sparse_timer_bundle/metadata_purity_test.json)

三组各八对完整对照显示组合退化：CPU 耗时中位 **增加 5.37%**、累计增加 **7.72%**；墙钟中位 **增加 5.58%**、累计增加 **8.14%**，仅 1/24 对更快。三组 CPU 中位增加约 5.92%、4.61%、6.16%，墙钟增加约 5.68%、5.36%、6.48%；去掉任一组后累计仍反向。全程接电，后台负载 **1.06%–27.72%**，所有极端值保留。本组合不部署，未运行其 2,604 场发布验收及发布 24 批；组件保留，不能由组合反向认定各项均有害。[完整对照](../output/_v1110/native_perf50/sparse_timer_bundle/ab_assessment.json)

随后的诊断直接读取同一 DLL 已有的 TLS epoch，没有改变受测二进制：固定 200 场记录到 **462,029 次失效**，约为角色计时器阶段次数的 1.19 倍。计数包含装配、数组变更及回调，不能直接等同于重建次数。另一个小型反例证实，未经过生成分配器的普通 CoreContext，连续两次纯 getter 会造成两次失效，且没有缓存类型；经过预填的同类对象零失效，未知 C++ getter 仍正确执行两次并失效两次。这是维护路径可修正的误判，不是关闭未知回调保护的理由。下一候选在真正进入 getter／回调时只识别一次精确类型；资格预读仍对未识别的未来项保守保留，避免提前解引用占位对象。修正后重新直接测整个组合，当前运行时保持 `7af5ff94…`。[实际失效计数](../output/_v1110/native_perf50/sparse_timer_bundle/epoch_probe.json) · [普通 getter 反例](../output/_v1110/native_perf50/sparse_timer_bundle/known_getter_negative.json)

同时记录下一日志候选：addSpeed 当前无条件构造 trace_diag 参数，其中包含 getTopLeftCell 动态调用，不能简单删除。只有证明类型、参数及位置读取均无副作用且诊断关闭时才可省略；未知覆写、对象转字符串的实例 ID 副作用、位置对象 getter 和诊断开启路径都须保留。此项仅源码审视，未实现、未计入收益。[后续诊断参数审视](../output/_v1110/native_perf50/post_scan_bundle_profile/diagnostic_followup_review.json)

上述试验及反例已提交 `a2eb92d3`，远端备份 `8255e523`；704 份生产源码与已验收 `7af5ff94…` DLL／运行时清单再次核对原始字节一致。

### 稀疏索引失效分类修正（未合入，保留）

已实现前述修正：只在实际 getter／回调入口第一次遇到对象时解析精确 RTTI，缓存生成类型或未知类型结果。已识别的生成对象走原 getter，不再误报失效；真正未知或审计不符的对象每次进入仍先使索引失效。新解析也记录原来的惰性解析和未知类型诊断计数。资格预读保持原来的保守规则，未识别的未来项不会为了索引提前执行 RTTI／虚方法。普通未启用稀疏路径的上下文保持旧规则。

新候选继续包含先前已验证的复制清缓存、未知 meta 无额外调用、数组别名与内联写入追踪、原顺序回退及饱和／嵌套保护。相对上一个试验没有再改对象布局；相对当前部署版仍采用完整 20 单元重建与全新 18 单元 PGO。修改前已核对远端 `8255e523` 的生产源码／DLL。测试新增要求为普通未预填 getter 零误失效且缓存类型、预填 getter 零失效、未知 getter 保持两次调用与两次失效。正在构建，尚无新 A/B 结果，当前运行时仍为 `7af5ff94…`。[修正实现](../output/_v1110/prototype_native_sparse_timer_lazy_bundle.py) · [新组合测量方案](../output/_v1110/native_perf50/sparse_timer_lazy_bundle/evaluation_plan.json)

最终候选 `9e541820…` 完成新 PGO 和全部前置检查。普通 getter 零误失效且缓存类型，未知 getter 保持两次调用／两次失效；既有 1,348 次分配、复制、回调、元数据纯度、索引／原遍历、数组、RNG 及三场严格原版检查均通过。704 份源码再生成两遍一致。固定 200 场结果签名不变，epoch 失效数从 462,029 降至 **311,497**（约 −32.6%）；这不是重建次数或耗时收益。[getter 验证](../output/_v1110/native_perf50/sparse_timer_lazy_bundle/known_getter_test.json) · [实际失效计数](../output/_v1110/native_perf50/sparse_timer_lazy_bundle/epoch_probe.json)

完整三组各八对仍显示退化：CPU 中位／累计耗时 **增加 6.11%／6.08%**，0 对更快、1 对持平；墙钟中位／累计 **增加 6.48%／6.42%**，24 对全部更慢。三组中位均反向，去掉任一组后的累计仍反向；全程接电，后台负载 **1.06%–9.35%**。因此不部署，未跑该候选的 2,604 场发布验收或发布 24 批。保留全部组件与数据，不将计数改善当作实际提速。稀疏路径在当前回调／维护结构下优先级下降；下一轮从已部署版尝试分配时方法表预填与诊断参数省略，避免把它们的价值与这笔索引维护成本混为一谈。[完整对照](../output/_v1110/native_perf50/sparse_timer_lazy_bundle/ab_assessment.json)

已实现独立的 addSpeed 诊断参数原型，尚未编译／测速。它只对已证明无覆写的生成类型、普通有限 Vec2 坐标、纯参数、精确 Context／Rng／ItemData 及关闭的诊断生效；未知或开启路径保留整条原调用。特别保留先前未知 descriptor getter 修复未来坐标／RNG 字段的顺序，检查 descriptor 的纯度在预读位置数组之前。数值更新及两个后续 tooltip 快照均不改动。[原型](../output/_v1110/prototype_native_addspeed_trace.py) · [源码预检](../output/_v1110/native_perf50/post_scan_bundle_profile/addspeed_prototype_preflight.json)

### 方法表预填与关闭日志参数省略（独立组合，构建中）

已核对远端备份 `7da8b44d`，从当前验收版 `7af5ff94…` 直接组合 674 个生成分配器的方法行预填与前述 addSpeed 原型，未引入稀疏计时器索引、回调追踪或新对象布局。完整 20 单元计数构建及 18 单元全新 PGO 已启动；浮点选项不变。准备了 124 项日志开关／纯参数／自定义方法与 getter／对象格式化／同次调用修复未来字段的基线差分用例，以及 1,348 次生成分配开关用例，尚待执行。运行时未替换。

按用户补充的组合原则，单笔在噪声中不明确不作为淘汰理由；本轮对整个组合做三组各八对同批 A/B，保留全部负结果，以 CPU／墙钟、分组及去掉任一组的结果共同判断。若组合有效，只归因于组合；需要分配单笔贡献时再做逐项撤回对照，不累加旧百分比。组合也可能互相抵消或争用缓存，因此不以“数量更多”预设有效。确定性与发布门槛保持原要求。[组合实现](../output/_v1110/prototype_native_eager_trace_bundle.py) · [预先测量方案](../output/_v1110/native_perf50/eager_trace_bundle/evaluation_plan.json)

### 下一局部性组合原型（仅源码预检）

对同份部署版采样的热点指令复核发现，角色计时器阶段 323 个叶样本中，一个在读取宝石数组长度之后的 test 位置有 97 样本。附近依次读取物品、位于 `+0x648` 的计时器数组指针、计时器长度、位于 `+0x3e0` 的宝石数组指针及宝石长度。这支持尝试改善局部性，但单个采样位置不能直接证明缓存缺失或换算收益。旧 11 热字段布局未显示明确收益，保留其思路，现针对已经内嵌的计时器头重新组合。

新独立原型把 f_timers、f_gems 与原内嵌计时器头放近，使两个值和计时器长度有机会共处一个缓存行；另给桥接装配时 **setup 之后替换的** 宝石数组设置独立的一次性内嵌头。原 init_fields 宝石分配不变，原引用不会因替换／重初始化被复用；栈对象、外部上下文、非所属 arena、第二次装配仍创建独立头。保留原定时器与宝石遍历、长度捕获、回调和数值计算，无稀疏索引追踪。已通过完整 704 份输入校验和源码变换预检，并准备 43 项引用／生命周期／容量与布局检查；尚未编译执行，实际对象大小、偏移、A/B 收益及发布门槛均待验证。[原型](../output/_v1110/prototype_native_item_locality_bundle.py) · [证据与后续检查](../output/_v1110/native_perf50/post_scan_bundle_profile/locality_followup_review.json)

### 方法表与关闭日志组合结果（已部署）

最终正式 DLL 为 `444e75c6…`。全新 20 单元计数构建与 18 单元 PGO 后的源码校验曾因准备阶段递归 Python 语法检查生成五个缓存文件而停止；全部真实源码字节未改，记录并仅清理这五个新增缓存后复核完整源清单，复用已经完成的同源构建。初版边界用例还错误假定嵌套 gd_add 参数按描述符先于坐标求值，导致原版在无效坐标指针用例中崩溃。定位后改为有效坐标、由 getter 修复随后读取的 RNG，比较实际原表达式顺序，不修改候选代码。冻结 CPP 中对此顺序的旧注释不准确；安全条件实际要求未知 getter 一律回退，不依赖此顺序。后续原型在下次重建前修正该注释。[缓存拦截记录](../output/_v1110/native_perf50/eager_trace_bundle/python_cache_guard_incident.json) · [用例修正记录](../output/_v1110/native_perf50/eager_trace_bundle/harness_order_incident.json)

124 项新增日志／覆写／对象格式化／字段变更差分、1,348 次生成分配开关、1,624 项 Buff 与 40 项冷却标志检查通过，旧 RNG／派发／数组／计时器回归和三场原版定向通过。704 份源码完整再生成两遍一致。固定 200 场相对旧部署版省去 59,033 次惰性类型解析；关闭日志的纯路径实际命中，数值、ID、RNG、快照等均保持原结果，计数不作为提速结论。[日志差分](../output/_v1110/native_perf50/eager_trace_bundle/addspeed_trace_differential.json) · [构建来源](../output/_v1110/native_perf50/eager_trace_bundle/fresh_profile_source.json)

完整三组各八对 A/B 中 **24/24 对 CPU 与墙钟均更快**：CPU 中位／累计耗时下降 **4.1096%／4.1475%**，墙钟中位／累计下降 **4.5582%／4.1997%**。三组 CPU 中位下降 4.1096%、4.0000%、4.2857%，墙钟下降 3.5244%、4.4611%、4.9618%；去掉任一组后累计仍正向。全程接电，观测后台负载 **0.7848%–10.7436%**，原始样本全部保留。这证明本组合有可重复收益，不将收益分配给单个组件。[A/B 汇总](../output/_v1110/native_perf50/eager_trace_bundle/ab_assessment.json)

914 + 1,690 场原版严格逐事件全部通过，2,604 场与当前部署版及早期真值 C++ 事件哈希均一致，根仍为 `b8066c92…`，新旧类型审计不匹配均为零。一次连续 24 批原始吞吐中位 **175.7258**、最慢 **138.0912 场/秒**，全部超过 50；全程接电，后台负载 **1.6766%–19.9585%**。一次 24 批校准覆盖 **5.8223%–33.2496%** 负载，20% 拟合 **137.6948 场/秒**，R² 0.91364，交叉验证中位／P90 相对耗时误差 3.545%／6.784%。该拟合不代替原始吞吐门槛，也不把与旧版独立拟合的差当作代码收益；140 目标仍未达到。[全量验收](../output/_v1110/native_perf50/eager_trace_bundle/bundle_full_gate.json) · [逐场哈希](../output/_v1110/native_perf50/eager_trace_bundle/bundle_vs_deployed_hashes.json) · [吞吐和拟合](../output/_v1110/native_perf50/eager_trace_bundle/measurements_summary.json)

已经更新本地运行时，部署 DLL、源码目录 DLL、清单和验收 SHA 一致；正常训练入口 12 场无错误，另 12 项固定结果与基线一致。旧 `7af5ff94…` 运行时保留于 `dist/native_1_1_10_before_eager_trace_bundle_20261121`。下一轮以此正式版本为基线测局部性组合，先备份后构建。[部署与训练](../output/_v1110/native_perf50/eager_trace_bundle/bundle_installation.json)

本版已提交 `960daceb`，远端 `d4938c4e`，全部 704 份源码、DLL／清单及报告原始字节核对一致。随后从已验收 `444e75c6…` 启动局部性组合的完整 20 单元／全新 18 单元 PGO 构建。宝石头按 GdArr::create 原规则精确分配初始容量，不改为 reserve 的增长规则；桥接之后的 resize 和字段赋值保持原位置。43 项容量、别名、重初始化、复制、栈／其他 arena 与字节偏移检查将在正式比较前执行；新候选尚未完成构建或测速。当前运行时仍为本段已验收版。[下一组合预先方案](../output/_v1110/native_perf50/item_locality_bundle/evaluation_plan.json)

### 计时器／宝石局部性组合结果（已部署）

正式 DLL `8e7d5740…` 完成全量 20 单元计数构建及全新 18 单元 PGO。43 项容量／别名／重新初始化／复制／栈与不同 arena 生命周期检查通过，原有 124 项日志差分、1,348 次生成分配、1,624 项 Buff 和 40 项冷却标志等回归通过；704 份源码两遍完整再生成字节与时间戳一致。当前基线 `444e75c6…` 独立重采样取得 2,083 栈、2,079 个回放根，前三个叶节点仍为物品 physicsTick 160、主 physicsTick 139、角色计时器遍历 130。[新采样](../output/_v1110/native_perf50/post_eager_trace_profile/profile_depth64.json)

布局实测：CoreItem 大小 1,792 → 1,856 字节，C++ Item 与 Weapon 均保持 3,968 字节；f_timers／f_gems／内嵌计时器长度偏移为 1,600／1,624／1,656，共处一个缓存行，桥接宝石长度偏移 1,680。全部 674 种生成类型另以连续同型单对象分配验证实际大小：430 种物品类型各增 64 字节，其余大小不变。所有类型各取一个的非加权总量从 2,614,456 增至 2,641,976 字节，该量不是语料峰值内存。记录这一空间代价，不仅展示父类未增大的例子。[布局](../output/_v1110/native_perf50/item_locality_bundle/item_layout_offsets.json) · [全部类型大小](../output/_v1110/native_perf50/item_locality_bundle/all_layouts.json)

三组各八对 A/B：CPU 中位／累计耗时下降 **1.4389%／3.7077%**，17 对更快、6 对持平、1 对更慢；墙钟中位／累计下降 **1.2568%／3.5123%**，19 对更快。三组中位均正向，去掉任一组后累计仍正向；首组 −10.96% 至 +17.78% 的 CPU 极端波动全部保留，累计值受其影响，收益按约 1% 的中位量级理解。全程接电，后台负载 **1.0455%–23.7146%**，未要求每个组件单独显著。[完整配对](../output/_v1110/native_perf50/item_locality_bundle/ab_assessment.json)

原版 914 + 1,690 场逐事件通过，与当前部署版和早期真值全部 2,604 个 C++ 事件哈希一致，根仍为 `b8066c92…`，类型不匹配零。一次连续 24 批吞吐中位 **179.5952**、最慢 **144.5862 场/秒**，全部高于 50；全程接电，后台负载 **1.9471%–20.3746%**。一次 24 批校准覆盖 **6.2373%–28.6828%**，20% 拟合 **133.9979 场/秒**，R² 0.94382，交叉验证中位／P90 相对耗时误差 1.917%／4.704%。保留这一低于上轮独立拟合的结果，140 目标未达到，不重跑至有利值。[验收](../output/_v1110/native_perf50/item_locality_bundle/bundle_full_gate.json) · [吞吐／拟合](../output/_v1110/native_perf50/item_locality_bundle/measurements_summary.json)

为分辨独立拟合与代码效应，另一次固定 16 对受控负载对照使用旧 `444e75c6…` 与新 `8e7d5740…`。CPU 中位／累计耗时下降 **1.6247%／2.0027%**，13 对更快、2 对持平、1 对更慢；墙钟下降 **1.9446%／2.2979%**，15/16 对更快。全程接电，实际后台负载 **17.4352%–36.8010%**；这是区间内的配对证据，不宣称精确 20%，也不替代原 133.9979 拟合。保留本组合，在更高负载下也未观察到整体退化。[受控配对](../output/_v1110/native_perf50/item_locality_bundle/target_load_assessment.json)

运行时已部署，正常训练评估 12 场无错误，12 项结果与原版基线相同；部署／源码 DLL、清单、验收与测速 SHA 已复核。旧版保留于 `dist/native_1_1_10_before_item_locality_bundle_20261121`。下一组合优先将冷却标志也移入紧凑控制块以回收空间，再扩展已知类型的纯字段读取入口；分配＋初始化融合保留为后续候选。未知 getter、字段遮蔽和原属性入口的优先规则都必须先证明并定向验证，之后以整个组合重测。[部署](../output/_v1110/native_perf50/item_locality_bundle/bundle_installation.json) · [复核](../output/_v1110/native_perf50/item_locality_bundle/post_install_verification.json)

### 纯字段读取与紧凑控制块组合（已部署）

基线 `8e7d5740…` 已在远端 `ccecb628` 核对源码／DLL 后，完成本组合。32 个按生成代码调用频次选择的属性，按全部 674 类的实际字段与继承解析，得到 14 份共享字段表；112 个方法槽保持原解析，方法行从 665 调整为 667，674 个生成分配器的行号同步重算。非字段 own case 仍遮蔽父字段；Obj 的 resource_path 继续在原入口优先处理。未知 C++ getter 执行原虚回调一次，原先为空的内部缓存不会在回调前被填入未知标记。未缓存的已知类型只在实际属性读取入口用精确 RTTI 识别，不提前读取未来对象。[组合生成器](../output/_v1110/prototype_native_property_control_bundle.py)

冷却标志移入已有计时器／宝石控制块，仅改纯默认成员顺序，init_fields 语句及算式不变。CoreItem 回到 1,792 字节；计时器、宝石、计时器长度偏移为 1,536／1,560／1,592，冷却标志偏移 1,632，与桥接宝石长度同缓存行。全部 674 类实测，371 类各减 64 字节，其余不变；所有类型各一个的非加权总量 2,641,976 → 2,618,232 字节，不代表语料峰值内存。[布局与全部类型](../output/_v1110/native_perf50/property_control_bundle/all_layouts.json)

全量 20 单元计数构建及新 18 单元 PGO 的源码一致。674 个原虚 getter 函数体字节均未改变，作为独立测试真值；172,172 项字段值检查覆盖 22 组代表值、浮点位模式、指针与类型，7,826 项别名检查及 24 项边界检查通过，覆盖共享 metadata 的 C++ 覆写、空缓存、resource_path 优先、静态回调 false、禁用、复制／切片和错误缓存的审计先行。旧日志、RNG、计时器、容器及分配回归通过；704 份源码完整生成两遍通过。固定 200 场真实命中字段快路径 3,217,772 次，旧方法／FuncRef 命中计数与基线相同，类型不匹配零。[字段检查](../output/_v1110/native_perf50/property_control_bundle/property_test.json) · [原 getter 源码证明](../output/_v1110/native_perf50/property_control_bundle/getter_oracle_source_proof.json) · [覆盖](../output/_v1110/native_perf50/property_control_bundle/release_audit.json)

24 对合计 CPU 中位／累计耗时下降 **2.0686%／3.6228%**，17 对更快、4 对持平、3 对更慢；墙钟中位／累计下降 **2.4513%／3.1706%**，19 对更快。三组 CPU 中位为 2.7799%、5.8291%、0%，墙钟为 3.2595%、2.7282%、1.2499%；没有因第三组 CPU 持平而排除组合，去掉任一组后累计仍正向。所有波动保留，全程接电，后台负载 **0.8750%–14.0031%**。这是组合收益，不逐笔归因。[完整 A/B](../output/_v1110/native_perf50/property_control_bundle/ab_assessment.json)

914 + 1,690 场原版逐事件全部通过，全部 C++ 逐场事件哈希与部署基线及早期真值一致，根仍 `b8066c92…`；原事件内核及新行缓存类型不匹配均零。全量字段快路径实际命中 56,271,418 次。一次连续 24 批吞吐中位 **185.1269**、最慢 **139.3168 场/秒**，全部 ≥50，全程接电，后台负载 **2.2037%–19.3833%**。一次 24 批校准覆盖 **6.8268%–40.2692%**，20% 拟合 **139.7169 场/秒**，R² 0.96052，交叉验证中位／P90 耗时误差 1.755%／4.172%；保留首个结果，不将 139.72 四舍五入为目标已完成。[验收](../output/_v1110/native_perf50/property_control_bundle/bundle_full_gate.json) · [全量覆盖](../output/_v1110/native_perf50/property_control_bundle/full_type_audit.json) · [吞吐／拟合](../output/_v1110/native_perf50/property_control_bundle/measurements_summary.json)

已部署 DLL `14263d42…`，训练入口 12 场无错误、12 项结果匹配基线；源码／部署 DLL、清单和报告 SHA 全部复核。旧运行时保留于 `dist/native_1_1_10_before_property_control_bundle_20261121`。140 目标仍进行，下一组合选纯类型判定缓存与已知类型分配／初始化融合，继续保留默认初始化与 _init 的原顺序，不改数值算法。[部署](../output/_v1110/native_perf50/property_control_bundle/bundle_installation.json) · [复核](../output/_v1110/native_perf50/property_control_bundle/post_install_verification.json)

### 纯类型判断与对象初始化组合（构建中）

开始前核对当前远端 `eb898e2b…` 的 DLL `14263d42…` 和 704 份生产源码。674 个生成类的 meta 均为纯常量返回，metadata 父链与 C++ 继承一致；在已有精确类型方法行中附带 metadata 和八类高频祖先标记。实际类型判断处读取已缓存的精确证明；未知 C++ 覆写、未缓存、禁用及复制 metadata 保留原入口，错误缓存先审计再解引用，不增加未知 meta 回调。

已知全局 ClassMeta 的对象分配与 init_fields 合并为具体类型入口，使编译器有机会消除冗余初始化和间接调用。保留全部默认构造、方法行预填、字段初始化及原 _init 参数／调用顺序；复制／自定义 ClassMeta 即使 ID 相同也回退原分配器。只改内部方法行布局，GdObj、BattleCtx、ClassMeta 及物品布局不变。全部 20 单元计数构建和全新 18 单元 PGO 进行中；未得到速度结论，未部署。[实现](../output/_v1110/prototype_native_type_constructor_bundle.py) · [预先方案](../output/_v1110/native_perf50/type_constructor_bundle/evaluation_plan.json)

新增定向检查计划覆盖 674×674 类型判断、674 类在两种计时器头模式下共 1,348 次原／融合初始化的全部继承 GdVal 字段与引用关系、RNG／ID，以及未知 meta 回调和自定义分配／_init 顺序。随后沿用三组各八对单线程 AB／BA、2,604 场严格逐事件验收和单次发布／负载校准。按用户澄清评价整组累计收益，不要求单笔先达到显著性，也不由整组收益宣称各组件均有效。

### 类型判断与初始化组合结果（保留，不部署）

正式候选 `742ef705…` 完成同源 20 单元计数／全新 18 单元 PGO。454,276 项类型判断、1,348 次原／融合初始化、210,938 项递归字段状态和 2,039 项边界检查通过；别名、浮点位模式、RNG、实例 ID 与自定义回调顺序一致。旧字段／日志／容器／计时器回归、三场定向及 704 份源码两遍完整再生成通过。固定 200 场类型快路径 3,715,324 次、融合初始化 82,399 次，结果签名一致。[定向结果](../output/_v1110/native_perf50/type_constructor_bundle/type_constructor_test.json) · [构建来源](../output/_v1110/native_perf50/type_constructor_bundle/fresh_profile_source.json)

原三组 24 对的 CPU 中位耗时减少 0.4425%，墙钟中位增加 0.2699%，结论混合。按原路线允许的不明确结果追加一次独立八对，提前保存方案，保留原 24 对和所有极端样本，不再增加同条件组数。完整 32 对 CPU／墙钟中位减少 **0.4425%／0.1727%**，CPU 16 次更快、4 次持平、12 次更慢；墙钟 18 次更快、14 次更慢。累计耗时分别 **增加 0.8505%／1.4007%**。全程接电，观测后台负载 **5.9446%–46.0632%**。这是弱证据，不能因中位数刚转正就宣称可重复收益，也不能据此否定每个组件。[原 24 对](../output/_v1110/native_perf50/type_constructor_bundle/ab_assessment.json) · [追加方案](../output/_v1110/native_perf50/type_constructor_bundle/followup_plan.json) · [全部 32 对](../output/_v1110/native_perf50/type_constructor_bundle/ab_assessment_32.json)

为避免过早排除小收益，继续完成本组合 914 + 1,690 场原版严格逐事件核验，全部通过；逐场 C++ 事件哈希与当前部署一致，根仍为 `b8066c92…`，新旧类型审计均零不匹配。全量类型快路径 51,782,642 次、融合初始化 1,134,539 次，均零对应回退。[全量核验](../output/_v1110/native_perf50/type_constructor_bundle/bundle_full_gate.json) · [逐场哈希](../output/_v1110/native_perf50/type_constructor_bundle/bundle_vs_deployed_hashes.json) · [覆盖](../output/_v1110/native_perf50/type_constructor_bundle/full_type_audit.json)

单次连续 24 批原始吞吐中位 **132.2582**、最慢 **99.4551 场/秒**，全部超过 50；全程接电，后台负载 **8.9575%–27.7624%**。独立单次 24 批校准覆盖 **10.9375%–42.4127%**，20% 拟合 **128.8361 场/秒**，R² 0.92986，交叉验证耗时误差中位／P90 为 **3.693%／7.953%**。保留首份结果，不重跑至有利值；其与旧版独立拟合的差值不等于代码因果变化。[吞吐／拟合](../output/_v1110/native_perf50/type_constructor_bundle/measurements_summary.json)

随后只运行一次预先记录的固定负载 16 对 AB／BA，两条低优先级后台任务各 72% 占空比、120 秒交替预热。实际负载 **24.1416%–41.5749%**，因此不声称精确 20%。CPU 中位耗时减少 **0.0086%**、墙钟中位增加 **0.0424%**；累计分别增加 **0.5855%／0.6095%**，CPU 胜负 8:8、墙钟 7:9。全部样本保留，未确认有稳定收益。[固定负载方案](../output/_v1110/native_perf50/type_constructor_bundle/target_load_protocol.json) · [完整结果](../output/_v1110/native_perf50/type_constructor_bundle/target_load_assessment.json)

决定保留源码、DLL 和全部数据，暂不部署，也不再给同一候选追加测速组。当前运行时保持已验收的 `14263d42…`，140 目标继续进行。下一步重采样当前部署版，优先寻找能与保留组件组合、并减少实际间接调用或数据访问的改动。部署核对另补充逐场哈希原始文件备份和直接复算拟合，避免仅凭汇总状态判断完成。

当前部署版随后重采样取得 **2,023 栈、2,020 个有效回放根**。主要叶节点仍是物品 physicsTick 123、主 physicsTick 111、角色计时器 95；事件总线 emitAndLog 43、通用调用若干以及 get_prop 26 仍可见。沿调用链检查发现 Weapon.doCooldownEffect 的 attack 调用尚不在 112 个缓存槽中；useStamina 已在槽 111，不能把它误列为缺口。已按完整继承分析生成 16 项新方法候选，计划扩至 128 槽，保持旧 112 槽次序和全部派生覆写，并与纯字段覆盖扩展及保留组件合测。采样是提出假设，未换算成提速承诺。[新采样](../output/_v1110/native_perf50/post_property_control_profile/profile_depth64.json) · [方法缺口与完整新行](../output/_v1110/native_perf50/post_property_control_profile/hot_slot_gaps.json)

### 热点方法／字段覆盖扩展组合（构建中）

保留上一组未明确见效的类型判断与初始化组件，在同一 `14263d42…` 部署基线之上叠加 16 项热点方法和 32 项纯字段。方法槽 112 → 128，旧 112 槽次序与函数保持一致；属性槽 32 → 64，旧 32 槽解析保持一致，新增字段按实际生成读取频次选择。字段共享行 14 → 43，内部表有空间代价，GdObj／BattleCtx／ClassMeta／物品布局不变。全部 1,348 个原 getter／call_method 虚函数分发表保持原文，派生覆写、静态遮蔽及未知类型均保留原回退。128 是本轮增量选择，后续可按证据改用更宽索引增加槽数，不作为架构上限。[组合实现](../output/_v1110/prototype_native_hot_coverage_bundle.py) · [变换预检](../output/_v1110/native_perf50/hot_coverage_bundle/transform_preflight.json)

构建早期源码审查发现，新纳入的方法此前不会预填未知 C++ 接收者缓存，沿用旧统一派发入口则可能在原回调前写入空类型行。已停止明确识别的候选构建，保留其源码与日志；新增方法遇到未知类型时不写缓存、不新增回调，原有 112 个方法的缓存行为不变。修复后重新以最终源码进行完整 20 单元计数构建／新 18 单元 PGO，未复用旧采样。另加 16 个新方法的参数位模式、false 返回、绑定顺序、缓存可见性及 RNG 差分用例；字段检查改为按实际列数遍历，覆盖全部 64 槽。尚无正式测速结论，当前运行时仍为 `14263d42…`。[修复记录](../output/_v1110/native_perf50/hot_coverage_bundle/unknown_cache_guard_incident.json) · [新方法检查](../output/_v1110/test_native_hot_coverage.cpp)

### 热点覆盖扩展组合结果（已部署）

正式候选 `401376af…` 已完成最终一致源码的完整 20 单元计数与全新 18 单元 PGO。新增 1,344 项未知接收者／缓存可见性／参数位模式／false 返回／FuncRef 绑定及 RNG 差分通过；64 个属性槽覆盖 289,476 项字段值、13,158 项绑定／别名及 24 项边界检查，原虚 getter 作为真值。既有 454,276 项类型判断、1,348 次初始化、210,938 项递归字段及全部日志、容器、计时器、生命周期等回归通过。704 份源码完整再生成两遍字节与时间戳一致，全部 674 份对象头与部署基线原文一致，布局不变。固定 200 场实际新增方法命中 71,933 次、新增字段命中 1,164,624 次，原输入／结果签名一致。[新方法检查](../output/_v1110/native_perf50/hot_coverage_bundle/hot_coverage_test.json) · [字段检查](../output/_v1110/native_perf50/hot_coverage_bundle/property_test.json) · [正式覆盖](../output/_v1110/native_perf50/hot_coverage_bundle/release_audit.json)

三组各八对单线程 AB／BA 的 CPU 中位耗时分别减少 **2.8304%、1.4108%、0.9524%**，墙钟分别减少 **1.7955%、1.5007%、0.3874%**。完整 24 对 CPU 中位／累计减少 **1.9328%／0.3556%**，16 对更快、1 对持平、7 对更慢；墙钟中位／累计减少 **1.6319%／0.6082%**，19 对更快。去掉第一组后累计值小幅反向，全部波动保留，不能只展示更高的中位数；各组中位均正向，支持整个组合的小幅收益。全程接电，后台负载 **13.1202%–34.0881%**。这是在保留旧组件后新增覆盖的整体结果，不证明上一组每项均有效。[全部 24 对](../output/_v1110/native_perf50/hot_coverage_bundle/ab_assessment.json)

原版 914 + 1,690 场严格逐事件全部通过，全部 C++ 逐场事件哈希与部署基线一致，根仍为 `b8066c92…`；新旧类型不匹配零。全量新增方法／字段分别实际命中 **1,126,227／16,608,087 次**，类型路径 51,782,642 次、融合初始化 1,134,539 次，相关回退零。[全量核验](../output/_v1110/native_perf50/hot_coverage_bundle/bundle_full_gate.json) · [逐场哈希](../output/_v1110/native_perf50/hot_coverage_bundle/bundle_vs_deployed_hashes.json) · [覆盖审计](../output/_v1110/native_perf50/hot_coverage_bundle/full_type_audit.json)

一次连续 24 批吞吐中位 **119.3122**、最慢 **54.5465 场/秒**，全部超过 50；全程接电，后台负载 **10.4232%–60.7137%**。独立一次 24 批校准覆盖 **14.8574%–41.3270%**，20% 拟合 **114.9550 场/秒**，R² 0.90959，交叉验证耗时误差中位／P90 为 **2.205%／5.974%**。保留这份低值，不重跑至过线；历史 139.7169 与本次 114.9550 属于不同环境的独立拟合，不能直接视为代码退化。负载模型仍不能完全消除频率等未控制因素，140 目标继续进行。[原始 24 批与拟合](../output/_v1110/native_perf50/hot_coverage_bundle/measurements_summary.json)

针对独立拟合与同期 A/B 的差异，部署前只追加一次预先记录的固定负载 16 对。两条低优先级后台任务各 72% 占空比，交替预热 120 秒；实际后台负载 **29.1246%–40.6162%**，全程接电，不称为精确 20%。CPU 中位／累计耗时减少 **2.8987%／2.4091%**，12 对更快、4 对更慢；墙钟减少 **2.9134%／2.6011%**，13 对更快。这支持负载下仍有真实的组合收益，不覆盖原 114.9550 拟合，也不对同一候选继续追加测速组。[预先方案](../output/_v1110/native_perf50/hot_coverage_bundle/target_load_protocol.json) · [完整受控对照](../output/_v1110/native_perf50/hot_coverage_bundle/target_load_assessment.json) · [取舍](../output/_v1110/native_perf50/hot_coverage_bundle/composition_decision.json)

通过后原子部署到默认训练运行时及生产 C++ 目录，DLL 为 `401376af…`，旧运行时保留在 `dist/native_1_1_10_before_hot_coverage_bundle_20261121`。训练入口 12 场无错误、12 项固定结果与旧版匹配。部署后重新读取 2,604 份原始逐场记录、复算事件根与 20% 拟合，核对全部 704 份生产源码、DLL、报告与清单 SHA，均通过；当前目标状态仍为未达到 140。[部署](../output/_v1110/native_perf50/hot_coverage_bundle/bundle_installation.json) · [部署后复核](../output/_v1110/native_perf50/hot_coverage_bundle/post_install_verification.json)

本版已提交 `1a31f3b8` 并推送远端 `60963d08`，704 份生产源码、DLL、清单、原始逐场记录及本轮 8,988 份自有文件均逐字节核对。[备份记录](../output/_v1110/native_perf50/hot_coverage_bundle/checkpoint.log)

### 已证明纯读取的直接访问组合（构建中）

当前 `401376af…` 重采样取得 **2,023 栈、2,018 个有效回放根**，继续保留原固定 200 场。下一组合把已经证明只是返回 GdVal 字段的读取改为类型明确的直接字段访问；不改表达式、浮点运算、参数构造或物理帧。64 个已选属性共有 105 种实际字段绑定；128 个已选方法中，character、hasHit、getStacks、speed 的部分具体实现满足严格的纯字段返回模式，分别读取 CoreItem.character_、CoreDamageResult.hit、CoreBuff.current、CoreItem.speedScale。其他覆写继续走原函数，不能因方法名相同而跳过其逻辑。[新采样](../output/_v1110/native_perf50/post_hot_coverage_profile/profile_depth64.json) · [源码证明与绑定](../output/_v1110/native_perf50/typed_read_bundle/source_design.json)

用 44 份按 64 字节对齐的读取标签行，保留 43 份共享原 getter 函数表作为回退。每行的 64 个属性标签位于一个缓存行，具体字段访问使用合法的父类转换与成员访问，没有依赖多态对象的裸字节偏移。辅助表总量 22,016 → 27,648 字节，记录这一空间增加；不能只展示标签行大小从 512 减至 128。全部 16 份生成分片、674 份类头、上下文布局和旧 128 方法／64 属性槽均原文保持。未知接收者、关闭优化、字段遮蔽、FuncRef 参数绑定和审计先行规则保持原路径。[实现](../output/_v1110/prototype_native_typed_read_bundle.py) · [变换预检](../output/_v1110/native_perf50/typed_read_bundle/transform_preflight.json)

已在备份核对后启动完整 20 单元计数构建及后续全新 18 单元 PGO。新增方法检查先用未改动的原虚分派验证测试字段，再比较直接读取；覆盖全部 674 类、四个方法、各 GdVal 引用种类、NaN 位模式／有符号零／次正规数、绑定和别名，并检查标签实际对齐。目前尚无 A/B 收益结论，未部署本候选。

### 直接读取组合首轮结果（保留，准备叠加）

候选 `c0649c77…` 完成同源 20 单元计数与新 18 单元 PGO；61,344 项纯方法值检查、2,556 项字段绑定／别名及 674 项实际对齐检查通过，原虚方法先验证每次字段赋值作为独立真值。旧 289,476 项属性值、类型、构造、RNG、计时器、容器、生命周期等回归、三场严格定向及两遍完整再生成通过。固定 200 场实际直接属性读取 4,382,396 次、纯方法读取 1,109,188 次，输入和结果签名一致。[方法差分](../output/_v1110/native_perf50/typed_read_bundle/typed_read_test.json) · [正式构建覆盖](../output/_v1110/native_perf50/typed_read_bundle/release_audit.json)

完整 24 对中，CPU／墙钟中位耗时分别 **增加 0.5102%／0.5186%**，累计耗时则减少 **0.6216%／0.5806%**。CPU 9 对更快、3 对持平、12 对更慢；墙钟 12:12。三组 CPU 中位降幅为 +0.5102%、−1.0478%、−0.9615%，墙钟为 −0.5186%、+0.8806%、−4.3184%；全程接电，后台负载 7.6219%–32.8788%，全部样本保留。未确认稳定收益，不部署，也未继续运行本候选的发布全量验收／24 批；两个组件均保留，下一组合增加与原数值分支等效的局部算术入口后重新整体比较，不由这一混合结果认定每个组件无效。[完整 A/B](../output/_v1110/native_perf50/typed_read_bundle/ab_assessment.json)


### 局部算术入口：发布前发现并保留 NaN 差异

在直接读取组合上叠加 2,072 处局部算术入口（加 878、减 317、乘 447、除 430）；安全整数和有限数按原操作计算，溢出、非有限值、实数零除及非数值通过非 LTO 单元调用原求值器。首版 `993cd7ed…` 已完成新 20 单元计数和 18 单元 PGO，固定 200 场结果签名一致；计数中加法整数／实数命中 3,079,325／1,852,283 次、除法实数命中 421,168 次。

新增 5,903 项数值、容器、参数求值顺序、引用别名及 RNG 检查，在实际部署 DLL 与候选 DLL 之间发现 **12 项 NaN 位模式不一致**：只有两个操作数均为不同 NaN 的加法／乘法，LTO 对未修改的公开原求值器交换了指令操作数，改变了所选 NaN 载荷。候选内部新入口与其原函数相同并不足以证明跨版本相同，因此本版在正式 A/B 前终止，未部署，全部原始输出与源码保留。[失败记录](../output/_v1110/native_perf50/scalar_math_bundle/final_decision.json)

后继 `scalar_math_ordered_bundle` 仅为两个 Float NaN 的加法／乘法固定部署版操作数顺序，实际执行原种类 SSE 指令，保留 signaling NaN 引发的浮点异常，其他公开求值分支保持原文。先用实际部署 DLL 独立验证 72 项不同符号／NaN 载荷／quiet 与 signaling 组合，结果位和异常标志均一致，再启动全新同源构建；完整数值差分同时增加浮点异常标志检查。没有通过忽略 NaN 差异放宽确定性要求，也未据未测速版本宣称性能收益。[独立预检](../output/_v1110/native_perf50/scalar_math_ordered_bundle/baseline_nan_order_preflight.json)


### 局部算术叠加正式结果：明确退化，停止采用

修正后 `f3f5d947…` 的 5,903 项跨实际部署 DLL 数值／容器／参数求值／引用别名／RNG 差分全部通过，包含原位模式及所有浮点异常标志；72 项独立 NaN 载荷／指令顺序检查、既有完整回归、定向逐事件及两遍再生成通过。辅助反汇编检查先误匹配地址注释而失败，仅修正测试的完整函数标签匹配后复用原 DLL 和同源 PGO，失败日志保留，未改编译中的源码。

三组各八对固定 200 场单线程 AB／BA 全部退化：CPU 中位耗时增加 **4.7906%、6.5565%、9.4494%**，墙钟增加 **4.3900%、7.5545%、9.5996%**。合计 24 对 CPU 中位／累计增加 **6.5565%／6.1435%**，仅 4 对更快；墙钟增加 **7.1733%／6.7036%**，仅 3 对更快。全程接电，后台负载 **3.0968%–30.2498%**。不再追加同候选测速，没有启动发布用 2,604 场、原始／校准 24 批，生产仍为 `401376af…`。不能把退化单独归因于某一组件，但整组已无采用依据。[完整结果](../output/_v1110/native_perf50/scalar_math_ordered_bundle/ab_assessment.json) · [取舍](../output/_v1110/native_perf50/scalar_math_ordered_bundle/final_decision.json)

下一条路径回到每帧循环：既有相同固定 200 场计数显示 13,473,218 次物品扫描中仅 682,897 次物品或宝石含计时器，约 **5.07%**；该历史计数只作候选依据，将重新记录新路径的实际命中。先做无跨帧缓存的短路空段，再评估只在无回调的连续物品区间复用角色眩晕／共享速度增量；触发、冷却显示钩子、宝石方法及未知接收者均设边界，回调后的后续物品读取实时状态，禁止持久资格索引及全局无关数组失效维护。新实现先用已部署 DLL 作为独立原函数真值做局部差分，再花时间完整编译。


### 无回调区间角色状态复用与空计时器短路（新候选）

新实现 `frame_segments_bundle` 移除上轮算术内联，保留待叠加的纯读取组件；在每次物理帧的物品阶段，连续无回调的物品复用同一角色的眩晕判断和共享热／冷速度增量。首次访问延迟计算，不跨帧保存；触发、冷却进度钩子、宝石 character 方法、未知／停用／审计不匹配接收者、getSpeed 回退、角色物理回调及活跃宝石均清空。原 CoreItem.physicsTick 函数完整保留为独立真值，按原顺序读取并计算物品自己的速度和剩余冷却，回调后触发判断仍读取实时 triggerTime。

计时器循环增加八物品的空段短路；每项按原顺序检查自身与宝石计时器，遇到第一个可能调用回调的条目立即停止预读，整段回到原实时循环。保持原捕获长度及同帧新增／停用／数组替换、重排、扩容和嵌套调用，没有持久资格索引和数组失效维护。

完整编译前直接链接当前部署 `401376af…` 的原函数做本地差分：**6,912** 项角色区间测试通过，覆盖触发与进度回调修改热冷／眩晕／未来物品／角色引用／Buff 字典、未知 metadata 回调、递归阶段、宝石两种归属、关闭优化、审计、有符号／NaN 位和浮点异常及 RNG；**9,554** 项计时器短路测试通过，含同帧新增宝石／计时器、原始数组写入、当前段重排、替换、扩容、递归、回调前无效占位指针修复及 gem 内部回调修复。尚未有整场吞吐收益结论。[角色预检](../output/_v1110/native_perf50/frame_segments_bundle/frame_preflight.json) · [计时器预检](../output/_v1110/native_perf50/frame_segments_bundle/timer_preflight.json)

本轮同时保留已证明与当前部署相同的两个 NaN 操作数指令顺序保护；仅影响原公开加法／乘法的双 Float NaN，其他数值分支不做内联。正式构建仍须对实际部署 DLL 做 5,903 项数值位模式及浮点异常对照。全部 674 份对象头和上下文／容器布局不变，704 份源码清单不变，继续原固定 200 场三组 A/B、2,604 场逐事件及一次 24 批门槛。


后续候选补充：纯字段表可以尝试保存 `GdVal GdObj::*` 成员指针，通过标准 `static_cast` 从实际字段所有者转换后，在已核对精确类型的对象上应用 `object->*member`，从而省掉函数指针调用以及当前字段标签的二次分派。C++ 草案 [expr.static.cast 第 11 段](https://eel.is/c++draft/expr.static.cast#11) 允许向字段所属类的基类转换成员指针；[expr.mptr.oper](https://eel.is/c++draft/expr.mptr.oper) 要求实际最派生对象包含该成员。因此必须沿用原元数据精确行、未知接收者回退及审计先于行读取，禁止在缺少真实成员的对象上应用。该方案不使用多态对象 offsetof、整数偏移或裸字节读取；先用当前编译器验证所有所有者／遮蔽／继承／空成员指针与完整值差分。未实现、未测得收益，不能把假设计入当前成绩。可在本轮回调区间方案验收后再决定叠加，当前编译源码保持冻结。


本轮同源计数构建的固定 200 场结果签名保持原值。角色区间实际处理 3,633,579 次，眩晕状态复用 85.974%、共享速度增量复用 85.952%；触发边界 37,452 次、宝石 character 边界 101,234 次。计时器跳过 1,111,250 个八物品空段，8,890,000 次父物品原循环（65.983%）；但预检与回退合计 15,233,980 次父项资格读取，超过原 13,473,218 次，必须同时记录这一成本。不能把访问省略比例当成吞吐提升；仍待正式 PGO 版本的 A/B。[本轮计数与反向成本](../output/_v1110/native_perf50/frame_segments_bundle/count_interpretation.json)


### 路径复盘：停止机械叠加，围绕大热点推进

用户要求重新整理后，已在正式测速入口设置复盘边界；已有候选编译与正确性检查正常收尾，复盘期间没有启动 A/B、没有部署，也没有改编译完成的引擎源码。

当前运行仍为 `401376af…`。直接读取 `c0649c77…` 的 CPU 中位耗时 +0.5102%、结论不明确；算术内联组合 `f3f5d947…` +6.5565%、三组均退化，已弃用；当前 `fd7c6eb2…` 为无回调区间复用加空计时器段，已完成全新构建与 6,912／9,554／5,903 项新增差分，尚无正式吞吐结论。86% 状态复用只是访问计数，不是速度收益。

复盘发现两个关键偏差。第一，同一个 `401376af…` 在相邻两轮 A/B 中，基线自身的单线程中位吞吐约 **130.09 → 152.97 场/秒**，主线程 CPU 耗时 **1.515625 → 1.28125 秒／200 场**；两轮后台负载范围不同，不能把环境变化算成代码提升，更不能用旧 20% 拟合值代表当前性能。第二，2,018 个有效回放根采样中，物品 physicsTick 自身叶样本约 **7.19%**、角色计时器扫描叶样本约 **4.96%**；而触发及后续效果链包含约 **44.40%** 的样本，装配路径包含约 **17.69%**。包含子调用的比例互相重叠，不能相加；样本用于排优先级，不作为保守排除小收益的硬门槛。

执行收束为：先只给已经编译完成的候选一份既定 24 对结论，不再追加代码和 PGO；确有收益则完成原 2,604 场和 24 批发布门槛，退化则保留失败证据并结束这个组合，不继续机械叠加。随后主线转向一条明确的武器触发／伤害链，以当前 DLL 原函数作独立真值，先完成局部正确性和性能筛查，再投入完整编译。成员指针字段表等小型分派候选暂后置；小收益仍可合并，但要有同一热点或联合收益假设。逐事件一致、RNG 顺序、同帧可见性和原发布门槛继续保持。

本轮耗时问题来自试验顺序与范围控制：每个想法过早支付三十余分钟完整构建，且相互无关的组件混在一起。后续先证明值得投入的路径，再做完整验收；不把测试数量、编译次数或计数覆盖当作产出。[结构化复盘](../output/_v1110/native_perf50/frame_segments_bundle/path_review_result.json)


复盘后为已完成构建的 `fd7c6eb2…` 收尾：既定三组共 24 对，CPU 中位／累计耗时增加 **0.2092%／0.9375%**，墙钟增加 **0.2749%／1.1670%**；CPU 9 对更快、3 对持平，墙钟 8 对更快。三组 CPU 降幅 +0.6276%、−1.6914%、−0.2110%，没有确认组合收益。全程接电、后台负载 7.3720%–25.5864%。不启动发布全量／24 批，不部署，不追加同组合测速；保留组件与数据，主线按复盘切到触发／伤害链，不继续用访问复用比例替代提速结论。[完整对照](../output/_v1110/native_perf50/frame_segments_bundle/ab_assessment.json) · [取舍](../output/_v1110/native_perf50/frame_segments_bundle/final_decision.json)


### 新主线首个具体候选：伤害事件分发中的标识构造

从触发／伤害链追到 CoreEventBus.emitAndLog，发现存在监听器时会在原位置构造 `identifier + "/ot" + ownerType` 标识快照。原表达式先把整数格式化成字符串，再做两次字符串连接；即使关闭诊断也会执行，且回调可能中途开启诊断，因此不能简单取消或推迟快照。

本候选只在已缓存且审计相符的纯字段 getter、Str 标识和 Int 所有者输入上，把三次字符串对象构造合成一次，用同一字节哈希与终止零。has_method 检查、快照时点、日志开关检查、监听器遍历和原表达式回退保持；未知对象／非原始类型／审计不匹配继续执行原表达式。回调修改标识字符串底层数据时，已构造的结果仍保持原快照。仅修改原生 `shard_12.cpp`、`native_event_kernel.hpp`、`engine_wrapper.cpp`，674 份对象头、上下文布局、原算术代码及其他15个生成分片均不变；没有带入前几轮的字段标签、算术内联或计时器组合。

先链接当前实际 DLL 做低成本筛查，未完整构建：**24,288** 项整数边界、随机64位整数、空字符串／空指针、嵌入零、UTF-8、长标识及 RNG／对象 ID／浮点异常／结果快照差分通过；构造原语八对中位 CPU／墙钟降低 81.25%／82.21%，这个数字不能当成事件总线或整场收益。[原语记录](../output/_v1110/native_perf50/event_identity_probe/primitive_screen.json)

完整事件分发的局部测试先跑100,000事件／臂，约0.06CPU秒，线程时间15.625ms粒度过粗；保留首轮全部结果，并在运行前声明仅追加一次10倍长度筛查，场景大小仍为每场1,000事件。后续每臂1,000,000事件、八对AB／BA，CPU中位／累计降低 **11.9385%／10.8761%**（7/8更快），墙钟 **11.3252%／9.7954%**（6/8更快），线程周期 **11.2252%／10.3698%**（7/8更快）。这是可控事件分发样本，包含原分发函数、回调和场景构造，仍不证明整场收益；此后不再追加同局部候选测速。[短轮原始结果](../output/_v1110/native_perf50/event_identity_probe/bus_screen_initial100k.json) · [延长前方案](../output/_v1110/native_perf50/event_identity_probe/bus_screen_protocol.json) · [完整局部结果](../output/_v1110/native_perf50/event_identity_probe/bus_screen.json)

再以正确性模式扩至 **320** 项真实原函数／本地候选差分，覆盖绑定参数、追加和替换监听器、嵌套、同帧终局、双向切换日志标志、字段及底层字符修改、未知 emitter／descriptor getter 回调、非整数 owner、非字符串 identifier、空行缓存、审计错行、关闭优化及整数极值；完整回调记录、诊断内容、RNG、对象 ID、浮点异常和逐项结果哈希一致。仅在这些筛查通过后，才准备单一 `event_identity_bundle` 做固定200场正式A/B；正收益仍须原2,604场及24批门槛才能部署。[独立原版320项记录](../output/_v1110/native_perf50/event_identity_probe/bus_correctness_baseline.json) · [仅三份原生文件变更](../output/_v1110/native_perf50/event_identity_bundle/transform_preflight.json)


同源计数构建进一步核对实际频次：固定200场标识快路径 **34,193次**，回退0，平均170.965次／场，结果签名不变。这个频次远小于整个事件分发次数，不能把局部11.94%乘到整条触发链上；整场收益可能很小。当前候选保持冻结，仍由一次既定A/B判断，不因低频预估直接永久排除，也不追加组件。后续候选筛查应把“单次成本、实际频次、整场占比”一起放在完整构建之前。[实际频次](../output/_v1110/native_perf50/event_identity_bundle/frequency_evidence.json)


### 同一路径微收益叠加与计时分辨率

标识候选 `af3de945…` 的正式24对 CPU中位持平（11胜、6平、7负），累计减少 **0.2890%**；墙钟中位／累计减少 **0.2710%／0.2954%**（14胜）。三组CPU中位降幅0.6667%、0.7246%、0%，墙钟−0.2022%、1.0712%、−0.7533%；接电、后台负载2.2714%–12.5682%。不称稳定收益，也不永久排除已被局部证明有效的小组件；保留为同一事件路径的组合候选，没有部署，也不追加同候选A/B。[正式结果](../output/_v1110/native_perf50/event_identity_bundle/ab_assessment.json)

下一组件仅处理 CoreEventBus.getEmissionID：对已有有效缓存且无原生覆写的生成类，直接执行同一个非虚 get_instance_id；在实例ID读取后，对已证明不溢出的非负信号与ID直接组合；未缓存、未知C++、审计不匹配、非对象和数值边界继续原派发／原移位加法。信号整数转换的时点、实例ID分配次数及懒分配顺序保持。完整16分片确认没有生成类覆写该内建方法。**4,417** 项原DLL直接差分（含未知C++返回不同类型、false回退、ClassRef静态回调、已有／新epoch／大ID、空缓存、关闭优化、信号边界、无ctx指针）通过，原始结果、RNG、对象ID与异常标志一致；直接函数八对CPU中位降幅53.5714%、墙钟51.9479%，仅为函数筛查。[编号原函数筛查](../output/_v1110/native_perf50/event_emission_probe/emission_screen.json)

把两项放在同一个完整事件分发样本中，320项回调／日志／别名测试通过。八对每臂1,000,000事件的组合 CPU中位／累计降幅 **11.9844%／13.8365%**，墙钟 **11.6598%／13.4412%**，两项8/8更快。不能与上一轮不同环境的11.94%相减得出新增项贡献，也不外推成整场收益。[组合局部筛查](../output/_v1110/native_perf50/event_emission_probe/bus_screen.json)

旧单批CPU时间有大量约15.625ms步长与持平；为测量小收益，本组合在看到正式结果前声明：仍用同一固定200场、单线程、三组各八对AB／BA、120秒预热；每臂连续执行 **4批同样的200场**，用覆盖全部800场的外层CPU／墙钟计时，再除4报告每200场耗时，保留每批时长与完整结果签名。每批必须独立匹配原200场结果，正向中位门槛不放宽。原24批吞吐与20%校准继续使用原单批200场。新计时器的函数及隔离工作进程协议均已用实际基线验证4×200结果哈希、外层计时与归一化，原比较脚本保持不变。[方案](../output/_v1110/native_perf50/event_emission_bundle/evaluation_plan.json) · [工作进程验证](../output/_v1110/native_perf50/event_emission_probe/measurement_worker_smoke.json)

### 事件标识组合已取得整场收益并部署

候选 `b2018eb2…` 只合并上述标识快照与 emission ID 两项，未带入纯读取标签、算术内联或帧扫描候选。三组共24对，CPU配对中位／累计耗时减少 **1.9154%／1.4107%**（17胜、1平），墙钟减少 **1.4524%／1.2839%**（18胜）。三组CPU中位降幅 **2.2395%、1.5035%、1.5552%**；墙钟 **1.7363%、−0.1667%、1.4058%**。逐一去掉任何一组后，CPU及墙钟中位与累计降幅仍为正。全程接电，后台负载 **5.3846%–13.0901%**。所有4×200原始结果签名均匹配。这证明组合有效，不能单独证明两项各自的整场贡献；上一轮不明确的小收益没有被直接丢弃。[完整A/B](../output/_v1110/native_perf50/event_emission_bundle/ab_assessment.json)

完整 **914+1,690=2,604** 场原版逐事件验收通过，优化前后全部逐场C++事件哈希一致，事件根仍为 `b8066c92…`，类型审计不匹配为0。正式DLL另通过24,288项原语、320项真实事件总线及4,417项emission ID差分和原有回归／再生成检查。全量验收标识快路径663,207次、emission快路径2,550,578次。[逐事件门槛](../output/_v1110/native_perf50/event_emission_bundle/bundle_full_gate.json) · [事件哈希](../output/_v1110/native_perf50/event_emission_bundle/bundle_vs_deployed_hashes.json)

首份连续24批原始吞吐中位 **141.6948**、最慢 **106.6862场/秒**，全部通过50门槛；接电，后台负载 **5.0572%–26.4270%**。首份独立校准24批覆盖 **9.9834%–56.0456%**，20%负载拟合 **106.2633场/秒**，R² 0.93607，交叉验证耗时误差中位／P90 **5.118%／10.538%**。保留第一份结果，不重跑挑高值；不同轮的负载拟合仍受频率、温度及负载类型影响，不能用141.69或历史拟合值宣称20%负载140目标已达成，代码收益以同期A/B为据。[全部发布测量](../output/_v1110/native_perf50/event_emission_bundle/measurements_summary.json)

已原子部署默认运行时和生产C++源码，DLL SHA-256为 `b2018eb28b90ae5527d9e0764a8b11e5bf6df0b60df7cb722c67629fcfedb588`。旧4013运行时保存在 `dist/native_1_1_10_before_event_emission_bundle_20261121`。正常训练入口12场无错误、结果与旧版一致；部署后重读704份生产源码、674份未改类头、全部逐场事件记录、报告和运行时清单，并复算校准值，通过。[部署后复核](../output/_v1110/native_perf50/event_emission_bundle/post_install_verification.json)

后续执行顺序保持收敛：先备份本次已验收状态，再对新DLL重采样；从触发／伤害链选一条有自身成本证据的路径，先测实际频次和局部成本，确定值得投入后才完整编译。既有失败及不明确结果保留，不继续对同一候选反复测速；小改动可围绕同一热点叠加，由整体A/B确认。负载模型用于解释环境波动，不能消除全部环境影响，也不作为挑选部署版本的替代指标。

本版已提交 `068785f2` 并推送备份 `674fff4f`；704份生产源码、DLL和本轮6,893份自有文件均与备份逐字节核对。用户原有三份已跟踪改动保持原状。新DLL固定200场重采样取得 **2,080个有效回放根栈样本**，标签位置函数包含42个样本，仍只作为候选排序依据。[备份](../output/_v1110/native_perf50/event_emission_bundle/checkpoint.log) · [新采样](../output/_v1110/native_perf50/event_emission_bundle/profile_depth64.json)

### 同一效果链的冗余诊断构造组合（尚待整场测速）

在已部署 `b2018eb2…` 上，仅为 CoreItem.getNextFreeLabelPosition 的一处诊断，以及 CoreBuff 中六处 `_blnd_snap` 参数构造增加纯读取守卫。日志关闭、上下文／RNG为已缓存且审计相符的实际生成类、所有待略过的参数均无副作用时才省略。标签时间戳遍历、更新和原两次RNG调用完整保留；630份非Gem物品方法行逐项证明 character() 只是返回字段，Gem覆写、未知对象／getter、非原始标识／所有者、审计错行和关闭原生派发均走原代码。

Buff参数仅略过 Null、Bool、Int、Str及原格式器会进入整数分支的精确整数Float。使用位检查识别后者；分数、大数、无穷和NaN继续原格式化，以保留浮点异常。对原DLL以四种舍入模式进行 **40,036项**此类Float格式化异常检查，均无异常；40,036是已命中安全输入的检查次数，不是所有Float位模式的穷举。未知TemporaryStacks.amount getter及回调中切换日志的情况保持原表达式。

完整编译前，实际部署DLL作独立真值：标签 **2,048项**状态／RNG／日志／未知getter／覆写／位值／异常差分通过，八对每臂500,000次局部函数CPU中位耗时降低 **8.3333%**、墙钟 **10.7661%**；CPU4对更快、其余受计时粒度影响，墙钟8对更快。Buff六处诊断 **20,736项**差分通过，八对每臂600,000次纯诊断表达式CPU中位耗时降低 **95.4545%**、墙钟 **94.6673%**，均8对更快。后者只测诊断表达式，不能外推成Buff函数或整场提升；保留首份全部结果与首个标签helper源码快照。[标签筛查](../output/_v1110/native_perf50/lazy_diagnostics_probe/screen.json) · [Buff筛查](../output/_v1110/native_perf50/lazy_diagnostics_probe/buff_screen.json)

组合只改三份原生文件，674份类头、上下文布局、其他分片、公开算术和已部署事件标识优化保持。三份变换及生成分片语法预检通过，之后才进入同源20单元计数／新18单元PGO。计数构建将记录七处实际略过与保留次数；正式收益仍由固定200×4、三组各八对AB／BA决定，原2,604场与首份24批发布门槛保持。[变换预检](../output/_v1110/native_perf50/lazy_diagnostics_bundle/transform_preflight.json)

### 诊断组合正式结果与当前目标核验

发布DLL为 `593acaf3d6bf1dfedc7926cc5f3659c074a285dd95a9dcf0db95c1f913077670`，保持同源20单元计数、新18单元PGO及原浮点选项。固定200场实际略过标签诊断77,135次、保留1,802次；Buff六处略过2,130次、保留708次。六处Buff的实际频次较低，不能用局部95%降幅外推到整场；标签路径也只有基线42/2,080的包含样本。保留这份反向成本证据，后续应尽可能在完整编译前取得实际频次。[实际频次](../output/_v1110/native_perf50/lazy_diagnostics_bundle/frequency_interpretation.json)

首份24对CPU中位／累计耗时减少 **0.5190%／0.3024%**，墙钟减少 **0.1432%／0.2004%**。因组间有分歧，按原路线“结果不明确时再做一组独立对照”，在运行前仅声明一次额外8对，既有24对全部保留，不重跑发布24批或负载校准。合计32对CPU中位／累计减少 **0.5190%／0.9467%**（18胜、3平、11负），墙钟减少 **0.1432%／1.2223%**（17胜、15负）。接电，背景负载 **3.8498%–43.3747%**。[追加前方案](../output/_v1110/native_perf50/lazy_diagnostics_bundle/followup_plan.json) · [完整32对](../output/_v1110/native_perf50/lazy_diagnostics_bundle/ab_assessment_32.json)

证据强度需明确：四组CPU中位降幅依次 **−0.5449%、+0.9631%、+0.5190%、−1.6159%**，墙钟 **−0.3892%、+0.2647%、+0.3079%、−2.5948%**，有两组反向。逐一去掉任意一组后，CPU中位及CPU／墙钟累计降幅仍为正，但一项墙钟中位为−0.0540%。按事先声明的整体CPU／墙钟正中位门槛采用这个小组合，不称为大幅或各组稳定一致的收益，也不继续追加测到满意；保留全部反向样本与取舍。[取舍及局限](../output/_v1110/native_perf50/lazy_diagnostics_bundle/composition_decision.json)

当前候选完成 **914+1,690=2,604场**原版逐事件验收，全部逐场C++事件哈希与部署基线一致，事件根 `b8066c92…` 不变，类型不匹配为0。实际发布DLL的标签函数及六处guard表达式另与独立旧DLL的2,048／20,736份原始逐项结果哈希核对；全部旧属性、构造、分派、容器、计时器、RNG及两遍源码再生成检查通过。保留的旧计划文件有历史注释，已另列具体纠正与本轮适用范围，未改原测量或验收门槛。[严格门槛](../output/_v1110/native_perf50/lazy_diagnostics_bundle/bundle_full_gate.json) · [范围复核](../output/_v1110/native_perf50/lazy_diagnostics_bundle/candidate_scope_review.json)

首份连续24批原始吞吐中位 **178.9487**、最慢 **120.1241场/秒**，均高于50；接电，后台负载 **3.0736%–29.5859%**。首份独立24批校准覆盖 **7.2949%–76.5672%**，20%负载拟合 **149.9734场/秒**，R² **0.96472**，交叉验证耗时误差中位／P90 **3.665%／8.594%**。本次校准点估计已超过100／125／140目标；不把前轮106.2633到149.9734的变化算为代码提速，也不保证任意未来后台任务都能达到该值。负载与CPU时间仍无法完全消除频率、温度和负载类型的影响。[首份发布与校准数据](../output/_v1110/native_perf50/lazy_diagnostics_bundle/measurements_summary.json)

已原子部署默认训练运行时及生产源码，旧b201运行时位于 `dist/native_1_1_10_before_lazy_diagnostics_bundle_20261121`。正常训练入口12场无错误、固定结果全部与旧版相同。部署后重读704份生产源码、674份类头、2,604份逐场事件记录、全部4×200原始A/B结果、报告与清单SHA；另通过Windows实际已加载模块路径确认默认训练读取的确为新593a DLL，独立复算32对统计及20%拟合均通过。[部署后复核](../output/_v1110/native_perf50/lazy_diagnostics_bundle/post_install_verification.json) · [目标逐项核验](../output/_v1110/native_perf50/lazy_diagnostics_bundle/goal_completion_audit.json)

### 2026-11-22：成员指针与独立角色状态复用组合

按新的优化目标，以已发布593a为基线、已核对远端备份c9bebb76为源码保障，启动 `member_frame_bundle`。43份纯属性表改存标准C++数据成员指针，保留64槽、元数据行、审计先行及未知对象回退；同步调整事件标识快路径的三个纯字段读取。角色状态复用单独取出原先的回调区间组件，明确不包含空计时器段、读取标签、全局NaN保护或算术内联。物品原physicsTick函数、公开算术、674份类头和对象／上下文布局保持原文。

完整构建前，链接实际593a DLL验证674类、6,579个字段绑定、125,001项值与原虚getter／原函数getter差分、6,579项容器别名；成员指针8字节，GdVal仍24字节。独立角色区间组件通过6,912项原DLL差分，覆盖回调变更、嵌套、宝石、RNG、数值位与异常标志。组合后的三个相关生成分片语法检查通过。尚未测得整场收益；随后使用同源20单元计数／新18单元PGO、固定200×4的三组各八对单线程AB／BA，保留原2,604场逐事件和首份24批吞吐门槛。只有审阅通过后才部署。[成员预检](../output/_v1110/native_perf50/member_frame_bundle/member_preflight.json) · [区间预检](../output/_v1110/native_perf50/member_frame_bundle/frame_preflight.json) · [本轮方案](../output/_v1110/native_perf50/member_frame_bundle/evaluation_plan.json)

首轮组合d3c47cdf完成正式PGO、全部新旧回归及两遍再生成。既定24对CPU中位／累计耗时减少0.3656%／0.3752%，墙钟中位增加1.6654%、累计减少0.9854%；CPU12胜、墙钟11胜。三组CPU中位降幅+3.7614%、−2.3532%、−2.2044%，墙钟+3.0271%、−0.5104%、−2.7175%，未确认组合收益。接电、后台负载14.7896%–65.8494%，所有样本保留，未启动发布全量／24批，未部署。下一轮保持同一593a基线，只保留成员指针组件进行拆分验证；不据混合结果排除两个独立组件，也不反复重测同一个组合直到过线。[组合完整结果](../output/_v1110/native_perf50/member_frame_bundle/ab_assessment.json) · [拆分方案](../output/_v1110/native_perf50/member_only_bundle/evaluation_plan.json)

成员指针独立候选 `6cb258ec…` 的24对CPU中位／累计耗时减少 **0.5498%／0.4007%**（15胜、1平），墙钟减少 **0.6082%／0.3337%**（15胜）。三组CPU中位降幅−0.1748%、+0.1901%、+1.9056%，墙钟−0.1806%、+0.4717%、+1.6944%。接电、后台负载3.9646%–9.9798%。收益较小且有组间差异，去掉第三组后累计耗时会反向；按原整体正中位门槛采用，不称为大幅稳定提速，也不继续追加直到满意。[完整对照](../output/_v1110/native_perf50/member_only_bundle/ab_assessment.json)

该候选通过全部2,604场原版逐事件验收，逐场事件哈希与593a一致，类型审计不匹配0；首份24批吞吐中位172.6070、最慢136.4461场/秒，接电、后台负载1.4921%–14.7320%。独立首份24批20%负载拟合142.7264场/秒，覆盖8.3261%–33.8268%，R²0.87215，误差中位／P90为3.635%／7.707%，不与旧149.9734拟合直接作代码比较。已部署本地默认训练运行时和生产源码，SHA-256为 `6cb258ec1baf335d3bc8e9da1538b2edd8aee87669b05249728f4829b1c47785`；正常训练12场结果与旧版一致、无错误，部署后复核704份源码、674份未改类头、全部逐场事件和报告清单哈希通过。GitHub v0.6.1发布附件保持原593a，本次未改已发布版本。[发布测量](../output/_v1110/native_perf50/member_only_bundle/measurements_summary.json) · [部署复核](../output/_v1110/native_perf50/member_only_bundle/post_install_verification.json)

对角色区间组件补做持久场景成本筛查：每臂200万次、两种预先声明工作负载各八对，原DLL与局部helper的状态位及异常标志一致；墙钟中位降幅6.2648%／6.2904%，周期中位7.2221%／6.4483%。CPU时间粒度过粗，分别持平／显示29.17%降幅，不能把后者当可靠收益；该场景也存在跨DLL调用与本地内联可见性差异，不代表整场速度。[完整局部数据](../output/_v1110/native_perf50/member_frame_bundle/frame_cost_screen.json)

### 角色状态复用相对成员指针版本的增量验证

以已部署6cb为新基线，单独比较增加角色区间复用后的效果。将该变换作用于6cb源码后，核对全部709份源码字节均与既有d3候选及其原同源PGO清单完全相同，因此直接复用d3 DLL和原PGO证据，省去重复编译。仍重新执行全部新旧回归、两遍再生成和预先声明的三组24对；此对照回答“在成员读取版本上增加角色复用是否有效”，不是重复d3对593直到过线。首次混合结果完整保留，不与这次百分比相加。[逐字节复用证明](../output/_v1110/native_perf50/frame_ablation_bundle/candidate_reuse_proof.json) · [增量方案](../output/_v1110/native_perf50/frame_ablation_bundle/evaluation_plan.json)

24对CPU中位／累计耗时减少 **0.6803%／0.3802%**（14胜、3平），墙钟减少 **0.6243%／0.5380%**（16胜）。三组CPU中位降幅+0.3401%、+0.5156%、+0.6973%，墙钟+0.6300%、+0.4846%、+1.3020%，三组方向一致；逐一去掉任一组后，中位及累计降幅仍正。接电，后台负载4.4533%–11.4406%。属于小幅、方向较一致的增量收益。[全部A/B](../output/_v1110/native_perf50/frame_ablation_bundle/ab_assessment.json)

重新完成2,604场原版逐事件验收，与6cb的逐场C++事件哈希全部一致，事件根仍b8066c92，类型审计不匹配0。首份24批吞吐中位168.0505、最慢130.9852场/秒，接电、后台负载3.2226%–21.6738%；首份校准24批20%拟合128.9055场/秒，覆盖7.3081%–27.9846%，R²0.87075，误差中位／P90为3.357%／6.663%。保留这份低拟合值，不与此前142.7264或149.9734直接作代码比较。[发布测量](../output/_v1110/native_perf50/frame_ablation_bundle/measurements_summary.json)

通过后已部署本地默认训练运行时和生产源码，当前DLL为 `d3c47cdfe1b3218e7936cc02f706e8452464c1420c5e1fe4bf6963f2e3844c14`，包含成员指针和独立角色状态复用，未包含空计时器段、字段标签或全局NaN保护。正常训练12场无错、结果与6cb一致；部署后复核全部源码、674份未改类头、原始逐场事件和运行时清单哈希通过。GitHub v0.6.1附件仍为593a。[部署复核](../output/_v1110/native_perf50/frame_ablation_bundle/post_install_verification.json)

当前d3重采样取得2,002个原生栈、1,999个有效回放根；角色复用函数已内联进CoreCombat，不能把函数叶样本搬移当作提速幅度。装配仍含约399/1,999的样本，字典操作与格子查询仍出现；另发现classAttackSoundCount每次两次重建固定职业音效计数字典，包含26个样本，适合下一轮先做常量查表的局部筛查。[最新采样](../output/_v1110/native_perf50/frame_ablation_bundle/profile_depth64.json)

### 静态集合数值消费者折叠（新候选）

以已备份03d2f106的d3为基线，先严格匹配CLASS_SOUND_COUNTS构造表达式：7个整数职业键各有3个固定数值。只对职业Int且在0..6的attack／round数值读取直接查表，round的胜负参数仍先按原顺序转Bool，其他键种类、范围和关闭派发保持完整原表达式。全局字典返回接口不变，不引入共享可变字典。另核对getStacks=[100]+range(101,108)+range(108,111)、三个直接静态调用绑定及函数源码，将只取size的numStackTypes折叠为11，返回数组的接口保持原样。

实际d3 DLL独立真值的13,440项差分通过，覆盖40种输入／边界、四种舍入模式、开关、数值位、浮点异常、RNG及实例ID状态。预先声明的两个局部函数场景各八对，墙钟中位降幅98.6540%／97.6741%，周期98.6406%／97.6645%；CPU候选臂低于15.625ms粒度，显示100%中位降幅，不能作为可靠百分比，更不能外推整场。全部首份结果及测试源码快照保留。[独立局部筛查](../output/_v1110/native_perf50/static_collections_probe/screen.json)

组合只改shard_02、shard_06与诊断计数导出的engine_wrapper三个CPP文件，没有改类头、上下文、公开算术或已部署两项优化。生成阶段逐字核对纯构造形状；两个修改分片的语法预检通过后进入同源20单元计数／新18单元PGO，正式收益尚待原固定200单线程A/B，不提前部署。计数将分别记录attack、round和numStackTypes实际命中次数。[变换预检](../output/_v1110/native_perf50/static_collections_bundle/transform_preflight.json)

### 静态集合折叠正式结果（已部署）

固定200场计数：attack 8,587次、round 200次、numStackTypes 59,977次；因此省去140,592次音效字典对象构造、492,072次字典set及299,885个取长度用的临时数组头。此为实际工作量，不等同耗时收益。两个数值消费者以实际旧DLL保存的13,440份独立结果为真值，正式DLL差分通过；旧字段／回调／计时器／RNG等回归及完整源码两次再生成通过。

相对d3的固定200×4、三组共24对AB／BA：CPU配对中位／累计耗时减少 **2.0308%／1.6254%**，21胜1平2负；墙钟减少 **2.2849%／1.8882%**，20胜4负。三组CPU中位降幅1.5054%、2.5022%、1.8523%，墙钟1.8030%、3.0256%、1.0545%；逐一去掉任一组后中位和累计仍均正向。全程接电，后台负载4.6279%–13.9321%，全部首份正反数据保留。[完整对照](../output/_v1110/native_perf50/static_collections_bundle/ab_assessment.json)

原版914+1,690场严格逐事件全部通过，全部逐场C++事件哈希与d3一致，根仍为b8066c92，类型不匹配0。首份连续24批中位 **150.9226**、最低 **130.4157场/秒**，接电、后台负载4.8310%–24.3556%；原50场/秒部署门槛通过。首份独立24批校准覆盖11.2655%–43.2470%，20%负载拟合 **143.1494场/秒**，R²0.89130，交叉验证耗时误差中位／P90为2.698%／7.314%。不把此前128.9055到本次143.1494的独立拟合差当成代码收益。[全量验收](../output/_v1110/native_perf50/static_collections_bundle/bundle_full_gate.json) · [首份发布测量](../output/_v1110/native_perf50/static_collections_bundle/measurements_summary.json)

已部署本地默认训练运行时和生产源码，DLL SHA-256为 `541238b57e2e18ce258a0afa9f548115761da28f4a1c119812277b4c0dae2983`；旧d3运行时保留于 `dist/native_1_1_10_before_static_collections_bundle_20261121`。正常训练入口12场无错误、固定结果与旧版一致；部署后复核704份生产源码、674份未改类头、2,604份原始逐场事件、全部A/B与24批数据、运行时清单和校准复算，通过。GitHub v0.6.1附件仍为原593a，不改已发布附件。[部署后核验](../output/_v1110/native_perf50/static_collections_bundle/post_install_verification.json)

用户将20%负载换算目标提高为 **200场/秒**，后续每轮明确报告该口径。按本轮点估计，达到目标需要吞吐再提高约39.7%、每场耗时再降低约28.4%，作为选路尺度，不是精确预测。当前目标尚未达到。新DLL采样2,015栈、2,014个有效回放根：互斥归属触发链855、物品／宝石装配366、其余帧内683、其余初始化／导出110；字典与哈希叶样本131，通用方法叶样本88，TLS运行库叶样本59。采样百分比不是可优化收益上限。已按当前代码及既有失败记录重新展开45项候选，详见[下一阶段优化评估](C++模拟器下一阶段优化评估.md)。

### 纯静态属性与固定装配表组合（构建中）

以远端209b5711已核对的5412为基线。674个生成类逐项解析，34类共144个原始直接枚举／类引用／数值／布尔／Vec2字面量分支在getter访问TLS前返回原表达式，其余属性，包括可变数组、字典和字符串，完整保留原分配及回退。类头、上下文布局、容器布局和公开算术不改。

同步证明CoreConst的stack序列100..110及枚举长度20／6／4；两个无参指标数量消费者折叠为14和80，只遍历的stack／颜色数组改为同序整数循环。setup的两张Buff表仅在独立、空且从未分配存储的原生字典上批量构造，最终entries容量16、桶容量32、插入顺序、存储哈希及桶顺序与原来一致。预留、清空后复用、非空、别名、数组、未知对象等情况仍按原顺序逐项写入；关闭优化继续完整原循环。描述符getter修改未来表字段的情形保留同次调用可见性。

实际旧5412 DLL作独立真值的6,436项差分通过：覆盖674类的227个自有静态属性及每类两个未知属性、返回值和失败时out保持、可变返回容器独立性、完整setup的15种表／getter变体、开关、四种舍入模式、浮点异常及RNG。首份两个局部场景各八对，墙钟中位耗时减少44.6947%／71.8742%，周期41.1096%／71.5099%；前者用导出的原常量访问器模拟省去TLS，而正式候选直接返回原字面量，不混称同一机器码。后者四对基线CPU时间为零，CPU中位不报告，所有原始数据保留；汇总脚本因除零失败后只重算首份原始记录，没有重跑测速。测试源快照保留，后续仅为字典别名比较补上Kind守卫，实际发布函数仍需逐项匹配原6436份哈希。[局部筛查](../output/_v1110/native_perf50/static_setup_probe/screen.json)

14份修改CPP的语法预检通过，远端备份、源码和本地DLL核对后才开始全量20单元计数／新18单元PGO。固定200×4、三组各八对AB／BA和原发布门槛不变；目前没有整场收益结论，没有部署本候选。[源码预检](../output/_v1110/native_perf50/static_setup_bundle/transform_preflight.json) · [正式方案](../output/_v1110/native_perf50/static_setup_bundle/evaluation_plan.json)

### 纯静态属性与固定装配表正式结果（已部署）

正式DLL为 `00cbcf9d9467feab8d8d99aa437683af507c5f924ee90a9b9f076b661d5c6a60`，实际生产getter、setup及指标方法的6,436份逐项结果哈希与独立旧5412 DLL一致；既有成员读取、角色复用、类型、容器、计时器、事件及RNG等回归全部通过，674份类头和公开算术不变。完整704份源码再生成两遍一致，未知编辑保护通过。计数构建固定200场：批量初始化14,933次、有序回退0次、指标数量折叠74,910次、颜色遍历14,933次；它们用于确认实际覆盖，不当成速度收益。[实际覆盖](../output/_v1110/native_perf50/static_setup_bundle/frequency_interpretation.json) · [正式DLL独立差分](../output/_v1110/native_perf50/static_setup_bundle/static_setup_tests.json)

首份固定200×4、三组共24对单线程AB／BA：CPU配对中位／累计耗时减少 **4.8913%／5.0721%**，23胜1负；墙钟减少 **5.3947%／4.9628%**，23胜1负。三组CPU中位降幅5.0403%、4.8388%、5.0621%，墙钟5.5324%、5.7623%、4.7062%；逐一去掉任一组后的中位及累计仍均正向。全程接电，后台负载3.5507%–10.7048%。保留完整首份正反样本，不把组合收益逐项拆分或与历史百分比相加。[完整24对](../output/_v1110/native_perf50/static_setup_bundle/ab_assessment.json)

原版914+1,690=2,604场严格逐事件全部通过；优化前后全部逐场C++事件哈希相同，根仍b8066c92，类型不匹配0。全量实际批量初始化202,616次、指标数量折叠1,272,643次、颜色遍历202,616次。[全量验收](../output/_v1110/native_perf50/static_setup_bundle/bundle_full_gate.json) · [逐场哈希](../output/_v1110/native_perf50/static_setup_bundle/bundle_vs_deployed_hashes.json) · [实际覆盖](../output/_v1110/native_perf50/static_setup_bundle/full_type_audit.json)

首份连续24批原始吞吐中位 **215.7776**、最低 **188.3602场/秒**，全部超过50门槛；接电，后台负载3.1444%–12.3591%。首份独立24批校准覆盖6.2961%–32.9539%，20%负载拟合 **170.3125场/秒**，R²0.89702，交叉验证耗时误差中位／P90为3.971%／5.713%。当前20%目标仍未达到200；215.78是原始低负载中位，不能代替该目标口径。此前143.1494到本次170.3125属于独立环境拟合，不将差额算作代码收益，代码收益依据同期A/B。[发布测量](../output/_v1110/native_perf50/static_setup_bundle/measurements_summary.json)

通过全部门槛后已部署本地默认训练运行时和生产源码，旧5412保留于 `dist/native_1_1_10_before_static_setup_bundle_20261122`。正常训练入口12场无错误，固定结果与旧版一致。部署后重读704份生产源码、674份未改类头、所有原始事件／A/B／24批记录、四项新计数及运行时清单，独立复算20%校准并核对SHA，通过。GitHub v0.6.1发布附件保持原593a。[部署后核验](../output/_v1110/native_perf50/static_setup_bundle/post_install_verification.json)

下一轮按45项审视的结构主线，优先研究武器触发／伤害链的定型入口与事件／监听器表示；开始前先推送本次已验收源码与DLL并核对远端，再依据新DLL采样选择一条纵向闭环。静态getter与setup这一包已经完成，不继续对同包重复测速。

部署版新采样取得2,037栈、2,033个有效回放根。触发链包含825个样本，武器doCooldownEffect375、事件总线emitAndLog342；主要叶节点为物理帧241、角色计时器122、事件总线51、相等比较41、运动队列36。通用调用到intern_sym有21个叶样本，可作为同一效果链内的候选；包含样本互相重叠，不相加为收益。保存新采样及互斥阶段汇总，供下一轮选择路径。[新采样](../output/_v1110/native_perf50/static_setup_bundle/profile_depth64.json) · [可复算汇总](../output/_v1110/native_perf50/static_setup_bundle/brainstorm_profile_summary.json)

### 行为路由与事件回调链扁平化（构建中）

以远端1bf22370已核对的00cb为基线，沿伤害触发链处理两个具体的间接调用段。第一项为CoreItem的九项SELF_BEHAVIOR_METHODS：对已有精确类型行的生成对象，用单独只读方法表解析最派生实现，省去临时白名单数组及has_method／callv重复解析；仍执行同一个原方法体。674类的call_method和has_own_method父链均证明无副作用，另逐项证明现有缓存行的metadata确实属于对应类，防止把共享代表行用于新方法覆写。静态遮蔽、未知／未缓存对象、关闭路径、审计错行以及符号重登记均保留原回退。行为对象非Null也走完整旧分支。

第二项在事件总线的native_event_funcv处，对无绑定参数、已缓存且命中的FuncRef直接调用原函数指针；参数数组仍以相同data／len传入，保留原FuncRef／非空／argc条件后才读取args[0]。有绑定、未知、未缓存、失效引用及未覆盖方法全部回退原call_funcv，不改变FuncRef对Object builtin的原Null规则。原方法表128槽、对象、上下文、FuncRef布局及全部674份类头不改；原方法体、算术、帧阶段、RNG及回调顺序不改。没有引入新的事件记录表示，也不是重写整条伤害算法。

实际旧DLL的初版310,440项差分通过，覆盖646个物品类、30种参数、冷／热缓存、开关、四种舍入、未知C++／错行、绑定与重绑定、符号重登记、返回位和旧派发计数。随后增加60项调用外壳边界，原310,440份哈希不变。审查发现原gd_eq会先比较String存储哈希，初版只比较长度和字节会对异常哈希给出不同判断；已用独立旧DLL负例复现，保留反例及旧初版源码／测速。修正版保留相同存储哈希判断及短路，新增31,104项不一致哈希、同长度另一白名单哈希、以及因哈希不匹配而不应读取的数据指针用例；最终 **341,604项**通过，原310,500份逐项哈希仍一致。[反例](../output/_v1110/native_perf50/dispatch_chain_probe/hash_negative.json) · [修正版局部检查](../output/_v1110/native_perf50/dispatch_chain_probe/screen_hash_guard.json)

完整构建前声明修正版仅跑一份同样的局部8对，不覆盖旧记录、不反复重测同一源码。修正版行为／回调两个局部场景墙钟中位耗时降低 **65.5116%／8.5814%**，周期 **66.1813%／8.5538%**。两场景分别有4／1对基线CPU时间为零，因此CPU中位不报告；首版55.0081%／17.0981%的局部墙钟结果也完整保留，但不能外推整场或把两次环境差异归因于哈希修正。正式吞吐仍待固定200×4、三组各八对AB／BA。[修正前首份筛查](../output/_v1110/native_perf50/dispatch_chain_probe/screen.json) · [修正版首份筛查](../output/_v1110/native_perf50/dispatch_chain_probe/screen_hash_guard.json)

四文件变换和gd_rt／物品／事件总线三个编译单元的语法预检通过后，启动全20单元计数／新18单元PGO，最高两项低优先级编译任务。正式DLL须与独立旧DLL的全部341,604份结果哈希匹配，再进入原整场门槛。当前部署仍为00cb，20%负载170.3125场/秒，200目标继续；本候选尚无整场收益，未部署。[正式预检](../output/_v1110/native_perf50/dispatch_chain_bundle/transform_preflight.json) · [本轮方案](../output/_v1110/native_perf50/dispatch_chain_bundle/evaluation_plan.json)

### 行为路由与事件回调正式结果（已部署）

正式DLL为 `39c559a0bc4ef04f89444be63b42b842884a7d2fee1d59c4332fcdc7367d8e0b`。实际生产方法和回调头文件的341,604份逐项结果哈希与独立旧00cb DLL一致；原属性、成员读取、角色状态复用、常量／装配、容器、计时器、RNG、ABI和两次完整再生成等检查通过。补充源码核对证明：九种行为中原128槽已覆盖的目标均与新解析的最派生方法完全一致；构建冻结源码没有因补充断言发生变化。[生产差分](../output/_v1110/native_perf50/dispatch_chain_bundle/dispatch_chain_tests.json) · [补充源码证明](../output/_v1110/native_perf50/dispatch_chain_bundle/additional_source_proof.json)

计数构建固定200场：实际直达行为17,807次、行为资格查询57,618次、扁平回调100,900次，空行为短路0次。这里只统计命中，不将局部65%／8%的降幅外推整场，也不按“空行为”假定收益。[频次与边界](../output/_v1110/native_perf50/dispatch_chain_bundle/frequency_interpretation.json)

首份三组共24对固定200×4单线程AB／BA：CPU配对中位／累计耗时减少 **1.6878%／1.4080%**，18胜1平5负；墙钟减少 **2.0715%／1.5056%**，19胜5负。三组CPU中位降幅2.4845%、1.8855%、0.2041%，墙钟2.0207%、2.3184%、1.1141%；逐一去掉任何一组后，中位及累计降幅仍均正向。接电，后台负载3.3960%–10.4063%。全部原始正反数据保留，以组合判断，不分别归因。[全部24对](../output/_v1110/native_perf50/dispatch_chain_bundle/ab_assessment.json)

914+1,690=2,604场原版严格逐事件通过；所有逐场C++事件哈希与00cb相同，根仍b8066c92，类型不匹配0。全量行为直达275,579次、资格查询777,809次、扁平回调2,143,020次。原六项派发总计数也与00cb逐项相同，确认未靠少调用取得收益。[全量门槛](../output/_v1110/native_perf50/dispatch_chain_bundle/bundle_full_gate.json) · [逐场事件](../output/_v1110/native_perf50/dispatch_chain_bundle/bundle_vs_deployed_hashes.json) · [旧计数核对](../output/_v1110/native_perf50/dispatch_chain_bundle/legacy_counter_equivalence.json)

首份连续24批原始中位 **211.9797**、最低 **173.6292场/秒**，全部超过50；接电，后台负载0.5504%–22.9600%。首份独立24批校准覆盖5.1733%–25.0687%，20%负载拟合 **171.7714场/秒**，R²0.87732，交叉验证耗时误差中位／P90为2.163%／6.498%。保留首份拟合，不将原始中位211.98视为达到20%负载200目标，也不把与上轮170.3125的独立拟合差额当作代码收益。[发布测量](../output/_v1110/native_perf50/dispatch_chain_bundle/measurements_summary.json)

全部门槛通过后已部署本地默认训练运行时及生产源码；旧00cb保留于 `dist/native_1_1_10_before_dispatch_chain_bundle_20261122`。正常训练入口12场无错误、固定结果与旧版一致。部署后重读704份源码、674份未改类头、原逐事件／A/B／24批记录及新增四项计数，复算20%模型并核对DLL／清单／报告SHA，通过。GitHub v0.6.1附件仍保持原593a。[部署后复核](../output/_v1110/native_perf50/dispatch_chain_bundle/post_install_verification.json)

新DLL采样2,043栈、2,042个有效回放根；主要叶节点为物理帧250、角色计时器133、事件总线54、运动队列43、通用调用克隆38、相等比较37、入包联动34、格子查询30。下一轮优先审视装配空间查询中的重复查找与稳定去重，兼顾帧内热点；先读现有实现并验证局部成本，不直接恢复旧全局失效索引或旧算术内联方案。[新采样](../output/_v1110/native_perf50/dispatch_chain_bundle/profile_depth64.json) · [互斥汇总](../output/_v1110/native_perf50/dispatch_chain_bundle/brainstorm_profile_summary.json)

### 空间查询合并与稳定去重（正式构建中）

以远端69cab46b已核对的39c5为基线，仅改shard_13中的getItemsInCells、countItemsInCells及getBagsInCells。精确原生Dict将has与紧接的索引合为一次find_index；不命中、空指针、关闭原生路径或其他接收者保留原语义。未知has回调可替换网格字段，回退仍从同一活字段读取后续索引。去重只对Obj采用同种类对象指针比较，其他值继续gd_in；保持首次遇见顺序、输入长度快照、未来元素变化和placed getter的原位置。所有对象／容器布局、算术、RNG、方法路由与帧阶段保持原样；没有引入坐标缓存或全局写监视。

实际旧39c5 DLL独立真值的11,760项局部差分通过，覆盖三方法、原生／通用与计数开关、四种舍入、整数／负零／非整数／NaN坐标、混合值、空与未知接收者，以及placed回调改写／删除／清空网格、替换字段、改写或追加输入、嵌套查询。对照返回值、可变状态、原派发和容器计数、RNG／实例ID状态、浮点异常。首份四场景各八对、每臂100,000次：墙钟配对中位耗时降低37.0951%、22.0518%、52.7338%、54.6387%；周期降低37.1157%、19.4406%、53.2972%、54.6294%。这是局部合成查询结果，不外推为整场收益。[局部原始结果](../output/_v1110/native_perf50/spatial_probe/screen.json) · [原DLL逐项真值](../output/_v1110/native_perf50/spatial_probe/correctness_baseline.json)

单文件变换与完整分片语法检查通过，已核对远端704份源码与部署DLL后开始同源20单元计数／新18单元PGO，最高两项低优先级编译任务。正式候选须先匹配上述11,760份独立结果及全部旧回归，再进入固定200×4、三组八对AB／BA；正向后才做2,604场逐事件、24批和20%负载校准。当前部署仍为39c5、20%换算171.7714场/秒，本候选尚无整场收益或部署结论。[预检](../output/_v1110/native_perf50/spatial_bundle/transform_preflight.json) · [正式方案](../output/_v1110/native_perf50/spatial_bundle/evaluation_plan.json)

### 空间查询正式结果（已部署）

正式DLL为 `3a9269887ace0ad9cd6dafdb9e0ee2a77b857b231f2a0d412888af2516e5b520`。实际三项生产方法的11,760份结果哈希与独立旧39c5 DLL逐项一致；原派发／容器计数、字段与角色状态复用、旧行为路由、容器、RNG等回归和两次704份源码再生成均通过，674份类头未变。固定200场实际执行652,011次合并查询、命中242,572次、对象指针去重242,467次、通用回退0次；不把频次直接当作收益。[生产差分](../output/_v1110/native_perf50/spatial_bundle/spatial_tests.json) · [实际覆盖](../output/_v1110/native_perf50/spatial_bundle/release_audit.json)

首份固定200×4、三组共24对单线程AB／BA：CPU配对中位／累计耗时降低 **1.0685%／0.7783%**，17胜2平5负；墙钟降低 **0.8135%／0.4270%**，18胜6负。三组CPU中位降幅0.8529%、0.4283%、1.7316%，墙钟0.7233%、0.5263%、1.0786%，方向一致。去掉第三组后的墙钟累计降幅为−0.0307%，说明累计证据较弱；该子集的配对中位仍为正。按预先声明的整体配对中位标准采用，不增设事后门槛或选择性重测，不分别归因给两项修改。接电，后台负载3.2929%–11.2207%，全部首份正反结果保留。[24对完整结果及敏感性](../output/_v1110/native_perf50/spatial_bundle/ab_assessment.json)

914+1,690=2,604场原版逐事件全部通过，逐场C++事件哈希与39c5全部相同，根仍b8066c92。全量合并查询9,008,725次、命中3,360,453次、对象去重3,358,915次，原六项派发总计数逐项不变，类型不匹配0。[全量门槛](../output/_v1110/native_perf50/spatial_bundle/bundle_full_gate.json) · [逐场事件](../output/_v1110/native_perf50/spatial_bundle/bundle_vs_deployed_hashes.json) · [原计数核对](../output/_v1110/native_perf50/spatial_bundle/legacy_counter_equivalence.json)

首份连续24批原始吞吐中位 **211.6717**、最低 **142.5113场/秒**，均超过50门槛；接电，后台负载1.2749%–34.1704%。首份独立24批校准覆盖6.5090%–29.1120%，20%负载拟合 **172.5261场/秒**，R²0.93102，交叉验证耗时误差中位／P90为2.222%／4.925%。200目标尚未达到；不把此前171.7714到本次172.5261的独立拟合差额视为代码收益。[发布测量](../output/_v1110/native_perf50/spatial_bundle/measurements_summary.json)

通过后已部署本地默认训练运行时及生产源码，旧39c5保留于 `dist/native_1_1_10_before_spatial_bundle_20261122`。正常训练12场无错误，结果与基线一致；部署后复核704份源码、674份类头、全量逐事件及原始A/B／24批数据、四项新增计数、运行时清单和20%模型重算通过。GitHub v0.6.1附件继续保持原593a。[部署后核验](../output/_v1110/native_perf50/spatial_bundle/post_install_verification.json)

部署后新采样2,028栈、2,027个有效回放根；互斥归属触发链826、其余帧内721、装配370、其余初始化／导出110。字典／哈希叶样本67、通用方法77；物理帧254、角色计时器120、事件总线47、格子查询40、运动队列31。内联及采样波动会搬移叶节点，不把单个函数样本变化当回归或收益。采样包装脚本第一次因缺少模块搜索路径在实际采样前退出，日志保留，补上路径后首份完整采样通过；没有重跑正式测速。下一轮转入14／54的定型武器触发链，空间直接坐标索引与运动队列保留。[新采样](../output/_v1110/native_perf50/spatial_bundle/profile_depth64.json) · [可复算汇总](../output/_v1110/native_perf50/spatial_bundle/brainstorm_profile_summary.json)
