"""Freeze the frame-local combination against deployed63D with the same gates."""
import ast
import json
from prepare_native_frame_values import STAGE,WORK as PROBE,ACCEPTED,EXPECTED,ARCHIVE,sha
WORK=STAGE/'native_perf50/frame_value_bundle'
OLD_SHA='5ddb2c1b15ad7ab7dfe1a8f2640701abddf6da88600b2930e55fc85165b59209'
OLD_ARCHIVE='4bc0f346988f01e046b6ac81ec1630223d0683b5'

def once(t,a,b):
    assert t.count(a)==1,(a[:120],t.count(a));return t.replace(a,b,1)
def save(p,t):
    ast.parse(t,filename=str(p));assert not p.exists();p.write_text(t,encoding='utf8',newline='\n')
def adapt(t):
    for a,b in [('prototype_native_scalar_guards_bundle','prototype_native_frame_values_bundle'),
            ('prepare_native_scalar_guards','prepare_native_frame_values'),('verify_native_scalar_guards','verify_frame_value_truth'),
            ('verify_scalar_guard_private','verify_frame_value_private'),('verify_scalar_guard_display','verify_frame_value_display'),
            ('verify_scalar_guard_control','verify_frame_value_control'),('verify_scalar_guards_build_options','verify_frame_values_build_options'),
            ('scalar_guards_bundle','frame_value_bundle'),('scalar_guards_prototype','frame_value_prototype'),
            ('scalar-guards-formal-','frame-values-formal-'),(OLD_SHA,EXPECTED),(OLD_ARCHIVE,ARCHIVE)]:t=t.replace(a,b)
    return t
def main():
    suite=json.loads((PROBE/'semantic_suite.json').read_bytes());assert suite['passed'] and suite['total_cases']==335776
    assert not WORK.exists();WORK.mkdir()
    for p in ACCEPTED.glob('*.py'):
        if p.name in ('verified_bundle_pending.py','wait_calibration_window.py'):continue
        t=adapt(p.read_text('utf8'))
        t=t.replace("WORK.parent/'display_storage_bundle/","WORK.parent/'scalar_guards_bundle/")
        t=t.replace("'native_display_storage_bundle_bundle_'","'native_scalar_guards_bundle_bundle_'")
        if p.name=='build_bundle.py':
            t=once(t,"STAGE/'native_perf50/restored_snapshots_bundle/checkpoint_receipt.json'","STAGE/'native_perf50/scalar_guards_bundle/checkpoint_receipt.json'")
            t=once(t,'assert len(files)==707','assert len(files)==708')
            t=once(t,"'verified_source_files':707","'verified_source_files':708")
            t=once(t,'deployment and707 sources','deployment and708 sources')
        if p.name=='prepare_regeneration.py':
            t=once(t,"OLD=WORK.parent/'display_storage_bundle'","OLD=WORK.parent/'scalar_guards_bundle'")
            t=t.replace('native_perf50/display_storage_bundle','native_perf50/scalar_guards_bundle')
        save(WORK/p.name,t)
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp','bounded_followup_policy.json'):(WORK/name).write_bytes((ACCEPTED/name).read_bytes())
    plan=json.loads((ACCEPTED/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,latest_remote_verified_production_backup=ARCHIVE,
        baseline_source_files=708,candidate_source_files=708,components=['frame-local scalar truth','Null override copy avoidance'],
        full_source_changes=['native_inline_dispatch.hpp'],existing_scalar_equality_unchanged=True,
        existing_private_display_control_and_generated_scalar_truth_retained=True,
        semantic_suite_sha256=sha(PROBE/'semantic_suite.json'),full20_new18PGO_required=True,
        fresh_profile='native_perf50/scalar_guards_followup_profile/profile_depth64.json',
        fresh_profile_sha256=sha(STAGE/'native_perf50/scalar_guards_followup_profile/profile_depth64.json'),
        target200_requires_no_omitted_valid_deployments=True)
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    save(STAGE/'verify_frame_values_build_options.py',adapt((STAGE/'verify_scalar_guards_build_options.py').read_text('utf8')))
    driver=adapt((STAGE/'run_scalar_guards_formal.py').read_text('utf8')).replace('RETAINED as BACKUP','ACCEPTED as BACKUP')
    save(STAGE/'run_frame_values_formal.py',driver)
    save(STAGE/'close_frame_values_round.py',adapt((STAGE/'close_scalar_guards_round.py').read_text('utf8')))
    review=adapt((STAGE/'review_scalar_guards_release.py').read_text('utf8'))
    review=once(review,"sorted(['gd_rt.hpp',*[f'gen/shards/shard_{i:02d}.cpp' for i in range(16)],'native_private_snapshots.hpp'])","['native_inline_dispatch.hpp']")
    save(STAGE/'review_frame_values_release.py',review)
    print(json.dumps(dict(prepared=True,source_files=708,baseline_source_files=708,scripts=len(list(WORK.glob('*.py'))),changed_header_only=True)),flush=True)

if __name__=='__main__':main()
