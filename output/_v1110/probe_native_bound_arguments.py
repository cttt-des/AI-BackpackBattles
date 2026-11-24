"""Count actual bound concatenations and arities without making a speed claim."""
import ctypes
import hashlib
import json
from pathlib import Path
import runpy
import shutil
import subprocess
import tempfile
import psutil

STAGE=Path(__file__).resolve().parent
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/literal_spans_bundle'
WORK=STAGE/'native_perf50/bound_callbacks_prototype'
EXPECTED='c46cc19c06fb3c424a470f04bb7a0ef5acf8b7ff01caaccd5f41a5c44d955ee1'

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()

PROBE=r'''
#include <typeinfo>
namespace gd {
static thread_local uint64_t bound_probe_counts[5][4096]{};
struct BoundProbeReceiver {const char* name;uint64_t unbound;uint64_t bound;};
static thread_local std::vector<BoundProbeReceiver> bound_probe_receivers;
static unsigned bound_probe_bucket(uint64_t value){return value<=32?unsigned(value):33;}
static void bound_probe_hit(GdObj* object,SymId method,int argc,uint32_t binds) {
    ++bound_probe_counts[0][0];
    ++bound_probe_counts[0][binds?1:2];
    if(binds && argc>=0 && uint64_t(argc)+binds<=8)++bound_probe_counts[0][3];
    if(binds && argc>=0 && uint64_t(argc)+binds<=16)++bound_probe_counts[0][4];
    if(argc<0)++bound_probe_counts[0][5];
    ++bound_probe_counts[1][argc<0?34:bound_probe_bucket(uint64_t(argc))];
    ++bound_probe_counts[2][bound_probe_bucket(binds)];
    if(binds)++bound_probe_counts[3][argc<0?34:bound_probe_bucket(uint64_t(argc)+binds)];
    if(method<4096)++bound_probe_counts[4][method];
    if(!object)return;
    const auto* name=typeid(*object).name();
    for(auto& row:bound_probe_receivers)if(row.name==name){++(binds?row.bound:row.unbound);return;}
    bound_probe_receivers.push_back({name,binds?0u:1u,binds?1u:0u});
}
extern "C" uint64_t gd_bound_probe_stat(unsigned group,unsigned index){return group<5 && index<4096?bound_probe_counts[group][index]:0;}
extern "C" unsigned gd_bound_probe_receiver_size(){return unsigned(bound_probe_receivers.size());}
extern "C" const char* gd_bound_probe_receiver_name(unsigned index){return index<bound_probe_receivers.size()?bound_probe_receivers[index].name:nullptr;}
extern "C" uint64_t gd_bound_probe_receiver_count(unsigned index,unsigned bound){return index<bound_probe_receivers.size()?(bound?bound_probe_receivers[index].bound:bound_probe_receivers[index].unbound):0;}
}
'''

