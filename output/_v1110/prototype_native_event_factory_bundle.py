"""Reproduce the exact event factory validated through the semantic DLL."""
import json
from prepare_native_event_factory import STAGE, WORK as PROBE, ACCEPTED, EXPECTED, sha, transform

def optimize(native):
    local=json.loads((PROBE/'correctness.json').read_bytes())
    built=json.loads((PROBE/'build.json').read_bytes())
    assert local['passed'] and local['cases']==5120 and built['passed']
    assert local['dll_sha256']==built['dll_sha256']==sha(PROBE/'prototype.dll')
    assert local['fixture_sha256']==sha(STAGE/'test_native_event_factory.cpp')
    assert local['shared_fixture_sha256']==sha(STAGE/'test_native_event_capacity.cpp')
    for n,h in local['raw_cases_sha256'].items():assert sha(PROBE/(n+'_factory_cases.json'))==h
    before={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    component=transform(native)
    after={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    assert after==json.loads((PROBE/'transform.json').read_bytes())['source_sha256']
    result=json.loads((ACCEPTED/'transform.json').read_bytes())
    result.update(baseline_dll_sha256=EXPECTED,components=[component['component']],source_sha256=after,
        modified_files=sorted(n for n in before if before[n]!=after[n]),new_files=[],
        object_layout_changes=False,battle_context_watch_layout_changes=False,
        layout_changes_require_full_rebuild=False,full20_build_chosen_for_fresh18_pgo=True,
        event_factory_component=component,semantic_receipt_sha256=sha(PROBE/'correctness.json'),
        no_individual_component_speed_claim=True)
    assert result['modified_files']==['gen/shards/shard_05.cpp']
    return result
