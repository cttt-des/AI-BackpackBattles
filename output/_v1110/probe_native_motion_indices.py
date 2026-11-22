"""Independent deployed-DLL cases and a one-shot matched local cost screen."""
import json
from pathlib import Path
import shutil
import statistics
import subprocess
import sys
import tempfile
from prepare_native_motion_indices import BASE,STAGE,WORK,EXPECTED,sha

def main():
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    screen='--screen' in sys.argv;matched='--matched' in sys.argv
    assert not screen or matched,'Compare both method bodies compiled in the same EXE'
    deps={p.name:sha(p) for p in (STAGE/'test_native_motion_indices.cpp',WORK/'preflight_motion_indices.hpp')}
    for p in ('native_inline_dispatch.hpp','native_scalar_equal.hpp','native_array_index.hpp','gd_rt.hpp'):
        deps[p]=sha(BASE/p)
    name='screen_matched' if screen else 'correctness_matched' if matched else 'correctness_baseline'
    target=WORK/(name+'.json');assert not target.exists()
    if screen:
        oracle=json.loads((WORK/'correctness_matched.json').read_bytes());assert oracle['passed'] and oracle['dependency_sha256']==deps
        plan=dict(baseline_dll_sha256=EXPECTED,pairs_per_workload=8,calls_per_arm=30000,workloads=['empty','mixed kept','visual dropped','charge kept'],normal_priority_all8=True,
            matching_local_compilation=True,source_hashes=deps,independent_original_dll_cases=5840,
            reset_cost='Both arms include queue length and slot restoration between calls; allocation only before the repeated calls',
            no_whole_fight_gain_claim=True)
        (WORK/'evaluation_plan_matched.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    log=WORK/f'{name}_attempt_{len(list(WORK.glob(name+"_attempt_*.log")))+1}.log'
    with tempfile.TemporaryDirectory(prefix='native-motion-indices-') as directory:
        root=Path(directory);shutil.copyfile(BASE/'libgdcore.dll',root/'libgdcore.dll');exe=root/'test.exe'
        with log.open('w',encoding='utf8') as out:
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off',*(['-DGD_MATCHED_LOCAL'] if matched else []),'-I',str(WORK),'-I',str(BASE),str(STAGE/'test_native_motion_indices.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],stdout=out,stderr=subprocess.STDOUT,check=True)
            result=subprocess.run([str(exe),*(['--screen'] if screen else [])],text=True,capture_output=True)
            out.write(result.stdout+result.stderr)
        if result.returncode:print(result.stderr,flush=True)
        result.check_returncode();report=json.loads(result.stdout)
    if not screen:
        assert report['passed'] and report['cases']==5840
        if matched:
            oracle=json.loads((WORK/'correctness_baseline.json').read_bytes())
            assert report['case_hashes']==oracle['case_hashes'] and report['legacy_counter_hashes']==oracle['legacy_counter_hashes']
            report['all_actual_old_dll_hashes_equal']=True
    else:
        for workload in report['workloads']:
            workload['metrics']={m:dict(paired_median_time_reduction_pct=statistics.median(100*(1-p['candidate'][m]/p['baseline'][m]) for p in workload['pairs']) if all(p['baseline'][m]>0 for p in workload['pairs']) else None,
                sum_time_reduction_pct=100*(1-sum(p['candidate'][m] for p in workload['pairs'])/sum(p['baseline'][m] for p in workload['pairs'])) if sum(p['baseline'][m] for p in workload['pairs'])>0 else None) for m in ('wall_s','cpu_s','cycles')}
        report.update(passed=True,matching_local_compilation=True,no_whole_fight_gain_claim=True)
    report.update(baseline_dll_sha256=EXPECTED,dependency_sha256=deps)
    target.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps({k:([dict(workload=w['workload'],metrics=w['metrics']) for w in v] if k=='workloads' else v) for k,v in report.items() if k not in ('case_hashes','legacy_counter_hashes','dependency_sha256')},indent=2))

if __name__=='__main__':main()
