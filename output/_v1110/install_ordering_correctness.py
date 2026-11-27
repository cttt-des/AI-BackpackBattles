"""Install the fully verified correctness repair with complete rollback."""
import hashlib,json,os,subprocess,sys,tempfile
from pathlib import Path
from prepare_ordering_correctness import REPO,STAGE,WORK,BASE,EXPECTED,sha,save,inventory,verify_projection

def read(name):return json.loads((WORK/name).read_bytes())
def replace(path,data):
    path.parent.mkdir(parents=True,exist_ok=True)
    with tempfile.NamedTemporaryFile(dir=path.parent,prefix='ordering-swap-',delete=False) as stream:
        temporary=Path(stream.name);stream.write(data)
    try:os.replace(temporary,path)
    finally:temporary.unlink(missing_ok=True)

def boundary():
    frozen=read('user_boundary_before.json')
    assert subprocess.check_output(['git','rev-parse','HEAD'],cwd=REPO,text=True).strip()==frozen['head']
    assert hashlib.sha256(subprocess.check_output(['git','ls-files','--stage','-z'],cwd=REPO)).hexdigest()==frozen['staged_entries_sha256']
    assert all(sha(REPO/n)==h for n,h in frozen['protected'].items())

def training(directory=None):
    code="""import json
from trainer.evaluator import OpponentPool,_run_jobs,eval_vs_pool
from trainer.native_backend import runtime_directory
pool=OpponentPool().sample((450,650),50,seed=42)[:4]
jobs=[(pool[0],other,seed) for other in pool for seed in (0,42,(1<<64)-1)]
assert len(jobs)==12 and runtime_directory() is not None
public=eval_vs_pool(pool[0],pool,seeds_per_opp=3,workers=1)
assert public['total_sims']==12 and public['sim_errors']==0
print(json.dumps({'outcomes':_run_jobs(jobs,workers=1),'evaluation':public}))
"""
    env=dict(os.environ,BACKPACK_TRAINER_BACKEND=str(directory) if directory else 'auto')
    output=subprocess.check_output([sys.executable,'-X','utf8','-c',code],cwd=REPO,env=env,text=True)
    return json.loads(output.splitlines()[-1])

def required_proofs():
    actual=sha(WORK/'bundle.dll');verify_projection(WORK/'bundle_src');boundary()
    for name in ('complete_correctness_gate.json','formal_ordering_tests.json','formal_extra_potion_tests.json','compiled_option_receipt.json'):
        row=read(name);assert row['passed'] and row['dll_sha256']==actual,name
    assert read('formal_ordering_tests.json')['literal_fast_path_and_public_native_and_generic_paths_checked']
    for name in ('python_compiled_ordering_tests.json','python_source_ordering_tests.json','python_fresh_battle_comparison.json','full_regeneration_test.json','maintained_runtime_syntax.json','maintained_event_bus_syntax.json'):
        assert read(name)['passed'],name
    old,new=read('python_baseline_primitives.json'),read('python_candidate_primitives.json')
    assert read('maintained_event_bus_syntax.json')['source_sha256']==sha(WORK/'maintenance_pending/native_sim_cpp/native_sim/gen/shards/shard_11.cpp')
    assert read('maintained_runtime_syntax.json')['root_runtime_sha256']==sha(WORK/'maintenance_pending/native_sim_cpp/native_sim/gd_rt.cpp')
    assert old['primitive_cases']==new['primitive_cases']==46702 and old['primitive_and_rng_sha256']==new['primitive_and_rng_sha256']
    battles=read('python_fresh_battle_comparison.json');assert battles['fights']==battles['candidate_matches']==30
    gate=read('bundle_full_gate.json');assert gate['complete'] and gate['dll_sha256']==actual
    for cohort,count in [('base',914),('expand',1690)]:
        row=gate['cohorts'][cohort];assert row['passed']==count and not row['winner_mismatch'] and not row['pending']
    events=read('bundle_vs_deployed_hashes.json');assert events['candidate_dll_sha256']==actual and events['unchanged_cpp_event_streams']==2604
    audit=read('full_type_audit.json');assert audit['fights']==2604 and audit['coverage']['audit_mismatch']==audit['old_event_kernel_type_mismatches']==0
    weapon=read('weapon_chain_tests.json');assert weapon['passed'] and weapon['cases']==136128 and weapon['dll_sha256']==actual
    measurements=read('measurements_summary.json');assert measurements['dll_sha256']==actual and measurements['single_run_all_samples_retained']
    fit=read('bundle_load20.json');assert fit['dll_sha256']==actual and fit['reference_load_pct']==20
    for relative,row in read('maintenance_changes.json').items():assert sha(WORK/'maintenance_pending'/relative)==row['after_sha256']
    return actual

