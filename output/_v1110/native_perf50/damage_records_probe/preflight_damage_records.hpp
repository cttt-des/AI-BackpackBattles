#pragma once
#include "native_event_kernel.hpp"
#include "native_scalar_equal.hpp"
#include "native_array_index.hpp"
constexpr gd::GdStr battle_string_literals[] = {
    {"\n\n", 2u, 2274317941u},
    {"CARD_COUNT", 10u, 1490789295u},
    {"num", 3u, 242376115u},
    {"CARD_HINT", 9u, 4169059801u},
    {"character_vampirism_changed", 27u, 75150398u},
    {"onVampirismChanged", 18u, 3624660862u},
    {"character_spikes_changed", 24u, 3463900413u},
    {"onSpikesChanged", 15u, 3715123341u},
    {"", 0u, 2166136261u},
    {"attack", 6u, 1167440125u},
    {"win", 3u, 200788825u},
    {"lose", 4u, 3509868664u},
    {"unknown", 7u, 2608177081u},
    {"character_", 10u, 2085970269u},
    {"_changed", 8u, 3417166458u},
    {"Player", 6u, 477166624u},
    {"Opponent", 8u, 1032749700u},
    {"Character.gd:327", 16u, 3219899945u},
    {"onPreDealDamage_early", 21u, 1141032398u},
    {"pre_take_damage", 15u, 2330033632u},
    {"onPreDealDamage_late", 20u, 4290954099u},
    {"pre_take_damage_late", 20u, 571519801u},
    {"Poison", 6u, 3158204625u},
    {"Block", 5u, 3171368962u},
    {"Fatigue", 7u, 1556357630u},
    {"Hit", 3u, 1700614218u},
    {"dealt_damage_signal_placeholder", 31u, 1864214166u},
    {"character_attacked", 18u, 2439462988u},
    {"character_damaged", 17u, 745527748u},
    {"onDealtDamage", 13u, 1467360435u},
    {"character_healed", 16u, 2989261042u},
    {"character_overhealed", 20u, 177632284u},
    {"reincarnated", 12u, 2408540175u},
    {"temporary_max_health_changed", 28u, 310654751u},
    {"character_pre_use_stamina", 25u, 4061960724u},
    {"character_used_stamina", 22u, 4094391974u},
    {"character_stunned", 17u, 4164697708u},
    {"fatigue_damage_changed", 22u, 2103754981u},
    {"blinding_light_ended", 20u, 2616732264u},
    {"battle_rage_started", 19u, 3997014835u},
    {"battle_rage_ended", 17u, 4230921894u},
    {"class_changed", 13u, 1615855124u},
    {"health", 6u, 1805184399u},
    {"stamina", 7u, 3875003702u},
    {"randPitch", 9u, 1151803428u},
    {"character_invulnerable_start", 28u, 2327172069u},
    {"character_invulnerable_end", 26u, 3350240732u},
    {"recalculateMaxStamina", 21u, 508469027u},
    {"Stamina Sack", 12u, 3135812348u},
    {"_", 1u, 3658226030u},
    {"Stone", 5u, 1842662042u},
    {"name", 4u, 2369371622u},
    {"identifier", 10u, 681945150u},
    {"index", 5u, 151693739u},
    {"minDam", 6u, 3647452719u},
    {"maxDam", 6u, 592428749u},
    {"staminaCost", 11u, 692264327u},
    {"block", 5u, 3943480674u},
    {"cd", 2u, 1529452802u},
    {"extraCds", 8u, 295123783u},
    {"accuracy", 8u, 1889185700u},
    {"canActivate", 11u, 2277690352u},
    {"chance", 6u, 2459084481u},
    {"chance2", 7u, 2950484105u},
    {"shopChance", 10u, 1435148261u},
    {"types", 5u, 4292920474u},
    {"tags", 4u, 4095142816u},
    {"physics", 7u, 2267225250u},
    {"rarity", 6u, 1266615690u},
    {"price", 5u, 189023530u},
    {"classes", 7u, 1882039975u},
    {"randomUniquePool", 16u, 3614658971u},
    {"hasBattleRageEffect", 19u, 3074838841u},
    {"gatedItems", 10u, 4187939518u},
    {"startsSubclass", 14u, 2130492966u},
    {"gateItem", 8u, 1563718697u},
    {"gate_item", 9u, 968161264u},
    {"originatingRecipes", 18u, 3632248325u},
    {"originating_recipes", 19u, 1356245250u},
    {"animationScene", 14u, 1958236555u},
    {"flickerAni", 10u, 869505055u},
    {"flicker_animation", 17u, 599064606u},
    {"flickerMinDist", 14u, 3154533517u},
    {"flicker_min_dist", 16u, 1027794029u},
    {"flickerMaxDist", 14u, 766191159u},
    {"flicker_max_dist", 16u, 1768726851u},
    {"flickerMinSpeed", 15u, 3355891604u},
    {"flicker_min_speed", 17u, 1515266548u},
    {"flickerMaxSpeed", 15u, 2566538706u},
    {"flicker_max_speed", 17u, 3198618670u},
    {"connectorReadyRoll", 18u, 3610243000u},
    {"connector_ready_roll", 20u, 516633754u},
    {"gemRoll", 7u, 352763615u},
    {"gem_roll", 8u, 1358800554u},
    {"sceneDepth", 10u, 637688668u},
    {"scene_depth", 11u, 3992921433u},
    {"releaseState", 12u, 2486442979u},
    {"release_state", 13u, 725990852u},
    {"params", 6u, 559900755u},
    {"namedParams", 11u, 212769148u},
    {"named_params", 12u, 3034422257u},
    {"gainedStacks", 12u, 1306778278u},
    {"removedStacks", 13u, 140807226u},
    {"usedStacks", 10u, 3590608929u},
    {"onDebuffsChanged", 16u, 4096794781u},
    {"character_mana_changed", 22u, 798563205u},
    {"onManaChanged", 13u, 3105672029u},
    {"lifesteal", 9u, 1515578962u},
    {"dam", 3u, 4031722721u},
    {"mana", 4u, 3650585354u},
    {"potion_emptied", 14u, 70999789u},
    {"onPotionEmptied", 15u, 4255313949u},
    {"Bagtacular", 10u, 2131747329u},
    {"buffs", 5u, 2149256365u},
    {"heal", 4u, 979982427u},
    {"dur_unhealing", 13u, 3047247524u},
    {"UnhealingTimer", 14u, 2986033917u},
    {"buffEnded", 9u, 3457903416u},
    {"revealspeed", 11u, 3267256187u},
    {"empower", 7u, 2037162760u},
    {"attacked", 8u, 3381721668u},
    {"onAffectedAttacked", 18u, 2827661201u},
    {"lifesteal_scaling", 17u, 610492256u},
    {"PotionTriggerTimer", 18u, 999831227u},
    {"triggerNextPotion", 17u, 745728413u},
    {"delay", 5u, 1322381784u},
    {"regent", 6u, 4290639402u},
    {"vampirism", 9u, 773404377u},
    {"spikes", 6u, 439106706u},
    {"luck", 4u, 4145017712u},
    {"luckt", 5u, 4061892428u},
    {"regen", 5u, 16724762u},
    {"Exclusive/Chess/ChessPiece.gd:74", 32u, 2209030417u},
    {"HINT_Chess", 10u, 68829135u},
    {"White", 5u, 1827351814u},
    {"Corrupted Crystal", 17u, 1233848549u},
    {"debuffs", 7u, 504032524u},
    {"speed", 5u, 2072037248u},
    {"onBattleRageStarted", 19u, 3330696088u},
    {"onBattleRageEnded", 17u, 1252110145u},
    {"duration", 8u, 799079693u},
    {"dur", 3u, 3509645056u},
    {"dur_1", 5u, 1189330420u},
    {"BuffTimer", 9u, 194754125u},
    {"blind", 5u, 274826164u},
    {"activated", 9u, 2866667388u},
    {"onCardRevealed", 14u, 755762322u},
    {"pos", 3u, 1412654217u},
    {"Joker_COUNTER", 13u, 333425847u},
    {"pairs", 5u, 1637539686u},
    {"triplets", 8u, 3869841120u},
    {"quadruples", 10u, 3542246839u},
    {"\n", 1u, 252472541u},
    {"cards", 5u, 2180079684u},
    {"character_lucky_changed", 23u, 2259242176u},
    {"onLuckyChanged", 14u, 1760969932u},
    {"sales", 5u, 2258376375u},
    {"luckneeded", 10u, 1930291013u},
    {"manat", 5u, 126091098u},
    {"fatiguemana", 11u, 2121368953u},
    {"potion_triggered", 16u, 729283976u},
    {"onPotionTriggered", 17u, 2537318808u},
    {"heal_food", 9u, 2824253696u},
    {"heat", 4u, 577319571u},
    {"gold", 4u, 3966162835u},
    {"speed2", 6u, 498752822u},
    {"Goobling", 8u, 1161906606u},
    {"used_stamina", 12u, 2801525262u},
    {"onItemUsedStamina", 17u, 2944104951u},
    {"staminat", 8u, 3660664550u},
    {"onWeaponAttacked", 16u, 3445043441u},
    {"speedreduction", 14u, 1031897425u},
    {"dambonus", 8u, 2769252496u},
    {"slow", 4u, 1838498488u},
    {"poisont", 7u, 1955680031u},
    {"critdam", 7u, 4140065929u},
    {"onAttack", 8u, 3086142220u},
    {"Perfect Amethyst_DESCR", 22u, 2265897535u},
    {"@", 1u, 3305896031u},
    {",", 1u, 688690635u},
    {"GRD", 3u, 2769401224u},
    {"fd=", 3u, 4228204814u},
    {" cp=", 4u, 3282868099u},
    {" aff=", 5u, 2844077393u},
    {"n=", 2u, 271970020u},
    {"PoisonTimer", 11u, 1785938446u},
    {"poisonTimerTimeout", 18u, 792798457u},
};
gd::GdVal candidate_takeDamage(Gd__gd_core__CoreCharacter& character,const gd::GdVal* _args,int _argc) {
    gd::BattleCtx& gd_ctx = *character.rt_ctx_;
    if (gd_ctx.native_event_kernel) {
        ++gd_ctx.native_event_counts[1];
    gd::GdVal lv_damageSource = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_damageRes = native_event_new<Gd__gd_core__CoreDamageResult>(gd_ctx, nullptr, 0);
    auto* const native_damage_result=static_cast<Gd__gd_core__CoreDamageResult*>(lv_damageRes.obj);
    lv_damageSource = ([&]() { gd::GdVal _ca[] = {lv_damageSource}; return native_event_call<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::fn_fromDamageSource>(gd_ctx, native_event_new<Gd__gd_core__CoreDamageSource>(gd_ctx, nullptr, 0), SYM_GEN_fromDamageSource_1549, _ca, 1); })();
    auto* const native_damage_source=static_cast<Gd__gd_core__CoreDamageSource*>(lv_damageSource.obj);
    (native_damage_source->f__rng = native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, character.f_ctx, SYM_GEN_rng_1406));
    (native_damage_result->f_damageSource = lv_damageSource);
    (void)native_damage_result->fn_reset(nullptr, 0);
    if (gd::gd_truth(character.f_isDead)) {
        return lv_damageRes;
    }
    gd::GdVal lv_item = gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_inline_is_type(gd_ctx, (native_damage_source->f_origin), &META_Gd__gd_core__CoreItem)))) {
        lv_item = (native_damage_source->f_origin);
    }
    gd::GdVal lv_attackEffectCount = gd::GdVal::from_int(1LL);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item, gd::GdVal::null())))) {
        lv_attackEffectCount = gd::gd_add(gd_ctx, lv_attackEffectCount, gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_rollDoubleAttackEffect_187, nullptr, 0));
    }
    if (gd::gd_truth(native_damage_source->fn_canMiss(nullptr, 0))) {
        gd::GdVal lv_accuracy = (native_damage_source->f_accuracy);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(&battle_string_literals[8]))))) {
            (void)gd::GdVal::null();
        }
        (native_damage_result->f_hit = gd::gd_coerce_bool(([&]() { gd::GdVal _ca[] = {lv_accuracy}; return native_event_call<Gd__gd_core__CoreRng__INNER__BalancedRng, &Gd__gd_core__CoreRng__INNER__BalancedRng::fn_rollPercent>(gd_ctx, character.f_accuracyRng, SYM_GEN_rollPercent_1760, _ca, 1); })()));
        if (gd::gd_truth((gd::gd_truth((native_damage_result->f_hit)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(character.f_dodgeStacks, gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_int(1LL))}; return character.fn_changeDodgeStacks(_ca, 1); })();
            (native_damage_result->f_hit = gd::gd_coerce_bool(gd::GdVal::from_bool(false)));
        }
    }
    else {
        (native_damage_result->f_hit = gd::gd_coerce_bool(gd::GdVal::from_bool(true)));
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(50.0)), gd::GdVal::from_float(50.0)}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_randf_range>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, character.f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(70.0)), gd::GdVal::from_float(70.0)}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_randf_range>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, character.f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(0.3665191429188092)), gd::gd_neg(gd::GdVal::from_float(0.05235987755982988))}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_randf_range>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, character.f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(native_damage_source->fn_isAttack(nullptr, 0))) : gd::GdVal::from_bool(false)))) {
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
    if (gd::gd_truth((native_damage_result->f_hit))) {
        (native_damage_result->f_damage = gd::gd_coerce_int(gd::gd_add(gd_ctx, (native_damage_result->f_damage), native_damage_source->fn_randDamage(nullptr, 0))));
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Fatigue_2781)}; return native_damage_source->fn_hasType(_ca, 1); })())) {
            (native_damage_result->f_damage = gd::gd_coerce_int(gd::gd_add(gd_ctx, (native_damage_result->f_damage), character.f_bonusFatigueDamage)));
        }
        if (gd::gd_truth(native_damage_source->fn_canCrit(nullptr, 0))) {
            gd::GdVal lv_critical = gd::GdVal::from_bool(false);
            gd::GdVal lv_critChancePercent = native_damage_source->fn_getCritChancePercent(nullptr, 0);
            if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_critChancePercent, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_critChancePercent}; return native_event_call<Gd__gd_core__CoreRng__INNER__BalancedRng, &Gd__gd_core__CoreRng__INNER__BalancedRng::fn_rollPercent>(gd_ctx, character.f_critRng, SYM_GEN_rollPercent_1760, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
                lv_critical = gd::GdVal::from_bool(true);
            }
            else if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getCritTokens_182, nullptr, 0), gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
                (void)gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_useCritToken_184, nullptr, 0);
                lv_critical = gd::GdVal::from_bool(true);
            }
            else if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(native_event_call<Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::fn_getCritTokens>(gd_ctx, character.f_opponent, SYM_GEN_getCritTokens_182, nullptr, 0), gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(native_damage_source->fn_isAttackOrEffect(nullptr, 0))) : gd::GdVal::from_bool(false)))) {
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
                    (void)native_damage_result->fn_makeCritical(nullptr, 0);
                }
            }
        }
        gd::GdVal lv_activeDmgResi = gd::gd_clamp(gd::gd_div(gd_ctx, character.f_damageResistance, gd::GdVal::from_int(100LL)), gd::gd_neg(gd::GdVal::from_int(10LL)), gd::GdVal::from_int(1LL));
        (native_damage_result->f_damage = gd::gd_coerce_int(gd::gd_round(gd::gd_mul((native_damage_result->f_damage), gd::gd_sub(gd::GdVal::from_float(1.0), lv_activeDmgResi)))));
        if (gd::gd_truth(native_event_call<Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::fn_isAttack>(gd_ctx, (native_damage_result->f_damageSource), SYM_GEN_isAttack_1560, nullptr, 0))) {
            (native_damage_result->f_damage = gd::gd_coerce_int(gd::gd_sub((native_damage_result->f_damage), character.f_damageReduction)));
        }
        if (gd::gd_truth(character.f_invulnerable)) {
            (native_damage_result->f_damage = gd::gd_coerce_int(gd::GdVal::from_int(0LL)));
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj((&character)), gd::GdVal::from_str(&battle_string_literals[19]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return native_event_call<Gd__gd_core__CoreEventBus, &Gd__gd_core__CoreEventBus::fn_emitSignal>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_bus>(gd_ctx, character.f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
        (native_damage_result->f_damage = gd::gd_coerce_int(gd::gd_sub((native_damage_result->f_damage), (native_damage_result->f_damageReduction))));
        (native_damage_result->f_damage = gd::gd_coerce_int(gd::gd_max(gd::GdVal::from_int(0LL), (native_damage_result->f_damage))));
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(native_damage_source->fn_isAttack(nullptr, 0))) : gd::GdVal::from_bool(false)))) {
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
        (native_damage_result->f_healthDamage = gd::gd_coerce_int((native_damage_result->f_damage)));
        if (gd::gd_truth(native_damage_source->fn_canBeBlocked(nullptr, 0))) {
            gd::GdVal lv_curBlock = character.fn_getBlock(nullptr, 0);
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt((native_damage_result->f_damage), lv_curBlock)))) {
                (native_damage_result->f_healthDamage = gd::gd_coerce_int(gd::gd_sub((native_damage_result->f_healthDamage), lv_curBlock)));
                (void)([&]() { gd::GdVal _ca[] = {lv_curBlock}; return character.fn_loseBlock(_ca, 1); })();
            }
            else {
                (void)([&]() { gd::GdVal _ca[] = {(native_damage_result->f_damage)}; return character.fn_loseBlock(_ca, 1); })();
                (native_damage_result->f_healthDamage = gd::gd_coerce_int(gd::GdVal::from_int(0LL)));
            }
        }
        character.f_curHealth = gd::gd_coerce_float(gd::gd_sub(character.f_curHealth, (native_damage_result->f_healthDamage)));
        if (gd::gd_truth(native_damage_result->fn_wasCriticalHit(nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL), (native_damage_result->f_damage), lv_item}; return character.fn_spawnLabel_native(_ca, 3); })();
        }
        else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Fatigue_2781)}; return native_damage_source->fn_hasType(_ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(99LL), (native_damage_result->f_damage), lv_item}; return character.fn_spawnLabel_native(_ca, 3); })();
        }
        else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Poison_2664)}; return native_damage_source->fn_hasType(_ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(108LL), (native_damage_result->f_damage), lv_item}; return character.fn_spawnLabel_native(_ca, 3); })();
        }
        else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Spikes_2662)}; return native_damage_source->fn_hasType(_ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(104LL), (native_damage_result->f_damage), lv_item}; return character.fn_spawnLabel_native(_ca, 3); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), (native_damage_result->f_damage), lv_item}; return character.fn_spawnLabel_native(_ca, 3); })();
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(character.f_damage_anim_current, gd::GdVal::from_str(&battle_string_literals[22]))))) {
            if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq((native_damage_result->f_healthDamage), gd::GdVal::from_int(0LL))))) {
                character.f_damage_anim_current = gd::GdVal::from_str(&battle_string_literals[23]);
            }
            else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Fatigue_2781)}; return native_damage_source->fn_hasType(_ca, 1); })())) {
                character.f_damage_anim_current = gd::GdVal::from_str(&battle_string_literals[24]);
            }
            else {
                character.f_damage_anim_current = gd::GdVal::from_str(&battle_string_literals[25]);
            }
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_randf_range>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, character.f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj((&character)), (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Fatigue_2781)}; return native_damage_source->fn_hasType(_ca, 1); })()) ? (gd::GdVal::from_str(&battle_string_literals[24])) : (gd::GdVal::from_str(&battle_string_literals[25])))}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, character.f_ctx, SYM_GEN_hooks_1409), SYM_GEN_damageAnimation_1639, _ca, 2); })();
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
    (native_damage_result->f_event = lv_event);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj((&character)), gd::GdVal::from_str(&battle_string_literals[27]), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return native_event_call<Gd__gd_core__CoreEventBus, &Gd__gd_core__CoreEventBus::fn_emitEvent>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_bus>(gd_ctx, character.f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitEvent_1593, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj((&character)), gd::GdVal::from_str(&battle_string_literals[28]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {(native_damage_result->f_healthDamage), (native_damage_result->f_event)}))}; return native_event_call<Gd__gd_core__CoreEventBus, &Gd__gd_core__CoreEventBus::fn_emitSignal>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_bus>(gd_ctx, character.f_ctx, SYM_GEN_bus_1408), SYM_GEN_emitSignal_1592, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj((&character))}; return gd_native_event_hooks_call(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_hooks>(gd_ctx, character.f_ctx, SYM_GEN_hooks_1409), SYM_GEN_onHealthChangedUI_1641, _ca, 1); })();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(native_damage_source->fn_isAttack(nullptr, 0))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_hasDealtDamageEffect_64))) : gd::GdVal::from_bool(false)))) {
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
