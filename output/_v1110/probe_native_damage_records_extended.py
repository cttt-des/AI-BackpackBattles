"""Expanded original-DLL differential followed by one declared local cost screen."""
import json
import shutil
import statistics
import subprocess
import sys
import tempfile
from prepare_native_damage_records import BASE,STAGE,WORK,EXPECTED,sha

DEPENDENCIES=[STAGE/'test_native_damage_records_extended.cpp',STAGE/'test_native_damage_records.cpp',WORK/'preflight_damage_records.hpp',WORK/'native_event_kernel.hpp',WORK/'damage_state_fields.hpp',WORK/'damage_fixture.hpp']

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    hashes={p.name:sha(p) for p in DEPENDENCIES}
    screen='--screen' in sys.argv
    matched='--matched' in sys.argv
    if matched:hashes['reference_damage_records.hpp']=sha(WORK/'reference_damage_records.hpp')
    correctness_name='matched_correctness.json' if matched else 'extended_correctness.json'
    if screen:
        oracle=json.loads((WORK/correctness_name).read_bytes())
        assert oracle['passed'] and oracle['dependency_sha256']==hashes
        target=WORK/('screen_matched.json' if matched else 'screen.json');assert not target.exists()
        log=WORK/('screen_matched.log' if matched else 'screen.log');assert not log.exists()
        plan=dict(baseline_dll_sha256=EXPECTED,workloads=['effect damage','weapon-source damage'],calls_per_arm=10000,pairs_per_workload=8,alternating_order=True,normal_priority_all8=True,
                  all_original_case_hashes_required=True,complete_local_matrix_cases=oracle['cases'],no_whole_fight_gain_claim=True,dependency_sha256=hashes)
        if matched:
            plan.update(baseline_kind='exact old method body compiled in the same EXE with the candidate; both O3, neither PGO',reason='Matching local compilation isolates the source transformation from the deployed DLL PGO/LTO coverage; fresh whole-DLL PGO and fixed200 A/B still required')
            if (WORK/'screen.json').exists():plan['retained_initial_screen_sha256']=sha(WORK/'screen.json')
        (WORK/('evaluation_plan_matched.json' if matched else 'evaluation_plan.json')).write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    else:
        target=WORK/correctness_name;assert not target.exists()
        index=len(list(WORK.glob('extended_attempt_*.log')))+1;log=WORK/f'extended_attempt_{index}.log'
    with tempfile.TemporaryDirectory(prefix='native-damage-records-expanded-') as directory:
        from pathlib import Path
        root=Path(directory);shutil.copyfile(BASE/'libgdcore.dll',root/'libgdcore.dll');exe=root/'test.exe'
        with log.open('w',encoding='utf8') as output:
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off',*(['-DGD_MATCHED_LOCAL'] if matched else []),'-I',str(WORK),'-I',str(BASE),str(STAGE/'test_native_damage_records_extended.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],stdout=output,stderr=subprocess.STDOUT,check=True)
            result=subprocess.run([str(exe),*(['--screen'] if screen else [])],capture_output=True,text=True)
            output.write(result.stdout+result.stderr)
        if result.returncode:print(result.stdout+result.stderr,flush=True)
        result.check_returncode();report=json.loads(result.stdout)
    if not screen and (WORK/'extended_correctness_12800.json').exists():
        previous=json.loads((WORK/'extended_correctness_12800.json').read_bytes())
        assert report['case_hashes'][:previous['cases']]==previous['case_hashes']
        report['retained_original_12800_case_hashes']=True
    if matched and not screen:
        original=json.loads((WORK/'extended_correctness.json').read_bytes())
        assert report['case_hashes']==original['case_hashes'] and report['legacy_counter_hashes']==original['legacy_counter_hashes']
        report['all12920_independent_dll_hashes_and_counters_equal']=True
    if screen:
        for workload in report['workloads']:
            workload['metrics']={name:dict(paired_median_time_reduction_pct=statistics.median(100*(1-p['candidate'][name]/p['baseline'][name]) for p in workload['pairs']) if all(p['baseline'][name]>0 for p in workload['pairs']) else None,
                zero_baseline_pairs=sum(p['baseline'][name]==0 for p in workload['pairs']),sum_time_reduction_pct=100*(1-sum(p['candidate'][name] for p in workload['pairs'])/sum(p['baseline'][name] for p in workload['pairs'])) if sum(p['baseline'][name] for p in workload['pairs'])>0 else None) for name in ('cpu_s','wall_s','cycles')}
        report.update(passed=True,independent_oracle_sha256=sha(WORK/'extended_correctness.json'),no_whole_fight_gain_claim=True,matching_local_compilation=matched)
    report.update(baseline_dll_sha256=EXPECTED,dependency_sha256=hashes)
    target.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps({key:([dict(item=w['item'],metrics=w['metrics']) for w in value] if key=='workloads' else value) for key,value in report.items() if key not in ('case_hashes','legacy_counter_hashes','dependency_sha256')},indent=2))

if __name__=='__main__':main()
