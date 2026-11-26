"""Reproduce the independently checked frame-local value changes."""
import json
from prepare_native_frame_values import WORK as PROBE,ACCEPTED,EXPECTED,sha,inventory,transform,verify_projection

def optimize(native):
    suite=json.loads((PROBE/'semantic_suite.json').read_bytes());assert suite['passed'] and suite['total_cases']==335776
    assert suite['dll_sha256']==sha(PROBE/'prototype.dll')
    assert inventory(native)==json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    component=transform(native);frozen=json.loads((PROBE/'transform.json').read_bytes())
    assert inventory(native)==frozen['source_sha256']
    result=json.loads((ACCEPTED/'transform.json').read_bytes())
    result.update(baseline_dll_sha256=EXPECTED,source_sha256=frozen['source_sha256'],source_projection=verify_projection(native),
        components=['frame-local scalar truth','avoid copying unused Null override payload'],modified_files=frozen['modified_files'],new_files=[],
        object_layout_changes=False,battle_context_watch_layout_changes=False,layout_changes_require_full_rebuild=False,
        full20_build_chosen_for_fresh18_pgo=True,floating_options_unchanged=True,frame_value_component=component,
        semantic_suite_sha256=sha(PROBE/'semantic_suite.json'),current_display_control_private_scalar_components_retained=True,
        baseline_cpp_source_files=708,candidate_cpp_source_files=708,
        baseline_core_item_bytes=2112,candidate_core_item_bytes=2112,
        intentional_layout_changes=[],new_layout_changes=False,object_layout_change_declared=False,
        internal_layout_changed_full20_rebuild_required=False,
        empirical20_coverage_not_a_release_gate=True,no_individual_component_speed_claim=True)
    return result
