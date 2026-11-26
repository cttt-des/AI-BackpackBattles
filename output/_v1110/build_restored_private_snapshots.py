"""Semantic-only two-consumer build against unchanged current release objects."""
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
from prepare_restored_private_snapshots import STAGE,BASE,ACCEPTED,WORK,EXPECTED,sha,archive,verify_projection

def main():
    p=psutil.Process();p.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS);archive()
    assert not (WORK/'prototype.dll').exists() and sha(BASE/'libgdcore.dll')==EXPECTED
    source=WORK/'prototype_src';proof=verify_projection(source)
    frozen=json.loads((WORK/'transform.json').read_bytes())
    assert frozen['source_sha256']=={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    previous_record=json.loads((ACCEPTED/'release_objects.json').read_bytes());previous=Path(previous_record['object_directory'])
    hashes=previous_record['objects_sha256'];assert len(hashes)==20 and all(sha(previous/name)==digest for name,digest in hashes.items())
    root=Path(tempfile.mkdtemp(prefix='restored-snapshots-semantic-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'))
    objects=root/'objects';objects.mkdir();scratch=root/'scratch';scratch.mkdir()
    os.environ.update(TEMP=str(scratch),TMP=str(scratch),TMPDIR=str(scratch),MAKE='D:/mingw64/bin/mingw32-make.exe');tempfile.tempdir=str(scratch)
    identity=dict(pid=p.pid,created=p.create_time(),object_directory=str(objects),previous_object_directory=str(previous),root=str(root))
    (WORK/'live_semantic_build.json').write_text(json.dumps(identity,indent=2)+'\n',encoding='utf8')
    flags=runpy.run_path(str(source/'build_windows.py'))['COMMON'];compiler='D:/mingw64/bin/g++.exe'
    names=['gd_rt','engine_wrapper','sym_ids','register_all',*[f'shard_{i:02d}' for i in range(16)]];changed={'shard_00','shard_12'}
    with (WORK/'semantic_compile_first.log').open('wb') as log:
        for name in sorted(changed):
            subprocess.run([compiler,*flags,'-c',str(source/'gen/shards'/(name+'.cpp')),'-o',str(objects/(name+'.o'))],stdout=log,stderr=subprocess.STDOUT,check=True)
        subprocess.run([compiler,*flags,'-flto=2',f'-fprofile-use={(previous/"pgo").as_posix()}',
            '-fprofile-partial-training','-fprofile-correction','-save-temps=obj','-shared','-static','-o',str(objects/'libgdcore.dll'),
            *[str((objects if name in changed else previous)/(name+'.o')) for name in names]],stdout=log,stderr=subprocess.STDOUT,check=True)
    assert all(sha(previous/name)==digest for name,digest in hashes.items())
    shutil.copyfile(objects/'libgdcore.dll',WORK/'prototype.dll')
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    sim=load_simulator(WORK/'prototype.dll');signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    sim.lib.gd_diag_native_resolved_audit.argtypes=[ctypes.c_int];sim.lib.gd_diag_native_resolved_audit(1)
    def counter(name,n):
        f=getattr(sim.lib,name);f.argtypes=[ctypes.c_uint];f.restype=ctypes.c_uint64
        return lambda:[f(i) for i in range(n)]
    old=counter('gd_diag_native_resolved_stat',6);timers=counter('gd_diag_native_targeted_timer_stat',10);active=counter('gd_diag_native_active_cooldown_stat',10);private=counter('gd_diag_native_private_snapshot_stat',4)
    before=old();tb=timers();ab=active();pb=private();run=measure(sim,jobs,1,0,continuous=True)
    counts=[x-y for x,y in zip(old(),before)];tc=[x-y for x,y in zip(timers(),tb)];ac=[x-y for x,y in zip(active(),ab)];pc=[x-y for x,y in zip(private(),pb)]
    assert counts==[9599433,100900,54635,200,0,233004]
    assert tc==[386704,400,386304,683532,0,0,0,16170,701,0]
    assert ac==[386704,1904,384800,3632134,0,760,23435,83822,19040,0]
    assert pc[0]>0 and pc[2]>0
    assert signature.hexdigest()=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert run['matched_original_terminal']==200 and run['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    result=dict(passed=True,dll_sha256=sha(WORK/'prototype.dll'),baseline_dll_sha256=EXPECTED,
        semantic_only=True,not_for_timing_or_deployment=True,recompiled_units=2,reused_objects=18,
        exact_consumer_closure_proved=True,original_release_objects_unchanged=True,all_deployed_layouts_retained=True,
        old_six_counts=counts,targeted_timer_counts=tc,active_cooldown_counts=ac,private_snapshot_counts=pc,
        fixed200_inputs_sha256=signature.hexdigest(),fixed200_results_sha256=run['results_sha256'],projection=proof)
    (WORK/'build.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8');print(json.dumps(result,indent=2),flush=True)

if __name__=='__main__':main()
