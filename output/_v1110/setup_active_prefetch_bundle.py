"""Prepare the original complete protocol for one distinct prefetch candidate."""
import ast
import json
from pathlib import Path
from prepare_native_active_prefetch import STAGE,WORK as PROBE,ACCEPTED,BACKUP,EXPECTED,ARCHIVE,sha

WORK=STAGE/'native_perf50/active_prefetch_bundle'

def once(text,old,new):
    assert text.count(old)==1,(old[:110],text.count(old));return text.replace(old,new,1)

def main():
    proof=json.loads((PROBE/'correctness.json').read_bytes())
    assert proof['passed'] and proof['cases']==12864
    assert not WORK.exists();WORK.mkdir()
    for p in BACKUP.glob('*.py'):
        if p.name=='verified_bundle_pending.py':continue
        text=p.read_text('utf8').replace('compiler_pta_bundle','active_prefetch_bundle')
        text=text.replace('prepare_native_compiler_pta','prepare_native_active_prefetch')
        if p.name=='build_bundle.py':
            text=text.replace('from build_native_compiler_pta import','from build_native_hot_lto import')
            text=once(text,'from prepare_native_active_prefetch import optimize','from prototype_native_active_prefetch_bundle import optimize')
            text=text.replace('80c06b2db6f525ae5b0b4acd2f2130f1bd418310',ARCHIVE)
            text=once(text,"STAGE/'native_perf50/private_snapshots_bundle/checkpoint_receipt.json'","STAGE/'native_perf50/compiler_pta_bundle/checkpoint_receipt.json'")
            text=text.replace('compiler-pta-formal-','active-prefetch-formal-')
            text=once(text,",'compiler_optimization_flags':['-fipa-pta'],'same_compiler_configuration_in_both_profile_phases':True",",'compiler_optimization_flags':[],'same_compiler_configuration_in_both_profile_phases':True")
        if p.name=='resume_build.py':
            text=text.replace('from build_native_compiler_pta import','from build_native_hot_lto import')
            text=once(text,"    definition=objects/'instrumented_exports.def'","    exports.update(('gd_diag_native_active_prefetch_stat','gd_test_native_active_prefetch'))\n    definition=objects/'instrumented_exports.def'")
        if p.name=='verify_targeted_timers.py':
            text=once(text,"WORK.parent/'object_routes_prototype/transform.json'","WORK.parent/'active_prefetch_prototype/transform.json'")
        if p.name=='validate_then_compare.py':
            text=once(text,"    run('verify_active_cooldowns.py','active_cooldown_tests.log')","    run('verify_active_cooldowns.py','active_cooldown_tests.log')\n    run('verify_active_prefetch.py','active_prefetch_tests.log')")
        if p.name=='verify_object_routes_after_ab.py':
            text=once(text,"    result=dict(passed=True", "    from verify_native_active_prefetch import verify as verify_prefetch\n    hints=target/'active_prefetch';hints.mkdir()\n    verify_prefetch(WORK/'bundle_src',WORK/'bundle.dll',hints/'correctness.json')\n    result=dict(active_prefetch_cases=12864,passed=True")
        if p.name=='inspect_variant.py':
            text=once(text,"    audit(1);before=[stat(i) for i in range(6)]","    hints=sim.lib.gd_diag_native_active_prefetch_stat;hints.argtypes=[ctypes.c_uint];hints.restype=ctypes.c_uint64\n    hints_before=[hints(i) for i in range(4)]\n    audit(1);before=[stat(i) for i in range(6)]")
            text=once(text,"    args.out.write_text(","    hint_counts=[hints(i)-hints_before[i] for i in range(4)]\n    assert all(v>0 for v in hint_counts) and hint_counts[3]>=5*hint_counts[2],hint_counts\n    assert [active(i)-active_before[i] for i in range(10)]==[386704,1904,384800,3632134,0,760,23435,83822,19040,0]\n    assert counts==[9599433,100900,54635,200,0,233004]\n    report['active_prefetch_coverage']=hint_counts\n    args.out.write_text(")
        if p.name=='verify_installed.py':
            text=once(text,"assert profile['compiler_optimization_flags']==['-fipa-pta']", "assert profile['compiler_optimization_flags']==[]")
            text=once(text,"    options=read('compiled_option_receipt.json')\n    assert options['passed'] and options['checked_hot_objects']==18 and options['fp_contract_off_all'] and options['flags_identical_except_pta_and_profile_directory']", "    hints=read('active_prefetch_tests.json')\n    assert hints['passed'] and hints['dll_sha256']==actual and hints['cases']==12864")
        ast.parse(text,filename=p.name);(WORK/p.name).write_text(text,encoding='utf8',newline='\n')
    verifier='''import sys
from pathlib import Path
WORK=Path(__file__).resolve().parent
sys.path.insert(0,str(WORK.parents[1]))
from verify_native_active_prefetch import verify
if __name__=='__main__':verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'active_prefetch_tests.json')
'''
    (WORK/'verify_active_prefetch.py').write_text(verifier,encoding='utf8',newline='\n')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp','bounded_followup_policy.json'):
        (WORK/name).write_bytes((ACCEPTED/name).read_bytes())
    plan=json.loads((BACKUP/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,
        latest_remote_verified_production_backup=ARCHIVE,prior_trial_remote_archive=ARCHIVE,
        components=['distance3 address-only active owner/display prefetch'],
        full_source_changes=['gen/shards/shard_03.cpp','native_active_cooldowns.hpp'],
        compiler_optimization_flags=[],private_snapshots_not_included=True,compiler_pta_not_included=True,
        intentional_layout_changes=['private NativeActiveCooldownCache56->64; no public layout change'],
        new_layout_changes=True,local_prefetch_cases=12864,semantic_dll_not_used_for_timing=True)
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    assert '-fipa-pta' not in (WORK/'build_bundle.py').read_text('utf8')
    print('Prepared full20/fresh18 protocol, frozen24/32 A/B and all original gates; not started')

if __name__=='__main__':main()
