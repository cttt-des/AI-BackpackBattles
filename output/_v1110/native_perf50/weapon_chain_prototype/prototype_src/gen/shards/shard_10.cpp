#include "../../native_inline_dispatch.hpp"
#include "../../native_scalar_equal.hpp"
#include "../../native_array_index.hpp"
#include "../../native_event_kernel.hpp"
#pragma STDC FP_CONTRACT OFF

#include "../hdrs/Gd__gd_core__Bag.hpp"
#include "../hdrs/Gd__gd_core_items__Gems__Gem.hpp"
#include "../hdrs/Gd__gd_core__CoreDamageSource.hpp"
#include "../hdrs/Gd__gd_core__CritwoodStaff.hpp"
#include "../hdrs/Gd__gd_core_items__Pan.hpp"
#include "../hdrs/Gd__gd_core__HeartContainer.hpp"
#include "../hdrs/Gd__gd_core__LuckyBow.hpp"
#include "../hdrs/Gd__gd_core__Piggybank.hpp"
#include "../hdrs/Gd__gd_core__RubyChonk.hpp"
#include "../hdrs/Gd__gd_core__StrongDemonicFlask.hpp"
#include "../hdrs/Gd__gd_core__VillainSword.hpp"
#include "../hdrs/Gd__gd_core_items__Food.hpp"
#include "../hdrs/Gd__gd_core_items__CarrotGoobert.hpp"
#include "../hdrs/Gd__gd_core_items__DjinnLamp.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__AmuletUnidentified.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__BadgerSpirit.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__BookofIce.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__CapofBrilliance.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Chess__WhiteKing.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Cthulhu.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__DoubleRainbow.hpp"
#include "../hdrs/Gd__gd_core_items__LeatherArmor.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__FlameBadge.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Ghost.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__HolyCollar.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__KnifetoMeetYou.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__MagicRing.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__MoreStats.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__PineProtector.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__PuzzlebagT.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Repeater.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ShellTotem.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Snowmaster.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Squirrel.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__TeslaCoil.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Ukulele.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Wrench.hpp"
#include "../hdrs/Gd__gd_core_items__GingerbreadMan.hpp"
#include "../hdrs/Gd__gd_core_items__LightGoobert.hpp"
#include "../hdrs/Gd__gd_core_items__PoisonBow.hpp"
#include "../hdrs/Gd__gd_core_items__SpectralDagger.hpp"
#include "../hdrs/Gd__gd_core_items__VampiricGloves.hpp"

namespace {
constexpr gd::GdStr battle_string_literals[] = {
    {"Box of Riches", 13u, 862823567u},
    {"melee", 5u, 2043306875u},
    {"ranged", 6u, 2657616514u},
    {"effect", 6u, 1852738900u},
    {"isCoreItem", 10u, 3597329357u},
    {"dur", 3u, 3509645056u},
    {"CritBuffTimer", 13u, 700944069u},
    {"buffEnded", 9u, 3457903416u},
    {"character_regeneration_changed", 30u, 2797934681u},
    {"onRegenChanged", 14u, 661197895u},
    {"maxhealth", 9u, 429334299u},
    {"Piggy Pinata_CRAFT", 18u, 23902885u},
    {"Piggy Pinata", 12u, 2904436292u},
    {"Hammer", 6u, 3178970599u},
    {"Thors Hammer", 12u, 3528755945u},
    {"character_heat_changed", 22u, 2413560104u},
    {"onHeatChanged", 13u, 775078454u},
    {"dur_stun", 8u, 1388942617u},
    {"lifesteal", 9u, 1515578962u},
    {"character_damaged", 17u, 745527748u},
    {"onPlayerDamaged", 15u, 677000780u},
    {"onOpponentDamaged", 17u, 568571164u},
    {"HealingReductionTimer", 21u, 2282847931u},
    {"healingReductionTimeout", 23u, 3865003293u},
    {"dam", 3u, 4031722721u},
    {"ownhpt", 6u, 3210869041u},
    {"opphpt", 6u, 4039152086u},
    {"ParticleTimer", 13u, 758126900u},
    {"onParticleTimeout", 17u, 3801482653u},
    {"character_block_changed", 23u, 4278945901u},
    {"checkStacks", 11u, 2317645022u},
    {"character_spikes_changed", 24u, 3463900413u},
    {"character_mana_changed", 22u, 798563205u},
    {"character_lucky_changed", 23u, 2259242176u},
    {"character_healed", 16u, 2989261042u},
    {"identifyAmulet", 14u, 1528809011u},
    {"dropped", 7u, 3229108261u},
    {"onDropped", 9u, 1334518102u},
    {"onDamaged", 9u, 2303747743u},
    {"heal", 4u, 979982427u},
    {"maxhealth_bonus", 15u, 1805060867u},
    {"healtht", 7u, 1555997217u},
    {"manat", 5u, 126091098u},
    {"mana", 4u, 3650585354u},
    {"cold", 4u, 3930381583u},
    {"speed", 5u, 2072037248u},
    {"piece_captured", 14u, 1502329272u},
    {"onAnyPieceCaptured", 18u, 2156068214u},
    {"empower", 7u, 2037162760u},
    {"buffs", 5u, 2149256365u},
    {"unhealing", 9u, 1425973148u},
    {"activated", 9u, 2866667388u},
    {"onItemActivated", 15u, 1109670618u},
    {"onLuckyOrRegenChanged", 21u, 3882299982u},
    {"luck", 4u, 4145017712u},
    {"regen", 5u, 16724762u},
    {"Dagger", 6u, 1838682075u},
    {"speed2", 6u, 498752822u},
    {"onOppoDamaged", 13u, 103180173u},
    {"scale", 5u, 2190941297u},
    {"triggerType", 11u, 2605013595u},
    {"stackType", 9u, 1268075559u},
    {"", 0u, 2166136261u},
    {"effects", 7u, 4278727781u},
    {"healtht_opp", 11u, 1479510151u},
    {"round", 5u, 1326178875u},
    {"TOOLTIP_Always Offered", 22u, 1323998851u},
    {"\n\n", 2u, 2274317941u},
    {"damblock", 8u, 2582642454u},
    {"maxspikes", 9u, 2756726798u},
    {"maxspikes_food", 14u, 3148355019u},
    {"damblock2", 9u, 2026808748u},
    {"maxblock", 8u, 3031704814u},
    {"onBuffChanged", 13u, 3423803215u},
    {"used", 4u, 1786277552u},
    {"_BAGEFFECT", 10u, 2435072665u},
    {"p_buff", 6u, 3365517425u},
    {"buff", 4u, 1244307660u},
    {"stamina", 7u, 3875003702u},
    {"coldt", 5u, 1164486817u},
    {"Exclusive/TeslaCoil.gd:26", 25u, 3265302821u},
    {"Exclusive/TeslaCoil.gd:34", 25u, 1386062398u},
    {"cdadvance", 9u, 1429998028u},
    {"sales", 5u, 2258376375u},
    {"weight", 6u, 1352703673u},
    {"Exclusive/Ukulele.gd:34", 23u, 3264254105u},
    {"advance", 7u, 667710333u},
    {"healamp", 7u, 54482251u},
    {"maxhealth_use", 13u, 2642987079u},
    {"dur_blind", 9u, 3690439708u},
    {"character_poison_changed", 24u, 65736246u},
    {"onOpponentPoisonChanged", 23u, 839266911u},
};
}

static const gd::GdEnum::KV _ekv_Gd__gd_core__Bag_BagTiles[] = {{"Default", 2LL}, {"CanAdd", 6LL}, {"CannotAdd", 5LL}};
static const gd::GdEnum _enum_Gd__gd_core__Bag_BagTiles = {"BagTiles", _ekv_Gd__gd_core__Bag_BagTiles, 3u};
void Gd__gd_core__Bag::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_bagTilemapPosition = gd::GdVal::null();
    this->f_cachedAffectedInsideItems = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_cachedInsideItems = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_bagTilemap = gd::GdVal::null();
    this->f_border = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__Bag::meta() const { return &META_Gd__gd_core__Bag; }
