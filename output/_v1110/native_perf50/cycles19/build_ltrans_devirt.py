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
from optimize_native_ltrans_devirt import optimize

def digest(path):return hashlib.sha256(path.read_bytes()).hexdigest()
def git(*args):return subprocess.check_output(['git',*args],cwd=REPO)

def main():
    name='ltrans_devirt'
    assert digest(BASE_DLL)==BASE_SHA
    assert digest(ACTIVE/'libgdcore.dll')==digest(REPO/'dist/native_1_1_10/libgdcore.dll')==ACTIVE_SHA
    assert git('ls-remote','--exit-code','origin','refs/heads/codex/native-perf50-verified').decode().split()[0]==ARCHIVE
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
    (WORK/'ltrans_devirt_baseline_archive.json').write_text(json.dumps(receipt,indent=2)+'\n',encoding='utf8',newline='\n')
    source=WORK/(name+'_src')
    shutil.copytree(BASE_SRC,source,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    optimize(source)
    changed=[name for name,sha in expected.items() if digest(source/name)!=sha]
    assert changed==['build_windows.py'],changed
    before={p:(p.read_bytes(),p.stat().st_mtime_ns) for p in source.rglob('*') if p.is_file()}
    optimize(source);assert before=={p:(p.read_bytes(),p.stat().st_mtime_ns) for p in before}
    base_config=runpy.run_path(str(BASE_SRC/'build_windows.py'))['COMMON']
    candidate_config=runpy.run_path(str(source/'build_windows.py'))['COMMON']
    base_flags=[x for x in base_config if x!=str(BASE_SRC)]
    candidate_flags=[x for x in candidate_config if x!=str(source)]
    assert [x for x in candidate_flags if x!='-fdevirtualize-at-ltrans']==base_flags
    assert '-ffp-contract=off' in candidate_flags and '-ffast-math' not in candidate_flags
    (WORK/'ltrans_devirt_design.json').write_text(json.dumps({
        'only_runtime_compiler_option_added':'-fdevirtualize-at-ltrans','base_flags':base_flags,'candidate_flags':candidate_flags,
        'cpp_and_hpp_bytes_identical_to_experimental_baseline':True,'self_dependency_fix':'build script edits invalidate object cache',
        'generator_idempotent_bytes_and_mtime':True,'fresh_compile_units':20,'fresh_pgo_units':18,
        'source':'https://gcc.gnu.org/onlinedocs/gcc-16.1.0/gcc/Optimize-Options.html#index-fdevirtualize-at-ltrans',
        'local_gcc_default':'disabled, queried with -O3 -flto=2 -Q --help=common',
        'default_runtime_and_generator_unchanged':True,
    },indent=2)+'\n',encoding='utf8',newline='\n')
    objects=Path(tempfile.mkdtemp(prefix='native-ltrans-devirt-'))
    (WORK/(name+'_objects.txt')).write_text(str(objects),encoding='utf8')
    os.environ.update(NATIVE_SIM_OBJ=str(objects),MAKE='D:/mingw64/bin/mingw32-make.exe',NATIVE_SIM_CXX='D:/mingw64/bin/g++.exe')
    profile=objects/'pgo';profile.mkdir()
    print('Verified archived baseline DLL and all 699 source/config files; full20 PGO18, max2 jobs',flush=True)
    instrumented=build_dll(source,objects/'instrumented.dll',2,(f'-fprofile-generate={profile.as_posix()}',),hot_units=HOT_UNITS)
    collect_profiles(instrumented,objects,profile,HOT_UNITS)
    for unit in HOT_UNITS:(objects/(unit+'.o')).unlink()
    print('Compiling profile-guided release',flush=True)
    dll=build_dll(source,objects/'release.dll',2,(f'-fprofile-use={profile.as_posix()}','-fprofile-partial-training','-fprofile-correction'),hot_units=HOT_UNITS)
    output=WORK/(name+'.dll');shutil.copyfile(dll,output)
    print(name,digest(output),flush=True)

if __name__=='__main__':main()
