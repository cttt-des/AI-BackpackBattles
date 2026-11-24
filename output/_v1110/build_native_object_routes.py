"""Build only the changed semantic unit; use fresh full PGO for any speed trial."""
import ctypes
import hashlib
import json
from pathlib import Path
import runpy
import shutil
import subprocess
import tempfile
import psutil
from prepare_native_object_routes import STAGE,BASE,WORK,ACCEPTED,EXPECTED,sha

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    source=WORK/'prototype_src';out=WORK/'prototype.dll';assert not out.exists()
    frozen=json.loads((WORK/'transform.json').read_bytes())['source_sha256']
    assert frozen=={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    old=STAGE/'native_perf50/callback_dispatch_prototype'
    assert json.loads((old/'transform.json').read_bytes())['source_sha256']==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    previous=Path((old/'objects.txt').read_text('utf8'))
    objects=Path(tempfile.mkdtemp(prefix='native-object-routes-semantic-'))
    (WORK/'semantic_objects.txt').write_text(str(objects),encoding='utf8')
    p=psutil.Process();(WORK/'live_semantic_build.json').write_text(json.dumps(dict(pid=p.pid,created=p.create_time(),script=str(Path(__file__).resolve())))+'\n',encoding='utf8')
    names=['gd_rt','engine_wrapper','sym_ids','register_all',*[f'shard_{i:02d}' for i in range(16)]]
    before={n:sha(previous/(n+'.o')) for n in names}
    for name in names:
        if name!='gd_rt':shutil.copyfile(previous/(name+'.o'),objects/(name+'.o'))
    flags=runpy.run_path(str(source/'build_windows.py'))['COMMON'];compiler='D:/mingw64/bin/g++.exe'
    with (WORK/'semantic_compile_first.log').open('wb') as log:
        subprocess.run([compiler,*flags,'-c',str(source/'gd_rt.cpp'),'-o',str(objects/'gd_rt.o')],stdout=log,stderr=subprocess.STDOUT,check=True)
        subprocess.run([compiler,*flags,'-shared','-static','-o',str(objects/'libgdcore.dll'),
            *[str(objects/(name+'.o')) for name in names]],stdout=log,stderr=subprocess.STDOUT,check=True)
    assert before=={n:sha(previous/(n+'.o')) for n in names}
    shutil.copyfile(objects/'libgdcore.dll',out)
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    sim=load_simulator(out);signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    audit=sim.lib.gd_diag_native_resolved_audit;audit.argtypes=[ctypes.c_int];audit.restype=None;audit(1)
    stat=sim.lib.gd_diag_native_resolved_stat;stat.argtypes=[ctypes.c_uint];stat.restype=ctypes.c_uint64
    extra=sim.lib.gd_diag_native_object_route_stat;extra.argtypes=[ctypes.c_uint];extra.restype=ctypes.c_uint64
    before=[stat(i) for i in range(6)];route_before=[extra(i) for i in range(2)]
    run=measure(sim,jobs,1,0,continuous=True)
    counts=[stat(i)-before[i] for i in range(6)];routes=[extra(i)-route_before[i] for i in range(2)]
    assert counts==[9599433,100900,54635,200,0,233004],counts
    assert routes==[901392,88491],routes
    assert signature.hexdigest()=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert run['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    assert run['matched_original_terminal']==200 and sha(BASE/'libgdcore.dll')==EXPECTED
    report=dict(passed=True,semantic_only=True,dll_sha256=sha(out),baseline_dll_sha256=EXPECTED,
        source_manifest_sha256=sha(WORK/'transform.json'),reused_objects=19,recompiled_units=1,
        unchanged_object_layout_and_original_call_bodies=True,previous_objects_unchanged=True,
        old_six_counters=counts,route_counts=dict(instance_methods=routes[0],static_context_f32=routes[1]),
        inputs_sha256=signature.hexdigest(),results_sha256=run['results_sha256'],matched_original_terminal=200,
        no_throughput_claim=True,not_for_deployment=True)
    (WORK/'build.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report,indent=2))

if __name__=='__main__':main()
