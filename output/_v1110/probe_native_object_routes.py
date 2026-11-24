"""Count actual receiver types at residual object virtual calls; never benchmark this DLL."""
import ctypes
import hashlib
import json
from pathlib import Path
import re
import runpy
import shutil
import subprocess
import tempfile
import psutil

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/callback_dispatch_bundle'
WORK=STAGE/'native_perf50/object_routes_prototype'
EXPECTED='80a0681c1c93268af2b29c21e5439b6444de36a29ad39486b3f4afadf548a44a'

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()

PROBE=r'''
#include <map>
#include <tuple>
#include <typeinfo>
namespace gd {
using ObjectRouteProbeKey=std::tuple<uintptr_t,SymId,uintptr_t>;
static thread_local std::map<ObjectRouteProbeKey,uint64_t> object_route_probe_counts;
static void object_route_probe(GdObj* object,SymId method) {
    ++object_route_probe_counts[{reinterpret_cast<uintptr_t>(&typeid(*object)),method,
        reinterpret_cast<uintptr_t>(object->native_call_row_)}];
}
static auto object_route_probe_entry(unsigned i) {
    auto it=object_route_probe_counts.begin();
    while(i-- && it!=object_route_probe_counts.end())++it;
    return it;
}
extern "C" void gd_object_route_probe_reset(){object_route_probe_counts.clear();}
extern "C" uint64_t gd_object_route_probe_size(){return object_route_probe_counts.size();}
extern "C" uint64_t gd_object_route_probe_count(unsigned i){
    auto it=object_route_probe_entry(i);return it==object_route_probe_counts.end()?0:it->second;
}
extern "C" uint64_t gd_object_route_probe_method(unsigned i){
    auto it=object_route_probe_entry(i);return it==object_route_probe_counts.end()?0:std::get<1>(it->first);
}
extern "C" const char* gd_object_route_probe_type(unsigned i){
    auto it=object_route_probe_entry(i);return it==object_route_probe_counts.end()?"":
        reinterpret_cast<const std::type_info*>(std::get<0>(it->first))->name();
}
}
'''

ROW_PROBE=r'''
namespace gd {
extern "C" uint64_t gd_object_route_probe_exact_row(unsigned i){
    auto it=object_route_probe_entry(i);if(it==object_route_probe_counts.end())return 0;
    const auto value=std::get<2>(it->first);
    const auto first=reinterpret_cast<uintptr_t>(native_resolved_rows);
    if(value<first || value-first>=sizeof(native_resolved_rows) ||
       (value-first)%sizeof(NativeMethodRow))return 0;
    const auto index=(value-first)/sizeof(NativeMethodRow);
    return reinterpret_cast<uintptr_t>(native_extra_callback_rows[index].exact_type)==
        std::get<0>(it->first)?index+1:0;
}
}
'''

