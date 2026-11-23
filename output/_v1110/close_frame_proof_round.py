"""Retain the fixed32 decision and report one non-release load calibration."""
import json
from pathlib import Path
import subprocess
import sys
from prepare_native_frame_proof import STAGE,EXPECTED,sha
WORK=STAGE/'native_perf50/frame_proof_bundle'

def main():
    decision=json.loads((WORK/'candidate_decision.json').read_bytes())
    assessment=json.loads((WORK/'ab_assessment_32.json').read_bytes())
    assert decision['no_more_same_source_groups'] and decision['status']=='inconclusive_retained'
    assert all(v['pairs']==32 for v in assessment['metrics'].values())
    dll=WORK/'bundle.dll';assert sha(dll)==decision['candidate_dll_sha256']
    calibration=WORK/'rejected_load_calibration.json';fit=WORK/'rejected_load20.json'
    assert not calibration.exists() and not fit.exists()
    subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'bench_native_load_calibration.py'),
        '--dll',str(dll),'--warmup-seconds','30','--out',str(calibration)],check=True)
    subprocess.run([sys.executable,'-X','utf8',str(STAGE/'fit_native_serial_load.py'),str(calibration),
        '--reference-load','20','--out',str(fit)],check=True)
    model=json.loads(fit.read_bytes())
    assert sha(STAGE/'sim_native/native_sim_cpp/native_sim/libgdcore.dll')==EXPECTED
    receipt=dict(candidate_dll_sha256=sha(dll),status='not_adopted_inconclusive',selected_pairs=32,
        main_thread_cpu_time_reduction_pct=assessment['metrics']['main_thread_cpu_s']['paired_median_time_reduction_pct'],
        wall_time_reduction_pct=assessment['metrics']['wall_s']['paired_median_time_reduction_pct'],
        candidate_fitted_at20_fps=model['fitted_fights_per_second_at_reference_load'],
        current_runtime_dll_sha256=EXPECTED,no_more_same_source_comparisons=True,
        strict2604_not_started=True,release_raw24_not_started=True,rejected_calibration_is_not_release_gate=True,
        reports_sha256={p.name:sha(p) for p in (WORK/'candidate_decision.json',WORK/'ab_assessment_32.json',calibration,fit,WORK/'frame_proof_tests.json')})
    out=WORK/'rejection_receipt.json';assert not out.exists()
    out.write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf8');print(json.dumps(receipt,indent=2))
if __name__=='__main__':main()
