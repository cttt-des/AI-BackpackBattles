"""Keep the first local screen and independent original-DLL per-case oracle."""
import hashlib
import json
from pathlib import Path
import shutil
import statistics
import subprocess
import tempfile
STAGE=Path(__file__).resolve().parent
WORK=STAGE/'native_perf50/static_collections_probe'
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
def main():
    plan=json.loads((WORK/'evaluation_plan.json').read_bytes());assert not (WORK/'screen.json').exists()
    assert hashlib.sha256((BASE/'libgdcore.dll').read_bytes()).hexdigest()==plan['baseline_dll_sha256']
    with tempfile.TemporaryDirectory(prefix='native-static-collections-') as directory:
        root=Path(directory);shutil.copyfile(BASE/'libgdcore.dll',root/'libgdcore.dll');exe=root/'screen.exe'
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-I',str(WORK),'-I',str(BASE),str(STAGE/'test_native_static_collections.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
        completed=subprocess.run([str(exe)],capture_output=True,text=True)
        (WORK/'screen.log').write_text(completed.stdout+completed.stderr,encoding='utf8')
        if completed.returncode:print(completed.stdout+completed.stderr,flush=True)
        completed.check_returncode();report=json.loads(completed.stdout)
        raw=subprocess.check_output([str(exe),'--correctness-only'],text=True)
        (WORK/'correctness_baseline.json').write_text(raw,encoding='utf8')
    assert report['passed'] and len(report['workloads'])==2
    for workload in report['workloads']:
        assert len(workload['pairs'])==8
        workload['metrics']={name:{'paired_median_time_reduction_pct':statistics.median(100*(1-p['candidate'][name]/p['baseline'][name]) for p in workload['pairs']),
            'sum_time_reduction_pct':100*(1-sum(p['candidate'][name] for p in workload['pairs'])/sum(p['baseline'][name] for p in workload['pairs']))} for name in ('cpu_s','wall_s','cycles')}
    report.update(baseline_dll_sha256=plan['baseline_dll_sha256'],source_sha256=hashlib.sha256((STAGE/'test_native_static_collections.cpp').read_bytes()).hexdigest(),
        helper_sha256=hashlib.sha256((WORK/'static_collection_helper.hpp').read_bytes()).hexdigest(),no_whole_fight_performance_claim=True)
    (WORK/'screen.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps({k:([{'mode':v['mode'],'metrics':v['metrics']} for v in value] if k=='workloads' else value) for k,value in report.items()},indent=2))
if __name__=='__main__':main()
