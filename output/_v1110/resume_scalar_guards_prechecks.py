"""Resume only unexecuted work after the pre-timing source-pin repair."""
import json
import subprocess
import sys
import psutil
from prepare_native_scalar_guards import STAGE,sha
WORK=STAGE/'native_perf50/scalar_guards_bundle'

def main():
    p=psutil.Process();p.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    old=json.loads((WORK/'pre_timing_source_pin_repair/live_formal_driver.json').read_bytes())
    for row in old.values():
        try:
            other=psutil.Process(row['pid']);assert other.create_time()!=row['created'] or not other.is_running()
        except psutil.NoSuchProcess:pass
    logs=[WORK/'remaining_prechecks_first.log',WORK/'qualification_resumed_first.log'];assert not any(x.exists() for x in logs)
    state=dict(driver=dict(pid=p.pid,created=p.create_time()))
    with logs[0].open('w',encoding='utf8') as output:
        child=subprocess.Popen([sys.executable,'-u','-X','utf8',str(STAGE/'run_scalar_guards_remaining.py')],
            stdout=output,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW)
        state['build']=dict(pid=child.pid,created=psutil.Process(child.pid).create_time())
        (WORK/'live_formal_driver.json').write_text(json.dumps(state,indent=2)+'\n',encoding='utf8')
        child.wait();print('Remaining prechecks/first24 exit '+str(child.returncode),flush=True)
        assert child.returncode==0,'Inspect preserved log; never restart observed timing'
    ready=WORK/'precheck_resume_ready.json';assert json.loads(ready.read_bytes())['first24_completed_once']
    with logs[1].open('w',encoding='utf8') as output:
        qualify=subprocess.Popen([sys.executable,'-u','-X','utf8',str(WORK/'qualify_when_ready.py'),
            '--pid','0','--created','0','--ready-receipt',str(ready)],stdout=output,stderr=subprocess.STDOUT,
            creationflags=subprocess.CREATE_NO_WINDOW)
        state['qualifier']=dict(pid=qualify.pid,created=psutil.Process(qualify.pid).create_time())
        (WORK/'live_formal_driver.json').write_text(json.dumps(state,indent=2)+'\n',encoding='utf8')
        qualify.wait();print('Qualification exit '+str(qualify.returncode),flush=True)
        assert qualify.returncode==0,'Inspect original qualification log'

if __name__=='__main__':main()
