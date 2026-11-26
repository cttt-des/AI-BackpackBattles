"""Freeze one native Buff inlining and return-kind slice with the existing complete protocol."""
import ast
import json
from prepare_native_buff_inline_types import STAGE,WORK as PROBE,ACCEPTED,BACKUP,EXPECTED,ARCHIVE,sha
WORK=STAGE/'native_perf50/buff_inline_types_bundle'
OLD_SHA='0a6d24f459eb1011a0bfcc1bc5c4188c1ca67add410b9caf0e04c8f5d30d44d4'
OLD_ARCHIVE='4cbfd55b10a7dae66529c41da01cbcce63ae66d2'

def once(t,a,b):
    assert t.count(a)==1,(a[:140],t.count(a));return t.replace(a,b,1)

def save(p,t):
    ast.parse(t,filename=str(p))
    if p.exists():assert p.read_text('utf8')==t,p
    else:p.write_text(t,encoding='utf8',newline='\n')

def adapt(t):
    for a,b in [('prototype_native_container_builtins_bundle','prototype_native_buff_inline_bundle'),
        ('prepare_native_container_builtins','prepare_native_buff_inline_types'),
        ('verify_native_container_builtins','verify_buff_inline_builtins'),
        ('verify_container_builtin_truth','verify_buff_inline_truth'),('verify_container_builtin_private','verify_buff_inline_private'),
        ('verify_container_builtin_display','verify_buff_inline_display'),('verify_container_builtin_control','verify_buff_inline_control'),
        ('verify_container_builtins_build_options','verify_buff_inline_build_options'),
        ('review_container_builtins_release','review_buff_inline_release'),
        ('container_builtins_bundle','buff_inline_types_bundle'),('container_builtins_prototype','buff_inline_types_prototype'),
        ('container-builtins-formal-','buff-inline-formal-'),(OLD_SHA,EXPECTED),(OLD_ARCHIVE,ARCHIVE)]:t=t.replace(a,b)
    return t

