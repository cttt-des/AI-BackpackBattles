"""Back up retained combination evidence without replacing the verified runtime."""
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
PREVIOUS='53b16a2cbcd198db7201c73a48b34e1b7ad8fcd8'
BRANCH='refs/heads/codex/native-perf50-verified'
BASE_SHA='7af5ff948b949859339f0897a6d857953ae8e3b30ec451cee030672ba9c5129b'

def git(*args,env=None,input=None):
    return subprocess.check_output(['git',*args],cwd=REPO,env=env,input=input)

def main():
    assert not git('diff','--cached','--name-only').strip()
    assert git('ls-remote','--exit-code','origin',BRANCH).decode().split()[0]==PREVIOUS
    paths={p for p in WORK.iterdir() if p.is_file() and p.suffix in ('.py','.json','.txt','.log','.hpp') and not p.name.startswith('checkpoint')}
    manifest=json.loads((WORK/'regeneration_manifest.json').read_bytes())
    paths.update(WORK/'bundle_src'/r['path'] for r in manifest['files'])
    paths.update(p for p in (WORK/'before_runtime').rglob('*') if p.is_file())
    paths.update(p for p in (WORK.parent/'post_scan_bundle_profile').iterdir() if p.is_file())
    probe=WORK.parent/'scan_activity_probe'
    paths.update(p for p in probe.iterdir() if p.is_file() and p.suffix in ('.py','.json','.txt','.log','.hpp'))
    paths.update(probe/'scan_activity_src/gen/shards'/f'shard_{i:02d}.cpp' for i in (2,3))
    paths.update(STAGE/name for name in ('prototype_native_sparse_timer_bundle.py','test_native_sparse_timer_callbacks.cpp','test_native_timer_metadata_purity.cpp','test_native_timer_cache_copy.cpp','test_native_sparse_timers_seeded.cpp','test_native_scan_known_getters.cpp','test_native_sparse_timers.cpp','test_native_timer_scan_tracking.cpp','optimize_native_sparse_timers.py','optimize_native_inline_timers.py','optimize_native_serial_paths.py'))
    paths.add(REPO/'docs/C++模拟器性能优化清单.md')
    assert all(p.is_file() for p in paths)
    relative=sorted(p.relative_to(REPO).as_posix() for p in paths)
    git('-c','core.autocrlf=false','add','-f','--',*relative)
    assert set(x for x in git('diff','--cached','--name-only','-z').decode().split('\0') if x).issubset(relative)
    git('commit','-m','perf: retain sparse-timer package evidence and getter invalidation counterexample')
    local=git('rev-parse','HEAD').decode().strip()
    with tempfile.TemporaryDirectory(prefix='native-retained-variant-index-') as directory:
        env=dict(os.environ,GIT_INDEX_FILE=str(Path(directory)/'index'))
        git('read-tree',PREVIOUS,env=env)
        git('-c','core.autocrlf=false','add','-f','--',*relative,env=env)
        tree=git('write-tree',env=env).decode().strip()
    commit=git('commit-tree',tree,'-p',PREVIOUS,'-p',local,'-m','backup: retain measured variant trials and scan evidence').decode().strip()
    native=STAGE/'sim_native/native_sim_cpp/native_sim'
    files=sorted(p for p in native.rglob('*') if p.is_file() and (p.suffix in ('.cpp','.hpp') or p.name=='build_windows.py'))
    assert len(files)==704
    assert hashlib.sha256((native/'libgdcore.dll').read_bytes()).hexdigest()==BASE_SHA
    files.extend((native/'libgdcore.dll',REPO/'dist/native_1_1_10/libgdcore.dll',REPO/'dist/native_1_1_10/manifest.json'))
    files.extend(sorted(paths))
    stream=io.BytesIO(git('cat-file','--batch',input=''.join(f'{commit}:{p.relative_to(REPO).as_posix()}\n' for p in files).encode('utf8')))
    for p in files:
        header=stream.readline().split();assert len(header)==3 and header[1]==b'blob'
        assert stream.read(int(header[2]))==p.read_bytes(),p
        assert stream.read(1)==b'\n'
    subprocess.run(['git','push','origin',f'{commit}:{BRANCH}'],cwd=REPO,check=True)
    assert git('ls-remote','--exit-code','origin',BRANCH).decode().split()[0]==commit
    print(json.dumps({'local_commit':local,'remote_verified_commit':commit,
        'runtime_dll_sha256':BASE_SHA,'retained_trial_dll_sha256':manifest['candidate_dll_sha256'],
        'runtime_unchanged':True,'own_files_saved':len(relative),'production_source_files_verified':704}))

if __name__=='__main__':main()
