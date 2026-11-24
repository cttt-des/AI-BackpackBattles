"""Start the distinct compiler configuration once, preserving all original gates."""
import ast
import json
from pathlib import Path
import subprocess
import sys
import psutil
from prepare_native_compiler_pta import STAGE,WORK,BASE,ACCEPTED,BACKUP,EXPECTED,ARCHIVE,sha

def main():
    process=psutil.Process();process.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    configuration=json.loads((WORK/'compiler_configuration.json').read_bytes())
    assert configuration['candidate_flags']==['-fipa-pta'] and configuration['source_changes']==[]
    assert configuration['private_snapshots_not_included'] and configuration['no_floating_option_change']
    backup=json.loads((BACKUP/'checkpoint_receipt.json').read_bytes())
    assert backup['remote_upload_verified'] and backup['remote_verified_commit']==ARCHIVE
    for script in WORK.glob('*.py'):ast.parse(script.read_text('utf8'),filename=script.name)
    # The wrapper retains the correct F950 source proof; there is no new C++
    # transform. Actual compiler-produced code still runs every old regression.
    assert "object_routes_prototype/transform.json" in (WORK/'verify_targeted_timers.py').read_text('utf8')
    assert json.loads((STAGE/'native_perf50/object_routes_prototype/transform.json').read_bytes())['source_sha256']==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    build_log=WORK/'build_first.log';qualification_log=WORK/'qualification_first.log'
    assert not build_log.exists() and not qualification_log.exists()
    with build_log.open('w',encoding='utf8') as bo,qualification_log.open('w',encoding='utf8') as qo:
        build=subprocess.Popen([sys.executable,'-u','-X','utf8',str(WORK/'build_bundle.py')],stdout=bo,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW)
        created=psutil.Process(build.pid).create_time()
        qualify=subprocess.Popen([sys.executable,'-u','-X','utf8',str(WORK/'qualify_when_ready.py'),'--pid',str(build.pid),'--created',str(created)],stdout=qo,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW)
        receipt=dict(driver=dict(pid=process.pid,created=process.create_time()),build=dict(pid=build.pid,created=created),
            qualifier=dict(pid=qualify.pid,created=psutil.Process(qualify.pid).create_time()),
            compiler_configuration_sha256=sha(WORK/'compiler_configuration.json'),compiler_flags=['-fipa-pta'],source_unchanged=True)
        (WORK/'live_formal_driver.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf8')
        for child in (build,qualify):
            while child.poll() is None:
                try:child.wait(timeout=30)
                except subprocess.TimeoutExpired:continue
            print('Protocol process '+str(child.pid)+' exit '+str(child.returncode),flush=True)
        assert build.returncode==qualify.returncode==0,'Inspect actual terminal state and original logs; never restart observed timing'

if __name__=='__main__':main()
