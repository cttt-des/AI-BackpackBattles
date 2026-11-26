"""Count fallback receiver kinds/methods; semantic-only oneTU diagnostic build."""
import ctypes
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
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ACCEPTED=STAGE/'native_perf50/frame_value_bundle'
NORMAL=STAGE/'native_perf50/frame_value_prototype'
WORK=STAGE/'native_perf50/method_dispatch_probe_20261126'
EXPECTED='0a6d24f459eb1011a0bfcc1bc5c4188c1ca67add410b9caf0e04c8f5d30d44d4'
ARCHIVE='4cbfd55b10a7dae66529c41da01cbcce63ae66d2'
KINDS=('Null','Bool','Int','Float','Vec2','Color','Str','Arr','Dict','Obj','ClassRef','Enum','FuncRef','Rng','Unknown')

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def save(name,r):(WORK/name).write_text(json.dumps(r,indent=2)+'\n',encoding='utf8')
def main():
    p=psutil.Process();p.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    receipt=json.loads((ACCEPTED/'checkpoint_receipt.json').read_bytes())
    assert receipt['remote_upload_verified'] and receipt['remote_verified_commit']==ARCHIVE
    assert sha(BASE/'libgdcore.dll')==sha(ACCEPTED/'bundle.dll')==EXPECTED and not WORK.exists()
    WORK.mkdir();source=WORK/'source';shutil.copytree(ACCEPTED/'bundle_src',source)
    baseline=json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    assert baseline==json.loads((NORMAL/'transform.json').read_bytes())['source_sha256']
    assert {q.relative_to(source).as_posix():sha(q) for q in source.rglob('*') if q.is_file()}==baseline
    cpp=source/'gd_rt.cpp';text=cpp.read_text('utf8')
    anchor='GdVal call_method(BattleCtx& ctx, const GdVal& recv, SymId m, const GdVal* args, int argc) {\n'
    assert text.count(anchor)==1 and 'method_profile_enabled' not in text
    globals='''// 仅供单线程诊断，当前发布构建与游戏状态不使用这些计数。
static bool method_profile_enabled=false;
static uint64_t method_profile_counts[15u*65536u]{};
static uint64_t method_profile_overflow[15]{};
'''
    count='''    if(method_profile_enabled) {
        const unsigned kind=std::min(static_cast<unsigned>(recv.kind),14u);
        if(m<65536u)++method_profile_counts[size_t(kind)*65536u+m];
        else ++method_profile_overflow[kind];
    }
'''
    text=text.replace(anchor,globals+anchor+count,1)
    text+='''
// 这些入口只存在于本次诊断DLL。
extern "C" void gd_diag_native_method_profile_reset() {
    std::memset(gd::method_profile_counts,0,sizeof(gd::method_profile_counts));
    std::memset(gd::method_profile_overflow,0,sizeof(gd::method_profile_overflow));
    gd::method_profile_enabled=true;
}
extern "C" const uint64_t* gd_diag_native_method_profile_data(){return gd::method_profile_counts;}
extern "C" const uint64_t* gd_diag_native_method_profile_overflow(){return gd::method_profile_overflow;}
extern "C" const char* gd_diag_native_method_profile_name(uint32_t id){return gd::sym_name(id);}
'''
    cpp.write_text(text,encoding='utf8',newline='\n')
    assert all(sha(source/n)==h for n,h in baseline.items() if n!='gd_rt.cpp')
    save('source_before_probe.json',{q.relative_to(source).as_posix():sha(q) for q in source.rglob('*') if q.is_file()})
    old=json.loads((NORMAL/'live_semantic_build.json').read_bytes());previous=Path(old['object_directory'])
    old_objects=json.loads((NORMAL/'build.json').read_bytes())['objects_sha256']
    assert len(old_objects)==20 and all(sha(previous/n)==h for n,h in old_objects.items())
    root=Path(tempfile.mkdtemp(prefix='method-dispatch-counts-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'))
    objects=root/'objects';objects.mkdir();scratch=root/'scratch';scratch.mkdir()
    os.environ.update(TEMP=str(scratch),TMP=str(scratch),TMPDIR=str(scratch),MAKE='D:/mingw64/bin/mingw32-make.exe');tempfile.tempdir=str(scratch)
    save('live_probe.json',dict(pid=p.pid,created=p.create_time(),object_directory=str(objects),normal_objects=str(previous)))
    flags=runpy.run_path(str(source/'build_windows.py'))['COMMON'];compiler='D:/mingw64/bin/g++.exe'
    with (WORK/'compile_first.log').open('wb') as output:
        subprocess.run([compiler,*flags,'-c',str(cpp),'-o',str(objects/'gd_rt.o')],stdout=output,stderr=subprocess.STDOUT,check=True)
        subprocess.run([compiler,*flags,'-shared','-static','-save-temps=obj','-o',str(objects/'libgdcore.dll'),
            *[str((objects if n=='gd_rt.o' else previous)/n) for n in old_objects]],stdout=output,stderr=subprocess.STDOUT,check=True)
    assert all(sha(previous/n)==h for n,h in old_objects.items())
    shutil.copyfile(objects/'libgdcore.dll',WORK/'diagnostic.dll')
    from bench_native_corpus import load_simulator,prepare,select_cases,measure
    sim=load_simulator(WORK/'diagnostic.dll');signature=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),signature));assert len(jobs)==200
    sim.lib.gd_diag_native_resolved_audit.argtypes=[ctypes.c_int];sim.lib.gd_diag_native_resolved_audit(1)
    stat=sim.lib.gd_diag_native_resolved_stat;stat.argtypes=[ctypes.c_uint];stat.restype=ctypes.c_uint64
    before=[stat(i) for i in range(6)];sim.lib.gd_diag_native_method_profile_reset()
    run=measure(sim,jobs,1,0,continuous=True);counts=[stat(i)-before[i] for i in range(6)]
    assert counts==[9599433,100900,54635,200,0,233004]
    assert signature.hexdigest()=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert run['matched_original_terminal']==200 and run['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    data=sim.lib.gd_diag_native_method_profile_data;data.restype=ctypes.POINTER(ctypes.c_uint64)
    values=ctypes.cast(data(),ctypes.POINTER(ctypes.c_uint64*(15*65536))).contents
    overflow=sim.lib.gd_diag_native_method_profile_overflow;overflow.restype=ctypes.POINTER(ctypes.c_uint64)
    name=sim.lib.gd_diag_native_method_profile_name;name.argtypes=[ctypes.c_uint32];name.restype=ctypes.c_char_p
    rows=[]
    for index,value in enumerate(values):
        if value:
            kind,symbol=divmod(index,65536);label=name(symbol)
            rows.append(dict(receiver_kind=KINDS[kind],symbol=symbol,name=label.decode('utf8',errors='replace') if label else None,calls=value))
    rows.sort(key=lambda row:row['calls'],reverse=True)
    result=dict(passed=True,baseline_dll_sha256=EXPECTED,diagnostic_dll_sha256=sha(WORK/'diagnostic.dll'),
        semantic_only_not_for_timing_or_deployment=True,no_speed_claim=True,one_recompiled_normal_unit=1,
        identical_current_source_19_normal_objects_reused=True,all_layouts_unchanged=True,workers=1,fights=200,
        old_six_counts=counts,inputs_sha256=signature.hexdigest(),results_sha256=run['results_sha256'],
        method_counts=rows,overflow={kind:overflow()[i] for i,kind in enumerate(KINDS)},
        scope='Logical fallback invocations in a normal-object diagnostic DLL; release costs still require actual profiling and A/B')
    save('counts.json',result);print(json.dumps(dict(passed=True,total_calls=sum(row['calls'] for row in rows),top=rows[:22])),flush=True)

if __name__=='__main__':main()
