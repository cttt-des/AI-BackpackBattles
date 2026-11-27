"""Count real callback, membership and dictionary shapes; never a speed candidate."""
import ctypes,hashlib,json,os,runpy,shutil,subprocess,tempfile
from pathlib import Path
import psutil
from prepare_frame_guard_reuse import STAGE,BASE,sha,inventory
from install_ordering_correctness import boundary
WORK=STAGE/'native_perf50/next_two_assessment'
ACCEPTED=STAGE/'native_perf50/frame_guard_reuse_bundle'

def main():
    boundary();psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    root=Path(tempfile.mkdtemp(prefix='next-two-probe-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'))
    source=root/'source';shutil.copytree(BASE,source);objects=root/'objects';objects.mkdir()
    old=json.loads((ACCEPTED/'prototype_build.json').read_bytes())['objects_sha256']
    live=json.loads((ACCEPTED/'live_semantic_build.json').read_bytes())
    paths={n:Path(live['reused_objects'].get(n,str(Path(live['object_directory'])/n))) for n in old}
    assert all(sha(paths[n])==h for n,h in old.items())
    text=(source/'gd_rt.cpp').read_text('utf8')
    text='extern "C" __declspec(dllexport) unsigned long long next_two_probe_counts[256] = {};\n'+text
    replacements={
        'GdVal GdFuncRef::call_func(BattleCtx& ctx, const GdVal* args, int argc) const {':'\n    ++next_two_probe_counts[0];\n    if(binds && binds->len) { ++next_two_probe_counts[1]; ++next_two_probe_counts[2+std::min<unsigned>(argc+binds->len,31)]; }',
        'int64_t GdArr::find_val(const GdVal& v, int64_t from) const {':'\n    ++next_two_probe_counts[40]; ++next_two_probe_counts[41+std::min<unsigned>(len,31)]; if(v.kind==GdVal::Kind::Vec2)++next_two_probe_counts[73];',
        'int32_t GdDict::find_index(const GdVal& key, uint64_t h) const {':'\n    ++next_two_probe_counts[80]; if(!buckets && cap>8)++next_two_probe_counts[81];',
        'GdDict* GdDict::duplicate(BattleArena& arena, bool deep) const {':'\n    ++next_two_probe_counts[82]; next_two_probe_counts[83]+=len;',
    }
    for old_text,extra in replacements.items():assert text.count(old_text)==1,old_text;text=text.replace(old_text,old_text+extra)
    (source/'gd_rt.cpp').write_text(text,encoding='utf8',newline='\n')
    flags=runpy.run_path(str(source/'build_windows.py'))['COMMON'];cxx='D:/mingw64/bin/g++.exe'
    with (WORK/'shape_probe_compile.log').open('wb') as log:
        subprocess.run([cxx,*flags,'-c',str(source/'gd_rt.cpp'),'-o',str(objects/'gd_rt.o')],stdout=log,stderr=subprocess.STDOUT,check=True)
        paths['gd_rt.o']=objects/'gd_rt.o'
        subprocess.run([cxx,*flags,'-shared','-static','-o',str(objects/'probe.dll'),*map(str,paths.values())],stdout=log,stderr=subprocess.STDOUT,check=True)
    from bench_native_corpus import load_simulator,prepare,select_cases,measure
    sim=load_simulator(objects/'probe.dll');counts=(ctypes.c_uint64*256).in_dll(ctypes.CDLL(str(objects/'probe.dll')),'next_two_probe_counts')
    inputs=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),inputs));result=measure(sim,jobs,1,0,continuous=True)
    assert result['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    report=dict(diagnostic_only=True,no_speed_claim=True,baseline_dll_sha256=sha(BASE/'libgdcore.dll'),root=str(root),counts=list(counts),inputs_sha256=inputs.hexdigest(),results_sha256=result['results_sha256'])
    (WORK/'shape_probe.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');boundary();print(json.dumps(report),flush=True)
if __name__=='__main__':main()
