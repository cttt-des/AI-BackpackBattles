#pragma STDC FP_CONTRACT OFF

#include "../hdrs/Gd__gd_core_items__Stone.hpp"
#include "../hdrs/Gd__gd_core__BowandArrow.hpp"
#include "../hdrs/Gd__gd_core__CoreContext.hpp"
#include "../hdrs/Gd__gd_core__CoreUtil__INNER__DictSorter.hpp"
#include "../hdrs/Gd__gd_core__CoreUtil.hpp"
#include "../hdrs/Gd__gd_core__DragonEgg.hpp"
#include "../hdrs/Gd__gd_core__HealingHerbs.hpp"
#include "../hdrs/Gd__gd_core__LightGoobert.hpp"
#include "../hdrs/Gd__gd_core__PestilenceFlask.hpp"
#include "../hdrs/Gd__gd_core__RangerBag.hpp"
#include "../hdrs/Gd__gd_core__StoneSkinPotion.hpp"
#include "../hdrs/Gd__gd_core__VampiricGloves.hpp"
#include "../hdrs/Gd__gd_core_items__Bag.hpp"
#include "../hdrs/Gd__gd_core_items__BurningTorch.hpp"
#include "../hdrs/Gd__gd_core_items__DeckofCards.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__AmuletofSteel.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__BadgerRune.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__BookofBasics.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__BustedBlade.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Chess__BlackRook.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__CriticalPoison.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__DoomCap.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__EmeraldEgg.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__FireShelly.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__FurciferPrime.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__HogusBogus.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__KingGoobert.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__MagicCollar.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__MoltenSpear2.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__PiggyPinata.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__PuzzlebagL.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Recombobulator.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SewingCase.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Snowcake.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SpiritBells.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SunArmor.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Twine.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__WolfBadge.hpp"
#include "../hdrs/Gd__gd_core_items__Gems__Skull.hpp"
#include "../hdrs/Gd__gd_core_items__Jynxtorquilla.hpp"
#include "../hdrs/Gd__gd_core_items__PlatinCustomerCard.hpp"
#include "../hdrs/Gd__gd_core_items__Shovel.hpp"
#include "../hdrs/Gd__gd_core_items__Torch.hpp"

void Gd__gd_core_items__Stone::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_ammunition = gd::GdVal::from_int(0);
    this->f_bonusDamage = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core_items__Stone::meta() const { return &META_Gd__gd_core_items__Stone; }
