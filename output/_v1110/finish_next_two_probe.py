"""Relink diagnostic exports explicitly, reusing the already compiled probe object."""
import ctypes,hashlib,json,runpy,subprocess
from pathlib import Path
from probe_next_two import WORK,ACCEPTED,BASE,sha,boundary

def main():
    boundary();root=Path('C:/Users/Windows/AppData/Local/CodexNativeBuilds/next-two-probe-14nqltrl')
    old=json.loads((ACCEPTED/'prototype_build.json').read_bytes())['objects_sha256'];live=json.loads((ACCEPTED/'live_semantic_build.json').read_bytes())
    paths={n:Path(live['reused_objects'].get(n,str(Path(live['object_directory'])/n))) for n in old}
    assert all(sha(paths[n])==h for n,h in old.items());paths['gd_rt.o']=root/'objects/gd_rt.o'
    flags=runpy.run_path(str(root/'source/build_windows.py'))['COMMON'];dll=root/'objects/probe_exports.dll'
    with (WORK/'shape_probe_relink.log').open('wb') as log:subprocess.run(['D:/mingw64/bin/g++.exe',*flags,'-shared','-static','-Wl,--export-all-symbols','-o',str(dll),*map(str,paths.values())],stdout=log,stderr=subprocess.STDOUT,check=True)
    from bench_native_corpus import load_simulator,prepare,select_cases,measure
    sim=load_simulator(dll);counts=(ctypes.c_uint64*256).in_dll(ctypes.CDLL(str(dll)),'next_two_probe_counts')
    inputs=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),inputs));result=measure(sim,jobs,1,0,continuous=True)
    assert result['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    report=dict(diagnostic_only=True,no_speed_claim=True,baseline_dll_sha256=sha(BASE/'libgdcore.dll'),root=str(root),counts=list(counts),inputs_sha256=inputs.hexdigest(),results_sha256=result['results_sha256'])
    (WORK/'shape_probe.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');boundary();print(json.dumps(report),flush=True)
if __name__=='__main__':main()
