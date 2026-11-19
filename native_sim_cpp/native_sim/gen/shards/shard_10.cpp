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
#include "../hdrs/Gd__gd_core_items__Exclusive__Hypercube.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Laboratory.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__MagicRing.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__MrsStruggles.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__PlasticCube.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__PuzzlebagZ.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Resistor.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ShepherdsCrook.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SnowStick.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SquirrelArcher.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Thornbloom.hpp"
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
        case SYM_GEN_BagTiles_929: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Bag_BagTiles);
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
        case SYM_GEN_bagTilemapPosition_910: out = this->f_bagTilemapPosition; return true;
        case SYM_GEN_cachedAffectedInsideItems_911: out = this->f_cachedAffectedInsideItems; return true;
        case SYM_GEN_cachedInsideItems_912: out = this->f_cachedInsideItems; return true;
        case SYM_GEN_bagTilemap_913: out = this->f_bagTilemap; return true;
        case SYM_GEN_border_914: out = this->f_border; return true;
        case SYM_GEN_BagTiles_929: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Bag_BagTiles); return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__Bag::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bagTilemapPosition_910: this->f_bagTilemapPosition = val; return true;
        case SYM_GEN_cachedAffectedInsideItems_911: this->f_cachedAffectedInsideItems = val; return true;
        case SYM_GEN_cachedInsideItems_912: this->f_cachedInsideItems = val; return true;
        case SYM_GEN_bagTilemap_913: this->f_bagTilemap = val; return true;
        case SYM_GEN_border_914: this->f_border = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Bag::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getHoverPriority_688: return true;
        case SYM_GEN_isBag_81: return true;
        case SYM_GEN_showBagBorderForItem_915: return true;
        case SYM_GEN_canApplyEffect_916: return true;
        case SYM_GEN_canBePicked_735: return true;
        case SYM_GEN_canBeLocked_817: return true;
        case SYM_GEN_resetZ_448: return true;
        case SYM_GEN_addToInventory_118: return true;
        case SYM_GEN_getBagLayerPriority_917: return true;
        case SYM_GEN_hasBagEffect_918: return true;
        case SYM_GEN__process_678: return true;
        case SYM_GEN_reactToDropResult_718: return true;
        case SYM_GEN_onRemoveFromInventory_416: return true;
        case SYM_GEN_getTopLeftGlobal_651: return true;
        case SYM_GEN_getBottomRightGlobal_652: return true;
        case SYM_GEN_isEmpty_919: return true;
        case SYM_GEN_getItemsInside_920: return true;
        case SYM_GEN_getEmptyCells_921: return true;
        case SYM_GEN_getEmptyGlobalPositions_922: return true;
        case SYM_GEN_getAffectedItemsInside_923: return true;
        case SYM_GEN_previewCanAffect_471: return true;
        case SYM_GEN_prepare_120: return true;
        case SYM_GEN_combatToShop_740: return true;
        case SYM_GEN_getCraftableNeighbors_490: return true;
        case SYM_GEN_onItemAdded_435: return true;
        case SYM_GEN_onAffectedItemInsideAdded_924: return true;
        case SYM_GEN_onItemRemoved_436: return true;
        case SYM_GEN_onAffectedItemInsideRemoved_925: return true;
        case SYM_GEN_pushItemsInsideToStorage_396: return true;
        case SYM_GEN_onDraggedWithParentStart_714: return true;
        case SYM_GEN_onDraggedWithParentEnd_716: return true;
        case SYM_GEN_getNumAffectedInside_926: return true;
        case SYM_GEN_getNumAffectedInside_type_927: return true;
        case SYM_GEN_getBagMultiplicity_928: return true;
        case SYM_GEN_discard_760: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Bag::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getHoverPriority_688: out = fn_getHoverPriority(args, argc); return true;
        case SYM_GEN_isBag_81: out = fn_isBag(args, argc); return true;
        case SYM_GEN_showBagBorderForItem_915: out = fn_showBagBorderForItem(args, argc); return true;
        case SYM_GEN_canApplyEffect_916: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN_canBePicked_735: out = fn_canBePicked(args, argc); return true;
        case SYM_GEN_canBeLocked_817: out = fn_canBeLocked(args, argc); return true;
        case SYM_GEN_resetZ_448: out = fn_resetZ(args, argc); return true;
        case SYM_GEN_addToInventory_118: out = fn_addToInventory(args, argc); return true;
        case SYM_GEN_getBagLayerPriority_917: out = fn_getBagLayerPriority(args, argc); return true;
        case SYM_GEN_hasBagEffect_918: out = fn_hasBagEffect(args, argc); return true;
        case SYM_GEN__process_678: out = fn__process(args, argc); return true;
        case SYM_GEN_reactToDropResult_718: out = fn_reactToDropResult(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_416: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_getTopLeftGlobal_651: out = fn_getTopLeftGlobal(args, argc); return true;
        case SYM_GEN_getBottomRightGlobal_652: out = fn_getBottomRightGlobal(args, argc); return true;
        case SYM_GEN_isEmpty_919: out = fn_isEmpty(args, argc); return true;
        case SYM_GEN_getItemsInside_920: out = fn_getItemsInside(args, argc); return true;
        case SYM_GEN_getEmptyCells_921: out = fn_getEmptyCells(args, argc); return true;
        case SYM_GEN_getEmptyGlobalPositions_922: out = fn_getEmptyGlobalPositions(args, argc); return true;
        case SYM_GEN_getAffectedItemsInside_923: out = fn_getAffectedItemsInside(args, argc); return true;
        case SYM_GEN_previewCanAffect_471: out = fn_previewCanAffect(args, argc); return true;
        case SYM_GEN_prepare_120: out = fn_prepare(args, argc); return true;
        case SYM_GEN_combatToShop_740: out = fn_combatToShop(args, argc); return true;
        case SYM_GEN_getCraftableNeighbors_490: out = fn_getCraftableNeighbors(args, argc); return true;
        case SYM_GEN_onItemAdded_435: out = fn_onItemAdded(args, argc); return true;
        case SYM_GEN_onAffectedItemInsideAdded_924: out = fn_onAffectedItemInsideAdded(args, argc); return true;
        case SYM_GEN_onItemRemoved_436: out = fn_onItemRemoved(args, argc); return true;
        case SYM_GEN_onAffectedItemInsideRemoved_925: out = fn_onAffectedItemInsideRemoved(args, argc); return true;
        case SYM_GEN_pushItemsInsideToStorage_396: out = fn_pushItemsInsideToStorage(args, argc); return true;
        case SYM_GEN_onDraggedWithParentStart_714: out = fn_onDraggedWithParentStart(args, argc); return true;
        case SYM_GEN_onDraggedWithParentEnd_716: out = fn_onDraggedWithParentEnd(args, argc); return true;
        case SYM_GEN_getNumAffectedInside_926: out = fn_getNumAffectedInside(args, argc); return true;
        case SYM_GEN_getNumAffectedInside_type_927: out = fn_getNumAffectedInside_type(args, argc); return true;
        case SYM_GEN_getBagMultiplicity_928: out = fn_getBagMultiplicity(args, argc); return true;
        case SYM_GEN_discard_760: out = fn_discard(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
        return Gd__gd_core__Bag::get_static_const_or_enum(gd_ctx, SYM_GEN_DRAG_PRIORITY_523);
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
    return (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isBag_81, nullptr, 0)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_916, _ca, 1); })())) : gd::GdVal::from_bool(false));
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
    (void)([&]() { gd::GdVal _ca[] = {lv__inventory, lv__occupiedCells, lv__placedByPlayer}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_addToInventory_118, _ca, 3, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_getBagLayerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getRarity_234, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Rarity_858), SYM_GEN_Unique_2756))))) {
        return gd::GdVal::from_int(2LL);
    }
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasBagEffect_918, nullptr, 0))) {
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
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1280), SYM_GEN_INVENTORY_1089), SYM_GEN_canAddBag_2757, _ca, 1); })())) {
        }
        else {
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_reactToDropResult(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_result = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_result}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_reactToDropResult_718, _ca, 1, _out); return _out; })();
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
    return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_920, nullptr, 0), gd::SYM_empty, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_getItemsInside(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, this->f_cachedInsideItems, gd::SYM_empty, nullptr, 0))))) {
        return this->f_cachedInsideItems;
    }
    return ([&]() { gd::GdVal _ca[] = {this->f_occupiedCells}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItemsInCells_1515, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_getEmptyCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_emptyCells = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1406 = gd::gd_iter_seq(gd_ctx.arena, this->f_occupiedCells);
        gd::GdArr* _t1407 = (_t1406.kind == gd::GdVal::Kind::Arr) ? _t1406.arr : nullptr;
        uint32_t _len__t1408 = _t1407 ? _t1407->len : 0u;
        for (uint32_t _t1408 = 0; _t1408 < _len__t1408; ++_t1408) {
            gd::GdVal lv_cell = _t1407->data[_t1408];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_cell}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_isCellEmpty_1512, _ca, 1); })())) {
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
        gd::GdVal _t1409 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getEmptyCells_921, nullptr, 0));
        gd::GdArr* _t1410 = (_t1409.kind == gd::GdVal::Kind::Arr) ? _t1409.arr : nullptr;
        uint32_t _len__t1411 = _t1410 ? _t1410->len : 0u;
        for (uint32_t _t1411 = 0; _t1411 < _len__t1411; ++_t1411) {
            gd::GdVal lv_cell = _t1410->data[_t1411];
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_cell, gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_cellToGlobalPos_2758, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_positions, gd::SYM_push_back, _ca, 1); })();
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
        gd::GdVal _t1412 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_920, nullptr, 0));
        gd::GdArr* _t1413 = (_t1412.kind == gd::GdVal::Kind::Arr) ? _t1412.arr : nullptr;
        uint32_t _len__t1414 = _t1413 ? _t1413->len : 0u;
        for (uint32_t _t1414 = 0; _t1414 < _len__t1414; ++_t1414) {
            gd::GdVal lv_item = _t1413->data[_t1414];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_916, _ca, 1); })())) {
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
    this->f_cachedInsideItems = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_920, nullptr, 0);
    {
        gd::GdVal _t1415 = gd::gd_iter_seq(gd_ctx.arena, this->f_cachedInsideItems);
        gd::GdArr* _t1416 = (_t1415.kind == gd::GdVal::Kind::Arr) ? _t1415.arr : nullptr;
        uint32_t _len__t1417 = _t1416 ? _t1416->len : 0u;
        for (uint32_t _t1417 = 0; _t1417 < _len__t1417; ++_t1417) {
            gd::GdVal lv_item = _t1416->data[_t1417];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_916, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, this->f_cachedAffectedInsideItems, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_prepare_120, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_combatToShop(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_cachedAffectedInsideItems, gd::SYM_clear, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_cachedInsideItems, gd::SYM_clear, nullptr, 0);
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_combatToShop_740, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_getCraftableNeighbors(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_craftableItems = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1418 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_920, nullptr, 0));
        gd::GdArr* _t1419 = (_t1418.kind == gd::GdVal::Kind::Arr) ? _t1418.arr : nullptr;
        uint32_t _len__t1420 = _t1419 ? _t1419->len : 0u;
        for (uint32_t _t1420 = 0; _t1420 < _len__t1420; ++_t1420) {
            gd::GdVal lv_item = _t1419->data[_t1420];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isAvailableForCrafting_491, nullptr, 0))) {
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
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_onItemAdded_435, _ca, 1, _out); return _out; })();
    if (gd::gd_truth((gd::gd_truth(gd::gd_in(lv_item, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_920, nullptr, 0))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_916, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        if (gd::gd_truth(gd::get_prop(gd_ctx, lv_item, SYM_GEN_placedByPlayer_48))) {
        }
        (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAffectedItemInsideAdded_924, _ca, 1); })();
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
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_onItemRemoved_436, _ca, 1, _out); return _out; })();
    if (gd::gd_truth((gd::gd_truth(gd::gd_in(lv_item, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_920, nullptr, 0))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_916, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAffectedItemInsideRemoved_925, _ca, 1); })();
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
    (void)([&]() { gd::GdVal _ca[] = {lv_bag}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_onDraggedWithParentStart_714, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_onDraggedWithParentEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_onDraggedWithParentEnd_716, nullptr, 0, _out); return _out; })();
    if (gd::gd_truth(this->f_dragged)) {
    }
    else {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetZ_448, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn_getNumAffectedInside(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_num = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t1421 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_923, nullptr, 0));
        gd::GdArr* _t1422 = (_t1421.kind == gd::GdVal::Kind::Arr) ? _t1421.arr : nullptr;
        uint32_t _len__t1423 = _t1422 ? _t1422->len : 0u;
        for (uint32_t _t1423 = 0; _t1423 < _len__t1423; ++_t1423) {
            gd::GdVal lv_item = _t1422->data[_t1423];
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
        gd::GdVal _t1424 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_923, nullptr, 0));
        gd::GdArr* _t1425 = (_t1424.kind == gd::GdVal::Kind::Arr) ? _t1424.arr : nullptr;
        uint32_t _len__t1426 = _t1425 ? _t1425->len : 0u;
        for (uint32_t _t1426 = 0; _t1426 < _len__t1426; ++_t1426) {
            gd::GdVal lv_item = _t1425->data[_t1426];
            lv_num = gd::gd_add(gd_ctx, lv_num, ([&]() { gd::GdVal _ca[] = {lv_type}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_getTypeMultiplicity_78, _ca, 1); })());
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
    (void)([&]() { gd::GdVal _ca[] = {lv_discardGems}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_discard_760, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bag::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_GemMode_990: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Gems__Gem_GemMode);
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
        case SYM_GEN_hoveredSocket_957: out = this->f_hoveredSocket; return true;
        case SYM_GEN_socket_958: out = this->f_socket; return true;
        case SYM_GEN_movebackSocket_959: out = this->f_movebackSocket; return true;
        case SYM_GEN_dropTween_960: out = this->f_dropTween; return true;
        case SYM_GEN_gemPower_961: out = this->f_gemPower; return true;
        case SYM_GEN_dropPosition_962: out = this->f_dropPosition; return true;
        case SYM_GEN_dropRotation_963: out = this->f_dropRotation; return true;
        case SYM_GEN_quantizedRotation_964: out = this->f_quantizedRotation; return true;
        case SYM_GEN_socketDetectionArea_965: out = this->f_socketDetectionArea; return true;
        case SYM_GEN_gemAnimation_966: out = this->f_gemAnimation; return true;
        case SYM_GEN_GemMode_990: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Gems__Gem_GemMode); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Gems__Gem::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_hoveredSocket_957: this->f_hoveredSocket = val; return true;
        case SYM_GEN_socket_958: this->f_socket = val; return true;
        case SYM_GEN_movebackSocket_959: this->f_movebackSocket = val; return true;
        case SYM_GEN_dropTween_960: this->f_dropTween = val; return true;
        case SYM_GEN_gemPower_961: this->f_gemPower = val; return true;
        case SYM_GEN_dropPosition_962: this->f_dropPosition = val; return true;
        case SYM_GEN_dropRotation_963: this->f_dropRotation = val; return true;
        case SYM_GEN_quantizedRotation_964: this->f_quantizedRotation = val; return true;
        case SYM_GEN_socketDetectionArea_965: this->f_socketDetectionArea = val; return true;
        case SYM_GEN_gemAnimation_966: this->f_gemAnimation = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Gems__Gem::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_isGem_82: return true;
        case SYM_GEN_isOwnable_248: return true;
        case SYM_GEN_isOwnedByOpponent_249: return true;
        case SYM_GEN_getEffectiveOwnerType_255: return true;
        case SYM_GEN_getInventory_654: return true;
        case SYM_GEN_getItem_387: return true;
        case SYM_GEN_isPlaced_74: return true;
        case SYM_GEN_isInInventory_967: return true;
        case SYM_GEN_getGemMode_968: return true;
        case SYM_GEN_getGemPower_969: return true;
        case SYM_GEN_changeGemPower_970: return true;
        case SYM_GEN_getHoverPriority_688: return true;
        case SYM_GEN_character_72: return true;
        case SYM_GEN__process_678: return true;
        case SYM_GEN_previewCellCollision_469: return true;
        case SYM_GEN_gainFocus_690: return true;
        case SYM_GEN_loseFocus_699: return true;
        case SYM_GEN_prepareLerpToSocket_971: return true;
        case SYM_GEN_drop_719: return true;
        case SYM_GEN_lerpToSocket_972: return true;
        case SYM_GEN_pickup_713: return true;
        case SYM_GEN_addToSocket_973: return true;
        case SYM_GEN_unsocket_974: return true;
        case SYM_GEN_removeFromSocket_975: return true;
        case SYM_GEN_killDropTween_976: return true;
        case SYM_GEN_returnToSocket_397: return true;
        case SYM_GEN_hasCooldown_93: return true;
        case SYM_GEN_miniActivate_468: return true;
        case SYM_GEN_prepareInventory_977: return true;
        case SYM_GEN_prepareWeapon_978: return true;
        case SYM_GEN_prepareArmor_979: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_combatStartInventory_980: return true;
        case SYM_GEN_combatStartWeapon_981: return true;
        case SYM_GEN_combatStartArmor_982: return true;
        case SYM_GEN_combatStart_125: return true;
        case SYM_GEN_combatEndInventory_983: return true;
        case SYM_GEN_combatEndWeapon_984: return true;
        case SYM_GEN_combatEndArmor_985: return true;
        case SYM_GEN_combatEnd_129: return true;
        case SYM_GEN_shopEntered_741: return true;
        case SYM_GEN_getBaseDescription_986: return true;
        case SYM_GEN_getDescription_638: return true;
        case SYM_GEN_onHotSwapHoverWithGem_987: return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_988: return true;
        case SYM_GEN_createGemParticles_989: return true;
        case SYM_GEN_canPreviewFusions_824: return true;
        case SYM_GEN_canModifyChance_291: return true;
        case SYM_GEN_getNeighborItemsAndGems_487: return true;
        case SYM_GEN_canCombine_443: return true;
        case SYM_GEN_shift_452: return true;
        case SYM_GEN_isMovingBack_797: return true;
        case SYM_GEN_addToStorageBox_663: return true;
        case SYM_GEN_discard_760: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Gems__Gem::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_isGem_82: out = fn_isGem(args, argc); return true;
        case SYM_GEN_isOwnable_248: out = fn_isOwnable(args, argc); return true;
        case SYM_GEN_isOwnedByOpponent_249: out = fn_isOwnedByOpponent(args, argc); return true;
        case SYM_GEN_getEffectiveOwnerType_255: out = fn_getEffectiveOwnerType(args, argc); return true;
        case SYM_GEN_getInventory_654: out = fn_getInventory(args, argc); return true;
        case SYM_GEN_getItem_387: out = fn_getItem(args, argc); return true;
        case SYM_GEN_isPlaced_74: out = fn_isPlaced(args, argc); return true;
        case SYM_GEN_isInInventory_967: out = fn_isInInventory(args, argc); return true;
        case SYM_GEN_getGemMode_968: out = fn_getGemMode(args, argc); return true;
        case SYM_GEN_getGemPower_969: out = fn_getGemPower(args, argc); return true;
        case SYM_GEN_changeGemPower_970: out = fn_changeGemPower(args, argc); return true;
        case SYM_GEN_getHoverPriority_688: out = fn_getHoverPriority(args, argc); return true;
        case SYM_GEN_character_72: out = fn_character(args, argc); return true;
        case SYM_GEN__process_678: out = fn__process(args, argc); return true;
        case SYM_GEN_previewCellCollision_469: out = fn_previewCellCollision(args, argc); return true;
        case SYM_GEN_gainFocus_690: out = fn_gainFocus(args, argc); return true;
        case SYM_GEN_loseFocus_699: out = fn_loseFocus(args, argc); return true;
        case SYM_GEN_prepareLerpToSocket_971: out = fn_prepareLerpToSocket(args, argc); return true;
        case SYM_GEN_drop_719: out = fn_drop(args, argc); return true;
        case SYM_GEN_lerpToSocket_972: out = fn_lerpToSocket(args, argc); return true;
        case SYM_GEN_pickup_713: out = fn_pickup(args, argc); return true;
        case SYM_GEN_addToSocket_973: out = fn_addToSocket(args, argc); return true;
        case SYM_GEN_unsocket_974: out = fn_unsocket(args, argc); return true;
        case SYM_GEN_removeFromSocket_975: out = fn_removeFromSocket(args, argc); return true;
        case SYM_GEN_killDropTween_976: out = fn_killDropTween(args, argc); return true;
        case SYM_GEN_returnToSocket_397: out = fn_returnToSocket(args, argc); return true;
        case SYM_GEN_hasCooldown_93: out = fn_hasCooldown(args, argc); return true;
        case SYM_GEN_miniActivate_468: out = fn_miniActivate(args, argc); return true;
        case SYM_GEN_prepareInventory_977: out = fn_prepareInventory(args, argc); return true;
        case SYM_GEN_prepareWeapon_978: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_prepareArmor_979: out = fn_prepareArmor(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_combatStartInventory_980: out = fn_combatStartInventory(args, argc); return true;
        case SYM_GEN_combatStartWeapon_981: out = fn_combatStartWeapon(args, argc); return true;
        case SYM_GEN_combatStartArmor_982: out = fn_combatStartArmor(args, argc); return true;
        case SYM_GEN_combatStart_125: out = fn_combatStart(args, argc); return true;
        case SYM_GEN_combatEndInventory_983: out = fn_combatEndInventory(args, argc); return true;
        case SYM_GEN_combatEndWeapon_984: out = fn_combatEndWeapon(args, argc); return true;
        case SYM_GEN_combatEndArmor_985: out = fn_combatEndArmor(args, argc); return true;
        case SYM_GEN_combatEnd_129: out = fn_combatEnd(args, argc); return true;
        case SYM_GEN_shopEntered_741: out = fn_shopEntered(args, argc); return true;
        case SYM_GEN_getBaseDescription_986: out = fn_getBaseDescription(args, argc); return true;
        case SYM_GEN_getDescription_638: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_onHotSwapHoverWithGem_987: out = fn_onHotSwapHoverWithGem(args, argc); return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_988: out = fn_onHotSwapHoverWithGemEnd(args, argc); return true;
        case SYM_GEN_createGemParticles_989: out = fn_createGemParticles(args, argc); return true;
        case SYM_GEN_canPreviewFusions_824: out = fn_canPreviewFusions(args, argc); return true;
        case SYM_GEN_canModifyChance_291: out = fn_canModifyChance(args, argc); return true;
        case SYM_GEN_getNeighborItemsAndGems_487: out = fn_getNeighborItemsAndGems(args, argc); return true;
        case SYM_GEN_canCombine_443: out = fn_canCombine(args, argc); return true;
        case SYM_GEN_shift_452: out = fn_shift(args, argc); return true;
        case SYM_GEN_isMovingBack_797: out = fn_isMovingBack(args, argc); return true;
        case SYM_GEN_addToStorageBox_663: out = fn_addToStorageBox(args, argc); return true;
        case SYM_GEN_discard_760: out = fn_discard(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
        return gd::call_method(gd_ctx, gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_387, nullptr, 0), SYM_GEN_isOwnable_248, nullptr, 0);
    }
    else {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_isOwnable_248, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_isOwnedByOpponent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_socket, gd::GdVal::null())))) {
        return gd::call_method(gd_ctx, gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_387, nullptr, 0), SYM_GEN_isOwnedByOpponent_249, nullptr, 0);
    }
    else {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_isOwnedByOpponent_249, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_getEffectiveOwnerType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_socket, gd::GdVal::null())))) {
        return gd::call_method(gd_ctx, gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_387, nullptr, 0), SYM_GEN_getEffectiveOwnerType_255, nullptr, 0);
    }
    else {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getEffectiveOwnerType_255, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_getInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_socket, gd::GdVal::null())))) {
        return gd::call_method(gd_ctx, gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_387, nullptr, 0), SYM_GEN_getInventory_654, nullptr, 0);
    }
    else {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getInventory_654, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_getItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_socket, gd::GdVal::null())))) {
        return gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_387, nullptr, 0);
    }
    else {
        return gd::GdVal::null();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_isPlaced(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_socket, gd::GdVal::null())))) {
        return gd::call_method(gd_ctx, gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_387, nullptr, 0), SYM_GEN_isPlaced_74, nullptr, 0);
    }
    else {
        return this->f_placed;
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_isInInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_socket, gd::GdVal::null())))) {
        return gd::call_method(gd_ctx, gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_387, nullptr, 0), SYM_GEN_isInInventory_967, nullptr, 0);
    }
    else {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_isInInventory_967, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_getGemMode(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_socket, gd::GdVal::null())))) {
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_387, nullptr, 0), SYM_GEN_isWeapon_80, nullptr, 0))) {
            return gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_990), SYM_GEN_Weapon_2666);
        }
        else {
            return gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_990), SYM_GEN_Armor_2750);
        }
    }
    else {
        if (gd::gd_truth(this->f_placed)) {
            return gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_990), SYM_GEN_Inventory_2754);
        }
        else {
            return gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_990), SYM_GEN_Inactive_2593);
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
        return Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_DRAG_PRIORITY_523);
    }
    else {
        return gd::GdVal::from_int(1LL);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_character(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_968, nullptr, 0), gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_990), SYM_GEN_Inactive_2593))))) {
        return gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1280);
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_968, nullptr, 0), gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_990), SYM_GEN_Inventory_2754))))) {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_character_72, nullptr, 0, _out); return _out; })();
    }
    else {
        return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_387, nullptr, 0), SYM_GEN_character_72, nullptr, 0);
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
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_hoveredSocket))) ? gd::GdVal::from_bool(gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_movebackSocket))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_frame_counter_1380), gd::gd_add(gd_ctx, this->f_pickupFrame, gd::GdVal::from_int(1LL))))))))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_previewCellCollision_469, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_gainFocus(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_gainFocus_690, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_loseFocus(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_loseFocus_699, nullptr, 0, _out); return _out; })();
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
    gd::GdVal lv_pickupType = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_PickupType_862), SYM_GEN_Grabbed_2633));
    (void)([&]() { gd::GdVal _ca[] = {lv_pickupType}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_pickup_713, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_socket, gd::GdVal::null())))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_killDropTween_976, nullptr, 0);
        this->f_movebackSocket = this->f_socket;
        this->f_hoveredSocket = this->f_socket;
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_387, nullptr, 0), SYM_GEN_ownerType_47), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_PlayerStorageBox_2579))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_UP)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setFaceDirection_476, _ca, 1); })();
        }
        else {
            this->f_faceDirection = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGlobalFaceDirection_464, nullptr, 0));
        }
        (void)gd::call_method(gd_ctx, this->f_socket, SYM_GEN_onPickupGem_2772, nullptr, 0);
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_killDropTween_976, nullptr, 0);
    gd::GdVal lv_s = this->f_socket;
    (void)gd::call_method(gd_ctx, this->f_socket, SYM_GEN_onPickupGem_2772, nullptr, 0);
    (void)gd::call_method(gd_ctx, lv_s, SYM_GEN_hideSocket_2773, nullptr, 0);
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
    gd::GdVal lv_gemMode = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_968, nullptr, 0);
    return (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_gemMode, gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_990), SYM_GEN_Inventory_2754)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_gemMode, gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_990), SYM_GEN_Inactive_2593))))))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_hasCooldown_93, nullptr, 0, _out); return _out; })())) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_miniActivate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_miniActivate_468, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.5)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_Scale_771, _ca, 1); })();
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
        gd::GdVal _t1427 = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_968, nullptr, 0);
        if (gd::gd_eq(_t1427, gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_990), SYM_GEN_Inventory_2754))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_prepareInventory_977, nullptr, 0);
        }
        else if (gd::gd_eq(_t1427, gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_990), SYM_GEN_Weapon_2666))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_prepareWeapon_978, nullptr, 0);
        }
        else if (gd::gd_eq(_t1427, gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_990), SYM_GEN_Armor_2750))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_prepareArmor_979, nullptr, 0);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_combatStart_125, nullptr, 0, _out); return _out; })();
    this->f_iterationCooldown = gd::gd_coerce_float(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_adjustCooldown_105, nullptr, 0));
    this->f_triggerTime = gd::gd_coerce_float(this->f_iterationCooldown);
    {
        gd::GdVal _t1428 = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_968, nullptr, 0);
        if (gd::gd_eq(_t1428, gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_990), SYM_GEN_Inventory_2754))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_combatStartInventory_980, nullptr, 0);
        }
        else if (gd::gd_eq(_t1428, gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_990), SYM_GEN_Weapon_2666))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_combatStartWeapon_981, nullptr, 0);
        }
        else if (gd::gd_eq(_t1428, gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_990), SYM_GEN_Armor_2750))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_combatStartArmor_982, nullptr, 0);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_combatEnd_129, nullptr, 0, _out); return _out; })();
    {
        gd::GdVal _t1429 = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_968, nullptr, 0);
        if (gd::gd_eq(_t1429, gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_990), SYM_GEN_Inventory_2754))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_combatEndInventory_983, nullptr, 0);
        }
        else if (gd::gd_eq(_t1429, gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_990), SYM_GEN_Weapon_2666))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_combatEndWeapon_984, nullptr, 0);
        }
        else if (gd::gd_eq(_t1429, gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_990), SYM_GEN_Armor_2750))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_combatEndArmor_985, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_shopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_craft = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_craft = gd::gd_coerce_bool(lv_craft);
    (void)([&]() { gd::GdVal _ca[] = {lv_craft}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_shopEntered_741, _ca, 1, _out); return _out; })();
    this->f_gemPower = gd::GdVal::from_float(1.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_getBaseDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    return ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getDescription_638, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseDescription_986, _ca, 1); })();
    gd::GdVal lv_colors = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_inactiveColor_2731), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_inactiveColor_2731), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_inactiveColor_2731)}));
    gd::GdVal lv_gemMode = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_968, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_gemMode, gd::get_prop(gd_ctx, Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_990), SYM_GEN_Inactive_2593))))) {
        { gd::GdVal _t1430 = lv_colors; gd::GdVal _t1431 = lv_gemMode; gd::set_index(gd_ctx, _t1430, _t1431, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_modifiedColor_2724)); }
    }
    return ([&]() { gd::GdVal _ca[] = {lv_descr, lv_colors, gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModeDescription_641, _ca, 4); })();
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
        return gd::call_method(gd_ctx, gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_387, nullptr, 0), SYM_GEN_canPreviewFusions_824, nullptr, 0);
    }
    else {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_canPreviewFusions_824, nullptr, 0, _out); return _out; })();
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
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_387, nullptr, 0), SYM_GEN_ownerType_47), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_850), SYM_GEN_PlayerStorageBox_2579))))) {
            return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
        }
        gd::GdVal lv_neighbors = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_387, nullptr, 0)}));
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_387, nullptr, 0), SYM_GEN_getNeighborItemsAndGems_487, nullptr, 0)}; return gd::call_method(gd_ctx, lv_neighbors, gd::SYM_append_array, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, lv_neighbors, gd::SYM_erase, _ca, 1); })();
        return lv_neighbors;
    }
    else {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getNeighborItemsAndGems_487, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_canCombine(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_socket)) {
        return gd::GdVal::from_bool(true);
    }
    else {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_canCombine_443, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_shift(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_direction = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_socket)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_direction}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_shift_452, _ca, 1, _out); return _out; })();
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
        (void)([&]() { gd::GdVal _ca[] = {lv_addImpulse, lv_tweenBouncyness, lv_checkCollisions, lv_targetPos, lv_speed, lv_secondCheck}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_addToStorageBox_663, _ca, 6, _out); return _out; })();
        (void)gd::call_method(gd_ctx, lv_s, SYM_GEN_onPickupGem_2772, nullptr, 0);
        (void)gd::call_method(gd_ctx, lv_s, SYM_GEN_hideSocket_2773, nullptr, 0);
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {lv_addImpulse, lv_tweenBouncyness, lv_checkCollisions, lv_targetPos, lv_speed, lv_secondCheck}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_addToStorageBox_663, _ca, 6, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn_discard(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_discardGems = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    (void)([&]() { gd::GdVal _ca[] = {lv_discardGems}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_discard_760, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_socket, gd::GdVal::null())))) {
        gd::set_prop(gd_ctx, this->f_socket, SYM_GEN_gem_2774, gd::GdVal::null());
        (void)gd::call_method(gd_ctx, this->f_socket, SYM_GEN_hideSocket_2773, nullptr, 0);
        this->f_socket = gd::GdVal::null();
        this->f_movebackSocket = gd::GdVal::null();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Gem::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_gateItem_1595), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Box of Riches", 13u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getDescriptor_1562, _ca, 1); })())))) {
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
        case SYM_GEN_Target_1490: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreEvent_Target);
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
        case SYM_GEN_id_1473: out = this->f_id; return true;
        case SYM_GEN_timestamp_1474: out = this->f_timestamp; return true;
        case SYM_GEN_parentEvent_1475: out = this->f_parentEvent; return true;
        case SYM_GEN_origin_1453: out = this->f_origin; return true;
        case SYM_GEN_type_1001: out = this->f_type; return true;
        case SYM_GEN_target_1476: out = this->f_target; return true;
        case SYM_GEN_params_1477: out = this->f_params; return true;
        case SYM_GEN_formatParams_1478: out = this->f_formatParams; return true;
        case SYM_GEN_Target_1490: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreEvent_Target); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreEvent::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_id_1473: this->f_id = gd::gd_coerce_int(val); return true;
        case SYM_GEN_timestamp_1474: this->f_timestamp = val; return true;
        case SYM_GEN_parentEvent_1475: this->f_parentEvent = val; return true;
        case SYM_GEN_origin_1453: this->f_origin = val; return true;
        case SYM_GEN_type_1001: this->f_type = val; return true;
        case SYM_GEN_target_1476: this->f_target = val; return true;
        case SYM_GEN_params_1477: this->f_params = val; return true;
        case SYM_GEN_formatParams_1478: this->f_formatParams = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreEvent::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_getType_1479: return true;
        case SYM_GEN_setTarget_1480: return true;
        case SYM_GEN_setParam_1481: return true;
        case SYM_GEN_getParam_1482: return true;
        case SYM_GEN_getAmount_1483: return true;
        case SYM_GEN_getAmountWithDefault_1484: return true;
        case SYM_GEN_hasParam_1485: return true;
        case SYM_GEN_getMainActor_1486: return true;
        case SYM_GEN_getOrigin_1487: return true;
        case SYM_GEN_fromCharacter_1488: return true;
        case SYM_GEN_getDepth_1489: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreEvent::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_getType_1479: out = fn_getType(args, argc); return true;
        case SYM_GEN_setTarget_1480: out = fn_setTarget(args, argc); return true;
        case SYM_GEN_setParam_1481: out = fn_setParam(args, argc); return true;
        case SYM_GEN_getParam_1482: out = fn_getParam(args, argc); return true;
        case SYM_GEN_getAmount_1483: out = fn_getAmount(args, argc); return true;
        case SYM_GEN_getAmountWithDefault_1484: out = fn_getAmountWithDefault(args, argc); return true;
        case SYM_GEN_hasParam_1485: out = fn_hasParam(args, argc); return true;
        case SYM_GEN_getMainActor_1486: out = fn_getMainActor(args, argc); return true;
        case SYM_GEN_getOrigin_1487: out = fn_getOrigin(args, argc); return true;
        case SYM_GEN_fromCharacter_1488: out = fn_fromCharacter(args, argc); return true;
        case SYM_GEN_getDepth_1489: out = fn_getDepth(args, argc); return true;
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
    { gd::GdVal _t1432 = this->f_params; gd::GdVal _t1433 = lv_paramName; gd::set_index(gd_ctx, _t1432, _t1433, lv_paramVal); }
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
        return gd::get_prop(gd_ctx, gd::call_method(gd_ctx, this->f_origin, SYM_GEN_character_72, nullptr, 0), SYM_GEN_playerId_1042);
    }
    else if (gd::gd_truth(this->f_target)) {
        return this->f_target;
    }
    else {
        return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCharacter), SYM_GEN_ID_1275), SYM_GEN_PLAYER_2539);
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
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(this->f_origin, &META_Gd__gd_core__CoreItem))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, this->f_origin, SYM_GEN_character_72, nullptr, 0), lv_character)))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreEvent::fn_getDepth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_parentEvent)) {
        return gd::gd_add(gd_ctx, gd::call_method(gd_ctx, this->f_parentEvent, SYM_GEN_getDepth_1489, nullptr, 0), gd::GdVal::from_int(1LL));
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
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_canAffect_secondary_285: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN_getCraftingOffset_846: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__Crossblades::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_285: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_getCraftingOffset_846: out = fn_getCraftingOffset(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_88, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crossblades::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_93, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crossblades::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1434 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Primary_2580)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, _ca, 1); })());
        gd::GdArr* _t1435 = (_t1434.kind == gd::GdVal::Kind::Arr) ? _t1434.arr : nullptr;
        uint32_t _len__t1436 = _t1435 ? _t1435->len : 0u;
        for (uint32_t _t1436 = 0; _t1436 < _len__t1436; ++_t1436) {
            gd::GdVal lv_item = _t1435->data[_t1436];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_159, _ca, 1); })();
        }
    }
    {
        gd::GdVal _t1437 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Secondary_2582)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, _ca, 1); })());
        gd::GdArr* _t1438 = (_t1437.kind == gd::GdVal::Kind::Arr) ? _t1437.arr : nullptr;
        uint32_t _len__t1439 = _t1438 ? _t1438->len : 0u;
        for (uint32_t _t1439 = 0; _t1439 < _len__t1439; ++_t1439) {
            gd::GdVal lv_item = _t1438->data[_t1439];
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_271, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crossblades::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_159, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_264, nullptr, 0), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_271, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crossblades::fn_getCraftingOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1440 = lv_forDirection;
        if (gd::gd_eq(_t1440, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_UP))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
        else if (gd::gd_eq(_t1440, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_DOWN))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
        else if (gd::gd_eq(_t1440, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_LEFT))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
        else if (gd::gd_eq(_t1440, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_RIGHT))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Crossblades::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_onDealtDamage_904: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Pan::has_own_method(m);
}
bool Gd__gd_core__Eggscalibur::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onDealtDamage_904: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseMana_331, _ca, 2); })();
    if (gd::gd_truth(lv_event)) {
        gd::GdVal lv_affected = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0);
        (void)gd::call_method(gd_ctx, lv_affected, gd::SYM_shuffle, nullptr, 0);
        {
            gd::GdVal _t1441 = gd::gd_iter_seq(gd_ctx.arena, lv_affected);
            gd::GdArr* _t1442 = (_t1441.kind == gd::GdVal::Kind::Arr) ? _t1441.arr : nullptr;
            uint32_t _len__t1443 = _t1442 ? _t1442->len : 0u;
            for (uint32_t _t1443 = 0; _t1443 < _len__t1443; ++_t1443) {
                gd::GdVal lv_food = _t1442->data[_t1443];
                (void)gd::call_method(gd_ctx, lv_food, SYM_GEN_doCooldownEffect_142, nullptr, 0);
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Eggscalibur::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Pan::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_activated_1292: out = this->f_activated; return true;
        case SYM_GEN_regenNeeded_938: out = this->f_regenNeeded; return true;
        case SYM_GEN_numStealedBuffs_1796: out = this->f_numStealedBuffs; return true;
        case SYM_GEN_fillAnimation_1794: out = this->f_fillAnimation; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__HeartofDarkness::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activated_1292: this->f_activated = val; return true;
        case SYM_GEN_regenNeeded_938: this->f_regenNeeded = val; return true;
        case SYM_GEN_numStealedBuffs_1796: this->f_numStealedBuffs = val; return true;
        case SYM_GEN_fillAnimation_1794: this->f_fillAnimation = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__HeartofDarkness::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onRegenChanged_1795: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__HeartofDarkness::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onRegenChanged_1795: out = fn_onRegenChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Dark_2600)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeartofDarkness::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_regeneration_changed", 30u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onRegenChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "darkspeed", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })()), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_271, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeartofDarkness::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_numStealedBuffs, gd::GdVal::null(), gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1357, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Regeneration_2568)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealRandomBuff_371, _ca, 4); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeartofDarkness::fn_onRegenChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_activated)))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getRegeneration_1213, nullptr, 0), this->f_regenNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_regenNeeded, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_344, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_315, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_215, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healreduction", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_reduceHealingEfficiency_1163, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeartofDarkness::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HeartofDarkness::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_852), SYM_GEN_High_2601);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_regenNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regent", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_numStealedBuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffsteal", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
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
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__LuckyClover::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__LuckyClover::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__LuckyClover::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_213, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_379, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LuckyClover::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Food::has_own_method(m);
}
bool Gd__gd_core__Pineapple::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Pineapple::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Pineapple::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_207, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Pineapple::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Food::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_reflects_1880: out = this->f_reflects; return true;
        case SYM_GEN_heat_1800: out = this->f_heat; return true;
        default: break;
    }
    return Gd__gd_core__DragonEgg::get_prop(prop, out);
}
bool Gd__gd_core__RubyEgg::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_reflects_1880: this->f_reflects = val; return true;
        case SYM_GEN_heat_1800: this->f_heat = val; return true;
        default: break;
    }
    return Gd__gd_core__DragonEgg::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__RubyEgg::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreCombatStart_123: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__DragonEgg::has_own_method(m);
}
bool Gd__gd_core__RubyEgg::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreCombatStart_123: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__DragonEgg::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__RubyEgg::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__DragonEgg::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__RubyEgg::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_reflects}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveReflectStacks_198, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RubyEgg::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doCooldownEffect_142, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RubyEgg::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_withReflectStacks = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    lv_withReflectStacks = gd::gd_coerce_bool(lv_withReflectStacks);
    if (gd::gd_truth(lv_withReflectStacks)) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_reflects}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveReflectStacks_198, _ca, 1); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RubyEgg::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__DragonEgg::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_reflects = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0));
    this->f_heat = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0));
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
        case SYM_GEN_potionColor_1742: out = this->f_potionColor; return true;
        case SYM_GEN_fluidTween_1743: out = this->f_fluidTween; return true;
        case SYM_GEN_isFull_1744: out = this->f_isFull; return true;
        case SYM_GEN_connector_881: out = this->f_connector; return true;
        case SYM_GEN_fluid_1745: out = this->f_fluid; return true;
        case SYM_GEN_fluidGradientTex_1746: out = this->f_fluidGradientTex; return true;
        case SYM_GEN_fluidGradient_1747: out = this->f_fluidGradient; return true;
        case SYM_GEN_baseFoaminess_1748: out = this->f_baseFoaminess; return true;
        case SYM_GEN_baseScroll_1749: out = this->f_baseScroll; return true;
        case SYM_GEN_baseLevel_1750: out = this->f_baseLevel; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Potion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_potionColor_1742: this->f_potionColor = val; return true;
        case SYM_GEN_fluidTween_1743: this->f_fluidTween = val; return true;
        case SYM_GEN_isFull_1744: this->f_isFull = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_connector_881: this->f_connector = val; return true;
        case SYM_GEN_fluid_1745: this->f_fluid = val; return true;
        case SYM_GEN_fluidGradientTex_1746: this->f_fluidGradientTex = val; return true;
        case SYM_GEN_fluidGradient_1747: this->f_fluidGradient = val; return true;
        case SYM_GEN_baseFoaminess_1748: this->f_baseFoaminess = val; return true;
        case SYM_GEN_baseScroll_1749: this->f_baseScroll = val; return true;
        case SYM_GEN_baseLevel_1750: this->f_baseLevel = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Potion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_prepare_120: return true;
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_isEmpty_919: return true;
        case gd::SYM_fill: return true;
        case gd::SYM_empty: return true;
        case SYM_GEN_drink_1751: return true;
        case SYM_GEN_consumePotion_1752: return true;
        case SYM_GEN_onTriggerPotion_1753: return true;
        case SYM_GEN_triggerPotion_1754: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN_activate_148: return true;
        case SYM_GEN_shopEntered_741: return true;
        case SYM_GEN_getAffectedCellsAfterRotate_primary_408: return true;
        case SYM_GEN_addToInventory_118: return true;
        case SYM_GEN_onRemoveFromInventory_416: return true;
        case SYM_GEN_onFusingAsIngredient_838: return true;
        case SYM_GEN_onAffectedItemAdded_433: return true;
        case SYM_GEN_onAffectedItemRemoved_434: return true;
        case SYM_GEN_updateConnector_1755: return true;
        case SYM_GEN_resetGradient_1756: return true;
        case SYM_GEN_discard_760: return true;
        case SYM_GEN_getStarPosition_1757: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Potion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_prepare_120: out = fn_prepare(args, argc); return true;
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_isEmpty_919: out = fn_isEmpty(args, argc); return true;
        case gd::SYM_fill: out = fn_fill(args, argc); return true;
        case gd::SYM_empty: out = fn_empty(args, argc); return true;
        case SYM_GEN_drink_1751: out = fn_drink(args, argc); return true;
        case SYM_GEN_consumePotion_1752: out = fn_consumePotion(args, argc); return true;
        case SYM_GEN_onTriggerPotion_1753: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_triggerPotion_1754: out = fn_triggerPotion(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_activate_148: out = fn_activate(args, argc); return true;
        case SYM_GEN_shopEntered_741: out = fn_shopEntered(args, argc); return true;
        case SYM_GEN_getAffectedCellsAfterRotate_primary_408: out = fn_getAffectedCellsAfterRotate_primary(args, argc); return true;
        case SYM_GEN_addToInventory_118: out = fn_addToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_416: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_onFusingAsIngredient_838: out = fn_onFusingAsIngredient(args, argc); return true;
        case SYM_GEN_onAffectedItemAdded_433: out = fn_onAffectedItemAdded(args, argc); return true;
        case SYM_GEN_onAffectedItemRemoved_434: out = fn_onAffectedItemRemoved(args, argc); return true;
        case SYM_GEN_updateConnector_1755: out = fn_updateConnector(args, argc); return true;
        case SYM_GEN_resetGradient_1756: out = fn_resetGradient(args, argc); return true;
        case SYM_GEN_discard_760: out = fn_discard(args, argc); return true;
        case SYM_GEN_getStarPosition_1757: out = fn_getStarPosition(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Potion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Potion::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_prepare_120, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Potion_2652)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
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
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_consumePotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_withActivate = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    lv_withActivate = gd::gd_coerce_bool(lv_withActivate);
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_919, nullptr, 0))) {
        return gd::GdVal::null();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drink_1751, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_triggerPotion_1754, _ca, 1); })();
    gd::GdVal lv_affected = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_affected, gd::SYM_empty, nullptr, 0))))) {
        (void)gd::call_method(gd_ctx, gd::get_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL)), SYM_GEN_triggerPotion_1754, nullptr, 0);
        (void)gd::call_method(gd_ctx, gd::get_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL)), SYM_GEN_miniActivate_468, nullptr, 0);
    }
    if (gd::gd_truth(lv_withActivate)) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
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
    (void)([&]() { gd::GdVal _ca[] = {lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onTriggerPotion_1753, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_774, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "potion_triggered", 16u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_obj(this)}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1375), SYM_GEN_emitSignal_1499, _ca, 3); })();
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
    (void)([&]() { gd::GdVal _ca[] = {lv_damageRes, lv_playCombatAni, lv_consume, gd::GdVal::null()}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_activate_148, _ca, 4, _out); return _out; })();
    if (gd::gd_truth(lv_emitSignal)) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "potion_emptied", 14u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_obj(this)}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1375), SYM_GEN_emitSignal_1499, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_shopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_craft = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_craft = gd::gd_coerce_bool(lv_craft);
    (void)([&]() { gd::GdVal _ca[] = {lv_craft}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_shopEntered_741, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_isFull)))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_fill, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_getAffectedCellsAfterRotate_primary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rotatedCells = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_faceDirection, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_DOWN))))) {
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
    (void)([&]() { gd::GdVal _ca[] = {lv__inventory, lv__occupiedCells, lv__placedByPlayer}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_addToInventory_118, _ca, 3, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateConnector_1755, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetGradient_1756, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_onFusingAsIngredient(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetGradient_1756, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_onAffectedItemAdded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_color, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Primary_2580))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateConnector_1755, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_onAffectedItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_color, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Primary_2580))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateConnector_1755, nullptr, 0);
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
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetGradient_1756, nullptr, 0);
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_discardGems}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_discard_760, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn_getStarPosition(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Potion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__WalrusTusk::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__WalrusTusk::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__WalrusTusk::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_207, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_379, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__WalrusTusk::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Banana::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Banana::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Banana::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_316, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Banana::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_attackCounter_997: out = this->f_attackCounter; return true;
        case SYM_GEN_lastSpeedBonus_998: out = this->f_lastSpeedBonus; return true;
        case SYM_GEN_speedPerSpike_999: out = this->f_speedPerSpike; return true;
        case SYM_GEN_numHits_1000: out = this->f_numHits; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__ClawsofAttack::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_attackCounter_997: this->f_attackCounter = val; return true;
        case SYM_GEN_lastSpeedBonus_998: this->f_lastSpeedBonus = val; return true;
        case SYM_GEN_speedPerSpike_999: this->f_speedPerSpike = val; return true;
        case SYM_GEN_numHits_1000: this->f_numHits = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__ClawsofAttack::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onSpikesChanged_940: return true;
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__ClawsofAttack::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onSpikesChanged_940: out = fn_onSpikesChanged(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__ClawsofAttack::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__ClawsofAttack::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_spikes_changed", 24u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onSpikesChanged", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ClawsofAttack::fn_onSpikesChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_clawsBonus = gd::gd_min(gd::gd_mul(this->f_speedPerSpike, gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getSpikes_1203, nullptr, 0)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0));
    lv_clawsBonus = gd::gd_div(gd_ctx, lv_clawsBonus, gd::GdVal::from_float(100.0));
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_sub(lv_clawsBonus, this->f_lastSpeedBonus)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_271, _ca, 1); })();
    this->f_lastSpeedBonus = lv_clawsBonus;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ClawsofAttack::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        this->f_attackCounter = gd::gd_add(gd_ctx, this->f_attackCounter, gd::GdVal::from_int(1LL));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_attackCounter, this->f_numHits)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_215, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_speedPerSpike = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0);
    this->f_numHits = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0));
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
        case SYM_GEN_hatchParticles_1764: out = this->f_hatchParticles; return true;
        case SYM_GEN_firePulse_1765: out = this->f_firePulse; return true;
        case SYM_GEN_whelpName_1766: out = this->f_whelpName; return true;
        case SYM_GEN_roundsToHatch_1767: out = this->f_roundsToHatch; return true;
        case SYM_GEN_reflectionStacks_1768: out = this->f_reflectionStacks; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__DragonEgg::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_hatchParticles_1764: this->f_hatchParticles = val; return true;
        case SYM_GEN_firePulse_1765: this->f_firePulse = val; return true;
        case SYM_GEN_whelpName_1766: this->f_whelpName = val; return true;
        case SYM_GEN_roundsToHatch_1767: this->f_roundsToHatch = val; return true;
        case SYM_GEN_reflectionStacks_1768: this->f_reflectionStacks = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__DragonEgg::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getData_634: return true;
        case SYM_GEN_setData_635: return true;
        case SYM_GEN_updateEgg_1769: return true;
        case SYM_GEN_isNextToNest_1770: return true;
        case SYM_GEN_readyToTransform_749: return true;
        case SYM_GEN_canHatch_1771: return true;
        case SYM_GEN_shopEntered_741: return true;
        case SYM_GEN_startHatching_1772: return true;
        case SYM_GEN_hatch_1773: return true;
        case SYM_GEN_hatch_deferred_1774: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__DragonEgg::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getData_634: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_635: out = fn_setData(args, argc); return true;
        case SYM_GEN_updateEgg_1769: out = fn_updateEgg(args, argc); return true;
        case SYM_GEN_isNextToNest_1770: out = fn_isNextToNest(args, argc); return true;
        case SYM_GEN_readyToTransform_749: out = fn_readyToTransform(args, argc); return true;
        case SYM_GEN_canHatch_1771: out = fn_canHatch(args, argc); return true;
        case SYM_GEN_shopEntered_741: out = fn_shopEntered(args, argc); return true;
        case SYM_GEN_startHatching_1772: out = fn_startHatching(args, argc); return true;
        case SYM_GEN_hatch_1773: out = fn_hatch(args, argc); return true;
        case SYM_GEN_hatch_deferred_1774: out = fn_hatch_deferred(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateEgg_1769, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_updateEgg(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canHatch_1771, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.0), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_789, _ca, 2); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_sub(gd::GdVal::from_float(1.0), gd::gd_div(gd_ctx, this->f_roundsToHatch, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0))), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_789, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_isNextToNest(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_placed)) {
        {
            gd::GdVal _t1444 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1510, nullptr, 0));
            gd::GdArr* _t1445 = (_t1444.kind == gd::GdVal::Kind::Arr) ? _t1444.arr : nullptr;
            uint32_t _len__t1446 = _t1445 ? _t1445->len : 0u;
            for (uint32_t _t1446 = 0; _t1446 < _len__t1446; ++_t1446) {
                gd::GdVal lv_item = _t1445->data[_t1446];
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, lv_item, SYM_GEN_getName_232, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Dragon Nest", 11u)))))) {
                    return gd::gd_in(gd::GdVal::from_obj(this), gd::call_method(gd_ctx, lv_item, SYM_GEN_getAffectedItems_418, nullptr, 0));
                }
            }
        }
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_readyToTransform(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canHatch_1771, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_canHatch(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_roundsToHatch, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_roundsToHatch, gd::GdVal::from_int(1LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isNextToNest_1770, nullptr, 0))) : gd::GdVal::from_bool(false)))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_shopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_craft = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_craft = gd::gd_coerce_bool(lv_craft);
    (void)([&]() { gd::GdVal _ca[] = {lv_craft}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_shopEntered_741, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_startHatching(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "hatch", 5u)), gd::gd_sub(Gd__gd_core_items__DragonEgg::get_static_const_or_enum(gd_ctx, SYM_GEN_TRANSFORMATION_DUR_602), gd::GdVal::from_float(0.1))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_callDelayed_1416, _ca, 3); })();
    {
        gd::GdVal _t1447 = gd::gd_iter_seq(gd_ctx.arena, this->f_shadows);
        gd::GdArr* _t1448 = (_t1447.kind == gd::GdVal::Kind::Arr) ? _t1447.arr : nullptr;
        uint32_t _len__t1449 = _t1448 ? _t1448->len : 0u;
        for (uint32_t _t1449 = 0; _t1449 < _len__t1449; ++_t1449) {
            gd::GdVal lv_shadow = _t1448->data[_t1449];
            gd::set_prop(gd_ctx, lv_shadow, SYM_GEN_offset_512, gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(138LL))).as_float()));
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_hatch(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "hatch_deferred", 14u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_defer_1418, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn_hatch_deferred(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DragonEgg::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_roundsToHatch = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateEgg_1769, nullptr, 0);
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
        case SYM_GEN_regen_1903: out = this->f_regen; return true;
        case SYM_GEN_regenPerHoly_1940: out = this->f_regenPerHoly; return true;
        case SYM_GEN_empower_994: out = this->f_empower; return true;
        case SYM_GEN_empowerPerHoly_1941: out = this->f_empowerPerHoly; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__AngelCrystal::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_regen_1903: this->f_regen = val; return true;
        case SYM_GEN_regenPerHoly_1940: this->f_regenPerHoly = val; return true;
        case SYM_GEN_empower_994: this->f_empower = val; return true;
        case SYM_GEN_empowerPerHoly_1941: this->f_empowerPerHoly = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__AngelCrystal::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onRegenChanged_1795: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__AngelCrystal::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onRegenChanged_1795: out = fn_onRegenChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Holy_2592)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AngelCrystal::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_regeneration_changed", 30u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onRegenChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AngelCrystal::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_regen, gd::gd_mul(this->f_regenPerHoly, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0)))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_212, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AngelCrystal::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_empower, gd::gd_mul(this->f_empowerPerHoly, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0)))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_215, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_143, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AngelCrystal::fn_onRegenChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), lv_amount), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_315, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AngelCrystal::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_regenPerHoly = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen_holy", 10u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_empowerPerHoly = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower_holy", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
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
        case SYM_GEN_activationParticles_908: out = this->f_activationParticles; return true;
        case SYM_GEN_maxStamina_1050: out = this->f_maxStamina; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BagofGiving::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activationParticles_908: this->f_activationParticles = val; return true;
        case SYM_GEN_maxStamina_1050: this->f_maxStamina = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BagofGiving::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canApplyEffect_916: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onItemInsideActivated_1957: return true;
        case SYM_GEN_onAddToInventory_417: return true;
        case SYM_GEN_onRemoveFromInventory_416: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_getShopPriority_849: return true;
        case SYM_GEN_getRelatedItems_457: return true;
        case SYM_GEN_getRelatedItemColumns_695: return true;
        case SYM_GEN_getRelatedItemHeight_696: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BagofGiving::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canApplyEffect_916: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemInsideActivated_1957: out = fn_onItemInsideActivated(args, argc); return true;
        case SYM_GEN_onAddToInventory_417: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_416: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_getShopPriority_849: out = fn_getShopPriority(args, argc); return true;
        case SYM_GEN_getRelatedItems_457: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_695: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN_getRelatedItemHeight_696: out = fn_getRelatedItemHeight(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_toItem, SYM_GEN_isClassItem_246, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1450 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_923, nullptr, 0));
        gd::GdArr* _t1451 = (_t1450.kind == gd::GdVal::Kind::Arr) ? _t1450.arr : nullptr;
        uint32_t _len__t1452 = _t1451 ? _t1451->len : 0u;
        for (uint32_t _t1452 = 0; _t1452 < _len__t1452; ++_t1452) {
            gd::GdVal lv_item = _t1451->data[_t1452];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "activated", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onItemInsideActivated", 21u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn_onItemInsideActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_maxStamina, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxStaminaTemporary_314, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn_onAddToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN_onRemoveFromInventory_416, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BagofGiving::fn_getShopPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_852), SYM_GEN_Low_2718);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_maxStamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
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
        case SYM_GEN_manaNeeded_1785: out = this->f_manaNeeded; return true;
        case SYM_GEN_regen_1903: out = this->f_regen; return true;
        case SYM_GEN_spellSpeed_1998: out = this->f_spellSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BookofLight::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaNeeded_1785: this->f_manaNeeded = val; return true;
        case SYM_GEN_regen_1903: this->f_regen = val; return true;
        case SYM_GEN_spellSpeed_1998: this->f_spellSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BookofLight::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BookofLight::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Spell_2606)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofLight::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_speed = gd::GdVal::from_float(0.0);
    {
        gd::GdVal _t1453 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1454 = (_t1453.kind == gd::GdVal::Kind::Arr) ? _t1453.arr : nullptr;
        uint32_t _len__t1455 = _t1454 ? _t1454->len : 0u;
        for (uint32_t _t1455 = 0; _t1455 < _len__t1455; ++_t1455) {
            gd::GdVal lv_item = _t1454->data[_t1455];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Holy_2592)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())) {
                lv_speed = gd::gd_add(gd_ctx, lv_speed, gd::gd_mul(this->f_spellSpeed, gd::GdVal::from_int(2LL)));
            }
            else {
                lv_speed = gd::gd_add(gd_ctx, lv_speed, this->f_spellSpeed);
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_speed}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_271, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofLight::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getMana_1224, nullptr, 0), this->f_manaNeeded)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_330, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_regen, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_212, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, _ca, 2); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofLight::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_manaNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_spellSpeed = gd::gd_div(gd_ctx, gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })()), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_manaNeeded_1785: out = this->f_manaNeeded; return true;
        case SYM_GEN_luck_893: out = this->f_luck; return true;
        case SYM_GEN_empower_994: out = this->f_empower; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__SpiritCompanion::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__CatSpirit::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaNeeded_1785: this->f_manaNeeded = val; return true;
        case SYM_GEN_luck_893: this->f_luck = val; return true;
        case SYM_GEN_empower_994: this->f_empower = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__SpiritCompanion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__CatSpirit::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_playPickupSound_732: return true;
        case SYM_GEN_playDropSound_147: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__SpiritCompanion::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__CatSpirit::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_playPickupSound_732: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_147: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canDamage_87, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CatSpirit::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1456 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1457 = (_t1456.kind == gd::GdVal::Kind::Arr) ? _t1456.arr : nullptr;
        uint32_t _len__t1458 = _t1457 ? _t1457->len : 0u;
        for (uint32_t _t1458 = 0; _t1458 < _len__t1458; ++_t1458) {
            gd::GdVal lv_item = _t1457->data[_t1458];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addCritChancePercent_177, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CatSpirit::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getMana_1224, nullptr, 0), this->f_manaNeeded)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_330, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_luck, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_213, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_empower, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_215, _ca, 2); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CatSpirit::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CatSpirit::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CatSpirit::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__SpiritCompanion::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_manaNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "manat", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
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
        case SYM_GEN_boardSpeed_2062: out = this->f_boardSpeed; return true;
        case SYM_GEN_stamina_2059: out = this->f_stamina; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteKnight::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_boardSpeed_2062: this->f_boardSpeed = val; return true;
        case SYM_GEN_stamina_2059: this->f_stamina = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteKnight::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2049: return true;
        case SYM_GEN_doEliminatedEffect_2051: return true;
        case SYM_GEN_canBeBlocked_1465: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Chess__WhiteKnight::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2049: out = fn_doCapturingEffect(args, argc); return true;
        case SYM_GEN_doEliminatedEffect_2051: out = fn_doEliminatedEffect(args, argc); return true;
        case SYM_GEN_canBeBlocked_1465: out = fn_canBeBlocked(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {this->f_boardSpeed}; return gd::call_method(gd_ctx, this->f_board, SYM_GEN_addSpeed_271, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteKnight::fn_doEliminatedEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__capturingPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_stamina}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxStaminaTemporary_314, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteKnight::fn_canBeBlocked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__WhiteKnight::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_boardSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_stamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
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
        case SYM_GEN_goobertAnimation_932: out = this->f_goobertAnimation; return true;
        case SYM_GEN_regen_1903: out = this->f_regen; return true;
        case SYM_GEN_regenNeeded_938: out = this->f_regenNeeded; return true;
        case SYM_GEN_empower_994: out = this->f_empower; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Cubert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_goobertAnimation_932: this->f_goobertAnimation = val; return true;
        case SYM_GEN_regen_1903: this->f_regen = val; return true;
        case SYM_GEN_regenNeeded_938: this->f_regenNeeded = val; return true;
        case SYM_GEN_empower_994: this->f_empower = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Cubert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_canAffect_secondary_285: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onItemActivated1_2088: return true;
        case SYM_GEN_onItemActivated2_2089: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Cubert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_285: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemActivated1_2088: out = fn_onItemActivated1(args, argc); return true;
        case SYM_GEN_onItemActivated2_2089: out = fn_onItemActivated2(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canActivate_89, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cubert::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canActivate_89, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cubert::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1459 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1460 = (_t1459.kind == gd::GdVal::Kind::Arr) ? _t1459.arr : nullptr;
        uint32_t _len__t1461 = _t1460 ? _t1460->len : 0u;
        for (uint32_t _t1461 = 0; _t1461 < _len__t1461; ++_t1461) {
            gd::GdVal lv_item = _t1460->data[_t1461];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "activated", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onItemActivated1", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
        }
    }
    {
        gd::GdVal _t1462 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Secondary_2582)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, _ca, 1); })());
        gd::GdArr* _t1463 = (_t1462.kind == gd::GdVal::Kind::Arr) ? _t1462.arr : nullptr;
        uint32_t _len__t1464 = _t1463 ? _t1463->len : 0u;
        for (uint32_t _t1464 = 0; _t1464 < _len__t1464; ++_t1464) {
            gd::GdVal lv_item = _t1463->data[_t1464];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "activated", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onItemActivated2", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cubert::fn_onItemActivated1(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_regen, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_212, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cubert::fn_onItemActivated2(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getRegeneration_1213, nullptr, 0), this->f_regenNeeded)))) {
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance2_172, nullptr, 0))) {
            gd::GdVal lv_event2 = ([&]() { gd::GdVal _ca[] = {this->f_regenNeeded, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_344, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_empower, lv_event2}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_215, _ca, 2); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cubert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_212, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getRegeneration_1213, nullptr, 0), this->f_regenNeeded)))) {
        gd::GdVal lv_event2 = ([&]() { gd::GdVal _ca[] = {this->f_regenNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_344, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_empower, lv_event2}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_215, _ca, 2); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Cubert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_regenNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regent", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
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
        case SYM_GEN_counter_2114: out = this->f_counter; return true;
        case SYM_GEN_activationParticles_908: out = this->f_activationParticles; return true;
        case SYM_GEN_heatThreshold_1879: out = this->f_heatThreshold; return true;
        case SYM_GEN_spikeRemoval_2115: out = this->f_spikeRemoval; return true;
        case SYM_GEN_heatPerSpike_2116: out = this->f_heatPerSpike; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DraconicOrb::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_counter_2114: this->f_counter = val; return true;
        case SYM_GEN_activationParticles_908: this->f_activationParticles = val; return true;
        case SYM_GEN_heatThreshold_1879: this->f_heatThreshold = gd::gd_coerce_int(val); return true;
        case SYM_GEN_spikeRemoval_2115: this->f_spikeRemoval = gd::gd_coerce_int(val); return true;
        case SYM_GEN_heatPerSpike_2116: this->f_heatPerSpike = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DraconicOrb::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onHeatChanged_909: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DraconicOrb::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onHeatChanged_909: out = fn_onHeatChanged(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_heat_changed", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onHeatChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DraconicOrb::fn_onHeatChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_counter, this->f_heatThreshold)))) {
        this->f_counter = gd::gd_add(gd_ctx, this->f_counter, lv_amount);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_counter, this->f_heatThreshold)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveCritTokens_312, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DraconicOrb::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_oppoSpikes = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_getSpikes_1203, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_oppoSpikes, gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_spikeRemoval, gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_loseSpikes_336, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::gd_min(lv_oppoSpikes, this->f_spikeRemoval), this->f_heatPerSpike), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 2); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DraconicOrb::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_heatThreshold = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0));
    this->f_spikeRemoval = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0));
    this->f_heatPerSpike = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_264, nullptr, 0));
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
        case SYM_GEN_onCalcTradeChance_1729: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherArmor::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__EmployeeUniform::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCalcTradeChance_1729: out = fn_onCalcTradeChance(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherArmor::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_spikesNeeded_2014: out = this->f_spikesNeeded; return true;
        case SYM_GEN_heatGain_2165: out = this->f_heatGain; return true;
        case SYM_GEN_bonusDamage_900: out = this->f_bonusDamage; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__FlameWhip::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_spikesNeeded_2014: this->f_spikesNeeded = gd::gd_coerce_int(val); return true;
        case SYM_GEN_heatGain_2165: this->f_heatGain = gd::gd_coerce_int(val); return true;
        case SYM_GEN_bonusDamage_900: this->f_bonusDamage = gd::gd_coerce_float(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__FlameWhip::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__FlameWhip::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getSpikes_1203, nullptr, 0), this->f_spikesNeeded)))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_spikesNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useSpikes_335, _ca, 1); })();
            gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1425, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1425), this->f_bonusDamage));
            (void)([&]() { gd::GdVal _ca[] = {this->f_heatGain}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FlameWhip::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_spikesNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_heatGain = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_bonusDamage = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "bonusdam", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
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
        case SYM_GEN_numSpeedboosts_2193: out = this->f_numSpeedboosts; return true;
        case SYM_GEN_curDamageBonus_2194: out = this->f_curDamageBonus; return true;
        case SYM_GEN_maxNumSpeedBoosts_2195: out = this->f_maxNumSpeedBoosts; return true;
        case SYM_GEN_speedBonus_1781: out = this->f_speedBonus; return true;
        case SYM_GEN_damageBonus_2196: out = this->f_damageBonus; return true;
        case SYM_GEN_blind_1815: out = this->f_blind; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Gigawatz::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numSpeedboosts_2193: this->f_numSpeedboosts = gd::gd_coerce_int(val); return true;
        case SYM_GEN_curDamageBonus_2194: this->f_curDamageBonus = gd::gd_coerce_int(val); return true;
        case SYM_GEN_maxNumSpeedBoosts_2195: this->f_maxNumSpeedBoosts = val; return true;
        case SYM_GEN_speedBonus_1781: this->f_speedBonus = val; return true;
        case SYM_GEN_damageBonus_2196: this->f_damageBonus = val; return true;
        case SYM_GEN_blind_1815: this->f_blind = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Gigawatz::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onChargeReceived_2032: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Gigawatz::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onChargeReceived_2032: out = fn_onChargeReceived(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
        (void)([&]() { gd::GdVal _ca[] = {this->f_speedBonus}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_271, _ca, 1); })();
        this->f_numSpeedboosts = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_numSpeedboosts, gd::GdVal::from_int(1LL)));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Gigawatz::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_blind}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_211, _ca, 1); })();
    gd::GdVal lv_dam = gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_minDam_1577), this->f_curDamageBonus);
    gd::GdVal lv_res = ([&]() { gd::GdVal _ca[] = {lv_dam}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealEffectDamage_219, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    this->f_curDamageBonus = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_curDamageBonus, this->f_damageBonus));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Gigawatz::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_maxNumSpeedBoosts = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "max", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_speedBonus = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_damageBonus = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "damincrease", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_blind = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blind", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1457, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Gigawatz(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Gigawatz>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Gigawatz = {CLS_Gd__gd_core_items__Exclusive__Gigawatz, "Gigawatz", "res://gd_core_items/Exclusive/Gigawatz.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Gigawatz, &Gd__gd_core_items__Exclusive__Gigawatz::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Gigawatz::call_static_fn};