gd::GdVal Gd__gd_core__Bag::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_BagTiles_933: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Bag_BagTiles);
        default: break;
    }
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Bag::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    switch (prop) {
        case SYM_GEN_BagTiles_933: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Bag_BagTiles); return true;
        default: break;
    }
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Bag::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_bagTilemapPosition_914: out = this->f_bagTilemapPosition; return true;
        case SYM_GEN_cachedAffectedInsideItems_915: out = this->f_cachedAffectedInsideItems; return true;
        case SYM_GEN_cachedInsideItems_916: out = this->f_cachedInsideItems; return true;
        case SYM_GEN_bagTilemap_917: out = this->f_bagTilemap; return true;
        case SYM_GEN_border_918: out = this->f_border; return true;
        case SYM_GEN_BagTiles_933: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Bag_BagTiles); return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__Bag::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bagTilemapPosition_914: this->f_bagTilemapPosition = val; return true;
        case SYM_GEN_cachedAffectedInsideItems_915: this->f_cachedAffectedInsideItems = val; return true;
        case SYM_GEN_cachedInsideItems_916: this->f_cachedInsideItems = val; return true;
        case SYM_GEN_bagTilemap_917: this->f_bagTilemap = val; return true;
        case SYM_GEN_border_918: this->f_border = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Bag::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getHoverPriority_692: return true;
        case SYM_GEN_isBag_83: return true;
        case SYM_GEN_showBagBorderForItem_919: return true;
        case SYM_GEN_canApplyEffect_920: return true;
        case SYM_GEN_canBePicked_739: return true;
        case SYM_GEN_canBeLocked_821: return true;
        case SYM_GEN_resetZ_450: return true;
        case SYM_GEN_addToInventory_120: return true;
        case SYM_GEN_getBagLayerPriority_921: return true;
        case SYM_GEN_hasBagEffect_922: return true;
        case SYM_GEN__process_682: return true;
        case SYM_GEN_reactToDropResult_722: return true;
        case SYM_GEN_onRemoveFromInventory_418: return true;
        case SYM_GEN_getTopLeftGlobal_655: return true;
        case SYM_GEN_getBottomRightGlobal_656: return true;
        case SYM_GEN_isEmpty_923: return true;
        case SYM_GEN_getItemsInside_924: return true;
        case SYM_GEN_getEmptyCells_925: return true;
        case SYM_GEN_getEmptyGlobalPositions_926: return true;
        case SYM_GEN_getAffectedItemsInside_927: return true;
        case SYM_GEN_previewCanAffect_473: return true;
        case SYM_GEN_prepare_122: return true;
        case SYM_GEN_combatToShop_744: return true;
        case SYM_GEN_getCraftableNeighbors_492: return true;
        case SYM_GEN_onItemAdded_437: return true;
        case SYM_GEN_onAffectedItemInsideAdded_928: return true;
        case SYM_GEN_onItemRemoved_438: return true;
        case SYM_GEN_onAffectedItemInsideRemoved_929: return true;
        case SYM_GEN_pushItemsInsideToStorage_398: return true;
        case SYM_GEN_onDraggedWithParentStart_718: return true;
        case SYM_GEN_onDraggedWithParentEnd_720: return true;
        case SYM_GEN_getNumAffectedInside_930: return true;
        case SYM_GEN_getNumAffectedInside_type_931: return true;
        case SYM_GEN_getBagMultiplicity_932: return true;
        case SYM_GEN_discard_764: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Bag::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getHoverPriority_692: out = fn_getHoverPriority(args, argc); return true;
        case SYM_GEN_isBag_83: out = fn_isBag(args, argc); return true;
        case SYM_GEN_showBagBorderForItem_919: out = fn_showBagBorderForItem(args, argc); return true;
        case SYM_GEN_canApplyEffect_920: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN_canBePicked_739: out = fn_canBePicked(args, argc); return true;
        case SYM_GEN_canBeLocked_821: out = fn_canBeLocked(args, argc); return true;
        case SYM_GEN_resetZ_450: out = fn_resetZ(args, argc); return true;
        case SYM_GEN_addToInventory_120: out = fn_addToInventory(args, argc); return true;
        case SYM_GEN_getBagLayerPriority_921: out = fn_getBagLayerPriority(args, argc); return true;
        case SYM_GEN_hasBagEffect_922: out = fn_hasBagEffect(args, argc); return true;
        case SYM_GEN__process_682: out = fn__process(args, argc); return true;
        case SYM_GEN_reactToDropResult_722: out = fn_reactToDropResult(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_418: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_getTopLeftGlobal_655: out = fn_getTopLeftGlobal(args, argc); return true;
        case SYM_GEN_getBottomRightGlobal_656: out = fn_getBottomRightGlobal(args, argc); return true;
        case SYM_GEN_isEmpty_923: out = fn_isEmpty(args, argc); return true;
        case SYM_GEN_getItemsInside_924: out = fn_getItemsInside(args, argc); return true;
        case SYM_GEN_getEmptyCells_925: out = fn_getEmptyCells(args, argc); return true;
        case SYM_GEN_getEmptyGlobalPositions_926: out = fn_getEmptyGlobalPositions(args, argc); return true;
        case SYM_GEN_getAffectedItemsInside_927: out = fn_getAffectedItemsInside(args, argc); return true;
        case SYM_GEN_previewCanAffect_473: out = fn_previewCanAffect(args, argc); return true;
        case SYM_GEN_prepare_122: out = fn_prepare(args, argc); return true;
        case SYM_GEN_combatToShop_744: out = fn_combatToShop(args, argc); return true;
        case SYM_GEN_getCraftableNeighbors_492: out = fn_getCraftableNeighbors(args, argc); return true;
        case SYM_GEN_onItemAdded_437: out = fn_onItemAdded(args, argc); return true;
        case SYM_GEN_onAffectedItemInsideAdded_928: out = fn_onAffectedItemInsideAdded(args, argc); return true;
        case SYM_GEN_onItemRemoved_438: out = fn_onItemRemoved(args, argc); return true;
        case SYM_GEN_onAffectedItemInsideRemoved_929: out = fn_onAffectedItemInsideRemoved(args, argc); return true;
        case SYM_GEN_pushItemsInsideToStorage_398: out = fn_pushItemsInsideToStorage(args, argc); return true;
        case SYM_GEN_onDraggedWithParentStart_718: out = fn_onDraggedWithParentStart(args, argc); return true;
        case SYM_GEN_onDraggedWithParentEnd_720: out = fn_onDraggedWithParentEnd(args, argc); return true;
        case SYM_GEN_getNumAffectedInside_930: out = fn_getNumAffectedInside(args, argc); return true;
        case SYM_GEN_getNumAffectedInside_type_931: out = fn_getNumAffectedInside_type(args, argc); return true;
        case SYM_GEN_getBagMultiplicity_932: out = fn_getBagMultiplicity(args, argc); return true;
        case SYM_GEN_discard_764: out = fn_discard(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Bag::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Bag::fn_getHoverPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(this->f_dragged)) {
        return Gd__gd_core__Bag::get_static_const_or_enum(gd_ctx, SYM_GEN_DRAG_PRIORITY_527);
    }
    else {
        return gd::gd_neg(gd::GdVal::from_int(1LL));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_isBag(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_showBagBorderForItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isBag_83, nullptr, 0)))) ? gd::GdVal::from_bool(gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_920, _ca, 1); })())) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_canApplyEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__toItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_canBePicked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_canBeLocked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_resetZ(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_addToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__inventory = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__occupiedCells = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv__placedByPlayer = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv__placedByPlayer = gd::gd_coerce_bool(lv__placedByPlayer);
    (void)([&]() { gd::GdVal _ca[] = {lv__inventory, lv__occupiedCells, lv__placedByPlayer}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_addToInventory_120, _ca, 3, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_getBagLayerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getRarity_236, nullptr, 0), gd::GdVal::from_int(5LL))))) {
        return gd::GdVal::from_int(2LL);
    }
    if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasBagEffect_922, nullptr, 0))) {
        return gd::GdVal::from_int(1LL);
    }
    return gd::GdVal::from_int(0LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_hasBagEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::native_scalar_ne(this->f_border, gd::GdVal::null()));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn__process(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    if (gd::native_scalar_truth(this->f_dragged)) {
        if (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1302), SYM_GEN_INVENTORY_1093), SYM_GEN_canAddBag_2858, _ca, 1); })())) {
        }
        else {
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_reactToDropResult(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_result = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_result}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_reactToDropResult_722, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_getTopLeftGlobal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_getBottomRightGlobal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_isEmpty(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0), gd::SYM_empty, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_getItemsInside(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(gd::native_inline_call(gd_ctx, this->f_cachedInsideItems, gd::SYM_empty, nullptr, 0))))) {
        return this->f_cachedInsideItems;
    }
    return ([&]() { gd::GdVal _ca[] = {this->f_occupiedCells}; return gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getItemsInCells_1608, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_getEmptyCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_emptyCells = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1449 = gd::gd_iter_seq(gd_ctx.arena, this->f_occupiedCells);
        gd::GdArr* _t1450 = (_t1449.kind == gd::GdVal::Kind::Arr) ? _t1449.arr : nullptr;
        uint32_t _len__t1451 = _t1450 ? _t1450->len : 0u;
        for (uint32_t _t1451 = 0; _t1451 < _len__t1451; ++_t1451) {
            gd::GdVal lv_cell = _t1450->data[_t1451];
            if (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {lv_cell}; return gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_isCellEmpty_1605, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_cell}; return gd::native_inline_call(gd_ctx, lv_emptyCells, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    return lv_emptyCells;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_getEmptyGlobalPositions(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_positions = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1452 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getEmptyCells_925, nullptr, 0));
        gd::GdArr* _t1453 = (_t1452.kind == gd::GdVal::Kind::Arr) ? _t1452.arr : nullptr;
        uint32_t _len__t1454 = _t1453 ? _t1453->len : 0u;
        for (uint32_t _t1454 = 0; _t1454 < _len__t1454; ++_t1454) {
            gd::GdVal lv_cell = _t1453->data[_t1454];
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_cell, gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_cellToGlobalPos_2859, _ca, 2); })()}; return gd::native_inline_call(gd_ctx, lv_positions, gd::SYM_push_back, _ca, 1); })();
        }
    }
    return lv_positions;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_getAffectedItemsInside(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(this->f_placed)))) {
        return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    }
    if (gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(gd::native_inline_call(gd_ctx, this->f_cachedAffectedInsideItems, gd::SYM_empty, nullptr, 0))))) {
        return this->f_cachedAffectedInsideItems;
    }
    gd::GdVal lv_affected = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1455 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0));
        gd::GdArr* _t1456 = (_t1455.kind == gd::GdVal::Kind::Arr) ? _t1455.arr : nullptr;
        uint32_t _len__t1457 = _t1456 ? _t1456->len : 0u;
        for (uint32_t _t1457 = 0; _t1457 < _len__t1457; ++_t1457) {
            gd::GdVal lv_item = _t1456->data[_t1457];
            if (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_920, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, lv_affected, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    return lv_affected;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_previewCanAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_cachedInsideItems = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0);
    {
        gd::GdVal _t1458 = gd::gd_iter_seq(gd_ctx.arena, this->f_cachedInsideItems);
        gd::GdArr* _t1459 = (_t1458.kind == gd::GdVal::Kind::Arr) ? _t1458.arr : nullptr;
        uint32_t _len__t1460 = _t1459 ? _t1459->len : 0u;
        for (uint32_t _t1460 = 0; _t1460 < _len__t1460; ++_t1460) {
            gd::GdVal lv_item = _t1459->data[_t1460];
            if (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_920, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, this->f_cachedAffectedInsideItems, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_prepare_122, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_combatToShop(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_cachedAffectedInsideItems, gd::SYM_clear, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, this->f_cachedInsideItems, gd::SYM_clear, nullptr, 0);
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_combatToShop_744, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_getCraftableNeighbors(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_craftableItems = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1461 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0));
        gd::GdArr* _t1462 = (_t1461.kind == gd::GdVal::Kind::Arr) ? _t1461.arr : nullptr;
        uint32_t _len__t1463 = _t1462 ? _t1462->len : 0u;
        for (uint32_t _t1463 = 0; _t1463 < _len__t1463; ++_t1463) {
            gd::GdVal lv_item = _t1462->data[_t1463];
            if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isAvailableForCrafting_493, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, lv_craftableItems, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    return lv_craftableItems;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_onItemAdded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_onItemAdded_437, _ca, 1, _out); return _out; })();
    if (gd::native_scalar_truth((gd::native_scalar_truth(gd::gd_in(lv_item, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0))) ? gd::GdVal::from_bool(gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_920, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        if (gd::native_scalar_truth(gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_placedByPlayer_50))) {
        }
        (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAffectedItemInsideAdded_928, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_onAffectedItemInsideAdded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_onItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_onItemRemoved_438, _ca, 1, _out); return _out; })();
    if (gd::native_scalar_truth((gd::native_scalar_truth(gd::gd_in(lv_item, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0))) ? gd::GdVal::from_bool(gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_920, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAffectedItemInsideRemoved_929, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_onAffectedItemInsideRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_pushItemsInsideToStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_onDraggedWithParentStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_bag = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_bag}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_onDraggedWithParentStart_718, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_onDraggedWithParentEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_onDraggedWithParentEnd_720, nullptr, 0, _out); return _out; })();
    if (gd::native_scalar_truth(this->f_dragged)) {
    }
    else {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetZ_450, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_getNumAffectedInside(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_num = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t1464 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_927, nullptr, 0));
        gd::GdArr* _t1465 = (_t1464.kind == gd::GdVal::Kind::Arr) ? _t1464.arr : nullptr;
        uint32_t _len__t1466 = _t1465 ? _t1465->len : 0u;
        for (uint32_t _t1466 = 0; _t1466 < _len__t1466; ++_t1466) {
            gd::GdVal lv_item = _t1465->data[_t1466];
            lv_num = gd::gd_add(gd_ctx, lv_num, gd::GdVal::from_int(1LL));
        }
    }
    return lv_num;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_getNumAffectedInside_type(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    gd::GdVal lv_num = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t1467 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_927, nullptr, 0));
        gd::GdArr* _t1468 = (_t1467.kind == gd::GdVal::Kind::Arr) ? _t1467.arr : nullptr;
        uint32_t _len__t1469 = _t1468 ? _t1468->len : 0u;
        for (uint32_t _t1469 = 0; _t1469 < _len__t1469; ++_t1469) {
            gd::GdVal lv_item = _t1468->data[_t1469];
            lv_num = gd::gd_add(gd_ctx, lv_num, ([&]() { gd::GdVal _ca[] = {lv_type}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getTypeMultiplicity_80, _ca, 1); })());
        }
    }
    return lv_num;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_getBagMultiplicity(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_int(1LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_discard(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_discardGems = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    if (gd::native_scalar_truth(this->f_pooled)) {
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_discardGems}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_discard_764, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_bagTilemapPosition, gd::GdVal::null())))) {
    }
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Bag(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__Bag>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,4u); return object; }
const gd::GdClassMeta META_Gd__gd_core__Bag = {CLS_Gd__gd_core__Bag, "Bag", "res://gd_core/Bag.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__Bag, &Gd__gd_core__Bag::get_static_prop_fn, &Gd__gd_core__Bag::call_static_fn};

static const gd::GdEnum::KV _ekv_Gd__gd_core_items__Gems__Gem_GemMode[] = {{"Weapon", 0LL}, {"Armor", 1LL}, {"Inventory", 2LL}, {"Inactive", 3LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__Gems__Gem_GemMode = {"GemMode", _ekv_Gd__gd_core_items__Gems__Gem_GemMode, 4u};
void Gd__gd_core_items__Gems__Gem::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_hoveredSocket = gd::GdVal::null();
    this->f_socket = gd::GdVal::null();
    this->f_movebackSocket = gd::GdVal::null();
    this->f_dropTween = gd::GdVal::null();
    this->f_gemPower = gd::GdVal::from_float(1.0);
    this->f_dropPosition = gd::GdVal::null();
    this->f_dropRotation = gd::GdVal::null();
    this->f_quantizedRotation = gd::GdVal::null();
    this->f_socketDetectionArea = gd::GdVal::null();
    this->f_gemAnimation = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Gems__Gem::meta() const { return &META_Gd__gd_core_items__Gems__Gem; }
gd::GdVal Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_GemMode_994: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Gems__Gem_GemMode);
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Gems__Gem::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    switch (prop) {
        case SYM_GEN_GemMode_994: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Gems__Gem_GemMode); return true;
        default: break;
    }
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Gems__Gem::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_hoveredSocket_961: out = this->f_hoveredSocket; return true;
        case SYM_GEN_socket_962: out = this->f_socket; return true;
        case SYM_GEN_movebackSocket_963: out = this->f_movebackSocket; return true;
        case SYM_GEN_dropTween_964: out = this->f_dropTween; return true;
        case SYM_GEN_gemPower_965: out = this->f_gemPower; return true;
        case SYM_GEN_dropPosition_966: out = this->f_dropPosition; return true;
        case SYM_GEN_dropRotation_967: out = this->f_dropRotation; return true;
        case SYM_GEN_quantizedRotation_968: out = this->f_quantizedRotation; return true;
        case SYM_GEN_socketDetectionArea_969: out = this->f_socketDetectionArea; return true;
        case SYM_GEN_gemAnimation_970: out = this->f_gemAnimation; return true;
        case SYM_GEN_GemMode_994: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Gems__Gem_GemMode); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Gems__Gem::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_hoveredSocket_961: this->f_hoveredSocket = val; return true;
        case SYM_GEN_socket_962: this->f_socket = val; return true;
        case SYM_GEN_movebackSocket_963: this->f_movebackSocket = val; return true;
        case SYM_GEN_dropTween_964: this->f_dropTween = val; return true;
        case SYM_GEN_gemPower_965: this->f_gemPower = val; return true;
        case SYM_GEN_dropPosition_966: this->f_dropPosition = val; return true;
        case SYM_GEN_dropRotation_967: this->f_dropRotation = val; return true;
        case SYM_GEN_quantizedRotation_968: this->f_quantizedRotation = val; return true;
        case SYM_GEN_socketDetectionArea_969: this->f_socketDetectionArea = val; return true;
        case SYM_GEN_gemAnimation_970: this->f_gemAnimation = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Gems__Gem::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_isGem_84: return true;
        case SYM_GEN_isOwnable_250: return true;
        case SYM_GEN_isOwnedByOpponent_251: return true;
        case SYM_GEN_getEffectiveOwnerType_257: return true;
        case SYM_GEN_getInventory_658: return true;
        case SYM_GEN_getItem_389: return true;
        case SYM_GEN_isPlaced_76: return true;
        case SYM_GEN_isInInventory_971: return true;
        case SYM_GEN_getGemMode_972: return true;
        case SYM_GEN_getGemPower_973: return true;
        case SYM_GEN_changeGemPower_974: return true;
        case SYM_GEN_getHoverPriority_692: return true;
        case SYM_GEN_character_74: return true;
        case SYM_GEN__process_682: return true;
        case SYM_GEN_previewCellCollision_471: return true;
        case SYM_GEN_gainFocus_694: return true;
        case SYM_GEN_loseFocus_703: return true;
        case SYM_GEN_prepareLerpToSocket_975: return true;
        case SYM_GEN_drop_723: return true;
        case SYM_GEN_lerpToSocket_976: return true;
        case SYM_GEN_pickup_717: return true;
        case SYM_GEN_addToSocket_977: return true;
        case SYM_GEN_unsocket_978: return true;
        case SYM_GEN_removeFromSocket_979: return true;
        case SYM_GEN_killDropTween_980: return true;
        case SYM_GEN_returnToSocket_399: return true;
        case SYM_GEN_hasCooldown_95: return true;
        case SYM_GEN_miniActivate_470: return true;
        case SYM_GEN_prepareInventory_981: return true;
        case SYM_GEN_prepareWeapon_982: return true;
        case SYM_GEN_prepareArmor_983: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_combatStartInventory_984: return true;
        case SYM_GEN_combatStartWeapon_985: return true;
        case SYM_GEN_combatStartArmor_986: return true;
        case SYM_GEN_combatStart_127: return true;
        case SYM_GEN_combatEndInventory_987: return true;
        case SYM_GEN_combatEndWeapon_988: return true;
        case SYM_GEN_combatEndArmor_989: return true;
        case SYM_GEN_combatEnd_131: return true;
        case SYM_GEN_shopEntered_745: return true;
        case SYM_GEN_getBaseDescription_990: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN_onHotSwapHoverWithGem_991: return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_992: return true;
        case SYM_GEN_createGemParticles_993: return true;
        case SYM_GEN_canPreviewFusions_828: return true;
        case SYM_GEN_canModifyChance_293: return true;
        case SYM_GEN_getNeighborItemsAndGems_489: return true;
        case SYM_GEN_canCombine_445: return true;
        case SYM_GEN_shift_454: return true;
        case SYM_GEN_isMovingBack_801: return true;
        case SYM_GEN_addToStorageBox_667: return true;
        case SYM_GEN_discard_764: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Gems__Gem::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_isGem_84: out = fn_isGem(args, argc); return true;
        case SYM_GEN_isOwnable_250: out = fn_isOwnable(args, argc); return true;
        case SYM_GEN_isOwnedByOpponent_251: out = fn_isOwnedByOpponent(args, argc); return true;
        case SYM_GEN_getEffectiveOwnerType_257: out = fn_getEffectiveOwnerType(args, argc); return true;
        case SYM_GEN_getInventory_658: out = fn_getInventory(args, argc); return true;
        case SYM_GEN_getItem_389: out = fn_getItem(args, argc); return true;
        case SYM_GEN_isPlaced_76: out = fn_isPlaced(args, argc); return true;
        case SYM_GEN_isInInventory_971: out = fn_isInInventory(args, argc); return true;
        case SYM_GEN_getGemMode_972: out = fn_getGemMode(args, argc); return true;
        case SYM_GEN_getGemPower_973: out = fn_getGemPower(args, argc); return true;
        case SYM_GEN_changeGemPower_974: out = fn_changeGemPower(args, argc); return true;
        case SYM_GEN_getHoverPriority_692: out = fn_getHoverPriority(args, argc); return true;
        case SYM_GEN_character_74: out = fn_character(args, argc); return true;
        case SYM_GEN__process_682: out = fn__process(args, argc); return true;
        case SYM_GEN_previewCellCollision_471: out = fn_previewCellCollision(args, argc); return true;
        case SYM_GEN_gainFocus_694: out = fn_gainFocus(args, argc); return true;
        case SYM_GEN_loseFocus_703: out = fn_loseFocus(args, argc); return true;
        case SYM_GEN_prepareLerpToSocket_975: out = fn_prepareLerpToSocket(args, argc); return true;
        case SYM_GEN_drop_723: out = fn_drop(args, argc); return true;
        case SYM_GEN_lerpToSocket_976: out = fn_lerpToSocket(args, argc); return true;
        case SYM_GEN_pickup_717: out = fn_pickup(args, argc); return true;
        case SYM_GEN_addToSocket_977: out = fn_addToSocket(args, argc); return true;
        case SYM_GEN_unsocket_978: out = fn_unsocket(args, argc); return true;
        case SYM_GEN_removeFromSocket_979: out = fn_removeFromSocket(args, argc); return true;
        case SYM_GEN_killDropTween_980: out = fn_killDropTween(args, argc); return true;
        case SYM_GEN_returnToSocket_399: out = fn_returnToSocket(args, argc); return true;
        case SYM_GEN_hasCooldown_95: out = fn_hasCooldown(args, argc); return true;
        case SYM_GEN_miniActivate_470: out = fn_miniActivate(args, argc); return true;
        case SYM_GEN_prepareInventory_981: out = fn_prepareInventory(args, argc); return true;
        case SYM_GEN_prepareWeapon_982: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_prepareArmor_983: out = fn_prepareArmor(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_combatStartInventory_984: out = fn_combatStartInventory(args, argc); return true;
        case SYM_GEN_combatStartWeapon_985: out = fn_combatStartWeapon(args, argc); return true;
        case SYM_GEN_combatStartArmor_986: out = fn_combatStartArmor(args, argc); return true;
        case SYM_GEN_combatStart_127: out = fn_combatStart(args, argc); return true;
        case SYM_GEN_combatEndInventory_987: out = fn_combatEndInventory(args, argc); return true;
        case SYM_GEN_combatEndWeapon_988: out = fn_combatEndWeapon(args, argc); return true;
        case SYM_GEN_combatEndArmor_989: out = fn_combatEndArmor(args, argc); return true;
        case SYM_GEN_combatEnd_131: out = fn_combatEnd(args, argc); return true;
        case SYM_GEN_shopEntered_745: out = fn_shopEntered(args, argc); return true;
        case SYM_GEN_getBaseDescription_990: out = fn_getBaseDescription(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_onHotSwapHoverWithGem_991: out = fn_onHotSwapHoverWithGem(args, argc); return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_992: out = fn_onHotSwapHoverWithGemEnd(args, argc); return true;
        case SYM_GEN_createGemParticles_993: out = fn_createGemParticles(args, argc); return true;
        case SYM_GEN_canPreviewFusions_828: out = fn_canPreviewFusions(args, argc); return true;
        case SYM_GEN_canModifyChance_293: out = fn_canModifyChance(args, argc); return true;
        case SYM_GEN_getNeighborItemsAndGems_489: out = fn_getNeighborItemsAndGems(args, argc); return true;
        case SYM_GEN_canCombine_445: out = fn_canCombine(args, argc); return true;
        case SYM_GEN_shift_454: out = fn_shift(args, argc); return true;
        case SYM_GEN_isMovingBack_801: out = fn_isMovingBack(args, argc); return true;
        case SYM_GEN_addToStorageBox_667: out = fn_addToStorageBox(args, argc); return true;
        case SYM_GEN_discard_764: out = fn_discard(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Gems__Gem::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_isGem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_isOwnable(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_socket, gd::GdVal::null())))) {
        return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, this->f_socket, SYM_GEN_getItem_389, nullptr, 0), SYM_GEN_isOwnable_250, nullptr, 0);
    }
    else {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_isOwnable_250, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_isOwnedByOpponent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_socket, gd::GdVal::null())))) {
        return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, this->f_socket, SYM_GEN_getItem_389, nullptr, 0), SYM_GEN_isOwnedByOpponent_251, nullptr, 0);
    }
    else {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_isOwnedByOpponent_251, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_getEffectiveOwnerType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_socket, gd::GdVal::null())))) {
        return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, this->f_socket, SYM_GEN_getItem_389, nullptr, 0), SYM_GEN_getEffectiveOwnerType_257, nullptr, 0);
    }
    else {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getEffectiveOwnerType_257, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_getInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_socket, gd::GdVal::null())))) {
        return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, this->f_socket, SYM_GEN_getItem_389, nullptr, 0), SYM_GEN_getInventory_658, nullptr, 0);
    }
    else {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getInventory_658, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_getItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_socket, gd::GdVal::null())))) {
        return gd::native_inline_call(gd_ctx, this->f_socket, SYM_GEN_getItem_389, nullptr, 0);
    }
    else {
        return gd::GdVal::null();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_isPlaced(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_socket, gd::GdVal::null())))) {
        return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, this->f_socket, SYM_GEN_getItem_389, nullptr, 0), SYM_GEN_isPlaced_76, nullptr, 0);
    }
    else {
        return this->f_placed;
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_isInInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_socket, gd::GdVal::null())))) {
        return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, this->f_socket, SYM_GEN_getItem_389, nullptr, 0), SYM_GEN_isInInventory_971, nullptr, 0);
    }
    else {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_isInInventory_971, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_getGemMode(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_socket, gd::GdVal::null())))) {
        if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_389, nullptr, 0), SYM_GEN_isWeapon_82, nullptr, 0))) {
            return gd::GdVal::from_int(0LL);
        }
        else {
            return gd::GdVal::from_int(1LL);
        }
    }
    else {
        if (gd::native_scalar_truth(this->f_placed)) {
            return gd::GdVal::from_int(2LL);
        }
        else {
            return gd::GdVal::from_int(3LL);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_getGemPower(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_max(gd::GdVal::from_float(0.0), this->f_gemPower);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_changeGemPower(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_float(lv_amount);
    this->f_gemPower = gd::gd_add(gd_ctx, this->f_gemPower, lv_amount);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_getHoverPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(this->f_dragged)) {
        return Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_DRAG_PRIORITY_527);
    }
    else {
        return gd::GdVal::from_int(1LL);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_character(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_972, nullptr, 0), gd::GdVal::from_int(3LL))))) {
        return gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1302);
    }
    else if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_972, nullptr, 0), gd::GdVal::from_int(2LL))))) {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_character_74, nullptr, 0, _out); return _out; })();
    }
    else {
        return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_389, nullptr, 0), SYM_GEN_character_74, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn__process(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_previewCellCollision(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth((gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(this->f_hoveredSocket))) ? gd::GdVal::from_bool(gd::native_scalar_truth((gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(this->f_movebackSocket))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_frame_counter_1413), gd::gd_add(gd_ctx, this->f_pickupFrame, gd::GdVal::from_int(1LL))))))))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_previewCellCollision_471, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_gainFocus(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_gainFocus_694, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_loseFocus(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_loseFocus_703, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_prepareLerpToSocket(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_drop(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(0LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_lerpToSocket(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_interpolationPoint = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_interpolationPoint = gd::gd_coerce_float(lv_interpolationPoint);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_pickup(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_pickupType = (_argc > 0) ? _args[0] : (gd::native_inline_get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_PickupType_866), SYM_GEN_Grabbed_2730));
    (void)([&]() { gd::GdVal _ca[] = {lv_pickupType}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_pickup_717, _ca, 1, _out); return _out; })();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_socket, gd::GdVal::null())))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_killDropTween_980, nullptr, 0);
        this->f_movebackSocket = this->f_socket;
        this->f_hoveredSocket = this->f_socket;
        if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, gd::native_inline_call(gd_ctx, this->f_socket, SYM_GEN_getItem_389, nullptr, 0), SYM_GEN_ownerType_49), gd::GdVal::from_int(2LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setFaceDirection_478, _ca, 1); })();
        }
        else {
            this->f_faceDirection = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGlobalFaceDirection_466, nullptr, 0));
        }
        (void)gd::native_inline_call(gd_ctx, this->f_socket, SYM_GEN_onPickupGem_2861, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_addToSocket(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__socket = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_unsocket(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_killDropTween_980, nullptr, 0);
    gd::GdVal lv_s = this->f_socket;
    (void)gd::native_inline_call(gd_ctx, this->f_socket, SYM_GEN_onPickupGem_2861, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, lv_s, SYM_GEN_hideSocket_2862, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_removeFromSocket(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_killDropTween(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_returnToSocket(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_movebackDur = (_argc > 0) ? _args[0] : (gd::GdVal::from_float(0.1));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_hasCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_gemMode = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_972, nullptr, 0);
    return (gd::native_scalar_truth((gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_gemMode, gd::GdVal::from_int(2LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_gemMode, gd::GdVal::from_int(3LL))))))) ? gd::GdVal::from_bool(gd::native_scalar_truth(([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_hasCooldown_95, nullptr, 0, _out); return _out; })())) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_miniActivate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_miniActivate_470, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.5)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_Scale_775, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_prepareInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_prepareWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_prepareArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1470 = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_972, nullptr, 0);
        if (gd::native_scalar_eq(_t1470, gd::GdVal::from_int(2LL))) {
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_prepareInventory_981, nullptr, 0);
        }
        else if (gd::native_scalar_eq(_t1470, gd::GdVal::from_int(0LL))) {
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_prepareWeapon_982, nullptr, 0);
        }
        else if (gd::native_scalar_eq(_t1470, gd::GdVal::from_int(1LL))) {
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_prepareArmor_983, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_combatStartInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_combatStartWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_combatStartArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_combatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_combatStart_127, nullptr, 0, _out); return _out; })();
    this->f_iterationCooldown = gd::gd_coerce_float(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_adjustCooldown_107, nullptr, 0));
    this->f_triggerTime = gd::gd_coerce_float(this->f_iterationCooldown);
    {
        gd::GdVal _t1471 = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_972, nullptr, 0);
        if (gd::native_scalar_eq(_t1471, gd::GdVal::from_int(2LL))) {
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_combatStartInventory_984, nullptr, 0);
        }
        else if (gd::native_scalar_eq(_t1471, gd::GdVal::from_int(0LL))) {
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_combatStartWeapon_985, nullptr, 0);
        }
        else if (gd::native_scalar_eq(_t1471, gd::GdVal::from_int(1LL))) {
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_combatStartArmor_986, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_combatEndInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_combatEndWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_combatEndArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_combatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_combatEnd_131, nullptr, 0, _out); return _out; })();
    {
        gd::GdVal _t1472 = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_972, nullptr, 0);
        if (gd::native_scalar_eq(_t1472, gd::GdVal::from_int(2LL))) {
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_combatEndInventory_987, nullptr, 0);
        }
        else if (gd::native_scalar_eq(_t1472, gd::GdVal::from_int(0LL))) {
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_combatEndWeapon_988, nullptr, 0);
        }
        else if (gd::native_scalar_eq(_t1472, gd::GdVal::from_int(1LL))) {
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_combatEndArmor_989, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_shopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_craft = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_craft = gd::gd_coerce_bool(lv_craft);
    (void)([&]() { gd::GdVal _ca[] = {lv_craft}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_shopEntered_745, _ca, 1, _out); return _out; })();
    this->f_gemPower = gd::GdVal::from_float(1.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_getBaseDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    return ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getDescription_642, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseDescription_990, _ca, 1); })();
    gd::GdVal lv_colors = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_inactiveColor_2834), gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_inactiveColor_2834), gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_inactiveColor_2834)}));
    gd::GdVal lv_gemMode = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_972, nullptr, 0);
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_gemMode, gd::GdVal::from_int(3LL))))) {
        { gd::GdVal _t1473 = lv_colors; gd::GdVal _t1474 = lv_gemMode; gd::native_array_set_index(gd_ctx, _t1473, _t1474, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_modifiedColor_2829)); }
    }
    return ([&]() { gd::GdVal _ca[] = {lv_descr, lv_colors, gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModeDescription_645, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_onHotSwapHoverWithGem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_onHotSwapHoverWithGemEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_createGemParticles(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_canPreviewFusions(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(this->f_socket)) {
        return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, this->f_socket, SYM_GEN_getItem_389, nullptr, 0), SYM_GEN_canPreviewFusions_828, nullptr, 0);
    }
    else {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_canPreviewFusions_828, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_canModifyChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_getNeighborItemsAndGems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(this->f_socket)) {
        if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_389, nullptr, 0), SYM_GEN_ownerType_49), gd::GdVal::from_int(2LL))))) {
            return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
        }
        gd::GdVal lv_neighbors = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_389, nullptr, 0)}));
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_389, nullptr, 0), SYM_GEN_getNeighborItemsAndGems_489, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_neighbors, gd::SYM_append_array, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, lv_neighbors, gd::SYM_erase, _ca, 1); })();
        return lv_neighbors;
    }
    else {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getNeighborItemsAndGems_489, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_canCombine(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(this->f_socket)) {
        return gd::GdVal::from_bool(true);
    }
    else {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_canCombine_445, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_shift(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_direction = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(this->f_socket)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_direction}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_shift_454, _ca, 1, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_isMovingBack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_addToStorageBox(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_addImpulse = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_tweenBouncyness = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    lv_tweenBouncyness = gd::gd_coerce_bool(lv_tweenBouncyness);
    gd::GdVal lv_checkCollisions = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_targetPos = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_speed = (_argc > 4) ? _args[4] : (gd::GdVal::from_float(1.0));
    gd::GdVal lv_secondCheck = (_argc > 5) ? _args[5] : (gd::GdVal::from_bool(false));
    if (gd::native_scalar_truth(this->f_socket)) {
        gd::GdVal lv_s = this->f_socket;
        (void)([&]() { gd::GdVal _ca[] = {lv_addImpulse, lv_tweenBouncyness, lv_checkCollisions, lv_targetPos, lv_speed, lv_secondCheck}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_addToStorageBox_667, _ca, 6, _out); return _out; })();
        (void)gd::native_inline_call(gd_ctx, lv_s, SYM_GEN_onPickupGem_2861, nullptr, 0);
        (void)gd::native_inline_call(gd_ctx, lv_s, SYM_GEN_hideSocket_2862, nullptr, 0);
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {lv_addImpulse, lv_tweenBouncyness, lv_checkCollisions, lv_targetPos, lv_speed, lv_secondCheck}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_addToStorageBox_667, _ca, 6, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_discard(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_discardGems = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    (void)([&]() { gd::GdVal _ca[] = {lv_discardGems}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_discard_764, _ca, 1, _out); return _out; })();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_socket, gd::GdVal::null())))) {
        gd::set_prop(gd_ctx, this->f_socket, SYM_GEN_gem_2863, gd::GdVal::null());
        (void)gd::native_inline_call(gd_ctx, this->f_socket, SYM_GEN_hideSocket_2862, nullptr, 0);
        this->f_socket = gd::GdVal::null();
        this->f_movebackSocket = gd::GdVal::null();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_gateItem_1693), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[0])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })())))) {
        if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, this->f_specificDragParticles, gd::SYM_empty, nullptr, 0))) {
        }
    }
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Gems__Gem(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Gems__Gem>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,575u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Gems__Gem = {CLS_Gd__gd_core_items__Gems__Gem, "Gem", "res://gd_core_items/Gems/Gem.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Gems__Gem, &Gd__gd_core_items__Gems__Gem::get_static_prop_fn, &Gd__gd_core_items__Gems__Gem::call_static_fn};

static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreDamageSource_Type[] = {{"Melee", 0LL}, {"Ranged", 1LL}, {"Effect", 2LL}, {"SelfDamage", 3LL}, {"Unhealing", 98LL}, {"Spikes", 104LL}, {"Poison", 108LL}, {"Fatigue", 99LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreDamageSource_Type = {"Type", _ekv_Gd__gd_core__CoreDamageSource_Type, 8u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreDamageSource_Flags[] = {{"None", 0LL}, {"CanBeBlocked", 1LL}, {"CanTriggerSpikes", 2LL}, {"CanTriggerVampirism", 4LL}, {"CanTriggerItems", 8LL}, {"CanMiss", 16LL}, {"CanCrit", 32LL}, {"All", 63LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreDamageSource_Flags = {"Flags", _ekv_Gd__gd_core__CoreDamageSource_Flags, 8u};
void Gd__gd_core__CoreDamageSource::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_minDamage = gd::GdVal::from_int(0);
    this->f_maxDamage = gd::GdVal::from_int(0);
    this->f_types = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_accuracy = gd::gd_coerce_float(gd::GdVal::from_int(100LL));
    this->f_critChancePercent = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    this->f_origin = gd::GdVal::null();
    this->f_flags = gd::GdVal::from_int(63LL);
    this->f__rng = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__CoreDamageSource::meta() const { return &META_Gd__gd_core__CoreDamageSource; }
gd::GdVal Gd__gd_core__CoreDamageSource::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_Type_855: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreDamageSource_Type);
        case SYM_GEN_Flags_1565: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreDamageSource_Flags);
        case SYM_GEN_damTypeNames_1535: return ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 3); d->set(gd_ctx.arena, gd::GdVal::from_int(0LL), gd::GdVal::from_str(&battle_string_literals[1])); d->set(gd_ctx.arena, gd::GdVal::from_int(1LL), gd::GdVal::from_str(&battle_string_literals[2])); d->set(gd_ctx.arena, gd::GdVal::from_int(2LL), gd::GdVal::from_str(&battle_string_literals[3])); return gd::GdVal::from_dict(d); })();
        case SYM_GEN_chipDamageFlags_1536: return gd::GdVal::from_int(1LL);
        case SYM_GEN_meleeFlags_1537: return gd::GdVal::from_int(63LL);
        case SYM_GEN_rangedFlags_1538: return gd::GdVal::from_int(63LL);
        case SYM_GEN_effectFlags_1539: return gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_int(1LL), gd::GdVal::from_int(8LL)), gd::GdVal::from_int(32LL));
        case SYM_GEN_unhealingFlags_1540: return gd::gd_add(gd_ctx, gd::GdVal::from_int(1LL), gd::GdVal::from_int(8LL));
        case SYM_GEN_selfDamageFlags_1541: return gd::gd_add(gd_ctx, gd::GdVal::from_int(1LL), gd::GdVal::from_int(8LL));
        default: break;
    }
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreDamageSource::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    switch (prop) {
        case SYM_GEN_Type_855: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreDamageSource_Type); return true;
        case SYM_GEN_Flags_1565: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreDamageSource_Flags); return true;
        case SYM_GEN_chipDamageFlags_1536: out = gd::GdVal::from_int(1LL); return true;
        case SYM_GEN_meleeFlags_1537: out = gd::GdVal::from_int(63LL); return true;
        case SYM_GEN_rangedFlags_1538: out = gd::GdVal::from_int(63LL); return true;
        default: break;
    }
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreDamageSource::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_minDamage_1542: out = this->f_minDamage; return true;
        case SYM_GEN_maxDamage_1543: out = this->f_maxDamage; return true;
        case SYM_GEN_types_1544: out = this->f_types; return true;
        case SYM_GEN_accuracy_1545: out = this->f_accuracy; return true;
        case SYM_GEN_critChancePercent_15: out = this->f_critChancePercent; return true;
        case SYM_GEN_origin_1546: out = this->f_origin; return true;
        case SYM_GEN_flags_1547: out = this->f_flags; return true;
        case SYM_GEN__rng_1548: out = this->f__rng; return true;
        case SYM_GEN_Type_855: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreDamageSource_Type); return true;
        case SYM_GEN_Flags_1565: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreDamageSource_Flags); return true;
        case SYM_GEN_damTypeNames_1535: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_chipDamageFlags_1536: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_meleeFlags_1537: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_rangedFlags_1538: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_effectFlags_1539: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_unhealingFlags_1540: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_selfDamageFlags_1541: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreDamageSource::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_minDamage_1542: this->f_minDamage = gd::gd_coerce_int(val); return true;
        case SYM_GEN_maxDamage_1543: this->f_maxDamage = gd::gd_coerce_int(val); return true;
        case SYM_GEN_types_1544: this->f_types = val; return true;
        case SYM_GEN_accuracy_1545: this->f_accuracy = gd::gd_coerce_float(val); return true;
        case SYM_GEN_critChancePercent_15: this->f_critChancePercent = gd::gd_coerce_float(val); return true;
        case SYM_GEN_origin_1546: this->f_origin = val; return true;
        case SYM_GEN_flags_1547: this->f_flags = val; return true;
        case SYM_GEN__rng_1548: this->f__rng = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreDamageSource::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_fromDamageSource_1549: return true;
        case SYM_GEN_setItem_1550: return true;
        case SYM_GEN_init_1022: return true;
        case SYM_GEN_hasType_79: return true;
        case SYM_GEN_setDamage_1551: return true;
        case SYM_GEN_addDamage_1552: return true;
        case SYM_GEN_getCritChancePercent_178: return true;
        case SYM_GEN_updateItem_1553: return true;
        case SYM_GEN_updateEffect_1554: return true;
        case SYM_GEN_addCritChancePercent_179: return true;
        case SYM_GEN_setFlag_1555: return true;
        case SYM_GEN_unsetFlag_1556: return true;
        case SYM_GEN_canMiss_1557: return true;
        case SYM_GEN_canTriggerSpikes_1532: return true;
        case SYM_GEN_canTriggerVampirism_1533: return true;
        case SYM_GEN_canBeBlocked_1558: return true;
        case SYM_GEN_canCrit_1559: return true;
        case SYM_GEN_isAttack_1560: return true;
        case SYM_GEN_isEffectDamage_1561: return true;
        case SYM_GEN_isAttackOrEffect_1562: return true;
        case SYM_GEN_canApplyLifesteal_1563: return true;
        case SYM_GEN_makeSpectral_1564: return true;
        case SYM_GEN_randDamage_159: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreDamageSource::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_fromDamageSource_1549: out = fn_fromDamageSource(args, argc); return true;
        case SYM_GEN_setItem_1550: out = fn_setItem(args, argc); return true;
        case SYM_GEN_init_1022: out = fn_init(args, argc); return true;
        case SYM_GEN_hasType_79: out = fn_hasType(args, argc); return true;
        case SYM_GEN_setDamage_1551: out = fn_setDamage(args, argc); return true;
        case SYM_GEN_addDamage_1552: out = fn_addDamage(args, argc); return true;
        case SYM_GEN_getCritChancePercent_178: out = fn_getCritChancePercent(args, argc); return true;
        case SYM_GEN_updateItem_1553: out = fn_updateItem(args, argc); return true;
        case SYM_GEN_updateEffect_1554: out = fn_updateEffect(args, argc); return true;
        case SYM_GEN_addCritChancePercent_179: out = fn_addCritChancePercent(args, argc); return true;
        case SYM_GEN_setFlag_1555: out = fn_setFlag(args, argc); return true;
        case SYM_GEN_unsetFlag_1556: out = fn_unsetFlag(args, argc); return true;
        case SYM_GEN_canMiss_1557: out = fn_canMiss(args, argc); return true;
        case SYM_GEN_canTriggerSpikes_1532: out = fn_canTriggerSpikes(args, argc); return true;
        case SYM_GEN_canTriggerVampirism_1533: out = fn_canTriggerVampirism(args, argc); return true;
        case SYM_GEN_canBeBlocked_1558: out = fn_canBeBlocked(args, argc); return true;
        case SYM_GEN_canCrit_1559: out = fn_canCrit(args, argc); return true;
        case SYM_GEN_isAttack_1560: out = fn_isAttack(args, argc); return true;
        case SYM_GEN_isEffectDamage_1561: out = fn_isEffectDamage(args, argc); return true;
        case SYM_GEN_isAttackOrEffect_1562: out = fn_isAttackOrEffect(args, argc); return true;
        case SYM_GEN_canApplyLifesteal_1563: out = fn_canApplyLifesteal(args, argc); return true;
        case SYM_GEN_makeSpectral_1564: out = fn_makeSpectral(args, argc); return true;
        case SYM_GEN_randDamage_159: out = fn_randDamage(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreDamageSource::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return false;
}
gd::GdVal Gd__gd_core__CoreDamageSource::fn_fromDamageSource(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_otherDamSource = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_minDamage = gd::gd_coerce_int(gd::native_inline_get_prop(gd_ctx, lv_otherDamSource, SYM_GEN_minDamage_1542));
    this->f_maxDamage = gd::gd_coerce_int(gd::native_inline_get_prop(gd_ctx, lv_otherDamSource, SYM_GEN_maxDamage_1543));
    this->f_types = gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_otherDamSource, SYM_GEN_types_1544), gd::SYM_duplicate, nullptr, 0);
    this->f_accuracy = gd::gd_coerce_float(gd::native_inline_get_prop(gd_ctx, lv_otherDamSource, SYM_GEN_accuracy_1545));
    this->f_critChancePercent = gd::gd_coerce_float(gd::native_inline_get_prop(gd_ctx, lv_otherDamSource, SYM_GEN_critChancePercent_15));
    this->f_flags = gd::native_inline_get_prop(gd_ctx, lv_otherDamSource, SYM_GEN_flags_1547);
    this->f_origin = gd::native_inline_get_prop(gd_ctx, lv_otherDamSource, SYM_GEN_origin_1546);
    return gd::GdVal::from_obj(this);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreDamageSource::fn_setItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__type = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv__type, gd::GdVal::null())))) {
        this->f_types = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv__type}));
    }
    else {
        if (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(20LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, this->f_types, gd::SYM_push_back, _ca, 1); })();
        }
        if (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(19LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, this->f_types, gd::SYM_push_back, _ca, 1); })();
        }
        if (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(21LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, this->f_types, gd::SYM_push_back, _ca, 1); })();
        }
        if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, this->f_types, gd::SYM_empty, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, this->f_types, gd::SYM_push_back, _ca, 1); })();
        }
    }
    if (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return this->fn_hasType(_ca, 1); })())) {
        this->f_flags = Gd__gd_core__CoreDamageSource::get_static_const_or_enum(gd_ctx, SYM_GEN_meleeFlags_1537);
    }
    else if (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return this->fn_hasType(_ca, 1); })())) {
        this->f_flags = Gd__gd_core__CoreDamageSource::get_static_const_or_enum(gd_ctx, SYM_GEN_rangedFlags_1538);
    }
    else if (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(3LL)}; return this->fn_hasType(_ca, 1); })())) {
        this->f_flags = Gd__gd_core__CoreDamageSource::get_static_const_or_enum(gd_ctx, SYM_GEN_selfDamageFlags_1541);
    }
    else {
        this->f_flags = Gd__gd_core__CoreDamageSource::get_static_const_or_enum(gd_ctx, SYM_GEN_effectFlags_1539);
    }
    return ([&]() { gd::GdVal _ca[] = {lv_item, this->f_types, gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getMinDamage_156, nullptr, 0), gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getMaxDamage_157, nullptr, 0), gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getAccuracy_194, nullptr, 0)}; return this->fn_init(_ca, 5); })();
    return gd::GdVal::null();
    }
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__type = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv__type, gd::GdVal::null())))) {
        this->f_types = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv__type}));
    }
    else {
        if (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(20LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, this->f_types, gd::SYM_push_back, _ca, 1); })();
        }
        if (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(19LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, this->f_types, gd::SYM_push_back, _ca, 1); })();
        }
        if (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(21LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, this->f_types, gd::SYM_push_back, _ca, 1); })();
        }
        if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, this->f_types, gd::SYM_empty, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, this->f_types, gd::SYM_push_back, _ca, 1); })();
        }
    }
    if (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasType_79, _ca, 1); })())) {
        this->f_flags = Gd__gd_core__CoreDamageSource::get_static_const_or_enum(gd_ctx, SYM_GEN_meleeFlags_1537);
    }
    else if (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasType_79, _ca, 1); })())) {
        this->f_flags = Gd__gd_core__CoreDamageSource::get_static_const_or_enum(gd_ctx, SYM_GEN_rangedFlags_1538);
    }
    else if (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(3LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasType_79, _ca, 1); })())) {
        this->f_flags = Gd__gd_core__CoreDamageSource::get_static_const_or_enum(gd_ctx, SYM_GEN_selfDamageFlags_1541);
    }
    else {
        this->f_flags = Gd__gd_core__CoreDamageSource::get_static_const_or_enum(gd_ctx, SYM_GEN_effectFlags_1539);
    }
    return ([&]() { gd::GdVal _ca[] = {lv_item, this->f_types, gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getMinDamage_156, nullptr, 0), gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getMaxDamage_157, nullptr, 0), gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getAccuracy_194, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_init_1022, _ca, 5); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreDamageSource::fn_init(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv__origin = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv__type = (_argc > 1) ? _args[1] : (gd::GdVal::from_int(2LL));
    gd::GdVal lv__minDamage = (_argc > 2) ? _args[2] : (gd::GdVal::from_int(0LL));
    gd::GdVal lv__maxDamage = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv__accuracy = (_argc > 4) ? _args[4] : (gd::GdVal::from_int(100LL));
    this->f_origin = lv__origin;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_is_builtin(lv__type, 19)))) {
        this->f_types = lv__type;
    }
    else {
        this->f_types = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv__type}));
    }
    (void)([&]() { gd::GdVal _ca[] = {lv__minDamage, lv__maxDamage}; return this->fn_setDamage(_ca, 2); })();
    this->f_accuracy = gd::gd_coerce_float(lv__accuracy);
    return gd::GdVal::from_obj(this);
    return gd::GdVal::null();
    }
    gd::GdVal lv__origin = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv__type = (_argc > 1) ? _args[1] : (gd::GdVal::from_int(2LL));
    gd::GdVal lv__minDamage = (_argc > 2) ? _args[2] : (gd::GdVal::from_int(0LL));
    gd::GdVal lv__maxDamage = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv__accuracy = (_argc > 4) ? _args[4] : (gd::GdVal::from_int(100LL));
    this->f_origin = lv__origin;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_is_builtin(lv__type, 19)))) {
        this->f_types = lv__type;
    }
    else {
        this->f_types = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv__type}));
    }
    (void)([&]() { gd::GdVal _ca[] = {lv__minDamage, lv__maxDamage}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setDamage_1551, _ca, 2); })();
    this->f_accuracy = gd::gd_coerce_float(lv__accuracy);
    return gd::GdVal::from_obj(this);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreDamageSource::fn_hasType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv__type = gd::gd_coerce_int(lv__type);
    return gd::gd_in(lv__type, this->f_types);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreDamageSource::fn_setDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__minDamage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__maxDamage = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    this->f_minDamage = gd::gd_coerce_int(lv__minDamage);
    if (gd::native_scalar_truth(lv__maxDamage)) {
        this->f_maxDamage = gd::gd_coerce_int(lv__maxDamage);
    }
    else {
        this->f_maxDamage = gd::gd_coerce_int(this->f_minDamage);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreDamageSource::fn_addDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_minDamage = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_minDamage, lv__damage));
    this->f_maxDamage = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_maxDamage, lv__damage));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreDamageSource::fn_getCritChancePercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_clamp(this->f_critChancePercent, gd::GdVal::from_float(0.0), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreDamageSource::fn_updateItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_accuracy = gd::gd_coerce_float(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getAccuracy_194, nullptr, 0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreDamageSource::fn_updateEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_damage = (_argc > 1) ? _args[1] : gd::GdVal::null();
    this->f_origin = lv_item;
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_damage}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getModifiedEffectDamage_160, _ca, 1); })()}; return this->fn_setDamage(_ca, 1); })();
    this->f_critChancePercent = gd::gd_coerce_float(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getCritChancePercent_178, nullptr, 0));
    return gd::GdVal::null();
    }
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_damage = (_argc > 1) ? _args[1] : gd::GdVal::null();
    this->f_origin = lv_item;
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_damage}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getModifiedEffectDamage_160, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setDamage_1551, _ca, 1); })();
    this->f_critChancePercent = gd::gd_coerce_float(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getCritChancePercent_178, nullptr, 0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreDamageSource::fn_addCritChancePercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__critChance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_critChancePercent = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_critChancePercent, lv__critChance));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreDamageSource::fn_setFlag(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_flag = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_flags = gd::gd_bitor(this->f_flags, lv_flag);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreDamageSource::fn_unsetFlag(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_flag = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_flags = gd::gd_bitand(this->f_flags, gd::gd_bitnot(lv_flag));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreDamageSource::fn_canMiss(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_bitand(this->f_flags, gd::GdVal::from_int(16LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreDamageSource::fn_canTriggerSpikes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_bitand(this->f_flags, gd::GdVal::from_int(2LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreDamageSource::fn_canTriggerVampirism(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_bitand(this->f_flags, gd::GdVal::from_int(4LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreDamageSource::fn_canBeBlocked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_bitand(this->f_flags, gd::GdVal::from_int(1LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreDamageSource::fn_canCrit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_bitand(this->f_flags, gd::GdVal::from_int(32LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreDamageSource::fn_isAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    return (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return this->fn_hasType(_ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return this->fn_hasType(_ca, 1); })())));
    return gd::GdVal::null();
    }
    return (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasType_79, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreDamageSource::fn_isEffectDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    return (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return this->fn_hasType(_ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(98LL)}; return this->fn_hasType(_ca, 1); })())));
    return gd::GdVal::null();
    }
    return (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(98LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasType_79, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreDamageSource::fn_isAttackOrEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    return (gd::native_scalar_truth(this->fn_isAttack(nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(this->fn_isEffectDamage(nullptr, 0))));
    return gd::GdVal::null();
    }
    return (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isAttack_1560, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEffectDamage_1561, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreDamageSource::fn_canApplyLifesteal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    return (gd::native_scalar_truth(this->fn_isAttack(nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return this->fn_hasType(_ca, 1); })())));
    return gd::GdVal::null();
    }
    return (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isAttack_1560, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasType_79, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreDamageSource::fn_makeSpectral(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return this->fn_unsetFlag(_ca, 1); })();
    return gd::GdVal::null();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_unsetFlag_1556, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreDamageSource::fn_randDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd_ctx.native_event_kernel) {
    if (gd::native_scalar_truth((gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_origin, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[4])}; return gd::native_inline_call(gd_ctx, this->f_origin, gd::SYM_has_method, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        this->f_critChancePercent = gd::gd_coerce_float(gd::native_inline_call(gd_ctx, this->f_origin, SYM_GEN_getCritChancePercent_178, nullptr, 0));
        if (gd::native_scalar_truth(this->fn_isAttack(nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, this->f_origin, SYM_GEN_getMinDamage_156, _ca, 1); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, this->f_origin, SYM_GEN_getMaxDamage_157, _ca, 1); })()}; return this->fn_setDamage(_ca, 2); })();
        }
        return ([&]() { gd::GdVal _ca[] = {this->f_minDamage, this->f_maxDamage}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_origin, SYM_GEN_damageRangeRng_32), SYM_GEN_randIntRange_1764, _ca, 2); })();
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {this->f_minDamage, this->f_maxDamage}; return native_event_call<Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::fn_randi_range>(gd_ctx, this->f__rng, gd::SYM_randi_range, _ca, 2); })();
    }
    return gd::GdVal::null();
    }
    if (gd::native_scalar_truth((gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_origin, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[4])}; return gd::native_inline_call(gd_ctx, this->f_origin, gd::SYM_has_method, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        this->f_critChancePercent = gd::gd_coerce_float(gd::native_inline_call(gd_ctx, this->f_origin, SYM_GEN_getCritChancePercent_178, nullptr, 0));
        if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isAttack_1560, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, this->f_origin, SYM_GEN_getMinDamage_156, _ca, 1); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, this->f_origin, SYM_GEN_getMaxDamage_157, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setDamage_1551, _ca, 2); })();
        }
        return ([&]() { gd::GdVal _ca[] = {this->f_minDamage, this->f_maxDamage}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_origin, SYM_GEN_damageRangeRng_32), SYM_GEN_randIntRange_1764, _ca, 2); })();
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {this->f_minDamage, this->f_maxDamage}; return gd::native_inline_call(gd_ctx, this->f__rng, gd::SYM_randi_range, _ca, 2); })();
    }
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreDamageSource(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__CoreDamageSource>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,32u); return object; }
const gd::GdClassMeta META_Gd__gd_core__CoreDamageSource = {CLS_Gd__gd_core__CoreDamageSource, "CoreDamageSource", "res://gd_core/CoreDamageSource.gd", nullptr, false, _alloc_Gd__gd_core__CoreDamageSource, &Gd__gd_core__CoreDamageSource::get_static_prop_fn, &Gd__gd_core__CoreDamageSource::call_static_fn};

