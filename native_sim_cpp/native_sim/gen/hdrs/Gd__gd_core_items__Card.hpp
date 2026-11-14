#pragma once
#pragma STDC FP_CONTRACT OFF
#include "Gd__gd_core_items__Item.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core_items__Card : public Gd__gd_core_items__Item {
    explicit Gd__gd_core_items__Card(gd::BattleCtx* ctx) : Gd__gd_core_items__Item(ctx) {}
    gd::GdVal f_back;
    gd::GdVal f_activeFront;
    gd::GdVal f_curActivationDelay;
    gd::GdVal f_faceUp;
    gd::GdVal f_activating;
    gd::GdVal f_chainPosition;
    gd::GdVal f_deck;
    gd::GdVal f_cardAnimation;
    gd::GdVal f_front;
    gd::GdVal f_connector;
    gd::GdVal f_notInChainMark;
    gd::GdVal fn_setFaceUp(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_setFaceDown(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_updateTexture(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_cardSecondaryEffectActive(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_canAffect(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_prepare(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_preCombatStart(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getNextCard(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_startActivation(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_playActivationAnimation(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onStateChanged(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_doRevealEffect(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_trigger(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_combatEnd(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_shopEntered(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_addToInventory(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_notifyChainPosition(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getDescription(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getCardDescription(const gd::GdVal* _args, int _argc);
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
