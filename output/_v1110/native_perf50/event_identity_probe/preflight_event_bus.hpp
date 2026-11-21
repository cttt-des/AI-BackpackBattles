#pragma once
#include "native_scalar_equal.hpp"
#include "native_array_index.hpp"
#include "native_event_kernel.hpp"
#include "event_identity_receiver_fastpath.hpp"
namespace {
constexpr gd::GdStr battle_string_literals[] = {
    {"", 0u, 2166136261u},
    {"?", 1u, 973910158u},
    {"isCoreItem", 10u, 3597329357u},
    {"/ot", 3u, 3885608693u},
    {"BUS", 3u, 3834310425u},
    {"emitter=", 8u, 2374018256u},
    {"BUSL", 4u, 464962255u},
    {"BUSD", 4u, 599183207u},
    {"character_mana_changed", 22u, 798563205u},
    {"checkTrigger", 12u, 3751686889u},
    {"character_invulnerable_end", 26u, 3350240732u},
    {"onInvuEnded", 11u, 2135122486u},
    {"dur_invu", 8u, 277695711u},
    {"BuffTimer", 9u, 194754125u},
    {"buffEnded", 9u, 3457903416u},
    {"mana", 4u, 3650585354u},
    {"dur", 3u, 3509645056u},
    {"character_pre_use_stamina", 25u, 4061960724u},
    {"checkStamina", 12u, 3432866148u},
    {"maxhealth", 9u, 429334299u},
    {"Piggy Pinata_CRAFT", 18u, 23902885u},
    {"Piggy Pinata", 12u, 2904436292u},
    {"Hammer", 6u, 3178970599u},
    {"Thors Hammer", 12u, 3528755945u},
    {"heal", 4u, 979982427u},
    {"character_damaged", 17u, 745527748u},
    {"onDamaged", 9u, 2303747743u},
    {"dam", 3u, 4031722721u},
    {"Eggscalibur.gd:9", 16u, 394458383u},
    {"|", 1u, 4178332219u},
    {"ESHUF", 5u, 2622025276u},
    {"t=", 2u, 340066234u},
    {"Flame", 5u, 739594656u},
    {"Fanny Pack", 10u, 1541458896u},
    {"Stamina Sack", 12u, 3135812348u},
    {"Potion Belt", 11u, 3530571787u},
    {"Protective Purse", 16u, 3560043597u},
    {"regen", 5u, 16724762u},
    {"luck", 4u, 4145017712u},
    {"spikes", 6u, 439106706u},
    {"speed", 5u, 2072037248u},
    {"buffs", 5u, 2149256365u},
    {"battle_rage_started", 19u, 3997014835u},
    {"onBattleRageStarted", 19u, 3330696088u},
    {"battle_rage_ended", 17u, 4230921894u},
    {"onBattleRageEnded", 17u, 1252110145u},
    {"character_regeneration_changed", 30u, 2797934681u},
    {"onRegenChanged", 14u, 661197895u},
    {"empower", 7u, 2037162760u},
    {"dam_empower", 11u, 3673063641u},
    {"character_lucky_changed", 23u, 2259242176u},
    {"onLuckyChanged", 14u, 1760969932u},
    {"manat", 5u, 126091098u},
    {"cleanse", 7u, 4032992022u},
    {"block", 5u, 3943480674u},
    {"Fly Agaric", 10u, 3159823061u},
    {"Doom Cap", 8u, 3691411692u},
    {"num", 3u, 242376115u},
    {"onBuffsChanged", 14u, 1288163266u},
    {"poison2", 7u, 848357177u},
    {"mana2", 5u, 3246625064u},
    {"gained", 6u, 52449535u},
    {"used", 4u, 1786277552u},
    {"poison", 6u, 3470992305u},
    {"L", 1u, 3373006507u},
    {"S", 1u, 3591115554u},
    {"Z", 1u, 3742114125u},
    {"T", 1u, 3507227459u},
    {"J", 1u, 3473672221u},
    {"speed2", 6u, 498752822u},
    {"reflect", 7u, 2462546090u},
    {"steal", 5u, 218799968u},
    {"\n", 1u, 252472541u},
    {"CARD_DUPLICATES", 15u, 4183871766u},
    {"CARD_HINT", 9u, 4169059801u},
    {"Shield of Valor", 15u, 644584623u},
    {"chance", 6u, 2459084481u},
    {"blocked", 7u, 1516072627u},
    {"onShieldBlocked", 15u, 2340875007u},
    {"used_heat", 9u, 3089606235u},
    {"onArmorUsedHeat", 15u, 2991089272u},
    {"Sun Shield", 10u, 826446202u},
    {"Sun Armor", 9u, 1667246802u},
    {"Holy Armor", 10u, 4110091228u},
    {"heat", 4u, 577319571u},
    {"character_spikes_changed", 24u, 3463900413u},
    {"onSpikesChanged", 15u, 3715123341u},
    {"dur_stun", 8u, 1388942617u},
    {"max", 3u, 3617776409u},
    {"Exclusive/UnidentifiedSkill.gd:23", 33u, 3479551509u},
    {"identifySkill", 13u, 3093266174u},
    {"round1", 6u, 2041894334u},
    {"round2", 6u, 2025116715u},
    {"TOOLTIP_Always Offered2", 23u, 3965178019u},
    {"\n\n", 2u, 2274317941u},
    {"dropped", 7u, 3229108261u},
    {"onDropped", 9u, 1334518102u},
    {"getSkillPool", 12u, 1868377090u},
    {"luckt", 5u, 4061892428u},
    {"Bagtacular", 10u, 2131747329u},
    {"stamina", 7u, 3875003702u},
};
}
inline gd::GdVal candidate_emit_and_log(Gd__gd_core__CoreEventBus& bus,const gd::GdVal* _args,int _argc) {

    gd::BattleCtx& gd_ctx = *bus.rt_ctx_;
    if (gd_ctx.native_event_kernel) {
        ++gd_ctx.native_event_counts[0];
    gd::GdVal lv_emitter = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_signalName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_arguments = (_argc > 3) ? _args[3] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_event, gd::GdVal::null())))) {
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_fight_ended>(gd_ctx, bus.f__ctx, SYM_GEN_fight_ended_1305))))) {
            if (gd::gd_truth(native_event_get<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::f_oracle_trace>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, bus.f__ctx, SYM_GEN_rng_1406), SYM_GEN_oracle_trace_1729))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, lv_event, SYM_GEN_type_1005)}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_trace_event>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, bus.f__ctx, SYM_GEN_rng_1406), SYM_GEN_trace_event_1740, _ca, 1); })();
            }
            (void)([&]() { gd::GdVal _ca[] = {lv_event}; return native_event_call<Gd__gd_core__CoreCombatLog, &Gd__gd_core__CoreCombatLog::fn_logEvent>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_combat_log>(gd_ctx, bus.f__ctx, SYM_GEN_combat_log_1410), SYM_GEN_logEvent_1357, _ca, 1); })();
        }
    }
    if (lv_emitter.is_null()) return gd::GdVal::null();
    gd::GdVal lv_signalID;
    if (bus.f_signalIDs.kind == gd::GdVal::Kind::Dict && bus.f_signalIDs.dict) {
        const auto* signals = bus.f_signalIDs.dict;
        const auto index = signals->find_index(lv_signalName);
        if (index < 0) return gd::GdVal::null();
        lv_signalID = signals->entries[index].val;
    } else {
        if (!gd::gd_truth(gd::gd_in(lv_signalName, bus.f_signalIDs))) return gd::GdVal::null();
        lv_signalID = gd::native_array_index(gd_ctx, bus.f_signalIDs, lv_signalName);
    }
    gd::GdVal lv_emissionID = ([&]() { gd::GdVal _ca[] = {lv_emitter, lv_signalID}; return bus.fn_getEmissionID(_ca, 2); })();
    const auto bus_trace_enabled = [&] {
        const auto rng = native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, bus.f__ctx, SYM_GEN_rng_1406);
        return gd::gd_truth(gd::native_inline_get_prop(gd_ctx, rng, SYM_GEN_oracle_trace_1729))
            && gd::gd_truth(gd::native_inline_get_prop(gd_ctx, rng, SYM_GEN__stacktrace_1731));
    };
    gd::GdVal lv__bus_list;
    if (bus.f_connections.kind == gd::GdVal::Kind::Dict && bus.f_connections.dict) {
        const auto* connections = bus.f_connections.dict;
        const auto index = connections->find_index(lv_emissionID);
        if (index < 0) {
            if (!bus_trace_enabled()) return gd::GdVal::null();
            lv__bus_list = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
        } else {
            lv__bus_list = connections->entries[index].val;
            if (lv__bus_list.kind == gd::GdVal::Kind::Arr && lv__bus_list.arr
                    && lv__bus_list.arr->len == 0 && !bus_trace_enabled()) return gd::GdVal::null();
        }
    } else {
        lv__bus_list = ([&]() { gd::GdVal _ca[] = {lv_emissionID, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::native_inline_call(gd_ctx, bus.f_connections, gd::SYM_get, _ca, 2); })();
    }
    if (gd::gd_truth((gd::gd_truth(native_event_get<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::f_oracle_trace>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, bus.f__ctx, SYM_GEN_rng_1406), SYM_GEN_oracle_trace_1729)) ? gd::GdVal::from_bool(gd::gd_truth(native_event_get<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::f__stacktrace>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, bus.f__ctx, SYM_GEN_rng_1406), SYM_GEN__stacktrace_1731))) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv__eid = gd::GdVal::from_str(&battle_string_literals[1]);
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_emitter, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[2])}; return gd::native_inline_call(gd_ctx, lv_emitter, gd::SYM_has_method, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
            lv__eid = gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_emitter, SYM_GEN_descriptor_2), SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[3])), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(gd::native_inline_get_prop(gd_ctx, lv_emitter, SYM_GEN_ownerType_49))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })());
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[4]), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, lv_signalName)), ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, lv__bus_list, gd::SYM_size, nullptr, 0)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[5]), lv__eid)}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_trace_diag>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, bus.f__ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
    }
    gd::GdVal lv__bus_i = gd::GdVal::from_int(0LL);
    gd::GdVal lv__eid2 = gd::GdVal::from_str(&battle_string_literals[1]);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_emitter, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[2])}; return gd::native_inline_call(gd_ctx, lv_emitter, gd::SYM_has_method, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        if(!gd::native_try_event_identity(gd_ctx,lv_emitter,&battle_string_literals[3],lv__eid2)) {
        lv__eid2 = gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_emitter, SYM_GEN_descriptor_2), SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[3])), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(gd::native_inline_get_prop(gd_ctx, lv_emitter, SYM_GEN_ownerType_49))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })());
        }
    }
    {
        gd::GdVal _t1644 = gd::gd_iter_seq(gd_ctx.arena, lv__bus_list);
        gd::GdArr* _t1645 = (_t1644.kind == gd::GdVal::Kind::Arr) ? _t1644.arr : nullptr;
        uint32_t _len__t1646 = _t1645 ? _t1645->len : 0u;
        for (uint32_t _t1646 = 0; _t1646 < _len__t1646; ++_t1646) {
            gd::GdVal lv__bus_pair = _t1645->data[_t1646];
            if (gd::gd_truth(native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_fight_ended>(gd_ctx, bus.f__ctx, SYM_GEN_fight_ended_1305))) {
                return gd::GdVal::null();
            }
            if (gd::gd_truth((gd::gd_truth(native_event_get<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::f_oracle_trace>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, bus.f__ctx, SYM_GEN_rng_1406), SYM_GEN_oracle_trace_1729)) ? gd::GdVal::from_bool(gd::gd_truth(native_event_get<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::f__stacktrace>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, bus.f__ctx, SYM_GEN_rng_1406), SYM_GEN__stacktrace_1731))) : gd::GdVal::from_bool(false)))) {
                gd::GdVal lv__rid = gd::GdVal::from_str(&battle_string_literals[1]);
                gd::GdVal lv__recv = gd::native_array_index(gd_ctx, lv__bus_pair, gd::GdVal::from_int(1LL));
                if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv__recv, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[2])}; return gd::native_inline_call(gd_ctx, lv__recv, gd::SYM_has_method, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
                    lv__rid = gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv__recv, SYM_GEN_descriptor_2), SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[3])), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(gd::native_inline_get_prop(gd_ctx, lv__recv, SYM_GEN_ownerType_49))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })());
                }
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[6]), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, lv_signalName)), ([&]() { gd::GdVal _ca[] = {lv__bus_i}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), lv__rid}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_trace_diag>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, bus.f__ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
            }
            lv__bus_i = gd::gd_add(gd_ctx, lv__bus_i, gd::GdVal::from_int(1LL));
            (void)([&]() { gd::GdVal _ca[] = {lv_arguments}; return native_event_funcv(gd_ctx, gd::native_array_index(gd_ctx, lv__bus_pair, gd::GdVal::from_int(0LL)), _ca, 1); })();
        }
    }
    if (gd::gd_truth((gd::gd_truth(native_event_get<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::f_oracle_trace>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, bus.f__ctx, SYM_GEN_rng_1406), SYM_GEN_oracle_trace_1729)) ? gd::GdVal::from_bool(gd::gd_truth(native_event_get<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::f__stacktrace>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, bus.f__ctx, SYM_GEN_rng_1406), SYM_GEN__stacktrace_1731))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7]), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, lv_signalName)), ([&]() { gd::GdVal _ca[] = {lv__bus_i}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[5]), lv__eid2)}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_trace_diag>(gd_ctx, native_event_get<Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::f_rng>(gd_ctx, bus.f__ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
    }
    return gd::GdVal::null();
    }
    gd::GdVal lv_emitter = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_signalName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_arguments = (_argc > 3) ? _args[3] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_event, gd::GdVal::null())))) {
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_get_prop(gd_ctx, bus.f__ctx, SYM_GEN_fight_ended_1305))))) {
            if (gd::gd_truth(gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, bus.f__ctx, SYM_GEN_rng_1406), SYM_GEN_oracle_trace_1729))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, lv_event, SYM_GEN_type_1005)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, bus.f__ctx, SYM_GEN_rng_1406), SYM_GEN_trace_event_1740, _ca, 1); })();
            }
            (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, bus.f__ctx, SYM_GEN_combat_log_1410), SYM_GEN_logEvent_1357, _ca, 1); })();
        }
    }
    if (lv_emitter.is_null()) return gd::GdVal::null();
    gd::GdVal lv_signalID;
    if (bus.f_signalIDs.kind == gd::GdVal::Kind::Dict && bus.f_signalIDs.dict) {
        const auto* signals = bus.f_signalIDs.dict;
        const auto index = signals->find_index(lv_signalName);
        if (index < 0) return gd::GdVal::null();
        lv_signalID = signals->entries[index].val;
    } else {
        if (!gd::gd_truth(gd::gd_in(lv_signalName, bus.f_signalIDs))) return gd::GdVal::null();
        lv_signalID = gd::native_array_index(gd_ctx, bus.f_signalIDs, lv_signalName);
    }
    gd::GdVal lv_emissionID = ([&]() { gd::GdVal _ca[] = {lv_emitter, lv_signalID}; return bus.fn_getEmissionID(_ca, 2); })();
    const auto bus_trace_enabled = [&] {
        const auto rng = gd::native_inline_get_prop(gd_ctx, bus.f__ctx, SYM_GEN_rng_1406);
        return gd::gd_truth(gd::native_inline_get_prop(gd_ctx, rng, SYM_GEN_oracle_trace_1729))
            && gd::gd_truth(gd::native_inline_get_prop(gd_ctx, rng, SYM_GEN__stacktrace_1731));
    };
    gd::GdVal lv__bus_list;
    if (bus.f_connections.kind == gd::GdVal::Kind::Dict && bus.f_connections.dict) {
        const auto* connections = bus.f_connections.dict;
        const auto index = connections->find_index(lv_emissionID);
        if (index < 0) {
            if (!bus_trace_enabled()) return gd::GdVal::null();
            lv__bus_list = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
        } else {
            lv__bus_list = connections->entries[index].val;
            if (lv__bus_list.kind == gd::GdVal::Kind::Arr && lv__bus_list.arr
                    && lv__bus_list.arr->len == 0 && !bus_trace_enabled()) return gd::GdVal::null();
        }
    } else {
        lv__bus_list = ([&]() { gd::GdVal _ca[] = {lv_emissionID, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::native_inline_call(gd_ctx, bus.f_connections, gd::SYM_get, _ca, 2); })();
    }
    if (gd::gd_truth((gd::gd_truth(gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, bus.f__ctx, SYM_GEN_rng_1406), SYM_GEN_oracle_trace_1729)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, bus.f__ctx, SYM_GEN_rng_1406), SYM_GEN__stacktrace_1731))) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv__eid = gd::GdVal::from_str(&battle_string_literals[1]);
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_emitter, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[2])}; return gd::native_inline_call(gd_ctx, lv_emitter, gd::SYM_has_method, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
            lv__eid = gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_emitter, SYM_GEN_descriptor_2), SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[3])), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(gd::native_inline_get_prop(gd_ctx, lv_emitter, SYM_GEN_ownerType_49))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })());
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[4]), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, lv_signalName)), ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, lv__bus_list, gd::SYM_size, nullptr, 0)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[5]), lv__eid)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, bus.f__ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
    }
    gd::GdVal lv__bus_i = gd::GdVal::from_int(0LL);
    gd::GdVal lv__eid2 = gd::GdVal::from_str(&battle_string_literals[1]);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_emitter, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[2])}; return gd::native_inline_call(gd_ctx, lv_emitter, gd::SYM_has_method, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        lv__eid2 = gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_emitter, SYM_GEN_descriptor_2), SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[3])), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(gd::native_inline_get_prop(gd_ctx, lv_emitter, SYM_GEN_ownerType_49))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })());
    }
    {
        gd::GdVal _t1644 = gd::gd_iter_seq(gd_ctx.arena, lv__bus_list);
        gd::GdArr* _t1645 = (_t1644.kind == gd::GdVal::Kind::Arr) ? _t1644.arr : nullptr;
        uint32_t _len__t1646 = _t1645 ? _t1645->len : 0u;
        for (uint32_t _t1646 = 0; _t1646 < _len__t1646; ++_t1646) {
            gd::GdVal lv__bus_pair = _t1645->data[_t1646];
            if (gd::gd_truth(gd::native_inline_get_prop(gd_ctx, bus.f__ctx, SYM_GEN_fight_ended_1305))) {
                return gd::GdVal::null();
            }
            if (gd::gd_truth((gd::gd_truth(gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, bus.f__ctx, SYM_GEN_rng_1406), SYM_GEN_oracle_trace_1729)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, bus.f__ctx, SYM_GEN_rng_1406), SYM_GEN__stacktrace_1731))) : gd::GdVal::from_bool(false)))) {
                gd::GdVal lv__rid = gd::GdVal::from_str(&battle_string_literals[1]);
                gd::GdVal lv__recv = gd::native_array_index(gd_ctx, lv__bus_pair, gd::GdVal::from_int(1LL));
                if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv__recv, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[2])}; return gd::native_inline_call(gd_ctx, lv__recv, gd::SYM_has_method, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
                    lv__rid = gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv__recv, SYM_GEN_descriptor_2), SYM_GEN_identifier_1673))), gd::GdVal::from_str(&battle_string_literals[3])), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(gd::native_inline_get_prop(gd_ctx, lv__recv, SYM_GEN_ownerType_49))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })());
                }
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[6]), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, lv_signalName)), ([&]() { gd::GdVal _ca[] = {lv__bus_i}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), lv__rid}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, bus.f__ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
            }
            lv__bus_i = gd::gd_add(gd_ctx, lv__bus_i, gd::GdVal::from_int(1LL));
            (void)([&]() { gd::GdVal _ca[] = {lv_arguments}; return gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, lv__bus_pair, gd::GdVal::from_int(0LL)), gd::SYM_call_funcv, _ca, 1); })();
        }
    }
    if (gd::gd_truth((gd::gd_truth(gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, bus.f__ctx, SYM_GEN_rng_1406), SYM_GEN_oracle_trace_1729)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, bus.f__ctx, SYM_GEN_rng_1406), SYM_GEN__stacktrace_1731))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[7]), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, lv_signalName)), ([&]() { gd::GdVal _ca[] = {lv__bus_i}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[5]), lv__eid2)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, bus.f__ctx, SYM_GEN_rng_1406), SYM_GEN_trace_diag_1741, _ca, 4); })();
    }
    return gd::GdVal::null();
}
