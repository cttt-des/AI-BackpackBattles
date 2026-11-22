"""Finish pending verification on the same frozen DLL, then perform first formal A/B."""
import hashlib
import json
from pathlib import Path
import subprocess
import sys
import psutil
WORK=Path(__file__).resolve().parent

def run(script,log,*args):
    path=WORK/log;assert not path.exists()
    print('Starting '+script,flush=True)
    with path.open('w',encoding='utf8') as out:subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/script),*map(str,args)],stdout=out,stderr=subprocess.STDOUT,check=True)
    print('Passed '+script,flush=True)

def main():
    p=psutil.Process();p.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    (WORK/'live_resumed_preflight.json').write_text(json.dumps(dict(pid=p.pid,created=p.create_time(),script=str(Path(__file__).resolve())),indent=2),encoding='utf8')
    assert not (WORK/'ab_1.json').exists() and not (WORK/'ab_assessment.json').exists()
    digest=hashlib.sha256((WORK/'bundle.dll').read_bytes()).hexdigest()
    assert digest==json.loads((WORK/'fresh_profile_source.json').read_bytes())['dll_sha256']
    assert json.loads((WORK/'targeted_timer_tests.json').read_bytes())['cases']==2016
    run('resume_resolved_after_layout.py','verify_after_layout.log')
    run('inspect_variant.py','release_audit.log','--dll',WORK/'bundle.dll','--out',WORK/'release_audit.json')
    run('test_regeneration_guards.py','regeneration_guards.log')
    run('test_full_regeneration.py','full_regeneration.log')
    assert digest==hashlib.sha256((WORK/'bundle.dll').read_bytes()).hexdigest()
    run('run_comparison.py','comparison.log')
    print('All pending checks and first three formal A/B groups complete; qualification still required',flush=True)

if __name__=='__main__':main()
