"""Qualify the one predeclared32-pair follow-up, retaining weak evidence."""
import hashlib
import json
from pathlib import Path
from qualify_when_ready import run

WORK=Path(__file__).resolve().parent


def main():
    record=json.loads((WORK/'ab_assessment_32.json').read_bytes())
    assert record['status']=='positive_combined_evidence'
    assert all(row['pairs']==32 for row in record['metrics'].values())
    assert record['candidate_dll_sha256']==hashlib.sha256((WORK/'bundle.dll').read_bytes()).hexdigest()
    plan={'assessment':'ab_assessment_32.json','whole_bundle_retained':True,
        'median_cpu_time_reduction_pct':record['metrics']['main_thread_cpu_s']['paired_median_time_reduction_pct'],
        'median_wall_time_reduction_pct':record['metrics']['wall_s']['paired_median_time_reduction_pct'],
        'sum_cpu_time_reduction_pct':record['metrics']['main_thread_cpu_s']['sum_time_reduction_pct'],
        'sum_wall_time_reduction_pct':record['metrics']['wall_s']['sum_time_reduction_pct'],
        'interpretation':'Small positive medians, negative cumulative reductions; weak evidence, not proven repeatable gain.',
        'additional_ab_groups':0,'next':'Full strict truth and one raw24/calibration24; inspect before any deployment.'}
    path=WORK/'composition_decision.json';assert not path.exists()
    path.write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8',newline='\n')
    run('run_full_gate.py','full_gate.log','bundle')
    run('finish_gate.py','finish_gate.log')
    run('run_release_measurements.py','release_measurements.log')
    print('Qualification finished; weak paired evidence still requires deployment review',flush=True)


if __name__=='__main__':main()
