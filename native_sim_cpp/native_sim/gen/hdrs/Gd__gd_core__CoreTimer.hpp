#pragma once
#pragma STDC FP_CONTRACT OFF
#include "../../gd_rt.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core__CoreTimer : public gd::GdObj {
    explicit Gd__gd_core__CoreTimer(gd::BattleCtx* ctx) : gd::GdObj(ctx) {}
    gd::GdVal f__ctx;
    gd::GdVal f__owner;
    gd::GdVal f_name;
    gd::GdVal f_wait_time;
    gd::GdVal f_one_shot;
    gd::GdVal f_multi;
    gd::GdVal f_callback_method;
    gd::GdVal f_timestamps;
    gd::GdVal f__left;
    gd::GdVal f__stopped;
    gd::GdVal f_fire_count;
    gd::GdVal f__eng;
    gd::GdVal f__seen;
    gd::GdVal f__multi_start_time;
    gd::GdVal f__dbg;
    gd::GdVal f__started_frame;
    gd::GdVal fn__init(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_is_stopped(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_get_time_left(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_start(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_stop(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_isFinished(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_tick(const gd::GdVal* _args, int _argc);
    gd::GdVal fn__onTimeout(const gd::GdVal* _args, int _argc);
    gd::GdVal fn__utilTime(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_rebuildSeen(const gd::GdVal* _args, int _argc);
    static gd::GdVal sf__f32eng(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
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
