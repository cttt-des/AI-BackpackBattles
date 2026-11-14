#pragma STDC FP_CONTRACT OFF

#include "../hdrs/Gd__gd_core__Bag.hpp"
#include "../hdrs/Gd__gd_core_items__Gems__Gem.hpp"
#include "../hdrs/Gd__gd_core__CoreEvent.hpp"
#include "../hdrs/Gd__gd_core__Crossblades.hpp"
#include "../hdrs/Gd__gd_core__Eggscalibur.hpp"
#include "../hdrs/Gd__gd_core__HeartofDarkness.hpp"
#include "../hdrs/Gd__gd_core__LuckyClover.hpp"
#include "../hdrs/Gd__gd_core__Pineapple.hpp"
#include "../hdrs/Gd__gd_core__RubyEgg.hpp"
#include "../hdrs/Gd__gd_core_items__Potion.hpp"
#include "../hdrs/Gd__gd_core__WalrusTusk.hpp"
#include "../hdrs/Gd__gd_core_items__Banana.hpp"
#include "../hdrs/Gd__gd_core_items__ClawsofAttack.hpp"
#include "../hdrs/Gd__gd_core_items__DragonEgg.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__AngelCrystal.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__BagofGiving.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__BookofLight.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__CatSpirit.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Chess__WhiteKnight.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Cubert.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__DraconicOrb.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__EmployeeUniform.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__FlameWhip.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Gigawatz.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__HyperHedgehog.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Laboratory.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__MagicRing.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__MrsStruggles.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__PlasticCube.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__PuzzlebagZ.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Resistor.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ShepherdsCrook.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Snowmaster.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SquirrelArcher.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ThornElemental.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Ultima.hpp"
#include "../hdrs/Gd__gd_core_items__FalconBlade.hpp"
#include "../hdrs/Gd__gd_core_items__GlovesofHaste.hpp"
#include "../hdrs/Gd__gd_core_items__LuckyBow.hpp"
#include "../hdrs/Gd__gd_core_items__PoisonDagger.hpp"
#include "../hdrs/Gd__gd_core_items__StaffofUnhealing.hpp"
#include "../hdrs/Gd__gd_core_items__VampiricScythe.hpp"

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
        case SYM_GEN_isBag_85: return true;
        case SYM_GEN_showBagBorderForItem_919: return true;
        case SYM_GEN_canApplyEffect_920: return true;
        case SYM_GEN_canBePicked_739: return true;
        case SYM_GEN_canBeLocked_821: return true;
        case SYM_GEN_resetZ_452: return true;
        case SYM_GEN_addToInventory_122: return true;
        case SYM_GEN_getBagLayerPriority_921: return true;
        case SYM_GEN_hasBagEffect_922: return true;
        case SYM_GEN__process_682: return true;
        case SYM_GEN_reactToDropResult_722: return true;
        case SYM_GEN_onRemoveFromInventory_420: return true;
        case SYM_GEN_getTopLeftGlobal_655: return true;
        case SYM_GEN_getBottomRightGlobal_656: return true;
        case SYM_GEN_isEmpty_923: return true;
        case SYM_GEN_getItemsInside_924: return true;
        case SYM_GEN_getEmptyCells_925: return true;
        case SYM_GEN_getEmptyGlobalPositions_926: return true;
        case SYM_GEN_getAffectedItemsInside_927: return true;
        case SYM_GEN_previewCanAffect_475: return true;
        case SYM_GEN_prepare_124: return true;
        case SYM_GEN_combatToShop_744: return true;
        case SYM_GEN_getCraftableNeighbors_494: return true;
        case SYM_GEN_onItemAdded_439: return true;
        case SYM_GEN_onAffectedItemInsideAdded_928: return true;
        case SYM_GEN_onItemRemoved_440: return true;
        case SYM_GEN_onAffectedItemInsideRemoved_929: return true;
        case SYM_GEN_pushItemsInsideToStorage_400: return true;
        case SYM_GEN_onDraggedWithParentStart_718: return true;
        case SYM_GEN_onDraggedWithParentEnd_720: return true;
        case SYM_GEN_getNumAffectedInside_930: return true;
        case SYM_GEN_getNumAffectedInside_type_931: return true;
        case SYM_GEN_getBagMultiplicity_932: return true;
        case SYM_GEN_discard_764: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Bag::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getHoverPriority_692: out = fn_getHoverPriority(args, argc); return true;
        case SYM_GEN_isBag_85: out = fn_isBag(args, argc); return true;
        case SYM_GEN_showBagBorderForItem_919: out = fn_showBagBorderForItem(args, argc); return true;
        case SYM_GEN_canApplyEffect_920: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN_canBePicked_739: out = fn_canBePicked(args, argc); return true;
        case SYM_GEN_canBeLocked_821: out = fn_canBeLocked(args, argc); return true;
        case SYM_GEN_resetZ_452: out = fn_resetZ(args, argc); return true;
        case SYM_GEN_addToInventory_122: out = fn_addToInventory(args, argc); return true;
        case SYM_GEN_getBagLayerPriority_921: out = fn_getBagLayerPriority(args, argc); return true;
        case SYM_GEN_hasBagEffect_922: out = fn_hasBagEffect(args, argc); return true;
        case SYM_GEN__process_682: out = fn__process(args, argc); return true;
        case SYM_GEN_reactToDropResult_722: out = fn_reactToDropResult(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_420: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_getTopLeftGlobal_655: out = fn_getTopLeftGlobal(args, argc); return true;
        case SYM_GEN_getBottomRightGlobal_656: out = fn_getBottomRightGlobal(args, argc); return true;
        case SYM_GEN_isEmpty_923: out = fn_isEmpty(args, argc); return true;
        case SYM_GEN_getItemsInside_924: out = fn_getItemsInside(args, argc); return true;
        case SYM_GEN_getEmptyCells_925: out = fn_getEmptyCells(args, argc); return true;
        case SYM_GEN_getEmptyGlobalPositions_926: out = fn_getEmptyGlobalPositions(args, argc); return true;
        case SYM_GEN_getAffectedItemsInside_927: out = fn_getAffectedItemsInside(args, argc); return true;
        case SYM_GEN_previewCanAffect_475: out = fn_previewCanAffect(args, argc); return true;
        case SYM_GEN_prepare_124: out = fn_prepare(args, argc); return true;
        case SYM_GEN_combatToShop_744: out = fn_combatToShop(args, argc); return true;
        case SYM_GEN_getCraftableNeighbors_494: out = fn_getCraftableNeighbors(args, argc); return true;
        case SYM_GEN_onItemAdded_439: out = fn_onItemAdded(args, argc); return true;
        case SYM_GEN_onAffectedItemInsideAdded_928: out = fn_onAffectedItemInsideAdded(args, argc); return true;
        case SYM_GEN_onItemRemoved_440: out = fn_onItemRemoved(args, argc); return true;
        case SYM_GEN_onAffectedItemInsideRemoved_929: out = fn_onAffectedItemInsideRemoved(args, argc); return true;
        case SYM_GEN_pushItemsInsideToStorage_400: out = fn_pushItemsInsideToStorage(args, argc); return true;
        case SYM_GEN_onDraggedWithParentStart_718: out = fn_onDraggedWithParentStart(args, argc); return true;
        case SYM_GEN_onDraggedWithParentEnd_720: out = fn_onDraggedWithParentEnd(args, argc); return true;
        case SYM_GEN_getNumAffectedInside_930: out = fn_getNumAffectedInside(args, argc); return true;
        case SYM_GEN_getNumAffectedInside_type_931: out = fn_getNumAffectedInside_type(args, argc); return true;
        case SYM_GEN_getBagMultiplicity_932: out = fn_getBagMultiplicity(args, argc); return true;
        case SYM_GEN_discard_764: out = fn_discard(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Bag::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Bag::fn_getHoverPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_dragged)) {
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
    return (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isBag_85, nullptr, 0)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_920, _ca, 1); })())) : gd::GdVal::from_bool(false));
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
    (void)([&]() { gd::GdVal _ca[] = {lv__inventory, lv__occupiedCells, lv__placedByPlayer}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_addToInventory_122, _ca, 3, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_getBagLayerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getRarity_238, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Rarity_862), SYM_GEN_Unique_2757))))) {
        return gd::GdVal::from_int(2LL);
    }
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasBagEffect_922, nullptr, 0))) {
        return gd::GdVal::from_int(1LL);
    }
    return gd::GdVal::from_int(0LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_hasBagEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_ne(this->f_border, gd::GdVal::null()));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn__process(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    if (gd::gd_truth(this->f_dragged)) {
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1284), SYM_GEN_INVENTORY_1093), SYM_GEN_canAddBag_2758, _ca, 1); })())) {
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
    return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0), gd::SYM_empty, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_getItemsInside(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, this->f_cachedInsideItems, gd::SYM_empty, nullptr, 0))))) {
        return this->f_cachedInsideItems;
    }
    return ([&]() { gd::GdVal _ca[] = {this->f_occupiedCells}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItemsInCells_1517, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_getEmptyCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_emptyCells = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1404 = gd::gd_iter_seq(gd_ctx.arena, this->f_occupiedCells);
        gd::GdArr* _t1405 = (_t1404.kind == gd::GdVal::Kind::Arr) ? _t1404.arr : nullptr;
        uint32_t _len__t1406 = _t1405 ? _t1405->len : 0u;
        for (uint32_t _t1406 = 0; _t1406 < _len__t1406; ++_t1406) {
            gd::GdVal lv_cell = _t1405->data[_t1406];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_cell}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_isCellEmpty_1514, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_cell}; return gd::call_method(gd_ctx, lv_emptyCells, gd::SYM_push_back, _ca, 1); })();
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
        gd::GdVal _t1407 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getEmptyCells_925, nullptr, 0));
        gd::GdArr* _t1408 = (_t1407.kind == gd::GdVal::Kind::Arr) ? _t1407.arr : nullptr;
        uint32_t _len__t1409 = _t1408 ? _t1408->len : 0u;
        for (uint32_t _t1409 = 0; _t1409 < _len__t1409; ++_t1409) {
            gd::GdVal lv_cell = _t1408->data[_t1409];
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_cell, gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_cellToGlobalPos_2759, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_positions, gd::SYM_push_back, _ca, 1); })();
        }
    }
    return lv_positions;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_getAffectedItemsInside(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_placed)))) {
        return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    }
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, this->f_cachedAffectedInsideItems, gd::SYM_empty, nullptr, 0))))) {
        return this->f_cachedAffectedInsideItems;
    }
    gd::GdVal lv_affected = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1410 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0));
        gd::GdArr* _t1411 = (_t1410.kind == gd::GdVal::Kind::Arr) ? _t1410.arr : nullptr;
        uint32_t _len__t1412 = _t1411 ? _t1411->len : 0u;
        for (uint32_t _t1412 = 0; _t1412 < _len__t1412; ++_t1412) {
            gd::GdVal lv_item = _t1411->data[_t1412];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_920, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, lv_affected, gd::SYM_push_back, _ca, 1); })();
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
    this->f_cachedInsideItems = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0);
    {
        gd::GdVal _t1413 = gd::gd_iter_seq(gd_ctx.arena, this->f_cachedInsideItems);
        gd::GdArr* _t1414 = (_t1413.kind == gd::GdVal::Kind::Arr) ? _t1413.arr : nullptr;
        uint32_t _len__t1415 = _t1414 ? _t1414->len : 0u;
        for (uint32_t _t1415 = 0; _t1415 < _len__t1415; ++_t1415) {
            gd::GdVal lv_item = _t1414->data[_t1415];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_920, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, this->f_cachedAffectedInsideItems, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_prepare_124, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_combatToShop(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_cachedAffectedInsideItems, gd::SYM_clear, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_cachedInsideItems, gd::SYM_clear, nullptr, 0);
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_combatToShop_744, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_getCraftableNeighbors(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_craftableItems = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1416 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0));
        gd::GdArr* _t1417 = (_t1416.kind == gd::GdVal::Kind::Arr) ? _t1416.arr : nullptr;
        uint32_t _len__t1418 = _t1417 ? _t1417->len : 0u;
        for (uint32_t _t1418 = 0; _t1418 < _len__t1418; ++_t1418) {
            gd::GdVal lv_item = _t1417->data[_t1418];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isAvailableForCrafting_495, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, lv_craftableItems, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    return lv_craftableItems;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_onItemAdded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_onItemAdded_439, _ca, 1, _out); return _out; })();
    if (gd::gd_truth((gd::gd_truth(gd::gd_in(lv_item, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_920, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        if (gd::gd_truth(gd::get_prop(gd_ctx, lv_item, SYM_GEN_placedByPlayer_52))) {
        }
        (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAffectedItemInsideAdded_928, _ca, 1); })();
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
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_onItemRemoved_440, _ca, 1, _out); return _out; })();
    if (gd::gd_truth((gd::gd_truth(gd::gd_in(lv_item, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_920, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAffectedItemInsideRemoved_929, _ca, 1); })();
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
    if (gd::gd_truth(this->f_dragged)) {
    }
    else {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetZ_452, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_getNumAffectedInside(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_num = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t1419 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_927, nullptr, 0));
        gd::GdArr* _t1420 = (_t1419.kind == gd::GdVal::Kind::Arr) ? _t1419.arr : nullptr;
        uint32_t _len__t1421 = _t1420 ? _t1420->len : 0u;
        for (uint32_t _t1421 = 0; _t1421 < _len__t1421; ++_t1421) {
            gd::GdVal lv_item = _t1420->data[_t1421];
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
        gd::GdVal _t1422 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_927, nullptr, 0));
        gd::GdArr* _t1423 = (_t1422.kind == gd::GdVal::Kind::Arr) ? _t1422.arr : nullptr;
        uint32_t _len__t1424 = _t1423 ? _t1423->len : 0u;
        for (uint32_t _t1424 = 0; _t1424 < _len__t1424; ++_t1424) {
            gd::GdVal lv_item = _t1423->data[_t1424];
            lv_num = gd::gd_add(gd_ctx, lv_num, ([&]() { gd::GdVal _ca[] = {lv_type}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_getTypeMultiplicity_82, _ca, 1); })());
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
    if (gd::gd_truth(this->f_pooled)) {
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_discardGems}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_discard_764, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_bagTilemapPosition, gd::GdVal::null())))) {
    }
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Bag(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Bag>(&ctx); }
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
        case SYM_GEN_isGem_86: return true;
        case SYM_GEN_isOwnable_252: return true;
        case SYM_GEN_isOwnedByOpponent_253: return true;
        case SYM_GEN_getEffectiveOwnerType_259: return true;
        case SYM_GEN_getInventory_658: return true;
        case SYM_GEN_getItem_391: return true;
        case SYM_GEN_isPlaced_78: return true;
        case SYM_GEN_isInInventory_971: return true;
        case SYM_GEN_getGemMode_972: return true;
        case SYM_GEN_getGemPower_973: return true;
        case SYM_GEN_changeGemPower_974: return true;
        case SYM_GEN_getHoverPriority_692: return true;
        case SYM_GEN_character_76: return true;
        case SYM_GEN__process_682: return true;
        case SYM_GEN_previewCellCollision_473: return true;
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
        case SYM_GEN_returnToSocket_401: return true;
        case SYM_GEN_hasCooldown_97: return true;
        case SYM_GEN_miniActivate_472: return true;
        case SYM_GEN_prepareInventory_981: return true;
        case SYM_GEN_prepareWeapon_982: return true;
        case SYM_GEN_prepareArmor_983: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_combatStartInventory_984: return true;
        case SYM_GEN_combatStartWeapon_985: return true;
        case SYM_GEN_combatStartArmor_986: return true;
        case SYM_GEN_combatStart_129: return true;
        case SYM_GEN_combatEndInventory_987: return true;
        case SYM_GEN_combatEndWeapon_988: return true;
        case SYM_GEN_combatEndArmor_989: return true;
        case SYM_GEN_combatEnd_133: return true;
        case SYM_GEN_shopEntered_745: return true;
        case SYM_GEN_getBaseDescription_990: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN_onHotSwapHoverWithGem_991: return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_992: return true;
        case SYM_GEN_createGemParticles_993: return true;
        case SYM_GEN_canPreviewFusions_828: return true;
        case SYM_GEN_canModifyChance_295: return true;
        case SYM_GEN_getNeighborItemsAndGems_491: return true;
        case SYM_GEN_canCombine_447: return true;
        case SYM_GEN_shift_456: return true;
        case SYM_GEN_isMovingBack_801: return true;
        case SYM_GEN_addToStorageBox_667: return true;
        case SYM_GEN_discard_764: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Gems__Gem::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_isGem_86: out = fn_isGem(args, argc); return true;
        case SYM_GEN_isOwnable_252: out = fn_isOwnable(args, argc); return true;
        case SYM_GEN_isOwnedByOpponent_253: out = fn_isOwnedByOpponent(args, argc); return true;
        case SYM_GEN_getEffectiveOwnerType_259: out = fn_getEffectiveOwnerType(args, argc); return true;
        case SYM_GEN_getInventory_658: out = fn_getInventory(args, argc); return true;
        case SYM_GEN_getItem_391: out = fn_getItem(args, argc); return true;
        case SYM_GEN_isPlaced_78: out = fn_isPlaced(args, argc); return true;
        case SYM_GEN_isInInventory_971: out = fn_isInInventory(args, argc); return true;
        case SYM_GEN_getGemMode_972: out = fn_getGemMode(args, argc); return true;
        case SYM_GEN_getGemPower_973: out = fn_getGemPower(args, argc); return true;
        case SYM_GEN_changeGemPower_974: out = fn_changeGemPower(args, argc); return true;
        case SYM_GEN_getHoverPriority_692: out = fn_getHoverPriority(args, argc); return true;
        case SYM_GEN_character_76: out = fn_character(args, argc); return true;
        case SYM_GEN__process_682: out = fn__process(args, argc); return true;
        case SYM_GEN_previewCellCollision_473: out = fn_previewCellCollision(args, argc); return true;
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
        case SYM_GEN_returnToSocket_401: out = fn_returnToSocket(args, argc); return true;
        case SYM_GEN_hasCooldown_97: out = fn_hasCooldown(args, argc); return true;
        case SYM_GEN_miniActivate_472: out = fn_miniActivate(args, argc); return true;
        case SYM_GEN_prepareInventory_981: out = fn_prepareInventory(args, argc); return true;
        case SYM_GEN_prepareWeapon_982: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_prepareArmor_983: out = fn_prepareArmor(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_combatStartInventory_984: out = fn_combatStartInventory(args, argc); return true;
        case SYM_GEN_combatStartWeapon_985: out = fn_combatStartWeapon(args, argc); return true;
        case SYM_GEN_combatStartArmor_986: out = fn_combatStartArmor(args, argc); return true;
        case SYM_GEN_combatStart_129: out = fn_combatStart(args, argc); return true;
        case SYM_GEN_combatEndInventory_987: out = fn_combatEndInventory(args, argc); return true;
        case SYM_GEN_combatEndWeapon_988: out = fn_combatEndWeapon(args, argc); return true;
        case SYM_GEN_combatEndArmor_989: out = fn_combatEndArmor(args, argc); return true;
        case SYM_GEN_combatEnd_133: out = fn_combatEnd(args, argc); return true;
        case SYM_GEN_shopEntered_745: out = fn_shopEntered(args, argc); return true;
        case SYM_GEN_getBaseDescription_990: out = fn_getBaseDescription(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_onHotSwapHoverWithGem_991: out = fn_onHotSwapHoverWithGem(args, argc); return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_992: out = fn_onHotSwapHoverWithGemEnd(args, argc); return true;
        case SYM_GEN_createGemParticles_993: out = fn_createGemParticles(args, argc); return true;
        case SYM_GEN_canPreviewFusions_828: out = fn_canPreviewFusions(args, argc); return true;
        case SYM_GEN_canModifyChance_295: out = fn_canModifyChance(args, argc); return true;
        case SYM_GEN_getNeighborItemsAndGems_491: out = fn_getNeighborItemsAndGems(args, argc); return true;
        case SYM_GEN_canCombine_447: out = fn_canCombine(args, argc); return true;
        case SYM_GEN_shift_456: out = fn_shift(args, argc); return true;
        case SYM_GEN_isMovingBack_801: out = fn_isMovingBack(args, argc); return true;
        case SYM_GEN_addToStorageBox_667: out = fn_addToStorageBox(args, argc); return true;
        case SYM_GEN_discard_764: out = fn_discard(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_socket, gd::GdVal::null())))) {
        return gd::call_method(gd_ctx, gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_391, nullptr, 0), SYM_GEN_isOwnable_252, nullptr, 0);
    }
    else {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_isOwnable_252, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_isOwnedByOpponent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_socket, gd::GdVal::null())))) {
        return gd::call_method(gd_ctx, gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_391, nullptr, 0), SYM_GEN_isOwnedByOpponent_253, nullptr, 0);
    }
    else {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_isOwnedByOpponent_253, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_getEffectiveOwnerType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_socket, gd::GdVal::null())))) {
        return gd::call_method(gd_ctx, gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_391, nullptr, 0), SYM_GEN_getEffectiveOwnerType_259, nullptr, 0);
    }
    else {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getEffectiveOwnerType_259, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_getInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_socket, gd::GdVal::null())))) {
        return gd::call_method(gd_ctx, gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_391, nullptr, 0), SYM_GEN_getInventory_658, nullptr, 0);
    }
    else {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getInventory_658, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_getItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_socket, gd::GdVal::null())))) {
        return gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_391, nullptr, 0);
    }
    else {
        return gd::GdVal::null();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_isPlaced(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_socket, gd::GdVal::null())))) {
        return gd::call_method(gd_ctx, gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_391, nullptr, 0), SYM_GEN_isPlaced_78, nullptr, 0);
    }
    else {
        return this->f_placed;
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_isInInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_socket, gd::GdVal::null())))) {
        return gd::call_method(gd_ctx, gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_391, nullptr, 0), SYM_GEN_isInInventory_971, nullptr, 0);
    }
    else {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_isInInventory_971, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_getGemMode(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_socket, gd::GdVal::null())))) {
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_391, nullptr, 0), SYM_GEN_isWeapon_84, nullptr, 0))) {
            return gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Weapon_2666);
        }
        else {
            return gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Armor_2751);
        }
    }
    else {
        if (gd::gd_truth(this->f_placed)) {
            return gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Inventory_2755);
        }
        else {
            return gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Inactive_2594);
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
    if (gd::gd_truth(this->f_dragged)) {
        return Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_DRAG_PRIORITY_527);
    }
    else {
        return gd::GdVal::from_int(1LL);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_character(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_972, nullptr, 0), gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Inactive_2594))))) {
        return gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1284);
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_972, nullptr, 0), gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Inventory_2755))))) {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_character_76, nullptr, 0, _out); return _out; })();
    }
    else {
        return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_391, nullptr, 0), SYM_GEN_character_76, nullptr, 0);
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
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_hoveredSocket))) ? gd::GdVal::from_bool(gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_movebackSocket))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_frame_counter_1384), gd::gd_add(gd_ctx, this->f_pickupFrame, gd::GdVal::from_int(1LL))))))))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_previewCellCollision_473, nullptr, 0, _out); return _out; })();
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
    gd::GdVal lv_pickupType = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_PickupType_866), SYM_GEN_Grabbed_2634));
    (void)([&]() { gd::GdVal _ca[] = {lv_pickupType}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_pickup_717, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_socket, gd::GdVal::null())))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_killDropTween_980, nullptr, 0);
        this->f_movebackSocket = this->f_socket;
        this->f_hoveredSocket = this->f_socket;
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_391, nullptr, 0), SYM_GEN_ownerType_51), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_PlayerStorageBox_2580))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setFaceDirection_480, _ca, 1); })();
        }
        else {
            this->f_faceDirection = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGlobalFaceDirection_468, nullptr, 0));
        }
        (void)gd::call_method(gd_ctx, this->f_socket, SYM_GEN_onPickupGem_2773, nullptr, 0);
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_killDropTween_980, nullptr, 0);
    gd::GdVal lv_s = this->f_socket;
    (void)gd::call_method(gd_ctx, this->f_socket, SYM_GEN_onPickupGem_2773, nullptr, 0);
    (void)gd::call_method(gd_ctx, lv_s, SYM_GEN_hideSocket_2774, nullptr, 0);
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
    gd::GdVal lv_gemMode = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_972, nullptr, 0);
    return (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_gemMode, gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Inventory_2755)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_gemMode, gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Inactive_2594))))))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_hasCooldown_97, nullptr, 0, _out); return _out; })())) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_miniActivate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_miniActivate_472, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.5)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_Scale_775, _ca, 1); })();
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
        gd::GdVal _t1425 = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_972, nullptr, 0);
        if (gd::gd_eq(_t1425, gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Inventory_2755))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_prepareInventory_981, nullptr, 0);
        }
        else if (gd::gd_eq(_t1425, gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Weapon_2666))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_prepareWeapon_982, nullptr, 0);
        }
        else if (gd::gd_eq(_t1425, gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Armor_2751))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_prepareArmor_983, nullptr, 0);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_combatStart_129, nullptr, 0, _out); return _out; })();
    this->f_iterationCooldown = gd::gd_coerce_float(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_adjustCooldown_109, nullptr, 0));
    this->f_triggerTime = gd::gd_coerce_float(this->f_iterationCooldown);
    {
        gd::GdVal _t1426 = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_972, nullptr, 0);
        if (gd::gd_eq(_t1426, gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Inventory_2755))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_combatStartInventory_984, nullptr, 0);
        }
        else if (gd::gd_eq(_t1426, gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Weapon_2666))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_combatStartWeapon_985, nullptr, 0);
        }
        else if (gd::gd_eq(_t1426, gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Armor_2751))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_combatStartArmor_986, nullptr, 0);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_combatEnd_133, nullptr, 0, _out); return _out; })();
    {
        gd::GdVal _t1427 = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_972, nullptr, 0);
        if (gd::gd_eq(_t1427, gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Inventory_2755))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_combatEndInventory_987, nullptr, 0);
        }
        else if (gd::gd_eq(_t1427, gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Weapon_2666))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_combatEndWeapon_988, nullptr, 0);
        }
        else if (gd::gd_eq(_t1427, gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Armor_2751))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_combatEndArmor_989, nullptr, 0);
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
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseDescription_990, _ca, 1); })();
    gd::GdVal lv_colors = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_inactiveColor_2731), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_inactiveColor_2731), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_inactiveColor_2731)}));
    gd::GdVal lv_gemMode = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_972, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_gemMode, gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Inactive_2594))))) {
        { gd::GdVal _t1428 = lv_colors; gd::GdVal _t1429 = lv_gemMode; gd::set_index(gd_ctx, _t1428, _t1429, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_modifiedColor_2724)); }
    }
    return ([&]() { gd::GdVal _ca[] = {lv_descr, lv_colors, gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModeDescription_645, _ca, 4); })();
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
    if (gd::gd_truth(this->f_socket)) {
        return gd::call_method(gd_ctx, gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_391, nullptr, 0), SYM_GEN_canPreviewFusions_828, nullptr, 0);
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
    if (gd::gd_truth(this->f_socket)) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_391, nullptr, 0), SYM_GEN_ownerType_51), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_PlayerStorageBox_2580))))) {
            return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
        }
        gd::GdVal lv_neighbors = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_391, nullptr, 0)}));
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_391, nullptr, 0), SYM_GEN_getNeighborItemsAndGems_491, nullptr, 0)}; return gd::call_method(gd_ctx, lv_neighbors, gd::SYM_append_array, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, lv_neighbors, gd::SYM_erase, _ca, 1); })();
        return lv_neighbors;
    }
    else {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getNeighborItemsAndGems_491, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_canCombine(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_socket)) {
        return gd::GdVal::from_bool(true);
    }
    else {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_canCombine_447, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_shift(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_direction = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_socket)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_direction}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_shift_456, _ca, 1, _out); return _out; })();
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
    if (gd::gd_truth(this->f_socket)) {
        gd::GdVal lv_s = this->f_socket;
        (void)([&]() { gd::GdVal _ca[] = {lv_addImpulse, lv_tweenBouncyness, lv_checkCollisions, lv_targetPos, lv_speed, lv_secondCheck}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_addToStorageBox_667, _ca, 6, _out); return _out; })();
        (void)gd::call_method(gd_ctx, lv_s, SYM_GEN_onPickupGem_2773, nullptr, 0);
        (void)gd::call_method(gd_ctx, lv_s, SYM_GEN_hideSocket_2774, nullptr, 0);
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
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_socket, gd::GdVal::null())))) {
        gd::set_prop(gd_ctx, this->f_socket, SYM_GEN_gem_2775, gd::GdVal::null());
        (void)gd::call_method(gd_ctx, this->f_socket, SYM_GEN_hideSocket_2774, nullptr, 0);
        this->f_socket = gd::GdVal::null();
        this->f_movebackSocket = gd::GdVal::null();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_gateItem_1597), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Box of Riches", 13u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })())))) {
        if (gd::gd_truth(gd::call_method(gd_ctx, this->f_specificDragParticles, gd::SYM_empty, nullptr, 0))) {
        }
    }
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Gems__Gem(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Gems__Gem>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Gems__Gem = {CLS_Gd__gd_core_items__Gems__Gem, "Gem", "res://gd_core_items/Gems/Gem.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Gems__Gem, &Gd__gd_core_items__Gems__Gem::get_static_prop_fn, &Gd__gd_core_items__Gems__Gem::call_static_fn};

static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreEvent_Target[] = {{"Player", 0LL}, {"Opponent", 1LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreEvent_Target = {"Target", _ekv_Gd__gd_core__CoreEvent_Target, 2u};
void Gd__gd_core__CoreEvent::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_id = gd::GdVal::from_int(0);
    this->f_timestamp = gd::GdVal::null();
    this->f_parentEvent = gd::GdVal::null();
    this->f_origin = gd::GdVal::null();
    this->f_type = gd::GdVal::null();
    this->f_target = gd::GdVal::null();
    this->f_params = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_formatParams = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
}
const gd::GdClassMeta* Gd__gd_core__CoreEvent::meta() const { return &META_Gd__gd_core__CoreEvent; }
gd::GdVal Gd__gd_core__CoreEvent::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_Target_1492: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreEvent_Target);
        default: break;
    }
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreEvent::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreEvent::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_id_1475: out = this->f_id; return true;
        case SYM_GEN_timestamp_1476: out = this->f_timestamp; return true;
        case SYM_GEN_parentEvent_1477: out = this->f_parentEvent; return true;
        case SYM_GEN_origin_1455: out = this->f_origin; return true;
        case SYM_GEN_type_1005: out = this->f_type; return true;
        case SYM_GEN_target_1478: out = this->f_target; return true;
        case SYM_GEN_params_1479: out = this->f_params; return true;
        case SYM_GEN_formatParams_1480: out = this->f_formatParams; return true;
        case SYM_GEN_Target_1492: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreEvent_Target); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreEvent::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_id_1475: this->f_id = gd::gd_coerce_int(val); return true;
        case SYM_GEN_timestamp_1476: this->f_timestamp = val; return true;
        case SYM_GEN_parentEvent_1477: this->f_parentEvent = val; return true;
        case SYM_GEN_origin_1455: this->f_origin = val; return true;
        case SYM_GEN_type_1005: this->f_type = val; return true;
        case SYM_GEN_target_1478: this->f_target = val; return true;
        case SYM_GEN_params_1479: this->f_params = val; return true;
        case SYM_GEN_formatParams_1480: this->f_formatParams = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreEvent::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_getType_1481: return true;
        case SYM_GEN_setTarget_1482: return true;
        case SYM_GEN_setParam_1483: return true;
        case SYM_GEN_getParam_1484: return true;
        case SYM_GEN_getAmount_1485: return true;
        case SYM_GEN_getAmountWithDefault_1486: return true;
        case SYM_GEN_hasParam_1487: return true;
        case SYM_GEN_getMainActor_1488: return true;
        case SYM_GEN_getOrigin_1489: return true;
        case SYM_GEN_fromCharacter_1490: return true;
        case SYM_GEN_getDepth_1491: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreEvent::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_getType_1481: out = fn_getType(args, argc); return true;
        case SYM_GEN_setTarget_1482: out = fn_setTarget(args, argc); return true;
        case SYM_GEN_setParam_1483: out = fn_setParam(args, argc); return true;
        case SYM_GEN_getParam_1484: out = fn_getParam(args, argc); return true;
        case SYM_GEN_getAmount_1485: out = fn_getAmount(args, argc); return true;
        case SYM_GEN_getAmountWithDefault_1486: out = fn_getAmountWithDefault(args, argc); return true;
        case SYM_GEN_hasParam_1487: out = fn_hasParam(args, argc); return true;
        case SYM_GEN_getMainActor_1488: out = fn_getMainActor(args, argc); return true;
        case SYM_GEN_getOrigin_1489: out = fn_getOrigin(args, argc); return true;
        case SYM_GEN_fromCharacter_1490: out = fn_fromCharacter(args, argc); return true;
        case SYM_GEN_getDepth_1491: out = fn_getDepth(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreEvent::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return false;
}
gd::GdVal Gd__gd_core__CoreEvent::fn__init(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__id = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__timestamp = (_argc > 1) ? _args[1] : (gd::GdVal::from_float(0.0));
    gd::GdVal lv__parentEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv__origin = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv__type = (_argc > 4) ? _args[4] : (gd::GdVal::null());
    this->f_id = gd::gd_coerce_int(lv__id);
    this->f_timestamp = lv__timestamp;
    this->f_parentEvent = lv__parentEvent;
    this->f_origin = lv__origin;
    this->f_type = lv__type;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEvent::fn_getType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_type;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEvent::fn_setTarget(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__target = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_target = lv__target;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEvent::fn_setParam(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_paramName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_paramVal = (_argc > 1) ? _args[1] : gd::GdVal::null();
    { gd::GdVal _t1430 = this->f_params; gd::GdVal _t1431 = lv_paramName; gd::set_index(gd_ctx, _t1430, _t1431, lv_paramVal); }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEvent::fn_getParam(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_paramName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_default = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_paramName, lv_default}; return gd::call_method(gd_ctx, this->f_params, gd::SYM_get, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEvent::fn_getAmount(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_index(gd_ctx, this->f_params, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "amount", 6u)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEvent::fn_getAmountWithDefault(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_default = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "amount", 6u)), lv_default}; return gd::call_method(gd_ctx, this->f_params, gd::SYM_get, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEvent::fn_hasParam(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_param = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::gd_in(lv_param, this->f_params);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEvent::fn_getMainActor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(this->f_origin, &META_Gd__gd_core__CoreItem)))) {
        return gd::get_prop(gd_ctx, gd::call_method(gd_ctx, this->f_origin, SYM_GEN_character_76, nullptr, 0), SYM_GEN_playerId_1046);
    }
    else if (gd::gd_truth(this->f_target)) {
        return this->f_target;
    }
    else {
        return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCharacter), SYM_GEN_ID_1279), SYM_GEN_PLAYER_2540);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEvent::fn_getOrigin(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_origin;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEvent::fn_fromCharacter(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_character = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(this->f_origin, &META_Gd__gd_core__CoreItem))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, this->f_origin, SYM_GEN_character_76, nullptr, 0), lv_character)))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEvent::fn_getDepth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_parentEvent)) {
        return gd::gd_add(gd_ctx, gd::call_method(gd_ctx, this->f_parentEvent, SYM_GEN_getDepth_1491, nullptr, 0), gd::GdVal::from_int(1LL));
    }
    else {
        return gd::GdVal::from_int(0LL);
    }
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreEvent(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__CoreEvent>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__CoreEvent = {CLS_Gd__gd_core__CoreEvent, "CoreEvent", "res://gd_core/CoreEvent.gd", nullptr, false, _alloc_Gd__gd_core__CoreEvent, &Gd__gd_core__CoreEvent::get_static_prop_fn, &Gd__gd_core__CoreEvent::call_static_fn};

void Gd__gd_core__Crossblades::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__Crossblades::meta() const { return &META_Gd__gd_core__Crossblades; }
gd::GdVal Gd__gd_core__Crossblades::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Crossblades::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Crossblades::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__Crossblades::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Crossblades::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_canAffect_secondary_289: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_getCraftingOffset_850: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__Crossblades::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_289: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_getCraftingOffset_850: out = fn_getCraftingOffset(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Crossblades::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Crossblades::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_92, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crossblades::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_97, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crossblades::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1432 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, _ca, 1); })());
        gd::GdArr* _t1433 = (_t1432.kind == gd::GdVal::Kind::Arr) ? _t1432.arr : nullptr;
        uint32_t _len__t1434 = _t1433 ? _t1433->len : 0u;
        for (uint32_t _t1434 = 0; _t1434 < _len__t1434; ++_t1434) {
            gd::GdVal lv_item = _t1433->data[_t1434];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_163, _ca, 1); })();
        }
    }
    {
        gd::GdVal _t1435 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Secondary_2583)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, _ca, 1); })());
        gd::GdArr* _t1436 = (_t1435.kind == gd::GdVal::Kind::Arr) ? _t1435.arr : nullptr;
        uint32_t _len__t1437 = _t1436 ? _t1436->len : 0u;
        for (uint32_t _t1437 = 0; _t1437 < _len__t1437; ++_t1437) {
            gd::GdVal lv_item = _t1436->data[_t1437];
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_275, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crossblades::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_163, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crossblades::fn_getCraftingOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1438 = lv_forDirection;
        if (gd::gd_eq(_t1438, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
        else if (gd::gd_eq(_t1438, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
        else if (gd::gd_eq(_t1438, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_LEFT))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
        else if (gd::gd_eq(_t1438, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_RIGHT))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crossblades::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Crossblades(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Crossblades>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Crossblades = {CLS_Gd__gd_core__Crossblades, "Crossblades", "res://gd_core/Crossblades.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__Crossblades, &Gd__gd_core__Crossblades::get_static_prop_fn, &Gd__gd_core__Crossblades::call_static_fn};

void Gd__gd_core__Eggscalibur::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Pan::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__Eggscalibur::meta() const { return &META_Gd__gd_core__Eggscalibur; }
gd::GdVal Gd__gd_core__Eggscalibur::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Pan::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Eggscalibur::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Eggscalibur::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Pan::get_prop(prop, out);
}
bool Gd__gd_core__Eggscalibur::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Pan::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Eggscalibur::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Pan::has_own_method(m);
}
bool Gd__gd_core__Eggscalibur::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Pan::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Eggscalibur::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Pan::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Eggscalibur::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseMana_335, _ca, 2); })();
    if (gd::gd_truth(lv_event)) {
        gd::GdVal lv_affected = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0);
        (void)gd::call_method(gd_ctx, lv_affected, gd::SYM_shuffle, nullptr, 0);
        {
            gd::GdVal _t1439 = gd::gd_iter_seq(gd_ctx.arena, lv_affected);
            gd::GdArr* _t1440 = (_t1439.kind == gd::GdVal::Kind::Arr) ? _t1439.arr : nullptr;
            uint32_t _len__t1441 = _t1440 ? _t1440->len : 0u;
            for (uint32_t _t1441 = 0; _t1441 < _len__t1441; ++_t1441) {
                gd::GdVal lv_food = _t1440->data[_t1441];
                (void)gd::call_method(gd_ctx, lv_food, SYM_GEN_doCooldownEffect_146, nullptr, 0);
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Eggscalibur::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Pan::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Eggscalibur(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Eggscalibur>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Eggscalibur = {CLS_Gd__gd_core__Eggscalibur, "Eggscalibur", "res://gd_core/Eggscalibur.gd", &META_Gd__gd_core_items__Pan, false, _alloc_Gd__gd_core__Eggscalibur, &Gd__gd_core__Eggscalibur::get_static_prop_fn, &Gd__gd_core__Eggscalibur::call_static_fn};

void Gd__gd_core__HeartofDarkness::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_activated = gd::GdVal::from_bool(false);
    this->f_regenNeeded = gd::GdVal::null();
    this->f_numStealedBuffs = gd::GdVal::null();
    this->f_fillAnimation = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__HeartofDarkness::meta() const { return &META_Gd__gd_core__HeartofDarkness; }
gd::GdVal Gd__gd_core__HeartofDarkness::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__HeartofDarkness::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__HeartofDarkness::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activated_1296: out = this->f_activated; return true;
        case SYM_GEN_regenNeeded_942: out = this->f_regenNeeded; return true;
        case SYM_GEN_numStealedBuffs_1797: out = this->f_numStealedBuffs; return true;
        case SYM_GEN_fillAnimation_1795: out = this->f_fillAnimation; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__HeartofDarkness::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activated_1296: this->f_activated = val; return true;
        case SYM_GEN_regenNeeded_942: this->f_regenNeeded = val; return true;
        case SYM_GEN_numStealedBuffs_1797: this->f_numStealedBuffs = val; return true;
        case SYM_GEN_fillAnimation_1795: this->f_fillAnimation = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__HeartofDarkness::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onRegenChanged_1796: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__HeartofDarkness::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onRegenChanged_1796: out = fn_onRegenChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__HeartofDarkness::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__HeartofDarkness::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Dark_2602)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeartofDarkness::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_regeneration_changed", 30u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onRegenChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "darkspeed", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })()), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeartofDarkness::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_numStealedBuffs, gd::GdVal::null(), gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Regeneration_2569)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealRandomBuff_375, _ca, 4); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeartofDarkness::fn_onRegenChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_activated)))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getRegeneration_1217, nullptr, 0), this->f_regenNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_regenNeeded, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_348, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_319, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_219, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healreduction", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_reduceHealingEfficiency_1167, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeartofDarkness::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeartofDarkness::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_856), SYM_GEN_High_2603);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeartofDarkness::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_filled = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_activated, lv_filled)))) {
        return gd::GdVal::null();
    }
    this->f_activated = lv_filled;
    if (gd::gd_truth(lv_filled)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeartofDarkness::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_regenNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regent", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_numStealedBuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffsteal", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__HeartofDarkness(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__HeartofDarkness>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__HeartofDarkness = {CLS_Gd__gd_core__HeartofDarkness, "HeartofDarkness", "res://gd_core/HeartofDarkness.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__HeartofDarkness, &Gd__gd_core__HeartofDarkness::get_static_prop_fn, &Gd__gd_core__HeartofDarkness::call_static_fn};

void Gd__gd_core__LuckyClover::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__LuckyClover::meta() const { return &META_Gd__gd_core__LuckyClover; }
gd::GdVal Gd__gd_core__LuckyClover::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__LuckyClover::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__LuckyClover::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__LuckyClover::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__LuckyClover::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__LuckyClover::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__LuckyClover::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__LuckyClover::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_383, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LuckyClover::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__LuckyClover(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__LuckyClover>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__LuckyClover = {CLS_Gd__gd_core__LuckyClover, "LuckyClover", "res://gd_core/LuckyClover.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__LuckyClover, &Gd__gd_core__LuckyClover::get_static_prop_fn, &Gd__gd_core__LuckyClover::call_static_fn};

void Gd__gd_core__Pineapple::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Food::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__Pineapple::meta() const { return &META_Gd__gd_core__Pineapple; }
gd::GdVal Gd__gd_core__Pineapple::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Pineapple::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Pineapple::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Food::get_prop(prop, out);
}
bool Gd__gd_core__Pineapple::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Pineapple::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Food::has_own_method(m);
}
bool Gd__gd_core__Pineapple::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Pineapple::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Pineapple::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_211, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Pineapple::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Food::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Pineapple(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Pineapple>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Pineapple = {CLS_Gd__gd_core__Pineapple, "Pineapple", "res://gd_core/Pineapple.gd", &META_Gd__gd_core__Food, false, _alloc_Gd__gd_core__Pineapple, &Gd__gd_core__Pineapple::get_static_prop_fn, &Gd__gd_core__Pineapple::call_static_fn};

void Gd__gd_core__RubyEgg::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__DragonEgg::init_fields(gd_ctx);
    this->f_reflects = gd::GdVal::null();
    this->f_heat = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__RubyEgg::meta() const { return &META_Gd__gd_core__RubyEgg; }
gd::GdVal Gd__gd_core__RubyEgg::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__DragonEgg::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__RubyEgg::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__RubyEgg::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_reflects_1881: out = this->f_reflects; return true;
        case SYM_GEN_heat_1801: out = this->f_heat; return true;
        default: break;
    }
    return Gd__gd_core__DragonEgg::get_prop(prop, out);
}
bool Gd__gd_core__RubyEgg::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_reflects_1881: this->f_reflects = val; return true;
        case SYM_GEN_heat_1801: this->f_heat = val; return true;
        default: break;
    }
    return Gd__gd_core__DragonEgg::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__RubyEgg::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreCombatStart_127: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__DragonEgg::has_own_method(m);
}
bool Gd__gd_core__RubyEgg::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreCombatStart_127: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__DragonEgg::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__RubyEgg::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__DragonEgg::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__RubyEgg::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_reflects}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveReflectStacks_202, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RubyEgg::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doCooldownEffect_146, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RubyEgg::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_withReflectStacks = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    lv_withReflectStacks = gd::gd_coerce_bool(lv_withReflectStacks);
    if (gd::gd_truth(lv_withReflectStacks)) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_reflects}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveReflectStacks_202, _ca, 1); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RubyEgg::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__DragonEgg::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_reflects = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0));
    this->f_heat = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__RubyEgg(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__RubyEgg>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__RubyEgg = {CLS_Gd__gd_core__RubyEgg, "RubyEgg", "res://gd_core/RubyEgg.gd", &META_Gd__gd_core__DragonEgg, false, _alloc_Gd__gd_core__RubyEgg, &Gd__gd_core__RubyEgg::get_static_prop_fn, &Gd__gd_core__RubyEgg::call_static_fn};

void Gd__gd_core_items__Potion::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_potionColor = gd::make_color_from_args(nullptr, 0);
    this->f_fluidTween = gd::GdVal::null();
    this->f_isFull = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
    this->f_connector = gd::GdVal::null();
    this->f_fluid = gd::GdVal::null();
    this->f_fluidGradientTex = gd::GdVal::null();
    this->f_fluidGradient = gd::GdVal::null();
    this->f_baseFoaminess = gd::GdVal::null();
    this->f_baseScroll = gd::GdVal::null();
    this->f_baseLevel = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Potion::meta() const { return &META_Gd__gd_core_items__Potion; }
gd::GdVal Gd__gd_core_items__Potion::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Potion::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Potion::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_potionColor_1743: out = this->f_potionColor; return true;
        case SYM_GEN_fluidTween_1744: out = this->f_fluidTween; return true;
        case SYM_GEN_isFull_1745: out = this->f_isFull; return true;
        case SYM_GEN_connector_885: out = this->f_connector; return true;
        case SYM_GEN_fluid_1746: out = this->f_fluid; return true;
        case SYM_GEN_fluidGradientTex_1747: out = this->f_fluidGradientTex; return true;
        case SYM_GEN_fluidGradient_1748: out = this->f_fluidGradient; return true;
        case SYM_GEN_baseFoaminess_1749: out = this->f_baseFoaminess; return true;
        case SYM_GEN_baseScroll_1750: out = this->f_baseScroll; return true;
        case SYM_GEN_baseLevel_1751: out = this->f_baseLevel; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Potion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_potionColor_1743: this->f_potionColor = val; return true;
        case SYM_GEN_fluidTween_1744: this->f_fluidTween = val; return true;
        case SYM_GEN_isFull_1745: this->f_isFull = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_connector_885: this->f_connector = val; return true;
        case SYM_GEN_fluid_1746: this->f_fluid = val; return true;
        case SYM_GEN_fluidGradientTex_1747: this->f_fluidGradientTex = val; return true;
        case SYM_GEN_fluidGradient_1748: this->f_fluidGradient = val; return true;
        case SYM_GEN_baseFoaminess_1749: this->f_baseFoaminess = val; return true;
        case SYM_GEN_baseScroll_1750: this->f_baseScroll = val; return true;
        case SYM_GEN_baseLevel_1751: this->f_baseLevel = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Potion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_prepare_124: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_isEmpty_923: return true;
        case gd::SYM_fill: return true;
        case gd::SYM_empty: return true;
        case SYM_GEN_drink_1752: return true;
        case SYM_GEN_consumePotion_1753: return true;
        case SYM_GEN_onTriggerPotion_1754: return true;
        case SYM_GEN_triggerPotion_1755: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN_activate_152: return true;
        case SYM_GEN_shopEntered_745: return true;
        case SYM_GEN_getAffectedCellsAfterRotate_primary_412: return true;
        case SYM_GEN_addToInventory_122: return true;
        case SYM_GEN_onRemoveFromInventory_420: return true;
        case SYM_GEN_onFusingAsIngredient_842: return true;
        case SYM_GEN_onAffectedItemAdded_437: return true;
        case SYM_GEN_onAffectedItemRemoved_438: return true;
        case SYM_GEN_updateConnector_1756: return true;
        case SYM_GEN_resetGradient_1757: return true;
        case SYM_GEN_discard_764: return true;
        case SYM_GEN_getStarPosition_1758: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Potion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_prepare_124: out = fn_prepare(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_isEmpty_923: out = fn_isEmpty(args, argc); return true;
        case gd::SYM_fill: out = fn_fill(args, argc); return true;
        case gd::SYM_empty: out = fn_empty(args, argc); return true;
        case SYM_GEN_drink_1752: out = fn_drink(args, argc); return true;
        case SYM_GEN_consumePotion_1753: out = fn_consumePotion(args, argc); return true;
        case SYM_GEN_onTriggerPotion_1754: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_triggerPotion_1755: out = fn_triggerPotion(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_activate_152: out = fn_activate(args, argc); return true;
        case SYM_GEN_shopEntered_745: out = fn_shopEntered(args, argc); return true;
        case SYM_GEN_getAffectedCellsAfterRotate_primary_412: out = fn_getAffectedCellsAfterRotate_primary(args, argc); return true;
        case SYM_GEN_addToInventory_122: out = fn_addToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_420: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_onFusingAsIngredient_842: out = fn_onFusingAsIngredient(args, argc); return true;
        case SYM_GEN_onAffectedItemAdded_437: out = fn_onAffectedItemAdded(args, argc); return true;
        case SYM_GEN_onAffectedItemRemoved_438: out = fn_onAffectedItemRemoved(args, argc); return true;
        case SYM_GEN_updateConnector_1756: out = fn_updateConnector(args, argc); return true;
        case SYM_GEN_resetGradient_1757: out = fn_resetGradient(args, argc); return true;
        case SYM_GEN_discard_764: out = fn_discard(args, argc); return true;
        case SYM_GEN_getStarPosition_1758: out = fn_getStarPosition(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Potion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Potion::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_prepare_124, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Potion_2652)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_isEmpty(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(!gd::gd_truth(this->f_isFull));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_fill(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_isFull = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_empty(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_isFull = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_drink(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_consumePotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_withActivate = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    lv_withActivate = gd::gd_coerce_bool(lv_withActivate);
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_923, nullptr, 0))) {
        return gd::GdVal::null();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drink_1752, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_triggerPotion_1755, _ca, 1); })();
    gd::GdVal lv_affected = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_affected, gd::SYM_empty, nullptr, 0))))) {
        (void)gd::call_method(gd_ctx, gd::get_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL)), SYM_GEN_triggerPotion_1755, nullptr, 0);
        (void)gd::call_method(gd_ctx, gd::get_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL)), SYM_GEN_miniActivate_472, nullptr, 0);
    }
    if (gd::gd_truth(lv_withActivate)) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_triggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onTriggerPotion_1754, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_778, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "potion_triggered", 16u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_obj(this)}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitSignal_1501, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__isFull = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv__isFull)) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_fill, nullptr, 0);
    }
    else {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_empty, nullptr, 0);
    }
    this->f_isFull = gd::gd_coerce_bool(lv__isFull);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_activate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_playCombatAni = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_consume = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(false));
    gd::GdVal lv_animationOverride = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_emitSignal = (_argc > 4) ? _args[4] : (gd::GdVal::from_bool(true));
    lv_emitSignal = gd::gd_coerce_bool(lv_emitSignal);
    (void)([&]() { gd::GdVal _ca[] = {lv_damageRes, lv_playCombatAni, lv_consume, gd::GdVal::null()}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_activate_152, _ca, 4, _out); return _out; })();
    if (gd::gd_truth(lv_emitSignal)) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "potion_emptied", 14u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_obj(this)}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitSignal_1501, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_shopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_craft = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_craft = gd::gd_coerce_bool(lv_craft);
    (void)([&]() { gd::GdVal _ca[] = {lv_craft}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_shopEntered_745, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_isFull)))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_fill, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_getAffectedCellsAfterRotate_primary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rotatedCells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_faceDirection, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN))))) {
        return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::gd_add(gd_ctx, gd::get_index(gd_ctx, lv_rotatedCells, gd::GdVal::from_int(1LL)), gd::GdVal::from_vec2(0.0, -1.0))}));
    }
    else {
        return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::gd_add(gd_ctx, gd::get_index(gd_ctx, lv_rotatedCells, gd::GdVal::from_int(0LL)), gd::GdVal::from_vec2(0.0, -1.0))}));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_addToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__inventory = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__occupiedCells = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv__placedByPlayer = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv__placedByPlayer = gd::gd_coerce_bool(lv__placedByPlayer);
    (void)([&]() { gd::GdVal _ca[] = {lv__inventory, lv__occupiedCells, lv__placedByPlayer}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_addToInventory_122, _ca, 3, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateConnector_1756, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetGradient_1757, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_onFusingAsIngredient(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetGradient_1757, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_onAffectedItemAdded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_color, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateConnector_1756, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_onAffectedItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_color, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateConnector_1756, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_updateConnector(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_resetGradient(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_discard(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_discardGems = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    if (gd::gd_truth(this->f_pooled)) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetGradient_1757, nullptr, 0);
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_discardGems}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_discard_764, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_getStarPosition(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Potion(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Potion>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Potion = {CLS_Gd__gd_core_items__Potion, "Potion", "res://gd_core_items/Potion.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Potion, &Gd__gd_core_items__Potion::get_static_prop_fn, &Gd__gd_core_items__Potion::call_static_fn};

void Gd__gd_core__WalrusTusk::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__WalrusTusk::meta() const { return &META_Gd__gd_core__WalrusTusk; }
gd::GdVal Gd__gd_core__WalrusTusk::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__WalrusTusk::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__WalrusTusk::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__WalrusTusk::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__WalrusTusk::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__WalrusTusk::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__WalrusTusk::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__WalrusTusk::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_211, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_383, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__WalrusTusk::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__WalrusTusk(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__WalrusTusk>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__WalrusTusk = {CLS_Gd__gd_core__WalrusTusk, "WalrusTusk", "res://gd_core/WalrusTusk.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__WalrusTusk, &Gd__gd_core__WalrusTusk::get_static_prop_fn, &Gd__gd_core__WalrusTusk::call_static_fn};

void Gd__gd_core_items__Banana::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Food::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Banana::meta() const { return &META_Gd__gd_core_items__Banana; }
gd::GdVal Gd__gd_core_items__Banana::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Banana::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Banana::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__Banana::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Banana::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Banana::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Banana::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Banana::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_320, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Banana::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Banana(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Banana>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Banana = {CLS_Gd__gd_core_items__Banana, "Banana", "res://gd_core_items/Banana.gd", &META_Gd__gd_core_items__Food, true, _alloc_Gd__gd_core_items__Banana, &Gd__gd_core_items__Banana::get_static_prop_fn, &Gd__gd_core_items__Banana::call_static_fn};

void Gd__gd_core_items__ClawsofAttack::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_attackCounter = gd::GdVal::from_int(0LL);
    this->f_lastSpeedBonus = gd::GdVal::from_float(0.0);
    this->f_speedPerSpike = gd::GdVal::null();
    this->f_numHits = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__ClawsofAttack::meta() const { return &META_Gd__gd_core_items__ClawsofAttack; }
gd::GdVal Gd__gd_core_items__ClawsofAttack::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__ClawsofAttack::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__ClawsofAttack::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_attackCounter_1001: out = this->f_attackCounter; return true;
        case SYM_GEN_lastSpeedBonus_1002: out = this->f_lastSpeedBonus; return true;
        case SYM_GEN_speedPerSpike_1003: out = this->f_speedPerSpike; return true;
        case SYM_GEN_numHits_1004: out = this->f_numHits; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__ClawsofAttack::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_attackCounter_1001: this->f_attackCounter = val; return true;
        case SYM_GEN_lastSpeedBonus_1002: this->f_lastSpeedBonus = val; return true;
        case SYM_GEN_speedPerSpike_1003: this->f_speedPerSpike = val; return true;
        case SYM_GEN_numHits_1004: this->f_numHits = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__ClawsofAttack::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onSpikesChanged_944: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__ClawsofAttack::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onSpikesChanged_944: out = fn_onSpikesChanged(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__ClawsofAttack::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__ClawsofAttack::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_spikes_changed", 24u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onSpikesChanged", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ClawsofAttack::fn_onSpikesChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_clawsBonus = gd::gd_min(gd::gd_mul(this->f_speedPerSpike, gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getSpikes_1207, nullptr, 0)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0));
    lv_clawsBonus = gd::gd_div(gd_ctx, lv_clawsBonus, gd::GdVal::from_float(100.0));
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_sub(lv_clawsBonus, this->f_lastSpeedBonus)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    this->f_lastSpeedBonus = lv_clawsBonus;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ClawsofAttack::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        this->f_attackCounter = gd::gd_add(gd_ctx, this->f_attackCounter, gd::GdVal::from_int(1LL));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_attackCounter, this->f_numHits)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_219, _ca, 1); })();
            this->f_attackCounter = gd::GdVal::from_int(0LL);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ClawsofAttack::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_lastSpeedBonus = gd::GdVal::from_float(0.0);
    this->f_attackCounter = gd::GdVal::from_int(0LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ClawsofAttack::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_speedPerSpike = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0);
    this->f_numHits = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__ClawsofAttack(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__ClawsofAttack>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__ClawsofAttack = {CLS_Gd__gd_core_items__ClawsofAttack, "ClawsofAttack", "res://gd_core_items/ClawsofAttack.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__ClawsofAttack, &Gd__gd_core_items__ClawsofAttack::get_static_prop_fn, &Gd__gd_core_items__ClawsofAttack::call_static_fn};

void Gd__gd_core_items__DragonEgg::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_hatchParticles = gd::GdVal::null();
    this->f_firePulse = gd::GdVal::null();
    this->f_whelpName = gd::GdVal::null();
    this->f_roundsToHatch = gd::GdVal::null();
    this->f_reflectionStacks = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__DragonEgg::meta() const { return &META_Gd__gd_core_items__DragonEgg; }
gd::GdVal Gd__gd_core_items__DragonEgg::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__DragonEgg::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__DragonEgg::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_hatchParticles_1765: out = this->f_hatchParticles; return true;
        case SYM_GEN_firePulse_1766: out = this->f_firePulse; return true;
        case SYM_GEN_whelpName_1767: out = this->f_whelpName; return true;
        case SYM_GEN_roundsToHatch_1768: out = this->f_roundsToHatch; return true;
        case SYM_GEN_reflectionStacks_1769: out = this->f_reflectionStacks; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__DragonEgg::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_hatchParticles_1765: this->f_hatchParticles = val; return true;
        case SYM_GEN_firePulse_1766: this->f_firePulse = val; return true;
        case SYM_GEN_whelpName_1767: this->f_whelpName = val; return true;
        case SYM_GEN_roundsToHatch_1768: this->f_roundsToHatch = val; return true;
        case SYM_GEN_reflectionStacks_1769: this->f_reflectionStacks = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__DragonEgg::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getData_638: return true;
        case SYM_GEN_setData_639: return true;
        case SYM_GEN_updateEgg_1770: return true;
        case SYM_GEN_isNextToNest_1771: return true;
        case SYM_GEN_readyToTransform_753: return true;
        case SYM_GEN_canHatch_1772: return true;
        case SYM_GEN_shopEntered_745: return true;
        case SYM_GEN_startHatching_1773: return true;
        case SYM_GEN_hatch_1774: return true;
        case SYM_GEN_hatch_deferred_1775: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__DragonEgg::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getData_638: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_639: out = fn_setData(args, argc); return true;
        case SYM_GEN_updateEgg_1770: out = fn_updateEgg(args, argc); return true;
        case SYM_GEN_isNextToNest_1771: out = fn_isNextToNest(args, argc); return true;
        case SYM_GEN_readyToTransform_753: out = fn_readyToTransform(args, argc); return true;
        case SYM_GEN_canHatch_1772: out = fn_canHatch(args, argc); return true;
        case SYM_GEN_shopEntered_745: out = fn_shopEntered(args, argc); return true;
        case SYM_GEN_startHatching_1773: out = fn_startHatching(args, argc); return true;
        case SYM_GEN_hatch_1774: out = fn_hatch(args, argc); return true;
        case SYM_GEN_hatch_deferred_1775: out = fn_hatch_deferred(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__DragonEgg::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_getData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_roundsToHatch;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_setData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_data = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_roundsToHatch = lv_data;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateEgg_1770, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_updateEgg(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canHatch_1772, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.0), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_793, _ca, 2); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_sub(gd::GdVal::from_float(1.0), gd::gd_div(gd_ctx, this->f_roundsToHatch, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0))), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_793, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_isNextToNest(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_placed)) {
        {
            gd::GdVal _t1442 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1512, nullptr, 0));
            gd::GdArr* _t1443 = (_t1442.kind == gd::GdVal::Kind::Arr) ? _t1442.arr : nullptr;
            uint32_t _len__t1444 = _t1443 ? _t1443->len : 0u;
            for (uint32_t _t1444 = 0; _t1444 < _len__t1444; ++_t1444) {
                gd::GdVal lv_item = _t1443->data[_t1444];
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, lv_item, SYM_GEN_getName_236, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Dragon Nest", 11u)))))) {
                    return gd::gd_in(gd::GdVal::from_obj(this), gd::call_method(gd_ctx, lv_item, SYM_GEN_getAffectedItems_422, nullptr, 0));
                }
            }
        }
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_readyToTransform(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canHatch_1772, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_canHatch(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_roundsToHatch, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_roundsToHatch, gd::GdVal::from_int(1LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isNextToNest_1771, nullptr, 0))) : gd::GdVal::from_bool(false)))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_shopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_craft = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_craft = gd::gd_coerce_bool(lv_craft);
    (void)([&]() { gd::GdVal _ca[] = {lv_craft}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_shopEntered_745, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_startHatching(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "hatch", 5u)), gd::gd_sub(Gd__gd_core_items__DragonEgg::get_static_const_or_enum(gd_ctx, SYM_GEN_TRANSFORMATION_DUR_606), gd::GdVal::from_float(0.1))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_callDelayed_1420, _ca, 3); })();
    {
        gd::GdVal _t1445 = gd::gd_iter_seq(gd_ctx.arena, this->f_shadows);
        gd::GdArr* _t1446 = (_t1445.kind == gd::GdVal::Kind::Arr) ? _t1445.arr : nullptr;
        uint32_t _len__t1447 = _t1446 ? _t1446->len : 0u;
        for (uint32_t _t1447 = 0; _t1447 < _len__t1447; ++_t1447) {
            gd::GdVal lv_shadow = _t1446->data[_t1447];
            gd::set_prop(gd_ctx, lv_shadow, SYM_GEN_offset_516, gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(138LL))).as_float()));
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_hatch(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "hatch_deferred", 14u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_defer_1422, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_hatch_deferred(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_roundsToHatch = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateEgg_1770, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__DragonEgg(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__DragonEgg>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__DragonEgg = {CLS_Gd__gd_core_items__DragonEgg, "DragonEgg", "res://gd_core_items/DragonEgg.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__DragonEgg, &Gd__gd_core_items__DragonEgg::get_static_prop_fn, &Gd__gd_core_items__DragonEgg::call_static_fn};

void Gd__gd_core_items__Exclusive__AngelCrystal::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_regen = gd::GdVal::null();
    this->f_regenPerHoly = gd::GdVal::null();
    this->f_empower = gd::GdVal::null();
    this->f_empowerPerHoly = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__AngelCrystal::meta() const { return &META_Gd__gd_core_items__Exclusive__AngelCrystal; }
gd::GdVal Gd__gd_core_items__Exclusive__AngelCrystal::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__AngelCrystal::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__AngelCrystal::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_regen_1904: out = this->f_regen; return true;
        case SYM_GEN_regenPerHoly_1941: out = this->f_regenPerHoly; return true;
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        case SYM_GEN_empowerPerHoly_1942: out = this->f_empowerPerHoly; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__AngelCrystal::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_regen_1904: this->f_regen = val; return true;
        case SYM_GEN_regenPerHoly_1941: this->f_regenPerHoly = val; return true;
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        case SYM_GEN_empowerPerHoly_1942: this->f_empowerPerHoly = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__AngelCrystal::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onRegenChanged_1796: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__AngelCrystal::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onRegenChanged_1796: out = fn_onRegenChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__AngelCrystal::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__AngelCrystal::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Holy_2593)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AngelCrystal::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_regeneration_changed", 30u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onRegenChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AngelCrystal::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_regen, gd::gd_mul(this->f_regenPerHoly, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0)))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AngelCrystal::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_empower, gd::gd_mul(this->f_empowerPerHoly, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0)))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_219, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_147, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AngelCrystal::fn_onRegenChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), lv_amount), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_319, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AngelCrystal::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_regenPerHoly = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen_holy", 10u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_empowerPerHoly = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower_holy", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__AngelCrystal(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__AngelCrystal>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AngelCrystal = {CLS_Gd__gd_core_items__Exclusive__AngelCrystal, "AngelCrystal", "res://gd_core_items/Exclusive/AngelCrystal.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__AngelCrystal, &Gd__gd_core_items__Exclusive__AngelCrystal::get_static_prop_fn, &Gd__gd_core_items__Exclusive__AngelCrystal::call_static_fn};

void Gd__gd_core_items__Exclusive__BagofGiving::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Bag::init_fields(gd_ctx);
    this->f_activationParticles = gd::GdVal::null();
    this->f_maxStamina = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__BagofGiving::meta() const { return &META_Gd__gd_core_items__Exclusive__BagofGiving; }
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Bag::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__BagofGiving::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__BagofGiving::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_maxStamina_1054: out = this->f_maxStamina; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BagofGiving::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_maxStamina_1054: this->f_maxStamina = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BagofGiving::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canApplyEffect_920: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onItemInsideActivated_1958: return true;
        case SYM_GEN_onAddToInventory_421: return true;
        case SYM_GEN_onRemoveFromInventory_420: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_getShopPriority_853: return true;
        case SYM_GEN_getRelatedItems_461: return true;
        case SYM_GEN_getRelatedItemColumns_699: return true;
        case SYM_GEN_getRelatedItemHeight_700: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BagofGiving::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canApplyEffect_920: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemInsideActivated_1958: out = fn_onItemInsideActivated(args, argc); return true;
        case SYM_GEN_onAddToInventory_421: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_420: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_getShopPriority_853: out = fn_getShopPriority(args, argc); return true;
        case SYM_GEN_getRelatedItems_461: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_699: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN_getRelatedItemHeight_700: out = fn_getRelatedItemHeight(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__BagofGiving::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn_canApplyEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_toItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_toItem, SYM_GEN_isClassItem_250, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1448 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_927, nullptr, 0));
        gd::GdArr* _t1449 = (_t1448.kind == gd::GdVal::Kind::Arr) ? _t1448.arr : nullptr;
        uint32_t _len__t1450 = _t1449 ? _t1449->len : 0u;
        for (uint32_t _t1450 = 0; _t1450 < _len__t1450; ++_t1450) {
            gd::GdVal lv_item = _t1449->data[_t1450];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "activated", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onItemInsideActivated", 21u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn_onItemInsideActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_maxStamina, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxStaminaTemporary_318, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn_onAddToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN_onRemoveFromInventory_420, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn_getShopPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_856), SYM_GEN_Low_2718);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn_getRelatedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn_getRelatedItemColumns(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(6LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn_getRelatedItemHeight(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(110LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_maxStamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__BagofGiving(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__BagofGiving>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BagofGiving = {CLS_Gd__gd_core_items__Exclusive__BagofGiving, "BagofGiving", "res://gd_core_items/Exclusive/BagofGiving.gd", &META_Gd__gd_core_items__Bag, true, _alloc_Gd__gd_core_items__Exclusive__BagofGiving, &Gd__gd_core_items__Exclusive__BagofGiving::get_static_prop_fn, &Gd__gd_core_items__Exclusive__BagofGiving::call_static_fn};

void Gd__gd_core_items__Exclusive__BookofLight::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_manaNeeded = gd::GdVal::null();
    this->f_regen = gd::GdVal::null();
    this->f_spellSpeed = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__BookofLight::meta() const { return &META_Gd__gd_core_items__Exclusive__BookofLight; }
gd::GdVal Gd__gd_core_items__Exclusive__BookofLight::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__BookofLight::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__BookofLight::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_manaNeeded_1786: out = this->f_manaNeeded; return true;
        case SYM_GEN_regen_1904: out = this->f_regen; return true;
        case SYM_GEN_spellSpeed_1999: out = this->f_spellSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BookofLight::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaNeeded_1786: this->f_manaNeeded = val; return true;
        case SYM_GEN_regen_1904: this->f_regen = val; return true;
        case SYM_GEN_spellSpeed_1999: this->f_spellSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BookofLight::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BookofLight::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__BookofLight::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofLight::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Spell_2607)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofLight::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_speed = gd::GdVal::from_float(0.0);
    {
        gd::GdVal _t1451 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1452 = (_t1451.kind == gd::GdVal::Kind::Arr) ? _t1451.arr : nullptr;
        uint32_t _len__t1453 = _t1452 ? _t1452->len : 0u;
        for (uint32_t _t1453 = 0; _t1453 < _len__t1453; ++_t1453) {
            gd::GdVal lv_item = _t1452->data[_t1453];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Holy_2593)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())) {
                lv_speed = gd::gd_add(gd_ctx, lv_speed, gd::gd_mul(this->f_spellSpeed, gd::GdVal::from_int(2LL)));
            }
            else {
                lv_speed = gd::gd_add(gd_ctx, lv_speed, this->f_spellSpeed);
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_speed}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofLight::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getMana_1228, nullptr, 0), this->f_manaNeeded)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_334, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_regen, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, _ca, 2); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofLight::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_manaNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_spellSpeed = gd::gd_div(gd_ctx, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })()), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__BookofLight(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__BookofLight>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BookofLight = {CLS_Gd__gd_core_items__Exclusive__BookofLight, "BookofLight", "res://gd_core_items/Exclusive/BookofLight.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__BookofLight, &Gd__gd_core_items__Exclusive__BookofLight::get_static_prop_fn, &Gd__gd_core_items__Exclusive__BookofLight::call_static_fn};

void Gd__gd_core_items__Exclusive__CatSpirit::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__SpiritCompanion::init_fields(gd_ctx);
    this->f_manaNeeded = gd::GdVal::null();
    this->f_luck = gd::GdVal::null();
    this->f_empower = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__CatSpirit::meta() const { return &META_Gd__gd_core_items__Exclusive__CatSpirit; }
gd::GdVal Gd__gd_core_items__Exclusive__CatSpirit::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__SpiritCompanion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__CatSpirit::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__CatSpirit::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_manaNeeded_1786: out = this->f_manaNeeded; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__SpiritCompanion::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__CatSpirit::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaNeeded_1786: this->f_manaNeeded = val; return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__SpiritCompanion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__CatSpirit::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN_playDropSound_151: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__SpiritCompanion::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__CatSpirit::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_151: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__SpiritCompanion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__CatSpirit::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__SpiritCompanion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__CatSpirit::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canDamage_91, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CatSpirit::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1454 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1455 = (_t1454.kind == gd::GdVal::Kind::Arr) ? _t1454.arr : nullptr;
        uint32_t _len__t1456 = _t1455 ? _t1455->len : 0u;
        for (uint32_t _t1456 = 0; _t1456 < _len__t1456; ++_t1456) {
            gd::GdVal lv_item = _t1455->data[_t1456];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addCritChancePercent_181, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CatSpirit::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getMana_1228, nullptr, 0), this->f_manaNeeded)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_334, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_luck, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_empower, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_219, _ca, 2); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CatSpirit::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CatSpirit::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CatSpirit::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__SpiritCompanion::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_manaNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "manat", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__CatSpirit(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__CatSpirit>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__CatSpirit = {CLS_Gd__gd_core_items__Exclusive__CatSpirit, "CatSpirit", "res://gd_core_items/Exclusive/CatSpirit.gd", &META_Gd__gd_core_items__Exclusive__SpiritCompanion, true, _alloc_Gd__gd_core_items__Exclusive__CatSpirit, &Gd__gd_core_items__Exclusive__CatSpirit::get_static_prop_fn, &Gd__gd_core_items__Exclusive__CatSpirit::call_static_fn};

void Gd__gd_core_items__Exclusive__Chess__WhiteKnight::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__Chess__ChessPiece::init_fields(gd_ctx);
    this->f_boardSpeed = gd::GdVal::null();
    this->f_stamina = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Chess__WhiteKnight::meta() const { return &META_Gd__gd_core_items__Exclusive__Chess__WhiteKnight; }
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteKnight::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteKnight::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteKnight::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_boardSpeed_2063: out = this->f_boardSpeed; return true;
        case SYM_GEN_stamina_2060: out = this->f_stamina; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteKnight::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_boardSpeed_2063: this->f_boardSpeed = val; return true;
        case SYM_GEN_stamina_2060: this->f_stamina = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteKnight::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2050: return true;
        case SYM_GEN_doEliminatedEffect_2052: return true;
        case SYM_GEN_canBeBlocked_1467: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteKnight::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2050: out = fn_doCapturingEffect(args, argc); return true;
        case SYM_GEN_doEliminatedEffect_2052: out = fn_doEliminatedEffect(args, argc); return true;
        case SYM_GEN_canBeBlocked_1467: out = fn_canBeBlocked(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteKnight::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteKnight::fn_doCapturingEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__eliminatedPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_boardSpeed}; return gd::call_method(gd_ctx, this->f_board, SYM_GEN_addSpeed_275, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteKnight::fn_doEliminatedEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__capturingPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_stamina}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxStaminaTemporary_318, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteKnight::fn_canBeBlocked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteKnight::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_boardSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_stamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Chess__WhiteKnight(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Chess__WhiteKnight>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Chess__WhiteKnight = {CLS_Gd__gd_core_items__Exclusive__Chess__WhiteKnight, "WhiteKnight", "res://gd_core_items/Exclusive/Chess/WhiteKnight.gd", &META_Gd__gd_core_items__Exclusive__Chess__ChessPiece, true, _alloc_Gd__gd_core_items__Exclusive__Chess__WhiteKnight, &Gd__gd_core_items__Exclusive__Chess__WhiteKnight::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Chess__WhiteKnight::call_static_fn};

void Gd__gd_core_items__Exclusive__Cubert::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_goobertAnimation = gd::GdVal::null();
    this->f_regen = gd::GdVal::null();
    this->f_regenNeeded = gd::GdVal::null();
    this->f_empower = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Cubert::meta() const { return &META_Gd__gd_core_items__Exclusive__Cubert; }
gd::GdVal Gd__gd_core_items__Exclusive__Cubert::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Cubert::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Cubert::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_goobertAnimation_936: out = this->f_goobertAnimation; return true;
        case SYM_GEN_regen_1904: out = this->f_regen; return true;
        case SYM_GEN_regenNeeded_942: out = this->f_regenNeeded; return true;
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Cubert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_goobertAnimation_936: this->f_goobertAnimation = val; return true;
        case SYM_GEN_regen_1904: this->f_regen = val; return true;
        case SYM_GEN_regenNeeded_942: this->f_regenNeeded = val; return true;
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Cubert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_canAffect_secondary_289: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onItemActivated1_2089: return true;
        case SYM_GEN_onItemActivated2_2090: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Cubert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_289: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemActivated1_2089: out = fn_onItemActivated1(args, argc); return true;
        case SYM_GEN_onItemActivated2_2090: out = fn_onItemActivated2(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Cubert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Cubert::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canActivate_93, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cubert::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canActivate_93, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cubert::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1457 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1458 = (_t1457.kind == gd::GdVal::Kind::Arr) ? _t1457.arr : nullptr;
        uint32_t _len__t1459 = _t1458 ? _t1458->len : 0u;
        for (uint32_t _t1459 = 0; _t1459 < _len__t1459; ++_t1459) {
            gd::GdVal lv_item = _t1458->data[_t1459];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "activated", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onItemActivated1", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
        }
    }
    {
        gd::GdVal _t1460 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Secondary_2583)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, _ca, 1); })());
        gd::GdArr* _t1461 = (_t1460.kind == gd::GdVal::Kind::Arr) ? _t1460.arr : nullptr;
        uint32_t _len__t1462 = _t1461 ? _t1461->len : 0u;
        for (uint32_t _t1462 = 0; _t1462 < _len__t1462; ++_t1462) {
            gd::GdVal lv_item = _t1461->data[_t1462];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "activated", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onItemActivated2", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cubert::fn_onItemActivated1(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_regen, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cubert::fn_onItemActivated2(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getRegeneration_1217, nullptr, 0), this->f_regenNeeded)))) {
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance2_176, nullptr, 0))) {
            gd::GdVal lv_event2 = ([&]() { gd::GdVal _ca[] = {this->f_regenNeeded, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_348, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_empower, lv_event2}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_219, _ca, 2); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cubert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getRegeneration_1217, nullptr, 0), this->f_regenNeeded)))) {
        gd::GdVal lv_event2 = ([&]() { gd::GdVal _ca[] = {this->f_regenNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_348, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_empower, lv_event2}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_219, _ca, 2); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cubert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_regenNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regent", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Cubert(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Cubert>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Cubert = {CLS_Gd__gd_core_items__Exclusive__Cubert, "Cubert", "res://gd_core_items/Exclusive/Cubert.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Cubert, &Gd__gd_core_items__Exclusive__Cubert::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Cubert::call_static_fn};

void Gd__gd_core_items__Exclusive__DraconicOrb::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_counter = gd::GdVal::from_int(0LL);
    this->f_activationParticles = gd::GdVal::null();
    this->f_heatThreshold = gd::GdVal::from_int(0);
    this->f_spikeRemoval = gd::GdVal::from_int(0);
    this->f_heatPerSpike = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__DraconicOrb::meta() const { return &META_Gd__gd_core_items__Exclusive__DraconicOrb; }
gd::GdVal Gd__gd_core_items__Exclusive__DraconicOrb::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__DraconicOrb::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__DraconicOrb::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_counter_2115: out = this->f_counter; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_heatThreshold_1880: out = this->f_heatThreshold; return true;
        case SYM_GEN_spikeRemoval_2116: out = this->f_spikeRemoval; return true;
        case SYM_GEN_heatPerSpike_2117: out = this->f_heatPerSpike; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DraconicOrb::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_counter_2115: this->f_counter = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_heatThreshold_1880: this->f_heatThreshold = gd::gd_coerce_int(val); return true;
        case SYM_GEN_spikeRemoval_2116: this->f_spikeRemoval = gd::gd_coerce_int(val); return true;
        case SYM_GEN_heatPerSpike_2117: this->f_heatPerSpike = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DraconicOrb::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onHeatChanged_913: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DraconicOrb::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onHeatChanged_913: out = fn_onHeatChanged(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__DraconicOrb::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__DraconicOrb::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_counter = gd::GdVal::from_int(0LL);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_heat_changed", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onHeatChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DraconicOrb::fn_onHeatChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_counter, this->f_heatThreshold)))) {
        this->f_counter = gd::gd_add(gd_ctx, this->f_counter, lv_amount);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_counter, this->f_heatThreshold)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveCritTokens_316, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DraconicOrb::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_oppoSpikes = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_getSpikes_1207, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_oppoSpikes, gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_spikeRemoval, gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_loseSpikes_340, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::gd_min(lv_oppoSpikes, this->f_spikeRemoval), this->f_heatPerSpike), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 2); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DraconicOrb::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_heatThreshold = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0));
    this->f_spikeRemoval = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0));
    this->f_heatPerSpike = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__DraconicOrb(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__DraconicOrb>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DraconicOrb = {CLS_Gd__gd_core_items__Exclusive__DraconicOrb, "DraconicOrb", "res://gd_core_items/Exclusive/DraconicOrb.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__DraconicOrb, &Gd__gd_core_items__Exclusive__DraconicOrb::get_static_prop_fn, &Gd__gd_core_items__Exclusive__DraconicOrb::call_static_fn};

void Gd__gd_core_items__Exclusive__EmployeeUniform::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__LeatherArmor::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__EmployeeUniform::meta() const { return &META_Gd__gd_core_items__Exclusive__EmployeeUniform; }
gd::GdVal Gd__gd_core_items__Exclusive__EmployeeUniform::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__LeatherArmor::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__EmployeeUniform::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__EmployeeUniform::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__LeatherArmor::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__EmployeeUniform::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__LeatherArmor::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__EmployeeUniform::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCalcTradeChance_1730: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherArmor::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__EmployeeUniform::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCalcTradeChance_1730: out = fn_onCalcTradeChance(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherArmor::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__EmployeeUniform::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__LeatherArmor::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__EmployeeUniform::fn_onCalcTradeChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EmployeeUniform::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherArmor::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__EmployeeUniform(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__EmployeeUniform>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__EmployeeUniform = {CLS_Gd__gd_core_items__Exclusive__EmployeeUniform, "EmployeeUniform", "res://gd_core_items/Exclusive/EmployeeUniform.gd", &META_Gd__gd_core_items__LeatherArmor, true, _alloc_Gd__gd_core_items__Exclusive__EmployeeUniform, &Gd__gd_core_items__Exclusive__EmployeeUniform::get_static_prop_fn, &Gd__gd_core_items__Exclusive__EmployeeUniform::call_static_fn};

void Gd__gd_core_items__Exclusive__FlameWhip::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_spikesNeeded = gd::GdVal::from_int(0);
    this->f_heatGain = gd::GdVal::from_int(0);
    this->f_bonusDamage = gd::GdVal::from_float(0.0);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__FlameWhip::meta() const { return &META_Gd__gd_core_items__Exclusive__FlameWhip; }
gd::GdVal Gd__gd_core_items__Exclusive__FlameWhip::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__FlameWhip::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__FlameWhip::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_spikesNeeded_2015: out = this->f_spikesNeeded; return true;
        case SYM_GEN_heatGain_2166: out = this->f_heatGain; return true;
        case SYM_GEN_bonusDamage_904: out = this->f_bonusDamage; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__FlameWhip::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_spikesNeeded_2015: this->f_spikesNeeded = gd::gd_coerce_int(val); return true;
        case SYM_GEN_heatGain_2166: this->f_heatGain = gd::gd_coerce_int(val); return true;
        case SYM_GEN_bonusDamage_904: this->f_bonusDamage = gd::gd_coerce_float(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__FlameWhip::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__FlameWhip::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__FlameWhip::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__FlameWhip::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getSpikes_1207, nullptr, 0), this->f_spikesNeeded)))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_spikesNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useSpikes_339, _ca, 1); })();
            gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427), this->f_bonusDamage));
            (void)([&]() { gd::GdVal _ca[] = {this->f_heatGain}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FlameWhip::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_spikesNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_heatGain = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_bonusDamage = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "bonusdam", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__FlameWhip(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__FlameWhip>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__FlameWhip = {CLS_Gd__gd_core_items__Exclusive__FlameWhip, "FlameWhip", "res://gd_core_items/Exclusive/FlameWhip.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__FlameWhip, &Gd__gd_core_items__Exclusive__FlameWhip::get_static_prop_fn, &Gd__gd_core_items__Exclusive__FlameWhip::call_static_fn};

void Gd__gd_core_items__Exclusive__Gigawatz::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_numSpeedboosts = gd::GdVal::from_int(0);
    this->f_curDamageBonus = gd::GdVal::from_int(0);
    this->f_maxNumSpeedBoosts = gd::GdVal::null();
    this->f_speedBonus = gd::GdVal::null();
    this->f_damageBonus = gd::GdVal::null();
    this->f_blind = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Gigawatz::meta() const { return &META_Gd__gd_core_items__Exclusive__Gigawatz; }
gd::GdVal Gd__gd_core_items__Exclusive__Gigawatz::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Gigawatz::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Gigawatz::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_numSpeedboosts_2194: out = this->f_numSpeedboosts; return true;
        case SYM_GEN_curDamageBonus_2195: out = this->f_curDamageBonus; return true;
        case SYM_GEN_maxNumSpeedBoosts_2196: out = this->f_maxNumSpeedBoosts; return true;
        case SYM_GEN_speedBonus_1782: out = this->f_speedBonus; return true;
        case SYM_GEN_damageBonus_2197: out = this->f_damageBonus; return true;
        case SYM_GEN_blind_1816: out = this->f_blind; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Gigawatz::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numSpeedboosts_2194: this->f_numSpeedboosts = gd::gd_coerce_int(val); return true;
        case SYM_GEN_curDamageBonus_2195: this->f_curDamageBonus = gd::gd_coerce_int(val); return true;
        case SYM_GEN_maxNumSpeedBoosts_2196: this->f_maxNumSpeedBoosts = val; return true;
        case SYM_GEN_speedBonus_1782: this->f_speedBonus = val; return true;
        case SYM_GEN_damageBonus_2197: this->f_damageBonus = val; return true;
        case SYM_GEN_blind_1816: this->f_blind = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Gigawatz::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onChargeReceived_2035: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Gigawatz::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onChargeReceived_2035: out = fn_onChargeReceived(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Gigawatz::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Gigawatz::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_curDamageBonus = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_numSpeedboosts = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Gigawatz::fn_onChargeReceived(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_numSpeedboosts, this->f_maxNumSpeedBoosts)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_speedBonus}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
        this->f_numSpeedboosts = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_numSpeedboosts, gd::GdVal::from_int(1LL)));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Gigawatz::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_blind}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_215, _ca, 1); })();
    gd::GdVal lv_dam = gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_minDam_1579), this->f_curDamageBonus);
    gd::GdVal lv_res = ([&]() { gd::GdVal _ca[] = {lv_dam}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealEffectDamage_223, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    this->f_curDamageBonus = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_curDamageBonus, this->f_damageBonus));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Gigawatz::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_maxNumSpeedBoosts = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "max", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_speedBonus = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_damageBonus = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "damincrease", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_blind = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blind", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1459, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Gigawatz(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Gigawatz>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Gigawatz = {CLS_Gd__gd_core_items__Exclusive__Gigawatz, "Gigawatz", "res://gd_core_items/Exclusive/Gigawatz.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Gigawatz, &Gd__gd_core_items__Exclusive__Gigawatz::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Gigawatz::call_static_fn};

