#pragma once
#pragma STDC FP_CONTRACT OFF
#include "../../gd_rt.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core__CoreRng__INNER__BalancedRng : public gd::GdObj {
    explicit Gd__gd_core__CoreRng__INNER__BalancedRng(gd::BattleCtx* ctx) : gd::GdObj(ctx) {}
    gd::GdVal f_expectedWins;
    gd::GdVal f_wins;
    gd::GdVal f_balancedness;
    gd::GdVal f_lastResult;
    gd::GdVal f_extraLuck;
    gd::GdVal f_lastTarget;
    gd::GdVal f_accChance;
    gd::GdVal f__rng;
    gd::GdVal fn__init(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_setBias(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_rollPercent(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_roll(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_roll2(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_roll1(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_reset(const gd::GdVal* _args, int _argc);
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
