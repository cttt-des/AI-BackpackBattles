#pragma once
#pragma STDC FP_CONTRACT OFF
#include "Gd__gd_core_items__Weapon.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core_items__Exclusive__WaterElemental : public Gd__gd_core_items__Weapon {
    explicit Gd__gd_core_items__Exclusive__WaterElemental(gd::BattleCtx* ctx) : Gd__gd_core_items__Weapon(ctx) {}
    gd::GdVal f_manaUsed;
    gd::GdVal f_activeEffects;
    gd::GdVal f_coldParticles;
    gd::GdVal f_distortion;
    gd::GdVal f_manaOnHit;
    gd::GdVal f_bonusManaOnHit;
    gd::GdVal f_iceSpeed;
    gd::GdVal f_bonusDam;
    gd::GdVal f_coldOnHit;
    gd::GdVal f_manaNeeded1;
    gd::GdVal f_manaNeeded2;
    gd::GdVal f_manaNeeded3;
    gd::GdVal fn_canAffect(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_canAffect_secondary(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onPrepare(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onManaChanged(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onDealtDamage(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onShopEntered(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onStateChanged(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getDescription(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_playPickupSound(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_playDropSound(const gd::GdVal* _args, int _argc);
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
