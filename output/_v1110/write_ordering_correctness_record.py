"""Write the deployment record only from completed receipts."""
import json
from prepare_ordering_correctness import REPO,WORK,sha
def main():
    def read(n):return json.loads((WORK/n).read_bytes())
    installed=read('installation.json');post=read('post_install_verification.json');assert installed['passed'] and post['passed']
    speed=read('measurements_summary.json');fit=read('bundle_load20.json');gate=read('complete_correctness_gate.json')
    body=f'''# C++ 模拟器排序与事件派发修复记录（2026-11-27）

已完成现用 C++ 和 Python 内核的排序、事件派发修复，完整验证后部署到 `dist/native_1_1_10`。其他性能优化暂停。本次是正确性修复，不以相对旧错误行为的加速作为部署条件。

## 修复范围

- C++ 通用 `sort_custom_stable` 保留原有导出符号，内部改为 Godot 3.6 的 SortArray；Python `_sort_custom` 与实际 `_rt.pyd` 同步修改。等值排列和比较器调用次序均与原版一致。默认专用开战排序保持既有实现。
- C++ 公共普通路径、原生路径，以及复制了原生循环的字面量参数快速路径，均改为读取当前监听数组长度。追加到尚未遍历位置的监听器本次执行，缩短数组后停止访问尾部，嵌套仍然同步执行；终局仍立即退出。
- 维护中的转译器、事件优化器和完整版本锁定生成流程同步修复。两个完整重生成循环均复现 710 个 C++ 文件，重复运行字节和 mtime 不变，未知修改在写入前拒绝。
- 674 个对象头文件和所有对象布局保持不变，上一版已接受的优化保留。

## 原版对照与回归

原版证据来自本地 1.1.10 解包游戏源码及真实 Godot 3.6 可执行文件。事件总线执行原始游戏方法；药水和腰带使用提取的原始控制流，仅隔离视觉、随机 buff/清理服务。隔离测试验证调用次序，完整事件语料另行验证整场行为。

| 检查 | 结果 |
|---|---|
| 排序 | 256 组，0–512 项，最终排列及每次比较器调用逐项一致；C++ 正式 DLL、编译 Python、Python 源码均通过 |
| 动态事件派发 | 18 场景，覆盖普通／原生／字面量参数路径及 Python；追加、缩短、删除当前或未来元素、替换、数组重分配、连接表清空、嵌套、延迟冲刷、终局均对照原版 |
| 药水 | 12 个基础场景、6 个腰带和嵌套连锁场景、17 项同优先级双瓶实际药水案例均通过 |
| 默认开战 | 60 组真实洗牌和优先级排序，两侧均检查，不注入激活终序 |
| Python 整场 | 当前六套阵容重新生成 30 场 Godot 内核基准，修复版 30/30 一致，旧编译版 0/30；旧缓存零可比较行的失败记录保留 |
| Python 数值／RNG | 46,702 项修复前后观测哈希一致，部署后新进程复验通过 |
| 原版完整语料 | 914 + 1690 = 2604 场逐事件通过；顺序事件根 `{post['ordered_event_root']}` |
| 构建和运行 | 完整 20 单元插桩、重新收集 18 份 profile、18 热单元正式 PGO/LTO；原有浮点选项不变；训练器 12 作业、正式部署后新进程检查通过 |

完整正确性流程共 {gate['all_declared_steps']} 个步骤。保留所有定向矩阵及旧失败记录，不删除与旧错误行为不一致的用例。

## 旧测试预期的修正

旧事件测试把“追加监听器等待下一轮”当成真值。320 个事件身份用例中的 32 个追加／替换用例因此变化：新回调及其对应诊断必须出现；其余 RNG、对象 ID、浮点异常及未受影响日志均通过精确旧契约投影检查。

计时器矩阵中的 16 个用例调用带副作用的自定义排序，比较器返回 null、每次创建一个计时器。真实 Godot 对 8 项调用 14 次比较器并保持输入次序；旧稳定排序的比较次数不同。保留全部 1760 例，更新这 16 个状态及其中 8 个启用计数的预期，其余旧哈希保持；正常编译参考与正式 PGO 继续逐项比较。

私有快照矩阵保留全部 234880 例，其中 14336 个追加／替换场景更新到 Godot 语义；字面量参数矩阵保留 5184 例，其中 192 个追加场景更新。其余旧结果不变，正式版与正常编译的修正参考逐项一致。

武器链矩阵保留全部 136128 例：135136 个未受影响用例继续严格采用独立旧 PGO 结果，992 个追加监听器用例采用原版 Godot 派发语义和修正后的正常编译参考。另发现正常编译参考与两份 PGO 输出在 56 个未受影响用例上不同；旧／新 PGO 在这 56 项完全一致。该三方差异完整留档，未将正常编译的差异当成修改未受影响用例真值的理由，未跳过任何用例。详见 `weapon_normal_build_difference.json`、`weapon_chain_tests.json` 和原始全向量。

首份候选在复核中发现字面量快速路径遗漏，没有部署。其源代码、DLL、失败测试和 profile 全部保存在 `ordering_correctness_bundle_revision1`；最终候选补齐第三份循环并重新正式构建。所有预期调整都有对应 correction 记录和原始失败输出。

## 部署与速度记录

正式 DLL SHA-256：`{installed['dll_sha256']}`。上一版 DLL：`{installed['previous_dll_sha256']}`。回退运行目录：`{installed['backup_runtime']}`；源文件回退字节在证据目录 `installation_before`。

保留唯一一轮 raw24 和独立校准24，固定 200 场输入与结果签名不变。原始中位 {speed['serial']['median_fights_per_second']:.2f} 场/秒，最小 {speed['serial']['minimum_fights_per_second']:.2f} 场/秒；按照当前经验公式统一折算到 20% 负载为 {speed['fitted_fights_per_second_at20']:.2f} 场/秒（{'外推' if fit['reference_is_extrapolation'] else '插值'}）。这些数据只记录当前版本速度，不声称其比旧版更快，也不因没有直接测到 20% 而弃用修复。

证据目录：`output/_v1110/native_perf50/ordering_correctness_bundle`。维护入口和部署 DLL 逐字节绑定到通过验证的候选，部署后重新检查全部 2604 场原版事件凭据和实际安装字节，并执行新进程 Python 对照及训练器检查。

## 边界

本轮部署覆盖现用 native 和 `gd_core_py` 内核；已经退出默认内核列表的 `simulator/item.py` 旧引擎未纳入本次发布，其此前记录的药水顺序问题仍是旧入口已知限制。更广泛的数组迭代审计暂不展开。没有取得反馈对应的具体战斗输入，不能将这些已修复问题称为该反馈的唯一根因。

沿用 `codex/native-perf50-verified` 既有备份引用，没有创建新分支，没有移动工作区 HEAD 或改动用户暂存条目，也没有覆盖用户已有的原版 Item.gd、根 DLL 和性能输出。
'''
    note=REPO/'docs/C++模拟器排序与事件派发修复记录_2026-11-27.md';assert not note.exists();note.write_text(body,encoding='utf8',newline='\n')
    audit=REPO/'docs/C++模拟器同帧事件与药水触发顺序核查_2026-11-27.md'
    with audit.open('a',encoding='utf8',newline='\n') as stream:stream.write('\n## 修复后续（2026-11-27）\n\n现用 C++／Python 排序及三条 C++ 派发路径已完成修复、原版对照、完整 2604 场验证和部署。完整证据、旧错误测试的更正与边界见《C++模拟器排序与事件派发修复记录_2026-11-27.md》。上文保留的是修复前核查结果。\n')
    print(note)
if __name__=='__main__':main()
