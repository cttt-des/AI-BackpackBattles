"""Cheap correctness and kernel screening; no candidate simulator DLL build."""
import hashlib
import json
from pathlib import Path
import shutil
import statistics
import subprocess
import tempfile

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
WORK=STAGE/'native_perf50/event_identity_probe'


def main():
    WORK.mkdir(exist_ok=True)
    baseline=hashlib.sha256((BASE/'libgdcore.dll').read_bytes()).hexdigest()
    assert baseline=='401376afb48e5340be48578aa534eac0b823a69d3447044639e3d3ee5cb7a259'
    assert not (WORK/'primitive_screen.json').exists(),'Keep the first screening result'
    with tempfile.TemporaryDirectory(prefix='native-event-identity-') as directory:
        root=Path(directory);shutil.copyfile(BASE/'libgdcore.dll',root/'libgdcore.dll');exe=root/'screen.exe'
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off',
            '-I',str(STAGE),'-I',str(BASE),str(STAGE/'test_native_event_identity.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
        result=subprocess.run([str(exe)],capture_output=True,text=True)
        (WORK/'primitive_screen.log').write_text(result.stdout+result.stderr,encoding='utf8')
        if result.returncode:print(result.stdout+result.stderr,flush=True)
        result.check_returncode();report=json.loads(result.stdout)
    report.update(baseline_dll_sha256=baseline,
        helper_sha256=hashlib.sha256((STAGE/'event_identity_fastpath.hpp').read_bytes()).hexdigest(),
        fixture_sha256=hashlib.sha256((STAGE/'test_native_event_identity.cpp').read_bytes()).hexdigest(),
        original_source='CoreEventBus.emitAndLog emitter identity: identifier string + /ot + integer owner',
        no_full_simulator_build=True,no_deployment=True,
        limitations='Local primitive screening includes avoided allocations. It does not establish full-fight speedup or yet validate the event-bus integration/unknown getter order.')
    report['metrics']={}
    for metric in ('cpu_s','wall_s','cycles'):
        report['metrics'][metric]={
            'paired_median_time_reduction_pct':statistics.median(100*(1-p['candidate'][metric]/p['baseline'][metric]) for p in report['pairs']),
            'sum_time_reduction_pct':100*(1-sum(p['candidate'][metric] for p in report['pairs'])/sum(p['baseline'][metric] for p in report['pairs'])),
            'candidate_wins':sum(p['candidate'][metric]<p['baseline'][metric] for p in report['pairs'])}
    assert report['cases']==24288 and len(report['pairs'])==8
    (WORK/'primitive_screen.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps({k:v for k,v in report.items() if k!='pairs'},indent=2))


if __name__=='__main__':main()
