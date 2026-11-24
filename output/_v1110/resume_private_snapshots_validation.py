"""Continue only unchecked preflight stages; preserve the original full build."""
import hashlib
import json
from pathlib import Path
import subprocess
import sys
import psutil
from prepare_native_private_snapshots import STAGE,EXPECTED,sha

WORK=STAGE/'native_perf50/private_snapshots_bundle'

def save(name,value):
    p=WORK/name;assert not p.exists();p.write_text(json.dumps(value,indent=2)+'\n',encoding='utf8')

def run(script,log,*args):
    path=WORK/log;assert not path.exists(),path
    print('Starting '+script,flush=True)
    with path.open('w',encoding='utf8') as output:
        subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/script),*map(str,args)],stdout=output,stderr=subprocess.STDOUT,check=True)
    print('Passed '+script,flush=True)

def main():
    process=psutil.Process();process.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    save('live_validation_resume.json',dict(pid=process.pid,created=process.create_time(),script=str(Path(__file__).resolve())))
    repair=json.loads((WORK/'validation_harness_repair_1.json').read_bytes())
    assert repair['no_formal_timing_started'] and repair['original_processes_terminal']
    assert repair['dll_sha256']==sha(WORK/'bundle.dll') and repair['source_manifest_sha256']==sha(WORK/'source_before_build.json')
    assert repair['fresh_profile_receipt_sha256']==sha(WORK/'fresh_profile_source.json')
    for n,h in repair['retained_passed_reports'].items():assert sha(WORK/n)==h
    source=json.loads((WORK/'source_before_build.json').read_bytes())
    assert source=={p.relative_to(WORK/'bundle_src').as_posix():sha(p) for p in (WORK/'bundle_src').rglob('*') if p.is_file()}
    assert source==json.loads((WORK.parent/'private_snapshots_prototype/transform.json').read_bytes())['source_sha256']
    assert sha(STAGE/'sim_native/native_sim_cpp/native_sim/libgdcore.dll')==EXPECTED
    assert not (WORK/'comparison.log').exists() and not list(WORK.glob('ab_*.json'))
    for script,log in [
        ('verify_targeted_timers.py','targeted_timer_tests.log'),
        ('verify_active_cooldowns.py','active_cooldown_tests.log'),
        ('verify_integer_grid.py','integer_grid_tests.log'),
        ('verify_event_factory.py','event_factory_tests.log'),
        ('verify_literal_spans.py','literal_span_tests.log'),
        ('verify_callback_dispatch.py','callback_dispatch_tests.log'),
        ('verify_object_routes.py','object_routes_tests.log'),
        ('verify_private_snapshots.py','private_snapshots_tests.log'),
        ('verify_resolved.py','verify.log')]:run(script,log)
    run('inspect_variant.py','release_audit.log','--dll',WORK/'bundle.dll','--out',WORK/'release_audit.json')
    run('test_regeneration_guards.py','regeneration_guards.log')
    run('test_full_regeneration.py','full_regeneration.log')
    assert json.loads((WORK/'buff_chunk_differential.json').read_bytes())['passed']
    # No edits, compilation, sampling or analysis after this point. The original
    # runner performs the first24 once, then the original qualifier may add8.
    run('run_comparison.py','comparison.log')
    ready=WORK/'validation_resumed_ready.json'
    save(ready.name,dict(passed=True,all_remaining_prechecks_passed=True,first24_completed_once=True,
        dll_sha256=sha(WORK/'bundle.dll'),source_manifest_sha256=sha(WORK/'source_before_build.json'),
        ab_assessment_sha256=sha(WORK/'ab_assessment.json')))
    run('qualify_when_ready.py','qualification_resumed_first.log','--pid','0','--created','0','--ready-receipt',ready)
    print('Remaining validation and original bounded qualification terminal; installation still gated',flush=True)

if __name__=='__main__':main()
