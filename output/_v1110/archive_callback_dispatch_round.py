"""Save only this round; preserve production in a verified, fast-forward backup."""
import argparse
import hashlib
import io
import json
import os
from pathlib import Path
import subprocess
import tempfile

STAGE=Path(__file__).resolve().parent
REPO=STAGE.parents[1]
WORK=STAGE/'native_perf50/callback_dispatch_bundle'
PREVIOUS='a27d289f2009c3ad42145d61334d50647b2c060f'
REMOTE='https://github.com/cttt-des/AI-BackpackBattles.git'
REF='refs/heads/codex/native-perf50-verified'
BASE='c46cc19c06fb3c424a470f04bb7a0ef5acf8b7ff01caaccd5f41a5c44d955ee1'
SCRIPTS=('probe_native_bound_arguments.py', 'prepare_native_callback_dispatch.py', 'build_native_callback_dispatch.py', 'test_native_callback_dispatch.cpp', 'verify_native_callback_dispatch.py', 'probe_native_callback_arrays.py', 'probe_native_object_callbacks.py', 'prototype_native_callback_dispatch_bundle.py', 'setup_callback_dispatch_bundle.py', 'preflight_native_callback_dispatch.py', 'run_callback_dispatch_formal.py', 'close_callback_dispatch_round.py', 'archive_callback_dispatch_round.py', 'setup_callback_dispatch_archive.py', 'analyze_native_dispatch.py','repair_callback_validation_harness.py','repair_callback_validation_harness_2.py','resume_callback_dispatch_validation.py','review_callback_dispatch_release.py','record_callback_dispatch_deployment.py')

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def git(*args,env=None,timeout=None):
    return subprocess.check_output(['git',*args],cwd=REPO,env=env,timeout=timeout)
def save(name,data):
    (WORK/name).write_text(json.dumps(data,indent=2,ensure_ascii=False)+'\n',encoding='utf8')
def remote_ref():
    return git('-c','http.connectTimeout=10','-c','http.lowSpeedLimit=1','-c','http.lowSpeedTime=10',
               'ls-remote','--exit-code',REMOTE,REF,timeout=30).decode().split()[0]

def add(paths,env=None):
    with tempfile.NamedTemporaryFile(prefix='event-factory-paths-',delete=False) as f:
        spec=Path(f.name);f.write(b''.join(p.encode('utf8')+b'\0' for p in paths))
    try:
        git('-c','core.autocrlf=false','add','-f',f'--pathspec-from-file={spec}','--pathspec-file-nul',env=env)
    finally:spec.unlink()

def collect():
    decision=json.loads((WORK/'candidate_decision.json').read_bytes())
    assert decision['assessment_sha256']==sha(Path(decision['selected_assessment']))
    assert decision['candidate_dll_sha256']==sha(WORK/'bundle.dll')
    paths={STAGE/n for n in SCRIPTS}
    for root in (WORK,WORK.parent/'callback_dispatch_prototype',WORK.parent/'bound_callbacks_prototype'):
        paths.update(p for p in root.rglob('*') if p.is_file() and '__pycache__' not in p.parts
            and p.suffix not in ('.pyc','.o','.gcda','.gcno') and not p.name.startswith('checkpoint_'))
    profiles=json.loads((WORK/'frozen_pgo_manifest.json').read_bytes())
    assert len(profiles['counts'])==18
    for name,digest in profiles['counts'].items():
        p=WORK/'frozen_pgo_counts'/(name+'.gcda');assert sha(p)==digest;paths.add(p)
    paths.update(REPO/'docs'/n for n in ('C++模拟器性能优化清单.md','C++模拟器下一阶段优化评估.md','C++模拟器优化交接_2026-11-23.md'))
    paths.add(STAGE/'native_perf50/literal_spans_bundle/checkpoint_receipt.json')
    native=STAGE/'sim_native/native_sim_cpp/native_sim'
    production=sorted(p for p in native.rglob('*') if p.is_file() and (p.suffix in ('.cpp','.hpp') or p.name=='build_windows.py'))
    assert len(production)==707
    installed=(WORK/'post_install_verification.json').exists()
    if installed:
        check=json.loads((WORK/'post_install_verification.json').read_bytes())
        assert check['passed'] and check['dll_sha256']==sha(native/'libgdcore.dll')==sha(WORK/'bundle.dll')
        assert check['strict_event_cases']==2604
        audit=json.loads((WORK/'full_type_audit.json').read_bytes())
        for root in map(Path,audit['receipts']):paths.update(root.glob('*.json'))
    else:
        assert sha(native/'libgdcore.dll')==BASE
    assert sha(native/'libgdcore.dll')==sha(REPO/'dist/native_1_1_10/libgdcore.dll')
    paths.update(production)
    paths.update((native/'libgdcore.dll',STAGE/'optimize_native_verified_bundle.py',
                  REPO/'dist/native_1_1_10/libgdcore.dll',REPO/'dist/native_1_1_10/manifest.json'))
    assert all(p.is_file() for p in paths)
    relative=sorted(p.relative_to(REPO).as_posix() for p in paths)
    # Explicitly protect all user files named by the handoff.
    assert not any(p.startswith(('native_sim_cpp/','oracle/','output/perf/')) for p in relative)
    return relative,production,installed

