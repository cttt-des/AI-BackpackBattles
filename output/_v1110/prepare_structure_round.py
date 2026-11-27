"""Data-oriented layout prototype; preserve every computation and object size."""
import json,re,shutil
from pathlib import Path
from prepare_frame_guard_reuse import REPO,STAGE,BASE,sha,inventory
from calibrate_structure_measurement import WORK,ACCEPTED,EXPECTED,PARENT as ARCHIVE
NAME=WORK.name
HOT={
'CoreItem':['__cooldown_active','__cooldown_blocked_epoch','ctx','character_','statDisplayOverrides','speedScale','placed','triggerTime','iterationCooldown','descriptor','damageSource','staminaFactor','bonusMinDam','bonusMaxDam','bonusDamageFactor','critChancePercent','doubleActivationChance','doubleAttackEffectChance','gems','ownerType','lastActivationTime','activationsThisFrame','lastTriggerTime','triggersThisFrame','itemMetrics'],
'CoreCharacter':['stunnedDuration','staminaRegen','curStamina','maxStamina','temporaryMaxStamina','buffs','inventory','playerId','ctx','curHealth','maxHealth','temporaryMaxHealth','invulnerable','damageResistance','damageReduction','dodgeStacks','critResistance','critResistStacks','critTokens','empowerDamage','__physics_timer_mask','__tick_timer_active','__tick_timer_left','__invul_active','__invul_left','__rage_active','__rage_left','__autoRage_active','__autoRage_left'],
'CoreBuff':['__timer_active','__timer_left','__timer_member_epoch','current','character','ctx','type','temporaryStacks','nextTemporaryTimeout','permanentStacks','__timer_first_pass','__timer_wait'],
'CoreContext':['timer_pass_epoch','in_physics_timer_pass','in_item_physics_pass','show_cooldown_progress','native_frame_rng','frame_counter','time','combat_time','fight_ended','_deferred','_idle_frame_calls','_timed','_motion_queue','bus','rng','hooks','combat_log','player','opponent','deferred_flush_enabled','_critical_shake_delta','_critical_shake_active','_critical_shake_frame','_critical_shake_after_idle','_particle_pending_draws','_particle_before_physics','_particle_draws','particle_draw_frame']}
def save(name,value):(WORK/name).write_text(json.dumps(value,indent=2,ensure_ascii=False)+'\n',encoding='utf8')
def verify_projection(source):
    actual=inventory(source);before=json.loads((WORK/'baseline_source.json').read_bytes());changes=json.loads((WORK/'source_changes.json').read_bytes())
    assert len(actual)==len(before)==715 and set(actual)==set(before)
    for name,h in before.items():
        if name not in changes:assert actual[name]==h,name
        else:
            text=(source/name).read_text('utf8');original=(ACCEPTED/'bundle_src'/name).read_text('utf8')
            old,new=changes[name][0];assert text==new and original==old
            pattern=r'(?m)^    gd::GdVal (f_\w+);$'
            assert sorted(re.findall(pattern,old))==sorted(re.findall(pattern,new))
            assert re.sub(pattern,'    gd::GdVal DECLARATION_SLOT;',old)==re.sub(pattern,'    gd::GdVal DECLARATION_SLOT;',new)
    if (WORK/'source_before_build.json').exists():assert actual==json.loads((WORK/'source_before_build.json').read_bytes())
    return dict(passed=True,exact_inverse_matches_retained_source=True,only_permuted_same_type_field_declarations=True,
      all_function_bodies_and_arithmetic_and_callbacks_unchanged=True,all_nonfield_storage_and_alignas64_anchor_slots_retained=True,
      all_sorting_and_three_live_listener_loops_retained=True,no_change_to_floating_RNG_or_callback_order=True,
      changed_generated_headers=sorted(changes),unchanged_generated_headers=670,layout_size_and_alignment_proof='layout_projection.json')
def main():
    assert (WORK/'aa_timing_complete.json').exists() and (WORK/'diagnostic_counts.json').exists()
    source=WORK/'bundle_src'
    if source.exists():assert inventory(source)==inventory(ACCEPTED/'bundle_src') and not (WORK/'source_changes.json').exists()
    else:shutil.copytree(ACCEPTED/'bundle_src',source)
    changes={};field_plan={}
    for cls,priority in HOT.items():
        name=f'gen/hdrs/Gd__gd_core__{cls}.hpp';path=source/name;old=path.read_text('utf8');pattern=r'(?m)^    gd::GdVal (f_\w+);$'
        fields=re.findall(pattern,old);ordered=['f_'+f.removeprefix('_') if f.startswith('__') else 'f_'+f for f in priority];assert len(set(ordered))==len(ordered) and set(ordered)<=set(fields),(cls,set(ordered)-set(fields))
        ordered += [f for f in fields if f not in ordered];it=iter(ordered)
        new=re.sub(pattern,lambda m:'    gd::GdVal '+next(it)+';',old);assert new!=old
        path.write_text(new,encoding='utf8',newline='\n');changes[name]=[[old,new]];field_plan[cls]=dict(priority_fields=ordered[:len(priority)],original_order=fields,candidate_order=ordered)
    save('source_changes.json',changes);save('source_before_build.json',inventory(source));save('layout_field_plan.json',field_plan)
    save('round.json',dict(name=NAME,baseline_bundle=ACCEPTED.name,baseline_dll_sha256=EXPECTED,parent_remote_commit=ARCHIVE))
    save('transform.json',dict(baseline_dll_sha256=EXPECTED,source_sha256=inventory(source),modified_files=sorted(changes),projection=verify_projection(source)))
    save('architecture_selection.json',dict(selected='hot-state layout schema across item/character/buff/context; preserve original execution',
      evidence=['3,633,579 scattered cooldown item accesses per fixed200','frame and trigger chains account for76.38% sampled cost','current CoreItem2112 bytes with hot fields distributed across distant lines','global memcpy15MB is not evidence that only copy instructions dominate'],
      scope='one structural representation prototype, no additional micro-fixes',
      comparison=['whole-frame skip has83.6% log-free bins but requires exact recurrence and full observer certificate; absence of logs is insufficient','full event-stream rewrite changes phase and callback model; larger semantic proof surface','GdVal16 needs lossless Vec2 indirection and all ABI boundaries; no evidence yet that tradeoff wins','lineup blueprint promising for repeated lineups; cold build still must execute ordered setup callbacks and RNG'],
      limits='layout change is an architecture prototype, not an algorithmic removal of all frame work; no promised gain or claim of cache misses measured',
      frozen_AB_protocol_sha256=sha(WORK/'formal_ab_protocol.json'),must_use_exactly_predeclared24_quads=True,no_same_source_retiming=True,
      complete2604_original_events_and_retained_directed_tests_required=True,deploy_only_after_credible_positive_gain=True,
      source_maintenance_recipe_and_two_full_regenerations_required=True,max_compiler_workers=2,below_normal_compilers=True,no_new_branches=True))
    print('Prepared four-class hot-state layout prototype; all method bodies unchanged',flush=True)
if __name__=='__main__':main()
