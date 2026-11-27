"""Version second-direction records and the existing-ref-only backup workflow."""
import ast
import hashlib
import json
import subprocess
from pathlib import Path
from prepare_native_assembly_membership import STAGE,WORK as PROBE,sha

def main():
    t=(STAGE/'prepare_weapon_chain_terminal_tools.py').read_text('utf8').replace('weapon_chain','assembly_membership')
    t=t.replace('first_direction','second_direction').replace('first-direction','second-direction')
    t=t.replace('这是三个方向中的第一方向；本轮通过收益与语义验收后部署备份，之后继续第二、第三方向','这是三个方向中的第二方向；本轮通过收益与语义验收后部署备份，之后继续第三方向').replace('武器至伤害调用链定型已部署','装配成员查询优化已部署')
    t=t.replace('武器至伤害调用链定型第一轮','装配成员查询优化第一轮')
    t=t.replace('C++模拟器武器伤害调用链优化记录_2026-11-26.md','C++模拟器装配成员查询优化记录_2026-11-26.md')
    t=t.replace("('assembly_membership_tests.json',136128)]","('weapon_chain_tests.json',136128),('assembly_membership_tests.json',229376)]")
    t=t.replace('assembly_membership_cases=136128,total_semantic_cases=818432','weapon_chain_cases=136128,assembly_membership_cases=229376,total_semantic_cases=1047808')
    t=t.replace("STAGE/'native_perf50/remaining_value_review_after_d206'","STAGE/'native_perf50/assembly_membership_assessment'")
    t=t.replace("\"STAGE/'native_perf50/buff_inline_types_bundle/checkpoint_receipt.json'\"","\"STAGE/'native_perf50/weapon_inline_chain_bundle/checkpoint_receipt.json'\"")
    start=t.index("    description='");end=t.index("\n    t=t[:start]+description+t[end:]",start)
    description='。以实际生产D206为基线，仅改变CoreItem::onItemAdded当前受影响对象集合的一处成员判断，增加私有原生bool助手。200场诊断记录1009420次对象集合查询，其中961606次字典为空；坐标数组查询50894次。本切片在对象键且字典未索引、长度为零时返回false，避免无副作用的对象指针哈希和GdVal布尔返回中转；已索引或非空字典继续调用原has，其他容器继续原gd_in与真假转换。未将普通空表推论扩大到可能保留陈旧索引的len=0表，也未跳过非对象键原哈希的FP异常标志。不更改全局相等、哈希或字典表示；坐标查询、完整query阶段／commit阶段及回调、字段观察、RNG和物理帧顺序保持。原型固定200场结果与全部旧计数一致，新增229376组私有助手语义测试，覆盖原112形态、128容器状态和16浮点模式；实际原DLL内部原gd_in与助手逐例完全一致，跨原型／生产结果、fenv／MXCSR及旧计数一致。涵盖未索引空表、保留索引的空表、手工len=0陈旧索引、深复制、整数网格、数值别名、NaN／subnormal及未知形态，并检查输入与容器不变。首个测试夹具因两次新建临时GdVal的填充字节比较而失败，修为对同一持久值前后比较，全部229376例保留，仅新增测试重跑。既有818432例保留，共1047808例；普通构建保留既有56例武器矩阵跨构建差异及源同生产普通基准的零差异证明，正式PGO必须与实际生产完整一致。674对象头、CoreItem2112／Weapon4288／BattleCtx328及所有布局不变。正式完整20插桩／新18PGO，原浮点选项保持。频数及无独立助手函数的机器码证据仅证明机制，不代替成对收益。'
    t=t[:start]+'    description='+repr(description)+t[end:]
    # Add the two new validation receipts to the deployed phase checks.
    anchor="    save(STAGE/'verify_assembly_membership_phase.py',t)"
    extra='''    t=t.replace('import json\\n','import json\\nimport hashlib\\n',1)
    t=t.replace("backup['workspace_state']['head']==boundary['head'] and backup['workspace_state']['index_sha256']==boundary['index_sha256']","backup['workspace_state']['head']==boundary['head']\\n    assert hashlib.sha256(subprocess.check_output(['git','ls-files','--stage','-z'],cwd=REPO)).hexdigest()==boundary['staged_entries_sha256']")
    a="    assert read('buff_integer_tests.json')['cases']==218400"
    t=once(t,a,a+"\\n    assert read('weapon_chain_tests.json')['cases']==136128 and read('assembly_membership_tests.json')['cases']==229376\\n    assert read('post_ab_directed_regressions.json')['weapon_chain_cases']==136128 and read('post_ab_directed_regressions.json')['assembly_membership_cases']==229376")
'''
    assert t.count(anchor)==1;t=t.replace(anchor,extra+anchor)
    # Use this direction's sources; the unchanged weapon fixture is retained.
    start=t.index('    scripts=');end=t.index('\n    start=t.index(\'SCRIPTS=\')',start)
    scripts=('prepare_assembly_membership_protocol.py','prepare_native_assembly_membership.py','probe_native_assembly_membership.py',
        'build_native_assembly_membership.py','test_native_assembly_membership.cpp','verify_native_assembly_membership_helpers.py',
        'test_native_weapon_chain.cpp','verify_assembly_weapon_chain.py','run_native_assembly_membership_semantics.py',
        'verify_assembly_membership_builtins.py','verify_assembly_membership_truth.py','verify_assembly_membership_private.py',
        'verify_assembly_membership_display.py','verify_assembly_membership_control.py','verify_assembly_membership_buff_helpers.py',
        'verify_assembly_membership_buff_methods.py','setup_native_assembly_membership_bundle.py','prototype_native_assembly_membership_bundle.py',
        'prepare_assembly_membership_terminal_tools.py','run_assembly_membership_formal.py','verify_assembly_membership_build_options.py',
        'review_assembly_membership_release.py','verify_native_assembly_membership_full_pgo.py','inspect_native_assembly_membership_machine.py',
        'inspect_retained_buff_assembly_membership_machine.py','close_assembly_membership_round.py','record_assembly_membership_round.py',
        'archive_assembly_membership_round.py','finish_assembly_membership_release.py','verify_assembly_membership_phase.py','fit_native_serial_load.py')
    t=t[:start]+'    scripts='+repr(scripts)+t[end:]
    ast.parse(t)
    generated=STAGE/'prepare_assembly_membership_records_generated.py'
    if generated.exists():assert generated.read_text('utf8')==t
    else:generated.write_text(t,encoding='utf8',newline='\n')
    p=PROBE/'user_boundary_before.json'
    if not p.exists():
        repo=STAGE.parents[1];old=json.loads((STAGE/'native_perf50/weapon_inline_chain_prototype/user_boundary_before.json').read_bytes())
        assert all(sha(repo/n)==h for n,h in old['protected'].items())
        index=Path(subprocess.check_output(['git','rev-parse','--git-path','index'],cwd=repo,text=True).strip())
        if not index.is_absolute():index=repo/index
        old.update(head=subprocess.check_output(['git','rev-parse','HEAD'],cwd=repo,text=True).strip(),index_sha256=sha(index),staged_entries_sha256=hashlib.sha256(subprocess.check_output(['git','ls-files','--stage','-z'],cwd=repo)).hexdigest())
        p.write_text(json.dumps(old,indent=2)+'\n',encoding='utf8')
    subprocess.run([__import__('sys').executable,'-X','utf8',str(generated)],check=True)

if __name__=='__main__':main()