def verify_tree(commit,paths):
    assert paths
    data=subprocess.check_output(
        ['git','cat-file','--batch'],cwd=REPO,
        input=''.join(f'{commit}:{p}\n' for p in paths).encode('utf8'))
    stream=io.BytesIO(data)
    for path in paths:
        header=stream.readline().split();assert len(header)==3 and header[1]==b'blob',path
        assert stream.read(int(header[2]))==(REPO/path).read_bytes(),path
        assert stream.read(1)==b'\n'

def upload():
    receipt=json.loads((WORK/'checkpoint_receipt.json').read_bytes())
    target=receipt['prepared_backup_commit'];current=remote_ref()
    assert current in (PREVIOUS,target),'Review changed remote ancestry before uploading'
    if current!=target:
        subprocess.run(['git','-c','http.connectTimeout=10','-c','http.lowSpeedLimit=1','-c','http.lowSpeedTime=30',
                        'push',REMOTE,f'{target}:{REF}'],cwd=REPO,check=True,timeout=180)
    assert remote_ref()==target
    receipt.update(remote_upload_verified=True,remote_verified_commit=target)
    save('checkpoint_receipt.json',receipt);print(json.dumps(receipt))

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--commit',action='store_true');parser.add_argument('--upload',action='store_true')
    args=parser.parse_args()
    if args.upload:upload();return
    assert not git('diff','--cached','--name-only').strip(),'Preserve already staged user work'
    paths,production,installed=collect()
    hashes={p:sha(REPO/p) for p in paths}
    save('checkpoint_inventory.json',hashes)
    print(json.dumps(dict(files=len(paths),production_source_files=len(production),candidate_installed=installed,
                          production_dll_sha256=sha(STAGE/'sim_native/native_sim_cpp/native_sim/libgdcore.dll'))))
    if not args.commit:return
    assert not (WORK/'checkpoint_receipt.json').exists(),'Reuse the prepared receipt for upload retries'
    add(paths)
    staged=set(filter(None,git('diff','--cached','--name-only','-z').decode('utf8').split('\0')))
    assert staged.issubset(paths)
    assert hashes=={p:sha(REPO/p) for p in paths}
    git('commit','-m','perf: preserve exact-type callback dispatch evaluation')
    local=git('rev-parse','HEAD').decode().strip()
    with tempfile.TemporaryDirectory(prefix='native-callback-dispatch-backup-') as directory:
        env=dict(os.environ,GIT_INDEX_FILE=str(Path(directory)/'index'))
        git('read-tree',PREVIOUS,env=env);add(paths,env=env)
        tree=git('write-tree',env=env).decode().strip()
    commit=git('commit-tree',tree,'-p',PREVIOUS,'-p',local,'-m',
               'backup: preserve callback dispatch trials with actual production runtime').decode().strip()
    verify_tree(commit,paths)
    protection='refs/heads/codex/callback-dispatch-backup-20261123'
    git('update-ref',protection,commit)
    receipt=dict(local_commit=local,prepared_backup_commit=commit,local_preservation_ref=protection,
                 parent_remote_verified_commit=PREVIOUS,own_files_saved=len(paths),
                 production_source_files_verified=707,candidate_installed=installed,
                 production_dll_sha256=sha(STAGE/'sim_native/native_sim_cpp/native_sim/libgdcore.dll'),
                 user_existing_changes_not_staged=True,remote_upload_verified=False)
    save('checkpoint_receipt.json',receipt);print(json.dumps(receipt))

if __name__=='__main__':main()
