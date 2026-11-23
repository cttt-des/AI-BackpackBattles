"""Prepare a new, bounded formal protocol; never reuse prior timing data."""
import ast
import json
from prepare_native_event_factory import STAGE, once

OLD=STAGE/'native_perf50/coallocated_events_bundle'
WORK=STAGE/'native_perf50/event_factory_bundle'

def main():
    assert not WORK.exists();WORK.mkdir()
    for p in OLD.glob('*.py'):
        if p.name in ('save_checkpoint.py','verify_coallocated_events.py','verified_bundle_pending.py'):
            continue
        t=p.read_text('utf8').replace('coallocated_events_bundle','event_factory_bundle')
        t=t.replace('native-coallocated-events-','native-event-factory-')
        t=t.replace('prepare_native_coallocated_events','prepare_native_event_factory')
        t=t.replace('prototype_native_coallocated_events_bundle','prototype_native_event_factory_bundle')
        t=t.replace('coallocated_events_prototype','event_factory_prototype')
        if p.name=='validate_then_compare.py':
            t=once(t,"run('verify_coallocated_events.py','coallocated_events_tests.log')",
                     "run('verify_event_factory.py','event_factory_tests.log')")
        if p.name=='verify_installed.py':
            t=t.replace('coallocated_events_tests.json','event_factory_tests.json').replace("['cases']==4161","['cases']==5120")
            t=t.replace("'coallocated_component_cases':4161","'event_factory_cases':5120")
        ast.parse(t,filename=p.name)
        (WORK/p.name).write_text(t,encoding='utf8',newline='\n')
    wrapper="import sys\nfrom pathlib import Path\nWORK=Path(__file__).resolve().parent\nsys.path.insert(0,str(WORK.parents[1]))\nfrom verify_native_event_factory import verify\nif __name__=='__main__':verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'event_factory_tests.json')\n"
    (WORK/'verify_event_factory.py').write_text(wrapper,encoding='utf8')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp','bounded_followup_policy.json'):
        (WORK/name).write_bytes((OLD/name).read_bytes())
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(components=['fused closed event construction and distinct dictionary storage'],
        local_independent_cases=dict(event_factory=5120),
        local_original_dll_cases=5120,rejected_trial_archive_upload_pending=False,
        latest_remote_verified_production_backup='a3e6658fea86d306fbfb3e84dcc7d65918853b24',
        prior_trial_remote_archive='d0f4c2e3e5281dfc7375db924a0326db102ff200',
        rejected_frame_proof_combination_included=False,rejected_frame_inline_included=False,
        full_source_changes=['gen/shards/shard_05.cpp'],
        prior_coallocated_source_not_retested=True,
        no_extrapolated_load20_if_outside_observations=True)
    plan['required'][0]='Retained regressions plus5120 actual-DLL event factory cases; all707 sources reproduced before freshPGO'
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared new event factory protocol; correctness remains prerequisite')

if __name__=='__main__':main()