gd::GdVal Gd__gd_core_items__Stone::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Stone::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Stone::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_ammunition_899: out = this->f_ammunition; return true;
        case SYM_GEN_bonusDamage_900: out = this->f_bonusDamage; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Stone::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_ammunition_899: this->f_ammunition = gd::gd_coerce_int(val); return true;
        case SYM_GEN_bonusDamage_900: this->f_bonusDamage = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Stone::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_combatEnd_129: return true;
        case SYM_GEN_setBagOfStones_901: return true;
        case SYM_GEN_onPreDealDamage_late_902: return true;
        case SYM_GEN_preHit_903: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onDealtDamage_904: return true;
        case SYM_GEN_onHit_905: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Stone::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_combatEnd_129: out = fn_combatEnd(args, argc); return true;
        case SYM_GEN_setBagOfStones_901: out = fn_setBagOfStones(args, argc); return true;
        case SYM_GEN_onPreDealDamage_late_902: out = fn_onPreDealDamage_late(args, argc); return true;
        case SYM_GEN_preHit_903: out = fn_preHit(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onDealtDamage_904: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_onHit_905: out = fn_onHit(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Stone::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Stone::fn_combatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_combatEnd_129, nullptr, 0, _out); return _out; })();
    this->f_ammunition = gd::gd_coerce_int(gd::GdVal::from_int(1LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Stone::fn_setBagOfStones(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_ammunition = gd::gd_coerce_int(gd::GdVal::from_int(9000LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Stone::fn_onPreDealDamage_late(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_preHit_903, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Stone::fn_preHit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeBlock_203, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Stone::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_ammunition, gd::GdVal::from_int(1LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_114, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StaminaResult_1276), SYM_GEN_Sufficient_2603))))) : gd::GdVal::from_bool(false)))) {
        this->f_ammunition = gd::gd_coerce_int(gd::gd_sub(this->f_ammunition, gd::GdVal::from_int(1LL)));
        gd::GdVal lv_res = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_218, nullptr, 0);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ammunition, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_143, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_379, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Stone::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onHit_905, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Stone::fn_onHit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Stone::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1457, _ca, 1); })();
    this->f_ammunition = gd::gd_coerce_int(gd::GdVal::from_int(1LL));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Stone(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Stone>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Stone = {CLS_Gd__gd_core_items__Stone, "Stone", "res://gd_core_items/Stone.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Stone, &Gd__gd_core_items__Stone::get_static_prop_fn, &Gd__gd_core_items__Stone::call_static_fn};

void Gd__gd_core__BowandArrow::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Bow::init_fields(gd_ctx);
    this->f_bonusDmg = gd::GdVal::from_int(0);
    this->f_bonusDmgPerHit = gd::GdVal::from_int(0);
    this->f_maxDmg = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core__BowandArrow::meta() const { return &META_Gd__gd_core__BowandArrow; }
gd::GdVal Gd__gd_core__BowandArrow::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Bow::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__BowandArrow::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__BowandArrow::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_bonusDmg_947: out = this->f_bonusDmg; return true;
        case SYM_GEN_bonusDmgPerHit_948: out = this->f_bonusDmgPerHit; return true;
        case SYM_GEN_maxDmg_949: out = this->f_maxDmg; return true;
        default: break;
    }
    return Gd__gd_core__Bow::get_prop(prop, out);
}
bool Gd__gd_core__BowandArrow::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bonusDmg_947: this->f_bonusDmg = gd::gd_coerce_int(val); return true;
        case SYM_GEN_bonusDmgPerHit_948: this->f_bonusDmgPerHit = gd::gd_coerce_int(val); return true;
        case SYM_GEN_maxDmg_949: this->f_maxDmg = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core__Bow::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__BowandArrow::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_hasAttackEffect_293: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onWeaponAttacked_946: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Bow::has_own_method(m);
}
bool Gd__gd_core__BowandArrow::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_hasAttackEffect_293: out = fn_hasAttackEffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onWeaponAttacked_946: out = fn_onWeaponAttacked(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Bow::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__BowandArrow::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Bow::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__BowandArrow::fn_hasAttackEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BowandArrow::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_bonusDmg = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BowandArrow::fn_onWeaponAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        gd::GdVal lv_dmgAdded = gd::GdVal::from_bool(false);
        gd::GdVal lv_attackEffectCount = gd::gd_add(gd_ctx, gd::GdVal::from_int(1LL), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollDoubleAttackEffect_185, nullptr, 0));
        {
            gd::GdVal _t1123 = gd::gd_iter_seq(gd_ctx.arena, lv_attackEffectCount);
            gd::GdArr* _t1124 = (_t1123.kind == gd::GdVal::Kind::Arr) ? _t1123.arr : nullptr;
            uint32_t _len__t1125 = _t1124 ? _t1124->len : 0u;
            for (uint32_t _t1125 = 0; _t1125 < _len__t1125; ++_t1125) {
                gd::GdVal lv_i = _t1124->data[_t1125];
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_bonusDmg, this->f_maxDmg)))) {
                    this->f_bonusDmg = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_bonusDmg, this->f_bonusDmgPerHit));
                    (void)([&]() { gd::GdVal _ca[] = {this->f_bonusDmgPerHit}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_159, _ca, 1); })();
                    lv_dmgAdded = gd::GdVal::from_bool(true);
                }
            }
        }
        if (gd::gd_truth(lv_dmgAdded)) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusDmg, gd::GdVal::from_bool(false), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BowandArrow::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BowandArrow::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__bonusDmg = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv__bonusDmg, gd::GdVal::from_int(0LL))))) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BowandArrow::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Bow::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_bonusDmgPerHit = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0));
    this->f_maxDmg = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__BowandArrow(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__BowandArrow>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__BowandArrow = {CLS_Gd__gd_core__BowandArrow, "BowandArrow", "res://gd_core/BowandArrow.gd", &META_Gd__gd_core__Bow, false, _alloc_Gd__gd_core__BowandArrow, &Gd__gd_core__BowandArrow::get_static_prop_fn, &Gd__gd_core__BowandArrow::call_static_fn};

void Gd__gd_core__CoreContext::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_rng = gd::GdVal::null();
    this->f_util = gd::GdVal::null();
    this->f_bus = gd::GdVal::null();
    this->f_hooks = gd::GdVal::null();
    this->f_combat_log = gd::GdVal::null();
    this->f_player = gd::GdVal::null();
    this->f_opponent = gd::GdVal::null();
    this->f_fight_ended = gd::GdVal::from_bool(false);
    this->f_time = gd::GdVal::from_float(0.0);
    this->f_probe_pass = gd::GdVal::from_int(0LL);
    this->f_frame_counter = gd::GdVal::from_int(0LL);
    this->f_combat_time = gd::GdVal::from_float(0.0);
    this->f_below_master = gd::GdVal::from_bool(false);
    this->f_label_rng_enabled = gd::GdVal::from_bool(true);
    this->f_lobbies_mode = gd::GdVal::from_bool(false);
    this->f_custom_health_multiplier = gd::GdVal::from_float(100.0);
    this->f__drawseq_enabled = gd::GdVal::from_bool(false);
    this->f_lib_fires = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_combat = gd::GdVal::null();
    this->f_item_book = gd::GdVal::null();
    this->f_sandbag_active = gd::GdVal::from_bool(false);
    this->f_cur_mode = gd::GdVal::from_int(0LL);
    this->f_cur_round = gd::GdVal::from_int(0LL);
    this->f_rope_speedups = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_cube_advanced = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_event_type_keys = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_class_resources = gd::GdVal::null();
    this->f_unhealingDamageSource = gd::GdVal::null();
    this->f_fatigueDamageSource = gd::GdVal::null();
    this->f_stealLifeDamageSource = gd::GdVal::null();
    this->f_out_of_stamina_count = gd::GdVal::from_int(0LL);
    this->f_warn_unknown_api = gd::GdVal::from_bool(true);
    this->f__deferred = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f__idle_frame_calls = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f__timed = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_deferred_flush_enabled = gd::GdVal::from_bool(true);
    this->f_eb_relay_mirrored = gd::GdVal::from_bool(false);
    this->f_keyed_stop_clears_seen = gd::GdVal::from_bool(false);
    this->f_keyed_cleanse_biggest_first = gd::GdVal::from_bool(false);
    this->f__emptyGrid = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__CoreContext::meta() const { return &META_Gd__gd_core__CoreContext; }
gd::GdVal Gd__gd_core__CoreContext::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_PHYSICS_FPS_1370: return gd::GdVal::from_float(60.0);
        case SYM_GEN_PHYSICS_DELTA_1371: return gd::gd_div(gd_ctx, gd::GdVal::from_float(1.0), gd::GdVal::from_float(60.0));
        case SYM_GEN_COMBAT_DELAY_1372: return gd::GdVal::from_float(2.5);
        case SYM_GEN_FATIGUE_TIME_1277: return gd::GdVal::from_int(17LL);
        default: break;
    }
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreContext::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreContext::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_rng_1373: out = this->f_rng; return true;
        case SYM_GEN_util_1374: out = this->f_util; return true;
        case SYM_GEN_bus_1375: out = this->f_bus; return true;
        case SYM_GEN_hooks_1376: out = this->f_hooks; return true;
        case SYM_GEN_combat_log_1377: out = this->f_combat_log; return true;
        case SYM_GEN_player_1280: out = this->f_player; return true;
        case SYM_GEN_opponent_73: out = this->f_opponent; return true;
        case SYM_GEN_fight_ended_1283: out = this->f_fight_ended; return true;
        case SYM_GEN_time_1378: out = this->f_time; return true;
        case SYM_GEN_probe_pass_1379: out = this->f_probe_pass; return true;
        case SYM_GEN_frame_counter_1380: out = this->f_frame_counter; return true;
        case SYM_GEN_combat_time_1284: out = this->f_combat_time; return true;
        case SYM_GEN_below_master_1381: out = this->f_below_master; return true;
        case SYM_GEN_label_rng_enabled_1382: out = this->f_label_rng_enabled; return true;
        case SYM_GEN_lobbies_mode_1383: out = this->f_lobbies_mode; return true;
        case SYM_GEN_custom_health_multiplier_1384: out = this->f_custom_health_multiplier; return true;
        case SYM_GEN__drawseq_enabled_1385: out = this->f__drawseq_enabled; return true;
        case SYM_GEN_lib_fires_1386: out = this->f_lib_fires; return true;
        case SYM_GEN_combat_1387: out = this->f_combat; return true;
        case SYM_GEN_item_book_1388: out = this->f_item_book; return true;
        case SYM_GEN_sandbag_active_1389: out = this->f_sandbag_active; return true;
        case SYM_GEN_cur_mode_1390: out = this->f_cur_mode; return true;
        case SYM_GEN_cur_round_1391: out = this->f_cur_round; return true;
        case SYM_GEN_rope_speedups_1392: out = this->f_rope_speedups; return true;
        case SYM_GEN_cube_advanced_1393: out = this->f_cube_advanced; return true;
        case SYM_GEN_event_type_keys_1394: out = this->f_event_type_keys; return true;
        case SYM_GEN_class_resources_1395: out = this->f_class_resources; return true;
        case SYM_GEN_unhealingDamageSource_1396: out = this->f_unhealingDamageSource; return true;
        case SYM_GEN_fatigueDamageSource_1397: out = this->f_fatigueDamageSource; return true;
        case SYM_GEN_stealLifeDamageSource_1398: out = this->f_stealLifeDamageSource; return true;
        case SYM_GEN_out_of_stamina_count_1399: out = this->f_out_of_stamina_count; return true;
        case SYM_GEN_warn_unknown_api_1400: out = this->f_warn_unknown_api; return true;
        case SYM_GEN__deferred_1401: out = this->f__deferred; return true;
        case SYM_GEN__idle_frame_calls_1402: out = this->f__idle_frame_calls; return true;
        case SYM_GEN__timed_1403: out = this->f__timed; return true;
        case SYM_GEN_deferred_flush_enabled_1404: out = this->f_deferred_flush_enabled; return true;
        case SYM_GEN_eb_relay_mirrored_1405: out = this->f_eb_relay_mirrored; return true;
        case SYM_GEN_keyed_stop_clears_seen_1406: out = this->f_keyed_stop_clears_seen; return true;
        case SYM_GEN_keyed_cleanse_biggest_first_1407: out = this->f_keyed_cleanse_biggest_first; return true;
        case SYM_GEN__emptyGrid_1408: out = this->f__emptyGrid; return true;
        case SYM_GEN_PHYSICS_FPS_1370: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_PHYSICS_DELTA_1371: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_COMBAT_DELAY_1372: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_FATIGUE_TIME_1277: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreContext::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_rng_1373: this->f_rng = val; return true;
        case SYM_GEN_util_1374: this->f_util = val; return true;
        case SYM_GEN_bus_1375: this->f_bus = val; return true;
        case SYM_GEN_hooks_1376: this->f_hooks = val; return true;
        case SYM_GEN_combat_log_1377: this->f_combat_log = val; return true;
        case SYM_GEN_player_1280: this->f_player = val; return true;
        case SYM_GEN_opponent_73: this->f_opponent = val; return true;
        case SYM_GEN_fight_ended_1283: this->f_fight_ended = val; return true;
        case SYM_GEN_time_1378: this->f_time = val; return true;
        case SYM_GEN_probe_pass_1379: this->f_probe_pass = val; return true;
        case SYM_GEN_frame_counter_1380: this->f_frame_counter = val; return true;
        case SYM_GEN_combat_time_1284: this->f_combat_time = val; return true;
        case SYM_GEN_below_master_1381: this->f_below_master = val; return true;
        case SYM_GEN_label_rng_enabled_1382: this->f_label_rng_enabled = val; return true;
        case SYM_GEN_lobbies_mode_1383: this->f_lobbies_mode = val; return true;
        case SYM_GEN_custom_health_multiplier_1384: this->f_custom_health_multiplier = val; return true;
        case SYM_GEN__drawseq_enabled_1385: this->f__drawseq_enabled = val; return true;
        case SYM_GEN_lib_fires_1386: this->f_lib_fires = val; return true;
        case SYM_GEN_combat_1387: this->f_combat = val; return true;
        case SYM_GEN_item_book_1388: this->f_item_book = val; return true;
        case SYM_GEN_sandbag_active_1389: this->f_sandbag_active = val; return true;
        case SYM_GEN_cur_mode_1390: this->f_cur_mode = val; return true;
        case SYM_GEN_cur_round_1391: this->f_cur_round = val; return true;
        case SYM_GEN_rope_speedups_1392: this->f_rope_speedups = val; return true;
        case SYM_GEN_cube_advanced_1393: this->f_cube_advanced = val; return true;
        case SYM_GEN_event_type_keys_1394: this->f_event_type_keys = val; return true;
        case SYM_GEN_class_resources_1395: this->f_class_resources = val; return true;
        case SYM_GEN_unhealingDamageSource_1396: this->f_unhealingDamageSource = val; return true;
        case SYM_GEN_fatigueDamageSource_1397: this->f_fatigueDamageSource = val; return true;
        case SYM_GEN_stealLifeDamageSource_1398: this->f_stealLifeDamageSource = val; return true;
        case SYM_GEN_out_of_stamina_count_1399: this->f_out_of_stamina_count = val; return true;
        case SYM_GEN_warn_unknown_api_1400: this->f_warn_unknown_api = val; return true;
        case SYM_GEN__deferred_1401: this->f__deferred = val; return true;
        case SYM_GEN__idle_frame_calls_1402: this->f__idle_frame_calls = val; return true;
        case SYM_GEN__timed_1403: this->f__timed = val; return true;
        case SYM_GEN_deferred_flush_enabled_1404: this->f_deferred_flush_enabled = val; return true;
        case SYM_GEN_eb_relay_mirrored_1405: this->f_eb_relay_mirrored = val; return true;
        case SYM_GEN_keyed_stop_clears_seen_1406: this->f_keyed_stop_clears_seen = val; return true;
        case SYM_GEN_keyed_cleanse_biggest_first_1407: this->f_keyed_cleanse_biggest_first = val; return true;
        case SYM_GEN__emptyGrid_1408: this->f__emptyGrid = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreContext::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_set_drawseq_enabled_1409: return true;
        case SYM_GEN_lib_fires_tick_1410: return true;
        case SYM_GEN_set_custom_health_multiplier_1411: return true;
        case gd::SYM__init: return true;
        case gd::SYM_set_state: return true;
        case SYM_GEN__newDamageSource_1412: return true;
        case SYM_GEN_getCharacterFromId_1413: return true;
        case SYM_GEN_otherCharacter_1414: return true;
        case SYM_GEN_advancePhysicsFrame_1415: return true;
        case SYM_GEN_callDelayed_1416: return true;
        case SYM_GEN__flushTimed_1417: return true;
        case SYM_GEN_defer_1418: return true;
        case SYM_GEN_hasDeferred_1419: return true;
        case SYM_GEN_flushDeferred_1420: return true;
        case SYM_GEN_connectIdleFrameOnce_1421: return true;
        case SYM_GEN_flushIdleFrameCalls_1422: return true;
        case SYM_GEN_emptyGrid_1423: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreContext::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_set_drawseq_enabled_1409: out = fn_set_drawseq_enabled(args, argc); return true;
        case SYM_GEN_lib_fires_tick_1410: out = fn_lib_fires_tick(args, argc); return true;
        case SYM_GEN_set_custom_health_multiplier_1411: out = fn_set_custom_health_multiplier(args, argc); return true;
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case gd::SYM_set_state: out = fn_set_state(args, argc); return true;
        case SYM_GEN__newDamageSource_1412: out = fn__newDamageSource(args, argc); return true;
        case SYM_GEN_getCharacterFromId_1413: out = fn_getCharacterFromId(args, argc); return true;
        case SYM_GEN_otherCharacter_1414: out = fn_otherCharacter(args, argc); return true;
        case SYM_GEN_advancePhysicsFrame_1415: out = fn_advancePhysicsFrame(args, argc); return true;
        case SYM_GEN_callDelayed_1416: out = fn_callDelayed(args, argc); return true;
        case SYM_GEN__flushTimed_1417: out = fn__flushTimed(args, argc); return true;
        case SYM_GEN_defer_1418: out = fn_defer(args, argc); return true;
        case SYM_GEN_hasDeferred_1419: out = fn_hasDeferred(args, argc); return true;
        case SYM_GEN_flushDeferred_1420: out = fn_flushDeferred(args, argc); return true;
        case SYM_GEN_connectIdleFrameOnce_1421: out = fn_connectIdleFrameOnce(args, argc); return true;
        case SYM_GEN_flushIdleFrameCalls_1422: out = fn_flushIdleFrameCalls(args, argc); return true;
        case SYM_GEN_emptyGrid_1423: out = fn_emptyGrid(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreContext::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return false;
}
gd::GdVal Gd__gd_core__CoreContext::fn_set_drawseq_enabled(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_v = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_v = gd::gd_coerce_bool(lv_v);
    this->f__drawseq_enabled = lv_v;
    gd::set_prop(gd_ctx, this->f_rng, SYM_GEN_draw_seq_1634, (gd::gd_truth(lv_v) ? (gd::GdVal::from_int(0LL)) : (gd::gd_neg(gd::GdVal::from_int(1LL)))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_lib_fires_tick(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    if (gd::gd_truth(gd::call_method(gd_ctx, this->f_lib_fires, gd::SYM_empty, nullptr, 0))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_keep = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    gd::GdVal lv_due = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1126 = gd::gd_iter_seq(gd_ctx.arena, this->f_lib_fires);
        gd::GdArr* _t1127 = (_t1126.kind == gd::GdVal::Kind::Arr) ? _t1126.arr : nullptr;
        uint32_t _len__t1128 = _t1127 ? _t1127->len : 0u;
        for (uint32_t _t1128 = 0; _t1128 < _len__t1128; ++_t1128) {
            gd::GdVal lv_e = _t1127->data[_t1128];
            { gd::GdVal _t1129 = lv_e; gd::GdVal _t1130 = gd::GdVal::from_int(0LL); gd::set_index(gd_ctx, _t1129, _t1130, gd::gd_sub(gd::get_index(gd_ctx, lv_e, gd::GdVal::from_int(0LL)), lv_delta)); }
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_index(gd_ctx, lv_e, gd::GdVal::from_int(0LL)), gd::GdVal::from_float(0.0))))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_e}; return gd::call_method(gd_ctx, lv_keep, gd::SYM_push_back, _ca, 1); })();
            }
            else if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_fight_ended)))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_e}; return gd::call_method(gd_ctx, lv_due, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    this->f_lib_fires = lv_keep;
    {
        gd::GdVal _t1131 = gd::gd_iter_seq(gd_ctx.arena, lv_due);
        gd::GdArr* _t1132 = (_t1131.kind == gd::GdVal::Kind::Arr) ? _t1131.arr : nullptr;
        uint32_t _len__t1133 = _t1132 ? _t1132->len : 0u;
        for (uint32_t _t1133 = 0; _t1133 < _len__t1133; ++_t1133) {
            gd::GdVal lv_e = _t1132->data[_t1133];
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_coerce_float(gd::get_index(gd_ctx, lv_e, gd::GdVal::from_int(1LL))), gd::gd_coerce_float(gd::get_index(gd_ctx, lv_e, gd::GdVal::from_int(2LL)))}; return gd::call_method(gd_ctx, this->f_rng, gd::SYM_randf_range, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_set_custom_health_multiplier(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_v = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_v = gd::gd_coerce_float(lv_v);
    this->f_custom_health_multiplier = lv_v;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn__init(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__seed = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv__seed = gd::gd_coerce_int(lv__seed);
    gd::GdVal lv__hooks = (_argc > 1) ? _args[1] : (gd::GdVal::null());
    this->f_rng = ([&]() { gd::GdVal _ca[] = {lv__seed}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreRng), gd::SYM_new, _ca, 1); })();
    this->f_util = ([&]() { gd::GdVal _ca[] = {this->f_rng}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), gd::SYM_new, _ca, 1); })();
    gd::set_prop(gd_ctx, this->f_util, SYM_GEN__ctx_1321, gd::GdVal::from_obj(this));
    this->f_hooks = (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv__hooks, gd::GdVal::null()))) ? (lv__hooks) : (gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreHooks), gd::SYM_new, nullptr, 0)));
    this->f_bus = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreEventBus), gd::SYM_new, nullptr, 0);
    gd::set_prop(gd_ctx, this->f_bus, SYM_GEN__ctx_1321, gd::GdVal::from_obj(this));
    this->f_combat_log = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCombatLog), gd::SYM_new, nullptr, 0);
    gd::set_prop(gd_ctx, this->f_combat_log, SYM_GEN__ctx_1321, gd::GdVal::from_obj(this));
    this->f_item_book = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreItemBook), gd::SYM_new, nullptr, 0);
    gd::set_prop(gd_ctx, this->f_item_book, SYM_GEN__ctx_1321, gd::GdVal::from_obj(this));
    this->f_stealLifeDamageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_851), SYM_GEN_Effect_2558), gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_effectFlags_1446)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__newDamageSource_1412, _ca, 3); })();
    this->f_unhealingDamageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_851), SYM_GEN_Unhealing_2695), gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_unhealingFlags_1447)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__newDamageSource_1412, _ca, 3); })();
    this->f_fatigueDamageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_851), SYM_GEN_Fatigue_2687), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Flags_1472), SYM_GEN_CanBeBlocked_2755)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__newDamageSource_1412, _ca, 3); })();
    this->f_event_type_keys = ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362)}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_invertDictionary_1704, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_set_state(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_state = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_state = gd::gd_coerce_int(lv_state);
    (void)([&]() { gd::GdVal _ca[] = {lv_state}; return gd::call_method(gd_ctx, this->f_rng, gd::SYM_set_state, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn__newDamageSource(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_origin = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_type = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    gd::GdVal lv_flags = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_flags = gd::gd_coerce_int(lv_flags);
    gd::GdVal lv_src = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0);
    gd::set_prop(gd_ctx, lv_src, SYM_GEN__rng_1455, this->f_rng);
    (void)([&]() { gd::GdVal _ca[] = {lv_origin, lv_type}; return gd::call_method(gd_ctx, lv_src, SYM_GEN_init_1017, _ca, 2); })();
    gd::set_prop(gd_ctx, lv_src, SYM_GEN_flags_1454, lv_flags);
    return lv_src;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_getCharacterFromId(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_playerId = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_playerId = gd::gd_coerce_int(lv_playerId);
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_playerId, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCharacter), SYM_GEN_ID_1275), SYM_GEN_PLAYER_2539)))) ? (this->f_player) : (this->f_opponent));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_otherCharacter(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_character = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_character, this->f_player))) ? (this->f_opponent) : (this->f_player));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_advancePhysicsFrame(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : (Gd__gd_core__CoreContext::get_static_const_or_enum(gd_ctx, SYM_GEN_PHYSICS_DELTA_1371));
    lv_delta = gd::gd_coerce_float(lv_delta);
    this->f_frame_counter = gd::gd_add(gd_ctx, this->f_frame_counter, gd::GdVal::from_int(1LL));
    this->f_time = gd::gd_add(gd_ctx, this->f_time, lv_delta);
    this->f_combat_time = this->f_combat_time;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_callDelayed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_obj = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_methodName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_delay = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv_delay = gd::gd_coerce_float(lv_delay);
    gd::GdVal lv_binds = (_argc > 3) ? _args[3] : (gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_obj, gd::GdVal::null())))) {
        return gd::GdVal::null();
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_obj, lv_methodName, lv_delay, lv_binds}))}; return gd::call_method(gd_ctx, this->f__timed, gd::SYM_push_back, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn__flushTimed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::call_method(gd_ctx, this->f__timed, gd::SYM_empty, nullptr, 0))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_due = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    gd::GdVal lv_keep = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1134 = gd::gd_iter_seq(gd_ctx.arena, this->f__timed);
        gd::GdArr* _t1135 = (_t1134.kind == gd::GdVal::Kind::Arr) ? _t1134.arr : nullptr;
        uint32_t _len__t1136 = _t1135 ? _t1135->len : 0u;
        for (uint32_t _t1136 = 0; _t1136 < _len__t1136; ++_t1136) {
            gd::GdVal lv_call = _t1135->data[_t1136];
            { gd::GdVal _t1137 = lv_call; gd::GdVal _t1138 = gd::GdVal::from_int(2LL); gd::set_index(gd_ctx, _t1137, _t1138, gd::gd_sub(gd::get_index(gd_ctx, lv_call, gd::GdVal::from_int(2LL)), Gd__gd_core__CoreContext::get_static_const_or_enum(gd_ctx, SYM_GEN_PHYSICS_DELTA_1371))); }
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_index(gd_ctx, lv_call, gd::GdVal::from_int(2LL)), gd::GdVal::from_float(0.0))))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_call}; return gd::call_method(gd_ctx, lv_keep, gd::SYM_push_back, _ca, 1); })();
            }
            else if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_fight_ended)))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_call}; return gd::call_method(gd_ctx, lv_due, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_due, gd::SYM_empty, nullptr, 0))) {
        this->f__timed = lv_keep;
        return gd::GdVal::null();
    }
    this->f__timed = lv_keep;
    {
        gd::GdVal _t1139 = gd::gd_iter_seq(gd_ctx.arena, lv_due);
        gd::GdArr* _t1140 = (_t1139.kind == gd::GdVal::Kind::Arr) ? _t1139.arr : nullptr;
        uint32_t _len__t1141 = _t1140 ? _t1140->len : 0u;
        for (uint32_t _t1141 = 0; _t1141 < _len__t1141; ++_t1141) {
            gd::GdVal lv_call = _t1140->data[_t1141];
            (void)([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, lv_call, gd::GdVal::from_int(1LL)), gd::get_index(gd_ctx, lv_call, gd::GdVal::from_int(3LL))}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, lv_call, gd::GdVal::from_int(0LL)), gd::SYM_callv, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_defer(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_obj = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_methodName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_args = (_argc > 2) ? _args[2] : (gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_obj, lv_methodName, lv_args}))}; return gd::call_method(gd_ctx, this->f__deferred, gd::SYM_push_back, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_hasDeferred(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, this->f__deferred, gd::SYM_empty, nullptr, 0)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_flushDeferred(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_deferred_flush_enabled)))) {
        return gd::GdVal::null();
    }
    while (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, this->f__deferred, gd::SYM_empty, nullptr, 0))))) {
        gd::GdVal lv_batch = this->f__deferred;
        this->f__deferred = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
        {
            gd::GdVal _t1142 = gd::gd_iter_seq(gd_ctx.arena, lv_batch);
            gd::GdArr* _t1143 = (_t1142.kind == gd::GdVal::Kind::Arr) ? _t1142.arr : nullptr;
            uint32_t _len__t1144 = _t1143 ? _t1143->len : 0u;
            for (uint32_t _t1144 = 0; _t1144 < _len__t1144; ++_t1144) {
                gd::GdVal lv_call = _t1143->data[_t1144];
                gd::GdVal lv_obj = gd::get_index(gd_ctx, lv_call, gd::GdVal::from_int(0LL));
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_obj, gd::GdVal::null())))) {
                    (void)([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, lv_call, gd::GdVal::from_int(1LL)), gd::get_index(gd_ctx, lv_call, gd::GdVal::from_int(2LL))}; return gd::call_method(gd_ctx, lv_obj, gd::SYM_callv, _ca, 2); })();
                }
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_connectIdleFrameOnce(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_obj = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_methodName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_args = (_argc > 2) ? _args[2] : (gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})));
    {
        gd::GdVal _t1145 = gd::gd_iter_seq(gd_ctx.arena, this->f__idle_frame_calls);
        gd::GdArr* _t1146 = (_t1145.kind == gd::GdVal::Kind::Arr) ? _t1145.arr : nullptr;
        uint32_t _len__t1147 = _t1146 ? _t1146->len : 0u;
        for (uint32_t _t1147 = 0; _t1147 < _len__t1147; ++_t1147) {
            gd::GdVal lv_call = _t1146->data[_t1147];
            if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_index(gd_ctx, lv_call, gd::GdVal::from_int(0LL)), lv_obj))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_index(gd_ctx, lv_call, gd::GdVal::from_int(1LL)), lv_methodName)))) : gd::GdVal::from_bool(false)))) {
                return gd::GdVal::null();
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_obj, lv_methodName, lv_args}))}; return gd::call_method(gd_ctx, this->f__idle_frame_calls, gd::SYM_push_back, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_flushIdleFrameCalls(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_deferred_flush_enabled)))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_batch = this->f__idle_frame_calls;
    this->f__idle_frame_calls = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    if (gd::gd_truth(this->f_fight_ended)) {
        return gd::GdVal::null();
    }
    {
        gd::GdVal _t1148 = gd::gd_iter_seq(gd_ctx.arena, lv_batch);
        gd::GdArr* _t1149 = (_t1148.kind == gd::GdVal::Kind::Arr) ? _t1148.arr : nullptr;
        uint32_t _len__t1150 = _t1149 ? _t1149->len : 0u;
        for (uint32_t _t1150 = 0; _t1150 < _len__t1150; ++_t1150) {
            gd::GdVal lv_call = _t1149->data[_t1150];
            gd::GdVal lv_obj = gd::get_index(gd_ctx, lv_call, gd::GdVal::from_int(0LL));
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_obj, gd::GdVal::null())))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, lv_call, gd::GdVal::from_int(1LL)), gd::get_index(gd_ctx, lv_call, gd::GdVal::from_int(2LL))}; return gd::call_method(gd_ctx, lv_obj, gd::SYM_callv, _ca, 2); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_emptyGrid(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f__emptyGrid, gd::GdVal::null())))) {
        this->f__emptyGrid = ([&]() { gd::GdVal _ca[] = {gd::GdVal::null()}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreGrid), gd::SYM_new, _ca, 1); })();
    }
    return this->f__emptyGrid;
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreContext(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__CoreContext>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__CoreContext = {CLS_Gd__gd_core__CoreContext, "CoreContext", "res://gd_core/CoreContext.gd", nullptr, false, _alloc_Gd__gd_core__CoreContext, &Gd__gd_core__CoreContext::get_static_prop_fn, &Gd__gd_core__CoreContext::call_static_fn};

void Gd__gd_core__CoreUtil__INNER__DictSorter::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_dict = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
}
const gd::GdClassMeta* Gd__gd_core__CoreUtil__INNER__DictSorter::meta() const { return &META_Gd__gd_core__CoreUtil__INNER__DictSorter; }
gd::GdVal Gd__gd_core__CoreUtil__INNER__DictSorter::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreUtil__INNER__DictSorter::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreUtil__INNER__DictSorter::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_dict_1713: out = this->f_dict; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreUtil__INNER__DictSorter::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_dict_1713: this->f_dict = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreUtil__INNER__DictSorter::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_sort_1714: return true;
        case SYM_GEN_sort_reverse_1715: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreUtil__INNER__DictSorter::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_sort_1714: out = fn_sort(args, argc); return true;
        case SYM_GEN_sort_reverse_1715: out = fn_sort_reverse(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreUtil__INNER__DictSorter::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return false;
}
gd::GdVal Gd__gd_core__CoreUtil__INNER__DictSorter::fn__init(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__dict = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_dict = lv__dict;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil__INNER__DictSorter::fn_sort(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_key1 = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_key2 = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return gd::GdVal::from_bool(gd::gd_gt(gd::get_index(gd_ctx, this->f_dict, lv_key1), gd::get_index(gd_ctx, this->f_dict, lv_key2)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreUtil__INNER__DictSorter::fn_sort_reverse(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_key1 = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_key2 = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return gd::GdVal::from_bool(gd::gd_lt(gd::get_index(gd_ctx, this->f_dict, lv_key1), gd::get_index(gd_ctx, this->f_dict, lv_key2)));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreUtil__INNER__DictSorter(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__CoreUtil__INNER__DictSorter>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__CoreUtil__INNER__DictSorter = {CLS_Gd__gd_core__CoreUtil__INNER__DictSorter, "DictSorter", "", nullptr, false, _alloc_Gd__gd_core__CoreUtil__INNER__DictSorter, &Gd__gd_core__CoreUtil__INNER__DictSorter::get_static_prop_fn, &Gd__gd_core__CoreUtil__INNER__DictSorter::call_static_fn};

void Gd__gd_core__DragonEgg::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_hatchParticles = gd::GdVal::null();
    this->f_firePulse = gd::GdVal::null();
    this->f_whelpName = gd::GdVal::null();
    this->f_roundsToHatch = gd::GdVal::null();
    this->f_reflectionStacks = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__DragonEgg::meta() const { return &META_Gd__gd_core__DragonEgg; }
gd::GdVal Gd__gd_core__DragonEgg::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__DragonEgg::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__DragonEgg::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_hatchParticles_1764: out = this->f_hatchParticles; return true;
        case SYM_GEN_firePulse_1765: out = this->f_firePulse; return true;
        case SYM_GEN_whelpName_1766: out = this->f_whelpName; return true;
        case SYM_GEN_roundsToHatch_1767: out = this->f_roundsToHatch; return true;
        case SYM_GEN_reflectionStacks_1768: out = this->f_reflectionStacks; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__DragonEgg::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_hatchParticles_1764: this->f_hatchParticles = val; return true;
        case SYM_GEN_firePulse_1765: this->f_firePulse = val; return true;
        case SYM_GEN_whelpName_1766: this->f_whelpName = val; return true;
        case SYM_GEN_roundsToHatch_1767: this->f_roundsToHatch = val; return true;
        case SYM_GEN_reflectionStacks_1768: this->f_reflectionStacks = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__DragonEgg::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getData_634: return true;
        case SYM_GEN_setData_635: return true;
        case SYM_GEN_updateEgg_1769: return true;
        case SYM_GEN_isNextToNest_1770: return true;
        case SYM_GEN_readyToTransform_749: return true;
        case SYM_GEN_canHatch_1771: return true;
        case SYM_GEN_shopEntered_741: return true;
        case SYM_GEN_startHatching_1772: return true;
        case SYM_GEN_hatch_1773: return true;
        case SYM_GEN_hatch_deferred_1774: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__DragonEgg::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getData_634: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_635: out = fn_setData(args, argc); return true;
        case SYM_GEN_updateEgg_1769: out = fn_updateEgg(args, argc); return true;
        case SYM_GEN_isNextToNest_1770: out = fn_isNextToNest(args, argc); return true;
        case SYM_GEN_readyToTransform_749: out = fn_readyToTransform(args, argc); return true;
        case SYM_GEN_canHatch_1771: out = fn_canHatch(args, argc); return true;
        case SYM_GEN_shopEntered_741: out = fn_shopEntered(args, argc); return true;
        case SYM_GEN_startHatching_1772: out = fn_startHatching(args, argc); return true;
        case SYM_GEN_hatch_1773: out = fn_hatch(args, argc); return true;
        case SYM_GEN_hatch_deferred_1774: out = fn_hatch_deferred(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__DragonEgg::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__DragonEgg::fn_getData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_roundsToHatch;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DragonEgg::fn_setData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_data = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_roundsToHatch = lv_data;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateEgg_1769, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DragonEgg::fn_updateEgg(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canHatch_1771, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.0), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_789, _ca, 2); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_sub(gd::GdVal::from_float(1.0), gd::gd_div(gd_ctx, this->f_roundsToHatch, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0))), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_789, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DragonEgg::fn_isNextToNest(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_placed)) {
        {
            gd::GdVal _t1151 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1510, nullptr, 0));
            gd::GdArr* _t1152 = (_t1151.kind == gd::GdVal::Kind::Arr) ? _t1151.arr : nullptr;
            uint32_t _len__t1153 = _t1152 ? _t1152->len : 0u;
            for (uint32_t _t1153 = 0; _t1153 < _len__t1153; ++_t1153) {
                gd::GdVal lv_item = _t1152->data[_t1153];
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, lv_item, SYM_GEN_getName_232, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Dragon Nest", 11u)))))) {
                    return gd::gd_in(gd::GdVal::from_obj(this), gd::call_method(gd_ctx, lv_item, SYM_GEN_getAffectedItems_418, nullptr, 0));
                }
            }
        }
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DragonEgg::fn_readyToTransform(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canHatch_1771, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DragonEgg::fn_canHatch(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_roundsToHatch, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_roundsToHatch, gd::GdVal::from_int(1LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isNextToNest_1770, nullptr, 0))) : gd::GdVal::from_bool(false)))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DragonEgg::fn_shopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_craft = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_craft = gd::gd_coerce_bool(lv_craft);
    (void)([&]() { gd::GdVal _ca[] = {lv_craft}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_shopEntered_741, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DragonEgg::fn_startHatching(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "hatch", 5u)), gd::gd_sub(Gd__gd_core__DragonEgg::get_static_const_or_enum(gd_ctx, SYM_GEN_TRANSFORMATION_DUR_602), gd::GdVal::from_float(0.1))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_callDelayed_1416, _ca, 3); })();
    {
        gd::GdVal _t1154 = gd::gd_iter_seq(gd_ctx.arena, this->f_shadows);
        gd::GdArr* _t1155 = (_t1154.kind == gd::GdVal::Kind::Arr) ? _t1154.arr : nullptr;
        uint32_t _len__t1156 = _t1155 ? _t1155->len : 0u;
        for (uint32_t _t1156 = 0; _t1156 < _len__t1156; ++_t1156) {
            gd::GdVal lv_shadow = _t1155->data[_t1156];
            gd::set_prop(gd_ctx, lv_shadow, SYM_GEN_offset_512, gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(138LL))).as_float()));
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DragonEgg::fn_hatch(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "hatch_deferred", 14u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_defer_1418, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DragonEgg::fn_hatch_deferred(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DragonEgg::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_roundsToHatch = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateEgg_1769, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__DragonEgg(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__DragonEgg>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__DragonEgg = {CLS_Gd__gd_core__DragonEgg, "DragonEgg", "res://gd_core/DragonEgg.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__DragonEgg, &Gd__gd_core__DragonEgg::get_static_prop_fn, &Gd__gd_core__DragonEgg::call_static_fn};

void Gd__gd_core__HealingHerbs::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__HealingHerbs::meta() const { return &META_Gd__gd_core__HealingHerbs; }
gd::GdVal Gd__gd_core__HealingHerbs::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__HealingHerbs::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__HealingHerbs::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__HealingHerbs::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__HealingHerbs::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__HealingHerbs::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__HealingHerbs::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__HealingHerbs::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_212, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_379, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HealingHerbs::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__HealingHerbs(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__HealingHerbs>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__HealingHerbs = {CLS_Gd__gd_core__HealingHerbs, "HealingHerbs", "res://gd_core/HealingHerbs.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__HealingHerbs, &Gd__gd_core__HealingHerbs::get_static_prop_fn, &Gd__gd_core__HealingHerbs::call_static_fn};

void Gd__gd_core__LightGoobert::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Goobert::init_fields(gd_ctx);
    this->f_particleTimer = gd::GdVal::null();
    this->f_activationParticles = gd::GdVal::null();
    this->f_blindAmount = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__LightGoobert::meta() const { return &META_Gd__gd_core__LightGoobert; }
gd::GdVal Gd__gd_core__LightGoobert::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__LightGoobert::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__LightGoobert::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_particleTimer_995: out = this->f_particleTimer; return true;
        case SYM_GEN_activationParticles_908: out = this->f_activationParticles; return true;
        case SYM_GEN_blindAmount_1813: out = this->f_blindAmount; return true;
        default: break;
    }
    return Gd__gd_core__Goobert::get_prop(prop, out);
}
bool Gd__gd_core__LightGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_particleTimer_995: this->f_particleTimer = val; return true;
        case SYM_GEN_activationParticles_908: this->f_activationParticles = val; return true;
        case SYM_GEN_blindAmount_1813: this->f_blindAmount = val; return true;
        default: break;
    }
    return Gd__gd_core__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__LightGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onCombatEnd_130: return true;
        case SYM_GEN_onParticleTimeout_996: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Goobert::has_own_method(m);
}
bool Gd__gd_core__LightGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onCombatEnd_130: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onParticleTimeout_996: out = fn_onParticleTimeout(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__LightGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__LightGoobert::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LightGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, nullptr, 0);
    gd::GdVal lv_duration = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_blind", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1362), SYM_GEN_Blind_2567), this->f_blindAmount, lv_duration}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacksTemporary_200, _ca, 4); })();
    (void)gd::call_method(gd_ctx, this->f_particleTimer, SYM_GEN_stop_1684, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {lv_duration}; return gd::call_method(gd_ctx, this->f_particleTimer, SYM_GEN_start_1683, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LightGoobert::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_particleTimer, SYM_GEN_stop_1684, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LightGoobert::fn_onParticleTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LightGoobert::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LightGoobert::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv_active)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LightGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_particleTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "ParticleTimer", 13u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onParticleTimeout", 17u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_133, _ca, 3); })();
    this->f_blindAmount = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__LightGoobert(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__LightGoobert>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__LightGoobert = {CLS_Gd__gd_core__LightGoobert, "LightGoobert", "res://gd_core/LightGoobert.gd", &META_Gd__gd_core__Goobert, false, _alloc_Gd__gd_core__LightGoobert, &Gd__gd_core__LightGoobert::get_static_prop_fn, &Gd__gd_core__LightGoobert::call_static_fn};

void Gd__gd_core__PestilenceFlask::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Potion::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__PestilenceFlask::meta() const { return &META_Gd__gd_core__PestilenceFlask; }
gd::GdVal Gd__gd_core__PestilenceFlask::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Potion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__PestilenceFlask::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__PestilenceFlask::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Potion::get_prop(prop, out);
}
bool Gd__gd_core__PestilenceFlask::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Potion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__PestilenceFlask::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1753: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onOpponentHeal_1861: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Potion::has_own_method(m);
}
bool Gd__gd_core__PestilenceFlask::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1753: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onOpponentHeal_1861: out = fn_onOpponentHeal(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Potion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__PestilenceFlask::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Potion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__PestilenceFlask::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_209, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_selfInflictPoison_210, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PestilenceFlask::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_healed", 16u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onOpponentHeal", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PestilenceFlask::fn_onOpponentHeal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_919, nullptr, 0))) {
        return gd::GdVal::null();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drink_1751, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_triggerPotion_1754, _ca, 1); })();
    gd::GdVal lv_affected = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_affected, gd::SYM_empty, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL)), SYM_GEN_triggerPotion_1754, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::get_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL)), SYM_GEN_miniActivate_468, nullptr, 0);
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PestilenceFlask::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Potion::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__PestilenceFlask(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__PestilenceFlask>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__PestilenceFlask = {CLS_Gd__gd_core__PestilenceFlask, "PestilenceFlask", "res://gd_core/PestilenceFlask.gd", &META_Gd__gd_core__Potion, false, _alloc_Gd__gd_core__PestilenceFlask, &Gd__gd_core__PestilenceFlask::get_static_prop_fn, &Gd__gd_core__PestilenceFlask::call_static_fn};

void Gd__gd_core__RangerBag::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Bag::init_fields(gd_ctx);
    this->f_itemsInside = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__RangerBag::meta() const { return &META_Gd__gd_core__RangerBag; }
gd::GdVal Gd__gd_core__RangerBag::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Bag::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__RangerBag::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__RangerBag::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_itemsInside_1874: out = this->f_itemsInside; return true;
        default: break;
    }
    return Gd__gd_core__Bag::get_prop(prop, out);
}
bool Gd__gd_core__RangerBag::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_itemsInside_1874: this->f_itemsInside = val; return true;
        default: break;
    }
    return Gd__gd_core__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__RangerBag::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onLuckyChanged_897: return true;
        case SYM_GEN_canApplyEffect_916: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Bag::has_own_method(m);
}
bool Gd__gd_core__RangerBag::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onLuckyChanged_897: out = fn_onLuckyChanged(args, argc); return true;
        case SYM_GEN_canApplyEffect_916: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__RangerBag::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__RangerBag::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_itemsInside = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_920, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_920, nullptr, 0), gd::SYM_empty, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_lucky_changed", 23u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onLuckyChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    }
    {
        gd::GdVal _t1157 = gd::gd_iter_seq(gd_ctx.arena, this->f_itemsInside);
        gd::GdArr* _t1158 = (_t1157.kind == gd::GdVal::Kind::Arr) ? _t1157.arr : nullptr;
        uint32_t _len__t1159 = _t1158 ? _t1158->len : 0u;
        for (uint32_t _t1159 = 0; _t1159 < _len__t1159; ++_t1159) {
            gd::GdVal lv_item = _t1158->data[_t1159];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeCritChancePercent_179, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RangerBag::fn_onLuckyChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_change = gd::gd_mul(lv_amount, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_170, nullptr, 0));
    {
        gd::GdVal _t1160 = gd::gd_iter_seq(gd_ctx.arena, this->f_itemsInside);
        gd::GdArr* _t1161 = (_t1160.kind == gd::GdVal::Kind::Arr) ? _t1160.arr : nullptr;
        uint32_t _len__t1162 = _t1161 ? _t1161->len : 0u;
        for (uint32_t _t1162 = 0; _t1162 < _len__t1162; ++_t1162) {
            gd::GdVal lv_item = _t1161->data[_t1162];
            (void)([&]() { gd::GdVal _ca[] = {lv_change}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeCritChancePercent_179, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RangerBag::fn_canApplyEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_toItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_toItem, SYM_GEN_canDamage_87, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RangerBag::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Bag::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__RangerBag(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__RangerBag>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__RangerBag = {CLS_Gd__gd_core__RangerBag, "RangerBag", "res://gd_core/RangerBag.gd", &META_Gd__gd_core__Bag, false, _alloc_Gd__gd_core__RangerBag, &Gd__gd_core__RangerBag::get_static_prop_fn, &Gd__gd_core__RangerBag::call_static_fn};

void Gd__gd_core__StoneSkinPotion::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Potion::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__StoneSkinPotion::meta() const { return &META_Gd__gd_core__StoneSkinPotion; }
gd::GdVal Gd__gd_core__StoneSkinPotion::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Potion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__StoneSkinPotion::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__StoneSkinPotion::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Potion::get_prop(prop, out);
}
bool Gd__gd_core__StoneSkinPotion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Potion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__StoneSkinPotion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1753: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onBlockChanged_1890: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Potion::has_own_method(m);
}
bool Gd__gd_core__StoneSkinPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1753: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onBlockChanged_1890: out = fn_onBlockChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Potion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__StoneSkinPotion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Potion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__StoneSkinPotion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_202, nullptr, 0), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_healthToBlock_326, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StoneSkinPotion::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_block_changed", 23u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBlockChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StoneSkinPotion::fn_onBlockChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_919, nullptr, 0))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getBlock_202, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consumePotion_1752, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StoneSkinPotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Potion::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__StoneSkinPotion(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__StoneSkinPotion>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__StoneSkinPotion = {CLS_Gd__gd_core__StoneSkinPotion, "StoneSkinPotion", "res://gd_core/StoneSkinPotion.gd", &META_Gd__gd_core__Potion, false, _alloc_Gd__gd_core__StoneSkinPotion, &Gd__gd_core__StoneSkinPotion::get_static_prop_fn, &Gd__gd_core__StoneSkinPotion::call_static_fn};

void Gd__gd_core__VampiricGloves::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_inactiveTexture = gd::GdVal::null();
    this->f_activationParticles = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__VampiricGloves::meta() const { return &META_Gd__gd_core__VampiricGloves; }
gd::GdVal Gd__gd_core__VampiricGloves::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__VampiricGloves::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__VampiricGloves::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_inactiveTexture_1906: out = this->f_inactiveTexture; return true;
        case SYM_GEN_activationParticles_908: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__VampiricGloves::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_inactiveTexture_1906: this->f_inactiveTexture = val; return true;
        case SYM_GEN_activationParticles_908: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__VampiricGloves::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__VampiricGloves::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__VampiricGloves::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__VampiricGloves::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_93, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__VampiricGloves::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__VampiricGloves::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_208, _ca, 1); })();
    gd::GdVal lv_bonusSpeed = gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0), gd::GdVal::from_int(100LL));
    {
        gd::GdVal _t1163 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1164 = (_t1163.kind == gd::GdVal::Kind::Arr) ? _t1163.arr : nullptr;
        uint32_t _len__t1165 = _t1164 ? _t1164->len : 0u;
        for (uint32_t _t1165 = 0; _t1165 < _len__t1165; ++_t1165) {
            gd::GdVal lv_item = _t1164->data[_t1165];
            (void)([&]() { gd::GdVal _ca[] = {lv_bonusSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_271, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_143, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__VampiricGloves::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__VampiricGloves::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv_active)) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateShadowTexture_785, nullptr, 0);
    }
    else {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateShadowTexture_785, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__VampiricGloves::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__VampiricGloves(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__VampiricGloves>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__VampiricGloves = {CLS_Gd__gd_core__VampiricGloves, "VampiricGloves", "res://gd_core/VampiricGloves.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__VampiricGloves, &Gd__gd_core__VampiricGloves::get_static_prop_fn, &Gd__gd_core__VampiricGloves::call_static_fn};

static const gd::GdEnum::KV _ekv_Gd__gd_core_items__Bag_BagTiles[] = {{"Default", 2LL}, {"CanAdd", 6LL}, {"CannotAdd", 5LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__Bag_BagTiles = {"BagTiles", _ekv_Gd__gd_core_items__Bag_BagTiles, 3u};
void Gd__gd_core_items__Bag::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_bagTilemapPosition = gd::GdVal::null();
    this->f_cachedAffectedInsideItems = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_cachedInsideItems = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_bagTilemap = gd::GdVal::null();
    this->f_border = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Bag::meta() const { return &META_Gd__gd_core_items__Bag; }
gd::GdVal Gd__gd_core_items__Bag::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_BagTiles_929: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Bag_BagTiles);
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Bag::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Bag::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_bagTilemapPosition_910: out = this->f_bagTilemapPosition; return true;
        case SYM_GEN_cachedAffectedInsideItems_911: out = this->f_cachedAffectedInsideItems; return true;
        case SYM_GEN_cachedInsideItems_912: out = this->f_cachedInsideItems; return true;
        case SYM_GEN_bagTilemap_913: out = this->f_bagTilemap; return true;
        case SYM_GEN_border_914: out = this->f_border; return true;
        case SYM_GEN_BagTiles_929: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Bag_BagTiles); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Bag::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bagTilemapPosition_910: this->f_bagTilemapPosition = val; return true;
        case SYM_GEN_cachedAffectedInsideItems_911: this->f_cachedAffectedInsideItems = val; return true;
        case SYM_GEN_cachedInsideItems_912: this->f_cachedInsideItems = val; return true;
        case SYM_GEN_bagTilemap_913: this->f_bagTilemap = val; return true;
        case SYM_GEN_border_914: this->f_border = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Bag::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getHoverPriority_688: return true;
        case SYM_GEN_isBag_81: return true;
        case SYM_GEN_showBagBorderForItem_915: return true;
        case SYM_GEN_canApplyEffect_916: return true;
        case SYM_GEN_canBePicked_735: return true;
        case SYM_GEN_canBeLocked_817: return true;
        case SYM_GEN_resetZ_448: return true;
        case SYM_GEN_addToInventory_118: return true;
        case SYM_GEN_getBagLayerPriority_917: return true;
        case SYM_GEN_hasBagEffect_918: return true;
        case SYM_GEN__process_678: return true;
        case SYM_GEN_reactToDropResult_718: return true;
        case SYM_GEN_onRemoveFromInventory_416: return true;
        case SYM_GEN_getTopLeftGlobal_651: return true;
        case SYM_GEN_getBottomRightGlobal_652: return true;
        case SYM_GEN_isEmpty_919: return true;
        case SYM_GEN_getItemsInside_920: return true;
        case SYM_GEN_getEmptyCells_921: return true;
        case SYM_GEN_getEmptyGlobalPositions_922: return true;
        case SYM_GEN_getAffectedItemsInside_923: return true;
        case SYM_GEN_previewCanAffect_471: return true;
        case SYM_GEN_prepare_120: return true;
        case SYM_GEN_combatToShop_740: return true;
        case SYM_GEN_getCraftableNeighbors_490: return true;
        case SYM_GEN_onItemAdded_435: return true;
        case SYM_GEN_onAffectedItemInsideAdded_924: return true;
        case SYM_GEN_onItemRemoved_436: return true;
        case SYM_GEN_onAffectedItemInsideRemoved_925: return true;
        case SYM_GEN_pushItemsInsideToStorage_396: return true;
        case SYM_GEN_onDraggedWithParentStart_714: return true;
        case SYM_GEN_onDraggedWithParentEnd_716: return true;
        case SYM_GEN_getNumAffectedInside_926: return true;
        case SYM_GEN_getNumAffectedInside_type_927: return true;
        case SYM_GEN_getBagMultiplicity_928: return true;
        case SYM_GEN_discard_760: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Bag::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getHoverPriority_688: out = fn_getHoverPriority(args, argc); return true;
        case SYM_GEN_isBag_81: out = fn_isBag(args, argc); return true;
        case SYM_GEN_showBagBorderForItem_915: out = fn_showBagBorderForItem(args, argc); return true;
        case SYM_GEN_canApplyEffect_916: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN_canBePicked_735: out = fn_canBePicked(args, argc); return true;
        case SYM_GEN_canBeLocked_817: out = fn_canBeLocked(args, argc); return true;
        case SYM_GEN_resetZ_448: out = fn_resetZ(args, argc); return true;
        case SYM_GEN_addToInventory_118: out = fn_addToInventory(args, argc); return true;
        case SYM_GEN_getBagLayerPriority_917: out = fn_getBagLayerPriority(args, argc); return true;
        case SYM_GEN_hasBagEffect_918: out = fn_hasBagEffect(args, argc); return true;
        case SYM_GEN__process_678: out = fn__process(args, argc); return true;
        case SYM_GEN_reactToDropResult_718: out = fn_reactToDropResult(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_416: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_getTopLeftGlobal_651: out = fn_getTopLeftGlobal(args, argc); return true;
        case SYM_GEN_getBottomRightGlobal_652: out = fn_getBottomRightGlobal(args, argc); return true;
        case SYM_GEN_isEmpty_919: out = fn_isEmpty(args, argc); return true;
        case SYM_GEN_getItemsInside_920: out = fn_getItemsInside(args, argc); return true;
        case SYM_GEN_getEmptyCells_921: out = fn_getEmptyCells(args, argc); return true;
        case SYM_GEN_getEmptyGlobalPositions_922: out = fn_getEmptyGlobalPositions(args, argc); return true;
        case SYM_GEN_getAffectedItemsInside_923: out = fn_getAffectedItemsInside(args, argc); return true;
        case SYM_GEN_previewCanAffect_471: out = fn_previewCanAffect(args, argc); return true;
        case SYM_GEN_prepare_120: out = fn_prepare(args, argc); return true;
        case SYM_GEN_combatToShop_740: out = fn_combatToShop(args, argc); return true;
        case SYM_GEN_getCraftableNeighbors_490: out = fn_getCraftableNeighbors(args, argc); return true;
        case SYM_GEN_onItemAdded_435: out = fn_onItemAdded(args, argc); return true;
        case SYM_GEN_onAffectedItemInsideAdded_924: out = fn_onAffectedItemInsideAdded(args, argc); return true;
        case SYM_GEN_onItemRemoved_436: out = fn_onItemRemoved(args, argc); return true;
        case SYM_GEN_onAffectedItemInsideRemoved_925: out = fn_onAffectedItemInsideRemoved(args, argc); return true;
        case SYM_GEN_pushItemsInsideToStorage_396: out = fn_pushItemsInsideToStorage(args, argc); return true;
        case SYM_GEN_onDraggedWithParentStart_714: out = fn_onDraggedWithParentStart(args, argc); return true;
        case SYM_GEN_onDraggedWithParentEnd_716: out = fn_onDraggedWithParentEnd(args, argc); return true;
        case SYM_GEN_getNumAffectedInside_926: out = fn_getNumAffectedInside(args, argc); return true;
        case SYM_GEN_getNumAffectedInside_type_927: out = fn_getNumAffectedInside_type(args, argc); return true;
        case SYM_GEN_getBagMultiplicity_928: out = fn_getBagMultiplicity(args, argc); return true;
        case SYM_GEN_discard_760: out = fn_discard(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Bag::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Bag::fn_getHoverPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_dragged)) {
        return Gd__gd_core_items__Bag::get_static_const_or_enum(gd_ctx, SYM_GEN_DRAG_PRIORITY_523);
    }
    else {
        return gd::gd_neg(gd::GdVal::from_int(1LL));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_isBag(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_showBagBorderForItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isBag_81, nullptr, 0)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_916, _ca, 1); })())) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_canApplyEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__toItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_canBePicked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_canBeLocked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_resetZ(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_addToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__inventory = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__occupiedCells = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv__placedByPlayer = (_argc > 2) ? _args[2] : gd::GdVal::null();
    lv__placedByPlayer = gd::gd_coerce_bool(lv__placedByPlayer);
    (void)([&]() { gd::GdVal _ca[] = {lv__inventory, lv__occupiedCells, lv__placedByPlayer}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_addToInventory_118, _ca, 3, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_getBagLayerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getRarity_234, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Rarity_858), SYM_GEN_Unique_2756))))) {
        return gd::GdVal::from_int(2LL);
    }
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasBagEffect_918, nullptr, 0))) {
        return gd::GdVal::from_int(1LL);
    }
    return gd::GdVal::from_int(0LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_hasBagEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_ne(this->f_border, gd::GdVal::null()));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn__process(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    if (gd::gd_truth(this->f_dragged)) {
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1280), SYM_GEN_INVENTORY_1089), SYM_GEN_canAddBag_2757, _ca, 1); })())) {
        }
        else {
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_reactToDropResult(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_result = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_result}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_reactToDropResult_718, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_getTopLeftGlobal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_getBottomRightGlobal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_isEmpty(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_920, nullptr, 0), gd::SYM_empty, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_getItemsInside(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, this->f_cachedInsideItems, gd::SYM_empty, nullptr, 0))))) {
        return this->f_cachedInsideItems;
    }
    return ([&]() { gd::GdVal _ca[] = {this->f_occupiedCells}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItemsInCells_1515, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_getEmptyCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_emptyCells = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1166 = gd::gd_iter_seq(gd_ctx.arena, this->f_occupiedCells);
        gd::GdArr* _t1167 = (_t1166.kind == gd::GdVal::Kind::Arr) ? _t1166.arr : nullptr;
        uint32_t _len__t1168 = _t1167 ? _t1167->len : 0u;
        for (uint32_t _t1168 = 0; _t1168 < _len__t1168; ++_t1168) {
            gd::GdVal lv_cell = _t1167->data[_t1168];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_cell}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_isCellEmpty_1512, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_cell}; return gd::call_method(gd_ctx, lv_emptyCells, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    return lv_emptyCells;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_getEmptyGlobalPositions(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_positions = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1169 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getEmptyCells_921, nullptr, 0));
        gd::GdArr* _t1170 = (_t1169.kind == gd::GdVal::Kind::Arr) ? _t1169.arr : nullptr;
        uint32_t _len__t1171 = _t1170 ? _t1170->len : 0u;
        for (uint32_t _t1171 = 0; _t1171 < _len__t1171; ++_t1171) {
            gd::GdVal lv_cell = _t1170->data[_t1171];
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_cell, gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_cellToGlobalPos_2758, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_positions, gd::SYM_push_back, _ca, 1); })();
        }
    }
    return lv_positions;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_getAffectedItemsInside(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_placed)))) {
        return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    }
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, this->f_cachedAffectedInsideItems, gd::SYM_empty, nullptr, 0))))) {
        return this->f_cachedAffectedInsideItems;
    }
    gd::GdVal lv_affected = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1172 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_920, nullptr, 0));
        gd::GdArr* _t1173 = (_t1172.kind == gd::GdVal::Kind::Arr) ? _t1172.arr : nullptr;
        uint32_t _len__t1174 = _t1173 ? _t1173->len : 0u;
        for (uint32_t _t1174 = 0; _t1174 < _len__t1174; ++_t1174) {
            gd::GdVal lv_item = _t1173->data[_t1174];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_916, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, lv_affected, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    return lv_affected;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_previewCanAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_cachedInsideItems = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_920, nullptr, 0);
    {
        gd::GdVal _t1175 = gd::gd_iter_seq(gd_ctx.arena, this->f_cachedInsideItems);
        gd::GdArr* _t1176 = (_t1175.kind == gd::GdVal::Kind::Arr) ? _t1175.arr : nullptr;
        uint32_t _len__t1177 = _t1176 ? _t1176->len : 0u;
        for (uint32_t _t1177 = 0; _t1177 < _len__t1177; ++_t1177) {
            gd::GdVal lv_item = _t1176->data[_t1177];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_916, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, this->f_cachedAffectedInsideItems, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_prepare_120, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_combatToShop(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_cachedAffectedInsideItems, gd::SYM_clear, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_cachedInsideItems, gd::SYM_clear, nullptr, 0);
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_combatToShop_740, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_getCraftableNeighbors(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_craftableItems = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1178 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_920, nullptr, 0));
        gd::GdArr* _t1179 = (_t1178.kind == gd::GdVal::Kind::Arr) ? _t1178.arr : nullptr;
        uint32_t _len__t1180 = _t1179 ? _t1179->len : 0u;
        for (uint32_t _t1180 = 0; _t1180 < _len__t1180; ++_t1180) {
            gd::GdVal lv_item = _t1179->data[_t1180];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isAvailableForCrafting_491, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, lv_craftableItems, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    return lv_craftableItems;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_onItemAdded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onItemAdded_435, _ca, 1, _out); return _out; })();
    if (gd::gd_truth((gd::gd_truth(gd::gd_in(lv_item, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_920, nullptr, 0))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_916, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        if (gd::gd_truth(gd::get_prop(gd_ctx, lv_item, SYM_GEN_placedByPlayer_48))) {
        }
        (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAffectedItemInsideAdded_924, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_onAffectedItemInsideAdded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_onItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onItemRemoved_436, _ca, 1, _out); return _out; })();
    if (gd::gd_truth((gd::gd_truth(gd::gd_in(lv_item, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_920, nullptr, 0))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_916, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAffectedItemInsideRemoved_925, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_onAffectedItemInsideRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_pushItemsInsideToStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_onDraggedWithParentStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_bag = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_bag}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onDraggedWithParentStart_714, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_onDraggedWithParentEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onDraggedWithParentEnd_716, nullptr, 0, _out); return _out; })();
    if (gd::gd_truth(this->f_dragged)) {
    }
    else {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetZ_448, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_getNumAffectedInside(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_num = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t1181 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_923, nullptr, 0));
        gd::GdArr* _t1182 = (_t1181.kind == gd::GdVal::Kind::Arr) ? _t1181.arr : nullptr;
        uint32_t _len__t1183 = _t1182 ? _t1182->len : 0u;
        for (uint32_t _t1183 = 0; _t1183 < _len__t1183; ++_t1183) {
            gd::GdVal lv_item = _t1182->data[_t1183];
            lv_num = gd::gd_add(gd_ctx, lv_num, gd::GdVal::from_int(1LL));
        }
    }
    return lv_num;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_getNumAffectedInside_type(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    gd::GdVal lv_num = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t1184 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_923, nullptr, 0));
        gd::GdArr* _t1185 = (_t1184.kind == gd::GdVal::Kind::Arr) ? _t1184.arr : nullptr;
        uint32_t _len__t1186 = _t1185 ? _t1185->len : 0u;
        for (uint32_t _t1186 = 0; _t1186 < _len__t1186; ++_t1186) {
            gd::GdVal lv_item = _t1185->data[_t1186];
            lv_num = gd::gd_add(gd_ctx, lv_num, ([&]() { gd::GdVal _ca[] = {lv_type}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_getTypeMultiplicity_78, _ca, 1); })());
        }
    }
    return lv_num;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_getBagMultiplicity(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_int(1LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_discard(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_discardGems = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    if (gd::gd_truth(this->f_pooled)) {
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_discardGems}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_discard_760, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_bagTilemapPosition, gd::GdVal::null())))) {
    }
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Bag(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Bag>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Bag = {CLS_Gd__gd_core_items__Bag, "Bag", "res://gd_core_items/Bag.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Bag, &Gd__gd_core_items__Bag::get_static_prop_fn, &Gd__gd_core_items__Bag::call_static_fn};

void Gd__gd_core_items__BurningTorch::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_permDamBonus = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__BurningTorch::meta() const { return &META_Gd__gd_core_items__BurningTorch; }
gd::GdVal Gd__gd_core_items__BurningTorch::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__BurningTorch::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__BurningTorch::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_permDamBonus_993: out = this->f_permDamBonus; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__BurningTorch::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_permDamBonus_993: this->f_permDamBonus = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__BurningTorch::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__BurningTorch::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__BurningTorch::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__BurningTorch::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BurningTorch::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_permDamBonus}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_159, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BurningTorch::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_permDamBonus = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__BurningTorch(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__BurningTorch>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__BurningTorch = {CLS_Gd__gd_core_items__BurningTorch, "BurningTorch", "res://gd_core_items/BurningTorch.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__BurningTorch, &Gd__gd_core_items__BurningTorch::get_static_prop_fn, &Gd__gd_core_items__BurningTorch::call_static_fn};

void Gd__gd_core_items__DeckofCards::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_cards = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_cardActivations = gd::GdVal::from_int(0LL);
    this->f_chainStarted = gd::GdVal::from_bool(false);
    this->f_connector = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__DeckofCards::meta() const { return &META_Gd__gd_core_items__DeckofCards; }
gd::GdVal Gd__gd_core_items__DeckofCards::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__DeckofCards::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__DeckofCards::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_cards_1736: out = this->f_cards; return true;
        case SYM_GEN_cardActivations_1737: out = this->f_cardActivations; return true;
        case SYM_GEN_chainStarted_1738: out = this->f_chainStarted; return true;
        case SYM_GEN_connector_881: out = this->f_connector; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__DeckofCards::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_cards_1736: this->f_cards = val; return true;
        case SYM_GEN_cardActivations_1737: this->f_cardActivations = val; return true;
        case SYM_GEN_chainStarted_1738: this->f_chainStarted = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_connector_881: this->f_connector = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__DeckofCards::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onAddToInventory_417: return true;
        case SYM_GEN_onRemoveFromInventory_416: return true;
        case SYM_GEN_resetChain_1739: return true;
        case SYM_GEN_countDuplicates_1706: return true;
        case SYM_GEN_updateCards_1740: return true;
        case SYM_GEN_onItemAdded_435: return true;
        case SYM_GEN_onItemRemoved_436: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_notifyActivation_1741: return true;
        case SYM_GEN_getGatedDescriptor_952: return true;
        case SYM_GEN_getRelatedItemColumns_695: return true;
        case SYM_GEN_getRelatedItemHeight_696: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__DeckofCards::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onAddToInventory_417: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_416: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_resetChain_1739: out = fn_resetChain(args, argc); return true;
        case SYM_GEN_countDuplicates_1706: out = fn_countDuplicates(args, argc); return true;
        case SYM_GEN_updateCards_1740: out = fn_updateCards(args, argc); return true;
        case SYM_GEN_onItemAdded_435: out = fn_onItemAdded(args, argc); return true;
        case SYM_GEN_onItemRemoved_436: out = fn_onItemRemoved(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_notifyActivation_1741: out = fn_notifyActivation(args, argc); return true;
        case SYM_GEN_getGatedDescriptor_952: out = fn_getGatedDescriptor(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_695: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN_getRelatedItemHeight_696: out = fn_getRelatedItemHeight(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__DeckofCards::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__DeckofCards::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Card_2672)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeckofCards::fn_onAddToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateCards_1740, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeckofCards::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetChain_1739, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeckofCards::fn_resetChain(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1187 = gd::gd_iter_seq(gd_ctx.arena, this->f_cards);
        gd::GdArr* _t1188 = (_t1187.kind == gd::GdVal::Kind::Arr) ? _t1187.arr : nullptr;
        uint32_t _len__t1189 = _t1188 ? _t1188->len : 0u;
        for (uint32_t _t1189 = 0; _t1189 < _len__t1189; ++_t1189) {
            gd::GdVal lv_card = _t1188->data[_t1189];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::gd_neg(gd::GdVal::from_int(1LL)), gd::call_method(gd_ctx, this->f_cards, gd::SYM_size, nullptr, 0)}; return gd::call_method(gd_ctx, lv_card, SYM_GEN_notifyChainPosition_890, _ca, 3); })();
        }
    }
    (void)gd::call_method(gd_ctx, this->f_cards, gd::SYM_clear, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeckofCards::fn_countDuplicates(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_untilCardIndex = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_descriptors = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1190 = gd::gd_iter_seq(gd_ctx.arena, lv_untilCardIndex);
        gd::GdArr* _t1191 = (_t1190.kind == gd::GdVal::Kind::Arr) ? _t1190.arr : nullptr;
        uint32_t _len__t1192 = _t1191 ? _t1191->len : 0u;
        for (uint32_t _t1192 = 0; _t1192 < _len__t1192; ++_t1192) {
            gd::GdVal lv_i = _t1191->data[_t1192];
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_index(gd_ctx, this->f_cards, lv_i), SYM_GEN_descriptor_2)}; return gd::call_method(gd_ctx, lv_descriptors, gd::SYM_push_back, _ca, 1); })();
        }
    }
    return ([&]() { gd::GdVal _ca[] = {lv_descriptors}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_countDuplicates_1706, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeckofCards::fn_updateCards(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetChain_1739, nullptr, 0);
    gd::GdVal lv_affected = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_affected, gd::SYM_empty, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL))}; return gd::call_method(gd_ctx, this->f_cards, gd::SYM_push_back, _ca, 1); })();
        gd::GdVal lv_nextCard = gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_cards, gd::GdVal::from_int(0LL)), SYM_GEN_getNextCard_887, nullptr, 0);
        while (gd::gd_truth((gd::gd_truth(lv_nextCard) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_nextCard, this->f_cards))))) : gd::GdVal::from_bool(false)))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_nextCard}; return gd::call_method(gd_ctx, this->f_cards, gd::SYM_push_back, _ca, 1); })();
            lv_nextCard = gd::call_method(gd_ctx, lv_nextCard, SYM_GEN_getNextCard_887, nullptr, 0);
        }
    }
    else {
    }
    gd::GdVal lv_chainLength = gd::call_method(gd_ctx, this->f_cards, gd::SYM_size, nullptr, 0);
    {
        gd::GdVal _t1193 = gd::gd_iter_seq(gd_ctx.arena, lv_chainLength);
        gd::GdArr* _t1194 = (_t1193.kind == gd::GdVal::Kind::Arr) ? _t1193.arr : nullptr;
        uint32_t _len__t1195 = _t1194 ? _t1194->len : 0u;
        for (uint32_t _t1195 = 0; _t1195 < _len__t1195; ++_t1195) {
            gd::GdVal lv_i = _t1194->data[_t1195];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_i, lv_chainLength}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_cards, lv_i), SYM_GEN_notifyChainPosition_890, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeckofCards::fn_onItemAdded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onItemAdded_435, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(lv_item, &META_Gd__gd_core_items__Card)))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateCards_1740, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeckofCards::fn_onItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onItemRemoved_436, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(lv_item, &META_Gd__gd_core_items__Card)))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateCards_1740, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeckofCards::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_chainStarted = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeckofCards::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_213, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_chainStarted)))) {
        this->f_chainStarted = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        this->f_cardActivations = gd::GdVal::from_int(0LL);
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, this->f_cards, gd::SYM_empty, nullptr, 0))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, this->f_cards, gd::GdVal::from_int(0LL)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "startActivation", 15u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_defer_1418, _ca, 3); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeckofCards::fn_notifyActivation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_cardActivations = gd::gd_add(gd_ctx, this->f_cardActivations, gd::GdVal::from_int(1LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeckofCards::fn_getGatedDescriptor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rarity = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeckofCards::fn_getRelatedItemColumns(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(4LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeckofCards::fn_getRelatedItemHeight(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(120LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeckofCards::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__DeckofCards(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__DeckofCards>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__DeckofCards = {CLS_Gd__gd_core_items__DeckofCards, "DeckofCards", "res://gd_core_items/DeckofCards.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__DeckofCards, &Gd__gd_core_items__DeckofCards::get_static_prop_fn, &Gd__gd_core_items__DeckofCards::call_static_fn};

void Gd__gd_core_items__Exclusive__AmuletofSteel::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_blockAcc = gd::GdVal::from_int(0);
    this->f_blockForEmpower = gd::GdVal::null();
    this->f_empowerForBlock = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__AmuletofSteel::meta() const { return &META_Gd__gd_core_items__Exclusive__AmuletofSteel; }
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofSteel::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_amuletColor_1924: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.34902), gd::GdVal::from_float(0.415686), gd::GdVal::from_float(0.45098)}; return gd::make_color_from_args(_ca, 3); })();
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__AmuletofSteel::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__AmuletofSteel::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_blockAcc_1850: out = this->f_blockAcc; return true;
        case SYM_GEN_blockForEmpower_1936: out = this->f_blockForEmpower; return true;
        case SYM_GEN_empowerForBlock_1937: out = this->f_empowerForBlock; return true;
        case SYM_GEN_amuletColor_1924: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__AmuletofSteel::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blockAcc_1850: this->f_blockAcc = gd::gd_coerce_int(val); return true;
        case SYM_GEN_blockForEmpower_1936: this->f_blockForEmpower = val; return true;
        case SYM_GEN_empowerForBlock_1937: this->f_empowerForBlock = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__AmuletofSteel::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_onItemGaveBlock_1852: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__AmuletofSteel::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onItemGaveBlock_1852: out = fn_onItemGaveBlock(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__AmuletofSteel::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofSteel::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBlock_289, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofSteel::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_blockAcc = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    {
        gd::GdVal _t1196 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1197 = (_t1196.kind == gd::GdVal::Kind::Arr) ? _t1196.arr : nullptr;
        uint32_t _len__t1198 = _t1197 ? _t1197->len : 0u;
        for (uint32_t _t1198 = 0; _t1198 < _len__t1198; ++_t1198) {
            gd::GdVal lv_item = _t1197->data[_t1198];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gave_block", 10u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onItemGaveBlock", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofSteel::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofSteel::fn_onItemGaveBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    this->f_blockAcc = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_blockAcc, lv_amount));
    gd::GdVal lv_empower = gd::gd_div(gd_ctx, this->f_blockAcc, this->f_blockForEmpower);
    this->f_blockAcc = gd::gd_coerce_int(gd::gd_mod(gd_ctx, this->f_blockAcc, this->f_blockForEmpower));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_empower, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_empower, this->f_empowerForBlock), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_215, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofSteel::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_blockForEmpower = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blockt", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_empowerForBlock = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "empower", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__AmuletofSteel(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__AmuletofSteel>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AmuletofSteel = {CLS_Gd__gd_core_items__Exclusive__AmuletofSteel, "AmuletofSteel", "res://gd_core_items/Exclusive/AmuletofSteel.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__AmuletofSteel, &Gd__gd_core_items__Exclusive__AmuletofSteel::get_static_prop_fn, &Gd__gd_core_items__Exclusive__AmuletofSteel::call_static_fn};

void Gd__gd_core_items__Exclusive__BadgerRune::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Gems__Gem::init_fields(gd_ctx);
    this->f_attackSpeedBonus = gd::GdVal::null();
    this->f_damageReduction = gd::GdVal::from_int(0);
    this->f_staminaReduction = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__BadgerRune::meta() const { return &META_Gd__gd_core_items__Exclusive__BadgerRune; }
gd::GdVal Gd__gd_core_items__Exclusive__BadgerRune::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_gemColor_991: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.845703), gd::GdVal::from_float(0.420593), gd::GdVal::from_float(0.062767)}; return gd::make_color_from_args(_ca, 3); })();
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__BadgerRune::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__BadgerRune::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_attackSpeedBonus_1955: out = this->f_attackSpeedBonus; return true;
        case SYM_GEN_damageReduction_1059: out = this->f_damageReduction; return true;
        case SYM_GEN_staminaReduction_1917: out = this->f_staminaReduction; return true;
        case SYM_GEN_gemColor_991: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BadgerRune::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_attackSpeedBonus_1955: this->f_attackSpeedBonus = val; return true;
        case SYM_GEN_damageReduction_1059: this->f_damageReduction = gd::gd_coerce_int(val); return true;
        case SYM_GEN_staminaReduction_1917: this->f_staminaReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BadgerRune::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_isBattleRageItem_83: return true;
        case SYM_GEN_prepareWeapon_978: return true;
        case SYM_GEN_onAttack_1956: return true;
        case SYM_GEN_prepareArmor_979: return true;
        case SYM_GEN_preTakeDamage_1848: return true;
        case SYM_GEN_hasCooldown_93: return true;
        case SYM_GEN_prepareInventory_977: return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_988: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BadgerRune::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_isBattleRageItem_83: out = fn_isBattleRageItem(args, argc); return true;
        case SYM_GEN_prepareWeapon_978: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_onAttack_1956: out = fn_onAttack(args, argc); return true;
        case SYM_GEN_prepareArmor_979: out = fn_prepareArmor(args, argc); return true;
        case SYM_GEN_preTakeDamage_1848: out = fn_preTakeDamage(args, argc); return true;
        case SYM_GEN_hasCooldown_93: out = fn_hasCooldown(args, argc); return true;
        case SYM_GEN_prepareInventory_977: out = fn_prepareInventory(args, argc); return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_988: out = fn_onHotSwapHoverWithGemEnd(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__BadgerRune::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Gems__Gem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__BadgerRune::fn_isBattleRageItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_968, nullptr, 0), gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__BadgerRune::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_990), SYM_GEN_Armor_2750)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BadgerRune::fn_prepareWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_387, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attacked", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onAttack", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BadgerRune::fn_onAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_attackSpeedBonus}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_387, nullptr, 0), SYM_GEN_addSpeed_271, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BadgerRune::fn_prepareArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "pre_take_damage", 15u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "preTakeDamage", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BadgerRune::fn_preTakeDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_triggerOnAttacked_1437, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_isBattleRaging_1187, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_round(gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_969, nullptr, 0), this->f_damageReduction)), gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_applyDamageReduction_1433, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BadgerRune::fn_hasCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BadgerRune::fn_prepareInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1199 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1510, nullptr, 0));
        gd::GdArr* _t1200 = (_t1199.kind == gd::GdVal::Kind::Arr) ? _t1199.arr : nullptr;
        uint32_t _len__t1201 = _t1200 ? _t1200->len : 0u;
        for (uint32_t _t1201 = 0; _t1201 < _len__t1201; ++_t1201) {
            gd::GdVal lv_item = _t1200->data[_t1201];
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_staminaReduction)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeStaminaFactor_303, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BadgerRune::fn_onHotSwapHoverWithGemEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BadgerRune::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_attackSpeedBonus = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attackspeed", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_damageReduction = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "damreduction", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_staminaReduction = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__BadgerRune(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__BadgerRune>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BadgerRune = {CLS_Gd__gd_core_items__Exclusive__BadgerRune, "BadgerRune", "res://gd_core_items/Exclusive/BadgerRune.gd", &META_Gd__gd_core_items__Gems__Gem, true, _alloc_Gd__gd_core_items__Exclusive__BadgerRune, &Gd__gd_core_items__Exclusive__BadgerRune::get_static_prop_fn, &Gd__gd_core_items__Exclusive__BadgerRune::call_static_fn};

