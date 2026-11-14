#pragma once
#pragma STDC FP_CONTRACT OFF
#include "Gd__gd_core_items__Stone.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core__ArtifactStoneCold : public Gd__gd_core_items__Stone {
    explicit Gd__gd_core__ArtifactStoneCold(gd::BattleCtx* ctx) : Gd__gd_core_items__Stone(ctx) {}
    gd::GdVal fn_canAffect(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onPrepare(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onAffectedWeaponAttacked(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_preHit(const gd::GdVal* _args, int _argc);
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
