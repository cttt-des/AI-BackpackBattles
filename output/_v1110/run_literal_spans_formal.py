"""Start one frozen full build and bounded AB/qualification protocol."""
import json
from pathlib import Path
import subprocess
import sys
import psutil
from prepare_native_literal_spans import STAGE,WORK as PROBE,sha

WORK=STAGE/'native_perf50/literal_spans_bundle'

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    proof=json.loads((PROBE/'correctness.json').read_bytes())
    assert proof['passed'] and proof['cases']==5184 and proof['dll_sha256']==sha(PROBE/'prototype.dll')
    first=WORK/'transform_preflight_first.log';assert not first.exists()
    preflight=WORK/'transform_preflight.json'
    if preflight.exists():
        retained=json.loads(preflight.read_bytes())
        assert retained['full_source_matches_tested_prototype'] and retained['no_speed_claim']
        assert retained['source_sha256']==json.loads((PROBE/'transform.json').read_bytes())['source_sha256']
        first.write_text('Retained the first completed707-source preflight; SHA256 '+sha(preflight)+'\n',encoding='utf8')
    else:
        with first.open('w',encoding='utf8') as log:
            subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'preflight_native_literal_spans.py')],stdout=log,stderr=subprocess.STDOUT,check=True)
    print('Passed5184 cases; exact707-source reproduction; starting full20/new18PGO',flush=True)
    build_log=WORK/'build_first.log';qualify_log=WORK/'qualification_first.log'
    assert not build_log.exists() and not qualify_log.exists()
    with build_log.open('w',encoding='utf8') as bo,qualify_log.open('w',encoding='utf8') as qo:
        build=subprocess.Popen([sys.executable,'-u','-X','utf8',str(WORK/'build_bundle.py')],stdout=bo,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW)
        created=psutil.Process(build.pid).create_time()
        qualify=subprocess.Popen([sys.executable,'-u','-X','utf8',str(WORK/'qualify_when_ready.py'),'--pid',str(build.pid),'--created',str(created)],stdout=qo,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW)
        for process in (build,qualify):
            while process.poll() is None:
                try:process.wait(timeout=30)
                except subprocess.TimeoutExpired:continue
            print('Protocol process '+str(process.pid)+' exit '+str(process.returncode),flush=True)
        assert build.returncode==qualify.returncode==0,'Inspect original logs; never restart observed timings'

if __name__=='__main__':main()
