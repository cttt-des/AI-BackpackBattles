"""Prepare first-direction records; the three-direction goal remains active."""
import ast
from prepare_native_weapon_inline_chain import STAGE,WORK as PROBE
from setup_native_weapon_inline_chain_bundle import adapt,once,save,WORK

def terminal_adapt(t):
    for a,b in [('record_buff_inline_round','record_weapon_inline_chain_round'),('archive_buff_inline_round','archive_weapon_inline_chain_round'),
        ('finish_buff_inline_release','finish_weapon_inline_chain_release'),('verify_buff_inline_goal','verify_weapon_inline_chain_phase'),
        ('close_buff_inline_round','close_weapon_inline_chain_round'),('run_buff_inline_formal','run_weapon_inline_chain_formal')]:t=t.replace(a,b)
    return adapt(t)

def main():
    t=terminal_adapt((STAGE/'record_buff_inline_round.py').read_text('utf8'))
    t=once(t,"MARKER='## Buff内联与类型传播终态（2026-11-26）'","MARKER='## 武器具体类型内联第二轮（2026-11-26）'")
    t=t.replace("('buff_integer_tests.json',218400)]","('buff_integer_tests.json',218400),('weapon_inline_chain_tests.json',136128)]")
    t=t.replace("check['production_source_files']==708","check['production_source_files']==709")
    t=t.replace('typed_buff_goal_deployment_complete','first_direction_deployment_complete').replace('total_semantic_cases=682304','weapon_inline_chain_cases=136128,total_semantic_cases=818432')
    t=t.replace('buff_integer_deployed_retaining_all_prior_components','weapon_inline_chain_deployed_retaining_all_prior_components')
    start=t.index('。基于实际生产5BD3，');end=t.index('\\n\\n完整{cpu',start)
    description='。基于生产D206，第一轮完整ABI链535D已保留32对无正收益证据并归档379afbdd；本轮只在该链基础上将两个很短的Weapon生产入口移至私有头，以具体武器类型模板实例化并强制内联，消除其独立调用及CoreItem接收者类型丢失。取舍来自首轮正式PGO中仍存在的weapon_attack／weapon_cooldown独立函数、其直接调用指令及2032次真实语料栈采样；Character::dealDamage在首轮已被内联到Item伤害，本轮不原样重做该项或旧数学助手实验。所有伤害／体力算式、Source与Result入口、覆写／未知形态／默认argc回退、参数快照、浮点／RNG／回调和物理帧顺序均沿用前轮已验的原逻辑。674对象头及所有布局不变。严格双层逆变换逐字还原生产D206。保留全部818432例；普通构建须与源同生产的普通基准逐例一致，正式全新PGO须与实际生产完整一致才能测速。正式机器码要求两个微型生产入口不再形成独立函数；机制变化不充当收益，收益只由新源码的24对及至多一次8对A/B判定。'
    t=t[:start]+description+t[end:]
    t=t.replace('本轮目标是通过验收的伤害／Buff定型正收益部署与远端备份；旧200场/秒目标已由用户清除，不作为本轮完成条件','这是三个方向中的第一方向；本轮通过收益与语义验收后部署备份，之后继续第二、第三方向；旧200场/秒不是本轮门槛')
    t=t.replace('Buff内联与类型传播已部署','武器至伤害调用链定型已部署').replace('C++模拟器Buff内联定型优化记录_2026-11-26.md','C++模拟器武器具体类型内联优化记录_2026-11-26.md')
    save(STAGE/'record_weapon_inline_chain_round.py',t)
    t=terminal_adapt((STAGE/'archive_buff_inline_round.py').read_text('utf8'))
    scripts=('prepare_weapon_inline_chain_protocol.py','prepare_native_weapon_inline_chain.py','build_native_weapon_inline_chain.py','test_native_weapon_chain.cpp','verify_native_weapon_inline_chain.py',
        'setup_native_weapon_inline_chain_bundle.py','prototype_native_weapon_inline_chain_bundle.py','prepare_weapon_inline_chain_terminal_tools.py',
        'run_native_weapon_inline_chain_semantics.py','run_weapon_inline_chain_formal.py','verify_weapon_inline_chain_build_options.py','review_weapon_inline_chain_release.py',
        'verify_native_weapon_inline_chain_full_pgo.py','inspect_native_weapon_inline_chain_machine.py','inspect_retained_buff_weapon_inline_chain_machine.py',
        'verify_weapon_inline_chain_builtins.py','verify_weapon_inline_chain_truth.py','verify_weapon_inline_chain_private.py','verify_weapon_inline_chain_display.py',
        'verify_weapon_inline_chain_control.py','verify_weapon_inline_chain_buff_helpers.py','verify_weapon_inline_chain_buff_methods.py',
        'close_weapon_inline_chain_round.py','record_weapon_inline_chain_round.py','archive_weapon_inline_chain_round.py','finish_weapon_inline_chain_release.py',
        'verify_weapon_inline_chain_phase.py','fit_native_serial_load.py','test_native_buff_integer_helpers.cpp','test_native_buff_integer_methods.cpp')
    start=t.index('SCRIPTS=');end=t.index('\n\n',start);t=t[:start]+'SCRIPTS='+repr(scripts)+t[end:]
    t=t.replace('buff-inline-own-','weapon-chain-own-').replace("STAGE.glob('buff_inline*.log')","STAGE.glob('weapon_inline_chain*.log')").replace("'buff_inline_archive_'","'weapon_inline_chain_archive_'")
    t=t.replace("STAGE/'native_perf50/buff_typed_assessment_20261126'","STAGE/'native_perf50/weapon_chain_boundary_assessment'")
    t=t.replace("STAGE/'native_perf50/buff_integer_kernel_bundle/checkpoint_receipt.json'","STAGE/'native_perf50/weapon_chain_bundle/checkpoint_receipt.json'")
    t=t.replace('C++模拟器Buff内联定型优化记录_2026-11-26.md','C++模拟器武器具体类型内联优化记录_2026-11-26.md')
    t=once(t,"    assert len(production)==(708)\n    deployed=status['deployed']","    deployed=status['deployed']\n    assert len(production)==(709 if deployed else 708)")
    t=t.replace('len(expected_cpp)==(708)','len(expected_cpp)==(709 if deployed else 708)')
    t=t.replace('production_source_files=708','production_source_files=(709 if deployed else 708)').replace('production_source_files_verified=708','production_source_files_verified=(709 if deployed else 708)')
    t=t.replace('perf: preserve forced inline Buff type propagation with complete evidence','perf: preserve typed weapon damage chain with complete evidence')
    t=t.replace("    paths.add(ACCEPTED/'checkpoint_receipt.json')","    paths.add(ACCEPTED/'checkpoint_receipt.json')\n    paths.add(STAGE/'weapon_chain_boundary_profile_first.log')")
    save(STAGE/'archive_weapon_inline_chain_round.py',t)
    t=terminal_adapt((STAGE/'finish_buff_inline_release.py').read_text('utf8'))
    t=once(t,"    run(STAGE/'archive_weapon_inline_chain_round.py','checkpoint_prepare_first.log','--commit')",'    # Freeze the backup only after this driver and its stdout have terminated.')
    save(STAGE/'finish_weapon_inline_chain_release.py',t)
    t=terminal_adapt((STAGE/'verify_buff_inline_goal.py').read_text('utf8'))
    t=t.replace('typed_buff_goal_deployment_complete','first_direction_deployment_complete')
    t=t.replace('goal_complete=True','first_direction_complete=True,three_direction_goal_remains_active=True')
    t=t.replace("WORK/'goal_completion_receipt.json'","WORK/'first_direction_completion_receipt.json'")
    t=t.replace('import json\n','import json\nimport hashlib\n',1)
    t=t.replace("backup['workspace_state']['head']==boundary['head'] and backup['workspace_state']['index_sha256']==boundary['index_sha256']","backup['workspace_state']['head']==boundary['head']\n    assert hashlib.sha256(subprocess.check_output(['git','ls-files','--stage','-z'],cwd=REPO)).hexdigest()==boundary['staged_entries_sha256']")
    save(STAGE/'verify_weapon_inline_chain_phase.py',t)
    boundary=(PROBE/'user_boundary_before.json').read_bytes();p=WORK/'user_boundary_before.json'
    if p.exists():assert p.read_bytes()==boundary
    else:p.write_bytes(boundary)
    print('Prepared first-direction records and existing-ref backup; three-direction goal remains active',flush=True)

if __name__=='__main__':main()
