"""Reproduce only the source covered by the literal span DLL differential."""
import json
from prepare_native_literal_spans import STAGE,WORK as PROBE,ACCEPTED,EXPECTED,sha,transform

def optimize(native):
    proof=json.loads((PROBE/'correctness.json').read_bytes())
    built=json.loads((PROBE/'build.json').read_bytes())
    allocation=json.loads((PROBE/'allocation_probe.json').read_bytes())
    assert proof['passed'] and proof['cases']==5184 and built['passed']
    assert proof['dll_sha256']==built['dll_sha256']==sha(PROBE/'prototype.dll')
    assert proof['fixture_sha256']==sha(STAGE/'test_native_literal_spans.cpp')
    assert proof['canonical_no_materialization_checks']>0
    assert allocation['passed'] and allocation['arrays_avoided']==73353 and allocation['arrays_materialized']==40624
    for name,digest in proof['raw_cases_sha256'].items():assert sha(PROBE/name)==digest
    before={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    design=transform(native)
    after={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    assert after==json.loads((PROBE/'transform.json').read_bytes())['source_sha256']
    result=json.loads((ACCEPTED/'transform.json').read_bytes())
    result.update(baseline_dll_sha256=EXPECTED,components=[design['component']],source_sha256=after,
        modified_files=sorted(n for n in before if before[n]!=after[n]),new_files=[],
        object_layout_changes=False,battle_context_watch_layout_changes=False,layout_changes_require_full_rebuild=False,
        full20_build_chosen_for_fresh18_pgo=True,literal_span_component=design,
        semantic_receipt_sha256=sha(PROBE/'correctness.json'),allocation_probe_sha256=sha(PROBE/'allocation_probe.json'),no_individual_component_speed_claim=True)
    assert len(result['modified_files'])==5
    return result
