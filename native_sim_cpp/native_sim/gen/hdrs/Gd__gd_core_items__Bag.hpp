#pragma once
#pragma STDC FP_CONTRACT OFF
#include "Gd__gd_core_items__Item.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core_items__Bag : public Gd__gd_core_items__Item {
    explicit Gd__gd_core_items__Bag(gd::BattleCtx* ctx) : Gd__gd_core_items__Item(ctx) {}
    gd::GdVal f_bagTilemapPosition;
    gd::GdVal f_cachedAffectedInsideItems;
    gd::GdVal f_cachedInsideItems;
    gd::GdVal f_bagTilemap;
    gd::GdVal f_border;
    gd::GdVal fn_getHoverPriority(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_isBag(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_showBagBorderForItem(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_canApplyEffect(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_canBePicked(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_canBeLocked(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_resetZ(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_addToInventory(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getBagLayerPriority(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_hasBagEffect(const gd::GdVal* _args, int _argc);
    gd::GdVal fn__process(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_reactToDropResult(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getTopLeftGlobal(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getBottomRightGlobal(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_isEmpty(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getItemsInside(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getEmptyCells(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getEmptyGlobalPositions(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getAffectedItemsInside(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_previewCanAffect(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_prepare(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_combatToShop(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getCraftableNeighbors(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onItemAdded(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onAffectedItemInsideAdded(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onItemRemoved(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onAffectedItemInsideRemoved(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_pushItemsInsideToStorage(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onDraggedWithParentStart(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onDraggedWithParentEnd(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getNumAffectedInside(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getNumAffectedInside_type(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getBagMultiplicity(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_discard(const gd::GdVal* _args, int _argc);
    gd::GdVal fn__readyInit(const gd::GdVal* _args, int _argc);
    const gd::GdClassMeta* meta() const override;
    void init_fields(gd::BattleCtx& gd_ctx) override;
    bool get_prop(gd::SymId prop, gd::GdVal& out) const override;
    bool set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) override;
    bool has_own_method(gd::SymId m) const override;
    bool call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) override;
    static gd::GdVal get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop);
    static bool get_static_prop_fn(gd::SymId prop, gd::GdVal& out);
    static bool call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out);
};
