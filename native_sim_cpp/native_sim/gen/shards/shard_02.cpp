#pragma STDC FP_CONTRACT OFF

#include "../hdrs/Gd__gd_core__Card.hpp"
#include "../hdrs/Gd__gd_core__Bloodthorne.hpp"
#include "../hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "../hdrs/Gd__gd_core__CoreRng.hpp"
#include "../hdrs/Gd__gd_core__DeathScythe.hpp"
#include "../hdrs/Gd__gd_core__Garlic.hpp"
#include "../hdrs/Gd__gd_core__Item__INNER__SignalConnection.hpp"
#include "../hdrs/Gd__gd_core__Item.hpp"
#include "../hdrs/Gd__gd_core__Shield.hpp"
#include "../hdrs/Gd__gd_core__Present.hpp"
#include "../hdrs/Gd__gd_core__StaminaSack.hpp"
#include "../hdrs/Gd__gd_core__TheLovers.hpp"
#include "../hdrs/Gd__gd_core_items__AceofSpades.hpp"
#include "../hdrs/Gd__gd_core_items__Bow.hpp"
#include "../hdrs/Gd__gd_core_items__CustomerCard.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__AmuletofAlchemy.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__WisdomPuppy.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__BionicArmor.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Broccotree.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Chess__BlackBishop.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ChromeCube.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__DeathLotus.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__DualWielding.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ExtraBags.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Frostbite.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__HeartoftheCards.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__JustStats.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Lootbox.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__MercuryElemental.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ParadiseBirb.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__PoweroftheMoon.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__RainbowOrb.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ScholarBag.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Sloth.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SpicyBanana.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__StoneShoes.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__TimeMelting.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__WaterElemental.hpp"
#include "../hdrs/Gd__gd_core_items__Gems__CorruptedCrystal.hpp"
#include "../hdrs/Gd__gd_core_items__HoloFireLizard.hpp"
#include "../hdrs/Gd__gd_core_items__MoonShield.hpp"
#include "../hdrs/Gd__gd_core_items__RainbowGoobertRanger.hpp"
#include "../hdrs/Gd__gd_core_items__StrongStoneSkinPotion.hpp"

void Gd__gd_core__Card::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_back = gd::GdVal::null();
    this->f_activeFront = gd::GdVal::null();
    this->f_curActivationDelay = gd::GdVal::from_float(0.0);
    this->f_faceUp = gd::GdVal::from_bool(true);
    this->f_activating = gd::GdVal::from_bool(false);
    this->f_chainPosition = gd::gd_neg(gd::GdVal::from_int(1LL));
    this->f_deck = gd::GdVal::null();
    this->f_cardAnimation = gd::GdVal::null();
    this->f_front = gd::GdVal::null();
    this->f_connector = gd::GdVal::null();
    this->f_notInChainMark = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__Card::meta() const { return &META_Gd__gd_core__Card; }