void Gd__gd_core_items__Exclusive__Hypercube::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Hypercube::meta() const { return &META_Gd__gd_core_items__Exclusive__Hypercube; }
gd::GdVal Gd__gd_core_items__Exclusive__Hypercube::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Hypercube::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Hypercube::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Hypercube::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Hypercube::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onDropped_1938: return true;
        case SYM_GEN_replaceWithCubes_2216: return true;
        case SYM_GEN_getTextureSize_777: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Hypercube::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onDropped_1938: out = fn_onDropped(args, argc); return true;
        case SYM_GEN_replaceWithCubes_2216: out = fn_replaceWithCubes(args, argc); return true;
        case SYM_GEN_getTextureSize_777: out = fn_getTextureSize(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Hypercube::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Hypercube::fn_onDropped(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_dropRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_dropRes}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core_items__Exclusive__Hypercube::call_static_fn(gd_ctx, SYM_GEN_wasAddedToInventory_655, _ca, 1, _out); return _out; })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Hypercube::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_861), SYM_GEN_AddedToStorageBox_2626)))))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_prepareReplacement_444, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "replaceWithCubes", 16u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_dropRes}))}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_defer_1418, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Hypercube::fn_replaceWithCubes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_dropResult = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Hypercube::fn_getTextureSize(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Hypercube::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dropped", 7u)), gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDropped", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_connect, _ca, 3); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Hypercube(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Hypercube>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Hypercube = {CLS_Gd__gd_core_items__Exclusive__Hypercube, "Hypercube", "res://gd_core_items/Exclusive/Hypercube.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Hypercube, &Gd__gd_core_items__Exclusive__Hypercube::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Hypercube::call_static_fn};

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
        case SYM_GEN_params_1477: return ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 15); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luckt", 5u)), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heatt", 5u)), gd::GdVal::from_int(4LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat_bonus", 10u)), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat", 4u)), gd::GdVal::from_int(4LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikest", 7u)), gd::GdVal::from_int(6LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes_bonus", 12u)), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u)), gd::GdVal::from_int(8LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regent", 6u)), gd::GdVal::from_int(8LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen_bonus", 11u)), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u)), gd::GdVal::from_int(10LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "vampirism", 9u)), gd::GdVal::from_int(12LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "vamp_bonus", 10u)), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "vampt", 5u)), gd::GdVal::from_int(10LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower_bonus", 13u)), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u)), gd::GdVal::from_int(14LL)); return gd::GdVal::from_dict(d); })();
        case SYM_GEN_flashColor_2244: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.3), gd::GdVal::from_float(1.3), gd::GdVal::from_float(1.3)}; return gd::make_color_from_args(_ca, 3); })();
        case SYM_GEN_DUR_2245: return gd::GdVal::from_float(0.2);
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
        case SYM_GEN_phase_2212: out = this->f_phase; return true;
        case SYM_GEN_typesDict_1972: out = this->f_typesDict; return true;
        case SYM_GEN_fluidTween_1743: out = this->f_fluidTween; return true;
        case SYM_GEN_fluid_1745: out = this->f_fluid; return true;
        case SYM_GEN_fluidMat_2246: out = this->f_fluidMat; return true;
        case SYM_GEN_params_1477: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_flashColor_2244: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_DUR_2245: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Laboratory::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_phase_2212: this->f_phase = gd::gd_coerce_int(val); return true;
        case SYM_GEN_typesDict_1972: this->f_typesDict = val; return true;
        case SYM_GEN_fluidTween_1743: this->f_fluidTween = val; return true;
        case SYM_GEN_fluid_1745: this->f_fluid = val; return true;
        case SYM_GEN_fluidMat_2246: this->f_fluidMat = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Laboratory::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_getDescription_638: return true;
        case SYM_GEN_onPreCombatStart_123: return true;
        case SYM_GEN_trigger_141: return true;
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN_switchGradient_2247: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Laboratory::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_getDescription_638: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_onPreCombatStart_123: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_trigger_141: out = fn_trigger(args, argc); return true;
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_switchGradient_2247: out = fn_switchGradient(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Laboratory::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_int(1LL))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = gd::call_method(gd_ctx, this->f_descriptor, SYM_GEN_getDescription_638, nullptr, 0);
    {
        gd::GdVal _t1465 = gd::gd_iter_seq(gd_ctx.arena, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1477));
        gd::GdArr* _t1466 = (_t1465.kind == gd::GdVal::Kind::Arr) ? _t1465.arr : nullptr;
        uint32_t _len__t1467 = _t1466 ? _t1466->len : 0u;
        for (uint32_t _t1467 = 0; _t1467 < _len__t1467; ++_t1467) {
            gd::GdVal lv_param = _t1466->data[_t1467];
            lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "p_", 2u)), lv_param}; return gd::gd_str_fn(gd_ctx.arena, _ca, 2); })(), gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1477), lv_param), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_860), SYM_GEN_No_2547), gd::GdVal::from_bool(false), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_640, _ca, 6); })();
        }
    }
    return ([&]() { gd::GdVal _ca[] = {lv_descr, lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameters_639, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    this->f_typesDict = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countTypes_493, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::fn_trigger(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_phase, gd::GdVal::from_int(1LL))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_trigger_141, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth((gd::gd_truth((gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Fire_2599)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Nature_2596)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Holy_2592)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Vampiric_2597)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Classes_Full_1369), SYM_GEN_Engineer_2684)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isClassItem_246, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_phase, gd::GdVal::from_int(1LL))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getLucky_1217, nullptr, 0), gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1477), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luckt", 5u))))))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1477), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luckt", 5u)))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useLucky_348, _ca, 1); })();
            gd::GdVal lv_numFire = gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Fire_2599));
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1477), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat", 4u))), gd::gd_mul(lv_numFire, gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1477), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat_bonus", 10u))))), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 2); })();
        }
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_phase, gd::GdVal::from_int(2LL))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getHeat_1231, nullptr, 0), gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1477), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heatt", 5u))))))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1477), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heatt", 5u)))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useHeat_352, _ca, 1); })();
            gd::GdVal lv_numNature = gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Nature_2596));
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1477), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u))), gd::gd_mul(lv_numNature, gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1477), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes_bonus", 12u))))), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_207, _ca, 2); })();
        }
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_phase, gd::GdVal::from_int(3LL))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getSpikes_1203, nullptr, 0), gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1477), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikest", 7u))))))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1477), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikest", 7u)))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useSpikes_335, _ca, 1); })();
            gd::GdVal lv_numHoly = gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Holy_2592));
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1477), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))), gd::gd_mul(lv_numHoly, gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1477), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen_bonus", 11u))))), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_212, _ca, 2); })();
        }
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_phase, gd::GdVal::from_int(4LL))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getRegeneration_1213, nullptr, 0), gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1477), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regent", 6u))))))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1477), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regent", 6u)))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_344, _ca, 1); })();
            gd::GdVal lv_numVamp = gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Vampiric_2597));
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1477), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "vampirism", 9u))), gd::gd_mul(lv_numVamp, gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1477), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "vamp_bonus", 10u))))), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_208, _ca, 2); })();
        }
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_phase, gd::GdVal::from_int(5LL))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getVampirism_1206, nullptr, 0), gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1477), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "vampt", 5u))))))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1477), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "vampt", 5u)))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useVampirism_338, _ca, 1); })();
            gd::GdVal lv_numEngineer = gd::GdVal::from_int(0LL);
            {
                gd::GdVal _t1468 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
                gd::GdArr* _t1469 = (_t1468.kind == gd::GdVal::Kind::Arr) ? _t1468.arr : nullptr;
                uint32_t _len__t1470 = _t1469 ? _t1469->len : 0u;
                for (uint32_t _t1470 = 0; _t1470 < _len__t1470; ++_t1470) {
                    gd::GdVal lv_item = _t1469->data[_t1470];
                    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Classes_Full_1369), SYM_GEN_Engineer_2684)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isClassItem_246, _ca, 1); })())) {
                        lv_numEngineer = gd::gd_add(gd_ctx, lv_numEngineer, gd::GdVal::from_int(1LL));
                    }
                }
            }
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1477), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))), gd::gd_mul(lv_numEngineer, gd::get_index(gd_ctx, Gd__gd_core_items__Exclusive__Laboratory::get_static_const_or_enum(gd_ctx, SYM_GEN_params_1477), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower_bonus", 13u))))), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_215, _ca, 2); })();
        }
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_phase, gd::GdVal::from_int(5LL))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_143, nullptr, 0);
    }
    else {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__phase = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv__phase = gd::gd_coerce_int(lv__phase);
    this->f_phase = gd::gd_coerce_int(lv__phase);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(this->f_phase, gd::GdVal::from_int(0LL))))) {
        this->f_baseCooldownOverride = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldownIndex_99, _ca, 1); })());
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_phase, gd::GdVal::from_int(5LL))))) {
        this->f_baseCooldownOverride = gd::gd_coerce_float(gd::gd_sub(([&]() { gd::GdVal _ca[] = {this->f_phase}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldownIndex_99, _ca, 1); })(), ([&]() { gd::GdVal _ca[] = {gd::gd_sub(this->f_phase, gd::GdVal::from_int(1LL))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldownIndex_99, _ca, 1); })()));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::fn_switchGradient(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Laboratory::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_phase = gd::gd_coerce_int(gd::gd_neg(gd::GdVal::from_int(1LL)));
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_switchGradient_2247, nullptr, 0);
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
        case SYM_GEN_triggerType_2291: out = this->f_triggerType; return true;
        case SYM_GEN_stackType_2292: out = this->f_stackType; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_triggerType_2291: this->f_triggerType = gd::gd_coerce_int(val); return true;
        case SYM_GEN_stackType_2292: this->f_stackType = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_pushEncoded_2293: return true;
        case SYM_GEN_setFromEncoded_2294: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_pushEncoded_2293: out = fn_pushEncoded(args, argc); return true;
        case SYM_GEN_setFromEncoded_2294: out = fn_setFromEncoded(args, argc); return true;
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
    gd::GdVal lv_normalizedStack = gd::gd_sub(this->f_stackType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Lucky_2569));
    (void)([&]() { gd::GdVal _ca[] = {this->f_triggerType, gd::call_method(gd_ctx, Gd__gd_core_items__Exclusive__MagicRing::get_static_const_or_enum(gd_ctx, SYM_GEN_TriggerType_2289), gd::SYM_size, nullptr, 0)}; return gd::call_method(gd_ctx, lv_bitStream, SYM_GEN_push_2775, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_normalizedStack, gd::GdVal::from_int(16LL)}; return gd::call_method(gd_ctx, lv_bitStream, SYM_GEN_push_2775, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect::fn_setFromEncoded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_bitStream = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_triggerType = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, Gd__gd_core_items__Exclusive__MagicRing::get_static_const_or_enum(gd_ctx, SYM_GEN_TriggerType_2289), gd::SYM_size, nullptr, 0)}; return gd::call_method(gd_ctx, lv_bitStream, SYM_GEN_pull_2776, _ca, 1); })());
    this->f_stackType = gd::gd_coerce_int(gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(16LL)}; return gd::call_method(gd_ctx, lv_bitStream, SYM_GEN_pull_2776, _ca, 1); })(), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Lucky_2569)));
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
        case SYM_GEN_activationParticles_908: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MrsStruggles::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activationParticles_908: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MrsStruggles::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MrsStruggles::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Dark_2600)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MrsStruggles::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_271, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MrsStruggles::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1471 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1357, nullptr, 0));
        gd::GdArr* _t1472 = (_t1471.kind == gd::GdVal::Kind::Arr) ? _t1471.arr : nullptr;
        uint32_t _len__t1473 = _t1472 ? _t1472->len : 0u;
        for (uint32_t _t1473 = 0; _t1473 < _len__t1473; ++_t1473) {
            gd::GdVal lv_buff = _t1472->data[_t1473];
            (void)([&]() { gd::GdVal _ca[] = {lv_buff, gd::GdVal::from_int(1LL), gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_loseStacks_1027, _ca, 3); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MrsStruggles::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_spikes_894: out = this->f_spikes; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Cube::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PlasticCube::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_spikes_894: this->f_spikes = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Cube::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PlasticCube::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Cube::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PlasticCube::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_93, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PlasticCube::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_deactivateCooldown_97, nullptr, 0);
    gd::GdVal lv_affectedItem = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getFirstAffectedItem_426, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_affectedItem, gd::GdVal::null())))) {
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_affectedItem, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_cube_advanced_1393)))))) {
            { gd::GdVal _t1474 = gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_cube_advanced_1393); gd::GdVal _t1475 = lv_affectedItem; gd::set_index(gd_ctx, _t1474, _t1475, gd::GdVal::from_obj(this)); }
            (void)([&]() { gd::GdVal _ca[] = {this->f_cdAdvance}; return gd::call_method(gd_ctx, lv_affectedItem, SYM_GEN_advanceCooldownPercent_144, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_cdAdvance, this->f_penaltyFactor)}; return gd::call_method(gd_ctx, lv_affectedItem, SYM_GEN_advanceCooldownPercent_144, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {this->f_spikes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_207, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_143, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PlasticCube::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Cube::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
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
        case SYM_GEN_canApplyEffect_916: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagZ::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canApplyEffect_916: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_toItem, SYM_GEN_inflictsDebuffs_296, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagZ::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1476 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_923, nullptr, 0));
        gd::GdArr* _t1477 = (_t1476.kind == gd::GdVal::Kind::Arr) ? _t1476.arr : nullptr;
        uint32_t _len__t1478 = _t1477 ? _t1477->len : 0u;
        for (uint32_t _t1478 = 0; _t1478 < _len__t1478; ++_t1478) {
            gd::GdVal lv_item = _t1477->data[_t1478];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_allDebuffs_196, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagZ::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_heatThreshold_1879: out = this->f_heatThreshold; return true;
        case SYM_GEN_heat_1800: out = this->f_heat; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Resistor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_heatThreshold_1879: this->f_heatThreshold = val; return true;
        case SYM_GEN_heat_1800: this->f_heat = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Resistor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onChargeReceived_2032: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Resistor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onChargeReceived_2032: out = fn_onChargeReceived(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getHeat_1231, nullptr, 0), this->f_heatThreshold)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Resistor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_heatThreshold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heatt", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
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
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ShepherdsCrook::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_88, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShepherdsCrook::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeBuffProtectionChance_1266, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Blind_2567), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_170, nullptr, 0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeResistChance_1021, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Cold_2573), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_170, nullptr, 0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeResistChance_1021, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShepherdsCrook::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1479 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1480 = (_t1479.kind == gd::GdVal::Kind::Arr) ? _t1479.arr : nullptr;
        uint32_t _len__t1481 = _t1480 ? _t1480->len : 0u;
        for (uint32_t _t1481 = 0; _t1481 < _len__t1481; ++_t1481) {
            gd::GdVal lv_item = _t1480->data[_t1481];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_159, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ShepherdsCrook::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ShepherdsCrook(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ShepherdsCrook>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ShepherdsCrook = {CLS_Gd__gd_core_items__Exclusive__ShepherdsCrook, "ShepherdsCrook", "res://gd_core_items/Exclusive/ShepherdsCrook.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__ShepherdsCrook, &Gd__gd_core_items__Exclusive__ShepherdsCrook::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ShepherdsCrook::call_static_fn};

void Gd__gd_core_items__Exclusive__SnowStick::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_cold = gd::GdVal::null();
    this->f_selfCold = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SnowStick::meta() const { return &META_Gd__gd_core_items__Exclusive__SnowStick; }
gd::GdVal Gd__gd_core_items__Exclusive__SnowStick::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SnowStick::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SnowStick::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_cold_1949: out = this->f_cold; return true;
        case SYM_GEN_selfCold_2421: out = this->f_selfCold; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SnowStick::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_cold_1949: this->f_cold = val; return true;
        case SYM_GEN_selfCold_2421: this->f_selfCold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SnowStick::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SnowStick::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SnowStick::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SnowStick::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_cold}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_349, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Cold_2573), this->f_selfCold}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_199, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SnowStick::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_cold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cold", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_selfCold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cold2", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SnowStick(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SnowStick>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SnowStick = {CLS_Gd__gd_core_items__Exclusive__SnowStick, "SnowStick", "res://gd_core_items/Exclusive/SnowStick.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__SnowStick, &Gd__gd_core_items__Exclusive__SnowStick::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SnowStick::call_static_fn};

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
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Squirrel::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SquirrelArcher::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealRandomBuff_371, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SquirrelArcher::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_114, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StaminaResult_1276), SYM_GEN_Sufficient_2603))))) {
        gd::GdVal lv_res = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_218, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SquirrelArcher::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Squirrel::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1457, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SquirrelArcher(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SquirrelArcher>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SquirrelArcher = {CLS_Gd__gd_core_items__Exclusive__SquirrelArcher, "SquirrelArcher", "res://gd_core_items/Exclusive/SquirrelArcher.gd", &META_Gd__gd_core_items__Exclusive__Squirrel, true, _alloc_Gd__gd_core_items__Exclusive__SquirrelArcher, &Gd__gd_core_items__Exclusive__SquirrelArcher::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SquirrelArcher::call_static_fn};

void Gd__gd_core_items__Exclusive__Thornbloom::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_spikes = gd::GdVal::from_int(0);
    this->f_empower = gd::GdVal::from_int(0);
    this->f_damPerSpike = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Thornbloom::meta() const { return &META_Gd__gd_core_items__Exclusive__Thornbloom; }
gd::GdVal Gd__gd_core_items__Exclusive__Thornbloom::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Thornbloom::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Thornbloom::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_spikes_894: out = this->f_spikes; return true;
        case SYM_GEN_empower_994: out = this->f_empower; return true;
        case SYM_GEN_damPerSpike_2486: out = this->f_damPerSpike; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Thornbloom::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_spikes_894: this->f_spikes = gd::gd_coerce_int(val); return true;
        case SYM_GEN_empower_994: this->f_empower = gd::gd_coerce_int(val); return true;
        case SYM_GEN_damPerSpike_2486: this->f_damPerSpike = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Thornbloom::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onSpikesChanged_940: return true;
        case SYM_GEN_onEmpowerChanged_2017: return true;
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Thornbloom::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onSpikesChanged_940: out = fn_onSpikesChanged(args, argc); return true;
        case SYM_GEN_onEmpowerChanged_2017: out = fn_onEmpowerChanged(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Thornbloom::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Thornbloom::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_empower_changed", 25u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onEmpowerChanged", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_spikes_changed", 24u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onSpikesChanged", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Thornbloom::fn_onSpikesChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_damPerSpike, lv_amount)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_160, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Thornbloom::fn_onEmpowerChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), lv_amount), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_315, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Thornbloom::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_spikes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_207, _ca, 1); })();
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_empower}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_215, _ca, 1); })();
        }
        else {
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Thornbloom::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_damPerSpike = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "damperspike", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Thornbloom(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Thornbloom>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Thornbloom = {CLS_Gd__gd_core_items__Exclusive__Thornbloom, "Thornbloom", "res://gd_core_items/Exclusive/Thornbloom.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__Thornbloom, &Gd__gd_core_items__Exclusive__Thornbloom::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Thornbloom::call_static_fn};

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
        case SYM_GEN_typesDict_1972: out = this->f_typesDict; return true;
        case SYM_GEN_speedPerSpell_2504: out = this->f_speedPerSpell; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Ultima::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_typesDict_1972: this->f_typesDict = val; return true;
        case SYM_GEN_speedPerSpell_2504: this->f_speedPerSpell = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Ultima::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_getDescription_638: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Ultima::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getDescription_638: out = fn_getDescription(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return (gd::gd_truth((gd::gd_truth((gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Nature_2596)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Ice_2722)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Holy_2592)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Dark_2600)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Spell_2606)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Ultima::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_typesDict = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countTypes_493, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Spell_2606)), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_speedPerSpell, gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Spell_2606)))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_271, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Ultima::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Nature_2596)), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Nature_2596)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_213, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Nature_2596)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_207, _ca, 1); })();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Ice_2722)), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Ice_2722)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_202, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Ice_2722)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cold", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_349, _ca, 1); })();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Holy_2592)), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Holy_2592)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_212, _ca, 1); })();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Dark_2600)), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Dark_2600))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealRandomBuff_371, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_143, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Ultima::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getDescription_638, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_placed)))) {
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$n_nature", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$n_ice", 6u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$n_holy", 7u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$n_dark", 7u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        return lv_descr;
    }
    this->f_typesDict = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countTypes_493, _ca, 1); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "n_nature", 8u)), gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Nature_2596))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_450, _ca, 3); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "n_ice", 5u)), gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Ice_2722))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_450, _ca, 3); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "n_holy", 6u)), gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Holy_2592))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_450, _ca, 3); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "n_dark", 6u)), gd::get_index(gd_ctx, this->f_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Dark_2600))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_450, _ca, 3); })();
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Ultima::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_speedPerSpell = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_getCraftingOffset_846: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__FalconBlade::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getCraftingOffset_846: out = fn_getCraftingOffset(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_93, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__FalconBlade::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1482 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1483 = (_t1482.kind == gd::GdVal::Kind::Arr) ? _t1482.arr : nullptr;
        uint32_t _len__t1484 = _t1483 ? _t1483->len : 0u;
        for (uint32_t _t1484 = 0; _t1484 < _len__t1484; ++_t1484) {
            gd::GdVal lv_item = _t1483->data[_t1484];
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0), gd::GdVal::from_int(100LL))}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_271, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__FalconBlade::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_114, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StaminaResult_1276), SYM_GEN_Sufficient_2603))))) {
        gd::GdVal lv_res = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_218, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, _ca, 2); })();
        gd::GdVal lv_res2 = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_218, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res2, gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, _ca, 2); })();
        gd::GdVal lv_hits = gd::GdVal::from_int(0LL);
        if (gd::gd_truth(gd::call_method(gd_ctx, lv_res, SYM_GEN_hasHit_1430, nullptr, 0))) {
            lv_hits = gd::gd_add(gd_ctx, lv_hits, gd::GdVal::from_int(1LL));
        }
        if (gd::gd_truth(gd::call_method(gd_ctx, lv_res2, SYM_GEN_hasHit_1430, nullptr, 0))) {
            lv_hits = gd::gd_add(gd_ctx, lv_hits, gd::GdVal::from_int(1LL));
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(30.0)), gd::GdVal::from_float(30.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), SYM_GEN_bare_randf_range_1645, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(100.0)), gd::GdVal::from_float(100.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), SYM_GEN_bare_randf_range_1645, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(5.0)), gd::GdVal::from_float(5.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1373), SYM_GEN_bare_randf_range_1645, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__FalconBlade::fn_getCraftingOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t1485 = lv_forDirection;
        if (gd::gd_eq(_t1485, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_UP))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
        else if (gd::gd_eq(_t1485, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_DOWN))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
        else if (gd::gd_eq(_t1485, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_LEFT))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
        else if (gd::gd_eq(_t1485, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_859), gd::SYM_RIGHT))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__FalconBlade::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_bonusSpeed_1786: out = this->f_bonusSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__GlovesofHaste::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bonusSpeed_1786: this->f_bonusSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__GlovesofHaste::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__GlovesofHaste::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_93, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__GlovesofHaste::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1486 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1487 = (_t1486.kind == gd::GdVal::Kind::Arr) ? _t1486.arr : nullptr;
        uint32_t _len__t1488 = _t1487 ? _t1487->len : 0u;
        for (uint32_t _t1488 = 0; _t1488 < _len__t1488; ++_t1488) {
            gd::GdVal lv_item = _t1487->data[_t1488];
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_271, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__GlovesofHaste::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_bonusSpeed = gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0), gd::GdVal::from_int(100LL));
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
        case SYM_GEN_extraAttack_1821: out = this->f_extraAttack; return true;
        default: break;
    }
    return Gd__gd_core_items__Bow::get_prop(prop, out);
}
bool Gd__gd_core_items__LuckyBow::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_extraAttack_1821: this->f_extraAttack = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Bow::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__LuckyBow::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onWeaponAttacked_946: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Bow::has_own_method(m);
}
bool Gd__gd_core_items__LuckyBow::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onWeaponAttacked_946: out = fn_onWeaponAttacked(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Bow::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__LuckyBow::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Bow::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__LuckyBow::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyBow::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_213, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyBow::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_114, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StaminaResult_1276), SYM_GEN_Sufficient_2603))))) {
        gd::GdVal lv_res = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_218, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, _ca, 1); })();
        if (gd::gd_truth(this->f_extraAttack)) {
            gd::GdVal lv_res2 = ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, lv_res, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_218, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_res2}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false), gd::GdVal::from_bool(false), gd::get_prop(gd_ctx, lv_res2, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyBow::fn_onWeaponAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_wasCriticalHit_1431, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(false), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__LuckyBow::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bow::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_poison_1866: out = this->f_poison; return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::get_prop(prop, out);
}
bool Gd__gd_core_items__PoisonDagger::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_poison_1866: this->f_poison = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__PoisonDagger::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::has_own_method(m);
}
bool Gd__gd_core_items__PoisonDagger::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_poison}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_209, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PoisonDagger::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Dagger::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_poison = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0));
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
        case SYM_GEN_buffActive_1717: out = this->f_buffActive; return true;
        case SYM_GEN_activationParticles_908: out = this->f_activationParticles; return true;
        case SYM_GEN_unhealingTimer_1888: out = this->f_unhealingTimer; return true;
        case SYM_GEN_manaCost_1719: out = this->f_manaCost; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__StaffofUnhealing::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffActive_1717: this->f_buffActive = val; return true;
        case SYM_GEN_activationParticles_908: this->f_activationParticles = val; return true;
        case SYM_GEN_unhealingTimer_1888: this->f_unhealingTimer = val; return true;
        case SYM_GEN_manaCost_1719: this->f_manaCost = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__StaffofUnhealing::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_buffEnded_1721: return true;
        case SYM_GEN_onCombatEnd_130: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__StaffofUnhealing::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_buffEnded_1721: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_onCombatEnd_130: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__StaffofUnhealing::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__StaffofUnhealing::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StaffofUnhealing::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_114, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StaminaResult_1276), SYM_GEN_Sufficient_2603))))) {
        gd::GdVal lv_healAmount = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getMana_1224, nullptr, 0), this->f_manaCost)))) {
            if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_buffActive)))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 2); })();
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_giveUnhealing_1158, _ca, 1); })();
            }
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_unhealing", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })()}; return gd::call_method(gd_ctx, this->f_unhealingTimer, SYM_GEN_start_1683, _ca, 1); })();
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_330, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_healAmount, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, _ca, 2); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {lv_healAmount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, _ca, 1); })();
        }
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StaffofUnhealing::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_reduceUnhealing_1159, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StaffofUnhealing::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_unhealingTimer, SYM_GEN_stop_1684, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StaffofUnhealing::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_unhealingTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "UnhealingTimer", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffEnded", 9u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_133, _ca, 3); })();
    this->f_manaCost = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0);
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
        case SYM_GEN_lastSpeedBonus_998: out = this->f_lastSpeedBonus; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__VampiricScythe::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_lastSpeedBonus_998: this->f_lastSpeedBonus = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__VampiricScythe::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onVampirismChanged_939: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__VampiricScythe::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onVampirismChanged_939: out = fn_onVampirismChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Stack_855), SYM_GEN_Vampirism_2565)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_gainsStack_84, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__VampiricScythe::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1489 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1490 = (_t1489.kind == gd::GdVal::Kind::Arr) ? _t1489.arr : nullptr;
        uint32_t _len__t1491 = _t1490 ? _t1490->len : 0u;
        for (uint32_t _t1491 = 0; _t1491 < _len__t1491; ++_t1491) {
            gd::GdVal lv_item = _t1490->data[_t1491];
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Vampirism_2565), gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_giveBuffPower_301, _ca, 2); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_vampirism_changed", 27u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onVampirismChanged", 18u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__VampiricScythe::fn_onVampirismChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_scytheSpeedBonus = gd::gd_min(gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0), gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getVampirism_1206, nullptr, 0)), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0));
    lv_scytheSpeedBonus = gd::gd_div(gd_ctx, lv_scytheSpeedBonus, gd::GdVal::from_float(100.0));
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_sub(lv_scytheSpeedBonus, this->f_lastSpeedBonus)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_271, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__VampiricScythe(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__VampiricScythe>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__VampiricScythe = {CLS_Gd__gd_core_items__VampiricScythe, "VampiricScythe", "res://gd_core_items/VampiricScythe.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__VampiricScythe, &Gd__gd_core_items__VampiricScythe::get_static_prop_fn, &Gd__gd_core_items__VampiricScythe::call_static_fn};
