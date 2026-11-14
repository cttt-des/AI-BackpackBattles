#pragma once
#pragma STDC FP_CONTRACT OFF
#include "../../gd_rt.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core__CoreConst : public gd::GdObj {
    explicit Gd__gd_core__CoreConst(gd::BattleCtx* ctx) : gd::GdObj(ctx) {}
    static gd::GdVal sf_truth(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_getStacks(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_getBuffs(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_getDebuffs(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_isBuff(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_isDebuff(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_isStack(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    static gd::GdVal sf_numStackTypes(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
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
