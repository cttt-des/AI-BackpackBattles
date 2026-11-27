"""Count two actual assembly membership sites; diagnostic only, never time it."""
import ctypes
import argparse
import hashlib
import json
import os
from pathlib import Path
import runpy
import shutil
import subprocess
import tempfile
import psutil
STAGE=Path(__file__).resolve().parent
ASSESSMENT=STAGE/'native_perf50/assembly_membership_assessment'
WORK=ASSESSMENT
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/buff_inline_types_bundle'
NORMAL=STAGE/'native_perf50/buff_inline_types_prototype'
EXPECTED='d2064b3f17d8168cf87a2e9f46e9fb336ffe4aaf6581c27d93350b2c41477a57'

PREFIX='''#include "gd_rt.hpp"
#include <algorithm>
namespace gd::assembly_probe {
static uint64_t counts[96]{};
inline GdVal member(unsigned family,const GdVal& needle,const GdVal& haystack) {
    auto* out=counts+family*48;
    ++out[0];out[1]+=needle.kind==GdVal::Kind::Vec2;out[2]+=needle.kind==GdVal::Kind::Obj;
    if(haystack.kind==GdVal::Kind::Arr && haystack.arr){
        ++out[3];out[8]+=haystack.arr->len;out[9]=std::max(out[9],uint64_t(haystack.arr->len));
        ++out[16+std::min(haystack.arr->len,16u)];
        bool vectors=true;for(uint32_t i=0;i<haystack.arr->len;++i)vectors &= haystack.arr->data[i].kind==GdVal::Kind::Vec2;
        ++out[vectors?10:11];
    }else if(haystack.kind==GdVal::Kind::Dict && haystack.dict){
        ++out[4];out[34]+=haystack.dict->len;out[35]=std::max(out[35],uint64_t(haystack.dict->len));
        ++out[37+std::min(haystack.dict->len,10u)];
    }
    else ++out[5];
    const auto result=gd_in(needle,haystack);
    if(result.kind==GdVal::Kind::Bool)++out[result.b?6:7];
    return result;
}
}
extern "C" uint64_t gd_diag_assembly_membership_stat(unsigned i){return i<96?gd::assembly_probe::counts[i]:0;}
'''

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def inventory(p):return {f.relative_to(p).as_posix():sha(f) for f in p.rglob('*') if f.is_file() and '__pycache__' not in f.parts and f.suffix not in ('.dll','.o','.gcda','.gcno','.pyc')}
def save(name,r):(WORK/name).write_text(json.dumps(r,indent=2)+'\n',encoding='utf8')

