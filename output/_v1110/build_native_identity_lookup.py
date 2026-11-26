"""Full20 semantic-only normal-object build; formal timing requires freshPGO."""
import ctypes
import hashlib
import json
import os
from pathlib import Path
import shutil
import tempfile
import psutil
from prepare_native_identity_lookup import STAGE,BASE,WORK,EXPECTED,sha,archive,inventory,verify_projection

def main():
    p=psutil.Process();p.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS);archive()
    assert sha(BASE/'libgdcore.dll')==EXPECTED and not (WORK/'prototype.dll').exists()
    source=WORK/'prototype_src';verify_projection(source)
    root=Path(tempfile.mkdtemp(prefix='identity-lookup-semantic-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'))
    objects=root/'objects';objects.mkdir();scratch=root/'scratch';scratch.mkdir()
    os.environ.update(NATIVE_SIM_CXX='D:/mingw64/bin/g++.exe',NATIVE_SIM_OBJ=str(objects),
        TEMP=str(scratch),TMP=str(scratch),TMPDIR=str(scratch),MAKE='D:/mingw64/bin/mingw32-make.exe')
    tempfile.tempdir=str(scratch)
    (WORK/'live_semantic_build.json').write_text(json.dumps(dict(pid=p.pid,created=p.create_time(),
        root=str(root),object_directory=str(objects)),indent=2)+'\n',encoding='utf8')
    from build_native_hot_lto import build_dll
    # No old objects or profiles: this DLL is only a semantic integration probe.
    dll=build_dll(source,objects/'semantic.dll',2,hot_units=frozenset(),link_flags=('-save-temps=obj',))
    names=['gd_rt','engine_wrapper','sym_ids','register_all',*[f'shard_{i:02d}' for i in range(16)]]
    assert all((objects/(name+'.o')).is_file() for name in names)
    shutil.copyfile(dll,WORK/'prototype.dll')
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    sim=load_simulator(WORK/'prototype.dll');signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    sim.lib.gd_diag_native_resolved_audit.argtypes=[ctypes.c_int];sim.lib.gd_diag_native_resolved_audit(1)
    def counts(name,n):
        f=getattr(sim.lib,name);f.argtypes=[ctypes.c_uint];f.restype=ctypes.c_uint64
        return lambda:[f(i) for i in range(n)]
    counters=[counts(*row) for row in [('gd_diag_native_resolved_stat',6),('gd_diag_native_targeted_timer_stat',10),
        ('gd_diag_native_active_cooldown_stat',10),('gd_diag_native_private_snapshot_stat',4)]]
    before=[f() for f in counters];run=measure(sim,jobs,1,0,continuous=True)
    actual=[[a-b for a,b in zip(f(),old)] for f,old in zip(counters,before)]
    expected=[[9599433,100900,54635,200,0,233004],[386704,400,386304,683532,0,0,0,16170,701,0],
        [386704,1904,384800,3632134,0,760,23435,83822,19040,0],[30901,0,34193,0]]
    assert actual==expected,actual
    assert signature.hexdigest()=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert run['matched_original_terminal']==200 and run['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    verify_projection(source);assert sha(BASE/'libgdcore.dll')==EXPECTED
    result=dict(passed=True,dll_sha256=sha(WORK/'prototype.dll'),baseline_dll_sha256=EXPECTED,
        semantic_only=True,not_for_timing_or_deployment=True,full20_normal_objects=True,reused_objects=0,no_pgo_used=True,
        old_six_counts=actual[0],targeted_timer_counts=actual[1],active_cooldown_counts=actual[2],private_snapshot_counts=actual[3],
        fixed200_inputs_sha256=signature.hexdigest(),fixed200_results_sha256=run['results_sha256'],
        objects_sha256={name+'.o':sha(objects/(name+'.o')) for name in names})
    (WORK/'build.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8');print(json.dumps(result),flush=True)

if __name__=='__main__':main()
