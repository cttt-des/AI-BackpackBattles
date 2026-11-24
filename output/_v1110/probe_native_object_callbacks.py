"""Count residual generic object calls; select scope from actual occurrences."""
import ctypes
import hashlib
import json
from pathlib import Path
import runpy
import shutil
import subprocess
import tempfile
import psutil
from prepare_native_callback_dispatch import STAGE,BASE,WORK,ACCEPTED,EXPECTED,sha

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    out=WORK/'object_callback_probe.json';assert not out.exists()
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    source=WORK/'object_probe_src';assert not source.exists()
    shutil.copytree(BASE,source,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    assert {p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    p=source/'gd_rt.cpp';text=p.read_text('utf8');pos=text.index('\nnamespace gd {')
    text=text[:pos]+'''\nnamespace gd {
static thread_local uint64_t object_callback_probe_counts[4096]{};
extern "C" uint64_t gd_object_callback_probe_stat(unsigned i){return i<4096?object_callback_probe_counts[i]:0;}
}\n'''+text[pos:]
    marker='            if (recv.obj->call_method(ctx, m, args, argc, out)) return out;'
    assert text.count(marker)==1
    text=text.replace(marker,'            if(m<4096)++object_callback_probe_counts[m];\n'+marker,1)
    p.write_text(text,encoding='utf8',newline='\n')
    objects=Path(tempfile.mkdtemp(prefix='native-object-callback-count-'))
    previous=Path((STAGE/'native_perf50/literal_spans_prototype/objects.txt').read_text('utf8'))
    names=['gd_rt','engine_wrapper','sym_ids','register_all',*[f'shard_{i:02d}' for i in range(16)]]
    flags=runpy.run_path(str(source/'build_windows.py'))['COMMON'];compiler='D:/mingw64/bin/g++.exe'
    with (WORK/'object_probe_compile_first.log').open('wb') as log:
        subprocess.run([compiler,*flags,'-c',str(p),'-o',str(objects/'gd_rt.o')],stdout=log,stderr=subprocess.STDOUT,check=True)
        subprocess.run([compiler,*flags,'-shared','-static','-o',str(objects/'probe.dll'),
            *[str((objects if n=='gd_rt' else previous)/(n+'.o')) for n in names]],stdout=log,stderr=subprocess.STDOUT,check=True)
    dll=WORK/'object_probe.dll';shutil.copyfile(objects/'probe.dll',dll)
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    sim=load_simulator(dll);signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    stat=sim.lib.gd_object_callback_probe_stat;stat.argtypes=[ctypes.c_uint];stat.restype=ctypes.c_uint64
    before=[stat(i) for i in range(4096)];run=measure(sim,jobs,1,0,continuous=True)
    counts=[stat(i)-before[i] for i in range(4096)]
    import re
    first=len(re.findall(r'X\((SYM_\w+),',(BASE/'builtin_syms.hpp').read_text('utf8')))+2
    symbols=re.findall(r'^\s+(SYM_GEN_\w+),\s*$',(BASE/'gen/sym_ids.hpp').read_text('utf8'),re.M)
    names_by_id={first+i:s for i,s in enumerate(symbols)}
    selected=set(json.loads((WORK/'callback_source_proof.json').read_bytes())['selected'])
    hits={names_by_id[i]:n for i,n in enumerate(counts) if n and names_by_id.get(i) in selected}
    assert signature.hexdigest()=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert run['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    report=dict(passed=True,probe_only=True,no_throughput_claim=True,not_for_deployment=True,
        baseline_dll_sha256=EXPECTED,probe_dll_sha256=sha(dll),
        remaining_object_virtual_calls=sum(counts),selected65_callback_calls=sum(hits.values()),selected_callback_methods=hits,
        selected_method_count_is_an_opportunity_upper_bound_not_type_eligibility=True,
        all_method_symbols={str(i):n for i,n in enumerate(counts) if n},
        inputs_sha256=signature.hexdigest(),results_sha256=run['results_sha256'])
    out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report,indent=2),flush=True)

if __name__=='__main__':main()
