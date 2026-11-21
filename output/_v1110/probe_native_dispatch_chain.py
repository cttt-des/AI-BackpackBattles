"""Run one local screen against the deployed independent reference DLL."""
import hashlib
import json
from pathlib import Path
import shutil
import statistics
import subprocess
import sys
import tempfile
STAGE=Path(__file__).resolve().parent
WORK=STAGE/'native_perf50/dispatch_chain_probe'
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'

def main():
    revised='--hash-guard' in sys.argv
    screen_path=WORK/('screen_hash_guard.json' if revised else 'screen.json')
    log_path=WORK/('screen_hash_guard.log' if revised else 'screen.log')
    oracle_path=WORK/('correctness_baseline_hash_guard.json' if revised else 'correctness_baseline.json')
    plan=json.loads((WORK/'evaluation_plan.json').read_bytes());assert not screen_path.exists()
    if revised:
        previous=json.loads((WORK/'screen.json').read_bytes())
        assert plan['helper_sha256']!=previous['helper_sha256'] and plan['hash_guard_revision']['performance_protocol_unchanged']
        assert json.loads((WORK/'hash_negative.json').read_bytes())['reproduced']
    assert hashlib.sha256((BASE/'libgdcore.dll').read_bytes()).hexdigest()==plan['baseline_dll_sha256']
    with tempfile.TemporaryDirectory(prefix='native-dispatch-chain-') as directory:
        root=Path(directory);shutil.copyfile(BASE/'libgdcore.dll',root/'libgdcore.dll');exe=root/'screen.exe'
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-I',str(WORK),'-I',str(BASE),str(STAGE/'test_native_dispatch_chain.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
        result=subprocess.run([str(exe)],capture_output=True,text=True)
        log_path.write_text(result.stdout+result.stderr,encoding='utf8')
        if result.returncode:print(result.stdout+result.stderr,flush=True)
        result.check_returncode();report=json.loads(result.stdout)
        raw=subprocess.check_output([str(exe),'--correctness-only'],text=True)
        if revised:
            oracle=json.loads(raw);previous=json.loads((WORK/'correctness_baseline_extended.json').read_bytes())
            assert oracle['cases']==341604 and oracle['case_hashes'][:previous['cases']]==previous['case_hashes']
        oracle_path.write_text(raw,encoding='utf8')
    for workload in report['workloads']:
        assert len(workload['pairs'])==8
        workload['metrics']={name:{'paired_median_time_reduction_pct':statistics.median(100*(1-p['candidate'][name]/p['baseline'][name]) for p in workload['pairs']) if all(p['baseline'][name]>0 for p in workload['pairs']) else None,
            'zero_baseline_pairs':sum(p['baseline'][name]==0 for p in workload['pairs']),
            'sum_time_reduction_pct':100*(1-sum(p['candidate'][name] for p in workload['pairs'])/sum(p['baseline'][name] for p in workload['pairs'])) if sum(p['baseline'][name] for p in workload['pairs'])>0 else None} for name in ('cpu_s','wall_s','cycles')}
    report.update(baseline_dll_sha256=plan['baseline_dll_sha256'],test_source_sha256=hashlib.sha256((STAGE/'test_native_dispatch_chain.cpp').read_bytes()).hexdigest(),
        helper_sha256=plan['helper_sha256'],callback_sha256=plan['callback_sha256'],no_whole_fight_gain_claim=True)
    report['hash_guard_revision']=revised
    screen_path.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps({k:([{'mode':row['mode'],'metrics':row['metrics']} for row in v] if k=='workloads' else v) for k,v in report.items()},indent=2))

if __name__=='__main__':main()
