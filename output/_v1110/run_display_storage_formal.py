"""Start one full fresh-PGO prefetch trial after its independent semantic proof."""
import ast
import json
from pathlib import Path
import subprocess
import sys
import psutil
from prepare_native_display_storage import STAGE,WORK as PROBE,BASE,ACCEPTED as BACKUP,EXPECTED,ARCHIVE,sha
WORK=STAGE/'native_perf50/display_storage_bundle'

def main():
    p=psutil.Process();p.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    assert json.loads((PROBE/'correctness.json').read_bytes())['passed']
    r=json.loads((BACKUP/'checkpoint_receipt.json').read_bytes())
    assert r['remote_upload_verified'] and r['remote_verified_commit']==ARCHIVE
    for path in WORK.glob('*.py'):ast.parse(path.read_text('utf8'),filename=path.name)
    paths=[WORK/'build_first.log',WORK/'qualification_first.log'];assert not any(x.exists() for x in paths)
    with paths[0].open('w',encoding='utf8') as bo,paths[1].open('w',encoding='utf8') as qo:
        build=subprocess.Popen([sys.executable,'-u','-X','utf8',str(WORK/'build_bundle.py')],stdout=bo,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW)
        created=psutil.Process(build.pid).create_time()
        qualify=subprocess.Popen([sys.executable,'-u','-X','utf8',str(WORK/'qualify_when_ready.py'),'--pid',str(build.pid),'--created',str(created)],stdout=qo,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW)
        r=dict(driver=dict(pid=p.pid,created=p.create_time()),build=dict(pid=build.pid,created=created),qualifier=dict(pid=qualify.pid,created=psutil.Process(qualify.pid).create_time()))
        (WORK/'live_formal_driver.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf8')
        for child in (build,qualify):
            while child.poll() is None:
                try:child.wait(timeout=30)
                except subprocess.TimeoutExpired:continue
            print(f'Protocol process {child.pid} exit {child.returncode}',flush=True)
        assert build.returncode==qualify.returncode==0,'Inspect original logs; do not restart an observed timing run'

if __name__=='__main__':main()
