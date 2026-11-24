"""Build a semantic DLL, after the identified count-only build has finished."""
import ctypes
import hashlib
import json
import os
from pathlib import Path
import runpy
import shutil
import subprocess
import tempfile
import psutil
from prepare_native_private_snapshots import STAGE,BASE,ACCEPTED,WORK,EXPECTED,sha

def save(name,value):(WORK/name).write_text(json.dumps(value,indent=2)+'\n',encoding='utf8')

def main():
    process=psutil.Process();process.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert not (WORK/'prototype.dll').exists()
    save('live_semantic_build.json',dict(pid=process.pid,created=process.create_time(),script=str(Path(__file__).resolve())))
    count_work=STAGE/'native_perf50/event_identity_snapshot_prototype'
    r=json.loads((count_work/'live_probe.json').read_bytes())
    try:
        p=psutil.Process(r['pid'])
        if p.create_time()==r['created']:p.wait()
    except psutil.NoSuchProcess:pass
    assert json.loads((count_work/'identity_probe.json').read_bytes())['passed']
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    source=WORK/'prototype_src'
    frozen=json.loads((WORK/'transform.json').read_bytes())['source_sha256']
    assert frozen=={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    cache=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'
    root=Path(tempfile.mkdtemp(prefix='private-snapshot-semantic-',dir=cache));objects=root/'objects';objects.mkdir();scratch=root/'scratch';scratch.mkdir()
    os.environ.update(TEMP=str(scratch),TMP=str(scratch),TMPDIR=str(scratch),MAKE='D:/mingw64/bin/mingw32-make.exe');tempfile.tempdir=str(scratch)
    (WORK/'semantic_objects.txt').write_text(str(objects),encoding='utf8')
    previous=Path(json.loads((ACCEPTED/'live_recovered_build.json').read_bytes())['object_directory'])
    hashes=json.loads((ACCEPTED/'recovered_release_objects.json').read_bytes())['objects_sha256']
    assert hashes=={n:sha(previous/(n+'.o')) for n in hashes}
    names=['gd_rt','engine_wrapper','sym_ids','register_all',*[f'shard_{i:02d}' for i in range(16)]]
    changed={'shard_00','shard_12'};compiler='D:/mingw64/bin/g++.exe'
    flags=runpy.run_path(str(source/'build_windows.py'))['COMMON']
    with (WORK/'semantic_compile_first.log').open('wb') as log:
        for name in sorted(changed):
            subprocess.run([compiler,*flags,'-c',str(source/'gen/shards'/(name+'.cpp')),'-o',str(objects/(name+'.o'))],stdout=log,stderr=subprocess.STDOUT,check=True)
        subprocess.run([compiler,*flags,'-flto=2',f'-fprofile-use={(previous/"pgo").as_posix()}',
            '-fprofile-partial-training','-fprofile-correction','-save-temps=obj','-shared','-static','-o',str(objects/'prototype.dll'),
            *[str((objects if name in changed else previous)/(name+'.o')) for name in names]],stdout=log,stderr=subprocess.STDOUT,check=True)
    assert hashes=={n:sha(previous/(n+'.o')) for n in names}
    out=WORK/'prototype.dll';shutil.copyfile(objects/'prototype.dll',out)
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    sim=load_simulator(out);signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    sim.lib.gd_diag_native_resolved_audit.argtypes=[ctypes.c_int];sim.lib.gd_diag_native_resolved_audit(1)
    def counters(name,n):
        f=getattr(sim.lib,name);f.argtypes=[ctypes.c_uint];f.restype=ctypes.c_uint64
        return lambda:[f(i) for i in range(n)]
    old=counters('gd_diag_native_resolved_stat',6);extra=counters('gd_diag_native_private_snapshot_stat',4)
    routes=counters('gd_diag_native_object_route_stat',2)
    before=old();extra_before=extra();route_before=routes();run=measure(sim,jobs,1,0,continuous=True)
    counts=[a-b for a,b in zip(old(),before)];new=[a-b for a,b in zip(extra(),extra_before)];route=[a-b for a,b in zip(routes(),route_before)]
    assert counts==[9599433,100900,54635,200,0,233004],counts
    assert route==[901392,88491],route
    assert new[0]==30901 and new[1]==0 and new[2]>0,new
    assert signature.hexdigest()=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert run['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9' and run['matched_original_terminal']==200
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    save('build.json',dict(passed=True,semantic_only=True,not_for_deployment=True,no_throughput_claim=True,
        baseline_dll_sha256=EXPECTED,dll_sha256=sha(out),recompiled_units=2,reused_objects=18,
        old_six_counters=counts,object_route_counts=route,new_counts=dict(zip(('private_integer','private_fallback','identity_snapshot','identity_eager'),new)),
        matched_original_terminal=200,results_sha256=run['results_sha256'],inputs_sha256=signature.hexdigest(),
        source_manifest_sha256=sha(WORK/'transform.json'),previous_objects_unchanged=True))
    print((WORK/'build.json').read_text('utf8'),flush=True)

if __name__=='__main__':main()
