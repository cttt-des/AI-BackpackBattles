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
ARCHIVE='42be0c4610c7d93fc8eb0f260269e1ab9725613f'
BASE_SHA='6cb258ec1baf335d3bc8e9da1538b2edd8aee87669b05249728f4829b1c47785'
sys.path.insert(0,str(STAGE))
from build_native_hot_lto import HOT_UNITS,build_dll,collect_profiles
from prototype_native_frame_ablation_bundle import optimize

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
    prior=WORK.parent/'member_frame_bundle'
    expected=json.loads((prior/'source_before_build.json').read_bytes())
    assert expected==json.loads((WORK/'source_before_build.json').read_bytes())
    assert expected=={p.relative_to(prior/'bundle_src').as_posix():digest(p) for p in (prior/'bundle_src').rglob('*') if p.is_file()}
    (WORK/'source_before_build.json').write_bytes((prior/'source_before_build.json').read_bytes())
    assert digest(prior/'bundle.dll')=='d3c47cdfe1b3218e7936cc02f706e8452464c1420c5e1fe4bf6963f2e3844c14'
    profile=json.loads((prior/'fresh_profile_source.json').read_bytes())
    assert profile['dll_sha256']==digest(prior/'bundle.dll') and profile['source_manifest_sha256']==digest(WORK/'source_before_build.json')
    assert profile['profile_training_and_release_source_identical'] and profile['floating_options_unchanged']
    shutil.copyfile(prior/'bundle.dll',WORK/'bundle.dll')
    save('fresh_profile_source.json',profile)
    save('candidate_reuse_proof.json',{'passed':True,'dll_sha256':digest(WORK/'bundle.dll'),'source_files':len(expected),
        'all_cpp_and_runtime_source_bytes_equal_to_original_compiled_candidate':True,
        'same_original_source_identical_fresh_PGO_reused':True,'no_new_compilation_or_PGO':True,
        'incremental_baseline_dll_sha256':BASE_SHA,'original_comparison_baseline':'593acaf3',
        'reason':'Directly isolate frame reuse relative to newly deployed member reads; no whole-DLL recompilation when every source byte is identical.'})
    print('Reused exactly matched original candidate and PGO; validating before incremental AB/BA',flush=True)
    subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/'validate_then_compare.py'),'--build-pid','0','--created','0'],check=True)

if __name__=='__main__':main()
