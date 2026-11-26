"""Reproduce the independently verified restoration on the current deployment."""
import json
from prepare_restored_private_snapshots import STAGE,WORK as PROBE,ACCEPTED,EXPECTED,ARCHIVE,sha,transform,verify_projection

def optimize(native):
    suite=json.loads((PROBE/'semantic_suite.json').read_bytes());assert suite['passed'] and suite['total_cases']==301376
    assert suite['dll_sha256']==sha(PROBE/'prototype.dll')
    before={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    assert before==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    component=transform(native);after={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    frozen=json.loads((PROBE/'transform.json').read_bytes());assert after==frozen['source_sha256']
    result=json.loads((ACCEPTED/'transform.json').read_bytes())
    result.update(baseline_dll_sha256=EXPECTED,source_sha256=after,source_projection=verify_projection(native),
        components=['restore bounded private integer views','restore pre-callback identity bytes with deferred allocation'],
        modified_files=frozen['modified_files'],new_files=['native_private_snapshots.hpp'],
        object_layout_changes=False,battle_context_watch_layout_changes=False,layout_changes_require_full_rebuild=False,
        full20_build_chosen_for_fresh18_pgo=True,floating_options_unchanged=True,
        private_snapshots_component=component,semantic_suite_sha256=sha(PROBE/'semantic_suite.json'),
        current_display_and_control_components_retained=True,baseline_core_item_bytes=2112,candidate_core_item_bytes=2112,
        candidate_cpp_source_files=708,empirical20_coverage_not_a_release_gate=True,no_individual_component_speed_claim=True)
    return result
