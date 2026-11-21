"""Screen the actual event-bus path before committing to a full simulator build."""
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
    protocol=json.loads((WORK/'bus_screen_protocol.json').read_bytes())
    assert protocol['status']=='declared_before_long_screen' and protocol['pairs']==8
    assert not (WORK/'bus_screen.json').exists()
    assert hashlib.sha256((BASE/'libgdcore.dll').read_bytes()).hexdigest()=='401376afb48e5340be48578aa534eac0b823a69d3447044639e3d3ee5cb7a259'
    with tempfile.TemporaryDirectory(prefix='native-event-bus-screen-') as directory:
        root=Path(directory);shutil.copyfile(BASE/'libgdcore.dll',root/'libgdcore.dll');exe=root/'screen.exe'
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-march=native','-std=c++20','-ffp-contract=off',
            '-I',str(STAGE),'-I',str(WORK),'-I',str(BASE),str(STAGE/'test_native_event_identity_bus.cpp'),str(root/'libgdcore.dll'),'-o',str(exe)],check=True)
        completed=subprocess.run([str(exe)],capture_output=True,text=True)
        (WORK/'bus_screen_long.log').write_text(completed.stdout+completed.stderr,encoding='utf8')
        if completed.returncode:print(completed.stdout+completed.stderr,flush=True)
        completed.check_returncode();report=json.loads(completed.stdout)
    assert report['cases']==256 and report['events_per_arm']==1000000 and len(report['pairs'])==8
    assert report['fast_hits']>0 and report['fallbacks']>0
    report['metrics']={}
    for metric in ('cpu_s','wall_s','cycles'):
        report['metrics'][metric]={
            'paired_median_time_reduction_pct':statistics.median(100*(1-p['candidate'][metric]/p['baseline'][metric]) for p in report['pairs']),
            'sum_time_reduction_pct':100*(1-sum(p['candidate'][metric] for p in report['pairs'])/sum(p['baseline'][metric] for p in report['pairs'])),
            'candidate_wins':sum(p['candidate'][metric]<p['baseline'][metric] for p in report['pairs'])}
    report.update(baseline_dll_sha256=hashlib.sha256((BASE/'libgdcore.dll').read_bytes()).hexdigest(),
        source_sha256={name:hashlib.sha256((STAGE/name).read_bytes()).hexdigest() for name in ('event_identity_fastpath.hpp','event_identity_receiver_fastpath.hpp','test_native_event_identity_bus.cpp')},
        actual_original_bus_function_is_reference=True,
        callbacks_binding_nested_terminal_unknown_getters_trace_toggles_snapshot_rng_ids_flags_checked=True,
        no_full_simulator_build=True,no_deployment=True,
        limitation='This measures a controlled event-bus fixture and establishes no whole-fight speedup. Actual call frequency, production code generation and fixed200 A/B still matter.')
    (WORK/'bus_screen.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps({k:v for k,v in report.items() if k!='pairs'},indent=2))


if __name__=='__main__':main()
