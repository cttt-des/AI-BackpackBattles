"""Count uncovered calls without changing object layout or the deployed DLL."""
import ctypes
import hashlib
import json
import os
from pathlib import Path
import runpy
import shutil
import subprocess
import sys
import tempfile
import psutil

psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=WORK.parent/'resolved_dispatch_a'
sys.path.insert(0,str(STAGE))
from bench_native_corpus import load_simulator,measure,prepare,select_cases

def digest(p):return hashlib.sha256(p.read_bytes()).hexdigest()

def main():
    os.environ['NATIVE_SIM_CXX']='D:/mingw64/bin/g++.exe'
    os.environ['MAKE']='D:/mingw64/bin/mingw32-make.exe'
    assert digest(BASE/'libgdcore.dll')=='6e232391806268a9e77dde1ba5d89a96320453fe82bacd9d092e355a56c67a5b'
    recorded=json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    for name,sha in recorded.items():assert digest(BASE/name)==sha,name
    cache=Path((ACCEPTED/'resolved_objects.txt').read_text('utf8'))
    assert len(list(cache.glob('*.o')))==20
    folder=Path(tempfile.mkdtemp(prefix='native-method-miss-probe-'));source=folder/'src'
    shutil.copytree(BASE,source,ignore=shutil.ignore_patterns('__pycache__','*.dll','*.o','*.gcda','*.gcno'))
    header=source/'native_resolved_dispatch.hpp';text=header.read_text('utf8')
    anchor='bool try_native_resolved_dispatch('
    assert text.count(anchor)==1
    text=text.replace(anchor,'static thread_local std::array<uint64_t,native_resolved_slots.size()> native_uncovered_calls{};\n'+anchor,1)
    anchor='const int slot=native_resolved_slots[method]; if(slot<0)return false;'
    assert text.count(anchor)==1
    text=text.replace(anchor,'const int slot=native_resolved_slots[method]; if(slot<0) {if(ctx.native_resolved_collect)++native_uncovered_calls[method];return false;}',1)
    header.write_text(text,encoding='utf8',newline='\n')
    rt=source/'gd_rt.cpp'
    with rt.open('a',encoding='utf8',newline='\n') as f:f.write('''
extern "C" uint64_t gd_diag_uncovered_calls(unsigned symbol) {return symbol<gd::native_uncovered_calls.size()?gd::native_uncovered_calls[symbol]:0;}
extern "C" unsigned gd_diag_uncovered_limit() {return static_cast<unsigned>(gd::native_uncovered_calls.size());}
extern "C" const char* gd_diag_uncovered_name(unsigned symbol) {return gd::sym_name(symbol);}
''')
    for name in recorded:
        if name not in ('gd_rt.cpp','native_resolved_dispatch.hpp'):assert digest(source/name)==recorded[name],name
    module=runpy.run_path(str(source/'build_windows.py'))
    common=module['COMMON'];cxx=module['CXX']
    # Only gd_rt.cpp includes the private table definition; gd_rt.hpp, every
    # object layout, and all other source files are byte-identical to the cache.
    print('Diagnostic only: compile one layout-compatible unit, reuse19 verified objects, linkLTO2',flush=True)
    command=[cxx,*common,'-flto=2','-c',str(rt),'-o',str(folder/'gd_rt.o')]
    with (WORK/'miss_probe_build.log').open('wb') as log:
        subprocess.run(command,cwd=folder,stdout=log,stderr=subprocess.STDOUT,check=True)
        objects=[folder/'gd_rt.o' if p.name=='gd_rt.o' else p for p in sorted(cache.glob('*.o'))]
        dll=folder/'miss_probe.dll'
        subprocess.run([cxx,*common,'-flto=2','-shared','-static','-o',str(dll),*map(str,objects)],cwd=folder,stdout=log,stderr=subprocess.STDOUT,check=True)
    sim=load_simulator(dll);signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    audit=sim.lib.gd_diag_native_resolved_audit;audit.argtypes=[ctypes.c_int];audit.restype=None;audit(1)
    result=measure(sim,jobs,1,0,continuous=True)
    reference=json.loads((STAGE/'native_perf50_event_bus_serial.json').read_bytes())
    assert signature.hexdigest()==reference['inputs_sha256'] and result['results_sha256']==reference['results_sha256']
    count=sim.lib.gd_diag_uncovered_calls;count.argtypes=[ctypes.c_uint];count.restype=ctypes.c_uint64
    limit=sim.lib.gd_diag_uncovered_limit;limit.argtypes=[];limit.restype=ctypes.c_uint
    name=sim.lib.gd_diag_uncovered_name;name.argtypes=[ctypes.c_uint];name.restype=ctypes.c_char_p
    rows=[]
    for symbol in range(limit()):
        if value:=count(symbol):rows.append({'id':symbol,'name':name(symbol).decode('utf8','replace'),'calls':value})
    rows.sort(key=lambda r:r['calls'],reverse=True)
    report={'diagnostic_only':True,'deployed_baseline_sha256':digest(BASE/'libgdcore.dll'),'diagnostic_sha256':digest(dll),
        'inputs_sha256':signature.hexdigest(),'results_sha256':result['results_sha256'],
        'cached_objects_reused':19,'compiler':cxx,'object_layout_unchanged':True,'total_uncovered_calls':sum(r['calls'] for r in rows),
        'method_counts':rows,'directory':str(folder)}
    (WORK/'uncovered_method_counts.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8',newline='\n')
    print(json.dumps({**report,'method_counts':rows[:24]},indent=2))

if __name__=='__main__':main()
