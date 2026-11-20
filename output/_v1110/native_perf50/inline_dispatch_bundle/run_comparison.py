"""Execute the predeclared three independent isolated AB/BA groups."""
import json
from pathlib import Path
import subprocess
import sys
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
REPO=STAGE.parents[1]
for group in (1,2,3):
    command=[sys.executable,'-u','-X','utf8',str(STAGE/'compare_native_isolated.py'),'--baseline',str(REPO/'dist/native_1_1_10/libgdcore.dll'),'--candidate',str(WORK/'bundle.dll'),'--reference',str(STAGE/'native_perf50_event_bus_serial.json'),'--out',str(WORK/f'ab_{group}.json'),'--pairs','8','--warmup-seconds','120','--quiet']
    if group in (1,3):command.append('--candidate-first')
    if group==2:command.append('--candidate-load-first')
    print(f'Starting independent group {group}/3',flush=True)
    subprocess.run(command,check=True)
subprocess.run([sys.executable,'-X','utf8',str(WORK/'assess_resolved.py'),'--reports',*[str(WORK/f'ab_{i}.json') for i in (1,2,3)],'--out',str(WORK/'ab_assessment.json')],check=True)