void Gd__gd_core_items__Exclusive__BookofBasics::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_bonusHealthFactor = gd::GdVal::from_int(0);
    this->f_salesChance = gd::GdVal::null();
    this->f_manaNeeded = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__BookofBasics::meta() const { return &META_Gd__gd_core_items__Exclusive__BookofBasics; }
gd::GdVal Gd__gd_core_items__Exclusive__BookofBasics::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__BookofBasics::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__BookofBasics::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_bonusHealthFactor_1995: out = this->f_bonusHealthFactor; return true;
        case SYM_GEN_salesChance_1996: out = this->f_salesChance; return true;
        case SYM_GEN_manaNeeded_1785: out = this->f_manaNeeded; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BookofBasics::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bonusHealthFactor_1995: this->f_bonusHealthFactor = gd::gd_coerce_int(val); return true;
        case SYM_GEN_salesChance_1996: this->f_salesChance = val; return true;
        case SYM_GEN_manaNeeded_1785: this->f_manaNeeded = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BookofBasics::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onSaleRoll_1997: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BookofBasics::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onSaleRoll_1997: out = fn_onSaleRoll(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__BookofBasics::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofBasics::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Spell_2606)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofBasics::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_bonusHealthFactor = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    {
        gd::GdVal _t1202 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1203 = (_t1202.kind == gd::GdVal::Kind::Arr) ? _t1202.arr : nullptr;
        uint32_t _len__t1204 = _t1203 ? _t1203->len : 0u;
        for (uint32_t _t1204 = 0; _t1204 < _len__t1204; ++_t1204) {
            gd::GdVal lv_item = _t1203->data[_t1204];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isCrafted_796, nullptr, 0))) {
                this->f_bonusHealthFactor = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_bonusHealthFactor, gd::GdVal::from_int(2LL)));
            }
            else {
                this->f_bonusHealthFactor = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_bonusHealthFactor, gd::GdVal::from_int(1LL)));
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofBasics::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getMana_1224, nullptr, 0), this->f_manaNeeded)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_330, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth_spell", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), this->f_bonusHealthFactor)), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_315, _ca, 2); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofBasics::fn_onSaleRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofBasics::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_salesChance = gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getShopChance_235, nullptr, 0), gd::GdVal::from_float(100.0));
    this->f_manaNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "manat", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__BookofBasics(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__BookofBasics>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BookofBasics = {CLS_Gd__gd_core_items__Exclusive__BookofBasics, "BookofBasics", "res://gd_core_items/Exclusive/BookofBasics.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__BookofBasics, &Gd__gd_core_items__Exclusive__BookofBasics::get_static_prop_fn, &Gd__gd_core_items__Exclusive__BookofBasics::call_static_fn};

void Gd__gd_core_items__Exclusive__BustedBlade::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Greatsword::init_fields(gd_ctx);
    this->f_bonusDamPerEmpower = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__BustedBlade::meta() const { return &META_Gd__gd_core_items__Exclusive__BustedBlade; }
gd::GdVal Gd__gd_core_items__Exclusive__BustedBlade::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Greatsword::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__BustedBlade::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__BustedBlade::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_bonusDamPerEmpower_2016: out = this->f_bonusDamPerEmpower; return true;
        default: break;
    }
    return Gd__gd_core_items__Greatsword::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BustedBlade::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bonusDamPerEmpower_2016: this->f_bonusDamPerEmpower = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Greatsword::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BustedBlade::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onEmpowerChanged_2017: return true;
        case SYM_GEN_onBattleRageStarted_1970: return true;
        case SYM_GEN_onBattleRageEnded_1971: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Greatsword::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BustedBlade::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onEmpowerChanged_2017: out = fn_onEmpowerChanged(args, argc); return true;
        case SYM_GEN_onBattleRageStarted_1970: out = fn_onBattleRageStarted(args, argc); return true;
        case SYM_GEN_onBattleRageEnded_1971: out = fn_onBattleRageEnded(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Greatsword::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__BustedBlade::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Greatsword::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__BustedBlade::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "battle_rage_started", 19u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBattleRageStarted", 19u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "battle_rage_ended", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBattleRageEnded", 17u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_empower_changed", 25u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onEmpowerChanged", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BustedBlade::fn_onEmpowerChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, this->f_bonusDamPerEmpower)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_160, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BustedBlade::fn_onBattleRageStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_buffed)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
        this->f_baseCooldownOverride = gd::gd_coerce_float(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0));
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateBaseCooldown_108, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1365), SYM_GEN_StaminaCost_2546)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1377), SYM_GEN_snapshotItemTooltipStat_1351, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BustedBlade::fn_onBattleRageEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(this->f_buffed)) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
        this->f_baseCooldownOverride = gd::gd_coerce_float(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldown_98, nullptr, 0));
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateBaseCooldown_108, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1365), SYM_GEN_StaminaCost_2546)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1377), SYM_GEN_snapshotItemTooltipStat_1351, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BustedBlade::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Greatsword::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_bonusDamPerEmpower = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__BustedBlade(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__BustedBlade>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BustedBlade = {CLS_Gd__gd_core_items__Exclusive__BustedBlade, "BustedBlade", "res://gd_core_items/Exclusive/BustedBlade.gd", &META_Gd__gd_core_items__Greatsword, true, _alloc_Gd__gd_core_items__Exclusive__BustedBlade, &Gd__gd_core_items__Exclusive__BustedBlade::get_static_prop_fn, &Gd__gd_core_items__Exclusive__BustedBlade::call_static_fn};

void Gd__gd_core_items__Exclusive__Chess__BlackRook::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__Chess__ChessPiece::init_fields(gd_ctx);
    this->f_buffTimer = gd::GdVal::null();
    this->f_spikes = gd::GdVal::null();
    this->f_crit = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Chess__BlackRook::meta() const { return &META_Gd__gd_core_items__Exclusive__Chess__BlackRook; }
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackRook::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackRook::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Chess__BlackRook::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_buffTimer_1723: out = this->f_buffTimer; return true;
        case SYM_GEN_spikes_894: out = this->f_spikes; return true;
        case SYM_GEN_crit_2060: out = this->f_crit; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackRook::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffTimer_1723: this->f_buffTimer = val; return true;
        case SYM_GEN_spikes_894: this->f_spikes = val; return true;
        case SYM_GEN_crit_2060: this->f_crit = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackRook::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2049: return true;
        case SYM_GEN_doEliminatedEffect_2051: return true;
        case SYM_GEN_buffEnded_1721: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackRook::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2049: out = fn_doCapturingEffect(args, argc); return true;
        case SYM_GEN_doEliminatedEffect_2051: out = fn_doEliminatedEffect(args, argc); return true;
        case SYM_GEN_buffEnded_1721: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackRook::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackRook::fn_doCapturingEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__eliminatedPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {this->f_spikes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_207, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackRook::fn_doEliminatedEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__capturingPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_crit}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeAllItemsCritRate_467, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })()}; return gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_start_1683, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackRook::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_crit)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeAllItemsCritRate_467, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackRook::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "BuffTimer", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffEnded", 9u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_133, _ca, 3); })();
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_crit = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "crit", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Chess__BlackRook(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Chess__BlackRook>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Chess__BlackRook = {CLS_Gd__gd_core_items__Exclusive__Chess__BlackRook, "BlackRook", "res://gd_core_items/Exclusive/Chess/BlackRook.gd", &META_Gd__gd_core_items__Exclusive__Chess__ChessPiece, true, _alloc_Gd__gd_core_items__Exclusive__Chess__BlackRook, &Gd__gd_core_items__Exclusive__Chess__BlackRook::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Chess__BlackRook::call_static_fn};

void Gd__gd_core_items__Exclusive__CriticalPoison::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_damageAcc = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_damagePerPoison = gd::GdVal::from_int(0);
    this->f_poison = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__CriticalPoison::meta() const { return &META_Gd__gd_core_items__Exclusive__CriticalPoison; }
gd::GdVal Gd__gd_core_items__Exclusive__CriticalPoison::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__CriticalPoison::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__CriticalPoison::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_damageAcc_1864: out = this->f_damageAcc; return true;
        case SYM_GEN_damagePerPoison_1865: out = this->f_damagePerPoison; return true;
        case SYM_GEN_poison_1866: out = this->f_poison; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__CriticalPoison::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damageAcc_1864: this->f_damageAcc = gd::gd_coerce_int(val); return true;
        case SYM_GEN_damagePerPoison_1865: this->f_damagePerPoison = gd::gd_coerce_int(val); return true;
        case SYM_GEN_poison_1866: this->f_poison = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__CriticalPoison::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onWeaponAttacked_946: return true;
        case SYM_GEN_onLuckChanged_1968: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__CriticalPoison::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onWeaponAttacked_946: out = fn_onWeaponAttacked(args, argc); return true;
        case SYM_GEN_onLuckChanged_1968: out = fn_onLuckChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__CriticalPoison::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__CriticalPoison::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_88, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CriticalPoison::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1205 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1206 = (_t1205.kind == gd::GdVal::Kind::Arr) ? _t1205.arr : nullptr;
        uint32_t _len__t1207 = _t1206 ? _t1206->len : 0u;
        for (uint32_t _t1207 = 0; _t1207 < _len__t1207; ++_t1207) {
            gd::GdVal lv_weapon = _t1206->data[_t1207];
            (void)([&]() { gd::GdVal _ca[] = {lv_weapon, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attacked", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onWeaponAttacked", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_lucky_changed", 23u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onLuckChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CriticalPoison::fn_onWeaponAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        this->f_damageAcc = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_damageAcc, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1425)));
        gd::GdVal lv_poisonStacks = gd::gd_div(gd_ctx, this->f_damageAcc, this->f_damagePerPoison);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_poisonStacks, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_poisonStacks, this->f_poison), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_209, _ca, 2); })();
            this->f_damageAcc = gd::gd_coerce_int(gd::gd_mod(gd_ctx, this->f_damageAcc, this->f_damagePerPoison));
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CriticalPoison::fn_onLuckChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_changePoisonCritChancePercent_1263, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CriticalPoison::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_damagePerPoison = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "damt", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_poison = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "poison", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__CriticalPoison(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__CriticalPoison>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__CriticalPoison = {CLS_Gd__gd_core_items__Exclusive__CriticalPoison, "CriticalPoison", "res://gd_core_items/Exclusive/CriticalPoison.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__CriticalPoison, &Gd__gd_core_items__Exclusive__CriticalPoison::get_static_prop_fn, &Gd__gd_core_items__Exclusive__CriticalPoison::call_static_fn};

void Gd__gd_core_items__Exclusive__DoomCap::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Food::init_fields(gd_ctx);
    this->f_poison = gd::GdVal::null();
    this->f_healingDebuff = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__DoomCap::meta() const { return &META_Gd__gd_core_items__Exclusive__DoomCap; }
gd::GdVal Gd__gd_core_items__Exclusive__DoomCap::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__DoomCap::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__DoomCap::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_poison_1866: out = this->f_poison; return true;
        case SYM_GEN_healingDebuff_1892: out = this->f_healingDebuff; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DoomCap::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_poison_1866: this->f_poison = val; return true;
        case SYM_GEN_healingDebuff_1892: this->f_healingDebuff = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DoomCap::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DoomCap::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__DoomCap::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__DoomCap::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_poison}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_209, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_healingDebuff}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_reduceHealingEfficiency_1163, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DoomCap::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_poison = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "poison", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_healingDebuff = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healreduction", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__DoomCap(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__DoomCap>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DoomCap = {CLS_Gd__gd_core_items__Exclusive__DoomCap, "DoomCap", "res://gd_core_items/Exclusive/DoomCap.gd", &META_Gd__gd_core_items__Food, true, _alloc_Gd__gd_core_items__Exclusive__DoomCap, &Gd__gd_core_items__Exclusive__DoomCap::get_static_prop_fn, &Gd__gd_core_items__Exclusive__DoomCap::call_static_fn};

void Gd__gd_core_items__Exclusive__EmeraldEgg::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__DragonEgg::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__EmeraldEgg::meta() const { return &META_Gd__gd_core_items__Exclusive__EmeraldEgg; }
gd::GdVal Gd__gd_core_items__Exclusive__EmeraldEgg::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__DragonEgg::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__EmeraldEgg::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__EmeraldEgg::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__DragonEgg::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__EmeraldEgg::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__DragonEgg::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__EmeraldEgg::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__DragonEgg::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__EmeraldEgg::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__DragonEgg::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__EmeraldEgg::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__DragonEgg::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__EmeraldEgg::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doCooldownEffect_142, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EmeraldEgg::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_213, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EmeraldEgg::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__DragonEgg::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__EmeraldEgg(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__EmeraldEgg>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__EmeraldEgg = {CLS_Gd__gd_core_items__Exclusive__EmeraldEgg, "EmeraldEgg", "res://gd_core_items/Exclusive/EmeraldEgg.gd", &META_Gd__gd_core_items__DragonEgg, true, _alloc_Gd__gd_core_items__Exclusive__EmeraldEgg, &Gd__gd_core_items__Exclusive__EmeraldEgg::get_static_prop_fn, &Gd__gd_core_items__Exclusive__EmeraldEgg::call_static_fn};

void Gd__gd_core_items__Exclusive__FireShelly::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Exclusive__Shelly::init_fields(gd_ctx);
    this->f_heat = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__FireShelly::meta() const { return &META_Gd__gd_core_items__Exclusive__FireShelly; }
gd::GdVal Gd__gd_core_items__Exclusive__FireShelly::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Exclusive__Shelly::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__FireShelly::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__FireShelly::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_heat_1800: out = this->f_heat; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Shelly::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__FireShelly::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_heat_1800: this->f_heat = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Shelly::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__FireShelly::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Shelly::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__FireShelly::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Shelly::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__FireShelly::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__Shelly::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__FireShelly::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 1); })();
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Shelly::call_method(gd_ctx, SYM_GEN_doCooldownEffect_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FireShelly::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Shelly::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__FireShelly(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__FireShelly>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__FireShelly = {CLS_Gd__gd_core_items__Exclusive__FireShelly, "FireShelly", "res://gd_core_items/Exclusive/FireShelly.gd", &META_Gd__gd_core_items__Exclusive__Shelly, true, _alloc_Gd__gd_core_items__Exclusive__FireShelly, &Gd__gd_core_items__Exclusive__FireShelly::get_static_prop_fn, &Gd__gd_core_items__Exclusive__FireShelly::call_static_fn};

void Gd__gd_core_items__Exclusive__FurciferPrime::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_active = gd::GdVal::from_bool(false);
    this->f_salesChance = gd::GdVal::null();
    this->f_goldCost = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__FurciferPrime::meta() const { return &META_Gd__gd_core_items__Exclusive__FurciferPrime; }
gd::GdVal Gd__gd_core_items__Exclusive__FurciferPrime::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__FurciferPrime::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__FurciferPrime::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_active_2128: out = this->f_active; return true;
        case SYM_GEN_salesChance_1996: out = this->f_salesChance; return true;
        case SYM_GEN_goldCost_2068: out = this->f_goldCost; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__FurciferPrime::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_active_2128: this->f_active = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_salesChance_1996: this->f_salesChance = val; return true;
        case SYM_GEN_goldCost_2068: this->f_goldCost = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__FurciferPrime::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getData_634: return true;
        case SYM_GEN_setData_635: return true;
        case SYM_GEN_onSwitchToCombat_2190: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_onSaleRoll_1997: return true;
        case SYM_GEN_onSaleRoll_storage_2191: return true;
        case SYM_GEN_getGatedDescriptor_952: return true;
        case SYM_GEN_onGateItemRoll_449: return true;
        case SYM_GEN_onGateItemRoll_storage_2192: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__FurciferPrime::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getData_634: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_635: out = fn_setData(args, argc); return true;
        case SYM_GEN_onSwitchToCombat_2190: out = fn_onSwitchToCombat(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onSaleRoll_1997: out = fn_onSaleRoll(args, argc); return true;
        case SYM_GEN_onSaleRoll_storage_2191: out = fn_onSaleRoll_storage(args, argc); return true;
        case SYM_GEN_getGatedDescriptor_952: out = fn_getGatedDescriptor(args, argc); return true;
        case SYM_GEN_onGateItemRoll_449: out = fn_onGateItemRoll(args, argc); return true;
        case SYM_GEN_onGateItemRoll_storage_2192: out = fn_onGateItemRoll_storage(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__FurciferPrime::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__FurciferPrime::fn_getData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_active;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FurciferPrime::fn_setData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_data = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_active = gd::gd_coerce_bool(lv_data);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FurciferPrime::fn_onSwitchToCombat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_active = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FurciferPrime::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FurciferPrime::fn_onSaleRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FurciferPrime::fn_onSaleRoll_storage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv__item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onSaleRoll_1997, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FurciferPrime::fn_getGatedDescriptor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rarity = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FurciferPrime::fn_onGateItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_active)) {
        (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onGateItemRoll_449, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FurciferPrime::fn_onGateItemRoll_storage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onGateItemRoll_449, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FurciferPrime::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_salesChance = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "sales", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_goldCost = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gold", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__FurciferPrime(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__FurciferPrime>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__FurciferPrime = {CLS_Gd__gd_core_items__Exclusive__FurciferPrime, "FurciferPrime", "res://gd_core_items/Exclusive/FurciferPrime.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__FurciferPrime, &Gd__gd_core_items__Exclusive__FurciferPrime::get_static_prop_fn, &Gd__gd_core_items__Exclusive__FurciferPrime::call_static_fn};

void Gd__gd_core_items__Exclusive__HogusBogus::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_phase = gd::GdVal::from_int(0);
    this->f_maxStaminaUsed = gd::GdVal::null();
    this->f_buffsPerStamina = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__HogusBogus::meta() const { return &META_Gd__gd_core_items__Exclusive__HogusBogus; }
gd::GdVal Gd__gd_core_items__Exclusive__HogusBogus::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__HogusBogus::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__HogusBogus::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_phase_2212: out = this->f_phase; return true;
        case SYM_GEN_maxStaminaUsed_2213: out = this->f_maxStaminaUsed; return true;
        case SYM_GEN_buffsPerStamina_2214: out = this->f_buffsPerStamina; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__HogusBogus::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_phase_2212: this->f_phase = gd::gd_coerce_int(val); return true;
        case SYM_GEN_maxStaminaUsed_2213: this->f_maxStaminaUsed = val; return true;
        case SYM_GEN_buffsPerStamina_2214: this->f_buffsPerStamina = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__HogusBogus::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_trigger_141: return true;
        case SYM_GEN_canUseStamina_292: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__HogusBogus::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_trigger_141: out = fn_trigger(args, argc); return true;
        case SYM_GEN_canUseStamina_292: out = fn_canUseStamina(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__HogusBogus::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__HogusBogus::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_phase = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HogusBogus::fn_trigger(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_phase, gd::GdVal::from_int(1LL))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_trigger_141, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HogusBogus::fn_canUseStamina(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HogusBogus::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_phase, gd::GdVal::from_int(1LL))))) {
        gd::GdVal lv_curStamina = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getCurrentStamina_1242, nullptr, 0);
        gd::GdVal lv_step = gd::gd_div(gd_ctx, gd::GdVal::from_float(1.0), this->f_buffsPerStamina);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_curStamina, lv_step)))) {
            gd::GdVal lv_numProccs = gd::gd_floor(gd::gd_div(gd_ctx, lv_curStamina, lv_step));
            gd::GdVal lv_staminaToUse = gd::gd_min(lv_curStamina, gd::gd_min(gd::gd_mul(lv_numProccs, lv_step), this->f_maxStaminaUsed));
            (void)([&]() { gd::GdVal _ca[] = {lv_staminaToUse}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_114, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_round(gd::gd_mul(lv_staminaToUse, this->f_buffsPerStamina))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_367, _ca, 1); })();
        }
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_phase, gd::GdVal::from_int(2LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_stun", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_328, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_self_stun", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_stun_328, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    }
    else {
        gd::GdVal lv_curHealth = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_getCurrentHealth_1134, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::gd_mul(lv_curHealth, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })()), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_143, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HogusBogus::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__phase = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv__phase = gd::gd_coerce_int(lv__phase);
    this->f_phase = gd::gd_coerce_int(lv__phase);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_phase, gd::GdVal::from_int(0LL))))) {
        this->f_baseCooldownOverride = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldownIndex_99, _ca, 1); })());
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_phase, gd::GdVal::from_int(3LL))))) {
        this->f_baseCooldownOverride = gd::gd_coerce_float(gd::gd_sub(([&]() { gd::GdVal _ca[] = {this->f_phase}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldownIndex_99, _ca, 1); })(), ([&]() { gd::GdVal _ca[] = {gd::gd_sub(this->f_phase, gd::GdVal::from_int(1LL))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldownIndex_99, _ca, 1); })()));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HogusBogus::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_maxStaminaUsed = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_buffsPerStamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__HogusBogus(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__HogusBogus>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__HogusBogus = {CLS_Gd__gd_core_items__Exclusive__HogusBogus, "HogusBogus", "res://gd_core_items/Exclusive/HogusBogus.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__HogusBogus, &Gd__gd_core_items__Exclusive__HogusBogus::get_static_prop_fn, &Gd__gd_core_items__Exclusive__HogusBogus::call_static_fn};

static const gd::GdEnum::KV _ekv_Gd__gd_core_items__Exclusive__KingGoobert_CrownState[] = {{"Inactive", 0LL}, {"Active", 1LL}, {"Used", 2LL}};
static const gd::GdEnum _enum_Gd__gd_core_items__Exclusive__KingGoobert_CrownState = {"CrownState", _ekv_Gd__gd_core_items__Exclusive__KingGoobert_CrownState, 3u};
void Gd__gd_core_items__Exclusive__KingGoobert::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Goobert::init_fields(gd_ctx);
    this->f_invuCharges = gd::GdVal::from_int(0);
    this->f_protectedBuffs = gd::GdVal::null();
    this->f_manaCost = gd::GdVal::null();
    this->f_activationParticles = gd::GdVal::null();
    this->f_buffTimer = gd::GdVal::null();
    this->f_light = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__KingGoobert::meta() const { return &META_Gd__gd_core_items__Exclusive__KingGoobert; }
gd::GdVal Gd__gd_core_items__Exclusive__KingGoobert::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_CrownState_1726: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Exclusive__KingGoobert_CrownState);
        default: break;
    }
    return Gd__gd_core_items__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__KingGoobert::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__KingGoobert::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_invuCharges_2235: out = this->f_invuCharges; return true;
        case SYM_GEN_protectedBuffs_2236: out = this->f_protectedBuffs; return true;
        case SYM_GEN_manaCost_1719: out = this->f_manaCost; return true;
        case SYM_GEN_activationParticles_908: out = this->f_activationParticles; return true;
        case SYM_GEN_buffTimer_1723: out = this->f_buffTimer; return true;
        case SYM_GEN_light_945: out = this->f_light; return true;
        case SYM_GEN_CrownState_1726: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Exclusive__KingGoobert_CrownState); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__KingGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_invuCharges_2235: this->f_invuCharges = gd::gd_coerce_int(val); return true;
        case SYM_GEN_protectedBuffs_2236: this->f_protectedBuffs = val; return true;
        case SYM_GEN_manaCost_1719: this->f_manaCost = val; return true;
        case SYM_GEN_activationParticles_908: this->f_activationParticles = val; return true;
        case SYM_GEN_buffTimer_1723: this->f_buffTimer = val; return true;
        case SYM_GEN_light_945: this->f_light = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__KingGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_prepare_120: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_buffEnded_1721: return true;
        case SYM_GEN_onCombatEnd_130: return true;
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_onStateChanged_381: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__KingGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_prepare_120: out = fn_prepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_buffEnded_1721: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_onCombatEnd_130: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_381: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__KingGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__KingGoobert::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_gemPower = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gempower", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    {
        gd::GdVal _t1208 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemsNoNull_495, nullptr, 0));
        gd::GdArr* _t1209 = (_t1208.kind == gd::GdVal::Kind::Arr) ? _t1208.arr : nullptr;
        uint32_t _len__t1210 = _t1209 ? _t1209->len : 0u;
        for (uint32_t _t1210 = 0; _t1210 < _len__t1210; ++_t1210) {
            gd::GdVal lv_gem = _t1209->data[_t1210];
            (void)([&]() { gd::GdVal _ca[] = {lv_gemPower}; return gd::call_method(gd_ctx, lv_gem, SYM_GEN_changeGemPower_970, _ca, 1); })();
        }
    }
    this->f_invuCharges = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "charges", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__KingGoobert::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1726), SYM_GEN_Inactive_2593)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 1); })();
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN_prepare_120, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KingGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_protectedBuffs}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeBuffProtectStacks_1167, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_invuCharges, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_isVulnerable_1271, nullptr, 0))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkMana_329, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        this->f_invuCharges = gd::gd_coerce_int(gd::gd_sub(this->f_invuCharges, gd::GdVal::from_int(1LL)));
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__KingGoobert::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1726), SYM_GEN_Active_2594), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 2); })();
        gd::GdVal lv_invuDur = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_invu", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })();
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_invuDur, gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_makeInvulnerable_1191, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_invuDur}; return gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_start_1683, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_manaCost, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_330, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KingGoobert::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_invuCharges, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__KingGoobert::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1726), SYM_GEN_Inactive_2593), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 2); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__KingGoobert::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1726), SYM_GEN_Used_2595), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_380, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KingGoobert::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1684, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KingGoobert::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__KingGoobert::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1726), SYM_GEN_Inactive_2593)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_381, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KingGoobert::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__crownState = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv__crownState, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__KingGoobert::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1726), SYM_GEN_Inactive_2593))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv__crownState, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__KingGoobert::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1726), SYM_GEN_Active_2594))))) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KingGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_protectedBuffs = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_manaCost = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "BuffTimer", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffEnded", 9u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_133, _ca, 3); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__KingGoobert(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__KingGoobert>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__KingGoobert = {CLS_Gd__gd_core_items__Exclusive__KingGoobert, "KingGoobert", "res://gd_core_items/Exclusive/KingGoobert.gd", &META_Gd__gd_core_items__Goobert, true, _alloc_Gd__gd_core_items__Exclusive__KingGoobert, &Gd__gd_core_items__Exclusive__KingGoobert::get_static_prop_fn, &Gd__gd_core_items__Exclusive__KingGoobert::call_static_fn};

