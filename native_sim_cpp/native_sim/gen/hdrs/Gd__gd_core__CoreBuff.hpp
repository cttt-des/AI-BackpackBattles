#pragma once
#pragma STDC FP_CONTRACT OFF
#include "../../gd_rt.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core__CoreBuff : public gd::GdObj {
    explicit Gd__gd_core__CoreBuff(gd::BattleCtx* ctx) : gd::GdObj(ctx) {}
    gd::GdVal f_type;
    gd::GdVal f_isBuff;
    gd::GdVal f_character;
    gd::GdVal f_current;
    gd::GdVal f_permanentStacks;
    gd::GdVal f_resistChancePercent;
    gd::GdVal f_resistStacks;
    gd::GdVal f_reflectChancePercent;
    gd::GdVal f_cleanseProtectionChancePercent;
    gd::GdVal f_signalName;
    gd::GdVal f_temporaryStacks;
    gd::GdVal f_nextTemporaryTimeout;
    gd::GdVal f_MAX_STACKS;
    gd::GdVal f__timer_left;
    gd::GdVal f__timer_active;
    gd::GdVal f__timer_eng;
    gd::GdVal f__timer_seen;
    gd::GdVal f_ctx;
    gd::GdVal fn_init(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getStacks(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_setStacks(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_reset(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_changeResistChance(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_changeResistStacks(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_changeCleanseProtectionChance(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_changeReflectChance(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_gainStacks(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_gainTemporary(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_loseStacks(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_changeCurrentLogShowLabel(const gd::GdVal* _args, int _argc);
    gd::GdVal fn__blnd_snap(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onTimeout(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_combatEnd(const gd::GdVal* _args, int _argc);
    gd::GdVal fn__startTimer(const gd::GdVal* _args, int _argc);
    static gd::GdVal sf__f32eng(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc);
    gd::GdVal fn__stopTimer(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_isTimerActive(const gd::GdVal* _args, int _argc);
    gd::GdVal fn__tick(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_rebuildTimerSeen(const gd::GdVal* _args, int _argc);
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
