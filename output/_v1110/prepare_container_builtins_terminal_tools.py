"""Prepare terminal review/archive tools before any formal timing begins."""
import ast
from prepare_native_container_builtins import STAGE
from setup_native_container_builtins_bundle import adapt

def once(t,a,b):
    assert t.count(a)==1,(a[:120],t.count(a));return t.replace(a,b,1)

def save(name,t):
    ast.parse(t,filename=name)
    path=STAGE/name;assert not path.exists();path.write_text(t,encoding='utf8',newline='\n')

def main():
    t=adapt((STAGE/'record_frame_values_round.py').read_text('utf8'))
    t=once(t,"MARKER='## 逐帧值处理组合终态（2026-11-26）'","MARKER='## 容器内建调用组合终态（2026-11-26）'")
    t=once(t,"('scalar_truth_tests.json',34400)]","('scalar_truth_tests.json',34400),('container_builtins_tests.json',128128)]")
    t=once(t,"assert read(WORK/'post_ab_directed_regressions.json')['scalar_truth_cases']==34400","assert read(WORK/'post_ab_directed_regressions.json')['scalar_truth_cases']==34400\n        assert read(WORK/'post_ab_directed_regressions.json')['container_builtin_cases']==128128")
    t=t.replace('frame_values_deployed_retaining_all_prior_components','container_builtins_deployed_retaining_all_prior_components')
    t=once(t,'scalar_truth_cases=34400,all_protocol_processes_finished=True,','scalar_truth_cases=34400,container_builtin_cases=128128,total_semantic_cases=463904,all_protocol_processes_finished=True,')
    start=t.index('。基于已部署63D，');end=t.index('\\n\\n完整{cpu',start)
    description='。基于实际生产0A6D，仅改native_inline_dispatch.hpp的native_inline_call：补充Array的push_back／append／append_array／clear／resize／fill／duplicate、Dict的keys／values、Enum的size／empty／has／keys／values短路径；调用与原gd::call_method相同的原成员函数，保留原有容器观察／计时器失效、空值、自追加、深浅复制、参数别名和用户回调语义。Float resize以及Float／Vec2／Color duplicate参数继续走原通用分派，以保持浮点状态。原gd_rt.cpp及全部生成方法、其他712目录文件、708份C++清单及674对象头／GdVal24／GdArr32／CoreItem2112／BattleCtx328／watch64布局不变。严格逆变换逐字还原完整旧头文件。全部先前优化保留；原型完整20普通对象仅作语义验证，正式完整20插桩／新18PGO。原型与正式版新增128128容器边界（原／新实际DLL逐状态精确比较及每例哈希、4舍入方式×4DAZ/FTZ组合、异常标志、容器别名与观察版本），另保留34400标量、234880私有、21888显示、44608控制／计时器／帧检查，总463904例及独立4项registry检查。固定200原结果／终局和原计数保持。分派诊断频次只用于选方向，不作为正式版本成本或收益。'
    t=t[:start]+description+t[end:]
    t=t.replace('逐帧值处理已部署','容器内建调用已部署').replace('C++模拟器逐帧值处理优化记录_2026-11-26.md','C++模拟器容器内建调用优化记录_2026-11-26.md')
    save('record_container_builtins_round.py',t)

    t=adapt((STAGE/'archive_frame_values_round.py').read_text('utf8'))
    scripts=('prepare_native_container_builtins.py','build_native_container_builtins.py',
        'test_native_container_builtins.cpp','verify_native_container_builtins.py',
        'verify_container_builtin_truth.py','verify_container_builtin_private.py','verify_container_builtin_display.py','verify_container_builtin_control.py',
        'run_native_container_semantics.py','prototype_native_container_builtins_bundle.py','setup_native_container_builtins_bundle.py',
        'prepare_container_builtins_terminal_tools.py','run_container_builtins_formal.py','verify_container_builtins_build_options.py',
        'review_container_builtins_release.py','close_container_builtins_round.py','record_container_builtins_round.py',
        'archive_container_builtins_round.py','fit_native_serial_load.py','count_native_method_dispatch.py',
        'test_native_scalar_truth.cpp','test_native_identity_snapshots.cpp','test_native_private_buff_loops.cpp','test_native_private_integer_view.cpp')
    start=t.index('SCRIPTS=');end=t.index('\n\n',start);t=t[:start]+'SCRIPTS='+repr(scripts)+t[end:]
    t=t.replace('frame-values-own-','container-builtins-own-').replace("STAGE.glob('frame_values*.log')","STAGE.glob('container_builtins*.log')").replace("'frame_values_archive_'","'container_builtins_archive_'")
    t=t.replace("STAGE/'native_perf50/scalar_guards_followup_profile'","STAGE/'native_perf50/method_dispatch_probe_20261126'")
    t=once(t,"    frozen=json.loads((WORK/'frozen_pgo_manifest.json').read_bytes())","    paths.add(STAGE/'method_dispatch_counts_first.log')\n    frozen=json.loads((WORK/'frozen_pgo_manifest.json').read_bytes())")
    t=t.replace('C++模拟器逐帧值处理优化记录_2026-11-26.md','C++模拟器容器内建调用优化记录_2026-11-26.md')
    t=t.replace('perf: preserve verified frame-local value handling','perf: preserve container builtin trial with complete evidence')
    t=t.replace('comparing712 entries with707 C++ files','comparing713 entries with708 C++ files')
    save('archive_container_builtins_round.py',t)
    print('Prepared terminal tools; no timings or production files changed',flush=True)

if __name__=='__main__':main()
