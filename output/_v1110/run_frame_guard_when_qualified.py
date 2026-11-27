"""Finish automatically after the identified qualifier succeeds, never on failure."""
import json,subprocess,sys,time
import psutil
from prepare_frame_guard_reuse import STAGE,WORK,save
def main():
    candidates=[]
    for process in psutil.process_iter(['name','cmdline']):
        args=process.info['cmdline'] or []
        if not process.info['name'].lower().startswith('python') or not any(x.endswith('verify_frame_guard_release.py') for x in args):continue
        children=process.children()
        if not any(c.name().lower().startswith('python') and any(x.endswith('verify_frame_guard_release.py') for x in c.cmdline()) for c in children):candidates.append(process)
    if (WORK/'complete_correctness_gate.json').exists():candidates=[]
    else:assert len(candidates)==1,[(p.pid,p.cmdline()) for p in candidates]
    if candidates:
        process=candidates[0];save('live_goal_driver.json',dict(qualifier_pid=process.pid,qualifier_created=process.create_time(),driver_pid=psutil.Process().pid,driver_created=psutil.Process().create_time()))
        print('Waiting for identified correctness qualifier',flush=True)
        while process.is_running():
            try:process.wait(timeout=30)
            except psutil.TimeoutExpired:continue
            break
    proof=WORK/'complete_correctness_gate.json';assert proof.exists() and json.loads(proof.read_bytes())['passed'],'Qualifier did not succeed; retain all logs and resolve its actual failure before timing'
    subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'finalize_frame_guard.py')],check=True)
if __name__=='__main__':main()
