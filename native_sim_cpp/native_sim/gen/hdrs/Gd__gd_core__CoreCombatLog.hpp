#pragma once
#pragma STDC FP_CONTRACT OFF
#include "../../gd_rt.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core__CoreCombatLog : public gd::GdObj {
    explicit Gd__gd_core__CoreCombatLog(gd::BattleCtx* ctx) : gd::GdObj(ctx) {}
    gd::GdVal f_eventNum;
    gd::GdVal f__ctx;
    gd::GdVal fn_getTimeStamp(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_createEvent(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_logEvent(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_createEvent_Attack(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_createEvent_Damage(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_createEvent_Heal(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_createEvent_LoseHealth(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_createEvent_Stack(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_createEvent_StackTemporary(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_createEvent_StackTimeout(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_createEvent_StackResistOrNullify(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_createEvent_StackProtect(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_createEvent_Stun(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_createEvent_StunResist(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_createEvent_InvulnerableStart(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_createEvent_InvulnerableEnd(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_createEvent_Stamina(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_createEvent_DrainStamina(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_createEvent_OutOfStamina(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_createEvent_DamageBuff(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_createEvent_TemporaryMaxHealth(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_createEvent_TemporaryMaxStamina(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_createEvent_BattleRageStart(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_createEvent_BattleRageEnd(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_createEvent_Reincarnate(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_createEvent_Activation(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_createEvent_DamChange(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_snapshotMetric(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_snapshotItemMetric(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_snapshotItemTooltipStat(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_snapshotItemState(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_snapshotGlobalStat(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_snapshotCharacterStat(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_snapshotStack(const gd::GdVal* _args, int _argc);
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
