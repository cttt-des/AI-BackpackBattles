#pragma once
#pragma STDC FP_CONTRACT OFF
#include "Gd__gd_core_items__Item.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core_items__Potion : public Gd__gd_core_items__Item {
    explicit Gd__gd_core_items__Potion(gd::BattleCtx* ctx) : Gd__gd_core_items__Item(ctx) {}
    gd::GdVal f_potionColor;
    gd::GdVal f_fluidTween;
    gd::GdVal f_isFull;
    gd::GdVal f_connector;
    gd::GdVal f_fluid;
    gd::GdVal f_fluidGradientTex;
    gd::GdVal f_fluidGradient;
    gd::GdVal f_baseFoaminess;
    gd::GdVal f_baseScroll;
    gd::GdVal f_baseLevel;
    gd::GdVal fn_prepare(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_canAffect(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_isEmpty(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_fill(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_empty(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_drink(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_consumePotion(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onTriggerPotion(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_triggerPotion(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onStateChanged(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_activate(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_shopEntered(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getAffectedCellsAfterRotate_primary(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_addToInventory(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onFusingAsIngredient(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onAffectedItemAdded(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onAffectedItemRemoved(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_updateConnector(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_resetGradient(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_discard(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getStarPosition(const gd::GdVal* _args, int _argc);
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