def main():
    process=psutil.Process();process.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert not WORK.exists();WORK.mkdir()
    (WORK/'live_probe.json').write_text(json.dumps(dict(pid=process.pid,created=process.create_time(),script=str(Path(__file__).resolve())))+'\n',encoding='utf8')
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    backup=json.loads((ACCEPTED/'checkpoint_receipt.json').read_bytes())
    assert backup['remote_upload_verified'] and backup['production_dll_sha256']==EXPECTED
    frozen=json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    source=WORK/'probe_src'
    shutil.copytree(BASE,source,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    assert frozen=={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    file=source/'gd_rt.cpp';text=file.read_text('utf8')
    position=text.index('\nnamespace gd {')
    text=text[:position]+PROBE+text[position:]
    marker='            if (recv.obj->call_method(ctx, m, args, argc, out)) return out;'
    assert text.count(marker)==1
    text=text.replace(marker,'            object_route_probe(recv.obj,m);\n'+marker,1)
    marker='#include "native_resolved_dispatch.hpp"';assert text.count(marker)==1
    text=text.replace(marker,marker+'\n'+ROW_PROBE,1)
    file.write_text(text,encoding='utf8',newline='\n')
    # Only gd_rt adds a probe. The semantic candidate's other nineteen objects
    # already implement these exact accepted source bytes and unchanged layouts.
    old=STAGE/'native_perf50/callback_dispatch_prototype'
    assert json.loads((old/'transform.json').read_bytes())['source_sha256']==frozen
    previous=Path((old/'objects.txt').read_text('utf8'))
    objects=Path(tempfile.mkdtemp(prefix='native-object-routes-count-'))
    (WORK/'objects.txt').write_text(str(objects),encoding='utf8')
    names=['gd_rt','engine_wrapper','sym_ids','register_all',*[f'shard_{i:02d}' for i in range(16)]]
    old_hashes={n:sha(previous/(n+'.o')) for n in names}
    flags=runpy.run_path(str(source/'build_windows.py'))['COMMON'];compiler='D:/mingw64/bin/g++.exe'
    with (WORK/'compile_first.log').open('wb') as log:
        subprocess.run([compiler,*flags,'-c',str(file),'-o',str(objects/'gd_rt.o')],stdout=log,stderr=subprocess.STDOUT,check=True)
        subprocess.run([compiler,*flags,'-shared','-static','-o',str(objects/'probe.dll'),
            *[str((objects if n=='gd_rt' else previous)/(n+'.o')) for n in names]],stdout=log,stderr=subprocess.STDOUT,check=True)
    assert old_hashes=={n:sha(previous/(n+'.o')) for n in names}
    dll=WORK/'probe.dll';shutil.copyfile(objects/'probe.dll',dll)
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    sim=load_simulator(dll);signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    audit=sim.lib.gd_diag_native_resolved_audit;audit.argtypes=[ctypes.c_int];audit.restype=None;audit(1)
    stat=sim.lib.gd_diag_native_resolved_stat;stat.argtypes=[ctypes.c_uint];stat.restype=ctypes.c_uint64
    reset=sim.lib.gd_object_route_probe_reset;reset.argtypes=[];reset.restype=None;reset()
    before=[stat(i) for i in range(6)];run=measure(sim,jobs,1,0,continuous=True)
    actual=[stat(i)-before[i] for i in range(6)]
    assert actual==[9599433,100900,54635,200,0,233004],actual
    assert signature.hexdigest()=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert run['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    assert run['matched_original_terminal']==200
    get={}
    for n in ('size','count','method','exact_row','type'):
        fn=getattr(sim.lib,'gd_object_route_probe_'+n);fn.argtypes=[] if n=='size' else [ctypes.c_uint]
        fn.restype=ctypes.c_char_p if n=='type' else ctypes.c_uint64;get[n]=fn
    builtin=re.findall(r'X\((SYM_\w+),',(BASE/'builtin_syms.hpp').read_text('utf8'))
    generated=re.findall(r'^\s+(SYM_GEN_\w+),\s*$',(BASE/'gen/sym_ids.hpp').read_text('utf8'),re.M)
    symbols={i+1:s for i,s in enumerate(builtin)}
    symbols.update({len(builtin)+2+i:s for i,s in enumerate(generated)})
    rows=[]
    for i in range(get['size']()):
        method=get['method'](i);index=get['exact_row'](i)
        rows.append(dict(method_id=method,method=symbols.get(method,str(method)),
            receiver_cpp_type=get['type'](i).decode(),canonical_exact_row_index=index-1 if index else None,count=get['count'](i)))
    rows.sort(key=lambda r:(-r['count'],r['method'],r['receiver_cpp_type']))
    report=dict(passed=True,probe_only=True,not_for_deployment=True,no_throughput_claim=True,
        baseline_dll_sha256=EXPECTED,probe_dll_sha256=sha(dll),verified_backup_commit=backup['remote_verified_commit'],
        matched_original_terminal=200,inputs_sha256=signature.hexdigest(),results_sha256=run['results_sha256'],
        old_six_counters=actual,total_object_virtual_calls=sum(r['count'] for r in rows),
        exact_generated_row_calls=sum(r['count'] for r in rows if r['canonical_exact_row_index'] is not None),rows=rows,
        source_manifest_sha256=sha(ACCEPTED/'source_before_build.json'),previous_objects_sha256=old_hashes)
    (WORK/'object_route_probe.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    print(json.dumps({k:v for k,v in report.items() if k not in ('rows','previous_objects_sha256')},indent=2))
    print(json.dumps(rows[:25],indent=2))

if __name__=='__main__':main()
