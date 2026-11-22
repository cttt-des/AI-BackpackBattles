"""Apply the frozen, independently checked targeted timer representation."""
import json
from prepare_native_targeted_timers import BASE,WORK as PROBE,STAGE,EXPECTED,transform,sha
ACCEPTED=STAGE/'native_perf50/motion_indices_bundle'

def optimize(native):
    before=json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    assert before=={p.relative_to(native).as_posix():sha(p) for p in native.rglob('*') if p.is_file()}
    for name,n in [('differential_expanded_revision2.json',1760),('safety_differential_revision2.json',192),('ownership_differential_revision2.json',64)]:
        record=json.loads((PROBE/name).read_bytes());assert record['passed'] and record['cases']==n
    screen=json.loads((PROBE/'local_screen.json').read_bytes());assert screen['passed']
    for name,digest in screen['dependency_sha256'].items():
        p=STAGE/name if name.endswith('.cpp') else native/name if name=='native_targeted_timers.hpp' else PROBE/name
        # The initial matched screen predates the additional cold ownership
        # checks. Preserve it as hypothesis only; formal A/B measures revision2.
        if name=='native_targeted_timers.hpp':p=PROBE/'native_targeted_timers_revision1.hpp'
        assert sha(p)==digest,name
    local=json.loads((PROBE/'local_correctness_revision2.json').read_bytes())
    assert local['passed'] and local['cases']==1760 and local['all_actual_old_dll_hashes_equal']
    assert local['dependency_sha256']['native_targeted_timers.hpp']==sha(STAGE/'native_targeted_timers.hpp')
    design=transform(native)
    frozen=json.loads((PROBE/'transform.json').read_bytes())
    assert design['source_sha256']==frozen['source_sha256'],'Full PGO must use the exact tested source'
    result=json.loads((ACCEPTED/'transform.json').read_bytes())
    for key in list(result):
        if 'layout' in key:del result[key]
    result.update(baseline_dll_sha256=EXPECTED,components=['targeted array mutation watchers','ordered sparse nonempty timer owners','exact same-pass continuation','unknown boundary fallback'],
        modified_native_files=design['modified_files'],new_native_files=design['new_files'],independent_original_dll_cases=2016,
        source_shape='GdArr24->32, BattleCtx264->304; CoreItem1792 in measured probe; measure all retained layouts again',
        generated_object_header_text_unchanged=True,internal_layout_changed_full20_rebuild_required=True,
        ownership_revision=2,
        helper_sha256=sha(STAGE/'native_targeted_timers.hpp'),all_arithmetic_rng_and_observable_callback_order_retained=True,
        retained_initial_local_screen_scope='Revision1 before extra cold ownership checks; not a measurement of the final candidate',
        revision1_cross_context_counterexample_retained=True,no_whole_fight_gain_claim=True)
    return result
