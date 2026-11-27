"""Continue the re-ranked second direction after the first driver closes safely."""
import json,subprocess,sys
import psutil
from prepare_frame_guard_reuse import STAGE

def main():
    matches=[]
    for process in psutil.process_iter(['name','cmdline']):
        args=process.info['cmdline'] or []
        if not process.info['name'].lower().startswith('python') or args[-2:]!=['dictionary_scalar_bundle','drive_all']:continue
        if any((child.cmdline() or [])[-2:]==['dictionary_scalar_bundle','drive_all'] for child in process.children()):continue
        matches.append(process)
    assert len(matches)==1,[(p.pid,p.cmdline()) for p in matches]
    process=matches[0];print('Waiting for first identified coordinator; no extra candidate or timing runs',flush=True)
    while process.is_running():
        try:process.wait(timeout=30)
        except psutil.TimeoutExpired:continue
        break
    checkpoint=STAGE/'native_perf50/dictionary_scalar_bundle/checkpoint_receipt.json'
    assert checkpoint.exists() and json.loads(checkpoint.read_bytes())['remote_upload_verified'],'First experiment did not close; investigate its preserved failure before continuing'
    print('First round remotely verified; restarting coordinator with re-ranked RNG second direction',flush=True)
    subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'next_two.py'),'rng_scaling_bundle','drive_all'],check=True)
if __name__=='__main__':main()
