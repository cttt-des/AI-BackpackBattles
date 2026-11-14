#pragma once
#pragma STDC FP_CONTRACT OFF
#include "../../gd_rt.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core__CoreContext : public gd::GdObj {
    explicit Gd__gd_core__CoreContext(gd::BattleCtx* ctx) : gd::GdObj(ctx) {}
    gd::GdVal f_rng;
    gd::GdVal f_util;
    gd::GdVal f_bus;
    gd::GdVal f_hooks;
    gd::GdVal f_combat_log;
    gd::GdVal f_player;
    gd::GdVal f_opponent;
    gd::GdVal f_fight_ended;
    gd::GdVal f_time;
    gd::GdVal f_probe_pass;
    gd::GdVal f_frame_counter;
    gd::GdVal f_combat_time;
    gd::GdVal f_below_master;
    gd::GdVal f_label_rng_enabled;
    gd::GdVal f_lobbies_mode;
    gd::GdVal f_custom_health_multiplier;
    gd::GdVal f_flk_delay_cursor;
    gd::GdVal f__drawseq_enabled;
    gd::GdVal f_lib_fires;
    gd::GdVal f_combat;
    gd::GdVal f_item_book;
    gd::GdVal f_sandbag_active;
    gd::GdVal f_cur_mode;
    gd::GdVal f_cur_round;
    gd::GdVal f_rope_speedups;
    gd::GdVal f_cube_advanced;
    gd::GdVal f_event_type_keys;
    gd::GdVal f_class_resources;
    gd::GdVal f_unhealingDamageSource;
    gd::GdVal f_fatigueDamageSource;
    gd::GdVal f_stealLifeDamageSource;
    gd::GdVal f_out_of_stamina_count;
    gd::GdVal f_warn_unknown_api;
    gd::GdVal f__deferred;
    gd::GdVal f__timed;
    gd::GdVal f_deferred_flush_enabled;
    gd::GdVal f_eb_relay_mirrored;
    gd::GdVal f_keyed_stop_clears_seen;
    gd::GdVal f_keyed_cleanse_biggest_first;
    gd::GdVal f__emptyGrid;
    gd::GdVal fn_set_drawseq_enabled(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_lib_fires_tick(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_set_custom_health_multiplier(const gd::GdVal* _args, int _argc);
    gd::GdVal fn__init(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_set_state(const gd::GdVal* _args, int _argc);
    gd::GdVal fn__newDamageSource(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getCharacterFromId(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_otherCharacter(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_advancePhysicsFrame(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_callDelayed(const gd::GdVal* _args, int _argc);
    gd::GdVal fn__flushTimed(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_defer(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_hasDeferred(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_flushDeferred(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_emptyGrid(const gd::GdVal* _args, int _argc);
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
