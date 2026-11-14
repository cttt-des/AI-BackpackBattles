#pragma once
#pragma STDC FP_CONTRACT OFF
#include "Gd__gd_core_items__Item.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core_items__Gems__Gem : public Gd__gd_core_items__Item {
    explicit Gd__gd_core_items__Gems__Gem(gd::BattleCtx* ctx) : Gd__gd_core_items__Item(ctx) {}
    gd::GdVal f_hoveredSocket;
    gd::GdVal f_socket;
    gd::GdVal f_movebackSocket;
    gd::GdVal f_dropTween;
    gd::GdVal f_gemPower;
    gd::GdVal f_dropPosition;
    gd::GdVal f_dropRotation;
    gd::GdVal f_quantizedRotation;
    gd::GdVal f_socketDetectionArea;
    gd::GdVal f_gemAnimation;
    gd::GdVal fn_isGem(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_isOwnable(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_isOwnedByOpponent(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getEffectiveOwnerType(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getInventory(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getItem(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_isPlaced(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_isInInventory(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getGemMode(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getGemPower(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_changeGemPower(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getHoverPriority(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_character(const gd::GdVal* _args, int _argc);
    gd::GdVal fn__process(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_previewCellCollision(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_gainFocus(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_loseFocus(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_prepareLerpToSocket(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_drop(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_lerpToSocket(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_pickup(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_addToSocket(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_unsocket(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_removeFromSocket(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_killDropTween(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_returnToSocket(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_hasCooldown(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_miniActivate(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_prepareInventory(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_prepareWeapon(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_prepareArmor(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onPrepare(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_combatStartInventory(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_combatStartWeapon(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_combatStartArmor(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_combatStart(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_combatEndInventory(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_combatEndWeapon(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_combatEndArmor(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_combatEnd(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_shopEntered(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getBaseDescription(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getDescription(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onHotSwapHoverWithGem(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onHotSwapHoverWithGemEnd(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_createGemParticles(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_canPreviewFusions(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_canModifyChance(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_getNeighborItemsAndGems(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_canCombine(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_shift(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_isMovingBack(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_addToStorageBox(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_discard(const gd::GdVal* _args, int _argc);
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
