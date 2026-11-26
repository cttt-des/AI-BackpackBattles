"""Archive this trial using an isolated index and the existing remote ref only."""
import argparse
import hashlib
import io
import json
import os
from pathlib import Path
import subprocess
import tempfile
from prepare_native_identity_lookup import STAGE,BASE,WORK as PROBE,ACCEPTED,EXPECTED,ARCHIVE,sha

REPO=STAGE.parents[1]
WORK=STAGE/'native_perf50/identity_lookup_bundle'
REMOTE='https://github.com/cttt-des/AI-BackpackBattles.git'
REF='refs/heads/codex/native-perf50-verified'
SCRIPTS=('prepare_native_identity_lookup.py', 'setup_identity_lookup_semantics.py', 'build_native_identity_lookup.py', 'test_native_identity_lookup.cpp', 'verify_native_identity_lookup.py', 'verify_identity_lookup_builtins.py', 'verify_identity_lookup_truth.py', 'verify_identity_lookup_private.py', 'verify_identity_lookup_display.py', 'verify_identity_lookup_control.py', 'run_native_identity_lookup_semantics.py', 'resume_native_identity_lookup_semantics.py', 'prototype_native_identity_lookup_bundle.py', 'setup_native_identity_lookup_bundle.py', 'prepare_identity_lookup_terminal_tools.py', 'run_identity_lookup_formal.py', 'verify_identity_lookup_build_options.py', 'review_identity_lookup_release.py', 'close_identity_lookup_round.py', 'record_identity_lookup_round.py', 'archive_identity_lookup_round.py', 'finish_identity_lookup_release.py', 'verify_identity_lookup_goal.py', 'fit_native_serial_load.py', 'record_container_builtins_followup.py', 'test_native_scalar_truth.cpp', 'test_native_identity_snapshots.cpp', 'test_native_private_buff_loops.cpp', 'test_native_private_integer_view.cpp')

def git(*args,env=None,timeout=None,input=None):
    return subprocess.check_output(['git',*args],cwd=REPO,env=env,timeout=timeout,input=input)

def save(name,value):
    (WORK/name).write_text(json.dumps(value,indent=2,ensure_ascii=False)+'\n',encoding='utf8')

def remote_ref():
    return git('-c','http.connectTimeout=10','-c','http.lowSpeedLimit=1','-c','http.lowSpeedTime=10',
        'ls-remote','--exit-code',REMOTE,REF,timeout=30).decode().split()[0]

def workspace_state():
    path=Path(git('rev-parse','--git-path','index').decode().strip())
    if not path.is_absolute():path=REPO/path
    branch=subprocess.run(['git','symbolic-ref','-q','HEAD'],cwd=REPO,capture_output=True)
    assert branch.returncode in (0,1)
    return dict(head=git('rev-parse','HEAD').decode().strip(),
        branch=branch.stdout.decode().strip() if branch.returncode==0 else None,
        index_sha256=sha(path) if path.exists() else None)

def add(paths,env):
    with tempfile.NamedTemporaryFile(prefix='identity-lookup-own-paths-',delete=False) as f:
        spec=Path(f.name);f.write(b''.join(p.encode('utf8')+b'\0' for p in paths))
    try:git('-c','core.autocrlf=false','add','-f',f'--pathspec-from-file={spec}','--pathspec-file-nul',env=env)
    finally:spec.unlink()

