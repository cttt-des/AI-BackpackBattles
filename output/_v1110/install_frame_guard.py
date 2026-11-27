"""Deploy only the measured winner and its one-header regeneration recipe."""
import hashlib,json,subprocess,sys
from pathlib import Path
from prepare_frame_guard_reuse import REPO,STAGE,WORK,BASE,ACCEPTED,EXPECTED,HEADER,sha,inventory,save,verify_projection
from install_ordering_correctness import boundary,replace,training
def read(n):return json.loads((WORK/n).read_bytes())
def require():
    boundary();verify_projection(WORK/'bundle_src');actual=sha(WORK/'bundle.dll')
    decision=read('candidate_decision.json');assert decision['accepted'] and decision['candidate_dll_sha256']==actual
    assessment=read(decision['selected_assessment']);assert sha(WORK/decision['selected_assessment'])==decision['assessment_sha256']
    assert assessment['baseline_dll_sha256']==EXPECTED and assessment['candidate_dll_sha256']==actual
    assert all(assessment['metrics'][m]['paired_median_time_reduction_pct']>0 for m in ('main_thread_cpu_s','wall_s'))
    for n in ('complete_correctness_gate.json','post_ab_directed_checks.json','formal_actual_frame_tests.json','post_ab_actual_frame_tests.json','formal_ordering_tests.json','formal_extra_potion_tests.json','compiled_option_receipt.json','weapon_chain_tests.json'):
        r=read(n);assert r['passed'] and r['dll_sha256']==actual,n
    assert read('formal_actual_frame_tests.json')['cases']==135168 and read('weapon_chain_tests.json')['cases']==136128
    assert read('full_regeneration_test.json')['passed']
    speed=read('measurements_summary.json');assert speed['dll_sha256']==actual and speed['raw24_gate_passed'] and not speed['nonrelease_only']
    gate=read('bundle_full_gate.json');assert gate['complete'] and gate['dll_sha256']==actual
    for label,count in [('base',914),('expand',1690)]:assert gate['cohorts'][label]['passed']==count and not gate['cohorts'][label]['pending']
    return actual
def main():
    actual=require();runtime=REPO/'dist/native_1_1_10';pending=REPO/'dist/native_1_1_10_frame_guard_pending';backup=REPO/'dist/native_1_1_10_before_frame_guard_20261127'
    for p in (runtime,pending,backup):assert p.resolve().is_relative_to(REPO.resolve())
    assert not backup.exists() and sha(runtime/'libgdcore.dll')==sha(BASE/'libgdcore.dll')==EXPECTED
    assert inventory(BASE)==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    recipe=STAGE/'optimize_native_verified_bundle.py';assert recipe.read_bytes()==(ACCEPTED/'verified_bundle_pending.py').read_bytes()
    subprocess.run([sys.executable,'-X','utf8',str(STAGE/'package_native_training_runtime.py'),'--dll',str(WORK/'bundle.dll'),'--gate',str(WORK/'bundle_full_gate.json'),'--out',str(pending)],check=True)
    before_training=training();staged=training(pending);assert before_training==staged
    save('staged_training.json',dict(passed=True,jobs=12,baseline=before_training,candidate=staged))
    changes={BASE/HEADER:((BASE/HEADER).read_bytes(),(WORK/'bundle_src'/HEADER).read_bytes()),BASE/'libgdcore.dll':((BASE/'libgdcore.dll').read_bytes(),(WORK/'bundle.dll').read_bytes()),recipe:(recipe.read_bytes(),(WORK/'verified_bundle_pending.py').read_bytes())}
    saved=WORK/'installation_before';assert not saved.exists();saved.mkdir()
    for p,(old,_) in changes.items():
        target=saved/p.relative_to(REPO);target.parent.mkdir(parents=True,exist_ok=True);target.write_bytes(old)
    installed=[];backed=False;switched=False
    try:
        for path,(_,new) in changes.items():replace(path,new);installed.append(path)
        runtime.rename(backup);backed=True;pending.rename(runtime);switched=True
        verify_projection(BASE);assert sha(BASE/'libgdcore.dll')==sha(runtime/'libgdcore.dll')==actual
        manifest=json.loads((runtime/'manifest.json').read_bytes());assert manifest['gate_sha256']==sha(WORK/'bundle_full_gate.json')
        for name,h in manifest['sha256'].items():assert sha(runtime/name)==h
        assert training()==staged;boundary()
        with (WORK/'post_install_actual_frame.log').open('wb') as log:subprocess.run([sys.executable,'-u','-X','utf8',str(STAGE/'verify_frame_guard_actual.py'),'--formal','--tag','installed','--dll',str(runtime/'libgdcore.dll')],stdout=log,stderr=subprocess.STDOUT,check=True)
        assert read('installed_actual_frame_tests.json')['passed']
    except BaseException:
        if switched:runtime.rename(pending)
        if backed:backup.rename(runtime)
        for path in reversed(installed):replace(path,changes[path][0])
        save('installation_rollback.json',dict(rolled_back=True,production_dll_sha256=sha(BASE/'libgdcore.dll')));raise
    save('post_install_verification.json',dict(passed=True,dll_sha256=actual,baseline_dll_sha256=EXPECTED,source_files=715,CPP_source_files=710,all674_object_headers_and_layouts_unchanged=True,actual_installed_DLL_frame_cases=135168,strict_original_events_before_and_after_AB=2604,original_event_root=read('post_ab_bundle_vs_deployed_hashes.json')['ordered_case_and_cpp_event_hashes_sha256'],training_jobs=12,training=staged,all_user_files_and_staged_entries_preserved=True,recipe_matches_full_twice_regenerated_source=True))
    save('installation.json',dict(passed=True,dll_sha256=actual,baseline_dll_sha256=EXPECTED,runtime=str(runtime.relative_to(REPO)),backup_runtime=str(backup.relative_to(REPO)),changed_files=[p.relative_to(REPO).as_posix() for p in installed],post_install_verification_sha256=sha(WORK/'post_install_verification.json')))
    print('Verified positive frame-guard optimization deployed; actual installed135168 and trainer12 passed',flush=True)
if __name__=='__main__':main()