void Gd__gd_core__CritwoodStaff::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
    this->f_buffActive = gd::GdVal::from_bool(false);
    this->f_activationParticles = gd::GdVal::null();
    this->f_critTimer = gd::GdVal::null();
    this->f_manaCost = gd::GdVal::null();
    this->f_tempDamBonus = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__CritwoodStaff::meta() const { return &META_Gd__gd_core__CritwoodStaff; }
gd::GdVal Gd__gd_core__CritwoodStaff::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__CritwoodStaff::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CritwoodStaff::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_buffActive_1813: out = this->f_buffActive; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_critTimer_1814: out = this->f_critTimer; return true;
        case SYM_GEN_manaCost_1815: out = this->f_manaCost; return true;
        case SYM_GEN_tempDamBonus_1816: out = this->f_tempDamBonus; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__CritwoodStaff::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffActive_1813: this->f_buffActive = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_critTimer_1814: this->f_critTimer = val; return true;
        case SYM_GEN_manaCost_1815: this->f_manaCost = val; return true;
        case SYM_GEN_tempDamBonus_1816: this->f_tempDamBonus = val; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__CritwoodStaff::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_buffEnded_1817: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__CritwoodStaff::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_buffEnded_1817: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__CritwoodStaff::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__CritwoodStaff::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CritwoodStaff::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0), this->f_manaCost)))) {
        if (gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(this->f_buffActive)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 2); })();
            {
                gd::GdVal _t1475 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
                gd::GdArr* _t1476 = (_t1475.kind == gd::GdVal::Kind::Arr) ? _t1475.arr : nullptr;
                uint32_t _len__t1477 = _t1476 ? _t1476->len : 0u;
                for (uint32_t _t1477 = 0; _t1477 < _len__t1477; ++_t1477) {
                    gd::GdVal lv_item = _t1476->data[_t1477];
                    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(100LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addCritChancePercent_179, _ca, 1); })();
                }
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_332, _ca, 1); })();
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_add(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), this->f_tempDamBonus));
        gd::GdVal lv_critBuffDur = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[5])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_critTimer, lv_critBuffDur}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_changeTimer_1796, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CritwoodStaff::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1478 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
        gd::GdArr* _t1479 = (_t1478.kind == gd::GdVal::Kind::Arr) ? _t1478.arr : nullptr;
        uint32_t _len__t1480 = _t1479 ? _t1479->len : 0u;
        for (uint32_t _t1480 = 0; _t1480 < _len__t1480; ++_t1480) {
            gd::GdVal lv_item = _t1479->data[_t1480];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(100LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_reduceCritChancePercent_180, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CritwoodStaff::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_critTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CritwoodStaff::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CritwoodStaff::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(lv_active)) {
    }
    else {
    }
    this->f_buffActive = lv_active;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CritwoodStaff::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_critTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[6]), gd::GdVal::from_str(&battle_string_literals[7]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    this->f_manaCost = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0);
    this->f_tempDamBonus = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CritwoodStaff(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__CritwoodStaff>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,49u); return object; }
const gd::GdClassMeta META_Gd__gd_core__CritwoodStaff = {CLS_Gd__gd_core__CritwoodStaff, "CritwoodStaff", "res://gd_core/CritwoodStaff.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__CritwoodStaff, &Gd__gd_core__CritwoodStaff::get_static_prop_fn, &Gd__gd_core__CritwoodStaff::call_static_fn};

void Gd__gd_core_items__Pan::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_bonusDamage = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core_items__Pan::meta() const { return &META_Gd__gd_core_items__Pan; }
gd::GdVal Gd__gd_core_items__Pan::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Pan::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Pan::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_bonusDamage_904: out = this->f_bonusDamage; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Pan::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bonusDamage_904: this->f_bonusDamage = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Pan::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPreCombatStart_125: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Pan::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPreCombatStart_125: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Pan::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Pan::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Pan::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_161, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Pan::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Pan(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Pan>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,615u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Pan = {CLS_Gd__gd_core_items__Pan, "Pan", "res://gd_core_items/Pan.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Pan, &Gd__gd_core_items__Pan::get_static_prop_fn, &Gd__gd_core_items__Pan::call_static_fn};

void Gd__gd_core__HeartContainer::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_activated = gd::GdVal::from_bool(false);
    this->f_regenNeeded = gd::GdVal::null();
    this->f_fillAnimation = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__HeartContainer::meta() const { return &META_Gd__gd_core__HeartContainer; }
gd::GdVal Gd__gd_core__HeartContainer::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__HeartContainer::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__HeartContainer::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activated_1314: out = this->f_activated; return true;
        case SYM_GEN_regenNeeded_942: out = this->f_regenNeeded; return true;
        case SYM_GEN_fillAnimation_1890: out = this->f_fillAnimation; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__HeartContainer::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activated_1314: this->f_activated = val; return true;
        case SYM_GEN_regenNeeded_942: this->f_regenNeeded = val; return true;
        case SYM_GEN_fillAnimation_1890: this->f_fillAnimation = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__HeartContainer::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onRegenChanged_1891: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__HeartContainer::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onRegenChanged_1891: out = fn_onRegenChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__HeartContainer::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__HeartContainer::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[8]), gd::GdVal::from_str(&battle_string_literals[9])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeartContainer::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeartContainer::fn_onRegenChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::native_scalar_truth((gd::native_scalar_truth((gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(this->f_activated)))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRegeneration_1233, nullptr, 0), this->f_regenNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_regenNeeded, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_346, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[10])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_267, nullptr, 0), gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_addHealingEfficiency_1182, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeartContainer::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeartContainer::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_filled = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_activated, lv_filled)))) {
        return gd::GdVal::null();
    }
    this->f_activated = lv_filled;
    if (gd::native_scalar_truth(lv_filled)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeartContainer::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_regenNeeded = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__HeartContainer(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__HeartContainer>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,81u); return object; }
