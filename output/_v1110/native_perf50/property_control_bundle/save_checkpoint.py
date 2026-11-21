"""Commit only this round and fast-forward the verified source/DLL backup."""
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
PREVIOUS='ccecb628a9e36e05e6491b6fd1bfbe3a47d0af1e'
BRANCH='refs/heads/codex/native-perf50-verified'

def git(*args,env=None):return subprocess.check_output(['git',*args],cwd=REPO,env=env)
def digest(data):return hashlib.sha256(data).hexdigest()

def main():
    assert not git('diff','--cached','--name-only').strip(),'Retain preexisting staged work'
    assert git('ls-remote','--exit-code','origin',BRANCH).decode().split()[0]==PREVIOUS
    installation=json.loads((WORK/'bundle_installation.json').read_bytes())
    manifest=json.loads((WORK/'regeneration_manifest.json').read_bytes())
    paths={p for p in WORK.iterdir() if p.is_file() and p.suffix in ('.py','.json','.txt','.log','.hpp') and not p.name.startswith('checkpoint')}
    paths.update((WORK/'bundle_src'/row['path']) for row in manifest['files'])
    paths.update(p for p in (WORK/'before_runtime').rglob('*') if p.is_file())
    paths.update(p for p in (WORK.parent/'post_eager_trace_profile').iterdir() if p.is_file())
    paths.update(REPO/p for p in installation['changed_native_files'])
    paths.update(REPO/p for p in ('dist/native_1_1_10/libgdcore.dll','dist/native_1_1_10/manifest.json','docs/C++模拟器性能优化清单.md'))
    paths.update(STAGE/p for p in ('prototype_native_eager_trace_bundle.py','prototype_native_addspeed_trace.py','test_native_eager_rows.cpp','test_native_addspeed_trace.cpp','setup_eager_trace_bundle.py','setup_item_locality_bundle.py','prototype_native_item_locality_bundle.py','test_native_item_locality.cpp','test_native_all_layouts.cpp','prototype_native_property_control_bundle.py','prototype_native_hot_control_bundle.py','setup_property_control_bundle.py','test_native_properties.cpp'))
    audit=json.loads((WORK/'full_type_audit.json').read_bytes())
    for root in map(Path,audit['receipts']):
        paths.update(root/name for name in ('native_resolved_audit.json','native_type_audit.json','native_property_audit.json','summary.json'))
    relative=sorted(p.relative_to(REPO).as_posix() for p in paths)
    assert all((REPO/p).is_file() for p in relative)
    # Preserve raw bytes, including pinned JSON report hashes and DLL manifests.
    git('-c','core.autocrlf=false','add','-f','--',*relative)
    staged=git('diff','--cached','--name-only','-z').decode().split('\0')
    assert set(p for p in staged if p).issubset(relative)
    git('commit','-m','perf: deploy pure property rows and compact controls with full replay validation')
    local=git('rev-parse','HEAD').decode().strip()
    with tempfile.TemporaryDirectory(prefix='native-dispatch-array-backup-') as directory:
        env=dict(os.environ,GIT_INDEX_FILE=str(Path(directory)/'index'))
        git('read-tree',PREVIOUS,env=env)
        git('-c','core.autocrlf=false','add','-f','--',*relative,env=env)
        tree=git('write-tree',env=env).decode().strip()
    commit=git('commit-tree',tree,'-p',PREVIOUS,'-p',local,'-m','backup: preserve verified property cache and compact controls').decode().strip()
    native=STAGE/'sim_native/native_sim_cpp/native_sim'
    source=[p for p in native.rglob('*') if p.is_file() and (p.suffix in ('.cpp','.hpp') or p.name=='build_windows.py')]
    assert len(source)==704
    checked=[*source,native/'libgdcore.dll',REPO/'dist/native_1_1_10/libgdcore.dll',WORK/'bundle_full_gate.json',WORK/'bundle_serial.json',REPO/'dist/native_1_1_10/manifest.json']
    data=subprocess.check_output(['git','cat-file','--batch'],cwd=REPO,input=''.join(f'{commit}:{p.relative_to(REPO).as_posix()}\n' for p in checked).encode('utf8'))
    stream=io.BytesIO(data)
    for path in checked:
        header=stream.readline().split();assert len(header)==3 and header[1]==b'blob'
        assert stream.read(int(header[2]))==path.read_bytes(),path
        assert stream.read(1)==b'\n'
    subprocess.run(['git','push','origin',f'{commit}:{BRANCH}'],cwd=REPO,check=True)
    assert git('ls-remote','--exit-code','origin',BRANCH).decode().split()[0]==commit
    print(json.dumps({'local_commit':local,'remote_verified_commit':commit,
        'source_files_verified':len(source),'dll_sha256':installation['dll_sha256'],'own_files_saved':len(relative)}))

if __name__=='__main__':main()