def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert sha(BASE/'libgdcore.dll')==sha(ACCEPTED/'bundle.dll')==EXPECTED
    verified=json.loads((ACCEPTED/'post_install_verification.json').read_bytes())
    assert verified['passed'] and verified['dll_sha256']==EXPECTED
    assert not WORK.exists();WORK.mkdir()
    source=WORK/'count_probe_src'
    shutil.copytree(BASE,source,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    source_hashes={p.relative_to(source).as_posix():sha(p) for p in source.rglob('*') if p.is_file()}
    assert source_hashes==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    old=STAGE/'native_perf50/literal_spans_prototype'
    assert source_hashes==json.loads((old/'transform.json').read_bytes())['source_sha256']
    p=source/'gd_rt.cpp';text=p.read_text('utf8')
    pos=text.index('\nnamespace gd {');text=text[:pos]+'\n'+PROBE+text[pos:]
    marker='''GdVal GdFuncRef::call_func(BattleCtx& ctx, const GdVal* args, int argc) const {
    if (!instance || method == SYM_NONE) return GdVal::null();
    native_timer_observe_object(ctx,instance);'''
    assert text.count(marker)==1
    text=text.replace(marker,marker+'\n    bound_probe_hit(instance,method,argc,binds?binds->len:0);',1)
    p.write_text(text,encoding='utf8',newline='\n')
    (WORK/'count_probe_source.json').write_text(json.dumps(dict(
        baseline_dll_sha256=EXPECTED,baseline_source_sha256=source_hashes,
        modified_files=['gd_rt.cpp'],probe_only=True,not_for_deployment=True),indent=2)+'\n',encoding='utf8')
    objects=Path(tempfile.mkdtemp(prefix='native-bound-count-'))
    (WORK/'count_objects.txt').write_text(str(objects),encoding='utf8')
    previous=Path((old/'objects.txt').read_text('utf8'))
    names=['gd_rt','engine_wrapper','sym_ids','register_all',*[f'shard_{i:02d}' for i in range(16)]]
    old_hashes={n:sha(previous/(n+'.o')) for n in names}
    flags=runpy.run_path(str(source/'build_windows.py'))['COMMON'];compiler='D:/mingw64/bin/g++.exe'
    with (WORK/'count_probe_compile_first.log').open('wb') as log:
        subprocess.run([compiler,*flags,'-c',str(p),'-o',str(objects/'gd_rt.o')],stdout=log,stderr=subprocess.STDOUT,check=True)
        subprocess.run([compiler,*flags,'-shared','-static','-o',str(objects/'probe.dll'),
            *[str((objects if n=='gd_rt' else previous)/(n+'.o')) for n in names]],stdout=log,stderr=subprocess.STDOUT,check=True)
    assert old_hashes=={n:sha(previous/(n+'.o')) for n in names}
    dll=WORK/'count_probe.dll';shutil.copyfile(objects/'probe.dll',dll)
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    sim=load_simulator(dll);signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    stat=sim.lib.gd_bound_probe_stat;stat.argtypes=[ctypes.c_uint,ctypes.c_uint];stat.restype=ctypes.c_uint64
    receiver_size=sim.lib.gd_bound_probe_receiver_size;receiver_size.argtypes=[];receiver_size.restype=ctypes.c_uint
    receiver_name=sim.lib.gd_bound_probe_receiver_name;receiver_name.argtypes=[ctypes.c_uint];receiver_name.restype=ctypes.c_char_p
    receiver_count=sim.lib.gd_bound_probe_receiver_count;receiver_count.argtypes=[ctypes.c_uint,ctypes.c_uint];receiver_count.restype=ctypes.c_uint64
    before=[[stat(g,i) for i in range(4096)] for g in range(5)]
    before_types={receiver_name(i).decode():[receiver_count(i,b) for b in (0,1)] for i in range(receiver_size())}
    result=measure(sim,jobs,1,0,continuous=True)
    counts=[[stat(g,i)-before[g][i] for i in range(4096)] for g in range(5)]
    receivers={}
    for i in range(receiver_size()):
        name=receiver_name(i).decode();prior=before_types.get(name,[0,0]);row=[receiver_count(i,b)-prior[b] for b in (0,1)]
        if any(row):receivers[name]=dict(unbound=row[0],bound=row[1])
    assert counts[0][0]==counts[0][1]+counts[0][2]
    assert signature.hexdigest()=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert result['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    report=dict(passed=True,probe_only=True,not_for_deployment=True,no_throughput_claim=True,
        baseline_dll_sha256=EXPECTED,probe_dll_sha256=sha(dll),recompiled_units=1,reused_objects=19,
        original_observe_before_binding_read_preserved=True,no_extra_virtual_metadata_calls=True,
        calls=counts[0][0],heap_bound_concatenations=counts[0][1],unbound_slow_calls=counts[0][2],
        bound_total_arity_at_most8=counts[0][3],bound_total_arity_at_most16=counts[0][4],negative_argc=counts[0][5],
        incoming_arity={str(i):n for i,n in enumerate(counts[1]) if n},
        binding_arity={str(i):n for i,n in enumerate(counts[2]) if n},
        bound_combined_arity={str(i):n for i,n in enumerate(counts[3]) if n},
        slow_method_symbols={str(i):n for i,n in enumerate(counts[4]) if n},receiver_types=receivers,
        inputs_sha256=signature.hexdigest(),results_sha256=result['results_sha256'])
    (WORK/'bound_argument_probe.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print(json.dumps(report,indent=2),flush=True)

if __name__=='__main__':main()