def main():
    global WORK
    parser=argparse.ArgumentParser();parser.add_argument('--dictionary-lengths',action='store_true');args=parser.parse_args()
    if args.dictionary_lengths:
        WORK=ASSESSMENT/'dictionary_lengths';assert not WORK.exists();WORK.mkdir()
    p=psutil.Process();p.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    assert json.loads((ASSESSMENT/'previous_direction_backup_verified.json').read_bytes())['second_direction_can_begin']
    before=json.loads((ACCEPTED/'source_before_build.json').read_bytes());assert inventory(BASE)==before
    source=WORK/'probe_src';assert not source.exists();shutil.copytree(ACCEPTED/'bundle_src',source)
    file='gen/shards/shard_00.cpp';path=source/file;old=path.read_text('utf8')
    start=old.index('gd::GdVal Gd__gd_core__CoreItem::fn_onItemAdded(');end=old.index('\n}',start)+2
    text=old[start:end]
    for a,b in [('gd::gd_in(occupied->data[i], tiles)','gd::assembly_probe::member(0, occupied->data[i], tiles)'),
                ('gd::gd_in(item, current)','gd::assembly_probe::member(1, item, current)')]:
        assert text.count(a)==1;text=text.replace(a,b,1)
    text=PREFIX+old[:start]+text+old[end:];path.write_text(text,encoding='utf8',newline='\n')
    current=inventory(source);assert [n for n,h in before.items() if current[n]!=h]==[file]
    save('diagnostic_source.json',dict(baseline_dll_sha256=EXPECTED,changed_files=[file],source_sha256=current,prefix_sha256=hashlib.sha256(PREFIX.encode()).hexdigest(),no_fp_operations_or_value_comparisons_added=True,no_timing_claim=True))
    old_objects=json.loads((NORMAL/'build.json').read_bytes())['objects_sha256'];assert len(old_objects)==20
    state=json.loads((NORMAL/'live_semantic_build.json').read_bytes());roots=[Path(state['object_directory']),Path(state['reused_object_directory'])]
    originals={n:next(root/n for root in roots if (root/n).exists() and sha(root/n)==h) for n,h in old_objects.items()}
    assert before==json.loads((NORMAL/'transform.json').read_bytes())['source_sha256']
    root=Path(tempfile.mkdtemp(prefix='assembly-membership-probe-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'))
    objects=root/'objects';objects.mkdir();scratch=root/'scratch';scratch.mkdir()
    os.environ.update(TEMP=str(scratch),TMP=str(scratch),TMPDIR=str(scratch));tempfile.tempdir=str(scratch)
    save('live_probe.json',dict(pid=p.pid,created=p.create_time(),root=str(root),object_directory=str(objects)))
    flags=runpy.run_path(str(source/'build_windows.py'))['COMMON'];compiler='D:/mingw64/bin/g++.exe'
    with (WORK/'probe_compile_first.log').open('wb') as log:
        subprocess.run([compiler,*flags,'-c',str(path),'-o',str(objects/'shard_00.o')],stdout=log,stderr=subprocess.STDOUT,check=True)
    actual={n:(objects/n if n=='shard_00.o' else x) for n,x in originals.items()}
    with (WORK/'probe_link_first.log').open('wb') as log:
        subprocess.run([compiler,*flags,'-shared','-static','-save-temps=obj','-o',str(objects/'libgdcore.dll'),*[str(x) for x in actual.values()]],stdout=log,stderr=subprocess.STDOUT,check=True)
    assert all(sha(originals[n])==h for n,h in old_objects.items());shutil.copyfile(objects/'libgdcore.dll',WORK/'probe.dll')
    from bench_native_corpus import load_simulator,measure,prepare,select_cases
    sim=load_simulator(WORK/'probe.dll');signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature))
    sim.lib.gd_diag_native_resolved_audit.argtypes=[ctypes.c_int];sim.lib.gd_diag_native_resolved_audit(1)
    counter=sim.lib.gd_diag_assembly_membership_stat;counter.argtypes=[ctypes.c_uint];counter.restype=ctypes.c_uint64
    initial=[counter(i) for i in range(96)]
    def get_counts(name,n):
        f=getattr(sim.lib,name);f.argtypes=[ctypes.c_uint];f.restype=ctypes.c_uint64
        return lambda:[f(i) for i in range(n)]
    legacy=[get_counts(*r) for r in [('gd_diag_native_resolved_stat',6),('gd_diag_native_targeted_timer_stat',10),('gd_diag_native_active_cooldown_stat',10),('gd_diag_native_private_snapshot_stat',4)]]
    legacy_before=[f() for f in legacy];result=measure(sim,jobs,1,0,continuous=True)
    observed=[[a-b for a,b in zip(f(),v)] for f,v in zip(legacy,legacy_before)]
    assert observed==[[9599433,100900,54635,200,0,233004],[386704,400,386304,683532,0,0,0,16170,701,0],[386704,1904,384800,3632134,0,760,23435,83822,19040,0],[30901,0,34193,0]],observed
    assert signature.hexdigest()=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert result['matched_original_terminal']==200 and result['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    raw=[counter(i)-v for i,v in enumerate(initial)];families={}
    for family,name in enumerate(['coordinate_tiles','affected_object_set']):
        x=raw[family*48:(family+1)*48]
        families[name]=dict(calls=x[0],vec2_needles=x[1],object_needles=x[2],array_haystacks=x[3],dictionary_haystacks=x[4],other_haystacks=x[5],true_results=x[6],false_results=x[7],array_lengths_sum=x[8],maximum_array_length=x[9],pure_vec2_arrays=x[10],mixed_arrays=x[11],array_length_histogram={str(i) if i<16 else '16+':v for i,v in enumerate(x[16:33])})
        families[name].update(dictionary_lengths_sum=x[34],maximum_dictionary_length=x[35],dictionary_length_histogram={str(i) if i<10 else '10+':v for i,v in enumerate(x[37:48])})
    assert current==inventory(source) and sha(BASE/'libgdcore.dll')==EXPECTED
    report=dict(passed=True,dll_sha256=sha(WORK/'probe.dll'),baseline_dll_sha256=EXPECTED,fixed200_inputs_sha256=signature.hexdigest(),fixed200_results_sha256=result['results_sha256'],matched_original_terminal=200,all_old_counters_equal=observed,families=families,raw=raw,diagnostic_only_no_cost_or_gain_claim=True,reused19_source_verified_normal_objects=True)
    save('counts.json',report);print(json.dumps(report),flush=True)

if __name__=='__main__':main()
