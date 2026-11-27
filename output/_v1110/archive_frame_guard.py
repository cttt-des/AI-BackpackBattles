"""Save this one completed optimization on the existing backup ref only."""
import argparse,hashlib,io,json,os,subprocess,tempfile
from pathlib import Path
from prepare_frame_guard_reuse import REPO,STAGE,WORK,BASE,ACCEPTED,EXPECTED,ARCHIVE,sha,inventory,save,verify_projection
from install_ordering_correctness import boundary
REMOTE='https://github.com/cttt-des/AI-BackpackBattles.git';REF='refs/heads/codex/native-perf50-verified'
def git(*args,env=None,input=None,timeout=None):return subprocess.check_output(['git',*args],cwd=REPO,env=env,input=input,timeout=timeout)
def remote():return git('-c','http.connectTimeout=10','ls-remote','--exit-code',REMOTE,REF,timeout=40).decode().split()[0]
def state():return dict(head=git('rev-parse','HEAD').decode().strip(),staged_entries_sha256=hashlib.sha256(git('ls-files','--stage','-z')).hexdigest())
def collect():
    status=json.loads((WORK/'current_runtime_status.json').read_bytes());assert status['all_protocol_processes_finished']
    decision=json.loads((WORK/'candidate_decision.json').read_bytes());assert decision['assessment_sha256']==sha(WORK/decision['selected_assessment'])
    if status['deployed']:assert sha(BASE/'libgdcore.dll')==sha(WORK/'bundle.dll');verify_projection(BASE);assert json.loads((WORK/'post_install_verification.json').read_bytes())['passed']
    else:assert sha(BASE/'libgdcore.dll')==EXPECTED and inventory(BASE)==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    paths=set(STAGE.glob('*frame_guard*.py'));paths.add(STAGE/'profile_post_ordering.py')
    paths.update(p for p in STAGE.glob('frame_guard*.log') if not p.name.startswith(('frame_guard_archive_','frame_guard_goal_driver_')));paths.add(STAGE/'post_ordering_profile_first.log')
    for folder in (WORK,STAGE/'native_perf50/post_ordering_assessment'):
        for p in folder.rglob('*'):
            if not p.is_file() or '__pycache__' in p.parts or p.suffix in ('.pyc','.o','.obj','.gcno','.exe','.c','.lib','.exp'):continue
            if p.name.startswith('checkpoint_'):continue
            if p.suffix=='.gcda' and 'frozen_pgo_counts' not in p.parts:continue
            paths.add(p)
    frozen=json.loads((WORK/'frozen_pgo_manifest.json').read_bytes());assert len(frozen['counts'])==18
    for n,h in frozen['counts'].items():assert sha(WORK/'frozen_pgo_counts'/(n+'.gcda'))==h
    for n in inventory(BASE):paths.add(BASE/n)
    paths.update([BASE/'libgdcore.dll',STAGE/'optimize_native_verified_bundle.py'])
    for n in ('sim.py','gd_core_runtime.json','libgdcore.dll','manifest.json'):paths.add(REPO/'dist/native_1_1_10'/n)
    note=REPO/'docs/C++模拟器逐帧类型守卫复用优化记录_2026-11-27.md';assert note.exists();paths.add(note)
    for name in ('full_type_audit.json','post_ab_full_type_audit.json'):
        p=WORK/name
        if p.exists():
            for directory in json.loads(p.read_bytes())['receipts']:paths.update(Path(directory).glob('*.json'))
    relative=sorted(p.relative_to(REPO).as_posix() for p in paths);protected=json.loads((WORK/'user_boundary_before.json').read_bytes())['protected']
    assert not set(relative)&set(protected)
    assert all((REPO/n).is_file() and (REPO/n).resolve().is_relative_to(REPO.resolve()) for n in relative)
    return relative,status
def verify_tree(commit,names):
    stream=io.BytesIO(git('cat-file','--batch',input=''.join(f'{commit}:{n}\n' for n in names).encode('utf8')))
    for name in names:
        header=stream.readline().split();assert len(header)==3 and header[1]==b'blob';assert stream.read(int(header[2]))==(REPO/name).read_bytes(),name;assert stream.read(1)==b'\n'
def upload():
    r=json.loads((WORK/'checkpoint_receipt.json').read_bytes());commit=r['prepared_backup_commit'];current=remote();assert current in (ARCHIVE,commit);assert git('rev-parse',commit+'^').decode().strip()==ARCHIVE
    boundary();before=state()
    if current!=commit:subprocess.run(['git','-c','http.connectTimeout=10','-c','http.lowSpeedLimit=1','-c','http.lowSpeedTime=30','push',REMOTE,f'{commit}:{REF}'],cwd=REPO,check=True,timeout=240)
    assert remote()==commit and state()==before;boundary();r.update(remote_upload_verified=True,remote_verified_commit=commit);save('checkpoint_receipt.json',r);print('Existing backup ref verified at '+commit,flush=True)
def main():
    p=argparse.ArgumentParser();p.add_argument('--upload',action='store_true');a=p.parse_args()
    if a.upload:upload();return
    assert not (WORK/'checkpoint_receipt.json').exists();boundary();before=state();paths,status=collect();assert remote()==ARCHIVE
    hashes={n:sha(REPO/n) for n in paths};save('checkpoint_inventory.json',hashes)
    with tempfile.TemporaryDirectory(prefix='frame-guard-own-index-') as temp:
        env=dict(os.environ,GIT_INDEX_FILE=str(Path(temp)/'index'));git('read-tree',ARCHIVE,env=env)
        spec=Path(temp)/'paths';spec.write_bytes(b''.join(n.encode('utf8')+b'\0' for n in paths));git('-c','core.autocrlf=false','add','-f',f'--pathspec-from-file={spec}','--pathspec-file-nul',env=env);tree=git('write-tree',env=env).decode().strip()
    commit=git('commit-tree',tree,'-p',ARCHIVE,'-m','perf: '+('deploy' if status['deployed'] else 'close')+' frame type guard reuse with complete original-order evidence').decode().strip()
    verify_tree(commit,paths);assert hashes=={n:sha(REPO/n) for n in paths};assert state()==before;boundary()
    save('checkpoint_receipt.json',dict(prepared_backup_commit=commit,parent_remote_verified_commit=ARCHIVE,remote_existing_ref=REF,remote_upload_verified=False,no_new_branches=True,no_local_refs_updated=True,user_existing_changes_not_staged=True,workspace_head_and_staged_entries_unchanged=True,files=len(paths),production_full_source_files=715,production_CPP_source_files=710,deployed=status['deployed'],production_dll_sha256=sha(BASE/'libgdcore.dll'),candidate_dll_sha256=sha(WORK/'bundle.dll'),workspace_state=before));print('Prepared verified existing-ref backup '+commit,flush=True)
if __name__=='__main__':main()
