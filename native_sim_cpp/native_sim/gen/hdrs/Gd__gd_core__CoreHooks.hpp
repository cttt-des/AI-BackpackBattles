#pragma once
#pragma STDC FP_CONTRACT OFF
#include "../../gd_rt.hpp"
#include "../class_metas.hpp"
#include "../sym_ids.hpp"

struct Gd__gd_core__CoreHooks : public gd::GdObj {
    explicit Gd__gd_core__CoreHooks(gd::BattleCtx* ctx) : gd::GdObj(ctx) {}
    gd::GdVal fn_showCooldown(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_showCooldownSmooth(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_resetZ(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_playActivationAnimation(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_playActivationSound(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_playDropSound(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_spawnLabel(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_queueTooltipUpdate(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_activateBuffCounter(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_playOutOfStaminaAnimation(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_playStunAnimation(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_playFatigueAnimation(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_playFatigueSound(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_playAttackAnimation(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_playActivateAnimation(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_playAffectedPlacedAnimation(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_playWinLoseAnimation(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onClassChanged(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_playBattleRageAnimation(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_playInvulnerableAnimation(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onItemRotated(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_previewCellCollision(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_previewCells(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_previewCanAffect(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_spawnLabel_character(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_spawnReflectLabel(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_spawnResistedLabel(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_spawnProtectedLabel(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_spawnBuffLabel_item(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_spawnBuffLabel(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_spawnNumberLabel(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_spawnMissLabel(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_damageAnimation(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_playCharacterSound(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onHealthChangedUI(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onMaxStaminaChangedUI(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_spawnLabelOnItem(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_onItemTypeChanged(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_sendCharge(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_applyImpulse(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_addMetric(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_snapshotItemTooltipStat(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_snapshotItemState(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_snapshotItemMetric(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_snapshotCharacterStat(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_snapshotStack(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_snapshotDamageDealt(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_snapshotGlobalStat(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_snapshotMetric(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_updateDamageMeter(const gd::GdVal* _args, int _argc);
    gd::GdVal fn_logEvent(const gd::GdVal* _args, int _argc);
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
