"""Compile just the new cooldown consumer on top of the checked grid semantic DLL."""
import ctypes
import hashlib
import json
from pathlib import Path
import runpy
import shutil
import subprocess
import tempfile
import psutil
from prepare_native_grid_cooldown import STAGE,BASE,WORK,GRID,EXPECTED,ARCHIVE,sha

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    out=WORK/'prototype.dll';assert not out.exists();source=WORK/'prototype_src'
    frozen=json.loads((WORK/'transform.json').read_bytes())['source_sha256']
    assert frozen=={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    before=json.loads((GRID/'transform.json').read_bytes())['source_sha256']
    assert [n for n in before if before[n]!=frozen[n]]==['native_active_cooldowns.hpp']
    original=Path((GRID/'objects.txt').read_text('utf8'));objects=Path(tempfile.mkdtemp(prefix='native-grid-cooldown-prototype-'))
    (WORK/'objects.txt').write_text(str(objects),encoding='utf8')
    names=['gd_rt','engine_wrapper','sym_ids','register_all',*[f'shard_{i:02d}' for i in range(16)]]
    hashes={n:sha(original/(n+'.o')) for n in names}
    for n in names:
        if n!='shard_03':shutil.copyfile(original/(n+'.o'),objects/(n+'.o'))
    flags=runpy.run_path(str(source/'build_windows.py'))['COMMON'];compiler='D:/mingw64/bin/g++.exe'
    subprocess.run([compiler,*flags,'-c',str(source/'gen/shards/shard_03.cpp'),'-o',str(objects/'shard_03.o')],check=True)
    subprocess.run([compiler,*flags,'-shared','-static','-o',str(objects/'libgdcore.dll'),*[str(objects/(n+'.o')) for n in names]],check=True)
    assert hashes=={n:sha(original/(n+'.o')) for n in names};shutil.copyfile(objects/'libgdcore.dll',out)
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    sim=load_simulator(out);signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    audit=sim.lib.gd_diag_native_resolved_audit;audit.argtypes=[ctypes.c_int];audit.restype=None;audit(1)
    funcs=[]
    for name,n in [('gd_diag_native_integer_grid_stat',6),('gd_diag_native_active_cooldown_stat',10),('gd_diag_native_targeted_timer_stat',10),('gd_diag_native_resolved_stat',6)]:
        fn=getattr(sim.lib,name);fn.argtypes=[ctypes.c_uint];fn.restype=ctypes.c_uint64;funcs.append((fn,n,[fn(i) for i in range(n)]))
    result=measure(sim,jobs,1,0,continuous=True)
    counts=[[fn(i)-old[i] for i in range(n)] for fn,n,old in funcs]
    ref=json.loads((STAGE/'native_perf50_event_bus_serial.json').read_bytes())
    assert signature.hexdigest()==ref['inputs_sha256'] and result['results_sha256']==ref['results_sha256'] and result['matched_original_terminal']==200
    old_counts=dict(zip(('generic_hits','funcref_hits','lazy_resolutions','unsupported_types','audit_mismatch','selected_fallback'),counts[3]))
    assert old_counts==json.loads((STAGE/'native_perf50/active_cooldown_bundle/release_audit.json').read_bytes())['coverage']
    assert counts[0][0]==652011 and counts[0][1]==counts[0][4]==0
    assert counts[1][:6]==[386704,1904,384800,3632134,0,760]
    assert counts[2][1:3]==[400,386304]
    report=dict(passed=True,semantic_only=True,dll_sha256=sha(out),baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,
        source_manifest_sha256=sha(WORK/'transform.json'),reused_grid_objects=19,recompiled_units=1,
        counts=dict(grid=counts[0],cooldown=counts[1],timer=counts[2]),original_six_counters=old_counts,
        inputs_sha256=signature.hexdigest(),results_sha256=result['results_sha256'],matched_original_terminal=200,
        no_throughput_claim=True,not_for_deployment=True)
    (WORK/'build.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report,indent=2))

if __name__=='__main__':main()
