import json
from pathlib import Path
import subprocess
import sys
import psutil
WORK=Path(__file__).resolve().parent
def run(script,log,*args):
    path=WORK/log;assert not path.exists(),path
    print('Starting '+script,flush=True)
    with path.open('w',encoding='utf8') as output:subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/script),*map(str,args)],stdout=output,stderr=subprocess.STDOUT,check=True)
    print('Passed '+script,flush=True)
def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    dll=WORK/'bundle.dll'
    run('verify_motion_indices.py','motion_indices_tests_after_source_pin_repair.log')
    run('verify_targeted_timers.py','targeted_timer_tests.log')
    run('verify_active_cooldowns.py','active_cooldown_tests.log')
    run('verify_identity_lookup.py','identity_lookup_tests.log')
    run('verify_container_builtins.py','container_builtins_tests.log')
    run('verify_scalar_truth.py','scalar_truth_tests.log')
    run('verify_private_snapshots.py','private_snapshots_tests.log')
    run('verify_control_word.py','control_word_tests.log')
    run('verify_display_storage.py','display_storage_tests.log')
    run('verify_integer_grid.py','integer_grid_tests.log')
    run('verify_event_factory.py','event_factory_tests.log')
    run('verify_literal_spans.py','literal_span_tests.log')
    run('verify_callback_dispatch.py','callback_dispatch_tests.log')
    run('verify_object_routes.py','object_routes_tests.log')
    run('verify_resolved.py','verify.log')
    run('inspect_variant.py','release_audit.log','--dll',dll,'--out',WORK/'release_audit.json')
    run('test_regeneration_guards.py','regeneration_guards.log')
    run('test_full_regeneration.py','full_regeneration.log')
    # Only this process and the two serial A/B workers remain; no more preparation.
    assert json.loads((WORK/'buff_chunk_differential.json').read_bytes())['passed']
    run('run_comparison.py','comparison.log')
    print('All preflight checks and three comparison groups completed; deployment still gated',flush=True)

if __name__=='__main__':main()
