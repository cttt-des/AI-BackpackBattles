"""Preserve the first screen and per-case original DLL results."""
import hashlib
import json
from pathlib import Path
import shutil
import statistics
import subprocess
import sys
import tempfile
STAGE=Path(__file__).resolve().parent
WORK=STAGE/'native_perf50/static_setup_probe'
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'

def main():
    plan=json.loads((WORK/'evaluation_plan.json').read_bytes())
    assert not (WORK/'screen.json').exists()
    assert hashlib.sha256((BASE/'libgdcore.dll').read_bytes()).hexdigest()==plan['baseline_dll_sha256']
    if '--assess-existing' in sys.argv:
        report=json.loads((WORK/'screen.log').read_text('utf8'))
        oracle=json.loads((WORK/'correctness_baseline.json').read_bytes())
        assert report['passed'] and oracle['case_hashes'] and report['cases']==oracle['cases']
    else:
      with tempfile.TemporaryDirectory(prefix='native-static-setup-') as directory:
        root=Path(directory);shutil.copyfile(BASE/'libgdcore.dll',root/'libgdcore.dll');exe=root/'screen.exe'
        command=['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-I',str(WORK),'-I',str(BASE),str(STAGE/'test_native_static_setup.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)]
        subprocess.run(command,check=True)
        result=subprocess.run([str(exe)],capture_output=True,text=True)
        (WORK/'screen.log').write_text(result.stdout+result.stderr,encoding='utf8')
        if result.returncode: print(result.stdout+result.stderr,flush=True)
        result.check_returncode();report=json.loads(result.stdout)
        raw=subprocess.check_output([str(exe),'--correctness-only'],text=True)
        (WORK/'correctness_baseline.json').write_text(raw,encoding='utf8')
    for workload in report['workloads']:
        assert len(workload['pairs'])==8
        workload['metrics']={name:{'paired_median_time_reduction_pct':statistics.median(100*(1-p['candidate'][name]/p['baseline'][name]) for p in workload['pairs']) if all(p['baseline'][name]>0 for p in workload['pairs']) else None,
            'zero_baseline_pairs':sum(p['baseline'][name]==0 for p in workload['pairs']),
            'sum_time_reduction_pct':100*(1-sum(p['candidate'][name] for p in workload['pairs'])/sum(p['baseline'][name] for p in workload['pairs'])) if sum(p['baseline'][name] for p in workload['pairs'])>0 else None} for name in ('cpu_s','wall_s','cycles')}
    report.update(baseline_dll_sha256=plan['baseline_dll_sha256'],test_source_sha256=hashlib.sha256((STAGE/'test_native_static_setup.cpp').read_bytes()).hexdigest(),helper_sha256=hashlib.sha256((WORK/'static_setup_helper.hpp').read_bytes()).hexdigest(),no_whole_fight_gain_claim=True,
        local_getter_uses_exported_constant_accessor=True,production_getter_returns_same_literal_directly=True)
    (WORK/'screen.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps({k:([{'mode':row['mode'],'metrics':row['metrics']} for row in v] if k=='workloads' else v) for k,v in report.items()},indent=2))

if __name__=='__main__':main()
