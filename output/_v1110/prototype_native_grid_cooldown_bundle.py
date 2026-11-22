"""Freeze the fully checked two-region bundle for one whole-fight comparison."""
import json
from prepare_native_integer_grid import transform as grid_transform
from prepare_native_grid_cooldown import STAGE,WORK as PROBE,EXPECTED,sha,transform_cached_cooldowns

def optimize(native):
    local=json.loads((PROBE/'correctness.json').read_bytes());assert local['passed']
    assert local['cooldown_cases']==1856 and local['dictionary_cases']==1792 and local['spatial_cases']==23520
    for name,digest in local['report_sha256'].items():assert sha(PROBE/name)==digest
    before={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    grid=grid_transform(native);cooldown=transform_cached_cooldowns(native)
    after={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    assert after==json.loads((PROBE/'transform.json').read_bytes())['source_sha256']
    result=json.loads((STAGE/'native_perf50/active_cooldown_bundle/transform.json').read_bytes())
    result.update(baseline_dll_sha256=EXPECTED,components=['integer filledCells bucket format','cooldown cache-hit guard hoisting','redundant indexed Bool check removal'],
        source_sha256=after,modified_files=sorted(n for n in before if before[n]!=after[n]),new_files=sorted(set(after)-set(before)),
        grid_component=grid,cooldown_component=cooldown,object_layout_changes=False,battle_context_watch_layout_changes=False,
        layout_changes_require_full_rebuild=False,full20_build_chosen_for_fresh18_pgo=True,
        private_cooldown_cache_adds_grid_pointer=True,existing_header_inline_bodies_unchanged_except_cooldown_consumer=True,
        no_individual_component_speed_claim=True)
    return result
