"""Carry forward the frozen comparison/release protocol to event-param storage."""
import ast
import json
from pathlib import Path
STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/grid_cooldown_bundle'
WORK=STAGE/'native_perf50/event_capacity_bundle'
BASE='e0bedc4960077407e85763cb5e4af70175a0623cca15e923403fa89174390687'
ARCHIVE='0526a5b0b241cc76c25c9f5d3dfaf9ef24710114'

def once(t,a,b):
    assert t.count(a)==1,(a[:120],t.count(a));return t.replace(a,b,1)

def main():
    assert not WORK.exists();WORK.mkdir()
    for p in OLD.glob('*.py'):
        if p.name=='verified_bundle_pending.py':continue
        t=p.read_text('utf8').replace('grid_cooldown_bundle','event_capacity_bundle').replace('active_cooldown_bundle','grid_cooldown_bundle')
        t=t.replace('55b62a2044b87311a967878a91d88ef4702641d240594989a09c396f67172ece',BASE).replace('f67e7c55fd5d4c161b6ab3c81d925d2ba7ea5ffd',ARCHIVE)
        t=t.replace('native-grid-cooldown-','native-event-capacity-')
        if p.name=='build_bundle.py':
            t=t.replace('==706','==707').replace("'verified_source_files':706","'verified_source_files':707").replace('and706 sources','and707 sources')
        if p.name=='validate_then_compare.py':
            t=once(t,"    run('verify_integer_grid.py','integer_grid_tests.log')","    run('verify_integer_grid.py','integer_grid_tests.log')\n    run('verify_event_capacity.py','event_capacity_tests.log')")
        if p.name=='verify_targeted_timers.py':
            t=t.replace('grid_cooldown_prototype/transform.json','event_capacity_prototype/transform.json')
        if p.name=='verify_closed_registry_current.py':
            t=t.replace('from prepare_native_integer_grid import BASE,STAGE,EXPECTED,sha','from prepare_native_event_capacity import BASE,STAGE,EXPECTED,sha')
        if p.name=='verify_installed.py':
            assert t.count("'integer_grid_tests.json','integer_grid_dictionary_tests.json'")==2
            t=t.replace("'integer_grid_tests.json','integer_grid_dictionary_tests.json'","'event_capacity_tests.json','integer_grid_tests.json','integer_grid_dictionary_tests.json'")
            marker="    assert read('active_cooldown_tests.json')['cases']==1856"
            t=once(t,marker,"    assert read('event_capacity_tests.json')['cases']==1024\n"+marker)
            t=once(t,"'integer_grid_dictionary_cases':1792,","'event_param_capacity_cases':1024,'integer_grid_dictionary_cases':1792,")
            # Include the new actual-DLL receipt among the final hashed evidence.
            t=t.replace("'source_before_build.json','bundle_full_gate.json'","'event_capacity_tests.json','source_before_build.json','bundle_full_gate.json'")
        if p.name=='save_checkpoint.py':
            t=once(t,'    audit=json.loads',"    paths.update(STAGE/p for p in ('inspect_native_event_param_capacity.py','prepare_native_event_capacity.py','build_native_event_capacity_prototype.py','test_native_event_capacity.cpp','verify_native_event_capacity.py','prototype_native_event_capacity_bundle.py','setup_event_capacity_bundle.py','preflight_native_event_capacity_bundle.py'))\n    for folder in ('event_param_capacity_probe','event_capacity_prototype'):\n        paths.update(p for p in (WORK.parent/folder).rglob('*') if p.is_file())\n    audit=json.loads")
            # Retain referenced prior root scripts as well as this round's new names.
            t=once(t,'    audit=json.loads',"    paths.update(STAGE/p for p in ('prototype_native_grid_cooldown_bundle.py','setup_grid_cooldown_bundle.py','preflight_native_grid_cooldown_bundle.py'))\n    audit=json.loads")
            t=t.replace('perf: index integer grid cells and hoist cached cooldown guards','perf: reduce event parameter dictionary initial capacity')
            t=t.replace('backup: preserve verified integer grid and cooldown bundle','backup: preserve verified event parameter storage')
        if p.name=='verify_integer_grid.py':
            t='''import json
from pathlib import Path
import sys
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
sys.path.insert(0,str(STAGE))
from prepare_native_event_capacity import BASE,EXPECTED,sha
import verify_native_integer_grid_dict as dictionaries
from verify_native_integer_grid_queries import verify as queries

def main():
    source=WORK/'bundle_src';dll=WORK/'bundle.dll';out=WORK/'integer_grid_tests.json'
    assert not out.exists()
    dictionaries.BASE=BASE;dictionaries.EXPECTED=EXPECTED
    a=dictionaries.verify(source,dll,WORK/'integer_grid_dictionary_tests.json')
    b=queries(source,dll,WORK/'integer_grid_query_tests.json')
    scalar=STAGE/'native_perf50/integer_grid_prototype/slot_correctness.json'
    assert json.loads(scalar.read_bytes())['helper_sha256']==sha(source/'native_integer_grid.hpp')
    result=dict(passed=True,dll_sha256=sha(dll),dictionary_cases=a['cases'],query_cases=b['cases'],scalar_cases=132576,
        actual_optimized_dll_independent_oracles=True,fast_dictionary_queries=a['fast_queries'],
        forced_spatial_fast_queries=b['variants']['forced_grid']['fast_queries'],layouts=a['new_layout'],
        receipt_sha256={name:sha(WORK/name) for name in ('integer_grid_dictionary_tests.json','integer_grid_query_tests.json')},
        scalar_receipt_sha256=sha(scalar))
    out.write_text(json.dumps(result,indent=2)+'\\n',encoding='utf8');print(json.dumps(result,indent=2))
if __name__=='__main__':main()
'''
        ast.parse(t,filename=p.name);(WORK/p.name).write_text(t,encoding='utf8',newline='\n')
    wrapper="import sys\nfrom pathlib import Path\nWORK=Path(__file__).resolve().parent\nsys.path.insert(0,str(WORK.parents[1]))\nfrom verify_native_event_capacity import verify\nif __name__=='__main__':verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'event_capacity_tests.json')\n"
    (WORK/'verify_event_capacity.py').write_text(wrapper,encoding='utf8',newline='\n')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp'):(WORK/name).write_bytes((OLD/name).read_bytes())
    policy=json.loads((OLD/'bounded_followup_policy.json').read_bytes())
    (WORK/'bounded_followup_policy.json').write_text(json.dumps(policy,indent=2)+'\n',encoding='utf8')
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=BASE,verified_remote_backup=ARCHIVE,baseline_source_files=707,candidate_source_files=707,
        components=['event.params canonical empty dictionary first String write reserves4'],intentional_layout_changes=[],
        private_cooldown_cache_adds_grid_pointer=False,local_independent_cases=dict(event_params=1024),
        semantic_native_cache_not_used_for_formal_timing=True,full20_fresh18_pgo_required=True,
        no_standalone_grid_or_guard_speed_claim=True,prior_declared_bounded_followup_rule_retained=True)
    plan['required'][0]+=';1024 event-param alias/growth/FP cases on the actual final DLL'
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared event storage candidate: full20/new18PGO; fixed200 24/bounded32,2604 and first24 retained')

if __name__=='__main__':main()
