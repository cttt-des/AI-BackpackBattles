"""Build the changed event consumer; retain all nineteen checked semantic objects."""
import ctypes
import json
from pathlib import Path
import runpy
import shutil
import subprocess
import tempfile
import psutil
from prepare_native_event_capacity import STAGE,BASE,WORK,ACCEPTED,EXPECTED,ARCHIVE,sha

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    source=WORK/'prototype_src';out=WORK/'prototype.dll';assert not out.exists()
    frozen=json.loads((WORK/'transform.json').read_bytes())['source_sha256']
    assert frozen=={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    old=STAGE/'native_perf50/grid_cooldown_prototype'
    before=json.loads((old/'transform.json').read_bytes())['source_sha256']
    assert [n for n in before if before[n]!=frozen[n]]==['gen/shards/shard_11.cpp']
    original=Path((old/'objects.txt').read_text('utf8'));objects=Path(tempfile.mkdtemp(prefix='native-event-capacity-'))
    (WORK/'objects.txt').write_text(str(objects),encoding='utf8')
    names=['gd_rt','engine_wrapper','sym_ids','register_all',*[f'shard_{i:02d}' for i in range(16)]]
    hashes={n:sha(original/(n+'.o')) for n in names}
    for n in names:
        if n!='shard_11':shutil.copyfile(original/(n+'.o'),objects/(n+'.o'))
    flags=runpy.run_path(str(source/'build_windows.py'))['COMMON'];compiler='D:/mingw64/bin/g++.exe'
    subprocess.run([compiler,*flags,'-c',str(source/'gen/shards/shard_11.cpp'),'-o',str(objects/'shard_11.o')],check=True)
    subprocess.run([compiler,*flags,'-shared','-static','-o',str(objects/'libgdcore.dll'),*[str(objects/(n+'.o')) for n in names]],check=True)
    assert hashes=={n:sha(original/(n+'.o')) for n in names}
    assert all(sha(objects/(n+'.o'))==hashes[n] for n in names if n!='shard_11')
    shutil.copyfile(objects/'libgdcore.dll',out)
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    import hashlib
    sim=load_simulator(out);signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    audit=sim.lib.gd_diag_native_resolved_audit;audit.argtypes=[ctypes.c_int];audit.restype=None;audit(1)
    stat=sim.lib.gd_diag_native_resolved_stat;stat.argtypes=[ctypes.c_uint];stat.restype=ctypes.c_uint64
    start=[stat(i) for i in range(6)];result=measure(sim,jobs,1,0,continuous=True)
    fields=('generic_hits','funcref_hits','lazy_resolutions','unsupported_types','audit_mismatch','selected_fallback')
    counts=dict(zip(fields,[stat(i)-start[i] for i in range(6)]))
    reference=json.loads((STAGE/'native_perf50_event_bus_serial.json').read_bytes())
    assert signature.hexdigest()==reference['inputs_sha256'] and result['results_sha256']==reference['results_sha256'] and result['matched_original_terminal']==200
    assert counts==json.loads((ACCEPTED/'release_audit.json').read_bytes())['coverage']
    report=dict(passed=True,semantic_only=True,dll_sha256=sha(out),baseline_dll_sha256=EXPECTED,
        verified_remote_backup=ARCHIVE,source_manifest_sha256=sha(WORK/'transform.json'),
        reused_objects=19,recompiled_units=1,original_objects_unchanged=True,original_six_counters=counts,
        inputs_sha256=signature.hexdigest(),results_sha256=result['results_sha256'],matched_original_terminal=200,
        no_throughput_claim=True,not_for_deployment=True)
    (WORK/'build.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report,indent=2))

if __name__=='__main__':main()
