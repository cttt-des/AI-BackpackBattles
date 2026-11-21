"""Keep the standard gates and build only the screened event identity change."""
import ast
import json
from pathlib import Path
import re

STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/typed_read_bundle'
WORK=STAGE/'native_perf50/event_identity_bundle'
PROBE=STAGE/'native_perf50/event_identity_probe'


def main():
    assert not WORK.exists()
    screen=json.loads((PROBE/'bus_screen.json').read_bytes())
    assert screen['passed'] and screen['metrics']['cpu_s']['paired_median_time_reduction_pct']>0
    assert json.loads((PROBE/'bus_correctness_baseline.json').read_bytes())['cases']==320
    WORK.mkdir()
    for p in OLD.glob('*.py'):
        if p.name=='generate_typed_read_tests.py':continue
        text=p.read_text('utf8').replace('typed_read_bundle','event_identity_bundle').replace('native-typed-read-','native-event-identity-')
        if p.name=='resume_build.py':
            text=text.replace("exports.add('gd_diag_native_typed_read_stat')","exports.add('gd_diag_native_event_identity_stat')")
        if p.name in ('audit_verify.py','inspect_variant.py','finish_gate.py','verify_installed.py'):
            for before,after in (
                ('gd_diag_native_typed_read_stat','gd_diag_native_event_identity_stat'),
                ('typed_read_stat','identity_stat'),('typed_read_before','identity_before'),
                ('typed_read_report','identity_report'),('typed_counts','identity_counts'),
                ('native_typed_read_audit.json','native_event_identity_audit.json'),
                ('typed_read_coverage','event_identity_coverage'),
                ("('property_reads','pure_method_reads')","('fast_identities','fallbacks')")):
                text=text.replace(before,after)
            text=re.sub(r'\btyped\b','identity',text)
            text=text.replace("    assert all(value>0 for value in report['event_identity_coverage'].values())", "    assert report['event_identity_coverage']['fast_identities']>0")
            text=text.replace("    assert report['event_identity_coverage']['property_reads']==report['property_coverage']['field_hits']\n",'')
            text=text.replace('    assert all(value>0 for value in identity_counts) and identity_counts[0]==property_counts[0]','    assert identity_counts[0]>0')
            text=text.replace("    assert all(value>0 for value in audit['event_identity_coverage'].values())", "    assert audit['event_identity_coverage']['fast_identities']>0")
            text=text.replace("    assert audit['event_identity_coverage']['property_reads']==audit['property_coverage']['field_hits']\n",'')
            text=text.replace("'typed_read_test.json'","'event_identity_tests.json'")
        if p.name=='verify_resolved.py':
            text=text.replace('tests=(("test_native_typed_reads.cpp","typed_read_test.json",["-I",str(WORK)]),','tests=(')
        if p.name=='validate_then_compare.py':
            text=text.replace("    run('generate_typed_read_tests.py','typed_read_test_generation.log')\n",'')
            text=text.replace("    run('verify_resolved.py','verify.log')", "    run('verify_event_identity.py','event_identity_tests.log')\n    run('verify_resolved.py','verify.log')")
        if p.name=='save_checkpoint.py':
            text=text.replace("'native_typed_read_audit.json'","'native_event_identity_audit.json'")
            text=text.replace("'setup_typed_read_qualification.py','test_native_typed_reads.cpp'", "'setup_typed_read_qualification.py','test_native_typed_reads.cpp'")
            text=text.replace('    audit=json.loads', "    paths.update(STAGE/p for p in ('event_identity_fastpath.hpp','event_identity_receiver_fastpath.hpp','test_native_event_identity.cpp','test_native_event_identity_bus.cpp','probe_native_event_identity.py','probe_native_event_identity_bus.py','prepare_event_identity_preflight.py','prototype_native_frame_segments_bundle.py','setup_frame_segments_bundle.py','run_frame_segments_preflight.py','test_native_frame_segments.cpp','test_native_timer_chunks.cpp','prototype_native_scalar_math_bundle.py','setup_scalar_math_bundle.py','setup_scalar_math_qualification.py','test_native_numeric_math.cpp','prototype_native_scalar_math_ordered_bundle.py','setup_scalar_math_ordered_bundle.py','test_native_numeric_math_ordered.cpp','test_native_nan_order.cpp','optimize_native_ordered_nan.py','prototype_native_typed_read_bundle.py','setup_typed_read_bundle.py'))\n    for label in ('event_identity_probe','frame_segments_bundle','typed_read_bundle','scalar_math_bundle','scalar_math_ordered_bundle'):\n        prior=WORK.parent/label\n        paths.update(p for p in prior.iterdir() if p.is_file())\n        paths.update(p for p in (prior/'bundle_src').rglob('*') if p.is_file())\n    audit=json.loads",1)
            text=text.replace('perf: deploy typed pure reads with full replay validation','perf: construct event emitter identities once with strict replay validation')
            text=text.replace('backup: preserve verified typed reads and all strict receipts','backup: preserve verified event identities and the complete path review')
        ast.parse(text,filename=p.name);(WORK/p.name).write_text(text,encoding='utf8',newline='\n')
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan['components']=['one event-bus emitter identity construction fast path with original fallback']
    plan['new_object_or_context_layout']=False
    plan['screening_before_full_build']={'primitive_cases':24288,'bus_cases':320,'bus_local_cpu_median_reduction_pct':screen['metrics']['cpu_s']['paired_median_time_reduction_pct'],'bus_local_wall_median_reduction_pct':screen['metrics']['wall_s']['paired_median_time_reduction_pct'],'scope':'local event-bus fixture; not whole-fight speedup','long_screen_pairs':8,'events_per_arm':1000000}
    plan['no_unrelated_retained_components']=True
    plan['required_before_comparison']=[x for x in plan['required_before_comparison'] if 'pure-method' not in x.lower()]
    plan['required_before_comparison'].append('320 actual-baseline event-bus results, trace snapshot/unknown callback paths and24288 primitive identity values')
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared isolated event identity candidate and unchanged fixed200/2604/24-batch gates')


if __name__=='__main__':main()
