"""One calibrated report per candidate, without an observed20% range gate."""
import json,statistics,subprocess,sys
from prepare_frame_guard_reuse import STAGE,WORK,sha,save
def main():
    decision=json.loads((WORK/'candidate_decision.json').read_bytes());positive=decision['accepted'];dll=WORK/'bundle.dll'
    assert json.loads((WORK/'complete_correctness_gate.json').read_bytes())['passed']
    serial=WORK/'bundle_serial.json';cal=WORK/'bundle_load_calibration.json';fit=WORK/'bundle_load20.json';assert not any(p.exists() for p in (serial,cal,fit))
    if positive:
        assert json.loads((WORK/'post_ab_directed_checks.json').read_bytes())['passed'];print('Starting the only release raw24',flush=True)
        subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'bench_native_corpus.py'),'--dll',str(dll),'--workers','1','--repeat','24','--out',str(serial)],check=True)
    print('Starting the only independent calibration24'+(' (nonrelease)' if not positive else ''),flush=True)
    subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'bench_native_load_calibration.py'),'--dll',str(dll),'--warmup-seconds','30','--out',str(cal)],check=True)
    subprocess.run([sys.executable,'-X','utf8',str(STAGE/'fit_native_serial_load.py'),str(cal),'--reference-load','20','--allow-extrapolation','--out',str(fit)],check=True)
    def summary(path):
        r=json.loads(path.read_bytes());assert r['dll_sha256']==sha(dll) and r['inputs_sha256']=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef' and r['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9';assert len(r['samples'])==r['repeat']==24 and r['workers']==1
        values=[x['fights_per_second'] for x in r['samples']];return dict(median_fights_per_second=statistics.median(values),minimum_fights_per_second=min(values),maximum_fights_per_second=max(values),load_range=[min(x['background_load_pct'] for x in r['samples']),max(x['background_load_pct'] for x in r['samples'])])
    estimated=json.loads(fit.read_bytes());raw=summary(serial) if positive else None
    save('measurements_summary.json',dict(dll_sha256=sha(dll),serial=raw,load_calibration=summary(cal),fitted_fights_per_second_at20=estimated['fitted_fights_per_second_at_reference_load'],reference_is_extrapolation=estimated['reference_is_extrapolation'],r_squared_log_wall_time=estimated['r_squared_log_wall_time'],validation=estimated['validation'],raw24_gate_passed=raw['minimum_fights_per_second']>=50 if raw else None,nonrelease_only=not positive,all_samples_retained=True,report_sha256={p.name:sha(p) for p in (serial,cal,fit) if p.exists()}))
    print('Single raw/calibration protocol complete',flush=True)
if __name__=='__main__':main()
