"""Predeclared24 paired trials plus at most one bounded sensitivity follow-up."""
import json,shutil,subprocess,sys
from pathlib import Path
from prepare_frame_guard_reuse import STAGE,WORK,BASE,ACCEPTED,EXPECTED,sha,save,verify_projection
def main():
    import psutil
    psutil.Process().nice(psutil.NORMAL_PRIORITY_CLASS)
    gate=json.loads((WORK/'complete_correctness_gate.json').read_bytes());assert gate['passed'] and gate['dll_sha256']==sha(WORK/'bundle.dll')
    assert sha(BASE/'libgdcore.dll')==EXPECTED;verify_projection(WORK/'bundle_src')
    assert not (WORK/'ab_1.json').exists(),'Do not repeat observed comparisons'
    assess=WORK/'assess_resolved.py';shutil.copyfile(ACCEPTED/'assess_resolved.py',assess)
    for group in (1,2,3):
        command=[sys.executable,'-u','-X','utf8',str(STAGE/'compare_native_isolated_blocks.py'),'--baseline',str(ACCEPTED/'bundle.dll'),'--candidate',str(WORK/'bundle.dll'),'--reference',str(STAGE/'native_perf50_event_bus_serial.json'),'--out',str(WORK/f'ab_{group}.json'),'--pairs','8','--batch-repetitions','4','--warmup-seconds','120','--quiet']
        if group in (1,3):command.append('--candidate-first')
        if group==2:command.append('--candidate-load-first')
        print(f'Starting predeclared paired group{group}/3',flush=True);subprocess.run(command,check=True)
    def assessment(count,name):
        subprocess.run([sys.executable,'-X','utf8',str(assess),'--reports',*[str(WORK/f'ab_{i}.json') for i in range(1,count+1)],'--out',str(WORK/name)],check=True)
        return json.loads((WORK/name).read_bytes())
    first=assessment(3,'ab_assessment.json');chosen='ab_assessment.json';result=first
    mixed=first['status']=='inconclusive_retained' or any(r[m]['paired_median_time_reduction_pct']<=0 for r in first['leave_one_group_out_sensitivity'] for m in ('main_thread_cpu_s','wall_s'))
    if mixed and first['status']!='consistent_regression_bundle_only':
        save('followup_plan.json',dict(maximum_extra_groups=1,all_original24_retained=True,all32_must_be_used=True,no_more_same_source_groups=True,trigger='First24 inconclusive or leave-one-group sensitivity not positive'))
        print('Starting the only allowed eight-pair follow-up',flush=True)
        subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'compare_native_isolated_blocks.py'),'--baseline',str(ACCEPTED/'bundle.dll'),'--candidate',str(WORK/'bundle.dll'),'--reference',str(STAGE/'native_perf50_event_bus_serial.json'),'--out',str(WORK/'ab_4.json'),'--pairs','8','--batch-repetitions','4','--warmup-seconds','120','--quiet','--candidate-load-first'],check=True)
        chosen='ab_assessment_32.json';result=assessment(4,chosen)
    assert result['baseline_dll_sha256']==EXPECTED and result['candidate_dll_sha256']==sha(WORK/'bundle.dll')
    verify_projection(WORK/'bundle_src');assert sha(BASE/'libgdcore.dll')==EXPECTED
    save('candidate_decision.json',dict(status=result['status'],accepted=result['status']=='positive_combined_evidence',selected_assessment=chosen,assessment_sha256=sha(WORK/chosen),candidate_dll_sha256=sha(WORK/'bundle.dll'),baseline_dll_sha256=EXPECTED,pairs=result['metrics']['wall_s']['pairs'],all_original_pairs_and_extremes_retained=True,no_same_source_retiming=True,not_deployed_yet=True))
    print('A/B decision '+result['status'],flush=True)
if __name__=='__main__':main()
