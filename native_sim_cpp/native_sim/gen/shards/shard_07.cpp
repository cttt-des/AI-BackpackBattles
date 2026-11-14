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
#include "../hdrs/Gd__gd_core_items__Exclusive__AmuletofLight.hpp"
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
#include "../hdrs/Gd__gd_core_items__Exclusive__PiggyofRiches.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__PuzzlebagL.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Recombobulator.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SewingCase.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Snowball.hpp"
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
        case SYM_GEN_ammunition_903: out = this->f_ammunition; return true;
        case SYM_GEN_bonusDamage_904: out = this->f_bonusDamage; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Stone::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_ammunition_903: this->f_ammunition = gd::gd_coerce_int(val); return true;
        case SYM_GEN_bonusDamage_904: this->f_bonusDamage = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Stone::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_combatEnd_133: return true;
        case SYM_GEN_setBagOfStones_905: return true;
        case SYM_GEN_onPreDealDamage_late_906: return true;
        case SYM_GEN_preHit_907: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN_onHit_909: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Stone::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_combatEnd_133: out = fn_combatEnd(args, argc); return true;
        case SYM_GEN_setBagOfStones_905: out = fn_setBagOfStones(args, argc); return true;
        case SYM_GEN_onPreDealDamage_late_906: out = fn_onPreDealDamage_late(args, argc); return true;
        case SYM_GEN_preHit_907: out = fn_preHit(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_onHit_909: out = fn_onHit(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Stone::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Stone::fn_combatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_combatEnd_133, nullptr, 0, _out); return _out; })();
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_preHit_907, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Stone::fn_preHit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeBlock_207, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Stone::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(this->f_ammunition, gd::GdVal::from_int(1LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_118, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StaminaResult_1280), SYM_GEN_Sufficient_2605))))) : gd::GdVal::from_bool(false)))) {
        this->f_ammunition = gd::gd_coerce_int(gd::gd_sub(this->f_ammunition, gd::GdVal::from_int(1LL)));
        gd::GdVal lv_res = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_222, nullptr, 0);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_ammunition, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_147, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_383, _ca, 1); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Stone::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onHit_909, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Stone::fn_onHit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Stone::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1459, _ca, 1); })();
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
        case SYM_GEN_bonusDmg_951: out = this->f_bonusDmg; return true;
        case SYM_GEN_bonusDmgPerHit_952: out = this->f_bonusDmgPerHit; return true;
        case SYM_GEN_maxDmg_953: out = this->f_maxDmg; return true;
        default: break;
    }
    return Gd__gd_core__Bow::get_prop(prop, out);
}
bool Gd__gd_core__BowandArrow::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bonusDmg_951: this->f_bonusDmg = gd::gd_coerce_int(val); return true;
        case SYM_GEN_bonusDmgPerHit_952: this->f_bonusDmgPerHit = gd::gd_coerce_int(val); return true;
        case SYM_GEN_maxDmg_953: this->f_maxDmg = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core__Bow::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__BowandArrow::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_hasAttackEffect_297: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onWeaponAttacked_950: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Bow::has_own_method(m);
}
bool Gd__gd_core__BowandArrow::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_hasAttackEffect_297: out = fn_hasAttackEffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onWeaponAttacked_950: out = fn_onWeaponAttacked(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BowandArrow::fn_onWeaponAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        gd::GdVal lv_dmgAdded = gd::GdVal::from_bool(false);
        gd::GdVal lv_attackEffectCount = gd::gd_add(gd_ctx, gd::GdVal::from_int(1LL), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollDoubleAttackEffect_189, nullptr, 0));
        {
            gd::GdVal _t1127 = gd::gd_iter_seq(gd_ctx.arena, lv_attackEffectCount);
            gd::GdArr* _t1128 = (_t1127.kind == gd::GdVal::Kind::Arr) ? _t1127.arr : nullptr;
            uint32_t _len__t1129 = _t1128 ? _t1128->len : 0u;
            for (uint32_t _t1129 = 0; _t1129 < _len__t1129; ++_t1129) {
                gd::GdVal lv_i = _t1128->data[_t1129];
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_bonusDmg, this->f_maxDmg)))) {
                    this->f_bonusDmg = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_bonusDmg, this->f_bonusDmgPerHit));
                    (void)([&]() { gd::GdVal _ca[] = {this->f_bonusDmgPerHit}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_163, _ca, 1); })();
                    lv_dmgAdded = gd::GdVal::from_bool(true);
                }
            }
        }
        if (gd::gd_truth(lv_dmgAdded)) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusDmg, gd::GdVal::from_bool(false), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__BowandArrow::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Bow::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_bonusDmgPerHit = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0));
    this->f_maxDmg = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0));
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
    this->f_flk_delay_cursor = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
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
        case SYM_GEN_PHYSICS_FPS_1374: return gd::GdVal::from_float(60.0);
        case SYM_GEN_PHYSICS_DELTA_1375: return gd::gd_div(gd_ctx, gd::GdVal::from_float(1.0), gd::GdVal::from_float(60.0));
        case SYM_GEN_COMBAT_DELAY_1376: return gd::GdVal::from_float(2.5);
        case SYM_GEN_FATIGUE_TIME_1281: return gd::GdVal::from_int(17LL);
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
        case SYM_GEN_rng_1377: out = this->f_rng; return true;
        case SYM_GEN_util_1378: out = this->f_util; return true;
        case SYM_GEN_bus_1379: out = this->f_bus; return true;
        case SYM_GEN_hooks_1380: out = this->f_hooks; return true;
        case SYM_GEN_combat_log_1381: out = this->f_combat_log; return true;
        case SYM_GEN_player_1284: out = this->f_player; return true;
        case SYM_GEN_opponent_77: out = this->f_opponent; return true;
        case SYM_GEN_fight_ended_1287: out = this->f_fight_ended; return true;
        case SYM_GEN_time_1382: out = this->f_time; return true;
        case SYM_GEN_probe_pass_1383: out = this->f_probe_pass; return true;
        case SYM_GEN_frame_counter_1384: out = this->f_frame_counter; return true;
        case SYM_GEN_combat_time_1288: out = this->f_combat_time; return true;
        case SYM_GEN_below_master_1385: out = this->f_below_master; return true;
        case SYM_GEN_label_rng_enabled_1386: out = this->f_label_rng_enabled; return true;
        case SYM_GEN_lobbies_mode_1387: out = this->f_lobbies_mode; return true;
        case SYM_GEN_custom_health_multiplier_1388: out = this->f_custom_health_multiplier; return true;
        case SYM_GEN_flk_delay_cursor_1389: out = this->f_flk_delay_cursor; return true;
        case SYM_GEN__drawseq_enabled_1390: out = this->f__drawseq_enabled; return true;
        case SYM_GEN_lib_fires_1391: out = this->f_lib_fires; return true;
        case SYM_GEN_combat_1392: out = this->f_combat; return true;
        case SYM_GEN_item_book_1393: out = this->f_item_book; return true;
        case SYM_GEN_sandbag_active_1394: out = this->f_sandbag_active; return true;
        case SYM_GEN_cur_mode_1395: out = this->f_cur_mode; return true;
        case SYM_GEN_cur_round_1396: out = this->f_cur_round; return true;
        case SYM_GEN_rope_speedups_1397: out = this->f_rope_speedups; return true;
        case SYM_GEN_cube_advanced_1398: out = this->f_cube_advanced; return true;
        case SYM_GEN_event_type_keys_1399: out = this->f_event_type_keys; return true;
        case SYM_GEN_class_resources_1400: out = this->f_class_resources; return true;
        case SYM_GEN_unhealingDamageSource_1401: out = this->f_unhealingDamageSource; return true;
        case SYM_GEN_fatigueDamageSource_1402: out = this->f_fatigueDamageSource; return true;
        case SYM_GEN_stealLifeDamageSource_1403: out = this->f_stealLifeDamageSource; return true;
        case SYM_GEN_out_of_stamina_count_1404: out = this->f_out_of_stamina_count; return true;
        case SYM_GEN_warn_unknown_api_1405: out = this->f_warn_unknown_api; return true;
        case SYM_GEN__deferred_1406: out = this->f__deferred; return true;
        case SYM_GEN__timed_1407: out = this->f__timed; return true;
        case SYM_GEN_deferred_flush_enabled_1408: out = this->f_deferred_flush_enabled; return true;
        case SYM_GEN_eb_relay_mirrored_1409: out = this->f_eb_relay_mirrored; return true;
        case SYM_GEN_keyed_stop_clears_seen_1410: out = this->f_keyed_stop_clears_seen; return true;
        case SYM_GEN_keyed_cleanse_biggest_first_1411: out = this->f_keyed_cleanse_biggest_first; return true;
        case SYM_GEN__emptyGrid_1412: out = this->f__emptyGrid; return true;
        case SYM_GEN_PHYSICS_FPS_1374: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_PHYSICS_DELTA_1375: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_COMBAT_DELAY_1376: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_FATIGUE_TIME_1281: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreContext::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_rng_1377: this->f_rng = val; return true;
        case SYM_GEN_util_1378: this->f_util = val; return true;
        case SYM_GEN_bus_1379: this->f_bus = val; return true;
        case SYM_GEN_hooks_1380: this->f_hooks = val; return true;
        case SYM_GEN_combat_log_1381: this->f_combat_log = val; return true;
        case SYM_GEN_player_1284: this->f_player = val; return true;
        case SYM_GEN_opponent_77: this->f_opponent = val; return true;
        case SYM_GEN_fight_ended_1287: this->f_fight_ended = val; return true;
        case SYM_GEN_time_1382: this->f_time = val; return true;
        case SYM_GEN_probe_pass_1383: this->f_probe_pass = val; return true;
        case SYM_GEN_frame_counter_1384: this->f_frame_counter = val; return true;
        case SYM_GEN_combat_time_1288: this->f_combat_time = val; return true;
        case SYM_GEN_below_master_1385: this->f_below_master = val; return true;
        case SYM_GEN_label_rng_enabled_1386: this->f_label_rng_enabled = val; return true;
        case SYM_GEN_lobbies_mode_1387: this->f_lobbies_mode = val; return true;
        case SYM_GEN_custom_health_multiplier_1388: this->f_custom_health_multiplier = val; return true;
        case SYM_GEN_flk_delay_cursor_1389: this->f_flk_delay_cursor = val; return true;
        case SYM_GEN__drawseq_enabled_1390: this->f__drawseq_enabled = val; return true;
        case SYM_GEN_lib_fires_1391: this->f_lib_fires = val; return true;
        case SYM_GEN_combat_1392: this->f_combat = val; return true;
        case SYM_GEN_item_book_1393: this->f_item_book = val; return true;
        case SYM_GEN_sandbag_active_1394: this->f_sandbag_active = val; return true;
        case SYM_GEN_cur_mode_1395: this->f_cur_mode = val; return true;
        case SYM_GEN_cur_round_1396: this->f_cur_round = val; return true;
        case SYM_GEN_rope_speedups_1397: this->f_rope_speedups = val; return true;
        case SYM_GEN_cube_advanced_1398: this->f_cube_advanced = val; return true;
        case SYM_GEN_event_type_keys_1399: this->f_event_type_keys = val; return true;
        case SYM_GEN_class_resources_1400: this->f_class_resources = val; return true;
        case SYM_GEN_unhealingDamageSource_1401: this->f_unhealingDamageSource = val; return true;
        case SYM_GEN_fatigueDamageSource_1402: this->f_fatigueDamageSource = val; return true;
        case SYM_GEN_stealLifeDamageSource_1403: this->f_stealLifeDamageSource = val; return true;
        case SYM_GEN_out_of_stamina_count_1404: this->f_out_of_stamina_count = val; return true;
        case SYM_GEN_warn_unknown_api_1405: this->f_warn_unknown_api = val; return true;
        case SYM_GEN__deferred_1406: this->f__deferred = val; return true;
        case SYM_GEN__timed_1407: this->f__timed = val; return true;
        case SYM_GEN_deferred_flush_enabled_1408: this->f_deferred_flush_enabled = val; return true;
        case SYM_GEN_eb_relay_mirrored_1409: this->f_eb_relay_mirrored = val; return true;
        case SYM_GEN_keyed_stop_clears_seen_1410: this->f_keyed_stop_clears_seen = val; return true;
        case SYM_GEN_keyed_cleanse_biggest_first_1411: this->f_keyed_cleanse_biggest_first = val; return true;
        case SYM_GEN__emptyGrid_1412: this->f__emptyGrid = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreContext::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_set_drawseq_enabled_1413: return true;
        case SYM_GEN_lib_fires_tick_1414: return true;
        case SYM_GEN_set_custom_health_multiplier_1415: return true;
        case gd::SYM__init: return true;
        case gd::SYM_set_state: return true;
        case SYM_GEN__newDamageSource_1416: return true;
        case SYM_GEN_getCharacterFromId_1417: return true;
        case SYM_GEN_otherCharacter_1418: return true;
        case SYM_GEN_advancePhysicsFrame_1419: return true;
        case SYM_GEN_callDelayed_1420: return true;
        case SYM_GEN__flushTimed_1421: return true;
        case SYM_GEN_defer_1422: return true;
        case SYM_GEN_hasDeferred_1423: return true;
        case SYM_GEN_flushDeferred_1424: return true;
        case SYM_GEN_emptyGrid_1425: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreContext::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_set_drawseq_enabled_1413: out = fn_set_drawseq_enabled(args, argc); return true;
        case SYM_GEN_lib_fires_tick_1414: out = fn_lib_fires_tick(args, argc); return true;
        case SYM_GEN_set_custom_health_multiplier_1415: out = fn_set_custom_health_multiplier(args, argc); return true;
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case gd::SYM_set_state: out = fn_set_state(args, argc); return true;
        case SYM_GEN__newDamageSource_1416: out = fn__newDamageSource(args, argc); return true;
        case SYM_GEN_getCharacterFromId_1417: out = fn_getCharacterFromId(args, argc); return true;
        case SYM_GEN_otherCharacter_1418: out = fn_otherCharacter(args, argc); return true;
        case SYM_GEN_advancePhysicsFrame_1419: out = fn_advancePhysicsFrame(args, argc); return true;
        case SYM_GEN_callDelayed_1420: out = fn_callDelayed(args, argc); return true;
        case SYM_GEN__flushTimed_1421: out = fn__flushTimed(args, argc); return true;
        case SYM_GEN_defer_1422: out = fn_defer(args, argc); return true;
        case SYM_GEN_hasDeferred_1423: out = fn_hasDeferred(args, argc); return true;
        case SYM_GEN_flushDeferred_1424: out = fn_flushDeferred(args, argc); return true;
        case SYM_GEN_emptyGrid_1425: out = fn_emptyGrid(args, argc); return true;
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
    gd::set_prop(gd_ctx, this->f_rng, SYM_GEN_draw_seq_1636, (gd::gd_truth(lv_v) ? (gd::GdVal::from_int(0LL)) : (gd::gd_neg(gd::GdVal::from_int(1LL)))));
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
        gd::GdVal _t1130 = gd::gd_iter_seq(gd_ctx.arena, this->f_lib_fires);
        gd::GdArr* _t1131 = (_t1130.kind == gd::GdVal::Kind::Arr) ? _t1130.arr : nullptr;
        uint32_t _len__t1132 = _t1131 ? _t1131->len : 0u;
        for (uint32_t _t1132 = 0; _t1132 < _len__t1132; ++_t1132) {
            gd::GdVal lv_e = _t1131->data[_t1132];
            { gd::GdVal _t1133 = lv_e; gd::GdVal _t1134 = gd::GdVal::from_int(0LL); gd::set_index(gd_ctx, _t1133, _t1134, gd::gd_sub(gd::get_index(gd_ctx, lv_e, gd::GdVal::from_int(0LL)), lv_delta)); }
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
        gd::GdVal _t1135 = gd::gd_iter_seq(gd_ctx.arena, lv_due);
        gd::GdArr* _t1136 = (_t1135.kind == gd::GdVal::Kind::Arr) ? _t1135.arr : nullptr;
        uint32_t _len__t1137 = _t1136 ? _t1136->len : 0u;
        for (uint32_t _t1137 = 0; _t1137 < _len__t1137; ++_t1137) {
            gd::GdVal lv_e = _t1136->data[_t1137];
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
    gd::set_prop(gd_ctx, this->f_util, SYM_GEN__ctx_1325, gd::GdVal::from_obj(this));
    this->f_hooks = (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ne(lv__hooks, gd::GdVal::null()))) ? (lv__hooks) : (gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreHooks), gd::SYM_new, nullptr, 0)));
    this->f_bus = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreEventBus), gd::SYM_new, nullptr, 0);
    gd::set_prop(gd_ctx, this->f_bus, SYM_GEN__ctx_1325, gd::GdVal::from_obj(this));
    this->f_combat_log = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCombatLog), gd::SYM_new, nullptr, 0);
    gd::set_prop(gd_ctx, this->f_combat_log, SYM_GEN__ctx_1325, gd::GdVal::from_obj(this));
    this->f_item_book = gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreItemBook), gd::SYM_new, nullptr, 0);
    gd::set_prop(gd_ctx, this->f_item_book, SYM_GEN__ctx_1325, gd::GdVal::from_obj(this));
    this->f_stealLifeDamageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Effect_2559), gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_effectFlags_1448)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__newDamageSource_1416, _ca, 3); })();
    this->f_unhealingDamageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Unhealing_2695), gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_unhealingFlags_1449)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__newDamageSource_1416, _ca, 3); })();
    this->f_fatigueDamageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Type_855), SYM_GEN_Fatigue_2687), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), SYM_GEN_Flags_1474), SYM_GEN_CanBeBlocked_2756)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__newDamageSource_1416, _ca, 3); })();
    this->f_event_type_keys = ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366)}; return gd::call_method(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreUtil), SYM_GEN_invertDictionary_1705, _ca, 1); })();
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
    gd::set_prop(gd_ctx, lv_src, SYM_GEN__rng_1457, this->f_rng);
    (void)([&]() { gd::GdVal _ca[] = {lv_origin, lv_type}; return gd::call_method(gd_ctx, lv_src, SYM_GEN_init_1021, _ca, 2); })();
    gd::set_prop(gd_ctx, lv_src, SYM_GEN_flags_1456, lv_flags);
    return lv_src;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreContext::fn_getCharacterFromId(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_playerId = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_playerId = gd::gd_coerce_int(lv_playerId);
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_playerId, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreCharacter), SYM_GEN_ID_1279), SYM_GEN_PLAYER_2540)))) ? (this->f_player) : (this->f_opponent));
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
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : (Gd__gd_core__CoreContext::get_static_const_or_enum(gd_ctx, SYM_GEN_PHYSICS_DELTA_1375));
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
        gd::GdVal _t1138 = gd::gd_iter_seq(gd_ctx.arena, this->f__timed);
        gd::GdArr* _t1139 = (_t1138.kind == gd::GdVal::Kind::Arr) ? _t1138.arr : nullptr;
        uint32_t _len__t1140 = _t1139 ? _t1139->len : 0u;
        for (uint32_t _t1140 = 0; _t1140 < _len__t1140; ++_t1140) {
            gd::GdVal lv_call = _t1139->data[_t1140];
            { gd::GdVal _t1141 = lv_call; gd::GdVal _t1142 = gd::GdVal::from_int(2LL); gd::set_index(gd_ctx, _t1141, _t1142, gd::gd_sub(gd::get_index(gd_ctx, lv_call, gd::GdVal::from_int(2LL)), Gd__gd_core__CoreContext::get_static_const_or_enum(gd_ctx, SYM_GEN_PHYSICS_DELTA_1375))); }
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
        gd::GdVal _t1143 = gd::gd_iter_seq(gd_ctx.arena, lv_due);
        gd::GdArr* _t1144 = (_t1143.kind == gd::GdVal::Kind::Arr) ? _t1143.arr : nullptr;
        uint32_t _len__t1145 = _t1144 ? _t1144->len : 0u;
        for (uint32_t _t1145 = 0; _t1145 < _len__t1145; ++_t1145) {
            gd::GdVal lv_call = _t1144->data[_t1145];
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
    if (gd::gd_truth(gd::call_method(gd_ctx, this->f__deferred, gd::SYM_empty, nullptr, 0))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_batch = this->f__deferred;
    this->f__deferred = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1146 = gd::gd_iter_seq(gd_ctx.arena, lv_batch);
        gd::GdArr* _t1147 = (_t1146.kind == gd::GdVal::Kind::Arr) ? _t1146.arr : nullptr;
        uint32_t _len__t1148 = _t1147 ? _t1147->len : 0u;
        for (uint32_t _t1148 = 0; _t1148 < _len__t1148; ++_t1148) {
            gd::GdVal lv_call = _t1147->data[_t1148];
            gd::GdVal lv_obj = gd::get_index(gd_ctx, lv_call, gd::GdVal::from_int(0LL));
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_obj, gd::GdVal::null())))) {
                continue;
            }
            (void)([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, lv_call, gd::GdVal::from_int(1LL)), gd::get_index(gd_ctx, lv_call, gd::GdVal::from_int(2LL))}; return gd::call_method(gd_ctx, lv_obj, gd::SYM_callv, _ca, 2); })();
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
        case SYM_GEN_dict_1714: out = this->f_dict; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreUtil__INNER__DictSorter::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_dict_1714: this->f_dict = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreUtil__INNER__DictSorter::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_sort_1715: return true;
        case SYM_GEN_sort_reverse_1716: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreUtil__INNER__DictSorter::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_sort_1715: out = fn_sort(args, argc); return true;
        case SYM_GEN_sort_reverse_1716: out = fn_sort_reverse(args, argc); return true;
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
        case SYM_GEN_hatchParticles_1765: out = this->f_hatchParticles; return true;
        case SYM_GEN_firePulse_1766: out = this->f_firePulse; return true;
        case SYM_GEN_whelpName_1767: out = this->f_whelpName; return true;
        case SYM_GEN_roundsToHatch_1768: out = this->f_roundsToHatch; return true;
        case SYM_GEN_reflectionStacks_1769: out = this->f_reflectionStacks; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__DragonEgg::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_hatchParticles_1765: this->f_hatchParticles = val; return true;
        case SYM_GEN_firePulse_1766: this->f_firePulse = val; return true;
        case SYM_GEN_whelpName_1767: this->f_whelpName = val; return true;
        case SYM_GEN_roundsToHatch_1768: this->f_roundsToHatch = val; return true;
        case SYM_GEN_reflectionStacks_1769: this->f_reflectionStacks = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__DragonEgg::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getData_638: return true;
        case SYM_GEN_setData_639: return true;
        case SYM_GEN_updateEgg_1770: return true;
        case SYM_GEN_isNextToNest_1771: return true;
        case SYM_GEN_readyToTransform_753: return true;
        case SYM_GEN_canHatch_1772: return true;
        case SYM_GEN_shopEntered_745: return true;
        case SYM_GEN_startHatching_1773: return true;
        case SYM_GEN_hatch_1774: return true;
        case SYM_GEN_hatch_deferred_1775: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__DragonEgg::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getData_638: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_639: out = fn_setData(args, argc); return true;
        case SYM_GEN_updateEgg_1770: out = fn_updateEgg(args, argc); return true;
        case SYM_GEN_isNextToNest_1771: out = fn_isNextToNest(args, argc); return true;
        case SYM_GEN_readyToTransform_753: out = fn_readyToTransform(args, argc); return true;
        case SYM_GEN_canHatch_1772: out = fn_canHatch(args, argc); return true;
        case SYM_GEN_shopEntered_745: out = fn_shopEntered(args, argc); return true;
        case SYM_GEN_startHatching_1773: out = fn_startHatching(args, argc); return true;
        case SYM_GEN_hatch_1774: out = fn_hatch(args, argc); return true;
        case SYM_GEN_hatch_deferred_1775: out = fn_hatch_deferred(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateEgg_1770, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DragonEgg::fn_updateEgg(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canHatch_1772, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.0), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_793, _ca, 2); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_sub(gd::GdVal::from_float(1.0), gd::gd_div(gd_ctx, this->f_roundsToHatch, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0))), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_793, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DragonEgg::fn_isNextToNest(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_placed)) {
        {
            gd::GdVal _t1149 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1512, nullptr, 0));
            gd::GdArr* _t1150 = (_t1149.kind == gd::GdVal::Kind::Arr) ? _t1149.arr : nullptr;
            uint32_t _len__t1151 = _t1150 ? _t1150->len : 0u;
            for (uint32_t _t1151 = 0; _t1151 < _len__t1151; ++_t1151) {
                gd::GdVal lv_item = _t1150->data[_t1151];
                if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, lv_item, SYM_GEN_getName_236, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Dragon Nest", 11u)))))) {
                    return gd::gd_in(gd::GdVal::from_obj(this), gd::call_method(gd_ctx, lv_item, SYM_GEN_getAffectedItems_422, nullptr, 0));
                }
            }
        }
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DragonEgg::fn_readyToTransform(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canHatch_1772, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DragonEgg::fn_canHatch(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_roundsToHatch, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_roundsToHatch, gd::GdVal::from_int(1LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isNextToNest_1771, nullptr, 0))) : gd::GdVal::from_bool(false)))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DragonEgg::fn_shopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_craft = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_craft = gd::gd_coerce_bool(lv_craft);
    (void)([&]() { gd::GdVal _ca[] = {lv_craft}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN_shopEntered_745, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DragonEgg::fn_startHatching(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "hatch", 5u)), gd::gd_sub(Gd__gd_core__DragonEgg::get_static_const_or_enum(gd_ctx, SYM_GEN_TRANSFORMATION_DUR_606), gd::GdVal::from_float(0.1))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_callDelayed_1420, _ca, 3); })();
    {
        gd::GdVal _t1152 = gd::gd_iter_seq(gd_ctx.arena, this->f_shadows);
        gd::GdArr* _t1153 = (_t1152.kind == gd::GdVal::Kind::Arr) ? _t1152.arr : nullptr;
        uint32_t _len__t1154 = _t1153 ? _t1153->len : 0u;
        for (uint32_t _t1154 = 0; _t1154 < _len__t1154; ++_t1154) {
            gd::GdVal lv_shadow = _t1153->data[_t1154];
            gd::set_prop(gd_ctx, lv_shadow, SYM_GEN_offset_516, gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(138LL))).as_float()));
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DragonEgg::fn_hatch(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "hatch_deferred", 14u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_defer_1422, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DragonEgg::fn_hatch_deferred(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DragonEgg::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_roundsToHatch = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateEgg_1770, nullptr, 0);
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
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__HealingHerbs::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__HealingHerbs::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__HealingHerbs::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_383, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HealingHerbs::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_particleTimer_999: out = this->f_particleTimer; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_blindAmount_1814: out = this->f_blindAmount; return true;
        default: break;
    }
    return Gd__gd_core__Goobert::get_prop(prop, out);
}
bool Gd__gd_core__LightGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_particleTimer_999: this->f_particleTimer = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_blindAmount_1814: this->f_blindAmount = val; return true;
        default: break;
    }
    return Gd__gd_core__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__LightGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onCombatEnd_134: return true;
        case SYM_GEN_onParticleTimeout_1000: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Goobert::has_own_method(m);
}
bool Gd__gd_core__LightGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onCombatEnd_134: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onParticleTimeout_1000: out = fn_onParticleTimeout(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__LightGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__LightGoobert::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LightGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, nullptr, 0);
    gd::GdVal lv_duration = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_blind", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_EventType_1366), SYM_GEN_Blind_2568), this->f_blindAmount, lv_duration}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacksTemporary_204, _ca, 4); })();
    (void)gd::call_method(gd_ctx, this->f_particleTimer, SYM_GEN_stop_1686, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {lv_duration}; return gd::call_method(gd_ctx, this->f_particleTimer, SYM_GEN_start_1685, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LightGoobert::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_particleTimer, SYM_GEN_stop_1686, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LightGoobert::fn_onParticleTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__LightGoobert::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_particleTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "ParticleTimer", 13u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onParticleTimeout", 17u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_137, _ca, 3); })();
    this->f_blindAmount = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0);
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
        case SYM_GEN_onTriggerPotion_1754: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onOpponentHeal_1862: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Potion::has_own_method(m);
}
bool Gd__gd_core__PestilenceFlask::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1754: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onOpponentHeal_1862: out = fn_onOpponentHeal(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_213, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_selfInflictPoison_214, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PestilenceFlask::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_healed", 16u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onOpponentHeal", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PestilenceFlask::fn_onOpponentHeal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_923, nullptr, 0))) {
        return gd::GdVal::null();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drink_1752, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_triggerPotion_1755, _ca, 1); })();
    gd::GdVal lv_affected = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_affected, gd::SYM_empty, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL)), SYM_GEN_triggerPotion_1755, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::get_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL)), SYM_GEN_miniActivate_472, nullptr, 0);
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PestilenceFlask::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Potion::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_itemsInside_1875: out = this->f_itemsInside; return true;
        default: break;
    }
    return Gd__gd_core__Bag::get_prop(prop, out);
}
bool Gd__gd_core__RangerBag::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_itemsInside_1875: this->f_itemsInside = val; return true;
        default: break;
    }
    return Gd__gd_core__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__RangerBag::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onLuckyChanged_901: return true;
        case SYM_GEN_canApplyEffect_920: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Bag::has_own_method(m);
}
bool Gd__gd_core__RangerBag::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onLuckyChanged_901: out = fn_onLuckyChanged(args, argc); return true;
        case SYM_GEN_canApplyEffect_920: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__RangerBag::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__RangerBag::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_itemsInside = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0), gd::SYM_empty, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_lucky_changed", 23u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onLuckyChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    }
    {
        gd::GdVal _t1155 = gd::gd_iter_seq(gd_ctx.arena, this->f_itemsInside);
        gd::GdArr* _t1156 = (_t1155.kind == gd::GdVal::Kind::Arr) ? _t1155.arr : nullptr;
        uint32_t _len__t1157 = _t1156 ? _t1156->len : 0u;
        for (uint32_t _t1157 = 0; _t1157 < _len__t1157; ++_t1157) {
            gd::GdVal lv_item = _t1156->data[_t1157];
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeCritChancePercent_183, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RangerBag::fn_onLuckyChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_change = gd::gd_mul(lv_amount, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_174, nullptr, 0));
    {
        gd::GdVal _t1158 = gd::gd_iter_seq(gd_ctx.arena, this->f_itemsInside);
        gd::GdArr* _t1159 = (_t1158.kind == gd::GdVal::Kind::Arr) ? _t1158.arr : nullptr;
        uint32_t _len__t1160 = _t1159 ? _t1159->len : 0u;
        for (uint32_t _t1160 = 0; _t1160 < _len__t1160; ++_t1160) {
            gd::GdVal lv_item = _t1159->data[_t1160];
            (void)([&]() { gd::GdVal _ca[] = {lv_change}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeCritChancePercent_183, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RangerBag::fn_canApplyEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_toItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_toItem, SYM_GEN_canDamage_91, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__RangerBag::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Bag::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_onTriggerPotion_1754: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onBlockChanged_1891: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Potion::has_own_method(m);
}
bool Gd__gd_core__StoneSkinPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1754: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onBlockChanged_1891: out = fn_onBlockChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_206, nullptr, 0), lv_triggerEvent}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_healthToBlock_330, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StoneSkinPotion::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_block_changed", 23u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBlockChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StoneSkinPotion::fn_onBlockChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_923, nullptr, 0))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getBlock_206, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0))))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consumePotion_1753, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StoneSkinPotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Potion::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_inactiveTexture_1907: out = this->f_inactiveTexture; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__VampiricGloves::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_inactiveTexture_1907: this->f_inactiveTexture = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__VampiricGloves::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__VampiricGloves::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_97, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__VampiricGloves::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__VampiricGloves::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_212, _ca, 1); })();
    gd::GdVal lv_bonusSpeed = gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0), gd::GdVal::from_int(100LL));
    {
        gd::GdVal _t1161 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1162 = (_t1161.kind == gd::GdVal::Kind::Arr) ? _t1161.arr : nullptr;
        uint32_t _len__t1163 = _t1162 ? _t1162->len : 0u;
        for (uint32_t _t1163 = 0; _t1163 < _len__t1163; ++_t1163) {
            gd::GdVal lv_item = _t1162->data[_t1163];
            (void)([&]() { gd::GdVal _ca[] = {lv_bonusSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_275, _ca, 1); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_147, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__VampiricGloves::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__VampiricGloves::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv_active)) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateShadowTexture_789, nullptr, 0);
    }
    else {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateShadowTexture_789, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__VampiricGloves::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_BagTiles_933: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Bag_BagTiles);
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
        case SYM_GEN_bagTilemapPosition_914: out = this->f_bagTilemapPosition; return true;
        case SYM_GEN_cachedAffectedInsideItems_915: out = this->f_cachedAffectedInsideItems; return true;
        case SYM_GEN_cachedInsideItems_916: out = this->f_cachedInsideItems; return true;
        case SYM_GEN_bagTilemap_917: out = this->f_bagTilemap; return true;
        case SYM_GEN_border_918: out = this->f_border; return true;
        case SYM_GEN_BagTiles_933: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Bag_BagTiles); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Bag::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bagTilemapPosition_914: this->f_bagTilemapPosition = val; return true;
        case SYM_GEN_cachedAffectedInsideItems_915: this->f_cachedAffectedInsideItems = val; return true;
        case SYM_GEN_cachedInsideItems_916: this->f_cachedInsideItems = val; return true;
        case SYM_GEN_bagTilemap_917: this->f_bagTilemap = val; return true;
        case SYM_GEN_border_918: this->f_border = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Bag::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getHoverPriority_692: return true;
        case SYM_GEN_isBag_85: return true;
        case SYM_GEN_showBagBorderForItem_919: return true;
        case SYM_GEN_canApplyEffect_920: return true;
        case SYM_GEN_canBePicked_739: return true;
        case SYM_GEN_canBeLocked_821: return true;
        case SYM_GEN_resetZ_452: return true;
        case SYM_GEN_addToInventory_122: return true;
        case SYM_GEN_getBagLayerPriority_921: return true;
        case SYM_GEN_hasBagEffect_922: return true;
        case SYM_GEN__process_682: return true;
        case SYM_GEN_reactToDropResult_722: return true;
        case SYM_GEN_onRemoveFromInventory_420: return true;
        case SYM_GEN_getTopLeftGlobal_655: return true;
        case SYM_GEN_getBottomRightGlobal_656: return true;
        case SYM_GEN_isEmpty_923: return true;
        case SYM_GEN_getItemsInside_924: return true;
        case SYM_GEN_getEmptyCells_925: return true;
        case SYM_GEN_getEmptyGlobalPositions_926: return true;
        case SYM_GEN_getAffectedItemsInside_927: return true;
        case SYM_GEN_previewCanAffect_475: return true;
        case SYM_GEN_prepare_124: return true;
        case SYM_GEN_combatToShop_744: return true;
        case SYM_GEN_getCraftableNeighbors_494: return true;
        case SYM_GEN_onItemAdded_439: return true;
        case SYM_GEN_onAffectedItemInsideAdded_928: return true;
        case SYM_GEN_onItemRemoved_440: return true;
        case SYM_GEN_onAffectedItemInsideRemoved_929: return true;
        case SYM_GEN_pushItemsInsideToStorage_400: return true;
        case SYM_GEN_onDraggedWithParentStart_718: return true;
        case SYM_GEN_onDraggedWithParentEnd_720: return true;
        case SYM_GEN_getNumAffectedInside_930: return true;
        case SYM_GEN_getNumAffectedInside_type_931: return true;
        case SYM_GEN_getBagMultiplicity_932: return true;
        case SYM_GEN_discard_764: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Bag::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getHoverPriority_692: out = fn_getHoverPriority(args, argc); return true;
        case SYM_GEN_isBag_85: out = fn_isBag(args, argc); return true;
        case SYM_GEN_showBagBorderForItem_919: out = fn_showBagBorderForItem(args, argc); return true;
        case SYM_GEN_canApplyEffect_920: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN_canBePicked_739: out = fn_canBePicked(args, argc); return true;
        case SYM_GEN_canBeLocked_821: out = fn_canBeLocked(args, argc); return true;
        case SYM_GEN_resetZ_452: out = fn_resetZ(args, argc); return true;
        case SYM_GEN_addToInventory_122: out = fn_addToInventory(args, argc); return true;
        case SYM_GEN_getBagLayerPriority_921: out = fn_getBagLayerPriority(args, argc); return true;
        case SYM_GEN_hasBagEffect_922: out = fn_hasBagEffect(args, argc); return true;
        case SYM_GEN__process_682: out = fn__process(args, argc); return true;
        case SYM_GEN_reactToDropResult_722: out = fn_reactToDropResult(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_420: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_getTopLeftGlobal_655: out = fn_getTopLeftGlobal(args, argc); return true;
        case SYM_GEN_getBottomRightGlobal_656: out = fn_getBottomRightGlobal(args, argc); return true;
        case SYM_GEN_isEmpty_923: out = fn_isEmpty(args, argc); return true;
        case SYM_GEN_getItemsInside_924: out = fn_getItemsInside(args, argc); return true;
        case SYM_GEN_getEmptyCells_925: out = fn_getEmptyCells(args, argc); return true;
        case SYM_GEN_getEmptyGlobalPositions_926: out = fn_getEmptyGlobalPositions(args, argc); return true;
        case SYM_GEN_getAffectedItemsInside_927: out = fn_getAffectedItemsInside(args, argc); return true;
        case SYM_GEN_previewCanAffect_475: out = fn_previewCanAffect(args, argc); return true;
        case SYM_GEN_prepare_124: out = fn_prepare(args, argc); return true;
        case SYM_GEN_combatToShop_744: out = fn_combatToShop(args, argc); return true;
        case SYM_GEN_getCraftableNeighbors_494: out = fn_getCraftableNeighbors(args, argc); return true;
        case SYM_GEN_onItemAdded_439: out = fn_onItemAdded(args, argc); return true;
        case SYM_GEN_onAffectedItemInsideAdded_928: out = fn_onAffectedItemInsideAdded(args, argc); return true;
        case SYM_GEN_onItemRemoved_440: out = fn_onItemRemoved(args, argc); return true;
        case SYM_GEN_onAffectedItemInsideRemoved_929: out = fn_onAffectedItemInsideRemoved(args, argc); return true;
        case SYM_GEN_pushItemsInsideToStorage_400: out = fn_pushItemsInsideToStorage(args, argc); return true;
        case SYM_GEN_onDraggedWithParentStart_718: out = fn_onDraggedWithParentStart(args, argc); return true;
        case SYM_GEN_onDraggedWithParentEnd_720: out = fn_onDraggedWithParentEnd(args, argc); return true;
        case SYM_GEN_getNumAffectedInside_930: out = fn_getNumAffectedInside(args, argc); return true;
        case SYM_GEN_getNumAffectedInside_type_931: out = fn_getNumAffectedInside_type(args, argc); return true;
        case SYM_GEN_getBagMultiplicity_932: out = fn_getBagMultiplicity(args, argc); return true;
        case SYM_GEN_discard_764: out = fn_discard(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
        return Gd__gd_core_items__Bag::get_static_const_or_enum(gd_ctx, SYM_GEN_DRAG_PRIORITY_527);
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
    return (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isBag_85, nullptr, 0)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_920, _ca, 1); })())) : gd::GdVal::from_bool(false));
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
    (void)([&]() { gd::GdVal _ca[] = {lv__inventory, lv__occupiedCells, lv__placedByPlayer}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_addToInventory_122, _ca, 3, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_getBagLayerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getRarity_238, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Rarity_862), SYM_GEN_Unique_2757))))) {
        return gd::GdVal::from_int(2LL);
    }
    if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasBagEffect_922, nullptr, 0))) {
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
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_player_1284), SYM_GEN_INVENTORY_1093), SYM_GEN_canAddBag_2758, _ca, 1); })())) {
        }
        else {
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_reactToDropResult(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_result = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_result}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_reactToDropResult_722, _ca, 1, _out); return _out; })();
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
    return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0), gd::SYM_empty, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_getItemsInside(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, this->f_cachedInsideItems, gd::SYM_empty, nullptr, 0))))) {
        return this->f_cachedInsideItems;
    }
    return ([&]() { gd::GdVal _ca[] = {this->f_occupiedCells}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItemsInCells_1517, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_getEmptyCells(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_emptyCells = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1164 = gd::gd_iter_seq(gd_ctx.arena, this->f_occupiedCells);
        gd::GdArr* _t1165 = (_t1164.kind == gd::GdVal::Kind::Arr) ? _t1164.arr : nullptr;
        uint32_t _len__t1166 = _t1165 ? _t1165->len : 0u;
        for (uint32_t _t1166 = 0; _t1166 < _len__t1166; ++_t1166) {
            gd::GdVal lv_cell = _t1165->data[_t1166];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_cell}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_isCellEmpty_1514, _ca, 1); })())) {
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
        gd::GdVal _t1167 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getEmptyCells_925, nullptr, 0));
        gd::GdArr* _t1168 = (_t1167.kind == gd::GdVal::Kind::Arr) ? _t1167.arr : nullptr;
        uint32_t _len__t1169 = _t1168 ? _t1168->len : 0u;
        for (uint32_t _t1169 = 0; _t1169 < _len__t1169; ++_t1169) {
            gd::GdVal lv_cell = _t1168->data[_t1169];
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {lv_cell, gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_cellToGlobalPos_2759, _ca, 2); })()}; return gd::call_method(gd_ctx, lv_positions, gd::SYM_push_back, _ca, 1); })();
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
        gd::GdVal _t1170 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0));
        gd::GdArr* _t1171 = (_t1170.kind == gd::GdVal::Kind::Arr) ? _t1170.arr : nullptr;
        uint32_t _len__t1172 = _t1171 ? _t1171->len : 0u;
        for (uint32_t _t1172 = 0; _t1172 < _len__t1172; ++_t1172) {
            gd::GdVal lv_item = _t1171->data[_t1172];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_920, _ca, 1); })())) {
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
    this->f_cachedInsideItems = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0);
    {
        gd::GdVal _t1173 = gd::gd_iter_seq(gd_ctx.arena, this->f_cachedInsideItems);
        gd::GdArr* _t1174 = (_t1173.kind == gd::GdVal::Kind::Arr) ? _t1173.arr : nullptr;
        uint32_t _len__t1175 = _t1174 ? _t1174->len : 0u;
        for (uint32_t _t1175 = 0; _t1175 < _len__t1175; ++_t1175) {
            gd::GdVal lv_item = _t1174->data[_t1175];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_920, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, this->f_cachedAffectedInsideItems, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_prepare_124, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_combatToShop(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_cachedAffectedInsideItems, gd::SYM_clear, nullptr, 0);
    (void)gd::call_method(gd_ctx, this->f_cachedInsideItems, gd::SYM_clear, nullptr, 0);
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_combatToShop_744, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_getCraftableNeighbors(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_craftableItems = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t1176 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0));
        gd::GdArr* _t1177 = (_t1176.kind == gd::GdVal::Kind::Arr) ? _t1176.arr : nullptr;
        uint32_t _len__t1178 = _t1177 ? _t1177->len : 0u;
        for (uint32_t _t1178 = 0; _t1178 < _len__t1178; ++_t1178) {
            gd::GdVal lv_item = _t1177->data[_t1178];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isAvailableForCrafting_495, nullptr, 0))) {
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
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onItemAdded_439, _ca, 1, _out); return _out; })();
    if (gd::gd_truth((gd::gd_truth(gd::gd_in(lv_item, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_920, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        if (gd::gd_truth(gd::get_prop(gd_ctx, lv_item, SYM_GEN_placedByPlayer_52))) {
        }
        (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAffectedItemInsideAdded_928, _ca, 1); })();
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
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onItemRemoved_440, _ca, 1, _out); return _out; })();
    if (gd::gd_truth((gd::gd_truth(gd::gd_in(lv_item, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canApplyEffect_920, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAffectedItemInsideRemoved_929, _ca, 1); })();
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
    (void)([&]() { gd::GdVal _ca[] = {lv_bag}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onDraggedWithParentStart_718, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_onDraggedWithParentEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onDraggedWithParentEnd_720, nullptr, 0, _out); return _out; })();
    if (gd::gd_truth(this->f_dragged)) {
    }
    else {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetZ_452, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn_getNumAffectedInside(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_num = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t1179 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_927, nullptr, 0));
        gd::GdArr* _t1180 = (_t1179.kind == gd::GdVal::Kind::Arr) ? _t1179.arr : nullptr;
        uint32_t _len__t1181 = _t1180 ? _t1180->len : 0u;
        for (uint32_t _t1181 = 0; _t1181 < _len__t1181; ++_t1181) {
            gd::GdVal lv_item = _t1180->data[_t1181];
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
        gd::GdVal _t1182 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_927, nullptr, 0));
        gd::GdArr* _t1183 = (_t1182.kind == gd::GdVal::Kind::Arr) ? _t1182.arr : nullptr;
        uint32_t _len__t1184 = _t1183 ? _t1183->len : 0u;
        for (uint32_t _t1184 = 0; _t1184 < _len__t1184; ++_t1184) {
            gd::GdVal lv_item = _t1183->data[_t1184];
            lv_num = gd::gd_add(gd_ctx, lv_num, ([&]() { gd::GdVal _ca[] = {lv_type}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_getTypeMultiplicity_82, _ca, 1); })());
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
    (void)([&]() { gd::GdVal _ca[] = {lv_discardGems}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_discard_764, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Bag::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_permDamBonus_997: out = this->f_permDamBonus; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__BurningTorch::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_permDamBonus_997: this->f_permDamBonus = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__BurningTorch::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__BurningTorch::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__BurningTorch::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__BurningTorch::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BurningTorch::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_permDamBonus}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_163, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BurningTorch::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_permDamBonus = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0);
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
        case SYM_GEN_cards_1737: out = this->f_cards; return true;
        case SYM_GEN_cardActivations_1738: out = this->f_cardActivations; return true;
        case SYM_GEN_chainStarted_1739: out = this->f_chainStarted; return true;
        case SYM_GEN_connector_885: out = this->f_connector; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__DeckofCards::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_cards_1737: this->f_cards = val; return true;
        case SYM_GEN_cardActivations_1738: this->f_cardActivations = val; return true;
        case SYM_GEN_chainStarted_1739: this->f_chainStarted = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_connector_885: this->f_connector = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__DeckofCards::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onAddToInventory_421: return true;
        case SYM_GEN_onRemoveFromInventory_420: return true;
        case SYM_GEN_resetChain_1740: return true;
        case SYM_GEN_countDuplicates_1707: return true;
        case SYM_GEN_updateCards_1741: return true;
        case SYM_GEN_onItemAdded_439: return true;
        case SYM_GEN_onItemRemoved_440: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_notifyActivation_1742: return true;
        case SYM_GEN_getGatedDescriptor_956: return true;
        case SYM_GEN_getRelatedItemColumns_699: return true;
        case SYM_GEN_getRelatedItemHeight_700: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__DeckofCards::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onAddToInventory_421: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_420: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_resetChain_1740: out = fn_resetChain(args, argc); return true;
        case SYM_GEN_countDuplicates_1707: out = fn_countDuplicates(args, argc); return true;
        case SYM_GEN_updateCards_1741: out = fn_updateCards(args, argc); return true;
        case SYM_GEN_onItemAdded_439: out = fn_onItemAdded(args, argc); return true;
        case SYM_GEN_onItemRemoved_440: out = fn_onItemRemoved(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_notifyActivation_1742: out = fn_notifyActivation(args, argc); return true;
        case SYM_GEN_getGatedDescriptor_956: out = fn_getGatedDescriptor(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_699: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN_getRelatedItemHeight_700: out = fn_getRelatedItemHeight(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Card_2672)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeckofCards::fn_onAddToInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateCards_1741, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeckofCards::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetChain_1740, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeckofCards::fn_resetChain(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1185 = gd::gd_iter_seq(gd_ctx.arena, this->f_cards);
        gd::GdArr* _t1186 = (_t1185.kind == gd::GdVal::Kind::Arr) ? _t1185.arr : nullptr;
        uint32_t _len__t1187 = _t1186 ? _t1186->len : 0u;
        for (uint32_t _t1187 = 0; _t1187 < _len__t1187; ++_t1187) {
            gd::GdVal lv_card = _t1186->data[_t1187];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::gd_neg(gd::GdVal::from_int(1LL)), gd::call_method(gd_ctx, this->f_cards, gd::SYM_size, nullptr, 0)}; return gd::call_method(gd_ctx, lv_card, SYM_GEN_notifyChainPosition_894, _ca, 3); })();
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
        gd::GdVal _t1188 = gd::gd_iter_seq(gd_ctx.arena, lv_untilCardIndex);
        gd::GdArr* _t1189 = (_t1188.kind == gd::GdVal::Kind::Arr) ? _t1188.arr : nullptr;
        uint32_t _len__t1190 = _t1189 ? _t1189->len : 0u;
        for (uint32_t _t1190 = 0; _t1190 < _len__t1190; ++_t1190) {
            gd::GdVal lv_i = _t1189->data[_t1190];
            (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_index(gd_ctx, this->f_cards, lv_i), SYM_GEN_descriptor_2)}; return gd::call_method(gd_ctx, lv_descriptors, gd::SYM_push_back, _ca, 1); })();
        }
    }
    return ([&]() { gd::GdVal _ca[] = {lv_descriptors}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_countDuplicates_1707, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeckofCards::fn_updateCards(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetChain_1740, nullptr, 0);
    gd::GdVal lv_affected = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_affected, gd::SYM_empty, nullptr, 0))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, lv_affected, gd::GdVal::from_int(0LL))}; return gd::call_method(gd_ctx, this->f_cards, gd::SYM_push_back, _ca, 1); })();
        gd::GdVal lv_nextCard = gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_cards, gd::GdVal::from_int(0LL)), SYM_GEN_getNextCard_891, nullptr, 0);
        while (gd::gd_truth((gd::gd_truth(lv_nextCard) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::gd_in(lv_nextCard, this->f_cards))))) : gd::GdVal::from_bool(false)))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_nextCard}; return gd::call_method(gd_ctx, this->f_cards, gd::SYM_push_back, _ca, 1); })();
            lv_nextCard = gd::call_method(gd_ctx, lv_nextCard, SYM_GEN_getNextCard_891, nullptr, 0);
        }
    }
    else {
    }
    gd::GdVal lv_chainLength = gd::call_method(gd_ctx, this->f_cards, gd::SYM_size, nullptr, 0);
    {
        gd::GdVal _t1191 = gd::gd_iter_seq(gd_ctx.arena, lv_chainLength);
        gd::GdArr* _t1192 = (_t1191.kind == gd::GdVal::Kind::Arr) ? _t1191.arr : nullptr;
        uint32_t _len__t1193 = _t1192 ? _t1192->len : 0u;
        for (uint32_t _t1193 = 0; _t1193 < _len__t1193; ++_t1193) {
            gd::GdVal lv_i = _t1192->data[_t1193];
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), lv_i, lv_chainLength}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_cards, lv_i), SYM_GEN_notifyChainPosition_894, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeckofCards::fn_onItemAdded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onItemAdded_439, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(lv_item, &META_Gd__gd_core_items__Card)))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateCards_1741, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__DeckofCards::fn_onItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onItemRemoved_440, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(lv_item, &META_Gd__gd_core_items__Card)))) {
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateCards_1741, nullptr, 0);
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
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_chainStarted)))) {
        this->f_chainStarted = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
        this->f_cardActivations = gd::GdVal::from_int(0LL);
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, this->f_cards, gd::SYM_empty, nullptr, 0))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::get_index(gd_ctx, this->f_cards, gd::GdVal::from_int(0LL)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "startActivation", 15u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::call_method(gd_ctx, this->f_ctx, SYM_GEN_defer_1422, _ca, 3); })();
        }
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__DeckofCards(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__DeckofCards>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__DeckofCards = {CLS_Gd__gd_core_items__DeckofCards, "DeckofCards", "res://gd_core_items/DeckofCards.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__DeckofCards, &Gd__gd_core_items__DeckofCards::get_static_prop_fn, &Gd__gd_core_items__DeckofCards::call_static_fn};

void Gd__gd_core_items__Exclusive__AmuletofLight::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_regenOnActivate = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__AmuletofLight::meta() const { return &META_Gd__gd_core_items__Exclusive__AmuletofLight; }
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofLight::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_amuletColor_1927: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::GdVal::from_float(0.850098), gd::GdVal::from_float(0.400391)}; return gd::make_color_from_args(_ca, 3); })();
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__AmuletofLight::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__AmuletofLight::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_regenOnActivate_1938: out = this->f_regenOnActivate; return true;
        case SYM_GEN_amuletColor_1927: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__AmuletofLight::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_regenOnActivate_1938: this->f_regenOnActivate = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__AmuletofLight::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onItemActivated_938: return true;
        case SYM_GEN_onRegenChanged_1796: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__AmuletofLight::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onItemActivated_938: out = fn_onItemActivated(args, argc); return true;
        case SYM_GEN_onRegenChanged_1796: out = fn_onRegenChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__AmuletofLight::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofLight::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canActivate_93, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofLight::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_regeneration_changed", 30u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onRegenChanged", 14u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    {
        gd::GdVal _t1194 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1195 = (_t1194.kind == gd::GdVal::Kind::Arr) ? _t1194.arr : nullptr;
        uint32_t _len__t1196 = _t1195 ? _t1195->len : 0u;
        for (uint32_t _t1196 = 0; _t1196 < _len__t1196; ++_t1196) {
            gd::GdVal lv_item = _t1195->data[_t1196];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "activated", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onItemActivated", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofLight::fn_onItemActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Holy_2593)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, lv_event, SYM_GEN_origin_1455), SYM_GEN_hasType_81, _ca, 1); })())) {
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance2_176, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_regenOnActivate, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 2); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
        }
    }
    else {
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_regenOnActivate, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_216, _ca, 2); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofLight::fn_onRegenChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })()), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_319, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofLight::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_regenOnActivate = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "regen", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__AmuletofLight(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__AmuletofLight>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AmuletofLight = {CLS_Gd__gd_core_items__Exclusive__AmuletofLight, "AmuletofLight", "res://gd_core_items/Exclusive/AmuletofLight.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__AmuletofLight, &Gd__gd_core_items__Exclusive__AmuletofLight::get_static_prop_fn, &Gd__gd_core_items__Exclusive__AmuletofLight::call_static_fn};

void Gd__gd_core_items__Exclusive__BadgerRune::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Gems__Gem::init_fields(gd_ctx);
    this->f_attackSpeedBonus = gd::GdVal::null();
    this->f_damageReduction = gd::GdVal::from_int(0);
    this->f_staminaReduction = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__BadgerRune::meta() const { return &META_Gd__gd_core_items__Exclusive__BadgerRune; }
gd::GdVal Gd__gd_core_items__Exclusive__BadgerRune::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_gemColor_995: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.845703), gd::GdVal::from_float(0.420593), gd::GdVal::from_float(0.062767)}; return gd::make_color_from_args(_ca, 3); })();
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
        case SYM_GEN_attackSpeedBonus_1956: out = this->f_attackSpeedBonus; return true;
        case SYM_GEN_damageReduction_1063: out = this->f_damageReduction; return true;
        case SYM_GEN_staminaReduction_1918: out = this->f_staminaReduction; return true;
        case SYM_GEN_gemColor_995: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BadgerRune::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_attackSpeedBonus_1956: this->f_attackSpeedBonus = val; return true;
        case SYM_GEN_damageReduction_1063: this->f_damageReduction = gd::gd_coerce_int(val); return true;
        case SYM_GEN_staminaReduction_1918: this->f_staminaReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BadgerRune::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_isBattleRageItem_87: return true;
        case SYM_GEN_prepareWeapon_982: return true;
        case SYM_GEN_onAttack_1957: return true;
        case SYM_GEN_prepareArmor_983: return true;
        case SYM_GEN_preTakeDamage_1849: return true;
        case SYM_GEN_hasCooldown_97: return true;
        case SYM_GEN_prepareInventory_981: return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_992: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BadgerRune::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_isBattleRageItem_87: out = fn_isBattleRageItem(args, argc); return true;
        case SYM_GEN_prepareWeapon_982: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_onAttack_1957: out = fn_onAttack(args, argc); return true;
        case SYM_GEN_prepareArmor_983: out = fn_prepareArmor(args, argc); return true;
        case SYM_GEN_preTakeDamage_1849: out = fn_preTakeDamage(args, argc); return true;
        case SYM_GEN_hasCooldown_97: out = fn_hasCooldown(args, argc); return true;
        case SYM_GEN_prepareInventory_981: out = fn_prepareInventory(args, argc); return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_992: out = fn_onHotSwapHoverWithGemEnd(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__BadgerRune::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Gems__Gem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__BadgerRune::fn_isBattleRageItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::gd_eq(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemMode_972, nullptr, 0), gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__BadgerRune::get_static_const_or_enum(gd_ctx, SYM_GEN_GemMode_994), SYM_GEN_Armor_2751)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BadgerRune::fn_prepareWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_391, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attacked", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onAttack", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BadgerRune::fn_onAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_attackSpeedBonus}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_391, nullptr, 0), SYM_GEN_addSpeed_275, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BadgerRune::fn_prepareArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "pre_take_damage", 15u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "preTakeDamage", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BadgerRune::fn_preTakeDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_triggerOnAttacked_1439, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_isBattleRaging_1191, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_round(gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0), this->f_damageReduction)), gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_applyDamageReduction_1435, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
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
        gd::GdVal _t1197 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_getItems_1512, nullptr, 0));
        gd::GdArr* _t1198 = (_t1197.kind == gd::GdVal::Kind::Arr) ? _t1197.arr : nullptr;
        uint32_t _len__t1199 = _t1198 ? _t1198->len : 0u;
        for (uint32_t _t1199 = 0; _t1199 < _len__t1199; ++_t1199) {
            gd::GdVal lv_item = _t1198->data[_t1199];
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_staminaReduction)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeStaminaFactor_307, _ca, 1); })();
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_attackSpeedBonus = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attackspeed", 11u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_damageReduction = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "damreduction", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_staminaReduction = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
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
        case SYM_GEN_bonusHealthFactor_1996: out = this->f_bonusHealthFactor; return true;
        case SYM_GEN_salesChance_1997: out = this->f_salesChance; return true;
        case SYM_GEN_manaNeeded_1786: out = this->f_manaNeeded; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BookofBasics::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bonusHealthFactor_1996: this->f_bonusHealthFactor = gd::gd_coerce_int(val); return true;
        case SYM_GEN_salesChance_1997: this->f_salesChance = val; return true;
        case SYM_GEN_manaNeeded_1786: this->f_manaNeeded = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BookofBasics::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onSaleRoll_1998: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BookofBasics::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onSaleRoll_1998: out = fn_onSaleRoll(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Spell_2607)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofBasics::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_bonusHealthFactor = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    {
        gd::GdVal _t1200 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1201 = (_t1200.kind == gd::GdVal::Kind::Arr) ? _t1200.arr : nullptr;
        uint32_t _len__t1202 = _t1201 ? _t1201->len : 0u;
        for (uint32_t _t1202 = 0; _t1202 < _len__t1202; ++_t1202) {
            gd::GdVal lv_item = _t1201->data[_t1202];
            if (gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isCrafted_800, nullptr, 0))) {
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
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getMana_1228, nullptr, 0), this->f_manaNeeded)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_manaNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_334, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth_spell", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), this->f_bonusHealthFactor)), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_319, _ca, 2); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofBasics::fn_onSaleRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BookofBasics::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_salesChance = gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getShopChance_239, nullptr, 0), gd::GdVal::from_float(100.0));
    this->f_manaNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "manat", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
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
        case SYM_GEN_bonusDamPerEmpower_2017: out = this->f_bonusDamPerEmpower; return true;
        default: break;
    }
    return Gd__gd_core_items__Greatsword::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__BustedBlade::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bonusDamPerEmpower_2017: this->f_bonusDamPerEmpower = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Greatsword::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__BustedBlade::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onEmpowerChanged_2018: return true;
        case SYM_GEN_onBattleRageStarted_1971: return true;
        case SYM_GEN_onBattleRageEnded_1972: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Greatsword::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__BustedBlade::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onEmpowerChanged_2018: out = fn_onEmpowerChanged(args, argc); return true;
        case SYM_GEN_onBattleRageStarted_1971: out = fn_onBattleRageStarted(args, argc); return true;
        case SYM_GEN_onBattleRageEnded_1972: out = fn_onBattleRageEnded(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Greatsword::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__BustedBlade::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Greatsword::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__BustedBlade::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "battle_rage_started", 19u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBattleRageStarted", 19u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "battle_rage_ended", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBattleRageEnded", 17u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_empower_changed", 25u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onEmpowerChanged", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BustedBlade::fn_onEmpowerChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, this->f_bonusDamPerEmpower)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeVaryingDamage_164, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BustedBlade::fn_onBattleRageStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_buffed)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
        this->f_baseCooldownOverride = gd::gd_coerce_float(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0));
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateBaseCooldown_112, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_StaminaCost_2547)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BustedBlade::fn_onBattleRageEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(this->f_buffed)) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
        this->f_baseCooldownOverride = gd::gd_coerce_float(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldown_102, nullptr, 0));
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateBaseCooldown_112, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1369), SYM_GEN_StaminaCost_2547)}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1381), SYM_GEN_snapshotItemTooltipStat_1355, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__BustedBlade::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Greatsword::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_bonusDamPerEmpower = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0);
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
        case SYM_GEN_buffTimer_1724: out = this->f_buffTimer; return true;
        case SYM_GEN_spikes_898: out = this->f_spikes; return true;
        case SYM_GEN_crit_2061: out = this->f_crit; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackRook::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffTimer_1724: this->f_buffTimer = val; return true;
        case SYM_GEN_spikes_898: this->f_spikes = val; return true;
        case SYM_GEN_crit_2061: this->f_crit = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackRook::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2050: return true;
        case SYM_GEN_doEliminatedEffect_2052: return true;
        case SYM_GEN_buffEnded_1722: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Chess__ChessPiece::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Chess__BlackRook::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCapturingEffect_2050: out = fn_doCapturingEffect(args, argc); return true;
        case SYM_GEN_doEliminatedEffect_2052: out = fn_doEliminatedEffect(args, argc); return true;
        case SYM_GEN_buffEnded_1722: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {this->f_spikes}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_211, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackRook::fn_doEliminatedEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__capturingPiece = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_crit}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeAllItemsCritRate_471, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })()}; return gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_start_1685, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackRook::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_crit)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_changeAllItemsCritRate_471, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Chess__BlackRook::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Chess__ChessPiece::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "BuffTimer", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffEnded", 9u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_137, _ca, 3); })();
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "spikes", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_crit = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "crit", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
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
        case SYM_GEN_damageAcc_1865: out = this->f_damageAcc; return true;
        case SYM_GEN_damagePerPoison_1866: out = this->f_damagePerPoison; return true;
        case SYM_GEN_poison_1867: out = this->f_poison; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__CriticalPoison::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damageAcc_1865: this->f_damageAcc = gd::gd_coerce_int(val); return true;
        case SYM_GEN_damagePerPoison_1866: this->f_damagePerPoison = gd::gd_coerce_int(val); return true;
        case SYM_GEN_poison_1867: this->f_poison = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__CriticalPoison::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onWeaponAttacked_950: return true;
        case SYM_GEN_onLuckChanged_1969: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__CriticalPoison::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onWeaponAttacked_950: out = fn_onWeaponAttacked(args, argc); return true;
        case SYM_GEN_onLuckChanged_1969: out = fn_onLuckChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_92, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CriticalPoison::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1203 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1204 = (_t1203.kind == gd::GdVal::Kind::Arr) ? _t1203.arr : nullptr;
        uint32_t _len__t1205 = _t1204 ? _t1204->len : 0u;
        for (uint32_t _t1205 = 0; _t1205 < _len__t1205; ++_t1205) {
            gd::GdVal lv_weapon = _t1204->data[_t1205];
            (void)([&]() { gd::GdVal _ca[] = {lv_weapon, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attacked", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onWeaponAttacked", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_lucky_changed", 23u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onLuckChanged", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CriticalPoison::fn_onWeaponAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        this->f_damageAcc = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_damageAcc, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1427)));
        gd::GdVal lv_poisonStacks = gd::gd_div(gd_ctx, this->f_damageAcc, this->f_damagePerPoison);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_poisonStacks, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_poisonStacks, this->f_poison), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_213, _ca, 2); })();
            this->f_damageAcc = gd::gd_coerce_int(gd::gd_mod(gd_ctx, this->f_damageAcc, this->f_damagePerPoison));
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CriticalPoison::fn_onLuckChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_changePoisonCritChancePercent_1267, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CriticalPoison::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_damagePerPoison = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "damt", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_poison = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "poison", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
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
        case SYM_GEN_poison_1867: out = this->f_poison; return true;
        case SYM_GEN_healingDebuff_1893: out = this->f_healingDebuff; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DoomCap::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_poison_1867: this->f_poison = val; return true;
        case SYM_GEN_healingDebuff_1893: this->f_healingDebuff = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DoomCap::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DoomCap::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__DoomCap::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__DoomCap::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_poison}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_213, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_healingDebuff}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_reduceHealingEfficiency_1167, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DoomCap::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_poison = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "poison", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_healingDebuff = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healreduction", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__DragonEgg::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__EmeraldEgg::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__DragonEgg::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__EmeraldEgg::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__DragonEgg::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__EmeraldEgg::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_doCooldownEffect_146, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EmeraldEgg::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_217, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EmeraldEgg::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__DragonEgg::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_heat_1801: out = this->f_heat; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Shelly::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__FireShelly::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_heat_1801: this->f_heat = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Shelly::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__FireShelly::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Shelly::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__FireShelly::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Exclusive__Shelly::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__FireShelly::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Exclusive__Shelly::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__FireShelly::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Shelly::call_method(gd_ctx, SYM_GEN_doCooldownEffect_146, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FireShelly::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Exclusive__Shelly::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heat", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
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
        case SYM_GEN_active_2129: out = this->f_active; return true;
        case SYM_GEN_salesChance_1997: out = this->f_salesChance; return true;
        case SYM_GEN_goldCost_2069: out = this->f_goldCost; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__FurciferPrime::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_active_2129: this->f_active = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_salesChance_1997: this->f_salesChance = val; return true;
        case SYM_GEN_goldCost_2069: this->f_goldCost = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__FurciferPrime::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getData_638: return true;
        case SYM_GEN_setData_639: return true;
        case SYM_GEN_onSwitchToCombat_2191: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onSaleRoll_1998: return true;
        case SYM_GEN_onSaleRoll_storage_2192: return true;
        case SYM_GEN_getGatedDescriptor_956: return true;
        case SYM_GEN_onGateItemRoll_453: return true;
        case SYM_GEN_onGateItemRoll_storage_2193: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__FurciferPrime::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getData_638: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_639: out = fn_setData(args, argc); return true;
        case SYM_GEN_onSwitchToCombat_2191: out = fn_onSwitchToCombat(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onSaleRoll_1998: out = fn_onSaleRoll(args, argc); return true;
        case SYM_GEN_onSaleRoll_storage_2192: out = fn_onSaleRoll_storage(args, argc); return true;
        case SYM_GEN_getGatedDescriptor_956: out = fn_getGatedDescriptor(args, argc); return true;
        case SYM_GEN_onGateItemRoll_453: out = fn_onGateItemRoll(args, argc); return true;
        case SYM_GEN_onGateItemRoll_storage_2193: out = fn_onGateItemRoll_storage(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {lv__item}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onSaleRoll_1998, _ca, 1); })();
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
        (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onGateItemRoll_453, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FurciferPrime::fn_onGateItemRoll_storage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onGateItemRoll_453, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__FurciferPrime::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_salesChance = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "sales", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_goldCost = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gold", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
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
        case SYM_GEN_phase_2213: out = this->f_phase; return true;
        case SYM_GEN_maxStaminaUsed_2214: out = this->f_maxStaminaUsed; return true;
        case SYM_GEN_buffsPerStamina_2215: out = this->f_buffsPerStamina; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__HogusBogus::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_phase_2213: this->f_phase = gd::gd_coerce_int(val); return true;
        case SYM_GEN_maxStaminaUsed_2214: this->f_maxStaminaUsed = val; return true;
        case SYM_GEN_buffsPerStamina_2215: this->f_buffsPerStamina = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__HogusBogus::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_trigger_145: return true;
        case SYM_GEN_canUseStamina_296: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__HogusBogus::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_trigger_145: out = fn_trigger(args, argc); return true;
        case SYM_GEN_canUseStamina_296: out = fn_canUseStamina(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, this->f_phase, gd::GdVal::from_int(1LL))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_trigger_145, nullptr, 0, _out); return _out; })();
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
        gd::GdVal lv_curStamina = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getCurrentStamina_1246, nullptr, 0);
        gd::GdVal lv_step = gd::gd_div(gd_ctx, gd::GdVal::from_float(1.0), this->f_buffsPerStamina);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_curStamina, lv_step)))) {
            gd::GdVal lv_numProccs = gd::gd_floor(gd::gd_div(gd_ctx, lv_curStamina, lv_step));
            gd::GdVal lv_staminaToUse = gd::gd_min(lv_curStamina, gd::gd_min(gd::gd_mul(lv_numProccs, lv_step), this->f_maxStaminaUsed));
            (void)([&]() { gd::GdVal _ca[] = {lv_staminaToUse}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_118, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_round(gd::gd_mul(lv_staminaToUse, this->f_buffsPerStamina))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_371, _ca, 1); })();
        }
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_phase, gd::GdVal::from_int(2LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_stun", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })()}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_332, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_self_stun", 13u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_stun_332, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    }
    else {
        gd::GdVal lv_curHealth = gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_getCurrentHealth_1138, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::gd_mul(lv_curHealth, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })()), gd::GdVal::from_float(100.0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_147, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HogusBogus::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__phase = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv__phase = gd::gd_coerce_int(lv__phase);
    this->f_phase = gd::gd_coerce_int(lv__phase);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(this->f_phase, gd::GdVal::from_int(0LL))))) {
        this->f_baseCooldownOverride = gd::gd_coerce_float(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldownIndex_103, _ca, 1); })());
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_phase, gd::GdVal::from_int(3LL))))) {
        this->f_baseCooldownOverride = gd::gd_coerce_float(gd::gd_sub(([&]() { gd::GdVal _ca[] = {this->f_phase}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldownIndex_103, _ca, 1); })(), ([&]() { gd::GdVal _ca[] = {gd::gd_sub(this->f_phase, gd::GdVal::from_int(1LL))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseCooldownIndex_103, _ca, 1); })()));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HogusBogus::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_maxStaminaUsed = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "stamina", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_buffsPerStamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
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
        case SYM_GEN_CrownState_1727: return gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Exclusive__KingGoobert_CrownState);
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
        case SYM_GEN_invuCharges_2236: out = this->f_invuCharges; return true;
        case SYM_GEN_protectedBuffs_2237: out = this->f_protectedBuffs; return true;
        case SYM_GEN_manaCost_1720: out = this->f_manaCost; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_buffTimer_1724: out = this->f_buffTimer; return true;
        case SYM_GEN_light_949: out = this->f_light; return true;
        case SYM_GEN_CrownState_1727: out = gd::GdVal::from_enum(&_enum_Gd__gd_core_items__Exclusive__KingGoobert_CrownState); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__KingGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_invuCharges_2236: this->f_invuCharges = gd::gd_coerce_int(val); return true;
        case SYM_GEN_protectedBuffs_2237: this->f_protectedBuffs = val; return true;
        case SYM_GEN_manaCost_1720: this->f_manaCost = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_buffTimer_1724: this->f_buffTimer = val; return true;
        case SYM_GEN_light_949: this->f_light = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__KingGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_prepare_124: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_buffEnded_1722: return true;
        case SYM_GEN_onCombatEnd_134: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_385: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__KingGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_prepare_124: out = fn_prepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_buffEnded_1722: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_onCombatEnd_134: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_385: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__KingGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__KingGoobert::fn_prepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_gemPower = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "gempower", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    {
        gd::GdVal _t1206 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemsNoNull_499, nullptr, 0));
        gd::GdArr* _t1207 = (_t1206.kind == gd::GdVal::Kind::Arr) ? _t1206.arr : nullptr;
        uint32_t _len__t1208 = _t1207 ? _t1207->len : 0u;
        for (uint32_t _t1208 = 0; _t1208 < _len__t1208; ++_t1208) {
            gd::GdVal lv_gem = _t1207->data[_t1208];
            (void)([&]() { gd::GdVal _ca[] = {lv_gemPower}; return gd::call_method(gd_ctx, lv_gem, SYM_GEN_changeGemPower_974, _ca, 1); })();
        }
    }
    this->f_invuCharges = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "charges", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__KingGoobert::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1727), SYM_GEN_Inactive_2594)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 1); })();
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN_prepare_124, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KingGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_protectedBuffs}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeBuffProtectStacks_1171, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_invuCharges, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_isVulnerable_1275, nullptr, 0))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkMana_333, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        this->f_invuCharges = gd::gd_coerce_int(gd::gd_sub(this->f_invuCharges, gd::GdVal::from_int(1LL)));
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__KingGoobert::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1727), SYM_GEN_Active_2595), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 2); })();
        gd::GdVal lv_invuDur = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_invu", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })();
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {lv_invuDur, gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_makeInvulnerable_1195, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_invuDur}; return gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_start_1685, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_manaCost, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_334, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KingGoobert::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(this->f_invuCharges, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__KingGoobert::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1727), SYM_GEN_Inactive_2594), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 2); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__KingGoobert::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1727), SYM_GEN_Used_2596), gd::GdVal::from_bool(true)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_384, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KingGoobert::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1686, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KingGoobert::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__KingGoobert::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1727), SYM_GEN_Inactive_2594)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_385, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KingGoobert::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__crownState = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv__crownState, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__KingGoobert::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1727), SYM_GEN_Inactive_2594))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv__crownState, gd::get_prop(gd_ctx, Gd__gd_core_items__Exclusive__KingGoobert::get_static_const_or_enum(gd_ctx, SYM_GEN_CrownState_1727), SYM_GEN_Active_2595))))) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__KingGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_protectedBuffs = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_manaCost = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "BuffTimer", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffEnded", 9u)), gd::GdVal::from_bool(false)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_137, _ca, 3); })();
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
        case SYM_GEN_mana_1833: out = this->f_mana; return true;
        default: break;
    }
    return Gd__gd_core_items__RangerCollar::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MagicCollar::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_mana_1833: this->f_mana = val; return true;
        default: break;
    }
    return Gd__gd_core_items__RangerCollar::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MagicCollar::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onWeaponAttacked_950: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__RangerCollar::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MagicCollar::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onWeaponAttacked_950: out = fn_onWeaponAttacked(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_92, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicCollar::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1209 = gd::gd_iter_seq(gd_ctx.arena, this->f_affectedItems);
        gd::GdArr* _t1210 = (_t1209.kind == gd::GdVal::Kind::Arr) ? _t1209.arr : nullptr;
        uint32_t _len__t1211 = _t1210 ? _t1210->len : 0u;
        for (uint32_t _t1211 = 0; _t1211 < _len__t1211; ++_t1211) {
            gd::GdVal lv_item = _t1210->data[_t1211];
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attacked", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onWeaponAttacked", 16u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicCollar::fn_onWeaponAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_triggerOnHit_1436, nullptr, 0))) {
        gd::GdVal lv_totalChance = gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0), gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getLucky_1221, nullptr, 0));
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_totalChance}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, _ca, 1); })())) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_mana, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_218, _ca, 2); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MagicCollar::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__RangerCollar::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "mana", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
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
        case SYM_GEN_totalBlockRemoval_1886: out = this->f_totalBlockRemoval; return true;
        case SYM_GEN_blockRemoval_1802: out = this->f_blockRemoval; return true;
        case SYM_GEN_heatNeeded_1785: out = this->f_heatNeeded; return true;
        case SYM_GEN_missDamage_2312: out = this->f_missDamage; return true;
        case SYM_GEN_blind_1816: out = this->f_blind; return true;
        case SYM_GEN_selfblind_2313: out = this->f_selfblind; return true;
        case SYM_GEN_fireMultiplicity_2311: out = this->f_fireMultiplicity; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MoltenSpear2::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_totalBlockRemoval_1886: this->f_totalBlockRemoval = gd::gd_coerce_int(val); return true;
        case SYM_GEN_blockRemoval_1802: this->f_blockRemoval = val; return true;
        case SYM_GEN_heatNeeded_1785: this->f_heatNeeded = val; return true;
        case SYM_GEN_missDamage_2312: this->f_missDamage = val; return true;
        case SYM_GEN_blind_1816: this->f_blind = val; return true;
        case SYM_GEN_selfblind_2313: this->f_selfblind = val; return true;
        case SYM_GEN_fireMultiplicity_2311: this->f_fireMultiplicity = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MoltenSpear2::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_affectsEmpty_257: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_onPreDealDamage_late_906: return true;
        case SYM_GEN_getTypeMultiplicity_82: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MoltenSpear2::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_affectsEmpty_257: out = fn_affectsEmpty(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onPreDealDamage_late_906: out = fn_onPreDealDamage_late(args, argc); return true;
        case SYM_GEN_getTypeMultiplicity_82: out = fn_getTypeMultiplicity(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Fire_2601)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear2::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_totalBlockRemoval = gd::gd_coerce_int(gd::gd_mul(this->f_blockRemoval, gd::gd_add(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Fire_2601)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffected_type_431, _ca, 1); })(), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumEmptyAffectedCells_428, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear2::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getHeat_1235, nullptr, 0), this->f_heatNeeded)))) {
            (void)([&]() { gd::GdVal _ca[] = {this->f_missDamage}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_163, _ca, 1); })();
            gd::set_prop(gd_ctx, lv_damageRes, SYM_GEN_hit_1429, gd::GdVal::from_bool(true));
            (void)([&]() { gd::GdVal _ca[] = {this->f_heatNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useHeat_356, _ca, 1); })();
        }
    }
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_blind}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_215, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_selfblind}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_selfInflictBlind_345, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear2::fn_onPreDealDamage_late(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_totalBlockRemoval}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeBlock_207, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear2::fn_getTypeMultiplicity(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_type = gd::gd_coerce_int(lv_type);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(lv_type, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Fire_2601))))) {
        return this->f_fireMultiplicity;
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {lv_type}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN_getTypeMultiplicity_82, _ca, 1, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MoltenSpear2::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_blockRemoval = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blockremoval", 12u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })();
    this->f_heatNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heatt", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_missDamage = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "missdam", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_blind = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blind", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_selfblind = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "blind_self", 10u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_fireMultiplicity = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "fire", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__MoltenSpear2(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__MoltenSpear2>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MoltenSpear2 = {CLS_Gd__gd_core_items__Exclusive__MoltenSpear2, "MoltenSpear2", "res://gd_core_items/Exclusive/MoltenSpear2.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__MoltenSpear2, &Gd__gd_core_items__Exclusive__MoltenSpear2::get_static_prop_fn, &Gd__gd_core_items__Exclusive__MoltenSpear2::call_static_fn};

void Gd__gd_core_items__Exclusive__PiggyofRiches::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__BoxofRiches::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__PiggyofRiches::meta() const { return &META_Gd__gd_core_items__Exclusive__PiggyofRiches; }
gd::GdVal Gd__gd_core_items__Exclusive__PiggyofRiches::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__BoxofRiches::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__PiggyofRiches::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__PiggyofRiches::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__BoxofRiches::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PiggyofRiches::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__BoxofRiches::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PiggyofRiches::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_getRelatedItems_461: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__BoxofRiches::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PiggyofRiches::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_getRelatedItems_461: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__BoxofRiches::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__PiggyofRiches::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__BoxofRiches::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__PiggyofRiches::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, this->f_inventory, SYM_GEN_countSocketedGems_1523, nullptr, 0), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "maxhealth", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })())}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_319, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_383, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PiggyofRiches::fn_getRelatedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "Box of Riches", 13u))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1393), SYM_GEN_getDescriptor_1564, _ca, 1); })(), SYM_GEN_gatedItems_1595);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PiggyofRiches::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__BoxofRiches::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_numGems = gd::GdVal::from_int(2LL);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PiggyofRiches(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__PiggyofRiches>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PiggyofRiches = {CLS_Gd__gd_core_items__Exclusive__PiggyofRiches, "PiggyofRiches", "res://gd_core_items/Exclusive/PiggyofRiches.gd", &META_Gd__gd_core_items__BoxofRiches, true, _alloc_Gd__gd_core_items__Exclusive__PiggyofRiches, &Gd__gd_core_items__Exclusive__PiggyofRiches::get_static_prop_fn, &Gd__gd_core_items__Exclusive__PiggyofRiches::call_static_fn};

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
        case SYM_GEN_healamp_2062: out = this->f_healamp; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagL::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_healamp_2062: this->f_healamp = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagL::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canApplyEffect_920: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_getBagEffect_482: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PuzzlebagL::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canApplyEffect_920: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_getBagEffect_482: out = fn_getBagEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_toItem, SYM_GEN_canHealOrLifesteal_294, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagL::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1212 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_927, nullptr, 0));
        gd::GdArr* _t1213 = (_t1212.kind == gd::GdVal::Kind::Arr) ? _t1212.arr : nullptr;
        uint32_t _len__t1214 = _t1213 ? _t1213->len : 0u;
        for (uint32_t _t1214 = 0; _t1214 < _len__t1214; ++_t1214) {
            gd::GdVal lv_item = _t1213->data[_t1214];
            (void)([&]() { gd::GdVal _ca[] = {this->f_healamp}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeHealAmp_306, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagL::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_319, nullptr, 0);
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagL::fn_getBagEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_number = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_descr = ([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getName_236, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "_BAGEFFECT", 10u)))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1378), SYM_GEN_tra_2620, _ca, 1); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "p_healamp", 9u)), gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healamp", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), lv_number)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 3); })();
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PuzzlebagL::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_healamp = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healamp", 7u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_stable_2372: out = this->f_stable; return true;
        case SYM_GEN_idleAnimation_2373: out = this->f_idleAnimation; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Recombobulator::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_stable_2372: this->f_stable = val; return true;
        case SYM_GEN_idleAnimation_2373: this->f_idleAnimation = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Recombobulator::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_cacheAffectedItemsForCombat_121: return true;
        case SYM_GEN_readyToFuse_751: return true;
        case SYM_GEN_onFusingFinished_848: return true;
        case SYM_GEN_reactToDropResult_722: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_getCounterValue_2256: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Recombobulator::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_cacheAffectedItemsForCombat_121: out = fn_cacheAffectedItemsForCombat(args, argc); return true;
        case SYM_GEN_readyToFuse_751: out = fn_readyToFuse(args, argc); return true;
        case SYM_GEN_onFusingFinished_848: out = fn_onFusingFinished(args, argc); return true;
        case SYM_GEN_reactToDropResult_722: out = fn_reactToDropResult(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_getCounterValue_2256: out = fn_getCounterValue(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_isBag_85, nullptr, 0)))) ? gd::GdVal::from_bool(gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_item, SYM_GEN_canStartNewRecipe_807, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_eq(gd::get_prop(gd_ctx, lv_item, SYM_GEN_bondedBaseItem_573), gd::GdVal::from_obj(this)))))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Recombobulator::fn_cacheAffectedItemsForCombat(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_cacheAffectedItemsForCombat_121, nullptr, 0, _out); return _out; })();
    gd::GdVal lv_arr = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInAffectedCells_cached_425, nullptr, 0);
    { gd::GdVal _t1215 = this->f_cachedAffectedItems; gd::GdVal _t1216 = gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581); gd::set_index(gd_ctx, _t1215, _t1216, lv_arr); }
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
    (void)([&]() { gd::GdVal _ca[] = {lv_validBonds}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onFusingFinished_848, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Recombobulator::fn_reactToDropResult(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_dropResult = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_dropResult}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_reactToDropResult_722, _ca, 1, _out); return _out; })();
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_dropResult}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core_items__Exclusive__Recombobulator::call_static_fn(gd_ctx, SYM_GEN_wasAddedToInventory_659, _ca, 1, _out); return _out; })())) {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Recombobulator::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_371, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_358, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Recombobulator::fn_getCounterValue(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedGoldValue_496, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Recombobulator::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_bonusSpeed_1787: out = this->f_bonusSpeed; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SewingCase::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_bonusSpeed_1787: this->f_bonusSpeed = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SewingCase::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canApplyEffect_920: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SewingCase::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canApplyEffect_920: out = fn_canApplyEffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return (gd::gd_truth(gd::call_method(gd_ctx, lv_toItem, SYM_GEN_isCrafted_800, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_toItem, SYM_GEN_hasCooldown_97, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, lv_toItem, SYM_GEN_gainsBuffs_298, nullptr, 0)))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SewingCase::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1217 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItemsInside_927, nullptr, 0));
        gd::GdArr* _t1218 = (_t1217.kind == gd::GdVal::Kind::Arr) ? _t1217.arr : nullptr;
        uint32_t _len__t1219 = _t1218 ? _t1218->len : 0u;
        for (uint32_t _t1219 = 0; _t1219 < _len__t1219; ++_t1219) {
            gd::GdVal lv_item = _t1218->data[_t1219];
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_275, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_allBuffs_199, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SewingCase::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_bonusSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SewingCase(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SewingCase>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SewingCase = {CLS_Gd__gd_core_items__Exclusive__SewingCase, "SewingCase", "res://gd_core_items/Exclusive/SewingCase.gd", &META_Gd__gd_core_items__Bag, true, _alloc_Gd__gd_core_items__Exclusive__SewingCase, &Gd__gd_core_items__Exclusive__SewingCase::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SewingCase::call_static_fn};

void Gd__gd_core_items__Exclusive__Snowball::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_cold = gd::GdVal::null();
    this->f_maxHealthReduction = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Snowball::meta() const { return &META_Gd__gd_core_items__Exclusive__Snowball; }
gd::GdVal Gd__gd_core_items__Exclusive__Snowball::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Snowball::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Snowball::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_cold_1950: out = this->f_cold; return true;
        case SYM_GEN_maxHealthReduction_2057: out = this->f_maxHealthReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Snowball::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_cold_1950: this->f_cold = val; return true;
        case SYM_GEN_maxHealthReduction_2057: this->f_maxHealthReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Snowball::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Snowball::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Snowball::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Snowball::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_maxHealthReduction}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_changeMaxHealthGain_1261, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Snowball::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_cold}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictCold_353, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consume_383, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Snowball::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_cold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "cold", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
    this->f_maxHealthReduction = gd::gd_div(gd_ctx, gd::gd_neg(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "healthreduction", 15u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })()), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Snowball(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Snowball>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Snowball = {CLS_Gd__gd_core_items__Exclusive__Snowball, "Snowball", "res://gd_core_items/Exclusive/Snowball.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Snowball, &Gd__gd_core_items__Exclusive__Snowball::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Snowball::call_static_fn};

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
        case SYM_GEN_pets_2429: out = this->f_pets; return true;
        case SYM_GEN_boostedCompanions_2448: out = this->f_boostedCompanions; return true;
        case SYM_GEN_buffFactor_2267: out = this->f_buffFactor; return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SpiritBells::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_pets_2429: this->f_pets = val; return true;
        case SYM_GEN_boostedCompanions_2448: this->f_boostedCompanions = val; return true;
        case SYM_GEN_buffFactor_2267: this->f_buffFactor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SpiritBells::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onBought_457: return true;
        case SYM_GEN_getData_638: return true;
        case SYM_GEN_setData_639: return true;
        case SYM_GEN_isAffectingDistinct_256: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_getBuffDur_1813: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onItemRoll_1923: return true;
        case SYM_GEN_onItemRolled_1924: return true;
        case SYM_GEN_getRelatedItems_461: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__LeatherHelm::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SpiritBells::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onBought_457: out = fn_onBought(args, argc); return true;
        case SYM_GEN_getData_638: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_639: out = fn_setData(args, argc); return true;
        case SYM_GEN_isAffectingDistinct_256: out = fn_isAffectingDistinct(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_getBuffDur_1813: out = fn_getBuffDur(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onItemRoll_1923: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_onItemRolled_1924: out = fn_onItemRolled(args, argc); return true;
        case SYM_GEN_getRelatedItems_461: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581));
    return gd::GdVal::from_bool(gd::gd_eq(lv_color, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpiritBells::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Pet_2600)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpiritBells::fn_getBuffDur(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_dur = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_base", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })();
    lv_dur = gd::gd_add(gd_ctx, lv_dur, gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur_bonus", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumDistinctAffectedItems_432, nullptr, 0)));
    return lv_dur;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpiritBells::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_buffFactor, gd::GdVal::from_int(1000LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_multiplyBuffsLimit_365, _ca, 2); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAfterEffectFinished_147, nullptr, 0);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__LeatherHelm::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_buffFactor = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "buffs", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
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
        case SYM_GEN_heatNeeded_1785: out = this->f_heatNeeded; return true;
        case SYM_GEN_debuffsCleansed_2475: out = this->f_debuffsCleansed; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SunArmor::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_heatNeeded_1785: this->f_heatNeeded = gd::gd_coerce_int(val); return true;
        case SYM_GEN_debuffsCleansed_2475: this->f_debuffsCleansed = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SunArmor::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_reactToItemTypeChange_459: return true;
        case SYM_GEN_onAffectedItemAdded_437: return true;
        case SYM_GEN_onAffectedItemRemoved_438: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SunArmor::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_reactToItemTypeChange_459: out = fn_reactToItemTypeChange(args, argc); return true;
        case SYM_GEN_onAffectedItemAdded_437: out = fn_onAffectedItemAdded(args, argc); return true;
        case SYM_GEN_onAffectedItemRemoved_438: out = fn_onAffectedItemRemoved(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Fire_2601)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Holy_2593)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SunArmor::fn_reactToItemTypeChange(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::gd_in(lv_item, gd::get_index(gd_ctx, this->f_currentAffectedItems, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581))))) {
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Fire_2601)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })()))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Holy_2593), gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasDynamicType_243, _ca, 2); })())) : gd::GdVal::from_bool(false)))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::call_method(gd_ctx, gd::get_index(gd_ctx, this->f_currentAffectedItems, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581)), gd::SYM_erase, _ca, 1); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Primary_2581)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onAffectedItemRemoved_438, _ca, 2); })();
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
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Fire_2601)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasType_81, _ca, 1); })())) {
        (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Holy_2593), gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addDynamicType_244, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SunArmor::fn_onAffectedItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_color = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_color = gd::gd_coerce_int(lv_color);
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), SYM_GEN_Holy_2593), gd::GdVal::from_obj(this)}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_removeDynamicType_245, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SunArmor::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getHeat_1235, nullptr, 0), this->f_heatNeeded)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_heatNeeded}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useHeat_356, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_debuffsCleansed, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_358, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "used_heat", 9u)), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_event}))}; return gd::call_method(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_bus_1379), SYM_GEN_emitSignal_1501, _ca, 3); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SunArmor::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_205, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_220, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SunArmor::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_heatNeeded = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0));
    this->f_debuffsCleansed = gd::gd_coerce_int(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0));
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
        case SYM_GEN_maxHealth_1049: out = this->f_maxHealth; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Twine::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_maxHealth_1049: this->f_maxHealth = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Twine::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_canAffect_secondary_289: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onTriggerItemActivated_2379: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Twine::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_289: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onTriggerItemActivated_2379: out = fn_onTriggerItemActivated(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_canActivate_93, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Twine::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_isNeutral_248, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Twine::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t1220 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1221 = (_t1220.kind == gd::GdVal::Kind::Arr) ? _t1220.arr : nullptr;
        uint32_t _len__t1222 = _t1221 ? _t1221->len : 0u;
        for (uint32_t _t1222 = 0; _t1222 < _len__t1222; ++_t1222) {
            gd::GdVal lv_triggerItem = _t1221->data[_t1222];
            (void)([&]() { gd::GdVal _ca[] = {lv_triggerItem, gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "activated", 9u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onTriggerItemActivated", 22u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Twine::fn_onTriggerItemActivated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_totalChance = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseChance_170, nullptr, 0);
    lv_totalChance = gd::gd_add(gd_ctx, lv_totalChance, gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Affected_867), SYM_GEN_Secondary_2583)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, _ca, 1); })(), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseChance2_171, nullptr, 0)));
    if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_totalChance}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, _ca, 1); })())) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_maxHealth, lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_319, _ca, 2); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Twine::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_maxHealth = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "health", 6u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
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
        case SYM_GEN_activated_1296: out = this->f_activated; return true;
        case SYM_GEN_healthThreshold_1759: out = this->f_healthThreshold; return true;
        case SYM_GEN_battleRageSpeed_1970: out = this->f_battleRageSpeed; return true;
        case SYM_GEN_battleRageDamReduction_2530: out = this->f_battleRageDamReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__WolfBadge::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activated_1296: this->f_activated = val; return true;
        case SYM_GEN_healthThreshold_1759: this->f_healthThreshold = val; return true;
        case SYM_GEN_battleRageSpeed_1970: this->f_battleRageSpeed = val; return true;
        case SYM_GEN_battleRageDamReduction_2530: this->f_battleRageDamReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__WolfBadge::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onAddToInventory_421: return true;
        case SYM_GEN_onRemoveFromInventory_420: return true;
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_onDamaged_1760: return true;
        case SYM_GEN_onBattleRageStarted_1971: return true;
        case SYM_GEN_onBattleRageEnded_1972: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN_getRelatedItems_461: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__WolfBadge::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onAddToInventory_421: out = fn_onAddToInventory(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_420: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDamaged_1760: out = fn_onDamaged(args, argc); return true;
        case SYM_GEN_onBattleRageStarted_1971: out = fn_onBattleRageStarted(args, argc); return true;
        case SYM_GEN_onBattleRageEnded_1972: out = fn_onBattleRageEnded(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN_getRelatedItems_461: out = fn_getRelatedItems(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_97, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WolfBadge::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_activated = gd::GdVal::from_bool(false);
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_damaged", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onDamaged", 9u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "battle_rage_started", 19u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBattleRageStarted", 19u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "battle_rage_ended", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onBattleRageEnded", 17u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WolfBadge::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_activated)))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_getRelativeHealth_304, nullptr, 0), this->f_healthThreshold)))) {
            this->f_activated = gd::GdVal::from_bool(true);
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "dur", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), lv_event}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_startBattleRage_1183, _ca, 3); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WolfBadge::fn_onBattleRageStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {this->f_battleRageDamReduction}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeDamageResistance_1263, _ca, 1); })();
    {
        gd::GdVal _t1223 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1224 = (_t1223.kind == gd::GdVal::Kind::Arr) ? _t1223.arr : nullptr;
        uint32_t _len__t1225 = _t1224 ? _t1224->len : 0u;
        for (uint32_t _t1225 = 0; _t1225 < _len__t1225; ++_t1225) {
            gd::GdVal lv_item = _t1224->data[_t1225];
            (void)([&]() { gd::GdVal _ca[] = {this->f_battleRageSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_275, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WolfBadge::fn_onBattleRageEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_battleRageDamReduction)}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeDamageResistance_1263, _ca, 1); })();
    {
        gd::GdVal _t1226 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
        gd::GdArr* _t1227 = (_t1226.kind == gd::GdVal::Kind::Arr) ? _t1226.arr : nullptr;
        uint32_t _len__t1228 = _t1227 ? _t1227->len : 0u;
        for (uint32_t _t1228 = 0; _t1228 < _len__t1228; ++_t1228) {
            gd::GdVal lv_item = _t1227->data[_t1228];
            (void)([&]() { gd::GdVal _ca[] = {this->f_battleRageSpeed}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_reduceSpeed_276, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WolfBadge::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Priority_856), SYM_GEN_High_2603), gd::GdVal::from_int(10LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WolfBadge::fn_getRelatedItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WolfBadge::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_healthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    this->f_battleRageSpeed = gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0), gd::GdVal::from_float(100.0));
    this->f_battleRageDamReduction = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_268, nullptr, 0);
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
        case SYM_GEN_gemColor_995: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.912109), gd::GdVal::from_float(0.904984), gd::GdVal::from_float(0.904984)}; return gd::make_color_from_args(_ca, 3); })();
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
        case SYM_GEN_activated_1296: out = this->f_activated; return true;
        case SYM_GEN_healthThreshold_1759: out = this->f_healthThreshold; return true;
        case SYM_GEN_gemColor_995: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core_items__Gems__Skull::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_activated_1296: this->f_activated = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_healthThreshold_1759: this->f_healthThreshold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Gems__Skull::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_prepareInventory_981: return true;
        case SYM_GEN_onOpponentDamaged_1897: return true;
        case SYM_GEN_prepareWeapon_982: return true;
        case SYM_GEN_onAttack_1957: return true;
        case SYM_GEN_prepareArmor_983: return true;
        case SYM_GEN_hasCooldown_97: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::has_own_method(m);
}
bool Gd__gd_core_items__Gems__Skull::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_prepareInventory_981: out = fn_prepareInventory(args, argc); return true;
        case SYM_GEN_onOpponentDamaged_1897: out = fn_onOpponentDamaged(args, argc); return true;
        case SYM_GEN_prepareWeapon_982: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_onAttack_1957: out = fn_onAttack(args, argc); return true;
        case SYM_GEN_prepareArmor_983: out = fn_prepareArmor(args, argc); return true;
        case SYM_GEN_hasCooldown_97: out = fn_hasCooldown(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "character_damaged", 17u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onOpponentDamaged", 17u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Skull::fn_onOpponentDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__healthChange = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_activated)))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_getRelativeHealth_304, nullptr, 0), this->f_healthThreshold)))) {
            this->f_activated = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
            (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "heal", 4u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_191, _ca, 1); })(), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_329, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0), lv_event}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_219, _ca, 2); })();
            (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Skull::fn_prepareWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, this->f_socket, SYM_GEN_getItem_391, nullptr, 0), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "attacked", 8u)), gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "onAttack", 8u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_502, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Skull::fn_onAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance2_176, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stealRandomBuff_375, _ca, 1); })();
        (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_472, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Skull::fn_prepareArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeDebuffResistChances_1204, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_173, nullptr, 0))}; return gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_76, nullptr, 0), SYM_GEN_changeCritResistance_1157, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Skull::fn_hasCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Gems__Skull::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_healthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
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
        case SYM_GEN_numActivations_1809: out = this->f_numActivations; return true;
        case SYM_GEN_speedBonus_1782: out = this->f_speedBonus; return true;
        case SYM_GEN_maxActivations_1810: out = this->f_maxActivations; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Jynxtorquilla::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numActivations_1809: this->f_numActivations = gd::gd_coerce_int(val); return true;
        case SYM_GEN_speedBonus_1782: this->f_speedBonus = val; return true;
        case SYM_GEN_maxActivations_1810: this->f_maxActivations = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Jynxtorquilla::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPrepare_125: return true;
        case SYM_GEN_doCooldownEffect_146: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Jynxtorquilla::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_125: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_146: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::call_method(gd_ctx, lv_item, SYM_GEN_hasCooldown_97, nullptr, 0);
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
            gd::GdVal _t1229 = gd::gd_iter_seq(gd_ctx.arena, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_422, nullptr, 0));
            gd::GdArr* _t1230 = (_t1229.kind == gd::GdVal::Kind::Arr) ? _t1229.arr : nullptr;
            uint32_t _len__t1231 = _t1230 ? _t1230->len : 0u;
            for (uint32_t _t1231 = 0; _t1231 < _len__t1231; ++_t1231) {
                gd::GdVal lv_item = _t1230->data[_t1231];
                (void)([&]() { gd::GdVal _ca[] = {this->f_speedBonus}; return gd::call_method(gd_ctx, lv_item, SYM_GEN_addSpeed_275, _ca, 1); })();
            }
        }
        this->f_numActivations = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_numActivations, gd::GdVal::from_int(1LL)));
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::call_method(gd_ctx, gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_77, nullptr, 0), SYM_GEN_getLucky_1221, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_267, nullptr, 0)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeLucky_351, _ca, 1); })();
    }
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Jynxtorquilla::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_speedBonus = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "speed", 5u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_maxActivations = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::make_str(gd_ctx.arena, "max", 3u))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_190, _ca, 1); })());
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
        case SYM_GEN_canAffect_288: return true;
        case SYM_GEN_onPreCombatStart_127: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onCalcTradeChance_1730: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__PlatinCustomerCard::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_288: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPreCombatStart_127: out = fn_onPreCombatStart(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onCalcTradeChance_1730: out = fn_onCalcTradeChance(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    return gd::GdVal::from_bool(gd::gd_ge(gd::call_method(gd_ctx, lv_item, SYM_GEN_getRarity_238, nullptr, 0), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Rarity_862), SYM_GEN_Legendary_2738)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__PlatinCustomerCard::fn_onPreCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_429, nullptr, 0), gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_266, nullptr, 0))}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveReflectStacks_202, _ca, 1); })();
    (void)gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_152, nullptr, 0);
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
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_digUpItems_1883: out = this->f_digUpItems; return true;
        case SYM_GEN_digParticles_1884: out = this->f_digParticles; return true;
        case SYM_GEN_spawnPos_1885: out = this->f_spawnPos; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Shovel::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_digUpItems_1883: this->f_digUpItems = val; return true;
        case SYM_GEN_digParticles_1884: this->f_digParticles = val; return true;
        case SYM_GEN_spawnPos_1885: this->f_spawnPos = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Shovel::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Shovel::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    if (gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0))) {
        if (gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, nullptr, 0))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1426)}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_215, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Shovel::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
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
        case SYM_GEN_permDamBonus_997: out = this->f_permDamBonus; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Torch::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_permDamBonus_997: this->f_permDamBonus = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Torch::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_142: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Torch::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_142: out = fn__readyInit(args, argc); return true;
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
    if (gd::gd_truth((gd::gd_truth(gd::call_method(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1432, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_175, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_permDamBonus}; return gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addBonusDamage_163, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Torch::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_142, nullptr, 0, _out); return _out; })();
    this->f_permDamBonus = gd::call_method(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_265, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Torch(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Torch>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Torch = {CLS_Gd__gd_core_items__Torch, "Torch", "res://gd_core_items/Torch.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Torch, &Gd__gd_core_items__Torch::get_static_prop_fn, &Gd__gd_core_items__Torch::call_static_fn};