gd::GdVal Gd__gd_core__Card::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Card::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Card::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case gd::SYM_back: out = this->f_back; return true;
        case SYM_GEN_activeFront_878: out = this->f_activeFront; return true;
        case SYM_GEN_curActivationDelay_879: out = this->f_curActivationDelay; return true;
        case SYM_GEN_faceUp_880: out = this->f_faceUp; return true;
        case SYM_GEN_activating_881: out = this->f_activating; return true;
        case SYM_GEN_chainPosition_882: out = this->f_chainPosition; return true;
        case SYM_GEN_deck_883: out = this->f_deck; return true;
        case SYM_GEN_cardAnimation_884: out = this->f_cardAnimation; return true;
        case gd::SYM_front: out = this->f_front; return true;
        case SYM_GEN_connector_885: out = this->f_connector; return true;
        case SYM_GEN_notInChainMark_886: out = this->f_notInChainMark; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__Card::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case gd::SYM_back: this->f_back = val; return true;
        case SYM_GEN_activeFront_878: this->f_activeFront = val; return true;
        case SYM_GEN_curActivationDelay_879: this->f_curActivationDelay = gd::gd_coerce_float(val); return true;
        case SYM_GEN_faceUp_880: this->f_faceUp = val; return true;
        case SYM_GEN_activating_881: this->f_activating = val; return true;
        case SYM_GEN_chainPosition_882: this->f_chainPosition = val; return true;
        case SYM_GEN_deck_883: this->f_deck = val; return true;
        case SYM_GEN_cardAnimation_884: this->f_cardAnimation = val; return true;
        case gd::SYM_front: this->f_front = val; return true;
        case SYM_GEN_connector_885: this->f_connector = val; return true;
        case SYM_GEN_notInChainMark_886: this->f_notInChainMark = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Card::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_setFaceUp_887: return true;
        case SYM_GEN_setFaceDown_888: return true;
        case SYM_GEN_updateTexture_889: return true;
        case SYM_GEN_cardSecondaryEffectActive_890: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_prepare_124: return true;
        case SYM_GEN_preCombatStart_126: return true;
        case SYM_GEN_getNextCard_891: return true;
        case SYM_GEN_startActivation_892: return true;
        case SYM_GEN_playActivationAnimation_778: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN_doRevealEffect_893: return true;
        case SYM_GEN_trigger_145: return true;
        case SYM_GEN_combatEnd_133: return true;
        case SYM_GEN_shopEntered_745: return true;
        case SYM_GEN_addToInventory_122: return true;
        case SYM_GEN_onRemoveFromInventory_420: return true;
        case SYM_GEN_notifyChainPosition_894: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN_getCardDescription_895: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Card::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_setFaceUp_887: out = fn_setFaceUp(args, argc); return true;
        case SYM_GEN_setFaceDown_888: out = fn_setFaceDown(args, argc); return true;
        case SYM_GEN_updateTexture_889: out = fn_updateTexture(args, argc); return true;
        case SYM_GEN_cardSecondaryEffectActive_890: out = fn_cardSecondaryEffectActive(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_prepare_124: out = fn_prepare(args, argc); return true;
        case SYM_GEN_preCombatStart_126: out = fn_preCombatStart(args, argc); return true;
        case SYM_GEN_getNextCard_891: out = fn_getNextCard(args, argc); return true;
        case SYM_GEN_startActivation_892: out = fn_startActivation(args, argc); return true;
        case SYM_GEN_playActivationAnimation_778: out = fn_playActivationAnimation(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_doRevealEffect_893: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN_trigger_145: out = fn_trigger(args, argc); return true;
        case SYM_GEN_combatEnd_133: out = fn_combatEnd(args, argc); return true;
        case SYM_GEN_shopEntered_745: out = fn_shopEntered(args, argc); return true;
        case SYM_GEN_addToInventory_122: out = fn_addToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_420: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_notifyChainPosition_894: out = fn_notifyChainPosition(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_getCardDescription_895: out = fn_getCardDescription(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Card::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Card::fn_setFaceUp(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_faceUp)))) {
        this->f_faceUp = gd::GdVal::from_bool(true);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_setFaceDown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_faceUp)) {
        this->f_faceUp = gd::GdVal::from_bool(false);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_updateTexture(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_faceUp)) {
        if (gd::gd_truth((gd::gd_truth((gd::gd_truth(this->f_deck) ? gd::GdVal::from_bool(gd::gd_truth(this->f_activeFront)) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cardSecondaryEffectActive_890, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        }
        else {
        }
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_cardSecondaryEffectActive(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(this->f_placed)) {
        return (gd::gd_truth((gd::gd_truth(this->f_deck) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Card_2672)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, lv_item, SYM_GEN_chainPosition_882), this->f_chainPosition))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_item, SYM_GEN_chainPosition_882), gd::gd_neg(gd::GdVal::from_int(1LL))))))))) : gd::GdVal::from_bool(false));
    }
    else {
        return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Card_2672)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::get_prop(gd_ctx, lv_item, SYM_GEN_deck_883))))) : gd::GdVal::from_bool(false));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_prepare_124, nullptr, 0, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_preCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_preCombatStart_126, nullptr, 0, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_deactivateCooldown_101, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_getNextCard(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_affected = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInAffectedCells_cached_425, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_affected, gd::SYM_empty, nullptr, 0)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Card_2672)}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL)), SYM_GEN_hasType_81, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        return gd::get_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL));
    }
    else {
        return gd::GdVal::null();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_startActivation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth((gd::gd_truth(this->f_activating) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(this->f_faceUp))))) {
        return gd::GdVal::null();
    }
    this->f_activating = gd::GdVal::from_bool(true);
    this->f_iterationCooldown = gd::gd_coerce_float(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCooldown_104, nullptr, 0));
    this->f_triggerTime = gd::gd_coerce_float(this->f_iterationCooldown);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activateCooldown_100, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_Cooldown_2546)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_playActivationAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_aniType = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_activationAni_1621));
    gd::GdVal lv_consume = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(false));
    lv_consume = gd::gd_coerce_bool(lv_consume);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__faceUp = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv__faceUp = gd::gd_coerce_bool(lv__faceUp);
    if (gd::gd_truth(lv__faceUp)) {
        if (gd::gd_truth(this->f_faceUp)) {
        }
        else {
        }
    }
    else {
        if (gd::gd_truth(this->f_faceUp)) {
        }
    }
    this->f_faceUp = lv__faceUp;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_doRevealEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_trigger(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_activating = gd::GdVal::from_bool(false);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldown_794, _ca, 1); })();
    gd::GdVal lv_nextCard = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNextCard_891, nullptr, 0);
    if (gd::gd_truth(lv_nextCard)) {
        (void)gd::call_method(gd_ctx, lv_nextCard, SYM_GEN_startActivation_892, nullptr, 0);
    }
    this->f_triggerTime = gd::gd_coerce_float(this->f_iterationCooldown);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_deactivateCooldown_101, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doRevealEffect_893, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_combatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_combatEnd_133, nullptr, 0, _out); return _out; })();
    this->f_activating = gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_shopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_craft = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_craft = gd::gd_coerce_bool(lv_craft);
    (void)([&]() { gd::GdVal _ca[] = {lv_craft}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_shopEntered_745, _ca, 1, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setFaceUp_887, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_addToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__inventory = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__occupiedCells = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv__placedByPlayer = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv__placedByPlayer = gd::gd_coerce_bool(lv__placedByPlayer);
    (void)([&]() { gd::GdVal _ca[] = {lv__inventory, lv__occupiedCells, lv__placedByPlayer}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_addToInventory_122, _ca, 3, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_deck = gd::GdVal::null();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateTexture_889, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_notifyChainPosition(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__deck = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__chainPos = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_chainLength = (_argc > 2) ? _args[2] : gd::GdVal::null();
    this->f_chainPosition = lv__chainPos;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_chainPosition, gd::gd_neg(gd::GdVal::from_int(1LL)))))) {
        this->f_deck = gd::GdVal::null();
        if (gd::gd_truth(this->f_placed)) {
        }
    }
    else {
        this->f_deck = lv__deck;
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_chainPosition, gd::gd_sub(lv_chainLength, gd::GdVal::from_int(1LL)))))) {
        }
        else {
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateTexture_889, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_getDescription_642, _ca, 1, _out); return _out; })();
    return ([&]() { gd::GdVal _ca[] = {lv_descr}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCardDescription_895, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn_getCardDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(this->f_deck)) {
        lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "\n\n", 2u)), ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "CARD_COUNT", 10u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_tra_2620, _ca, 1); })(), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "num", 3u)), this->f_chainPosition, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StatModified_864), SYM_GEN_No_2548), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 5); })()));
    }
    else if (gd::gd_truth(this->f_placed)) {
        lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "\n\n", 2u)), ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "CARD_HINT", 9u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_tra_2620, _ca, 1); })(), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_paramColor_2622)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_wrapInColor_2673, _ca, 2); })()));
    }
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Card::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Card(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Card>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Card = {CLS_Gd__gd_core__Card, "Card", "res://gd_core/Card.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__Card, &Gd__gd_core__Card::get_static_prop_fn, &Gd__gd_core__Card::call_static_fn};

void Gd__gd_core__Bloodthorne::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
    this->f_regenNeeded = gd::GdVal::null();
    this->f_vampirism = gd::GdVal::null();
    this->f_spikes = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__Bloodthorne::meta() const { return &META_Gd__gd_core__Bloodthorne; }
gd::GdVal Gd__gd_core__Bloodthorne::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Bloodthorne::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Bloodthorne::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_regenNeeded_942: out = this->f_regenNeeded; return true;
        case SYM_GEN_vampirism_940: out = this->f_vampirism; return true;
        case SYM_GEN_spikes_898: out = this->f_spikes; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__Bloodthorne::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_regenNeeded_942: this->f_regenNeeded = val; return true;
        case SYM_GEN_vampirism_940: this->f_vampirism = val; return true;
        case SYM_GEN_spikes_898: this->f_spikes = val; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Bloodthorne::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onVampirismChanged_943: return true;
        case SYM_GEN_onSpikesChanged_944: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__Bloodthorne::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onVampirismChanged_943: out = fn_onVampirismChanged(args, argc); return true;
        case SYM_GEN_onSpikesChanged_944: out = fn_onSpikesChanged(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Bloodthorne::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Bloodthorne::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_vampirism_changed", 27u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onVampirismChanged", 18u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_spikes_changed", 24u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onSpikesChanged", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bloodthorne::fn_onVampirismChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_164, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bloodthorne::fn_onSpikesChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_164, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bloodthorne::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        gd::GdVal lv_numRegen = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getRegeneration_1217, nullptr, 0);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_numRegen, this->f_regenNeeded)))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_regenNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useRegeneration_348, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_vampirism, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_212, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_spikes, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_211, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Bloodthorne::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_regenNeeded = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0));
    this->f_vampirism = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0));
    this->f_spikes = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Bloodthorne(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Bloodthorne>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Bloodthorne = {CLS_Gd__gd_core__Bloodthorne, "Bloodthorne", "res://gd_core/Bloodthorne.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__Bloodthorne, &Gd__gd_core__Bloodthorne::get_static_prop_fn, &Gd__gd_core__Bloodthorne::call_static_fn};

static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreCharacter_ID[] = {{"PLAYER", 0LL}, {"OPPONENT", 1LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreCharacter_ID = {"ID", _ekv_Gd__gd_core__CoreCharacter_ID, 2u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreCharacter_Stat[] = {{"Health", 0LL}, {"MaxHealth", 1LL}, {"Stamina", 2LL}, {"MaxStamina", 3LL}, {"Invulnerable", 4LL}, {"Stunned", 5LL}, {"BattleRage", 6LL}, {"ReflectStacks", 7LL}, {"DebuffResistStacks", 8LL}, {"CritStacks", 9LL}, {"DodgeStacks", 10LL}, {"CritResistStacks", 11LL}, {"CritResistance", 12LL}, {"StunResistance", 13LL}, {"HealEfficiency", 14LL}, {"DamageResistance", 15LL}, {"MeleeDmgFactor", 16LL}, {"RangedDmgFactor", 17LL}, {"EffectDmgFactor", 18LL}, {"Unhealing", 19LL}, {"StaminaRegen", 20LL}, {"MaxHealthGain", 21LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreCharacter_Stat = {"Stat", _ekv_Gd__gd_core__CoreCharacter_Stat, 22u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__CoreCharacter_StaminaResult[] = {{"Sufficient", 0LL}, {"Insufficient", 1LL}};
static const gd::GdEnum _enum_Gd__gd_core__CoreCharacter_StaminaResult = {"StaminaResult", _ekv_Gd__gd_core__CoreCharacter_StaminaResult, 2u};
void Gd__gd_core__CoreCharacter::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_ctx = gd::GdVal::null();
    this->f_playerId = gd::GdVal::from_int(0);
    this->f_opponent = gd::GdVal::null();
    this->f_isDead = gd::GdVal::from_bool(false);
    this->f_buffs = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_maxHealth = gd::gd_coerce_float(gd::GdVal::from_float(30.0));
    this->f_curHealth = gd::GdVal::from_float(0.0);
    this->f_temporaryMaxHealth = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_temporaryMaxHealthGain = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_baseMaxStamina = gd::GdVal::from_float(0.0);
    this->f_maxStamina = gd::gd_coerce_float(gd::GdVal::from_float(5.0));
    this->f_curStamina = gd::GdVal::from_float(0.0);
    this->f_temporaryMaxStamina = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_baseStaminaRegen = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_staminaRegen = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_allowStaminaOverflow = gd::GdVal::from_bool(false);
    this->f_staminaUpdateQueued = gd::GdVal::from_bool(false);
    this->f_statsDisplay = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_damageResistance = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_damageReduction = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_invulnerable = gd::GdVal::from_bool(false);
    this->f_dodgeStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_critResistance = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_critResistStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_critTokens = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_stunResistance = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_unhealingAmount = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_healingEfficiency = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_critTokensUsed = gd::GdVal::from_int(0LL);
    this->f_debuffResistStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_debuffReflectStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_buffProtectStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_bonusFatigueDamage = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_empowerDamage = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_blindingLightActive = gd::GdVal::from_bool(false);
    this->f_stunnedDuration = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_tickCounter = gd::GdVal::from_int(0LL);
    this->f_typedDamageFactors = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_meleeSpikesLimit = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_rangedSpikesLimit = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_effectSpikesLimit = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_meleeVampirismLimit = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_rangedVampirismLimit = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_battleRageAura = gd::GdVal::null();
    this->f_battleRageBonusDur = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_accuracyRng = gd::GdVal::null();
    this->f_critRng = gd::GdVal::null();
    this->f_critResistanceRng = gd::GdVal::null();
    this->f_stunResistanceRng = gd::GdVal::null();
    this->f_items = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_inventory = gd::GdVal::null();
    this->f_INVENTORY = gd::GdVal::null();
    this->f_character_died_handlers = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_poisonDamageSource = gd::GdVal::null();
    this->f_spikeDamageSource = gd::GdVal::null();
    this->f_characterClass = gd::gd_coerce_int(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Classes_1372), SYM_GEN_Ranger_2678));
    this->f_chibi = gd::GdVal::from_bool(false);
    this->f_invulnerabilityItem = gd::GdVal::null();
    this->f__invul_left = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f__invul_active = gd::GdVal::from_bool(false);
    this->f_autoRageItem = gd::GdVal::null();
    this->f__rage_left = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f__rage_active = gd::GdVal::from_bool(false);
    this->f__autoRage_left = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f__autoRage_active = gd::GdVal::from_bool(false);
    this->f__rage_seen = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f__invul_seen = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f__rage_eng = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f__invul_eng = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_attack_moving_forward = gd::GdVal::from_bool(false);
    this->f_attack_sound_ready_time = gd::gd_neg(gd::GdVal::from_float(1.0));
    this->f__tick_timer_left = gd::GdVal::from_float(0.0);
    this->f__tick_timer_active = gd::GdVal::from_bool(false);
    this->f_damage_anim_current = gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u));
}
const gd::GdClassMeta* Gd__gd_core__CoreCharacter::meta() const { return &META_Gd__gd_core__CoreCharacter; }
gd::GdVal Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_ID_1279: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreCharacter_ID);
        case SYM_GEN_Stat_870: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreCharacter_Stat);
        case SYM_GEN_StaminaResult_1280: return gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreCharacter_StaminaResult);
        case SYM_GEN_AUTO_RAGE_DELAY_1044: return gd::GdVal::from_float(5.0);
        case SYM_GEN_AUTO_RAGE_DUR_1045: return gd::GdVal::from_float(4.0);
        case SYM_GEN_CLASS_SOUND_COUNTS_1116: return ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 7); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Classes_1372), SYM_GEN_Ranger_2678), ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 3); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attack", 6u)), gd::GdVal::from_int(3LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "win", 3u)), gd::GdVal::from_int(6LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lose", 4u)), gd::GdVal::from_int(6LL)); return gd::GdVal::from_dict(d); })()); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Classes_1372), SYM_GEN_Reaper_2679), ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 3); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attack", 6u)), gd::GdVal::from_int(3LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "win", 3u)), gd::GdVal::from_int(2LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lose", 4u)), gd::GdVal::from_int(4LL)); return gd::GdVal::from_dict(d); })()); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Classes_1372), SYM_GEN_Berserker_2680), ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 3); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attack", 6u)), gd::GdVal::from_int(3LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "win", 3u)), gd::GdVal::from_int(4LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lose", 4u)), gd::GdVal::from_int(6LL)); return gd::GdVal::from_dict(d); })()); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Classes_1372), SYM_GEN_Pyromancer_2681), ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 3); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attack", 6u)), gd::GdVal::from_int(5LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "win", 3u)), gd::GdVal::from_int(4LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lose", 4u)), gd::GdVal::from_int(4LL)); return gd::GdVal::from_dict(d); })()); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Classes_Full_1373), SYM_GEN_Mage_2682), ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 3); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attack", 6u)), gd::GdVal::from_int(3LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "win", 3u)), gd::GdVal::from_int(6LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lose", 4u)), gd::GdVal::from_int(5LL)); return gd::GdVal::from_dict(d); })()); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Classes_Full_1373), SYM_GEN_Adventurer_2683), ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 3); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attack", 6u)), gd::GdVal::from_int(4LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "win", 3u)), gd::GdVal::from_int(7LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lose", 4u)), gd::GdVal::from_int(6LL)); return gd::GdVal::from_dict(d); })()); d->set(gd_ctx.arena, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Classes_Full_1373), SYM_GEN_Engineer_2684), ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 3); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attack", 6u)), gd::GdVal::from_int(6LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "win", 3u)), gd::GdVal::from_int(5LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lose", 4u)), gd::GdVal::from_int(8LL)); return gd::GdVal::from_dict(d); })()); return gd::GdVal::from_dict(d); })();
        default: break;
    }
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreCharacter::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreCharacter::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_ctx_3: out = this->f_ctx; return true;
        case SYM_GEN_playerId_1046: out = this->f_playerId; return true;
        case SYM_GEN_opponent_77: out = this->f_opponent; return true;
        case SYM_GEN_isDead_1047: out = this->f_isDead; return true;
        case SYM_GEN_buffs_1048: out = this->f_buffs; return true;
        case SYM_GEN_maxHealth_1049: out = this->f_maxHealth; return true;
        case SYM_GEN_curHealth_1050: out = this->f_curHealth; return true;
        case SYM_GEN_temporaryMaxHealth_1051: out = this->f_temporaryMaxHealth; return true;
        case SYM_GEN_temporaryMaxHealthGain_1052: out = this->f_temporaryMaxHealthGain; return true;
        case SYM_GEN_baseMaxStamina_1053: out = this->f_baseMaxStamina; return true;
        case SYM_GEN_maxStamina_1054: out = this->f_maxStamina; return true;
        case SYM_GEN_curStamina_1055: out = this->f_curStamina; return true;
        case SYM_GEN_temporaryMaxStamina_1056: out = this->f_temporaryMaxStamina; return true;
        case SYM_GEN_baseStaminaRegen_1057: out = this->f_baseStaminaRegen; return true;
        case SYM_GEN_staminaRegen_1058: out = this->f_staminaRegen; return true;
        case SYM_GEN_allowStaminaOverflow_1059: out = this->f_allowStaminaOverflow; return true;
        case SYM_GEN_staminaUpdateQueued_1060: out = this->f_staminaUpdateQueued; return true;
        case SYM_GEN_statsDisplay_1061: out = this->f_statsDisplay; return true;
        case SYM_GEN_damageResistance_1062: out = this->f_damageResistance; return true;
        case SYM_GEN_damageReduction_1063: out = this->f_damageReduction; return true;
        case SYM_GEN_invulnerable_1064: out = this->f_invulnerable; return true;
        case SYM_GEN_dodgeStacks_1065: out = this->f_dodgeStacks; return true;
        case SYM_GEN_critResistance_1066: out = this->f_critResistance; return true;
        case SYM_GEN_critResistStacks_1067: out = this->f_critResistStacks; return true;
        case SYM_GEN_critTokens_16: out = this->f_critTokens; return true;
        case SYM_GEN_stunResistance_1068: out = this->f_stunResistance; return true;
        case SYM_GEN_unhealingAmount_1069: out = this->f_unhealingAmount; return true;
        case SYM_GEN_healingEfficiency_1070: out = this->f_healingEfficiency; return true;
        case SYM_GEN_critTokensUsed_1071: out = this->f_critTokensUsed; return true;
        case SYM_GEN_debuffResistStacks_1072: out = this->f_debuffResistStacks; return true;
        case SYM_GEN_debuffReflectStacks_1073: out = this->f_debuffReflectStacks; return true;
        case SYM_GEN_buffProtectStacks_1074: out = this->f_buffProtectStacks; return true;
        case SYM_GEN_bonusFatigueDamage_1075: out = this->f_bonusFatigueDamage; return true;
        case SYM_GEN_empowerDamage_1076: out = this->f_empowerDamage; return true;
        case SYM_GEN_blindingLightActive_1077: out = this->f_blindingLightActive; return true;
        case SYM_GEN_stunnedDuration_1078: out = this->f_stunnedDuration; return true;
        case SYM_GEN_tickCounter_1079: out = this->f_tickCounter; return true;
        case SYM_GEN_typedDamageFactors_1080: out = this->f_typedDamageFactors; return true;
        case SYM_GEN_meleeSpikesLimit_1081: out = this->f_meleeSpikesLimit; return true;
        case SYM_GEN_rangedSpikesLimit_1082: out = this->f_rangedSpikesLimit; return true;
        case SYM_GEN_effectSpikesLimit_1083: out = this->f_effectSpikesLimit; return true;
        case SYM_GEN_meleeVampirismLimit_1084: out = this->f_meleeVampirismLimit; return true;
        case SYM_GEN_rangedVampirismLimit_1085: out = this->f_rangedVampirismLimit; return true;
        case SYM_GEN_battleRageAura_1086: out = this->f_battleRageAura; return true;
        case SYM_GEN_battleRageBonusDur_1087: out = this->f_battleRageBonusDur; return true;
        case SYM_GEN_accuracyRng_1088: out = this->f_accuracyRng; return true;
        case SYM_GEN_critRng_1089: out = this->f_critRng; return true;
        case SYM_GEN_critResistanceRng_1090: out = this->f_critResistanceRng; return true;
        case SYM_GEN_stunResistanceRng_1091: out = this->f_stunResistanceRng; return true;
        case SYM_GEN_items_1092: out = this->f_items; return true;
        case SYM_GEN_inventory_5: out = this->f_inventory; return true;
        case SYM_GEN_INVENTORY_1093: out = this->f_INVENTORY; return true;
        case SYM_GEN_character_died_handlers_1094: out = this->f_character_died_handlers; return true;
        case SYM_GEN_poisonDamageSource_1095: out = this->f_poisonDamageSource; return true;
        case SYM_GEN_spikeDamageSource_1096: out = this->f_spikeDamageSource; return true;
        case SYM_GEN_characterClass_1097: out = this->f_characterClass; return true;
        case SYM_GEN_chibi_1098: out = this->f_chibi; return true;
        case SYM_GEN_invulnerabilityItem_1099: out = this->f_invulnerabilityItem; return true;
        case SYM_GEN__invul_left_1100: out = this->f__invul_left; return true;
        case SYM_GEN__invul_active_1101: out = this->f__invul_active; return true;
        case SYM_GEN_autoRageItem_1102: out = this->f_autoRageItem; return true;
        case SYM_GEN__rage_left_1103: out = this->f__rage_left; return true;
        case SYM_GEN__rage_active_1104: out = this->f__rage_active; return true;
        case SYM_GEN__autoRage_left_1105: out = this->f__autoRage_left; return true;
        case SYM_GEN__autoRage_active_1106: out = this->f__autoRage_active; return true;
        case SYM_GEN__rage_seen_1107: out = this->f__rage_seen; return true;
        case SYM_GEN__invul_seen_1108: out = this->f__invul_seen; return true;
        case SYM_GEN__rage_eng_1109: out = this->f__rage_eng; return true;
        case SYM_GEN__invul_eng_1110: out = this->f__invul_eng; return true;
        case SYM_GEN_attack_moving_forward_1111: out = this->f_attack_moving_forward; return true;
        case SYM_GEN_attack_sound_ready_time_1112: out = this->f_attack_sound_ready_time; return true;
        case SYM_GEN__tick_timer_left_1113: out = this->f__tick_timer_left; return true;
        case SYM_GEN__tick_timer_active_1114: out = this->f__tick_timer_active; return true;
        case SYM_GEN_damage_anim_current_1115: out = this->f_damage_anim_current; return true;
        case SYM_GEN_ID_1279: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreCharacter_ID); return true;
        case SYM_GEN_Stat_870: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreCharacter_Stat); return true;
        case SYM_GEN_StaminaResult_1280: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__CoreCharacter_StaminaResult); return true;
        case SYM_GEN_AUTO_RAGE_DELAY_1044: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_AUTO_RAGE_DUR_1045: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_CLASS_SOUND_COUNTS_1116: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreCharacter::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_ctx_3: this->f_ctx = val; return true;
        case SYM_GEN_playerId_1046: this->f_playerId = gd::gd_coerce_int(val); return true;
        case SYM_GEN_opponent_77: this->f_opponent = val; return true;
        case SYM_GEN_isDead_1047: this->f_isDead = val; return true;
        case SYM_GEN_buffs_1048: this->f_buffs = val; return true;
        case SYM_GEN_maxHealth_1049: this->f_maxHealth = gd::gd_coerce_float(val); return true;
        case SYM_GEN_curHealth_1050: this->f_curHealth = gd::gd_coerce_float(val); return true;
        case SYM_GEN_temporaryMaxHealth_1051: this->f_temporaryMaxHealth = gd::gd_coerce_float(val); return true;
        case SYM_GEN_temporaryMaxHealthGain_1052: this->f_temporaryMaxHealthGain = gd::gd_coerce_float(val); return true;
        case SYM_GEN_baseMaxStamina_1053: this->f_baseMaxStamina = gd::gd_coerce_float(val); return true;
        case SYM_GEN_maxStamina_1054: this->f_maxStamina = gd::gd_coerce_float(val); return true;
        case SYM_GEN_curStamina_1055: this->f_curStamina = gd::gd_coerce_float(val); return true;
        case SYM_GEN_temporaryMaxStamina_1056: this->f_temporaryMaxStamina = gd::gd_coerce_float(val); return true;
        case SYM_GEN_baseStaminaRegen_1057: this->f_baseStaminaRegen = gd::gd_coerce_float(val); return true;
        case SYM_GEN_staminaRegen_1058: this->f_staminaRegen = gd::gd_coerce_float(val); return true;
        case SYM_GEN_allowStaminaOverflow_1059: this->f_allowStaminaOverflow = val; return true;
        case SYM_GEN_staminaUpdateQueued_1060: this->f_staminaUpdateQueued = val; return true;
        case SYM_GEN_statsDisplay_1061: this->f_statsDisplay = val; return true;
        case SYM_GEN_damageResistance_1062: this->f_damageResistance = gd::gd_coerce_float(val); return true;
        case SYM_GEN_damageReduction_1063: this->f_damageReduction = gd::gd_coerce_int(val); return true;
        case SYM_GEN_invulnerable_1064: this->f_invulnerable = val; return true;
        case SYM_GEN_dodgeStacks_1065: this->f_dodgeStacks = gd::gd_coerce_int(val); return true;
        case SYM_GEN_critResistance_1066: this->f_critResistance = gd::gd_coerce_float(val); return true;
        case SYM_GEN_critResistStacks_1067: this->f_critResistStacks = gd::gd_coerce_int(val); return true;
        case SYM_GEN_critTokens_16: this->f_critTokens = gd::gd_coerce_int(val); return true;
        case SYM_GEN_stunResistance_1068: this->f_stunResistance = gd::gd_coerce_float(val); return true;
        case SYM_GEN_unhealingAmount_1069: this->f_unhealingAmount = gd::gd_coerce_float(val); return true;
        case SYM_GEN_healingEfficiency_1070: this->f_healingEfficiency = gd::gd_coerce_float(val); return true;
        case SYM_GEN_critTokensUsed_1071: this->f_critTokensUsed = val; return true;
        case SYM_GEN_debuffResistStacks_1072: this->f_debuffResistStacks = gd::gd_coerce_int(val); return true;
        case SYM_GEN_debuffReflectStacks_1073: this->f_debuffReflectStacks = gd::gd_coerce_int(val); return true;
        case SYM_GEN_buffProtectStacks_1074: this->f_buffProtectStacks = gd::gd_coerce_int(val); return true;
        case SYM_GEN_bonusFatigueDamage_1075: this->f_bonusFatigueDamage = gd::gd_coerce_int(val); return true;
        case SYM_GEN_empowerDamage_1076: this->f_empowerDamage = gd::gd_coerce_float(val); return true;
        case SYM_GEN_blindingLightActive_1077: this->f_blindingLightActive = val; return true;
        case SYM_GEN_stunnedDuration_1078: this->f_stunnedDuration = gd::gd_coerce_float(val); return true;
        case SYM_GEN_tickCounter_1079: this->f_tickCounter = val; return true;
        case SYM_GEN_typedDamageFactors_1080: this->f_typedDamageFactors = val; return true;
        case SYM_GEN_meleeSpikesLimit_1081: this->f_meleeSpikesLimit = gd::gd_coerce_float(val); return true;
        case SYM_GEN_rangedSpikesLimit_1082: this->f_rangedSpikesLimit = gd::gd_coerce_float(val); return true;
        case SYM_GEN_effectSpikesLimit_1083: this->f_effectSpikesLimit = gd::gd_coerce_float(val); return true;
        case SYM_GEN_meleeVampirismLimit_1084: this->f_meleeVampirismLimit = gd::gd_coerce_float(val); return true;
        case SYM_GEN_rangedVampirismLimit_1085: this->f_rangedVampirismLimit = gd::gd_coerce_float(val); return true;
        case SYM_GEN_battleRageAura_1086: this->f_battleRageAura = val; return true;
        case SYM_GEN_battleRageBonusDur_1087: this->f_battleRageBonusDur = gd::gd_coerce_float(val); return true;
        case SYM_GEN_accuracyRng_1088: this->f_accuracyRng = val; return true;
        case SYM_GEN_critRng_1089: this->f_critRng = val; return true;
        case SYM_GEN_critResistanceRng_1090: this->f_critResistanceRng = val; return true;
        case SYM_GEN_stunResistanceRng_1091: this->f_stunResistanceRng = val; return true;
        case SYM_GEN_items_1092: this->f_items = val; return true;
        case SYM_GEN_inventory_5: this->f_inventory = val; return true;
        case SYM_GEN_INVENTORY_1093: this->f_INVENTORY = val; return true;
        case SYM_GEN_character_died_handlers_1094: this->f_character_died_handlers = val; return true;
        case SYM_GEN_poisonDamageSource_1095: this->f_poisonDamageSource = val; return true;
        case SYM_GEN_spikeDamageSource_1096: this->f_spikeDamageSource = val; return true;
        case SYM_GEN_characterClass_1097: this->f_characterClass = gd::gd_coerce_int(val); return true;
        case SYM_GEN_chibi_1098: this->f_chibi = val; return true;
        case SYM_GEN_invulnerabilityItem_1099: this->f_invulnerabilityItem = val; return true;
        case SYM_GEN__invul_left_1100: this->f__invul_left = gd::gd_coerce_float(val); return true;
        case SYM_GEN__invul_active_1101: this->f__invul_active = val; return true;
        case SYM_GEN_autoRageItem_1102: this->f_autoRageItem = val; return true;
        case SYM_GEN__rage_left_1103: this->f__rage_left = gd::gd_coerce_float(val); return true;
        case SYM_GEN__rage_active_1104: this->f__rage_active = val; return true;
        case SYM_GEN__autoRage_left_1105: this->f__autoRage_left = gd::gd_coerce_float(val); return true;
        case SYM_GEN__autoRage_active_1106: this->f__autoRage_active = val; return true;
        case SYM_GEN__rage_seen_1107: this->f__rage_seen = gd::gd_coerce_float(val); return true;
        case SYM_GEN__invul_seen_1108: this->f__invul_seen = gd::gd_coerce_float(val); return true;
        case SYM_GEN__rage_eng_1109: this->f__rage_eng = gd::gd_coerce_float(val); return true;
        case SYM_GEN__invul_eng_1110: this->f__invul_eng = gd::gd_coerce_float(val); return true;
        case SYM_GEN_attack_moving_forward_1111: this->f_attack_moving_forward = val; return true;
        case SYM_GEN_attack_sound_ready_time_1112: this->f_attack_sound_ready_time = val; return true;
        case SYM_GEN__tick_timer_left_1113: this->f__tick_timer_left = val; return true;
        case SYM_GEN__tick_timer_active_1114: this->f__tick_timer_active = val; return true;
        case SYM_GEN_damage_anim_current_1115: this->f_damage_anim_current = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreCharacter::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_setOpponent_1117: return true;
        case SYM_GEN_isPlayer_80: return true;
        case SYM_GEN_getName_236: return true;
        case SYM_GEN_registerCharacterDied_1118: return true;
        case SYM_GEN_clearCharacterDiedHandlers_1119: return true;
        case SYM_GEN_prepare_124: return true;
        case SYM_GEN_combatStart_129: return true;
        case SYM_GEN_combatEnd_133: return true;
        case SYM_GEN_attackMovingForward_reset_1120: return true;
        case SYM_GEN_cleanse_1121: return true;
        case SYM_GEN_onTick_1122: return true;
        case SYM_GEN_playAttackAnimation_1123: return true;
        case SYM_GEN_classAttackSoundCount_1124: return true;
        case SYM_GEN_classRoundSoundCount_1125: return true;
        case SYM_GEN_playActivateAnimation_1126: return true;
        case SYM_GEN_randBuffLabelPos_1127: return true;
        case SYM_GEN_randBuffLabelDir_1128: return true;
        case SYM_GEN_randDmgNumberPos_1129: return true;
        case SYM_GEN_randDmgNumberDir_1130: return true;
        case SYM_GEN_randHealNumberPos_1131: return true;
        case SYM_GEN_dealDamage_222: return true;
        case SYM_GEN_takeDamage_1132: return true;
        case SYM_GEN_spawnLabel_native_1133: return true;
        case SYM_GEN_applySpikes_1134: return true;
        case SYM_GEN_applyVampirism_1135: return true;
        case SYM_GEN_heal_329: return true;
        case SYM_GEN_healToFull_1136: return true;
        case SYM_GEN_reincarnate_1137: return true;
        case SYM_GEN_getCurrentHealth_1138: return true;
        case SYM_GEN_getRelativeHealth_304: return true;
        case SYM_GEN_getMissingHealth_1139: return true;
        case SYM_GEN_setCurrentHealth_1140: return true;
        case SYM_GEN_loseHealth_1141: return true;
        case SYM_GEN_setMaxHealth_1142: return true;
        case SYM_GEN_giveMaxHealth_319: return true;
        case SYM_GEN_getBaseMaxHealth_1143: return true;
        case SYM_GEN_getMaxHealth_1144: return true;
        case SYM_GEN_applyTemporaryMaxHealthGain_1145: return true;
        case SYM_GEN_changeMaxHealthTemporary_1146: return true;
        case SYM_GEN_getMaxStamina_1147: return true;
        case SYM_GEN_gainStamina_1148: return true;
        case SYM_GEN_addStamina_1149: return true;
        case SYM_GEN_clampStamina_1150: return true;
        case SYM_GEN_fillUpStamina_302: return true;
        case SYM_GEN_useStamina_118: return true;
        case SYM_GEN_drainStamina_119: return true;
        case SYM_GEN_setTemporaryMaxStamina_1151: return true;
        case SYM_GEN_setTemporaryMaxHealthGain_1152: return true;
        case SYM_GEN_death_1153: return true;
        case SYM_GEN_stun_332: return true;
        case SYM_GEN_endStun_1154: return true;
        case SYM_GEN_isStunned_1155: return true;
        case SYM_GEN_changeDodgeStacks_1156: return true;
        case SYM_GEN_changeCritResistance_1157: return true;
        case SYM_GEN_critResisted_1158: return true;
        case SYM_GEN_gainCritResistStacks_1159: return true;
        case SYM_GEN_changeStunResistance_1160: return true;
        case SYM_GEN_stunResisted_1161: return true;
        case SYM_GEN_giveUnhealing_1162: return true;
        case SYM_GEN_reduceUnhealing_1163: return true;
        case SYM_GEN_getUnhealing_1164: return true;
        case SYM_GEN_getHealingEfficiency_1165: return true;
        case SYM_GEN_addHealingEfficiency_1166: return true;
        case SYM_GEN_reduceHealingEfficiency_1167: return true;
        case SYM_GEN_getCritTokens_184: return true;
        case SYM_GEN_gainCritTokens_1168: return true;
        case SYM_GEN_changeDebuffResistStacks_1169: return true;
        case SYM_GEN_changeDebuffReflectStacks_1170: return true;
        case SYM_GEN_changeBuffProtectStacks_1171: return true;
        case SYM_GEN_changeReflectChance_1028: return true;
        case SYM_GEN_changeAllDebuffsReflectChance_1172: return true;
        case SYM_GEN_changeMeleeSpikesLimit_1173: return true;
        case SYM_GEN_changeRangedSpikesLimit_1174: return true;
        case SYM_GEN_changeEffectSpikesLimit_1175: return true;
        case SYM_GEN_changeMeleeVampirismLimit_1176: return true;
        case SYM_GEN_changeRangedVampirismLimit_1177: return true;
        case SYM_GEN_getBonusFatigueDamage_1178: return true;
        case SYM_GEN_addFatigueDamage_1179: return true;
        case SYM_GEN_takeFatigueDamage_1180: return true;
        case SYM_GEN_startBlindingLight_1181: return true;
        case SYM_GEN_endBlindingLight_1182: return true;
        case SYM_GEN_startBattleRage_1183: return true;
        case SYM_GEN_endBattleRage_1184: return true;
        case SYM_GEN_getClass_1185: return true;
        case SYM_GEN_isChibi_1186: return true;
        case SYM_GEN_setClass_1187: return true;
        case SYM_GEN_setClassResource_1188: return true;
        case SYM_GEN_lose_1189: return true;
        case SYM_GEN_win_1190: return true;
        case SYM_GEN_setStat_117: return true;
        case SYM_GEN_getStat_263: return true;
        case SYM_GEN_isBattleRaging_1191: return true;
        case SYM_GEN_startAutoRage_1192: return true;
        case SYM_GEN_playBattleRageAnimation_1193: return true;
        case SYM_GEN__setRageTimer_1194: return true;
        case SYM_GEN_makeInvulnerable_1195: return true;
        case SYM_GEN_makeVulnerable_1196: return true;
        case SYM_GEN_invulnerabilityEnded_1197: return true;
        case SYM_GEN_setInvulnerable_1198: return true;
        case SYM_GEN_getStacks_1022: return true;
        case SYM_GEN_getBuffStacks_1199: return true;
        case SYM_GEN_getDebuffStacks_1200: return true;
        case SYM_GEN_setStacks_1023: return true;
        case SYM_GEN_setStacksLogged_1201: return true;
        case SYM_GEN_gainStacks_1029: return true;
        case SYM_GEN_gainStacksTemporary_1202: return true;
        case SYM_GEN_loseStacks_1031: return true;
        case SYM_GEN_useStacks_1203: return true;
        case SYM_GEN_changeResistChance_1025: return true;
        case SYM_GEN_changeDebuffResistChances_1204: return true;
        case SYM_GEN_changeResistStacks_1026: return true;
        case SYM_GEN_getBlock_206: return true;
        case SYM_GEN_setBlock_1205: return true;
        case SYM_GEN_gainBlock_1206: return true;
        case SYM_GEN_loseBlock_208: return true;
        case SYM_GEN_getSpikes_1207: return true;
        case SYM_GEN_setSpikes_1208: return true;
        case SYM_GEN_gainSpikes_1209: return true;
        case SYM_GEN_loseSpikes_340: return true;
        case SYM_GEN_getVampirism_1210: return true;
        case SYM_GEN_setVampirism_1211: return true;
        case SYM_GEN_gainVampirism_1212: return true;
        case SYM_GEN_loseVampirism_343: return true;
        case SYM_GEN_getPoison_1213: return true;
        case SYM_GEN_setPoison_1214: return true;
        case SYM_GEN_gainPoison_1215: return true;
        case SYM_GEN_losePoison_1216: return true;
        case SYM_GEN_getRegeneration_1217: return true;
        case SYM_GEN_setRegeneration_1218: return true;
        case SYM_GEN_gainRegeneration_1219: return true;
        case SYM_GEN_loseRegeneration_1220: return true;
        case SYM_GEN_getLucky_1221: return true;
        case SYM_GEN_setLucky_1222: return true;
        case SYM_GEN_gainLucky_1223: return true;
        case SYM_GEN_loseLucky_350: return true;
        case SYM_GEN_getBlind_1224: return true;
        case SYM_GEN_setBlind_1225: return true;
        case SYM_GEN_gainBlind_1226: return true;
        case SYM_GEN_loseBlind_1227: return true;
        case SYM_GEN_getMana_1228: return true;
        case SYM_GEN_setMana_1229: return true;
        case SYM_GEN_gainMana_1230: return true;
        case SYM_GEN_loseMana_1231: return true;
        case SYM_GEN_getEmpower_1232: return true;
        case SYM_GEN_setEmpower_1233: return true;
        case SYM_GEN_gainEmpower_1234: return true;
        case SYM_GEN_loseEmpower_357: return true;
        case SYM_GEN_getHeat_1235: return true;
        case SYM_GEN_setHeat_1236: return true;
        case SYM_GEN_gainHeat_1237: return true;
        case SYM_GEN_loseHeat_355: return true;
        case SYM_GEN_getCold_1238: return true;
        case SYM_GEN_setCold_1239: return true;
        case SYM_GEN_gainCold_1240: return true;
        case SYM_GEN_loseCold_1241: return true;
        case SYM_GEN_getBuffDamageMod_1242: return true;
        case SYM_GEN_getBuffAccuracyMod_1243: return true;
        case SYM_GEN_getBaseMaxStamina_1244: return true;
        case SYM_GEN_getMaxBaseStamina_1245: return true;
        case SYM_GEN_getCurrentStamina_1246: return true;
        case SYM_GEN_setCurrentStamina_1247: return true;
        case SYM_GEN_getMissingStamina_1248: return true;
        case SYM_GEN_isFullStamina_1249: return true;
        case SYM_GEN_setMaxStamina_1250: return true;
        case SYM_GEN_giveMaxStamina_317: return true;
        case SYM_GEN_reduceMaxStamina_1251: return true;
        case SYM_GEN_gainMaxStaminaTemporary_1252: return true;
        case SYM_GEN_getStaminaRegeneration_1253: return true;
        case SYM_GEN_giveStaminaRegeneration_1254: return true;
        case SYM_GEN_getTotalStaminaUsage_1255: return true;
        case SYM_GEN_changeBaseMaxStamina_1256: return true;
        case SYM_GEN_recalculateMaxStamina_1257: return true;
        case SYM_GEN_getTemporaryMaxHealth_1258: return true;
        case SYM_GEN_setTemporaryMaxHealth_1259: return true;
        case SYM_GEN_reduceMaxHealth_1260: return true;
        case SYM_GEN_changeMaxHealthGain_1261: return true;
        case SYM_GEN_changeDamageReduction_1262: return true;
        case SYM_GEN_changeDamageResistance_1263: return true;
        case SYM_GEN_changeTypedDamageFactor_1264: return true;
        case SYM_GEN_changeEffectDamageFactor_1265: return true;
        case SYM_GEN_changeEmpowerDamage_1266: return true;
        case SYM_GEN_changePoisonCritChancePercent_1267: return true;
        case SYM_GEN_changeSpikesCritChancePercent_1268: return true;
        case SYM_GEN_useCritToken_186: return true;
        case SYM_GEN_useMana_334: return true;
        case SYM_GEN_changeProtectionChance_1269: return true;
        case SYM_GEN_changeBuffProtectionChance_1270: return true;
        case SYM_GEN_changeDebuffProtectionChance_1271: return true;
        case SYM_GEN_changeBuffNullifyChances_1272: return true;
        case SYM_GEN_changeDebuffNullifyChances_1273: return true;
        case SYM_GEN_addBattleRageDuration_1274: return true;
        case SYM_GEN_isVulnerable_1275: return true;
        case SYM_GEN_physicsTickCharacter_1276: return true;
        case SYM_GEN_tickPhysicsTimers_1277: return true;
        case SYM_GEN_tickBuffs_1278: return true;
        case SYM_GEN_rebuildTimerSeen_141: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreCharacter::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_setOpponent_1117: out = fn_setOpponent(args, argc); return true;
        case SYM_GEN_isPlayer_80: out = fn_isPlayer(args, argc); return true;
        case SYM_GEN_getName_236: out = fn_getName(args, argc); return true;
        case SYM_GEN_registerCharacterDied_1118: out = fn_registerCharacterDied(args, argc); return true;
        case SYM_GEN_clearCharacterDiedHandlers_1119: out = fn_clearCharacterDiedHandlers(args, argc); return true;
        case SYM_GEN_prepare_124: out = fn_prepare(args, argc); return true;
        case SYM_GEN_combatStart_129: out = fn_combatStart(args, argc); return true;
        case SYM_GEN_combatEnd_133: out = fn_combatEnd(args, argc); return true;
        case SYM_GEN_attackMovingForward_reset_1120: out = fn_attackMovingForward_reset(args, argc); return true;
        case SYM_GEN_cleanse_1121: out = fn_cleanse(args, argc); return true;
        case SYM_GEN_onTick_1122: out = fn_onTick(args, argc); return true;
        case SYM_GEN_playAttackAnimation_1123: out = fn_playAttackAnimation(args, argc); return true;
        case SYM_GEN_classAttackSoundCount_1124: out = fn_classAttackSoundCount(args, argc); return true;
        case SYM_GEN_classRoundSoundCount_1125: out = fn_classRoundSoundCount(args, argc); return true;
        case SYM_GEN_playActivateAnimation_1126: out = fn_playActivateAnimation(args, argc); return true;
        case SYM_GEN_randBuffLabelPos_1127: out = fn_randBuffLabelPos(args, argc); return true;
        case SYM_GEN_randBuffLabelDir_1128: out = fn_randBuffLabelDir(args, argc); return true;
        case SYM_GEN_randDmgNumberPos_1129: out = fn_randDmgNumberPos(args, argc); return true;
        case SYM_GEN_randDmgNumberDir_1130: out = fn_randDmgNumberDir(args, argc); return true;
        case SYM_GEN_randHealNumberPos_1131: out = fn_randHealNumberPos(args, argc); return true;
        case SYM_GEN_dealDamage_222: out = fn_dealDamage(args, argc); return true;
        case SYM_GEN_takeDamage_1132: out = fn_takeDamage(args, argc); return true;
        case SYM_GEN_spawnLabel_native_1133: out = fn_spawnLabel_native(args, argc); return true;
        case SYM_GEN_applySpikes_1134: out = fn_applySpikes(args, argc); return true;
        case SYM_GEN_applyVampirism_1135: out = fn_applyVampirism(args, argc); return true;
        case SYM_GEN_heal_329: out = fn_heal(args, argc); return true;
        case SYM_GEN_healToFull_1136: out = fn_healToFull(args, argc); return true;
        case SYM_GEN_reincarnate_1137: out = fn_reincarnate(args, argc); return true;
        case SYM_GEN_getCurrentHealth_1138: out = fn_getCurrentHealth(args, argc); return true;
        case SYM_GEN_getRelativeHealth_304: out = fn_getRelativeHealth(args, argc); return true;
        case SYM_GEN_getMissingHealth_1139: out = fn_getMissingHealth(args, argc); return true;
        case SYM_GEN_setCurrentHealth_1140: out = fn_setCurrentHealth(args, argc); return true;
        case SYM_GEN_loseHealth_1141: out = fn_loseHealth(args, argc); return true;
        case SYM_GEN_setMaxHealth_1142: out = fn_setMaxHealth(args, argc); return true;
        case SYM_GEN_giveMaxHealth_319: out = fn_giveMaxHealth(args, argc); return true;
        case SYM_GEN_getBaseMaxHealth_1143: out = fn_getBaseMaxHealth(args, argc); return true;
        case SYM_GEN_getMaxHealth_1144: out = fn_getMaxHealth(args, argc); return true;
        case SYM_GEN_applyTemporaryMaxHealthGain_1145: out = fn_applyTemporaryMaxHealthGain(args, argc); return true;
        case SYM_GEN_changeMaxHealthTemporary_1146: out = fn_changeMaxHealthTemporary(args, argc); return true;
        case SYM_GEN_getMaxStamina_1147: out = fn_getMaxStamina(args, argc); return true;
        case SYM_GEN_gainStamina_1148: out = fn_gainStamina(args, argc); return true;
        case SYM_GEN_addStamina_1149: out = fn_addStamina(args, argc); return true;
        case SYM_GEN_clampStamina_1150: out = fn_clampStamina(args, argc); return true;
        case SYM_GEN_fillUpStamina_302: out = fn_fillUpStamina(args, argc); return true;
        case SYM_GEN_useStamina_118: out = fn_useStamina(args, argc); return true;
        case SYM_GEN_drainStamina_119: out = fn_drainStamina(args, argc); return true;
        case SYM_GEN_setTemporaryMaxStamina_1151: out = fn_setTemporaryMaxStamina(args, argc); return true;
        case SYM_GEN_setTemporaryMaxHealthGain_1152: out = fn_setTemporaryMaxHealthGain(args, argc); return true;
        case SYM_GEN_death_1153: out = fn_death(args, argc); return true;
        case SYM_GEN_stun_332: out = fn_stun(args, argc); return true;
        case SYM_GEN_endStun_1154: out = fn_endStun(args, argc); return true;
        case SYM_GEN_isStunned_1155: out = fn_isStunned(args, argc); return true;
        case SYM_GEN_changeDodgeStacks_1156: out = fn_changeDodgeStacks(args, argc); return true;
        case SYM_GEN_changeCritResistance_1157: out = fn_changeCritResistance(args, argc); return true;
        case SYM_GEN_critResisted_1158: out = fn_critResisted(args, argc); return true;
        case SYM_GEN_gainCritResistStacks_1159: out = fn_gainCritResistStacks(args, argc); return true;
        case SYM_GEN_changeStunResistance_1160: out = fn_changeStunResistance(args, argc); return true;
        case SYM_GEN_stunResisted_1161: out = fn_stunResisted(args, argc); return true;
        case SYM_GEN_giveUnhealing_1162: out = fn_giveUnhealing(args, argc); return true;
        case SYM_GEN_reduceUnhealing_1163: out = fn_reduceUnhealing(args, argc); return true;
        case SYM_GEN_getUnhealing_1164: out = fn_getUnhealing(args, argc); return true;
        case SYM_GEN_getHealingEfficiency_1165: out = fn_getHealingEfficiency(args, argc); return true;
        case SYM_GEN_addHealingEfficiency_1166: out = fn_addHealingEfficiency(args, argc); return true;
        case SYM_GEN_reduceHealingEfficiency_1167: out = fn_reduceHealingEfficiency(args, argc); return true;
        case SYM_GEN_getCritTokens_184: out = fn_getCritTokens(args, argc); return true;
        case SYM_GEN_gainCritTokens_1168: out = fn_gainCritTokens(args, argc); return true;
        case SYM_GEN_changeDebuffResistStacks_1169: out = fn_changeDebuffResistStacks(args, argc); return true;
        case SYM_GEN_changeDebuffReflectStacks_1170: out = fn_changeDebuffReflectStacks(args, argc); return true;
        case SYM_GEN_changeBuffProtectStacks_1171: out = fn_changeBuffProtectStacks(args, argc); return true;
        case SYM_GEN_changeReflectChance_1028: out = fn_changeReflectChance(args, argc); return true;
        case SYM_GEN_changeAllDebuffsReflectChance_1172: out = fn_changeAllDebuffsReflectChance(args, argc); return true;
        case SYM_GEN_changeMeleeSpikesLimit_1173: out = fn_changeMeleeSpikesLimit(args, argc); return true;
        case SYM_GEN_changeRangedSpikesLimit_1174: out = fn_changeRangedSpikesLimit(args, argc); return true;
        case SYM_GEN_changeEffectSpikesLimit_1175: out = fn_changeEffectSpikesLimit(args, argc); return true;
        case SYM_GEN_changeMeleeVampirismLimit_1176: out = fn_changeMeleeVampirismLimit(args, argc); return true;
        case SYM_GEN_changeRangedVampirismLimit_1177: out = fn_changeRangedVampirismLimit(args, argc); return true;
        case SYM_GEN_getBonusFatigueDamage_1178: out = fn_getBonusFatigueDamage(args, argc); return true;
        case SYM_GEN_addFatigueDamage_1179: out = fn_addFatigueDamage(args, argc); return true;
        case SYM_GEN_takeFatigueDamage_1180: out = fn_takeFatigueDamage(args, argc); return true;
        case SYM_GEN_startBlindingLight_1181: out = fn_startBlindingLight(args, argc); return true;
        case SYM_GEN_endBlindingLight_1182: out = fn_endBlindingLight(args, argc); return true;
        case SYM_GEN_startBattleRage_1183: out = fn_startBattleRage(args, argc); return true;
        case SYM_GEN_endBattleRage_1184: out = fn_endBattleRage(args, argc); return true;
        case SYM_GEN_getClass_1185: out = fn_getClass(args, argc); return true;
        case SYM_GEN_isChibi_1186: out = fn_isChibi(args, argc); return true;
        case SYM_GEN_setClass_1187: out = fn_setClass(args, argc); return true;
        case SYM_GEN_setClassResource_1188: out = fn_setClassResource(args, argc); return true;
        case SYM_GEN_lose_1189: out = fn_lose(args, argc); return true;
        case SYM_GEN_win_1190: out = fn_win(args, argc); return true;
        case SYM_GEN_setStat_117: out = fn_setStat(args, argc); return true;
        case SYM_GEN_getStat_263: out = fn_getStat(args, argc); return true;
        case SYM_GEN_isBattleRaging_1191: out = fn_isBattleRaging(args, argc); return true;
        case SYM_GEN_startAutoRage_1192: out = fn_startAutoRage(args, argc); return true;
        case SYM_GEN_playBattleRageAnimation_1193: out = fn_playBattleRageAnimation(args, argc); return true;
        case SYM_GEN__setRageTimer_1194: out = fn__setRageTimer(args, argc); return true;
        case SYM_GEN__f32eng_1036: out = sf__f32eng(gd_ctx, args, argc); return true;
        case SYM_GEN_makeInvulnerable_1195: out = fn_makeInvulnerable(args, argc); return true;
        case SYM_GEN_makeVulnerable_1196: out = fn_makeVulnerable(args, argc); return true;
        case SYM_GEN_invulnerabilityEnded_1197: out = fn_invulnerabilityEnded(args, argc); return true;
        case SYM_GEN_setInvulnerable_1198: out = fn_setInvulnerable(args, argc); return true;
        case SYM_GEN_getStacks_1022: out = fn_getStacks(args, argc); return true;
        case SYM_GEN_getBuffStacks_1199: out = fn_getBuffStacks(args, argc); return true;
        case SYM_GEN_getDebuffStacks_1200: out = fn_getDebuffStacks(args, argc); return true;
        case SYM_GEN_setStacks_1023: out = fn_setStacks(args, argc); return true;
        case SYM_GEN_setStacksLogged_1201: out = fn_setStacksLogged(args, argc); return true;
        case SYM_GEN_gainStacks_1029: out = fn_gainStacks(args, argc); return true;
        case SYM_GEN_gainStacksTemporary_1202: out = fn_gainStacksTemporary(args, argc); return true;
        case SYM_GEN_loseStacks_1031: out = fn_loseStacks(args, argc); return true;
        case SYM_GEN_useStacks_1203: out = fn_useStacks(args, argc); return true;
        case SYM_GEN_changeResistChance_1025: out = fn_changeResistChance(args, argc); return true;
        case SYM_GEN_changeDebuffResistChances_1204: out = fn_changeDebuffResistChances(args, argc); return true;
        case SYM_GEN_changeResistStacks_1026: out = fn_changeResistStacks(args, argc); return true;
        case SYM_GEN_getBlock_206: out = fn_getBlock(args, argc); return true;
        case SYM_GEN_setBlock_1205: out = fn_setBlock(args, argc); return true;
        case SYM_GEN_gainBlock_1206: out = fn_gainBlock(args, argc); return true;
        case SYM_GEN_loseBlock_208: out = fn_loseBlock(args, argc); return true;
        case SYM_GEN_getSpikes_1207: out = fn_getSpikes(args, argc); return true;
        case SYM_GEN_setSpikes_1208: out = fn_setSpikes(args, argc); return true;
        case SYM_GEN_gainSpikes_1209: out = fn_gainSpikes(args, argc); return true;
        case SYM_GEN_loseSpikes_340: out = fn_loseSpikes(args, argc); return true;
        case SYM_GEN_getVampirism_1210: out = fn_getVampirism(args, argc); return true;
        case SYM_GEN_setVampirism_1211: out = fn_setVampirism(args, argc); return true;
        case SYM_GEN_gainVampirism_1212: out = fn_gainVampirism(args, argc); return true;
        case SYM_GEN_loseVampirism_343: out = fn_loseVampirism(args, argc); return true;
        case SYM_GEN_getPoison_1213: out = fn_getPoison(args, argc); return true;
        case SYM_GEN_setPoison_1214: out = fn_setPoison(args, argc); return true;
        case SYM_GEN_gainPoison_1215: out = fn_gainPoison(args, argc); return true;
        case SYM_GEN_losePoison_1216: out = fn_losePoison(args, argc); return true;
        case SYM_GEN_getRegeneration_1217: out = fn_getRegeneration(args, argc); return true;
        case SYM_GEN_setRegeneration_1218: out = fn_setRegeneration(args, argc); return true;
        case SYM_GEN_gainRegeneration_1219: out = fn_gainRegeneration(args, argc); return true;
        case SYM_GEN_loseRegeneration_1220: out = fn_loseRegeneration(args, argc); return true;
        case SYM_GEN_getLucky_1221: out = fn_getLucky(args, argc); return true;
        case SYM_GEN_setLucky_1222: out = fn_setLucky(args, argc); return true;
        case SYM_GEN_gainLucky_1223: out = fn_gainLucky(args, argc); return true;
        case SYM_GEN_loseLucky_350: out = fn_loseLucky(args, argc); return true;
        case SYM_GEN_getBlind_1224: out = fn_getBlind(args, argc); return true;
        case SYM_GEN_setBlind_1225: out = fn_setBlind(args, argc); return true;
        case SYM_GEN_gainBlind_1226: out = fn_gainBlind(args, argc); return true;
        case SYM_GEN_loseBlind_1227: out = fn_loseBlind(args, argc); return true;
        case SYM_GEN_getMana_1228: out = fn_getMana(args, argc); return true;
        case SYM_GEN_setMana_1229: out = fn_setMana(args, argc); return true;
        case SYM_GEN_gainMana_1230: out = fn_gainMana(args, argc); return true;
        case SYM_GEN_loseMana_1231: out = fn_loseMana(args, argc); return true;
        case SYM_GEN_getEmpower_1232: out = fn_getEmpower(args, argc); return true;
        case SYM_GEN_setEmpower_1233: out = fn_setEmpower(args, argc); return true;
        case SYM_GEN_gainEmpower_1234: out = fn_gainEmpower(args, argc); return true;
        case SYM_GEN_loseEmpower_357: out = fn_loseEmpower(args, argc); return true;
        case SYM_GEN_getHeat_1235: out = fn_getHeat(args, argc); return true;
        case SYM_GEN_setHeat_1236: out = fn_setHeat(args, argc); return true;
        case SYM_GEN_gainHeat_1237: out = fn_gainHeat(args, argc); return true;
        case SYM_GEN_loseHeat_355: out = fn_loseHeat(args, argc); return true;
        case SYM_GEN_getCold_1238: out = fn_getCold(args, argc); return true;
        case SYM_GEN_setCold_1239: out = fn_setCold(args, argc); return true;
        case SYM_GEN_gainCold_1240: out = fn_gainCold(args, argc); return true;
        case SYM_GEN_loseCold_1241: out = fn_loseCold(args, argc); return true;
        case SYM_GEN_getBuffDamageMod_1242: out = fn_getBuffDamageMod(args, argc); return true;
        case SYM_GEN_getBuffAccuracyMod_1243: out = fn_getBuffAccuracyMod(args, argc); return true;
        case SYM_GEN_getBaseMaxStamina_1244: out = fn_getBaseMaxStamina(args, argc); return true;
        case SYM_GEN_getMaxBaseStamina_1245: out = fn_getMaxBaseStamina(args, argc); return true;
        case SYM_GEN_getCurrentStamina_1246: out = fn_getCurrentStamina(args, argc); return true;
        case SYM_GEN_setCurrentStamina_1247: out = fn_setCurrentStamina(args, argc); return true;
        case SYM_GEN_getMissingStamina_1248: out = fn_getMissingStamina(args, argc); return true;
        case SYM_GEN_isFullStamina_1249: out = fn_isFullStamina(args, argc); return true;
        case SYM_GEN_setMaxStamina_1250: out = fn_setMaxStamina(args, argc); return true;
        case SYM_GEN_giveMaxStamina_317: out = fn_giveMaxStamina(args, argc); return true;
        case SYM_GEN_reduceMaxStamina_1251: out = fn_reduceMaxStamina(args, argc); return true;
        case SYM_GEN_gainMaxStaminaTemporary_1252: out = fn_gainMaxStaminaTemporary(args, argc); return true;
        case SYM_GEN_getStaminaRegeneration_1253: out = fn_getStaminaRegeneration(args, argc); return true;
        case SYM_GEN_giveStaminaRegeneration_1254: out = fn_giveStaminaRegeneration(args, argc); return true;
        case SYM_GEN_getTotalStaminaUsage_1255: out = fn_getTotalStaminaUsage(args, argc); return true;
        case SYM_GEN_changeBaseMaxStamina_1256: out = fn_changeBaseMaxStamina(args, argc); return true;
        case SYM_GEN_recalculateMaxStamina_1257: out = fn_recalculateMaxStamina(args, argc); return true;
        case SYM_GEN_getTemporaryMaxHealth_1258: out = fn_getTemporaryMaxHealth(args, argc); return true;
        case SYM_GEN_setTemporaryMaxHealth_1259: out = fn_setTemporaryMaxHealth(args, argc); return true;
        case SYM_GEN_reduceMaxHealth_1260: out = fn_reduceMaxHealth(args, argc); return true;
        case SYM_GEN_changeMaxHealthGain_1261: out = fn_changeMaxHealthGain(args, argc); return true;
        case SYM_GEN_changeDamageReduction_1262: out = fn_changeDamageReduction(args, argc); return true;
        case SYM_GEN_changeDamageResistance_1263: out = fn_changeDamageResistance(args, argc); return true;
        case SYM_GEN_changeTypedDamageFactor_1264: out = fn_changeTypedDamageFactor(args, argc); return true;
        case SYM_GEN_changeEffectDamageFactor_1265: out = fn_changeEffectDamageFactor(args, argc); return true;
        case SYM_GEN_changeEmpowerDamage_1266: out = fn_changeEmpowerDamage(args, argc); return true;
        case SYM_GEN_changePoisonCritChancePercent_1267: out = fn_changePoisonCritChancePercent(args, argc); return true;
        case SYM_GEN_changeSpikesCritChancePercent_1268: out = fn_changeSpikesCritChancePercent(args, argc); return true;
        case SYM_GEN_useCritToken_186: out = fn_useCritToken(args, argc); return true;
        case SYM_GEN_useMana_334: out = fn_useMana(args, argc); return true;
        case SYM_GEN_changeProtectionChance_1269: out = fn_changeProtectionChance(args, argc); return true;
        case SYM_GEN_changeBuffProtectionChance_1270: out = fn_changeBuffProtectionChance(args, argc); return true;
        case SYM_GEN_changeDebuffProtectionChance_1271: out = fn_changeDebuffProtectionChance(args, argc); return true;
        case SYM_GEN_changeBuffNullifyChances_1272: out = fn_changeBuffNullifyChances(args, argc); return true;
        case SYM_GEN_changeDebuffNullifyChances_1273: out = fn_changeDebuffNullifyChances(args, argc); return true;
        case SYM_GEN_addBattleRageDuration_1274: out = fn_addBattleRageDuration(args, argc); return true;
        case SYM_GEN_isVulnerable_1275: out = fn_isVulnerable(args, argc); return true;
        case SYM_GEN_physicsTickCharacter_1276: out = fn_physicsTickCharacter(args, argc); return true;
        case SYM_GEN_tickPhysicsTimers_1277: out = fn_tickPhysicsTimers(args, argc); return true;
        case SYM_GEN_tickBuffs_1278: out = fn_tickBuffs(args, argc); return true;
        case SYM_GEN_rebuildTimerSeen_141: out = fn_rebuildTimerSeen(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreCharacter::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN__f32eng_1036: out = sf__f32eng(gd_ctx, args, argc); return true;
        default: break;
    }
    return false;
}
gd::GdVal Gd__gd_core__CoreCharacter::fn__init(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__ctx = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__playerId = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv__playerId = gd::gd_coerce_int(lv__playerId);
    this->f_ctx = lv__ctx;
    this->f_playerId = gd::gd_coerce_int(lv__playerId);
    this->f_accuracyRng = ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_BalancedRng_1653), gd::SYM_new, _ca, 1); })();
    this->f_critRng = ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_BalancedRng_1653), gd::SYM_new, _ca, 1); })();
    this->f_critResistanceRng = ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_BalancedRng_1653), gd::SYM_new, _ca, 1); })();
    this->f_stunResistanceRng = ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_BalancedRng_1653), gd::SYM_new, _ca, 1); })();
    this->f_inventory = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreGrid), gd::SYM_new, _ca, 1); })();
    this->f_INVENTORY = this->f_inventory;
    this->f_spikeDamageSource = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0);
    gd::set_prop(gd_ctx, this->f_spikeDamageSource, SYM_GEN__rng_1457, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Spikes_2565), gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, this->f_spikeDamageSource, SYM_GEN_init_1021, _ca, 3); })();
    gd::set_prop(gd_ctx, this->f_spikeDamageSource, SYM_GEN_flags_1456, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_chipDamageFlags_1445), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Flags_1474), SYM_GEN_CanCrit_2685)));
    this->f_poisonDamageSource = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0);
    gd::set_prop(gd_ctx, this->f_poisonDamageSource, SYM_GEN__rng_1457, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Poison_2567), gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, this->f_poisonDamageSource, SYM_GEN_init_1021, _ca, 3); })();
    gd::set_prop(gd_ctx, this->f_poisonDamageSource, SYM_GEN_flags_1456, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_chipDamageFlags_1445), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Flags_1474), SYM_GEN_CanCrit_2685)));
    {
        gd::GdVal _t572 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getStacks_1022, nullptr, 0));
        gd::GdArr* _t573 = (_t572.kind == gd::GdVal::Kind::Arr) ? _t572.arr : nullptr;
        uint32_t _len__t574 = _t573 ? _t573->len : 0u;
        for (uint32_t _t574 = 0; _t574 < _len__t574; ++_t574) {
            gd::GdVal lv_stackType = _t573->data[_t574];
            gd::GdVal lv_buff = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreBuff), gd::SYM_new, nullptr, 0);
            gd::GdVal lv__stack_type_name = gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "unknown", 7u));
            {
                gd::GdVal _t575 = gd::gd_iter_seq(gd_ctx.arena, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366));
                gd::GdArr* _t576 = (_t575.kind == gd::GdVal::Kind::Arr) ? _t575.arr : nullptr;
                uint32_t _len__t577 = _t576 ? _t576->len : 0u;
                for (uint32_t _t577 = 0; _t577 < _len__t577; ++_t577) {
                    gd::GdVal lv__k = _t576->data[_t577];
                    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_index(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), lv__k), lv_stackType)))) {
                        lv__stack_type_name = lv__k;
                        break;
                    }
                }
            }
            (void)([&]() { gd::GdVal _ca[] = {lv_stackType, gd::GdVal::from_obj(this), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_", 10u)), gd::call_method(gd_ctx, lv__stack_type_name, gd::SYM_to_lower, nullptr, 0)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "_changed", 8u)))}; return gd::call_method(gd_ctx, lv_buff, SYM_GEN_init_1021, _ca, 3); })();
            { gd::GdVal _t578 = this->f_buffs; gd::GdVal _t579 = lv_stackType; gd::set_index(gd_ctx, _t578, _t579, lv_buff); }
        }
    }
    this->f_curHealth = gd::gd_coerce_float(this->f_maxHealth);
    this->f_baseMaxStamina = gd::gd_coerce_float(this->f_maxStamina);
    this->f_curStamina = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_staminaRegen = gd::gd_coerce_float(this->f_baseStaminaRegen);
    {
        gd::GdVal _t580 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), gd::SYM_values, nullptr, 0));
        gd::GdArr* _t581 = (_t580.kind == gd::GdVal::Kind::Arr) ? _t580.arr : nullptr;
        uint32_t _len__t582 = _t581 ? _t581->len : 0u;
        for (uint32_t _t582 = 0; _t582 < _len__t582; ++_t582) {
            gd::GdVal lv_type = _t581->data[_t582];
            { gd::GdVal _t583 = this->f_typedDamageFactors; gd::GdVal _t584 = lv_type; gd::set_index(gd_ctx, _t583, _t584, gd::GdVal::from_float(0.0)); }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setOpponent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__opponent = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_opponent = lv__opponent;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_isPlayer(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_eq(this->f_playerId, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_ID_1279), SYM_GEN_PLAYER_2540)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getName(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_index(gd_ctx, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Player", 6u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Opponent", 8u))})), this->f_playerId);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_registerCharacterDied(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_handler = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_handler}; return gd::call_method(gd_ctx, this->f_character_died_handlers, gd::SYM_push_back, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_clearCharacterDiedHandlers(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_character_died_handlers, gd::SYM_clear, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_staminaRegen = gd::gd_coerce_float(this->f_baseStaminaRegen);
    gd::GdVal lv_bonusHealth = gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxHealth_1144, nullptr, 0), gd::gd_div(gd_ctx, gd::gd_sub(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_custom_health_multiplier_1388), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(100.0)));
    (void)([&]() { gd::GdVal _ca[] = {lv_bonusHealth}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeMaxHealthTemporary_1146, _ca, 1); })();
    (void)gd::call_method(gd_ctx, this->f_accuracyRng, SYM_GEN_reset_1024, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_critRng, SYM_GEN_reset_1024, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_critResistanceRng, SYM_GEN_reset_1024, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_stunResistanceRng, SYM_GEN_reset_1024, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_below_master_1385)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_lobbies_mode_1387)))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_playerId, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_ID_1279), SYM_GEN_PLAYER_2540))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(0.2))}; return gd::call_method(gd_ctx, this->f_accuracyRng, SYM_GEN_setBias_1663, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(0.2))}; return gd::call_method(gd_ctx, this->f_critRng, SYM_GEN_setBias_1663, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.2)}; return gd::call_method(gd_ctx, this->f_accuracyRng, SYM_GEN_setBias_1663, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.2)}; return gd::call_method(gd_ctx, this->f_critRng, SYM_GEN_setBias_1663, _ca, 1); })();
        }
    }
    this->f_autoRageItem = gd::GdVal::null();
    gd::GdVal lv_hasBattleRageStarter = gd::GdVal::from_bool(false);
    {
        gd::GdVal _t585 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1512, nullptr, 0));
        gd::GdArr* _t586 = (_t585.kind == gd::GdVal::Kind::Arr) ? _t585.arr : nullptr;
        uint32_t _len__t587 = _t586 ? _t586->len : 0u;
        for (uint32_t _t587 = 0; _t587 < _len__t587; ++_t587) {
            gd::GdVal lv_item = _t586->data[_t587];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Tag_858), SYM_GEN_BattleRage_2686)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasTag_83, _ca, 1); })())) {
                lv_hasBattleRageStarter = gd::GdVal::from_bool(true);
                break;
            }
        }
    }
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_hasBattleRageStarter)))) {
        gd::GdVal lv_battleRageItems = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
        {
            gd::GdVal _t588 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItemsAndGems_1513, nullptr, 0));
            gd::GdArr* _t589 = (_t588.kind == gd::GdVal::Kind::Arr) ? _t588.arr : nullptr;
            uint32_t _len__t590 = _t589 ? _t589->len : 0u;
            for (uint32_t _t590 = 0; _t590 < _len__t590; ++_t590) {
                gd::GdVal lv_item = _t589->data[_t590];
                if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isBattleRageItem_87, nullptr, 0))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, lv_battleRageItems, gd::SYM_push_back, _ca, 1); })();
                }
            }
        }
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_battleRageItems, gd::SYM_empty, nullptr, 0))))) {
            this->f_autoRageItem = ([&]() { gd::GdVal _ca[] = {lv_battleRageItems, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Character.gd:327", 16u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_pickRandomEngine_1652, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_combatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_stunnedDuration = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_tickCounter = gd::GdVal::from_int(0LL);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_autoRageItem, gd::GdVal::null())))) {
        this->f__autoRage_left = gd::gd_coerce_float(Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_AUTO_RAGE_DELAY_1044));
        this->f__autoRage_active = gd::GdVal::from_bool(true);
    }
    this->f__tick_timer_left = gd::GdVal::from_float(1.0);
    this->f__tick_timer_active = gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_combatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_attackMovingForward_reset_1120, nullptr, 0);
    {
        gd::GdVal _t591 = gd::gd_iter_seq(gd_ctx.arena, this->f_buffs);
        gd::GdArr* _t592 = (_t591.kind == gd::GdVal::Kind::Arr) ? _t591.arr : nullptr;
        uint32_t _len__t593 = _t592 ? _t592->len : 0u;
        for (uint32_t _t593 = 0; _t593 < _len__t593; ++_t593) {
            gd::GdVal lv_buffType = _t592->data[_t593];
            (void)gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_buffType), SYM_GEN_combatEnd_133, nullptr, 0);
        }
    }
    this->f__rage_left = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f__rage_active = gd::GdVal::from_bool(false);
    this->f__rage_eng = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f__rage_seen = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f__autoRage_left = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f__autoRage_active = gd::GdVal::from_bool(false);
    this->f__invul_left = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f__invul_active = gd::GdVal::from_bool(false);
    this->f__invul_eng = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f__invul_seen = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_attackMovingForward_reset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_cleanse(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_isDead = gd::GdVal::from_bool(false);
    this->f_temporaryMaxHealth = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    this->f_temporaryMaxHealthGain = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_staminaRegen = gd::gd_coerce_float(this->f_baseStaminaRegen);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_healToFull_1136, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setTemporaryMaxStamina_1151, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_fillUpStamina_302, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_endStun_1154, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setBlock_1205, _ca, 1); })();
    {
        gd::GdVal _t594 = gd::gd_iter_seq(gd_ctx.arena, this->f_buffs);
        gd::GdArr* _t595 = (_t594.kind == gd::GdVal::Kind::Arr) ? _t594.arr : nullptr;
        uint32_t _len__t596 = _t595 ? _t595->len : 0u;
        for (uint32_t _t596 = 0; _t596 < _len__t596; ++_t596) {
            gd::GdVal lv_buffType = _t595->data[_t596];
            (void)gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_buffType), SYM_GEN_reset_1024, nullptr, 0);
        }
    }
    this->f_invulnerable = gd::GdVal::from_bool(false);
    this->f_damageResistance = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_damageReduction = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_dodgeStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_critResistance = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_critResistStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_stunResistance = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_unhealingAmount = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_healingEfficiency = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_critTokens = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_debuffResistStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_debuffReflectStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_buffProtectStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_battleRageBonusDur = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusFatigueDamage = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_blindingLightActive = gd::GdVal::from_bool(false);
    this->f_meleeSpikesLimit = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_rangedSpikesLimit = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_effectSpikesLimit = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_meleeVampirismLimit = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_rangedVampirismLimit = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_empowerDamage = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    {
        gd::GdVal _t597 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), gd::SYM_values, nullptr, 0));
        gd::GdArr* _t598 = (_t597.kind == gd::GdVal::Kind::Arr) ? _t597.arr : nullptr;
        uint32_t _len__t599 = _t598 ? _t598->len : 0u;
        for (uint32_t _t599 = 0; _t599 < _len__t599; ++_t599) {
            gd::GdVal lv_damageType = _t598->data[_t599];
            { gd::GdVal _t600 = this->f_typedDamageFactors; gd::GdVal _t601 = lv_damageType; gd::set_index(gd_ctx, _t600, _t601, gd::GdVal::from_float(0.0)); }
        }
    }
    gd::set_prop(gd_ctx, this->f_poisonDamageSource, SYM_GEN_critChancePercent_15, gd::GdVal::from_int(0LL));
    gd::set_prop(gd_ctx, this->f_spikeDamageSource, SYM_GEN_critChancePercent_15, gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_onTick(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::gd_mod(gd_ctx, this->f_tickCounter, gd::GdVal::from_int(2LL)), gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_regen = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getRegeneration_1217, nullptr, 0);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_regen, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_regen, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Regeneration_2569)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Regeneration_2569)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_activateBuffCounter_1532, _ca, 2); })();
        }
    }
    else {
        gd::GdVal lv_poison = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getPoison_1213, nullptr, 0);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_poison, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_poison}; return gd::call_method(gd_ctx, this->f_poisonDamageSource, SYM_GEN_setDamage_1460, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_poisonDamageSource}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_takeDamage_1132, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Poison_2567)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_activateBuffCounter_1532, _ca, 2); })();
        }
    }
    this->f_tickCounter = gd::gd_add(gd_ctx, this->f_tickCounter, gd::GdVal::from_int(1LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_playAttackAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(100.0), gd::GdVal::from_float(160.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    if (gd::gd_truth(this->f_attack_moving_forward)) {
        return gd::GdVal::null();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), gd::GdVal::from_int(2LL)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randi_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.8), gd::GdVal::from_float(1.2)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1382), this->f_attack_sound_ready_time)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), gd::gd_sub(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_classAttackSoundCount_1124, nullptr, 0), gd::GdVal::from_int(1LL))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randi_range, _ca, 2); })();
        this->f_attack_sound_ready_time = gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_time_1382), gd::GdVal::from_float(0.1));
    }
    this->f_attack_moving_forward = gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_classAttackSoundCount(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_characterClass}; return gd::call_method(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_CLASS_SOUND_COUNTS_1116), gd::SYM_has, _ca, 1); })())))) {
        (void)gd::GdVal::null();
    }
    return gd::get_index(gd_ctx, gd::get_index(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_CLASS_SOUND_COUNTS_1116), this->f_characterClass), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attack", 6u)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_classRoundSoundCount(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_win = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_win = gd::gd_coerce_bool(lv_win);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_characterClass}; return gd::call_method(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_CLASS_SOUND_COUNTS_1116), gd::SYM_has, _ca, 1); })())))) {
        (void)gd::GdVal::null();
    }
    return gd::get_index(gd_ctx, gd::get_index(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_CLASS_SOUND_COUNTS_1116), this->f_characterClass), (gd::gd_truth(lv_win) ? (gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "win", 3u))) : (gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lose", 4u)))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_playActivateAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_attack_moving_forward)) {
        return gd::GdVal::null();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    this->f_attack_moving_forward = gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_randBuffLabelPos(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(60.0)), gd::GdVal::from_float(60.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(40.0)), gd::GdVal::from_float(40.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_randBuffLabelDir(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(75.0)), gd::gd_neg(gd::GdVal::from_float(120.0))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_randDmgNumberPos(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(50.0)), gd::GdVal::from_float(50.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(70.0)), gd::GdVal::from_float(70.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_randDmgNumberDir(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(0.3665191429188092)), gd::gd_neg(gd::GdVal::from_float(0.05235987755982988))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_randHealNumberPos(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(50.0)), gd::GdVal::from_float(50.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(70.0)), gd::GdVal::from_float(70.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_dealDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageSource = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playAttackAnimation_1123, nullptr, 0);
    gd::GdVal lv_res = ([&]() { gd::GdVal _ca[] = {lv_damageSource, lv_triggerEvent}; return gd::call_method(gd_ctx, this->f_opponent, SYM_GEN_takeDamage_1132, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_applyVampirism_1135, _ca, 1); })();
    return lv_res;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_takeDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageSource = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_damageRes = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageResult), gd::SYM_new, nullptr, 0);
    lv_damageSource = ([&]() { gd::GdVal _ca[] = {lv_damageSource}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_fromDamageSource_1458, _ca, 1); })();
    gd::set_prop(gd_ctx, lv_damageSource, SYM_GEN__rng_1457, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377));
    gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24, lv_damageSource);
    (void)gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_reset_1024, nullptr, 0);
    if (gd::gd_truth(this->f_isDead)) {
        return lv_damageRes;
    }
    gd::GdVal lv_item = gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(gd::get_prop(gd_ctx, lv_damageSource, SYM_GEN_origin_1455), &META_Gd__gd_core__CoreItem)))) {
        lv_item = gd::get_prop(gd_ctx, lv_damageSource, SYM_GEN_origin_1455);
    }
    gd::GdVal lv_attackEffectCount = gd::GdVal::from_int(1LL);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null())))) {
        lv_attackEffectCount = gd::gd_add(gd_ctx, lv_attackEffectCount, gd::call_method(gd_ctx, lv_item, SYM_GEN_rollDoubleAttackEffect_189, nullptr, 0));
    }
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_canMiss_1466, nullptr, 0))) {
        gd::GdVal lv_accuracy = gd::get_prop(gd_ctx, lv_damageSource, SYM_GEN_accuracy_1454);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u)))))) {
            (void)gd::GdVal::null();
        }
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_hit_1429, ([&]() { gd::GdVal _ca[] = {lv_accuracy}; return gd::call_method(gd_ctx, this->f_accuracyRng, SYM_GEN_rollPercent_1664, _ca, 1); })());
        if (gd::gd_truth((gd::gd_truth(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_hit_1429)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_dodgeStacks, gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_int(1LL))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeDodgeStacks_1156, _ca, 1); })();
            gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_hit_1429, gd::GdVal::from_bool(false));
        }
    }
    else {
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_hit_1429, gd::GdVal::from_bool(true));
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(50.0)), gd::GdVal::from_float(50.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(70.0)), gd::GdVal::from_float(70.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(0.3665191429188092)), gd::gd_neg(gd::GdVal::from_float(0.05235987755982988))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_isAttack_1469, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_damageRes}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_preDealDamage_early_224, _ca, 1); })();
        if (gd::gd_truth(gd::get_prop(gd_ctx, lv_item, SYM_GEN_hasPreDealDamageEarlyEffect_64))) {
            {
                gd::GdVal _t602 = gd::gd_iter_seq(gd_ctx.arena, lv_attackEffectCount);
                gd::GdArr* _t603 = (_t602.kind == gd::GdVal::Kind::Arr) ? _t602.arr : nullptr;
                uint32_t _len__t604 = _t603 ? _t603->len : 0u;
                for (uint32_t _t604 = 0; _t604 < _len__t604; ++_t604) {
                    gd::GdVal lv_i = _t603->data[_t604];
                    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onPreDealDamage_early", 21u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::call_method(gd_ctx, lv_item, SYM_GEN__behavior_call_506, _ca, 2); })();
                }
            }
        }
    }
    if (gd::gd_truth(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_hit_1429))) {
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427), gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_randDamage_161, nullptr, 0)));
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Fatigue_2687)}; return gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_hasType_81, _ca, 1); })())) {
            gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427, gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427), this->f_bonusFatigueDamage));
        }
        if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_canCrit_1468, nullptr, 0))) {
            gd::GdVal lv_critical = gd::GdVal::from_bool(false);
            gd::GdVal lv_critChancePercent = gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_getCritChancePercent_180, nullptr, 0);
            if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_critChancePercent, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_critChancePercent}; return gd::call_method(gd_ctx, this->f_critRng, SYM_GEN_rollPercent_1664, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
                lv_critical = gd::GdVal::from_bool(true);
            }
            if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_critical_1430)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null())))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, lv_item, SYM_GEN_getCritTokens_184, nullptr, 0), gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
                (void)gd::call_method(gd_ctx, lv_item, SYM_GEN_useCritToken_186, nullptr, 0);
                lv_critical = gd::GdVal::from_bool(true);
            }
            if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_critical_1430)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, this->f_opponent, SYM_GEN_getCritTokens_184, nullptr, 0), gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
                (void)gd::call_method(gd_ctx, this->f_opponent, SYM_GEN_useCritToken_186, nullptr, 0);
                lv_critical = gd::GdVal::from_bool(true);
            }
            if (gd::gd_truth(lv_critical)) {
                if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_critResisted_1158, nullptr, 0))) {
                    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_randBuffLabelPos_1127, nullptr, 0);
                    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_randBuffLabelDir_1128, nullptr, 0);
                    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_CriticalResisted_2688), gd::GdVal::null()}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_spawnBuffLabel_1545, _ca, 2); })();
                }
                else {
                    (void)gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_makeCritical_1434, nullptr, 0);
                }
            }
        }
        gd::GdVal lv_activeDmgResi = gd::gd_clamp(gd::gd_div(gd_ctx, this->f_damageResistance, gd::GdVal::from_int(100LL)), gd::gd_neg(gd::GdVal::from_int(10LL)), gd::GdVal::from_int(1LL));
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427, gd::gd_round(gd::gd_mul(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427), gd::gd_sub(gd::GdVal::from_float(1.0), lv_activeDmgResi))));
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_isAttack_1469, nullptr, 0))) {
            gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427, gd::gd_sub(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427), this->f_damageReduction));
        }
        if (gd::gd_truth(this->f_invulnerable)) {
            gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427, gd::GdVal::from_int(0LL));
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "pre_take_damage", 15u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitSignal_1501, _ca, 3); })();
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427, gd::gd_sub(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageReduction_1063)));
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427, gd::gd_max(gd::GdVal::from_int(0LL), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427)));
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_isAttack_1469, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_damageRes}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_preDealDamage_late_225, _ca, 1); })();
            if (gd::gd_truth(gd::get_prop(gd_ctx, lv_item, SYM_GEN_hasPreDealDamageLateEffect_65))) {
                {
                    gd::GdVal _t605 = gd::gd_iter_seq(gd_ctx.arena, lv_attackEffectCount);
                    gd::GdArr* _t606 = (_t605.kind == gd::GdVal::Kind::Arr) ? _t605.arr : nullptr;
                    uint32_t _len__t607 = _t606 ? _t606->len : 0u;
                    for (uint32_t _t607 = 0; _t607 < _len__t607; ++_t607) {
                        gd::GdVal lv_i = _t606->data[_t607];
                        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onPreDealDamage_late", 20u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::call_method(gd_ctx, lv_item, SYM_GEN__behavior_call_506, _ca, 2); })();
                    }
                }
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "pre_take_damage_late", 20u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitSignal_1501, _ca, 3); })();
        gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1428, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427));
        if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_canBeBlocked_1467, nullptr, 0))) {
            gd::GdVal lv_curBlock = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_206, nullptr, 0);
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427), lv_curBlock)))) {
                gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1428, gd::gd_sub(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1428), lv_curBlock));
                (void)([&]() { gd::GdVal _ca[] = {lv_curBlock}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseBlock_208, _ca, 1); })();
            }
            else {
                (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseBlock_208, _ca, 1); })();
                gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1428, gd::GdVal::from_int(0LL));
            }
        }
        this->f_curHealth = gd::gd_coerce_float(gd::gd_sub(this->f_curHealth, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1428)));
        if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_wasCriticalHit_1433, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_CriticalDamage_2689), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427), lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_spawnLabel_native_1133, _ca, 3); })();
        }
        else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Fatigue_2687)}; return gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_hasType_81, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Fatigue_2687), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427), lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_spawnLabel_native_1133, _ca, 3); })();
        }
        else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Poison_2567)}; return gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_hasType_81, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Poison_2567), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427), lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_spawnLabel_native_1133, _ca, 3); })();
        }
        else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Spikes_2565)}; return gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_hasType_81, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Spikes_2565), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427), lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_spawnLabel_native_1133, _ca, 3); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_DealDamage_2690), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427), lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_spawnLabel_native_1133, _ca, 3); })();
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_damage_anim_current, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Poison", 6u)))))) {
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1428), gd::GdVal::from_int(0LL))))) {
                this->f_damage_anim_current = gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Block", 5u));
            }
            else if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Fatigue_2687)}; return gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_hasType_81, _ca, 1); })())) {
                this->f_damage_anim_current = gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Fatigue", 7u));
            }
            else {
                this->f_damage_anim_current = gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Hit", 3u));
            }
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Fatigue_2687)}; return gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_hasType_81, _ca, 1); })()) ? (gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Fatigue", 7u))) : (gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Hit", 3u))))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_damageAnimation_1548, _ca, 2); })();
        }
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_MissedAttack_2691), gd::GdVal::from_int(0LL), lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_spawnLabel_native_1133, _ca, 3); })();
    }
    gd::GdVal lv_event = gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null())))) {
        lv_event = ([&]() { gd::GdVal _ca[] = {lv_damageRes, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_createEvent_Attack_1329, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dealt_damage_signal_placeholder", 31u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitSignal_1501, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_damageRes}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_dealtDamage_226, _ca, 1); })();
    }
    else {
        lv_event = ([&]() { gd::GdVal _ca[] = {lv_damageRes, gd::get_prop(gd_ctx, this->f_opponent, SYM_GEN_playerId_1046), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_createEvent_Damage_1330, _ca, 3); })();
    }
    gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426, lv_event);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_attacked", 18u)), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitEvent_1502, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_damaged", 17u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_healthDamage_1428), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitSignal_1501, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_onHealthChangedUI_1550, _ca, 1); })();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_damageSource, SYM_GEN_isAttack_1469, nullptr, 0))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::get_prop(gd_ctx, lv_item, SYM_GEN_hasDealtDamageEffect_66))) : gd::GdVal::from_bool(false)))) {
        {
            gd::GdVal _t608 = gd::gd_iter_seq(gd_ctx.arena, lv_attackEffectCount);
            gd::GdArr* _t609 = (_t608.kind == gd::GdVal::Kind::Arr) ? _t608.arr : nullptr;
            uint32_t _len__t610 = _t609 ? _t609->len : 0u;
            for (uint32_t _t610 = 0; _t610 < _len__t610; ++_t610) {
                gd::GdVal lv_i = _t609->data[_t610];
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDealtDamage", 13u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_damageRes}))}; return gd::call_method(gd_ctx, lv_item, SYM_GEN__behavior_call_506, _ca, 2); })();
            }
        }
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(this->f_curHealth, gd::GdVal::from_int(0LL))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_death_1153, nullptr, 0);
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_damageRes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_applySpikes_1134, _ca, 1); })();
    return lv_damageRes;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_spawnLabel_native(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    gd::GdVal lv_damage = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_damage = gd::gd_coerce_int(lv_damage);
    gd::GdVal lv_item = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(10.0)), gd::GdVal::from_float(10.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(10.0)), gd::GdVal::from_float(10.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_type, lv_damage, lv_item}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_spawnLabel_character_1540, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_applySpikes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getSpikes_1207, nullptr, 0), gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_canTriggerSpikes_1441, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv_spikesLimit = gd::GdVal::from_float(0.0);
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Ranged_2670)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_hasType_81, _ca, 1); })())) {
            lv_spikesLimit = gd::gd_coerce_float(this->f_rangedSpikesLimit);
        }
        else {
            lv_spikesLimit = gd::gd_coerce_float(this->f_meleeSpikesLimit);
        }
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Effect_2559)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_hasType_81, _ca, 1); })())) {
            lv_spikesLimit = gd::gd_coerce_float(gd::gd_max(this->f_effectSpikesLimit, lv_spikesLimit));
        }
        gd::GdVal lv_spikeDam = gd::gd_min(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getSpikes_1207, nullptr, 0), gd::gd_round(gd::gd_mul(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427), lv_spikesLimit)));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_spikeDam, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_spikeDam}; return gd::call_method(gd_ctx, this->f_spikeDamageSource, SYM_GEN_setDamage_1460, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_spikeDamageSource, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, this->f_opponent, SYM_GEN_takeDamage_1132, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Spikes_2565)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_activateBuffCounter_1532, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_applyVampirism(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getVampirism_1210, nullptr, 0), gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_canTriggerVampirism_1442, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv_vampLimit = gd::GdVal::from_float(0.0);
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Ranged_2670)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_hasType_81, _ca, 1); })())) {
            lv_vampLimit = gd::gd_coerce_float(this->f_rangedVampirismLimit);
        }
        else {
            lv_vampLimit = gd::gd_coerce_float(this->f_meleeVampirismLimit);
        }
        gd::GdVal lv_healAmount = gd::gd_min(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getVampirism_1210, nullptr, 0), gd::gd_round(gd::gd_mul(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427), lv_vampLimit)));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_healAmount, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_healAmount, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Vampirism_2566), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, _ca, 3); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Vampirism_2566)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_activateBuffCounter_1532, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_heal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_origin = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    lv_amount = gd::gd_mul(lv_amount, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getHealingEfficiency_1165, nullptr, 0));
    lv_amount = gd::gd_round(lv_amount);
    gd::GdVal lv_missingHealth = gd::gd_sub(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxHealth_1144, nullptr, 0), this->f_curHealth);
    gd::GdVal lv_overheal = gd::gd_max(gd::GdVal::from_int(0LL), gd::gd_sub(lv_amount, lv_missingHealth));
    this->f_curHealth = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_curHealth, lv_amount));
    this->f_curHealth = gd::gd_coerce_float(gd::gd_min(this->f_curHealth, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxHealth_1144, nullptr, 0)));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_onHealthChangedUI_1550, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_randHealNumberPos_1131, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_randDmgNumberDir_1130, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_origin, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(lv_origin, &META_Gd__gd_core__CoreItem)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(10.0)), gd::GdVal::from_float(10.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_float(10.0)), gd::GdVal::from_float(10.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Health_2692), lv_amount, lv_origin}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_spawnLabel_character_1540, _ca, 4); })();
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_amount, this->f_playerId, lv_origin, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_createEvent_Heal_1331, _ca, 4); })();
    if (gd::gd_truth(lv_origin)) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(lv_origin, &META_Gd__gd_core__CoreItem)))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemMetrics_1367), SYM_GEN_Heal_2693), lv_amount}; return gd::call_method(gd_ctx, lv_origin, SYM_GEN_addMetric_232, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemMetrics_1367), SYM_GEN_Overheal_2694), lv_overheal}; return gd::call_method(gd_ctx, lv_origin, SYM_GEN_addMetric_232, _ca, 2); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {this->f_playerId, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemMetrics_1367), SYM_GEN_Heal_2693), lv_origin, lv_amount}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotMetric_1353, _ca, 4); })();
            (void)([&]() { gd::GdVal _ca[] = {this->f_playerId, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemMetrics_1367), SYM_GEN_Overheal_2694), lv_origin, lv_overheal}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotMetric_1353, _ca, 4); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_healed", 16u)), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::call_method(gd_ctx, lv_event, SYM_GEN_getAmount_1485, nullptr, 0), lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitEvent_1502, _ca, 4); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_overheal, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_overhealed", 20u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_overheal, lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitSignal_1501, _ca, 3); })();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getUnhealing_1164, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_unhealing = gd::gd_ceil(gd::gd_mul(gd::gd_mul(lv_amount, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getUnhealing_1164, nullptr, 0)), gd::gd_add(gd_ctx, gd::GdVal::from_int(1LL), gd::get_index(gd_ctx, this->f_typedDamageFactors, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Unhealing_2695)))));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_unhealing, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_unhealing}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_unhealingDamageSource_1401), SYM_GEN_setDamage_1460, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_unhealingDamageSource_1401), lv_event}; return gd::call_method(gd_ctx, this->f_opponent, SYM_GEN_takeDamage_1132, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_healToFull(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_curHealth = gd::gd_coerce_float(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxHealth_1144, nullptr, 0));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_onHealthChangedUI_1550, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_reincarnate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_healAmount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_healAmount = gd::gd_coerce_int(lv_healAmount);
    gd::GdVal lv_isHeal = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_isHeal = gd::gd_coerce_bool(lv_isHeal);
    gd::GdVal lv_item = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setCurrentHealth_1140, _ca, 1); })();
    lv_healAmount = gd::gd_coerce_int(gd::gd_min(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxHealth_1144, nullptr, 0), lv_healAmount));
    (void)([&]() { gd::GdVal _ca[] = {lv_healAmount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setCurrentHealth_1140, _ca, 1); })();
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_item, lv_healAmount, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_createEvent_Reincarnate_1350, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemMetrics_1367), SYM_GEN_Heal_2693), lv_healAmount}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addMetric_232, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "reincarnated", 12u)), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitEvent_1502, _ca, 4); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getCurrentHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_curHealth;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getRelativeHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCurrentHealth_1138, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxHealth_1144, nullptr, 0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getMissingHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_coerce_int(gd::gd_ceil(gd::gd_sub(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxHealth_1144, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCurrentHealth_1138, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setCurrentHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__curHealth = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_curHealth = gd::gd_coerce_float(lv__curHealth);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_onHealthChangedUI_1550, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_loseHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    this->f_curHealth = gd::gd_coerce_float(gd::gd_sub(this->f_curHealth, lv_amount));
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_randDmgNumberPos_1129, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_randDmgNumberDir_1130, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_LoseHealth_2696), gd::GdVal::null(), gd::GdVal::null(), lv_amount}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_spawnNumberLabel_1546, _ca, 4); })();
    gd::GdVal lv_event = gd::GdVal::null();
    if (gd::gd_truth(lv_item)) {
        lv_event = ([&]() { gd::GdVal _ca[] = {gd::gd_neg(lv_amount), this->f_playerId, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_createEvent_LoseHealth_1332, _ca, 4); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_damaged", 17u)), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::call_method(gd_ctx, lv_event, SYM_GEN_getAmount_1485, nullptr, 0), lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitEvent_1502, _ca, 4); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_onHealthChangedUI_1550, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(this->f_curHealth, gd::GdVal::from_int(0LL))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_death_1153, nullptr, 0);
    }
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setMaxHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__maxHealth = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_maxHealth = gd::gd_coerce_float(lv__maxHealth);
    this->f_curHealth = gd::gd_coerce_float(this->f_maxHealth);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_onHealthChangedUI_1550, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_giveMaxHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_maxHealth = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_maxHealth, lv_amount));
    this->f_curHealth = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_curHealth, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_onHealthChangedUI_1550, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getBaseMaxHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_maxHealth;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getMaxHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, this->f_maxHealth, this->f_temporaryMaxHealth);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_applyTemporaryMaxHealthGain(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::gd_round(gd::gd_mul(lv_amount, this->f_temporaryMaxHealthGain));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeMaxHealthTemporary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_amount, gd::GdVal::from_int(0LL))))) {
        this->f_temporaryMaxHealth = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_temporaryMaxHealth, lv_amount));
        this->f_curHealth = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_curHealth, lv_amount));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null())))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_item, lv_amount, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_createEvent_TemporaryMaxHealth_1346, _ca, 3); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "temporary_max_health_changed", 28u)), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitEvent_1502, _ca, 4); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getMaxStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, this->f_maxStamina, this->f_temporaryMaxStamina);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    this->f_curStamina = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_curStamina, lv_amount));
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_allowStaminaOverflow)))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clampStamina_1150, nullptr, 0);
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null())))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_amount, lv_item, this->f_playerId, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_createEvent_Stamina_1342, _ca, 4); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_logEvent_1328, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StackChangeType_871), SYM_GEN_Added_Player_2577)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_staminaChanged_235, _ca, 2); })();
        (void)gd::call_method(gd_ctx, lv_item, SYM_GEN_getNextFreeLabelPosition_380, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_addStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_curStamina = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_curStamina, lv_amount));
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clampStamina_1150, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_1392), gd::GdVal::null())))) : gd::GdVal::from_bool(false)))) {
        (void)gd::GdVal::null();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_clampStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_curStamina = gd::gd_coerce_float(gd::gd_clamp(this->f_curStamina, gd::GdVal::from_int(0LL), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxStamina_1147, nullptr, 0)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_fillUpStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_maxStamina}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addStamina_1149, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_useStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_allowStaminaOverflow = gd::GdVal::from_bool(true);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_pre_use_stamina", 25u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_amount}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitSignal_1501, _ca, 3); })();
    this->f_allowStaminaOverflow = gd::GdVal::from_bool(false);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_1392), gd::GdVal::null())))) : gd::GdVal::from_bool(false)))) {
        (void)gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_curStamina, lv_amount)))) {
        this->f_curStamina = gd::gd_coerce_float(gd::gd_max(gd::gd_sub(this->f_curStamina, lv_amount), gd::GdVal::from_int(0LL)));
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clampStamina_1150, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_used_stamina", 22u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_amount}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitSignal_1501, _ca, 3); })();
        return gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_StaminaResult_1280), SYM_GEN_Sufficient_2605);
    }
    else {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clampStamina_1150, nullptr, 0);
        return gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_StaminaResult_1280), SYM_GEN_Insufficient_2551);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_drainStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_drained = gd::gd_min(this->f_curStamina, lv_amount);
    this->f_curStamina = gd::gd_coerce_float(gd::gd_sub(this->f_curStamina, lv_drained));
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_drained, lv_item, this->f_playerId, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_createEvent_DrainStamina_1343, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_logEvent_1328, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_drained, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StackChangeType_871), SYM_GEN_Removed_Opponent_2697)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_staminaChanged_235, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setTemporaryMaxStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_ctx, gd::GdVal::null())))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_1392), gd::GdVal::null())))) : gd::GdVal::from_bool(false)))) {
        (void)gd::GdVal::null();
    }
    this->f_temporaryMaxStamina = gd::gd_coerce_float(lv_amount);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setTemporaryMaxHealthGain(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_temporaryMaxHealthGain = gd::gd_coerce_float(lv_amount);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_death(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_isDead = gd::GdVal::from_bool(true);
    {
        gd::GdVal _t611 = gd::gd_iter_seq(gd_ctx.arena, this->f_character_died_handlers);
        gd::GdArr* _t612 = (_t611.kind == gd::GdVal::Kind::Arr) ? _t611.arr : nullptr;
        uint32_t _len__t613 = _t612 ? _t612->len : 0u;
        for (uint32_t _t613 = 0; _t613 < _len__t613; ++_t613) {
            gd::GdVal lv_handler = _t612->data[_t613];
            (void)gd::call_method(gd_ctx, lv_handler, gd::SYM_call_func, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_stun(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_duration = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stunResisted_1161, nullptr, 0))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_randBuffLabelPos_1127, nullptr, 0);
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_randBuffLabelDir_1128, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_StunResisted_2698), gd::GdVal::null()}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_spawnBuffLabel_1545, _ca, 2); })();
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_item, this->f_playerId, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_createEvent_StunResist_1339, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_logEvent_1328, _ca, 1); })();
    }
    else {
        this->f_stunnedDuration = gd::gd_coerce_float(gd::gd_max(this->f_stunnedDuration, lv_duration));
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_item, lv_duration, this->f_playerId, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_createEvent_Stun_1338, _ca, 4); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_stunned", 17u)), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitEvent_1502, _ca, 4); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_duration, gd::GdVal::from_int(0LL))))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_randBuffLabelPos_1127, nullptr, 0);
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_randBuffLabelDir_1128, nullptr, 0);
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_duration}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_playStunAnimation_1533, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_endStun(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_stunnedDuration = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_Stunned_2699)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotCharacterStat_1358, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_isStunned(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_gt(this->f_stunnedDuration, gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeDodgeStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    this->f_dodgeStacks = gd::gd_coerce_int(gd::gd_coerce_int(gd::gd_max(gd::GdVal::from_int(0LL), gd::gd_add(gd_ctx, this->f_dodgeStacks, lv_amount))));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_DodgeStacks_2700)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotCharacterStat_1358, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeCritResistance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_float(lv_amount);
    this->f_critResistance = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_critResistance, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_CritResistance_2701)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotCharacterStat_1358, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_critResisted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_resisted = ([&]() { gd::GdVal _ca[] = {this->f_critResistance}; return gd::call_method(gd_ctx, this->f_critResistanceRng, SYM_GEN_rollPercent_1664, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_resisted)))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_critResistStacks, gd::GdVal::from_int(0LL))))) {
            this->f_critResistStacks = gd::gd_coerce_int(gd::gd_sub(this->f_critResistStacks, gd::GdVal::from_int(1LL)));
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_CritResistStacks_2702)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotCharacterStat_1358, _ca, 2); })();
            return gd::GdVal::from_bool(true);
        }
    }
    return lv_resisted;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainCritResistStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_num = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_num = gd::gd_coerce_int(lv_num);
    this->f_critResistStacks = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_critResistStacks, lv_num));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_CritResistStacks_2702)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotCharacterStat_1358, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeStunResistance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_float(lv_amount);
    this->f_stunResistance = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_stunResistance, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_stunResisted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {this->f_stunResistance}; return gd::call_method(gd_ctx, this->f_stunResistanceRng, SYM_GEN_rollPercent_1664, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_giveUnhealing(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_float(lv_amount);
    this->f_unhealingAmount = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_unhealingAmount, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_Unhealing_2695)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotCharacterStat_1358, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_reduceUnhealing(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_float(lv_amount);
    this->f_unhealingAmount = gd::gd_coerce_float(gd::gd_max(gd::GdVal::from_float(0.0), gd::gd_sub(this->f_unhealingAmount, lv_amount)));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_Unhealing_2695)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotCharacterStat_1358, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getUnhealing(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_unhealingAmount;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getHealingEfficiency(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_max(gd::GdVal::from_float(0.0), this->f_healingEfficiency);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_addHealingEfficiency(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_float(lv_amount);
    this->f_healingEfficiency = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_healingEfficiency, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_HealEfficiency_2703)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotCharacterStat_1358, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_reduceHealingEfficiency(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_float(lv_amount);
    this->f_healingEfficiency = gd::gd_coerce_float(gd::gd_sub(this->f_healingEfficiency, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_HealEfficiency_2703)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotCharacterStat_1358, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getCritTokens(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_critTokens;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainCritTokens(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_critTokens = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_critTokens, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeDebuffResistStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_debuffResistStacks = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_debuffResistStacks, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_DebuffResistStacks_2704)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotCharacterStat_1358, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeDebuffReflectStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_debuffReflectStacks = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_debuffReflectStacks, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_ReflectStacks_2705)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotCharacterStat_1358, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeBuffProtectStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_buffProtectStacks = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_buffProtectStacks, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeReflectChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_debuff = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_debuff), SYM_GEN_changeReflectChance_1028, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeAllDebuffsReflectChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t614 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1362, nullptr, 0));
        gd::GdArr* _t615 = (_t614.kind == gd::GdVal::Kind::Arr) ? _t614.arr : nullptr;
        uint32_t _len__t616 = _t615 ? _t615->len : 0u;
        for (uint32_t _t616 = 0; _t616 < _len__t616; ++_t616) {
            gd::GdVal lv_debuff = _t615->data[_t616];
            (void)([&]() { gd::GdVal _ca[] = {lv_debuff, lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeReflectChance_1028, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeMeleeSpikesLimit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_meleeSpikesLimit = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_meleeSpikesLimit, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeRangedSpikesLimit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_rangedSpikesLimit = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_rangedSpikesLimit, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeEffectSpikesLimit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_effectSpikesLimit = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_effectSpikesLimit, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeMeleeVampirismLimit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_meleeVampirismLimit = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_meleeVampirismLimit, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeRangedVampirismLimit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_rangedVampirismLimit = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_rangedVampirismLimit, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getBonusFatigueDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_bonusFatigueDamage;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_addFatigueDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_bonusFatigueDamage = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_bonusFatigueDamage, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "fatigue_damage_changed", 22u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitSignal_1501, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_takeFatigueDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_fatigueDamageSource_1402)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_takeDamage_1132, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_startBlindingLight(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_blindingLightActive = gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_endBlindingLight(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    this->f_blindingLightActive = gd::GdVal::from_bool(false);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blinding_light_ended", 20u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitSignal_1501, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_startBattleRage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_duration = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_applyBonus = (_argc > 3) ? _args[3] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_fullDur = lv_duration;
    if (gd::gd_truth(lv_applyBonus)) {
        lv_fullDur = gd::gd_add(gd_ctx, lv_fullDur, this->f_battleRageBonusDur);
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_fullDur}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__setRageTimer_1194, _ca, 1); })();
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_item, lv_fullDur, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_createEvent_BattleRageStart_1348, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "battle_rage_started", 19u)), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitEvent_1502, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_BattleRage_2686), gd::GdVal::from_bool(false), lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotCharacterStat_1358, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_playBattleRageAnimation_1193, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_endBattleRage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f__rage_active = gd::GdVal::from_bool(false);
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_playerId}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_createEvent_BattleRageEnd_1349, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "battle_rage_ended", 17u)), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitEvent_1502, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_BattleRage_2686), gd::GdVal::from_bool(false), lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotCharacterStat_1358, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_playBattleRageAnimation_1193, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getClass(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_characterClass;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_isChibi(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_chibi;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setClass(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__class = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv__class = gd::gd_coerce_int(lv__class);
    gd::GdVal lv__chibi = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv__chibi = gd::gd_coerce_bool(lv__chibi);
    gd::GdVal lv_classResource = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    this->f_characterClass = gd::gd_coerce_int(lv__class);
    this->f_chibi = lv__chibi;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_classResource, gd::GdVal::null())))) {
        lv_classResource = (gd::gd_truth(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_class_resources_1400)) ? (([&]() { gd::GdVal _ca[] = {lv__class, gd::GdVal::null()}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_class_resources_1400), gd::SYM_get, _ca, 2); })()) : (gd::GdVal::null()));
    }
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_classResource, gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_playerId, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_ID_1279), SYM_GEN_PLAYER_2540))))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_classResource}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setClassResource_1188, _ca, 1); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_classResource}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_onClassChanged_1537, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "class_changed", 13u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitSignal_1501, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setClassResource(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_classResource = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_classResource, gd::GdVal::null())))) {
        return gd::GdVal::null();
    }
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "health", 6u))}; return gd::call_method(gd_ctx, lv_classResource, gd::SYM_get, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setMaxHealth_1142, _ca, 1); })();
    this->f_baseMaxStamina = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, lv_classResource, gd::SYM_get, _ca, 1); })());
    (void)([&]() { gd::GdVal _ca[] = {this->f_baseMaxStamina}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setMaxStamina_1250, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_classResource}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_onClassChanged_1537, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_lose(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_playWinLoseAnimation_1536, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_win(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_playWinLoseAnimation_1536, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setStat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stat = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_value = (_argc > 1) ? _args[1] : gd::GdVal::null();
    {
        gd::GdVal _t617 = lv_stat;
        if (gd::gd_eq(_t617, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_Health_2692))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_value}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setCurrentHealth_1140, _ca, 1); })();
        }
        else if (gd::gd_eq(_t617, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_MaxHealth_2587))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_value}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setTemporaryMaxHealth_1259, _ca, 1); })();
        }
        else if (gd::gd_eq(_t617, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_Stamina_2576))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_value}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setCurrentStamina_1247, _ca, 1); })();
        }
        else if (gd::gd_eq(_t617, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_MaxStamina_2706))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_sub(lv_value, this->f_maxStamina)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setTemporaryMaxStamina_1151, _ca, 1); })();
        }
        else if (gd::gd_eq(_t617, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_Stunned_2699))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_value}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_playStunAnimation_1533, _ca, 2); })();
        }
        else if (gd::gd_eq(_t617, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_Invulnerable_2707))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_value}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_playInvulnerableAnimation_1538, _ca, 2); })();
        }
        else if (gd::gd_eq(_t617, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_BattleRage_2686))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_value}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_playBattleRageAnimation_1193, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getStat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stat = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t618 = lv_stat;
        if (gd::gd_eq(_t618, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_StaminaRegen_2708))) {
            return gd::gd_mul(gd::gd_sub(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStaminaRegeneration_1253, nullptr, 0), gd::GdVal::from_int(1LL)), gd::GdVal::from_float(100.0));
        }
        else if (gd::gd_eq(_t618, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_Health_2692))) {
            return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCurrentHealth_1138, nullptr, 0);
        }
        else if (gd::gd_eq(_t618, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_MaxHealth_2587))) {
            return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getTemporaryMaxHealth_1258, nullptr, 0);
        }
        else if (gd::gd_eq(_t618, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_Stamina_2576))) {
            return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCurrentStamina_1246, nullptr, 0);
        }
        else if (gd::gd_eq(_t618, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_MaxStamina_2706))) {
            return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxStamina_1147, nullptr, 0);
        }
        else if (gd::gd_eq(_t618, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_Stunned_2699))) {
            return this->f_stunnedDuration;
        }
        else if (gd::gd_eq(_t618, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_Invulnerable_2707))) {
            return this->f_invulnerable;
        }
        else if (gd::gd_eq(_t618, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_BattleRage_2686))) {
            return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isBattleRaging_1191, nullptr, 0);
        }
        else if (gd::gd_eq(_t618, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_ReflectStacks_2705))) {
            return this->f_debuffReflectStacks;
        }
        else if (gd::gd_eq(_t618, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_DebuffResistStacks_2704))) {
            return this->f_debuffResistStacks;
        }
        else if (gd::gd_eq(_t618, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_CritStacks_2709))) {
            return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCritTokens_184, nullptr, 0);
        }
        else if (gd::gd_eq(_t618, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_DodgeStacks_2700))) {
            return this->f_dodgeStacks;
        }
        else if (gd::gd_eq(_t618, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_CritResistStacks_2702))) {
            return this->f_critResistStacks;
        }
        else if (gd::gd_eq(_t618, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_CritResistance_2701))) {
            return this->f_critResistance;
        }
        else if (gd::gd_eq(_t618, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_StunResistance_2710))) {
            return this->f_stunResistance;
        }
        else if (gd::gd_eq(_t618, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_HealEfficiency_2703))) {
            return gd::gd_mul(gd::gd_sub(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getHealingEfficiency_1165, nullptr, 0), gd::GdVal::from_int(1LL)), gd::GdVal::from_int(100LL));
        }
        else if (gd::gd_eq(_t618, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_DamageResistance_2711))) {
            return this->f_damageResistance;
        }
        else if (gd::gd_eq(_t618, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_MeleeDmgFactor_2712))) {
            return gd::gd_mul(gd::get_index(gd_ctx, this->f_typedDamageFactors, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Melee_2669)), gd::GdVal::from_int(100LL));
        }
        else if (gd::gd_eq(_t618, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_RangedDmgFactor_2713))) {
            return gd::gd_mul(gd::get_index(gd_ctx, this->f_typedDamageFactors, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Ranged_2670)), gd::GdVal::from_int(100LL));
        }
        else if (gd::gd_eq(_t618, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_EffectDmgFactor_2714))) {
            return gd::gd_mul(gd::get_index(gd_ctx, this->f_typedDamageFactors, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Effect_2559)), gd::GdVal::from_int(100LL));
        }
        else if (gd::gd_eq(_t618, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_Unhealing_2695))) {
            return gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getUnhealing_1164, nullptr, 0), gd::GdVal::from_int(100LL));
        }
        else if (gd::gd_eq(_t618, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_MaxHealthGain_2715))) {
            return gd::gd_mul(gd::gd_sub(this->f_temporaryMaxHealthGain, gd::GdVal::from_float(1.0)), gd::GdVal::from_int(100LL));
        }
    }
    return gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_isBattleRaging(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f__rage_active;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_startAutoRage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_autoRageItem, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_AUTO_RAGE_DUR_1045)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_startBattleRage_1183, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_playBattleRageAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rageStart = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_rageStart}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_playBattleRageAnimation_1193, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn__setRageTimer(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_t = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_t = gd::gd_coerce_float(lv_t);
    this->f__rage_eng = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {lv_t}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreCharacter::call_static_fn(gd_ctx, SYM_GEN__f32eng_1036, _ca, 1, _out); return _out; })());
    this->f__rage_active = gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::sf__f32eng(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_x = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_x = gd::gd_coerce_float(lv_x);
    gd::GdVal lv_pa = gd::GdVal::from_arr(gd::GdArr::create_pool_real(gd_ctx.arena));
    (void)([&]() { gd::GdVal _ca[] = {lv_x}; return gd::call_method(gd_ctx, lv_pa, gd::SYM_append, _ca, 1); })();
    return gd::get_index(gd_ctx, lv_pa, gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_makeInvulnerable(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_invuDur = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    this->f_invulnerabilityItem = lv_item;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_invulnerable)))) {
        this->f__invul_eng = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {lv_invuDur}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreCharacter::call_static_fn(gd_ctx, SYM_GEN__f32eng_1036, _ca, 1, _out); return _out; })());
        this->f__invul_active = gd::GdVal::from_bool(true);
        this->f_invulnerable = gd::GdVal::from_bool(true);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_playInvulnerableAnimation_1538, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "randPitch", 9u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 3); })();
    }
    else {
        gd::GdVal lv__invul_base = this->f__invul_left;
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv__invul_base, gd::GdVal::from_float(0.0))))) {
            lv__invul_base = this->f__invul_eng;
        }
        this->f__invul_eng = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, lv_invuDur, lv__invul_base)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__CoreCharacter::call_static_fn(gd_ctx, SYM_GEN__f32eng_1036, _ca, 1, _out); return _out; })());
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "INVU", 4u)), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "make p", 6u)), ([&]() { gd::GdVal _ca[] = {this->f_playerId}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_invulnerable))) ? (gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " first", 6u))) : (gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " ext", 4u))))), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " dur=", 5u))), ([&]() { gd::GdVal _ca[] = {lv_invuDur}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " lt3.1=", 7u))), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(gd::gd_lt(lv_invuDur, gd::GdVal::from_float(3.1)))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " gt3.1=", 7u))), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(gd::gd_gt(lv_invuDur, gd::GdVal::from_float(3.1)))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " eng=", 5u))), ([&]() { gd::GdVal _ca[] = {this->f__invul_eng}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " left=", 6u))), ([&]() { gd::GdVal _ca[] = {this->f__invul_left}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "act=", 4u)), ([&]() { gd::GdVal _ca[] = {this->f__invul_active}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " fr=", 4u))), ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_frame_counter_1384)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_trace_diag_1645, _ca, 3); })();
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_item, lv_invuDur, this->f_playerId, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_createEvent_InvulnerableStart_1340, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_invulnerable_start", 28u)), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitEvent_1502, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_Invulnerable_2707)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotCharacterStat_1358, _ca, 2); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_makeVulnerable(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_invulnerabilityEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_invulnerable = gd::GdVal::from_bool(false);
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_invulnerabilityItem, this->f_playerId}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_createEvent_InvulnerableEnd_1341, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_invulnerable_end", 26u)), lv_event, gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitEvent_1502, _ca, 4); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_Invulnerable_2707)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotCharacterStat_1358, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_playInvulnerableAnimation_1538, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setInvulnerable(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_active = gd::gd_coerce_bool(lv_active);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    this->f_invulnerable = lv_active;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_buffType), SYM_GEN_getStacks_1022, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getBuffStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stacks = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t619 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0));
        gd::GdArr* _t620 = (_t619.kind == gd::GdVal::Kind::Arr) ? _t619.arr : nullptr;
        uint32_t _len__t621 = _t620 ? _t620->len : 0u;
        for (uint32_t _t621 = 0; _t621 < _len__t621; ++_t621) {
            gd::GdVal lv_buff = _t620->data[_t621];
            lv_stacks = gd::gd_add(gd_ctx, lv_stacks, ([&]() { gd::GdVal _ca[] = {lv_buff}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1022, _ca, 1); })());
        }
    }
    return lv_stacks;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getDebuffStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stacks = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t622 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1362, nullptr, 0));
        gd::GdArr* _t623 = (_t622.kind == gd::GdVal::Kind::Arr) ? _t622.arr : nullptr;
        uint32_t _len__t624 = _t623 ? _t623->len : 0u;
        for (uint32_t _t624 = 0; _t624 < _len__t624; ++_t624) {
            gd::GdVal lv_debuff = _t623->data[_t624];
            lv_stacks = gd::gd_add(gd_ctx, lv_stacks, ([&]() { gd::GdVal _ca[] = {lv_debuff}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1022, _ca, 1); })());
        }
    }
    return lv_stacks;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_buffType), SYM_GEN_setStacks_1023, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setStacksLogged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_curStacks = ([&]() { gd::GdVal _ca[] = {lv_buffType}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1022, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, lv_curStacks)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_buffType, gd::gd_sub(lv_curStacks, lv_amount), lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseStacks_1031, _ca, 4); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, lv_curStacks)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_buffType, gd::gd_sub(lv_amount, lv_curStacks), lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_gainStacks_1029, _ca, 4); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_reflect = (_argc > 4) ? _args[4] : (gd::GdVal::from_bool(false));
    lv_reflect = gd::gd_coerce_bool(lv_reflect);
    return ([&]() { gd::GdVal _ca[] = {lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_buffType), SYM_GEN_gainStacks_1029, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainStacksTemporary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_duration = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 4) ? _args[4] : (gd::GdVal::null());
    gd::GdVal lv_reflect = (_argc > 5) ? _args[5] : (gd::GdVal::from_bool(false));
    lv_reflect = gd::gd_coerce_bool(lv_reflect);
    return ([&]() { gd::GdVal _ca[] = {lv_amount, lv_duration, lv_item, lv_triggerEvent, lv_reflect}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_buffType), SYM_GEN_gainTemporary_1030, _ca, 5); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_loseStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_buffType), SYM_GEN_loseStacks_1031, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_useStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {lv_amount, lv_item, lv_triggerEvent, gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_buffType), SYM_GEN_loseStacks_1031, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeResistChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_chance = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_chance}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_buffType), SYM_GEN_changeResistChance_1025, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeDebuffResistChances(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t625 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1362, nullptr, 0));
        gd::GdArr* _t626 = (_t625.kind == gd::GdVal::Kind::Arr) ? _t625.arr : nullptr;
        uint32_t _len__t627 = _t626 ? _t626->len : 0u;
        for (uint32_t _t627 = 0; _t627 < _len__t627; ++_t627) {
            gd::GdVal lv_debuff = _t626->data[_t627];
            (void)([&]() { gd::GdVal _ca[] = {lv_debuff, lv_chance}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeResistChance_1025, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeResistStacks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_buffType), SYM_GEN_changeResistStacks_1026, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Block_2564)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1022, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Spikes_2565), lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setStacks_1023, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Block_2564), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_gainStacks_1029, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_loseBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Block_2564), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseStacks_1031, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getSpikes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Spikes_2565)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1022, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setSpikes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Spikes_2565), lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setStacks_1023, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainSpikes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Spikes_2565), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_gainStacks_1029, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_loseSpikes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Spikes_2565), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseStacks_1031, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getVampirism(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Vampirism_2566)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1022, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setVampirism(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Vampirism_2566), lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setStacks_1023, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainVampirism(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Vampirism_2566), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_gainStacks_1029, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_loseVampirism(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Vampirism_2566), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseStacks_1031, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getPoison(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Poison_2567)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1022, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setPoison(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Poison_2567), lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setStacks_1023, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainPoison(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Poison_2567), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_gainStacks_1029, _ca, 4); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        this->f_damage_anim_current = gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Poison", 6u));
    }
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_losePoison(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Poison_2567), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseStacks_1031, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getRegeneration(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Regeneration_2569)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1022, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setRegeneration(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Regeneration_2569), lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setStacks_1023, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainRegeneration(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Regeneration_2569), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_gainStacks_1029, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_loseRegeneration(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Regeneration_2569), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseStacks_1031, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getLucky(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Lucky_2570)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1022, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setLucky(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Lucky_2570), lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setStacks_1023, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainLucky(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Lucky_2570), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_gainStacks_1029, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_loseLucky(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Lucky_2570), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseStacks_1031, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getBlind(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Blind_2568)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1022, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setBlind(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Blind_2568), lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setStacks_1023, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainBlind(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Blind_2568), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_gainStacks_1029, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_loseBlind(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Blind_2568), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseStacks_1031, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getMana(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Mana_2571)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1022, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setMana(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Mana_2571), lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setStacks_1023, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainMana(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Mana_2571), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_gainStacks_1029, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_loseMana(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Mana_2571), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseStacks_1031, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getEmpower(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Empower_2572)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1022, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setEmpower(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Empower_2572), lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setStacks_1023, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainEmpower(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Empower_2572), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_gainStacks_1029, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_loseEmpower(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Empower_2572), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseStacks_1031, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getHeat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Heat_2573)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1022, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setHeat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Heat_2573), lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setStacks_1023, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainHeat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Heat_2573), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_gainStacks_1029, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_loseHeat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Heat_2573), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseStacks_1031, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getCold(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Cold_2574)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStacks_1022, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setCold(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Cold_2574), lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setStacks_1023, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainCold(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Cold_2574), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_gainStacks_1029, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_loseCold(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Cold_2574), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseStacks_1031, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getBuffDamageMod(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getEmpower_1232, nullptr, 0), this->f_empowerDamage);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getBuffAccuracyMod(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_mul(gd::gd_sub(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getLucky_1221, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlind_1224, nullptr, 0)), gd::GdVal::from_int(5LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getBaseMaxStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_baseMaxStamina;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getMaxBaseStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_maxStamina;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getCurrentStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_curStamina;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setCurrentStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_stamina = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_stamina = gd::gd_coerce_float(lv_stamina);
    this->f_curStamina = gd::gd_coerce_float(lv_stamina);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getMissingStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_sub(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMaxStamina_1147, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCurrentStamina_1246, nullptr, 0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_isFullStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_le(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMissingStamina_1248, nullptr, 0), gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setMaxStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__maxStamina = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_ctx, gd::GdVal::null())))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_1392), gd::GdVal::null())))) : gd::GdVal::from_bool(false)))) {
        (void)gd::GdVal::null();
    }
    this->f_maxStamina = gd::gd_coerce_float(lv__maxStamina);
    this->f_curStamina = gd::gd_coerce_float(this->f_maxStamina);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_onMaxStaminaChangedUI_1551, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_giveMaxStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_maxStamina = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_maxStamina, lv_amount));
    this->f_curStamina = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_curStamina, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_onMaxStaminaChangedUI_1551, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_reduceMaxStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_maxStamina = gd::gd_coerce_float(gd::gd_max(gd::GdVal::from_int(1LL), gd::gd_sub(this->f_maxStamina, lv_amount)));
    this->f_curStamina = gd::gd_coerce_float(gd::gd_min(this->f_maxStamina, this->f_curStamina));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_onMaxStaminaChangedUI_1551, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_gainMaxStaminaTemporary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_filled = (_argc > 3) ? _args[3] : (gd::GdVal::from_bool(true));
    lv_filled = gd::gd_coerce_bool(lv_filled);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_amount, gd::GdVal::from_int(0LL))))) {
        this->f_temporaryMaxStamina = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_temporaryMaxStamina, lv_amount));
        if (gd::gd_truth((gd::gd_truth(lv_filled) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
            this->f_curStamina = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_curStamina, lv_amount));
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null())))) {
            gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_item, lv_amount, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_createEvent_TemporaryMaxStamina_1347, _ca, 3); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_logEvent_1328, _ca, 1); })();
            if (gd::gd_truth(lv_filled)) {
                (void)([&]() { gd::GdVal _ca[] = {lv_amount, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StackChangeType_871), SYM_GEN_Added_Player_2577)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_staminaChanged_235, _ca, 2); })();
            }
            (void)gd::call_method(gd_ctx, lv_item, SYM_GEN_getNextFreeLabelPosition_380, nullptr, 0);
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_TemporaryMaxStamina_2716), lv_item, lv_amount}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_spawnLabelOnItem_1552, _ca, 3); })();
        }
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_onMaxStaminaChangedUI_1551, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getStaminaRegeneration(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_staminaRegen;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_giveStaminaRegeneration(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_staminaRegen = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_staminaRegen, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_StaminaRegen_2708)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotCharacterStat_1358, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getTotalStaminaUsage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_totalStaminaUse = gd::GdVal::from_float(0.0);
    {
        gd::GdVal _t628 = gd::gd_iter_seq(gd_ctx.arena, this->f_items);
        gd::GdArr* _t629 = (_t628.kind == gd::GdVal::Kind::Arr) ? _t628.arr : nullptr;
        uint32_t _len__t630 = _t629 ? _t629->len : 0u;
        for (uint32_t _t630 = 0; _t630 < _len__t630; ++_t630) {
            gd::GdVal lv_item = _t629->data[_t630];
            gd::GdVal lv_staminaUse = gd::call_method(gd_ctx, lv_item, SYM_GEN_getStaminaCost_114, nullptr, 0);
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, lv_item, SYM_GEN_getCooldown_104, nullptr, 0), gd::GdVal::from_int(0LL))))) {
                lv_staminaUse = gd::gd_div(gd_ctx, lv_staminaUse, gd::call_method(gd_ctx, lv_item, SYM_GEN_getCooldown_104, nullptr, 0));
            }
            lv_totalStaminaUse = gd::gd_add(gd_ctx, lv_totalStaminaUse, lv_staminaUse);
        }
    }
    return lv_totalStaminaUse;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeBaseMaxStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_playerId, gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_ID_1279), SYM_GEN_PLAYER_2540)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_staminaUpdateQueued)))) : gd::GdVal::from_bool(false)))) {
        this->f_staminaUpdateQueued = gd::GdVal::from_bool(true);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "recalculateMaxStamina", 21u))}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_defer_1422, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_recalculateMaxStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_staminaUpdateQueued = gd::GdVal::from_bool(false);
    this->f_maxStamina = gd::gd_coerce_float(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseMaxStamina_1244, nullptr, 0));
    gd::GdVal lv__sack = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t631 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1512, nullptr, 0));
        gd::GdArr* _t632 = (_t631.kind == gd::GdVal::Kind::Arr) ? _t631.arr : nullptr;
        uint32_t _len__t633 = _t632 ? _t632->len : 0u;
        for (uint32_t _t633 = 0; _t633 < _len__t633; ++_t633) {
            gd::GdVal lv_item = _t632->data[_t633];
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), SYM_GEN_name_7), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Stamina Sack", 12u)))))) {
                this->f_maxStamina = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_maxStamina, gd::GdVal::from_int(1LL)));
                lv__sack = gd::gd_add(gd_ctx, lv__sack, gd::GdVal::from_int(1LL));
            }
        }
    }
    this->f_curStamina = gd::gd_coerce_float(this->f_maxStamina);
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_ctx, gd::GdVal::null())))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_1392), gd::GdVal::null())))) : gd::GdVal::from_bool(false)))) {
        (void)gd::GdVal::null();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_onMaxStaminaChangedUI_1551, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_getTemporaryMaxHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_temporaryMaxHealth;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_setTemporaryMaxHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_tempHealth = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_temporaryMaxHealth = gd::gd_coerce_float(lv_tempHealth);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_onHealthChangedUI_1550, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_reduceMaxHealth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_maxHealth = gd::gd_coerce_float(gd::gd_max(gd::GdVal::from_int(1LL), gd::gd_sub(this->f_maxHealth, lv_amount)));
    this->f_curHealth = gd::gd_coerce_float(gd::gd_min(this->f_maxHealth, this->f_curHealth));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_hooks_1380), SYM_GEN_onHealthChangedUI_1550, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeMaxHealthGain(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_temporaryMaxHealthGain = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_temporaryMaxHealthGain, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_MaxHealthGain_2715)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotCharacterStat_1358, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeDamageReduction(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    this->f_damageReduction = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_damageReduction, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeDamageResistance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_float(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_duration = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    this->f_damageResistance = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_damageResistance, lv_amount));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_DamageResistance_2711)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotCharacterStat_1358, _ca, 2); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_item, gd::GdVal::null())))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_item, gd::gd_neg(lv_amount), gd::GdVal::from_bool(true), lv_duration, gd::GdVal::null(), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_createEvent_DamChange_1352, _ca, 6); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_logEvent_1328, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeTypedDamageFactor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_damageType = gd::gd_coerce_int(lv_damageType);
    gd::GdVal lv_amount = (_argc > 1) ? _args[1] : gd::GdVal::null();
    { gd::GdVal _t634 = this->f_typedDamageFactors; gd::GdVal _t635 = lv_damageType; gd::set_index(gd_ctx, _t634, _t635, gd::gd_add(gd_ctx, gd::get_index(gd_ctx, _t634, _t635), lv_amount)); }
    {
        gd::GdVal _t636 = gd::gd_iter_seq(gd_ctx.arena, this->f_items);
        gd::GdArr* _t637 = (_t636.kind == gd::GdVal::Kind::Arr) ? _t636.arr : nullptr;
        uint32_t _len__t638 = _t637 ? _t637->len : 0u;
        for (uint32_t _t638 = 0; _t638 < _len__t638; ++_t638) {
            gd::GdVal lv_item = _t637->data[_t638];
            if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_item, SYM_GEN_damageSource_24), gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_damageType}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_item, SYM_GEN_damageSource_24), SYM_GEN_hasType_81, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_MinDamage_2557)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
                (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_MaxDamage_2558)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
            }
        }
    }
    {
        gd::GdVal _t639 = lv_damageType;
        if (gd::gd_eq(_t639, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Melee_2669))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_MeleeDmgFactor_2712)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotCharacterStat_1358, _ca, 2); })();
        }
        else if (gd::gd_eq(_t639, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Ranged_2670))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_RangedDmgFactor_2713)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotCharacterStat_1358, _ca, 2); })();
        }
        else if (gd::gd_eq(_t639, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Effect_2559))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_EffectDmgFactor_2714)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotCharacterStat_1358, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeEffectDamageFactor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    { gd::GdVal _t640 = this->f_typedDamageFactors; gd::GdVal _t641 = gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Effect_2559); gd::set_index(gd_ctx, _t640, _t641, gd::gd_add(gd_ctx, gd::get_index(gd_ctx, _t640, _t641), lv_amount)); }
    { gd::GdVal _t642 = this->f_typedDamageFactors; gd::GdVal _t643 = gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Unhealing_2695); gd::set_index(gd_ctx, _t642, _t643, gd::gd_add(gd_ctx, gd::get_index(gd_ctx, _t642, _t643), lv_amount)); }
    {
        gd::GdVal _t644 = gd::gd_iter_seq(gd_ctx.arena, this->f_items);
        gd::GdArr* _t645 = (_t644.kind == gd::GdVal::Kind::Arr) ? _t644.arr : nullptr;
        uint32_t _len__t646 = _t645 ? _t645->len : 0u;
        for (uint32_t _t646 = 0; _t646 < _len__t646; ++_t646) {
            gd::GdVal lv_item = _t645->data[_t646];
            if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::get_prop(gd_ctx, lv_item, SYM_GEN_damageSource_24), gd::GdVal::null()))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Effect_2559)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_item, SYM_GEN_damageSource_24), SYM_GEN_hasType_81, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_MinDamage_2557)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
                (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_MaxDamage_2558)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_EffectDmgFactor_2714)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotCharacterStat_1358, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeEmpowerDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_empowerDamage = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_empowerDamage, lv_amount));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changePoisonCritChancePercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::call_method(gd_ctx, this->f_poisonDamageSource, SYM_GEN_addCritChancePercent_181, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeSpikesCritChancePercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::call_method(gd_ctx, this->f_spikeDamageSource, SYM_GEN_addCritChancePercent_181, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_useCritToken(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_critTokens = gd::gd_coerce_int(gd::gd_sub(this->f_critTokens, gd::GdVal::from_int(1LL)));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, Gd__gd_core__CoreCharacter::get_static_const_or_enum(gd_ctx, SYM_GEN_Stat_870), SYM_GEN_CritStacks_2709)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotCharacterStat_1358, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_useMana(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    gd::GdVal lv_item = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    gd::GdVal lv_triggerEvent = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Mana_2571), lv_amount, lv_item, lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStacks_1203, _ca, 4); })();
    return lv_event;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeProtectionChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_buffType = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_chance = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_chance}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_buffType), SYM_GEN_changeCleanseProtectionChance_1027, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeBuffProtectionChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t647 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0));
        gd::GdArr* _t648 = (_t647.kind == gd::GdVal::Kind::Arr) ? _t647.arr : nullptr;
        uint32_t _len__t649 = _t648 ? _t648->len : 0u;
        for (uint32_t _t649 = 0; _t649 < _len__t649; ++_t649) {
            gd::GdVal lv_buff = _t648->data[_t649];
            (void)([&]() { gd::GdVal _ca[] = {lv_chance}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_buff), SYM_GEN_changeCleanseProtectionChance_1027, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeDebuffProtectionChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t650 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1362, nullptr, 0));
        gd::GdArr* _t651 = (_t650.kind == gd::GdVal::Kind::Arr) ? _t650.arr : nullptr;
        uint32_t _len__t652 = _t651 ? _t651->len : 0u;
        for (uint32_t _t652 = 0; _t652 < _len__t652; ++_t652) {
            gd::GdVal lv_debuff = _t651->data[_t652];
            (void)([&]() { gd::GdVal _ca[] = {lv_chance}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_debuff), SYM_GEN_changeCleanseProtectionChance_1027, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeBuffNullifyChances(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t653 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1361, nullptr, 0));
        gd::GdArr* _t654 = (_t653.kind == gd::GdVal::Kind::Arr) ? _t653.arr : nullptr;
        uint32_t _len__t655 = _t654 ? _t654->len : 0u;
        for (uint32_t _t655 = 0; _t655 < _len__t655; ++_t655) {
            gd::GdVal lv_buff = _t654->data[_t655];
            (void)([&]() { gd::GdVal _ca[] = {lv_buff, lv_chance}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeResistChance_1025, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_changeDebuffNullifyChances(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t656 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getDebuffs_1362, nullptr, 0));
        gd::GdArr* _t657 = (_t656.kind == gd::GdVal::Kind::Arr) ? _t656.arr : nullptr;
        uint32_t _len__t658 = _t657 ? _t657->len : 0u;
        for (uint32_t _t658 = 0; _t658 < _len__t658; ++_t658) {
            gd::GdVal lv_debuff = _t657->data[_t658];
            (void)([&]() { gd::GdVal _ca[] = {lv_debuff, lv_chance}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeResistChance_1025, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_addBattleRageDuration(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_dur = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_battleRageBonusDur = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_battleRageBonusDur, lv_dur));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_isVulnerable(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(!gd::gd_truth(this->f_invulnerable));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_physicsTickCharacter(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isStunned_1155, nullptr, 0))) {
        this->f_stunnedDuration = gd::gd_coerce_float(gd::gd_sub(this->f_stunnedDuration, lv_delta));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(this->f_stunnedDuration, gd::GdVal::from_float(0.0))))) {
            this->f_stunnedDuration = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_endStun_1154, nullptr, 0);
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_staminaRegen, lv_delta)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addStamina_1149, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_tickPhysicsTimers(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    if (gd::gd_truth(this->f__tick_timer_active)) {
        this->f__tick_timer_left = gd::gd_sub(this->f__tick_timer_left, lv_delta);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(this->f__tick_timer_left, gd::GdVal::from_float(0.0))))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onTick_1122, nullptr, 0);
            this->f__tick_timer_left = gd::gd_add(gd_ctx, this->f__tick_timer_left, gd::GdVal::from_float(1.0));
        }
    }
    if (gd::gd_truth(this->f__rage_active)) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f__rage_eng, this->f__rage_seen)))) {
            this->f__rage_left = gd::gd_coerce_float(gd::gd_sub(this->f__rage_left, lv_delta));
        }
        else {
            this->f__rage_left = gd::gd_coerce_float(this->f__rage_eng);
        }
        this->f__rage_seen = gd::gd_coerce_float(this->f__rage_eng);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(this->f__rage_left, gd::GdVal::from_float(0.0))))) {
            this->f__rage_active = gd::GdVal::from_bool(false);
            this->f__rage_eng = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_endBattleRage_1184, nullptr, 0);
            if (gd::gd_truth(this->f__rage_active)) {
                this->f__rage_left = gd::gd_coerce_float(this->f__rage_eng);
                this->f__rage_seen = gd::gd_coerce_float(this->f__rage_eng);
            }
        }
    }
    if (gd::gd_truth(this->f__invul_active)) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f__invul_eng, this->f__invul_seen)))) {
            this->f__invul_left = gd::gd_coerce_float(gd::gd_sub(this->f__invul_left, lv_delta));
        }
        else {
            this->f__invul_left = gd::gd_coerce_float(this->f__invul_eng);
        }
        this->f__invul_seen = gd::gd_coerce_float(this->f__invul_eng);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(this->f__invul_left, gd::GdVal::from_float(0.0))))) {
            this->f__invul_active = gd::GdVal::from_bool(false);
            this->f__invul_eng = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "INVU", 4u)), gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "fire p", 6u)), ([&]() { gd::GdVal _ca[] = {this->f_playerId}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " left=", 6u))), ([&]() { gd::GdVal _ca[] = {this->f__invul_left}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " eng=", 5u))), ([&]() { gd::GdVal _ca[] = {this->f__invul_eng}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, " seen=", 6u))), ([&]() { gd::GdVal _ca[] = {this->f__invul_seen}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()), gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "fr=", 3u)), ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_frame_counter_1384)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), SYM_GEN_trace_diag_1645, _ca, 3); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_invulnerabilityEnded_1197, nullptr, 0);
            if (gd::gd_truth(this->f__invul_active)) {
                this->f__invul_left = gd::gd_coerce_float(this->f__invul_eng);
                this->f__invul_seen = gd::gd_coerce_float(this->f__invul_eng);
            }
        }
    }
    else {
        this->f__invul_left = gd::gd_coerce_float(gd::gd_neg(gd::GdVal::from_float(1.0)));
    }
    if (gd::gd_truth(this->f__autoRage_active)) {
        this->f__autoRage_left = gd::gd_coerce_float(gd::gd_sub(this->f__autoRage_left, lv_delta));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(this->f__autoRage_left, gd::GdVal::from_float(0.0))))) {
            this->f__autoRage_left = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
            this->f__autoRage_active = gd::GdVal::from_bool(false);
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_startAutoRage_1192, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_tickBuffs(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    {
        gd::GdVal _t659 = gd::gd_iter_seq(gd_ctx.arena, this->f_buffs);
        gd::GdArr* _t660 = (_t659.kind == gd::GdVal::Kind::Arr) ? _t659.arr : nullptr;
        uint32_t _len__t661 = _t660 ? _t660->len : 0u;
        for (uint32_t _t661 = 0; _t661 < _len__t661; ++_t661) {
            gd::GdVal lv_buffType = _t660->data[_t661];
            (void)([&]() { gd::GdVal _ca[] = {lv_delta}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_buffType), SYM_GEN__tick_1039, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreCharacter::fn_rebuildTimerSeen(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f__rage_active)))) {
        this->f__rage_eng = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    }
    this->f__rage_left = gd::gd_coerce_float(this->f__rage_eng);
    this->f__rage_seen = gd::gd_coerce_float(this->f__rage_eng);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f__invul_active)))) {
        this->f__invul_eng = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    }
    this->f__invul_left = gd::gd_coerce_float(this->f__invul_eng);
    this->f__invul_seen = gd::gd_coerce_float(this->f__invul_eng);
    {
        gd::GdVal _t662 = gd::gd_iter_seq(gd_ctx.arena, this->f_buffs);
        gd::GdArr* _t663 = (_t662.kind == gd::GdVal::Kind::Arr) ? _t662.arr : nullptr;
        uint32_t _len__t664 = _t663 ? _t663->len : 0u;
        for (uint32_t _t664 = 0; _t664 < _len__t664; ++_t664) {
            gd::GdVal lv_buffType = _t663->data[_t664];
            (void)gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_buffs, lv_buffType), SYM_GEN_rebuildTimerSeen_141, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreCharacter(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__CoreCharacter>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__CoreCharacter = {CLS_Gd__gd_core__CoreCharacter, "CoreCharacter", "res://gd_core/CoreCharacter.gd", nullptr, false, _alloc_Gd__gd_core__CoreCharacter, &Gd__gd_core__CoreCharacter::get_static_prop_fn, &Gd__gd_core__CoreCharacter::call_static_fn};

void Gd__gd_core__CoreRng::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_rng = gd::GdVal::null();
    this->f_debug_flip_tag = gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u));
    this->f_oracle_trace = gd::GdVal::from_bool(false);
    this->f_oracle_trace_log = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f__stacktrace = gd::GdVal::from_bool(false);
    this->f_draw_seq = gd::gd_neg(gd::GdVal::from_int(1LL));
    this->f_globalChainOpen = gd::GdVal::from_bool(false);
}
const gd::GdClassMeta* Gd__gd_core__CoreRng::meta() const { return &META_Gd__gd_core__CoreRng; }
gd::GdVal Gd__gd_core__CoreRng::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_BalancedRng_1653: return gd::GdVal::from_cls(&META_Gd__gd_core__CoreRng__INNER__BalancedRng);
        case SYM_GEN_BalancedRange_1654: return gd::GdVal::from_cls(&META_Gd__gd_core__CoreRng__INNER__BalancedRange);
        default: break;
    }
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreRng::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreRng::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_rng_1377: out = this->f_rng; return true;
        case SYM_GEN_debug_flip_tag_1632: out = this->f_debug_flip_tag; return true;
        case SYM_GEN_oracle_trace_1633: out = this->f_oracle_trace; return true;
        case SYM_GEN_oracle_trace_log_1634: out = this->f_oracle_trace_log; return true;
        case SYM_GEN__stacktrace_1635: out = this->f__stacktrace; return true;
        case SYM_GEN_draw_seq_1636: out = this->f_draw_seq; return true;
        case SYM_GEN_globalChainOpen_1637: out = this->f_globalChainOpen; return true;
        case SYM_GEN_BalancedRng_1653: out = gd::GdVal::from_cls(&META_Gd__gd_core__CoreRng__INNER__BalancedRng); return true;
        case SYM_GEN_BalancedRange_1654: out = gd::GdVal::from_cls(&META_Gd__gd_core__CoreRng__INNER__BalancedRange); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreRng::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_rng_1377: this->f_rng = val; return true;
        case SYM_GEN_debug_flip_tag_1632: this->f_debug_flip_tag = val; return true;
        case SYM_GEN_oracle_trace_1633: this->f_oracle_trace = val; return true;
        case SYM_GEN_oracle_trace_log_1634: this->f_oracle_trace_log = val; return true;
        case SYM_GEN__stacktrace_1635: this->f__stacktrace = val; return true;
        case SYM_GEN_draw_seq_1636: this->f_draw_seq = val; return true;
        case SYM_GEN_globalChainOpen_1637: this->f_globalChainOpen = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreRng::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case gd::SYM_set_state: return true;
        case SYM_GEN_roll_1638: return true;
        case SYM_GEN_flip_1639: return true;
        case SYM_GEN_flipPercent_1640: return true;
        case SYM_GEN_flipRound_1641: return true;
        case SYM_GEN_flipWeighted_1642: return true;
        case SYM_GEN__trace_1643: return true;
        case SYM_GEN_trace_event_1644: return true;
        case SYM_GEN_trace_diag_1645: return true;
        case SYM_GEN_bare_draw_seq_1646: return true;
        case SYM_GEN_bare_randf_range_1647: return true;
        case SYM_GEN_bare_randf_1648: return true;
        case SYM_GEN_bare_randi_range_1649: return true;
        case gd::SYM_randf_range: return true;
        case gd::SYM_randi_range: return true;
        case SYM_GEN_pickRandomElement_1650: return true;
        case gd::SYM_shuffle: return true;
        case SYM_GEN_shuffleEngine_1651: return true;
        case SYM_GEN_pickRandomEngine_1652: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreRng::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case gd::SYM_set_state: out = fn_set_state(args, argc); return true;
        case SYM_GEN_roll_1638: out = fn_roll(args, argc); return true;
        case SYM_GEN_flip_1639: out = fn_flip(args, argc); return true;
        case SYM_GEN_flipPercent_1640: out = fn_flipPercent(args, argc); return true;
        case SYM_GEN_flipRound_1641: out = fn_flipRound(args, argc); return true;
        case SYM_GEN_flipWeighted_1642: out = fn_flipWeighted(args, argc); return true;
        case SYM_GEN__trace_1643: out = fn__trace(args, argc); return true;
        case SYM_GEN_trace_event_1644: out = fn_trace_event(args, argc); return true;
        case SYM_GEN_trace_diag_1645: out = fn_trace_diag(args, argc); return true;
        case SYM_GEN_bare_draw_seq_1646: out = fn_bare_draw_seq(args, argc); return true;
        case SYM_GEN_bare_randf_range_1647: out = fn_bare_randf_range(args, argc); return true;
        case SYM_GEN_bare_randf_1648: out = fn_bare_randf(args, argc); return true;
        case SYM_GEN_bare_randi_range_1649: out = fn_bare_randi_range(args, argc); return true;
        case gd::SYM_randf_range: out = fn_randf_range(args, argc); return true;
        case gd::SYM_randi_range: out = fn_randi_range(args, argc); return true;
        case SYM_GEN_pickRandomElement_1650: out = fn_pickRandomElement(args, argc); return true;
        case gd::SYM_shuffle: out = fn_shuffle(args, argc); return true;
        case SYM_GEN_shuffleEngine_1651: out = fn_shuffleEngine(args, argc); return true;
        case SYM_GEN_pickRandomEngine_1652: out = fn_pickRandomEngine(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreRng::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return false;
}
gd::GdVal Gd__gd_core__CoreRng::fn__init(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__seed = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv__seed = gd::gd_coerce_int(lv__seed);
    this->f_rng = gd::GdVal::from_rng(gd_ctx.arena.make<gd::GdRng>());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv__seed, gd::GdVal::from_int(0LL))))) {
        (void)gd::call_method(gd_ctx, this->f_rng, gd::SYM_randomize, nullptr, 0);
    }
    else {
        gd::set_prop(gd_ctx, this->f_rng, gd::SYM_seed, lv__seed);
    }
    this->f__stacktrace = gd::GdVal::from_bool(gd::gd_ne(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_set_state(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_state = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_state = gd::gd_coerce_int(lv_state);
    gd::set_prop(gd_ctx, this->f_rng, gd::SYM_state, lv_state);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_roll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_maximum = (_argc > 0) ? _args[0] : (gd::GdVal::from_float(100.0));
    lv_maximum = gd::gd_coerce_float(lv_maximum);
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), lv_maximum}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_flip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : (gd::GdVal::from_float(0.5));
    lv_chance = gd::gd_coerce_float(lv_chance);
    gd::GdVal lv_r = gd::call_method(gd_ctx, this->f_rng, gd::SYM_randf, nullptr, 0);
    if (gd::gd_truth(this->f_oracle_trace)) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "randf", 5u)), gd::GdVal::from_int(0LL), gd::GdVal::from_int(0LL), lv_r}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__trace_1643, _ca, 4); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "randf", 5u)), gd::GdVal::from_int(0LL), gd::GdVal::from_int(0LL), lv_r}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_bare_draw_seq_1646, _ca, 4); })();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(gd::GdVal::from_cstr(gd_ctx.arena, ""), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_debug_flip_tag, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u)))))) : gd::GdVal::from_bool(false)))) {
        (void)gd::GdVal::null();
        this->f_debug_flip_tag = gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u));
    }
    return gd::GdVal::from_bool(gd::gd_le(lv_r, lv_chance));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_flipPercent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_chance = gd::gd_coerce_float(lv_chance);
    return gd::GdVal::from_bool(gd::gd_le(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_roll_1638, nullptr, 0), lv_chance));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_flipRound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_chance = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_chance = gd::gd_coerce_float(lv_chance);
    return gd::gd_coerce_int(gd::gd_add(gd_ctx, gd::gd_floor(lv_chance), gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::gd_fmod(lv_chance, gd::GdVal::from_float(1.0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_flip_1639, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_flipWeighted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_weights = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_sum = gd::GdVal::from_float(0.0);
    {
        gd::GdVal _t665 = gd::gd_iter_seq(gd_ctx.arena, lv_weights);
        gd::GdArr* _t666 = (_t665.kind == gd::GdVal::Kind::Arr) ? _t665.arr : nullptr;
        uint32_t _len__t667 = _t666 ? _t666->len : 0u;
        for (uint32_t _t667 = 0; _t667 < _len__t667; ++_t667) {
            gd::GdVal lv_weight = _t666->data[_t667];
            lv_sum = gd::gd_add(gd_ctx, lv_sum, lv_weight);
        }
    }
    gd::GdVal lv_val = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), lv_sum, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "flipWeighted", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_randf_range, _ca, 3); })();
    gd::GdVal lv_subsum = gd::GdVal::from_float(0.0);
    {
        gd::GdVal _t668 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, lv_weights, gd::SYM_size, nullptr, 0));
        gd::GdArr* _t669 = (_t668.kind == gd::GdVal::Kind::Arr) ? _t668.arr : nullptr;
        uint32_t _len__t670 = _t669 ? _t669->len : 0u;
        for (uint32_t _t670 = 0; _t670 < _len__t670; ++_t670) {
            gd::GdVal lv_i = _t669->data[_t670];
            lv_subsum = gd::gd_add(gd_ctx, lv_subsum, gd::get_index(gd_ctx, lv_weights, lv_i));
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_subsum, lv_val)))) {
                return lv_i;
            }
        }
    }
    return gd::call_method(gd_ctx, lv_weights, gd::SYM_size, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn__trace(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_kind = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_from = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_to = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_r = (_argc > 3) ? _args[3] : gd::GdVal::null();
    gd::GdVal lv_row = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::call_method(gd_ctx, this->f_oracle_trace_log, gd::SYM_size, nullptr, 0), lv_kind, lv_from, lv_to, lv_r, gd::GdVal::from_float(0.0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u)), ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, this->f_rng, gd::SYM_get_state, nullptr, 0)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}));
    if (gd::gd_truth(this->f__stacktrace)) {
        gd::GdVal lv_frames = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
        gd::GdVal lv_st = gd::GdVal::null();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_st, gd::GdVal::null())))) {
            {
                gd::GdVal _t671 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL), gd::gd_min(gd::GdVal::from_int(5LL), gd::call_method(gd_ctx, lv_st, gd::SYM_size, nullptr, 0))}; return gd::gd_range(gd_ctx.arena, _ca, 2); })());
                gd::GdArr* _t672 = (_t671.kind == gd::GdVal::Kind::Arr) ? _t671.arr : nullptr;
                uint32_t _len__t673 = _t672 ? _t672->len : 0u;
                for (uint32_t _t673 = 0; _t673 < _len__t673; ++_t673) {
                    gd::GdVal lv_i = _t672->data[_t673];
                    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mod(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "%s:%d:%s", 8u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::call_method(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_index(gd_ctx, gd::get_index(gd_ctx, lv_st, lv_i), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "source", 6u))))), SYM_GEN_get_file_2717, nullptr, 0), gd::gd_coerce_int(gd::get_index(gd_ctx, gd::get_index(gd_ctx, lv_st, lv_i), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "line", 4u)))), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::get_index(gd_ctx, gd::get_index(gd_ctx, lv_st, lv_i), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "function", 8u)))))})))}; return gd::call_method(gd_ctx, lv_frames, gd::SYM_append, _ca, 1); })();
                }
            }
        }
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "<-", 2u))}; return gd::call_method(gd_ctx, (lv_frames), gd::SYM_join, _ca, 1); })()}; return gd::call_method(gd_ctx, lv_row, gd::SYM_append, _ca, 1); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_row}; return gd::call_method(gd_ctx, this->f_oracle_trace_log, gd::SYM_push_back, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_trace_event(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::call_method(gd_ctx, this->f_oracle_trace_log, gd::SYM_size, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "EVENT", 5u)), ([&]() { gd::GdVal _ca[] = {lv_type}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u)), gd::GdVal::from_float(0.0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u)), ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, this->f_rng, gd::SYM_get_state, nullptr, 0)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}))}; return gd::call_method(gd_ctx, this->f_oracle_trace_log, gd::SYM_push_back, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_trace_diag(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_kind = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_a = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_b = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_c = (_argc > 3) ? _args[3] : (gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u)));
    if (gd::gd_truth((gd::gd_truth(this->f_oracle_trace) ? gd::GdVal::from_bool(gd::gd_truth(this->f__stacktrace)) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::call_method(gd_ctx, this->f_oracle_trace_log, gd::SYM_size, nullptr, 0), lv_kind, ([&]() { gd::GdVal _ca[] = {lv_a}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), ([&]() { gd::GdVal _ca[] = {lv_b}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), ([&]() { gd::GdVal _ca[] = {lv_c}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })()}))}; return gd::call_method(gd_ctx, this->f_oracle_trace_log, gd::SYM_push_back, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_bare_draw_seq(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_kind = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_from = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_to = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_r = (_argc > 3) ? _args[3] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_draw_seq, gd::GdVal::from_int(0LL))))) {
        this->f_draw_seq = gd::gd_add(gd_ctx, this->f_draw_seq, gd::GdVal::from_int(1LL));
        (void)gd::GdVal::null();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_bare_randf_range(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_from = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_from = gd::gd_coerce_float(lv_from);
    gd::GdVal lv_to = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_to = gd::gd_coerce_float(lv_to);
    gd::GdVal lv_r = ([&]() { gd::GdVal _ca[] = {lv_from, lv_to}; return gd::call_method(gd_ctx, this->f_rng, gd::SYM_randf_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "randf_range", 11u)), lv_from, lv_to, lv_r}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_bare_draw_seq_1646, _ca, 4); })();
    return lv_r;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_bare_randf(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_r = gd::call_method(gd_ctx, this->f_rng, gd::SYM_randf, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "randf", 5u)), gd::GdVal::from_int(0LL), gd::GdVal::from_int(0LL), lv_r}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_bare_draw_seq_1646, _ca, 4); })();
    return lv_r;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_bare_randi_range(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_from = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_from = gd::gd_coerce_int(lv_from);
    gd::GdVal lv_to = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_to = gd::gd_coerce_int(lv_to);
    gd::GdVal lv_r = ([&]() { gd::GdVal _ca[] = {lv_from, lv_to}; return gd::call_method(gd_ctx, this->f_rng, gd::SYM_randi_range, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "randi_range", 11u)), lv_from, lv_to, lv_r}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_bare_draw_seq_1646, _ca, 4); })();
    return lv_r;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_randf_range(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_from = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_from = gd::gd_coerce_float(lv_from);
    gd::GdVal lv_to = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_to = gd::gd_coerce_float(lv_to);
    gd::GdVal lv_tag = (_argc > 2) ? _args[2] : (gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "randf_range", 11u)));
    gd::GdVal lv_r = ([&]() { gd::GdVal _ca[] = {lv_from, lv_to}; return gd::call_method(gd_ctx, this->f_rng, gd::SYM_randf_range, _ca, 2); })();
    if (gd::gd_truth(this->f_oracle_trace)) {
        (void)([&]() { gd::GdVal _ca[] = {lv_tag, lv_from, lv_to, lv_r}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__trace_1643, _ca, 4); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_tag, lv_from, lv_to, lv_r}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_bare_draw_seq_1646, _ca, 4); })();
    return lv_r;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_randi_range(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_from = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_from = gd::gd_coerce_int(lv_from);
    gd::GdVal lv_to = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_to = gd::gd_coerce_int(lv_to);
    gd::GdVal lv_tag = (_argc > 2) ? _args[2] : (gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "randi_range", 11u)));
    gd::GdVal lv_r = ([&]() { gd::GdVal _ca[] = {lv_from, lv_to}; return gd::call_method(gd_ctx, this->f_rng, gd::SYM_randi_range, _ca, 2); })();
    if (gd::gd_truth(this->f_oracle_trace)) {
        (void)([&]() { gd::GdVal _ca[] = {lv_tag, lv_from, lv_to, lv_r}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__trace_1643, _ca, 4); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_tag, lv_from, lv_to, lv_r}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_bare_draw_seq_1646, _ca, 4); })();
    return lv_r;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_pickRandomElement(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_array = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::get_index(gd_ctx, lv_array, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), gd::gd_sub(gd::call_method(gd_ctx, lv_array, gd::SYM_size, nullptr, 0), gd::GdVal::from_int(1LL)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "pickRandomElement", 17u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_randi_range, _ca, 3); })());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_shuffle(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_array = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_n = gd::gd_coerce_int(gd::call_method(gd_ctx, lv_array, gd::SYM_size, nullptr, 0));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_n, gd::GdVal::from_int(2LL))))) {
        return lv_array;
    }
    {
        gd::GdVal _t674 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::gd_sub(lv_n, gd::GdVal::from_int(1LL))}; return gd::gd_range(gd_ctx.arena, _ca, 1); })());
        gd::GdArr* _t675 = (_t674.kind == gd::GdVal::Kind::Arr) ? _t674.arr : nullptr;
        uint32_t _len__t676 = _t675 ? _t675->len : 0u;
        for (uint32_t _t676 = 0; _t676 < _len__t676; ++_t676) {
            gd::GdVal lv_i = _t675->data[_t676];
            gd::GdVal lv_r = gd::call_method(gd_ctx, this->f_rng, gd::SYM_randi, nullptr, 0);
            if (gd::gd_truth(this->f_oracle_trace)) {
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "randi", 5u)), gd::GdVal::from_int(0LL), gd::GdVal::from_int(0LL), lv_r}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__trace_1643, _ca, 4); })();
            }
            gd::GdVal lv_j = gd::gd_coerce_int(gd::gd_mod(gd_ctx, gd::gd_coerce_int(gd::gd_abs(lv_r)), gd::gd_sub(lv_n, lv_i)));
            gd::GdVal lv_tmp = gd::get_index(gd_ctx, lv_array, lv_i);
            { gd::GdVal _t677 = lv_array; gd::GdVal _t678 = lv_i; gd::set_index(gd_ctx, _t677, _t678, gd::get_index(gd_ctx, lv_array, gd::gd_add(gd_ctx, lv_i, lv_j))); }
            { gd::GdVal _t679 = lv_array; gd::GdVal _t680 = gd::gd_add(gd_ctx, lv_i, lv_j); gd::set_index(gd_ctx, _t679, _t680, lv_tmp); }
        }
    }
    return lv_array;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_shuffleEngine(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_array = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_tag = (_argc > 1) ? _args[1] : (gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Gshuffle", 8u)));
    (void)gd::call_method(gd_ctx, lv_array, gd::SYM_shuffle, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(this->f_globalChainOpen) ? gd::GdVal::from_bool(gd::gd_truth(this->f_oracle_trace)) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::call_method(gd_ctx, this->f_oracle_trace_log, gd::SYM_size, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Gshuffle", 8u)), lv_tag, gd::call_method(gd_ctx, lv_array, gd::SYM_size, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}))}; return gd::call_method(gd_ctx, this->f_oracle_trace_log, gd::SYM_push_back, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreRng::fn_pickRandomEngine(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_array = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_tag = (_argc > 1) ? _args[1] : (gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Gpick", 5u)));
    gd::GdVal lv_v = gd::call_method(gd_ctx, lv_array, gd::SYM_pick_random, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(this->f_globalChainOpen) ? gd::GdVal::from_bool(gd::gd_truth(this->f_oracle_trace)) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::call_method(gd_ctx, this->f_oracle_trace_log, gd::SYM_size, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Gpick", 5u)), lv_tag, gd::call_method(gd_ctx, lv_array, gd::SYM_size, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}))}; return gd::call_method(gd_ctx, this->f_oracle_trace_log, gd::SYM_push_back, _ca, 1); })();
    }
    return lv_v;
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreRng(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__CoreRng>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__CoreRng = {CLS_Gd__gd_core__CoreRng, "CoreRng", "res://gd_core/CoreRng.gd", nullptr, false, _alloc_Gd__gd_core__CoreRng, &Gd__gd_core__CoreRng::get_static_prop_fn, &Gd__gd_core__CoreRng::call_static_fn};

void Gd__gd_core__DeathScythe::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
    this->f_critBonusActive = gd::GdVal::from_bool(false);
    this->f_poisonThreshold = gd::GdVal::from_int(0);
    this->f_activationParticles = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__DeathScythe::meta() const { return &META_Gd__gd_core__DeathScythe; }
gd::GdVal Gd__gd_core__DeathScythe::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__DeathScythe::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__DeathScythe::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_critBonusActive_1734: out = this->f_critBonusActive; return true;
        case SYM_GEN_poisonThreshold_1735: out = this->f_poisonThreshold; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__DeathScythe::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_critBonusActive_1734: this->f_critBonusActive = val; return true;
        case SYM_GEN_poisonThreshold_1735: this->f_poisonThreshold = gd::gd_coerce_int(val); return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__DeathScythe::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onOpponentPoisonChanged_1736: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__DeathScythe::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onOpponentPoisonChanged_1736: out = fn_onOpponentPoisonChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__DeathScythe::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__DeathScythe::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Stack_859), SYM_GEN_Poison_2567)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_gainsStack_88, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeathScythe::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_poison_changed", 24u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onOpponentPoisonChanged", 23u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    {
        gd::GdVal _t681 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t682 = (_t681.kind == gd::GdVal::Kind::Arr) ? _t681.arr : nullptr;
        uint32_t _len__t683 = _t682 ? _t682->len : 0u;
        for (uint32_t _t683 = 0; _t683 < _len__t683; ++_t683) {
            gd::GdVal lv_item = _t682->data[_t683];
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Poison_2567), gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_giveBuffPower_305, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeathScythe::fn_onOpponentPoisonChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_curPoison = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_getPoison_1213, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_critBonusActive))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_curPoison, this->f_poisonThreshold)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeCritChancePercent_183, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeathScythe::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeathScythe::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__critBonusActive = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv__critBonusActive)) {
    }
    else {
    }
    this->f_critBonusActive = lv__critBonusActive;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DeathScythe::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_poisonThreshold = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__DeathScythe(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__DeathScythe>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__DeathScythe = {CLS_Gd__gd_core__DeathScythe, "DeathScythe", "res://gd_core/DeathScythe.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__DeathScythe, &Gd__gd_core__DeathScythe::get_static_prop_fn, &Gd__gd_core__DeathScythe::call_static_fn};

void Gd__gd_core__Garlic::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Food::init_fields(gd_ctx);
    this->f_extraBlock = gd::GdVal::from_int(0LL);
}
const gd::GdClassMeta* Gd__gd_core__Garlic::meta() const { return &META_Gd__gd_core__Garlic; }
gd::GdVal Gd__gd_core__Garlic::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Garlic::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Garlic::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_extraBlock_1783: out = this->f_extraBlock; return true;
        default: break;
    }
    return Gd__gd_core__Food::get_prop(prop, out);
}
bool Gd__gd_core__Garlic::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_extraBlock_1783: this->f_extraBlock = val; return true;
        default: break;
    }
    return Gd__gd_core__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Garlic::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_addBonusBlock_1784: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Food::has_own_method(m);
}
bool Gd__gd_core__Garlic::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_addBonusBlock_1784: out = fn_addBonusBlock(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Garlic::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Garlic::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_206, nullptr, 0), this->f_extraBlock)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, _ca, 1); })();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeVampirism_341, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Garlic::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_extraBlock = gd::GdVal::from_int(0LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Garlic::fn_addBonusBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__extraBlock = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_extraBlock = gd::gd_add(gd_ctx, this->f_extraBlock, lv__extraBlock);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Garlic::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Food::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Garlic(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Garlic>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Garlic = {CLS_Gd__gd_core__Garlic, "Garlic", "res://gd_core/Garlic.gd", &META_Gd__gd_core__Food, false, _alloc_Gd__gd_core__Garlic, &Gd__gd_core__Garlic::get_static_prop_fn, &Gd__gd_core__Garlic::call_static_fn};

void Gd__gd_core__Item__INNER__SignalConnection::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_emitter = gd::GdVal::null();
    this->f_signalName = gd::GdVal::null();
    this->f_receiver = gd::GdVal::null();
    this->f_methodName = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__Item__INNER__SignalConnection::meta() const { return &META_Gd__gd_core__Item__INNER__SignalConnection; }
gd::GdVal Gd__gd_core__Item__INNER__SignalConnection::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return gd::GdVal::null();
}
bool Gd__gd_core__Item__INNER__SignalConnection::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Item__INNER__SignalConnection::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_emitter_1558: out = this->f_emitter; return true;
        case SYM_GEN_signalName_1013: out = this->f_signalName; return true;
        case SYM_GEN_receiver_1559: out = this->f_receiver; return true;
        case SYM_GEN_methodName_1560: out = this->f_methodName; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__Item__INNER__SignalConnection::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_emitter_1558: this->f_emitter = val; return true;
        case SYM_GEN_signalName_1013: this->f_signalName = val; return true;
        case SYM_GEN_receiver_1559: this->f_receiver = val; return true;
        case SYM_GEN_methodName_1560: this->f_methodName = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__Item__INNER__SignalConnection::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_destroy_1561: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__Item__INNER__SignalConnection::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_destroy_1561: out = fn_destroy(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__Item__INNER__SignalConnection::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return false;
}
gd::GdVal Gd__gd_core__Item__INNER__SignalConnection::fn__init(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__emitter = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__signalName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv__receiver = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv__methodName = (_argc > 3) ? _args[3] : gd::GdVal::null();
    gd::GdVal lv_binds = (_argc > 4) ? _args[4] : (gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})));
    this->f_emitter = lv__emitter;
    this->f_signalName = lv__signalName;
    this->f_receiver = lv__receiver;
    this->f_methodName = lv__methodName;
    (void)([&]() { gd::GdVal _ca[] = {this->f_signalName, this->f_receiver, this->f_methodName, lv_binds}; return gd::call_method(gd_ctx, this->f_emitter, gd::SYM_connect, _ca, 4); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item__INNER__SignalConnection::fn_destroy(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Item__INNER__SignalConnection(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Item__INNER__SignalConnection>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Item__INNER__SignalConnection = {CLS_Gd__gd_core__Item__INNER__SignalConnection, "SignalConnection", "", nullptr, false, _alloc_Gd__gd_core__Item__INNER__SignalConnection, &Gd__gd_core__Item__INNER__SignalConnection::get_static_prop_fn, &Gd__gd_core__Item__INNER__SignalConnection::call_static_fn};

void Gd__gd_core__Shield::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_blockedDamageRes = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__Shield::meta() const { return &META_Gd__gd_core__Shield; }
gd::GdVal Gd__gd_core__Shield::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Shield::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Shield::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_blockedDamageRes_1844: out = this->f_blockedDamageRes; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__Shield::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blockedDamageRes_1844: this->f_blockedDamageRes = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Shield::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_prepare_124: return true;
        case SYM_GEN_getDamageBlock_1845: return true;
        case SYM_GEN_beforeBlock_1846: return true;
        case SYM_GEN_afterBlock_1847: return true;
        case SYM_GEN_canBlockDamageRes_1848: return true;
        case SYM_GEN_preTakeDamage_1849: return true;
        case SYM_GEN_onCharacterAttacked_1850: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Shield::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_prepare_124: out = fn_prepare(args, argc); return true;
        case SYM_GEN_getDamageBlock_1845: out = fn_getDamageBlock(args, argc); return true;
        case SYM_GEN_beforeBlock_1846: out = fn_beforeBlock(args, argc); return true;
        case SYM_GEN_afterBlock_1847: out = fn_afterBlock(args, argc); return true;
        case SYM_GEN_canBlockDamageRes_1848: out = fn_canBlockDamageRes(args, argc); return true;
        case SYM_GEN_preTakeDamage_1849: out = fn_preTakeDamage(args, argc); return true;
        case SYM_GEN_onCharacterAttacked_1850: out = fn_onCharacterAttacked(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Shield::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Shield::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_blockedDamageRes = gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "pre_take_damage", 15u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "preTakeDamage", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_attacked", 18u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onCharacterAttacked", 19u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_prepare_124, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Shield::fn_getDamageBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "damblock", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Shield::fn_beforeBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getDamageBlock_1845, nullptr, 0), gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, this->f_blockedDamageRes, SYM_GEN_applyDamageReduction_1435, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Shield::fn_afterBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Shield::fn_canBlockDamageRes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_triggerOnMeleeAttacked_1438, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Shield::fn_preTakeDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_damageRes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canBlockDamageRes_1848, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        this->f_blockedDamageRes = lv_damageRes;
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_beforeBlock_1846, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Shield::fn_onCharacterAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_blockedDamageRes, lv_damageRes)))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_afterBlock_1847, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blocked", 7u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {this->f_blockedDamageRes}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitSignal_1501, _ca, 3); })();
        this->f_blockedDamageRes = gd::GdVal::null();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Shield::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Shield(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Shield>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Shield = {CLS_Gd__gd_core__Shield, "Shield", "res://gd_core/Shield.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__Shield, &Gd__gd_core__Shield::get_static_prop_fn, &Gd__gd_core__Shield::call_static_fn};

void Gd__gd_core__Present::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_activationParticles = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__Present::meta() const { return &META_Gd__gd_core__Present; }
gd::GdVal Gd__gd_core__Present::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Present::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Present::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__Present::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Present::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_getShopPriority_853: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Present::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_getShopPriority_853: out = fn_getShopPriority(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Present::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Present::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_371, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Present::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Present::fn_getShopPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_856), SYM_GEN_Low_2718), gd::GdVal::from_int(1LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Present::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Present(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Present>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Present = {CLS_Gd__gd_core__Present, "Present", "res://gd_core/Present.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__Present, &Gd__gd_core__Present::get_static_prop_fn, &Gd__gd_core__Present::call_static_fn};

void Gd__gd_core__StaminaSack::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Bag::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__StaminaSack::meta() const { return &META_Gd__gd_core__StaminaSack; }
gd::GdVal Gd__gd_core__StaminaSack::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Bag::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__StaminaSack::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__StaminaSack::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Bag::get_prop(prop, out);
}
bool Gd__gd_core__StaminaSack::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__StaminaSack::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_addToInventory_122: return true;
        case SYM_GEN_onRemoveFromInventory_420: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Bag::has_own_method(m);
}
bool Gd__gd_core__StaminaSack::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_addToInventory_122: out = fn_addToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_420: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__StaminaSack::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__StaminaSack::fn_addToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__inventory = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__occupiedCells = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv__placedByPlayer = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv__placedByPlayer = gd::gd_coerce_bool(lv__placedByPlayer);
    (void)([&]() { gd::GdVal _ca[] = {lv__inventory, lv__occupiedCells, lv__placedByPlayer}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Bag::call_method(gd_ctx, SYM_GEN_addToInventory_122, _ca, 3, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_PlayerInventory_2555))))) {
        (void)gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeBaseMaxStamina_1256, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StaminaSack::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Bag::call_method(gd_ctx, SYM_GEN_onRemoveFromInventory_420, nullptr, 0, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_BuildViewer_2554))))) {
        (void)gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeBaseMaxStamina_1256, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StaminaSack::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Bagtacular", 10u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isTypeInInventory_805, _ca, 1); })())) {
        gd::GdVal lv_stamina = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Bagtacular", 10u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })(), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
        (void)([&]() { gd::GdVal _ca[] = {lv_stamina}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_giveStaminaRegeneration_1254, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StaminaSack::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Bag::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__StaminaSack(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__StaminaSack>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__StaminaSack = {CLS_Gd__gd_core__StaminaSack, "StaminaSack", "res://gd_core/StaminaSack.gd", &META_Gd__gd_core__Bag, false, _alloc_Gd__gd_core__StaminaSack, &Gd__gd_core__StaminaSack::get_static_prop_fn, &Gd__gd_core__StaminaSack::call_static_fn};

void Gd__gd_core__TheLovers::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Card::init_fields(gd_ctx);
    this->f_heartParticles = gd::GdVal::null();
    this->f_healAmp = gd::GdVal::null();
    this->f_dam = gd::GdVal::null();
    this->f_regen = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__TheLovers::meta() const { return &META_Gd__gd_core__TheLovers; }
gd::GdVal Gd__gd_core__TheLovers::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Card::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__TheLovers::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__TheLovers::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_heartParticles_1902: out = this->f_heartParticles; return true;
        case SYM_GEN_healAmp_1903: out = this->f_healAmp; return true;
        case SYM_GEN_dam_939: out = this->f_dam; return true;
        case SYM_GEN_regen_1904: out = this->f_regen; return true;
        default: break;
    }
    return Gd__gd_core__Card::get_prop(prop, out);
}
bool Gd__gd_core__TheLovers::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_heartParticles_1902: this->f_heartParticles = val; return true;
        case SYM_GEN_healAmp_1903: this->f_healAmp = val; return true;
        case SYM_GEN_dam_939: this->f_dam = val; return true;
        case SYM_GEN_regen_1904: this->f_regen = val; return true;
        default: break;
    }
    return Gd__gd_core__Card::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__TheLovers::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_cardSecondaryEffectActive_890: return true;
        case SYM_GEN_doRevealEffect_893: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Card::has_own_method(m);
}
bool Gd__gd_core__TheLovers::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_cardSecondaryEffectActive_890: out = fn_cardSecondaryEffectActive(args, argc); return true;
        case SYM_GEN_doRevealEffect_893: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Card::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__TheLovers::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Card::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__TheLovers::fn_cardSecondaryEffectActive(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_eq(gd::gd_mod(gd_ctx, this->f_chainPosition, gd::GdVal::from_int(2LL)), gd::GdVal::from_int(0LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__TheLovers::fn_doRevealEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cardSecondaryEffectActive_890, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_healAmp}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_addHealingEfficiency_1166, _ca, 1); })();
    }
    (void)([&]() { gd::GdVal _ca[] = {this->f_dam, gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "lifesteal", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealLife_331, _ca, 2); })();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cardSecondaryEffectActive_890, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__TheLovers::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Card::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_healAmp = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healamp", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_dam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__TheLovers(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__TheLovers>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__TheLovers = {CLS_Gd__gd_core__TheLovers, "TheLovers", "res://gd_core/TheLovers.gd", &META_Gd__gd_core__Card, false, _alloc_Gd__gd_core__TheLovers, &Gd__gd_core__TheLovers::get_static_prop_fn, &Gd__gd_core__TheLovers::call_static_fn};

