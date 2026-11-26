"""Reproduce the exact semantically checked private-snapshot/truth combination."""
import json
from prepare_native_scalar_guards import WORK as PROBE,ACCEPTED,EXPECTED,ARCHIVE,sha,inventory,transform,verify_projection

def optimize(native):
    suite=json.loads((PROBE/'semantic_suite.json').read_bytes());assert suite['passed']
    assert suite['dll_sha256']==sha(PROBE/'prototype.dll')
    assert inventory(native)==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    component=transform(native);frozen=json.loads((PROBE/'transform.json').read_bytes())
    assert inventory(native)==frozen['source_sha256'];verify_projection(native)
    result=json.loads((ACCEPTED/'transform.json').read_bytes())
    result.update(baseline_dll_sha256=EXPECTED,source_sha256=frozen['source_sha256'],source_projection=verify_projection(native),
        components=['retained private integer and identity snapshots','inline scalar truth with original complex fallback'],
        modified_files=frozen['modified_files'],new_files=frozen['new_files'],object_layout_changes=False,
        battle_context_watch_layout_changes=False,layout_changes_require_full_rebuild=False,
        full20_build_chosen_for_fresh18_pgo=True,floating_options_unchanged=True,scalar_component=component,
        semantic_suite_sha256=sha(PROBE/'semantic_suite.json'),current_display_and_control_components_retained=True,
        candidate_cpp_source_files=708,empirical20_coverage_not_a_release_gate=True,no_individual_component_speed_claim=True)
    return result
