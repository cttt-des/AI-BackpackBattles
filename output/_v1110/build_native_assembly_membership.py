"""Build the one changed normal unit; reuse19 verified compatible objects."""
from concurrent.futures import ThreadPoolExecutor
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
from prepare_native_assembly_membership import STAGE,BASE,WORK,ACCEPTED,EXPECTED,sha,archive,inventory,verify_projection

def main():
    p=psutil.Process();p.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS);archive()
    assert sha(BASE/'libgdcore.dll')==EXPECTED and not (WORK/'prototype.dll').exists()
    source=WORK/'prototype_src';verify_projection(source)
    normal=STAGE/'native_perf50/buff_inline_types_prototype'
    old=json.loads((normal/'build.json').read_bytes())['objects_sha256'];assert len(old)==20
    state=json.loads((normal/'live_semantic_build.json').read_bytes())
    roots=[Path(state['object_directory']),Path(state['reused_object_directory'])]
    old_paths={n:next(root/n for root in roots if (root/n).exists() and sha(root/n)==h) for n,h in old.items()}
    baseline=json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    assert baseline==json.loads((normal/'transform.json').read_bytes())['source_sha256']
    changed={f'shard_{i:02}.o' for i in [0]}
    root=Path(tempfile.mkdtemp(prefix='assembly-membership-semantic-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'))
    objects=root/'objects';objects.mkdir();scratch=root/'scratch';scratch.mkdir()
    os.environ.update(TEMP=str(scratch),TMP=str(scratch),TMPDIR=str(scratch));tempfile.tempdir=str(scratch)
    (WORK/'live_semantic_build.json').write_text(json.dumps(dict(pid=p.pid,created=p.create_time(),root=str(root),object_directory=str(objects),reused_objects={n:str(f) for n,f in old_paths.items() if n not in changed}),indent=2)+'\n')
    flags=runpy.run_path(str(source/'build_windows.py'))['COMMON'];compiler='D:/mingw64/bin/g++.exe'
    def compile_one(name):
        with (WORK/('compile_'+Path(name).stem+'.log')).open('wb') as out:
            subprocess.run([compiler,*flags,'-c',str(source/'gen/shards'/(Path(name).stem+'.cpp')),'-o',str(objects/name)],stdout=out,stderr=subprocess.STDOUT,check=True)
    with ThreadPoolExecutor(max_workers=2) as pool:list(pool.map(compile_one,sorted(changed)))
    paths={n:(objects/n if n in changed else old_paths[n]) for n in old}
    with (WORK/'link_first.log').open('wb') as out:
        subprocess.run([compiler,*flags,'-shared','-static','-save-temps=obj','-o',str(objects/'libgdcore.dll'),*[str(paths[n]) for n in old]],stdout=out,stderr=subprocess.STDOUT,check=True)
    assert all(sha(old_paths[n])==h for n,h in old.items())
    shutil.copyfile(objects/'libgdcore.dll',WORK/'prototype.dll')
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    sim=load_simulator(WORK/'prototype.dll');signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    sim.lib.gd_diag_native_resolved_audit.argtypes=[ctypes.c_int];sim.lib.gd_diag_native_resolved_audit(1)
    def counts(name,n):
        f=getattr(sim.lib,name);f.argtypes=[ctypes.c_uint];f.restype=ctypes.c_uint64
        return lambda:[f(i) for i in range(n)]
    counters=[counts(*row) for row in [('gd_diag_native_resolved_stat',6),('gd_diag_native_targeted_timer_stat',10),('gd_diag_native_active_cooldown_stat',10),('gd_diag_native_private_snapshot_stat',4)]]
    before=[f() for f in counters];run=measure(sim,jobs,1,0,continuous=True)
    actual=[[a-b for a,b in zip(f(),v)] for f,v in zip(counters,before)]
    assert actual==[[9599433,100900,54635,200,0,233004],[386704,400,386304,683532,0,0,0,16170,701,0],[386704,1904,384800,3632134,0,760,23435,83822,19040,0],[30901,0,34193,0]],actual
    assert signature.hexdigest()=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert run['matched_original_terminal']==200 and run['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    verify_projection(source);assert sha(BASE/'libgdcore.dll')==EXPECTED
    result=dict(passed=True,dll_sha256=sha(WORK/'prototype.dll'),baseline_dll_sha256=EXPECTED,semantic_only=True,not_for_timing_or_deployment=True,
        changed_normal_units=sorted(changed),reused_objects=19,all_other_source_files_and674_headers_identical=True,
        old_six_counts=actual[0],targeted_timer_counts=actual[1],active_cooldown_counts=actual[2],private_snapshot_counts=actual[3],
        fixed200_inputs_sha256=signature.hexdigest(),fixed200_results_sha256=run['results_sha256'],objects_sha256={n:sha(path) for n,path in paths.items()})
    (WORK/'build.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(result),flush=True)

if __name__=='__main__':main()
