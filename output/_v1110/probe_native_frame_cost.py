"""Measure persistent frame fixtures only after current whole-fight jobs finish."""
import hashlib
import json
from pathlib import Path
import shutil
import statistics
import subprocess
import tempfile
import psutil
STAGE=Path(__file__).resolve().parent
WORK=STAGE/'native_perf50/member_frame_bundle'
BASE=STAGE/'native_perf50/lazy_diagnostics_bundle/bundle_src'
DLL=BASE.parent/'bundle.dll'
def main():
    assert not (WORK/'frame_cost_screen.json').exists()
    plan=json.loads((WORK/'frame_cost_protocol.json').read_bytes())
    assert hashlib.sha256(DLL.read_bytes()).hexdigest()==plan['baseline_dll_sha256']
    # Avoid adding even one compiler or fixture process to active formal jobs.
    for process in psutil.process_iter(['pid','cmdline']):
        if process.pid==psutil.Process().pid:continue
        command=' '.join(process.info['cmdline'] or []).replace('\\','/')
        assert not any(name in command for name in ('member_only_bundle/build_bundle.py','member_only_bundle/qualify_when_ready.py','compare_native_isolated_blocks.py','bench_native_load_calibration.py')),command
    with tempfile.TemporaryDirectory(prefix='native-frame-cost-') as directory:
        root=Path(directory);shutil.copyfile(DLL,root/'libgdcore.dll');exe=root/'screen.exe'
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off','-I',str(WORK),'-I',str(BASE),str(STAGE/'test_native_frame_cost.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
        completed=subprocess.run([str(exe)],capture_output=True,text=True)
        (WORK/'frame_cost_screen.log').write_text(completed.stdout+completed.stderr,encoding='utf8')
        if completed.returncode:print(completed.stdout+completed.stderr,flush=True)
        completed.check_returncode();report=json.loads(completed.stdout)
    assert len(report['workloads'])==2
    for workload in report['workloads']:
        assert len(workload['pairs'])==8
        workload['metrics']={name:{'paired_median_reduction_pct':statistics.median(100*(1-p['candidate'][name]/p['baseline'][name]) for p in workload['pairs']),
            'cumulative_reduction_pct':100*(1-sum(p['candidate'][name] for p in workload['pairs'])/sum(p['baseline'][name] for p in workload['pairs']))} for name in ('cpu_s','wall_s','cycles')}
    report.update(baseline_dll_sha256=plan['baseline_dll_sha256'],source_sha256=hashlib.sha256((STAGE/'test_native_frame_cost.cpp').read_bytes()).hexdigest(),
        helper_sha256=hashlib.sha256((WORK/'preflight_frame_helper.hpp').read_bytes()).hexdigest(),whole_fight_performance_not_established=True)
    (WORK/'frame_cost_screen.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps({k:([{'mode':v['mode'],'metrics':v['metrics']} for v in value] if k=='workloads' else value) for k,value in report.items()},indent=2))
if __name__=='__main__':main()
