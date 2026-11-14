#pragma once
#pragma STDC FP_CONTRACT OFF
#include "../../gd_rt.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core__CoreCombat : public gd::GdObj {
    explicit Gd__gd_core__CoreCombat(gd::BattleCtx* ctx) : gd::GdObj(ctx) {}
    gd::GdVal f_ctx;
    gd::GdVal f_player;
    gd::GdVal f_opponent;
    gd::GdVal f_ordered_items;
    gd::GdVal f_result;
    gd::GdVal f_fight_ended;
    gd::GdVal f_combat_time;
    gd::GdVal f_fatigue_counter;
    gd::GdVal f_fatigue_started;
    gd::GdVal f_fatigue_next_tick;
    gd::GdVal f_fatigue_interval;
    gd::GdVal f_time_advance;
    gd::GdVal f_speed_scale;
    gd::GdVal f__activate_countdown;
    gd::GdVal f_activated;
    gd::GdVal f__dbg_spdt;
    gd::GdVal f__tick_timer_left;
    gd::GdVal f__tick_timer_active;
    gd::GdVal f_max_time;
    gd::GdVal f_timed_out;
    gd::GdVal f__pending_deferred;
    gd::GdVal fn__init(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_setup(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_startBattle(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_prepareItems(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_resetInventories(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_activateItems(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_physicsTick(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_run(const gd::GdVal* _args, int _argc);
    gd::GdVal fn__fatigueTick(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_startFatigue(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_dealFatigueDamage(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_hasFatigueStarted(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_advanceTime(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getEffectiveTime(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_endCombat(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_forceLoseCombat(const gd::GdVal* _args, int _argc);
    gd::GdVal fn__flushDeferred(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_combatEndDeferred(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_playerWins(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_winner(const gd::GdVal* _args, int _argc);
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
