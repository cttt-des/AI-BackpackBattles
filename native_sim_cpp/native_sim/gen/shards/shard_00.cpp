#pragma STDC FP_CONTRACT OFF

#include "../hdrs/Gd__gd_core__CoreItem.hpp"
#include "../hdrs/Gd__gd_core__BloodGoobert.hpp"
#include "../hdrs/Gd__gd_core__CoreBuff.hpp"
#include "../hdrs/Gd__gd_core__CoreItemBook.hpp"
#include "../hdrs/Gd__gd_core__DarkestLotus.hpp"
#include "../hdrs/Gd__gd_core__Flute.hpp"
#include "../hdrs/Gd__gd_core__HolySpear.hpp"
#include "../hdrs/Gd__gd_core__ManaPotion.hpp"
#include "../hdrs/Gd__gd_core__PoisonIvy.hpp"
#include "../hdrs/Gd__gd_core__SpikedShield.hpp"
#include "../hdrs/Gd__gd_core__StrongStoneSkinPotion.hpp"
#include "../hdrs/Gd__gd_core__YggdrasilLeaf.hpp"
#include "../hdrs/Gd__gd_core_items__BloodyDagger.hpp"
#include "../hdrs/Gd__gd_core_items__CursedDagger.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__AmuletUnidentified.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__PowerPuppy.hpp"
#include "../hdrs/Gd__gd_core_items__Greatsword.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Broccoli.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__CheeseGoobert.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ChiliGoobert.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__DarkLantern.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__DragonscaleArmor.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__EvilHat.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Toad.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__HawkRune.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__InvestmentOpportunity.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__LittleMimic.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__MechaBat.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__OnionCutter.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__PortableAltar.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__RainbowGoobertMage.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SapphireWhelp.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SliceofToast.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SpellScrollLight.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__StoneGloves.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__TigerRune.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__WandofDissonance.hpp"
#include "../hdrs/Gd__gd_core_items__Garlic.hpp"
#include "../hdrs/Gd__gd_core_items__HeroSword.hpp"
#include "../hdrs/Gd__gd_core_items__ManaPotion.hpp"
#include "../hdrs/Gd__gd_core_items__Pumpkin.hpp"
#include "../hdrs/Gd__gd_core_items__StrongHealthPotion.hpp"
#include "../hdrs/Gd__gd_core_items__YggdrasilLeaf.hpp"

void Gd__gd_core__CoreItem::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_descriptor = gd::GdVal::null();
    this->f_ctx = gd::GdVal::null();
    this->f_character_ = gd::GdVal::null();
    this->f_inventory = gd::GdVal::null();
    this->f_placed = gd::GdVal::from_bool(false);
    this->f_name = gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u));
    this->f_chargeFrame = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2(0.0, 0.0), gd::GdVal::from_vec2(0.0, 0.0), gd::GdVal::from_vec2(0.0, 0.0), gd::GdVal::from_vec2(0.0, 0.0)}));
    this->f_speedScale = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusMaxDam = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusMinDam = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_removableDam = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusDamageFactor = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_staminaFactor = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_critChancePercent = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_critTokens = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_critSeverity = gd::gd_coerce_float(Gd__gd_core__CoreItem::get_static_const_or_enum(gd_ctx, SYM_GEN_BASE_CRIT_SEVERITY_0));
    this->f_bonusChancePercent_mult = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusChancePercent_additive1 = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusChancePercent_additive2 = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusAccuracy = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_buffPowers = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_buffAmplificationChances = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_damageSource = gd::GdVal::null();
    this->f_doubleActivationChance = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_doubleAttackEffectChance = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_paramMult = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_paramAdd = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_numCharges = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_baseCooldownOverride = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_chanceRng = gd::GdVal::null();
    this->f_damageRangeRng = gd::GdVal::null();
    this->f_statDisplayOverrides = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_lastActivationTime = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_activationsThisFrame = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_lastTriggerTime = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_triggersThisFrame = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_triggerTime = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_iterationCooldown = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_flk_suppress_fire = gd::GdVal::from_bool(false);
    this->f__inj_item = gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u));
    this->f__inj_trigger_n = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f__inj_trigger_count = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_itemMetrics = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_gems = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f__grid = gd::GdVal::null();
    this->f__behavior = gd::GdVal::null();
    this->f__cooldown_active = gd::GdVal::from_bool(false);
    this->f_dynamicTypes = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_combatConnections = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_ownerType = gd::gd_coerce_int(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_Undefined_2539));
    this->f_placedByPlayer = gd::GdVal::from_bool(false);
    this->f_dragged = gd::GdVal::from_bool(false);
    this->f_occupiedCells = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_collisionCells = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_extensionCells = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_affectedExtensionCells = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_affectedCellsCache = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_currentAffectedItems = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_cachedAffectedItems = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_affectedTileCells = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_consumed = gd::GdVal::from_bool(false);
    this->f_hasPreDealDamageEarlyEffect = gd::GdVal::from_bool(false);
    this->f_hasPreDealDamageLateEffect = gd::GdVal::from_bool(false);
    this->f_hasDealtDamageEffect = gd::GdVal::from_bool(false);
    this->f_hasOnChargeReceivedEffect = gd::GdVal::from_bool(false);
    this->f_hasOnChargeLeftEffect = gd::GdVal::from_bool(false);
    this->f_timers = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_buffLabelPositionTimestamps = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_float(0.0), gd::GdVal::from_float(0.0), gd::GdVal::from_float(0.0), gd::GdVal::from_float(0.0), gd::GdVal::from_float(0.0)}));
    this->f_replacementPending = gd::GdVal::from_bool(false);
    this->f_faceDirection = gd::gd_coerce_int(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP));
    this->f_rotation = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
}
const gd::GdClassMeta* Gd__gd_core__CoreItem::meta() const { return &META_Gd__gd_core__CoreItem; }
gd::GdVal Gd__gd_core__CoreItem::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_BASE_CRIT_SEVERITY_0: return gd::GdVal::from_float(2.0);
        case SYM_GEN_cdEncodingFactor_1: return gd::GdVal::from_float(100000.0);
        case SYM_GEN_SELF_BEHAVIOR_METHODS_63: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onCombatStart", 13u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "getGatedDescriptor", 18u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "getReplaceDescriptor", 20u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onChargeReceived", 16u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onChargeLeft", 12u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "chargedItemStatChange", 21u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onPreDealDamage_early", 21u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onPreDealDamage_late", 20u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDealtDamage", 13u))}));
        case SYM_GEN_CoreElectricalCharge_507: return gd::GdVal::from_cls(&META_Gd__gd_core__CoreItem__INNER__CoreElectricalCharge);
        case SYM_GEN_CoreSignalConnection_508: return gd::GdVal::from_cls(&META_Gd__gd_core__CoreItem__INNER__CoreSignalConnection);
        default: break;
    }
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreItem::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreItem::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_descriptor_2: out = this->f_descriptor; return true;
        case SYM_GEN_ctx_3: out = this->f_ctx; return true;
        case SYM_GEN_character__4: out = this->f_character_; return true;
        case SYM_GEN_inventory_5: out = this->f_inventory; return true;
        case SYM_GEN_placed_6: out = this->f_placed; return true;
        case SYM_GEN_name_7: out = this->f_name; return true;
        case SYM_GEN_chargeFrame_8: out = this->f_chargeFrame; return true;
        case SYM_GEN_speedScale_9: out = this->f_speedScale; return true;
        case SYM_GEN_bonusMaxDam_10: out = this->f_bonusMaxDam; return true;
        case SYM_GEN_bonusMinDam_11: out = this->f_bonusMinDam; return true;
        case SYM_GEN_removableDam_12: out = this->f_removableDam; return true;
        case SYM_GEN_bonusDamageFactor_13: out = this->f_bonusDamageFactor; return true;
        case SYM_GEN_staminaFactor_14: out = this->f_staminaFactor; return true;
        case SYM_GEN_critChancePercent_15: out = this->f_critChancePercent; return true;
        case SYM_GEN_critTokens_16: out = this->f_critTokens; return true;
        case SYM_GEN_critSeverity_17: out = this->f_critSeverity; return true;
        case SYM_GEN_bonusChancePercent_mult_18: out = this->f_bonusChancePercent_mult; return true;
        case SYM_GEN_bonusChancePercent_additive1_19: out = this->f_bonusChancePercent_additive1; return true;
        case SYM_GEN_bonusChancePercent_additive2_20: out = this->f_bonusChancePercent_additive2; return true;
        case SYM_GEN_bonusAccuracy_21: out = this->f_bonusAccuracy; return true;
        case SYM_GEN_buffPowers_22: out = this->f_buffPowers; return true;
        case SYM_GEN_buffAmplificationChances_23: out = this->f_buffAmplificationChances; return true;
        case SYM_GEN_damageSource_24: out = this->f_damageSource; return true;
        case SYM_GEN_doubleActivationChance_25: out = this->f_doubleActivationChance; return true;
        case SYM_GEN_doubleAttackEffectChance_26: out = this->f_doubleAttackEffectChance; return true;
        case SYM_GEN_paramMult_27: out = this->f_paramMult; return true;
        case SYM_GEN_paramAdd_28: out = this->f_paramAdd; return true;
        case SYM_GEN_numCharges_29: out = this->f_numCharges; return true;
        case SYM_GEN_baseCooldownOverride_30: out = this->f_baseCooldownOverride; return true;
        case SYM_GEN_chanceRng_31: out = this->f_chanceRng; return true;
        case SYM_GEN_damageRangeRng_32: out = this->f_damageRangeRng; return true;
        case SYM_GEN_statDisplayOverrides_33: out = this->f_statDisplayOverrides; return true;
        case SYM_GEN_lastActivationTime_34: out = this->f_lastActivationTime; return true;
        case SYM_GEN_activationsThisFrame_35: out = this->f_activationsThisFrame; return true;
        case SYM_GEN_lastTriggerTime_36: out = this->f_lastTriggerTime; return true;
        case SYM_GEN_triggersThisFrame_37: out = this->f_triggersThisFrame; return true;
        case SYM_GEN_triggerTime_38: out = this->f_triggerTime; return true;
        case SYM_GEN_iterationCooldown_39: out = this->f_iterationCooldown; return true;
        case SYM_GEN_flk_suppress_fire_40: out = this->f_flk_suppress_fire; return true;
        case SYM_GEN__inj_item_41: out = this->f__inj_item; return true;
        case SYM_GEN__inj_trigger_n_42: out = this->f__inj_trigger_n; return true;
        case SYM_GEN__inj_trigger_count_43: out = this->f__inj_trigger_count; return true;
        case SYM_GEN_itemMetrics_44: out = this->f_itemMetrics; return true;
        case SYM_GEN_gems_45: out = this->f_gems; return true;
        case SYM_GEN__grid_46: out = this->f__grid; return true;
        case SYM_GEN__behavior_47: out = this->f__behavior; return true;
        case SYM_GEN__cooldown_active_48: out = this->f__cooldown_active; return true;
        case SYM_GEN_dynamicTypes_49: out = this->f_dynamicTypes; return true;
        case SYM_GEN_combatConnections_50: out = this->f_combatConnections; return true;
        case SYM_GEN_ownerType_51: out = this->f_ownerType; return true;
        case SYM_GEN_placedByPlayer_52: out = this->f_placedByPlayer; return true;
        case SYM_GEN_dragged_53: out = this->f_dragged; return true;
        case SYM_GEN_occupiedCells_54: out = this->f_occupiedCells; return true;
        case SYM_GEN_collisionCells_55: out = this->f_collisionCells; return true;
        case SYM_GEN_extensionCells_56: out = this->f_extensionCells; return true;
        case SYM_GEN_affectedExtensionCells_57: out = this->f_affectedExtensionCells; return true;
        case SYM_GEN_affectedCellsCache_58: out = this->f_affectedCellsCache; return true;
        case SYM_GEN_currentAffectedItems_59: out = this->f_currentAffectedItems; return true;
        case SYM_GEN_cachedAffectedItems_60: out = this->f_cachedAffectedItems; return true;
        case SYM_GEN_affectedTileCells_61: out = this->f_affectedTileCells; return true;
        case SYM_GEN_consumed_62: out = this->f_consumed; return true;
        case SYM_GEN_hasPreDealDamageEarlyEffect_64: out = this->f_hasPreDealDamageEarlyEffect; return true;
        case SYM_GEN_hasPreDealDamageLateEffect_65: out = this->f_hasPreDealDamageLateEffect; return true;
        case SYM_GEN_hasDealtDamageEffect_66: out = this->f_hasDealtDamageEffect; return true;
        case SYM_GEN_hasOnChargeReceivedEffect_67: out = this->f_hasOnChargeReceivedEffect; return true;
        case SYM_GEN_hasOnChargeLeftEffect_68: out = this->f_hasOnChargeLeftEffect; return true;
        case SYM_GEN_timers_69: out = this->f_timers; return true;
        case SYM_GEN_buffLabelPositionTimestamps_70: out = this->f_buffLabelPositionTimestamps; return true;
        case SYM_GEN_replacementPending_71: out = this->f_replacementPending; return true;
        case SYM_GEN_faceDirection_72: out = this->f_faceDirection; return true;
        case SYM_GEN_rotation_73: out = this->f_rotation; return true;
        case SYM_GEN_CoreElectricalCharge_507: out = gd::GdVal::from_cls(&META_Gd__gd_core__CoreItem__INNER__CoreElectricalCharge); return true;
        case SYM_GEN_CoreSignalConnection_508: out = gd::GdVal::from_cls(&META_Gd__gd_core__CoreItem__INNER__CoreSignalConnection); return true;
        case SYM_GEN_BASE_CRIT_SEVERITY_0: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_cdEncodingFactor_1: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_SELF_BEHAVIOR_METHODS_63: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItem::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_descriptor_2: this->f_descriptor = val; return true;
        case SYM_GEN_ctx_3: this->f_ctx = val; return true;
        case SYM_GEN_character__4: this->f_character_ = val; return true;
        case SYM_GEN_inventory_5: this->f_inventory = val; return true;
        case SYM_GEN_placed_6: this->f_placed = val; return true;
        case SYM_GEN_name_7: this->f_name = val; return true;
        case SYM_GEN_chargeFrame_8: this->f_chargeFrame = val; return true;
        case SYM_GEN_speedScale_9: this->f_speedScale = gd::gd_coerce_float(val); return true;
        case SYM_GEN_bonusMaxDam_10: this->f_bonusMaxDam = gd::gd_coerce_float(val); return true;
        case SYM_GEN_bonusMinDam_11: this->f_bonusMinDam = gd::gd_coerce_float(val); return true;
        case SYM_GEN_removableDam_12: this->f_removableDam = gd::gd_coerce_float(val); return true;
        case SYM_GEN_bonusDamageFactor_13: this->f_bonusDamageFactor = gd::gd_coerce_float(val); return true;
        case SYM_GEN_staminaFactor_14: this->f_staminaFactor = gd::gd_coerce_float(val); return true;
        case SYM_GEN_critChancePercent_15: this->f_critChancePercent = gd::gd_coerce_float(val); return true;
        case SYM_GEN_critTokens_16: this->f_critTokens = gd::gd_coerce_int(val); return true;
        case SYM_GEN_critSeverity_17: this->f_critSeverity = gd::gd_coerce_float(val); return true;
        case SYM_GEN_bonusChancePercent_mult_18: this->f_bonusChancePercent_mult = gd::gd_coerce_float(val); return true;
        case SYM_GEN_bonusChancePercent_additive1_19: this->f_bonusChancePercent_additive1 = gd::gd_coerce_float(val); return true;
        case SYM_GEN_bonusChancePercent_additive2_20: this->f_bonusChancePercent_additive2 = gd::gd_coerce_float(val); return true;
        case SYM_GEN_bonusAccuracy_21: this->f_bonusAccuracy = gd::gd_coerce_float(val); return true;
        case SYM_GEN_buffPowers_22: this->f_buffPowers = val; return true;
        case SYM_GEN_buffAmplificationChances_23: this->f_buffAmplificationChances = val; return true;
        case SYM_GEN_damageSource_24: this->f_damageSource = val; return true;
        case SYM_GEN_doubleActivationChance_25: this->f_doubleActivationChance = gd::gd_coerce_float(val); return true;
        case SYM_GEN_doubleAttackEffectChance_26: this->f_doubleAttackEffectChance = gd::gd_coerce_float(val); return true;
        case SYM_GEN_paramMult_27: this->f_paramMult = val; return true;
        case SYM_GEN_paramAdd_28: this->f_paramAdd = val; return true;
        case SYM_GEN_numCharges_29: this->f_numCharges = gd::gd_coerce_int(val); return true;
        case SYM_GEN_baseCooldownOverride_30: this->f_baseCooldownOverride = gd::gd_coerce_float(val); return true;
        case SYM_GEN_chanceRng_31: this->f_chanceRng = val; return true;
        case SYM_GEN_damageRangeRng_32: this->f_damageRangeRng = val; return true;
        case SYM_GEN_statDisplayOverrides_33: this->f_statDisplayOverrides = val; return true;
        case SYM_GEN_lastActivationTime_34: this->f_lastActivationTime = gd::gd_coerce_float(val); return true;
        case SYM_GEN_activationsThisFrame_35: this->f_activationsThisFrame = gd::gd_coerce_int(val); return true;
        case SYM_GEN_lastTriggerTime_36: this->f_lastTriggerTime = gd::gd_coerce_float(val); return true;
        case SYM_GEN_triggersThisFrame_37: this->f_triggersThisFrame = gd::gd_coerce_int(val); return true;
        case SYM_GEN_triggerTime_38: this->f_triggerTime = gd::gd_coerce_float(val); return true;
        case SYM_GEN_iterationCooldown_39: this->f_iterationCooldown = gd::gd_coerce_float(val); return true;
        case SYM_GEN_flk_suppress_fire_40: this->f_flk_suppress_fire = val; return true;
        case SYM_GEN__inj_item_41: this->f__inj_item = val; return true;
        case SYM_GEN__inj_trigger_n_42: this->f__inj_trigger_n = gd::gd_coerce_int(val); return true;
        case SYM_GEN__inj_trigger_count_43: this->f__inj_trigger_count = gd::gd_coerce_int(val); return true;
        case SYM_GEN_itemMetrics_44: this->f_itemMetrics = val; return true;
        case SYM_GEN_gems_45: this->f_gems = val; return true;
        case SYM_GEN__grid_46: this->f__grid = val; return true;
        case SYM_GEN__behavior_47: this->f__behavior = val; return true;
        case SYM_GEN__cooldown_active_48: this->f__cooldown_active = val; return true;
        case SYM_GEN_dynamicTypes_49: this->f_dynamicTypes = val; return true;
        case SYM_GEN_combatConnections_50: this->f_combatConnections = val; return true;
        case SYM_GEN_ownerType_51: this->f_ownerType = gd::gd_coerce_int(val); return true;
        case SYM_GEN_placedByPlayer_52: this->f_placedByPlayer = val; return true;
        case SYM_GEN_dragged_53: this->f_dragged = val; return true;
        case SYM_GEN_occupiedCells_54: this->f_occupiedCells = val; return true;
        case SYM_GEN_collisionCells_55: this->f_collisionCells = val; return true;
        case SYM_GEN_extensionCells_56: this->f_extensionCells = val; return true;
        case SYM_GEN_affectedExtensionCells_57: this->f_affectedExtensionCells = val; return true;
        case SYM_GEN_affectedCellsCache_58: this->f_affectedCellsCache = val; return true;
        case SYM_GEN_currentAffectedItems_59: this->f_currentAffectedItems = val; return true;
        case SYM_GEN_cachedAffectedItems_60: this->f_cachedAffectedItems = val; return true;
        case SYM_GEN_affectedTileCells_61: this->f_affectedTileCells = val; return true;
        case SYM_GEN_consumed_62: this->f_consumed = val; return true;
        case SYM_GEN_hasPreDealDamageEarlyEffect_64: this->f_hasPreDealDamageEarlyEffect = val; return true;
        case SYM_GEN_hasPreDealDamageLateEffect_65: this->f_hasPreDealDamageLateEffect = val; return true;
        case SYM_GEN_hasDealtDamageEffect_66: this->f_hasDealtDamageEffect = val; return true;
        case SYM_GEN_hasOnChargeReceivedEffect_67: this->f_hasOnChargeReceivedEffect = val; return true;
        case SYM_GEN_hasOnChargeLeftEffect_68: this->f_hasOnChargeLeftEffect = val; return true;
        case SYM_GEN_timers_69: this->f_timers = val; return true;
        case SYM_GEN_buffLabelPositionTimestamps_70: this->f_buffLabelPositionTimestamps = val; return true;
        case SYM_GEN_replacementPending_71: this->f_replacementPending = val; return true;
        case SYM_GEN_faceDirection_72: this->f_faceDirection = gd::gd_coerce_int(val); return true;
        case SYM_GEN_rotation_73: this->f_rotation = gd::gd_coerce_float(val); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItem::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_setup_74: return true;
        case SYM_GEN_hasCharacter_75: return true;
        case SYM_GEN_character_76: return true;
        case SYM_GEN_opponent_77: return true;
        case SYM_GEN_isPlaced_78: return true;
        case SYM_GEN_isCoreItem_79: return true;
        case SYM_GEN_isPlayer_80: return true;
        case SYM_GEN_hasType_81: return true;
        case SYM_GEN_getTypeMultiplicity_82: return true;
        case SYM_GEN_hasTag_83: return true;
        case SYM_GEN_isWeapon_84: return true;
        case SYM_GEN_isBag_85: return true;
        case SYM_GEN_isGem_86: return true;
        case SYM_GEN_isBattleRageItem_87: return true;
        case SYM_GEN_gainsStack_88: return true;
        case SYM_GEN_removesStack_89: return true;
        case SYM_GEN_usesStack_90: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN_canDamage_91: return true;
        case SYM_GEN_canBeEmpowered_92: return true;
        case SYM_GEN_canActivate_93: return true;
        case SYM_GEN_getSpeed_94: return true;
        case SYM_GEN_speed_95: return true;
        case SYM_GEN_getStackSpeedMods_96: return true;
        case SYM_GEN_hasCooldown_97: return true;
        case SYM_GEN_isCooldownActive_98: return true;
        case SYM_GEN_setCooldownActive_99: return true;
        case SYM_GEN_activateCooldown_100: return true;
        case SYM_GEN_deactivateCooldown_101: return true;
        case SYM_GEN_getBaseCooldown_102: return true;
        case SYM_GEN_getBaseCooldownIndex_103: return true;
        case SYM_GEN_getCooldown_104: return true;
        case SYM_GEN_getCooldownIndex_105: return true;
        case SYM_GEN_getModifiedCooldown_106: return true;
        case SYM_GEN_getModifiedCooldownIndex_107: return true;
        case SYM_GEN_getCooldownEncoded_108: return true;
        case SYM_GEN_adjustCooldown_109: return true;
        case SYM_GEN_setBaseCooldown_110: return true;
        case SYM_GEN_resetBaseCooldown_111: return true;
        case SYM_GEN_updateBaseCooldown_112: return true;
        case SYM_GEN_getBaseStaminaCost_113: return true;
        case SYM_GEN_getStaminaCost_114: return true;
        case SYM_GEN_isStaminaModified_115: return true;
        case SYM_GEN_isStatModified_116: return true;
        case SYM_GEN_setStat_117: return true;
        case SYM_GEN_useStamina_118: return true;
        case SYM_GEN_drainStamina_119: return true;
        case SYM_GEN_playOutOfStaminaAnimation_120: return true;
        case SYM_GEN_cacheAffectedItemsForCombat_121: return true;
        case SYM_GEN_addToInventory_122: return true;
        case SYM_GEN_registerWithInventory_123: return true;
        case SYM_GEN_prepare_124: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_preCombatStart_126: return true;
        case SYM_GEN_onPreCombatStart_127: return true;
        case SYM_GEN_hasStartofBattle_128: return true;
        case SYM_GEN_combatStart_129: return true;
        case SYM_GEN_postCombatStart_130: return true;
        case SYM_GEN_onPostCombatStart_131: return true;
        case SYM_GEN_repeatCombatStart_132: return true;
        case SYM_GEN_combatEnd_133: return true;
        case SYM_GEN_onCombatEnd_134: return true;
        case SYM_GEN_resetCombatState_135: return true;
        case SYM_GEN_physicsTick_136: return true;
        case SYM_GEN_newItemTimer_137: return true;
        case SYM_GEN_getTimer_138: return true;
        case SYM_GEN__tickTimers_139: return true;
        case SYM_GEN_tickTimersPass_140: return true;
        case SYM_GEN_rebuildTimerSeen_141: return true;
        case SYM_GEN__readyInit_142: return true;
        case SYM_GEN_flickerPlayAni_143: return true;
        case SYM_GEN_checkTriggerCount_144: return true;
        case SYM_GEN_trigger_145: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onAfterEffectFinished_147: return true;
        case SYM_GEN_advanceCooldownPercent_148: return true;
        case SYM_GEN_advanceCooldownSeconds_149: return true;
        case SYM_GEN_playActivationSound_150: return true;
        case SYM_GEN_playDropSound_151: return true;
        case SYM_GEN_activate_152: return true;
        case SYM_GEN_checkActivationLimit_153: return true;
        case SYM_GEN_getBaseMinDamage_154: return true;
        case SYM_GEN_getBaseMaxDamage_155: return true;
        case SYM_GEN_getBaseAverageDamage_156: return true;
        case SYM_GEN_getTypedDamageFactor_157: return true;
        case SYM_GEN_getMinDamage_158: return true;
        case SYM_GEN_getMaxDamage_159: return true;
        case SYM_GEN_getAverageDamage_160: return true;
        case SYM_GEN_randDamage_161: return true;
        case SYM_GEN_getModifiedEffectDamage_162: return true;
        case SYM_GEN_addBonusDamage_163: return true;
        case SYM_GEN_changeVaryingDamage_164: return true;
        case SYM_GEN_addMinDamage_165: return true;
        case SYM_GEN_addMaxDamage_166: return true;
        case SYM_GEN_getRemovableDamage_167: return true;
        case SYM_GEN_removeBonusDamage_168: return true;
        case SYM_GEN_setBonusDamageFactor_169: return true;
        case SYM_GEN_getBaseChance_170: return true;
        case SYM_GEN_getBaseChance2_171: return true;
        case SYM_GEN_applyBonusChance_172: return true;
        case SYM_GEN_getChance_173: return true;
        case SYM_GEN_getChance2_174: return true;
        case SYM_GEN_rollChance_175: return true;
        case SYM_GEN_rollChance2_176: return true;
        case SYM_GEN_addBonusChance_177: return true;
        case SYM_GEN_addBonusChance_additive_178: return true;
        case SYM_GEN_addAccuracy_179: return true;
        case SYM_GEN_getCritChancePercent_180: return true;
        case SYM_GEN_addCritChancePercent_181: return true;
        case SYM_GEN_reduceCritChancePercent_182: return true;
        case SYM_GEN_changeCritChancePercent_183: return true;
        case SYM_GEN_getCritTokens_184: return true;
        case SYM_GEN_addCritTokens_185: return true;
        case SYM_GEN_useCritToken_186: return true;
        case SYM_GEN_addCritSeverity_187: return true;
        case SYM_GEN_getCritSeverity_188: return true;
        case SYM_GEN_rollDoubleAttackEffect_189: return true;
        case SYM_GEN_getP_190: return true;
        case SYM_GEN_getP_m_191: return true;
        case SYM_GEN_getParamModified_192: return true;
        case SYM_GEN_modifyParam_193: return true;
        case SYM_GEN_modifyParam_add_194: return true;
        case SYM_GEN_getBaseAccuracy_195: return true;
        case SYM_GEN_getAccuracy_196: return true;
        case SYM_GEN_getAmplificationChancePercent_197: return true;
        case SYM_GEN_changeAmplificiationChancePercent_198: return true;
        case SYM_GEN_changeAmplificiationChancePercent_allBuffs_199: return true;
        case SYM_GEN_changeAmplificiationChancePercent_allDebuffs_200: return true;
        case SYM_GEN_changeNullifyChancePercent_201: return true;
        case SYM_GEN_giveReflectStacks_202: return true;
        case SYM_GEN_giveStacks_203: return true;
        case SYM_GEN_giveStacksTemporary_204: return true;
        case SYM_GEN_giveBlock_205: return true;
        case SYM_GEN_getBlock_206: return true;
        case SYM_GEN_removeBlock_207: return true;
        case SYM_GEN_loseBlock_208: return true;
        case SYM_GEN_useBlock_209: return true;
        case SYM_GEN_stealStack_210: return true;
        case SYM_GEN_giveSpikes_211: return true;
        case SYM_GEN_giveVampirism_212: return true;
        case SYM_GEN_inflictPoison_213: return true;
        case SYM_GEN_selfInflictPoison_214: return true;
        case SYM_GEN_inflictBlind_215: return true;
        case SYM_GEN_giveRegeneration_216: return true;
        case SYM_GEN_giveLucky_217: return true;
        case SYM_GEN_giveMana_218: return true;
        case SYM_GEN_giveEmpower_219: return true;
        case SYM_GEN_giveHeat_220: return true;
        case SYM_GEN_giveCold_221: return true;
        case SYM_GEN_dealDamage_222: return true;
        case SYM_GEN_dealEffectDamage_223: return true;
        case SYM_GEN_preDealDamage_early_224: return true;
        case SYM_GEN_preDealDamage_late_225: return true;
        case SYM_GEN_dealtDamage_226: return true;
        case SYM_GEN_countDamage_227: return true;
        case SYM_GEN_addMetric_232: return true;
        case SYM_GEN_getMetric_233: return true;
        case SYM_GEN_stackChanged_234: return true;
        case SYM_GEN_staminaChanged_235: return true;
        case SYM_GEN_getName_236: return true;
        case SYM_GEN_getIndex_237: return true;
        case SYM_GEN_getRarity_238: return true;
        case SYM_GEN_getShopChance_239: return true;
        case SYM_GEN_getMainType_240: return true;
        case SYM_GEN_getNumStaticTypes_241: return true;
        case SYM_GEN_getTypes_242: return true;
        case SYM_GEN_hasDynamicType_243: return true;
        case SYM_GEN_addDynamicType_244: return true;
        case SYM_GEN_removeDynamicType_245: return true;
        case SYM_GEN_clearDynamicTypes_246: return true;
        case SYM_GEN_isA_247: return true;
        case SYM_GEN_isNeutral_248: return true;
        case SYM_GEN_isTreasure_249: return true;
        case SYM_GEN_isClassItem_250: return true;
        case SYM_GEN_isSubclassItem_251: return true;
        case SYM_GEN_isOwnable_252: return true;
        case SYM_GEN_isOwnedByOpponent_253: return true;
        case SYM_GEN_isGateItem_254: return true;
        case SYM_GEN_isShowCaseItem_255: return true;
        case SYM_GEN_isAffectingDistinct_256: return true;
        case SYM_GEN_affectsEmpty_257: return true;
        case SYM_GEN_hasOpponent_258: return true;
        case SYM_GEN_getEffectiveOwnerType_259: return true;
        case SYM_GEN_isBaseItem_260: return true;
        case SYM_GEN_isBusy_261: return true;
        case SYM_GEN_isBoundAsIngredient_262: return true;
        case SYM_GEN_getStat_263: return true;
        case SYM_GEN_getP_check_264: return true;
        case SYM_GEN_getP1_265: return true;
        case SYM_GEN_getP2_266: return true;
        case SYM_GEN_getP3_267: return true;
        case SYM_GEN_getP4_268: return true;
        case SYM_GEN_getP5_269: return true;
        case SYM_GEN_getP6_270: return true;
        case SYM_GEN_getP7_271: return true;
        case SYM_GEN_getP8_272: return true;
        case SYM_GEN_getP9_273: return true;
        case SYM_GEN_getP10_274: return true;
        case SYM_GEN_addSpeed_275: return true;
        case SYM_GEN_reduceSpeed_276: return true;
        case SYM_GEN_getDPS_277: return true;
        case SYM_GEN_isDPSModified_278: return true;
        case SYM_GEN_getDamageRange_279: return true;
        case SYM_GEN_isCooldownModified_280: return true;
        case SYM_GEN_isAccuracyModified_281: return true;
        case SYM_GEN_isChance1Modified_282: return true;
        case SYM_GEN_isChance2Modified_283: return true;
        case SYM_GEN_isDamageModified_284: return true;
        case SYM_GEN_getBaseStaminaPerSecond_285: return true;
        case SYM_GEN_getStaminaPerSecond_286: return true;
        case SYM_GEN_isStaminaPerSecondModified_287: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_canAffect_secondary_289: return true;
        case SYM_GEN_canAffect_tertiary_290: return true;
        case SYM_GEN_canAffect_lightning_291: return true;
        case SYM_GEN_canAffect_color_292: return true;
        case SYM_GEN_canBlock_293: return true;
        case SYM_GEN_canHealOrLifesteal_294: return true;
        case SYM_GEN_canModifyChance_295: return true;
        case SYM_GEN_canUseStamina_296: return true;
        case SYM_GEN_hasAttackEffect_297: return true;
        case SYM_GEN_gainsBuffs_298: return true;
        case SYM_GEN_usesBuffs_299: return true;
        case SYM_GEN_inflictsDebuffs_300: return true;
        case SYM_GEN_reactsToCharges_301: return true;
        case SYM_GEN_fillUpStamina_302: return true;
        case SYM_GEN_getRelativeOpponentHealth_303: return true;
        case SYM_GEN_getRelativeHealth_304: return true;
        case SYM_GEN_giveBuffPower_305: return true;
        case SYM_GEN_changeHealAmp_306: return true;
        case SYM_GEN_changeStaminaFactor_307: return true;
        case SYM_GEN_addBonusDamageFactor_308: return true;
        case SYM_GEN_reduceBonusDamageFactor_309: return true;
        case SYM_GEN_reduceMinDamage_310: return true;
        case SYM_GEN_reduceMaxDamage_311: return true;
        case SYM_GEN_reduceBonusDamage_312: return true;
        case SYM_GEN_purgeDamage_313: return true;
        case SYM_GEN_giveDoubleActivationChance_314: return true;
        case SYM_GEN_giveDoubleAttackEffectChance_315: return true;
        case SYM_GEN_giveCritTokens_316: return true;
        case SYM_GEN_giveMaxStamina_317: return true;
        case SYM_GEN_giveMaxStaminaTemporary_318: return true;
        case SYM_GEN_giveMaxHealth_319: return true;
        case SYM_GEN_giveStamina_320: return true;
        case SYM_GEN_inflictFatigueDamage_321: return true;
        case SYM_GEN_sendCharge_322: return true;
        case SYM_GEN__chargeInventoryCells_323: return true;
        case SYM_GEN__rotVecQuarterTurns_324: return true;
        case SYM_GEN__chargeEnterCell_325: return true;
        case SYM_GEN_chargeReceived_326: return true;
        case SYM_GEN_chargeLeft_327: return true;
        case SYM_GEN_changeChargedItemStat_328: return true;
        case SYM_GEN_heal_329: return true;
        case SYM_GEN_healthToBlock_330: return true;
        case SYM_GEN_stealLife_331: return true;
        case SYM_GEN_stun_332: return true;
        case SYM_GEN_checkMana_333: return true;
        case SYM_GEN_useMana_334: return true;
        case SYM_GEN_tryUseMana_335: return true;
        case SYM_GEN_removeMana_336: return true;
        case SYM_GEN_giveMana_capped_337: return true;
        case SYM_GEN_removeSpikes_338: return true;
        case SYM_GEN_useSpikes_339: return true;
        case SYM_GEN_loseSpikes_340: return true;
        case SYM_GEN_removeVampirism_341: return true;
        case SYM_GEN_useVampirism_342: return true;
        case SYM_GEN_loseVampirism_343: return true;
        case SYM_GEN_cleansePoison_344: return true;
        case SYM_GEN_selfInflictBlind_345: return true;
        case SYM_GEN_cleanseBlind_346: return true;
        case SYM_GEN_removeRegeneration_347: return true;
        case SYM_GEN_useRegeneration_348: return true;
        case SYM_GEN_tryUseLucky_349: return true;
        case SYM_GEN_loseLucky_350: return true;
        case SYM_GEN_removeLucky_351: return true;
        case SYM_GEN_useLucky_352: return true;
        case SYM_GEN_inflictCold_353: return true;
        case SYM_GEN_cleanseCold_354: return true;
        case SYM_GEN_loseHeat_355: return true;
        case SYM_GEN_useHeat_356: return true;
        case SYM_GEN_loseEmpower_357: return true;
        case SYM_GEN_cleanseRandomDebuffs_358: return true;
        case SYM_GEN_inflictRandomDebuffs_359: return true;
        case SYM_GEN_pickRandomStacks_360: return true;
        case SYM_GEN_pickRandomStacksToGive_361: return true;
        case SYM_GEN_getLeastStacks_362: return true;
        case SYM_GEN_getMostStacks_363: return true;
        case SYM_GEN_getStackFraction_364: return true;
        case SYM_GEN_multiplyBuffsLimit_365: return true;
        case SYM_GEN_removeBuffsFraction_366: return true;
        case SYM_GEN_stealBuffsFraction_367: return true;
        case SYM_GEN_giveLeastBuffs_368: return true;
        case SYM_GEN_giveMostBuffs_369: return true;
        case SYM_GEN_removeMostBuffs_370: return true;
        case SYM_GEN_giveRandomBuffs_371: return true;
        case SYM_GEN_giveAllBuffs_372: return true;
        case SYM_GEN_useRandomBuffs_373: return true;
        case SYM_GEN_removeRandomBuffs_374: return true;
        case SYM_GEN_stealRandomBuff_375: return true;
        case SYM_GEN_connectToCharacterBuffs_376: return true;
        case SYM_GEN_connectToCharacterDebuffs_377: return true;
        case SYM_GEN_connectToOpponentDebuffs_378: return true;
        case SYM_GEN_connectToOpponentBuffs_379: return true;
        case SYM_GEN_getNextFreeLabelPosition_380: return true;
        case SYM_GEN_spawnLabel_381: return true;
        case SYM_GEN_spawnLabel_other_382: return true;
        case SYM_GEN_consume_383: return true;
        case SYM_GEN_setState_384: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN_onTemporaryStacksTimeout_386: return true;
        case SYM_GEN_empowerEnd_387: return true;
        case SYM_GEN_hasSockets_388: return true;
        case SYM_GEN_getNumSockets_389: return true;
        case SYM_GEN_initSockets_390: return true;
        case SYM_GEN_getItem_391: return true;
        case SYM_GEN_hasGems_392: return true;
        case SYM_GEN_getGemsOfItems_393: return true;
        case SYM_GEN_getPrice_394: return true;
        case SYM_GEN_getBaseSellPrice_395: return true;
        case SYM_GEN_getSellPrice_396: return true;
        case SYM_GEN_getSalePrice_397: return true;
        case SYM_GEN_setGem_398: return true;
        case SYM_GEN_pushGemsToStorage_399: return true;
        case SYM_GEN_pushItemsInsideToStorage_400: return true;
        case SYM_GEN_returnToSocket_401: return true;
        case SYM_GEN_getOwnOrPlayerInventory_402: return true;
        case SYM_GEN_getCellsForGlobalPositions_403: return true;
        case SYM_GEN_getGlobalPointsForCells_404: return true;
        case SYM_GEN_getGlobalPointsForCells_noRotate_405: return true;
        case SYM_GEN_getCollisionCells_406: return true;
        case SYM_GEN_getExtensionCells_407: return true;
        case SYM_GEN_getCollisionPoints_408: return true;
        case SYM_GEN_getExtensionPoints_409: return true;
        case SYM_GEN_getAffectedCells_tilemap_410: return true;
        case SYM_GEN_getAffectedCellsAfterRotate_411: return true;
        case SYM_GEN_getAffectedCellsAfterRotate_primary_412: return true;
        case SYM_GEN_getAffectedCellsAfterRotate_secondary_413: return true;
        case SYM_GEN_getAffectedCells_noRotate_414: return true;
        case SYM_GEN_getAffectedPoints_415: return true;
        case SYM_GEN_getAffectedCellsInInventory_416: return true;
        case SYM_GEN_getAffectedCellsInInventory_cached_417: return true;
        case SYM_GEN_cacheAffectedCells_418: return true;
        case SYM_GEN_cleanCachedAffectedItems_419: return true;
        case SYM_GEN_onRemoveFromInventory_420: return true;
        case SYM_GEN_onAddToInventory_421: return true;
        case SYM_GEN_getAffectedItems_422: return true;
        case SYM_GEN_getAffectedItems_nocache_423: return true;
        case SYM_GEN_getItemsInAffectedCells_424: return true;
        case SYM_GEN_getItemsInAffectedCells_cached_425: return true;
        case SYM_GEN_countItemsInAffectedCells_cached_426: return true;
        case SYM_GEN_isItemAffected_427: return true;
        case SYM_GEN_getNumEmptyAffectedCells_428: return true;
        case SYM_GEN_getNumAffectedItems_429: return true;
        case SYM_GEN_getFirstAffectedItem_430: return true;
        case SYM_GEN_getNumAffected_type_431: return true;
        case SYM_GEN_getNumDistinctAffectedItems_432: return true;
        case SYM_GEN_getNumAffectedCells_433: return true;
        case SYM_GEN_activateExtendedAffectedCells_434: return true;
        case SYM_GEN_deactivateExtendedAffectedCells_435: return true;
        case SYM_GEN_canAffectDraggedItem_436: return true;
        case SYM_GEN_onAffectedItemAdded_437: return true;
        case SYM_GEN_onAffectedItemRemoved_438: return true;
        case SYM_GEN_onItemAdded_439: return true;
        case SYM_GEN_onItemRemoved_440: return true;
        case SYM_GEN_getNumOccupiedCells_441: return true;
        case SYM_GEN_getNumBagCells_442: return true;
        case SYM_GEN_getNumCells_443: return true;
        case SYM_GEN_getSizeInCells_444: return true;
        case SYM_GEN_getTopLeftCell_445: return true;
        case SYM_GEN_getNormalizedCollisionCells_446: return true;
        case SYM_GEN_canCombine_447: return true;
        case SYM_GEN_prepareReplacement_448: return true;
        case SYM_GEN_finishReplacement_449: return true;
        case SYM_GEN_placeGeneratedItem_450: return true;
        case SYM_GEN_moveTo_451: return true;
        case SYM_GEN_resetZ_452: return true;
        case SYM_GEN_onGateItemRoll_453: return true;
        case SYM_GEN_insertCounter_454: return true;
        case SYM_GEN_queue_free_455: return true;
        case SYM_GEN_shift_456: return true;
        case SYM_GEN_onBought_457: return true;
        case SYM_GEN_onSold_458: return true;
        case SYM_GEN_reactToItemTypeChange_459: return true;
        case SYM_GEN_onItemTypeChanged_460: return true;
        case SYM_GEN_getRelatedItems_461: return true;
        case SYM_GEN_countAllPlacedOfType_462: return true;
        case SYM_GEN_getTouchedBagsCounted_463: return true;
        case SYM_GEN_getHeightRange_464: return true;
        case SYM_GEN_ready_deferred_465: return true;
        case SYM_GEN_rotationFromFaceDirection_466: return true;
        case SYM_GEN_getFaceDirection_467: return true;
        case SYM_GEN_getGlobalFaceDirection_468: return true;
        case SYM_GEN_setFaceDirectionInstant_469: return true;
        case SYM_GEN_setRotation_470: return true;
        case SYM_GEN_changeAllItemsCritRate_471: return true;
        case SYM_GEN_miniActivate_472: return true;
        case SYM_GEN_previewCellCollision_473: return true;
        case SYM_GEN_previewCells_474: return true;
        case SYM_GEN_previewCanAffect_475: return true;
        case SYM_GEN_rotateRight_476: return true;
        case SYM_GEN_rotateLeft_477: return true;
        case SYM_GEN_rotateTo_478: return true;
        case SYM_GEN_rotateToDeferred_479: return true;
        case SYM_GEN_setFaceDirection_480: return true;
        case SYM_GEN_correctInsideItemFacedirection_481: return true;
        case SYM_GEN_getBagEffect_482: return true;
        case SYM_GEN_getGemData_483: return true;
        case SYM_GEN_setGemData_484: return true;
        case SYM_GEN_reconstructCooldown_485: return true;
        case SYM_GEN_findBondsWithAffectedItems_486: return true;
        case SYM_GEN_rotateProgress_487: return true;
        case SYM_GEN_cacheCollisionCells_488: return true;
        case SYM_GEN_isBaseItemForShopItem_489: return true;
        case SYM_GEN_activateFromEvent_490: return true;
        case SYM_GEN_getNeighborItemsAndGems_491: return true;
        case SYM_GEN_getTouchedBags_492: return true;
        case SYM_GEN_getBusyNeighbors_493: return true;
        case SYM_GEN_getCraftableNeighbors_494: return true;
        case SYM_GEN_isAvailableForCrafting_495: return true;
        case SYM_GEN_getAffectedGoldValue_496: return true;
        case SYM_GEN_countTypes_497: return true;
        case SYM_GEN_hasSameOrientationAsPickup_498: return true;
        case SYM_GEN_getGemsNoNull_499: return true;
        case SYM_GEN_getGems_500: return true;
        case SYM_GEN_buildDamageSource_501: return true;
        case SYM_GEN_connectForCombat_502: return true;
        case SYM_GEN_connectForCombat_signal_503: return true;
        case SYM_GEN_disconnectCombat_504: return true;
        case SYM_GEN__hasBehaviorMethod_505: return true;
        case SYM_GEN__behavior_call_506: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItem::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_setup_74: out = fn_setup(args, argc); return true;
        case SYM_GEN_hasCharacter_75: out = fn_hasCharacter(args, argc); return true;
        case SYM_GEN_character_76: out = fn_character(args, argc); return true;
        case SYM_GEN_opponent_77: out = fn_opponent(args, argc); return true;
        case SYM_GEN_isPlaced_78: out = fn_isPlaced(args, argc); return true;
        case SYM_GEN_isCoreItem_79: out = fn_isCoreItem(args, argc); return true;
        case SYM_GEN_isPlayer_80: out = fn_isPlayer(args, argc); return true;
        case SYM_GEN_hasType_81: out = fn_hasType(args, argc); return true;
        case SYM_GEN_getTypeMultiplicity_82: out = fn_getTypeMultiplicity(args, argc); return true;
        case SYM_GEN_hasTag_83: out = fn_hasTag(args, argc); return true;
        case SYM_GEN_isWeapon_84: out = fn_isWeapon(args, argc); return true;
        case SYM_GEN_isBag_85: out = fn_isBag(args, argc); return true;
        case SYM_GEN_isGem_86: out = fn_isGem(args, argc); return true;
        case SYM_GEN_isBattleRageItem_87: out = fn_isBattleRageItem(args, argc); return true;
        case SYM_GEN_gainsStack_88: out = fn_gainsStack(args, argc); return true;
        case SYM_GEN_removesStack_89: out = fn_removesStack(args, argc); return true;
        case SYM_GEN_usesStack_90: out = fn_usesStack(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN_canDamage_91: out = fn_canDamage(args, argc); return true;
        case SYM_GEN_canBeEmpowered_92: out = fn_canBeEmpowered(args, argc); return true;
        case SYM_GEN_canActivate_93: out = fn_canActivate(args, argc); return true;
        case SYM_GEN_getSpeed_94: out = fn_getSpeed(args, argc); return true;
        case SYM_GEN_speed_95: out = fn_speed(args, argc); return true;
        case SYM_GEN_getStackSpeedMods_96: out = fn_getStackSpeedMods(args, argc); return true;
        case SYM_GEN_hasCooldown_97: out = fn_hasCooldown(args, argc); return true;
        case SYM_GEN_isCooldownActive_98: out = fn_isCooldownActive(args, argc); return true;
        case SYM_GEN_setCooldownActive_99: out = fn_setCooldownActive(args, argc); return true;
        case SYM_GEN_activateCooldown_100: out = fn_activateCooldown(args, argc); return true;
        case SYM_GEN_deactivateCooldown_101: out = fn_deactivateCooldown(args, argc); return true;
        case SYM_GEN_getBaseCooldown_102: out = fn_getBaseCooldown(args, argc); return true;
        case SYM_GEN_getBaseCooldownIndex_103: out = fn_getBaseCooldownIndex(args, argc); return true;
        case SYM_GEN_getCooldown_104: out = fn_getCooldown(args, argc); return true;
        case SYM_GEN_getCooldownIndex_105: out = fn_getCooldownIndex(args, argc); return true;
        case SYM_GEN_getModifiedCooldown_106: out = fn_getModifiedCooldown(args, argc); return true;
        case SYM_GEN_getModifiedCooldownIndex_107: out = fn_getModifiedCooldownIndex(args, argc); return true;
        case SYM_GEN_getCooldownEncoded_108: out = fn_getCooldownEncoded(args, argc); return true;
        case SYM_GEN_adjustCooldown_109: out = fn_adjustCooldown(args, argc); return true;
        case SYM_GEN_setBaseCooldown_110: out = fn_setBaseCooldown(args, argc); return true;
        case SYM_GEN_resetBaseCooldown_111: out = fn_resetBaseCooldown(args, argc); return true;
        case SYM_GEN_updateBaseCooldown_112: out = fn_updateBaseCooldown(args, argc); return true;
        case SYM_GEN_getBaseStaminaCost_113: out = fn_getBaseStaminaCost(args, argc); return true;
        case SYM_GEN_getStaminaCost_114: out = fn_getStaminaCost(args, argc); return true;
        case SYM_GEN_isStaminaModified_115: out = fn_isStaminaModified(args, argc); return true;
        case SYM_GEN_isStatModified_116: out = fn_isStatModified(args, argc); return true;
        case SYM_GEN_setStat_117: out = fn_setStat(args, argc); return true;
        case SYM_GEN_useStamina_118: out = fn_useStamina(args, argc); return true;
        case SYM_GEN_drainStamina_119: out = fn_drainStamina(args, argc); return true;
        case SYM_GEN_playOutOfStaminaAnimation_120: out = fn_playOutOfStaminaAnimation(args, argc); return true;
        case SYM_GEN_cacheAffectedItemsForCombat_121: out = fn_cacheAffectedItemsForCombat(args, argc); return true;
        case SYM_GEN_addToInventory_122: out = fn_addToInventory(args, argc); return true;
        case SYM_GEN_registerWithInventory_123: out = fn_registerWithInventory(args, argc); return true;
        case SYM_GEN_prepare_124: out = fn_prepare(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_preCombatStart_126: out = fn_preCombatStart(args, argc); return true;
        case SYM_GEN_onPreCombatStart_127: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_hasStartofBattle_128: out = fn_hasStartofBattle(args, argc); return true;
        case SYM_GEN_combatStart_129: out = fn_combatStart(args, argc); return true;
        case SYM_GEN_postCombatStart_130: out = fn_postCombatStart(args, argc); return true;
        case SYM_GEN_onPostCombatStart_131: out = fn_onPostCombatStart(args, argc); return true;
        case SYM_GEN_repeatCombatStart_132: out = fn_repeatCombatStart(args, argc); return true;
        case SYM_GEN_combatEnd_133: out = fn_combatEnd(args, argc); return true;
        case SYM_GEN_onCombatEnd_134: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_resetCombatState_135: out = fn_resetCombatState(args, argc); return true;
        case SYM_GEN_physicsTick_136: out = fn_physicsTick(args, argc); return true;
        case SYM_GEN_newItemTimer_137: out = fn_newItemTimer(args, argc); return true;
        case SYM_GEN_getTimer_138: out = fn_getTimer(args, argc); return true;
        case SYM_GEN__tickTimers_139: out = fn__tickTimers(args, argc); return true;
        case SYM_GEN_tickTimersPass_140: out = fn_tickTimersPass(args, argc); return true;
        case SYM_GEN_rebuildTimerSeen_141: out = fn_rebuildTimerSeen(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        case SYM_GEN_flickerPlayAni_143: out = fn_flickerPlayAni(args, argc); return true;
        case SYM_GEN_checkTriggerCount_144: out = fn_checkTriggerCount(args, argc); return true;
        case SYM_GEN_trigger_145: out = fn_trigger(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onAfterEffectFinished_147: out = fn_onAfterEffectFinished(args, argc); return true;
        case SYM_GEN_advanceCooldownPercent_148: out = fn_advanceCooldownPercent(args, argc); return true;
        case SYM_GEN_advanceCooldownSeconds_149: out = fn_advanceCooldownSeconds(args, argc); return true;
        case SYM_GEN_playActivationSound_150: out = fn_playActivationSound(args, argc); return true;
        case SYM_GEN_playDropSound_151: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN_activate_152: out = fn_activate(args, argc); return true;
        case SYM_GEN_checkActivationLimit_153: out = fn_checkActivationLimit(args, argc); return true;
        case SYM_GEN_getBaseMinDamage_154: out = fn_getBaseMinDamage(args, argc); return true;
        case SYM_GEN_getBaseMaxDamage_155: out = fn_getBaseMaxDamage(args, argc); return true;
        case SYM_GEN_getBaseAverageDamage_156: out = fn_getBaseAverageDamage(args, argc); return true;
        case SYM_GEN_getTypedDamageFactor_157: out = fn_getTypedDamageFactor(args, argc); return true;
        case SYM_GEN_getMinDamage_158: out = fn_getMinDamage(args, argc); return true;
        case SYM_GEN_getMaxDamage_159: out = fn_getMaxDamage(args, argc); return true;
        case SYM_GEN_getAverageDamage_160: out = fn_getAverageDamage(args, argc); return true;
        case SYM_GEN_randDamage_161: out = fn_randDamage(args, argc); return true;
        case SYM_GEN_getModifiedEffectDamage_162: out = fn_getModifiedEffectDamage(args, argc); return true;
        case SYM_GEN_addBonusDamage_163: out = fn_addBonusDamage(args, argc); return true;
        case SYM_GEN_changeVaryingDamage_164: out = fn_changeVaryingDamage(args, argc); return true;
        case SYM_GEN_addMinDamage_165: out = fn_addMinDamage(args, argc); return true;
        case SYM_GEN_addMaxDamage_166: out = fn_addMaxDamage(args, argc); return true;
        case SYM_GEN_getRemovableDamage_167: out = fn_getRemovableDamage(args, argc); return true;
        case SYM_GEN_removeBonusDamage_168: out = fn_removeBonusDamage(args, argc); return true;
        case SYM_GEN_setBonusDamageFactor_169: out = fn_setBonusDamageFactor(args, argc); return true;
        case SYM_GEN_getBaseChance_170: out = fn_getBaseChance(args, argc); return true;
        case SYM_GEN_getBaseChance2_171: out = fn_getBaseChance2(args, argc); return true;
        case SYM_GEN_applyBonusChance_172: out = fn_applyBonusChance(args, argc); return true;
        case SYM_GEN_getChance_173: out = fn_getChance(args, argc); return true;
        case SYM_GEN_getChance2_174: out = fn_getChance2(args, argc); return true;
        case SYM_GEN_rollChance_175: out = fn_rollChance(args, argc); return true;
        case SYM_GEN_rollChance2_176: out = fn_rollChance2(args, argc); return true;
        case SYM_GEN_addBonusChance_177: out = fn_addBonusChance(args, argc); return true;
        case SYM_GEN_addBonusChance_additive_178: out = fn_addBonusChance_additive(args, argc); return true;
        case SYM_GEN_addAccuracy_179: out = fn_addAccuracy(args, argc); return true;
        case SYM_GEN_getCritChancePercent_180: out = fn_getCritChancePercent(args, argc); return true;
        case SYM_GEN_addCritChancePercent_181: out = fn_addCritChancePercent(args, argc); return true;
        case SYM_GEN_reduceCritChancePercent_182: out = fn_reduceCritChancePercent(args, argc); return true;
        case SYM_GEN_changeCritChancePercent_183: out = fn_changeCritChancePercent(args, argc); return true;
        case SYM_GEN_getCritTokens_184: out = fn_getCritTokens(args, argc); return true;
        case SYM_GEN_addCritTokens_185: out = fn_addCritTokens(args, argc); return true;
        case SYM_GEN_useCritToken_186: out = fn_useCritToken(args, argc); return true;
        case SYM_GEN_addCritSeverity_187: out = fn_addCritSeverity(args, argc); return true;
        case SYM_GEN_getCritSeverity_188: out = fn_getCritSeverity(args, argc); return true;
        case SYM_GEN_rollDoubleAttackEffect_189: out = fn_rollDoubleAttackEffect(args, argc); return true;
        case SYM_GEN_getP_190: out = fn_getP(args, argc); return true;
        case SYM_GEN_getP_m_191: out = fn_getP_m(args, argc); return true;
        case SYM_GEN_getParamModified_192: out = fn_getParamModified(args, argc); return true;
        case SYM_GEN_modifyParam_193: out = fn_modifyParam(args, argc); return true;
        case SYM_GEN_modifyParam_add_194: out = fn_modifyParam_add(args, argc); return true;
        case SYM_GEN_getBaseAccuracy_195: out = fn_getBaseAccuracy(args, argc); return true;
        case SYM_GEN_getAccuracy_196: out = fn_getAccuracy(args, argc); return true;
        case SYM_GEN_getAmplificationChancePercent_197: out = fn_getAmplificationChancePercent(args, argc); return true;
        case SYM_GEN_changeAmplificiationChancePercent_198: out = fn_changeAmplificiationChancePercent(args, argc); return true;
        case SYM_GEN_changeAmplificiationChancePercent_allBuffs_199: out = fn_changeAmplificiationChancePercent_allBuffs(args, argc); return true;
        case SYM_GEN_changeAmplificiationChancePercent_allDebuffs_200: out = fn_changeAmplificiationChancePercent_allDebuffs(args, argc); return true;
        case SYM_GEN_changeNullifyChancePercent_201: out = fn_changeNullifyChancePercent(args, argc); return true;
        case SYM_GEN_giveReflectStacks_202: out = fn_giveReflectStacks(args, argc); return true;
        case SYM_GEN_giveStacks_203: out = fn_giveStacks(args, argc); return true;
        case SYM_GEN_giveStacksTemporary_204: out = fn_giveStacksTemporary(args, argc); return true;
        case SYM_GEN_giveBlock_205: out = fn_giveBlock(args, argc); return true;
        case SYM_GEN_getBlock_206: out = fn_getBlock(args, argc); return true;
        case SYM_GEN_removeBlock_207: out = fn_removeBlock(args, argc); return true;
        case SYM_GEN_loseBlock_208: out = fn_loseBlock(args, argc); return true;
        case SYM_GEN_useBlock_209: out = fn_useBlock(args, argc); return true;
        case SYM_GEN_stealStack_210: out = fn_stealStack(args, argc); return true;
        case SYM_GEN_giveSpikes_211: out = fn_giveSpikes(args, argc); return true;
        case SYM_GEN_giveVampirism_212: out = fn_giveVampirism(args, argc); return true;
        case SYM_GEN_inflictPoison_213: out = fn_inflictPoison(args, argc); return true;
        case SYM_GEN_selfInflictPoison_214: out = fn_selfInflictPoison(args, argc); return true;
        case SYM_GEN_inflictBlind_215: out = fn_inflictBlind(args, argc); return true;
        case SYM_GEN_giveRegeneration_216: out = fn_giveRegeneration(args, argc); return true;
        case SYM_GEN_giveLucky_217: out = fn_giveLucky(args, argc); return true;
        case SYM_GEN_giveMana_218: out = fn_giveMana(args, argc); return true;
        case SYM_GEN_giveEmpower_219: out = fn_giveEmpower(args, argc); return true;
        case SYM_GEN_giveHeat_220: out = fn_giveHeat(args, argc); return true;
        case SYM_GEN_giveCold_221: out = fn_giveCold(args, argc); return true;
        case SYM_GEN_dealDamage_222: out = fn_dealDamage(args, argc); return true;
        case SYM_GEN_dealEffectDamage_223: out = fn_dealEffectDamage(args, argc); return true;
        case SYM_GEN_preDealDamage_early_224: out = fn_preDealDamage_early(args, argc); return true;
        case SYM_GEN_preDealDamage_late_225: out = fn_preDealDamage_late(args, argc); return true;
        case SYM_GEN_dealtDamage_226: out = fn_dealtDamage(args, argc); return true;
        case SYM_GEN_countDamage_227: out = fn_countDamage(args, argc); return true;
        case SYM_GEN_getNumNonStackItemMetrics_228: out = sf_getNumNonStackItemMetrics(gd_ctx, args, argc); return true;
        case SYM_GEN_getNumItemMetrics_229: out = sf_getNumItemMetrics(gd_ctx, args, argc); return true;
        case SYM_GEN_getStackMetricIndex_230: out = sf_getStackMetricIndex(gd_ctx, args, argc); return true;
        case SYM_GEN_getMultiMetricIndex_231: out = sf_getMultiMetricIndex(gd_ctx, args, argc); return true;
        case SYM_GEN_addMetric_232: out = fn_addMetric(args, argc); return true;
        case SYM_GEN_getMetric_233: out = fn_getMetric(args, argc); return true;
        case SYM_GEN_stackChanged_234: out = fn_stackChanged(args, argc); return true;
        case SYM_GEN_staminaChanged_235: out = fn_staminaChanged(args, argc); return true;
        case SYM_GEN_getName_236: out = fn_getName(args, argc); return true;
        case SYM_GEN_getIndex_237: out = fn_getIndex(args, argc); return true;
        case SYM_GEN_getRarity_238: out = fn_getRarity(args, argc); return true;
        case SYM_GEN_getShopChance_239: out = fn_getShopChance(args, argc); return true;
        case SYM_GEN_getMainType_240: out = fn_getMainType(args, argc); return true;
        case SYM_GEN_getNumStaticTypes_241: out = fn_getNumStaticTypes(args, argc); return true;
        case SYM_GEN_getTypes_242: out = fn_getTypes(args, argc); return true;
        case SYM_GEN_hasDynamicType_243: out = fn_hasDynamicType(args, argc); return true;
        case SYM_GEN_addDynamicType_244: out = fn_addDynamicType(args, argc); return true;
        case SYM_GEN_removeDynamicType_245: out = fn_removeDynamicType(args, argc); return true;
        case SYM_GEN_clearDynamicTypes_246: out = fn_clearDynamicTypes(args, argc); return true;
        case SYM_GEN_isA_247: out = fn_isA(args, argc); return true;
        case SYM_GEN_isNeutral_248: out = fn_isNeutral(args, argc); return true;
        case SYM_GEN_isTreasure_249: out = fn_isTreasure(args, argc); return true;
        case SYM_GEN_isClassItem_250: out = fn_isClassItem(args, argc); return true;
        case SYM_GEN_isSubclassItem_251: out = fn_isSubclassItem(args, argc); return true;
        case SYM_GEN_isOwnable_252: out = fn_isOwnable(args, argc); return true;
        case SYM_GEN_isOwnedByOpponent_253: out = fn_isOwnedByOpponent(args, argc); return true;
        case SYM_GEN_isGateItem_254: out = fn_isGateItem(args, argc); return true;
        case SYM_GEN_isShowCaseItem_255: out = fn_isShowCaseItem(args, argc); return true;
        case SYM_GEN_isAffectingDistinct_256: out = fn_isAffectingDistinct(args, argc); return true;
        case SYM_GEN_affectsEmpty_257: out = fn_affectsEmpty(args, argc); return true;
        case SYM_GEN_hasOpponent_258: out = fn_hasOpponent(args, argc); return true;
        case SYM_GEN_getEffectiveOwnerType_259: out = fn_getEffectiveOwnerType(args, argc); return true;
        case SYM_GEN_isBaseItem_260: out = fn_isBaseItem(args, argc); return true;
        case SYM_GEN_isBusy_261: out = fn_isBusy(args, argc); return true;
        case SYM_GEN_isBoundAsIngredient_262: out = fn_isBoundAsIngredient(args, argc); return true;
        case SYM_GEN_getStat_263: out = fn_getStat(args, argc); return true;
        case SYM_GEN_getP_check_264: out = fn_getP_check(args, argc); return true;
        case SYM_GEN_getP1_265: out = fn_getP1(args, argc); return true;
        case SYM_GEN_getP2_266: out = fn_getP2(args, argc); return true;
        case SYM_GEN_getP3_267: out = fn_getP3(args, argc); return true;
        case SYM_GEN_getP4_268: out = fn_getP4(args, argc); return true;
        case SYM_GEN_getP5_269: out = fn_getP5(args, argc); return true;
        case SYM_GEN_getP6_270: out = fn_getP6(args, argc); return true;
        case SYM_GEN_getP7_271: out = fn_getP7(args, argc); return true;
        case SYM_GEN_getP8_272: out = fn_getP8(args, argc); return true;
        case SYM_GEN_getP9_273: out = fn_getP9(args, argc); return true;
        case SYM_GEN_getP10_274: out = fn_getP10(args, argc); return true;
        case SYM_GEN_addSpeed_275: out = fn_addSpeed(args, argc); return true;
        case SYM_GEN_reduceSpeed_276: out = fn_reduceSpeed(args, argc); return true;
        case SYM_GEN_getDPS_277: out = fn_getDPS(args, argc); return true;
        case SYM_GEN_isDPSModified_278: out = fn_isDPSModified(args, argc); return true;
        case SYM_GEN_getDamageRange_279: out = fn_getDamageRange(args, argc); return true;
        case SYM_GEN_isCooldownModified_280: out = fn_isCooldownModified(args, argc); return true;
        case SYM_GEN_isAccuracyModified_281: out = fn_isAccuracyModified(args, argc); return true;
        case SYM_GEN_isChance1Modified_282: out = fn_isChance1Modified(args, argc); return true;
        case SYM_GEN_isChance2Modified_283: out = fn_isChance2Modified(args, argc); return true;
        case SYM_GEN_isDamageModified_284: out = fn_isDamageModified(args, argc); return true;
        case SYM_GEN_getBaseStaminaPerSecond_285: out = fn_getBaseStaminaPerSecond(args, argc); return true;
        case SYM_GEN_getStaminaPerSecond_286: out = fn_getStaminaPerSecond(args, argc); return true;
        case SYM_GEN_isStaminaPerSecondModified_287: out = fn_isStaminaPerSecondModified(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_289: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_canAffect_tertiary_290: out = fn_canAffect_tertiary(args, argc); return true;
        case SYM_GEN_canAffect_lightning_291: out = fn_canAffect_lightning(args, argc); return true;
        case SYM_GEN_canAffect_color_292: out = fn_canAffect_color(args, argc); return true;
        case SYM_GEN_canBlock_293: out = fn_canBlock(args, argc); return true;
        case SYM_GEN_canHealOrLifesteal_294: out = fn_canHealOrLifesteal(args, argc); return true;
        case SYM_GEN_canModifyChance_295: out = fn_canModifyChance(args, argc); return true;
        case SYM_GEN_canUseStamina_296: out = fn_canUseStamina(args, argc); return true;
        case SYM_GEN_hasAttackEffect_297: out = fn_hasAttackEffect(args, argc); return true;
        case SYM_GEN_gainsBuffs_298: out = fn_gainsBuffs(args, argc); return true;
        case SYM_GEN_usesBuffs_299: out = fn_usesBuffs(args, argc); return true;
        case SYM_GEN_inflictsDebuffs_300: out = fn_inflictsDebuffs(args, argc); return true;
        case SYM_GEN_reactsToCharges_301: out = fn_reactsToCharges(args, argc); return true;
        case SYM_GEN_fillUpStamina_302: out = fn_fillUpStamina(args, argc); return true;
        case SYM_GEN_getRelativeOpponentHealth_303: out = fn_getRelativeOpponentHealth(args, argc); return true;
        case SYM_GEN_getRelativeHealth_304: out = fn_getRelativeHealth(args, argc); return true;
        case SYM_GEN_giveBuffPower_305: out = fn_giveBuffPower(args, argc); return true;
        case SYM_GEN_changeHealAmp_306: out = fn_changeHealAmp(args, argc); return true;
        case SYM_GEN_changeStaminaFactor_307: out = fn_changeStaminaFactor(args, argc); return true;
        case SYM_GEN_addBonusDamageFactor_308: out = fn_addBonusDamageFactor(args, argc); return true;
        case SYM_GEN_reduceBonusDamageFactor_309: out = fn_reduceBonusDamageFactor(args, argc); return true;
        case SYM_GEN_reduceMinDamage_310: out = fn_reduceMinDamage(args, argc); return true;
        case SYM_GEN_reduceMaxDamage_311: out = fn_reduceMaxDamage(args, argc); return true;
        case SYM_GEN_reduceBonusDamage_312: out = fn_reduceBonusDamage(args, argc); return true;
        case SYM_GEN_purgeDamage_313: out = fn_purgeDamage(args, argc); return true;
        case SYM_GEN_giveDoubleActivationChance_314: out = fn_giveDoubleActivationChance(args, argc); return true;
        case SYM_GEN_giveDoubleAttackEffectChance_315: out = fn_giveDoubleAttackEffectChance(args, argc); return true;
        case SYM_GEN_giveCritTokens_316: out = fn_giveCritTokens(args, argc); return true;
        case SYM_GEN_giveMaxStamina_317: out = fn_giveMaxStamina(args, argc); return true;
        case SYM_GEN_giveMaxStaminaTemporary_318: out = fn_giveMaxStaminaTemporary(args, argc); return true;
        case SYM_GEN_giveMaxHealth_319: out = fn_giveMaxHealth(args, argc); return true;
        case SYM_GEN_giveStamina_320: out = fn_giveStamina(args, argc); return true;
        case SYM_GEN_inflictFatigueDamage_321: out = fn_inflictFatigueDamage(args, argc); return true;
        case SYM_GEN_sendCharge_322: out = fn_sendCharge(args, argc); return true;
        case SYM_GEN__chargeInventoryCells_323: out = fn__chargeInventoryCells(args, argc); return true;
        case SYM_GEN__rotVecQuarterTurns_324: out = fn__rotVecQuarterTurns(args, argc); return true;
        case SYM_GEN__chargeEnterCell_325: out = fn__chargeEnterCell(args, argc); return true;
        case SYM_GEN_chargeReceived_326: out = fn_chargeReceived(args, argc); return true;
        case SYM_GEN_chargeLeft_327: out = fn_chargeLeft(args, argc); return true;
        case SYM_GEN_changeChargedItemStat_328: out = fn_changeChargedItemStat(args, argc); return true;
        case SYM_GEN_heal_329: out = fn_heal(args, argc); return true;
        case SYM_GEN_healthToBlock_330: out = fn_healthToBlock(args, argc); return true;
        case SYM_GEN_stealLife_331: out = fn_stealLife(args, argc); return true;
        case SYM_GEN_stun_332: out = fn_stun(args, argc); return true;
        case SYM_GEN_checkMana_333: out = fn_checkMana(args, argc); return true;
        case SYM_GEN_useMana_334: out = fn_useMana(args, argc); return true;
        case SYM_GEN_tryUseMana_335: out = fn_tryUseMana(args, argc); return true;
        case SYM_GEN_removeMana_336: out = fn_removeMana(args, argc); return true;
        case SYM_GEN_giveMana_capped_337: out = fn_giveMana_capped(args, argc); return true;
        case SYM_GEN_removeSpikes_338: out = fn_removeSpikes(args, argc); return true;
        case SYM_GEN_useSpikes_339: out = fn_useSpikes(args, argc); return true;
        case SYM_GEN_loseSpikes_340: out = fn_loseSpikes(args, argc); return true;
        case SYM_GEN_removeVampirism_341: out = fn_removeVampirism(args, argc); return true;
        case SYM_GEN_useVampirism_342: out = fn_useVampirism(args, argc); return true;
        case SYM_GEN_loseVampirism_343: out = fn_loseVampirism(args, argc); return true;
        case SYM_GEN_cleansePoison_344: out = fn_cleansePoison(args, argc); return true;
        case SYM_GEN_selfInflictBlind_345: out = fn_selfInflictBlind(args, argc); return true;
        case SYM_GEN_cleanseBlind_346: out = fn_cleanseBlind(args, argc); return true;
        case SYM_GEN_removeRegeneration_347: out = fn_removeRegeneration(args, argc); return true;
        case SYM_GEN_useRegeneration_348: out = fn_useRegeneration(args, argc); return true;
        case SYM_GEN_tryUseLucky_349: out = fn_tryUseLucky(args, argc); return true;
        case SYM_GEN_loseLucky_350: out = fn_loseLucky(args, argc); return true;
        case SYM_GEN_removeLucky_351: out = fn_removeLucky(args, argc); return true;
        case SYM_GEN_useLucky_352: out = fn_useLucky(args, argc); return true;
        case SYM_GEN_inflictCold_353: out = fn_inflictCold(args, argc); return true;
        case SYM_GEN_cleanseCold_354: out = fn_cleanseCold(args, argc); return true;
        case SYM_GEN_loseHeat_355: out = fn_loseHeat(args, argc); return true;
        case SYM_GEN_useHeat_356: out = fn_useHeat(args, argc); return true;
        case SYM_GEN_loseEmpower_357: out = fn_loseEmpower(args, argc); return true;
        case SYM_GEN_cleanseRandomDebuffs_358: out = fn_cleanseRandomDebuffs(args, argc); return true;
        case SYM_GEN_inflictRandomDebuffs_359: out = fn_inflictRandomDebuffs(args, argc); return true;
        case SYM_GEN_pickRandomStacks_360: out = fn_pickRandomStacks(args, argc); return true;
        case SYM_GEN_pickRandomStacksToGive_361: out = fn_pickRandomStacksToGive(args, argc); return true;
        case SYM_GEN_getLeastStacks_362: out = fn_getLeastStacks(args, argc); return true;
        case SYM_GEN_getMostStacks_363: out = fn_getMostStacks(args, argc); return true;
        case SYM_GEN_getStackFraction_364: out = fn_getStackFraction(args, argc); return true;
        case SYM_GEN_multiplyBuffsLimit_365: out = fn_multiplyBuffsLimit(args, argc); return true;
        case SYM_GEN_removeBuffsFraction_366: out = fn_removeBuffsFraction(args, argc); return true;
        case SYM_GEN_stealBuffsFraction_367: out = fn_stealBuffsFraction(args, argc); return true;
        case SYM_GEN_giveLeastBuffs_368: out = fn_giveLeastBuffs(args, argc); return true;
        case SYM_GEN_giveMostBuffs_369: out = fn_giveMostBuffs(args, argc); return true;
        case SYM_GEN_removeMostBuffs_370: out = fn_removeMostBuffs(args, argc); return true;
        case SYM_GEN_giveRandomBuffs_371: out = fn_giveRandomBuffs(args, argc); return true;
        case SYM_GEN_giveAllBuffs_372: out = fn_giveAllBuffs(args, argc); return true;
        case SYM_GEN_useRandomBuffs_373: out = fn_useRandomBuffs(args, argc); return true;
        case SYM_GEN_removeRandomBuffs_374: out = fn_removeRandomBuffs(args, argc); return true;
        case SYM_GEN_stealRandomBuff_375: out = fn_stealRandomBuff(args, argc); return true;
        case SYM_GEN_connectToCharacterBuffs_376: out = fn_connectToCharacterBuffs(args, argc); return true;
        case SYM_GEN_connectToCharacterDebuffs_377: out = fn_connectToCharacterDebuffs(args, argc); return true;
        case SYM_GEN_connectToOpponentDebuffs_378: out = fn_connectToOpponentDebuffs(args, argc); return true;
        case SYM_GEN_connectToOpponentBuffs_379: out = fn_connectToOpponentBuffs(args, argc); return true;
        case SYM_GEN_getNextFreeLabelPosition_380: out = fn_getNextFreeLabelPosition(args, argc); return true;
        case SYM_GEN_spawnLabel_381: out = fn_spawnLabel(args, argc); return true;
        case SYM_GEN_spawnLabel_other_382: out = fn_spawnLabel_other(args, argc); return true;
        case SYM_GEN_consume_383: out = fn_consume(args, argc); return true;
        case SYM_GEN_setState_384: out = fn_setState(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_onTemporaryStacksTimeout_386: out = fn_onTemporaryStacksTimeout(args, argc); return true;
        case SYM_GEN_empowerEnd_387: out = fn_empowerEnd(args, argc); return true;
        case SYM_GEN_hasSockets_388: out = fn_hasSockets(args, argc); return true;
        case SYM_GEN_getNumSockets_389: out = fn_getNumSockets(args, argc); return true;
        case SYM_GEN_initSockets_390: out = fn_initSockets(args, argc); return true;
        case SYM_GEN_getItem_391: out = fn_getItem(args, argc); return true;
        case SYM_GEN_hasGems_392: out = fn_hasGems(args, argc); return true;
        case SYM_GEN_getGemsOfItems_393: out = fn_getGemsOfItems(args, argc); return true;
        case SYM_GEN_getPrice_394: out = fn_getPrice(args, argc); return true;
        case SYM_GEN_getBaseSellPrice_395: out = fn_getBaseSellPrice(args, argc); return true;
        case SYM_GEN_getSellPrice_396: out = fn_getSellPrice(args, argc); return true;
        case SYM_GEN_getSalePrice_397: out = fn_getSalePrice(args, argc); return true;
        case SYM_GEN_setGem_398: out = fn_setGem(args, argc); return true;
        case SYM_GEN_pushGemsToStorage_399: out = fn_pushGemsToStorage(args, argc); return true;
        case SYM_GEN_pushItemsInsideToStorage_400: out = fn_pushItemsInsideToStorage(args, argc); return true;
        case SYM_GEN_returnToSocket_401: out = fn_returnToSocket(args, argc); return true;
        case SYM_GEN_getOwnOrPlayerInventory_402: out = fn_getOwnOrPlayerInventory(args, argc); return true;
        case SYM_GEN_getCellsForGlobalPositions_403: out = fn_getCellsForGlobalPositions(args, argc); return true;
        case SYM_GEN_getGlobalPointsForCells_404: out = fn_getGlobalPointsForCells(args, argc); return true;
        case SYM_GEN_getGlobalPointsForCells_noRotate_405: out = fn_getGlobalPointsForCells_noRotate(args, argc); return true;
        case SYM_GEN_getCollisionCells_406: out = fn_getCollisionCells(args, argc); return true;
        case SYM_GEN_getExtensionCells_407: out = fn_getExtensionCells(args, argc); return true;
        case SYM_GEN_getCollisionPoints_408: out = fn_getCollisionPoints(args, argc); return true;
        case SYM_GEN_getExtensionPoints_409: out = fn_getExtensionPoints(args, argc); return true;
        case SYM_GEN_getAffectedCells_tilemap_410: out = fn_getAffectedCells_tilemap(args, argc); return true;
        case SYM_GEN_getAffectedCellsAfterRotate_411: out = fn_getAffectedCellsAfterRotate(args, argc); return true;
        case SYM_GEN_getAffectedCellsAfterRotate_primary_412: out = fn_getAffectedCellsAfterRotate_primary(args, argc); return true;
        case SYM_GEN_getAffectedCellsAfterRotate_secondary_413: out = fn_getAffectedCellsAfterRotate_secondary(args, argc); return true;
        case SYM_GEN_getAffectedCells_noRotate_414: out = fn_getAffectedCells_noRotate(args, argc); return true;
        case SYM_GEN_getAffectedPoints_415: out = fn_getAffectedPoints(args, argc); return true;
        case SYM_GEN_getAffectedCellsInInventory_416: out = fn_getAffectedCellsInInventory(args, argc); return true;
        case SYM_GEN_getAffectedCellsInInventory_cached_417: out = fn_getAffectedCellsInInventory_cached(args, argc); return true;
        case SYM_GEN_cacheAffectedCells_418: out = fn_cacheAffectedCells(args, argc); return true;
        case SYM_GEN_cleanCachedAffectedItems_419: out = fn_cleanCachedAffectedItems(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_420: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_onAddToInventory_421: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_getAffectedItems_422: out = fn_getAffectedItems(args, argc); return true;
        case SYM_GEN_getAffectedItems_nocache_423: out = fn_getAffectedItems_nocache(args, argc); return true;
        case SYM_GEN_getItemsInAffectedCells_424: out = fn_getItemsInAffectedCells(args, argc); return true;
        case SYM_GEN_getItemsInAffectedCells_cached_425: out = fn_getItemsInAffectedCells_cached(args, argc); return true;
        case SYM_GEN_countItemsInAffectedCells_cached_426: out = fn_countItemsInAffectedCells_cached(args, argc); return true;
        case SYM_GEN_isItemAffected_427: out = fn_isItemAffected(args, argc); return true;
        case SYM_GEN_getNumEmptyAffectedCells_428: out = fn_getNumEmptyAffectedCells(args, argc); return true;
        case SYM_GEN_getNumAffectedItems_429: out = fn_getNumAffectedItems(args, argc); return true;
        case SYM_GEN_getFirstAffectedItem_430: out = fn_getFirstAffectedItem(args, argc); return true;
        case SYM_GEN_getNumAffected_type_431: out = fn_getNumAffected_type(args, argc); return true;
        case SYM_GEN_getNumDistinctAffectedItems_432: out = fn_getNumDistinctAffectedItems(args, argc); return true;
        case SYM_GEN_getNumAffectedCells_433: out = fn_getNumAffectedCells(args, argc); return true;
        case SYM_GEN_activateExtendedAffectedCells_434: out = fn_activateExtendedAffectedCells(args, argc); return true;
        case SYM_GEN_deactivateExtendedAffectedCells_435: out = fn_deactivateExtendedAffectedCells(args, argc); return true;
        case SYM_GEN_canAffectDraggedItem_436: out = fn_canAffectDraggedItem(args, argc); return true;
        case SYM_GEN_onAffectedItemAdded_437: out = fn_onAffectedItemAdded(args, argc); return true;
        case SYM_GEN_onAffectedItemRemoved_438: out = fn_onAffectedItemRemoved(args, argc); return true;
        case SYM_GEN_onItemAdded_439: out = fn_onItemAdded(args, argc); return true;
        case SYM_GEN_onItemRemoved_440: out = fn_onItemRemoved(args, argc); return true;
        case SYM_GEN_getNumOccupiedCells_441: out = fn_getNumOccupiedCells(args, argc); return true;
        case SYM_GEN_getNumBagCells_442: out = fn_getNumBagCells(args, argc); return true;
        case SYM_GEN_getNumCells_443: out = fn_getNumCells(args, argc); return true;
        case SYM_GEN_getSizeInCells_444: out = fn_getSizeInCells(args, argc); return true;
        case SYM_GEN_getTopLeftCell_445: out = fn_getTopLeftCell(args, argc); return true;
        case SYM_GEN_getNormalizedCollisionCells_446: out = fn_getNormalizedCollisionCells(args, argc); return true;
        case SYM_GEN_canCombine_447: out = fn_canCombine(args, argc); return true;
        case SYM_GEN_prepareReplacement_448: out = fn_prepareReplacement(args, argc); return true;
        case SYM_GEN_finishReplacement_449: out = fn_finishReplacement(args, argc); return true;
        case SYM_GEN_placeGeneratedItem_450: out = fn_placeGeneratedItem(args, argc); return true;
        case SYM_GEN_moveTo_451: out = fn_moveTo(args, argc); return true;
        case SYM_GEN_resetZ_452: out = fn_resetZ(args, argc); return true;
        case SYM_GEN_onGateItemRoll_453: out = fn_onGateItemRoll(args, argc); return true;
        case SYM_GEN_insertCounter_454: out = fn_insertCounter(args, argc); return true;
        case SYM_GEN_queue_free_455: out = fn_queue_free(args, argc); return true;
        case SYM_GEN_shift_456: out = fn_shift(args, argc); return true;
        case SYM_GEN_onBought_457: out = fn_onBought(args, argc); return true;
        case SYM_GEN_onSold_458: out = fn_onSold(args, argc); return true;
        case SYM_GEN_reactToItemTypeChange_459: out = fn_reactToItemTypeChange(args, argc); return true;
        case SYM_GEN_onItemTypeChanged_460: out = fn_onItemTypeChanged(args, argc); return true;
        case SYM_GEN_getRelatedItems_461: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN_countAllPlacedOfType_462: out = fn_countAllPlacedOfType(args, argc); return true;
        case SYM_GEN_getTouchedBagsCounted_463: out = fn_getTouchedBagsCounted(args, argc); return true;
        case SYM_GEN_getHeightRange_464: out = fn_getHeightRange(args, argc); return true;
        case SYM_GEN_ready_deferred_465: out = fn_ready_deferred(args, argc); return true;
        case SYM_GEN_rotationFromFaceDirection_466: out = fn_rotationFromFaceDirection(args, argc); return true;
        case SYM_GEN_getFaceDirection_467: out = fn_getFaceDirection(args, argc); return true;
        case SYM_GEN_getGlobalFaceDirection_468: out = fn_getGlobalFaceDirection(args, argc); return true;
        case SYM_GEN_setFaceDirectionInstant_469: out = fn_setFaceDirectionInstant(args, argc); return true;
        case SYM_GEN_setRotation_470: out = fn_setRotation(args, argc); return true;
        case SYM_GEN_changeAllItemsCritRate_471: out = fn_changeAllItemsCritRate(args, argc); return true;
        case SYM_GEN_miniActivate_472: out = fn_miniActivate(args, argc); return true;
        case SYM_GEN_previewCellCollision_473: out = fn_previewCellCollision(args, argc); return true;
        case SYM_GEN_previewCells_474: out = fn_previewCells(args, argc); return true;
        case SYM_GEN_previewCanAffect_475: out = fn_previewCanAffect(args, argc); return true;
        case SYM_GEN_rotateRight_476: out = fn_rotateRight(args, argc); return true;
        case SYM_GEN_rotateLeft_477: out = fn_rotateLeft(args, argc); return true;
        case SYM_GEN_rotateTo_478: out = fn_rotateTo(args, argc); return true;
        case SYM_GEN_rotateToDeferred_479: out = fn_rotateToDeferred(args, argc); return true;
        case SYM_GEN_setFaceDirection_480: out = fn_setFaceDirection(args, argc); return true;
        case SYM_GEN_correctInsideItemFacedirection_481: out = fn_correctInsideItemFacedirection(args, argc); return true;
        case SYM_GEN_getBagEffect_482: out = fn_getBagEffect(args, argc); return true;
        case SYM_GEN_getGemData_483: out = fn_getGemData(args, argc); return true;
        case SYM_GEN_setGemData_484: out = fn_setGemData(args, argc); return true;
        case SYM_GEN_reconstructCooldown_485: out = fn_reconstructCooldown(args, argc); return true;
        case SYM_GEN_findBondsWithAffectedItems_486: out = fn_findBondsWithAffectedItems(args, argc); return true;
        case SYM_GEN_rotateProgress_487: out = fn_rotateProgress(args, argc); return true;
        case SYM_GEN_cacheCollisionCells_488: out = fn_cacheCollisionCells(args, argc); return true;
        case SYM_GEN_isBaseItemForShopItem_489: out = fn_isBaseItemForShopItem(args, argc); return true;
        case SYM_GEN_activateFromEvent_490: out = fn_activateFromEvent(args, argc); return true;
        case SYM_GEN_getNeighborItemsAndGems_491: out = fn_getNeighborItemsAndGems(args, argc); return true;
        case SYM_GEN_getTouchedBags_492: out = fn_getTouchedBags(args, argc); return true;
        case SYM_GEN_getBusyNeighbors_493: out = fn_getBusyNeighbors(args, argc); return true;
        case SYM_GEN_getCraftableNeighbors_494: out = fn_getCraftableNeighbors(args, argc); return true;
        case SYM_GEN_isAvailableForCrafting_495: out = fn_isAvailableForCrafting(args, argc); return true;
        case SYM_GEN_getAffectedGoldValue_496: out = fn_getAffectedGoldValue(args, argc); return true;
        case SYM_GEN_countTypes_497: out = fn_countTypes(args, argc); return true;
        case SYM_GEN_hasSameOrientationAsPickup_498: out = fn_hasSameOrientationAsPickup(args, argc); return true;
        case SYM_GEN_getGemsNoNull_499: out = fn_getGemsNoNull(args, argc); return true;
        case SYM_GEN_getGems_500: out = fn_getGems(args, argc); return true;
        case SYM_GEN_buildDamageSource_501: out = fn_buildDamageSource(args, argc); return true;
        case SYM_GEN_connectForCombat_502: out = fn_connectForCombat(args, argc); return true;
        case SYM_GEN_connectForCombat_signal_503: out = fn_connectForCombat_signal(args, argc); return true;
        case SYM_GEN_disconnectCombat_504: out = fn_disconnectCombat(args, argc); return true;
        case SYM_GEN__hasBehaviorMethod_505: out = fn__hasBehaviorMethod(args, argc); return true;
        case SYM_GEN__behavior_call_506: out = fn__behavior_call(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItem::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getNumNonStackItemMetrics_228: out = sf_getNumNonStackItemMetrics(gd_ctx, args, argc); return true;
        case SYM_GEN_getNumItemMetrics_229: out = sf_getNumItemMetrics(gd_ctx, args, argc); return true;
        case SYM_GEN_getStackMetricIndex_230: out = sf_getStackMetricIndex(gd_ctx, args, argc); return true;
        case SYM_GEN_getMultiMetricIndex_231: out = sf_getMultiMetricIndex(gd_ctx, args, argc); return true;
        default: break;
    }
    return false;
}
gd::GdVal Gd__gd_core__CoreItem::fn__init(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__ctx = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv__descriptor = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv__character = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv__descriptor, gd::GdVal::null())))) {
        return gd::GdVal::null();
    }
    (void)([&]() { gd::GdVal _ca[] = {lv__ctx, lv__descriptor, lv__character}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setup_74, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_setup(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__ctx = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__descriptor = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv__character = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    this->f_ctx = lv__ctx;
    this->f_descriptor = lv__descriptor;
    this->f_character_ = lv__character;
    this->f_name = gd::get_prop(gd_ctx, lv__descriptor, SYM_GEN_name_7);
    this->f_chanceRng = ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_BalancedRng_1653), gd::SYM_new, _ca, 1); })();
    this->f_damageRangeRng = ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_BalancedRange_1654), gd::SYM_new, _ca, 1); })();
    {
        gd::GdVal _t1 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::gd_max(gd::GdVal::from_int(0LL), gd::gd_sub(gd::gd_coerce_int(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_sceneDepth_1607)), gd::GdVal::from_int(1LL)))}; return gd::gd_range(gd_ctx.arena, _ca, 1); })());
        gd::GdArr* _t2 = (_t1.kind == gd::GdVal::Kind::Arr) ? _t1.arr : nullptr;
        uint32_t _len__t3 = _t2 ? _t2->len : 0u;
        for (uint32_t _t3 = 0; _t3 < _len__t3; ++_t3) {
            gd::GdVal lv__i = _t2->data[_t3];
            this->f_chanceRng = ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_BalancedRng_1653), gd::SYM_new, _ca, 1); })();
        }
    }
    this->f_baseCooldownOverride = gd::gd_coerce_float(gd::get_prop(gd_ctx, lv__descriptor, SYM_GEN_cd_1583));
    {
        gd::GdVal _t4 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getStacks_1022, nullptr, 0));
        gd::GdArr* _t5 = (_t4.kind == gd::GdVal::Kind::Arr) ? _t4.arr : nullptr;
        uint32_t _len__t6 = _t5 ? _t5->len : 0u;
        for (uint32_t _t6 = 0; _t6 < _len__t6; ++_t6) {
            gd::GdVal lv_buff = _t5->data[_t6];
            { gd::GdVal _t7 = this->f_buffPowers; gd::GdVal _t8 = lv_buff; gd::set_index(gd_ctx, _t7, _t8, gd::GdVal::from_float(1.0)); }
            { gd::GdVal _t9 = this->f_buffAmplificationChances; gd::GdVal _t10 = lv_buff; gd::set_index(gd_ctx, _t9, _t10, gd::GdVal::from_float(0.0)); }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreItem::call_static_fn(gd_ctx, SYM_GEN_getNumItemMetrics_229, nullptr, 0, _out); return _out; })()}; return gd::call_method(gd_ctx, this->f_itemMetrics, gd::SYM_resize, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, this->f_itemMetrics, gd::SYM_fill, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), gd::SYM_size, nullptr, 0)}; return gd::call_method(gd_ctx, this->f_statDisplayOverrides, gd::SYM_resize, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null()}; return gd::call_method(gd_ctx, this->f_statDisplayOverrides, gd::SYM_fill, _ca, 1); })();
    {
        gd::GdVal _t11 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), gd::SYM_values, nullptr, 0));
        gd::GdArr* _t12 = (_t11.kind == gd::GdVal::Kind::Arr) ? _t11.arr : nullptr;
        uint32_t _len__t13 = _t12 ? _t12->len : 0u;
        for (uint32_t _t13 = 0; _t13 < _len__t13; ++_t13) {
            gd::GdVal lv_color = _t12->data[_t13];
            { gd::GdVal _t14 = this->f_currentAffectedItems; gd::GdVal _t15 = lv_color; gd::set_index(gd_ctx, _t14, _t15, gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena))); }
        }
    }
    return gd::GdVal::from_obj(this);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_hasCharacter(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(this->f_placed) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_character_, gd::GdVal::null())))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_character(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_character_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_opponent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {this->f_character_}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_otherCharacter_1418, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isPlaced(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_placed;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isCoreItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isPlayer(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_character_, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, this->f_character_, SYM_GEN_playerId_1046), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_CharID_1368), SYM_GEN_PLAYER_2540))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_hasType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    return (gd::gd_truth(gd::gd_in(lv_type, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_types_1453))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::gd_in(lv_type, this->f_dynamicTypes))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getTypeMultiplicity(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_type}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasType_81, _ca, 1); })()) ? (gd::GdVal::from_int(1LL)) : (gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_hasTag(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_tag = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_tag}; return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_hasTag_83, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_isWeapon_84, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isBag(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isGem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isBattleRageItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_hasBattleRageEffect_1594);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_gainsStack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stackType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::gd_bitand(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_gainedStacks_1618), lv_stackType);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_removesStack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stackType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::gd_bitand(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_removedStacks_1619), lv_stackType);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_usesStack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stackType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::gd_bitand(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_usedStacks_1620), lv_stackType);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "getTriggerPriority", 18u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_505, _ca, 1); })())) {
        return gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "getTriggerPriority", 18u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_506, _ca, 2); })());
    }
    return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_856), SYM_GEN_Normal_2541);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseMinDamage_154, nullptr, 0), gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Tag_858), SYM_GEN_Lifesteal_2542)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasTag_83, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canBeEmpowered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isWeapon_84, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canDamage_91, nullptr, 0))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canActivate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_canActivate_93);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getSpeed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_override = gd::get_index(gd_ctx, this->f_statDisplayOverrides, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_Speed_2543));
    if (gd::gd_truth(lv_override)) {
        return lv_override;
    }
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasCharacter_75, nullptr, 0))) {
        gd::GdVal lv_speed_ = gd::gd_add(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_speed_95, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStackSpeedMods_96, nullptr, 0));
        gd::GdVal lv_modifiedSpeed = gd::GdVal::from_float(0.0);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_speed_, gd::GdVal::from_int(0LL))))) {
            lv_modifiedSpeed = gd::gd_coerce_float(gd::gd_add(gd_ctx, gd::GdVal::from_float(1.0), lv_speed_));
        }
        else {
            lv_modifiedSpeed = gd::gd_coerce_float(gd::gd_div(gd_ctx, gd::GdVal::from_float(1.0), gd::gd_sub(gd::GdVal::from_float(1.0), lv_speed_)));
        }
        lv_modifiedSpeed = gd::gd_coerce_float(gd::gd_clamp(lv_modifiedSpeed, gd::GdVal::from_float(0.1), gd::GdVal::from_float(10.0)));
        return lv_modifiedSpeed;
    }
    else {
        return gd::GdVal::from_float(1.0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_speed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_speedScale;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getStackSpeedMods(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_mul(gd::gd_sub(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getHeat_1235, nullptr, 0), gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getCold_1238, nullptr, 0)), gd::GdVal::from_float(0.02));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_hasCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_cd_1583), gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isCooldownActive(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f__cooldown_active;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_setCooldownActive(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_active = gd::gd_coerce_bool(lv_active);
    this->f__cooldown_active = lv_active;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_activateCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f__cooldown_active = gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_deactivateCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f__cooldown_active = gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBaseCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_baseCooldownOverride;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBaseCooldownIndex(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_index = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_index = gd::gd_coerce_int(lv_index);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_index, gd::GdVal::from_int(0LL))))) {
        return gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_cd_1583);
    }
    else {
        return gd::get_index(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_extraCds_1584), gd::gd_sub(lv_index, gd::GdVal::from_int(1LL)));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_override = gd::get_index(gd_ctx, this->f_statDisplayOverrides, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_BaseCooldown_2544));
    if (gd::gd_truth(lv_override)) {
        return lv_override;
    }
    return this->f_baseCooldownOverride;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getCooldownIndex(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_index = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_index = gd::gd_coerce_int(lv_index);
    return ([&]() { gd::GdVal _ca[] = {lv_index}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldownIndex_103, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getModifiedCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCooldown_104, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getSpeed_94, nullptr, 0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getModifiedCooldownIndex(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_index = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_index = gd::gd_coerce_int(lv_index);
    return gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_index}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCooldownIndex_105, _ca, 1); })(), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getSpeed_94, nullptr, 0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getCooldownEncoded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_iterationCooldown, gd::GdVal::from_int(0LL))))) {
        return gd::gd_neg(gd::GdVal::from_int(1LL));
    }
    gd::GdVal lv_relProgress = gd::gd_sub(gd::GdVal::from_float(1.0), gd::gd_div(gd_ctx, this->f_triggerTime, this->f_iterationCooldown));
    gd::GdVal lv_progressPerSecond = gd::GdVal::from_float(0.0);
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isCooldownActive_98, nullptr, 0))) {
        lv_progressPerSecond = gd::gd_coerce_float(gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getSpeed_94, nullptr, 0), this->f_iterationCooldown));
    }
    else {
        lv_progressPerSecond = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    }
    gd::GdVal lv_value = gd::gd_shl(gd::gd_coerce_int(gd::gd_mul(lv_relProgress, Gd__gd_core__CoreItem::get_static_const_or_enum(gd_ctx, SYM_GEN_cdEncodingFactor_1))), gd::GdVal::from_int(32LL));
    lv_value = gd::gd_add(gd_ctx, lv_value, gd::gd_coerce_int(gd::gd_mul(lv_progressPerSecond, Gd__gd_core__CoreItem::get_static_const_or_enum(gd_ctx, SYM_GEN_cdEncodingFactor_1))));
    return lv_value;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_adjustCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_adjustedCooldown = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCooldown_104, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_Opponent_2545)))) ? gd::GdVal::from_bool(gd::gd_truth((gd::gd_truth(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_below_master_1385)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_lobbies_mode_1387)))))) : gd::GdVal::from_bool(false)))) {
        lv_adjustedCooldown = gd::gd_mul(lv_adjustedCooldown, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.975), gd::GdVal::from_float(1.05)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })());
    }
    else {
        lv_adjustedCooldown = gd::gd_mul(lv_adjustedCooldown, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.95), gd::GdVal::from_float(1.05)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })());
    }
    return lv_adjustedCooldown;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_setBaseCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_newBaseCd = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_baseCooldownOverride = gd::gd_coerce_float(lv_newBaseCd);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateBaseCooldown_112, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_resetBaseCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_cd_1583)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setBaseCooldown_110, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_updateBaseCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_cdProgress = gd::gd_div(gd_ctx, this->f_triggerTime, this->f_iterationCooldown);
    this->f_iterationCooldown = gd::gd_coerce_float(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_adjustCooldown_109, nullptr, 0));
    this->f_triggerTime = gd::gd_coerce_float(gd::gd_mul(lv_cdProgress, this->f_iterationCooldown));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_Cooldown_2546)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_BaseCooldown_2544)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBaseStaminaCost(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_staminaCost_1581);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getStaminaCost(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_override = gd::get_index(gd_ctx, this->f_statDisplayOverrides, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_StaminaCost_2547));
    if (gd::gd_truth(lv_override)) {
        return lv_override;
    }
    return gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseStaminaCost_113, nullptr, 0), this->f_staminaFactor);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isStaminaModified(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::gd_sub(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseStaminaCost_113, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStaminaCost_114, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isStatModified_116, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isStatModified(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_statVal = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_statVal, gd::GdVal::from_int(0LL))))) {
        return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_864), SYM_GEN_No_2548);
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_statVal, gd::GdVal::from_int(0LL))))) {
        return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_864), SYM_GEN_Positive_2549);
    }
    else {
        return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_864), SYM_GEN_Negative_2550);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_setStat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stat = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_value = (_argc > 1) ? _args[1] : gd::GdVal::null();
    { gd::GdVal _t16 = this->f_statDisplayOverrides; gd::GdVal _t17 = lv_stat; gd::set_index(gd_ctx, _t16, _t17, lv_value); }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_queueTooltipUpdate_708, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_useStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_amount, gd::GdVal::null())))) {
        lv_amount = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStaminaCost_114, nullptr, 0);
    }
    gd::GdVal lv_res = ([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_useStamina_118, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_res, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StaminaResult_1280), SYM_GEN_Insufficient_2551))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemMetrics_1367), SYM_GEN_OutOfStamina_2552), gd::GdVal::from_int(1LL), gd::GdVal::null(), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addMetric_232, _ca, 4); })();
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_playerId_1046)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_createEvent_OutOfStamina_1344, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_logEvent_1328, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_Cooldown_2546)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playOutOfStaminaAnimation_120, nullptr, 0);
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "used_stamina", 12u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_amount}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitSignal_1501, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StackChangeType_871), SYM_GEN_Used_Player_2553), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_staminaChanged_235, _ca, 3); })();
    }
    return lv_res;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_drainStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_drainStamina_119, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_playOutOfStaminaAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isPlayer_80, nullptr, 0))) {
        gd::set_prop(gd_ctx, this->f_ctx, SYM_GEN_out_of_stamina_count_1404, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_out_of_stamina_count_1404), gd::GdVal::from_int(1LL)));
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_playOutOfStaminaAnimation_120, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_cacheAffectedItemsForCombat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t18 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), gd::SYM_values, nullptr, 0));
        gd::GdArr* _t19 = (_t18.kind == gd::GdVal::Kind::Arr) ? _t18.arr : nullptr;
        uint32_t _len__t20 = _t19 ? _t19->len : 0u;
        for (uint32_t _t20 = 0; _t20 < _len__t20; ++_t20) {
            gd::GdVal lv_color = _t19->data[_t20];
            { gd::GdVal _t21 = this->f_cachedAffectedItems; gd::GdVal _t22 = lv_color; gd::set_index(gd_ctx, _t21, _t22, gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_currentAffectedItems, lv_color), gd::SYM_keys, nullptr, 0)); }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__inventory = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__occupiedCells = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv__placedByPlayer = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv__placedByPlayer = gd::gd_coerce_bool(lv__placedByPlayer);
    this->f_placedByPlayer = lv__placedByPlayer;
    this->f_placed = gd::GdVal::from_bool(true);
    this->f_inventory = lv__inventory;
    this->f_occupiedCells = lv__occupiedCells;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_BuildViewer_2554))))) {
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1284), gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_inventory, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1284), SYM_GEN_inventory_5))))) : gd::GdVal::from_bool(false)))) {
            this->f_ownerType = gd::gd_coerce_int(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_PlayerInventory_2555));
        }
        else if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_opponent_77), gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_inventory, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_opponent_77), SYM_GEN_inventory_5))))) : gd::GdVal::from_bool(false)))) {
            this->f_ownerType = gd::gd_coerce_int(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_Opponent_2545));
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cacheAffectedCells_418, nullptr, 0);
    {
        gd::GdVal _t23 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), gd::SYM_values, nullptr, 0));
        gd::GdArr* _t24 = (_t23.kind == gd::GdVal::Kind::Arr) ? _t23.arr : nullptr;
        uint32_t _len__t25 = _t24 ? _t24->len : 0u;
        for (uint32_t _t25 = 0; _t25 < _len__t25; ++_t25) {
            gd::GdVal lv_color = _t24->data[_t25];
            {
                gd::GdVal _t26 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, _ca, 1); })());
                gd::GdArr* _t27 = (_t26.kind == gd::GdVal::Kind::Arr) ? _t26.arr : nullptr;
                uint32_t _len__t28 = _t27 ? _t27->len : 0u;
                for (uint32_t _t28 = 0; _t28 < _len__t28; ++_t28) {
                    gd::GdVal lv_item = _t27->data[_t28];
                    { gd::GdVal _t29 = gd::get_index(gd_ctx, this->f_currentAffectedItems, lv_color); gd::GdVal _t30 = lv_item; gd::set_index(gd_ctx, _t29, _t30, gd::GdVal::from_bool(true)); }
                    (void)([&]() { gd::GdVal _ca[] = {lv_item, lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAffectedItemAdded_437, _ca, 2); })();
                }
            }
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAddToInventory_421, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_registerWithInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_inventory, this->f_occupiedCells, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addToInventory_122, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cacheAffectedItemsForCombat_121, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_chanceRng, SYM_GEN_reset_1024, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_damageRangeRng, SYM_GEN_reset_1024, nullptr, 0);
    {
        gd::GdVal _t31 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemsNoNull_499, nullptr, 0));
        gd::GdArr* _t32 = (_t31.kind == gd::GdVal::Kind::Arr) ? _t31.arr : nullptr;
        uint32_t _len__t33 = _t32 ? _t32->len : 0u;
        for (uint32_t _t33 = 0; _t33 < _len__t33; ++_t33) {
            gd::GdVal lv_gem = _t32->data[_t33];
            (void)gd::call_method(gd_ctx, lv_gem, SYM_GEN_prepare_124, nullptr, 0);
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onPrepare_125, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_preCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t34 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemsNoNull_499, nullptr, 0));
        gd::GdArr* _t35 = (_t34.kind == gd::GdVal::Kind::Arr) ? _t34.arr : nullptr;
        uint32_t _len__t36 = _t35 ? _t35->len : 0u;
        for (uint32_t _t36 = 0; _t36 < _len__t36; ++_t36) {
            gd::GdVal lv_gem = _t35->data[_t36];
            (void)gd::call_method(gd_ctx, lv_gem, SYM_GEN_preCombatStart_126, nullptr, 0);
        }
    }
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasCooldown_97, nullptr, 0))) {
        this->f_iterationCooldown = gd::gd_coerce_float(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_adjustCooldown_109, nullptr, 0));
        this->f_triggerTime = gd::gd_coerce_float(this->f_iterationCooldown);
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activateCooldown_100, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_Cooldown_2546)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onPreCombatStart_127, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_hasStartofBattle(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onCombatStart", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_505, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_combatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t37 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemsNoNull_499, nullptr, 0));
        gd::GdArr* _t38 = (_t37.kind == gd::GdVal::Kind::Arr) ? _t37.arr : nullptr;
        uint32_t _len__t39 = _t38 ? _t38->len : 0u;
        for (uint32_t _t39 = 0; _t39 < _len__t39; ++_t39) {
            gd::GdVal lv_gem = _t38->data[_t39];
            (void)gd::call_method(gd_ctx, lv_gem, SYM_GEN_combatStart_129, nullptr, 0);
        }
    }
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasStartofBattle_128, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onCombatStart", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_506, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_postCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t40 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemsNoNull_499, nullptr, 0));
        gd::GdArr* _t41 = (_t40.kind == gd::GdVal::Kind::Arr) ? _t40.arr : nullptr;
        uint32_t _len__t42 = _t41 ? _t41->len : 0u;
        for (uint32_t _t42 = 0; _t42 < _len__t42; ++_t42) {
            gd::GdVal lv_gem = _t41->data[_t42];
            (void)gd::call_method(gd_ctx, lv_gem, SYM_GEN_postCombatStart_130, nullptr, 0);
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onPostCombatStart_131, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onPostCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_repeatCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onPreCombatStart_127, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onCombatStart", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_506, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onPostCombatStart_131, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_combatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setCooldownActive_99, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_disconnectCombat_504, nullptr, 0);
    {
        gd::GdVal _t43 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemsNoNull_499, nullptr, 0));
        gd::GdArr* _t44 = (_t43.kind == gd::GdVal::Kind::Arr) ? _t43.arr : nullptr;
        uint32_t _len__t45 = _t44 ? _t44->len : 0u;
        for (uint32_t _t45 = 0; _t45 < _len__t45; ++_t45) {
            gd::GdVal lv_gem = _t44->data[_t45];
            (void)gd::call_method(gd_ctx, lv_gem, SYM_GEN_combatEnd_133, nullptr, 0);
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onCombatEnd_134, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_resetCombatState(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_baseCooldownOverride = gd::gd_coerce_float(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_cd_1583));
    this->f_speedScale = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusMinDam = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    this->f_bonusMaxDam = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    this->f_removableDam = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    this->f_bonusDamageFactor = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_staminaFactor = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    {
        gd::GdVal _t46 = gd::gd_iter_seq(gd_ctx.arena, this->f_buffPowers);
        gd::GdArr* _t47 = (_t46.kind == gd::GdVal::Kind::Arr) ? _t46.arr : nullptr;
        uint32_t _len__t48 = _t47 ? _t47->len : 0u;
        for (uint32_t _t48 = 0; _t48 < _len__t48; ++_t48) {
            gd::GdVal lv_buff = _t47->data[_t48];
            { gd::GdVal _t49 = this->f_buffPowers; gd::GdVal _t50 = lv_buff; gd::set_index(gd_ctx, _t49, _t50, gd::GdVal::from_float(1.0)); }
            { gd::GdVal _t51 = this->f_buffAmplificationChances; gd::GdVal _t52 = lv_buff; gd::set_index(gd_ctx, _t51, _t52, gd::GdVal::from_float(0.0)); }
        }
    }
    this->f_critChancePercent = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_critTokens = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_critSeverity = gd::gd_coerce_float(Gd__gd_core__CoreItem::get_static_const_or_enum(gd_ctx, SYM_GEN_BASE_CRIT_SEVERITY_0));
    this->f_bonusChancePercent_mult = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusChancePercent_additive1 = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusChancePercent_additive2 = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusAccuracy = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_doubleActivationChance = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_doubleAttackEffectChance = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    (void)gd::call_method(gd_ctx, this->f_paramMult, gd::SYM_clear, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_paramAdd, gd::SYM_clear, nullptr, 0);
    this->f_numCharges = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null()}; return gd::call_method(gd_ctx, this->f_statDisplayOverrides, gd::SYM_fill, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, this->f_itemMetrics, gd::SYM_fill, _ca, 1); })();
    this->f_consumed = gd::GdVal::from_bool(false);
    this->f_lastActivationTime = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_activationsThisFrame = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_triggersThisFrame = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_lastTriggerTime = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_triggerTime = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_iterationCooldown = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f__cooldown_active = gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_physicsTick(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f__cooldown_active)))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_isStunned_1155, nullptr, 0))))) {
        this->f_triggerTime = gd::gd_coerce_float(gd::gd_sub(this->f_triggerTime, gd::gd_mul(lv_delta, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getSpeed_94, nullptr, 0))));
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::gd_sub(gd::GdVal::from_float(1.0), gd::gd_div(gd_ctx, this->f_triggerTime, this->f_iterationCooldown))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_showCooldown_794, _ca, 2); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(this->f_triggerTime, gd::GdVal::from_int(0LL))))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_trigger_145, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_newItemTimer(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_timerName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_method = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_isMulti = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(false));
    lv_isMulti = gd::gd_coerce_bool(lv_isMulti);
    {
        gd::GdVal _t53 = gd::gd_iter_seq(gd_ctx.arena, this->f_timers);
        gd::GdArr* _t54 = (_t53.kind == gd::GdVal::Kind::Arr) ? _t53.arr : nullptr;
        uint32_t _len__t55 = _t54 ? _t54->len : 0u;
        for (uint32_t _t55 = 0; _t55 < _len__t55; ++_t55) {
            gd::GdVal lv_existing = _t54->data[_t55];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_existing, SYM_GEN_name_7), lv_timerName)))) {
                (void)gd::call_method(gd_ctx, lv_existing, SYM_GEN_stop_1686, nullptr, 0);
                (void)([&]() { gd::GdVal _ca[] = {lv_existing}; return gd::call_method(gd_ctx, this->f_timers, gd::SYM_erase, _ca, 1); })();
                break;
            }
        }
    }
    gd::GdVal lv_t = ([&]() { gd::GdVal _ca[] = {this->f_ctx, gd::GdVal::from_obj(this), lv_timerName}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreTimer), gd::SYM_new, _ca, 3); })();
    gd::set_prop(gd_ctx, lv_t, SYM_GEN_multi_1672, lv_isMulti);
    gd::set_prop(gd_ctx, lv_t, SYM_GEN_one_shot_1671, gd::GdVal::from_bool(true));
    gd::set_prop(gd_ctx, lv_t, SYM_GEN_callback_method_1673, lv_method);
    (void)([&]() { gd::GdVal _ca[] = {lv_t}; return gd::call_method(gd_ctx, this->f_timers, gd::SYM_push_back, _ca, 1); })();
    return lv_t;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getTimer(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_timerName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t56 = gd::gd_iter_seq(gd_ctx.arena, this->f_timers);
        gd::GdArr* _t57 = (_t56.kind == gd::GdVal::Kind::Arr) ? _t56.arr : nullptr;
        uint32_t _len__t58 = _t57 ? _t57->len : 0u;
        for (uint32_t _t58 = 0; _t58 < _len__t58; ++_t58) {
            gd::GdVal lv_t = _t57->data[_t58];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_t, SYM_GEN_name_7), lv_timerName)))) {
                return lv_t;
            }
        }
    }
    return gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn__tickTimers(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    {
        gd::GdVal _t59 = gd::gd_iter_seq(gd_ctx.arena, this->f_timers);
        gd::GdArr* _t60 = (_t59.kind == gd::GdVal::Kind::Arr) ? _t59.arr : nullptr;
        uint32_t _len__t61 = _t60 ? _t60->len : 0u;
        for (uint32_t _t61 = 0; _t61 < _len__t61; ++_t61) {
            gd::GdVal lv_t = _t60->data[_t61];
            (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return gd::call_method(gd_ctx, lv_t, SYM_GEN_tick_1688, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_tickTimersPass(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__tickTimers_139, _ca, 1); })();
    {
        gd::GdVal _t62 = gd::gd_iter_seq(gd_ctx.arena, this->f_gems);
        gd::GdArr* _t63 = (_t62.kind == gd::GdVal::Kind::Arr) ? _t62.arr : nullptr;
        uint32_t _len__t64 = _t63 ? _t63->len : 0u;
        for (uint32_t _t64 = 0; _t64 < _len__t64; ++_t64) {
            gd::GdVal lv_gem = _t63->data[_t64];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_gem, gd::GdVal::null())))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return gd::call_method(gd_ctx, lv_gem, SYM_GEN__tickTimers_139, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_rebuildTimerSeen(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t65 = gd::gd_iter_seq(gd_ctx.arena, this->f_timers);
        gd::GdArr* _t66 = (_t65.kind == gd::GdVal::Kind::Arr) ? _t65.arr : nullptr;
        uint32_t _len__t67 = _t66 ? _t66->len : 0u;
        for (uint32_t _t67 = 0; _t67 < _len__t67; ++_t67) {
            gd::GdVal lv_t = _t66->data[_t67];
            (void)gd::call_method(gd_ctx, lv_t, SYM_GEN_rebuildSeen_1691, nullptr, 0);
        }
    }
    {
        gd::GdVal _t68 = gd::gd_iter_seq(gd_ctx.arena, this->f_gems);
        gd::GdArr* _t69 = (_t68.kind == gd::GdVal::Kind::Arr) ? _t68.arr : nullptr;
        uint32_t _len__t70 = _t69 ? _t69->len : 0u;
        for (uint32_t _t70 = 0; _t70 < _len__t70; ++_t70) {
            gd::GdVal lv_gem = _t69->data[_t70];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_gem, gd::GdVal::null())))) {
                (void)gd::call_method(gd_ctx, lv_gem, SYM_GEN_rebuildTimerSeen_141, nullptr, 0);
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_flickerAni_1600))) {
        gd::GdVal lv_flicker_delay = ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_flickerMinDist_1601), gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_flickerMaxDist_1602)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
        gd::GdVal lv__flk_delay_use = gd::gd_coerce_float(gd::gd_coerce_float(lv_flicker_delay));
        gd::GdVal lv__flk_ov = gd::GdVal::from_cstr(gd_ctx.arena, "");
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv__flk_ov, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u)))))) {
            gd::GdVal lv__key = gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1577))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "/ot", 3u))), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(this->f_ownerType)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })());
            gd::GdVal lv__vals = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
            {
                gd::GdVal _t71 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, ",", 1u))}; return gd::call_method(gd_ctx, lv__flk_ov, gd::SYM_split, _ca, 1); })());
                gd::GdArr* _t72 = (_t71.kind == gd::GdVal::Kind::Arr) ? _t71.arr : nullptr;
                uint32_t _len__t73 = _t72 ? _t72->len : 0u;
                for (uint32_t _t73 = 0; _t73 < _len__t73; ++_t73) {
                    gd::GdVal lv_pair = _t72->data[_t73];
                    gd::GdVal lv_kv = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "=", 1u))}; return gd::call_method(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, lv_pair)), gd::SYM_split, _ca, 1); })();
                    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, lv_kv, gd::SYM_size, nullptr, 0), gd::GdVal::from_int(2LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_index(gd_ctx, lv_kv, gd::GdVal::from_int(0LL)), lv__key)))) : gd::GdVal::from_bool(false)))) {
                        (void)([&]() { gd::GdVal _ca[] = {gd::gd_coerce_float(gd::get_index(gd_ctx, lv_kv, gd::GdVal::from_int(1LL)))}; return gd::call_method(gd_ctx, lv__vals, gd::SYM_append, _ca, 1); })();
                    }
                }
            }
            if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv__vals, gd::SYM_empty, nullptr, 0))))) {
                gd::GdVal lv__cur = gd::gd_coerce_int(gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {lv__key, gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_flk_delay_cursor_1389), gd::SYM_get, _ca, 2); })()));
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv__cur, gd::call_method(gd_ctx, lv__vals, gd::SYM_size, nullptr, 0))))) {
                    lv__flk_delay_use = gd::gd_coerce_float(gd::get_index(gd_ctx, lv__vals, lv__cur));
                    { gd::GdVal _t74 = gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_flk_delay_cursor_1389); gd::GdVal _t75 = lv__key; gd::set_index(gd_ctx, _t74, _t75, gd::gd_add(gd_ctx, lv__cur, gd::GdVal::from_int(1LL))); }
                }
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "flickerPlayAni", 14u)), lv__flk_delay_use}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_callDelayed_1420, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "FLKREG", 6u)), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1577))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "/ot", 3u))), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(this->f_ownerType)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), ([&]() { gd::GdVal _ca[] = {lv_flicker_delay}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "st=", 3u)), ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_rng_1377), gd::SYM_get_state, nullptr, 0)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_trace_diag_1645, _ca, 4); })();
    }
    if (gd::gd_truth(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_connectorReadyRoll_1605))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    }
    if (gd::gd_truth(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_gemRoll_1606))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), gd::GdVal::from_int(10LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    }
    this->f_hasPreDealDamageEarlyEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onPreDealDamage_early", 21u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasPreDealDamageLateEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onPreDealDamage_late", 20u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasDealtDamageEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDealtDamage", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasOnChargeReceivedEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onChargeReceived", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasOnChargeLeftEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onChargeLeft", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_initSockets_390, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "ITEMREADY", 9u)), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1577))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "/ot", 3u))), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(this->f_ownerType)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u)), gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "st=", 3u)), ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_rng_1377), gd::SYM_get_state, nullptr, 0)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_trace_diag_1645, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_flickerPlayAni(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "FLKFIRE", 7u)), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1577))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "/ot", 3u))), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(this->f_ownerType)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1382)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "st=", 3u)), ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_rng_1377), gd::SYM_get_state, nullptr, 0)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_trace_diag_1645, _ca, 4); })();
    gd::GdVal lv__key = gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1577))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "/ot", 3u))), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(this->f_ownerType)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })());
    gd::GdVal lv__flk_off = gd::GdVal::from_cstr(gd_ctx.arena, "");
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv__flk_off, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u)))))) {
        {
            gd::GdVal _t76 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, ",", 1u))}; return gd::call_method(gd_ctx, lv__flk_off, gd::SYM_split, _ca, 1); })());
            gd::GdArr* _t77 = (_t76.kind == gd::GdVal::Kind::Arr) ? _t76.arr : nullptr;
            uint32_t _len__t78 = _t77 ? _t77->len : 0u;
            for (uint32_t _t78 = 0; _t78 < _len__t78; ++_t78) {
                gd::GdVal lv_off = _t77->data[_t78];
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, lv_off)), lv__key)))) {
                    return gd::GdVal::null();
                }
            }
        }
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u)))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_flickerMinSpeed_1603), gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_flickerMaxSpeed_1604)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_bare_randf_range_1647, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_checkTriggerCount(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_limit = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_limit = gd::gd_coerce_int(lv_limit);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1382), this->f_triggersThisFrame)))) {
        this->f_triggersThisFrame = gd::gd_coerce_int(gd::GdVal::from_int(1LL));
        this->f_lastTriggerTime = gd::gd_coerce_float(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1382));
    }
    else {
        this->f_triggersThisFrame = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_triggersThisFrame, gd::GdVal::from_int(1LL)));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_triggersThisFrame, lv_limit)))) {
            return gd::GdVal::from_bool(false);
        }
    }
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_trigger(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "TRIG", 4u)), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1577))), gd::gd_coerce_int(this->f_ownerType), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "tt=", 3u)), ([&]() { gd::GdVal _ca[] = {this->f_triggerTime}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " cd=", 4u))), ([&]() { gd::GdVal _ca[] = {this->f_iterationCooldown}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " spd=", 5u))), ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getSpeed_94, nullptr, 0)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " t=", 3u))), ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1382)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_trace_diag_1645, _ca, 4); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f__inj_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u)))))) {
        this->f__inj_item = gd::GdVal::from_cstr(gd_ctx.arena, "");
        gd::GdVal lv__inj_n_s = gd::GdVal::from_cstr(gd_ctx.arena, "");
        this->f__inj_trigger_n = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv__inj_n_s, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u)))))) {
            this->f__inj_trigger_n = gd::gd_coerce_int(gd::gd_coerce_int(lv__inj_n_s));
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f__inj_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u)))))) {
            (void)gd::GdVal::null();
        }
    }
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f__inj_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1577))), this->f__inj_item)))) : gd::GdVal::from_bool(false)))) {
        this->f__inj_trigger_count = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f__inj_trigger_count, gd::GdVal::from_int(1LL)));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f__inj_trigger_count, this->f__inj_trigger_n)))) {
            (void)gd::GdVal::null();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.0), gd::GdVal::from_float(1.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_bare_randf_range_1647, _ca, 2); })();
        }
    }
    this->f_iterationCooldown = gd::gd_coerce_float(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_adjustCooldown_109, nullptr, 0));
    this->f_triggerTime = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_triggerTime, this->f_iterationCooldown));
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doCooldownEffect_146, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_doubleActivationChance, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_doubleActivationChance}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_flip_1639, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doCooldownEffect_146, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "CDX", 3u)), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1577))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "/ot", 3u))), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(this->f_ownerType)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "t=", 2u)), ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1382)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_trace_diag_1645, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "doCooldownEffect", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_506, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onAfterEffectFinished(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__consume = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_deactivateCooldown_101, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(0LL), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_showCooldownSmooth_793, _ca, 3); })();
    if (gd::gd_truth(lv__consume)) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_383, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_advanceCooldownPercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isCooldownActive_98, nullptr, 0))))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_reduction = gd::gd_mul(gd::gd_div(gd_ctx, lv_amount, gd::GdVal::from_float(100.0)), this->f_iterationCooldown);
    this->f_triggerTime = gd::gd_coerce_float(gd::gd_sub(this->f_triggerTime, lv_reduction));
    while (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(this->f_triggerTime, gd::GdVal::from_int(0LL))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_trigger_145, nullptr, 0);
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isCooldownActive_98, nullptr, 0))))) {
            return gd::GdVal::null();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNextFreeLabelPosition_380, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_Cooldown_2546)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_advanceCooldownSeconds(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isCooldownActive_98, nullptr, 0))))) {
        return gd::GdVal::null();
    }
    this->f_triggerTime = gd::gd_coerce_float(gd::gd_sub(this->f_triggerTime, gd::gd_mul(lv_amount, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getSpeed_94, nullptr, 0))));
    while (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(this->f_triggerTime, gd::GdVal::from_int(0LL))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_trigger_145, nullptr, 0);
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isCooldownActive_98, nullptr, 0))))) {
            return gd::GdVal::null();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNextFreeLabelPosition_380, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_Cooldown_2546)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_playActivationSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_int(6LL))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playDropSound_151, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_activate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_playCombatAni = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_consume = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(false));
    gd::GdVal lv_animationOverride = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkActivationLimit_153, nullptr, 0))))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_event = gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_fight_ended_1287))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isBag_85, nullptr, 0))))) {
            lv_event = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_createEvent_Activation_1351, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "activated", 9u)), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitEvent_1502, _ca, 4); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemMetrics_1367), SYM_GEN_Activations_2556)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addMetric_232, _ca, 1); })();
        }
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasCooldown_97, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_Cooldown_2546), gd::GdVal::null(), gd::GdVal::from_bool(false), lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 5); })();
        }
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_animationOverride, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_animationOverride, lv_consume}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_playActivationAnimation_778, _ca, 3); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationSound_150, nullptr, 0);
    if (gd::gd_truth(lv_playCombatAni)) {
        gd::GdVal lv_anim_hit = gd::GdVal::from_bool(true);
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_damageRes, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))))) : gd::GdVal::from_bool(false)))) {
            lv_anim_hit = gd::GdVal::from_bool(false);
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "ANIM", 4u)), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1577))), ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_animationScene_1599)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "hit=", 4u)), ([&]() { gd::GdVal _ca[] = {lv_anim_hit}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_trace_diag_1645, _ca, 4); })();
    }
    if (gd::gd_truth((gd::gd_truth(lv_playCombatAni) ? gd::GdVal::from_bool(gd::gd_truth(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_animationScene_1599))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(30.0)), gd::GdVal::from_float(30.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_bare_randf_range_1647, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(100.0)), gd::GdVal::from_float(100.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_bare_randf_range_1647, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(5.0)), gd::GdVal::from_float(5.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_bare_randf_range_1647, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.8), gd::GdVal::from_float(1.2)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_bare_randf_range_1647, _ca, 2); })();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_damageRes, gd::GdVal::null())))) {
        gd::GdVal lv_ch = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_ch, gd::GdVal::null())))) {
            (void)gd::call_method(gd_ctx, lv_ch, SYM_GEN_playActivateAnimation_1126, nullptr, 0);
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_playActivationSound_150, _ca, 1); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_checkActivationLimit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1382), this->f_lastActivationTime)))) {
        this->f_activationsThisFrame = gd::gd_coerce_int(gd::GdVal::from_int(1LL));
        this->f_lastActivationTime = gd::gd_coerce_float(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1382));
    }
    else {
        this->f_activationsThisFrame = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_activationsThisFrame, gd::GdVal::from_int(1LL)));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_activationsThisFrame, gd::GdVal::from_int(3LL))))) {
            return gd::GdVal::from_bool(false);
        }
    }
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBaseMinDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_minDam_1579);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBaseMaxDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_maxDam_1580);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBaseAverageDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_div(gd_ctx, gd::gd_add(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseMinDamage_154, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseMaxDamage_155, nullptr, 0)), gd::GdVal::from_float(2.0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getTypedDamageFactor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damSource = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_typedDmgFactor = gd::GdVal::from_float(1.0);
    {
        gd::GdVal _t79 = gd::gd_iter_seq(gd_ctx.arena, gd::get_prop(gd_ctx, lv_damSource, SYM_GEN_types_1453));
        gd::GdArr* _t80 = (_t79.kind == gd::GdVal::Kind::Arr) ? _t79.arr : nullptr;
        uint32_t _len__t81 = _t80 ? _t80->len : 0u;
        for (uint32_t _t81 = 0; _t81 < _len__t81; ++_t81) {
            gd::GdVal lv_type = _t80->data[_t81];
            lv_typedDmgFactor = gd::gd_add(gd_ctx, lv_typedDmgFactor, gd::get_index(gd_ctx, gd::get_prop(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_typedDamageFactors_1080), lv_type));
        }
    }
    return lv_typedDmgFactor;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getMinDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damSource = (_argc > 0) ? _args[0] : (this->f_damageSource);
    gd::GdVal lv_override = gd::get_index(gd_ctx, this->f_statDisplayOverrides, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_MinDamage_2557));
    if (gd::gd_truth(lv_override)) {
        return lv_override;
    }
    gd::GdVal lv_minDam = gd::gd_ceil(gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_minDam_1579), this->f_bonusMinDam));
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasCharacter_75, nullptr, 0))) {
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canBeEmpowered_92, nullptr, 0))) {
            lv_minDam = gd::gd_add(gd_ctx, lv_minDam, gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getBuffDamageMod_1242, nullptr, 0));
        }
        lv_minDam = gd::gd_mul(lv_minDam, ([&]() { gd::GdVal _ca[] = {lv_damSource}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getTypedDamageFactor_157, _ca, 1); })());
    }
    lv_minDam = gd::gd_round(gd::gd_mul(lv_minDam, this->f_bonusDamageFactor));
    lv_minDam = gd::gd_max(lv_minDam, gd::GdVal::from_int(0LL));
    return lv_minDam;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getMaxDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damSource = (_argc > 0) ? _args[0] : (this->f_damageSource);
    gd::GdVal lv_override = gd::get_index(gd_ctx, this->f_statDisplayOverrides, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_MaxDamage_2558));
    if (gd::gd_truth(lv_override)) {
        return lv_override;
    }
    gd::GdVal lv_maxDam = gd::gd_ceil(gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_maxDam_1580), this->f_bonusMaxDam));
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasCharacter_75, nullptr, 0))) {
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canBeEmpowered_92, nullptr, 0))) {
            lv_maxDam = gd::gd_add(gd_ctx, lv_maxDam, gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getBuffDamageMod_1242, nullptr, 0));
        }
        lv_maxDam = gd::gd_mul(lv_maxDam, ([&]() { gd::GdVal _ca[] = {lv_damSource}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getTypedDamageFactor_157, _ca, 1); })());
    }
    lv_maxDam = gd::gd_round(gd::gd_mul(lv_maxDam, this->f_bonusDamageFactor));
    lv_maxDam = gd::gd_max(lv_maxDam, gd::GdVal::from_int(0LL));
    return lv_maxDam;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAverageDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_div(gd_ctx, gd::gd_add(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMinDamage_158, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxDamage_159, nullptr, 0)), gd::GdVal::from_float(2.0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_randDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMinDamage_158, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxDamage_159, nullptr, 0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randi_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getModifiedEffectDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_baseDamage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_modifiedDamage = lv_baseDamage;
    lv_modifiedDamage = gd::gd_mul(lv_modifiedDamage, gd::gd_add(gd_ctx, gd::GdVal::from_float(1.0), gd::get_index(gd_ctx, gd::get_prop(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_typedDamageFactors_1080), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Effect_2559))));
    lv_modifiedDamage = gd::gd_mul(lv_modifiedDamage, this->f_bonusDamageFactor);
    return lv_modifiedDamage;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addBonusDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_removable = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    lv_removable = gd::gd_coerce_bool(lv_removable);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_damage, gd::GdVal::from_int(0LL))))) {
        this->f_bonusMinDam = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_bonusMinDam, lv_damage));
        this->f_bonusMaxDam = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_bonusMaxDam, lv_damage));
        if (gd::gd_truth(lv_removable)) {
            this->f_removableDam = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_removableDam, lv_damage));
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_MinDamage_2557)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_MaxDamage_2558)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
        if (gd::gd_truth(lv_removable)) {
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_DamageBuff_2560), lv_damage}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_spawnLabel_381, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_changeVaryingDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_damage, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_163, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addMinDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_bonusMinDam = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_bonusMinDam, lv_damage));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_MinDamage_2557)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addMaxDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_bonusMaxDam = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_bonusMaxDam, lv_damage));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_MaxDamage_2558)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getRemovableDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_removableDam;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_removeBonusDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_bonusMinDam = gd::gd_coerce_float(gd::gd_sub(this->f_bonusMinDam, this->f_removableDam));
    this->f_bonusMaxDam = gd::gd_coerce_float(gd::gd_sub(this->f_bonusMaxDam, this->f_removableDam));
    this->f_removableDam = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_setBonusDamageFactor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_factor = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_bonusDamageFactor = gd::gd_coerce_float(lv_factor);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBaseChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_chance_1585);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBaseChance2(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_chance2_1586);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_applyBonusChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_toChance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_index = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_index, gd::GdVal::from_int(1LL))))) {
        return gd::gd_mul(gd::gd_add(gd_ctx, lv_toChance, this->f_bonusChancePercent_additive1), gd::gd_div(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_int(100LL), this->f_bonusChancePercent_mult), gd::GdVal::from_float(100.0)));
    }
    else {
        return gd::gd_mul(gd::gd_add(gd_ctx, lv_toChance, this->f_bonusChancePercent_additive2), gd::gd_div(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_int(100LL), this->f_bonusChancePercent_mult), gd::GdVal::from_float(100.0)));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_override = gd::get_index(gd_ctx, this->f_statDisplayOverrides, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_Chance_2561));
    if (gd::gd_truth(lv_override)) {
        return lv_override;
    }
    return gd::gd_clamp(([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseChance_170, nullptr, 0), gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_applyBonusChance_172, _ca, 2); })(), gd::GdVal::from_int(0LL), gd::GdVal::from_int(100LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getChance2(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_override = gd::get_index(gd_ctx, this->f_statDisplayOverrides, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_Chance2_2562));
    if (gd::gd_truth(lv_override)) {
        return lv_override;
    }
    return gd::gd_clamp(([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseChance2_171, nullptr, 0), gd::GdVal::from_int(2LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_applyBonusChance_172, _ca, 2); })(), gd::GdVal::from_int(0LL), gd::GdVal::from_int(100LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_rollChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_chance, gd::GdVal::null())))) {
        lv_chance = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseChance_170, nullptr, 0);
    }
    gd::GdVal lv__target = ([&]() { gd::GdVal _ca[] = {lv_chance, gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_applyBonusChance_172, _ca, 2); })();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1577), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Hammer", 6u)))))) : gd::GdVal::from_bool(false)))) {
        (void)gd::GdVal::null();
    }
    gd::GdVal lv__rc = ([&]() { gd::GdVal _ca[] = {lv__target}; return gd::call_method(gd_ctx, this->f_chanceRng, SYM_GEN_rollPercent_1664, _ca, 1); })();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1577), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Hammer", 6u)))))) : gd::GdVal::from_bool(false)))) {
        (void)gd::GdVal::null();
    }
    if (gd::gd_truth((gd::gd_truth(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_oracle_trace_1633)) ? gd::GdVal::from_bool(gd::gd_truth(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN__stacktrace_1635))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "ROLLW", 5u)), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1577))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "/ot", 3u))), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(this->f_ownerType)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "ch=", 3u)), ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_chance, gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_applyBonusChance_172, _ca, 2); })()}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "res=", 4u)), ([&]() { gd::GdVal _ca[] = {lv__rc}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_trace_diag_1645, _ca, 4); })();
    }
    return lv__rc;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_rollChance2(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_chance2_1586), gd::GdVal::from_int(2LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_applyBonusChance_172, _ca, 2); })()}; return gd::call_method(gd_ctx, this->f_chanceRng, SYM_GEN_rollPercent_1664, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addBonusChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_bonusChancePercent_mult = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_bonusChancePercent_mult, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_Chance_2561)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_Chance2_2562)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addBonusChance_additive(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount1 = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount2 = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    this->f_bonusChancePercent_additive1 = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_bonusChancePercent_additive1, lv_amount1));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_amount2, gd::GdVal::null())))) {
        this->f_bonusChancePercent_additive2 = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_bonusChancePercent_additive2, lv_amount1));
    }
    else {
        this->f_bonusChancePercent_additive2 = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_bonusChancePercent_additive2, lv_amount2));
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_Chance_2561)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_amount2, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_Chance2_2562)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addAccuracy(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_bonusAccuracy = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_bonusAccuracy, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getCritChancePercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_clamp(this->f_critChancePercent, gd::GdVal::from_int(0LL), gd::GdVal::from_int(100LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addCritChancePercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_critChancePercent = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_critChancePercent, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_CritChance_2563)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_reduceCritChancePercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_critChancePercent = gd::gd_coerce_float(gd::gd_sub(this->f_critChancePercent, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_CritChance_2563)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_changeCritChancePercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_critChancePercent = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_critChancePercent, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_CritChance_2563)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getCritTokens(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_critTokens;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addCritTokens(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_critTokens = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_critTokens, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_useCritToken(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_critTokens = gd::gd_coerce_int(gd::gd_sub(this->f_critTokens, gd::GdVal::from_int(1LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addCritSeverity(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_critSeverity = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_critSeverity, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getCritSeverity(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_critSeverity;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_rollDoubleAttackEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {this->f_doubleAttackEffectChance}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_flip_1639, _ca, 1); })());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getP(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_index = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_index}; return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getP_190, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getP_m(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_paramName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_baseVal = ([&]() { gd::GdVal _ca[] = {lv_paramName}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    return ([&]() { gd::GdVal _ca[] = {lv_paramName, lv_baseVal}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getParamModified_192, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getParamModified(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_paramName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_baseVal = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_baseParam = gd::get_index(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_paramBases_1616), lv_paramName);
    return gd::gd_mul(gd::gd_add(gd_ctx, lv_baseVal, ([&]() { gd::GdVal _ca[] = {lv_baseParam, gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, this->f_paramAdd, gd::SYM_get, _ca, 2); })()), ([&]() { gd::GdVal _ca[] = {lv_baseParam, gd::GdVal::from_float(1.0)}; return gd::call_method(gd_ctx, this->f_paramMult, gd::SYM_get, _ca, 2); })());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_modifyParam(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_paramName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_float(lv_amount);
    { gd::GdVal _t82 = this->f_paramMult; gd::GdVal _t83 = lv_paramName; gd::set_index(gd_ctx, _t82, _t83, gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_paramName, gd::GdVal::from_float(1.0)}; return gd::call_method(gd_ctx, this->f_paramMult, gd::SYM_get, _ca, 2); })(), lv_amount)); }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_modifyParam_add(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_paramName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_float(lv_amount);
    { gd::GdVal _t84 = this->f_paramAdd; gd::GdVal _t85 = lv_paramName; gd::set_index(gd_ctx, _t84, _t85, gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_paramName, gd::GdVal::from_float(0.0)}; return gd::call_method(gd_ctx, this->f_paramAdd, gd::SYM_get, _ca, 2); })(), lv_amount)); }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBaseAccuracy(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_accuracy_1454);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAccuracy(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_acc = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseAccuracy_195, nullptr, 0);
    lv_acc = gd::gd_add(gd_ctx, lv_acc, this->f_bonusAccuracy);
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasCharacter_75, nullptr, 0))) {
        lv_acc = gd::gd_add(gd_ctx, lv_acc, gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getBuffAccuracyMod_1243, nullptr, 0));
    }
    return lv_acc;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAmplificationChancePercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::get_index(gd_ctx, this->f_buffAmplificationChances, lv_buffType);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_changeAmplificiationChancePercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_chance = (_argc > 1) ? _args[1] : gd::GdVal::null();
    { gd::GdVal _t86 = this->f_buffAmplificationChances; gd::GdVal _t87 = lv_buffType; gd::set_index(gd_ctx, _t86, _t87, gd::gd_add(gd_ctx, gd::get_index(gd_ctx, _t86, _t87), lv_chance)); }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_changeAmplificiationChancePercent_allBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t88 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0));
        gd::GdArr* _t89 = (_t88.kind == gd::GdVal::Kind::Arr) ? _t88.arr : nullptr;
        uint32_t _len__t90 = _t89 ? _t89->len : 0u;
        for (uint32_t _t90 = 0; _t90 < _len__t90; ++_t90) {
            gd::GdVal lv_buff = _t89->data[_t90];
            (void)([&]() { gd::GdVal _ca[] = {lv_buff, lv_chance}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeAmplificiationChancePercent_198, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_changeAmplificiationChancePercent_allDebuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t91 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1362, nullptr, 0));
        gd::GdArr* _t92 = (_t91.kind == gd::GdVal::Kind::Arr) ? _t91.arr : nullptr;
        uint32_t _len__t93 = _t92 ? _t92->len : 0u;
        for (uint32_t _t93 = 0; _t93 < _len__t93; ++_t93) {
            gd::GdVal lv_buff = _t92->data[_t93];
            (void)([&]() { gd::GdVal _ca[] = {lv_buff, lv_chance}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeAmplificiationChancePercent_198, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_changeNullifyChancePercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_chance = (_argc > 1) ? _args[1] : gd::GdVal::null();
    { gd::GdVal _t94 = this->f_buffAmplificationChances; gd::GdVal _t95 = lv_buffType; gd::set_index(gd_ctx, _t94, _t95, gd::gd_sub(gd::get_index(gd_ctx, _t94, _t95), lv_chance)); }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveReflectStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeDebuffReflectStacks_1170, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_target = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_type = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    gd::GdVal lv_amount = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        return ([&]() { gd::GdVal _ca[] = {lv_type, gd::gd_round(gd::gd_mul(lv_amount, gd::get_index(gd_ctx, this->f_buffPowers, lv_type))), gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, lv_target, SYM_GEN_gainStacks_1029, _ca, 4); })();
    }
    return gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveStacksTemporary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_target = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_type = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    gd::GdVal lv_amount = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_duration = (_argc > 3) ? _args[3] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 4) ? _args[4] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        return ([&]() { gd::GdVal _ca[] = {lv_type, gd::gd_round(gd::gd_mul(lv_amount, gd::get_index(gd_ctx, this->f_buffPowers, lv_type))), lv_duration, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, lv_target, SYM_GEN_gainStacksTemporary_1202, _ca, 5); })();
    }
    return gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_canTriggerEffects = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_amount, gd::GdVal::null())))) {
        lv_amount = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_206, nullptr, 0);
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Block_2564), lv_amount, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 4); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_event, gd::GdVal::null())))) {
            if (gd::gd_truth(lv_canTriggerEffects)) {
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gave_block", 10u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::call_method(gd_ctx, lv_event, SYM_GEN_getAmount_1485, nullptr, 0), lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitSignal_1501, _ca, 3); })();
            }
            else {
                (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_logEvent_1328, _ca, 1); })();
            }
            return lv_event;
        }
    }
    return gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_block_1582);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_removeBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_loseBlock_208, _ca, 3); })();
    if (gd::gd_truth(lv_event)) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::call_method(gd_ctx, lv_event, SYM_GEN_getAmount_1485, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countDamage_227, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_loseBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_loseBlock_208, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_useBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Block_2564), lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_useStacks_1203, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_stealStack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_removeEvent = ([&]() { gd::GdVal _ca[] = {lv_type, lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_loseStacks_1031, _ca, 4); })();
    gd::GdVal lv_giveEvent = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), lv_type, lv_amount, lv_removeEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 4); })();
    return lv_giveEvent;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveSpikes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Spikes_2565), lv_amount, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveVampirism(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Vampirism_2566), lv_amount, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_inflictPoison(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Poison_2567), lv_amount, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_selfInflictPoison(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Poison_2567), lv_amount, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_inflictBlind(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Blind_2568), lv_amount, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveRegeneration(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Regeneration_2569), lv_amount, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveLucky(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Lucky_2570), lv_amount, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveMana(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Mana_2571), lv_amount, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveEmpower(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Empower_2572), lv_amount, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveHeat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Heat_2573), lv_amount, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveCold(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Cold_2574), lv_amount, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_dealDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, this->f_damageSource, SYM_GEN_updateItem_1462, _ca, 1); })();
    gd::GdVal lv_damageRes = ([&]() { gd::GdVal _ca[] = {this->f_damageSource, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_dealDamage_222, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attacked", 8u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitSignal_1501, _ca, 3); })();
    return lv_damageRes;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_dealEffectDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv__damageSource = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv__damageSource, gd::GdVal::null())))) {
        lv__damageSource = this->f_damageSource;
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_damage}; return gd::call_method(gd_ctx, lv__damageSource, SYM_GEN_updateEffect_1463, _ca, 2); })();
    gd::GdVal lv_damageRes = ([&]() { gd::GdVal _ca[] = {lv__damageSource, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_takeDamage_1132, _ca, 2); })();
    return lv_damageRes;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_preDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "pre_deal_damage_early", 21u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitSignal_1501, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_preDealDamage_late(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "pre_deal_damage_late", 20u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitSignal_1501, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_dealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dealt_damage", 12u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitSignal_1501, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_countDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemMetrics_1367), SYM_GEN_Damage_2575), lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addMetric_232, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::sf_getNumNonStackItemMetrics(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    return gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemMetrics_1367), SYM_GEN_Stamina_2576), gd::gd_mul(gd::gd_sub(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemMetrics_1367), SYM_GEN_Block_2564), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemMetrics_1367), SYM_GEN_Stamina_2576)), gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StackChangeType_871), gd::SYM_size, nullptr, 0)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::sf_getNumItemMetrics(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    return gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemMetrics_1367), SYM_GEN_Stamina_2576), gd::gd_mul(gd::gd_sub(gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemMetrics_1367), gd::SYM_size, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemMetrics_1367), SYM_GEN_Stamina_2576)), gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StackChangeType_871), gd::SYM_size, nullptr, 0)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::sf_getStackMetricIndex(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_stackChangeType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_stackChangeType = gd::gd_coerce_int(lv_stackChangeType);
    gd::GdVal lv_stackType = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_stackType = gd::gd_coerce_int(lv_stackType);
    gd::GdVal lv_offsetStackType = gd::gd_sub(lv_stackType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Block_2564));
    gd::GdVal lv_changeTypeOffset = gd::gd_mul(lv_stackChangeType, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_numStackTypes_1365, nullptr, 0));
    return gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, ([&]() { gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreItem::call_static_fn(gd_ctx, SYM_GEN_getNumNonStackItemMetrics_228, nullptr, 0, _out); return _out; })(), lv_changeTypeOffset), lv_offsetStackType);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::sf_getMultiMetricIndex(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_stackChangeType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_stackChangeType = gd::gd_coerce_int(lv_stackChangeType);
    gd::GdVal lv_metric = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_metric = gd::gd_coerce_int(lv_metric);
    gd::GdVal lv_offsetMetric = gd::gd_sub(lv_metric, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemMetrics_1367), SYM_GEN_Stamina_2576));
    gd::GdVal lv_numMultiMetrics = gd::gd_mul(lv_offsetMetric, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StackChangeType_871), gd::SYM_size, nullptr, 0));
    return gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemMetrics_1367), SYM_GEN_Stamina_2576), lv_numMultiMetrics), lv_stackChangeType);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addMetric(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_metricsIndex = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : (gd::GdVal::from_int(1LL));
    gd::GdVal lv_playerId = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_withNextEvent = (_argc > 3) ? _args[3] : (gd::GdVal::from_bool(false));
    { gd::GdVal _t96 = this->f_itemMetrics; gd::GdVal _t97 = lv_metricsIndex; gd::set_index(gd_ctx, _t96, _t97, gd::gd_add(gd_ctx, gd::get_index(gd_ctx, _t96, _t97), lv_amount)); }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_metricsIndex, lv_playerId, lv_withNextEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_snapshotItemMetric_1354, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getMetric(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_metric = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::get_index(gd_ctx, this->f_itemMetrics, lv_metric);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_stackChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stackType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_stackType = gd::gd_coerce_int(lv_stackType);
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_onPlayer = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_onPlayer = gd::gd_coerce_bool(lv_onPlayer);
    gd::GdVal lv_used = (_argc > 3) ? _args[3] : (gd::GdVal::from_bool(false));
    lv_used = gd::gd_coerce_bool(lv_used);
    gd::GdVal lv_changeType = gd::GdVal::from_int(0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        lv_changeType = gd::gd_coerce_int(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StackChangeType_871), SYM_GEN_Added_Player_2577));
    }
    else {
        if (gd::gd_truth(lv_used)) {
            lv_changeType = gd::gd_coerce_int(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StackChangeType_871), SYM_GEN_Used_Player_2553));
        }
        else {
            lv_changeType = gd::gd_coerce_int(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StackChangeType_871), SYM_GEN_Removed_Player_2578));
        }
    }
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_onPlayer)))) {
        lv_changeType = gd::gd_coerce_int(gd::gd_add(gd_ctx, lv_changeType, gd::GdVal::from_int(1LL)));
    }
    gd::GdVal lv_index = ([&]() { gd::GdVal _ca[] = {lv_changeType, lv_stackType}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreItem::call_static_fn(gd_ctx, SYM_GEN_getStackMetricIndex_230, _ca, 2, _out); return _out; })();
    gd::GdVal lv_playerId = (gd::gd_truth(lv_onPlayer) ? (gd::GdVal::from_int(0LL)) : (gd::GdVal::from_int(1LL)));
    (void)([&]() { gd::GdVal _ca[] = {lv_index, gd::gd_abs(lv_amount), lv_playerId, gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addMetric_232, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_staminaChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_float(lv_amount);
    gd::GdVal lv_changeType = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_changeType = gd::gd_coerce_int(lv_changeType);
    gd::GdVal lv_withNextEvent = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(false));
    lv_withNextEvent = gd::gd_coerce_bool(lv_withNextEvent);
    gd::GdVal lv_index = ([&]() { gd::GdVal _ca[] = {lv_changeType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemMetrics_1367), SYM_GEN_Stamina_2576)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreItem::call_static_fn(gd_ctx, SYM_GEN_getMultiMetricIndex_231, _ca, 2, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {lv_index, lv_amount, gd::get_prop(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_playerId_1046), lv_withNextEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addMetric_232, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getName(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getName_236, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getIndex(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getIndex_237, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getRarity(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_rarity_1590);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getShopChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getShopChance_239, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getMainType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_index(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_types_1453), gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getNumStaticTypes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getTypes_242, nullptr, 0), gd::SYM_size, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getTypes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::call_method(gd_ctx, this->f_dynamicTypes, gd::SYM_keys, nullptr, 0), gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_types_1453));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_hasDynamicType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    gd::GdVal lv_fromItem = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::gd_in(lv_type, this->f_dynamicTypes))) {
        if (gd::gd_truth(gd::gd_in(gd::call_method(gd_ctx, lv_fromItem, gd::SYM_get_instance_id, nullptr, 0), gd::get_index(gd_ctx, this->f_dynamicTypes, lv_type)))) {
            return gd::GdVal::from_bool(true);
        }
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addDynamicType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    gd::GdVal lv_byItem = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_type, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_types_1453)))))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_dynamicTypes, lv_type, gd::call_method(gd_ctx, lv_byItem, gd::SYM_get_instance_id, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_dictAppend_1697, _ca, 3); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_dynamicTypes, lv_type), gd::SYM_size, nullptr, 0), gd::GdVal::from_int(1LL))))) {
            if (gd::gd_truth(this->f_placed)) {
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_onItemTypeChanged_460, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_removeDynamicType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    gd::GdVal lv_byItem = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_type, lv_byItem}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasDynamicType_243, _ca, 2); })())) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_dynamicTypes, lv_type, gd::call_method(gd_ctx, lv_byItem, gd::SYM_get_instance_id, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_dictErase_1698, _ca, 3); })();
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_type, this->f_dynamicTypes))))) {
            if (gd::gd_truth(this->f_placed)) {
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_onItemTypeChanged_460, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_clearDynamicTypes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_dynamicTypes, gd::SYM_clear, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isA(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__descriptor = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(gd::gd_eq(this->f_descriptor, lv__descriptor));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isNeutral(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_isNeutral_248, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isTreasure(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_randomUniquePool_1593);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isClassItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_classIndex = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_classIndex, gd::GdVal::null())))) {
        return (gd::gd_truth(gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_isClassItem_250, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_classIndex}; return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_isAvailableFor_1623, _ca, 1); })())) : gd::GdVal::from_bool(false));
    }
    return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_isClassItem_250, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isSubclassItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_isSubclassItem_251, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isOwnable(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_Shop_2579)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_PlayerInventory_2555))))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_PlayerStorageBox_2580))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isOwnedByOpponent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_Opponent_2545)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isGateItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "getGatedDescriptor", 18u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_505, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "getReplaceDescriptor", 20u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_505, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isShowCaseItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::null()));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isAffectingDistinct(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581));
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "isAffectingDistinct", 19u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_505, _ca, 1); })())) {
        return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "isAffectingDistinct", 19u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_color}))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_506, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_truth_1360, _ca, 1); })();
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_affectsEmpty(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "affectsEmpty", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_505, _ca, 1); })())) {
        return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "affectsEmpty", 12u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_color}))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_506, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_truth_1360, _ca, 1); })();
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_hasOpponent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasCharacter_75, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), gd::GdVal::null())))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getEffectiveOwnerType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_ownerType;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isBaseItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isBusy(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isBoundAsIngredient(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getStat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stat = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t98 = lv_stat;
        if (gd::gd_eq(_t98, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_MaxDamage_2558))) {
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseMaxDamage_155, nullptr, 0), gd::GdVal::from_int(0LL))))) {
                return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxDamage_159, nullptr, 0);
            }
            else {
                return gd::GdVal::from_int(0LL);
            }
        }
        else if (gd::gd_eq(_t98, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_MinDamage_2557))) {
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseMinDamage_154, nullptr, 0), gd::GdVal::from_int(0LL))))) {
                return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMinDamage_158, nullptr, 0);
            }
            else {
                return gd::GdVal::from_int(0LL);
            }
        }
        else if (gd::gd_eq(_t98, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_Accuracy_2582))) {
            return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAccuracy_196, nullptr, 0);
        }
        else if (gd::gd_eq(_t98, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_CritChance_2563))) {
            return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCritChancePercent_180, nullptr, 0);
        }
        else if (gd::gd_eq(_t98, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_Speed_2543))) {
            return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getSpeed_94, nullptr, 0);
        }
        else if (gd::gd_eq(_t98, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_Cooldown_2546))) {
            return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCooldownEncoded_108, nullptr, 0);
        }
        else if (gd::gd_eq(_t98, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_StaminaCost_2547))) {
            return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStaminaCost_114, nullptr, 0);
        }
        else if (gd::gd_eq(_t98, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_Chance_2561))) {
            return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0);
        }
        else if (gd::gd_eq(_t98, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_Chance2_2562))) {
            return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_174, nullptr, 0);
        }
        else if (gd::gd_eq(_t98, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_BaseCooldown_2544))) {
            return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCooldown_104, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getP_check(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_index = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::get_index(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_params_1479), lv_index);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getP1(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_check_264, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getP2(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_check_264, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getP3(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_check_264, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getP4(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(3LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_check_264, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getP5(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(4LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_check_264, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getP6(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(5LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_check_264, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getP7(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(6LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_check_264, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getP8(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(7LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_check_264, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getP9(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(8LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_check_264, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getP10(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(9LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_check_264, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addSpeed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_speedScale = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_speedScale, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "SPD+", 4u)), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1577))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "@", 1u))), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getTopLeftCell_445, nullptr, 0)))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " ot=", 4u))), ([&]() { gd::GdVal _ca[] = {gd::gd_coerce_int(this->f_ownerType)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), ([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "now=", 4u)), ([&]() { gd::GdVal _ca[] = {this->f_speedScale}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_trace_diag_1645, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_Speed_2543)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_Cooldown_2546)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_reduceSpeed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_speedScale = gd::gd_coerce_float(gd::gd_sub(this->f_speedScale, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_Speed_2543)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_Cooldown_2546)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getDPS(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_div(gd_ctx, gd::gd_mul(gd::gd_add(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMinDamage_158, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxDamage_159, nullptr, 0)), gd::GdVal::from_float(0.5)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModifiedCooldown_106, nullptr, 0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isDPSModified(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_baseDPS = gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseAverageDamage_156, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCooldown_104, nullptr, 0));
    gd::GdVal lv_modifiedDPS = gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAverageDamage_160, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModifiedCooldown_106, nullptr, 0));
    return ([&]() { gd::GdVal _ca[] = {gd::gd_sub(lv_modifiedDPS, lv_baseDPS)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isStatModified_116, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getDamageRange(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMinDamage_158, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxDamage_159, nullptr, 0))))) {
        return gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMinDamage_158, nullptr, 0)));
    }
    else {
        return gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMinDamage_158, nullptr, 0))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "-", 1u))), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxDamage_159, nullptr, 0))));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isCooldownModified(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_baseCd = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldown_102, nullptr, 0);
    gd::GdVal lv_curCd = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModifiedCooldown_106, nullptr, 0);
    return ([&]() { gd::GdVal _ca[] = {gd::gd_sub(lv_baseCd, lv_curCd)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isStatModified_116, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isAccuracyModified(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::gd_sub(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAccuracy_196, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseAccuracy_195, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isStatModified_116, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isChance1Modified(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::gd_sub(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseChance_170, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isStatModified_116, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isChance2Modified(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::gd_sub(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_174, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseChance2_171, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isStatModified_116, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isDamageModified(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_bonusDam = gd::gd_sub(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAverageDamage_160, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseAverageDamage_156, nullptr, 0));
    return ([&]() { gd::GdVal _ca[] = {lv_bonusDam}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isStatModified_116, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBaseStaminaPerSecond(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseStaminaCost_113, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCooldown_104, nullptr, 0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getStaminaPerSecond(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStaminaCost_114, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModifiedCooldown_106, nullptr, 0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isStaminaPerSecondModified(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_baseSPS = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseStaminaPerSecond_285, nullptr, 0);
    gd::GdVal lv_modifiedSPS = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStaminaPerSecond_286, nullptr, 0);
    return ([&]() { gd::GdVal _ca[] = {gd::gd_sub(lv_baseSPS, lv_modifiedSPS)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isStatModified_116, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "canAffect", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_505, _ca, 1); })())) {
        return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "canAffect", 9u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_item}))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_506, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_truth_1360, _ca, 1); })();
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "canAffect_secondary", 19u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_505, _ca, 1); })())) {
        return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "canAffect_secondary", 19u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_item}))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_506, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_truth_1360, _ca, 1); })();
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canAffect_tertiary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "canAffect_tertiary", 18u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_505, _ca, 1); })())) {
        return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "canAffect_tertiary", 18u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_item}))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_506, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_truth_1360, _ca, 1); })();
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canAffect_lightning(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "canAffect_lightning", 19u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_505, _ca, 1); })())) {
        return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "canAffect_lightning", 19u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_item}))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_506, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_truth_1360, _ca, 1); })();
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canAffect_color(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_color, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581))))) {
        return ([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_288, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_color, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Secondary_2583))))) {
        return ([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_secondary_289, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_color, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Tertiary_2584))))) {
        return ([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_tertiary_290, _ca, 1); })();
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_lightning_291, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_206, nullptr, 0), gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canHealOrLifesteal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal", 4u))}; return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_hasParam_1487, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lifesteal", 9u))}; return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_hasParam_1487, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canModifyChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseChance_170, nullptr, 0), gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canUseStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseStaminaCost_113, nullptr, 0), gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_hasAttackEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth((gd::gd_truth(this->f_hasPreDealDamageEarlyEffect) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(this->f_hasPreDealDamageLateEffect)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(this->f_hasDealtDamageEffect)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_gainsBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_bitand(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_gainedStacks_1618), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Stack_859), SYM_GEN_Buff_2585));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_usesBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_bitand(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_usedStacks_1620), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Stack_859), SYM_GEN_Buff_2585));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_inflictsDebuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_bitand(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_gainedStacks_1618), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Stack_859), SYM_GEN_Debuff_2586));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_reactsToCharges(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(this->f_hasOnChargeReceivedEffect) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(this->f_hasOnChargeLeftEffect)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_fillUpStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_fillUpStamina_302, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getRelativeOpponentHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_getRelativeHealth_304, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getRelativeHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getRelativeHealth_304, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveBuffPower(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_power = (_argc > 1) ? _args[1] : gd::GdVal::null();
    { gd::GdVal _t99 = this->f_buffPowers; gd::GdVal _t100 = lv_buffType; gd::set_index(gd_ctx, _t99, _t100, gd::gd_add(gd_ctx, gd::get_index(gd_ctx, _t99, _t100), lv_power)); }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_changeHealAmp(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal", 4u)), lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_modifyParam_193, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lifesteal", 9u)), lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_modifyParam_193, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_changeStaminaFactor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_staminaFactor = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_staminaFactor, gd::gd_div(gd_ctx, lv_amount, gd::GdVal::from_float(100.0))));
    this->f_staminaFactor = gd::gd_coerce_float(gd::gd_max(gd::GdVal::from_int(0LL), this->f_staminaFactor));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_StaminaCost_2547)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_addBonusDamageFactor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_factor = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_bonusDamageFactor = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_bonusDamageFactor, lv_factor));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_MinDamage_2557)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_MaxDamage_2558)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_reduceBonusDamageFactor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_factor = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_bonusDamageFactor = gd::gd_coerce_float(gd::gd_sub(this->f_bonusDamageFactor, lv_factor));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_MinDamage_2557)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_MaxDamage_2558)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_reduceMinDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_bonusMinDam = gd::gd_coerce_float(gd::gd_sub(this->f_bonusMinDam, lv_damage));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_MinDamage_2557)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_reduceMaxDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_bonusMaxDam = gd::gd_coerce_float(gd::gd_sub(this->f_bonusMaxDam, lv_damage));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_MaxDamage_2558)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_reduceBonusDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_showLabel = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    lv_showLabel = gd::gd_coerce_bool(lv_showLabel);
    gd::GdVal lv_removable = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(true));
    lv_removable = gd::gd_coerce_bool(lv_removable);
    this->f_bonusMinDam = gd::gd_coerce_float(gd::gd_sub(this->f_bonusMinDam, lv_damage));
    this->f_bonusMaxDam = gd::gd_coerce_float(gd::gd_sub(this->f_bonusMaxDam, lv_damage));
    if (gd::gd_truth(lv_removable)) {
        this->f_removableDam = gd::gd_coerce_float(gd::gd_sub(this->f_removableDam, lv_damage));
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_MinDamage_2557)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_MaxDamage_2558)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    if (gd::gd_truth(lv_showLabel)) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_DamageBuff_2560), gd::gd_neg(lv_damage)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_spawnLabel_381, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_purgeDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_purgable = gd::gd_min(lv_damage, this->f_removableDam);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_purgable, gd::GdVal::from_int(0LL))))) {
        this->f_removableDam = gd::gd_coerce_float(gd::gd_sub(this->f_removableDam, lv_purgable));
        this->f_bonusMinDam = gd::gd_coerce_float(gd::gd_sub(this->f_bonusMinDam, lv_purgable));
        this->f_bonusMaxDam = gd::gd_coerce_float(gd::gd_sub(this->f_bonusMaxDam, lv_purgable));
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_MinDamage_2557)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_MaxDamage_2558)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_DamageBuff_2560), gd::gd_neg(lv_purgable)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_spawnLabel_381, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveDoubleActivationChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_doubleActivationChance = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_doubleActivationChance, gd::gd_div(gd_ctx, lv__chance, gd::GdVal::from_float(100.0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveDoubleAttackEffectChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_doubleAttackEffectChance = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_doubleAttackEffectChance, gd::gd_div(gd_ctx, lv__chance, gd::GdVal::from_float(100.0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveCritTokens(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_gainCritTokens_1168, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveMaxStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_giveMaxStamina_317, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveMaxStaminaTemporary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_filled = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(true));
    lv_filled = gd::gd_coerce_bool(lv_filled);
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent, lv_filled}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_gainMaxStaminaTemporary_1252, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveMaxHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_amount, gd::GdVal::null())))) {
        lv_amount = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })();
    }
    lv_amount = ([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_applyTemporaryMaxHealthGain_1145, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemMetrics_1367), SYM_GEN_MaxHealth_2587), lv_amount, gd::GdVal::null(), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addMetric_232, _ca, 4); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeMaxHealthTemporary_1146, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_TemporaryMaxHealth_2588), lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_spawnLabel_381, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(1LL));
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_gainStamina_1148, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_inflictFatigueDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_fatigueIncrease = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(1LL));
    (void)([&]() { gd::GdVal _ca[] = {lv_fatigueIncrease}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_addFatigueDamage_1179, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_takeFatigueDamage_1180, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_sendCharge(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_durPerTile = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_durPerTile = gd::gd_coerce_float(lv_durPerTile);
    gd::GdVal lv_cells = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_speedFactor = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_speedFactor = gd::gd_coerce_float(lv_speedFactor);
    gd::GdVal lv_event = (_argc > 3) ? _args[3] : gd::GdVal::null();
    gd::GdVal lv_chargeDuration = gd::gd_mul(lv_durPerTile, gd::gd_sub(gd::call_method(gd_ctx, lv_cells, gd::SYM_size, nullptr, 0), gd::GdVal::from_int(1LL)));
    gd::GdVal lv_inv_cells = ([&]() { gd::GdVal _ca[] = {lv_cells}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__chargeInventoryCells_323, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreItem__INNER__CoreElectricalCharge), gd::SYM_new, nullptr, 0), gd::GdVal::from_int(1LL), lv_inv_cells}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__chargeEnterCell_325, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_cells, gd::gd_div(gd_ctx, lv_chargeDuration, lv_speedFactor), lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_sendCharge_322, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_int(12LL)), gd::gd_neg(gd::GdVal::from_int(5LL))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.7), gd::GdVal::from_float(1.3)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn__chargeInventoryCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_cells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_top_left = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getTopLeftCell_445, nullptr, 0);
    gd::GdVal lv_inv = (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_inventory, gd::GdVal::null()))) ? (this->f_inventory) : (gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getOwnOrPlayerInventory_402, nullptr, 0)));
    gd::GdVal lv_out = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t101 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
        gd::GdArr* _t102 = (_t101.kind == gd::GdVal::Kind::Arr) ? _t101.arr : nullptr;
        uint32_t _len__t103 = _t102 ? _t102->len : 0u;
        for (uint32_t _t103 = 0; _t103 < _len__t103; ++_t103) {
            gd::GdVal lv_c = _t102->data[_t103];
            gd::GdVal lv_v = gd::gd_sub(gd::gd_add(gd_ctx, lv_top_left, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_vec2((gd::get_prop(gd_ctx, lv_c, gd::SYM_x)).as_float(), (gd::get_prop(gd_ctx, lv_c, gd::SYM_y)).as_float()), this->f_faceDirection}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__rotVecQuarterTurns_324, _ca, 2); })()), gd::get_index(gd_ctx, this->f_chargeFrame, gd::gd_mod(gd_ctx, this->f_faceDirection, gd::GdVal::from_int(4LL))));
            gd::GdVal lv_hit_cells = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_v}))}; return gd::call_method(gd_ctx, lv_inv, SYM_GEN_getCellsForGlobalPositions_403, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, lv_hit_cells, gd::GdVal::from_int(0LL))}; return gd::call_method(gd_ctx, lv_out, gd::SYM_push_back, _ca, 1); })();
        }
    }
    return lv_out;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn__rotVecQuarterTurns(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_v = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_n = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_n = gd::gd_coerce_int(lv_n);
    lv_n = gd::gd_coerce_int(gd::gd_mod(gd_ctx, lv_n, gd::GdVal::from_int(4LL)));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_n, gd::GdVal::from_int(0LL))))) {
        lv_n = gd::gd_coerce_int(gd::gd_add(gd_ctx, lv_n, gd::GdVal::from_int(4LL)));
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_n, gd::GdVal::from_int(1LL))))) {
        return gd::GdVal::from_vec2((gd::gd_neg(gd::get_prop(gd_ctx, lv_v, gd::SYM_y))).as_float(), (gd::get_prop(gd_ctx, lv_v, gd::SYM_x)).as_float());
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_n, gd::GdVal::from_int(2LL))))) {
        return gd::GdVal::from_vec2((gd::gd_neg(gd::get_prop(gd_ctx, lv_v, gd::SYM_x))).as_float(), (gd::gd_neg(gd::get_prop(gd_ctx, lv_v, gd::SYM_y))).as_float());
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_n, gd::GdVal::from_int(3LL))))) {
        return gd::GdVal::from_vec2((gd::get_prop(gd_ctx, lv_v, gd::SYM_y)).as_float(), (gd::gd_neg(gd::get_prop(gd_ctx, lv_v, gd::SYM_x))).as_float());
    }
    return lv_v;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn__chargeEnterCell(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_cell_index = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_cell_index = gd::gd_coerce_int(lv_cell_index);
    gd::GdVal lv_inv_cells = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::set_prop(gd_ctx, lv_charge, SYM_GEN_lastChargedItem_1556, gd::get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1557));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_cell_index, gd::call_method(gd_ctx, lv_inv_cells, gd::SYM_size, nullptr, 0))))) {
        gd::set_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1557, gd::GdVal::null());
    }
    else {
        gd::GdVal lv_inv = (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_inventory, gd::GdVal::null()))) ? (this->f_inventory) : (gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getOwnOrPlayerInventory_402, nullptr, 0)));
        gd::set_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1557, ([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, lv_inv_cells, lv_cell_index)}; return gd::call_method(gd_ctx, lv_inv, SYM_GEN_getItemInCell_1516, _ca, 1); })());
    }
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onChargeEnteredCell", 19u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })())) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onChargeEnteredCell", 19u)), lv_charge, lv_cell_index}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_call, _ca, 3); })();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1557), gd::get_prop(gd_ctx, lv_charge, SYM_GEN_lastChargedItem_1556))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_charge, SYM_GEN_lastChargedItem_1556), gd::GdVal::null())))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_charge}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_charge, SYM_GEN_lastChargedItem_1556), SYM_GEN_chargeLeft_327, _ca, 1); })();
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1557), gd::GdVal::null())))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_charge}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1557), SYM_GEN_chargeReceived_326, _ca, 1); })();
            if (gd::gd_truth(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1557), SYM_GEN_hasOnChargeReceivedEffect_67))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(4.0), gd::GdVal::from_float(4.02)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_chargeReceived(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_numCharges = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_numCharges, gd::GdVal::from_int(1LL)));
    if (gd::gd_truth(this->f_hasOnChargeReceivedEffect)) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onChargeReceived", 16u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_charge}))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_506, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_chargeLeft(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_numCharges = gd::gd_coerce_int(gd::gd_sub(this->f_numCharges, gd::GdVal::from_int(1LL)));
    if (gd::gd_truth(this->f_hasOnChargeLeftEffect)) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onChargeLeft", 12u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_charge}))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_506, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_changeChargedItemStat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_cellIndex = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_flatVal = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_valPerTile = (_argc > 3) ? _args[3] : gd::GdVal::null();
    gd::GdVal lv_previousVal = gd::gd_add(gd_ctx, lv_flatVal, gd::gd_mul(gd::gd_sub(lv_cellIndex, gd::GdVal::from_int(2LL)), lv_valPerTile));
    gd::GdVal lv_newVal = gd::gd_add(gd_ctx, lv_previousVal, lv_valPerTile);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "CHRG", 4u)), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1577))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "@", 1u))), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getTopLeftCell_445, nullptr, 0)))), gd::gd_coerce_int(lv_cellIndex), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "last=", 5u)), (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_charge, SYM_GEN_lastChargedItem_1556), gd::GdVal::null()))) ? (gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv_charge, SYM_GEN_lastChargedItem_1556), SYM_GEN_descriptor_2), SYM_GEN_identifier_1577)))) : (gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "null", 4u))))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " cur=", 5u))), (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1557), gd::GdVal::null()))) ? (gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1557), SYM_GEN_descriptor_2), SYM_GEN_identifier_1577)))) : (gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "null", 4u))))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " del=", 5u))), ([&]() { gd::GdVal _ca[] = {gd::gd_neg(lv_previousVal)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " add=", 5u))), ([&]() { gd::GdVal _ca[] = {lv_newVal}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_trace_diag_1645, _ca, 4); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_charge, SYM_GEN_lastChargedItem_1556), gd::GdVal::null())))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1557), gd::GdVal::null())))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "chargedItemStatChange", 21u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::get_prop(gd_ctx, lv_charge, SYM_GEN_lastChargedItem_1556), gd::gd_neg(lv_previousVal)}))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_506, _ca, 2); })();
        }
        else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1557), gd::get_prop(gd_ctx, lv_charge, SYM_GEN_lastChargedItem_1556))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "chargedItemStatChange", 21u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1557), lv_valPerTile}))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_506, _ca, 2); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "chargedItemStatChange", 21u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::get_prop(gd_ctx, lv_charge, SYM_GEN_lastChargedItem_1556), gd::gd_neg(lv_previousVal)}))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_506, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "chargedItemStatChange", 21u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1557), lv_newVal}))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_506, _ca, 2); })();
        }
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1557), gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "chargedItemStatChange", 21u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::get_prop(gd_ctx, lv_charge, SYM_GEN_curChargedItem_1557), lv_newVal}))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_506, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_heal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_amount, gd::GdVal::null())))) {
        lv_amount = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })();
    }
    else {
        lv_amount = gd::gd_coerce_int(lv_amount);
    }
    gd::GdVal lv_healed = ([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_heal_329, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_healthToBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_health = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_health = gd::gd_coerce_float(lv_health);
    gd::GdVal lv_block = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_clampedHealth = gd::gd_min(lv_health, gd::gd_sub(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getCurrentHealth_1138, nullptr, 0), gd::GdVal::from_int(1LL)));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_clampedHealth, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_clampedHealth, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_loseHealth_1141, _ca, 3); })();
        lv_block = gd::gd_ceil(gd::gd_mul(gd::gd_div(gd_ctx, lv_clampedHealth, lv_health), lv_block));
        (void)([&]() { gd::GdVal _ca[] = {lv_block, gd::GdVal::from_bool(true), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_stealLife(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_lifestealFactor = (_argc > 1) ? _args[1] : (gd::GdVal::from_float(1.0));
    lv_lifestealFactor = gd::gd_coerce_float(lv_lifestealFactor);
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_damage}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_stealLifeDamageSource_1403), SYM_GEN_updateEffect_1463, _ca, 2); })();
    gd::GdVal lv_damageRes = ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_stealLifeDamageSource_1403), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_takeDamage_1132, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427), lv_lifestealFactor), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, _ca, 2); })();
    return lv_damageRes;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_stun(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_duration = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_duration, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_stun_332, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_checkMana(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getMana_1228, nullptr, 0), lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_useMana(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_useMana_334, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_tryUseMana(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_curMana = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getMana_1228, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_curMana, lv_amount)))) {
        return gd::GdVal::null();
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {lv_amount, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_334, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_removeMana(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_loseMana_1231, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveMana_capped(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_maximum = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    lv_amount = gd::gd_round(gd::gd_mul(lv_amount, gd::get_index(gd_ctx, this->f_buffPowers, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Mana_2571))));
    gd::GdVal lv_curMana = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getMana_1228, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_maximum, lv_curMana)))) {
        gd::GdVal lv_missingMana = gd::gd_sub(lv_maximum, lv_curMana);
        gd::GdVal lv_manaGiven = gd::gd_min(lv_amount, lv_missingMana);
        (void)([&]() { gd::GdVal _ca[] = {lv_manaGiven, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_gainMana_1230, _ca, 3); })();
        return gd::gd_sub(lv_amount, lv_manaGiven);
    }
    else {
        return lv_amount;
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_removeSpikes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_loseSpikes_340, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_useSpikes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Spikes_2565), lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_useStacks_1203, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_loseSpikes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_loseSpikes_340, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_removeVampirism(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_loseVampirism_343, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_useVampirism(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Vampirism_2566), lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_useStacks_1203, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_loseVampirism(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_loseVampirism_343, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_cleansePoison(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_curPoison = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getPoison_1213, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_curPoison, gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::from_int(0LL);
    }
    lv_amount = gd::gd_coerce_int(gd::gd_min(lv_curPoison, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_losePoison_1216, _ca, 3); })();
    return lv_amount;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_selfInflictBlind(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Blind_2568), lv_amount, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_cleanseBlind(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_curBlind = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getBlind_1224, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_curBlind, gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::from_int(0LL);
    }
    lv_amount = gd::gd_coerce_int(gd::gd_min(lv_curBlind, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_loseBlind_1227, _ca, 3); })();
    return lv_amount;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_removeRegeneration(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_loseRegeneration_1220, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_useRegeneration(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Regeneration_2569), lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_useStacks_1203, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_tryUseLucky(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getLucky_1221, nullptr, 0), lv_amount)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_amount, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useLucky_352, _ca, 2); })();
        return gd::GdVal::from_bool(true);
    }
    else {
        return gd::GdVal::from_bool(false);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_loseLucky(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_loseLucky_350, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_removeLucky(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_loseLucky_350, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_useLucky(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Lucky_2570), lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_useStacks_1203, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_inflictCold(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Cold_2574), lv_amount, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_cleanseCold(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_curCold = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getCold_1238, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_curCold, gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::from_int(0LL);
    }
    lv_amount = gd::gd_coerce_int(gd::gd_min(lv_curCold, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_loseCold_1241, _ca, 3); })();
    return lv_amount;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_loseHeat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_loseHeat_355, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_useHeat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Heat_2573), lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_useStacks_1203, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_loseEmpower(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_loseEmpower_357, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_cleanseRandomDebuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numDebuffs = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_cleansedDebuffs = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1362, nullptr, 0), lv_numDebuffs, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_pickRandomStacks_360, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreEventBus), SYM_GEN_LoggingMode_1508), SYM_GEN_Delayed_2589)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_setLoggingMode_1497, _ca, 1); })();
    {
        gd::GdVal _t104 = gd::gd_iter_seq(gd_ctx.arena, lv_cleansedDebuffs);
        gd::GdArr* _t105 = (_t104.kind == gd::GdVal::Kind::Arr) ? _t104.arr : nullptr;
        uint32_t _len__t106 = _t105 ? _t105->len : 0u;
        for (uint32_t _t106 = 0; _t106 < _len__t106; ++_t106) {
            gd::GdVal lv_debuff = _t105->data[_t106];
            (void)([&]() { gd::GdVal _ca[] = {lv_debuff, gd::get_index(gd_ctx, lv_cleansedDebuffs, lv_debuff), gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_loseStacks_1031, _ca, 4); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_flushLoggingQueue_1500, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_inflictRandomDebuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numDebuffs = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_availableDebuffs = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_availableDebuffs, gd::GdVal::null())))) {
        lv_availableDebuffs = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1362, nullptr, 0);
    }
    gd::GdVal lv_pickedDebuffs = ([&]() { gd::GdVal _ca[] = {lv_availableDebuffs, lv_numDebuffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_pickRandomStacksToGive_361, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreEventBus), SYM_GEN_LoggingMode_1508), SYM_GEN_Delayed_2589)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_setLoggingMode_1497, _ca, 1); })();
    {
        gd::GdVal _t107 = gd::gd_iter_seq(gd_ctx.arena, lv_pickedDebuffs);
        gd::GdArr* _t108 = (_t107.kind == gd::GdVal::Kind::Arr) ? _t107.arr : nullptr;
        uint32_t _len__t109 = _t108 ? _t108->len : 0u;
        for (uint32_t _t109 = 0; _t109 < _len__t109; ++_t109) {
            gd::GdVal lv_debuff = _t108->data[_t109];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), lv_debuff, gd::get_index(gd_ctx, lv_pickedDebuffs, lv_debuff), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 4); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_flushLoggingQueue_1500, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_pickRandomStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stackTypes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_numStacks = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_target = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_priorityStack = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_stacks = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t110 = gd::gd_iter_seq(gd_ctx.arena, lv_stackTypes);
        gd::GdArr* _t111 = (_t110.kind == gd::GdVal::Kind::Arr) ? _t110.arr : nullptr;
        uint32_t _len__t112 = _t111 ? _t111->len : 0u;
        for (uint32_t _t112 = 0; _t112 < _len__t112; ++_t112) {
            gd::GdVal lv_stackType = _t111->data[_t112];
            gd::GdVal lv_numTargetStacks = ([&]() { gd::GdVal _ca[] = {lv_stackType}; return gd::call_method(gd_ctx, lv_target, SYM_GEN_getStacks_1022, _ca, 1); })();
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numTargetStacks, gd::GdVal::from_int(0LL))))) {
                { gd::GdVal _t113 = lv_stacks; gd::GdVal _t114 = lv_stackType; gd::set_index(gd_ctx, _t113, _t114, lv_numTargetStacks); }
            }
        }
    }
    gd::GdVal lv_pickedStacks = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_priorityStack, gd::GdVal::null())))) {
        gd::GdVal lv_pickedPriorityStacks = gd::gd_min(lv_numStacks, ([&]() { gd::GdVal _ca[] = {lv_priorityStack, gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, lv_stacks, gd::SYM_get, _ca, 2); })());
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_pickedPriorityStacks, gd::GdVal::from_int(0LL))))) {
            { gd::GdVal _t115 = lv_pickedStacks; gd::GdVal _t116 = lv_priorityStack; gd::set_index(gd_ctx, _t115, _t116, lv_pickedPriorityStacks); }
            lv_numStacks = gd::gd_sub(lv_numStacks, lv_pickedPriorityStacks);
            (void)([&]() { gd::GdVal _ca[] = {lv_stacks, lv_priorityStack, lv_pickedPriorityStacks}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_dictSub_1695, _ca, 3); })();
        }
    }
    {
        gd::GdVal _t117 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {lv_numStacks}; return gd::gd_range(gd_ctx.arena, _ca, 1); })());
        gd::GdArr* _t118 = (_t117.kind == gd::GdVal::Kind::Arr) ? _t117.arr : nullptr;
        uint32_t _len__t119 = _t118 ? _t118->len : 0u;
        for (uint32_t _t119 = 0; _t119 < _len__t119; ++_t119) {
            gd::GdVal lv_i = _t118->data[_t119];
            if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_stacks, gd::SYM_empty, nullptr, 0))))) {
                gd::GdVal lv_stackType = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, lv_stacks, gd::SYM_keys, nullptr, 0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_pickRandomElement_1650, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {lv_pickedStacks, lv_stackType, gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_dictAdd_1694, _ca, 3); })();
                (void)([&]() { gd::GdVal _ca[] = {lv_stacks, lv_stackType, gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_dictSub_1695, _ca, 3); })();
            }
        }
    }
    return lv_pickedStacks;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_pickRandomStacksToGive(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stackTypes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_numStacks = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_pickedStacks = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t120 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {lv_numStacks}; return gd::gd_range(gd_ctx.arena, _ca, 1); })());
        gd::GdArr* _t121 = (_t120.kind == gd::GdVal::Kind::Arr) ? _t120.arr : nullptr;
        uint32_t _len__t122 = _t121 ? _t121->len : 0u;
        for (uint32_t _t122 = 0; _t122 < _len__t122; ++_t122) {
            gd::GdVal lv_i = _t121->data[_t122];
            gd::GdVal lv_stackType = ([&]() { gd::GdVal _ca[] = {lv_stackTypes}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_pickRandomElement_1650, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_pickedStacks, lv_stackType, gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_dictAdd_1694, _ca, 3); })();
        }
    }
    return lv_pickedStacks;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getLeastStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numStacks = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_target = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_availableStacks = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_priorStacks = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t123 = gd::gd_iter_seq(gd_ctx.arena, lv_availableStacks);
        gd::GdArr* _t124 = (_t123.kind == gd::GdVal::Kind::Arr) ? _t123.arr : nullptr;
        uint32_t _len__t125 = _t124 ? _t124->len : 0u;
        for (uint32_t _t125 = 0; _t125 < _len__t125; ++_t125) {
            gd::GdVal lv_stackType = _t124->data[_t125];
            { gd::GdVal _t126 = lv_priorStacks; gd::GdVal _t127 = lv_stackType; gd::set_index(gd_ctx, _t126, _t127, ([&]() { gd::GdVal _ca[] = {lv_stackType}; return gd::call_method(gd_ctx, lv_target, SYM_GEN_getStacks_1022, _ca, 1); })()); }
        }
    }
    gd::GdVal lv_pickedStacks = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    while (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numStacks, gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_leastStacksCount = gd::gd_coerce_int(gd::GdVal::from_int(10000LL));
        gd::GdVal lv_leastStacks = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
        {
            gd::GdVal _t128 = gd::gd_iter_seq(gd_ctx.arena, lv_priorStacks);
            gd::GdArr* _t129 = (_t128.kind == gd::GdVal::Kind::Arr) ? _t128.arr : nullptr;
            uint32_t _len__t130 = _t129 ? _t129->len : 0u;
            for (uint32_t _t130 = 0; _t130 < _len__t130; ++_t130) {
                gd::GdVal lv_stackType = _t129->data[_t130];
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::get_index(gd_ctx, lv_priorStacks, lv_stackType), lv_leastStacksCount)))) {
                    lv_leastStacksCount = gd::gd_coerce_int(gd::get_index(gd_ctx, lv_priorStacks, lv_stackType));
                    (void)gd::call_method(gd_ctx, lv_leastStacks, gd::SYM_clear, nullptr, 0);
                    (void)([&]() { gd::GdVal _ca[] = {lv_stackType}; return gd::call_method(gd_ctx, lv_leastStacks, gd::SYM_push_back, _ca, 1); })();
                }
                else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_index(gd_ctx, lv_priorStacks, lv_stackType), lv_leastStacksCount)))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_stackType}; return gd::call_method(gd_ctx, lv_leastStacks, gd::SYM_push_back, _ca, 1); })();
                }
            }
        }
        gd::GdVal lv_stackToGive = ([&]() { gd::GdVal _ca[] = {lv_leastStacks}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_pickRandomElement_1650, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_pickedStacks, lv_stackToGive, gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_dictAdd_1694, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_priorStacks, lv_stackToGive, gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_dictAdd_1694, _ca, 3); })();
        lv_numStacks = gd::gd_sub(lv_numStacks, gd::GdVal::from_int(1LL));
    }
    return lv_pickedStacks;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getMostStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_target = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_availableStacks = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_buffs = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t131 = gd::gd_iter_seq(gd_ctx.arena, lv_availableStacks);
        gd::GdArr* _t132 = (_t131.kind == gd::GdVal::Kind::Arr) ? _t131.arr : nullptr;
        uint32_t _len__t133 = _t132 ? _t132->len : 0u;
        for (uint32_t _t133 = 0; _t133 < _len__t133; ++_t133) {
            gd::GdVal lv_buff = _t132->data[_t133];
            { gd::GdVal _t134 = lv_buffs; gd::GdVal _t135 = lv_buff; gd::set_index(gd_ctx, _t134, _t135, ([&]() { gd::GdVal _ca[] = {lv_buff}; return gd::call_method(gd_ctx, lv_target, SYM_GEN_getStacks_1022, _ca, 1); })()); }
        }
    }
    gd::GdVal lv_maxBuffs = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    gd::GdVal lv_maxStacks = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t136 = gd::gd_iter_seq(gd_ctx.arena, lv_buffs);
        gd::GdArr* _t137 = (_t136.kind == gd::GdVal::Kind::Arr) ? _t136.arr : nullptr;
        uint32_t _len__t138 = _t137 ? _t137->len : 0u;
        for (uint32_t _t138 = 0; _t138 < _len__t138; ++_t138) {
            gd::GdVal lv_buff = _t137->data[_t138];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_index(gd_ctx, lv_buffs, lv_buff), lv_maxStacks)))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_buff}; return gd::call_method(gd_ctx, lv_maxBuffs, gd::SYM_push_back, _ca, 1); })();
            }
            else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_index(gd_ctx, lv_buffs, lv_buff), lv_maxStacks)))) {
                (void)gd::call_method(gd_ctx, lv_maxBuffs, gd::SYM_clear, nullptr, 0);
                (void)([&]() { gd::GdVal _ca[] = {lv_buff}; return gd::call_method(gd_ctx, lv_maxBuffs, gd::SYM_push_back, _ca, 1); })();
                lv_maxStacks = gd::get_index(gd_ctx, lv_buffs, lv_buff);
            }
        }
    }
    return lv_maxBuffs;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getStackFraction(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_target = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_fraction = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_fraction = gd::gd_coerce_float(lv_fraction);
    gd::GdVal lv_limit = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_limit = gd::gd_coerce_int(lv_limit);
    gd::GdVal lv_availableStacks = (_argc > 3) ? _args[3] : gd::GdVal::null();
    gd::GdVal lv_sum = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    gd::GdVal lv_stacksUnlimited = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t139 = gd::gd_iter_seq(gd_ctx.arena, lv_availableStacks);
        gd::GdArr* _t140 = (_t139.kind == gd::GdVal::Kind::Arr) ? _t139.arr : nullptr;
        uint32_t _len__t141 = _t140 ? _t140->len : 0u;
        for (uint32_t _t141 = 0; _t141 < _len__t141; ++_t141) {
            gd::GdVal lv_buff = _t140->data[_t141];
            gd::GdVal lv_prior = ([&]() { gd::GdVal _ca[] = {lv_buff}; return gd::call_method(gd_ctx, lv_target, SYM_GEN_getStacks_1022, _ca, 1); })();
            gd::GdVal lv_withBonus = gd::gd_mul(lv_prior, lv_fraction);
            { gd::GdVal _t142 = lv_stacksUnlimited; gd::GdVal _t143 = lv_buff; gd::set_index(gd_ctx, _t142, _t143, lv_withBonus); }
            lv_sum = gd::gd_coerce_float(gd::gd_add(gd_ctx, lv_sum, lv_withBonus));
        }
    }
    gd::GdVal lv_sumRounded = gd::gd_round(lv_sum);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_sumRounded, gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_totalToGive = gd::gd_coerce_float(gd::gd_min(lv_limit, lv_sumRounded));
    gd::GdVal lv_limitFactor = gd::gd_div(gd_ctx, lv_totalToGive, lv_sumRounded);
    gd::GdVal lv_buffsToGive = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    gd::GdVal lv_overflow = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    gd::GdVal lv_totalGiven = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    {
        gd::GdVal _t144 = gd::gd_iter_seq(gd_ctx.arena, lv_stacksUnlimited);
        gd::GdArr* _t145 = (_t144.kind == gd::GdVal::Kind::Arr) ? _t144.arr : nullptr;
        uint32_t _len__t146 = _t145 ? _t145->len : 0u;
        for (uint32_t _t146 = 0; _t146 < _len__t146; ++_t146) {
            gd::GdVal lv_buff = _t145->data[_t146];
            gd::GdVal lv_limited = gd::gd_mul(gd::get_index(gd_ctx, lv_stacksUnlimited, lv_buff), lv_limitFactor);
            gd::GdVal lv_guaranteed = gd::gd_coerce_int(lv_limited);
            { gd::GdVal _t147 = lv_buffsToGive; gd::GdVal _t148 = lv_buff; gd::set_index(gd_ctx, _t147, _t148, lv_guaranteed); }
            { gd::GdVal _t149 = lv_overflow; gd::GdVal _t150 = lv_buff; gd::set_index(gd_ctx, _t149, _t150, gd::gd_sub(lv_limited, lv_guaranteed)); }
            lv_totalGiven = gd::gd_coerce_int(gd::gd_add(gd_ctx, lv_totalGiven, lv_guaranteed));
        }
    }
    gd::GdVal lv_overflowBuffs = gd::gd_coerce_int(gd::gd_sub(lv_totalToGive, lv_totalGiven));
    gd::GdVal lv_sortedOverflow = gd::call_method(gd_ctx, lv_overflow, gd::SYM_keys, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {lv_sortedOverflow, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Items/Item.gd:5642", 18u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_shuffleEngine_1651, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_overflow}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_DictSorter_1713), gd::SYM_new, _ca, 1); })(), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "sort", 4u))}; return gd::call_method(gd_ctx, lv_sortedOverflow, gd::SYM_sort_custom, _ca, 2); })();
    {
        gd::GdVal _t151 = gd::gd_iter_seq(gd_ctx.arena, lv_sortedOverflow);
        gd::GdArr* _t152 = (_t151.kind == gd::GdVal::Kind::Arr) ? _t151.arr : nullptr;
        uint32_t _len__t153 = _t152 ? _t152->len : 0u;
        for (uint32_t _t153 = 0; _t153 < _len__t153; ++_t153) {
            gd::GdVal lv_buff = _t152->data[_t153];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_overflowBuffs, gd::GdVal::from_int(0LL))))) {
                break;
            }
            { gd::GdVal _t154 = lv_buffsToGive; gd::GdVal _t155 = lv_buff; gd::set_index(gd_ctx, _t154, _t155, gd::gd_add(gd_ctx, gd::get_index(gd_ctx, _t154, _t155), gd::GdVal::from_int(1LL))); }
            lv_overflowBuffs = gd::gd_coerce_int(gd::gd_sub(lv_overflowBuffs, gd::GdVal::from_int(1LL)));
        }
    }
    return lv_buffsToGive;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_multiplyBuffsLimit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_bonus = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_bonus = gd::gd_coerce_float(lv_bonus);
    gd::GdVal lv_limit = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_limit = gd::gd_coerce_int(lv_limit);
    gd::GdVal lv_availableBuffs = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_availableBuffs, gd::GdVal::null())))) {
        lv_availableBuffs = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0);
    }
    gd::GdVal lv_buffsToGive = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), lv_bonus, lv_limit, lv_availableBuffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStackFraction_364, _ca, 4); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_buffsToGive, gd::GdVal::null())))) {
        return gd::GdVal::null();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreEventBus), SYM_GEN_LoggingMode_1508), SYM_GEN_Delayed_2589)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_setLoggingMode_1497, _ca, 1); })();
    {
        gd::GdVal _t156 = gd::gd_iter_seq(gd_ctx.arena, lv_buffsToGive);
        gd::GdArr* _t157 = (_t156.kind == gd::GdVal::Kind::Arr) ? _t156.arr : nullptr;
        uint32_t _len__t158 = _t157 ? _t157->len : 0u;
        for (uint32_t _t158 = 0; _t158 < _len__t158; ++_t158) {
            gd::GdVal lv_buff = _t157->data[_t158];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), lv_buff, gd::get_index(gd_ctx, lv_buffsToGive, lv_buff)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 3); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_flushLoggingQueue_1500, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_removeBuffsFraction(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_fraction = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_fraction = gd::gd_coerce_float(lv_fraction);
    gd::GdVal lv_limit = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_limit = gd::gd_coerce_int(lv_limit);
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_availableBuffs = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_availableBuffs, gd::GdVal::null())))) {
        lv_availableBuffs = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0);
    }
    gd::GdVal lv_buffsToRemove = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), lv_fraction, lv_limit, lv_availableBuffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStackFraction_364, _ca, 4); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_buffsToRemove, gd::GdVal::null())))) {
        return gd::GdVal::null();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreEventBus), SYM_GEN_LoggingMode_1508), SYM_GEN_Delayed_2589)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_setLoggingMode_1497, _ca, 1); })();
    {
        gd::GdVal _t159 = gd::gd_iter_seq(gd_ctx.arena, lv_buffsToRemove);
        gd::GdArr* _t160 = (_t159.kind == gd::GdVal::Kind::Arr) ? _t159.arr : nullptr;
        uint32_t _len__t161 = _t160 ? _t160->len : 0u;
        for (uint32_t _t161 = 0; _t161 < _len__t161; ++_t161) {
            gd::GdVal lv_buff = _t160->data[_t161];
            (void)([&]() { gd::GdVal _ca[] = {lv_buff, gd::get_index(gd_ctx, lv_buffsToRemove, lv_buff), gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_loseStacks_1031, _ca, 4); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_flushLoggingQueue_1500, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_stealBuffsFraction(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_fraction = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_fraction = gd::gd_coerce_float(lv_fraction);
    gd::GdVal lv_limit = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_limit = gd::gd_coerce_int(lv_limit);
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_availableBuffs = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_availableBuffs, gd::GdVal::null())))) {
        lv_availableBuffs = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0);
    }
    gd::GdVal lv_buffsToSteal = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), lv_fraction, lv_limit, lv_availableBuffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStackFraction_364, _ca, 4); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_buffsToSteal, gd::GdVal::null())))) {
        return gd::GdVal::null();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreEventBus), SYM_GEN_LoggingMode_1508), SYM_GEN_Delayed_2589)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_setLoggingMode_1497, _ca, 1); })();
    {
        gd::GdVal _t162 = gd::gd_iter_seq(gd_ctx.arena, lv_buffsToSteal);
        gd::GdArr* _t163 = (_t162.kind == gd::GdVal::Kind::Arr) ? _t162.arr : nullptr;
        uint32_t _len__t164 = _t163 ? _t163->len : 0u;
        for (uint32_t _t164 = 0; _t164 < _len__t164; ++_t164) {
            gd::GdVal lv_buff = _t163->data[_t164];
            (void)([&]() { gd::GdVal _ca[] = {lv_buff, gd::get_index(gd_ctx, lv_buffsToSteal, lv_buff), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealStack_210, _ca, 3); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_flushLoggingQueue_1500, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveLeastBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numBuffs = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_target = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_availableBuffs = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_target, gd::GdVal::null())))) {
        lv_target = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0);
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_availableBuffs, gd::GdVal::null())))) {
        lv_availableBuffs = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0);
    }
    gd::GdVal lv_pickedStacks = ([&]() { gd::GdVal _ca[] = {lv_numBuffs, lv_target, lv_availableBuffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getLeastStacks_362, _ca, 3); })();
    {
        gd::GdVal _t165 = gd::gd_iter_seq(gd_ctx.arena, lv_pickedStacks);
        gd::GdArr* _t166 = (_t165.kind == gd::GdVal::Kind::Arr) ? _t165.arr : nullptr;
        uint32_t _len__t167 = _t166 ? _t166->len : 0u;
        for (uint32_t _t167 = 0; _t167 < _len__t167; ++_t167) {
            gd::GdVal lv_buffType = _t166->data[_t167];
            (void)([&]() { gd::GdVal _ca[] = {lv_target, lv_buffType, gd::get_index(gd_ctx, lv_pickedStacks, lv_buffType), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 4); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveMostBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numBuffs = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_availableBuffs = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_availableBuffs, gd::GdVal::null())))) {
        lv_availableBuffs = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0);
    }
    gd::GdVal lv_maxBuffs = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), lv_availableBuffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMostStacks_363, _ca, 2); })();
    gd::GdVal lv_buffToGive = ([&]() { gd::GdVal _ca[] = {lv_maxBuffs}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_pickRandomElement_1650, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), lv_buffToGive, lv_numBuffs, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_removeMostBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numBuffs = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_use = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(false));
    lv_use = gd::gd_coerce_bool(lv_use);
    gd::GdVal lv_availableBuffs = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_availableBuffs, gd::GdVal::null())))) {
        lv_availableBuffs = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0);
    }
    gd::GdVal lv_target = gd::GdVal::null();
    gd::GdVal lv_buffs = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    if (gd::gd_truth(lv_use)) {
        lv_target = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0);
    }
    else {
        lv_target = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0);
    }
    gd::GdVal lv_maxBuffs = ([&]() { gd::GdVal _ca[] = {lv_target, lv_availableBuffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMostStacks_363, _ca, 2); })();
    gd::GdVal lv_buffToRemove = ([&]() { gd::GdVal _ca[] = {lv_maxBuffs}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_pickRandomElement_1650, _ca, 1); })();
    gd::GdVal lv_toRemove = gd::gd_min(lv_numBuffs, ([&]() { gd::GdVal _ca[] = {lv_buffToRemove}; return gd::call_method(gd_ctx, lv_target, SYM_GEN_getStacks_1022, _ca, 1); })());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_toRemove, gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_event = gd::GdVal::null();
    if (gd::gd_truth(lv_use)) {
        lv_event = ([&]() { gd::GdVal _ca[] = {lv_buffToRemove, lv_toRemove, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_useStacks_1203, _ca, 4); })();
    }
    else {
        lv_event = ([&]() { gd::GdVal _ca[] = {lv_buffToRemove, lv_toRemove, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_loseStacks_1031, _ca, 4); })();
    }
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveRandomBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numBuffs = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_numBuffs = gd::gd_coerce_int(lv_numBuffs);
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_availableBuffs = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_target = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_availableBuffs, gd::GdVal::null())))) {
        lv_availableBuffs = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0);
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_target, gd::GdVal::null())))) {
        lv_target = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0);
    }
    gd::GdVal lv_pickedBuffs = ([&]() { gd::GdVal _ca[] = {lv_availableBuffs, lv_numBuffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_pickRandomStacksToGive_361, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreEventBus), SYM_GEN_LoggingMode_1508), SYM_GEN_Delayed_2589)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_setLoggingMode_1497, _ca, 1); })();
    {
        gd::GdVal _t168 = gd::gd_iter_seq(gd_ctx.arena, lv_pickedBuffs);
        gd::GdArr* _t169 = (_t168.kind == gd::GdVal::Kind::Arr) ? _t168.arr : nullptr;
        uint32_t _len__t170 = _t169 ? _t169->len : 0u;
        for (uint32_t _t170 = 0; _t170 < _len__t170; ++_t170) {
            gd::GdVal lv_buff = _t169->data[_t170];
            (void)([&]() { gd::GdVal _ca[] = {lv_target, lv_buff, gd::get_index(gd_ctx, lv_pickedBuffs, lv_buff), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 4); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_flushLoggingQueue_1500, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_giveAllBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numBuffs = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(1LL));
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    {
        gd::GdVal _t171 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0));
        gd::GdArr* _t172 = (_t171.kind == gd::GdVal::Kind::Arr) ? _t171.arr : nullptr;
        uint32_t _len__t173 = _t172 ? _t172->len : 0u;
        for (uint32_t _t173 = 0; _t173 < _len__t173; ++_t173) {
            gd::GdVal lv_buff = _t172->data[_t173];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), lv_buff, lv_numBuffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_useRandomBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numBuffs = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_availableBuffs = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_availableBuffs, gd::GdVal::null())))) {
        lv_availableBuffs = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0);
    }
    gd::GdVal lv_pickedBuffs = ([&]() { gd::GdVal _ca[] = {lv_availableBuffs, lv_numBuffs, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_pickRandomStacks_360, _ca, 3); })();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_pickedBuffs, gd::SYM_empty, nullptr, 0))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_events = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreEventBus), SYM_GEN_LoggingMode_1508), SYM_GEN_Delayed_2589)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_setLoggingMode_1497, _ca, 1); })();
    {
        gd::GdVal _t174 = gd::gd_iter_seq(gd_ctx.arena, lv_pickedBuffs);
        gd::GdArr* _t175 = (_t174.kind == gd::GdVal::Kind::Arr) ? _t174.arr : nullptr;
        uint32_t _len__t176 = _t175 ? _t175->len : 0u;
        for (uint32_t _t176 = 0; _t176 < _len__t176; ++_t176) {
            gd::GdVal lv_buff = _t175->data[_t176];
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_buff, gd::get_index(gd_ctx, lv_pickedBuffs, lv_buff), gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_useStacks_1203, _ca, 4); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, lv_events, gd::SYM_push_back, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_flushLoggingQueue_1500, nullptr, 0);
    return lv_events;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_removeRandomBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numBuffs = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_removedStacks = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0), lv_numBuffs, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_pickRandomStacks_360, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreEventBus), SYM_GEN_LoggingMode_1508), SYM_GEN_Delayed_2589)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_setLoggingMode_1497, _ca, 1); })();
    {
        gd::GdVal _t177 = gd::gd_iter_seq(gd_ctx.arena, lv_removedStacks);
        gd::GdArr* _t178 = (_t177.kind == gd::GdVal::Kind::Arr) ? _t177.arr : nullptr;
        uint32_t _len__t179 = _t178 ? _t178->len : 0u;
        for (uint32_t _t179 = 0; _t179 < _len__t179; ++_t179) {
            gd::GdVal lv_buff = _t178->data[_t179];
            (void)([&]() { gd::GdVal _ca[] = {lv_buff, gd::get_index(gd_ctx, lv_removedStacks, lv_buff), gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_loseStacks_1031, _ca, 4); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_flushLoggingQueue_1500, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_stealRandomBuff(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numBuffs = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_possibleBuffs = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_priorityBuff = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_possibleBuffs, gd::GdVal::null())))) {
        lv_possibleBuffs = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0);
    }
    gd::GdVal lv_removedStacks = ([&]() { gd::GdVal _ca[] = {lv_possibleBuffs, lv_numBuffs, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), lv_priorityBuff}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_pickRandomStacks_360, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreEventBus), SYM_GEN_LoggingMode_1508), SYM_GEN_Delayed_2589)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_setLoggingMode_1497, _ca, 1); })();
    {
        gd::GdVal _t180 = gd::gd_iter_seq(gd_ctx.arena, lv_removedStacks);
        gd::GdArr* _t181 = (_t180.kind == gd::GdVal::Kind::Arr) ? _t180.arr : nullptr;
        uint32_t _len__t182 = _t181 ? _t181->len : 0u;
        for (uint32_t _t182 = 0; _t182 < _len__t182; ++_t182) {
            gd::GdVal lv_buff = _t181->data[_t182];
            (void)([&]() { gd::GdVal _ca[] = {lv_buff, gd::get_index(gd_ctx, lv_removedStacks, lv_buff), gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_loseStacks_1031, _ca, 4); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), lv_buff, gd::get_index(gd_ctx, lv_removedStacks, lv_buff), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 4); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_flushLoggingQueue_1500, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_connectToCharacterBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_methodName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t183 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0));
        gd::GdArr* _t184 = (_t183.kind == gd::GdVal::Kind::Arr) ? _t183.arr : nullptr;
        uint32_t _len__t185 = _t184 ? _t184->len : 0u;
        for (uint32_t _t185 = 0; _t185 < _len__t185; ++_t185) {
            gd::GdVal lv_buff = _t184->data[_t185];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::get_prop(gd_ctx, gd::get_index(gd_ctx, gd::get_prop(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_buffs_1048), lv_buff), SYM_GEN_signalName_1013), lv_methodName}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_connectToCharacterDebuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_methodName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t186 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1362, nullptr, 0));
        gd::GdArr* _t187 = (_t186.kind == gd::GdVal::Kind::Arr) ? _t186.arr : nullptr;
        uint32_t _len__t188 = _t187 ? _t187->len : 0u;
        for (uint32_t _t188 = 0; _t188 < _len__t188; ++_t188) {
            gd::GdVal lv_debuff = _t187->data[_t188];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::get_prop(gd_ctx, gd::get_index(gd_ctx, gd::get_prop(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_buffs_1048), lv_debuff), SYM_GEN_signalName_1013), lv_methodName}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_connectToOpponentDebuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_methodName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t189 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1362, nullptr, 0));
        gd::GdArr* _t190 = (_t189.kind == gd::GdVal::Kind::Arr) ? _t189.arr : nullptr;
        uint32_t _len__t191 = _t190 ? _t190->len : 0u;
        for (uint32_t _t191 = 0; _t191 < _len__t191; ++_t191) {
            gd::GdVal lv_debuff = _t190->data[_t191];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), gd::get_prop(gd_ctx, gd::get_index(gd_ctx, gd::get_prop(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_buffs_1048), lv_debuff), SYM_GEN_signalName_1013), lv_methodName}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_connectToOpponentBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_methodName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t192 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0));
        gd::GdArr* _t193 = (_t192.kind == gd::GdVal::Kind::Arr) ? _t192.arr : nullptr;
        uint32_t _len__t194 = _t193 ? _t193->len : 0u;
        for (uint32_t _t194 = 0; _t194 < _len__t194; ++_t194) {
            gd::GdVal lv_buff = _t193->data[_t194];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), gd::get_prop(gd_ctx, gd::get_index(gd_ctx, gd::get_prop(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_buffs_1048), lv_buff), SYM_GEN_signalName_1013), lv_methodName}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getNextFreeLabelPosition(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "LABEL", 5u)), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_identifier_1577))), gd::gd_coerce_int(this->f_ownerType), ([&]() { gd::GdVal _ca[] = {(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::get_prop(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_playerId_1046))) : gd::GdVal::from_bool(false))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_trace_diag_1645, _ca, 4); })();
    {
        gd::GdVal _t195 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_buffLabelPositionTimestamps, gd::SYM_size, nullptr, 0));
        gd::GdArr* _t196 = (_t195.kind == gd::GdVal::Kind::Arr) ? _t195.arr : nullptr;
        uint32_t _len__t197 = _t196 ? _t196->len : 0u;
        for (uint32_t _t197 = 0; _t197 < _len__t197; ++_t197) {
            gd::GdVal lv_i = _t196->data[_t197];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1382), gd::get_index(gd_ctx, this->f_buffLabelPositionTimestamps, lv_i))))) {
                { gd::GdVal _t198 = this->f_buffLabelPositionTimestamps; gd::GdVal _t199 = lv_i; gd::set_index(gd_ctx, _t198, _t199, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1382), gd::GdVal::from_float(0.5))); }
                (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(10.0)), gd::GdVal::from_float(10.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
                (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(10.0)), gd::GdVal::from_float(10.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
                return gd::GdVal::null();
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(30.0)), gd::GdVal::from_float(30.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(30.0)), gd::GdVal::from_float(30.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_spawnLabel(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNextFreeLabelPosition_380, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {lv_type, gd::GdVal::from_obj(this), lv_amount}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_spawnLabelOnItem_1552, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_spawnLabel_other(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_type, gd::GdVal::from_obj(this), lv_amount}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_spawnLabelOnItem_1552, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_consume(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_playCombatAni = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    (void)([&]() { gd::GdVal _ca[] = {lv_damageRes, lv_playCombatAni, gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 3); })();
    this->f_consumed = gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_setState(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_newState = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_withNextEvent = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(false));
    lv_withNextEvent = gd::gd_coerce_bool(lv_withNextEvent);
    gd::GdVal lv_event = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_newState, lv_withNextEvent, lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemState_1356, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_newState}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_newState = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onTemporaryStacksTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_empowerEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_hasSockets(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, this->f_gems, gd::SYM_empty, nullptr, 0)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getNumSockets(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, this->f_gems, gd::SYM_size, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_initSockets(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_obj(this);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_hasGems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t200 = gd::gd_iter_seq(gd_ctx.arena, this->f_gems);
        gd::GdArr* _t201 = (_t200.kind == gd::GdVal::Kind::Arr) ? _t200.arr : nullptr;
        uint32_t _len__t202 = _t201 ? _t201->len : 0u;
        for (uint32_t _t202 = 0; _t202 < _len__t202; ++_t202) {
            gd::GdVal lv_gem = _t201->data[_t202];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_gem, gd::GdVal::null())))) {
                return gd::GdVal::from_bool(true);
            }
        }
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getGemsOfItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_items = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_out = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t203 = gd::gd_iter_seq(gd_ctx.arena, lv_items);
        gd::GdArr* _t204 = (_t203.kind == gd::GdVal::Kind::Arr) ? _t203.arr : nullptr;
        uint32_t _len__t205 = _t204 ? _t204->len : 0u;
        for (uint32_t _t205 = 0; _t205 < _len__t205; ++_t205) {
            gd::GdVal lv_item = _t204->data[_t205];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, lv_item, SYM_GEN_getGemsNoNull_499, nullptr, 0)}; return gd::call_method(gd_ctx, lv_out, gd::SYM_append_array, _ca, 1); })();
        }
    }
    return lv_out;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getPrice(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getPrice_394, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBaseSellPrice(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getSellPrice_396, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getSellPrice(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getSellPrice_396, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getSalePrice(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getSalePrice_397, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_setGem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_socketId = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_socketId = gd::gd_coerce_int(lv_socketId);
    gd::GdVal lv_gem = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_socketId, gd::call_method(gd_ctx, this->f_gems, gd::SYM_size, nullptr, 0))))) {
        (void)gd::GdVal::null();
    }
    else {
        gd::set_prop(gd_ctx, lv_gem, SYM_GEN_ownerType_51, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_Socket_2590));
        { gd::GdVal _t206 = this->f_gems; gd::GdVal _t207 = lv_socketId; gd::set_index(gd_ctx, _t206, _t207, lv_gem); }
        gd::set_prop(gd_ctx, lv_gem, SYM_GEN_socket_962, gd::GdVal::from_obj(this));
        (void)gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_gem, SYM_GEN_occupiedCells_54), gd::SYM_clear, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_pushGemsToStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_pushItemsInsideToStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_returnToSocket(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_movebackDur = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getOwnOrPlayerInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_placed)) {
        return this->f_inventory;
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1284), gd::GdVal::null())))) {
        return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1284), SYM_GEN_inventory_5);
    }
    return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_emptyGrid_1425, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getCellsForGlobalPositions(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_points = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return lv_points;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getGlobalPointsForCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_cells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return lv_cells;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getGlobalPointsForCells_noRotate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_cells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return lv_cells;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getCollisionCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_collisionCells;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getExtensionCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_extensionCells;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getCollisionPoints(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_collisionCells;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getExtensionPoints(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_extensionCells;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAffectedCells_tilemap(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581));
    return ([&]() { gd::GdVal _ca[] = {lv_color, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, this->f_affectedTileCells, gd::SYM_get, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAffectedCellsAfterRotate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rotatedCells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_color, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581))))) {
        return ([&]() { gd::GdVal _ca[] = {lv_rotatedCells}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCellsAfterRotate_primary_412, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_color, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Secondary_2583))))) {
        return ([&]() { gd::GdVal _ca[] = {lv_rotatedCells}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCellsAfterRotate_secondary_413, _ca, 1); })();
    }
    else {
        return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAffectedCellsAfterRotate_primary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__rotatedCells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "getAffectedCellsAfterRotate_primary", 35u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_505, _ca, 1); })())) {
        return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "getAffectedCellsAfterRotate_primary", 35u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv__rotatedCells}))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_506, _ca, 2); })();
    }
    return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAffectedCellsAfterRotate_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__rotatedCells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "getAffectedCellsAfterRotate_secondary", 37u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_505, _ca, 1); })())) {
        return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "getAffectedCellsAfterRotate_secondary", 37u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv__rotatedCells}))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_506, _ca, 2); })();
    }
    return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAffectedCells_noRotate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581));
    return ([&]() { gd::GdVal _ca[] = {this->f_collisionCells, lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCellsAfterRotate_411, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAffectedPoints(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581));
    return gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCells_tilemap_410, _ca, 1); })(), ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCells_noRotate_414, _ca, 1); })());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAffectedCellsInInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581));
    return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedPoints_415, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getOwnOrPlayerInventory_402, nullptr, 0), SYM_GEN_getCellsForGlobalPositions_403, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAffectedCellsInInventory_cached(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_color, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, this->f_affectedCellsCache, gd::SYM_get, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_cacheAffectedCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t208 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), gd::SYM_values, nullptr, 0));
        gd::GdArr* _t209 = (_t208.kind == gd::GdVal::Kind::Arr) ? _t208.arr : nullptr;
        uint32_t _len__t210 = _t209 ? _t209->len : 0u;
        for (uint32_t _t210 = 0; _t210 < _len__t210; ++_t210) {
            gd::GdVal lv_color = _t209->data[_t210];
            { gd::GdVal _t211 = this->f_affectedCellsCache; gd::GdVal _t212 = lv_color; gd::set_index(gd_ctx, _t211, _t212, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCellsInInventory_416, _ca, 1); })()); }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_cleanCachedAffectedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_affectedCellsCache, gd::SYM_clear, nullptr, 0);
    {
        gd::GdVal _t213 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), gd::SYM_values, nullptr, 0));
        gd::GdArr* _t214 = (_t213.kind == gd::GdVal::Kind::Arr) ? _t213.arr : nullptr;
        uint32_t _len__t215 = _t214 ? _t214->len : 0u;
        for (uint32_t _t215 = 0; _t215 < _len__t215; ++_t215) {
            gd::GdVal lv_color = _t214->data[_t215];
            (void)gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_currentAffectedItems, lv_color), gd::SYM_clear, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanCachedAffectedItems_419, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onAddToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAffectedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581));
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, this->f_cachedAffectedItems, gd::SYM_empty, nullptr, 0))))) {
        return gd::get_index(gd_ctx, this->f_cachedAffectedItems, lv_color);
    }
    gd::GdVal lv_items = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t216 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInAffectedCells_cached_425, _ca, 1); })());
        gd::GdArr* _t217 = (_t216.kind == gd::GdVal::Kind::Arr) ? _t216.arr : nullptr;
        uint32_t _len__t218 = _t217 ? _t217->len : 0u;
        for (uint32_t _t218 = 0; _t218 < _len__t218; ++_t218) {
            gd::GdVal lv_item = _t217->data[_t218];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item, lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_color_292, _ca, 2); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, lv_items, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    return lv_items;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAffectedItems_nocache(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581));
    gd::GdVal lv_items = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t219 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInAffectedCells_424, _ca, 1); })());
        gd::GdArr* _t220 = (_t219.kind == gd::GdVal::Kind::Arr) ? _t219.arr : nullptr;
        uint32_t _len__t221 = _t220 ? _t220->len : 0u;
        for (uint32_t _t221 = 0; _t221 < _len__t221; ++_t221) {
            gd::GdVal lv_item = _t220->data[_t221];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item, lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_color_292, _ca, 2); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, lv_items, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    return lv_items;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getItemsInAffectedCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581));
    return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCellsInInventory_416, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getOwnOrPlayerInventory_402, nullptr, 0), SYM_GEN_getItemsInCells_1517, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getItemsInAffectedCells_cached(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581));
    return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCellsInInventory_cached_417, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getOwnOrPlayerInventory_402, nullptr, 0), SYM_GEN_getItemsInCells_1517, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_countItemsInAffectedCells_cached(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581));
    return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCellsInInventory_cached_417, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getOwnOrPlayerInventory_402, nullptr, 0), SYM_GEN_countItemsInCells_1518, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isItemAffected(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581));
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isBag_85, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item, lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_color_292, _ca, 2); })()))))))) {
        return gd::GdVal::from_bool(false);
    }
    gd::GdVal lv_affectedTiles = ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCellsInInventory_cached_417, _ca, 1); })();
    {
        gd::GdVal _t222 = gd::gd_iter_seq(gd_ctx.arena, gd::get_prop(gd_ctx, lv_item, SYM_GEN_occupiedCells_54));
        gd::GdArr* _t223 = (_t222.kind == gd::GdVal::Kind::Arr) ? _t222.arr : nullptr;
        uint32_t _len__t224 = _t223 ? _t223->len : 0u;
        for (uint32_t _t224 = 0; _t224 < _len__t224; ++_t224) {
            gd::GdVal lv_cell = _t223->data[_t224];
            if (gd::gd_truth(gd::gd_in(lv_cell, lv_affectedTiles))) {
                return gd::GdVal::from_bool(true);
            }
        }
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getNumEmptyAffectedCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581));
    return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCellsInInventory_416, _ca, 1); })()}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getEmptyCellsInCells_1515, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getNumAffectedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581));
    return gd::call_method(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, _ca, 1); })(), gd::SYM_size, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getFirstAffectedItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581));
    gd::GdVal lv__affectedItems = ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv__affectedItems, gd::SYM_empty, nullptr, 0))))) {
        return gd::get_index(gd_ctx, lv__affectedItems, gd::GdVal::from_int(0LL));
    }
    return gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getNumAffected_type(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581));
    gd::GdVal lv_num = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t225 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, _ca, 1); })());
        gd::GdArr* _t226 = (_t225.kind == gd::GdVal::Kind::Arr) ? _t225.arr : nullptr;
        uint32_t _len__t227 = _t226 ? _t226->len : 0u;
        for (uint32_t _t227 = 0; _t227 < _len__t227; ++_t227) {
            gd::GdVal lv_item = _t226->data[_t227];
            lv_num = gd::gd_add(gd_ctx, lv_num, ([&]() { gd::GdVal _ca[] = {lv_type}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_getTypeMultiplicity_82, _ca, 1); })());
        }
    }
    return lv_num;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getNumDistinctAffectedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581));
    gd::GdVal lv_distinctAffectedDescriptors = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t228 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, _ca, 1); })());
        gd::GdArr* _t229 = (_t228.kind == gd::GdVal::Kind::Arr) ? _t228.arr : nullptr;
        uint32_t _len__t230 = _t229 ? _t229->len : 0u;
        for (uint32_t _t230 = 0; _t230 < _len__t230; ++_t230) {
            gd::GdVal lv_item = _t229->data[_t230];
            { gd::GdVal _t231 = lv_distinctAffectedDescriptors; gd::GdVal _t232 = gd::get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2); gd::set_index(gd_ctx, _t231, _t232, gd::GdVal::from_bool(true)); }
        }
    }
    return gd::call_method(gd_ctx, lv_distinctAffectedDescriptors, gd::SYM_size, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getNumAffectedCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581));
    if (gd::gd_truth(gd::gd_in(lv_color, this->f_affectedCellsCache))) {
        return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_affectedCellsCache, lv_color), gd::SYM_size, nullptr, 0);
    }
    else {
        return gd::gd_add(gd_ctx, gd::call_method(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCells_tilemap_410, _ca, 1); })(), gd::SYM_size, nullptr, 0), gd::call_method(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCells_noRotate_414, _ca, 1); })(), gd::SYM_size, nullptr, 0));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_activateExtendedAffectedCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t233 = gd::gd_iter_seq(gd_ctx.arena, this->f_affectedExtensionCells);
        gd::GdArr* _t234 = (_t233.kind == gd::GdVal::Kind::Arr) ? _t233.arr : nullptr;
        uint32_t _len__t235 = _t234 ? _t234->len : 0u;
        for (uint32_t _t235 = 0; _t235 < _len__t235; ++_t235) {
            gd::GdVal lv_cell = _t234->data[_t235];
            (void)([&]() { gd::GdVal _ca[] = {this->f_affectedTileCells, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581), lv_cell}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_dictAppend_1697, _ca, 3); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cacheAffectedCells_418, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_deactivateExtendedAffectedCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t236 = gd::gd_iter_seq(gd_ctx.arena, this->f_affectedExtensionCells);
        gd::GdArr* _t237 = (_t236.kind == gd::GdVal::Kind::Arr) ? _t236.arr : nullptr;
        uint32_t _len__t238 = _t237 ? _t237->len : 0u;
        for (uint32_t _t238 = 0; _t238 < _len__t238; ++_t238) {
            gd::GdVal lv_cell = _t237->data[_t238];
            gd::GdVal lv_arr = ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, this->f_affectedTileCells, gd::SYM_get, _ca, 2); })();
            if (gd::gd_truth(gd::gd_in(lv_cell, lv_arr))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_cell}; return gd::call_method(gd_ctx, lv_arr, gd::SYM_erase, _ca, 1); })();
            }
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cacheAffectedCells_418, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canAffectDraggedItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item, lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_color_292, _ca, 2); })())) {
        gd::GdVal lv_affectedCells = ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedCellsInInventory_cached_417, _ca, 1); })();
        {
            gd::GdVal _t239 = gd::gd_iter_seq(gd_ctx.arena, lv_affectedCells);
            gd::GdArr* _t240 = (_t239.kind == gd::GdVal::Kind::Arr) ? _t239.arr : nullptr;
            uint32_t _len__t241 = _t240 ? _t240->len : 0u;
            for (uint32_t _t241 = 0; _t241 < _len__t241; ++_t241) {
                gd::GdVal lv_cell = _t240->data[_t241];
                if (gd::gd_truth(gd::get_prop(gd_ctx, lv_item, SYM_GEN_dragged_53))) {
                    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_cell}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_isHovered_714, _ca, 1); })())) {
                        return gd::GdVal::from_bool(true);
                    }
                }
                else {
                    if (gd::gd_truth(gd::gd_in(lv_cell, gd::get_prop(gd_ctx, lv_item, SYM_GEN_occupiedCells_54)))) {
                        return gd::GdVal::from_bool(true);
                    }
                }
            }
        }
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onAffectedItemAdded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onAffectedItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onItemAdded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_newItemIsAffected = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t242 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), gd::SYM_values, nullptr, 0));
        gd::GdArr* _t243 = (_t242.kind == gd::GdVal::Kind::Arr) ? _t242.arr : nullptr;
        uint32_t _len__t244 = _t243 ? _t243->len : 0u;
        for (uint32_t _t244 = 0; _t244 < _len__t244; ++_t244) {
            gd::GdVal lv_color = _t243->data[_t244];
            { gd::GdVal _t245 = lv_newItemIsAffected; gd::GdVal _t246 = lv_color; gd::set_index(gd_ctx, _t245, _t246, (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_item, gd::get_index(gd_ctx, this->f_currentAffectedItems, lv_color))))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item, lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isItemAffected_427, _ca, 2); })())) : gd::GdVal::from_bool(false))); }
        }
    }
    {
        gd::GdVal _t247 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), gd::SYM_values, nullptr, 0));
        gd::GdArr* _t248 = (_t247.kind == gd::GdVal::Kind::Arr) ? _t247.arr : nullptr;
        uint32_t _len__t249 = _t248 ? _t248->len : 0u;
        for (uint32_t _t249 = 0; _t249 < _len__t249; ++_t249) {
            gd::GdVal lv_color = _t248->data[_t249];
            if (gd::gd_truth(gd::get_index(gd_ctx, lv_newItemIsAffected, lv_color))) {
                { gd::GdVal _t250 = gd::get_index(gd_ctx, this->f_currentAffectedItems, lv_color); gd::GdVal _t251 = lv_item; gd::set_index(gd_ctx, _t250, _t251, gd::GdVal::from_bool(true)); }
                (void)([&]() { gd::GdVal _ca[] = {lv_item, lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAffectedItemAdded_437, _ca, 2); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t252 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), gd::SYM_values, nullptr, 0));
        gd::GdArr* _t253 = (_t252.kind == gd::GdVal::Kind::Arr) ? _t252.arr : nullptr;
        uint32_t _len__t254 = _t253 ? _t253->len : 0u;
        for (uint32_t _t254 = 0; _t254 < _len__t254; ++_t254) {
            gd::GdVal lv_color = _t253->data[_t254];
            (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_currentAffectedItems, lv_color), gd::SYM_erase, _ca, 1); })();
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item, lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffectDraggedItem_436, _ca, 2); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item, lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAffectedItemRemoved_438, _ca, 2); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getNumOccupiedCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, this->f_collisionCells, gd::SYM_size, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getNumBagCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, this->f_extensionCells, gd::SYM_size, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getNumCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumOccupiedCells_441, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumBagCells_442, nullptr, 0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getSizeInCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_topLeft = gd::GdVal::from_vec2((gd::GdVal::from_int(100LL)).as_float(), (gd::GdVal::from_int(100LL)).as_float());
    gd::GdVal lv_bottomRight = gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(100LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(100LL))).as_float());
    gd::GdVal lv_cells = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCollisionCells_406, nullptr, 0);
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_cells, gd::SYM_empty, nullptr, 0))) {
        return gd::GdVal::from_vec2(0.0, 0.0);
    }
    {
        gd::GdVal _t255 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
        gd::GdArr* _t256 = (_t255.kind == gd::GdVal::Kind::Arr) ? _t255.arr : nullptr;
        uint32_t _len__t257 = _t256 ? _t256->len : 0u;
        for (uint32_t _t257 = 0; _t257 < _len__t257; ++_t257) {
            gd::GdVal lv_cell = _t256->data[_t257];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::get_prop(gd_ctx, lv_cell, gd::SYM_x), gd::get_prop(gd_ctx, lv_topLeft, gd::SYM_x))))) {
                gd::set_prop(gd_ctx, lv_topLeft, gd::SYM_x, gd::get_prop(gd_ctx, lv_cell, gd::SYM_x));
            }
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::get_prop(gd_ctx, lv_cell, gd::SYM_y), gd::get_prop(gd_ctx, lv_topLeft, gd::SYM_y))))) {
                gd::set_prop(gd_ctx, lv_topLeft, gd::SYM_y, gd::get_prop(gd_ctx, lv_cell, gd::SYM_y));
            }
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, lv_cell, gd::SYM_x), gd::get_prop(gd_ctx, lv_bottomRight, gd::SYM_x))))) {
                gd::set_prop(gd_ctx, lv_bottomRight, gd::SYM_x, gd::get_prop(gd_ctx, lv_cell, gd::SYM_x));
            }
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, lv_cell, gd::SYM_y), gd::get_prop(gd_ctx, lv_bottomRight, gd::SYM_y))))) {
                gd::set_prop(gd_ctx, lv_bottomRight, gd::SYM_y, gd::get_prop(gd_ctx, lv_cell, gd::SYM_y));
            }
        }
    }
    return gd::gd_add(gd_ctx, gd::gd_sub(lv_bottomRight, lv_topLeft), gd::GdVal::from_vec2((gd::GdVal::from_int(1LL)).as_float(), (gd::GdVal::from_int(1LL)).as_float()));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getTopLeftCell(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_topLeft = gd::GdVal::from_vec2((gd::GdVal::from_float(std::numeric_limits<double>::infinity())).as_float(), (gd::GdVal::from_float(std::numeric_limits<double>::infinity())).as_float());
    {
        gd::GdVal _t258 = gd::gd_iter_seq(gd_ctx.arena, this->f_occupiedCells);
        gd::GdArr* _t259 = (_t258.kind == gd::GdVal::Kind::Arr) ? _t258.arr : nullptr;
        uint32_t _len__t260 = _t259 ? _t259->len : 0u;
        for (uint32_t _t260 = 0; _t260 < _len__t260; ++_t260) {
            gd::GdVal lv_cell = _t259->data[_t260];
            gd::set_prop(gd_ctx, lv_topLeft, gd::SYM_x, gd::gd_min(gd::get_prop(gd_ctx, lv_cell, gd::SYM_x), gd::get_prop(gd_ctx, lv_topLeft, gd::SYM_x)));
            gd::set_prop(gd_ctx, lv_topLeft, gd::SYM_y, gd::gd_min(gd::get_prop(gd_ctx, lv_cell, gd::SYM_y), gd::get_prop(gd_ctx, lv_topLeft, gd::SYM_y)));
        }
    }
    return lv_topLeft;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getNormalizedCollisionCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_cells = gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isBag_85, nullptr, 0))) {
        lv_cells = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getExtensionCells_407, nullptr, 0), gd::SYM_duplicate, nullptr, 0);
    }
    else {
        lv_cells = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCollisionCells_406, nullptr, 0), gd::SYM_duplicate, nullptr, 0);
    }
    gd::GdVal lv_minimum = gd::GdVal::from_vec2((gd::GdVal::from_int(100LL)).as_float(), (gd::GdVal::from_int(100LL)).as_float());
    {
        gd::GdVal _t261 = gd::gd_iter_seq(gd_ctx.arena, lv_cells);
        gd::GdArr* _t262 = (_t261.kind == gd::GdVal::Kind::Arr) ? _t261.arr : nullptr;
        uint32_t _len__t263 = _t262 ? _t262->len : 0u;
        for (uint32_t _t263 = 0; _t263 < _len__t263; ++_t263) {
            gd::GdVal lv_cell = _t262->data[_t263];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(gd::get_prop(gd_ctx, lv_cell, gd::SYM_y), gd::get_prop(gd_ctx, lv_minimum, gd::SYM_y))))) {
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::get_prop(gd_ctx, lv_cell, gd::SYM_y), gd::get_prop(gd_ctx, lv_minimum, gd::SYM_y))))) {
                    gd::set_prop(gd_ctx, lv_minimum, gd::SYM_x, gd::get_prop(gd_ctx, lv_cell, gd::SYM_x));
                }
                else {
                    gd::set_prop(gd_ctx, lv_minimum, gd::SYM_x, gd::gd_min(gd::get_prop(gd_ctx, lv_cell, gd::SYM_x), gd::get_prop(gd_ctx, lv_minimum, gd::SYM_x)));
                }
                gd::set_prop(gd_ctx, lv_minimum, gd::SYM_y, gd::get_prop(gd_ctx, lv_cell, gd::SYM_y));
            }
        }
    }
    {
        gd::GdVal _t264 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, lv_cells, gd::SYM_size, nullptr, 0)}; return gd::gd_range(gd_ctx.arena, _ca, 1); })());
        gd::GdArr* _t265 = (_t264.kind == gd::GdVal::Kind::Arr) ? _t264.arr : nullptr;
        uint32_t _len__t266 = _t265 ? _t265->len : 0u;
        for (uint32_t _t266 = 0; _t266 < _len__t266; ++_t266) {
            gd::GdVal lv_i = _t265->data[_t266];
            { gd::GdVal _t267 = lv_cells; gd::GdVal _t268 = lv_i; gd::set_index(gd_ctx, _t267, _t268, gd::gd_sub(gd::get_index(gd_ctx, lv_cells, lv_i), lv_minimum)); }
        }
    }
    return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_cells, gd::GdVal::from_vec2(0.0, 0.0)}));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_canCombine(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_placed;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_prepareReplacement(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_replacementPending = gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_finishReplacement(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_replacementPending = gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_placeGeneratedItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_candidateCells = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_moveTo(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_fromPos = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_newPos = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_duration = (_argc > 2) ? _args[2] : (gd::GdVal::from_float(0.2));
    gd::GdVal lv_transitionType = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_resetZ(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_resetZ_452, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onGateItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_insertCounter(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_paramName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 2) ? _args[2] : gd::GdVal::null();
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_queue_free(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_shift(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_direction = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onBought(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onSold(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_reactToItemTypeChange(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "reactToItemTypeChange", 21u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_505, _ca, 1); })())) {
        return ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "reactToItemTypeChange", 21u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_item}))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_506, _ca, 2); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_truth_1360, _ca, 1); })();
    }
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_onItemTypeChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_canAddAgain = ([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_reactToItemTypeChange_459, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_canAddAgain)))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_addedToAffected = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t269 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), gd::SYM_values, nullptr, 0));
        gd::GdArr* _t270 = (_t269.kind == gd::GdVal::Kind::Arr) ? _t269.arr : nullptr;
        uint32_t _len__t271 = _t270 ? _t270->len : 0u;
        for (uint32_t _t271 = 0; _t271 < _len__t271; ++_t271) {
            gd::GdVal lv_color = _t270->data[_t271];
            { gd::GdVal _t272 = lv_addedToAffected; gd::GdVal _t273 = lv_color; gd::set_index(gd_ctx, _t272, _t273, gd::GdVal::from_bool(false)); }
            if (gd::gd_truth(gd::gd_in(lv_item, gd::get_index(gd_ctx, this->f_currentAffectedItems, lv_color)))) {
                if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item, lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_color_292, _ca, 2); })())))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_currentAffectedItems, lv_color), gd::SYM_erase, _ca, 1); })();
                    (void)([&]() { gd::GdVal _ca[] = {lv_item, lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAffectedItemRemoved_438, _ca, 2); })();
                }
            }
            else if (gd::gd_truth(gd::gd_in(lv_item, ([&]() { gd::GdVal _ca[] = {lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, _ca, 1); })()))) {
                { gd::GdVal _t274 = gd::get_index(gd_ctx, this->f_currentAffectedItems, lv_color); gd::GdVal _t275 = lv_item; gd::set_index(gd_ctx, _t274, _t275, gd::GdVal::from_bool(true)); }
                (void)([&]() { gd::GdVal _ca[] = {lv_item, lv_color}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAffectedItemAdded_437, _ca, 2); })();
                { gd::GdVal _t276 = lv_addedToAffected; gd::GdVal _t277 = lv_color; gd::set_index(gd_ctx, _t276, _t277, gd::GdVal::from_bool(true)); }
            }
        }
    }
    if (gd::gd_truth(gd::get_prop(gd_ctx, lv_item, SYM_GEN_placedByPlayer_52))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_addedToAffected}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_playAffectedPlacedAnimation_663, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getRelatedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_gatedItems_1595);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_countAllPlacedOfType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_count = gd::GdVal::from_int(0LL);
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isOwnedByOpponent_253, nullptr, 0))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_opponent_77), gd::GdVal::null())))) {
            return gd::GdVal::from_int(0LL);
        }
        {
            gd::GdVal _t278 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_opponent_77), SYM_GEN_inventory_5), SYM_GEN_getItemsAndGems_1513, nullptr, 0));
            gd::GdArr* _t279 = (_t278.kind == gd::GdVal::Kind::Arr) ? _t278.arr : nullptr;
            uint32_t _len__t280 = _t279 ? _t279->len : 0u;
            for (uint32_t _t280 = 0; _t280 < _len__t280; ++_t280) {
                gd::GdVal lv_item = _t279->data[_t280];
                if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), lv_descr)))) : gd::GdVal::from_bool(false)))) {
                    lv_count = gd::gd_add(gd_ctx, lv_count, gd::GdVal::from_int(1LL));
                }
            }
        }
        return lv_count;
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1284), gd::GdVal::null())))) {
        {
            gd::GdVal _t281 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1284), SYM_GEN_inventory_5), SYM_GEN_getItemsAndGems_1513, nullptr, 0));
            gd::GdArr* _t282 = (_t281.kind == gd::GdVal::Kind::Arr) ? _t281.arr : nullptr;
            uint32_t _len__t283 = _t282 ? _t282->len : 0u;
            for (uint32_t _t283 = 0; _t283 < _len__t283; ++_t283) {
                gd::GdVal lv_item = _t282->data[_t283];
                if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), lv_descr))))))) {
                    continue;
                }
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_item, SYM_GEN_ownerType_51), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_Socket_2590))))) {
                    lv_count = gd::gd_add(gd_ctx, lv_count, gd::GdVal::from_int(1LL));
                }
                else if (gd::gd_truth((gd::gd_truth(gd::get_prop(gd_ctx, lv_item, SYM_GEN_placed_6)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_item, SYM_GEN_ownerType_51), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_PlayerInventory_2555))))) : gd::GdVal::from_bool(false)))) {
                    lv_count = gd::gd_add(gd_ctx, lv_count, gd::GdVal::from_int(1LL));
                }
            }
        }
    }
    return lv_count;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getTouchedBagsCounted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isBag_85, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_placed))))))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_touchedBags = ([&]() { gd::GdVal _ca[] = {this->f_occupiedCells}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getBagsInCells_1519, _ca, 1); })();
    gd::GdVal lv_bagCounter = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t284 = gd::gd_iter_seq(gd_ctx.arena, lv_touchedBags);
        gd::GdArr* _t285 = (_t284.kind == gd::GdVal::Kind::Arr) ? _t284.arr : nullptr;
        uint32_t _len__t286 = _t285 ? _t285->len : 0u;
        for (uint32_t _t286 = 0; _t286 < _len__t286; ++_t286) {
            gd::GdVal lv_bag = _t285->data[_t286];
            gd::GdVal lv_found = gd::GdVal::from_bool(false);
            {
                gd::GdVal _t287 = gd::gd_iter_seq(gd_ctx.arena, lv_bagCounter);
                gd::GdArr* _t288 = (_t287.kind == gd::GdVal::Kind::Arr) ? _t287.arr : nullptr;
                uint32_t _len__t289 = _t288 ? _t288->len : 0u;
                for (uint32_t _t289 = 0; _t289 < _len__t289; ++_t289) {
                    gd::GdVal lv_countedBag = _t288->data[_t289];
                    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_countedBag, SYM_GEN_descriptor_2), gd::get_prop(gd_ctx, lv_bag, SYM_GEN_descriptor_2))))) {
                        { gd::GdVal _t290 = lv_bagCounter; gd::GdVal _t291 = lv_countedBag; gd::set_index(gd_ctx, _t290, _t291, gd::gd_add(gd_ctx, gd::get_index(gd_ctx, _t290, _t291), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, lv_bag, SYM_GEN_getBagMultiplicity_932, _ca, 1); })())); }
                        lv_found = gd::GdVal::from_bool(true);
                        break;
                    }
                }
            }
            if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_found)))) {
                { gd::GdVal _t292 = lv_bagCounter; gd::GdVal _t293 = lv_bag; gd::set_index(gd_ctx, _t292, _t293, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, lv_bag, SYM_GEN_getBagMultiplicity_932, _ca, 1); })()); }
            }
        }
    }
    return lv_bagCounter;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getHeightRange(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2((gd::get_prop(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getTopLeftCell_445, nullptr, 0), gd::SYM_y)).as_float(), (gd::gd_sub(gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getTopLeftCell_445, nullptr, 0), gd::SYM_y), gd::get_prop(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getSizeInCells_444, nullptr, 0), gd::SYM_y)), gd::GdVal::from_int(1LL))).as_float());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_ready_deferred(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "ready_deferred", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__hasBehaviorMethod_505, _ca, 1); })())) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "ready_deferred", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__behavior_call_506, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_rotationFromFaceDirection(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__faceDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::gd_mul(gd::gd_mul(lv__faceDirection, gd::GdVal::from_float(3.14159265358979323846)), gd::GdVal::from_float(0.5));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getFaceDirection(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_mod(gd_ctx, gd::gd_add(gd_ctx, gd::gd_coerce_int(gd::gd_add(gd_ctx, gd::gd_div(gd_ctx, gd::gd_mul(gd::GdVal::from_int(2LL), this->f_rotation), gd::GdVal::from_float(3.14159265358979323846)), gd::gd_mul(gd::GdVal::from_float(2.25), gd::GdVal::from_float(3.14159265358979323846)))), gd::GdVal::from_int(5LL)), gd::GdVal::from_int(4LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getGlobalFaceDirection(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getFaceDirection_467, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_setFaceDirectionInstant(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__faceDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_faceDirection = gd::gd_coerce_int(lv__faceDirection);
    this->f_rotation = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {this->f_faceDirection}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rotationFromFaceDirection_466, _ca, 1); })());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_setRotation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__rotation = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_rotation = gd::gd_coerce_float(lv__rotation);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_changeAllItemsCritRate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t294 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1512, nullptr, 0));
        gd::GdArr* _t295 = (_t294.kind == gd::GdVal::Kind::Arr) ? _t294.arr : nullptr;
        uint32_t _len__t296 = _t295 ? _t295->len : 0u;
        for (uint32_t _t296 = 0; _t296 < _len__t296; ++_t296) {
            gd::GdVal lv_item = _t295->data[_t296];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_92, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeCritChancePercent_183, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_miniActivate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), (gd::gd_truth(this->f_consumed) ? (gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "MiniActivate_consumed", 21u))) : (gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "MiniActivate", 12u)))), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_playActivationAnimation_778, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_previewCellCollision(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_previewCellCollision_473, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_previewCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_previewCells_474, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_previewCanAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_previewCanAffect_475, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_rotateRight(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_faceDirection = gd::gd_coerce_int(gd::gd_mod(gd_ctx, gd::gd_add(gd_ctx, this->f_faceDirection, gd::GdVal::from_int(1LL)), gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_size, nullptr, 0)));
    (void)([&]() { gd::GdVal _ca[] = {this->f_faceDirection}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setFaceDirectionInstant_469, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_onItemRotated_1539, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_rotateLeft(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_faceDirection = gd::gd_coerce_int(gd::gd_mod(gd_ctx, gd::gd_add(gd_ctx, gd::gd_sub(this->f_faceDirection, gd::GdVal::from_int(1LL)), gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_size, nullptr, 0)), gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_size, nullptr, 0)));
    (void)([&]() { gd::GdVal _ca[] = {this->f_faceDirection}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setFaceDirectionInstant_469, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_onItemRotated_1539, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_rotateTo(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_targetRotation = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_duration = (_argc > 1) ? _args[1] : (gd::GdVal::from_float(0.15));
    this->f_faceDirection = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGlobalFaceDirection_468, nullptr, 0));
    this->f_rotation = gd::gd_coerce_float(lv_targetRotation);
    this->f_faceDirection = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGlobalFaceDirection_468, nullptr, 0));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_onItemRotated_1539, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_rotateToDeferred(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_targetRotation = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_duration = (_argc > 1) ? _args[1] : (gd::GdVal::from_float(0.15));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "rotateTo", 8u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_targetRotation, lv_duration}))}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_defer_1422, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_setFaceDirection(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__faceDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::gd_mul(lv__faceDirection, gd::GdVal::from_float(3.14159265358979323846)), gd::GdVal::from_float(0.5))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rotateTo_478, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_correctInsideItemFacedirection(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBagEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_number = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getGemData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_setGemData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_gemData = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_reconstructCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_encodedCd = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_timeSinceEntry = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_findBondsWithAffectedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_rotateProgress(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_progress = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_progress = gd::gd_coerce_float(lv_progress);
    {
        gd::GdVal _t297 = this->f_faceDirection;
        if (gd::gd_eq(_t297, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP))) {
            lv_progress = gd::gd_coerce_float(gd::gd_sub(gd::GdVal::from_float(1.0), lv_progress));
        }
        else if (gd::gd_eq(_t297, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_RIGHT))) {
            lv_progress = gd::gd_coerce_float(gd::gd_sub(gd::GdVal::from_float(1.0), lv_progress));
        }
        else if (gd::gd_eq(_t297, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_LEFT))) {
            lv_progress = gd::gd_coerce_float(gd::gd_neg(lv_progress));
        }
        else if (gd::gd_eq(_t297, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN))) {
            lv_progress = gd::gd_coerce_float(gd::gd_neg(lv_progress));
        }
    }
    return lv_progress;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_cacheCollisionCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isBaseItemForShopItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_activateFromEvent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Activate", 8u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_playActivationAnimation_778, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getNeighborItemsAndGems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_neighbors = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getAdjacentItems_1522, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemsNoNull_499, nullptr, 0)}; return gd::call_method(gd_ctx, lv_neighbors, gd::SYM_append_array, _ca, 1); })();
    {
        gd::GdVal _t298 = gd::gd_iter_seq(gd_ctx.arena, lv_neighbors);
        gd::GdArr* _t299 = (_t298.kind == gd::GdVal::Kind::Arr) ? _t298.arr : nullptr;
        uint32_t _len__t300 = _t299 ? _t299->len : 0u;
        for (uint32_t _t300 = 0; _t300 < _len__t300; ++_t300) {
            gd::GdVal lv_neighbor = _t299->data[_t300];
            gd::GdVal lv_neighborGems = gd::call_method(gd_ctx, lv_neighbor, SYM_GEN_getGemsNoNull_499, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {lv_neighborGems}; return gd::call_method(gd_ctx, lv_neighbors, gd::SYM_append_array, _ca, 1); })();
        }
    }
    return lv_neighbors;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getTouchedBags(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isBag_85, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_placed))))))) {
        return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {this->f_occupiedCells}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getBagsInCells_1519, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getBusyNeighbors(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_busyNeighbors = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t301 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNeighborItemsAndGems_491, nullptr, 0));
        gd::GdArr* _t302 = (_t301.kind == gd::GdVal::Kind::Arr) ? _t301.arr : nullptr;
        uint32_t _len__t303 = _t302 ? _t302->len : 0u;
        for (uint32_t _t303 = 0; _t303 < _len__t303; ++_t303) {
            gd::GdVal lv_neighbor = _t302->data[_t303];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_neighbor, SYM_GEN_isBusy_261, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_neighbor}; return gd::call_method(gd_ctx, lv_busyNeighbors, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    {
        gd::GdVal _t304 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getTouchedBags_492, nullptr, 0));
        gd::GdArr* _t305 = (_t304.kind == gd::GdVal::Kind::Arr) ? _t304.arr : nullptr;
        uint32_t _len__t306 = _t305 ? _t305->len : 0u;
        for (uint32_t _t306 = 0; _t306 < _len__t306; ++_t306) {
            gd::GdVal lv_bag = _t305->data[_t306];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_bag, SYM_GEN_isBusy_261, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_bag}; return gd::call_method(gd_ctx, lv_busyNeighbors, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    return lv_busyNeighbors;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getCraftableNeighbors(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_craftableNeighbors = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t307 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNeighborItemsAndGems_491, nullptr, 0));
        gd::GdArr* _t308 = (_t307.kind == gd::GdVal::Kind::Arr) ? _t307.arr : nullptr;
        uint32_t _len__t309 = _t308 ? _t308->len : 0u;
        for (uint32_t _t309 = 0; _t309 < _len__t309; ++_t309) {
            gd::GdVal lv_neighbor = _t308->data[_t309];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_neighbor, SYM_GEN_isAvailableForCrafting_495, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_neighbor}; return gd::call_method(gd_ctx, lv_craftableNeighbors, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    {
        gd::GdVal _t310 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getTouchedBags_492, nullptr, 0));
        gd::GdArr* _t311 = (_t310.kind == gd::GdVal::Kind::Arr) ? _t310.arr : nullptr;
        uint32_t _len__t312 = _t311 ? _t311->len : 0u;
        for (uint32_t _t312 = 0; _t312 < _len__t312; ++_t312) {
            gd::GdVal lv_bag = _t311->data[_t312];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_bag, SYM_GEN_isAvailableForCrafting_495, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_bag}; return gd::call_method(gd_ctx, lv_craftableNeighbors, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    return lv_craftableNeighbors;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_isAvailableForCrafting(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getAffectedGoldValue(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_gold = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t313 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_nocache_423, nullptr, 0));
        gd::GdArr* _t314 = (_t313.kind == gd::GdVal::Kind::Arr) ? _t313.arr : nullptr;
        uint32_t _len__t315 = _t314 ? _t314->len : 0u;
        for (uint32_t _t315 = 0; _t315 < _len__t315; ++_t315) {
            gd::GdVal lv_item = _t314->data[_t315];
            lv_gold = gd::gd_add(gd_ctx, lv_gold, gd::call_method(gd_ctx, lv_item, SYM_GEN_getPrice_394, nullptr, 0));
        }
    }
    return lv_gold;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_countTypes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_ofItems = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_typesDict = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    {
        gd::GdVal _t316 = gd::gd_iter_seq(gd_ctx.arena, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855));
        gd::GdArr* _t317 = (_t316.kind == gd::GdVal::Kind::Arr) ? _t316.arr : nullptr;
        uint32_t _len__t318 = _t317 ? _t317->len : 0u;
        for (uint32_t _t318 = 0; _t318 < _len__t318; ++_t318) {
            gd::GdVal lv_type = _t317->data[_t318];
            { gd::GdVal _t319 = lv_typesDict; gd::GdVal _t320 = gd::get_index(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), lv_type); gd::set_index(gd_ctx, _t319, _t320, gd::GdVal::from_int(0LL)); }
        }
    }
    {
        gd::GdVal _t321 = gd::gd_iter_seq(gd_ctx.arena, lv_ofItems);
        gd::GdArr* _t322 = (_t321.kind == gd::GdVal::Kind::Arr) ? _t321.arr : nullptr;
        uint32_t _len__t323 = _t322 ? _t322->len : 0u;
        for (uint32_t _t323 = 0; _t323 < _len__t323; ++_t323) {
            gd::GdVal lv_item = _t322->data[_t323];
            {
                gd::GdVal _t324 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, lv_item, SYM_GEN_getTypes_242, nullptr, 0));
                gd::GdArr* _t325 = (_t324.kind == gd::GdVal::Kind::Arr) ? _t324.arr : nullptr;
                uint32_t _len__t326 = _t325 ? _t325->len : 0u;
                for (uint32_t _t326 = 0; _t326 < _len__t326; ++_t326) {
                    gd::GdVal lv_type = _t325->data[_t326];
                    { gd::GdVal _t327 = lv_typesDict; gd::GdVal _t328 = lv_type; gd::set_index(gd_ctx, _t327, _t328, gd::gd_add(gd_ctx, gd::get_index(gd_ctx, _t327, _t328), gd::GdVal::from_int(1LL))); }
                }
            }
        }
    }
    return lv_typesDict;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_hasSameOrientationAsPickup(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getGemsNoNull(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_out = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t329 = gd::gd_iter_seq(gd_ctx.arena, this->f_gems);
        gd::GdArr* _t330 = (_t329.kind == gd::GdVal::Kind::Arr) ? _t329.arr : nullptr;
        uint32_t _len__t331 = _t330 ? _t330->len : 0u;
        for (uint32_t _t331 = 0; _t331 < _len__t331; ++_t331) {
            gd::GdVal lv_gem = _t330->data[_t331];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_gem, gd::GdVal::null())))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_gem}; return gd::call_method(gd_ctx, lv_out, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    return lv_out;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_getGems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_gems;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_buildDamageSource(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__type = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    this->f_damageSource = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0);
    gd::set_prop(gd_ctx, this->f_damageSource, SYM_GEN__rng_1457, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv__type}; return gd::call_method(gd_ctx, this->f_damageSource, SYM_GEN_setItem_1459, _ca, 2); })();
    return this->f_damageSource;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_connectForCombat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_emitter = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_signalName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_methodName = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_binds = (_argc > 3) ? _args[3] : (gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})));
    (void)([&]() { gd::GdVal _ca[] = {lv_emitter, lv_signalName, gd::GdVal::from_obj(this), lv_methodName}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_connectEvent_1504, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_connectForCombat_signal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_emitter = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_signalName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_methodName = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_binds = (_argc > 3) ? _args[3] : (gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})));
    gd::GdVal lv_newConnection = ([&]() { gd::GdVal _ca[] = {lv_emitter, lv_signalName, gd::GdVal::from_obj(this), lv_methodName, lv_binds}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreItem__INNER__CoreSignalConnection), gd::SYM_new, _ca, 5); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_newConnection}; return gd::call_method(gd_ctx, this->f_combatConnections, gd::SYM_push_back, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn_disconnectCombat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t332 = gd::gd_iter_seq(gd_ctx.arena, this->f_combatConnections);
        gd::GdArr* _t333 = (_t332.kind == gd::GdVal::Kind::Arr) ? _t332.arr : nullptr;
        uint32_t _len__t334 = _t333 ? _t333->len : 0u;
        for (uint32_t _t334 = 0; _t334 < _len__t334; ++_t334) {
            gd::GdVal lv_connection = _t333->data[_t334];
            (void)gd::call_method(gd_ctx, lv_connection, SYM_GEN_destroy_1561, nullptr, 0);
        }
    }
    (void)gd::call_method(gd_ctx, this->f_combatConnections, gd::SYM_clear, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn__hasBehaviorMethod(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_methodName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f__behavior, gd::GdVal::null())))) {
        return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_methodName}; return gd::call_method(gd_ctx, this->f__behavior, SYM_GEN_hasBehavior_2591, _ca, 2); })();
    }
    return (gd::gd_truth(gd::gd_in(lv_methodName, Gd__gd_core__CoreItem::get_static_const_or_enum(gd_ctx, SYM_GEN_SELF_BEHAVIOR_METHODS_63))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_methodName}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })())) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItem::fn__behavior_call(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_methodName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_args = (_argc > 1) ? _args[1] : (gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f__behavior, gd::GdVal::null())))) {
        return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_methodName, lv_args}; return gd::call_method(gd_ctx, this->f__behavior, SYM_GEN_callBehavior_2592, _ca, 3); })();
    }
    if (gd::gd_truth((gd::gd_truth(gd::gd_in(lv_methodName, Gd__gd_core__CoreItem::get_static_const_or_enum(gd_ctx, SYM_GEN_SELF_BEHAVIOR_METHODS_63))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_methodName}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        return ([&]() { gd::GdVal _ca[] = {lv_methodName, lv_args}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_callv, _ca, 2); })();
    }
    return gd::GdVal::null();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreItem(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__CoreItem>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__CoreItem = {CLS_Gd__gd_core__CoreItem, "CoreItem", "res://gd_core/CoreItem.gd", nullptr, false, _alloc_Gd__gd_core__CoreItem, &Gd__gd_core__CoreItem::get_static_prop_fn, &Gd__gd_core__CoreItem::call_static_fn};

void Gd__gd_core__BloodGoobert::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Goobert::init_fields(gd_ctx);
    this->f_dam = gd::GdVal::null();
    this->f_vampirism = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__BloodGoobert::meta() const { return &META_Gd__gd_core__BloodGoobert; }
gd::GdVal Gd__gd_core__BloodGoobert::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__BloodGoobert::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__BloodGoobert::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_dam_939: out = this->f_dam; return true;
        case SYM_GEN_vampirism_940: out = this->f_vampirism; return true;
        default: break;
    }
    return Gd__gd_core__Goobert::get_prop(prop, out);
}
bool Gd__gd_core__BloodGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_dam_939: this->f_dam = val; return true;
        case SYM_GEN_vampirism_940: this->f_vampirism = val; return true;
        default: break;
    }
    return Gd__gd_core__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__BloodGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Goobert::has_own_method(m);
}
bool Gd__gd_core__BloodGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__BloodGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__BloodGoobert::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_vampirism}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_212, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BloodGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_dam, gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getVampirism_1210, nullptr, 0)), gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lifesteal", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealLife_331, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BloodGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_dam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_vampirism = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "vampirism", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__BloodGoobert(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__BloodGoobert>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__BloodGoobert = {CLS_Gd__gd_core__BloodGoobert, "BloodGoobert", "res://gd_core/BloodGoobert.gd", &META_Gd__gd_core__Goobert, false, _alloc_Gd__gd_core__BloodGoobert, &Gd__gd_core__BloodGoobert::get_static_prop_fn, &Gd__gd_core__BloodGoobert::call_static_fn};

void Gd__gd_core__CoreBuff::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_type = gd::GdVal::from_int(0);
    this->f_isBuff = gd::GdVal::from_bool(false);
    this->f_character = gd::GdVal::null();
    this->f_current = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_permanentStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_resistChancePercent = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_resistStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_reflectChancePercent = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_cleanseProtectionChancePercent = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_signalName = gd::GdVal::from_cstr(gd_ctx.arena, "");
    this->f_temporaryStacks = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_nextTemporaryTimeout = gd::GdVal::from_int(0);
    this->f_MAX_STACKS = gd::GdVal::from_int(0);
    this->f__timer_left = gd::gd_coerce_float(gd::gd_neg(gd::GdVal::from_float(1.0)));
    this->f__timer_active = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    this->f__timer_eng = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f__timer_seen = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_ctx = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__CoreBuff::meta() const { return &META_Gd__gd_core__CoreBuff; }
gd::GdVal Gd__gd_core__CoreBuff::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_TemporaryStacks_1040: return gd::GdVal::from_cls(&META_Gd__gd_core__CoreBuff__INNER__TemporaryStacks);
        default: break;
    }
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreBuff::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreBuff::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_type_1005: out = this->f_type; return true;
        case SYM_GEN_isBuff_1006: out = this->f_isBuff; return true;
        case SYM_GEN_character_76: out = this->f_character; return true;
        case SYM_GEN_current_1007: out = this->f_current; return true;
        case SYM_GEN_permanentStacks_1008: out = this->f_permanentStacks; return true;
        case SYM_GEN_resistChancePercent_1009: out = this->f_resistChancePercent; return true;
        case SYM_GEN_resistStacks_1010: out = this->f_resistStacks; return true;
        case SYM_GEN_reflectChancePercent_1011: out = this->f_reflectChancePercent; return true;
        case SYM_GEN_cleanseProtectionChancePercent_1012: out = this->f_cleanseProtectionChancePercent; return true;
        case SYM_GEN_signalName_1013: out = this->f_signalName; return true;
        case SYM_GEN_temporaryStacks_1014: out = this->f_temporaryStacks; return true;
        case SYM_GEN_nextTemporaryTimeout_1015: out = this->f_nextTemporaryTimeout; return true;
        case SYM_GEN_MAX_STACKS_1016: out = this->f_MAX_STACKS; return true;
        case SYM_GEN__timer_left_1017: out = this->f__timer_left; return true;
        case SYM_GEN__timer_active_1018: out = this->f__timer_active; return true;
        case SYM_GEN__timer_eng_1019: out = this->f__timer_eng; return true;
        case SYM_GEN__timer_seen_1020: out = this->f__timer_seen; return true;
        case SYM_GEN_ctx_3: out = this->f_ctx; return true;
        case SYM_GEN_TemporaryStacks_1040: out = gd::GdVal::from_cls(&META_Gd__gd_core__CoreBuff__INNER__TemporaryStacks); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreBuff::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_type_1005: this->f_type = gd::gd_coerce_int(val); return true;
        case SYM_GEN_isBuff_1006: this->f_isBuff = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_character_76: this->f_character = val; return true;
        case SYM_GEN_current_1007: this->f_current = gd::gd_coerce_int(val); return true;
        case SYM_GEN_permanentStacks_1008: this->f_permanentStacks = gd::gd_coerce_int(val); return true;
        case SYM_GEN_resistChancePercent_1009: this->f_resistChancePercent = gd::gd_coerce_float(val); return true;
        case SYM_GEN_resistStacks_1010: this->f_resistStacks = gd::gd_coerce_int(val); return true;
        case SYM_GEN_reflectChancePercent_1011: this->f_reflectChancePercent = gd::gd_coerce_float(val); return true;
        case SYM_GEN_cleanseProtectionChancePercent_1012: this->f_cleanseProtectionChancePercent = gd::gd_coerce_float(val); return true;
        case SYM_GEN_signalName_1013: this->f_signalName = val; return true;
        case SYM_GEN_temporaryStacks_1014: this->f_temporaryStacks = val; return true;
        case SYM_GEN_nextTemporaryTimeout_1015: this->f_nextTemporaryTimeout = gd::gd_coerce_int(val); return true;
        case SYM_GEN_MAX_STACKS_1016: this->f_MAX_STACKS = gd::gd_coerce_int(val); return true;
        case SYM_GEN__timer_left_1017: this->f__timer_left = gd::gd_coerce_float(val); return true;
        case SYM_GEN__timer_active_1018: this->f__timer_active = gd::gd_coerce_bool(val); return true;
        case SYM_GEN__timer_eng_1019: this->f__timer_eng = gd::gd_coerce_float(val); return true;
        case SYM_GEN__timer_seen_1020: this->f__timer_seen = gd::gd_coerce_float(val); return true;
        case SYM_GEN_ctx_3: this->f_ctx = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreBuff::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_init_1021: return true;
        case SYM_GEN_getStacks_1022: return true;
        case SYM_GEN_setStacks_1023: return true;
        case SYM_GEN_reset_1024: return true;
        case SYM_GEN_changeResistChance_1025: return true;
        case SYM_GEN_changeResistStacks_1026: return true;
        case SYM_GEN_changeCleanseProtectionChance_1027: return true;
        case SYM_GEN_changeReflectChance_1028: return true;
        case SYM_GEN_gainStacks_1029: return true;
        case SYM_GEN_gainTemporary_1030: return true;
        case SYM_GEN_loseStacks_1031: return true;
        case SYM_GEN_changeCurrentLogShowLabel_1032: return true;
        case SYM_GEN__blnd_snap_1033: return true;
        case SYM_GEN_onTimeout_1034: return true;
        case SYM_GEN_combatEnd_133: return true;
        case SYM_GEN__startTimer_1035: return true;
        case SYM_GEN__stopTimer_1037: return true;
        case SYM_GEN_isTimerActive_1038: return true;
        case SYM_GEN__tick_1039: return true;
        case SYM_GEN_rebuildTimerSeen_141: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreBuff::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_init_1021: out = fn_init(args, argc); return true;
        case SYM_GEN_getStacks_1022: out = fn_getStacks(args, argc); return true;
        case SYM_GEN_setStacks_1023: out = fn_setStacks(args, argc); return true;
        case SYM_GEN_reset_1024: out = fn_reset(args, argc); return true;
        case SYM_GEN_changeResistChance_1025: out = fn_changeResistChance(args, argc); return true;
        case SYM_GEN_changeResistStacks_1026: out = fn_changeResistStacks(args, argc); return true;
        case SYM_GEN_changeCleanseProtectionChance_1027: out = fn_changeCleanseProtectionChance(args, argc); return true;
        case SYM_GEN_changeReflectChance_1028: out = fn_changeReflectChance(args, argc); return true;
        case SYM_GEN_gainStacks_1029: out = fn_gainStacks(args, argc); return true;
        case SYM_GEN_gainTemporary_1030: out = fn_gainTemporary(args, argc); return true;
        case SYM_GEN_loseStacks_1031: out = fn_loseStacks(args, argc); return true;
        case SYM_GEN_changeCurrentLogShowLabel_1032: out = fn_changeCurrentLogShowLabel(args, argc); return true;
        case SYM_GEN__blnd_snap_1033: out = fn__blnd_snap(args, argc); return true;
        case SYM_GEN_onTimeout_1034: out = fn_onTimeout(args, argc); return true;
        case SYM_GEN_combatEnd_133: out = fn_combatEnd(args, argc); return true;
        case SYM_GEN__startTimer_1035: out = fn__startTimer(args, argc); return true;
        case SYM_GEN__f32eng_1036: out = sf__f32eng(gd_ctx, args, argc); return true;
        case SYM_GEN__stopTimer_1037: out = fn__stopTimer(args, argc); return true;
        case SYM_GEN_isTimerActive_1038: out = fn_isTimerActive(args, argc); return true;
        case SYM_GEN__tick_1039: out = fn__tick(args, argc); return true;
        case SYM_GEN_rebuildTimerSeen_141: out = fn_rebuildTimerSeen(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreBuff::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN__f32eng_1036: out = sf__f32eng(gd_ctx, args, argc); return true;
        default: break;
    }
    return false;
}
gd::GdVal Gd__gd_core__CoreBuff::fn_init(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__character = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv__signalName = (_argc > 2) ? _args[2] : (gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u)));
    this->f_type = gd::gd_coerce_int(lv__type);
    this->f_isBuff = gd::gd_coerce_bool(([&]() { gd::GdVal _ca[] = {this->f_type}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_isBuff_1006, _ca, 1); })());
    this->f_character = lv__character;
    this->f_signalName = lv__signalName;
    this->f_ctx = gd::get_prop(gd_ctx, lv__character, SYM_GEN_ctx_3);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_type, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Block_2564))))) {
        this->f_MAX_STACKS = gd::gd_coerce_int(gd::GdVal::from_int(100000LL));
    }
    else {
        this->f_MAX_STACKS = gd::gd_coerce_int(gd::GdVal::from_int(10000LL));
    }
    return gd::GdVal::from_obj(this);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_getStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_current;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_setStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    this->f_current = gd::gd_coerce_int(lv_amount);
    (void)([&]() { gd::GdVal _ca[] = {this->f_character, this->f_type}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_activateBuffCounter_1532, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_reset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setStacks_1023, _ca, 1); })();
    this->f_resistStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_resistChancePercent = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_cleanseProtectionChancePercent = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_reflectChancePercent = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_changeResistChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_resistChancePercent = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_resistChancePercent, lv_chance));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_changeResistStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_resistStacks = gd::gd_coerce_int(gd::gd_max(gd::GdVal::from_int(0LL), gd::gd_add(gd_ctx, this->f_resistStacks, lv_amount)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_changeCleanseProtectionChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_cleanseProtectionChancePercent = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_cleanseProtectionChancePercent, lv_chance));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_changeReflectChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_reflectChancePercent = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_reflectChancePercent, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_gainStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_reflect = (_argc > 3) ? _args[3] : (gd::GdVal::from_bool(false));
    lv_reflect = gd::gd_coerce_bool(lv_reflect);
    return ([&]() { gd::GdVal _ca[] = {lv_amount, gd::gd_neg(gd::GdVal::from_int(1LL)), lv_item, lv_triggerEvent, lv_reflect}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_gainTemporary_1030, _ca, 5); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_gainTemporary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_duration = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_duration = gd::gd_coerce_float(lv_duration);
    gd::GdVal lv_item = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_reflect = (_argc > 4) ? _args[4] : (gd::GdVal::from_bool(false));
    lv_reflect = gd::gd_coerce_bool(lv_reflect);
    gd::GdVal lv_event = gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_resisted = gd::GdVal::from_int(0LL);
        gd::GdVal lv_totalResistChance = this->f_resistChancePercent;
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_reflect)))) : gd::GdVal::from_bool(false)))) {
            lv_totalResistChance = gd::gd_sub(lv_totalResistChance, ([&]() { gd::GdVal _ca[] = {this->f_type}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_getAmplificationChancePercent_197, _ca, 1); })());
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_totalResistChance, gd::GdVal::from_int(0LL))))) {
            {
                gd::GdVal _t335 = gd::gd_iter_seq(gd_ctx.arena, lv_amount);
                gd::GdArr* _t336 = (_t335.kind == gd::GdVal::Kind::Arr) ? _t335.arr : nullptr;
                uint32_t _len__t337 = _t336 ? _t336->len : 0u;
                for (uint32_t _t337 = 0; _t337 < _len__t337; ++_t337) {
                    gd::GdVal lv_i = _t336->data[_t337];
                    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_totalResistChance}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_flipPercent_1640, _ca, 1); })())) {
                        lv_resisted = gd::gd_add(gd_ctx, lv_resisted, gd::GdVal::from_int(1LL));
                    }
                }
            }
        }
        else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_totalResistChance, gd::GdVal::from_int(0LL))))) {
            {
                gd::GdVal _t338 = gd::gd_iter_seq(gd_ctx.arena, lv_amount);
                gd::GdArr* _t339 = (_t338.kind == gd::GdVal::Kind::Arr) ? _t338.arr : nullptr;
                uint32_t _len__t340 = _t339 ? _t339->len : 0u;
                for (uint32_t _t340 = 0; _t340 < _len__t340; ++_t340) {
                    gd::GdVal lv_i = _t339->data[_t340];
                    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::gd_neg(lv_totalResistChance)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_flipPercent_1640, _ca, 1); })())) {
                        lv_amount = gd::gd_coerce_int(gd::gd_add(gd_ctx, lv_amount, gd::GdVal::from_int(1LL)));
                    }
                }
            }
        }
        gd::GdVal lv_left = gd::gd_sub(lv_amount, lv_resisted);
        gd::GdVal lv_reflected = gd::GdVal::from_int(0LL);
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_isBuff)))) {
            if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_reflect)))) {
                {
                    gd::GdVal _t341 = gd::gd_iter_seq(gd_ctx.arena, lv_amount);
                    gd::GdArr* _t342 = (_t341.kind == gd::GdVal::Kind::Arr) ? _t341.arr : nullptr;
                    uint32_t _len__t343 = _t342 ? _t342->len : 0u;
                    for (uint32_t _t343 = 0; _t343 < _len__t343; ++_t343) {
                        gd::GdVal lv_i = _t342->data[_t343];
                        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_reflectChancePercent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_flipPercent_1640, _ca, 1); })())) {
                            lv_reflected = gd::gd_add(gd_ctx, lv_reflected, gd::GdVal::from_int(1LL));
                        }
                    }
                }
                lv_left = gd::gd_sub(lv_left, lv_reflected);
                gd::GdVal lv_reflectedByStacks = gd::GdVal::from_int(0LL);
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_left, gd::GdVal::from_int(0LL))))) {
                    lv_reflectedByStacks = gd::gd_min(lv_left, gd::get_prop(gd_ctx, this->f_character, SYM_GEN_debuffReflectStacks_1073));
                }
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_reflectedByStacks, gd::GdVal::from_int(0LL))))) {
                    lv_reflected = gd::gd_add(gd_ctx, lv_reflected, lv_reflectedByStacks);
                    lv_left = gd::gd_sub(lv_left, lv_reflectedByStacks);
                    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(lv_reflectedByStacks)}; return gd::call_method(gd_ctx, this->f_character, SYM_GEN_changeDebuffReflectStacks_1170, _ca, 1); })();
                }
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_reflected, gd::GdVal::from_int(0LL))))) {
                    lv_amount = gd::gd_coerce_int(gd::gd_sub(lv_amount, lv_reflected));
                    gd::GdVal lv_target = gd::get_prop(gd_ctx, this->f_character, SYM_GEN_opponent_77);
                    (void)gd::call_method(gd_ctx, lv_target, SYM_GEN_randBuffLabelPos_1127, nullptr, 0);
                    (void)gd::call_method(gd_ctx, lv_target, SYM_GEN_randBuffLabelDir_1128, nullptr, 0);
                    (void)([&]() { gd::GdVal _ca[] = {this->f_type, lv_reflected}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_spawnReflectLabel_1541, _ca, 2); })();
                }
            }
            gd::GdVal lv_ownStacksUsed = gd::gd_min(lv_left, this->f_resistStacks);
            lv_resisted = gd::gd_add(gd_ctx, lv_resisted, lv_ownStacksUsed);
            lv_left = gd::gd_sub(lv_left, lv_ownStacksUsed);
            this->f_resistStacks = gd::gd_coerce_int(gd::gd_sub(this->f_resistStacks, lv_ownStacksUsed));
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_left, gd::GdVal::from_int(0LL))))) {
                gd::GdVal lv_characterStacksUsed = gd::gd_min(lv_left, gd::get_prop(gd_ctx, this->f_character, SYM_GEN_debuffResistStacks_1072));
                lv_resisted = gd::gd_add(gd_ctx, lv_resisted, lv_characterStacksUsed);
                (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(lv_characterStacksUsed)}; return gd::call_method(gd_ctx, this->f_character, SYM_GEN_changeDebuffResistStacks_1169, _ca, 1); })();
            }
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_resisted, gd::GdVal::from_int(0LL))))) {
            lv_amount = gd::gd_coerce_int(gd::gd_sub(lv_amount, lv_resisted));
            (void)gd::call_method(gd_ctx, this->f_character, SYM_GEN_randBuffLabelPos_1127, nullptr, 0);
            (void)gd::call_method(gd_ctx, this->f_character, SYM_GEN_randBuffLabelDir_1128, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {this->f_type, lv_resisted}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_spawnResistedLabel_1542, _ca, 2); })();
            gd::GdVal lv_resistedEvent = ([&]() { gd::GdVal _ca[] = {this->f_type, lv_item, lv_resisted, gd::get_prop(gd_ctx, this->f_character, SYM_GEN_playerId_1046), lv_triggerEvent, lv_reflect}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_createEvent_StackResistOrNullify_1336, _ca, 6); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_resistedEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_logEvent_1328, _ca, 1); })();
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
            lv_amount = gd::gd_coerce_int(gd::gd_coerce_int(gd::gd_min(lv_amount, gd::gd_sub(this->f_MAX_STACKS, this->f_current))));
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_amount, gd::GdVal::from_int(0LL))))) {
                return gd::GdVal::null();
            }
            this->f_current = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_current, lv_amount));
            (void)([&]() { gd::GdVal _ca[] = {this->f_character, this->f_type}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_activateBuffCounter_1532, _ca, 2); })();
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_duration, gd::GdVal::from_int(0LL))))) {
                this->f_permanentStacks = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_permanentStacks, lv_amount));
            }
            else {
                gd::GdVal lv_timeout = gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1382), lv_duration);
                gd::GdVal lv_tempStacks = ([&]() { gd::GdVal _ca[] = {lv_amount, lv_timeout, lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreBuff__INNER__TemporaryStacks), gd::SYM_new, _ca, 3); })();
                (void)([&]() { gd::GdVal _ca[] = {lv_tempStacks}; return gd::call_method(gd_ctx, this->f_temporaryStacks, gd::SYM_push_back, _ca, 1); })();
                if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f__timer_active)))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_duration}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__startTimer_1035, _ca, 1); })();
                    this->f_nextTemporaryTimeout = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
                }
                else {
                    gd::GdVal lv_timerLeft = this->f__timer_left;
                    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_timerLeft, gd::GdVal::from_float(0.0))))) {
                        lv_timerLeft = this->f__timer_eng;
                    }
                    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_duration, lv_timerLeft)))) {
                        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__stopTimer_1037, nullptr, 0);
                        (void)([&]() { gd::GdVal _ca[] = {lv_duration}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__startTimer_1035, _ca, 1); })();
                        this->f_nextTemporaryTimeout = gd::gd_coerce_int(gd::gd_sub(gd::call_method(gd_ctx, this->f_temporaryStacks, gd::SYM_size, nullptr, 0), gd::GdVal::from_int(1LL)));
                    }
                }
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gain", 4u)), ([&]() { gd::GdVal _ca[] = {lv_duration}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__blnd_snap_1033, _ca, 2); })();
            }
            if (gd::gd_truth(lv_item)) {
                gd::GdVal lv_isPlayer = gd::GdVal::from_bool(gd::gd_eq(this->f_character, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1284)));
                if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_isBuff)))) {
                    lv_isPlayer = gd::GdVal::from_bool(!gd::gd_truth(lv_isPlayer));
                }
                (void)([&]() { gd::GdVal _ca[] = {this->f_type, lv_amount, lv_isPlayer}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_stackChanged_234, _ca, 3); })();
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(lv_duration, gd::GdVal::from_int(0LL))))) {
                    lv_event = ([&]() { gd::GdVal _ca[] = {this->f_type, lv_item, lv_amount, gd::get_prop(gd_ctx, this->f_character, SYM_GEN_playerId_1046), lv_triggerEvent, gd::GdVal::from_bool(false), lv_reflect}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_createEvent_Stack_1333, _ca, 7); })();
                }
                else {
                    lv_event = ([&]() { gd::GdVal _ca[] = {this->f_type, lv_item, lv_amount, lv_duration, gd::get_prop(gd_ctx, this->f_character, SYM_GEN_playerId_1046), lv_triggerEvent, lv_reflect}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_createEvent_StackTemporary_1334, _ca, 7); })();
                }
                gd::GdVal lv_appliedToOpponent = gd::GdVal::from_bool(gd::gd_ne(this->f_character, gd::call_method(gd_ctx, lv_item, SYM_GEN_character_76, nullptr, 0)));
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "SRC", 3u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gain_label", 10u)), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), SYM_GEN_identifier_1577))), ([&]() { gd::GdVal _ca[] = {this->f_type}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_trace_diag_1645, _ca, 4); })();
                (void)gd::call_method(gd_ctx, lv_item, SYM_GEN_getNextFreeLabelPosition_380, nullptr, 0);
                (void)([&]() { gd::GdVal _ca[] = {this->f_type, lv_item, lv_amount, lv_appliedToOpponent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_spawnBuffLabel_item_1544, _ca, 4); })();
                (void)([&]() { gd::GdVal _ca[] = {this->f_character, this->f_signalName, lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::call_method(gd_ctx, lv_event, SYM_GEN_getAmount_1485, nullptr, 0), lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitEvent_1502, _ca, 4); })();
            }
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_reflected, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_type, lv_reflected, lv_duration, lv_item, lv_triggerEvent, gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_character, SYM_GEN_opponent_77), SYM_GEN_gainStacksTemporary_1202, _ca, 6); })();
        }
    }
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_loseStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_used = (_argc > 3) ? _args[3] : (gd::GdVal::from_bool(false));
    lv_amount = gd::gd_coerce_int(gd::gd_min(this->f_current, lv_amount));
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_used)))) {
        gd::GdVal lv_protected = gd::GdVal::from_int(0LL);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_cleanseProtectionChancePercent, gd::GdVal::from_int(0LL))))) {
            {
                gd::GdVal _t344 = gd::gd_iter_seq(gd_ctx.arena, lv_amount);
                gd::GdArr* _t345 = (_t344.kind == gd::GdVal::Kind::Arr) ? _t344.arr : nullptr;
                uint32_t _len__t346 = _t345 ? _t345->len : 0u;
                for (uint32_t _t346 = 0; _t346 < _len__t346; ++_t346) {
                    gd::GdVal lv_i = _t345->data[_t346];
                    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_cleanseProtectionChancePercent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_flipPercent_1640, _ca, 1); })())) {
                        lv_protected = gd::gd_add(gd_ctx, lv_protected, gd::GdVal::from_int(1LL));
                    }
                }
            }
        }
        else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_cleanseProtectionChancePercent, gd::GdVal::from_int(0LL))))) {
            {
                gd::GdVal _t347 = gd::gd_iter_seq(gd_ctx.arena, lv_amount);
                gd::GdArr* _t348 = (_t347.kind == gd::GdVal::Kind::Arr) ? _t347.arr : nullptr;
                uint32_t _len__t349 = _t348 ? _t348->len : 0u;
                for (uint32_t _t349 = 0; _t349 < _len__t349; ++_t349) {
                    gd::GdVal lv_i = _t348->data[_t349];
                    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_cleanseProtectionChancePercent)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_flipPercent_1640, _ca, 1); })())) {
                        lv_protected = gd::gd_sub(lv_protected, gd::GdVal::from_int(1LL));
                    }
                }
            }
        }
        lv_amount = gd::gd_coerce_int(gd::gd_sub(lv_amount, lv_protected));
        lv_amount = gd::gd_coerce_int(gd::gd_clamp(lv_amount, gd::GdVal::from_int(0LL), this->f_current));
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_resistStacks, gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
            gd::GdVal lv_protectedByStacks = gd::gd_min(lv_amount, this->f_resistStacks);
            lv_protected = gd::gd_add(gd_ctx, lv_protected, lv_protectedByStacks);
            lv_amount = gd::gd_coerce_int(gd::gd_sub(lv_amount, lv_protectedByStacks));
            this->f_resistStacks = gd::gd_coerce_int(gd::gd_sub(this->f_resistStacks, lv_protectedByStacks));
        }
        if (gd::gd_truth((gd::gd_truth((gd::gd_truth((gd::gd_truth(this->f_isBuff) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_type, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Block_2564))))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, this->f_character, SYM_GEN_buffProtectStacks_1074), gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
            gd::GdVal lv_protectedByStacks = gd::gd_min(lv_amount, gd::get_prop(gd_ctx, this->f_character, SYM_GEN_buffProtectStacks_1074));
            lv_protected = gd::gd_add(gd_ctx, lv_protected, lv_protectedByStacks);
            lv_amount = gd::gd_coerce_int(gd::gd_sub(lv_amount, lv_protectedByStacks));
            gd::set_prop(gd_ctx, this->f_character, SYM_GEN_buffProtectStacks_1074, gd::gd_sub(gd::get_prop(gd_ctx, this->f_character, SYM_GEN_buffProtectStacks_1074), lv_protectedByStacks));
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_protected, gd::GdVal::from_int(0LL))))) {
            (void)gd::call_method(gd_ctx, this->f_character, SYM_GEN_randBuffLabelPos_1127, nullptr, 0);
            (void)gd::call_method(gd_ctx, this->f_character, SYM_GEN_randBuffLabelDir_1128, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {this->f_type, lv_protected}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_spawnProtectedLabel_1543, _ca, 2); })();
            gd::GdVal lv_protectedEvent = ([&]() { gd::GdVal _ca[] = {this->f_type, lv_item, lv_protected, gd::get_prop(gd_ctx, this->f_character, SYM_GEN_playerId_1046), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_createEvent_StackProtect_1337, _ca, 5); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_protectedEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_logEvent_1328, _ca, 1); })();
        }
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_permanentStacks, lv_amount)))) {
        this->f_permanentStacks = gd::gd_coerce_int(gd::gd_sub(this->f_permanentStacks, lv_amount));
    }
    else {
        gd::GdVal lv_tempToCleanse = gd::gd_sub(lv_amount, this->f_permanentStacks);
        this->f_permanentStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
        while (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_tempToCleanse, gd::GdVal::from_int(0LL))))) {
            if (gd::gd_truth(gd::call_method(gd_ctx, this->f_temporaryStacks, gd::SYM_empty, nullptr, 0))) {
                break;
            }
            gd::GdVal lv_farthestTimeout = gd::GdVal::from_int(0LL);
            gd::GdVal lv_farthestIndex = gd::gd_neg(gd::GdVal::from_int(1LL));
            {
                gd::GdVal _t350 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_temporaryStacks, gd::SYM_size, nullptr, 0));
                gd::GdArr* _t351 = (_t350.kind == gd::GdVal::Kind::Arr) ? _t350.arr : nullptr;
                uint32_t _len__t352 = _t351 ? _t351->len : 0u;
                for (uint32_t _t352 = 0; _t352 < _len__t352; ++_t352) {
                    gd::GdVal lv_i = _t351->data[_t352];
                    gd::GdVal lv_stacks = gd::get_index(gd_ctx, this->f_temporaryStacks, lv_i);
                    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, lv_stacks, SYM_GEN_timeout_1042), lv_farthestTimeout)))) {
                        lv_farthestTimeout = gd::get_prop(gd_ctx, lv_stacks, SYM_GEN_timeout_1042);
                        lv_farthestIndex = lv_i;
                    }
                }
            }
            gd::GdVal lv_farthest = gd::get_index(gd_ctx, this->f_temporaryStacks, lv_farthestIndex);
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, lv_farthest, SYM_GEN_amount_1041), lv_tempToCleanse)))) {
                gd::set_prop(gd_ctx, lv_farthest, SYM_GEN_amount_1041, gd::gd_sub(gd::get_prop(gd_ctx, lv_farthest, SYM_GEN_amount_1041), lv_tempToCleanse));
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "partial", 7u)), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_farthestIndex}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "amt", 3u))), ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, lv_farthest, SYM_GEN_amount_1041)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__blnd_snap_1033, _ca, 2); })();
                lv_tempToCleanse = gd::GdVal::from_int(0LL);
            }
            else {
                lv_tempToCleanse = gd::gd_sub(lv_tempToCleanse, gd::get_prop(gd_ctx, lv_farthest, SYM_GEN_amount_1041));
                (void)([&]() { gd::GdVal _ca[] = {lv_farthestIndex}; return gd::call_method(gd_ctx, this->f_temporaryStacks, gd::SYM_remove, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lose", 4u)), ([&]() { gd::GdVal _ca[] = {lv_farthestIndex}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__blnd_snap_1033, _ca, 2); })();
                if (gd::gd_truth(gd::call_method(gd_ctx, this->f_temporaryStacks, gd::SYM_empty, nullptr, 0))) {
                    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__stopTimer_1037, nullptr, 0);
                }
            }
        }
    }
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false), lv_amount, lv_item, lv_triggerEvent, lv_used}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeCurrentLogShowLabel_1032, _ca, 5); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_changeCurrentLogShowLabel(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_isTimeout = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_isTimeout = gd::gd_coerce_bool(lv_isTimeout);
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_used = (_argc > 4) ? _args[4] : (gd::GdVal::from_bool(false));
    lv_used = gd::gd_coerce_bool(lv_used);
    gd::GdVal lv_change = gd::gd_min(this->f_current, lv_amount);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_change, gd::GdVal::from_int(0LL))))) {
        this->f_current = gd::gd_coerce_int(gd::gd_sub(this->f_current, lv_change));
        (void)([&]() { gd::GdVal _ca[] = {this->f_character, this->f_type}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_activateBuffCounter_1532, _ca, 2); })();
        if (gd::gd_truth(lv_item)) {
            gd::GdVal lv_isPlayer = gd::GdVal::from_bool(gd::gd_eq(this->f_character, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1284)));
            if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_used)))) {
                if (gd::gd_truth(this->f_isBuff)) {
                    lv_isPlayer = gd::GdVal::from_bool(!gd::gd_truth(lv_isPlayer));
                }
            }
            (void)([&]() { gd::GdVal _ca[] = {this->f_type, gd::gd_neg(lv_change), lv_isPlayer, lv_used}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_stackChanged_234, _ca, 4); })();
            gd::GdVal lv_event = gd::GdVal::null();
            if (gd::gd_truth(lv_isTimeout)) {
                lv_event = ([&]() { gd::GdVal _ca[] = {this->f_type, lv_item, gd::gd_neg(lv_change), gd::get_prop(gd_ctx, this->f_character, SYM_GEN_playerId_1046), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_createEvent_StackTimeout_1335, _ca, 5); })();
            }
            else {
                lv_event = ([&]() { gd::GdVal _ca[] = {this->f_type, lv_item, gd::gd_neg(lv_change), gd::get_prop(gd_ctx, this->f_character, SYM_GEN_playerId_1046), lv_triggerEvent, lv_used}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_createEvent_Stack_1333, _ca, 6); })();
            }
            (void)([&]() { gd::GdVal _ca[] = {this->f_character, this->f_signalName, lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::call_method(gd_ctx, lv_event, SYM_GEN_getAmount_1485, nullptr, 0), lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitEvent_1502, _ca, 4); })();
            gd::GdVal lv_appliedToOpponent = gd::GdVal::from_bool(gd::gd_ne(this->f_character, gd::call_method(gd_ctx, lv_item, SYM_GEN_character_76, nullptr, 0)));
            (void)gd::call_method(gd_ctx, lv_item, SYM_GEN_getNextFreeLabelPosition_380, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {this->f_type, lv_item, gd::gd_neg(lv_change), lv_appliedToOpponent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_spawnBuffLabel_item_1544, _ca, 4); })();
            return lv_event;
        }
    }
    return gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn__blnd_snap(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_op = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_pre = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_oracle_trace_1633)) ? gd::GdVal::from_bool(gd::gd_truth(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN__stacktrace_1635))) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv__b = gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u));
        {
            gd::GdVal _t353 = gd::gd_iter_seq(gd_ctx.arena, this->f_temporaryStacks);
            gd::GdArr* _t354 = (_t353.kind == gd::GdVal::Kind::Arr) ? _t353.arr : nullptr;
            uint32_t _len__t355 = _t354 ? _t354->len : 0u;
            for (uint32_t _t355 = 0; _t355 < _len__t355; ++_t355) {
                gd::GdVal lv_ts = _t354->data[_t355];
                lv__b = gd::gd_add(gd_ctx, lv__b, gd::gd_mod(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "(%s@%s)", 7u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, lv_ts, SYM_GEN_amount_1041)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), gd::GdVal::from_int(5LL)}; return gd::call_method(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, lv_ts, SYM_GEN_timeout_1042)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::SYM_substr, _ca, 2); })()}))));
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "BLND", 4u)), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "p", 1u)), ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_character, SYM_GEN_playerId_1046)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " ty", 3u))), ([&]() { gd::GdVal _ca[] = {this->f_type}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " ", 1u))), lv_op), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " ", 1u))), lv_pre), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "len=", 4u)), ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, this->f_temporaryStacks, gd::SYM_size, nullptr, 0)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " ntp=", 5u))), ([&]() { gd::GdVal _ca[] = {this->f_nextTemporaryTimeout}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " tm=", 4u))), ([&]() { gd::GdVal _ca[] = {this->f__timer_active}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "/", 1u))), ([&]() { gd::GdVal _ca[] = {this->f__timer_left}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "/e", 2u))), ([&]() { gd::GdVal _ca[] = {this->f__timer_eng}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "/s", 2u))), ([&]() { gd::GdVal _ca[] = {this->f__timer_seen}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " fr=", 4u))), ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_frame_counter_1384)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), lv__b}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_trace_diag_1645, _ca, 4); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_onTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "fire", 4u)), ([&]() { gd::GdVal _ca[] = {this->f_nextTemporaryTimeout}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__blnd_snap_1033, _ca, 2); })();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_nextTemporaryTimeout, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_nextTemporaryTimeout, gd::call_method(gd_ctx, this->f_temporaryStacks, gd::SYM_size, nullptr, 0)))))))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_timedOutStacks = gd::get_index(gd_ctx, this->f_temporaryStacks, this->f_nextTemporaryTimeout);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::get_prop(gd_ctx, lv_timedOutStacks, SYM_GEN_amount_1041), gd::get_prop(gd_ctx, lv_timedOutStacks, SYM_GEN_item_1043)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeCurrentLogShowLabel_1032, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_nextTemporaryTimeout}; return gd::call_method(gd_ctx, this->f_temporaryStacks, gd::SYM_remove, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "timeout", 7u)), ([&]() { gd::GdVal _ca[] = {this->f_nextTemporaryTimeout}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__blnd_snap_1033, _ca, 2); })();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, this->f_temporaryStacks, gd::SYM_empty, nullptr, 0))))) {
        gd::GdVal lv_earliestTimeout = gd::GdVal::from_float(std::numeric_limits<double>::infinity());
        gd::GdVal lv_earliestIndex = gd::gd_neg(gd::GdVal::from_int(1LL));
        {
            gd::GdVal _t356 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_temporaryStacks, gd::SYM_size, nullptr, 0));
            gd::GdArr* _t357 = (_t356.kind == gd::GdVal::Kind::Arr) ? _t356.arr : nullptr;
            uint32_t _len__t358 = _t357 ? _t357->len : 0u;
            for (uint32_t _t358 = 0; _t358 < _len__t358; ++_t358) {
                gd::GdVal lv_i = _t357->data[_t358];
                gd::GdVal lv_stacks = gd::get_index(gd_ctx, this->f_temporaryStacks, lv_i);
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::get_prop(gd_ctx, lv_stacks, SYM_GEN_timeout_1042), lv_earliestTimeout)))) {
                    lv_earliestTimeout = gd::get_prop(gd_ctx, lv_stacks, SYM_GEN_timeout_1042);
                    lv_earliestIndex = lv_i;
                }
            }
        }
        this->f_nextTemporaryTimeout = gd::gd_coerce_int(lv_earliestIndex);
        gd::GdVal lv_delay = gd::gd_sub(lv_earliestTimeout, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1382));
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "rearm", 5u)), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "delay=", 6u)), ([&]() { gd::GdVal _ca[] = {lv_delay}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " et=", 4u))), ([&]() { gd::GdVal _ca[] = {lv_earliestTimeout}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " now=", 5u))), ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1382)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__blnd_snap_1033, _ca, 2); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(lv_delay, gd::GdVal::from_float(0.01))))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onTimeout_1034, nullptr, 0);
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {lv_delay}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__startTimer_1035, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_combatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__stopTimer_1037, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_temporaryStacks, gd::SYM_clear, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn__startTimer(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_duration = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_duration = gd::gd_coerce_float(lv_duration);
    this->f__timer_eng = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {lv_duration}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreBuff::call_static_fn(gd_ctx, SYM_GEN__f32eng_1036, _ca, 1, _out); return _out; })());
    this->f__timer_active = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::sf__f32eng(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_x = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_x = gd::gd_coerce_float(lv_x);
    gd::GdVal lv_pa = gd::GdVal::from_arr(gd::GdArr::create_pool_real(gd_ctx.arena));
    (void)([&]() { gd::GdVal _ca[] = {lv_x}; return gd::call_method(gd_ctx, lv_pa, gd::SYM_append, _ca, 1); })();
    return gd::get_index(gd_ctx, lv_pa, gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn__stopTimer(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f__timer_active = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    this->f__timer_eng = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    if (gd::gd_truth(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_keyed_stop_clears_seen_1410))) {
        this->f__timer_seen = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_isTimerActive(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f__timer_active;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn__tick(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f__timer_active)))) {
        this->f__timer_left = gd::gd_coerce_float(gd::gd_neg(gd::GdVal::from_float(1.0)));
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f__timer_eng, this->f__timer_seen)))) {
        this->f__timer_left = gd::gd_coerce_float(gd::gd_sub(this->f__timer_left, lv_delta));
    }
    else {
        this->f__timer_left = gd::gd_coerce_float(this->f__timer_eng);
    }
    this->f__timer_seen = gd::gd_coerce_float(this->f__timer_eng);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f__timer_left, gd::GdVal::from_float(0.0))))) {
        return gd::GdVal::null();
    }
    this->f__timer_active = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    this->f__timer_eng = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onTimeout_1034, nullptr, 0);
    if (gd::gd_truth(this->f__timer_active)) {
        this->f__timer_left = gd::gd_coerce_float(this->f__timer_eng);
        this->f__timer_seen = gd::gd_coerce_float(this->f__timer_eng);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreBuff::fn_rebuildTimerSeen(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f__timer_active)))) {
        this->f__timer_eng = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    }
    this->f__timer_left = gd::gd_coerce_float(this->f__timer_eng);
    this->f__timer_seen = gd::gd_coerce_float(this->f__timer_eng);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreBuff(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__CoreBuff>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__CoreBuff = {CLS_Gd__gd_core__CoreBuff, "CoreBuff", "res://gd_core/CoreBuff.gd", nullptr, false, _alloc_Gd__gd_core__CoreBuff, &Gd__gd_core__CoreBuff::get_static_prop_fn, &Gd__gd_core__CoreBuff::call_static_fn};

void Gd__gd_core__CoreItemBook::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_descriptors = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f__ctx = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__CoreItemBook::meta() const { return &META_Gd__gd_core__CoreItemBook; }
gd::GdVal Gd__gd_core__CoreItemBook::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_DESCRIPTOR_IDS_1563: return ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 49); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "boxOfRichesDescriptor", 21u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Box of Riches", 13u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "deckOfCardsDescriptor", 21u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Deck of Cards", 13u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "crossbladesDescriptor", 21u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Crossblades", 11u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "platinCardDescriptor", 20u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Platin Customer Card", 20u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "customerCardDescriptor", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Customer Card", 13u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "staminaSackDescriptor", 21u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Stamina Sack", 12u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "presentDescriptor", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Present", 7u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "flameDescriptor", 15u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Flame", 5u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "forgingHammerDescriptor", 23u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Forging Hammer", 14u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "amuletDescriptor", 16u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Amulet Unidentified", 19u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "amuletOfFeastingDescriptor", 26u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Amulet of Feasting", 18u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "starOfCourageDescriptor", 23u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Star of Courage", 15u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "toolboxDescriptor", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Toolbox", 7u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stableRecombobulatorDescriptor", 30u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Stable Recombobulator", 21u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "unstableRecombobulatorDescriptor", 32u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Unstable Recombobulator", 23u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "extraBagsDescriptor", 19u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Extra Bags", 10u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "rainbowBadgeDescriptor", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Rainbow Badge", 13u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stoneBadgeDescriptor", 20u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Stone Badge", 11u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spiritBellsDescriptor", 21u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Spirit Bells", 12u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "bagOfGivingDescriptor", 21u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Bag of Giving", 13u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "chessboardDescriptor", 20u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Chess Board", 11u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "snowmanDescriptor", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Snowman", 7u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "uniquelyUniqueDescriptor", 24u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Uniquely Unique", 15u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "bagtacularDescriptor", 20u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Bagtacular", 10u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "justStatsDescriptor", 19u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Just Stats", 10u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "moreStatsDescriptor", 19u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "More Stats", 10u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "unidentifiedSkillDescriptor", 27u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Unidentified Skill", 18u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "digDeeperDescriptor", 19u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Dig Deeper", 10u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "puzzleboxDescriptor", 19u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Puzzlebox", 9u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "puzzleBadgeDescriptor", 21u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Puzzle Badge", 12u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "sewingCaseDescriptor", 20u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Sewing Case", 11u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "twineDescriptor", 15u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Twine", 5u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "arcaneIntellectDescriptor", 25u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Arcane Intellect", 16u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "fedoraDescriptor", 16u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Fedora", 6u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "piggyOfRichesDescriptor", 23u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Piggy of Riches", 15u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "batteryDescriptor", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Battery", 7u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "coilDescriptor", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Coil", 4u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "chargeSplitterDescriptor", 24u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Charge Splitter", 15u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "manaCrystalDescriptor", 21u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Mana Crystal", 12u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lightningStaffDescriptor", 24u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Lightning Staff", 15u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "boxofCogsDescriptor", 19u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Engineer Bag 2", 14u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cogDescriptor", 13u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Cog", 3u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "generatorDescriptor", 19u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Generator", 9u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cogBadgeDescriptor", 18u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Cog Badge", 9u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "contraptronDescriptor", 21u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Con-Trap-Tron", 13u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "bloodAmuletDescriptor", 21u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Blood Amulet", 12u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "magicRingDescriptor", 19u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Magic Ring", 10u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "superiorRingDescriptor", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Superior Ring", 13u))); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "hyperCubeDescriptor", 19u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Hypercube", 9u))); return gd::GdVal::from_dict(d); })();
        default: break;
    }
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreItemBook::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreItemBook::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_descriptors_1562: out = this->f_descriptors; return true;
        case SYM_GEN__ctx_1325: out = this->f__ctx; return true;
        case SYM_GEN_DESCRIPTOR_IDS_1563: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItemBook::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_descriptors_1562: this->f_descriptors = val; return true;
        case SYM_GEN__ctx_1325: this->f__ctx = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItemBook::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_getDescriptor_1564: return true;
        case SYM_GEN_hasDescriptor_1565: return true;
        case SYM_GEN_register_1566: return true;
        case SYM_GEN__sideItems_1567: return true;
        case SYM_GEN__inventorySide_1568: return true;
        case SYM_GEN__filter_1569: return true;
        case SYM_GEN_getItemsInInventoryOfType_1570: return true;
        case SYM_GEN_getItemsInInventoryOfType_opponent_1571: return true;
        case SYM_GEN_countItemsInInventoryOfType_1572: return true;
        case SYM_GEN_countItemsInInventoryOfType_opponent_1573: return true;
        case SYM_GEN_countPlacedItemsInInventoryOfType_1574: return true;
        case SYM_GEN_isItemInInventory_1575: return true;
        case SYM_GEN_isItemInInventory_opponent_1576: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItemBook::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_getDescriptor_1564: out = fn_getDescriptor(args, argc); return true;
        case SYM_GEN_hasDescriptor_1565: out = fn_hasDescriptor(args, argc); return true;
        case SYM_GEN_register_1566: out = fn_register(args, argc); return true;
        case SYM_GEN__sideItems_1567: out = fn__sideItems(args, argc); return true;
        case SYM_GEN__inventorySide_1568: out = fn__inventorySide(args, argc); return true;
        case SYM_GEN__filter_1569: out = fn__filter(args, argc); return true;
        case SYM_GEN_getItemsInInventoryOfType_1570: out = fn_getItemsInInventoryOfType(args, argc); return true;
        case SYM_GEN_getItemsInInventoryOfType_opponent_1571: out = fn_getItemsInInventoryOfType_opponent(args, argc); return true;
        case SYM_GEN_countItemsInInventoryOfType_1572: out = fn_countItemsInInventoryOfType(args, argc); return true;
        case SYM_GEN_countItemsInInventoryOfType_opponent_1573: out = fn_countItemsInInventoryOfType_opponent(args, argc); return true;
        case SYM_GEN_countPlacedItemsInInventoryOfType_1574: out = fn_countPlacedItemsInInventoryOfType(args, argc); return true;
        case SYM_GEN_isItemInInventory_1575: out = fn_isItemInInventory(args, argc); return true;
        case SYM_GEN_isItemInInventory_opponent_1576: out = fn_isItemInInventory_opponent(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItemBook::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return false;
}
gd::GdVal Gd__gd_core__CoreItemBook::fn__init(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemBook::fn_getDescriptor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_itemName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_itemName}; return gd::call_method(gd_ctx, this->f_descriptors, gd::SYM_has, _ca, 1); })())))) {
        { gd::GdVal _t359 = this->f_descriptors; gd::GdVal _t360 = lv_itemName; gd::set_index(gd_ctx, _t359, _t360, ([&]() { gd::GdVal _ca[] = {([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 2); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "identifier", 10u)), lv_itemName); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "name", 4u)), lv_itemName); return gd::GdVal::from_dict(d); })()}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreItemData), gd::SYM_new, nullptr, 0), SYM_GEN_fromDict_1630, _ca, 1); })()); }
    }
    return gd::get_index(gd_ctx, this->f_descriptors, lv_itemName);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemBook::fn_hasDescriptor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_itemName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_itemName}; return gd::call_method(gd_ctx, this->f_descriptors, gd::SYM_has, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemBook::fn_register(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_data = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_data, SYM_GEN_name_7), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u)))))) {
        { gd::GdVal _t361 = this->f_descriptors; gd::GdVal _t362 = gd::get_prop(gd_ctx, lv_data, SYM_GEN_name_7); gd::set_index(gd_ctx, _t361, _t362, lv_data); }
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_data, SYM_GEN_identifier_1577), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u)))))) {
        { gd::GdVal _t363 = this->f_descriptors; gd::GdVal _t364 = gd::get_prop(gd_ctx, lv_data, SYM_GEN_identifier_1577); gd::set_index(gd_ctx, _t363, _t364, lv_data); }
    }
    return lv_data;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemBook::fn__sideItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_opponentSide = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_opponentSide = gd::gd_coerce_bool(lv_opponentSide);
    if (gd::gd_truth(lv_opponentSide)) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_opponent_77), gd::GdVal::null())))) {
            return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
        }
        return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_opponent_77), SYM_GEN_inventory_5), SYM_GEN_getItemsAndGems_1513, nullptr, 0);
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_player_1284), gd::GdVal::null())))) {
        return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    }
    return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_player_1284), SYM_GEN_inventory_5), SYM_GEN_getItemsAndGems_1513, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemBook::fn__inventorySide(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_item, SYM_GEN_ownerType_51), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_PlayerInventory_2555)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_item, SYM_GEN_ownerType_51), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_Socket_2590))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemBook::fn__filter(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_opponentSide = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_opponentSide = gd::gd_coerce_bool(lv_opponentSide);
    gd::GdVal lv_out = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t365 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {lv_opponentSide}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__sideItems_1567, _ca, 1); })());
        gd::GdArr* _t366 = (_t365.kind == gd::GdVal::Kind::Arr) ? _t365.arr : nullptr;
        uint32_t _len__t367 = _t366 ? _t366->len : 0u;
        for (uint32_t _t367 = 0; _t367 < _len__t367; ++_t367) {
            gd::GdVal lv_item = _t366->data[_t367];
            if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), lv_descr))))))) {
                continue;
            }
            if (gd::gd_truth((gd::gd_truth(lv_opponentSide) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__inventorySide_1568, _ca, 1); })()))))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, lv_out, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    return lv_out;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemBook::fn_getItemsInInventoryOfType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__filter_1569, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemBook::fn_getItemsInInventoryOfType_opponent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__filter_1569, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemBook::fn_countItemsInInventoryOfType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__filter_1569, _ca, 2); })(), gd::SYM_size, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemBook::fn_countItemsInInventoryOfType_opponent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__filter_1569, _ca, 2); })(), gd::SYM_size, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemBook::fn_countPlacedItemsInInventoryOfType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_count = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t368 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__sideItems_1567, _ca, 1); })());
        gd::GdArr* _t369 = (_t368.kind == gd::GdVal::Kind::Arr) ? _t368.arr : nullptr;
        uint32_t _len__t370 = _t369 ? _t369->len : 0u;
        for (uint32_t _t370 = 0; _t370 < _len__t370; ++_t370) {
            gd::GdVal lv_item = _t369->data[_t370];
            if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), lv_descr))))))) {
                continue;
            }
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_item, SYM_GEN_ownerType_51), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_Socket_2590))))) {
                lv_count = gd::gd_add(gd_ctx, lv_count, gd::GdVal::from_int(1LL));
            }
            else if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_item, SYM_GEN_ownerType_51), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_PlayerInventory_2555)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::get_prop(gd_ctx, lv_item, SYM_GEN_placed_6))) : gd::GdVal::from_bool(false)))) {
                lv_count = gd::gd_add(gd_ctx, lv_count, gd::GdVal::from_int(1LL));
            }
        }
    }
    return lv_count;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemBook::fn_isItemInInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__filter_1569, _ca, 2); })(), gd::SYM_empty, nullptr, 0)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemBook::fn_isItemInInventory_opponent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__filter_1569, _ca, 2); })(), gd::SYM_empty, nullptr, 0)));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreItemBook(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__CoreItemBook>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__CoreItemBook = {CLS_Gd__gd_core__CoreItemBook, "CoreItemBook", "res://gd_core/CoreItemBook.gd", nullptr, false, _alloc_Gd__gd_core__CoreItemBook, &Gd__gd_core__CoreItemBook::get_static_prop_fn, &Gd__gd_core__CoreItemBook::call_static_fn};

void Gd__gd_core__DarkestLotus::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Card::init_fields(gd_ctx);
    this->f_manaParticles = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__DarkestLotus::meta() const { return &META_Gd__gd_core__DarkestLotus; }
gd::GdVal Gd__gd_core__DarkestLotus::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Card::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__DarkestLotus::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__DarkestLotus::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_manaParticles_1731: out = this->f_manaParticles; return true;
        default: break;
    }
    return Gd__gd_core__Card::get_prop(prop, out);
}
bool Gd__gd_core__DarkestLotus::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaParticles_1731: this->f_manaParticles = val; return true;
        default: break;
    }
    return Gd__gd_core__Card::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__DarkestLotus::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doRevealEffect_893: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Card::has_own_method(m);
}
bool Gd__gd_core__DarkestLotus::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doRevealEffect_893: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Card::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__DarkestLotus::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Card::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__DarkestLotus::fn_doRevealEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_mana = gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), this->f_chainPosition);
    (void)([&]() { gd::GdVal _ca[] = {lv_mana}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0), this->f_chainPosition)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeRandomBuffs_374, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DarkestLotus::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Card::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__DarkestLotus(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__DarkestLotus>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__DarkestLotus = {CLS_Gd__gd_core__DarkestLotus, "DarkestLotus", "res://gd_core/DarkestLotus.gd", &META_Gd__gd_core__Card, false, _alloc_Gd__gd_core__DarkestLotus, &Gd__gd_core__DarkestLotus::get_static_prop_fn, &Gd__gd_core__DarkestLotus::call_static_fn};

void Gd__gd_core__Flute::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_options = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
}
const gd::GdClassMeta* Gd__gd_core__Flute::meta() const { return &META_Gd__gd_core__Flute; }
gd::GdVal Gd__gd_core__Flute::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Flute::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Flute::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_options_1781: out = this->f_options; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__Flute::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_options_1781: this->f_options = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Flute::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Flute::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Flute::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Flute::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Flute::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0), gd::GdVal::from_float(100.0)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    this->f_options = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL), gd::GdVal::from_int(2LL)}));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Flute::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rng = ([&]() { gd::GdVal _ca[] = {this->f_options}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_pickRandomElement_1650, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_rng, gd::GdVal::from_int(0LL))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, nullptr, 0);
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_rng, gd::GdVal::from_int(1LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_320, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    this->f_options = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL), gd::GdVal::from_int(2LL)}));
    (void)([&]() { gd::GdVal _ca[] = {lv_rng}; return gd::call_method(gd_ctx, this->f_options, gd::SYM_erase, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Flute::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Flute(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Flute>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Flute = {CLS_Gd__gd_core__Flute, "Flute", "res://gd_core/Flute.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__Flute, &Gd__gd_core__Flute::get_static_prop_fn, &Gd__gd_core__Flute::call_static_fn};

static const gd::GdEnum::KV _ekv_Gd__gd_core__HolySpear_SpearState[] = {{"Inactive", 0LL}, {"Active", 1LL}, {"Used", 2LL}};
static const gd::GdEnum _enum_Gd__gd_core__HolySpear_SpearState = {"SpearState", _ekv_Gd__gd_core__HolySpear_SpearState, 3u};
void Gd__gd_core__HolySpear::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
    this->f_blockRemoval = gd::GdVal::from_int(0);
    this->f_cleanses = gd::GdVal::from_int(0);
    this->f_spearState = gd::GdVal::from_int(0);
    this->f_activationParticles = gd::GdVal::null();
    this->f_buffTimer = gd::GdVal::null();
    this->f_blockRemovalPerSlot = gd::GdVal::from_int(0);
    this->f_buffedSpeed = gd::GdVal::null();
    this->f_manaCost = gd::GdVal::from_int(0);
    this->f_light = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__HolySpear::meta() const { return &META_Gd__gd_core__HolySpear; }
gd::GdVal Gd__gd_core__HolySpear::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_SpearState_1807: return gd::GdVal::from_enum(&_enum_Gd__gd_core__HolySpear_SpearState);
        default: break;
    }
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__HolySpear::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__HolySpear::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_blockRemoval_1802: out = this->f_blockRemoval; return true;
        case SYM_GEN_cleanses_1803: out = this->f_cleanses; return true;
        case SYM_GEN_spearState_1804: out = this->f_spearState; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_buffTimer_1724: out = this->f_buffTimer; return true;
        case SYM_GEN_blockRemovalPerSlot_1805: out = this->f_blockRemovalPerSlot; return true;
        case SYM_GEN_buffedSpeed_1806: out = this->f_buffedSpeed; return true;
        case SYM_GEN_manaCost_1720: out = this->f_manaCost; return true;
        case SYM_GEN_light_949: out = this->f_light; return true;
        case SYM_GEN_SpearState_1807: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__HolySpear_SpearState); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__HolySpear::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blockRemoval_1802: this->f_blockRemoval = gd::gd_coerce_int(val); return true;
        case SYM_GEN_cleanses_1803: this->f_cleanses = gd::gd_coerce_int(val); return true;
        case SYM_GEN_spearState_1804: this->f_spearState = gd::gd_coerce_int(val); return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_buffTimer_1724: this->f_buffTimer = val; return true;
        case SYM_GEN_blockRemovalPerSlot_1805: this->f_blockRemovalPerSlot = gd::gd_coerce_int(val); return true;
        case SYM_GEN_buffedSpeed_1806: this->f_buffedSpeed = val; return true;
        case SYM_GEN_manaCost_1720: this->f_manaCost = gd::gd_coerce_int(val); return true;
        case SYM_GEN_light_949: this->f_light = val; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__HolySpear::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_affectsEmpty_257: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onPreDealDamage_late_906: return true;
        case SYM_GEN_onInvuEnded_1725: return true;
        case SYM_GEN_checkTrigger_1726: return true;
        case SYM_GEN_buffEnded_1722: return true;
        case SYM_GEN_onCombatEnd_134: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__HolySpear::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_affectsEmpty_257: out = fn_affectsEmpty(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_late_906: out = fn_onPreDealDamage_late(args, argc); return true;
        case SYM_GEN_onInvuEnded_1725: out = fn_onInvuEnded(args, argc); return true;
        case SYM_GEN_checkTrigger_1726: out = fn_checkTrigger(args, argc); return true;
        case SYM_GEN_buffEnded_1722: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_onCombatEnd_134: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__HolySpear::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__HolySpear::fn_affectsEmpty(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolySpear::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Holy_2593)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolySpear::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numSlots = gd::gd_add(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumEmptyAffectedCells_428, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0));
    this->f_blockRemoval = gd::gd_coerce_int(gd::gd_mul(this->f_blockRemovalPerSlot, lv_numSlots));
    this->f_cleanses = gd::gd_coerce_int(lv_numSlots);
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core__HolySpear::get_static_const_or_enum(gd_ctx, SYM_GEN_SpearState_1807), SYM_GEN_Inactive_2594)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_mana_changed", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "checkTrigger", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_invulnerable_end", 26u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onInvuEnded", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolySpear::fn_onPreDealDamage_late(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_blockRemoval}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeBlock_207, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_cleanses}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_358, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolySpear::fn_onInvuEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkTrigger_1726, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolySpear::fn_checkTrigger(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_spearState, gd::get_prop(gd_ctx, Gd__gd_core__HolySpear::get_static_const_or_enum(gd_ctx, SYM_GEN_SpearState_1807), SYM_GEN_Inactive_2594)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_isVulnerable_1275, nullptr, 0))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkMana_333, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core__HolySpear::get_static_const_or_enum(gd_ctx, SYM_GEN_SpearState_1807), SYM_GEN_Active_2595), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 2); })();
        gd::GdVal lv_invuDur = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_invu", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_invuDur, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_makeInvulnerable_1195, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_invuDur}; return gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_start_1685, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_manaCost, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_334, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, this->f_buffedSpeed, gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolySpear::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core__HolySpear::get_static_const_or_enum(gd_ctx, SYM_GEN_SpearState_1807), SYM_GEN_Used_2596), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, this->f_buffedSpeed, gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_reduceSpeed_276, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolySpear::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1686, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolySpear::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core__HolySpear::get_static_const_or_enum(gd_ctx, SYM_GEN_SpearState_1807), SYM_GEN_Inactive_2594)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolySpear::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__spearState = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv__spearState, gd::get_prop(gd_ctx, Gd__gd_core__HolySpear::get_static_const_or_enum(gd_ctx, SYM_GEN_SpearState_1807), SYM_GEN_Inactive_2594))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv__spearState, gd::get_prop(gd_ctx, Gd__gd_core__HolySpear::get_static_const_or_enum(gd_ctx, SYM_GEN_SpearState_1807), SYM_GEN_Active_2595))))) {
    }
    else {
    }
    this->f_spearState = gd::gd_coerce_int(lv__spearState);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolySpear::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_856), SYM_GEN_Normal_2541), gd::GdVal::from_int(2LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolySpear::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "BuffTimer", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffEnded", 9u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_137, _ca, 3); })();
    this->f_blockRemovalPerSlot = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0));
    this->f_buffedSpeed = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0);
    this->f_manaCost = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__HolySpear(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__HolySpear>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__HolySpear = {CLS_Gd__gd_core__HolySpear, "HolySpear", "res://gd_core/HolySpear.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__HolySpear, &Gd__gd_core__HolySpear::get_static_prop_fn, &Gd__gd_core__HolySpear::call_static_fn};

void Gd__gd_core__ManaPotion::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Potion::init_fields(gd_ctx);
    this->f_healthThreshold = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__ManaPotion::meta() const { return &META_Gd__gd_core__ManaPotion; }
gd::GdVal Gd__gd_core__ManaPotion::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Potion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__ManaPotion::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__ManaPotion::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_healthThreshold_1759: out = this->f_healthThreshold; return true;
        default: break;
    }
    return Gd__gd_core__Potion::get_prop(prop, out);
}
bool Gd__gd_core__ManaPotion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_healthThreshold_1759: this->f_healthThreshold = val; return true;
        default: break;
    }
    return Gd__gd_core__Potion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__ManaPotion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1754: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onDamaged_1760: return true;
        case SYM_GEN_onManaChanged_1834: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Potion::has_own_method(m);
}
bool Gd__gd_core__ManaPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1754: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDamaged_1760: out = fn_onDamaged(args, argc); return true;
        case SYM_GEN_onManaChanged_1834: out = fn_onManaChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Potion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__ManaPotion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Potion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__ManaPotion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_319, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ManaPotion::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_mana_changed", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onManaChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_damaged", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDamaged", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ManaPotion::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__healthChange = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_923, nullptr, 0))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_relHealth = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getRelativeHealth_304, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_relHealth, this->f_healthThreshold)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consumePotion_1753, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ManaPotion::fn_onManaChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_923, nullptr, 0))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(gd::call_method(gd_ctx, lv_event, SYM_GEN_getOrigin_1489, nullptr, 0), &META_Gd__gd_core_items__Item)))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::call_method(gd_ctx, lv_event, SYM_GEN_getOrigin_1489, nullptr, 0), SYM_GEN_character_76, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0))))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consumePotion_1753, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ManaPotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Potion::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_healthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__ManaPotion(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__ManaPotion>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__ManaPotion = {CLS_Gd__gd_core__ManaPotion, "ManaPotion", "res://gd_core/ManaPotion.gd", &META_Gd__gd_core__Potion, false, _alloc_Gd__gd_core__ManaPotion, &Gd__gd_core__ManaPotion::get_static_prop_fn, &Gd__gd_core__ManaPotion::call_static_fn};

void Gd__gd_core__PoisonIvy::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_damageIncreaseActive = gd::GdVal::from_bool(false);
    this->f_activationParticles = gd::GdVal::null();
    this->f_poisonPerSpike = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core__PoisonIvy::meta() const { return &META_Gd__gd_core__PoisonIvy; }
gd::GdVal Gd__gd_core__PoisonIvy::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__PoisonIvy::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__PoisonIvy::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_damageIncreaseActive_1868: out = this->f_damageIncreaseActive; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_poisonPerSpike_1869: out = this->f_poisonPerSpike; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__PoisonIvy::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damageIncreaseActive_1868: this->f_damageIncreaseActive = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_poisonPerSpike_1869: this->f_poisonPerSpike = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__PoisonIvy::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onSpikesChanged_944: return true;
        case SYM_GEN_onOpponentPoisonChanged_1736: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__PoisonIvy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onSpikesChanged_944: out = fn_onSpikesChanged(args, argc); return true;
        case SYM_GEN_onOpponentPoisonChanged_1736: out = fn_onOpponentPoisonChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__PoisonIvy::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__PoisonIvy::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Nature_2597)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PoisonIvy::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_spikes_changed", 24u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onSpikesChanged", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_poison_changed", 24u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onOpponentPoisonChanged", 23u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeDebuffResistChances_1204, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PoisonIvy::fn_onSpikesChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, this->f_poisonPerSpike), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_213, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PoisonIvy::fn_onOpponentPoisonChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_curPoison = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_getPoison_1213, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_damageIncreaseActive))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_curPoison, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0))))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_changeDamageResistance_1263, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(false), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PoisonIvy::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PoisonIvy::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv_active)) {
    }
    else {
    }
    this->f_damageIncreaseActive = lv_active;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PoisonIvy::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_poisonPerSpike = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__PoisonIvy(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__PoisonIvy>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__PoisonIvy = {CLS_Gd__gd_core__PoisonIvy, "PoisonIvy", "res://gd_core/PoisonIvy.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__PoisonIvy, &Gd__gd_core__PoisonIvy::get_static_prop_fn, &Gd__gd_core__PoisonIvy::call_static_fn};

void Gd__gd_core__SpikedShield::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Shield::init_fields(gd_ctx);
    this->f_spikesGiven = gd::GdVal::from_int(0);
    this->f_spikes = gd::GdVal::null();
    this->f_maxSpikes = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__SpikedShield::meta() const { return &META_Gd__gd_core__SpikedShield; }
gd::GdVal Gd__gd_core__SpikedShield::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Shield::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__SpikedShield::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__SpikedShield::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_spikesGiven_1887: out = this->f_spikesGiven; return true;
        case SYM_GEN_spikes_898: out = this->f_spikes; return true;
        case SYM_GEN_maxSpikes_1888: out = this->f_maxSpikes; return true;
        default: break;
    }
    return Gd__gd_core__Shield::get_prop(prop, out);
}
bool Gd__gd_core__SpikedShield::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_spikesGiven_1887: this->f_spikesGiven = gd::gd_coerce_int(val); return true;
        case SYM_GEN_spikes_898: this->f_spikes = val; return true;
        case SYM_GEN_maxSpikes_1888: this->f_maxSpikes = val; return true;
        default: break;
    }
    return Gd__gd_core__Shield::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__SpikedShield::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_beforeBlock_1846: return true;
        case SYM_GEN_afterBlock_1847: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Shield::has_own_method(m);
}
bool Gd__gd_core__SpikedShield::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_beforeBlock_1846: out = fn_beforeBlock(args, argc); return true;
        case SYM_GEN_afterBlock_1847: out = fn_afterBlock(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Shield::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__SpikedShield::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Shield::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__SpikedShield::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_spikesGiven = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__SpikedShield::fn_beforeBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Shield::call_method(gd_ctx, SYM_GEN_beforeBlock_1846, nullptr, 0, _out); return _out; })();
    gd::GdVal lv_spikesLeft = gd::gd_sub(this->f_maxSpikes, this->f_spikesGiven);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_spikesLeft, gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_spikesToGive = gd::gd_min(lv_spikesLeft, this->f_spikes);
        this->f_spikesGiven = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_spikesGiven, lv_spikesToGive));
        (void)([&]() { gd::GdVal _ca[] = {lv_spikesToGive}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_211, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__SpikedShield::fn_afterBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0), gd::get_prop(gd_ctx, this->f_blockedDamageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drainStamina_119, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__SpikedShield::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Shield::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_maxSpikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxspikes", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__SpikedShield(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__SpikedShield>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__SpikedShield = {CLS_Gd__gd_core__SpikedShield, "SpikedShield", "res://gd_core/SpikedShield.gd", &META_Gd__gd_core__Shield, false, _alloc_Gd__gd_core__SpikedShield, &Gd__gd_core__SpikedShield::get_static_prop_fn, &Gd__gd_core__SpikedShield::call_static_fn};

void Gd__gd_core__StrongStoneSkinPotion::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__StoneSkinPotion::init_fields(gd_ctx);
    this->f_spikes = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__StrongStoneSkinPotion::meta() const { return &META_Gd__gd_core__StrongStoneSkinPotion; }
gd::GdVal Gd__gd_core__StrongStoneSkinPotion::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__StoneSkinPotion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__StrongStoneSkinPotion::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__StrongStoneSkinPotion::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_spikes_898: out = this->f_spikes; return true;
        default: break;
    }
    return Gd__gd_core_items__StoneSkinPotion::get_prop(prop, out);
}
bool Gd__gd_core__StrongStoneSkinPotion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_spikes_898: this->f_spikes = val; return true;
        default: break;
    }
    return Gd__gd_core_items__StoneSkinPotion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__StrongStoneSkinPotion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1754: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__StoneSkinPotion::has_own_method(m);
}
bool Gd__gd_core__StrongStoneSkinPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1754: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__StoneSkinPotion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__StrongStoneSkinPotion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__StoneSkinPotion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__StrongStoneSkinPotion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_triggerEvent}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__StoneSkinPotion::call_method(gd_ctx, SYM_GEN_onTriggerPotion_1754, _ca, 1, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Spikes_2565), this->f_spikes, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacksTemporary_204, _ca, 5); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StrongStoneSkinPotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__StoneSkinPotion::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__StrongStoneSkinPotion(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__StrongStoneSkinPotion>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__StrongStoneSkinPotion = {CLS_Gd__gd_core__StrongStoneSkinPotion, "StrongStoneSkinPotion", "res://gd_core/StrongStoneSkinPotion.gd", &META_Gd__gd_core_items__StoneSkinPotion, false, _alloc_Gd__gd_core__StrongStoneSkinPotion, &Gd__gd_core__StrongStoneSkinPotion::get_static_prop_fn, &Gd__gd_core__StrongStoneSkinPotion::call_static_fn};

void Gd__gd_core__YggdrasilLeaf::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_manaUsed = gd::GdVal::from_int(0LL);
    this->f_manaNeeded = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__YggdrasilLeaf::meta() const { return &META_Gd__gd_core__YggdrasilLeaf; }
gd::GdVal Gd__gd_core__YggdrasilLeaf::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__YggdrasilLeaf::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__YggdrasilLeaf::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_manaUsed_1912: out = this->f_manaUsed; return true;
        case SYM_GEN_manaNeeded_1786: out = this->f_manaNeeded; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__YggdrasilLeaf::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaUsed_1912: this->f_manaUsed = val; return true;
        case SYM_GEN_manaNeeded_1786: this->f_manaNeeded = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__YggdrasilLeaf::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onManaChanged_1834: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__YggdrasilLeaf::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onManaChanged_1834: out = fn_onManaChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__YggdrasilLeaf::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__YggdrasilLeaf::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Nature_2597)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__YggdrasilLeaf::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_manaUsed = gd::GdVal::from_int(0LL);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_mana_changed", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onManaChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__YggdrasilLeaf::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0), gd::SYM_size, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0), gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0), gd::SYM_size, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__YggdrasilLeaf::fn_onManaChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "used", 4u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, lv_event, SYM_GEN_getParam_1484, _ca, 2); })())) : gd::GdVal::from_bool(false)))) {
        this->f_manaUsed = gd::gd_add(gd_ctx, this->f_manaUsed, gd::gd_neg(lv_amount));
        gd::GdVal lv_activations = gd::gd_div(gd_ctx, this->f_manaUsed, this->f_manaNeeded);
        this->f_manaUsed = gd::gd_mod(gd_ctx, this->f_manaUsed, this->f_manaNeeded);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_activations, gd::GdVal::from_int(1LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), lv_activations), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_269, nullptr, 0), lv_activations), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_358, _ca, 2); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__YggdrasilLeaf::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_manaNeeded = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__YggdrasilLeaf(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__YggdrasilLeaf>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__YggdrasilLeaf = {CLS_Gd__gd_core__YggdrasilLeaf, "YggdrasilLeaf", "res://gd_core/YggdrasilLeaf.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__YggdrasilLeaf, &Gd__gd_core__YggdrasilLeaf::get_static_prop_fn, &Gd__gd_core__YggdrasilLeaf::call_static_fn};

void Gd__gd_core_items__BloodyDagger::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Dagger::init_fields(gd_ctx);
    this->f_vampirismStacks = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core_items__BloodyDagger::meta() const { return &META_Gd__gd_core_items__BloodyDagger; }
gd::GdVal Gd__gd_core_items__BloodyDagger::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Dagger::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__BloodyDagger::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__BloodyDagger::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_vampirismStacks_947: out = this->f_vampirismStacks; return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::get_prop(prop, out);
}
bool Gd__gd_core_items__BloodyDagger::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_vampirismStacks_947: this->f_vampirismStacks = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__BloodyDagger::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::has_own_method(m);
}
bool Gd__gd_core_items__BloodyDagger::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__BloodyDagger::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Dagger::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__BloodyDagger::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Vampiric_2598)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BloodyDagger::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_vampirismStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BloodyDagger::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_vampirismStacks, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_212, _ca, 1); })();
            this->f_vampirismStacks = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_vampirismStacks, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)));
        }
        gd::GdVal lv_numAffected = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numAffected, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_numAffected, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BloodyDagger::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Dagger::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__BloodyDagger(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__BloodyDagger>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__BloodyDagger = {CLS_Gd__gd_core_items__BloodyDagger, "BloodyDagger", "res://gd_core_items/BloodyDagger.gd", &META_Gd__gd_core_items__Dagger, true, _alloc_Gd__gd_core_items__BloodyDagger, &Gd__gd_core_items__BloodyDagger::get_static_prop_fn, &Gd__gd_core_items__BloodyDagger::call_static_fn};

void Gd__gd_core_items__CursedDagger::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Dagger::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__CursedDagger::meta() const { return &META_Gd__gd_core_items__CursedDagger; }
gd::GdVal Gd__gd_core_items__CursedDagger::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Dagger::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__CursedDagger::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__CursedDagger::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Dagger::get_prop(prop, out);
}
bool Gd__gd_core_items__CursedDagger::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Dagger::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__CursedDagger::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_onOpponentDebuffsChanged_1728: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::has_own_method(m);
}
bool Gd__gd_core_items__CursedDagger::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onOpponentDebuffsChanged_1728: out = fn_onOpponentDebuffsChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__CursedDagger::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Dagger::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__CursedDagger::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canDamage_91, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CursedDagger::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onOpponentDebuffsChanged", 24u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToOpponentDebuffs_378, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CursedDagger::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictRandomDebuffs_359, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CursedDagger::fn_onOpponentDebuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_extraCritChance = gd::gd_mul(lv_amount, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0));
    gd::GdVal lv_extraAccuracy = gd::gd_mul(lv_amount, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0));
    (void)([&]() { gd::GdVal _ca[] = {lv_extraCritChance}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addCritChancePercent_181, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_extraAccuracy}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addAccuracy_179, _ca, 1); })();
    {
        gd::GdVal _t371 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t372 = (_t371.kind == gd::GdVal::Kind::Arr) ? _t371.arr : nullptr;
        uint32_t _len__t373 = _t372 ? _t372->len : 0u;
        for (uint32_t _t373 = 0; _t373 < _len__t373; ++_t373) {
            gd::GdVal lv_item = _t372->data[_t373];
            (void)([&]() { gd::GdVal _ca[] = {lv_extraCritChance}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addCritChancePercent_181, _ca, 1); })();
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isWeapon_84, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_extraAccuracy}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addAccuracy_179, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CursedDagger::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Dagger::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__CursedDagger(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__CursedDagger>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__CursedDagger = {CLS_Gd__gd_core_items__CursedDagger, "CursedDagger", "res://gd_core_items/CursedDagger.gd", &META_Gd__gd_core_items__Dagger, true, _alloc_Gd__gd_core_items__CursedDagger, &Gd__gd_core_items__CursedDagger::get_static_prop_fn, &Gd__gd_core_items__CursedDagger::call_static_fn};

void Gd__gd_core_items__Exclusive__AmuletUnidentified::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__AmuletUnidentified::meta() const { return &META_Gd__gd_core_items__Exclusive__AmuletUnidentified; }
gd::GdVal Gd__gd_core_items__Exclusive__AmuletUnidentified::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__AmuletUnidentified::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__AmuletUnidentified::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__AmuletUnidentified::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__AmuletUnidentified::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onDropped_1925: return true;
        case SYM_GEN_identifyAmulet_1926: return true;
        case SYM_GEN_getRelatedItemColumns_699: return true;
        case SYM_GEN_getRelatedItemHeight_700: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__AmuletUnidentified::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onDropped_1925: out = fn_onDropped(args, argc); return true;
        case SYM_GEN_identifyAmulet_1926: out = fn_identifyAmulet(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_699: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN_getRelatedItemHeight_700: out = fn_getRelatedItemHeight(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__AmuletUnidentified::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletUnidentified::fn_onDropped(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_dropRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_dropRes}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core_items__Exclusive__AmuletUnidentified::call_static_fn(gd_ctx, SYM_GEN_wasAddedToInventory_659, _ca, 1, _out); return _out; })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__AmuletUnidentified::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_865), SYM_GEN_AddedToStorageBox_2599)))))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_prepareReplacement_448, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "identifyAmulet", 14u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_dropRes}))}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_defer_1422, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletUnidentified::fn_identifyAmulet(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_dropResult = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletUnidentified::fn_getRelatedItemColumns(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(4LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletUnidentified::fn_getRelatedItemHeight(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(100LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletUnidentified::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dropped", 7u)), gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDropped", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_connect, _ca, 3); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__AmuletUnidentified(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__AmuletUnidentified>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AmuletUnidentified = {CLS_Gd__gd_core_items__Exclusive__AmuletUnidentified, "AmuletUnidentified", "res://gd_core_items/Exclusive/AmuletUnidentified.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__AmuletUnidentified, &Gd__gd_core_items__Exclusive__AmuletUnidentified::get_static_prop_fn, &Gd__gd_core_items__Exclusive__AmuletUnidentified::call_static_fn};

void Gd__gd_core_items__Exclusive__PowerPuppy::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_options = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__PowerPuppy::meta() const { return &META_Gd__gd_core_items__Exclusive__PowerPuppy; }
gd::GdVal Gd__gd_core_items__Exclusive__PowerPuppy::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__PowerPuppy::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__PowerPuppy::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_options_1781: out = this->f_options; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PowerPuppy::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_options_1781: this->f_options = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PowerPuppy::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN_playDropSound_151: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PowerPuppy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_151: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__PowerPuppy::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__PowerPuppy::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PowerPuppy::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PowerPuppy::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Pet_2600)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PowerPuppy::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0)), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    this->f_options = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL), gd::GdVal::from_int(2LL)}));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PowerPuppy::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rng = ([&]() { gd::GdVal _ca[] = {this->f_options}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_pickRandomElement_1650, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_rng, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_rng, gd::GdVal::from_int(1LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_219, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    this->f_options = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL), gd::GdVal::from_int(2LL)}));
    (void)([&]() { gd::GdVal _ca[] = {lv_rng}; return gd::call_method(gd_ctx, this->f_options, gd::SYM_erase, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PowerPuppy::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PowerPuppy(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__PowerPuppy>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PowerPuppy = {CLS_Gd__gd_core_items__Exclusive__PowerPuppy, "PowerPuppy", "res://gd_core_items/Exclusive/PowerPuppy.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__PowerPuppy, &Gd__gd_core_items__Exclusive__PowerPuppy::get_static_prop_fn, &Gd__gd_core_items__Exclusive__PowerPuppy::call_static_fn};

void Gd__gd_core_items__Greatsword::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_buffed = gd::GdVal::from_bool(false);
    this->f_buffParticles = gd::GdVal::null();
    this->f_empowerNeeded = gd::GdVal::null();
    this->f_buffedStamina = gd::GdVal::null();
    this->f_buffedCooldown = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Greatsword::meta() const { return &META_Gd__gd_core_items__Greatsword; }
gd::GdVal Gd__gd_core_items__Greatsword::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Greatsword::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Greatsword::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_buffed_1788: out = this->f_buffed; return true;
        case SYM_GEN_buffParticles_1789: out = this->f_buffParticles; return true;
        case SYM_GEN_empowerNeeded_1790: out = this->f_empowerNeeded; return true;
        case SYM_GEN_buffedStamina_1791: out = this->f_buffedStamina; return true;
        case SYM_GEN_buffedCooldown_1792: out = this->f_buffedCooldown; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Greatsword::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffed_1788: this->f_buffed = val; return true;
        case SYM_GEN_buffParticles_1789: this->f_buffParticles = val; return true;
        case SYM_GEN_empowerNeeded_1790: this->f_empowerNeeded = val; return true;
        case SYM_GEN_buffedStamina_1791: this->f_buffedStamina = val; return true;
        case SYM_GEN_buffedCooldown_1792: this->f_buffedCooldown = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Greatsword::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_isBuffed_1793: return true;
        case SYM_GEN_getStaminaCost_114: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_empowerChanged_1794: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Greatsword::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_isBuffed_1793: out = fn_isBuffed(args, argc); return true;
        case SYM_GEN_getStaminaCost_114: out = fn_getStaminaCost(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_empowerChanged_1794: out = fn_empowerChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Greatsword::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Greatsword::fn_isBuffed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_buffed;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Greatsword::fn_getStaminaCost(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_override = gd::get_index(gd_ctx, this->f_statDisplayOverrides, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_StaminaCost_2547));
    if (gd::gd_truth(lv_override)) {
        return lv_override;
    }
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isBuffed_1793, nullptr, 0))) {
        return gd::gd_mul(this->f_buffedStamina, this->f_staminaFactor);
    }
    else {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN_getStaminaCost_114, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Greatsword::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_empower_changed", 25u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empowerChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Greatsword::fn_empowerChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_buffed))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getEmpower_1232, nullptr, 0), this->f_empowerNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_buffedCooldown}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setBaseCooldown_110, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_StaminaCost_2547)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    }
    else if (gd::gd_truth((gd::gd_truth(this->f_buffed) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getEmpower_1232, nullptr, 0), this->f_empowerNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetBaseCooldown_111, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_StaminaCost_2547)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Greatsword::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Greatsword::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__buffed = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_buffed = lv__buffed;
    if (gd::gd_truth(this->f_buffed)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Greatsword::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_empowerNeeded = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0));
    this->f_buffedStamina = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0);
    this->f_buffedCooldown = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Greatsword(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Greatsword>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Greatsword = {CLS_Gd__gd_core_items__Greatsword, "Greatsword", "res://gd_core_items/Greatsword.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Greatsword, &Gd__gd_core_items__Greatsword::get_static_prop_fn, &Gd__gd_core_items__Greatsword::call_static_fn};

void Gd__gd_core_items__Exclusive__Broccoli::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Food::init_fields(gd_ctx);
    this->f_luck = gd::GdVal::null();
    this->f_luckNeeded = gd::GdVal::null();
    this->f_regen = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Broccoli::meta() const { return &META_Gd__gd_core_items__Exclusive__Broccoli; }
gd::GdVal Gd__gd_core_items__Exclusive__Broccoli::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Broccoli::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Broccoli::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_luckNeeded_1779: out = this->f_luckNeeded; return true;
        case SYM_GEN_regen_1904: out = this->f_regen; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Broccoli::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_luckNeeded_1779: this->f_luckNeeded = val; return true;
        case SYM_GEN_regen_1904: this->f_regen = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Broccoli::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Broccoli::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Broccoli::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Broccoli::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getLucky_1221, nullptr, 0), this->f_luckNeeded)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Broccoli::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_luckNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luckt", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Broccoli(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Broccoli>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Broccoli = {CLS_Gd__gd_core_items__Exclusive__Broccoli, "Broccoli", "res://gd_core_items/Exclusive/Broccoli.gd", &META_Gd__gd_core_items__Food, true, _alloc_Gd__gd_core_items__Exclusive__Broccoli, &Gd__gd_core_items__Exclusive__Broccoli::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Broccoli::call_static_fn};

void Gd__gd_core_items__Exclusive__CheeseGoobert::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Goobert::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__CheeseGoobert::meta() const { return &META_Gd__gd_core_items__Exclusive__CheeseGoobert; }
gd::GdVal Gd__gd_core_items__Exclusive__CheeseGoobert::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__CheeseGoobert::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__CheeseGoobert::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Goobert::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__CheeseGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__CheeseGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__CheeseGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__CheeseGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__CheeseGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_319, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_371, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CheeseGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__CheeseGoobert(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__CheeseGoobert>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__CheeseGoobert = {CLS_Gd__gd_core_items__Exclusive__CheeseGoobert, "CheeseGoobert", "res://gd_core_items/Exclusive/CheeseGoobert.gd", &META_Gd__gd_core_items__Goobert, true, _alloc_Gd__gd_core_items__Exclusive__CheeseGoobert, &Gd__gd_core_items__Exclusive__CheeseGoobert::get_static_prop_fn, &Gd__gd_core_items__Exclusive__CheeseGoobert::call_static_fn};

void Gd__gd_core_items__Exclusive__ChiliGoobert::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Goobert::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ChiliGoobert::meta() const { return &META_Gd__gd_core_items__Exclusive__ChiliGoobert; }
gd::GdVal Gd__gd_core_items__Exclusive__ChiliGoobert::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ChiliGoobert::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ChiliGoobert::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Goobert::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ChiliGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ChiliGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ChiliGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ChiliGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ChiliGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ChiliGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ChiliGoobert(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ChiliGoobert>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ChiliGoobert = {CLS_Gd__gd_core_items__Exclusive__ChiliGoobert, "ChiliGoobert", "res://gd_core_items/Exclusive/ChiliGoobert.gd", &META_Gd__gd_core_items__Goobert, true, _alloc_Gd__gd_core_items__Exclusive__ChiliGoobert, &Gd__gd_core_items__Exclusive__ChiliGoobert::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ChiliGoobert::call_static_fn};

void Gd__gd_core_items__Exclusive__DarkLantern::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_deathPrevented = gd::GdVal::from_bool(false);
    this->f_normalSprite = gd::GdVal::null();
    this->f_invuTimer = gd::GdVal::null();
    this->f_lanternLight = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__DarkLantern::meta() const { return &META_Gd__gd_core_items__Exclusive__DarkLantern; }
gd::GdVal Gd__gd_core_items__Exclusive__DarkLantern::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__DarkLantern::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__DarkLantern::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_deathPrevented_2095: out = this->f_deathPrevented; return true;
        case SYM_GEN_normalSprite_2096: out = this->f_normalSprite; return true;
        case SYM_GEN_invuTimer_2097: out = this->f_invuTimer; return true;
        case SYM_GEN_lanternLight_2098: out = this->f_lanternLight; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DarkLantern::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_deathPrevented_2095: this->f_deathPrevented = val; return true;
        case SYM_GEN_normalSprite_2096: this->f_normalSprite = val; return true;
        case SYM_GEN_invuTimer_2097: this->f_invuTimer = val; return true;
        case SYM_GEN_lanternLight_2098: this->f_lanternLight = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DarkLantern::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_canAffect_secondary_289: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onDamaged_1760: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onReincarnate_2099: return true;
        case SYM_GEN_invuEnded_2100: return true;
        case SYM_GEN_onCombatEnd_134: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DarkLantern::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_289: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDamaged_1760: out = fn_onDamaged(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onReincarnate_2099: out = fn_onReincarnate(args, argc); return true;
        case SYM_GEN_invuEnded_2100: out = fn_invuEnded(args, argc); return true;
        case SYM_GEN_onCombatEnd_134: out = fn_onCombatEnd(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__DarkLantern::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkLantern::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Fire_2601)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkLantern::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Dark_2602)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkLantern::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_damaged", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDamaged", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "reincarnated", 12u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onReincarnate", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkLantern::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(this->f_deathPrevented)) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getCurrentHealth_1138, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
        gd::GdVal lv_duration = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_invu", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_duration}; return gd::call_method(gd_ctx, this->f_invuTimer, SYM_GEN_start_1685, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_duration, gd::GdVal::from_obj(this), lv_event}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_makeInvulnerable_1195, _ca, 3); })();
        gd::GdVal lv_healAmount = gd::gd_round(gd::gd_mul(gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0), gd::GdVal::from_float(100.0)), gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getMaxHealth_1144, nullptr, 0)));
        gd::GdVal lv_event2 = ([&]() { gd::GdVal _ca[] = {lv_healAmount, gd::GdVal::from_bool(false), gd::GdVal::from_obj(this), lv_event}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_reincarnate_1137, _ca, 4); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkLantern::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), gd::GdVal::from_float(100.0)), gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getMaxHealth_1144, nullptr, 0)), gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_loseHealth_1141, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkLantern::fn_onReincarnate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_dam = gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMinDamage_158, nullptr, 0), ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Fire_2601)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffected_type_431, _ca, 1); })());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_dam, gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_damageRes = ([&]() { gd::GdVal _ca[] = {lv_dam, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealEffectDamage_223, _ca, 2); })();
    }
    gd::GdVal lv_numDebuffs = gd::gd_coerce_int(gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_269, nullptr, 0), ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Secondary_2583)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, _ca, 1); })()));
    (void)([&]() { gd::GdVal _ca[] = {lv_numDebuffs, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictRandomDebuffs_359, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkLantern::fn_invuEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkLantern::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_invuTimer, SYM_GEN_stop_1686, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkLantern::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_856), SYM_GEN_High_2603);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkLantern::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkLantern::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__deathPrevented = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv__deathPrevented = gd::gd_coerce_bool(lv__deathPrevented);
    this->f_deathPrevented = lv__deathPrevented;
    if (gd::gd_truth(this->f_deathPrevented)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkLantern::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_invuTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "InvuTimer", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "invuEnded", 9u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_137, _ca, 3); })();
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1459, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__DarkLantern(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__DarkLantern>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DarkLantern = {CLS_Gd__gd_core_items__Exclusive__DarkLantern, "DarkLantern", "res://gd_core_items/Exclusive/DarkLantern.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__DarkLantern, &Gd__gd_core_items__Exclusive__DarkLantern::get_static_prop_fn, &Gd__gd_core_items__Exclusive__DarkLantern::call_static_fn};

void Gd__gd_core_items__Exclusive__DragonscaleArmor::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__DragonscaleArmor::meta() const { return &META_Gd__gd_core_items__Exclusive__DragonscaleArmor; }
gd::GdVal Gd__gd_core_items__Exclusive__DragonscaleArmor::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__DragonscaleArmor::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__DragonscaleArmor::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DragonscaleArmor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DragonscaleArmor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onBattleRageStarted_1971: return true;
        case SYM_GEN_onBattleRageEnded_1972: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DragonscaleArmor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onBattleRageStarted_1971: out = fn_onBattleRageStarted(args, argc); return true;
        case SYM_GEN_onBattleRageEnded_1972: out = fn_onBattleRageEnded(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__DragonscaleArmor::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonscaleArmor::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "battle_rage_started", 19u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBattleRageStarted", 19u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "battle_rage_ended", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBattleRageEnded", 17u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonscaleArmor::fn_onBattleRageStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_206, nullptr, 0), gd::GdVal::from_bool(true), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeDamageResistance_1263, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonscaleArmor::fn_onBattleRageEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeDamageResistance_1263, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonscaleArmor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__DragonscaleArmor(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__DragonscaleArmor>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DragonscaleArmor = {CLS_Gd__gd_core_items__Exclusive__DragonscaleArmor, "DragonscaleArmor", "res://gd_core_items/Exclusive/DragonscaleArmor.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__DragonscaleArmor, &Gd__gd_core_items__Exclusive__DragonscaleArmor::get_static_prop_fn, &Gd__gd_core_items__Exclusive__DragonscaleArmor::call_static_fn};

void Gd__gd_core_items__Exclusive__EvilHat::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_selfBuffs = gd::GdVal::null();
    this->f_opponentBuffs = gd::GdVal::null();
    this->f_regen = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__EvilHat::meta() const { return &META_Gd__gd_core_items__Exclusive__EvilHat; }
gd::GdVal Gd__gd_core_items__Exclusive__EvilHat::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__EvilHat::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__EvilHat::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_selfBuffs_2156: out = this->f_selfBuffs; return true;
        case SYM_GEN_opponentBuffs_2157: out = this->f_opponentBuffs; return true;
        case SYM_GEN_regen_1904: out = this->f_regen; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__EvilHat::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_selfBuffs_2156: this->f_selfBuffs = val; return true;
        case SYM_GEN_opponentBuffs_2157: this->f_opponentBuffs = val; return true;
        case SYM_GEN_regen_1904: this->f_regen = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__EvilHat::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_canAffect_secondary_289: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onDebuffsChanged_1733: return true;
        case SYM_GEN_onOpponentBuffsChanged_2027: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN_playDropSound_151: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__EvilHat::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_289: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDebuffsChanged_1733: out = fn_onDebuffsChanged(args, argc); return true;
        case SYM_GEN_onOpponentBuffsChanged_2027: out = fn_onOpponentBuffsChanged(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_151: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__EvilHat::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__EvilHat::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canDamage_91, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EvilHat::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Dark_2602)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EvilHat::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_unhealing = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "unhealing", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    lv_unhealing = gd::gd_add(gd_ctx, lv_unhealing, gd::gd_div(gd_ctx, gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Secondary_2583)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, _ca, 1); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "unhealing2", 10u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })()), gd::GdVal::from_float(100.0)));
    (void)([&]() { gd::GdVal _ca[] = {lv_unhealing}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_giveUnhealing_1162, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDebuffsChanged", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToCharacterDebuffs_377, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onOpponentBuffsChanged", 22u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToOpponentBuffs_379, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EvilHat::fn_onDebuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(gd::get_prop(gd_ctx, lv_event, SYM_GEN_origin_1455), &META_Gd__gd_core_items__Item)))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_event, SYM_GEN_origin_1455), SYM_GEN_character_76, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0))))) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv_regenToGive = gd::GdVal::from_int(0LL);
        {
            gd::GdVal _t374 = gd::gd_iter_seq(gd_ctx.arena, lv_amount);
            gd::GdArr* _t375 = (_t374.kind == gd::GdVal::Kind::Arr) ? _t374.arr : nullptr;
            uint32_t _len__t376 = _t375 ? _t375->len : 0u;
            for (uint32_t _t376 = 0; _t376 < _len__t376; ++_t376) {
                gd::GdVal lv_i = _t375->data[_t376];
                if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, nullptr, 0))) {
                    lv_regenToGive = gd::gd_add(gd_ctx, lv_regenToGive, this->f_regen);
                }
            }
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_regenToGive, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_regenToGive, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EvilHat::fn_onOpponentBuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(gd::get_prop(gd_ctx, lv_event, SYM_GEN_origin_1455), &META_Gd__gd_core_items__Item)))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_event, SYM_GEN_origin_1455), SYM_GEN_character_76, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0))))) : gd::GdVal::from_bool(false)))) {
        {
            gd::GdVal _t377 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
            gd::GdArr* _t378 = (_t377.kind == gd::GdVal::Kind::Arr) ? _t377.arr : nullptr;
            uint32_t _len__t379 = _t378 ? _t378->len : 0u;
            for (uint32_t _t379 = 0; _t379 < _len__t379; ++_t379) {
                gd::GdVal lv_item = _t378->data[_t379];
                (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_174, nullptr, 0), gd::gd_neg(lv_amount))}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addCritChancePercent_181, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EvilHat::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_selfBuffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_371, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_opponentBuffs, gd::GdVal::null(), gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_371, _ca, 4); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EvilHat::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EvilHat::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EvilHat::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_selfBuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_opponentBuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs2", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__EvilHat(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__EvilHat>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__EvilHat = {CLS_Gd__gd_core_items__Exclusive__EvilHat, "EvilHat", "res://gd_core_items/Exclusive/EvilHat.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__EvilHat, &Gd__gd_core_items__Exclusive__EvilHat::get_static_prop_fn, &Gd__gd_core_items__Exclusive__EvilHat::call_static_fn};

void Gd__gd_core_items__Exclusive__Toad::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_affectedItemsDict = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_gainedBuffs = gd::GdVal::from_int(0);
    this->f_usedBuffs = gd::GdVal::from_int(0);
    this->f_gainedThreshold = gd::GdVal::null();
    this->f_usedThreshold = gd::GdVal::null();
    this->f_luck = gd::GdVal::null();
    this->f_mana = gd::GdVal::null();
    this->f_luck2 = gd::GdVal::null();
    this->f_mana2 = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Toad::meta() const { return &META_Gd__gd_core_items__Exclusive__Toad; }
gd::GdVal Gd__gd_core_items__Exclusive__Toad::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Toad::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Toad::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_affectedItemsDict_2014: out = this->f_affectedItemsDict; return true;
        case SYM_GEN_gainedBuffs_2173: out = this->f_gainedBuffs; return true;
        case SYM_GEN_usedBuffs_2174: out = this->f_usedBuffs; return true;
        case SYM_GEN_gainedThreshold_2175: out = this->f_gainedThreshold; return true;
        case SYM_GEN_usedThreshold_2176: out = this->f_usedThreshold; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_mana_1833: out = this->f_mana; return true;
        case SYM_GEN_luck2_2177: out = this->f_luck2; return true;
        case SYM_GEN_mana2_2178: out = this->f_mana2; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Toad::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedItemsDict_2014: this->f_affectedItemsDict = val; return true;
        case SYM_GEN_gainedBuffs_2173: this->f_gainedBuffs = gd::gd_coerce_int(val); return true;
        case SYM_GEN_usedBuffs_2174: this->f_usedBuffs = gd::gd_coerce_int(val); return true;
        case SYM_GEN_gainedThreshold_2175: this->f_gainedThreshold = val; return true;
        case SYM_GEN_usedThreshold_2176: this->f_usedThreshold = val; return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_mana_1833: this->f_mana = val; return true;
        case SYM_GEN_luck2_2177: this->f_luck2 = val; return true;
        case SYM_GEN_mana2_2178: this->f_mana2 = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Toad::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onGainThresholdReached_2179: return true;
        case SYM_GEN_onUseThresholdReached_2180: return true;
        case SYM_GEN_onBuffsChanged_1992: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN_playDropSound_151: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Toad::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onGainThresholdReached_2179: out = fn_onGainThresholdReached(args, argc); return true;
        case SYM_GEN_onUseThresholdReached_2180: out = fn_onUseThresholdReached(args, argc); return true;
        case SYM_GEN_onBuffsChanged_1992: out = fn_onBuffsChanged(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_151: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Toad::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Toad::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_gainsBuffs_298, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_usesBuffs_299, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Toad::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_affectedItemsDict = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_arrayAsIndexDict_1704, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBuffsChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToCharacterBuffs_376, _ca, 1); })();
    this->f_gainedBuffs = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_usedBuffs = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Toad::fn_onGainThresholdReached(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_ticks = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_ticks, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })()), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Toad::fn_onUseThresholdReached(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_ticks = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_ticks, this->f_luck), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_ticks, this->f_mana), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Toad::fn_onBuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::gd_in(gd::call_method(gd_ctx, lv_event, SYM_GEN_getOrigin_1489, nullptr, 0), this->f_affectedItemsDict))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
            this->f_gainedBuffs = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_gainedBuffs, lv_amount));
            gd::GdVal lv_ticks = gd::gd_div(gd_ctx, this->f_gainedBuffs, this->f_gainedThreshold);
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_ticks, gd::GdVal::from_int(0LL))))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_ticks, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onGainThresholdReached_2179, _ca, 2); })();
                this->f_gainedBuffs = gd::gd_coerce_int(gd::gd_mod(gd_ctx, this->f_gainedBuffs, this->f_gainedThreshold));
            }
        }
        else {
            this->f_usedBuffs = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_usedBuffs, gd::gd_coerce_int(gd::gd_abs(lv_amount))));
            gd::GdVal lv_ticks = gd::gd_div(gd_ctx, this->f_usedBuffs, this->f_usedThreshold);
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_ticks, gd::GdVal::from_int(0LL))))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_ticks, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onUseThresholdReached_2180, _ca, 2); })();
                this->f_usedBuffs = gd::gd_coerce_int(gd::gd_mod(gd_ctx, this->f_usedBuffs, this->f_usedThreshold));
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Toad::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_luck2}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_mana2}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Toad::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Toad::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Toad::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_gainedThreshold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gained", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_usedThreshold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "used", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_luck2 = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck2", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_mana2 = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana2", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Toad(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Toad>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Toad = {CLS_Gd__gd_core_items__Exclusive__Toad, "Toad", "res://gd_core_items/Exclusive/Toad.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Toad, &Gd__gd_core_items__Exclusive__Toad::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Toad::call_static_fn};

void Gd__gd_core_items__Exclusive__HawkRune::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Gems__Gem::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__HawkRune::meta() const { return &META_Gd__gd_core_items__Exclusive__HawkRune; }
gd::GdVal Gd__gd_core_items__Exclusive__HawkRune::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_gemColor_995: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.267323), gd::GdVal::from_float(0.624508), gd::GdVal::from_float(0.970703)}; return gd::make_color_from_args(_ca, 3); })();
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__HawkRune::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__HawkRune::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_gemColor_995: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__HawkRune::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__HawkRune::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_prepareWeapon_982: return true;
        case SYM_GEN_prepareArmor_983: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_992: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__HawkRune::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_prepareWeapon_982: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_prepareArmor_983: out = fn_prepareArmor(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_992: out = fn_onHotSwapHoverWithGemEnd(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__HawkRune::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Gems__Gem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__HawkRune::fn_prepareWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "critchance", 10u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_391, nullptr, 0), SYM_GEN_addCritChancePercent_181, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "critdam", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_391, nullptr, 0), SYM_GEN_addCritSeverity_187, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HawkRune::fn_prepareArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Blind_2568), gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeResistChance_1025, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HawkRune::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_215, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HawkRune::fn_onHotSwapHoverWithGemEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HawkRune::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__HawkRune(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__HawkRune>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__HawkRune = {CLS_Gd__gd_core_items__Exclusive__HawkRune, "HawkRune", "res://gd_core_items/Exclusive/HawkRune.gd", &META_Gd__gd_core_items__Gems__Gem, true, _alloc_Gd__gd_core_items__Exclusive__HawkRune, &Gd__gd_core_items__Exclusive__HawkRune::get_static_prop_fn, &Gd__gd_core_items__Exclusive__HawkRune::call_static_fn};

void Gd__gd_core_items__Exclusive__InvestmentOpportunity::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_affectedItemsDict = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_healthAcc = gd::GdVal::from_float(0.0);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__InvestmentOpportunity::meta() const { return &META_Gd__gd_core_items__Exclusive__InvestmentOpportunity; }
gd::GdVal Gd__gd_core_items__Exclusive__InvestmentOpportunity::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__InvestmentOpportunity::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__InvestmentOpportunity::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_affectedItemsDict_2014: out = this->f_affectedItemsDict; return true;
        case SYM_GEN_healthAcc_2229: out = this->f_healthAcc; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__InvestmentOpportunity::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedItemsDict_2014: this->f_affectedItemsDict = val; return true;
        case SYM_GEN_healthAcc_2229: this->f_healthAcc = gd::gd_coerce_float(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__InvestmentOpportunity::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onBuffChanged_1911: return true;
        case SYM_GEN_getShopPriority_853: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__InvestmentOpportunity::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onBuffChanged_1911: out = fn_onBuffChanged(args, argc); return true;
        case SYM_GEN_getShopPriority_853: out = fn_getShopPriority(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__InvestmentOpportunity::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__InvestmentOpportunity::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveGold_754, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__InvestmentOpportunity::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_usesBuffs_299, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__InvestmentOpportunity::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_healthAcc = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    (void)gd::call_method(gd_ctx, this->f_affectedItemsDict, gd::SYM_clear, nullptr, 0);
    {
        gd::GdVal _t380 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t381 = (_t380.kind == gd::GdVal::Kind::Arr) ? _t380.arr : nullptr;
        uint32_t _len__t382 = _t381 ? _t381->len : 0u;
        for (uint32_t _t382 = 0; _t382 < _len__t382; ++_t382) {
            gd::GdVal lv_item = _t381->data[_t382];
            { gd::GdVal _t383 = this->f_affectedItemsDict; gd::GdVal _t384 = lv_item; gd::set_index(gd_ctx, _t383, _t384, gd::GdVal::from_bool(true)); }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBuffChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToCharacterBuffs_376, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__InvestmentOpportunity::fn_onBuffChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::gd_in(gd::call_method(gd_ctx, lv_event, SYM_GEN_getOrigin_1489, nullptr, 0), this->f_affectedItemsDict))) {
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "used", 4u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, lv_event, SYM_GEN_getParam_1484, _ca, 2); })())) : gd::GdVal::from_bool(false)))) {
            this->f_healthAcc = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_healthAcc, gd::gd_mul(gd::gd_abs(lv_amount), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })())));
            gd::GdVal lv_health = gd::gd_round(this->f_healthAcc);
            this->f_healthAcc = gd::gd_coerce_float(gd::gd_sub(this->f_healthAcc, lv_health));
            (void)([&]() { gd::GdVal _ca[] = {lv_health, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_319, _ca, 2); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__InvestmentOpportunity::fn_getShopPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_856), SYM_GEN_Lowest_2604);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__InvestmentOpportunity::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__InvestmentOpportunity(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__InvestmentOpportunity>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__InvestmentOpportunity = {CLS_Gd__gd_core_items__Exclusive__InvestmentOpportunity, "InvestmentOpportunity", "res://gd_core_items/Exclusive/InvestmentOpportunity.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__InvestmentOpportunity, &Gd__gd_core_items__Exclusive__InvestmentOpportunity::get_static_prop_fn, &Gd__gd_core_items__Exclusive__InvestmentOpportunity::call_static_fn};

void Gd__gd_core_items__Exclusive__LittleMimic::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_numBuffs = gd::GdVal::null();
    this->f_speedPerGold = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__LittleMimic::meta() const { return &META_Gd__gd_core_items__Exclusive__LittleMimic; }
gd::GdVal Gd__gd_core_items__Exclusive__LittleMimic::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__LittleMimic::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__LittleMimic::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_numBuffs_1910: out = this->f_numBuffs; return true;
        case SYM_GEN_speedPerGold_2255: out = this->f_speedPerGold; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__LittleMimic::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numBuffs_1910: this->f_numBuffs = val; return true;
        case SYM_GEN_speedPerGold_2255: this->f_speedPerGold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__LittleMimic::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_getCounterValue_2256: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onCalcTradeChance_1730: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__LittleMimic::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_getCounterValue_2256: out = fn_getCounterValue(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onCalcTradeChance_1730: out = fn_onCalcTradeChance(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__LittleMimic::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__LittleMimic::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LittleMimic::fn_getCounterValue(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_gold = gd::GdVal::from_int(0LL);
    if (gd::gd_truth(this->f_placed)) {
        {
            gd::GdVal _t385 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
            gd::GdArr* _t386 = (_t385.kind == gd::GdVal::Kind::Arr) ? _t385.arr : nullptr;
            uint32_t _len__t387 = _t386 ? _t386->len : 0u;
            for (uint32_t _t387 = 0; _t387 < _len__t387; ++_t387) {
                gd::GdVal lv_item = _t386->data[_t387];
                lv_gold = gd::gd_add(gd_ctx, lv_gold, gd::call_method(gd_ctx, lv_item, SYM_GEN_getPrice_394, nullptr, 0));
            }
        }
    }
    else {
        {
            gd::GdVal _t388 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_nocache_423, nullptr, 0));
            gd::GdArr* _t389 = (_t388.kind == gd::GdVal::Kind::Arr) ? _t388.arr : nullptr;
            uint32_t _len__t390 = _t389 ? _t389->len : 0u;
            for (uint32_t _t390 = 0; _t390 < _len__t390; ++_t390) {
                gd::GdVal lv_item = _t389->data[_t390];
                lv_gold = gd::gd_add(gd_ctx, lv_gold, gd::call_method(gd_ctx, lv_item, SYM_GEN_getPrice_394, nullptr, 0));
            }
        }
    }
    return lv_gold;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LittleMimic::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCounterValue_2256, nullptr, 0), this->f_speedPerGold)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LittleMimic::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_numBuffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMostBuffs_369, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LittleMimic::fn_onCalcTradeChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LittleMimic::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_numBuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_speedPerGold = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__LittleMimic(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__LittleMimic>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__LittleMimic = {CLS_Gd__gd_core_items__Exclusive__LittleMimic, "LittleMimic", "res://gd_core_items/Exclusive/LittleMimic.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__LittleMimic, &Gd__gd_core_items__Exclusive__LittleMimic::get_static_prop_fn, &Gd__gd_core_items__Exclusive__LittleMimic::call_static_fn};

void Gd__gd_core_items__Exclusive__MechaBat::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_lifestealActive = gd::GdVal::from_bool(false);
    this->f_lifestealParticles = gd::GdVal::null();
    this->f_lifestealLight = gd::GdVal::null();
    this->f_vampirism1 = gd::GdVal::null();
    this->f_luckNeeded = gd::GdVal::null();
    this->f_luckUsed = gd::GdVal::null();
    this->f_vampirism2 = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__MechaBat::meta() const { return &META_Gd__gd_core_items__Exclusive__MechaBat; }
gd::GdVal Gd__gd_core_items__Exclusive__MechaBat::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__MechaBat::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__MechaBat::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_lifestealActive_2302: out = this->f_lifestealActive; return true;
        case SYM_GEN_lifestealParticles_2303: out = this->f_lifestealParticles; return true;
        case SYM_GEN_lifestealLight_2304: out = this->f_lifestealLight; return true;
        case SYM_GEN_vampirism1_2305: out = this->f_vampirism1; return true;
        case SYM_GEN_luckNeeded_1779: out = this->f_luckNeeded; return true;
        case SYM_GEN_luckUsed_2306: out = this->f_luckUsed; return true;
        case SYM_GEN_vampirism2_2307: out = this->f_vampirism2; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MechaBat::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_lifestealActive_2302: this->f_lifestealActive = val; return true;
        case SYM_GEN_lifestealParticles_2303: this->f_lifestealParticles = val; return true;
        case SYM_GEN_lifestealLight_2304: this->f_lifestealLight = val; return true;
        case SYM_GEN_vampirism1_2305: this->f_vampirism1 = val; return true;
        case SYM_GEN_luckNeeded_1779: this->f_luckNeeded = val; return true;
        case SYM_GEN_luckUsed_2306: this->f_luckUsed = val; return true;
        case SYM_GEN_vampirism2_2307: this->f_vampirism2 = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MechaBat::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onOpponentDamaged_1897: return true;
        case SYM_GEN_onChargeReceived_2035: return true;
        case SYM_GEN_onChargeLeft_2036: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MechaBat::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onOpponentDamaged_1897: out = fn_onOpponentDamaged(args, argc); return true;
        case SYM_GEN_onChargeReceived_2035: out = fn_onChargeReceived(args, argc); return true;
        case SYM_GEN_onChargeLeft_2036: out = fn_onChargeLeft(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__MechaBat::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__MechaBat::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canDamage_91, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MechaBat::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numVamp = gd::GdVal::from_int(0LL);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getLucky_1221, nullptr, 0), this->f_luckNeeded)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_luckUsed}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useLucky_352, _ca, 1); })();
        lv_numVamp = gd::gd_add(gd_ctx, lv_numVamp, this->f_vampirism2);
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_118, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StaminaResult_1280), SYM_GEN_Sufficient_2605))))) {
        lv_numVamp = gd::gd_add(gd_ctx, lv_numVamp, this->f_vampirism1);
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numVamp, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_numVamp}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_212, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MechaBat::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_attacked", 18u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onOpponentDamaged", 17u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MechaBat::fn_onOpponentDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(this->f_lifestealActive)) {
        if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_canApplyLifesteal_1472, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
            if (gd::gd_truth(gd::gd_in(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_origin_1455), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0)))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::gd_ceil(gd::gd_div(gd_ctx, gd::gd_mul(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lifesteal", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })()), gd::GdVal::from_float(100.0))), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, _ca, 2); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MechaBat::fn_onChargeReceived(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_numCharges, gd::GdVal::from_int(1LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MechaBat::fn_onChargeLeft(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_numCharges, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MechaBat::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MechaBat::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__lifestealActive = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_lifestealActive = lv__lifestealActive;
    if (gd::gd_truth(this->f_lifestealActive)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MechaBat::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_vampirism1 = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "vampirism", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_luckNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luckt", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_luckUsed = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_vampirism2 = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "vampirism2", 10u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__MechaBat(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__MechaBat>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MechaBat = {CLS_Gd__gd_core_items__Exclusive__MechaBat, "MechaBat", "res://gd_core_items/Exclusive/MechaBat.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__MechaBat, &Gd__gd_core_items__Exclusive__MechaBat::get_static_prop_fn, &Gd__gd_core_items__Exclusive__MechaBat::call_static_fn};

void Gd__gd_core_items__Exclusive__OnionCutter::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_foodSpeed = gd::GdVal::null();
    this->f_damFactor = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__OnionCutter::meta() const { return &META_Gd__gd_core_items__Exclusive__OnionCutter; }
gd::GdVal Gd__gd_core_items__Exclusive__OnionCutter::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__OnionCutter::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__OnionCutter::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_foodSpeed_1935: out = this->f_foodSpeed; return true;
        case SYM_GEN_damFactor_1800: out = this->f_damFactor; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__OnionCutter::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_foodSpeed_1935: this->f_foodSpeed = val; return true;
        case SYM_GEN_damFactor_1800: this->f_damFactor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__OnionCutter::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__OnionCutter::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__OnionCutter::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__OnionCutter::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Food_2606)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__OnionCutter::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_foodSpeed, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__OnionCutter::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damFactor)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_changeDamageResistance_1263, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__OnionCutter::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_foodSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_damFactor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__OnionCutter(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__OnionCutter>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__OnionCutter = {CLS_Gd__gd_core_items__Exclusive__OnionCutter, "OnionCutter", "res://gd_core_items/Exclusive/OnionCutter.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__OnionCutter, &Gd__gd_core_items__Exclusive__OnionCutter::get_static_prop_fn, &Gd__gd_core_items__Exclusive__OnionCutter::call_static_fn};

void Gd__gd_core_items__Exclusive__PortableAltar::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Bag::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__PortableAltar::meta() const { return &META_Gd__gd_core_items__Exclusive__PortableAltar; }
gd::GdVal Gd__gd_core_items__Exclusive__PortableAltar::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_valueFactor_2339: return gd::GdVal::from_float(1.0);
        default: break;
    }
    return Gd__gd_core_items__Bag::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__PortableAltar::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__PortableAltar::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_valueFactor_2339: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PortableAltar::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PortableAltar::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canLockBag_820: return true;
        case SYM_GEN_showBagBorderForItem_919: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onRecipesUpdated_2340: return true;
        case SYM_GEN_readyToFuse_751: return true;
        case SYM_GEN_onFusingFinished_848: return true;
        case SYM_GEN_getCounterValue_2256: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PortableAltar::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canLockBag_820: out = fn_canLockBag(args, argc); return true;
        case SYM_GEN_showBagBorderForItem_919: out = fn_showBagBorderForItem(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onRecipesUpdated_2340: out = fn_onRecipesUpdated(args, argc); return true;
        case SYM_GEN_readyToFuse_751: out = fn_readyToFuse(args, argc); return true;
        case SYM_GEN_onFusingFinished_848: out = fn_onFusingFinished(args, argc); return true;
        case SYM_GEN_getCounterValue_2256: out = fn_getCounterValue(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__PortableAltar::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__PortableAltar::fn_canLockBag(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PortableAltar::fn_showBagBorderForItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isBag_85, nullptr, 0)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PortableAltar::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_219, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PortableAltar::fn_onRecipesUpdated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_PlayerInventory_2555))))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(this->f_fusing)) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth((gd::gd_truth(this->f_locked) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_placed))))))) {
        {
            gd::GdVal _t391 = gd::gd_iter_seq(gd_ctx.arena, this->f_bondedIngredients);
            gd::GdArr* _t392 = (_t391.kind == gd::GdVal::Kind::Arr) ? _t391.arr : nullptr;
            uint32_t _len__t393 = _t392 ? _t392->len : 0u;
            for (uint32_t _t393 = 0; _t393 < _len__t393; ++_t393) {
                gd::GdVal lv_bonded = _t392->data[_t393];
                (void)gd::call_method(gd_ctx, lv_bonded, SYM_GEN_removeBondedBaseItem_810, nullptr, 0);
            }
        }
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeAllIngredients_812, nullptr, 0);
        return gd::GdVal::null();
    }
    {
        gd::GdVal _t394 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0));
        gd::GdArr* _t395 = (_t394.kind == gd::GdVal::Kind::Arr) ? _t394.arr : nullptr;
        uint32_t _len__t396 = _t395 ? _t395->len : 0u;
        for (uint32_t _t396 = 0; _t396 < _len__t396; ++_t396) {
            gd::GdVal lv_item = _t395->data[_t396];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canStartNewRecipe_807, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createBondVisual_839, _ca, 1); })();
                (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateBondVisuals_840, nullptr, 0);
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addToBaseItem_815, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PortableAltar::fn_readyToFuse(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, this->f_bondedIngredients, gd::SYM_empty, nullptr, 0)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PortableAltar::fn_onFusingFinished(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_validBonds = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_validBonds}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN_onFusingFinished_848, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PortableAltar::fn_getCounterValue(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_gold = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t397 = gd::gd_iter_seq(gd_ctx.arena, this->f_bondedIngredients);
        gd::GdArr* _t398 = (_t397.kind == gd::GdVal::Kind::Arr) ? _t397.arr : nullptr;
        uint32_t _len__t399 = _t398 ? _t398->len : 0u;
        for (uint32_t _t399 = 0; _t399 < _len__t399; ++_t399) {
            gd::GdVal lv_item = _t398->data[_t399];
            lv_gold = gd::gd_add(gd_ctx, lv_gold, gd::call_method(gd_ctx, lv_item, SYM_GEN_getPrice_394, nullptr, 0));
        }
    }
    return lv_gold;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PortableAltar::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PortableAltar(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__PortableAltar>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PortableAltar = {CLS_Gd__gd_core_items__Exclusive__PortableAltar, "PortableAltar", "res://gd_core_items/Exclusive/PortableAltar.gd", &META_Gd__gd_core_items__Bag, true, _alloc_Gd__gd_core_items__Exclusive__PortableAltar, &Gd__gd_core_items__Exclusive__PortableAltar::get_static_prop_fn, &Gd__gd_core_items__Exclusive__PortableAltar::call_static_fn};

void Gd__gd_core_items__Exclusive__RainbowGoobertMage::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Goobert::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__RainbowGoobertMage::meta() const { return &META_Gd__gd_core_items__Exclusive__RainbowGoobertMage; }
gd::GdVal Gd__gd_core_items__Exclusive__RainbowGoobertMage::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertMage::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertMage::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Goobert::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertMage::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertMage::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertMage::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertMage::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowGoobertMage::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_212, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMostBuffs_369, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_269, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_215, _ca, 1); })();
    {
        gd::GdVal _t400 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t401 = (_t400.kind == gd::GdVal::Kind::Arr) ? _t400.arr : nullptr;
        uint32_t _len__t402 = _t401 ? _t401->len : 0u;
        for (uint32_t _t402 = 0; _t402 < _len__t402; ++_t402) {
            gd::GdVal lv_item = _t401->data[_t402];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_92, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP6_270, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_163, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowGoobertMage::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__RainbowGoobertMage(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__RainbowGoobertMage>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__RainbowGoobertMage = {CLS_Gd__gd_core_items__Exclusive__RainbowGoobertMage, "RainbowGoobertMage", "res://gd_core_items/Exclusive/RainbowGoobertMage.gd", &META_Gd__gd_core_items__Goobert, true, _alloc_Gd__gd_core_items__Exclusive__RainbowGoobertMage, &Gd__gd_core_items__Exclusive__RainbowGoobertMage::get_static_prop_fn, &Gd__gd_core_items__Exclusive__RainbowGoobertMage::call_static_fn};

void Gd__gd_core_items__Exclusive__SapphireWhelp::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_stackTypes = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SapphireWhelp::meta() const { return &META_Gd__gd_core_items__Exclusive__SapphireWhelp; }
gd::GdVal Gd__gd_core_items__Exclusive__SapphireWhelp::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SapphireWhelp::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SapphireWhelp::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_stackTypes_1831: out = this->f_stackTypes; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SapphireWhelp::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_stackTypes_1831: this->f_stackTypes = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SapphireWhelp::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SapphireWhelp::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SapphireWhelp::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SapphireWhelp::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SapphireWhelp::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseMana_335, _ca, 1); })();
        if (gd::gd_truth(lv_event)) {
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_206, nullptr, 0), gd::GdVal::from_bool(true), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, _ca, 3); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), lv_event, this->f_stackTypes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_371, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SapphireWhelp::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_stackTypes = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Mana_2571)}; return gd::call_method(gd_ctx, this->f_stackTypes, gd::SYM_erase, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SapphireWhelp(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SapphireWhelp>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SapphireWhelp = {CLS_Gd__gd_core_items__Exclusive__SapphireWhelp, "SapphireWhelp", "res://gd_core_items/Exclusive/SapphireWhelp.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__SapphireWhelp, &Gd__gd_core_items__Exclusive__SapphireWhelp::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SapphireWhelp::call_static_fn};

void Gd__gd_core_items__Exclusive__SliceofToast::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Food::init_fields(gd_ctx);
    this->f_staminaThreshold = gd::GdVal::null();
    this->f_stamina = gd::GdVal::null();
    this->f_regen = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SliceofToast::meta() const { return &META_Gd__gd_core_items__Exclusive__SliceofToast; }
gd::GdVal Gd__gd_core_items__Exclusive__SliceofToast::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SliceofToast::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SliceofToast::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_staminaThreshold_1980: out = this->f_staminaThreshold; return true;
        case SYM_GEN_stamina_2060: out = this->f_stamina; return true;
        case SYM_GEN_regen_1904: out = this->f_regen; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SliceofToast::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_staminaThreshold_1980: this->f_staminaThreshold = val; return true;
        case SYM_GEN_stamina_2060: this->f_stamina = val; return true;
        case SYM_GEN_regen_1904: this->f_regen = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SliceofToast::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SliceofToast::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SliceofToast::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SliceofToast::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getCurrentStamina_1246, nullptr, 0), this->f_staminaThreshold)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_stamina}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_320, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SliceofToast::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_staminaThreshold = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "staminat", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_stamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SliceofToast(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SliceofToast>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SliceofToast = {CLS_Gd__gd_core_items__Exclusive__SliceofToast, "SliceofToast", "res://gd_core_items/Exclusive/SliceofToast.gd", &META_Gd__gd_core_items__Food, true, _alloc_Gd__gd_core_items__Exclusive__SliceofToast, &Gd__gd_core_items__Exclusive__SliceofToast::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SliceofToast::call_static_fn};

void Gd__gd_core_items__Exclusive__SpellScrollLight::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_speedBonus = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SpellScrollLight::meta() const { return &META_Gd__gd_core_items__Exclusive__SpellScrollLight; }
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollLight::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SpellScrollLight::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SpellScrollLight::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_speedBonus_1782: out = this->f_speedBonus; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SpellScrollLight::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_speedBonus_1782: this->f_speedBonus = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SpellScrollLight::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SpellScrollLight::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SpellScrollLight::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollLight::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Holy_2593)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollLight::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_speedBonus, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollLight::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_358, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getDebuffStacks_1200, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, nullptr, 0);
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollLight::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_speedBonus = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SpellScrollLight(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SpellScrollLight>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpellScrollLight = {CLS_Gd__gd_core_items__Exclusive__SpellScrollLight, "SpellScrollLight", "res://gd_core_items/Exclusive/SpellScrollLight.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__SpellScrollLight, &Gd__gd_core_items__Exclusive__SpellScrollLight::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SpellScrollLight::call_static_fn};

void Gd__gd_core_items__Exclusive__StoneGloves::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_speedReduction = gd::GdVal::null();
    this->f_damBonusFactor = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__StoneGloves::meta() const { return &META_Gd__gd_core_items__Exclusive__StoneGloves; }
gd::GdVal Gd__gd_core_items__Exclusive__StoneGloves::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__StoneGloves::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__StoneGloves::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_speedReduction_2457: out = this->f_speedReduction; return true;
        case SYM_GEN_damBonusFactor_2374: out = this->f_damBonusFactor; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__StoneGloves::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_speedReduction_2457: this->f_speedReduction = val; return true;
        case SYM_GEN_damBonusFactor_2374: this->f_damBonusFactor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__StoneGloves::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onWeaponAttacked_950: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__StoneGloves::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onWeaponAttacked_950: out = fn_onWeaponAttacked(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__StoneGloves::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGloves::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_92, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGloves::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t403 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t404 = (_t403.kind == gd::GdVal::Kind::Arr) ? _t403.arr : nullptr;
        uint32_t _len__t405 = _t404 ? _t404->len : 0u;
        for (uint32_t _t405 = 0; _t405 < _len__t405; ++_t405) {
            gd::GdVal lv_weapon = _t404->data[_t405];
            (void)([&]() { gd::GdVal _ca[] = {lv_weapon, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attacked", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onWeaponAttacked", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGloves::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t406 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t407 = (_t406.kind == gd::GdVal::Kind::Arr) ? _t406.arr : nullptr;
        uint32_t _len__t408 = _t407 ? _t407->len : 0u;
        for (uint32_t _t408 = 0; _t408 < _len__t408; ++_t408) {
            gd::GdVal lv_item = _t407->data[_t408];
            (void)([&]() { gd::GdVal _ca[] = {this->f_speedReduction}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_reduceSpeed_276, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_damBonusFactor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamageFactor_308, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGloves::fn_onWeaponAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_206, nullptr, 0), gd::GdVal::from_bool(true), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, _ca, 3); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneGloves::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_speedReduction = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speedreduction", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_damBonusFactor = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dambonus", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__StoneGloves(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__StoneGloves>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__StoneGloves = {CLS_Gd__gd_core_items__Exclusive__StoneGloves, "StoneGloves", "res://gd_core_items/Exclusive/StoneGloves.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__StoneGloves, &Gd__gd_core_items__Exclusive__StoneGloves::get_static_prop_fn, &Gd__gd_core_items__Exclusive__StoneGloves::call_static_fn};

void Gd__gd_core_items__Exclusive__TigerRune::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Gems__Gem::init_fields(gd_ctx);
    this->f_buffCounter = gd::GdVal::from_int(0LL);
    this->f_vampChance = gd::GdVal::null();
    this->f_vampirism = gd::GdVal::null();
    this->f_buffsNeeded = gd::GdVal::null();
    this->f_blockForBuffs = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__TigerRune::meta() const { return &META_Gd__gd_core_items__Exclusive__TigerRune; }
gd::GdVal Gd__gd_core_items__Exclusive__TigerRune::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_gemColor_995: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(3LL), gd::GdVal::from_float(2.501563), gd::GdVal::from_float(0.8)}; return gd::make_color_from_args(_ca, 3); })();
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__TigerRune::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__TigerRune::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_buffCounter_1988: out = this->f_buffCounter; return true;
        case SYM_GEN_vampChance_2496: out = this->f_vampChance; return true;
        case SYM_GEN_vampirism_940: out = this->f_vampirism; return true;
        case SYM_GEN_buffsNeeded_1990: out = this->f_buffsNeeded; return true;
        case SYM_GEN_blockForBuffs_2497: out = this->f_blockForBuffs; return true;
        case SYM_GEN_gemColor_995: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__TigerRune::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffCounter_1988: this->f_buffCounter = val; return true;
        case SYM_GEN_vampChance_2496: this->f_vampChance = val; return true;
        case SYM_GEN_vampirism_940: this->f_vampirism = val; return true;
        case SYM_GEN_buffsNeeded_1990: this->f_buffsNeeded = val; return true;
        case SYM_GEN_blockForBuffs_2497: this->f_blockForBuffs = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__TigerRune::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canModifyChance_295: return true;
        case SYM_GEN_prepareInventory_981: return true;
        case SYM_GEN_prepareWeapon_982: return true;
        case SYM_GEN_preAttack_996: return true;
        case SYM_GEN_prepareArmor_983: return true;
        case SYM_GEN_onBuffsChanged_1992: return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_992: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__TigerRune::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canModifyChance_295: out = fn_canModifyChance(args, argc); return true;
        case SYM_GEN_prepareInventory_981: out = fn_prepareInventory(args, argc); return true;
        case SYM_GEN_prepareWeapon_982: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_preAttack_996: out = fn_preAttack(args, argc); return true;
        case SYM_GEN_prepareArmor_983: out = fn_prepareArmor(args, argc); return true;
        case SYM_GEN_onBuffsChanged_1992: out = fn_onBuffsChanged(args, argc); return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_992: out = fn_onHotSwapHoverWithGemEnd(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__TigerRune::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Gems__Gem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__TigerRune::fn_canModifyChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TigerRune::fn_prepareInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t409 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItemsAndGems_1513, nullptr, 0));
        gd::GdArr* _t410 = (_t409.kind == gd::GdVal::Kind::Arr) ? _t409.arr : nullptr;
        uint32_t _len__t411 = _t410 ? _t410->len : 0u;
        for (uint32_t _t411 = 0; _t411 < _len__t411; ++_t411) {
            gd::GdVal lv_item = _t410->data[_t411];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_allBuffs_199, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TigerRune::fn_prepareWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_391, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "pre_deal_damage_late", 20u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "preAttack", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TigerRune::fn_preAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_vampChance}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_vampirism}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_212, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TigerRune::fn_prepareArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_buffCounter = gd::GdVal::from_int(0LL);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBuffsChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToCharacterBuffs_376, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TigerRune::fn_onBuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        this->f_buffCounter = gd::gd_add(gd_ctx, this->f_buffCounter, lv_amount);
        gd::GdVal lv_relBuffs = gd::gd_div(gd_ctx, this->f_buffCounter, this->f_buffsNeeded);
        gd::GdVal lv_block = gd::gd_mul(lv_relBuffs, this->f_blockForBuffs);
        this->f_buffCounter = gd::gd_mod(gd_ctx, this->f_buffCounter, this->f_buffsNeeded);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_block, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0), lv_block), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_relBuffs, gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_793, _ca, 2); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {lv_relBuffs, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_793, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TigerRune::fn_onHotSwapHoverWithGemEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TigerRune::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_vampChance = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "chance_vamp", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_vampirism = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "vampirism", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_buffsNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_blockForBuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "block", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__TigerRune(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__TigerRune>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__TigerRune = {CLS_Gd__gd_core_items__Exclusive__TigerRune, "TigerRune", "res://gd_core_items/Exclusive/TigerRune.gd", &META_Gd__gd_core_items__Gems__Gem, true, _alloc_Gd__gd_core_items__Exclusive__TigerRune, &Gd__gd_core_items__Exclusive__TigerRune::get_static_prop_fn, &Gd__gd_core_items__Exclusive__TigerRune::call_static_fn};

void Gd__gd_core_items__Exclusive__WandofDissonance::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_healthUsed = gd::GdVal::null();
    this->f_effectDmg = gd::GdVal::null();
    this->f_availableBuffs = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__WandofDissonance::meta() const { return &META_Gd__gd_core_items__Exclusive__WandofDissonance; }
gd::GdVal Gd__gd_core_items__Exclusive__WandofDissonance::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__WandofDissonance::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__WandofDissonance::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_healthUsed_2516: out = this->f_healthUsed; return true;
        case SYM_GEN_effectDmg_2490: out = this->f_effectDmg; return true;
        case SYM_GEN_availableBuffs_2517: out = this->f_availableBuffs; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__WandofDissonance::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_healthUsed_2516: this->f_healthUsed = val; return true;
        case SYM_GEN_effectDmg_2490: this->f_effectDmg = val; return true;
        case SYM_GEN_availableBuffs_2517: this->f_availableBuffs = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__WandofDissonance::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__WandofDissonance::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__WandofDissonance::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__WandofDissonance::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getCurrentHealth_1138, nullptr, 0), this->f_healthUsed)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_healthUsed, gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_loseHealth_1141, _ca, 2); })();
        gd::GdVal lv_dam = gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_minDam_1579);
        gd::GdVal lv_res = ([&]() { gd::GdVal _ca[] = {lv_dam, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealEffectDamage_223, _ca, 2); })();
        gd::GdVal lv_maxBuffs = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::call_method(gd_ctx, this->f_availableBuffs, gd::SYM_keys, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMostStacks_363, _ca, 2); })();
        gd::GdVal lv_buffToGive = ([&]() { gd::GdVal _ca[] = {lv_maxBuffs}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_pickRandomElement_1650, _ca, 1); })();
        gd::GdVal lv_amount = gd::get_index(gd_ctx, this->f_availableBuffs, lv_buffToGive);
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), lv_buffToGive, lv_amount, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_203, _ca, 4); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WandofDissonance::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Dark_2602)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WandofDissonance::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_bonusEffectDmg = gd::GdVal::from_float(0.0);
    {
        gd::GdVal _t412 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t413 = (_t412.kind == gd::GdVal::Kind::Arr) ? _t412.arr : nullptr;
        uint32_t _len__t414 = _t413 ? _t413->len : 0u;
        for (uint32_t _t414 = 0; _t414 < _len__t414; ++_t414) {
            gd::GdVal lv_item = _t413->data[_t414];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Spell_2607)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())) {
                lv_bonusEffectDmg = gd::gd_add(gd_ctx, lv_bonusEffectDmg, gd::gd_mul(this->f_effectDmg, gd::GdVal::from_float(2.0)));
            }
            else {
                lv_bonusEffectDmg = gd::gd_add(gd_ctx, lv_bonusEffectDmg, this->f_effectDmg);
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_bonusEffectDmg}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeEffectDamageFactor_1265, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WandofDissonance::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_healthUsed = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healtht", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_effectDmg = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_availableBuffs = ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 3); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Mana_2571), gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })())); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Lucky_2570), gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })())); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Regeneration_2569), gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })())); return gd::GdVal::from_dict(d); })();
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1459, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__WandofDissonance(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__WandofDissonance>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__WandofDissonance = {CLS_Gd__gd_core_items__Exclusive__WandofDissonance, "WandofDissonance", "res://gd_core_items/Exclusive/WandofDissonance.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__WandofDissonance, &Gd__gd_core_items__Exclusive__WandofDissonance::get_static_prop_fn, &Gd__gd_core_items__Exclusive__WandofDissonance::call_static_fn};

void Gd__gd_core_items__Garlic::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Food::init_fields(gd_ctx);
    this->f_extraBlock = gd::GdVal::from_int(0LL);
}
const gd::GdClassMeta* Gd__gd_core_items__Garlic::meta() const { return &META_Gd__gd_core_items__Garlic; }
gd::GdVal Gd__gd_core_items__Garlic::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Garlic::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Garlic::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_extraBlock_1783: out = this->f_extraBlock; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__Garlic::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_extraBlock_1783: this->f_extraBlock = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Garlic::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_addBonusBlock_1784: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Garlic::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_addBonusBlock_1784: out = fn_addBonusBlock(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Garlic::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Garlic::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_206, nullptr, 0), this->f_extraBlock)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, _ca, 1); })();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeVampirism_341, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Garlic::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_extraBlock = gd::GdVal::from_int(0LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Garlic::fn_addBonusBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__extraBlock = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_extraBlock = gd::gd_add(gd_ctx, this->f_extraBlock, lv__extraBlock);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Garlic::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Garlic(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Garlic>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Garlic = {CLS_Gd__gd_core_items__Garlic, "Garlic", "res://gd_core_items/Garlic.gd", &META_Gd__gd_core_items__Food, true, _alloc_Gd__gd_core_items__Garlic, &Gd__gd_core_items__Garlic::get_static_prop_fn, &Gd__gd_core_items__Garlic::call_static_fn};

void Gd__gd_core_items__HeroSword::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__HeroSword::meta() const { return &META_Gd__gd_core_items__HeroSword; }
gd::GdVal Gd__gd_core_items__HeroSword::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__HeroSword::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__HeroSword::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__HeroSword::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__HeroSword::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__HeroSword::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__HeroSword::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__HeroSword::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_92, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HeroSword::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t415 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t416 = (_t415.kind == gd::GdVal::Kind::Arr) ? _t415.arr : nullptr;
        uint32_t _len__t417 = _t416 ? _t416->len : 0u;
        for (uint32_t _t417 = 0; _t417 < _len__t417; ++_t417) {
            gd::GdVal lv_item = _t416->data[_t417];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_163, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false), gd::GdVal::from_bool(false), gd::get_prop(gd_ctx, Gd__gd_core_items__HeroSword::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Jump_2608)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HeroSword::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__HeroSword(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__HeroSword>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__HeroSword = {CLS_Gd__gd_core_items__HeroSword, "HeroSword", "res://gd_core_items/HeroSword.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__HeroSword, &Gd__gd_core_items__HeroSword::get_static_prop_fn, &Gd__gd_core_items__HeroSword::call_static_fn};

void Gd__gd_core_items__ManaPotion::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Potion::init_fields(gd_ctx);
    this->f_healthThreshold = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__ManaPotion::meta() const { return &META_Gd__gd_core_items__ManaPotion; }
gd::GdVal Gd__gd_core_items__ManaPotion::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Potion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__ManaPotion::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__ManaPotion::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_healthThreshold_1759: out = this->f_healthThreshold; return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::get_prop(prop, out);
}
bool Gd__gd_core_items__ManaPotion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_healthThreshold_1759: this->f_healthThreshold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__ManaPotion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1754: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onDamaged_1760: return true;
        case SYM_GEN_onManaChanged_1834: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::has_own_method(m);
}
bool Gd__gd_core_items__ManaPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1754: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDamaged_1760: out = fn_onDamaged(args, argc); return true;
        case SYM_GEN_onManaChanged_1834: out = fn_onManaChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__ManaPotion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Potion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__ManaPotion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_319, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ManaPotion::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_mana_changed", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onManaChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_damaged", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDamaged", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ManaPotion::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__healthChange = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_923, nullptr, 0))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_relHealth = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getRelativeHealth_304, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_relHealth, this->f_healthThreshold)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consumePotion_1753, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ManaPotion::fn_onManaChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_923, nullptr, 0))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(gd::call_method(gd_ctx, lv_event, SYM_GEN_getOrigin_1489, nullptr, 0), &META_Gd__gd_core_items__Item)))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::call_method(gd_ctx, lv_event, SYM_GEN_getOrigin_1489, nullptr, 0), SYM_GEN_character_76, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0))))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consumePotion_1753, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ManaPotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Potion::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_healthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__ManaPotion(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__ManaPotion>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__ManaPotion = {CLS_Gd__gd_core_items__ManaPotion, "ManaPotion", "res://gd_core_items/ManaPotion.gd", &META_Gd__gd_core_items__Potion, true, _alloc_Gd__gd_core_items__ManaPotion, &Gd__gd_core_items__ManaPotion::get_static_prop_fn, &Gd__gd_core_items__ManaPotion::call_static_fn};

void Gd__gd_core_items__Pumpkin::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Food::init_fields(gd_ctx);
    this->f_heat = gd::GdVal::null();
    this->f_normalTexture = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Pumpkin::meta() const { return &META_Gd__gd_core_items__Pumpkin; }
gd::GdVal Gd__gd_core_items__Pumpkin::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Pumpkin::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Pumpkin::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_heat_1801: out = this->f_heat; return true;
        case SYM_GEN_normalTexture_1873: out = this->f_normalTexture; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__Pumpkin::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_heat_1801: this->f_heat = val; return true;
        case SYM_GEN_normalTexture_1873: this->f_normalTexture = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Pumpkin::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN_onFatigueStarted_1874: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Pumpkin::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_onFatigueStarted_1874: out = fn_onFatigueStarted(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Pumpkin::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Pumpkin::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_118, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StaminaResult_1280), SYM_GEN_Sufficient_2605))))) {
        gd::GdVal lv_res = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_222, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Pumpkin::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::set_prop(gd_ctx, this->f_descriptor, SYM_GEN_activationAni_1621, gd::get_prop(gd_ctx, Gd__gd_core_items__Pumpkin::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Throw_2609));
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_1392), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "fatigue_start", 13u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onFatigueStarted", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Pumpkin::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_stun", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_332, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Pumpkin::fn_onFatigueStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Pumpkin::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Pumpkin::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1459, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Pumpkin(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Pumpkin>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Pumpkin = {CLS_Gd__gd_core_items__Pumpkin, "Pumpkin", "res://gd_core_items/Pumpkin.gd", &META_Gd__gd_core_items__Food, true, _alloc_Gd__gd_core_items__Pumpkin, &Gd__gd_core_items__Pumpkin::get_static_prop_fn, &Gd__gd_core_items__Pumpkin::call_static_fn};

void Gd__gd_core_items__StrongHealthPotion::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__HealthPotion::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__StrongHealthPotion::meta() const { return &META_Gd__gd_core_items__StrongHealthPotion; }
gd::GdVal Gd__gd_core_items__StrongHealthPotion::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__HealthPotion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__StrongHealthPotion::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__StrongHealthPotion::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__HealthPotion::get_prop(prop, out);
}
bool Gd__gd_core_items__StrongHealthPotion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__HealthPotion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__StrongHealthPotion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1754: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__HealthPotion::has_own_method(m);
}
bool Gd__gd_core_items__StrongHealthPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1754: out = fn_onTriggerPotion(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__HealthPotion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__StrongHealthPotion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__HealthPotion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__StrongHealthPotion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_triggerEvent}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__HealthPotion::call_method(gd_ctx, SYM_GEN_onTriggerPotion_1754, _ca, 1, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongHealthPotion::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_856), SYM_GEN_High_2603), gd::GdVal::from_int(1LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongHealthPotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__HealthPotion::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__StrongHealthPotion(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__StrongHealthPotion>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__StrongHealthPotion = {CLS_Gd__gd_core_items__StrongHealthPotion, "StrongHealthPotion", "res://gd_core_items/StrongHealthPotion.gd", &META_Gd__gd_core_items__HealthPotion, true, _alloc_Gd__gd_core_items__StrongHealthPotion, &Gd__gd_core_items__StrongHealthPotion::get_static_prop_fn, &Gd__gd_core_items__StrongHealthPotion::call_static_fn};

void Gd__gd_core_items__YggdrasilLeaf::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_manaUsed = gd::GdVal::from_int(0LL);
    this->f_manaNeeded = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__YggdrasilLeaf::meta() const { return &META_Gd__gd_core_items__YggdrasilLeaf; }
gd::GdVal Gd__gd_core_items__YggdrasilLeaf::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__YggdrasilLeaf::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__YggdrasilLeaf::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_manaUsed_1912: out = this->f_manaUsed; return true;
        case SYM_GEN_manaNeeded_1786: out = this->f_manaNeeded; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__YggdrasilLeaf::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaUsed_1912: this->f_manaUsed = val; return true;
        case SYM_GEN_manaNeeded_1786: this->f_manaNeeded = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__YggdrasilLeaf::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onManaChanged_1834: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__YggdrasilLeaf::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onManaChanged_1834: out = fn_onManaChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__YggdrasilLeaf::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__YggdrasilLeaf::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Nature_2597)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__YggdrasilLeaf::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_manaUsed = gd::GdVal::from_int(0LL);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_mana_changed", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onManaChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__YggdrasilLeaf::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0), gd::SYM_size, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0), gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0), gd::SYM_size, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__YggdrasilLeaf::fn_onManaChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "used", 4u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, lv_event, SYM_GEN_getParam_1484, _ca, 2); })())) : gd::GdVal::from_bool(false)))) {
        this->f_manaUsed = gd::gd_add(gd_ctx, this->f_manaUsed, gd::gd_coerce_int(gd::gd_neg(lv_amount)));
        gd::GdVal lv_activations = gd::gd_div(gd_ctx, this->f_manaUsed, this->f_manaNeeded);
        this->f_manaUsed = gd::gd_mod(gd_ctx, this->f_manaUsed, this->f_manaNeeded);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_activations, gd::GdVal::from_int(1LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), lv_activations), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_269, nullptr, 0), lv_activations), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_358, _ca, 2); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__YggdrasilLeaf::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_manaNeeded = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__YggdrasilLeaf(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__YggdrasilLeaf>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__YggdrasilLeaf = {CLS_Gd__gd_core_items__YggdrasilLeaf, "YggdrasilLeaf", "res://gd_core_items/YggdrasilLeaf.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__YggdrasilLeaf, &Gd__gd_core_items__YggdrasilLeaf::get_static_prop_fn, &Gd__gd_core_items__YggdrasilLeaf::call_static_fn};
