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
PREVIOUS='60963d0804db5dc01a5cace6d3fe56c658bfae13'
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
    manifest=json.loads((WORK/'regeneration_manifest.json').read_bytes())
    paths={p for p in WORK.iterdir() if p.is_file() and p.suffix in ('.py','.json','.txt','.log','.hpp') and not p.name.startswith('checkpoint')}
    paths.update((WORK/'bundle_src'/row['path']) for row in manifest['files'])
    paths.update(p for p in (WORK/'before_runtime').rglob('*') if p.is_file())
    paths.update(REPO/p for p in installation['changed_native_files'])
    paths.update(REPO/p for p in ('dist/native_1_1_10/libgdcore.dll','dist/native_1_1_10/manifest.json','docs/C++模拟器性能优化清单.md'))
    paths.add(WORK/'bundle.dll')
    paths.update(STAGE/p for p in ('prototype_native_event_identity_bundle.py','analyze_native_typed_reads.py','setup_event_identity_bundle.py','setup_typed_read_qualification.py','test_native_typed_reads.cpp'))
    paths.update(p for p in (WORK.parent/'post_hot_coverage_profile').iterdir() if p.is_file())
    paths.update(STAGE/p for p in ('event_identity_fastpath.hpp','event_identity_receiver_fastpath.hpp','test_native_event_identity.cpp','test_native_event_identity_bus.cpp','probe_native_event_identity.py','probe_native_event_identity_bus.py','prepare_event_identity_preflight.py','prototype_native_frame_segments_bundle.py','setup_frame_segments_bundle.py','run_frame_segments_preflight.py','test_native_frame_segments.cpp','test_native_timer_chunks.cpp','prototype_native_scalar_math_bundle.py','setup_scalar_math_bundle.py','setup_scalar_math_qualification.py','test_native_numeric_math.cpp','prototype_native_scalar_math_ordered_bundle.py','setup_scalar_math_ordered_bundle.py','test_native_numeric_math_ordered.cpp','test_native_nan_order.cpp','optimize_native_ordered_nan.py','prototype_native_typed_read_bundle.py','setup_typed_read_bundle.py'))
    for label in ('event_identity_probe','frame_segments_bundle','typed_read_bundle','scalar_math_bundle','scalar_math_ordered_bundle'):
        prior=WORK.parent/label
        paths.update(p for p in prior.iterdir() if p.is_file())
        paths.update(p for p in (prior/'bundle_src').rglob('*') if p.is_file())
    audit=json.loads((WORK/'full_type_audit.json').read_bytes())
    for root in map(Path,audit['receipts']):
        paths.update(root/name for name in ('native_resolved_audit.json','native_type_audit.json','native_property_audit.json','native_type_constructor_audit.json','native_hot_slot_audit.json','native_event_identity_audit.json','summary.json'))
    # Preserve per-case event hashes for this comparison and its actual baseline.
    for root in map(Path,audit['receipts']):paths.update(root.glob('*.json'))
    relative=sorted(p.relative_to(REPO).as_posix() for p in paths)
    assert all((REPO/p).is_file() for p in relative)
    # Preserve raw bytes, including pinned JSON report hashes and DLL manifests.
    add_paths(relative)
    staged=git('diff','--cached','--name-only','-z').decode().split('\0')
    assert set(p for p in staged if p).issubset(relative)
    git('commit','-m','perf: construct event emitter identities once with strict replay validation')
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
