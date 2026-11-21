"""Complete strict truth, raw throughput, load report and guarded installation."""
import hashlib
import json
from pathlib import Path
import subprocess
import sys

WORK=Path(__file__).resolve().parent

def run(script,log,*arguments):
    print('Starting '+script,flush=True)
    assert not (WORK/log).exists(),'Retain every observed qualification run'
    with (WORK/log).open('w',encoding='utf8') as output:
        subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/script),*map(str,arguments)],
                       stdout=output,stderr=subprocess.STDOUT,check=True)
    print('Passed '+script,flush=True)

def main():
    assessment=json.loads((WORK/'ab_assessment.json').read_bytes())
    assert assessment['status']=='positive_combined_evidence'
    dll=hashlib.sha256((WORK/'bundle.dll').read_bytes()).hexdigest()
    assert assessment['candidate_dll_sha256']==dll
    assert all(assessment['metrics'][m]['pairs']==24 for m in ('main_thread_cpu_s','wall_s'))
    run('measure_all_layouts.py','all_layouts.log')
    run('run_full_gate.py','full_gate.log','bundle')
    run('finish_gate.py','finish_gate.log')
    run('run_release_measurements.py','release_measurements.log')
    summary=json.loads((WORK/'measurements_summary.json').read_bytes())
    assert summary['dll_sha256']==dll and summary['raw24_gate_passed']
    run('install_verified.py','installation.log','bundle','--speed-report',WORK/'bundle_serial.json')
    print('All deployment gates and normal training smoke passed',flush=True)

if __name__=='__main__':main()
