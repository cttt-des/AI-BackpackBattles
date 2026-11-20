"""Preserve all measurements without changing the running simulator."""
import json
from pathlib import Path
import sys
import subprocess

WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
REPO=WORK.parents[3]
sys.path.insert(0,str(STAGE))
from compare_native_serial import summarize

reports=['buff_context_ab.json','buff_context_ab_repeat.json']
rows=[row for name in reports for row in json.loads((WORK/name).read_bytes())['pairs']]
reason='Both initial groups increased main-thread CPU time, satisfying the predeclared futility condition'
baseline='58383a1158e951d7aae8b4d4c34df4d52332446156946d31a488f5dff323ec39'
candidate='781176d0012d0b08c9da8e28874a16ea52546911b734a8b2260c47a8d4a8d8f5'
for name in reports:
    assert summarize(json.loads((WORK/name).read_bytes())['pairs'],'main_thread_cpu_s')['median_reduction_pct']<0
pooled={'baseline_dll_sha256':baseline,'candidate_dll_sha256':candidate,'pairs':len(rows),
        'source_reports':reports,**{field:summarize(rows,field) for field in ('main_thread_cpu_s','wall_s')},
        'all_samples_retained':True,'early_reject_reason':reason}
(WORK/'buff_context_ab_pooled.json').write_text(json.dumps(pooled,indent=2)+'\n',encoding='utf8',newline='\n')
record={'kind':'rejected_candidate_runtime_unchanged','dll_sha256':baseline,'candidate_dll_sha256':candidate,
        'changed_native_files':[],'reason':reason,'boundary_cases_matched':444,'rng_draws_matched':133,
        'full_2604_gate_run':False,'raw_24_gate_run':False,'deployed':False,'default_generator_wired':False}
(WORK/'buff_context_installation.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf8',newline='\n')
publisher=(WORK.parent/'cycles15/publish_verified_snapshot.py').read_text('utf8').replace('79dbf3b2547eb45b28d9b3e97046f3e0bc77f0ef','c7b62a281d4c3a840225769eedeeb81409a32451')
(WORK/'publish_verified_snapshot.py').write_text(publisher,encoding='utf8',newline='\n')
doc=REPO/'docs/C++模拟器性能优化清单.md'
text=doc.read_text('utf8')
assert '### 第十六轮' not in text
text+='''

### 第十六轮（未替换运行时）

仍以第十一轮 `58383a11…` 为基线，已核对远端备份 `c7b62a28` 的 DLL 和 699 份源码／构建文件。候选仅改两个 C++ 单元：在原生回放入口建立可嵌套、异常安全的调用域，在 CoreBuff.gainTemporary 首次实际读取上下文时确认精确 CoreContext 类型；15 处属性读取改为直接读取六个当前字段。每次仍检查接收者身份，回调替换上下文后恢复原 getter，不缓存字段值，外部 C++ 调用继续原路径。未改头文件、浮点表达式、RNG 或回调顺序；重新训练两个改动单元的 PGO。[候选脚本](../output/_v1110/optimize_native_buff_context.py) · [设计约束](../output/_v1110/native_perf50/cycles16/buff_context_design.json) · [备份核对](../output/_v1110/native_perf50/cycles16/verified_baseline.json)

基线与候选 444 组转换、计时器、状态、RNG 及 getter 顺序对照相同，共 133 次 RNG 调用；覆盖 getter 内替换上下文、无效上下文在零值／上限提前返回路径不应被访问、外部自定义 getter。原有回归、三场严格逐事件检查和 22 个 C ABI 检查通过。[边界测试](../output/_v1110/native_perf50/cycles16/buff_context_boundary_test.json) · [ABI](../output/_v1110/native_perf50/cycles16/buff_context_abi.json)

两轮各八组、120 秒预热、静默隔离 AB／BA，CPU 耗时分别增加 **3.07%、0.53%**，墙钟降幅 **−2.02%、0.17%**，触发预先记录的早停排除条件。保留全部 16 对，不合入，不进入 2,604 场及 24 批发布门槛，也未接入默认生成流程。下一轮先计数冷却阶段中相同角色加速／减速层数的重复计算，核对回调之间的有效复用区间，再决定是否值得缓存。[试验条件](../output/_v1110/native_perf50/cycles16/buff_context_trial_policy.json) · [首测](../output/_v1110/native_perf50/cycles16/buff_context_ab.json) · [反转复测](../output/_v1110/native_perf50/cycles16/buff_context_ab_repeat.json) · [汇总](../output/_v1110/native_perf50/cycles16/buff_context_ab_pooled.json) · [未部署记录](../output/_v1110/native_perf50/cycles16/buff_context_installation.json)
'''
doc.write_text(text,encoding='utf8',newline='\n')
paths=[STAGE/'optimize_native_buff_context.py',STAGE/'test_native_buff_context.cpp',doc]
paths += [p for p in WORK.iterdir() if p.is_file() and p.suffix in ('.py','.json')]
paths += list((WORK/'buff_context_target').glob('*.json'))
subprocess.run(['git','add','-f','--',*(str(p.relative_to(REPO)) for p in paths)],cwd=REPO,check=True,capture_output=True)
check=subprocess.run(['git','diff','--cached','--check'],cwd=REPO,capture_output=True)
assert check.returncode==0,check.stdout.decode('utf8','replace')[:2000]
subprocess.run(['git','commit','-m','perf: record rejected Buff context reads and preserve baseline'],cwd=REPO,check=True)
print(json.dumps(pooled,indent=2))
