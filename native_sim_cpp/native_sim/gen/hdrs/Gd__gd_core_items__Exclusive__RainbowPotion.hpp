#pragma once
#pragma STDC FP_CONTRACT OFF
#include "Gd__gd_core_items__Potion.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core_items__Exclusive__RainbowPotion : public Gd__gd_core_items__Potion {
    explicit Gd__gd_core_items__Exclusive__RainbowPotion(gd::BattleCtx* ctx) : Gd__gd_core_items__Potion(ctx) {}
    gd::GdVal f_usedBuffs;
    gd::GdVal f_buffsNeeded;
    gd::GdVal f_numPotions;
    gd::GdVal f_buffsPerStaff;
    gd::GdVal f_manaPerBook;
    gd::GdVal f_staminaPerBook;
    gd::GdVal fn_canAffect_global(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getAffectedCellsAfterRotate_primary(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_isAffectingDistinct(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_canAffect_secondary(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_canAffect_tertiary(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onTriggerPotion(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onPrepare(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onCombatStart(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onBuffsChanged(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getGatedDescriptor(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getStarPosition(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getRelatedItems(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getRelatedItemColumns(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getRelatedItemHeight(const gd::GdVal* _args, int _argc);
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
