"""Start the original full20/new18PGO and bounded AB protocol once."""
import json
from pathlib import Path
import subprocess
import sys
import psutil
from prepare_native_private_snapshots import STAGE,WORK as PROBE,sha

WORK=STAGE/'native_perf50/private_snapshots_bundle'

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    proof=json.loads((PROBE/'correctness.json').read_bytes())
    assert proof['passed'] and proof['cases']==234880 and proof['dll_sha256']==sha(PROBE/'prototype.dll')
    first=WORK/'transform_preflight_first.log';assert not first.exists()
    preflight=WORK/'transform_preflight.json'
    if preflight.exists():
        retained=json.loads(preflight.read_bytes())
        assert retained['full_source_matches_tested_prototype'] and retained['no_speed_claim']
        assert retained['source_sha256']==json.loads((PROBE/'transform.json').read_bytes())['source_sha256']
        first.write_text('Retained completed preflight; SHA256 '+sha(preflight)+'\n',encoding='utf8')
    else:
        with first.open('w',encoding='utf8') as log:
            subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'preflight_native_private_snapshots.py')],stdout=log,stderr=subprocess.STDOUT,check=True)
    print('Passed234880 affected-path cases and708-source reproduction; all retained checks required before AB; full20/new18PGO',flush=True)
    build_log=WORK/'build_first.log';qualify_log=WORK/'qualification_first.log'
    assert not build_log.exists() and not qualify_log.exists()
    with build_log.open('w',encoding='utf8') as bo,qualify_log.open('w',encoding='utf8') as qo:
        build=subprocess.Popen([sys.executable,'-u','-X','utf8',str(WORK/'build_bundle.py')],stdout=bo,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW)
        created=psutil.Process(build.pid).create_time()
        qualifier=subprocess.Popen([sys.executable,'-u','-X','utf8',str(WORK/'qualify_when_ready.py'),'--pid',str(build.pid),'--created',str(created)],stdout=qo,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW)
        for process in (build,qualifier):
            while process.poll() is None:
                try:process.wait(timeout=30)
                except subprocess.TimeoutExpired:continue
            print('Protocol process '+str(process.pid)+' exit '+str(process.returncode),flush=True)
        assert build.returncode==qualifier.returncode==0,'Inspect original logs; never restart observed timings'

if __name__=='__main__':main()
