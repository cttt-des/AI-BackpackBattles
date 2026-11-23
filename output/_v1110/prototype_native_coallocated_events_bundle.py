"""Reproduce the independently checked factory/frame bundle without changing production."""
import json
from prepare_native_coallocated_events import STAGE,WORK as PROBE,ACCEPTED,EXPECTED,sha,transform

def optimize(native):
    local=json.loads((PROBE/'correctness.json').read_bytes());built=json.loads((PROBE/'build.json').read_bytes())
    assert local['passed'] and local['cases']==4161 and built['passed']
    assert local['dll_sha256']==built['dll_sha256']==sha(PROBE/'prototype.dll')
    for name,digest in local['fixtures_sha256'].items():assert sha(STAGE/name)==digest
    for name,digest in local['raw_cases_sha256'].items():assert sha(PROBE/name)==digest
    for name,record in local['components'].items():assert sha(PROBE/(name+'_correctness.json'))==record['report_sha256']
    before={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    component=transform(native)
    after={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    assert after==json.loads((PROBE/'transform.json').read_bytes())['source_sha256']
    result=json.loads((ACCEPTED/'transform.json').read_bytes())
    result.update(baseline_dll_sha256=EXPECTED,components=[component['component']],source_sha256=after,
        modified_files=sorted(n for n in before if before[n]!=after[n]),new_files=[],
        object_layout_changes=False,battle_context_watch_layout_changes=False,private_cooldown_cache_adds_grid_pointer=False,
        layout_changes_require_full_rebuild=False,full20_build_chosen_for_fresh18_pgo=True,
        coallocated_event_component=component,semantic_receipt_sha256=sha(PROBE/'correctness.json'),
        no_individual_component_speed_claim=True)
    assert result['modified_files']==['engine_wrapper.cpp','gen/shards/shard_11.cpp','native_inline_dispatch.hpp']
    return result
