"""Freeze the distinct identity/lookup candidate and retain established gates."""
import ast
import json
from prepare_native_identity_lookup import STAGE,WORK as PROBE,ACCEPTED,EXPECTED,ARCHIVE,sha
WORK=STAGE/'native_perf50/identity_lookup_bundle'
OLD_SHA='0a6d24f459eb1011a0bfcc1bc5c4188c1ca67add410b9caf0e04c8f5d30d44d4'
OLD_ARCHIVE='4cbfd55b10a7dae66529c41da01cbcce63ae66d2'

def once(t,a,b):
    assert t.count(a)==1,(a[:140],t.count(a));return t.replace(a,b,1)
def save(p,t):
    ast.parse(t,filename=str(p))
    if p.exists():assert p.read_text('utf8')==t,p
    else:p.write_text(t,encoding='utf8',newline='\n')
def adapt(t):
    for a,b in [('prototype_native_container_builtins_bundle','prototype_native_identity_lookup_bundle'),
            ('prepare_native_container_builtins','prepare_native_identity_lookup'),('verify_native_container_builtins','verify_identity_lookup_builtins'),
            ('verify_container_builtin_truth','verify_identity_lookup_truth'),('verify_container_builtin_private','verify_identity_lookup_private'),
            ('verify_container_builtin_display','verify_identity_lookup_display'),('verify_container_builtin_control','verify_identity_lookup_control'),
            ('verify_container_builtins_build_options','verify_identity_lookup_build_options'),
            ('review_container_builtins_release','review_identity_lookup_release'),
            ('container_builtins_bundle','identity_lookup_bundle'),('container_builtins_prototype','identity_lookup_prototype'),
            ('container-builtins-formal-','identity-lookup-formal-'),(OLD_SHA,EXPECTED),(OLD_ARCHIVE,ARCHIVE)]:t=t.replace(a,b)
    return t
