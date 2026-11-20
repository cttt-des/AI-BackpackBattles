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
