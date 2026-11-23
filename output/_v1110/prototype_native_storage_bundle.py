"""Reproduce the exact source covered by the independent storage checks."""
import json
from prepare_native_storage_bundle import STAGE,WORK as PROBE,ACCEPTED,EXPECTED,sha,transform

def optimize(native):
    proof=json.loads((PROBE/'correctness.json').read_bytes())
    built=json.loads((PROBE/'build.json').read_bytes())
    allocation=json.loads((PROBE/'allocation_probe.json').read_bytes())
    assert proof['passed'] and proof['cases']==87425 and built['passed'] and allocation['passed']
    assert proof['dll_sha256']==built['dll_sha256']==sha(PROBE/'prototype.dll')
    assert proof['shared_fixture_sha256']==sha(STAGE/'test_native_event_capacity.cpp')
    assert proof['constructor_inventory_sha256']==sha(ACCEPTED/'native_type_constructor_test_cases.hpp')
    for name,row in proof['components'].items():
        assert row['fixture_sha256']==sha(STAGE/('test_native_storage_'+name+'.cpp'))
    for name,digest in proof['raw_cases_sha256'].items():assert sha(PROBE/name)==digest
    before={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    design=transform(native)
    after={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    assert after==json.loads((PROBE/'transform.json').read_bytes())['source_sha256']
    result=json.loads((ACCEPTED/'transform.json').read_bytes())
    result.update(baseline_dll_sha256=EXPECTED,components=design['components'],source_sha256=after,
        modified_files=sorted(n for n in before if before[n]!=after[n]),new_files=[],
        object_layout_changes=False,battle_context_watch_layout_changes=False,layout_changes_require_full_rebuild=False,
        full20_build_chosen_for_fresh18_pgo=True,storage_components=design,
        semantic_receipt_sha256=sha(PROBE/'correctness.json'),allocation_probe_sha256=sha(PROBE/'allocation_probe.json'),
        no_individual_component_speed_claim=True)
    assert result['modified_files']==['gd_rt.cpp','gen/shards/shard_00.cpp']
    return result
