"""Wait before the first independent calibration; never resample an observed run."""
import json
from pathlib import Path
import time
import psutil
WORK=Path(__file__).resolve().parent
assert not (WORK/'bundle_load_calibration.json').exists()
assert not (WORK/'rejected_load_calibration.json').exists()
assert not (WORK/'calibration_eligibility.json').exists()
started=time.monotonic();consecutive=[];samples=0;last_log=started-30
print('Waiting for3 consecutive idle CPU observations<=12%, before the sole calibration',flush=True)
while len(consecutive)<3:
    load=psutil.cpu_percent(interval=1);samples+=1
    consecutive=consecutive+[load] if load<=12 else []
    now=time.monotonic()
    if now-last_log>=30:
        record=dict(status='waiting_before_first_calibration',latest_idle_cpu_pct=load,consecutive=len(consecutive),
            elapsed_seconds=now-started,observations=samples,no_candidate_benchmarks_used=True)
        (WORK/'calibration_wait_status.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf8')
        print(f'Idle CPU={load:.1f}%; eligible observations={len(consecutive)}/3',flush=True);last_log=now
(WORK/'calibration_eligibility.json').write_text(json.dumps(dict(passed=True,maximum_idle_cpu_pct=12,
    qualifying_observations=consecutive,observations=samples,elapsed_seconds=time.monotonic()-started,
    no_candidate_benchmarks_used=True,calibration_not_yet_started=True),indent=2)+'\n',encoding='utf8')
print('Eligible; start the original warm30/calibration24 once',flush=True)
