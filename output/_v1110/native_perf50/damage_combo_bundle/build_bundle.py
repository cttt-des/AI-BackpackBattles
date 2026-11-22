"""Build an isolated exact-type method cache against the backed-up deployment."""
import hashlib
import io
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import psutil

psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
REPO=WORK.parents[3]
BASE=STAGE/'sim_native/native_sim_cpp/native_sim'
ARCHIVE='fcfe317116882ad80e2dd59611c38c01690ba004'
BASE_SHA='3a9269887ace0ad9cd6dafdb9e0ee2a77b857b231f2a0d412888af2516e5b520'
sys.path.insert(0,str(STAGE))
from build_native_hot_lto import HOT_UNITS,build_dll,collect_profiles
from prototype_native_damage_combo_bundle import optimize

from resume_build import create_instrumented_exports

def digest(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def git(*args):return subprocess.check_output(['git',*args],cwd=REPO)
def save(name,data):(WORK/name).write_text(json.dumps(data,indent=2)+'\n',encoding='utf8',newline='\n')

def main():
    process=psutil.Process()
    save('live_build.json',{'pid':process.pid,'created':process.create_time(),'script':str(Path(__file__).resolve())})
    assert git('ls-remote','--exit-code','origin','refs/heads/codex/native-perf50-verified').decode().split()[0]==ARCHIVE
    assert digest(BASE/'libgdcore.dll')==digest(REPO/'dist/native_1_1_10/libgdcore.dll')==BASE_SHA
    assert hashlib.sha256(git('show',f'{ARCHIVE}:{(BASE/"libgdcore.dll").relative_to(REPO).as_posix()}')).hexdigest()==BASE_SHA
    files=sorted(p for p in BASE.rglob('*') if p.is_file() and (p.suffix in ('.cpp','.hpp') or p.name=='build_windows.py'))
    assert len(files)==704
    data=subprocess.check_output(['git','cat-file','--batch'],cwd=REPO,
        input=''.join(f'{ARCHIVE}:{p.relative_to(REPO).as_posix()}\n' for p in files).encode('utf8'))
    stream=io.BytesIO(data)
    for p in files:
        head=stream.readline().split();assert len(head)==3 and head[1]==b'blob'
        raw=stream.read(int(head[2]));assert stream.read(1)==b'\n' and raw==p.read_bytes(),p
    save('baseline_verified.json',{'archive_commit':ARCHIVE,'dll_sha256':BASE_SHA,'verified_source_files':704,
        'source_sha256':{p.relative_to(BASE).as_posix():digest(p) for p in files}})
    src=WORK/'bundle_src'
    shutil.copytree(BASE,src,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    design=optimize(src);save('transform.json',design)
    save('source_before_build.json',{p.relative_to(src).as_posix():digest(p) for p in src.rglob('*') if p.is_file()})
    objects=Path(tempfile.mkdtemp(prefix='native-damage-combo-'))
    (WORK/'bundle_objects.txt').write_text(str(objects),encoding='utf8')
    os.environ.update(NATIVE_SIM_OBJ=str(objects),MAKE='D:/mingw64/bin/mingw32-make.exe',NATIVE_SIM_CXX='D:/mingw64/bin/g++.exe')
    profile=objects/'pgo';profile.mkdir()
    print('Backed-up deployment and704 sources verified; full20/PGO18, max2 jobs',flush=True)
    definition,exports=create_instrumented_exports(objects)
    save('instrumented_export_policy.json',{'instrumentation_only':True,'exports':exports,'release_link_policy':'Original automatic export, unchanged'})
    instrumented=build_dll(src,objects/'instrumented.dll',2,(f'-fprofile-generate={profile.as_posix()}',),hot_units=HOT_UNITS,
        link_flags=('-Wl,--exclude-all-symbols',str(definition)))
    audit=objects/'audit_profile';audit.mkdir()
    subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/'inspect_variant.py'),'--dll',str(instrumented),'--out',str(WORK/'instrumented_audit.json')],check=True,
        env=dict(os.environ,GCOV_PREFIX=str(audit),GCOV_PREFIX_STRIP='99'))
    collect_profiles(instrumented,objects,profile,HOT_UNITS)
    for unit in HOT_UNITS:(objects/(unit+'.o')).unlink()
    print('Compiling profile-guided release',flush=True)
    dll=build_dll(src,objects/'release.dll',2,(f'-fprofile-use={profile.as_posix()}','-fprofile-partial-training','-fprofile-correction'),hot_units=HOT_UNITS)
    shutil.copyfile(dll,WORK/'bundle.dll');print('resolved',digest(WORK/'bundle.dll'),flush=True)
    assert json.loads((WORK/'source_before_build.json').read_bytes())=={p.relative_to(src).as_posix():digest(p) for p in src.rglob('*') if p.is_file()}
    save('fresh_profile_source.json',{'dll_sha256':digest(WORK/'bundle.dll'),'source_manifest_sha256':digest(WORK/'source_before_build.json'),'profile_training_and_release_source_identical':True,'hot_profiles_sha256':{name:digest(profile/(name+'.gcda')) for name in sorted(HOT_UNITS)},'full20_instrumentation_and18_release_hot_units':True,'floating_options_unchanged':True})
    subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/'validate_then_compare.py'),'--build-pid','0','--created','0'],check=True)

if __name__=='__main__':main()
