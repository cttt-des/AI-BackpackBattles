"""Archive this round's complete negative evidence without changing the accepted runtime."""
import hashlib
import io
import json
import os
from pathlib import Path
import subprocess
import tempfile

STAGE=Path(__file__).resolve().parent
REPO=STAGE.parents[1]
WORK=STAGE/'native_perf50/frame_proof_bundle'
PREVIOUS='1b18298e39ed36f0fd0dbe5d0e00699d9407c643'
BRANCH='refs/heads/codex/native-perf50-verified'
BASE='e0bedc4960077407e85763cb5e4af70175a0623cca15e923403fa89174390687'

def git(*args,env=None):return subprocess.check_output(['git',*args],cwd=REPO,env=env)
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def add(paths,env=None):
    with tempfile.NamedTemporaryFile(prefix='native-rejected-event-paths-',suffix='.txt',delete=False) as f:
        p=Path(f.name);f.write(b''.join(n.encode('utf8')+b'\0' for n in paths))
    try:git('-c','core.autocrlf=false','add','-f',f'--pathspec-from-file={p}','--pathspec-file-nul',env=env)
    finally:p.unlink()

def main():
    assert not git('diff','--cached','--name-only').strip()
    assert git('ls-remote','--exit-code','origin',BRANCH).decode().split()[0]==PREVIOUS
    rejection=json.loads((WORK/'rejection_receipt.json').read_bytes())
    assert rejection['selected_pairs']==32 and rejection['no_more_same_source_comparisons']
    assert rejection['main_thread_cpu_time_reduction_pct']<0
    native=STAGE/'sim_native/native_sim_cpp/native_sim'
    assert sha(native/'libgdcore.dll')==sha(REPO/'dist/native_1_1_10/libgdcore.dll')==BASE
    frozen=json.loads((WORK.parent/'grid_cooldown_bundle/source_before_build.json').read_bytes())
    source=[p for p in native.rglob('*') if p.is_file() and (p.suffix in ('.cpp','.hpp') or p.name=='build_windows.py')]
    assert len(source)==707 and all(sha(p)==frozen[p.relative_to(native).as_posix()] for p in source)
    paths=set()
    for folder in ('frame_proof_prototype','frame_proof_bundle'):
        paths.update(p for p in (WORK.parent/folder).rglob('*') if p.is_file() and '__pycache__' not in p.parts and not p.name.startswith('checkpoint'))
    paths.update(STAGE/name for name in ('prepare_native_frame_proof.py','setup_native_frame_proof_checks.py',
        'build_native_frame_proof_prototype.py','test_native_frame_proof.cpp','verify_native_frame_proof.py',
        'prototype_native_frame_proof_bundle.py','setup_frame_proof_bundle.py','preflight_native_frame_proof_bundle.py',
        'close_frame_proof_round.py','archive_frame_proof_round.py','save_rejected_frame_proof.py'))
    paths.update(STAGE.glob('native_frame_proof*.log'))
    paths.update(REPO/'docs'/name for name in ('C++模拟器下一阶段优化评估.md','C++模拟器性能优化清单.md'))
    relative=sorted(p.relative_to(REPO).as_posix() for p in paths)
    assert all((REPO/p).is_file() for p in relative)
    add(relative)
    staged={p for p in git('diff','--cached','--name-only','-z').decode().split('\0') if p}
    assert staged and staged.issubset(relative)
    git('commit','-m','perf: retain complete inconclusive32 tick-proof trials')
    local=git('rev-parse','HEAD').decode().strip()
    with tempfile.TemporaryDirectory(prefix='native-rejected-event-index-') as directory:
        env=dict(os.environ,GIT_INDEX_FILE=str(Path(directory)/'index'))
        git('read-tree',PREVIOUS,env=env);add(relative,env=env)
        tree=git('write-tree',env=env).decode().strip()
    commit=git('commit-tree',tree,'-p',PREVIOUS,'-p',local,'-m',
        'backup: retain inconclusive tick-proof trials; keep verified e0bedc runtime').decode().strip()
    checked=sorted(set(source)|paths|{native/'libgdcore.dll',REPO/'dist/native_1_1_10/libgdcore.dll'})
    data=subprocess.check_output(['git','cat-file','--batch'],cwd=REPO,
        input=''.join(f'{commit}:{p.relative_to(REPO).as_posix()}\n' for p in checked).encode('utf8'))
    stream=io.BytesIO(data)
    for p in checked:
        head=stream.readline().split();assert len(head)==3 and head[1]==b'blob',p
        assert stream.read(int(head[2]))==p.read_bytes() and stream.read(1)==b'\n',p
    subprocess.run(['git','push','origin',f'{commit}:{BRANCH}'],cwd=REPO,check=True)
    assert git('ls-remote','--exit-code','origin',BRANCH).decode().split()[0]==commit
    report=dict(local_commit=local,remote_verified_commit=commit,source_files_verified=707,
        unchanged_runtime_dll_sha256=BASE,rejected_candidate_dll_sha256=rejection['candidate_dll_sha256'],
        own_files_saved=len(relative),all_source_and_artifact_bytes_verified=True,user_existing_changes_not_staged=True)
    out=WORK/'checkpoint_rejection_receipt.json';assert not out.exists()
    out.write_text(json.dumps(report,indent=2)+'\n',encoding='utf8');print(json.dumps(report,indent=2))

if __name__=='__main__':main()
