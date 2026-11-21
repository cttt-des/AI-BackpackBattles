"""Predeclare the same-path composition and amortized fixed200 measurements."""
import ast
import json
from pathlib import Path

STAGE=Path(__file__).resolve().parent
OLD=STAGE/'native_perf50/event_identity_bundle'
WORK=STAGE/'native_perf50/event_emission_bundle'
PROBE=STAGE/'native_perf50/event_emission_probe'


def main():
    assert not WORK.exists()
    assert json.loads((PROBE/'measurement_worker_smoke.json').read_bytes())['passed']
    WORK.mkdir()
    for path in OLD.glob('*.py'):
        text=path.read_text('utf8').replace('event_identity_bundle','event_emission_bundle').replace('native-event-identity-','native-event-emission-')
        if path.name in ('audit_verify.py','inspect_variant.py','finish_gate.py'):
            text=text.replace("('fast_identities','fallbacks')","('fast_identities','fallbacks','fast_emissions','emission_fallbacks')")
            if path.name=='audit_verify.py':text=text.replace('identity_before=[identity_stat(i) for i in range(2)]','identity_before=[identity_stat(i) for i in range(4)]').replace('identity_stat(i)-identity_before[i] for i in range(2)','identity_stat(i)-identity_before[i] for i in range(4)')
            if path.name=='inspect_variant.py':
                text=text.replace('typed_before=[identity(i) for i in range(2)]','typed_before=[identity(i) for i in range(4)]').replace('identity(i)-typed_before[i] for i in range(2)','identity(i)-typed_before[i] for i in range(4)')
                text=text.replace("    assert report['event_identity_coverage']['fast_identities']>0", "    assert report['event_identity_coverage']['fast_identities']>0 and report['event_identity_coverage']['fast_emissions']>0")
            if path.name=='finish_gate.py':text=text.replace('identity_counts=[0,0]','identity_counts=[0]*4').replace('    assert identity_counts[0]>0','    assert identity_counts[0]>0 and identity_counts[2]>0')
        if path.name=='run_comparison.py':
            text=text.replace("'compare_native_isolated.py'","'compare_native_isolated_blocks.py'")
            text=text.replace("'--pairs','8','--warmup-seconds'","'--pairs','8','--batch-repetitions','4','--warmup-seconds'")
        if path.name=='verify_installed.py':
            text=text.replace("assert audit['event_identity_coverage']['fast_identities']>0", "assert audit['event_identity_coverage']['fast_identities']>0 and audit['event_identity_coverage']['fast_emissions']>0")
        if path.name=='save_checkpoint.py':
            text=text.replace("'event_identity_probe','frame_segments_bundle'", "'event_emission_probe','event_identity_probe','event_identity_bundle','frame_segments_bundle'")
            text=text.replace('    audit=json.loads', "    paths.update(STAGE/p for p in ('prototype_native_event_identity_bundle.py','setup_event_identity_bundle.py','prototype_native_event_emission_bundle.py','setup_event_emission_bundle.py','event_emission_fastpath.hpp','prepare_event_emission_preflight.py','probe_native_event_emission_bus.py','test_native_event_emission.cpp','measure_native_corpus_blocks.py','prepare_native_block_comparison.py','compare_native_isolated_blocks.py'))\n    audit=json.loads",1)
            text=text.replace('perf: construct event emitter identities once with strict replay validation','perf: compose verified event identity and emission ID paths')
        ast.parse(text,filename=path.name);(WORK/path.name).write_text(text,encoding='utf8',newline='\n')
    # The generation provenance remains the accepted hot coverage baseline.
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan['components']=['retained one-allocation emitter identity','known generated instance/signal ID composition']
    plan['measurement']['batches_per_arm']=4
    plan['measurement']['unchanged_fixed_fights_per_batch']=200
    plan['measurement']['outer_cpu_clock_amortized_over_fights']=800
    plan['measurement']['report_times_normalized_per_200']=True
    plan['measurement']['raw_each_batch_results_and_times_retained']=True
    plan['measurement']['reason']='PriorCPUtimes had many15.625ms steps and ties. Four identical fixed200 batches amortize that granularity, before observing this candidate; preserve the positive-median gates.'
    plan['required_before_comparison'].append('4417 original emission ID cases including unknown C++ overrides and arithmetic limits; every repeated200 result hash must match')
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared event composition;3x8 AB/BA pairs, each arm fixed200 repeated4 times, unchanged2604/raw24 gates')


if __name__=='__main__':main()
