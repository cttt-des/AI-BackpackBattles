"""Count real literal arrays avoided, using an isolated one-unit probe DLL."""
import ctypes
import hashlib
import json
from pathlib import Path
import runpy
import shutil
import subprocess
import tempfile
import psutil
from prepare_native_literal_spans import STAGE,WORK,sha

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    out=WORK/'allocation_probe.json';assert not out.exists()
    original=WORK/'prototype_src';source=WORK/'count_probe_src'
    assert not source.exists();shutil.copytree(original,source)
    p=source/'gen/shards/shard_12.cpp';text=p.read_text('utf8')
    marker='gd::GdVal gd_native_emit_literal_body(Gd__gd_core__CoreEventBus* bus,const gd::GdVal* prefix,NativeLiteralEventArguments& arguments) {'
    assert text.count(marker)==1
    probe='''static thread_local uint64_t literal_probe[4]{};
extern "C" uint64_t gd_literal_probe_stat(unsigned i){return i<4?literal_probe[i]:0;}
struct LiteralProbeScope {
    NativeLiteralEventArguments& args;
    ~LiteralProbeScope(){++literal_probe[args.array.is_null()?1:2];if(args.array.is_null())literal_probe[3]+=args.count;}
};
'''
    text=text.replace(marker,probe+marker+'\n    ++literal_probe[0];LiteralProbeScope literal_scope{arguments};',1)
    p.write_text(text,encoding='utf8',newline='\n')
    objects=Path(tempfile.mkdtemp(prefix='native-literal-count-'))
    previous=Path((WORK/'objects.txt').read_text('utf8'))
    names=['gd_rt','engine_wrapper','sym_ids','register_all',*[f'shard_{i:02d}' for i in range(16)]]
    flags=runpy.run_path(str(source/'build_windows.py'))['COMMON'];compiler='D:/mingw64/bin/g++.exe'
    with (WORK/'count_probe_compile_first.log').open('wb') as log:
        subprocess.run([compiler,*flags,'-c',str(p),'-o',str(objects/'shard_12.o')],stdout=log,stderr=subprocess.STDOUT,check=True)
        subprocess.run([compiler,*flags,'-shared','-static','-o',str(objects/'probe.dll'),
            *[str((objects if n=='shard_12' else previous)/(n+'.o')) for n in names]],stdout=log,stderr=subprocess.STDOUT,check=True)
    dll=WORK/'count_probe.dll';shutil.copyfile(objects/'probe.dll',dll)
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    sim=load_simulator(dll);signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    stat=sim.lib.gd_literal_probe_stat;stat.argtypes=[ctypes.c_uint];stat.restype=ctypes.c_uint64
    before=[stat(i) for i in range(4)];run=measure(sim,jobs,1,0,continuous=True);counts=[stat(i)-before[i] for i in range(4)]
    assert counts[0]==counts[1]+counts[2] and counts[1]>0
    assert signature.hexdigest()=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert run['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    result=dict(passed=True,probe_only=True,not_for_deployment=True,no_throughput_claim=True,
        probe_dll_sha256=sha(dll),literal_emissions=counts[0],arrays_avoided=counts[1],arrays_materialized=counts[2],
        argument_cells_avoided=counts[3],minimum_arena_allocations_avoided=2*counts[1],
        inputs_sha256=signature.hexdigest(),results_sha256=run['results_sha256'])
    out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf8');print(json.dumps(result,indent=2),flush=True)

if __name__=='__main__':main()
