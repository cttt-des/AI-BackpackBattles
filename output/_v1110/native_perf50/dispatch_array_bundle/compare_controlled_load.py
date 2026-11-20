"""A shared, bounded background load for directly comparable code measurements."""
import json
import os
from pathlib import Path
import subprocess
import sys
import time

WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
REPO=STAGE.parents[1]
sys.path.insert(0,str(STAGE))
from bench_native_load_calibration import WORKER

def main():
    children=[];start=time.perf_counter()
    worker=WORKER.replace('deadline = start + 120','deadline = start + 240')
    assert worker!=WORKER
    try:
        for _ in range(2):
            child=subprocess.Popen([sys.executable,'-u','-c',worker,str(os.getpid()),str(start)],
                stdout=subprocess.PIPE,text=True,creationflags=subprocess.CREATE_NO_WINDOW)
            children.append(child)
            assert child.stdout.readline().strip()=='ready'
        command=[sys.executable,'-u','-X','utf8',str(STAGE/'compare_native_isolated.py'),
            '--baseline',str(REPO/'dist/native_1_1_10/libgdcore.dll'),
            '--candidate',str(WORK/'bundle.dll'),'--reference',str(STAGE/'native_perf50_event_bus_serial.json'),
            '--out',str(WORK/'ab_shared_load.json'),'--pairs','16','--warmup-seconds','120','--quiet','--candidate-first']
        subprocess.run(command,check=True)
        assert time.perf_counter()-start<240,'Load expired before all paired measurements'
    finally:
        for child in children:
            if child.poll() is None:child.terminate()
            child.wait(timeout=10)
    report={'purpose':'Shared-load paired control, separate from the primary24pairs and raw24-batch gate',
        'workers':2,'priority':'below_normal','busy_fractions':[.2,.85],
        'phase_seconds':10,'maximum_duration_seconds':240,'elapsed_seconds':time.perf_counter()-start,
        'report':'ab_shared_load.json'}
    (WORK/'shared_load_protocol.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8',newline='\n')

if __name__=='__main__':main()
