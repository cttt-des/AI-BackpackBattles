"""Continue this identified build through qualification, without deploying."""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess
import sys
import psutil

WORK=Path(__file__).resolve().parent


def run(script,log,*args):
    print('Starting '+script,flush=True)
    path=WORK/log
    assert not path.exists(),path
    with path.open('w',encoding='utf8') as output:
        subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/script),*args],stdout=output,stderr=subprocess.STDOUT,check=True)
    print('Passed '+script,flush=True)


def main():
    parser=argparse.ArgumentParser();parser.add_argument('--pid',type=int,required=True)
    parser.add_argument('--created',type=float,required=True);args=parser.parse_args()
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    try:process=psutil.Process(args.pid)
    except psutil.NoSuchProcess:process=None
    if process is not None:
        assert abs(process.create_time()-args.created)<0.001
        assert any('typed_read_bundle/build_bundle.py' in part.replace('\\','/') for part in process.cmdline())
        print('Awaiting identified live build '+str(process.pid),flush=True)
        while process.is_running():
            try:process.wait(timeout=30)
            except psutil.TimeoutExpired:continue
            break
    assessment=WORK/'ab_assessment.json'
    assert assessment.exists(),'Build/validation/comparison incomplete: inspect original logs; do not restart'
    result=json.loads(assessment.read_bytes())
    actual=hashlib.sha256((WORK/'bundle.dll').read_bytes()).hexdigest()
    assert result['candidate_dll_sha256']==actual
    assert len(result['reports'])==3 and all(row['pairs']==24 for row in result['metrics'].values())
    if result['status']!='positive_combined_evidence':
        print('Retained entire comparison; no qualification/deployment: '+result['status'],flush=True)
        return
    run('run_full_gate.py','full_gate.log','bundle')
    run('finish_gate.py','finish_gate.log')
    run('run_release_measurements.py','release_measurements.log')
    print('Qualification and one-shot release measurements finished; deployment requires report review',flush=True)


if __name__=='__main__':main()
