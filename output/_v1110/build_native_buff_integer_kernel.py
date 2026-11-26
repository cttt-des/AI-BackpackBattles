"""Build one changed semantic TU with19 byte/source-compatible normal objects."""
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
from prepare_native_buff_integer_kernel import STAGE,BASE,WORK,ACCEPTED,EXPECTED,sha,archive,inventory,verify_projection
NORMAL=STAGE/'native_perf50/container_builtins_prototype'
def main():
    p=psutil.Process();p.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS);archive()
    assert sha(BASE/'libgdcore.dll')==EXPECTED and not (WORK/'prototype.dll').exists()
    source=WORK/'prototype_src';verify_projection(source)
    previous=Path(json.loads((NORMAL/'live_semantic_build.json').read_bytes())['object_directory'])
    old=json.loads((NORMAL/'build.json').read_bytes())['objects_sha256'];assert len(old)==20
    baseline=json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    assert baseline==json.loads((NORMAL/'transform.json').read_bytes())['source_sha256']
    assert all(sha(previous/n)==v for n,v in old.items())
    root=Path(tempfile.mkdtemp(prefix='buff-integer-semantic-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'))
    objects=root/'objects';objects.mkdir();scratch=root/'scratch';scratch.mkdir()
    os.environ.update(TEMP=str(scratch),TMP=str(scratch),TMPDIR=str(scratch));tempfile.tempdir=str(scratch)
    (WORK/'live_semantic_build.json').write_text(json.dumps(dict(pid=p.pid,created=p.create_time(),root=str(root),object_directory=str(objects),reused_object_directory=str(previous)),indent=2)+'\n',encoding='utf8')
    flags=runpy.run_path(str(source/'build_windows.py'))['COMMON'];compiler='D:/mingw64/bin/g++.exe'
    with (WORK/'compile_first.log').open('wb') as output:
        subprocess.run([compiler,*flags,'-c',str(source/'gen/shards/shard_00.cpp'),'-o',str(objects/'shard_00.o')],stdout=output,stderr=subprocess.STDOUT,check=True)
        subprocess.run([compiler,*flags,'-shared','-static','-save-temps=obj','-o',str(objects/'libgdcore.dll'),
            *[str((objects if n=='shard_00.o' else previous)/n) for n in old]],stdout=output,stderr=subprocess.STDOUT,check=True)
    assert all(sha(previous/n)==v for n,v in old.items());shutil.copyfile(objects/'libgdcore.dll',WORK/'prototype.dll')
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    sim=load_simulator(WORK/'prototype.dll');signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    sim.lib.gd_diag_native_resolved_audit.argtypes=[ctypes.c_int];sim.lib.gd_diag_native_resolved_audit(1)
    def counts(name,n):
        f=getattr(sim.lib,name);f.argtypes=[ctypes.c_uint];f.restype=ctypes.c_uint64
        return lambda:[f(i) for i in range(n)]
    counters=[counts(*row) for row in [('gd_diag_native_resolved_stat',6),('gd_diag_native_targeted_timer_stat',10),
        ('gd_diag_native_active_cooldown_stat',10),('gd_diag_native_private_snapshot_stat',4)]]
    before=[f() for f in counters];run=measure(sim,jobs,1,0,continuous=True)
    actual=[[a-b for a,b in zip(f(),v)] for f,v in zip(counters,before)]
    assert actual==[[9599433,100900,54635,200,0,233004],[386704,400,386304,683532,0,0,0,16170,701,0],
        [386704,1904,384800,3632134,0,760,23435,83822,19040,0],[30901,0,34193,0]]
    assert signature.hexdigest()=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert run['matched_original_terminal']==200 and run['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    verify_projection(source);assert sha(BASE/'libgdcore.dll')==EXPECTED
    report=dict(passed=True,dll_sha256=sha(WORK/'prototype.dll'),baseline_dll_sha256=EXPECTED,
        semantic_only=True,not_for_timing_or_deployment=True,one_changed_cpp_normal_object=True,
        reused_objects=19,source_compatibility_all_other712_files_and674_headers_verified=True,no_pgo_used=True,
        old_six_counts=actual[0],targeted_timer_counts=actual[1],active_cooldown_counts=actual[2],private_snapshot_counts=actual[3],
        fixed200_inputs_sha256=signature.hexdigest(),fixed200_results_sha256=run['results_sha256'],
        objects_sha256={n:sha((objects if n=='shard_00.o' else previous)/n) for n in old})
    (WORK/'build.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report),flush=True)
if __name__=='__main__':main()
