#pragma once
#pragma STDC FP_CONTRACT OFF
#include "../../gd_rt.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core__CoreItemBook : public gd::GdObj {
    explicit Gd__gd_core__CoreItemBook(gd::BattleCtx* ctx) : gd::GdObj(ctx) {}
    gd::GdVal f_descriptors;
    gd::GdVal f__ctx;
    gd::GdVal fn__init(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getDescriptor(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_hasDescriptor(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_register(const gd::GdVal* _args, int _argc);
    gd::GdVal fn__sideItems(const gd::GdVal* _args, int _argc);
    gd::GdVal fn__inventorySide(const gd::GdVal* _args, int _argc);
    gd::GdVal fn__filter(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getItemsInInventoryOfType(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getItemsInInventoryOfType_opponent(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_countItemsInInventoryOfType(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_countItemsInInventoryOfType_opponent(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_countPlacedItemsInInventoryOfType(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_isItemInInventory(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_isItemInInventory_opponent(const gd::GdVal* _args, int _argc);
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
