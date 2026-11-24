"""One predeclared raw24 and load-calibration24 run after the complete truth gate."""
import hashlib
import json
from pathlib import Path
import statistics
import subprocess
import sys
import psutil

WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()

def main():
    psutil.Process().nice(psutil.NORMAL_PRIORITY_CLASS)
    gate=json.loads((WORK/'bundle_full_gate.json').read_bytes())
    audit=json.loads((WORK/'full_type_audit.json').read_bytes())
    hashes=json.loads((WORK/'bundle_vs_deployed_hashes.json').read_bytes())
    dll=WORK/'bundle.dll';digest=sha(dll)
    assert gate['complete'] and gate['dll_sha256']==digest
    assert audit['fights']==hashes['unchanged_cpp_event_streams']==2604
    assert audit['coverage']['audit_mismatch']==audit['old_event_kernel_type_mismatches']==0
    outputs=[WORK/name for name in ('bundle_serial.json','bundle_load_calibration.json','bundle_load20.json')]
    assert not any(p.exists() for p in outputs),'Do not overwrite or rerun observed measurements'
    python=[sys.executable,'-u','-X','utf8']
    print('Starting one raw24 run',flush=True)
    subprocess.run([*python,str(STAGE/'bench_native_corpus.py'),'--dll',str(dll),
        '--workers','1','--repeat','24','--out',str(outputs[0])],check=True)
    subprocess.run([*python,str(WORK/'wait_calibration_window.py')],check=True)
    print('Starting one controlled load-calibration24 run',flush=True)
    subprocess.run([*python,str(STAGE/'bench_native_load_calibration.py'),'--dll',str(dll),
        '--warmup-seconds','30','--out',str(outputs[1])],check=True)
    subprocess.run([*python,str(STAGE/'fit_native_serial_load.py'),str(outputs[1]),
        '--reference-load','20','--out',str(outputs[2])],check=True)
    serial,calibration,fit=[json.loads(p.read_bytes()) for p in outputs]
    for report in (serial,calibration):
        assert report['dll_sha256']==digest and report['workers']==1 and report['fights']==200
        assert len(report['samples'])==report['repeat']==24
        assert report['inputs_sha256']=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
        assert report['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    def summarize(report):
        rows=report['samples'];speed=[r['fights_per_second'] for r in rows]
        return {'median_fights_per_second':statistics.median(speed),'minimum_fights_per_second':min(speed),'maximum_fights_per_second':max(speed),
            'background_load_range_pct':[min(r['background_load_pct'] for r in rows),max(r['background_load_pct'] for r in rows)],
            'on_ac_all':all(r['on_ac_before'] is True and r['on_ac_after'] is True for r in rows)}
    result={'dll_sha256':digest,'serial':summarize(serial),'load_calibration':summarize(calibration),
        'fitted_fights_per_second_at20':fit['fitted_fights_per_second_at_reference_load'],
        'r_squared_log_wall_time':fit['r_squared_log_wall_time'],'fit_validation':fit['validation'],
        'report_sha256':{p.name:sha(p) for p in outputs},'single_run_all_samples_retained':True}
    result['raw24_gate_passed']=result['serial']['minimum_fights_per_second']>=50
    (WORK/'measurements_summary.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
    print(json.dumps(result,indent=2),flush=True)

if __name__=='__main__':main()
