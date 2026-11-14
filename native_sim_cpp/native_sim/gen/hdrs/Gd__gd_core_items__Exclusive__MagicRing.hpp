#pragma once
#pragma STDC FP_CONTRACT OFF
#include "Gd__gd_core_items__Item.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core_items__Exclusive__MagicRing : public Gd__gd_core_items__Item {
    explicit Gd__gd_core_items__Exclusive__MagicRing(gd::BattleCtx* ctx) : Gd__gd_core_items__Item(ctx) {}
    gd::GdVal f_stackToTypes;
    gd::GdVal f_stackToColor;
    gd::GdVal f_effects;
    gd::GdVal f_effectDict;
    gd::GdVal f_gainedStacks;
    gd::GdVal f_playerLowTriggered;
    gd::GdVal f_oppoLowTriggered;
    gd::GdVal f_ringTypes;
    gd::GdVal f_textEffect;
    gd::GdVal f_numEffects;
    gd::GdVal f_healthThreshold;
    gd::GdVal f_opponentHealthThreshold;
    gd::GdVal f_stones;
    gd::GdVal f_symbols;
    gd::GdVal fn_hasCooldown(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_hasStartofBattle(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onPrepare(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onCombatStart(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_doCooldownEffect(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onDamaged(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onOppoDamaged(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_giveStacksFromEffect(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_sortEffects(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getTypes(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_hasType(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getNumStaticTypes(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_gainsStack(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_gainsBuffs(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_inflictsDebuffs(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getTextEffect(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_randEffects(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_setCraftedEffects(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getScaledParam(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_isOnlyForDisplay(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getDescription(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_copyFrom(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getData(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_setData(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_persistDataInShop(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getDataPersistent(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getDataPersistentBits(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onCraftedFrom(const gd::GdVal* _args, int _argc);
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
