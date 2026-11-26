"""Prepare reviewable round records and an existing-ref-only backup."""
import ast
from prepare_native_buff_integer_kernel import STAGE
from setup_native_buff_integer_bundle import adapt

def once(t,a,b):
    assert t.count(a)==1,(a[:120],t.count(a));return t.replace(a,b,1)

def save(name,t):
    ast.parse(t,filename=name);p=STAGE/name;assert not p.exists();p.write_text(t,encoding='utf8',newline='\n')

def terminal_adapt(t):
    for a,b in [('record_container_builtins_round','record_buff_integer_round'),('archive_container_builtins_round','archive_buff_integer_round'),
        ('finish_container_builtins_release','finish_buff_integer_release'),('verify_container_builtins_goal','verify_buff_integer_goal'),
        ('close_container_builtins_round','close_buff_integer_round'),('run_container_builtins_formal','run_buff_integer_formal')]:t=t.replace(a,b)
    return adapt(t)

def main():
    t=terminal_adapt((STAGE/'record_container_builtins_round.py').read_text('utf8'))
    t=once(t,"MARKER='## 容器内建调用组合终态（2026-11-26）'","MARKER='## Buff整数运算局部定型终态（2026-11-26）'")
    t=once(t,"('container_builtins_tests.json',128128)]","('container_builtins_tests.json',128128),('buff_integer_tests.json',218400)]")
    t=once(t,"assert read(WORK/'post_ab_directed_regressions.json')['container_builtin_cases']==128128","assert read(WORK/'post_ab_directed_regressions.json')['container_builtin_cases']==128128\n        assert read(WORK/'post_ab_directed_regressions.json')['buff_integer_helper_cases']==204288 and read(WORK/'post_ab_directed_regressions.json')['buff_integer_method_cases']==14112")
    t=t.replace('container_builtins_deployed_retaining_all_prior_components','buff_integer_deployed_retaining_all_prior_components')
    t=once(t,'total_semantic_cases=463904','buff_integer_helper_cases=204288,buff_integer_method_cases=14112,total_semantic_cases=682304')
    t=once(t,'goal200_reached=bool(deployed and point>=200),goal_still_active=True,','typed_buff_goal_deployment_complete=deployed,goal_requires_verified_remote_backup=True,')
    start=t.index('。基于实际生产0A6D，');end=t.index('\\n\\n完整{cpu',start)
    description='。基于实际生产5BD3，仅修改gen/shards/shard_00.cpp中的CoreBuff::gainTemporary原生分支：将整数加减、整数最小值、整数与布尔强转及小整数正数判断局部内联。整数加减溢出、混合类型、未知形态及全部浮点运算仍执行原运行库；比较快路径限制在±2^53以保留整数转double的舍入与异常标志。完整通用分支、全部回调与RNG调用顺序、字段读取位置、循环快照和物理帧时序保持。严格逆变换逐字还原旧分片，其余712份完整清单文件、674对象头与全部布局不变。保留此前所有优化。原型仅重编译变更分片并复用19份已核对源码及字节的普通对象作语义检查；正式完整20插桩／新18PGO，原浮点选项保持。新增204288组助手边界测试（806160次有效操作／库、16浮点模式），在各实际DLL内部逐操作精确比较原函数与助手的完整值向量、输入字节、异常标志与MXCSR；其中9904次新增整数／布尔快路径额外跨DLL一致。112种值形态保留，但原gd_lt无法定义的240次空Str指针排序不执行，原版崩溃、gdb证据与首稿保留。普通编译的未改动gd_sub在极小数减零时与生产PGO存在既有差异，保留两版原始记录，不将未改动fallback的跨编译差异伪报为一致；各库内部所有fallback与原函数必须完全一致。正式PGO版额外要求全部204288组跨DLL完整观测（含浮点、NaN、复杂类型和溢出回退）一致，结果见buff_full_pgo_tests.json。实际Buff方法另有14112例，在16浮点模式下覆盖整数边界、转换、零值、NaN、反射、临时层数及计时器，并与生产DLL逐例核对状态／RNG／异常标志／MXCSR。既有463904例全部保留，共682304及独立4项registry边界。诊断的49858次方法调用及整数热路径频数只用于选题，不代替机器码或测速收益。'
    t=t[:start]+description+t[end:]
    t=t.replace("目标200达到={status['goal200_reached']}，目标最终完成须另核验实际部署／备份和目标状态", "本轮目标是通过验收的伤害／Buff定型正收益部署与远端备份；旧200场/秒目标已由用户清除，不作为本轮完成条件")
    t=t.replace('容器内建调用已部署','Buff整数运算局部定型已部署').replace('C++模拟器容器内建调用优化记录_2026-11-26.md','C++模拟器Buff整数定型优化记录_2026-11-26.md')
    save('record_buff_integer_round.py',t)

    t=terminal_adapt((STAGE/'archive_container_builtins_round.py').read_text('utf8'))
    scripts=('verify_native_buff_full_pgo.py','inspect_native_buff_machine.py','prepare_native_buff_integer_kernel.py','count_native_buff_typed_work.py','build_native_buff_integer_kernel.py',
        'test_native_buff_integer_helpers.cpp','test_native_buff_integer_methods.cpp','verify_native_buff_integer_helpers.py',
        'verify_native_buff_integer_methods.py','verify_buff_integer_builtins.py','verify_buff_integer_truth.py','verify_buff_integer_private.py',
        'verify_buff_integer_display.py','verify_buff_integer_control.py','run_native_buff_integer_semantics.py',
        'prototype_native_buff_integer_bundle.py','setup_native_buff_integer_bundle.py','prepare_buff_integer_terminal_tools.py',
        'run_buff_integer_formal.py','verify_buff_integer_build_options.py','review_buff_integer_release.py','close_buff_integer_round.py',
        'record_buff_integer_round.py','archive_buff_integer_round.py','finish_buff_integer_release.py','verify_buff_integer_goal.py',
        'fit_native_serial_load.py','test_native_scalar_truth.cpp','test_native_identity_snapshots.cpp','test_native_private_buff_loops.cpp',
        'test_native_private_integer_view.cpp','test_native_buff_scalar_locals.cpp','test_native_integer_ranges.cpp','test_native_identity_lookup.cpp')
    start=t.index('SCRIPTS=');end=t.index('\n\n',start);t=t[:start]+'SCRIPTS='+repr(scripts)+t[end:]
    t=t.replace('container-builtins-own-','buff-integer-own-').replace("STAGE.glob('container_builtins*.log')","STAGE.glob('buff_integer*.log')").replace("'container_builtins_archive_'","'buff_integer_archive_'")
    t=t.replace("STAGE/'native_perf50/method_dispatch_probe_20261126'","STAGE/'native_perf50/buff_typed_assessment_20261126'")
    t=t.replace("paths.add(STAGE/'method_dispatch_counts_first.log')","paths.add(STAGE/'native_perf50/identity_lookup_bundle/checkpoint_receipt.json')")
    t=t.replace('C++模拟器容器内建调用优化记录_2026-11-26.md','C++模拟器Buff整数定型优化记录_2026-11-26.md')
    t=t.replace('perf: preserve container builtin trial with complete evidence','perf: preserve native Buff integer specialization with complete evidence')
    save('archive_buff_integer_round.py',t)
    save('finish_buff_integer_release.py',terminal_adapt((STAGE/'finish_container_builtins_release.py').read_text('utf8')))
    t=terminal_adapt((STAGE/'verify_container_builtins_goal.py').read_text('utf8'))
    t=once(t,"assert status['deployed'] and status['goal200_reached'] and status['candidate_load20_fps']>=200","assert status['deployed'] and status['typed_buff_goal_deployment_complete']\n    assert read('buff_integer_tests.json')['cases']==218400\n    assert read('post_ab_directed_regressions.json')['buff_integer_helper_cases']==204288 and read('post_ab_directed_regressions.json')['buff_integer_method_cases']==14112")
    t=once(t,"    fit=read('bundle_load20.json');norm=read('normalized20_sample_summary.json')","    boundary=read('user_boundary_before.json')\n    assert all(sha(REPO/n)==h for n,h in boundary['protected'].items())\n    assert backup['workspace_state']['head']==boundary['head'] and backup['workspace_state']['index_sha256']==boundary['index_sha256']\n    fit=read('bundle_load20.json');norm=read('normalized20_sample_summary.json')")
    save('verify_buff_integer_goal.py',t)
    print('Prepared round records, review and existing-ref backup; no timing or deployment',flush=True)

if __name__=='__main__':main()