void Gd__gd_core_items__Exclusive__HyperHedgehog::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__Hedgehog::init_fields(gd_ctx);
    this->f_damagePerEmpower = gd::GdVal::null();
    this->f_empower = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__HyperHedgehog::meta() const { return &META_Gd__gd_core_items__Exclusive__HyperHedgehog; }
gd::GdVal Gd__gd_core_items__Exclusive__HyperHedgehog::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__Hedgehog::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__HyperHedgehog::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__HyperHedgehog::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_damagePerEmpower_2217: out = this->f_damagePerEmpower; return true;
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Hedgehog::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__HyperHedgehog::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damagePerEmpower_2217: this->f_damagePerEmpower = val; return true;
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Hedgehog::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__HyperHedgehog::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onHPLow_2210: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN_playDropSound_151: return true;
        case SYM_GEN_spawnSpikeParticles_2211: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Hedgehog::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__HyperHedgehog::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onHPLow_2210: out = fn_onHPLow(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_151: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN_spawnSpikeParticles_2211: out = fn_spawnSpikeParticles(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Hedgehog::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__HyperHedgehog::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__Hedgehog::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__HyperHedgehog::fn_onHPLow(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_event}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Hedgehog::call_method(gd_ctx, SYM_GEN_onHPLow_2210, _ca, 1, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_empower, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_219, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HyperHedgehog::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_dam = gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_minDam_1579);
    lv_dam = gd::gd_add(gd_ctx, lv_dam, gd::gd_mul(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getSpikes_1207, nullptr, 0), this->f_damagePerSpike));
    lv_dam = gd::gd_add(gd_ctx, lv_dam, gd::gd_mul(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getEmpower_1232, nullptr, 0), this->f_damagePerEmpower));
    gd::GdVal lv_res = ([&]() { gd::GdVal _ca[] = {lv_dam}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealEffectDamage_223, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HyperHedgehog::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HyperHedgehog::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HyperHedgehog::fn_spawnSpikeParticles(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HyperHedgehog::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Hedgehog::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_damagePerEmpower = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam_empower", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__HyperHedgehog(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__HyperHedgehog>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__HyperHedgehog = {CLS_Gd__gd_core_items__Exclusive__HyperHedgehog, "HyperHedgehog", "res://gd_core_items/Exclusive/HyperHedgehog.gd", &META_Gd__gd_core_items__Exclusive__Hedgehog, true, _alloc_Gd__gd_core_items__Exclusive__HyperHedgehog, &Gd__gd_core_items__Exclusive__HyperHedgehog::get_static_prop_fn, &Gd__gd_core_items__Exclusive__HyperHedgehog::call_static_fn};

void Gd__gd_core_items__Exclusive__Laboratory::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_phase = gd::GdVal::from_int(0);
    this->f_typesDict = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_fluidTween = gd::GdVal::null();
    this->f_fluid = gd::GdVal::null();
    this->f_fluidMat = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Laboratory::meta() const { return &META_Gd__gd_core_items__Exclusive__Laboratory; }
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_params_1479: return ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 15); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luckt", 5u)), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heatt", 5u)), gd::GdVal::from_int(4LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat_bonus", 10u)), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat", 4u)), gd::GdVal::from_int(4LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikest", 7u)), gd::GdVal::from_int(6LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes_bonus", 12u)), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u)), gd::GdVal::from_int(8LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regent", 6u)), gd::GdVal::from_int(8LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen_bonus", 11u)), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u)), gd::GdVal::from_int(10LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "vampirism", 9u)), gd::GdVal::from_int(12LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "vamp_bonus", 10u)), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "vampt", 5u)), gd::GdVal::from_int(10LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower_bonus", 13u)), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u)), gd::GdVal::from_int(14LL)); return gd::GdVal::from_dict(d); })();
        case SYM_GEN_flashColor_2245: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.3), gd::GdVal::from_float(1.3), gd::GdVal::from_float(1.3)}; return gd::make_color_from_args(_ca, 3); })();
        case SYM_GEN_DUR_2246: return gd::GdVal::from_float(0.2);
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Laboratory::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Laboratory::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_phase_2213: out = this->f_phase; return true;
        case SYM_GEN_typesDict_1973: out = this->f_typesDict; return true;
        case SYM_GEN_fluidTween_1744: out = this->f_fluidTween; return true;
        case SYM_GEN_fluid_1746: out = this->f_fluid; return true;
        case SYM_GEN_fluidMat_2247: out = this->f_fluidMat; return true;
        case SYM_GEN_params_1479: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_flashColor_2245: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_DUR_2246: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Laboratory::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_phase_2213: this->f_phase = gd::gd_coerce_int(val); return true;
        case SYM_GEN_typesDict_1973: this->f_typesDict = val; return true;
        case SYM_GEN_fluidTween_1744: this->f_fluidTween = val; return true;
        case SYM_GEN_fluid_1746: this->f_fluid = val; return true;
        case SYM_GEN_fluidMat_2247: this->f_fluidMat = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Laboratory::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN_onPreCombatStart_127: return true;
        case SYM_GEN_trigger_145: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN_switchGradient_2248: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Laboratory::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_onPreCombatStart_127: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_trigger_145: out = fn_trigger(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_switchGradient_2248: out = fn_switchGradient(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Laboratory::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_int(1LL))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getDescription_642, nullptr, 0);
    {
        gd::GdVal _t1463 = gd::gd_iter_seq(gd_ctx.arena, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1479));
        gd::GdArr* _t1464 = (_t1463.kind == gd::GdVal::Kind::Arr) ? _t1463.arr : nullptr;
        uint32_t _len__t1465 = _t1464 ? _t1464->len : 0u;
        for (uint32_t _t1465 = 0; _t1465 < _len__t1465; ++_t1465) {
            gd::GdVal lv_param = _t1464->data[_t1465];
            lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "p_", 2u)), lv_param}; return gd::gd_str_fn(gd_ctx.arena, _ca, 2); })(), gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1479), lv_param), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_864), SYM_GEN_No_2548), gd::GdVal::from_bool(false), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 6); })();
        }
    }
    return ([&]() { gd::GdVal _ca[] = {lv_descr, lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameters_643, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    this->f_typesDict = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countTypes_497, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::fn_trigger(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_phase, gd::GdVal::from_int(1LL))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_trigger_145, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth((gd::gd_truth((gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Fire_2601)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Nature_2597)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Holy_2593)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Vampiric_2598)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Classes_Full_1373), SYM_GEN_Engineer_2684)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isClassItem_250, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_phase, gd::GdVal::from_int(1LL))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getLucky_1221, nullptr, 0), gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1479), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luckt", 5u))))))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1479), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luckt", 5u)))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useLucky_352, _ca, 1); })();
            gd::GdVal lv_numFire = gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Fire_2601));
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1479), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat", 4u))), gd::gd_mul(lv_numFire, gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1479), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat_bonus", 10u))))), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 2); })();
        }
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_phase, gd::GdVal::from_int(2LL))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getHeat_1235, nullptr, 0), gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1479), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heatt", 5u))))))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1479), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heatt", 5u)))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useHeat_356, _ca, 1); })();
            gd::GdVal lv_numNature = gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Nature_2597));
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1479), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u))), gd::gd_mul(lv_numNature, gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1479), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes_bonus", 12u))))), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_211, _ca, 2); })();
        }
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_phase, gd::GdVal::from_int(3LL))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getSpikes_1207, nullptr, 0), gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1479), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikest", 7u))))))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1479), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikest", 7u)))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useSpikes_339, _ca, 1); })();
            gd::GdVal lv_numHoly = gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Holy_2593));
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1479), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))), gd::gd_mul(lv_numHoly, gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1479), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen_bonus", 11u))))), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 2); })();
        }
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_phase, gd::GdVal::from_int(4LL))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getRegeneration_1217, nullptr, 0), gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1479), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regent", 6u))))))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1479), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regent", 6u)))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_348, _ca, 1); })();
            gd::GdVal lv_numVamp = gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Vampiric_2598));
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1479), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "vampirism", 9u))), gd::gd_mul(lv_numVamp, gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1479), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "vamp_bonus", 10u))))), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_212, _ca, 2); })();
        }
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_phase, gd::GdVal::from_int(5LL))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getVampirism_1210, nullptr, 0), gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1479), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "vampt", 5u))))))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1479), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "vampt", 5u)))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useVampirism_342, _ca, 1); })();
            gd::GdVal lv_numEngineer = gd::GdVal::from_int(0LL);
            {
                gd::GdVal _t1466 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
                gd::GdArr* _t1467 = (_t1466.kind == gd::GdVal::Kind::Arr) ? _t1466.arr : nullptr;
                uint32_t _len__t1468 = _t1467 ? _t1467->len : 0u;
                for (uint32_t _t1468 = 0; _t1468 < _len__t1468; ++_t1468) {
                    gd::GdVal lv_item = _t1467->data[_t1468];
                    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Classes_Full_1373), SYM_GEN_Engineer_2684)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isClassItem_250, _ca, 1); })())) {
                        lv_numEngineer = gd::gd_add(gd_ctx, lv_numEngineer, gd::GdVal::from_int(1LL));
                    }
                }
            }
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1479), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))), gd::gd_mul(lv_numEngineer, gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1479), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower_bonus", 13u))))), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_219, _ca, 2); })();
        }
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_phase, gd::GdVal::from_int(5LL))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_147, nullptr, 0);
    }
    else {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__phase = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv__phase = gd::gd_coerce_int(lv__phase);
    this->f_phase = gd::gd_coerce_int(lv__phase);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(this->f_phase, gd::GdVal::from_int(0LL))))) {
        this->f_baseCooldownOverride = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldownIndex_103, _ca, 1); })());
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_phase, gd::GdVal::from_int(5LL))))) {
        this->f_baseCooldownOverride = gd::gd_coerce_float(gd::gd_sub(([&]() { gd::GdVal _ca[] = {this->f_phase}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldownIndex_103, _ca, 1); })(), ([&]() { gd::GdVal _ca[] = {gd::gd_sub(this->f_phase, gd::GdVal::from_int(1LL))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldownIndex_103, _ca, 1); })()));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::fn_switchGradient(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_phase = gd::gd_coerce_int(gd::gd_neg(gd::GdVal::from_int(1LL)));
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_switchGradient_2248, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Laboratory(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Laboratory>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Laboratory = {CLS_Gd__gd_core_items__Exclusive__Laboratory, "Laboratory", "res://gd_core_items/Exclusive/Laboratory.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Laboratory, &Gd__gd_core_items__Exclusive__Laboratory::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Laboratory::call_static_fn};

void Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_triggerType = gd::GdVal::from_int(0);
    this->f_stackType = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::meta() const { return &META_Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect; }
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return gd::GdVal::null();
}
bool Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_triggerType_2292: out = this->f_triggerType; return true;
        case SYM_GEN_stackType_2293: out = this->f_stackType; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_triggerType_2292: this->f_triggerType = gd::gd_coerce_int(val); return true;
        case SYM_GEN_stackType_2293: this->f_stackType = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_pushEncoded_2294: return true;
        case SYM_GEN_setFromEncoded_2295: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_pushEncoded_2294: out = fn_pushEncoded(args, argc); return true;
        case SYM_GEN_setFromEncoded_2295: out = fn_setFromEncoded(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return false;
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::fn_pushEncoded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_bitStream = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_normalizedStack = gd::gd_sub(this->f_stackType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Lucky_2570));
    (void)([&]() { gd::GdVal _ca[] = {this->f_triggerType, gd::call_method(gd_ctx, Gd__gd_core_items__Exclusive__MagicRing::get_static_const_or_enum(gd_ctx, SYM_GEN_TriggerType_2290), gd::SYM_size, nullptr, 0)}; return gd::call_method(gd_ctx, lv_bitStream, SYM_GEN_push_2776, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_normalizedStack, gd::GdVal::from_int(16LL)}; return gd::call_method(gd_ctx, lv_bitStream, SYM_GEN_push_2776, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::fn_setFromEncoded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_bitStream = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_triggerType = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, Gd__gd_core_items__Exclusive__MagicRing::get_static_const_or_enum(gd_ctx, SYM_GEN_TriggerType_2290), gd::SYM_size, nullptr, 0)}; return gd::call_method(gd_ctx, lv_bitStream, SYM_GEN_pull_2777, _ca, 1); })());
    this->f_stackType = gd::gd_coerce_int(gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(16LL)}; return gd::call_method(gd_ctx, lv_bitStream, SYM_GEN_pull_2777, _ca, 1); })(), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Lucky_2570)));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect = {CLS_Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect, "RingEffect", "", nullptr, true, _alloc_Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect, &Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::get_static_prop_fn, &Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::call_static_fn};