void Gd__gd_core_items__AceofSpades::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Card::init_fields(gd_ctx);
    this->f_spadesParticles = gd::GdVal::null();
    this->f_luck = gd::GdVal::null();
    this->f_spikes = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__AceofSpades::meta() const { return &META_Gd__gd_core_items__AceofSpades; }
gd::GdVal Gd__gd_core_items__AceofSpades::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Card::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__AceofSpades::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__AceofSpades::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_spadesParticles_896: out = this->f_spadesParticles; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_spikes_898: out = this->f_spikes; return true;
        default: break;
    }
    return Gd__gd_core_items__Card::get_prop(prop, out);
}
bool Gd__gd_core_items__AceofSpades::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_spadesParticles_896: this->f_spadesParticles = val; return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_spikes_898: this->f_spikes = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Card::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__AceofSpades::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_cardSecondaryEffectActive_890: return true;
        case SYM_GEN_doRevealEffect_893: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Card::has_own_method(m);
}
bool Gd__gd_core_items__AceofSpades::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_cardSecondaryEffectActive_890: out = fn_cardSecondaryEffectActive(args, argc); return true;
        case SYM_GEN_doRevealEffect_893: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Card::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__AceofSpades::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Card::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__AceofSpades::fn_cardSecondaryEffectActive(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_eq(gd::gd_mod(gd_ctx, this->f_chainPosition, gd::GdVal::from_int(2LL)), gd::GdVal::from_int(1LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__AceofSpades::fn_doRevealEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveCritTokens_316, _ca, 1); })();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cardSecondaryEffectActive_890, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_spikes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_211, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__AceofSpades::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Card::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__AceofSpades(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__AceofSpades>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__AceofSpades = {CLS_Gd__gd_core_items__AceofSpades, "AceofSpades", "res://gd_core_items/AceofSpades.gd", &META_Gd__gd_core_items__Card, true, _alloc_Gd__gd_core_items__AceofSpades, &Gd__gd_core_items__AceofSpades::get_static_prop_fn, &Gd__gd_core_items__AceofSpades::call_static_fn};

void Gd__gd_core_items__Bow::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_affectedWeapon = gd::GdVal::null();
    this->f_activationParticles = gd::GdVal::null();
    this->f_light = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Bow::meta() const { return &META_Gd__gd_core_items__Bow; }
gd::GdVal Gd__gd_core_items__Bow::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Bow::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Bow::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_affectedWeapon_948: out = this->f_affectedWeapon; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_light_949: out = this->f_light; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Bow::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedWeapon_948: this->f_affectedWeapon = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_light_949: this->f_light = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Bow::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_prepare_124: return true;
        case SYM_GEN_onWeaponAttacked_950: return true;
        case SYM_GEN_combatEnd_133: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Bow::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_prepare_124: out = fn_prepare(args, argc); return true;
        case SYM_GEN_onWeaponAttacked_950: out = fn_onWeaponAttacked(args, argc); return true;
        case SYM_GEN_combatEnd_133: out = fn_combatEnd(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Bow::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Bow::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_isWeapon_84, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bow::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_affectedWeapon = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getFirstAffectedItem_430, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_affectedWeapon, gd::GdVal::null())))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_affectedWeapon, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attacked", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onWeaponAttacked", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    }
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN_prepare_124, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bow::fn_onWeaponAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bow::fn_combatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN_combatEnd_133, nullptr, 0, _out); return _out; })();
    this->f_affectedWeapon = gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bow::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Bow(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Bow>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Bow = {CLS_Gd__gd_core_items__Bow, "Bow", "res://gd_core_items/Bow.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Bow, &Gd__gd_core_items__Bow::get_static_prop_fn, &Gd__gd_core_items__Bow::call_static_fn};

void Gd__gd_core_items__CustomerCard::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__CustomerCard::meta() const { return &META_Gd__gd_core_items__CustomerCard; }
gd::GdVal Gd__gd_core_items__CustomerCard::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__CustomerCard::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__CustomerCard::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__CustomerCard::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__CustomerCard::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCalcTradeChance_1730: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__CustomerCard::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCalcTradeChance_1730: out = fn_onCalcTradeChance(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__CustomerCard::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__CustomerCard::fn_onCalcTradeChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CustomerCard::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__CustomerCard(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__CustomerCard>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__CustomerCard = {CLS_Gd__gd_core_items__CustomerCard, "CustomerCard", "res://gd_core_items/CustomerCard.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__CustomerCard, &Gd__gd_core_items__CustomerCard::get_static_prop_fn, &Gd__gd_core_items__CustomerCard::call_static_fn};

void Gd__gd_core_items__Exclusive__AmuletofAlchemy::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_potionsToTrigger = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_potionTriggerTimer = gd::GdVal::null();
    this->f_delay = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__AmuletofAlchemy::meta() const { return &META_Gd__gd_core_items__Exclusive__AmuletofAlchemy; }
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAlchemy::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_amuletColor_1927: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.266667), gd::GdVal::from_float(0.309804), gd::GdVal::from_float(0.960784)}; return gd::make_color_from_args(_ca, 3); })();
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__AmuletofAlchemy::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__AmuletofAlchemy::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_potionsToTrigger_1930: out = this->f_potionsToTrigger; return true;
        case SYM_GEN_potionTriggerTimer_1931: out = this->f_potionTriggerTimer; return true;
        case SYM_GEN_delay_1932: out = this->f_delay; return true;
        case SYM_GEN_amuletColor_1927: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__AmuletofAlchemy::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_potionsToTrigger_1930: this->f_potionsToTrigger = val; return true;
        case SYM_GEN_potionTriggerTimer_1931: this->f_potionTriggerTimer = val; return true;
        case SYM_GEN_delay_1932: this->f_delay = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__AmuletofAlchemy::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onPotionEmptied_1872: return true;
        case SYM_GEN_triggerNextPotion_1933: return true;
        case SYM_GEN_onCombatEnd_134: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__AmuletofAlchemy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onPotionEmptied_1872: out = fn_onPotionEmptied(args, argc); return true;
        case SYM_GEN_triggerNextPotion_1933: out = fn_triggerNextPotion(args, argc); return true;
        case SYM_GEN_onCombatEnd_134: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__AmuletofAlchemy::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAlchemy::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Potion_2652)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAlchemy::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t684 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t685 = (_t684.kind == gd::GdVal::Kind::Arr) ? _t684.arr : nullptr;
        uint32_t _len__t686 = _t685 ? _t685->len : 0u;
        for (uint32_t _t686 = 0; _t686 < _len__t686; ++_t686) {
            gd::GdVal lv_item = _t685->data[_t686];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "potion_emptied", 14u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onPotionEmptied", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAlchemy::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_371, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAlchemy::fn_onPotionEmptied(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_potion = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_potion}; return gd::call_method(gd_ctx, this->f_potionsToTrigger, gd::SYM_push_back, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_delay}; return gd::call_method(gd_ctx, this->f_potionTriggerTimer, SYM_GEN_start_1685, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAlchemy::fn_triggerNextPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_potion = gd::call_method(gd_ctx, this->f_potionsToTrigger, gd::SYM_pop_front, nullptr, 0);
    (void)gd::call_method(gd_ctx, lv_potion, SYM_GEN_triggerPotion_1755, nullptr, 0);
    (void)gd::call_method(gd_ctx, lv_potion, SYM_GEN_miniActivate_472, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAlchemy::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_potionTriggerTimer, SYM_GEN_stop_1686, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_potionsToTrigger, gd::SYM_clear, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAlchemy::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_potionTriggerTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "PotionTriggerTimer", 18u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "triggerNextPotion", 17u)), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_137, _ca, 3); })();
    this->f_delay = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "delay", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__AmuletofAlchemy(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__AmuletofAlchemy>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AmuletofAlchemy = {CLS_Gd__gd_core_items__Exclusive__AmuletofAlchemy, "AmuletofAlchemy", "res://gd_core_items/Exclusive/AmuletofAlchemy.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__AmuletofAlchemy, &Gd__gd_core_items__Exclusive__AmuletofAlchemy::get_static_prop_fn, &Gd__gd_core_items__Exclusive__AmuletofAlchemy::call_static_fn};

void Gd__gd_core_items__Exclusive__WisdomPuppy::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__WisdomPuppy::meta() const { return &META_Gd__gd_core_items__Exclusive__WisdomPuppy; }
gd::GdVal Gd__gd_core_items__Exclusive__WisdomPuppy::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__WisdomPuppy::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__WisdomPuppy::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__WisdomPuppy::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__WisdomPuppy::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN_playDropSound_151: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__WisdomPuppy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_151: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__WisdomPuppy::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__WisdomPuppy::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WisdomPuppy::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WisdomPuppy::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Pet_2600)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WisdomPuppy::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseCold_354, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WisdomPuppy::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0)), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WisdomPuppy::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__WisdomPuppy(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__WisdomPuppy>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__WisdomPuppy = {CLS_Gd__gd_core_items__Exclusive__WisdomPuppy, "WisdomPuppy", "res://gd_core_items/Exclusive/WisdomPuppy.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__WisdomPuppy, &Gd__gd_core_items__Exclusive__WisdomPuppy::get_static_prop_fn, &Gd__gd_core_items__Exclusive__WisdomPuppy::call_static_fn};

void Gd__gd_core_items__Exclusive__BionicArmor::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_blockHealthAcc = gd::GdVal::from_int(0);
    this->f_staminaRegenMalus = gd::GdVal::null();
    this->f_healthThreshold = gd::GdVal::null();
    this->f_maxStamina = gd::GdVal::null();
    this->f_staminaThreshold = gd::GdVal::null();
    this->f_staminaUsed = gd::GdVal::null();
    this->f_empower = gd::GdVal::null();
    this->f_block2 = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__BionicArmor::meta() const { return &META_Gd__gd_core_items__Exclusive__BionicArmor; }
gd::GdVal Gd__gd_core_items__Exclusive__BionicArmor::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__BionicArmor::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__BionicArmor::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_blockHealthAcc_1978: out = this->f_blockHealthAcc; return true;
        case SYM_GEN_staminaRegenMalus_1979: out = this->f_staminaRegenMalus; return true;
        case SYM_GEN_healthThreshold_1759: out = this->f_healthThreshold; return true;
        case SYM_GEN_maxStamina_1054: out = this->f_maxStamina; return true;
        case SYM_GEN_staminaThreshold_1980: out = this->f_staminaThreshold; return true;
        case SYM_GEN_staminaUsed_1981: out = this->f_staminaUsed; return true;
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        case SYM_GEN_block2_1982: out = this->f_block2; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BionicArmor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blockHealthAcc_1978: this->f_blockHealthAcc = gd::gd_coerce_int(val); return true;
        case SYM_GEN_staminaRegenMalus_1979: this->f_staminaRegenMalus = val; return true;
        case SYM_GEN_healthThreshold_1759: this->f_healthThreshold = val; return true;
        case SYM_GEN_maxStamina_1054: this->f_maxStamina = val; return true;
        case SYM_GEN_staminaThreshold_1980: this->f_staminaThreshold = val; return true;
        case SYM_GEN_staminaUsed_1981: this->f_staminaUsed = val; return true;
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        case SYM_GEN_block2_1982: this->f_block2 = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BionicArmor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onHealOrBlockChanged_1983: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BionicArmor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onHealOrBlockChanged_1983: out = fn_onHealOrBlockChanged(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__BionicArmor::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__BionicArmor::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_blockHealthAcc = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    gd::GdVal lv_baseStaminaRegen = gd::get_prop(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_baseStaminaRegen_1057);
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_staminaRegenMalus, lv_baseStaminaRegen)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_giveStaminaRegeneration_1254, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_healed", 16u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onHealOrBlockChanged", 20u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_block_changed", 23u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onHealOrBlockChanged", 20u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BionicArmor::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BionicArmor::fn_onHealOrBlockChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        this->f_blockHealthAcc = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_blockHealthAcc, lv_amount));
        gd::GdVal lv_numProccs = gd::gd_coerce_int(gd::gd_div(gd_ctx, this->f_blockHealthAcc, this->f_healthThreshold));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numProccs, gd::GdVal::from_int(0LL))))) {
            this->f_blockHealthAcc = gd::gd_coerce_int(gd::gd_sub(this->f_blockHealthAcc, gd::gd_mul(lv_numProccs, this->f_healthThreshold)));
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_maxStamina, lv_numProccs)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxStaminaTemporary_318, _ca, 1); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BionicArmor::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getCurrentStamina_1246, nullptr, 0), this->f_staminaThreshold)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_block2}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {this->f_staminaUsed}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_118, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_empower}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_219, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BionicArmor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_staminaRegenMalus = gd::gd_div(gd_ctx, gd::gd_neg(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "staminaregen", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })()), gd::GdVal::from_float(100.0));
    this->f_healthThreshold = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healtht", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_maxStamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxstamina", 10u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_staminaThreshold = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "staminat1", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_staminaUsed = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "staminat2", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_empower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_block2 = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "block", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__BionicArmor(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__BionicArmor>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BionicArmor = {CLS_Gd__gd_core_items__Exclusive__BionicArmor, "BionicArmor", "res://gd_core_items/Exclusive/BionicArmor.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__BionicArmor, &Gd__gd_core_items__Exclusive__BionicArmor::get_static_prop_fn, &Gd__gd_core_items__Exclusive__BionicArmor::call_static_fn};

void Gd__gd_core_items__Exclusive__Broccotree::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Food::init_fields(gd_ctx);
    this->f_staminaPerRegen = gd::GdVal::from_float(0.0);
    this->f_luck = gd::GdVal::null();
    this->f_luckNeeded = gd::GdVal::null();
    this->f_regen = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Broccotree::meta() const { return &META_Gd__gd_core_items__Exclusive__Broccotree; }
gd::GdVal Gd__gd_core_items__Exclusive__Broccotree::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Broccotree::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Broccotree::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_staminaPerRegen_2007: out = this->f_staminaPerRegen; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_luckNeeded_1779: out = this->f_luckNeeded; return true;
        case SYM_GEN_regen_1904: out = this->f_regen; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Broccotree::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_staminaPerRegen_2007: this->f_staminaPerRegen = gd::gd_coerce_float(val); return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_luckNeeded_1779: this->f_luckNeeded = val; return true;
        case SYM_GEN_regen_1904: this->f_regen = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Broccotree::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onRegenChanged_1796: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Broccotree::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onRegenChanged_1796: out = fn_onRegenChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Broccotree::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Broccotree::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getLucky_1221, nullptr, 0), this->f_luckNeeded)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Broccotree::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_baseStaminaRegen = gd::get_prop(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_baseStaminaRegen_1057);
    this->f_staminaPerRegen = gd::gd_coerce_float(gd::gd_div(gd_ctx, gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), lv_baseStaminaRegen), gd::GdVal::from_float(100.0)));
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_regeneration_changed", 30u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onRegenChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Broccotree::fn_onRegenChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, this->f_staminaPerRegen)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_giveStaminaRegeneration_1254, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Broccotree::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_luckNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luckt", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Broccotree(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Broccotree>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Broccotree = {CLS_Gd__gd_core_items__Exclusive__Broccotree, "Broccotree", "res://gd_core_items/Exclusive/Broccotree.gd", &META_Gd__gd_core_items__Food, true, _alloc_Gd__gd_core_items__Exclusive__Broccotree, &Gd__gd_core_items__Exclusive__Broccotree::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Broccotree::call_static_fn};

void Gd__gd_core_items__Exclusive__Chess__BlackBishop::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__Chess__ChessPiece::init_fields(gd_ctx);
    this->f_debuffs = gd::GdVal::null();
    this->f_healReduction = gd::GdVal::null();
    this->f_maxHealthReduction = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Chess__BlackBishop::meta() const { return &META_Gd__gd_core_items__Exclusive__Chess__BlackBishop; }
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackBishop::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackBishop::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Chess__BlackBishop::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_debuffs_2055: out = this->f_debuffs; return true;
        case SYM_GEN_healReduction_2056: out = this->f_healReduction; return true;
        case SYM_GEN_maxHealthReduction_2057: out = this->f_maxHealthReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackBishop::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_debuffs_2055: this->f_debuffs = val; return true;
        case SYM_GEN_healReduction_2056: this->f_healReduction = val; return true;
        case SYM_GEN_maxHealthReduction_2057: this->f_maxHealthReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackBishop::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2050: return true;
        case SYM_GEN_doEliminatedEffect_2052: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackBishop::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2050: out = fn_doCapturingEffect(args, argc); return true;
        case SYM_GEN_doEliminatedEffect_2052: out = fn_doEliminatedEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackBishop::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackBishop::fn_doCapturingEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__eliminatedPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {this->f_debuffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictRandomDebuffs_359, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackBishop::fn_doEliminatedEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__capturingPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_healReduction}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_reduceHealingEfficiency_1167, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_maxHealthReduction}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_changeMaxHealthGain_1261, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackBishop::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_debuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "debuffs", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_healReduction = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healreduction", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_maxHealthReduction = gd::gd_div(gd_ctx, gd::gd_neg(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healthreduction", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })()), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Chess__BlackBishop(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Chess__BlackBishop>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Chess__BlackBishop = {CLS_Gd__gd_core_items__Exclusive__Chess__BlackBishop, "BlackBishop", "res://gd_core_items/Exclusive/Chess/BlackBishop.gd", &META_Gd__gd_core_items__Exclusive__Chess__ChessPiece, true, _alloc_Gd__gd_core_items__Exclusive__Chess__BlackBishop, &Gd__gd_core_items__Exclusive__Chess__BlackBishop::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Chess__BlackBishop::call_static_fn};

void Gd__gd_core_items__Exclusive__ChromeCube::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__Cube::init_fields(gd_ctx);
    this->f_hasActivated = gd::GdVal::from_bool(false);
    this->f_healthThreshold = gd::GdVal::null();
    this->f_healReduction = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ChromeCube::meta() const { return &META_Gd__gd_core_items__Exclusive__ChromeCube; }
gd::GdVal Gd__gd_core_items__Exclusive__ChromeCube::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__Cube::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ChromeCube::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ChromeCube::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_hasActivated_1811: out = this->f_hasActivated; return true;
        case SYM_GEN_healthThreshold_1759: out = this->f_healthThreshold; return true;
        case SYM_GEN_healReduction_2056: out = this->f_healReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Cube::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ChromeCube::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_hasActivated_1811: this->f_hasActivated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_healthThreshold_1759: this->f_healthThreshold = val; return true;
        case SYM_GEN_healReduction_2056: this->f_healReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Cube::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ChromeCube::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onDamaged_1760: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Cube::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ChromeCube::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDamaged_1760: out = fn_onDamaged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Cube::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ChromeCube::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__Cube::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ChromeCube::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_97, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ChromeCube::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    this->f_affectedItem = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getFirstAffectedItem_430, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_damaged", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDamaged", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ChromeCube::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(this->f_hasActivated)) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_relHealth = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_getRelativeHealth_304, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_relHealth, this->f_healthThreshold)))) {
        this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(this->f_affectedItem, gd::GdVal::null())))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_advanceAffectedItem_1987, nullptr, 0);
        }
        (void)([&]() { gd::GdVal _ca[] = {this->f_healReduction}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_reduceHealingEfficiency_1167, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_383, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ChromeCube::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Cube::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_healthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healtht", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    this->f_healReduction = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healreduction", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ChromeCube(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ChromeCube>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ChromeCube = {CLS_Gd__gd_core_items__Exclusive__ChromeCube, "ChromeCube", "res://gd_core_items/Exclusive/ChromeCube.gd", &META_Gd__gd_core_items__Exclusive__Cube, true, _alloc_Gd__gd_core_items__Exclusive__ChromeCube, &Gd__gd_core_items__Exclusive__ChromeCube::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ChromeCube::call_static_fn};

void Gd__gd_core_items__Exclusive__DeathLotus::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_mana = gd::GdVal::null();
    this->f_buffs = gd::GdVal::null();
    this->f_darkSpeed = gd::GdVal::null();
    this->f_luckNeeded = gd::GdVal::null();
    this->f_stamina = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__DeathLotus::meta() const { return &META_Gd__gd_core_items__Exclusive__DeathLotus; }
gd::GdVal Gd__gd_core_items__Exclusive__DeathLotus::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__DeathLotus::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__DeathLotus::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_mana_1833: out = this->f_mana; return true;
        case SYM_GEN_buffs_1048: out = this->f_buffs; return true;
        case SYM_GEN_darkSpeed_2103: out = this->f_darkSpeed; return true;
        case SYM_GEN_luckNeeded_1779: out = this->f_luckNeeded; return true;
        case SYM_GEN_stamina_2060: out = this->f_stamina; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DeathLotus::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_mana_1833: this->f_mana = val; return true;
        case SYM_GEN_buffs_1048: this->f_buffs = val; return true;
        case SYM_GEN_darkSpeed_2103: this->f_darkSpeed = val; return true;
        case SYM_GEN_luckNeeded_1779: this->f_luckNeeded = val; return true;
        case SYM_GEN_stamina_2060: this->f_stamina = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DeathLotus::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DeathLotus::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__DeathLotus::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__DeathLotus::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Dark_2602)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DeathLotus::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0), this->f_darkSpeed)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DeathLotus::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_mana}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeRandomBuffs_374, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getLucky_1221, nullptr, 0), this->f_luckNeeded)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_luckNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useLucky_352, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_stamina, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_320, _ca, 2); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DeathLotus::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_buffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_darkSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_luckNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luckt", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_stamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__DeathLotus(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__DeathLotus>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DeathLotus = {CLS_Gd__gd_core_items__Exclusive__DeathLotus, "DeathLotus", "res://gd_core_items/Exclusive/DeathLotus.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__DeathLotus, &Gd__gd_core_items__Exclusive__DeathLotus::get_static_prop_fn, &Gd__gd_core_items__Exclusive__DeathLotus::call_static_fn};

