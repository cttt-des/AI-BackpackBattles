"""Prepare fresh full20/new18PGO and the unchanged bounded measurement policy."""
import ast
import json
from prepare_native_storage_bundle import STAGE,once,EXPECTED,ARCHIVE

OLD=STAGE/'native_perf50/event_factory_bundle'
WORK=STAGE/'native_perf50/storage_bundle'

def main():
    assert not WORK.exists();WORK.mkdir()
    for p in OLD.glob('*.py'):
        if p.name in ('verified_bundle_pending.py','verify_factory_after_ab.py'):continue
        t=p.read_text('utf8')
        t=t.replace('event_factory_bundle','storage_bundle').replace('event_factory_prototype','storage_prototype')
        t=t.replace('grid_cooldown_bundle','event_factory_bundle')
        t=t.replace('prepare_native_event_factory','prepare_native_storage_bundle')
        t=t.replace('prototype_native_event_factory_bundle','prototype_native_storage_bundle')
        t=t.replace('native-event-factory-','native-storage-')
        t=t.replace('e0bedc4960077407e85763cb5e4af70175a0623cca15e923403fa89174390687',EXPECTED)
        t=t.replace('1b18298e39ed36f0fd0dbe5d0e00699d9407c643',ARCHIVE)
        t=t.replace('verify_factory_after_ab.py','verify_storage_after_ab.py')
        if p.name=='build_bundle.py':
            a="    backup=json.loads((STAGE/'native_perf50/display_defaults_bundle/checkpoint_rejection_receipt.json').read_bytes())\n    assert backup['remote_verified_commit']==ARCHIVE and backup['unchanged_runtime_dll_sha256']==BASE_SHA"
            b="    backup=json.loads((STAGE/'native_perf50/event_factory_bundle/checkpoint_receipt.json').read_bytes())\n    assert backup['remote_verified_commit']==ARCHIVE and backup['production_dll_sha256']==BASE_SHA"
            t=once(t,a,b)
        if p.name=='validate_then_compare.py':
            t=once(t,"    run('verify_resolved.py','verify.log')", "    run('verify_storage.py','storage_tests.log')\n    run('verify_resolved.py','verify.log')")
        if p.name=='install_verified.py':
            t=once(t,"post_ab['affected_factory_cases'] == 5120","post_ab['affected_storage_cases'] == 87425")
        if p.name=='run_release_measurements.py':
            t=once(t,"'minimum_fights_per_second':min(speed),","'minimum_fights_per_second':min(speed),'maximum_fights_per_second':max(speed),")
        if p.name=='verify_installed.py':
            t=once(t,"    assert read('event_factory_tests.json')['cases']==5120", "    assert read('event_factory_tests.json')['cases']==5120\n    assert read('storage_tests.json')['passed'] and read('storage_tests.json')['cases']==87425\n    assert read('storage_tests.json')['dll_sha256']==actual")
            t=once(t,"'event_factory_cases':5120,","'storage_cases':87425,'event_factory_cases':5120,")
            t=t.replace("('event_factory_tests.json','source_before_build.json'","('storage_tests.json','post_ab_directed_regressions.json','event_factory_tests.json','source_before_build.json'")
        ast.parse(t,filename=p.name);(WORK/p.name).write_text(t,encoding='utf8',newline='\n')
    wrapper="import sys\nfrom pathlib import Path\nWORK=Path(__file__).resolve().parent\nsys.path.insert(0,str(WORK.parents[1]))\nfrom verify_native_storage_bundle import verify\nif __name__=='__main__':verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'storage_tests.json')\n"
    (WORK/'verify_storage.py').write_text(wrapper,encoding='utf8')
    after=(OLD/'verify_factory_after_ab.py').read_text('utf8')
    after=once(after,'from prepare_native_event_factory import sha','from prepare_native_storage_bundle import sha')
    after=once(after,'from verify_native_event_factory import verify','from verify_native_storage_bundle import verify')
    after=after.replace("target/'event_factory.json'","target/'storage.json'").replace('affected_factory_cases=5120','affected_storage_cases=87425')
    ast.parse(after);(WORK/'verify_storage_after_ab.py').write_text(after,encoding='utf8',newline='\n')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp','bounded_followup_policy.json'):
        (WORK/name).write_bytes((OLD/name).read_bytes())
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,
        latest_remote_verified_production_backup=ARCHIVE,components=['CoreItem independent container batch','strings and reserved containers coallocation'],
        local_independent_cases=dict(runtime=1025,constructors=86400),local_original_dll_cases=87425,
        full_source_changes=['gd_rt.cpp','gen/shards/shard_00.cpp'],
        previous_deployed_event_factory_retained=True,prior_trial_remote_archive=ARCHIVE,
        old_source_not_retimed=True,include_median_minimum_maximum_and_load20_every_round=True)
    plan['required'][0]='Retained regressions plus87425 actual-DLL storage/constructor cases; all707 sources reproduced before freshPGO'
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared storage protocol; source-specific correctness and count probe remain required')

if __name__=='__main__':main()
