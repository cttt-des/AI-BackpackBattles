"""Rebuild an isolated semantic baseline with one extra optimizer option."""
import hashlib
import io
import json
import os
from pathlib import Path
import runpy
import shutil
import subprocess
import sys
import tempfile
import psutil

psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
REPO=WORK.parents[3]
BASE_SRC=WORK.parent/'cycles18/reverse_stack_names_src'
BASE_DLL=WORK.parent/'cycles18/reverse_stack_names.dll'
ACTIVE=STAGE/'sim_native/native_sim_cpp/native_sim'
ARCHIVE='76847e3b8fdafb469184aa813b714a9362241848'
BASE_SHA='7213d9466543beda9903471cc2ed381fb240d896abe739479e6c9029eb7bd560'
ACTIVE_SHA='58383a1158e951d7aae8b4d4c34df4d52332446156946d31a488f5dff323ec39'
sys.path.insert(0,str(STAGE))
from build_native_hot_lto import HOT_UNITS,build_dll,collect_profiles
from prototype_native_event_kernel import optimize
from optimize_native_build_config_dependencies import optimize as fix_build_dependencies

def digest(path):return hashlib.sha256(path.read_bytes()).hexdigest()
def git(*args):return subprocess.check_output(['git',*args],cwd=REPO)

def main():
    name='event_kernel'
    assert digest(BASE_DLL)==BASE_SHA
    assert digest(ACTIVE/'libgdcore.dll')==digest(REPO/'dist/native_1_1_10/libgdcore.dll')==ACTIVE_SHA
    assert git('ls-remote','--exit-code','origin','refs/heads/codex/native-perf50-verified').decode().split()[0]=='08e34adeeb38543477b99d00478dcb66eb45e677'
    assert hashlib.sha256(git('show',f'{ARCHIVE}:{BASE_DLL.relative_to(REPO).as_posix()}')).hexdigest()==BASE_SHA
    active_prefix=ACTIVE.relative_to(REPO)
    files=sorted(p for p in BASE_SRC.rglob('*') if p.is_file() and (p.suffix in ('.cpp','.hpp') or p.name=='build_windows.py'))
    assert len(files)==699
    source_map={}
    for path in files:
        relative=path.relative_to(BASE_SRC)
        source_map[relative.as_posix()]=(BASE_SRC/relative).relative_to(REPO).as_posix() if relative.as_posix()=='gen/shards/shard_02.cpp' else (active_prefix/relative).as_posix()
    raw=subprocess.run(['git','cat-file','--batch'],input=''.join(f'{ARCHIVE}:{source_map[p.relative_to(BASE_SRC).as_posix()]}\n' for p in files).encode('utf8'),capture_output=True,check=True,cwd=REPO)
    stream=io.BytesIO(raw.stdout);expected={}
    for path in files:
        header=stream.readline().split();assert len(header)==3 and header[1]==b'blob'
        data=stream.read(int(header[2]));assert stream.read(1)==b'\n' and path.read_bytes()==data,path
        expected[path.relative_to(BASE_SRC).as_posix()]=hashlib.sha256(data).hexdigest()
    receipt={'archive_commit':ARCHIVE,'experimental_baseline_dll_sha256':BASE_SHA,
             'active_runtime_unchanged_sha256':ACTIVE_SHA,'source_reader':'git cat-file --batch (raw objects)',
             'verified_sources':len(expected),'source_sha256':expected,'git_source_paths':source_map,
             'baseline_semantics':'2604 strict original and unchanged per-case hashes passed',
             'baseline_release_status':'withheld: raw 24-batch minimum 43.40 <50'}
    (WORK/'event_kernel_baseline_archive.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf8',newline='\n')
    source=WORK/(name+'_src')
    shutil.copytree(BASE_SRC,source,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    fix_build_dependencies(source)
    report=optimize(source)
    assert report and sum(report['methods'].values())>50
    (WORK/'event_kernel_transform.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf8',newline='\n')
    assert '-fdevirtualize-at-ltrans' not in (source/'build_windows.py').read_text('utf8')
    objects=Path(tempfile.mkdtemp(prefix='native-event-kernel-'))
    (WORK/(name+'_objects.txt')).write_text(str(objects),encoding='utf8')
    os.environ.update(NATIVE_SIM_OBJ=str(objects),MAKE='D:/mingw64/bin/mingw32-make.exe',NATIVE_SIM_CXX='D:/mingw64/bin/g++.exe')
    profile=objects/'pgo';profile.mkdir()
    print('Verified archived baseline DLL and all 699 source/config files; full20 PGO18, max2 jobs',flush=True)
    instrumented=build_dll(source,objects/'instrumented.dll',2,(f'-fprofile-generate={profile.as_posix()}',),hot_units=HOT_UNITS)
    audit_folder=objects/'audit_profile';audit_folder.mkdir()
    subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'inspect_native_event_kernel.py'),'--dll',str(instrumented),'--audit','--out',str(WORK/'event_kernel_instrumented_audit.json')],check=True,env=dict(os.environ,GCOV_PREFIX=str(audit_folder),GCOV_PREFIX_STRIP='99'))
    collect_profiles(instrumented,objects,profile,HOT_UNITS)
    for unit in HOT_UNITS:(objects/(unit+'.o')).unlink()
    print('Compiling profile-guided release',flush=True)
    dll=build_dll(source,objects/'release.dll',2,(f'-fprofile-use={profile.as_posix()}','-fprofile-partial-training','-fprofile-correction'),hot_units=HOT_UNITS)
    output=WORK/(name+'.dll');shutil.copyfile(dll,output)
    print(name,digest(output),flush=True)

if __name__=='__main__':main()
