"""Run the predeclared label-function differential and local AB/BA screen once."""
import hashlib
import json
from pathlib import Path
import shutil
import statistics
import subprocess
import tempfile

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
WORK=STAGE/'native_perf50/lazy_diagnostics_probe'

def main():
    design=json.loads((WORK/'design.json').read_bytes())
    assert hashlib.sha256((BASE/'libgdcore.dll').read_bytes()).hexdigest()==design['baseline_dll_sha256']
    assert not (WORK/'screen.json').exists()
    with tempfile.TemporaryDirectory(prefix='native-lazy-diagnostic-') as directory:
        root=Path(directory);shutil.copyfile(BASE/'libgdcore.dll',root/'libgdcore.dll')
        exe=root/'screen.exe'
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off',
            '-I',str(STAGE),'-I',str(WORK),'-I',str(BASE),str(STAGE/'test_native_lazy_diagnostics.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
        completed=subprocess.run([str(exe)],capture_output=True,text=True)
        (WORK/'screen.log').write_text(completed.stdout+completed.stderr,encoding='utf8')
        if completed.returncode:print(completed.stdout+completed.stderr,flush=True)
        completed.check_returncode();report=json.loads(completed.stdout)
        original=subprocess.run([str(exe),'--correctness-only'],capture_output=True,text=True,check=True)
        (WORK/'correctness_baseline.json').write_text(original.stdout,encoding='utf8')
    assert report['passed'] and report['cases']==2048 and len(report['pairs'])==8
    report['metrics']={metric:{
        'paired_median_time_reduction_pct':statistics.median(100*(1-p['candidate'][metric]/p['baseline'][metric]) for p in report['pairs']),
        'sum_time_reduction_pct':100*(1-sum(p['candidate'][metric] for p in report['pairs'])/sum(p['baseline'][metric] for p in report['pairs'])),
        'candidate_wins':sum(p['candidate'][metric]<p['baseline'][metric] for p in report['pairs'])}for metric in ('cpu_s','wall_s','cycles')}
    report['baseline_dll_sha256']=design['baseline_dll_sha256']
    report['source_sha256']={name:hashlib.sha256((STAGE/name).read_bytes()).hexdigest() for name in ('native_lazy_diagnostics.hpp','test_native_lazy_diagnostics.cpp','prepare_native_lazy_diagnostics.py')}
    report['fixture_sha256']=hashlib.sha256((WORK/'preflight_label.hpp').read_bytes()).hexdigest()
    report['no_full_build_or_deployment']=True
    (WORK/'screen.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps({k:v for k,v in report.items() if k!='pairs'},indent=2))

if __name__=='__main__':main()
