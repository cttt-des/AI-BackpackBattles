"""Reproduce the isolated address-only candidate from the verified deployment."""
import json
from prepare_native_active_prefetch import WORK as PROBE,STAGE,BASE,ACCEPTED,BACKUP,EXPECTED,ARCHIVE,sha,transform

def optimize(native):
    proof=json.loads((PROBE/'correctness.json').read_bytes())
    built=json.loads((PROBE/'build.json').read_bytes())
    assert proof['passed'] and proof['cases']==12864 and built['passed']
    assert proof['dll_sha256']==built['dll_sha256']==sha(PROBE/'prototype.dll')
    assert proof['fixture_sha256']==sha(STAGE/'test_native_active_prefetch_addresses.cpp')
    checkpoint=json.loads((BACKUP/'checkpoint_receipt.json').read_bytes())
    assert checkpoint['remote_upload_verified'] and checkpoint['remote_verified_commit']==ARCHIVE
    before={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    assert before==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    component=transform(native)
    after={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    frozen=json.loads((PROBE/'transform.json').read_bytes())
    assert after==frozen['source_sha256']
    result=json.loads((ACCEPTED/'transform.json').read_bytes())
    result.update(baseline_dll_sha256=EXPECTED,components=[component['component']],source_sha256=after,
        modified_files=frozen['modified_files'],new_files=[],active_prefetch_component=component,
        semantic_receipt_sha256=sha(PROBE/'correctness.json'),object_layout_changes=False,
        battle_context_watch_layout_changes=False,private_active_cache_layout_changed=True,
        layout_changes_require_full_rebuild=True,full20_build_chosen_for_fresh18_pgo=True,
        floating_options_unchanged=True,private_snapshots_trial_not_included=True,
        compiler_pta_trial_not_included=True,no_speed_claim=True)
    return result
