"""Reproduce exactly the source checked against the current independent DLL."""
import json
from prepare_native_private_snapshots import WORK as PROBE,ACCEPTED,EXPECTED,sha,transform

def optimize(native):
    proof=json.loads((PROBE/'correctness.json').read_bytes());built=json.loads((PROBE/'build.json').read_bytes())
    assert proof['passed'] and proof['cases']==234880 and built['passed']
    assert proof['dll_sha256']==built['dll_sha256']==sha(PROBE/'prototype.dll')
    for n,h in proof['fixture_sha256'].items():assert sha(PROBE.parents[1]/n)==h
    for n,h in proof['raw_cases_sha256'].items():assert sha(PROBE/n)==h
    before={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    assert before==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    component=transform(native)
    after={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    assert after==json.loads((PROBE/'transform.json').read_bytes())['source_sha256']
    result=json.loads((ACCEPTED/'transform.json').read_bytes())
    result.update(baseline_dll_sha256=EXPECTED,source_sha256=after,
        components=['bounded private integer views','pre-callback identity bytes with deferred string allocation'],
        modified_files=sorted(n for n in before if before[n]!=after[n]),new_files=['native_private_snapshots.hpp'],
        object_layout_changes=False,battle_context_watch_layout_changes=False,layout_changes_require_full_rebuild=False,
        full20_build_chosen_for_fresh18_pgo=True,private_snapshots_component=component,
        semantic_receipt_sha256=sha(PROBE/'correctness.json'),no_individual_component_speed_claim=True)
    return result
