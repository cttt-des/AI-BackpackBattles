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
