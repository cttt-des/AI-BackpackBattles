"""Back up the completed repair on the existing ref without changing HEAD/index."""
import argparse,hashlib,io,json,os,subprocess,tempfile
from pathlib import Path
from prepare_ordering_correctness import REPO,STAGE,WORK,BASE,ARCHIVE,REF,sha,save,inventory,verify_projection
from install_ordering_correctness import boundary
REMOTE='https://github.com/cttt-des/AI-BackpackBattles.git'
def git(*args,env=None,input=None,timeout=None):return subprocess.check_output(['git',*args],cwd=REPO,env=env,input=input,timeout=timeout)
def remote():return git('-c','http.connectTimeout=10','ls-remote','--exit-code',REMOTE,REF,timeout=40).decode().split()[0]
def state():return dict(head=git('rev-parse','HEAD').decode().strip(),branch=git('symbolic-ref','--short','HEAD').decode().strip(),staged_entries_sha256=hashlib.sha256(git('ls-files','--stage','-z')).hexdigest())
def collect():
    proof=json.loads((WORK/'post_install_verification.json').read_bytes());assert proof['passed'] and proof['strict_event_cases']==2604
    actual=sha(BASE/'libgdcore.dll');assert actual==proof['dll_sha256']==sha(REPO/'dist/native_1_1_10/libgdcore.dll')
    verify_projection(BASE);paths=set()
    for pattern in ('*ordering*.py','ordering*.gd','test_ordering*.cpp','audit_same_frame*.py','same_frame_potion_reference.gd','test_same_frame_potion*.cpp'):
        paths.update(STAGE.glob(pattern))
    paths.update(p for p in STAGE.glob('ordering_correctness*.log') if not p.name.startswith('ordering_correctness_archive_'))
    for directory in (WORK,WORK.with_name(WORK.name+'_revision1'),STAGE/'same_frame_potion_audit_20261127'):
        for p in directory.rglob('*'):
            if not p.is_file() or '__pycache__' in p.parts or '.import' in p.parts:continue
            if p.suffix in ('.pyc','.o','.obj','.gcno','.exe','.c','.lib','.exp'):continue
            if p.suffix=='.gcda' and 'frozen_pgo_counts' not in p.parts:continue
            if p.name.startswith('checkpoint_'):continue
            paths.add(p)
    for name in inventory(BASE):paths.add(BASE/name)
    paths.add(BASE/'libgdcore.dll')
    for name in json.loads((WORK/'maintenance_changes.json').read_bytes()):paths.add(REPO/name)
    for name in ('sim.py','gd_core_runtime.json','libgdcore.dll','manifest.json'):paths.add(REPO/'dist/native_1_1_10'/name)
    for name in ('C++模拟器排序与事件派发修复记录_2026-11-27.md','C++模拟器同帧事件与药水触发顺序核查_2026-11-27.md'):
        p=REPO/'docs'/name;assert p.exists();paths.add(p)
    audit=json.loads((WORK/'full_type_audit.json').read_bytes())
    for directory in audit['receipts']:paths.update(Path(directory).glob('*.json'))
    protected=json.loads((WORK/'user_boundary_before.json').read_bytes())['protected']
    relative=sorted(p.relative_to(REPO).as_posix() for p in paths)
    assert {'output/_v1110/test_ordering_contracts.cpp','output/_v1110/test_ordering_potion_chains.cpp'}<=set(relative)
    assert not set(relative)&set(protected)
    assert all((REPO/n).is_file() and (REPO/n).resolve().is_relative_to(REPO.resolve()) for n in relative)
    assert len(inventory(BASE))==715
    for folder in (WORK,WORK.with_name(WORK.name+'_revision1')):
        frozen=json.loads((folder/'frozen_pgo_manifest.json').read_bytes())
        assert len(frozen['counts'])==18
        for n,h in frozen['counts'].items():assert sha(folder/'frozen_pgo_counts'/(n+'.gcda'))==h
    return relative,actual

def verify_tree(commit,paths):
    stream=io.BytesIO(git('cat-file','--batch',input=''.join(f'{commit}:{n}\n' for n in paths).encode('utf8')))
    for name in paths:
        header=stream.readline().split();assert len(header)==3 and header[1]==b'blob',name
        assert stream.read(int(header[2]))==(REPO/name).read_bytes(),name
        assert stream.read(1)==b'\n'

def upload():
    receipt=json.loads((WORK/'checkpoint_receipt.json').read_bytes());commit=receipt['prepared_backup_commit'];current=remote()
    assert current in (ARCHIVE,commit),'Existing backup ref advanced; do not overwrite it'
    assert git('rev-parse',commit+'^').decode().strip()==ARCHIVE;boundary();before=state()
    if current!=commit:subprocess.run(['git','-c','http.connectTimeout=10','-c','http.lowSpeedLimit=1','-c','http.lowSpeedTime=30','push',REMOTE,f'{commit}:{REF}'],cwd=REPO,check=True,timeout=240)
    assert remote()==commit;assert state()==before;boundary()
    receipt.update(remote_upload_verified=True,remote_verified_commit=commit);save('checkpoint_receipt.json',receipt);print(json.dumps(receipt,ensure_ascii=False),flush=True)

def main():
    parser=argparse.ArgumentParser();parser.add_argument('--upload',action='store_true');args=parser.parse_args()
    if args.upload:upload();return
    assert not (WORK/'checkpoint_receipt.json').exists();boundary();before=state();paths,digest=collect();assert remote()==ARCHIVE
    hashes={n:sha(REPO/n) for n in paths};save('checkpoint_inventory.json',hashes)
    with tempfile.TemporaryDirectory(prefix='ordering-backup-index-') as temp:
        env=dict(os.environ,GIT_INDEX_FILE=str(Path(temp)/'index'));git('read-tree',ARCHIVE,env=env)
        spec=Path(temp)/'paths';spec.write_bytes(b''.join(n.encode('utf8')+b'\0' for n in paths))
        git('-c','core.autocrlf=false','add','-f',f'--pathspec-from-file={spec}','--pathspec-file-nul',env=env)
        tree=git('write-tree',env=env).decode().strip()
    commit=git('commit-tree',tree,'-p',ARCHIVE,'-m','fix: align sorting and all event dispatch paths with game 1.1.10').decode().strip()
    verify_tree(commit,paths);assert {n:sha(REPO/n) for n in paths}==hashes;assert state()==before;boundary()
    save('checkpoint_receipt.json',dict(prepared_backup_commit=commit,parent_remote_verified_commit=ARCHIVE,remote_existing_ref=REF,remote_upload_verified=False,no_new_branches=True,no_local_refs_updated=True,workspace_head_and_staged_entries_unchanged=True,user_existing_changes_not_staged=True,own_files_saved=len(paths),production_full_source_files=715,production_cpp_source_files=710,production_dll_sha256=digest,workspace_state=before))
    print('Prepared verified backup '+commit+'; '+str(len(paths))+' files, existing ref only',flush=True)
if __name__=='__main__':main()
