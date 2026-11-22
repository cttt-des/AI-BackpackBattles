#pragma once
#include "preflight_damage_records.hpp"
gd::GdVal reference_takeDamage(Gd__gd_core__CoreCharacter& character,const gd::GdVal* _args,int _argc) {
    gd::BattleCtx& gd_ctx = *character.rt_ctx_;
    if (gd_ctx.native_event_kernel) {
        ++gd_ctx.native_event_counts[1];
    gd::GdVal lv_damageSource = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_damageRes = native_event_new<Gd__gd_core__CoreDamageResult>(gd_ctx, nullptr, 0);
    lv_damageSource = ([&]() { gd::GdVal _ca[] = {lv_damageSource}; return native_event_call<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::fn_fromDamageSource>(gd_ctx, native_event_new<Gd__gd_core__CoreDamageSource>(gd_ctx, nullptr, 0), SYM_GEN_fromDamageSource_1549, _ca, 1); })();
    native_event_set<Gd__gd_core__CoreDamageSource>(gd_ctx, lv_damageSource, SYM_GEN__rng_1548, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, character.f_ctx, SYM_GEN_rng_1406));
    native_event_set<Gd__gd_core__CoreDamageResult>(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24, lv_damageSource);
    (void)native_event_call<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::fn_reset>(gd_ctx, lv_damageRes, SYM_GEN_reset_1025, nullptr, 0);
    if (gd::gd_truth(character.f_isDead)) {
        return lv_damageRes;
    }
    gd::GdVal lv_item = gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_inline_is_type(gd_ctx, native_event_get<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::f_origin>(gd_ctx, lv_damageSource, SYM_GEN_origin_1546), &META_Gd__gd_core__CoreItem)))) {
        lv_item = native_event_get<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::f_origin>(gd_ctx, lv_damageSource, SYM_GEN_origin_1546);
    }
    gd::GdVal lv_attackEffectCount = gd::GdVal::from_int(1LL);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item, gd::GdVal::null())))) {
        lv_attackEffectCount = gd::gd_add(gd_ctx, lv_attackEffectCount, gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_rollDoubleAttackEffect_187, nullptr, 0));
    }
    if (gd::gd_truth(native_event_call<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::fn_canMiss>(gd_ctx, lv_damageSource, SYM_GEN_canMiss_1557, nullptr, 0))) {
        gd::GdVal lv_accuracy = native_event_get<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::f_accuracy>(gd_ctx, lv_damageSource, SYM_GEN_accuracy_1545);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(&battle_string_literals[8]))))) {
            (void)gd::GdVal::null();
        }
        native_event_set<Gd__gd_core__CoreDamageResult>(gd_ctx, lv_damageRes, SYM_GEN_hit_1520, ([&]() { gd::GdVal _ca[] = {lv_accuracy}; return native_event_call<Gd__gd_core__CoreRng__INNER__BalancedRng, &Gd__gd_core__CoreRng__INNER__BalancedRng::fn_rollPercent>(gd_ctx, character.f_accuracyRng, SYM_GEN_rollPercent_1760, _ca, 1); })());
        if (gd::gd_truth((gd::gd_truth(native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_hit>(gd_ctx, lv_damageRes, SYM_GEN_hit_1520)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(character.f_dodgeStacks, gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_int(1LL))}; return character.fn_changeDodgeStacks(_ca, 1); })();
            native_event_set<Gd__gd_core__CoreDamageResult>(gd_ctx, lv_damageRes, SYM_GEN_hit_1520, gd::GdVal::from_bool(false));
        }
    }
    else {
        native_event_set<Gd__gd_core__CoreDamageResult>(gd_ctx, lv_damageRes, SYM_GEN_hit_1520, gd::GdVal::from_bool(true));
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(50.0)), gd::GdVal::from_float(50.0)}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_randf_range>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, character.f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(70.0)), gd::GdVal::from_float(70.0)}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_randf_range>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, character.f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(0.3665191429188092)), gd::gd_neg(gd::GdVal::from_float(0.05235987755982988))}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_randf_range>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, character.f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(native_event_call<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::fn_isAttack>(gd_ctx, lv_damageSource, SYM_GEN_isAttack_1560, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_damageRes}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_preDealDamage_early_222, _ca, 1); })();
        if (gd::gd_truth(gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_hasPreDealDamageEarlyEffect_62))) {
            {
                gd::GdVal _t569 = gd::gd_iter_seq(gd_ctx.arena, lv_attackEffectCount);
                gd::GdArr* _t570 = (_t569.kind == gd::GdVal::Kind::Arr) ? _t569.arr : nullptr;
                uint32_t _len__t571 = _t570 ? _t570->len : 0u;
                for (uint32_t _t571 = 0; _t571 < _len__t571; ++_t571) {
                    gd::GdVal lv_i = _t570->data[_t571];
                    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[18]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN__behavior_call_504, _ca, 2); })();
                }
            }
        }
    }
    if (gd::gd_truth(native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_hit>(gd_ctx, lv_damageRes, SYM_GEN_hit_1520))) {
        native_event_set<Gd__gd_core__CoreDamageResult>(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_add(gd_ctx, native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_damage>(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), native_event_call<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::fn_randDamage>(gd_ctx, lv_damageSource, SYM_GEN_randDamage_159, nullptr, 0)));
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Fatigue_2781)}; return native_event_call<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::fn_hasType>(gd_ctx, lv_damageSource, SYM_GEN_hasType_79, _ca, 1); })())) {
            native_event_set<Gd__gd_core__CoreDamageResult>(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_add(gd_ctx, native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_damage>(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), character.f_bonusFatigueDamage));
        }
        if (gd::gd_truth(native_event_call<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::fn_canCrit>(gd_ctx, lv_damageSource, SYM_GEN_canCrit_1559, nullptr, 0))) {
            gd::GdVal lv_critical = gd::GdVal::from_bool(false);
            gd::GdVal lv_critChancePercent = native_event_call<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::fn_getCritChancePercent>(gd_ctx, lv_damageSource, SYM_GEN_getCritChancePercent_178, nullptr, 0);
            if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_critChancePercent, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_critChancePercent}; return native_event_call<Gd__gd_core__CoreRng__INNER__BalancedRng, &Gd__gd_core__CoreRng__INNER__BalancedRng::fn_rollPercent>(gd_ctx, character.f_critRng, SYM_GEN_rollPercent_1760, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
                lv_critical = gd::GdVal::from_bool(true);
            }
            else if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getCritTokens_182, nullptr, 0), gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
                (void)gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_useCritToken_184, nullptr, 0);
                lv_critical = gd::GdVal::from_bool(true);
            }
            else if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(native_event_call<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::fn_getCritTokens>(gd_ctx, character.f_opponent, SYM_GEN_getCritTokens_182, nullptr, 0), gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(native_event_call<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::fn_isAttackOrEffect>(gd_ctx, lv_damageSource, SYM_GEN_isAttackOrEffect_1562, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
                (void)native_event_call<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::fn_useCritToken>(gd_ctx, character.f_opponent, SYM_GEN_useCritToken_184, nullptr, 0);
                lv_critical = gd::GdVal::from_bool(true);
            }
            if (gd::gd_truth(lv_critical)) {
                if (gd::gd_truth(character.fn_critResisted(nullptr, 0))) {
                    (void)character.fn_randBuffLabelPos(nullptr, 0);
                    (void)character.fn_randBuffLabelDir(nullptr, 0);
                    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(11LL), gd::GdVal::null()}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, character.f_ctx, SYM_GEN_hooks_1409), SYM_GEN_spawnBuffLabel_1636, _ca, 2); })();
                }
                else {
                    (void)native_event_call<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::fn_makeCritical>(gd_ctx, lv_damageRes, SYM_GEN_makeCritical_1525, nullptr, 0);
                }
            }
        }
        gd::GdVal lv_activeDmgResi = gd::gd_clamp(gd::gd_div(gd_ctx, character.f_damageResistance, gd::GdVal::from_int(100LL)), gd::gd_neg(gd::GdVal::from_int(10LL)), gd::GdVal::from_int(1LL));
        native_event_set<Gd__gd_core__CoreDamageResult>(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_round(gd::gd_mul(native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_damage>(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), gd::gd_sub(gd::GdVal::from_float(1.0), lv_activeDmgResi))));
        if (gd::gd_truth(native_event_call<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::fn_isAttack>(gd_ctx, native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_damageSource>(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_isAttack_1560, nullptr, 0))) {
            native_event_set<Gd__gd_core__CoreDamageResult>(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_sub(native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_damage>(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), character.f_damageReduction));
        }
        if (gd::gd_truth(character.f_invulnerable)) {
            native_event_set<Gd__gd_core__CoreDamageResult>(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::GdVal::from_int(0LL));
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj((&character)), gd::GdVal::from_str(&battle_string_literals[19]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return native_event_call<Gd__gd_core__CoreEventBus, &Gd__gd_core__CoreEventBus::fn_emitSignal>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_bus>(gd_ctx, character.f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
        native_event_set<Gd__gd_core__CoreDamageResult>(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_sub(native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_damage>(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_damageReduction>(gd_ctx, lv_damageRes, SYM_GEN_damageReduction_1063)));
        native_event_set<Gd__gd_core__CoreDamageResult>(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_max(gd::GdVal::from_int(0LL), native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_damage>(gd_ctx, lv_damageRes, SYM_GEN_damage_1518)));
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(native_event_call<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::fn_isAttack>(gd_ctx, lv_damageSource, SYM_GEN_isAttack_1560, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_damageRes}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_preDealDamage_late_223, _ca, 1); })();
            if (gd::gd_truth(gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_hasPreDealDamageLateEffect_63))) {
                {
                    gd::GdVal _t572 = gd::gd_iter_seq(gd_ctx.arena, lv_attackEffectCount);
                    gd::GdArr* _t573 = (_t572.kind == gd::GdVal::Kind::Arr) ? _t572.arr : nullptr;
                    uint32_t _len__t574 = _t573 ? _t573->len : 0u;
                    for (uint32_t _t574 = 0; _t574 < _len__t574; ++_t574) {
                        gd::GdVal lv_i = _t573->data[_t574];
                        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[20]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN__behavior_call_504, _ca, 2); })();
                    }
                }
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj((&character)), gd::GdVal::from_str(&battle_string_literals[21]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return native_event_call<Gd__gd_core__CoreEventBus, &Gd__gd_core__CoreEventBus::fn_emitSignal>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_bus>(gd_ctx, character.f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
        native_event_set<Gd__gd_core__CoreDamageResult>(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1519, native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_damage>(gd_ctx, lv_damageRes, SYM_GEN_damage_1518));
        if (gd::gd_truth(native_event_call<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::fn_canBeBlocked>(gd_ctx, lv_damageSource, SYM_GEN_canBeBlocked_1558, nullptr, 0))) {
            gd::GdVal lv_curBlock = character.fn_getBlock(nullptr, 0);
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_damage>(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), lv_curBlock)))) {
                native_event_set<Gd__gd_core__CoreDamageResult>(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1519, gd::gd_sub(native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_healthDamage>(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1519), lv_curBlock));
                (void)([&]() { gd::GdVal _ca[] = {lv_curBlock}; return character.fn_loseBlock(_ca, 1); })();
            }
            else {
                (void)([&]() { gd::GdVal _ca[] = {native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_damage>(gd_ctx, lv_damageRes, SYM_GEN_damage_1518)}; return character.fn_loseBlock(_ca, 1); })();
                native_event_set<Gd__gd_core__CoreDamageResult>(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1519, gd::GdVal::from_int(0LL));
            }
        }
        character.f_curHealth = gd::gd_coerce_float(gd::gd_sub(character.f_curHealth, native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_healthDamage>(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1519)));
        if (gd::gd_truth(native_event_call<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::fn_wasCriticalHit>(gd_ctx, lv_damageRes, SYM_GEN_wasCriticalHit_1524, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL), native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_damage>(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), lv_item}; return character.fn_spawnLabel_native(_ca, 3); })();
        }
        else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Fatigue_2781)}; return native_event_call<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::fn_hasType>(gd_ctx, lv_damageSource, SYM_GEN_hasType_79, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(99LL), native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_damage>(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), lv_item}; return character.fn_spawnLabel_native(_ca, 3); })();
        }
        else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Poison_2664)}; return native_event_call<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::fn_hasType>(gd_ctx, lv_damageSource, SYM_GEN_hasType_79, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(108LL), native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_damage>(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), lv_item}; return character.fn_spawnLabel_native(_ca, 3); })();
        }
        else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Spikes_2662)}; return native_event_call<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::fn_hasType>(gd_ctx, lv_damageSource, SYM_GEN_hasType_79, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(104LL), native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_damage>(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), lv_item}; return character.fn_spawnLabel_native(_ca, 3); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_damage>(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), lv_item}; return character.fn_spawnLabel_native(_ca, 3); })();
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(character.f_damage_anim_current, gd::GdVal::from_str(&battle_string_literals[22]))))) {
            if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_healthDamage>(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1519), gd::GdVal::from_int(0LL))))) {
                character.f_damage_anim_current = gd::GdVal::from_str(&battle_string_literals[23]);
            }
            else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Fatigue_2781)}; return native_event_call<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::fn_hasType>(gd_ctx, lv_damageSource, SYM_GEN_hasType_79, _ca, 1); })())) {
                character.f_damage_anim_current = gd::GdVal::from_str(&battle_string_literals[24]);
            }
            else {
                character.f_damage_anim_current = gd::GdVal::from_str(&battle_string_literals[25]);
            }
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_randf_range>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, character.f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj((&character)), (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Fatigue_2781)}; return native_event_call<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::fn_hasType>(gd_ctx, lv_damageSource, SYM_GEN_hasType_79, _ca, 1); })()) ? (gd::GdVal::from_str(&battle_string_literals[24])) : (gd::GdVal::from_str(&battle_string_literals[25])))}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, character.f_ctx, SYM_GEN_hooks_1409), SYM_GEN_damageAnimation_1639, _ca, 2); })();
        }
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(3LL), gd::GdVal::from_int(0LL), lv_item}; return character.fn_spawnLabel_native(_ca, 3); })();
    }
    gd::GdVal lv_event = gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item, gd::GdVal::null())))) {
        lv_event = ([&]() { gd::GdVal _ca[] = {lv_damageRes, lv_triggerEvent}; return native_event_call<Gd__gd_core__CoreCombatLog, &Gd__gd_core__CoreCombatLog::fn_createEvent_Attack>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_combat_log>(gd_ctx, character.f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_Attack_1358, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[26]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return native_event_call<Gd__gd_core__CoreEventBus, &Gd__gd_core__CoreEventBus::fn_emitSignal>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_bus>(gd_ctx, character.f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_damageRes}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_dealtDamage_224, _ca, 1); })();
    }
    else {
        lv_event = ([&]() { gd::GdVal _ca[] = {lv_damageRes, native_event_get<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::f_playerId>(gd_ctx, character.f_opponent, SYM_GEN_playerId_1046), lv_triggerEvent}; return native_event_call<Gd__gd_core__CoreCombatLog, &Gd__gd_core__CoreCombatLog::fn_createEvent_Damage>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_combat_log>(gd_ctx, character.f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_Damage_1359, _ca, 3); })();
    }
    native_event_set<Gd__gd_core__CoreDamageResult>(gd_ctx, lv_damageRes, SYM_GEN_event_1517, lv_event);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj((&character)), gd::GdVal::from_str(&battle_string_literals[27]), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return native_event_call<Gd__gd_core__CoreEventBus, &Gd__gd_core__CoreEventBus::fn_emitEvent>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_bus>(gd_ctx, character.f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitEvent_1593, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj((&character)), gd::GdVal::from_str(&battle_string_literals[28]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_healthDamage>(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1519), native_event_get<Gd__gd_core__CoreDamageResult, &Gd__gd_core__CoreDamageResult::f_event>(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}))}; return native_event_call<Gd__gd_core__CoreEventBus, &Gd__gd_core__CoreEventBus::fn_emitSignal>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_bus>(gd_ctx, character.f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj((&character))}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, character.f_ctx, SYM_GEN_hooks_1409), SYM_GEN_onHealthChangedUI_1641, _ca, 1); })();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(native_event_call<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::fn_isAttack>(gd_ctx, lv_damageSource, SYM_GEN_isAttack_1560, nullptr, 0))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_hasDealtDamageEffect_64))) : gd::GdVal::from_bool(false)))) {
        {
            gd::GdVal _t575 = gd::gd_iter_seq(gd_ctx.arena, lv_attackEffectCount);
            gd::GdArr* _t576 = (_t575.kind == gd::GdVal::Kind::Arr) ? _t575.arr : nullptr;
            uint32_t _len__t577 = _t576 ? _t576->len : 0u;
            for (uint32_t _t577 = 0; _t577 < _len__t577; ++_t577) {
                gd::GdVal lv_i = _t576->data[_t577];
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[29]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN__behavior_call_504, _ca, 2); })();
            }
        }
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(character.f_curHealth, gd::GdVal::from_int(0LL))))) {
        (void)character.fn_death(nullptr, 0);
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_damageRes}; return character.fn_applySpikes(_ca, 1); })();
    return lv_damageRes;
    return gd::GdVal::null();
    }
    gd::GdVal lv_damageSource = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_damageRes = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageResult), gd::SYM_new, nullptr, 0);
    lv_damageSource = ([&]() { gd::GdVal _ca[] = {lv_damageSource}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_fromDamageSource_1549, _ca, 1); })();
    gd::set_prop(gd_ctx, lv_damageSource, SYM_GEN__rng_1548, gd::native_inline_get_prop(gd_ctx, character.f_ctx, SYM_GEN_rng_1406));
    gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24, lv_damageSource);
    (void)gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_reset_1025, nullptr, 0);
    if (gd::gd_truth(character.f_isDead)) {
        return lv_damageRes;
    }
    gd::GdVal lv_item = gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_inline_is_type(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_damageSource, SYM_GEN_origin_1546), &META_Gd__gd_core__CoreItem)))) {
        lv_item = gd::native_inline_get_prop(gd_ctx, lv_damageSource, SYM_GEN_origin_1546);
    }
    gd::GdVal lv_attackEffectCount = gd::GdVal::from_int(1LL);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item, gd::GdVal::null())))) {
        lv_attackEffectCount = gd::gd_add(gd_ctx, lv_attackEffectCount, gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_rollDoubleAttackEffect_187, nullptr, 0));
    }
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageSource, SYM_GEN_canMiss_1557, nullptr, 0))) {
        gd::GdVal lv_accuracy = gd::native_inline_get_prop(gd_ctx, lv_damageSource, SYM_GEN_accuracy_1545);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(&battle_string_literals[8]))))) {
            (void)gd::GdVal::null();
        }
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_hit_1520, ([&]() { gd::GdVal _ca[] = {lv_accuracy}; return gd::native_inline_call(gd_ctx, character.f_accuracyRng, SYM_GEN_rollPercent_1760, _ca, 1); })());
        if (gd::gd_truth((gd::gd_truth(gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_hit_1520)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(character.f_dodgeStacks, gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_int(1LL))}; return character.fn_changeDodgeStacks(_ca, 1); })();
            gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_hit_1520, gd::GdVal::from_bool(false));
        }
    }
    else {
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_hit_1520, gd::GdVal::from_bool(true));
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(50.0)), gd::GdVal::from_float(50.0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, character.f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(70.0)), gd::GdVal::from_float(70.0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, character.f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(0.3665191429188092)), gd::gd_neg(gd::GdVal::from_float(0.05235987755982988))}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, character.f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageSource, SYM_GEN_isAttack_1560, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_damageRes}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_preDealDamage_early_222, _ca, 1); })();
        if (gd::gd_truth(gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_hasPreDealDamageEarlyEffect_62))) {
            {
                gd::GdVal _t569 = gd::gd_iter_seq(gd_ctx.arena, lv_attackEffectCount);
                gd::GdArr* _t570 = (_t569.kind == gd::GdVal::Kind::Arr) ? _t569.arr : nullptr;
                uint32_t _len__t571 = _t570 ? _t570->len : 0u;
                for (uint32_t _t571 = 0; _t571 < _len__t571; ++_t571) {
                    gd::GdVal lv_i = _t570->data[_t571];
                    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[18]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN__behavior_call_504, _ca, 2); })();
                }
            }
        }
    }
    if (gd::gd_truth(gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_hit_1520))) {
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_add(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), gd::native_inline_call(gd_ctx, lv_damageSource, SYM_GEN_randDamage_159, nullptr, 0)));
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Fatigue_2781)}; return gd::native_inline_call(gd_ctx, lv_damageSource, SYM_GEN_hasType_79, _ca, 1); })())) {
            gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_add(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), character.f_bonusFatigueDamage));
        }
        if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageSource, SYM_GEN_canCrit_1559, nullptr, 0))) {
            gd::GdVal lv_critical = gd::GdVal::from_bool(false);
            gd::GdVal lv_critChancePercent = gd::native_inline_call(gd_ctx, lv_damageSource, SYM_GEN_getCritChancePercent_178, nullptr, 0);
            if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_critChancePercent, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_critChancePercent}; return gd::native_inline_call(gd_ctx, character.f_critRng, SYM_GEN_rollPercent_1760, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
                lv_critical = gd::GdVal::from_bool(true);
            }
            else if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getCritTokens_182, nullptr, 0), gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
                (void)gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_useCritToken_184, nullptr, 0);
                lv_critical = gd::GdVal::from_bool(true);
            }
            else if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_call(gd_ctx, character.f_opponent, SYM_GEN_getCritTokens_182, nullptr, 0), gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageSource, SYM_GEN_isAttackOrEffect_1562, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
                (void)gd::native_inline_call(gd_ctx, character.f_opponent, SYM_GEN_useCritToken_184, nullptr, 0);
                lv_critical = gd::GdVal::from_bool(true);
            }
            if (gd::gd_truth(lv_critical)) {
                if (gd::gd_truth(character.fn_critResisted(nullptr, 0))) {
                    (void)character.fn_randBuffLabelPos(nullptr, 0);
                    (void)character.fn_randBuffLabelDir(nullptr, 0);
                    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(11LL), gd::GdVal::null()}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, character.f_ctx, SYM_GEN_hooks_1409), SYM_GEN_spawnBuffLabel_1636, _ca, 2); })();
                }
                else {
                    (void)gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_makeCritical_1525, nullptr, 0);
                }
            }
        }
        gd::GdVal lv_activeDmgResi = gd::gd_clamp(gd::gd_div(gd_ctx, character.f_damageResistance, gd::GdVal::from_int(100LL)), gd::gd_neg(gd::GdVal::from_int(10LL)), gd::GdVal::from_int(1LL));
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_round(gd::gd_mul(gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), gd::gd_sub(gd::GdVal::from_float(1.0), lv_activeDmgResi))));
        if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_isAttack_1560, nullptr, 0))) {
            gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_sub(gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), character.f_damageReduction));
        }
        if (gd::gd_truth(character.f_invulnerable)) {
            gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::GdVal::from_int(0LL));
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj((&character)), gd::GdVal::from_str(&battle_string_literals[19]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, character.f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_sub(gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageReduction_1063)));
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_max(gd::GdVal::from_int(0LL), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518)));
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageSource, SYM_GEN_isAttack_1560, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_damageRes}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_preDealDamage_late_223, _ca, 1); })();
            if (gd::gd_truth(gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_hasPreDealDamageLateEffect_63))) {
                {
                    gd::GdVal _t572 = gd::gd_iter_seq(gd_ctx.arena, lv_attackEffectCount);
                    gd::GdArr* _t573 = (_t572.kind == gd::GdVal::Kind::Arr) ? _t572.arr : nullptr;
                    uint32_t _len__t574 = _t573 ? _t573->len : 0u;
                    for (uint32_t _t574 = 0; _t574 < _len__t574; ++_t574) {
                        gd::GdVal lv_i = _t573->data[_t574];
                        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[20]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN__behavior_call_504, _ca, 2); })();
                    }
                }
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj((&character)), gd::GdVal::from_str(&battle_string_literals[21]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, character.f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1519, gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518));
        if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageSource, SYM_GEN_canBeBlocked_1558, nullptr, 0))) {
            gd::GdVal lv_curBlock = character.fn_getBlock(nullptr, 0);
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), lv_curBlock)))) {
                gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1519, gd::gd_sub(gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1519), lv_curBlock));
                (void)([&]() { gd::GdVal _ca[] = {lv_curBlock}; return character.fn_loseBlock(_ca, 1); })();
            }
            else {
                (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518)}; return character.fn_loseBlock(_ca, 1); })();
                gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1519, gd::GdVal::from_int(0LL));
            }
        }
        character.f_curHealth = gd::gd_coerce_float(gd::gd_sub(character.f_curHealth, gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1519)));
        if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_wasCriticalHit_1524, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), lv_item}; return character.fn_spawnLabel_native(_ca, 3); })();
        }
        else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Fatigue_2781)}; return gd::native_inline_call(gd_ctx, lv_damageSource, SYM_GEN_hasType_79, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(99LL), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), lv_item}; return character.fn_spawnLabel_native(_ca, 3); })();
        }
        else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Poison_2664)}; return gd::native_inline_call(gd_ctx, lv_damageSource, SYM_GEN_hasType_79, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(108LL), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), lv_item}; return character.fn_spawnLabel_native(_ca, 3); })();
        }
        else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Spikes_2662)}; return gd::native_inline_call(gd_ctx, lv_damageSource, SYM_GEN_hasType_79, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(104LL), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), lv_item}; return character.fn_spawnLabel_native(_ca, 3); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), lv_item}; return character.fn_spawnLabel_native(_ca, 3); })();
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(character.f_damage_anim_current, gd::GdVal::from_str(&battle_string_literals[22]))))) {
            if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1519), gd::GdVal::from_int(0LL))))) {
                character.f_damage_anim_current = gd::GdVal::from_str(&battle_string_literals[23]);
            }
            else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Fatigue_2781)}; return gd::native_inline_call(gd_ctx, lv_damageSource, SYM_GEN_hasType_79, _ca, 1); })())) {
                character.f_damage_anim_current = gd::GdVal::from_str(&battle_string_literals[24]);
            }
            else {
                character.f_damage_anim_current = gd::GdVal::from_str(&battle_string_literals[25]);
            }
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, character.f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj((&character)), (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Fatigue_2781)}; return gd::native_inline_call(gd_ctx, lv_damageSource, SYM_GEN_hasType_79, _ca, 1); })()) ? (gd::GdVal::from_str(&battle_string_literals[24])) : (gd::GdVal::from_str(&battle_string_literals[25])))}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, character.f_ctx, SYM_GEN_hooks_1409), SYM_GEN_damageAnimation_1639, _ca, 2); })();
        }
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(3LL), gd::GdVal::from_int(0LL), lv_item}; return character.fn_spawnLabel_native(_ca, 3); })();
    }
    gd::GdVal lv_event = gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item, gd::GdVal::null())))) {
        lv_event = ([&]() { gd::GdVal _ca[] = {lv_damageRes, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, character.f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_Attack_1358, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[26]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, character.f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_damageRes}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_dealtDamage_224, _ca, 1); })();
    }
    else {
        lv_event = ([&]() { gd::GdVal _ca[] = {lv_damageRes, gd::native_inline_get_prop(gd_ctx, character.f_opponent, SYM_GEN_playerId_1046), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, character.f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_Damage_1359, _ca, 3); })();
    }
    gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517, lv_event);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj((&character)), gd::GdVal::from_str(&battle_string_literals[27]), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, character.f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitEvent_1593, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj((&character)), gd::GdVal::from_str(&battle_string_literals[28]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1519), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}))}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, character.f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj((&character))}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, character.f_ctx, SYM_GEN_hooks_1409), SYM_GEN_onHealthChangedUI_1641, _ca, 1); })();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageSource, SYM_GEN_isAttack_1560, nullptr, 0))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_hasDealtDamageEffect_64))) : gd::GdVal::from_bool(false)))) {
        {
            gd::GdVal _t575 = gd::gd_iter_seq(gd_ctx.arena, lv_attackEffectCount);
            gd::GdArr* _t576 = (_t575.kind == gd::GdVal::Kind::Arr) ? _t575.arr : nullptr;
            uint32_t _len__t577 = _t576 ? _t576->len : 0u;
            for (uint32_t _t577 = 0; _t577 < _len__t577; ++_t577) {
                gd::GdVal lv_i = _t576->data[_t577];
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[29]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN__behavior_call_504, _ca, 2); })();
            }
        }
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(character.f_curHealth, gd::GdVal::from_int(0LL))))) {
        (void)character.fn_death(nullptr, 0);
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_damageRes}; return character.fn_applySpikes(_ca, 1); })();
    return lv_damageRes;
    return gd::GdVal::null();
}
