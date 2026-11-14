#pragma once
#pragma STDC FP_CONTRACT OFF
#include "../../gd_rt.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core__CoreGrid : public gd::GdObj {
    explicit Gd__gd_core__CoreGrid(gd::BattleCtx* ctx) : gd::GdObj(ctx) {}
    gd::GdVal f_filledCells;
    gd::GdVal f_bagCells;
    gd::GdVal f_items;
    gd::GdVal f_character;
    gd::GdVal f_curHovered;
    gd::GdVal fn__init(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getCellsForGlobalPositions(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getItems(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getItemsAndGems(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_isHovered(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_isCellEmpty(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getEmptyCellsInCells(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getItemInCell(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getItemsInCells(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_countItemsInCells(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getBagsInCells(const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_getCellsInLine(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_getAdjacentCells(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getAdjacentItems(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_countSocketedGems(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_changeBuffPower_allItems(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_changeBuffAmplification_allItems(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_addItemCells(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_addItem(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_removeItem(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_clearItemCells(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_moveItem(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onItemTypeChanged(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_cleanUp(const gd::GdVal* _args, int _argc);
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
