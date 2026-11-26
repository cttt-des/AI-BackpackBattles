"""Prepare first-direction records; the three-direction goal remains active."""
import ast
from prepare_native_weapon_chain import STAGE,WORK as PROBE
from setup_native_weapon_chain_bundle import adapt,once,save,WORK

def terminal_adapt(t):
    for a,b in [('record_buff_inline_round','record_weapon_chain_round'),('archive_buff_inline_round','archive_weapon_chain_round'),
        ('finish_buff_inline_release','finish_weapon_chain_release'),('verify_buff_inline_goal','verify_weapon_chain_phase'),
        ('close_buff_inline_round','close_weapon_chain_round'),('run_buff_inline_formal','run_weapon_chain_formal')]:t=t.replace(a,b)
    return adapt(t)

def main():
    t=terminal_adapt((STAGE/'record_buff_inline_round.py').read_text('utf8'))
    t=once(t,"MARKER='## Buff内联与类型传播终态（2026-11-26）'","MARKER='## 武器至伤害调用链定型第一轮（2026-11-26）'")
    t=t.replace("('buff_integer_tests.json',218400)]","('buff_integer_tests.json',218400),('weapon_chain_tests.json',136128)]")
    t=t.replace("check['production_source_files']==708","check['production_source_files']==709")
    t=t.replace('typed_buff_goal_deployment_complete','first_direction_deployment_complete').replace('total_semantic_cases=682304','weapon_chain_cases=136128,total_semantic_cases=818432')
    t=t.replace('buff_integer_deployed_retaining_all_prior_components','weapon_chain_deployed_retaining_all_prior_components')
    start=t.index('。基于实际生产5BD3，');end=t.index('\\n\\n完整{cpu',start)
    description='。基于实际生产D206，修改4个分片并新增私有接口头，连接武器冷却触发／攻击、Item体力与伤害、Character体力／伤害／takeDamage。用已缓存且绑定完全匹配的方法行进入私有入口，未知接收者、覆写、跨上下文和审计不匹配均在原位置回退；不增加对象字段。私有入口消除对应调用边界的参数数组中转，沿角色伤害链传递Source指针并返回Result指针；体力状态返回原整数。原伤害运算、浮点求值、RNG、字段观察与回调顺序均保留。参数在具有副作用的character()获取器之前快照，默认调用仍保持argc=0。公开原函数和通用分支完整保留，674对象头及所有布局不变。不是旧整段takeDamage数学助手或指针／flags缓存候选的重跑。独立实际DLL新增136128例，覆盖两套Weapon层次、覆写与空缓存行、参数快照、嵌套及可变回调、16浮点模式和开闭上下文；既有682304例均保留。普通原型与生产PGO有56例构建方式差异，关闭新入口时也存在；源码等同生产的普通构建与原型136128例完全一致。保留两版原始差异与诊断，不把原型跨构建差异伪报成生产一致；正式PGO候选必须与实际生产全部136128例及既有回归一致才允许测速。真实固定语料422次栈采样已观察到私有生产消费链，频数仅证明路径到达，不是性能收益；正式机器码另保存实际私有入口及直接调用证据。完整20插桩与全新18PGO，原浮点选项不变。'
    t=t[:start]+description+t[end:]
    t=t.replace('本轮目标是通过验收的伤害／Buff定型正收益部署与远端备份；旧200场/秒目标已由用户清除，不作为本轮完成条件','这是三个方向中的第一方向；本轮通过收益与语义验收后部署备份，之后继续第二、第三方向；旧200场/秒不是本轮门槛')
    t=t.replace('Buff内联与类型传播已部署','武器至伤害调用链定型已部署').replace('C++模拟器Buff内联定型优化记录_2026-11-26.md','C++模拟器武器伤害调用链优化记录_2026-11-26.md')
    save(STAGE/'record_weapon_chain_round.py',t)
    t=terminal_adapt((STAGE/'archive_buff_inline_round.py').read_text('utf8'))
    scripts=('prepare_native_weapon_chain.py','build_native_weapon_chain.py','test_native_weapon_chain.cpp','verify_native_weapon_chain.py',
        'setup_native_weapon_chain_bundle.py','prototype_native_weapon_chain_bundle.py','prepare_weapon_chain_terminal_tools.py',
        'run_native_weapon_chain_semantics.py','run_weapon_chain_formal.py','verify_weapon_chain_build_options.py','review_weapon_chain_release.py',
        'verify_native_weapon_chain_full_pgo.py','inspect_native_weapon_chain_machine.py','inspect_retained_buff_weapon_chain_machine.py',
        'verify_weapon_chain_builtins.py','verify_weapon_chain_truth.py','verify_weapon_chain_private.py','verify_weapon_chain_display.py',
        'verify_weapon_chain_control.py','verify_weapon_chain_buff_helpers.py','verify_weapon_chain_buff_methods.py',
        'close_weapon_chain_round.py','record_weapon_chain_round.py','archive_weapon_chain_round.py','finish_weapon_chain_release.py',
        'verify_weapon_chain_phase.py','fit_native_serial_load.py','test_native_buff_integer_helpers.cpp','test_native_buff_integer_methods.cpp')
    start=t.index('SCRIPTS=');end=t.index('\n\n',start);t=t[:start]+'SCRIPTS='+repr(scripts)+t[end:]
    t=t.replace('buff-inline-own-','weapon-chain-own-').replace("STAGE.glob('buff_inline*.log')","STAGE.glob('weapon_chain*.log')").replace("'buff_inline_archive_'","'weapon_chain_archive_'")
    t=t.replace("STAGE/'native_perf50/buff_typed_assessment_20261126'","STAGE/'native_perf50/remaining_value_review_after_d206'")
    t=t.replace("STAGE/'native_perf50/buff_integer_kernel_bundle/checkpoint_receipt.json'","STAGE/'native_perf50/buff_inline_types_bundle/checkpoint_receipt.json'")
    t=t.replace('C++模拟器Buff内联定型优化记录_2026-11-26.md','C++模拟器武器伤害调用链优化记录_2026-11-26.md')
    t=once(t,"    assert len(production)==(708)\n    deployed=status['deployed']","    deployed=status['deployed']\n    assert len(production)==(709 if deployed else 708)")
    t=t.replace('len(expected_cpp)==(708)','len(expected_cpp)==(709 if deployed else 708)')
    t=t.replace('production_source_files=708','production_source_files=(709 if deployed else 708)').replace('production_source_files_verified=708','production_source_files_verified=(709 if deployed else 708)')
    t=t.replace('perf: preserve forced inline Buff type propagation with complete evidence','perf: preserve typed weapon damage chain with complete evidence')
    save(STAGE/'archive_weapon_chain_round.py',t)
    t=terminal_adapt((STAGE/'finish_buff_inline_release.py').read_text('utf8'))
    t=once(t,"    run(STAGE/'archive_weapon_chain_round.py','checkpoint_prepare_first.log','--commit')",'    # Freeze the backup only after this driver and its stdout have terminated.')
    save(STAGE/'finish_weapon_chain_release.py',t)
    t=terminal_adapt((STAGE/'verify_buff_inline_goal.py').read_text('utf8'))
    t=t.replace('typed_buff_goal_deployment_complete','first_direction_deployment_complete')
    t=t.replace('goal_complete=True','first_direction_complete=True,three_direction_goal_remains_active=True')
    t=t.replace("WORK/'goal_completion_receipt.json'","WORK/'first_direction_completion_receipt.json'")
    save(STAGE/'verify_weapon_chain_phase.py',t)
    boundary=(PROBE/'user_boundary_before.json').read_bytes();p=WORK/'user_boundary_before.json'
    if p.exists():assert p.read_bytes()==boundary
    else:p.write_bytes(boundary)
    print('Prepared first-direction records and existing-ref backup; three-direction goal remains active',flush=True)

if __name__=='__main__':main()