const gd::GdClassMeta META_Gd__gd_core__HeartContainer = {CLS_Gd__gd_core__HeartContainer, "HeartContainer", "res://gd_core/HeartContainer.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__HeartContainer, &Gd__gd_core__HeartContainer::get_static_prop_fn, &Gd__gd_core__HeartContainer::call_static_fn};

void Gd__gd_core__LuckyBow::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Bow::init_fields(gd_ctx);
    this->f_extraAttack = gd::GdVal::from_bool(false);
}
const gd::GdClassMeta* Gd__gd_core__LuckyBow::meta() const { return &META_Gd__gd_core__LuckyBow; }
gd::GdVal Gd__gd_core__LuckyBow::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Bow::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__LuckyBow::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__LuckyBow::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_extraAttack_1917: out = this->f_extraAttack; return true;
        default: break;
    }
    return Gd__gd_core__Bow::get_prop(prop, out);
}
bool Gd__gd_core__LuckyBow::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_extraAttack_1917: this->f_extraAttack = val; return true;
        default: break;
    }
    return Gd__gd_core__Bow::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__LuckyBow::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onWeaponAttacked_950: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Bow::has_own_method(m);
}
bool Gd__gd_core__LuckyBow::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onWeaponAttacked_950: out = fn_onWeaponAttacked(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Bow::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__LuckyBow::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Bow::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__LuckyBow::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LuckyBow::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LuckyBow::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_116, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_res = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_220, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 1); })();
        if (gd::native_scalar_truth(this->f_extraAttack)) {
            gd::GdVal lv_res2 = ([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, lv_res, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_220, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_res2}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false), gd::GdVal::from_bool(false), gd::native_inline_get_prop(gd_ctx, lv_res2, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LuckyBow::fn_onWeaponAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_wasCriticalHit_1524, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(false), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LuckyBow::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LuckyBow::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__extraAttack = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(lv__extraAttack)) {
    }
    else {
    }
    this->f_extraAttack = lv__extraAttack;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LuckyBow::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Bow::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__LuckyBow(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__LuckyBow>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,98u); return object; }
const gd::GdClassMeta META_Gd__gd_core__LuckyBow = {CLS_Gd__gd_core__LuckyBow, "LuckyBow", "res://gd_core/LuckyBow.gd", &META_Gd__gd_core__Bow, false, _alloc_Gd__gd_core__LuckyBow, &Gd__gd_core__LuckyBow::get_static_prop_fn, &Gd__gd_core__LuckyBow::call_static_fn};

void Gd__gd_core__Piggybank::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_piggyPinataDescriptor = gd::GdVal::null();
    this->f_hammerDescriptor = gd::GdVal::null();
    this->f_thorsHammerDescriptor = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__Piggybank::meta() const { return &META_Gd__gd_core__Piggybank; }
gd::GdVal Gd__gd_core__Piggybank::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Piggybank::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Piggybank::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_piggyPinataDescriptor_1918: out = this->f_piggyPinataDescriptor; return true;
        case SYM_GEN_hammerDescriptor_1919: out = this->f_hammerDescriptor; return true;
        case SYM_GEN_thorsHammerDescriptor_1920: out = this->f_thorsHammerDescriptor; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__Piggybank::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_piggyPinataDescriptor_1918: this->f_piggyPinataDescriptor = val; return true;
        case SYM_GEN_hammerDescriptor_1919: this->f_hammerDescriptor = val; return true;
        case SYM_GEN_thorsHammerDescriptor_1920: this->f_thorsHammerDescriptor = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Piggybank::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_explodeRandomly_1921: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_hasPinata_1922: return true;
        case SYM_GEN_isSmashRecipe_1923: return true;
        case SYM_GEN_getFusionItemName_836: return true;
        case SYM_GEN_allowGeneratingFusionItem_846: return true;
        case SYM_GEN_explode_1924: return true;
        case SYM_GEN_finishFusing_845: return true;
        case SYM_GEN_getShopPriority_853: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Piggybank::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_explodeRandomly_1921: out = fn_explodeRandomly(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_hasPinata_1922: out = fn_hasPinata(args, argc); return true;
        case SYM_GEN_isSmashRecipe_1923: out = fn_isSmashRecipe(args, argc); return true;
        case SYM_GEN_getFusionItemName_836: out = fn_getFusionItemName(args, argc); return true;
        case SYM_GEN_allowGeneratingFusionItem_846: out = fn_allowGeneratingFusionItem(args, argc); return true;
        case SYM_GEN_explode_1924: out = fn_explode(args, argc); return true;
        case SYM_GEN_finishFusing_845: out = fn_finishFusing(args, argc); return true;
        case SYM_GEN_getShopPriority_853: out = fn_getShopPriority(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Piggybank::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Piggybank::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveGold_754, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_explodeRandomly_1921, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Piggybank::fn_explodeRandomly(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth((gd::native_scalar_truth((gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isBaseItem_258, nullptr, 0)))) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isBoundAsIngredient_260, nullptr, 0))))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasPinata_1922, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        if (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, this->f_piggyPinataDescriptor, SYM_GEN_shopChance_1683)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_flipPercent_1736, _ca, 1); })())) {
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_explode_1924, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_removeItem_1619, _ca, 1); })();
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_discard_764, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Piggybank::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasStartofBattle_126, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Piggybank::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[10])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_381, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Piggybank::fn_hasPinata(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {this->f_piggyPinataDescriptor}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_isItemInInventory_1671, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Piggybank::fn_isSmashRecipe(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_array_index(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_curRecipe, SYM_GEN_ingredients_2867), gd::GdVal::from_int(0LL)), this->f_hammerDescriptor))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_array_index(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_curRecipe, SYM_GEN_ingredients_2867), gd::GdVal::from_int(0LL)), this->f_thorsHammerDescriptor)))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Piggybank::fn_getFusionItemName(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth((gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isSmashRecipe_1923, nullptr, 0)) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasPinata_1922, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[11])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_tr_2826, _ca, 1); })();
    }
    return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_getFusionItemName_836, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Piggybank::fn_allowGeneratingFusionItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth((gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isSmashRecipe_1923, nullptr, 0)) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasPinata_1922, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        return gd::GdVal::from_bool(false);
    }
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Piggybank::fn_explode(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Piggybank::fn_finishFusing(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isSmashRecipe_1923, nullptr, 0))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_explode_1924, nullptr, 0);
    }
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_finishFusing_845, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Piggybank::fn_getShopPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(-10000LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Piggybank::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_piggyPinataDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[12])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_hammerDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[13])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_thorsHammerDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[14])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Piggybank(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__Piggybank>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,112u); return object; }
const gd::GdClassMeta META_Gd__gd_core__Piggybank = {CLS_Gd__gd_core__Piggybank, "Piggybank", "res://gd_core/Piggybank.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__Piggybank, &Gd__gd_core__Piggybank::get_static_prop_fn, &Gd__gd_core__Piggybank::call_static_fn};

void Gd__gd_core__RubyChonk::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
    this->f_heatThresholdReached = gd::GdVal::from_bool(false);
    this->f_hasStunned = gd::GdVal::from_bool(false);
    this->f_activationParticles = gd::GdVal::null();
    this->f_heatThreshold = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__RubyChonk::meta() const { return &META_Gd__gd_core__RubyChonk; }
gd::GdVal Gd__gd_core__RubyChonk::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__RubyChonk::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__RubyChonk::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_heatThresholdReached_1973: out = this->f_heatThresholdReached; return true;
        case SYM_GEN_hasStunned_1974: out = this->f_hasStunned; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_heatThreshold_1975: out = this->f_heatThreshold; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__RubyChonk::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_heatThresholdReached_1973: this->f_heatThresholdReached = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_hasStunned_1974: this->f_hasStunned = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_heatThreshold_1975: this->f_heatThreshold = val; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__RubyChonk::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onHeatChanged_913: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN_getCraftingOffset_850: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__RubyChonk::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onHeatChanged_913: out = fn_onHeatChanged(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_getCraftingOffset_850: out = fn_getCraftingOffset(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__RubyChonk::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__RubyChonk::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[15]), gd::GdVal::from_str(&battle_string_literals[16])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RubyChonk::fn_onHeatChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(this->f_heatThresholdReached)))) {
        if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getHeat_1251, nullptr, 0), this->f_heatThreshold)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(false), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 3); })();
        }
    }
    else if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getHeat_1251, nullptr, 0), this->f_heatThreshold)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false), gd::GdVal::from_bool(false), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RubyChonk::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_116, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        this->f_hasStunned = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
        gd::GdVal lv_res = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_220, nullptr, 0);
        if (gd::native_scalar_truth(this->f_hasStunned)) {
            (void)([&]() { gd::GdVal _ca[] = {lv_res, gd::GdVal::from_bool(false), gd::GdVal::from_bool(false), gd::native_inline_get_prop(gd_ctx, Gd__gd_core__RubyChonk::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Tackle_2753)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 4); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {lv_res, gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 2); })();
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(30.0)), gd::GdVal::from_float(30.0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_bare_randf_range_1743, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(100.0)), gd::GdVal::from_float(100.0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_bare_randf_range_1743, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(5.0)), gd::GdVal::from_float(5.0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_bare_randf_range_1743, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RubyChonk::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 2); })();
        if (gd::native_scalar_truth(this->f_heatThresholdReached)) {
            if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[17])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_330, _ca, 2); })();
                this->f_hasStunned = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RubyChonk::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RubyChonk::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__heatThresholdReached = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(lv__heatThresholdReached)) {
    }
    else {
    }
    this->f_heatThresholdReached = gd::gd_coerce_bool(lv__heatThresholdReached);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RubyChonk::fn_getCraftingOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1481 = lv_forDirection;
        if (gd::native_scalar_eq(_t1481, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
        else if (gd::native_scalar_eq(_t1481, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
        else if (gd::native_scalar_eq(_t1481, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_LEFT))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
        else if (gd::native_scalar_eq(_t1481, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_RIGHT))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RubyChonk::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_heatThreshold = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__RubyChonk(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__RubyChonk>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,130u); return object; }
const gd::GdClassMeta META_Gd__gd_core__RubyChonk = {CLS_Gd__gd_core__RubyChonk, "RubyChonk", "res://gd_core/RubyChonk.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__RubyChonk, &Gd__gd_core__RubyChonk::get_static_prop_fn, &Gd__gd_core__RubyChonk::call_static_fn};

void Gd__gd_core__StrongDemonicFlask::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Potion::init_fields(gd_ctx);
    this->f_healingReductionTimer = gd::GdVal::null();
    this->f_healingDebuff = gd::GdVal::null();
    this->f_damPerDebuff = gd::GdVal::null();
    this->f_playerHealthThreshold = gd::GdVal::null();
    this->f_opponentHealthThreshold = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__StrongDemonicFlask::meta() const { return &META_Gd__gd_core__StrongDemonicFlask; }
gd::GdVal Gd__gd_core__StrongDemonicFlask::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Potion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__StrongDemonicFlask::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__StrongDemonicFlask::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_healingReductionTimer_1987: out = this->f_healingReductionTimer; return true;
        case SYM_GEN_healingDebuff_1988: out = this->f_healingDebuff; return true;
        case SYM_GEN_damPerDebuff_1827: out = this->f_damPerDebuff; return true;
        case SYM_GEN_playerHealthThreshold_1989: out = this->f_playerHealthThreshold; return true;
        case SYM_GEN_opponentHealthThreshold_1990: out = this->f_opponentHealthThreshold; return true;
        default: break;
    }
    return Gd__gd_core__Potion::get_prop(prop, out);
}
bool Gd__gd_core__StrongDemonicFlask::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_healingReductionTimer_1987: this->f_healingReductionTimer = val; return true;
        case SYM_GEN_healingDebuff_1988: this->f_healingDebuff = val; return true;
        case SYM_GEN_damPerDebuff_1827: this->f_damPerDebuff = val; return true;
        case SYM_GEN_playerHealthThreshold_1989: this->f_playerHealthThreshold = val; return true;
        case SYM_GEN_opponentHealthThreshold_1990: this->f_opponentHealthThreshold = val; return true;
        default: break;
    }
    return Gd__gd_core__Potion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__StrongDemonicFlask::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canDamage_89: return true;
        case SYM_GEN_onTriggerPotion_1849: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPlayerDamaged_1991: return true;
        case SYM_GEN_onOpponentDamaged_1992: return true;
        case SYM_GEN_drinkStrongDemonicFlask_1993: return true;
        case SYM_GEN_healingReductionTimeout_1994: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Potion::has_own_method(m);
}
bool Gd__gd_core__StrongDemonicFlask::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canDamage_89: out = fn_canDamage(args, argc); return true;
        case SYM_GEN_onTriggerPotion_1849: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPlayerDamaged_1991: out = fn_onPlayerDamaged(args, argc); return true;
        case SYM_GEN_onOpponentDamaged_1992: out = fn_onOpponentDamaged(args, argc); return true;
        case SYM_GEN_drinkStrongDemonicFlask_1993: out = fn_drinkStrongDemonicFlask(args, argc); return true;
        case SYM_GEN_healingReductionTimeout_1994: out = fn_healingReductionTimeout(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Potion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__StrongDemonicFlask::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Potion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__StrongDemonicFlask::fn_canDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StrongDemonicFlask::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {this->f_healingDebuff}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_reduceHealingEfficiency_1183, _ca, 1); })();
    gd::GdVal lv_dam = gd::gd_mul(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_getDebuffStacks_1216, nullptr, 0), this->f_damPerDebuff);
    lv_dam = gd::gd_ceil(lv_dam);
    (void)([&]() { gd::GdVal _ca[] = {lv_dam, gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[18])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::GdVal::from_float(100.0)), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealLife_329, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[5])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, this->f_healingReductionTimer, SYM_GEN_start_1779, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StrongDemonicFlask::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[19]), gd::GdVal::from_str(&battle_string_literals[20])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[19]), gd::GdVal::from_str(&battle_string_literals[21])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StrongDemonicFlask::fn_onPlayerDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_healthChange = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_923, nullptr, 0))) {
        return gd::GdVal::null();
    }
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRelativeHealth_302, nullptr, 0), this->f_playerHealthThreshold)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drinkStrongDemonicFlask_1993, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StrongDemonicFlask::fn_onOpponentDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_healthChange = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_923, nullptr, 0))) {
        return gd::GdVal::null();
    }
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_getRelativeHealth_302, nullptr, 0), this->f_opponentHealthThreshold)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drinkStrongDemonicFlask_1993, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StrongDemonicFlask::fn_drinkStrongDemonicFlask(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drink_1847, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_triggerPotion_1850, _ca, 1); })();
    gd::GdVal lv_affected = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0);
    if (gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_affected, gd::SYM_empty, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL)), SYM_GEN_triggerPotion_1850, _ca, 1); })();
        (void)gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL)), SYM_GEN_miniActivate_470, nullptr, 0);
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StrongDemonicFlask::fn_healingReductionTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_healingDebuff}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_addHealingEfficiency_1182, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StrongDemonicFlask::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_healingReductionTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StrongDemonicFlask::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Potion::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_healingReductionTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[22]), gd::GdVal::from_str(&battle_string_literals[23]), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    this->f_healingDebuff = gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0), gd::GdVal::from_float(100.0));
    this->f_damPerDebuff = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[24])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_playerHealthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[25])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    this->f_opponentHealthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[26])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__StrongDemonicFlask(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__StrongDemonicFlask>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,146u); return object; }
const gd::GdClassMeta META_Gd__gd_core__StrongDemonicFlask = {CLS_Gd__gd_core__StrongDemonicFlask, "StrongDemonicFlask", "res://gd_core/StrongDemonicFlask.gd", &META_Gd__gd_core__Potion, false, _alloc_Gd__gd_core__StrongDemonicFlask, &Gd__gd_core__StrongDemonicFlask::get_static_prop_fn, &Gd__gd_core__StrongDemonicFlask::call_static_fn};

void Gd__gd_core__VillainSword::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__VillainSword::meta() const { return &META_Gd__gd_core__VillainSword; }
gd::GdVal Gd__gd_core__VillainSword::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__VillainSword::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__VillainSword::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__VillainSword::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__VillainSword::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPreCombatStart_125: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__VillainSword::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPreCombatStart_125: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__VillainSword::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__VillainSword::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0)) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), SYM_GEN_isMeleeWeapon_1722, nullptr, 0))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__VillainSword::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1482 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1483 = (_t1482.kind == gd::GdVal::Kind::Arr) ? _t1482.arr : nullptr;
        uint32_t _len__t1484 = _t1483 ? _t1483->len : 0u;
        for (uint32_t _t1484 = 0; _t1484 < _len__t1484; ++_t1484) {
            gd::GdVal lv_item = _t1483->data[_t1484];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_reduceBonusDamage_310, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_161, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__VillainSword::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__VillainSword(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core__VillainSword>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,158u); return object; }
