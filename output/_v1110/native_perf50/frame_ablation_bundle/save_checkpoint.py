"""Commit only this round and fast-forward the verified source/DLL backup."""
import hashlib
import io
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile

WORK=Path(__file__).resolve().parent
STAGE=WORK.parents[1]
REPO=STAGE.parents[1]
PREVIOUS='42be0c4610c7d93fc8eb0f260269e1ab9725613f'
BRANCH='refs/heads/codex/native-perf50-verified'

def git(*args,env=None):return subprocess.check_output(['git',*args],cwd=REPO,env=env)
def digest(data):return hashlib.sha256(data).hexdigest()

def add_paths(paths,env=None):
    # Thousands of per-case receipts exceed the Windows command-line limit.
    with tempfile.NamedTemporaryFile(prefix='native-verified-paths-',suffix='.txt',delete=False) as output:
        path=Path(output.name);output.write(b''.join(name.encode('utf8')+b'\0' for name in paths))
    try:git('-c','core.autocrlf=false','add','-f',f'--pathspec-from-file={path}','--pathspec-file-nul',env=env)
    finally:path.unlink()

def main():
    assert not git('diff','--cached','--name-only').strip(),'Retain preexisting staged work'
    assert git('ls-remote','--exit-code','origin',BRANCH).decode().split()[0]==PREVIOUS
    installation=json.loads((WORK/'bundle_installation.json').read_bytes())
    verified=json.loads((WORK/'post_install_verification.json').read_bytes())
    assert verified['passed'] and verified['strict_event_cases']==2604
    assert verified['dll_sha256']==installation['dll_sha256']==digest((WORK/'bundle.dll').read_bytes())
    manifest=json.loads((WORK/'regeneration_manifest.json').read_bytes())
    paths={p for p in WORK.iterdir() if p.is_file() and p.suffix in ('.py','.json','.txt','.log','.hpp') and not p.name.startswith('checkpoint')}
    paths.update((WORK/'bundle_src'/row['path']) for row in manifest['files'])
    paths.update(p for p in (WORK/'before_runtime').rglob('*') if p.is_file())
    paths.update(REPO/p for p in installation['changed_native_files'])
    paths.update(REPO/p for p in ('dist/native_1_1_10/libgdcore.dll','dist/native_1_1_10/manifest.json','docs/C++模拟器性能优化清单.md'))
    paths.add(WORK/'bundle.dll')
    paths.update(STAGE/p for p in ('native_lazy_diagnostics.hpp','prepare_native_lazy_diagnostics.py','prepare_native_buff_diagnostics.py','test_native_lazy_diagnostics.cpp','test_native_buff_diagnostics.cpp','probe_native_lazy_diagnostics.py','probe_native_buff_diagnostics.py','snapshot_label_diagnostic_screen.py','prototype_native_frame_ablation_bundle.py','setup_frame_ablation_bundle.py','preflight_native_lazy_bundle.py'))
    paths.update(p for p in (WORK.parent/'lazy_diagnostics_probe').iterdir() if p.is_file())
    paths.update(STAGE/p for p in ('prototype_native_frame_ablation_bundle.py','preflight_native_member_frame.py','setup_frame_ablation_bundle.py','test_native_member_fields.cpp','test_native_frame_segments.cpp'))
    paths.update(STAGE/p for p in ('prototype_native_member_frame_bundle.py','setup_member_frame_bundle.py','test_native_frame_cost.cpp','probe_native_frame_cost.py'))
    prior=WORK.parent/'member_frame_bundle'
    paths.update(p for p in prior.iterdir() if p.is_file())
    paths.update(p for p in (prior/'bundle_src').rglob('*') if p.is_file())
    paths.update(STAGE/p for p in ('prototype_native_frame_ablation_bundle.py','setup_frame_ablation_bundle.py'))
    audit=json.loads((WORK/'full_type_audit.json').read_bytes())
    for root in map(Path,audit['receipts']):
        paths.update(root/name for name in ('native_resolved_audit.json','native_type_audit.json','native_property_audit.json','native_type_constructor_audit.json','native_hot_slot_audit.json','native_event_identity_audit.json','native_lazy_diagnostic_audit.json','summary.json'))
    # Preserve per-case event hashes for this comparison and its actual baseline.
    for root in map(Path,audit['receipts']):paths.update(root.glob('*.json'))
    relative=sorted(p.relative_to(REPO).as_posix() for p in paths)
    missing=[p for p in relative if not (REPO/p).is_file()]
    assert not missing,missing
    if '--check-only' in sys.argv:
        print(json.dumps({'paths':len(relative),'missing':missing,'dll_sha256':installation['dll_sha256']}))
        return
    # Preserve raw bytes, including pinned JSON report hashes and DLL manifests.
    add_paths(relative)
    staged=git('diff','--cached','--name-only','-z').decode().split('\0')
    assert set(p for p in staged if p).issubset(relative)
    git('commit','-m','perf: deploy equivalent callback-bounded character state reuse')
    local=git('rev-parse','HEAD').decode().strip()
    with tempfile.TemporaryDirectory(prefix='native-dispatch-array-backup-') as directory:
        env=dict(os.environ,GIT_INDEX_FILE=str(Path(directory)/'index'))
        git('read-tree',PREVIOUS,env=env)
        add_paths(relative,env=env)
        tree=git('write-tree',env=env).decode().strip()
    commit=git('commit-tree',tree,'-p',PREVIOUS,'-p',local,'-m','backup: preserve verified event identities and the complete path review').decode().strip()
    native=STAGE/'sim_native/native_sim_cpp/native_sim'
    source=[p for p in native.rglob('*') if p.is_file() and (p.suffix in ('.cpp','.hpp') or p.name=='build_windows.py')]
    assert len(source)==704
    checked=sorted(set(source)|{REPO/path for path in relative}|{native/'libgdcore.dll'})
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