void Gd__gd_core_items__Exclusive__DualWielding::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_active = gd::GdVal::from_bool(false);
    this->f_weaponSpeed = gd::GdVal::null();
    this->f_weaponStamina = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__DualWielding::meta() const { return &META_Gd__gd_core_items__Exclusive__DualWielding; }
gd::GdVal Gd__gd_core_items__Exclusive__DualWielding::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__DualWielding::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__DualWielding::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_active_2129: out = this->f_active; return true;
        case SYM_GEN_weaponSpeed_2058: out = this->f_weaponSpeed; return true;
        case SYM_GEN_weaponStamina_2130: out = this->f_weaponStamina; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DualWielding::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_active_2129: this->f_active = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_weaponSpeed_2058: this->f_weaponSpeed = val; return true;
        case SYM_GEN_weaponStamina_2130: this->f_weaponStamina = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DualWielding::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onItemAdded_439: return true;
        case SYM_GEN_onItemRemoved_440: return true;
        case SYM_GEN_onRemoveFromInventory_420: return true;
        case SYM_GEN_canAffect_global_1919: return true;
        case SYM_GEN_checkItems_2128: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DualWielding::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onItemAdded_439: out = fn_onItemAdded(args, argc); return true;
        case SYM_GEN_onItemRemoved_440: out = fn_onItemRemoved(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_420: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_canAffect_global_1919: out = fn_canAffect_global(args, argc); return true;
        case SYM_GEN_checkItems_2128: out = fn_checkItems(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__DualWielding::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__DualWielding::fn_onItemAdded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onItemAdded_439, _ca, 1, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkItems_2128, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DualWielding::fn_onItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onItemRemoved_440, _ca, 1, _out); return _out; })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkItems_2128, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DualWielding::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_active = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DualWielding::fn_canAffect_global(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isWeapon_84, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, lv_item, SYM_GEN_getBaseStaminaCost_113, nullptr, 0), gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DualWielding::fn_checkItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numWeapons = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t687 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1512, nullptr, 0));
        gd::GdArr* _t688 = (_t687.kind == gd::GdVal::Kind::Arr) ? _t687.arr : nullptr;
        uint32_t _len__t689 = _t688 ? _t688->len : 0u;
        for (uint32_t _t689 = 0; _t689 < _len__t689; ++_t689) {
            gd::GdVal lv_item = _t688->data[_t689];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_global_1919, _ca, 1); })())) {
                lv_numWeapons = gd::gd_add(gd_ctx, lv_numWeapons, gd::GdVal::from_int(1LL));
            }
        }
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_numWeapons, gd::GdVal::from_int(2LL))))) {
        this->f_active = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
    }
    else {
        this->f_active = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DualWielding::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_active)) {
        {
            gd::GdVal _t690 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1512, nullptr, 0));
            gd::GdArr* _t691 = (_t690.kind == gd::GdVal::Kind::Arr) ? _t690.arr : nullptr;
            uint32_t _len__t692 = _t691 ? _t691->len : 0u;
            for (uint32_t _t692 = 0; _t692 < _len__t692; ++_t692) {
                gd::GdVal lv_item = _t691->data[_t692];
                if (gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Weapon_2666)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })()) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, lv_item, SYM_GEN_getBaseStaminaCost_113, nullptr, 0), gd::GdVal::from_int(0LL))))) : gd::GdVal::from_bool(false)))) {
                    (void)([&]() { gd::GdVal _ca[] = {this->f_weaponSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_275, _ca, 1); })();
                    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_weaponStamina)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeStaminaFactor_307, _ca, 1); })();
                }
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DualWielding::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_weaponSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_weaponStamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__DualWielding(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__DualWielding>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DualWielding = {CLS_Gd__gd_core_items__Exclusive__DualWielding, "DualWielding", "res://gd_core_items/Exclusive/DualWielding.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__DualWielding, &Gd__gd_core_items__Exclusive__DualWielding::get_static_prop_fn, &Gd__gd_core_items__Exclusive__DualWielding::call_static_fn};

void Gd__gd_core_items__Exclusive__ExtraBags::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_freeSlotSpeed = gd::GdVal::null();
    this->f_salesChance = gd::GdVal::null();
    this->f_bagWeight = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ExtraBags::meta() const { return &META_Gd__gd_core_items__Exclusive__ExtraBags; }
gd::GdVal Gd__gd_core_items__Exclusive__ExtraBags::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ExtraBags::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ExtraBags::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_freeSlotSpeed_2159: out = this->f_freeSlotSpeed; return true;
        case SYM_GEN_salesChance_1997: out = this->f_salesChance; return true;
        case SYM_GEN_bagWeight_2160: out = this->f_bagWeight; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ExtraBags::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_freeSlotSpeed_2159: this->f_freeSlotSpeed = val; return true;
        case SYM_GEN_salesChance_1997: this->f_salesChance = val; return true;
        case SYM_GEN_bagWeight_2160: this->f_bagWeight = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ExtraBags::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_affectsEmpty_257: return true;
        case SYM_GEN_canAffect_secondary_289: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onSaleRoll_1998: return true;
        case SYM_GEN_onItemRoll_1923: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ExtraBags::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_affectsEmpty_257: out = fn_affectsEmpty(args, argc); return true;
        case SYM_GEN_canAffect_secondary_289: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onSaleRoll_1998: out = fn_onSaleRoll(args, argc); return true;
        case SYM_GEN_onItemRoll_1923: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ExtraBags::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ExtraBags::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_97, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ExtraBags::fn_affectsEmpty(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(gd::gd_eq(lv_color, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Secondary_2583)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ExtraBags::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ExtraBags::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_freeSlotSpeed_total = gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Secondary_2583)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumEmptyAffectedCells_428, _ca, 1); })(), this->f_freeSlotSpeed);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_freeSlotSpeed_total, gd::GdVal::from_int(0LL))))) {
        {
            gd::GdVal _t693 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
            gd::GdArr* _t694 = (_t693.kind == gd::GdVal::Kind::Arr) ? _t693.arr : nullptr;
            uint32_t _len__t695 = _t694 ? _t694->len : 0u;
            for (uint32_t _t695 = 0; _t695 < _len__t695; ++_t695) {
                gd::GdVal lv_item = _t694->data[_t695];
                (void)([&]() { gd::GdVal _ca[] = {lv_freeSlotSpeed_total}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_275, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ExtraBags::fn_onSaleRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ExtraBags::fn_onItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ExtraBags::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_freeSlotSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_salesChance = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "sales", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_bagWeight = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "bagweight", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ExtraBags(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ExtraBags>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ExtraBags = {CLS_Gd__gd_core_items__Exclusive__ExtraBags, "ExtraBags", "res://gd_core_items/Exclusive/ExtraBags.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__ExtraBags, &Gd__gd_core_items__Exclusive__ExtraBags::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ExtraBags::call_static_fn};

void Gd__gd_core_items__Exclusive__Frostbite::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_gaveVampirism = gd::GdVal::from_bool(false);
    this->f_damagePerCold = gd::GdVal::null();
    this->f_coldNeeded = gd::GdVal::null();
    this->f_vampirism = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Frostbite::meta() const { return &META_Gd__gd_core_items__Exclusive__Frostbite; }
gd::GdVal Gd__gd_core_items__Exclusive__Frostbite::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Frostbite::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Frostbite::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_gaveVampirism_2183: out = this->f_gaveVampirism; return true;
        case SYM_GEN_damagePerCold_2184: out = this->f_damagePerCold; return true;
        case SYM_GEN_coldNeeded_2185: out = this->f_coldNeeded; return true;
        case SYM_GEN_vampirism_940: out = this->f_vampirism; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Frostbite::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_gaveVampirism_2183: this->f_gaveVampirism = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_damagePerCold_2184: this->f_damagePerCold = val; return true;
        case SYM_GEN_coldNeeded_2185: this->f_coldNeeded = val; return true;
        case SYM_GEN_vampirism_940: this->f_vampirism = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Frostbite::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onVampirismChanged_943: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_onOpponentColdChanged_2108: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Frostbite::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onVampirismChanged_943: out = fn_onVampirismChanged(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onOpponentColdChanged_2108: out = fn_onOpponentColdChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Frostbite::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Frostbite::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_gaveVampirism = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_vampirism_changed", 27u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onVampirismChanged", 18u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_cold_changed", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onOpponentColdChanged", 21u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Frostbite::fn_onVampirismChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_amount}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_164, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Frostbite::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_353, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Frostbite::fn_onOpponentColdChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_damagePerCold, lv_amount)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_164, _ca, 1); })();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_gaveVampirism))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_getCold_1238, nullptr, 0), this->f_coldNeeded)))) : gd::GdVal::from_bool(false)))) {
        this->f_gaveVampirism = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        (void)([&]() { gd::GdVal _ca[] = {this->f_vampirism, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_212, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Frostbite::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_damagePerCold = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0);
    this->f_coldNeeded = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0));
    this->f_vampirism = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Frostbite(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Frostbite>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Frostbite = {CLS_Gd__gd_core_items__Exclusive__Frostbite, "Frostbite", "res://gd_core_items/Exclusive/Frostbite.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__Frostbite, &Gd__gd_core_items__Exclusive__Frostbite::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Frostbite::call_static_fn};

void Gd__gd_core_items__Exclusive__HeartoftheCards::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_regen = gd::GdVal::null();
    this->f_mana = gd::GdVal::null();
    this->f_chainPosition = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__HeartoftheCards::meta() const { return &META_Gd__gd_core_items__Exclusive__HeartoftheCards; }
gd::GdVal Gd__gd_core_items__Exclusive__HeartoftheCards::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__HeartoftheCards::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__HeartoftheCards::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_regen_1904: out = this->f_regen; return true;
        case SYM_GEN_mana_1833: out = this->f_mana; return true;
        case SYM_GEN_chainPosition_882: out = this->f_chainPosition; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__HeartoftheCards::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_regen_1904: this->f_regen = val; return true;
        case SYM_GEN_mana_1833: this->f_mana = val; return true;
        case SYM_GEN_chainPosition_882: this->f_chainPosition = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__HeartoftheCards::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onCardRevealed_2206: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__HeartoftheCards::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCardRevealed_2206: out = fn_onCardRevealed(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__HeartoftheCards::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__HeartoftheCards::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t696 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1512, nullptr, 0));
        gd::GdArr* _t697 = (_t696.kind == gd::GdVal::Kind::Arr) ? _t696.arr : nullptr;
        uint32_t _len__t698 = _t697 ? _t697->len : 0u;
        for (uint32_t _t698 = 0; _t698 < _len__t698; ++_t698) {
            gd::GdVal lv_item = _t697->data[_t698];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Card_2672)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "activated", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onCardRevealed", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeartoftheCards::fn_onCardRevealed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_card = gd::call_method(gd_ctx, lv_event, SYM_GEN_getOrigin_1489, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {this->f_regen, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 2); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, lv_card, SYM_GEN_chainPosition_882), gd::GdVal::from_int(1LL)), this->f_chainPosition)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_mana, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 2); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HeartoftheCards::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_chainPosition = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "pos", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__HeartoftheCards(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__HeartoftheCards>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__HeartoftheCards = {CLS_Gd__gd_core_items__Exclusive__HeartoftheCards, "HeartoftheCards", "res://gd_core_items/Exclusive/HeartoftheCards.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__HeartoftheCards, &Gd__gd_core_items__Exclusive__HeartoftheCards::get_static_prop_fn, &Gd__gd_core_items__Exclusive__HeartoftheCards::call_static_fn};

void Gd__gd_core_items__Exclusive__JustStats::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_staminaRegen = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__JustStats::meta() const { return &META_Gd__gd_core_items__Exclusive__JustStats; }
gd::GdVal Gd__gd_core_items__Exclusive__JustStats::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__JustStats::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__JustStats::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_staminaRegen_1058: out = this->f_staminaRegen; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__JustStats::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_staminaRegen_1058: this->f_staminaRegen = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__JustStats::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN_getSalesMultiplier_762: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__JustStats::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_getSalesMultiplier_762: out = fn_getSalesMultiplier(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__JustStats::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__JustStats::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_round(gd::gd_mul(gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), gd::GdVal::from_float(100.0)), gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getMaxHealth_1144, nullptr, 0)))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_319, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_staminaRegen}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_giveStaminaRegeneration_1254, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__JustStats::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_856), SYM_GEN_Low_2718);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__JustStats::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getDescription_642, _ca, 1, _out); return _out; })();
    gd::GdVal lv_string = gd::GdVal::null();
    if (gd::gd_truth(lv_wrapInColor)) {
        lv_string = ([&]() { gd::GdVal _ca[] = {([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 1); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "round", 5u)), gd::GdVal::null()); return gd::GdVal::from_dict(d); })()}; return gd::call_method(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "TOOLTIP_Always Offered", 22u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_tr_2719, _ca, 1); })(), SYM_GEN_format_2621, _ca, 1); })();
    }
    else {
        lv_string = ([&]() { gd::GdVal _ca[] = {([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 1); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "round", 5u)), gd::get_index(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_appearRounds_2720), gd::GdVal::from_int(0LL))); return gd::GdVal::from_dict(d); })()}; return gd::call_method(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "TOOLTIP_Always Offered", 22u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_tr_2719, _ca, 1); })(), SYM_GEN_format_2621, _ca, 1); })();
    }
    lv_descr = gd::gd_add(gd_ctx, lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "\n\n", 2u)), lv_string));
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__JustStats::fn_getSalesMultiplier(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_float(0.2);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__JustStats::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_staminaRegen = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__JustStats(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__JustStats>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__JustStats = {CLS_Gd__gd_core_items__Exclusive__JustStats, "JustStats", "res://gd_core_items/Exclusive/JustStats.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__JustStats, &Gd__gd_core_items__Exclusive__JustStats::get_static_prop_fn, &Gd__gd_core_items__Exclusive__JustStats::call_static_fn};

void Gd__gd_core_items__Exclusive__Lootbox::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_itemValue = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Lootbox::meta() const { return &META_Gd__gd_core_items__Exclusive__Lootbox; }
gd::GdVal Gd__gd_core_items__Exclusive__Lootbox::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_OFFSET_2258: return gd::GdVal::from_float(50.0);
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Lootbox::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Lootbox::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_itemValue_2259: out = this->f_itemValue; return true;
        case SYM_GEN_OFFSET_2258: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Lootbox::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_itemValue_2259: this->f_itemValue = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Lootbox::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onDropped_1925: return true;
        case SYM_GEN_generateItems_2260: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Lootbox::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onDropped_1925: out = fn_onDropped(args, argc); return true;
        case SYM_GEN_generateItems_2260: out = fn_generateItems(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Lootbox::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Lootbox::fn_onDropped(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_dropRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_dropRes}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core_items__Exclusive__Lootbox::call_static_fn(gd_ctx, SYM_GEN_wasAddedToInventory_659, _ca, 1, _out); return _out; })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_dropRes, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__Lootbox::get_static_const_or_enum(gd_ctx, SYM_GEN_DropResult_865), SYM_GEN_AddedToStorageBox_2599)))))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_prepareReplacement_448, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "generateItems", 13u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_dropRes}))}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_defer_1422, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Lootbox::fn_generateItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_dropResult = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Lootbox::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_itemValue = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gold", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dropped", 7u)), gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDropped", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_connect, _ca, 3); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Lootbox(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Lootbox>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Lootbox = {CLS_Gd__gd_core_items__Exclusive__Lootbox, "Lootbox", "res://gd_core_items/Exclusive/Lootbox.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Lootbox, &Gd__gd_core_items__Exclusive__Lootbox::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Lootbox::call_static_fn};

