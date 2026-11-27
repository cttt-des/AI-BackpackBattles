"""Freeze the repaired deployment; remove only a proven redundant type guard."""
import hashlib,io,json,shutil,subprocess
from pathlib import Path
from prepare_ordering_correctness import STAGE,REPO,BASE,sha,inventory
from install_ordering_correctness import boundary
ACCEPTED=STAGE/'native_perf50/ordering_correctness_bundle'
WORK=STAGE/'native_perf50/frame_guard_reuse_bundle'
EXPECTED='02fda77681361a6ddc721aa9ea75950126fa0f82df787b83ac3ca97144192d52'
ARCHIVE='768d2c48e2ce12b9859318b0ac7713cd44100c6d'
HEADER='native_inline_dispatch.hpp'
OLD='''    const auto receiver = gd::native_inline_self_type(item->rt_ctx_,item,&META_Gd__gd_core_items__Gems__Gem)'''
NEW='''    // Entry proved this exact cached row. Until this point only direct
    // fields, scalar conversions and counter functions were evaluated:
    // no user callback or row/context write can invalidate that proof.
    // Preserve the original successful type-query diagnostic at its old point.
    if (collect) native_type_constructor_hit(0);
    const auto receiver = (row->type_mask & uint64_t{1}) != 0'''
def save(name,value):(WORK/name).write_text(json.dumps(value,indent=2,ensure_ascii=False)+'\n',encoding='utf8')
def verify_projection(source):
    actual=inventory(source);before=json.loads((ACCEPTED/'source_before_build.json').read_bytes())
    assert set(actual)==set(before) and len(actual)==715
    for name,h in before.items():
        if name!=HEADER:assert actual[name]==h,name
    text=(source/HEADER).read_text('utf8');assert text.count(NEW)==1
    assert text.replace(NEW,OLD)==(ACCEPTED/'bundle_src'/HEADER).read_text('utf8')
    frozen=WORK/'source_before_build.json'
    if frozen.exists():assert actual==json.loads(frozen.read_bytes())
    return dict(passed=True,exact_inverse_matches_repaired_production=True,exact_inverse_matches_retained_source=True,all674_headers_and_layouts_unchanged=True,all_sorting_and_three_live_listener_loops_retained=True,no_change_to_floating_RNG_or_callback_order=True)
def main():
    boundary();assert not WORK.exists();assert sha(BASE/'libgdcore.dll')==sha(REPO/'dist/native_1_1_10/libgdcore.dll')==EXPECTED
    receipt=json.loads((ACCEPTED/'checkpoint_receipt.json').read_bytes());assert receipt['remote_verified_commit']==ARCHIVE and receipt['remote_upload_verified']
    assert subprocess.check_output(['git','ls-remote','--exit-code','https://github.com/cttt-des/AI-BackpackBattles.git','refs/heads/codex/native-perf50-verified'],cwd=REPO,text=True,timeout=40).split()[0]==ARCHIVE
    before=json.loads((ACCEPTED/'source_before_build.json').read_bytes());assert inventory(BASE)==before
    WORK.mkdir();source=WORK/'bundle_src';shutil.copytree(ACCEPTED/'bundle_src',source)
    p=source/HEADER;text=p.read_text('utf8');assert text.count(OLD)==1;text=text.replace(OLD,NEW);p.write_text(text,encoding='utf8',newline='\n')
    save('source_before_build.json',inventory(source));proof=verify_projection(source)
    save('transform.json',dict(baseline_dll_sha256=EXPECTED,parent_verified_commit=ARCHIVE,source_sha256=inventory(source),modified_files=[HEADER],projection=proof,established_proof_scope='same invocation, before the first Gem.character callback only',must_revalidate_each_next_item_and_after_each_callback=True,unchanged_successful_type_query_counter=True))
    save('evaluation_plan.json',dict(baseline=EXPECTED,maximum_compiler_workers=2,compiler_priority='below_normal',normal_prototype_not_for_speed_claim=True,formal_full20_instrumentation_fresh18_PGO=True,original_floating_flags_unchanged=True,AB=dict(initial_pairs=24,only_if_mixed_evidence_one_extra_group=8,maximum_pairs=32,all_samples_and_outliers_retained=True,require_both_CPU_and_wall_paired_median_reduction_positive=True),correctness=dict(current_repaired_original_Godot_oracles=True,all_retained_directed_cases=True,current_production_weapon_all136128_exact=True,full_original_events=2604,all_original_fixed200_inputs_results_counters=True),load20=dict(empirical_formula=True,extrapolation_allowed=True,observed_range_or_idle_window_not_gate=True),deploy_only_after_positive_AB_and_complete_original_event_verification=True,no_new_branches=True,no_old200_FPS_target=True))
    save('user_boundary_before.json',json.loads((ACCEPTED/'user_boundary_before.json').read_bytes()))
    print('Single-header candidate prepared on repaired02fd baseline; all715 files inverse-checked',flush=True)
if __name__=='__main__':main()