def post_install(actual,expected_training):
    runtime=REPO/'dist/native_1_1_10';assert sha(BASE/'libgdcore.dll')==sha(runtime/'libgdcore.dll')==actual
    verify_projection(BASE)
    manifest=json.loads((runtime/'manifest.json').read_bytes());assert manifest['gate_sha256']==sha(WORK/'bundle_full_gate.json')
    for name,h in manifest['sha256'].items():assert sha(runtime/name)==h
    for name,row in read('maintenance_changes.json').items():assert sha(REPO/name)==row['after_sha256']
    # Check every frozen original-game event receipt, bound to the installed bytes.
    sys.path.insert(0,str(STAGE))
    from compare_native_event_receipts import read_gate,reference_index,FIELDS
    _,before=read_gate(WORK.parent/'assembly_membership_bundle/bundle_full_gate.json','native_assembly_membership_bundle_bundle_')
    _,after=read_gate(WORK/'bundle_full_gate.json','native_ordering_correctness_bundle_bundle_')
    references=reference_index(STAGE/'native_host_observed_reference_plan.json');count=0;digest=hashlib.sha256()
    for cases in references.values():
        for case_id,reference in sorted(cases.items()):
            old=before[reference['path']][case_id];new=after[reference['path']][case_id]
            assert new['category']=='pass' and new['cpp_events_sha256']
            for field in FIELDS:assert old.get(field)==new.get(field),(case_id,field)
            digest.update(f"{case_id} {new['cpp_events_sha256']}\n".encode());count+=1
    assert count==2604 and digest.hexdigest()=='b8066c9224bc418923c62f5a3dafb8912100b21bb0026c3b13669872f90e2f54'
    with (WORK/'post_install_python.log').open('wb') as log:
        for label,args in [('compiled',[]),('source',['--pure-rt'])]:
            subprocess.run([sys.executable,'-X','utf8',str(STAGE/'test_ordering_python.py'),'--package',str(REPO),'--work',str(WORK),'--out',str(WORK/f'post_install_python_{label}.json'),*args],stdout=log,stderr=subprocess.STDOUT,check=True,cwd=REPO)
        subprocess.run([sys.executable,'-X','utf8',str(STAGE/'test_ordering_python_primitives.py'),'--package',str(REPO),'--out',str(WORK/'post_install_python_primitives.json')],stdout=log,stderr=subprocess.STDOUT,check=True,cwd=REPO)
        subprocess.run([sys.executable,'-X','utf8',str(STAGE/'check_ordering_installed_python_battles.py')],stdout=log,stderr=subprocess.STDOUT,check=True,cwd=REPO)
    assert read('post_install_python_primitives.json')['primitive_and_rng_sha256']==read('python_baseline_primitives.json')['primitive_and_rng_sha256']
    assert read('post_install_python_fresh_battle.json')['passed'] and read('post_install_python_fresh_battle.json')['fights']==30
    current=training();assert current==expected_training;boundary()
    save('post_install_verification.json',dict(passed=True,dll_sha256=actual,strict_event_cases=count,ordered_event_root=digest.hexdigest(),full_source_files=len(inventory(BASE)),cpp_source_files=710,all674_headers_unchanged=True,python_compiled_and_source_oracles_passed=True,primitive_cases=46702,training_jobs=12,training=current,verified_original_events_replayed_before_install_and_receipts_rechecked_after=True,source_and_runtime_installed_bytes_identical_to_qualified_candidate=True,user_files_and_staged_entries_unchanged=True))

def main():
    actual=required_proofs();runtime=REPO/'dist/native_1_1_10'
    pending=REPO/'dist/native_1_1_10_ordering_correctness_pending'
    backup=REPO/'dist/native_1_1_10_before_ordering_correctness_20261127'
    for p in (runtime,pending,backup):assert p.resolve().is_relative_to(REPO.resolve())
    assert not backup.exists() and sha(runtime/'libgdcore.dll')==sha(BASE/'libgdcore.dll')==EXPECTED
    subprocess.run([sys.executable,'-X','utf8',str(STAGE/'package_native_training_runtime.py'),'--dll',str(WORK/'bundle.dll'),'--gate',str(WORK/'bundle_full_gate.json'),'--out',str(pending)],check=True)
    old_training=training();staged_training=training(pending);assert staged_training==old_training
    save('staged_training.json',dict(passed=True,jobs=12,old_runtime=old_training,candidate=staged_training))
    assert inventory(BASE)==json.loads((WORK.parent/'assembly_membership_bundle/source_before_build.json').read_bytes())
    changes={}
    for relative in inventory(WORK/'bundle_src'):
        target=BASE/relative;new=(WORK/'bundle_src'/relative).read_bytes();old=target.read_bytes() if target.exists() else None
        if old!=new:changes[target]=(old,new)
    changes[BASE/'libgdcore.dll']=((BASE/'libgdcore.dll').read_bytes(),(WORK/'bundle.dll').read_bytes())
    for relative,row in read('maintenance_changes.json').items():
        target=REPO/relative;old=target.read_bytes() if target.exists() else None
        assert (sha(target) if old is not None else None)==row['before_sha256'],relative
        new=(WORK/'maintenance_pending'/relative).read_bytes()
        if new!=old:changes[target]=(old,new)
    saved=WORK/'installation_before';assert not saved.exists();saved.mkdir()
    for target,(old,_) in changes.items():
        if old is not None:
            p=saved/target.relative_to(REPO);p.parent.mkdir(parents=True,exist_ok=True);p.write_bytes(old)
    boundary();installed=[];backed=False;switched=False
    try:
        for target,(_,new) in changes.items():replace(target,new);installed.append(target)
        runtime.rename(backup);backed=True;pending.rename(runtime);switched=True
        post_install(actual,staged_training)
    except BaseException:
        if switched:runtime.rename(pending)
        if backed:backup.rename(runtime)
        for target in reversed(installed):
            old=changes[target][0]
            if old is None:target.unlink()
            else:replace(target,old)
        save('installation_rollback.json',dict(rolled_back=True,production_dll_sha256=sha(BASE/'libgdcore.dll')))
        raise
    save('installation.json',dict(passed=True,dll_sha256=actual,previous_dll_sha256=EXPECTED,runtime=str(runtime.relative_to(REPO)),backup_runtime=str(backup.relative_to(REPO)),changed_files=[p.relative_to(REPO).as_posix() for p in installed],correctness_deployment_without_performance_win_requirement=True,all_other_optimization_work_paused=True,new_branches_created=0,post_install_verification_sha256=sha(WORK/'post_install_verification.json')))
    print('Deployed verified sorting/event repair; native + Python new-process checks and trainer12 passed',flush=True)
if __name__=='__main__':main()
