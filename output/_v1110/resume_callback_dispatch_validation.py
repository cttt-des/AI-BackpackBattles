"""Continue remaining checks once, after repairing the stale pre-AB harness."""
import hashlib
import json
from pathlib import Path
import subprocess
import sys
import psutil
from prepare_native_callback_dispatch import STAGE,BASE,WORK as PROBE,EXPECTED,sha

WORK=STAGE/'native_perf50/callback_dispatch_bundle'
FORMAL='80a0681c1c93268af2b29c21e5439b6444de36a29ad39486b3f4afadf548a44a'

def save(name,value):(WORK/name).write_text(json.dumps(value,indent=2)+'\n',encoding='utf8')
def source_manifest():return {p.relative_to(WORK/'bundle_src').as_posix():sha(p) for p in (WORK/'bundle_src').rglob('*') if p.is_file()}
def run(script,log,*args):
    path=WORK/log;assert not path.exists(),path
    print('Starting '+script,flush=True)
    with path.open('w',encoding='utf8') as output:
        subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/script),*map(str,args)],stdout=output,stderr=subprocess.STDOUT,check=True)
    print('Passed '+script,flush=True)

def main():
    continuation='--continue-harness-repair-2' in sys.argv
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert not (WORK/'comparison.log').exists() and not (WORK/'ab_assessment.json').exists()
    marker=WORK/('resume_validation_second.log' if continuation else 'resume_validation_first.log')
    assert not marker.exists(),'Use the live process or existing result; never restart observed timings'
    if continuation:
        assert (WORK/'validation_harness_repair_2.json').exists()
        previous=json.loads((WORK/'live_resumed_validation.json').read_bytes())
        if psutil.pid_exists(previous['pid']):assert abs(psutil.Process(previous['pid']).create_time()-previous['created'])>=.001
    original=json.loads((WORK/'live_build.json').read_bytes())
    if psutil.pid_exists(original['pid']):
        assert abs(psutil.Process(original['pid']).create_time()-original['created'])>=.001,'Original build still active'
    assert sha(WORK/'bundle.dll')==FORMAL
    assert sha(BASE/'libgdcore.dll')==sha(STAGE.parents[1]/'dist/native_1_1_10/libgdcore.dll')==EXPECTED
    frozen=json.loads((WORK/'source_before_build.json').read_bytes())
    assert frozen==source_manifest()==json.loads((PROBE/'transform.json').read_bytes())['source_sha256']
    repair=json.loads((WORK/'validation_harness_repair.json').read_bytes())
    assert repair['formal_dll_sha256']==FORMAL and repair['no_ab_or_release_measurement_had_started']
    profile=json.loads((WORK/'fresh_profile_source.json').read_bytes())
    assert profile['dll_sha256']==FORMAL and profile['profile_training_and_release_source_identical']
    assert json.loads((WORK/'frozen_pgo_manifest.json').read_bytes())['counts']==profile['hot_profiles_sha256']
    retained=('event_identity_tests.json','lazy_diagnostics_tests.json','member_frame_tests.json',
              'static_collections_tests.json','static_setup_tests.json','dispatch_chain_tests.json',
              'spatial_tests.json','motion_indices_tests.json')
    for name in retained:
        record=json.loads((WORK/name).read_bytes());assert record['passed'],name
        if 'dll_sha256' in record:assert record['dll_sha256']==FORMAL,name
    p=psutil.Process();save('live_resumed_validation.json',dict(pid=p.pid,created=p.create_time(),script=str(Path(__file__).resolve()),
        original_build=original,formal_dll_sha256=FORMAL,retained_passed_receipts={n:sha(WORK/n) for n in retained}))
    # This marker prevents a second invocation; original failure logs remain intact.
    marker.write_text('Continuing after preserved stale-fingerprint failure; no rebuild or timing restart\n',encoding='utf8')
    if continuation:run('verify_targeted_timers.py','targeted_timer_tests_resumed_second.log','--resume-checked-cases')
    else:run('verify_targeted_timers.py','targeted_timer_tests_resumed_first.log')
    for script,log in [('verify_active_cooldowns.py','active_cooldown_tests.log'),('verify_integer_grid.py','integer_grid_tests.log'),
        ('verify_event_factory.py','event_factory_tests.log'),('verify_literal_spans.py','literal_span_tests.log'),
        ('verify_callback_dispatch.py','callback_dispatch_tests.log'),('verify_resolved.py','verify.log')]:run(script,log)
    run('inspect_variant.py','release_audit.log','--dll',WORK/'bundle.dll','--out',WORK/'release_audit.json')
    run('test_regeneration_guards.py','regeneration_guards.log')
    run('test_full_regeneration.py','full_regeneration.log')
    assert json.loads((WORK/'buff_chunk_differential.json').read_bytes())['passed']
    assert source_manifest()==frozen and sha(WORK/'bundle.dll')==FORMAL
    run('run_comparison.py','comparison.log')
    assert source_manifest()==frozen and sha(WORK/'bundle.dll')==FORMAL
    assessment=json.loads((WORK/'ab_assessment.json').read_bytes())
    assert all(row['pairs']==24 for row in assessment['metrics'].values())
    save('resume_validation_complete.json',dict(passed=True,all_remaining_prechecks_passed=True,first24_completed_once=True,
        dll_sha256=FORMAL,source_manifest_sha256=sha(WORK/'source_before_build.json'),ab_assessment_sha256=sha(WORK/'ab_assessment.json'),
        original_failure_retained=True,build_and_pgo_not_repeated=True))
    run('qualify_when_ready.py','qualification_resumed_first.log','--pid',original['pid'],'--created',original['created'],
        '--ready-receipt',WORK/'resume_validation_complete.json')
    save('resumed_protocol_complete.json',dict(passed=True,dll_sha256=FORMAL,original_first24_and_at_most_one_extra8=True))
    print('Remaining original protocol completed; installation remains gated by evidence review',flush=True)

if __name__=='__main__':main()
