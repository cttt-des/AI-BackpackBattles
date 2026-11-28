"""One milestone backup through the existing ref, without touching local refs."""
import hashlib,json,os,subprocess,tempfile
from pathlib import Path
import psutil
from native_build_storage import isolated_build
from native_backup_index import stage_files,verify_tree_files
from prepare_timeline_round import REPO,STAGE,WORK as CANDIDATE,BASE,EXPECTED,ARCHIVE,sha
from install_ordering_correctness import boundary
WORK=CANDIDATE.parent;REMOTE='https://github.com/cttt-des/AI-BackpackBattles.git';REF='refs/heads/codex/native-perf50-verified'
def git(*args,env=None,input=None,timeout=60):return subprocess.check_output(['git','-c','pack.threads=2',*args],cwd=REPO,env=env,input=input,timeout=timeout)
def state():return dict(head=git('rev-parse','HEAD').decode().strip(),staged_entries_sha256=hashlib.sha256(git('ls-files','--stage','-z')).hexdigest())
def remote():return git('-c','http.connectTimeout=10','ls-remote','--exit-code',REMOTE,REF,timeout=40).decode().split()[0]
def collect():
    end=json.loads((WORK/'round_completion.json').read_bytes());assert end['all_three_directions_have_execution_decisions'] and end['all_protocol_processes_finished']
    paths={p for p in WORK.rglob('*') if p.is_file() and '__pycache__' not in p.parts and not p.name.startswith(('checkpoint_','timeline_goal_driver','architecture_archive')) and p.suffix not in ['.o','.obj','.exe','.pyc']}
    names=['probe_phase_plan.py','test_phase_plan_probe.cpp','test_phase_plan_live_probe.cpp','probe_exact_countdown.py','test_exact_countdown_jump.cpp','exact_countdown_jump.hpp','bench_exact_countdown.py','bench_exact_countdown_jump.cpp','probe_architecture_resume.py','test_invariant_resume_probe.cpp','test_timeline_resume_probe.cpp','test_frontier_resume_probe.cpp','prepare_timeline_step_probe.py','test_timeline_step_resume_probe.cpp','test_delay_resume_probe.cpp','analyze_architecture_resume.py','prepare_timeline_round.py','timeline_round.py','verify_timeline_affected.py','timeline_fast_verify.py','verify_timeline_full.py','archive_architecture_resume.py','native_backup_index.py','native_build_storage.py','native_build_schedule.py','run_native_managed.py','AGENTS.md']
    paths.update(STAGE/n for n in names)
    paths.update(STAGE/n for n in ['apply_timeline_transform.py','measure_timeline_round.py','install_timeline_round.py','run_timeline_goal.py'])
    paths.update(STAGE/n for n in ['revise_timeline_candidate.py','test_delay_container_regression.cpp','verify_timeline_container.py'])
    paths.update(STAGE/n for n in ['revise_timeline_rows.py','test_row_guard_resume_probe.cpp','probe_timeline_real200.py'])
    paths.update(STAGE/n for n in ['test_native_frame_segments.cpp','test_native_motion_indices.cpp','native_perf50/motion_indices_probe/preflight_motion_indices.hpp','native_perf50/measurement_structure_bundle/profile_baseline.json'])
    paths.update(REPO/'docs'/n for n in ['C++模拟器三方向优化与高效迭代_2026-11-28.md','C++模拟器优化交接_2026-11-28.md','C++模拟器三方向接手与类型化时间线候选_2026-11-28.md'])
    for folder in STAGE.glob('native_timeline_typed_*'):
        if folder.is_dir():paths.update(folder.rglob('*.json'))
    # Keep generated actual-DLL fixtures and cleanup evidence when identifiable
    # by this workflow's names; disposable objects/executables are never added.
    for folder in (STAGE/'build_storage/archive').iterdir():
        if not folder.is_dir():continue
        explicit=folder.name.startswith(('probe_architecture_resume-','timeline_round-','verify_timeline_affected-'))
        generated=list(folder.rglob('timeline_step.cpp'))+list(folder.rglob('delay.cpp'))+list(folder.rglob('legacy_motion.cpp'))
        if explicit or generated:
            paths.update(p for p in folder.rglob('*') if p.is_file() and p.suffix not in ['.o','.obj','.exe','.pyc','.dll'] and '__pycache__' not in p.parts)
    for record in CANDIDATE.rglob('persistent_build_directory.json'):
        root=Path(json.loads(record.read_bytes())['root'])
        while root.parent!=Path('D:/CodexNativeBuilds/work') and len(root.parts)>2:root=root.parent
        receipt=STAGE/'build_storage/archive'/root.name/'cleanup_receipt.json';assert json.loads(receipt.read_bytes())['cleanup_complete'];paths.add(receipt)
    if end['deployed']:
        paths.update(p for p in BASE.rglob('*') if p.is_file() and p.suffix not in ['.o','.obj','.pyc'] and '__pycache__' not in p.parts)
        paths.update(REPO/'dist/native_1_1_10'/n for n in ['libgdcore.dll','manifest.json'])
    protected=json.loads((CANDIDATE/'user_boundary_before.json').read_bytes())['protected'];names=sorted(p.relative_to(REPO).as_posix() for p in paths);assert not set(names)&set(protected)
    assert all((REPO/n).resolve().is_relative_to(REPO.resolve()) for n in names);return names,end

@isolated_build
def main():
    psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS);boundary();before=state();paths,end=collect();receipt=WORK/'checkpoint_receipt.json'
    if receipt.exists():
        r=json.loads(receipt.read_bytes());commit=r['prepared_backup_commit'];verify_tree_files(REPO,commit,paths)
    else:
        assert remote()==ARCHIVE;hashes={n:sha(REPO/n) for n in paths};inventory=WORK/'checkpoint_inventory.json';inventory.write_text(json.dumps(hashes,indent=2,ensure_ascii=False)+'\n',encoding='utf8')
        with tempfile.TemporaryDirectory(prefix='architecture-own-index-') as directory:
            env=dict(os.environ,GIT_INDEX_FILE=str(Path(directory)/'index'));git('read-tree',ARCHIVE,env=env);stage_files(REPO,[*paths,inventory.relative_to(REPO).as_posix()],env);tree=git('write-tree',env=env).decode().strip()
        commit=git('commit-tree',tree,'-p',ARCHIVE,'-m','perf: assess three architecture directions and retain typed timeline release evidence').decode().strip();verify_tree_files(REPO,commit,paths);assert hashes=={n:sha(REPO/n) for n in paths}
        r=dict(prepared_backup_commit=commit,parent_remote_verified_commit=ARCHIVE,remote_existing_ref=REF,remote_upload_verified=False,no_new_branches=True,no_local_refs_updated=True,workspace_state=before,files=len(paths),deployed=end['deployed'],production_dll_sha256=sha(BASE/'libgdcore.dll'));receipt.write_text(json.dumps(r,indent=2)+'\n',encoding='utf8')
    current=remote();assert current in (ARCHIVE,commit)
    if current!=commit:subprocess.run(['git','-c','pack.threads=2','-c','http.connectTimeout=10','-c','http.lowSpeedLimit=1','-c','http.lowSpeedTime=30','push',REMOTE,f'{commit}:{REF}'],cwd=REPO,check=True,timeout=240)
    assert remote()==commit and state()==before;boundary();r.update(remote_upload_verified=True,remote_verified_commit=commit);receipt.write_text(json.dumps(r,indent=2)+'\n',encoding='utf8');print('Verified existing backup ref at '+commit,flush=True)
if __name__=='__main__':main()