void Gd__gd_core_items__Exclusive__MrsStruggles::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_activationParticles = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__MrsStruggles::meta() const { return &META_Gd__gd_core_items__Exclusive__MrsStruggles; }
gd::GdVal Gd__gd_core_items__Exclusive__MrsStruggles::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__MrsStruggles::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__MrsStruggles::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MrsStruggles::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MrsStruggles::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MrsStruggles::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__MrsStruggles::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__MrsStruggles::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Dark_2602)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MrsStruggles::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MrsStruggles::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1469 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0));
        gd::GdArr* _t1470 = (_t1469.kind == gd::GdVal::Kind::Arr) ? _t1469.arr : nullptr;
        uint32_t _len__t1471 = _t1470 ? _t1470->len : 0u;
        for (uint32_t _t1471 = 0; _t1471 < _len__t1471; ++_t1471) {
            gd::GdVal lv_buff = _t1470->data[_t1471];
            (void)([&]() { gd::GdVal _ca[] = {lv_buff, gd::GdVal::from_int(1LL), gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_loseStacks_1031, _ca, 3); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MrsStruggles::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__MrsStruggles(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__MrsStruggles>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MrsStruggles = {CLS_Gd__gd_core_items__Exclusive__MrsStruggles, "MrsStruggles", "res://gd_core_items/Exclusive/MrsStruggles.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__MrsStruggles, &Gd__gd_core_items__Exclusive__MrsStruggles::get_static_prop_fn, &Gd__gd_core_items__Exclusive__MrsStruggles::call_static_fn};

void Gd__gd_core_items__Exclusive__PlasticCube::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__Cube::init_fields(gd_ctx);
    this->f_spikes = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__PlasticCube::meta() const { return &META_Gd__gd_core_items__Exclusive__PlasticCube; }
gd::GdVal Gd__gd_core_items__Exclusive__PlasticCube::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__Cube::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__PlasticCube::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__PlasticCube::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_spikes_898: out = this->f_spikes; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Cube::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PlasticCube::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_spikes_898: this->f_spikes = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Cube::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PlasticCube::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Cube::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PlasticCube::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Cube::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__PlasticCube::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__Cube::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__PlasticCube::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_97, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PlasticCube::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_deactivateCooldown_101, nullptr, 0);
    gd::GdVal lv_affectedItem = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getFirstAffectedItem_430, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_affectedItem, gd::GdVal::null())))) {
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_affectedItem, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_cube_advanced_1398)))))) {
            { gd::GdVal _t1472 = gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_cube_advanced_1398); gd::GdVal _t1473 = lv_affectedItem; gd::set_index(gd_ctx, _t1472, _t1473, gd::GdVal::from_obj(this)); }
            (void)([&]() { gd::GdVal _ca[] = {this->f_cdAdvance}; return gd::call_method(gd_ctx, lv_affectedItem, SYM_GEN_advanceCooldownPercent_148, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_cdAdvance, this->f_penaltyFactor)}; return gd::call_method(gd_ctx, lv_affectedItem, SYM_GEN_advanceCooldownPercent_148, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {this->f_spikes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_211, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_147, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PlasticCube::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Cube::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PlasticCube(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__PlasticCube>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PlasticCube = {CLS_Gd__gd_core_items__Exclusive__PlasticCube, "PlasticCube", "res://gd_core_items/Exclusive/PlasticCube.gd", &META_Gd__gd_core_items__Exclusive__Cube, true, _alloc_Gd__gd_core_items__Exclusive__PlasticCube, &Gd__gd_core_items__Exclusive__PlasticCube::get_static_prop_fn, &Gd__gd_core_items__Exclusive__PlasticCube::call_static_fn};

void Gd__gd_core_items__Exclusive__PuzzlebagZ::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Bag::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__PuzzlebagZ::meta() const { return &META_Gd__gd_core_items__Exclusive__PuzzlebagZ; }
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagZ::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Bag::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagZ::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__PuzzlebagZ::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagZ::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagZ::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canApplyEffect_920: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagZ::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canApplyEffect_920: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagZ::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagZ::fn_canApplyEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_toItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_toItem, SYM_GEN_inflictsDebuffs_300, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagZ::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1474 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_927, nullptr, 0));
        gd::GdArr* _t1475 = (_t1474.kind == gd::GdVal::Kind::Arr) ? _t1474.arr : nullptr;
        uint32_t _len__t1476 = _t1475 ? _t1475->len : 0u;
        for (uint32_t _t1476 = 0; _t1476 < _len__t1476; ++_t1476) {
            gd::GdVal lv_item = _t1475->data[_t1476];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_allDebuffs_200, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagZ::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PuzzlebagZ(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__PuzzlebagZ>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PuzzlebagZ = {CLS_Gd__gd_core_items__Exclusive__PuzzlebagZ, "PuzzlebagZ", "res://gd_core_items/Exclusive/PuzzlebagZ.gd", &META_Gd__gd_core_items__Bag, true, _alloc_Gd__gd_core_items__Exclusive__PuzzlebagZ, &Gd__gd_core_items__Exclusive__PuzzlebagZ::get_static_prop_fn, &Gd__gd_core_items__Exclusive__PuzzlebagZ::call_static_fn};

void Gd__gd_core_items__Exclusive__Resistor::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_heatThreshold = gd::GdVal::null();
    this->f_heat = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Resistor::meta() const { return &META_Gd__gd_core_items__Exclusive__Resistor; }
gd::GdVal Gd__gd_core_items__Exclusive__Resistor::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Resistor::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Resistor::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_heatThreshold_1880: out = this->f_heatThreshold; return true;
        case SYM_GEN_heat_1801: out = this->f_heat; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Resistor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_heatThreshold_1880: this->f_heatThreshold = val; return true;
        case SYM_GEN_heat_1801: this->f_heat = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Resistor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onChargeReceived_2035: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Resistor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onChargeReceived_2035: out = fn_onChargeReceived(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Resistor::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Resistor::fn_onChargeReceived(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getHeat_1235, nullptr, 0), this->f_heatThreshold)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Resistor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_heatThreshold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heatt", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Resistor(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Resistor>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Resistor = {CLS_Gd__gd_core_items__Exclusive__Resistor, "Resistor", "res://gd_core_items/Exclusive/Resistor.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Resistor, &Gd__gd_core_items__Exclusive__Resistor::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Resistor::call_static_fn};

void Gd__gd_core_items__Exclusive__ShepherdsCrook::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ShepherdsCrook::meta() const { return &META_Gd__gd_core_items__Exclusive__ShepherdsCrook; }
gd::GdVal Gd__gd_core_items__Exclusive__ShepherdsCrook::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ShepherdsCrook::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ShepherdsCrook::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ShepherdsCrook::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ShepherdsCrook::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ShepherdsCrook::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ShepherdsCrook::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ShepherdsCrook::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_92, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShepherdsCrook::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeBuffProtectionChance_1270, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Blind_2568), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_174, nullptr, 0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeResistChance_1025, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Cold_2574), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_174, nullptr, 0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeResistChance_1025, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShepherdsCrook::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1477 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1478 = (_t1477.kind == gd::GdVal::Kind::Arr) ? _t1477.arr : nullptr;
        uint32_t _len__t1479 = _t1478 ? _t1478->len : 0u;
        for (uint32_t _t1479 = 0; _t1479 < _len__t1479; ++_t1479) {
            gd::GdVal lv_item = _t1478->data[_t1479];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_163, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShepherdsCrook::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ShepherdsCrook(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ShepherdsCrook>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ShepherdsCrook = {CLS_Gd__gd_core_items__Exclusive__ShepherdsCrook, "ShepherdsCrook", "res://gd_core_items/Exclusive/ShepherdsCrook.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__ShepherdsCrook, &Gd__gd_core_items__Exclusive__ShepherdsCrook::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ShepherdsCrook::call_static_fn};

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
        case SYM_GEN_iceSpeed_2422: out = this->f_iceSpeed; return true;
        case SYM_GEN_cold_1950: out = this->f_cold; return true;
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        case SYM_GEN_coldNeeded_2185: out = this->f_coldNeeded; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Snowmaster::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_iceSpeed_2422: this->f_iceSpeed = val; return true;
        case SYM_GEN_cold_1950: this->f_cold = val; return true;
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        case SYM_GEN_coldNeeded_2185: this->f_coldNeeded = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Snowmaster::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Snowmaster::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Ice_2722)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Snowmaster::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0), this->f_iceSpeed)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Snowmaster::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_getCold_1238, nullptr, 0), this->f_coldNeeded)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_empower}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_219, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {this->f_cold}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_353, _ca, 1); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_358, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Snowmaster::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_iceSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_cold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cold", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_coldNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "coldt", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Snowmaster(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Snowmaster>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Snowmaster = {CLS_Gd__gd_core_items__Exclusive__Snowmaster, "Snowmaster", "res://gd_core_items/Exclusive/Snowmaster.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Snowmaster, &Gd__gd_core_items__Exclusive__Snowmaster::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Snowmaster::call_static_fn};