def main():
    suite=json.loads((PROBE/'semantic_suite.json').read_bytes());assert suite['passed'] and suite['total_cases']==860304
    assert not (WORK/'build_first.log').exists();WORK.mkdir(exist_ok=True)
    for p in ACCEPTED.glob('*.py'):
        if p.name in ('verified_bundle_pending.py','wait_calibration_window.py'):continue
        t=adapt(p.read_text('utf8'))
        t=t.replace("WORK.parent/'frame_value_bundle/","WORK.parent/'container_builtins_bundle/")
        t=t.replace("'native_frame_value_bundle_bundle_'","'native_container_builtins_bundle_bundle_'")
        if p.name=='build_bundle.py':
            t=once(t,"STAGE/'native_perf50/frame_value_bundle/checkpoint_receipt.json'","STAGE/'native_perf50/container_builtins_bundle/checkpoint_receipt.json'")
        if p.name=='prepare_regeneration.py':
            t=once(t,"OLD=WORK.parent/'frame_value_bundle'","OLD=WORK.parent/'container_builtins_bundle'")
            t=t.replace('native_perf50/frame_value_bundle','native_perf50/container_builtins_bundle')
        if p.name=='verify_motion_indices.py':
            t=once(t,'        else:assert sha(path)==digest,name',"        elif name=='native_scalar_equal.hpp':\n            import sys\n            sys.path.insert(0,str(STAGE))\n            from prepare_native_identity_lookup import IDENTITY,LOOKUP,ACCEPTED,verify_projection\n            frozen=json.loads((WORK/'source_before_build.json').read_bytes())\n            assert sha(path)==frozen[name] and sha(ACCEPTED/'bundle_src'/name)==digest\n            current=path.read_text('utf8');assert current.count(IDENTITY)==current.count(LOOKUP)==1\n            original=current.replace(IDENTITY,'',1).replace(LOOKUP,'',1)\n            assert hashlib.sha256(original.encode()).hexdigest()==digest\n            assert verify_projection(WORK/'bundle_src')['exact_inverse_matches_retained_source']\n        else:assert sha(path)==digest,name")
        if p.name=='validate_then_compare.py':
            anchor="    run('verify_container_builtins.py','container_builtins_tests.log')"
            t=once(t,anchor,"    run('verify_identity_lookup.py','identity_lookup_tests.log')\n"+anchor)
        if p.name=='verify_object_routes_after_ab.py':
            anchor="    result=dict(container_builtin_cases=builtins_report['cases'],"
            insertion="    from verify_native_identity_lookup import verify as verify_lookup\n    lookup=target/'identity_lookup';lookup.mkdir()\n    lookup_report=verify_lookup(WORK/'bundle_src',WORK/'bundle.dll',lookup/'correctness.json')\n"
            t=once(t,anchor,insertion+anchor.replace('result=dict(',"result=dict(identity_lookup_cases=lookup_report['cases'],"))
        if p.name=='install_verified.py':
            anchor="    assert post_ab['container_builtin_cases']==128128"
            t=once(t,anchor,anchor+"\n    assert post_ab['identity_lookup_cases']==396400\n    lookup=json.loads((WORK/'identity_lookup_tests.json').read_bytes());assert lookup['passed'] and lookup['cases']==396400 and lookup['dll_sha256']==actual")
        if p.name=='verify_installed.py':
            anchor="    builtin=read('container_builtins_tests.json');assert builtin['passed'] and builtin['cases']==128128 and builtin['dll_sha256']==actual"
            t=once(t,anchor,anchor+"\n    lookup=read('identity_lookup_tests.json');assert lookup['passed'] and lookup['cases']==396400 and lookup['dll_sha256']==actual")
            t=t.replace('# Generated header text is retained; GdArr/BattleCtx layout changes are intentional and were fully rebuilt.',
                '# All674 generated object headers and all layouts are unchanged in this round.')
        save(WORK/p.name,t)
    save(WORK/'verify_identity_lookup.py',f'''import sys
from pathlib import Path
WORK=Path(__file__).resolve().parent
sys.path.insert(0,str(WORK.parents[1]))
from verify_native_identity_lookup import verify
if __name__=='__main__':
    report=verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'identity_lookup_tests.json')
    assert report['cases']==396400 and report['fixture_sha256']=='{sha(STAGE/'test_native_identity_lookup.cpp')}'
''')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp','bounded_followup_policy.json'):(WORK/name).write_bytes((ACCEPTED/name).read_bytes())
    plan=json.loads((ACCEPTED/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,latest_remote_verified_production_backup=ARCHIVE,
        baseline_source_files=708,candidate_source_files=708,full_source_changes=['gd_rt.cpp','native_scalar_equal.hpp'],
        components=['pure identity equality cases','conservative array/dictionary lookup equality'],identity_lookup_cases=396400,
        identity_lookup_fixture_sha256=sha(STAGE/'test_native_identity_lookup.cpp'),
        fresh_profile='native_perf50/container_builtins_followup_profile/profile_depth64.json',
        fresh_profile_sha256=sha(STAGE/'native_perf50/container_builtins_followup_profile/profile_depth64.json'),
        diagnostic_frequencies_not_release_cost_or_gain=True,all_prior_components_retained=True,
        semantic_suite_sha256=sha(PROBE/'semantic_suite.json'),total_semantic_cases=860304,
        float_lookup_uses_original_comparison_body=True,original_gd_eq_body_unchanged=True,
        fixture_setup_repair_record='native_perf50/identity_lookup_prototype/fixture_repair.json')
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    options=adapt((STAGE/'verify_container_builtins_build_options.py').read_text('utf8'))
    options=options.replace('compared_with_verified_5DDB_objects=True','compared_with_current_verified_production_objects=True')
    save(STAGE/'verify_identity_lookup_build_options.py',options)
    save(STAGE/'run_identity_lookup_formal.py',adapt((STAGE/'run_container_builtins_formal.py').read_text('utf8')))
    save(STAGE/'close_identity_lookup_round.py',adapt((STAGE/'close_container_builtins_round.py').read_text('utf8')))
    review=adapt((STAGE/'review_container_builtins_release.py').read_text('utf8'))
    review=once(review,"assert sorted(changed)==['native_inline_dispatch.hpp']","assert sorted(changed)==['gd_rt.cpp','native_scalar_equal.hpp']")
    review=once(review,"'scalar_truth_tests.json','container_builtins_tests.json')","'scalar_truth_tests.json','container_builtins_tests.json','identity_lookup_tests.json')")
    anchor="    assert read('container_builtins_tests.json')['cases']==read('post_ab_directed_regressions.json')['container_builtin_cases']==128128"
    review=once(review,anchor,anchor+"\n    assert read('identity_lookup_tests.json')['cases']==read('post_ab_directed_regressions.json')['identity_lookup_cases']==396400")
    save(STAGE/'review_identity_lookup_release.py',review)
    print(json.dumps(dict(prepared=True,scripts=len(list(WORK.glob('*.py'))),source_files=708,total_semantic_cases=860304)),flush=True)

if __name__=='__main__':main()
