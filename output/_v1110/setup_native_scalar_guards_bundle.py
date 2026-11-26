"""Freeze the next distinct combination with the original acceptance protocol."""
import ast
import json
from pathlib import Path
from prepare_native_scalar_guards import STAGE,WORK as PROBE,ACCEPTED,RETAINED,EXPECTED,ARCHIVE,sha

WORK=STAGE/'native_perf50/scalar_guards_bundle'
OLD_ARCHIVE='6ceab43e0324e20b4d9d96b75828253c265dcc2c'

def once(t,a,b):
    assert t.count(a)==1,(a[:160],t.count(a));return t.replace(a,b,1)
def save(p,t):
    ast.parse(t,filename=str(p));assert not p.exists();p.write_text(t,encoding='utf8',newline='\n')
def adapt(t):
    for a,b in [('prototype_restored_snapshots_bundle','prototype_native_scalar_guards_bundle'),
            ('prepare_restored_private_snapshots','prepare_native_scalar_guards'),
            ('verify_restored_private_snapshots','verify_scalar_guard_private'),
            ('verify_restored_display_storage','verify_scalar_guard_display'),('verify_restored_control','verify_scalar_guard_control'),
            ('verify_restored_snapshots_build_options','verify_scalar_guards_build_options'),
            ('restored_snapshots_bundle','scalar_guards_bundle'),('restored_snapshots_prototype','scalar_guards_prototype'),
            ('restored-snapshots-formal-','scalar-guards-formal-'),(OLD_ARCHIVE,ARCHIVE)]:t=t.replace(a,b)
    return t

