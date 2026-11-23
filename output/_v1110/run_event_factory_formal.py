"""Run the fixed full20/new18PGO, regression and bounded AB protocol once."""
import json
from pathlib import Path
import subprocess
import sys
import psutil
from prepare_native_event_factory import STAGE, WORK as PROBE, sha

WORK=STAGE/'native_perf50/event_factory_bundle'

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    proof=json.loads((PROBE/'correctness.json').read_bytes())
    assert proof['passed'] and proof['cases']==5120 and proof['dll_sha256']==sha(PROBE/'prototype.dll')
    first=WORK/'transform_preflight_first.log'
    assert not first.exists()
    with first.open('w',encoding='utf8') as log:
        subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'preflight_native_event_factory_bundle.py')],
                       stdout=log,stderr=subprocess.STDOUT,check=True)
    print('Passed5120 cases and exact707-source reproduction; starting full20/new18PGO',flush=True)
    build_log=WORK/'build_first.log';qualify_log=WORK/'qualification_first.log'
    assert not build_log.exists() and not qualify_log.exists()
    with build_log.open('w',encoding='utf8') as bo,qualify_log.open('w',encoding='utf8') as qo:
        build=subprocess.Popen([sys.executable,'-u','-X','utf8',str(WORK/'build_bundle.py')],
                               stdout=bo,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW)
        created=psutil.Process(build.pid).create_time()
        qualify=subprocess.Popen([sys.executable,'-u','-X','utf8',str(WORK/'qualify_when_ready.py'),
                                  '--pid',str(build.pid),'--created',str(created)],
                                 stdout=qo,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW)
        for process in (build,qualify):
            while process.poll() is None:
                try:process.wait(timeout=30)
                except subprocess.TimeoutExpired:continue
            print('Protocol process '+str(process.pid)+' exit '+str(process.returncode),flush=True)
        assert build.returncode==qualify.returncode==0,'Inspect original logs; never restart observed comparisons'

if __name__=='__main__':main()
