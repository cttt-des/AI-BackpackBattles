#pragma once
#include "gd_rt.hpp"
#include "gen/sym_ids.hpp"
#include "gen/class_metas.hpp"
#include <array>
#include <cstddef>
#include <bit>
#include <limits>
#include "gen/hdrs/Gd__gd_core__Card.hpp"
#include "gen/hdrs/Gd__gd_core__CoreBuff.hpp"
#include "gen/hdrs/Gd__gd_core__CoreBuff__INNER__TemporaryStacks.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCombat.hpp"
#include "gen/hdrs/Gd__gd_core__CoreContext.hpp"
#include "gen/hdrs/Gd__gd_core__CoreContext__INNER__NativeFlicker.hpp"
#include "gen/hdrs/Gd__gd_core__CoreDamageResult.hpp"
#include "gen/hdrs/Gd__gd_core__CoreDamageSource.hpp"
#include "gen/hdrs/Gd__gd_core__CoreEvent.hpp"
#include "gen/hdrs/Gd__gd_core__CoreGrid.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItemData.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem__INNER__CoreElectricalCharge.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem__INNER__CoreSignalConnection.hpp"
#include "gen/hdrs/Gd__gd_core__CoreRng.hpp"
#include "gen/hdrs/Gd__gd_core__CoreTimer.hpp"
#include "gen/hdrs/Gd__gd_core__CoreUtil.hpp"
#include "gen/hdrs/Gd__gd_core__DeckofCards.hpp"
#include "gen/hdrs/Gd__gd_core__Item.hpp"
#include "gen/hdrs/Gd__gd_core__Item__INNER__SignalConnection.hpp"
#include "gen/hdrs/Gd__gd_core__ManaOrb.hpp"
#include "gen/hdrs/Gd__gd_core_items__Card.hpp"
#include "gen/hdrs/Gd__gd_core_items__DeckofCards.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Chess__BlackKing.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Chess__BlackQueen.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Chess__ChessPiece.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Chess__WhiteKing.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__DeathLotus.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__EnchantedWeapons.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__HeartoftheCards.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__MagicRing.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__NullBlade.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__PrismaticWand.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__RainbowOrb.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Sloth.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Ukulele.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Wand.hpp"
#include "gen/hdrs/Gd__gd_core_items__Item.hpp"
#include "gen/hdrs/Gd__gd_core_items__Item__INNER__SignalConnection.hpp"
#include "gen/hdrs/Gd__gd_core_items__ManaOrb.hpp"
namespace gd {
using NativeResolvedFn = GdVal (*)(GdObj*, const GdVal*, int);
using NativePropertyFn = GdVal (*)(const GdObj*);
struct alignas(64) NativePropertyRow {
    std::array<uint8_t,64> property_tags;
    std::array<uint8_t,4> method_tags;
    const NativePropertyFn* getters;
};
static_assert(alignof(NativePropertyRow)==64 && sizeof(NativePropertyRow)==128);
static_assert(offsetof(NativePropertyRow,property_tags)==0);
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
void native_inline_typed_read_hit(unsigned);

// These wrappers live in the existing non-LTO sym_ids compilation unit. In
// particular, exceptional floating values retain the original evaluator.
GdVal native_numeric_original_add(BattleCtx&,const GdVal&,const GdVal&);
GdVal native_numeric_original_sub(const GdVal&,const GdVal&);
GdVal native_numeric_original_mul(const GdVal&,const GdVal&);
GdVal native_numeric_original_div(BattleCtx&,const GdVal&,const GdVal&);
void native_numeric_math_hit(unsigned);

#if defined(_MSC_VER)
__forceinline
#elif defined(__GNUC__)
__attribute__((always_inline)) inline
#else
inline
#endif
bool native_numeric_is_finite(const GdVal& value) {
    return value.kind!=GdVal::Kind::Float ||
        (std::bit_cast<uint64_t>(value.f)&UINT64_C(0x7ff0000000000000))!=UINT64_C(0x7ff0000000000000);
}

#if defined(_MSC_VER)
__forceinline
#elif defined(__GNUC__)
__attribute__((always_inline)) inline
#else
inline
#endif
GdVal native_numeric_add(BattleCtx& ctx,const GdVal& a,const GdVal& b) {
    if(a.kind==GdVal::Kind::Int && b.kind==GdVal::Kind::Int) {
#if defined(__GNUC__) || defined(__clang__)
        int64_t result;
        if(!__builtin_add_overflow(a.i,b.i,&result)) {
            if(ctx.native_resolved_collect)native_numeric_math_hit(0); return GdVal::from_int(result);
        }
#endif
    } else if(a.is_num() && b.is_num() && native_numeric_is_finite(a) && native_numeric_is_finite(b)) {
        if(ctx.native_resolved_collect)native_numeric_math_hit(1); return GdVal::from_float(a.as_float()+b.as_float());
    }
    if(ctx.native_resolved_collect)native_numeric_math_hit(2);
    return native_numeric_original_add(ctx,a,b);
}

#if defined(_MSC_VER)
__forceinline
#elif defined(__GNUC__)
__attribute__((always_inline)) inline
#else
inline
#endif
GdVal native_numeric_sub(const GdVal& a,const GdVal& b) {
    if(a.kind==GdVal::Kind::Int && b.kind==GdVal::Kind::Int) {
#if defined(__GNUC__) || defined(__clang__)
        int64_t result;
        if(!__builtin_sub_overflow(a.i,b.i,&result)) {
             return GdVal::from_int(result);
        }
#endif
    } else if(a.is_num() && b.is_num() && native_numeric_is_finite(a) && native_numeric_is_finite(b)) {
         return GdVal::from_float(a.as_float()-b.as_float());
    }
    
    return native_numeric_original_sub(a,b);
}

#if defined(_MSC_VER)
__forceinline
#elif defined(__GNUC__)
__attribute__((always_inline)) inline
#else
inline
#endif
GdVal native_numeric_mul(const GdVal& a,const GdVal& b) {
    if(a.kind==GdVal::Kind::Int && b.kind==GdVal::Kind::Int) {
#if defined(__GNUC__) || defined(__clang__)
        int64_t result;
        if(!__builtin_mul_overflow(a.i,b.i,&result)) {
             return GdVal::from_int(result);
        }
#endif
    } else if(a.is_num() && b.is_num() && native_numeric_is_finite(a) && native_numeric_is_finite(b)) {
         return GdVal::from_float(a.as_float()*b.as_float());
    }
    
    return native_numeric_original_mul(a,b);
}

#if defined(_MSC_VER)
__forceinline
#elif defined(__GNUC__)
__attribute__((always_inline)) inline
#else
inline
#endif
GdVal native_numeric_div(BattleCtx& ctx,const GdVal& a,const GdVal& b) {
    if(a.kind==GdVal::Kind::Int && b.kind==GdVal::Kind::Int) {
        if(b.i==0) { if(ctx.native_resolved_collect)native_numeric_math_hit(3); return GdVal::from_int(0); }
        if(!(a.i==std::numeric_limits<int64_t>::min() && b.i==-1)) {
            if(ctx.native_resolved_collect)native_numeric_math_hit(3); return GdVal::from_int(a.i/b.i);
        }
    } else if(a.is_num() && b.is_num() && native_numeric_is_finite(a) && native_numeric_is_finite(b)) {
        const double divisor=b.as_float();
        if((std::bit_cast<uint64_t>(divisor)&UINT64_C(0x7fffffffffffffff))!=0) {
            if(ctx.native_resolved_collect)native_numeric_math_hit(4); return GdVal::from_float(a.as_float()/divisor);
        }
    }
    if(ctx.native_resolved_collect)native_numeric_math_hit(5);
    return native_numeric_original_div(ctx,a,b);
}

#if defined(_MSC_VER)
__forceinline
#elif defined(__GNUC__)
__attribute__((always_inline)) inline
#else
inline
#endif
bool native_direct_property_field(const NativePropertyRow* row,const GdObj* object,SymId symbol,GdVal& out) {
    switch(symbol) {
        case SYM_GEN_rng_1406:
            switch(row->property_tags[0]) {
                case 1: out=static_cast<const Gd__gd_core__CoreContext*>(object)->f_rng;return true;
                case 2: out=static_cast<const Gd__gd_core__CoreRng*>(object)->f_rng;return true;
                case 3: out=static_cast<const Gd__gd_core__CoreUtil*>(object)->f_rng;return true;
                default:return false;
            }
        case SYM_GEN_item_book_1421:
            switch(row->property_tags[1]) {
                case 1: out=static_cast<const Gd__gd_core__CoreContext*>(object)->f_item_book;return true;
                default:return false;
            }
        case SYM_GEN_util_1407:
            switch(row->property_tags[2]) {
                case 1: out=static_cast<const Gd__gd_core__CoreContext*>(object)->f_util;return true;
                default:return false;
            }
        case SYM_GEN_combat_log_1410:
            switch(row->property_tags[3]) {
                case 1: out=static_cast<const Gd__gd_core__CoreContext*>(object)->f_combat_log;return true;
                default:return false;
            }
        case SYM_GEN_bus_1408:
            switch(row->property_tags[4]) {
                case 1: out=static_cast<const Gd__gd_core__CoreContext*>(object)->f_bus;return true;
                default:return false;
            }
        case SYM_GEN_event_1517:
            switch(row->property_tags[5]) {
                case 1: out=static_cast<const Gd__gd_core__CoreDamageResult*>(object)->f_event;return true;
                default:return false;
            }
        case SYM_GEN_hooks_1409:
            switch(row->property_tags[6]) {
                case 1: out=static_cast<const Gd__gd_core__CoreContext*>(object)->f_hooks;return true;
                default:return false;
            }
        case SYM_GEN_damage_1518:
            switch(row->property_tags[7]) {
                case 1: out=static_cast<const Gd__gd_core__CoreDamageResult*>(object)->f_damage;return true;
                default:return false;
            }
        case SYM_GEN_descriptor_2:
            switch(row->property_tags[8]) {
                case 1: out=static_cast<const Gd__gd_core__CoreItem*>(object)->f_descriptor;return true;
                default:return false;
            }
        case SYM_GEN_identifier_1673:
            switch(row->property_tags[9]) {
                case 1: out=static_cast<const Gd__gd_core__CoreItemData*>(object)->f_identifier;return true;
                default:return false;
            }
        case SYM_GEN_damageSource_24:
            switch(row->property_tags[10]) {
                case 1: out=static_cast<const Gd__gd_core__CoreDamageResult*>(object)->f_damageSource;return true;
                case 2: out=static_cast<const Gd__gd_core__CoreItem*>(object)->f_damageSource;return true;
                default:return false;
            }
        case SYM_GEN_playerId_1046:
            switch(row->property_tags[11]) {
                case 1: out=static_cast<const Gd__gd_core__CoreCharacter*>(object)->f_playerId;return true;
                default:return false;
            }
        case SYM_GEN_time_1411:
            switch(row->property_tags[12]) {
                case 1: out=static_cast<const Gd__gd_core__CoreContext*>(object)->f_time;return true;
                default:return false;
            }
        case SYM_GEN_origin_1546:
            switch(row->property_tags[13]) {
                case 1: out=static_cast<const Gd__gd_core__CoreDamageSource*>(object)->f_origin;return true;
                case 2: out=static_cast<const Gd__gd_core__CoreEvent*>(object)->f_origin;return true;
                default:return false;
            }
        case SYM_GEN_player_1302:
            switch(row->property_tags[14]) {
                case 1: out=static_cast<const Gd__gd_core__CoreCombat*>(object)->f_player;return true;
                case 2: out=static_cast<const Gd__gd_core__CoreContext*>(object)->f_player;return true;
                default:return false;
            }
        case SYM_GEN_minDam_1675:
            switch(row->property_tags[15]) {
                case 1: out=static_cast<const Gd__gd_core__CoreItemData*>(object)->f_minDam;return true;
                default:return false;
            }
        case SYM_GEN_curChargedItem_1648:
            switch(row->property_tags[16]) {
                case 1: out=static_cast<const Gd__gd_core__CoreItem__INNER__CoreElectricalCharge*>(object)->f_curChargedItem;return true;
                default:return false;
            }
        case SYM_GEN_occupiedCells_52:
            switch(row->property_tags[17]) {
                case 1: out=static_cast<const Gd__gd_core__CoreItem*>(object)->f_occupiedCells;return true;
                default:return false;
            }
        case SYM_GEN_ownerType_49:
            switch(row->property_tags[18]) {
                case 1: out=static_cast<const Gd__gd_core__CoreItem*>(object)->f_ownerType;return true;
                default:return false;
            }
        case SYM_GEN_oracle_trace_1729:
            switch(row->property_tags[19]) {
                case 1: out=static_cast<const Gd__gd_core__CoreRng*>(object)->f_oracle_trace;return true;
                default:return false;
            }
        case SYM_GEN_timer_pass_epoch_1445:
            switch(row->property_tags[20]) {
                case 1: out=static_cast<const Gd__gd_core__CoreContext*>(object)->f_timer_pass_epoch;return true;
                default:return false;
            }
        case SYM_GEN_inventory_5:
            switch(row->property_tags[21]) {
                case 1: out=static_cast<const Gd__gd_core__CoreCharacter*>(object)->f_inventory;return true;
                case 2: out=static_cast<const Gd__gd_core__CoreItem*>(object)->f_inventory;return true;
                default:return false;
            }
        case SYM_GEN__stacktrace_1731:
            switch(row->property_tags[22]) {
                case 1: out=static_cast<const Gd__gd_core__CoreRng*>(object)->f__stacktrace;return true;
                default:return false;
            }
        case SYM_GEN_opponent_75:
            switch(row->property_tags[23]) {
                case 1: out=static_cast<const Gd__gd_core__CoreCharacter*>(object)->f_opponent;return true;
                case 2: out=static_cast<const Gd__gd_core__CoreCombat*>(object)->f_opponent;return true;
                case 3: out=static_cast<const Gd__gd_core__CoreContext*>(object)->f_opponent;return true;
                default:return false;
            }
        case SYM_GEN_amount_1041:
            switch(row->property_tags[24]) {
                case 1: out=static_cast<const Gd__gd_core__CoreBuff__INNER__TemporaryStacks*>(object)->f_amount;return true;
                default:return false;
            }
        case SYM_GEN_types_1544:
            switch(row->property_tags[25]) {
                case 1: out=static_cast<const Gd__gd_core__CoreDamageSource*>(object)->f_types;return true;
                case 2: out=static_cast<const Gd__gd_core__CoreItemData*>(object)->f_types;return true;
                default:return false;
            }
        case SYM_GEN_lastChargedItem_1647:
            switch(row->property_tags[26]) {
                case 1: out=static_cast<const Gd__gd_core__CoreItem__INNER__CoreElectricalCharge*>(object)->f_lastChargedItem;return true;
                default:return false;
            }
        case SYM_GEN_timeout_1042:
            switch(row->property_tags[27]) {
                case 1: out=static_cast<const Gd__gd_core__CoreBuff__INNER__TemporaryStacks*>(object)->f_timeout;return true;
                default:return false;
            }
        case SYM_GEN_combat_1420:
            switch(row->property_tags[28]) {
                case 1: out=static_cast<const Gd__gd_core__CoreContext*>(object)->f_combat;return true;
                default:return false;
            }
        case SYM_GEN_INVENTORY_1093:
            switch(row->property_tags[29]) {
                case 1: out=static_cast<const Gd__gd_core__CoreCharacter*>(object)->f_INVENTORY;return true;
                default:return false;
            }
        case SYM_GEN_name_7:
            switch(row->property_tags[30]) {
                case 1: out=static_cast<const Gd__gd_core__CoreItem*>(object)->f_name;return true;
                case 2: out=static_cast<const Gd__gd_core__CoreItemData*>(object)->f_name;return true;
                case 3: out=static_cast<const Gd__gd_core__CoreTimer*>(object)->f_name;return true;
                default:return false;
            }
        case SYM_GEN_cd_1679:
            switch(row->property_tags[31]) {
                case 1: out=static_cast<const Gd__gd_core__CoreItemData*>(object)->f_cd;return true;
                default:return false;
            }
        case SYM_GEN_buffs_1048:
            switch(row->property_tags[32]) {
                case 1: out=static_cast<const Gd__gd_core__CoreCharacter*>(object)->f_buffs;return true;
                case 2: out=static_cast<const Gd__gd_core__ManaOrb*>(object)->f_buffs;return true;
                case 3: out=static_cast<const Gd__gd_core_items__Exclusive__Chess__BlackKing*>(object)->f_buffs;return true;
                case 4: out=static_cast<const Gd__gd_core_items__Exclusive__Chess__BlackQueen*>(object)->f_buffs;return true;
                case 5: out=static_cast<const Gd__gd_core_items__Exclusive__Chess__WhiteKing*>(object)->f_buffs;return true;
                case 6: out=static_cast<const Gd__gd_core_items__Exclusive__DeathLotus*>(object)->f_buffs;return true;
                case 7: out=static_cast<const Gd__gd_core_items__Exclusive__EnchantedWeapons*>(object)->f_buffs;return true;
                case 8: out=static_cast<const Gd__gd_core_items__Exclusive__NullBlade*>(object)->f_buffs;return true;
                case 9: out=static_cast<const Gd__gd_core_items__Exclusive__PrismaticWand*>(object)->f_buffs;return true;
                case 10: out=static_cast<const Gd__gd_core_items__Exclusive__RainbowOrb*>(object)->f_buffs;return true;
                case 11: out=static_cast<const Gd__gd_core_items__Exclusive__Sloth*>(object)->f_buffs;return true;
                case 12: out=static_cast<const Gd__gd_core_items__Exclusive__Ukulele*>(object)->f_buffs;return true;
                case 13: out=static_cast<const Gd__gd_core_items__Exclusive__Wand*>(object)->f_buffs;return true;
                case 14: out=static_cast<const Gd__gd_core_items__ManaOrb*>(object)->f_buffs;return true;
                default:return false;
            }
        case SYM_GEN_frame_counter_1413:
            switch(row->property_tags[33]) {
                case 1: out=static_cast<const Gd__gd_core__CoreContext*>(object)->f_frame_counter;return true;
                default:return false;
            }
        case SYM_GEN_shopChance_1683:
            switch(row->property_tags[34]) {
                case 1: out=static_cast<const Gd__gd_core__CoreItemData*>(object)->f_shopChance;return true;
                default:return false;
            }
        case SYM_GEN_cube_advanced_1426:
            switch(row->property_tags[35]) {
                case 1: out=static_cast<const Gd__gd_core__CoreContext*>(object)->f_cube_advanced;return true;
                default:return false;
            }
        case SYM_GEN_signalName_1013:
            switch(row->property_tags[36]) {
                case 1: out=static_cast<const Gd__gd_core__CoreBuff*>(object)->f_signalName;return true;
                case 2: out=static_cast<const Gd__gd_core__CoreItem__INNER__CoreSignalConnection*>(object)->f_signalName;return true;
                case 3: out=static_cast<const Gd__gd_core__Item__INNER__SignalConnection*>(object)->f_signalName;return true;
                case 4: out=static_cast<const Gd__gd_core_items__Item__INNER__SignalConnection*>(object)->f_signalName;return true;
                default:return false;
            }
        case SYM_GEN_type_1005:
            switch(row->property_tags[37]) {
                case 1: out=static_cast<const Gd__gd_core__CoreBuff*>(object)->f_type;return true;
                case 2: out=static_cast<const Gd__gd_core__CoreEvent*>(object)->f_type;return true;
                default:return false;
            }
        case SYM_GEN_placedByPlayer_50:
            switch(row->property_tags[38]) {
                case 1: out=static_cast<const Gd__gd_core__CoreItem*>(object)->f_placedByPlayer;return true;
                default:return false;
            }
        case SYM_GEN_placed_6:
            switch(row->property_tags[39]) {
                case 1: out=static_cast<const Gd__gd_core__CoreItem*>(object)->f_placed;return true;
                default:return false;
            }
        case SYM_GEN_chainPosition_882:
            switch(row->property_tags[40]) {
                case 1: out=static_cast<const Gd__gd_core__Card*>(object)->f_chainPosition;return true;
                case 2: out=static_cast<const Gd__gd_core_items__Card*>(object)->f_chainPosition;return true;
                case 3: out=static_cast<const Gd__gd_core_items__Exclusive__HeartoftheCards*>(object)->f_chainPosition;return true;
                default:return false;
            }
        case SYM_GEN_cards_1832:
            switch(row->property_tags[41]) {
                case 1: out=static_cast<const Gd__gd_core__DeckofCards*>(object)->f_cards;return true;
                case 2: out=static_cast<const Gd__gd_core_items__DeckofCards*>(object)->f_cards;return true;
                default:return false;
            }
        case SYM_GEN_pieceColor_2135:
            switch(row->property_tags[42]) {
                case 1: out=static_cast<const Gd__gd_core_items__Exclusive__Chess__ChessPiece*>(object)->f_pieceColor;return true;
                default:return false;
            }
        case SYM_GEN_items_1092:
            switch(row->property_tags[43]) {
                case 1: out=static_cast<const Gd__gd_core__CoreCharacter*>(object)->f_items;return true;
                case 2: out=static_cast<const Gd__gd_core__CoreGrid*>(object)->f_items;return true;
                default:return false;
            }
        case SYM_GEN_rope_speedups_1425:
            switch(row->property_tags[44]) {
                case 1: out=static_cast<const Gd__gd_core__CoreContext*>(object)->f_rope_speedups;return true;
                default:return false;
            }
        case SYM_GEN_baseStaminaRegen_1057:
            switch(row->property_tags[45]) {
                case 1: out=static_cast<const Gd__gd_core__CoreCharacter*>(object)->f_baseStaminaRegen;return true;
                default:return false;
            }
        case SYM_GEN_stackType_2388:
            switch(row->property_tags[46]) {
                case 1: out=static_cast<const Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect*>(object)->f_stackType;return true;
                default:return false;
            }
        case SYM_GEN_animationScene_1695:
            switch(row->property_tags[47]) {
                case 1: out=static_cast<const Gd__gd_core__CoreItemData*>(object)->f_animationScene;return true;
                default:return false;
            }
        case SYM_GEN_nextCell_1652:
            switch(row->property_tags[48]) {
                case 1: out=static_cast<const Gd__gd_core__CoreItem__INNER__CoreElectricalCharge*>(object)->f_nextCell;return true;
                default:return false;
            }
        case SYM_GEN_in_physics_timer_pass_1446:
            switch(row->property_tags[49]) {
                case 1: out=static_cast<const Gd__gd_core__CoreContext*>(object)->f_in_physics_timer_pass;return true;
                default:return false;
            }
        case SYM_GEN_activationAni_1717:
            switch(row->property_tags[50]) {
                case 1: out=static_cast<const Gd__gd_core__CoreItemData*>(object)->f_activationAni;return true;
                default:return false;
            }
        case SYM_GEN_curRecipe_577:
            switch(row->property_tags[51]) {
                case 1: out=static_cast<const Gd__gd_core__Item*>(object)->f_curRecipe;return true;
                case 2: out=static_cast<const Gd__gd_core_items__Item*>(object)->f_curRecipe;return true;
                default:return false;
            }
        case SYM_GEN_healthDamage_1519:
            switch(row->property_tags[52]) {
                case 1: out=static_cast<const Gd__gd_core__CoreDamageResult*>(object)->f_healthDamage;return true;
                default:return false;
            }
        case SYM_GEN_fatigueDamageSource_1430:
            switch(row->property_tags[53]) {
                case 1: out=static_cast<const Gd__gd_core__CoreContext*>(object)->f_fatigueDamageSource;return true;
                default:return false;
            }
        case SYM_GEN_gainedStacks_1714:
            switch(row->property_tags[54]) {
                case 1: out=static_cast<const Gd__gd_core__CoreItemData*>(object)->f_gainedStacks;return true;
                case 2: out=static_cast<const Gd__gd_core_items__Exclusive__MagicRing*>(object)->f_gainedStacks;return true;
                default:return false;
            }
        case SYM_GEN_extraCds_1680:
            switch(row->property_tags[55]) {
                case 1: out=static_cast<const Gd__gd_core__CoreItemData*>(object)->f_extraCds;return true;
                default:return false;
            }
        case SYM_GEN_flickerMinDist_1697:
            switch(row->property_tags[56]) {
                case 1: out=static_cast<const Gd__gd_core__CoreItemData*>(object)->f_flickerMinDist;return true;
                default:return false;
            }
        case SYM_GEN_flickerMaxDist_1698:
            switch(row->property_tags[57]) {
                case 1: out=static_cast<const Gd__gd_core__CoreItemData*>(object)->f_flickerMaxDist;return true;
                default:return false;
            }
        case SYM_GEN_flickerMinSpeed_1699:
            switch(row->property_tags[58]) {
                case 1: out=static_cast<const Gd__gd_core__CoreItemData*>(object)->f_flickerMinSpeed;return true;
                default:return false;
            }
        case SYM_GEN_flickerMaxSpeed_1700:
            switch(row->property_tags[59]) {
                case 1: out=static_cast<const Gd__gd_core__CoreItemData*>(object)->f_flickerMaxSpeed;return true;
                default:return false;
            }
        case SYM_GEN_fight_ended_1305:
            switch(row->property_tags[60]) {
                case 1: out=static_cast<const Gd__gd_core__CoreCombat*>(object)->f_fight_ended;return true;
                case 2: out=static_cast<const Gd__gd_core__CoreContext*>(object)->f_fight_ended;return true;
                default:return false;
            }
        case SYM_GEN_accuracy_1545:
            switch(row->property_tags[61]) {
                case 1: out=static_cast<const Gd__gd_core__CoreDamageSource*>(object)->f_accuracy;return true;
                case 2: out=static_cast<const Gd__gd_core__CoreItemData*>(object)->f_accuracy;return true;
                default:return false;
            }
        case SYM_GEN_params_1570:
            switch(row->property_tags[62]) {
                case 1: out=static_cast<const Gd__gd_core__CoreEvent*>(object)->f_params;return true;
                case 2: out=static_cast<const Gd__gd_core__CoreItemData*>(object)->f_params;return true;
                default:return false;
            }
        case SYM_GEN_ctx_3:
            switch(row->property_tags[63]) {
                case 1: out=static_cast<const Gd__gd_core__CoreBuff*>(object)->f_ctx;return true;
                case 2: out=static_cast<const Gd__gd_core__CoreCharacter*>(object)->f_ctx;return true;
                case 3: out=static_cast<const Gd__gd_core__CoreCombat*>(object)->f_ctx;return true;
                case 4: out=static_cast<const Gd__gd_core__CoreContext__INNER__NativeFlicker*>(object)->f_ctx;return true;
                case 5: out=static_cast<const Gd__gd_core__CoreItem*>(object)->f_ctx;return true;
                default:return false;
            }
        default:return false;
    }
}
#if defined(_MSC_VER)
__forceinline
#elif defined(__GNUC__)
__attribute__((always_inline)) inline
#else
inline
#endif
bool native_direct_method_field(const NativePropertyRow* row,const GdObj* object,SymId symbol,GdVal& out) {
    switch(symbol) {
        case SYM_GEN_character_74:
            switch(row->method_tags[0]) {
                case 1: out=static_cast<const Gd__gd_core__CoreItem*>(object)->f_character_;return true;
                default:return false;
            }
        case SYM_GEN_hasHit_1523:
            switch(row->method_tags[1]) {
                case 1: out=static_cast<const Gd__gd_core__CoreDamageResult*>(object)->f_hit;return true;
                default:return false;
            }
        case SYM_GEN_getStacks_1023:
            switch(row->method_tags[2]) {
                case 1: out=static_cast<const Gd__gd_core__CoreBuff*>(object)->f_current;return true;
                default:return false;
            }
        case SYM_GEN_speed_93:
            switch(row->method_tags[3]) {
                case 1: out=static_cast<const Gd__gd_core__CoreItem*>(object)->f_speedScale;return true;
                default:return false;
            }
        default:return false;
    }
}

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
            GdVal direct_out;
            if(row->properties && native_direct_property_field(row->properties,recv.obj,prop,direct_out)) {
                if(ctx.native_resolved_collect) {
                    native_inline_property_hit(0);if(slot>=32)native_inline_hot_slot_hit(1);
                    native_inline_typed_read_hit(0);
                }
                return direct_out;
            }
            const auto function=row->properties ? row->properties->getters[slot] : nullptr;
            if(function) {
                if(ctx.native_resolved_collect) {native_inline_property_hit(0);if(slot>=32)native_inline_hot_slot_hit(1);}
                return function(recv.obj);
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
            GdVal direct_out;
            if(row->properties && native_direct_method_field(row->properties,recv.obj,method,direct_out)) {
                if(ctx.native_resolved_collect) {
                    ++ctx.native_resolved_counts[0];if(slot>=112)native_inline_hot_slot_hit(0);
                    native_inline_typed_read_hit(1);
                }
                return direct_out;
            }
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
} // namespace gd