void Gd__gd_core_items__Exclusive__SquirrelArcher::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__Squirrel::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SquirrelArcher::meta() const { return &META_Gd__gd_core_items__Exclusive__SquirrelArcher; }
gd::GdVal Gd__gd_core_items__Exclusive__SquirrelArcher::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__Squirrel::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SquirrelArcher::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SquirrelArcher::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Exclusive__Squirrel::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SquirrelArcher::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Exclusive__Squirrel::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SquirrelArcher::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Squirrel::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SquirrelArcher::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Squirrel::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SquirrelArcher::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__Squirrel::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SquirrelArcher::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealRandomBuff_375, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SquirrelArcher::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_118, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StaminaResult_1280), SYM_GEN_Sufficient_2605))))) {
        gd::GdVal lv_res = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_222, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SquirrelArcher::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Squirrel::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1459, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SquirrelArcher(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SquirrelArcher>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SquirrelArcher = {CLS_Gd__gd_core_items__Exclusive__SquirrelArcher, "SquirrelArcher", "res://gd_core_items/Exclusive/SquirrelArcher.gd", &META_Gd__gd_core_items__Exclusive__Squirrel, true, _alloc_Gd__gd_core_items__Exclusive__SquirrelArcher, &Gd__gd_core_items__Exclusive__SquirrelArcher::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SquirrelArcher::call_static_fn};

void Gd__gd_core_items__Exclusive__ThornElemental::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_spikesLimit = gd::GdVal::null();
    this->f_spikes = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ThornElemental::meta() const { return &META_Gd__gd_core_items__Exclusive__ThornElemental; }
gd::GdVal Gd__gd_core_items__Exclusive__ThornElemental::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ThornElemental::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ThornElemental::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_spikesLimit_2442: out = this->f_spikesLimit; return true;
        case SYM_GEN_spikes_898: out = this->f_spikes; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ThornElemental::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_spikesLimit_2442: this->f_spikesLimit = val; return true;
        case SYM_GEN_spikes_898: this->f_spikes = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ThornElemental::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ThornElemental::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ThornElemental::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ThornElemental::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Nature_2597)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThornElemental::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_spikesLimit}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeEffectSpikesLimit_1175, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_spikesLimit}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeRangedSpikesLimit_1174, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeSpikesCritChancePercent_1268, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThornElemental::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_spikes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_211, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ThornElemental::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_spikesLimit = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikedam", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ThornElemental(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ThornElemental>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ThornElemental = {CLS_Gd__gd_core_items__Exclusive__ThornElemental, "ThornElemental", "res://gd_core_items/Exclusive/ThornElemental.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__ThornElemental, &Gd__gd_core_items__Exclusive__ThornElemental::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ThornElemental::call_static_fn};

