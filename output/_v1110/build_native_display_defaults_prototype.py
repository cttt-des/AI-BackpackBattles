"""Rebuild the three display consumers on verified ABI-identical native objects."""
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
from prepare_native_display_defaults import STAGE,BASE,WORK,ACCEPTED,EXPECTED,ARCHIVE,sha

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    src=WORK/'prototype_src';out=WORK/'prototype.dll';assert not out.exists()
    frozen=json.loads((WORK/'transform.json').read_bytes())['source_sha256']
    assert frozen=={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    old=STAGE/'native_perf50/grid_cooldown_prototype'
    before=json.loads((old/'transform.json').read_bytes())['source_sha256']
    assert sorted(n for n in before if before[n]!=frozen[n])==['engine_wrapper.cpp','gen/shards/shard_00.cpp','native_active_cooldowns.hpp','native_inline_dispatch.hpp']
    original=Path((old/'objects.txt').read_text('utf8'));objects=Path(tempfile.mkdtemp(prefix='native-display-defaults-'))
    (WORK/'objects.txt').write_text(str(objects),encoding='utf8')
    names=['gd_rt','engine_wrapper','sym_ids','register_all',*[f'shard_{i:02d}' for i in range(16)]]
    changed={'engine_wrapper':src/'engine_wrapper.cpp','shard_00':src/'gen/shards/shard_00.cpp','shard_03':src/'gen/shards/shard_03.cpp'}
    hashes={n:sha(original/(n+'.o')) for n in names}
    uses=[]
    for n in names:
        symbols=subprocess.check_output(['D:/mingw64/bin/nm.exe','-C',str(original/(n+'.o'))],text=True)
        if 'native_frame_segment_tick(' in symbols:uses.append(n)
        if n not in changed:shutil.copyfile(original/(n+'.o'),objects/(n+'.o'))
    assert set(uses).issubset(changed),uses
    flags=runpy.run_path(str(src/'build_windows.py'))['COMMON'];assert not any('lto' in f for f in flags)
    compiler='D:/mingw64/bin/g++.exe'
    def compile_one(row):
        n,p=row
        with (WORK/(n+'_compile_first.log')).open('wb') as log:
            subprocess.run([compiler,*flags,'-c',str(p),'-o',str(objects/(n+'.o'))],check=True,stdout=log,stderr=subprocess.STDOUT)
    with ThreadPoolExecutor(max_workers=2) as pool:list(pool.map(compile_one,changed.items()))
    with (WORK/'link_first.log').open('wb') as log:
        subprocess.run([compiler,*flags,'-shared','-static','-o',str(objects/'libgdcore.dll'),*[str(objects/(n+'.o')) for n in names]],check=True,stdout=log,stderr=subprocess.STDOUT)
    assert hashes=={n:sha(original/(n+'.o')) for n in names}
    assert all(sha(objects/(n+'.o'))==hashes[n] for n in names if n not in changed)
    shutil.copyfile(objects/'libgdcore.dll',out)
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    sim=load_simulator(out);signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    audit=sim.lib.gd_diag_native_resolved_audit;audit.argtypes=[ctypes.c_int];audit.restype=None;audit(1)
    funcs=[]
    for symbol,count in [('gd_diag_native_resolved_stat',6),('gd_diag_native_display_defaults_stat',8),('gd_diag_native_active_cooldown_stat',10),('gd_diag_native_targeted_timer_stat',10)]:
        fn=getattr(sim.lib,symbol);fn.argtypes=[ctypes.c_uint];fn.restype=ctypes.c_uint64
        funcs.append((fn,count,[fn(i) for i in range(count)]))
    result=measure(sim,jobs,1,0,continuous=True)
    counts=[[fn(i)-initial[i] for i in range(n)] for fn,n,initial in funcs]
    fields=('generic_hits','funcref_hits','lazy_resolutions','unsupported_types','audit_mismatch','selected_fallback')
    old_counts=dict(zip(fields,counts[0]));assert old_counts==json.loads((ACCEPTED/'release_audit.json').read_bytes())['coverage']
    ref=json.loads((STAGE/'native_perf50_event_bus_serial.json').read_bytes())
    assert signature.hexdigest()==ref['inputs_sha256'] and result['results_sha256']==ref['results_sha256'] and result['matched_original_terminal']==200
    assert counts[1][0]==counts[1][1]==200 and counts[1][3]>0 and counts[1][4]>0
    report=dict(passed=True,semantic_only=True,dll_sha256=sha(out),baseline_dll_sha256=EXPECTED,
        verified_remote_backup=ARCHIVE,source_manifest_sha256=sha(WORK/'transform.json'),
        reused_objects=17,recompiled_units=3,original_objects_unchanged=True,frame_symbol_consumers=uses,
        original_six_counters=old_counts,display_counts=counts[1],active_cooldown_counts=counts[2],targeted_timer_counts=counts[3],
        inputs_sha256=signature.hexdigest(),results_sha256=result['results_sha256'],matched_original_terminal=200,
        no_throughput_claim=True,not_for_deployment=True)
    (WORK/'build.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report,indent=2))

if __name__=='__main__':main()
