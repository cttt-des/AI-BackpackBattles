"""Compare actual old/new DLL arrays, aliases, setup and FP state case by case."""
import ctypes
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import psutil
from prepare_native_buff_integer_kernel import STAGE,BASE,WORK,ACCEPTED,EXPECTED,sha,verify_projection

def verify(source,dll,out):
    assert not out.exists()
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    projection=verify_projection(source)
    checks=out.parent/(out.stem+'_checks');assert not checks.exists();checks.mkdir()
    root=Path(tempfile.mkdtemp(prefix='display-storage-check-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'))
    scratch=root/'scratch';scratch.mkdir();env=dict(os.environ,TEMP=str(scratch),TMP=str(scratch),TMPDIR=str(scratch))
    fixture=STAGE/'test_native_display_storage.cpp';reports={}
    for name,headers,library,flags in [('baseline',ACCEPTED/'bundle_src',ACCEPTED/'bundle.dll',[]),
            ('candidate',source,dll,['-DGD_DISPLAY_CANDIDATE'])]:
        local=root/name;local.mkdir();shutil.copyfile(library,local/'libgdcore.dll');shutil.copyfile(fixture,local/'fixture.cpp')
        exe=local/'verify.exe'
        with (checks/(name+'_compile.log')).open('wb') as log:
            subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O3','-std=c++20','-march=native','-ffp-contract=off',
                *flags,'-I',str(headers),str(local/'fixture.cpp'),str(local/'libgdcore.dll'),'-o',str(exe)],
                stdout=log,stderr=subprocess.STDOUT,env=env,check=True)
        result=subprocess.run([str(exe)],capture_output=True,env=env)
        (checks/(name+'_cases.json')).write_bytes(result.stdout)
        (checks/(name+'_execution.log')).write_bytes(result.stderr)
        result.check_returncode();reports[name]=json.loads(result.stdout)
        assert reports[name]['passed'] and reports[name]['cases']==21888
        print(name,'cases',reports[name]['cases'],'CoreItem',reports[name]['core_item_bytes'],flush=True)
    a,b=reports['baseline'],reports['candidate']
    assert a['case_hashes']==b['case_hashes'],[(i,x,y) for i,(x,y) in enumerate(zip(a['case_hashes'],b['case_hashes'])) if x!=y][:12]
    assert a['core_item_bytes']==b['core_item_bytes']==2112
    assert all(a[n]==b[n]==v for n,v in [('gdval_bytes',24),('gdarr_bytes',32),('context_bytes',328),('watch_bytes',64)])
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    sim=load_simulator(dll);signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    sim.lib.gd_diag_native_resolved_audit.argtypes=[ctypes.c_int];sim.lib.gd_diag_native_resolved_audit(1)
    def counter(name,n):
        f=getattr(sim.lib,name);f.argtypes=[ctypes.c_uint];f.restype=ctypes.c_uint64
        return lambda:[f(i) for i in range(n)]
    old=counter('gd_diag_native_resolved_stat',6);timers=counter('gd_diag_native_targeted_timer_stat',10);active=counter('gd_diag_native_active_cooldown_stat',10)
    before=old();tb=timers();ab=active();run=measure(sim,jobs,1,0,continuous=True)
    counts=[x-y for x,y in zip(old(),before)];tc=[x-y for x,y in zip(timers(),tb)];ac=[x-y for x,y in zip(active(),ab)]
    assert counts==[9599433,100900,54635,200,0,233004],counts
    assert tc==[386704,400,386304,683532,0,0,0,16170,701,0],tc
    assert ac==[386704,1904,384800,3632134,0,760,23435,83822,19040,0],ac
    assert signature.hexdigest()=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert run['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9' and run['matched_original_terminal']==200
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    result=dict(passed=True,cases=21888,actual_separate_baseline_candidate_dlls=True,
        per_case_hashes_equal=True,case_hashes_sha256=hashlib.sha256(json.dumps(a['case_hashes']).encode()).hexdigest(),
        storage_cases=21504,actual_setup_cases=384,fp_rounding_daz_ftz_sticky_states=64,
        baseline_core_item_bytes=a['core_item_bytes'],candidate_core_item_bytes=b['core_item_bytes'],
        baseline_dll_sha256=EXPECTED,dll_sha256=sha(dll),fixture_sha256=sha(fixture),projection=projection,
        old_six_counters=counts,targeted_timer_counters=tc,active_cooldown_counters=ac,
        fixed200_results_sha256=run['results_sha256'],fixed200_inputs_sha256=signature.hexdigest(),
        no_throughput_claim=True,not_for_deployment=True)
    out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf8');print(json.dumps(result,indent=2),flush=True)
    return result

if __name__=='__main__':verify(WORK/'prototype_src',WORK/'prototype.dll',WORK/'retained_display.json')
