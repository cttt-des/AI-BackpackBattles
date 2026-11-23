"""Retain the full fixed-corpus gates for the tick-header proof bundle."""
import ast
import json
from pathlib import Path
from prepare_native_frame_proof import STAGE,ARCHIVE,once

OLD=STAGE/'native_perf50/event_capacity_bundle'
WORK=STAGE/'native_perf50/frame_proof_bundle'

def main():
    assert not WORK.exists();WORK.mkdir()
    for p in OLD.glob('*.py'):
        if p.name in ('verified_bundle_pending.py','verify_event_capacity.py'):continue
        t=p.read_text('utf8').replace('event_capacity_bundle','frame_proof_bundle')
        t=t.replace('0526a5b0b241cc76c25c9f5d3dfaf9ef24710114',ARCHIVE)
        t=t.replace('native-event-capacity-','native-frame-proof-')
        if p.name=='validate_then_compare.py':
            t=once(t,"run('verify_event_capacity.py','event_capacity_tests.log')", "run('verify_frame_proof.py','frame_proof_tests.log')")
        if p.name=='verify_targeted_timers.py':t=t.replace('event_capacity_prototype/transform.json','frame_proof_prototype/transform.json')
        if p.name in ('verify_closed_registry_current.py','verify_integer_grid.py'):
            t=t.replace('prepare_native_event_capacity','prepare_native_frame_proof')
        if p.name=='verify_installed.py':
            t=t.replace('event_capacity_tests.json','frame_proof_tests.json')
            t=t.replace("read('frame_proof_tests.json')['cases']==1024","read('frame_proof_tests.json')['cases']==3073")
            t=t.replace("'event_param_capacity_cases':1024","'frame_header_proof_cases':3073")
        if p.name=='inspect_variant.py':
            t=once(t,"    args.out.write_text(", "    for name in ('type_constructor_coverage','frame_segment_coverage'):\n        assert report[name]==retained[name],(name,report[name],retained[name])\n    args.out.write_text(")
        ast.parse(t,filename=p.name);(WORK/p.name).write_text(t,encoding='utf8',newline='\n')
    wrapper="import sys\nfrom pathlib import Path\nWORK=Path(__file__).resolve().parent\nsys.path.insert(0,str(WORK.parents[1]))\nfrom verify_native_frame_proof import verify\nif __name__=='__main__':verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'frame_proof_tests.json')\n"
    (WORK/'verify_frame_proof.py').write_text(wrapper,encoding='utf8',newline='\n')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp'):(WORK/name).write_bytes((OLD/name).read_bytes())
    (WORK/'bounded_followup_policy.json').write_bytes((OLD/'bounded_followup_policy.json').read_bytes())
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(verified_remote_backup=ARCHIVE,components=['reuse checked tick row before callback','two Bool flag specializations'],
        local_independent_cases=dict(frame_header_proof=3073),rejected_display_and_event_capacity_included=False,
        all_object_container_context_layouts_unchanged=True,full20_fresh18_pgo_required=True)
    plan['required'][0]='All retained regressions plus3073 actual-DLL header/flags/row/context/getter/registry/FP/counter differential cases'
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared707-source formal build; fixed200 24/bounded32,2604 and first24 gates retained')

if __name__=='__main__':main()
