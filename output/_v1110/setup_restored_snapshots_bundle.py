"""Retain all real acceptance gates and use the corrected empirical-load policy."""
import ast
import json
from pathlib import Path
from prepare_restored_private_snapshots import STAGE,WORK as PROBE,ACCEPTED,EXPECTED,ARCHIVE,sha

WORK=STAGE/'native_perf50/restored_snapshots_bundle'
OLD_SHA='680f3e37ed7485daac1d6b023bc8530706efb22370a479a02b2e212609c39775'
OLD_ARCHIVE='6f14e73f2b7a6fd3a055dd8a858115cf339d3352'

def once(t,a,b):
    assert t.count(a)==1,(a[:150],t.count(a));return t.replace(a,b,1)
def save(path,text):ast.parse(text,filename=str(path));assert not path.exists();path.write_text(text,encoding='utf8',newline='\n')

def main():
    suite=json.loads((PROBE/'semantic_suite.json').read_bytes());assert suite['passed'] and suite['total_cases']==301376
    assert not WORK.exists();WORK.mkdir()
    for p in ACCEPTED.glob('*.py'):
        if p.name=='verified_bundle_pending.py':continue
        t=p.read_text('utf8').replace('display_storage_bundle','restored_snapshots_bundle')
        t=t.replace('display_storage_prototype','restored_snapshots_prototype')
        t=t.replace('prepare_native_display_storage','prepare_restored_private_snapshots')
        t=t.replace('prototype_native_display_storage_bundle','prototype_restored_snapshots_bundle')
        t=t.replace('prototype_native_restored_snapshots_bundle','prototype_restored_snapshots_bundle')
        t=t.replace('verify_native_display_control','verify_restored_control')
        t=t.replace('verify_native_display_storage','verify_restored_display_storage')
        t=t.replace('verify_display_storage_build_options.py','verify_restored_snapshots_build_options.py')
        t=t.replace(OLD_SHA,EXPECTED).replace(OLD_ARCHIVE,ARCHIVE)
        if p.name=='build_bundle.py':
            t=once(t,"STAGE/'native_perf50/control_word_bundle/checkpoint_receipt.json'","STAGE/'native_perf50/display_storage_bundle/checkpoint_receipt.json'")
            t=t.replace('display-storage-formal-','restored-snapshots-formal-')
            anchor="    shutil.copyfile(dll,WORK/'bundle.dll');print('resolved',digest(WORK/'bundle.dll'),flush=True)"
            policy="    save('user_load20_policy_20261126.json',dict(empirical_estimate_allowed_outside_observed_range=True,candidate_dll_sha256=digest(WORK/'bundle.dll'),authorization='Explicit user clarification2026-11-26',low_idle_window_required=False,all_original_AB_correctness_and_raw24_gates_retained=True))"
            t=once(t,anchor,anchor+'\n'+policy)
        if p.name=='resume_build.py':
            t=once(t,"    exports.add('gd_test_native_timer_control')","    exports.add('gd_test_native_timer_control')\n    exports.add('gd_diag_native_private_snapshot_stat')")
        if p.name=='prepare_regeneration.py':
            t=once(t,"OLD=WORK.parent/'control_word_bundle'","OLD=WORK.parent/'display_storage_bundle'")
            t=t.replace(".replace('native_perf50/control_word_bundle','native_perf50/restored_snapshots_bundle')", ".replace('native_perf50/display_storage_bundle','native_perf50/restored_snapshots_bundle')")
            t=once(t,'assert len(rows)==707','assert len(rows)==708')
        if p.name=='test_regeneration_guards.py':
            t=once(t,'if p.is_file())==707','if p.is_file())==708')
            t=once(t,"'source_inventory_verified':707","'source_inventory_verified':708")
        if p.name=='validate_then_compare.py':
            anchor="    run('verify_control_word.py','control_word_tests.log')"
            t=once(t,anchor,"    run('verify_private_snapshots.py','private_snapshots_tests.log')\n"+anchor)
        if p.name=='verify_targeted_timers.py':
            t=once(t,"WORK.parent/'control_word_bundle/targeted_timer_tests.json'","WORK.parent/'display_storage_bundle/targeted_timer_tests.json'")
            old="    assert {k:v for k,v in layouts['baseline'].items() if k!='CoreItem'}=={k:v for k,v in layouts['candidate'].items() if k!='CoreItem'} and layouts['candidate']['BattleCtx']==328"
            t=once(t,old,"    assert layouts['baseline']==layouts['candidate'] and layouts['candidate']['CoreItem']==2112 and layouts['candidate']['BattleCtx']==328")
        if p.name=='inspect_variant.py':
            anchor="    audit(1);before=[stat(i) for i in range(6)]"
            t=once(t,anchor,"    private_stat=sim.lib.gd_diag_native_private_snapshot_stat;private_stat.argtypes=[ctypes.c_uint];private_stat.restype=ctypes.c_uint64\n    private_before=[private_stat(i) for i in range(4)]\n"+anchor)
            line="    args.out.write_text(json.dumps(report,indent=2)+'\\n',encoding='utf8',newline='\\n')"
            insertion="    private_counts=[private_stat(i)-private_before[i] for i in range(4)]\n    expected_private=json.loads((Path(__file__).resolve().parent.parent/'restored_snapshots_prototype/build.json').read_bytes())['private_snapshot_counts']\n    assert private_counts==expected_private,(private_counts,expected_private)\n    report['private_snapshot_coverage']=dict(zip(('integer_view_fast','private_array_fallback','identity_captured','identity_eager'),private_counts))\n"
            t=once(t,line,insertion+line)
        if p.name=='verify_object_routes_after_ab.py':
            anchor="    result=dict(display_storage_cases=21888,control_word_cases=44608,"
            t=once(t,anchor,"    from verify_restored_private_snapshots import verify as verify_private\n    private=target/'private_snapshots';private.mkdir()\n    verify_private(WORK/'bundle_src',WORK/'bundle.dll',private/'correctness.json')\n"+anchor)
            t=once(t,'result=dict(display_storage_cases=21888,','result=dict(private_snapshot_cases=234880,display_storage_cases=21888,')
        if p.name in ('finish_gate.py','verify_installed.py'):
            t=t.replace("WORK.parent/'control_word_bundle/","WORK.parent/'display_storage_bundle/")
            t=t.replace("'native_control_word_bundle_bundle_'","'native_display_storage_bundle_bundle_'")
        if p.name=='run_release_measurements.py':
            t=once(t,"    subprocess.run([*python,str(WORK/'wait_calibration_window.py')],check=True)\n",'')
            t=once(t,"'--reference-load','20','--out'","'--reference-load','20','--allow-extrapolation','--out'")
        if p.name=='install_verified.py':
            t=t.replace('before_restored_snapshots_bundle_20261124','before_restored_snapshots_bundle_20261126')
            anchor="    assert post_ab['display_storage_cases']==21888"
            t=once(t,anchor,anchor+"\n    assert post_ab['private_snapshot_cases']==234880\n    private=json.loads((WORK/'private_snapshots_tests.json').read_bytes());assert private['passed'] and private['cases']==234880 and private['dll_sha256']==actual")
        if p.name=='verify_installed.py':
            t=once(t,'assert len(inventory)==707','assert len(inventory)==708')
            old="    assert all(path.read_bytes()==(old/path.relative_to(native)).read_bytes() for path in headers if path!=changed_header)"
            t=once(t,old,"    assert all(path.read_bytes()==(old/path.relative_to(native)).read_bytes() for path in headers)")
            t=t.replace("'production_source_files':707,'unchanged_object_headers':673,'declared_core_item_layout_change':True", "'production_source_files':708,'unchanged_object_headers':674,'declared_core_item_layout_change':False,'private_snapshot_cases':234880")
            anchor="    display=read('display_storage_tests.json');assert display['passed'] and display['cases']==21888 and display['candidate_core_item_bytes']==2112"
            t=once(t,anchor,anchor+"\n    private=read('private_snapshots_tests.json');assert private['passed'] and private['cases']==234880 and private['dll_sha256']==actual")
        save(WORK/p.name,t)
    save(WORK/'verify_private_snapshots.py',"import sys\nfrom pathlib import Path\nWORK=Path(__file__).resolve().parent\nsys.path.insert(0,str(WORK.parents[1]))\nfrom verify_restored_private_snapshots import verify\nif __name__=='__main__':verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'private_snapshots_tests.json')\n")
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp','bounded_followup_policy.json'):(WORK/name).write_bytes((ACCEPTED/name).read_bytes())
    plan=json.loads((ACCEPTED/'evaluation_plan.json').read_bytes())
    plan['required']=[row.replace('707-source','708-source') for row in plan['required']]
    plan.update(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,latest_remote_verified_production_backup=ARCHIVE,
        components=['restore private bounded integer views','restore pre-callback identity snapshots'],
        full_source_changes=['gen/shards/shard_00.cpp','gen/shards/shard_12.cpp','native_private_snapshots.hpp'],
        baseline_source_files=707,candidate_source_files=708,intentional_layout_changes=[],new_layout_changes=False,
        all_object_container_context_layouts_unchanged=True,object_layout_change_declared=False,
        private_snapshots_not_included=False,restored_private_cases=234880,retained_display_cases=21888,retained_control_cases=44608,
        first_calibration_eligibility=dict(required=False,reason='User requests empirical normalization from measured load; do not wait for20% coverage'),
        no_extrapolated_load20_if_outside_observations=False,empirical20_estimation_allowed=True,
        same_first24_raw_and_calibration_only=True,no_new_branches=True,preserve_current_branch_and_index=True)
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    options=(STAGE/'verify_display_storage_build_options.py').read_text('utf8')
    options=options.replace('prepare_native_display_storage','prepare_restored_private_snapshots').replace('display_storage_bundle','restored_snapshots_bundle').replace('compared_with_verified_680_objects','compared_with_verified_5DDB_objects')
    save(STAGE/'verify_restored_snapshots_build_options.py',options)
    driver=(STAGE/'run_display_storage_formal.py').read_text('utf8')
    driver=driver.replace('prepare_native_display_storage','prepare_restored_private_snapshots').replace('display_storage_bundle','restored_snapshots_bundle')
    save(STAGE/'run_restored_snapshots_formal.py',driver)
    close=(STAGE/'close_display_storage_round.py').read_text('utf8').replace('display_storage_bundle','restored_snapshots_bundle')
    close=once(close,"    subprocess.run([sys.executable,'-u','-X','utf8',str(WORK/'wait_calibration_window.py')],check=True)\n",'')
    save(STAGE/'close_restored_snapshots_round.py',close)
    review=(STAGE/'review_display_storage_release.py').read_text('utf8')
    review=review.replace('prepare_native_display_storage','prepare_restored_private_snapshots').replace('display_storage_bundle','restored_snapshots_bundle').replace('display_storage_prototype','restored_snapshots_prototype')
    review=once(review,"if sha(BASE/n)!=h","if not (BASE/n).exists() or sha(BASE/n)!=h")
    review=once(review,"['gen/hdrs/Gd__gd_core__CoreItem.hpp','gen/shards/shard_00.cpp']","['gen/shards/shard_00.cpp','gen/shards/shard_12.cpp','native_private_snapshots.hpp']")
    review=once(review,"for n in frozen)==707","for n in frozen)==708")
    review=once(review,"'control_word_tests.json','display_storage_tests.json')","'control_word_tests.json','display_storage_tests.json','private_snapshots_tests.json')")
    needle="    assert read('control_word_tests.json')['cases']==44608"
    review=once(review,needle,needle+"\n    assert read('private_snapshots_tests.json')['cases']==234880 and read('post_ab_directed_regressions.json')['private_snapshot_cases']==234880")
    old="    eligible=read('calibration_eligibility.json')\n    assert eligible['passed'] and len(eligible['qualifying_observations'])==3 and max(eligible['qualifying_observations'])<=12"
    review=once(review,old,"    policy=read('user_load20_policy_20261126.json')\n    assert policy['empirical_estimate_allowed_outside_observed_range'] and not policy['low_idle_window_required']")
    review=review.replace("'calibration_eligibility.json'","'user_load20_policy_20261126.json'")
    save(STAGE/'review_restored_snapshots_release.py',review)
    print('Prepared full20/fresh18,708-source reproduction, all retained gates, empirical20 normalization and no idle-window gate')

if __name__=='__main__':main()
