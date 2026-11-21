"""Run exactly the one predeclared independent clarification group."""
import hashlib
import json
from pathlib import Path
import subprocess
import sys
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
REPO=STAGE.parents[1]
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def main():
    plan=json.loads((WORK/'followup_plan.json').read_bytes())
    assert plan['additional_groups']==1 and plan['additional_pairs']==8 and plan['all_original_samples_retained']
    assert sha(WORK/'bundle.dll')==plan['candidate_dll_sha256']
    assert sha(REPO/'dist/native_1_1_10/libgdcore.dll')==plan['baseline_dll_sha256']
    assert not (WORK/'ab_4.json').exists() and not (WORK/'ab_assessment_32.json').exists()
    for i in (1,2,3):assert (WORK/f'ab_{i}.json').is_file()
    subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'compare_native_isolated_blocks.py'),
        '--baseline',str(REPO/'dist/native_1_1_10/libgdcore.dll'),'--candidate',str(WORK/'bundle.dll'),
        '--reference',str(STAGE/'native_perf50_event_bus_serial.json'),'--out',str(WORK/'ab_4.json'),
        '--pairs','8','--batch-repetitions','4','--warmup-seconds','120','--quiet'],check=True)
    subprocess.run([sys.executable,'-X','utf8',str(WORK/'assess_resolved.py'),
        '--reports',*[str(WORK/f'ab_{i}.json') for i in (1,2,3,4)],'--out',str(WORK/'ab_assessment_32.json')],check=True)
if __name__=='__main__':main()
