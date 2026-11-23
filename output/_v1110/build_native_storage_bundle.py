"""Rebuild only the two ABI-identical changed units for semantic verification."""
from concurrent.futures import ThreadPoolExecutor
import ctypes
import hashlib
import json
from pathlib import Path
import runpy
import shutil
import subprocess
import tempfile
import psutil
from prepare_native_storage_bundle import STAGE,BASE,WORK,ACCEPTED,EXPECTED,sha

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    src=WORK/'prototype_src';out=WORK/'prototype.dll';assert not out.exists()
    frozen=json.loads((WORK/'transform.json').read_bytes())['source_sha256']
    assert frozen=={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    old=STAGE/'native_perf50/event_factory_prototype'
    before=json.loads((old/'transform.json').read_bytes())['source_sha256']
    assert sorted(n for n in before if before[n]!=frozen[n])==['gd_rt.cpp','gen/shards/shard_00.cpp']
    original=Path((old/'objects.txt').read_text('utf8'))
    objects=Path(tempfile.mkdtemp(prefix='native-storage-semantic-'))
    (WORK/'objects.txt').write_text(str(objects),encoding='utf8')
    names=['gd_rt','engine_wrapper','sym_ids','register_all',*[f'shard_{i:02d}' for i in range(16)]]
    changes={'gd_rt':src/'gd_rt.cpp','shard_00':src/'gen/shards/shard_00.cpp'}
    hashes={n:sha(original/(n+'.o')) for n in names}
    for n in names:
        if n not in changes:shutil.copyfile(original/(n+'.o'),objects/(n+'.o'))
    flags=runpy.run_path(str(src/'build_windows.py'))['COMMON'];compiler='D:/mingw64/bin/g++.exe'
    def compile_one(row):
        n,p=row
        with (WORK/(n+'_compile_first.log')).open('wb') as log:
            subprocess.run([compiler,*flags,'-c',str(p),'-o',str(objects/(n+'.o'))],
                           stdout=log,stderr=subprocess.STDOUT,check=True)
    with ThreadPoolExecutor(max_workers=2) as pool:list(pool.map(compile_one,changes.items()))
    with (WORK/'link_first.log').open('wb') as log:
        subprocess.run([compiler,*flags,'-shared','-static','-o',str(objects/'libgdcore.dll'),
                        *[str(objects/(n+'.o')) for n in names]],stdout=log,stderr=subprocess.STDOUT,check=True)
    assert hashes=={n:sha(original/(n+'.o')) for n in names}
    shutil.copyfile(objects/'libgdcore.dll',out)
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    sim=load_simulator(out);signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    audit=sim.lib.gd_diag_native_resolved_audit;audit.argtypes=[ctypes.c_int];audit.restype=None;audit(1)
    stat=sim.lib.gd_diag_native_resolved_stat;stat.argtypes=[ctypes.c_uint];stat.restype=ctypes.c_uint64
    initial=[stat(i) for i in range(6)]
    result=measure(sim,jobs,1,0,continuous=True)
    counts=dict(zip(('generic_hits','funcref_hits','lazy_resolutions','unsupported_types','audit_mismatch','selected_fallback'),
                    [stat(i)-initial[i] for i in range(6)]))
    assert counts==json.loads((ACCEPTED/'release_audit.json').read_bytes())['coverage']
    ref=json.loads((STAGE/'native_perf50_event_bus_serial.json').read_bytes())
    assert signature.hexdigest()==ref['inputs_sha256'] and result['results_sha256']==ref['results_sha256']
    assert result['matched_original_terminal']==200 and sha(BASE/'libgdcore.dll')==EXPECTED
    report=dict(passed=True,semantic_only=True,dll_sha256=sha(out),baseline_dll_sha256=EXPECTED,
        source_manifest_sha256=sha(WORK/'transform.json'),reused_objects=18,recompiled_units=2,
        original_six_counters=counts,inputs_sha256=signature.hexdigest(),results_sha256=result['results_sha256'],
        matched_original_terminal=200,no_throughput_claim=True,not_for_deployment=True)
    (WORK/'build.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report,indent=2),flush=True)

if __name__=='__main__':main()
