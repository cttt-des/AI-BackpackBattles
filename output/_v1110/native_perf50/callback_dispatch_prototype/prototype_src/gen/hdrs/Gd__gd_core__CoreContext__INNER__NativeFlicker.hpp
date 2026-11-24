#pragma once
#pragma STDC FP_CONTRACT OFF
#include "../../gd_rt.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core__CoreContext__INNER__NativeFlicker : public gd::GdObj {
    explicit Gd__gd_core__CoreContext__INNER__NativeFlicker(gd::BattleCtx* ctx) : gd::GdObj(ctx) {}
    gd::GdVal f_ctx;
    gd::GdVal f_limits;
    gd::GdVal f_position;
    gd::GdVal f_speed;
    gd::GdVal f_length;
    gd::GdVal f_playing;
    gd::GdVal f_inside_tree;
    gd::GdVal f_loop;
    gd::GdVal fn_playAni(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_tick(const gd::GdVal* _args, int _argc);
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
