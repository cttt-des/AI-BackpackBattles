#pragma once
#pragma STDC FP_CONTRACT OFF
#include "../../gd_rt.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core__CoreRng : public gd::GdObj {
    explicit Gd__gd_core__CoreRng(gd::BattleCtx* ctx) : gd::GdObj(ctx) {}
    gd::GdVal f_rng;
    gd::GdVal f_debug_flip_tag;
    gd::GdVal f_oracle_trace;
    gd::GdVal f_oracle_trace_log;
    gd::GdVal f__stacktrace;
    gd::GdVal f_draw_seq;
    gd::GdVal f_globalChainOpen;
    gd::GdVal fn__init(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_set_state(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_roll(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_flip(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_flipPercent(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_flipRound(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_flipWeighted(const gd::GdVal* _args, int _argc);
    gd::GdVal fn__trace(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_trace_event(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_trace_diag(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_bare_draw_seq(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_bare_randf_range(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_bare_randf(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_bare_randi_range(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_randf_range(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_randi_range(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_pickRandomElement(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_shuffle(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_shuffleEngine(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_pickRandomEngine(const gd::GdVal* _args, int _argc);
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
