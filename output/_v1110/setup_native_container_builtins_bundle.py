"""Freeze the next distinct builtin combination with all established gates."""
import ast
import json
from prepare_native_container_builtins import STAGE,WORK as PROBE,ACCEPTED,EXPECTED,ARCHIVE,sha
WORK=STAGE/'native_perf50/container_builtins_bundle'
OLD_SHA='63d8966c95c629855fc336a748cbfcc20860d5e75d7c1700506022f347ac10c5'
OLD_ARCHIVE='8f7022b1e28093d6f48d1c1250a92cab8789bad3'
def once(t,a,b):
    assert t.count(a)==1,(a[:140],t.count(a));return t.replace(a,b,1)
def save(p,t):
    ast.parse(t,filename=str(p))
    if p.exists():assert p.read_text('utf8')==t,p
    else:p.write_text(t,encoding='utf8',newline='\n')
def adapt(t):
    for a,b in [('prototype_native_frame_values_bundle','prototype_native_container_builtins_bundle'),
            ('prepare_native_frame_values','prepare_native_container_builtins'),('verify_frame_value_truth','verify_container_builtin_truth'),
            ('verify_frame_value_private','verify_container_builtin_private'),('verify_frame_value_display','verify_container_builtin_display'),
            ('verify_frame_value_control','verify_container_builtin_control'),('verify_frame_values_build_options','verify_container_builtins_build_options'),
            ('frame_value_bundle','container_builtins_bundle'),('frame_value_prototype','container_builtins_prototype'),
            ('frame-values-formal-','container-builtins-formal-'),(OLD_SHA,EXPECTED),(OLD_ARCHIVE,ARCHIVE)]:t=t.replace(a,b)
    return t
def main():
    suite=json.loads((PROBE/'semantic_suite.json').read_bytes());assert suite['passed'] and suite['total_cases']==463904
    assert not (WORK/'build_first.log').exists();WORK.mkdir(exist_ok=True)
    for p in ACCEPTED.glob('*.py'):
        if p.name in ('verified_bundle_pending.py','wait_calibration_window.py'):continue
        t=adapt(p.read_text('utf8'))
        t=t.replace("WORK.parent/'scalar_guards_bundle/","WORK.parent/'frame_value_bundle/")
        t=t.replace("'native_scalar_guards_bundle_bundle_'","'native_frame_value_bundle_bundle_'")
        if p.name=='build_bundle.py':
            t=once(t,"STAGE/'native_perf50/scalar_guards_bundle/checkpoint_receipt.json'","STAGE/'native_perf50/frame_value_bundle/checkpoint_receipt.json'")
        if p.name=='prepare_regeneration.py':
            t=once(t,"OLD=WORK.parent/'scalar_guards_bundle'","OLD=WORK.parent/'frame_value_bundle'")
            t=t.replace('native_perf50/scalar_guards_bundle','native_perf50/frame_value_bundle')
        if p.name=='validate_then_compare.py':
            anchor="    run('verify_scalar_truth.py','scalar_truth_tests.log')"
            t=once(t,anchor,"    run('verify_container_builtins.py','container_builtins_tests.log')\n"+anchor)
        if p.name=='verify_object_routes_after_ab.py':
            anchor="    result=dict(scalar_truth_cases=truth_report['cases'],"
            insertion="    from verify_native_container_builtins import verify as verify_builtins\n    builtin=target/'container_builtins';builtin.mkdir()\n    builtins_report=verify_builtins(WORK/'bundle_src',WORK/'bundle.dll',builtin/'correctness.json')\n"
            t=once(t,anchor,insertion+anchor.replace('result=dict(','result=dict(container_builtin_cases=builtins_report[\'cases\'],'))
        if p.name=='install_verified.py':
            anchor="    assert post_ab['scalar_truth_cases']==34400"
            t=once(t,anchor,anchor+"\n    assert post_ab['container_builtin_cases']==128128\n    builtin=json.loads((WORK/'container_builtins_tests.json').read_bytes());assert builtin['passed'] and builtin['cases']==128128 and builtin['dll_sha256']==actual")
        if p.name=='verify_installed.py':
            anchor="    truth=read('scalar_truth_tests.json');assert truth['passed'] and truth['cases']==34400 and truth['dll_sha256']==actual"
            t=once(t,anchor,anchor+"\n    builtin=read('container_builtins_tests.json');assert builtin['passed'] and builtin['cases']==128128 and builtin['dll_sha256']==actual")
        save(WORK/p.name,t)
    save(WORK/'verify_container_builtins.py',f'''import sys
from pathlib import Path
WORK=Path(__file__).resolve().parent
sys.path.insert(0,str(WORK.parents[1]))
from verify_native_container_builtins import verify
if __name__=='__main__':
    report=verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'container_builtins_tests.json')
    assert report['cases']==128128 and report['fixture_sha256']=='{sha(STAGE/'test_native_container_builtins.cpp')}'
''')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp','bounded_followup_policy.json'):(WORK/name).write_bytes((ACCEPTED/name).read_bytes())
    plan=json.loads((ACCEPTED/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,latest_remote_verified_production_backup=ARCHIVE,
        baseline_source_files=708,candidate_source_files=708,full_source_changes=['native_inline_dispatch.hpp'],
        components=['missing array builtins','dictionary keys/values','enum reads'],container_builtin_cases=128128,
        container_builtin_fixture_sha256=sha(STAGE/'test_native_container_builtins.cpp'),
        diagnostic_counts='native_perf50/method_dispatch_probe_20261126/counts.json',
        diagnostic_counts_sha256=sha(STAGE/'native_perf50/method_dispatch_probe_20261126/counts.json'),
        diagnostic_frequencies_not_release_cost_or_gain=True,all_prior_components_retained=True,
        semantic_suite_sha256=sha(PROBE/'semantic_suite.json'))
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    save(STAGE/'verify_container_builtins_build_options.py',adapt((STAGE/'verify_frame_values_build_options.py').read_text('utf8')))
    save(STAGE/'run_container_builtins_formal.py',adapt((STAGE/'run_frame_values_formal.py').read_text('utf8')))
    save(STAGE/'close_container_builtins_round.py',adapt((STAGE/'close_frame_values_round.py').read_text('utf8')))
    review=adapt((STAGE/'review_frame_values_release.py').read_text('utf8'))
    review=once(review,"'private_snapshots_tests.json','scalar_truth_tests.json')","'private_snapshots_tests.json','scalar_truth_tests.json','container_builtins_tests.json')")
    anchor="    assert read('scalar_truth_tests.json')['cases']==read('post_ab_directed_regressions.json')['scalar_truth_cases']==34400"
    review=once(review,anchor,anchor+"\n    assert read('container_builtins_tests.json')['cases']==read('post_ab_directed_regressions.json')['container_builtin_cases']==128128")
    save(STAGE/'review_container_builtins_release.py',review)
    print(json.dumps(dict(prepared=True,scripts=len(list(WORK.glob('*.py'))),source_files=708,total_semantic_cases=463904)),flush=True)

if __name__=='__main__':main()
