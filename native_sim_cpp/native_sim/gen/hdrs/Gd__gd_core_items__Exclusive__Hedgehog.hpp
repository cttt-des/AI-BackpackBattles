#pragma once
#pragma STDC FP_CONTRACT OFF
#include "Gd__gd_core_items__Exclusive__ForestFriend.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core_items__Exclusive__Hedgehog : public Gd__gd_core_items__Exclusive__ForestFriend {
    explicit Gd__gd_core_items__Exclusive__Hedgehog(gd::BattleCtx* ctx) : Gd__gd_core_items__Exclusive__ForestFriend(ctx) {}
    gd::GdVal f_hasActivated;
    gd::GdVal f_spikes;
    gd::GdVal f_damagePerSpike;
    gd::GdVal f_healthThreshold;
    gd::GdVal fn_doCooldownEffect(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onPrepare(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onDamaged(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onHPLow(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_spawnSpikeParticles(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getTriggerPriority(const gd::GdVal* _args, int _argc);
    gd::GdVal fn__readyInit(const gd::GdVal* _args, int _argc);
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