def collect():
    status=json.loads((WORK/'current_runtime_status.json').read_bytes())
    assert status['all_protocol_processes_finished'] and status['no_more_same_configuration_measurements']
    decision=json.loads((WORK/'candidate_decision.json').read_bytes())
    assert decision['assessment_sha256']==sha(Path(decision['selected_assessment']))
    assert decision['candidate_dll_sha256']==sha(WORK/'bundle.dll')
    paths={STAGE/n for n in SCRIPTS if (STAGE/n).is_file()}
    paths.add(STAGE/'verify_identity_lookup_goal.py')
    paths.add(STAGE/'finish_identity_lookup_release.py')
    paths.add(STAGE/'resume_identity_lookup_prechecks.py')
    paths.update(p for p in STAGE.glob('identity_lookup*.log') if not p.name.startswith('identity_lookup_archive_'))
    for root in (WORK,PROBE,STAGE/'native_perf50/container_builtins_followup_profile'):
        paths.update(p for p in root.rglob('*') if p.is_file() and '__pycache__' not in p.parts
            and p.suffix not in ('.pyc','.o','.gcda','.gcno') and not p.name.startswith('checkpoint_'))
    paths.add(STAGE/'container_builtins_followup_profile_first.log')
    frozen=json.loads((WORK/'frozen_pgo_manifest.json').read_bytes())
    assert len(frozen['counts'])==18
    for name,digest in frozen['counts'].items():
        p=WORK/'frozen_pgo_counts'/(name+'.gcda');assert sha(p)==digest;paths.add(p)
    paths.add(ACCEPTED/'checkpoint_receipt.json')
    note=REPO/'docs/C++模拟器对象身份与容器查找优化记录_2026-11-26.md';assert note.is_file();paths.add(note)
    overlays=json.loads((WORK/'archive_document_overlays.json').read_bytes())
    virtual={}
    for name,row in overlays.items():
        p=REPO/row['snapshot'];assert p.resolve().is_relative_to(WORK.resolve()) and sha(p)==row['sha256']
        assert name in ('docs/C++模拟器性能优化清单.md','docs/C++模拟器下一阶段优化评估.md','docs/C++模拟器优化交接_2026-11-23.md')
        virtual[name]=p.read_bytes()
    production=sorted(p for p in BASE.rglob('*') if p.is_file() and (p.suffix in ('.cpp','.hpp') or p.name=='build_windows.py'))
    assert len(production)==(708)
    deployed=status['deployed']
    expected_sources=json.loads(((WORK if deployed else ACCEPTED)/'source_before_build.json').read_bytes())
    expected_cpp={n:h for n,h in expected_sources.items() if Path(n).suffix in ('.cpp','.hpp') or Path(n).name=='build_windows.py'}
    assert len(expected_cpp)==(708)
    assert {p.relative_to(BASE).as_posix():sha(p) for p in production}==expected_cpp
    # The frozen directory also includes five unchanged package/platform files.
    # Verify them independently rather than comparing713 entries with708 C++ files.
    for name,digest in expected_sources.items():
        p=BASE/name;assert p.resolve().is_relative_to(BASE.resolve()) and sha(p)==digest
        paths.add(p)
    digest=sha(BASE/'libgdcore.dll')
    assert digest==status['production_dll_sha256']==sha(REPO/'dist/native_1_1_10/libgdcore.dll')
    assert digest==(sha(WORK/'bundle.dll') if deployed else EXPECTED)
    if deployed:
        check=json.loads((WORK/'post_install_verification.json').read_bytes())
        assert check['passed'] and check['strict_event_cases']==2604 and check['dll_sha256']==digest
    if (WORK/'full_type_audit.json').exists():
        audit=json.loads((WORK/'full_type_audit.json').read_bytes())
        for folder in map(Path,audit['receipts']):paths.update(folder.glob('*.json'))
    paths.update(production)
    paths.update((BASE/'libgdcore.dll',STAGE/'optimize_native_verified_bundle.py',
        REPO/'dist/native_1_1_10/libgdcore.dll',REPO/'dist/native_1_1_10/manifest.json'))
    assert all(p.is_file() and p.resolve().is_relative_to(REPO.resolve()) for p in paths)
    relative=sorted(p.relative_to(REPO).as_posix() for p in paths)
    assert not any(p.startswith(('native_sim_cpp/','oracle/','output/perf/')) for p in relative)
    assert not set(relative)&virtual.keys()
    return relative,virtual,digest,deployed

