"""Preserve the fixed200, strict2604, first24 and independent calibration gates."""
import ast
import json
from pathlib import Path
from prepare_native_frame_proof import STAGE,once
OLD=STAGE/'native_perf50/frame_proof_bundle'
WORK=STAGE/'native_perf50/coallocated_events_bundle'
ARCHIVE='1b18298e39ed36f0fd0dbe5d0e00699d9407c643'

def main():
    assert not WORK.exists();WORK.mkdir()
    for p in OLD.glob('*.py'):
        if p.name in ('verified_bundle_pending.py','verify_frame_proof.py'):continue
        t=p.read_text('utf8').replace('frame_proof_bundle','coallocated_events_bundle')
        t=t.replace('native-frame-proof-','native-coallocated-events-')
        t=t.replace('prepare_native_frame_proof','prepare_native_coallocated_events')
        t=t.replace('frame_proof_prototype/transform.json','coallocated_events_prototype/transform.json')
        if p.name=='validate_then_compare.py':
            t=t.replace("run('verify_frame_proof.py','frame_proof_tests.log')","run('verify_coallocated_events.py','coallocated_events_tests.log')")
        if p.name=='build_bundle.py':
            line="    assert git('ls-remote','--exit-code','origin','refs/heads/codex/native-perf50-verified').decode().split()[0]==ARCHIVE"
            t=once(t,line,"    backup=json.loads((STAGE/'native_perf50/display_defaults_bundle/checkpoint_rejection_receipt.json').read_bytes())\n    assert backup['remote_verified_commit']==ARCHIVE and backup['unchanged_runtime_dll_sha256']==BASE_SHA")
        if p.name=='verify_installed.py':
            t=t.replace('frame_proof_tests.json','coallocated_events_tests.json')
            t=t.replace("read('coallocated_events_tests.json')['cases']==3073","read('coallocated_events_tests.json')['cases']==4161")
            t=t.replace("'frame_header_proof_cases':3073","'coallocated_component_cases':4161")
        ast.parse(t,filename=p.name);(WORK/p.name).write_text(t,encoding='utf8',newline='\n')
    wrapper="import sys\nfrom pathlib import Path\nWORK=Path(__file__).resolve().parent\nsys.path.insert(0,str(WORK.parents[1]))\nfrom verify_native_coallocated_events import verify\nif __name__=='__main__':verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'coallocated_events_tests.json')\n"
    (WORK/'verify_coallocated_events.py').write_text(wrapper,encoding='utf8')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp','bounded_followup_policy.json'):(WORK/name).write_bytes((OLD/name).read_bytes())
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(verified_remote_backup=ARCHIVE,components=['one allocation per short event dictionary','inline existing frame kernel'],
        local_independent_cases=dict(frame=3073,event_params=1024,storage_lifetime=64),
        rejected_frame_proof_combination_included=False,production_unchanged_since_last_verified_remote_backup=True,
        rejected_trial_archive_upload_pending=True,no_extrapolated_load20_if_outside_observations=True)
    plan['required'][0]='Retained regressions plus4161 actual-DLL frame/event/storage cases; all source reproduced before freshPGO'
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared formal protocol; execution remains gated on4161 actual-DLL cases')

if __name__=='__main__':main()
