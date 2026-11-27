"""Exact-source manifest for the guarded quiet-core segment experiment."""
import json,shutil
from prepare_frame_guard_reuse import REPO,STAGE,BASE,sha,inventory
from install_ordering_correctness import boundary
WORK=STAGE/'native_perf50/quiet_interval_bundle'
NAME=WORK.name
ACCEPTED=STAGE/'native_perf50/frame_guard_reuse_bundle'
EXPECTED='cea3c1c81a9294e05f0aac3b609ee4e474aa7019a1bf766ad12c22d876fe4b52'
ARCHIVE='a6bbfddbc6d6bf4fd1d56accddefb2f28467f3dd'
def save(n,v):(WORK/n).write_text(json.dumps(v,indent=2,ensure_ascii=False)+'\n',encoding='utf8')

def verify_projection(source):
    actual=inventory(source);before=json.loads((WORK/'baseline_source.json').read_bytes());changes=json.loads((WORK/'source_changes.json').read_bytes())
    assert len(actual)==len(before)==715 and set(actual)==set(before)
    assert set(changes)=={'engine_wrapper.cpp'}
    for name,digest in before.items():
        if name not in changes:assert actual[name]==digest,name
        else:
            text=(source/name).read_text('utf8')
            for old,new in reversed(changes[name]):assert text.count(new)==1,(name,new[:100]);text=text.replace(new,old)
            assert text==(ACCEPTED/'bundle_src'/name).read_text('utf8')
    if (WORK/'source_before_build.json').exists():assert actual==json.loads((WORK/'source_before_build.json').read_bytes())
    return dict(passed=True,exact_inverse_matches_retained_source=True,all674_headers_and_layouts_unchanged=True,all_sorting_and_three_live_listener_loops_retained=True,original_frame_function_and_all_original_game_methods_unchanged=True,guarded_alternative_engine_loop=True)

def main():
    boundary();assert sha(BASE/'libgdcore.dll')==EXPECTED
    diagnostic=json.loads((WORK/'diagnostic_counts.json').read_bytes());assert diagnostic['passed']
    assert not (WORK/'bundle_src').exists()
    source=WORK/'bundle_src';shutil.copytree(ACCEPTED/'bundle_src',source)
    shutil.copyfile(ACCEPTED/'bundle.dll',WORK/'baseline.dll')
    shutil.copyfile(ACCEPTED/'release_audit.json',WORK/'fixed200_reference.json')
    shutil.copyfile(ACCEPTED/'user_boundary_before.json',WORK/'user_boundary_before.json')
    save('baseline_source.json',inventory(ACCEPTED/'bundle_src'))
    calibration=STAGE/'native_perf50/measurement_structure_bundle'
    for name in ('calibration_plan.json','aa_analysis.json'):shutil.copyfile(calibration/name,WORK/name)
    plan=json.loads((calibration/'formal_ab_protocol.json').read_bytes());plan['seeds']=[2026112707,2026112708]
    save('formal_ab_protocol.json',plan)
    path=source/'engine_wrapper.cpp';text=path.read_text('utf8');operations=[]
    def replace(old,new):
        nonlocal text
        assert text.count(old)==1,old[:100];text=text.replace(old,new);operations.append([old,new])
    replace('#include <typeinfo>','#include <cfenv>\n#include <xmmintrin.h>\n#include "native_active_cooldowns.hpp"\n#include "gen/hdrs/Gd__gd_core__CoreTimer.hpp"\n#include "gen/hdrs/Gd__gd_core__CoreContext__INNER__NativeFlicker.hpp"\n#include <typeinfo>')
    marker='static void run_one_internal('
    fragment=(STAGE/'quiet_core_kernel.cpp').read_text('utf8')
    replace(marker,fragment+'\n'+marker)
    original='''        combat_obj->fn_physicsTick(tick_args, host ? 2 : 1);
        if (host && gd::gd_truth(combat_obj->f_activated)) {
            apply_host_draws(*host, *ctx_obj, combat_obj->f_combat_time.as_float(), 1);
        }
        ticks += 1;'''
    replacement='''        const auto advanced = static_cast<int32_t>(battle.event_count) <= ev_gate
            ? gd_diag_quiet_core_advance(combat_obj,ctx_obj,unsigned(max_ticks-ticks),host) : 0u;
        if(advanced) ticks += static_cast<int32_t>(advanced);
        else {
            combat_obj->fn_physicsTick(tick_args, host ? 2 : 1);
            if (host && gd::gd_truth(combat_obj->f_activated)) {
                apply_host_draws(*host, *ctx_obj, combat_obj->f_combat_time.as_float(), 1);
            }
            ticks += 1;
        }'''
    replace(original,replacement);path.write_text(text,encoding='utf8',newline='\n')
    save('source_changes.json',{'engine_wrapper.cpp':operations});save('source_before_build.json',inventory(source))
    save('round.json',dict(name=NAME,baseline_bundle=ACCEPTED.name,baseline_dll_sha256=EXPECTED,parent_remote_commit=ARCHIVE))
    save('transform.json',dict(baseline_dll_sha256=EXPECTED,source_sha256=inventory(source),modified_files=['engine_wrapper.cpp'],projection=verify_projection(source)))
    save('architecture_selection.json',dict(selected='guarded numerical core segments between original callback boundaries; original RNG/idle/visual phases still execute each frame',diagnostic_counts=diagnostic['counts'],diagnostic_sha256=sha(WORK/'diagnostic_counts.json'),frozen_AB_protocol_sha256=sha(WORK/'formal_ab_protocol.json'),no_aggregate_delta_formula=True,no_same_source_retiming=True,full2604_with_optimization_exercised_required=True,all_retained_tests_required=True,deploy_only_after_positive_calibrated_AB=True))

if __name__=='__main__':main()
