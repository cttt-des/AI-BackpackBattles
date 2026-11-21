"""Resume the unchanged built DLL after correcting only the disassembly parser."""
import hashlib
import json
from pathlib import Path
import psutil
from validate_then_compare import run
from qualify_when_ready import run as qualify

WORK=Path(__file__).resolve().parent


def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
    dll=sha(WORK/'bundle.dll')
    assert dll=='f3f5d9476c66d9c84356e89bc8124c6f0b18096f0fb925a71b7173d2bdf315c9'
    source=WORK/'bundle_src'
    assert json.loads((WORK/'source_before_build.json').read_bytes())=={
        p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    for name in ('numeric_math_differential.json','numeric_barrier_build_proof.json'):
        result=json.loads((WORK/name).read_bytes())
        assert result['passed'] and result['dll_sha256']==dll
    receipt={'candidate_dll_sha256':dll,'compiled_source_unchanged':True,
        'cause':'Disassembly parser previously matched an address annotation instead of the exact function label. Only the test parser was corrected.',
        'failed_log_retained':'numeric_barrier_parser_failure.log',
        'numeric_actual_baseline_cases':5903,'floating_exception_flags_checked':True,
        'fresh_pgo_reused_without_engine_edits':True}
    (WORK/'validation_continuation.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf8')
    run('verify_resolved.py','verify.log')
    run('inspect_variant.py','release_audit.log','--dll',WORK/'bundle.dll','--out',WORK/'release_audit.json')
    run('test_regeneration_guards.py','regeneration_guards.log')
    run('test_full_regeneration.py','full_regeneration.log')
    assert json.loads((WORK/'buff_chunk_differential.json').read_bytes())['passed']
    run('run_comparison.py','comparison.log')
    assessment=json.loads((WORK/'ab_assessment.json').read_bytes())
    assert assessment['candidate_dll_sha256']==dll
    assert len(assessment['reports'])==3 and all(row['pairs']==24 for row in assessment['metrics'].values())
    if assessment['status']!='positive_combined_evidence':
        print('Retained all paired evidence; no qualification: '+assessment['status'],flush=True)
        return
    qualify('run_full_gate.py','full_gate.log','bundle')
    qualify('finish_gate.py','finish_gate.log')
    qualify('run_release_measurements.py','release_measurements.log')
    print('Qualification and one-shot release measurements complete; deployment awaits report review',flush=True)


if __name__=='__main__':main()
