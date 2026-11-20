"""Save retained trials while keeping the verified deployment unchanged."""
import argparse
import hashlib
import io
import json
import os
from pathlib import Path
import subprocess
import tempfile

WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
REPO=STAGE.parents[1]
BRANCH='refs/heads/codex/native-perf50-verified'
def git(*args,env=None,input=None):return subprocess.check_output(['git',*args],cwd=REPO,env=env,input=input)

def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--previous',required=True)
    args=parser.parse_args();previous=args.previous
    assert not git('diff','--cached','--name-only').strip()
    assert git('ls-remote','--exit-code','origin',BRANCH).decode().split()[0]==previous
    paths={p for p in WORK.iterdir() if p.is_file() and p.suffix in ('.py','.json','.txt','.log') and not p.name.startswith('checkpoint')}
    manifest=json.loads((WORK/'regeneration_manifest.json').read_bytes())
    paths.update(WORK/'bundle_src'/r['path'] for r in manifest['files'])
    paths.update(p for p in (WORK/'before_runtime').rglob('*') if p.is_file())
    paths.update(p for p in (WORK.parent/'post_dispatch_array_profile').iterdir() if p.is_file())
    paths.update(WORK.parent/'dispatch_array_bundle'/name for name in ('checkpoint.log','post_profile.log','post_profile_retry.log'))
    paths.update(STAGE/name for name in ('profile_native_windows.py','prototype_native_scalar_array_bundle.py','test_native_scalar_array.cpp'))
    paths.add(REPO/'docs/C++模拟器性能优化清单.md')
    relative=sorted(p.relative_to(REPO).as_posix() for p in paths)
    git('-c','core.autocrlf=false','add','-f','--',*relative)
    assert set(x for x in git('diff','--cached','--name-only','-z').decode().split('\0') if x).issubset(relative)
    git('commit','-m','perf: retain small scalar-array gains for further composition')
    local=git('rev-parse','HEAD').decode().strip()
    with tempfile.TemporaryDirectory(prefix='native-retained-trials-index-') as directory:
        env=dict(os.environ,GIT_INDEX_FILE=str(Path(directory)/'index'))
        git('read-tree',previous,env=env)
        git('-c','core.autocrlf=false','add','-f','--',*relative,env=env)
        tree=git('write-tree',env=env).decode().strip()
    commit=git('commit-tree',tree,'-p',previous,'-p',local,'-m','backup: retain composite trials alongside verified runtime').decode().strip()
    native=STAGE/'sim_native/native_sim_cpp/native_sim'
    files=sorted(p for p in native.rglob('*') if p.is_file() and (p.suffix in ('.cpp','.hpp') or p.name=='build_windows.py'))
    assert len(files)==702
    files.extend((native/'libgdcore.dll',REPO/'dist/native_1_1_10/libgdcore.dll',REPO/'dist/native_1_1_10/manifest.json'))
    stream=io.BytesIO(git('cat-file','--batch',input=''.join(f'{commit}:{p.relative_to(REPO).as_posix()}\n' for p in files).encode('utf8')))
    for p in files:
        header=stream.readline().split();assert len(header)==3 and header[1]==b'blob'
        assert stream.read(int(header[2]))==p.read_bytes(),p
        assert stream.read(1)==b'\n'
    subprocess.run(['git','push','origin',f'{commit}:{BRANCH}'],cwd=REPO,check=True)
    assert git('ls-remote','--exit-code','origin',BRANCH).decode().split()[0]==commit
    print(json.dumps({'local_commit':local,'remote_verified_commit':commit,
        'runtime_dll_sha256':hashlib.sha256((native/'libgdcore.dll').read_bytes()).hexdigest(),
        'retained_trial_dll_sha256':json.loads((WORK/'ab_assessment.json').read_bytes())['candidate_dll_sha256'],
        'runtime_unchanged':True,'own_files_saved':len(relative)}))

if __name__=='__main__':main()