void Gd__gd_core_items__Exclusive__MagicCollar::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__RangerCollar::init_fields(gd_ctx);
    this->f_mana = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__MagicCollar::meta() const { return &META_Gd__gd_core_items__Exclusive__MagicCollar; }
gd::GdVal Gd__gd_core_items__Exclusive__MagicCollar::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__RangerCollar::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__MagicCollar::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__MagicCollar::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_mana_1832: out = this->f_mana; return true;
        default: break;
    }
    return Gd__gd_core_items__RangerCollar::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MagicCollar::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_mana_1832: this->f_mana = val; return true;
        default: break;
    }
    return Gd__gd_core_items__RangerCollar::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MagicCollar::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onWeaponAttacked_946: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__RangerCollar::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MagicCollar::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onWeaponAttacked_946: out = fn_onWeaponAttacked(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__RangerCollar::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__MagicCollar::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__RangerCollar::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicCollar::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_88, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicCollar::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1211 = gd::gd_iter_seq(gd_ctx.arena, this->f_affectedItems);
        gd::GdArr* _t1212 = (_t1211.kind == gd::GdVal::Kind::Arr) ? _t1211.arr : nullptr;
        uint32_t _len__t1213 = _t1212 ? _t1212->len : 0u;
        for (uint32_t _t1213 = 0; _t1213 < _len__t1213; ++_t1213) {
            gd::GdVal lv_item = _t1212->data[_t1213];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attacked", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onWeaponAttacked", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicCollar::fn_onWeaponAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_triggerOnHit_1434, nullptr, 0))) {
        gd::GdVal lv_totalChance = gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0), gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getLucky_1217, nullptr, 0));
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_totalChance}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_mana, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_214, _ca, 2); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicCollar::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__RangerCollar::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__MagicCollar(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__MagicCollar>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MagicCollar = {CLS_Gd__gd_core_items__Exclusive__MagicCollar, "MagicCollar", "res://gd_core_items/Exclusive/MagicCollar.gd", &META_Gd__gd_core_items__RangerCollar, true, _alloc_Gd__gd_core_items__Exclusive__MagicCollar, &Gd__gd_core_items__Exclusive__MagicCollar::get_static_prop_fn, &Gd__gd_core_items__Exclusive__MagicCollar::call_static_fn};

void Gd__gd_core_items__Exclusive__MoltenSpear2::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_totalBlockRemoval = gd::GdVal::from_int(0);
    this->f_blockRemoval = gd::GdVal::null();
    this->f_heatNeeded = gd::GdVal::null();
    this->f_missDamage = gd::GdVal::null();
    this->f_blind = gd::GdVal::null();
    this->f_selfblind = gd::GdVal::null();
    this->f_fireMultiplicity = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__MoltenSpear2::meta() const { return &META_Gd__gd_core_items__Exclusive__MoltenSpear2; }
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear2::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__MoltenSpear2::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__MoltenSpear2::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_totalBlockRemoval_1885: out = this->f_totalBlockRemoval; return true;
        case SYM_GEN_blockRemoval_1801: out = this->f_blockRemoval; return true;
        case SYM_GEN_heatNeeded_1784: out = this->f_heatNeeded; return true;
        case SYM_GEN_missDamage_2311: out = this->f_missDamage; return true;
        case SYM_GEN_blind_1815: out = this->f_blind; return true;
        case SYM_GEN_selfblind_2312: out = this->f_selfblind; return true;
        case SYM_GEN_fireMultiplicity_2310: out = this->f_fireMultiplicity; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MoltenSpear2::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_totalBlockRemoval_1885: this->f_totalBlockRemoval = gd::gd_coerce_int(val); return true;
        case SYM_GEN_blockRemoval_1801: this->f_blockRemoval = val; return true;
        case SYM_GEN_heatNeeded_1784: this->f_heatNeeded = val; return true;
        case SYM_GEN_missDamage_2311: this->f_missDamage = val; return true;
        case SYM_GEN_blind_1815: this->f_blind = val; return true;
        case SYM_GEN_selfblind_2312: this->f_selfblind = val; return true;
        case SYM_GEN_fireMultiplicity_2310: this->f_fireMultiplicity = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MoltenSpear2::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_affectsEmpty_253: return true;
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN_onPreDealDamage_late_902: return true;
        case SYM_GEN_getTypeMultiplicity_78: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MoltenSpear2::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_affectsEmpty_253: out = fn_affectsEmpty(args, argc); return true;
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onPreDealDamage_late_902: out = fn_onPreDealDamage_late(args, argc); return true;
        case SYM_GEN_getTypeMultiplicity_78: out = fn_getTypeMultiplicity(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__MoltenSpear2::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear2::fn_affectsEmpty(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear2::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Fire_2599)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear2::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_totalBlockRemoval = gd::gd_coerce_int(gd::gd_mul(this->f_blockRemoval, gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Fire_2599)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffected_type_427, _ca, 1); })(), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumEmptyAffectedCells_424, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear2::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getHeat_1231, nullptr, 0), this->f_heatNeeded)))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_missDamage}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_159, _ca, 1); })();
            gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_hit_1427, gd::GdVal::from_bool(true));
            (void)([&]() { gd::GdVal _ca[] = {this->f_heatNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useHeat_352, _ca, 1); })();
        }
    }
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_blind}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_211, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_selfblind}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_selfInflictBlind_341, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear2::fn_onPreDealDamage_late(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_totalBlockRemoval}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeBlock_203, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear2::fn_getTypeMultiplicity(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_type, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Fire_2599))))) {
        return this->f_fireMultiplicity;
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {lv_type}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN_getTypeMultiplicity_78, _ca, 1, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear2::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_blockRemoval = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blockremoval", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })();
    this->f_heatNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heatt", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_missDamage = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "missdam", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_blind = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blind", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_selfblind = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blind_self", 10u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_fireMultiplicity = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "fire", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__MoltenSpear2(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__MoltenSpear2>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MoltenSpear2 = {CLS_Gd__gd_core_items__Exclusive__MoltenSpear2, "MoltenSpear2", "res://gd_core_items/Exclusive/MoltenSpear2.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__MoltenSpear2, &Gd__gd_core_items__Exclusive__MoltenSpear2::get_static_prop_fn, &Gd__gd_core_items__Exclusive__MoltenSpear2::call_static_fn};

void Gd__gd_core_items__Exclusive__PiggyPinata::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_piggybankDescriptor = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__PiggyPinata::meta() const { return &META_Gd__gd_core_items__Exclusive__PiggyPinata; }
gd::GdVal Gd__gd_core_items__Exclusive__PiggyPinata::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__PiggyPinata::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__PiggyPinata::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_piggybankDescriptor_2329: out = this->f_piggybankDescriptor; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PiggyPinata::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_piggybankDescriptor_2329: this->f_piggybankDescriptor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PiggyPinata::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onItemRoll_1922: return true;
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_canAffect_global_1918: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PiggyPinata::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onItemRoll_1922: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_canAffect_global_1918: out = fn_canAffect_global(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__PiggyPinata::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__PiggyPinata::fn_onItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PiggyPinata::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canDamage_87, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PiggyPinata::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1214 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1215 = (_t1214.kind == gd::GdVal::Kind::Arr) ? _t1214.arr : nullptr;
        uint32_t _len__t1216 = _t1215 ? _t1215->len : 0u;
        for (uint32_t _t1216 = 0; _t1216 < _len__t1216; ++_t1216) {
            gd::GdVal lv_item = _t1215->data[_t1216];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addCritChancePercent_177, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PiggyPinata::fn_canAffect_global(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {this->f_piggybankDescriptor}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_isA_243, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PiggyPinata::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_piggybankDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Piggybank", 9u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1388), SYM_GEN_getDescriptor_1562, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PiggyPinata(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__PiggyPinata>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PiggyPinata = {CLS_Gd__gd_core_items__Exclusive__PiggyPinata, "PiggyPinata", "res://gd_core_items/Exclusive/PiggyPinata.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__PiggyPinata, &Gd__gd_core_items__Exclusive__PiggyPinata::get_static_prop_fn, &Gd__gd_core_items__Exclusive__PiggyPinata::call_static_fn};

void Gd__gd_core_items__Exclusive__PuzzlebagL::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Bag::init_fields(gd_ctx);
    this->f_healamp = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__PuzzlebagL::meta() const { return &META_Gd__gd_core_items__Exclusive__PuzzlebagL; }
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagL::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Bag::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagL::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__PuzzlebagL::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_healamp_2061: out = this->f_healamp; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagL::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_healamp_2061: this->f_healamp = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagL::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canApplyEffect_916: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_getBagEffect_478: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagL::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canApplyEffect_916: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_getBagEffect_478: out = fn_getBagEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagL::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagL::fn_canApplyEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_toItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_toItem, SYM_GEN_canHealOrLifesteal_290, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagL::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1217 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_923, nullptr, 0));
        gd::GdArr* _t1218 = (_t1217.kind == gd::GdVal::Kind::Arr) ? _t1217.arr : nullptr;
        uint32_t _len__t1219 = _t1218 ? _t1218->len : 0u;
        for (uint32_t _t1219 = 0; _t1219 < _len__t1219; ++_t1219) {
            gd::GdVal lv_item = _t1218->data[_t1219];
            (void)([&]() { gd::GdVal _ca[] = {this->f_healamp}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeHealAmp_302, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagL::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_315, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagL::fn_getBagEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_number = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getName_232, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "_BAGEFFECT", 10u)))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1374), SYM_GEN_tra_2618, _ca, 1); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "p_healamp", 9u)), gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healamp", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), lv_number)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_640, _ca, 3); })();
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagL::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_healamp = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healamp", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PuzzlebagL(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__PuzzlebagL>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PuzzlebagL = {CLS_Gd__gd_core_items__Exclusive__PuzzlebagL, "PuzzlebagL", "res://gd_core_items/Exclusive/PuzzlebagL.gd", &META_Gd__gd_core_items__Bag, true, _alloc_Gd__gd_core_items__Exclusive__PuzzlebagL, &Gd__gd_core_items__Exclusive__PuzzlebagL::get_static_prop_fn, &Gd__gd_core_items__Exclusive__PuzzlebagL::call_static_fn};

