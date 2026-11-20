"""Build three compatible micro-optimizations on the verified native event chain."""
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
BASE=WORK.parent/'native_event_kernel_a'
SOURCE=BASE/'event_kernel_src'
ARCHIVE='a5b108d2b60860d27aff564ac78013707e5600c6'
BASE_SHA='2b48ccf3526da880ce905f163b771d84462a90c52cc83f7ada181c7c8e62f521'
ACTIVE_SHA='58383a1158e951d7aae8b4d4c34df4d52332446156946d31a488f5dff323ec39'
HEADER_SHA='01c0ea5c56e25e96a06da6e2b8c65d370cc7ea52b012d0f91878401e7cf22a3c'
sys.path.insert(0,str(STAGE))
from build_native_hot_lto import HOT_UNITS,build_dll,collect_profiles
import optimize_native_arena_split as arena
from optimize_native_dict_indices import optimize as optimize_dict
from optimize_native_label_ranges import optimize as optimize_labels

def digest(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def git(*args):return subprocess.check_output(['git',*args],cwd=REPO)
def save(name,data):(WORK/name).write_text(json.dumps(data,indent=2)+'\n',encoding='utf8',newline='\n')

def main():
    assert git('ls-remote','--exit-code','origin','refs/heads/codex/native-perf50-verified').decode().split()[0]==ARCHIVE
    assert digest(BASE/'event_kernel.dll')==BASE_SHA
    assert hashlib.sha256(git('show',f'{ARCHIVE}:{(BASE/"event_kernel.dll").relative_to(REPO).as_posix()}')).hexdigest()==BASE_SHA
    active=STAGE/'sim_native/native_sim_cpp/native_sim'
    assert digest(active/'libgdcore.dll')==digest(REPO/'dist/native_1_1_10/libgdcore.dll')==ACTIVE_SHA
    record=json.loads((BASE/'event_kernel_installation.json').read_bytes())
    changed=set(record['isolated_changed_source_files'])
    files=sorted(p for p in SOURCE.rglob('*') if p.is_file() and (p.suffix in ('.cpp','.hpp') or p.name=='build_windows.py'))
    assert len(files)==700
    mapping={p.relative_to(SOURCE).as_posix():p.relative_to(REPO).as_posix() if p.relative_to(REPO).as_posix() in changed else (active/p.relative_to(SOURCE)).relative_to(REPO).as_posix() for p in files}
    data=subprocess.check_output(['git','cat-file','--batch'],
        input=''.join(f'{ARCHIVE}:{mapping[p.relative_to(SOURCE).as_posix()]}\n' for p in files).encode('utf8'),cwd=REPO)
    stream=io.BytesIO(data)
    for p in files:
        head=stream.readline().split();assert len(head)==3 and head[1]==b'blob'
        raw=stream.read(int(head[2]));assert stream.read(1)==b'\n' and raw==p.read_bytes(),p
    save('baseline_verified.json',{'archive_commit':ARCHIVE,'dll_sha256':BASE_SHA,'verified_source_files':len(files),
         'source_map':mapping,'source_sha256':{p.relative_to(SOURCE).as_posix():digest(p) for p in files},'active_dll_unchanged_sha256':ACTIVE_SHA})
    src=WORK/'bundle_src'
    shutil.copytree(SOURCE,src,ignore=shutil.ignore_patterns('*.dll','*.o','*.gcda','*.gcno','__pycache__'))
    path=src/'gd_rt.hpp';text=path.read_text('utf8');assert digest(path)==HEADER_SHA
    # Verify the old allocation code's surrounding header after accounting only
    # for the accepted event-kernel fields. Keep those fields in the new header.
    flags='    bool native_event_kernel = false;\n    bool native_event_audit = false;\n    uint64_t native_event_counts[5]{};\n'
    reset='        native_event_kernel = false;\n'
    assert text.count(flags)==1 and text.count(reset)==1
    old_header=text.replace(flags,'',1).replace(reset,'',1)
    assert hashlib.sha256(old_header.encode()).hexdigest()==arena.INPUT_SHA256
    transformed=arena.transform(text)
    assert arena.normalize(transformed)==text and arena.transform(transformed)==transformed
    path.write_text(transformed,encoding='utf8',newline='\n')
    optimize_dict(src)
    optimize_labels(src)
    modifications=[p.relative_to(src).as_posix() for p in src.rglob('*') if p.is_file() and
        (p.suffix in ('.cpp','.hpp') or p.name=='build_windows.py') and p.read_bytes()!=(SOURCE/p.relative_to(src)).read_bytes()]
    assert set(modifications)=={'gd_rt.hpp','gd_rt.cpp','gen/shards/shard_00.cpp'}
    for test in ('test_native_arena_split.cpp','test_native_dict_indices.cpp','test_native_label_ranges.cpp'):
        assert (STAGE/test).is_file(),test
    save('transform.json',{'bundle':['arena growth/locking outline','stored integer dictionary index','label integer iteration'],
        'base_dll_sha256':BASE_SHA,'changed_files':modifications,'header_normalization_to_accepted_baseline':True,
        'fixed_frames_fp_rng_and_callbacks':'unchanged','source_sha256':{p.relative_to(src).as_posix():digest(p) for p in src.rglob('*') if p.is_file()}})
    objects=Path(tempfile.mkdtemp(prefix='native-arena-dict-labels-'))
    (WORK/'bundle_objects.txt').write_text(str(objects),encoding='utf8')
    os.environ.update(NATIVE_SIM_OBJ=str(objects),MAKE='D:/mingw64/bin/mingw32-make.exe',NATIVE_SIM_CXX='D:/mingw64/bin/g++.exe')
    profile=objects/'pgo';profile.mkdir()
    print('Archived baseline and 700 files verified; building full20/PGO18, max2 jobs',flush=True)
    instrumented=build_dll(src,objects/'instrumented.dll',2,(f'-fprofile-generate={profile.as_posix()}',),hot_units=HOT_UNITS)
    audit=objects/'audit_profile';audit.mkdir()
    subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'inspect_native_event_kernel.py'),'--dll',str(instrumented),'--audit','--out',str(WORK/'instrumented_audit.json')],check=True,
        env=dict(os.environ,GCOV_PREFIX=str(audit),GCOV_PREFIX_STRIP='99'))
    collect_profiles(instrumented,objects,profile,HOT_UNITS)
    for unit in HOT_UNITS:(objects/(unit+'.o')).unlink()
    print('Compiling profile-guided release',flush=True)
    dll=build_dll(src,objects/'release.dll',2,(f'-fprofile-use={profile.as_posix()}','-fprofile-partial-training','-fprofile-correction'),hot_units=HOT_UNITS)
    shutil.copyfile(dll,WORK/'bundle.dll')
    print('bundle',digest(WORK/'bundle.dll'),flush=True)

if __name__=='__main__':main()
