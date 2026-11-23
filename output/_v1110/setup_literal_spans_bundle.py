"""Freeze the retained protocol around the new, independently checked source."""
import ast
import json
from prepare_native_literal_spans import STAGE,EXPECTED,ARCHIVE,once

OLD=STAGE/'native_perf50/storage_bundle'
WORK=STAGE/'native_perf50/literal_spans_bundle'

def main():
    assert not WORK.exists();WORK.mkdir()
    for path in OLD.glob('*.py'):
        if path.name=='verified_bundle_pending.py':continue
        text=path.read_text('utf8')
        text=text.replace('storage_bundle','literal_spans_bundle').replace('storage_prototype','literal_spans_prototype')
        text=text.replace('prepare_native_literal_spans_bundle','prepare_native_literal_spans')
        text=text.replace('prototype_native_literal_spans_bundle','prototype_native_literal_spans_bundle')
        text=text.replace('verify_native_literal_spans_bundle','verify_native_literal_spans')
        text=text.replace('verify_storage','verify_literal_spans').replace('storage_tests','literal_span_tests')
        text=text.replace('affected_storage_cases','affected_literal_span_cases').replace('storage_cases','literal_span_cases')
        text=text.replace('87425','5184').replace('native-storage-','native-literal-spans-')
        text=text.replace('8e6ef3449e7a5a26d9d3fc7f268e380fbc7694fe',ARCHIVE)
        if path.name=='build_bundle.py':
            text=once(text,"STAGE/'native_perf50/event_factory_bundle/checkpoint_receipt.json'","STAGE/'native_perf50/storage_bundle/checkpoint_receipt.json'")
        if path.name=='verify_storage_after_ab.py':text=text.replace("target/'storage.json'","target/'literal_spans.json'")
        ast.parse(text,filename=path.name)
        name=path.name.replace('verify_storage','verify_literal_spans')
        (WORK/name).write_text(text,encoding='utf8',newline='\n')
    for name in ('member_probe_cases.hpp','native_property_test_cases.hpp','bounded_followup_policy.json'):
        (WORK/name).write_bytes((OLD/name).read_bytes())
    plan=json.loads((OLD/'evaluation_plan.json').read_bytes())
    plan.update(baseline_dll_sha256=EXPECTED,verified_remote_backup=ARCHIVE,
        latest_remote_verified_production_backup=ARCHIVE,prior_trial_remote_archive=ARCHIVE,
        components=['12 private event argument spans with lazy materialization'],
        local_independent_cases=dict(literal_spans=5184),local_original_dll_cases=5184,
        full_source_changes=['gen/shards/shard_00.cpp','gen/shards/shard_02.cpp','gen/shards/shard_12.cpp','native_event_kernel.hpp','native_resolved_dispatch.hpp'],
        rejected_storage_not_inherited=True,old_source_not_retimed=True)
    plan['required'][0]='Retained regressions plus5184 actual-DLL literal event argument cases; exact707-source reproduction before freshPGO'
    (WORK/'evaluation_plan.json').write_text(json.dumps(plan,indent=2)+'\n',encoding='utf8')
    print('Prepared full20/new18PGO and unchanged fixed200 bounded24(+8)/2604/raw24 protocol')

if __name__=='__main__':main()
