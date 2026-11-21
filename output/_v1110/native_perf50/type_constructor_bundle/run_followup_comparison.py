"""One additional predeclared group for the mixed original24-pair result."""
import hashlib
import json
from pathlib import Path
import subprocess
import sys

WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
REPO=STAGE.parents[1]


def main():
    original=json.loads((WORK/'ab_assessment.json').read_bytes())
    assert original['status']=='inconclusive_retained'
    assert all(row['pairs']==24 for row in original['metrics'].values())
    assert not (WORK/'ab_4.json').exists() and not (WORK/'ab_assessment_32.json').exists()
    baseline=REPO/'dist/native_1_1_10/libgdcore.dll';candidate=WORK/'bundle.dll'
    def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
    assert sha(baseline)==original['baseline_dll_sha256'] and sha(candidate)==original['candidate_dll_sha256']
    plan={'reason':'Original24 pairs mixed: CPU median +0.4425%, wall -0.2699%; retain all extreme observations.',
        'baseline_dll_sha256':sha(baseline),'candidate_dll_sha256':sha(candidate),
        'additional_groups':1,'additional_pairs':8,'combined_pairs':32,'warmup_seconds':120,
        'order':'Default AB/BA, candidate load first, complement groups1/3 candidate-first',
        'all_original_samples_retained':True,'no_additional_group_after_this_one':True,
        'original_assessment_sha256':sha(WORK/'ab_assessment.json')}
    path=WORK/'followup_plan.json';assert not path.exists()
    path.write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8',newline='\n')
    subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'compare_native_isolated.py'),
        '--baseline',str(baseline),'--candidate',str(candidate),'--reference',str(STAGE/'native_perf50_event_bus_serial.json'),
        '--out',str(WORK/'ab_4.json'),'--pairs','8','--warmup-seconds','120','--quiet','--candidate-load-first'],check=True)
    subprocess.run([sys.executable,'-X','utf8',str(WORK/'assess_resolved.py'),'--reports',
        *[str(WORK/f'ab_{i}.json') for i in (1,2,3,4)],'--out',str(WORK/'ab_assessment_32.json')],check=True)


if __name__=='__main__':main()
