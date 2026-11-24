"""Retain the full frozen protocol around the new callback implementation."""
import ast
import json
from prepare_native_callback_dispatch import STAGE,EXPECTED,ARCHIVE,once

OLD=STAGE/'native_perf50/literal_spans_bundle'
WORK=STAGE/'native_perf50/callback_dispatch_bundle'

def main():
    assert not WORK.exists();WORK.mkdir()
    for path in OLD.glob('*.py'):
        if path.name in ('verified_bundle_pending.py','record_deployed_round.py','verify_literal_spans_after_ab.py'):continue
        text=path.read_text('utf8')
        text=text.replace('literal_spans_bundle','callback_dispatch_bundle').replace('event_factory_bundle','literal_spans_bundle')
        text=text.replace('literal_spans_prototype','callback_dispatch_prototype')
        text=text.replace('8c40f0b1b2cbb1ce5227f69757f89eca3bbc644a',ARCHIVE)
        text=text.replace('d8a7365191ad57a48ac378a7db77e8587169814f6f74298734f7d0b4786e3a76',EXPECTED)
        text=text.replace('verify_literal_spans_after_ab.py','verify_callback_dispatch_after_ab.py')
        text=text.replace('native-literal-spans-','native-callback-dispatch-')
        if path.name=='build_bundle.py':
            text=once(text,"STAGE/'native_perf50/storage_bundle/checkpoint_receipt.json'","STAGE/'native_perf50/literal_spans_bundle/checkpoint_receipt.json'")
        if path.name=='validate_then_compare.py':
            text=once(text,"    run('verify_resolved.py','verify.log')","    run('verify_callback_dispatch.py','callback_dispatch_tests.log')\n    run('verify_resolved.py','verify.log')")
        if path.name=='install_verified.py':
            text=once(text,"post_ab['affected_literal_span_cases'] == 5184","post_ab['affected_callback_cases'] == 126192 and post_ab['retained_literal_span_cases'] == 5184")
        if path.name=='verify_installed.py':
            text=once(text,"    assert read('literal_span_tests.json')['dll_sha256']==actual", "    assert read('literal_span_tests.json')['dll_sha256']==actual\n    assert read('callback_dispatch_tests.json')['passed'] and read('callback_dispatch_tests.json')['cases']==126192\n    assert read('callback_dispatch_tests.json')['dll_sha256']==actual")
            text=once(text,"'literal_span_cases':5184,","'callback_dispatch_cases':126192,'literal_span_cases':5184,")
            text=text.replace("('literal_span_tests.json','post_ab_directed_regressions.json'","('callback_dispatch_tests.json','literal_span_tests.json','post_ab_directed_regressions.json'")
        ast.parse(text,filename=path.name);(WORK/path.name).write_text(text,encoding='utf8',newline='\n')
    wrapper="import sys\nfrom pathlib import Path\nWORK=Path(__file__).resolve().parent\nsys.path.insert(0,str(WORK.parents[1]))\nfrom verify_native_callback_dispatch import verify\nif __name__=='__main__':verify(WORK/'bundle_src',WORK/'bundle.dll',WORK/'callback_dispatch_tests.json')\n"
    (WORK/'verify_callback_dispatch.py').write_text(wrapper,encoding='utf8')
    after=(OLD/'verify_literal_spans_after_ab.py').read_text('utf8')
    after=after.replace('from prepare_native_literal_spans import sha','from prepare_native_callback_dispatch import sha')
    after=after.replace('from verify_native_literal_spans import verify','from verify_native_callback_dispatch import verify\nfrom verify_native_literal_spans import verify as verify_retained')
    after=once(after,"    verify(WORK/'bundle_src',WORK/'bundle.dll',target/'literal_spans.json')", "    verify(WORK/'bundle_src',WORK/'bundle.dll',target/'callback_dispatch.json')\n    retained=target/'retained_literal';retained.mkdir()\n    verify_retained(WORK/'bundle_src',WORK/'bundle.dll',retained/'literal_spans.json')")
    after=after.replace('affected_literal_span_cases=5184','affected_callback_cases=126192,retained_literal_span_cases=5184')
    after=after.replace("{p.name:sha(p) for p in target.iterdir() if p.is_file()}","{p.relative_to(target).as_posix():sha(p) for p in target.rglob('*') if p.is_file()}")
    ast.parse(after);(WORK/'verify_callback_dispatch_after_ab.py').write_text(after,encoding='utf8',newline='\n')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp','bounded_followup_policy.json'):
        (WORK/name).write_bytes((OLD/name).read_bytes())
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,
        latest_remote_verified_production_backup=ARCHIVE,prior_trial_remote_archive=ARCHIVE,
        components=['65 observed uncached unbound callbacks via exact-type side table','private event argument spans through new callback routes'],
        local_independent_cases=dict(unknown_cpp_overrides=15600,real_generated_handler_scenarios=110592),
        local_original_dll_cases=126192,full_source_changes=['gd_rt.cpp','native_event_kernel.hpp','native_resolved_dispatch.hpp'],
        prior_literal_spans_retained=True,baseline_bound_concatenations=0,object_scope_only268_not_expanded=True,
        callback_counts_only_not_speed_claim=dict(generic_funcref=50121,private_literal=51219),
        previous_round_raw_and_normalized_rates_not_compared_as_code_gains=True)
    plan['required'][0]='All retained regressions plus126192 callback cases; exact707-source reproduction before freshPGO'
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared full20/new18PGO, fixed200 bounded24(+8), postAB126192+5184, strict2604, first raw24 and independent calibration24')

if __name__=='__main__':main()
