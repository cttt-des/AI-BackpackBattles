#pragma once
#pragma STDC FP_CONTRACT OFF
#include "Gd__gd_core_items__Item.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core_items__Exclusive__SpintoWin : public Gd__gd_core_items__Item {
    explicit Gd__gd_core_items__Exclusive__SpintoWin(gd::BattleCtx* ctx) : Gd__gd_core_items__Item(ctx) {}
    gd::GdVal f_heat;
    gd::GdVal f_luck;
    gd::GdVal f_regen;
    gd::GdVal f_mana;
    gd::GdVal f_frame;
    gd::GdVal f_skillLight;
    gd::GdVal fn_ready_deferred(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_updateColor(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getDescription(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_doCooldownEffect(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_gainsStack(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_rotateTo(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_setFaceDirectionInstant(const gd::GdVal* _args, int _argc);
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