void Gd__gd_core_items__Exclusive__MercuryElemental::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_staminaRegen = gd::GdVal::from_float(0.0);
    this->f_staminaUsed = gd::GdVal::from_float(0.0);
    this->f_poison = gd::GdVal::null();
    this->f_selfPoison = gd::GdVal::null();
    this->f_staminaThreshold = gd::GdVal::null();
    this->f_distortion = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__MercuryElemental::meta() const { return &META_Gd__gd_core_items__Exclusive__MercuryElemental; }
gd::GdVal Gd__gd_core_items__Exclusive__MercuryElemental::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__MercuryElemental::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__MercuryElemental::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_staminaRegen_1058: out = this->f_staminaRegen; return true;
        case SYM_GEN_staminaUsed_1981: out = this->f_staminaUsed; return true;
        case SYM_GEN_poison_1867: out = this->f_poison; return true;
        case SYM_GEN_selfPoison_2308: out = this->f_selfPoison; return true;
        case SYM_GEN_staminaThreshold_1980: out = this->f_staminaThreshold; return true;
        case SYM_GEN_distortion_2107: out = this->f_distortion; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MercuryElemental::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_staminaRegen_1058: this->f_staminaRegen = gd::gd_coerce_float(val); return true;
        case SYM_GEN_staminaUsed_1981: this->f_staminaUsed = gd::gd_coerce_float(val); return true;
        case SYM_GEN_poison_1867: this->f_poison = val; return true;
        case SYM_GEN_selfPoison_2308: this->f_selfPoison = val; return true;
        case SYM_GEN_staminaThreshold_1980: this->f_staminaThreshold = val; return true;
        case SYM_GEN_distortion_2107: this->f_distortion = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MercuryElemental::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_isAffectingDistinct_256: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onOpponentAttacked_2309: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onStaminaUsed_2310: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MercuryElemental::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_isAffectingDistinct_256: out = fn_isAffectingDistinct(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onOpponentAttacked_2309: out = fn_onOpponentAttacked(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onStaminaUsed_2310: out = fn_onStaminaUsed(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__MercuryElemental::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__MercuryElemental::fn_isAffectingDistinct(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581));
    return gd::GdVal::from_bool(gd::gd_eq(lv_color, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MercuryElemental::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), SYM_GEN_isMeleeWeapon_1626, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MercuryElemental::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_attacked", 18u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onOpponentAttacked", 18u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_used_stamina", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onStaminaUsed", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    this->f_staminaRegen = gd::gd_coerce_float(gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumDistinctAffectedItems_432, nullptr, 0)));
    this->f_staminaUsed = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MercuryElemental::fn_onOpponentAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_triggerOnAttacked_1439, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_206, nullptr, 0), gd::GdVal::from_float(100.0)), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MercuryElemental::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_staminaRegen}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_320, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MercuryElemental::fn_onStaminaUsed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_staminaUsed = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_staminaUsed, lv_amount));
    gd::GdVal lv_ticks = gd::gd_floor(gd::gd_div(gd_ctx, this->f_staminaUsed, this->f_staminaThreshold));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_ticks, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_ticks, this->f_poison)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_213, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_ticks, this->f_selfPoison)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_selfInflictPoison_214, _ca, 1); })();
        this->f_staminaUsed = gd::gd_coerce_float(gd::gd_sub(this->f_staminaUsed, gd::gd_mul(lv_ticks, this->f_staminaThreshold)));
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MercuryElemental::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_poison = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "poison", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_selfPoison = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "poison2", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_staminaThreshold = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "staminat", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_GridStorage_2610))))) {
    }
    else {
    }
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__MercuryElemental(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__MercuryElemental>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MercuryElemental = {CLS_Gd__gd_core_items__Exclusive__MercuryElemental, "MercuryElemental", "res://gd_core_items/Exclusive/MercuryElemental.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__MercuryElemental, &Gd__gd_core_items__Exclusive__MercuryElemental::get_static_prop_fn, &Gd__gd_core_items__Exclusive__MercuryElemental::call_static_fn};

void Gd__gd_core_items__Exclusive__ParadiseBirb::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_numActivations = gd::GdVal::from_int(0);
    this->f_speedBonus = gd::GdVal::null();
    this->f_maxActivations = gd::GdVal::null();
    this->f_bonusHeal = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ParadiseBirb::meta() const { return &META_Gd__gd_core_items__Exclusive__ParadiseBirb; }
gd::GdVal Gd__gd_core_items__Exclusive__ParadiseBirb::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ParadiseBirb::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ParadiseBirb::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_numActivations_1809: out = this->f_numActivations; return true;
        case SYM_GEN_speedBonus_1782: out = this->f_speedBonus; return true;
        case SYM_GEN_maxActivations_1810: out = this->f_maxActivations; return true;
        case SYM_GEN_bonusHeal_2324: out = this->f_bonusHeal; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ParadiseBirb::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numActivations_1809: this->f_numActivations = gd::gd_coerce_int(val); return true;
        case SYM_GEN_speedBonus_1782: this->f_speedBonus = val; return true;
        case SYM_GEN_maxActivations_1810: this->f_maxActivations = val; return true;
        case SYM_GEN_bonusHeal_2324: this->f_bonusHeal = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ParadiseBirb::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN_playDropSound_151: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ParadiseBirb::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_151: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ParadiseBirb::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ParadiseBirb::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_97, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_gainsBuffs_298, nullptr, 0))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canHealOrLifesteal_294, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ParadiseBirb::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_numActivations = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ParadiseBirb::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_numActivations, this->f_maxActivations)))) {
        {
            gd::GdVal _t699 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
            gd::GdArr* _t700 = (_t699.kind == gd::GdVal::Kind::Arr) ? _t699.arr : nullptr;
            uint32_t _len__t701 = _t700 ? _t700->len : 0u;
            for (uint32_t _t701 = 0; _t701 < _len__t701; ++_t701) {
                gd::GdVal lv_item = _t700->data[_t701];
                (void)([&]() { gd::GdVal _ca[] = {this->f_speedBonus}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_275, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_allBuffs_199, _ca, 1); })();
                (void)([&]() { gd::GdVal _ca[] = {this->f_bonusHeal}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeHealAmp_306, _ca, 1); })();
            }
        }
        this->f_numActivations = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_numActivations, gd::GdVal::from_int(1LL)));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_numActivations, this->f_maxActivations)))) {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_147, nullptr, 0);
        }
        else {
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ParadiseBirb::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_pitch = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.8), gd::GdVal::from_float(1.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ParadiseBirb::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    gd::GdVal lv_pitch = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.8), gd::GdVal::from_float(1.0)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ParadiseBirb::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_speedBonus = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_maxActivations = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "max", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_bonusHeal = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healamp", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ParadiseBirb(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ParadiseBirb>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ParadiseBirb = {CLS_Gd__gd_core_items__Exclusive__ParadiseBirb, "ParadiseBirb", "res://gd_core_items/Exclusive/ParadiseBirb.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__ParadiseBirb, &Gd__gd_core_items__Exclusive__ParadiseBirb::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ParadiseBirb::call_static_fn};

