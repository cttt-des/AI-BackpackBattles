"""Reproduce the exact three-file control candidate proved by the semantic DLL."""
import json
from prepare_native_control_word import STAGE,WORK as PROBE,BASE,ACCEPTED,BACKUP,EXPECTED,ARCHIVE,sha,transform,verify_projection

def optimize(native):
    proof=json.loads((PROBE/'correctness.json').read_bytes());built=json.loads((PROBE/'build.json').read_bytes())
    assert proof['passed'] and proof['cases']==44608 and proof['actual_word_path_enabled']
    assert proof['portable_namespace_isolated_and_no_dll_loaded']
    assert built['passed'] and proof['dll_sha256']==built['dll_sha256']==sha(PROBE/'prototype.dll')
    assert proof['fixture_sha256']==sha(STAGE/'test_native_control_word.cpp')
    receipt=json.loads((BACKUP/'checkpoint_receipt.json').read_bytes())
    assert receipt['remote_upload_verified'] and receipt['remote_verified_commit']==ARCHIVE
    before={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    assert before==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    component=transform(native);projection=verify_projection(native)
    after={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    frozen=json.loads((PROBE/'transform.json').read_bytes());assert after==frozen['source_sha256']
    result=json.loads((ACCEPTED/'transform.json').read_bytes())
    result.update(baseline_dll_sha256=EXPECTED,components=[component['component']],source_sha256=after,
        modified_files=frozen['modified_files'],new_files=[],control_word_component=component,
        semantic_receipt_sha256=sha(PROBE/'correctness.json'),source_projection=projection,
        object_layout_changes=False,battle_context_watch_layout_changes=False,
        private_active_cache_layout_changed=False,layout_changes_require_full_rebuild=False,
        full20_build_chosen_for_fresh18_pgo=True,floating_options_unchanged=True,
        prior_prefetch_pta_snapshots_not_included=True,no_speed_claim=True)
    return result
