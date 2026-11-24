"""Reproduce the exact two-file source validated by the independent DLLs."""
import json
from prepare_native_object_routes import WORK as PROBE,STAGE,ACCEPTED,EXPECTED,sha,transform

def optimize(native):
    proof=json.loads((PROBE/'correctness.json').read_bytes());built=json.loads((PROBE/'build.json').read_bytes())
    assert proof['passed'] and built['passed'] and proof['cases']==320256 and proof['active_route_assertions']==10240
    assert proof['dll_sha256']==built['dll_sha256']==sha(PROBE/'prototype.dll')
    assert proof['fixture_sha256']==sha(STAGE/'test_native_object_routes.cpp')
    assert proof['symbols_header_sha256']==sha(PROBE/'object_route_test_symbols.hpp')
    assert built['route_counts']==dict(instance_methods=901392,static_context_f32=88491)
    for n,h in proof['raw_cases_sha256'].items():assert sha(PROBE/n)==h
    before={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    assert before==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    component=transform(native)
    after={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    frozen=json.loads((PROBE/'transform.json').read_bytes());assert after==frozen['source_sha256']
    result=json.loads((ACCEPTED/'transform.json').read_bytes())
    result.update(baseline_dll_sha256=EXPECTED,components=[component['component']],source_sha256=after,
        modified_files=sorted(n for n in before if before[n]!=after[n]),new_files=[],object_layout_changes=False,
        battle_context_watch_layout_changes=False,layout_changes_require_full_rebuild=False,
        full20_build_chosen_for_fresh18_pgo=True,object_routes_component=component,
        semantic_receipt_sha256=sha(PROBE/'correctness.json'),source_proof_sha256=sha(PROBE/'object_routes_source_proof.json'),
        call_probe_sha256=sha(PROBE/'object_route_probe.json'),scope_analysis_sha256=sha(PROBE/'route_scope_analysis.json'),
        prior65_callback_and_literal_routes_unchanged=True,no_individual_component_speed_claim=True)
    assert result['modified_files']==['gd_rt.cpp','native_resolved_dispatch.hpp']
    return result
