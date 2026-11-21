"""Verify metadata pre-read counterexample, correct cold predicates, and rebuild."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import psutil
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
sys.path.insert(0,str(STAGE))
from build_native_hot_lto import HOT_UNITS,build_dll
from prototype_native_sparse_timer_bundle import optimize

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()

def main():
    parser=argparse.ArgumentParser();parser.add_argument('--copy-pid',type=int,required=True)
    parser.add_argument('--created',type=float,required=True);args=parser.parse_args()
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    process=None
    if args.copy_pid>0:
        try:process=psutil.Process(args.copy_pid)
        except psutil.NoSuchProcess:pass
    if process:
        assert abs(process.create_time()-args.created)<.001
        assert any('sparse_timer_bundle/fix_copy_and_rebuild.py' in x.replace('\\','/') for x in process.cmdline())
        print('Awaiting copy-fix build PID '+str(process.pid),flush=True)
        while process.is_running():
            try:process.wait(timeout=30)
            except psutil.TimeoutExpired:continue
            break
    assert (WORK/'copy_fix_rebuild.json').is_file()
    src=WORK/'bundle_src';dll=WORK/'bundle.dll'
    old=json.loads((WORK/'source_before_build.json').read_bytes())
    assert {p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}==old
    assert not (WORK/'metadata_purity_rebuild.json').exists()
    (WORK/'source_before_metadata_purity.json').write_bytes((WORK/'source_before_build.json').read_bytes())
    shutil.copyfile(dll,WORK/'before_metadata_purity.dll')
    objects=Path((WORK/'bundle_objects.txt').read_text('utf8'))
    assert objects.is_dir() and objects.name.startswith('native-sparse-timer-bundle-')
    executable=objects/'metadata_before.exe'
    shutil.copyfile(dll,objects/'libgdcore.dll')
    subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O2','-std=c++20','-ffp-contract=off',
        '-I',str(src),str(STAGE/'test_native_timer_metadata_purity.cpp'),str(objects/'libgdcore.dll'),'-o',str(executable)],check=True)
    negative=subprocess.run([str(executable)],capture_output=True,text=True)
    assert negative.returncode==1
    result=json.loads(negative.stdout);assert result['unexpected_meta_calls']>0
    print('Reproduced extra observable meta() call in old sparse precheck',flush=True)
    path=src/'gd_rt.cpp';text=path.read_text('utf8')
    anchor='''       !native_resolved_generated_class(type)) advance_native_scan_epoch();
}
'''
    addition='''void native_timer_scan_validity_probe(GdObj* object) {
    if(object && (!object->rt_ctx_ ||
       !native_resolved_cached_generated(*object->rt_ctx_,object))) advance_native_scan_epoch();
}
'''
    assert text.count(anchor)==1
    text=text.replace(anchor,anchor+addition,1)
    anchor='return instance != nullptr && method != SYM_NONE && instance->has_own_method(method);'
    assert text.count(anchor)==1
    text=text.replace(anchor,'return instance != nullptr && method != SYM_NONE && (native_timer_scan_validity_probe(instance), instance->has_own_method(method));',1)
    path.write_text(text,encoding='utf8',newline='\n')
    path=src/'gen/shards/shard_03.cpp';text=path.read_text('utf8')
    text=text.replace('native_scan_item','native_scan_item_exact').replace('native_scan_has_timers','native_scan_has_timers_exact')
    anchor='    if (!slot.obj->meta()->is_subclass_of(&META_Gd__gd_core__CoreItem)) return nullptr;'
    assert text.count(anchor)==1
    text=text.replace(anchor,'    if (!gd::native_resolved_cached_generated(battle,slot.obj)) return nullptr;\n'+anchor,1)
    text=text.replace('const Gd__gd_core__CoreItem* native_scan_item_exact(', '__attribute__((noinline)) const Gd__gd_core__CoreItem* native_scan_item_exact(')
    text=text.replace('bool native_scan_has_timers_exact(', '__attribute__((noinline)) bool native_scan_has_timers_exact(')
    path.write_text(text,encoding='utf8',newline='\n')
    with tempfile.TemporaryDirectory(prefix='native-sparse-purity-regeneration-') as directory:
        generated=Path(directory)/'native'
        shutil.copytree(STAGE/'sim_native/native_sim_cpp/native_sim',generated,
            ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
        optimize(generated)
        assert {p.relative_to(generated).as_posix():sha(p) for p in generated.rglob('*') if p.is_file()}=={
            p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    updated={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    (WORK/'source_before_build.json').write_text(json.dumps(updated,indent=2)+'\n',encoding='utf8')
    report={'negative_return_code':negative.returncode,'negative_result':result,
        'old_dll_sha256':sha(dll),'source_matches_full_transform':True,
        'changed_units':['gd_rt','shard_03'],
        'profile_policy':'Reuse compatible prior profiles; renamed cold predicate functions use partial training. A compiler coverage mismatch stops this run for explicit retraining.',
        'corrections':['unknown metadata is not called in eligibility pre-read','unknown FuncRef validity callbacks invalidate before execution','cold eligibility helpers kept out of hot loop footprint']}
    (WORK/'metadata_purity_preflight.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    os.environ.update(NATIVE_SIM_OBJ=str(objects),MAKE='D:/mingw64/bin/mingw32-make.exe',NATIVE_SIM_CXX='D:/mingw64/bin/g++.exe')
    profile=objects/'pgo'
    corrected=build_dll(src,objects/'release_metadata_fixed.dll',2,
        (f'-fprofile-use={profile.as_posix()}','-fprofile-partial-training','-fprofile-correction'),hot_units=HOT_UNITS)
    shutil.copyfile(corrected,dll)
    report['corrected_dll_sha256']=sha(dll)
    assert updated=={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    (WORK/'metadata_purity_rebuild.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/'validate_then_compare.py'),
        '--build-pid','0','--created','0'],check=True)

if __name__=='__main__':main()