void Gd__gd_core_items__Exclusive__Ultima::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_typesDict = gd::GdVal::null();
    this->f_speedPerSpell = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Ultima::meta() const { return &META_Gd__gd_core_items__Exclusive__Ultima; }
gd::GdVal Gd__gd_core_items__Exclusive__Ultima::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Ultima::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Ultima::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_typesDict_1973: out = this->f_typesDict; return true;
        case SYM_GEN_speedPerSpell_2505: out = this->f_speedPerSpell; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Ultima::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_typesDict_1973: this->f_typesDict = val; return true;
        case SYM_GEN_speedPerSpell_2505: this->f_speedPerSpell = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Ultima::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Ultima::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Ultima::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Ultima::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth((gd::gd_truth((gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Nature_2597)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Ice_2722)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Holy_2593)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Dark_2602)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Spell_2607)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Ultima::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_typesDict = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countTypes_497, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Spell_2607)), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_speedPerSpell, gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Spell_2607)))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Ultima::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Nature_2597)), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Nature_2597)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Nature_2597)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_211, _ca, 1); })();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Ice_2722)), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Ice_2722)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_206, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Ice_2722)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cold", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_353, _ca, 1); })();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Holy_2593)), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Holy_2593)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 1); })();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Dark_2602)), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Dark_2602))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealRandomBuff_375, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_147, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Ultima::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getDescription_642, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_placed)))) {
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$n_nature", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$n_ice", 6u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$n_holy", 7u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$n_dark", 7u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        return lv_descr;
    }
    this->f_typesDict = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countTypes_497, _ca, 1); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "n_nature", 8u)), gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Nature_2597))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_454, _ca, 3); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "n_ice", 5u)), gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Ice_2722))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_454, _ca, 3); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "n_holy", 6u)), gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Holy_2593))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_454, _ca, 3); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "n_dark", 6u)), gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Dark_2602))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_454, _ca, 3); })();
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Ultima::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_speedPerSpell = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Ultima(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Ultima>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Ultima = {CLS_Gd__gd_core_items__Exclusive__Ultima, "Ultima", "res://gd_core_items/Exclusive/Ultima.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Ultima, &Gd__gd_core_items__Exclusive__Ultima::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Ultima::call_static_fn};

void Gd__gd_core_items__FalconBlade::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__FalconBlade::meta() const { return &META_Gd__gd_core_items__FalconBlade; }
gd::GdVal Gd__gd_core_items__FalconBlade::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__FalconBlade::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__FalconBlade::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__FalconBlade::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__FalconBlade::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_getCraftingOffset_850: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__FalconBlade::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getCraftingOffset_850: out = fn_getCraftingOffset(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__FalconBlade::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__FalconBlade::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_97, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__FalconBlade::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1480 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1481 = (_t1480.kind == gd::GdVal::Kind::Arr) ? _t1480.arr : nullptr;
        uint32_t _len__t1482 = _t1481 ? _t1481->len : 0u;
        for (uint32_t _t1482 = 0; _t1482 < _len__t1482; ++_t1482) {
            gd::GdVal lv_item = _t1481->data[_t1482];
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), gd::GdVal::from_int(100LL))}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_275, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__FalconBlade::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_118, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StaminaResult_1280), SYM_GEN_Sufficient_2605))))) {
        gd::GdVal lv_res = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_222, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 2); })();
        gd::GdVal lv_res2 = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_222, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res2, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 2); })();
        gd::GdVal lv_hits = gd::GdVal::from_int(0LL);
        if (gd::gd_truth(gd::call_method(gd_ctx, lv_res, SYM_GEN_hasHit_1432, nullptr, 0))) {
            lv_hits = gd::gd_add(gd_ctx, lv_hits, gd::GdVal::from_int(1LL));
        }
        if (gd::gd_truth(gd::call_method(gd_ctx, lv_res2, SYM_GEN_hasHit_1432, nullptr, 0))) {
            lv_hits = gd::gd_add(gd_ctx, lv_hits, gd::GdVal::from_int(1LL));
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(30.0)), gd::GdVal::from_float(30.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_bare_randf_range_1647, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(100.0)), gd::GdVal::from_float(100.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_bare_randf_range_1647, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(5.0)), gd::GdVal::from_float(5.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_bare_randf_range_1647, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__FalconBlade::fn_getCraftingOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1483 = lv_forDirection;
        if (gd::gd_eq(_t1483, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
        else if (gd::gd_eq(_t1483, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
        else if (gd::gd_eq(_t1483, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_LEFT))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
        else if (gd::gd_eq(_t1483, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_RIGHT))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__FalconBlade::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__FalconBlade(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__FalconBlade>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__FalconBlade = {CLS_Gd__gd_core_items__FalconBlade, "FalconBlade", "res://gd_core_items/FalconBlade.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__FalconBlade, &Gd__gd_core_items__FalconBlade::get_static_prop_fn, &Gd__gd_core_items__FalconBlade::call_static_fn};

void Gd__gd_core_items__GlovesofHaste::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_bonusSpeed = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__GlovesofHaste::meta() const { return &META_Gd__gd_core_items__GlovesofHaste; }
gd::GdVal Gd__gd_core_items__GlovesofHaste::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__GlovesofHaste::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__GlovesofHaste::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_bonusSpeed_1787: out = this->f_bonusSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__GlovesofHaste::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bonusSpeed_1787: this->f_bonusSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__GlovesofHaste::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__GlovesofHaste::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__GlovesofHaste::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__GlovesofHaste::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_97, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__GlovesofHaste::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1484 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1485 = (_t1484.kind == gd::GdVal::Kind::Arr) ? _t1484.arr : nullptr;
        uint32_t _len__t1486 = _t1485 ? _t1485->len : 0u;
        for (uint32_t _t1486 = 0; _t1486 < _len__t1486; ++_t1486) {
            gd::GdVal lv_item = _t1485->data[_t1486];
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_275, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__GlovesofHaste::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_bonusSpeed = gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), gd::GdVal::from_int(100LL));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__GlovesofHaste(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__GlovesofHaste>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__GlovesofHaste = {CLS_Gd__gd_core_items__GlovesofHaste, "GlovesofHaste", "res://gd_core_items/GlovesofHaste.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__GlovesofHaste, &Gd__gd_core_items__GlovesofHaste::get_static_prop_fn, &Gd__gd_core_items__GlovesofHaste::call_static_fn};

void Gd__gd_core_items__LuckyBow::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Bow::init_fields(gd_ctx);
    this->f_extraAttack = gd::GdVal::from_bool(false);
}
const gd::GdClassMeta* Gd__gd_core_items__LuckyBow::meta() const { return &META_Gd__gd_core_items__LuckyBow; }
gd::GdVal Gd__gd_core_items__LuckyBow::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Bow::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__LuckyBow::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__LuckyBow::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_extraAttack_1822: out = this->f_extraAttack; return true;
        default: break;
    }
    return Gd__gd_core_items__Bow::get_prop(prop, out);
}
bool Gd__gd_core_items__LuckyBow::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_extraAttack_1822: this->f_extraAttack = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Bow::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__LuckyBow::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onWeaponAttacked_950: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Bow::has_own_method(m);
}
bool Gd__gd_core_items__LuckyBow::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onWeaponAttacked_950: out = fn_onWeaponAttacked(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Bow::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__LuckyBow::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Bow::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__LuckyBow::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyBow::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyBow::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_118, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StaminaResult_1280), SYM_GEN_Sufficient_2605))))) {
        gd::GdVal lv_res = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_222, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 1); })();
        if (gd::gd_truth(this->f_extraAttack)) {
            gd::GdVal lv_res2 = ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, lv_res, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_222, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_res2}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false), gd::GdVal::from_bool(false), gd::get_prop(gd_ctx, lv_res2, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyBow::fn_onWeaponAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_wasCriticalHit_1433, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(false), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyBow::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyBow::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__extraAttack = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv__extraAttack)) {
    }
    else {
    }
    this->f_extraAttack = lv__extraAttack;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyBow::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bow::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__LuckyBow(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__LuckyBow>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__LuckyBow = {CLS_Gd__gd_core_items__LuckyBow, "LuckyBow", "res://gd_core_items/LuckyBow.gd", &META_Gd__gd_core_items__Bow, true, _alloc_Gd__gd_core_items__LuckyBow, &Gd__gd_core_items__LuckyBow::get_static_prop_fn, &Gd__gd_core_items__LuckyBow::call_static_fn};

void Gd__gd_core_items__PoisonDagger::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Dagger::init_fields(gd_ctx);
    this->f_poison = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__PoisonDagger::meta() const { return &META_Gd__gd_core_items__PoisonDagger; }
gd::GdVal Gd__gd_core_items__PoisonDagger::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Dagger::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__PoisonDagger::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__PoisonDagger::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_poison_1867: out = this->f_poison; return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::get_prop(prop, out);
}
bool Gd__gd_core_items__PoisonDagger::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_poison_1867: this->f_poison = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__PoisonDagger::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::has_own_method(m);
}
bool Gd__gd_core_items__PoisonDagger::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__PoisonDagger::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Dagger::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__PoisonDagger::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_poison}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_213, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PoisonDagger::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Dagger::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_poison = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__PoisonDagger(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__PoisonDagger>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__PoisonDagger = {CLS_Gd__gd_core_items__PoisonDagger, "PoisonDagger", "res://gd_core_items/PoisonDagger.gd", &META_Gd__gd_core_items__Dagger, true, _alloc_Gd__gd_core_items__PoisonDagger, &Gd__gd_core_items__PoisonDagger::get_static_prop_fn, &Gd__gd_core_items__PoisonDagger::call_static_fn};

void Gd__gd_core_items__StaffofUnhealing::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_buffActive = gd::GdVal::from_bool(false);
    this->f_activationParticles = gd::GdVal::null();
    this->f_unhealingTimer = gd::GdVal::null();
    this->f_manaCost = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__StaffofUnhealing::meta() const { return &META_Gd__gd_core_items__StaffofUnhealing; }
gd::GdVal Gd__gd_core_items__StaffofUnhealing::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__StaffofUnhealing::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__StaffofUnhealing::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_buffActive_1718: out = this->f_buffActive; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_unhealingTimer_1889: out = this->f_unhealingTimer; return true;
        case SYM_GEN_manaCost_1720: out = this->f_manaCost; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__StaffofUnhealing::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffActive_1718: this->f_buffActive = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_unhealingTimer_1889: this->f_unhealingTimer = val; return true;
        case SYM_GEN_manaCost_1720: this->f_manaCost = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__StaffofUnhealing::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_buffEnded_1722: return true;
        case SYM_GEN_onCombatEnd_134: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__StaffofUnhealing::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_buffEnded_1722: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_onCombatEnd_134: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__StaffofUnhealing::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__StaffofUnhealing::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StaffofUnhealing::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_118, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StaminaResult_1280), SYM_GEN_Sufficient_2605))))) {
        gd::GdVal lv_healAmount = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getMana_1228, nullptr, 0), this->f_manaCost)))) {
            if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_buffActive)))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 2); })();
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_giveUnhealing_1162, _ca, 1); })();
            }
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_unhealing", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })()}; return gd::call_method(gd_ctx, this->f_unhealingTimer, SYM_GEN_start_1685, _ca, 1); })();
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_334, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_healAmount, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, _ca, 2); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {lv_healAmount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, _ca, 1); })();
        }
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StaffofUnhealing::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_reduceUnhealing_1163, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StaffofUnhealing::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_unhealingTimer, SYM_GEN_stop_1686, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StaffofUnhealing::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StaffofUnhealing::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv_active)) {
    }
    else {
    }
    this->f_buffActive = lv_active;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StaffofUnhealing::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_unhealingTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "UnhealingTimer", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffEnded", 9u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_137, _ca, 3); })();
    this->f_manaCost = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__StaffofUnhealing(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__StaffofUnhealing>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__StaffofUnhealing = {CLS_Gd__gd_core_items__StaffofUnhealing, "StaffofUnhealing", "res://gd_core_items/StaffofUnhealing.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__StaffofUnhealing, &Gd__gd_core_items__StaffofUnhealing::get_static_prop_fn, &Gd__gd_core_items__StaffofUnhealing::call_static_fn};

void Gd__gd_core_items__VampiricScythe::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_lastSpeedBonus = gd::GdVal::from_float(0.0);
}
const gd::GdClassMeta* Gd__gd_core_items__VampiricScythe::meta() const { return &META_Gd__gd_core_items__VampiricScythe; }
gd::GdVal Gd__gd_core_items__VampiricScythe::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__VampiricScythe::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__VampiricScythe::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_lastSpeedBonus_1002: out = this->f_lastSpeedBonus; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__VampiricScythe::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_lastSpeedBonus_1002: this->f_lastSpeedBonus = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__VampiricScythe::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onVampirismChanged_943: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__VampiricScythe::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onVampirismChanged_943: out = fn_onVampirismChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__VampiricScythe::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__VampiricScythe::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Stack_859), SYM_GEN_Vampirism_2566)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_gainsStack_88, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__VampiricScythe::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1487 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1488 = (_t1487.kind == gd::GdVal::Kind::Arr) ? _t1487.arr : nullptr;
        uint32_t _len__t1489 = _t1488 ? _t1488->len : 0u;
        for (uint32_t _t1489 = 0; _t1489 < _len__t1489; ++_t1489) {
            gd::GdVal lv_item = _t1488->data[_t1489];
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Vampirism_2566), gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_giveBuffPower_305, _ca, 2); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_vampirism_changed", 27u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onVampirismChanged", 18u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__VampiricScythe::fn_onVampirismChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_scytheSpeedBonus = gd::gd_min(gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getVampirism_1210, nullptr, 0)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0));
    lv_scytheSpeedBonus = gd::gd_div(gd_ctx, lv_scytheSpeedBonus, gd::GdVal::from_float(100.0));
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_sub(lv_scytheSpeedBonus, this->f_lastSpeedBonus)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    this->f_lastSpeedBonus = lv_scytheSpeedBonus;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__VampiricScythe::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_lastSpeedBonus = gd::GdVal::from_float(0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__VampiricScythe::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__VampiricScythe(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__VampiricScythe>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__VampiricScythe = {CLS_Gd__gd_core_items__VampiricScythe, "VampiricScythe", "res://gd_core_items/VampiricScythe.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__VampiricScythe, &Gd__gd_core_items__VampiricScythe::get_static_prop_fn, &Gd__gd_core_items__VampiricScythe::call_static_fn};
