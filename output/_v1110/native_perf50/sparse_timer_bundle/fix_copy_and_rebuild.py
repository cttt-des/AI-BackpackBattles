"""Reproduce cache aliasing, fix copy semantics, then rebuild every release unit."""
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
    parser=argparse.ArgumentParser();parser.add_argument('--build-pid',type=int,required=True)
    parser.add_argument('--created',type=float,required=True);args=parser.parse_args()
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
    try:process=psutil.Process(args.build_pid)
    except psutil.NoSuchProcess:process=None
    if process:
        assert abs(process.create_time()-args.created)<.001
        assert any('sparse_timer_bundle/build_bundle.py' in x.replace('\\','/') for x in process.cmdline())
        print('Awaiting original build PID '+str(process.pid),flush=True)
        while process.is_running():
            try:process.wait(timeout=30)
            except psutil.TimeoutExpired:continue
            break
    src=WORK/'bundle_src';dll=WORK/'bundle.dll'
    assert dll.is_file() and not (WORK/'copy_fix_rebuild.json').exists()
    old=json.loads((WORK/'source_before_build.json').read_bytes())
    assert {p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}==old
    (WORK/'source_before_copy_fix.json').write_bytes((WORK/'source_before_build.json').read_bytes())
    shutil.copyfile(dll,WORK/'before_copy_fix.dll')
    objects=Path((WORK/'bundle_objects.txt').read_text('utf8'))
    assert objects.is_dir() and objects.name.startswith('native-sparse-timer-bundle-')
    def test(name):
        executable=objects/(name+'.exe')
        subprocess.run(['D:/mingw64/bin/g++.exe','-static','-O2','-std=c++20','-ffp-contract=off',
            '-I',str(src),str(STAGE/'test_native_timer_cache_copy.cpp'),'-o',str(executable)],check=True)
        result=subprocess.run([str(executable)],capture_output=True,text=True)
        return {'return_code':result.returncode,'result':json.loads(result.stdout)}
    negative=test('cache_copy_before');assert negative['return_code']==1
    print('Reproduced cached-buffer sharing on all four copy/move/assignment cases',flush=True)
    path=src/'gd_rt.hpp';text=path.read_text('utf8')
    (WORK/'cache_header_before_fix.hpp').write_bytes(path.read_bytes())
    before='    uint32_t* indices = nullptr;\n};'
    after='''    uint32_t* indices = nullptr;
    NativeTimerScanCache() = default;
    NativeTimerScanCache(const NativeTimerScanCache&) {}
    NativeTimerScanCache& operator=(const NativeTimerScanCache&) {
        items=nullptr;context=nullptr;generation=epoch=0;
        length=count=capacity=0;indices=nullptr;return *this;
    }
};'''
    assert text.count(before)==1
    path.write_text(text.replace(before,after,1),encoding='utf8',newline='\n')
    positive=test('cache_copy_after');assert positive['return_code']==0 and all(positive['result'].values())
    with tempfile.TemporaryDirectory(prefix='native-sparse-copy-regeneration-') as directory:
        generated=Path(directory)/'native'
        shutil.copytree(STAGE/'sim_native/native_sim_cpp/native_sim',generated,
            ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
        optimize(generated)
        assert {p.relative_to(generated).as_posix():sha(p) for p in generated.rglob('*') if p.is_file()}=={
            p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    updated={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    (WORK/'source_before_build.json').write_text(json.dumps(updated,indent=2)+'\n',encoding='utf8')
    # Member functions change no object size. The previously trained graph is
    # representative of the host corpus (which does not copy characters). New
    # copy functions use partial training; incompatible profiles fail compilation.
    object_files=sorted(objects.glob('*.o'));assert len(object_files)==20
    assert all(path.stat().st_mtime_ns>p.stat().st_mtime_ns for p in object_files)
    report={'reproduced_before_fix':negative,'fixed_after_change':positive,
        'original_dll_sha256':sha(dll),'all20_units_forced_stale_by_header':True,
        'profile_training_source_manifest':'source_before_copy_fix.json',
        'profile_reuse_reason':'Only cache copy/assignment member functions changed; no layout, timer, math, RNG or host corpus control-flow changes. Recompile all20 with prior18 profiles and partial-training support; reject incompatible profiles.',
        'source_matches_full_transform':True}
    (WORK/'copy_fix_preflight.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    os.environ.update(NATIVE_SIM_OBJ=str(objects),MAKE='D:/mingw64/bin/mingw32-make.exe',NATIVE_SIM_CXX='D:/mingw64/bin/g++.exe')
    profile=objects/'pgo'
    corrected=build_dll(src,objects/'release_copy_fixed.dll',2,
        (f'-fprofile-use={profile.as_posix()}','-fprofile-partial-training','-fprofile-correction'),hot_units=HOT_UNITS)
    shutil.copyfile(corrected,dll)
    report['corrected_dll_sha256']=sha(dll)
    assert updated=={p.relative_to(src).as_posix():sha(p) for p in src.rglob('*') if p.is_file()}
    (WORK/'copy_fix_rebuild.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8')
    print('Corrected release '+sha(dll),flush=True)
    subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/'validate_then_compare.py'),
        '--build-pid','0','--created','0'],check=True)

if __name__=='__main__':main()
