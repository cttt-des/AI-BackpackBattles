"""Continue unexecuted checks on the same frozenDLL; first AB only."""
import json
import sys
import psutil
from prepare_native_scalar_guards import STAGE,BASE,EXPECTED,sha,inventory,verify_projection
WORK=STAGE/'native_perf50/scalar_guards_bundle'
sys.path.insert(0,str(WORK))
from validate_then_compare import run

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    repair=json.loads((WORK/'pre_timing_source_pin_repair/repair.json').read_bytes())
    assert sha(WORK/'bundle.dll')==repair['before_dll_sha256']=='63d8966c95c629855fc336a748cbfcc20860d5e75d7c1700506022f347ac10c5'
    assert sha(WORK/'source_before_build.json')==repair['source_manifest_sha256']
    assert sha(BASE/'libgdcore.dll')==EXPECTED and verify_projection(WORK/'bundle_src')['exact_inverse_matches_retained_source']
    for name in ('compiled_option_receipt.json','event_identity_tests.json','lazy_diagnostics_tests.json','member_frame_tests.json',
            'static_collections_tests.json','static_setup_tests.json','dispatch_chain_tests.json','spatial_tests.json'):
        assert json.loads((WORK/name).read_bytes())['passed'],name
    assert not any((WORK/name).exists() for name in ('comparison.log','ab_1.json','ab_assessment.json','candidate_decision.json'))
    checks=[('verify_motion_indices.py','motion_indices_tests_resumed.log'),('verify_targeted_timers.py','targeted_timer_tests.log'),
        ('verify_active_cooldowns.py','active_cooldown_tests.log'),('verify_scalar_truth.py','scalar_truth_tests.log'),
        ('verify_private_snapshots.py','private_snapshots_tests.log'),('verify_control_word.py','control_word_tests.log'),
        ('verify_display_storage.py','display_storage_tests.log'),('verify_integer_grid.py','integer_grid_tests.log'),
        ('verify_event_factory.py','event_factory_tests.log'),('verify_literal_spans.py','literal_span_tests.log'),
        ('verify_callback_dispatch.py','callback_dispatch_tests.log'),('verify_object_routes.py','object_routes_tests.log'),
        ('verify_resolved.py','verify.log')]
    for script,log in checks:
        assert not (WORK/log).exists(),log
        run(script,log)
    run('inspect_variant.py','release_audit.log','--dll',WORK/'bundle.dll','--out',WORK/'release_audit.json')
    run('test_regeneration_guards.py','regeneration_guards.log');run('test_full_regeneration.py','full_regeneration.log')
    assert json.loads((WORK/'buff_chunk_differential.json').read_bytes())['passed']
    run('run_comparison.py','comparison.log')
    assert inventory(WORK/'bundle_src')==json.loads((WORK/'source_before_build.json').read_bytes())
    ready=dict(passed=True,all_remaining_prechecks_passed=True,first24_completed_once=True,
        dll_sha256=sha(WORK/'bundle.dll'),source_manifest_sha256=sha(WORK/'source_before_build.json'),
        ab_assessment_sha256=sha(WORK/'ab_assessment.json'),same_release_no_rebuild=True,all_first_precheck_logs_retained=True)
    out=WORK/'precheck_resume_ready.json';assert not out.exists();out.write_text(json.dumps(ready,indent=2)+'\n',encoding='utf8')
    print(json.dumps(ready),flush=True)

if __name__=='__main__':main()
