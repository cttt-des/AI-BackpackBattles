"""Screen the same-event-path composition without another simulator rebuild."""
import hashlib
import json
from pathlib import Path
import shutil
import statistics
import subprocess
import tempfile

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
WORK=STAGE/'native_perf50/event_emission_probe'


def main():
    plan=json.loads((WORK/'screen_protocol.json').read_bytes())
    assert plan['screen_pairs']==8 and plan['bus_events_per_arm']==1000000
    assert not (WORK/'bus_screen.json').exists()
    assert json.loads((WORK/'emission_correctness_baseline.json').read_bytes())['cases']==4417
    with tempfile.TemporaryDirectory(prefix='native-emission-bus-screen-') as directory:
        root=Path(directory);shutil.copyfile(BASE/'libgdcore.dll',root/'libgdcore.dll');exe=root/'test.exe'
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off',
            '-I',str(STAGE),'-I',str(WORK),'-I',str(BASE),str(STAGE/'test_native_event_identity_bus.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
        result=subprocess.run([str(exe)],capture_output=True,text=True)
        (WORK/'bus_screen.log').write_text(result.stdout+result.stderr,encoding='utf8')
        if result.returncode:print(result.stdout+result.stderr,flush=True)
        result.check_returncode();report=json.loads(result.stdout)
    assert report['passed'] and report['cases']==320 and len(report['pairs'])==8
    report['metrics']={}
    for metric in ('cpu_s','wall_s','cycles'):
        report['metrics'][metric]={
            'paired_median_time_reduction_pct':statistics.median(100*(1-p['candidate'][metric]/p['baseline'][metric]) for p in report['pairs']),
            'sum_time_reduction_pct':100*(1-sum(p['candidate'][metric] for p in report['pairs'])/sum(p['baseline'][metric] for p in report['pairs'])),
            'candidate_wins':sum(p['candidate'][metric]<p['baseline'][metric] for p in report['pairs'])}
    report.update(baseline_dll_sha256=hashlib.sha256((BASE/'libgdcore.dll').read_bytes()).hexdigest(),
        helper_sha256=hashlib.sha256((STAGE/'event_emission_fastpath.hpp').read_bytes()).hexdigest(),
        scope='Combined event-bus fixture only. No whole-fight gain is established.',
        retained_component_actual_whole_fight_time_reduction_pct={'cpu_sum':0.28901734104046506,'cpu_median':0.0,'wall_median':0.27100363753698176},
        no_full_simulator_build_before_screen=True,no_deployment=True)
    (WORK/'bus_screen.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps({k:v for k,v in report.items() if k!='pairs'},indent=2))


if __name__=='__main__':main()