def main():
    suite=json.loads((PROBE/'semantic_suite.json').read_bytes());assert suite['passed']
    truth_cases=suite['cases']['scalar_truth'];assert truth_cases>30000
    assert not WORK.exists();WORK.mkdir()
    for p in RETAINED.glob('*.py'):
        if p.name=='verified_bundle_pending.py':continue
        t=adapt(p.read_text('utf8'))
        if p.name=='build_bundle.py':
            t=once(t,"STAGE/'native_perf50/display_storage_bundle/checkpoint_receipt.json'","STAGE/'native_perf50/restored_snapshots_bundle/checkpoint_receipt.json'")
        if p.name=='validate_then_compare.py':
            anchor="    run('verify_private_snapshots.py','private_snapshots_tests.log')"
            t=once(t,anchor,"    run('verify_scalar_truth.py','scalar_truth_tests.log')\n"+anchor)
        if p.name=='verify_motion_indices.py':
            t=once(t,"    assert method_sha==retained['candidate_method_sha256']",
                "    assert 'native_scalar_truth(' in method\n    original_method=method.replace('native_scalar_truth(', 'gd_truth(')\n    original_sha=hashlib.sha256(original_method.encode()).hexdigest()\n    assert original_sha==retained['candidate_method_sha256']\n    from prepare_native_scalar_guards import verify_projection\n    assert verify_projection(WORK/'bundle_src')['exact_inverse_matches_retained_source']")
            t=once(t,'source_method_sha256=method_sha)','source_method_sha256=method_sha,source_before_scalar_truth_sha256=original_sha,exact_inverse_verified=True)')
        if p.name=='verify_object_routes_after_ab.py':
            anchor="    result=dict(private_snapshot_cases=234880,display_storage_cases=21888,control_word_cases=44608,"
            insertion="    from verify_native_scalar_guards import verify as verify_truth\n    truth=target/'scalar_truth';truth.mkdir()\n    truth_report=verify_truth(WORK/'bundle_src',WORK/'bundle.dll',truth/'correctness.json')\n"
            t=once(t,anchor,insertion+anchor.replace('result=dict(','result=dict(scalar_truth_cases=truth_report[\'cases\'],'))
        if p.name=='install_verified.py':
            anchor="    assert post_ab['private_snapshot_cases']==234880"
            t=once(t,anchor,anchor+f"\n    assert post_ab['scalar_truth_cases']=={truth_cases}\n    truth=json.loads((WORK/'scalar_truth_tests.json').read_bytes());assert truth['passed'] and truth['cases']=={truth_cases} and truth['dll_sha256']==actual")
        if p.name=='verify_installed.py':
            anchor="    private=read('private_snapshots_tests.json');assert private['passed'] and private['cases']==234880 and private['dll_sha256']==actual"
            t=once(t,anchor,anchor+f"\n    truth=read('scalar_truth_tests.json');assert truth['passed'] and truth['cases']=={truth_cases} and truth['dll_sha256']==actual")
        save(WORK/p.name,t)
    save(WORK/'verify_scalar_truth.py',f'''import sys
from pathlib import Path
WORK=Path(__file__).resolve().parent
sys.path.insert(0,str(WORK.parents[1]))
from verify_native_scalar_guards import verify
if __name__=='__main__':
    report=verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'scalar_truth_tests.json')
    assert report['cases']=={truth_cases} and report['fixture_sha256']=='{sha(STAGE/'test_native_scalar_truth.cpp')}'
''')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp','bounded_followup_policy.json'):(WORK/name).write_bytes((RETAINED/name).read_bytes())
    plan=json.loads((RETAINED/'evaluation_plan.json').read_bytes())
    plan.update(verified_remote_backup=ARCHIVE,latest_remote_verified_production_backup=ARCHIVE,
        components=['retained private snapshots','scalar truth guards'],
        full_source_changes=['gd_rt.hpp',*[f'gen/shards/shard_{i:02d}.cpp' for i in range(16)],'native_private_snapshots.hpp'],
        scalar_truth_cases=truth_cases,scalar_truth_fixture_sha256=sha(STAGE/'test_native_scalar_truth.cpp'),
        existing_scalar_equality_unchanged=True,prior_same_source32_not_repeated=True,
        semantic_suite_sha256=sha(PROBE/'semantic_suite.json'),full20_new18PGO_required=True)
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    save(STAGE/'verify_scalar_guards_build_options.py',adapt((STAGE/'verify_restored_snapshots_build_options.py').read_text('utf8')))
    driver=adapt((STAGE/'run_restored_snapshots_formal_second.py').read_text('utf8'))
    driver=once(driver,'ACCEPTED as BACKUP','RETAINED as BACKUP')
    driver=once(driver,"PROBE/'correctness.json'","PROBE/'semantic_suite.json'")
    driver=driver.replace('build_second.log','build_first.log').replace('qualification_second.log','qualification_first.log')
    save(STAGE/'run_scalar_guards_formal.py',driver)
    save(STAGE/'close_scalar_guards_round.py',adapt((STAGE/'close_restored_snapshots_round.py').read_text('utf8')))
    review=adapt((STAGE/'review_restored_snapshots_release.py').read_text('utf8'))
    review=once(review,"['gen/shards/shard_00.cpp','gen/shards/shard_12.cpp','native_private_snapshots.hpp']", "sorted(['gd_rt.hpp',*[f'gen/shards/shard_{i:02d}.cpp' for i in range(16)],'native_private_snapshots.hpp'])")
    review=once(review,"'display_storage_tests.json','private_snapshots_tests.json')","'display_storage_tests.json','private_snapshots_tests.json','scalar_truth_tests.json')")
    anchor="    assert read('private_snapshots_tests.json')['cases']==234880 and read('post_ab_directed_regressions.json')['private_snapshot_cases']==234880"
    review=once(review,anchor,anchor+f"\n    assert read('scalar_truth_tests.json')['cases']==read('post_ab_directed_regressions.json')['scalar_truth_cases']=={truth_cases}")
    save(STAGE/'review_scalar_guards_release.py',review)
    for p in WORK.glob('*.py'):ast.parse(p.read_text('utf8'),filename=str(p))
    print(json.dumps(dict(prepared=True,truth_cases=truth_cases,source_files=708,scripts=len(list(WORK.glob('*.py'))),new_branches=0)),flush=True)

if __name__=='__main__':main()