def main():
    suite=json.loads((PROBE/'semantic_suite.json').read_bytes());assert suite['passed'] and suite['total_cases']==682304
    assert not (WORK/'build_first.log').exists();WORK.mkdir(exist_ok=True)
    for p in ACCEPTED.glob('*.py'):
        if p.name in ('verified_bundle_pending.py','wait_calibration_window.py'):continue
        t=adapt(p.read_text('utf8'))
        t=t.replace("WORK.parent/'frame_value_bundle/","WORK.parent/'container_builtins_bundle/")
        t=t.replace("'native_frame_value_bundle_bundle_'","'native_container_builtins_bundle_bundle_'")
        if p.name=='build_bundle.py':
            t=once(t,"STAGE/'native_perf50/frame_value_bundle/checkpoint_receipt.json'","STAGE/'native_perf50/buff_integer_kernel_bundle/checkpoint_receipt.json'")
        if p.name=='prepare_regeneration.py':
            t=once(t,"OLD=WORK.parent/'frame_value_bundle'","OLD=WORK.parent/'container_builtins_bundle'")
            t=t.replace('native_perf50/frame_value_bundle','native_perf50/container_builtins_bundle')
        if p.name=='validate_then_compare.py':
            anchor="    run('verify_container_builtins.py','container_builtins_tests.log')"
            t=once(t,anchor,"    run('inspect_buff_machine.py','machine_code.log')\n    run('verify_buff_integer.py','buff_integer_tests.log')\n"+anchor)
            t=once(t,"    run('verify_resolved.py','verify.log')","    run('verify_full_pgo_buff.py','buff_full_pgo_tests.log')\n    run('verify_resolved.py','verify.log')")
        if p.name=='verify_object_routes_after_ab.py':
            anchor="    result=dict(container_builtin_cases=builtins_report['cases'],"
            insertion="    from verify_native_buff_inline_helpers import verify as verify_helpers\n    from verify_native_buff_inline_methods import verify as verify_methods\n    typed=target/'buff_integer';typed.mkdir()\n    helper_report=verify_helpers(WORK/'bundle_src',WORK/'bundle.dll',typed/'typed_helper_tests.json')\n    assert helper_report['unchanged_fallback_runtime_cross_compiler_hash_equal']\n    method_report=verify_methods(WORK/'bundle_src',WORK/'bundle.dll',typed/'method_tests.json')\n"
            t=once(t,anchor,insertion+anchor.replace('result=dict(',"result=dict(buff_integer_helper_cases=helper_report['cases'],buff_integer_method_cases=method_report['cases'],"))
        if p.name=='install_verified.py':
            anchor="    assert post_ab['container_builtin_cases']==128128"
            t=once(t,anchor,anchor+"\n    assert post_ab['buff_integer_helper_cases']==204288 and post_ab['buff_integer_method_cases']==14112\n    typed=json.loads((WORK/'buff_integer_tests.json').read_bytes());assert typed['passed'] and typed['cases']==218400 and typed['dll_sha256']==actual")
        if p.name=='verify_installed.py':
            anchor="    builtin=read('container_builtins_tests.json');assert builtin['passed'] and builtin['cases']==128128 and builtin['dll_sha256']==actual"
            t=once(t,anchor,anchor+"\n    typed=read('buff_integer_tests.json');assert typed['passed'] and typed['cases']==218400 and typed['dll_sha256']==actual")
            t=once(t,"'target_at20_fps':recalculated,'goal_target_fps':200,'goal200_reached':recalculated>=200,","'target_at20_fps':recalculated,'typed_buff_deployment_verified':True,")
        save(WORK/p.name,t)
    save(WORK/'verify_buff_integer.py',f'''import json
import sys
from pathlib import Path
WORK=Path(__file__).resolve().parent
sys.path.insert(0,str(WORK.parents[1]))
from prepare_native_buff_inline_types import sha
from verify_native_buff_inline_helpers import verify as helpers
from verify_native_buff_inline_methods import verify as methods
if __name__=='__main__':
    target=WORK/'buff_integer_checks';assert not target.exists();target.mkdir()
    a=helpers(WORK/'bundle_src',WORK/'bundle.dll',target/'typed_helper_tests.json')
    b=methods(WORK/'bundle_src',WORK/'bundle.dll',target/'method_tests.json')
    assert a['fixture_sha256']=='{sha(STAGE/'test_native_buff_integer_helpers.cpp')}'
    assert b['fixture_sha256']=='{sha(STAGE/'test_native_buff_integer_methods.cpp')}'
    result=dict(passed=True,cases=a['cases']+b['cases'],dll_sha256=sha(WORK/'bundle.dll'),helper_cases=a['cases'],method_cases=b['cases'])
    assert result['cases']==218400
    (WORK/'buff_integer_tests.json').write_text(json.dumps(result,indent=2)+'\\n',encoding='utf8')
    print(json.dumps(result),flush=True)
''')
    save(WORK/'inspect_buff_machine.py','import runpy\nfrom pathlib import Path\nimport sys\ns=Path(__file__).resolve().parents[2];sys.path.insert(0,str(s))\nrunpy.run_path(str(s/"inspect_native_buff_inline_machine.py"),run_name="__main__")\n')
    save(WORK/'verify_full_pgo_buff.py','import runpy\nfrom pathlib import Path\nimport sys\ns=Path(__file__).resolve().parents[2];sys.path.insert(0,str(s))\nrunpy.run_path(str(s/"verify_native_buff_inline_full_pgo.py"),run_name="__main__")\n')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp','bounded_followup_policy.json'):(WORK/name).write_bytes((ACCEPTED/name).read_bytes())
    plan=json.loads((ACCEPTED/'evaluation_plan.json').read_bytes())
    plan.pop('goal_fps_at20_load',None)
    plan.update(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,latest_remote_verified_production_backup=ARCHIVE,
        goal='Deploy one positively verified native Buff arithmetic optimization and back it up on the existing ref',
        baseline_source_files=708,candidate_source_files=708,full_source_changes=['gen/shards/shard_00.cpp'],
        components=['native CoreBuff gainTemporary forced inline arithmetic and proven coercion return kinds'],
        buff_integer_helper_cases=204288,buff_integer_method_cases=14112,total_semantic_cases=682304,
        semantic_suite_sha256=sha(PROBE/'semantic_suite.json'),all674_object_headers_and_all_layouts_unchanged=True,
        diagnostic_counts='native_perf50/buff_typed_assessment_20261126/workload_probe/counts.json',
        diagnostic_counts_sha256=sha(STAGE/'native_perf50/buff_typed_assessment_20261126/workload_probe/counts.json'),
        floating_operations_and_unknown_domains_use_original_runtime=True,diagnostic_frequencies_not_release_cost_or_gain=True,
        all_prior_components_retained=True,full_generic_branch_unchanged=True)
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    save(STAGE/'verify_buff_inline_build_options.py',adapt((STAGE/'verify_container_builtins_build_options.py').read_text('utf8')))
    formal=adapt((STAGE/'run_container_builtins_formal.py').read_text('utf8'))
    formal=once(formal,'ACCEPTED as BACKUP','BACKUP')
    save(STAGE/'run_buff_inline_formal.py',formal)
    save(STAGE/'close_buff_inline_round.py',adapt((STAGE/'close_container_builtins_round.py').read_text('utf8')))
    review=adapt((STAGE/'review_container_builtins_release.py').read_text('utf8'))
    review=once(review,"assert sorted(changed)==['native_inline_dispatch.hpp']","assert sorted(changed)==['gen/shards/shard_00.cpp']")
    review=once(review,"'scalar_truth_tests.json','container_builtins_tests.json')","'scalar_truth_tests.json','container_builtins_tests.json','buff_integer_tests.json','buff_full_pgo_tests.json')")
    anchor="    assert read('container_builtins_tests.json')['cases']==read('post_ab_directed_regressions.json')['container_builtin_cases']==128128"
    review=once(review,anchor,anchor+"\n    assert read('buff_integer_tests.json')['cases']==218400\n    assert read('post_ab_directed_regressions.json')['buff_integer_helper_cases']==204288 and read('post_ab_directed_regressions.json')['buff_integer_method_cases']==14112")
    save(STAGE/'review_buff_inline_release.py',review)
    print(json.dumps(dict(prepared=True,scripts=len(list(WORK.glob('*.py'))),source_files=708,total_semantic_cases=682304)),flush=True)

if __name__=='__main__':main()
