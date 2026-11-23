"""Count actual changed-path calls; the macro is absent from production builds."""
import ctypes
import hashlib
import json
from pathlib import Path
import runpy
import shutil
import subprocess
import tempfile
import psutil
from prepare_native_storage_bundle import STAGE,WORK,ACCEPTED,EXPECTED,sha

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    out=WORK/'allocation_probe.json';assert not out.exists()
    src=WORK/'prototype_src';original=Path((WORK/'objects.txt').read_text('utf8'))
    objects=Path(tempfile.mkdtemp(prefix='native-storage-counts-'))
    names=['gd_rt','engine_wrapper','sym_ids','register_all',*[f'shard_{i:02d}' for i in range(16)]]
    changes={'gd_rt':src/'gd_rt.cpp','shard_00':src/'gen/shards/shard_00.cpp'}
    for n in names:
        if n not in changes:shutil.copyfile(original/(n+'.o'),objects/(n+'.o'))
    flags=runpy.run_path(str(src/'build_windows.py'))['COMMON'];compiler='D:/mingw64/bin/g++.exe'
    # A semantic verifier may compile one independent fixture concurrently.
    # Keep this probe at one compiler so the total never exceeds two.
    for n,p in changes.items():
        with (WORK/('probe_'+n+'_compile.log')).open('wb') as log:
            subprocess.run([compiler,*flags,'-DGD_STORAGE_PROBE','-c',str(p),'-o',str(objects/(n+'.o'))],
                           stdout=log,stderr=subprocess.STDOUT,check=True)
    dll=objects/'libgdcore.dll'
    with (WORK/'probe_link.log').open('wb') as log:
        subprocess.run([compiler,*flags,'-shared','-static','-o',str(dll),
            *[str(objects/(n+'.o')) for n in names]],stdout=log,stderr=subprocess.STDOUT,check=True)
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    sim=load_simulator(dll);signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    stat=sim.lib.gd_storage_probe_stat;stat.argtypes=[ctypes.c_uint];stat.restype=ctypes.c_uint64
    original_counts=[stat(i) for i in range(8)]
    result=measure(sim,jobs,1,0,continuous=True)
    counts=[stat(i)-original_counts[i] for i in range(8)]
    ref=json.loads((STAGE/'native_perf50_event_bus_serial.json').read_bytes())
    assert signature.hexdigest()==ref['inputs_sha256'] and result['results_sha256']==ref['results_sha256']
    assert result['matched_original_terminal']==200 and all(counts[i]>0 for i in range(5))
    saved=sum(counts[:4])+20*counts[4]
    report=dict(passed=True,semantic_probe_only=True,not_for_timing_or_deployment=True,
        baseline_dll_sha256=EXPECTED,probe_dll_sha256=sha(dll),source_manifest_sha256=sha(WORK/'transform.json'),
        macro='GD_STORAGE_PROBE; absent from ordinary semantic and formal builds',
        counts=dict(zip(('make_str','str_concat','reserved_arrays','reserved_dicts','item_header_groups',
                         'unused','array_reserved_values','dict_reserved_entries'),counts)),
        eliminated_arena_alloc_calls_in_fixed200=saved,
        no_cpu_saving_or_percentage_forecast=True,results_sha256=result['results_sha256'])
    out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report,indent=2),flush=True)

if __name__=='__main__':main()
