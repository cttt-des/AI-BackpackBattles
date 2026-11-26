"""Freeze the complete existing qualification protocol for isolated storage."""
import ast
import json
from prepare_native_display_storage import STAGE,WORK as PROBE,ACCEPTED,EXPECTED,ARCHIVE,once

WORK=STAGE/'native_perf50/display_storage_bundle'

def main():
    proof=json.loads((PROBE/'correctness.json').read_bytes())
    retained=json.loads((PROBE/'retained_control.json').read_bytes())
    assert proof['passed'] and retained['passed'];size=proof['candidate_core_item_bytes']
    assert not WORK.exists();WORK.mkdir()
    for p in ACCEPTED.glob('*.py'):
        if p.name=='verified_bundle_pending.py':continue
        t=p.read_text('utf8').replace('control_word_bundle','display_storage_bundle')
        t=t.replace('control_word_prototype','display_storage_prototype')
        t=t.replace('prepare_native_control_word','prepare_native_display_storage')
        t=t.replace('prototype_native_control_word_bundle','prototype_native_display_storage_bundle')
        t=t.replace('verify_native_control_word','verify_native_display_control')
        t=t.replace('verify_native_active_cooldown_final','verify_native_display_active')
        t=t.replace('verify_control_word_build_options.py','verify_display_storage_build_options.py')
        t=t.replace('584aef472686dc09bb5abda831c358a2026a2fe3',ARCHIVE)
        t=t.replace('f950b64c74684ae70ce4e41b9622541c849da0121e1235ab88b7aaface22a6d7',EXPECTED)
        if p.name=='build_bundle.py':
            t=t.replace("STAGE/'native_perf50/active_prefetch_bundle/checkpoint_receipt.json'","STAGE/'native_perf50/control_word_bundle/checkpoint_receipt.json'")
            t=t.replace('control-word-formal-','display-storage-formal-')
        if p.name=='prepare_regeneration.py':
            t=once(t,"OLD=WORK.parent/'object_routes_bundle'","OLD=WORK.parent/'control_word_bundle'")
            t=t.replace(".replace('native_perf50/object_routes_bundle','native_perf50/display_storage_bundle')", ".replace('native_perf50/control_word_bundle','native_perf50/display_storage_bundle')")
        if p.name=='validate_then_compare.py':
            anchor="    run('verify_control_word.py','control_word_tests.log')"
            t=once(t,anchor,anchor+"\n    run('verify_display_storage.py','display_storage_tests.log')")
        if p.name=='verify_targeted_timers.py':
            t=once(t,"    assert layouts['baseline']['CoreItem']==layouts['candidate']['CoreItem']==1792",
                "    assert layouts['baseline']['CoreItem']==1792 and layouts['candidate']['CoreItem']=="+str(size))
            t=once(t,"WORK.parent/'object_routes_bundle/targeted_timer_tests.json'","WORK.parent/'control_word_bundle/targeted_timer_tests.json'")
            t=once(t,"    assert layouts['baseline']==layouts['candidate'] and layouts['candidate']['BattleCtx']==328",
                "    assert {k:v for k,v in layouts['baseline'].items() if k!='CoreItem'}=={k:v for k,v in layouts['candidate'].items() if k!='CoreItem'} and layouts['candidate']['BattleCtx']==328")
        if p.name=='verify_object_routes_after_ab.py':
            anchor="    result=dict(control_word_cases=44608,"
            t=once(t,anchor,"    from verify_native_display_storage import verify as verify_display\n    verify_display(WORK/'bundle_src',WORK/'bundle.dll',target/'display_storage.json')\n"+anchor)
            t=once(t,'result=dict(control_word_cases=44608,','result=dict(display_storage_cases=21888,control_word_cases=44608,')
        if p.name in ('finish_gate.py','verify_installed.py'):
            t=t.replace("WORK.parent/'object_routes_bundle/", "WORK.parent/'control_word_bundle/")
            t=t.replace("'native_object_routes_bundle_bundle_'","'native_control_word_bundle_bundle_'")
        if p.name=='verify_installed.py':
            t=once(t,'STAGE=WORK.parents[1]\n','STAGE=WORK.parents[1]\nsys.path.insert(0,str(STAGE))\n')
            t=once(t,"    assert all(path.read_bytes()==(old/path.relative_to(native)).read_bytes() for path in headers)",
                "    changed_header=native/'gen/hdrs/Gd__gd_core__CoreItem.hpp'\n    assert all(path.read_bytes()==(old/path.relative_to(native)).read_bytes() for path in headers if path!=changed_header)\n    from prepare_native_display_storage import verify_projection\n    assert verify_projection(native)['passed']\n    display=read('display_storage_tests.json');assert display['passed'] and display['cases']==21888 and display['candidate_core_item_bytes']=="+str(size))
            t=t.replace("'unchanged_object_headers':674","'unchanged_object_headers':673,'declared_core_item_layout_change':True")
        if p.name=='install_verified.py':
            anchor="    assert post_ab['control_word_cases']==44608"
            t=once(t,anchor,anchor+"\n    assert post_ab['display_storage_cases']==21888\n    display=json.loads((WORK/'display_storage_tests.json').read_bytes());assert display['passed'] and display['dll_sha256']==actual and display['candidate_core_item_bytes']=="+str(size))
        ast.parse(t,filename=p.name);(WORK/p.name).write_text(t,encoding='utf8',newline='\n')
    (WORK/'verify_display_storage.py').write_text('''import sys
from pathlib import Path
WORK=Path(__file__).resolve().parent
sys.path.insert(0,str(WORK.parents[1]))
from verify_native_display_storage import verify
if __name__=='__main__':verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'display_storage_tests.json')
''',encoding='utf8')
    for name in ['member_probe_cases.hpp','native_property_test_cases.hpp','bounded_followup_policy.json']:
        (WORK/name).write_bytes((ACCEPTED/name).read_bytes())
    plan=json.loads((ACCEPTED/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,
        latest_remote_verified_production_backup=ARCHIVE,prior_trial_remote_archive=ARCHIVE,
        components=['inline first display array storage, all reads/calls retained'],
        full_source_changes=['gen/hdrs/Gd__gd_core__CoreItem.hpp','gen/shards/shard_00.cpp'],
        intentional_layout_changes=[dict(type='CoreItem',old_bytes=1792,new_bytes=size)],
        new_layout_changes=True,full20_rebuild_required=True,local_display_cases=21888,
        all_object_container_context_layouts_unchanged=False,
        container_context_and_watch_layouts_unchanged=True,object_layout_change_declared=True,
        retained_control_cases=44608,semantic_dll_not_used_for_timing=True,
        no_new_branches=True,preserve_current_branch_and_index=True)
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    options=(STAGE/'verify_control_word_build_options.py').read_text('utf8')
    options=options.replace('prepare_native_control_word','prepare_native_display_storage').replace('control_word_bundle','display_storage_bundle')
    options=once(options,"ACCEPTED/'recovered_release_objects.json'","ACCEPTED/'release_objects.json'")
    options=once(options,"Path(json.loads((ACCEPTED/'live_recovered_build.json').read_bytes())['object_directory'])","Path(baseline['object_directory'])")
    options=options.replace('compared_with_verified_F950_objects','compared_with_verified_680_objects')
    ast.parse(options);target=STAGE/'verify_display_storage_build_options.py';assert not target.exists();target.write_text(options,encoding='utf8',newline='\n')
    driver=(STAGE/'run_control_word_formal.py').read_text('utf8')
    driver=driver.replace('prepare_native_control_word','prepare_native_display_storage').replace('control_word_bundle','display_storage_bundle')
    driver=once(driver,'STAGE,WORK as PROBE,BASE,BACKUP,EXPECTED,ARCHIVE,sha','STAGE,WORK as PROBE,BASE,ACCEPTED as BACKUP,EXPECTED,ARCHIVE,sha')
    ast.parse(driver);target=STAGE/'run_display_storage_formal.py';assert not target.exists();target.write_text(driver,encoding='utf8',newline='\n')
    close=(STAGE/'close_control_word_round.py').read_text('utf8').replace('control_word_bundle','display_storage_bundle')
    ast.parse(close);target=STAGE/'close_display_storage_round.py';assert not target.exists();target.write_text(close,encoding='utf8',newline='\n')
    print('Prepared isolated full20/fresh18 trial, original all gates retained, no branches created')

if __name__=='__main__':main()
