"""Freeze the independently checked packed-display view for formal whole-fight trials."""
import json
from pathlib import Path
from prepare_native_display_defaults import STAGE,WORK as PROBE,ACCEPTED,EXPECTED,sha,transform

def optimize(native):
    local=json.loads((PROBE/'correctness.json').read_bytes());built=json.loads((PROBE/'build.json').read_bytes())
    assert local['passed'] and local['cases']==2305 and built['passed']
    assert local['dll_sha256']==built['dll_sha256']==sha(PROBE/'prototype.dll')
    assert sha(STAGE/'test_native_display_defaults.cpp')==local['fixture_sha256']
    raw=Path(local['raw_cases_directory'])
    for name,digest in local['raw_cases_sha256'].items():assert sha(raw/name)==digest
    before={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    component=transform(native)
    after={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    assert after==json.loads((PROBE/'transform.json').read_bytes())['source_sha256']
    result=json.loads((ACCEPTED/'transform.json').read_bytes())
    result.update(baseline_dll_sha256=EXPECTED,components=[component['component']],source_sha256=after,
        modified_files=sorted(n for n in before if before[n]!=after[n]),new_files=sorted(set(after)-set(before)),
        object_layout_changes=False,battle_context_watch_layout_changes=False,private_cooldown_cache_adds_grid_pointer=False,
        layout_changes_require_full_rebuild=False,full20_build_chosen_for_fresh18_pgo=True,
        existing_header_inline_bodies_unchanged_except_cooldown_consumer=False,display_default_component=component,
        semantic_receipt_sha256=sha(PROBE/'correctness.json'),rejected_event_capacity_change_included=False,
        no_individual_component_speed_claim=False)
    return result