void Gd__gd_core_items__Exclusive__Recombobulator::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_stable = gd::GdVal::from_bool(true);
    this->f_idleAnimation = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Recombobulator::meta() const { return &META_Gd__gd_core_items__Exclusive__Recombobulator; }
gd::GdVal Gd__gd_core_items__Exclusive__Recombobulator::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Recombobulator::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Recombobulator::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_stable_2371: out = this->f_stable; return true;
        case SYM_GEN_idleAnimation_2372: out = this->f_idleAnimation; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Recombobulator::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_stable_2371: this->f_stable = val; return true;
        case SYM_GEN_idleAnimation_2372: this->f_idleAnimation = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Recombobulator::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_cacheAffectedItemsForCombat_117: return true;
        case SYM_GEN_readyToFuse_747: return true;
        case SYM_GEN_onFusingFinished_844: return true;
        case SYM_GEN_reactToDropResult_718: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_getCounterValue_2255: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Recombobulator::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_cacheAffectedItemsForCombat_117: out = fn_cacheAffectedItemsForCombat(args, argc); return true;
        case SYM_GEN_readyToFuse_747: out = fn_readyToFuse(args, argc); return true;
        case SYM_GEN_onFusingFinished_844: out = fn_onFusingFinished(args, argc); return true;
        case SYM_GEN_reactToDropResult_718: out = fn_reactToDropResult(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getCounterValue_2255: out = fn_getCounterValue(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Recombobulator::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Recombobulator::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isBag_81, nullptr, 0)))) ? gd::GdVal::from_bool(gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canStartNewRecipe_803, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_item, SYM_GEN_bondedBaseItem_569), gd::GdVal::from_obj(this)))))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Recombobulator::fn_cacheAffectedItemsForCombat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_cacheAffectedItemsForCombat_117, nullptr, 0, _out); return _out; })();
    gd::GdVal lv_arr = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInAffectedCells_cached_421, nullptr, 0);
    { gd::GdVal _t1220 = this->f_cachedAffectedItems; gd::GdVal _t1221 = gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Primary_2580); gd::set_index(gd_ctx, _t1220, _t1221, lv_arr); }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Recombobulator::fn_readyToFuse(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_stable)) {
        return gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, this->f_bondedIngredients, gd::SYM_empty, nullptr, 0)));
    }
    else {
        return gd::GdVal::from_bool(gd::gd_eq(this->f_bondedBaseItem, gd::GdVal::null()));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Recombobulator::fn_onFusingFinished(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_validBonds = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_validBonds}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onFusingFinished_844, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Recombobulator::fn_reactToDropResult(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_dropResult = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_dropResult}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_reactToDropResult_718, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_dropResult}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core_items__Exclusive__Recombobulator::call_static_fn(gd_ctx, SYM_GEN_wasAddedToInventory_655, _ca, 1, _out); return _out; })())) {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Recombobulator::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_367, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_354, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Recombobulator::fn_getCounterValue(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedGoldValue_492, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Recombobulator::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Recombobulator(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Recombobulator>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Recombobulator = {CLS_Gd__gd_core_items__Exclusive__Recombobulator, "Recombobulator", "res://gd_core_items/Exclusive/Recombobulator.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Recombobulator, &Gd__gd_core_items__Exclusive__Recombobulator::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Recombobulator::call_static_fn};

void Gd__gd_core_items__Exclusive__SewingCase::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Bag::init_fields(gd_ctx);
    this->f_bonusSpeed = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SewingCase::meta() const { return &META_Gd__gd_core_items__Exclusive__SewingCase; }
gd::GdVal Gd__gd_core_items__Exclusive__SewingCase::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Bag::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SewingCase::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SewingCase::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_bonusSpeed_1786: out = this->f_bonusSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SewingCase::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bonusSpeed_1786: this->f_bonusSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SewingCase::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canApplyEffect_916: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SewingCase::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canApplyEffect_916: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SewingCase::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SewingCase::fn_canApplyEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_toItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::call_method(gd_ctx, lv_toItem, SYM_GEN_isCrafted_796, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_toItem, SYM_GEN_hasCooldown_93, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_toItem, SYM_GEN_gainsBuffs_294, nullptr, 0)))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SewingCase::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1222 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_923, nullptr, 0));
        gd::GdArr* _t1223 = (_t1222.kind == gd::GdVal::Kind::Arr) ? _t1222.arr : nullptr;
        uint32_t _len__t1224 = _t1223 ? _t1223->len : 0u;
        for (uint32_t _t1224 = 0; _t1224 < _len__t1224; ++_t1224) {
            gd::GdVal lv_item = _t1223->data[_t1224];
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_271, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_allBuffs_195, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SewingCase::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_bonusSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SewingCase(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SewingCase>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SewingCase = {CLS_Gd__gd_core_items__Exclusive__SewingCase, "SewingCase", "res://gd_core_items/Exclusive/SewingCase.gd", &META_Gd__gd_core_items__Bag, true, _alloc_Gd__gd_core_items__Exclusive__SewingCase, &Gd__gd_core_items__Exclusive__SewingCase::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SewingCase::call_static_fn};

void Gd__gd_core_items__Exclusive__Snowcake::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Food::init_fields(gd_ctx);
    this->f_cold = gd::GdVal::null();
    this->f_coldNeeded = gd::GdVal::null();
    this->f_effectDam = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Snowcake::meta() const { return &META_Gd__gd_core_items__Exclusive__Snowcake; }
gd::GdVal Gd__gd_core_items__Exclusive__Snowcake::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Snowcake::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Snowcake::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_cold_1949: out = this->f_cold; return true;
        case SYM_GEN_coldNeeded_2184: out = this->f_coldNeeded; return true;
        case SYM_GEN_effectDam_2417: out = this->f_effectDam; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Snowcake::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_cold_1949: this->f_cold = val; return true;
        case SYM_GEN_coldNeeded_2184: this->f_coldNeeded = val; return true;
        case SYM_GEN_effectDam_2417: this->f_effectDam = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Snowcake::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Snowcake::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Snowcake::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Snowcake::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_cold}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_349, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_getCold_1234, nullptr, 0), this->f_coldNeeded)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_effectDam}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeEffectDamageFactor_1261, _ca, 1); })();
        gd::GdVal lv_dam = gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_minDam_1577);
        gd::GdVal lv_damageRes = ([&]() { gd::GdVal _ca[] = {lv_dam}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealEffectDamage_219, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Snowcake::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_cold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cold", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_coldNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "coldt", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    this->f_effectDam = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "damfactor", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1457, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Snowcake(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Snowcake>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Snowcake = {CLS_Gd__gd_core_items__Exclusive__Snowcake, "Snowcake", "res://gd_core_items/Exclusive/Snowcake.gd", &META_Gd__gd_core_items__Food, true, _alloc_Gd__gd_core_items__Exclusive__Snowcake, &Gd__gd_core_items__Exclusive__Snowcake::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Snowcake::call_static_fn};

void Gd__gd_core_items__Exclusive__SpiritBells::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__LeatherHelm::init_fields(gd_ctx);
    this->f_pets = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_boostedCompanions = gd::GdVal::from_int(0LL);
    this->f_buffFactor = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SpiritBells::meta() const { return &META_Gd__gd_core_items__Exclusive__SpiritBells; }
gd::GdVal Gd__gd_core_items__Exclusive__SpiritBells::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__LeatherHelm::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SpiritBells::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SpiritBells::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_pets_2428: out = this->f_pets; return true;
        case SYM_GEN_boostedCompanions_2447: out = this->f_boostedCompanions; return true;
        case SYM_GEN_buffFactor_2266: out = this->f_buffFactor; return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SpiritBells::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_pets_2428: this->f_pets = val; return true;
        case SYM_GEN_boostedCompanions_2447: this->f_boostedCompanions = val; return true;
        case SYM_GEN_buffFactor_2266: this->f_buffFactor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SpiritBells::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onBought_453: return true;
        case SYM_GEN_getData_634: return true;
        case SYM_GEN_setData_635: return true;
        case SYM_GEN_isAffectingDistinct_252: return true;
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_getBuffDur_1812: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onItemRoll_1922: return true;
        case SYM_GEN_onItemRolled_1923: return true;
        case SYM_GEN_getRelatedItems_457: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SpiritBells::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onBought_453: out = fn_onBought(args, argc); return true;
        case SYM_GEN_getData_634: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_635: out = fn_setData(args, argc); return true;
        case SYM_GEN_isAffectingDistinct_252: out = fn_isAffectingDistinct(args, argc); return true;
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_getBuffDur_1812: out = fn_getBuffDur(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onItemRoll_1922: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_onItemRolled_1923: out = fn_onItemRolled(args, argc); return true;
        case SYM_GEN_getRelatedItems_457: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SpiritBells::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__LeatherHelm::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SpiritBells::fn_onBought(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_boostedCompanions = gd::GdVal::from_int(1LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpiritBells::fn_getData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_boostedCompanions;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpiritBells::fn_setData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_data = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv_data, gd::GdVal::null())))) {
        this->f_boostedCompanions = lv_data;
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpiritBells::fn_isAffectingDistinct(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Primary_2580));
    return gd::GdVal::from_bool(gd::gd_eq(lv_color, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Primary_2580)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpiritBells::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Pet_2598)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpiritBells::fn_getBuffDur(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_dur = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_base", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })();
    lv_dur = gd::gd_add(gd_ctx, lv_dur, gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_bonus", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumDistinctAffectedItems_428, nullptr, 0)));
    return lv_dur;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpiritBells::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffFactor, gd::GdVal::from_int(1000LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_multiplyBuffsLimit_361, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_143, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpiritBells::fn_onItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpiritBells::fn_onItemRolled(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpiritBells::fn_getRelatedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpiritBells::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_buffFactor = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SpiritBells(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SpiritBells>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpiritBells = {CLS_Gd__gd_core_items__Exclusive__SpiritBells, "SpiritBells", "res://gd_core_items/Exclusive/SpiritBells.gd", &META_Gd__gd_core_items__LeatherHelm, true, _alloc_Gd__gd_core_items__Exclusive__SpiritBells, &Gd__gd_core_items__Exclusive__SpiritBells::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SpiritBells::call_static_fn};

void Gd__gd_core_items__Exclusive__SunArmor::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_heatNeeded = gd::GdVal::from_int(0);
    this->f_debuffsCleansed = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SunArmor::meta() const { return &META_Gd__gd_core_items__Exclusive__SunArmor; }
gd::GdVal Gd__gd_core_items__Exclusive__SunArmor::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SunArmor::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SunArmor::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_heatNeeded_1784: out = this->f_heatNeeded; return true;
        case SYM_GEN_debuffsCleansed_2474: out = this->f_debuffsCleansed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SunArmor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_heatNeeded_1784: this->f_heatNeeded = gd::gd_coerce_int(val); return true;
        case SYM_GEN_debuffsCleansed_2474: this->f_debuffsCleansed = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SunArmor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_reactToItemTypeChange_455: return true;
        case SYM_GEN_onAffectedItemAdded_433: return true;
        case SYM_GEN_onAffectedItemRemoved_434: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SunArmor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_reactToItemTypeChange_455: out = fn_reactToItemTypeChange(args, argc); return true;
        case SYM_GEN_onAffectedItemAdded_433: out = fn_onAffectedItemAdded(args, argc); return true;
        case SYM_GEN_onAffectedItemRemoved_434: out = fn_onAffectedItemRemoved(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SunArmor::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SunArmor::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Fire_2599)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Holy_2592)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SunArmor::fn_reactToItemTypeChange(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::gd_in(lv_item, gd::get_index(gd_ctx, this->f_currentAffectedItems, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Primary_2580))))) {
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Fire_2599)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })()))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Holy_2592), gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasDynamicType_239, _ca, 2); })())) : gd::GdVal::from_bool(false)))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_currentAffectedItems, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Primary_2580)), gd::SYM_erase, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Primary_2580)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAffectedItemRemoved_434, _ca, 2); })();
            return gd::GdVal::from_bool(false);
        }
    }
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SunArmor::fn_onAffectedItemAdded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Fire_2599)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_77, _ca, 1); })())) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Holy_2592), gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addDynamicType_240, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SunArmor::fn_onAffectedItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_851), SYM_GEN_Holy_2592), gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_removeDynamicType_241, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SunArmor::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getHeat_1231, nullptr, 0), this->f_heatNeeded)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_heatNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useHeat_352, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_debuffsCleansed, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_354, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "used_heat", 9u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1375), SYM_GEN_emitSignal_1499, _ca, 3); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SunArmor::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_201, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_216, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SunArmor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_heatNeeded = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0));
    this->f_debuffsCleansed = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_264, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SunArmor(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SunArmor>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SunArmor = {CLS_Gd__gd_core_items__Exclusive__SunArmor, "SunArmor", "res://gd_core_items/Exclusive/SunArmor.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__SunArmor, &Gd__gd_core_items__Exclusive__SunArmor::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SunArmor::call_static_fn};

void Gd__gd_core_items__Exclusive__Twine::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_maxHealth = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Twine::meta() const { return &META_Gd__gd_core_items__Exclusive__Twine; }
gd::GdVal Gd__gd_core_items__Exclusive__Twine::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Twine::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Twine::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_maxHealth_1045: out = this->f_maxHealth; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Twine::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_maxHealth_1045: this->f_maxHealth = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Twine::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_canAffect_secondary_285: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onTriggerItemActivated_2378: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Twine::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_285: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onTriggerItemActivated_2378: out = fn_onTriggerItemActivated(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Twine::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Twine::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canActivate_89, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Twine::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_isNeutral_244, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Twine::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1225 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1226 = (_t1225.kind == gd::GdVal::Kind::Arr) ? _t1225.arr : nullptr;
        uint32_t _len__t1227 = _t1226 ? _t1226->len : 0u;
        for (uint32_t _t1227 = 0; _t1227 < _len__t1227; ++_t1227) {
            gd::GdVal lv_triggerItem = _t1226->data[_t1227];
            (void)([&]() { gd::GdVal _ca[] = {lv_triggerItem, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "activated", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onTriggerItemActivated", 22u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Twine::fn_onTriggerItemActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_totalChance = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseChance_166, nullptr, 0);
    lv_totalChance = gd::gd_add(gd_ctx, lv_totalChance, gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_863), SYM_GEN_Secondary_2582)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, _ca, 1); })(), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseChance2_167, nullptr, 0)));
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_totalChance}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, _ca, 1); })())) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_maxHealth, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_315, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Twine::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_maxHealth = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "health", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Twine(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Twine>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Twine = {CLS_Gd__gd_core_items__Exclusive__Twine, "Twine", "res://gd_core_items/Exclusive/Twine.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Twine, &Gd__gd_core_items__Exclusive__Twine::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Twine::call_static_fn};

void Gd__gd_core_items__Exclusive__WolfBadge::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_activated = gd::GdVal::from_bool(false);
    this->f_healthThreshold = gd::GdVal::null();
    this->f_battleRageSpeed = gd::GdVal::null();
    this->f_battleRageDamReduction = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__WolfBadge::meta() const { return &META_Gd__gd_core_items__Exclusive__WolfBadge; }
gd::GdVal Gd__gd_core_items__Exclusive__WolfBadge::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__WolfBadge::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__WolfBadge::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activated_1292: out = this->f_activated; return true;
        case SYM_GEN_healthThreshold_1758: out = this->f_healthThreshold; return true;
        case SYM_GEN_battleRageSpeed_1969: out = this->f_battleRageSpeed; return true;
        case SYM_GEN_battleRageDamReduction_2529: out = this->f_battleRageDamReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__WolfBadge::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activated_1292: this->f_activated = val; return true;
        case SYM_GEN_healthThreshold_1758: this->f_healthThreshold = val; return true;
        case SYM_GEN_battleRageSpeed_1969: this->f_battleRageSpeed = val; return true;
        case SYM_GEN_battleRageDamReduction_2529: this->f_battleRageDamReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__WolfBadge::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onAddToInventory_417: return true;
        case SYM_GEN_onRemoveFromInventory_416: return true;
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_onDamaged_1759: return true;
        case SYM_GEN_onBattleRageStarted_1970: return true;
        case SYM_GEN_onBattleRageEnded_1971: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN_getRelatedItems_457: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__WolfBadge::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onAddToInventory_417: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_416: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDamaged_1759: out = fn_onDamaged(args, argc); return true;
        case SYM_GEN_onBattleRageStarted_1970: out = fn_onBattleRageStarted(args, argc); return true;
        case SYM_GEN_onBattleRageEnded_1971: out = fn_onBattleRageEnded(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN_getRelatedItems_457: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__WolfBadge::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__WolfBadge::fn_onAddToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WolfBadge::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WolfBadge::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_93, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WolfBadge::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_activated = gd::GdVal::from_bool(false);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_damaged", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDamaged", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "battle_rage_started", 19u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBattleRageStarted", 19u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "battle_rage_ended", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBattleRageEnded", 17u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WolfBadge::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_activated)))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_getRelativeHealth_300, nullptr, 0), this->f_healthThreshold)))) {
            this->f_activated = gd::GdVal::from_bool(true);
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), lv_event}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_startBattleRage_1179, _ca, 3); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WolfBadge::fn_onBattleRageStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_battleRageDamReduction}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeDamageResistance_1259, _ca, 1); })();
    {
        gd::GdVal _t1228 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1229 = (_t1228.kind == gd::GdVal::Kind::Arr) ? _t1228.arr : nullptr;
        uint32_t _len__t1230 = _t1229 ? _t1229->len : 0u;
        for (uint32_t _t1230 = 0; _t1230 < _len__t1230; ++_t1230) {
            gd::GdVal lv_item = _t1229->data[_t1230];
            (void)([&]() { gd::GdVal _ca[] = {this->f_battleRageSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_271, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WolfBadge::fn_onBattleRageEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_battleRageDamReduction)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeDamageResistance_1259, _ca, 1); })();
    {
        gd::GdVal _t1231 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
        gd::GdArr* _t1232 = (_t1231.kind == gd::GdVal::Kind::Arr) ? _t1231.arr : nullptr;
        uint32_t _len__t1233 = _t1232 ? _t1232->len : 0u;
        for (uint32_t _t1233 = 0; _t1233 < _len__t1233; ++_t1233) {
            gd::GdVal lv_item = _t1232->data[_t1233];
            (void)([&]() { gd::GdVal _ca[] = {this->f_battleRageSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_reduceSpeed_272, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WolfBadge::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_852), SYM_GEN_High_2601), gd::GdVal::from_int(10LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WolfBadge::fn_getRelatedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WolfBadge::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_healthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    this->f_battleRageSpeed = gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0), gd::GdVal::from_float(100.0));
    this->f_battleRageDamReduction = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_264, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__WolfBadge(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__WolfBadge>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__WolfBadge = {CLS_Gd__gd_core_items__Exclusive__WolfBadge, "WolfBadge", "res://gd_core_items/Exclusive/WolfBadge.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__WolfBadge, &Gd__gd_core_items__Exclusive__WolfBadge::get_static_prop_fn, &Gd__gd_core_items__Exclusive__WolfBadge::call_static_fn};

void Gd__gd_core_items__Gems__Skull::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Gems__Gem::init_fields(gd_ctx);
    this->f_activated = gd::GdVal::from_bool(false);
    this->f_healthThreshold = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Gems__Skull::meta() const { return &META_Gd__gd_core_items__Gems__Skull; }
gd::GdVal Gd__gd_core_items__Gems__Skull::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_gemColor_991: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.912109), gd::GdVal::from_float(0.904984), gd::GdVal::from_float(0.904984)}; return gd::make_color_from_args(_ca, 3); })();
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Gems__Skull::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Gems__Skull::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_activated_1292: out = this->f_activated; return true;
        case SYM_GEN_healthThreshold_1758: out = this->f_healthThreshold; return true;
        case SYM_GEN_gemColor_991: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core_items__Gems__Skull::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activated_1292: this->f_activated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_healthThreshold_1758: this->f_healthThreshold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Gems__Skull::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_prepareInventory_977: return true;
        case SYM_GEN_onOpponentDamaged_1896: return true;
        case SYM_GEN_prepareWeapon_978: return true;
        case SYM_GEN_onAttack_1956: return true;
        case SYM_GEN_prepareArmor_979: return true;
        case SYM_GEN_hasCooldown_93: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::has_own_method(m);
}
bool Gd__gd_core_items__Gems__Skull::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_prepareInventory_977: out = fn_prepareInventory(args, argc); return true;
        case SYM_GEN_onOpponentDamaged_1896: out = fn_onOpponentDamaged(args, argc); return true;
        case SYM_GEN_prepareWeapon_978: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_onAttack_1956: out = fn_onAttack(args, argc); return true;
        case SYM_GEN_prepareArmor_979: out = fn_prepareArmor(args, argc); return true;
        case SYM_GEN_hasCooldown_93: out = fn_hasCooldown(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Gems__Skull::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Gems__Gem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Gems__Skull::fn_prepareInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_activated = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_damaged", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onOpponentDamaged", 17u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Skull::fn_onOpponentDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__healthChange = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_activated)))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_getRelativeHealth_300, nullptr, 0), this->f_healthThreshold)))) {
            this->f_activated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_187, _ca, 1); })(), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_325, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_215, _ca, 2); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Skull::fn_prepareWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_387, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attacked", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onAttack", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_498, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Skull::fn_onAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance2_172, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealRandomBuff_371, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_468, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Skull::fn_prepareArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_969, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeDebuffResistChances_1200, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_969, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_169, nullptr, 0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_72, nullptr, 0), SYM_GEN_changeCritResistance_1153, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Skull::fn_hasCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Skull::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_healthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Gems__Skull(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Gems__Skull>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Gems__Skull = {CLS_Gd__gd_core_items__Gems__Skull, "Skull", "res://gd_core_items/Gems/Skull.gd", &META_Gd__gd_core_items__Gems__Gem, true, _alloc_Gd__gd_core_items__Gems__Skull, &Gd__gd_core_items__Gems__Skull::get_static_prop_fn, &Gd__gd_core_items__Gems__Skull::call_static_fn};

void Gd__gd_core_items__Jynxtorquilla::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_numActivations = gd::GdVal::from_int(0);
    this->f_speedBonus = gd::GdVal::null();
    this->f_maxActivations = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Jynxtorquilla::meta() const { return &META_Gd__gd_core_items__Jynxtorquilla; }
gd::GdVal Gd__gd_core_items__Jynxtorquilla::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Jynxtorquilla::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Jynxtorquilla::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_numActivations_1808: out = this->f_numActivations; return true;
        case SYM_GEN_speedBonus_1781: out = this->f_speedBonus; return true;
        case SYM_GEN_maxActivations_1809: out = this->f_maxActivations; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Jynxtorquilla::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numActivations_1808: this->f_numActivations = gd::gd_coerce_int(val); return true;
        case SYM_GEN_speedBonus_1781: this->f_speedBonus = val; return true;
        case SYM_GEN_maxActivations_1809: this->f_maxActivations = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Jynxtorquilla::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPrepare_121: return true;
        case SYM_GEN_doCooldownEffect_142: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Jynxtorquilla::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_121: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_142: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Jynxtorquilla::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Jynxtorquilla::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_93, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Jynxtorquilla::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_numActivations = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Jynxtorquilla::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_numActivations, this->f_maxActivations)))) {
        {
            gd::GdVal _t1234 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_418, nullptr, 0));
            gd::GdArr* _t1235 = (_t1234.kind == gd::GdVal::Kind::Arr) ? _t1234.arr : nullptr;
            uint32_t _len__t1236 = _t1235 ? _t1235->len : 0u;
            for (uint32_t _t1236 = 0; _t1236 < _len__t1236; ++_t1236) {
                gd::GdVal lv_item = _t1235->data[_t1236];
                (void)([&]() { gd::GdVal _ca[] = {this->f_speedBonus}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_271, _ca, 1); })();
            }
        }
        this->f_numActivations = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_numActivations, gd::GdVal::from_int(1LL)));
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_73, nullptr, 0), SYM_GEN_getLucky_1217, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_263, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeLucky_347, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Jynxtorquilla::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_speedBonus = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_maxActivations = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "max", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_186, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Jynxtorquilla(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Jynxtorquilla>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Jynxtorquilla = {CLS_Gd__gd_core_items__Jynxtorquilla, "Jynxtorquilla", "res://gd_core_items/Jynxtorquilla.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Jynxtorquilla, &Gd__gd_core_items__Jynxtorquilla::get_static_prop_fn, &Gd__gd_core_items__Jynxtorquilla::call_static_fn};

void Gd__gd_core_items__PlatinCustomerCard::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__PlatinCustomerCard::meta() const { return &META_Gd__gd_core_items__PlatinCustomerCard; }
gd::GdVal Gd__gd_core_items__PlatinCustomerCard::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__PlatinCustomerCard::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__PlatinCustomerCard::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__PlatinCustomerCard::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__PlatinCustomerCard::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_284: return true;
        case SYM_GEN_onPreCombatStart_123: return true;
        case SYM_GEN_onCombatStart_930: return true;
        case SYM_GEN_onCalcTradeChance_1729: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__PlatinCustomerCard::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_284: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPreCombatStart_123: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_onCombatStart_930: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onCalcTradeChance_1729: out = fn_onCalcTradeChance(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__PlatinCustomerCard::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__PlatinCustomerCard::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, lv_item, SYM_GEN_getRarity_234, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Rarity_858), SYM_GEN_Legendary_2737)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PlatinCustomerCard::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_425, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_262, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveReflectStacks_198, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_148, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PlatinCustomerCard::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PlatinCustomerCard::fn_onCalcTradeChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PlatinCustomerCard::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__PlatinCustomerCard(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__PlatinCustomerCard>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__PlatinCustomerCard = {CLS_Gd__gd_core_items__PlatinCustomerCard, "PlatinCustomerCard", "res://gd_core_items/PlatinCustomerCard.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__PlatinCustomerCard, &Gd__gd_core_items__PlatinCustomerCard::get_static_prop_fn, &Gd__gd_core_items__PlatinCustomerCard::call_static_fn};

void Gd__gd_core_items__Shovel::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_digUpItems = ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 25); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Stone", 5u)), gd::GdVal::from_int(4LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Garlic", 6u)), gd::GdVal::from_int(3LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Blueberries", 11u)), gd::GdVal::from_int(2LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Lump of Coal", 12u)), gd::GdVal::from_int(3LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Pocket Sand", 11u)), gd::GdVal::from_int(3LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Chipped Ruby", 12u)), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Chipped Sapphire", 16u)), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Chipped Emerald", 15u)), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Chipped Topaz", 13u)), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Chipped Amethyst", 16u)), gd::GdVal::from_int(1LL)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Healing Herbs", 13u)), gd::GdVal::from_float(0.5)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Bag of Stones", 13u)), gd::GdVal::from_float(0.5)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Walrus Tusk", 11u)), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Whetstone", 9u)), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Piggybank", 9u)), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Pan", 3u)), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Customer Card", 13u)), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Gloves of Haste", 15u)), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Dagger", 6u)), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Protective Purse", 16u)), gd::GdVal::from_float(0.1)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Flawed Ruby", 11u)), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Flawed Sapphire", 15u)), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Flawed Emerald", 14u)), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Flawed Topaz", 12u)), gd::GdVal::from_float(0.2)); d->set(gd_ctx.arena, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Flawed Amethyst", 15u)), gd::GdVal::from_float(0.2)); return gd::GdVal::from_dict(d); })();
    this->f_digParticles = gd::GdVal::null();
    this->f_spawnPos = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Shovel::meta() const { return &META_Gd__gd_core_items__Shovel; }
gd::GdVal Gd__gd_core_items__Shovel::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Shovel::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Shovel::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_digUpItems_1882: out = this->f_digUpItems; return true;
        case SYM_GEN_digParticles_1883: out = this->f_digParticles; return true;
        case SYM_GEN_spawnPos_1884: out = this->f_spawnPos; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Shovel::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_digUpItems_1882: this->f_digUpItems = val; return true;
        case SYM_GEN_digParticles_1883: this->f_digParticles = val; return true;
        case SYM_GEN_spawnPos_1884: this->f_spawnPos = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Shovel::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onShopEntered_742: return true;
        case SYM_GEN_onDealtDamage_904: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Shovel::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onShopEntered_742: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onDealtDamage_904: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Shovel::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Shovel::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Shovel::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0))) {
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1424)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_211, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Shovel::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Shovel(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Shovel>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Shovel = {CLS_Gd__gd_core_items__Shovel, "Shovel", "res://gd_core_items/Shovel.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Shovel, &Gd__gd_core_items__Shovel::get_static_prop_fn, &Gd__gd_core_items__Shovel::call_static_fn};

void Gd__gd_core_items__Torch::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_permDamBonus = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Torch::meta() const { return &META_Gd__gd_core_items__Torch; }
gd::GdVal Gd__gd_core_items__Torch::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Torch::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Torch::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_permDamBonus_993: out = this->f_permDamBonus; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Torch::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_permDamBonus_993: this->f_permDamBonus = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Torch::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_941: return true;
        case SYM_GEN__readyInit_138: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Torch::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_941: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_138: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Torch::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Torch::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1430, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_171, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_permDamBonus}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_159, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Torch::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_138, nullptr, 0, _out); return _out; })();
    this->f_permDamBonus = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_261, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Torch(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Torch>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Torch = {CLS_Gd__gd_core_items__Torch, "Torch", "res://gd_core_items/Torch.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Torch, &Gd__gd_core_items__Torch::get_static_prop_fn, &Gd__gd_core_items__Torch::call_static_fn};
