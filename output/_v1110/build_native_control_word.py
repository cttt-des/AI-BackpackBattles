"""Build the sole changed consumer for semantic checks, not a speed trial."""
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
from prepare_native_control_word import STAGE,BASE,ACCEPTED,WORK,EXPECTED,sha

def main():
    process=psutil.Process();process.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert not (WORK/'prototype.dll').exists()
    source=WORK/'prototype_src';frozen=json.loads((WORK/'transform.json').read_bytes())['source_sha256']
    assert frozen=={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    root=Path(tempfile.mkdtemp(prefix='control-word-semantic-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'))
    objects=root/'objects';objects.mkdir();scratch=root/'scratch';scratch.mkdir()
    os.environ.update(TEMP=str(scratch),TMP=str(scratch),TMPDIR=str(scratch),MAKE='D:/mingw64/bin/mingw32-make.exe');tempfile.tempdir=str(scratch)
    (WORK/'semantic_objects.txt').write_text(str(objects),encoding='utf8')
    (WORK/'live_semantic_build.json').write_text(json.dumps(dict(pid=process.pid,created=process.create_time(),script=str(Path(__file__).resolve()),root=str(root)))+'\n',encoding='utf8')
    previous=Path(json.loads((ACCEPTED/'live_recovered_build.json').read_bytes())['object_directory'])
    hashes=json.loads((ACCEPTED/'recovered_release_objects.json').read_bytes())['objects_sha256']
    assert hashes=={n:sha(previous/(n+'.o')) for n in hashes}
    names=['gd_rt','engine_wrapper','sym_ids','register_all',*[f'shard_{i:02d}' for i in range(16)]]
    flags=runpy.run_path(str(source/'build_windows.py'))['COMMON'];compiler='D:/mingw64/bin/g++.exe'
    with (WORK/'semantic_compile_first.log').open('wb') as log:
        subprocess.run([compiler,*flags,'-c',str(source/'gen/shards/shard_03.cpp'),'-o',str(objects/'shard_03.o')],stdout=log,stderr=subprocess.STDOUT,check=True)
        subprocess.run([compiler,*flags,'-flto=2',f'-fprofile-use={(previous/"pgo").as_posix()}',
            '-fprofile-partial-training','-fprofile-correction','-save-temps=obj','-shared','-static','-o',str(objects/'libgdcore.dll'),
            *[str((objects if n=='shard_03' else previous)/(n+'.o')) for n in names]],stdout=log,stderr=subprocess.STDOUT,check=True)
    assert hashes=={n:sha(previous/(n+'.o')) for n in names}
    out=WORK/'prototype.dll';shutil.copyfile(objects/'libgdcore.dll',out)
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    sim=load_simulator(out);signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    sim.lib.gd_diag_native_resolved_audit.argtypes=[ctypes.c_int];sim.lib.gd_diag_native_resolved_audit(1)
    def counters(name,count):
        fn=getattr(sim.lib,name);fn.argtypes=[ctypes.c_uint];fn.restype=ctypes.c_uint64
        return lambda:[fn(i) for i in range(count)]
    old=counters('gd_diag_native_resolved_stat',6);timers=counters('gd_diag_native_targeted_timer_stat',10)
    active=counters('gd_diag_native_active_cooldown_stat',10)
    before=old();timer_before=timers();active_before=active();run=measure(sim,jobs,1,0,continuous=True)
    counts=[a-b for a,b in zip(old(),before)];timer_counts=[a-b for a,b in zip(timers(),timer_before)];active_counts=[a-b for a,b in zip(active(),active_before)]
    assert counts==[9599433,100900,54635,200,0,233004],counts
    assert timer_counts==[386704,400,386304,683532,0,0,0,16170,701,0],timer_counts
    assert active_counts==[386704,1904,384800,3632134,0,760,23435,83822,19040,0],active_counts
    assert signature.hexdigest()=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert run['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9' and run['matched_original_terminal']==200
    report=dict(passed=True,semantic_only=True,no_throughput_claim=True,not_for_deployment=True,
        baseline_dll_sha256=EXPECTED,dll_sha256=sha(out),old_six_counters=counts,active_cooldown_counts=active_counts,
        targeted_timer_counts=timer_counts,
        source_manifest_sha256=sha(WORK/'transform.json'),recompiled_units=1,reused_objects=19,
        sole_consumer_source_proved=True,public_object_layouts_unchanged=True,previous_objects_unchanged=True,
        inputs_sha256=signature.hexdigest(),results_sha256=run['results_sha256'],matched_original_terminal=200)
    (WORK/'build.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    print(json.dumps(report,indent=2),flush=True)

if __name__=='__main__':main()
