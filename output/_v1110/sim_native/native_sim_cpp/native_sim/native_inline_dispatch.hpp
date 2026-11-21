#pragma once
#include "gd_rt.hpp"
#include "gen/sym_ids.hpp"
#include "gen/class_metas.hpp"
#include <array>
#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include "gen/hdrs/Gd__gd_core__CoreContext.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "gen/hdrs/Gd__gd_core__CoreBuff.hpp"
#include "gen/hdrs/Gd__gd_core_items__Gems__Gem.hpp"
namespace gd {
using NativeResolvedFn = GdVal (*)(GdObj*, const GdVal*, int);
using NativePropertyFn = GdVal GdObj::*;
struct NativePropertyRow { std::array<NativePropertyFn,64> getters; };
struct NativeMethodRow { const GdClassMeta* metadata; const NativePropertyRow* properties; uint64_t type_mask; std::array<NativeResolvedFn,128> methods; };
inline constexpr auto native_resolved_slots=[] { std::array<int8_t,static_cast<size_t>(SYM_GEN_Dragon_2878)+1> value{}; value.fill(-1);
    value[SYM_GEN_trigger_143]=0;
    value[SYM_GEN_doCooldownEffect_144]=1;
    value[SYM_GEN_dealDamage_220]=2;
    value[SYM_GEN_addItem_1618]=3;
    value[SYM_GEN_activate_150]=4;
    value[SYM_GEN_giveStacks_201]=5;
    value[SYM_GEN_gainStacks_1030]=6;
    value[SYM_GEN__behavior_call_504]=7;
    value[SYM_GEN_onItemAdded_437]=8;
    value[SYM_GEN_emitEvent_1593]=9;
    value[SYM_GEN_onDealtDamage_908]=10;
    value[SYM_GEN__tickChargePath_506]=11;
    value[SYM_GEN_combatStart_127]=12;
    value[SYM_GEN_heal_327]=13;
    value[SYM_GEN_onItemActivated_938]=14;
    value[SYM_GEN_addToInventory_120]=15;
    value[SYM_GEN_onCombatStart_934]=16;
    value[SYM_GEN_stackChanged_232]=17;
    value[SYM_GEN_prepareItems_1320]=18;
    value[SYM_GEN__readyInit_140]=19;
    value[SYM_GEN_loseStacks_1032]=20;
    value[SYM_GEN_setup_72]=21;
    value[SYM_GEN_prepare_122]=22;
    value[SYM_GEN_addSpeed_273]=23;
    value[SYM_GEN__chargeEnterCell_323]=24;
    value[SYM_GEN_giveMana_216]=25;
    value[SYM_GEN_getNextFreeLabelPosition_378]=26;
    value[SYM_GEN_giveHeat_218]=27;
    value[SYM_GEN_emitSignal_1592]=28;
    value[SYM_GEN_onTriggerItemActivated_2474]=29;
    value[SYM_GEN_cacheAffectedCells_416]=30;
    value[SYM_GEN_giveBlock_203]=31;
    value[SYM_GEN_getP_188]=32;
    value[SYM_GEN_character_74]=33;
    value[SYM_GEN_connectForCombat_500]=34;
    value[SYM_GEN_getAffectedItems_420]=35;
    value[SYM_GEN_getP1_263]=36;
    value[SYM_GEN_hasType_79]=37;
    value[SYM_GEN_setState_382]=38;
    value[SYM_GEN_opponent_75]=39;
    value[SYM_GEN_getP_m_189]=40;
    value[SYM_GEN_getP2_264]=41;
    value[SYM_GEN_hasHit_1523]=42;
    value[SYM_GEN_getP3_265]=43;
    value[SYM_GEN_getDescriptor_1660]=44;
    value[SYM_GEN_getNumAffectedItems_427]=45;
    value[SYM_GEN_getChance_171]=46;
    value[SYM_GEN_miniActivate_470]=47;
    value[SYM_GEN_tick_1516]=48;
    value[SYM_GEN_isBag_83]=49;
    value[SYM_GEN_getStacks_1023]=50;
    value[gd::SYM_randf_range]=51;
    value[SYM_GEN_canAffect_286]=52;
    value[SYM_GEN_getItemsInCells_1608]=53;
    value[SYM_GEN_canAffect_lightning_289]=54;
    value[SYM_GEN_canAffect_secondary_287]=55;
    value[SYM_GEN_canAffect_tertiary_288]=56;
    value[SYM_GEN_getGemMode_972]=57;
    value[SYM_GEN_getGemsNoNull_497]=58;
    value[SYM_GEN_getItemsInside_924]=59;
    value[SYM_GEN_addMetric_230]=60;
    value[SYM_GEN_snapshotItemMetric_1383]=61;
    value[SYM_GEN_trace_diag_1741]=62;
    value[SYM_GEN_getOwnOrPlayerInventory_400]=63;
    value[SYM_GEN_snapshotItemTooltipStat_1384]=64;
    value[SYM_GEN_playActivationSound_148]=65;
    value[SYM_GEN_isWeapon_82]=66;
    value[SYM_GEN_tickVisualMotion_1137]=67;
    value[SYM_GEN_hasCooldown_95]=68;
    value[SYM_GEN_getAffectedCellsInInventory_cached_415]=69;
    value[SYM_GEN_getItemsInAffectedCells_cached_423]=70;
    value[SYM_GEN_getItem_389]=71;
    value[SYM_GEN_hasCharacter_73]=72;
    value[SYM_GEN_getCellsForGlobalPositions_401]=73;
    value[SYM_GEN__hasBehaviorMethod_503]=74;
    value[SYM_GEN_getAffectedCells_tilemap_408]=75;
    value[SYM_GEN_getAffectedCellsAfterRotate_409]=76;
    value[SYM_GEN_getAffectedCells_noRotate_412]=77;
    value[SYM_GEN_getAffectedPoints_413]=78;
    value[SYM_GEN_getAffectedCellsInInventory_414]=79;
    value[SYM_GEN_checkActivationLimit_151]=80;
    value[SYM_GEN_playDropSound_149]=81;
    value[SYM_GEN_createEvent_Activation_1380]=82;
    value[SYM_GEN_flip_1735]=83;
    value[SYM_GEN_getHeat_1251]=84;
    value[SYM_GEN_getP_check_262]=85;
    value[SYM_GEN_getAmplificationChancePercent_195]=86;
    value[SYM_GEN_applyBonusChance_170]=87;
    value[SYM_GEN_getCooldown_102]=88;
    value[SYM_GEN_adjustCooldown_107]=89;
    value[SYM_GEN_bare_randf_range_1743]=90;
    value[SYM_GEN_getBaseChance_168]=91;
    value[SYM_GEN_getCold_1254]=92;
    value[SYM_GEN_getSpeed_92]=93;
    value[SYM_GEN_speed_93]=94;
    value[SYM_GEN_getStackSpeedMods_94]=95;
    value[SYM_GEN_changeAmplificiationChancePercent_196]=96;
    value[SYM_GEN_rollPercent_1760]=97;
    value[SYM_GEN_hasTag_81]=98;
    value[SYM_GEN_rollChance_173]=99;
    value[SYM_GEN_reset_1025]=100;
    value[SYM_GEN_getMana_1244]=101;
    value[SYM_GEN_getAmount_1576]=102;
    value[SYM_GEN_onManaChanged_1929]=103;
    value[SYM_GEN_canApplyEffect_920]=104;
    value[SYM_GEN_onBuffChanged_2006]=105;
    value[SYM_GEN_getParamModified_190]=106;
    value[SYM_GEN_canBeEmpowered_90]=107;
    value[SYM_GEN_hasStartofBattle_126]=108;
    value[SYM_GEN_canAffect_global_2014]=109;
    value[SYM_GEN_otherCharacter_1477]=110;
    value[SYM_GEN_useStamina_116]=111;
    value[SYM_GEN_attack_941]=112;
    value[SYM_GEN_useMana_332]=113;
    value[SYM_GEN_cleanseRandomDebuffs_356]=114;
    value[SYM_GEN_giveMaxHealth_317]=115;
    value[SYM_GEN_giveLucky_215]=116;
    value[SYM_GEN_giveMostBuffs_367]=117;
    value[SYM_GEN_onPreDealDamage_early_945]=118;
    value[SYM_GEN_onPrepare_123]=119;
    value[SYM_GEN_changeChargedItemStat_326]=120;
    value[SYM_GEN_onChargeEnteredCell_2059]=121;
    value[SYM_GEN_emitCharge_2058]=122;
    value[SYM_GEN_giveSpikes_209]=123;
    value[SYM_GEN_chargeReceived_324]=124;
    value[SYM_GEN_onChargeReceived_2129]=125;
    value[SYM_GEN_giveRandomBuffs_369]=126;
    value[SYM_GEN_combatEndDeferred_1335]=127;
    return value; }();
bool native_resolved_row_matches(const GdObj*,const NativeMethodRow*);
inline constexpr std::array<const GdClassMeta*,8> native_type_targets={&META_Gd__gd_core_items__Gems__Gem,&META_Gd__gd_core__CoreItem,&META_Gd__gd_core_items__Item,&META_Gd__gd_core_items__Exclusive__Chess__ChessPiece,&META_Gd__gd_core_items__Card,&META_Gd__gd_core_items__Dagger,&META_Gd__gd_core_items__Goobert,&META_Gd__gd_core_items__RangerCollar};

void native_type_constructor_hit(unsigned);
#if defined(_MSC_VER)
__forceinline
#elif defined(__GNUC__)
__attribute__((always_inline)) inline
#else
inline
#endif
bool native_inline_is_type(BattleCtx& ctx,const GdVal& value,const GdClassMeta* target) {
    if(!target || value.kind!=GdVal::Kind::Obj || !value.obj)return false;
    if(ctx.native_resolved_dispatch) {
        const NativeMethodRow* row=value.obj->native_call_row_;
        if(row) {
            if(ctx.native_resolved_audit && !native_resolved_row_matches(value.obj,row)) {
                ++ctx.native_resolved_counts[4];
            } else if(row->metadata) {
                if(ctx.native_resolved_collect)native_type_constructor_hit(0);
                for(unsigned i=0;i<native_type_targets.size();++i)
                    if(target==native_type_targets[i])return (row->type_mask & (uint64_t{1}<<i))!=0;
                return row->metadata->is_subclass_of(target);
            }
        }
        if(ctx.native_resolved_collect)native_type_constructor_hit(1);
    }
    return gd::gd_is_type(value,target);
}
inline bool native_inline_self_type(BattleCtx* ctx,GdObj* object,const GdClassMeta* target) {
    if(ctx)return native_inline_is_type(*ctx,GdVal::from_obj(object),target);
    return gd::gd_is_type(GdVal::from_obj(object),target);
}

inline constexpr auto native_property_slots=[] { std::array<int8_t,static_cast<size_t>(SYM_GEN_Dragon_2878)+1> value{}; value.fill(-1);
    value[SYM_GEN_rng_1406]=0;
    value[SYM_GEN_item_book_1421]=1;
    value[SYM_GEN_util_1407]=2;
    value[SYM_GEN_combat_log_1410]=3;
    value[SYM_GEN_bus_1408]=4;
    value[SYM_GEN_event_1517]=5;
    value[SYM_GEN_hooks_1409]=6;
    value[SYM_GEN_damage_1518]=7;
    value[SYM_GEN_descriptor_2]=8;
    value[SYM_GEN_identifier_1673]=9;
    value[SYM_GEN_damageSource_24]=10;
    value[SYM_GEN_playerId_1046]=11;
    value[SYM_GEN_time_1411]=12;
    value[SYM_GEN_origin_1546]=13;
    value[SYM_GEN_player_1302]=14;
    value[SYM_GEN_minDam_1675]=15;
    value[SYM_GEN_curChargedItem_1648]=16;
    value[SYM_GEN_occupiedCells_52]=17;
    value[SYM_GEN_ownerType_49]=18;
    value[SYM_GEN_oracle_trace_1729]=19;
    value[SYM_GEN_timer_pass_epoch_1445]=20;
    value[SYM_GEN_inventory_5]=21;
    value[SYM_GEN__stacktrace_1731]=22;
    value[SYM_GEN_opponent_75]=23;
    value[SYM_GEN_amount_1041]=24;
    value[SYM_GEN_types_1544]=25;
    value[SYM_GEN_lastChargedItem_1647]=26;
    value[SYM_GEN_timeout_1042]=27;
    value[SYM_GEN_combat_1420]=28;
    value[SYM_GEN_INVENTORY_1093]=29;
    value[SYM_GEN_name_7]=30;
    value[SYM_GEN_cd_1679]=31;
    value[SYM_GEN_buffs_1048]=32;
    value[SYM_GEN_frame_counter_1413]=33;
    value[SYM_GEN_shopChance_1683]=34;
    value[SYM_GEN_cube_advanced_1426]=35;
    value[SYM_GEN_signalName_1013]=36;
    value[SYM_GEN_type_1005]=37;
    value[SYM_GEN_placedByPlayer_50]=38;
    value[SYM_GEN_placed_6]=39;
    value[SYM_GEN_chainPosition_882]=40;
    value[SYM_GEN_cards_1832]=41;
    value[SYM_GEN_pieceColor_2135]=42;
    value[SYM_GEN_items_1092]=43;
    value[SYM_GEN_rope_speedups_1425]=44;
    value[SYM_GEN_baseStaminaRegen_1057]=45;
    value[SYM_GEN_stackType_2388]=46;
    value[SYM_GEN_animationScene_1695]=47;
    value[SYM_GEN_nextCell_1652]=48;
    value[SYM_GEN_in_physics_timer_pass_1446]=49;
    value[SYM_GEN_activationAni_1717]=50;
    value[SYM_GEN_curRecipe_577]=51;
    value[SYM_GEN_healthDamage_1519]=52;
    value[SYM_GEN_fatigueDamageSource_1430]=53;
    value[SYM_GEN_gainedStacks_1714]=54;
    value[SYM_GEN_extraCds_1680]=55;
    value[SYM_GEN_flickerMinDist_1697]=56;
    value[SYM_GEN_flickerMaxDist_1698]=57;
    value[SYM_GEN_flickerMinSpeed_1699]=58;
    value[SYM_GEN_flickerMaxSpeed_1700]=59;
    value[SYM_GEN_fight_ended_1305]=60;
    value[SYM_GEN_accuracy_1545]=61;
    value[SYM_GEN_params_1570]=62;
    value[SYM_GEN_ctx_3]=63;
    return value; }();
bool try_native_resolved_property(BattleCtx&,GdObj*,SymId,GdVal&);
void native_inline_property_hit(unsigned);
void native_inline_hot_slot_hit(unsigned);
#if defined(_MSC_VER)
__forceinline
#elif defined(__GNUC__)
__attribute__((always_inline)) inline
#else
inline
#endif
GdVal native_inline_get_prop(BattleCtx& ctx,const GdVal& recv,SymId prop) {
    const int slot=prop<native_property_slots.size()?native_property_slots[prop]:-1;
    if(slot>=0 && prop!=SYM_resource_path && ctx.native_resolved_dispatch &&
       recv.kind==GdVal::Kind::Obj && recv.obj) {
        const NativeMethodRow* row=recv.obj->native_call_row_;
        if(row && (!ctx.native_resolved_audit || native_resolved_row_matches(recv.obj,row))) {
            const auto function=row->properties ? row->properties->getters[slot] : nullptr;
            if(function) {
                if(ctx.native_resolved_collect) {native_inline_property_hit(0);if(slot>=32)native_inline_hot_slot_hit(1);}
                return recv.obj->*function;
            }
            if(ctx.native_resolved_collect)native_inline_property_hit(1);
            return gd::get_prop(ctx,recv,prop);
        }
        GdVal out;
        if(try_native_resolved_property(ctx,recv.obj,prop,out))return out;
    }
    return gd::get_prop(ctx,recv,prop);
}

void native_inline_variant_hit(unsigned);
#if defined(_MSC_VER)
__forceinline
#elif defined(__GNUC__)
__attribute__((always_inline)) inline
#else
inline
#endif
GdVal native_inline_call(BattleCtx& ctx,const GdVal& recv,SymId method,const GdVal* args,int argc) {
    const int slot=method<native_resolved_slots.size()?native_resolved_slots[method]:-1;
    if(slot>=0 && ctx.native_resolved_dispatch && recv.kind==GdVal::Kind::Obj && recv.obj) {
        const NativeMethodRow* row=recv.obj->native_call_row_;
        // Audit before reading the row, just like the original dispatcher.
        if(row && (!ctx.native_resolved_audit || native_resolved_row_matches(recv.obj,row))) {
            const auto function=row->methods[slot];
            if(function) {
                if(ctx.native_resolved_collect) {++ctx.native_resolved_counts[0];if(slot>=112)native_inline_hot_slot_hit(0);}
                return function(recv.obj,args,argc);
            }
        }
    }
    if(ctx.native_resolved_dispatch) {
        if(recv.kind==GdVal::Kind::Arr) {
            GdArr* a=recv.arr;
            if(!a)return GdVal::null();
            switch(method) {
                case SYM_size:
                    if(ctx.native_resolved_collect)native_inline_variant_hit(0);
                    return GdVal::from_int(a->len);
                case SYM_empty:
                    if(ctx.native_resolved_collect)native_inline_variant_hit(1);
                    return GdVal::from_bool(a->len == 0);
                case SYM_has:
                    if(ctx.native_resolved_collect)native_inline_variant_hit(2);
                    return GdVal::from_bool(argc >= 1 && a->has_val(args[0]));
                case SYM_front:
                    if(ctx.native_resolved_collect)native_inline_variant_hit(3);
                    return a->len > 0 ? a->data[0] : GdVal::null();
                case SYM_back:
                    if(ctx.native_resolved_collect)native_inline_variant_hit(4);
                    return a->len > 0 ? a->data[a->len - 1] : GdVal::null();
                default:break;
            }
        } else if(recv.kind==GdVal::Kind::Dict) {
            GdDict* d=recv.dict;
            if(!d)return GdVal::null();
            switch(method) {
                case SYM_size:
                    if(ctx.native_resolved_collect)native_inline_variant_hit(5);
                    return GdVal::from_int(d->len);
                case SYM_empty:
                    if(ctx.native_resolved_collect)native_inline_variant_hit(6);
                    return GdVal::from_bool(d->len == 0);
                case SYM_has:
                    if(ctx.native_resolved_collect)native_inline_variant_hit(7);
                    return GdVal::from_bool(argc >= 1 && d->has(args[0]));
                case SYM_get:
                    if(ctx.native_resolved_collect)native_inline_variant_hit(8);
                    return argc >= 1 ? d->get(args[0], argc >= 2 ? args[1] : GdVal::null()) : GdVal::null();
                default:break;
            }
        } else if(recv.kind==GdVal::Kind::ClassRef && method!=SYM_new) {
            if(ctx.native_resolved_collect)native_inline_variant_hit(9);
            if(recv.cls && recv.cls->call_static_fn) {
                GdVal out=GdVal::null();
                if(recv.cls->call_static_fn(ctx,method,args,argc,out))return out;
            }
            // A false callback is already executed; the original returns Null.
            return GdVal::null();
        }
    }
    // No virtual/user call has happened yet; fallback performs it exactly once.
    return gd::call_method(ctx,recv,method,args,argc);
}

void native_frame_segment_hit(unsigned);
struct NativeFrameSegmentSnapshot {
    const Gd__gd_core__CoreCharacter* stun_character=nullptr;
    const Gd__gd_core__CoreCharacter* speed_character=nullptr;
    bool stunned_value=false;
    double speed_value=0.0;
    void clear() {stun_character=nullptr;speed_character=nullptr;}
    bool stunned(const Gd__gd_core__CoreCharacter* character,bool collect) {
        if(stun_character!=character) {
            stunned_value=character->f_stunnedDuration.as_float()>0.0;
            stun_character=character;
            if(collect)native_frame_segment_hit(1);
        } else if(collect)native_frame_segment_hit(2);
        return stunned_value;
    }
    template<class Compute> double speed_increment(
            const Gd__gd_core__CoreCharacter* character,bool collect,Compute compute) {
        if(speed_character!=character) {
            speed_value=compute();speed_character=character;
            if(collect)native_frame_segment_hit(3);
        } else if(collect)native_frame_segment_hit(4);
        return speed_value;
    }
};
inline void native_frame_segment_hit_if(bool collect,unsigned index) {
    if(collect)native_frame_segment_hit(index);
}
inline void native_frame_segment_tick(Gd__gd_core__CoreItem* item,
        NativeFrameSegmentSnapshot& snapshot,const GdVal& delta_value) {

    const auto* row=item->native_call_row_;
    auto* battle=item->rt_ctx_;
    const bool collect=battle && battle->native_resolved_collect;
    if(!battle || !battle->native_resolved_dispatch || !row ||
       (battle->native_resolved_audit && !native_resolved_row_matches(item,row)) || !row->metadata) {
        snapshot.clear();native_frame_segment_hit_if(collect,5);
        item->fn_physicsTick(&delta_value,1);return;
    }
    native_frame_segment_hit_if(collect,0);

    if (!([&] { const auto& active = item->f__cooldown_active; if (active.kind == gd::GdVal::Kind::Bool) [[likely]] return active.b; return gd::gd_truth(active); }())) return;
    auto& context = *static_cast<Gd__gd_core__CoreContext*>(item->f_ctx.obj);
    const auto blocked = item->f__cooldown_blocked_epoch.as_int();
    if (blocked >= 0 && blocked == context.f_timer_pass_epoch.as_int()) return;

    const auto receiver = gd::native_inline_self_type(item->rt_ctx_,item,&META_Gd__gd_core_items__Gems__Gem)
        ? (snapshot.clear(), native_frame_segment_hit_if(collect,6), static_cast<Gd__gd_core_items__Gems__Gem*>(item)->fn_character(nullptr, 0))
        : item->f_character_;
    const auto* character = receiver.kind == gd::GdVal::Kind::Obj
        ? static_cast<const Gd__gd_core__CoreCharacter*>(receiver.obj) : nullptr;
    if (character && snapshot.stunned(character,collect)) return;

    const auto* display = item->f_statDisplayOverrides.arr;
    const auto override = display && display->len > 3 ? display->data[3] : gd::GdVal::null();
    double speed = 1.0;
    const bool uses_override = !override.is_null() && gd::gd_truth(override);
    if (uses_override) {
        speed = override.as_float();
    } else if (gd::gd_truth(item->f_placed) && !item->f_character_.is_null()) {
        if (character) {
            const auto* buffs = character->f_buffs.dict;
            const auto stacks = [&](int64_t type) {
                const auto slot = static_cast<uint32_t>(type - 100);
                const auto* entries = buffs->entries;
                if (slot < buffs->len && entries[slot].key.i == type)
                    return static_cast<const Gd__gd_core__CoreBuff*>(entries[slot].val.obj)->f_current.as_int();
                const auto stack = buffs->get(gd::GdVal::from_int(type));
                return stack.kind == gd::GdVal::Kind::Obj && stack.obj
                    ? static_cast<const Gd__gd_core__CoreBuff*>(stack.obj)->f_current.as_int() : int64_t{0};
            };
            const auto bonus = item->f_speedScale.as_float() + snapshot.speed_increment(character,collect,[&] {return static_cast<double>(stacks(107) - stacks(110)) * 0.02;});
            const auto modified = bonus >= 0.0 ? 1.0 + bonus : 1.0 / (1.0 - bonus);
            speed = modified < 0.1 ? 0.1 : (modified > 10.0 ? 10.0 : modified);
        } else {
            snapshot.clear(); speed = item->fn_getSpeed(nullptr, 0).as_float();
        }
    }

    const auto delta = delta_value.as_float();
    const auto left = uses_override && !override.is_num() ? 0.0 : item->f_triggerTime.as_float() - delta * speed;
    item->f_triggerTime = gd::GdVal::from_float(left);
    auto& gd_ctx = *item->rt_ctx_;
    if (gd::gd_truth(context.f_show_cooldown_progress)) {
        const gd::GdVal progress[] = {gd::GdVal::from_obj(item), gd::GdVal::from_float(1.0 - left / item->f_iterationCooldown.as_float())};
        snapshot.clear(); native_frame_segment_hit_if(collect,7);
        gd::native_inline_call(gd_ctx, context.f_hooks, SYM_GEN_showCooldown_794, progress, 2);
    }
    if (item->f_triggerTime.as_float() <= 0.0) { snapshot.clear(); native_frame_segment_hit_if(collect,8); gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(item), SYM_GEN_trigger_143, nullptr, 0); }
    return;
}

} // namespace gd