const gd::GdClassMeta META_Gd__gd_core__VillainSword = {CLS_Gd__gd_core__VillainSword, "VillainSword", "res://gd_core/VillainSword.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__VillainSword, &Gd__gd_core__VillainSword::get_static_prop_fn, &Gd__gd_core__VillainSword::call_static_fn};

void Gd__gd_core_items__Food::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Food::meta() const { return &META_Gd__gd_core_items__Food; }
gd::GdVal Gd__gd_core_items__Food::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Food::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Food::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Food::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Food::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_prepare_122: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Food::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_prepare_122: out = fn_prepare(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Food::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Food::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::native_inline_get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), this->f_descriptor)))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Food::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_prepare_122, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0), gd::GdVal::from_float(0.1))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Food::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Food(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Food>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,570u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Food = {CLS_Gd__gd_core_items__Food, "Food", "res://gd_core_items/Food.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Food, &Gd__gd_core_items__Food::get_static_prop_fn, &Gd__gd_core_items__Food::call_static_fn};

void Gd__gd_core_items__CarrotGoobert::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Goobert::init_fields(gd_ctx);
    this->f_empower = gd::GdVal::null();
    this->f_particleTimer = gd::GdVal::null();
    this->f_activationParticles = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__CarrotGoobert::meta() const { return &META_Gd__gd_core_items__CarrotGoobert; }
gd::GdVal Gd__gd_core_items__CarrotGoobert::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__CarrotGoobert::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__CarrotGoobert::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        case SYM_GEN_particleTimer_999: out = this->f_particleTimer; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::get_prop(prop, out);
}
bool Gd__gd_core_items__CarrotGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        case SYM_GEN_particleTimer_999: this->f_particleTimer = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__CarrotGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN_onParticleTimeout_1000: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__CarrotGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onParticleTimeout_1000: out = fn_onParticleTimeout(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__CarrotGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__CarrotGoobert::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CarrotGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_356, _ca, 1); })();
    gd::GdVal lv_duration = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[5])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_int(106LL), this->f_empower, lv_duration}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacksTemporary_202, _ca, 4); })();
    (void)gd::native_inline_call(gd_ctx, this->f_particleTimer, SYM_GEN_stop_1780, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {lv_duration}; return gd::native_inline_call(gd_ctx, this->f_particleTimer, SYM_GEN_start_1779, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CarrotGoobert::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_particleTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CarrotGoobert::fn_onParticleTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CarrotGoobert::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CarrotGoobert::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(lv_active)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CarrotGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_empower = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0);
    this->f_particleTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[27]), gd::GdVal::from_str(&battle_string_literals[28]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__CarrotGoobert(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__CarrotGoobert>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,187u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__CarrotGoobert = {CLS_Gd__gd_core_items__CarrotGoobert, "CarrotGoobert", "res://gd_core_items/CarrotGoobert.gd", &META_Gd__gd_core_items__Goobert, true, _alloc_Gd__gd_core_items__CarrotGoobert, &Gd__gd_core_items__CarrotGoobert::get_static_prop_fn, &Gd__gd_core_items__CarrotGoobert::call_static_fn};

void Gd__gd_core_items__DjinnLamp::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_activated = gd::GdVal::from_bool(false);
    this->f_affectedWeapon = gd::GdVal::null();
    this->f_stacksNeeded = gd::GdVal::null();
    this->f_healthNeeded = gd::GdVal::null();
    this->f_activationParticles = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__DjinnLamp::meta() const { return &META_Gd__gd_core_items__DjinnLamp; }
gd::GdVal Gd__gd_core_items__DjinnLamp::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_numIngredients_1856: return gd::GdVal::from_float(5.0);
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__DjinnLamp::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    switch (prop) {
        case SYM_GEN_numIngredients_1856: out = gd::GdVal::from_float(5.0); return true;
        default: break;
    }
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__DjinnLamp::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activated_1314: out = this->f_activated; return true;
        case SYM_GEN_affectedWeapon_948: out = this->f_affectedWeapon; return true;
        case SYM_GEN_stacksNeeded_1857: out = this->f_stacksNeeded; return true;
        case SYM_GEN_healthNeeded_1858: out = this->f_healthNeeded; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_numIngredients_1856: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__DjinnLamp::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activated_1314: this->f_activated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_affectedWeapon_948: this->f_affectedWeapon = val; return true;
        case SYM_GEN_stacksNeeded_1857: this->f_stacksNeeded = val; return true;
        case SYM_GEN_healthNeeded_1858: this->f_healthNeeded = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__DjinnLamp::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_checkStacks_1859: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__DjinnLamp::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_checkStacks_1859: out = fn_checkStacks(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__DjinnLamp::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__DjinnLamp::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DjinnLamp::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_activated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    this->f_affectedWeapon = gd::GdVal::null();
    gd::GdVal lv_affectedItems = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0);
    if (gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_affectedItems, gd::SYM_empty, nullptr, 0))))) {
        this->f_affectedWeapon = gd::native_array_index(gd_ctx, lv_affectedItems, gd::GdVal::from_int(0LL));
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[29]), gd::GdVal::from_str(&battle_string_literals[30])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[31]), gd::GdVal::from_str(&battle_string_literals[30])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[32]), gd::GdVal::from_str(&battle_string_literals[30])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[33]), gd::GdVal::from_str(&battle_string_literals[30])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[19]), gd::GdVal::from_str(&battle_string_literals[30])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[34]), gd::GdVal::from_str(&battle_string_literals[30])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DjinnLamp::fn_checkStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_changeAmount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::native_scalar_truth(this->f_activated)) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_progress = gd::GdVal::from_float(0.0);
    lv_progress = gd::gd_add(gd_ctx, lv_progress, gd::gd_div(gd_ctx, gd::gd_min(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getBlock_204, nullptr, 0), this->f_stacksNeeded), gd::gd_coerce_float(this->f_stacksNeeded)));
    lv_progress = gd::gd_add(gd_ctx, lv_progress, gd::gd_div(gd_ctx, gd::gd_min(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getSpikes_1223, nullptr, 0), this->f_stacksNeeded), gd::gd_coerce_float(this->f_stacksNeeded)));
    lv_progress = gd::gd_add(gd_ctx, lv_progress, gd::gd_div(gd_ctx, gd::gd_min(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0), this->f_stacksNeeded), gd::gd_coerce_float(this->f_stacksNeeded)));
    lv_progress = gd::gd_add(gd_ctx, lv_progress, gd::gd_div(gd_ctx, gd::gd_min(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getLucky_1237, nullptr, 0), this->f_stacksNeeded), gd::gd_coerce_float(this->f_stacksNeeded)));
    lv_progress = gd::gd_add(gd_ctx, lv_progress, gd::gd_div(gd_ctx, gd::gd_min(gd::gd_sub(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getCurrentHealth_1154, nullptr, 0), gd::GdVal::from_int(1LL)), this->f_healthNeeded), gd::gd_coerce_float(this->f_healthNeeded)));
    lv_progress = gd::gd_div(gd_ctx, lv_progress, Gd__gd_core_items__DjinnLamp::get_static_const_or_enum(gd_ctx, SYM_GEN_numIngredients_1856));
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_gt(lv_changeAmount, gd::GdVal::from_int(0LL))))) {
        if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_ge(lv_progress, gd::GdVal::from_float(0.9999))))) {
            this->f_activated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_LoggingMode_1599), SYM_GEN_Delayed_2686)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_setLoggingMode_1588, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_stacksNeeded, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useBlock_207, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_stacksNeeded, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useSpikes_337, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_stacksNeeded, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_332, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_stacksNeeded, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useLucky_350, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_healthNeeded, gd::GdVal::from_obj(this), lv_event}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_loseHealth_1157, _ca, 3); })();
            gd::GdVal lv_bonusDamage = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {lv_bonusDamage}; return gd::native_inline_call(gd_ctx, this->f_affectedWeapon, SYM_GEN_addBonusDamage_161, _ca, 1); })();
            gd::GdVal lv_dmgBuffEvent = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), this->f_affectedWeapon, lv_bonusDamage, gd::native_inline_get_prop(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_playerId_1046), lv_event}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_createEvent_DamageBuff_1374, _ca, 5); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_dmgBuffEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_logEvent_1357, _ca, 1); })();
            (void)gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_flushLoggingQueue_1591, nullptr, 0);
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DjinnLamp::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numLucky = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getLucky_1237, nullptr, 0);
    gd::GdVal lv_numSpikes = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getSpikes_1223, nullptr, 0);
    gd::GdVal lv_numMana = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0);
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_lt(lv_numLucky, lv_numSpikes)))) {
        if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_lt(lv_numLucky, lv_numMana)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
        }
    }
    else {
        if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_lt(lv_numSpikes, lv_numMana)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_209, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DjinnLamp::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_stacksNeeded = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0);
    this->f_healthNeeded = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__DjinnLamp(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__DjinnLamp>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,204u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__DjinnLamp = {CLS_Gd__gd_core_items__DjinnLamp, "DjinnLamp", "res://gd_core_items/DjinnLamp.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__DjinnLamp, &Gd__gd_core_items__DjinnLamp::get_static_prop_fn, &Gd__gd_core_items__DjinnLamp::call_static_fn};

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
        case SYM_GEN_onDropped_2034: return true;
        case SYM_GEN_identifyAmulet_2035: return true;
        case SYM_GEN_getRelatedItemColumns_699: return true;
        case SYM_GEN_getRelatedItemHeight_700: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__AmuletUnidentified::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onDropped_2034: out = fn_onDropped(args, argc); return true;
        case SYM_GEN_identifyAmulet_2035: out = fn_identifyAmulet(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_699: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN_getRelatedItemHeight_700: out = fn_getRelatedItemHeight(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
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
    if (gd::native_scalar_truth((gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {lv_dropRes}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core_items__Exclusive__AmuletUnidentified::call_static_fn(gd_ctx, SYM_GEN_wasAddedToInventory_659, _ca, 1, _out); return _out; })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_dropRes, gd::native_inline_get_prop(gd_ctx, Gd__gd_core_items__Exclusive__AmuletUnidentified::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_865), SYM_GEN_AddedToStorageBox_2723)))))))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_prepareReplacement_446, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[35]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_dropRes}))}; return gd::native_inline_call(gd_ctx, this->f_ctx, SYM_GEN_defer_1482, _ca, 3); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[36]), gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[37])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_connect, _ca, 3); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__AmuletUnidentified(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__AmuletUnidentified>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,211u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AmuletUnidentified = {CLS_Gd__gd_core_items__Exclusive__AmuletUnidentified, "AmuletUnidentified", "res://gd_core_items/Exclusive/AmuletUnidentified.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__AmuletUnidentified, &Gd__gd_core_items__Exclusive__AmuletUnidentified::get_static_prop_fn, &Gd__gd_core_items__Exclusive__AmuletUnidentified::call_static_fn};

void Gd__gd_core_items__Exclusive__BadgerSpirit::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__SpiritCompanion::init_fields(gd_ctx);
    this->f_activated = gd::GdVal::from_bool(false);
    this->f_healthThreshold = gd::GdVal::null();
    this->f_manaNeeded = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__BadgerSpirit::meta() const { return &META_Gd__gd_core_items__Exclusive__BadgerSpirit; }
gd::GdVal Gd__gd_core_items__Exclusive__BadgerSpirit::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__SpiritCompanion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__BadgerSpirit::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__BadgerSpirit::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activated_1314: out = this->f_activated; return true;
        case SYM_GEN_healthThreshold_1854: out = this->f_healthThreshold; return true;
        case SYM_GEN_manaNeeded_1881: out = this->f_manaNeeded; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__SpiritCompanion::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BadgerSpirit::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activated_1314: this->f_activated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_healthThreshold_1854: this->f_healthThreshold = val; return true;
        case SYM_GEN_manaNeeded_1881: this->f_manaNeeded = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__SpiritCompanion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BadgerSpirit::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onDamaged_1855: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN_playDropSound_149: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__SpiritCompanion::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BadgerSpirit::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDamaged_1855: out = fn_onDamaged(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_149: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__SpiritCompanion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__BadgerSpirit::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__SpiritCompanion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__BadgerSpirit::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(26LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BadgerSpirit::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_activated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[19]), gd::GdVal::from_str(&battle_string_literals[38])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BadgerSpirit::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__healthChange = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::native_scalar_truth((gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(this->f_activated))) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRelativeHealth_302, nullptr, 0), this->f_healthThreshold)))) : gd::GdVal::from_bool(false)))) {
        this->f_activated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::gd_mul(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMaxHealth_1160, nullptr, 0), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[39])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()), gd::GdVal::from_float(100.0)), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BadgerSpirit::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0), this->f_manaNeeded)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_332, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[10])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[40])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })())), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, _ca, 2); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BadgerSpirit::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BadgerSpirit::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BadgerSpirit::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__SpiritCompanion::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_healthThreshold = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[41])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_manaNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[42])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__BadgerSpirit(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__BadgerSpirit>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,232u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BadgerSpirit = {CLS_Gd__gd_core_items__Exclusive__BadgerSpirit, "BadgerSpirit", "res://gd_core_items/Exclusive/BadgerSpirit.gd", &META_Gd__gd_core_items__Exclusive__SpiritCompanion, true, _alloc_Gd__gd_core_items__Exclusive__BadgerSpirit, &Gd__gd_core_items__Exclusive__BadgerSpirit::get_static_prop_fn, &Gd__gd_core_items__Exclusive__BadgerSpirit::call_static_fn};

void Gd__gd_core_items__Exclusive__BookofIce::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_manaNeeded = gd::GdVal::null();
    this->f_cold = gd::GdVal::null();
    this->f_spellSpeed = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__BookofIce::meta() const { return &META_Gd__gd_core_items__Exclusive__BookofIce; }
gd::GdVal Gd__gd_core_items__Exclusive__BookofIce::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__BookofIce::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__BookofIce::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_manaNeeded_1881: out = this->f_manaNeeded; return true;
        case SYM_GEN_cold_2045: out = this->f_cold; return true;
        case SYM_GEN_spellSpeed_2094: out = this->f_spellSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BookofIce::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaNeeded_1881: this->f_manaNeeded = val; return true;
        case SYM_GEN_cold_2045: this->f_cold = val; return true;
        case SYM_GEN_spellSpeed_2094: this->f_spellSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BookofIce::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BookofIce::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__BookofIce::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofIce::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(18LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofIce::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_speed = gd::GdVal::from_float(0.0);
    {
        gd::GdVal _t1485 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1486 = (_t1485.kind == gd::GdVal::Kind::Arr) ? _t1485.arr : nullptr;
        uint32_t _len__t1487 = _t1486 ? _t1486->len : 0u;
        for (uint32_t _t1487 = 0; _t1487 < _len__t1487; ++_t1487) {
            gd::GdVal lv_item = _t1486->data[_t1487];
            if (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(28LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())) {
                lv_speed = gd::gd_add(gd_ctx, lv_speed, gd::gd_mul(this->f_spellSpeed, gd::GdVal::from_int(2LL)));
            }
            else {
                lv_speed = gd::gd_add(gd_ctx, lv_speed, this->f_spellSpeed);
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_speed}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofIce::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0), this->f_manaNeeded)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_332, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_cold, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_351, _ca, 2); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofIce::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_manaNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[43])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_cold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[44])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_spellSpeed = gd::gd_div(gd_ctx, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[45])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })()), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__BookofIce(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__BookofIce>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,246u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BookofIce = {CLS_Gd__gd_core_items__Exclusive__BookofIce, "BookofIce", "res://gd_core_items/Exclusive/BookofIce.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__BookofIce, &Gd__gd_core_items__Exclusive__BookofIce::get_static_prop_fn, &Gd__gd_core_items__Exclusive__BookofIce::call_static_fn};

void Gd__gd_core_items__Exclusive__CapofBrilliance::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__LeatherHelm::init_fields(gd_ctx);
    this->f_mana = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__CapofBrilliance::meta() const { return &META_Gd__gd_core_items__Exclusive__CapofBrilliance; }
gd::GdVal Gd__gd_core_items__Exclusive__CapofBrilliance::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__LeatherHelm::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__CapofBrilliance::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__CapofBrilliance::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_mana_1928: out = this->f_mana; return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__CapofBrilliance::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_mana_1928: this->f_mana = val; return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__CapofBrilliance::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__CapofBrilliance::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__CapofBrilliance::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__LeatherHelm::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__CapofBrilliance::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(32LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_gainsStack_86, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CapofBrilliance::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN_onPrepare_123, nullptr, 0, _out); return _out; })();
    {
        gd::GdVal _t1488 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1489 = (_t1488.kind == gd::GdVal::Kind::Arr) ? _t1488.arr : nullptr;
        uint32_t _len__t1490 = _t1489 ? _t1489->len : 0u;
        for (uint32_t _t1490 = 0; _t1490 < _len__t1490; ++_t1490) {
            gd::GdVal lv_item = _t1489->data[_t1490];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(105LL), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_172, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_196, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CapofBrilliance::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_mana}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN_onCombatStart_934, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CapofBrilliance::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[43])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__CapofBrilliance(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__CapofBrilliance>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,262u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__CapofBrilliance = {CLS_Gd__gd_core_items__Exclusive__CapofBrilliance, "CapofBrilliance", "res://gd_core_items/Exclusive/CapofBrilliance.gd", &META_Gd__gd_core_items__LeatherHelm, true, _alloc_Gd__gd_core_items__Exclusive__CapofBrilliance, &Gd__gd_core_items__Exclusive__CapofBrilliance::get_static_prop_fn, &Gd__gd_core_items__Exclusive__CapofBrilliance::call_static_fn};

void Gd__gd_core_items__Exclusive__Chess__WhiteKing::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__Chess__ChessPiece::init_fields(gd_ctx);
    this->f_empower = gd::GdVal::null();
    this->f_buffs = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Chess__WhiteKing::meta() const { return &META_Gd__gd_core_items__Exclusive__Chess__WhiteKing; }
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteKing::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteKing::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteKing::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        case SYM_GEN_buffs_1048: out = this->f_buffs; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteKing::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        case SYM_GEN_buffs_1048: this->f_buffs = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteKing::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCapturingEffect_2146: return true;
        case SYM_GEN_onAnyPieceCaptured_2155: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteKing::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCapturingEffect_2146: out = fn_doCapturingEffect(args, argc); return true;
        case SYM_GEN_onAnyPieceCaptured_2155: out = fn_onAnyPieceCaptured(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteKing::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteKing::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_board, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_board, gd::GdVal::from_str(&battle_string_literals[46]), gd::GdVal::from_str(&battle_string_literals[47])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteKing::fn_doCapturingEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__eliminatedPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {this->f_empower}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteKing::fn_onAnyPieceCaptured(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_capturingPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__eliminatedPiece = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, lv_capturingPiece, SYM_GEN_pieceColor_2135), gd::native_inline_get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Chess__WhiteKing::get_static_const_or_enum(gd_ctx, SYM_GEN_PieceColor_2150), SYM_GEN_White_2819))))) {
        if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_get_prop(gd_ctx, lv_capturingPiece, SYM_GEN_numCaptures_2138), gd::GdVal::from_int(1LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_buffs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_369, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_369, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteKing::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[48])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_buffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[49])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Chess__WhiteKing(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Chess__WhiteKing>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,280u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Chess__WhiteKing = {CLS_Gd__gd_core_items__Exclusive__Chess__WhiteKing, "WhiteKing", "res://gd_core_items/Exclusive/Chess/WhiteKing.gd", &META_Gd__gd_core_items__Exclusive__Chess__ChessPiece, true, _alloc_Gd__gd_core_items__Exclusive__Chess__WhiteKing, &Gd__gd_core_items__Exclusive__Chess__WhiteKing::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Chess__WhiteKing::call_static_fn};

void Gd__gd_core_items__Exclusive__Cthulhu::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_affectedFood = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_foodSpeed = gd::GdVal::null();
    this->f_dam = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Cthulhu::meta() const { return &META_Gd__gd_core_items__Exclusive__Cthulhu; }
gd::GdVal Gd__gd_core_items__Exclusive__Cthulhu::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Cthulhu::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Cthulhu::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_affectedFood_2184: out = this->f_affectedFood; return true;
        case SYM_GEN_foodSpeed_2028: out = this->f_foodSpeed; return true;
        case SYM_GEN_dam_939: out = this->f_dam; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Cthulhu::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedFood_2184: this->f_affectedFood = val; return true;
        case SYM_GEN_foodSpeed_2028: this->f_foodSpeed = val; return true;
        case SYM_GEN_dam_939: this->f_dam = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Cthulhu::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onAffectedItemAdded_435: return true;
        case SYM_GEN_onAffectedItemRemoved_436: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Cthulhu::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onAffectedItemAdded_435: out = fn_onAffectedItemAdded(args, argc); return true;
        case SYM_GEN_onAffectedItemRemoved_436: out = fn_onAffectedItemRemoved(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Cthulhu::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Cthulhu::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(25LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cthulhu::fn_onAffectedItemAdded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    if (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(25LL), gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addDynamicType_242, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cthulhu::fn_onAffectedItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(25LL), gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_removeDynamicType_243, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cthulhu::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_affectedFood, gd::SYM_clear, nullptr, 0);
    {
        gd::GdVal _t1491 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1492 = (_t1491.kind == gd::GdVal::Kind::Arr) ? _t1491.arr : nullptr;
        uint32_t _len__t1493 = _t1492 ? _t1492->len : 0u;
        for (uint32_t _t1493 = 0; _t1493 < _len__t1493; ++_t1493) {
            gd::GdVal lv_item = _t1492->data[_t1493];
            if (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, this->f_affectedFood, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_foodSpeed, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cthulhu::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_dam, gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[18])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealLife_329, _ca, 2); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    if (gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(gd::native_inline_call(gd_ctx, this->f_affectedFood, gd::SYM_empty, nullptr, 0))))) {
        (void)gd::native_inline_call(gd_ctx, ([&]() { gd::GdVal _ca[] = {this->f_affectedFood}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_pickRandomElement_1746, _ca, 1); })(), SYM_GEN_doCooldownEffect_144, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cthulhu::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_foodSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[45])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_dam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[24])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Cthulhu(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Cthulhu>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,295u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Cthulhu = {CLS_Gd__gd_core_items__Exclusive__Cthulhu, "Cthulhu", "res://gd_core_items/Exclusive/Cthulhu.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Cthulhu, &Gd__gd_core_items__Exclusive__Cthulhu::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Cthulhu::call_static_fn};

void Gd__gd_core_items__Exclusive__DoubleRainbow::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_speedPerHolyItem = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__DoubleRainbow::meta() const { return &META_Gd__gd_core_items__Exclusive__DoubleRainbow; }
gd::GdVal Gd__gd_core_items__Exclusive__DoubleRainbow::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__DoubleRainbow::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__DoubleRainbow::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_speedPerHolyItem_2210: out = this->f_speedPerHolyItem; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DoubleRainbow::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_speedPerHolyItem_2210: this->f_speedPerHolyItem = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DoubleRainbow::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_canAffect_secondary_287: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DoubleRainbow::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_287: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__DoubleRainbow::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__DoubleRainbow::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_gainsBuffs_296, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DoubleRainbow::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(22LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DoubleRainbow::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_369, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DoubleRainbow::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1494 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1495 = (_t1494.kind == gd::GdVal::Kind::Arr) ? _t1494.arr : nullptr;
        uint32_t _len__t1496 = _t1495 ? _t1495->len : 0u;
        for (uint32_t _t1496 = 0; _t1496 < _len__t1496; ++_t1496) {
            gd::GdVal lv_item = _t1495->data[_t1496];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_allBuffs_197, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, _ca, 1); })(), this->f_speedPerHolyItem)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DoubleRainbow::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_speedPerHolyItem = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[45])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__DoubleRainbow(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__DoubleRainbow>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,312u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DoubleRainbow = {CLS_Gd__gd_core_items__Exclusive__DoubleRainbow, "DoubleRainbow", "res://gd_core_items/Exclusive/DoubleRainbow.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__DoubleRainbow, &Gd__gd_core_items__Exclusive__DoubleRainbow::get_static_prop_fn, &Gd__gd_core_items__Exclusive__DoubleRainbow::call_static_fn};

void Gd__gd_core_items__LeatherArmor::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__LeatherArmor::meta() const { return &META_Gd__gd_core_items__LeatherArmor; }
gd::GdVal Gd__gd_core_items__LeatherArmor::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__LeatherArmor::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__LeatherArmor::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__LeatherArmor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__LeatherArmor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreCombatStart_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__LeatherArmor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreCombatStart_125: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__LeatherArmor::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__LeatherArmor::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeDebuffResistStacks_1185, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LeatherArmor::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LeatherArmor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__LeatherArmor(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__LeatherArmor>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,600u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__LeatherArmor = {CLS_Gd__gd_core_items__LeatherArmor, "LeatherArmor", "res://gd_core_items/LeatherArmor.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__LeatherArmor, &Gd__gd_core_items__LeatherArmor::get_static_prop_fn, &Gd__gd_core_items__LeatherArmor::call_static_fn};

void Gd__gd_core_items__Exclusive__FlameBadge::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__FlameBadge::meta() const { return &META_Gd__gd_core_items__Exclusive__FlameBadge; }
gd::GdVal Gd__gd_core_items__Exclusive__FlameBadge::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__FlameBadge::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__FlameBadge::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__FlameBadge::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__FlameBadge::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onAddToInventory_419: return true;
        case SYM_GEN_onRemoveFromInventory_418: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_getRelatedItems_459: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__FlameBadge::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onAddToInventory_419: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_418: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_getRelatedItems_459: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__FlameBadge::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__FlameBadge::fn_onAddToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FlameBadge::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FlameBadge::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_381, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FlameBadge::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FlameBadge::fn_getRelatedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FlameBadge::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__FlameBadge(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__FlameBadge>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,341u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__FlameBadge = {CLS_Gd__gd_core_items__Exclusive__FlameBadge, "FlameBadge", "res://gd_core_items/Exclusive/FlameBadge.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__FlameBadge, &Gd__gd_core_items__Exclusive__FlameBadge::get_static_prop_fn, &Gd__gd_core_items__Exclusive__FlameBadge::call_static_fn};

void Gd__gd_core_items__Exclusive__Ghost::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_unhealing = gd::GdVal::null();
    this->f_activationParticles = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Ghost::meta() const { return &META_Gd__gd_core_items__Exclusive__Ghost; }
gd::GdVal Gd__gd_core_items__Exclusive__Ghost::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Ghost::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Ghost::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_unhealing_2088: out = this->f_unhealing; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Ghost::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_unhealing_2088: this->f_unhealing = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Ghost::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN_playDropSound_149: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Ghost::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_149: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Ghost::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Ghost::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_unhealing}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_giveUnhealing_1178, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Ghost::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_useEvents = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRandomBuffs_371, _ca, 1); })();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_useEvents, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[39])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::native_array_index(gd_ctx, lv_useEvents, gd::GdVal::from_int(0LL))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 2); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Ghost::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Ghost::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Ghost::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_unhealing = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[50])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Ghost(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Ghost>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,355u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Ghost = {CLS_Gd__gd_core_items__Exclusive__Ghost, "Ghost", "res://gd_core_items/Exclusive/Ghost.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Ghost, &Gd__gd_core_items__Exclusive__Ghost::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Ghost::call_static_fn};

void Gd__gd_core_items__Exclusive__HolyCollar::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__RangerCollar::init_fields(gd_ctx);
    this->f_luck = gd::GdVal::null();
    this->f_regen = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__HolyCollar::meta() const { return &META_Gd__gd_core_items__Exclusive__HolyCollar; }
gd::GdVal Gd__gd_core_items__Exclusive__HolyCollar::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__RangerCollar::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__HolyCollar::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__HolyCollar::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_regen_1999: out = this->f_regen; return true;
        default: break;
    }
    return Gd__gd_core_items__RangerCollar::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__HolyCollar::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_regen_1999: this->f_regen = val; return true;
        default: break;
    }
    return Gd__gd_core_items__RangerCollar::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__HolyCollar::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onLuckyOrRegenChanged_2311: return true;
        case SYM_GEN_onItemActivated_938: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__RangerCollar::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__HolyCollar::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onLuckyOrRegenChanged_2311: out = fn_onLuckyOrRegenChanged(args, argc); return true;
        case SYM_GEN_onItemActivated_938: out = fn_onItemActivated(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__RangerCollar::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__HolyCollar::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__RangerCollar::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__HolyCollar::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canActivate_91, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HolyCollar::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1497 = gd::gd_iter_seq(gd_ctx.arena, this->f_affectedItems);
        gd::GdArr* _t1498 = (_t1497.kind == gd::GdVal::Kind::Arr) ? _t1497.arr : nullptr;
        uint32_t _len__t1499 = _t1498 ? _t1498->len : 0u;
        for (uint32_t _t1499 = 0; _t1499 < _len__t1499; ++_t1499) {
            gd::GdVal lv_item = _t1498->data[_t1499];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[51]), gd::GdVal::from_str(&battle_string_literals[52])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    if (gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(gd::native_inline_call(gd_ctx, this->f_affectedItems, gd::SYM_empty, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[33]), gd::GdVal::from_str(&battle_string_literals[53])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[8]), gd::GdVal::from_str(&battle_string_literals[53])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HolyCollar::fn_onLuckyOrRegenChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    {
        gd::GdVal _t1500 = gd::gd_iter_seq(gd_ctx.arena, this->f_affectedItems);
        gd::GdArr* _t1501 = (_t1500.kind == gd::GdVal::Kind::Arr) ? _t1500.arr : nullptr;
        uint32_t _len__t1502 = _t1501 ? _t1501->len : 0u;
        for (uint32_t _t1502 = 0; _t1502 < _len__t1502; ++_t1502) {
            gd::GdVal lv_item = _t1501->data[_t1502];
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_172, nullptr, 0))}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeCritChancePercent_181, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HolyCollar::fn_onItemActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_luck, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_regen, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 2); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HolyCollar::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__RangerCollar::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[54])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[55])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__HolyCollar(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__HolyCollar>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,370u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__HolyCollar = {CLS_Gd__gd_core_items__Exclusive__HolyCollar, "HolyCollar", "res://gd_core_items/Exclusive/HolyCollar.gd", &META_Gd__gd_core_items__RangerCollar, true, _alloc_Gd__gd_core_items__Exclusive__HolyCollar, &Gd__gd_core_items__Exclusive__HolyCollar::get_static_prop_fn, &Gd__gd_core_items__Exclusive__HolyCollar::call_static_fn};

void Gd__gd_core_items__Exclusive__KnifetoMeetYou::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_boosted = gd::GdVal::from_int(0LL);
    this->f_daggerDescriptor = gd::GdVal::null();
    this->f_daggerSpeed = gd::GdVal::null();
    this->f_damFactor = gd::GdVal::null();
    this->f_speedPerDagger = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__KnifetoMeetYou::meta() const { return &META_Gd__gd_core_items__Exclusive__KnifetoMeetYou; }
gd::GdVal Gd__gd_core_items__Exclusive__KnifetoMeetYou::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__KnifetoMeetYou::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__KnifetoMeetYou::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_boosted_2197: out = this->f_boosted; return true;
        case SYM_GEN_daggerDescriptor_2337: out = this->f_daggerDescriptor; return true;
        case SYM_GEN_daggerSpeed_2338: out = this->f_daggerSpeed; return true;
        case SYM_GEN_damFactor_1895: out = this->f_damFactor; return true;
        case SYM_GEN_speedPerDagger_2339: out = this->f_speedPerDagger; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__KnifetoMeetYou::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_boosted_2197: this->f_boosted = val; return true;
        case SYM_GEN_daggerDescriptor_2337: this->f_daggerDescriptor = val; return true;
        case SYM_GEN_daggerSpeed_2338: this->f_daggerSpeed = val; return true;
        case SYM_GEN_damFactor_1895: this->f_damFactor = val; return true;
        case SYM_GEN_speedPerDagger_2339: this->f_speedPerDagger = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__KnifetoMeetYou::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onBought_455: return true;
        case SYM_GEN_getData_638: return true;
        case SYM_GEN_setData_639: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onItemRoll_2018: return true;
        case SYM_GEN_onItemRolled_2019: return true;
        case SYM_GEN_canAffect_global_2014: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__KnifetoMeetYou::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onBought_455: out = fn_onBought(args, argc); return true;
        case SYM_GEN_getData_638: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_639: out = fn_setData(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onItemRoll_2018: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_onItemRolled_2019: out = fn_onItemRolled(args, argc); return true;
        case SYM_GEN_canAffect_global_2014: out = fn_canAffect_global(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__KnifetoMeetYou::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__KnifetoMeetYou::fn_onBought(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_boosted = gd::GdVal::from_int(3LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KnifetoMeetYou::fn_getData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_boosted;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KnifetoMeetYou::fn_setData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_data = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_data, gd::GdVal::null())))) {
        this->f_boosted = lv_data;
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KnifetoMeetYou::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(gd::native_inline_is_type(gd_ctx, lv_item, &META_Gd__gd_core_items__Dagger));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KnifetoMeetYou::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1503 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
        gd::GdArr* _t1504 = (_t1503.kind == gd::GdVal::Kind::Arr) ? _t1503.arr : nullptr;
        uint32_t _len__t1505 = _t1504 ? _t1504->len : 0u;
        for (uint32_t _t1505 = 0; _t1505 < _len__t1505; ++_t1505) {
            gd::GdVal lv_item = _t1504->data[_t1505];
            if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_inline_is_type(gd_ctx, lv_item, &META_Gd__gd_core_items__Dagger)))) {
                (void)([&]() { gd::GdVal _ca[] = {this->f_daggerSpeed}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_speedPerDagger, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KnifetoMeetYou::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1506 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
        gd::GdArr* _t1507 = (_t1506.kind == gd::GdVal::Kind::Arr) ? _t1506.arr : nullptr;
        uint32_t _len__t1508 = _t1507 ? _t1507->len : 0u;
        for (uint32_t _t1508 = 0; _t1508 < _len__t1508; ++_t1508) {
            gd::GdVal lv_item = _t1507->data[_t1508];
            if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {this->f_damFactor}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusDamageFactor_306, _ca, 1); })();
            }
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KnifetoMeetYou::fn_onItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KnifetoMeetYou::fn_onItemRolled(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_descr, this->f_daggerDescriptor)))) {
        this->f_boosted = gd::gd_sub(this->f_boosted, gd::GdVal::from_int(1LL));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KnifetoMeetYou::fn_canAffect_global(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KnifetoMeetYou::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_daggerDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[56])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_daggerSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[45])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_damFactor = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[24])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_speedPerDagger = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[57])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__KnifetoMeetYou(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__KnifetoMeetYou>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,385u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__KnifetoMeetYou = {CLS_Gd__gd_core_items__Exclusive__KnifetoMeetYou, "KnifetoMeetYou", "res://gd_core_items/Exclusive/KnifetoMeetYou.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__KnifetoMeetYou, &Gd__gd_core_items__Exclusive__KnifetoMeetYou::get_static_prop_fn, &Gd__gd_core_items__Exclusive__KnifetoMeetYou::call_static_fn};

static const gd::GdEnum::KV _ekv_Gd__gd_core_items__Exclusive__MagicRing_TriggerType[] = {{"StartOfBattle", 0LL}, {"Every", 1LL}, {"PlayerLow", 2LL}, {"OppoLow", 3LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__Exclusive__MagicRing_TriggerType = {"TriggerType", _ekv_Gd__gd_core_items__Exclusive__MagicRing_TriggerType, 4u};
void Gd__gd_core_items__Exclusive__MagicRing::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_stackToTypes = ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 10); d->set(gd_ctx.arena, gd::GdVal::from_int(101LL), gd::GdVal::from_int(26LL)); d->set(gd_ctx.arena, gd::GdVal::from_int(104LL), gd::GdVal::from_int(26LL)); d->set(gd_ctx.arena, gd::GdVal::from_int(102LL), gd::GdVal::from_int(22LL)); d->set(gd_ctx.arena, gd::GdVal::from_int(107LL), gd::GdVal::from_int(27LL)); d->set(gd_ctx.arena, gd::GdVal::from_int(103LL), gd::GdVal::from_int(24LL)); d->set(gd_ctx.arena, gd::GdVal::from_int(106LL), gd::GdVal::from_int(22LL)); d->set(gd_ctx.arena, gd::GdVal::from_int(105LL), gd::GdVal::from_int(23LL)); d->set(gd_ctx.arena, gd::GdVal::from_int(109LL), gd::GdVal::from_int(25LL)); d->set(gd_ctx.arena, gd::GdVal::from_int(110LL), gd::GdVal::from_int(28LL)); d->set(gd_ctx.arena, gd::GdVal::from_int(108LL), gd::GdVal::from_int(26LL)); return gd::GdVal::from_dict(d); })();
    this->f_stackToColor = ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 10); d->set(gd_ctx.arena, gd::GdVal::from_int(101LL), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.329826), gd::GdVal::from_int(1LL), gd::GdVal::from_float(0.263672)}; return gd::make_color_from_args(_ca, 3); })()); d->set(gd_ctx.arena, gd::GdVal::from_int(104LL), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.700867), gd::GdVal::from_int(1LL), gd::GdVal::from_float(0.263672)}; return gd::make_color_from_args(_ca, 3); })()); d->set(gd_ctx.arena, gd::GdVal::from_int(102LL), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::GdVal::from_float(0.388672), gd::GdVal::from_float(0.696724)}; return gd::make_color_from_args(_ca, 3); })()); d->set(gd_ctx.arena, gd::GdVal::from_int(107LL), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.1), gd::GdVal::from_float(0.44), gd::GdVal::from_float(0.24)}; return gd::make_color_from_args(_ca, 3); })()); d->set(gd_ctx.arena, gd::GdVal::from_int(103LL), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.900391), gd::GdVal::from_float(0.04924), gd::GdVal::from_float(0.04924)}; return gd::make_color_from_args(_ca, 3); })()); d->set(gd_ctx.arena, gd::GdVal::from_int(106LL), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.955078), gd::GdVal::from_float(0.665003), gd::GdVal::from_float(0.341366)}; return gd::make_color_from_args(_ca, 3); })()); d->set(gd_ctx.arena, gd::GdVal::from_int(105LL), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.257812), gd::GdVal::from_float(0.330292), gd::GdVal::from_int(1LL)}; return gd::make_color_from_args(_ca, 3); })()); d->set(gd_ctx.arena, gd::GdVal::from_int(109LL), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.569776), gd::GdVal::from_float(0.196078), gd::GdVal::from_int(1LL)}; return gd::make_color_from_args(_ca, 3); })()); d->set(gd_ctx.arena, gd::GdVal::from_int(110LL), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.196078), gd::GdVal::from_float(0.952895), gd::GdVal::from_int(1LL)}; return gd::make_color_from_args(_ca, 3); })()); d->set(gd_ctx.arena, gd::GdVal::from_int(108LL), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.008865), gd::GdVal::from_float(0.648438), gd::GdVal::from_float(0.176254)}; return gd::make_color_from_args(_ca, 3); })()); return gd::GdVal::from_dict(d); })();
    this->f_effects = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_effectDict = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_gainedStacks = gd::GdVal::from_int(0);
    this->f_playerLowTriggered = gd::GdVal::from_bool(false);
    this->f_oppoLowTriggered = gd::GdVal::from_bool(false);
    this->f_ringTypes = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_textEffect = gd::GdVal::from_int(0);
    this->f_numEffects = gd::GdVal::null();
    this->f_healthThreshold = gd::GdVal::null();
    this->f_opponentHealthThreshold = gd::GdVal::null();
    this->f_stones = gd::GdVal::null();
    this->f_symbols = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__MagicRing::meta() const { return &META_Gd__gd_core_items__Exclusive__MagicRing; }
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_TriggerType_2385: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Exclusive__MagicRing_TriggerType);
        case SYM_GEN_RingEffect_2386: return gd::GdVal::from_cls(&META_Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect);
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__MagicRing::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    switch (prop) {
        case SYM_GEN_TriggerType_2385: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Exclusive__MagicRing_TriggerType); return true;
        case SYM_GEN_RingEffect_2386: out = gd::GdVal::from_cls(&META_Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect); return true;
        default: break;
    }
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__MagicRing::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_stackToTypes_2364: out = this->f_stackToTypes; return true;
        case SYM_GEN_stackToColor_2365: out = this->f_stackToColor; return true;
        case SYM_GEN_effects_2366: out = this->f_effects; return true;
        case SYM_GEN_effectDict_2367: out = this->f_effectDict; return true;
        case SYM_GEN_gainedStacks_1714: out = this->f_gainedStacks; return true;
        case SYM_GEN_playerLowTriggered_2368: out = this->f_playerLowTriggered; return true;
        case SYM_GEN_oppoLowTriggered_2369: out = this->f_oppoLowTriggered; return true;
        case SYM_GEN_ringTypes_2370: out = this->f_ringTypes; return true;
        case SYM_GEN_textEffect_2371: out = this->f_textEffect; return true;
        case SYM_GEN_numEffects_2372: out = this->f_numEffects; return true;
        case SYM_GEN_healthThreshold_1854: out = this->f_healthThreshold; return true;
        case SYM_GEN_opponentHealthThreshold_1990: out = this->f_opponentHealthThreshold; return true;
        case SYM_GEN_stones_2373: out = this->f_stones; return true;
        case SYM_GEN_symbols_2374: out = this->f_symbols; return true;
        case SYM_GEN_TriggerType_2385: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Exclusive__MagicRing_TriggerType); return true;
        case SYM_GEN_RingEffect_2386: out = gd::GdVal::from_cls(&META_Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MagicRing::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_stackToTypes_2364: this->f_stackToTypes = val; return true;
        case SYM_GEN_stackToColor_2365: this->f_stackToColor = val; return true;
        case SYM_GEN_effects_2366: this->f_effects = val; return true;
        case SYM_GEN_effectDict_2367: this->f_effectDict = val; return true;
        case SYM_GEN_gainedStacks_1714: this->f_gainedStacks = gd::gd_coerce_int(val); return true;
        case SYM_GEN_playerLowTriggered_2368: this->f_playerLowTriggered = val; return true;
        case SYM_GEN_oppoLowTriggered_2369: this->f_oppoLowTriggered = val; return true;
        case SYM_GEN_ringTypes_2370: this->f_ringTypes = val; return true;
        case SYM_GEN_textEffect_2371: this->f_textEffect = gd::gd_coerce_int(val); return true;
        case SYM_GEN_numEffects_2372: this->f_numEffects = val; return true;
        case SYM_GEN_healthThreshold_1854: this->f_healthThreshold = val; return true;
        case SYM_GEN_opponentHealthThreshold_1990: this->f_opponentHealthThreshold = val; return true;
        case SYM_GEN_stones_2373: this->f_stones = val; return true;
        case SYM_GEN_symbols_2374: this->f_symbols = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MagicRing::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_hasCooldown_95: return true;
        case SYM_GEN_hasStartofBattle_126: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onDamaged_1855: return true;
        case SYM_GEN_onOppoDamaged_2375: return true;
        case SYM_GEN_giveStacksFromEffect_2376: return true;
        case SYM_GEN_sortEffects_2377: return true;
        case SYM_GEN_getTypes_240: return true;
        case SYM_GEN_hasType_79: return true;
        case SYM_GEN_getNumStaticTypes_239: return true;
        case SYM_GEN_gainsStack_86: return true;
        case SYM_GEN_gainsBuffs_296: return true;
        case SYM_GEN_inflictsDebuffs_298: return true;
        case SYM_GEN_getTextEffect_835: return true;
        case SYM_GEN_randEffects_2378: return true;
        case SYM_GEN_setCraftedEffects_2379: return true;
        case SYM_GEN_getScaledParam_2380: return true;
        case SYM_GEN_isOnlyForDisplay_2381: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN_copyFrom_2382: return true;
        case SYM_GEN_getData_638: return true;
        case SYM_GEN_setData_639: return true;
        case SYM_GEN_persistDataInShop_640: return true;
        case SYM_GEN_getDataPersistent_2383: return true;
        case SYM_GEN_getDataPersistentBits_2384: return true;
        case SYM_GEN_onCraftedFrom_849: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MagicRing::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_hasCooldown_95: out = fn_hasCooldown(args, argc); return true;
        case SYM_GEN_hasStartofBattle_126: out = fn_hasStartofBattle(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onDamaged_1855: out = fn_onDamaged(args, argc); return true;
        case SYM_GEN_onOppoDamaged_2375: out = fn_onOppoDamaged(args, argc); return true;
        case SYM_GEN_giveStacksFromEffect_2376: out = fn_giveStacksFromEffect(args, argc); return true;
        case SYM_GEN_sortEffects_2377: out = fn_sortEffects(args, argc); return true;
        case SYM_GEN_getTypes_240: out = fn_getTypes(args, argc); return true;
        case SYM_GEN_hasType_79: out = fn_hasType(args, argc); return true;
        case SYM_GEN_getNumStaticTypes_239: out = fn_getNumStaticTypes(args, argc); return true;
        case SYM_GEN_gainsStack_86: out = fn_gainsStack(args, argc); return true;
        case SYM_GEN_gainsBuffs_296: out = fn_gainsBuffs(args, argc); return true;
        case SYM_GEN_inflictsDebuffs_298: out = fn_inflictsDebuffs(args, argc); return true;
        case SYM_GEN_getTextEffect_835: out = fn_getTextEffect(args, argc); return true;
        case SYM_GEN_randEffects_2378: out = fn_randEffects(args, argc); return true;
        case SYM_GEN_setCraftedEffects_2379: out = fn_setCraftedEffects(args, argc); return true;
        case SYM_GEN_getScaledParam_2380: out = fn_getScaledParam(args, argc); return true;
        case SYM_GEN_isOnlyForDisplay_2381: out = fn_isOnlyForDisplay(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_copyFrom_2382: out = fn_copyFrom(args, argc); return true;
        case SYM_GEN_getData_638: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_639: out = fn_setData(args, argc); return true;
        case SYM_GEN_persistDataInShop_640: out = fn_persistDataInShop(args, argc); return true;
        case SYM_GEN_getDataPersistent_2383: out = fn_getDataPersistent(args, argc); return true;
        case SYM_GEN_getDataPersistentBits_2384: out = fn_getDataPersistentBits(args, argc); return true;
        case SYM_GEN_onCraftedFrom_849: out = fn_onCraftedFrom(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__MagicRing::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_hasCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_in(gd::GdVal::from_int(1LL), this->f_effectDict);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_hasStartofBattle(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_in(gd::GdVal::from_int(0LL), this->f_effectDict);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_playerLowTriggered = gd::GdVal::from_bool(false);
    this->f_oppoLowTriggered = gd::GdVal::from_bool(false);
    if (gd::native_scalar_truth(gd::gd_in(gd::GdVal::from_int(2LL), this->f_effectDict))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[19]), gd::GdVal::from_str(&battle_string_literals[38])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    }
    if (gd::native_scalar_truth(gd::gd_in(gd::GdVal::from_int(3LL), this->f_effectDict))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[19]), gd::GdVal::from_str(&battle_string_literals[58])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1509 = gd::gd_iter_seq(gd_ctx.arena, gd::native_array_index(gd_ctx, this->f_effectDict, gd::GdVal::from_int(0LL)));
        gd::GdArr* _t1510 = (_t1509.kind == gd::GdVal::Kind::Arr) ? _t1509.arr : nullptr;
        uint32_t _len__t1511 = _t1510 ? _t1510->len : 0u;
        for (uint32_t _t1511 = 0; _t1511 < _len__t1511; ++_t1511) {
            gd::GdVal lv_effect = _t1510->data[_t1511];
            (void)([&]() { gd::GdVal _ca[] = {lv_effect}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacksFromEffect_2376, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1512 = gd::gd_iter_seq(gd_ctx.arena, gd::native_array_index(gd_ctx, this->f_effectDict, gd::GdVal::from_int(1LL)));
        gd::GdArr* _t1513 = (_t1512.kind == gd::GdVal::Kind::Arr) ? _t1512.arr : nullptr;
        uint32_t _len__t1514 = _t1513 ? _t1513->len : 0u;
        for (uint32_t _t1514 = 0; _t1514 < _len__t1514; ++_t1514) {
            gd::GdVal lv_effect = _t1513->data[_t1514];
            (void)([&]() { gd::GdVal _ca[] = {lv_effect}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacksFromEffect_2376, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__healthChange = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::native_scalar_truth(this->f_playerLowTriggered)) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_relHealth = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRelativeHealth_302, nullptr, 0);
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_lt(lv_relHealth, this->f_healthThreshold)))) {
        this->f_playerLowTriggered = gd::GdVal::from_bool(true);
        {
            gd::GdVal _t1515 = gd::gd_iter_seq(gd_ctx.arena, gd::native_array_index(gd_ctx, this->f_effectDict, gd::GdVal::from_int(2LL)));
            gd::GdArr* _t1516 = (_t1515.kind == gd::GdVal::Kind::Arr) ? _t1515.arr : nullptr;
            uint32_t _len__t1517 = _t1516 ? _t1516->len : 0u;
            for (uint32_t _t1517 = 0; _t1517 < _len__t1517; ++_t1517) {
                gd::GdVal lv_effect = _t1516->data[_t1517];
                (void)([&]() { gd::GdVal _ca[] = {lv_effect, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacksFromEffect_2376, _ca, 2); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_onOppoDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__healthChange = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::native_scalar_truth(this->f_oppoLowTriggered)) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_relHealth = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_getRelativeHealth_302, nullptr, 0);
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_lt(lv_relHealth, this->f_opponentHealthThreshold)))) {
        this->f_oppoLowTriggered = gd::GdVal::from_bool(true);
        {
            gd::GdVal _t1518 = gd::gd_iter_seq(gd_ctx.arena, gd::native_array_index(gd_ctx, this->f_effectDict, gd::GdVal::from_int(3LL)));
            gd::GdArr* _t1519 = (_t1518.kind == gd::GdVal::Kind::Arr) ? _t1518.arr : nullptr;
            uint32_t _len__t1520 = _t1519 ? _t1519->len : 0u;
            for (uint32_t _t1520 = 0; _t1520 < _len__t1520; ++_t1520) {
                gd::GdVal lv_effect = _t1519->data[_t1520];
                (void)([&]() { gd::GdVal _ca[] = {lv_effect, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacksFromEffect_2376, _ca, 2); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_giveStacksFromEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_effect = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_target = gd::GdVal::null();
    if (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, lv_effect, SYM_GEN_stackType_2388)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_isBuff_1006, _ca, 1); })())) {
        lv_target = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0);
    }
    else {
        lv_target = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0);
    }
    gd::GdVal lv_stackName = gd::native_inline_call(gd_ctx, gd::native_array_index(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_event_type_keys_1427), gd::native_inline_get_prop(gd_ctx, lv_effect, SYM_GEN_stackType_2388)), gd::SYM_to_lower, nullptr, 0);
    gd::GdVal lv_paramScale = ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[59]), gd::gd_add(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_effect, SYM_GEN_triggerType_2387), gd::GdVal::from_int(1LL))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 2); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_target, gd::native_inline_get_prop(gd_ctx, lv_effect, SYM_GEN_stackType_2388), ([&]() { gd::GdVal _ca[] = {lv_stackName, lv_paramScale}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getScaledParam_2380, _ca, 2); })(), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 4); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_sortEffects(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_gainedStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)gd::native_inline_call(gd_ctx, this->f_effectDict, gd::SYM_clear, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, this->f_ringTypes, gd::SYM_clear, nullptr, 0);
    gd::GdVal lv_effectI = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t1521 = gd::gd_iter_seq(gd_ctx.arena, this->f_effects);
        gd::GdArr* _t1522 = (_t1521.kind == gd::GdVal::Kind::Arr) ? _t1521.arr : nullptr;
        uint32_t _len__t1523 = _t1522 ? _t1522->len : 0u;
        for (uint32_t _t1523 = 0; _t1523 < _len__t1523; ++_t1523) {
            gd::GdVal lv_effect = _t1522->data[_t1523];
            lv_effectI = gd::gd_add(gd_ctx, lv_effectI, gd::GdVal::from_int(1LL));
        }
    }
    if (gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isOnlyForDisplay_2381, nullptr, 0))))) {
        {
            gd::GdVal _t1524 = gd::gd_iter_seq(gd_ctx.arena, this->f_effects);
            gd::GdArr* _t1525 = (_t1524.kind == gd::GdVal::Kind::Arr) ? _t1524.arr : nullptr;
            uint32_t _len__t1526 = _t1525 ? _t1525->len : 0u;
            for (uint32_t _t1526 = 0; _t1526 < _len__t1526; ++_t1526) {
                gd::GdVal lv_effect = _t1525->data[_t1526];
                (void)([&]() { gd::GdVal _ca[] = {this->f_effectDict, gd::native_inline_get_prop(gd_ctx, lv_effect, SYM_GEN_triggerType_2387), lv_effect}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_dictAppend_1792, _ca, 3); })();
                this->f_gainedStacks = gd::gd_coerce_int(gd::gd_bitor(this->f_gainedStacks, gd::gd_shl(gd::GdVal::from_int(2LL), gd::gd_sub(gd::native_inline_get_prop(gd_ctx, lv_effect, SYM_GEN_stackType_2388), gd::GdVal::from_int(101LL)))));
                gd::GdVal lv_newType = gd::native_array_index(gd_ctx, this->f_stackToTypes, gd::native_inline_get_prop(gd_ctx, lv_effect, SYM_GEN_stackType_2388));
                if (gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(gd::gd_in(lv_newType, this->f_ringTypes))))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_newType}; return gd::native_inline_call(gd_ctx, this->f_ringTypes, gd::SYM_push_back, _ca, 1); })();
                }
            }
        }
        if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_inventory, gd::GdVal::null())))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_onItemTypeChanged_458, _ca, 1); })();
        }
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_getTypes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getTypes_240, nullptr, 0, _out); return _out; })(), this->f_ringTypes);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_hasType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    return (gd::native_scalar_truth(gd::gd_in(lv_type, this->f_ringTypes)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {lv_type}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_hasType_79, _ca, 1, _out); return _out; })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_getNumStaticTypes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getNumStaticTypes_239, nullptr, 0, _out); return _out; })(), gd::native_inline_call(gd_ctx, this->f_ringTypes, gd::SYM_size, nullptr, 0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_gainsStack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stackType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::gd_bitand(this->f_gainedStacks, lv_stackType);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_gainsBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_bitand(this->f_gainedStacks, gd::GdVal::from_int(254LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_inflictsDebuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_bitand(this->f_gainedStacks, gd::GdVal::from_int(1792LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_getTextEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_textEffect;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_randEffects(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_clearIfOnlyDisplay = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    (void)gd::native_inline_call(gd_ctx, this->f_effects, gd::SYM_clear, nullptr, 0);
    {
        gd::GdVal _t1527 = gd::gd_iter_seq(gd_ctx.arena, this->f_numEffects);
        gd::GdArr* _t1528 = (_t1527.kind == gd::GdVal::Kind::Arr) ? _t1527.arr : nullptr;
        uint32_t _len__t1529 = _t1528 ? _t1528->len : 0u;
        for (uint32_t _t1529 = 0; _t1529 < _len__t1529; ++_t1529) {
            gd::GdVal lv_i = _t1528->data[_t1529];
            gd::GdVal lv_effect = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect), gd::SYM_new, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {lv_effect}; return gd::native_inline_call(gd_ctx, this->f_effects, gd::SYM_push_back, _ca, 1); })();
            gd::set_prop(gd_ctx, lv_effect, SYM_GEN_triggerType_2387, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), gd::GdVal::from_int(3LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randi_range, _ca, 2); })());
            gd::set_prop(gd_ctx, lv_effect, SYM_GEN_stackType_2388, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(101LL), gd::GdVal::from_int(110LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randi_range, _ca, 2); })());
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_sortEffects_2377, nullptr, 0);
    if (gd::native_scalar_truth((gd::native_scalar_truth(lv_clearIfOnlyDisplay) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isOnlyForDisplay_2381, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)gd::native_inline_call(gd_ctx, this->f_effects, gd::SYM_clear, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_setCraftedEffects(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_crafted = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)gd::native_inline_call(gd_ctx, this->f_effects, gd::SYM_clear, nullptr, 0);
    {
        gd::GdVal _t1530 = gd::gd_iter_seq(gd_ctx.arena, lv_crafted);
        gd::GdArr* _t1531 = (_t1530.kind == gd::GdVal::Kind::Arr) ? _t1530.arr : nullptr;
        uint32_t _len__t1532 = _t1531 ? _t1531->len : 0u;
        for (uint32_t _t1532 = 0; _t1532 < _len__t1532; ++_t1532) {
            gd::GdVal lv_e = _t1531->data[_t1532];
            gd::GdVal lv_effect = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect), gd::SYM_new, nullptr, 0);
            gd::set_prop(gd_ctx, lv_effect, SYM_GEN_triggerType_2387, gd::gd_coerce_int(gd::native_array_index(gd_ctx, lv_e, gd::GdVal::from_str(&battle_string_literals[60]))));
            gd::set_prop(gd_ctx, lv_effect, SYM_GEN_stackType_2388, gd::gd_coerce_int(gd::native_array_index(gd_ctx, lv_e, gd::GdVal::from_str(&battle_string_literals[61]))));
            (void)([&]() { gd::GdVal _ca[] = {lv_effect}; return gd::native_inline_call(gd_ctx, this->f_effects, gd::SYM_push_back, _ca, 1); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_sortEffects_2377, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_getScaledParam(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stackName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_paramScale = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_paramScale = gd::gd_coerce_float(lv_paramScale);
    return gd::gd_round(gd::gd_mul(([&]() { gd::GdVal _ca[] = {lv_stackName}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), lv_paramScale));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_isOnlyForDisplay(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::native_scalar_truth((gd::native_scalar_truth((gd::native_scalar_truth((gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_ownerType, gd::GdVal::from_int(8LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_ownerType, gd::GdVal::from_int(9LL))))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_ownerType, gd::GdVal::from_int(6LL))))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_ownerType, gd::GdVal::from_int(5LL))))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_ownerType, gd::GdVal::from_int(11LL))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    return gd::GdVal::from_str(&battle_string_literals[62]);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_copyFrom(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_otherRing = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, lv_otherRing, SYM_GEN_getData_638, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setData_639, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_getData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_setData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__data = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_persistDataInShop(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_getDataPersistent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_bitStream = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1533 = gd::gd_iter_seq(gd_ctx.arena, this->f_effects);
        gd::GdArr* _t1534 = (_t1533.kind == gd::GdVal::Kind::Arr) ? _t1533.arr : nullptr;
        uint32_t _len__t1535 = _t1534 ? _t1534->len : 0u;
        for (uint32_t _t1535 = 0; _t1535 < _len__t1535; ++_t1535) {
            gd::GdVal lv_effect = _t1534->data[_t1535];
            (void)([&]() { gd::GdVal _ca[] = {lv_bitStream}; return gd::native_inline_call(gd_ctx, lv_effect, SYM_GEN_pushEncoded_2389, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_getDataPersistentBits(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_mul(this->f_numEffects, gd::gd_add(gd_ctx, gd::GdVal::from_int(2LL), gd::GdVal::from_int(4LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn_onCraftedFrom(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_baseItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_ingredients = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)gd::native_inline_call(gd_ctx, this->f_effects, gd::SYM_clear, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, lv_baseItem, SYM_GEN_effects_2366)}; return gd::native_inline_call(gd_ctx, this->f_effects, gd::SYM_append_array, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_array_index(gd_ctx, lv_ingredients, gd::GdVal::from_int(0LL)), SYM_GEN_effects_2366)}; return gd::native_inline_call(gd_ctx, this->f_effects, gd::SYM_append_array, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), gd::GdVal::from_int(3LL)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randi_range, _ca, 2); })()}; return gd::native_inline_call(gd_ctx, this->f_effects, gd::SYM_remove, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_sortEffects_2377, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_numEffects = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[63])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_healthThreshold = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[41])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_opponentHealthThreshold = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[64])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_stones = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_symbols = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, this->f_stones, gd::SYM_empty, nullptr, 0))) {
        {
            gd::GdVal _t1536 = gd::gd_iter_seq(gd_ctx.arena, this->f_numEffects);
            gd::GdArr* _t1537 = (_t1536.kind == gd::GdVal::Kind::Arr) ? _t1536.arr : nullptr;
            uint32_t _len__t1538 = _t1537 ? _t1537->len : 0u;
            for (uint32_t _t1538 = 0; _t1538 < _len__t1538; ++_t1538) {
                gd::GdVal lv_i = _t1537->data[_t1538];
            }
        }
    }
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_ownerType, gd::GdVal::from_int(8LL))))) {
    }
    else {
        if (gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(this->f_wasJustCrafted)))) {
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_randEffects_2378, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__MagicRing(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__MagicRing>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,401u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MagicRing = {CLS_Gd__gd_core_items__Exclusive__MagicRing, "MagicRing", "res://gd_core_items/Exclusive/MagicRing.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__MagicRing, &Gd__gd_core_items__Exclusive__MagicRing::get_static_prop_fn, &Gd__gd_core_items__Exclusive__MagicRing::call_static_fn};

void Gd__gd_core_items__Exclusive__MoreStats::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_damageFactor = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__MoreStats::meta() const { return &META_Gd__gd_core_items__Exclusive__MoreStats; }
gd::GdVal Gd__gd_core_items__Exclusive__MoreStats::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__MoreStats::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__MoreStats::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_damageFactor_2410: out = this->f_damageFactor; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MoreStats::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damageFactor_2410: this->f_damageFactor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MoreStats::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_global_2014: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN_getSalesMultiplier_762: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MoreStats::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_global_2014: out = fn_canAffect_global(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_getSalesMultiplier_762: out = fn_getSalesMultiplier(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__MoreStats::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__MoreStats::fn_canAffect_global(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoreStats::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1539 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
        gd::GdArr* _t1540 = (_t1539.kind == gd::GdVal::Kind::Arr) ? _t1539.arr : nullptr;
        uint32_t _len__t1541 = _t1540 ? _t1540->len : 0u;
        for (uint32_t _t1541 = 0; _t1541 < _len__t1541; ++_t1541) {
            gd::GdVal lv_item = _t1540->data[_t1541];
            if (gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_global_2014, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {this->f_damageFactor}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusDamageFactor_306, _ca, 1); })();
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_round(gd::gd_mul(gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[10])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::GdVal::from_float(100.0)), gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMaxHealth_1160, nullptr, 0)))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoreStats::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(-1000LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoreStats::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getDescription_642, _ca, 1, _out); return _out; })();
    gd::GdVal lv_string = gd::GdVal::null();
    if (gd::native_scalar_truth(lv_wrapInColor)) {
        lv_string = ([&]() { gd::GdVal _ca[] = {([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 1); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[65]), gd::GdVal::null()); return gd::GdVal::from_dict(d); })()}; return gd::native_inline_call(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[66])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_tr_2826, _ca, 1); })(), SYM_GEN_format_2716, _ca, 1); })();
    }
    else {
        lv_string = ([&]() { gd::GdVal _ca[] = {([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 1); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[65]), gd::native_array_index(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_descriptor, SYM_GEN_appearRounds_2827), gd::GdVal::from_int(0LL))); return gd::GdVal::from_dict(d); })()}; return gd::native_inline_call(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[66])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_tr_2826, _ca, 1); })(), SYM_GEN_format_2716, _ca, 1); })();
    }
    lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[67]), lv_string));
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoreStats::fn_getSalesMultiplier(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_float(0.2);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoreStats::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_damageFactor = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[24])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__MoreStats(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__MoreStats>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,417u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MoreStats = {CLS_Gd__gd_core_items__Exclusive__MoreStats, "MoreStats", "res://gd_core_items/Exclusive/MoreStats.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__MoreStats, &Gd__gd_core_items__Exclusive__MoreStats::get_static_prop_fn, &Gd__gd_core_items__Exclusive__MoreStats::call_static_fn};

void Gd__gd_core_items__Exclusive__PineProtector::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__SpikedShield::init_fields(gd_ctx);
    this->f_damblockIncrease = gd::GdVal::from_int(0LL);
    this->f_damblock2 = gd::GdVal::null();
    this->f_maxblock = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__PineProtector::meta() const { return &META_Gd__gd_core_items__Exclusive__PineProtector; }
gd::GdVal Gd__gd_core_items__Exclusive__PineProtector::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__SpikedShield::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__PineProtector::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__PineProtector::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_damblockIncrease_2426: out = this->f_damblockIncrease; return true;
        case SYM_GEN_damblock2_2427: out = this->f_damblock2; return true;
        case SYM_GEN_maxblock_2428: out = this->f_maxblock; return true;
        default: break;
    }
    return Gd__gd_core_items__SpikedShield::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PineProtector::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damblockIncrease_2426: this->f_damblockIncrease = val; return true;
        case SYM_GEN_damblock2_2427: this->f_damblock2 = val; return true;
        case SYM_GEN_maxblock_2428: this->f_maxblock = val; return true;
        default: break;
    }
    return Gd__gd_core_items__SpikedShield::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PineProtector::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getDamageBlock_1940: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onItemActivated_938: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__SpikedShield::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PineProtector::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getDamageBlock_1940: out = fn_getDamageBlock(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemActivated_938: out = fn_onItemActivated(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__SpikedShield::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__PineProtector::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__SpikedShield::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__PineProtector::fn_getDamageBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[68]), gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[68])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), this->f_damblockIncrease)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getParamModified_190, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PineProtector::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PineProtector::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__SpikedShield::call_method(gd_ctx, SYM_GEN_onPrepare_123, nullptr, 0, _out); return _out; })();
    this->f_damblockIncrease = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t1542 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1543 = (_t1542.kind == gd::GdVal::Kind::Arr) ? _t1542.arr : nullptr;
        uint32_t _len__t1544 = _t1543 ? _t1543->len : 0u;
        for (uint32_t _t1544 = 0; _t1544 < _len__t1544; ++_t1544) {
            gd::GdVal lv_item = _t1543->data[_t1544];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[51]), gd::GdVal::from_str(&battle_string_literals[52])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
        }
    }
    this->f_maxSpikes = gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[69])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[70])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PineProtector::fn_onItemActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_damblockIncrease, this->f_maxblock)))) {
        this->f_damblockIncrease = gd::gd_add(gd_ctx, this->f_damblockIncrease, gd::gd_min(this->f_damblock2, gd::gd_sub(this->f_maxblock, this->f_damblockIncrease)));
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PineProtector::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__SpikedShield::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_damblock2 = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[71])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_maxblock = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[72])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PineProtector(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__PineProtector>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,432u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PineProtector = {CLS_Gd__gd_core_items__Exclusive__PineProtector, "PineProtector", "res://gd_core_items/Exclusive/PineProtector.gd", &META_Gd__gd_core_items__SpikedShield, true, _alloc_Gd__gd_core_items__Exclusive__PineProtector, &Gd__gd_core_items__Exclusive__PineProtector::get_static_prop_fn, &Gd__gd_core_items__Exclusive__PineProtector::call_static_fn};

void Gd__gd_core_items__Exclusive__PuzzlebagT::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Bag::init_fields(gd_ctx);
    this->f_usedStacks = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_affectedInside = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_refund = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__PuzzlebagT::meta() const { return &META_Gd__gd_core_items__Exclusive__PuzzlebagT; }
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagT::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Bag::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagT::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__PuzzlebagT::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_usedStacks_1716: out = this->f_usedStacks; return true;
        case SYM_GEN_affectedInside_2451: out = this->f_affectedInside; return true;
        case SYM_GEN_refund_2021: out = this->f_refund; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagT::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_usedStacks_1716: this->f_usedStacks = val; return true;
        case SYM_GEN_affectedInside_2451: this->f_affectedInside = val; return true;
        case SYM_GEN_refund_2021: this->f_refund = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagT::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canApplyEffect_920: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onBuffChanged_2006: return true;
        case SYM_GEN_getBagEffect_480: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagT::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canApplyEffect_920: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onBuffChanged_2006: out = fn_onBuffChanged(args, argc); return true;
        case SYM_GEN_getBagEffect_480: out = fn_getBagEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagT::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagT::fn_canApplyEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_toItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_toItem, SYM_GEN_usesBuffs_297, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagT::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_affectedInside = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_927, nullptr, 0);
    if (gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(gd::native_inline_call(gd_ctx, this->f_affectedInside, gd::SYM_empty, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[73])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToCharacterBuffs_374, _ca, 1); })();
        {
            gd::GdVal _t1545 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0));
            gd::GdArr* _t1546 = (_t1545.kind == gd::GdVal::Kind::Arr) ? _t1545.arr : nullptr;
            uint32_t _len__t1547 = _t1546 ? _t1546->len : 0u;
            for (uint32_t _t1547 = 0; _t1547 < _len__t1547; ++_t1547) {
                gd::GdVal lv_buff = _t1546->data[_t1547];
                { gd::GdVal _t1548 = this->f_usedStacks; gd::GdVal _t1549 = lv_buff; gd::native_array_set_index(gd_ctx, _t1548, _t1549, gd::GdVal::from_float(0.0)); }
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagT::fn_onBuffChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::native_scalar_truth((gd::native_scalar_truth((gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[74]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getParam_1575, _ca, 2); })())) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::gd_in(gd::native_inline_get_prop(gd_ctx, lv_event, SYM_GEN_origin_1546), this->f_affectedInside))) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv_used = gd::gd_neg(lv_amount);
        gd::GdVal lv_buffType = gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getType_1572, nullptr, 0);
        { gd::GdVal _t1550 = this->f_usedStacks; gd::GdVal _t1551 = lv_buffType; gd::native_array_set_index(gd_ctx, _t1550, _t1551, gd::gd_add(gd_ctx, gd::native_array_index(gd_ctx, _t1550, _t1551), gd::gd_mul(lv_used, this->f_refund))); }
        gd::GdVal lv_toRefund = gd::gd_coerce_int(gd::gd_round(gd::native_array_index(gd_ctx, this->f_usedStacks, lv_buffType)));
        if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_gt(lv_toRefund, gd::GdVal::from_int(0LL))))) {
            { gd::GdVal _t1552 = this->f_usedStacks; gd::GdVal _t1553 = lv_buffType; gd::native_array_set_index(gd_ctx, _t1552, _t1553, gd::gd_sub(gd::native_array_index(gd_ctx, _t1552, _t1553), lv_toRefund)); }
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), lv_buffType, lv_toRefund, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 4); })();
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagT::fn_getBagEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_number = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getName_234, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[75]))}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_tra_2715, _ca, 1); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(&battle_string_literals[76]), gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[77])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), lv_number)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 3); })();
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagT::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_refund = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[77])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PuzzlebagT(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__PuzzlebagT>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,449u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PuzzlebagT = {CLS_Gd__gd_core_items__Exclusive__PuzzlebagT, "PuzzlebagT", "res://gd_core_items/Exclusive/PuzzlebagT.gd", &META_Gd__gd_core_items__Bag, true, _alloc_Gd__gd_core_items__Exclusive__PuzzlebagT, &Gd__gd_core_items__Exclusive__PuzzlebagT::get_static_prop_fn, &Gd__gd_core_items__Exclusive__PuzzlebagT::call_static_fn};

void Gd__gd_core_items__Exclusive__Repeater::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Repeater::meta() const { return &META_Gd__gd_core_items__Exclusive__Repeater; }
gd::GdVal Gd__gd_core_items__Exclusive__Repeater::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Repeater::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Repeater::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Repeater::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Repeater::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Repeater::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Repeater::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Repeater::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasStartofBattle_126, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Repeater::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1554 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1555 = (_t1554.kind == gd::GdVal::Kind::Arr) ? _t1554.arr : nullptr;
        uint32_t _len__t1556 = _t1555 ? _t1555->len : 0u;
        for (uint32_t _t1556 = 0; _t1556 < _len__t1556; ++_t1556) {
            gd::GdVal lv_item = _t1555->data[_t1556];
            (void)gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_repeatCombatStart_130, nullptr, 0);
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Repeater::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Repeater(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Repeater>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,465u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Repeater = {CLS_Gd__gd_core_items__Exclusive__Repeater, "Repeater", "res://gd_core_items/Exclusive/Repeater.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Repeater, &Gd__gd_core_items__Exclusive__Repeater::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Repeater::call_static_fn};

void Gd__gd_core_items__Exclusive__ShellTotem::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_healthThreshold = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ShellTotem::meta() const { return &META_Gd__gd_core_items__Exclusive__ShellTotem; }
gd::GdVal Gd__gd_core_items__Exclusive__ShellTotem::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ShellTotem::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ShellTotem::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_healthThreshold_1854: out = this->f_healthThreshold; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ShellTotem::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_healthThreshold_1854: this->f_healthThreshold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ShellTotem::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ShellTotem::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ShellTotem::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ShellTotem::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(22LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShellTotem::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::gd_neg(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[78])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })()), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeStaminaFactor_305, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShellTotem::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_116, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRelativeHealth_302, nullptr, 0), this->f_healthThreshold)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 1); })();
        }
        else {
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
        }
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShellTotem::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_healthThreshold = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[41])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ShellTotem(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__ShellTotem>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,480u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ShellTotem = {CLS_Gd__gd_core_items__Exclusive__ShellTotem, "ShellTotem", "res://gd_core_items/Exclusive/ShellTotem.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__ShellTotem, &Gd__gd_core_items__Exclusive__ShellTotem::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ShellTotem::call_static_fn};

void Gd__gd_core_items__Exclusive__Snowmaster::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_iceSpeed = gd::GdVal::null();
    this->f_cold = gd::GdVal::null();
    this->f_empower = gd::GdVal::null();
    this->f_coldNeeded = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Snowmaster::meta() const { return &META_Gd__gd_core_items__Exclusive__Snowmaster; }
gd::GdVal Gd__gd_core_items__Exclusive__Snowmaster::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Snowmaster::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Snowmaster::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_iceSpeed_2516: out = this->f_iceSpeed; return true;
        case SYM_GEN_cold_2045: out = this->f_cold; return true;
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        case SYM_GEN_coldNeeded_2280: out = this->f_coldNeeded; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Snowmaster::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_iceSpeed_2516: this->f_iceSpeed = val; return true;
        case SYM_GEN_cold_2045: this->f_cold = val; return true;
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        case SYM_GEN_coldNeeded_2280: this->f_coldNeeded = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Snowmaster::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Snowmaster::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Snowmaster::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Snowmaster::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(28LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Snowmaster::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0), this->f_iceSpeed)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Snowmaster::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_getCold_1254, nullptr, 0), this->f_coldNeeded)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_empower}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {this->f_cold}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_351, _ca, 1); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_356, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Snowmaster::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_iceSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[45])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_cold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[44])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[48])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_coldNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[79])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Snowmaster(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Snowmaster>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,498u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Snowmaster = {CLS_Gd__gd_core_items__Exclusive__Snowmaster, "Snowmaster", "res://gd_core_items/Exclusive/Snowmaster.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Snowmaster, &Gd__gd_core_items__Exclusive__Snowmaster::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Snowmaster::call_static_fn};

void Gd__gd_core_items__Exclusive__Squirrel::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__ForestFriend::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Squirrel::meta() const { return &META_Gd__gd_core_items__Exclusive__Squirrel; }
gd::GdVal Gd__gd_core_items__Exclusive__Squirrel::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__ForestFriend::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Squirrel::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Squirrel::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Exclusive__ForestFriend::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Squirrel::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Exclusive__ForestFriend::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Squirrel::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN_playDropSound_149: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__ForestFriend::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Squirrel::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_149: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__ForestFriend::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Squirrel::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__ForestFriend::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Squirrel::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealRandomBuff_373, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Squirrel::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_pitch = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Squirrel::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    gd::GdVal lv_pitch = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Squirrel::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__ForestFriend::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Squirrel(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Squirrel>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,514u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Squirrel = {CLS_Gd__gd_core_items__Exclusive__Squirrel, "Squirrel", "res://gd_core_items/Exclusive/Squirrel.gd", &META_Gd__gd_core_items__Exclusive__ForestFriend, true, _alloc_Gd__gd_core_items__Exclusive__Squirrel, &Gd__gd_core_items__Exclusive__Squirrel::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Squirrel::call_static_fn};

void Gd__gd_core_items__Exclusive__TeslaCoil::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_itemsToAdvance = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_numCollectedCharges = gd::GdVal::from_int(0LL);
    this->f_advanceItemCounter = gd::GdVal::from_int(0LL);
    this->f_collectCharges = gd::GdVal::from_bool(true);
    this->f_cdAdvance = gd::GdVal::null();
    this->f_salesChance = gd::GdVal::null();
    this->f_engineerWeight = gd::GdVal::null();
    this->f_chargeCounter = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__TeslaCoil::meta() const { return &META_Gd__gd_core_items__Exclusive__TeslaCoil; }
gd::GdVal Gd__gd_core_items__Exclusive__TeslaCoil::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__TeslaCoil::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__TeslaCoil::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_itemsToAdvance_2575: out = this->f_itemsToAdvance; return true;
        case SYM_GEN_numCollectedCharges_2576: out = this->f_numCollectedCharges; return true;
        case SYM_GEN_advanceItemCounter_2577: out = this->f_advanceItemCounter; return true;
        case SYM_GEN_collectCharges_2578: out = this->f_collectCharges; return true;
        case SYM_GEN_cdAdvance_2080: out = this->f_cdAdvance; return true;
        case SYM_GEN_salesChance_2092: out = this->f_salesChance; return true;
        case SYM_GEN_engineerWeight_2579: out = this->f_engineerWeight; return true;
        case SYM_GEN_chargeCounter_2580: out = this->f_chargeCounter; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__TeslaCoil::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_itemsToAdvance_2575: this->f_itemsToAdvance = val; return true;
        case SYM_GEN_numCollectedCharges_2576: this->f_numCollectedCharges = val; return true;
        case SYM_GEN_advanceItemCounter_2577: this->f_advanceItemCounter = val; return true;
        case SYM_GEN_collectCharges_2578: this->f_collectCharges = val; return true;
        case SYM_GEN_cdAdvance_2080: this->f_cdAdvance = val; return true;
        case SYM_GEN_salesChance_2092: this->f_salesChance = val; return true;
        case SYM_GEN_engineerWeight_2579: this->f_engineerWeight = val; return true;
        case SYM_GEN_chargeCounter_2580: this->f_chargeCounter = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__TeslaCoil::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onChargeReceived_2129: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_advanceItem_2581: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onSaleRoll_2093: return true;
        case SYM_GEN_onItemRoll_2018: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__TeslaCoil::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onChargeReceived_2129: out = fn_onChargeReceived(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_advanceItem_2581: out = fn_advanceItem(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onSaleRoll_2093: out = fn_onSaleRoll(args, argc); return true;
        case SYM_GEN_onItemRoll_2018: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__TeslaCoil::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__TeslaCoil::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TeslaCoil::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    this->f_collectCharges = gd::GdVal::from_bool(true);
    this->f_numCollectedCharges = gd::GdVal::from_int(0LL);
    this->f_advanceItemCounter = gd::GdVal::from_int(0LL);
    this->f_itemsToAdvance = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0), gd::SYM_duplicate, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {this->f_itemsToAdvance, gd::GdVal::from_str(&battle_string_literals[80])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_shuffleEngine_1747, _ca, 2); })();
    gd::GdVal lv_otherItems = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1557 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
        gd::GdArr* _t1558 = (_t1557.kind == gd::GdVal::Kind::Arr) ? _t1557.arr : nullptr;
        uint32_t _len__t1559 = _t1558 ? _t1558->len : 0u;
        for (uint32_t _t1559 = 0; _t1559 < _len__t1559; ++_t1559) {
            gd::GdVal lv_item = _t1558->data[_t1559];
            if (gd::native_scalar_truth((gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item, gd::GdVal::from_obj(this)))) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(gd::gd_in(lv_item, this->f_itemsToAdvance))))) : gd::GdVal::from_bool(false)))) {
                if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, lv_otherItems, gd::SYM_push_back, _ca, 1); })();
                }
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_otherItems, gd::GdVal::from_str(&battle_string_literals[81])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_shuffleEngine_1747, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_otherItems}; return gd::native_inline_call(gd_ctx, this->f_itemsToAdvance, gd::SYM_append_array, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TeslaCoil::fn_onChargeReceived(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(this->f_collectCharges)) {
        this->f_numCollectedCharges = gd::gd_add(gd_ctx, this->f_numCollectedCharges, gd::GdVal::from_int(1LL));
        (void)([&]() { gd::GdVal _ca[] = {this->f_numCollectedCharges}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    }
    else {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_advanceItem_2581, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TeslaCoil::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_collectCharges = gd::GdVal::from_bool(false);
    {
        gd::GdVal _t1560 = gd::gd_iter_seq(gd_ctx.arena, this->f_numCollectedCharges);
        gd::GdArr* _t1561 = (_t1560.kind == gd::GdVal::Kind::Arr) ? _t1560.arr : nullptr;
        uint32_t _len__t1562 = _t1561 ? _t1561->len : 0u;
        for (uint32_t _t1562 = 0; _t1562 < _len__t1562; ++_t1562) {
            gd::GdVal lv_i = _t1561->data[_t1562];
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_advanceItem_2581, nullptr, 0);
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    gd::GdVal lv_done = gd::GdVal::from_bool(gd::gd_lt(gd::native_inline_call(gd_ctx, this->f_itemsToAdvance, gd::SYM_size, nullptr, 0), gd::gd_add(gd_ctx, this->f_advanceItemCounter, gd::GdVal::from_int(1LL))));
    (void)([&]() { gd::GdVal _ca[] = {lv_done}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, _ca, 1); })();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(lv_done)))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TeslaCoil::fn_advanceItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    while (gd::native_scalar_truth(gd::GdVal::from_bool(true))) {
        if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_inline_call(gd_ctx, this->f_itemsToAdvance, gd::SYM_size, nullptr, 0), gd::gd_add(gd_ctx, this->f_advanceItemCounter, gd::GdVal::from_int(1LL)))))) {
            return gd::GdVal::null();
        }
        gd::GdVal lv_item = gd::native_array_index(gd_ctx, this->f_itemsToAdvance, this->f_advanceItemCounter);
        this->f_advanceItemCounter = gd::gd_add(gd_ctx, this->f_advanceItemCounter, gd::GdVal::from_int(1LL));
        if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isCooldownActive_96, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_cdAdvance}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_advanceCooldownSeconds_147, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(4.0), gd::GdVal::from_float(4.02)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
            if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_inline_call(gd_ctx, this->f_itemsToAdvance, gd::SYM_size, nullptr, 0), gd::gd_add(gd_ctx, this->f_advanceItemCounter, gd::GdVal::from_int(1LL)))))) {
                this->f_consumed = gd::GdVal::from_bool(true);
            }
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
            return gd::GdVal::null();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TeslaCoil::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__numCollectedCharges = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv__numCollectedCharges, gd::GdVal::null())))) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TeslaCoil::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TeslaCoil::fn_onSaleRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TeslaCoil::fn_onItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TeslaCoil::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_cdAdvance = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[82])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_salesChance = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[83])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_engineerWeight = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[84])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__TeslaCoil(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__TeslaCoil>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,529u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__TeslaCoil = {CLS_Gd__gd_core_items__Exclusive__TeslaCoil, "TeslaCoil", "res://gd_core_items/Exclusive/TeslaCoil.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__TeslaCoil, &Gd__gd_core_items__Exclusive__TeslaCoil::get_static_prop_fn, &Gd__gd_core_items__Exclusive__TeslaCoil::call_static_fn};

void Gd__gd_core_items__Exclusive__Ukulele::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_nonMusicalItems = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_activateIndex = gd::GdVal::from_int(0);
    this->f_options = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_speedPerItem = gd::GdVal::null();
    this->f_cdAdvance = gd::GdVal::null();
    this->f_healAmp = gd::GdVal::null();
    this->f_buffs = gd::GdVal::null();
    this->f_cold = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Ukulele::meta() const { return &META_Gd__gd_core_items__Exclusive__Ukulele; }
gd::GdVal Gd__gd_core_items__Exclusive__Ukulele::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Ukulele::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Ukulele::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_nonMusicalItems_2598: out = this->f_nonMusicalItems; return true;
        case SYM_GEN_activateIndex_2599: out = this->f_activateIndex; return true;
        case SYM_GEN_options_1876: out = this->f_options; return true;
        case SYM_GEN_speedPerItem_2237: out = this->f_speedPerItem; return true;
        case SYM_GEN_cdAdvance_2080: out = this->f_cdAdvance; return true;
        case SYM_GEN_healAmp_1998: out = this->f_healAmp; return true;
        case SYM_GEN_buffs_1048: out = this->f_buffs; return true;
        case SYM_GEN_cold_2045: out = this->f_cold; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Ukulele::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_nonMusicalItems_2598: this->f_nonMusicalItems = val; return true;
        case SYM_GEN_activateIndex_2599: this->f_activateIndex = gd::gd_coerce_int(val); return true;
        case SYM_GEN_options_1876: this->f_options = val; return true;
        case SYM_GEN_speedPerItem_2237: this->f_speedPerItem = val; return true;
        case SYM_GEN_cdAdvance_2080: this->f_cdAdvance = val; return true;
        case SYM_GEN_healAmp_1998: this->f_healAmp = val; return true;
        case SYM_GEN_buffs_1048: this->f_buffs = val; return true;
        case SYM_GEN_cold_2045: this->f_cold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Ukulele::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_canAffect_secondary_287: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onItemActivated_938: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN_playDropSound_149: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Ukulele::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_287: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemActivated_938: out = fn_onItemActivated(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_149: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Ukulele::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Ukulele::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Ukulele::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(29LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Ukulele::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_activateIndex = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)gd::native_inline_call(gd_ctx, this->f_nonMusicalItems, gd::SYM_clear, nullptr, 0);
    {
        gd::GdVal _t1563 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
        gd::GdArr* _t1564 = (_t1563.kind == gd::GdVal::Kind::Arr) ? _t1563.arr : nullptr;
        uint32_t _len__t1565 = _t1564 ? _t1564->len : 0u;
        for (uint32_t _t1565 = 0; _t1565 < _len__t1565; ++_t1565) {
            gd::GdVal lv_item = _t1564->data[_t1565];
            if (gd::native_scalar_truth((gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(29LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })()))) ? gd::GdVal::from_bool(gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, this->f_nonMusicalItems, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    if (gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(gd::native_inline_call(gd_ctx, this->f_nonMusicalItems, gd::SYM_empty, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_nonMusicalItems, gd::GdVal::from_str(&battle_string_literals[85])}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), SYM_GEN_shuffleEngine_1747, _ca, 2); })();
        {
            gd::GdVal _t1566 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, _ca, 1); })());
            gd::GdArr* _t1567 = (_t1566.kind == gd::GdVal::Kind::Arr) ? _t1566.arr : nullptr;
            uint32_t _len__t1568 = _t1567 ? _t1567->len : 0u;
            for (uint32_t _t1568 = 0; _t1568 < _len__t1568; ++_t1568) {
                gd::GdVal lv_item = _t1567->data[_t1568];
                (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[51]), gd::GdVal::from_str(&battle_string_literals[52])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_speedPerItem, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_healAmp}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_addHealingEfficiency_1182, _ca, 1); })();
    {
        gd::GdVal _t1569 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
        gd::GdArr* _t1570 = (_t1569.kind == gd::GdVal::Kind::Arr) ? _t1569.arr : nullptr;
        uint32_t _len__t1571 = _t1570 ? _t1570->len : 0u;
        for (uint32_t _t1571 = 0; _t1571 < _len__t1571; ++_t1571) {
            gd::GdVal lv_item = _t1570->data[_t1571];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_allBuffs_197, _ca, 1); })();
        }
    }
    this->f_options = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL), gd::GdVal::from_int(2LL)}));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Ukulele::fn_onItemActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    while (gd::native_scalar_truth(gd::GdVal::from_bool(true))) {
        if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, this->f_nonMusicalItems, gd::SYM_empty, nullptr, 0))) {
            return gd::GdVal::null();
        }
        gd::GdVal lv_item = gd::native_array_index(gd_ctx, this->f_nonMusicalItems, this->f_activateIndex);
        if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isCooldownActive_96, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_cdAdvance}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_advanceCooldownPercent_146, _ca, 1); })();
            this->f_activateIndex = gd::gd_coerce_int(gd::gd_mod(gd_ctx, gd::gd_add(gd_ctx, this->f_activateIndex, gd::GdVal::from_int(1LL)), gd::native_inline_call(gd_ctx, this->f_nonMusicalItems, gd::SYM_size, nullptr, 0)));
            break;
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, this->f_nonMusicalItems, gd::SYM_erase, _ca, 1); })();
            if (gd::native_scalar_truth(gd::GdVal::from_bool(!gd::native_scalar_truth(gd::native_inline_call(gd_ctx, this->f_nonMusicalItems, gd::SYM_empty, nullptr, 0))))) {
                this->f_activateIndex = gd::gd_coerce_int(gd::gd_mod(gd_ctx, this->f_activateIndex, gd::native_inline_call(gd_ctx, this->f_nonMusicalItems, gd::SYM_size, nullptr, 0)));
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Ukulele::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rng = ([&]() { gd::GdVal _ca[] = {this->f_options}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_pickRandomElement_1746, _ca, 1); })();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_rng, gd::GdVal::from_int(0LL))))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    }
    else if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_rng, gd::GdVal::from_int(1LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_buffs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_369, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {this->f_cold}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_351, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    this->f_options = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL), gd::GdVal::from_int(2LL)}));
    (void)([&]() { gd::GdVal _ca[] = {lv_rng}; return gd::native_inline_call(gd_ctx, this->f_options, gd::SYM_erase, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Ukulele::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Ukulele::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Ukulele::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_speedPerItem = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[45])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_cdAdvance = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[86])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_healAmp = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[87])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_buffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[49])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_cold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[44])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Ukulele(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Ukulele>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,546u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Ukulele = {CLS_Gd__gd_core_items__Exclusive__Ukulele, "Ukulele", "res://gd_core_items/Exclusive/Ukulele.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Ukulele, &Gd__gd_core_items__Exclusive__Ukulele::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Ukulele::call_static_fn};

void Gd__gd_core_items__Exclusive__Wrench::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Wrench::meta() const { return &META_Gd__gd_core_items__Exclusive__Wrench; }
gd::GdVal Gd__gd_core_items__Exclusive__Wrench::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Wrench::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Wrench::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Wrench::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Wrench::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_canAffect_secondary_287: return true;
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Wrench::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_287: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Wrench::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Wrench::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_gainsBuffs_296, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wrench::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canDamage_89, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wrench::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        gd::GdVal lv_item1 = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getFirstAffectedItem_428, _ca, 1); })();
        if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item1, gd::GdVal::null())))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item1, SYM_GEN_changeAmplificiationChancePercent_allBuffs_197, _ca, 1); })();
        }
        gd::GdVal lv_item2 = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getFirstAffectedItem_428, _ca, 1); })();
        if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_item2, gd::GdVal::null())))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_172, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item2, SYM_GEN_changeCritChancePercent_181, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Wrench::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Wrench(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__Exclusive__Wrench>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,563u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Wrench = {CLS_Gd__gd_core_items__Exclusive__Wrench, "Wrench", "res://gd_core_items/Exclusive/Wrench.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__Wrench, &Gd__gd_core_items__Exclusive__Wrench::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Wrench::call_static_fn};

void Gd__gd_core_items__GingerbreadMan::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Food::init_fields(gd_ctx);
    this->f_luckNeeded = gd::GdVal::from_int(0);
    this->f_heatNeeded = gd::GdVal::from_int(0);
    this->f_manaNeeded = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core_items__GingerbreadMan::meta() const { return &META_Gd__gd_core_items__GingerbreadMan; }
gd::GdVal Gd__gd_core_items__GingerbreadMan::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__GingerbreadMan::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__GingerbreadMan::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_luckNeeded_1874: out = this->f_luckNeeded; return true;
        case SYM_GEN_heatNeeded_1880: out = this->f_heatNeeded; return true;
        case SYM_GEN_manaNeeded_1881: out = this->f_manaNeeded; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__GingerbreadMan::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_luckNeeded_1874: this->f_luckNeeded = gd::gd_coerce_int(val); return true;
        case SYM_GEN_heatNeeded_1880: this->f_heatNeeded = gd::gd_coerce_int(val); return true;
        case SYM_GEN_manaNeeded_1881: this->f_manaNeeded = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__GingerbreadMan::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__GingerbreadMan::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__GingerbreadMan::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__GingerbreadMan::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__GingerbreadMan::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getLucky_1237, nullptr, 0), this->f_luckNeeded)))) {
        if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getHeat_1251, nullptr, 0), this->f_heatNeeded)))) {
            if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMana_1244, nullptr, 0), this->f_manaNeeded)))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_LoggingMode_1599), SYM_GEN_Delayed_2686)}; return gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_setLoggingMode_1588, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {this->f_luckNeeded}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useLucky_350, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {this->f_heatNeeded}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useHeat_354, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_332, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_267, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP6_268, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
                (void)gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1408), SYM_GEN_flushLoggingQueue_1591, nullptr, 0);
                (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[88])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, _ca, 1); })();
            }
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__GingerbreadMan::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_luckNeeded = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0));
    this->f_heatNeeded = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0));
    this->f_manaNeeded = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__GingerbreadMan(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__GingerbreadMan>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,581u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__GingerbreadMan = {CLS_Gd__gd_core_items__GingerbreadMan, "GingerbreadMan", "res://gd_core_items/GingerbreadMan.gd", &META_Gd__gd_core_items__Food, true, _alloc_Gd__gd_core_items__GingerbreadMan, &Gd__gd_core_items__GingerbreadMan::get_static_prop_fn, &Gd__gd_core_items__GingerbreadMan::call_static_fn};

void Gd__gd_core_items__LightGoobert::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Goobert::init_fields(gd_ctx);
    this->f_particleTimer = gd::GdVal::null();
    this->f_activationParticles = gd::GdVal::null();
    this->f_blindAmount = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__LightGoobert::meta() const { return &META_Gd__gd_core_items__LightGoobert; }
gd::GdVal Gd__gd_core_items__LightGoobert::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__LightGoobert::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__LightGoobert::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_particleTimer_999: out = this->f_particleTimer; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_blindAmount_1909: out = this->f_blindAmount; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::get_prop(prop, out);
}
bool Gd__gd_core_items__LightGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_particleTimer_999: this->f_particleTimer = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_blindAmount_1909: this->f_blindAmount = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__LightGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN_onParticleTimeout_1000: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__LightGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onParticleTimeout_1000: out = fn_onParticleTimeout(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__LightGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__LightGoobert::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LightGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 2); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    gd::GdVal lv_duration = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[89])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_int(109LL), this->f_blindAmount, lv_duration}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacksTemporary_202, _ca, 4); })();
    (void)gd::native_inline_call(gd_ctx, this->f_particleTimer, SYM_GEN_stop_1780, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {lv_duration}; return gd::native_inline_call(gd_ctx, this->f_particleTimer, SYM_GEN_start_1779, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LightGoobert::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_particleTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LightGoobert::fn_onParticleTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LightGoobert::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LightGoobert::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(lv_active)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LightGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_particleTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[27]), gd::GdVal::from_str(&battle_string_literals[28]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    this->f_blindAmount = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__LightGoobert(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__LightGoobert>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,603u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__LightGoobert = {CLS_Gd__gd_core_items__LightGoobert, "LightGoobert", "res://gd_core_items/LightGoobert.gd", &META_Gd__gd_core_items__Goobert, true, _alloc_Gd__gd_core_items__LightGoobert, &Gd__gd_core_items__LightGoobert::get_static_prop_fn, &Gd__gd_core_items__LightGoobert::call_static_fn};

void Gd__gd_core_items__PoisonBow::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Bow::init_fields(gd_ctx);
    this->f_damageAcc = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_damagePerPoison = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core_items__PoisonBow::meta() const { return &META_Gd__gd_core_items__PoisonBow; }
gd::GdVal Gd__gd_core_items__PoisonBow::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Bow::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__PoisonBow::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__PoisonBow::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_damageAcc_1960: out = this->f_damageAcc; return true;
        case SYM_GEN_damagePerPoison_1961: out = this->f_damagePerPoison; return true;
        default: break;
    }
    return Gd__gd_core_items__Bow::get_prop(prop, out);
}
bool Gd__gd_core_items__PoisonBow::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damageAcc_1960: this->f_damageAcc = gd::gd_coerce_int(val); return true;
        case SYM_GEN_damagePerPoison_1961: this->f_damagePerPoison = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Bow::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__PoisonBow::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_hasAttackEffect_295: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onWeaponAttacked_950: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onOpponentPoisonChanged_1831: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Bow::has_own_method(m);
}
bool Gd__gd_core_items__PoisonBow::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_hasAttackEffect_295: out = fn_hasAttackEffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onWeaponAttacked_950: out = fn_onWeaponAttacked(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onOpponentPoisonChanged_1831: out = fn_onOpponentPoisonChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Bow::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__PoisonBow::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Bow::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__PoisonBow::fn_hasAttackEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PoisonBow::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[90]), gd::GdVal::from_str(&battle_string_literals[91])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    this->f_damageAcc = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PoisonBow::fn_onWeaponAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        gd::GdVal lv_attackEffectCount = gd::gd_add(gd_ctx, gd::GdVal::from_int(1LL), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollDoubleAttackEffect_187, nullptr, 0));
        {
            gd::GdVal _t1572 = gd::gd_iter_seq(gd_ctx.arena, lv_attackEffectCount);
            gd::GdArr* _t1573 = (_t1572.kind == gd::GdVal::Kind::Arr) ? _t1572.arr : nullptr;
            uint32_t _len__t1574 = _t1573 ? _t1573->len : 0u;
            for (uint32_t _t1574 = 0; _t1574 < _len__t1574; ++_t1574) {
                gd::GdVal lv_i = _t1573->data[_t1574];
                this->f_damageAcc = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_damageAcc, gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518)));
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {this->f_damageAcc, gd::GdVal::from_bool(false), gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PoisonBow::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_116, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_poisonStacks = gd::gd_div(gd_ctx, this->f_damageAcc, this->f_damagePerPoison);
        gd::GdVal lv_poisonEvent = ([&]() { gd::GdVal _ca[] = {lv_poisonStacks}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_211, _ca, 1); })();
        this->f_damageAcc = gd::gd_coerce_int(gd::gd_mod(gd_ctx, this->f_damageAcc, this->f_damagePerPoison));
        (void)([&]() { gd::GdVal _ca[] = {this->f_damageAcc, gd::GdVal::from_bool(false), lv_poisonEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 3); })();
        gd::GdVal lv_res = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_220, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PoisonBow::fn_onOpponentPoisonChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_162, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PoisonBow::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PoisonBow::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__damageAcc = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::GdVal::from_bool(gd::gd_lt(lv__damageAcc, this->f_damagePerPoison)))) {
    }
    else {
        gd::GdVal lv_poisonStacks = gd::gd_div(gd_ctx, lv__damageAcc, this->f_damagePerPoison);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PoisonBow::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bow::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_damagePerPoison = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__PoisonBow(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__PoisonBow>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,623u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__PoisonBow = {CLS_Gd__gd_core_items__PoisonBow, "PoisonBow", "res://gd_core_items/PoisonBow.gd", &META_Gd__gd_core_items__Bow, true, _alloc_Gd__gd_core_items__PoisonBow, &Gd__gd_core_items__PoisonBow::get_static_prop_fn, &Gd__gd_core_items__PoisonBow::call_static_fn};

void Gd__gd_core_items__SpectralDagger::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Dagger::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__SpectralDagger::meta() const { return &META_Gd__gd_core_items__SpectralDagger; }
gd::GdVal Gd__gd_core_items__SpectralDagger::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Dagger::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__SpectralDagger::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__SpectralDagger::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Dagger::get_prop(prop, out);
}
bool Gd__gd_core_items__SpectralDagger::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Dagger::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__SpectralDagger::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::has_own_method(m);
}
bool Gd__gd_core_items__SpectralDagger::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__SpectralDagger::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Dagger::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__SpectralDagger::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseMana_333, _ca, 1); })();
        if (gd::native_scalar_truth(lv_event)) {
            gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518, gd::gd_add(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)));
            (void)gd::native_inline_call(gd_ctx, gd::native_inline_get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_makeSpectral_1564, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__SpectralDagger::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Dagger::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__SpectralDagger(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__SpectralDagger>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,644u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__SpectralDagger = {CLS_Gd__gd_core_items__SpectralDagger, "SpectralDagger", "res://gd_core_items/SpectralDagger.gd", &META_Gd__gd_core_items__Dagger, true, _alloc_Gd__gd_core_items__SpectralDagger, &Gd__gd_core_items__SpectralDagger::get_static_prop_fn, &Gd__gd_core_items__SpectralDagger::call_static_fn};

void Gd__gd_core_items__VampiricGloves::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_inactiveTexture = gd::GdVal::null();
    this->f_activationParticles = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__VampiricGloves::meta() const { return &META_Gd__gd_core_items__VampiricGloves; }
gd::GdVal Gd__gd_core_items__VampiricGloves::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__VampiricGloves::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__VampiricGloves::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_inactiveTexture_2002: out = this->f_inactiveTexture; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__VampiricGloves::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_inactiveTexture_2002: this->f_inactiveTexture = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__VampiricGloves::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__VampiricGloves::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__VampiricGloves::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__VampiricGloves::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__VampiricGloves::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__VampiricGloves::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 1); })();
    gd::GdVal lv_bonusSpeed = gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), gd::GdVal::from_int(100LL));
    {
        gd::GdVal _t1575 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t1576 = (_t1575.kind == gd::GdVal::Kind::Arr) ? _t1575.arr : nullptr;
        uint32_t _len__t1577 = _t1576 ? _t1576->len : 0u;
        for (uint32_t _t1577 = 0; _t1577 < _len__t1577; ++_t1577) {
            gd::GdVal lv_item = _t1576->data[_t1577];
            (void)([&]() { gd::GdVal _ca[] = {lv_bonusSpeed}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_145, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__VampiricGloves::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__VampiricGloves::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::native_scalar_truth(lv_active)) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateShadowTexture_789, nullptr, 0);
    }
    else {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateShadowTexture_789, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__VampiricGloves::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__VampiricGloves(gd::BattleCtx& ctx) { auto* object=ctx.arena.make<Gd__gd_core_items__VampiricGloves>(&ctx); if(ctx.native_resolved_dispatch)gd::native_resolved_seed(object,663u); return object; }
const gd::GdClassMeta META_Gd__gd_core_items__VampiricGloves = {CLS_Gd__gd_core_items__VampiricGloves, "VampiricGloves", "res://gd_core_items/VampiricGloves.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__VampiricGloves, &Gd__gd_core_items__VampiricGloves::get_static_prop_fn, &Gd__gd_core_items__VampiricGloves::call_static_fn};
