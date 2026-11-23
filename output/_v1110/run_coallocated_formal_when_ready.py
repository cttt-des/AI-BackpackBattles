"""Start the frozen formal protocol only after the identified actual-DLL checks."""
import json
from pathlib import Path
import subprocess
import sys
import psutil
from prepare_native_coallocated_events import STAGE,WORK as PROBE,sha
WORK=STAGE/'native_perf50/coallocated_events_bundle'

def await_process(process):
    while process.is_running():
        try:process.wait(timeout=30)
        except psutil.TimeoutExpired:continue
        break

def main():
    own=psutil.Process();own.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS);matches=[]
    for p in psutil.process_iter(['pid','cmdline']):
        try:
            if p.pid!=own.pid and p.exe()==own.exe() and any(Path(x).name=='verify_native_coallocated_events.py' for x in p.info['cmdline'] or []):matches.append(p)
        except (psutil.NoSuchProcess,psutil.AccessDenied):continue
    assert len(matches)<=1
    if matches:
        print('Awaiting identified actual-DLL verifier PID '+str(matches[0].pid),flush=True)
        await_process(matches[0])
    proof=json.loads((PROBE/'correctness.json').read_bytes())
    assert proof['passed'] and proof['cases']==4161 and proof['dll_sha256']==sha(PROBE/'prototype.dll')
    first=WORK/'transform_preflight_first.log';assert not first.exists()
    with first.open('w',encoding='utf8') as output:
        subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'preflight_native_coallocated_events_bundle.py')],stdout=output,stderr=subprocess.STDOUT,check=True)
    print('Passed4161 cases and exact707-source reproduction; starting formal build',flush=True)
    build_log=WORK/'build_first.log';qualify_log=WORK/'qualification_first.log'
    assert not build_log.exists() and not qualify_log.exists()
    with build_log.open('w',encoding='utf8') as build_output,qualify_log.open('w',encoding='utf8') as qualify_output:
        build=subprocess.Popen([sys.executable,'-u','-X','utf8',str(WORK/'build_bundle.py')],stdout=build_output,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW)
        created=psutil.Process(build.pid).create_time()
        qualifier=subprocess.Popen([sys.executable,'-u','-X','utf8',str(WORK/'qualify_when_ready.py'),'--pid',str(build.pid),'--created',str(created)],stdout=qualify_output,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW)
        for child in (build,qualifier):
            while child.poll() is None:
                try:child.wait(timeout=30)
                except subprocess.TimeoutExpired:continue
            print('Protocol process '+str(child.pid)+' exit '+str(child.returncode),flush=True)
        assert build.returncode==qualifier.returncode==0,'Inspect retained original logs; do not restart observed comparisons'

if __name__=='__main__':main()
