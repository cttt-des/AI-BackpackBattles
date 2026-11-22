"""Apply only the frozen closed-input timer source checked against the actual baseline."""
import json
from prepare_native_closed_timer import BASE,WORK as PROBE,STAGE,EXPECTED,transform,sha
ACCEPTED=STAGE/'native_perf50/motion_indices_bundle'

def optimize(native):
    before=json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    assert before=={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    for name in ('correctness.json','known_sealed_tests.json','closed_mode_fixed200.json'):
        record=json.loads((PROBE/name).read_bytes())
        assert record['passed'] and record['dll_sha256']==sha(PROBE/'prototype.dll'),name
    assert json.loads((PROBE/'correctness.json').read_bytes())['open_runtime_cases']==2016
    assert json.loads((PROBE/'known_sealed_tests.json').read_bytes())['cases']==1056
    dependencies=json.loads((PROBE/'proof_dependencies.json').read_bytes())
    assert dependencies=={name:sha(STAGE/name) for name in dependencies}
    design=transform(native)
    frozen=json.loads((PROBE/'transform.json').read_bytes())
    assert design['source_sha256']==frozen['source_sha256'],'Train and release only the exact checked source'
    result=json.loads((ACCEPTED/'transform.json').read_bytes())
    for key in list(result):
        if 'layout' in key:del result[key]
    result.update(baseline_dll_sha256=EXPECTED,components=['targeted array mutation watchers','ordered nonempty timer owners','exact same-pass continuation','sealed packed-input observer specialization','foreign registration permanently unseals future battles'],
        modified_native_files=design['modified_files'],new_native_files=design['new_files'],independent_original_dll_cases=2016,
        sealed_known_only_cases=1056,sealed_registry_boundary_cases=4,
        source_shape='GdArr24->32,BattleCtx264->304; full20 rebuild; measured CoreItem1792',
        generated_object_header_text_unchanged=True,internal_layout_changed_full20_rebuild_required=True,
        ownership_revision=2,closed_world_proof=design['closed_world_proof'],proof_dependencies_sha256=sha(PROBE/'proof_dependencies.json'),
        helper_sha256=sha(STAGE/'native_targeted_timers.hpp'),all_arithmetic_rng_and_observable_callback_order_retained=True,
        prior_negative_targeted_timer_ab_preserved=True,no_whole_fight_gain_claim=True)
    return result
