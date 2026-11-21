"""One predeclared local screen; preserve its first results and independent oracle."""
import hashlib
import json
from pathlib import Path
import shutil
import statistics
import subprocess
import tempfile
from prepare_native_spatial import BASE,WORK,STAGE,EXPECTED

def main():
    assert not (WORK/'screen.json').exists()
    assert hashlib.sha256((BASE/'libgdcore.dll').read_bytes()).hexdigest()==EXPECTED
    with tempfile.TemporaryDirectory(prefix='native-spatial-') as directory:
        root=Path(directory);shutil.copyfile(BASE/'libgdcore.dll',root/'libgdcore.dll');exe=root/'screen.exe'
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-I',str(WORK),'-I',str(BASE),str(STAGE/'test_native_spatial.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
        result=subprocess.run([str(exe)],capture_output=True,text=True)
        (WORK/'screen.log').write_text(result.stdout+result.stderr,encoding='utf8')
        if result.returncode:print(result.stdout+result.stderr,flush=True)
        result.check_returncode();report=json.loads(result.stdout)
        raw=subprocess.check_output([str(exe),'--correctness-only'],text=True)
        (WORK/'correctness_baseline.json').write_text(raw,encoding='utf8')
    for workload in report['workloads']:
        assert len(workload['pairs'])==8
        workload['metrics']={name:{'paired_median_time_reduction_pct':statistics.median(100*(1-p['candidate'][name]/p['baseline'][name]) for p in workload['pairs']) if all(p['baseline'][name]>0 for p in workload['pairs']) else None,
            'sum_time_reduction_pct':100*(1-sum(p['candidate'][name] for p in workload['pairs'])/sum(p['baseline'][name] for p in workload['pairs'])) if sum(p['baseline'][name] for p in workload['pairs'])>0 else None} for name in ('cpu_s','wall_s','cycles')}
    report.update(baseline_dll_sha256=EXPECTED,test_source_sha256=hashlib.sha256((STAGE/'test_native_spatial.cpp').read_bytes()).hexdigest(),header_sha256=hashlib.sha256((WORK/'preflight_spatial.hpp').read_bytes()).hexdigest(),no_whole_fight_gain_claim=True)
    (WORK/'screen.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(dict(passed=report['passed'],cases=report['cases'],workloads=[dict(mode=w['mode'],metrics=w['metrics']) for w in report['workloads']]),indent=2))

if __name__=='__main__':main()
