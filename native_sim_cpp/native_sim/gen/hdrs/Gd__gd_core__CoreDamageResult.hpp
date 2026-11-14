#pragma once
#pragma STDC FP_CONTRACT OFF
#include "../../gd_rt.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core__CoreDamageResult : public gd::GdObj {
    explicit Gd__gd_core__CoreDamageResult(gd::BattleCtx* ctx) : gd::GdObj(ctx) {}
    gd::GdVal f_event;
    gd::GdVal f_damageSource;
    gd::GdVal f_damage;
    gd::GdVal f_healthDamage;
    gd::GdVal f_hit;
    gd::GdVal f_critical;
    gd::GdVal f_damageReduction;
    gd::GdVal f__ctx;
    gd::GdVal fn_reset(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getDamage(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_hasHit(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_wasCriticalHit(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_makeCritical(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_applyDamageReduction(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_triggerOnHit(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_triggerOnDamaged(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_triggerOnMeleeAttacked(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_triggerOnAttacked(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_canTriggerItems(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_canTriggerSpikes(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_canTriggerVampirism(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_willBeLethal(const gd::GdVal* _args, int _argc);
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