void Gd__gd_core_items__Exclusive__PoweroftheMoon::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_boosted = gd::GdVal::from_int(0LL);
    this->f_moonArmorDescriptor = gd::GdVal::null();
    this->f_moonShieldDescriptor = gd::GdVal::null();
    this->f_manaOrbDescriptor = gd::GdVal::null();
    this->f_timeAdvance = gd::GdVal::null();
    this->f_blind = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__PoweroftheMoon::meta() const { return &META_Gd__gd_core_items__Exclusive__PoweroftheMoon; }
gd::GdVal Gd__gd_core_items__Exclusive__PoweroftheMoon::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__PoweroftheMoon::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__PoweroftheMoon::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_boosted_2101: out = this->f_boosted; return true;
        case SYM_GEN_moonArmorDescriptor_2344: out = this->f_moonArmorDescriptor; return true;
        case SYM_GEN_moonShieldDescriptor_2345: out = this->f_moonShieldDescriptor; return true;
        case SYM_GEN_manaOrbDescriptor_2298: out = this->f_manaOrbDescriptor; return true;
        case SYM_GEN_timeAdvance_2346: out = this->f_timeAdvance; return true;
        case SYM_GEN_blind_1816: out = this->f_blind; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PoweroftheMoon::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_boosted_2101: this->f_boosted = val; return true;
        case SYM_GEN_moonArmorDescriptor_2344: this->f_moonArmorDescriptor = val; return true;
        case SYM_GEN_moonShieldDescriptor_2345: this->f_moonShieldDescriptor = val; return true;
        case SYM_GEN_manaOrbDescriptor_2298: this->f_manaOrbDescriptor = val; return true;
        case SYM_GEN_timeAdvance_2346: this->f_timeAdvance = val; return true;
        case SYM_GEN_blind_1816: this->f_blind = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PoweroftheMoon::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_getData_638: return true;
        case SYM_GEN_setData_639: return true;
        case SYM_GEN_onBought_457: return true;
        case SYM_GEN_onPostCombatStart_131: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onFatigueStarted_1874: return true;
        case SYM_GEN_onMoonArmorActivated_2347: return true;
        case SYM_GEN_onMoonShiedActivated_2348: return true;
        case SYM_GEN_onItemRoll_1923: return true;
        case SYM_GEN_onItemRolled_1924: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PoweroftheMoon::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_getData_638: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_639: out = fn_setData(args, argc); return true;
        case SYM_GEN_onBought_457: out = fn_onBought(args, argc); return true;
        case SYM_GEN_onPostCombatStart_131: out = fn_onPostCombatStart(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onFatigueStarted_1874: out = fn_onFatigueStarted(args, argc); return true;
        case SYM_GEN_onMoonArmorActivated_2347: out = fn_onMoonArmorActivated(args, argc); return true;
        case SYM_GEN_onMoonShiedActivated_2348: out = fn_onMoonShiedActivated(args, argc); return true;
        case SYM_GEN_onItemRoll_1923: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_onItemRolled_1924: out = fn_onItemRolled(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__PoweroftheMoon::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__PoweroftheMoon::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_moonArmorDescriptor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isA_247, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_moonShieldDescriptor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isA_247, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoweroftheMoon::fn_getData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_boosted;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoweroftheMoon::fn_setData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_data = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_data, gd::GdVal::null())))) {
        this->f_boosted = lv_data;
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoweroftheMoon::fn_onBought(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_boosted = gd::GdVal::from_int(1LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoweroftheMoon::fn_onPostCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoweroftheMoon::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_1392), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "fatigue_start", 13u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onFatigueStarted", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    {
        gd::GdVal _t702 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t703 = (_t702.kind == gd::GdVal::Kind::Arr) ? _t702.arr : nullptr;
        uint32_t _len__t704 = _t703 ? _t703->len : 0u;
        for (uint32_t _t704 = 0; _t704 < _len__t704; ++_t704) {
            gd::GdVal lv_item = _t703->data[_t704];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_moonArmorDescriptor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isA_247, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "activated", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onMoonArmorActivated", 20u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
            }
            else {
                (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "activated", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onMoonShiedActivated", 20u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoweroftheMoon::fn_onFatigueStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_bonusHealth = gd::gd_mul(gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), gd::GdVal::from_float(100.0)), gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getMaxHealth_1144, nullptr, 0));
    (void)([&]() { gd::GdVal _ca[] = {lv_bonusHealth}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_319, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoweroftheMoon::fn_onMoonArmorActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_blind, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_215, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoweroftheMoon::fn_onMoonShiedActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveReflectStacks_202, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoweroftheMoon::fn_onItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoweroftheMoon::fn_onItemRolled(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_descr, this->f_manaOrbDescriptor)))) {
        this->f_boosted = gd::gd_sub(this->f_boosted, gd::GdVal::from_int(1LL));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PoweroftheMoon::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_moonArmorDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Moon Armor", 10u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })();
    this->f_moonShieldDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Moon Shield", 11u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })();
    this->f_manaOrbDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Mana Orb", 8u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })();
    this->f_timeAdvance = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "time", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_blind = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blind", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PoweroftheMoon(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__PoweroftheMoon>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PoweroftheMoon = {CLS_Gd__gd_core_items__Exclusive__PoweroftheMoon, "PoweroftheMoon", "res://gd_core_items/Exclusive/PoweroftheMoon.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__PoweroftheMoon, &Gd__gd_core_items__Exclusive__PoweroftheMoon::get_static_prop_fn, &Gd__gd_core_items__Exclusive__PoweroftheMoon::call_static_fn};

void Gd__gd_core_items__Exclusive__RainbowOrb::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_buffs = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__RainbowOrb::meta() const { return &META_Gd__gd_core_items__Exclusive__RainbowOrb; }
gd::GdVal Gd__gd_core_items__Exclusive__RainbowOrb::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__RainbowOrb::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__RainbowOrb::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_buffs_1048: out = this->f_buffs; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__RainbowOrb::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffs_1048: this->f_buffs = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__RainbowOrb::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__RainbowOrb::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__RainbowOrb::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowOrb::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth((gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Vampiric_2598)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Magic_2721)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Holy_2593)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Dark_2602)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowOrb::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_typesDict = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countTypes_497, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_index(gd_ctx, lv_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Vampiric_2598)), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::get_index(gd_ctx, lv_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Vampiric_2598)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "vampirism", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_212, _ca, 1); })();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_index(gd_ctx, lv_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Magic_2721)), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::get_index(gd_ctx, lv_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Magic_2721)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 1); })();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_index(gd_ctx, lv_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Holy_2593)), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::gd_mul(gd::get_index(gd_ctx, lv_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Holy_2593)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healamp", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })()), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_addHealingEfficiency_1166, _ca, 1); })();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_index(gd_ctx, lv_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Dark_2602)), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::get_index(gd_ctx, lv_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Dark_2602)), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "debuffs", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictRandomDebuffs_359, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowOrb::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveAllBuffs_372, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowOrb::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getDescription_642, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_placed)))) {
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$n_magic", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$n_vampiric", 11u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$n_holy", 7u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$n_dark", 7u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "", 0u))}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        return lv_descr;
    }
    gd::GdVal lv_typesDict = ([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countTypes_497, _ca, 1); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "n_magic", 7u)), gd::get_index(gd_ctx, lv_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Magic_2721))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_454, _ca, 3); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "n_vampiric", 10u)), gd::get_index(gd_ctx, lv_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Vampiric_2598))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_454, _ca, 3); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "n_holy", 6u)), gd::get_index(gd_ctx, lv_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Holy_2593))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_454, _ca, 3); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "n_dark", 6u)), gd::get_index(gd_ctx, lv_typesDict, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Dark_2602))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertCounter_454, _ca, 3); })();
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowOrb::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_buffs = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__RainbowOrb(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__RainbowOrb>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__RainbowOrb = {CLS_Gd__gd_core_items__Exclusive__RainbowOrb, "RainbowOrb", "res://gd_core_items/Exclusive/RainbowOrb.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__RainbowOrb, &Gd__gd_core_items__Exclusive__RainbowOrb::get_static_prop_fn, &Gd__gd_core_items__Exclusive__RainbowOrb::call_static_fn};

void Gd__gd_core_items__Exclusive__ScholarBag::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Bag::init_fields(gd_ctx);
    this->f_mana = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ScholarBag::meta() const { return &META_Gd__gd_core_items__Exclusive__ScholarBag; }
gd::GdVal Gd__gd_core_items__Exclusive__ScholarBag::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Bag::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ScholarBag::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ScholarBag::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_mana_1833: out = this->f_mana; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ScholarBag::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_mana_1833: this->f_mana = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ScholarBag::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canApplyEffect_920: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ScholarBag::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canApplyEffect_920: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ScholarBag::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ScholarBag::fn_canApplyEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_toItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Stack_859), SYM_GEN_Mana_2571)}; return gd::call_method(gd_ctx, lv_toItem, SYM_GEN_gainsStack_88, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ScholarBag::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t705 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_927, nullptr, 0));
        gd::GdArr* _t706 = (_t705.kind == gd::GdVal::Kind::Arr) ? _t705.arr : nullptr;
        uint32_t _len__t707 = _t706 ? _t706->len : 0u;
        for (uint32_t _t707 = 0; _t707 < _len__t707; ++_t707) {
            gd::GdVal lv_item = _t706->data[_t707];
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Mana_2571), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_198, _ca, 2); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Mana_2571), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_174, nullptr, 0)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeProtectionChance_1269, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ScholarBag::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_mana}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ScholarBag::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ScholarBag(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ScholarBag>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ScholarBag = {CLS_Gd__gd_core_items__Exclusive__ScholarBag, "ScholarBag", "res://gd_core_items/Exclusive/ScholarBag.gd", &META_Gd__gd_core_items__Bag, true, _alloc_Gd__gd_core_items__Exclusive__ScholarBag, &Gd__gd_core_items__Exclusive__ScholarBag::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ScholarBag::call_static_fn};

void Gd__gd_core_items__Exclusive__Sloth::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_awakenNow = gd::GdVal::from_bool(false);
    this->f_speed_v = gd::GdVal::null();
    this->f_buffs = gd::GdVal::null();
    this->f_buffsAmulet = gd::GdVal::null();
    this->f_light1 = gd::GdVal::null();
    this->f_light2 = gd::GdVal::null();
    this->f_particles1 = gd::GdVal::null();
    this->f_particles2 = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Sloth::meta() const { return &META_Gd__gd_core_items__Exclusive__Sloth; }
gd::GdVal Gd__gd_core_items__Exclusive__Sloth::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Sloth::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Sloth::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_awakenNow_2404: out = this->f_awakenNow; return true;
        case SYM_GEN_speed_v_2083: out = this->f_speed_v; return true;
        case SYM_GEN_buffs_1048: out = this->f_buffs; return true;
        case SYM_GEN_buffsAmulet_2405: out = this->f_buffsAmulet; return true;
        case SYM_GEN_light1_2406: out = this->f_light1; return true;
        case SYM_GEN_light2_2407: out = this->f_light2; return true;
        case SYM_GEN_particles1_2408: out = this->f_particles1; return true;
        case SYM_GEN_particles2_2409: out = this->f_particles2; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Sloth::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_awakenNow_2404: this->f_awakenNow = val; return true;
        case SYM_GEN_speed_v_2083: this->f_speed_v = val; return true;
        case SYM_GEN_buffs_1048: this->f_buffs = val; return true;
        case SYM_GEN_buffsAmulet_2405: this->f_buffsAmulet = val; return true;
        case SYM_GEN_light1_2406: this->f_light1 = val; return true;
        case SYM_GEN_light2_2407: this->f_light2 = val; return true;
        case SYM_GEN_particles1_2408: this->f_particles1 = val; return true;
        case SYM_GEN_particles2_2409: this->f_particles2 = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Sloth::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_trigger_145: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Sloth::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_trigger_145: out = fn_trigger(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Sloth::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Sloth::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_97, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Sloth::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    {
        gd::GdVal _t708 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t709 = (_t708.kind == gd::GdVal::Kind::Arr) ? _t708.arr : nullptr;
        uint32_t _len__t710 = _t709 ? _t709->len : 0u;
        for (uint32_t _t710 = 0; _t710 < _len__t710; ++_t710) {
            gd::GdVal lv_item = _t709->data[_t710];
            (void)([&]() { gd::GdVal _ca[] = {this->f_speed_v}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_reduceSpeed_276, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Sloth::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_m = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth_base", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })();
    lv_m = gd::gd_add(gd_ctx, lv_m, gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth_item", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })()));
    lv_m = gd::gd_round(gd::gd_mul(gd::gd_div(gd_ctx, lv_m, gd::GdVal::from_float(100.0)), gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getMaxHealth_1144, nullptr, 0)));
    (void)([&]() { gd::GdVal _ca[] = {lv_m}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_319, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Sloth::fn_trigger(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_awakenNow = gd::GdVal::from_bool(true);
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_trigger_145, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Sloth::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_awakenNow)) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_buffs}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveAllBuffs_372, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_stun", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_332, _ca, 1); })();
        this->f_awakenNow = gd::GdVal::from_bool(false);
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_147, nullptr, 0);
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {this->f_buffsAmulet}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveAllBuffs_372, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_stun_amulet", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_332, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Sloth::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Sloth::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_awakened = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_awakened = gd::gd_coerce_bool(lv_awakened);
    if (gd::gd_truth(lv_awakened)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Sloth::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_getDescription_642, _ca, 1, _out); return _out; })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$s[", 3u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "[shake]", 7u))}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "$s]", 3u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "[/shake]", 8u))}; return gd::call_method(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Sloth::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_speed_v = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_buffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_buffsAmulet = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs_amulet", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Sloth(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Sloth>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Sloth = {CLS_Gd__gd_core_items__Exclusive__Sloth, "Sloth", "res://gd_core_items/Exclusive/Sloth.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Sloth, &Gd__gd_core_items__Exclusive__Sloth::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Sloth::call_static_fn};

void Gd__gd_core_items__Exclusive__SpicyBanana::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_staminaUsed = gd::GdVal::from_float(0.0);
    this->f_boostedBananas = gd::GdVal::from_int(0LL);
    this->f_bananaDescriptor = gd::GdVal::null();
    this->f_manananaDescriptor = gd::GdVal::null();
    this->f_heatPerActivation = gd::GdVal::null();
    this->f_staminaForHeal = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SpicyBanana::meta() const { return &META_Gd__gd_core_items__Exclusive__SpicyBanana; }
gd::GdVal Gd__gd_core_items__Exclusive__SpicyBanana::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SpicyBanana::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SpicyBanana::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_staminaUsed_1981: out = this->f_staminaUsed; return true;
        case SYM_GEN_boostedBananas_2436: out = this->f_boostedBananas; return true;
        case SYM_GEN_bananaDescriptor_2437: out = this->f_bananaDescriptor; return true;
        case SYM_GEN_manananaDescriptor_2438: out = this->f_manananaDescriptor; return true;
        case SYM_GEN_heatPerActivation_2439: out = this->f_heatPerActivation; return true;
        case SYM_GEN_staminaForHeal_2440: out = this->f_staminaForHeal; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SpicyBanana::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_staminaUsed_1981: this->f_staminaUsed = gd::gd_coerce_float(val); return true;
        case SYM_GEN_boostedBananas_2436: this->f_boostedBananas = val; return true;
        case SYM_GEN_bananaDescriptor_2437: this->f_bananaDescriptor = val; return true;
        case SYM_GEN_manananaDescriptor_2438: this->f_manananaDescriptor = val; return true;
        case SYM_GEN_heatPerActivation_2439: this->f_heatPerActivation = val; return true;
        case SYM_GEN_staminaForHeal_2440: this->f_staminaForHeal = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SpicyBanana::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onBought_457: return true;
        case SYM_GEN_getData_638: return true;
        case SYM_GEN_setData_639: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onBananaActivated_2441: return true;
        case SYM_GEN_onStaminaUsed_2310: return true;
        case SYM_GEN_onItemRoll_1923: return true;
        case SYM_GEN_onItemRolled_1924: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SpicyBanana::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onBought_457: out = fn_onBought(args, argc); return true;
        case SYM_GEN_getData_638: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_639: out = fn_setData(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onBananaActivated_2441: out = fn_onBananaActivated(args, argc); return true;
        case SYM_GEN_onStaminaUsed_2310: out = fn_onStaminaUsed(args, argc); return true;
        case SYM_GEN_onItemRoll_1923: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_onItemRolled_1924: out = fn_onItemRolled(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SpicyBanana::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SpicyBanana::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_bananaDescriptor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isA_247, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_manananaDescriptor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isA_247, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpicyBanana::fn_onBought(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_boostedBananas = gd::GdVal::from_int(3LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpicyBanana::fn_getData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_boostedBananas;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpicyBanana::fn_setData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_data = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_data, gd::GdVal::null())))) {
        this->f_boostedBananas = lv_data;
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpicyBanana::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t711 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t712 = (_t711.kind == gd::GdVal::Kind::Arr) ? _t711.arr : nullptr;
        uint32_t _len__t713 = _t712 ? _t712->len : 0u;
        for (uint32_t _t713 = 0; _t713 < _len__t713; ++_t713) {
            gd::GdVal lv_banana = _t712->data[_t713];
            (void)([&]() { gd::GdVal _ca[] = {lv_banana, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "activated", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBananaActivated", 17u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
        }
    }
    this->f_staminaUsed = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_used_stamina", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onStaminaUsed", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpicyBanana::fn_onBananaActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_heatPerActivation, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpicyBanana::fn_onStaminaUsed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_staminaUsed = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_staminaUsed, lv_amount));
    gd::GdVal lv_healTicks = gd::gd_floor(gd::gd_div(gd_ctx, this->f_staminaUsed, this->f_staminaForHeal));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_healTicks, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_healTicks, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, _ca, 1); })();
        this->f_staminaUsed = gd::gd_coerce_float(gd::gd_sub(this->f_staminaUsed, gd::gd_mul(lv_healTicks, this->f_staminaForHeal)));
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpicyBanana::fn_onItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpicyBanana::fn_onItemRolled(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_descr, this->f_bananaDescriptor)))) {
        this->f_boostedBananas = gd::gd_sub(this->f_boostedBananas, gd::GdVal::from_int(1LL));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpicyBanana::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_bananaDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Banana", 6u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })();
    this->f_manananaDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Mananana", 8u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })();
    this->f_heatPerActivation = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_staminaForHeal = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SpicyBanana(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SpicyBanana>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpicyBanana = {CLS_Gd__gd_core_items__Exclusive__SpicyBanana, "SpicyBanana", "res://gd_core_items/Exclusive/SpicyBanana.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__SpicyBanana, &Gd__gd_core_items__Exclusive__SpicyBanana::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SpicyBanana::call_static_fn};

void Gd__gd_core_items__Exclusive__StoneShoes::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_hasActivated = gd::GdVal::from_bool(false);
    this->f_luck = gd::GdVal::null();
    this->f_empower = gd::GdVal::null();
    this->f_damReduction = gd::GdVal::null();
    this->f_healthThreshold = gd::GdVal::null();
    this->f_buffTimer = gd::GdVal::null();
    this->f_activationParticles = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__StoneShoes::meta() const { return &META_Gd__gd_core_items__Exclusive__StoneShoes; }
gd::GdVal Gd__gd_core_items__Exclusive__StoneShoes::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__StoneShoes::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__StoneShoes::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_hasActivated_1811: out = this->f_hasActivated; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_empower_998: out = this->f_empower; return true;
        case SYM_GEN_damReduction_1778: out = this->f_damReduction; return true;
        case SYM_GEN_healthThreshold_1759: out = this->f_healthThreshold; return true;
        case SYM_GEN_buffTimer_1724: out = this->f_buffTimer; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__StoneShoes::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_hasActivated_1811: this->f_hasActivated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_empower_998: this->f_empower = val; return true;
        case SYM_GEN_damReduction_1778: this->f_damReduction = val; return true;
        case SYM_GEN_healthThreshold_1759: this->f_healthThreshold = val; return true;
        case SYM_GEN_buffTimer_1724: this->f_buffTimer = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__StoneShoes::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onDamaged_1760: return true;
        case SYM_GEN_onBuffTimeout_1929: return true;
        case SYM_GEN_onCombatEnd_134: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__StoneShoes::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDamaged_1760: out = fn_onDamaged(args, argc); return true;
        case SYM_GEN_onBuffTimeout_1929: out = fn_onBuffTimeout(args, argc); return true;
        case SYM_GEN_onCombatEnd_134: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__StoneShoes::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneShoes::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_damaged", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDamaged", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneShoes::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(this->f_hasActivated)) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_relHealth = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getRelativeHealth_304, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_relHealth, this->f_healthThreshold)))) {
        this->f_hasActivated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_219, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_206, nullptr, 0), gd::GdVal::from_bool(true), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })()}; return gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_start_1685, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Ranged_2670), gd::gd_neg(this->f_damReduction)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_changeTypedDamageFactor_1264, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damReduction)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_changeEffectDamageFactor_1265, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_383, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneShoes::fn_onBuffTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Ranged_2670), this->f_damReduction}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_changeTypedDamageFactor_1264, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_damReduction}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_changeEffectDamageFactor_1265, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneShoes::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1686, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneShoes::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneShoes::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damResActive = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv_damResActive)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneShoes::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_856), SYM_GEN_High_2603), gd::GdVal::from_int(3LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__StoneShoes::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_luck = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "luck", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_empower = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_damReduction = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "damreduction", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_healthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "BuffTimer", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBuffTimeout", 13u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_137, _ca, 3); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__StoneShoes(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__StoneShoes>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__StoneShoes = {CLS_Gd__gd_core_items__Exclusive__StoneShoes, "StoneShoes", "res://gd_core_items/Exclusive/StoneShoes.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__StoneShoes, &Gd__gd_core_items__Exclusive__StoneShoes::get_static_prop_fn, &Gd__gd_core_items__Exclusive__StoneShoes::call_static_fn};

void Gd__gd_core_items__Exclusive__TimeMelting::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_heat = gd::GdVal::null();
    this->f_bonusdur = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__TimeMelting::meta() const { return &META_Gd__gd_core_items__Exclusive__TimeMelting; }
gd::GdVal Gd__gd_core_items__Exclusive__TimeMelting::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__TimeMelting::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__TimeMelting::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_heat_1801: out = this->f_heat; return true;
        case SYM_GEN_bonusdur_2355: out = this->f_bonusdur; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__TimeMelting::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_heat_1801: this->f_heat = val; return true;
        case SYM_GEN_bonusdur_2355: this->f_bonusdur = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__TimeMelting::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__TimeMelting::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__TimeMelting::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__TimeMelting::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasInventoryDuration_797, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TimeMelting::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t714 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t715 = (_t714.kind == gd::GdVal::Kind::Arr) ? _t714.arr : nullptr;
        uint32_t _len__t716 = _t715 ? _t715->len : 0u;
        for (uint32_t _t716 = 0; _t716 < _len__t716; ++_t716) {
            gd::GdVal lv_item = _t715->data[_t716];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u)), this->f_bonusdur}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_modifyParam_193, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TimeMelting::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TimeMelting::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_856), SYM_GEN_High_2603), gd::GdVal::from_int(100LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TimeMelting::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_bonusdur = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "bonusdur", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__TimeMelting(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__TimeMelting>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__TimeMelting = {CLS_Gd__gd_core_items__Exclusive__TimeMelting, "TimeMelting", "res://gd_core_items/Exclusive/TimeMelting.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__TimeMelting, &Gd__gd_core_items__Exclusive__TimeMelting::get_static_prop_fn, &Gd__gd_core_items__Exclusive__TimeMelting::call_static_fn};

void Gd__gd_core_items__Exclusive__WaterElemental::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_manaUsed = gd::GdVal::from_int(0);
    this->f_activeEffects = gd::GdVal::from_int(0LL);
    this->f_coldParticles = gd::GdVal::null();
    this->f_distortion = gd::GdVal::null();
    this->f_manaOnHit = gd::GdVal::null();
    this->f_bonusManaOnHit = gd::GdVal::null();
    this->f_iceSpeed = gd::GdVal::null();
    this->f_bonusDam = gd::GdVal::null();
    this->f_coldOnHit = gd::GdVal::null();
    this->f_manaNeeded1 = gd::GdVal::null();
    this->f_manaNeeded2 = gd::GdVal::null();
    this->f_manaNeeded3 = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__WaterElemental::meta() const { return &META_Gd__gd_core_items__Exclusive__WaterElemental; }
gd::GdVal Gd__gd_core_items__Exclusive__WaterElemental::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__WaterElemental::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__WaterElemental::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_manaUsed_1912: out = this->f_manaUsed; return true;
        case SYM_GEN_activeEffects_2520: out = this->f_activeEffects; return true;
        case SYM_GEN_coldParticles_2521: out = this->f_coldParticles; return true;
        case SYM_GEN_distortion_2107: out = this->f_distortion; return true;
        case SYM_GEN_manaOnHit_2522: out = this->f_manaOnHit; return true;
        case SYM_GEN_bonusManaOnHit_2523: out = this->f_bonusManaOnHit; return true;
        case SYM_GEN_iceSpeed_2422: out = this->f_iceSpeed; return true;
        case SYM_GEN_bonusDam_1780: out = this->f_bonusDam; return true;
        case SYM_GEN_coldOnHit_2220: out = this->f_coldOnHit; return true;
        case SYM_GEN_manaNeeded1_2524: out = this->f_manaNeeded1; return true;
        case SYM_GEN_manaNeeded2_2525: out = this->f_manaNeeded2; return true;
        case SYM_GEN_manaNeeded3_2526: out = this->f_manaNeeded3; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__WaterElemental::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaUsed_1912: this->f_manaUsed = gd::gd_coerce_int(val); return true;
        case SYM_GEN_activeEffects_2520: this->f_activeEffects = val; return true;
        case SYM_GEN_coldParticles_2521: this->f_coldParticles = val; return true;
        case SYM_GEN_distortion_2107: this->f_distortion = val; return true;
        case SYM_GEN_manaOnHit_2522: this->f_manaOnHit = val; return true;
        case SYM_GEN_bonusManaOnHit_2523: this->f_bonusManaOnHit = val; return true;
        case SYM_GEN_iceSpeed_2422: this->f_iceSpeed = val; return true;
        case SYM_GEN_bonusDam_1780: this->f_bonusDam = val; return true;
        case SYM_GEN_coldOnHit_2220: this->f_coldOnHit = val; return true;
        case SYM_GEN_manaNeeded1_2524: this->f_manaNeeded1 = val; return true;
        case SYM_GEN_manaNeeded2_2525: this->f_manaNeeded2 = val; return true;
        case SYM_GEN_manaNeeded3_2526: this->f_manaNeeded3 = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__WaterElemental::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_canAffect_secondary_289: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onManaChanged_1834: return true;
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN_playDropSound_151: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__WaterElemental::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_289: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onManaChanged_1834: out = fn_onManaChanged(args, argc); return true;
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_151: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__WaterElemental::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__WaterElemental::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Nature_2597)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WaterElemental::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Ice_2722)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WaterElemental::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_mana_changed", 22u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onManaChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    this->f_manaUsed = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_iceSpeed, ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Secondary_2583)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_275, _ca, 1); })();
    this->f_activeEffects = gd::GdVal::from_int(0LL);
    (void)([&]() { gd::GdVal _ca[] = {this->f_activeEffects}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WaterElemental::fn_onManaChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_event, SYM_GEN_type_1005), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Mana_2571))))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "used", 4u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, lv_event, SYM_GEN_getParam_1484, _ca, 2); })())) : gd::GdVal::from_bool(false)))) {
        this->f_manaUsed = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_manaUsed, gd::gd_abs(lv_amount)));
        gd::GdVal lv_before = this->f_activeEffects;
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_activeEffects, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_manaUsed, this->f_manaNeeded1)))) : gd::GdVal::from_bool(false)))) {
            this->f_activeEffects = gd::GdVal::from_int(1LL);
        }
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_activeEffects, gd::GdVal::from_int(1LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_manaUsed, this->f_manaNeeded2)))) : gd::GdVal::from_bool(false)))) {
            this->f_activeEffects = gd::GdVal::from_int(2LL);
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusDam}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_163, _ca, 1); })();
        }
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_activeEffects, gd::GdVal::from_int(2LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_manaUsed, this->f_manaNeeded3)))) : gd::GdVal::from_bool(false)))) {
            this->f_activeEffects = gd::GdVal::from_int(3LL);
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_before, this->f_activeEffects)))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_activeEffects}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WaterElemental::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        gd::GdVal lv_mana = this->f_manaOnHit;
        gd::GdVal lv_chance = gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0));
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_chance}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, _ca, 1); })())) {
            lv_mana = gd::gd_add(gd_ctx, lv_mana, this->f_bonusManaOnHit);
        }
        (void)([&]() { gd::GdVal _ca[] = {lv_mana, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 2); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_activeEffects, gd::GdVal::from_int(1LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, _ca, 2); })();
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_activeEffects, gd::GdVal::from_int(3LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_coldOnHit, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_353, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WaterElemental::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WaterElemental::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__activeEffects = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv__activeEffects = gd::gd_coerce_int(lv__activeEffects);
    this->f_activeEffects = lv__activeEffects;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_activeEffects, gd::GdVal::from_int(3LL))))) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WaterElemental::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {lv_wrapInColor}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN_getDescription_642, _ca, 1, _out); return _out; })();
    gd::GdVal lv_colors = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_triggerColor_2723), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_triggerColor_2723), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_triggerColor_2723)}));
    if (gd::gd_truth(this->f_placed)) {
        {
            gd::GdVal _t717 = gd::gd_iter_seq(gd_ctx.arena, this->f_activeEffects);
            gd::GdArr* _t718 = (_t717.kind == gd::GdVal::Kind::Arr) ? _t717.arr : nullptr;
            uint32_t _len__t719 = _t718 ? _t718->len : 0u;
            for (uint32_t _t719 = 0; _t719 < _len__t719; ++_t719) {
                gd::GdVal lv_i = _t718->data[_t719];
                { gd::GdVal _t720 = lv_colors; gd::GdVal _t721 = lv_i; gd::set_index(gd_ctx, _t720, _t721, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_modifiedColor_2724)); }
            }
        }
    }
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, lv_colors, gd::GdVal::from_bool(false), lv_wrapInColor}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModeDescription_645, _ca, 4); })();
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WaterElemental::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WaterElemental::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1377), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WaterElemental::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_manaOnHit = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_bonusManaOnHit = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana2", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_iceSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_bonusDam = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dam", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_coldOnHit = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cold", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_manaNeeded1 = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "manat1", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_manaNeeded2 = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "manat2", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_manaNeeded3 = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "manat3", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ownerType, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Owner_854), SYM_GEN_GridStorage_2610))))) {
    }
    else {
    }
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__WaterElemental(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__WaterElemental>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__WaterElemental = {CLS_Gd__gd_core_items__Exclusive__WaterElemental, "WaterElemental", "res://gd_core_items/Exclusive/WaterElemental.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__WaterElemental, &Gd__gd_core_items__Exclusive__WaterElemental::get_static_prop_fn, &Gd__gd_core_items__Exclusive__WaterElemental::call_static_fn};

void Gd__gd_core_items__Gems__CorruptedCrystal::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Gems__Gem::init_fields(gd_ctx);
    this->f_damageBonusApplied = gd::GdVal::from_bool(false);
    this->f_debuffsInflicted = gd::GdVal::from_int(0);
    this->f_weaponParticles = gd::GdVal::null();
    this->f_healthThreshold = gd::GdVal::null();
    this->f_damageFactor = gd::GdVal::null();
    this->f_debuffsNeeded = gd::GdVal::null();
    this->f_blockGain = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Gems__CorruptedCrystal::meta() const { return &META_Gd__gd_core_items__Gems__CorruptedCrystal; }
gd::GdVal Gd__gd_core_items__Gems__CorruptedCrystal::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_gemColor_995: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.938676), gd::GdVal::from_float(0.24128), gd::GdVal::from_float(0.988281)}; return gd::make_color_from_args(_ca, 3); })();
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Gems__CorruptedCrystal::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Gems__CorruptedCrystal::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_damageBonusApplied_2533: out = this->f_damageBonusApplied; return true;
        case SYM_GEN_debuffsInflicted_2534: out = this->f_debuffsInflicted; return true;
        case SYM_GEN_weaponParticles_2535: out = this->f_weaponParticles; return true;
        case SYM_GEN_healthThreshold_1759: out = this->f_healthThreshold; return true;
        case SYM_GEN_damageFactor_2315: out = this->f_damageFactor; return true;
        case SYM_GEN_debuffsNeeded_2111: out = this->f_debuffsNeeded; return true;
        case SYM_GEN_blockGain_2536: out = this->f_blockGain; return true;
        case SYM_GEN_gemColor_995: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core_items__Gems__CorruptedCrystal::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damageBonusApplied_2533: this->f_damageBonusApplied = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_debuffsInflicted_2534: this->f_debuffsInflicted = gd::gd_coerce_int(val); return true;
        case SYM_GEN_weaponParticles_2535: this->f_weaponParticles = val; return true;
        case SYM_GEN_healthThreshold_1759: this->f_healthThreshold = val; return true;
        case SYM_GEN_damageFactor_2315: this->f_damageFactor = val; return true;
        case SYM_GEN_debuffsNeeded_2111: this->f_debuffsNeeded = val; return true;
        case SYM_GEN_blockGain_2536: this->f_blockGain = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Gems__CorruptedCrystal::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_prepareWeapon_982: return true;
        case SYM_GEN_onOpponentDamaged_1897: return true;
        case SYM_GEN_combatEndWeapon_988: return true;
        case SYM_GEN_prepareArmor_983: return true;
        case SYM_GEN_onOpponentDebuffsChanged_1728: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_992: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::has_own_method(m);
}
bool Gd__gd_core_items__Gems__CorruptedCrystal::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_prepareWeapon_982: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_onOpponentDamaged_1897: out = fn_onOpponentDamaged(args, argc); return true;
        case SYM_GEN_combatEndWeapon_988: out = fn_combatEndWeapon(args, argc); return true;
        case SYM_GEN_prepareArmor_983: out = fn_prepareArmor(args, argc); return true;
        case SYM_GEN_onOpponentDebuffsChanged_1728: out = fn_onOpponentDebuffsChanged(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_992: out = fn_onHotSwapHoverWithGemEnd(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Gems__CorruptedCrystal::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Gems__Gem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Gems__CorruptedCrystal::fn_prepareWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_damageBonusApplied = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_damaged", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onOpponentDamaged", 17u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__CorruptedCrystal::fn_onOpponentDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__healthChange = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_getRelativeHealth_304, nullptr, 0), this->f_healthThreshold)))) {
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_damageBonusApplied)))) {
            this->f_damageBonusApplied = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
            (void)([&]() { gd::GdVal _ca[] = {this->f_damageFactor}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_391, nullptr, 0), SYM_GEN_addBonusDamageFactor_308, _ca, 1); })();
        }
    }
    else if (gd::gd_truth(this->f_damageBonusApplied)) {
        this->f_damageBonusApplied = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
        (void)([&]() { gd::GdVal _ca[] = {this->f_damageFactor}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_391, nullptr, 0), SYM_GEN_reduceBonusDamageFactor_309, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__CorruptedCrystal::fn_combatEndWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__CorruptedCrystal::fn_prepareArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_debuffsInflicted = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onOpponentDebuffsChanged", 24u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToOpponentDebuffs_378, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__CorruptedCrystal::fn_onOpponentDebuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(gd::call_method(gd_ctx, lv_event, SYM_GEN_getOrigin_1489, nullptr, 0), &META_Gd__gd_core_items__Item))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::call_method(gd_ctx, lv_event, SYM_GEN_getOrigin_1489, nullptr, 0), SYM_GEN_character_76, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0))))) : gd::GdVal::from_bool(false)))) {
            this->f_debuffsInflicted = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_debuffsInflicted, lv_amount));
            gd::GdVal lv_activations = gd::gd_coerce_int(gd::gd_div(gd_ctx, this->f_debuffsInflicted, this->f_debuffsNeeded));
            this->f_debuffsInflicted = gd::gd_coerce_int(gd::gd_mod(gd_ctx, this->f_debuffsInflicted, gd::gd_coerce_int(this->f_debuffsNeeded)));
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_activations, gd::GdVal::from_int(0LL))))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0), this->f_blockGain), lv_activations), gd::GdVal::from_bool(true), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, _ca, 3); })();
                (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__CorruptedCrystal::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_addFatigueDamage_1179, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_takeFatigueDamage_1180, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__CorruptedCrystal::fn_onHotSwapHoverWithGemEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__CorruptedCrystal::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_healthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    this->f_damageFactor = gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0), gd::GdVal::from_float(100.0));
    this->f_debuffsNeeded = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0);
    this->f_blockGain = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Gems__CorruptedCrystal(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Gems__CorruptedCrystal>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Gems__CorruptedCrystal = {CLS_Gd__gd_core_items__Gems__CorruptedCrystal, "CorruptedCrystal", "res://gd_core_items/Gems/CorruptedCrystal.gd", &META_Gd__gd_core_items__Gems__Gem, true, _alloc_Gd__gd_core_items__Gems__CorruptedCrystal, &Gd__gd_core_items__Gems__CorruptedCrystal::get_static_prop_fn, &Gd__gd_core_items__Gems__CorruptedCrystal::call_static_fn};

void Gd__gd_core_items__HoloFireLizard::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Card::init_fields(gd_ctx);
    this->f_fireParticles = gd::GdVal::null();
    this->f_damFactor = gd::GdVal::null();
    this->f_heat = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__HoloFireLizard::meta() const { return &META_Gd__gd_core_items__HoloFireLizard; }
gd::GdVal Gd__gd_core_items__HoloFireLizard::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Card::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__HoloFireLizard::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__HoloFireLizard::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_fireParticles_1799: out = this->f_fireParticles; return true;
        case SYM_GEN_damFactor_1800: out = this->f_damFactor; return true;
        case SYM_GEN_heat_1801: out = this->f_heat; return true;
        default: break;
    }
    return Gd__gd_core_items__Card::get_prop(prop, out);
}
bool Gd__gd_core_items__HoloFireLizard::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_fireParticles_1799: this->f_fireParticles = val; return true;
        case SYM_GEN_damFactor_1800: this->f_damFactor = val; return true;
        case SYM_GEN_heat_1801: this->f_heat = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Card::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__HoloFireLizard::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doRevealEffect_893: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Card::has_own_method(m);
}
bool Gd__gd_core_items__HoloFireLizard::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doRevealEffect_893: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Card::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__HoloFireLizard::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Card::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__HoloFireLizard::fn_doRevealEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_damFactor}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeEffectDamageFactor_1265, _ca, 1); })();
    gd::GdVal lv_dam = gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_minDam_1579), gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), this->f_chainPosition));
    gd::GdVal lv_res = ([&]() { gd::GdVal _ca[] = {lv_dam}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealEffectDamage_223, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HoloFireLizard::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Card::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_damFactor = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "damfactor", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_heat = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0));
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1459, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__HoloFireLizard(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__HoloFireLizard>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__HoloFireLizard = {CLS_Gd__gd_core_items__HoloFireLizard, "HoloFireLizard", "res://gd_core_items/HoloFireLizard.gd", &META_Gd__gd_core_items__Card, true, _alloc_Gd__gd_core_items__HoloFireLizard, &Gd__gd_core_items__HoloFireLizard::get_static_prop_fn, &Gd__gd_core_items__HoloFireLizard::call_static_fn};

void Gd__gd_core_items__MoonShield::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Shield::init_fields(gd_ctx);
    this->f_blockAcc = gd::GdVal::from_int(0);
    this->f_blockForMana = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core_items__MoonShield::meta() const { return &META_Gd__gd_core_items__MoonShield; }
gd::GdVal Gd__gd_core_items__MoonShield::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Shield::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__MoonShield::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__MoonShield::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_blockAcc_1851: out = this->f_blockAcc; return true;
        case SYM_GEN_blockForMana_1852: out = this->f_blockForMana; return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::get_prop(prop, out);
}
bool Gd__gd_core_items__MoonShield::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blockAcc_1851: this->f_blockAcc = gd::gd_coerce_int(val); return true;
        case SYM_GEN_blockForMana_1852: this->f_blockForMana = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__MoonShield::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_afterBlock_1847: return true;
        case SYM_GEN_onItemGaveBlock_1853: return true;
        case SYM_GEN_canBlockDamageRes_1848: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::has_own_method(m);
}
bool Gd__gd_core_items__MoonShield::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_afterBlock_1847: out = fn_afterBlock(args, argc); return true;
        case SYM_GEN_onItemGaveBlock_1853: out = fn_onItemGaveBlock(args, argc); return true;
        case SYM_GEN_canBlockDamageRes_1848: out = fn_canBlockDamageRes(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Shield::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__MoonShield::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Shield::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__MoonShield::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBlock_293, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MoonShield::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t722 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t723 = (_t722.kind == gd::GdVal::Kind::Arr) ? _t722.arr : nullptr;
        uint32_t _len__t724 = _t723 ? _t723->len : 0u;
        for (uint32_t _t724 = 0; _t724 < _len__t724; ++_t724) {
            gd::GdVal lv_item = _t723->data[_t724];
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Block_2564), gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_giveBuffPower_305, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gave_block", 10u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onItemGaveBlock", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
        }
    }
    this->f_blockAcc = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MoonShield::fn_afterBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0), gd::get_prop(gd_ctx, this->f_blockedDamageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drainStamina_119, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MoonShield::fn_onItemGaveBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    this->f_blockAcc = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_blockAcc, lv_amount));
    gd::GdVal lv_mana = gd::gd_div(gd_ctx, this->f_blockAcc, this->f_blockForMana);
    this->f_blockAcc = gd::gd_coerce_int(gd::gd_mod(gd_ctx, this->f_blockAcc, this->f_blockForMana));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_mana, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_mana, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MoonShield::fn_canBlockDamageRes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_triggerOnAttacked_1439, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__MoonShield::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Shield::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_blockForMana = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__MoonShield(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__MoonShield>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__MoonShield = {CLS_Gd__gd_core_items__MoonShield, "MoonShield", "res://gd_core_items/MoonShield.gd", &META_Gd__gd_core_items__Shield, true, _alloc_Gd__gd_core_items__MoonShield, &Gd__gd_core_items__MoonShield::get_static_prop_fn, &Gd__gd_core_items__MoonShield::call_static_fn};

void Gd__gd_core_items__RainbowGoobertRanger::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Goobert::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__RainbowGoobertRanger::meta() const { return &META_Gd__gd_core_items__RainbowGoobertRanger; }
gd::GdVal Gd__gd_core_items__RainbowGoobertRanger::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__RainbowGoobertRanger::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__RainbowGoobertRanger::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Goobert::get_prop(prop, out);
}
bool Gd__gd_core_items__RainbowGoobertRanger::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__RainbowGoobertRanger::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__RainbowGoobertRanger::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__RainbowGoobertRanger::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__RainbowGoobertRanger::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_212, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_219, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_269, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_215, _ca, 1); })();
    {
        gd::GdVal _t725 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t726 = (_t725.kind == gd::GdVal::Kind::Arr) ? _t725.arr : nullptr;
        uint32_t _len__t727 = _t726 ? _t726->len : 0u;
        for (uint32_t _t727 = 0; _t727 < _len__t727; ++_t727) {
            gd::GdVal lv_item = _t726->data[_t727];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_92, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP6_270, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addBonusDamage_163, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__RainbowGoobertRanger::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__RainbowGoobertRanger(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__RainbowGoobertRanger>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__RainbowGoobertRanger = {CLS_Gd__gd_core_items__RainbowGoobertRanger, "RainbowGoobertRanger", "res://gd_core_items/RainbowGoobertRanger.gd", &META_Gd__gd_core_items__Goobert, true, _alloc_Gd__gd_core_items__RainbowGoobertRanger, &Gd__gd_core_items__RainbowGoobertRanger::get_static_prop_fn, &Gd__gd_core_items__RainbowGoobertRanger::call_static_fn};

void Gd__gd_core_items__StrongStoneSkinPotion::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__StoneSkinPotion::init_fields(gd_ctx);
    this->f_spikes = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__StrongStoneSkinPotion::meta() const { return &META_Gd__gd_core_items__StrongStoneSkinPotion; }
gd::GdVal Gd__gd_core_items__StrongStoneSkinPotion::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__StoneSkinPotion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__StrongStoneSkinPotion::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__StrongStoneSkinPotion::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_spikes_898: out = this->f_spikes; return true;
        default: break;
    }
    return Gd__gd_core_items__StoneSkinPotion::get_prop(prop, out);
}
bool Gd__gd_core_items__StrongStoneSkinPotion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_spikes_898: this->f_spikes = val; return true;
        default: break;
    }
    return Gd__gd_core_items__StoneSkinPotion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__StrongStoneSkinPotion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1754: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__StoneSkinPotion::has_own_method(m);
}
bool Gd__gd_core_items__StrongStoneSkinPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1754: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__StoneSkinPotion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__StrongStoneSkinPotion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__StoneSkinPotion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__StrongStoneSkinPotion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_triggerEvent}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__StoneSkinPotion::call_method(gd_ctx, SYM_GEN_onTriggerPotion_1754, _ca, 1, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Spikes_2565), this->f_spikes, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacksTemporary_204, _ca, 5); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongStoneSkinPotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__StoneSkinPotion::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__StrongStoneSkinPotion(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__StrongStoneSkinPotion>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__StrongStoneSkinPotion = {CLS_Gd__gd_core_items__StrongStoneSkinPotion, "StrongStoneSkinPotion", "res://gd_core_items/StrongStoneSkinPotion.gd", &META_Gd__gd_core_items__StoneSkinPotion, true, _alloc_Gd__gd_core_items__StrongStoneSkinPotion, &Gd__gd_core_items__StrongStoneSkinPotion::get_static_prop_fn, &Gd__gd_core_items__StrongStoneSkinPotion::call_static_fn};
