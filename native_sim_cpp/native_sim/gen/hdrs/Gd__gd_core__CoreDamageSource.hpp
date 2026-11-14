#pragma once
#pragma STDC FP_CONTRACT OFF
#include "../../gd_rt.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core__CoreDamageSource : public gd::GdObj {
    explicit Gd__gd_core__CoreDamageSource(gd::BattleCtx* ctx) : gd::GdObj(ctx) {}
    gd::GdVal f_minDamage;
    gd::GdVal f_maxDamage;
    gd::GdVal f_types;
    gd::GdVal f_accuracy;
    gd::GdVal f_critChancePercent;
    gd::GdVal f_origin;
    gd::GdVal f_flags;
    gd::GdVal f__rng;
    gd::GdVal fn_fromDamageSource(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_setItem(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_init(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_hasType(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_setDamage(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_addDamage(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getCritChancePercent(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_updateItem(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_updateEffect(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_addCritChancePercent(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_setFlag(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_unsetFlag(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_canMiss(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_canTriggerSpikes(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_canTriggerVampirism(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_canBeBlocked(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_canCrit(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_isAttack(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_isEffectDamage(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_isAttackOrEffect(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_canApplyLifesteal(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_makeSpectral(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_randDamage(const gd::GdVal* _args, int _argc);
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
