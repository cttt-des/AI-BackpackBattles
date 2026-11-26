"""Reproduce the independently checked display-storage source exactly."""
import json
from prepare_native_display_storage import STAGE,BASE,WORK as PROBE,ACCEPTED,EXPECTED,ARCHIVE,sha,transform,verify_projection

def optimize(native):
    proof=json.loads((PROBE/'correctness.json').read_bytes())
    retained=json.loads((PROBE/'retained_control.json').read_bytes())
    assert proof['passed'] and proof['cases']==21888
    assert retained['passed'] and retained['cases']==44608
    assert proof['dll_sha256']==retained['dll_sha256']==sha(PROBE/'prototype.dll')
    assert sha(BASE/'libgdcore.dll')==EXPECTED
    frozen=json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    assert frozen=={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    transform(native);projection=verify_projection(native)
    after={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    saved=json.loads((PROBE/'transform.json').read_bytes());assert after==saved['source_sha256']
    result=json.loads((ACCEPTED/'transform.json').read_bytes())
    result.update(baseline_dll_sha256=EXPECTED,source_sha256=after,
        components=['first-use display array header and ten values embedded in arena-owned items'],
        modified_files=saved['modified_files'],new_files=[],source_projection=projection,
        object_layout_changes=True,layout_changes_require_full_rebuild=True,
        gdval_gdarr_context_watch_layout_changes=False,no_new_value_cache=True,
        all_observable_calls_counters_fp_rng_and_alias_mutations_preserved=True,
        semantic_receipt_sha256=sha(PROBE/'correctness.json'),retained_receipt_sha256=sha(PROBE/'retained_control.json'),
        candidate_core_item_bytes=proof['candidate_core_item_bytes'],baseline_core_item_bytes=1792,
        full20_build_chosen_for_fresh18_pgo=True,floating_options_unchanged=True,no_speed_claim=True)
    return result
