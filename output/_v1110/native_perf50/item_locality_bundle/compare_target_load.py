"""One fixed near20-load paired comparison, separate from independent fitted estimates."""
import hashlib
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
    out=WORK/'ab_target_load.json'
    assert not out.exists(),'Keep the one predeclared run, including unfavorable observations'
    baseline=REPO/'dist/native_1_1_10_before_item_locality_bundle_20261121/libgdcore.dll';candidate=WORK/'bundle.dll'
    assert hashlib.sha256(baseline.read_bytes()).hexdigest()=='444e75c6872fa2acec57f42d88eb6687c29f2dc97a82b88ba3e66fdf849312cc'
    assert hashlib.sha256(candidate.read_bytes()).hexdigest()=='8e7d574055c36e7535cb54139e11514729e72088c4314ad028c623d42ae32cfa'
    protocol={'purpose':'Check package performance near20 background load after independent wide-load fits differed; not a replacement fit or a rerun of release24.',
        'pairs':16,'warmup_seconds':120,'fixed200_single_thread':True,'priority':'normal','logical_cpus':'all8',
        'background_workers':2,'background_priority':'below_normal','busy_fraction_each':0.72,
        'background_period_seconds':0.02,'maximum_duration_seconds':300,
        'nominal_added_load_pct_of8_logical_cpus':18.0,
        'actual_load':'Measure and retain each arm; natural load is additional. No filtering or selection based on the observed load or result.',
        'decision':'Assess CPU and wall medians, sums and all16 pairs; retain unfavorable evidence. Confirm or investigate loaded behavior before choosing the next optimization baseline; this does not replace the recorded independent fit.',
        'original_wide_fit_at20':133.9979024452513,'original_wide_fit_kept':True}
    (WORK/'target_load_protocol.json').write_text(json.dumps(protocol,indent=2)+'\n',encoding='utf8')
    worker=WORKER.replace('deadline = start + 120','deadline = start + 300')
    line='duty = 0.20 if int((now - start) / 10) % 2 == 0 else 0.85'
    assert worker.count(line)==1
    worker=worker.replace(line,'duty = 0.72')
    assert worker.count('deadline = start + 300')==1
    children=[];start=time.perf_counter()
    try:
        for _ in range(2):
            child=subprocess.Popen([sys.executable,'-u','-c',worker,str(os.getpid()),str(start)],
                stdout=subprocess.PIPE,text=True,creationflags=subprocess.CREATE_NO_WINDOW)
            children.append(child)
            assert child.stdout.readline().strip()=='ready'
        subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'compare_native_isolated.py'),
            '--baseline',str(baseline),'--candidate',str(candidate),
            '--reference',str(STAGE/'native_perf50_event_bus_serial.json'),'--out',str(out),
            '--pairs','16','--warmup-seconds','120','--quiet','--candidate-first'],check=True)
        assert all(child.poll() is None for child in children),'Controlled workers ended early'
        assert time.perf_counter()-start<300,'Controlled load expired before completion'
    finally:
        for child in children:
            if child.poll() is None:child.terminate()
            child.wait(timeout=10)
    subprocess.run([sys.executable,'-X','utf8',str(WORK/'assess_resolved.py'),
        '--reports',str(out),'--out',str(WORK/'target_load_assessment.json')],check=True)
    print('Completed single near20 paired run; original fitted134.00 estimate remains recorded',flush=True)

if __name__=='__main__':main()