def verify_tree(commit,paths,virtual):
    names=sorted(set(paths)|virtual.keys())
    raw=git('cat-file','--batch',input=''.join(f'{commit}:{p}\n' for p in names).encode('utf8'))
    stream=io.BytesIO(raw)
    for name in names:
        header=stream.readline().split();assert len(header)==3 and header[1]==b'blob',name
        expected=virtual[name] if name in virtual else (REPO/name).read_bytes()
        assert stream.read(int(header[2]))==expected,name
        assert stream.read(1)==b'\n'

def upload():
    receipt=json.loads((WORK/'checkpoint_receipt.json').read_bytes())
    target=receipt['prepared_backup_commit'];current=remote_ref()
    assert current in (ARCHIVE,target),'Existing backup ref advanced externally; review before pushing'
    assert git('rev-parse',target+'^').decode().strip()==ARCHIVE
    if current!=target:
        subprocess.run(['git','-c','http.connectTimeout=10','-c','http.lowSpeedLimit=1','-c','http.lowSpeedTime=30',
            'push',REMOTE,f'{target}:{REF}'],cwd=REPO,check=True,timeout=180)
    assert remote_ref()==target
    receipt.update(remote_upload_verified=True,remote_verified_commit=target)
    save('checkpoint_receipt.json',receipt);print(json.dumps(receipt),flush=True)

def main():
    parser=argparse.ArgumentParser();parser.add_argument('--commit',action='store_true');parser.add_argument('--upload',action='store_true');args=parser.parse_args()
    if args.upload:upload();return
    before=workspace_state();paths,virtual,digest,deployed=collect()
    hashes={p:sha(REPO/p) for p in paths}
    hashes.update({p:hashlib.sha256(raw).hexdigest() for p,raw in virtual.items()})
    save('checkpoint_inventory.json',hashes)
    print(json.dumps(dict(files=len(hashes),production_source_files=708,candidate_installed=deployed,
        production_dll_sha256=digest,no_new_branches=True,isolated_index_only=True)),flush=True)
    if not args.commit:return
    assert not (WORK/'checkpoint_receipt.json').exists(),'Reuse prepared receipt for upload retries'
    with tempfile.TemporaryDirectory(prefix='identity-lookup-own-index-') as folder:
        env=dict(os.environ,GIT_INDEX_FILE=str(Path(folder)/'index'))
        git('read-tree',ARCHIVE,env=env);add(paths,env)
        for name,raw in virtual.items():
            blob=git('hash-object','-w','--stdin',input=raw).decode().strip()
            git('update-index','--add','--cacheinfo','100644',blob,name,env=env)
        tree=git('write-tree',env=env).decode().strip()
    commit=git('commit-tree',tree,'-p',ARCHIVE,'-m','perf: preserve identity and container lookup trial evidence').decode().strip()
    verify_tree(commit,paths,virtual)
    assert hashes=={**{p:sha(REPO/p) for p in paths},**{p:hashlib.sha256(raw).hexdigest() for p,raw in virtual.items()}}
    after=workspace_state();assert after==before,'Workspace HEAD/index changed concurrently; no refs have been updated'
    receipt=dict(local_commit=commit,prepared_backup_commit=commit,parent_remote_verified_commit=ARCHIVE,
        remote_existing_ref=REF,no_new_branches=True,no_local_refs_updated=True,
        own_files_saved=len(hashes),production_source_files_verified=708,candidate_installed=deployed,
        production_dll_sha256=digest,user_existing_changes_not_staged=True,
        workspace_head_and_index_unchanged=True,workspace_state=before,
        overlapping_documents_from_previous_backup_plus_own_note=True,remote_upload_verified=False)
    save('checkpoint_receipt.json',receipt);print(json.dumps(receipt),flush=True)

if __name__=='__main__':main()
