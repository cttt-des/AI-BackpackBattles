"""Reproduce the side-table source covered by actual-DLL differential evidence."""
import json
from prepare_native_callback_dispatch import STAGE,WORK as PROBE,COUNT,ACCEPTED,EXPECTED,sha,transform

def optimize(native):
    proof=json.loads((PROBE/'correctness.json').read_bytes())
    built=json.loads((PROBE/'build.json').read_bytes())
    arrays=json.loads((PROBE/'allocation_probe.json').read_bytes())
    objects=json.loads((PROBE/'object_callback_probe.json').read_bytes())
    assert proof['passed'] and proof['cases']==126192 and built['passed'] and arrays['passed'] and objects['passed']
    assert proof['dll_sha256']==built['dll_sha256']==sha(PROBE/'prototype.dll')
    assert proof['fixture_sha256']==sha(STAGE/'test_native_callback_dispatch.cpp')
    assert proof['symbols_header_sha256']==sha(PROBE/'callback_test_symbols.hpp')
    assert proof['fast_no_materialization_assertions']==3072
    assert built['extra_callback_coverage']==dict(generic_funcref=50121,private_literal=51219)
    assert arrays['literal_emissions']==113977 and arrays['arrays_avoided']==105257 and arrays['arrays_materialized']==8720
    assert objects['selected65_callback_calls']==268 and objects['remaining_object_virtual_calls']==1456961
    for name,digest in proof['raw_cases_sha256'].items():assert sha(PROBE/name)==digest
    before={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    design=transform(native)
    after={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    prototype=json.loads((PROBE/'transform.json').read_bytes())
    assert after==prototype['source_sha256']
    assert prototype['source_proof_sha256']==sha(PROBE/'callback_source_proof.json')
    result=json.loads((ACCEPTED/'transform.json').read_bytes())
    result.update(baseline_dll_sha256=EXPECTED,components=[design['component']],source_sha256=after,
        modified_files=sorted(name for name in before if before[name]!=after[name]),new_files=[],
        object_layout_changes=False,battle_context_watch_layout_changes=False,layout_changes_require_full_rebuild=False,
        full20_build_chosen_for_fresh18_pgo=True,callback_dispatch_component=design,
        semantic_receipt_sha256=sha(PROBE/'correctness.json'),source_proof_sha256=sha(PROBE/'callback_source_proof.json'),
        allocation_probe_sha256=sha(PROBE/'allocation_probe.json'),bound_probe_sha256=sha(COUNT/'bound_argument_probe.json'),
        object_scope_probe_sha256=sha(PROBE/'object_callback_probe.json'),generic_object_scope_deliberately_not_expanded=True,
        no_individual_component_speed_claim=True)
    assert result['modified_files']==['gd_rt.cpp','native_event_kernel.hpp','native_resolved_dispatch.hpp']
    return result
