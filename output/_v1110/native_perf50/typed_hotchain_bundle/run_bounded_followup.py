"""One independent group for a weak sign-sensitive result; retain all first24 pairs."""
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
    plan_path=WORK/'followup_plan.json';assert not plan_path.exists()
    first=json.loads((WORK/'ab_assessment.json').read_bytes())
    assert first['status']=='positive_combined_evidence' and first['metrics']['main_thread_cpu_s']['pairs']==24
    assert first['leave_one_group_out_sensitivity'][2]['main_thread_cpu_s']['paired_median_time_reduction_pct']==0
    assert first['leave_one_group_out_sensitivity'][2]['wall_s']['paired_median_time_reduction_pct']<0
    before=json.loads((WORK/'source_before_build.json').read_bytes())
    assert before=={p.relative_to(WORK/'bundle_src').as_posix():sha(p) for p in (WORK/'bundle_src').rglob('*') if p.is_file()}
    assert sha(WORK/'bundle.dll')==first['candidate_dll_sha256']
    assert sha(REPO/'dist/native_1_1_10/libgdcore.dll')==first['baseline_dll_sha256']
    plan=dict(reason='First24 positive by declared median rule,but removal of group3 gives CPU0 and wall negative;use the original one-followup allowance before deployment',
        first_assessment_sha256=sha(WORK/'ab_assessment.json'),baseline_dll_sha256=first['baseline_dll_sha256'],candidate_dll_sha256=first['candidate_dll_sha256'],
        additional_groups=1,additional_pairs=8,all_original_samples_retained=True,total_pairs=32,
        same_fixed200_repetitions=4,same_single_dll_workers=True,warmup_seconds=120,
        decision='Deploy only if CPU and wall medians over all32 pairs remain positive and all prior semantic/raw24 gates pass;no further groups for this source',
        no_primary_report_overwrite=True,no_semantic_or_raw24_rerun_for_unchanged_dll=True)
    plan_path.write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    out=WORK/'ab_4.json';assert not out.exists()
    command=[sys.executable,'-u','-X','utf8',str(STAGE/'compare_native_isolated_blocks.py'),'--baseline',str(REPO/'dist/native_1_1_10/libgdcore.dll'),
        '--candidate',str(WORK/'bundle.dll'),'--reference',str(STAGE/'native_perf50_event_bus_serial.json'),'--out',str(out),
        '--pairs','8','--batch-repetitions','4','--warmup-seconds','120','--quiet','--candidate-load-first']
    subprocess.run(command,check=True)
    subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/'assess_resolved.py'),'--reports',*[str(WORK/f'ab_{i}.json') for i in (1,2,3,4)],'--out',str(WORK/'ab_assessment_32.json')],check=True)
    assert sha(WORK/'ab_assessment.json')==plan['first_assessment_sha256']
    assert sha(WORK/'bundle.dll')==plan['candidate_dll_sha256']

if __name__=='__main__':main()
