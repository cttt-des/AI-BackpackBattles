"""Freeze the original complete evaluation protocol for the new control reads."""
import ast
import json
from pathlib import Path
from prepare_native_control_word import STAGE,WORK as PROBE,BACKUP,ACCEPTED,EXPECTED,ARCHIVE,sha
WORK=STAGE/'native_perf50/control_word_bundle'

def once(t,a,b):
    assert t.count(a)==1,(a[:120],t.count(a));return t.replace(a,b,1)

def main():
    proof=json.loads((PROBE/'correctness.json').read_bytes());assert proof['passed'] and proof['cases']==44608
    assert not WORK.exists();WORK.mkdir()
    for p in BACKUP.glob('*.py'):
        if p.name=='verified_bundle_pending.py':continue
        if p.name=='verify_active_prefetch.py':continue
        t=p.read_text('utf8').replace('active_prefetch_bundle','control_word_bundle')
        t=t.replace('prepare_native_active_prefetch','prepare_native_control_word')
        t=t.replace('prototype_native_control_word_bundle','prototype_native_control_word_bundle')
        t=t.replace('prototype_native_active_prefetch_bundle','prototype_native_control_word_bundle')
        t=t.replace('bcad9e17d0af08821582759a44e0e4e8fe068be3',ARCHIVE)
        if p.name=='build_bundle.py':
            t=once(t,"STAGE/'native_perf50/compiler_pta_bundle/checkpoint_receipt.json'","STAGE/'native_perf50/active_prefetch_bundle/checkpoint_receipt.json'")
            t=t.replace('active-prefetch-formal-','control-word-formal-')
        if p.name=='resume_build.py':
            t=once(t,"exports.update(('gd_diag_native_active_prefetch_stat','gd_test_native_active_prefetch'))","exports.add('gd_test_native_timer_control')")
            # Only this module's bounded instrumentation export function is
            # used. A historical recovery main must not retrain this round.
            t=t.split('\ndef main():',1)[0]
        if p.name=='verify_targeted_timers.py':
            t=once(t,"WORK.parent/'active_prefetch_prototype/transform.json'","WORK.parent/'control_word_prototype/transform.json'")
            t=once(t,"assert sha(WORK/'bundle_src/native_targeted_timers.hpp')==","assert sha(WORK.parent/'object_routes_bundle/bundle_src/native_targeted_timers.hpp')==")
            needle="    closed=WORK.parent/'closed_timer_prototype'"
            t=once(t,needle,"    import sys\n    sys.path.insert(0,str(STAGE))\n    from prepare_native_control_word import verify_projection\n    assert verify_projection(WORK/'bundle_src')['passed']\n"+needle)
        if p.name=='validate_then_compare.py':
            t=t.replace('verify_active_prefetch_build_options.py','verify_control_word_build_options.py')
            t=once(t,"run('verify_active_prefetch.py','active_prefetch_tests.log')","run('verify_control_word.py','control_word_tests.log')")
        if p.name=='verify_object_routes_after_ab.py':
            t=t.replace('verify_native_active_prefetch','verify_native_control_word')
            t=t.replace('verify_prefetch','verify_control').replace("target/'active_prefetch'","target/'control_word'")
            t=once(t,'active_prefetch_cases=12864','control_word_cases=44608')
        if p.name=='inspect_variant.py':
            t=once(t,"    hints=sim.lib.gd_diag_native_active_prefetch_stat;hints.argtypes=[ctypes.c_uint];hints.restype=ctypes.c_uint64\n    hints_before=[hints(i) for i in range(4)]\n",'')
            t=once(t,"    hint_counts=[hints(i)-hints_before[i] for i in range(4)]\n    assert all(v>0 for v in hint_counts) and hint_counts[3]>=5*hint_counts[2],hint_counts\n",'')
            t=once(t,"    report['active_prefetch_coverage']=hint_counts\n",'')
            needle='    assert counts==[9599433,100900,54635,200,0,233004]'
            t=once(t,needle,needle+"\n    assert [targeted(i)-targeted_before[i] for i in range(10)]==[386704,400,386304,683532,0,0,0,16170,701,0]")
        if p.name in ('verify_installed.py','install_verified.py'):
            t=t.replace('active_prefetch_tests.json','control_word_tests.json').replace('active_prefetch_cases','control_word_cases').replace('12864','44608')
        ast.parse(t,filename=p.name);(WORK/p.name).write_text(t,encoding='utf8',newline='\n')
    wrapper='''import sys
from pathlib import Path
WORK=Path(__file__).resolve().parent
sys.path.insert(0,str(WORK.parents[1]))
from verify_native_control_word import verify
if __name__=='__main__':verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'control_word_tests.json')
'''
    (WORK/'verify_control_word.py').write_text(wrapper,encoding='utf8')
    for n in ('member_probe_cases.hpp','native_property_test_cases.hpp','bounded_followup_policy.json'):
        (WORK/n).write_bytes((ACCEPTED/n).read_bytes())
    plan=json.loads((BACKUP/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,
        latest_remote_verified_production_backup=ARCHIVE,prior_trial_remote_archive=ARCHIVE,
        components=['fresh masked reads of three original watch-control predicates'],
        full_source_changes=['gen/shards/shard_03.cpp','native_active_cooldowns.hpp','native_targeted_timers.hpp'],
        compiler_optimization_flags=[],private_snapshots_not_included=True,compiler_pta_not_included=True,
        active_prefetch_not_included=True,intentional_layout_changes=[],new_layout_changes=False,
        local_control_cases=44608,registry_boundary_checks=4,semantic_dll_not_used_for_timing=True)
    for old in ('local_prefetch_cases',):plan.pop(old,None)
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    assert 'gd_diag_native_active_prefetch' not in (WORK/'inspect_variant.py').read_text('utf8')
    assert '-fipa-pta' not in (WORK/'build_bundle.py').read_text('utf8')
    print('Prepared full20/fresh18, retained all original gates and new44608 checks; not started')

if __name__=='__main__':main()
