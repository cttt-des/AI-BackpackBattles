"""Measure Buff operand domains/loop frequency, never throughput or release gains."""
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
ACCEPTED=STAGE/'native_perf50/container_builtins_bundle'
NORMAL=STAGE/'native_perf50/container_builtins_prototype'
WORK=STAGE/'native_perf50/buff_typed_assessment_20261126/workload_probe'
EXPECTED='5bd31fdc2ab2e4a556c63987de62b9541d5793752d67662cc4034a36bdd69ecc'
LABELS=['calls','amount_input_int','duration_input_float','reflect_input_bool','resist_iterations','amplify_iterations','reflect_iterations',
    'add_calls','add_both_int','sub_calls','sub_both_int','min_calls','min_both_int_small53','coerce_int_calls','coerce_input_int']
GLOBALS='''namespace {
static bool native_buff_probe_enabled=false;
static uint64_t native_buff_probe_counts[15]{};
static bool native_buff_probe_small(int64_t x){return uint64_t(x)+(UINT64_C(1)<<53)<=(UINT64_C(1)<<54);}
static gd::GdVal native_buff_probe_add(gd::BattleCtx& c,const gd::GdVal& a,const gd::GdVal& b){
 if(native_buff_probe_enabled){++native_buff_probe_counts[7];native_buff_probe_counts[8]+=a.kind==gd::GdVal::Kind::Int && b.kind==gd::GdVal::Kind::Int;}
 return gd::gd_add(c,a,b);
}
static gd::GdVal native_buff_probe_sub(const gd::GdVal& a,const gd::GdVal& b){
 if(native_buff_probe_enabled){++native_buff_probe_counts[9];native_buff_probe_counts[10]+=a.kind==gd::GdVal::Kind::Int && b.kind==gd::GdVal::Kind::Int;}
 return gd::gd_sub(a,b);
}
static gd::GdVal native_buff_probe_min(const gd::GdVal& a,const gd::GdVal& b){
 if(native_buff_probe_enabled){++native_buff_probe_counts[11];native_buff_probe_counts[12]+=a.kind==gd::GdVal::Kind::Int && b.kind==gd::GdVal::Kind::Int && native_buff_probe_small(a.i) && native_buff_probe_small(b.i);}
 return gd::gd_min(a,b);
}
static gd::GdVal native_buff_probe_coerce(const gd::GdVal& a){
 if(native_buff_probe_enabled){++native_buff_probe_counts[13];native_buff_probe_counts[14]+=a.kind==gd::GdVal::Kind::Int;}
 return gd::gd_coerce_int(a);
}
}
'''
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def save(n,d):(WORK/n).write_text(json.dumps(d,indent=2)+'\n',encoding='utf8')
def main():
    p=psutil.Process();p.nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    assert sha(BASE/'libgdcore.dll')==EXPECTED and not WORK.exists();WORK.mkdir()
    src=WORK/'source';shutil.copytree(ACCEPTED/'bundle_src',src)
    frozen=json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    assert frozen==json.loads((NORMAL/'transform.json').read_bytes())['source_sha256']
    assert all(sha(src/n)==v==sha(BASE/n) for n,v in frozen.items())
    path=src/'gen/shards/shard_00.cpp';t=path.read_text('utf8');signature='gd::GdVal Gd__gd_core__CoreBuff::fn_gainTemporary('
    a=t.index(signature);end=t.index('    }\n    gd::GdVal lv_amount',a);head=t[a:end]
    head=head.replace('        ++gd_ctx.native_event_counts[2];','        ++gd_ctx.native_event_counts[2];\n        if(native_buff_probe_enabled)++native_buff_probe_counts[0];',1)
    for name,kind,index in [('amount','Int',1),('duration','Float',2),('reflect','Bool',3)]:
        token=f'    lv_{name} = gd::gd_coerce_';i=head.index(token)
        head=head[:i]+f'    if(native_buff_probe_enabled)native_buff_probe_counts[{index}]+=lv_{name}.kind==gd::GdVal::Kind::{kind};\n'+head[i:]
    for variable,index in [('_t332',4),('_t335',5),('_t338',6)]:
        token=f'for (uint32_t {variable} = 0;';i=head.index(token);i=head.index('{\n',i)+2
        head=head[:i]+f'                    if(native_buff_probe_enabled)++native_buff_probe_counts[{index}];\n'+head[i:]
    for old,new in [('gd::gd_add(','native_buff_probe_add('),('gd::gd_sub(','native_buff_probe_sub('),
            ('gd::gd_min(','native_buff_probe_min('),('gd::gd_coerce_int(','native_buff_probe_coerce(')]:head=head.replace(old,new)
    t=t[:a]+GLOBALS+head+t[end:]
    t+='\nextern "C" void gd_diag_native_buff_work_reset(){std::memset(native_buff_probe_counts,0,sizeof(native_buff_probe_counts));native_buff_probe_enabled=true;}\nextern "C" const uint64_t* gd_diag_native_buff_work_counts(){return native_buff_probe_counts;}\n'
    path.write_text(t,encoding='utf8',newline='\n');assert all(sha(src/n)==v for n,v in frozen.items() if n!='gen/shards/shard_00.cpp')
    old=json.loads((NORMAL/'build.json').read_bytes())['objects_sha256'];previous=Path(json.loads((NORMAL/'live_semantic_build.json').read_bytes())['object_directory'])
    assert len(old)==20 and all(sha(previous/n)==v for n,v in old.items())
    root=Path(tempfile.mkdtemp(prefix='buff-work-counts-',dir=Path(os.environ['LOCALAPPDATA'])/'CodexNativeBuilds'));obj=root/'objects';obj.mkdir();scratch=root/'scratch';scratch.mkdir()
    os.environ.update(TEMP=str(scratch),TMP=str(scratch),TMPDIR=str(scratch));tempfile.tempdir=str(scratch)
    save('live_probe.json',dict(pid=p.pid,created=p.create_time(),objects=str(obj)))
    flags=runpy.run_path(str(src/'build_windows.py'))['COMMON'];compiler='D:/mingw64/bin/g++.exe'
    with (WORK/'compile_first.log').open('wb') as log:
        subprocess.run([compiler,*flags,'-c',str(path),'-o',str(obj/'shard_00.o')],stdout=log,stderr=subprocess.STDOUT,check=True)
        subprocess.run([compiler,*flags,'-shared','-static','-save-temps=obj','-o',str(obj/'libgdcore.dll'),
            *[str((obj if n=='shard_00.o' else previous)/n) for n in old]],stdout=log,stderr=subprocess.STDOUT,check=True)
    assert all(sha(previous/n)==v for n,v in old.items());shutil.copyfile(obj/'libgdcore.dll',WORK/'diagnostic.dll')
    from bench_native_corpus import load_simulator,prepare,select_cases,measure
    sim=load_simulator(WORK/'diagnostic.dll');sig=hashlib.sha256();jobs=list(prepare(sim,select_cases(200),sig))
    sim.lib.gd_diag_native_resolved_audit.argtypes=[ctypes.c_int];sim.lib.gd_diag_native_resolved_audit(1)
    f=sim.lib.gd_diag_native_resolved_stat;f.argtypes=[ctypes.c_uint];f.restype=ctypes.c_uint64
    before=[f(i) for i in range(6)];sim.lib.gd_diag_native_buff_work_reset();run=measure(sim,jobs,1,0,continuous=True)
    counts=[f(i)-before[i] for i in range(6)];assert counts==[9599433,100900,54635,200,0,233004]
    assert sig.hexdigest()=='d94b16d42cc88e9a3850a77c9360b9c4c4fdd676cb252e463044a903db2a5fef'
    assert run['matched_original_terminal']==200 and run['results_sha256']=='2e74b45caa87f7ee6ac72ffc35d98cc8db140b47031614d26542e183cef5d2c9'
    f=sim.lib.gd_diag_native_buff_work_counts;f.restype=ctypes.POINTER(ctypes.c_uint64);data={k:f()[i] for i,k in enumerate(LABELS)}
    result=dict(passed=True,baseline_dll_sha256=EXPECTED,diagnostic_dll_sha256=sha(WORK/'diagnostic.dll'),counts=data,
        fixed200_inputs_sha256=sig.hexdigest(),fixed200_results_sha256=run['results_sha256'],old_six_counts=counts,
        one_changed_normal_unit_19_verified_objects_reused=True,no_layout_changes=True,no_speed_claim=True,not_for_deployment=True)
    save('counts.json',result);print(json.dumps(result),flush=True)
if __name__=='__main__':main()
